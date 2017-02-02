/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpc_msg.c
  �� �� ��   : ����
  ��    ��   : yuqingping(25027)
  ��������   : 2002��11��21��
  ����޸�   :
  ��������   : dhcpcģ�����Ϣ����
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
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_MSG_C
/*lint +e767*/


/* add by w00316385 start */
extern VOS_UINT32 g_ulPtmHashGene;
#define M_PTM_HASH_GENE (g_ulPtmHashGene)
/* add by w00316385 end */

extern ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer);

/*****************************************************************************
 �� �� ��  : DHCPC_QueryContextByteidc
 ��������  :
 �������  : ULONG ulTeidc
 �������  : ��
 �� �� ֵ  : VOS_OK    �ҵ���������
             VOS_ERR   δ�ҵ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��07��08��
    ��    ��   : jixiaoming
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_QueryContextByteidc(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    ULONG ulContextsNum = 0;
    SDB_GSPU_CONTEXT_S *pstRelContexts[M_MNT_MAX_PDP_NUM] = {NULL};

    ulRet = (ULONG)SDB_GTPC_GetRelatedContextsByTeidc(ulTeidc, &ulContextsNum, (UCHAR **)pstRelContexts);
    if (SDB_SUCCESS == ulRet)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


ULONG DHCPC_GetCtlBlkHashKey( ULONG ulDHCPCtlIdx )
{
    ULONG ulHashKey = 0;

    /* ���ݿ��ƿ������ĺ�16λ����HASHKEY */
    ulHashKey = (ulDHCPCtlIdx & 0x0000ffff) % DHCPC_CTRLBLK_HASH_TABLE_SIZE;

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_GetCtlBlkHashKey:ulHashKey = %d",ulHashKey );
    return ulHashKey;
}
DHCPC_CTRLBLK * DHCPC_CalcCtlBlkHashValue( ULONG ulDHCPCtlIdx, ULONG ulTEIDC)
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK * pstDhcpcCtlBlk = NULL;

    /* ���ݿ��ƿ���������HASHKEY */
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulDHCPCtlIdx );
    pstDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];

    /* ��������HASHKEY��ȵĿ��ƿ� */
    while ( NULL != pstDhcpcCtlBlk )
    {
        /* V1�û����TEIDC������ҵ���Ӧ���ƿ� */
        if ( pstDhcpcCtlBlk->ulTEIDC == ulTEIDC)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_237);
            DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_CalcCtlBlkHashValue:ulTEIDC = %d",pstDhcpcCtlBlk->ulTEIDC );
            return pstDhcpcCtlBlk;
        }

        pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
        if (NULL == pstDhcpcCtlBlk)
        {
            break;
        }

    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_CalcCtlBlkHashValue: there is no DHCP CtlBlk! " );
    return NULL;
}
DHCPC_CTRLBLK * DHCPC_LookupCtlBlkNodeIntoHashTable( DHCP_S  *pstDHCPPkt)
{
    ULONG ulHashKey = 0;
    ULONG ulIndex = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    /* ��μ�� */
    if ( NULL == pstDHCPPkt)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_LookupCtlBlkNodeIntoHashTable:pstDHCPPkt is null!" );
        return NULL;
    }

    /* ����39����εĵ�5λ��ȡ���ƿ����� */
    if(g_ucSoftParaDHCPKPN & ((UCHAR)0x10))
    {
        ulIndex = VOS_HTONL(pstDHCPPkt->ulXid);
    }
    else
    {
        VOS_MemCpy( ( CHAR* )&ulIndex,( CHAR* )&( pstDHCPPkt->szChaddr[2] ),4 );
        ulIndex = VOS_HTONL(ulIndex);
    }

    /* ���ݿ��ƿ������ĺ�16λ����HASHKEY */
    ulHashKey = (ulIndex & 0x0000ffff) % DHCPC_CTRLBLK_HASH_TABLE_SIZE;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n ulXid = 0X%x, ulHashKey = %d",
                     pstDHCPPkt->ulXid, ulHashKey);

    pstDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];

    /* ����HASHKEY��ȵĿ��ƿ飬�����û����͵õ���Ӧ���ƿ� */
    while ( NULL != pstDhcpcCtlBlk )
    {
        if ( pstDhcpcCtlBlk->ulDHCPCtxIdx == ulIndex)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_238);
            return pstDhcpcCtlBlk;
        }

        pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
    }

    /*û���ҵ���Ӧ���ƿ�*/
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_241);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n there is no pstDhcpcCtlBlk!" );
    return NULL;
}
ULONG DHCPC_InsertCtlBlkNodeIntoHashTable( LAP2_DHCPC_MSG_S *pstReqMsg, ULONG ulIndex)
{
    ULONG ulHashKey = 0;
    ULONG ulRetCode = 0;
    DHCPC_CTRLBLK* pstDhcpcCtlBlk = NULL; /*DHCP ���ƿ�ָ��*/

    if ( NULL == pstReqMsg )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_235);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget: pstReqMsg is null!");
        return VOS_ERR;
    }

    /*���ݿ��ƿ���������HASHKEY*/
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulIndex );

    /*����HashKey�ж�DHCP���ƿ��Ƿ��Ѿ�����*/
    pstDhcpcCtlBlk = DHCPC_CalcCtlBlkHashValue(ulIndex, pstReqMsg->ulTeidc);
    if (NULL != pstDhcpcCtlBlk)
    {
        /*DHCP���ƿ��Ѿ�����*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_236);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget: pstDhcpcCtlBlk is already exist!");
        return DHCP_CTRLBLK_EXIST;
    }

    /*��ʼ���½��*/
    ulRetCode = (ULONG)DHCPC_GetDhcpCtrlBlk(&pstDhcpcCtlBlk);
    if ( VOS_OK != ulRetCode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_070);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget null DhcpCtrlBlk!");
        return VOS_ERR;
    }

    pstDhcpcCtlBlk->usApnIndex = pstReqMsg->usApnIndex;
    pstDhcpcCtlBlk->ulPDPIndex = pstReqMsg->ulIndex;
    pstDhcpcCtlBlk->ucUser= pstReqMsg->ucGtpVer;
    pstDhcpcCtlBlk->ulTEIDC= pstReqMsg->ulTeidc;
    pstDhcpcCtlBlk->ulDHCPCtxIdx= ulIndex;
    pstDhcpcCtlBlk->ucLAPNo = pstReqMsg->ucLAPNo;

    /*���½����뵽��һ��λ��*/
    pstDhcpcCtlBlk->pstNextNode = g_pstDhcpcCtrlBlkRec[ulHashKey];
    g_pstDhcpcCtrlBlkRec[ulHashKey] = pstDhcpcCtlBlk;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_InsertCtlBlkNodeIntoHashTableget success!");
    return VOS_OK;
}

/* BEGIN: Modified by jixiaoming for dhcpv6c at 2012-7-10 */

