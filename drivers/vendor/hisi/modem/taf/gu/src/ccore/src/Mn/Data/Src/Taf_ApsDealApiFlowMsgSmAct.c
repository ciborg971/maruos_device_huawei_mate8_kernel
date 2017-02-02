


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "NasCommDef.h"
#include "MnComm.h"
#include "TafApsCtx.h"
#include "MnApsComm.h"
#include "TafApsSndSm.h"

#include "WasNvInterface.h"

#include "TafApsComFunc.h"
#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIFLOWMSGSMACT_C


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


VOS_UINT32  Aps_PdpActReq(
    APS_PDP_ACT_REQ_ST                 *pActReq
)
{
    SMREG_PDP_ACTIVATE_REQ_STRU         *pstPdpActReq;

    if ( VOS_NULL_PTR == pActReq)
    {
        APS_WARN_LOG("Aps_PdpActReq input null pointer !");
        return TAF_APS_FAIL;
    }

    APS_NORM_LOG("APS rcv APS_PDP_ACT_REQ_ST ");

    /* ������Ϣ�������Ϣͷ */
    pstPdpActReq = (SMREG_PDP_ACTIVATE_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ACTIVATE_REQ);
    if (VOS_NULL_PTR == pstPdpActReq)
    {
        return TAF_APS_FAIL;
    }

    /*�����SM���͵�MSG;*/
    if ( TAF_APS_FAIL == Aps_PackSmActReqMsg (pActReq, pstPdpActReq))
    {
        APS_WARN_LOG("Aps PackSmActReq Msg ERR !");
        PS_FREE_MSG(WUEPS_PID_TAF, pstPdpActReq);
        return TAF_APS_FAIL;
    }

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpActReq))
    {
        APS_WARN_LOG("Aps_PdpActReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    /*���PDP״̬��;*/
    Aps_ActReqFillState(pActReq);
    return TAF_APS_SUCC;
}


VOS_UINT32 Aps_PackSmActReqMsg (
    APS_PDP_ACT_REQ_ST                 *pActReq,
    SMREG_PDP_ACTIVATE_REQ_STRU        *pStPdpActReq
)
{
    VOS_UINT32                          ulReturnValue;

    pStPdpActReq->bitOpAcsPointName = VOS_FALSE;
    pStPdpActReq->bitOpProtCfgOpt   = VOS_FALSE;
    pStPdpActReq->bitOpSapi         = VOS_FALSE;
    pStPdpActReq->bitOpSpare        = VOS_FALSE;

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pStPdpActReq->ucConnectId       = pActReq->ucPdpId;

    /*LLC SAPI*/
    pStPdpActReq->bitOpSapi         = VOS_TRUE;
    pStPdpActReq->ucSapi            = pActReq->ucSapi;

    /*QOS*/
    Aps_PackSmQos(  &(pActReq->ReqQos),
                    &(pStPdpActReq->stReqQos));

    /*ADDR*/
    ulReturnValue = Aps_PackSmAddr( &pActReq->ucPdpType,
                                    pActReq->aucIpAddr,
                                    &(pStPdpActReq->stReqPdpAddr));
    if (TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PackSmAddr err ");
        return  TAF_APS_FAIL;
    }

    /*APN*/
    if (0 == pActReq->aucApn[0])
    {
        /*���APN����Ϊ0����ѡAPN*/
        pStPdpActReq->bitOpAcsPointName = VOS_FALSE;
    }
    else
    {
        pStPdpActReq->bitOpAcsPointName = VOS_TRUE;
        Aps_PackSmApn( pActReq->aucApn, &(pStPdpActReq->stAcsPointName));
    }

    if (APS_ADDR_PPP != pActReq->ucPdpType)
    {
        /*PCO*/
        pStPdpActReq->bitOpProtCfgOpt   = VOS_TRUE;
        if ( TAF_APS_FAIL == Aps_PackSmPco(pActReq, &pStPdpActReq->stProtCfgOpt))
        {
            APS_WARN_LOG("Aps_PackSmPco err ");
            return  TAF_APS_FAIL;
        }
    }

    return  TAF_APS_SUCC;
}
VOS_VOID    Aps_ActReqFillState(
    APS_PDP_ACT_REQ_ST                 *pActReq
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId                             = pActReq->ucPdpId;


    /*��������*/
    g_PdpEntity[ucPdpId].ActType        = APS_PDP_ACT_PRI;

    /*���𼤻�ķ�ʽ*/
    g_PdpEntity[pActReq->ucPdpId].PdpProcTrackFlag  = VOS_TRUE;


    /*GPRS������ʶҪ��1*/
    g_PdpEntity[ucPdpId].PdpGprsParaFlag            = VOS_TRUE;

    /*QOS */
    g_PdpEntity[ucPdpId].PdpQosFlag                 = VOS_TRUE;
    PS_MEM_CPY(           &(g_PdpEntity[ucPdpId].PdpQos),
                          &(pActReq->ReqQos),
                          sizeof(APS_PDP_QOS_STRU));

    /*AUTH*/
    if (pActReq->OP_AUTH)
    {
        if ( TAF_PCO_NOT_AUTH != pActReq->PdpAuth.AuthType)
        {
            g_PdpEntity[ucPdpId].PdpAuthFlag        = VOS_TRUE;
            PS_MEM_CPY(   &g_PdpEntity[ucPdpId].AuthTab,
                          &pActReq->PdpAuth,
                          sizeof(TAF_PDP_PCO_AUTH_STRU));
        }
    }

    /*APN*/
    if (pActReq->OP_APN)
    {
        g_PdpEntity[ucPdpId].PdpApnFlag             = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpApn.ucLength        = pActReq->aucApn[0];
        if (pActReq->aucApn[0] > APS_MAX_LENGTH_OF_APN)
        {
            APS_WARN_LOG("pActReq->aucApn[0] > APS_MAX_LENGTH_OF_APN ");
            pActReq->aucApn[0] = APS_MAX_LENGTH_OF_APN;
        }
        PS_MEM_CPY(       g_PdpEntity[ucPdpId].PdpApn.aucValue,
                          &(pActReq->aucApn[1]),
                          pActReq->aucApn[0]);
    }

    /*ADDR.PdpType */
    g_PdpEntity[ucPdpId].PdpAddrFlag                = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum       = pActReq->ucPdpType;

    /*ADDR.value */
    if ( APS_ADDR_STATIC_IPV4 == pActReq->ucPdpType)
    {
        PS_MEM_CPY(       g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                          pActReq->aucIpAddr,
                          TAF_IPV4_ADDR_LEN );
    }
    else
    {
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2]   = 0;
        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3]   = 0;
    }

    /*XID*/
    if ( pActReq->Op_Xid_PCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth = pActReq->ucPCmprAlgrth;
    }

    if ( pActReq->Op_Xid_DCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth = pActReq->ucDCmprAlgrth;
    }

    /*Dns*/
    if (  (VOS_TRUE == pActReq->OP_DNS)
        &&(  (VOS_TRUE == pActReq->PdpDns.bitOpPrimDnsAddr)
           ||(VOS_TRUE == pActReq->PdpDns.bitOpSecDnsAddr) ))
    {
        /*��һ����Ч��DNS������״̬��*/
        g_PdpEntity[ucPdpId].PdpDnsFlag             = VOS_TRUE;

        if (VOS_TRUE == pActReq->PdpDns.bitOpPrimDnsAddr)
        {
            g_PdpEntity[ucPdpId].PdpDns.OP_PriDns   = VOS_TRUE;

            PS_MEM_CPY(g_PdpEntity[ucPdpId].PdpDns.aucPriDns,
                       pActReq->PdpDns.aucPrimDnsAddr,
                       TAF_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pActReq->PdpDns.bitOpSecDnsAddr)
        {
            g_PdpEntity[ucPdpId].PdpDns.OP_SecDns   = VOS_TRUE;

            PS_MEM_CPY(g_PdpEntity[ucPdpId].PdpDns.aucSecDns,
                       pActReq->PdpDns.aucSecDnsAddr,
                       TAF_IPV4_ADDR_LEN);
        }
    }

    /*TFT*/
    g_PdpEntity[ucPdpId].PdpTftFlag                 = VOS_FALSE;

    return;
}



