/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpc_pkt.c
  �� �� ��   : ����
  ��    ��   : yuqingping(25027)
  ��������   : 2002��11��21��
  ����޸�   :
  ��������   : dhcpcģ��ı��Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2002��11��21��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ļ�

******************************************************************************/
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

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_PKT_C
/*lint +e767*/



/*****************************************************************************
 �� �� ��  : DHCPC_GetOneContextByteidc
 ��������  : ����Teidc��ȡ1�������ġ������Ĵ����򷵻�ָ�������ĵ�ָ�룬������
             �򷵻�NULL����ȡ����ָ�벻��Ҫ�ͷš�
 �������  : ULONG ulTeidc,
 �������  : ��
 �� �� ֵ  : SDB_GSPU_CONTEXT_S * �����ĵ�ָ��
 ���ú���  : SDB_GTPC_GetRelatedContextsByTeidc
 ��������  : DHCPC_Pkt_ProcDHCP

 ��    ��   : 2011-07-20
 ��    ��   : jixiaoming

*****************************************************************************/
SDB_GSPU_CONTEXT_S * DHCPC_GetOneContextByteidc(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    ULONG ulContextsNum = 0;
    SDB_GSPU_CONTEXT_S *pstRelContexts[M_MNT_MAX_PDP_NUM] = {NULL};

    ulRet = (ULONG)SDB_GTPC_GetRelatedContextsByTeidc(ulTeidc, &ulContextsNum, (UCHAR **)pstRelContexts);
    if ((SDB_SUCCESS == ulRet) && (NULL != pstRelContexts[0]))
    {
        return pstRelContexts[0];
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : DHCPC_PGWPerfStat
 ��������  : PGW����ͳ��
 �������  : UCHAR ucMsgType
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 ��    ��   : 2011-06-22
 ��    ��   : ������

*****************************************************************************/
VOID DHCPC_PGWPerfStat(UCHAR ucMsgType)
{
    switch(ucMsgType)
    {
        case DHCP_DISCOVER:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4DiscoveryNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4DiscoveryNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_REQUEST:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4RequestNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4RequestNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_DECLINE:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4DeclineNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4DeclineNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_RELEASE:
            if (VOS_NULL_PTR != g_PGWtoServer_ulDHCPV4ReleaseNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoServer_ulDHCPV4ReleaseNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_OFFER:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4OfferNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4OfferNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_ACK:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4AckNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4AckNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        case DHCP_NAK:
            if (VOS_NULL_PTR != g_ServertoPGW_ulDHCPV4akNumAddr)
            {
                (VOID)PerfSetFamPerfCounterByAddress(g_ServertoPGW_ulDHCPV4akNumAddr, E_PERF_OBJECT_ADD, 1);
            }
            break;

        default :
            break;
    }
}


ULONG DHCPC_Pkt_CheckPkt(DHCP_S  *pstDHCPPkt)
{
    ULONG ulHostOrderAddress = 0;

    /*----------------DHPC���ĺϷ��Լ��----------------------*/
    if ( ( ( VOS_HTONL( pstDHCPPkt->ulYiaddr )&( ULONG )0xE0000000 )==( ULONG )0xE0000000 )
         ||( ( VOS_HTONL( pstDHCPPkt->ulSiaddr )&( ULONG )0xE0000000 )==( ULONG )0xE0000000 ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_105);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP )" );
        return VOS_ERR;
    }
    ulHostOrderAddress = VOS_HTONL( pstDHCPPkt->ulYiaddr );
    if (  0 ==  ulHostOrderAddress )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_106);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP )" );
        return VOS_ERR;
    }

    if (VOS_OK != GTPC_RadiusHlrIPValidCheck(pstDHCPPkt->ulYiaddr))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_107);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP = %u )",VOS_HTONL( pstDHCPPkt->ulYiaddr ) );
        return VOS_ERR;
    }

    if( (ulHostOrderAddress  ==  0x7FFFFFFF)
        || (ulHostOrderAddress == 0x80000000) || (ulHostOrderAddress == 0xBFFFFFFF)
        || (ulHostOrderAddress == 0xC0000000) || (ulHostOrderAddress == 0xDFFFFFFF) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_108);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP Failed to process server packet(invalid IP = %u )",ulHostOrderAddress );
        return VOS_ERR;
    }
    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : DHCPC_TransMsisdnToCallFromID
 ��������  : MSISDN BCD->ASSIC
 �������  : UCHAR *pucMsisdn
             UCHAR *pucCallFromId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��27��
    ��    ��   : caopu
    �޸�����   : ��ֲfrom gtpc

*****************************************************************************/
UCHAR DHCPC_TransMsisdnToCallFromID ( UCHAR *pucMsisdn, UCHAR *pucCallFromId )
{
    int   i = 0;
    UCHAR ucCallFromIdLen = 0;      /*���к��볤��*/

    if ( ( pucMsisdn == NULL ) || ( pucCallFromId == NULL ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_098);
        return ucCallFromIdLen;
    }

    for ( i=0; i<DHCP_MAX_MSISDN_LEN; i++ )
    {
        if ( 0X0F != ( ( *( pucMsisdn+i ) )&0X0F ) )
        {
            /*ת�����ַ�����ʽ*/
            *( pucCallFromId+ucCallFromIdLen ) = ( ( *( pucMsisdn+i ) )&0X0F ) + 48;
            ucCallFromIdLen++;
        }
        if ( 0XF0 != ( ( *( pucMsisdn+i ) )&0XF0 ) )
        {
            /*ת�����ַ�����ʽ*/
            *( pucCallFromId+ucCallFromIdLen ) = ( ( ( *( pucMsisdn+i ) )&0XF0 )>>4 ) + 48;
            ucCallFromIdLen++;
        }
    }

    return ucCallFromIdLen;
}
ULONG DHCPC_FillClientIdOption(UCHAR *pucOption, ULONG aulMsisdn[])
{
    UCHAR   szMSISDN[DHCP_MAX_MSISDN_STRING_LEN + 1] = {0};
    ULONG   ulMsisdnLen = 0;

    if ((NULL == pucOption) || (NULL == aulMsisdn))
    {
        VOS_Assert(0);
        return 0;
    }

    (VOID)DHCPC_TransMsisdnToCallFromID((UCHAR *)aulMsisdn, szMSISDN);
    ulMsisdnLen = VOS_StrLen(szMSISDN);
    if (0 == ulMsisdnLen)
    {
        return 0;
    }
    else
    {
        *pucOption++ = DHCP_CLIENTID_CODE;
        *pucOption++ = (UCHAR)(ulMsisdnLen + 1);   /*7;ѡ��� ����Ϊ 17*/
        *pucOption++ = 0;                    /*ʹ��MSISDN��ΪID�Ƿ���Ҫ�ı�Typeֵ*/
        VOS_MemCpy(pucOption, szMSISDN, ulMsisdnLen);
    }

    return ulMsisdnLen + 3;
}

