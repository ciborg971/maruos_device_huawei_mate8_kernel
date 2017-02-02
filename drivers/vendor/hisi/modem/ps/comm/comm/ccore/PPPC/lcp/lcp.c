/************************************************************************
*                                                                      *
*                             lcp.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/04/04                                      *
*  Author:             Deng Yi Ou                                      *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��LCPЭ��ģ��                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������LCPЭ��ģ���ȫ���ӿں������ڲ�������              *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_LCP_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* LCP�ص��������ݽṹ */
PPPFSMCALLBACK_S g_stLcpCallbacks =
{
    /* ������Э�̱��Ĵ��� */
    PPP_LCP_resetci,   /* ����������Ϣ����Э�̳�ʼֵ */
    PPP_LCP_cilen,     /* ��Ҫ���͵�request���ĳ��� */
    PPP_LCP_addci,     /* ��֯Э�̱��� */
    PPP_LCP_ackci,     /* ����Է���ack���� */
    PPP_LCP_nakci,     /* ����Է���nak���� */
    PPP_LCP_rejci,     /* ����Է���reject���� */
    PPP_LCP_reqci,     /* ����Է���request���� */
    PPP_LCP_extcode,   /* ����Э�����еı��ģ���protocol reject�� */

    /* �¼���Э��ת������ֹ״̬ */
    PPP_LCP_up,        /* Э��up */
    PPP_LCP_down,       /* Э����ʱdown,����Ҫ����Э��.
                           ��finished��������:����PPPOE��DDR�ȵ������
                           ����֪ͨ�²�����· */
    PPP_LCP_finished,   /* Э�������֪ͨ�ײ�:�����·.����LCP,ֻҪ����
                           PPPOE��DDR�ȵ����,�������reset��ʱ��,
                           ��ʱ����������Э�� */
    PPP_LCP_starting,   /* tls(This-Layer-Started)�����У�֪ͨ�²�:��׼
                           ����������Э��,�����,�뷢һ��up�¼�.
                           Э����������û�о���涨,���Բ�ʵ��*/

    /* ��Э����Ϣ */
    "LCP"               /* ��Э���� */
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��LCP�����ⲿ�¼�.�¼�������Up��Down��Open��Close            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstLcpInfo:LCP���ƿ�ָ��                                   *
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
VOID PPP_LCP_ReceiveEventFromCore (VOID *pstLcpInfo, ULONG ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;
    PPPINFO_S *pstPppInfo = NULL;

    VOS_DBGASSERT(pstLcpInfo);
    PPP_TRACE("\r\n---Into PPP_LCP_ReceiveEventFromCore ulCmd: %d---\r\n", ulCmd);

    if (NULL == pstLcpInfo)
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstFsm = &(((PPPLCPINFO_S*)pstLcpInfo)->stFsm);
    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;

    /* Begin Added by hyj for B02 */
    /* ����ͳ��:LCPЭ�̳��Դ��� */
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_913);
        PPP_PerfInc(&g_stPppPerfStatistic.ulLcpTotal, PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM, pstPppInfo->bEhrpdUser);
        PPP_TRACE("****LcpTotal: %d****", g_stPppPerfStatistic.ulLcpTotal);
    }

    /* End Added by hyj for B02 */


    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��LCP���ձ���                                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstLcpInfo:LCP���ƿ�                                       *
*                pHead:��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�              *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_LCP_ReceivePacket (VOID *pstLcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPFSM_S *pstFsm = NULL;
    PPPINFO_S *pstPppInfo = NULL;
    VOS_UINT8 ucPppId;

    VOS_DBGASSERT(pstLcpInfo);
    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);

    if ((NULL == pstLcpInfo) || (NULL == pPacket))
    {
        VOS_DBGASSERT(0);
        return;
    }

    pstFsm = &(((PPPLCPINFO_S*)pstLcpInfo)->stFsm);

    pstPppInfo = (((PPPLCPINFO_S*)pstLcpInfo)->pstPppInfo);

    if (pstPppInfo != NULL)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_914);
        pstPppInfo->bRecvLcpMsgFlag = VOS_TRUE;
    }

    ucPppId = PPPC_GetCurrentPppId();
    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, ucPppId);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
    return;

}

/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��ȷ��LCP��ҪЭ����Щ����,��LCP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��״̬����ִ��tls�����ĺ�PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_LCP_resetci_TestStub(PPPFSM_S *pstFsm)
{
    PPPLCPINFO_S *pstInfo;
    PPPCONFIGINFO_S *pstConfig;
    PPPINFO_S *pstPppInfo;
    PPP_LCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_LCP_OPTION_S *pstGotOptions, *pstHisOptions;
    PPP_LCP_OPTION_S stRenegoOptions; /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */

    PPP_TRACE("\r\n---Into PPP_LCP_resetci---\r\n");

    pstInfo = (PPPLCPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstInfo->pstPppInfo;

    if (NULL == pstPppInfo->pstUsedConfigInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "\r\n [ppp]PPP_LCP_resetci:rpindex=%u,ustate=%u,usPhase=%u",
                    pstPppInfo->ulRPIndex,pstPppInfo->usState,pstPppInfo->usPhase);
        (VOID)PPP_InitConfigInfo(pstPppInfo);
    }

    pstConfig = pstPppInfo->pstUsedConfigInfo;

    pstAllowOptions = &(pstInfo->stAllowOptions);
    pstWantOptions = &(pstInfo->stWantOptions);
    pstGotOptions = &(pstInfo->stGotOptions);
    pstHisOptions = &(pstInfo->stHisOptions);

    /* ��������ȱʡֵ */

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_LCP_OPTION_S));

    PPP_MemSet((VOID*)&stRenegoOptions, 0, sizeof(stRenegoOptions)); /* Added by heyajun kf1199 at 2005-02-23 V800R002C01B011 for BYHD04876 */

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)&stRenegoOptions, (VOID*)pstGotOptions, sizeof(PPP_LCP_OPTION_S));
    }

    /* ϣ��Э�̵�ѡ�� */
    pstWantOptions->neg_mru = 1;
    pstWantOptions->neg_asyncmap = 0;
    pstWantOptions->neg_upap = 0;
    pstWantOptions->neg_eap = 0;

    /* Added start by ZhangJun HT04406 at 2005-09-21 for PPP��Ȩ */
    pstWantOptions->neg_chap = 0;
    /* Added end by ZhangJun HT04406 at 2005-09-21 for PPP��Ȩ */
    pstWantOptions->neg_magicnumber = 1;

    pstWantOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstWantOptions->neg_accompression = g_ulACompressOnoff;
    pstWantOptions->neg_lqr   = 0;
    pstWantOptions->neg_mrru  = 0;
    pstWantOptions->neg_ssnhf = 0;
    pstWantOptions->neg_discr = 0;
    pstWantOptions->neg_callback = 0;

    /*VA��MTUȡ����VT   2002/4/28
    pstWantOptions->mru               = (USHORT)IF_GetConfigMTU(IF_GetIfByIndex(pstPppInfo->ulIfIndex));*/

    /* modified by gxf 20030224 */
    /*pstWantOptions->mru               = (USHORT)IF_GetConfigMTU(IF_GETTOPIF(IF_GetIfByIndex(pstPppInfo->ulIfIndex)));*/
    pstWantOptions->mru = pstConfig->usMru;

    /* ����Э�̵�ѡ�� */
    *pstAllowOptions = *pstWantOptions;
    pstAllowOptions->neg_mru  = 1;
    pstAllowOptions->neg_upap = 0;
    pstAllowOptions->neg_chap = 0;
    pstAllowOptions->neg_eap = 0;

    pstAllowOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstAllowOptions->neg_accompression = g_ulACompressOnoff;

    /* ���������ò���ֵ */

    if (pstPppInfo->bIsAsync)  /* �첽��ʽ,Э��ACCMAP */
    {
        pstWantOptions->neg_asyncmap  = 1;
        pstAllowOptions->neg_asyncmap = 1;

        pstWantOptions->asyncmap = pstPppInfo->ulLocalAccm;
    }

    if (pstConfig->bAuthRmtPap)
    {
        pstWantOptions->neg_upap = 1;
    }

    if (pstConfig->bAuthRmtChap)
    {
        pstWantOptions->neg_chap = 1;
    }

    if (pstConfig->bAuthRmtEap)
    {
        pstWantOptions->neg_eap = 1;
    }

    /* ���õ����ҵ�ѡ�� */
    *pstGotOptions = *pstWantOptions;

    /* �޸����������޸��������� */
    pstGotOptions->numloops = 0;
    pstPppInfo->bLoopBacked = 0;
    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    /* modified by gxf for GGSN80 20030224  ulEchoTimeOutTime=0����������Echo
       Request�Ķ�ʱ��*/
    pstFsm->ulEchoTimeOutTime = 0 /*IF_GetIfByIndex(pstPppInfo->ulIfIndex)->if_ulKeepAlive*/;

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&stRenegoOptions, sizeof(PPP_LCP_OPTION_S));
        *pstWantOptions = *pstGotOptions;
    }

    return;
}