VOS_UINT32  Aps_PdpSecActReq(
    APS_PDP_SEC_ACT_REQ_ST             *pSecActReq
)
{
    VOS_UINT32                          ulResult;
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pActSecReqMsg;

    APS_NORM_LOG("APS rcv APS_PDP_ACT_SEC_REQ_ST ");


    /*�����������Ƿ�Ϸ�;*/
    ulResult = Aps_PdpSecActReqParaCheck( pSecActReq );
    if (APS_PARA_INVALID == ulResult)
    {
        APS_WARN_LOG("Aps_PdpSecActReqParaCheck err ");

        return TAF_APS_FAIL;
    }
    /*��״̬���д���*/

    /*PDP�����Ƿ�PPP����*/
    if ( APS_ADDR_PPP == g_PdpEntity[pSecActReq->ucPriPdpId].PdpAddr.ucPdpTypeNum)
    {
        /*����ʧ�ܵ��¼��ڵ��øú����ĺ�����ִ��*/

        APS_WARN_LOG("prim PDP state err ");
        return  TAF_APS_FAIL;
    }

    /* ������Ϣ�������Ϣͷ */
    pActSecReqMsg = (SMREG_PDP_ACTIVATE_SEC_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ACTIVATE_SEC_REQ);
    if (VOS_NULL_PTR == pActSecReqMsg)
    {
        return TAF_APS_FAIL;
    }

    /*���ú���Aps_PackSmSecActReqMsg()�����SM���͵���Ϣ�ṹ;*/
    Aps_PackSmSecActReqMsg(pSecActReq, pActSecReqMsg);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pActSecReqMsg))
    {
        APS_WARN_LOG("Aps_PdpSecActReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    /*���״̬����*/
    Aps_SecActReqFillState(pSecActReq);

    return  TAF_APS_SUCC;

}


VOS_VOID    Aps_SecActReqFillState(
    APS_PDP_SEC_ACT_REQ_ST              *pSecActReq
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucPriPdpId;

    ucPdpId                             = pSecActReq->ucPdpId;
    ucPriPdpId                          = pSecActReq->ucPriPdpId;


    /*GPRS������ʶҪ��1*/
    g_PdpEntity[ucPdpId].PdpGprsParaFlag            = VOS_TRUE;

    /* ���μ���һ����APP�������𼤻� */
    g_PdpEntity[ucPdpId].PdpProcTrackFlag           = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct
                                                    = APS_APP_MANUL_ACT;
    g_PdpEntity[ucPdpId].ActType                    = APS_PDP_ACT_SEC;

    /*ADDR*/
    g_PdpEntity[ucPdpId].PdpAddrFlag    = g_PdpEntity[ucPriPdpId].PdpAddrFlag;
    g_PdpEntity[ucPdpId].PdpAddr        = g_PdpEntity[ucPriPdpId].PdpAddr;

    /*APN*/
    g_PdpEntity[ucPdpId].PdpApnFlag     = g_PdpEntity[ucPriPdpId].PdpApnFlag;
    g_PdpEntity[ucPdpId].PdpApn         = g_PdpEntity[ucPriPdpId].PdpApn;

    /*LinkedNsapi*/
    g_PdpEntity[ucPdpId].ActType        = APS_PDP_ACT_SEC;
    g_PdpEntity[ucPdpId].ucLinkedNsapi  = g_PdpEntity[ucPriPdpId].ucNsapi;

    /*TFT*/
    if ( VOS_TRUE == pSecActReq->Op_Tft )
    {
        g_PdpEntity[ucPdpId].PdpTftFlag = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpTft[0]  = pSecActReq->Tft;
    }

    /*QOS*/
    g_PdpEntity[ucPdpId].PdpQosFlag     = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpQos         = pSecActReq->Qos;

    /*AUTH*/
    g_PdpEntity[ucPdpId].PdpAuthFlag    = g_PdpEntity[ucPriPdpId].PdpAuthFlag;
    g_PdpEntity[ucPdpId].AuthTab        = g_PdpEntity[ucPriPdpId].AuthTab;

    /*XID*/
    if ( pSecActReq->Op_Xid_PCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth = pSecActReq->ucPCmprAlgrth;
    }

    if ( pSecActReq->Op_Xid_DCmp)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth = pSecActReq->ucDCmprAlgrth;
    }

    /*DNS*/
    g_PdpEntity[ucPdpId].PdpDnsFlag     = g_PdpEntity[ucPriPdpId].PdpDnsFlag;
    g_PdpEntity[ucPdpId].PdpDns         = g_PdpEntity[ucPriPdpId].PdpDns;

    return;
}


VOS_UINT32  Aps_PdpSecActReqParaCheck ( APS_PDP_SEC_ACT_REQ_ST *pSecActReq)
{

    /*��ڲ����ĺϷ���������������֤*/

    /*pdpId*/
    if( !(APS_JUDEG_PDPID_VALID(pSecActReq->ucPdpId)) )

    {
        return  APS_PARA_INVALID;
    }

    /*PriPdpId*/
    if( !(APS_JUDEG_PDPID_VALID(pSecActReq->ucPriPdpId)) )

    {
        return  APS_PARA_INVALID;
    }

#if 0
    /*TFT*/
    if( pSecActReq->Op_Tft )
    {
        if( TAF_APS_FAIL == Aps_TftValidOrNot(&pSecActReq->Tft))
        {
            return  APS_PARA_INVALID;
        }
    }
#endif

    return  APS_PARA_VALID;
}


