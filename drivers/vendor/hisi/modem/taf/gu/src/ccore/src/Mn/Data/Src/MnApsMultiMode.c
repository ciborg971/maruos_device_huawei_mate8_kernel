

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "RabmTafInterface.h"
#include "Taf_Aps.h"
#include "TafApsCtx.h"
#include "TafApsSndSm.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "PsTypeDef.h"
#include "MnApsComm.h"
#include "MnApsMultiMode.h"
#include "TafLog.h"
#include "TafApsComFunc.h"
#include "TafApsDecode.h"
#include "TafSdcLib.h"

#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_MN_APS_MULTI_MODE_C


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID MN_APS_FillEsmPdpInfoIndOptActivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    /* ��д TI */
    MN_APS_FillEsmPdpInfoTransId(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д NSAPI */
    MN_APS_FillEsmPdpInfoNsapi(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д CID */
    MN_APS_FillEsmPdpInfoCid(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д LINKED NSAPI */
    MN_APS_FillEsmPdpInfoLinkedNsapi(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PDP ADDRESS */
    MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д QOS */
    MN_APS_FillEsmPdpInfoPdpQos(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д APN */
    MN_APS_FillEsmPdpInfoApn(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PACKET FILTER */
    MN_APS_FillEsmPdpInfoPf(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PCO IPV4  */
    MN_APS_FillEsmPdpInfoPcoIpv4(pstEsmPdpInfoInd, pstPdpEntity);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��д PCO IPV6  */
    MN_APS_FillEsmPdpInfoPcoIpv6(pstEsmPdpInfoInd, pstPdpEntity);
#endif

}


VOS_VOID MN_APS_FillEsmPdpInfoIndOptModifyPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    /* ��д TI */
    MN_APS_FillEsmPdpInfoTransId(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д NSAPI */
    MN_APS_FillEsmPdpInfoNsapi(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д CID */
    MN_APS_FillEsmPdpInfoCid(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д LINKED NSAPI */
    MN_APS_FillEsmPdpInfoLinkedNsapi(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PDP ADDRESS */
    MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д QOS */
    MN_APS_FillEsmPdpInfoPdpQos(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д APN */
    MN_APS_FillEsmPdpInfoApn(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PACKET FILTER */
    MN_APS_FillEsmPdpInfoPf(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д PCO IPV4 */
    MN_APS_FillEsmPdpInfoPcoIpv4(pstEsmPdpInfoInd, pstPdpEntity);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��д PCO IPV6  */
    MN_APS_FillEsmPdpInfoPcoIpv6(pstEsmPdpInfoInd, pstPdpEntity);
#endif

}


VOS_VOID MN_APS_FillEsmPdpInfoIndOptDeactivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    /* ��д TI */
    MN_APS_FillEsmPdpInfoTransId(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д NSAPI */
    MN_APS_FillEsmPdpInfoNsapi(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д CID */
    MN_APS_FillEsmPdpInfoCid(pstEsmPdpInfoInd, pstPdpEntity);

    /* ��д LINKED NSAPI */
    MN_APS_FillEsmPdpInfoLinkedNsapi(pstEsmPdpInfoInd, pstPdpEntity);
}


VOS_UINT32 MN_APS_FillEsmPdpInfoIndPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
)
{
    switch (enPdpOption)
    {
        case SM_ESM_PDP_OPT_ACTIVATE:
            MN_APS_FillEsmPdpInfoIndOptActivatePara(pstEsmPdpInfoInd, pstPdpEntity);
            break;

        case SM_ESM_PDP_OPT_MODIFY:
            MN_APS_FillEsmPdpInfoIndOptModifyPara(pstEsmPdpInfoInd, pstPdpEntity);
            break;

        case SM_ESM_PDP_OPT_DEACTIVATE:
            MN_APS_FillEsmPdpInfoIndOptDeactivatePara(pstEsmPdpInfoInd, pstPdpEntity);
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID MN_APS_FillSmBearerActivateIndPara(
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstSmBearerActivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{

    /* ��д TI */
    pstSmBearerActivateInd->stTransId.ucTiFlag  = pstPdpEntity->stTransId.ucTiFlag;
    pstSmBearerActivateInd->stTransId.ucTiValue = pstPdpEntity->stTransId.ucTiValue;

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pstSmBearerActivateInd->ucConnectId       = pstPdpEntity->ucPdpId;


    /* ��д NSAPI */
    pstSmBearerActivateInd->ucNsapi           = pstPdpEntity->ucNsapi;

    /* ��д PDP ADDRESS */
    (VOS_VOID)Aps_PackSmAddr(&(pstPdpEntity->PdpAddr.ucPdpTypeNum),
                   pstPdpEntity->PdpAddr.aucIpAddr,
                   &pstSmBearerActivateInd->stPdpAddr);

    /* ��д APN */
    if (VOS_TRUE == pstPdpEntity->PdpApnFlag)
    {
        pstSmBearerActivateInd->bitOpApn          = VOS_TRUE;
        pstSmBearerActivateInd->stApn.ulApnLen    = pstPdpEntity->PdpApn.ucLength;
        PS_MEM_CPY(pstSmBearerActivateInd->stApn.aucApnAddr,
                   pstPdpEntity->PdpApn.aucValue,
                   pstPdpEntity->PdpApn.ucLength);
    }

    /* ��д QOS */
    if (VOS_TRUE == pstPdpEntity->PdpQosFlag)
    {
        pstSmBearerActivateInd->bitOpPdpQos       = VOS_TRUE;
        Aps_PackSmQos(&pstPdpEntity->PdpQos,
                      &pstSmBearerActivateInd->stNegQos);
    }

    /* ��д PDP TYPE: PRI or SEC */
    if (APS_PDP_ACT_SEC == pstPdpEntity->ActType)
    {
        pstSmBearerActivateInd->bitOpLinkedNsapi  = VOS_TRUE;
        pstSmBearerActivateInd->ucLinkedNsapi     = pstPdpEntity->ucLinkedNsapi;
    }

    /* ��д RADIO PRIORITY */
    if (VOS_TRUE == pstPdpEntity->GprsPara.Op_RadioPriority)
    {
        pstSmBearerActivateInd->bitOpRadioPriority = VOS_TRUE;
        pstSmBearerActivateInd->ucRadioPriority    = pstPdpEntity->GprsPara.ucRadioPriority;
    }

    /* LLC SAPIδʵ��ʹ��, �ݲ���д LLC SAPI */
    /* PACKET FLOW IDδʵ��ʹ��, �ݲ���д PACKET FLOW ID */
}


VOS_VOID MN_APS_FillSmBearerModifyIndPara(
    SMREG_BEARER_MODIFY_IND_STRU       *pstSmBearerModifyInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    /* ��д TI */
    pstSmBearerModifyInd->stTransId.ucTiFlag  = pstPdpEntity->stTransId.ucTiFlag;
    pstSmBearerModifyInd->stTransId.ucTiValue = pstPdpEntity->stTransId.ucTiValue;

    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pstSmBearerModifyInd->ucConnectId         = pstPdpEntity->ucPdpId;

    /* ��д QOS */
    if (VOS_TRUE == pstPdpEntity->PdpQosFlag)
    {
        pstSmBearerModifyInd->bitOpPdpQos     = VOS_TRUE;
        Aps_PackSmQos(&pstPdpEntity->PdpQos,
                      &pstSmBearerModifyInd->stNegQos);
    }

    /* ��д RADIO PRIORITY */
    if (VOS_TRUE == pstPdpEntity->GprsPara.Op_RadioPriority)
    {
        pstSmBearerModifyInd->bitOpRadioPriority  = VOS_TRUE;
        pstSmBearerModifyInd->ucRadioPriority     = pstPdpEntity->GprsPara.ucRadioPriority;
    }

}


VOS_VOID MN_APS_FillSmBearerDeactivateIndPara(
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstSmBearerDeactivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    /* ��д TI */
    pstSmBearerDeactivateInd->stTransId.ucTiFlag  = pstPdpEntity->stTransId.ucTiFlag;
    pstSmBearerDeactivateInd->stTransId.ucTiValue = pstPdpEntity->stTransId.ucTiValue;


    /* ��д ConnectId (CR)����ǰCR��ͬ��Pdp Id */
    pstSmBearerDeactivateInd->ucConnectId         = pstPdpEntity->ucPdpId;
}


VOS_VOID MN_APS_SndEsmPdpInfoInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
)
{
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd;

    /* ����LTE����ִ�� */
    if (VOS_FALSE == TAF_SDC_IsPlatformSupportLte())
    {
        return;
    }

    /* ������Ϣ */
    pstEsmPdpInfoInd = (SM_ESM_PDP_CONTEXT_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_TAF,
                            sizeof(SM_ESM_PDP_CONTEXT_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstEsmPdpInfoInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"MN_APS_PackEsmPdpOptModify: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstEsmPdpInfoInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_ESM_PDP_CONTEXT_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstEsmPdpInfoInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEsmPdpInfoInd->ulReceiverPid    = PS_PID_ESM;
    pstEsmPdpInfoInd->ulMsgId          = ID_SM_ESM_PDP_CONTEXT_INFO_IND;
    pstEsmPdpInfoInd->enPdpOption      = enPdpOption;

    /* ��д��Ϣ���� */
    (VOS_VOID)MN_APS_FillEsmPdpInfoIndPara(pstEsmPdpInfoInd, pstPdpEntity, enPdpOption);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstEsmPdpInfoInd))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,"MN_APS_PackEsmPdpOptModify: Send message failed.");
        return;
    }

    return;
}


VOS_VOID MN_APS_SndSmBearerActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstSmBearerActivateInd;

    /* ������Ϣ�������Ϣͷ */
    pstSmBearerActivateInd = (SMREG_BEARER_ACTIVATE_IND_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_BEARER_ACTIVATE_IND);
    if (VOS_NULL_PTR == pstSmBearerActivateInd)
    {
        return;
    }

    /* ��д��Ϣ���� */
    MN_APS_FillSmBearerActivateIndPara(pstSmBearerActivateInd, pstPdpEntity);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSmBearerActivateInd))
    {
        MN_ERR_LOG("MN_APS_SndSmBearerActivateInd: Send message failed.");
        return;
    }

    return;
}
VOS_VOID MN_APS_SndSmAllSecPdpActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    VOS_UINT8                           i;

    /* �ж����е�PDPʵ������û�йҽ��������Ҫȥ�����PDP�������棬
       ����еĻ�����������Ϣ�����Tear down��ʶ */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        if (pstPdpEntity->ucNsapi == g_PdpEntity[i].ucLinkedNsapi)
        {
            MN_APS_SndSmBearerActivateInd(&g_PdpEntity[i]);
        }
    }

    return;
}


VOS_VOID MN_APS_SndSmBearerModifyInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    SMREG_BEARER_MODIFY_IND_STRU       *pstSmBearerModifyInd;

    /* ������Ϣ�������Ϣͷ */
    pstSmBearerModifyInd = (SMREG_BEARER_MODIFY_IND_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_BEARER_MODIFY_IND);
    if (VOS_NULL_PTR == pstSmBearerModifyInd)
    {
        return;
    }

    /* ��д��Ϣ���� */
    MN_APS_FillSmBearerModifyIndPara(pstSmBearerModifyInd, pstPdpEntity);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSmBearerModifyInd))
    {
        MN_ERR_LOG("MN_APS_SndSmBearerModifyInd: Send message failed.");
        return;
    }

    return;
}
VOS_VOID MN_APS_SndSmBearerDeactivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
)
{
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstSmBearerDeactivateInd;

    /* ������Ϣ�������Ϣͷ */
    pstSmBearerDeactivateInd = (SMREG_BEARER_DEACTIVATE_IND_STRU *)TAF_APS_AllocMsgToSmAndFillMsgHeader(ID_SMREG_BEARER_DEACTIVATE_IND);
    if (VOS_NULL_PTR == pstSmBearerDeactivateInd)
    {
        return;
    }

    /* ��д��Ϣ���� */
    MN_APS_FillSmBearerDeactivateIndPara(pstSmBearerDeactivateInd, pstPdpEntity);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSmBearerDeactivateInd))
    {
        MN_ERR_LOG("MN_APS_SndSmBearerDeactivateInd: Send message failed.");
        return;
    }

    return;
}
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptActivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{

    /* ���������·���TI */
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpTransId)
    {
        pstPdpEntity->bitOpTransId = VOS_TRUE;

        pstPdpEntity->stTransId.ucTiFlag  = pstEpsBearerInfoInd->stTransId.ucTiFlag;
        pstPdpEntity->stTransId.ucTiValue = pstEpsBearerInfoInd->stTransId.ucTiValue;
    }

    /* ���� NSAPI */
    pstPdpEntity->PdpNsapiFlag      = VOS_TRUE;
    pstPdpEntity->ucNsapi           = (VOS_UINT8)pstEpsBearerInfoInd->ulEpsbId;

    /* ���� Linked NSAPI */
    MN_APS_UpdatePdpActTypeFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PDP ADDR */
    MN_APS_UpdatePdpAddrFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� APN */
    MN_APS_UpdatePdpApnFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PCO IPV4 */
    MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ���� PCO IPV6 */
    MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);
