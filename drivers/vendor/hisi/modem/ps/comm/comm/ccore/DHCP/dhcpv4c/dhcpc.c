
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
#include "dhcpv6c_fsm.h"

RELTMR_T g_ulDhcpcBoardStateChgDelayTimerId = 0;

/* add by w00316385 start */
#define DHCPM_MAX_REQUEST_TIMEOUT_NUM 5
extern DHCP_SERVER_STATUS_S *g_pstDhcpServerStatus;
/* add by w00316385 end */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_C
/*lint +e767*/

/*****************************************************************************
 �� �� ��  : DHCPC_RenewTimeOut
 ��������  : ��ַ���ⶨʱ����ʱ�Ĵ�������ɨ������dhcp���ƿ飬��ɵ�ַ�����⴦��
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��6��7��
    ��    ��   : heguangwei 65937
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_RenewTimeOut( VOID )
{
    ULONG i = 0;
    ULONG ulRetTimeInSec = 0;
    ULONG ulIpUsedTime = 0;
    UCHAR ucReSendFlg = 0;
    DHCPC_CTRLBLK    *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK    *pstDhcpNewcCtlBlk = NULL;
    ULONG ulDhcpCtlCount = 0;
    UCHAR ucSCID = 0;
    ULONG ulSendRlt = VOS_OK;     /* Modified by jixiaoming at 2011-05-10 for pclint */
    UCHAR ucByte24Value = 0;
    ULONG ulSendNum = 0;
    ULONG ulDhcpRenewNum = 0;
    ULONG ulLease = 0;
    ULONG ulT1 = 0;
    ULONG ulT2 = 0;
    ULONG ulSndLAP2RelMsgCnt = 0;
    DHCPC_CTRLBLK_NODE stDhcpcTempCtlBlkNode = {0};
    DHCPC_TEMPCTRLBLK *pstDhcpcTempCtlBlk = NULL;
    ULONG ulOldCtrlblkXaxis = 0;

    /*24����ο���DHCPÿ�η���������Ϣ����M_SPM_AM_DHCP_RENEW_MESSAGE_NUM*/
    if (VOS_OK != SPM_GetByteValue(M_SPM_BYTE_024, &ucByte24Value))
    {
        ucByte24Value = 0;
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_243);
    }

    /*���û������24����Σ���Ĭ��ÿ�η���60��*/
    if(0 == ucByte24Value)
    {
        ulSendNum = 60;
    }
    else
    {
        ulSendNum = ucByte24Value;
    }

    ucSCID = (UCHAR)DHCPC_SELF_CMPIDX_INSG;

    /*�������ƿ�HASH��*/
    for(i = g_ulCtrlblkXaxis; i < DHCPC_CTRLBLK_HASH_TABLE_SIZE; i++)
    {
        pstDhcpcCtlBlk = ( DHCPC_CTRLBLK * )g_pstDhcpcCtrlBlkRec[i];
        ulOldCtrlblkXaxis = i;
        g_ulCtrlblkXaxis++;

        /*��������꣬�ӵ�һ���û����¿�ʼ*/
        if (DHCPC_CTRLBLK_HASH_TABLE_SIZE == g_ulCtrlblkXaxis)
        {
            g_ulCtrlblkXaxis = 0;
        }

        while (g_ulCtrlblkYaxis != 0)
        {
            if (NULL == pstDhcpcCtlBlk)
            {
                g_ulCtrlblkYaxis = 0;
                break;
            }
            pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
            g_ulCtrlblkYaxis--;
        }
        for (; ;)
        {
            if (NULL == pstDhcpcCtlBlk)
            {
                g_ulCtrlblkYaxis = 0;
                break;
            }
            else
            {
                pstDhcpNewcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
                /*��ַ����ֻ���Ѿ����ߵ��û�*/
                if ( ( DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus )
                     ||( DHCPC_STATE_BOUND == pstDhcpcCtlBlk->usDhcpStatus ) )
                {
                    ucReSendFlg = VRP_NO;
                    ulLease     = pstDhcpcCtlBlk->ulLease;
                    ulT1 = DHCPC_GET_T1_BY_LEASE(ulLease);
                    ulT2 = DHCPC_GET_T2_BY_LEASE(ulLease);
                    ( VOS_VOID )PGP_TmNowInSec( &ulRetTimeInSec );
                    ulIpUsedTime = ulRetTimeInSec - pstDhcpcCtlBlk->ulTimeStamp;

                    if( ulIpUsedTime*2 >= ulT2 + ulLease ) /* 15/16 lease */
                    {
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOut::Notify GTPC to delete context by Ip address!%u,%u,%d,%u,%u" ,
                        ulRetTimeInSec,pstDhcpcCtlBlk->ulTimeStamp,pstDhcpcCtlBlk->usDhcpStatus,i,pstDhcpcCtlBlk->ulDHCPCtxIdx );
                        pstDhcpcTempCtlBlk = &(stDhcpcTempCtlBlkNode.stDhcpcTmpCtlBlk );
                        pstDhcpcTempCtlBlk->ulUserIpAddr = pstDhcpcCtlBlk->aulUserIpAddr[0];
                        pstDhcpcTempCtlBlk->ucUserType = pstDhcpcCtlBlk->ucUserType;
                        pstDhcpcTempCtlBlk->usPoolIndex = pstDhcpcCtlBlk->usPoolIndex;
                        pstDhcpcTempCtlBlk->ulAgetIP = pstDhcpcCtlBlk->aulAgentIpAddr[0];
                        pstDhcpcTempCtlBlk->ulPdpIndex = pstDhcpcCtlBlk->ulPDPIndex;
                        pstDhcpcTempCtlBlk->ucAddressType = LAP_IPV4;
                        pstDhcpcTempCtlBlk->usDhcpGroupIndex = pstDhcpcCtlBlk->usServerGrpIndex;
                        pstDhcpcTempCtlBlk->ucSCID = ucSCID;
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
                        /* BEGIN: Added by jixiaoming at 2011-04-13 */
                        pstDhcpcTempCtlBlk->ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;
                        /* END: Added by jixiaoming at 2011-04-13 */
                        pstDhcpcTempCtlBlk->ucRandomNo = pstDhcpcCtlBlk->ucRandomNo;

                        /* ��LAP2������Ϣ��֪ͨɾ���û�  */
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOutMsg to lap%u,%d,%u!",
                        pstDhcpcTempCtlBlk->ulUserIpAddr, pstDhcpcTempCtlBlk->usPoolIndex, pstDhcpcTempCtlBlk->ulAgetIP );
                        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_204);
                        ( VOID )DHCPC_SendMsgToLAP2(&stDhcpcTempCtlBlkNode, DHCPC_SND2_LAP2_ADDR_REL_MSG );
                        /* ����release��Ϣ */
                        ( VOID )DHCPC_Pkt_Send( DHCP_RELEASE, pstDhcpcTempCtlBlk );

                        /* ����Ӧ���ͷ�dhcp���ƿ�,��ʱ���ƿ� */
                        DHCPC_FreeDhcpCtrlBlk( pstDhcpcCtlBlk->ulDHCPCtxIdx, pstDhcpcCtlBlk->ulTEIDC, pstDhcpcCtlBlk->ucUser, pstDhcpcCtlBlk->ulPDPIndex);
                        PGP_MemZero(&stDhcpcTempCtlBlkNode, sizeof(DHCPC_CTRLBLK_NODE));
                        pstDhcpcTempCtlBlk = NULL;
                        ulSndLAP2RelMsgCnt++;
                        if ( ulSndLAP2RelMsgCnt > 150 )
                        {
                            g_ulCtrlblkXaxis = ulOldCtrlblkXaxis;
                            g_ulCtrlblkYaxis = 0;
                            return;
                        }
                    }
                    else if ( ulIpUsedTime >=  ulT2 ) /* 7/8 lease */
                    {
                        /* ����Э��涨ֻ��1/2��1/8ʱ�䷢������Ϣ��������KPN����Ҫ�����ܺ�����Ҫ������ο����Ƿ񲻶Ϸ��� */
                        if (DHCPC_STATE_ReBinding != pstDhcpcCtlBlk->usDhcpStatus)
                        {
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Rebounding-<<<pstDhcpcCtlBlk->usDhcpStatus=%d!",pstDhcpcCtlBlk->usDhcpStatus );
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n -<<<ulIpUsedTime Rebounding!" );
                            pstDhcpcCtlBlk->usDhcpStatus = DHCPC_STATE_ReBinding;
                            ucReSendFlg = VRP_YES;
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_229);
                        }
                    }
                    else if ( ulIpUsedTime >=  ulT1 ) /* 1/2 lease */
                    {
                        /* ����Э��涨ֻ��1/2��1/8ʱ�䷢������Ϣ��������KPN����Ҫ�����ܺ�����Ҫ������ο����Ƿ񲻶Ϸ��� */
                        if (DHCPC_STATE_ReNewing != pstDhcpcCtlBlk->usDhcpStatus)
                        {
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Renewing-<<<pstDhcpcCtlBlk->usDhcpStatus=%d!",pstDhcpcCtlBlk->usDhcpStatus );
                            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n -<<<ulIpUsedTime Renewing!" );
                            pstDhcpcCtlBlk->usDhcpStatus = DHCPC_STATE_ReNewing;
                            ucReSendFlg = VRP_YES;
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_230);
                        }
                    }
                    /*�Ƿ��ط�REQ��Ϣ*/
                    if ( VRP_YES == ucReSendFlg )
                    {
                        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RenewTimeOut::Renew Ip address for context %d !", g_ulCurrDHCPCCtlIndex );
                        ulSendRlt = DHCPC_RenewIpAddr( pstDhcpcCtlBlk );
                        if(VOS_OK != ulSendRlt)
                        {
                            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_239);
                        }

                        ulDhcpRenewNum ++; /*����������Ϣ����*/
                    }
                }

                g_ulCtrlblkYaxis++;

                ulDhcpCtlCount++;
            }
            pstDhcpcCtlBlk = pstDhcpNewcCtlBlk;
        }

        /*һ�α���200�����ƿ���߷���ulSendNum��������Ϣ*/
        if(  (ulDhcpCtlCount >= 300)
          ||(ulDhcpRenewNum >= ulSendNum))
        {
            break;
        }

        if (0 ==(g_ulCtrlblkXaxis %5000) )
        {
            break;
        }
    }

    return;
}


ULONG DHCPC_GetValidTestTime()
{
    ULONG ulPrimTesttime = 0;
    UCHAR ucSoftParaByte132 = 0;

    /* BEGIN: Added by jixiaoming at 2011-09-27 for  CR20101222007 */
    /* ��ȡbyte132��ε�ֵ */
    if (VOS_OK != SPM_GetByteValue(M_SPM_DHCP_SERVER_TEST_INTERVAL, &ucSoftParaByte132))
    {
        VOS_Assert( 0 );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_300);
        ucSoftParaByte132 = 0;
    }
    /* END: Added by jixiaoming at 2011-09-27 for  CR20101222007 */

    /*Ĭ��10����*/
    ulPrimTesttime = ((0 == ucSoftParaByte132) ?
        DHCPC_SRV_TIMER_LENGTH : ((DHCPC_SRV_TIMER_LENGTH / 10) * ucSoftParaByte132));

    return ulPrimTesttime;
}


VOID DHCPC_PriPrimarySrvStatusMaintenance(DHCP_SERVER_STATUS_S *pstDhcpServerStatus, ULONG ulDhcpGroupIndex)
{
    ULONG ulRet = 0;
    if ((NULL == pstDhcpServerStatus) || (ulDhcpGroupIndex >= DHCPGRP_MAX_NUM))
    {
        return;
    }

    if (pstDhcpServerStatus->ucPrimSrvTimerStatus == DHCP_PRISRV_TIMER_DOWN)
    {
        if (0 != g_aulDhcpcSrvTimerId[ulDhcpGroupIndex])
        {
            (VOID)PGP_Timer_Delete(&(g_aulDhcpcSrvTimerId[ulDhcpGroupIndex]));
        }

        if ( PGP_Timer_Create( DHCPC_SELF_CSI,
                               DHCPC_MSG_TYPE_TIMER,
                               DHCPC_GetValidTestTime(),/*ʹ��������õ�ֵ*/
                               ( VOID ( * )( VOID* ) )DHCPC_SeverTimeOut,/*pclint �ûص�����ʹ��ֵ���� ������*/
                               (VOID *)(ulDhcpGroupIndex),
                               &g_aulDhcpcSrvTimerId[ulDhcpGroupIndex],
                               VOS_TIMER_NOLOOP ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_007);
            VOS_Assert( 0 );
        }

        ulRet = DHCPM_SetPrimSrvTimerStatusByIndex(ulDhcpGroupIndex, DHCP_PRISRV_TIMER_ON);
        if (VOS_OK != ulRet)
        {
            g_ulCurrProcIndex++;
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_269);
        }

    }
    return;
}