/****************************************************************************
* CREATE DATE  ��2000/04/04                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��ȷ��LCP��ҪЭ����Щ����,��LCP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��״̬����ִ��tls�����ĺ�PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_LCP_resetci(PPPFSM_S *pstFsm)
{
    PPPLCPINFO_S *pstInfo;
    PPPCONFIGINFO_S *pstConfig;
    PPPINFO_S *pstPppInfo;
    PPP_LCP_OPTION_S *pstAllowOptions, *pstWantOptions;
    PPP_LCP_OPTION_S *pstGotOptions, *pstHisOptions;
    PPP_LCP_OPTION_S stRenegoOptions; /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */

    if ( VOS_TRUE == g_ulHsgwA10TestDbgFlg )
    {
         PPP_LCP_resetci_TestStub(pstFsm);
         return;
    }

    PPP_TRACE("\r\n---Into PPP_LCP_resetci---\r\n");

    pstInfo = (PPPLCPINFO_S *)pstFsm->pProtocolInfo;
    pstPppInfo = pstInfo->pstPppInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;

    pstAllowOptions = &(pstInfo->stAllowOptions);
    pstWantOptions = &(pstInfo->stWantOptions);
    pstGotOptions = &(pstInfo->stGotOptions);
    pstHisOptions = &(pstInfo->stHisOptions);

    /* ��������ȱʡֵ */

    /* pstHisOptions ���� */
    PPP_MemSet((VOID*)pstHisOptions, 0, sizeof(PPP_LCP_OPTION_S));

    PPP_MemSet((VOID*)&stRenegoOptions, 0, sizeof(stRenegoOptions)); /* Added by heyajun kf1199 at 2005-02-23 V800R002C01B011 for BYHD04876 */

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)&stRenegoOptions, (VOID*)pstGotOptions, sizeof(PPP_LCP_OPTION_S));
    }

    /* ϣ��Э�̵�ѡ�� */
    pstWantOptions->neg_mru = 1;
    pstWantOptions->neg_asyncmap = 0;
    pstWantOptions->neg_upap = 0;
    pstWantOptions->neg_eap = 0;

    /* Added start by ZhangJun HT04406 at 2005-09-21 for PPP��Ȩ */
    pstWantOptions->neg_chap = 0;
    /* Added end by ZhangJun HT04406 at 2005-09-21 for PPP��Ȩ */
    pstWantOptions->neg_magicnumber = 1;

    pstWantOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstWantOptions->neg_accompression = g_ulACompressOnoff;
    pstWantOptions->neg_lqr   = 0;
    pstWantOptions->neg_mrru  = 0;
    pstWantOptions->neg_ssnhf = 0;
    pstWantOptions->neg_discr = 0;
    pstWantOptions->neg_callback = 0;

    /*VA��MTUȡ����VT   2002/4/28
    pstWantOptions->mru               = (USHORT)IF_GetConfigMTU(IF_GetIfByIndex(pstPppInfo->ulIfIndex));*/

    /* modified by gxf 20030224 */
    /*pstWantOptions->mru               = (USHORT)IF_GetConfigMTU(IF_GETTOPIF(IF_GetIfByIndex(pstPppInfo->ulIfIndex)));*/
    pstWantOptions->mru = pstConfig->usMru;

    /* ����Э�̵�ѡ�� */
    *pstAllowOptions = *pstWantOptions;
    pstAllowOptions->neg_mru  = 1;
    pstAllowOptions->neg_upap = 1;
    pstAllowOptions->neg_chap = 1;
    pstAllowOptions->neg_eap = 0;

    pstAllowOptions->neg_pcompression  = g_ulPCompressOnoff;
    pstAllowOptions->neg_accompression = g_ulACompressOnoff;

    /* ���������ò���ֵ */

    if (pstPppInfo->bIsAsync)  /* �첽��ʽ,Э��ACCMAP */
    {
        pstWantOptions->neg_asyncmap  = 1;
        pstAllowOptions->neg_asyncmap = 1;

        pstWantOptions->asyncmap = pstPppInfo->ulLocalAccm;
    }

    if (pstConfig->bAuthRmtPap)
    {
        pstWantOptions->neg_upap = 1;
    }

    if (pstConfig->bAuthRmtChap)
    {
        pstWantOptions->neg_chap = 1;
    }

    if (pstConfig->bAuthRmtEap)
    {
        pstWantOptions->neg_eap = 1;
    }

    /* ���õ����ҵ�ѡ�� */
    *pstGotOptions = *pstWantOptions;

    /* �޸����������޸��������� */
    pstGotOptions->numloops = 0;
    pstPppInfo->bLoopBacked = 0;

    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;

    /* modified by gxf for GGSN80 20030224  ulEchoTimeOutTime=0����������Echo
       Request�Ķ�ʱ��*/
    pstFsm->ulEchoTimeOutTime = 0 /*IF_GetIfByIndex(pstPppInfo->ulIfIndex)->if_ulKeepAlive*/;

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    if ((pstPppInfo->bReNego) ||(pstPppInfo->bReNegoV6))
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&stRenegoOptions, sizeof(PPP_LCP_OPTION_S));
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
USHORT PPP_LCP_cilen(PPPFSM_S *pstFsm)
{
    PPP_LCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    /*
     * NB: we only ask for one of CHAP and UPAP, even if we will
     * accept either.
     */


    if (VOS_FALSE == SOFTPARA_BIT1395)
    {
        /* CHAP���� */
        return (USHORT)(PPP_LENCISHORT(pstGotOptions->neg_mru) +
                       PPP_LENCILONG(pstGotOptions->neg_asyncmap) +
                       PPP_LENCICHAP(pstGotOptions->neg_chap) +
                       PPP_LENCISHORT((!pstGotOptions->neg_chap && pstGotOptions->neg_upap)) +
                       PPP_LENCISHORT(pstGotOptions->neg_eap) +
                       PPP_LENCILQR(pstGotOptions->neg_lqr) +
                       PPP_LENCILONG(pstGotOptions->neg_magicnumber) +
                       PPP_LENCIVOID(pstGotOptions->neg_pcompression) +
                       PPP_LENCIVOID(pstGotOptions->neg_accompression) +
                       PPP_LENCISHORT(pstGotOptions->neg_mrru) +
                       PPP_LENCIVOID(pstGotOptions->neg_ssnhf) +
                       PPP_LENCIDISCR(pstGotOptions->neg_discr) +
                       PPP_LENCALLBACK(pstGotOptions->neg_callback)
        );
    }
    else
    {
        /* PAP���� */
        return (USHORT)(PPP_LENCISHORT(pstGotOptions->neg_mru) +
                       PPP_LENCILONG(pstGotOptions->neg_asyncmap) +
                       PPP_LENCISHORT(pstGotOptions->neg_upap) +
                       PPP_LENCICHAP((pstGotOptions->neg_chap && !pstGotOptions->neg_upap)) +
                       PPP_LENCISHORT(pstGotOptions->neg_eap) +
                       PPP_LENCILQR(pstGotOptions->neg_lqr) +
                       PPP_LENCILONG(pstGotOptions->neg_magicnumber) +
                       PPP_LENCIVOID(pstGotOptions->neg_pcompression) +
                       PPP_LENCIVOID(pstGotOptions->neg_accompression) +
                       PPP_LENCISHORT(pstGotOptions->neg_mrru) +
                       PPP_LENCIVOID(pstGotOptions->neg_ssnhf) +
                       PPP_LENCIDISCR(pstGotOptions->neg_discr) +
                       PPP_LENCALLBACK(pstGotOptions->neg_callback)
        );
    }

    /*End of liushuang*/
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
VOID PPP_LCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket)
{
    PPP_LCP_OPTION_S *pstGotOptions;

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstGotOptions->magicnumber = PPP_GetMagicNumber();

    ADDCISHORT(LCP_CI_MRU,
               pstGotOptions->neg_mru,
               pstGotOptions->mru
    );

    ADDCILONG(LCP_CI_ASYNCMAP,
              pstGotOptions->neg_asyncmap,
              pstGotOptions->asyncmap
    );

    if (VOS_FALSE == SOFTPARA_BIT1395)
    {
        /* CHAP���� */
        ADDCICHAP(LCP_CI_AUTHTYPE,
                  pstGotOptions->neg_chap,
                  (USHORT)PPP_CHAP,
                  pstGotOptions->chap_mdtype
        );

        ADDCISHORT(LCP_CI_AUTHTYPE,
                   !pstGotOptions->neg_chap && pstGotOptions->neg_upap,
                   (USHORT)PPP_PAP
        );
    }
    else
    {
        /* PAP���� */
        ADDCISHORT(LCP_CI_AUTHTYPE,
                   pstGotOptions->neg_upap,
                   (USHORT)PPP_PAP
        );
        ADDCICHAP(LCP_CI_AUTHTYPE,
                  pstGotOptions->neg_chap && !pstGotOptions->neg_upap,
                  (USHORT)PPP_CHAP,
                  pstGotOptions->chap_mdtype
        );
    }
  /*End of liushuang*/

    ADDCISHORT(LCP_CI_AUTHTYPE,
             pstGotOptions->neg_eap,
             (USHORT)PPP_EAP
    );

    ADDCILQR(LCP_CI_QUALITY,
             pstGotOptions->neg_lqr,
             pstGotOptions->lqr_period
    );

    ADDCILONG(LCP_CI_MAGICNUMBER,
              pstGotOptions->neg_magicnumber,
              pstGotOptions->magicnumber);

    ADDCIVOID(LCP_CI_PCOMPRESSION,
              pstGotOptions->neg_pcompression
    );

    ADDCIVOID(LCP_CI_ACCOMPRESSION,
              pstGotOptions->neg_accompression
    );

    ADDCISHORT(LCP_CI_MRRU,
               pstGotOptions->neg_mrru,
               pstGotOptions->mrru
    );

    ADDCIVOID(LCP_CI_SSNHF,
              pstGotOptions->neg_ssnhf
    );

    ADDCIDISCR(LCP_CI_DISCR,
               pstGotOptions->neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    ADDCICALLBACK(LCP_CI_CALLBACK,
                  pstGotOptions->neg_callback,
                  pstGotOptions->callbackopr,
                  pstGotOptions->callbackinfo,
                  (ULONG)(pstGotOptions->callbacklen)
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
USHORT PPP_LCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions;
    UCHAR cilen, citype, cichar;
    USHORT cishort;
    ULONG cilong;


    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);

    if (ulLen == 0)
    {
        return VOS_OK;
    }
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 1. \r\n");/*add by chenmin00265046*/

    /* L2TP��Ҫ�Ĳ��� */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* ˵��:����VRP1.2�ĳ����޸Ķ���.
            Э����˵Ӧ��¼���һ�����͵ı���,ʵ��VRP1.2
            �м�¼��ȴ�ǽ��յ����һ��ACK����,��֪��û��ʲô���� */
    {
        PPPINFO_S *pstPppInfo = (PPPINFO_S*)(pstFsm->pPppInfo);
        if (pstPppInfo->pL2tpPara != NULL)
        {
            L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

            /* �������һ�����յ�ACK���� */
            pstOptionalPara->ulLastSentLen = ulLen;
            VOS_MemCpy(pstOptionalPara->szLastSent, pPacket, ulLen);
        }
    }
#endif

    ACKCISHORT(LCP_CI_MRU, pstGotOptions->neg_mru, pstGotOptions->mru);
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 2. \r\n");/*add by chenmin00265046*/

    ACKCILONG(LCP_CI_ASYNCMAP,
              pstGotOptions->neg_asyncmap,
              pstGotOptions->asyncmap
    );
    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 3. \r\n");/*add by chenmin00265046*/

    if (VOS_FALSE == SOFTPARA_BIT1395)
    {
        /* CHAP���� */
        ACKCICHAP(LCP_CI_AUTHTYPE,
                  pstGotOptions->neg_chap,
                  PPP_CHAP,
                  pstGotOptions->chap_mdtype
        );

        PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 4. \r\n");/*add by chenmin00265046*/

        ACKCISHORT(LCP_CI_AUTHTYPE,
                   !pstGotOptions->neg_chap && pstGotOptions->neg_upap,
                   PPP_PAP
        );

        PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 5. \r\n");/*add by chenmin00265046*/

    }
    else
    {
        /* PAP���� */
        ACKCISHORT(LCP_CI_AUTHTYPE,
                   pstGotOptions->neg_upap,
                   PPP_PAP
        );

        PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 6. \r\n");/*add by chenmin00265046*/

        ACKCICHAP(LCP_CI_AUTHTYPE,
                  pstGotOptions->neg_chap && !pstGotOptions->neg_upap,
                  PPP_CHAP,
                  pstGotOptions->chap_mdtype
        );

        PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 7. \r\n");/*add by chenmin00265046*/

    }
    /*End of liushuang*/

    ACKCISHORT(LCP_CI_AUTHTYPE,
               pstGotOptions->neg_eap,
               PPP_EAP
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 8. \r\n");/*add by chenmin00265046*/

    ACKCILQR(LCP_CI_QUALITY,
             pstGotOptions->neg_lqr,
             pstGotOptions->lqr_period
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 9. \r\n");/*add by chenmin00265046*/

    ACKCILONG(LCP_CI_MAGICNUMBER,
              pstGotOptions->neg_magicnumber,
              pstGotOptions->magicnumber
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 10. \r\n");/*add by chenmin00265046*/

    ACKCIVOID(LCP_CI_PCOMPRESSION,
              pstGotOptions->neg_pcompression
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 11. \r\n");/*add by chenmin00265046*/

    ACKCIVOID(LCP_CI_ACCOMPRESSION,
              pstGotOptions->neg_accompression
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 12. \r\n");/*add by chenmin00265046*/

    ACKCISHORT(LCP_CI_MRRU,
               pstGotOptions->neg_mrru,
               pstGotOptions->mrru
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 13. \r\n");/*add by chenmin00265046*/

    ACKCIVOID(LCP_CI_SSNHF,
              pstGotOptions->neg_ssnhf
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 14. \r\n");/*add by chenmin00265046*/

    ACKCIDISCR(LCP_CI_DISCR,
               pstGotOptions->neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    PPPC_INFO_LOG("\r\n c00265046:PPP_LCP_ackci 15. \r\n");/*add by chenmin00265046*/

    ACKCALLBACK(LCP_CI_CALLBACK,
                pstGotOptions->neg_callback,
                pstGotOptions->callbackopr,
                pstGotOptions->callbackinfo,
                (ULONG)(pstGotOptions->callbacklen)
    );

    PPPC_INFO_LOG1("\r\n c00265046_1:  PPP_LCP_ackci ulLen. \r\n", ulLen);/*add by chenmin00265046*/

    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_234);
        PPPC_WARNING_LOG("\r\n c00265046_1:  PPP_LCP_ackci bad. \r\n");
        goto bad;
    }
    /*lint +e801*/

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_ackci: received bad Ack!");
    PPP_DBG_ERR_CNT(PPP_PHERR_235);
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
USHORT PPP_LCP_nakci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions, *pstWantOptions;
    PPP_LCP_OPTION_S stNoOption;  /* ���Է�no����ѡ�� */
    PPP_LCP_OPTION_S stTryOption; /* ������Է�Э�̵�ѡ�� */
    PPPINFO_S *pstPppInfo;
    UCHAR citype, cichar, *next;
    USHORT cishort;
    ULONG cilong;
    ULONG looped_back = 0;
    SHORT cilen;

    pstGotOptions  = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstWantOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stWantOptions);

    pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;

    PPP_MemSet((VOID*)(&stNoOption), 0, sizeof(PPP_LCP_OPTION_S));
    stTryOption = *pstGotOptions;

    /*
     * Any Nak'd CIs must be in exactly the same order that we sent.
     * Check packet length and CI length at each step.
     * If we find any deviations, then this packet is bad.
     */

    /******************************************************************
     * no nak comp packets;
     *******************************************************************/

    /*
     * We don't care if they want to send us smaller packets than
     * we want.  Therefore, accept any MRU less than what we asked for,
     * but then ignore the new value when setting the MRU in the kernel.
     * If they send us a bigger MRU than what we asked, accept it, up to
     * the limit of the default MRU we'd get if we didn't negotiate.
     */
    NAKCISHORT(LCP_CI_MRU, neg_mru,
               if ((cishort <= pstWantOptions->mru) || (cishort <= PPP_DEFMRU))
               {
                   stTryOption.mru = cishort;
               }

    );

    /*
     * Add any characters they want to our (receive-side) asyncmap.
     */
    NAKCILONG(LCP_CI_ASYNCMAP, neg_asyncmap,
              stTryOption.asyncmap = pstGotOptions->asyncmap | cilong;
    );

    /*
     * If they've nak'd our authentication-protocol, check whether
     * they are proposing a different protocol, or a different
     * hash algorithm for CHAP.
     */
    /*lint -e801*/
    if ((pstGotOptions->neg_chap || pstGotOptions->neg_upap)
        && (ulLen >= PPP_CILEN_SHORT)
        && (pPacket[0] == LCP_CI_AUTHTYPE) && (pPacket[1] >= PPP_CILEN_SHORT))
    {
        cilen = pPacket[1];
        PPP_INCPTR(2, pPacket);
        PPP_GETSHORT(cishort, pPacket);
        ulLen -= 4;
        if ((cishort == PPP_PAP) && (cilen == PPP_CILEN_SHORT))
        {
            /*
             * If they are asking for PAP, then they don't want to do CHAP.
             * If we weren't asking for CHAP, then we were asking for PAP,
             * in which case this Nak is bad.
             */
            if (!pstGotOptions->neg_chap)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_236);
                goto bad;
            }

            stTryOption.neg_chap = 0;
        }
        else
        {
            if ((cishort == PPP_CHAP) && (cilen == PPP_CILEN_CHAP))
            {
                PPP_GETCHAR(cichar, pPacket);
                ulLen -= 1;
                if (pstGotOptions->neg_chap)
                {
                    /*
                     * We were asking for CHAP/MD5; they must want a different
                     * algorithm.  If they can't do MD5, we'll have to stop
                     * asking for CHAP.
                     */
                    if (cichar != pstGotOptions->chap_mdtype)
                    {
                        stTryOption.neg_chap = 0;
                    }
                    else if (VOS_TRUE == SOFTPARA_BIT1395)
                    {
                        stTryOption.neg_upap = 0;
                    }
                    /*End of liushuang*/
                }
                else
                {
                    /*
                     * Stop asking for PAP if we were asking for it.
                     */
                    stTryOption.neg_upap = 0;
                }
            }
            else
            {
                /*
                 * We don't recognize what they're suggesting.
                 * Stop asking for what we were asking for.
                 */
                if (pstGotOptions->neg_chap)
                {
                    stTryOption.neg_chap = 0;
                }
                else
                {
                    stTryOption.neg_upap = 0;
                }

                pPacket += cilen - PPP_CILEN_SHORT;
                ulLen -= cilen - PPP_CILEN_SHORT;
            }
        }
    }

    /*
     * Peer shouldn't send Nak for protocol compression or
     * address/control compression requests; they should send
     * a Reject instead.  If they send a Nak, treat it as a Reject.
     */
    if (!pstGotOptions->neg_chap)
    {
        NAKCISHORT(LCP_CI_AUTHTYPE, neg_upap,
                   stTryOption.neg_upap = 0;
        );
    }

    NAKCISHORT(LCP_CI_AUTHTYPE, neg_eap,
               stTryOption.neg_eap = 0;
    );

    /*
     * If they can't cope with our link quality protocol, we'll have
     * to stop asking for LQR.  We haven't got any other protocol.
     * If they Nak the reporting period, take their value XXX ?
     */
    NAKCILQR(LCP_CI_QUALITY, neg_lqr,
             if (cishort != PPP_LQR)
             {
                 stTryOption.neg_lqr = 0;
             }
             else
             {
                 stTryOption.lqr_period = cilong;
             }

    );

    /*
     * Check for a looped-back line.
     */
    NAKCILONG(LCP_CI_MAGICNUMBER, neg_magicnumber,
              stTryOption.magicnumber = PPP_GetMagicNumber();
              looped_back = 1;
    );

    NAKCIVOID(LCP_CI_PCOMPRESSION, neg_pcompression,
              stTryOption.neg_pcompression = 0;
    );
    NAKCIVOID(LCP_CI_ACCOMPRESSION, neg_accompression,
              stTryOption.neg_accompression = 0;
    );

    /*modified by huzhiyong 2001/12/30 */

    /*
    NAKCISHORT(LCP_CI_MRRU, neg_mrru,
       if (cishort <= pstWantOptions->mrru || cishort < PPP_DEFMRRU)
            stTryOption.mrru = cishort;
       );
     */
    NAKCISHORT(LCP_CI_MRRU, neg_mrru,
               if ((cishort <= pstWantOptions->mrru) || (cishort <= PPP_DEFMRRU))
               {
                   stTryOption.mrru = cishort;
               }

    );
    NAKCIVOID(LCP_CI_SSNHF, neg_ssnhf,
              stTryOption.neg_ssnhf = 0;
    );

    NAKCIDISCR(LCP_CI_DISCR, neg_discr,
               stTryOption.neg_discr = 0;
    );

    NAKCICALLBACK(LCP_CI_CALLBACK, neg_callback);

    while (ulLen > PPP_CILEN_VOID)
    {
        PPP_GETCHAR(citype, pPacket);
        PPP_GETCHAR(cilen, pPacket);

        if (cilen < 2)/*���ӶԷǷ�����������Ĵ���*/
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_237);
            goto bad;
        }

        ulLen = (ULONG)(ulLen - cilen);
        if ((LONG)ulLen < 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_238);
            goto bad;
        }

        next = pPacket + cilen - 2;

        switch (citype)
        {
            case LCP_CI_MRU:
                if (pstGotOptions->neg_mru
               || stNoOption.neg_mru
               || (cilen != PPP_CILEN_SHORT))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_239);
                    goto bad;
                }

                break;

            case LCP_CI_ASYNCMAP:
                if (pstGotOptions->neg_asyncmap
               || stNoOption.neg_asyncmap
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_240);
                    goto bad;
                }

                break;

            case LCP_CI_AUTHTYPE:
                if (pstGotOptions->neg_chap
               || stNoOption.neg_chap
               || pstGotOptions->neg_upap
               || stNoOption.neg_upap)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_241);
                    goto bad;
                }

                break;

            case LCP_CI_MAGICNUMBER:
                if (pstGotOptions->neg_magicnumber
               || stNoOption.neg_magicnumber
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_242);
                    goto bad;
                }

                break;

            case LCP_CI_PCOMPRESSION:
                if (pstGotOptions->neg_pcompression
               || stNoOption.neg_pcompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_243);
                    goto bad;
                }

                break;

            case LCP_CI_ACCOMPRESSION:
                if (pstGotOptions->neg_accompression
               || stNoOption.neg_accompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_244);
                    goto bad;
                }

                break;

            case LCP_CI_QUALITY:
                if (pstGotOptions->neg_lqr
               || stNoOption.neg_lqr
               || (cilen != PPP_CILEN_LQR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_245);
                    goto bad;
                }

                break;
            case LCP_CI_CALLBACK:
                if (pstGotOptions->neg_callback
               || stNoOption.neg_callback
               || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_246);
                    goto bad;
                }

                break;
            default:
                break;
        }

        pPacket = next;
    }

    /* If there is still anything left, this packet is bad. */
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_247);
        goto bad;
    }
    /*lint +e801*/

    /*
     * OK, the Nak is good.  Now we can update state.
     */
    if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
    {
        if (looped_back)
        {
            if (++stTryOption.numloops >= PPP_MAXLOOPSBACK)
            {
                PPP_Debug_Error(pstFsm, PPP_LOG_NOTICE, "Serial line is looped back.");
                pstPppInfo->bLoopBacked = 1;
                PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_LOOPBACK);
                PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
            }
        }
        else
        {
            stTryOption.numloops = 0;
        }

        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_nakci: received bad Nak!");
    return VOS_ERR;
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
USHORT PPP_LCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen)
{
    PPP_LCP_OPTION_S *pstGotOptions;
    UCHAR cichar   = 0;
    USHORT cishort = 0;
    ULONG cilong;
    PPP_LCP_OPTION_S stTryOption;        /* options to request next time */

    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    stTryOption = *pstGotOptions;

    REJCISHORT(LCP_CI_MRU,
               neg_mru,
               pstGotOptions->mru
    );

    REJCILONG(LCP_CI_ASYNCMAP,
              neg_asyncmap,
              pstGotOptions->asyncmap
    );

    /* ����PPPЭ��RFC1661��LCP����ѡ����ACCMѡ������п��ܻ�ܾ���ѡ�
       �������LCPЭ�̲�֧���첽ӳ��ѡ���ô�첽ӳ��Ĭ��ֵ�趨Ϊ0 */
    if (0 == stTryOption.neg_asyncmap)
    {
        stTryOption.asyncmap = 0;
    }


    if (VOS_FALSE == SOFTPARA_BIT1395)
    {
        /* CHAP���� */
        REJCICHAP(LCP_CI_AUTHTYPE,
                  neg_chap,
                  PPP_CHAP,
                  pstGotOptions->chap_mdtype
        );

        if (!pstGotOptions->neg_chap)
        {
            REJCISHORT(LCP_CI_AUTHTYPE,
                       neg_upap,
                       PPP_PAP
            );
        }
    }
    else
    {
        REJCIPAP(LCP_CI_AUTHTYPE,
                   neg_upap,
                   PPP_PAP
        );
        if (!pstGotOptions->neg_upap)
        {
            REJCICHAP(LCP_CI_AUTHTYPE,
                      neg_chap,
                      PPP_CHAP,
                      pstGotOptions->chap_mdtype
            );
        }
    }

    REJCISHORT(LCP_CI_AUTHTYPE,
               neg_eap,
               PPP_EAP
    );

    REJCILQR(LCP_CI_QUALITY,
             neg_lqr,
             pstGotOptions->lqr_period
    );

    REJCILONG(LCP_CI_MAGICNUMBER,
              neg_magicnumber,
              pstGotOptions->magicnumber
    );

    REJCIVOID(LCP_CI_PCOMPRESSION,
              neg_pcompression
    );

    REJCIVOID(LCP_CI_ACCOMPRESSION,
              neg_accompression
    );

    REJCISHORT(LCP_CI_MRRU,
               neg_mrru,
               pstGotOptions->mrru
    );

    REJCIVOID(LCP_CI_SSNHF,
              neg_ssnhf
    );

    REJCIDISCR(LCP_CI_DISCR,
               neg_discr,
               pstGotOptions->discr_class,
               pstGotOptions->discr_len,
               pstGotOptions->discr_addr
    );

    REJCICALLBACK(LCP_CI_CALLBACK,
                  neg_callback,
                  (ULONG)(pstGotOptions->callbacklen),
                  pstGotOptions->callbackopr,
                  pstGotOptions->callbackinfo
    );

    /*
     * If there are any remaining CIs, then this packet is bad.
     */

    PPPC_INFO_LOG("\r\n c00265046_1: PPP_LCP_rejci. \r\n");/*add by chenmin00265046*/

    /*lint -e801*/
    if (ulLen != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_248);
        PPPC_WARNING_LOG("\r\n c00265046_1: PPP_LCP_rejci bad. \r\n");
        goto bad;
    }
    /*lint +e801*/

    /*
     * Now we can update state.
     */
    if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
    {
        *pstGotOptions = stTryOption;
    }

    return VOS_OK;