/*****************************************************************************
 �� �� ��  : DHCPC_Pkt_ProcDHCPRELEASE
 ��������  : ����Release����
 �������  :
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��23��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/

ULONG DHCPC_Pkt_ProcDHCPRELEASE ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    DHCPC_TEMPCTRLBLK    *pItemInfo = NULL;
	DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPNACK()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_099);
    if (NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_100);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release pstDhcpCtrlBlkNode is NULL!" );
        return VOS_ERR;
    }
    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*��ȡDHCP���ƿ�*/
    pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_101);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release enter error!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    if ( ( DHCPC_STATE_BOUND        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_LEASE        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pstDhcpCtrlBlk->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding        != pstDhcpCtrlBlk->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_102);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPRelease state err!" );
        return VOS_ERR;
    }

    (VOID)DHCPC_StopTimer(pstDhcpCtrlBlk->ucIpType, pstDhcpCtrlBlk->ulTEIDC, 0);
    ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode,DHCPC_SND2_LAP2_ADDR_REL_MSG );
    DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlk->ulDHCPCtxIdx, pstDhcpCtrlBlk->ulTEIDC, pstDhcpCtrlBlk->ucUser, pstDhcpCtrlBlk->ulPDPIndex);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_PktProc_RcvDHCP
 ��������  : �����յ���DHCP�ı��ģ����з���
 �������  : DHCP_S  *pstDHCPPkt
             ULONG       ulOptionLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��22��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG  DHCPC_Pkt_ProcDHCP( DHCP_S  *pstDHCPPkt, ULONG ulOptionLen,ULONG ulSrvIpAddr )
{
    DHCPC_TEMPCTRLBLK   *pstHashItem = NULL;
    DHCPC_CTRLBLK_NODE  *pstDhcpCtrlBlkNode = NULL;
    DHCPC_CTRLBLK       *pstDhcpCtrBlk = NULL;
    DHCP_OPTION_S       stDhcpOption;
    ULONG               ulUserIpAddr = 0;
    ULONG               ulDHCPCtxIdx = 0;        /*DHCP���ƿ�����*/
    ULONG               ulRet = 0;
    UCHAR               ucSCID = 0;
    UCHAR               ucRenewFlg = VRP_NO;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCP()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_206);

    if ( NULL == pstDHCPPkt )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_103);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP NULL packet!" );
        return NULL;
    }

    /*�жϱ��������Ƿ�ȷʵ��DHCPREPLY*/
    if ( pstDHCPPkt->ucOp != DHCP_OP_REPLY )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_104);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP receive a request packet!" );
        return VOS_ERR;
    }

    /*ȡ�����е�OPTION*/
    PGP_MemZero( ( CHAR * )&stDhcpOption,  sizeof( DHCP_OPTION_S ) );
    if ( VOS_OK != DHCPR_RecordAllOption( &stDhcpOption,pstDHCPPkt,ulOptionLen ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_109);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP dhcp options error!" );
        return VOS_ERR;
    }

    if ( NULL == stDhcpOption.pucDHCPMsgType )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_110);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP DHCP type error!" );
        return VOS_ERR;
    }

    /*��ȡDHCP���ƿ�*/
    pstDhcpCtrBlk = (DHCPC_CTRLBLK *)DHCPC_LookupCtlBlkNodeIntoHashTable( pstDHCPPkt );
    if( NULL == pstDhcpCtrBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_115);
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {

            DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                TRC_DIRECTION_RIGHT_IN_UGW_ERR,
                                (UCHAR*)pstDHCPPkt,
                                (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                LAP_IPV4,
                                &ulSrvIpAddr);
        }
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\nDHCPC_Pkt_ProcDHCP get DhcpCtrlBlk error ulDHCPCtxIdx = %u!",ulDHCPCtxIdx );
        /*��ǰ�û�û�д���dhcp���ƿ飬���ߵ�ǰ�û���������ȷ*/
        return VOS_ERR;
    }

    /*��ȡ��SC��id*/
    ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    /* �����ǰ���ƿ鲻Ϊ��ʼ״̬ (�ǵ�һ�μ�������) */
    if ( DHCPC_STATE_INITIAL != pstDhcpCtrBlk->usDhcpStatus )
    {
        ulRet = DHCPC_SetServerStatusToNormalByIndexAndIp(pstDhcpCtrBlk->usServerGrpIndex, ulSrvIpAddr);
        if (VOS_OK != ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_248);
            return ulRet;
        }

        /* V9 DHCP ���صĵ�ַ������SDB�������У�����ַ������ƿ鱣�棬��
        ����ʱ���ƿ鲻Ϊ��ʼ״̬����IP��ַ�ض���Ϊ0��0xFFFFFFFF����ʱ��
        ַ���ݿ��ƿ��е��ж� comment by caopu */
        ulUserIpAddr = pstDhcpCtrBlk->aulUserIpAddr[0];
        if ( ( 0 == ulUserIpAddr ) || ( 0xffffffff == ulUserIpAddr ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_116);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP get user ip fail when renew ip!" );
            /* ��ʱDHCP״̬������ */
            return VOS_ERR;
        }
        /*�������û�,�Լ�����һ�����ƿ�ڵ�*/
        pstDhcpCtrlBlkNode = ( DHCPC_CTRLBLK_NODE* )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK_NODE ) );
        if ( NULL == pstDhcpCtrlBlkNode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_117);
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCP memory alloc failed!" );
            return VOS_ERR;
        }
        /* ���ӱ�Ҫ��������� */
        PGP_MemZero(pstDhcpCtrlBlkNode, sizeof(DHCPC_CTRLBLK_NODE));
        /* pstHashItemΪ��ʱ���ƿ� */
        pstHashItem = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );
        DHCPC_INIT_ITEM( pstHashItem );
        pstHashItem->usLease = pstDhcpCtrBlk->ulLease;
        pstHashItem->ulSrvIp= pstDhcpCtrBlk->aulSrvIp[0];
        pstHashItem->ulTimeStamp= pstDhcpCtrBlk->ulTmpVar;    /*����REQ��ʱ�䱣����ulTmpVar*/
        pstHashItem->usDhcpStatus= pstDhcpCtrBlk->usDhcpStatus;
        pstHashItem->ulUserIpAddr = ulUserIpAddr;
        pstHashItem->ulPdpIndex = pstDhcpCtrBlk->ulPDPIndex;    /*ST*/
        pstHashItem->ulDHCPCtlIdx = pstDhcpCtrBlk->ulDHCPCtxIdx;
        pstHashItem->ucUserType = pstDhcpCtrBlk->ucUserType;
        pstHashItem->aulMSISDN[0] = pstDhcpCtrBlk->aulMSISDN[0];
        pstHashItem->aulMSISDN[1] = pstDhcpCtrBlk->aulMSISDN[1];
        pstHashItem->aulIMSI[0] = pstDhcpCtrBlk->aulIMSI[0];
        pstHashItem->aulIMSI[1] = pstDhcpCtrBlk->aulIMSI[1];
        /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
        pstHashItem->aulIMEI[0] = pstDhcpCtrBlk->aulIMEI[0];
        pstHashItem->aulIMEI[1] = pstDhcpCtrBlk->aulIMEI[1];
        /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */

        pstHashItem->ulAgetIP = pstDhcpCtrBlk->aulAgentIpAddr[0];
        pstHashItem->usPoolIndex = pstDhcpCtrBlk->usPoolIndex;
        pstHashItem->usDhcpGroupIndex = pstDhcpCtrBlk->usServerGrpIndex;
        /* BEGIN: Added for PN:DHCP Lease backup by jiahuidong, 2009/7/15 */
        pstHashItem->usVpnId= pstDhcpCtrBlk->usVPNIndex;
        /* END:   Added for PN:DHCP Lease backup by jiahuidong, 2009/7/15 */
        /* Start: Add by zhangyang for PN:BI8D02498, 2010/4/24 */
        pstHashItem->ucRole = pstDhcpCtrBlk->ucRole;
        /* End: Add by zhangyang for PN:BI8D02498, 2010/4/24 */
        /*usApnIndex�Ƿ���Ҫ?���Կ��Ǵ�Server�����ı�������ȡ*/
        pstHashItem->ucUser= pstDhcpCtrBlk->ucUser;
        pstHashItem->ulTEIDC = pstDhcpCtrBlk->ulTEIDC;
        ucRenewFlg = VRP_YES;
        pstHashItem->ucSCID = ucSCID;
        /* ���е�ַ�������ã���ǰָ��ΪIPv4 */
        pstHashItem->ucAddressType = LAP_IPV4;
        /* BEGIN: Added by jixiaoming at 2011-04-13 */
        pstHashItem->ucLAPNo = pstDhcpCtrBlk->ucLAPNo;
        /* END: Added by jixiaoming at 2011-04-13 */
        pstHashItem->ucRandomNo = pstDhcpCtrBlk->ucRandomNo;

    }
    /* �����ǰ���ƿ��һ�����������е�״̬ */
    else
    {
        /*ȡ��ʱ���ƿ�ָ�룬���жϸ��ڴ����Ƿ���ʱ���ƿ�?*/
        pstDhcpCtrlBlkNode = DHCPC_GetTmpDhcpCtrlBlkPtr( pstDhcpCtrBlk );
        if ( NULL == pstDhcpCtrlBlkNode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_118);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP find no DHCP temp control block!" );
            return VOS_ERR;
        }
        pstHashItem = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

        ulRet = DHCPC_SetServerStatusToNormalByIndexAndIp(pstHashItem->usDhcpGroupIndex, ulSrvIpAddr);
        if (VOS_OK != ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_250);
            return ulRet;
        }

        /*�û������е�ulXid�뱨�����Ƿ����*/
        if ( VOS_HTONL(pstDHCPPkt->ulXid) != pstHashItem->ulXid )
        {
            if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
            {

                DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                    TRC_DIRECTION_RIGHT_IN_UGW_ERR,
                                    (UCHAR*)pstDHCPPkt,
                                    (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                    LAP_IPV4,
                                    &ulSrvIpAddr);
            }
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_121);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP Xid different!" );
            return VOS_ERR;
        }
    }