ULONG DHCPC_RetransNodeTimerOutProc(DHCPC_CTRLBLK_NODE *pCurrNode)
{
    ULONG ulDhcpGroupIndex = 0;
    ULONG ulRet= VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pCurrNode)
    {
        return VOS_ERR;
    }

    ulDhcpGroupIndex = (ULONG)((pCurrNode->stDhcpcTmpCtlBlk ).usDhcpGroupIndex);
    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        /*��ǰ�ڵ㲻�ٴ���ֱ���˳�*/
        return VOS_ERR;
    }

    if (pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp == stDhcpServer.aulPrimaryServerIp[0])
    {
        /*��һ������server�Ϸ���*/
        if (DHCPC_SNDSRVSEND <= (pCurrNode->stDhcpcTmpCtlBlk ).usAlreadySendFlg)
        {
            /*�Ѿ��������β����ط���ֱ�ӻظ�ʧ�ܣ��������������server������λ��*/
            return VOS_ERR;
        }
        else if ((DHCPC_ALREADYRESEND == (pCurrNode->stDhcpcTmpCtlBlk.usAlreadySendFlg))
                || ((DHCPC_FIRSTSEND == (pCurrNode->stDhcpcTmpCtlBlk.usAlreadySendFlg)
                    && (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus))))
        {
            (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);
            DHCPC_PriPrimarySrvStatusMaintenance(&stDhcpServerStatus, ulDhcpGroupIndex);
            if (0 == stDhcpServer.aulSecondaryServerIp[0])
            {
                /*�����serverû�����ã�ֱ�Ӱ���ʧ�ܴ��������ط�*/
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_218);
                return VOS_ERR;
            }

            /*��Ҫ��server�ٷ���һ��*/
            pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp = stDhcpServer.aulSecondaryServerIp[0];
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_273);
            return VOS_OK;
        }

        /*��û�ط���,����server״̬Ϊnormal����������*/
        return VOS_OK;
    }
    else if ((pCurrNode->stDhcpcTmpCtlBlk).ulSrvIp == stDhcpServer.aulSecondaryServerIp[0])
    {
        /*��һ���ڱ�server�Ϸ���*/
        if (DHCPC_SNDSRVSEND <= ( pCurrNode->stDhcpcTmpCtlBlk ).usAlreadySendFlg)
        {
            /*�Ѿ��������β����ط���ֱ�ӻظ�ʧ��*/
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_265);
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);
            return VOS_ERR;
        }
        else if ((DHCPC_ALREADYRESEND == (pCurrNode->stDhcpcTmpCtlBlk).usAlreadySendFlg)
                 || (( DHCPC_FIRSTSEND == (pCurrNode->stDhcpcTmpCtlBlk).usAlreadySendFlg)
                    && (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucSecondarySrvStatus)))
        {
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_ABNORMAL);

            /*��Ҫ����server�ٷ���һ��*/
            pCurrNode->stDhcpcTmpCtlBlk.ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_273);
            return VOS_OK;
        }

        /*��û�ط���,����server״̬Ϊnormal����������*/
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : DHCPC_RetransTimeOut
 ��������  : ��ʱ�ط���ʱ���ص�������
 �������  : VOID
 �������  : ��
 �� �� ֵ  :VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����������������ж��Ƿ񻻷���������

*****************************************************************************/
VOID DHCPC_RetransTimeOut( VOID )
{
    /*�����ط���ʱ������
     *�����Ҫʧ�ܴ�����������ģ�鷵��ʧ�ܣ�ɾ��ʱ���ƿ飬�ͷ��ڴ�
     *����Ѹýڵ���Ƶ�8s�Ժ�Ķ�ʱ������ȥ��ע�ⲽ��ֻ��0.1s
     *���ж�N(s)�Ķ�ʱ����Ӧ�ò鵽N*10��������ȥ
     *һ���Դ������������нڵ㣬�������ء�
     */

    DHCPC_CTRLBLK_NODE *pCurrNode = NULL;
    DHCPC_CTRLBLK_NODE *pstNextNode = NULL;
    ULONG ulRet = VOS_OK;
    DLL_S* pstHeadTmrNode = NULL;

    if (g_ulCurrProcIndex >= DHCPC_TMR_CIRCLE_TIME)
    {
        g_ulCurrProcIndex = 0;
    }

    /*��ȡ��ǰʱ��۵�ͷ�ڵ㡣*/
    pstHeadTmrNode = &(g_astTimerLink[g_ulCurrProcIndex]);
    pCurrNode = (DHCPC_CTRLBLK_NODE * )DLL_First( pstHeadTmrNode);
    while (NULL != pCurrNode)
    {
        /*���ݽ��յ�����Ϣ���ݣ���DHCPģ��������еõ�������Ϣ*/
        pstNextNode = (DHCPC_CTRLBLK_NODE *)DLL_Next(pstHeadTmrNode,(DLL_NODE_S *)pCurrNode);

        /*�ж��Ƿ��ط��������ط����»�ȡserver��ip��ַ*/
        ulRet = DHCPC_RetransNodeTimerOutProc(pCurrNode);
        if (VOS_OK != ulRet)
        {
            /*����Ҫ�ط�����ȥ���*/
            ( VOID )DHCPC_SendMsgToLAP2(pCurrNode,DHCPC_SND2_LAP2_NO_RSP_MSG);

            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_217);

            /*����ǰ�ڵ���ط�������ɾ��*/
            DHCPC_DelNode(g_ulCurrProcIndex,pCurrNode);

            /* �ͷſ��ƿ�ڵ� */
            DHCPC_FreeDhcpCtrlBlk(pCurrNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pCurrNode->stDhcpcTmpCtlBlk.ulTEIDC,
                                   pCurrNode->stDhcpcTmpCtlBlk.ucUser, pCurrNode->stDhcpcTmpCtlBlk.ulPdpIndex);

            /* �ͷ���ʱ���ƿ�ڵ� */
            DHCPC_FreeDhcpTmpNode(pCurrNode);
        }
        else
        {
            /*��Ҫ�ط����������ⷢ����Ϣ*/
            (VOID)DHCPC_ResendMSG(pCurrNode);
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_011);

            /*���µ�����ǰ�ڵ����ط������е�λ��*/
            DHCPC_DelNode(g_ulCurrProcIndex,pCurrNode);
            DHCPC_InSertNodeAfterSecs(DHCPC_8_SECONDS,pCurrNode);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_RetransTimeOut: The first time retrans time out!");
        }
        pCurrNode = pstNextNode;
    }

    g_ulCurrProcIndex++;
    if (DHCPC_TMR_CIRCLE_TIME <= g_ulCurrProcIndex)
    {
        g_ulCurrProcIndex = 0;
    }

    return;
}
VOID DHCPv4C_TimerCallBack(UCHAR ucIpType, ULONG ulTeidc, UCHAR ucEvent)
{
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    ULONG ulRet = VOS_OK;

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_321);

    ulRet = DHCPC_QueryDhcpcContext(ucIpType, ulTeidc, &pstDhcpcCtlBlk);
    if  ((VOS_OK != ulRet) || (NULL == pstDhcpcCtlBlk))
    {
        return;
    }

    if ((DHCPC_STATE_LEASE == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_ReNewing == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_PreReBinding == pstDhcpcCtlBlk->usDhcpStatus)
         ||(DHCPC_STATE_ReBinding == pstDhcpcCtlBlk->usDhcpStatus))
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_322);

        ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, &stDhcpServer, &stDhcpServerStatus);
        if ( VOS_OK != ulRet )
        {
            /*��ǰ�ڵ㲻�ٴ���ֱ���˳�*/
            return;
        }

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPv4C_TimerCallBack pstDhcpcCtlBlk->aulSrvIp[0] = %u", pstDhcpcCtlBlk->aulSrvIp[0]);

        if (pstDhcpcCtlBlk->aulSrvIp[0] == stDhcpServer.aulPrimaryServerIp[0])
        {
            /* ��һ�θ���server��������Ϣ */
            if (DHCP_SEVER_NORMAL == stDhcpServerStatus.ucPrimarySrvStatus)
            {
                g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucPrimRequestTimeout++;
                if (g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucPrimRequestTimeout >= DHCPM_MAX_REQUEST_TIMEOUT_NUM)
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_323);
                    (VOID)DHCPM_SetPrimarySrvStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, DHCP_SEVER_ABNORMAL);
                    DHCPC_PriPrimarySrvStatusMaintenance(&stDhcpServerStatus, pstDhcpcCtlBlk->usServerGrpIndex);
                }
            }
        }
        else if (pstDhcpcCtlBlk->aulSrvIp[0] == stDhcpServer.aulSecondaryServerIp[0])
        {
            /* ��һ�θ���server��������Ϣ */
            if (DHCP_SEVER_NORMAL == stDhcpServerStatus.ucSecondarySrvStatus)
            {
                g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucSecRequestTimeout++;
                if (g_pstDhcpServerStatus[pstDhcpcCtlBlk->usServerGrpIndex].ucSecRequestTimeout >= DHCPM_MAX_REQUEST_TIMEOUT_NUM)
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_324);
                    (VOID)DHCPM_SetSecondarySrvStatusByIndex(pstDhcpcCtlBlk->usServerGrpIndex, DHCP_SEVER_ABNORMAL);
                }
            }
        }
    }

    return;

}

/*****************************************************************************
 �� �� ��  : DHCPC_TimerOut
 ��������  : dhcp��ʱ����ʱ����
 �������  : VOID
 �������  : ��
 �� �� ֵ  :VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����������������ж��Ƿ񻻷���������

*****************************************************************************/
VOID DHCPC_TimerOut( VOID* pvArg )
{
    ULONG    ulTimerType = 0;
    UCHAR    ucLogicSlot = 0;

    if ( NULL == pvArg )
    {
        return ;
    }

    /* �����ʼ���׶�,��ʼ������ͳ��,���������³�ʼ�� */
    if (ulDhcpcPerfInitFinish != VOS_TRUE)
    {
        (VOID)DHCPC_OmInitial();
    }

    /*���岻����*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return;
    }

    ulTimerType = *( ( ULONG* )pvArg );
    if ( g_ulTimerRenewType == ulTimerType )
    {
        /*���ö�ʱ����ʱ*/
        DHCPC_RenewTimeOut();
    }
    else if ( g_ulTimerRetransType == ulTimerType )
    {
        /*�ط���ʱ����ʱ*/
        DHCPC_RetransTimeOut();
    }

    return ;
}
/*****************************************************************************
 �� �� ��  : DHCPC_SeverTimeOut
 ��������  : ������״̬̽�ⶨʱ����ʱ
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��27��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_SeverTimeOut( ULONG pvArg )
{
    ULONG           ulServerIndex = 0;
    ULONG ulRet = VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus;
    LAP_DHCP_CFG_S stDhcpServer;

    if ( DHCPGRP_MAX_NUM <= pvArg )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_071);
        return ;
    }

    ulServerIndex = pvArg;

    g_aulDhcpcSrvTimerId[ulServerIndex] = 0;

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulServerIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_072);
        return ;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_073);

    // pstDhcpcSrvGrp->ucPrimarySrvTest = DHCP_PRISRV_TEST_ON;
    /* �޸Ķ�ʱ��״̬ ʹ�������л�ʱ�ܹ�����̽����������*/
    // pstDhcpcSrvGrp->ucPrimSrvTimerStatus = DHCP_PRISRV_TIMER_DOWN;

    /*linyufeng 001766669 DHCPv6���� 2012-07-14 start*/
    if(DHCP_SEVER_GROUP_IS_IPV6 == stDhcpServer.ucIsDHCPv6)
    {
        if ( DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus )
        {
            (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulServerIndex, DHCP_SEVER_TRY);

        }
        if ( DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucSecondarySrvStatus )
        {
            (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulServerIndex, DHCP_SEVER_TRY);
        }
    }
    else
    {
        if (DHCP_SEVER_ABNORMAL == stDhcpServerStatus.ucPrimarySrvStatus)
        {
            (VOID)DHCPM_SetPrimarySrvTestByIndex(ulServerIndex, DHCP_PRISRV_TEST_ON);

            (VOID)DHCPM_SetPrimSrvTimerStatusByIndex(ulServerIndex, DHCP_PRISRV_TIMER_DOWN);
        }
    }
    /*linyufeng 001766669 DHCPv6���� 2012-07-14 end*/


    return ;
}
ULONG DHCPC_SetServerStatusToNormalByIndexAndIp(USHORT usDhcpGroupIndex, ULONG ulIP)
{
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    ULONG ulRet = VOS_OK;
    ULONG ulDhcpGroupIndex = (ULONG)usDhcpGroupIndex;

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_119);
        return VOS_ERR;
    }

    if ( stDhcpServer.aulPrimaryServerIp[0] == ulIP )
    {
        ulRet = DHCPM_SetPrimarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_NORMAL);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_263);
        }

        ulRet = DHCPM_SetPrimTimeoutNumByIndex(ulDhcpGroupIndex, 0);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_264);
        }
    }
    else if ( stDhcpServer.aulSecondaryServerIp[0] == ulIP )
    {
        ulRet = DHCPM_SetSecondarySrvStatusByIndex(ulDhcpGroupIndex, DHCP_SEVER_NORMAL);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_261);
        }

        ulRet = DHCPM_SetSecTimeoutNumByIndex(ulDhcpGroupIndex, 0);
        if ( VOS_OK != ulRet )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_120);
        return VOS_ERR;
    }

    return VOS_OK;
}