bad:
    PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_rejci: received bad Reject!");

    return VOS_ERR;
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
UCHAR PPP_LCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG *pulLen)
{
    PPP_LCP_OPTION_S *pstAllowOptions;
    PPP_LCP_OPTION_S *pstGotOptions;
    PPP_LCP_OPTION_S *pstHisOptions;

    UCHAR *cip, *next, *currentpos;      /* Pointer to current and next CIs */

    UCHAR cilen, citype, cichar;/* Parsed len, type, char value */
    USHORT cishort;         /* Parsed short value */
    ULONG cilong;           /* Parse long value */
    UCHAR rc = CONFACK;        /* Final packet return code */
    SHORT orc;                /* Individual option return code */

    UCHAR *rejp;            /* Pointer to next char in reject frame */
    UCHAR *nakp;            /* Pointer to next char in Nak frame */
    LONG l = (LONG)*pulLen;        /* Length left */
    UCHAR nak_buffer[PPP_DEFAULT_NEGO_PACKET_LEN];

    /* L2TP��Ҫ�Ĳ��� */
 #if (VRP_MODULE_SEC_L2TP == VRP_YES)
    PPPINFO_S *pstPppInfo = (PPPINFO_S*)(pstFsm->pPppInfo);
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* ���µ�һ�����յ�LCP Conf-Req������ */
        if (pstOptionalPara->ulInitialRcvLen == 0)
        {
            pstOptionalPara->ulInitialRcvLen = *pulLen;
            VOS_MemCpy(pstOptionalPara->szInitialRcv, (CHAR*)pPacket, *pulLen);
        }

        /* �������һ�����յ�LCP Conf-Req���� */
        pstOptionalPara->ulLastRcvLen = *pulLen;
        VOS_MemCpy(pstOptionalPara->szLastRcv, (CHAR*)pPacket, *pulLen);
    }
 #endif

    pstAllowOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stAllowOptions);
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    pstHisOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stHisOptions);

    /*
     * Reset all his options.
     */
    (VOID)VOS_MemSet(pstHisOptions, 0, sizeof(PPP_LCP_OPTION_S));
    if (1 == pstAllowOptions->neg_asyncmap)
    {
        pstHisOptions->asyncmap = 0xffffffff;
    }

    /*
     * Process all his options.
     */
    next = pPacket;
    nakp = nak_buffer;
    rejp = pPacket;

    rc = CONFACK;            /* Assume success */

    if (l == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_915);
        return rc;
    }

    while (l)
    {
        orc = CONFACK;           /* Assume success */
        currentpos = next;            /* Remember begining of CI */
        cip = next;
        /*lint -e801*/
        if ((l < 2)               /* Not enough data for CI header or */
           || (currentpos[1] < 2)           /*  CI length too small or */
           || (currentpos[1] > l))
        {
            /*  CI length too big? */
            PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "lcp_reqci: bad CI length!");
            orc   = CONFREJ;      /* Reject bad CI */
            cilen = (UCHAR)l;            /* Reject till end of packet */
            l = 0;            /* Don't loop again */
            PPP_DBG_OK_CNT(PPP_PHOK_916);
            goto endswitch;
        }
        /*lint +e801*/

        PPP_GETCHAR(citype, currentpos);        /* Parse CI type */
        PPP_GETCHAR(cilen, currentpos);        /* Parse CI length */
        l -= cilen;                /* Adjust remaining length */

        next += cilen;            /* Step to next CI */

        switch (citype)
        {
            /* Check CI type */
            case LCP_CI_MRU:
                if (!pstAllowOptions->neg_mru       /* Allow option? */
               || (cilen != PPP_CILEN_SHORT))
                {
                    /* Check CI length */
                    orc = CONFREJ;    /* Reject CI */
                    PPP_DBG_ERR_CNT(PPP_PHERR_249);
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);/* Parse MRU */

                /*
                 * He must be able to receive at least our minimum.
                 * No need to check a maximum.  If he sends a large number,
                 * we'll just ignore it.
                 */
                if ((cishort < PPP_MINMRU) && (rc != CONFREJ))
                {
                    orc = CONFNAK;    /* Nak CI */
                    PPP_PUTCHAR(LCP_CI_MRU, nakp);
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                    PPP_PUTSHORT(PPP_MINMRU, nakp);/* Give him a hint */
                    PPP_DBG_OK_CNT(PPP_PHOK_917);
                    break;
                }

                pstHisOptions->neg_mru = 1;    /* Remember he sent MRU */
                pstHisOptions->mru = cishort;    /* And remember value */
                break;

            case LCP_CI_ASYNCMAP:
                if (!pstAllowOptions->neg_asyncmap
               || (cilen != PPP_CILEN_LONG))
                {
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_250);
                    break;
                }

                PPP_GETLONG(cilong, currentpos);

                /*
                 * Asyncmap must have set at least the bits
                 * which are set in lcp_allowoptions[unit].asyncmap.
                 */
                if (((pstAllowOptions->asyncmap & ~cilong) != 0) && (rc != CONFREJ))
                {
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_ASYNCMAP, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LONG, nakp);
                    PPP_PUTLONG((pstAllowOptions->asyncmap | cilong), nakp);
                    PPP_DBG_OK_CNT(PPP_PHOK_918);
                    break;
                }

                pstHisOptions->neg_asyncmap = 1;
                pstHisOptions->asyncmap = cilong;
                break;

            case LCP_CI_AUTHTYPE:
                if ((cilen < PPP_CILEN_SHORT)
               || !(pstAllowOptions->neg_upap || pstAllowOptions->neg_chap || pstAllowOptions->neg_eap))
                {
                    /*
                     * Reject the option if we're not willing to authenticate.
                     */
                    orc = CONFREJ;
                    PPP_DBG_ERR_CNT(PPP_PHERR_251);
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);

                /*
                 * Authtype must be UPAP or CHAP.
                 *
                 * Note: if both pstAllowOptions->neg_upap and pstAllowOptions->neg_chap are set,
                 * and the peer sends a Configure-Request with two
                 * authenticate-protocol requests, one for CHAP and one
                 * for UPAP, then we will reject the second request.
                 * Whether we end up doing CHAP or UPAP depends then on
                 * the ordering of the CIs in the peer's Configure-Request.
                 */