VOID DHCPC_ProcIpv4Apply(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    /*��������*/
    ULONG                   ulRet = 0;       /*�������÷���ֵ*/
    ULONG                   ulIpLease = 0;
    ULONG                   ulRetTimeInSec = 0;
    DHCPC_CTRLBLK_NODE*     pstDhcpCtrlNode = NULL;
    DHCPC_TEMPCTRLBLK*      pstTempItem = NULL;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulDhcpGroupIndex = 0;
    LAP_DHCP_CFG_S stDhcpServer = {0};

    /* �õ�DHCP��ʱ���ƿ�ڵ� */
    pstDhcpCtrlNode = (DHCPC_CTRLBLK_NODE *)DHCPC_GetDhcpTmpNode();
    if ( NULL == pstDhcpCtrlNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_068);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply get null DhcpTmpNode!");
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        return;
    }
    pstTempItem = &(pstDhcpCtrlNode->stDhcpcTmpCtlBlk);

    DHCPC_INIT_ITEM(pstTempItem );

    DHCPC_MSG2ITEM(pstReqMsg, pstTempItem);

    /* �����û�������䵱ǰDHCP���ƿ����� */
    pstTempItem->ulDHCPCtlIdx = pstReqMsg->ulTeidc;
    pstTempItem->ulAgetIP = pstReqMsg->aulAgentIP[0];
    pstTempItem->usPoolIndex = pstReqMsg->usPoolIndex;
    pstTempItem->aulMSISDN[0] = pstReqMsg->aulMSISDN[0];
    pstTempItem->aulMSISDN[1] = pstReqMsg->aulMSISDN[1];
    pstTempItem->ucUserType = pstReqMsg->ucUserType;
    pstTempItem->usVpnId = pstReqMsg->usVpnId;
    pstTempItem->ulPdpIndex = pstReqMsg->ulIndex;
    pstTempItem->ucUser = pstReqMsg->ucGtpVer;
    pstTempItem->ulTEIDC = pstReqMsg->ulTeidc;
    pstTempItem->ucLAPNo = pstReqMsg->ucLAPNo;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply:ucUser = 0X%x, ulTEIDC = 0X%x, ulIndex = 0X%x, ucLAPNo = %d",
                          pstReqMsg->ucGtpVer, pstReqMsg->ulTeidc, pstReqMsg->ulIndex, pstReqMsg->ucLAPNo);

#if 0
    /*����PDP INDEX, ��ȡ������*/
    ulRet = (ULONG)SDB_GetContextByIndex(pstReqMsg->ulIndex, (UCHAR**)&pstContext );
    if ( ( ulRet != VOS_OK ) || ( NULL == pstContext ) )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply : SDB_GetContextByIndex return ERR.!" );

        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        return;
    }

    VOS_MemCpy(pstTempItem->aulIMSI,&(pstContext->stImsi),sizeof(ULONG)*2);
    VOS_MemCpy(pstTempItem->aulMSISDN,pstContext->szMsisdn,sizeof(ULONG)*2);
    VOS_MemCpy(pstTempItem->aulIMEI,&(pstContext->stIMEI),sizeof(ULONG)*2); /* Added by jixiaoming for  IMEI���� at 2012-8-17 */
    pstTempItem->ucRole = pstContext->ucUgwRole;
    pstTempItem->ucRandomNo = pstContext->ucRandomNo;
#endif

    /* �����û����ʹ���DHCP���ƿ��HASH��*/
    ulRet = DHCPC_InsertCtlBlkNodeIntoHashTable(pstReqMsg, pstTempItem->ulDHCPCtlIdx);
    if ( ulRet != VOS_OK )
    {
        if(DHCP_CTRLBLK_EXIST == ulRet)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_069);
            /* ֪ͨLAP����---ADDR_REL��Ϣ��*/
            (VOID)DHCPC_SendMsgToLAP2(pstDhcpCtrlNode, DHCPC_SND2_LAP2_ADDR_REL_MSG);

            /* ֪ͨDHCPServer�ͷ�IP*/
            (VOID)DHCPC_Pkt_Send(DHCP_RELEASE, pstTempItem);
        }

        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);

        /*ɾ����ʱ���ƿ�ڵ㣬�ͷ��ڴ�*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_242);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply : DHCPC_InsertCtlBlkNodeIntoHashTable return ERR.!" );
        return;
    }

    /* ����DHCP���ƿ�ṹ����¼����Ӧ��ȫ�������У���ǰ�汾��SDB�Ѿ����ٱ������
    ��ṹ���������ڶ�̬������ƿ�ṹ�ռ䣬�������ƿ�ṹָ�����ȫ�������б���
    ����������PDP�������������൱��ԭ����SDB*/

    ulDhcpGroupIndex = pstTempItem->usDhcpGroupIndex;
    ulRet = DHCPM_GetDhcpSrvCfgByIndex(ulDhcpGroupIndex, &stDhcpServer);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_080);
        VOS_DBGASSERT(0);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "DHCPM_GetDhcpSrvCfgByIndex fail, ulDhcpGroupIndex=%u", ulDhcpGroupIndex);
        return;
    }

    ulIpLease = stDhcpServer.ucLeaseTime* 3600 ;/* ��Сʱת������ */

    if(0 != ulIpLease)
    {
        pstTempItem->usLease = ulIpLease;
    }

    /*----------------------------------------------------
    *              ���ķ���
    ----------------------------------------------------*/

    /*�л�״̬��������ʱ��*/
    DHCPC_ITEM_SETSATE(pstTempItem, DHCPC_STATE_DISCOVER);

    /*����discovery����*/
    ulRet = DHCPC_Pkt_Send(DHCP_DISCOVER , pstTempItem);
    if(VOS_OK != ulRet)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_081);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Apply send DHCP_DISCOVER packet failed!");

        /*�������ط���ʱ������ɾ���ڵ㣬�ͷ��ڴ�*/

        /* �ͷſ��ƿ� */
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
        return;
    }

    /*��¼����Discovery��ʱ��*/

    /*ȡ�����*/
    (VOID)PGP_TmNowInSec( &ulRetTimeInSec);
    pstTempItem->ulTimeStamp = ulRetTimeInSec;

    /*���ط���־���뵽�ط���ʱ������,�Ա����ʵ�ʱ���ط��ñ���*/
    DHCPC_InSertNodeAfterSecs(DHCPC_4_SECONDS, pstDhcpCtrlNode);

    /*��ʱ���ƿ�ָ�뱣�浽DHCP���ƿ��ulTmpVar�ֶβ���ʧ�ܲ�������*/
    if (VOS_OK != DHCPC_SaveTmpDhcpCtrlBlkPtr(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex, (VOID *)pstDhcpCtrlNode) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_082);
        (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply save TmpCtrlBlk pointer failed!");
        /* �ͷſ��ƿ� */
        DHCPC_FreeDhcpCtrlBlk(pstTempItem->ulDHCPCtlIdx, pstTempItem->ulTEIDC, pstTempItem->ucUser, pstTempItem->ulPdpIndex );
        DHCPC_DelNode(DHCPC_INVALID_INDEX, pstDhcpCtrlNode);
        DHCPC_FreeDhcpTmpNode(pstDhcpCtrlNode);
    }

}
ULONG DHCPC_InitDhcpContextByLapMsg(DHCPC_CTRLBLK *pstDhcpcContext, LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;

    DHCPC_FUNC_ENTRY();

    pstDhcpcContext->aulMSISDN[0] = pstReqMsg->aulMSISDN[0];
    pstDhcpcContext->aulMSISDN[1] = pstReqMsg->aulMSISDN[1];
    VOS_MemCpy(pstDhcpcContext->aulAgentIpAddr, pstReqMsg->aulAgentIP, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    pstDhcpcContext->usVPNIndex = pstReqMsg->usVpnId;
    pstDhcpcContext->usServerGrpIndex = pstReqMsg->usDhcpGroupIndex;
    pstDhcpcContext->ucUserType = pstReqMsg->ucUserType;
    pstDhcpcContext->usPoolIndex = pstReqMsg->usPoolIndex;
    pstDhcpcContext->usApnIndex = pstReqMsg->usApnIndex;
    pstDhcpcContext->ucLAPNo = pstReqMsg->ucLAPNo;
    pstDhcpcContext->ucIpType = pstReqMsg->ucAddressType;
    pstDhcpcContext->ucUser = pstReqMsg->ucGtpVer;
    //pstDhcpcContext->ulTEIDC = pstReqMsg->ulTeidc;
    pstDhcpcContext->ulPDPIndex = pstReqMsg->ulIndex;
    pstDhcpcContext->ucAgingFlag = 0;
    pstDhcpcContext->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
    DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulMainDnsAddr);
    DHCPV6C_SET_V6ADDR_NULL(pstDhcpcContext->aulSecdDnsAddr);
    DHCPC_CLR_ALL_RESOURCE(pstDhcpcContext->ucResource);
    pstDhcpcContext->ucRabId   = pstReqMsg->ucRabId;
    pstDhcpcContext->enModemId = pstReqMsg->enModemId;

    ulReturn = DHCPM_GetRetransmitTimeOutByIndex(pstReqMsg->usDhcpGroupIndex, &(pstDhcpcContext->ucResendTimeout));
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call DHCPM_GetRetransmitTimeOutByIndex failed! return=%u", ulReturn);
        return VOS_ERR;
    }

