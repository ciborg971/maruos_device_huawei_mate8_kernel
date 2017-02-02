/************************************************************************
*                                                                      *
*                             Vsncp.c                                  *
*                                                                      *
*  Project Code:                                                       *
*  Create Date:        2015/05/25                                      *
*  Author:             TIAN CHENCHEN                                   *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��VSNCPЭ��ģ��                              *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������VSNCPЭ��ģ���ȫ���ӿں������ڲ�������            *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

VOID PPP_PDNSendVSNCPReject(ULONG ulRPIndex,
                            UCHAR *pucMsg,
                            UCHAR ucErrCode);
ULONG PPP_VSNCP_CheckOUI(UCHAR *pPacket, ULONG ulLen);

/* PDN������ */
PDN_CONTEXT_S g_stPDNContext[A11_MAX_PDN_NUM];

/* VSNCP�ص��������ݽṹ */
PPPFSMCALLBACK_S g_stVsncpCallbacks =
{
    /* ������Э�̱��Ĵ��� */
    PPP_VSNCP_resetci,   /* ����������Ϣ����Э�̳�ʼֵ */
    PPP_VSNCP_cilen,     /* ��Ҫ���͵�request���ĳ��� */
    PPP_VSNCP_addci,     /* ��֯Э�̱��� */
    PPP_VSNCP_ackci,     /* ����Է���ack���� */
    VOS_NULL_PTR,                /* ����Է���nak���� */
    PPP_VSNCP_rejci,     /* ����Է���reject���� */
    PPP_VSNCP_reqci,     /* ����Է���request���� */
    VOS_NULL_PTR,                /* ����Э�����еı��ģ���protocol reject�� */
    /* �¼���Э��ת������ֹ״̬ */
    PPP_VSNCP_up,        /* Э��up */
    PPP_VSNCP_down,      /* Э����ʱdown,����Ҫ����Э��.
                           ��finished��������:����PPPOE��DDR�ȵ������
                           ����֪ͨ�²�����· */
    PPP_VSNCP_finished,  /* Э�������֪ͨ�ײ�:�����·.����LCP,ֻҪ����
                           PPPOE��DDR�ȵ����,�������reset��ʱ��,
                           ��ʱ����������Э�� */
    PPP_VSNCP_starting,  /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                           ����������Э��,�����,�뷢һ��up�¼�.
                           Э����������û�о���涨,���Բ�ʵ��*/
    /* ��Э����Ϣ */
    "VSNCP"               /* ��Э���� */
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOID PPP_VSNCP_ClearPdnContext(VOS_UINT8 ucPdnId)
{
    if (ucPdnId < A11_MAX_PDN_NUM)
    {
        PS_MEM_SET(&(g_stPDNContext[ucPdnId].stEhrpd.stApn),
            0, sizeof(CNAS_CTTF_EHRPD_APN_STRU));
        PS_MEM_SET(&(g_stPDNContext[ucPdnId].stEhrpd.stPdnAddress),
            0, sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
        PS_MEM_SET(&(g_stPDNContext[ucPdnId].stEhrpd.stPco),
            0, sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
        PS_MEM_SET(&(g_stPDNContext[ucPdnId].stEhrpd.aucIpv4DefaultRouterAddress),
            0, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);
        PS_MEM_SET(&(g_stPDNContext[ucPdnId].stEhrpd.stApnAmbr),
            0, sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
        g_stPDNContext[ucPdnId].stEhrpd.enAttachType    = 0;
        g_stPDNContext[ucPdnId].stEhrpd.enPdnType       = CNAS_CTTF_EHRPD_PDN_TYPE_INVALID;
        g_stPDNContext[ucPdnId].stEhrpd.ucAddressAllocCause    = 0;
        g_stPDNContext[ucPdnId].stEhrpd.enErrorCode     = 0;
    }
    else
    {
        PPPC_WARNING_LOG1("Ivalid pdn id!\r\n", ucPdnId);
    }

    return;
}


VOID PPP_CORE_VSNCPFinishProc(PPPINFO_S *pstPppInfo)
{
    PPPVSNCPINFO_S *pstVsncpInfo = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pstPppInfo->pstLcpInfo) || (VOS_NULL_PTR == pstPppInfo->pstVsncpInfo))
    {
        PPPC_WARNING_LOG("Null pointer!\r\n");
        return;
    }

    pstVsncpInfo = (PPPVSNCPINFO_S *)pstPppInfo->pstVsncpInfo;

    /*��Ӷ��ڶ�ʱ���ı���*/
    if (pstVsncpInfo->stFsm.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstVsncpInfo->stFsm.ulTimeOutID));
        pstVsncpInfo->stFsm.ulTimeOutID = 0;
    }

    pstVsncpInfo->ucRenegoFlag = VOS_FALSE;
    pstPppInfo->pstVsncpInfo = VOS_NULL_PTR;


    /* ʹ�ñ��ɾ�� */
    pstVsncpInfo->ucUsedFlag = VOS_FALSE;

    return;
}


ULONG PPP_Shell_ReceiveVSNCPUpFromCore(PPPINFO_S *pstPppInfo)
{
    PPPVSNCPINFO_S *pstVSNCPInfo = VOS_NULL_PTR;
    ULONG64 ulNegoTime = 0;

    PPP_DebugOut(MID_PPPC,
                 PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_Shell_ReceiveVSNCPUpFromCore: Enter");

    pstVSNCPInfo = (PPPVSNCPINFO_S *)pstPppInfo->pstVsncpInfo;

    /* ɾ��Э�̶�ʱ�� */
    (VOID)PPP_NodeDelete(pstPppInfo->ulRPIndex);
    (VOID)PPP_PDNNodeDelete(pstVSNCPInfo->ulPDNIndex);

    if (pstVSNCPInfo->ucRenegoFlag)
    {
        pstVSNCPInfo->ucRenegoFlag = 0;
        PPP_DBG_OK_CNT(PPP_PHOK_1383);
    }

    /* ����ͳ��:IPCPЭ�̳ɹ����� */
    //PPP_PerfInc(g_stPppPerfStatistic.pulIpcpSuccess, PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM);
    PPP_DBG_OK_CNT(PPP_PHOK_1384);

    /* ��̬���ӱ���óɹ� */
    //pstPppInfo->bPppStateFlg = PPP_STATE_SUCCESS;
    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS);
    PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo);

    if (0 == pstPppInfo->ulNegoEndTime)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1385);
        pstPppInfo->ulNegoEndTime = VOS_GetTick();
        ulNegoTime = pstPppInfo->ulNegoEndTime - pstPppInfo->ulNegoStartTime;
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_TOTAL_TIME,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        (ULONG)ulNegoTime);
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_NEGO_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
    }

    /* PPP��·�����ɹ� */
    pstPppInfo->bPppSuccess = 1;

    /* ֪ͨ���� */
    /* (VOID)PPP_SendUserInfo(pstPppInfo, VSNCP_INFOR); */


    /* (VOID)PPP_NotifyIpv6SendRA(pstPppInfo->ulRPIndex, pstVSNCPInfo->ucPDNID); */
    return VOS_OK;
}
VOID PPP_VSNCP_FSM_SetRetransmitTimer(PPPFSM_S *pstFsm)
{
    PPPVSNCPINFO_S *pstVsncpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    ULONG ulPdpIndex = 0;
    ULONG ulRet = 0;

    pstPppInfo = (PPPINFO_S *)(pstFsm->pPppInfo);
    pstVsncpInfo = (PPPVSNCPINFO_S *)(pstFsm->pProtocolInfo);

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("PPP_VSNCP_FSM_SetRetransmitTimer Null pointer!\r\n");
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVsncpInfo->ucPDNID,
                                     &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("PPP_GetPDNContextByPDNID!\r\n", pstVsncpInfo->ucPDNID);
        return;
    }


    if (0 == pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID)
    {
        pstPppInfo->pulCurrFsm = pstFsm;

        /* ulPdpIndex���2Byte��ΪIPCP/CCP/LCP/VSNCP����λ,�����û����50000/SC ������Byte��ʹ��*/
        ulPdpIndex = pstVsncpInfo->ulPDNIndex;
        ulPdpIndex |= (ULONG)pstFsm->usProtocol << 16;

        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_VSNCP_FSM_SetRetransmitTimer: ulPdpIndex = 0x%x ",
                      ulPdpIndex);

        ulRet = VOS_StartRelTimer((HTIMER)&(pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID),
                                    MID_PPPC,
                                    pstFsm->ulTimeOutTime,
                                    ulPdpIndex,
                                    PPPC_FSM_RETRANSMIT_TIMER,
                                    VOS_TIMER_NOLOOP,
                                    VOS_TIMER_PRECISION_0);

        if (ulRet != VOS_OK)
        {
            PPPC_WARNING_LOG1("VOS_StartRelTimer fail!\r\n", ulRet);
        }

        PPP_DBG_OK_CNT(PPP_PHOK_1386);

        VOS_DBGASSERT(ulRet == 0);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_FSM_SetRetransmitTimer :ulPDNIndex[%u]ucPDNID[%u]ulTimeOutID[%u]! ! ",
                 pstVsncpInfo->ulPDNIndex, pstVsncpInfo->ucPDNID,
                 pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID);

    PPP_DBG_OK_CNT(PPP_PHOK_1387);
    return;
}
ULONG PPP_VSNCP_FSM_DelRetransmitTimer(PPPFSM_S *pstFsm)
{
    PPPVSNCPINFO_S *pstVsncpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    ULONG ulRet = 0;

    pstPppInfo = (PPPINFO_S *)(pstFsm->pPppInfo);
    pstVsncpInfo = (PPPVSNCPINFO_S *)(pstFsm->pProtocolInfo);

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVsncpInfo->ucPDNID,
                                     &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("PPP_GetPDNContextByPDNID fail!\r\n", pstVsncpInfo->ucPDNID);
        return VOS_ERR;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_FSM_DelRetransmitTimer :ulPDNIndex[%u]ucPDNID[%u]ulTimeOutID[%u]! ! ",
                 pstVsncpInfo->ulPDNIndex, pstVsncpInfo->ucPDNID,
                 pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID);

    if (pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID));
        pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
        PPP_DBG_OK_CNT(PPP_PHOK_1388);
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1389);

    return VOS_OK;
}



