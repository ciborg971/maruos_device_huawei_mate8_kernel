/************************************************************************
*                                                                      *
*                             ipcp.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��IPCPЭ��ģ��                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������IPCPЭ��ģ���ȫ���ӿں������ڲ�������             *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_IPCP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* IPCP�ص��������ݽṹ */
PPPFSMCALLBACK_S g_stIpcpCallbacks =
{
    /* ������Э�̱��Ĵ��� */
    PPP_IPCP_resetci,   /* ����������Ϣ����Э�̳�ʼֵ */
    PPP_IPCP_cilen,     /* ��Ҫ���͵�request���ĳ��� */
    PPP_IPCP_addci,     /* ��֯Э�̱��� */
    PPP_IPCP_ackci,     /* ����Է���ack���� */
    PPP_IPCP_nakci,     /* ����Է���nak���� */
    PPP_IPCP_rejci,     /* ����Է���reject���� */
    PPP_IPCP_reqci,     /* ����Է���request���� */
    NULL,                /* extcode����,����Э�����еı���.
                            IPCPû���������ͱ���,��˲��ṩ�������*/

    /* �¼���Э��ת������ֹ״̬ */
    PPP_IPCP_up,        /* Э��up */
    PPP_IPCP_down,       /* Э����ʱdown,����Ҫ����Э��.
                           ��finished��������:����PPPOE��DDR�ȵ������
                           ����֪ͨ�²�����· */
    PPP_IPCP_finished,   /* Э�������֪ͨ�²�:�����·.����IPCP,����֪ͨ
                            LCP:���û�����������Э��,��LCP����down��*/
    PPP_IPCP_starting,   /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                           ����������Э��,�����,�뷢һ��up�¼�.
                           Э����������û�о���涨,���Բ�ʵ��*/

    /* ��Э����Ϣ */
    "IPCP"               /* ��Э���� */
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
****************************************************************************/
VOID PPP_IPCP_ReceiveEventFromCore (VOID *pstIpcpInfo, ULONG ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;

    VOS_DBGASSERT(pstIpcpInfo);

    PPP_TRACE("\r\n---Into PPP_IPCP_ReceiveEventFromCore ulCmd %d---\r\n", ulCmd);
    if (NULL == pstIpcpInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    /* Begin Added by hyj for B02 */
    /* ����ͳ��:IPCPЭ�̳��Դ��� */
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        PPP_PerfInc(&g_stPppPerfStatistic.ulIpcpTotal, PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM, 0);
        PPP_TRACE("****pulIpcpTotal: %d****", g_stPppPerfStatistic.ulIpcpTotal);
        PPP_DBG_OK_CNT(PPP_PHOK_885);
    }

    /* End Added by hyj for B02 */

    pstFsm = &(((PPPIPCPINFO_S*)pstIpcpInfo)->stFsm);

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
****************************************************************************/
VOID PPP_IPCP_ReceivePacket (VOID *pstIpcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPFSM_S *pstFsm;
    VOS_UINT8 ucPppId;


    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);
    if(NULL == pstIpcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_193);
        //VOS_DBGASSERT(0);
        return;
    }
    pstFsm = &(((PPPIPCPINFO_S*)pstIpcpInfo)->stFsm);

    ucPppId = PPPC_GetCurrentPppId();
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, ucPppId);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��ȷ��IPCP��ҪЭ����Щ����,��IPCP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��״̬����ִ��tls�����ĺ�PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_IPCP_resetci(PPPFSM_S *pstFsm)
{
    PPPIPCPINFO_S *pstInfo;
    PPPCONFIGINFO_S *pstConfig;
    PPPINFO_S *pstPppInfo;
    PPP_IPCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S *pstGotOptions, *pstHisOptions;
    PPPRENOGOINFO *pstPppRenegoInfo;

    pstInfo = (PPPIPCPINFO_S *)pstFsm->pProtocolInfo;
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
    pstWantOptions->neg_dnsaddr0  = 1;/*changed by chenmin00265046, negotiate Primary DNS server address*/
    pstWantOptions->req_dnsaddr0  = 1;/*changed by chenmin00265046, Ask peer to send DNS server address*/
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 1;/*changed by chenmin00265046, negotiate Secondary DNS server address*/
    pstWantOptions->req_dnsaddr1     = 1;/*changed by chenmin00265046, Ask peer to send Secondary DNS server address*/
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 1;/* modified by chenmin00265046 ���ܶԷ���DNS,��Ӱ�쵽�յ�IPCP NAK���ٴη���ConfigReqѡ�� */
    pstWantOptions->accept_dnsaddr1  = 1;/* modified by chenmin00265046 ���ܶԷ���DNS,��Ӱ�쵽�յ�IPCP NAK���ٴη���ConfigReqѡ��*/
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 1;
    pstAllowOptions->req_dnsaddr0  = 1;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 1;
    pstAllowOptions->req_dnsaddr1     = 1;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 0;  /* modified by gxf 20030414 �����ܶԷ���DNS */
    pstAllowOptions->accept_dnsaddr1  = 0;  /* modified by gxf 20030414 �����ܶԷ���DNS */
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* ��������Ϣ����Э�̲��� */
    if (pstConfig->bEnableVJComp)
    {
        if (1 == pstPppInfo->bPppClient)
        {
            pstWantOptions->neg_vj = 0;
        }
        else
        {
            pstWantOptions->neg_vj = 1;
        }
    }

    if (pstAllowOptions->dnsaddr0 == 0)
    {
        pstAllowOptions->accept_dnsaddr0 = 0;
    }

    if (pstAllowOptions->dnsaddr1 == 0)
    {
        pstAllowOptions->accept_dnsaddr1 = 0;
    }

    *pstGotOptions = *pstWantOptions;

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    pstPppRenegoInfo = pstPppInfo->pstPppRenegoInfo;
    if (pstPppRenegoInfo && pstPppRenegoInfo->ucIpcpFlag)
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&pstPppRenegoInfo->stIpcpOptions, sizeof(PPP_IPCP_OPTION_S));
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
****************************************************************************/
USHORT PPP_IPCP_cilen(PPPFSM_S *pstFsm)
{
    PPP_IPCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */
    return (USHORT)(IPCP_LENCIADDR(pstGotOptions->neg_addr, pstGotOptions->old_addrs) +
                   IPCP_LENCIVJ(pstGotOptions->neg_vj) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_dnsaddr0) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_nbnsaddr0) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_dnsaddr1) +
                   IPCP_LENCIDNSADDR(pstGotOptions->neg_nbnsaddr1)
    );
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
****************************************************************************/
VOID PPP_IPCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_IPCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    ADDCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->ouraddr,
              pstGotOptions->hisaddr
    );

    ADDCIVJ(IPCP_CI_COMPRESSTYPE,
            pstGotOptions->neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
    );

    ADDCIDNSADDR(IPCP_CI_DNSADDR0,
                 pstGotOptions->neg_dnsaddr0,
                 pstGotOptions->dnsaddr0
    );

    ADDCIDNSADDR(IPCP_CI_NBNSADDR0,
                 pstGotOptions->neg_nbnsaddr0,
                 pstGotOptions->nbnsaddr0
    );

    ADDCIDNSADDR(IPCP_CI_DNSADDR1,
                 pstGotOptions->neg_dnsaddr1,
                 pstGotOptions->dnsaddr1
    );

    ADDCIDNSADDR(IPCP_CI_NBNSADDR1,
                 pstGotOptions->neg_nbnsaddr1,
                 pstGotOptions->nbnsaddr1
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
* CALLED BY    ��PPP_FSM_ReceiveConfAck                                     *
****************************************************************************/
USHORT PPP_IPCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype;
    USHORT cishort;
    ULONG cilong;
    UCHAR cimaxslotindex, cicflag;

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * CIs must be in exactly the same order that we sent...
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /* We allow the configuration length is 0. */
    if (ulLen == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_886);
        return VOS_OK;
    }

    ACKCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
              pstGotOptions->neg_addr,
              pstGotOptions->old_addrs,
              pstGotOptions->ouraddr,
              pstGotOptions->hisaddr
    );

    ACKCIVJ(IPCP_CI_COMPRESSTYPE,
            pstGotOptions->neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
    );

    ACKCIDNSADDR(IPCP_CI_DNSADDR0,
                 pstGotOptions->neg_dnsaddr0,
                 pstGotOptions->dnsaddr0
    );

    ACKCIDNSADDR(IPCP_CI_NBNSADDR0,
                 pstGotOptions->neg_nbnsaddr0,
                 pstGotOptions->nbnsaddr0
    );

    ACKCIDNSADDR(IPCP_CI_DNSADDR1,
                 pstGotOptions->neg_dnsaddr1,
                 pstGotOptions->dnsaddr1
    );

    ACKCIDNSADDR(IPCP_CI_NBNSADDR1,
                 pstGotOptions->neg_nbnsaddr1,
                 pstGotOptions->nbnsaddr1
    );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_194);
        goto bad;
    }
    /*lint +e801*/

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "Ipcp_ackci: received bad Ack!");
    return VOS_ERR;
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
****************************************************************************/
USHORT PPP_IPCP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S stNoOption;  /* ���Է�no����ѡ�� */
    PPP_IPCP_OPTION_S stTryOption; /* ������Է�Э�̵�ѡ�� */

    UCHAR cimaxslotindex, cicflag;
    UCHAR citype, cilen, *next;
    USHORT cishort;
    ULONG ciaddr1, ciaddr2;

    pstGotOptions  = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_IPCP_OPTION_S));
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
    NAKCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR), neg_addr, pstGotOptions->old_addrs,
            if (ciaddr1)
            {
                stTryOption.ouraddr = ciaddr1;
            }

              if (ciaddr2)
              { /* Does he know his? */
                  stTryOption.hisaddr = ciaddr2;
              }

    );

    /*
     * Accept the peer's value of maxslotindex provided that it
     * is less than what we asked for.  Turn off slot-ID compression
     * if the peer wants.  Send old-style compress-type option if
     * the peer wants.
     */
    NAKCIVJ(IPCP_CI_COMPRESSTYPE, neg_vj,
            if (cilen == IPCP_CILEN_VJ)
            {
                PPP_GETCHAR(cimaxslotindex, pPacket);
                PPP_GETCHAR(cicflag, pPacket);
                if (cishort == PPP_VJ_COMP)
                {
                    if (cimaxslotindex < pstGotOptions->maxslotindex)
                    {
                        stTryOption.maxslotindex = cimaxslotindex;
                    }

                    if (!cicflag)
                    {
                        stTryOption.cflag = 0;
                    }
                }
                else
                {
                    stTryOption.neg_vj = 0;
                }
            }

    );

    NAKCIDNSADDR( IPCP_CI_DNSADDR0, neg_dnsaddr0,
                  if ((pstGotOptions->accept_dnsaddr0 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.dnsaddr0 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_dnsaddr0 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_dnsaddr0 = 0;
                  }

    );

    NAKCIDNSADDR( IPCP_CI_NBNSADDR0, neg_nbnsaddr0,
                  if ((pstGotOptions->accept_nbnsaddr0 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.nbnsaddr0 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_nbnsaddr0 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_nbnsaddr0 = 0;
                  }

    );
    NAKCIDNSADDR( IPCP_CI_DNSADDR1, neg_dnsaddr1,
                  if ((pstGotOptions->accept_dnsaddr1 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.dnsaddr1 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_dnsaddr1 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_dnsaddr1 = 0;
                  }

    );
    NAKCIDNSADDR( IPCP_CI_NBNSADDR1, neg_nbnsaddr1,
                  if ((pstGotOptions->accept_nbnsaddr1 != 0) && (ciaddr1 != 0))
                  {
                      stTryOption.nbnsaddr1 = ciaddr1;
                  }

                  if ((pstGotOptions->accept_nbnsaddr1 == 0) && (ciaddr1 != 0))
                  {
                      stTryOption.neg_nbnsaddr1 = 0;
                  }

    );

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
            PPP_DBG_ERR_CNT(PPP_PHERR_195);
            goto bad;
        }

        ulLen = (ULONG)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_196);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case IPCP_CI_COMPRESSTYPE:
                if (pstGotOptions->neg_vj || stNoOption.neg_vj
               || ((cilen != IPCP_CILEN_VJ) && (cilen != IPCP_CILEN_COMPRESS)))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_197);
                    goto bad;
                }

                stNoOption.neg_vj = 1;
                break;

            case IPCP_CI_ADDRS:
                if ((pstGotOptions->neg_addr && pstGotOptions->old_addrs) || stNoOption.old_addrs
                    || (cilen != IPCP_CILEN_ADDRS))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_198);
                    goto bad;
                }

                stTryOption.neg_addr  = 1;
                stTryOption.old_addrs = 1;
                PPP_GETADDR(ciaddr1, pPacket);
                if (ciaddr1 && (pstWantOptions->ouraddr == 0L))
                {
                    stTryOption.ouraddr = ciaddr1;
                }

                PPP_GETADDR(ciaddr2, pPacket);
                if (ciaddr2)
                {
                    stTryOption.hisaddr = ciaddr2;
                }

                stNoOption.old_addrs = 1;
                break;

            case IPCP_CI_ADDR:
                if (pstGotOptions->neg_addr || stNoOption.neg_addr || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_199);
                    goto bad;
                }

                PPP_GETADDR(ciaddr1, pPacket);
                if (ciaddr1 && (pstWantOptions->ouraddr == 0L))
                {
                    stTryOption.ouraddr  = ciaddr1;
                    stTryOption.neg_addr = 1;
                }

                stNoOption.neg_addr = 1;
                break;
            case IPCP_CI_DNSADDR0:
                NONEGDNSADDR( neg_dnsaddr0, accept_dnsaddr0, dnsaddr0 );
                break;
            case IPCP_CI_NBNSADDR0:
                NONEGDNSADDR( neg_nbnsaddr0, accept_nbnsaddr0, nbnsaddr0 );
                break;
            case IPCP_CI_DNSADDR1:
                NONEGDNSADDR( neg_dnsaddr1, accept_dnsaddr1, dnsaddr1 );
                break;
            case IPCP_CI_NBNSADDR1:
                NONEGDNSADDR( neg_nbnsaddr1, accept_nbnsaddr1, nbnsaddr1 );
                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_200);
        goto bad;
    }
    /*lint +e801*/

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

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     �������յ���Config Reject����                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���reject����;VOS_ERR:�Ƿ���reject����           *
* CALLED BY    ��PPP_FSM_ReceiveConfNakRej                                  *
****************************************************************************/
/*lint -e529*/
USHORT PPP_IPCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_IPCP_OPTION_S *pstGotOptions;
    UCHAR cimaxslotindex, ciflag, cilen = 0;
    USHORT cishort;
    ULONG cilong;
    PPP_IPCP_OPTION_S stTryOption;      /* options to request next time */

    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    /*lint -e821*/
    REJCIADDR((pstGotOptions->old_addrs ? IPCP_CI_ADDRS : IPCP_CI_ADDR),
               neg_addr,
               pstGotOptions->old_addrs,
               pstGotOptions->ouraddr,
               pstGotOptions->hisaddr
             );
    /*lint +e821*/

    REJCIVJ(IPCP_CI_COMPRESSTYPE,
            neg_vj,
            pstGotOptions->vj_protocol,
            pstGotOptions->maxslotindex,
            pstGotOptions->cflag
           );

    REJCIDNSADDR(IPCP_CI_DNSADDR0,
                 neg_dnsaddr0,
                 dnsaddr0
                );

    REJCIDNSADDR(IPCP_CI_NBNSADDR0,
                 neg_nbnsaddr0,
                 nbnsaddr0
                );

    REJCIDNSADDR(IPCP_CI_DNSADDR1,
                 neg_dnsaddr1,
                 dnsaddr1
                );

    REJCIDNSADDR(IPCP_CI_NBNSADDR1,
                 neg_nbnsaddr1,
                 nbnsaddr1
                );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */
    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_201);
        goto bad;
    }

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
    /*lint +e801*/
}
/*lint +e529*/

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

