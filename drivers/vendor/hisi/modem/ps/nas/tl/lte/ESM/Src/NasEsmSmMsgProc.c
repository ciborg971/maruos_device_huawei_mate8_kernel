



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmSmMsgProc.h"
#include    "SmEsmInterface.h"
#include    "NasEsmNwMsgDecode.h"
#include    "NasEsmNwMsgBearerResModProc.h"
#include    "NasEsmRabmMsgProc.h"
#include    "NasEsmOmMsgProc.h"
#include    "NasEsmEmmMsgProc.h"

#include    "NasEsmEhsmMsgProc.h"



/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMSMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMSMMSGPROC_C
/*lint +e767*/


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_ESM_SmMsgDistr
 Description    : ESMģ��SM��Ϣ�ַ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong00150010      2011-04-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SmMsgDistr
(
    VOS_VOID                           *pRcvMsg
)
{
    PS_MSG_HEADER_STRU         *pSmMsg = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SmMsgDistr_ENUM, LNAS_ENTRY);

    pSmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pSmMsg->ulMsgName)
    {
        /*����յ�����ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ*/
        case ID_SM_ESM_PDP_CONTEXT_INFO_IND:

            NAS_ESM_RcvPdpContextInfoInd( (SM_ESM_PDP_CONTEXT_INFO_IND_STRU *)pRcvMsg );
            break;

        default:
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_SmMsgDistr:WARNING:SM->ESM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SmMsgDistr_ENUM, 1);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_RcvPdpContextInfoInd
 Description     : ESMģ���յ�ID_SM_ESM_PDP_CONTEXT_INFO_IND������
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_RcvPdpContextInfoInd
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvPdpContextInfoInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvPdpContextInfoInd_ENUM, LNAS_ENTRY);

    if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_RcvPdpContextInfoInd:NORM: received abnormal Pdp context Ind !");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvPdpContextInfoInd_ENUM, ESM_CID_ERROR);
    }

    switch (pstRcvMsg->enPdpOption)
    {
        case SM_ESM_PDP_OPT_ACTIVATE:
            NAS_ESM_ProcSmPdpActivate(pstRcvMsg);
            break;
        case SM_ESM_PDP_OPT_MODIFY:
            NAS_ESM_ProcSmPdpModify(pstRcvMsg);
            break;
        case SM_ESM_PDP_OPT_DEACTIVATE:
            NAS_ESM_ProcSmPdpDeactivate(pstRcvMsg);
            break;
        default:
            NAS_ESM_WARN_LOG("NAS_ESM_RcvPdpContextInfoInd:illegal enPdpOption!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvPdpContextInfoInd_ENUM, ESM_PDN_TYPE_ERROR);
            break;
    }
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_MapPdpQos2EpsQos
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstEpsQos,
    const SM_ESM_PDP_QOS_STRU          *pstPdpQos
)
{
    VOS_UINT32                          ulRate = NAS_ESM_NULL;

    /* ӳ��QCI */
    switch (pstPdpQos->ucTrafficClass)
    {
        case NAS_ESM_TRAFFIC_CLASS_CONVENTIONAL:
            NAS_ESM_MapTraffClassConventional2EpsQci(pstEpsQos, pstPdpQos);
            break;
        case NAS_ESM_TRAFFIC_CLASS_STREAMING:
            pstEpsQos->ucNwQCI = NAS_ESM_QCI_TYPE_QCI4_GBR;
            pstEpsQos->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI4_GBR;
            break;
        case NAS_ESM_TRAFFIC_CLASS_INTERACTIVE:
            NAS_ESM_MapTraffClassInteractive2EpsQci(pstEpsQos, pstPdpQos);
            break;
        default:
            pstEpsQos->ucNwQCI = NAS_ESM_QCI_TYPE_QCI9_NONGBR;
            pstEpsQos->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI9_NONGBR;
            break;
    }

    /* �����NON-GBR��������ӳ������ */
    if (PS_TRUE != NAS_ESM_IsGbrBearer(pstEpsQos->ucNwQCI))
    {
        return ;
    }

    /* ת��DL MAX RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucMaxBitRateForDown;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForDownExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForDownExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulDLMaxRate);

    /* ת��UL MAX RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucMaxBitRateForUp;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForUpExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucMaxBitRateForUpExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulULMaxRate);

    /* ת��DL GUARANTEED RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucGuarantBitRateForDown;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForDownExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForDownExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulDLGMaxRate);

    /* ת��UL GUARANTEED RATE */
    ulRate = (VOS_UINT16)pstPdpQos->ucGuarantBitRateForUp;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForUpExt) << NAS_ESM_MOVEMENT_8_BITS;
    ulRate |= ((VOS_UINT16)pstPdpQos->ucGuarantBitRateForUpExt_2) << NAS_ESM_MOVEMENT_16_BITS;
    NAS_ESM_EpsQosRateDecodeTo32(ulRate, &pstEpsQos->stQosInfo.ulULGMaxRate);
}