#if 0
    ulReturn = (ULONG)SDB_GetContextByIndex(pstReqMsg->ulIndex, (UCHAR**)&pstContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_FIND_SDB_FAIL);
        DHCPC_DebugPrint(PTM_LOG_INFO, "call SDB_GetContextByIndex failed! return=%u", ulReturn);
        return VOS_ERR;
    }
    pstDhcpcContext->ucRandomNo = pstContext->ucRandomNo;
    pstDhcpcContext->ucRole = pstContext->ucUgwRole;
    VOS_MemCpy(pstDhcpcContext->aulIMSI, &(pstContext->stImsi),sizeof(ULONG) * 2);
    VOS_MemCpy(pstDhcpcContext->aulIMEI, &(pstContext->stIMEI),sizeof(ULONG) * 2);
#endif

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "MSISDN : 0x%x %x", pstDhcpcContext->aulMSISDN[0], pstDhcpcContext->aulMSISDN[1]);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "IMSI   : 0x%x %x", pstDhcpcContext->aulIMSI[0], pstDhcpcContext->aulIMSI[1]);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "IMEI   : 0x%x %x", pstDhcpcContext->aulIMEI[0], pstDhcpcContext->aulIMEI[1]);

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


ULONG DHCPC_ProcIpv6Apply(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPC_FUNC_ENTRY();

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_REQ_MSG);

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        ulReturn = DHCPC_MallocDhcpcContext(LAP_IPV6, pstReqMsg->ulTeidc, &pstDhcpcContext);
        if (VOS_OK != ulReturn)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CREAT_CONTEXT_FAIL);
            return VOS_ERR;
        }
        pstDhcpcContext->usDhcpStatus = DHCPV6C_STATE_INITIAL;
        ulReturn = DHCPC_InitDhcpContextByLapMsg(pstDhcpcContext, pstReqMsg);
        if (VOS_OK != ulReturn)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_INIT_CONTEXT_FAIL);

            ulReturn = DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcContext->ulTEIDC);
            if (ulReturn != VOS_OK)
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_ERR_2);
            }

            return VOS_ERR;
        }

    }
    else
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CONTEXT_EXIST_FAIL);

        /* �ͷŸõ�ַ */
        stPreResult.pstDhcpcContext = pstDhcpcContext;
        stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;
        stPreResult.pMsg = NULL;

        DHCPV6C_RunFsm(&stPreResult);
        return VOS_ERR;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.enEvent = DHCPV6C_EV_IP_REQUEST;
    stPreResult.pMsg = NULL;

    /* ����״̬�� */
    DHCPV6C_RunFsm(&stPreResult);

    DHCPC_FUNC_EXIT(VOS_OK);
    return VOS_OK;
}


VOID DHCPC_MsgProc_Apply(LAP2_DHCPC_MSG_S* pstReqMsg )
{
    ULONG   ulReturn = VOS_ERR;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Apply()");

    if (NULL == pstReqMsg)
    {
        VOS_Assert(0);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Apply get null pstReqMsg!");
        return;
    }

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        DHCPC_ProcIpv4Apply(pstReqMsg);
    }
    else
    {
        ulReturn = DHCPC_ProcIpv6Apply(pstReqMsg);
        if (VOS_OK != ulReturn)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_067);
            (VOID)DHCPC_SendMsgToLAP2_WithOriginalMsg(pstReqMsg, DHCPC_SND2_LAP2_ADDR_FAILED_MSG);
        }
    }

    return ;
}



