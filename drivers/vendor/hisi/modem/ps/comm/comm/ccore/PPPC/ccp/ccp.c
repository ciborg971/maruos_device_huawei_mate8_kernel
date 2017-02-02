/************************************************************************
*                                                                      *
*                             ccp.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        			                                    *
*  Author:             sunjianfeng  			                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��CCPЭ�麯����ʵ��                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CCP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*
 * Callbacks for fsm code.
 */

PPPFSMCALLBACK_S g_stCcpCallbacks =
{
    PPP_CCP_resetci,
    PPP_CCP_cilen,
    PPP_CCP_addci,
    PPP_CCP_ackci,
    PPP_CCP_nakci,
    PPP_CCP_rejci,
    PPP_CCP_reqci,
    PPP_CCP_extcode,
    PPP_CCP_up,
    PPP_CCP_down,
    PPP_CCP_finished,
    NULL,
    "CCP"
};
UCHAR ucCompType;/* Added by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ��2000/06/26                                                 *
* CREATED BY   ��SHI YONG                                                   *
* FUNCTION     ��CCP�����ⲿ�¼�.�¼�������Up��Down��Open��Close            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstCcpInfo:LCP���ƿ�ָ��                                   *
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

VOID PPP_CCP_ReceiveEventFromCore (VOID *pstCcpInfo, ULONG ulCmd, char *pPara)
{
    PPPFSM_S *pstFsm;

    if (NULL == pstCcpInfo)
    {
         VOS_DBGASSERT(0);
         return;
    }
    if (PPP_EVENT_FSM_OPEN == ulCmd)
    {
        PPP_PerfInc(&g_stPppPerfStatistic.ulCcpTotal, PERF_TYPE_PPPC_CCP_NEGO_ATTEMP, 0);
    }

    pstFsm = &(((PPP_CCP_INFO_S*)pstCcpInfo)->stFsm);

    PPP_FSM_ReceiveEvent(pstFsm, ulCmd, pPara);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ��ȷ��CCP��ҪЭ����Щ����,��CCP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo    :PPP���ƿ�                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_NetworkPhase                                      *
****************************************************************************/

