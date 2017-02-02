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
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_SERVER_C
/*lint +e767*/


VOID DHCPC_UpdateServerGroupStatusNormal(ULONG ulSvrGrpIndex, UCHAR ucCurrentSrv)
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        (VOID)DHCPM_SetPrimarySrvStatusByIndex(ulSvrGrpIndex, DHCP_SEVER_NORMAL);
    }
    else
    {
        (VOID)DHCPM_SetSecondarySrvStatusByIndex(ulSvrGrpIndex, DHCP_SEVER_NORMAL);
    }

    return;
}


VOID DHCPC_TrySetCurSvrAbnormal(ULONG ulSvrGrpIndex, UCHAR ucCurrentSrv)
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        (VOID)DHCPM_TrySetPrimStatusAbnormalByIndex(ulSvrGrpIndex);
    }
    else
    {
        (VOID)DHCPM_TrySetSecStatusAbnormalByIndex(ulSvrGrpIndex);
    }

    return;
}


ULONG DHCPC_ReachTotalLimit(DHCPC_CTRLBLK *pstDhcpcContext)
{
    /* ���õ�ǰʹ�õķ�����״̬ */
    DHCPC_TrySetCurSvrAbnormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    pstDhcpcContext->ucCurSvrSendCount = 0;
    pstDhcpcContext->ucTotalSendCount = 0;

    /* ����VOS_ERR,ֹͣ������Ϣ */
    return VOS_ERR;
}


ULONG DHCPC_ReachSingleLimit(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* �������õ�ǰʹ�õķ�����״̬ */
    DHCPC_TrySetCurSvrAbnormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    /* ����ǰserver������Ϣ������0 */
    pstDhcpcContext->ucCurSvrSendCount = 0;

    /* ����ǵ�������,���ʹﵽ������,ֱ�ӷ���ʧ��.���ٽ��з��� */
    if (DHCP_SEVER_INVALID_IP == pstDhcpServer->aulSecondaryServerIp[0])
    {
        return VOS_ERR;
    }

    /* ���������������л� */
    if (DHCPC_PRIMARY_SERVER == pstDhcpcContext->ucCurrentServer)
    {
        /* ����л������������NORMAL,ֻ���Է���һ�� */
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            pstDhcpcContext->ucTotalSendCount += pstDhcpServer->ucRetransmitNum;
        }

        pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
    }
    else
    {
        /* ����л������������NORMAL,ֻ���Է���һ�� */
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            pstDhcpcContext->ucTotalSendCount += pstDhcpServer->ucRetransmitNum;
        }

        pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    }

    return VOS_OK;
}