#endif

    /* ���� QOS */
    MN_APS_UpdatePdpQosFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� EPS QOS */
    MN_APS_UpdateEpsQosFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PACKET FILTER */
    MN_APS_UpdatePdpPfFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� GPRS PARA */
    MN_APS_UpdatePdpGprsParaFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� Emergency */
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpEmcInd)
    {
        pstPdpEntity->enEmergencyFlg = (TAF_PDP_EMC_IND_ENUM_UINT8)pstEpsBearerInfoInd->enEmergencyInd;
    }
    else
    {
        pstPdpEntity->enEmergencyFlg = TAF_PDP_NOT_FOR_EMC;
    }

    /* ���� IM CN SIGAL FLAG */
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpImCnSigalFlag)
    {
        pstPdpEntity->bitOpImCnSigalFlag= VOS_TRUE;
        pstPdpEntity->enImCnSignalFlg   = (VOS_UINT8)pstEpsBearerInfoInd->enImCnSignalFlag;
    }

    if ( (TAF_APS_DEFAULT_CID == TAF_APS_GetCidFromLteBitCid(pstEpsBearerInfoInd->ulBitCid))
      && (VOS_TRUE == pstEpsBearerInfoInd->bitOpErrorCode) )
    {
        pstPdpEntity->bitOpCause = VOS_TRUE;
        pstPdpEntity->enCause    = TAF_APS_MapL4aCause(pstEpsBearerInfoInd->ulErrorCode);
    }

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM����ID_MN_SM_BEARER_ACTIVATE_IND��Ϣ, ͬ��PDP��Ϣ */
        MN_APS_SndSmBearerActivateInd(pstPdpEntity);
    }

}
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptModify(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    /* ���� NSAPI */
    pstPdpEntity->PdpNsapiFlag      = VOS_TRUE;
    pstPdpEntity->ucNsapi           = (VOS_UINT8)pstEpsBearerInfoInd->ulEpsbId;

    /* ���� Linked NSAPI */
    MN_APS_UpdatePdpActTypeFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PDP ADDR */
    MN_APS_UpdatePdpAddrFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� APN */
    MN_APS_UpdatePdpApnFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PCO IPV4 */
    MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

#if (FEATURE_ON == FEATURE_IPV6)
    /* ���� PCO IPV6 */
    MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);