VOID DHCPC_PrintLap2DhcpMsg(LAP2_DHCPC_MSG_S* pstLap2Msg)
{
    if (NULL == pstLap2Msg)
    {
        VOS_Assert(0);
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "msgtype=%u iptype=%u lapno=%u poolindex=%u sectionnum=%u dhcpgroupindex=%u",
            pstLap2Msg->ucMsgType, pstLap2Msg->ucAddressType, pstLap2Msg->ucLAPNo, pstLap2Msg->usPoolIndex,
            pstLap2Msg->ucSectionNum, pstLap2Msg->usDhcpGroupIndex);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "agentip=0x%x %x %x %x  ip=0x%x %x %x %x",
            pstLap2Msg->aulAgentIP[0],pstLap2Msg->aulAgentIP[1], pstLap2Msg->aulAgentIP[2], pstLap2Msg->aulAgentIP[3],
            pstLap2Msg->aulPdpAddr[0],pstLap2Msg->aulPdpAddr[1], pstLap2Msg->aulPdpAddr[2], pstLap2Msg->aulPdpAddr[3]);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "apnindex=%u  vpnid=%u  usertype=%u ucGtpVer=%u ulTeidc=0x%x ulIndex=%u ",
            pstLap2Msg->usApnIndex, pstLap2Msg->usVpnId, pstLap2Msg->ucUserType, pstLap2Msg->ucGtpVer,
            pstLap2Msg->ulTeidc, pstLap2Msg->ulIndex);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "PrimaryDNS=0x%x %x %x %x  SecondaryDNS=0x%x %x %x %x",
            pstLap2Msg->aulPrimaryDNS[0], pstLap2Msg->aulPrimaryDNS[1], pstLap2Msg->aulPrimaryDNS[2], pstLap2Msg->aulPrimaryDNS[3],
            pstLap2Msg->aulSecondaryDNS[0], pstLap2Msg->aulSecondaryDNS[1], pstLap2Msg->aulSecondaryDNS[2], pstLap2Msg->aulSecondaryDNS[3]);

    return;
}

/*����LAP��ַ��������͵�ַ�ͷ�������Ϣ���ٷ�DHCP*/
ULONG DHCPC_ReceiveLAP2Msg( VOID* pMsgBuf )
{
    UCHAR    ucMsgCode = 0;
    ULONG ulDHCPCtlIdx = 0;
    UCHAR ucLogicSlot = 0;
    LAP2_DHCPC_MSG_S* pstLap2DhcpCMsg = NULL;

    /*���岻����*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return VOS_OK;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_ReceiveLAP2Msg()" );
    if ( NULL == pMsgBuf )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_013);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ReceiveLAP2Msg NULL MsgBuf" );
        return VOS_ERR;
    }
    pstLap2DhcpCMsg = ( LAP2_DHCPC_MSG_S* )pMsgBuf;
    DHCPC_PRINT_LAP_MSG(pstLap2DhcpCMsg);
    ucMsgCode = pstLap2DhcpCMsg->ucMsgType;

    /* �����û�������䵱ǰDHCP���ƿ����� */
    ulDHCPCtlIdx = pstLap2DhcpCMsg->ulTeidc;

    switch (ucMsgCode)
    {
            /* �յ���ַ������Ϣ */
        case LAP2_SND2_DHCPC_ADDR_REQ_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_014);
            DHCPC_MsgProc_Apply( pstLap2DhcpCMsg );
            break;

            /* �յ���ַ�ͷ���Ϣ */
        case LAP2_SND2_DHCPC_ADDR_REL_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_015);
            DHCPC_MsgProc_Release( pstLap2DhcpCMsg);
            break;

            /* �յ���ַ����/������Ϣ
               �˴������Ϣֻ�Ǹ��øù������,����LAP2������Ϣ*/
        case LAP2_SND2_DHCPC_ADDR_REN_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_016);
            DHCPC_MsgProc_Lease( ( LAP2_DHCPC_MSG_S * )pstLap2DhcpCMsg,ulDHCPCtlIdx );
            break;

            /* �յ���ַǿ�ƻ�����Ϣ */
        case LAP2_SND2_DHCPC_ADDR_FORCE_REL_MSG:
            break;

            /* �յ���ַ��ͻ��Ϣ */
        case LAP2_SND2_DHCPC_ADDR_CONFLICT_MSG:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_019);
            (VOID)DHCPC_MsgProc_Conflict( pstLap2DhcpCMsg);
            break;

        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_020);
            VOS_Assert( 0 );
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_ReceiveSPUMsg Error MsgCode!" );
            return VOS_ERR;
    }
    return VOS_OK;
}

VOID DHCPC_ReceiveLap2MbufMsg(PMBUF_S *pstMBuf)
{
    UCHAR  *pucFwdMsg = NULL;

    if (NULL == pstMBuf)
    {
        VOS_Assert(0);
        return;
    }

    /*��ȡ���ĳ��Ⱥ͵�ַ*/
    pucFwdMsg = PMBUF_MTOD(pstMBuf, UCHAR*);
    if (NULL == pucFwdMsg)
    {
        return;
    }

    (VOID)DHCPC_ReceiveLAP2Msg((VOID *)pucFwdMsg);

    /* ����ͷ�Mbuf */
    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_ReceiveServerMsg
 ��������  : ����sd���͵�server���ص���Ϣ�����������Ӧ����
 �������  :  VOID* pstMsgBuf
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_ReceiveServerMbufMsg(PMBUF_S *pstMsgBuf)
{
    /*server��Ӧ��
     *1)��ѭDHCP״̬��
     *2)��REBIND״̬���ǳ�ʼ״̬������?STATUSΪ0��ɴ�srv-ipȡ����ʱ���ƿ�ָ��
     *3)xid�Ƿ�һ��?
     *4)ɾ����ʱ���ƿ顣
     */
    UDPS_PACKET_INFO_S stPktInf = {0};
    ULONG       ulRet = 0;
    ULONG       ulSrvIP = 0;
    UCHAR       ucLogicSlot = 0;
    ULONG       ulMsgLen = 0;
    UCHAR       *pucMsg = VOS_NULL;

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        return VOS_OK;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "entry" );

    if ( NULL == pstMsgBuf )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_021);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n MBUF msg NULL!" );
        return VOS_ERR;
    }

    /* BEGIN: Modified by jixiaoming at 2011-11-28 for CR20110907018 */
    ulRet = (ULONG)UDPS_PickUpExt( &stPktInf, pstMsgBuf );
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_022);
        DHCPC_DebugPrint(PTM_LOG_ERR, " call UDPS_PickUp failed. [errcode=%u]", ulRet);
        return VOS_ERR;
    }

    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (ulMsgLen > DHCP_PKT_ASSUME_MAX_LEN)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_113);
        DHCPC_DebugPrint(PTM_LOG_WARNING, " receive malformed Packet. length=%u", ulMsgLen);
        return VOS_ERR;
    }
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ReceiveServerMsg pkt length=%u", ulMsgLen );

    /* ���Mbuf�Ƿ����Ϣ�����˷�Ƭ */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        /* û�з�Ƭ */
        pucMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* �з�Ƭ����MBUF���ݸ��Ƶ����������ڴ��� */
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ReceiveServerMsg pkt is sliced!" );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_114);
        PGP_MemZero(g_pucDhcpPktBuf, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
        ulRet = PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf,
                                            0,
                                            ulMsgLen,
                                            g_pucDhcpPktBuf);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_WARNING, " call PMBUF_CopyDataFromPMBufToBuffer failed. [errcode=%u]", ulRet);
            VOS_Assert(0);
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_147);
            return VOS_ERR;
        }
        pucMsg = g_pucDhcpPktBuf;
    }

    ulSrvIP = stPktInf.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr;
    if (ulMsgLen > DHCPC_PKT_FIXEDFIELD_LEN)
    {
        DHCPC_Dbg_PacketPrintReceive((DHCP_S*)pucMsg,  ulMsgLen - DHCPC_PKT_FIXEDFIELD_LEN);

        /* ����DHCP��Ϣ */
        (VOS_VOID)DHCPC_Pkt_ProcDHCP((DHCP_S*)pucMsg,  ulMsgLen - DHCPC_PKT_FIXEDFIELD_LEN, ulSrvIP);
    }

    return VOS_OK;
}
VOID DHCPC_ReceiveServerMsg(UCHAR *pucMsg)
{
    PMBUF_S *pstMsgBuf = NULL;

    if ( NULL == pucMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstMsgBuf = *((PMBUF_S **)pucMsg);

    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    (VOID)DHCPC_ReceiveServerMbufMsg(pstMsgBuf);

    ( VOS_VOID )PMBUF_Destroy(pstMsgBuf);
    *((PMBUF_S **)pucMsg) = NULL;

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_DelNode
 ��������  : �ӳ�ʱ�ط�������ɾ��һ���ڵ�
 �������  :  VOID* pstMsgBuf
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_DelNode( ULONG ulTimerIndex, DHCPC_CTRLBLK_NODE* pstCurrNode )
{
    /*�����һ���ڵ�*/
    ULONG    pTmrIndex = 0;

    if ( NULL == pstCurrNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_023);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_DelNode para err!" );
        return;
    }

    if ( DHCPC_INVALID_INDEX == ulTimerIndex )
    {
        ULONG ulHeadNodeType = 0;
        DLL_NODE_S* pstTmpNode = ( DLL_NODE_S* )pstCurrNode;
        /*lint -e716*/
        while ( VOS_TRUE )
        /*lint +e716*/
        {
            ulHeadNodeType = DLL_GET_HANDLE( pstTmpNode );
            if ( DHCPC_HEADNODE_TYPE == ulHeadNodeType )
            {
                DLL_Delete( ( DLL_S* )pstTmpNode,( DLL_NODE_S* )pstCurrNode );
                break;
            }
            pstTmpNode = pstTmpNode->pPrev;
            if(NULL == pstTmpNode)
            {
                break;
            }
        }
    }
    else
    {
        pTmrIndex = ulTimerIndex % DHCPC_TMR_CIRCLE_TIME;
        DLL_Delete( &( g_astTimerLink[pTmrIndex] ), ( DLL_NODE_S * )pstCurrNode );
    }

    return;
}

/*ulSeconds:ulSeconds�������*/
/*****************************************************************************
 �� �� ��  : DHCPC_InSertNodeAfterSecs
 ��������  : ���ط������в���һ���ڵ�
 �������  :  VOID* pstMsgBuf
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_InSertNodeAfterSecs( ULONG ulSeconds,DHCPC_CTRLBLK_NODE* pstCurrNode )
{
    ULONG pTmrIndex = 0;
    DLL_S *pstDhcpcTmrNode = NULL;

    if ( NULL == pstCurrNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_025);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_InSertNodeAfterSecs para err!" );
        return;
    }

    /*������ת����ͷ�������*/
    pTmrIndex = ( g_ulCurrProcIndex + ulSeconds * DHCPC_RETRANS_STEPS_PERSEC )% DHCPC_TMR_CIRCLE_TIME;
    if ( pTmrIndex >= DHCPC_TMR_CIRCLE_TIME )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_026);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_DelNode pTmrIndex error!" );
        return;
    }

    pstDhcpcTmrNode = &( g_astTimerLink[pTmrIndex] );
    DLL_Insert( pstDhcpcTmrNode,NULL,( DLL_NODE_S * )pstCurrNode );

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_GetDhcpTmpNode
 ��������  : ��ȡһ�����е���ʱ���ƿ�ڵ�
 �������  :  VOID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