*****************************************************************************/
UCHAR PPP_IPCP_IsSip(UCHAR *pPacket, ULONG *pulLen)
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
            PPP_DBG_OK_CNT(PPP_PHOK_887);
            return 0;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l -= cilen;                 /* Adjust remaining length */
        p += (cilen - 2);           /* Step to next CI */

        if (citype == IPCP_CI_ADDR)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_888);
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
* CALLED BY    ��PPP_FSM_ReceiveConfReq��������PPP_FSM_reqci�����          *
****************************************************************************/
UCHAR PPP_IPCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG *pulLen)
{
    PPP_IPCP_OPTION_S *pstWantOptions;
    PPP_IPCP_OPTION_S *pstAllowOptions;
    PPP_IPCP_OPTION_S *pstGotOptions;
    PPP_IPCP_OPTION_S *pstHisOptions;
    PPPINFO_S* pstPppInfo = NULL;

    UCHAR *cip, *next, *p;     /* Pointer to current and next CIs */
    USHORT cilen, citype;   /* Parsed len, type */
    USHORT cishort;     /* Parsed short value */
    ULONG ciaddr1, ciaddr2;/* Parsed address values */
    UCHAR rc = CONFACK;     /* Final packet return code */
    UCHAR orc;          /* Individual option return code */
    UCHAR *ucp = pPacket;       /* Pointer to current output char */
    long l = (long)*pulLen;       /* Length left */
    UCHAR maxslotindex, cflag;

    pstWantOptions  = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);
    pstAllowOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stAllowOptions);
    pstGotOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPIPCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);
    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;

    /*
     * Reset all his options.
     */
    (VOID)VOS_MemSet(pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));

    /*luofeng37050notify */
    /* added by gxf 20030415    �ж�SIP/MIP */
    if (!PPP_IPCP_IsSip(pPacket, pulLen))
    {
    }

    /*
     * Process all his options.
     */
    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_889);
        return rc;
    }

    next = pPacket;

    /*lint -e801*/
    while (l)
    {
        orc = CONFACK;          /* Assume success */
        cip = p = next;         /* Remember begining of CI */
        if ((l < 2)               /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > l))
        {
            /*  CI length too big? */
            orc   = CONFREJ;    /* Reject bad CI */
            cilen = (USHORT)l;          /* Reject till end of packet */
            l = 0;          /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_890);
            goto endswitch;
        }

        PPP_GETCHAR(citype, p);     /* Parse CI type */
        PPP_GETCHAR(cilen, p);      /* Parse CI length */
        l    -= cilen;      /* Adjust remaining length */
        next += cilen;          /* Step to next CI */

        switch (citype)
        {
            /* Check CI type */
            case IPCP_CI_ADDRS:
                if (!pstWantOptions->neg_addr
               || (cilen != IPCP_CILEN_ADDRS))
                {
                    /* Check CI length */
                    PPP_DBG_ERR_CNT(PPP_PHERR_202);
                    orc = CONFREJ;  /* Reject CI */
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_ADDRS is not compatible(neg_addr)! ");
                    break;
                }

                /*
                 * If he has no address, or if we both have his address but
                 * disagree about it, then NAK it with our idea.
                 * In particular, if we don't know his address, but he does,
                 * then accept it.
                 */

                /* make sure GetRmtIP return value is net byte */
                /* make sure GetLocIP return value is net byte */

                PPP_GETADDR(ciaddr1, p); /* Parse source address (his) */
                PPP_GETADDR(ciaddr2, p); /* Parse desination address (ours) */

                if ((!pstGotOptions->hisaddr && (!ciaddr1)) || ((!pstGotOptions->ouraddr) && (!ciaddr2)))
                {
                    /* we can't dispatch each other's address so have to say bye */
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_203);
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_ADDRS is not compatible(ciaddr1,ciaddr2)! ");
                    break;
                }

                if ((pstGotOptions->hisaddr == ciaddr1) && (pstGotOptions->ouraddr == ciaddr2))
                {
                    break;
                }
                else
                {
                    if (ciaddr1)
                    {
                        pstGotOptions->hisaddr = ciaddr1;
                        pstHisOptions->hisaddr = ciaddr1;
                    }

                    if (!pstGotOptions->ouraddr)
                    {
                        pstGotOptions->ouraddr = ciaddr2;
                        pstHisOptions->ouraddr = ciaddr2;
                        break;
                    }

                    if (pstGotOptions->ouraddr != ciaddr2)
                    {
                        orc = CONFNAK;
                        PPP_DECPTR(sizeof(ULONG) << 1, p);
                        PPP_PUTADDR(pstGotOptions->hisaddr, p);
                        PPP_PUTADDR(pstGotOptions->ouraddr, p);
                    }

                    pstGotOptions->old_addrs = 1;
                    pstHisOptions->old_addrs = 1;
                }

                /* this is occurce when she wants us to dispatch her a ip address */
                break;

            case IPCP_CI_ADDR:

                if (!pstWantOptions->neg_addr
                   || (cilen != IPCP_CILEN_ADDR)
                   || (0xffffffff == pstPppInfo->ulPeerIPAddr))
                {
                    /* Check CI length */
                    orc = CONFREJ;  /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_204);
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_ADDR is not compatible(neg_addr)! ");
                    break;
                }

                PPP_GETADDR(ciaddr1, p);/* Parse source address (his) */

                if (ciaddr1 != 0L)
                {
                    pstHisOptions->neg_addr = 1;

                    /* save his address, no whether his address is changed */
                    pstGotOptions->neg_addr = 1;
                    pstHisOptions->hisaddr = ciaddr1;
                    pstGotOptions->hisaddr = ciaddr1;
                }
                else
                {
                    /*
                     * If he has no address, or if we both have his address but
                     * disagree about it, then NAK it with our idea.
                     * In particular, if we don't know his address, but he does,
                     * then accept it.
                     */
                    if (pstWantOptions->hisaddr == 0L)
                    {
                        orc = CONFREJ;
                        PPP_DBG_ERR_CNT(PPP_PHERR_205);
                        PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_ADDR is not compatible(hisaddr)! ");
                        pstWantOptions->req_addr = 0;/* don't NAK with 0.0.0.0 later */
                    }
                    else
                    {
                        pstHisOptions->neg_addr = 1;
                        orc = CONFNAK;
                        pstGotOptions->neg_addr = 1;
                        PPP_DECPTR(sizeof(ULONG), p);
                        PPP_PUTADDR(pstGotOptions->hisaddr, p);
                    }
                }

                break;

            case IPCP_CI_COMPRESSTYPE:
                if (!pstWantOptions->neg_vj || (cilen != IPCP_CILEN_VJ))
                {
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_206);
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_COMPRESSTYPE is not compatible(neg_vj)! ");
                    break;
                }

                PPP_GETSHORT(cishort, p);

                if (cishort != PPP_VJ_COMP)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_207);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_COMPRESSTYPE is not compatible(cishort)! ");
                    break;
                }

                pstHisOptions->neg_vj = 1;
                pstHisOptions->vj_protocol = cishort;

                PPP_GETCHAR(maxslotindex, p);
                if (maxslotindex > pstWantOptions->maxslotindex)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_891);
                    orc = CONFNAK;
                    PPP_DECPTR(1, p);
                    PPP_PUTCHAR(pstWantOptions->maxslotindex, p);
                    break;
                }

                PPP_GETCHAR(cflag, p);
                if (cflag && !pstWantOptions->cflag)
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_892);
                    orc = CONFNAK;
                    PPP_DECPTR(1, p);
                    PPP_PUTCHAR(pstWantOptions->cflag, p);
                    break;
                }

                pstHisOptions->maxslotindex = maxslotindex;
                pstHisOptions->cflag = cflag;
                break;
            case IPCP_CI_DNSADDR0:
                if ((pstAllowOptions->neg_dnsaddr0 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_208);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR0 is not compatible(neg_dnsaddr0)! ");
                    break;
                }

                if (0 == pstAllowOptions->dnsaddr0)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_209);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR0 is not compatible(dnsaddr0)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_dnsaddr0 = 1;
                if ((ciaddr1 != pstAllowOptions->dnsaddr0) && ((0 == pstAllowOptions->accept_dnsaddr0)
                   || (ciaddr1 == 0)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_893);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(ULONG), p);
                    ciaddr1 = pstAllowOptions->dnsaddr0;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->dnsaddr0 = ciaddr1;
                }

                break;
            case IPCP_CI_DNSADDR1:
                if ((pstAllowOptions->neg_dnsaddr1 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_210);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR1 is not compatible(neg_dnsaddr1)! ");
                    break;
                }

                if (0 == pstAllowOptions->dnsaddr1)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_211);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_DNSADDR1 is not compatible(dnsaddr1)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_dnsaddr1 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->dnsaddr1) && (0 == pstAllowOptions->accept_dnsaddr1)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_894);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(ULONG), p);
                    ciaddr1 = pstAllowOptions->dnsaddr1;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->dnsaddr1 = ciaddr1;
                }

                break;
            case IPCP_CI_NBNSADDR0:
                if ((pstAllowOptions->neg_nbnsaddr0 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_212);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR0 is not compatible(neg_nbnsaddr0)! ");
                    break;
                }

                if (0 == pstAllowOptions->nbnsaddr0)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_213);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR0 is not compatible(nbnsaddr0)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_nbnsaddr0 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->nbnsaddr0) && (0 == pstAllowOptions->accept_nbnsaddr0)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_895);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(ULONG), p);
                    ciaddr1 = pstAllowOptions->nbnsaddr0;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->nbnsaddr0 = ciaddr1;
                }

                break;
            case IPCP_CI_NBNSADDR1:
                if ((pstAllowOptions->neg_nbnsaddr1 == 0)
               || (cilen != IPCP_CILEN_ADDR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_214);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR1 is not compatible(neg_nbnsaddr1)! ");
                    break;
                }

                if (0 == pstAllowOptions->nbnsaddr1)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_215);
                    orc = CONFREJ;
                    PPP_DebugOut(MID_PPPC,PPP_DEBUG_INFO,"\r\n PPP_IPCP_reqci: IPCP_CI_NBNSADDR1 is not compatible(nbnsaddr1)! ");
                    break;
                }

                PPP_GETADDR( ciaddr1, p );
                pstHisOptions->neg_nbnsaddr1 = 1;
                if ((ciaddr1 == 0)
               || ((ciaddr1 != pstAllowOptions->nbnsaddr1) && (0 == pstAllowOptions->accept_nbnsaddr1)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_896);
                    orc = CONFNAK;
                    PPP_DECPTR(sizeof(ULONG), p);
                    ciaddr1 = pstAllowOptions->nbnsaddr1;
                    PPP_PUTADDR( ciaddr1, p );
                }
                else
                {
                    pstHisOptions->nbnsaddr1 = ciaddr1;
                }

                break;
            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_216);
                orc = CONFREJ;
                break;
        }