/*****************************************************************************
 Function Name   : NAS_ESM_MapPdpQos2ApnAmbr
 Description     : ��PDP QOSӳ��ΪAPN-AMBR
 Input           : SM_ESM_PDP_QOS_STRU                *pstPdpQos
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_MapPdpQos2ApnAmbr
(
    NAS_ESM_CONTEXT_APN_AMBR_STRU      *pstApnAmbrInfo,
    const SM_ESM_PDP_QOS_STRU          *pstPdpQos
)
{
    pstApnAmbrInfo->ucDLApnAmbr = pstPdpQos->ucMaxBitRateForDown;
    pstApnAmbrInfo->ucULApnAmbr = pstPdpQos->ucMaxBitRateForUp;

    if (NAS_ESM_NULL != pstPdpQos->ucMaxBitRateForDownExt)
    {
        pstApnAmbrInfo->bitOpDLApnAmbrExt = NAS_ESM_OP_TRUE;
        pstApnAmbrInfo->ucDLApnAmbrExt = pstPdpQos->ucMaxBitRateForDownExt;
    }

    if (NAS_ESM_NULL != pstPdpQos->ucMaxBitRateForUpExt)
    {
        pstApnAmbrInfo->bitOpULApnAmbrExt = NAS_ESM_OP_TRUE;
        pstApnAmbrInfo->ucULApnAmbrExt = pstPdpQos->ucMaxBitRateForUpExt;
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpTftInfo
 Description     : ����PDP�����TFT��Ϣ
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SavePdpTftInfo
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstRcvMsg
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;
    const SM_ESM_CID_PF_STRU           *pstCidPf        = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_TFT_STRU           *pstContTft      = VOS_NULL_PTR;

    /* �洢SDF�ĳ��غ���Ϣ */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
        pstSdfCntxtInfo->ulEpsbId = pstRcvMsg->ulNsapi;
        pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;
    }

    if (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpTft)
    {
        return ;
    }

    /* �洢PF��Ϣ */
    for( ulCnt = NAS_ESM_NULL; ulCnt < pstRcvMsg->stTft.ulPfNum; ulCnt++ )
    {
        pstCidPf        = &pstRcvMsg->stTft.astCidPf[ulCnt];
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstCidPf->ulCid);

        /* �洢PF��Ϣ */
        pstContTft = &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum];
        NAS_ESM_MEM_CPY(pstContTft, &pstCidPf->stPf, sizeof(NAS_ESM_CONTEXT_TFT_STRU));
        pstSdfCntxtInfo->ulSdfPfNum++;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpTftInfo
 Description     : ����PDP�����PCO IPV4��
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SavePcoIpv4Item
(
    NAS_ESM_CONTEXT_PCO_STRU           *pstPcoInfo,
    const SM_ESM_PCO_IPV4_ITEM_STRU    *pstPcoIpv4Item
)
{
    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriDns)
    {
        pstPcoInfo->ucIpv4DnsSerNum = 1;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4DnsServer[0].aucIpV4Addr,
                            pstPcoIpv4Item->aucPriDns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecDns)
    {
        pstPcoInfo->ucIpv4DnsSerNum = 2;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4DnsServer[1].aucIpV4Addr,
                            pstPcoIpv4Item->aucSecDns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriPcscf)
    {
        pstPcoInfo->ucIpv4PcscfNum = 1;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4Pcscf[0].aucIpV4Addr,
                            pstPcoIpv4Item->aucPriPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecPcscf)
    {
        pstPcoInfo->ucIpv4PcscfNum = 2;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4Pcscf[1].aucIpV4Addr,
                            pstPcoIpv4Item->aucSecPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpPriNbns)
    {
        pstPcoInfo->ucIpv4NbnsNum = 1;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4Nbns[0].aucIpV4Addr,
                            pstPcoIpv4Item->aucPriNbns,
                            SM_ESM_IPV4_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv4Item->bitOpSecNbns)
    {
        pstPcoInfo->ucIpv4NbnsNum = 2;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv4Nbns[1].aucIpV4Addr,
                            pstPcoIpv4Item->aucSecPcscf,
                            SM_ESM_IPV4_ADDR_LEN);
    }
}