VOID PPP_CCP_init (PPPINFO_S* pstPppInfo)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPPFSM_S* pstFsm;

    PPP_CCP_options_S *pstWantOptions;
    PPP_CCP_options_S *pstGotOptions;
    PPP_CCP_options_S *pstHisOptions;

    pstCcpInfo = (PPP_CCP_INFO_S *)pstPppInfo->pstCcpInfo;
    pstCcpInfo->ucUsed = 1;
    pstFsm = &(pstCcpInfo->stFsm);

    pstWantOptions = &(pstCcpInfo->stWantOptions);
    pstGotOptions = &(pstCcpInfo->stGotOptions);
    pstHisOptions = &(pstCcpInfo->stHisOptions);

    /* CCP���ƿ��ʼ�� */
    pstCcpInfo->pstPppInfo = pstPppInfo;
    pstCcpInfo->ulCcpTimeoutID = 0; /* Added by heyajun kf1199 at 2004-08-05 V800R001C01B010 for BYHD03171 */
    pstCcpInfo->ulTimeOutTime = PPP_CCP_TIMEOUTTIME;

    /* Added start by liutao 38563 at 2004-09-29 V800R002 for PPPѹ����ֲ */
    pstCcpInfo->ucPppCompType = 0;
    /* Added end by liutao 38563 at 2004-09-29 V800R002 for PPPѹ����ֲ */

    /* ״̬����ʼ�� */
    pstFsm->usProtocol    = (USHORT)PPP_CCP;
    pstFsm->pstCallBacks  = &g_stCcpCallbacks;
    pstFsm->pProtocolInfo = (CHAR*)pstCcpInfo;
    pstFsm->pPppInfo = (CHAR*)pstCcpInfo->pstPppInfo;
    PPP_FSM_Init(pstFsm);

    /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
    /* Э�̲���ֵ��ʼ��,�Ƿ�Э��ĳ����������resetci�����г�ʼ�� */
    pstWantOptions->bMppc_compress = VRP_YES;
    pstWantOptions->bStac_compress = VRP_YES;
    pstWantOptions->bLZS0_comp = VRP_YES;/* Added by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */
    pstWantOptions->ulMppc_supportedbits = PPP_MPPC_SUPPORTEDBITS;
    pstWantOptions->usStac_historys  = STAC_HISTORY_COUNT;
    pstWantOptions->ucStac_checkmode = PPP_STAC_SEQUENCE_NUMBER; /* sequence number */
    /*End WGGSN_B03_L2TP_PPPC_COMP*/

    *pstGotOptions = *pstWantOptions;
    PPP_MemSet(pstHisOptions, 0, sizeof(PPP_CCP_options_S));

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��Deng Yi Ou                                                 *
* FUNCTION     ��CCP���ձ���                                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstCcpInfo:CCP���ƿ�                                       *
*                pHead:��ű����ڴ��ͷָ��,Ӧ�����ͷ�����ڴ�              *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_CCP_ReceivePacket (VOID *pstCcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG
                            ulLen, ULONG ulRPIndex)/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
{
    PPPFSM_S *pstFsm;

    VOS_DBGASSERT(pHead);
    VOS_DBGASSERT(pPacket);
    if (NULL == pstCcpInfo)
    {
         VOS_DBGASSERT(0);
         return;
    }
    pstFsm = &(((PPP_CCP_INFO_S*)pstCcpInfo)->stFsm);

    PPP_FSM_ReceivePacket(pstFsm, pHead, pPacket, ulLen, ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

    return;
}

/*
 * PPP_CCP_resetci - initialize at start of negotiation.
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ��ȷ��IPCP��ҪЭ����Щ����,��IPCP��ʼ��ʱ����                  *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm    :״̬��                                          *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��״̬����ִ��tls�����ĺ�PPP_FSM_tls                         *
****************************************************************************/
VOID PPP_CCP_resetci(PPPFSM_S *pstFsm)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstWantOptions;
    PPP_CCP_options_S *pstGotOptions;
    PPP_CCP_options_S *pstHisOptions;
    PPP_CCP_options_S *pstAllowOptions;
    PPPINFO_S *pPppInfo;
    PPPCONFIGINFO_S  *pstConfig;
    PPPRENOGOINFO *pstPppRenegoInfo; /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */

    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pPppInfo  = pstCcpInfo->pstPppInfo;
    pstConfig = pPppInfo->pstUsedConfigInfo;

    pstWantOptions = &(pstCcpInfo->stWantOptions);
    pstGotOptions   = &(pstCcpInfo->stGotOptions);
    pstHisOptions   = &(pstCcpInfo->stHisOptions);
    pstAllowOptions = &(pstCcpInfo->stAllowOptions);

    PPP_MemSet((char *)pstHisOptions, 0, sizeof(PPP_CCP_options_S));

    /* Added by heyajun kf1199 at 2004-08-04 V800R001C01B010 for BYHD03180 */
    pstPppRenegoInfo = pPppInfo->pstPppRenegoInfo;
    if (pstPppRenegoInfo && pstPppRenegoInfo->ucCcpFlag)
    {
        VOS_MemCpy((VOID*)pstGotOptions, (VOID*)&pstPppRenegoInfo->stCcpOptions, sizeof(PPP_CCP_options_S));
        *pstWantOptions  = *pstGotOptions;
        *pstAllowOptions = *pstGotOptions;
        return;
    }

    /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
    if (pstConfig->bStacCompress)
    {
        pstWantOptions->bStac_compress = VRP_YES;
        pstWantOptions->bLZS0_comp = VRP_YES; /* Added by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */
        pstWantOptions->usStac_historys  = STAC_HISTORY_COUNT;
        pstWantOptions->ucStac_checkmode = PPP_STAC_SEQUENCE_NUMBER;

    }
    /* Added start by liutao 38563 at 2004-10-30 V800R002 for PPPC��ֲ */
    else
    {
        pstWantOptions->bStac_compress = VRP_NO;
    }

    /* Added end by liutao 38563 at 2004-10-30 V800R002 for PPPC��ֲ */

    if (pstConfig->bMppcCompress)
    {
        pstWantOptions->bMppc_compress = VRP_YES;
        pstWantOptions->ulMppc_supportedbits = PPP_MPPC_SUPPORTEDBITS;

    }
    /* Added start by liutao 38563 at 2004-10-30 V800R002 for PPPC��ֲ */
    else
    {
        pstWantOptions->bMppc_compress = VRP_NO;
    }

    /* Added end by liutao 38563 at 2004-10-30 V800R002 for PPPC��ֲ */

    *pstGotOptions   = *pstWantOptions;
    *pstAllowOptions = *pstWantOptions;
    pstFsm->ulTimeOutTime = pstConfig->ulNegTimeOut;
}

/*
 * PPP_CCP_cilen - Return total length of our configuration info.
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ������Ҫ���͵�Config Request�������ݲ��ֳ���                 *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
* OUTPUT       ��                                                           *
* RETURN       ��Config Request���ĳ���                                     *
* CALLED BY    ��PPP_FSM_SendConfigReq                                      *
****************************************************************************/
USHORT PPP_CCP_cilen(PPPFSM_S *pstFsm)
{
 #ifdef __PRODUCT_TYPE_PDSN80
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstGotOptions;
    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstCcpInfo->stGotOptions);

    /* Modified start by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */
    /*Begin WGGSN_B03_L2TP_PPPC_COMP*/
    /* Modified start by menfujun mkf4618 at 2005-04-15 V800R002C01B012  for BYHDLicense */
    if ((pstGotOptions->bStac_compress == 1)
       && ((g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER)
           || (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER)))/* Modified by liutao 38563 at 2005-03-08 PDSN9660 V800R002C01 for BYHDLicense */
    {
        PPP_DBG_OK_CNT(PPP_PHOK_800);
        ucCompType = CI_STAC_COMPRESS;
        return CILEN_STAC_COMPRESS;
    }
    else
    {
        pstGotOptions->bStac_compress = 0;
    }
    /*lint -e746*/
    if ((pstGotOptions->bMppc_compress == 1)
       && (VOS_OK == PPP_CheckMppcLimit())) /* Modified by liutao 38563 at 2004-12-24 PDSN9660 V800R002C01 for BYHD04055 */
    /*lint +e746*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_801);
        ucCompType = CI_MPPC_COMPRESS;
        return CILEN_MPPC_COMPRESS;
    }
    /* Modified end by menfujun mkf4618 at 2005-04-15 V800R002C01B012  for BYHDLicense */
    /* Modified end by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_802);
        pstGotOptions->bMppc_compress = 0;
        ucCompType = 0;/* Added by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */
        return 0;
    }

    /*return (pstGotOptions->bStac_compress == VRP_YES ? CILEN_STAC_COMPRESS: 0);*/