#endif

    /* ���� QOS */
    MN_APS_UpdatePdpQosFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� PACKET FILTER */
    MN_APS_UpdatePdpPfFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    /* ���� GPRS PARA */
    MN_APS_UpdatePdpGprsParaFromEpsBearer(pstPdpEntity, pstEpsBearerInfoInd);

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM����ID_MN_SM_BEARER_MODIFY_IND��Ϣ, ͬ��PDP��Ϣ */
        MN_APS_SndSmBearerModifyInd(pstPdpEntity);
    }
}


VOS_VOID MN_APS_ProcEsmBearerInfoIndOptDeactivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    pstPdpEntity->PdpNsapiFlag = VOS_FALSE;

    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        /* ��SM����ID_MN_SM_BEARER_DEACTIVATE_IND��Ϣ, ͬ��PDP��Ϣ */
        MN_APS_SndSmBearerDeactivateInd(pstPdpEntity);
    }
}
VOS_VOID MN_APS_UpdatePdpActTypeFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE != pstEpsBearerInfoInd->bitOpLinkedEpsbId)
    {
        pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
    }
    else
    {
        pstPdpEntity->ActType       = APS_PDP_ACT_SEC;
        pstPdpEntity->ucLinkedNsapi = (VOS_UINT8)pstEpsBearerInfoInd->ulLinkedEpsbId;
    }
}