VOID PPP_VSNCP_Clear(PPPVSNCPINFO_S *pstVsncpInfo, PDN_CONTEXT_S *pstPDNContext)
{
    if ((VOS_NULL_PTR == pstVsncpInfo) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_Clear :ulPDNIndex[%u]ucPDNID[%u]ulTimeOutID[%u]! ",
                 pstVsncpInfo->ulPDNIndex, pstVsncpInfo->ucPDNID,
                 pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID);

    if (pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID);
        pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
    }

    pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag = VOS_FALSE;

    if (pstPDNContext->stEhrpd.stVSNCP.ulPmipv6UpdTimeOutID)
    {
        PDN_FsmStopTimer(TIMER_TYPE_PDN_IPV6_FSM_TIEMR,
                         pstPDNContext->stEhrpd.stVSNCP.ulPmipv6UpdTimeOutID);

        pstPDNContext->stEhrpd.stVSNCP.ulPmipv6UpdTimeOutID = 0;
    }
    if (pstPDNContext->stEhrpd.stVSNCP.ulReconnectDnsTimeOutID)
    {
        PDN_FsmStopTimer(TIMER_TYPE_PDN_IPV6_FSM_TIEMR,
                         pstPDNContext->stEhrpd.stVSNCP.ulReconnectDnsTimeOutID);

        pstPDNContext->stEhrpd.stVSNCP.ulReconnectDnsTimeOutID = 0;
    }
    PPP_MemSet((UCHAR *)&(pstVsncpInfo->stFsm), 0, sizeof(PPPFSM_S));

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_Clear :success! ");
    PPP_DBG_OK_CNT(PPP_PHOK_1390);

    return;
}



VOID PPP_VSNCP_ClearALL(PPPINFO_S *pstPppInfo)
{
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    UCHAR ucPDNId = 0;
    ULONG ulRet;

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is NULL!\r\n");
        return;
    }

    for (ucPDNId = 0; ucPDNId < (VSNCP_OPTION_PDNID_MAX + 1); ucPDNId++)
    {
        pstPDNContext = VOS_NULL_PTR;
        ulRet = PPP_GetPDNContextByPDNID(ucPDNId, &pstPDNContext);
        if ((ulRet == VOS_OK) && (VOS_NULL_PTR != pstPDNContext))
        {
            /* ��ʼ��VSNCP���ƿ� */
            PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);

            PPP_VSNCP_Clear(&stVSNCPInfo, pstPDNContext);
            /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
            PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

            /* �ͷ�֮ǰ�Ļ�����Ϣ */
            if (pstPDNContext->stEhrpd.pucVsncpReq != VOS_NULL_PTR)
            {
                PPP_Free(pstPDNContext->stEhrpd.pucVsncpReq);
                pstPDNContext->stEhrpd.pucVsncpReq = VOS_NULL_PTR;
            }
            pstPDNContext->stEhrpd.ucbit1L2CReconnectFlg = VOS_FALSE;

            /* ֹͣIPv6��ʱ�������ٷ���RA��Ϣ */
            if (VOS_OK != IPV6_StopTimer(pstPDNContext->ulIpv6Timer))
            {
               /* ���ӵ�����Ϣ�������˳� */
               PPPC_WARNING_LOG("IPV6_StopTimer fail!\r\n");
            }
            pstPDNContext->ulIpv6Timer = 0;

        }

        PPP_VSNCP_ClearPdnContext(ucPDNId);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_ClearALL :success! ");
    PPP_DBG_OK_CNT(PPP_PHOK_1392);
    return;
}
VOID PPP_VSNCP_SetRenegoFlagForAllPDN(PPPINFO_S *pstPppInfo)
{
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    UCHAR ucPDNId = 0;
    ULONG ulRet = 0;

    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is NULL!\r\n");

        return;
    }

    for (ucPDNId = 0; ucPDNId < (VSNCP_OPTION_PDNID_MAX + 1); ucPDNId++)
    {
        pstPDNContext = VOS_NULL_PTR;
        ulRet = PPP_GetPDNContextByPDNID(ucPDNId,
                                         &pstPDNContext);
        if ((ulRet == VOS_OK) && (VOS_NULL_PTR != pstPDNContext))
        {
            pstPDNContext->stEhrpd.stVSNCP.ucRenegoFlag = VOS_TRUE;
        }
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_VSNCP_SetRenegoFlagForAllPDN :success! ");
    PPP_DBG_OK_CNT(PPP_PHOK_1393);
    return;
}


ULONG PPP_GetPDNContextByPDNID(UCHAR ucPDNId, PDN_CONTEXT_S **ppstPDNContext)
{
    PS_BOOL_ENUM_UINT8                  enIsUsing;

    enIsUsing = PPPC_IsPdnIdUsing(ucPDNId);

    if (PS_FALSE == enIsUsing)
    {
        return VOS_ERR;
    }

    *ppstPDNContext = &(g_stPDNContext[ucPDNId]);

    return VOS_OK;
}


PS_BOOL_ENUM_UINT8 PPP_VSNCP_IsPDNOpened(UCHAR ucPDNId)
{
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    ULONG ulRet = 0;

    /* ȡ��PdnContext */
    ulRet = PPP_GetPDNContextByPDNID(ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("PPP_GetPDNContextByPDNID fail!\r\n", ulRet);

        return PS_FALSE;
    }

    if (PPP_STATE_OPENED == pstPDNContext->stEhrpd.stVSNCP.ucState)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

#if 0
ULONG PPP_VSNCP_GetPDNContextByPDNID(ULONG ulRpIdx, UCHAR ucPDNId, PDN_CONTEXT_S **ppstPDNContext)
{
    SDB_RETURNCODE_E enSdbResult = SDB_SUCCESS;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    if (VOS_NULL == ppstPDNContext)
    {
        PPPC_WARNING_LOG("ppstPDNContext is null!\r\n");
        return VOS_ERR;
    }

    if (A11_MAX_PDN_NUM <= ucPDNId)
    {
        PPPC_WARNING_LOG1("PPP_VSNCP_GetPDNContextByPDNID: ucPDNId is ERR!\r\n", ucPDNId);
        return VOS_ERR;
    }

    enSdbResult = SDB_GetRpContextByIndex(ulRpIdx, (UCHAR **)&pstRpContext);
    if ((SDB_SUCCESS != enSdbResult) || (VOS_NULL == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_682);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_VSNCP_GetPDNContextByPDNID: ulRpIdx(%d) is ERR!!pstRpContext(%x)",
                     ulRpIdx,
                     pstRpContext);
        return VOS_ERR;
    }

    if (0 != pstRpContext->ausPdnIndexArray[ucPDNId])
    {
        enSdbResult = SDB_GetPdnContextByIndex((ULONG)pstRpContext->ausPdnIndexArray[ucPDNId],
                                               (UCHAR **)&pstPDNContext);
        if ((SDB_SUCCESS != enSdbResult) || (VOS_NULL == pstPDNContext))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_683);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n PPP_VSNCP_GetPDNContextByPDNID: ulPdnIndex(%d) is ERR! pstPDNContext(%x)",
                         pstRpContext->ausPdnIndexArray[ucPDNId],
                         pstPDNContext);
            return VOS_ERR;
        }

        *ppstPDNContext = pstPDNContext;

        return VOS_OK;
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_684);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_VSNCP_GetPDNContextByPDNID: ulPdnIndex(%d) is ERR! ucPDNId(%u)",
                     pstRpContext->ausPdnIndexArray[ucPDNId], ucPDNId);
        return VOS_ERR;
    }
}
#endif


VOID PPP_VSNCP_ReceiveEventFromCore(VOID *pstVsncpInfo, ULONG ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;

    VOS_DBGASSERT(pstVsncpInfo);
    PPP_TRACE("\r\n---Into PPP_VSNCP_ReceiveEventFromCore ulCmd: %d---\r\n", ulCmd);

    if (VOS_NULL_PTR == pstVsncpInfo)
    {
        PPPC_WARNING_LOG("pstVsncpInfo is null!\r\n");
        return;
    }

    /* ����ͳ��:VSNCPЭ�̳��Դ��� */
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
    }

    pstFsm = &(((PPPVSNCPINFO_S*)pstVsncpInfo)->stFsm);

    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}
VOID PPP_VSNCP_ReceivePacket (VOID *pstVsncpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPFSM_S *pstFsm = VOS_NULL_PTR;
    VOS_UINT8 ucPppId;

    VOS_DBGASSERT(pstVsncpInfo);
    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);

    if ((VOS_NULL_PTR == pstVsncpInfo) || (VOS_NULL_PTR == pPacket))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return;
    }

    pstFsm = &(((PPPVSNCPINFO_S*)pstVsncpInfo)->stFsm);

    ucPppId = PPPC_GetCurrentPppId();
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, ucPppId);
    return;

}


VOID PPP_VSNCP_UpdateApnAmbr
(
    PDN_CONTEXT_S                      *pstPDNContext,
    PDN_PPP_VSNCP_REQ_S                *pstVsncpReqInfo
)
{
    UCHAR ucAMBRLen = 0;
    UCHAR *pucAMBR = VOS_NULL_PTR;
    CNAS_CTTF_EHRPD_APN_AMBR_STRU *pstApnAmbr = VOS_NULL_PTR;

    ucAMBRLen = pstVsncpReqInfo->ucAMBRLen;
    pucAMBR = pstVsncpReqInfo->aucAMBR;
    pstApnAmbr = &(pstPDNContext->stEhrpd.stApnAmbr);

    switch (ucAMBRLen)
    {
        case VSNCP_AMBR_LEN_3 * 2:
        {
            pstApnAmbr->bitOpDLApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpDLApnAmbrExt = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbrExt = PS_TRUE;
            pstApnAmbr->bitOpDLApnAmbrExt2 = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbrExt2 = PS_TRUE;
            pstApnAmbr->ucDLApnAmbr = pucAMBR[0];
            pstApnAmbr->ucULApnAmbr = pucAMBR[1];
            pstApnAmbr->ucDLApnAmbrExt = pucAMBR[2];
            pstApnAmbr->ucULApnAmbrExt = pucAMBR[3];
            pstApnAmbr->ucDLApnAmbrExt2 = pucAMBR[4];
            pstApnAmbr->ucULApnAmbrExt2 = pucAMBR[5];

            break;
        }
        case VSNCP_AMBR_LEN_2 * 2:
        {
            pstApnAmbr->bitOpDLApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpDLApnAmbrExt = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbrExt = PS_TRUE;
            pstApnAmbr->bitOpDLApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->ucDLApnAmbr = pucAMBR[0];
            pstApnAmbr->ucULApnAmbr = pucAMBR[1];
            pstApnAmbr->ucDLApnAmbrExt = pucAMBR[2];
            pstApnAmbr->ucULApnAmbrExt = pucAMBR[3];

            break;
        }
        case VSNCP_AMBR_LEN_1 * 2:
        {
            pstApnAmbr->bitOpDLApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpULApnAmbr = PS_TRUE;
            pstApnAmbr->bitOpDLApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpDLApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->ucDLApnAmbr = pucAMBR[0];
            pstApnAmbr->ucULApnAmbr = pucAMBR[1];

            break;
        }
        case 0:
        {
            pstApnAmbr->bitOpDLApnAmbr = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbr = PS_FALSE;
            pstApnAmbr->bitOpDLApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpDLApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt2 = PS_FALSE;

            break;
        }
        default:
        {
            pstApnAmbr->bitOpDLApnAmbr = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbr = PS_FALSE;
            pstApnAmbr->bitOpDLApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt = PS_FALSE;
            pstApnAmbr->bitOpDLApnAmbrExt2 = PS_FALSE;
            pstApnAmbr->bitOpULApnAmbrExt2 = PS_FALSE;

            PPPC_WARNING_LOG1("illegeal ucAMBRLen!\r\n", ucAMBRLen);

            return;
        }
    }
}