/* L2TP��Ҫ�Ĳ��� */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)

                if (pstPppInfo->bEhrpdUser)
                {
                    if (cishort == PPP_EAP)
                    {
                        if (cilen != PPP_CILEN_SHORT)
                        {
                            orc = CONFREJ;
                            PPP_DBG_ERR_CNT(PPP_PHERR_252);
                            break;
                        }

                        pstHisOptions->neg_eap = 1;
                        break;
                    }
                }
                else
                {
#endif
                    if (cishort == PPP_PAP)
                    {
                        if (pstHisOptions->neg_chap   /* we've already accepted CHAP */
                       || (cilen != PPP_CILEN_SHORT))
                        {
                            orc = CONFREJ;
                            PPP_DBG_ERR_CNT(PPP_PHERR_253);
                            break;
                        }

                        if (!pstAllowOptions->neg_upap && (rc != CONFREJ))
                        {
                            /* we don't want to do PAP */
                            orc = CONFNAK;/* NAK it and suggest CHAP */
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                            PPP_PUTSHORT(PPP_CHAP, nakp);
                            PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                            PPP_DBG_OK_CNT(PPP_PHOK_919);
                            break;
                        }

                        pstHisOptions->neg_upap = 1;
                        break;
                    }

                    if (cishort == PPP_CHAP)
                    {
                        if (pstHisOptions->neg_upap   /* we've already accepted PAP */
                       || (cilen != PPP_CILEN_CHAP))
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_254);
                            orc = CONFREJ;
                            break;
                        }

                        if (!pstAllowOptions->neg_chap && (rc != CONFREJ))
                        {
                            PPP_DBG_OK_CNT(PPP_PHOK_920);
                            /* we don't want to do CHAP */
                            orc = CONFNAK;/* NAK it and suggest PAP */
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                            PPP_PUTSHORT(PPP_PAP, nakp);
                            break;
                        }

                        PPP_GETCHAR(cichar, currentpos);/* get digest type*/
                        if ((cichar != pstAllowOptions->chap_mdtype) && (rc != CONFREJ))
                        {
                            PPP_DBG_OK_CNT(PPP_PHOK_921);
                            orc = CONFNAK;
                            PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);
                            PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                            PPP_PUTSHORT(PPP_CHAP, nakp);
                            PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                            break;
                        }

                        pstHisOptions->chap_mdtype = cichar;/* save md type */
                        pstHisOptions->neg_chap = 1;
                        break;
                    }