#else
    return 0;
 #endif

    /*End WGGSN_B03_L2TP_PPPC_COMP*/
}

/* Added start by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */

/*****************************************************************************
 �� �� ��  : PPP_CCP_addci
 ��������  : �齨config request����
 �������  : PPPFSM_S *pstFsm
             UCHAR *puc
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2004��9��27��
    ��    ��   : liutao 38563
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CCP_addci(PPPFSM_S *pstFsm, UCHAR *puc)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstGotOptions;

    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstCcpInfo->stGotOptions);

    if (CI_STAC_COMPRESS == ucCompType)
    {
        if (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_803);
            PPP_PUTCHAR(CI_STAC_COMPRESS, puc);
            PPP_PUTCHAR(CILEN_STAC_COMPRESS, puc);
            PPP_PUTSHORT(pstGotOptions->usStac_historys, puc);
            PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, puc);
            return;
        }
        else if (g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_804);
            PPP_PUTCHAR(CI_STAC_COMPRESS, puc);
            PPP_PUTCHAR(CILEN_STAC_COMPRESS, puc);
            PPP_PUTSHORT(0, puc);
            PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, puc);
            return;
        }
    }

    /*lint -e746*/
    if ((CI_MPPC_COMPRESS == ucCompType)
       && (VOS_OK == PPP_CheckMppcLimit()))
    /*lint +e746*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_805);
        PPP_PUTCHAR(CI_MPPC_COMPRESS, puc);
        PPP_PUTCHAR(CILEN_MPPC_COMPRESS, puc);
        PPP_PUTLONG(pstGotOptions->ulMppc_supportedbits, puc);
        return;
    }

    return;
}

/* Added end by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */
/* Added start by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */

/*
 * PPP_CCP_ackci - process a received configure-ack, and return
 * VOS_OK if the packet was OK.
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     �������յ���Config ACK����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���ACK����;VOS_ERR:�Ƿ���ACK����                 *
* CALLED BY    ��PPP_FSM_ReceiveConfAck                                     *
****************************************************************************/
USHORT PPP_CCP_ackci(PPPFSM_S *pstFsm, UCHAR *p, ULONG len)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstGotOptions;

    UCHAR ucCIlen, ucCItype, ucCICheckmode;
    USHORT usCIHistory;
    ULONG ulCISupportedbits;/*WGGSN_B03_L2TP_PPPC_COMP*/
    UCHAR * cp = NULL;

    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstCcpInfo->stGotOptions);

    /* �������ѹ������֧��ʱACK���ȿ���Ϊ0��������ѹ����ʽ���ն�NAK��Reject */
    if (0 == len)
    {
        if ((VRP_YES != pstGotOptions->bMppc_compress)
            && (VRP_YES != pstGotOptions->bStac_compress))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_806);
            return VOS_OK;
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_1);
            return VOS_ERR;
        }
    }

    cp = p;
    PPP_GETCHAR(ucCItype, cp);
    PPP_GETCHAR(ucCIlen, cp);
    switch (ucCItype)
    {
    case CI_MPPC_COMPRESS:
        if (CILEN_MPPC_COMPRESS != ucCIlen)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_2);
            return VOS_ERR;
        }

        if (VRP_YES != pstGotOptions->bMppc_compress)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_3);
            return VOS_ERR;
        }

        PPP_GETLONG(ulCISupportedbits, cp);
        if (pstGotOptions->ulMppc_supportedbits != ulCISupportedbits)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_4);
            return VOS_ERR;
        }

        pstGotOptions->bStac_compress = 0;
        len -= CILEN_MPPC_COMPRESS;
        break;

    case CI_STAC_COMPRESS:
        if (CILEN_STAC_COMPRESS != ucCIlen)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_5);
            return VOS_ERR;
        }

        if (VRP_YES != pstGotOptions->bStac_compress)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_6);
            return VOS_ERR;
        }

        PPP_GETSHORT(usCIHistory, cp);
        if (usCIHistory > 1)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_7);
            return VOS_ERR;
        }

        PPP_GETCHAR (ucCICheckmode, cp);
        if (pstGotOptions->ucStac_checkmode != ucCICheckmode)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_8);
            return VOS_ERR;
        }

        pstGotOptions->bMppc_compress = 0;

        /* Added start by liutao 38563 at 2005-05-28 PDSN9660V800R002C01B052 for BYHD06282 */
        if (1 == usCIHistory)
        {
            pstGotOptions->bLZS1_comp = 1;
            pstGotOptions->bLZS0_comp = 0;
        }
        else
        {
            pstGotOptions->bLZS1_comp = 0;
            pstGotOptions->bLZS0_comp = 1;
        }

        pstGotOptions->usStac_historys = usCIHistory;
        /* Added end by liutao 38563 at 2005-05-28 PDSN9660V800R002C01B052 for BYHD06282 */
        len -= CILEN_STAC_COMPRESS;
        break;
    default:
        PPP_DBG_ERR_CNT(PPP_PHERR_9);
        return VOS_ERR;
    }

    if (len != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_10);
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added end by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */

/*
 * PPP_CCP_nakci - process received configure-nak.
 * Returns 1 if the nak was OK.
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     �������յ���Config Nak����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���NAK����;VOS_ERR:�Ƿ���NAK����                 *
* CALLED BY    ��PPP_FSM_ReceiveConfNakRej                                  *
****************************************************************************/
USHORT PPP_CCP_nakci(PPPFSM_S *pstFsm, UCHAR *p, ULONG len)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstGotOptions;

    USHORT usCIHistory;
    ULONG ulCISupportedbits; /*WGGSN_B03_L2TP_PPPC_COMP*/

    PPP_CCP_options_S pstTryOption;       /* options to request next time */

    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstCcpInfo->stGotOptions);

    /* Deleted start by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */

    /* Deleted end by liutao 38563 at 2004-09-28 V800R002 for PPPѹ����ֲ */
    pstTryOption = *pstGotOptions;

    /*Begin WGGSN_B03_L2TP_PPPC_COMP*/

    /* nak����һ�����ܽ��ܵ�ѡ��Ĳ�����δ��� ?
    Ϊʲô��CCP�У��յ���ȷ��NAK����ȴ����1���յ�ʧ�ܵ�NAK����ȴ����0 ?
    WGGSN_B03_L2TP_PPPC_TEMP*/

    if ((pstGotOptions->bMppc_compress == VRP_YES) && (len >= CILEN_MPPC_COMPRESS)
        && (p[0] == CI_MPPC_COMPRESS) && (p[1] == CILEN_MPPC_COMPRESS))
    {
        len -= CILEN_MPPC_COMPRESS;
        PPP_INCPTR(2, p);
        PPP_GETLONG(ulCISupportedbits, p);
        if (ulCISupportedbits != 1)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_11);
            return VOS_ERR;
        }

        pstTryOption.ulMppc_supportedbits = PPP_MPPC_SUPPORTEDBITS;
    }

    if ((pstGotOptions->bStac_compress == VRP_YES) && (len >= CILEN_STAC_COMPRESS)
        && (p[0] == CI_STAC_COMPRESS) && (p[1] == CILEN_STAC_COMPRESS))
    {
        len -= CILEN_STAC_COMPRESS;
        PPP_INCPTR(2, p);
        PPP_GETSHORT(usCIHistory, p);
        if (usCIHistory > 1)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_12);
            return VOS_ERR;
        }

        /*shiy:we only realize one dictionary */
        /*try.usStac_historys = STAC_HISTORY_COUNT + 1;*/
        pstTryOption.usStac_historys = usCIHistory;

        /* Added start by liutao 38563 at 2005-05-28 PDSN9660V800R002C01B052 for BYHD06282 */
        if (1 == usCIHistory)
        {
            pstTryOption.bLZS1_comp = 1;
            pstTryOption.bLZS0_comp = 0;
        }
        else
        {
            pstTryOption.bLZS1_comp = 0;
            pstTryOption.bLZS0_comp = 1;
        }

        /* Added end by liutao 38563 at 2005-05-28 PDSN9660V800R002C01B052 for BYHD06282 */
    }

    if (len != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_13);
        return VOS_ERR;
    }

    if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
    {
        *pstGotOptions = pstTryOption;
    }

    return VOS_OK;
}

/*
 * PPP_CCP_rejci - reject some of our suggested compression methods.
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     �������յ���Config Reject����                                *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm: ״̬��                                             *
*                pPacket:����ͷλ��                                         *
*                ulLen:  ���ĳ���                                           *
* OUTPUT       ��                                                           *
* RETURN       ��VOS_OK,�Ϸ���reject����;VOS_ERR:�Ƿ���reject����           *
* CALLED BY    ��PPP_FSM_ReceiveConfNakRej                                  *
****************************************************************************/
USHORT PPP_CCP_rejci(PPPFSM_S *pstFsm, UCHAR *p, ULONG len)
{
    PPP_CCP_INFO_S * pstCcpInfo;
    PPP_CCP_options_S *pstGotOptions;

    PPP_CCP_options_S pstTryOption;       /* options to request next time */
    UCHAR ucCICheckmode;
    USHORT usCIHistory;
    ULONG ulCISupportedbits;

    pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    pstGotOptions = &(pstCcpInfo->stGotOptions);

    pstTryOption = *pstGotOptions;

    /*WGGSN_B03_L2TP_PPPC_TEMP���Ƿ���ֵ*/
    if ((pstGotOptions->bMppc_compress == 1) && (len == CILEN_MPPC_COMPRESS)
        && (p[0] == CI_MPPC_COMPRESS) && (p[1] == CILEN_MPPC_COMPRESS))
    {
        len = len - CILEN_MPPC_COMPRESS;
        PPP_INCPTR(2, p);
        PPP_GETLONG(ulCISupportedbits, p);
        if (ulCISupportedbits != PPP_MPPC_SUPPORTEDBITS)
        {
            PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "ccp_rejci: received bad Reject!");
            PPP_DBG_ERR_CNT(PPP_PHERR_14);
            return VOS_ERR;
        }

        pstTryOption.bMppc_compress = 0;

        if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
        {
            *pstGotOptions = pstTryOption;
        }

        return 0;
    }

    if ((pstGotOptions->bStac_compress == 1) && (len == CILEN_STAC_COMPRESS)
        && (p[0] == CI_STAC_COMPRESS) && (p[1] == CILEN_STAC_COMPRESS))
    {
        len = len - CILEN_STAC_COMPRESS;
        PPP_INCPTR(2, p);
        PPP_GETSHORT(usCIHistory, p);
        if ((usCIHistory != STAC_HISTORY_COUNT) && (usCIHistory != STAC_HISTORY_COUNT0))/*GGSNB03*/
        {
            PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "ccp_rejci: received bad Reject!");
            PPP_DBG_ERR_CNT(PPP_PHERR_15);
            return VOS_ERR;
        }

        PPP_GETCHAR(ucCICheckmode, p);
        if (ucCICheckmode != PPP_STAC_SEQUENCE_NUMBER)
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_16);
            PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "ccp_rejci: received bad Reject!");
            return VOS_ERR;
        }

        pstTryOption.bStac_compress = 0;

        if (pstFsm->ucState != (UCHAR)PPP_STATE_OPENED)
        {
            *pstGotOptions = pstTryOption;
        }

        return VOS_OK;
    }

    if (len != 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_17);
        PPP_Debug_Error(pstFsm, PPP_LOG_WARNING, "ccp_rejci: received bad Reject!");
        return VOS_ERR;
    }

    return VOS_ERR;
}