{
//        ULONG ulRet = 0;
        SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
        /* BEGIN: Added for PN:ȫ������  by LiHairong, 2010/4/8 */
        RM_SOCKET_PATH_S stPath = {0};
        S_OM_EMS_TRC_PARA stTrcPara = {0};
        /* END:   Added for PN:ȫ������  by LiHairong, 2010/4/8 */
        /* Start: Add by zhangyang for PN:BI8D02498, 2010/4/24 */
        ULONG ulDirection = TRC_DIRECTION_RIGHT_IN_PGW;
        /* End: Add by zhangyang for PN:BI8D02498, 2010/4/24 */

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP Trace !" );

        /*����Teidc, ��ȡ1��������*/
        pstContext = DHCPC_GetOneContextByteidc(pstDhcpCtrBlk->ulTEIDC);
        if (NULL == pstContext)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_114);
            if ( VRP_YES == ucRenewFlg )
            {
                DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode);
                pstDhcpCtrlBlkNode = NULL;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCP : SDB_GetContextByIndex return ERR.!" );
            return VOS_ERR;
        }
        /* Start: Modify by zhangyang for PN:BI8D02498, 2010/4/24 */
        if(( E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole )||( E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole ))
        {
            ulDirection = TRC_DIRECTION_RIGHT_IN_UGW;
        }

        UGW_OmUsrMsgTrace((UCHAR *)pstDHCPPkt,
                         GUSER_MSGTYPE_DHCPV4,
                         (ULONG)*( stDhcpOption.pucDHCPMsgType ) + ulDirection,
                         (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                         (UCHAR *)&(pstContext->stImsi),
                         (UCHAR *)&(pstContext->stIMEI),
                         pstContext->szMsisdn,
                         pstContext->ucRandomNo);
        /* Start: Modify by zhangyang for PN:BI8D02498, 2010/4/24 */

        /* DHCP������ϢV�ӿڸ��� */ /* ��TrcGetTraceFlag()���÷��ڸ��ٺ���֮��,����Ч�� */
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {

            DHCPC_OmVIfMsgTrc((ULONG)*(stDhcpOption.pucDHCPMsgType),
                                ulDirection,
                                (UCHAR*)pstDHCPPkt,
                                (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen),
                                LAP_IPV4,
                                &ulSrvIpAddr);
        }

        /* BEGIN: Added for PN:ȫ������  by LiHairong, 2010/4/10 */
        stPath.ulLocalAddr = pstHashItem->ulAgetIP;
        stPath.ulPeerAddr = ulSrvIpAddr;
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stPath.usLocalPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stPath.usLocalPort = DHCPC_PKT_PORTNO;
        }
        stPath.usPeerPort = DHCPS_PKT_PORTNO;

        stTrcPara.pucTrcMsg = (UCHAR *)pstDHCPPkt;
        stTrcPara.ucMsgType = (UCHAR)*( stDhcpOption.pucDHCPMsgType );
        stTrcPara.ucUgwRole = pstContext->ucUgwRole;
        stTrcPara.usMsgLen = (USHORT)(DHCPC_PKT_FIXEDFIELD_LEN + ulOptionLen);
        stTrcPara.ulEmsTrcDir = M_EMS_TRC_RECV_MSG;
        stTrcPara.ulUsrTrcDir = TRC_DIRECTION_RIGHT_IN_PGW;
        stTrcPara.usTraceId = pstContext->usTraceId;
        stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
        stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
        stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
        stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
        stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV4;
        stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
        stTrcPara.ucMsgSndFlg = 0;
        if((1 == stTrcPara.ucSgwTrcFlg)
            || (1 == stTrcPara.ucPgwTrcFlg))
        {
            UGW_OmEmsTrcMsgTrc(&stTrcPara,&stPath);
        }
        /* END:   Added for PN:ȫ������  by LiHairong, 2010/4/10 */

        /* PGW����ͳ�� */
        if ((E_NET_ELEMENT_ROLE_PGW == pstContext->ucUgwRole) || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole))
        {
            DHCPC_PGWPerfStat(*(stDhcpOption.pucDHCPMsgType));
        }
}

    if( DHCP_NAK != *( stDhcpOption.pucDHCPMsgType ) )
    {
        ulRet = DHCPC_Pkt_CheckPkt(pstDHCPPkt);
        if(VOS_ERR == ulRet)
        {
            if ( VRP_YES == ucRenewFlg )
            {
                DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode );
                pstDhcpCtrlBlkNode = NULL;
            }
            return VOS_ERR;
        }
    }

    switch ( *( stDhcpOption.pucDHCPMsgType ) )
    {
/* BEGIN: Modified by jixiaoming at 2011-03-02 */
        case DHCP_OFFER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_207);

            VOS_Assert( VRP_NO == ucRenewFlg );
            ( VOID )DHCPC_Pkt_ProcDHCPOFFER( pstDHCPPkt, &stDhcpOption, pstDhcpCtrlBlkNode );
            break;

        case DHCP_ACK:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_208);
            ( VOID )DHCPC_Pkt_ProcDHCPACK( pstDHCPPkt, &stDhcpOption, pstDhcpCtrlBlkNode );
            break;

        case DHCP_NAK:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_209);
            ( VOID )DHCPC_Pkt_ProcDHCPNACK( pstDhcpCtrlBlkNode );
            break;