VOS_VOID Aps_PackSmSecActReqMsg(
    APS_PDP_SEC_ACT_REQ_ST             *pSecActReq,
    SMREG_PDP_ACTIVATE_SEC_REQ_STRU    *pStSecActReq
)
{
    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pStSecActReq->ucConnectId       = pSecActReq->ucPdpId;
    pStSecActReq->bitOpSapi         = VOS_FALSE;
    pStSecActReq->bitOpTft          = VOS_FALSE;
    pStSecActReq->bitOpSpare        = VOS_FALSE;

    /*LLC SAPI*/
    pStSecActReq->bitOpSapi         = VOS_TRUE;
    pStSecActReq->ucSapi            = pSecActReq->ucSapi;

    /*QOS*/
    Aps_PackSmQos(  &(pSecActReq->Qos),
                    &(pStSecActReq->stRequestedQos)   );

    /*TFT*/
    if ( VOS_TRUE == pSecActReq->Op_Tft )
    {
        pStSecActReq->bitOpTft      = VOS_TRUE;
        Aps_PackSmTft(    pSecActReq->ucPdpId,
                          &pSecActReq->Tft,
                          &(pStSecActReq->stTft) );
    }

    /*PrimNsapi*/
    pStSecActReq->ucPrimNsapi       = g_PdpEntity[pSecActReq->ucPriPdpId].ucNsapi;

    return;
}
VOS_UINT32  Aps_PdpMdfReq( APS_PDP_MDF_REQ_ST              *pMdfReq)
{

    SMREG_PDP_MODIFY_REQ_STRU          *pstPdpModReq;

    APS_NORM_LOG("APS rcv APS_PDP_MDF_REQ_ST ");

    if ( VOS_NULL_PTR == pMdfReq )
    {
        /*�ϱ��޸�ʧ��*/
        APS_WARN_LOG("ERROR! The input pointer parameter  can not be NULL ! ");
        return(TAF_APS_FAIL);
    }

    /*������Ĳ����洢����g_PdpModifyReqTable*/
    g_PdpModifyReqTable[pMdfReq->ucPdpId]   = (*pMdfReq);

    /*�������޸�QOS�ı�ʶ*/
    if ( pMdfReq->Op_Qos )
    {
        g_PdpModifyReqTable[pMdfReq->ucPdpId].Op_Spare = APS_MDF_HAS_QOS;
    }
    else
    {
        g_PdpModifyReqTable[pMdfReq->ucPdpId].Op_Spare = APS_MDF_NO_QOS;
    }

    /* ������Ϣ�������Ϣͷ */
    pstPdpModReq = (SMREG_PDP_MODIFY_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_MODIFY_REQ);
    if (VOS_NULL_PTR == pstPdpModReq)
    {
        return TAF_APS_FAIL;
    }

    /*������SM���͵��޸���Ϣ*/
    Aps_PackSmMdfReqMsg( pMdfReq, pstPdpModReq);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpModReq))
    {
        APS_WARN_LOG("Aps_PdpMdfReq Snd msg fail!");
        return TAF_APS_FAIL;
    }

    return(TAF_APS_SUCC);
}
VOS_VOID    Aps_PackSmMdfReqMsg( APS_PDP_MDF_REQ_ST             *pMdfReq,
                                            SMREG_PDP_MODIFY_REQ_STRU       *pStPdpMdfReq   )
{
    /*StPcpMsg�ĳ�ʼ��*/
    /* ST_PCP_MSG����Ϣ���� */

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pStPdpMdfReq->ucConnectId           = pMdfReq->ucPdpId;
    pStPdpMdfReq->bitOpRequestedNewQos  = VOS_FALSE;
    pStPdpMdfReq->bitOpNsapi            = VOS_FALSE;
    pStPdpMdfReq->bitOpNewtft           = VOS_FALSE;
    pStPdpMdfReq->bitOpSapi             = VOS_FALSE;
    pStPdpMdfReq->bitOpSpare            = VOS_FALSE;

    /*SAPI*/
    pStPdpMdfReq->bitOpSapi             = VOS_TRUE;
    pStPdpMdfReq->ucSapi                = pMdfReq->ucSapi;

    /*Qos*/
    if ( pMdfReq->Op_Qos)
    {
        pStPdpMdfReq->bitOpRequestedNewQos = VOS_TRUE;
        Aps_PackSmQos(      &(pMdfReq->Qos),
                            &(pStPdpMdfReq->stRequestedNewQos) );
    }

   #if 0
    /*TFT */
    if ( pMdfReq->Op_Tft)
    {
        pStPdpMdfReq->OP_Newtft         = VOS_TRUE;
        Aps_PackSmTft(      pMdfReq->ucPdpId,
                            &pMdfReq->Tft,
                            &pStPdpMdfReq->Newtft );
    }
    #endif

    /*��MODIRY_REQ����дNSAPI */
    pStPdpMdfReq->bitOpNsapi            = VOS_TRUE;
    pStPdpMdfReq->ucNsapi               = g_PdpEntity[pMdfReq->ucPdpId].ucNsapi;

    return;
}
VOS_UINT32 Aps_AppDeactReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
)
{
    VOS_UINT32                          ulResult;
    APS_PDP_DEACT_REQ_ST                ApsDeActReq;

    /* ��ʼ�� */
    ulResult                            = VOS_OK;

    /* ��дȥ������� */
    ApsDeActReq.ucPdpId                 = ucPdpId;
    ApsDeActReq.ucTearDown              = TAF_PDP_NOT_TEAR_DOWN;
    ApsDeActReq.enCause                 = enCause;

    /* �����Ҫȥ�����PDP����PDP�����Teardown��ʶ */
    if (APS_PDP_ACT_PRI == TAF_APS_GetPdpEntActType(ucPdpId))
    {
        ApsDeActReq.ucTearDown      = TAF_PDP_TEAR_DOWN;
    }

    /* ����ȥ����� */
    ulResult    = Aps_PdpDeActReq(&ApsDeActReq);
    if (VOS_OK != ulResult)
    {
        MN_ERR_LOG("Aps_AppDeactReq: Deactivate PDP failed!");
    }

    g_PdpEntity[ucPdpId].PdpProcTrackFlag   = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitDeAct
                                            = APS_APP_INIT_DEACT;
     return ulResult;
}



VOS_UINT32 Aps_PdpDeActReq(
    APS_PDP_DEACT_REQ_ST               *pDeActReq
)
{
    VOS_UINT8                           ucPdpId;

    APS_NORM_LOG("APS rcv APS_PDP_DEACT_REQ_ST ");

    ucPdpId = pDeActReq->ucPdpId;


    /*���PDP������PPP,��Ӧ����TEARDOWN,��ʱ����TEARDWN,����û��TEARDOWN����ȥ����*/
    if ( ( VOS_FALSE == g_PdpEntity[ucPdpId].PdpAddrFlag)
        || ( APS_ADDR_PPP == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
    {
        /*û�е�ַ,˵����PPP;������д��ADDRFLAG,��PDP����ΪPPP*/
        pDeActReq->ucTearDown           = TAF_PDP_NOT_TEAR_DOWN;
    }

    if (TAF_PDP_NOT_TEAR_DOWN == pDeActReq->ucTearDown)
    {
        /* ״̬���е�TEARDOWN��ֵ */
        APS_SET_PDPENTITY_TEATDOWN(ucPdpId, APS_DEACT_NOTEARDOWN);
        Aps_PdpDeActOneReq(pDeActReq, APS_SYS_REL);
    }
    else
    {
        APS_SET_PDPENTITY_TEATDOWN(ucPdpId, APS_DEACT_TEARDOWN);
        Aps_PdpDeActOneReq(pDeActReq, APS_SYS_REL);
    }

    return VOS_OK;
}


VOS_VOID    Aps_PdpDeActOneReq(         APS_PDP_DEACT_REQ_ST   *pDeActReq,
                                        VOS_UINT8               ucRelSmType)
{
    SMREG_PDP_DEACTIVATE_REQ_STRU      *pStDeActReq;

    /* ������Ϣ�������Ϣͷ */
    pStDeActReq = (SMREG_PDP_DEACTIVATE_REQ_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_DEACTIVATE_REQ);
    if (VOS_NULL_PTR == pStDeActReq)
    {
        return;
    }

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pStDeActReq->ucConnectId            = pDeActReq->ucPdpId;

    /*��Ϣ��ʼ��*/
    pStDeActReq->bitOpTearDownInd       = VOS_FALSE;
    pStDeActReq->bitOpNsapi             = VOS_FALSE;
    pStDeActReq->bitOpPcpTaCause        = VOS_FALSE;
    pStDeActReq->bitOpSpare             = VOS_FALSE;

    /*�����Ϣ*/
    pStDeActReq->bitOpTearDownInd       = VOS_TRUE;
    pStDeActReq->ucTearDownInd          = pDeActReq->ucTearDown;

    /*����NSAPI����Ϊ����Դʱ���ܻ�û�з���NSAPI
    pStDeActReq->OP_Nsapi               = VOS_TRUE;
    pStDeActReq->ucNsapi                = g_PdpEntity[pDeActReq->ucPdpId].ucNsapi;
    */

    pStDeActReq->enCause                = pDeActReq->enCause;

    /*��ֵȥ����SM��ԭ��,�����ͷŻ���ϵͳ�ͷ�*/
    pStDeActReq->bitOpPcpTaCause        = VOS_TRUE;
    pStDeActReq->enPcpTaCause           = ucRelSmType;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pStDeActReq))
    {
        APS_WARN_LOG("Aps_PdpDeActOneReq Snd msg fail!");
    }

    return;
}



