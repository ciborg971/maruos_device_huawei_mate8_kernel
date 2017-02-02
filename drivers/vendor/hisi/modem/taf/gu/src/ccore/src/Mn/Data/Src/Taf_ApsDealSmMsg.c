


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "MnComm.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"

#include "TafApsSndSm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALSMMSG_C


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


VOS_UINT32 Aps_CheckPdpType(
    VOS_UINT8                           ucPdpId,
    SM_TAF_PDP_ADDR_STRU               *pSmAddr
)
{
    VOS_UINT8                           ucPdpOrgan;
    VOS_UINT8                           ucPdpTypeNum;
    VOS_UINT8                           ucPdpTypeReq;
    VOS_UINT8                           ucPdpTypeAcc;

    /*--------------------------------------------------------------------------
       ��ȡ�û�����PDP���������PDP type number
    --------------------------------------------------------------------------*/
    ucPdpTypeReq    = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;

    /*--------------------------------------------------------------------------
       ��ȡPDP ACTIVATE ACCEPT��Ϣ�е�PDP type organisation, PDP type number
       Refer to TS 24.008 section 10.5.6.4
    --------------------------------------------------------------------------*/
    ucPdpOrgan      = pSmAddr->aucPdpAddr[0] & 0x0F;
    ucPdpTypeNum    = pSmAddr->aucPdpAddr[1];

    /*--------------------------------------------------------------------------
       If PDP type organisation is 0(ETSI), PDP type num should be 0x01 for
       PDP-type PPP. All other values are reserved.
       If PDP type organisation is 1(IETF), PDP type num should be 0x21 (IPV4),
       0x57 (IPV6), or 0x8D (IPV4V6). All other values should be interpreted
       as IPV4. Refer to TS 24.008 section 10.5.6.4
    --------------------------------------------------------------------------*/
    switch(ucPdpOrgan)
    {
        case APS_ADDR_ORGAN_ETSI:
            if (APS_PDP_TYPE_NUM_PPP == ucPdpTypeNum)
            {
                ucPdpTypeAcc = APS_ADDR_PPP;
            }
            else
            {
               MN_ERR_LOG("Aps_CheckPdpType: PDP type is not supported!");
               return VOS_ERR;
            }
            break;

        case APS_ADDR_ORGAN_IETF:
#if (FEATURE_ON == FEATURE_IPV6)
            if ( (MN_APS_PDP_TYPE_NUM_IPV6   != ucPdpTypeNum)
              && (MN_APS_PDP_TYPE_NUM_IPV4V6 != ucPdpTypeNum) )
            {
                ucPdpTypeAcc = APS_ADDR_STATIC_IPV4;
            }
            else if (MN_APS_PDP_TYPE_NUM_IPV6 == ucPdpTypeNum)
            {
                ucPdpTypeAcc = MN_APS_ADDR_IPV6;
            }
            else
            {
                ucPdpTypeAcc = MN_APS_ADDR_IPV4V6;
            }
#else
            if (MN_APS_PDP_TYPE_NUM_IPV6 != ucPdpTypeNum)
            {
                ucPdpTypeAcc = APS_ADDR_STATIC_IPV4;
            }
            else
            {
               MN_ERR_LOG("Aps_CheckPdpType: PDP type IPV6 is not supported!");
               return VOS_ERR;
            }
#endif
            break;

        default:
            MN_ERR_LOG("Aps_CheckPdpType: Input Parameter error!");
            return VOS_ERR;
    }

    if (ucPdpTypeAcc != ucPdpTypeReq)
    {
#if (FEATURE_ON == FEATURE_IPV6)
        if ( (APS_ADDR_DYNAMIC_IPV4 == ucPdpTypeReq)
          && (APS_ADDR_STATIC_IPV4 == ucPdpTypeAcc) )
        {
            return VOS_OK;
        }
        else if ( (MN_APS_ADDR_IPV4V6 == ucPdpTypeReq)
               && (APS_ADDR_PPP != ucPdpTypeAcc) )
        {
            return VOS_OK;
        }
#else
        if ( (APS_ADDR_DYNAMIC_IPV4 == ucPdpTypeReq)
          && (APS_ADDR_STATIC_IPV4 == ucPdpTypeAcc) )
        {
            return VOS_OK;
        }
#endif
        else
        {
            MN_ERR_LOG("Aps_CheckPdpType: PDP type not matched!");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_VOID Aps_ValidPacketFlowId(VOS_UINT8 *pucPacketFlowId)
{
    if ( ((*pucPacketFlowId > 3) && (*pucPacketFlowId < 8))
      || (*pucPacketFlowId > APS_PACK_FLOW_ID_BIGGEST) )
    {
        MN_WARN_LOG("Aps_ValidPacketFlowId: Invalid PFI has been allocated.");
        *pucPacketFlowId = 0;
    }
}


VOS_UINT32 Aps_PdpActCnfParaCheck(
    SMREG_PDP_ACTIVATE_CNF_STRU            *pSmActCnfMsg,
    APS_ACTCNF_PARA_ST                     *pActCnfPara
)
{
    VOS_UINT8                               ucQosLen;
    VOS_UINT32                              ulReturnValue;
    TAF_APS_RAT_TYPE_ENUM_UINT32            enRatType;



    pActCnfPara->OP_PdpAddr             = VOS_FALSE;
    pActCnfPara->OP_ProtCfgOpt          = VOS_FALSE;
    pActCnfPara->OP_Sapi                = VOS_FALSE;
    pActCnfPara->OP_RadioPriority       = VOS_FALSE;
    pActCnfPara->OP_PacketFlowId        = VOS_FALSE;
    pActCnfPara->OP_Spare               = VOS_FALSE;

    /*NSAPI*/
    if (VOS_TRUE == pSmActCnfMsg->bitOpNsapi)
    {
        /*��������Ϣ����ucNsapi*/
        if ( !(APS_JUDGE_NSAPI_VALID(pSmActCnfMsg->ucNsapi)))
        {
            APS_WARN_LOG("Aps_PdpActCnfParaCheck err! ");
            return  APS_PARA_INVALID;
        }
    }
    else
    {
        /*���û��NSAPI����������Ϣ��NSAPI�Ǳ���Ĳ���*/
        APS_WARN_LOG("there is no NSAPI. err! ");
        return  APS_PARA_INVALID;
    }
    pActCnfPara->ucNsapi                = pSmActCnfMsg->ucNsapi;

    /*QOS*/
    /*��SM��������Ϣ�в����QOS */
    ulReturnValue = Aps_UnpackSmQos(    &pSmActCnfMsg->stNegoQos,
                                        &ucQosLen,
                                        &pActCnfPara->PdpQos    );
    /*�����error*/
    if(TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PdpActCnfParaCheck err! ");
        return  APS_PARA_INVALID;
    }

    /*����ɹ������QOS�Ϸ��Լ�� */
    ulReturnValue = Aps_QosValidOrNot(&pActCnfPara->PdpQos);
    if ( TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PdpActCnfParaCheck QOS err! ");
        return  APS_PARA_INVALID;
    }

    /*Addr*/
    /*���������ADDR, �򿽱�����*/
    if ( VOS_TRUE == pSmActCnfMsg->bitOpPdpAddr)
    {
        ulReturnValue = Aps_CheckPdpType( pSmActCnfMsg->ucConnectId,
                                          &(pSmActCnfMsg->stPdpAddr) );
        if ( TAF_APS_FAIL == ulReturnValue )
        {
            return APS_PDPTYPE_INVALID;
        }

        ulReturnValue = Aps_DetachSmAddrStru(   &(pSmActCnfMsg->stPdpAddr),
                                                &(pActCnfPara->PdpAddr) );
        if ( TAF_APS_FAIL == ulReturnValue)
        {
            APS_WARN_LOG("Aps_PdpActCnfParaCheck err! ");
            return  APS_PARA_INVALID;
        }
        pActCnfPara->OP_PdpAddr         = VOS_TRUE;


        /*���˴��յ��ĵ�ַ��Ŀǰ�Ѿ������PDP�ĵ�ַ�Ƿ���ͬ,�����ͬ,��
        Ϊ�쳣,����ԭ��Ϊ:���ص�ĳPDPΪ����̬,������಻���ڴ�PDP.������Ҫ
        �ͷŴ�PDP�����ϱ���PDP��ȥ����*/
        Aps_CheckAddrWithActPdp(pSmActCnfMsg->ucConnectId,
                                pActCnfPara->PdpAddr.aucIpAddr);

    }


    /*SAPI*/
    if (pSmActCnfMsg->bitOpSapi)
    {
        /* 6.1.3.1.1 Successful PDP context activation initiated by the mobile station*/
        if (APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pSmActCnfMsg->ucSapi))
        {
            APS_WARN_LOG("Aps_PdpActCnfParaCheck Sapi err! ");
            return  APS_PARA_INVALID;
        }
        else
        {
            pActCnfPara->OP_Sapi        = VOS_TRUE;
            pActCnfPara->ucSapi         = pSmActCnfMsg->ucSapi;
        }
    }

    /*ucRadioPriority*/
    if (pSmActCnfMsg->bitOpRadioPriority)
    {
        if (!(APS_JUDGE_RADIOPRI_VALID(pSmActCnfMsg->ucRadioPriority)))
        {
            APS_NORM_LOG("All other values are interpreted as priority level 4 by this version of the protocol.");
            pActCnfPara->ucRadioPriority = APS_RADIOPRI_4;
            pActCnfPara->OP_RadioPriority= VOS_TRUE;
        }
        else
        {
            pActCnfPara->ucRadioPriority = pSmActCnfMsg->ucRadioPriority;
            pActCnfPara->OP_RadioPriority= VOS_TRUE;
        }
    }


    enRatType = TAF_APS_GetCurrPdpEntityRatType();
    if ( TAF_APS_RAT_TYPE_GSM == enRatType)
    {
        /*PacketFlowId*/
        if ( pSmActCnfMsg->bitOpPacketFlowId )
        {
            pActCnfPara->OP_PacketFlowId    = VOS_TRUE;
            pActCnfPara->ucPacketFlowId     = pSmActCnfMsg->stPacketFlowId.ucPacketFlowId;
            Aps_ValidPacketFlowId(&(pActCnfPara->ucPacketFlowId));
        }
    }

    /*PCO,����DNS��NBNS */
    if (VOS_TRUE == pSmActCnfMsg->bitOpProtCfgOpt)
    {
        /*���DNS*/
        pActCnfPara->OP_ProtCfgOpt  = VOS_TRUE;
    }

    return  APS_PARA_VALID;
}


VOS_VOID    Aps_CheckAddrWithActPdp(    VOS_UINT8           ucPdpId,
                                        VOS_UINT8          *pucIpAddr)
{
    VOS_UINT8                           ucTmpPdpId;
    TAF_APS_STA_ENUM_UINT32             enState;

    for(ucTmpPdpId = 0; ucTmpPdpId < TAF_APS_MAX_PDPID; ucTmpPdpId++)
    {
        if(ucPdpId == ucTmpPdpId)
        {
            continue;
        }

        /*���ĳPDP����δ�������PDP����ΪIP��������������,�ͱȽ�IP��ַ*/
        enState = TAF_APS_GetPdpIdMainFsmState(ucTmpPdpId);
        if (((TAF_APS_STA_ACTIVE == enState)
            ||(TAF_APS_STA_MS_MODIFYING == enState))
          && (APS_ADDR_STATIC_IPV4 == g_PdpEntity[ucTmpPdpId].PdpAddr.ucPdpTypeNum)
          && (APS_PDP_ACT_PRI == g_PdpEntity[ucTmpPdpId].ActType))
        {
            /* ��ַ��ͬ�����ϱ�PDPȥ��������ڲ�ȥ����ָʾ */
            if ((pucIpAddr[0] == g_PdpEntity[ucTmpPdpId].PdpAddr.aucIpAddr[0]) &&
                (pucIpAddr[1] == g_PdpEntity[ucTmpPdpId].PdpAddr.aucIpAddr[1]) &&
                (pucIpAddr[2] == g_PdpEntity[ucTmpPdpId].PdpAddr.aucIpAddr[2]) &&
                (pucIpAddr[3] == g_PdpEntity[ucTmpPdpId].PdpAddr.aucIpAddr[3]) )
            {
                /*���ϱ���PDP��ȥ����*/
                TAF_APS_SndPdpDeActivateInd(ucTmpPdpId, TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION);

                /* �����ڲ�ȥ����ָʾ */
                TAF_APS_SndInterPdpDeactivateReq(ucTmpPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
            }
        }

    }

    return;
}



/*****************************************************************************
 Prototype      : Aps_CheckQosSatisify()
 Description    : ��ȡ�û�����ĸ�PDP���Խ��ܵ�MINQOS,���Ƚϣ��ж����緵�ص�QOS
                  �Ƿ�����MINQOS��Ҫ��.
 Input          : ucPdpId
                  pNetNegotQos
 Output         :
 Return Value   : ȡֵ: APS_PARA_VALID��APS_PARA_INVALID
 Date Accessed  :
 Date Update    :
 Calls          : Aps_GetPsMinQos()
                  Aps_CompareQos()
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_CheckQosSatisify (  VOS_UINT8               ucPdpId,
                                    APS_PDP_QOS_STRU*       pNetNegotQos)
{
    VOS_UINT32                      ulRet;
    VOS_UINT8                       ucDefinedOrNot;
    VOS_UINT8                       ucQosOkOrNot;
    APS_PDP_QOS_STRU                MinQos;

    /*��ȡTAF�趨����СQOS;����MinQos�� */
    ulRet = Aps_GetPsMinQos( ucPdpId, &ucDefinedOrNot, &MinQos );
    if ( TAF_ERR_ERROR == ulRet)
    {
        APS_WARN_LOG(" Can not get the MIN QOS of APP ! ");

        /*����QOS����MIN������*/
        return  APS_PARA_VALID;
    }

    if ( TAF_PDP_MIN_QOS_NOT_DEFINED == ucDefinedOrNot)
    {
        return  APS_PARA_VALID;
    }

    ulRet = Aps_CompareQos( pNetNegotQos, &MinQos, &ucQosOkOrNot );
    /*��Comparing the QOS error, ����ΪQOS����*/
    if ( TAF_APS_FAIL == ulRet)
    {
        APS_WARN_LOG("Comparing the QOSerror ! ");
        return  APS_PARA_VALID;
    }

    if ( APS_QOS_UP_TO_MIN == ucQosOkOrNot)
    {
        return  APS_PARA_VALID;
    }
    else
    {
        return  APS_PARA_INVALID;
    }
}

/**********************************************************
 Function:       Aps_GetPsMinQos
 Description:    APSģ���յ������Qos���������û����õ���С
                 Qos�������бȽ��Ծ����ǽ��ܻ��Ǿܾ�
 Calls:          APSģ��
 Data Accessed:
 Data Updated:
 Input:          ucCid
 Output:         pDefinedOrNot - �û��Ƿ�������СQos����
                 pQos - �û����õ�Qos����
 Return:         TAF-SUCCESS - �ɹ�
                 TAF-FAILURE - ʧ��
 Others:
**********************************************************/
VOS_UINT32 Aps_GetPsMinQos(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pDefinedOrNot,
    APS_PDP_QOS_STRU                   *pQos )
{
    VOS_UINT8           ucCid;

    ucCid               = g_PdpEntity[ucPdpId].stClientInfo.ucCid;

    if ( g_TafCidTab[ucCid].ucMinQosFlag )
    {
       *pDefinedOrNot = TAF_PDP_MIN_QOS_DEFINED;
        Taf_FillMinQos( &g_TafCidTab[ucCid], pQos );
        return TAF_SUCCESS;
    }


    /*��С�ɽ���Qosδ���壬APS������Ϊ�κ�Qos���ɽ���*/
    *pDefinedOrNot = TAF_PDP_MIN_QOS_NOT_DEFINED;

    return TAF_SUCCESS;
}
VOS_VOID Aps_PdpActCnfQosSatisfy(
    VOS_UINT8                           ucPdpId,
    APS_ACTCNF_PARA_ST                 *pActCnfPara,
    SMREG_PDP_ACTIVATE_CNF_STRU        *pStCnf
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_INNER_SN_ACT_ST                 ApsInerSnAct;
    SM_TAF_QOS_STRU                     stQos;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatTypeSuspend;

    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();
    enCurrRatTypeSuspend                = TAF_APS_GET_RAT_TYPE_IN_SUSPEND();

/*~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������SM���صĲ�����ʼ~~~~~~~~~~~~~~~~~~~~*/

    /*QOS*/
    PS_MEM_CPY(       &g_PdpEntity[ucPdpId].PdpQos,
                      &pActCnfPara->PdpQos,
                      sizeof(APS_PDP_QOS_STRU) );

    /*PdpAddr*/
    if (VOS_TRUE == pActCnfPara->OP_PdpAddr)
    {
        pstPdpEntity->PdpAddr = pActCnfPara->PdpAddr;
    }

    /*ucNsapi*/
    g_PdpEntity[ucPdpId].PdpNsapiFlag  = VOS_TRUE;
    g_PdpEntity[ucPdpId].ucNsapi       = pActCnfPara->ucNsapi;

    /*SAPI*/
    if ( pActCnfPara->OP_Sapi )
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Sapi  = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucSapi   = pActCnfPara->ucSapi;
    }

    /*ucRadioPriority*/
    if ( pActCnfPara->OP_RadioPriority )
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_RadioPriority = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority
                                        = pActCnfPara->ucRadioPriority;
    }

    /*DNS*/
    if (pActCnfPara->OP_ProtCfgOpt)
    {
        g_PdpEntity[ucPdpId].PdpDnsFlag = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpDns     = pActCnfPara->PcoDns;

        /* NBNS (WINS) */
        g_PdpEntity[ucPdpId].bitOpPdpNbns    = VOS_TRUE;
        g_PdpEntity[ucPdpId].stPdpNbns       = pActCnfPara->PcoNbns;

        /* GATE WAY (PEER IP) */
        g_PdpEntity[ucPdpId].bitOpPdpGateWay = VOS_TRUE;
        g_PdpEntity[ucPdpId].stPdpGateWay    = pActCnfPara->stPcoGateWay;
    }

    /*ucPacketFlowId*/
    if ( pStCnf->bitOpPacketFlowId )
    {
        g_PdpEntity[ucPdpId].GprsPara.OP_PacketFlowId = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPacketFlowId
                                        = pActCnfPara->ucPacketFlowId;
    }

    /*Pco*/
    if (pStCnf->bitOpProtCfgOpt)
    {
        pstPdpEntity->PdpDnsFlag        = VOS_TRUE;

        (VOS_VOID)MN_APS_UnpackPco(pstPdpEntity,
                         &pStCnf->stProtCfgOpt);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (VOS_TRUE == pStCnf->bitOpSmCause)
    {
        pstPdpEntity->bitOpCause        = VOS_TRUE;
        pstPdpEntity->enCause           = TAF_APS_MapSmCause(pStCnf->enCause);
    }
#endif

    pstPdpEntity->enEmergencyFlg        = TAF_PDP_NOT_FOR_EMC;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������������~~~~~~~~~~~~~~~~~~~~~~~~*/

    if ((TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
     || (TAF_APS_RAT_TYPE_WCDMA == enCurrRatTypeSuspend))
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        /*��ǰ��2G*/
        /*��SNDCP���𼤻�*/
        ApsInerSnAct.ucPdpId            = ucPdpId;
        ApsInerSnAct.pQos               = &pStCnf->stNegoQos;

        /* ����SNDCP��Ҫʹ�þ���������ת����Ĳ��� */
        Aps_PackSmQos(&(g_PdpEntity[ucPdpId].PdpQos), &stQos);
        ApsInerSnAct.pQos               = &stQos;

        Aps_SmMsgModSnActInd(&ApsInerSnAct, APS_ACT_SN_NORMAL);

        /*��д״̬���е�TRANSMODE*/
        g_PdpEntity[ucPdpId].GprsPara.Op_TransMode  = VOS_TRUE;
        if (    (APS_3GPP_QOS_RELIABCLASS_ACKGTPLLCRLC_PRODATA
                   == g_PdpEntity[ucPdpId].PdpQos.ucReliabClass)
             || (APS_3GPP_QOS_RELIABCLASS_UNKGTP_ACKLLCRLC_PRODATA
                   == g_PdpEntity[ucPdpId].PdpQos.ucReliabClass) )
        {
            g_PdpEntity[ucPdpId].GprsPara.TransMode = RABM_ABM_ENUM;
        }
        else
        {
            g_PdpEntity[ucPdpId].GprsPara.TransMode = RABM_ADM_ENUM;
        }

        /*�����Ѿ���SN���ͼ�����Ϣ�ı�ʶ*/
        g_PdpEntity[ucPdpId].PdpProcTrackFlag               = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot   = VOS_TRUE;
    }

    return;
}

/**********************************************************
 Function:       Aps_GetPsAnswerMode
 Description:    APSģ���յ����緢���PDP�����������Ҫ��
                 TAFM��ѯ��ǰ�����õ�Ӧ��ģʽ���˹�Ӧ��ģʽ��
                 ����Ҫ��APP��ָʾ���ȴ�APP��Ӧ���Զ�Ӧ��ģ
                 ʽ�£�APS��Ҫ����pAnswerType�������Զ�����
                 PDP������Զ��ܾ���������
 Calls:          APSģ��
 Data Accessed:
 Data Updated:
 Input:
 Output:         pAnswerMode - Ӧ��ģʽ
                 pAnswerType - �Զ�ģʽ�½��ܻ��߾ܾ�
 Return:         ��
 Others:
**********************************************************/
VOS_VOID  Aps_GetPsAnswerMode(
    TAF_PDP_ANSWER_MODE_ENUM_UINT8                    *pAnswerMode,
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8                    *pAnswerType
)
{
    if ( (VOS_NULL_PTR == pAnswerMode)
      || (VOS_NULL_PTR == pAnswerType) )
    {
        APS_WARN_LOG( "Taf_GetPsAnswerMode:Input pointer is null.\r");
        return;
    }

    *pAnswerMode = g_PsAnsMode.enAnsMode;
    *pAnswerType = g_PsAnsMode.enAnsType;
    return;
}



VOS_UINT32 Aps_ActIndAutoAns(
    TAF_PDP_ANSWER_TYPE_ENUM_UINT8                     AnswerType,
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd,
    APS_PDP_ACT_REQ_ST                 *pstApsPdpActReq
)
{
    VOS_UINT32                          ulRet;

    pstApsPdpActReq->OP_APN                 = VOS_FALSE;
    pstApsPdpActReq->OP_Sapi                = VOS_FALSE;
    pstApsPdpActReq->OP_AUTH                = VOS_FALSE;
    pstApsPdpActReq->OP_DNS                 = VOS_FALSE;
    pstApsPdpActReq->OP_NBNS                = VOS_FALSE;
    pstApsPdpActReq->Op_Xid_DCmp            = VOS_FALSE;
    pstApsPdpActReq->Op_Xid_PCmp            = VOS_FALSE;
    pstApsPdpActReq->OP_SPARE               = VOS_FALSE;
    pstApsPdpActReq->PdpAuth.AuthType       = TAF_PCO_NOT_AUTH;


    if ( TAF_PDP_ANSWER_TYPE_REJECT == AnswerType)
    {
        /*�ܾ����缤��ָʾ*/
        APS_WARN_LOG("Aps_ActIndAutoAns :the AnswerType is call reject");
        return TAF_APS_FAIL;
    }
    else
    {
        /*�������緢��ļ��� ,��ȡ�Զ�Ӧ����ܼ���ʱ����Ĳ���, ע��Ҫ��
          PDPTYPE��ADDR��APN��Ϣ���� ApsPdpActReq��, TAFM��ѡ��CIDʱҪ�鿴
          ��3�ֲ���
        */
        pstApsPdpActReq->ucPdpId            = ucPdpId;

        /*ADDR��Ϣ�ֽ�ΪADDRTYPE��ADDR������Ϣ*/
        ulRet   = Aps_DetachSmAddrStru( &pStActInd->stOfferPdpAddr,
                                        &g_PdpEntity[ucPdpId].PdpAddr   );
        if ( TAF_APS_FAIL == ulRet)
        {
            APS_WARN_LOG("ERROR! Getting PpdAddr of ACT_IND fail ! Aps_PdpActInd()");
            return TAF_APS_FAIL;
        }
        g_PdpEntity[ucPdpId].PdpAddrFlag= VOS_TRUE;

        /*���������������PDP���ͺ͵�ַ*/
        pstApsPdpActReq->ucPdpType          = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;

        if ( APS_ADDR_PPP != pstApsPdpActReq->ucPdpType )
        {
            /*�����IP����*/
            PS_MEM_CPY( pstApsPdpActReq->aucIpAddr,
                        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                        TAF_IPV4_ADDR_LEN );
        }

        /*APN*/
        if ( pStActInd->bitOpAcsPointName)
        {
            g_PdpEntity[ucPdpId].PdpApnFlag = VOS_TRUE;
            Aps_DetachSmApn( &pStActInd->stAcsPointName,
                             &g_PdpEntity[ucPdpId].PdpApn    );

            /*���������������APN*/
            pstApsPdpActReq->aucApn[0]      = g_PdpEntity[ucPdpId].PdpApn.ucLength;
            if (pstApsPdpActReq->aucApn[0] > APS_MAX_LENGTH_OF_APN)
            {
               pstApsPdpActReq->aucApn[0]  = APS_MAX_LENGTH_OF_APN;
            }

            /* ��APN���Ȳ�����0, ����APN, ���п��� */
            if ( 0 != pstApsPdpActReq->aucApn[0])
            {
                pstApsPdpActReq->OP_APN     = VOS_TRUE;
                PS_MEM_CPY(             &(pstApsPdpActReq->aucApn[1]),
                                        g_PdpEntity[ucPdpId].PdpApn.aucValue,
                                        pstApsPdpActReq->aucApn[0]);
            }
        }

        /*��ȡ�����������, TAFM������QOS��USERNAME��PASSCODE��Ϣ */
        ulRet = TAF_APS_GetPsReqPdp(pstApsPdpActReq);
        if ( TAF_ERR_ERROR == ulRet )
        {
            APS_WARN_LOG("ERROR! Can not get Parameters for PDP Activation ! Aps_PdpActInd()");
            return TAF_APS_FAIL;
        }

        /*SAPI*/
        pstApsPdpActReq->OP_Sapi            = VOS_TRUE;
        pstApsPdpActReq->ucSapi             = APS_SAPI_INIT;

        /*���ʽ��ֵΪAPS�Զ����𼤻�*/
        g_PdpEntity[ucPdpId].PdpProcTrackFlag            = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct = APS_TAF_AUTO_INIT_ACT;
    }

    return TAF_APS_SUCC;
}
VOS_VOID    Aps_ActIndRejRsp(       VOS_UINT8       ucPdpId )
{
    SMREG_PDP_ACTIVATE_REJ_RSP_STRU    *pstPdpActRejRsp;

    /* ������Ϣ�������Ϣͷ */
    pstPdpActRejRsp = (SMREG_PDP_ACTIVATE_REJ_RSP_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_ACTIVATE_REJ_RSP);
    if (VOS_NULL_PTR == pstPdpActRejRsp)
    {
        return;
    }

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pstPdpActRejRsp->ucConnectId = ucPdpId;

    /*�ܾ�ԭ����Ϊ" ��Դ������ " */
    pstPdpActRejRsp->enCause = SM_TAF_CAUSE_SM_NW_INSUFFICIENT_RESOURCES;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpActRejRsp))
    {
        APS_WARN_LOG("Aps_ActIndRejRsp Snd msg fail!");
        return;
    }

    return;
}