VOID DHCPC_MsgProc_Lease( LAP2_DHCPC_MSG_S *pstReqMsg, ULONG ulDHCPCtlIdx )
{
    /*��������*/
    ULONG                ulRet = 0;       /*�������÷���ֵ*/
    ULONG                ulIndex = 0;
    ULONG                ulRetTimeInSec = 0;
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;
    DHCPC_TEMPCTRLBLK    *pstHashItem = NULL;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Lease()" );
    if( NULL == pstReqMsg)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_083);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease() pstReqMsg =null!" );
        return;
    }
    ulIndex        =  pstReqMsg->ulIndex;

    /*��ȡDHCP���ƿ�*/
    pstDhcpCtrlBlk = DHCPC_CalcCtlBlkHashValue(ulDHCPCtlIdx, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_084);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Release there is no DHCPCTRLBLK REC!" );
        return;
    }

    if ( DHCPC_STATE_INITIAL == pstDhcpCtrlBlk->usDhcpStatus )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_085);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease get null SdbDhcpCtrlBlk!" );
        return;
    }

    /*����������Ϣ����Ҳ�����Ӧ�������ģ����ͷſ��ƿ飬��server����release ��Ϣ�ͷŵ�ַ*/
    if (VOS_OK != DHCPC_QueryContextByteidc(pstReqMsg->ulTeidc))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease: get null PDPContext!!IMSI=0x%x, 0x%x, PDPIndex = %u, IP=0x%x, agent-ip=0x%x",
                 pstDhcpCtrlBlk->aulIMSI[0], pstDhcpCtrlBlk->aulIMSI[1], ulIndex, pstDhcpCtrlBlk->aulUserIpAddr[0], pstDhcpCtrlBlk->aulAgentIpAddr[0]);

        /* �ͷ���Դ */
        (VOID)DHCPC_ReleaseDhcpCtrlBlock(pstDhcpCtrlBlk);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_800);
        return;
    }

    pstHashItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstHashItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_086);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_MsgProc_Lease alloc null memory!" );
        return;
    }
    /*lint -save -e530*/
    DHCPC_INIT_ITEM( pstHashItem );
    pstHashItem->ulPdpIndex     = ulIndex;
    pstHashItem->ulSrvIp = pstDhcpCtrlBlk->aulSrvIp[0];

    pstHashItem->ulDHCPCtlIdx = pstDhcpCtrlBlk->ulDHCPCtxIdx;
    pstHashItem->ulAgetIP = pstDhcpCtrlBlk->aulAgentIpAddr[0];
    pstHashItem->ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
    pstHashItem->aulMSISDN[0] = pstDhcpCtrlBlk->aulMSISDN[0];
    pstHashItem->aulMSISDN[1] = pstDhcpCtrlBlk->aulMSISDN[1];
    pstHashItem->usDhcpGroupIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstHashItem->ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;


    /* BEGIN: Added for PN: LAP thread by jiahuidong, 2009/7/2 */
    pstHashItem->aulIMSI[0] = pstDhcpCtrlBlk->aulIMSI[0];
    pstHashItem->aulIMSI[1] = pstDhcpCtrlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
    pstHashItem->aulIMEI[0] = pstDhcpCtrlBlk->aulIMEI[0];
    pstHashItem->aulIMEI[1] = pstDhcpCtrlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */
    pstHashItem->usVpnId= pstDhcpCtrlBlk->usVPNIndex;
    pstHashItem->usPoolIndex = pstDhcpCtrlBlk->usPoolIndex;
    pstHashItem->ucUserType = pstDhcpCtrlBlk->ucUserType;
    pstHashItem->usDhcpStatus = pstDhcpCtrlBlk->usDhcpStatus;
    pstHashItem->ulTimeStamp = pstDhcpCtrlBlk->ulTimeStamp;
    /* END:   Added for PN: LAP thread by jiahuidong, 2009/7/2 */
    pstHashItem->usLease = pstDhcpCtrlBlk->ulLease;/*MAY*/
    pstHashItem->ucRole = pstDhcpCtrlBlk->ucRole;
    pstHashItem->ucUser= pstDhcpCtrlBlk->ucUser;
    pstHashItem->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    /* BEGIN: Added by jixiaoming at 2011-03-29 */
    pstHashItem->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;
    /* END: Added by jixiaoming at 2011-03-29 */
    pstHashItem->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;

    /*�ı�״̬*/
    DHCPC_ITEM_SETSATE( pstHashItem , DHCPC_STATE_LEASE );

    /*����request����*/
    ulRet = DHCPC_Pkt_Send( DHCP_REQUEST, pstHashItem );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_087);
        /*ɾ���ƿ�*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease send DHCP_REQUEST packet failed!" );
        DHCP_Free( DHCPC_HANDLE, pstHashItem );
        return;
    }
    /*��¼����REQ��ʱ��*/
    /*����:ʱ��㱣�治�������������û����Ӧ
      *��һ�η�����Լ�����ʱ�佫����
      */
    //ulRetTimeInSec = BSP_getTimeByTicksInMisc();
    ( VOID )PGP_TmNowInSec( &ulRetTimeInSec );
    pstDhcpCtrlBlk->ulTmpVar = ulRetTimeInSec;
    pstDhcpCtrlBlk->aulSrvIp[0] = pstHashItem->ulSrvIp;

    /* ����������Ϣ��ʱ��ʱ�� */
    (VOID)DHCPC_StartTimer(pstDhcpCtrlBlk->ucIpType, pstDhcpCtrlBlk->ulTEIDC, 0,
                                DHCPC_4_SECONDS, DHCPC_TimerCallBack);

    DHCP_Free( DHCPC_HANDLE, pstHashItem );

    return ;
}
VOID DHCPC_ProcIpv4Release(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_TEMPCTRLBLK*    pstTempItem = NULL;
    DHCPC_CTRLBLK*           pstDhcpcCtlBlk = NULL;


    /*��ȡDHCP���ƿ�*/
    pstDhcpcCtlBlk = DHCPC_CalcCtlBlkHashValue( pstReqMsg->ulTeidc, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpcCtlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_089);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ProcIpv4Release there is no DHCPCTRLBLK REC!" );
        return;
    }

    /*��ʼ��stTempItem */
    pstTempItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstTempItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_090);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ProcIpv4Release alloc null memory!" );
        VOS_Assert( 0 );
        return;
    }

    PGP_MemZero( pstTempItem, sizeof( DHCPC_TEMPCTRLBLK ) );

    DHCPC_INIT_ITEM( pstTempItem );
    /*��pReqMsg��������䵽stTempItem ��*/
    DHCPC_RELEASEMSG2ITEM( pstReqMsg, pstTempItem );

    pstTempItem->ulSrvIp = pstDhcpcCtlBlk->aulSrvIp[0];
    pstTempItem->ulDHCPCtlIdx = pstDhcpcCtlBlk->ulDHCPCtxIdx;
    pstTempItem->ulPdpIndex= pstDhcpcCtlBlk->ulPDPIndex;
    pstTempItem->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
    pstTempItem->aulMSISDN[0] = pstDhcpcCtlBlk->aulMSISDN[0];
    pstTempItem->aulMSISDN[1] = pstDhcpcCtlBlk->aulMSISDN[1];
    pstTempItem->aulIMSI[0]= pstDhcpcCtlBlk->aulIMSI[0];
    pstTempItem->aulIMSI[1]= pstDhcpcCtlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
    pstTempItem->aulIMEI[0]= pstDhcpcCtlBlk->aulIMEI[0];
    pstTempItem->aulIMEI[1]= pstDhcpcCtlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */
    pstTempItem->ucUser= pstDhcpcCtlBlk->ucUser;
    pstTempItem->ulTEIDC = pstDhcpcCtlBlk->ulTEIDC;
    pstTempItem->ucRole = pstDhcpcCtlBlk->ucRole;
    /* BEGIN: Added by jixiaoming at 2011-03-29 */
    pstTempItem->ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;
    /* END: Added by jixiaoming at 2011-03-29 */
    pstTempItem->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo;

    DHCPC_DebugPrint(PTM_LOG_DEBUG,
                "\r\n DHCPC_ProcIpv4Release:pstTempItem->ucUser = %d, pstTempItem->ulTEIDC = 0X%x",
                 pstTempItem->ucUser, pstTempItem->ulTEIDC);

    /*������Ϣ*/
    ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pstTempItem );
    DHCP_Free( DHCPC_HANDLE, pstTempItem );
    /* ����Ӧ���ͷ�dhcp���ƿ� */

    DHCPC_FreeDhcpCtrlBlk( pstReqMsg->ulTeidc, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);

    return;
}
VOID DHCPC_ProcIpv6Release(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_RELEASE_MSG);

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_LAPREL_QRY_CONTEXT_FAIL);
        return;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = NULL;
    stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

    /* ���lap����Դλ */
    DHCPC_CLR_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE);

    /* ����ԭ��ֵΪȱʡ */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    /* ����״̬�� */
    DHCPV6C_RunFsm(&stPreResult);

    return;
}
VOID DHCPC_MsgProc_Release( LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_MsgProc_Release()" );

    if( NULL == pstReqMsg)
    {
        VOS_Assert(0);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_088);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_MsgProc_Lease() pstReqMsg =null!" );
        return;
    }

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        DHCPC_ProcIpv4Release(pstReqMsg);
    }
    else
    {
        DHCPC_ProcIpv6Release(pstReqMsg);
    }

    return;
}