/*****************************************************************************
 Prototype      : Aps_PdpDeActReqParaCheck()
 Description    : ��麯��Aps_PdpActReq()����ڲ����Ƿ�Ϸ�
 Input          : pSmActReq
 Output         :
 Return Value   : pucResult,ȡֵ: APS_PARA_VALID��APS_PARA_INVALID
 Data Accessed  : NO
 Data Update    : NO
 Calls          :
 Called By      : Aps_PdpActReq()
 History        : ---
  1.Date        : 2005-
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PdpDeActReqParaCheck( APS_PDP_DEACT_REQ_ST *pDeActReq )
{
    if ( VOS_NULL == pDeActReq)
    {
        APS_WARN_LOG("Aps_PdpDeActReq input pointer is NULL ");
        return  APS_PARA_INVALID;
    }

    if (!(APS_JUDEG_PDPID_VALID(pDeActReq->ucPdpId)))
    {
        APS_WARN_LOG("Aps_PdpDeActReq input ucPdpId ERR ");
        return  APS_PARA_INVALID;
    }

    if (!(APS_JUDEG_TEARDOWN_VALID(pDeActReq->ucTearDown)))
    {
        APS_WARN_LOG("Aps_PdpDeActReq input ucTearDown ERR ");
        return  APS_PARA_INVALID;
    }

    return  APS_PARA_VALID;

}
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, end */


VOS_VOID  Aps_PackSmQos   (
    APS_PDP_QOS_ST                     *pApsQos,
    SM_TAF_QOS_STRU                    *pSmQos
)
{
    VOS_INT8                            ue_revision;
    WAS_NVIM_UE_CAPA_STRU               stUECapa;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    PS_MEM_SET(&stUECapa, 0x00, sizeof(WAS_NVIM_UE_CAPA_STRU));
    /* ��ȡ֧������16QAM,DC UPA ֧������ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(WAS_NVIM_UE_CAPA_STRU)))
    {
        APS_WARN_LOG("Aps_PackSmQos: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
        return;
    }

    ue_revision = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);


#if (PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (ue_revision >= PS_PTL_VER_R5)
    {
        if ( ( TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
          && ( APS_2G_BIT3_ENABLE == g_ucDisable2GR5QosExt ))
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0xB;
        }
        else
        {
#if (PS_UE_REL_VER >= PS_PTL_VER_R7)
            if (TAF_APS_R7_SUPP_UL16QAM_OR_DCUPA(ue_revision, stUECapa))
            {
                enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
                /* TDS���ʴﲻ��11M���ϣ����TDS�»��ǰ��ճ���ΪE�����������޷����� */
                if ((TAF_SDC_SYS_MODE_WCDMA == TAF_SDC_GetSysMode())
                && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode))
                {
                    pSmQos->ulQosLen = 0xE;
                }
                else
                {
                    pSmQos->ulQosLen = 0x10;
                }
            }
            else
#endif
            {
                /* IEI Length */
                pSmQos->ulQosLen = 0xE;
            }

        }
    }
    else
#endif
    {
        if (ue_revision >= PS_PTL_VER_R99)
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0xB;
        }
        else
        {
            /* IEI Length */
            pSmQos->ulQosLen = 0x3;
        }
    }

    /* ucDelayClass����3λ, ʹucDelayClass��3����Чλλ��Э����QOS IE octet3��
    1~8λ�еĵ�6,5,4λ, ʹ��ͬ���ķ������Э����QOS IE ������octet */
    pSmQos->aucQos[0]       = (VOS_UINT8)((pApsQos->ucDelayClass)<<3);
    pSmQos->aucQos[0]       |= (pApsQos->ucReliabClass);

    pSmQos->aucQos[1]       = (VOS_UINT8)((pApsQos->ucPeakThrough)<<4);
    pSmQos->aucQos[1]       |= (pApsQos->ucPrecedenceClass);

    pSmQos->aucQos[2]       = (pApsQos->ucMeanThrough);

    if (ue_revision >= PS_PTL_VER_R99)
    {
        pSmQos->aucQos[3]   = (VOS_UINT8)((pApsQos->ucTrafficClass)<<5);
        pSmQos->aucQos[3]   |= (VOS_UINT8)((pApsQos->ucDeliverOrder)<<3);
        pSmQos->aucQos[3]   |= (pApsQos->ucDeliverOfErrSdu);

        pSmQos->aucQos[4]   = (pApsQos->ucMaximSduSize);
        pSmQos->aucQos[5]   = (pApsQos->ucMaxBitRateForUp);
        pSmQos->aucQos[6]   = (pApsQos->ucMaxBitRateForDown);

        pSmQos->aucQos[7]   = (VOS_UINT8)((pApsQos->ucResidualBer)<<4);
        pSmQos->aucQos[7]  |= (pApsQos->ucSduErrRatio);

        pSmQos->aucQos[8]  = (VOS_UINT8)((pApsQos->ucTransDelay)<<2);
        pSmQos->aucQos[8]  |= (pApsQos->ucTraffHandlPrior);

        pSmQos->aucQos[9]  = (pApsQos->ucGuarantBitRateForUp);
        pSmQos->aucQos[10] = (pApsQos->ucGuarantBitRateForDown);
    }

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (ue_revision >= PS_PTL_VER_R5)
    {
        if ( (TAF_APS_RAT_TYPE_GSM != TAF_APS_GetCurrPdpEntityRatType())
          || (APS_2G_BIT3_ENABLE != g_ucDisable2GR5QosExt) )
        {
            pSmQos->aucQos[11]  = (VOS_UINT8)((pApsQos->ucSignallingIndication)<<4);
            pSmQos->aucQos[11] |= (pApsQos->ucSrcStatisticsDescriptor);

            pSmQos->aucQos[12]  = (pApsQos->ucMaxBitRateForDownExt);
            pSmQos->aucQos[13]  = (pApsQos->ucGuarantBitRateForDownExt);
        }
    }
#endif
#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (0x10 == pSmQos->ulQosLen)
    {
        if ( ( TAF_APS_RAT_TYPE_GSM != TAF_APS_GetCurrPdpEntityRatType())
          || (APS_2G_BIT3_ENABLE != g_ucDisable2GR5QosExt) )
        {
            pSmQos->aucQos[14]  = (pApsQos->ucMaxBitRateForUpExt);
            pSmQos->aucQos[15]  = (pApsQos->ucGuarantBitRateForUpExt);
        }
    }
#endif
    return;

}