VOS_UINT32  TAF_APS_GetPsReqPdp(APS_PDP_ACT_REQ_ST *pReqPdp)
{
    VOS_UINT8 ucIndex;

    for (ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++)
    {   /*ȡPDP���е�һ����Ч��PDP������Ϊ���緢�𼤻�ʱPDP����*/
        if (VOS_TRUE == g_TafCidTab[ucIndex].ucUsed)
        {   /*CID����Ч*/
            if (TAF_FALSE == Taf_CheckActCid(ucIndex))
            {   /*Cidδ��ʹ��*/
                if (TAF_SUCCESS == Taf_ComparePdp(pReqPdp, &g_TafCidTab[ucIndex].CidTab))
                {   /*PDP����,��ַ���ݣ�APN������ͬ*/
                    if (TAF_SUCCESS == Aps_PackApsActReqPara(ucIndex,
                                                             pReqPdp->ucPdpId,
                                                             pReqPdp))
                    {   /*��¼��Ӧ��ú��е�PDP ID��Ϣ*/
                        TAF_APS_SetPdpEntClientInfo(pReqPdp->ucPdpId,
                                                    ucIndex,
                                                    TAF_APS_INVALID_MODULEID,
                                                    g_PsAnsMode.usClientId,
                                                    pReqPdp->ucPdpId + APS_MT_DIFF_VALU);

                        return TAF_SUCCESS;
                    }
                }
            }
        }
    }

    /*û���ҵ�ƥ���PDP�������ʹ������Я���Ĳ���������������д��Ĭ�ϵ�*/
    pReqPdp->OP_AUTH                = VOS_FALSE;
    pReqPdp->PdpAuth.AuthType       = TAF_PCO_NOT_AUTH;                    /*����Ȩ*/
    PS_MEM_SET(&pReqPdp->PdpAuth.AuthContent, 0, sizeof(pReqPdp->PdpAuth.AuthContent));

    /*Qos���Ϊ�������*/
    g_TafCidTab[0].ucQosTabFlag     = VOS_FALSE;
    Taf_FillQos(&g_TafCidTab[0], &pReqPdp->ReqQos);

    TAF_APS_SetPdpEntClientInfo(pReqPdp->ucPdpId,
                                TAF_APS_DEFAULT_CID,
                                TAF_APS_INVALID_MODULEID,
                                g_PsAnsMode.usClientId,
                                pReqPdp->ucPdpId + APS_MT_DIFF_VALU);

    return TAF_SUCCESS;
}