endswitch:
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
    /*lint +e801*/
}
/*lint +e529*/

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��״̬��up�Ĵ�����                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tlu������(PPP_FSM_tlu)����             *
****************************************************************************/
VOID PPP_IPCP_up(PPPFSM_S *pstFsm)
{
    ULONG ulAccept = 0;
    PPPINFO_S* pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    PPPC_INFO_LOG("enter PPP_IPCP_up\r\n");

    /* IPCPЭ�̽���Ƿ���Խ��� */
    ulAccept = PPP_IPCP_UpResetCi(pstPppInfo);
    if (VOS_OK != ulAccept)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_217);
        /* Э�̽�����ɽ���,����Э�� */
        return;
    }

    /* Э�̽�����Խ���,���ں˷���Ipcp Up�¼� */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo,
                                      (LONG)PPP_EVENT_IPCPUP,
                                      NULL);
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
****************************************************************************/
VOID PPP_IPCP_down(PPPFSM_S *pstFsm)
{
    /* �ش���ʱ����PPP_FSM_tld���Ѿ�ɾ�� */
    PPPIPCPINFO_S *pstIpcpInfo = (PPPIPCPINFO_S*)pstFsm->pProtocolInfo;

    if ((pstIpcpInfo->pstPppInfo)
        && (pstIpcpInfo->pstPppInfo->bVjFlag))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_897);
        PPP_CompUserNumDel(pstIpcpInfo->pstPppInfo, PPP_USERSTAT_VJ);
        PPP_INNER_COUNTER(PPP_INNER_COUTNER_066);
    }

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPDOWN,
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
****************************************************************************/
VOID PPP_IPCP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPFINISHED,
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
****************************************************************************/
VOID PPP_IPCP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (LONG)PPP_EVENT_IPCPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ʼ��IPCP���ƿ�                                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                ulMyIpAddr:�ҵ�IP��ַ                                      *
*                ulPeerIpAddr:������Է���IP��ַ                            *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��                                                           *
****************************************************************************/
VOID PPP_IPCP_Init(PPPINFO_S* pstPppInfo, ULONG ulMyIpAddr, ULONG ulPeerIpAddr)
{
    PPPIPCPINFO_S *pstIpcpInfo;
    PPPFSM_S *pstFsm;
    PPP_IPCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_IPCP_OPTION_S *pstGotOptions, *pstHisOptions;

    if ((NULL == pstPppInfo) || (NULL == pstPppInfo->pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_218);
        return;
    }

    pstIpcpInfo = (PPPIPCPINFO_S*)pstPppInfo->pstIpcpInfo;
    pstFsm = &(pstIpcpInfo->stFsm);
    pstPppInfo->bPppStateFlg = PPP_STATE_NEGOING;

    /* IPCP���ƿ��ʼ�� */
    pstIpcpInfo->pstPppInfo = pstPppInfo;
    pstIpcpInfo->ucUsedFlag = 1;

    /* ״̬����ʼ�� */
    pstFsm->usProtocol    = PPP_IPCP;
    pstFsm->pstCallBacks  = &g_stIpcpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstIpcpInfo;
    pstFsm->pPppInfo = (char*)pstIpcpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);

    /* Э�̲�����ʼ�� */
    pstAllowOptions = &(pstIpcpInfo->stAllowOptions);
    pstWantOptions = &(pstIpcpInfo->stWantOptions);
    pstGotOptions = &(pstIpcpInfo->stGotOptions);
    pstHisOptions = &(pstIpcpInfo->stHisOptions);

    if (0 == pstPppInfo->bPppClient)
    {
        pstWantOptions->ouraddr = ulMyIpAddr;
        pstWantOptions->hisaddr = ulPeerIpAddr;
    }
    else
    {
        pstWantOptions->ouraddr = 0;
        pstWantOptions->hisaddr = 0;
    }

    pstWantOptions->neg_addr  = 1;
    pstWantOptions->req_addr  = 1;
    pstWantOptions->old_addrs = 0;
    pstWantOptions->neg_vj = 0;
    pstWantOptions->vj_protocol  = PPP_VJ_COMP;
    pstWantOptions->maxslotindex = MAX_STATES - 1; /* really max index */
    pstWantOptions->cflag = 0;
    pstWantOptions->neg_dnsaddr0  = 1;/*changed by chenmin00265046, negotiate Primary DNS server address*/
    pstWantOptions->req_dnsaddr0  = 1;/*changed by chenmin00265046, Ask peer to send DNS server address*/
    pstWantOptions->neg_nbnsaddr0 = 0;
    pstWantOptions->req_nbnsaddr0 = 0;
    pstWantOptions->neg_dnsaddr1     = 1;/*changed by chenmin00265046, negotiate Secondary DNS server address*/
    pstWantOptions->req_dnsaddr1     = 1;/*changed by chenmin00265046, Ask peer to send Secondary DNS server address*/
    pstWantOptions->neg_nbnsaddr1    = 0;
    pstWantOptions->req_nbnsaddr1    = 0;
    pstWantOptions->accept_dnsaddr0  = 0;
    pstWantOptions->accept_dnsaddr1  = 0;
    pstWantOptions->accept_nbnsaddr0 = 0;
    pstWantOptions->accept_nbnsaddr1 = 0;

    *pstGotOptions = *pstWantOptions;

    pstAllowOptions->req_addr = 1;
    pstAllowOptions->neg_dnsaddr0  = 1;
    pstAllowOptions->req_dnsaddr0  = 1;
    pstAllowOptions->neg_nbnsaddr0 = 0;
    pstAllowOptions->req_nbnsaddr0 = 0;
    pstAllowOptions->neg_dnsaddr1     = 1;
    pstAllowOptions->req_dnsaddr1     = 1;
    pstAllowOptions->neg_nbnsaddr1    = 0;
    pstAllowOptions->req_nbnsaddr1    = 0;
    pstAllowOptions->accept_dnsaddr0  = 1;
    pstAllowOptions->accept_dnsaddr1  = 1;
    pstAllowOptions->accept_nbnsaddr0 = 0;
    pstAllowOptions->accept_nbnsaddr1 = 0;

    /* added by gxf 20030414    ��ʼ��dns */
    pstAllowOptions->dnsaddr0 = pstPppInfo->ulDNSAddr1;
    pstAllowOptions->dnsaddr1 = pstPppInfo->ulDNSAddr2;

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_IPCP_OPTION_S));
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
ULONG PPP_IPCP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    PPPIPCPINFO_S * pstIpcpInfo = NULL;
    //UCHAR szTempImsi[M_IMSI_LEN] = {0};
    //UCHAR szTranImsi[M_IMSI_LEN] = {0};

    /* Э�̳ɲ�ͬ���͵��û� (������Э��) */
    pstIpcpInfo = pstPppInfo->pstIpcpInfo;

    if (PPP_USERTYPE_MIP_RENEGO_TYPECHANGE(pstPppInfo,pstIpcpInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_218);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_IPCP_UpResetCi:Nego result isn't accepted!");

        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_33);
        if (0 == g_ulPppDBGStatisc[PPP_PHERR_218]%50)
        {
            //ImsiToString(pstPppInfo->stIMSI, szTempImsi);
            //AM_EncryptPrivacyData(szTempImsi,(M_IMSI_LEN - 1) , szTranImsi);
            PPPC_WARNING_LOG("\r\nPPP_Shell_IpcpUpNegotiateIp:cmip->sip");
        }
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_IPCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*�ͷ���·*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n [ppp]PPP_Shell_IpcpUpNegotiateIp: mip -> sip pstPppInfo->bReNego = %u pstPppInfo->bIPTech = %u  ",
                      pstPppInfo->bReNego, pstPppInfo->bIPTech);

        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER018);
        return VOS_ERR;
    }

    /* success */
    return VOS_OK;
}
VOID PPP_Ipv4cp_Proc( PPPINFO_S *pstPppInfo )
{
    /* ��ȡIPCP���ƿ� */
    if (NULL == pstPppInfo->pstIpcpInfo)
    {
        PPP_GETIPCPADDR(pstPppInfo->pstIpcpInfo, pstPppInfo->ulRPIndex);
        if (NULL == pstPppInfo->pstIpcpInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_219);
            /* Malloc Error */
            PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "Malloc IPCP CB Err!!");
            return;
        }
    }
    PPP_MemSet((void *)pstPppInfo->pstIpcpInfo, 0, sizeof(PPPIPCPINFO_S));

    /* �ж��Ƿ���ҪЭ��VJѹ�� */
    /*lint -e746*/
    if(VOS_OK == PPP_CheckVjLimit())
    /*lint +e746*/
    {
        /* ����Э��ǰ�Ͳ�֧��VJѹ��������ȻЭ��Ϊ��֧�֣�����֧��VJѹ�� */
        if ((0 != pstPppInfo->bReNego)
            && (NULL != pstPppInfo->pstPppRenegoInfo)
            && (0 != ((PPPRENOGOINFO*)pstPppInfo->pstPppRenegoInfo)->ucIpcpFlag)
            && (0 == ((PPPRENOGOINFO*)pstPppInfo->pstPppRenegoInfo)->stIpcpOptions.neg_vj))
        {
             ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;
             PPP_DBG_OK_CNT(PPP_PHOK_898);

        }
        else
        {
            ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 1;
            PPP_DBG_OK_CNT(PPP_PHOK_899);
        }
    }
    else
    {
        ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 0;

        if ((NULL != pstPppInfo->pstPppRenegoInfo)
            && (0 != pstPppInfo->pstPppRenegoInfo->stIpcpOptions.neg_vj))
        {

             ((PPPCONFIGINFO_S*)pstPppInfo->pstConfigInfo)->bEnableVJComp = 1;
             PPP_DBG_OK_CNT(PPP_PHOK_900);
        }

    }

    PPP_IPCP_Init(pstPppInfo, pstPppInfo->ulIPAddr, pstPppInfo->ulPeerIPAddr);

    /* ��IPCP������Ϣ,����IPCP��ʼЭ�� */
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL );
    PPP_IPCP_ReceiveEventFromCore(pstPppInfo->pstIpcpInfo, (ULONG)PPP_EVENT_FSM_UP, NULL );

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