DHCPC_CTRLBLK_NODE* DHCPC_GetDhcpTmpNode( VOID )
{
    ULONG i = 0;

    for ( i = 0; i < DHCPC_MAX_CTRLBLKNUM; i++ )
    {
        if ( DHCPC_CTRLBLK_IDLE == g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg )
        {
            /*��ռ�ñ�־������ָ��*/
            g_pstDhcpCtrlBlkNodeArr[i].ucOccupiedFlg = DHCPC_CTRLBLK_OCCUPIED;
            return ( DHCPC_CTRLBLK_NODE* )&( g_pstDhcpCtrlBlkNodeArr[i] );
        }
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_027);
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_GetDhcpTmpNode:Dhcp temp control block used up!" );
    return NULL;
}

/*****************************************************************************
 �� �� ��  : DHCPC_FreeDhcpTmpNode
 ��������  : �ͷ���ʱ���ƿ�ڵ�
 �������  :  VOID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_FreeDhcpTmpNode( DHCPC_CTRLBLK_NODE* pNode )
{

    if ( NULL == pNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_028);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_FreeDhcpTmpNode() pNode is null !" );
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_FreeDhcpTmpNode()" );
    /*�ṹ��0��ռ�ñ�־�ָ���IDLE״̬*/
    PGP_MemZero( pNode, sizeof( DHCPC_CTRLBLK_NODE ) );
    return;
}
ULONG DHCPC_RenewIpAddr( DHCPC_CTRLBLK *pstDhcpcCtlBlk )
{
    LAP2_DHCPC_MSG_S stMsg = {0};
    ULONG ulRet = 0;


    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_RenewIpAddr()" );
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_205);

    if ( NULL == pstDhcpcCtlBlk )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n-->DHCPC_RenewIpAddr:NULL == pstDhcpcCtlBlk" );
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_029);
        return VOS_ERR;
    }

    /* �����Ϣ�� */
    stMsg.ucMsgType = LAP2_SND2_DHCPC_ADDR_REN_MSG;
    stMsg.ulIndex = pstDhcpcCtlBlk->ulPDPIndex;
    stMsg.ulTeidc = pstDhcpcCtlBlk->ulTEIDC;
    stMsg.ucGtpVer = pstDhcpcCtlBlk->ucUser;
    stMsg.ucLAPNo = pstDhcpcCtlBlk->ucLAPNo;

    /* �����ô���Ҫ�Ż�, ���ڲ�����д��Ϣ */
    if ( CRM_BOARD_TYPE_SPUD == g_ulDhcpcSpuType )
    {
        ulRet = DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_LAP, LAP2_SND2_DHCPC_ADDR_REN_MSG,
                                (UCHAR *)&stMsg, sizeof(LAP2_DHCPC_MSG_S));
    }
    else
    {
        ulRet = DHCPC_SendURTMsg(DHCPC_SELF_CSI, DHCPC_SELF_CSI, DHCPC_MSG_TYPE_FCM,
                                 LAP2_SND2_DHCPC_ADDR_REN_MSG, (UCHAR *)&stMsg, sizeof(LAP2_DHCPC_MSG_S));
    }

    return ulRet;
}


ULONG DHCPC_SaveTmpDhcpCtrlBlkPtr( ULONG ulDHCPCtlIdx, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPdpIndex, DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNodePtr )
{
    ULONG ulRet = VOS_ERR;
    DHCPC_CTRLBLK   * pstDhcpcCtlBlk = NULL;

    if ( NULL == pstDhcpCtrlBlkNodePtr )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_031);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveTmpDhcpCtrlBlkPtr pDhcpCtrlBlkNodePtr is null!" );
        return ulRet;
    }

    /*��ȡ���ƿ�*/
    pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulDHCPCtlIdx, ulTEIDC);
    if ( NULL != pstDhcpcCtlBlk )
    {
        /*�û���ȡIP��ַ֮ǰ��DHCP���ƿ���û�õģ�
         *ʹ��ser-ip�ֶα�����ʱ���ƿ�ĵ�ַָ��
         */
        if ( DHCPC_STATE_INITIAL == pstDhcpcCtlBlk->usDhcpStatus )
        {
            /*ʹ��ulTmpVar�ֶα���ָ��*/
            pstDhcpcCtlBlk->pTmpDhcpCtrlBlkPtr = (VOID *)pstDhcpCtrlBlkNodePtr;
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveTmpDhcpCtrlBlkPtr usDhcpStatus = INITIAL " );
            ulRet = VOS_OK;
        }
        else
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_032);
            /*������Ϣ*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDhcp State err. when saving TmpCtrlBlk!" );
        }
    }
    else
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_033);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nContexe not exist when saving TmpCtrlBlk!" );
    }

    return ulRet;
}


DHCPC_CTRLBLK_NODE* DHCPC_GetTmpDhcpCtrlBlkPtr( DHCPC_CTRLBLK *pstDhcpCtrBlk )
{
    DHCPC_CTRLBLK_NODE*    pstDhcpCtrlBlkNode = NULL;

    if ( NULL == pstDhcpCtrBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_034);
        VOS_DBGASSERT( 0 );
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_GetTmpDhcpCtrlBlkPtr ulCtrlBlkIndex call func failed!" );
        return NULL;
    }

    if ( ( DHCPC_STATE_INITIAL == pstDhcpCtrBlk->usDhcpStatus )
         && ( 0 != pstDhcpCtrBlk->pTmpDhcpCtrlBlkPtr ) )
    {
        pstDhcpCtrlBlkNode = (DHCPC_CTRLBLK_NODE *)pstDhcpCtrBlk->pTmpDhcpCtrlBlkPtr;
        if ( 0 == VOS_StrCmp( ( const CHAR* )( ( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk ).ucCtrlBlkFlgStr ), DHCPC_TMPCTRLBLK_IDSTR ) )
            return pstDhcpCtrlBlkNode;
    }
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_035);
    return NULL;
}


ULONG DHCPC_SaveSdbDhcpCtrlBlk( DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, VOS_BOOL bIsRenewState )
{
    DHCPC_CTRLBLK        *pstDhcpCtrlBlk = NULL;
    ULONG                        ulRetTimeInSec = 0;

    if ( ( NULL == pstDhcpTmpCtrlBlk ) || ( 0 == pstDhcpTmpCtrlBlk->usLease ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_036);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_SaveSdbDhcpCtrlBlk para err!" );
        return VOS_ERR;
    }

    /*��ȡ���ƿ�*/
    pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(pstDhcpTmpCtrlBlk->ulDHCPCtlIdx, pstDhcpTmpCtrlBlk->ulTEIDC);
    if ( NULL == pstDhcpCtrlBlk )
    {
        /*��ӡ������Ϣ*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_039);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SaveSdbDhcpCtrlBlk pstDhcpCtrlBlk not exist!" );
        return VOS_ERR;
    }
    else
    {
        pstDhcpCtrlBlk->ulDHCPCtxIdx = pstDhcpTmpCtrlBlk->ulDHCPCtlIdx;
        pstDhcpCtrlBlk->aulAgentIpAddr[0] = pstDhcpTmpCtrlBlk->ulAgetIP;/*��ʱ������agent ip*/
        pstDhcpCtrlBlk->usVPNIndex= pstDhcpTmpCtrlBlk->usVpnId;
        pstDhcpCtrlBlk->usServerGrpIndex = pstDhcpTmpCtrlBlk->usDhcpGroupIndex;
        pstDhcpCtrlBlk->ucUserType = pstDhcpTmpCtrlBlk->ucUserType;

        pstDhcpCtrlBlk->aulMSISDN[0] = pstDhcpTmpCtrlBlk->aulMSISDN[0];
        pstDhcpCtrlBlk->aulMSISDN[1] = pstDhcpTmpCtrlBlk->aulMSISDN[1];
        pstDhcpCtrlBlk->aulUserIpAddr[0] = pstDhcpTmpCtrlBlk->ulUserIpAddr;
        pstDhcpCtrlBlk->ulLease = pstDhcpTmpCtrlBlk->usLease;
        pstDhcpCtrlBlk->aulSrvIp[0] = pstDhcpTmpCtrlBlk->ulSrvIp;
        pstDhcpCtrlBlk->usPoolIndex = pstDhcpTmpCtrlBlk->usPoolIndex;

        pstDhcpCtrlBlk->aulIMSI[0] = pstDhcpTmpCtrlBlk->aulIMSI[0];
        pstDhcpCtrlBlk->aulIMSI[1] = pstDhcpTmpCtrlBlk->aulIMSI[1];
        /* BEGIN: Added by jixiaoming for  IMEI���� at 2012-8-17 */
        pstDhcpCtrlBlk->aulIMEI[0] = pstDhcpTmpCtrlBlk->aulIMEI[0];
        pstDhcpCtrlBlk->aulIMEI[1] = pstDhcpTmpCtrlBlk->aulIMEI[1];
        /* END: Added by jixiaoming for IMEI���� at 2012-8-17 */
        pstDhcpCtrlBlk->ucRole = pstDhcpTmpCtrlBlk->ucRole;
        /*��Ҫ���û����͡�TEIDC��������������ֵ*/
		pstDhcpCtrlBlk->ucUser = pstDhcpTmpCtrlBlk->ucUser;
        pstDhcpCtrlBlk->ulTEIDC = pstDhcpTmpCtrlBlk->ulTEIDC;
        pstDhcpCtrlBlk->ulPDPIndex = pstDhcpTmpCtrlBlk->ulPdpIndex;
        /* BEGIN: Added by jixiaoming at 2011-03-29 */
        pstDhcpCtrlBlk->ucLAPNo = pstDhcpTmpCtrlBlk->ucLAPNo;
        /* END: Added by jixiaoming at 2011-03-29 */
        pstDhcpCtrlBlk->ucRandomNo = pstDhcpTmpCtrlBlk->ucRandomNo;

        (VOID)PGP_TmNowInSec( &ulRetTimeInSec);
        pstDhcpCtrlBlk->ulTimeStamp = ulRetTimeInSec;

        if ( VOS_TRUE == bIsRenewState )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_038);

            VOS_Assert( pstDhcpCtrlBlk->ulTmpVar == pstDhcpTmpCtrlBlk->ulTimeStamp );
        }
        else
        {
            pstDhcpCtrlBlk->ulTmpVar = 0;
        }

        pstDhcpCtrlBlk->usDhcpStatus = DHCPC_STATE_BOUND;

        return VOS_OK;
    }
}

/*****************************************************************************
 �� �� ��  : DHCPC_ResendMSG
 ��������  : �ط���Ϣ�Ĵ�����
 �������  :  DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_ResendMSG( DHCPC_CTRLBLK_NODE* pstDhcpCtrlBlkNode )
{
    /*ֻ�ط�DISCOVER��REQUEST��Ϣ*/
    USHORT    usDhcpStatus = 0;
    ULONG    ulRet = VOS_ERR;
    DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk = NULL;

    if ( NULL == pstDhcpCtrlBlkNode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_040);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG Null CtrlBlkNode!" );
        return VOS_ERR;
    }

    pstDhcpTmpCtrlBlk = &( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk );
    usDhcpStatus = pstDhcpTmpCtrlBlk->usDhcpStatus;
    switch ( usDhcpStatus )
    {
        case DHCPC_STATE_DISCOVER:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_041);
            ulRet = ( ULONG )DHCPC_Pkt_Send( DHCP_DISCOVER, pstDhcpTmpCtrlBlk );
            break;
        case DHCPC_STATE_REQUEST:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_042);
            ulRet = ( ULONG )DHCPC_Pkt_Send( DHCP_REQUEST, pstDhcpTmpCtrlBlk );
            break;
        default:
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_043);
            VOS_Assert( 0 );
            ulRet = VOS_ERR;/*for UT*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG error DHCP State!" );
            break;
    }
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_044);
        /*ɾ���ƿ�*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ResendMSG resend failed!" );
        /* �����ô���ʧ������Ѿ��������ͷŴ�����ע�͵��˴����ͷŴ��� */
        /*
        DHCPC_DelNode( g_ulCurrProcIndex,pstDhcpCtrlBlkNode );
        DHCPC_FreeDhcpCtrlBlk( pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulDHCPCtlIdx, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulTEIDC, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ucUser, pstDhcpCtrlBlkNode->stDhcpcTmpCtlBlk.ulPdpIndex );
        DHCPC_FreeDhcpTmpNode( pstDhcpCtrlBlkNode );
        */
        return ulRet;
    }
    /*�ط�ʱ������timestamp*/
    VOS_Assert( NULL != pstDhcpTmpCtrlBlk->ulTimeStamp );

    /* �����ط���־��ÿ���ط�״̬���Ǩ��1 */
    pstDhcpTmpCtrlBlk->usAlreadySendFlg += 1;

    return VOS_OK;
}