/* L2TP��Ҫ�Ĳ��� */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)

                }
#endif
                /*
                 * We don't recognize the protocol they're asking for.
                 * Nak it with something we're willing to do.
                 * (At this point we know pstAllowOptions->neg_upap || pstAllowOptions->neg_chap.)
                 */
                if (rc == CONFREJ)
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_255);
                    break;
                }

                orc = CONFNAK;
                PPP_PUTCHAR(LCP_CI_AUTHTYPE, nakp);

/* L2TP��Ҫ�Ĳ��� */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)

                if (pstPppInfo->bEhrpdUser)
                {
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                    PPP_PUTSHORT(PPP_EAP, nakp);
                }
                else
                {
#endif
                    if (pstAllowOptions->neg_chap)
                    {
                        PPP_PUTCHAR(PPP_CILEN_CHAP, nakp);
                        PPP_PUTSHORT(PPP_CHAP, nakp);
                        PPP_PUTCHAR(pstAllowOptions->chap_mdtype, nakp);
                    }
                    else
                    {
                        PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                        PPP_PUTSHORT(PPP_PAP, nakp);
                    }
/* L2TP��Ҫ�Ĳ��� */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)
                }
#endif
                break;

            case LCP_CI_QUALITY:
                if (!pstAllowOptions->neg_lqr
               || (cilen != PPP_CILEN_LQR))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_256);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);
                PPP_GETLONG(cilong, currentpos);

                /*
                 * Check the protocol and the reporting period.
                 * XXX When should we Nak this, and what with?
                 */
                if ((cishort != PPP_LQR) && (rc != CONFREJ))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_922);
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_QUALITY, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LQR, nakp);
                    PPP_PUTSHORT(PPP_LQR, nakp);
                    PPP_PUTLONG(pstAllowOptions->lqr_period, nakp);
                    break;
                }

                pstHisOptions->lqr_period = VOS_NTOHL(cilong);
                break;

            case LCP_CI_MAGICNUMBER:

                /* we should check if this link is loopbacked */
                if (!(pstAllowOptions->neg_magicnumber || pstGotOptions->neg_magicnumber)
               || (cilen != PPP_CILEN_LONG))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_257);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETLONG(cilong, currentpos);

                /*
                 * He must have a different magic number.
                 */
                if ((pstGotOptions->neg_magicnumber && (cilong == pstGotOptions->magicnumber))
                    || ((cilong == 0) && (rc != CONFREJ)))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_923);
                    cilong = PPP_GetMagicNumber();
                    orc = CONFNAK;
                    PPP_PUTCHAR(LCP_CI_MAGICNUMBER, nakp);
                    PPP_PUTCHAR(PPP_CILEN_LONG, nakp);
                    PPP_PUTLONG(cilong, nakp);
                    break;
                }

                pstHisOptions->neg_magicnumber = 1;
                pstHisOptions->magicnumber = cilong;
                break;

            case LCP_CI_PCOMPRESSION:
                if (!pstAllowOptions->neg_pcompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_258);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_pcompression = 1;
                break;

            case LCP_CI_ACCOMPRESSION:
                if (!pstAllowOptions->neg_accompression
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_259);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_accompression = 1;
                break;
            case LCP_CI_MRRU:
                if (!pstAllowOptions->neg_mrru || (cilen != PPP_CILEN_SHORT))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_260);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETSHORT(cishort, currentpos);/* Parse MRU */

                /*
                 * He must be able to receive at least our minimum.
                 * No need to check a maximum.  If he sends a large number,
                 * we'll just ignore it.
                 */
                if ((cishort < PPP_MINMRRU) && (rc != CONFREJ))
                {
                    PPP_DBG_OK_CNT(PPP_PHOK_924);
                    orc = CONFNAK;    /* Nak CI */
                    PPP_PUTCHAR(LCP_CI_MRRU, nakp);
                    PPP_PUTCHAR(PPP_CILEN_SHORT, nakp);
                    PPP_PUTSHORT(PPP_MINMRRU, nakp);/* Give him a hint */
                    break;
                }

                pstHisOptions->mrru = cishort;    /* And remember value */
                pstHisOptions->neg_mrru = 1;    /* Remember he sent MRRU */
                break;

            case LCP_CI_SSNHF:
                if (!pstAllowOptions->neg_ssnhf
               || (cilen != PPP_CILEN_VOID))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_261);
                    orc = CONFREJ;
                    break;
                }

                pstHisOptions->neg_ssnhf = 1;
                break;

            case LCP_CI_DISCR:
                if (!pstAllowOptions->neg_discr || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_262);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETCHAR(cichar, currentpos);/* Parse class */
                switch (cichar)
                {
                    case LCP_DISCR_NULL:
                        if (cilen != PPP_CILEN_DISCR)
                        {
                            PPP_DBG_ERR_CNT(PPP_PHERR_263);
                            orc = CONFREJ;
                            break;
                        }

                    /* following case without break */
                    /*lint -e825*/
                    case LCP_DISCR_IPADDR:
                    case LCP_DISCR_LOCASSIGN:
                    case LCP_DISCR_MACADDR:
                    case LCP_DISCR_MAGICNUM:
                    /*lint +e825*/
                        pstHisOptions->discr_len = cilen;
                        (VOID)VOS_MemCpy(pstHisOptions->discr_addr, (CHAR*)currentpos,
                                           (ULONG)(pstHisOptions->discr_len - PPP_CILEN_DISCR));
                        PPP_INCPTR( pstHisOptions->discr_len - PPP_CILEN_DISCR, currentpos);
                        break;
                    default:
                        PPP_DBG_ERR_CNT(PPP_PHERR_264);
                        orc = CONFREJ;
                        break;
                }

                pstHisOptions->discr_class = cichar;/* And remember value */
                pstHisOptions->neg_discr = 1;      /* Remember he sent MRRU */
                break;
            case LCP_CI_CALLBACK:

                /* if she negitiate callback she must neg the auth protocol */
                if (!pstAllowOptions->neg_callback || (cilen < 3))
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_265);
                    orc = CONFREJ;
                    break;
                }

                PPP_GETCHAR(pstHisOptions->callbackopr, currentpos);
                (VOID)VOS_MemCpy((char *)(pstHisOptions->callbackinfo), (char *)currentpos, (ULONG)(cilen - 3));
                currentpos += cilen - 3;
                pstHisOptions->neg_callback = 1;
                break;

            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_266);
                orc = CONFREJ;
                break;
        }