VOS_UINT32  Taf_ComparePdp(             APS_PDP_ACT_REQ_ST  *pApsPdp,
                                        TAF_PDP_PRIM_CONTEXT_STRU    *pTafCidPdp)
{
    VOS_UINT8                           i;
    VOS_UINT8                           aucTmpApn[TAF_MAX_APN_LEN + 1];
    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];

    PS_MEM_SET(aucTmpApn, 0x00, sizeof(aucTmpApn));
    PS_MEM_SET(aucIpAddr, 0x00, sizeof(aucIpAddr));

    if (pApsPdp->ucPdpType != pTafCidPdp->stPdpAddr.enPdpType)
    {
        return TAF_APS_FAIL;                                 /*��ַ���Ͳ���ͬ*/
    }

    /*��ַ������ͬ���ж������Ƿ���ͬ*/
    if ( APS_ADDR_STATIC_IPV4 == pApsPdp->ucPdpType)
    {   /*��ַ�����Ǿ�̬IP���Ƚ�IP��ַ�Ƿ���ͬ*/

        /*��CID���е�ADDRת����4�ֽڵĵ�ַ*/
        PS_MEM_CPY(aucIpAddr, pTafCidPdp->stPdpAddr.aucIpv4Addr, TAF_IPV4_ADDR_LEN);

        for (i = 0; i < TAF_IPV4_ADDR_LEN; i ++)
        {
            if (aucIpAddr[i] != pApsPdp->aucIpAddr[i] )
            {
                return TAF_APS_FAIL;                         /*��һ�����ȣ���ַ�Ͳ���ͬ*/
            }
        }
    }

    /*��ַ���ͺ͵�ַ������ͬ���ж�APN�Ƿ���ͬ*/
    /*�Ȱ�CID������ʽ��APNת��������Э����ʽ��APN*/
    Taf_LenStr2Apn(&(pTafCidPdp->stApn), aucTmpApn);

    if (pApsPdp->aucApn[0] != aucTmpApn[0])
    {
        return TAF_APS_FAIL;                                 /*���Ȳ���ͬ*/
    }
    else
    {
       if (0 != VOS_MemCmp(             pApsPdp->aucApn,
                                        aucTmpApn,
                                        aucTmpApn[0] + 1))
       {
            return TAF_APS_FAIL;                             /*���ݲ���ͬ*/
       }
    }
    return TAF_SUCCESS;

}
VOS_UINT32  Aps_PdpMdfCnfParaCheck (    SMREG_PDP_MODIFY_CNF_STRU   *pStMdfCnf,
                                        APS_MDFCNF_PARA_ST *pMdfCnfPara )
{

    VOS_UINT8                           ucQosLen;
    VOS_UINT32                          ulReturnValue;

    pMdfCnfPara->OP_QOS                 = VOS_FALSE;
    pMdfCnfPara->OP_SAPI                = VOS_FALSE;
    pMdfCnfPara->OP_RadioPri            = VOS_FALSE;
    pMdfCnfPara->OP_PFI                 = VOS_FALSE;
    pMdfCnfPara->OP_SPARE               = VOS_FALSE;

    /*NSAPI ���ã������*/

    /*QOS*/
    /*��SM��������Ϣ�в����QOS */
    if (pStMdfCnf->bitOpNegotiatedQos)
    {
        pMdfCnfPara->OP_QOS                 = VOS_TRUE;
        ulReturnValue = Aps_UnpackSmQos(    &pStMdfCnf->stNegotiatedQos,
                                            &ucQosLen,
                                            &pMdfCnfPara->PdpQos    );
        if ( TAF_APS_FAIL == ulReturnValue)
        {   /*�����error*/
            APS_WARN_LOG("Aps_PdpMdfCnfParaCheck Aps_UnpackSmQos err! ");
            return  APS_PARA_INVALID;
        }

        /*����ɹ������QOS�Ϸ��Լ�� */
        ulReturnValue = Aps_QosValidOrNot(      &pMdfCnfPara->PdpQos    );
        if ( TAF_APS_FAIL == ulReturnValue)
        {
            APS_WARN_LOG("Aps_PdpMdfCnfParaCheck QOS err! ");
            return  APS_PARA_INVALID;
        }
    }

    /*SAPI*/
    if (pStMdfCnf->bitOpSapi)
    {
        /*APP�����޸�ʱ������SAPI���ڽ��������޸�CNF��Ϣʱ���ж�SAPI*/
        if (g_PdpModifyReqTable[pStMdfCnf->ucConnectId].OP_Sapi)
        {
            if (APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pStMdfCnf->ucSapi))
            {
                APS_WARN_LOG("Aps_PdpMdfCnfParaCheck Sapi err! ");
                return  APS_PARA_INVALID;
            }
            else
            {
                pMdfCnfPara->OP_SAPI        = VOS_TRUE;
                pMdfCnfPara->ucSapi         = pStMdfCnf->ucSapi;
            }
        }
    }

    /*ucRadioPriority*/
    if (pStMdfCnf->bitOpRadioPriority)
    {
        if (!(APS_JUDGE_RADIOPRI_VALID(pStMdfCnf->ucRadioPriority)))
        {
            APS_NORM_LOG("All other values are interpreted as priority level 4 by this version of the protocol.");
            pMdfCnfPara->OP_RadioPri    = VOS_TRUE;
            pMdfCnfPara->ucRadioPriority= APS_RADIOPRI_4;
        }
        else
        {
            pMdfCnfPara->OP_RadioPri    = VOS_TRUE;
            pMdfCnfPara->ucRadioPriority= pStMdfCnf->ucRadioPriority;
        }
    }

    if ( TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
    {
        /*PacketFlowId*/
        if ( pStMdfCnf->bitOpPacketFlowId )
        {
            pMdfCnfPara->OP_PFI             = VOS_TRUE;
            pMdfCnfPara->ucPacketFlowId     = pStMdfCnf->stPacketFlowId.ucPacketFlowId;
            Aps_ValidPacketFlowId(&(pMdfCnfPara->ucPacketFlowId));
        }
    }

    return  APS_PARA_VALID;
}
VOS_VOID    Aps_PdpMdfCnfQosSatisfy (   VOS_UINT8          ucPdpId,
                                        APS_MDFCNF_PARA_ST          *pMdfCnfPara,
                                        SMREG_PDP_MODIFY_CNF_STRU   *pMdfCnf)
{
    APS_INNER_SN_MDF_ST                 ApsInerSnMdf;
    SM_TAF_QOS_STRU                     SnMdfQos;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    RABM_TRANS_MODE_ENUM                enTansMode;

    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();


/*~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������SM���صĲ�����ʼ~~~~~~~~~~~~~~~~~~~~*/
    /*QOS*/
    if ( pMdfCnf->bitOpNegotiatedQos )
    {
        PS_MEM_CPY(       &g_PdpEntity[ucPdpId].PdpQos,
                          &pMdfCnfPara->PdpQos,
                          sizeof(APS_PDP_QOS_STRU) );
    }
    else
    {   /*��g_PdpModifyReqTable�е�QOS������״̬����*/
        if ((VOS_TRUE == g_PdpModifyReqTable[ucPdpId].Op_Qos) &&
            (APS_MDF_HAS_QOS == g_PdpModifyReqTable[ucPdpId].Op_Spare))
        {
            PS_MEM_CPY(   &g_PdpEntity[ucPdpId].PdpQos,
                          &(g_PdpModifyReqTable[ucPdpId].Qos),
                          sizeof(APS_PDP_QOS_STRU)  );

            if (0 == g_PdpEntity[ucPdpId].PdpQos.ucDelayClass)
            {
                g_PdpEntity[ucPdpId].PdpQos.ucDelayClass = APS_3GPP_QOS_DELAYCLASS_4;
            }

            if (0 == g_PdpEntity[ucPdpId].PdpQos.ucReliabClass)
            {
                g_PdpEntity[ucPdpId].PdpQos.ucReliabClass = APS_3GPP_QOS_RELIABCLASS_UNKGTPLLC_ACKRLC_PRODATA;
            }

            if (0 == g_PdpEntity[ucPdpId].PdpQos.ucPrecedenceClass)
            {
                g_PdpEntity[ucPdpId].PdpQos.ucPrecedenceClass = APS_3GPP_QOS_PRECEDENCECLASS_NORMPRI;
            }

            if (0 == g_PdpEntity[ucPdpId].PdpQos.ucPeakThrough)
            {
                g_PdpEntity[ucPdpId].PdpQos.ucPeakThrough = APS_3GPP_QOS_PEAKTHROUGH_1000_OCTPS;
            }

            if (0 == g_PdpEntity[ucPdpId].PdpQos.ucMeanThrough)
            {
                g_PdpEntity[ucPdpId].PdpQos.ucMeanThrough = APS_3GPP_QOS_MEANTHROUGH_BESTEFFORT;
            }


            g_PdpModifyReqTable[ucPdpId].Op_Spare   = APS_MDF_CNF_RENEW_QOS;
        }
        else
        {   /*���ʶ*/
            g_PdpModifyReqTable[ucPdpId].Op_Spare   = APS_MDF_NO_QOS;
        }
    }

    /*SAPI*/
    if (pMdfCnfPara->OP_SAPI)
    {   /*��������SAPI*/
        g_PdpEntity[ucPdpId].GprsPara.ucSapi       = pMdfCnfPara->ucSapi;
    }
    else
    {   /*��û�з���SAPI,��ʹ�÷����޸�ʱAPP��SAPI����״̬���е�SAPI*/
        if (g_PdpModifyReqTable[ucPdpId].OP_Sapi)
        {
            g_PdpEntity[ucPdpId].GprsPara.ucSapi
                            = g_PdpModifyReqTable[ucPdpId].ucSapi;
        }
    }

    /*ucRadioPriority*/
    g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority
                                        = pMdfCnfPara->ucRadioPriority;

    /*ucPacketFlowId*/
    if ( pMdfCnf->bitOpPacketFlowId )
    {
        g_PdpEntity[ucPdpId].GprsPara.OP_PacketFlowId  = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPacketFlowId
                                        = pMdfCnfPara->ucPacketFlowId;
    }

    /*TFT*/
    if (g_PdpModifyReqTable[ucPdpId].Op_Tft)
    {
        g_PdpEntity[ucPdpId].PdpTftFlag = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpTft[0]  = g_PdpModifyReqTable[ucPdpId].Tft;
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������������~~~~~~~~~~~~~~~~~~~~~~~~*/

    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /*�ϱ�����ɹ� */
        TAF_APS_SndPdpModifyCnf(ucPdpId);
    }
    else
    {   /*��ǰ��2G*/
        /*����޸���QOS,����SNDCP���𼤻�*/
        if ((PS_TRUE == pMdfCnf->bitOpNegotiatedQos)
          ||(APS_MDF_CNF_RENEW_QOS == g_PdpModifyReqTable[ucPdpId].Op_Spare))
        {
            Aps_DecideTransMode(ucPdpId, &enTansMode);

            /* ��д״̬���е�TRANSMODE */
            g_PdpEntity[ucPdpId].GprsPara.Op_TransMode = VOS_TRUE;
            g_PdpEntity[ucPdpId].GprsPara.TransMode    = enTansMode;

            ApsInerSnMdf.ucPdpId        = ucPdpId;
            if ( pMdfCnf->bitOpNegotiatedQos )
            {   /*����Э����QOS����������Э�̵�QOS*/
                ApsInerSnMdf.pQos       = &pMdfCnf->stNegotiatedQos;
            }
            else
            {   /*����û��Э������UE�����QOS*/
                Aps_PackSmQos( &g_PdpEntity[ucPdpId].PdpQos, &SnMdfQos );
                ApsInerSnMdf.pQos       = &SnMdfQos;
            }

            Aps_SmMsgModSnMdfInd(&ApsInerSnMdf);

        }
        else
        {
            /*QOSû�б仯,��֪ͨSNDCP*/
            /*�ϱ�����ɹ� */
            TAF_APS_SndPdpModifyCnf(ucPdpId);
        }
    }

    /*���ʶ*/
    g_PdpModifyReqTable[ucPdpId].Op_Spare = APS_MDF_NO_QOS;

    return;
}
VOS_UINT32  Aps_PdpMdfIndParaCheck (    SMREG_PDP_MODIFY_IND_STRU     *pStMdfInd,
                                        APS_MDFIND_PARA_ST *pMdfIndPara )
{

    VOS_UINT8                           ucQosLen;
    VOS_UINT32                          ulReturnValue;

    pMdfIndPara->OP_PdpAddr             = VOS_FALSE;
    pMdfIndPara->OP_Nsapi               = VOS_FALSE;
    pMdfIndPara->OP_Sapi                = VOS_FALSE;
    pMdfIndPara->OP_RadioPriority       = VOS_FALSE;
    pMdfIndPara->OP_PacketFlowId        = VOS_FALSE;
    pMdfIndPara->OP_Spare               = VOS_FALSE;

    /*NSAPI ���ã������*/

    /*QOS*/
    /*��SM��������Ϣ�в����QOS */
    ulReturnValue = Aps_UnpackSmQos(    &pStMdfInd->stNewQos,
                                        &ucQosLen,
                                        &pMdfIndPara->NewQos    );
    if ( TAF_APS_FAIL == ulReturnValue)
    {   /*�����error*/
        APS_WARN_LOG("Aps_UnpackSmQos err! ");
        return  APS_PARA_INVALID;
    }

    /*����ɹ������QOS�Ϸ��Լ�� */
    ulReturnValue = Aps_QosValidOrNot(&pMdfIndPara->NewQos);
    if ( TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PdpMdfIndParaCheck QOS err! ");
        return  APS_PARA_INVALID;
    }


    /*SAPI*/
    if (pStMdfInd->bitOpSapi)
    {
        if (APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pStMdfInd->ucSapi))
        {
            APS_WARN_LOG("Aps_PdpMdfIndParaCheck Sapi err! ");
            return  APS_PARA_INVALID;
        }
        else
        {
            pMdfIndPara->OP_Sapi        = VOS_TRUE;
            pMdfIndPara->ucSapi         = pStMdfInd->ucSapi;
        }
    }

    /*ucRadioPriority*/
    if (pStMdfInd->bitOpRadioPriority)
    {
        if (!(APS_JUDGE_RADIOPRI_VALID(pStMdfInd->ucRadioPriority)))
        {
            APS_NORM_LOG("All other values are interpreted as priority level 4 by this version of the protocol.");
            pMdfIndPara->OP_RadioPriority    = VOS_TRUE;
            pMdfIndPara->ucRadioPriority     = APS_RADIOPRI_4;
        }
        else
        {
            pMdfIndPara->OP_RadioPriority   = VOS_TRUE;
            pMdfIndPara->ucRadioPriority    = pStMdfInd->ucRadioPriority;
        }
    }

    /*Addr*/
    /*���������ADDR, �򿽱�����*/
    if ( VOS_TRUE == pStMdfInd->bitOpPdpAddr)
    {
        ulReturnValue = Aps_DetachSmAddrStru(   &(pStMdfInd->stPdpAddr),
                                                &(pMdfIndPara->PdpAddr) );
        if ( TAF_APS_FAIL == ulReturnValue)
        {
            APS_WARN_LOG("Aps_PdpMdfIndParaCheck err! ");
            return  APS_PARA_INVALID;
        }
        pMdfIndPara->OP_PdpAddr         = VOS_TRUE;
    }

    if ( TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
    {
        /*PacketFlowId*/
        if ( pStMdfInd->bitOpPacketFlowId )
        {
            pMdfIndPara->OP_PacketFlowId    = VOS_TRUE;
            pMdfIndPara->ucPacketFlowId     = pStMdfInd->stPacketFlowId.ucPacketFlowId;
            Aps_ValidPacketFlowId(&(pMdfIndPara->ucPacketFlowId));
        }
    }

    return  APS_PARA_VALID;
}



