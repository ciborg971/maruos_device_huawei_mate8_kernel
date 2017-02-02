

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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_IPV6CP_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* IPV6CP�ص��������ݽṹ */
PPPFSMCALLBACK_S g_stIpv6cpCallbacks =
{
    /* ������Э�̱��Ĵ��� */
    PPP_IPV6CP_resetci,   /* ����������Ϣ����Э�̳�ʼֵ */
    PPP_IPV6CP_cilen,      /* ��Ҫ���͵�request���ĳ��� */
    PPP_IPV6CP_addci,     /* ��֯Э�̱��� */
    PPP_IPV6CP_ackci,      /* ����Է���ack���� */
    PPP_IPV6CP_nakci,      /* ����Է���nak���� */
    PPP_IPV6CP_rejci,       /* ����Է���reject���� */
    PPP_IPV6CP_reqci,      /* ����Է���request���� */
    NULL,                            /* extcode����,����Э�����еı���.
                                              IPCPû���������ͱ���,��˲��ṩ�������*/

    /* �¼���Э��ת������ֹ״̬ */
    PPP_IPV6CP_up,           /* Э��up */
    PPP_IPV6CP_down,       /* Э����ʱdown,����Ҫ����Э��.
                                                ��finished��������:����PPPOE��DDR�ȵ������
                                                ����֪ͨ�²�����· */
    PPP_IPV6CP_finished,   /* Э�������֪ͨ�²�:�����·.����IPCP,����֪ͨ
                                                 LCP:���û�����������Э��,��LCP����down��*/
    PPP_IPV6CP_starting,   /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                                               ����������Э��,�����,�뷢һ��up�¼�.
                                               Э����������û�о���涨,���Բ�ʵ��*/

    /* ��Э����Ϣ */
    "IPV6CP"                       /* ��Э���� */
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��IPCP�����ⲿ�¼�.�¼�������Up��Down��Open��Close           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                ulCmd:������,����Ϊ����ֵ:                                 *
*                      PPPFSMLOWERDOWN:�²�Down                             *
*                      PPPFSMLOWERUP:�²�Up                                 *
*                      PPPFSMOPEN:Open�¼�                                  *
*                      PPPFSMCLOSE:Down�¼�                                 *
*                pPara:�¼��Ĳ���,ΪNULL                                    *
* OUTPUT       ��                                                           *
* RETURN       ��NULL                                                       *
* CALLED BY    ��PPP_Core_ReceiveEventFromShell��PPP_Core_RejectProtocol    *
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp�����޸�
****************************************************************************/
VOID PPP_IPV6CP_ReceiveEventFromCore (VOID *pstIpcpInfo, ULONG ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;
    PPPIPV6CPINFO_S *pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstIpcpInfo;
    PPPINFO_S *pstPppInfo = NULL;

    VOS_DBGASSERT(pstIpcpInfo);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n---Into PPP_IPV6CP_ReceiveEventFromCore ulCmd %d---\r\n", ulCmd);
    if (NULL == pstIpcpInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstPppInfo = pstIpv6cpInfo->pstPppInfo;
    if ( NULL == pstPppInfo )
    {
        VOS_DBGASSERT(0);
        return;
    }
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        /* ipv6����ͳ��,IPv6CPЭ�̳��Դ��� */
        PPP_DBG_OK_CNT(PPP_PHOK_901);
        IPV6_PerfStatistic(IPV6_IPV6CP_ATTEMPT);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_IPV6CP_ReceiveEventFromCore,IPV6_PerfStatistic Attempt: enter!");

        A11_OM_PerfStatisticPCFUnit((ULONG)PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM, pstPppInfo->ulPcfIP);
    }

    pstFsm = &(((PPPIPV6CPINFO_S*)pstIpcpInfo)->stFsm);

    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��IPCP���ձ���                                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstIpcpInfo:IPCP���ƿ�                                     *
*                pHead:��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�              *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp�����޸�
****************************************************************************/
VOID PPP_IPV6CP_ReceivePacket (VOID *pstIpV6cpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPFSM_S *pstFsm;
    VOS_UINT8 ucPppId;

    VOS_DBGASSERT(pstIpV6cpInfo);
    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);

    pstFsm = &(((PPPIPV6CPINFO_S*)pstIpV6cpInfo)->stFsm);

    ucPppId = PPPC_GetCurrentPppId();
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, ucPppId);

    return;
}