VOS_VOID MN_APS_UpdatePdpAddrFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    /* ��һ�׶�ֻ����IPV4 */
    pstPdpEntity->PdpAddrFlag               = VOS_TRUE;
    pstPdpEntity->PdpAddr.ucPdpTypeOrgan    = APS_ADDR_ORGAN_IETF;

    if (SM_ESM_PDP_IPV4 == pstEpsBearerInfoInd->stPdnAddr.ucIpType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstEpsBearerInfoInd->stPdnAddr.aucIpV4Addr,
                   SM_ESM_IPV4_ADDR_LEN);
        pstPdpEntity->PdpAddr.ucPdpTypeNum  = APS_ADDR_STATIC_IPV4;
    }

#if (FEATURE_ON == FEATURE_IPV6)
    if (SM_ESM_PDP_IPV6 == pstEpsBearerInfoInd->stPdnAddr.ucIpType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstEpsBearerInfoInd->stPdnAddr.aucIpV6Addr,
                   SM_ESM_IPV6_ADDR_LEN);
        pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV6;
    }



    if (SM_ESM_PDP_IPV4V6 == pstEpsBearerInfoInd->stPdnAddr.ucIpType)
    {
        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpV6Addr,
                   pstEpsBearerInfoInd->stPdnAddr.aucIpV6Addr,
                   SM_ESM_IPV6_ADDR_LEN);

        PS_MEM_CPY(pstPdpEntity->PdpAddr.aucIpAddr,
                   pstEpsBearerInfoInd->stPdnAddr.aucIpV4Addr,
                   SM_ESM_IPV4_ADDR_LEN);
        pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV4V6;
    }