endswitch:

        /* according protocol, we first send rej, then send nak and finally send ack */
        if (orc == CONFREJ)
        {
            (VOID)VOS_MemCpy((char *)rejp, (char *)cip, (ULONG)cilen); /* Move it */
            PPP_INCPTR(cilen, rejp);    /* Update output pointer */
            rc = CONFREJ;
            continue;
        }

        if (rc == CONFREJ)
        {
            continue;
        }

        if (orc == CONFNAK)
        {
            rc = CONFNAK;
            continue;
        }
    }

    /*
     * If we wanted to send additional NAKs (for unsent CIs), the
     * code would go here.  The extra NAKs would go at *nakp.
     * At present there are no cases where we want to ask the
     * peer to negotiate an option.
     */

    switch (rc)
    {
        case CONFACK:
            *pulLen = (ULONG)(next - pPacket);
            break;
        case CONFNAK:
            *pulLen = (ULONG)(nakp - nak_buffer);
            (VOID)VOS_MemCpy((char *)pPacket, (char *)nak_buffer, *pulLen);
            break;
        case CONFREJ:
            *pulLen = (ULONG)(rejp - pPacket);
            break;
        default:
            break;
    }

    return (rc);            /* Return final code */
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��������Э��˽�еı���˽�еı�������                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                ucCode: ��������                                           *
*                ucId:   ����ID                                             *
*                pHead:  ��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�            *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK :�Ϸ�����                                           *
*                VOS_ERR:����ʶ��ı���                                     *
* CALLED BY    ��PPP_FSM_ReceivePacket                                      *
****************************************************************************/
/*lint -e529*/
USHORT PPP_LCP_extcode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG
                       ulLen, ULONG ulUserIndex)/* Added by liutao 38563 at 2004-10-08 V800R002 for PPPѹ����ֲ */
{
    PPP_LCP_OPTION_S *pstGotOptions;
    ULONG ulMagicNumber;

    pstGotOptions = &(((PPPLCPINFO_S*)(pstFsm->pProtocolInfo))->stGotOptions);
    ulMagicNumber = pstGotOptions->magicnumber;

    switch (ucCode)
    {
        case ECHOREQ:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (ULONG)PPP_EVENT_FSM_RXR);

            if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
            {
                /* ser action */
                PPP_FSM_ser(pstFsm, ucId, pHead, pPacket, ulLen, ulMagicNumber);
            }
            else
            {
                if ((pstFsm->ucState == (UCHAR)PPP_STATE_INITIAL)
               || (pstFsm->ucState == (UCHAR)PPP_STATE_STARTING))
                {
                    /* Illegal Event */
                    PPP_Debug_FsmIllegalEvent(pstFsm, PPP_EVENT_FSM_RXR);
                }

            }

            /* state not changed */
            break;

        case ECHOREP:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (ULONG)PPP_EVENT_FSM_RXR);

            PPP_LCP_ReceiveEchoReply(pstFsm, ucId, pPacket, ulLen);
            break;

        case DISCREQ:

            /* ���debug��Ϣ */
            PPP_Debug_FsmEvent(pstFsm, (ULONG)PPP_EVENT_FSM_RXR);

            break;

        case IDENTIFIC:
            PPP_GETLONG(ulMagicNumber, pPacket);

            break;

        case TIMEREMAIN:
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_267);

            /* RUC event */
            PPP_FSM_ReceiveUnknownCode(pstFsm, ucId, pHead, pPacket, ulLen);
            return VOS_ERR;
    }

    return VOS_OK;
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
****************************************************************************/
VOID PPP_LCP_up(PPPFSM_S *pstFsm)
{
    ULONG ulAccept = 0;
    ULONG ulRetVal = 0;

    PPPC_INFO_LOG("enter:PPP_LCP_up\r\n");

    /* ����LCPЭ�̽����ʼ������Э���Э�̲��� */
    ulAccept = PPP_LCP_UpResetCi((PPPINFO_S *)pstFsm->pPppInfo);

    if (ulAccept == VOS_OK)
    {
        /* Э�̽�����Խ���,���ں˷���Lcp Up�¼� */
        PPP_Core_ReceiveEventFromProtocol((PPPINFO_S *)pstFsm->pPppInfo,
                                          (ULONG)PPP_EVENT_LCPUP,
                                          NULL);

        /*add by huzhiyong for D13978 2002/02/26 */
        if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
        {
            if (pstFsm->ulEchoTimeOutTime > 0)
            {
                if (pstFsm->ulEchoTimeoutID == 0)
                {
                    /* ����Echo Request��ʱ��(ѭ����ʱ��!!!) */
                    ulRetVal   = VOS_StartRelTimer((HTIMER)&(pstFsm->ulEchoTimeoutID), MID_PPPC,
                           pstFsm->ulEchoTimeOutTime, (VOS_UINT32)pstFsm, PPPC_LCP_SEND_ECHO_REQ_TIMER,
                           VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
                }
                else
                {
                    PPP_DBG_ERR_CNT(PPP_PHERR_268);
                    VOS_DBGASSERT(0);
                }

                VOS_DBGASSERT(ulRetVal == 0);
            }
        }

        /* ����echo Req */
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_269);
        /* Э�̽�����ɽ���,����Э�� */
        PPP_SET_REL_CODE(((PPPINFO_S *)pstFsm->pPppInfo), AM_RELCODE_PPP_LCP_NEGONAK);
        PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
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
****************************************************************************/
VOID PPP_LCP_down(PPPFSM_S *pstFsm)
{
    /* �ش���ʱ����PPP_FSM_tld���Ѿ�ɾ�� */

    /* ɾ��Echo Request��ʱ���� */
    if (pstFsm->ulEchoTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    /*added by huzhiyong 2002/07/15*/
    {
        PPPINFO_S *pstPppInfo = NULL;
        pstPppInfo = (PPPINFO_S *)(pstFsm->pPppInfo);
        VOS_DBGASSERT(pstPppInfo);

        if (NULL == pstPppInfo)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_270);
            VOS_DBGASSERT(0);
            return;
        }

    }

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_LCPDOWN,
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
VOID PPP_LCP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_LCPFINISHED,
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
VOID PPP_LCP_starting(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_LCPSTARTING,
                                      NULL);
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ����ʼ��LCP���ƿ�                                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ����װ����                                                   *
****************************************************************************/
VOID PPP_LCP_Init(PPPINFO_S* pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo;
    PPPFSM_S *pstFsm;
    PPP_LCP_OPTION_S *pstWantOptions;
    PPP_LCP_OPTION_S *pstAllowOptions;

    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;
    pstFsm = &(pstLcpInfo->stFsm);

    pstPppInfo->bPppClient = 1;

    pstWantOptions  = &(pstLcpInfo->stWantOptions);
    pstAllowOptions = &(pstLcpInfo->stAllowOptions);

    /* LCP���ƿ��ʼ�� */
    pstLcpInfo->pstPppInfo = pstPppInfo;
    pstLcpInfo->ucUsedFlag = 1;
    /* ״̬����ʼ�� */
    pstFsm->usProtocol    = PPP_LCP;
    pstFsm->pstCallBacks  = &g_stLcpCallbacks;
    pstFsm->pProtocolInfo = (char*)pstLcpInfo;
    pstFsm->pPppInfo = (char*)pstLcpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);
    pstFsm->ucEchoId = 0;
    pstFsm->ulEchoTimeoutID = 0;

    /* modified by gxf for GGSN80 20030224  ulEchoTimeOutTime=0����������Echo
       Request�Ķ�ʱ��*/
    pstFsm->ulEchoTimeOutTime = 0 /*IF_GetIfByIndex(pstPppInfo->ulIfIndex)->if_ulKeepAlive*/;

    /*luofeng37050notify  Э�̲���ֵ��ʼ��,�Ƿ�Э��ĳ����������resetci�����г�ʼ�� */
    /* Э�̲���ֵ��ʼ��,�Ƿ�Э��ĳ����������resetci�����г�ʼ�� */

    /* mru */
    /* ��һ���ٵ���,�Ժ��滻�� */
    pstWantOptions->mru  = 1500;
    pstWantOptions->mrru = pstWantOptions->mru;

    pstWantOptions->chap_mdtype  = CHAP_DIGEST_MD5;
    pstAllowOptions->chap_mdtype = CHAP_DIGEST_MD5;
}

/*r002*/
VOID PPP_LCP_ReceiveEchoReply(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen)
{
    PPPINFO_S *pstPppInfo;
    PPPLCPINFO_S *pstLcpInfo;
    PPP_LCP_OPTION_S *pstGotOptions;
    ULONG ulMagic;
    ULONG ulReturn = VOS_OK;
    CHAR cDebug[200];
    CHAR *pBuf = cDebug;

    pstPppInfo = (PPPINFO_S *)pstFsm->pPppInfo;
    pstLcpInfo = (PPPLCPINFO_S *)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstLcpInfo->stGotOptions);

    pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;

    /* del the echo timer first */
    if (pstFsm->ulEchoTimeoutID != 0)
    {
        /* ɾ��Echo Request��ʱ���� */
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    /*lint -e801*/
    if (pstFsm->ulEchoTimeOutTime == 0) /*if someone have del the time first,we just return directly */
    {
        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error pstFsm->ulEchoTimeOutTime == 0");

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_OK_CNT(PPP_PHOK_925);

        goto A11PROC;
    }

    pstFsm->ulEchoTimeOutTime = 0;

    if ((pstFsm->ucEchoId & 0xFF) != ucId)
    {
        /* wrong ID */
        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error (pstFsm->ucEchoId & 0xFF):%lu != ucId:%lu",
                            (ULONG)(pstFsm->ucEchoId & 0xFF), (ULONG)ucId );

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_OK_CNT(PPP_PHOK_926);

        goto A11PROC;
    }

    /* Check the magic number - don't count replies from ourselves. */
    if (ulLen < 4)
    {
        /* no magic number */
        ulReturn = VOS_ERR;

        pBuf += VOS_sprintf(pBuf, "PPP_LCP_ReceiveEchoReply Error ulLen is %lu", ulLen);

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);
        PPP_DBG_ERR_CNT(PPP_PHERR_271);

        goto A11PROC;
    }
    /*lint +e801*/

    PPP_GETLONG(ulMagic, pPacket);
    if (pstGotOptions->neg_magicnumber
        && (ulMagic == pstGotOptions->magicnumber))
    {
        /* ���Լ���magic numberһ��,���ܷ������Ի� */
        if (++pstGotOptions->numloops >= PPP_MAXLOOPSBACK)
        {
            pstPppInfo->bLoopBacked = 1;

            /* �����Ի�,����Э�� */
            PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_LCP_LOOPBACK);
            PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);
        }
    }
    else
    {
        pstGotOptions->numloops = 0;
        pstPppInfo->bLoopBacked = 0;
    }

    /* notify a11 to start dormant timer */