/****************************************************************************
* CREATE DATE  ��                                                *
* CREATED BY   ��                                               *
* FUNCTION     ��ȷ��IPv6CP��ҪЭ����Щ����,��IPv6CP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��״̬����ִ��tls�����ĺ�PPP_FSM_tls                         *
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp�����޸�
****************************************************************************/
VOID PPP_IPV6CP_resetci(PPPFSM_S *pstFsm)
{
    PPPINFO_S           *pstPppInfo;
    PPPRENOGOINFO       *pstPppRenegoInfo;
    PPPIPV6CPINFO_S     *pstInfo;
    PPPCONFIGINFO_S     *pstConfig;
    PPP_IPV6CP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstHisOptions;

    pstInfo = (PPPIPV6CPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstInfo->pstPppInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;

    pstAllowOptions = &(pstInfo->stAllowOptions);
    pstWantOptions = &(pstInfo->stWantOptions);
    pstGotOptions = &(pstInfo->stGotOptions);
    pstHisOptions = &(pstInfo->stHisOptions);

    /* pstWantOptions��ouraddr��hisaddr��PPP_IPCP_Init���Ѿ���ʼ�� */

    /* ��������ȱʡֵ */
    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 0;
    pstWantOptions->req_dnsaddr0  = 0;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 0;
    pstWantOptions->req_dnsaddr1     = 0;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 0;
    pstAllowOptions->req_dnsaddr0  = 0;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 0;
    pstAllowOptions->req_dnsaddr1     = 0;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;  /* modified by gxf 20030414 �����ܶԷ���DNS */
    pstAllowOptions->accept_dnsaddr1  = 0;  /* modified by gxf 20030414 �����ܶԷ���DNS */
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
    if (pstPppRenegoInfo && pstPppRenegoInfo->ucIpV6cpFlag)
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&pstPppRenegoInfo->stIpcpV6Options, sizeof(PPP_IPV6CP_OPTION_S));
        *pstWantOptions = *pstGotOptions;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������Ҫ���͵�Config Request�������ݲ��ֳ���                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
* OUTPUT       ��                                                           *
* RETURN       ��Config Request���ĳ���                                     *
* CALLED BY    ��PPP_FSM_SendConfigReq                                      *
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp�����޸�
****************************************************************************/
USHORT PPP_IPV6CP_cilen(PPPFSM_S *pstFsm)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */
    return (USHORT)(IPV6CP_LENCIADDR(pstGotOptions->neg_addr, pstGotOptions->old_addrs) +
                   IPV6CP_LENCIVJ(pstGotOptions->neg_vj));
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����֯һ��Config Request��������                             *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
* OUTPUT       ��                                                           *
*                pPacket:��װ�õı���                                       *
* RETURN       ��                                                           *
* CALLED BY    ��PPP_FSM_SendConfigReq                                      *
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp�����޸�
****************************************************************************/
VOID PPP_IPV6CP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    ADDCIADDRV6(IPV6CP_CI_ADDR,
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->OurV6InId,
              pstGotOptions->HisV6InId
    );

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������յ���Config ACK����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���ACK����;VOS_ERR:�Ƿ���ACK����                 *
* CALLED BY    ��                                     *
 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cpЭ�����½������
****************************************************************************/
USHORT PPP_IPV6CP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype;
    USHORT ciusINid[4] = {0};
    ULONG ulResult1 ,ulResult2;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * CIs must be in exactly the same order that we sent...
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /* We allow the configuration length is 0. */
    if (ulLen == 0)
    {
        return VOS_OK;
    }

    /*lint -e63*/
    ACKCIADDRV6(IPV6CP_CI_ADDR,
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->OurV6InId,
              pstGotOptions->HisV6InId
    );
    /*lint +e63*/

    ulResult1= PPP_ipv6_intfid_check(pstGotOptions->OurV6InId,IPV6_ADDR_LEN);
    ulResult2 = (ULONG)VOS_MemCmp((VOS_VOID *)ciusINid, (VOS_VOID *)pstGotOptions->OurV6InId, IPV6_ADDR_LEN);

    /*���Ƿ����pdsn�ӿ�id��Ч����ack�е�idͬ���Ƿ���Ľӿ�id��һ��*/
    /*lint -e801*/
    if ((ulResult2 != VOS_OK) || (ulResult1))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_220);
        goto bad;
    }

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_221);
        goto bad;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_ackci: received bad Ack!");
    return VOS_ERR;
    /*lint +e801*/
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������յ���Config Nak����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���NAK����;VOS_ERR:�Ƿ���NAK����                 *
* CALLED BY    ��PPP_FSM_ReceiveConfNakRej                                  *
 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�����Ͻ����޸�
****************************************************************************/
USHORT PPP_IPV6CP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S stNoOption;  /* ���Է�no����ѡ�� */
    PPP_IPV6CP_OPTION_S stTryOption; /* ������Է�Э�̵�ѡ�� */

    UCHAR citype, cilen, *next;
    USHORT ciaddr1[IPV6_ADDR_LEN_INTER], ciaddr2[IPV6_ADDR_LEN_INTER];
    ULONG ulResult1 = VOS_ERR;
    ULONG ulResult2 = VOS_ERR;

    pstGotOptions  = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_IPV6CP_OPTION_S));
    stTryOption = *pstGotOptions;

    /*
     * Any Nak'd CIs must be in exactly the same order that we sent.
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /*
     * Accept the peer's idea of {our,his} address, if different
     * from our idea, only if the accept_{local,remote} flag is set.
     */
    ulResult1 = PPP_ipv6_intfid_check(pstWantOptions->OurV6InId, IPV6_ADDR_LEN);
    NAKCIADDRV6(IPV6CP_CI_ADDR, neg_addr, pstGotOptions->old_addrs,
              if (VOS_OK == ulResult1)/*���Ƿ����id��Ч*/
              {
                  stTryOption.neg_addr = 0;
              }

              ulResult2 = PPP_ipv6_intfid_check(ciaddr1,IPV6_ADDR_LEN);

              if (ulResult1 && (!ulResult2)) /*���Ƿ����id��Ч����nak�е�id��Ч*/
              { /* Do we know our address? */
                  VOS_MemCpy((void*)(stTryOption.OurV6InId),(void *)ciaddr1,IPV6_ADDR_LEN);
              }
    );

    /*
     * Accept the peer's value of maxslotindex provided that it
     * is less than what we asked for.  Turn off slot-ID compression
     * if the peer wants.  Send old-style compress-type option if
     * the peer wants.
     */


    /*
     * There may be remaining CIs, if the peer is requesting negotiation
     * on an option that we didn't include in our request packet.
     * If they want to negotiate about IP addresses, we comply.
     * If they want us to ask for compression, we refuse.
     */
    /*lint -e801*/
    while (ulLen > IPCP_CILEN_VOID)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);
        if (cilen < 2)/*���ӶԷǷ�����������Ĵ���*/
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_222);
            goto bad;
        }

        ulLen = (ULONG)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_223);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case IPCP_CI_COMPRESSTYPE:
                if (pstGotOptions->neg_vj || stNoOption.neg_vj
               || ((cilen != IPCP_CILEN_VJ) && (cilen != IPCP_CILEN_COMPRESS)))
                {
                    goto bad;
                }

                stNoOption.neg_vj = 1;
                break;
            case IPV6CP_CI_ADDR:
                if (pstGotOptions->neg_addr || stNoOption.neg_addr || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_224);
                    goto bad;
                }

                PPP_GETCHARPTR(ciaddr1, pPacket,IPV6_ADDR_LEN);
                ulResult1 = PPP_ipv6_intfid_check(ciaddr1,IPV6_ADDR_LEN);
                ulResult2 = PPP_ipv6_intfid_check(pstWantOptions->OurV6InId, IPV6_ADDR_LEN);
                if ((!ulResult1) && (ulResult2))
                {
                    VOS_MemCpy((void*)(stTryOption.OurV6InId),(void *)ciaddr1,IPV6_ADDR_LEN);
                    stTryOption.neg_addr = 1;
                }

                stNoOption.neg_addr = 1;
                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_225);
        goto bad;
    }

    /*
     * OK, the Nak is good.  Now we can update state.
     */
    if (pstFsm->ucState != (LONG)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_nakci: received bad Nak!");
    return VOS_ERR;
    /*lint +e801*/
}
USHORT PPP_IPV6CP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    USHORT ciaddr[IPV6_ADDR_LEN_INTER];
    PPP_IPV6CP_OPTION_S stTryOption;      /* options to request next time */
    UCHAR cilen = 0;

    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    /*lint -e821*/
    /*lint -e63*/
    REJCIADDRV6(IPV6CP_CI_ADDR,
                neg_addr,
                pstGotOptions->old_addrs,
                pstGotOptions->OurV6InId,
                pstGotOptions->HisV6InId
               );
    /*lint +e63*/
    /*lint +e821*/

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_226);
        goto bad;
    }
    /*lint +e801*/

    /*
     * Now we can update state.
     */
    if (pstFsm->ucState != (LONG)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_rejci: received bad Reject!");

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : PPP_IPCP_IsSip
 ��������  : �ж�IPCP��������Ƿ���IPѡ��У���SIP��������MIP
 �������  : UCHAR *pPacket
             ULONG *pulLen
 �������  : ��
 �� �� ֵ  : 1: SIP  0: MIP
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��4��15��
    ��    ��   : gxf
    �޸�����   : �����ɺ���
 �޸���ʷ      :
    ��    ��   : 2009��12��24��
    ��    ��   : ZHAICHAO
    �޸�����   : ����ipv6cpЭ���޸ĵ�ַ����
*****************************************************************************/
UCHAR PPP_IPV6CP_IsSip(UCHAR *pPacket, ULONG *pulLen)
{
    UCHAR *p;              /* Pointer to current and next CIs */
    USHORT cilen, citype;   /* Parsed len, type */
    ULONG l = *pulLen;      /* Length left */

    p = pPacket;

    while (l)
    {
        if ((l < 2)           /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        {
            /*  CI length too big? */
            PPP_DBG_OK_CNT(PPP_PHOK_902);
            return 0;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l -= cilen;                 /* Adjust remaining length */
        p += (cilen - 2);           /* Step to next CI */

        if (citype == IPV6CP_CI_ADDR)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_903);
            return 1;
        }
    }

    return 0;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������յ���config Request����                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                pulLen: ���ĳ���                                           *
* OUTPUT       ��                                                           *
*                pPacket:Ҫ�����Է��ı���(ACK��NAK��REJ)����                *
*                pulLen: Ҫ�����Է��ı��ĵĳ���                             *
* RETURN       �������Է��ı�������:CONFACK��CONFNAK����CONFREJ             *
* CALLED BY    ��
 �޸���ʷ      :
  1.��    ��   : 2009��12��24��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸�
****************************************************************************/
UCHAR PPP_IPV6CP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG *pulLen)
{
    PPP_IPV6CP_OPTION_S *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions;
    PPP_IPV6CP_OPTION_S *pstHisOptions;
    PPPINFO_S *pstPppInfo = NULL;

    UCHAR *cip, *next, *p;     /* Pointer to current and next CIs */
    USHORT cilen, citype;   /* Parsed len, type */
    USHORT ciaddr1[IPV6_ADDR_LEN_INTER]; /*interface id*/
    UCHAR rc = CONFACK;     /* Final packet return code */
    UCHAR orc;          /* Individual option return code */
    UCHAR *ucp = pPacket;       /* Pointer to current output char */
    long l = (long)*pulLen;       /* Length left */
    UCHAR ucresultaaa;
    UCHAR ucRetUsr;

    pstWantOptions  = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);
    pstGotOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPIPV6CPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);

    /*
     * Reset all his options.
     */
    (VOID)VOS_MemSet(pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));

    /* �ж�SIP/MIP */
    if (!PPP_IPV6CP_IsSip(pPacket, pulLen))
    {
    }

    /*
     * Process all his options.
     */
    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_904);
        return rc;
    }

    next = pPacket;

    while (l)
    {
        orc = CONFACK;          /* Assume success */
        cip = p = next;         /* Remember begining of CI */
        if ((l < 2)               /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        /*lint -e801*/
        {
            /*  CI length too big? */
            orc   = CONFREJ;    /* Reject bad CI */
            cilen = (USHORT)l;          /* Reject till end of packet */
            l = 0;          /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_905);
            goto endswitch;
        }
        /*lint +e801*/

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l    -= cilen;      /* Adjust remaining length */
        next += cilen;          /* Step to next CI */

        switch (citype)
        {
            case IPV6CP_CI_ADDR:

                if (!pstWantOptions->neg_addr
                     || (cilen != IPV6CP_CILEN_ADDR))
                {
                    /* Check CI length */
                    orc = CONFREJ;  /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_227);
                    break;
                }

                PPP_GETCHARPTR(ciaddr1, p, IPV6_ADDR_LEN);/* Parse source address (his) */

                /*�ӿ�id��ȡ����
                1�� AAA�·�
                2�� �ն�IPCPV6Э��������Я��
                3�� PDSN����
                */
                ucresultaaa = (UCHAR)PPP_ipv6_intfid_check(pstWantOptions->HisV6InId, IPV6_ADDR_LEN);
                pstHisOptions->neg_addr = 1;
                if (VOS_OK == ucresultaaa)/*aaa�·��˽ӿ�id*/
                {
                    /*�յ��ӿ�idͬaaa�·��Ľӿ�id��ͬ��ظ�ack������aaa�·��Ľӿ�idͨ��nak���͸��Է�*/
                    if ((ciaddr1[0] == pstWantOptions->HisV6InId[0])
                        &&(ciaddr1[1] == pstWantOptions->HisV6InId[1])
                        &&(ciaddr1[2] == pstWantOptions->HisV6InId[2])
                        &&(ciaddr1[3] == pstWantOptions->HisV6InId[3]))
                    {
                        pstGotOptions->neg_addr = 1;
                        VOS_MemCpy(pstHisOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        VOS_MemCpy(pstGotOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
                        if ( NULL!= pstPppInfo )
                        {
                            VOS_MemCpy((void *)(pstPppInfo->usPeerIPv6Addr + 4), (void*)ciaddr1, IPV6_ADDR_LEN);
                        }
                    }
                    else
                    {
                        PPP_DBG_OK_CNT(PPP_PHOK_906);
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(IPV6_ADDR_LEN, p);
                        PPP_PUTCHARPTR(pstWantOptions->HisV6InId, p,IPV6_ADDR_LEN);
                    }
                }
                else /*aaa û���·��ӿ�id ��ʹ�ñ�������*/
                {
                    /* �û�Я�����ҺϷ� */
                    ucRetUsr = (UCHAR)PPP_ipv6_intfid_check(ciaddr1, IPV6_ADDR_LEN);
                    if (VOS_OK == ucRetUsr)
                    {
                        pstGotOptions->neg_addr = 1;
                        VOS_MemCpy(pstHisOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);
                        VOS_MemCpy(pstGotOptions->HisV6InId, ciaddr1, IPV6_ADDR_LEN);

                        VOS_MemCpy((void *)(pstWantOptions->HisV6InId), (void*)ciaddr1, IPV6_ADDR_LEN);
                        pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
                        if ( NULL!= pstPppInfo )
                        {
                            VOS_MemCpy((void *)(pstPppInfo->usPeerIPv6Addr + 4), (void*)ciaddr1, IPV6_ADDR_LEN);
                        }

                    }
                    else
                    {
                        PPP_DBG_OK_CNT(PPP_PHOK_907);
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(IPV6_ADDR_LEN, p);
                        PPP_PUTCHARPTR(pstWantOptions->ConfigV6InId, p,IPV6_ADDR_LEN);

                        VOS_MemCpy((void *)(pstWantOptions->HisV6InId), (void*)pstWantOptions->ConfigV6InId, IPV6_ADDR_LEN);
                    }

                }
                break;
            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_228);
                orc = CONFREJ;
                break;
        }

endswitch:
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_IPV6CP_reqci: orc=%d , rc=%d, l = %d!",
                 orc, rc , l);

        if ((orc == CONFACK)          /* Good CI */
           && (rc != CONFACK))
        {
            /*  but prior CI wasnt? */
            continue;
        }                   /* Don't send this one */

        if (orc == CONFNAK)
        {
            /* Nak this CI? */
            if (rc == CONFREJ)
            {
                /* Rejecting prior CI? */
                continue;
            }                   /* Don't send this one */
            if (rc == CONFACK)
            {
                /* Ack'd all prior CIs? */
                rc  = CONFNAK;  /* Not anymore... */
                ucp = pPacket;      /* Backup */
            }
        }

        if ((orc == CONFREJ)          /* Reject this CI */
           && (rc != CONFREJ))
        {
            /*  but no prior ones? */
            rc  = CONFREJ;
            ucp = pPacket;          /* Backup */
        }

        /* Need to move CI? */
        if (ucp != cip)
        {
            (VOID)VOS_MemCpy(ucp, cip, (ULONG)cilen);
        }                                              /* Move it */

        /* Update output pointer */
        PPP_INCPTR(cilen, ucp);
    }

    *pulLen = (ULONG)(ucp - pPacket);           /* Compute output length */
    return (rc);            /* Return final code */
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬��up�Ĵ�����                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tlu������(PPP_FSM_tlu)����             *
 �޸���ʷ      :
  1.��    ��   : 2009��12��26��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸Ķ���
****************************************************************************/
VOID PPP_IPV6CP_up(PPPFSM_S *pstFsm)
{
    ULONG ulAccept;

    /* IPCPЭ�̽���Ƿ���Խ��� */
    ulAccept = PPP_IPV6CP_UpResetCi((PPPINFO_S *)pstFsm->pPppInfo);

    if (ulAccept == VOS_OK)
    {
        /* Э�̽�����Խ���,���ں˷���Ipcp Up�¼� */
        PPP_Core_ReceiveEventFromProtocol((PPPINFO_S *)pstFsm->pPppInfo,
                                          (LONG)PPP_EVENT_IPV6CPUP,
                                          NULL);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_229);
        /* Э�̽�����ɽ���,����Э�� */
        PPP_IPV6CP_NegotiationDown(pstFsm->pProtocolInfo);
    }
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬��down�Ĵ�����                                       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tld������(PPP_FSM_tld)����             *
 �޸���ʷ      :
  1.��    ��   : 2009��12��26��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸Ķ���

****************************************************************************/
VOID PPP_IPV6CP_down(PPPFSM_S *pstFsm)
{
    /* �ش���ʱ����PPP_FSM_tld���Ѿ�ɾ�� */

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPDOWN,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬��finished�Ĵ�����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tlf������(PPP_FSM_tlf)����             *
 �޸���ʷ      :
  1.��    ��   : 2009��12��26��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸Ķ���

****************************************************************************/
VOID PPP_IPV6CP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPFINISHED,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬��starting�Ĵ�����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tls������(PPP_FSM_tls)����             *
 �޸���ʷ      :
  1.��    ��   : 2009��12��26��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸Ķ���

****************************************************************************/
VOID PPP_IPV6CP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPV6CPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ��2009/12/23                                                 *
* CREATED BY   ��zhaichao                                                 *
* FUNCTION     ����ʼ��IPv6CP���ƿ�                                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                ausMyIpAddr:�ҵ�IP��ַ                                      *
*                ausPeerIpAddr:������Է���IP��ַ                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��                                                           *
 �޸���ʷ      :
  1.��    ��   : 2009��12��23��
    ��    ��   : zhaichao
    �޸�����   : ���ipv6cp��ipv4�Ͻ����޸Ķ���

****************************************************************************/
VOID PPP_IPV6CP_Init(PPPINFO_S* pstPppInfo, USHORT *ausMyIpAddr, USHORT *ausPeerIpAddr)
{
    PPPFSM_S            *pstFsm;
    PPPIPV6CPINFO_S     *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPV6CP_OPTION_S *pstGotOptions, *pstHisOptions;


    if ((NULL == pstPppInfo) || (NULL == pstPppInfo->pstIpV6cpInfo))
    {
        return;
    }

    pstIpv6cpInfo = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;
    pstFsm = &(pstIpv6cpInfo->stFsm);
    pstPppInfo->bPppStateFlgV6 = PPP_STATE_NEGOING;

    /* IPCP���ƿ��ʼ�� */
    pstIpv6cpInfo->pstPppInfo = pstPppInfo;

    if (1 != pstIpv6cpInfo->ucUsedFlag)
    {
        pstIpv6cpInfo->ucUsedFlag = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_908);

    }

    /* ״̬����ʼ�� */
    pstFsm->usProtocol    = PPP_IPV6CP;
    pstFsm->pstCallBacks  = &g_stIpv6cpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstIpv6cpInfo;
    pstFsm->pPppInfo = (char*)pstIpv6cpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);

    /* Э�̲�����ʼ�� */
    pstAllowOptions = &(pstIpv6cpInfo->stAllowOptions);
    pstWantOptions = &(pstIpv6cpInfo->stWantOptions);
    pstGotOptions = &(pstIpv6cpInfo->stGotOptions);
    pstHisOptions = &(pstIpv6cpInfo->stHisOptions);

    if (0 == pstPppInfo->bPppClient)
    {
        /*������ҪЭ�̵��ǽӿ�id����������ȫ��ipv6��ַ,�Զ˽ӿ�id��ʼֵΪfffffffffe*/
        VOS_MemCpy((void*)(pstWantOptions->OurV6InId),(void *)(&ausMyIpAddr[4]),IPV6_ADDR_LEN);

        /*aaa�·��ӿ�id��ʹ��aaa�ķ���ȡ��������*/
        if (VOS_OK == PPP_ipv6_intfid_check(ausPeerIpAddr + 4, IPV6_ADDR_LEN))
        {
            VOS_MemCpy((void*)(pstWantOptions->HisV6InId),(void *)(ausPeerIpAddr + 4),IPV6_ADDR_LEN);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n PPP_IPV6CP_Init: peer interface id = %x %x %x %x ",
                                                (ausPeerIpAddr + 4)[0],
                                                (ausPeerIpAddr + 4)[1],
                                                (ausPeerIpAddr + 4)[2],
                                                (ausPeerIpAddr + 4)[3]);
        }
        else
        {
            PPP_DBG_OK_CNT(PPP_PHOK_909);
            VOS_MemCpy((void*)(pstWantOptions->ConfigV6InId),(void *)g_pstApnByIndex[pstPppInfo->usCDBIndex].aucIterfaceID,IPV6_ADDR_LEN);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n wwwwwww PPP_IPV6CP_Init: local interface id = %x %x %x %x ",
                                                pstWantOptions->ConfigV6InId[0],
                                                pstWantOptions->ConfigV6InId[1],
                                                pstWantOptions->ConfigV6InId[2],
                                                pstWantOptions->ConfigV6InId[3]);
        }
    }
    else
    {
        PPP_MemSet((void*)(pstWantOptions->OurV6InId), 0, IPV6_ADDR_LEN);
        PPP_MemSet((void*)(pstWantOptions->HisV6InId), 0, IPV6_ADDR_LEN);
    }

    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 0;
    pstWantOptions->req_dnsaddr0  = 0;
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 0;
    pstWantOptions->req_dnsaddr1     = 0;
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 0;
    pstAllowOptions->req_dnsaddr0  = 0;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 0;
    pstAllowOptions->req_dnsaddr1     = 0;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;
    pstAllowOptions->accept_dnsaddr1  = 0;
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPV6CP_OPTION_S));
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��IPCP up���Э�̽�����м��,��Ҫ��Ϊ���Ժ���չ���µĽӿ�   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_ERR:Э�̽�����ɽ���,������Ӧ����Э��                  *
*                VOS_OK :Э�̽�����Խ���,������Ӧ���ϲ�Э�鱨UP            *
* CALLED BY    ��PPP_IPCP_up                                                *
****************************************************************************/
ULONG PPP_IPV6CP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    /* success */
    return VOS_OK;
}