ULONG DHCPC_MsgProcIpv4Conflict(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    DHCPC_TEMPCTRLBLK*    pstTempItem = NULL;
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;

    DHCPC_FUNC_ENTRY();

    /*��ȡDHCP���ƿ�*/
    pstDhcpCtrlBlk = DHCPC_CalcCtlBlkHashValue( pstReqMsg->ulTeidc, pstReqMsg->ulTeidc);
    if ( NULL == pstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_096);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n there is no DHCPCTRLBLK REC!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    /*��ʼ��stTempItem */
    pstTempItem = ( DHCPC_TEMPCTRLBLK * )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_TEMPCTRLBLK ) );
    if ( NULL == pstTempItem )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_097);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n alloc null memory!" );
        VOS_Assert( 0 );
        return VOS_ERR;
    }

    PGP_MemZero( pstTempItem, sizeof( DHCPC_TEMPCTRLBLK ) );

    DHCPC_INIT_ITEM( pstTempItem );
    /*��pReqMsg��������䵽stTempItem ��*/
    DHCPC_RELEASEMSG2ITEM( pstReqMsg, pstTempItem );
    pstTempItem->ulSrvIp = pstDhcpCtrlBlk->aulSrvIp[0];
    pstTempItem->ulDHCPCtlIdx = pstDhcpCtrlBlk->ulDHCPCtxIdx;
    pstTempItem->ulPdpIndex = pstDhcpCtrlBlk->ulPDPIndex;
    pstTempItem->ulAgetIP = pstDhcpCtrlBlk->aulAgentIpAddr[0];
    pstTempItem->ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
    pstTempItem->usDhcpGroupIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstTempItem->aulMSISDN[0]= pstDhcpCtrlBlk->aulMSISDN[0];
    pstTempItem->aulMSISDN[1]= pstDhcpCtrlBlk->aulMSISDN[1];

    pstTempItem->aulIMSI[0]= pstDhcpCtrlBlk->aulIMSI[0];
    pstTempItem->aulIMSI[1]= pstDhcpCtrlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
    pstTempItem->aulIMEI[0]= pstDhcpCtrlBlk->aulIMEI[0];
    pstTempItem->aulIMEI[1]= pstDhcpCtrlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */

    pstTempItem->ucRole = pstDhcpCtrlBlk->ucRole;
    pstTempItem->ucUser= pstDhcpCtrlBlk->ucUser;
    pstTempItem->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    /* BEGIN: Added by jixiaoming at 2011-03-29 */
    pstTempItem->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;
    /* END: Added by jixiaoming at 2011-03-29 */

    pstTempItem->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;

    /*������Ϣ*/
    ( VOID )DHCPC_Pkt_Send( DHCP_DECLINE, pstTempItem );
    DHCP_Free( DHCPC_HANDLE, pstTempItem );
    /* ����Ӧ���ͷ�dhcp���ƿ� */

    DHCPC_FreeDhcpCtrlBlk( pstReqMsg->ulTeidc, pstDhcpCtrlBlk->ulTEIDC, pstDhcpCtrlBlk->ucUser, pstDhcpCtrlBlk->ulPDPIndex);

    return VOS_OK;
}
ULONG DHCPC_MsgProcIpv6Conflict(LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_CONFLICT_MSG);

    DHCPC_FUNC_ENTRY();

    ulReturn = DHCPC_QueryDhcpcContext(pstReqMsg->ucAddressType, pstReqMsg->ulTeidc, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_LAP_CONFLICT_FAIL);
        return VOS_ERR;
    }

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = NULL;
    stPreResult.enEvent = DHCPV6C_EV_IP_DECLINE;

    /* ���lap����Դλ */
    DHCPC_CLR_RESOURCE(pstDhcpcContext->ucResource, DHCPC_LAP_RESOURCE);

    /* ����ԭ��ֵΪȱʡ */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    /* ����״̬�� */
    DHCPV6C_RunFsm(&stPreResult);

    return VOS_OK;
}
ULONG DHCPC_MsgProc_Conflict( LAP2_DHCPC_MSG_S* pstReqMsg)
{
    ULONG ulReturn = VOS_ERR;

    DHCPC_FUNC_ENTRY();

    if (M_AM_USM_ADDRTYPE_IPV4 == pstReqMsg->ucAddressType)
    {
        ulReturn = DHCPC_MsgProcIpv4Conflict(pstReqMsg);
    }
    else
    {
        ulReturn = DHCPC_MsgProcIpv6Conflict(pstReqMsg);
    }

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}
/* END: Modified by jixiaoming for dhcpv6c at 2012-7-10 */