VOID PPP_VSNCP_UpdatePdnContext
(
    PDN_CONTEXT_S                      *pstPDNContext,
    PDN_PPP_VSNCP_REQ_S                *pstVsncpReqInfo
)
{
    UCHAR ucAPNLen = 0;
    UCHAR *pucAPN = VOS_NULL_PTR;
    UCHAR *pucPco = VOS_NULL_PTR;
    UCHAR ucPdnType = 0;
    UCHAR *pucPdnAddress = VOS_NULL_PTR;
    UCHAR *pucIpv4DefaultRouterAddress = VOS_NULL_PTR;

    /* PdnId */
    pstPDNContext->stEhrpd.ucPdnId = pstVsncpReqInfo->ucPdnId;

    /* Apn */
    ucAPNLen = (UCHAR)VOS_StrLen(pstVsncpReqInfo->szApn);
    pucAPN = pstPDNContext->stEhrpd.stApn.aucApn;
    pstPDNContext->stEhrpd.stApn.ucApnLen = ucAPNLen;
    if (ucAPNLen > 0)
    {
        PPP_PUTCHARPTR(pstVsncpReqInfo->szApn, pucAPN, ucAPNLen);
    }

    /* PdnType */
    pstPDNContext->stEhrpd.enPdnType = pstVsncpReqInfo->ucPdnType;

    /* AttchType */
    pstPDNContext->stEhrpd.ucAttchType = pstVsncpReqInfo->ucAttchType;

    /* PdnAddress */
    ucPdnType = pstVsncpReqInfo->ucPdnType;
    pucPdnAddress = pstPDNContext->stEhrpd.stPdnAddress.aucAddress;
    if (ucPdnType & VSNCP_OPTION_PDNTYPE_IPV6)
    {
        PPP_PUTCHARPTR((UCHAR*)(pstVsncpReqInfo->aucIpv6Addr + PDN_IPV6PREF_LEN),
                       pucPdnAddress,
                       PDN_IPV6INTF_LEN);
    }

    if (ucPdnType & VSNCP_OPTION_PDNTYPE_IPV4)
    {
        PPP_PUTADDR(pstVsncpReqInfo->ulIpAddr, pucPdnAddress);
    }

    /* Pco */
    pucPco = pstPDNContext->stEhrpd.stPco.aucPco;
    pstPDNContext->stEhrpd.stPco.ucPcoLen = pstVsncpReqInfo->ucPcoLen;
    if (pstVsncpReqInfo->ucPcoLen > 0)
    {
        PPP_PUTCHARPTR(pstVsncpReqInfo->szPco, pucPco, pstVsncpReqInfo->ucPcoLen);
    }

    /* Ipv4DefaultRouterAddress */
    pucIpv4DefaultRouterAddress = pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress;
    PPP_PUTCHARPTR(pstVsncpReqInfo->aucIpv4DefaultRouterAddress,
                   pucIpv4DefaultRouterAddress,
                   VSNCP_OPTION_IPV4_DEFROUT_LEN - VSNCP_CODE_ID_LEN);

    /* AddressAllocCause */
    pstPDNContext->stEhrpd.ucAddressAllocCause = pstVsncpReqInfo->ucAddressAllocCause;
}


VOID PPP_VSNCP_UpdateErrorCode
(
    PDN_CONTEXT_S                      *pstPDNContext,
    UCHAR                               ucErrorCode
)
{
    pstPDNContext->stEhrpd.enErrorCode = ucErrorCode;
}


/*lint -e550*/
VOID PPP_VSNCP_resetci(PPPFSM_S *pstFsm)
{
    PPPVSNCPINFO_S *pstVsncpInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;

    PPP_TRACE("\r\n---Into PPP_VSNCP_resetci---\r\n");

    pstVsncpInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstVsncpInfo->pstPppInfo;


    return;
}
/*lint +e550*/


USHORT PPP_VSNCP_cilen(PPPFSM_S *pstFsm)
{
    PPPVSNCPINFO_S *pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    USHORT usTotalLen = 0;
    ULONG ulRet = 0;

    /* OUI */
    usTotalLen += VSNCP_3GPP2_OUI_LEN;

    /* ȡ��pdnContext */
    /* �Ҹ���ȡ����ֵ����pstVsncpReqInfo��pstOptSequence */
    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return 0;
    }

    /* PdnID */
    usTotalLen += VSNCP_OPTION_PDNID_LEN;
    /* Apn */
    usTotalLen += pstPDNContext->stEhrpd.stApn.ucApnLen + VSNCP_CODE_ID_LEN + 1;
    /* PdnType */
    usTotalLen += VSNCP_OPTION_PDNTYPE_LEN;
    /* PdnAddress */
    usTotalLen += (UCHAR)VOS_StrLen(pstPDNContext->stEhrpd.stPdnAddress.aucAddress)
                          + VSNCP_CODE_ID_LEN + 1;
    /* Pco */
    usTotalLen += pstPDNContext->stEhrpd.stPco.ucPcoLen + VSNCP_CODE_ID_LEN;
    /* AttachType */
    usTotalLen += VSNCP_OPTION_ATTACHTYPE_LEN;
    /* Ipv4DefaultRouterAddress */
    usTotalLen += VSNCP_OPTION_IPV4_DEFROUT_LEN;
    /* AddressAllocCause */
    usTotalLen += VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN;

    return usTotalLen;
}
VOID PPP_VSNCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPPVSNCPINFO_S *pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    PPPINFO_S *pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    PPPCONFIGINFO_S *pstConfigInfo = pstPppInfo->pstConfigInfo;

    UCHAR *pucOldPacket = VOS_NULL_PTR;
    VSNCP_OPTION_ENCODE pOptionFunc = VOS_NULL_PTR;
    VSNP_CONIFG_OPTION_SEQUENCE_S stOptSequence;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S stVsncpReqInfo;
    ULONG ulRet = 0;
    int i = 0;
    USHORT usOffset = 0;
    ULONG ulOptionLen = 0;
    ULONG ulTotalLen = 0;
    UCHAR ucType = 0;

    /* ��Ϣ���� */
    pucOldPacket = pPacket;

    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_1, pucOldPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_2, pucOldPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_3, pucOldPacket);

    /* ȡ��PdnContext */
    /* ����ȡ����ֵ����pstOptSequence */
    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");

        return;
    }

    /* ����OptSequence */
    stOptSequence.aucConfigOptionType[0] = PPP_VSNCP_CO_PDNID;
    stOptSequence.aucConfigOptionType[1] = PPP_VSNCP_CO_APN;
    stOptSequence.aucConfigOptionType[2] = PPP_VSNCP_CO_PDN_TYPE;
    stOptSequence.aucConfigOptionType[3] = PPP_VSNCP_CO_PDN_ADDR;
    stOptSequence.aucConfigOptionType[4] = PPP_VSNCP_CO_PDN_PCO;
    stOptSequence.aucConfigOptionType[5] = PPP_VSNCP_CO_ATTACH_TYPE;
    stOptSequence.aucConfigOptionType[6] = PPP_VSNCP_CO_IPV4_DEFRTADDR;
    stOptSequence.aucConfigOptionType[7] = PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE;

    for (i = 0; i < PPP_VSNCP_CO_BUTT; i++)
    {
        ucType = stOptSequence.aucConfigOptionType[i];
        if (ucType)
        {
            pOptionFunc = g_pVsncpOptionEncode[ucType];
            if (pOptionFunc != VOS_NULL_PTR)
            {
                ulRet = pOptionFunc(pucOldPacket, pstPDNContext, &ulOptionLen, &stVsncpReqInfo);
                if (VOS_OK != ulRet)
                {
                    PPPC_WARNING_LOG2("PPP_VSNCP_reqci fail!\r\n", ucType, ulRet);
                }
                else
                {
                    /* ��λ������һ������λ�� */
                    pucOldPacket = (pucOldPacket + ulOptionLen);
                    /* ���ȸ��� */
                    ulTotalLen = ulTotalLen + ulOptionLen;
                    /* ���Գ������� */
                    ulOptionLen = 0;
                }
            }

        }
    }

    ulTotalLen += VSNCP_3GPP2_OUI_LEN;

    /* ʹ�ÿ��ƿ� */
    pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = VOS_TRUE;

    return;
}



VOID PPP_VSNCP_Termaddci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPPVSNCPINFO_S *pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;

    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_1, pPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_2, pPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_3, pPacket);

    ADDCIPDNID(PPP_VSNCP_CO_PDNID,
               pstVSNCPInfo->ucPDNID);

    return;
}



USHORT PPP_VSNCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    USHORT usOffset = 0;
    PPPVSNCPINFO_S *pstVSNCPInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;
    ULONG ulRet = 0;

    if (ulLen == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1398);
        PPPC_WARNING_LOG("ulLen is 0!\r\n");
        return VOS_OK;
    }

    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pstFsm))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return VOS_ERROR;
    }

    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVSNCPInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERROR;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return VOS_ERROR;
    }

    /* ������� */
    usOffset = FSM_HDRLEN + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S) + sizeof(PDN_PPP_VSNCP_REQ_S);
    pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pPacket - usOffset);

    /* ��ȡ��ֵ���µ�PdnContext */
    PPP_VSNCP_UpdatePdnContext(pstPDNContext, pstVsncpReqInfo);

    return VOS_OK;
}


USHORT PPP_VSNCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_DBG_OK_CNT(PPP_PHOK_1399);
    return VOS_ERR;
}


