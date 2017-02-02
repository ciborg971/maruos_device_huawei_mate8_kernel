
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaCtx.h"
#include "PsCommonDef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_CTX_PKT_C

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ��������
*****************************************************************************/



VOS_VOID CMMCA_PKT_InitCtx(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    CMMCA_PKT_CTX_STRU                 *pstPktCtx = VOS_NULL_PTR;

    /* ��ʼ��ȫ�ֱ���g_stCmmcaPktCtx */
    pstPktCtx = CMMCA_PKT_GetCtxAddr();

    /* ��ʼ��CID�ͺ���ʵ��ӳ��� */
    for (ulIndex = 0; ulIndex <= CMMCA_PDN_ID_MAX; ulIndex++)
    {
        pstPktCtx->aucPdnToIndexTbl[ulIndex] = CMMCA_PDN_CONN_ENTITY_INDEX_INVALID;
    }

    /* ��ʼ������ʵ�� */
    for (ulIndex = 0; ulIndex < CMMCA_PDN_CONN_ENTITY_NUM_MAX; ulIndex++)
    {
        pstPktCtx->astPdnConnEntity[ulIndex].ucUsedFlg     = VOS_FALSE;

        pstPktCtx->astPdnConnEntity[ulIndex].ucPdnId       = CMMCA_PDN_ID_INVALID;

        pstPktCtx->astPdnConnEntity[ulIndex].enUserPdnType = CMMCA_IP_TYPE_BUTT;

        pstPktCtx->astPdnConnEntity[ulIndex].enPdnReqType  = CMMCA_PDN_REQUEST_TYPE_BUTT;

        pstPktCtx->astPdnConnEntity[ulIndex].enConnStatus  = CMMCA_CONN_STATUS_BUTT;

        /* Sdf Para */
        PS_MEM_SET(&(pstPktCtx->astPdnConnEntity[ulIndex].stSelSdfPara),
                   0,
                   sizeof(CMMCA_SEL_SDF_PARA_STRU));

        /* Pdp Info */
        PS_MEM_SET(&(pstPktCtx->astPdnConnEntity[ulIndex].stPdpInfo),
                   0,
                   sizeof(CMMCA_PDP_INFO_STRU));
    }

    return;
}
CMMCA_PKT_CTX_STRU* CMMCA_PKT_GetCtxAddr(VOS_VOID)
{
    return &(CMMCA_GetCtxAddr()->stPktCtx);
}


CMMCA_PDN_CONN_ENTITY_STRU* CMMCA_PKT_GetPdnEntityAddr(
    VOS_UINT8                           ucIndex
)
{
    CMMCA_PKT_CTX_STRU                 *pstPktCtxAddr = VOS_NULL_PTR;

    pstPktCtxAddr = CMMCA_PKT_GetCtxAddr();

    return &(pstPktCtxAddr->astPdnConnEntity[ucIndex]);
}



CMMCA_CONN_STATUS_ENUM_UINT8 CMMCA_PKT_GetConnStatus(
    VOS_UINT8                           ucIndex
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucIndex);

    return pstPdnConnEntity->enConnStatus;
}


VOS_VOID CMMCA_PKT_SetConnStatus(
    VOS_UINT8                           ucIndex,
    CMMCA_CONN_STATUS_ENUM_UINT8        enConnStatus
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucIndex);

    pstPdnConnEntity->enConnStatus = enConnStatus;

    return;
}


VOS_VOID CMMCA_PKT_SetUserPdnType(
    VOS_UINT8                           ucIndex,
    CMMCA_IP_TYPE_ENUM_UINT8            enPdnType
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucIndex);

    pstPdnConnEntity->enUserPdnType = enPdnType;

    return;
}


CMMCA_IP_TYPE_ENUM_UINT8 CMMCA_PKT_GetUserPdnType(
    VOS_UINT8                           ucIndex
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucIndex);

    return pstPdnConnEntity->enUserPdnType;
}