VOS_VOID Aps_PdpMdfIndQosSatisfy (
    VOS_UINT8                           ucPdpId,
    APS_MDFIND_PARA_ST                 *pMdfIndPara,
    SMREG_PDP_MODIFY_IND_STRU          *pStMdfInd
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_INNER_SN_MDF_ST                 ApsInerSnMdf;
    SM_TAF_QOS_STRU                     stQos;
    RABM_TRANS_MODE_ENUM                enTansMode;

    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


/*~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������SM���صĲ�����ʼ~~~~~~~~~~~~~~~~~~~~*/
    /*QOS*/
    PS_MEM_CPY(                       &g_PdpEntity[ucPdpId].PdpQos,
                                      &pMdfIndPara->NewQos,
                                      sizeof(APS_PDP_QOS_STRU) );
    /*SAPI*/
    if ( pMdfIndPara->OP_Sapi)
    {
        g_PdpEntity[ucPdpId].GprsPara.ucSapi           = pMdfIndPara->ucSapi;
    }

    /*ucRadioPriority*/
    if ( pMdfIndPara->OP_RadioPriority)
    {
        g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority
                                        = pMdfIndPara->ucRadioPriority;
    }

    /*ucPacketFlowId*/
    if ( pMdfIndPara->OP_PacketFlowId)
    {
        g_PdpEntity[ucPdpId].GprsPara.OP_PacketFlowId  = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPacketFlowId
                                        = pMdfIndPara->ucPacketFlowId;
    }

    /*PdpAddr*/
    if (VOS_TRUE == pMdfIndPara->OP_PdpAddr)
    {
        pstPdpEntity->PdpAddr = pMdfIndPara->PdpAddr;
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������������~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*��SM�����޸���Ӧ*/
    Aps_PdpMdfRsp(ucPdpId);

    if ( TAF_APS_RAT_TYPE_WCDMA == TAF_APS_GetCurrPdpEntityRatType())
    {
        /*�ϱ��޸ĳɹ� */
        TAF_APS_SndPdpModifyInd(ucPdpId);
    }
    else
    {
        Aps_DecideTransMode(ucPdpId, &enTansMode);

        /* ��д״̬���е�TRANSMODE */
        pstPdpEntity->GprsPara.Op_TransMode = VOS_TRUE;
        pstPdpEntity->GprsPara.TransMode    = enTansMode;

        /*�޸���QOS,��SNDCP���𼤻�*/
        ApsInerSnMdf.ucPdpId            = ucPdpId;
        ApsInerSnMdf.pQos               = &pStMdfInd->stNewQos;

        /* ����SNDCP��Ҫʹ�þ���������ת����Ĳ��� */
        Aps_PackSmQos(&(g_PdpEntity[ucPdpId].PdpQos), &stQos);
        ApsInerSnMdf.pQos               = &stQos;

        Aps_SmMsgModSnMdfInd(&ApsInerSnMdf);
    }


    return;
}



VOS_VOID    Aps_PdpMdfRsp(              VOS_UINT8           ucPdpId)
{
    SMREG_PDP_MODIFY_RSP_STRU          *pstPdpModRsp;

    /* ������Ϣ�������Ϣͷ */
    pstPdpModRsp = (SMREG_PDP_MODIFY_RSP_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_PDP_MODIFY_RSP);
    if (VOS_NULL_PTR == pstPdpModRsp)
    {
        return;
    }

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pstPdpModRsp->ucConnectId = ucPdpId;

    pstPdpModRsp->bitOpNsapi = VOS_TRUE;

    pstPdpModRsp->bitOpSpare = VOS_FALSE;

    pstPdpModRsp->ucNsapi    = g_PdpEntity[ucPdpId].ucNsapi;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstPdpModRsp))
    {
        APS_WARN_LOG("Aps_PdpMdfRsp Snd msg fail!");
        return;
    }

    return;
}
VOS_UINT32 Aps_PdpActSecCnfParaCheck(
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pStSecCnf,
    APS_ACTSECCNF_PARA_ST              *pActSecCnfPara
)
{

    VOS_UINT8                           ucQosLen;
    VOS_UINT32                          ulReturnValue;

    pActSecCnfPara->OP_Sapi             = VOS_FALSE;
    pActSecCnfPara->OP_RadioPriority    = VOS_FALSE;
    pActSecCnfPara->OP_PacketFlowId     = VOS_FALSE;
    pActSecCnfPara->OP_Spare            = VOS_FALSE;

    /*�ж�PdpId�Ϸ���*/
    if (!(APS_JUDEG_PDPID_VALID(pStSecCnf->ucConnectId)))
    {
        APS_WARN_LOG("Aps_PdpActSecCnfParaCheck err! ");
        return  APS_PDPID_INVALID;
    }

    /*NSAPI*/
    if (VOS_TRUE == pStSecCnf->bitOpNsapi)
    {   /*��������Ϣ����ucNsapi*/
        if ( !(APS_JUDGE_NSAPI_VALID(pStSecCnf->ucNsapi)))
        {
            APS_WARN_LOG("Aps_PdpActSecCnfParaCheck err! ");
            return  APS_PARA_INVALID;
        }
    }
    else
    {   /*���û��NSAPI����������Ϣ��NSAPI�Ǳ���Ĳ���*/
        APS_WARN_LOG("there is no NSAPI. err! ");
        return  APS_PARA_INVALID;
    }
    pActSecCnfPara->ucNsapi             = pStSecCnf->ucNsapi;


    /*QOS*/
    /*��SM��������Ϣ�в����QOS */
    ulReturnValue = Aps_UnpackSmQos(    &pStSecCnf->stNegotiatedQos,
                                        &ucQosLen,
                                        &pActSecCnfPara->PdpQos );
    /*�����error*/
    if(TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PdpActSecCnfParaCheck err! ");
        return  APS_PARA_INVALID;
    }

    /*����ɹ������QOS�Ϸ��Լ�� */
    ulReturnValue = Aps_QosValidOrNot(&pActSecCnfPara->PdpQos);
    if ( TAF_APS_FAIL == ulReturnValue)
    {
        APS_WARN_LOG("Aps_PdpActSecCnfParaCheck QOS err! ");
        return  APS_PARA_INVALID;
    }


    /*SAPI*/
    if (pStSecCnf->bitOpSapi)
    {
        /* 6.1.3.2.1 Successful Secondary PDP Context Activation Procedure Initiated by the MS */
        if (APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pStSecCnf->ucSapi))
        {
            APS_WARN_LOG("Aps_PdpActSecCnfParaCheck Sapi err! ");
            return  APS_PARA_INVALID;
        }
        else
        {
            pActSecCnfPara->OP_Sapi     = VOS_TRUE;
            pActSecCnfPara->ucSapi      = pStSecCnf->ucSapi;
        }
    }

    /*ucRadioPriority*/
    if (pStSecCnf->bitOpRadioPriority)
    {
        /* ����24.008 10.5.7.2 All other values are interpreted as priority level 4
           by this version of the protocol. */
        if (!(APS_JUDGE_RADIOPRI_VALID(pStSecCnf->ucRadioPriority)))
        {
            APS_NORM_LOG("All other values are interpreted as priority level 4 by this version of the protocol.");
            pActSecCnfPara->OP_RadioPriority    = VOS_TRUE;
            pActSecCnfPara->ucRadioPriority     = APS_RADIOPRI_4;
        }
        else
        {
            pActSecCnfPara->OP_RadioPriority    = VOS_TRUE;
            pActSecCnfPara->ucRadioPriority = pStSecCnf->ucRadioPriority;
        }
    }

    if ( TAF_APS_RAT_TYPE_GSM == TAF_APS_GetCurrPdpEntityRatType())
    {
        /*PacketFlowId*/
        if ( pStSecCnf->bitOpPacketFlowId )
        {
            pActSecCnfPara->OP_PacketFlowId = VOS_TRUE;
            pActSecCnfPara->ucPacketFlowId  = pStSecCnf->stPacketFlowId.ucPacketFlowId;
            Aps_ValidPacketFlowId(&(pActSecCnfPara->ucPacketFlowId));
        }
    }

    return  APS_PARA_VALID;
}
VOS_VOID    Aps_PdpActSecCnfQosSatisfy( VOS_UINT8              ucPdpId,
                                        APS_ACTSECCNF_PARA_ST             *pSecCnfPara,
                                        SMREG_PDP_ACTIVATE_SEC_CNF_STRU   *pStSecCnf   )
{

    APS_INNER_SN_ACT_ST                 ApsInerSnAct;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

/*~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������SM���صĲ�����ʼ~~~~~~~~~~~~~~~~~~~~*/

    /*QOS*/
    PS_MEM_CPY(       &g_PdpEntity[ucPdpId].PdpQos,
                      &pSecCnfPara->PdpQos,
                      sizeof(APS_PDP_QOS_STRU) );


    /*ucNsapi*/
    g_PdpEntity[ucPdpId].PdpNsapiFlag   = VOS_TRUE;
    g_PdpEntity[ucPdpId].ucNsapi        = pSecCnfPara->ucNsapi;

    /*SAPI*/
    if ( pStSecCnf->bitOpSapi)
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_Sapi   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucSapi    = pSecCnfPara->ucSapi;
    }

    /*ucRadioPriority*/
    if ( pStSecCnf->bitOpRadioPriority )
    {
        g_PdpEntity[ucPdpId].GprsPara.Op_RadioPriority  = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority
                                        = pSecCnfPara->ucRadioPriority;
    }

    /*ucPacketFlowId*/
    if ( pStSecCnf->bitOpPacketFlowId )
    {
        g_PdpEntity[ucPdpId].GprsPara.OP_PacketFlowId   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPacketFlowId
                                        = pSecCnfPara->ucPacketFlowId;
    }

    g_PdpEntity[ucPdpId].enEmergencyFlg = TAF_PDP_NOT_FOR_EMC;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~��PDP״̬������������~~~~~~~~~~~~~~~~~~~~~~~~*/

    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
    }
    else
    {
        /*��ǰ��2G*/
        /*��SNDCP���𼤻�*/
        ApsInerSnAct.ucPdpId            = ucPdpId;
        ApsInerSnAct.pQos               = &pStSecCnf->stNegotiatedQos;

        Aps_SmMsgModSnActInd(&ApsInerSnAct, APS_ACT_SN_NORMAL);

        /*�����Ѿ���SN���ͼ�����Ϣ�ı�ʶ*/
        g_PdpEntity[ucPdpId].PdpProcTrackFlag               = VOS_TRUE;
        g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot   = VOS_TRUE;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_SmMsgModSnActInd()
 Description    : APS�յ�SM�ļ���CNF��,�����ô˺�����SNDCP���ͼ���ָʾ��Ϣ.
                  �ú�������ѯPDP״̬���Ի�ü���SNDCP����Ĳ���.
 Input          : pSnActInd,�����������PDP������Э�̵�QOS
                  ucActCause :#define APS_ACT_SN_NORMAL     0
                              #define APS_ACT_SN_SYS_CHNG   1
 Output         : NO
 Return Value   :
 Calls          : Aps_SmMsgModSnActIndParaPack()
                  Aps_SmMsgModGetSnActIndPara()
                  Aps_SmMsgModPackSnMsg()
 Called By      : Aps_PdpActCnf()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_SmMsgModSnActInd  (     APS_INNER_SN_ACT_ST    *pInnerSnActInd,
                                        VOS_UINT8               ucActCause)
{
    VOS_UINT32                          ulRet;
    APS_SNDCP_ACTIVATE_IND_MSG         *pSnActIndMsg;

    /*������Ϣ*/
    /* BEGIN 2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    pSnActIndMsg = (APS_SNDCP_ACTIVATE_IND_MSG *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(APS_SNDCP_ACTIVATE_IND_MSG) - VOS_MSG_HEAD_LENGTH);
    /*  END  2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    if ( VOS_NULL_PTR == pSnActIndMsg )
    {
        APS_ERR_LOG("Aps_SmMsgModSnActInd VOS_AllocMsg err ");
        return;
    }
    PS_MEM_SET(pSnActIndMsg,0x00,sizeof(APS_SNDCP_ACTIVATE_IND_MSG));
    /*�����Ϣͷ*/
    APS_PACK_SN_MSG_HEADER((*pSnActIndMsg), APS_SNDCP_ACTIVATE_IND_ST)

    /*��ֵ��Ϣ����*/
    pSnActIndMsg->usMsgType             = APS_SN_ACT_IND_MSG_TYPE;

    /*����Ϣ�е�usPId*/
    pSnActIndMsg->usPId
            = (VOS_UINT16)g_PdpEntity[pInnerSnActInd->ucPdpId].ucNsapi;

    /*�����Ϣ��*/
    Aps_SmMsgModSnActIndParaPack (      pInnerSnActInd,
                                        &pSnActIndMsg->ApsSnActInd  );

    /*��д����SNDCP��ԭ��*/
    pSnActIndMsg->ApsSnActInd.ucActSndcpType  = ucActCause;

    /*��SNDCP������Ϣ*/
    ulRet = PS_SEND_MSG( WUEPS_PID_TAF, pSnActIndMsg );
    if ( VOS_OK != ulRet )
    {
        APS_WARN_LOG("Send APS_SNDCP_ACTIVATE_IND_MSG ERR ");
        return;
    }
    APS_NORM_LOG("APS->SNDCP APS_SNDCP_ACTIVATE_IND_MSG ");

    return;
}
VOS_VOID    Aps_SmMsgModSnActIndParaPack
                            (   APS_INNER_SN_ACT_ST        *pInnerSnActInd,
                                APS_SNDCP_ACTIVATE_IND_ST  *pSnActIndPara  )
{
    VOS_UINT8                           ucPdpId;

    ucPdpId                             = pInnerSnActInd->ucPdpId;

    pSnActIndPara->ucNsapi              = g_PdpEntity[ucPdpId].ucNsapi;
    pSnActIndPara->ucSapi               = g_PdpEntity[ucPdpId].GprsPara.ucSapi;
    pSnActIndPara->ulTLLI               = GMM_GetTlli();
    pSnActIndPara->ucRadioPriority      = g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority;

    /*����QoS:֮���Բ�ʹ��sizeof(ST_QOS)��ʹ��sizeof(APS_ST_QOS),����ΪQOS_STRU�ĳ���Ϊ�˼����ԵĿ��ǣ���Ϊ
      ��16(R7)����APS_ST_QOS�ṹ��ĳ������������汾����*/
    PS_MEM_CPY(                       &pSnActIndPara->NegoQos,
                                      pInnerSnActInd->pQos,
                                      sizeof(APS_ST_QOS) );

    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
    if(pSnActIndPara->NegoQos.ulCnt > 11)
    {
        APS_WARN_LOG("Aps_SmMsgModSnActIndParaPack:QOS LEN IS MORE THAN 11");
        pSnActIndPara->NegoQos.ulCnt = 11;
    }
    #endif

    Aps_SetSnXidPara(ucPdpId, &pSnActIndPara->XidParameter);

    return;
}

/*****************************************************************************
 Prototype      : Aps_SetSnXidPara
 Description    :
 Input          : ucPdpId
 Output         : pSnXid
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SetSnXidPara(           VOS_UINT8           ucPdpId,
                                        SN_XID_REQ_ST      *pSnXid  )
{
    pSnXid->ucMask                      = 0;

    if (g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp)
    {
        pSnXid->ucMask                 |= SN_XID_PARA_P_CMPR;
        pSnXid->ucPCmprAlgrth           = g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth;
    }

    if (g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp)
    {
        pSnXid->ucMask                 |= SN_XID_PARA_D_CMPR;
        pSnXid->ucDCmprAlgrth           = g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth;
    }
    return;
}

/*****************************************************************************
 Prototype      : Aps_SmMsgModSnMdfInd()
 Description    : APS�յ�SM���޸�CNF��,�����ô˺�����SNDCP�����޸�ָʾ��Ϣ.
                  �ú�������ѯPDP״̬���Ի���޸�SNDCP����Ĳ���.
 Input          : pApsInnerSnMdf,ָ��APS����ģ���ʹ�õ��޸�SNDCP�Ľṹ�壬
                  �ýṹ�������������:
                  ucPdpId,����SM���ص���Ϣ�еĲ���ucCr,����APS��ʶ��PDP;
                  SM_TAF_QOS_STRU,���緵�ص�QOS�ṹ��;
 Output         : NO
 Return Value   :
 Calls          : Aps_SmMsgModSnMdfIndParaPack()
                  Aps_SmMsgModPackSnMsg()
 Called By      : Aps_PdpMdfCnf()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_SmMsgModSnMdfInd  ( APS_INNER_SN_MDF_ST*    pInnerSnMdfInd )
{

    VOS_UINT32                          ulRet;
    APS_SNDCP_MODIFY_IND_MSG           *pSnMdfIndMsg;

    /*������Ϣ*/
    /* BEGIN 2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    pSnMdfIndMsg = (APS_SNDCP_MODIFY_IND_MSG *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(APS_SNDCP_MODIFY_IND_MSG)- VOS_MSG_HEAD_LENGTH));
    /*  END  2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    if ( VOS_NULL_PTR == pSnMdfIndMsg )
    {
        APS_ERR_LOG("Aps_SmMsgModSnMdfInd VOS_AllocMsg err ");
        return;
    }

    /*�����Ϣͷ*/
    APS_PACK_SN_MSG_HEADER((*pSnMdfIndMsg), APS_SNDCP_MODIFY_IND_ST);

    /*��ֵ��Ϣ����*/
    pSnMdfIndMsg->usMsgType             = APS_SN_MDF_IND_MSG_TYPE;

    /*����Ϣ�е�usPId*/
    pSnMdfIndMsg->usPId
            = (VOS_UINT16)g_PdpEntity[pInnerSnMdfInd->ucPdpId].ucNsapi;

    /*�����Ϣ��*/
    Aps_SmMsgModSnMdfIndParaPack (      pInnerSnMdfInd,
                                        &pSnMdfIndMsg->ApsSnMdfInd  );

    /*��SNDCP������Ϣ*/
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pSnMdfIndMsg );
    if ( VOS_OK != ulRet )
    {
        APS_WARN_LOG("Send APS_SNDCP_ACTIVATE_IND_MSG ERR ");
        return;
    }
    APS_NORM_LOG("APS->SNDCP APS_SNDCP_MODIFY_IND_MSG ");

    return;
}