/* Added start by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */

/*****************************************************************************
 �� �� ��  : PPP_CCP_reqci
 ��������  : �����Է�������Config Request
 �������  : PPPFSM_S *pstFsm
             UCHAR *inp
             ULONG *len
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2004��9��27��
    ��    ��   : liutao 38563
    �޸�����   : �����ɺ���

*****************************************************************************/
UCHAR PPP_CCP_reqci(PPPFSM_S *pstFsm, UCHAR *inp, ULONG *len)
{
 #ifdef __PRODUCT_TYPE_PDSN80
    PPP_CCP_INFO_S *pstCcpInfo;

    PPP_CCP_options_S *pstHisOptions;
    PPP_CCP_options_S *pstGotOptions;

    UCHAR *pucCINext = NULL;                      /* Pointer to current and next CIs */
    UCHAR ucCICheckmode = 0;
    USHORT ucCIlen, ucCItype;
    USHORT usCIStac_history = 0;  /* Parsed len, type */
    ULONG ulCISupportedbits = 0; /*WGGSN_B03_L2TP_PPPC_COMP*/
    UCHAR *p;           /* Pointer to next char to parse */
    LONG lLeftLengh = *((LONG*)len);        /* Length left */
    UCHAR ucReqCiError = 0;   /* ����config request�����ԭ�� */
    UCHAR ucBadCi[100];
    ULONG ulBadCiLen = 0;
    UCHAR * pucBadCi = &ucBadCi[0];
    UCHAR * cp = NULL;
    UCHAR ucCiCount = 0;

    enum ReqCiErr
    {
        CI_LEN_ERROR = 1,  /* Э��ѡ��ĳ��ȳ��� */
        UNKNOWN_CI,        /* δ֪��Э��ѡ�� */
    };

    pstCcpInfo = (PPP_CCP_INFO_S *)pstFsm->pProtocolInfo;

    pstHisOptions = &(pstCcpInfo->stHisOptions);
    pstGotOptions = &(pstCcpInfo->stGotOptions);
    PPP_MemSet(pstHisOptions, 0, sizeof(PPP_CCP_options_S));
    pucCINext = inp;
    if (lLeftLengh == 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_807);
        return CONFACK;/*WGGSN_B03_L2TP_PPPC_TEMP����ط�Ҫ��Ҫ�Ķ�??*/
    }

    /* ��ʼ����Э��ѡ�� */
    while (lLeftLengh)
    {
        p = pucCINext;          /* Remember begining of CI */
        if ((lLeftLengh < 2)              /* Not enough data for CI header or */
           || (p[1] < 2)    /*  CI length too small or */
           || (p[1] > lLeftLengh))/*  CI length too big? */
        {
            ucReqCiError = CI_LEN_ERROR;
            PPP_DBG_OK_CNT(PPP_PHOK_808);
            break;
        }

        PPP_GETCHAR(ucCItype, p);       /* Parse CI type */
        PPP_GETCHAR(ucCIlen, p);        /* Parse CI length */
        if (ucCIlen == 0)
        {
            ucReqCiError = CI_LEN_ERROR;
            PPP_DBG_OK_CNT(PPP_PHOK_809);
            break;
        }

        lLeftLengh -= ucCIlen;          /* Adjust remaining length */
        pucCINext += ucCIlen;           /* Step to next CI */

        switch (ucCItype)
        {
        case CI_MPPC_COMPRESS:
            if (ucCIlen != CILEN_MPPC_COMPRESS)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_810);
                return CONFREJ;
            }

            pstHisOptions->bMppc_compress = 1;
            PPP_GETLONG(ulCISupportedbits, p);
            ucCiCount++;
            break;

        case CI_STAC_COMPRESS:
            if (ucCIlen != CILEN_STAC_COMPRESS)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_811);
                return CONFREJ;
            }

            pstHisOptions->bStac_compress = 1;

            PPP_GETSHORT(usCIStac_history, p);
            PPP_GETCHAR(ucCICheckmode, p);
            ucCiCount++;

            break;

        default:
            cp = pucCINext - ucCIlen;
            VOS_MemCpy(pucBadCi, cp, (ULONG)ucCIlen);
            pucBadCi    += (ULONG)ucCIlen;
            ulBadCiLen  += (ULONG)ucCIlen;
            ucReqCiError = UNKNOWN_CI;
            break;
        }
    }

    if (CI_LEN_ERROR == ucReqCiError)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_18);
        return CONFREJ;
    }

    if (UNKNOWN_CI == ucReqCiError)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_19);
        VOS_MemCpy(inp, &ucBadCi[0], ulBadCiLen);
        *len = ulBadCiLen;
        return CONFREJ;
    }

    if (1 == ucCiCount) /* ֻ��һ����ʶ��ѡ�� */
    {
        if (1 == pstHisOptions->bStac_compress) /* �Է�֧��LZSѹ�� */
        {
            /* Modified start by menfujun mkf4618 at 2005-04-15 V800R002C01B012  for BYHDLicense */
            /* �ҷ�Ҳ֧��LZS */
            /*lint -e746*/
            if ((1 == pstGotOptions->bStac_compress)
                && (VOS_OK == PPP_CheckStacLimit()))
            /*lint +e746*/
            {
                if (0 == usCIStac_history) /* �Է�LZS��ʷΪ0 */
                {
                    if (g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER)
                    {
                        /* LZS0 �û�δ�� */
                        pstHisOptions->usStac_historys = 0;
                        pstHisOptions->bLZS0_comp = 1;

                        /* Modified start by liutao 38563 at 2005-05-29 PDSN9660V800R002C01B052 for BYHD06338 */
                        pstGotOptions->usStac_historys = 0;
                        pstGotOptions->bLZS0_comp = 1;
                        /* Modified end by liutao 38563 at 2005-05-29 PDSN9660V800R002C01B052 for BYHD06338 */
                        PPP_DBG_OK_CNT(PPP_PHOK_812);
                        return CONFACK;
                    }
                    else if (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER)
                    {
                        /* LZS1�û�δ�� */
                        cp = inp + 2;
                        PPP_PUTSHORT(1, cp);/* Modified by liutao 38563 at 2005-05-29 PDSN9660V800R002C01B052 for BYHD06338 */
                        PPP_DBG_OK_CNT(PPP_PHOK_813);
                        PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, cp);
                        return CONFNAK;
                    }
                    else
                    {
                        PPP_DBG_ERR_CNT(PPP_PHERR_20);
                        /* LZSѹ�����û������� */
                        pstGotOptions->bStac_compress = 0;
                        return CONFREJ;
                    }
                }
                else if (usCIStac_history == pstGotOptions->usStac_historys)
                {
                    /* �Է�֧��LZS1ѹ�� */
                    if (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER)
                    {
                        /* LZS1 �û�δ�� */
                        /* Added start by liutao 38563 at 2005-07-04 PDSN9660V800R002C01B054 for BYHD06721 */
                        if (pstGotOptions->ucStac_checkmode != ucCICheckmode)
                        {
                            /* ˫������ʷͬ����ʽ��һ�� */
                            cp = inp + 2;
                            PPP_PUTSHORT(1, cp);
                            PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, cp);
                            PPP_DBG_OK_CNT(PPP_PHOK_814);
                            return CONFNAK;
                        }

                        /* Added end by liutao 38563 at 2005-07-04 PDSN9660V800R002C01B054 for BYHD06721 */
                        pstHisOptions->usStac_historys = 1;
                        pstHisOptions->bLZS1_comp = 1;

                        /* Modified start by liutao 38563 at 2005-05-29 PDSN9660V800R002C01B052 for BYHD06338 */
                        pstGotOptions->usStac_historys = 1;
                        pstGotOptions->bLZS1_comp = 1;
                        /* Modified end by liutao 38563 at 2005-05-29 PDSN9660V800R002C01B052 for BYHD06338 */
                        return CONFACK;
                    }
                    else if (g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER)
                    {
                        /* LZS0�û�δ�� */
                        cp = inp + 2;
                        PPP_PUTSHORT(0, cp);

                        /* LZS0ѹ������Ҫchekemode��Э����û��˵�� */
                        PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, cp);
                        PPP_DBG_OK_CNT(PPP_PHOK_815);
                        return CONFNAK;
                    }
                    else
                    {
                        /* LZSѹ�����û������� */
                        pstGotOptions->bStac_compress = 0;
                        PPP_DBG_ERR_CNT(PPP_PHERR_21);
                        return CONFREJ;
                    }
                }
                else   /* �Է�֧��LZSѹ������ѹ����ʷ����1 */
                {
                    if (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER)
                    {
                        /* LZS1�û�δ�� */
                        cp = inp + 2;
                        PPP_PUTSHORT(pstGotOptions->usStac_historys, cp);
                        PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, cp);
                        PPP_DBG_OK_CNT(PPP_PHOK_816);
                        return CONFNAK;
                    }
                    else if (g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER)
                    {
                        /* LZS0�û�δ�� */
                        cp = inp + 2;
                        PPP_PUTSHORT(0, cp);

                        /* LZS0ѹ������Ҫchekemode��Э����û��˵�� */
                        PPP_PUTCHAR(pstGotOptions->ucStac_checkmode, cp);
                        PPP_DBG_OK_CNT(PPP_PHOK_817);
                        return CONFNAK;
                    }
                    else
                    {
                        /* LZSѹ�����û������� */
                        pstGotOptions->bStac_compress = 0;
                        PPP_DBG_ERR_CNT(PPP_PHERR_22);
                        return CONFREJ;
                    }
                }
            }
            else /*�ҷ���֧��LZSѹ�� */
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_23);
                return CONFREJ;
            }
        }
        /* Modified start by menfujun mkf4618 at 2005-04-15 V800R002C01B012  for BYHDLicense */
        else if (1 == pstHisOptions->bMppc_compress) /* �Է�֧��MPPC */
        {
            /* �ҷ�Ҳ֧��MPPC */
            if ((1 == pstGotOptions->bMppc_compress)
                && (VOS_OK == PPP_CheckMppcLimit()))
            {
                if (ulCISupportedbits == pstGotOptions->ulMppc_supportedbits)
                {
                    /* ˫��Supported Bitsһ�� */
                    pstHisOptions->ulMppc_supportedbits = ulCISupportedbits;
                    PPP_DBG_OK_CNT(PPP_PHOK_818);
                    return CONFACK;
                }
                else
                {
                    cp = inp + 2;
                    PPP_PUTLONG(pstGotOptions->ulMppc_supportedbits, cp);
                    PPP_DBG_OK_CNT(PPP_PHOK_819);
                    return CONFNAK;
                }
            }
            else  /* �ҷ���֧��MPPC��MPPC�û����� */
            {
                pstGotOptions->bMppc_compress = 0;
                PPP_DBG_ERR_CNT(PPP_PHERR_24);
                return CONFREJ;
            }
        }

        /* Modified end by menfujun mkf4618 at 2005-04-15 V800R002C01B012  for BYHDLicense */
    }
    else if (2 == ucCiCount) /* ��������ʶ��ѡ�� */
    {
        /* Modified start by menfujun mkf4618 at 2005-04-15  V800R002C01B012  for BYHDLicense */
        if ((1 == pstGotOptions->bStac_compress)
            && (VOS_OK == PPP_CheckStacLimit())) /* ��ѡLZSѹ�� */
        {
            if ((1 == usCIStac_history)    /* �Է�֧��LZS1�����û���δ�� */
               && (g_usPppLzs1UserNum < PPPCOMP_LZS1_MAXUSER))
            {
                /* �ܾ�MPPCѹ�� */
                cp = inp;
                PPP_PUTCHAR(CI_MPPC_COMPRESS, cp);
                PPP_PUTCHAR(CILEN_MPPC_COMPRESS, cp);
                PPP_PUTLONG(ulCISupportedbits, cp);
                *len = CILEN_MPPC_COMPRESS;
                PPP_DBG_ERR_CNT(PPP_PHERR_25);
                return CONFREJ;
            }
            else if ((0 == usCIStac_history)   /* �Է�֧��LZS0�����û���δ�� */
               && (g_usPppLzs0UserNum < PPPCOMP_LZS0_MAXUSER))
            {
                /* �ܾ�MPPCѹ�� */
                cp = inp;
                PPP_PUTCHAR(CI_MPPC_COMPRESS, cp);
                PPP_PUTCHAR(CILEN_MPPC_COMPRESS, cp);
                PPP_PUTLONG(ulCISupportedbits, cp);
                *len = CILEN_MPPC_COMPRESS;
                PPP_DBG_ERR_CNT(PPP_PHERR_26);
                return CONFREJ;
            }
        }

        /* ���ж�MPPCѹ�� */
        if ((1 == pstGotOptions->bMppc_compress)
           && (VOS_OK == PPP_CheckMppcLimit()))
        {
            /* �ҷ�֧��MPPC�����û���δ�� */
            /* �ܾ�LZSѹ�� */
            cp = inp;
            PPP_PUTCHAR(CI_STAC_COMPRESS, cp);
            PPP_PUTCHAR(CILEN_STAC_COMPRESS, cp);
            PPP_PUTSHORT(usCIStac_history, cp);
            PPP_PUTCHAR(ucCICheckmode, cp);
            *len = CILEN_STAC_COMPRESS;
            PPP_DBG_ERR_CNT(PPP_PHERR_27);
            return CONFREJ;
        }

        /* Modified end by menfujun mkf4618 at 2005-04-15   for BYHDLicense */
        /* ��������������㣬�ܾ�ȫ�� */
        PPP_DBG_ERR_CNT(PPP_PHERR_28);
        return CONFREJ;
    }
    PPP_DBG_ERR_CNT(PPP_PHERR_29);
 #endif
    return CONFREJ;
}