UCHAR PPP_VSNCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG *pulLen)
{
    PPPVSNCPINFO_S *pstVSNCPInfo = VOS_NULL_PTR;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR *pucOldPacket = VOS_NULL_PTR;
    VSNCP_OPTION_ENCODE pOptionFunc = VOS_NULL_PTR;
    VSNP_CONIFG_OPTION_SEQUENCE_S *pstOptSequence = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;
    ULONG ulRet = 0;
    int i = 0;
    USHORT usOffset = 0;
    ULONG ulOptionLen = 0;
    ULONG ulTotalLen = 0;
    UCHAR ucType = 0;

    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pstFsm) || (VOS_NULL_PTR == pulLen))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return CONFACK;
    }

    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVSNCPInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return CONFACK;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return CONFACK;
    }

    /* ��ԪЯ����� */
    usOffset = FSM_HDRLEN + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S);
    pstOptSequence = (VSNP_CONIFG_OPTION_SEQUENCE_S *)(pPacket - usOffset);
    /* ������� */
    usOffset = FSM_HDRLEN + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S) + sizeof(PDN_PPP_VSNCP_REQ_S);
    pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pPacket - usOffset);

    /* ��Ϣ���� */
    pucOldPacket = pPacket;
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_1, pucOldPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_2, pucOldPacket);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_3, pucOldPacket);

    for (i = 0; i < PPP_VSNCP_CO_BUTT; i++)
    {
        ucType = pstOptSequence->aucConfigOptionType[i];
        if (ucType)
        {
            pOptionFunc = g_pVsncpOptionEncode[ucType];
            if (pOptionFunc != VOS_NULL_PTR)
            {
                ulRet = pOptionFunc(pucOldPacket, pstPDNContext, &ulOptionLen, pstVsncpReqInfo);
                if (VOS_OK != ulRet)
                {
                    PPPC_WARNING_LOG2("PPP_VSNCP_reqci fail!\r\n", ucType, ulRet);
                }
                else
                {
                    /* ��λ������һ������λ�� */
                    pucOldPacket = (pucOldPacket + ulOptionLen);
                    /* ���ȸ��� */
                    ulTotalLen = ulTotalLen + ulOptionLen;
                    /* ���Գ������� */
                    ulOptionLen = 0;
                }
            }

        }
    }

    *pulLen = ulTotalLen + VSNCP_3GPP2_OUI_LEN;

    /* ����ApnAmbr */
    PPP_VSNCP_UpdateApnAmbr(pstPDNContext, pstVsncpReqInfo);

    /* Return final code */
    return CONFACK;
}


VOID PPP_VSNCP_up(PPPFSM_S *pstFsm)
{
    ULONG ulAccept = 0;
    PPPINFO_S *pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    PPPVSNCPINFO_S *pstVSNCPInfo = VOS_NULL_PTR;
    ULONG ulRet = 0;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    /* VSNCPЭ�̽���Ƿ���Խ��� */
    ulAccept = PPP_VSNCP_UpResetCi(pstPppInfo);
    if (VOS_OK != ulAccept)
    {
        /* Э�̽�����ɽ���,����Э�� */
        PPP_VSNCP_NegotiationDown(pstFsm->pProtocolInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_689);
        return;
    }

    /* Э�̽�����Խ���,���ں˷���VSNCP Up�¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo,
                                      (LONG)PPP_EVENT_VSNCPUP,
                                      VOS_NULL_PTR);

    pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVSNCPInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return;
    }

    /* ֪ͨLCP�ظ�CNAS */
    PPPC_RespEhsmPdnConnectCmd(pstVSNCPInfo, VOS_OK);

    /* ���ñ�ʶλ��ָʾĿǰ�Ѳ��ڳ��Խ���Pdn���� */
    pstPDNContext->stEhrpd.stVSNCP.ucStartingFlag = VOS_FALSE;
}
VOID PPP_VSNCP_down(PPPFSM_S *pstFsm)
{

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_VSNCPDOWN,
                                      VOS_NULL_PTR);
    return;
}


VOID PPP_VSNCP_finished(PPPFSM_S *pstFsm)
{
    ULONG ulRet = 0;
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S *pstVSNCPInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    pstVSNCPInfo = (PPPVSNCPINFO_S *)pstFsm->pProtocolInfo;
    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVSNCPInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstVSNCPInfo->ucPDNID,
                                     &pstPDNContext);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return;
    }

    /* ���״̬�����õ�����ԭ���ǳ�ʱ��������PdnContext�е�ErrorCodeΪ��ʱ */
    if (AM_RELCODE_PPP_VSNCP_NEGOTIMEOUT == pstVSNCPInfo->ulPDNRleaseCode)
    {
        PPP_VSNCP_UpdateErrorCode(pstPDNContext, CNAS_CTTF_EHRPD_ERROR_CODE_TIMEROUT);
    }

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_VSNCPFINISHED,
                                      VOS_NULL_PTR);

    /* ֪ͨNAS��ʧ�� */
    if (VOS_TRUE == pstPDNContext->stEhrpd.stVSNCP.ucStartingFlag)
    {
        PPPC_RespEhsmPdnConnectCmd(pstVSNCPInfo, VOS_ERROR);
        /* ���ñ�ʶλ��ָʾĿǰ�Ѳ��ڳ��Խ���Pdn���� */
        pstPDNContext->stEhrpd.stVSNCP.ucStartingFlag = VOS_FALSE;
    }
    else if (VOS_TRUE == pstPDNContext->stEhrpd.stVSNCP.ucStoppingFlag)
    {
        PPPC_RespEhsmPdnDisconnectCmd(VOS_ERROR);
        /* ���ñ�ʶλ��ָʾĿǰ�Ѳ��ڳ��ԶϿ�Pdn���� */
        pstPDNContext->stEhrpd.stVSNCP.ucStoppingFlag = VOS_FALSE;
    }
}


VOID PPP_VSNCP_starting(PPPFSM_S *pstFsm)
{

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_VSNCPSTARTING,
                                      VOS_NULL_PTR);
}


VOID PPP_VSNCP_Init(PPPINFO_S *pstPppInfo,
                    PPPVSNCPINFO_S *pstVSNCPInfo,
                    PDN_CONTEXT_S *pstPDNContext,
                    UCHAR ucPDNID)
{
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pstPppInfo) || (VOS_NULL_PTR == pstVSNCPInfo) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return;
    }

    pstFsm = &(pstVSNCPInfo->stFsm);
    //pstPppInfo->bPppStateFlg = PPP_STATE_NEGOING;
    pstPppInfo->pstVsncpInfo = pstVSNCPInfo;

    /* VSNCP���ƿ��ʼ�� */
    pstVSNCPInfo->pstPppInfo = pstPppInfo;
    pstVSNCPInfo->ucPDNID = ucPDNID;
    pstVSNCPInfo->ulPDNIndex = pstPDNContext->ulPdnIndex;
    pstVSNCPInfo->ucUsedFlag = pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag;
    pstVSNCPInfo->ucRenegoFlag =  pstPDNContext->stEhrpd.stVSNCP.ucRenegoFlag;
    pstVSNCPInfo->ucDefaultAPNFlag = pstPDNContext->stEhrpd.ucDefAPNFlag;
    pstVSNCPInfo->ulPDNRleaseCode = pstPDNContext->stEhrpd.stVSNCP.ucPdnReleaseCode;
    /* �Ƿ���Ч,��Ч����ҪЯ�� */
    if (VOS_TRUE == pstPDNContext->stEhrpd.ucApnAmbrDLFlag)
    {
        pstVSNCPInfo->ucApnAmbrDLFlag = VOS_TRUE;
        pstVSNCPInfo->ulApnAmbrDL = pstPDNContext->stEhrpd.ulApnAmbrDL;
    }
    if (VOS_TRUE == pstPDNContext->stEhrpd.ucApnAmbrULFlag)
    {
        pstVSNCPInfo->ucApnAmbrULFlag = VOS_TRUE;
        pstVSNCPInfo->ulApnAmbrUL = pstPDNContext->stEhrpd.ulApnAmbrUL;
    }

    /* ״̬����ʼ�� */
    pstFsm->usProtocol = PPP_VSNCP;
    pstFsm->pstCallBacks  = &g_stVsncpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstVSNCPInfo;
    pstFsm->pPppInfo = (char*)pstPppInfo;
    pstFsm->ucPktId = pstPDNContext->stEhrpd.stVSNCP.ucPktId;
    pstFsm->sRetransmits = pstPDNContext->stEhrpd.stVSNCP.sRetransmits;

    if (pstPppInfo->pstUsedConfigInfo == VOS_NULL_PTR)
    {
        pstFsm->ulTimeOutTime = PPP_DEFTIMEOUTTIME;
    }
    else
    {
        pstFsm->ulTimeOutTime = pstPppInfo->pstUsedConfigInfo->ulNegTimeOut;
    }

    pstFsm->ulTimeOutID = pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID;

    pstFsm->ucState = pstPDNContext->stEhrpd.stVSNCP.ucState;

    return;
}
VOID PPP_VSNCP_FreshPDNContext(PPPVSNCPINFO_S *pstVSNCPInfo, PDN_CONTEXT_S *pstPDNContext, PPPINFO_S *pstPppInfo)
{
    PPPFSM_S *pstFsm = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pstVSNCPInfo) || (VOS_NULL_PTR == pstPDNContext) || (VOS_NULL_PTR == pstPppInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return;
    }

    pstFsm = &(pstVSNCPInfo->stFsm);

    pstPDNContext->stEhrpd.stVSNCP.sRetransmits = pstFsm->sRetransmits;
    pstPDNContext->stEhrpd.stVSNCP.ucPktId = pstFsm->ucPktId;
    pstPDNContext->stEhrpd.stVSNCP.ucState = pstFsm->ucState;
    pstPDNContext->stEhrpd.stVSNCP.ucPDNID = pstVSNCPInfo->ucPDNID;
    pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = pstVSNCPInfo->ucUsedFlag;
    pstPDNContext->stEhrpd.stVSNCP.ucRenegoFlag = pstVSNCPInfo->ucRenegoFlag;
    pstPDNContext->stEhrpd.stVSNCP.ucPdnReleaseCode = (UCHAR)pstVSNCPInfo->ulPDNRleaseCode;
    pstPppInfo->pstVsncpInfo = VOS_NULL_PTR;

    return;
}


ULONG PPP_VSNCP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    return VOS_OK;
}