VOS_VOID NAS_ESM_SavePcoIpv6Item
(
    NAS_ESM_CONTEXT_PCO_STRU           *pstPcoInfo,
    const SM_ESM_PCO_IPV6_ITEM_STRU    *pstPcoIpv6Item
)
{
    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpPriDns)
    {
        pstPcoInfo->ucIpv6DnsSerNum = 1;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv6DnsServer[0].aucIpV6Addr,
                            pstPcoIpv6Item->aucPriDns,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpSecDns)
    {
        pstPcoInfo->ucIpv6DnsSerNum = 2;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv6DnsServer[1].aucIpV6Addr,
                            pstPcoIpv6Item->aucSecDns,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpPriPcscf)
    {
        pstPcoInfo->ucIpv6PcscfNum = 1;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv6Pcscf[0].aucIpV6Addr,
                            pstPcoIpv6Item->aucPriPcscf,
                            SM_ESM_IPV6_ADDR_LEN);
    }

    if (NAS_ESM_OP_TRUE == pstPcoIpv6Item->bitOpSecPcscf)
    {
        pstPcoInfo->ucIpv6PcscfNum = 2;
        NAS_ESM_MEM_CPY(    pstPcoInfo->astIpv6Pcscf[1].aucIpV6Addr,
                            pstPcoIpv6Item->aucSecPcscf,
                            SM_ESM_IPV6_ADDR_LEN);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveSdfQos
 Description     : ����PDP�����SDF QOS��Ϣ
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveSdfQos
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;

    /* �洢SDF��QOS��Ϣ */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
        NAS_ESM_MEM_CPY(    &pstSdfCntxtInfo->stSdfQosInfo,
                            pstEpsQos,
                            sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_SavePdpActivateInfo
 Description     : ����PDP�������������Ϣ
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SavePdpActivateInfo
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    VOS_UINT32                          ulCurPdnNum      = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1    = {0};
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2    = {0};

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_MEM_SET(    pstEpsbCntxtInfo,
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_EPSB_CNTXT_INFO_STRU));

    pstEpsbCntxtInfo->ulEpsbId              = ulEpsbId;
    pstEpsbCntxtInfo->bitOpCId              = NAS_ESM_OP_TRUE;
    pstEpsbCntxtInfo->ulBitCId              = pstRcvMsg->ulBitCid;
    pstEpsbCntxtInfo->bitOpTransId          = NAS_ESM_OP_TRUE;
    NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stTransId,
                        &pstRcvMsg->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /* ӳ��PDP QOSΪ����QOS */
    pstEpsbCntxtInfo->bitOpEpsQos           = NAS_ESM_OP_TRUE;
    NAS_ESM_MapPdpQos2EpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, &pstRcvMsg->stPdpQos);

    /* �洢PDP QOS */
    pstEpsbCntxtInfo->bitOpNegQos = NAS_ESM_OP_TRUE;
    NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stCntxtQosInfo,
                        &pstRcvMsg->stPdpQos,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /* �洢SDF QOS */
    NAS_ESM_SaveSdfQos(pstRcvMsg, &pstEpsbCntxtInfo->stEpsQoSInfo);

    /* �洢PF��Ϣ */
    NAS_ESM_SavePdpTftInfo(pstRcvMsg);

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* ר�г��� */
        pstEpsbCntxtInfo->ulLinkedEpsbId        = pstRcvMsg->ulLinkedNsapi;

        /*ת��״̬*/
        NAS_ESM_SetBearCntxtState(ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
        NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_DEDICATED);
    }
    else
    {
        /* ȱʡ���� */
        /*�洢PDN��Ϣ������PDN��ʶλ*/
        pstEpsbCntxtInfo->bitOpPdnAddr = NAS_ESM_OP_TRUE;
        NAS_ESM_SavePdnAddr(&pstEpsbCntxtInfo->stPdnAddrInfo, &pstRcvMsg->stPdpAddr);

        if ((NAS_ESM_PDN_IPV4 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType)
            || (NAS_ESM_PDN_IPV4_IPV6 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType))
        {
            /* �������������Ĭ������ */
            pstEpsbCntxtInfo->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;

            pstEpsbCntxtInfo->stSubnetMask.ucIpType = NAS_ESM_PDN_IPV4;
            NAS_ESM_DHCPGetIPv4Mask(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                    pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr);

            pstEpsbCntxtInfo->stGateWayAddrInfo.ucIpType = NAS_ESM_PDN_IPV4;
            NAS_ESM_DHCPGetIPv4GateWay( pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr);
        }

        /*����APN��ʶλ*/
        NAS_ESM_SaveApnAddr(&stTmpApnInfo1, &pstRcvMsg->stApn);

        /* ��APN��ʽ��δ����תΪ���� */
        ulRslt = NAS_ESM_ApnReverseTransformation(  &stTmpApnInfo2,
                                                    &stTmpApnInfo1);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_ERR_LOG("NAS_ESM_SavePdpActivateInfo:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_SavePdpActivateInfo_ENUM, ESM_APN_ERROR);
            pstEpsbCntxtInfo->bitOpApn = NAS_ESM_OP_FALSE;
        }
        else
        {
            pstEpsbCntxtInfo->bitOpApn = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stApnInfo,
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /* �洢APN-AMBR */
        pstEpsbCntxtInfo->bitOpApnAmbr = NAS_ESM_OP_TRUE;
        NAS_ESM_MapPdpQos2ApnAmbr(&pstEpsbCntxtInfo->stApnAmbrInfo, &pstRcvMsg->stPdpQos);

        /* �洢PCO IPV4�� */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv4Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv4Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv4Item);
        }

        /* �洢PCO IPV6�� */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv6Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv6Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv6Item);
        }

        /* lihong00150010 ims begin */
        /* �洢IM CN SIGNAL FLAG��ʶ */
        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpImCnSigalFlag))
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.enImsCnSignalFlag = pstRcvMsg->enImCnSignalFlag;
        }
        /* lihong00150010 ims end */

        /*��ǰPDN����������1��*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum()+1;

        /*���浱ǰPDN������*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);

        /*ת��״̬*/
        NAS_ESM_SetBearCntxtState(ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);

        /* lihong00150010 ims begin */
        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpEmcInd)
            && (SM_ESM_PDP_FOR_EMC == pstRcvMsg->enEmergencyInd))
        {
            NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_EMERGENCY);
        }
        else
        {
            NAS_ESM_SetBearCntxtType(ulEpsbId, NAS_ESM_BEARER_TYPE_DEFAULT);
        }
        /* lihong00150010 ims end */
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateSmSecPdpActivate
 Description     : ��֤SM�����Ĵ�PDP������Ϣ�ĺϷ���
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-19      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateSmSecPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    const SM_ESM_CID_PF_STRU           *pstCidPf        = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo= VOS_NULL_PTR;

    /* ר�г��ر������TFT��PDP QOS */
    if ((NAS_ESM_OP_TRUE != pstRcvMsg->bitOpTft) || (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpPdpQos))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:no tft or no qos!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstRcvMsg->ulLinkedNsapi);

    if ((NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
        || (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType)))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:linkEpsbId is illegal!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    /* ��֤TFT��Ϣ�е�CID��ulBitCid�ж����� */
    for( ulCnt = NAS_ESM_NULL; ulCnt < pstRcvMsg->stTft.ulPfNum; ulCnt++ )
    {
        pstCidPf        = &pstRcvMsg->stTft.astCidPf[ulCnt];

        if(NAS_ESM_OP_FALSE == (((pstRcvMsg->ulBitCid) >> (pstCidPf->ulCid)) & NAS_ESM_OP_TRUE))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmSecPdpActivate:TFT CID is not exist in BitCid!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmSecPdpActivate_ENUM, 3);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ValidateSmPdpActivate
 Description     : ��֤SM������PDP������Ϣ�ĺϷ���
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-04-29      Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_ValidateSmPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* ר�г��� */
        return NAS_ESM_ValidateSmSecPdpActivate(pstRcvMsg);
    }

    /* ȱʡ���� */
    if ((NAS_ESM_OP_TRUE != pstRcvMsg->bitOpPdpQos) || (NAS_ESM_OP_TRUE != pstRcvMsg->bitOpApn))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpActivate:no apn or no qos!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpActivate_ENUM, ESM_APN_ERROR);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcSmPdpActivate
 Description     : ESM����SM PDP����
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSmPdpActivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;

    if (NAS_ESM_L_MODE_STATUS_NORMAL == NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpActivate:ESM is not suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpActivate_ENUM, 1);
        return ;
    }
    /* ��֤SM������PDP������Ϣ */
    if (NAS_ESM_FAILURE == NAS_ESM_ValidateSmPdpActivate(pstRcvMsg))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcSmPdpActivate: Msg is Validated and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSmPdpActivate_ENUM, 2);
        return;
    }

    /* ��������Ѿ�����ȱ���ȥ���� */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpActivate : release already active bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpActivate_ENUM, 3);
        NAS_ESM_ProcSmPdpDeactivate(pstRcvMsg);
    }

    /* ����PDP�������������Ϣ */
    NAS_ESM_SavePdpActivateInfo(pstRcvMsg);

    /*�ؼ��¼��ϱ�*/
    NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_SETUP(ulEpsbId));

    /*��EMM����ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*��RABM����ID_ESM_ERABM_ACT_IND*/
    NAS_ESM_SndEsmRabmActIndMsg(ulEpsbId);

    NAS_ESM_PrintEpsbInfo(ulEpsbId);
}