/* Added end by liutao 38563 at 2004-09-27 V800R002 for PPPѹ����ֲ */
/*
 * CCP has come up  .
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ��״̬��up�Ĵ�����                                         *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tlu������(PPP_FSM_tlu)����             *
****************************************************************************/
VOID PPP_CCP_up(PPPFSM_S *pstFsm)
{
    PPPINFO_S* pstPppInfo = (PPPINFO_S*)pstFsm->pPppInfo;
    PPP_CCP_INFO_S* pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;
    PPP_CCP_options_S *pstGotOptions = NULL;

    pstGotOptions = &(pstCcpInfo->stGotOptions);

    if (pstCcpInfo->ulCcpTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstCcpInfo->ulCcpTimeoutID));
        pstCcpInfo->ulCcpTimeoutID = 0;
    }

    if(pstGotOptions->bMppc_compress)
    {
        pstCcpInfo->ucPppCompType   = PPPCOMP_MPPC;
    }
    else if (pstGotOptions->bStac_compress)
    {
        if (0 == pstGotOptions->usStac_historys)
        {
            pstCcpInfo->ucPppCompType   = PPPCOMP_LZS0;
        }
        else if (1 == pstGotOptions->usStac_historys)
        {
            pstCcpInfo->ucPppCompType   = PPPCOMP_LZS1;
        }
    }

    PPP_Core_ReceiveEventFromProtocol(pstPppInfo,
                                      (ULONG)PPP_EVENT_CCPUP,
                                      NULL);
    return;
}