/*lint -e550*/
VOID PPP_VSNCP_SendReject(PPPINFO_S *pstPppInfo,
                          UCHAR *pucMsg,
                          UCHAR ucErrCode,
                          USHORT usPdnId)
{
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulOffset = 0;
    ULONG ulErrorCode = 0;
    UCHAR *pCurPos = VOS_NULL_PTR;
    UCHAR ucOldCode = 0;
    UCHAR ucOldID = 0;
    USHORT usLen = 0;
    UCHAR *pucLenPos = 0;

    if (VOS_NULL_PTR == pstPppInfo)
    {
        /* ���debug��Ϣ */
        PPPC_WARNING_LOG("null pointer!\r\n");
        return;
    }


    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;
    if (VOS_NULL_PTR == pHead)
    {
        /*������������Ϣ*/
        PPPC_WARNING_LOG("pHead is null pointer!\r\n");
        return;
    }

    pPacket = pHead + ulOffset;
    pCurPos = pPacket;

    PPP_GETCHAR(ucOldCode, pucMsg);
    PPP_GETCHAR(ucOldID, pucMsg);

    /* ��Ϣͷ */
    PPP_PUTCHAR(CONFREJ, pCurPos);
    PPP_PUTCHAR(ucOldID, pCurPos);
    /* �ܳ��� */
    pucLenPos = pCurPos;
    PPP_PUTSHORT(0, pCurPos);
    usLen += VSNCP_HEADERLEN;

    /* OUI */
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_1, pCurPos);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_2, pCurPos);
    PPP_PUTCHAR(VSNCP_3GPP2_OUI_BYTE_3, pCurPos);
    usLen += VSNCP_3GPP2_OUI_LEN;

    if (VOS_NULL_WORD != usPdnId)
    {
        /* ��PDN IDд�뱨�� */
        PPP_PUTCHAR(PPP_VSNCP_CO_PDNID, pCurPos);
        PPP_PUTCHAR(VSNCP_OPTION_PDNID_LEN, pCurPos);
        PPP_PUTCHAR(usPdnId, pCurPos);
        usLen += VSNCP_OPTION_PDNID_LEN;
    }

    /* ��ERRCODEд�뱨�� */
    PPP_PUTCHAR(PPP_VSNCP_CO_ERRCODE, pCurPos);
    PPP_PUTCHAR(VSNCP_OPTION_ERRCODE_LEN, pCurPos);
    PPP_PUTCHAR(ucErrCode, pCurPos);
    usLen += VSNCP_OPTION_ERRCODE_LEN;

    /* �޸��ܳ��� */
    PPP_PUTSHORT(usLen, pucLenPos);

    /* ֱ�ӵ�����ǵķ��ͺ��� */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo,
                                              pHead,
                                              pPacket,
                                              (ULONG)usLen,
                                              PPP_VSNCP);
    if (ulErrorCode != VOS_OK)
    {
        /*���������Ϣ*/
        PPPC_WARNING_LOG1("PPP_Shell_GetPacketFromCore fail!\r\n", ulErrorCode);
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1402);
    return;
}
/*lint +e550*/



ULONG PPP_VSNCP_NotifyVSNCPStart(PPPINFO_S *pstPppInfo, UCHAR ucPDNId)
{
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    ULONG ulRet = 0;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    /* �ж��Ƿ�Ϊ����Э�̽׶�*/
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPPC_WARNING_LOG1("usPhase is not PPP_PHASE_NETWORK!\r\n", pstPppInfo->usPhase);
        return VOS_OK;
    }

    /* ȡ��PDNContext */
    ulRet = PPP_GetPDNContextByPDNID(ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return VOS_ERR;
    }

    /* ��ʼ������Ҫ��״̬����Ϣ���� */
    pstPDNContext->stEhrpd.stVSNCP.sRetransmits = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucPktId = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucState = 0;
    pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = VOS_TRUE;

    /* ���ñ�ʶλ��ָʾĿǰ�ڳ��Խ���Pdn���� */
    pstPDNContext->stEhrpd.stVSNCP.ucStartingFlag = VOS_TRUE;

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);
    /* VSNCP״̬��open up��ʼЭ�� */
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR);
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_UP, VOS_NULL_PTR);

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_VSNCP_NotifyVSNCPStart: Done!");
    PPP_DBG_OK_CNT(PPP_PHOK_1433);
    return VOS_OK;
}


ULONG PPP_VSNCP_NotifyVSNCPStop(PPPINFO_S *pstPppInfo, UCHAR ucPDNId)
{
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    ULONG ulRet = 0;
    UCHAR ucErrCode = 0;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    /* ȡ��PDNContext */
    ulRet = PPP_GetPDNContextByPDNID(ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        return VOS_ERR;
    }

    /* ���ñ�ʶλ��ָʾĿǰ�ڳ��ԶϿ�Pdn���� */
    pstPDNContext->stEhrpd.stVSNCP.ucStoppingFlag = VOS_TRUE;

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);

    /* ����vsncp term��Ϣ */
    if (PPP_STATE_INITIAL != stVSNCPInfo.stFsm.ucState)
    {
        PPP_VSNCP_NegotiationDown(&stVSNCPInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1449);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1450);

        PPP_CORE_VSNCPFinishProc(pstPppInfo);
    }

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_VSNCP_NotifyVSNCPStop Done!");
    return VOS_OK;
}

#if 0
ULONG PPP_VSNCP_CheckOptionIsChange(PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo,
                                    PDN_PPP_VSNCP_REQ_S *pstOldVsncpReqInfo,
                                    USHORT usOldAPNIndex,
                                    UCHAR ucPDNType)
{
    USHORT usNewAPNIndex = 0;
    ULONG ulRet = 0;
    UCHAR szApn[HSGW_MAX_APN_NAME_LEN + 1] = {0};

    if (VOS_NULL == pstNewVsncpReqInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_VSNCP_CheckOptionIsChange: input is null!");
        return VOS_ERR;
    }

    if (VOS_NULL != pstOldVsncpReqInfo)
    {
        if ((pstNewVsncpReqInfo->ucPdnId != pstOldVsncpReqInfo->ucPdnId)
            || (pstNewVsncpReqInfo->ucPdnType != pstOldVsncpReqInfo->ucPdnType)
            || (0 != VOS_MemCmp((const CHAR *)pstNewVsncpReqInfo->szApn,
                                (const CHAR *)pstOldVsncpReqInfo->szApn,
                                HSGW_MAX_APN_NAME_LEN)))
        {
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "\r\n PPP_VSNCP_CheckOptionIsChange: option is change!");
            PPP_DBG_ERR_CNT(PPP_PHERR_695);
            return VOS_ERR;
        }
    }
    else
    {
        /* ����APN NAME����APN */
        if ('\0' !=  pstNewVsncpReqInfo->szApn[0])
        {
            VOS_MemCpy(szApn, pstNewVsncpReqInfo->szApn, HSGW_MAX_APN_NAME_LEN);
            ulRet = USM_GetApnIndexByApnName(szApn, &usNewAPNIndex);
            if ((ulRet != VOS_OK) || (usNewAPNIndex != usOldAPNIndex))
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                             "\r\n PPP_VSNCP_CheckOptionIsChange: USM_GetApnIndexByApnName[%s] [old: %u][new: %u]fail!",
                             pstNewVsncpReqInfo->szApn, usOldAPNIndex, usNewAPNIndex);
                PPP_DBG_ERR_CNT(PPP_PHERR_696);
                return VOS_ERR;
            }
        }

        /* ��������PDN type��֮ǰ��һ�� */
        if (VSNCP_OPTION_PDNTYPE_IPV4V6 != pstNewVsncpReqInfo->ucPdnType)
        {
            if (pstNewVsncpReqInfo->ucPdnType != ucPDNType)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                             "\r\n PPP_VSNCP_CheckOptionIsChange: ucPDNType[old: %d][new: %d] is change!",
                             ucPDNType, pstNewVsncpReqInfo->ucPdnType);
                PPP_DBG_ERR_CNT(PPP_PHERR_697);
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;
}
#endif


ULONG PPP_VSNCP_ConReqPactketProc(PPPINFO_S *pstPppInfo,
                                  UCHAR *pHead,
                                  UCHAR *pPacket,
                                  ULONG ulLen)
{
    UCHAR *pucNewVsncpReq = VOS_NULL_PTR;
    UCHAR *pucOldVsncpReq = VOS_NULL_PTR;
    USHORT usPdnId = VOS_NULL_WORD;
    ULONG ulRet = 0;
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};

    /* Check OUI */
    ulRet = PPP_VSNCP_CheckOUI(pPacket, ulLen);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("PPP_VSNCP_CheckOUI fail!\r\n");

        /* �ظ�reject��Ϣ,errcodeΪ0 */
        PPP_VSNCP_SendReject(pstPppInfo, pPacket, PPP_VSNCP_GENERAL_ERROR, usPdnId);
        PPP_DBG_ERR_CNT(PPP_PHERR_698);
        return VOS_ERR;
    }

    /* ����vsncp, �����汨�� */
    pucNewPacket = PPP_VSNCP_DecodePactket(pPacket, ulLen, &usPdnId, pstPppInfo);
    if (VOS_NULL_PTR == pucNewPacket)
    {
        PPPC_WARNING_LOG("PPP_VSNCP_DecodePactket fail!\r\n");

        /* �ظ�reject��Ϣ,errcodeΪ6 */
        PPP_VSNCP_SendReject(pstPppInfo, pPacket, PPP_VSNCP_INSUFFICIENT_PARAS, usPdnId);
        PPP_DBG_ERR_CNT(PPP_PHERR_698);
        return VOS_ERR;
    }

    pstNewVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pucNewPacket);
    pucNewVsncpReq = (pucNewPacket + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));
    /* ����PDN ID��ѯPDN������ */
    ulRet = PPP_GetPDNContextByPDNID(pstNewVsncpReqInfo->ucPdnId,
                                     &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");

#if 0
        /* ����ѡ��Ԫ */
        if (VSNCP_CONFIG_REQ_OPTION_CHECK)
        {
            HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_42);
            /* �ظ�reject��Ϣ,errcodeΪ6 */
            PPP_VSNCP_SendReject(pstPppInfo,
                                 pPacket,
                                 PPP_VSNCP_INSUFFICIENT_PARAS,
                                 (USHORT)pstNewVsncpReqInfo->ucPdnId);
            PPP_Free(pucNewPacket);
            PPP_DBG_ERR_CNT(PPP_PHERR_699);
            return VOS_ERR;
        }

        /* ֪ͨPDN */
        ulRet = PDN_PppStartEhrpdPdn(pstPppInfo->ulRPIndex, (PDN_PPP_VSNCP_REQ_S *)pucNewPacket);
        if (ulRet != VOS_OK)
        {
            PPP_Free(pucNewPacket);
            PPP_DBG_ERR_CNT(PPP_PHERR_700);
        }
#endif
        return VOS_OK;
    }