/* END: Modified by jixiaoming at 2011-03-02 */
        case DHCP_RELEASE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_210);
            ( VOID )DHCPC_Pkt_ProcDHCPRELEASE ( pstDhcpCtrlBlkNode );
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_122);
            VOS_Assert( 0 );
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_Pkt_ProcDHCP unknown dhcp packet type!" );
            break;
    }

    if ( VRP_YES == ucRenewFlg )
    {
        DHCP_Free( DHCPC_HANDLE, pstDhcpCtrlBlkNode );
        pstDhcpCtrlBlkNode = NULL;
    }
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : DHCPC_PktProc_OFFER
 ��������  : ����offer����
 �������  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��23��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPOFFER ( DHCP_S *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    ULONG               ulRet = 0;
    DHCPC_TEMPCTRLBLK   *pItemInfo = NULL;
    ULONG               ulDnsNum = 0;

    if((NULL == pstDHCPPkt) || (NULL == pstDhcpOption) || (NULL == pstDhcpCtrlBlkNode))
    {
        VOS_Assert(0);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_123);
        return VOS_ERR;
    }

    DHCPC_FUNC_ENTRY();

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*--------------------------���ļ��--------------------------*/
    if ( DHCPC_STATE_DISCOVER != pItemInfo->usDhcpStatus )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_124);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "Dhcp State error!" );
        return VOS_ERR;
    }

    /*�����е����ݱ��浽item��*/
    pItemInfo->ulUserIpAddr        = pstDHCPPkt->ulYiaddr;
    if (pItemInfo->ulAgetIP == pstDHCPPkt->ulYiaddr)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_225);
        (VOID)DHCPC_Pkt_Send(DHCP_DECLINE, pItemInfo);
        return VOS_ERR;
    }

    if ( NULL != pstDhcpOption->pulLeaseTime )
    {
        pItemInfo->usLease = VOS_HTONL(*pstDhcpOption->pulLeaseTime);
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_125);
        /*DHCPOFFER MUST carry IP address lease time*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER OFFER carry no IP address lease time!" );
        return VOS_ERR;
    }

    /*��¼server-ip*/
    if ( NULL != pstDhcpOption->pulDHCPServerIp )
    {
        pItemInfo->ulSrvIp = *pstDhcpOption->pulDHCPServerIp;
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_126);
        /*DHCPOFFER MUST carry Server identifier*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER OFFER carry no server ip!" );
        return VOS_ERR;
    }

    /*��¼DNS IP*/
    if ( ( NULL != pstDhcpOption->pulDNSIp )&&( 0 == ( pstDhcpOption->ucDNSIpLen%4 ) ) && ( 0 != ( pstDhcpOption->ucDNSIpLen/4 ) ) )
    {
        ulDnsNum = pstDhcpOption->ucDNSIpLen/4;
        if ( ulDnsNum >= 2 )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_127);
            /*���ڷ��ض��DNS Server,ֻ����ǰ����DNS,��������DNS IP*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulDnsNum=%u,pItemInfo->ulPriDNSIP=%u!",ulDnsNum,pItemInfo->ulPriDNSIP );
            VOS_MemCpy( ( VOID* )&pItemInfo->ulSecDNSIP,( VOID* )( pstDhcpOption->pulDNSIp + 1 ),4 );

            pItemInfo->ulSecDNSIP = *(pstDhcpOption->pulDNSIp + 1) ;
            if (pItemInfo->ulPriDNSIP == pItemInfo->ulSecDNSIP)
            {
                pItemInfo->ulSecDNSIP = 0;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x ulSecDNSIP=%x",pItemInfo->ulPriDNSIP,pItemInfo->ulSecDNSIP );
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_128);

            /*ֻ����һ��DNS Server*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;

            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x", pItemInfo->ulPriDNSIP);
        }
    }

    /* ����״̬ΪDHCPC_STATE_REQUEST */
    DHCPC_ITEM_SETSATE( pItemInfo, DHCPC_STATE_REQUEST );

    /*���ķ���*/
    ulRet = DHCPC_Pkt_Send( DHCP_REQUEST, pItemInfo );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_129);
        /*ɾ��ʱ���ڵ�*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPOFFER send REQUEST error!" );

        /* zhangjinquan ֪ͨlap2����ʧ�� */
        ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPOFFER inform LAP2 error!" );
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_050);
        }
        DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser,
        pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);
        DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
        DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
        return VOS_ERR;
    }
    /*���÷��ͱ�־*/
    pItemInfo->usAlreadySendFlg = DHCPC_FIRSTSEND;
    DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
    DHCPC_InSertNodeAfterSecs( DHCPC_4_SECONDS, pstDhcpCtrlBlkNode );

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : DHCPC_PktProc_ACK
 ��������  : ����ack����
 �������  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��23��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPACK ( DHCP_S  *pstDHCPPkt, DHCP_OPTION_S *pstDhcpOption, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*
    *1�������������û�(ucModId = null)��ֱ��дSDB��
    *�޸�lease��time-stamp��status��ע��д���ݱ�־
    *2�����������û����޸�sdb��д��DHCP���ƿ飬���ݱ�־
    *֪ͨGTPC/PPPC��ɾ��ʱ���ƿ飻g_ulDhcpTotalCtrlBlkNum--;
    *3�����IP��ַ����Ч�ԣ���Ч��֪ͨGTPC/PPPC��
    *��Ч����SERVER��DECLINE��ͬʱ֪ͨGTPC/PPPC���ɹ�;
    *4�����IP��ַ�Ƿ��Ѿ����ظ�ʹ�ã�
    *����ǣ�����SERVER��DECLINE��ͬʱ֪ͨGTPC/PPPC���ɹ�;
    *5������ACK ���ģ����������û����͵�����
    *ֻҪ�����ҵ��������ģ���Ȼ��Ч
    *6�������IP��ַ����ɹ���֪ͨGTPC/PPPCģ��ʱ�����ز��ɹ�
    *����server����Release����
    */
    DHCPC_TEMPCTRLBLK   *pItemInfo = NULL;
    ULONG               ulDnsNum = 0;
    ULONG               ulRet = VOS_OK;
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPACK()" );

    if((NULL == pstDHCPPkt) || (NULL == pstDhcpOption) || (NULL == pstDhcpCtrlBlkNode))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_130);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCPOFFER NULL error!" );
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );


    if ( ( DHCPC_STATE_REQUEST        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_LEASE           != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding       != pItemInfo->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_131);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK state err!" );
        return VOS_ERR;
    }

    if ( NULL != pstDhcpOption->pulLeaseTime )
    {
        pItemInfo->usLease = VOS_HTONL(*pstDhcpOption->pulLeaseTime);
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_132);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK ACK carry no lease time!" );
        return VOS_ERR;
    }

    /*��¼DNS IP*/
    if ( ( NULL != pstDhcpOption->pulDNSIp )&&( 0 == ( pstDhcpOption->ucDNSIpLen%4 ) ) && ( 0 != ( pstDhcpOption->ucDNSIpLen/4 ) ) )
    {
        ulDnsNum = pstDhcpOption->ucDNSIpLen/4;
        if ( ulDnsNum >= 2 )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_133);
            /*���ڷ��ض��DNS Server,ֻ����ǰ����DNS,��������DNS IP*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulDnsNum=%u,pItemInfo->ulPriDNSIP=%u!",ulDnsNum,pItemInfo->ulPriDNSIP );
            VOS_MemCpy( ( VOID* )&pItemInfo->ulSecDNSIP,( VOID* )( pstDhcpOption->pulDNSIp + 1 ),4 );

            pItemInfo->ulSecDNSIP = * ( pstDhcpOption->pulDNSIp + 1) ;
            if (pItemInfo->ulPriDNSIP == pItemInfo->ulSecDNSIP)
            {
                pItemInfo->ulSecDNSIP = 0;
            }
            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x ulSecDNSIP=%x",pItemInfo->ulPriDNSIP,pItemInfo->ulSecDNSIP );
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_134);

            /*ֻ����һ��DNS Server*/
            pItemInfo->ulPriDNSIP = *pstDhcpOption->pulDNSIp;

            DHCPC_DebugPrint(PTM_LOG_DEBUG,  "ulPriDNSIP=%x",pItemInfo->ulPriDNSIP);
        }
    }

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST:
        {
             /* ��ַ��һ���ͷŵ�ǰIP */
            if ( pstDHCPPkt->ulYiaddr != pItemInfo->ulUserIpAddr )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_200);
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );

                /* zhangjinquan ֪ͨlap2����ʧ�� */
                ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
                if (VOS_OK != ulRet)
                {
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK inform LAP2 error 1!" );
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_057);
                }

                DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );
                DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
                return VOS_ERR;
            }
            if ( VOS_ERR == DHCPC_SaveSdbDhcpCtrlBlk( pItemInfo, VOS_FALSE ) )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_135);
                /*����IP�û�:
                  *���ƿ������Ѿ��ı䣬��ʱ���ɾ���ڵ�
                  *ɾ�����ƿ�ڵ㣬�ͷ��ڴ�
                  */
                /* zhangjinquan ֪ͨlap2����ʧ�� */
                ulRet = DHCPC_SendMsgToLAP2(pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
                if (VOS_OK != ulRet)
                {
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK inform LAP2 error 2!" );
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_061);
                }

                /* ����release��Ϣ */
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );

                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPACK save SDB err!" );
                DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );

                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );

                DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
                return VOS_ERR;
            }

            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_219);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode ,DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG );

            /*ɾ�����ƿ�ڵ㣬�ͷ��ڴ�*/
            DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
            DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
            break;
        }

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:
        {

            (VOID)DHCPC_StopTimer(pItemInfo->ucAddressType, pItemInfo->ulTEIDC, 0);
            /* �˴��ж�DHCP Server ���ص�IP�Ƿ�͵�ǰ��һ��,Ӧ�ò��᷵�ز�һ�µ������??????? by caopu*/
            if ( pstDHCPPkt->ulYiaddr == pItemInfo->ulUserIpAddr )
            {
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK For Lease!" );
                if ( VOS_ERR == DHCPC_SaveSdbDhcpCtrlBlk( pItemInfo, VOS_TRUE ) )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_136);
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK save SDB after renew err!" );
                    DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );
                    return VOS_ERR;
                }

                if (VOS_OK != DHCPC_NotifyBKUpdate(pItemInfo->ulTEIDC))
                {
                    /* ֻ��Ӵ����� */
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
                }

            }
            else
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_216);
                /* ��ַ��һ���ͷŵ�ǰIP */
                if ( VOS_ERR == DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG ) )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_137);
                    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_ProcDHCPACK delete user !" );
                    return VOS_ERR;
                }

                /* ����release��Ϣ */
                ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pItemInfo );
                DHCPC_FreeDhcpCtrlBlk( pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC, pItemInfo->ucUser, pItemInfo->ulPdpIndex );

                /* END:   Added for PN: Lease backup by jiahuidong, 2009/7/2 */
            }
            break;
        }
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_138);
            VOS_DBGASSERT( 0 );
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_PktProc_NACK
 ��������  : ����nack����
 �������  : DHCP_S  *pstDHCPPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��23��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_Pkt_ProcDHCPNACK ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*
    *1�����ڳ�ʼ�����û���֪ͨGTPC/PPPC���ɹ���ɾ��ʱ���ƿ�
    *2�������������û���֪ͨGTPCɾIP������
    */
    DHCPC_TEMPCTRLBLK    *pItemInfo = NULL;

    if(NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_139);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\nDHCPC_Pkt_ProcDHCPNACK NULL error!" );
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_ProcDHCPNACK()" );

    if ( ( DHCPC_STATE_REQUEST        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_LEASE        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReNewing        != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_PreReBinding    != pItemInfo->usDhcpStatus )
         && ( DHCPC_STATE_ReBinding        != pItemInfo->usDhcpStatus ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_140);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCPNACK state err!" );
        return VOS_ERR;
    }

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST  :
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nReceive NAK msg from server when renew IP!" );

            /* Modified start by heguangwei 65937 at 2008-03-22 LAP1 for AX4D01589 */
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_220);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode ,DHCPC_SND2_LAP2_ADDR_FAILED_MSG );
            /* Modified end by heguangwei 65937 at 2008-03-22 LAP1 for AX4D01589 */
            /*ɾ����ʱ���ƿ�ڵ㣬�ͷ��ڴ�*/
            DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);
            DHCPC_DelNode( DHCPC_INVALID_INDEX, pstDhcpCtrlBlkNode );
            DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
            break;

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_141);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nReceive NAK msg from server when renew IP!" );

            (VOID)DHCPC_StopTimer(pItemInfo->ucAddressType, pItemInfo->ulTEIDC, 0);
            ( VOID )DHCPC_SendMsgToLAP2( pstDhcpCtrlBlkNode,DHCPC_SND2_LAP2_ADDR_REL_MSG );
            DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex);

            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_142);
            VOS_DBGASSERT( 0 );
            break;
    }

    return VOS_OK;
}
ULONG DHCPC_SendMsgToLAP2 ( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode, UCHAR MsgType )
{
    ULONG ulRetValue = 0;
    LAP2_DHCPC_MSG_S stLapDhcpcMsg = {0};
    DHCPC_TEMPCTRLBLK *pItemInfo = NULL;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_SendMsgToLAP2()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_231);

    if (NULL == pstDhcpCtrlBlkNode)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_232);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_SendMsgToLAP2-pstDhcpCtrlBlkNode=null!");
        return VOS_ERR;
    }

    pItemInfo = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );

    /*��ȡDHCP���ƿ�*/
    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pItemInfo->ulDHCPCtlIdx, pItemInfo->ulTEIDC);
    if (NULL == pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_245);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
            "\r\n DHCPC_Pkt_SendMsgtoLAP2 DHCPCTRL Index is wrong= %u!", pItemInfo->ulDHCPCtlIdx);
        return VOS_ERR;
    }

    /* �����Ϣ���� */
    stLapDhcpcMsg.usVpnId = pItemInfo->usVpnId;
    stLapDhcpcMsg.aulPdpAddr[0] = pItemInfo->ulUserIpAddr;
    stLapDhcpcMsg.aulPdpAddr[1] = 0xFFFFFFFF;
    stLapDhcpcMsg.aulPdpAddr[2] = 0xFFFFFFFF;
    stLapDhcpcMsg.aulPdpAddr[3] = 0xFFFFFFFF;
    stLapDhcpcMsg.ucAddressType = pItemInfo->ucAddressType;
    stLapDhcpcMsg.usPoolIndex = pItemInfo->usPoolIndex;
    stLapDhcpcMsg.ucSCID = DHCPC_SELF_CMPIDX_INSG;
    stLapDhcpcMsg.aulAgentIP[0] = pItemInfo->ulAgetIP;
    /* ����V4�ķ���Ϣ�ӿڣ�ֱ�ӽ��ڶ���ULONG��ȫF */
    stLapDhcpcMsg.aulAgentIP[1] = VOS_NULL_LONG;
    stLapDhcpcMsg.ulIndex = pItemInfo->ulPdpIndex;
    stLapDhcpcMsg.usDhcpGroupIndex = pItemInfo->usDhcpGroupIndex;
    stLapDhcpcMsg.ucMsgType = MsgType;
    stLapDhcpcMsg.usApnIndex = pstDhcpcCtlBlk->usApnIndex;
    stLapDhcpcMsg.aulPrimaryDNS[0] = pItemInfo->ulPriDNSIP;
    stLapDhcpcMsg.aulSecondaryDNS[0] = pItemInfo->ulSecDNSIP;
    stLapDhcpcMsg.ucUserType = pItemInfo->ucUserType;
    stLapDhcpcMsg.ucGtpVer = pItemInfo->ucUser;
    stLapDhcpcMsg.ulTeidc = pItemInfo->ulTEIDC;
    stLapDhcpcMsg.ucStaticIpRouteType = 0;
    stLapDhcpcMsg.aulMSISDN[0] = pItemInfo->aulMSISDN[0];
    stLapDhcpcMsg.aulMSISDN[1] = pItemInfo->aulMSISDN[1];
    /* BEGIN: Added by jixiaoming at 2011-03-29 */
    stLapDhcpcMsg.ucLAPNo = pItemInfo->ucLAPNo;
    /* END: Added by jixiaoming at 2011-03-29 */

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
        "\r\n DHCPC_SendMsgToLAP2ByFCM lapNo = %u!", pItemInfo->ucLAPNo);

    ulRetValue = DHCPC_SendAddrMsgToLAP(&stLapDhcpcMsg,
                                           sizeof(LAP2_DHCPC_MSG_S),
                                           pItemInfo->ulUserIpAddr,
                                           pItemInfo->ucLAPNo);
    if (VOS_OK != ulRetValue)
    {
        return ulRetValue;
    }

    return ulRetValue;
}
ULONG DHCPC_SendMsgToLAP2_WithOriginalMsg(LAP2_DHCPC_MSG_S *pstLapDhcpcMsg, UCHAR ucMsgType)
{
    ULONG ulRet = 0;
    LAP2_DHCPC_MSG_S stLapDhcpcMsgOut = {0};
    LAP2_DHCPC_MSG_S *pstLapDhcpcMsgOut = &stLapDhcpcMsgOut;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_SendMsgToLAP2_WithOriginalMsg()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_246);

    if (NULL == pstLapDhcpcMsg)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_247);
        DHCPC_DebugPrint(PTM_LOG_DEBUG,  "\r\n DHCPC_SendMsgToLAP2_WithOriginalMsg-pstLapDhcpcMsg=null!");
        return VOS_ERR;
    }

    switch(ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_REL_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_249);
            break;
        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_251);
            break;
        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_252);
            break;
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_253);
            break;
        case DHCPC_SND2_LAP2_LEASE_REL:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_254);
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_255);
            break;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                    "\r\n DHCPC_SendMsgToLAP2_WithOriginalMsg aulPdpAddr=%x,ulAgentIP=%x,usPoolIndex=%d",pstLapDhcpcMsg->aulPdpAddr[0],
                    pstLapDhcpcMsg->aulAgentIP[0],pstLapDhcpcMsg->usPoolIndex);


    /* �����Ϣ���� */
    pstLapDhcpcMsgOut->usVpnId = pstLapDhcpcMsg->usVpnId;
    pstLapDhcpcMsgOut->aulPdpAddr[0] = pstLapDhcpcMsg->aulPdpAddr[0];
    pstLapDhcpcMsgOut->aulPdpAddr[1] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->aulPdpAddr[2] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->aulPdpAddr[3] = IPV4_NOT_USE_ADDULONG;
    pstLapDhcpcMsgOut->ucAddressType = pstLapDhcpcMsg->ucAddressType;
    pstLapDhcpcMsgOut->usPoolIndex = pstLapDhcpcMsg->usPoolIndex;
    pstLapDhcpcMsgOut->ucSCID = DHCPC_SELF_CMPIDX_INSG;
    pstLapDhcpcMsgOut->aulAgentIP[0] = pstLapDhcpcMsg->aulAgentIP[0];
    pstLapDhcpcMsgOut->aulAgentIP[1] = pstLapDhcpcMsg->aulAgentIP[1];
    pstLapDhcpcMsgOut->ulIndex = pstLapDhcpcMsg->ulIndex;
    pstLapDhcpcMsgOut->usDhcpGroupIndex = pstLapDhcpcMsg->usDhcpGroupIndex;
    /* �޸���Ϣ���� */
    pstLapDhcpcMsgOut->ucMsgType = ucMsgType;
    pstLapDhcpcMsgOut->usApnIndex = pstLapDhcpcMsg->usApnIndex;
    pstLapDhcpcMsgOut->aulPrimaryDNS[0] = pstLapDhcpcMsg->aulPrimaryDNS[0];
    pstLapDhcpcMsgOut->aulSecondaryDNS[0] = pstLapDhcpcMsg->aulSecondaryDNS[0];
    pstLapDhcpcMsgOut->ucUserType = pstLapDhcpcMsg->ucUserType;
    pstLapDhcpcMsgOut->ulTeidc= pstLapDhcpcMsg->ulTeidc;
    pstLapDhcpcMsgOut->ucStaticIpRouteType = pstLapDhcpcMsg->ucStaticIpRouteType;
    pstLapDhcpcMsgOut->aulMSISDN[0] = pstLapDhcpcMsg->aulMSISDN[0];
    pstLapDhcpcMsgOut->aulMSISDN[1] = pstLapDhcpcMsg->aulMSISDN[1];
    /* BEGIN: Added by jixiaoming at 2011-03-29 */
    pstLapDhcpcMsgOut->ucLAPNo = pstLapDhcpcMsg->ucLAPNo;
    /* END: Added by jixiaoming at 2011-03-29 */

    ulRet = DHCPC_SendAddrMsgToLAP((VOID *)pstLapDhcpcMsgOut,
                                      sizeof(LAP2_DHCPC_MSG_S),
                                      pstLapDhcpcMsg->aulPdpAddr[0],
                                      pstLapDhcpcMsg->ucLAPNo);
    return ulRet;
}