/*****************************************************************************
 Prototype    : PPP_IPv6_GetAddrType
 Description  : IPv6��ַ���ͼ��
 Input        : IN6ADDR_S *addr
 Output       : None
 Return Value :
 Calls        :
 Called By    :

*****************************************************************************/
USHORT PPP_IPv6_GetAddrType( in6_addr *addr )
{
    USHORT  type;
    ULONG  st;

    st = addr->s6_addr32[0];

    if ( ( st & VOS_HTONL( 0xFF000000 ) ) == VOS_HTONL( 0xFF000000 ) )
    {
        type = IPV6_ADDR_MULTICAST;

        switch ( ( st & VOS_HTONL( 0x00FF0000 ) ) )
        {
            /*lint -e30*/
            case 0x00000100: /*VOS_HTONL( 0x00010000 ) */
                            type |= IPV6_ADDR_LOOPBACK;
                break;

            case 0x00000200: /*VOS_HTONL( 0x00020000 )*/
                            type |= IPV6_ADDR_LINKLOCAL;
                break;

            case 0x00000500: /*VOS_HTONL( 0x00050000 )*/
                            type |= IPV6_ADDR_SITELOCAL;
                break;
            /*lint +e30*/
            default:
                break;
        };
        return type;
    }

    type = IPV6_ADDR_UNICAST;

    /* Consider all addresses with the first three bits different of
       000 and 111 as finished.
     */
    if ( ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0x00000000 ) &&
         ( st & VOS_HTONL( 0xE0000000 ) ) != VOS_HTONL( 0xE0000000 ) )
{
        if ( ( st & VOS_HTONL( 0x20000000 ) ) == VOS_HTONL( 0x20000000 ) )
        {
            return ( IPV6_ADDR_GLOBAL | type ); /* global 0010 0000 0000 0000
                                                     global 0011 0000 0000 0000 */
        }
        return type;
    }

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFE800000 ) )
        return ( IPV6_ADDR_LINKLOCAL | type );/*link-local 1111 1110 10*/

    if ( ( st & VOS_HTONL( 0xFFC00000 ) ) == VOS_HTONL( 0xFEC00000 ) )
        return ( IPV6_ADDR_SITELOCAL | type );/*site-local 1111 1110 11*/

    if ( ( addr->s6_addr32[0] | addr->s6_addr32[1] ) == 0 )
    {
        if ( addr->s6_addr32[2] == 0 )
        {
            if ( addr->s6_addr32[3] == 0 )
                return IPV6_ADDR_ANY;/*all ::0*/

            if ( addr->s6_addr32[3] == VOS_HTONL( 0x00000001 ) )
                return ( IPV6_ADDR_LOOPBACK | type );/* ::0:1 */

            return ( IPV6_ADDR_COMPATv4 | type );
        }

        if ( addr->s6_addr32[2] == VOS_HTONL( 0x0000ffff ) )
            return IPV6_ADDR_MAPPED;
    }

    st &= VOS_HTONL( 0xFF000000 );
    if ( st == 0 )
        return IPV6_ADDR_RESERVED; /*0000 0000 */
    st &= VOS_HTONL( 0xFE000000 );
    if ( st == VOS_HTONL( 0x02000000 ) )
        return IPV6_ADDR_RESERVED;    /* for NSAP */
    if ( st == VOS_HTONL( 0x04000000 ) )
        return IPV6_ADDR_RESERVED;    /* for IPX */

    return type;
}
ULONG PPP_ipv6_addr_check(USHORT *pstIpv6addr)
{
    USHORT ultype;
    ULONG ulGlobalAddr = VOS_HTONL(0x20000000);   /* "�ɾۼ�ȫ�ֵ�����ַ"�Ķ�����ǰ׺Ϊ001 */
    ULONG ulSiteLocalAddr = VOS_HTONL(0xFEC00000);/* "���㱾�ص�����ַ"�Ķ�����ǰ׺Ϊ1111 1111 11 */
    in6_addr *pstAddr = (in6_addr *)pstIpv6addr;
    ULONG ulIpAddr = pstAddr->s6_addr32[0];

    ultype = PPP_IPv6_GetAddrType( pstAddr );

    /*��ʱֻ֧��SITE- local address�����Կ����Ժ�����չ*/
    if ( ( ultype & IPV6_ADDR_UNICAST )&&
         ( ( ultype & IPV6_ADDR_SITELOCAL )||( ultype & IPV6_ADDR_GLOBAL ) ) ) /* ֧�� global */
    {
        /* ֻ��"�ɾۼ�ȫ�ֵ�����ַ"��"���㱾�ص�����ַ"�ɱ����� */
        if (((ulIpAddr & VOS_HTONL(0xE0000000)) != ulGlobalAddr)
            && ((ulIpAddr & VOS_HTONL(0xFFC00000)) != ulSiteLocalAddr))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_230);
            return VOS_ERR;
        }
        /*  ֻ��"�ɾۼ�ȫ�ֵ�����ַ"��"���㱾�ص�����ַ"�ɱ�����*/
        return VOS_OK;
    }
    PPP_DBG_ERR_CNT(PPP_PHERR_231);
    return VOS_ERR;
}