#define __CHECK__
ULONG DHCPC_JudgePdpContextCheck(SDB_GSPU_CONTEXT_S *pstContext)
{
    if (NULL == pstContext)
    {
        /*�쳣����������������ģ���¼��־��*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_304);
        return VOS_ERR;
    }

    if (0 == pstContext->ulGspuBdIndex)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_305);
        return VOS_ERR;
    }

    /* l2tp�û��������Ĳ���ΪSDB�˲���� */
    if (0 != pstContext->ucL2TPFlag)
    {
        return VOS_ERR;
    }


    if ( E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole )
    {
        if ((USM_PCRFC_DELETE == pstContext->ucMachineState) || (USM_CM_DELETE == pstContext->ucMachineState) || (USM_WAIT_SGSN_DELETE == pstContext->ucMachineState))
        {
            /*����������������ȥ��*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_346);
            return VOS_ERR;
        }
    }
    else
    {
        if (E_AM_USM_L1_STATE_DELETE == pstContext->ucMachineState)
        {
            /*����������������ȥ��*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_347);
            return VOS_ERR;
        }
    }


    if (E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole)
    {
        if (pstContext->ucMachineState <= USM_IP_APPLY)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_306);
            return VOS_ERR;
        }
    }
    else if ((E_NET_ELEMENT_ROLE_PGW == pstContext->ucUgwRole)
              || (E_NET_ELEMENT_ROLE_PGW_AND_SGW == pstContext->ucUgwRole))
    {
        if (E_AM_USM_L1_STATE_CREATE > pstContext->ucMachineState)
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_307);
            return VOS_ERR;
        }

        if ((E_AM_USM_L1_STATE_CREATE == pstContext->ucMachineState)
                &&( E_AM_USM_L2_STATE_LAP >= pstContext->ucMachineL2State))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_308);
            return VOS_ERR;
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_309);
        return VOS_ERR;
    }

    if ((GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv4AllocType)
        && (GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv6AllocType))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_315);
        return VOS_ERR;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_310);
    return VOS_OK;
}


ULONG DHCPC_NotifyLAPRelContext(UCHAR ucIPType, SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    LAP2_DHCPC_MSG_S stSendMessage = {0};

    if (NULL == pstContext)
    {
        return VOS_OK;
    }

    /*��װ��ַ��Ϣ*/
    stSendMessage.ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    stSendMessage.usApnIndex  =  pstContext->usApnIndex;
    stSendMessage.usVpnId =  pstContext->usVpnId;
    stSendMessage.ulIndex  =  pstContext->ulGspuBdIndex;
    stSendMessage.ucStaticIpRouteType = pstContext->ucStaticIpRouteType;
    stSendMessage.ucMsgType  = DHCPC_SND2_LAP2_REL_CONTEXT;
    stSendMessage.ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    if ( LAP_IPV4 == ucIPType )
    {
        stSendMessage.ucAddressType = M_AM_USM_ADDRTYPE_IPV4;
        stSendMessage.aulPdpAddr[0] = pstContext->ulIPv4Addr;
        stSendMessage.ucSectionNum = pstContext->ucLapSectionV4Num;
        stSendMessage.ucLAPNo = pstContext->ucipv4LAPSequence;
        stSendMessage.usPoolIndex = pstContext->usPoolIndex;

        /*������Ϣ��lap����lap֪ͨusmȥ���û���*/
        ulRet = DHCPC_SendAddrMsgToLAP((VOID *)(&stSendMessage),
                                          sizeof(LAP2_DHCPC_MSG_S),
                                          pstContext->ulIPv4Addr,
                                          pstContext->ucipv4LAPSequence);
    }
    else
    {
        stSendMessage.ucAddressType = M_AM_USM_ADDRTYPE_IPV6;
        stSendMessage.aulPdpAddr[0] = pstContext->stIPv6Addr.s6_addr32[0];
        stSendMessage.aulPdpAddr[1] = pstContext->stIPv6Addr.s6_addr32[1];
        stSendMessage.aulPdpAddr[2] = pstContext->stIPv6Addr.s6_addr32[2];
        stSendMessage.aulPdpAddr[3] = pstContext->stIPv6Addr.s6_addr32[3];
        stSendMessage.ucSectionNum = pstContext->ucLapSectionV6Num;
        stSendMessage.ucLAPNo = pstContext->ucipv6LAPSequence;
        stSendMessage.usPoolIndex = pstContext->usPoolIPV6Index;

        /*������Ϣ��lap����lap֪ͨusmȥ���û���*/
        ulRet = DHCPC_SendAddrMsgToLAP((VOID *)(&stSendMessage),
                                          sizeof(LAP2_DHCPC_MSG_S),
                                          pstContext->stIPv6Addr.s6_addr32[1],
                                          pstContext->ucipv6LAPSequence);
    }

    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    return VOS_OK;
}
ULONG DHCPC_ReleaseDhcpCtrlBlock(DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    DHCPC_CTRLBLK_NODE *pstDhcpcTempCtlBlkNode = NULL;
    DHCPC_TEMPCTRLBLK *pstDhcpcTempCtlBlk = NULL;

    if (NULL == pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_301);
        return VOS_ERR;
    }

    /*��ȡ��ʱ���ƿ�ڵ�*/
    pstDhcpcTempCtlBlkNode = ( DHCPC_CTRLBLK_NODE* )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK_NODE ) );
    if ( NULL == pstDhcpcTempCtlBlkNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_302);
        VOS_DBGASSERT( 0 );
        return VOS_ERR;
    }

    PGP_MemZero( pstDhcpcTempCtlBlkNode,sizeof( DHCPC_CTRLBLK_NODE ) );
    pstDhcpcTempCtlBlk = &( pstDhcpcTempCtlBlkNode->stDhcpcTmpCtlBlk );

    pstDhcpcTempCtlBlk->ulUserIpAddr = pstDhcpcCtlBlk->aulUserIpAddr[0];
    pstDhcpcTempCtlBlk->ucUserType = pstDhcpcCtlBlk->ucUserType;
    pstDhcpcTempCtlBlk->usPoolIndex = pstDhcpcCtlBlk->usPoolIndex;
    pstDhcpcTempCtlBlk->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
    pstDhcpcTempCtlBlk->ulPdpIndex = pstDhcpcCtlBlk->ulPDPIndex;
    pstDhcpcTempCtlBlk->ucAddressType = LAP_IPV4;
    pstDhcpcTempCtlBlk->usDhcpGroupIndex = pstDhcpcCtlBlk->usServerGrpIndex;
    pstDhcpcTempCtlBlk->ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;
    pstDhcpcTempCtlBlk->ulSrvIp = pstDhcpcCtlBlk->aulSrvIp[0];
    pstDhcpcTempCtlBlk->ulDHCPCtlIdx = pstDhcpcCtlBlk->ulDHCPCtxIdx;
    pstDhcpcTempCtlBlk->aulMSISDN[0] = pstDhcpcCtlBlk->aulMSISDN[0];
    pstDhcpcTempCtlBlk->aulMSISDN[1] = pstDhcpcCtlBlk->aulMSISDN[1];
    pstDhcpcTempCtlBlk->usVpnId = pstDhcpcCtlBlk->usVPNIndex;
    pstDhcpcTempCtlBlk->aulIMSI[0] = pstDhcpcCtlBlk->aulIMSI[0];
    pstDhcpcTempCtlBlk->aulIMSI[1] = pstDhcpcCtlBlk->aulIMSI[1];
    /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
    pstDhcpcTempCtlBlk->aulIMEI[0] = pstDhcpcCtlBlk->aulIMEI[0];
    pstDhcpcTempCtlBlk->aulIMEI[1] = pstDhcpcCtlBlk->aulIMEI[1];
    /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */
    pstDhcpcTempCtlBlk->ucRole = pstDhcpcCtlBlk->ucRole;

    /* ��Ҫ���û����ͺ�TEIDC��ֵ */
    pstDhcpcTempCtlBlk->ucUser = pstDhcpcCtlBlk->ucUser;
    pstDhcpcTempCtlBlk->ulTEIDC = pstDhcpcCtlBlk->ulTEIDC;
    pstDhcpcTempCtlBlk->ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;

    pstDhcpcTempCtlBlk->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo;

    /* ��LAP2������Ϣ��֪ͨɾ���û�  */
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOutMsg to lap,ulUserIpAddr = %u,usPoolIndex = %d,ulAgetIP = %u!",
    pstDhcpcTempCtlBlk->ulUserIpAddr, pstDhcpcTempCtlBlk->usPoolIndex, pstDhcpcTempCtlBlk->ulAgetIP );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_201);

    (VOID)DHCPC_SendMsgToLAP2( pstDhcpcTempCtlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG );

    /* ����release��Ϣ */
    (VOID)DHCPC_Pkt_Send(DHCP_RELEASE, pstDhcpcTempCtlBlk);

    /* ����Ӧ���ͷ�dhcp���ƿ�,��ʱ���ƿ� */
    DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
    DHCP_Free( DHCPC_HANDLE, pstDhcpcTempCtlBlkNode );
    pstDhcpcTempCtlBlkNode = NULL;
    pstDhcpcTempCtlBlk = NULL;

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_303);

    return VOS_OK;
}
ULONG DHCPC_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    ULONG ulReturn = VOS_OK;
    UCHAR *pucRtMsg = VOS_NULL;

    if ((VOS_NULL == pucMsg) || (0 == ulMsgLen))
    {
        return VOS_ERR;
    }

    pucRtMsg = (UCHAR*)DHCP_RTDistributeAllocMsg(DHCPC_HANDLE, ulMsgLen);
    if (VOS_NULL == pucRtMsg)
    {
        return VOS_ERR;
    }

    VOS_MemCpy(pucRtMsg, pucMsg, ulMsgLen);

    RTD_SET_MSGCODE(pucRtMsg, (USHORT)ulMsgCode);
    ulReturn = DHCP_RTDistributeSend(DHCPC_SELF_CSI,
                           ullDstCsi,
                           pucRtMsg,
                           ulMsgLen,
                           ulMsgType);

    if (VOS_OK != ulReturn)
    {
        DHCP_RTDistributeFreeMsg(pucRtMsg);
        return VOS_ERR;
    }

    return VOS_OK;
}