#endif

}
VOS_VOID MN_APS_UpdatePdpApnFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpApn)
    {
        pstPdpEntity->PdpApnFlag            = VOS_TRUE;
        pstPdpEntity->PdpApn.ucLength       = pstEpsBearerInfoInd->stApn.ucLength;
        PS_MEM_CPY(pstPdpEntity->PdpApn.aucValue,
                   pstEpsBearerInfoInd->stApn.aucValue,
                   SM_ESM_MAX_LENGTH_OF_APN);
    }
}


VOS_VOID MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpPcoIpv4Item)
    {
        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpPriDns)
        {
            pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
            pstPdpEntity->PdpDns.OP_PriDns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->PdpDns.aucPriDns,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucPriDns,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
            pstPdpEntity->PdpDns.OP_PriDns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->PdpDns.aucPriDns, 0 , SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpSecDns)
        {
            pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
            pstPdpEntity->PdpDns.OP_SecDns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->PdpDns.aucSecDns,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucSecDns,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->PdpDnsFlag        = VOS_TRUE;
            pstPdpEntity->PdpDns.OP_SecDns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->PdpDns.aucSecDns, 0 , SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpGateWay)
        {
            pstPdpEntity->bitOpPdpGateWay = VOS_TRUE;
            pstPdpEntity->stPdpGateWay.bitOpGateWay = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpGateWay.aucGateWay,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucGateWay,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->bitOpPdpGateWay = VOS_TRUE;
            pstPdpEntity->stPdpGateWay.bitOpGateWay = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpGateWay.aucGateWay, 0, SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpPriNbns)
        {
            pstPdpEntity->bitOpPdpNbns          = VOS_TRUE;
            pstPdpEntity->stPdpNbns.OP_PriNbns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpNbns.aucPriNbns,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucPriNbns,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->bitOpPdpNbns          = VOS_TRUE;
            pstPdpEntity->stPdpNbns.OP_PriNbns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpNbns.aucPriNbns, 0, SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpSecNbns)
        {
            pstPdpEntity->bitOpPdpNbns          = VOS_TRUE;
            pstPdpEntity->stPdpNbns.OP_SecNbns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpNbns.aucSecNbns,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucSecNbns,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->bitOpPdpNbns          = VOS_TRUE;
            pstPdpEntity->stPdpNbns.OP_SecNbns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpNbns.aucSecNbns, 0, SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpPriPcscf)
        {
            pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucPriPcscf,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr, 0, SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpSecPcscf)
        {
            pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucSecPcscf,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpPcscf.aucSecPcscfAddr, 0, SM_ESM_IPV4_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv4Item.bitOpThiPcscf)
        {
            pstPdpEntity->stPdpPcscf.bitOpThiPcscfAddr  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpPcscf.aucThiPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv4Item.aucThiPcscf,
                       SM_ESM_IPV4_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpPcscf.bitOpThiPcscfAddr  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpPcscf.aucThiPcscfAddr, 0, SM_ESM_IPV4_ADDR_LEN);
        }

    }

}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpPcoIpv6Item)
    {
        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv6Item.bitOpPriDns)
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpPriDns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucPriDns,
                       pstEpsBearerInfoInd->stPcoIpv6Item.aucPriDns,
                       SM_ESM_IPV6_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpPriDns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpIpV6Dns.aucPriDns, 0, SM_ESM_IPV6_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv6Item.bitOpSecDns)
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpSecDns  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpV6Dns.aucSecDns,
                       pstEpsBearerInfoInd->stPcoIpv6Item.aucSecDns,
                       SM_ESM_IPV6_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpIpV6Dns.bitOpSecDns  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpIpV6Dns.aucSecDns, 0, SM_ESM_IPV6_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv6Item.bitOpPriPcscf)
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv6Item.aucPriPcscf,
                       SM_ESM_IPV6_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr, 0, SM_ESM_IPV6_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv6Item.bitOpSecPcscf)
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv6Item.aucSecPcscf,
                       SM_ESM_IPV6_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr, 0, SM_ESM_IPV6_ADDR_LEN);
        }

        if (VOS_TRUE == pstEpsBearerInfoInd->stPcoIpv6Item.bitOpThiPcscf)
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpThiPcscfAddr  = VOS_TRUE;
            PS_MEM_CPY(pstPdpEntity->stPdpIpv6Pcscf.aucThiPcscfAddr,
                       pstEpsBearerInfoInd->stPcoIpv6Item.aucThiPcscf,
                       SM_ESM_IPV6_ADDR_LEN);
        }
        else
        {
            pstPdpEntity->stPdpIpv6Pcscf.bitOpThiPcscfAddr  = VOS_FALSE;
            PS_MEM_SET(pstPdpEntity->stPdpIpv6Pcscf.aucThiPcscfAddr, 0, SM_ESM_IPV6_ADDR_LEN);
        }
    }
}
#endif