/*****************************************************************************
 Prototype      : Aps_SmMsgModSnMdfIndParaPack()
 Description    : �����޸�SNDCP����Ĳ���;
 Input          : ucPdpId
 Output         : pSnMdfIndPara,��Щ������APS��PDP״̬���л��;
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SmMsgModSnMdfIndParaPack
                            (   APS_INNER_SN_MDF_ST        *pInnerSnMdfInd,
                                APS_SNDCP_MODIFY_IND_ST    *pSnMdfIndPara   )
{
    VOS_UINT8                           ucPdpId;

    ucPdpId                             = pInnerSnMdfInd->ucPdpId;

    pSnMdfIndPara->OP_SNPduNum          = 0;
    pSnMdfIndPara->OP_RNPduNum          = 0;
    pSnMdfIndPara->SPARE                = 0;

    pSnMdfIndPara->ucNsapi              = g_PdpEntity[ucPdpId].ucNsapi;
    pSnMdfIndPara->ucSapi               = g_PdpEntity[ucPdpId].GprsPara.ucSapi;
    pSnMdfIndPara->ulTLLI               = GMM_GetTlli();
    pSnMdfIndPara->ucRadioPriority      = g_PdpEntity[ucPdpId].GprsPara.ucRadioPriority;

    /*����QoS:֮���Բ�ʹ��sizeof(ST_QOS)��ʹ��sizeof(APS_ST_QOS),����ΪQOS_STRU�ĳ���Ϊ�˼����ԵĿ��ǣ���Ϊ
      ��14����APS_ST_QOS�ṹ��ĳ������������汾����*/
    PS_MEM_CPY(                       &pSnMdfIndPara->NegoQos,
                                      pInnerSnMdfInd->pQos,
                                      sizeof(APS_ST_QOS) );

}

/*****************************************************************************
 Prototype      : Aps_SmMsgModSnDeActInd()
 Description    : APS�յ�SM��ȥ����CNF��,�����ô˺�����SNDCP����ȥ����ָʾ��Ϣ.
                  �ú�������ѯPDP״̬���Ի��ȥ����SNDCP����Ĳ���.
 Input          : ucPdpId,����SM���ص���Ϣ�еĲ���ucCr,����APS��ʶ��PDP.
 Output         : NO
 Return Value   :
 Calls          : Aps_SmMsgModSnMdfIndParaPack()
                  Aps_SmMsgModPackSnMsg()
 Called By      : Aps_PdpDeActCnf()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SmMsgModSnDeActInd (    VOS_UINT8    ucPdpId )
{
    VOS_UINT32                          ulRet;
    APS_SNDCP_DEACTIVATE_IND_MSG       *pSnDeActIndMsg;

    /*������Ϣ*/
    /* BEGIN 2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    pSnDeActIndMsg = (APS_SNDCP_DEACTIVATE_IND_MSG *)PS_ALLOC_MSG(WUEPS_PID_TAF,(sizeof(APS_SNDCP_DEACTIVATE_IND_MSG) - VOS_MSG_HEAD_LENGTH));
    /*  END  2006-04-06 Modified by liuyang id:48197 for A32D01738*/
    if ( VOS_NULL_PTR == pSnDeActIndMsg )
    {
        APS_ERR_LOG("Aps_SmMsgModSnDeActInd VOS_AllocMsg err ");
        return TAF_APS_FAIL;
    }

    /*�����Ϣͷ*/
    APS_PACK_SN_MSG_HEADER((*pSnDeActIndMsg), APS_SNDCP_DEACTIVATE_IND_ST);

    /*��ֵ��Ϣ����*/
    pSnDeActIndMsg->usMsgType           = APS_SN_DEACT_IND_MSG_TYPE;

    /*����Ϣ�е�usPId*/
    pSnDeActIndMsg->usPId
            = (VOS_UINT16)g_PdpEntity[ucPdpId].ucNsapi;

    /*�����Ϣ��*/
    Aps_SmMsgModSnDeActIndParaPack(     ucPdpId,
                                        &pSnDeActIndMsg->ApsSnDeActInd  );

    /*��SNDCP������Ϣ*/
    ulRet = PS_SEND_MSG( WUEPS_PID_TAF, pSnDeActIndMsg );
    if ( VOS_OK != ulRet )
    {
        APS_WARN_LOG("Send APS_SNDCP_DEACTIVATE_IND_MSG ERR ");
        return  TAF_APS_FAIL;
    }
    APS_NORM_LOG("APS->SNDCP APS_SNDCP_DEACTIVATE_IND_MSG ");

    return TAF_APS_SUCC;
}

/*****************************************************************************
 Prototype      : Aps_SmMsgModSnMdfIndParaPack()
 Description    : �����޸�SNDCP����Ĳ���;
 Input          : ucPdpId
 Output         : pSnMdfIndPara,��Щ������APS��PDP״̬���л��;
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SmMsgModSnDeActIndParaPack
                            (   VOS_UINT8                     ucPdpId,
                                APS_SNDCP_DEACTIVATE_IND_ST*  pSnDeActIndPara )
{
    pSnDeActIndPara->ucNsapi            = g_PdpEntity[ucPdpId].ucNsapi;
    pSnDeActIndPara->ucLLCReleaseInd    = APS_SN_NOT_REL_LLC;
    pSnDeActIndPara->ucXIDNegoInd       = APS_SN_XID_NEGO;
    pSnDeActIndPara->ulTLLI             = GMM_GetTlli();

    return;
}



VOS_UINT32 Aps_UnpackSmQos (
    SM_TAF_QOS_STRU                     *pSmQos,
    VOS_UINT8                           *pucQosLen,
    APS_PDP_QOS_ST                      *pApsQos
)
{
    /*�������*/
    if( (VOS_NULL == pSmQos)
       || (VOS_NULL == pucQosLen)
       || (VOS_NULL == pApsQos) )
    {
        APS_WARN_LOG("The input pointer parameter  can not be NULL , Aps_DetachSmQosStru()");
        return(TAF_APS_FAIL);
    }

    *pucQosLen = (VOS_UINT8)pSmQos->ulQosLen;

    /* QoS���ȵļ����Լ�� */
    if (*pucQosLen < 3)
    {
        APS_WARN_LOG("QoS len is abnormal, Aps_DetachSmQosStru()");
        return(TAF_APS_FAIL);
    }

    /* ��ʼ��QosĿ��ṹ�� */
    (VOS_VOID)VOS_MemSet(pApsQos, 0x00, sizeof(APS_PDP_QOS_ST));

    pApsQos->ucDelayClass           = (pSmQos->aucQos[0] & APS_QOS_DELAY_CLASS)>>3;
    pApsQos->ucReliabClass          = (pSmQos->aucQos[0] & APS_QOS_RELIABILITY_CLASS);

    pApsQos->ucPeakThrough          = (pSmQos->aucQos[1] & APS_QOS_PEAK_THROUGHPUT)>>4;
    pApsQos->ucPrecedenceClass      = (pSmQos->aucQos[1] & APS_QOS_PRECEDENCE_CLASS);

    pApsQos->ucMeanThrough          = (pSmQos->aucQos[2] & APS_QOS_MEAN_THROUGHPUT);

    if (*pucQosLen > 3)
    {
        pApsQos->ucTrafficClass     = (pSmQos->aucQos[3] & APS_QOS_TRAFFIC_CLASS)>>5;
        pApsQos->ucDeliverOrder     = (pSmQos->aucQos[3] & APS_QOS_DELIVERY_ORDER)>>3;
        pApsQos->ucDeliverOfErrSdu  = (pSmQos->aucQos[3] & APS_QOS_DELIVERY_ERRORNEOUS_SDU);
    }

    if (*pucQosLen > 4)
    {
        pApsQos->ucMaximSduSize         = pSmQos->aucQos[4];
    }

    if (*pucQosLen > 5)
    {
        pApsQos->ucMaxBitRateForUp      = pSmQos->aucQos[5];
    }

    if (*pucQosLen > 6)
    {
        pApsQos->ucMaxBitRateForDown    = pSmQos->aucQos[6];
    }

    if (*pucQosLen > 7)
    {
        pApsQos->ucResidualBer          = (pSmQos->aucQos[7] & APS_QOS_RESIDUAL_BER)>>4;
        pApsQos->ucSduErrRatio          = (pSmQos->aucQos[7] & APS_QOS_SDU_ERROR_RATIO);
    }

    if (*pucQosLen > 8)
    {
        pApsQos->ucTransDelay           = (pSmQos->aucQos[8] & APS_QOS_TRANSFER_DELAY)>>2;
        pApsQos->ucTraffHandlPrior      = (pSmQos->aucQos[8] & APS_QOS_TRAFFIC_HANDLING_PRIORITY);
    }

    if (*pucQosLen > 9)
    {
        pApsQos->ucGuarantBitRateForUp  = pSmQos->aucQos[9];
    }

    if (*pucQosLen > 10)
    {
       pApsQos->ucGuarantBitRateForDown = pSmQos->aucQos[10];
    }

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    if (*pucQosLen > 11)
    {
        pApsQos->ucSrcStatisticsDescriptor = (pSmQos->aucQos[11] & APS_QOS_SSD);

        /* Signalling-Indication ��ֵֻȡ���ֽڵĵ�5λ */
        pApsQos->ucSignallingIndication    = ((pSmQos->aucQos[11] & APS_QOS_SIGNALLING_INDICATION) >> 4);
    }

    if (*pucQosLen > 12)
    {
        pApsQos->ucMaxBitRateForDownExt     = pSmQos->aucQos[12];
    }

    if (*pucQosLen > 13)
    {
        pApsQos->ucGuarantBitRateForDownExt = pSmQos->aucQos[13];
    }
    #endif

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    if (*pucQosLen > 14)
    {
        pApsQos->ucMaxBitRateForUpExt     = pSmQos->aucQos[14];
    }

    if (*pucQosLen > 15)
    {
        pApsQos->ucGuarantBitRateForUpExt = pSmQos->aucQos[15];
    }
    #endif

    return(TAF_APS_SUCC);
}


VOS_UINT32 MN_APS_DecodeIpcpConfigReqPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
)
{
    VOS_UINT8                           ucOptType;
    VOS_UINT8                           ucOptLen;

    /*-------------------------------------------------------------------
       ֻ����Gatewary IP (Peer IP)
    -------------------------------------------------------------------*/
    while (usPktLen)
    {
        /*lint -e961*/
        /* ��ȡIPCP Option���� */
        ucOptType   = *pucProtocolPacket++;

        /* ��ȡIPCP Option���� */
        ucOptLen    = *pucProtocolPacket++;
        /*lint +e961*/

        /* ���ʣ���IPCP Packet�ĳ��ȱȸ�IPCP Option�ĳ���С, ��ֱ�Ӷ��� */
        if (usPktLen < ucOptLen)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpCodeConfigReq: Invalid IPCP packet Len.");
            return VOS_ERR;
        }

        /* ���IPCP Option�ĳ���Ϊ0, ��ֱ�Ӷ��� */
        if (0 == ucOptLen)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpCodeConfigReq: IPCP option length is zero.");
            return VOS_ERR;
        }

        switch (ucOptType)
        {
            case APS_PPP_IP_ADDR_ID:
                /*--------------------------------------------------------------
                   Peer IP��ַ���ȱ������6
                   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
                --------------------------------------------------------------*/
                if (APS_PPP_IP_ADDR_LEN != ucOptLen)
                {
                    MN_ERR_LOG1("MN_APS_DecodeIpcpCodeConfigReq: Invalid IPCP ADDRESS Option. Len:",
                                ucOptLen);
                    return VOS_ERR;
                }
                else
                {
                    pstPdpEntity->stPdpGateWay.bitOpGateWay = VOS_TRUE;
                    PS_MEM_CPY(pstPdpEntity->stPdpGateWay.aucGateWay,
                               pucProtocolPacket,
                               TAF_IPV4_ADDR_LEN);

                    pucProtocolPacket += TAF_IPV4_ADDR_LEN;
                    usPktLen          -= ucOptLen;
                }
                break;

            default:
                MN_WARN_LOG1("MN_APS_DecodeIpcpCodeConfigReq: Option type not supported %d",ucOptType);
                pucProtocolPacket += (ucOptLen - 2);
                usPktLen -= ucOptLen;
                break;
        }
    }

    return VOS_OK;
}


VOS_UINT32 MN_APS_DecodeIpcpConfigNakAckRejPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
)
{
    VOS_UINT8                           ucOptType;
    VOS_UINT8                           ucOptLen;

    while (usPktLen)
    {
        /*lint -e961*/
        /* ��ȡIPCP Option���� */
        ucOptType   = *pucProtocolPacket++;

        /* ��ȡIPCP Option���� */
        ucOptLen    = *pucProtocolPacket++;
        /*lint +e961*/

        /* ���ʣ���IPCP Packet�ĳ��ȱȸ�IPCP Option�ĳ���С, ��ֱ�Ӷ��� */
        if (usPktLen < ucOptLen)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpConfigNakAckRejPkt: Invalid IPCP packet Len.");
            return VOS_ERR;
        }

        /* ���IPCP Option�ĳ���Ϊ0, ��ֱ�Ӷ��� */
        if (0 == ucOptLen)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpConfigNakAckRejPkt: IPCP option length is zero.");
            return VOS_ERR;
        }

        switch (ucOptType)
        {
            case APS_PPP_PRI_DNS_ID:
                /*--------------------------------------------------------------
                   Primary DNS��ַ���ȱ������6
                   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
                --------------------------------------------------------------*/
                if (APS_PPP_PRI_DNS_LEN != ucOptLen)
                {
                    MN_ERR_LOG1("MN_APS_DecodeIpcpConfigNakAckRejPkt: Invalid Pri DNS Option Len. Len:",
                                ucOptLen);
                    return VOS_ERR;
                }
                else
                {
                    pstPdpEntity->PdpDns.OP_PriDns      = VOS_TRUE;
                    PS_MEM_CPY(pstPdpEntity->PdpDns.aucPriDns,
                               pucProtocolPacket,
                               TAF_IPV4_ADDR_LEN);

                    pucProtocolPacket += TAF_IPV4_ADDR_LEN;
                    usPktLen          -= ucOptLen;
                }
                break;

            case APS_PPP_PRI_NBNS_ID:
                /*--------------------------------------------------------------
                   Primary NBNS��ַ���ȱ������6
                   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
                --------------------------------------------------------------*/
                if (APS_PPP_PRI_NBNS_LEN != ucOptLen)
                {
                    MN_ERR_LOG1("MN_APS_DecodeIpcpConfigNakAckRejPkt: Invalid Pri NBNS Option Len. Len:",
                                ucOptLen);
                    return VOS_ERR;
                }
                else
                {
                    pstPdpEntity->stPdpNbns.OP_PriNbns  = VOS_TRUE;
                    PS_MEM_CPY(pstPdpEntity->stPdpNbns.aucPriNbns,
                               pucProtocolPacket,
                               TAF_IPV4_ADDR_LEN);

                    pucProtocolPacket += TAF_IPV4_ADDR_LEN;
                    usPktLen          -= ucOptLen;
                }
                break;

            case APS_PPP_SEC_DNS_ID:
                /*--------------------------------------------------------------
                   Secondary DNS��ַ���ȱ������6
                   OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
                --------------------------------------------------------------*/
                if (APS_PPP_SEC_DNS_LEN != ucOptLen)
                {
                    MN_ERR_LOG1("MN_APS_DecodeIpcpConfigNakAckRejPkt: Invalid Sec DNS Option Len. Len:",
                                ucOptLen);
                    return VOS_ERR;
                }
                else
                {
                    pstPdpEntity->PdpDns.OP_SecDns      = VOS_TRUE;
                    PS_MEM_CPY(pstPdpEntity->PdpDns.aucSecDns,
                               pucProtocolPacket,
                               TAF_IPV4_ADDR_LEN);

                    pucProtocolPacket += TAF_IPV4_ADDR_LEN;
                    usPktLen          -= ucOptLen;
                }
                break;

          case APS_PPP_SEC_NBNS_ID:
              /*--------------------------------------------------------------
                 Secondary NBNS��ַ���ȱ������6
                 OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
              --------------------------------------------------------------*/
                if (APS_PPP_SEC_NBNS_LEN != ucOptLen)
                {
                    MN_ERR_LOG1("MN_APS_DecodeIpcpConfigNakAckRejPkt: Invalid Sec NBNS Option Len. Len:",
                                ucOptLen);
                    return VOS_ERR;
                }
                else
                {
                    pstPdpEntity->stPdpNbns.OP_SecNbns  = VOS_TRUE;
                    PS_MEM_CPY(pstPdpEntity->stPdpNbns.aucSecNbns,
                               pucProtocolPacket,
                               TAF_IPV4_ADDR_LEN);

                    pucProtocolPacket += TAF_IPV4_ADDR_LEN;
                    usPktLen          -= ucOptLen;
                }
                break;

            default:
                MN_WARN_LOG1("MN_APS_DecodeIpcpConfigNakAckRejPkt: Option type not supported. Type:",
                             ucOptType);

                pucProtocolPacket += (ucOptLen - 2);
                usPktLen          -= ucOptLen;
                break;
        }
    }

    return VOS_OK;
}