#if 0
    /* �������еĻ�����Ϣ������ */
    if (VOS_NULL_PTR != pstPDNContext->stEhrpd.pucVsncpReq)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1404);
        pucOldVsncpReq = (pstPDNContext->stEhrpd.pucVsncpReq + sizeof(PDN_PPP_VSNCP_REQ_S)
                                                     + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));
        /* ���״̬ΪPPP_STATE_INITIAL,�������Ϣ�е�ID,�����Ĳ��ø���,������Ϊ�ط���ϢӦ����һ���� */
        if ((PPP_STATE_INITIAL == pstPDNContext->stEhrpd.stVSNCP.ucState)
            || (VOS_TRUE == pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag)
            || (VOS_TRUE == pstPDNContext->stEhrpd.ucbit1L2CReconnectFlg))
        {
            VSNCP_REFRESH_PACKET_ID(pucOldVsncpReq, pucNewVsncpReq);
            PPP_Free(pucNewPacket);
            PPP_DBG_OK_CNT(PPP_PHOK_1405);
            return VOS_OK;
        }
        else
        {
            PPP_Free(pucNewPacket);
        }
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1406);

        /* �����ʱ����û��ʹ��,��Ҫ�����ƿ�����Ϊʹ�� */
        if (VOS_FALSE == pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag)
        {
            pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = VOS_TRUE;
            PPP_DBG_OK_CNT(PPP_PHOK_1407);
        }

        /* ����ѡ��Ԫ */
        if (VSNCP_CONFIG_REQ_OPTION_CHECK)
        {
            HSGW_EmsTraceByPdnIndex(pstPDNContext->ulPdnIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_43);
            /* �ظ�reject��Ϣ,errcodeΪ6 */
            PPP_VSNCP_SendReject(pstPppInfo,
                                 pPacket,
                                 PPP_VSNCP_INSUFFICIENT_PARAS,
                                 (USHORT)pstNewVsncpReqInfo->ucPdnId);
            PPP_Free(pucNewPacket);
            PPP_DBG_ERR_CNT(PPP_PHERR_701);
            return VOS_ERR;
        }

        /* ������л���Ϣ�򻺴����Ϣ,�ͷ�ԭPDN���� */
        if (VSNCP_OPTION_ATTACHTYPE_HANDOFF == pstNewVsncpReqInfo->ucAttchType)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1408_L2C_RECONNECT);

            /* ������Ϣ */
            if (pstPDNContext->stEhrpd.pucVsncpReq != VOS_NULL_PTR)
            {
                PPP_Free(pstPDNContext->stEhrpd.pucVsncpReq);
                pstPDNContext->stEhrpd.pucVsncpReq = VOS_NULL_PTR;
            }
            pstPDNContext->stEhrpd.pucVsncpReq = pucNewPacket;
            pstPDNContext->stEhrpd.ucbit1L2CReconnectFlg = VOS_TRUE;

            /* �ؽ�PDN���� */
            ulRet = PDN_VsncpNotifyReconnect(pstPDNContext, (PDN_PPP_VSNCP_REQ_S *)pucNewPacket);
            if (ulRet != VOS_OK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_702);
                return VOS_ERR;
            }
            return VOS_OK;
        }

        /* ��Э�� */
        /* ����ѡ��Ԫ�Ƿ�ı� */
        ulRet = PPP_VSNCP_CheckOptionIsChange(pstNewVsncpReqInfo,
                                              VOS_NULL_PTR,
                                              pstPDNContext->stEhrpd.usApnIndex,
                                              pstPDNContext->ucPdnCapability);
        if (ulRet != VOS_OK)
        {
            HSGW_EmsTraceByPdnIndex(pstPDNContext->ulPdnIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_44);
            /* ȥ��PDN */
            PPP_Free(pucNewPacket);
            PPP_DBG_OK_CNT(PPP_PHOK_1409);
            /* ��ʼ��VSNCP���ƿ� */
            PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, pstPDNContext->stEhrpd.ucPdnId);
            if (PPP_STATE_INITIAL != stVSNCPInfo.stFsm.ucState)
            {
                PPP_VSNCP_NegotiationDown(&stVSNCPInfo);
                PPP_DBG_OK_CNT(PPP_PHOK_1410);
            }
            else
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1411);
                PPP_CORE_VSNCPFinishProc(pstPppInfo);
            }
            /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
            PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);
            return VOS_ERR;
        }

        /* ���״̬ΪPPP_STATE_INITIAL, ����Ҫ�ҵ�pdn�������� */
        if (PPP_STATE_INITIAL == pstPDNContext->stEhrpd.stVSNCP.ucState)
        {
            if (pstPDNContext->stEhrpd.pucVsncpReq != VOS_NULL_PTR)
            {
                PPP_Free(pstPDNContext->stEhrpd.pucVsncpReq);
                pstPDNContext->stEhrpd.pucVsncpReq = VOS_NULL_PTR;
            }
            pstPDNContext->stEhrpd.pucVsncpReq = pucNewPacket;
            PPP_DBG_OK_CNT(PPP_PHOK_1412);
            return VOS_OK;
        }

#if 0
        /* ���Я��PCO, ����ҪȥPGW��ȡPCO */
        if ((VSNCP_CONFIG_REQ_PCO_OPTION_FLAG)
            && (VOS_FALSE == pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag)
            && (!(SOFTPARA_BIT1455)))
        {
            ulRet = PDN_VsncpNotifyGetPCO(pstPDNContext, (PDN_PPP_VSNCP_REQ_S *)pucNewPacket);
            if (ulRet != VOS_OK)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_703);
                return VOS_ERR;
            }
            pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag = VOS_TRUE;
            return VOS_OK;
        }
        /* ������ڻ�ȡPCO���򻺴� */
        else if (VOS_TRUE == pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag)
        {
            if (pstPDNContext->stEhrpd.pucVsncpReq != VOS_NULL_PTR)
            {
                PPP_Free(pstPDNContext->stEhrpd.pucVsncpReq);
                pstPDNContext->stEhrpd.pucVsncpReq = VOS_NULL_PTR;
            }
            pstPDNContext->stEhrpd.pucVsncpReq = pucNewPacket;
            PPP_DBG_OK_CNT(PPP_PHOK_1413);
            return VOS_OK;
        }
#endif
#endif

        /* ��ʼ��VSNCP���ƿ� */
        PPP_VSNCP_Init(pstPppInfo,
                       &stVSNCPInfo,
                       pstPDNContext,
                       pstNewVsncpReqInfo->ucPdnId);

        /* �����ն˵�VSNCP���� */
        PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                                pHead,
                                pucNewVsncpReq,
                                ulLen);
        /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
        PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);
        PPP_Free(pucNewPacket);
    //}

    return VOS_OK;
}
ULONG PPP_VSNCP_CheckOUI(UCHAR *pPacket, ULONG ulLen)
{
    UCHAR *pOuiPos = VOS_NULL_PTR;
    UCHAR *pOuiByte1;
    UCHAR *pOuiByte2;
    UCHAR *pOuiByte3;

    if (ulLen < (VSNCP_HEADERLEN + VSNCP_3GPP2_OUI_LEN))
    {
        PPPC_WARNING_LOG1("PPP_VSNCP_CheckOUI pPacket Len error!\r\n", ulLen);
        return VOS_ERR;
    }

    pOuiPos = pPacket + VSNCP_HEADERLEN;

    pOuiByte1 = *pOuiPos;
    pOuiByte2 = *(pOuiPos + 1);
    pOuiByte3 = *(pOuiPos + 2);

    /* Check OUI */
    if ((VSNCP_3GPP2_OUI_BYTE_1!= pOuiByte1) || (VSNCP_3GPP2_OUI_BYTE_2!= pOuiByte2)
        || (VSNCP_3GPP2_OUI_BYTE_3!= pOuiByte3))
    {
        PPPC_WARNING_LOG3("PPP_VSNCP_CheckOUI error!\r\n",
                     pOuiByte1, pOuiByte2, pOuiByte3);
        return VOS_ERR;
    }

    return VOS_OK;
}
ULONG PPP_VSNCP_ConAckPactketProc(PPPINFO_S *pstPppInfo,
                                  UCHAR *pHead,
                                  UCHAR *pPacket,
                                  ULONG ulLen)
{
    ULONG ulRet = 0;
    UCHAR *pucNewVsncpReq = VOS_NULL_PTR;
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    USHORT usPdnId = VOS_NULL_WORD;

    /* Check OUI */
    ulRet = PPP_VSNCP_CheckOUI(pPacket, ulLen);
    if (VOS_OK != ulRet)
    {
        /* �ظ�reject��Ϣ,errcodeΪ0 */
        PPP_VSNCP_SendReject(pstPppInfo, pPacket, PPP_VSNCP_GENERAL_ERROR, usPdnId);

        PPPC_WARNING_LOG("PPP_VSNCP_CheckOUI error!\r\n");
        return VOS_ERR;
    }

    /* ����vsncp, �����汨�� */
    pucNewPacket = PPP_VSNCP_DecodePactket(pPacket, ulLen, &usPdnId, pstPppInfo);
    if (VOS_NULL_PTR == pucNewPacket)
    {
        /* ���� */
        PPPC_WARNING_LOG("PPP_VSNCP_DecodePactket error!\r\n");
        return VOS_ERR;
    }

    if (VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag)
    {
        /* ���� */
        PPP_Free(pucNewPacket);
        PPPC_WARNING_LOG("PDNID error!\r\n");
        return VOS_ERR;
    }

    pstNewVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pucNewPacket);
    pucNewVsncpReq = (pucNewPacket + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));
    /* ����PDN ID��ѯPDN������ */
    ulRet = PPP_GetPDNContextByPDNID(pstNewVsncpReqInfo->ucPdnId,
                                     &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    /* �����ʱ����û��ʹ��,ֱ�ӷ��ض��� */
    if (VOS_FALSE == pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag)
    {
        PPP_Free(pucNewPacket);
        PPPC_WARNING_LOG("stVSNCP ucUsedFlag fail!\r\n");
        return VOS_ERR;
    }

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo,
                   &stVSNCPInfo,
                   pstPDNContext,
                   pstNewVsncpReqInfo->ucPdnId);

    /* �����ն˵�VSNCP ACK */
    PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                             pHead,
                             pucNewVsncpReq,
                             ulLen);

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_Free(pucNewPacket);

    PPP_DBG_OK_CNT(PPP_PHOK_1414);
    return VOS_OK;
}