A11PROC:

    /*  ��Ҫ���ϱ���꣬GGSN������ */
 #ifdef    __PRODUCT_TYPE_PDSN80
    if (VOS_ERR == ulReturn)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_272);
        (VOID)USM_NotifyReleaseUserMsg(pstPppInfo->ulRPIndex,  AM_RELCODE_PPP_ECHORRP_MAGIC_ERR);
    }
    pstFsm->ucEchoState = 0;
 #endif

    return;
}
VOID PPP_LCP_EchoTimeOut(VOID *pFsm)
{
    PPPFSM_S *pstFsm = (PPPFSM_S*)pFsm;

    pstFsm->ulEchoTimeoutID = 0;/* NOLOOP�Ķ�ʱ������Ҫɾ���ˣ�ֱ����λ */
    PPP_DBG_OK_CNT(PPP_PHOK_927);

    /* ֻ��OPENED״̬�ŷ���Echo Request���� */
    if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
    {
        CHAR cDebug[200];
        CHAR *pBuf = cDebug;

        /* �ش���������1 */
        pstFsm->sRetransmits--;

        pBuf += VOS_sprintf(pBuf, "Echo Timer Expired ,Retransmit = %d ", pstFsm->sRetransmits);

        PPP_Debug_CoreEvent((PPPINFO_S*)pstFsm->pPppInfo, PPP_LOG_WARNING, cDebug);

        /* ����Ƿ��ѳ�������ش����� */
        if (pstFsm->sRetransmits <= 0)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_273);
            pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;
            pstFsm->ucEchoState = 0;

            /* �ش��������࣬����Э�� */
            PPP_SET_REL_CODE(((PPPINFO_S *)(pstFsm->pPppInfo)), AM_RELCODE_PPP_LCP_ECHOTIMEOUT);
            PPP_LCP_NegotiationDown(pstFsm->pProtocolInfo);

            return;
        }
        PPP_DBG_OK_CNT(PPP_PHOK_928);

        /* ���ͱ��� */
        PPP_LCP_SendEchoRequest(pstFsm);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ������Echo Request����                                       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_LCP_EchoTimeOut                                        *