ULONG DHCPC_SendURTMsg(VOS_UINT64 ullSrcCsi, VOS_UINT64 ullDstCsi, ULONG ulMsgType,
                      ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    PMBUF_S *pstMbuf   = VOS_NULL;
    ULONG ulRet = 0;
    ULONG ulMode = 0;

    /* �����շ�CSI�Ƿ����� */
    if ( !PSM_Inf_GetStatByCSI(ullDstCsi))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "Dst CPU is not registered!");
        return VOS_ERR;
    }

    /* modify by w00316385 start */
#if 0
    pstMbuf = PMBUF_CreateByCopyBuffer(0, ulMsgLen, pucMsg, PMBUF_TYPE_DATA, MID_PAPI);
#endif
    pstMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulMsgLen);
    /* modify by w00316385 end */

    if (VOS_NULL == pstMbuf)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PMBUF_CreateByCopyBuffer fail");
        return VOS_ERR;
    }

    URTD_SET_MSGCODE(pstMbuf, (UCHAR)ulMsgCode);

    if ( CRM_BOARD_TYPE_SPUD == g_ulDhcpcSpuType )
    {
        ulMode = URTD_PRIORITY_LOW;
    }
    else
    {
        ulMode = URTD_PRIORITY_HIGH;
    }

    /* ����URT�ӿڷ��� */
    ulRet = PGP_URTDistributeSend(ullSrcCsi,
                                 ullDstCsi,
                                 pstMbuf,
                                 ulMode,
                                 ulMsgType,
                                 M_PTM_HASH_GENE);
    if (VOS_OK != ulRet)
    {
        /* ����ʧ�ܣ���Ҫ�ͷ�PMBUF */
        (VOID)PMBUF_Destroy(pstMbuf);

        DHCPC_DebugPrint(PTM_LOG_ERR, "PGP_URTDistributeSend fail, ulRet = %x", ulRet);
        return ulRet;
    }

    return VOS_OK;
}
VOID DHCPC_SendSelfPdpCheckMsg(ULONG ulPdpIndex)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_CHECK_PDP;
    stInnerMsg.ulPdpIndex = ulPdpIndex;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_CHECK_PDP,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}


ULONG DHCPC_SendSelfCtlBlockCheckMsg(ULONG ulHashValue)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK;
    stInnerMsg.ulCtlBlockHashValue = ulHashValue;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return VOS_OK;
}


VOID DHCPC_CheckPdpByCrtBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpcCtlBlk, SDB_GSPU_CONTEXT_S *pstContext)
{
    UCHAR ucLogicSlot = 0;

    if (NULL != pstDhcpcCtlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_311);

        if ((LAP_IPV4 == ucIpType) && ((DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus)
             ||( DHCPC_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus)))
        {
            /*���ƿ��е��ϻ������Ϊ0*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_312);
            pstDhcpcCtlBlk->ucAgingFlag = 0;
        }

        if ((LAP_IPV6 == ucIpType)
            && ((DHCPV6C_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus)
            || (DHCPV6C_STATE_RENEW == pstDhcpcCtlBlk->usDhcpStatus)))
        {
            /*���ƿ��е��ϻ������Ϊ0*/
            /* ���� */
            pstDhcpcCtlBlk->ucAgingFlag = 0;
        }

        return;
    }

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return;
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_316);
    /*�����Ĵ��ڣ���dhcp���ƿ鲻���ڣ�˵���������Ѿ���������ʱ֪ͨLAPȥ��*/

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    (VOID)DHCPC_NotifyLAPRelContext(ucIpType, pstContext);

    return;
}


ULONG DHCPC_GetTedicByUgwRole(UCHAR ucUgwRole, ULONG ulSgwLeftLocTeidc, ULONG ulS5_Gn_LocTeidc)
{
    if (E_NET_ELEMENT_ROLE_SGW == ucUgwRole)
    {
        return ulSgwLeftLocTeidc;
    }

    return ulS5_Gn_LocTeidc;
}