ULONG DHCPC_Pkt_Send( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    LONG        lRet  = -1;
    PMBUF_S      *pMBuf = NULL;
    DHCP_S      *pstDhcpPkt = NULL;
    LONG        lSecondReturnCode = -1;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    RM_SOCKET_PATH_S stPath = {0};
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    ULONG ulRet = 0;

    if (NULL == pItemInfo)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* modify by w00316385 start */
    /* ����MBUF */
#if 0
    pMBuf = PMBUF_CreateForControlPacket( 0, 1500, PMBUF_TYPE_DATA, MID_DHCPC );
#endif
    pMBuf = PMBUF_GetPMbuf(MID_DHCPC, 1500);
    /* modify by w00316385 end */

    if ( pMBuf == NULL )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_150);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_ProcDHCP MBUF memory alloc failed!" );
        return VOS_ERR;
    }

    pstDhcpPkt = PMBUF_MTOD( pMBuf, DHCP_S * );
    PGP_MemZero( pstDhcpPkt, sizeof( DHCP_S ) );

    switch ( ucPktType )
    {
        case DHCP_DISCOVER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_211);

            /*���discovery����*/
            DHCPC_Pkt_EncapDiscovry( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_REQUEST:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_212);
            /*���request����*/
            DHCPC_Pkt_EncapRequest( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_DECLINE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_213);
            /*���decline����*/
            DHCPC_Pkt_EncapDecline( pstDhcpPkt, pItemInfo );
            break;

        case DHCP_RELEASE:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_214);
            /*���release����*/
            DHCPC_Pkt_EncapRelease( pstDhcpPkt, pItemInfo );
            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_151);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send invalid DHCP packet type!" );
            ( VOID )PMBUF_Destroy( pMBuf );
            pMBuf = NULL;
            return VOS_ERR;
    }

    /*MBuf�б��ĳ�������*/
    pMBuf->ulTotalDataLength = DHCPC_PKT_LEN;/*��ȷ�����ȣ�û��IP UDPͷ�ĳ���*/
    pMBuf->stDataBlockDescriptor.ulDataLength = DHCPC_PKT_LEN;
    /*------------------------------------debug show packet----------------------*/
    DHCPC_Dbg_PacketPrintSend( pMBuf );

    lRet = DHCPC_OutPut( ucPktType, pItemInfo, pMBuf, &lSecondReturnCode );
    if ( VOS_OK != lRet )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send send packet 1st direction failed!" );
        ( VOID )PMBUF_Destroy( pMBuf );
        pMBuf = NULL;
        /*��ʱ��ɾ���ƿ�,�ɵ��ú���ɾ*/
        if ( VOS_ERR == lSecondReturnCode )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_152);
            /*���з����ϵķ��Ͷ�ʧ�ܣ�����ʧ�ܣ�ɾ����ʱ���ƿ죬������Ϊ���ͳɹ�*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_Send send packet 2nd direction failed!" );
            return VOS_ERR;
        }
    }
    /* BEGIN: Modified for PN:BI8D01083 by liuyuchao, 2009/6/30 */
    else
    {
        /* Start: Modify by zhangyang for PN:BI8D02498, 2010/4/24 */
        ULONG ulDirection = TRC_DIRECTION_RIGHT_OUT_PGW;

        if(( E_NET_ELEMENT_ROLE_GGSN == pItemInfo->ucRole )||( E_NET_ELEMENT_ROLE_PGW_AND_SGW == pItemInfo->ucRole ))
        {
            ulDirection = TRC_DIRECTION_RIGHT_OUT_UGW;
        }
        UGW_OmUsrMsgTrace((UCHAR *)pstDhcpPkt,
                     GUSER_MSGTYPE_DHCPV4,
                     (ULONG)ucPktType + ulDirection,
                     (USHORT)DHCPC_PKT_LEN,
                     (UCHAR *)(pItemInfo->aulIMSI),
                     (UCHAR *)(pItemInfo->aulIMEI),
                     (UCHAR *)(pItemInfo->aulMSISDN),
                     pItemInfo->ucRandomNo);
        /* End: Modify by zhangyang for PN:BI8D02498, 2010/4/24 */

        /* DHCP������ϢV�ӿڸ��� */ /* ��TrcGetTraceFlag()���÷��ڸ��ٺ���֮��,����Ч�� */
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            DHCPC_OmVIfMsgTrc((ULONG)(ucPktType),
                                ulDirection,
                                (UCHAR*)pstDhcpPkt,
                                DHCPC_PKT_LEN,
                                LAP_IPV4,
                                &(pItemInfo->ulSrvIp));
        }

        /* BEGIN: Added for PN:ȫ������  by LiHairong, 2010/4/10 */
        stPath.ulLocalAddr = pItemInfo->ulAgetIP;
        stPath.ulPeerAddr  = pItemInfo->ulSrvIp;
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stPath.usLocalPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stPath.usLocalPort = DHCPC_PKT_PORTNO;
        }
        stPath.usPeerPort = DHCPS_PKT_PORTNO;

        /*����PDP INDEX, ��ȡ������*/
        ulRet = (ULONG)SDB_GetContextByIndex(pItemInfo->ulPdpIndex, (UCHAR**)&pstContext );
        if ( ( ulRet == VOS_OK ) && ( NULL != pstContext ) )
        {
            stTrcPara.pucTrcMsg = (UCHAR *)pstDhcpPkt;
            stTrcPara.ucMsgType = ucPktType;
            stTrcPara.ucUgwRole = pstContext->ucUgwRole;
            stTrcPara.usMsgLen = DHCPC_PKT_LEN;
            stTrcPara.ulEmsTrcDir = M_EMS_TRC_SEND_MSG;
            stTrcPara.ulUsrTrcDir = TRC_DIRECTION_RIGHT_OUT_PGW;
            stTrcPara.usTraceId = pstContext->usTraceId;
            stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
            stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
            stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
            stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
            stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV4;
            stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
            stTrcPara.ucMsgSndFlg = 0;
            if((1 == stTrcPara.ucSgwTrcFlg)
                || (1 == stTrcPara.ucPgwTrcFlg))
            {
                UGW_OmEmsTrcMsgTrc(&stTrcPara,&stPath);
            }
        }
        /* END:   Added for PN:ȫ������  by LiHairong, 2010/4/10 */

        /* PGW����ͳ��*/
        if ((E_NET_ELEMENT_ROLE_PGW == pItemInfo->ucRole) || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pItemInfo->ucRole))
        {
            DHCPC_PGWPerfStat(ucPktType);
        }

    }
    /* END:   Modified for PN:BI8D01083 by liuyuchao, 2009/6/30 */

    return VOS_OK;
}