ULONG PPP_VSNCP_ConRejPactketProc(PPPINFO_S *pstPppInfo,
                                  UCHAR *pHead,
                                  UCHAR *pPacket,
                                  ULONG ulLen)
{
    ULONG ulRet = 0;
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    USHORT usPdnId = VOS_NULL_WORD;

    /* ����vsncp, �����汨�� */
    pucNewPacket = PPP_VSNCP_DecodePactket(pPacket, ulLen, &usPdnId, pstPppInfo);
    if (VOS_NULL_PTR == pucNewPacket)
    {
        /* ���� */
        PPPC_WARNING_LOG("PPP_VSNCP_DecodePactket fail!\r\n");
        return VOS_ERR;
    }

    if (VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag)
    {
        /* ���� */
        PPPC_WARNING_LOG("PDNID error!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    pstNewVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pucNewPacket);
    /* ����PDN ID��ѯPDN������ */
    ulRet = PPP_GetPDNContextByPDNID(pstNewVsncpReqInfo->ucPdnId,
                                     &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    /* ����ErrorCode */
    PPP_VSNCP_UpdateErrorCode(pstPDNContext, pstNewVsncpReqInfo->ucErrorCode);

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo,
                   &stVSNCPInfo,
                   pstPDNContext,
                   pstNewVsncpReqInfo->ucPdnId);

    /* �����ն˵�VSNCP REJECT */
    if (PPP_STATE_INITIAL != stVSNCPInfo.stFsm.ucState)
    {
        PPP_VSNCP_NegotiationDown(&stVSNCPInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1415);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1416);
        PPP_CORE_VSNCPFinishProc(pstPppInfo);
    }

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_Free(pucNewPacket);

    /* ֪ͨLCP�ظ�CNAS */
    PPPC_RespEhsmPdnConnectCmd(&stVSNCPInfo, VOS_ERROR);

    /* ���ñ�ʶλ��ָʾĿǰ�Ѳ��ڳ��Խ���Pdn���� */
    pstPDNContext->stEhrpd.stVSNCP.ucStartingFlag = VOS_FALSE;

    PPP_DBG_OK_CNT(PPP_PHOK_1417);
    return VOS_OK;
}



ULONG PPP_VSNCP_TermReqPactketProc(PPPINFO_S *pstPppInfo,
                                   UCHAR *pHead,
                                   UCHAR *pPacket,
                                   ULONG ulLen)
{
    ULONG ulRet = 0;
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    USHORT usPdnId = VOS_NULL_WORD;

    /* ����vsncp, �����汨�� */
    pucNewPacket = PPP_VSNCP_DecodePactket(pPacket, ulLen, &usPdnId, pstPppInfo);
    if (VOS_NULL_PTR == pucNewPacket)
    {
        /* ���� */
        PPPC_WARNING_LOG("PPP_VSNCP_DecodePactket fail!\r\n");
        return VOS_ERR;
    }

    if (VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag)
    {
        /* ���� */
        PPPC_WARNING_LOG("PDNID error!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    pstNewVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pucNewPacket);
    /* ����PDN ID��ѯPDN������ */
    ulRet = PPP_GetPDNContextByPDNID(pstNewVsncpReqInfo->ucPdnId,
                                     &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo,
                   &stVSNCPInfo,
                   pstPDNContext,
                   pstNewVsncpReqInfo->ucPdnId);


    /* �����ն˵�VSNCP TERM REQ */
    PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                            pHead,
                            pPacket,
                            ulLen);

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_Free(pucNewPacket);

    /* ֪ͨLCP�ظ�NAS */
    PPPC_SendEhsmPdnDisconnectNotify(usPdnId);

    PPP_DBG_OK_CNT(PPP_PHOK_1417);
    return VOS_OK;
}



ULONG PPP_VSNCP_TermAckPactketProc(PPPINFO_S *pstPppInfo,
                                   UCHAR *pHead,
                                   UCHAR *pPacket,
                                   ULONG ulLen)
{
    ULONG ulRet = 0;
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    USHORT usPdnId = VOS_NULL_WORD;

    /* ����vsncp, �����汨�� */
    pucNewPacket = PPP_VSNCP_DecodePactket(pPacket, ulLen, &usPdnId, pstPppInfo);
    if (VOS_NULL_PTR == pucNewPacket)
    {
        /* ���� */
        PPPC_WARNING_LOG("PPP_VSNCP_DecodePactket fail!\r\n");
        return VOS_ERR;
    }

    if (VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag)
    {
        /* ���� */
        PPPC_WARNING_LOG("PDNID error!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    pstNewVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)(pucNewPacket);
    /* ����PDN ID��ѯPDN������ */
    ulRet = PPP_GetPDNContextByPDNID(pstNewVsncpReqInfo->ucPdnId,
                                     &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG("PPP_GetPDNContextByPDNID fail!\r\n");
        PPP_Free(pucNewPacket);
        return VOS_ERR;
    }

    /* �����ʱ����û��ʹ��,ֱ�ӷ��ض��� */
    if (VOS_FALSE == pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag)
    {
        PPP_Free(pucNewPacket);
        PPP_DBG_ERR_CNT(PPP_PHERR_717);
        return VOS_ERR;
    }


    /* ���ñ�ʶλ��ָʾĿǰ�Ѳ��ڳ��ԶϿ�Pdn���� */
    pstPDNContext->stEhrpd.stVSNCP.ucStoppingFlag = VOS_FALSE;


    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo,
                   &stVSNCPInfo,
                   pstPDNContext,
                   pstNewVsncpReqInfo->ucPdnId);

    /* �����ն˵�VSNCP TERM ACK */
    PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                            pHead,
                            pPacket,
                            ulLen);

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_Free(pucNewPacket);

    PPP_DBG_OK_CNT(PPP_PHOK_1418);

    /* ֪ͨLCP���ͻظ���CNAS */
    PPPC_RespEhsmPdnDisconnectCmd(VOS_OK);

    /* �����������Ϣ */
    PPP_VSNCP_ClearPdnContext(pstNewVsncpReqInfo->ucPdnId);

    return VOS_OK;
}
VOID PPP_VSNCP_PactketProc(PPPINFO_S *pstPppInfo,
                           UCHAR *pHead,
                           UCHAR *pPacket,
                           ULONG ulLen,
                           UCHAR ucCode)
{
    /* �жϽ׶�״̬�Ƿ���ȷ */
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPPC_WARNING_LOG1("Phase error!\r\n", pstPppInfo->usPhase);
        return;
    }

    if (CONFREQ == ucCode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1419);
        (VOS_VOID)PPP_VSNCP_ConReqPactketProc(pstPppInfo, pHead, pPacket, ulLen);
    }
    else if (CONFREJ == ucCode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1420);
        (VOS_VOID)PPP_VSNCP_ConRejPactketProc(pstPppInfo, pHead, pPacket, ulLen);
    }
    else if (CONFACK == ucCode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1421);
        (VOS_VOID)PPP_VSNCP_ConAckPactketProc(pstPppInfo, pHead, pPacket, ulLen);
    }
    else if (TERMACK == ucCode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1422);
        (VOS_VOID)PPP_VSNCP_TermAckPactketProc(pstPppInfo, pHead, pPacket, ulLen);
    }
    else if (TERMREQ == ucCode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1423);
        (VOS_VOID)PPP_VSNCP_TermReqPactketProc(pstPppInfo, pHead, pPacket, ulLen);
    }
    else
    {
        PPPC_WARNING_LOG1("ucCode error!\r\n", ucCode);
    }

    return;
}

#if 0
#define __VSNCP_PDN_INTERFACE__


ULONG PPP_SubPDNNotifyVSNCPGetPCOSucc(ULONG ulRpIdx, UCHAR ucPDNId, UCHAR *pucPacket)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulRet = 0;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;

    if (VOS_NULL == pucPacket)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: pucPacket is null!",
                     ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_720);
        return VOS_OK;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: User %d isn't exist!",
                     ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_721);
        return VOS_ERR;
    }

    /* �ж��Ƿ�Ϊ����Э�̽׶�*/
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: usPhase[%lu] is not PPP_PHASE_NETWORK!",
                     pstPppInfo->usPhase);
        PPP_DBG_OK_CNT(PPP_PHOK_1424);
        return VOS_OK;
    }

    ulRet = PPP_VSNCP_GetPDNContextByPDNID(ulRpIdx, ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: PPP_VSNCP_GetPDNContextByPDNID fail pdnid[%d]RPindex[%lu]!",
                     ucPDNId, ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_722);
        return VOS_ERR;
    }

    if ((VOS_FALSE == pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag)
        && (VOS_FALSE == pstPDNContext->stEhrpd.ucbit1L2CReconnectFlg))
    {
        /* ���debug��Ϣ */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: ucGetPCOFlag is false!",
                     pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag);
        PPP_DBG_OK_CNT(PPP_PHOK_1425);
        return VOS_OK;
    }
    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);

    /* ��������Ϣ */
    pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)pucPacket;
    pPacket = pucPacket + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S);
    pHead = pPacket;

    /* �����ն˵�VSNCP���� */
    PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                            pHead,
                            pPacket,
                            (ULONG)(pstVsncpReqInfo->usVsncpMsgBodyLen));

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    pstPDNContext->stEhrpd.stVSNCP.ucGetPCOFlag = VOS_FALSE;
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_SubPDNNotifyVSNCPGetPCOSucc: Done!");
    PPP_DBG_OK_CNT(PPP_PHOK_1426);
    return VOS_OK;
}
ULONG PPP_SubPDNNotifyVSNCPRenegoStart(ULONG ulRpIdx, UCHAR ucPDNId)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    ULONG ulRet = 0;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPRenegoStart: User %d isn't exist!",
                     ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_723);
        return VOS_ERR;
    }

    /* �ж��Ƿ�Ϊ����Э�̽׶�*/
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPRenegoStart: usPhase[%lu] is not PPP_PHASE_NETWORK!",
                     pstPppInfo->usPhase);
        PPP_DBG_OK_CNT(PPP_PHOK_1427);
        return VOS_OK;
    }

    ulRet = PPP_VSNCP_GetPDNContextByPDNID(ulRpIdx, ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_SubPDNNotifyVSNCPRenegoStart: PPP_VSNCP_GetPDNContextByPDNID fail!");
        PPP_DBG_OK_CNT(PPP_PHOK_1428);
        return VOS_OK;
    }

    if (AM_RELCODE_PDN_HSGW_IDLETIMEOUT == pstPDNContext->usReleaseCode)
    {
        (VOID)PPP_PDNNodeAdd(pstPppInfo->ulRPIndex, pstPDNContext->ulPdnIndex, PPP_NEGO_LIST_NODE_VSNCP_RENEGO_START);
    }

    /* �����ʱvsncp�������¼���״̬˵����û���յ��û���VSNCP�������Բ���Ҫ�ٷ�����Э�� */
    if ((PPP_STATE_REQSENT == pstPDNContext->stEhrpd.stVSNCP.ucState)
        || (PPP_STATE_ACKRCVD == pstPDNContext->stEhrpd.stVSNCP.ucState))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPRenegoStart: state is not initial!",
                     pstPDNContext->stEhrpd.stVSNCP.ucState);
        PPP_DBG_OK_CNT(PPP_PHOK_1429);
        return VOS_OK;
    }

    /* ��ʼ������Ҫ��״̬����Ϣ���� */
    pstPDNContext->stEhrpd.stVSNCP.sRetransmits = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucPktId = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucState = 0;
    if (pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID)
    {
        (VOID)VOS_StopRelTimer(&(pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID));
        pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
    }
    pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = VOS_TRUE;

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);
    /* VSNCP״̬��open up��ʼЭ�� */
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR);
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_UP, VOS_NULL_PTR);

    /* �����ʱ�����ڻ��� */
    if (pstPDNContext->stEhrpd.pucVsncpReq != VOS_NULL_PTR)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1430);
        pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)pstPDNContext->stEhrpd.pucVsncpReq;
        pPacket = pstPDNContext->stEhrpd.pucVsncpReq + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S);
        pHead = pPacket;

        /* �����ն˵�VSNCP���� */
        PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                                pHead,
                                pPacket,
                                (ULONG)(pstVsncpReqInfo->usVsncpMsgBodyLen));
        PPP_Free(pstPDNContext->stEhrpd.pucVsncpReq);
        pstPDNContext->stEhrpd.pucVsncpReq = VOS_NULL_PTR;
    }

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_SubPDNNotifyVSNCPRenegoStart: Done!");
    PPP_DBG_OK_CNT(PPP_PHOK_1431);

    return VOS_OK;
}
ULONG PPP_SubPDNNotifyVSNCPStart(ULONG ulRpIdx, UCHAR ucPDNId, UCHAR *pucPacket)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    UCHAR *pHead = VOS_NULL_PTR;
    UCHAR *pPacket = VOS_NULL_PTR;
    ULONG ulRet = 0;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;


    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPStart: User %d isn't exist!",
                     ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_724);
        return VOS_ERR;
    }

    /* �ж��Ƿ�Ϊ����Э�̽׶�*/
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPStart: usPhase[%lu] is not PPP_PHASE_NETWORK!",
                     pstPppInfo->usPhase);
        PPP_DBG_OK_CNT(PPP_PHOK_1432);
        return VOS_OK;
    }

    ulRet = PPP_VSNCP_GetPDNContextByPDNID(ulRpIdx, ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_SubPDNNotifyVSNCPStart: PPP_VSNCP_GetPDNContextByPDNID fail pdnid[%d]RPindex[%lu]!",
                     ucPDNId, ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_725);
        return VOS_ERR;
    }


    /* ��ʼ������Ҫ��״̬����Ϣ���� */
    pstPDNContext->stEhrpd.stVSNCP.sRetransmits = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucPktId = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucState = 0;
    pstPDNContext->stEhrpd.stVSNCP.ulTimeOutID = 0;
    pstPDNContext->stEhrpd.stVSNCP.ucUsedFlag = VOS_TRUE;

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);
    /* VSNCP״̬��open up��ʼЭ�� */
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_OPEN, VOS_NULL_PTR);
    PPP_VSNCP_ReceiveEventFromCore(&stVSNCPInfo, (ULONG)PPP_EVENT_FSM_UP, VOS_NULL_PTR);

    /* ��������Ϣ */
    if (pucPacket != VOS_NULL_PTR)
    {
        pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)pucPacket;
        pPacket = pucPacket + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S);
        pHead = pPacket;

        /* �����ն˵�VSNCP���� */
        PPP_VSNCP_ReceivePacket(&stVSNCPInfo,
                                pHead,
                                pPacket,
                                (ULONG)(pstVsncpReqInfo->usVsncpMsgBodyLen));

    }

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_SubPDNNotifyVSNCPStart: Done!");
    PPP_DBG_OK_CNT(PPP_PHOK_1433);
    return VOS_OK;
}