VOID DHCPC_SetReNewDhcpServerIp(DHCPC_TEMPCTRLBLK *pstDhcpTmpCtrlBlk, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    UCHAR ucBit218Value = 0;

    if (VOS_OK != SPM_GetBitValue(M_SPM_BIT_218, &ucBit218Value))
    {
        ucBit218Value = 0;
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_281);
    }

    if (0 == ucBit218Value)
    {
        if (DHCP_SEVER_NORMAL == pstDhcpServerStatus->ucPrimarySrvStatus)
        {
                pstDhcpTmpCtrlBlk->ulSrvIp = pstDhcpServer->aulPrimaryServerIp[0];
                DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_OutPut The Secondary DHCP Server has been down!Send Lease Message To The Secondary DHCP Server!" );
        }
        else if ((DHCP_SEVER_NORMAL == pstDhcpServerStatus->ucSecondarySrvStatus)
            && (0 != pstDhcpServer->aulSecondaryServerIp[0]))
        {
                pstDhcpTmpCtrlBlk->ulSrvIp = pstDhcpServer->aulSecondaryServerIp[0];
                DHCPC_DebugPrint(PTM_LOG_DEBUG,
                                "\r\n DHCPC_OutPut The Primary DHCP Server has been down!Send Lease Message To The Primary DHCP Server!" );

        }
        /* ����������Ϣ: ��������˾���ԭ���ķ��� */
        else
        {
             DHCPC_DebugPrint(PTM_LOG_DEBUG,
                            "\r\n DHCPC_OutPut The Primary and Secondary both down! Send Lease Message To The Original DHCP Server!" );
        }
    }

    return;
}
void DHCPC_SetTmpCtrlBlkSrvIp(DHCPC_TEMPCTRLBLK *pstDhcpTmpCtrlBlk)
{
    ULONG ulRet = VOS_OK;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pstDhcpTmpCtrlBlk)
    {
        /*������Ϣ*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SetDhcpSrvIp para error pstDhcpTmpCtrlBlk = NULL");
        return;
    }

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex((ULONG)pstDhcpTmpCtrlBlk->usDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        return;
    }

    DHCPC_SetReNewDhcpServerIp(pstDhcpTmpCtrlBlk, &stDhcpServer, &stDhcpServerStatus);

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_OutPut
 ��������  : DHCPģ���udp���ͺ���
 �������  : UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, PMBUF_S* pMBuf, LONG* plSecondReturnCode
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
LONG DHCPC_OutPut( UCHAR ucPktType, DHCPC_TEMPCTRLBLK* pstDhcpTmpCtrlBlk, PMBUF_S* pMBuf, LONG* plSecondReturnCode )
{
    LONG                    lRetCode = VOS_OK;
    FWD_TO_CTRL_HDR         stCtrlEncap = {0};
    UDPS_PACKET_INFO_S         stNodeTemp = {0};
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};
    ULONG ulDhcpGroupIndex = 0;
    ULONG ulRet = VOS_OK;

    /*�����Ϸ��Լ��*/
    if ( NULL == plSecondReturnCode )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_045);
        /*������Ϣ*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG,
                     "\r\n DHCPC_OutPut para error plSecondReturnCode = NULL");
        return VOS_ERR;
    }

    *plSecondReturnCode = VOS_ERR;

    if ( ( NULL == pstDhcpTmpCtrlBlk ) || ( NULL == pMBuf ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_046);
        /*������Ϣ*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut para error pstDhcpTmpCtrlBlk = NULL,pMBuf = NULL");
        return VOS_ERR;
    }

    /*�ж�Ҫ������Ϣ�������Ƿ�Ϸ�*/
    if ( ( DHCP_DISCOVER != ucPktType )
         && ( DHCP_REQUEST != ucPktType )
         && ( DHCP_DECLINE != ucPktType )
         && ( DHCP_RELEASE != ucPktType ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_047);
        /*������Ϣ*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut Err DHCP packet type!" );
        return VOS_ERR;
    }

    /* ���ڿ���DHCP���Ʊ����Ƿ�Я��CheckSum */
    if (AM_IsNeedChecksum(AM_CHECKSUM_DHCP))
    {
        UDPS_SET_CHECK_SUM_ENABLE(&stNodeTemp);
    }

    ulDhcpGroupIndex = pstDhcpTmpCtrlBlk->usDhcpGroupIndex;
    if ( ulDhcpGroupIndex >= DHCPGRP_MAX_NUM )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_048);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut Err DHCP usDhcpGroupIndex!" );
        return VOS_ERR;
    }

    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulDhcpGroupIndex, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_049);
        *plSecondReturnCode = VOS_ERR;
        return VOS_ERR;
    }

    /*����Discover���͵���Ϣʱ���������������DHCP Server��Ҫ������DHCP Server����
    ����DHCP Server��ͨ������£�����DHCP Server������Ϣ*/

    stNodeTemp.ulFamily = AF_INET;/*add by cxf*/

    if ( DHCP_DISCOVER == ucPktType )
    {
        /* DHCP Server ip Ϊ���������һ�η���discover��Ϣ */
        if ( NULL == pstDhcpTmpCtrlBlk->ulSrvIp )
        {
            /*����DHCP Server��û������*/
            if ( ( 0 == stDhcpServer.aulPrimaryServerIp[0] ) )
            {
                DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_051);
                /*������Ϣ*/
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut apn non't configure DHCP Server!" );
                *plSecondReturnCode = VOS_ERR;
                return VOS_ERR;
            }
            /*��������DHCP Server ����������״̬����*/
            else if ( DHCP_SEVER_NORMAL == stDhcpServerStatus.ucPrimarySrvStatus )
            {
                /*����UDPͷ����*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*���ú������ͱ���*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut : 11 GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf ); /*Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/


            }
            else if ( DHCP_PRISRV_TEST_ON == stDhcpServerStatus.ucPrimarySrvTest )
            {
                /*����UDPͷ����*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*���ú������ͱ���*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 22 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );



                //pstDHCPCSrvGrp->ucPrimarySrvTest = DHCP_PRISRV_TEST_DOWN;
                ulRet = DHCPM_SetPrimarySrvTestByIndex(ulDhcpGroupIndex, DHCP_PRISRV_TEST_DOWN);
                if ( VOS_OK != ulRet )
                {
                    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_279);
                    return VOS_ERR;
                }
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );
                /* ��������ulRet��ֵ���д���������return */
            }

            /*�����˱�DHCP Server*/
            else if ( ( 0 != stDhcpServer.aulSecondaryServerIp[0] )&&( DHCP_SEVER_NORMAL == stDhcpServerStatus.ucSecondarySrvStatus ) )
            {
                /*����UDPͷ����*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulSecondaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*���ú������ͱ���*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulSecondaryServerIp[0];
                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 33 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );   /*Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
            }
            /*����������״̬��������,��ֻ������������������������*/
            else
            {
                /*����UDPͷ����*/
                stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
                /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
                }
                else
                {
                    stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
                }
                /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
                stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = stDhcpServer.aulPrimaryServerIp[0];
                stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
                stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
                stNodeTemp.pData = (CHAR*)&stCtrlEncap;
                stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

                /*���ú������ͱ���*/
                PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

                fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
                fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
                /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
                fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
                fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

                pstDhcpTmpCtrlBlk->ulSrvIp = stDhcpServer.aulPrimaryServerIp[0];

                //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
                DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_OutPut : 44 GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                             stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                             stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
                stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
                stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
                (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
                lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/

            }

        }
        /* ��ǰ���͹�discover��Ϣ�˴�Ϊ�ط� */
        else
        {
            /*����UDPͷ����*/
            stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
            /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
            if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
            {
                stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
            }
            else
            {
                stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
            }
            /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
            stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulSrvIp;
            stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
            stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
            stNodeTemp.pData =(CHAR*) &stCtrlEncap;
            stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

            /*���ú������ͱ���*/
            PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

            fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
            fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
            /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
            fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
            fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

            //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 55 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                         stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                         stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
            stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
            stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
            (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
            (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
            lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
        }

    }
    /*���ͷ�Discover����*/
    else
    {
        /* �����������ĵ����,���˷���Discover����,�������Ķ��Ѿ�ȷ���˷�������IP��ַ,
            ������ȥ�ж���Щ��������,�˴�ֻ�ж���ʱ���ƿ����Ƿ���ȷ�Ϳ����� */
        /*������DHCP Server*/
        /*���DHCP ��ʱ���ƿ��е�Server IP�Ȳ�������DHCP Server��IPҲ�����ڱ�DHCP Server��IP*/
        if ( ( pstDhcpTmpCtrlBlk->ulSrvIp != stDhcpServer.aulPrimaryServerIp[0] )
             && ( pstDhcpTmpCtrlBlk->ulSrvIp != stDhcpServer.aulSecondaryServerIp[0] ) )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_052);
            /*������Ϣ*/
            DHCPC_DebugPrint(PTM_LOG_DEBUG,
                         "\r\nDHCPC_OutPut not discover configure DHCP Server IP isn't DHCP Control block Server IP!" );
            *plSecondReturnCode = VOS_ERR;
            return VOS_ERR;
        }

        DHCPC_SetReNewDhcpServerIp(pstDhcpTmpCtrlBlk, &stDhcpServer, &stDhcpServerStatus);

        /*���췢��DHCP Server��Ϣ��UDPͷ����*/
        /* �����Դ��ַ��Щ����,ΪʲôҪ������ַ��?dhcp server��Ĵ����ַ��ת��ggsn��?
           ����Ҫ����·��?pf ����ʲô��dhcp�ı�������������?
        */
        stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulAgetIP;
        /* BEGIN: Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
        if (g_ucSoftParaDHCPKPN & ((UCHAR)0x02))
        {
            stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPS_PKT_PORTNO;
        }
        else
        {
            stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort = DHCPC_PKT_PORTNO;
        }
        /* END:   Modified for PN:AX4D10219 by jiahuidong, 2009/10/24 */
        stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr = pstDhcpTmpCtrlBlk->ulSrvIp;
        stNodeTemp.uaddrDst.stAddrDst.sin_usPort = DHCPS_PKT_PORTNO;
        stNodeTemp.ulVpnId = stDhcpServer.ulVpnIndex;
        stNodeTemp.pData = (CHAR*)&stCtrlEncap;
        stNodeTemp.ulDataLen = sizeof( FWD_TO_CTRL_HDR );

        PGP_MemZero( &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );

        fwd_set_ctrlhdr_vcpuid(&stCtrlEncap,0);
        fwd_set_ctrlhdr_vrfindex(&stCtrlEncap,stDhcpServer.ulVpnIndex);
        /*fwd_set_ctrlhdr_subindex(&stCtrlEncap,ulSubIndex);*/   /* Deleted by heguangwei 65937 at 2008-10-27 V900R007C01B031 for AX4D05664 */
        fwd_set_ctrlhdr_msgcode(&stCtrlEncap,(ULONG)ucPktType);
        fwd_set_ctrlhdr_moduleid(&stCtrlEncap,MID_DHCPC);

        //GTPC_DumpMessage(pMBuf->stDataBlockDescriptor.pucData,pMBuf->ulTotalDataLength);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n 66 DHCPC_OutPut :  GTPC_DumpMessage %u ; %d ; %u ; %d ; %u ; %u ;" ,
                     stNodeTemp.uaddrSrc.stAddrSrc.sin_stAddr.s_ulAddr,stNodeTemp.uaddrSrc.stAddrSrc.sin_usPort,stNodeTemp.uaddrDst.stAddrDst.sin_stAddr.s_ulAddr,
                     stNodeTemp.uaddrDst.stAddrDst.sin_usPort,stNodeTemp.ulVpnId,stCtrlEncap.ulVcpuId );
        stNodeTemp.uaddrDst.stAddrDst.sin_chFamily = AF_INET;
        stNodeTemp.uaddrSrc.stAddrSrc.sin_chFamily = AF_INET;
        (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrSrc.stAddrSrc), sizeof(SOCKADDRIN_S));
        (VOID)UDPS_ConvertToSockAddr(&(stNodeTemp.uaddrDst.stAddrDst), sizeof(SOCKADDRIN_S));
        lRetCode = UDPS_DataHandle ( &stNodeTemp, pMBuf );  /* Deleted by hourufeng &stCtrlEncap,sizeof( FWD_TO_CTRL_HDR ) );*/
    }

    /*Ϊ�������plSecondReturnCode��ֵ��ֻҪ��һ��DHCP Server��Ϣ�ɹ����ò�����ֵ����ΪVOS_OK*/
    if ( ( VOS_OK != lRetCode ) && ( VOS_OK != *plSecondReturnCode ) )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_053);
        *plSecondReturnCode = VOS_ERR;
        return VOS_ERR ;
    }
    else
    {
        *plSecondReturnCode = VOS_OK;
    }

    return VOS_OK;
}
VOID DHCPC_ConstructPhyAddr( DHCPC_TEMPCTRLBLK* pstTempCtrlBlk, UCHAR* szChaddr )
{
    int ii = 0;
    USHORT usGroup = 0;
    GTP_IMSI_S stImsi;
    ULONG ulNetOrderDHCPCtlIdx = 0;

    if (NULL == pstTempCtrlBlk)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_054);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ConstructPhyAddr index invalid!" );
        VOS_Assert( 0 );
        return ;
    }

    if ( NULL == szChaddr )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_055);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\nDHCPC_ConstructPhyAddr szChaddr is null!" );
        VOS_Assert( 0 );
        return ;
    }

    usGroup = (USHORT)CRM_GetSelfGroupId();
    if (0 == usGroup)
    {
        return;
    }

    usGroup = VOS_HTONS(usGroup);
    ulNetOrderDHCPCtlIdx = VOS_HTONL(pstTempCtrlBlk->ulDHCPCtlIdx);

    VOS_MemSet(&stImsi,0,sizeof(GTP_IMSI_S));
    VOS_MemCpy(&stImsi,pstTempCtrlBlk->aulIMSI, 2 * sizeof(ULONG));

    for ( ii = 0; ii < DHCP_ETHERNETHARDWARELEN; ii++ )
    {
        szChaddr[ii] = 0;
    }

    if((VOS_NULL_DWORD == pstTempCtrlBlk->aulIMSI[0])
        &&(VOS_NULL_DWORD == pstTempCtrlBlk->aulIMSI[1]))
    {
         /*���+teidc*/
        VOS_MemCpy((UCHAR*)( szChaddr ),&(usGroup),sizeof(USHORT));
        VOS_MemCpy( ( UCHAR* )( szChaddr+2 ),&(ulNetOrderDHCPCtlIdx),sizeof( ULONG ) );
    }
    else if (g_ucSoftParaDHCPKPN & ((UCHAR)0x04))
    {
        /*����IMSI �Ĵ洢�ṹ������12λ����*/
        *(szChaddr) = ((stImsi.MNC2 << 4  ) | (stImsi.MNC1 ));
        *(szChaddr+1) = ((stImsi.MSIN2 << 4 ) | (stImsi.MSIN1 ));
        *(szChaddr+2) = ((stImsi.MSIN4 << 4 ) | (stImsi.MSIN3 ));
        *(szChaddr+3) = ((stImsi.MSIN6 << 4 ) | (stImsi.MSIN5 ));
        *(szChaddr+4) = ((stImsi.MSIN8 << 4 ) | (stImsi.MSIN7 ));
        *(szChaddr+5) = ((stImsi.MSIN10 << 4 ) | (stImsi.MSIN9 ));
    }
    else
    {
        /*���+teidc*/
        VOS_MemCpy((UCHAR*)( szChaddr ),&(usGroup),sizeof(USHORT));
        VOS_MemCpy( ( UCHAR* )( szChaddr+2 ),&(ulNetOrderDHCPCtlIdx),sizeof( ULONG ) );
    }
    return;
}
/*****************************************************************************
 �� �� ��  : DHCPC_GetDhcpCtrlBlk
 ��������  : ��̬����DHCP���ƿ�ṹ
 �������  : DHCPC_CTRLBLK **ppstDhcp_CtrlBlk
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��11��21��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_GetDhcpCtrlBlk( DHCPC_CTRLBLK **ppstDhcpCtrlBlk )
{
    if ( NULL == ppstDhcpCtrlBlk )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_056);
        return VOS_ERR;
    }

    *ppstDhcpCtrlBlk = DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK ) );
    if ( NULL == ( *ppstDhcpCtrlBlk ) )
    {
        return VOS_ERR;
    }

    PGP_MemZero( *ppstDhcpCtrlBlk, sizeof( DHCPC_CTRLBLK ) );
    return VOS_OK;
}

VOID DHCPC_FreeDhcpCtrlBlk( ULONG ulCtrlBlkIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex )
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK * pstPreDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK * pstCurDhcpcCtlBlk = NULL;

    ulHashKey = DHCPC_GetCtlBlkHashKey( ulCtrlBlkIndex );

    if ( NULL == g_pstDhcpcCtrlBlkRec[ulHashKey] )
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_FreeDhcpCtrlBlk g_pstDhcpcCtrlBlkRec[ulHashKey] is null!" );
        return;
    }

    /*���Ҫɾ�����ǵ�һ�����*/
    pstCurDhcpcCtlBlk = g_pstDhcpcCtrlBlkRec[ulHashKey];
    if (pstCurDhcpcCtlBlk->ulTEIDC == ulTEIDC)
    {
        //DHCPC_Delete_BackupChain(ulCtrlBlkIndex);
        g_pstDhcpcCtrlBlkRec[ulHashKey] = pstCurDhcpcCtlBlk->pstNextNode;
        DHCP_Free( DHCPC_HANDLE, pstCurDhcpcCtlBlk );
        pstCurDhcpcCtlBlk = NULL;
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n--> DHCPC_FreeDhcpCtrlBlk ulCtrlBlkIndex OK" );
        return;
    }

    pstPreDhcpcCtlBlk = pstCurDhcpcCtlBlk;
    pstCurDhcpcCtlBlk = pstCurDhcpcCtlBlk->pstNextNode;

    /* ����HASHKEY��ȵĿ��ƿ�*/
    while ( NULL != pstCurDhcpcCtlBlk )
    {
        /* V1�û�,���TEIDC������ҵ���Ҫɾ���Ŀ��ƿ�*/
        if (pstCurDhcpcCtlBlk->ulTEIDC == ulTEIDC)
        {
            //DHCPC_Delete_BackupChain(ulCtrlBlkIndex);
            pstPreDhcpcCtlBlk->pstNextNode = pstCurDhcpcCtlBlk->pstNextNode;
            DHCP_Free( DHCPC_HANDLE, pstCurDhcpcCtlBlk );
            pstCurDhcpcCtlBlk = NULL;
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n--> DHCPC_FreeDhcpCtrlBlk ulCtrlBlkIndex OK" );
            return;
        }

        pstPreDhcpcCtlBlk = pstCurDhcpcCtlBlk;
        pstCurDhcpcCtlBlk = pstCurDhcpcCtlBlk->pstNextNode;
    }

    /*û���ҵ�Ҫɾ���Ľ��*/
    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_FreeDhcpCtrlBlk there is no DhcpcCtrlBlkRec!" );
    return;
}