/*
 * CCP has gone down .
 */

/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ��״̬��finished�Ĵ�����                                   *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstFsm:״̬��                                              *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ���ǻص���������״̬��tlf������(PPP_FSM_tlf)����             *
****************************************************************************/
VOID PPP_CCP_down(PPPFSM_S *pstFsm)
{
    PPP_CCP_INFO_S* pstCcpInfo = (PPP_CCP_INFO_S*)pstFsm->pProtocolInfo;

    pstCcpInfo->ucPppCompType = 0;

    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_CCPDOWN,
                                      NULL);
    return;
}

VOID PPP_CCP_finished(PPPFSM_S *pstFsm)
{
    PPP_Core_ReceiveEventFromProtocol(((PPPINFO_S *)pstFsm->pPppInfo),
                                      (ULONG)PPP_EVENT_CCPFINISHED,
                                      NULL);
    return;
}

/****************************************************************************
* CREATE DATE  ��2000/04/05                                                 *
* CREATED BY   ��SHI YONG                                                   *
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
USHORT PPP_CCP_extcode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen,
                       ULONG ulRPIndex)                                                                                      /* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
{
    if (pstFsm->ucState != PPP_STATE_OPENED)
    {

        return VOS_ERR;
    }

    switch (ucCode)
    {
    case RESETREQ:
        PPP_CCP_rresetreq(pstFsm, ucId, pHead, pPacket, ulLen, ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */
        break;
    case RESETACK:
        PPP_CCP_rresetack(pstFsm, ucId, pPacket, ulLen, ulRPIndex);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

        break;
    default:
        PPP_DBG_ERR_CNT(PPP_PHERR_30);
        /* RUC event */
        PPP_FSM_ReceiveUnknownCode(pstFsm, ucId, pHead, pPacket, ulLen);
        return VOS_ERR;
    }

    return VOS_OK;
}

