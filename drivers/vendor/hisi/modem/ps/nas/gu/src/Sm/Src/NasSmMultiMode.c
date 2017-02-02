

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "SmInclude.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_SM_MULTI_MODE_C


#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID NAS_SM_SndRabmBearerActivateInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_ACTIVATE_IND_STRU   *pstBearerActivateInd;
    VOS_UINT8                           ucAddrIndex;

    ucAddrIndex = pstPdpCtxInfo->ucAddrIndex;

    /* ������Ϣ */
    pstBearerActivateInd = (SM_RABM_BEARER_ACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_SM,
                            sizeof(SM_RABM_BEARER_ACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstBearerActivateInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerActivateInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstBearerActivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstBearerActivateInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerActivateInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerActivateInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_ACTIVATE_IND;

    /* ��д��Ϣ���� */
    pstBearerActivateInd->ulNsapi         = ucNsapi;
    pstBearerActivateInd->ulLinkdNsapi    = NAS_SM_GetPdpLinkedNsapi(ucAddrIndex);
    pstBearerActivateInd->stQos.ulLength  = pstPdpCtxInfo->QoS.ulQosLength;

    PS_MEM_CPY(pstBearerActivateInd->stQos.aucQosValue,
               pstPdpCtxInfo->QoS.aucQosValue,
               pstPdpCtxInfo->QoS.ulQosLength);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerActivateInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerActivateInd: Send message failed.");
    }

    return;

}
VOS_VOID NAS_SM_SndRabmBearerModifyInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_MODIFY_IND_STRU     *pstBearerModifyInd;

    /* ������Ϣ */
    pstBearerModifyInd = (SM_RABM_BEARER_MODIFY_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_SM,
                            sizeof(SM_RABM_BEARER_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstBearerModifyInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerModifyInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstBearerModifyInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstBearerModifyInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerModifyInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerModifyInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_MODIFY_IND;

    /* ��д��Ϣ���� */
    pstBearerModifyInd->ulNsapi         = ucNsapi;
    pstBearerModifyInd->stQos.ulLength  = pstPdpCtxInfo->QoS.ulQosLength;

    PS_MEM_CPY(pstBearerModifyInd->stQos.aucQosValue,
               pstPdpCtxInfo->QoS.aucQosValue,
               pstPdpCtxInfo->QoS.ulQosLength);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerModifyInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerModifyInd: Send message failed.");
    }

    return;

}
VOS_VOID NAS_SM_SndRabmBearerDeactivateInd(
    VOS_UINT8                           ucNsapi,
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo
)
{
    SM_RABM_BEARER_DEACTIVATE_IND_STRU *pstBearerDeactivateInd;

    /* ������Ϣ */
    pstBearerDeactivateInd = (SM_RABM_BEARER_DEACTIVATE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                WUEPS_PID_SM,
                                sizeof(SM_RABM_BEARER_DEACTIVATE_IND_STRU));
    if (VOS_NULL_PTR == pstBearerDeactivateInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerDeactivateInd: Memory alloc failed.");
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstBearerDeactivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SM_RABM_BEARER_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstBearerDeactivateInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBearerDeactivateInd->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstBearerDeactivateInd->stMsgHeader.ulMsgName       = ID_SM_RABM_BEARER_DEACTIVATE_IND;

    /* ��д��Ϣ���� */
    pstBearerDeactivateInd->ulNsapi                     = ucNsapi;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstBearerDeactivateInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_SndRabmBearerDeactivateInd: Send message failed.");
    }

    return;

}
VOS_VOID NAS_SM_RcvTafBearerActivateInd(
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstBearerActivateInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    NAS_SM_PDP_ADDR_INFO_STRU          *pstPdpAddrInfo;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucNsapiCnt;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucLinkedPdpCtxIndex;

    /*----------------------------------------------------------------
       ��ȡTI: ����TiFlag����TI��ȡֵ��Χ, �������·�TIΪ׼
               ��TiFlagΪTRUE(SM_TI_MS_ORG), TIȡֵ����[128, 254]
               ��TiFlagΪFALSE(SM_TI_NET_ORG), TIȡֵ����[0, 127]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerActivateInd->stTransId.ucTiFlag) ?
           (pstBearerActivateInd->stTransId.ucTiValue) :
           (pstBearerActivateInd->stTransId.ucTiValue + 0x80);

    /* ��ȡCR(PDPID) */
    ucCr = pstBearerActivateInd->ucConnectId;

    /* ����Ƿ���ں�TI��CR��Ӧ��PDP CONTEXT */
    if (0xFF != NAS_SM_GetNsapiFromTiMap(ucTi))
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerActivateInd: NSAPI is used by other PDP.");
        return;
    }

    /* ��ȡNSAPI��Ӧ��PDP CONTEXT����: PDP_INDEX = NSPAI - NSAPI_OFFSET(5) */
    ucPdpCtxIndex           = pstBearerActivateInd->ucNsapi - SM_NSAPI_OFFSET;

    /* ��ȡ��ǰPDP CONTEXT���ݵ�ַ */
    pstPdpCtxInfo           = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    if (SM_PDP_ACTIVE_PENDING == pstPdpCtxInfo->ucState)
    {
        /* ��SMʵ��״̬��ΪINACTIVE */
        pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

        /* ���TI��PDP INDEX��ӳ���ϵ */
        NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);

        /* ���CR��PDP INDEX��ӳ���ϵ */
        NAS_SM_ClearNsapiToCrMap(ucCr);

        /* �����Ӧ��PDPʵ����Ϣ */
        SM_ComClearPdpCntxt(ucPdpCtxIndex);
        SM_ComDelNsapiFromAddr(NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex), ucPdpCtxIndex);

        /* ֪ͨGMM����PDP CONTEXT״̬ */
        NAS_SM_SndGmmPdpStatusInd();

        /* ֪ͨRABM����״̬ */
        SM_SndRabmSmDeactivateInd(1, &ucPdpCtxIndex);

        /* ֪ͨGMM���SM���� */
        NAS_SM_SndGmmAbortReq();

        NAS_SM_SndGmmPdpDeactivatedInd();
    }

    /* ����PDPʵ��״̬ΪSM_PDP_INACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_ACTIVE;

    /* ����TI��CR(PDPID)��NSAPI��ӳ��� */
    NAS_SM_SetNsapiToTiMap(ucTi, ucPdpCtxIndex);
    NAS_SM_SetNsapiToCrMap(ucCr, ucPdpCtxIndex);

    /* ����TI��Ϣ */
    if (VOS_FALSE == pstBearerActivateInd->stTransId.ucTiFlag)
    {
        pstPdpCtxInfo->ucTiFlg = SM_TI_NET_ORG;
    }
    else
    {
        pstPdpCtxInfo->ucTiFlg = SM_TI_MS_ORG;
    }

    pstPdpCtxInfo->ucTi       = ucTi;

    /* ����PDP CONTEXT��Ϣ�е�CR, USER CHID, RADIO PRIORITY */
    pstPdpCtxInfo->ucCr       = ucCr;

    if (VOS_TRUE == pstBearerActivateInd->bitOpRadioPriority)
    {
        pstPdpCtxInfo->ucRadioPri = pstBearerActivateInd->ucRadioPriority;
    }

    /* ����PDP ADDR��APN��Ϣ */
    if (VOS_TRUE != pstBearerActivateInd->bitOpLinkedNsapi)
    {
        /* ��ȡδʹ�õ�PDP ADDRESS���� */
        ucAddrIndex     = SM_ComFindNullAddrApn();
        pstPdpAddrInfo  = NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex);

        /* ����PDP CONTEXT��Ϣ�е�ADRESS INDEX */
        pstPdpCtxInfo->ucAddrIndex  = ucAddrIndex;

        /* ����PDP ADDRESS��Ϣ�е�NSAPI(PDPʵ������) */
        pstPdpAddrInfo->ucNsapiCnt  = 1;
        pstPdpAddrInfo->aucNsapi[0] = ucPdpCtxIndex;

        /* ����PDP ADDRESS��Ϣ */
        NAS_SM_SetPdpAddrFlg(ucAddrIndex);
        pstPdpAddrInfo->PdpAddrInfo.ulAddrLength = pstBearerActivateInd->stPdpAddr.ulPdpAddrLen;
        PS_MEM_CPY(pstPdpAddrInfo->PdpAddrInfo.aucAddrValue,
                   pstBearerActivateInd->stPdpAddr.aucPdpAddr,
                   pstBearerActivateInd->stPdpAddr.ulPdpAddrLen);

        /* ����APN��Ϣ */
        if (VOS_TRUE == pstBearerActivateInd->bitOpApn)
        {
            pstPdpAddrInfo->PdpApn.ulApnLength = pstBearerActivateInd->stApn.ulApnLen;

            PS_MEM_CPY(pstPdpAddrInfo->PdpApn.aucApnValue,
                       pstBearerActivateInd->stApn.aucApnAddr,
                       NAS_SM_MAX_APN_LEN);
        }
    }
    else
    {
        /* ��ȡLINKED NSAPI��Ӧ��PDP CONTEXT����: LINKED_PDP_INDEX = LINKED_NSPAI - NSAPI_OFFSET(5) */
        ucLinkedPdpCtxIndex = pstBearerActivateInd->ucLinkedNsapi - SM_NSAPI_OFFSET;

        /* ����LINKED NSAPI��ȡ��Ӧ��PRIMARY PDP ADDR��Ϣ */
        ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucLinkedPdpCtxIndex);
        pstPdpAddrInfo  = NAS_SM_GetPdpAddrInfoAddr(ucAddrIndex);

        /* ����PDP CONTEXT��Ϣ�е�PDP ADDRESS���� */
        pstPdpCtxInfo->ucAddrIndex = ucAddrIndex;

        /* ����PDP ADDRESS��Ϣ�е�NSAPI(PDPʵ������) */
        ucNsapiCnt  = pstPdpAddrInfo->ucNsapiCnt;
        pstPdpAddrInfo->aucNsapi[ucNsapiCnt] = ucPdpCtxIndex;
        pstPdpAddrInfo->ucNsapiCnt++;
    }

    /* ����QOS��Ϣ */
    if (VOS_TRUE == pstBearerActivateInd->bitOpPdpQos)
    {
        pstPdpCtxInfo->QoS.ulQosLength = pstBearerActivateInd->stNegQos.ulQosLen;

        PS_MEM_CPY(pstPdpCtxInfo->QoS.aucQosValue,
                   pstBearerActivateInd->stNegQos.aucQos,
                   NAS_SM_MAX_QOS_LEN);
    }
    else
    {
        pstPdpCtxInfo->QoS.ulQosLength = 0;
        PS_MEM_SET(pstPdpCtxInfo->QoS.aucQosValue,
                   0x00,
                   sizeof(pstPdpCtxInfo->QoS.aucQosValue));
    }

    /* ֪ͨGMM����PDP CONTEXT״̬ */
    NAS_SM_SndGmmPdpStatusInd();

    /* ֪ͨRABM����״̬ */
    NAS_SM_SndRabmBearerActivateInd(pstBearerActivateInd->ucNsapi, pstPdpCtxInfo);

}


