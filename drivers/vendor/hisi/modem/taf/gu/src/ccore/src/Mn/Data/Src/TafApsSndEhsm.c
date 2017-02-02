/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndEhsm.c
  �� �� ��   : ����
  ��    ��   : y00314741
  ��������   : 2015��05��08��
  ����޸�   :
  ��������   : TAF APSģ�鷢����Ϣ��HSM�ĺ���ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��05��08��
    ��    ��   : y00314741
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsSndEhsm.h"
#include "TafApsCtx.h"
#include "TafApsComFunc.h"
#include "TafApsDecode.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "ehsm_aps_pif.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_EHSM_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmPdnActReq
 ��������  : ����ID_APS_EHSM_PDN_ACTIVATE_REQ��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnActReq(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType
)
{
    APS_EHSM_PDN_ACTIVATE_REQ_STRU     *pstActReq      = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstAppMsg      = VOS_NULL_PTR;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg       = (TAF_PS_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    pstActReq       = (APS_EHSM_PDN_ACTIVATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_EHSM_PDN_ACTIVATE_REQ_STRU));

    if (VOS_NULL_PTR == pstActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnActReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstActReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_ACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstActReq->ulReceiverPid            = UEPS_PID_EHSM;
    pstActReq->enMsgId                  = ID_APS_EHSM_PDN_ACTIVATE_REQ;
    pstActReq->usOpId                   = 0;
    pstActReq->ucCid                    = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    if (TAF_APS_ORIG_TYPE_PS_CALL == enDailType)
    {
        pstCallOrigReq                  = (TAF_PS_CALL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        pstActReq->enPdnType            = pstCallOrigReq->stDialParaInfo.enPdpType;

        VOS_StrNCpy((VOS_INT8*)pstActReq->aucUserName,
                    (VOS_INT8*)pstCallOrigReq->stDialParaInfo.aucUserName,
                     EHSM_APS_MAX_AUTHDATA_USERNAME_LEN);

        VOS_StrNCpy((VOS_INT8*)pstActReq->aucPassword,
                    (VOS_INT8*)pstCallOrigReq->stDialParaInfo.aucPassWord,
                     EHSM_APS_MAX_AUTHDATA_PASSWORD_LEN);

        pstActReq->stApn.ulLength = VOS_StrLen((VOS_INT8 *)pstCallOrigReq->stDialParaInfo.aucApn);
        PS_MEM_CPY((VOS_INT8*)pstActReq->stApn.aucApn,
                    (VOS_INT8*)pstCallOrigReq->stDialParaInfo.aucApn,
                     EHSM_APS_APN_MAX_LEN);
    }
    else
    {
        pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
        PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

        pstActReq->enPdnType = TAF_APS_GetPdpEntDialPdpType(ucPdpId, pstActReq->ucCid);

        /* MODEM����ʱ��ֻ֧��PAP���͵ļ�Ȩ */
        if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
         && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
        {
            ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                             pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

            if (VOS_OK == ulResult)
            {
                PS_MEM_CPY(pstActReq->aucUserName,
                           stAuthInfo.unAuthParam.stPapParam.aucUsername,
                           stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                PS_MEM_CPY(pstActReq->aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.aucPassword,
                           stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);
            }
        }

        pstActReq->stApn.ulLength = TAF_APS_GetTafCidInfoApnLen(pstActReq->ucCid);
        PS_MEM_CPY((VOS_INT8 *)pstActReq->stApn.aucApn,
                    (VOS_INT8 *)TAF_APS_GetTafCidInfoApnData(pstActReq->ucCid),
                     EHSM_APS_APN_MAX_LEN);

    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstActReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmPdnDeactReq
 ��������  : ����ID_APS_EHSM_PDN_DEACTIVATE_REQ��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnDeactReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstDeactReq  = VOS_NULL_PTR;

    pstDeactReq = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PDN_DEACTIVATE_REQ_STRU));

    if (VOS_NULL_PTR == pstDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnDeactReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDeactReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstDeactReq->ulReceiverPid          = UEPS_PID_EHSM;
    pstDeactReq->enMsgId                = ID_APS_EHSM_PDN_DEACTIVATE_REQ;
    pstDeactReq->usOpId                 = 0;
    pstDeactReq->ucCid                  = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstDeactReq->ucPdnId                = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstDeactReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmPsRatTypeNtf
 ��������  : ����ID_APS_EHSM_PS_RAT_TYPE_NOTIFY��Ϣ
 �������  : APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPsRatTypeNtf(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{

    APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU   *pstPsRatTypeNty = VOS_NULL_PTR;
    APS_EHSM_PS_RATTYPE_ENUM_UINT32     enPsRatType;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_NULL:
            enPsRatType = APS_EHSM_PS_RATTYPE_NULL;
            break;
        case TAF_APS_RAT_TYPE_1X:
            enPsRatType = APS_EHSM_PS_RATTYPE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enPsRatType = APS_EHSM_PS_RATTYPE_HRPD;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enPsRatType = APS_EHSM_PS_RATTYPE_EHRPD;
            break;
        case TAF_APS_RAT_TYPE_LTE:
            enPsRatType = APS_EHSM_PS_RATTYPE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPsRatTypeNtf: enRatType Error");
            return;
    }

    pstPsRatTypeNty  = (APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstPsRatTypeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPsRatTypeNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPsRatTypeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PS_RAT_TYPE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstPsRatTypeNty->ulReceiverPid     = UEPS_PID_EHSM;
    pstPsRatTypeNty->enMsgId           = ID_APS_EHSM_PS_RAT_TYPE_NOTIFY;
    pstPsRatTypeNty->usOpId            = 0;
    pstPsRatTypeNty->enPsRatType       = enPsRatType;

    PS_SEND_MSG(WUEPS_PID_TAF, pstPsRatTypeNty);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmReconnReq
 ��������  : ����ID_APS_EHSM_RECONN_REQ��Ϣ
 �������  : VOS_UINT8                           ucPdnId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmReconnReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_RECONN_REQ_STRU           *pstReconnReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnId;

    ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstReconnReq  = (APS_EHSM_RECONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_RECONN_REQ_STRU));

    if (VOS_NULL_PTR == pstReconnReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmReconnReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstReconnReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_RECONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstReconnReq->ulReceiverPid     = UEPS_PID_EHSM;
    pstReconnReq->enMsgId           = ID_APS_EHSM_RECONN_REQ;
    pstReconnReq->usOpId            = 0;
    pstReconnReq->ucPdnId           = ucPdnId;
    pstReconnReq->ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstReconnReq);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmPdnCtxInfoInd
 ��������  : ����ID_APS_EHSM_PDN_CONTEXT_INFO_IND��Ϣ
 �������  : VOS_UINT8                           ucPdnId
             VOS_UINT8                           ucCid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmPdnCtxInfoNotify(
    VOS_UINT8                           ucPdpId,
    EHSM_APS_PDN_OPTION_ENUM_UINT32     enOption
)
{
    APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU                  *pstPdnCtxInfoNty = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity     = VOS_NULL_PTR;

    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdnCtxInfoNty  = (APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstPdnCtxInfoNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmPdnCtxInfoInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPdnCtxInfoNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_PDN_CONTEXT_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstPdnCtxInfoNty->ulReceiverPid     = UEPS_PID_EHSM;
    pstPdnCtxInfoNty->enMsgId           = ID_APS_EHSM_PDN_CONTEXT_INFO_NOTIFY;
    pstPdnCtxInfoNty->usOpId            = 0;
    pstPdnCtxInfoNty->ucPdnId           = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
    pstPdnCtxInfoNty->ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdnCtxInfoNty->enOption          = enOption;

    if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)
    {
        pstPdnCtxInfoNty->stIpv4Dns.bitOpIpv4PrimDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv4Dns.aucIpv4PrimDNS,
                   pstPdpEntity->PdpDns.aucPriDns,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)
    {
        pstPdnCtxInfoNty->stIpv4Dns.bitOpIpv4SecDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv4Dns.aucIpv4SecDNS,
                   pstPdpEntity->PdpDns.aucSecDns,
                   EHSM_APS_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpPriDns)
    {
        pstPdnCtxInfoNty->stIpv6Dns.bitOpIpv6PrimDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv6Dns.aucIpv6PrimDNS,
                   pstPdpEntity->stPdpIpV6Dns.aucPriDns,
                   EHSM_APS_IPV6_ADDR_LEN);
    }

    if (VOS_TRUE == pstPdpEntity->stPdpIpV6Dns.bitOpSecDns)
    {
        pstPdnCtxInfoNty->stIpv6Dns.bitOpIpv6SecDNS = VOS_TRUE;
        PS_MEM_CPY(pstPdnCtxInfoNty->stIpv6Dns.aucIpv6SecDNS,
                   pstPdpEntity->stPdpIpV6Dns.aucSecDns,
                   EHSM_APS_IPV6_ADDR_LEN);
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPdnCtxInfoNty);

    return;
}
VOS_VOID TAF_APS_SndEhsmLocDetachNotify(VOS_VOID)
{
    APS_EHSM_LOC_DETACH_NOTIFY_STRU    *pstLocDetachNty = VOS_NULL_PTR;

    pstLocDetachNty  = (APS_EHSM_LOC_DETACH_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                                       sizeof(APS_EHSM_LOC_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstLocDetachNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmLocDetachInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLocDetachNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_LOC_DETACH_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstLocDetachNty->ulReceiverPid = UEPS_PID_EHSM;
    pstLocDetachNty->enMsgId       = ID_APS_EHSM_LOC_DETACH_NOTIFY;
    pstLocDetachNty->usOpId        = 0;

    PS_SEND_MSG(WUEPS_PID_TAF, pstLocDetachNty);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmLocDeactReq
 ��������  : ����ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY��Ϣ
 �������  : VOS_UINT8                    ucPdpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��11��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmLocDeactNtf(
    VOS_UINT8                           ucPdpId
)
{
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU           *pstLocDeacNtf;
    pstLocDeacNtf = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                                        sizeof(APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstLocDeacNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmLocDeactNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstLocDeacNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstLocDeacNtf->ulReceiverPid        = UEPS_PID_EHSM;
    pstLocDeacNtf->enMsgId              = ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY;
    pstLocDeacNtf->usOpId               = 0;
    pstLocDeacNtf->ucCid                = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_SEND_MSG(WUEPS_PID_TAF, pstLocDeacNtf);

    return;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_SndEhsmDiscNtf
 ��������  : ����ID_APS_EHSM_DISC_NOTIFY��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndEhsmDiscNtf(VOS_VOID)
{
    APS_EHSM_DISC_NOTIFY_STRU             *pstDiscNtf = VOS_NULL_PTR;

    /* ��ȡ��Ϣ���� */
    pstDiscNtf       = (APS_EHSM_DISC_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_EHSM_DISC_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDiscNtf)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndEhsmDiscNtf: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDiscNtf + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_EHSM_DISC_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д���� */
    pstDiscNtf->ulReceiverPid           = UEPS_PID_EHSM;
    pstDiscNtf->enMsgId                 = ID_APS_EHSM_DISC_NOTIFY;
    pstDiscNtf->usOpId                  = 0;

    PS_SEND_MSG(WUEPS_PID_TAF, pstDiscNtf);

    return;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, end */


#endif


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