VOS_VOID CMMCA_PKT_SetPdnRequestType(
    VOS_UINT8                           ucIndex,
    CMMCA_PDN_REQUEST_TYPE_ENUM_UINT8   enPdnReqType
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucIndex);

    pstPdnConnEntity->enPdnReqType = enPdnReqType;

    return;
}


VOS_VOID CMMCA_PKT_SavePdpInfo(
    CMMCA_PDP_INFO_STRU                *pstPdpInfo,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    pstPdpInfo->ucCid               = pstPdpActivateCnf->ucCid;
    pstPdpInfo->ucRabId             = pstPdpActivateCnf->ucRabId;
    pstPdpInfo->enPdpState          = CMMCA_PDP_STATE_ACTIVE;

    /* �洢IP��ַ */
    pstPdpInfo->bitOpPdpAddr        = pstPdpActivateCnf->bitOpPdpAddr;

    if (VOS_TRUE == pstPdpInfo->bitOpPdpAddr)
    {
        PS_MEM_CPY(&pstPdpInfo->stPdpAddr,
                   &pstPdpActivateCnf->stPdpAddr,
                   sizeof(CMMCA_IP_ADDRESS_STRU));

        /* �洢Interface Id */
        if ((CMMCA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
         || (CMMCA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
        {
            PS_MEM_CPY(pstPdpInfo->aucPdpIpv6IfId,
                       pstPdpInfo->stPdpAddr.aucIpV6Addr + CMMCA_IPV6_INTERFACE_ID_BYTE_LEN,
                       CMMCA_IPV6_INTERFACE_ID_BYTE_LEN);
        }
    }

    /* GateWay */
    PS_MEM_CPY(&pstPdpInfo->stPdpGateWay,
               &pstPdpActivateCnf->stGateWay,
               sizeof(CMMCA_PDP_GATEWAY_STRU));

    /* �洢IPV4 P-CSCF */
    PS_MEM_CPY(&pstPdpInfo->stPdpIpv4Pcscf,
               &pstPdpActivateCnf->stPcscf,
               sizeof(CMMCA_PDP_IPV4_PCSCF_STRU));

    /* �洢IPV4 DNS */
    PS_MEM_CPY(&pstPdpInfo->stPdpIpv4Dns,
               &pstPdpActivateCnf->stDns,
               sizeof(CMMCA_PDP_IPV4_DNS_STRU));

    /* �洢IPV6 P-CSCF */
    PS_MEM_CPY(&pstPdpInfo->stPdpIpv6Pcscf,
               &pstPdpActivateCnf->stIpv6Pcscf,
               sizeof(CMMCA_PDP_IPV6_PCSCF_STRU));

    /* �洢IPV6 DNS */
    PS_MEM_CPY(&pstPdpInfo->stPdpIpv6Dns,
               &pstPdpActivateCnf->stIpv6Dns,
               sizeof(CMMCA_PDP_IPV6_DNS_STRU));

    return;
}
VOS_VOID CMMCA_PKT_SaveIpv6RaInfo(
    CMMCA_PDP_INFO_STRU                *pstPdpInfo,
    TAF_PS_IPV6_INFO_IND_STRU          *pstIpv6InfoInd
)
{
    /* 23.401Ҫ��3GPP��IPV6ǰ׺������64λ
       IPv6 Stateless Address autoconfiguration specified in RFC 4862 [18] is
       the basic mechanism to allocate /64 IPv6 prefix to the UE. */

    /* 29.061Ҫ����������IPV6ǰ׺�����޳��ģ�������迼��IPV6ǰ׺����Ч��
       AdvValidLifetime
           Shall have a value giving Prefixes infinite lifetime, i.e. 0xFFFFFFFF.
           The assigned prefix remains Preferred until PDP Context/Bearer Deactivation.
       AdvPreferredLifetime
           Shall have a value giving Prefixes infinite lifetime, i.e. 0xFFFFFFFF.
           The assigned prefix remains Preferred until PDP Context/Bearer Deactivation.
     */
    PS_MEM_CPY(pstPdpInfo->stPdpAddr.aucIpV6Addr,
               pstIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
               CMMCA_IPV6_PREFIX_BYTE_LEN);

    return;
}


VOS_UINT8 CMMCA_PKT_FindPdnConnEntityIndex(
    VOS_UINT8                           ucPdnId
)
{
    CMMCA_PKT_CTX_STRU                 *pstPktCtxAddr = VOS_NULL_PTR;

    pstPktCtxAddr = CMMCA_PKT_GetCtxAddr();

    return pstPktCtxAddr->aucPdnToIndexTbl[ucPdnId];
}


VOS_VOID CMMCA_PKT_SavePdnConnEntityIndex(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucIndex
)
{
    CMMCA_PKT_CTX_STRU                 *pstPktCtxAddr = VOS_NULL_PTR;

    pstPktCtxAddr = CMMCA_PKT_GetCtxAddr();

    pstPktCtxAddr->aucPdnToIndexTbl[ucPdnId] = ucIndex;

    return;
}



VOS_VOID CMMCA_PKT_AssignPdnConnEntity(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                          *pucIndex
)
{
    VOS_UINT8                           i;
    CMMCA_PKT_CTX_STRU                 *pstPktCtxAddr = VOS_NULL_PTR;

    *pucIndex = CMMCA_PDN_CONN_ENTITY_INDEX_INVALID;

    pstPktCtxAddr = CMMCA_PKT_GetCtxAddr();

    for (i = 0; i < CMMCA_PDN_CONN_ENTITY_NUM_MAX; i++)
    {
        if (VOS_FALSE == pstPktCtxAddr->astPdnConnEntity[i].ucUsedFlg)
        {
            *pucIndex = i;

            pstPktCtxAddr->astPdnConnEntity[i].ucUsedFlg = VOS_TRUE;

            /* ����Pdn Id */
            pstPktCtxAddr->astPdnConnEntity[i].ucPdnId = ucPdnId;
            return;
        }
    }

    return;
}
VOS_VOID CMMCA_PKT_FreePdnConnEntity(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucPdnConnEntityIndex;
    CMMCA_PKT_CTX_STRU                 *pstPktCtxAddr = VOS_NULL_PTR;

    pstPktCtxAddr = CMMCA_PKT_GetCtxAddr();

    ucPdnConnEntityIndex = pstPktCtxAddr->aucPdnToIndexTbl[ucPdnId];

    /* ����Pdn Id��Ӧ��PDNʵ��indexֵ��Ϊ��Чֵ */
    pstPktCtxAddr->aucPdnToIndexTbl[ucPdnId] = CMMCA_PDN_CONN_ENTITY_INDEX_INVALID;

    /* ���ʵ����Ϣ */
    pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].ucUsedFlg     = VOS_FALSE;

    /* Pdn Id */
    pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].ucPdnId       = CMMCA_PDN_ID_INVALID;

    /* Ip Type*/
    pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].enUserPdnType = CMMCA_IP_TYPE_BUTT;

    /* Pdn Request Type */
    pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].enPdnReqType  = CMMCA_PDN_REQUEST_TYPE_BUTT;

    /* Connect Status */
    pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].enConnStatus  = CMMCA_CONN_STATUS_BUTT;

    /* Sdf Para */
    PS_MEM_SET(&(pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].stSelSdfPara),
               0,
               sizeof(CMMCA_SEL_SDF_PARA_STRU));

    /* Pdp Info */
    PS_MEM_SET(&(pstPktCtxAddr->astPdnConnEntity[ucPdnConnEntityIndex].stPdpInfo),
               0,
               sizeof(CMMCA_PDP_INFO_STRU));

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