VOID DHCPC_CheckPdpProcForIpv4(SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulTeidc = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ( GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv4AllocType )
    {
        /* ���� */
        return;
    }

    /*�����������м�¼��teidc����dhcp���ƿ�*/
    ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTeidc, ulTeidc);

    DHCPC_CheckPdpByCrtBlk(LAP_IPV4, pstDhcpcCtlBlk, pstContext);

    return;
}


VOID DHCPC_CheckPdpProcForIpv6(SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulTeidc = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    if ( NULL == pstContext )
    {
        VOS_DBGASSERT(0);
        return;
    }

    if ( GTP_DHCP_ALLOC_ADDR != pstContext->ucIPv6AllocType )
    {
        /* ���� */
        return;
    }

    /*�����������м�¼��teidc����dhcp���ƿ�*/
    ulTeidc = DHCPC_GetTedicByUgwRole(pstContext->ucUgwRole, pstContext->ulSgwLeftLocTeidc, pstContext->ulS5_Gn_LocTeidc);

    (VOID)DHCPC_QueryDhcpcContext(LAP_IPV6, ulTeidc, &pstDhcpcCtlBlk);

    DHCPC_CheckPdpByCrtBlk(LAP_IPV6, pstDhcpcCtlBlk, pstContext);

    return;
}


VOID DHCPC_CheckPdpContext(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulRet = VOS_OK;
    ULONG ulScanPdpNum = 0;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulPdpIndex = 0;

    if ( NULL == pstInnerMsg )
    {
        return;
    }

    ulPdpIndex = pstInnerMsg->ulPdpIndex;

    for (; ulPdpIndex <= SDB_MAX_CONTEXT_NUM; ulPdpIndex++)
    {
        ulScanPdpNum++;
        if (0 == (ulScanPdpNum % 10))
        {
            DHCPC_SendSelfPdpCheckMsg(ulPdpIndex);
            return;
        }

        /*����PDP INDEX, ��ȡ������*/
        ulRet = (ULONG)SDB_GetContextByIndex(ulPdpIndex, (UCHAR**)&pstContext);
        if ((ulRet != VOS_OK) || (NULL == pstContext))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_314);
            continue;
        }

        /*û�����뵽��ַ�������Ĳ���Ϊ�ϻ�����*/
        if (VOS_OK != DHCPC_JudgePdpContextCheck(pstContext))
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_313);
            continue;
        }

        DHCPC_CheckPdpProcForIpv4(pstContext);

        DHCPC_CheckPdpProcForIpv6(pstContext);

    }

    (VOID)DHCPC_SendSelfCtlBlockCheckMsg(0);
    return;
}


VOID DHCPC_CheckCtrBlkforIpv6(ULONG ulSelftSlotState, ULONG ulHashValue)
{
    ULONG ulRet = VOS_OK;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstDhcpcNextCtlBlk = NULL;

    pstDhcpcCtlBlk = g_pstDhcpcIpv6CtrlBlkRec[ulHashValue];

    while ( NULL != pstDhcpcCtlBlk )
    {
        pstDhcpcNextCtlBlk = pstDhcpcCtlBlk->pstNextNode;

        (pstDhcpcCtlBlk->ucAgingFlag)++;

        if ( pstDhcpcCtlBlk->ucAgingFlag <= DHCPC_AGING_TIMES )
        {
            pstDhcpcCtlBlk = pstDhcpcNextCtlBlk;
            continue;
        }

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CHECK_BLKDEL);
        ulRet = DHCPC_IsTimNodeExist(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
        if (VOS_OK == ulRet)
        {
            (VOID)DHCPC_StopTimer(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC, DHCPV6C_EV_TIMER_LEASE_EXPIRE);
            (VOID)DHCPC_StopTimer(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC, DHCPV6C_EV_TIMER_RENEW);
        }

        (VOID)DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);

        pstDhcpcCtlBlk = pstDhcpcNextCtlBlk;
    }
}


VOID DHCPC_CheckCtrBlkforIpv4(ULONG ulSelftSlotState, ULONG ulHashValue)
{
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstDhcpNewcCtlBlk = NULL;

    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)g_pstDhcpcCtrlBlkRec[ulHashValue];
    for (;;)
    {
        if (NULL == pstDhcpcCtlBlk)
        {
            break;
        }

        pstDhcpNewcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
        (pstDhcpcCtlBlk->ucAgingFlag)++;

        if (DHCPC_AGING_TIMES >= pstDhcpcCtlBlk->ucAgingFlag)
        {
            pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
            continue;
        }

        /*dhcp���ƿ�û����Ӧ�������ģ���ʱӦ���ͷ�dhcp���ƿ��Ӧ����Դ*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_300);

        if ( E_CRM_ACTIVE == ulSelftSlotState )
        {
            (VOID)DHCPC_ReleaseDhcpCtrlBlock(pstDhcpcCtlBlk);
        }
        else
        {
            DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx,
                pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
        }

        /*��ȡ��һ��dhcp���ƿ�*/
        pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
    }
}


VOID DHCPC_CheckCtlBlock(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulHashValue = 0;
    ULONG ulScanNum = 0;
    ULONG ulSelftSlotState = 0;
    UCHAR ucLogicSlot = 0;

    if ( NULL == pstInnerMsg )
    {
        return;
    }

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulSelftSlotState = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);
    if ((E_CRM_ACTIVE != ulSelftSlotState) && (E_CRM_STANDBY != ulSelftSlotState))
    {
        return;
    }


    pstInnerMsg = (DHCPC_INNER_MSG_S *)pstInnerMsg;
    ulHashValue = pstInnerMsg->ulCtlBlockHashValue;

    for(; ulHashValue < DHCPC_CTRLBLK_HASH_TABLE_SIZE; ulHashValue++)
    {
        ulScanNum++;
        if (0 == (ulScanNum % 3))
        {
            (VOID)DHCPC_SendSelfCtlBlockCheckMsg(ulHashValue);
            return;
        }

        DHCPC_CheckCtrBlkforIpv4(ulSelftSlotState, ulHashValue);

        DHCPC_CheckCtrBlkforIpv6(ulSelftSlotState, ulHashValue);
    }

    return;
}


VOID DHCPC_SelfMsgProc(UCHAR *pucMsg)
{
    DHCPC_INNER_MSG_S *pstInnerMsg = NULL;

    if ( NULL == pucMsg )
    {
        return;
    }

    pstInnerMsg = (DHCPC_INNER_MSG_S *)pucMsg;

    switch ( pstInnerMsg->ulMsgCode )
    {
        case DHCPC_INNER_MSGCODE_CHECK_PDP :
            DHCPC_CheckPdpContext(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_CHECK_CNTRL_BLCK :
            DHCPC_CheckCtlBlock(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_TIM_RESTORE :
            DHCPV6C_TimerRestoreForSpud(pstInnerMsg);
            break;

        case DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE :
            DHCPV6C_ProcBoardStateChangeMsg();
            break;

        default:
            VOS_Assert(0);
            break;
    }

    return;
}