VOS_UINT32 MN_APS_DecodeIpcpProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucProtocolPkt,
    VOS_UINT16                          usProtocolPktLen
)
{
    VOS_UINT8                           ucConfigType;
    VOS_UINT8                           ucIdentifier;
    VOS_UINT16                          usLength;

    while (usProtocolPktLen > 0)
    {
        /*lint -e961*/
        /* ��ȡConfig type */
        ucConfigType  = *pucProtocolPkt++;

        /* ��ȡIdentifier */
        ucIdentifier  = *pucProtocolPkt++;

        MN_NORM_LOG1("MN_APS_DecodeIpcpProtocolPacket: Identifier:", ucIdentifier);

        /* ��ȡPacket length */
        usLength  = (*pucProtocolPkt++) << 8;
        usLength |= *pucProtocolPkt++;
        /*lint +e961*/

        if (usProtocolPktLen < usLength)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpProtocolPacket: Invalid packet length.");
            return VOS_ERR;
        }

        usProtocolPktLen -= usLength;

        if (usLength < APS_PCO_CONFIG_HDR_LEN)
        {
            MN_ERR_LOG("MN_APS_DecodeIpcpProtocolPacket: Invalid IPCP packet length.");
            return VOS_ERR;
        }

        /* �Ӱ������м�ȥCONFIG_HDR_LEN */
        usLength -= APS_PCO_CONFIG_HDR_LEN;

        /* ֻ����CONFIG_REQ/CONFIG_NAK/CONFIG_ACK/CONFIG_REJ, ���������� */
        switch (ucConfigType)
        {
            case APS_PPP_CODE_REQ:
                MN_NORM_LOG("MN_APS_DecodeIpcpProtocolPacket: CONFIG_REQ IPCP pkt.");
                if (VOS_OK != MN_APS_DecodeIpcpConfigReqPkt(pstPdpEntity,
                                                            pucProtocolPkt,
                                                            usLength))
                {
                    return VOS_ERR;
                }

                pucProtocolPkt += usLength;
                break;

            case APS_PPP_CODE_NAK:
                MN_NORM_LOG("MN_APS_DecodeIpcpProtocolPacket: CONFIG NAK IPCP pkt.");
                if (VOS_OK != MN_APS_DecodeIpcpConfigNakAckRejPkt(pstPdpEntity,
                                                                  pucProtocolPkt,
                                                                  usLength))
                {
                    return VOS_ERR;
                }

                pucProtocolPkt += usLength;
                break;


            case APS_PPP_CODE_ACK:
                MN_NORM_LOG("MN_APS_DecodeIpcpProtocolPacket: CONFIG ACK IPCP pkt.");
                if (VOS_OK != MN_APS_DecodeIpcpConfigNakAckRejPkt(pstPdpEntity,
                                                                  pucProtocolPkt,
                                                                  usLength))
                {
                    return VOS_ERR;
                }

                pucProtocolPkt += usLength;
                break;

            case APS_PPP_CODE_REJ:
                MN_NORM_LOG("MN_APS_DecodeIpcpProtocolPacket: CONFIG REJ IPCP pkt.");
                if (VOS_OK != MN_APS_DecodeIpcpConfigNakAckRejPkt(pstPdpEntity,
                                                                  pucProtocolPkt,
                                                                  usLength))
                {
                    return VOS_ERR;
                }

                pucProtocolPkt += usLength;
                break;

            default:
                MN_WARN_LOG1("MN_APS_DecodeIpcpProtocolPacket: Invalid IPCP code, Ignore. Type:",
                             ucConfigType);
                pucProtocolPkt += usLength;
                break;
        }
    }

    return VOS_OK;
}
VOS_VOID TAF_APS_DecodeIpv4PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv4PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
)
{
    VOS_UINT8                           aucInvalidIpv4Addr[TAF_IPV4_ADDR_LEN] = {0,0,0,0};

    /* �����IPv4 P-CSCF��Packet���� */
    if (TAF_IPV4_ADDR_LEN != usProtocolPacketLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_DecodeIpv4PcscfProtocolPkt: Wrong IPv4 P-CSCF Address");
        return;
    }

    /*-------------------------------------------------------------
       ֻ��������IPv4��P-CSCF, ���PCO�����������ϵ�IPv4 P-CSCF,
       ֻȡǰ����, �����ĺ���.
    -------------------------------------------------------------*/
    if (*pucIpv4PcscfNum == 0)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv4Addr,
                            TAF_IPV4_ADDR_LEN))
        {
            pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV4_ADDR_LEN);
            (*pucIpv4PcscfNum)++;
        }
    }
    else if (*pucIpv4PcscfNum == 1)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv4Addr,
                            TAF_IPV4_ADDR_LEN))
        {
            pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV4_ADDR_LEN);
            (*pucIpv4PcscfNum)++;
        }
    }
    else if (*pucIpv4PcscfNum == 2)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv4Addr,
                            TAF_IPV4_ADDR_LEN))
        {
            pstPdpEntity->stPdpPcscf.bitOpThiPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucThiPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV4_ADDR_LEN);
            (*pucIpv4PcscfNum)++;
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_DecodeIpv4PcscfProtocolPkt: More than two IPv6 P-CSCF addresses present, Ignore the others.");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID MN_APS_DecodeIpV6DnsProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpV6DnsNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
)
{
    VOS_UINT8                           aucInvalidIpV6Addr[TAF_IPV6_ADDR_LEN];

    PS_MEM_SET(aucInvalidIpV6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    if (TAF_IPV6_ADDR_LEN != usProtocolPacketLen)
    {
        MN_WARN_LOG("MN_APS_DecodeIpV6DnsProtocolPacket: Wrong IPV6 DNS Address");
        return;
    }

    /*-------------------------------------------------------------------
       ֻ��������IPV6��DNS, ���PCO�����������ϵ�IPV6 DNS, ֻȡǰ����,
       �����ĺ���.
    -------------------------------------------------------------------*/
    if (*pucIpV6DnsNum == 0)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpV6Addr,
                            TAF_IPV6_ADDR_LEN))
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpPriDns = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucPriDns,
                       pucProtocolPacket,
                       TAF_IPV6_ADDR_LEN);
            (*pucIpV6DnsNum)++;
        }
    }
    else if (*pucIpV6DnsNum == 1)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpV6Addr,
                            TAF_IPV6_ADDR_LEN))
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpSecDns = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucSecDns,
                       pucProtocolPacket,
                       TAF_IPV6_ADDR_LEN);
            (*pucIpV6DnsNum)++;
        }
    }
    else
    {
        MN_WARN_LOG("MN_APS_DecodeIpV6DnsProtocolPacket: More than two IPV6 DNS addresses present, Ignore the others.");
    }

    return;
}


VOS_VOID TAF_APS_DecodeIpv6PcscfProtocolPkt(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    VOS_UINT8                          *pucIpv6PcscfNum,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usProtocolPacketLen
)
{
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    /* �����IPv6 P-CSCF��Packet���� */
    if (TAF_IPV6_ADDR_LEN != usProtocolPacketLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_DecodeIpv6PcscfProtocolPkt: Wrong IPv6 P-CSCF Address");
        return;
    }

    /*-------------------------------------------------------------
       ֻ��������IPv6��P-CSCF, ���PCO�����������ϵ�IPv6 P-CSCF,
       ֻȡǰ����, �����ĺ���.
    -------------------------------------------------------------*/
    if (*pucIpv6PcscfNum == 0)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv6Addr,
                            TAF_IPV6_ADDR_LEN))
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV6_ADDR_LEN);
            (*pucIpv6PcscfNum)++;
        }
    }
    else if (*pucIpv6PcscfNum == 1)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv6Addr,
                            TAF_IPV6_ADDR_LEN))
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV6_ADDR_LEN);
            (*pucIpv6PcscfNum)++;
        }
    }
    else if (*pucIpv6PcscfNum == 2)
    {
        if (0 != PS_MEM_CMP(pucProtocolPacket,
                            aucInvalidIpv6Addr,
                            TAF_IPV6_ADDR_LEN))
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpThiPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucThiPcscfAddr,
                       pucProtocolPacket,
                       TAF_IPV6_ADDR_LEN);
            (*pucIpv6PcscfNum)++;
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_DecodeIpv6PcscfProtocolPkt: More than two IPv6 P-CSCF addresses present, Ignore the others.");
    }

    return;
}
#endif


VOS_UINT32 MN_APS_DecodeProtocolConfigPara(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usProtocolId;
    VOS_UINT8                           ucIpv4PcscfNum;
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           ucIpV6DnsNum;
    VOS_UINT8                           ucIpv6PcscfNum;
#endif

    usProtocolId                        = 0;
    ucIpv4PcscfNum                      = 0;
#if (FEATURE_ON == FEATURE_IPV6)
    ucIpV6DnsNum                        = 0;
    ucIpv6PcscfNum                      = 0;
#endif

    for (ulIndex = 0; ulIndex < pstProtoCfgOptions->ucProtocolIdsNum; ulIndex++)
    {
        /* ��ȡProtocol ID */
        usProtocolId  = pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolId[0] << 8;
        usProtocolId |= pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolId[1];

        MN_NORM_LOG1("MN_APS_DecodeProtocolConfigPara: Decode Protocol ID:",
                     usProtocolId);

        switch (usProtocolId)
        {
            case MN_APS_IPCP_PROTOCOL_ID:
                /* ����IPCP Protocol (0x8021) */
                if (VOS_OK != MN_APS_DecodeIpcpProtocolPkt(
                                pstPdpEntity,
                                pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolContents,
                                pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen))
                {
                    return VOS_ERR;
                }
                break;

            case TAF_APS_IPV4_PCSCF_PROTOCOL_ID:
                /* ����IPv4 P-CSCF (0x000C) */
                TAF_APS_DecodeIpv4PcscfProtocolPkt(
                    pstPdpEntity,
                    &ucIpv4PcscfNum,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolContents,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen);
                break;

#if (FEATURE_ON == FEATURE_IPV6)
            case MN_APS_IPV6_DNS_PROTOCOL_ID:
                /* ����IPv6 DNS (0x0003) */
                MN_APS_DecodeIpV6DnsProtocolPkt(
                    pstPdpEntity,
                    &ucIpV6DnsNum,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolContents,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen);
                break;

            case TAF_APS_IPV6_PCSCF_PROTOCOL_ID:
                /* ����IPv6 P-CSCF (0x0001) */
                TAF_APS_DecodeIpv6PcscfProtocolPkt(
                    pstPdpEntity,
                    &ucIpv6PcscfNum,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolContents,
                    pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen);
                break;
#endif

            default:
                MN_NORM_LOG1("MN_APS_DecodeProtocolConfigPara: Protocol ID not supported. Protocol ID:",
                             usProtocolId);
        }
    }

    return VOS_OK;
}
VOS_UINT32 MN_APS_UnpackProtocolOptionsList(
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU   *pstProtoCfgOptions,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
)
{
    VOS_UINT32                          ulPcoIndex;
    VOS_UINT32                          ulIndex;

    ulPcoIndex                          = 0;

    /*lint -e961*/
    /* ���Configuration protocol */
    pstProtoCfgOptions->ucConfigProtocol = pstSmPco->aucProtCfgOpt[ulPcoIndex++] & 0x7F;
    /*lint +e961*/
    pstProtoCfgOptions->ucProtocolIdsNum = 0;

    /* �������Protocol ID������ */
    for (ulIndex = 0; ((ulPcoIndex + 1) <= pstSmPco->ulPcoLen)
             && (ulIndex < MN_APS_MAX_PROTOCOL_ID_NUM); ulIndex++)
    {
        pstProtoCfgOptions->ucProtocolIdsNum++;
        /*lint -e961*/
        /* ���Protocol ID */
        pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolId[0]
                                            = pstSmPco->aucProtCfgOpt[ulPcoIndex++];
        pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolId[1]
                                            = pstSmPco->aucProtCfgOpt[ulPcoIndex++];

        /* ���Protocol length */
        pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen
                                            = pstSmPco->aucProtCfgOpt[ulPcoIndex++];
        /*lint +e961*/

        if ( ((ulPcoIndex - 1) + pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen)
             <= pstSmPco->ulPcoLen )
        {
            PS_MEM_CPY(pstProtoCfgOptions->stProtocolInfo[ulIndex].aucProtocolContents,
                       &pstSmPco->aucProtCfgOpt[ulPcoIndex],
                       pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen);

            ulPcoIndex += pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen;
        }
        else
        {
            /* ����������Protocol ID */
            pstProtoCfgOptions->stProtocolInfo[ulIndex].usProtocolLen = 0;
            ulPcoIndex = pstSmPco->ulPcoLen;
            ulPcoIndex++;
        }
    }

    return VOS_OK;
}
VOS_UINT32 MN_APS_UnpackPco(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_TAF_PROT_CFG_OPT_STRU           *pstSmPco
)
{
    MN_APS_PROTOCOL_CFG_OPTIONS_STRU    stProtocolCfgOptions;

    /* ���DNS��ص�bitOp��־ */
    PS_MEM_SET(&pstPdpEntity->PdpDns, 0x00, sizeof(VOS_UINT32));
    PS_MEM_SET(&pstPdpEntity->stPdpNbns, 0x00, sizeof(VOS_UINT32));
    PS_MEM_SET(&pstPdpEntity->stPdpPcscf, 0x00, sizeof(VOS_UINT32));
#if (FEATURE_ON == FEATURE_IPV6)
    PS_MEM_SET(&pstPdpEntity->stPdpIpV6Dns, 0x00, sizeof(VOS_UINT32));
    PS_MEM_SET(&pstPdpEntity->stPdpIpv6Pcscf, 0x00, sizeof(VOS_UINT32));
#endif

    /* ���Protocol Configuration�����б� */
    if (VOS_OK != MN_APS_UnpackProtocolOptionsList(&stProtocolCfgOptions,
                                                   pstSmPco))
    {
        MN_ERR_LOG("MN_APS_UnpackPco: Unpack PCO failed.");
        return VOS_ERR;
    }

    /* ����Protocol Configuration���� */
    if (VOS_OK != MN_APS_DecodeProtocolConfigPara(pstPdpEntity,
                                                  &stProtocolCfgOptions))
    {
        MN_ERR_LOG("MN_APS_UnpackPco: Decode PCO parameters failed.");
        return VOS_ERR;
    }

    return VOS_OK;

}

 /*******************************************************************************
 Function       : Aps_CheckOutPcoAuth()
 Description    : �����緵�ص�PCO�в����Ȩ��Ϣ��PPP����
 Calls          :
 Called         : Aps_PdpActRej()
 Date Accessed  :
 Date Update    :
 Input          : pSmPco
 Output         : pAuthPcoPPP
 Return         : TAF_APS_FAIL ����ִ��ʧ��
                  TAF_APS_SUCC ����ִ�гɹ�
Others          :
*******************************************************************************/
VOS_UINT32  Aps_CheckOutPcoAuth(        SM_TAF_PROT_CFG_OPT_STRU        *pSmPco,
                                        APS_PCO_AUTH_PPP_ST    *pAuthPcoPPP)
{
    VOS_UINT8                           ucLocation = 0;


    ucLocation++;                       /*����PCOͷ����PCP type 0x80*/


    /*�������Ҫ�����Э���Ƿ�AUTHЭ��,��������������*/
    while( (VOS_UINT32)(ucLocation + 1)  < pSmPco->ulPcoLen)
    {
        if ( ((0xC0 != pSmPco->aucProtCfgOpt[ucLocation])
               ||(0x23 != pSmPco->aucProtCfgOpt[ucLocation + 1]))
             &&((0xC2 != pSmPco->aucProtCfgOpt[ucLocation])
               ||(0x23 != pSmPco->aucProtCfgOpt[ucLocation + 1])))
        {
            ucLocation  += 2;           /*����Э����2���ֽ� */
            ucLocation  += (pSmPco->aucProtCfgOpt[ucLocation] + 1);
        }
        else
        {   /*����IPCP,������ѭ��*/
            break;
        }
    }

    /*��û��AUTHЭ��,���˳�����*/
    if ( (VOS_UINT32)(ucLocation + 1) >= pSmPco->ulPcoLen )
    {
        APS_NORM_LOG("No IPCP in PCO.");
        return  TAF_APS_FAIL;
    }

    /*��û�������������洦��AUTH����*/
    ucLocation          += 2;           /*����Э����2���ֽ� */

    pAuthPcoPPP->usLen  = (VOS_UINT16)pSmPco->aucProtCfgOpt[ucLocation];

    ucLocation          += 1;           /*����������1���ֽ� */
    pAuthPcoPPP->pProtIdCont    = &(pSmPco->aucProtCfgOpt[ucLocation]);


    return  TAF_APS_SUCC;
}