VOID DHCPC_EncapBackBlkByCtrlBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpCtrlBlk,
                                        DHCPC_BACK_BLK_S *pstDhcpBackBlk)
{
    pstDhcpBackBlk->aulMSISDN[0] = pstDhcpCtrlBlk->aulMSISDN[0];
    pstDhcpBackBlk->aulMSISDN[1] = pstDhcpCtrlBlk->aulMSISDN[1];

    pstDhcpBackBlk->aulIMSI[0] = pstDhcpCtrlBlk->aulIMSI[0];
    pstDhcpBackBlk->aulIMSI[1] = pstDhcpCtrlBlk->aulIMSI[1];

    pstDhcpBackBlk->aulIMEI[0] = pstDhcpCtrlBlk->aulIMEI[0];
    pstDhcpBackBlk->aulIMEI[1] = pstDhcpCtrlBlk->aulIMEI[1];

    pstDhcpBackBlk->ulLease = pstDhcpCtrlBlk->ulLease;
    pstDhcpBackBlk->ulTimeStamp = pstDhcpCtrlBlk->ulTimeStamp;
    pstDhcpBackBlk->ulTEIDC = pstDhcpCtrlBlk->ulTEIDC;
    pstDhcpBackBlk->ulPDPIndex = pstDhcpCtrlBlk->ulPDPIndex;
    pstDhcpBackBlk->usVPNIndex = pstDhcpCtrlBlk->usVPNIndex;
    pstDhcpBackBlk->usPoolIndex = pstDhcpCtrlBlk->usPoolIndex;
    pstDhcpBackBlk->usServerGrpIndex = pstDhcpCtrlBlk->usServerGrpIndex;
    pstDhcpBackBlk->usApnIndex = pstDhcpCtrlBlk->usApnIndex;
    pstDhcpBackBlk->ucLAPNo = pstDhcpCtrlBlk->ucLAPNo;
    pstDhcpBackBlk->ucRandomNo = pstDhcpCtrlBlk->ucRandomNo;
    pstDhcpBackBlk->ucRole = pstDhcpCtrlBlk->ucRole;
    pstDhcpBackBlk->usDhcpStatus = pstDhcpCtrlBlk->usDhcpStatus;

    if (LAP_IPV4 == ucIpType)
    {
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulAgentIpAddr = pstDhcpCtrlBlk->aulAgentIpAddr[0];
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulUserIpAddr = pstDhcpCtrlBlk->aulUserIpAddr[0];
        pstDhcpBackBlk->unBakInfo.stDhcpv4.ulServerIp = pstDhcpCtrlBlk->aulSrvIp[0];
    }
    else
    {
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT1 = pstDhcpCtrlBlk->ulT1;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT2 = pstDhcpCtrlBlk->ulT2;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucLeaseStatus = pstDhcpCtrlBlk->ucLeaseStatus;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucResource = pstDhcpCtrlBlk->ucResource;
        pstDhcpBackBlk->unBakInfo.stDhcpv6.ucCurrentServer = pstDhcpCtrlBlk->ucCurrentServer;

        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aulAgentIpAddr, pstDhcpCtrlBlk->aulAgentIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aulUserIpAddr, pstDhcpCtrlBlk->aulUserIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpBackBlk->unBakInfo.stDhcpv6.aucSiDuid, pstDhcpCtrlBlk->aucSiDuid,
                    sizeof(UCHAR) * DHCPV6C_MAX_DUID_LEN);
    }

    return;
}