VOID DHCPC_Pkt_EncapDiscovry ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    /*����lease timeѡ��ķ���*/
    DHCP_S  *pDhcp = NULL;
    ULONG   *pulMagicCookie = NULL;
    UCHAR   *pucDhcpOption = NULL;
    UCHAR   szChaddrr[6] = {0};
    ULONG   ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_153);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapDiscovry pstDhcpPkt = NULL");
        return;
    }

    //PGP_MemZero(szChaddrr, sizeof(UCHAR)*6);
    //PGP_MemZero(szMSISDN, sizeof(UCHAR)*16);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapDiscovry()" );
    /*----------------- ���DHCP�̶��ֶ�����-----------------  */
    pDhcp    = pstDhcpPkt;

    /*��ȡ�����ַ*/
    DHCPC_ConstructPhyAddr(pItemInfo, szChaddrr);

    /*��ȡxid*/
    pItemInfo->ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapDiscovry: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );

    DHCP_FILLFIXEDFIELD(    DHCP_OP_REQUEST, pDhcp,
                            pItemInfo->ulXid, 0,
                            0, pItemInfo->ulUserIpAddr,
                            pItemInfo->ulAgetIP, 0, szChaddrr );

    pDhcp->ulSiaddr=0;      /*�˲�����REQUEST����������*/
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- ���DHCP�Ŀ�ѡ�ֶ� ------------------*/
    /*���MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_DISCOVER );

    if((0 ==(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        &&((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
        || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->pItemInfo->aulMSISDN(0) = %x,pItemInfo->aulMSISDN[1] = %x",
                                pItemInfo->aulMSISDN[0],pItemInfo->aulMSISDN[1] );
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }

    /*"server identifier" */
    if ( 0 != pItemInfo->usLease )
    {
        DHCP_FILLULONGOPTION( pucDhcpOption, DHCP_IPLEASETIME_CODE, pItemInfo->usLease );
    }

    /*
     *ֻΪ����������Ϣ�����볤��
     *UCHAR *pucHName;
     *pucHName="HuaWei MA5200 dhcp client inbed";
     *DHCP_FILLHOSTNAME(pucDhcpOption,pucHName,31);
     */
    /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) || (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
    {
        if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x80))))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x01;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
        }
        if ((0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x40))) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x03;
            *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
        if ((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x02;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
    }
    else
    {
        DHCP_FILLPARALISTOPTION( pucDhcpOption );   /*lfb ���ⵥD01785*/
    }
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */

    /*���ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );

    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*���ȴﵽ308   ����0*/

    return ;
}

/*****************************************************************************
 �� �� ��  : DHCPC_Pkt_EncapRequest
 ��������  : ��װrequest����
 �������  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��22��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_Pkt_EncapRequest ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S        *pDhcp = NULL;
    ULONG        *pulMagicCookie = NULL;
    UCHAR        *pucDhcpOption = NULL;
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_154);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapRequest pstDhcpPkt = NULL");
        return;
    }

    pDhcp = pstDhcpPkt;
    pDhcp->ulSiaddr=0;  /* (ULONG)VOS_HTONL(pItemInfo->ulDhcpSvrAddr); lfb �˲�����REQUEST����������*/
    pDhcp->szSname[0] = 0;   /*���ⵥ�� D01622*/
    pDhcp->szFile[0] = 0;

    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );
    /*----------------- ���DHCP�Ŀ�ѡ�ֶ� ------------------*/
    /*���MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_REQUEST );

    /*"client identifier" */
    /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    if((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */

    switch ( pItemInfo->usDhcpStatus )
    {
        case DHCPC_STATE_REQUEST :

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapRequest()" );

            /*----------------- ���DHCP�̶��ֶ�����-----------------  */
            DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                                 pItemInfo->ulXid, 0,
                                 0, 0/*pItemInfo->ulUserIpAddr*/,
                                 pItemInfo->ulAgetIP,0, szChaddrr );

            /*���REQUEST IP*/
            if ( pItemInfo->ulUserIpAddr!=NULL )
            {
                DHCP_FILLIPOPTION( pucDhcpOption, ( ULONG )DHCP_REQUESTEDIP_CODE, pItemInfo->ulUserIpAddr );
            }

            /*"server identifier" */
            /*??Э��˵MUST Я��"server identifier"��??*/
            if ( pItemInfo->ulSrvIp!=NULL )
            {
                DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);/*???���ⵥ��:D01030*/
            }

            /*MAY* "release time" REQUEST���ıش�ѡ��   (DHCPDISCOVER or DHCPREQUEST)*/
            if ( 0 != pItemInfo->usLease )
            {
                DHCP_FILLULONGOPTION( pucDhcpOption, ( ULONG )DHCP_IPLEASETIME_CODE, ( ULONG )( pItemInfo->usLease ) );
            }

            break;

        case DHCPC_STATE_LEASE :
        case DHCPC_STATE_ReNewing:
        case DHCPC_STATE_PreReBinding:
        case DHCPC_STATE_ReBinding:

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_Pkt_EncapRenew()" );

            /*���»�ȡxid*/
            pItemInfo->ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapRequest: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                                pItemInfo->ucSCID, g_ulDHCPCTransId );

            /*----------------- ���DHCP�̶��ֶ�����-----------------  */
            DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                                 pItemInfo->ulXid, 0, /*modified by z00113478leaseʱ��xid����Ҫ�������*/
                                 0, 0/*pItemInfo->ulUserIpAddr*/,
                                 pItemInfo->ulAgetIP,
                                 pItemInfo->ulUserIpAddr, szChaddrr );/* Modifyed by niutao 60002996 at 2006-08-25 V800R002C05B010 for KPN Project*/
            /*MAY  lease time */
            if ( 0 != pItemInfo->usLease )
            {
                DHCP_FILLULONGOPTION( pucDhcpOption, DHCP_IPLEASETIME_CODE, pItemInfo->usLease );
            }

            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_155);
            VOS_DBGASSERT( 1 == 0 );
            return;
    };
    /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) || (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
    {
        if((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x80))))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x01;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
        }
        if ((0 == (g_ucSoftParaDHCPKPN & ((UCHAR)0x40))) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x03;
            *pucDhcpOption++ = DHCP_SUBNETMASK_CODE;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
        if ((g_ucSoftParaDHCPKPN & ((UCHAR)0x40)) && (g_ucSoftParaDHCPKPN & ((UCHAR)0x80)))
        {
            *pucDhcpOption++ = DHCP_REQPARAM_CODE;
            *pucDhcpOption++ = 0x02;
            *pucDhcpOption++ = DHCP_DNSIP_CODE;
            *pucDhcpOption++ = DHCP_NBNS_CODE;
        }
    }
    else
    {
        DHCP_FILLPARALISTOPTION( pucDhcpOption ); /* ���ⵥD01785 // leaseʱ����Ҫ����ѡ��*/
    }
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    /*���ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*���ȴﵽ308   ����0*/

    return ;
}