VOS_VOID NAS_SM_RcvTafBearerModifyInd(
    SMREG_BEARER_MODIFY_IND_STRU       *pstBearerModifyInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucNsapi;

    /*----------------------------------------------------------------
       ��ȡTI: ����TiFlag����TI��ȡֵ��Χ, �������·�TIΪ׼
               ��TiFlagΪTRUE(SM_TI_MS_ORG), TIȡֵ����[128, 254]
               ��TiFlagΪFALSE(SM_TI_NET_ORG), TIȡֵ����[0, 127]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerModifyInd->stTransId.ucTiFlag) ?
           (pstBearerModifyInd->stTransId.ucTiValue) :
           (pstBearerModifyInd->stTransId.ucTiValue + 0x80);


    /* ��ȡTI��Ӧ��PDP CONTEXT���� */
    ucPdpCtxIndex = NAS_SM_GetNsapiFromTiMap(ucTi);

    /* ����Ƿ���ں�TI��CR��Ӧ��PDP CONTEXT */
    if (0xFF == ucPdpCtxIndex)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerModifyInd: NSAPI is not used.");
        return;
    }

    /* ��ȡPDP CONTEXT������Ӧ��NSAPI: NSAPI = PDP_INDEX - NSAPI_OFFSET(5) */
    ucNsapi         = ucPdpCtxIndex + SM_NSAPI_OFFSET;

    /* ��ȡ��ǰPDP CONTEXT���ݵ�ַ */
    pstPdpCtxInfo = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* ����RADIO PRIORITY */
    if (VOS_TRUE == pstBearerModifyInd->bitOpRadioPriority)
    {
        pstPdpCtxInfo->ucRadioPri = pstBearerModifyInd->ucRadioPriority;
    }

    /* ����QOS��Ϣ */
    if (VOS_TRUE == pstBearerModifyInd->bitOpPdpQos)
    {
        pstPdpCtxInfo->QoS.ulQosLength = pstBearerModifyInd->stNegQos.ulQosLen;

        PS_MEM_CPY(pstPdpCtxInfo->QoS.aucQosValue,
                   pstBearerModifyInd->stNegQos.aucQos,
                   NAS_SM_MAX_QOS_LEN);
    }

    /* ֪ͨRABM����״̬ */
    NAS_SM_SndRabmBearerModifyInd(ucNsapi, pstPdpCtxInfo);
}
VOS_VOID NAS_SM_RcvTafBearerDeactivateInd(
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstBearerDeactivateInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucPdpCtxIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucNsapi;

    /*----------------------------------------------------------------
       ��ȡTI: ����TiFlag����TI��ȡֵ��Χ, �������·�TIΪ׼
               ��TiFlagΪTRUE(SM_TI_MS_ORG), TIȡֵ����[0, 127]
               ��TiFlagΪFALSE(SM_TI_NET_ORG), TIȡֵ����[128, 254]
    ----------------------------------------------------------------*/
    ucTi = (VOS_FALSE == pstBearerDeactivateInd->stTransId.ucTiFlag) ?
           (pstBearerDeactivateInd->stTransId.ucTiValue) :
           (pstBearerDeactivateInd->stTransId.ucTiValue + 0x80);


    ucCr            = pstBearerDeactivateInd->ucConnectId;

    /* ��ȡTI��Ӧ��PDP CONTEXT���� */
    ucPdpCtxIndex   = NAS_SM_GetNsapiFromTiMap(ucTi);

    /* ��ȡPDP CONTEXT������Ӧ��NSAPI: NSAPI = PDP_INDEX - NSAPI_OFFSET(5) */
    ucNsapi         = ucPdpCtxIndex + SM_NSAPI_OFFSET;

    /* ����Ƿ���ں�TI��CR��Ӧ��PDP CONTEXT */
    if (0xFF == ucPdpCtxIndex)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvTafBearerDeactivateInd: NSAPI is not used.");
        return;
    }

    /* ��ȡ��ǰPDP CONTEXT���ݵ�ַ */
    pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(ucPdpCtxIndex);

    /* ��ȡPDP ADDRESS���� */
    ucAddrIndex     = NAS_SM_GetPdpAddrIndex(ucPdpCtxIndex);

    /* ����PDPʵ��״̬ΪSM_PDP_INACTIVE */
    pstPdpCtxInfo->ucState  = SM_PDP_INACTIVE;

    /* ���TI��PDP INDEX��ӳ���ϵ */
    NAS_SM_ClearNsapiToTiMap(ucTi);

    /* ���CR��PDP INDEX��ӳ���ϵ */
    NAS_SM_ClearNsapiToCrMap(ucCr);

    /* �����Ӧ��PDPʵ����Ϣ */
    SM_ComClearPdpCntxt(ucPdpCtxIndex);
    SM_ComDelNsapiFromAddr(ucAddrIndex, ucPdpCtxIndex);

    /* ֪ͨGMM����PDP CONTEXT״̬ */
    NAS_SM_SndGmmPdpStatusInd();

    /* ֪ͨRABM����״̬ */
    NAS_SM_SndRabmBearerDeactivateInd(ucNsapi, pstPdpCtxInfo);

}
#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