/* Added start by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */

/*****************************************************************************
 �� �� ��  : PPP_CCP_rresetreq
 ��������  : ����ResetReq��Ϣ�Ĵ�����
 �������  : PPPFSM_S *pstFsm
             UCHAR id
             UCHAR *pHead
             UCHAR *pPacket
             ULONGulLen
             ULONG ulRPIndex
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2004��9��22��
    ��    ��   : liutao 38563
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CCP_rresetreq (PPPFSM_S *pstFsm, UCHAR id, UCHAR *pHead, UCHAR *pPacket, ULONG
                        ulLen, ULONG ulRPIndex)
{
    /* Deleted start by zhudaoming 62333 at 2007-12-06 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
    /*GGSN ��֧��ѹ����V9û��GSPC�ۿ�����ʱɾ���˶δ���*/






    /* Deleted end by zhudaoming 62333 at 2007-12-06 GGSN9811V9R7C01B02 for L2TP/PPP V9��ֲ */
    return;
}

/*****************************************************************************
 �� �� ��  : PPP_CCP_rresetack
 ��������  : ����Reset ACK��Ϣ������
 �������  : PPPFSM_S *pstFsm
             UCHAR id
             UCHAR *pPacket
             ULONGulLen
             ULONG ulRPIndex
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2004��9��22��
    ��    ��   : liutao 38563
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_CCP_rresetack (PPPFSM_S *pstFsm, UCHAR id, UCHAR *pPacket, ULONG
                        ulLen, ULONG ulRPIndex)
{
    return;
}

/* Added end by liutao 38563 at 2004-09-22 V800R002 for PPPѹ����ֲ */


/****************************************************************************
* CREATE DATE  ��2000/06/24                                                 *
* CREATED BY   ��Shi Yong                                                   *
* FUNCTION     ������RESETREQ����                                           *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo    :PPP���ƿ�                                   *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_Core_NetworkPhase                                      *
****************************************************************************/
VOID PPP_CCP_SendResetReq(PPPINFO_S* pstPppInfo)
{
    return;
}

VOID PPP_CCP_SendResetReqTimeout (VOID *ulIndex)
{
    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    PPPINFO_S* pstPppInfo;
    PPP_CCP_INFO_S* pstCcpInfo;

    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_31);
        return;
    }

    pstCcpInfo = pstPppInfo->pstCcpInfo;
    if (NULL == pstCcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_32);
        return;
    }

    pstCcpInfo->stFsm.ucPktId--;
    PPP_CCP_SendResetReq(pstPppInfo);
    return;
}

/* Added by heyajun kf1199 at 2004-08-05 V800R001C01B010 for BYHD03171 */
VOS_VOID PPP_CCP_Timeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S* pPppInfo;
    PPP_CCP_INFO_S* pstCcpInfo;

    GETPPPINFOPTRBYRP(pPppInfo, ulPppId);
    if (NULL == pPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_33);
        return;
    }

    pstCcpInfo = pPppInfo->pstCcpInfo;
    if (NULL == pstCcpInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_34);
        return;
    }

    (VOID)VOS_StopRelTimer(&(pstCcpInfo->ulCcpTimeoutID));
    pstCcpInfo->ulCcpTimeoutID = 0;

    PPP_CCP_ReceiveEventFromCore(pPppInfo->pstCcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL);
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