/*******************************************************************************
 Function       : Aps_CheckOutPcoOneIpcp()
 Description    : ��IPCP�����в��һ�������NAK, ACK, REJ����
 Calls          :
 Called         : Aps_PdpActRej()
 Date Accessed  :
 Date Update    :
 Input          : pIpcpPcpPPP
                  ucPcoType :REQ,ACK,NAK,REJ
 Output         : pOneIpcp
 Return         : TAF_APS_FAIL
                  TAF_APS_SUCC
 Others         :
*******************************************************************************/
VOS_UINT32  Aps_CheckOutPcoOneIpcp(     APS_PCO_IPCP_PPP_ST    *pIpcpPcpPPP,
                                        VOS_UINT8               ucPcoCode,
                                        APS_PCO_PPP_ST         *pOneIpcp)
{
    VOS_UINT8                           ucLocation = 0;


    /*�������Ҫ�����code�Ƿ������code,��������������*/
    while( (ucLocation + 1)  < pIpcpPcpPPP->usLen)
    {
        if ((ucPcoCode != pIpcpPcpPPP->pProtIdCont[ucLocation]))
        {   /*�����������CODE*/

            /*IPV4���ȵ������ֽ���,ֻ�е��ֽ���Ч,������CODEЭ���PPP����*/
            ucLocation  += (pIpcpPcpPPP->pProtIdCont[ucLocation+3]);
        }
        else
        {   /*���������CODE,������ѭ��*/
            break;
        }
    }

    /*��û�������CODEЭ��,���˳�����*/
    if ( (ucLocation + 1) >= pIpcpPcpPPP->usLen )
    {
        APS_NORM_LOG("No this CODE in PCO.");
        return  TAF_APS_FAIL;
    }

    /*��û�������������洦��IPCP����*/
    /*IPV4���ȵ������ֽ��У�ֻ�е��ֽ���Ч*/
    pOneIpcp->usLen = (VOS_UINT16)pIpcpPcpPPP->pProtIdCont[ucLocation+3];

    pOneIpcp->pProtIdCont
                    = &(pIpcpPcpPPP->pProtIdCont[ucLocation]);

    return  TAF_APS_SUCC;
}


/*******************************************************************************
 Function       : Aps_CheckOutIpcpIpAddr()
 Description    : ��һ�������NAK, ACK, REJIPCP�����в�����е�IPADDR��PPP����
 Calls          :
 Called         : Aps_PdpActRej()
 Date Accessed  :
 Date Update    :
 Input          : pIpcpPcpPPP
                  ucIpcpId :    #define APS_PPP_IP_ADDR_ID      0x03
                                #define APS_PPP_PRI_DNS_ID      0x81
                                #define APS_PPP_SEC_DNS_ID      0x83
 Output         : pPppId
 Return         : TAF_APS_FAIL
                  TAF_APS_SUCC
 Others         :
*******************************************************************************/
VOS_UINT32  Aps_CheckOutOneIpcpOneId(   APS_PCO_IPCP_PPP_ST    *pOneIpcp,
                                        VOS_UINT8               ucIpcpId,
                                        APS_PPP_ID_ST          *pPppId)
{
    VOS_UINT8                           ucLoc = 0;

    ucLoc       += 4;                   /*����CODE1�ֽ�,Identifier1�ֽ�,����2�ֽ�*/


    /*�������Ҫ�����code�Ƿ������code,��������������*/
    while( (ucLoc + 1)  < pOneIpcp->usLen)
    {
        if ((ucIpcpId != pOneIpcp->pProtIdCont[ucLoc]))
        {   /*�����������ID*/

            /*IPV4���ȵ�1���ֽ���,������ID��PPP����*/
            ucLoc  += (pOneIpcp->pProtIdCont[ucLoc+1]);
        }
        else
        {   /*���������ID,������ѭ��*/
            break;
        }
    }

    /*��û�������IDЭ��,���˳�����*/
    if ( (ucLoc + 1) >= pOneIpcp->usLen )
    {
        APS_NORM_LOG("No this ID in IPCP.");
        return  TAF_APS_FAIL;
    }

    /*��û�������������洦��IPCP����*/
    /*IPV4���ȵ�1���ֽ���*/
    pPppId->usLen = (VOS_UINT16)pOneIpcp->pProtIdCont[ucLoc+1];

    pPppId->pProtIdCont
                    = &(pOneIpcp->pProtIdCont[ucLoc]);

    return  TAF_APS_SUCC;
}

/*******************************************************************************
 Function       : Aps_PPPDns2ApsDns()
 Description    : ��PPP DNS�����в�APS״̬����DNS�ṹ��
 Calls          :
 Called         :
 Date Accessed  :
 Date Update    :
 Input          : pOneIpcp
 Output         : pPdpDns
 Return         : TAF_APS_FAIL
                  TAF_APS_SUCC
 Others         :
*******************************************************************************/
VOS_VOID    Aps_PPPDns2ApsDns(          APS_PCO_PPP_ST     *pOneIpcp,
                                        APS_PDP_DNS_ST     *pPdpDns)
{
    VOS_UINT8                           ucLoc = 0;
    /*lint -e961*/
    if (APS_PPP_PRI_DNS_ID == pOneIpcp->pProtIdCont[ucLoc])
    {   /*��DNS*/
        ucLoc   += 2;                   /*����PriDns��ʶ1�ֽںͳ���1�ֽ�*/
        pPdpDns->OP_PriDns              = VOS_TRUE;
        pPdpDns->aucPriDns[0]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucPriDns[1]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucPriDns[2]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucPriDns[3]           = pOneIpcp->pProtIdCont[ucLoc++];
    }
    else if (APS_PPP_SEC_DNS_ID == pOneIpcp->pProtIdCont[ucLoc])
    {   /*��DNS*/
        ucLoc   += 2;                   /*����SecDns��ʶ1�ֽںͳ���1�ֽ�*/
        pPdpDns->OP_SecDns              = VOS_TRUE;
        pPdpDns->aucSecDns[0]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucSecDns[1]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucSecDns[2]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpDns->aucSecDns[3]           = pOneIpcp->pProtIdCont[ucLoc++];
    }
    else
    {
        APS_NORM_LOG("Not DNS PPP !");
    }
    /*lint +e961*/
    return;
}


/*******************************************************************************
 Function       : Aps_PPPNbns2ApsNbns()
 Description    : ��PPP NBNS�����в�APS״̬����NBNS�ṹ��
 Calls          :
 Called         :
 Date Accessed  :
 Date Update    :
 Input          : pOneIpcp
 Output         : pPdpNbns
 Return         : TAF_APS_FAIL
                  TAF_APS_SUCC
 Others         :
*******************************************************************************/
VOS_VOID    Aps_PPPNbns2ApsNbns(          APS_PCO_PPP_ST     *pOneIpcp,
                                        APS_PDP_NBNS_ST     *pPdpNbns)
{
    VOS_UINT8                           ucLoc = 0;
    /*lint -e961*/
    if ( APS_PPP_PRI_NBNS_ID == pOneIpcp->pProtIdCont[ucLoc])
    {   /*��NBNS*/
        ucLoc   += 2;                   /*����PriNbns��ʶ1�ֽںͳ���1�ֽ�*/
        pPdpNbns->OP_PriNbns              = VOS_TRUE;
        pPdpNbns->aucPriNbns[0]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucPriNbns[1]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucPriNbns[2]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucPriNbns[3]           = pOneIpcp->pProtIdCont[ucLoc++];
    }
    else if ( APS_PPP_SEC_NBNS_ID == pOneIpcp->pProtIdCont[ucLoc])
    {   /*��NBNS*/
        ucLoc   += 2;                   /*����SecNbns��ʶ1�ֽںͳ���1�ֽ�*/
        pPdpNbns->OP_SecNbns              = VOS_TRUE;
        pPdpNbns->aucSecNbns[0]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucSecNbns[1]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucSecNbns[2]           = pOneIpcp->pProtIdCont[ucLoc++];
        pPdpNbns->aucSecNbns[3]           = pOneIpcp->pProtIdCont[ucLoc++];
    }
    else
    {
        APS_NORM_LOG("Not NBNS PPP !");
    }
    /*lint +e961*/
    return;
}




/*******************************************************************************
 Function       : Aps_PPPAddr2ApsAddr()
 Description    : ��PPP DNS�����в�APS״̬����DNS�ṹ��
 Calls          :
 Called         :
 Date Accessed  :
 Date Update    :
 Input          : pOneIpcp
 Output         : pPdpDns
 Return         : TAF_APS_FAIL
                  TAF_APS_SUCC
 Others         :
*******************************************************************************/
VOS_VOID    Aps_PPPAddr2ApsAddr(        APS_PCO_PPP_ST     *pOneIpcp,
                                        VOS_UINT8          *pIpAddr)
{
    VOS_UINT8                           ucLoc = 0;
    /*lint -e961*/
    /*IP ADDR*/
    if ( 0x03 == pOneIpcp->pProtIdCont[ucLoc])
    {
        if ( 0 != pOneIpcp->pProtIdCont[ucLoc+1])
        {   /*�����IPADDR*/
            ucLoc   += 2;                   /*����PriDns��ʶ1�ֽںͳ���1�ֽ�*/
            pIpAddr[0]                  = pOneIpcp->pProtIdCont[ucLoc++];
            pIpAddr[1]                  = pOneIpcp->pProtIdCont[ucLoc++];
            pIpAddr[2]                  = pOneIpcp->pProtIdCont[ucLoc++];
            pIpAddr[3]                  = pOneIpcp->pProtIdCont[ucLoc++];
        }
    }
    /*lint +e961*/
    return;
}

/*****************************************************************************
 Prototype      : Aps_UnPackSmAddr
 Description    : ��SM������ADDR�ṹ�����APS�����STRUCT��,����PDPTYPE��ADDR
 Input          : pSmAddr
 Output         : pApsAddr
 Return Value   :
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_DetachSmAddrStru (
    SM_TAF_PDP_ADDR_STRU               *pSmAddr,
    APS_PDP_ADDR_ST                    *pApsAddr
)
{
    VOS_UINT8                           ucPdpOrgan;

    if((VOS_NULL == pSmAddr) || (VOS_NULL == pApsAddr))
    {
        APS_WARN_LOG("ERROR! The input pointer parameter can not be NULL! Aps_DetachSmAddrStru()");
        return(TAF_APS_FAIL);
    }

    /* ����PDPORGAN */
    ucPdpOrgan = (pSmAddr->aucPdpAddr[0]) & 0x0F;
    switch(ucPdpOrgan)
    {
        case APS_ADDR_ORGAN_ETSI:
        case APS_ADDR_ORGAN_IETF:
        case APS_ADDR_ORGAN_EMPTY_PDP_TYPE:
                pApsAddr->ucPdpTypeOrgan = (pSmAddr->aucPdpAddr[0]) & 0x0F;
                break;
        default:
            APS_WARN_LOG("ERROR! Input Parameter error! Aps_DetachSmAddrStru()");
            return(TAF_APS_FAIL);
    }


    /* ����PDPTYPE */
    switch (pSmAddr->aucPdpAddr[1])
    {
        /* ppp */
        case APS_PDP_TYPE_NUM_PPP  :
            pApsAddr->ucPdpTypeNum = APS_ADDR_PPP;
            break;

        /* IPV4 */
        case APS_PDP_TYPE_NUM_IPV4 :
            pApsAddr->ucPdpTypeNum = APS_ADDR_STATIC_IPV4;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        /* IPV6 */
        case MN_APS_PDP_TYPE_NUM_IPV6:
            pApsAddr->ucPdpTypeNum = MN_APS_ADDR_IPV6;
            break;

        /* IPV4V6 */
        case MN_APS_PDP_TYPE_NUM_IPV4V6:
            pApsAddr->ucPdpTypeNum = MN_APS_ADDR_IPV4V6;
            break;
#endif

        default:
            /* All other values shall be interpreted as IPv4 address */
            pApsAddr->ucPdpTypeNum = APS_ADDR_STATIC_IPV4;
            break;
    }

    /*
    If PDP type number indicates IPv4, the Address information in octet 5 to
    octet 8 contains the IPv4 address. Bit 8 of octet 5 represents the most
    significant bit of the IP address and bit 1 of octet 8 the least significant
    bit.
    If PDP type number indicates IPv6, the Address information in octet 5 to octet
    20 contains the IPv6 address. Bit 8 of octet 5 represents the most significant
    bit of the IP address and bit 1 of octet 20 the least significant bit.
    If PDP type number indicates IPv4v6:
    The Address information in octet 5 to octet 8 contains the IPv4 address. Bit
    8 of octet 5 represents the most significant bit of the IP address and bit 1
    of octet 8 the least significant bit.
    The Address information in octet 9 to octet 24 contains the IPv6 address. Bit
    8 of octet 9 represents the most significant bit of the IP address and bit 1
    of octet 24 the least significant bit.
    If PDP type number indicates IPv4 or IPv4v6 and DHCPv4 is to be used to allocate
    the IPv4 address, the IPv4 address shall be coded as 0.0.0.0.
    */

    /* �����IPV4, �򿽱�4���ֽڵ�IP ��ַ */
    if (APS_ADDR_STATIC_IPV4 == pApsAddr->ucPdpTypeNum)
    {
        PS_MEM_CPY(pApsAddr->aucIpAddr,
                   &(pSmAddr->aucPdpAddr[2]),
                   TAF_IPV4_ADDR_LEN);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����IPV6, �򿽱�16���ֽڵ�IP ��ַ */
    if (MN_APS_ADDR_IPV6 == pApsAddr->ucPdpTypeNum)
    {
        PS_MEM_CPY(pApsAddr->aucIpV6Addr,
                   &(pSmAddr->aucPdpAddr[2]),
                   TAF_IPV6_ADDR_LEN);
    }

    /* �����IPV4V6, �򿽱�4���ֽڵ�IPV4 ��ַ ���ٿ���IPV6��ַ*/
    if (MN_APS_ADDR_IPV4V6 == pApsAddr->ucPdpTypeNum)
    {
        PS_MEM_CPY(pApsAddr->aucIpAddr,
                   &(pSmAddr->aucPdpAddr[2]),
                   TAF_IPV4_ADDR_LEN);

        PS_MEM_CPY(pApsAddr->aucIpV6Addr,
                   &(pSmAddr->aucPdpAddr[2 + TAF_IPV4_ADDR_LEN]),
                   TAF_IPV6_ADDR_LEN);

    }
#endif

    return(TAF_APS_SUCC);

}
VOS_VOID    Aps_DetachSmApn  (  SM_TAF_APN_STRU*      pSmApn,
                                APS_PDP_APN_ST*         pApsApn )
{

    /* APN�ĳ��� */
    pApsApn->ucLength = (VOS_UINT8)pSmApn->ulApnLen;
    if ( pApsApn->ucLength >= APS_MAX_LENGTH_OF_APN)
    {
        pApsApn->ucLength = APS_MAX_LENGTH_OF_APN - 1;
    }

    /* ����APN */
    PS_MEM_CPY(       pApsApn->aucValue,
                      pSmApn->aucApnAddr,
                      pApsApn->ucLength   );

    return;
}


