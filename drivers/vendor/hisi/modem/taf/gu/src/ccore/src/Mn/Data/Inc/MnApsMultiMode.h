
#ifndef _MN_APS_MULTI_MODE_H_
#define _MN_APS_MULTI_MODE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�TI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/

/* ���� TI������SMʵ�ֵ������ԣ�Lģ�µĳ��ؼ����Ӧ��GU��SM��APS�Ľӿ���˵
   TI��ȡֵ��ΧӦ����8~14�����Իظ�TIֵʱ������ת����Tiflag��ֵȡ��
*/
#define MN_APS_FillEsmPdpInfoTransId(pstEsmPdpInfoInd, pstPdpEntity)           \
{                                                                              \
    pstEsmPdpInfoInd->stTransId.ucTiFlag  = pstPdpEntity->stTransId.ucTiFlag;  \
    pstEsmPdpInfoInd->stTransId.ucTiValue = pstPdpEntity->stTransId.ucTiValue; \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�NSAPI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoNsapi(pstEsmPdpInfoInd, pstPdpEntity)  \
{                                                                   \
    pstEsmPdpInfoInd->ulNsapi  = pstPdpEntity->ucNsapi;             \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�CID
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoCid(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                   \
    pstEsmPdpInfoInd->ulBitCid                                      \
        = (VOS_UINT32)0x00000001 << (pstPdpEntity->stClientInfo.ucCid);      \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�LINKED NSAPI
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoLinkedNsapi(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                           \
    if (APS_PDP_ACT_SEC == pstPdpEntity->ActType)                           \
    {                                                                       \
        pstEsmPdpInfoInd->bitOpLinkedNsapi = VOS_TRUE;                      \
        pstEsmPdpInfoInd->ulLinkedNsapi    = pstPdpEntity->ucLinkedNsapi;   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PDP ADDRESS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#if (FEATURE_ON == FEATURE_IPV6)
#define MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                       \
    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)     \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
    }                                                                   \
    else if (MN_APS_ADDR_IPV6 == pstPdpEntity->PdpAddr.ucPdpTypeNum)    \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV6;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV6Addr,             \
                   pstPdpEntity->PdpAddr.aucIpV6Addr,                   \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4V6;     \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV6Addr,             \
                   pstPdpEntity->PdpAddr.aucIpV6Addr,                   \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
}
#else
#define MN_APS_FillEsmPdpInfoPdpAddr(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                       \
    if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)     \
    {                                                                   \
        pstEsmPdpInfoInd->stPdpAddr.enPdpType  = SM_ESM_PDP_IPV4;       \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPdpAddr.aucIpV4Addr,             \
                   pstPdpEntity->PdpAddr.aucIpAddr,                     \
                   SM_ESM_IPV4_ADDR_LEN);                               \
    }                                                                   \
}
#endif

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PDP QOS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPdpQos(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                   \
    if (VOS_TRUE == pstPdpEntity->PdpQosFlag)                       \
    {                                                               \
        pstEsmPdpInfoInd->bitOpPdpQos      = VOS_TRUE;              \
        PS_MEM_CPY((VOS_CHAR*)&pstEsmPdpInfoInd->stPdpQos,          \
                   (VOS_CHAR*)&pstPdpEntity->PdpQos,                \
                   sizeof(APS_PDP_QOS_STRU));                       \
    }                                                               \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�APN
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoApn(pstEsmPdpInfoInd, pstPdpEntity)            \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->PdpApnFlag)                               \
    {                                                                       \
        pstEsmPdpInfoInd->bitOpApn  = VOS_TRUE;                             \
        pstEsmPdpInfoInd->stApn.ucLength  = pstPdpEntity->PdpApn.ucLength;  \
        PS_MEM_CPY(pstEsmPdpInfoInd->stApn.aucValue,                        \
                   pstPdpEntity->PdpApn.aucValue,                           \
                   pstPdpEntity->PdpApn.ucLength);                          \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PACKET FILTER
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPf(pstEsmPdpInfoInd, pstPdpEntity)     \
{                                                                   \
    if (VOS_TRUE == pstPdpEntity->bitOpPf)                          \
    {                                                               \
        pstEsmPdpInfoInd->bitOpTft = VOS_TRUE;                      \
        pstEsmPdpInfoInd->stTft    = pstPdpEntity->stTft;           \
    }                                                               \
}

/*-------------------------------------------------------------------
  ��ʼ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Begin(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    pstEsmPdpInfoInd->bitOpPcoIpv4Item     = VOS_TRUE;                      \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4: DNS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Dns(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                       \
    if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)                           \
    {                                                                   \
        if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)                 \
        {                                                               \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriDns = VOS_TRUE;     \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriDns,       \
                       pstPdpEntity->PdpDns.aucPriDns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                           \
        }                                                               \
        if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)                 \
        {                                                               \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecDns = VOS_TRUE;     \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecDns,       \
                       pstPdpEntity->PdpDns.aucSecDns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                           \
        }                                                               \
    }                                                                   \
}

/*-----------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4: GATE WAY (PEER IP)
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
------------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4GateWay(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->bitOpPdpGateWay)                          \
    {                                                                       \
        if (VOS_TRUE == pstPdpEntity->stPdpGateWay.bitOpGateWay)            \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpGateWay = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucGateWay,          \
                       pstPdpEntity->stPdpGateWay.aucGateWay,               \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4: NBNS (WINS)
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Nbns(pstEsmPdpInfoInd, pstPdpEntity)    \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->bitOpPdpNbns)                             \
    {                                                                       \
        if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_PriNbns)                 \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriNbns = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriNbns,          \
                       pstPdpEntity->stPdpNbns.aucPriNbns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
        if (VOS_TRUE == pstPdpEntity->stPdpNbns.OP_SecNbns)                 \
        {                                                                   \
            pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecNbns = VOS_TRUE;        \
            PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecNbns,          \
                       pstPdpEntity->stPdpNbns.aucSecNbns,                  \
                       SM_ESM_IPV4_ADDR_LEN);                               \
        }                                                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4: P-CSCF
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4Pcscf(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpPrimPcscfAddr)            \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv4Item.bitOpPriPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucPriPcscf,             \
                   pstPdpEntity->stPdpPcscf.aucPrimPcscfAddr,               \
                   SM_ESM_IPV4_ADDR_LEN);                                   \
    }                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpPcscf.bitOpSecPcscfAddr)             \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv4Item.bitOpSecPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv4Item.aucSecPcscf,             \
                   pstPdpEntity->stPdpPcscf.aucSecPcscfAddr,                \
                   SM_ESM_IPV4_ADDR_LEN);                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ������дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4End(pstEsmPdpInfoInd, pstPdpEntity)

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV4
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv4(pstEsmPdpInfoInd, pstPdpEntity)        \
    MN_APS_FillEsmPdpInfoPcoIpv4Begin(pstEsmPdpInfoInd, pstPdpEntity);      \
    MN_APS_FillEsmPdpInfoPcoIpv4Dns(pstEsmPdpInfoInd, pstPdpEntity);        \
    MN_APS_FillEsmPdpInfoPcoIpv4GateWay(pstEsmPdpInfoInd, pstPdpEntity);    \
    MN_APS_FillEsmPdpInfoPcoIpv4Nbns(pstEsmPdpInfoInd, pstPdpEntity);       \
    MN_APS_FillEsmPdpInfoPcoIpv4Pcscf(pstEsmPdpInfoInd, pstPdpEntity);      \
    MN_APS_FillEsmPdpInfoPcoIpv4End(pstEsmPdpInfoInd, pstPdpEntity);

#if (FEATURE_ON == FEATURE_IPV6)
/*-------------------------------------------------------------------
  ��ʼ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Begin(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    pstEsmPdpInfoInd->bitOpPcoIpv6Item     = VOS_TRUE;                      \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV6: DNS
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Dns(pstEsmPdpInfoInd, pstPdpEntity) \
{                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpPriDns)             \
    {                                                                   \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpPriDns = VOS_TRUE;         \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucPriDns,           \
                   pstPdpEntity->stPdpIpV6Dns.aucPriDns,                \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpSecDns)             \
    {                                                                   \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpSecDns = VOS_TRUE;         \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucSecDns,           \
                   pstPdpEntity->stPdpIpV6Dns.aucSecDns,                \
                   SM_ESM_IPV6_ADDR_LEN);                               \
    }                                                                   \
}

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV6: P-CSCF
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6Pcscf(pstEsmPdpInfoInd, pstPdpEntity)   \
{                                                                           \
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)        \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpPriPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucPriPcscf,             \
                   pstPdpEntity->stPdpIpv6Pcscf.aucPrimPcscfAddr,           \
                   SM_ESM_IPV6_ADDR_LEN);                                   \
    }                                                                       \
    if (VOS_TRUE == pstPdpEntity->stPdpIpv6Pcscf.bitOpSecPcscfAddr)         \
    {                                                                       \
        pstEsmPdpInfoInd->stPcoIpv6Item.bitOpSecPcscf = VOS_TRUE;           \
        PS_MEM_CPY(pstEsmPdpInfoInd->stPcoIpv6Item.aucSecPcscf,             \
                   pstPdpEntity->stPdpIpv6Pcscf.aucSecPcscfAddr,            \
                   SM_ESM_IPV6_ADDR_LEN);                                   \
    }                                                                       \
}

/*-------------------------------------------------------------------
  ������дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6End(pstEsmPdpInfoInd, pstPdpEntity)

/*-------------------------------------------------------------------
  ��дID_SM_ESM_EPS_BEARER_INFO_IND��Ϣ�е�PCO IPV6
  SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd
  APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
-------------------------------------------------------------------*/
#define MN_APS_FillEsmPdpInfoPcoIpv6(pstEsmPdpInfoInd, pstPdpEntity)    \
    MN_APS_FillEsmPdpInfoPcoIpv6Begin(pstEsmPdpInfoInd, pstPdpEntity);  \
    MN_APS_FillEsmPdpInfoPcoIpv6Dns(pstEsmPdpInfoInd, pstPdpEntity);    \
    MN_APS_FillEsmPdpInfoPcoIpv6Pcscf(pstEsmPdpInfoInd, pstPdpEntity);  \
    MN_APS_FillEsmPdpInfoPcoIpv6End(pstEsmPdpInfoInd, pstPdpEntity);
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_APS_FillEsmPdpInfoIndOptActivatePara
 ��������  : ��дID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
             PDP OPTION Ϊ SM_ESM_PDP_OPT_ACTIVATE
 �������  : pstPdpEntity       - PDPʵ����Ϣ
 �������  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptActivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillEsmPdpInfoIndOptModifyPara
 ��������  : ��дID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
             PDP OPTION Ϊ SM_ESM_PDP_OPT_MODIFY
 �������  : pstPdpEntity       - PDPʵ����Ϣ
 �������  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptModifyPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillEsmPdpInfoIndOptDeactivatePara
 ��������  : ��дID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
             PDP OPTION Ϊ SM_ESM_PDP_OPT_DEACTIVATE
 �������  : pstPdpEntity       - PDPʵ����Ϣ
 �������  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillEsmPdpInfoIndOptDeactivatePara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillEsmPdpInfoIndPara
 ��������  : ��дID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
 �������  : pstPdpEntity       - PDPʵ����Ϣ
             enPdpOption        - PDPʵ����²���(����, �޸�, ��ȥ����)
 �������  : pstEsmPdpInfoInd   - ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 MN_APS_FillEsmPdpInfoIndPara(
    SM_ESM_PDP_CONTEXT_INFO_IND_STRU   *pstEsmPdpInfoInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillSmBearerActivateIndPara
 ��������  : ��дID_MN_SM_BEARER_ACTIVATE_IND��Ϣ����
 �������  : pstPdpEntity           - PDPʵ����Ϣ
 �������  : pstSmBearerActivateInd - ID_MN_SM_BEARER_ACTIVATE_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerActivateIndPara(
    SMREG_BEARER_ACTIVATE_IND_STRU     *pstSmBearerActivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillSmBearerModifyIndPara
 ��������  : ��дID_MN_SM_BEARER_MODIFY_IND��Ϣ����
 �������  : pstPdpEntity           - PDPʵ����Ϣ
 �������  : pstSmBearerModifyInd   - ID_MN_SM_BEARER_MODIFY_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerModifyIndPara(
    SMREG_BEARER_MODIFY_IND_STRU       *pstSmBearerModifyInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_FillSmBearerDeactivateIndPara
 ��������  : ��дID_MN_SM_BEARER_DEACTIVATE_IND��Ϣ����
 �������  : pstPdpEntity               - PDPʵ����Ϣ
 �������  : pstSmBearerDeactivateInd   - ID_MN_SM_BEARER_DEACTIVATE_IND��Ϣ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_FillSmBearerDeactivateIndPara(
    SMREG_BEARER_DEACTIVATE_IND_STRU   *pstSmBearerDeactivateInd,
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_SndEsmPdpInfoInd
 ��������  : ����ID_SM_ESM_PDP_CONTEXT_INFO_IND��Ϣ��ESM
 �������  : pstPdpEntity   - PDPʵ����Ϣ
             enPdpOption    - PDP����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SndEsmPdpInfoInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_PDP_OPTION_ENUM_UINT32       enPdpOption
);


/*****************************************************************************
 �� �� ��  : MN_APS_SndSmBearerActivateInd
 ��������  : ����ID_MN_SM_BEARER_ACTIVATE_IND��Ϣ��SM
 �������  : pstPdpEntity   - PDPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


VOS_VOID MN_APS_SndSmAllSecPdpActivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);

/*****************************************************************************
 �� �� ��  : MN_APS_SndSmBearerModifyInd
 ��������  : ����ID_MN_SM_BEARER_MODIFY_IND��Ϣ��SM
 �������  : pstPdpEntity   - PDPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerModifyInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_SndSmBearerDeactivateInd
 ��������  : ����ID_MN_SM_BEARER_DEACTIVATE_IND��Ϣ��SM
 �������  : pstPdpEntity   - PDPʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_SndSmBearerDeactivateInd(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);


/*****************************************************************************
 �� �� ��  : MN_APS_ProcEsmBearerInfoIndOptActivate
 ��������  :
 �������  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptActivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_ProcEsmBearerInfoIndOptModify
 ��������  :
 �������  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptModify(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_ProcEsmBearerInfoIndOptDeactivate
 ��������  :
 �������  : SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_ProcEsmBearerInfoIndOptDeactivate(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);



/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpActTypeFromEpsBearer
 ��������  : ����PDP ACT TYPE (��������)
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpActTypeFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpAddrFromEpsBearer
 ��������  : ����PDP ADDRESS
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpAddrFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpApnFromEpsBearer
 ��������  : ����APN
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpApnFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer
 ��������  : ����PDP PCO IPV4��ز���, ����DNS, NBNS, PEER IP��
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPcoIpv4ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer
 ��������  : ����PDP PCO IPV6��ز���, ����DNS, PCSCF��
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPcoIpv6ItemFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);
#endif

/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpQosFromEpsBearer
 ��������  : ����QOS
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);

/*****************************************************************************
 �� �� ��  : MN_APS_UpdateEpsQosFromEpsBearer
 ��������  : ����EPS QOS
 �������  : pstPdpEntity           - PDPʵ��
             pstEpsBearerInfoInd    - EPS Bearer��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID

*****************************************************************************/
VOS_VOID MN_APS_UpdateEpsQosFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);

/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpPfFromEpsBearer
 ��������  : ����PACKET FILTER
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpPfFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_UpdatePdpGprsParaFromEpsBearer
 ��������  : ����GPRS��ز���
 �������  : APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
             SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID MN_APS_UpdatePdpGprsParaFromEpsBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearerInfoInd
);


/*****************************************************************************
 �� �� ��  : MN_APS_FindPdpEntByCid
 ��������  : ����CID����PDP����
 �������  : VOS_UINT32                          ucCid
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT8 MN_APS_FindPdpEntByCid(
    VOS_UINT32                          ucCid
);

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_MatchCallWithAttachBearer
 ��������  : ���ע������Ƿ�ƥ���û����Ų����ĳ���
 �������  : pstCtrl      --- ������Ϣ
             pstDialParam --- ���Ų���
 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
*****************************************************************************/
VOS_UINT32 TAF_APS_MatchCallWithAttachBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_IsApnSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_IsStaticIpAddrSameWithDefaultBearer(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucStaticIpAddr,
    VOS_UINT32                         *pulErrCode
);
VOS_UINT32 TAF_APS_FindSutiablePdpForPppDial_LteMode(
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo,
    VOS_UINT32                         *pulErrCode
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_APS_ProcImsDedicateBearer(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity
);

VOS_VOID TAF_APS_SndImsaSrvccCancelNotify(
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32   enNotificationIndicator
);
#endif

#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