****************************************************************************/
/*lint -e529*/
VOID PPP_LCP_SendEchoRequest(PPPFSM_S *pstFsm)
{
    UCHAR *pHead, *pPacket;
    ULONG ulLen = 0;
    ULONG ulOffset;
    ULONG ulMagic;
    PPP_LCP_OPTION_S *pstGotOptions;

    PPP_DBG_OK_CNT(PPP_PHOK_929);

    /* �õ�magic number */
    pstGotOptions = &(((PPPLCPINFO_S*)pstFsm->pProtocolInfo)->stGotOptions);
    ulMagic = pstGotOptions->neg_magicnumber ? pstGotOptions->magicnumber : 0L;

    /* Ԥ������PPP����ͷ�Ŀռ� */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* �����ڴ� */
    pHead = g_ucPppSendPacketHead;
    if (pHead == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_274);
        PPP_Debug_Error(pstFsm, PPP_LOG_ERROR, "Send Echo Request: Malloc Err!!");
        return;
    }

    pPacket = pHead + ulOffset;

    /* �������(bytes) */

    /*
                                      1   2   3   4
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |            ...                |   |   |   |   |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|
    pHead                           pPacket
     */

    PPP_PUTLONG(ulMagic, pPacket);
    pPacket -= 4;
    ulLen = 4;

    /* ������� */

    /*
                                      1   2   3   4
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |            ...                |  Magic Number |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |--------- ulOffset ------------|---- ulLen ----|
    pHead                           pPacket
     */
    pstFsm->ucEchoId++;
    PPP_FSM_SendPacket(pstFsm, ECHOREQ, pstFsm->ucEchoId, pHead, pPacket, ulLen);

    if (pstFsm->ulEchoTimeoutID)
    {
        /* ɾ��Echo Request��ʱ���� */
        (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
        pstFsm->ulEchoTimeoutID = 0;
    }

    if (pstFsm->ulEchoTimeoutID == 0)
    {
        /* ��������Echo Request��ʱ�� */
        (VOS_VOID)VOS_StartRelTimer((HTIMER)&(pstFsm->ulEchoTimeoutID),
                                    MID_PPPC,
                                    pstFsm->ulEchoTimeOutTime,
                                    (VOS_UINT32)pstFsm,
                                    PPPC_LCP_SEND_ECHO_REQ_TIMER,
                                    VOS_TIMER_NOLOOP,
                                    VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_275);
        VOS_DBGASSERT(0);
    }

    return;
}

/*r002 end*/

ULONG PPP_LCP_UpResetCi(PPPINFO_S *pstPppInfo)
{
    PPPLCPINFO_S *pstLcpInfo;
    PPP_LCP_OPTION_S *pstGotOptions;
    PPP_LCP_OPTION_S *pstHisOptions;

    pstLcpInfo = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
    pstGotOptions = &(pstLcpInfo->stGotOptions);
    pstHisOptions = &(pstLcpInfo->stHisOptions);

    /* ���Э�̽�� */
    if (!pstGotOptions->neg_magicnumber)
    {
        pstGotOptions->magicnumber = 0;
    }

    if (!pstHisOptions->neg_magicnumber)
    {
        pstHisOptions->magicnumber = 0;
    }

    /*ע��:pstGotOptions->neg_chap��pstGotOptions->neg_upap����
       ͬʱΪ1,��ʹ����chap���ȼ���,�ڴ�Ҫ�ȱ�ֻ֤��һ����־Ϊ1 */
    if (VOS_FALSE == SOFTPARA_BIT1395)
    {
        /* CHAP���� */
        if (pstGotOptions->neg_chap == 1)
        {
            pstGotOptions->neg_upap = 0;
        }

        if (pstHisOptions->neg_chap == 1)
        {
            pstHisOptions->neg_upap = 0;
        }
        pstPppInfo->bPppClient = 1;
    }
    else
    {
        /* PAP���� */
        if (pstGotOptions->neg_upap == 1)
        {
            pstGotOptions->neg_chap = 0;
        }

        if (pstHisOptions->neg_upap == 1)
        {
            pstHisOptions->neg_chap = 0;
        }
    }
    /*-------------------------------------------------------*/
#if 0
    /* eHRPD�û��������EAP��֤ */
    if ((pstPppInfo->bEhrpdUser) && (0 == pstGotOptions->neg_eap))
    {
        return VOS_ERR;
    }
#endif
    /*����Server����֤��δͨ��*/
    if ((pstGotOptions->neg_upap == 1) || (pstGotOptions->neg_chap == 1) || (pstGotOptions->neg_eap == 1))
    {
        pstPppInfo->bAuthServer = VRP_YES;
    }
    else
    {
        pstPppInfo->bAuthServer = VRP_NO;
    }

    /*����Client����֤��δͨ��*/
    if ((pstHisOptions->neg_upap == 1) || (pstHisOptions->neg_chap == 1))
    {
        pstPppInfo->bAuthClient = VRP_YES;
    }
    else
    {
        pstPppInfo->bAuthClient = VRP_NO;
    }

    /* ���õײ�ACCMAP */
    pstPppInfo->ulRemoteAccm = pstHisOptions->asyncmap;
    pstPppInfo->ulLocalAccm = pstGotOptions->asyncmap;

    /* ����MTU */
    if (pstHisOptions->neg_mru)
    {
        pstPppInfo->usMtu = pstHisOptions->mru > pstGotOptions->mru ? pstGotOptions->mru : pstHisOptions->mru;
    }
    else
    {
        pstPppInfo->usMtu =  pstGotOptions->mru;
    }

    if (pstPppInfo->usMtu > PPP_DEFMRRU)
    {
        pstPppInfo->usMtu = PPP_DEFMRRU;
    }

    return VOS_OK;
}

 #ifdef __PRODUCT_TYPE_PDSN80

/****************************************************************************
* CREATE DATE  ��2004/06/17                                                 *
* CREATED BY   ��QQ                                                     *
* FUNCTION     ��TDORMANT��ʱ����ʱ���øú�������echo��Ϣ       *
* MODIFY DATE  ��                               *
* INPUT        ��ucFlag ucFlagΪ1����ʶ֪ͨPPPC����Echo��Ϣ��ucFlagΪ0����ʶ��ֹ��Echo��صĴ��� *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_ERR:Э�̽�����ɽ���,������Ӧ����Э��                  *
*                VOS_OK :Э�̽�����Խ���,������Ӧ���ϲ�Э�鱨UP            *
* CALLED BY    ��A11_ActiveStateMachProc                                                *
****************************************************************************/
ULONG A11_PPPC_EchoSet(A11_ECHO_E ucFlag, ULONG ulRPIndex)
{
    PPPINFO_S *pstPppInfo;
    PPPFSM_S *pstFsm;
    PPPLCPINFO_S *pstLcpInfo;

    if (ulRPIndex > PPP_MAX_USER_NUM)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_276);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : rpindex %d isn't exist!", ulRPIndex);
        return VOS_ERR;
    }

    if (PPP_CB_STATE_FREE == g_astPppPool[ulRPIndex].usState)    /* �û���ɾ�� */
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_277);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : User %d isn't exist!", ulRPIndex);
        return VOS_ERR;
    }

    GETPPPINFOPTRBYRP(pstPppInfo, ulRPIndex);

    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : pstPppInfo is NULL!");
        return VOS_OK;
    }


    pstLcpInfo = (PPPLCPINFO_S*)pstPppInfo->pstLcpInfo;

    if (pstLcpInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_278);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP A11_PPPC_EchoSet : User %d isn't exist!", ulRPIndex);
        return VOS_OK;
    }

    pstFsm = &(pstLcpInfo->stFsm);

    if (A11_SEND_ECHO == ucFlag)
    {
        pstFsm->ulEchoTimeOutTime = pstPppInfo->pstUsedConfigInfo->ulNegTimeOut;
        pstFsm->sRetransmits = (SHORT)g_ulPppEchoRetransmit;
        pstFsm->ucEchoState = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_930);

        if (pstFsm->ucState == (UCHAR)PPP_STATE_OPENED)
        {
            /* ����echo Req */
            PPP_LCP_SendEchoRequest(pstFsm);
        }
    }
    else /* if during waiting the reply ,we get the traffic then delete all resource */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_931);
        if (pstFsm->ulEchoTimeoutID != 0)
        {
            /* ɾ��Echo Request��ʱ���� */
            (VOID)VOS_StopRelTimer(&(pstFsm->ulEchoTimeoutID));
            pstFsm->ulEchoTimeoutID   = 0;
            pstFsm->ulEchoTimeOutTime = 0;
            pstFsm->sRetransmits = PPP_DEFMAXCONFREQS;
        }
    }

    return VOS_OK;
}

 #endif


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