ULONG DHCPC_SingleFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
    {
        /* ����NORMAL̬, �����ʹ�������Ϊ�ط�������. */
        pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
    }

    return VOS_OK;
}
ULONG DHCPC_DoubleFirstSend_MainNormal(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    if (DHCP_SEVER_TRY == pstDhcpServerStatus->ucSecondarySrvStatus)
    {
        /* ����ѡTry,����ֻ����һ�� */
        pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
        pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
    }
    else
    {
        pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    }

    return VOS_OK;
}
ULONG DHCPC_DoubleFirstSend_MainAbnormal(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    switch(pstDhcpServerStatus->ucSecondarySrvStatus)
    {
        case DHCP_SEVER_NORMAL:
            pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
            break;

        case DHCP_SEVER_ABNORMAL:
            /* ������ΪAbnormal,����ѡ��.��ֻ����һ�� */
            pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
            break;

        case DHCP_SEVER_TRY:
            /* ��Abnormal��Try,����ѡ��.��ֻ����һ�� */
            pstDhcpcContext->ucCurrentServer = DHCPC_SECONDARY_SERVER;
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
            break;

        default:
            VOS_Assert(0);
            return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPC_DoubleFirstSend_MainTry(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* ����ѡTry,����ֻ����һ�� */
    pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
    pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
    pstDhcpcContext->ucCurrentServer = DHCPC_PRIMARY_SERVER;
    return VOS_OK;
}
ULONG DHCPC_DoubleFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    ULONG ulReturn = VOS_ERR;

    switch(pstDhcpServerStatus->ucPrimarySrvStatus)
    {
        case DHCP_SEVER_NORMAL:
            ulReturn = DHCPC_DoubleFirstSend_MainNormal(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        case DHCP_SEVER_ABNORMAL:
            ulReturn = DHCPC_DoubleFirstSend_MainAbnormal(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        case DHCP_SEVER_TRY:
            ulReturn = DHCPC_DoubleFirstSend_MainTry(pstDhcpcContext, pstDhcpServer, pstDhcpServerStatus);
            break;

        default:
            VOS_Assert(0);
            return VOS_ERR;
    }

    return ulReturn;
}


ULONG DHCPC_NotFirstSend(DHCPC_CTRLBLK *pstDhcpcContext, LAP_DHCP_CFG_S *pstDhcpServer,
                                DHCP_SERVER_STATUS_S *pstDhcpServerStatus)
{
    /* ���ǵ��ط�������,Server status��״̬���ܱ������û��޸�,
     * �˴������ж�,�������Normal,���ٷ���һ��.
     */
    if (DHCPC_PRIMARY_SERVER == pstDhcpcContext->ucCurrentServer)
    {
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucPrimarySrvStatus)
        {
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        }
    }
    else
    {
        if (DHCP_SEVER_NORMAL != pstDhcpServerStatus->ucSecondarySrvStatus)
        {
            pstDhcpcContext->ucCurSvrSendCount = pstDhcpServer->ucRetransmitNum;
            pstDhcpcContext->ucTotalSendCount = pstDhcpServer->ucRetransmitNum;
        }
    }

    return VOS_OK;
}


VOID DHCPC_GetServerIp(LAP_DHCP_CFG_S *pstDhcpServer, UCHAR ucCurrentSrv, ULONG aulServerIp[LAP_IP_ULONG_NUM])
{
    if (DHCPC_PRIMARY_SERVER == ucCurrentSrv)
    {
        VOS_MemCpy(aulServerIp, pstDhcpServer->aulPrimaryServerIp, (sizeof(ULONG) * LAP_IP_ULONG_NUM));
    }
    else
    {
        VOS_MemCpy(aulServerIp, pstDhcpServer->aulSecondaryServerIp, (sizeof(ULONG) * LAP_IP_ULONG_NUM));
    }

    return;
}


ULONG DHCPC_SelectAndGetServerCfg(DHCPC_CTRLBLK *pstDhcpcContext, ULONG aulServerIp[LAP_IP_ULONG_NUM])
{
    ULONG   ulRet = VOS_ERR;
    UCHAR   ucIsSingleServer = VOS_TRUE;
    ULONG   ulSrvrGrpIdx = 0;
    ULONG   ulSingleSendLimit = 0;
    ULONG   ulTotalSendLimit = 0;
    DHCP_SERVER_STATUS_S stDhcpServerStatus = {0};
    LAP_DHCP_CFG_S stDhcpServer = {0};

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulSrvrGrpIdx = pstDhcpcContext->usServerGrpIndex;
    if ( ulSrvrGrpIdx >= DHCPGRP_MAX_NUM )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n ulSrvrGrpIdx Err DHCP ulSrvrGrpIdx is invalid!" );
        return VOS_ERR;
    }

    /*���� dhcp server index ��ȡ server group ��Ϣ*/
    ulRet = DHCPM_GetDhcpSrvCfgStatusByIndex(ulSrvrGrpIdx, &stDhcpServer, &stDhcpServerStatus);
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n stDhcpServerStatus Err DHCP stDhcpServerStatus!" );
        return VOS_ERR;
    }

    ulSingleSendLimit = stDhcpServer.ucRetransmitNum + 1;   /* ���ϵ�һ�η�����Ϣ(���ط�) */
    ulTotalSendLimit = ulSingleSendLimit << 1;  /* ����������ʱ,����ʹ���Ӧ����2�� */

    /* �ж��Ƿ񵥷�������������������. ��ǰ������Լ���е�������ֻ������,
     * ����ͨ�����������ȿ��ж�.
     */
    if (DHCP_SEVER_INVALID_IP != stDhcpServer.aulSecondaryServerIp[0])
    {
        ucIsSingleServer = VOS_FALSE;
    }

    if (pstDhcpcContext->ucTotalSendCount >= ulTotalSendLimit)
    {
        ulRet = DHCPC_ReachTotalLimit(pstDhcpcContext);
    }
    else if (pstDhcpcContext->ucCurSvrSendCount >= ulSingleSendLimit)
    {
        ulRet = DHCPC_ReachSingleLimit(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
    }
    /* ��һ�η��� */
    else if (0 == pstDhcpcContext->ucTotalSendCount)
    {
        if (VOS_TRUE == ucIsSingleServer)
        {
            ulRet = DHCPC_SingleFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
        }
        else
        {
            ulRet = DHCPC_DoubleFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
        }
    }
    else
    {
        /* �ط�����û�дﵽ�����������������ط�Ҳû�ﵽ�޶�ֵ. */
        ulRet = DHCPC_NotFirstSend(pstDhcpcContext, &stDhcpServer, &stDhcpServerStatus);
    }

    if (VOS_OK != ulRet)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SERVER_NO_RSP);

        /* ����ԭ���� */
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_NOT_RSP;

        /* ��ռ�¼����Ϣ���ʹ��� */
        pstDhcpcContext->ucCurSvrSendCount = 0;
        pstDhcpcContext->ucTotalSendCount = 0;
    }
    else
    {
        DHCPC_GetServerIp(&stDhcpServer, pstDhcpcContext->ucCurrentServer, aulServerIp);
    }

    return ulRet;
}