VOID DHCPC_FillCtrlBlkByBackBlk(UCHAR ucIpType, DHCPC_CTRLBLK *pstDhcpCtrlBlk,
                                        DHCPC_BACK_BLK_S *pstDhcpBackBlk)
{
    pstDhcpCtrlBlk->aulMSISDN[0] = pstDhcpBackBlk->aulMSISDN[0];
    pstDhcpCtrlBlk->aulMSISDN[1] = pstDhcpBackBlk->aulMSISDN[1];

    pstDhcpCtrlBlk->aulIMSI[0] = pstDhcpBackBlk->aulIMSI[0];
    pstDhcpCtrlBlk->aulIMSI[1] = pstDhcpBackBlk->aulIMSI[1];

    pstDhcpCtrlBlk->aulIMEI[0] = pstDhcpBackBlk->aulIMEI[0];
    pstDhcpCtrlBlk->aulIMEI[1] = pstDhcpBackBlk->aulIMEI[1];

    pstDhcpCtrlBlk->ulTEIDC = pstDhcpBackBlk->ulTEIDC;
    pstDhcpCtrlBlk->ulLease = pstDhcpBackBlk->ulLease;
    pstDhcpCtrlBlk->ulTimeStamp = pstDhcpBackBlk->ulTimeStamp;
    pstDhcpCtrlBlk->ulPDPIndex = pstDhcpBackBlk->ulPDPIndex;
    pstDhcpCtrlBlk->usVPNIndex = pstDhcpBackBlk->usVPNIndex;
    pstDhcpCtrlBlk->usPoolIndex = pstDhcpBackBlk->usPoolIndex;
    pstDhcpCtrlBlk->usServerGrpIndex = pstDhcpBackBlk->usServerGrpIndex;
    pstDhcpCtrlBlk->usApnIndex = pstDhcpBackBlk->usApnIndex;
    pstDhcpCtrlBlk->ucLAPNo = pstDhcpBackBlk->ucLAPNo;
    pstDhcpCtrlBlk->ucRandomNo = pstDhcpBackBlk->ucRandomNo;
    pstDhcpCtrlBlk->ucRole = pstDhcpBackBlk->ucRole;
    pstDhcpCtrlBlk->ucIpType = ucIpType;

    if (LAP_IPV4 == ucIpType)
    {
        pstDhcpCtrlBlk->aulAgentIpAddr[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulAgentIpAddr;
        pstDhcpCtrlBlk->aulUserIpAddr[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulUserIpAddr;
        pstDhcpCtrlBlk->aulSrvIp[0] = pstDhcpBackBlk->unBakInfo.stDhcpv4.ulServerIp;
        pstDhcpCtrlBlk->usDhcpStatus = DHCPC_STATE_BOUND;    /* �����ؽ���ֱ�Ӹ���Ϊ��̬,Ŀǰ��Ϊʱ�������,���ܻ��ؽ�һЩ����̬�Ŀ��ƿ� */
    }
    else
    {
        pstDhcpCtrlBlk->ulT1 = pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT1;
        pstDhcpCtrlBlk->ulT2 = pstDhcpBackBlk->unBakInfo.stDhcpv6.ulT2;
        pstDhcpCtrlBlk->ucLeaseStatus = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucLeaseStatus;
        pstDhcpCtrlBlk->ucResource = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucResource;
        pstDhcpCtrlBlk->ucCurrentServer = pstDhcpBackBlk->unBakInfo.stDhcpv6.ucCurrentServer;
        pstDhcpCtrlBlk->usDhcpStatus = DHCPV6C_STATE_BOUND;  /* �����ؽ���ֱ�Ӹ���Ϊ��̬,Ŀǰ��Ϊʱ�������,���ܻ��ؽ�һЩ����̬�Ŀ��ƿ� */

        VOS_MemCpy(pstDhcpCtrlBlk->aulAgentIpAddr, pstDhcpBackBlk->unBakInfo.stDhcpv6.aulAgentIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpCtrlBlk->aulUserIpAddr, pstDhcpBackBlk->unBakInfo.stDhcpv6.aulUserIpAddr,
                    sizeof(ULONG) * LAP_IP_ULONG_NUM);
        VOS_MemCpy(pstDhcpCtrlBlk->aucSiDuid, pstDhcpBackBlk->unBakInfo.stDhcpv6.aucSiDuid,
                    sizeof(UCHAR) * DHCPV6C_MAX_DUID_LEN);
        DHCP_MemZero(pstDhcpCtrlBlk->aulMainDnsAddr, sizeof(ULONG) * 4);
        DHCP_MemZero(pstDhcpCtrlBlk->aulSecdDnsAddr, sizeof(ULONG) * 4);
    }

    /* ��ʼ��ʣ�ಿ�� */
    pstDhcpCtrlBlk->pTmpDhcpCtrlBlkPtr = NULL;
    pstDhcpCtrlBlk->ulDHCPCtxIdx = pstDhcpBackBlk->ulTEIDC;
    pstDhcpCtrlBlk->ulTmpVar = 0;
    pstDhcpCtrlBlk->usSeqNum = 0;
    pstDhcpCtrlBlk->ucUserType = 0;
    pstDhcpCtrlBlk->ucUser = 0;
    pstDhcpCtrlBlk->ucCurSvrSendCount = 0;
    pstDhcpCtrlBlk->ucTotalSendCount = 0;
    pstDhcpCtrlBlk->ucResendTimeout = 0;
    pstDhcpCtrlBlk->ucWaitRspTimeOutNum = 0;
    pstDhcpCtrlBlk->ucAgingFlag = 0;
    pstDhcpCtrlBlk->ucCause = DHCPV6C_CAUSE_DEFAULT;

    return ;
}
ULONG DHCPC_BackupProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC)
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstDhcpCtrlBlk = NULL;

    /*��ڲ������*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_059);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup err1!" );
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "iptype=%d teidc=0x%x!", ucIpType, ulTEIDC);

    if ( (LAP_IPV4 != ucIpType) && (LAP_IPV6 != ucIpType) )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAK_IPTYPEERR);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "In DHCPC_BackupProc input iptype err! iptype:%d", ucIpType);
        return VOS_ERR;
    }

    /* ��ȡdhcp���ƿ� */
    if ( LAP_IPV4 == ucIpType )
    {
        /*dhcp���ƿ�����:v0�û������������������;V1�û��������TEIDC*/
        pstDhcpCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
        if ( NULL == pstDhcpCtrlBlk )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_060);
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup for Dhcpv4 err2!" );
            return VOS_ERR;
        }
    }
    else
    {
        pstDhcpCtrlBlk = NULL;

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAK_IPV6);

        /*dhcp���ƿ�����:v0�û������������������;V1�û��������TEIDC*/
        ulRet = DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstDhcpCtrlBlk);
        if ( VOS_OK != ulRet )
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "master DhcpCtrlBlk backup for Dhcpv6 err2 ulTEIDC:%u!",ulTEIDC );
            return VOS_ERR;
        }
    }

    /* ��װ���ݿ� */
    DHCPC_EncapBackBlkByCtrlBlk(ucIpType, pstDhcpCtrlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));
    *ppbuff += sizeof(DHCPC_BACK_BLK_S);

    /* ���� */
    return VOS_OK;
}


ULONG DHCPC_BkRestoreProcforV4( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    ULONG ulRetValue = 0;
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK *pstCtrlBlk = NULL;

    /*���ݿ��ƿ���������HASHKEY*/
    ulHashKey = DHCPC_GetCtlBlkHashKey( ulTEIDC );
    /*dhcp���ƿ�����:v0�û������������������;V1�û��������TEIDC*/
    pstCtrlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
    if ( NULL != pstCtrlBlk )
    {
        /*�����ǰҪ���ݵ�Ŀ����Ʋ�Ϊ�գ������ͷ��ڴ棬���������·���*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "slave DhcpCtrlBlk backup err3!" );
        DHCPC_FreeDhcpCtrlBlk( ulTEIDC, pstCtrlBlk->ulTEIDC, pstCtrlBlk->ucUser, pstCtrlBlk->ulPDPIndex);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_317);
    }

    ulRetValue = DHCPC_GetDhcpCtrlBlk( &pstDhcpcCtlBlk );
    if ( VOS_OK != ulRetValue )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_062);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "get null DhcpCtrlBlk!" );
        return VOS_ERR;
    }

    DHCPC_FillCtrlBlkByBackBlk(LAP_IPV4, pstDhcpcCtlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));

    pstDhcpcCtlBlk->ulTmpVar = 0;

    /*���½����뵽��һ��λ��*/
    pstDhcpcCtlBlk->pstNextNode = g_pstDhcpcCtrlBlkRec[ulHashKey];
    g_pstDhcpcCtrlBlkRec[ulHashKey] = pstDhcpcCtlBlk;

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "ok!" );
    return VOS_OK;
}


ULONG DHCPC_BkRestoreProcforV6( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstCtrlBlk = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE);

    /* ״̬����,�����б��� */
    if (DHCPV6C_STATE_BOUND != ((DHCPC_BACK_BLK_S *)(*ppbuff))->usDhcpStatus)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_STAT_ERR);
        DHCPC_DebugPrint(PTM_LOG_INFO, "\r\n state (%u) !", ((DHCPC_BACK_BLK_S *)(*ppbuff))->usDhcpStatus);
        //return VOS_ERR; ��ʱɾ��
    }

    (VOID)DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstCtrlBlk);
    if ( NULL != pstCtrlBlk )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_RENEW);
        /*�����ǰҪ���ݵ�Ŀ����Ʋ�Ϊ�գ������ͷ��ڴ棬���������·���*/
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\npstCtrlBlk is not null ulTEDIC:%u!", ulTEIDC );

        /* ɾ�����ƿ鶨ʱ�� */
        if ( CRM_GetSpuWorkModeOfSelfGroup() == CRM_BKUP_N_PLUS_1 )
        {
            ulRet = DHCPV6C_StopLeaseTimer(pstCtrlBlk);
            if ( VOS_OK != ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_STOPTIMERR);
            }
        }


        ulRet = DHCPC_FreeDhcpcContext(LAP_IPV6, pstCtrlBlk->ulTEIDC);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_DELEERR);
            return VOS_ERR;
        }
    }

    ulRet = DHCPC_MallocDhcpcContext(LAP_IPV6, ((DHCPC_BACK_BLK_S *)(*ppbuff))->ulTEIDC, &pstCtrlBlk);
    if ( VOS_OK != ulRet )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_CRTERR);
        return VOS_ERR;
    }

    DHCPC_FillCtrlBlkByBackBlk(LAP_IPV6, pstCtrlBlk, (DHCPC_BACK_BLK_S *)(*ppbuff));

    /* ��ʱ���ؽ� */
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)CRM_GetSelfLogicSlotID()))
    {
        /* ����Ǳ���,����Ҫ�ؽ���ʱ�� */
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "ok!" );
        return VOS_OK;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_1);

    /* ���е��˴���2�����:
     * 1��N+1 Standby��ΪActive�󡣸õ������еĶ�ʱ�����ڴ˴��ؽ���
     * 2��1+1 Standby��ΪActive��,��Ҫ�������ڱ���ΪStandby״̬ʱ���ܵı�����Ϣ,
     *    ��Ϊ��ʱ�Ѿ���Ϊ����,��Ҫ������ʱ����
     */
    ulRet = DHCPV6C_TimerRestoreProc(pstCtrlBlk);
    if ( VOS_OK != ulRet )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_TIMERR);

        pstCtrlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;

        stPreResult.pstDhcpcContext = pstCtrlBlk;
        stPreResult.pMsg = NULL;
        stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

        /* ����״̬�� */
        DHCPV6C_RunFsm(&stPreResult);
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "ulRet=%u!", ulRet );
    return ulRet;
}
ULONG DHCPC_BKRestoreProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC )
{
    ULONG ulRetValue = 0;

    /*��ڲ������*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_058);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n master DhcpCtrlBlk backup err1!" );
        return VOS_ERR;
    }

    if ( (LAP_IPV4 != ucIpType) && (LAP_IPV6 != ucIpType) )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKRESTORE_IPTYPEERR);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n In DHCPC_BKRestoreProc input iptype err! iptype:%d", ucIpType);
        return VOS_ERR;
    }

    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_315);

    if (LAP_IPV4 == ucIpType)
    {
        ulRetValue = DHCPC_BkRestoreProcforV4(ppbuff, ucIpType, ulTEIDC);
        if ( VOS_OK != ulRetValue )
        {
            /* ���� */
        }
    }
    else
    {
        ulRetValue = DHCPC_BkRestoreProcforV6(ppbuff, ucIpType, ulTEIDC);
        if ( VOS_OK != ulRetValue )
        {
            /* ���� */
        }
    }

    /* ���ܳɹ�ʧ�ܶ�Ҫ����ƫ�� */
    *ppbuff += sizeof(DHCPC_BACK_BLK_S);

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n slave DhcpCtrlBlk backup succ!" );

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_BKDeleteProc
 ��������  : DHCPCģ����ƿ��ڱ���ı���ɾ���������ӱ��ݽṹ��ȡ�������ݵ�DHCP
             ���ƿ����ݣ����������DHCP���ƿ�������
 �������  : char **ppbuff, ULONG ulIndex, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��26��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��07��31��
    ��    ��   : caopu
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_BKDeleteProc( UCHAR ucIpType, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex )
{
    ULONG ulRet = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;

    /*dhcp���ƿ�����:v0�û������������������;V1�û��������TEIDC*/
    DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_318);

    if ( LAP_IPV4 == ucIpType )
    {
        pstDhcpcCtlBlk = (DHCPC_CTRLBLK *)DHCPC_CalcCtlBlkHashValue(ulTEIDC, ulTEIDC);
        if ( NULL == pstDhcpcCtlBlk )
        {
            DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_066);
            return VOS_ERR;
        }

        /*�ͷſ��ƿ��ڴ棬ɾ���ڵ�*/
        DHCPC_FreeDhcpCtrlBlk( ulTEIDC, ulTEIDC, ucUser, ulPDPIndex );
    }

    if ( LAP_IPV6 == ucIpType )
    {
        pstDhcpcCtlBlk = NULL;

        ulRet = DHCPC_QueryDhcpcContext(LAP_IPV6, ulTEIDC, &pstDhcpcCtlBlk);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKDEL_NOTFOUND);
            return VOS_ERR;
        }

        ulRet = DHCPC_FreeDhcpcContext(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BAKDEL_FREEFAIL);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