VOS_UINT32  NAS_ESM_ValidateSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstRcvMsg->ulNsapi);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpModify:pdp is not active!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpModify_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* ר�г���, ɾ��TFT */
        if ((NAS_ESM_OP_FALSE == pstRcvMsg->bitOpTft) && (NAS_ESM_NULL == pstRcvMsg->stTft.ulPfNum))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ValidateSmPdpModify:TFT of dedicated bearer cannot be delete!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ValidateSmPdpModify_ENUM, 2);
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}
VOS_VOID  NAS_ESM_ModifySdfQos
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU  *pstRcvMsg,
    const NAS_ESM_CONTEXT_LTE_QOS_STRU      *pstEpsQos
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stQosTemp = {{0}};
    VOS_UINT8                           ucCidNum  = 0;

    /* ��ó��ع�����CID��Ŀ */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }
        ucCidNum++;
    }

    if (0 == ucCidNum)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ModifySdfQos:Cid num cannot be zero!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ModifySdfQos_ENUM, 1);
        return;
    }

    NAS_ESM_MEM_CPY( &stQosTemp,
                     pstEpsQos,
                     sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));


    /* ������Qos ����ƽ������������CID��Qos�� */
    stQosTemp.stQosInfo.ulDLGMaxRate /= ucCidNum;
    stQosTemp.stQosInfo.ulULGMaxRate /= ucCidNum;
    stQosTemp.stQosInfo.ulDLMaxRate  /= ucCidNum;
    stQosTemp.stQosInfo.ulULMaxRate  /= ucCidNum;

    /* �洢SDF��QOS��Ϣ */
    for ( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((pstRcvMsg->ulBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }
        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
        NAS_ESM_MEM_CPY( &pstSdfCntxtInfo->stSdfQosInfo,
                         &stQosTemp,
                         sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }

}
VOS_VOID  NAS_ESM_ProcSmPdpModify
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1    = {0};
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2    = {0};
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;

    /* ��֤SM������PDP�޸���Ϣ */
    if (NAS_ESM_FAILURE == NAS_ESM_ValidateSmPdpModify(pstRcvMsg))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_ProcSmPdpModify: Msg is invalid and return!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcSmPdpModify_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /* ����stTransId��stPdnAddr��ulBitCid��ulLinkedNsapi������ */
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_MEM_CPY( &pstEpsbCntxtInfo->stTransId,
                     &pstRcvMsg->stTransId,
                     sizeof(SM_ESM_TRANSACTION_ID_STRU));

    NAS_ESM_MEM_CPY( &pstEpsbCntxtInfo->stPdnAddrInfo,
                     &pstRcvMsg->stPdpAddr,
                     sizeof(SM_ESM_PDP_ADDR_STRU));

    /* �������ԭ�й���CID��SDF��̬��Ϣ */
    for( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        /*������ȡ����CID��¼*/
        if(NAS_ESM_OP_TRUE ==((pstEpsbCntxtInfo->ulBitCId >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            /* ���SDF������ */
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);
            NAS_ESM_MEM_SET(pstSdfCntxtInfo, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
        }
    }
    /*leili modify for isr begin*/
    /*CID��ͬ�ҳ���������ר�о͸�EMM���ͳ����޸�������Ϣ*/
    if ((pstEpsbCntxtInfo->ulBitCId == pstRcvMsg->ulBitCid)||
        (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        NAS_ESM_SndEsmEmmBearerModifyReq(ulEpsbId);
    }
    /*leili modify for isr end*/
    pstEpsbCntxtInfo->ulBitCId = pstRcvMsg->ulBitCid;

    pstEpsbCntxtInfo->ulLinkedEpsbId = pstRcvMsg->ulLinkedNsapi;

    /* �޸�TFT��Ϣ */
    NAS_ESM_SavePdpTftInfo(pstRcvMsg);

    /* ӳ��PDP QOSΪ����QOS */
    pstEpsbCntxtInfo->bitOpEpsQos = pstRcvMsg->bitOpPdpQos;
    NAS_ESM_MapPdpQos2EpsQos(&pstEpsbCntxtInfo->stEpsQoSInfo, &pstRcvMsg->stPdpQos);

    /* �洢PDP QOS */
    pstEpsbCntxtInfo->bitOpNegQos = pstRcvMsg->bitOpPdpQos;
    NAS_ESM_MEM_CPY( &pstEpsbCntxtInfo->stCntxtQosInfo,
                     &pstRcvMsg->stPdpQos,
                     sizeof(NAS_ESM_CONTEXT_QOS_STRU));
    /* �޸�SDF QOS */
    NAS_ESM_ModifySdfQos(pstRcvMsg, &pstEpsbCntxtInfo->stEpsQoSInfo);

    /* ȱʡ�����޸� */
    if (NAS_ESM_OP_FALSE == pstRcvMsg->bitOpLinkedNsapi)
    {
        /* �洢APN-AMBR */
        pstEpsbCntxtInfo->bitOpApnAmbr = pstRcvMsg->bitOpPdpQos;
        NAS_ESM_MapPdpQos2ApnAmbr(&pstEpsbCntxtInfo->stApnAmbrInfo, &pstRcvMsg->stPdpQos);

        /* ����APN*/
        pstEpsbCntxtInfo->bitOpApn = pstRcvMsg->bitOpApn;
        NAS_ESM_SaveApnAddr(&stTmpApnInfo1, &pstRcvMsg->stApn);

        /* ��APN��ʽ��δ����תΪ���� */
        ulRslt = NAS_ESM_ApnReverseTransformation(  &stTmpApnInfo2,
                                                   &stTmpApnInfo1);
        /* APNת�����ɹ�������ԭ��APN */
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_ERR_LOG("NAS_ESM_ProcSmPdpModify:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcSmPdpModify_ENUM, ESM_APN_ERROR);
        }
        else
        {
            NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stApnInfo,
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }

        /* ����PCO IPv4 */
        NAS_ESM_MEM_SET(&pstEpsbCntxtInfo->stPcoInfo, NAS_ESM_NULL, sizeof(NAS_ESM_CONTEXT_PCO_STRU));

        /* �洢PCO IPV4�� */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv4Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv4Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv4Item);
        }

        /* �洢PCO IPV6�� */
        if (NAS_ESM_OP_TRUE == pstRcvMsg->bitOpPcoIpv6Item)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            NAS_ESM_SavePcoIpv6Item(&pstEpsbCntxtInfo->stPcoInfo, &pstRcvMsg->stPcoIpv6Item);
        }

        /* lihong00150010 ims begin */
        /* �洢IM CN SIGNAL FLAG��ʶ */
        if ((NAS_ESM_OP_TRUE == pstRcvMsg->bitOpImCnSigalFlag))
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
            pstEpsbCntxtInfo->stPcoInfo.enImsCnSignalFlag = pstRcvMsg->enImCnSignalFlag;
        }
        /* lihong00150010 ims end */
    }

    /*��RABM����ID_ESM_ERABM_MDF_IND*/
    NAS_ESM_SndEsmRabmMdfIndMsg(ulEpsbId);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* ���ŵĳ���Ҫ֪ͨEHSM�޸Ķ�Ӧ��CID��Ϣ */
    NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(ulEpsbId);
    #endif

    /* ��ӡ������Ϣ */
    NAS_ESM_PrintEpsbInfo(ulEpsbId);

    return ;
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_ProcSmPdpDeactivate
 Description     : ESM����SM PDPɾ��
 Input           : SM_ESM_PDP_CONTEXT_INFO_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010            2011-04-28      Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcSmPdpDeactivate
(
    const SM_ESM_PDP_CONTEXT_INFO_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT8                           ucCnt            =  NAS_ESM_NULL;
    VOS_UINT32                          ulCurPdnNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbIdNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbId         = pstRcvMsg->ulNsapi;
    VOS_UINT32                          aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcSmPdpDeactivate:The pdp is already inactive!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcSmPdpDeactivate_ENUM, 1);
        return ;
    }

    /*�����ǰ����Ϊȱʡ����*/
    if(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /*���ҵ�ǰPDN������*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum();

        /*PDN����������1��*/
        if(ulCurPdnNum > 0)
        {
            ulCurPdnNum -= 1;
        }

        /*���浱ǰPDN������*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);
    }

    /*����ulEpsbIdNum��aulEpsbId���Ա�֪ͨRABM*/
    aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

    /*ѭ��������Ϣ��������˳��ع�����ר�г���*/
    for( ucCnt = NAS_ESM_MIN_EPSB_ID; ucCnt <= NAS_ESM_MAX_EPSB_ID; ucCnt++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucCnt);

        /*ĳһ���ص�Linked EPSB IDΪ��ǰ����ID*/
        if( (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType)
            && (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)\
            && (pstEpsbCntxtInfo->ulLinkedEpsbId == ulEpsbId) )
        {
            /*����ulEpsbIdNum��aulEpsbId���Ա�֪ͨRABM*/
            aulEpsbId[ulEpsbIdNum++] = ucCnt;
        }
    }

    /*֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId);

    /*�����Ѽ�¼�ĳ���ID��ѭ���ͷų�����Դ*/
    for( ucCnt = 0; ucCnt < ulEpsbIdNum; ucCnt++ )
    {
        /*�ͷų�����Դ*/
        NAS_ESM_ClearEsmBearerResource(aulEpsbId[ucCnt]);

        /*�ؼ��¼��ϱ�*/
        NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_RELEASE(ulEpsbId));
    }

    if (NAS_ESM_L_MODE_STATUS_NORMAL == NAS_ESM_GetLModeStatus())
    {
        /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_LOCAL);
    }
    else
    {
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
    }
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/* end of NasEsmSmMsgProc.c */