ULONG PPP_ipv6_intfid_check(USHORT *pstIpv6addr, ULONG ullen)
{
    ULONG  ulReturn = 0;
    UCHAR  ucipv6Invalid[IPV6_ADDR_LEN*2] = {0};

    if (NULL == pstIpv6addr)
    {
        return VOS_ERR;
    }

    ulReturn = (ULONG)VOS_MemCmp((VOS_VOID *)pstIpv6addr, (VOS_VOID *)ucipv6Invalid, ullen);
    if (VOS_OK == ulReturn)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_910);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_ipv6_intfid_check: ipv6 addr is zero!");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOID PPP_Ipv6cp_Proc(PPPINFO_S *pstPppInfo)
{
    ULONG   ulResult   = VOS_ERR;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_Ipv6cp_Proc: ENTER.");

    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n PPP_Ipv6cp_Proc: Invalid input parameter pstPppInfo!");
        return;
    }

    ulResult = PPP_ipv6_addr_check(pstPppInfo->usPeerIPv6Addr);

    /*��ַ��Чδ�������ַ�ɹ����п�����aaa�·��ľ�̬��ַ�˲�ʧ�ܣ����������ַ�ǲ�����յ�*/
    if ((VOS_OK == ulResult)
        &&(pstPppInfo->pstIpV6cpInfo == NULL)
        &&( ( PPP_USERTYPE_SIP == pstPppInfo->bIPTech)))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,  "\r\n PPP_Ipv6cp_Proc: enter!");

        PPP_GETIPV6CPADDR(pstPppInfo->pstIpV6cpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpV6cpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_232);
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "\r\nPPP_Ipv6cp_Proc Malloc IPv6CP CB Err!!");
            return;
        }

        PPP_MemSet((void *)pstPppInfo->pstIpV6cpInfo, 0, sizeof(PPPIPV6CPINFO_S));
        PPP_IPV6CP_Init(pstPppInfo, pstPppInfo->usIpv6Addr, pstPppInfo->usPeerIPv6Addr);

        /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
        PPP_IPV6CP_ReceiveEventFromCore(pstPppInfo->pstIpV6cpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );

    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_911);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n PPP_Ipv6cp_Proc: don't nego ipv6 addr err ulResult %d, ",
                            ulResult);
    }

    return;
}




VOID PPP_IPV6CP_Pactket_Proc(PPPINFO_S *pstPppInfo,
                                         UCHAR*     pHead,
                                         UCHAR*     pPacket,
                                         ULONG      ulLen)
{
    /* ���������Ϣ */
    if (pstPppInfo->stPppDebugInfo.bDebug_Ipv6cp_Packet == VRP_YES)
    {
        PPP_Debug_FsmPacket(pstPppInfo,
                            pPacket,
                            ulLen,
                            PPP_IPV6CP,
                            (UCHAR)PPP_DEBUG_PACKET_IN);
    }

    /* �������ΪЭ��δ��Network�׶�pstIpcpInfo��Ϊ0��
       ���������ģ�������protocol reject��
       �μ�RFC1661��
     */
    if (pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_233);
        return;
    }

    if (pstPppInfo->pstIpV6cpInfo)
    {
        PPP_IPV6CP_ReceivePacket(pstPppInfo->pstIpV6cpInfo, pHead, pPacket, ulLen);
        PPP_DBG_OK_CNT(PPP_PHOK_912);
        return;
    }
    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