/*****************************************************************************
 �� �� ��  : DHCPC_Pkt_EncapDecline
 ��������  : ��װdecline����
 �������  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��22��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_Pkt_EncapDecline( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S        *pDhcp = NULL;
    ULONG         *pulMagicCookie = NULL;
    ULONG         ulXid = 0;
    UCHAR         *pucDhcpOption = NULL;
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_156);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapDeclinepstDhcpPkt = NULL");
        return;
    }

    ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapDecline: pItemInfo->ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                pItemInfo->ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    /*----------------- ���DHCP�̶��ֶ�����-----------------  */
    pDhcp = pstDhcpPkt;
    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );
    /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                         ulXid, 0,
                         0, 0,
                         pItemInfo->ulAgetIP,
                         0, szChaddrr );
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- ���DHCP�Ŀ�ѡ�ֶ� ------------------*/
    /*���MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_DECLINE );


    /*"client identifier" */
    /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
    if ((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }
    /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */

    DHCPC_SetTmpCtrlBlkSrvIp(pItemInfo);

    DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);


    DHCP_FILLIPOPTION( pucDhcpOption, DHCP_REQUESTEDIP_CODE, pItemInfo->ulUserIpAddr );

    /*���ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*���ȴﵽ308   ����0*/

    return ;
}


/*****************************************************************************
 �� �� ��  : DHCPC_Pkt_EncapRelease
 ��������  : ��װrelease����
 �������  : IP_S *pstIpPkt
             DHCPC_INFO_S* pItemInfo
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��22��
    ��    ��   : yuqingping(25027)
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_Pkt_EncapRelease ( DHCP_S * pstDhcpPkt, DHCPC_TEMPCTRLBLK* pItemInfo )
{
    DHCP_S       *pDhcp = NULL;
    ULONG        *pulMagicCookie = NULL;
    ULONG        ulXid = 0;
    UCHAR        *pucDhcpOption = NULL;
    UCHAR        szChaddrr[6] = {0};
    ULONG        ulClientIdLen = 0;

    if((NULL == pstDhcpPkt)||(NULL == pItemInfo))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_157);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_EncapRelease pstDhcpPkt = NULL");
        return;
    }

    /*----------------- ���DHCP�̶��ֶ�����-----------------  */
    pDhcp = pstDhcpPkt;
    DHCPC_ConstructPhyAddr( pItemInfo, szChaddrr );

    ulXid = DHCPC_Pkt_GetTransId(pItemInfo);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_Pkt_EncapRelease: ulXid = %x,pItemInfo->ulDHCPCtlIdx = %x",
                                ulXid, pItemInfo->ulDHCPCtlIdx );
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n pItemInfo->ucSCID = %x,g_ulDHCPCTransId = %x",
                            pItemInfo->ucSCID, g_ulDHCPCTransId );

    DHCP_FILLFIXEDFIELD( DHCP_OP_REQUEST, pDhcp,
                         ulXid, 0,
                         0, 0,
                         pItemInfo->ulAgetIP,pItemInfo->ulUserIpAddr, szChaddrr );
    pDhcp->szSname[0] = 0;
    pDhcp->szFile[0] = 0;

    /*----------------- ���DHCP�Ŀ�ѡ�ֶ� ------------------*/
    /*���MAGICCOOKIE*/
    pulMagicCookie  = ( ULONG * )( ( VOID * )( pDhcp + 1 ) );
    DHCP_FILLMAGICCODE( pulMagicCookie );

    /*"DHCP message type" */
    pucDhcpOption    = ( UCHAR * )( pulMagicCookie + 1 );
    DHCP_FILLMESSAGETYPEOPTION( pucDhcpOption, DHCP_RELEASE );

    /*"client identifier" */
    if((!(g_ucSoftParaDHCPKPN & ((UCHAR)0x20)))
        && ((VOS_NULL_DWORD != pItemInfo->aulMSISDN[0])
            || (VOS_NULL_DWORD != pItemInfo->aulMSISDN[1])))
    {
        ulClientIdLen = DHCPC_FillClientIdOption(pucDhcpOption, pItemInfo->aulMSISDN);
        if (0 != ulClientIdLen)
        {
            pucDhcpOption += ulClientIdLen;
        }
    }

    DHCPC_SetTmpCtrlBlkSrvIp(pItemInfo);

    DHCP_FILLIPOPTION(pucDhcpOption,(ULONG)DHCP_SERVERIP_CODE,pItemInfo->ulSrvIp);

    /*���ENDOPTION*/
    DHCP_FILLENDOPTION( pucDhcpOption );
    DHCP_LENGTHTO300( pulMagicCookie,pucDhcpOption ); /*���ȴﵽ308   ����0*/

    return;
}
ULONG  DHCPC_Pkt_GetTransId( DHCPC_TEMPCTRLBLK* pItemInfo )
{
    ULONG ulXid = 0;
    ULONG ulSCID = 0;

    /*��ȡ��SC��id*/
    ulSCID = DHCPC_SELF_CMPIDX_INSG;

    if (NULL == pItemInfo)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_158);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_Pkt_GetTransId pItemInfo = NULL");
        return VOS_ERR;
    }

	/*39����ε�5��bitΪ1��XIDֱ��ʹ��TEIDC���á�*/
	/*39����ε�5��bitλΪ0��v1�û�: DE��: token(13bit)+sc id(3bit)+Sequence��16bit��
                                     F��:token(14bit)+reserve(2bit)+Sequence��16bit��*/
    if(g_ucSoftParaDHCPKPN & ((UCHAR)0x10))
    {
        ulXid =  pItemInfo->ulDHCPCtlIdx;
    }
    else
    {
        if ( CRM_BOARD_TYPE_SPUF != g_ulDhcpcSpuType )
        {
            ulXid = (( ULONG )(pItemInfo->ulDHCPCtlIdx) & 0xFFF80000 )
                           | ((ulSCID << 16 ) & 0x70000)
                           | ((g_ulDHCPCTransId++) & 0xffff);
        }
        else
        {
            ulXid = (( ULONG )(pItemInfo->ulDHCPCtlIdx) & 0xFFFC0000 )
                           | ((g_ulDHCPCTransId++) & 0xffff);
        }

    }

    return ulXid;
}