VOS_UINT32 Aps_CompareQos_ForDelayClass(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucDelayClass )
    {
        if(pNetNegotQos->ucDelayClass > pUeMinQos->ucDelayClass)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForReliabClass(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucReliabClass)
    {
        if(pNetNegotQos->ucReliabClass > pUeMinQos->ucReliabClass)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForPeakThrough(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucPeakThrough)
    {
        if(pNetNegotQos->ucPeakThrough < pUeMinQos->ucPeakThrough)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForPrecedenceClass(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucPrecedenceClass)
    {
        if(pNetNegotQos->ucPrecedenceClass > pUeMinQos->ucPrecedenceClass)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForTrafficClass(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucTrafficClass)
    {
        if(pNetNegotQos->ucTrafficClass > pUeMinQos->ucTrafficClass)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}



VOS_UINT32 Aps_CompareQos_ForDeliverOrder(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucDeliverOrder )
    {
        if(pNetNegotQos->ucDeliverOrder != pUeMinQos->ucDeliverOrder)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForDeliverOfErrSdu(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucDeliverOfErrSdu )
    {
        if(pNetNegotQos->ucDeliverOfErrSdu < pUeMinQos->ucDeliverOfErrSdu)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForMaximSduSize(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucMaximSduSize )
    {
        if(pNetNegotQos->ucMaximSduSize < pUeMinQos->ucMaximSduSize)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForSduErrRatio(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucSduErrRatio )
    {
        if(SDU_ERR_RATIO_HIGHEST == pNetNegotQos->ucSduErrRatio)
        {
            if(SDU_ERR_RATIO_HIGHEST != pUeMinQos->ucSduErrRatio)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
        else/* ��������, ��ԽС, ����Ĵ�SDU��Խ�� */
        {
            if(pNetNegotQos->ucSduErrRatio < pUeMinQos->ucSduErrRatio)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }

    return APS_QOS_UP_TO_MIN;
}
VOS_UINT32 Aps_CompareQos_ForTransDelay(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ((APS_QOS_TRAFFIC_CLASS_INTERACTIVE != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_TRAFFIC_CLASS_BACKGROUND != pNetNegotQos->ucTrafficClass))
    {
        if ( 0 != pUeMinQos->ucTransDelay )
        {
            if(pNetNegotQos->ucTransDelay > pUeMinQos->ucTransDelay)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForTrafficHandlePriority(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ((APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_TRAFFIC_CLASS_STREAMING != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_TRAFFIC_CLASS_BACKGROUND != pNetNegotQos->ucTrafficClass))
    {
        if (0 != pUeMinQos->ucTraffHandlPrior)
        {
            if(pNetNegotQos->ucTraffHandlPrior > pUeMinQos->ucTraffHandlPrior)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForMaxBitRateForUp(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
    if ( 0 != pUeMinQos->ucMaxBitRateForUp )
    {
        if(pNetNegotQos->ucMaxBitRateForUp < pUeMinQos->ucMaxBitRateForUp)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }
    #else
    if ( 0 == pUeMinQos->ucMaxBitRateForUpExt )
    {
        if ( 0 == pNetNegotQos->ucMaxBitRateForUpExt )
        {
            if ( 0 != pUeMinQos->ucMaxBitRateForUp )
            {
                if(pNetNegotQos->ucMaxBitRateForUp < pUeMinQos->ucMaxBitRateForUp)
                {
                    return APS_QOS_NOT_UP_TO_MIN;
                }
            }
        }
        else
        {
            /* Э�̵�Qos��������б����ʱ�Ȼ����pUeMinQos��������б����� */
        }
    }
    else
    {
        if ( 0 == pNetNegotQos->ucMaxBitRateForUpExt )
        {
            /* ��������£�Э�̵�Qos��������б����ʱ�Ȼ����pUeMinQos��������б����� */
            return APS_QOS_NOT_UP_TO_MIN;
        }
        else
        {
            if ( pNetNegotQos->ucMaxBitRateForUpExt < pUeMinQos->ucMaxBitRateForUpExt )
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }
    #endif

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForMaxBitRateForDown(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
    if ( 0 != pUeMinQos->ucMaxBitRateForDown )
    {
        if(pNetNegotQos->ucMaxBitRateForDown < pUeMinQos->ucMaxBitRateForDown)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }
    #else
    if ( 0 == pUeMinQos->ucMaxBitRateForDownExt )
    {
        if ( 0 == pNetNegotQos->ucMaxBitRateForDownExt )
        {
            if ( 0 != pUeMinQos->ucMaxBitRateForDown )
            {
                if(pNetNegotQos->ucMaxBitRateForDown < pUeMinQos->ucMaxBitRateForDown)
                {
                    return APS_QOS_NOT_UP_TO_MIN;
                }
            }
        }
        else
        {
            /* Э�̵�Qos��������б����ʱ�Ȼ����pUeMinQos��������б����� */
        }
    }
    else
    {
        if ( 0 == pNetNegotQos->ucMaxBitRateForDownExt )
        {
            /* ��������£�Э�̵�Qos��������б����ʱ�Ȼ����pUeMinQos��������б����� */
            return APS_QOS_NOT_UP_TO_MIN;
        }
        else
        {
            if ( pNetNegotQos->ucMaxBitRateForDownExt < pUeMinQos->ucMaxBitRateForDownExt )
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }
    #endif

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForResidualBer(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( 0 != pUeMinQos->ucResidualBer )
    {
        if(pNetNegotQos->ucResidualBer < pUeMinQos->ucResidualBer)
        {
            return APS_QOS_NOT_UP_TO_MIN;
        }
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForGuarantBitRateForUp(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ((APS_QOS_TRAFFIC_CLASS_INTERACTIVE != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_TRAFFIC_CLASS_BACKGROUND != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_MAX_BITRATE_0KBPS != pNetNegotQos->ucMaxBitRateForUp))
    {
        #if(PS_UE_REL_VER < PS_PTL_VER_R7)
        if ( 0 != pUeMinQos->ucGuarantBitRateForUp )
        {
            if(pNetNegotQos->ucGuarantBitRateForUp < pUeMinQos->ucGuarantBitRateForUp)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
        #else
        if ( 0 == pUeMinQos->ucGuarantBitRateForUpExt )
        {
            if ( 0 == pNetNegotQos->ucGuarantBitRateForUpExt )
            {
                if ( 0 != pUeMinQos->ucGuarantBitRateForUp )
                {
                    if(pNetNegotQos->ucGuarantBitRateForUp < pUeMinQos->ucGuarantBitRateForUp)
                    {
                        return APS_QOS_NOT_UP_TO_MIN;
                    }
                }
            }
            else
            {
                /* Э�̵�Qos�Ŀɱ�֤���б����ʱ�Ȼ����pUeMinQos�Ŀɱ�֤���б����� */
            }
        }
        else
        {
            if ( 0 == pNetNegotQos->ucGuarantBitRateForUpExt )
            {
                /* ��������£�Э�̵�Qos�Ŀɱ�֤���б����ʱ�Ȼ����pUeMinQos�Ŀɱ�֤���б����� */
                return APS_QOS_NOT_UP_TO_MIN;
            }
            else
            {
                if ( pNetNegotQos->ucGuarantBitRateForUpExt < pUeMinQos->ucGuarantBitRateForUpExt )
                {
                    return APS_QOS_NOT_UP_TO_MIN;
                }
            }
        }
        #endif
    }

    return APS_QOS_UP_TO_MIN;
}


VOS_UINT32 Aps_CompareQos_ForGuarantBitRateForDown(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ((APS_QOS_TRAFFIC_CLASS_INTERACTIVE != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_TRAFFIC_CLASS_BACKGROUND != pNetNegotQos->ucTrafficClass)
         && (APS_QOS_MAX_BITRATE_0KBPS != pNetNegotQos->ucMaxBitRateForDown))
    {
        #if(PS_UE_REL_VER < PS_PTL_VER_R5)
        if ( 0 != pUeMinQos->ucGuarantBitRateForDown)
        {
            if(pNetNegotQos->ucGuarantBitRateForDown < pUeMinQos->ucGuarantBitRateForDown)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
        #else
        if ( 0 == pUeMinQos->ucGuarantBitRateForDownExt )
        {
            if ( 0 == pNetNegotQos->ucGuarantBitRateForDownExt )
            {
                if ( 0 != pUeMinQos->ucGuarantBitRateForDown )
                {
                    if(pNetNegotQos->ucGuarantBitRateForDown < pUeMinQos->ucGuarantBitRateForDown)
                    {
                        return APS_QOS_NOT_UP_TO_MIN;
                    }
                }
            }
            else
            {
                /* Э�̵�Qos�Ŀɱ�֤���б����ʱ�Ȼ����pUeMinQos�Ŀɱ�֤���б����� */
            }
        }
        else
        {
            if ( 0 == pNetNegotQos->ucGuarantBitRateForDownExt )
            {
                /* ��������£�Э�̵�Qos�Ŀɱ�֤���б����ʱ�Ȼ����pUeMinQos�Ŀɱ�֤���б����� */
                return APS_QOS_NOT_UP_TO_MIN;
            }
            else
            {
                if ( pNetNegotQos->ucGuarantBitRateForDownExt < pUeMinQos->ucGuarantBitRateForDownExt )
                {
                    return APS_QOS_NOT_UP_TO_MIN;
                }
            }
        }
        #endif
    }

    return APS_QOS_UP_TO_MIN;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_CompareQos_ForSrcStatisticsDescriptor
 ��������  : Aps_CompareQos��Ȧ���Ӷ�
 �������  : pNetNegotQos
             pUeMinQos
 �������  : pucQosOkOrNot,QOS�Ƿ�����MINҪ��
 �� �� ֵ  : APS_QOS_NOT_UP_TO_MIN
             APS_QOS_UP_TO_MIN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_CompareQos_ForSrcStatisticsDescriptor(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( (APS_QOS_TRAFFIC_CLASS_INTERACTIVE != pNetNegotQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND  != pNetNegotQos->ucTrafficClass))
    {
        if ( 0 != pUeMinQos->ucSrcStatisticsDescriptor)
        {
            if( pNetNegotQos->ucSrcStatisticsDescriptor < pUeMinQos->ucSrcStatisticsDescriptor)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }

    return APS_QOS_UP_TO_MIN;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_CompareQos_ForSignallingIndication
 ��������  : Aps_CompareQos��Ȧ���Ӷ�
 �������  : pNetNegotQos
             pUeMinQos
 �������  : pucQosOkOrNot,QOS�Ƿ�����MINҪ��
 �� �� ֵ  : APS_QOS_NOT_UP_TO_MIN
             APS_QOS_UP_TO_MIN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_CompareQos_ForSignallingIndication(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos
)
{
    if ( (APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL  != pNetNegotQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_STREAMING       != pNetNegotQos->ucTrafficClass)
      && (APS_QOS_TRAFFIC_CLASS_BACKGROUND      != pNetNegotQos->ucTrafficClass))
    {
        if ( 0 != pUeMinQos->ucSignallingIndication)
        {
            if( pNetNegotQos->ucSignallingIndication < pUeMinQos->ucSignallingIndication)
            {
                return APS_QOS_NOT_UP_TO_MIN;
            }
        }
    }

    return APS_QOS_UP_TO_MIN;
}



VOS_UINT32 Aps_CompareQos(
    APS_PDP_QOS_STRU                    *pNetNegotQos,
    APS_PDP_QOS_STRU                    *pUeMinQos,
    VOS_UINT8                           *pucQosOkOrNot
)
{
    VOS_UINT32  ulCmpResult;

    *pucQosOkOrNot = APS_QOS_NOT_UP_TO_MIN;

    /* �Ƚ�pNetNegotQos �� pUeMinQos��ָ������¸���:*/
    /* ucDelayClass */
    ulCmpResult = Aps_CompareQos_ForDelayClass(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucReliabClass */
    ulCmpResult = Aps_CompareQos_ForReliabClass(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucPeakThrough */
    ulCmpResult = Aps_CompareQos_ForPeakThrough(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /*Precedence class*/
    ulCmpResult = Aps_CompareQos_ForPrecedenceClass(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* Mean throughput  */
    /* ����31
    if (  )
    {
        if(pNetNegotQos->ucMeanThrough < pUeMinQos->ucMeanThrough)
        {
            *pucQosOkOrNot = APS_QOS_NOT_UP_TO_MIN;
            return(TAF_APS_SUCC);
        }
    }
    */

    /* ucTrafficClass */
    ulCmpResult = Aps_CompareQos_ForTrafficClass(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucDeliverOrder */
    ulCmpResult = Aps_CompareQos_ForDeliverOrder(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucDeliverOfErrSdu */
    ulCmpResult = Aps_CompareQos_ForDeliverOfErrSdu(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucMaximSduSize */
    ulCmpResult = Aps_CompareQos_ForMaximSduSize(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucMaxBitRateForUp */
    ulCmpResult = Aps_CompareQos_ForMaxBitRateForUp(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucMaxBitRateForDown */
    ulCmpResult = Aps_CompareQos_ForMaxBitRateForDown(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucResidualBer */
    ulCmpResult = Aps_CompareQos_ForResidualBer(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucSduErrRatio,ע�� 7����Ĵ�SDU����� */
    ulCmpResult = Aps_CompareQos_ForSduErrRatio(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucTransDelay */
    /* 24.008:The Transfer delay value is ignored if the Traffic Class is Interactive class or Background class */
    ulCmpResult = Aps_CompareQos_ForTransDelay(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /*  ucTrafficHandlePriority */
    /* 24.008: The Traffic handling priority value is ignored if the Traffic
       Class is Conversational class, Streaming class or Background class */
    ulCmpResult = Aps_CompareQos_ForTrafficHandlePriority(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucGuarantBitRateForUp */
    /* 24.008: The Guaranteed bit rate for uplink value is ignored if the Traffic Class
        is Interactive class or Background class, or Maximum bit rate for uplink
        is set to 0 kbps. */
    ulCmpResult = Aps_CompareQos_ForGuarantBitRateForUp(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* ucGuarantBitRateForDown */
    /* 24.008: The Guaranteed bit rate for downlink value is ignored if the Traffic Class
       is Interactive class or Background class, or Maximum bit rate for downlink
       is set to 0 kbps. */
    ulCmpResult = Aps_CompareQos_ForGuarantBitRateForDown(pNetNegotQos, pUeMinQos);
    if (APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return(TAF_APS_SUCC);
    }

    /* Added by w00316404 for M project A characeristic AT part, 2015-4-7, Begin */
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    
    /* 24.008:The Source Statistics Descriptor value is ignored if the Traffic Class is 
    Interactive class or Background class */
    ulCmpResult = TAF_APS_CompareQos_ForSrcStatisticsDescriptor(pNetNegotQos, pUeMinQos);
    if ( APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return TAF_APS_SUCC;
    }

    /* 24.008:The Signalling Indication value is ignored if the Traffic Class is 
    Conversational class or Streaming class or Background class */
    ulCmpResult = TAF_APS_CompareQos_ForSignallingIndication(pNetNegotQos, pUeMinQos);
    if ( APS_QOS_NOT_UP_TO_MIN == ulCmpResult)
    {
        return TAF_APS_SUCC;
    }
   
    #endif
    /* Added by w00316404 for M project A characeristic AT part, 2015-4-7, End */

    /* ����MINQOSҪ��, ���ñ�־ */
    *pucQosOkOrNot = APS_QOS_UP_TO_MIN;

    return(TAF_APS_SUCC);
}/*end of Function */

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