VOS_VOID  Aps_PackSmTft   (     VOS_UINT8           ucPdpId,
                                APS_PDP_TFT_ST*     pApsTft,
                                SM_TAF_TFT_STRU*    pSmTft  )
{

    VOS_UINT16 usBufSize = 0;


    /*Э���е�OCTET3�ĸ�3λ��TFT�Ĳ�����,�����TFTֻ֧��creat ��replace TFT, ��֧��
    ����TFT����, �ο�10.5.6.12/24008; OCTET3�ĵ�4λ��ֵΪ������������Ŀ,
    OCTET3�ĵ�4λ = 1;*/
    /*���ݸ�PDP��ǰ�Ƿ��Ѿ�ʹ����TFT��������������creat ����replace*/
    if (g_PdpEntity[ucPdpId].PdpTftFlag)
    {
        pSmTft->aucNewtft[0] = APS_TFT_REPLACE_TFT | APS_TFT_ONE_FILTER;
    }
    else
    {
        pSmTft->aucNewtft[0] = APS_TFT_CREAT_TFT | APS_TFT_ONE_FILTER;
    }

    /* OCTET4��ʼΪfilter1������ */
    pSmTft->aucNewtft[1] =(VOS_UINT8)pApsTft->ucPacketFilterId;/* OCTET4 Packet filter identifier 1 */
    pSmTft->aucNewtft[2] = pApsTft->ucPrecedence;              /* OCTET5 ,Packet filter evaluation precedence 1 */

    /* pSmTft->Newtft[3] Ϊ�±�filter1��4��component��ĳ��Ⱥ�,�����������
    4��component���������ֽ� */

    /* �������[4]��ʼ��filter1��components */
    usBufSize = APS_TFT_FILTER1_COMPONENT_BEGIN;

    if ( pApsTft->OP_SourceIpAddrAndMask )
    {
        /* component1�� IPv4 source address type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_IPV4_ADDR;
        usBufSize++;

        /* pSmTft->Newtft[5��8] ��ֵΪ4���ֽڵĵ�ַpApsTft-> ucSourceIpAddress;
        " Bit 8 of octet 5 represents the most signifi cant bit of the IP address
        and bit 1 of octet 8 the least signifi cant bit ." */
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[0];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[1];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[2];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpAddress[3];
        usBufSize++;

        /*pSmTft->Newtft[9��12]��ֵΪ4���ֽڵ�����pApsTft->ucSourceIpMask;*/
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[0];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[1];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[2];
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->aucSrcIpMask[3];
        usBufSize++;
    }


    if ( pApsTft->OP_ProtocolId )
    {
        /* component2�� Protocol identifier/Next header type*/
        pSmTft->aucNewtft[usBufSize] = APS_TFT_PROTOCAL_ID;
        usBufSize++;
        pSmTft->aucNewtft[usBufSize] = pApsTft->ucProtocolId;
        usBufSize++;
    }


    if ( pApsTft->OP_DestPort )
    {
        /* component3�� Destination port range type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_DEST_PORT_RANG ;
        usBufSize++;

        /*pSmTft->Newtft[16~17] = pApsTft->usDestinationPortLowLimit;
        ����port range low limit�ȷ���*/
        /*���ֽ��ȷ�*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usDstPortLowLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* ��λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usDstPortLowLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* ��λ�ֽ� */
        usBufSize++ ;

        /*pSmTft->Newtft[18~19] = pApsTft->usDestinationPortHighLimit;
        port range high limit���� */
        /*���ֽ��ȷ�*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usDstPortHighLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* ��λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usDstPortHighLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* ��λ�ֽ� */
        usBufSize++ ;
    }


    if ( pApsTft->OP_SourcePort )
    {
        /* component4�� Source port range type */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_SOURCE_PORT_RANG;
        usBufSize++;
        /*pSmTft->Newtft[21~22] = pApsTft->usSourcePortLowLimit*/

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usSrcPortLowLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* ��λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usSrcPortLowLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* ��λ�ֽ� */
        usBufSize++;

        /*pSmTft->Newtft[23~24] = pApsTft->usSourcePortHighLimit;*/
        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->usSrcPortHighLimit
                      & APS_UINT16_HIGH_LOCATION_OCTET)>>8);    /* ��λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)(pApsTft->usSrcPortHighLimit
                      & APS_UINT16_LOW_LOCATION_OCTET);         /* ��λ�ֽ� */
        usBufSize++;
    }


    if ( pApsTft->OP_ulSecuParaIndex)
    {
        /* component4�� IP Sec SPI */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_SPI;
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_32_TO_25_OCTET)>>24);/* ���λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_24_TO_17_OCTET)>>16);/* �θ�λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_16_TO_8_OCTET)>>8);  /* �ε�λ�ֽ� */
        usBufSize++;

        pSmTft->aucNewtft[usBufSize]
            = (VOS_UINT8)((pApsTft->ulSecuParaIndex
                       & APS_UINT32_RESERV_7_TO_0_OCTET));      /* ���λ�ֽ� */
        usBufSize++;
    }


    if ( pApsTft->OP_ucTypeOfService )
    {
        /* component4�� TOS (IPv4) / Traffic Class (IPv6) and Mask */
        pSmTft->aucNewtft[usBufSize] = APS_TFT_TOS;
        usBufSize++;

        pSmTft->aucNewtft[usBufSize] = pApsTft->ucTypeOfService;        /*TOS*/
        usBufSize++;

        pSmTft->aucNewtft[usBufSize] = pApsTft->ucTypeOfServiceMask;
        usBufSize++;
    }

    /* pSmTft->Newtft[3]    = filter1�е�����4��components�ĳ��Ⱥ�
                            = TFT����������ֽ���- TFT����ǰ��4������ֽ���*/
    pSmTft->aucNewtft[APS_TFT_FILTER1_LENGTH_LOCATION]
        = (VOS_UINT8)(usBufSize - APS_TFT_FILTER1_OP_ID_PRE_LEN_AMOUNT);

    /* TFT����������ֽ��� =  TFT�����������һ���ֽڵ������� + 1 */
    pSmTft->ulTftLen = usBufSize;

    return;
}

/*****************************************************************************
 Prototype      : Aps_PackSmAddr()
 Description    : ��APS��ADDR�ṹ�����SM��Ҫ��ADDR�ṹ
 Input          : pucPdpTypeָ���PDP����,
                  ȡֵΪ:APS_ADDR_STATIC_IPV4, APS_ADDR_DYNAMIC_IPV4, APS_ADDR_PPP
                  pucAppAddrָ���PDP��ַ
 Output         : pSmAddrָ��Ľṹ��
 Return Value   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PackSmAddr  (
    VOS_UINT8                          *pucPdpType,
    VOS_UINT8                          *pucAppAddr,
    SM_TAF_PDP_ADDR_STRU               *pSmAddr
)
{
    /*STATIC IPV4*/
    if (APS_ADDR_STATIC_IPV4    == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = TAF_IPV4_ADDR_LEN + 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_IPV4;
        PS_MEM_CPY(         &(pSmAddr->aucPdpAddr[2]),
                            pucAppAddr,
                            TAF_IPV4_ADDR_LEN);
    }
    else if (APS_ADDR_DYNAMIC_IPV4 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_IPV4;
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (MN_APS_ADDR_IPV6 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = MN_APS_PDP_TYPE_NUM_IPV6;
    }
    else if (MN_APS_ADDR_IPV4V6 == *pucPdpType)
    {
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_IETF;
        pSmAddr->aucPdpAddr[1]  = MN_APS_PDP_TYPE_NUM_IPV4V6;
    }
#endif
    else
    {
        /*PPP*/
        pSmAddr->ulPdpAddrLen   = 2;
        pSmAddr->aucPdpAddr[0]  = APS_ADDR_ORGAN_ETSI;
        pSmAddr->aucPdpAddr[1]  = APS_PDP_TYPE_NUM_PPP;
    }

    return(TAF_APS_SUCC);

}

/*****************************************************************************
 Prototype      : Aps_PackSmApn()
 Description    : ��SM��QOS�ṹ�����APS��QOS�ṹ
 Input          : pucAppApnָ�������
 Output         : pSmApnָ��Ľṹ��
 Return Value   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_PackSmApn(  VOS_UINT8              *pucAppApn,
                            SM_TAF_APN_STRU      *pSmApn      )
{
    pSmApn->ulApnLen           = *pucAppApn;

    if (pSmApn->ulApnLen < APS_MAX_LENGTH_OF_APN )
    {
        PS_MEM_CPY(       pSmApn->aucApnAddr,
                          &(pucAppApn[1]),
                          pSmApn->ulApnLen   );
    }
    else
    {
        pSmApn->ulApnLen       = 0;
    }

    return;
}

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, end */


VOS_UINT32 MN_APS_QosValidOrNot_ForTrafficHandlingPriority(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 3]*/
    if(psQos->ucTraffHandlPrior > APS_3GPP_QOS_TRAFFHANDLPRIOR_TOP)
    {
        APS_WARN_LOG("psQos->ucTraffHandlPrior , Aps_QosValidOrNot()");
    }

    return TAF_APS_SUCC;
}/* end of Function */

#if(PS_UE_REL_VER >= PS_PTL_VER_R5)