/*****************************************************************************
 �� �� ��  : DHCPR_RecordAllOption
 ��������  : ��¼DHCP OPTION��ָ��
 �������  : DHCPOPTION_S stDhcpOption
             DHCP_S *pstDhcp
             ULONG ulOptionLen
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2002��11��23��
    ��    ��   : ��鲨
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG  DHCPR_RecordAllOption( DHCP_OPTION_S *pstDhcpOpt, DHCP_S *pstDhcp, ULONG ulOptionLen )
{
    ULONG  ulMagicCookie = NULL;
    UCHAR  *pucOpt = NULL;
    LONG   lDhcpOptionLen = NULL;
    UCHAR  *pucOptions = NULL;
    ULONG  i = 0;
    UCHAR  a_ucCount[DHCP_OPTION_COUNT] = {0};

    /*�ж���εĺϷ���*/
    if ( ( pstDhcp == NULL )||( pstDhcpOpt == NULL ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_159);
        return VOS_ERR;
    }

    /*�õ�OPTION��ͷָ��pucOption*/
    pucOptions     = ( UCHAR * )( pstDhcp+1 );
    lDhcpOptionLen = ( LONG )ulOptionLen;

    pucOpt = pucOptions;


    /*�ж�MAGICCODE�Ƿ�Ϊ����Ҫ��*/
    ulMagicCookie = *( ULONG * )pucOpt;
    if ( ulMagicCookie != ( ULONG )VOS_HTONL( DCHP_MAGICCOOKIE ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_160);
        return VOS_ERR;
    }

    /*Ϊÿ�����Գ�ʼ������*/
    for ( i = 0; i < DHCP_OPTION_COUNT; a_ucCount[i] = 0, i++ ) ;

    /*pucOptionָ���4�����ȼ�4*/
    pucOptions     += 4;
    lDhcpOptionLen -= 4;

    while ( *pucOptions!= DHCP_ENDOFOPTIONS/* *pucOption != 0xFF*/ )
    {
        /*���������¼option���ͺ�option����*/
        UCHAR ucOptionCode = VOS_NULL;
        UCHAR ucOptionLen = VOS_NULL;

        /*�ж�ulOptionLen����2��2Ϊ��С��option����*/

        /*ȡ��option����*/
        ucOptionCode    = *pucOptions++;

        if ( ucOptionCode == 0 )
        {
            ucOptionLen     = 0;
            lDhcpOptionLen --;
        }
        else
        {
            ucOptionLen     = *pucOptions++;
            lDhcpOptionLen -= 2;
        }

        /*ȡ��option����*/

        /*�жϺ���ı䳤�ֶεĳ����Ƿ��㹻,���Ա�֤����
          ������ǰDHCP���ĵı䳤�ֶεĳ�����֮��ȥ*/
        if ( lDhcpOptionLen <= ( LONG )ucOptionLen )
        {
            /*��û��"DHCP message type"ѡ��ʱ������BOOTP����    */
            if ( pstDhcpOpt->pucDHCPMsgType == NULL )
            {
                /*lint -e801*/
                goto optionnumchk;
                /*lint +e801*/
            }
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_161);

            return VOS_ERR;
        }

        switch ( ucOptionCode/*option����*/ )
        {
                /*1.��"Subnet mask"ѡ�code = 0x01*/
            case DHCP_SUBNETMASK_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_162);
                    return VOS_ERR;
                }

                a_ucCount[0]++;
                pstDhcpOpt->pulSubnetMask = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNetMaskLen = ucOptionLen;
                break;

                /*2.��"Router"ѡ�code = 0x03*/
            case DHCP_ROUTERIP_CODE :
                /*�жϳ����Ƿ���4�ı���*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_163);
                    return VOS_ERR;
                }

                a_ucCount[1]++;
                pstDhcpOpt->pulRouterIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucRouterIpLen = ucOptionLen;
                break;

                /*3.��"DNS ������"ѡ�code = 0x06*/
            case DHCP_DNSIP_CODE :
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPR_RecordAllOption(),have DNS option" );
                /*�жϳ����Ƿ���4�ı���*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_164);
                    return VOS_ERR;
                }

                a_ucCount[2]++;
                pstDhcpOpt->pulDNSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucDNSIpLen = ucOptionLen;
                break;

                /*4.��"Host name"ѡ�code = 0x0b*/
            case DHCP_HOSTNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_165);
                    return VOS_ERR;
                }

                a_ucCount[3]++;
                pstDhcpOpt->pucHostName   = pucOptions;
                pstDhcpOpt->ucHostNameLen = ucOptionLen;
                break;

                /*5.��"Domain name"ѡ�code = 0x0f*/
            case DHCP_DOMAINNAME_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_166);
                    return VOS_ERR;
                }

                a_ucCount[4]++;
                pstDhcpOpt->pucDomainName   = pucOptions;
                pstDhcpOpt->ucDomainNameLen = ucOptionLen;
                break;

                /*6.��"Netbios name server"ѡ�code = 0x2c*/
            case DHCP_NBNS_CODE :
                /*�жϳ����Ƿ���4�ı���*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_167);
                    return VOS_ERR;
                }

                a_ucCount[5]++;
                pstDhcpOpt->pulNBNSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNBNSIpLen = ucOptionLen;
                break;

                /*7.��"Netbios data distribute server"ѡ�code = 0x2d*/
            case DHCP_NBDS_CODE :
                /*�жϳ����Ƿ���4�ı���*/
                if ( ( ucOptionLen & 0x03 )!= NULL )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_168);
                    return VOS_ERR;
                }

                a_ucCount[6]++;
                pstDhcpOpt->pulNBDSIp   = ( ULONG * )pucOptions;
                pstDhcpOpt->ucNBDSIpLen = ucOptionLen;
                break;

                /*8.��"Netbios node type"ѡ�code = 0x2e*/
            case DHCP_NBNT_CODE :
                if ( ucOptionLen != 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_169);
                    return VOS_ERR;
                }

                a_ucCount[7]++;
                pstDhcpOpt->pucNBNodeType   = pucOptions;
                break;

                /*9.��"Netbios scope"ѡ�code = 0x2f*/
            case DHCP_NBSCOPE_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_170);
                    return VOS_ERR;
                }

                a_ucCount[8]++;
                pstDhcpOpt->pucNBScope   = pucOptions;
                pstDhcpOpt->ucNBScopeLen = ucOptionLen;
                break;

                /*10.��"Requested Ip"ѡ�code = 0x32*/
            case DHCP_REQUESTEDIP_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_171);
                    return VOS_ERR;
                }

                a_ucCount[9]++;
                pstDhcpOpt->pulReqIp = ( ULONG * )pucOptions;
                break;

                /*11.��"Ip address lease time"ѡ�code=0x33*/
            case DHCP_IPLEASETIME_CODE:
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_172);
                    return VOS_ERR;
                }

                a_ucCount[10]++;
                pstDhcpOpt->pulLeaseTime = ( ULONG * )pucOptions;/*����Ϊ��λ��IPʹ������*/
                break;

                /*12.��"DHCP message type"ѡ�code=0x35*/
                /*��û�����ѡ��ʱ,���ڵ��ô˺����ĺ����н��г�����*/
            case DHCP_MESSAGETYPE_CODE:
                /*"DHCP Message Type"ѡ��ĳ����Ƿ�Ϊ1*/
                if ( ucOptionLen != 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_173);
                    return VOS_ERR;
                }

                a_ucCount[11]++;
                pstDhcpOpt->pucDHCPMsgType = pucOptions;
                break;

                /*13.��"Server Identifier"ѡ�code=0x36*/
            case DHCP_SERVERIP_CODE:
                if ( ucOptionLen != 4 )/*��ϸ���ǣ��費��Ҫ��һ������(ZQ0805)*/
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_174);
                    return VOS_ERR;
                }

                a_ucCount[12]++;
                pstDhcpOpt->pulDHCPServerIp = ( ULONG * )pucOptions;
                break;

                /*14.��"Requested parameter list"ѡ�code = 0x37*/
            case DHCP_REQPARAM_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_175);
                    return VOS_ERR;
                }

                a_ucCount[13]++;
                pstDhcpOpt->pucReqParamList   = pucOptions;
                pstDhcpOpt->ucReqParamListLen = ucOptionLen;
                break;

                /*15.��"Renew time"ѡ�code = 0x3a*/
            case DHCP_RENEWTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_176);
                    return VOS_ERR;
                }

                a_ucCount[14]++;
                pstDhcpOpt->pulRenewTime = ( ULONG * )pucOptions;/*����Ϊ��λ*/
                break;

                /*16.��"Rebind time"ѡ�code = 0x3b*/
            case DHCP_REBINDTIME_CODE :
                if ( ucOptionLen != 4 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_177);
                    return VOS_ERR;
                }

                a_ucCount[15]++;
                pstDhcpOpt->pulRebindTime = ( ULONG * )pucOptions;/*����Ϊ��λ*/
                break;

                /*17.��"Client Id"ѡ�code = 0x3d*/
            case DHCP_CLIENTID_CODE :
                if ( ucOptionLen < 2 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_178);
                    return VOS_ERR;
                }

                a_ucCount[16]++;
                pstDhcpOpt->pucClientId   = pucOptions;
                pstDhcpOpt->ucClientIdLen = ucOptionLen;
                break;

                /*18.��"Vendor information"ѡ�code = 0x29*/
            case DHCP_VENDORINFO_CODE :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_179);
                    return VOS_ERR;
                }

                a_ucCount[17]++;
                pstDhcpOpt->pucVendorOption   = pucOptions;
                pstDhcpOpt->ucVendorOptinLen  = ucOptionLen;
                break;

            case DHCP_OPT82_CODE :
                if ( ucOptionLen < 2 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_180);
                    return VOS_ERR;
                }

                a_ucCount[18]++;
                pstDhcpOpt->pucOpt82   = pucOptions;
                pstDhcpOpt->ucOpt82Len  = ucOptionLen;
                break;

            case DHCP_OPTION60 :
                if ( ucOptionLen < 1 )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_181);
                    return VOS_ERR;
                }

                a_ucCount[19]++;
                pstDhcpOpt->pucOption60= pucOptions;
                pstDhcpOpt->ucOpt60Len  = ucOptionLen;
                break;

                /*��������ѡ����κβ���*/
            default:
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_182);
                break;
        }

        /*����ucOptionLen���ȵ��ֽڣ��õ���һ��code�ֽ�*/
        pucOptions     += ucOptionLen;
        if(lDhcpOptionLen < ucOptionLen )
        {
            break;
        }
        lDhcpOptionLen -= ( long )ucOptionLen;

    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPR_RecordAllOption(),a_ucCount[2]=%d",a_ucCount[2] );

    if ( *pucOptions == DHCP_ENDOFOPTIONS/*��β����ΪEND OPTION*/ )
    {
        /*��ֵ*/
        pstDhcpOpt->pucEndOfOption = pucOptions;
    }
    else if ( pstDhcpOpt->pucDHCPMsgType == VOS_NULL_PTR/*��Ϣ����Ϊ��ΪBOOTP����*/ )
    {
        /*��ӡ*/

    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_183);
        /*��ӡ����ֱ�ӷ���*/
        return VOS_ERR;
    }

    /*goto���*/
optionnumchk:
    /*�������Լ������ж������Գ��ֹ����Σ�����������Σ�����*/
    for ( i = 0; ( i < DHCP_OPTION_COUNT ) && ( a_ucCount[i] <= 1 ); i++ ) ;

    /*
    if ( i < DHCP_OPTION_COUNT )
    {
        return VOS_ERR;
    }
    */

    /*���سɹ�*/
    return VOS_OK;

}