UCHAR PPP_VSNCP_SetRejectCodeByReleaseCode(ULONG ulReleaseCode)
{
    UCHAR ucErrCode = 0;

    if ((ulReleaseCode >= AM_RELCODE_DNS_ERR) && (ulReleaseCode <= AM_RELCODE_DNS_SORT_ERR))
    {
		return PPP_VSNCP_NO_PGW;
    }

    switch (ulReleaseCode)
    {
        case AM_RELCODE_PMIPV6_LMA_TOUT :
            ucErrCode = PPP_VSNCP_PGW_UNREACHABLE;
            PPP_DBG_OK_CNT(PPP_PHOK_1434);
            break;
        case AM_RELCODE_PMIPV6_INNER_ERR :
            ucErrCode = PPP_VSNCP_ADMIN_PROHIBITED;
            PPP_DBG_OK_CNT(PPP_PHOK_1435);
            break;
        case AM_RELCODE_PMIPV6_LMA_FAIL :                     /* lma����ʧ�� */
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1436);
            break;
        case AM_RELCODE_PMIPV6_LMA_CHECK_ERR :               /* lma��Ϣ���ʧ�� */
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1437);
            break;
        case AM_RELCODE_PMIPV6_LIFE_TOUT :                   /* lifetime��ʱ */
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1438);
            break;
        case AM_RELCODE_PMIPV6_PGW_REL_NORMAL :               /* PGW��������ȥ�� */
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1439);
            break;
        case AM_RELCODE_PMIPV6_PGW_REL_SAME_HAND :            /* PGW����ȥ�� - HSGW���л�*/
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1440);
            break;
        case AM_RELCODE_PMIPV6_PGW_REL_DIFF_HAND :           /* PGW����ȥ�� - �����л�*/
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1441);
            break;
        case AM_RELCODE_PMIPV6_PGW_REL_UNKNOWN_HAND :         /* PGW����ȥ�� - δ֪�л�*/
            ucErrCode = PPP_VSNCP_PGW_REJECT;
            PPP_DBG_OK_CNT(PPP_PHOK_1442);
            break;
        case AM_RELCODE_PDN_COMMAND :
            PPP_DBG_OK_CNT(PPP_PHOK_1443);
            ucErrCode = PPP_VSNCP_ADMIN_PROHIBITED;
            break;
        case AM_RELCODE_PDN_DUALSTACK_LICENSE_FAIL:
            PPP_DBG_OK_CNT(PPP_PHOK_1444);
            ucErrCode = PPP_VSNCP_RES_UNAVAILABLE;
            break;
        case AM_RELCODE_SUBNET_INVAILD_PGW:
            PPP_DBG_OK_CNT(PPP_PHOK_1445);
            ucErrCode = PPP_VSNCP_NO_PGW;
            break;

        case AM_RELCODE_SUBNET_HSGWPCC_LICE:
            PPP_DBG_OK_CNT(PPP_PHOK_1446);
            ucErrCode = PPP_VSNCP_RES_UNAVAILABLE;       /*HSGW PCC license��Դ����*/
            break;

        default:
            PPP_DBG_OK_CNT(PPP_PHOK_1447);
            ucErrCode = PPP_VSNCP_ADMIN_PROHIBITED;
            break;
    }

    return ucErrCode;
}


ULONG PPP_SubPDNNotifyVSNCPStop(ULONG ulRpIdx, UCHAR ucPDNId, ULONG ulReleaseCode)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};
    ULONG ulRet = 0;
    UCHAR ucErrCode = 0;
    PDN_CONTEXT_S *pstPDNContext = VOS_NULL_PTR;
    UCHAR eAlarmCode = FSM_ALARM_NULL;

    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIdx);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPStop: User %d isn't exist!",
                     ulRpIdx);
        PPP_DBG_ERR_CNT(PPP_PHERR_726);
        return VOS_ERR;
    }

    ulRet = PPP_VSNCP_GetPDNContextByPDNID(ulRpIdx, ucPDNId, &pstPDNContext);
    if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_SubPDNNotifyVSNCPStop: PPP_VSNCP_GetPDNContextByPDNID fail!");
        PPP_DBG_ERR_CNT(PPP_PHERR_727);
        return VOS_ERR;
    }

    /* �ж��Ƿ�Ϊ����Э�̽׶�*/
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        /* ���debug��Ϣ */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_SubPDNNotifyVSNCPStop: usPhase[%lu] is not PPP_PHASE_NETWORK!",
                     pstPppInfo->usPhase);
        PPP_DBG_OK_CNT(PPP_PHOK_1448);
        return VOS_ERR;
    }

    /* ����ȥ��ԭ��ֵ��ȡ �澯ԭ��ֵ */
    SNMP_GetFailReasonByReleaseCode(ulReleaseCode, &eAlarmCode);
    /* ��������ͳ��ȥ��ԭ�� */
    if ( FSM_ALARM_NULL != eAlarmCode )
    {
        SNMP_SetFailReason(pstPppInfo, (FSM_ALARM_CODE_E)eAlarmCode);
    }

    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, ucPDNId);

    /* ����vsncp term��Ϣ */
    if (PPP_STATE_INITIAL != stVSNCPInfo.stFsm.ucState)
    {
        PPP_VSNCP_NegotiationDown(&stVSNCPInfo);
        PPP_DBG_OK_CNT(PPP_PHOK_1449);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1450);

        ucErrCode = PPP_VSNCP_SetRejectCodeByReleaseCode(ulReleaseCode);
        PPP_PDNSendVSNCPReject(pstPDNContext->ulRpIndex,
                               pstPDNContext->stEhrpd.pucVsncpReq,
                               ucErrCode);

        PPP_CORE_VSNCPFinishProc(pstPppInfo);
    }

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_SubPDNNotifyVSNCPStop Done!");
    return VOS_OK;
}
VOID PPP_PDNSendVSNCPReject(ULONG ulRPIndex,
                            UCHAR *pucMsg,
                            UCHAR ucErrCode)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    UCHAR *pucVsncpReq = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstVsncpReqInfo = VOS_NULL_PTR;

    if ((ulRPIndex > PPP_MAX_USER_NUM)
        || (VOS_NULL_PTR == pucMsg))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_PDNSendVSNCPReject :ulRPIndex is invalid! error, %lu, %x",
                     ulRPIndex, pucMsg);
        PPP_DBG_ERR_CNT(PPP_PHERR_728);
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulRPIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n[ppp]: PPP_PDNSendVSNCPReject: rpindex[%lu] pstPppInfo is NULL!",
                      ulRPIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_729);
        return;
    }
    pstVsncpReqInfo = (PDN_PPP_VSNCP_REQ_S *)pucMsg;
    pucVsncpReq = (pucMsg + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));

    PPP_VSNCP_SendReject(pstPppInfo, pucVsncpReq, ucErrCode, (USHORT)pstVsncpReqInfo->ucPdnId);

    PPP_DBG_OK_CNT(PPP_PHOK_1451);
    return;
}



VOID PPP_PDNClearVSNCP(PDN_CONTEXT_S *pstPDNContext)
{
    PPPINFO_S *pstPppInfo = VOS_NULL_PTR;
    PPPVSNCPINFO_S stVSNCPInfo = {0};

    if (VOS_NULL_PTR == pstPDNContext)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_PDNClearVSNCP :pstPDNContext is NULL! ");
        PPP_DBG_ERR_CNT(PPP_PHERR_730);
        return;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, pstPDNContext->ulRpIndex);
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_PDNClearVSNCP: User %d isn't exist!",
                     pstPDNContext->ulRpIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_731);
        return ;
    }
    /* ��ʼ��VSNCP���ƿ� */
    PPP_VSNCP_Init(pstPppInfo, &stVSNCPInfo, pstPDNContext, pstPDNContext->stEhrpd.ucPdnId);

    PPP_VSNCP_Clear(&stVSNCPInfo, pstPDNContext);

    /* vsncp״̬��������Ϻ�ˢ��pdn�������е�״̬��Ϣ */
    PPP_VSNCP_FreshPDNContext(&stVSNCPInfo, pstPDNContext, pstPppInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n [ppp]PPP_PDNClearVSNCP :success! ");
    PPP_DBG_OK_CNT(PPP_PHOK_1452);
    return;
}
#endif


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