VOS_UINT32 Aps_QosValidOrNot_ForSrcStatisticsDescriptor(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 15]*/
    if(psQos->ucSrcStatisticsDescriptor > APS_3GPP_QOS_SSD_TOP)
    {
        APS_WARN_LOG("psQos->ucSrcStatisticsDescriptor not valid , Aps_QosValidOrNot()");
        return(TAF_APS_FAIL);
    }

    return TAF_APS_SUCC;
}
VOS_UINT32 Aps_QosValidOrNot_ForSignallingIndication(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 1]*/
    if(psQos->ucSignallingIndication > APS_3GPP_QOS_SIG_IND_TOP)
    {
        APS_WARN_LOG("psQos->ucSignallingIndication not valid , Aps_QosValidOrNot()");
    }

    return TAF_APS_SUCC;
}
VOS_UINT32 Aps_QosValidOrNot_ForMaxBitRateForDownExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 250](R6�汾����Ϊ[0, 74], R7�汾����Ϊ[0, 250])*/
    if(psQos->ucMaxBitRateForDownExt > APS_3GPP_MAX_BITRATE_DOWN_TOP)
    {
        APS_WARN_LOG("psQos->ucMaxBitRateForDownExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucMaxBitRateForDownExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucMaxBitRateForDown))
        {
            APS_WARN_LOG("psQos->ucMaxBitRateForDown not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
VOS_UINT32 Aps_QosValidOrNot_ForGuarantBitRateForDownExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 250](R6�汾����Ϊ[0, 74], R7�汾����Ϊ[0, 250])*/
    if(psQos->ucGuarantBitRateForDownExt > APS_3GPP_GUARANT_BITRATE_DOWN_TOP)
    {
        APS_WARN_LOG("psQos->ucGuarantBitRateForDownExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucGuarantBitRateForDownExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucGuarantBitRateForDown))
        {
            APS_WARN_LOG("psQos->ucGuarantBitRateForDown not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
#endif


#if(PS_UE_REL_VER >= PS_PTL_VER_R7)
VOS_UINT32 Aps_QosValidOrNot_ForMaxBitRateForUpExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 250](R7�汾����Ϊ[0, 250])*/
    if(psQos->ucMaxBitRateForUpExt > APS_3GPP_MAX_BITRATE_UP_TOP)
    {
        APS_WARN_LOG("psQos->ucMaxBitRateForUpExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucMaxBitRateForUpExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucMaxBitRateForUp))
        {
            APS_WARN_LOG("psQos->ucMaxBitRateForUpExt not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
VOS_UINT32 Aps_QosValidOrNot_ForGuarantBitRateForUpExt(
    APS_PDP_QOS_STRU                    *psQos
)
{
    /* �����ڱ�����[0, 250](R7�汾����Ϊ[0, 250])*/
    if(psQos->ucGuarantBitRateForUpExt > APS_3GPP_GUARANT_BITRATE_UP_TOP)
    {
        APS_WARN_LOG("psQos->ucGuarantBitRateForUpExt not valid , Aps_QosValidOrNot()");
    }
    else
    {
        if ((psQos->ucGuarantBitRateForUpExt > 0) && (APS_3GPP_QOS_BIT_8640KBPS != psQos->ucGuarantBitRateForUp))
        {
            APS_WARN_LOG("psQos->ucGuarantBitRateForUpExt not valid , Aps_QosValidOrNot()");
        }
    }

    return TAF_APS_SUCC;
}
#endif
VOS_UINT32 Aps_QosValidOrNot(
    APS_PDP_QOS_STRU                   *psQos
)
{
    /* ucDelayClass�����ڱ�����[0, 4] */
    if ( (APS_3GPP_QOS_DELAYCLASS_BOT == psQos->ucDelayClass)
      || (psQos->ucDelayClass > APS_3GPP_QOS_DELAYCLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucDelayClass not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Delay class 4 (best effort) in
        this version */
        psQos->ucDelayClass = APS_3GPP_QOS_DELAYCLASS_4;
    }

    /* ucReliabClass�����ڱ�����[0, 5] */
    if ( (APS_3GPP_QOS_RELIABCLASS_BOT == psQos->ucReliabClass)
      || (psQos->ucReliabClass > APS_3GPP_QOS_RELIABCLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucReliabClass not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Unacknowledged GTP and LLC;
        Acknowledged RLC, Protected data in this version of the protocol.*/
        psQos->ucReliabClass = APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA;
    }

    /* ucPeakThrough�����ڱ�����[0, 9] */
    if ( (APS_3GPP_QOS_PEAKTHROUGH_BOT == psQos->ucPeakThrough)
      || (psQos->ucPeakThrough > APS_3GPP_QOS_PEAKTHROUGH_TOP) )
    {
        APS_NORM_LOG("psQos->ucPeakThrough not valid , Aps_QosValidOrNot()");

        /*All other values are interpreted as Up to 1 000 octet/s in this
        version of the protocol.*/
        psQos->ucPeakThrough = APS_3GPP_QOS_PEAKTHROUGH_1000_OCTPS;
    }

    /* ucPrecedenceClass�����ڱ�����[0, 3] */
    if ( (APS_3GPP_QOS_PRECEDENCECLASS_BOT == psQos->ucPrecedenceClass)
      || (psQos->ucPrecedenceClass > APS_3GPP_QOS_PRECEDENCECLASS_TOP) )
    {
        APS_NORM_LOG("psQos->ucPrecedenceClass not valid , Aps_QosValidOrNot()");

        /*�Զ�ת��Ϊ Normal priority*/
        psQos->ucPrecedenceClass = APS_3GPP_QOS_PRECEDENCECLASS_NORMPRI;
    }

    /* �����ڱ�����[0,18]*/
    if ( (APS_3GPP_QOS_MEANTHROUGH_BOT == psQos->ucMeanThrough)
      || ( (psQos->ucMeanThrough > APS_3GPP_QOS_MEANTHROUGH_TOP)
        && (APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT != psQos->ucMeanThrough) ) )
    {
        APS_NORM_LOG("psQos->ucMeanThrough not valid , Aps_QosValidOrNot()");

        /*�Զ�ת��Ϊ Best effort*/
        psQos->ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
    }

    /* �����ڱ�����[0, 4]*/
    if (psQos->ucTrafficClass > APS_3GPP_QOS_TRAFFICCLASS_TOP)
    {
        APS_WARN_LOG("psQos->ucTrafficClass not valid , Aps_QosValidOrNot()");
        /* The network shall map all other values not explicitly defined onto one
           of the values defined in this version of the protocol */
    }

    /*  �����ڱ�����[0,3]*/
    if (psQos->ucDeliverOrder > APS_3GPP_QOS_DELIVERORDER_TOP)
    {
        APS_WARN_LOG("psQos->ucDeliverOrder not valid , Aps_QosValidOrNot()");
    }

    /* �����ڱ�����[0, 3]*/
    if (psQos->ucDeliverOfErrSdu > APS_3GPP_QOS_DELIVER_ERRSDU_TOP)
    {
        APS_WARN_LOG("psQos->ucDeliverOfErrSdu not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* ucMaximSduSize�����ڱ�����[0, 153] */
    if (psQos->ucMaximSduSize > APS_3GPP_QOS_MAXSDUSIZE_TOP)
    {
        APS_WARN_LOG("psQos->ucMaximSduSize not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* �����ڱ�����[0, 9]*/
    if (psQos->ucResidualBer > APS_3GPP_QOS_RESIDUALBER_TOP)
    {
        APS_WARN_LOG("psQos->ucResidualBer not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* �����ڱ�����[0, 7]*/
    if (psQos->ucSduErrRatio > APS_3GPP_QOS_SDUERRRATIO_TOP)
    {
        APS_WARN_LOG("psQos->ucSduErrRatio not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* �����ڱ�����[0,0x3E]*/
    /* The Transfer delay value is ignored if the Traffic Class is interactive
       class or Background class. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (psQos->ucTransDelay > APS_3GPP_QOS_TRANSDELAY_TOP) )
    {
        APS_WARN_LOG("psQos->ucTransDelay not valid , Aps_QosValidOrNot()");
        return (TAF_APS_FAIL);
    }

    /* The Traffic handling priority value is ignored if the Traffic Class is
       Conversational class,Streaming class or Background class */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE == psQos->ucTrafficClass) )
    {
        if (TAF_APS_SUCC != MN_APS_QosValidOrNot_ForTrafficHandlingPriority(psQos))
        {
            return (TAF_APS_FAIL);
        }
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForSrcStatisticsDescriptor(psQos))
    {
        return(TAF_APS_FAIL);
    }

    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForSignallingIndication(psQos))
    {
        return(TAF_APS_FAIL);
    }

    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForMaxBitRateForDownExt(psQos))
    {
        return(TAF_APS_FAIL);
    }

    /* The Guaranteed bit rate for downlink value is ignored
       if the Traffic Class is Interactive class or Background class,
       or Maximum bit rate for uplink is set to 0 kbps. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (0xFF != psQos->ucMaxBitRateForDown) )
    {
        if (TAF_APS_SUCC != Aps_QosValidOrNot_ForGuarantBitRateForDownExt(psQos))
        {
            return TAF_APS_FAIL;
        }
    }
    #endif

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (TAF_APS_SUCC != Aps_QosValidOrNot_ForMaxBitRateForUpExt(psQos))
    {
        return(TAF_APS_FAIL);
    }

    /* The Guaranteed bit rate for uplink value is ignored
       if the Traffic Class is Interactive class or Background class,
       or Maximum bit rate for uplink is set to 0 kbps. */
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != psQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != psQos->ucTrafficClass)
      && (0xFF != psQos->ucMaxBitRateForUp) )
    {
        if (TAF_APS_SUCC != Aps_QosValidOrNot_ForGuarantBitRateForUpExt(psQos))
        {
            return TAF_APS_FAIL;
        }
    }
    #endif

    return(TAF_APS_SUCC);
}


/*****************************************************************************
 Prototype      : Aps_PackSmPco
 Description    : ���SM��Ҫ��PCO��Ϣ������LCP��AUTH��IPCP(DNS)
 Input          :
 Output         :
 Return Value   :
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_UINT32 Aps_PackSmPco(
    APS_PDP_ACT_REQ_ST                 *pActReq,
    SM_TAF_PROT_CFG_OPT_STRU           *pSmPco
)
{
    VOS_UINT8                          *pPcoCur;

    if ((VOS_NULL_PTR == pActReq) || (VOS_NULL_PTR == pSmPco))
    {
        APS_WARN_LOG("ERROR! The Input can not be NULL !");
        return VOS_ERR;
    }

    /*���PCO��IE�еĵ�3���ֽ�-- 1 0000 Configuration protocol(PPP for IP PDP type)
      0x80                    -- 1 0000 000    */
    pSmPco->aucProtCfgOpt[0]        = 0x80;

    pPcoCur                         = &pSmPco->aucProtCfgOpt[1];


    /*���LCP*/

    /*���AUTH*/
    pPcoCur                         = Aps_PackPcoAuth(pActReq, pPcoCur);

    /*���IPCP*/
#if (FEATURE_ON == FEATURE_IPV6)
    if (MN_APS_ADDR_IPV6 != pActReq->ucPdpType)
    {
        pPcoCur = Aps_PackPcoIpcp(pActReq, pPcoCur);
        if (VOS_NULL_PTR == pPcoCur)
        {
            MN_ERR_LOG("Aps_PackSmPco: Fill IPCP parameter failed!");
            return VOS_ERR;
        }
    }

    if ( (MN_APS_ADDR_IPV6   == pActReq->ucPdpType)
      || (MN_APS_ADDR_IPV4V6 == pActReq->ucPdpType) )
    {
        pPcoCur = MN_APS_FillPcoIpV6DnsPara(pPcoCur);
        if (VOS_NULL_PTR == pPcoCur)
        {
            MN_ERR_LOG("Aps_PackSmPco: Fill IPV6 DNS parameter failed!");
            return VOS_ERR;
        }
    }
#else
    pPcoCur = Aps_PackPcoIpcp(pActReq, pPcoCur);
    if (VOS_NULL_PTR == pPcoCur)
    {
        MN_ERR_LOG("Aps_PackSmPco: Fill IPCP parameter failed!");
        return VOS_ERR;
    }
#endif

    /*�����д pSmPco->ulCnt */
    pSmPco->ulPcoLen = (VOS_UINT32)(pPcoCur - pSmPco->aucProtCfgOpt);

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Aps_PackPcoAuth
 Description    : ���SM��Ҫ��PCO��Ϣ�е�AUTH
 Input          : ApsAuthPara
                  pPcoAuthStart, ����AUTH��Ϣ�ĵ�һ���ֽڵĵ�ַ
 Output         :
 Return Value   : ����AUTH��Ϣ�����һ���ֽڵĵ�ַ+1, ����������һ��IE�ĵ�һ��
                  �ֽ�
 Data Accessed  :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_UINT8  *Aps_PackPcoAuth(            APS_PDP_ACT_REQ_ST     *pActReq,
                                        VOS_UINT8              *pPcoAuthBegin)
{
    VOS_UINT8                          *pAuthCurLoc;
    VOS_UINT8                          *pProPapCntLenLoc;
    VOS_UINT8                          *pInPapLenLoc;
    VOS_UINT8                           ucPapLen;
    VOS_UINT8                           ucStrLen;
    VOS_UINT8                           i;

    TAF_PDP_PCO_AUTH_STRU              *pApsAuthPara;

    if (VOS_TRUE != pActReq->OP_AUTH)
    {
        return pPcoAuthBegin;
    }

    pApsAuthPara                        = &(pActReq->PdpAuth);

    pAuthCurLoc                         = pPcoAuthBegin;

    if ( TAF_PCO_AUTH_PAP == pApsAuthPara->AuthType )
    {
        /*lint -e961*/
        /*PAP��֤��ʽ*/
        /* Password Authentication Protocol */
        *pAuthCurLoc++ = 0xC0;
        *pAuthCurLoc++ = 0x23;

        /* ��ʱ���� PROTOCAL ID1�ĳ���, ��ס������ַ, ��������������Ϣ������*/
        pProPapCntLenLoc                    = pAuthCurLoc++;

        /* code (Authenticate-Request) */
        *pAuthCurLoc++ = 0x01;

        /* Identifier */
        *pAuthCurLoc++ = 0x00;

        /* ��ʱ����PAP���ݵ�Length, ռ2���ֽ�, ��ס������ַ, ��������������Ϣ������ */
        pInPapLenLoc                        = pAuthCurLoc++;
        pAuthCurLoc++;

        /*���������AUTH��Ϣ������д������û�����������Ϣ*/

        /* Peer-ID Length */
        *pAuthCurLoc++                  = pApsAuthPara->AuthContent.stPap.aucUserName[0];

        /* Peer-Id  */
        ucStrLen                        = pApsAuthPara->AuthContent.stPap.aucUserName[0];
        if ( ucStrLen > TAF_MAX_USERNAME_LEN)
        {
            ucStrLen                    = TAF_MAX_USERNAME_LEN;
        }
        if ( 0 != ucStrLen)
        {
            for(i = 1; i <= ucStrLen; i++)
            {
                *pAuthCurLoc++          = pApsAuthPara->AuthContent.stPap.aucUserName[i];
            }
        }

        /* Passwd-Length  */
        *pAuthCurLoc++                  = pApsAuthPara->AuthContent.stPap.aucPassword[0];

        /* Password-ID  */
        ucStrLen                        = pApsAuthPara->AuthContent.stPap.aucPassword[0];
        if ( ucStrLen > TAF_MAX_PASSCODE_LEN)
        {
            ucStrLen                    = TAF_MAX_PASSCODE_LEN;
        }
        if ( 0 != ucStrLen)
        {
            for(i = 1; i <= ucStrLen; i++)
            {
                *pAuthCurLoc++          = pApsAuthPara->AuthContent.stPap.aucPassword[i];
            }
        }

        /* PAP���ݵ�Length */
        ucPapLen                            = (VOS_UINT8)((pAuthCurLoc
                                              - pPcoAuthBegin)
                                              - APS_PAP_PIDOCTS_AND_LENOCT_LEN);
        /* PROTOCAL ID1�ĳ��� */
       *pProPapCntLenLoc                    = ucPapLen;

        /* PAP���ݵ�Length, ռ2���ֽ� */
       *pInPapLenLoc++                      = 0;
       *pInPapLenLoc                        = ucPapLen;
    }
    else if ( TAF_PCO_AUTH_CHAP == pApsAuthPara->AuthType )
    {
        /*CHAP��֤��ʽ*/
        /* Challenge ���� */
        *pAuthCurLoc++ = 0xC2;
        *pAuthCurLoc++ = 0x23;

        /*Length of Challenge contents: ���ȹ̶�*/
        *pAuthCurLoc++ = pApsAuthPara->AuthContent.stChap.aucChallenge[0];

        /*Challenge contents*/
        PS_MEM_CPY(pAuthCurLoc,
                   &pApsAuthPara->AuthContent.stChap.aucChallenge[1],
                   pApsAuthPara->AuthContent.stChap.aucChallenge[0]);

        pAuthCurLoc += pApsAuthPara->AuthContent.stChap.aucChallenge[0];

        /* Response ���� */
        *pAuthCurLoc++ = 0xC2;
        *pAuthCurLoc++ = 0x23;

        /*Length of Response contents */
        /*Response contents�����̶�����Ϊ21��ͷ+user�����user>106����ΪAUTH��Ч*/
        if ((pApsAuthPara->AuthContent.stChap.aucResponse[0] - TAF_PCO_AUTH_CHAP_RESPONSE_HEAD_LEN)
            > TAF_PCO_AUTH_CHAP_RESPONSE_CONTENT_LEN)
        {
            return pPcoAuthBegin;
        }

        *pAuthCurLoc++ = pApsAuthPara->AuthContent.stChap.aucResponse[0];
        /*lint +e961*/

        /*Challenge contents*/
        PS_MEM_CPY(pAuthCurLoc,
                   &pApsAuthPara->AuthContent.stChap.aucResponse[1],
                   pApsAuthPara->AuthContent.stChap.aucResponse[0]);

        pAuthCurLoc += pApsAuthPara->AuthContent.stChap.aucResponse[0];

    }
    else
    {
        /*������֤��ֱ�ӷ���*/
    }

    return  pAuthCurLoc;
}
VOS_UINT8  *Aps_PackPcoIpcp(            APS_PDP_ACT_REQ_ST     *pActReq,
                                        VOS_UINT8              *pPcoIpcpBegin)
{
    VOS_UINT8                          *pIpcpCurLoc;
    VOS_UINT8                          *pProIpcpCntLenLoc;
    VOS_UINT8                          *pInIpcpLenLoc;
    VOS_UINT8                           ucIpcpLen;


    pIpcpCurLoc                         = pPcoIpcpBegin;

    /*lint -e961*/
    /* IPCP Protocol */
    *pIpcpCurLoc++                      = 0x80;
    *pIpcpCurLoc++                      = 0x21;

    /* ��ʱ���� PROTOCAL ID1�ĳ���, ��ס������ַ, ��������������Ϣ������*/
    pProIpcpCntLenLoc                   = pIpcpCurLoc++;

    /* code (Authenticate-Request) */
    *pIpcpCurLoc++                      = 0x01;

    /* Identifier */
    *pIpcpCurLoc++                      = 0x00;

    /* ��ʱ����IPCP���ݵ�Length, ռ2���ֽ�, ��ס������ַ, ��������������Ϣ
    ������ */
    pInIpcpLenLoc                       = pIpcpCurLoc++;
    pIpcpCurLoc++;


    /*��DNS*/
    *pIpcpCurLoc++                      = 0x81;             /*PriDns*/
    *pIpcpCurLoc++                      = 0x06;             /*����*/

    if ( (pActReq->OP_DNS) && (pActReq->PdpDns.bitOpPrimDnsAddr) )
    {
        PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpDns.aucPrimDnsAddr, TAF_IPV4_ADDR_LEN);
        pIpcpCurLoc                    += 4;                /*DNSΪ4���ֽ�*/
    }
    else
    {
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
        *pIpcpCurLoc++                  = 0x00;             /*PriDns*/
    }

    if (WINS_CONFIG_ENABLE == g_ApsWins)
    {
        /*��NBNS*/
        if ( (pActReq->OP_NBNS) && (pActReq->PdpNbns.bitOpPrimNbnsAddr) )
        {
            *pIpcpCurLoc++              = APS_PPP_PRI_NBNS_ID;     /*PriNbns*/
            *pIpcpCurLoc++              = 0x06;             /*����*/

            PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpNbns.aucPrimNbnsAddr, TAF_IPV4_ADDR_LEN);
            pIpcpCurLoc                    += 4;                /*NBNSΪ4���ֽ�*/
        }
    }

    /*��DNS*/
    *pIpcpCurLoc++                      = 0x83;             /*SecDns*/
    *pIpcpCurLoc++                      = 0x06;             /*����*/

    if ( (pActReq->OP_DNS) && (pActReq->PdpDns.bitOpSecDnsAddr) )
    {
        PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpDns.aucSecDnsAddr, TAF_IPV4_ADDR_LEN);
        pIpcpCurLoc                    += 4;                /*DNSΪ4���ֽ�*/
    }
    else
    {
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
        *pIpcpCurLoc++                  = 0x00;             /*SecDns*/
    }


    if (WINS_CONFIG_ENABLE == g_ApsWins)
    {
        /*��NBNS*/
        if ( (pActReq->OP_NBNS) && (pActReq->PdpNbns.bitOpSecNbnsAddr) )
        {
            *pIpcpCurLoc++              = APS_PPP_SEC_NBNS_ID;      /*SecNbns*/
            *pIpcpCurLoc++              = 0x06;                     /*����*/

            PS_MEM_CPY(pIpcpCurLoc, pActReq->PdpNbns.aucSecNbnsAddr, TAF_IPV4_ADDR_LEN);
            pIpcpCurLoc                    += 4;                    /*NBNSΪ4���ֽ�*/
        }
    }

    ucIpcpLen                           = (VOS_UINT8)((pIpcpCurLoc
                                          - pPcoIpcpBegin)
                                          - APS_PAP_PIDOCTS_AND_LENOCT_LEN);
    /* PROTOCAL ID1�ĳ��� */
    *pProIpcpCntLenLoc                  = ucIpcpLen;

    /* PAP���ݵ�Length, ռ2���ֽ� */
    *pInIpcpLenLoc++                    = 0;
    *pInIpcpLenLoc                      = ucIpcpLen;
    /*lint +e961*/
    return  pIpcpCurLoc;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT8* MN_APS_FillPcoIpV6DnsPara(
    VOS_UINT8                          *pucPcoPkt
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIPv6DnsAddrNum;

    /* Ŀǰ֧�ֻ�ȡ��DNS Server IPv6 Address����Ϊ2 */
    ucIPv6DnsAddrNum = 2;

    for (i = 0; i < ucIPv6DnsAddrNum; i++)
    {
        /*--------------------------------------------------
           ��дProtocol identifier (2 octets)
           0003H (DNS Server IPV6 Address Request)
        --------------------------------------------------*/
        /*lint -e961*/
        *pucPcoPkt++ = 0x00;
        *pucPcoPkt++ = 0x03;

        /*----------------------------------------------------------------------
           ��дLength of the protocol identifier contents of the unit (1 octet)
        ----------------------------------------------------------------------*/
        *pucPcoPkt++ = 0;
        /*lint +e961*/
    }

    return pucPcoPkt;

}
#endif

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