VOID DHCPC_Delete_BackupChain(ULONG ulCtrlBlkIndex)
{
    return ;
}

/*****************************************************************************
 �� �� ��  : DHCPC_NotifyBKUpdate
 ��������  : ֪ͨCKP���±��ݵ�dhcp���ƿ�
 �������  : DHCPC_CTRLBLK *
 �������  : ��
 �� �� ֵ  : VOS_OK  ��������
             VOS_ERR ֪ͨ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��07��22��
    ��    ��   : jixiaoming
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_NotifyBKUpdate(ULONG ulTeidc)
{
    ULONG ulRet = 0;
    SDB_GSPU_CONTEXT_S * pstContext = NULL;

    /* ��ȡ1�������� */
    pstContext = DHCPC_GetOneContextByteidc(ulTeidc);
    if (NULL == pstContext)
    {
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_262);
        return VOS_ERR;
    }

    /* ���ýӿ�֪ͨckp����dhcp���ƿ鱸�� */
    ulRet = AM_USM_NotifyBackupByIndex(pstContext->ulGspuBdIndex, SDB_UPDATEVERNOTCHANGE_BACKUP);
    if (SDB_SUCCESS != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_NotifyBKUpdate: call AM_USM_NotifyBackupByIndex failed!! ulRet = %u", ulRet);
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_261);
        return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPC_GetDiffTimeToCur(ULONG ulStampTime)
{
    ULONG ulCurTimeInSec = 0;

    /* ��ȡ��ǰʱ�� */
    (VOID)PGP_TmNowInSec(&ulCurTimeInSec);
    if ( ulCurTimeInSec < ulStampTime )
    {
        /* ʱ�䷭ת */
        return ulCurTimeInSec + (0xFFFFFFFF - ulStampTime);
    }
    else
    {
        return ulCurTimeInSec - ulStampTime;
    }
}


ULONG DHCPV6C_TimerRestoreProc(DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulRet = VOS_OK;
    ULONG ulT1 = 0;
    ULONG ulT2 = 0;
    ULONG ulDiffTime = 0;

    ulDiffTime = DHCPC_GetDiffTimeToCur(pstDhcpcCtlBlk->ulTimeStamp);

    ulT1 = DHCPV6C_GetT1(pstDhcpcCtlBlk);
    ulT2 = DHCPV6C_GetT2(pstDhcpcCtlBlk);

    if ( DHCPC_INFINITY_TIME == pstDhcpcCtlBlk->ulLease )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_NOTRESTORE);
        pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;
        return VOS_OK;
    }

    /*���ȸ���T1���ж϶�ʱ������*/
    /*T1>���������쳣�����Ӧ�����ͷ�*/
    if (ulT1 >= pstDhcpcCtlBlk->ulLease)
    {
        /* �ؽ���Լ��ʱ�� */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM);
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }
    else if (ulT1 > ulDiffTime)
    {
        /* �ؽ�T1��ʱ�� */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T1TIM);
        ulRet = DHCPV6C_T1TimerRestoreProc(ulT1, ulDiffTime, pstDhcpcCtlBlk);
    }
    /*��T1������T2�ж϶�ʱ������*/
    /*T2>���������쳣�����T2<��Լʱ��*/
    else if ((ulT2 >= pstDhcpcCtlBlk->ulLease) || (ulT2 <= ulDiffTime))
    {
        /* �ؽ���Լ��ʱ�� */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM);
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }
    else
    {
        /* �ؽ�T2��ʱ�� */
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T2TIM);
        ulRet = DHCPV6C_T2TimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);
    }

    return ulRet;
}


ULONG DHCPV6C_T1TimerRestoreProc(ULONG ulT1, ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulRet = 0;
    ULONG ulTimerInterval = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulTimerInterval = ulT1 - ulDiffTime;
    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_T1;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_RENEW, ulTimerInterval, DHCPC_TimerCallBack);
    return ulRet;
}


ULONG DHCPV6C_T2TimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG ulT2 = 0;
    ULONG ulRet = 0;
    ULONG ulTimerInterval = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulT2 = DHCPV6C_GetT2(pstDhcpcCtlBlk);

    if ( ulT2 <= ulDiffTime )
    {
        /* �����ǰʱ�䵽T1��ʱ��ʱ����Ѿ�����T2����������Լ��ʱ�� */
        ulRet = DHCPV6C_LeaseExpireTimerRestoreProc(ulDiffTime, pstDhcpcCtlBlk);

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_T2EXTIM);

        return ulRet;
    }

    /* �ؽ�T2��ʱ�� */
    ulTimerInterval = ulT2 - ulDiffTime;

    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_T2;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_RENEW, ulTimerInterval, DHCPC_TimerCallBack);
    return ulRet;
}


ULONG DHCPV6C_LeaseExpireTimerRestoreProc(ULONG ulDiffTime, DHCPC_CTRLBLK *pstDhcpcCtlBlk)
{
    ULONG   ulRet = 0;
    ULONG   ulTimerInterval = 0;
    ULONG   ulLease = 0;

    if ( NULL == pstDhcpcCtlBlk )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    ulLease = pstDhcpcCtlBlk->ulLease;

    if (ulLease <= ulDiffTime)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIMRES_EXTIM_ERR);

        /* ����ԭ��ֵ */
        pstDhcpcCtlBlk->ucCause = DHCPV6C_CAUSE_LEASE_EXPIRE;

        /* ��Լ����,��Ҫ�ͷŵ�ַ,�˴����ش���,����㴦�� */
        return VOS_ERR;
    }

    ulTimerInterval = ulLease - ulDiffTime;
    pstDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_WAIT_LEASE;

    ulRet = DHCPC_StartTimer(pstDhcpcCtlBlk->ucIpType, pstDhcpcCtlBlk->ulTEIDC,
                                DHCPV6C_EV_TIMER_LEASE_EXPIRE, ulTimerInterval, DHCPC_TimerCallBack);

    return ulRet;
}


VOID DHCPV6C_SendtoTimRestoreforSpud(ULONG ulHashValue)
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SENDTIM_SPUDRESTORE);

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_TIM_RESTORE;
    stInnerMsg.ulCtlBlockHashValue = ulHashValue;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_TIM_RESTORE,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}


VOID DHCPV6C_TimerRestoreForSpud(DHCPC_INNER_MSG_S *pstInnerMsg)
{
    ULONG ulRet = 0;
    ULONG ulHashValue = 0;
    ULONG ulScanNum = 0;
    ULONG ulReleaseNum = 0;
    DHCPC_CTRLBLK *pstDhcpcCtlBlk = NULL;
    DHCPC_CTRLBLK *pstTmpDhcpcCtlBlk = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    if ( NULL == pstInnerMsg )
    {
        VOS_DBGASSERT(0);
        return;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE_ENTER);

    for ( ulHashValue = pstInnerMsg->ulCtlBlockHashValue; ulHashValue < DHCPC_CTRLBLK_HASH_TABLE_SIZE ; ulHashValue++ )
    {
        pstDhcpcCtlBlk = g_pstDhcpcIpv6CtrlBlkRec[ulHashValue];
        while ( NULL != pstDhcpcCtlBlk )
        {
            ulScanNum++;
            if ( ulScanNum % 5000 == 0 )/* ���أ������ú� */
            {
                DHCPV6C_SendtoTimRestoreforSpud(ulHashValue);
                return;
            }
            /* ���Ҷ�ʱ���Ƿ��Ѿ����� */
            ulRet = DHCPC_IsTimNodeExist(LAP_IPV6, pstDhcpcCtlBlk->ulTEIDC);
            if ( VOS_OK == ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_HASEXIST);
                /* ��ʱ���Ѵ�������Ҫ�ٴ��� */
                pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;

                continue;
            }

            /* �ָ���ʱ�� */
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE);

            pstTmpDhcpcCtlBlk = pstDhcpcCtlBlk;
            pstDhcpcCtlBlk = pstDhcpcCtlBlk->pstNextNode;
            ulRet = DHCPV6C_TimerRestoreProc(pstTmpDhcpcCtlBlk);
            if ( VOS_OK != ulRet )
            {
                DHCPV6C_DBGCNT_ADD(E_DHCPV6C_TIME_SPUDRESTORE_FAIL);

                pstTmpDhcpcCtlBlk->ucLeaseStatus = DHCPV6C_LEASE_STATE_BUTT;

                stPreResult.pstDhcpcContext = pstTmpDhcpcCtlBlk;
                stPreResult.pMsg = NULL;
                stPreResult.enEvent = DHCPV6C_EV_IP_RELEASE;

                /* ����״̬�� */
                DHCPV6C_RunFsm(&stPreResult);

                /* �˴�����һ��Ҫ��!! */
                ulReleaseNum++;
                if (ulReleaseNum % 2 == 0)
                {
                    DHCPV6C_SendtoTimRestoreforSpud(ulHashValue);
                    return;
                }

                continue;
            }
        }
    }
}


VOID DHCPC_BoardStatChgTimerOutCallBack(VOID *pArg)
{
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_2);
    g_ulDhcpcBoardStateChgDelayTimerId = 0;

    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup((UCHAR)CRM_GetSelfLogicSlotID()))
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_4);

        /* �����ǰ״̬Ϊ���壬�����������ʱ���ȴ� */
        (VOID)DHCPC_StartLeaseRebuildWaitTimer();
        return;
    }

    /* ��ʼ��Լ��ʱ���ؽ� */
    DHCPV6C_SendtoTimRestoreforSpud(0);

    return;
}


ULONG DHCPC_StartLeaseRebuildWaitTimer()
{
    ULONG ulRet = VOS_ERR;

    if (g_ulDhcpcBoardStateChgDelayTimerId != 0)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* ����10s��ʱ��,10s��ʼ����s */
    ulRet = PGP_Timer_Create(DHCPC_SELF_CSI,
                               DHCPC_MSG_TYPE_TIMER,
                               10 * 1000,
                               DHCPC_BoardStatChgTimerOutCallBack,
                               NULL,
                               &g_ulDhcpcBoardStateChgDelayTimerId,
                               VOS_TIMER_NOLOOP);
    if (VOS_OK != ulRet)
    {
        VOS_DBGASSERT(0);
        DHCPC_DebugPrint(PTM_LOG_ERR, "call PGP_Timer_Create fail! ulRet=0x%x", ulRet);
        return ulRet;
    }

    return VOS_OK;
}
VOID DHCPV6C_SendInnerMsgForBoardStateChange()
{
    DHCPC_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE;

    (VOID)DHCPC_SendRtMsg(DHCPC_SELF_CSI, DHCPC_MSG_TYPE_SELF, DHCPC_INNER_MSGCODE_BOARD_STATE_CHANGE,
                          (UCHAR *)&stInnerMsg, sizeof(DHCPC_INNER_MSG_S));

    return;
}


VOID DHCPV6C_ProcBoardStateChangeMsg()
{
    ULONG ulRet = VOS_ERR;

    if (0 != g_ulDhcpcBoardStateChgDelayTimerId)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_CNT_TRC_3);
        return;
    }

    ulRet = DHCPC_StartLeaseRebuildWaitTimer();
    if (VOS_OK != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "call DHCPC_StartLeaseRebuildWaitTimer fail! ulRet=0x%x", ulRet);
    }
}



VOID DHCPC_BoardStateChgProc()
{
    DHCPV6C_SendInnerMsgForBoardStateChange();

    return;
}

VOID DHCPC_StateOfBoardChgCallback( CRM_SPUSTATE_CHG_ENUM enEvent, UCHAR ucGroupID, UCHAR ucSlotID, UCHAR ucCpuID, UCHAR ucSGIndex)
{
    if (ucGroupID != CRM_GetSelfGroupId())
    {
        return;
    }

    if (ucSlotID != CRM_GetSelfLogicSlotID())
    {
        return;
    }

    DHCPC_DebugPrint(PTM_LOG_INFO, "enEvent=%u ucGroupID=%d ucSlotID=%d ucCpuID=%d = %d!",
                enEvent, ucGroupID, ucSlotID, ucCpuID, ucSGIndex);

    switch (enEvent)
    {
        case CRM_BRDSTATE_CHG_STANDBY_TO_ACTIVE:
            DHCPC_BoardStateChgProc();
            break;

        default:
            break;
    }

    return;
}