VOS_VOID MN_APS_UpdatePdpQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    pstPdpEntity->PdpQosFlag            = VOS_TRUE;
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpNegQos)
    {
        PS_MEM_CPY(&(pstPdpEntity->PdpQos),
                   (APS_PDP_QOS_ST*)&(pstEpsBearerInfoInd->stNegQos),
                   sizeof(APS_PDP_QOS_ST));
    }
}


VOS_VOID MN_APS_UpdateEpsQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpEpsQos)
    {
        pstPdpEntity->bitOpEpsQos       = VOS_TRUE;
        PS_MEM_CPY((VOS_UINT8 *)&(pstPdpEntity->stEpsQos),
                   (VOS_UINT8 *)&(pstEpsBearerInfoInd->stEpsQos),
                   sizeof(SM_ESM_EPS_QOS_STRU));
    }
}


VOS_VOID MN_APS_UpdatePdpPfFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpTft)
    {
        pstPdpEntity->bitOpPf           = VOS_TRUE;
        pstPdpEntity->stTft             = pstEpsBearerInfoInd->stTft;
    }
}


VOS_VOID MN_APS_UpdatePdpGprsParaFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
)
{
    pstPdpEntity->PdpGprsParaFlag       = VOS_TRUE;

    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpLlcSapi)
    {
        /* LLC SAPI����Ҫ�������Լ�� */
        pstPdpEntity->GprsPara.Op_Sapi  = VOS_TRUE;
        pstPdpEntity->GprsPara.ucSapi   = pstEpsBearerInfoInd->ucLlcSapi;
    }

    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpRadioPriority)
    {
        /* RADIO PRIORITY, Refer to TS 24.008 section 10.5.7.2 */
        pstPdpEntity->GprsPara.Op_RadioPriority = VOS_TRUE;
        pstPdpEntity->GprsPara.ucRadioPriority  = pstEpsBearerInfoInd->ucRadioPriority;
        if (!APS_JUDGE_RADIOPRI_VALID(pstPdpEntity->GprsPara.ucRadioPriority))
        {
            pstPdpEntity->GprsPara.ucRadioPriority = APS_RADIOPRI_4;
        }
    }

    if (VOS_TRUE == pstEpsBearerInfoInd->bitOpPacketFlowId)
    {
        /* PACKET FLOW ID, Refer to TS 24.008 section 10.5.6.11 */
        pstPdpEntity->GprsPara.OP_PacketFlowId  = VOS_TRUE;
        pstPdpEntity->GprsPara.ucPacketFlowId   = pstEpsBearerInfoInd->ucPacketFlowId;
        Aps_ValidPacketFlowId(&(pstPdpEntity->GprsPara.ucPacketFlowId));
    }
}

#endif
/* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, begin */

VOS_UINT32 TAF_APS_MatchCallWithAttachBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam
)
{
    VOS_UINT8                          *pucPdpEntApnValue;
    VOS_UINT8                          *pucUsrApnValue;
    VOS_UINT8                           aucApn[APS_MAX_LENGTH_OF_APN];
    VOS_UINT8                           ucPdpEntApnLen;
    VOS_UINT8                           ucUsrApnLen;
    VOS_UINT8                           ucPdpId;

    PS_MEM_SET(aucApn, 0x00, APS_MAX_LENGTH_OF_APN);
    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-5, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-5, end */

    /* �����������Ƿ�ƥ�� */
    if (VOS_TRUE != pstMatchParam->ucPrimaryPdpFlg)
    {
        return VOS_FALSE;
    }

    /* ��ȡע����ص�ʵ������ */
    ucPdpId = TAF_APS_GetPdpIdByDefaultCid();
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_FALSE;
    }

    /* �����ص�IP�����Ƿ�ƥ�� */
    if (VOS_FALSE == TAF_APS_CheckBearerPdpTypeSuitable(
                                TAF_APS_GetPdpEntPdpAddrType(ucPdpId),
                                pstMatchParam->enPdpType))
    {
        return VOS_FALSE;
    }

    /* ���������ص������Ƿ�ƥ�� */
    if (TAF_APS_GetPdpEntEmcFlg(ucPdpId) != pstMatchParam->enEmergencyInd)
    {
        return VOS_FALSE;
    }

    /* �����ص�APN�Ƿ�ƥ�� */
    if (0 == pstMatchParam->stApn.ucLength)
    {
        return VOS_TRUE;
    }
    else
    {
        /* ���Ų����е�APNת��������Э���ʽ */
        Taf_LenStr2Apn(&pstMatchParam->stApn, aucApn);

        /* ��ȡ����Э���ʽAPN�ܳ��Ⱥ����� */
        pucUsrApnValue = &aucApn[1];
        ucUsrApnLen    = aucApn[0];

        /* �û�����APN, ��APN��ȫ��ͬ, �򲦺���Ϣƥ�� */
        if (VOS_TRUE == TAF_APS_GetPdpEntApnFlag(ucPdpId))
        {
            pucPdpEntApnValue = TAF_APS_GetPdpEntApnValue(ucPdpId);
            ucPdpEntApnLen    = TAF_APS_GetPdpEntApnLen(ucPdpId);

            /* �Ƚ�APN���� */
            if (VOS_OK == TAF_APS_CompareApn(pucPdpEntApnValue,
                                             ucPdpEntApnLen,
                                             pucUsrApnValue,
                                             ucUsrApnLen))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
/* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, end */

VOS_UINT32 TAF_APS_IsApnSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
)
{
    VOS_UINT8                          *pucPdpEntApnValue;
    VOS_UINT8                          *pucTafCidApnValue;
    VOS_UINT8                           aucTafCidApn[APS_MAX_LENGTH_OF_APN];
    VOS_UINT8                           ucTafCidApnLen;
    VOS_UINT8                           ucPdpEntApnLen;

    /* ��鵱ǰ��Ĭ�ϳ����Ƿ��ָ����CIDƥ�� */
    if (0 == TAF_APS_GetTafCidInfoApnLen(ucCid))
    {
        /* �û�δ����APN, �򲦺���Ϣƥ�� */
        return VOS_TRUE;
    }
    else
    {
        /* ��TAF CID�����е�APNת��������Э���ʽ */
        Taf_LenStr2Apn(TAF_APS_GetTafCidInfoApn(ucCid), aucTafCidApn);

        /* �û�����APN, ��APN��ȫ��ͬ, �򲦺���Ϣƥ�� */
        if (VOS_TRUE == TAF_APS_GetPdpEntApnFlag(ucPdpId))
        {
            pucPdpEntApnValue = TAF_APS_GetPdpEntApnValue(ucPdpId);
            ucPdpEntApnLen    = TAF_APS_GetPdpEntApnLen(ucPdpId);
            pucTafCidApnValue = &aucTafCidApn[1];
            ucTafCidApnLen    = aucTafCidApn[0];

            /* �Ƚ�APN���� */
            if (VOS_OK == TAF_APS_CompareApn(pucPdpEntApnValue,
                                             ucPdpEntApnLen,
                                             pucTafCidApnValue,
                                             ucTafCidApnLen))
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}
VOS_UINT32 TAF_APS_IsStaticIpAddrSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucStaticIpAddr,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT8                           ucDefaultPdpType;
    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
    VOS_UINT8                          *pucPdpEntIpAddr;

    *pulErrCode = TAF_ERR_NO_ERROR;
    PS_MEM_SET(aucIpAddr, 0, TAF_IPV4_ADDR_LEN);

    /* ���û�����þ�̬IP��ַ����ʹ���Ѵ��ڵ�PDP��Ϊ�������� */
    /* û�����þ�̬IP��ַ��PPP DIAL REQ��IPCP����IP��ַΪ0.0.0.0 */
    if (VOS_OK == VOS_MemCmp(pucStaticIpAddr, aucIpAddr, TAF_IPV4_ADDR_LEN))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_APS_GetPdpEntPdpAddrFlag(ucPdpId))
    {
        pucPdpEntIpAddr = TAF_APS_GetPdpEntPdpIpAddr(ucPdpId);
        /* ���õľ�̬IP��ַ��Ĭ�ϳ��ص�IP��ַ���бȽ� */
        if (VOS_OK == VOS_MemCmp(pucStaticIpAddr, pucPdpEntIpAddr, TAF_IPV4_ADDR_LEN))
        {
            return VOS_TRUE;
        }
        else
        {
            /* ���Ĭ�ϳ��ص�PdpTypeΪipv4v6���ͣ���̬IP��ַ��Ĭ�ϳ��ص�IP��ַ
               ����ͬ�������Ҳ��Ҫ���·���һ��PDN���� */
            ucDefaultPdpType    = TAF_APS_GetPdpEntPdpAddrType(ucPdpId);
            if (MN_APS_ADDR_IPV4V6 != ucDefaultPdpType)
            {
                *pulErrCode = TAF_ERR_ERROR;
            }
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_FindSutiablePdpForPppDial_LteMode(
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo,
    VOS_UINT32                         *pulErrCode
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucPdpId;
    TAF_APS_IPCP_INFO_STRU              stIpcpInfo;
    VOS_UINT8                           ucDefaultPdpType;

    *pulErrCode = TAF_ERR_NO_ERROR;
    ucCid       = pstPppDialParaInfo->ucCid;

    PS_MEM_SET(&stIpcpInfo, 0, sizeof(TAF_APS_IPCP_INFO_STRU));

    /* ���CID��Ӧ���������Ƿ�Ϊר�ó��� */
    if (VOS_TRUE == TAF_APS_GetTafCidInfoPrimPdpFlg(ucCid))
    {
        return VOS_FALSE;
    }

    /* ��ȡĬ�ϳ��ض�Ӧ��APSʵ������ */
    ucPdpId = TAF_APS_GetPdpIdByDefaultCid();
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_FALSE;
    }

    /* ����CID��Ӧ��PdpType(PPPֻ֧��IPV4)��Ĭ�ϳ����Ƿ���ڰ��ݹ�ϵ */
    ucDefaultPdpType    = TAF_APS_GetPdpEntPdpAddrType(ucPdpId);
    if (VOS_FALSE == TAF_APS_CheckBearerPdpTypeSuitable(ucDefaultPdpType, TAF_PDP_IPV4))
    {
        return VOS_FALSE;
    }

    /* �����ص������Ƿ���ͬ */
    if (TAF_APS_GetTafCidInfoEmcFlg(ucCid) != TAF_APS_GetPdpEntEmcFlg(ucPdpId))
    {
        return VOS_FALSE;
    }

    /* ��鵱ǰ��Ĭ�ϳ��ض�Ӧ��APN�Ƿ��ָ����Cidƥ�� */
    if (VOS_FALSE == TAF_APS_IsApnSameWithDefaultBearer(ucCid, ucPdpId))
    {
        return VOS_FALSE;
    }

    /* ��IPCP�����е�IPCP��Ԫ����� */
    if (VOS_ERR == TAF_APS_DecodeIpcpPkt(&stIpcpInfo,
                                         pstPppDialParaInfo->stPppReqConfigInfo.stIPCP.aucIpcp,
                                         pstPppDialParaInfo->stPppReqConfigInfo.stIPCP.usIpcpLen))
    {
        *pulErrCode = TAF_ERR_ERROR;

        return VOS_FALSE;
    }

    if (VOS_FALSE == TAF_APS_IsStaticIpAddrSameWithDefaultBearer(ucCid,
                                                                 ucPdpId,
                                                                 stIpcpInfo.aucIpAddr,
                                                                 pulErrCode))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_APS_ProcImsDedicateBearer(APS_PDP_CONTEXT_ENTITY_ST *pstPdpEntity)
{
    VOS_UINT8                           ucPriPdpId;
    VOS_UINT8                           ucPriCid;
    VOS_UINT8                           ucSecPdpId;
    VOS_UINT8                           ucSecCid;

    /* �ж�PDP��������Ϣ�е�linkedEspId��IMS��������е�RABID�Ƿ�һ�� */
    if (APS_PDP_ACT_SEC == pstPdpEntity->ActType)
    {
        if (VOS_TRUE == TAF_APS_CheckImsBearerByRabId(pstPdpEntity->ucLinkedNsapi))
        {
            /* ��ȡ��PDP��ʵ��ID */
            ucPriPdpId = TAF_APS_GetPdpIdByNsapi(pstPdpEntity->ucLinkedNsapi);
            ucPriCid = 0;
            TAF_APS_GetImsBearerCid(ucPriPdpId, &ucPriCid);

            /* ��ȡר�г��ص�ʵ��ID */
            ucSecPdpId = TAF_APS_GetCurrFsmEntityPdpId();
            ucSecCid   = TAF_APS_GetPdpEntCurrCid(ucSecPdpId);

            /* ĿǰIMS��ר�г���ֻ��IMSA�ϱ� */
            /* ����ר�г��� PDP TAB */
            TAF_APS_SetPdpEntClientInfo(ucSecPdpId,
                                        ucSecCid,
                                        TAF_APS_GetPdpEntModuleId(ucPriPdpId, ucPriCid),
                                        TAF_APS_GetPdpEntClientId(ucPriPdpId, ucPriCid),
                                        TAF_APS_GetPdpEntOpId(ucPriPdpId, ucPriCid));

            /* �ϱ�ר�г��� ACT_IND */
            TAF_APS_SndPdpActivateInd(ucSecPdpId, ucSecCid);
        }
    }
}
#endif

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


