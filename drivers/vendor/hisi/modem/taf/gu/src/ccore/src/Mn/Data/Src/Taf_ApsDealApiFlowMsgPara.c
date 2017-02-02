

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "NasMmlCtx.h"
#include "TafApsSndAds.h"
#if ( FEATURE_ON == FEATURE_LTE )
#include "v_lib.h"
#endif
#include "TafMd5.h"
#include "TafApsCtx.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsComFunc.h"
#include "NasOmTrans.h"
#include "NasOmInterface.h"
#include "TafLog.h"
#include "TafSdcLib.h"
#include "AtPppInterface.h"
#include "TafAppPpp.h"
#include "TafApsMntn.h"
#include "TafApsSndCds.h"
#include "TafApsSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/


#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALAPIFLOWMSGPARA_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

extern VOS_VOID Ttf_DataReq(VOS_UINT8 ucMode, VOS_UINT8 ucNsapi, VOS_UINT32 ulLen, VOS_UINT8 ucTimes, VOS_UINT32 ulMillSecs);


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 TAF_APS_SndPsEvt(
    VOS_UINT32                          ulEvtId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult = VOS_OK;
    TAF_PS_EVT_STRU                    *pstMsg   = VOS_NULL_PTR;
    TAF_CTRL_STRU                      *pstCtrl  = VOS_NULL_PTR;

    /* �����¼���Ϣ: PS���¼���Ϣ�ṹ��TAF_PS_EVT_STRU */
    pstMsg = (TAF_PS_EVT_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                    WUEPS_PID_TAF,
                    sizeof(MSG_HEADER_STRU) + sizeof(VOS_UINT32) + ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        return VOS_ERR;
    }

    /* ����TAF_APS_SndPsEvt����Ϣ����Ϣ�ṹͷ����TAF_CTRL_STRU */
    pstCtrl = (TAF_CTRL_STRU *)pData;

    pstCtrl->usClientId = MN_GetRealClientId(pstCtrl->usClientId, WUEPS_PID_TAF);

    /* ��д�¼���Ϣͷ */
    pstMsg->stHeader.ulReceiverPid = pstCtrl->ulModuleId;
    pstMsg->stHeader.ulMsgName     = MN_CALLBACK_PS_CALL;

    /* ��д�¼�ID */
    pstMsg->ulEvtId                = ulEvtId;

    /* ��д�¼����� */
    PS_MEM_CPY(pstMsg->aucContent, pData, ulLength);

    /* ������Ϣ */
    ulResult = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if (VOS_OK != ulResult)
    {
        MN_ERR_LOG1("TAF_APS_SndPsEvt: Send message failed. <EvtId>",
                    (VOS_INT32)ulEvtId);
        return VOS_ERR;
    }

    /* ��Ϣ���� */
    TAF_APS_TraceApsEvt(ulEvtId, ulLength, (VOS_UINT8 *)pData);

    return VOS_OK;
}
VOS_VOID TAF_APS_SndPdpActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActCnfEvt;
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceMode;
#endif
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */


    pstPdpActCnfEvt = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstPdpActCnfEvt)
    {
        /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpActivateCnf: PS_MEM_ALLOC Error!");
        return;
    }

    PS_MEM_SET(pstPdpActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));

    pstPdpActCnfEvt->ucCid = ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpActCnfEvt->ucCid, &pstPdpActCnfEvt->stCtrl);

    TAF_APS_FillEvtPdpType(&pstPdpActCnfEvt->stPdpAddr.enPdpType, ucPdpId, ucCid);
    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &pstPdpActCnfEvt->stPdpAddr))
    {
        pstPdpActCnfEvt->bitOpPdpAddr        = VOS_TRUE;
    }

    pstPdpActCnfEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &pstPdpActCnfEvt->stApn))
    {
        pstPdpActCnfEvt->bitOpApn = VOS_TRUE;
    }

    /* UMTS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpActCnfEvt->bitOpUmtsQos = VOS_TRUE;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpActCnfEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpActCnfEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpActCnfEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpActCnfEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpActCnfEvt->stTft);
    }
#endif

    if (APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType)
    {
        pstPdpActCnfEvt->bitOpLinkdRabId  = VOS_TRUE;
        pstPdpActCnfEvt->ucLinkdRabId     = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpImCnSigalFlag)
    {
        pstPdpActCnfEvt->bitOpImCnSignalFlg   = VOS_TRUE;
        pstPdpActCnfEvt->enImCnSignalFlg      = g_PdpEntity[ucPdpId].enImCnSignalFlg;
    }

    pstPdpActCnfEvt->bitOpEmergencyInd    = VOS_TRUE;
    pstPdpActCnfEvt->enEmergencyInd       = g_PdpEntity[ucPdpId].enEmergencyFlg;

    Aps_SetEvtDns(ucPdpId, &pstPdpActCnfEvt->stDns, &pstPdpActCnfEvt->stIpv6Dns);
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpActCnfEvt->stNbns);
    MN_APS_SetEvtGateWay(ucPdpId, pstPdpActCnfEvt);
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpActCnfEvt->stPcscf, &pstPdpActCnfEvt->stIpv6Pcscf);


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* CDMAģʽ������û��·�IPV4V6���ţ���ǰֻ֧��IPV4/IPV6֪ͨ�û���֧��˫ջ */
    TAF_APS_AddCauseForCdataDoalStackDailNotSuport(pstPdpActCnfEvt, ucPdpId, ucCid);


#endif

    /* ֪ͨADS PDP״̬����moduleΪimsa����Ҫ֪ͨADS PDP״̬ */
    TAF_APS_NotifyAdsWhenPdpAvtivated(pstPdpActCnfEvt);


#if (FEATURE_ON == FEATURE_IPV6)
    /* ����Ϊʵ���м�¼��ԭ��ֵ */
    MN_APS_SET_EVT_SM_CAUSE(pstPdpActCnfEvt, ucPdpId);
#endif

    /*����TAF�ṩ���¼��ϱ����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
                     pstPdpActCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU));


    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpActCnfEvt);

    APS_NORM_LOG("APS->APP ACT_CNF MSG ");

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_CONNECTED);

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
    enDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_1X    == enDataServiceMode)
    {
        /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
        CTTF_1X_RLP_RegUserDataUpdateCB(WUEPS_PID_TAF,TAF_APS_ProcRlpDataStatusCb);
    }

    if ((TAF_APS_RAT_TYPE_HRPD  == enDataServiceMode)
     || (TAF_APS_RAT_TYPE_EHRPD == enDataServiceMode))
    {
        /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);

    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */
#endif

    return;
}
VOS_VOID TAF_APS_SndPdpActivateRej(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU   stPdpActRejEvt;

    PS_MEM_SET(&stPdpActRejEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

   /* �������APP��������ļ���,���ֶ�Ӧ���𼤻�,�ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ */
    if ( (APS_APP_INIT_ACT != g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct)
        && (APS_APP_MANUL_ACT != g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct))
    {
        /* APS�Զ�����ļ���,���ϱ� */
        return;
    }

    stPdpActRejEvt.ucCid     = g_PdpEntity[ucPdpId].stClientInfo.ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpActRejEvt.ucCid, &stPdpActRejEvt.stCtrl);

    stPdpActRejEvt.enPdpType = TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    stPdpActRejEvt.enCause   = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ,
                     &stPdpActRejEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU));

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼PS�����쳣log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif



    return;
}
VOS_VOID TAF_APS_SndPdpActivateInd(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_ACTIVATE_IND_STRU  *pstPdpActIndEvt;

    pstPdpActIndEvt = (TAF_PS_CALL_PDP_ACTIVATE_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstPdpActIndEvt)
    {
        /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpActivateInd: PS_MEM_ALLOC Error!");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET(pstPdpActIndEvt, 0, sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* ��Ϣͷ */
    TAF_APS_SetPsCallEvtCtrl(ucPdpId, ucCid, &pstPdpActIndEvt->stCtrl);

    pstPdpActIndEvt->ucCid = ucCid;

    /* PDP���ͺ͵�ַ */
    pstPdpActIndEvt->stPdpAddr.enPdpType = TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum);
    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &pstPdpActIndEvt->stPdpAddr))
    {
        pstPdpActIndEvt->bitOpPdpAddr        = VOS_TRUE;
    }

    /* RBAID */
    pstPdpActIndEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    /* ����APN */
    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &pstPdpActIndEvt->stApn))
    {
        pstPdpActIndEvt->bitOpApn = VOS_TRUE;
    }

    /* UMTS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpActIndEvt->bitOpUmtsQos = VOS_TRUE;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpActIndEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpActIndEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpActIndEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpActIndEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpActIndEvt->stTft);
    }
#endif

    if (APS_PDP_ACT_SEC == g_PdpEntity[ucPdpId].ActType)
    {
        pstPdpActIndEvt->bitOpLinkdRabId  = VOS_TRUE;
        pstPdpActIndEvt->ucLinkdRabId     = g_PdpEntity[ucPdpId].ucLinkedNsapi;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpImCnSigalFlag)
    {
        pstPdpActIndEvt->bitOpImCnSignalFlg   = VOS_TRUE;
        pstPdpActIndEvt->enImCnSignalFlg      = g_PdpEntity[ucPdpId].enImCnSignalFlg;
    }

    pstPdpActIndEvt->bitOpEmergencyInd    = VOS_TRUE;
    pstPdpActIndEvt->enEmergencyInd       = g_PdpEntity[ucPdpId].enEmergencyFlg;

    /* DNS */
    Aps_SetEvtDns(ucPdpId, &pstPdpActIndEvt->stDns, &pstPdpActIndEvt->stIpv6Dns);

    /* NBNS */
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpActIndEvt->stNbns);

    /* GATE WAY */
    MN_APS_SetEvtGateWay(ucPdpId, pstPdpActIndEvt);

    /* P-CSCF */
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpActIndEvt->stPcscf, &pstPdpActIndEvt->stIpv6Pcscf);

#if (FEATURE_ON == FEATURE_IPV6)
    MN_APS_SET_EVT_SM_CAUSE(pstPdpActIndEvt, ucPdpId);
#endif

    /* ����ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND��IMSA */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND,
                     pstPdpActIndEvt,
                     sizeof(TAF_PS_CALL_PDP_ACTIVATE_IND_STRU));

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpActIndEvt);

    APS_NORM_LOG("APS->APP ACT_IND MSG ");
    return;
}
VOS_UINT32 TAF_APS_SndPdpManageInd(
    VOS_UINT8                           ucPdpId,
    SMREG_PDP_ACTIVATE_IND_STRU        *pStActInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          ClientId;
    TAF_PS_CALL_PDP_MANAGE_IND_STRU     stPdpManageIndEvt;

    ClientId                            = TAF_CLIENTID_BROADCAST;

    /*clean "stPdpActIndEvt" */
    PS_MEM_SET(&stPdpManageIndEvt, 0, sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));

    /*��SM��������Ϣ����PDP������,�ֶ�Ӧ��ʱҪ��ȡ��Щ��Ϣ:ADDR, APN*/
    /*ADDR��Ϣ�ֽ�ΪADDRTYPE��ADDR������Ϣ*/
    ulRet   = Aps_DetachSmAddrStru(     &pStActInd->stOfferPdpAddr,
                                        &g_PdpEntity[ucPdpId].PdpAddr   );
    if ( TAF_APS_FAIL == ulRet)
    {
        APS_WARN_LOG("ERROR! Getting PpdAddr of ACT_IND fail ! Aps_PdpActInd()");
        return TAF_APS_FAIL;
    }
    g_PdpEntity[ucPdpId].PdpAddrFlag    = VOS_TRUE;

    /*APN*/
    if ( pStActInd->bitOpAcsPointName)
    {
        g_PdpEntity[ucPdpId].PdpApnFlag = VOS_TRUE;
        Aps_DetachSmApn(&pStActInd->stAcsPointName, &g_PdpEntity[ucPdpId].PdpApn);
    }

    /* GUģʽ�£��ֶ�Ӧ����AT��� */
    stPdpManageIndEvt.stCtrl.ulModuleId    = WUEPS_PID_AT;
    stPdpManageIndEvt.stCtrl.usClientId    = ClientId;

    /*�ϱ���APP��OpId���Ǵ�PDP����ı�ʶ,��OpId����120 + ucPdpId*/
    stPdpManageIndEvt.stCtrl.ucOpId        = APS_MT_DIFF_VALU + ucPdpId;

    if (VOS_OK == Aps_SetEvtAddr(ucPdpId, &stPdpManageIndEvt.stPdpAddr))
    {
        stPdpManageIndEvt.bitOpPdpAddr     = VOS_TRUE;
    }

    if (VOS_OK == Aps_SetEvtApn(ucPdpId, &stPdpManageIndEvt.stApn))
    {
        stPdpManageIndEvt.bitOpApn = VOS_TRUE;
    }

    /* ���PDP���� */

    stPdpManageIndEvt.stPdpAddr.enPdpType = TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum);

    /* ��¼�����緢��PDP��������ͣ�����answer���ϱ���� */
    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                g_PdpEntity[ucPdpId].stClientInfo.ucCid,
                                stPdpManageIndEvt.stPdpAddr.enPdpType);


    /* �ϱ�TAFM */
    APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MANAGE_IND,
                     &stPdpManageIndEvt,
                     sizeof(TAF_PS_CALL_PDP_MANAGE_IND_STRU));


    return TAF_APS_SUCC;
}
VOS_VOID TAF_APS_SndPdpModifyCnf(VOS_UINT8 ucPdpId)
{
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU        *pstPdpMdfCnfEvt;

    pstPdpMdfCnfEvt = (TAF_PS_CALL_PDP_MODIFY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstPdpMdfCnfEvt)
    {
        /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpModifyCnf: PS_MEM_ALLOC Error!");
        return;
    }

    PS_MEM_SET(pstPdpMdfCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    pstPdpMdfCnfEvt->ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    TAF_APS_GetPdpEntModDialInfo(ucPdpId, &pstPdpMdfCnfEvt->stCtrl);

    pstPdpMdfCnfEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    /* ����UMTS QOS */
    if (VOS_FALSE != g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpMdfCnfEvt->bitOpUmtsQos = TAF_USED;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpMdfCnfEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpMdfCnfEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpMdfCnfEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpMdfCnfEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpMdfCnfEvt->stTft);
    }
#endif

    Aps_SetEvtDns(ucPdpId, &pstPdpMdfCnfEvt->stDns, &pstPdpMdfCnfEvt->stIpv6Dns);
    MN_APS_SetEvtNbns(ucPdpId, &pstPdpMdfCnfEvt->stNbns);
    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpMdfCnfEvt->stPcscf, &pstPdpMdfCnfEvt->stIpv6Pcscf);

    /* ֪ͨADS PDP״̬ */
    TAF_APS_NotifyAdsWhenPdpModify(pstPdpMdfCnfEvt);

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_CNF,
                     pstPdpMdfCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_MODIFY_CNF_STRU));

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpMdfCnfEvt);

    return;
}


VOS_VOID TAF_APS_SndPdpModifyInd(
    VOS_UINT8                           ucPdpId
)
{
    TAF_PS_CALL_PDP_MODIFY_IND_STRU    *pstPdpMdfIndEvt;
    VOS_UINT8                           i;
    TAF_APS_BITCID_INFO_STRU            stCid;

    pstPdpMdfIndEvt = (TAF_PS_CALL_PDP_MODIFY_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                      sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstPdpMdfIndEvt)
    {
        /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPdpModifyInd: PS_MEM_ALLOC Error!");
        return;
    }

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    PS_MEM_SET(pstPdpMdfIndEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));

    pstPdpMdfIndEvt->ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    if (VOS_FALSE != g_PdpEntity[ucPdpId].PdpQosFlag)
    {
        pstPdpMdfIndEvt->bitOpUmtsQos = TAF_USED;
        Aps_3GQos2AppQos(&g_PdpEntity[ucPdpId].PdpQos, &pstPdpMdfIndEvt->stUmtsQos);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* EPS QOS */
    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpEpsQos)
    {
        pstPdpMdfIndEvt->bitOpEpsQos  = VOS_TRUE;
        pstPdpMdfIndEvt->stEpsQos     = g_PdpEntity[ucPdpId].stEpsQos;
    }

    if (VOS_TRUE == g_PdpEntity[ucPdpId].bitOpPf)
    {
        pstPdpMdfIndEvt->bitOpTft = VOS_TRUE;
        TAF_APS_SetEvtTftInfo(ucPdpId, &pstPdpMdfIndEvt->stTft);
    }
#endif

    Aps_SetEvtDns(ucPdpId, &pstPdpMdfIndEvt->stDns, &pstPdpMdfIndEvt->stIpv6Dns);

    MN_APS_SetEvtNbns(ucPdpId, &pstPdpMdfIndEvt->stNbns);

    TAF_APS_SetEvtPcscf(ucPdpId, &pstPdpMdfIndEvt->stPcscf, &pstPdpMdfIndEvt->stIpv6Pcscf);


    /* ����APN����ʱ���������û������ϱ�MODIFY */
    /* ��ȡ��ǰ����ʹ�ø�ʵ����û� */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

    for (i = 0; i < stCid.ulNum; i++)
    {
        pstPdpMdfIndEvt->ucCid = stCid.aucCid[i];

        TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpMdfIndEvt->ucCid, &pstPdpMdfIndEvt->stCtrl);

        /* ֪ͨADS PDP״̬ */
        TAF_APS_NotifyAdsWhenPdpModify(pstPdpMdfIndEvt);

        APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND");
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND,
                         pstPdpMdfIndEvt,
                         sizeof(TAF_PS_CALL_PDP_MODIFY_IND_STRU));
    }

    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpMdfIndEvt);

    return;
}
VOS_VOID    TAF_APS_SndPdpModifyRej   (
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    TAF_PS_CALL_PDP_MODIFY_REJ_STRU     stPdpMdfRejEvt;

    PS_MEM_SET(&stPdpMdfRejEvt, 0, sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));

    stPdpMdfRejEvt.ucCid = g_PdpEntity[ucPdpId].stClientInfo.ucCid;

    TAF_APS_GetPdpEntModDialInfo(ucPdpId, &stPdpMdfRejEvt.stCtrl);

    /* ���෢���MODIFY��ʱ�򱻾ܣ����ϱ� */
    if (0 == stPdpMdfRejEvt.stCtrl.ulModuleId)
    {
        return;
    }

    stPdpMdfRejEvt.enCause        = enCause;

    /*����TAFM�ṩ���¼��ϱ����� */
    APS_NORM_LOG("APS->APP ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_MODIFY_REJ,
                     &stPdpMdfRejEvt,
                     sizeof(TAF_PS_CALL_PDP_MODIFY_REJ_STRU));
    return;
}



VOS_VOID    TAF_APS_SndPdpDeActivateCnf(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU stPdpDeActCnfEvt;

    PS_MEM_SET(&stPdpDeActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    stPdpDeActCnfEvt.ucCid = ucCid;

    TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpDeActCnfEvt.ucCid, &stPdpDeActCnfEvt.stCtrl);

    TAF_APS_FillEvtPdpType(&stPdpDeActCnfEvt.enPdpType, ucPdpId, ucCid);

    stPdpDeActCnfEvt.ucRabId = g_PdpEntity[ucPdpId].ucNsapi;

    stPdpDeActCnfEvt.enCause = TAF_PS_CAUSE_SUCCESS;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



    /* ��CDS����ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND��Ϣ */
    TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

#endif

    /* ֪ͨADS PDP״̬ */
    TAF_APS_NotifyAdsWhenPdpDeactivated(&stPdpDeActCnfEvt);

    /* �����ǰΪCDMA 1X/EVDOģʽ����Ҫ��AT�ϱ��û����õ�IP ���� */
    TAF_APS_FillEvtPdpType(&stPdpDeActCnfEvt.enPdpType, ucPdpId, ucCid);

    APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF");
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
                    &stPdpDeActCnfEvt,
                    sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif

    return;
}
VOS_VOID    TAF_APS_SndPdpDeActivateInd(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU stPdpDeActIndEvt;
    VOS_UINT8                           i;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    PS_MEM_SET(&stPdpDeActIndEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

    stPdpDeActIndEvt.ucRabId = g_PdpEntity[ucPdpId].ucNsapi;
    stPdpDeActIndEvt.enCause = enCause;

    /* ��ȡ��ǰ����ʹ�ø�ʵ����û� */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

    for (i = 0; i < stCid.ulNum; i++)
    {
        stPdpDeActIndEvt.ucCid = stCid.aucCid[i];
        TAF_APS_FillEvtPdpType(&stPdpDeActIndEvt.enPdpType, ucPdpId, stPdpDeActIndEvt.ucCid);
        TAF_APS_SetPsCallEvtCtrl(ucPdpId, stPdpDeActIndEvt.ucCid, &stPdpDeActIndEvt.stCtrl);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)



        /* ��CDS����ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND��Ϣ */
        TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

#endif

        /* ֪ͨADS PDP״̬ */
        TAF_APS_NotifyAdsWhenPdpDeactivated(&stPdpDeActIndEvt);

        /* �����ǰΪCDMA 1X/EVDOģʽ����Ҫ��AT�ϱ��û����õ�IP ���� */
        TAF_APS_FillEvtPdpType(&stPdpDeActIndEvt.enPdpType, ucPdpId, stPdpDeActIndEvt.ucCid);

        APS_NORM_LOG("APS->APP  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND");
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND,
                         &stPdpDeActIndEvt,
                         sizeof(TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU));

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }
    return;
}
VOS_VOID TAF_APS_SndPdpDisconnectInd(VOS_UINT8 ucPdpId)
{
    TAF_CTRL_STRU                       stCtrl;
    VOS_UINT8                           ucCid;

    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    stCtrl.usClientId = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);
    if (TAF_APS_INVALID_CLIENTID == stCtrl.usClientId)
    {
        stCtrl.usClientId = TAF_CLIENTID_BROADCAST;
    }

    stCtrl.ulModuleId = TAF_APS_GetPdpEntModuleId(ucPdpId, ucCid);
    stCtrl.ucOpId     = TAF_APS_GetPdpEntOpId(ucPdpId, ucCid);

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DISCONNECT_IND,
                                &stCtrl,
                                sizeof(TAF_CTRL_STRU));

    return;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_VOID TAF_APS_SndIpv6RaInfoNotifyInd(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucRabId,
    TAF_PDP_IPV6_RA_INFO_STRU          *pstIpv6RaInfo
)
{
    TAF_PS_IPV6_INFO_IND_STRU           stIpv6RaInfoNotifyInd;

    stIpv6RaInfoNotifyInd.stCtrl        = *pstCtrl;
    stIpv6RaInfoNotifyInd.ucCid         = ucCid;
    stIpv6RaInfoNotifyInd.ucRabId       = ucRabId;
    stIpv6RaInfoNotifyInd.stIpv6RaInfo  = *pstIpv6RaInfo;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND,
                               &stIpv6RaInfoNotifyInd,
                               sizeof(TAF_PS_IPV6_INFO_IND_STRU));

    return;
}
#endif


VOS_VOID TAF_APS_SndCallOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_ORIG_CNF_STRU           stCallOrigCnf;

    PS_MEM_SET(&stCallOrigCnf, 0x00, sizeof(TAF_PS_CALL_ORIG_CNF_STRU));

    /* ��д�¼����� */
    stCallOrigCnf.stCtrl    = *pstCtrl;
    stCallOrigCnf.ucCid     = ucCid;
    stCallOrigCnf.enCause   = enCause;

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_ORIG_CNF,
                                &stCallOrigCnf,
                                sizeof(TAF_PS_CALL_ORIG_CNF_STRU));
#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼PS�����쳣log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif

    return;
}
VOS_VOID TAF_APS_SndCallEndCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_END_CNF_STRU            stCallEndCnf;

    PS_MEM_SET(&stCallEndCnf, 0, sizeof(TAF_PS_CALL_END_CNF_STRU));

    /* ��д�¼����� */
    stCallEndCnf.stCtrl         = *pstCtrl;
    stCallEndCnf.ucCid          = ucCid;

    stCallEndCnf.enCause        = enCause;

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_END_CNF,
                                &stCallEndCnf,
                                sizeof(TAF_PS_CALL_END_CNF_STRU));

    return;
}


VOS_VOID TAF_APS_SndCallModifyCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_CALL_MODIFY_CNF_STRU         stCallModifyCnf;

    PS_MEM_SET(&stCallModifyCnf, 0, sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));

    /* ��д�¼����� */
    stCallModifyCnf.stCtrl  = *pstCtrl;
    stCallModifyCnf.enCause = enCause;

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_MODIFY_CNF,
                                &stCallModifyCnf,
                                sizeof(TAF_PS_CALL_MODIFY_CNF_STRU));

    return;
}


VOS_VOID TAF_APS_SndCallAnswerCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucErrCode
)
{
    TAF_PS_CALL_ANSWER_CNF_STRU         stCallAnswerCnf;

    PS_MEM_SET(&stCallAnswerCnf, 0, sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));

    /* ��д�¼����� */
    stCallAnswerCnf.stCtrl          = *pstCtrl;
    stCallAnswerCnf.ucCid           = ucCid;

    if ( TAF_ERR_NO_ERROR != ucErrCode )
    {
        if (TAF_ERR_AT_CONNECT == ucErrCode)
        {
            stCallAnswerCnf.enCause = ucErrCode;
        }
        else
        {
            stCallAnswerCnf.enCause = TAF_ERR_ERROR;
        }
    }
    else
    {
        stCallAnswerCnf.enCause = ucErrCode;
    }

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_ANSWER_CNF,
                                &stCallAnswerCnf,
                                sizeof(TAF_PS_CALL_ANSWER_CNF_STRU));

    return;
}


VOS_VOID TAF_APS_SndCallHangupCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucErrCode
)
{
    TAF_PS_CALL_HANGUP_CNF_STRU         stCallHangupCnf;

    PS_MEM_SET(&stCallHangupCnf, 0, sizeof(TAF_PS_CALL_HANGUP_CNF_STRU));

    /* ��д�¼����� */
    stCallHangupCnf.stCtrl       = *pstCtrl;

    if ( TAF_ERR_NO_ERROR != ucErrCode )
    {
        stCallHangupCnf.enCause = TAF_ERR_ERROR;
    }
    else
    {
        stCallHangupCnf.enCause = ucErrCode;
    }

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_HANGUP_CNF,
                                &stCallHangupCnf,
                                sizeof(TAF_PS_CALL_HANGUP_CNF_STRU));

    return;
}


VOS_VOID TAF_APS_SndSetPdpCtxStateCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_PDP_STATE_CNF_STRU       stSetPdpStateCnf;

    PS_MEM_SET(&stSetPdpStateCnf, 0x00, sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));

    /* ��д�¼����� */
    stSetPdpStateCnf.stCtrl             = *pstCtrl;
    stSetPdpStateCnf.enCause            = enCause;

    /* �����¼� */
   (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_CONTEXT_STATE_CNF,
                                &stSetPdpStateCnf,
                                sizeof(TAF_PS_SET_PDP_STATE_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetPdpStateCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_CONTEXT_STATE_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_VOID  TAF_APS_SndSetPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stSetPdpCtxInfoCnf;

    stSetPdpCtxInfoCnf.stCtrl       = *pstCtrl;
    stSetPdpCtxInfoCnf.enCause      = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF,
                                &stSetPdpCtxInfoCnf,
                                sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetPrimPdpCtxInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_VOID  TAF_APS_SndSetSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU    stSetPdpCtxInfoCnf;

    stSetPdpCtxInfoCnf.stCtrl    = *pstCtrl;
    stSetPdpCtxInfoCnf.enCause  = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF,
                                &stSetPdpCtxInfoCnf,
                                sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetSecPdpCtxInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_VOID  TAF_APS_SndSetTftInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_TFT_INFO_CNF_STRU        stSetTftInfoCnf;

    stSetTftInfoCnf.stCtrl      = *pstCtrl;
    stSetTftInfoCnf.enCause = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_TFT_INFO_CNF,
                                &stSetTftInfoCnf,
                                sizeof(TAF_PS_SET_TFT_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetTftInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_TFT_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndSetUmtsQosInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU   stSetUmtsQosInfoCnf;

    stSetUmtsQosInfoCnf.stCtrl  = *pstCtrl;
    stSetUmtsQosInfoCnf.enCause = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_UMTS_QOS_INFO_CNF,
                                &stSetUmtsQosInfoCnf,
                                sizeof(TAF_PS_SET_UMTS_QOS_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_UMTS_QOS_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndSetUmtsQosMinInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU   stSetUmtsQosMinInfoCnf;

    stSetUmtsQosMinInfoCnf.stCtrl       = *pstCtrl;
    stSetUmtsQosMinInfoCnf.enCause  = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF,
                                &stSetUmtsQosMinInfoCnf,
                                sizeof(TAF_PS_SET_UMTS_QOS_MIN_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetUmtsQosMinInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetDynamicUmtsQosInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetPdpIpAddrInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_IP_ADDR_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_VOID  TAF_APS_SndSetAnsModeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU    stSetAnsModeInfoCnf;

    stSetAnsModeInfoCnf.stCtrl      = *pstCtrl;
    stSetAnsModeInfoCnf.enCause = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_ANSWER_MODE_INFO_CNF,
                                &stSetAnsModeInfoCnf,
                                sizeof(TAF_PS_SET_ANSWER_MODE_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetAnsModeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulAnsMode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU    stGetAnsModeInfoCnf;

    stGetAnsModeInfoCnf.stCtrl      = *pstCtrl;
    stGetAnsModeInfoCnf.enCause = ulErrCode;
    stGetAnsModeInfoCnf.ulAnsMode   = ulAnsMode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_ANSWER_MODE_INFO_CNF,
                                &stGetAnsModeInfoCnf,
                                sizeof(TAF_PS_GET_ANSWER_MODE_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                                          ulResult;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU   stGetDynamicPdpCtxInfoCnf;

    stGetDynamicPdpCtxInfoCnf.stCtrl        = *pstCtrl;
    stGetDynamicPdpCtxInfoCnf.enCause       = ulErrCode;
    stGetDynamicPdpCtxInfoCnf.ulCidNum      = ulCidNum;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF,
                                &stGetDynamicPdpCtxInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU));

    return ulResult;
}


VOS_VOID  TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU    stGetDynamicPdpCtxInfoCnf;

    stGetDynamicPdpCtxInfoCnf.stCtrl        = *pstCtrl;
    stGetDynamicPdpCtxInfoCnf.enCause       = ulErrCode;
    stGetDynamicPdpCtxInfoCnf.ulCidNum      = ulCidNum;


    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF,
                                &stGetDynamicPdpCtxInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetDynamicTftInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU    stGetDynamicTftInfoCnf;

    stGetDynamicTftInfoCnf.stCtrl       = *pstCtrl;
    stGetDynamicTftInfoCnf.enCause      = ulErrCode;
    stGetDynamicTftInfoCnf.ulCidNum     = ulCidNum;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF,
                                &stGetDynamicTftInfoCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU));

    return ulResult;
}


VOS_VOID  TAF_APS_SndDsFlowRptInd(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    TAF_PS_REPORT_DSFLOW_IND_STRU       stReportDsFlowInd;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();
    ulChkCurcRptFlg             = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                    TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                    TAF_SDC_RPT_CMD_DSFLOWRPT);

    ulChkUnsolicitedRptFlg      = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                    TAF_SDC_RPT_CMD_DSFLOWRPT);

    /* �ж������ϱ��Ƿ�� */
    if ( (VOS_FALSE == ulChkUnsolicitedRptFlg)
      || (VOS_FALSE == ulChkCurcRptFlg) )
    {
        return;
    }

    stReportDsFlowInd.stCtrl            = *pstCtrl;
    stReportDsFlowInd.enCause           = ulErrCode;
    stReportDsFlowInd.stDsFlowRptInfo   = *pstDsFlowRptInfo;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_REPORT_DSFLOW_IND,
                                &stReportDsFlowInd,
                                sizeof(TAF_PS_REPORT_DSFLOW_IND_STRU));

    return;
}
VOS_VOID  TAF_APS_SndClearDsFlowCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CLEAR_DSFLOW_CNF_STRU        stClearDsFlowCnf;

    stClearDsFlowCnf.stCtrl         = *pstCtrl;
    stClearDsFlowCnf.enCause        = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CLEAR_DSFLOW_CNF,
                               &stClearDsFlowCnf,
                               sizeof(TAF_PS_CLEAR_DSFLOW_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndConfigDsFlowRptCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU   stClearDsFlowCnf;

    stClearDsFlowCnf.stCtrl         = *pstCtrl;
    stClearDsFlowCnf.enCause        = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CONFIG_DSFLOW_RPT_CNF,
                               &stClearDsFlowCnf,
                               sizeof(TAF_PS_CONFIG_DSFLOW_RPT_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndSetPdpAuthInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU       stSetPdpAuthInfoCnf;

    stSetPdpAuthInfoCnf.stCtrl          = *pstCtrl;
    stSetPdpAuthInfoCnf.enCause         = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_AUTH_INFO_CNF,
                                &stSetPdpAuthInfoCnf,
                                sizeof(TAF_PS_SET_PDP_AUTH_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndSetAuthDataInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                                 ulResult;
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU          stSetAuthDataInfoCnf;

    stSetAuthDataInfoCnf.stCtrl         = *pstCtrl;
    stSetAuthDataInfoCnf.enCause        = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF,
                                &stSetAuthDataInfoCnf,
                                sizeof(TAF_PS_SET_AUTHDATA_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetPdpAuthInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_AUTH_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetAuthDataInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_AUTHDATA_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndSetPdpDnsInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_SET_PDP_DNS_INFO_CNF_STRU        stSetPdpDnsInfoCnf;

    stSetPdpDnsInfoCnf.stCtrl           = *pstCtrl;
    stSetPdpDnsInfoCnf.enCause          = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_DNS_INFO_CNF,
                                &stSetPdpDnsInfoCnf,
                                sizeof(TAF_PS_SET_PDP_DNS_INFO_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetPdpDnsInfoCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_DNS_INFO_CNF,
                                pData,
                                ulLength);

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGetGprsActiveTypeCnf(
    TAF_CTRL_STRU                       *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_CID_GPRS_ACTIVE_TYPE_STRU      *pstCidGprsActiveType
)
{
    VOS_UINT32                              ulResult;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU  stGetGprsActiveTypeCnf;

    stGetGprsActiveTypeCnf.stCtrl               = *pstCtrl;
    stGetGprsActiveTypeCnf.enCause              = ulErrCode;
    stGetGprsActiveTypeCnf.stCidGprsActiveType  = *pstCidGprsActiveType;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF,
                               &stGetGprsActiveTypeCnf,
                               sizeof(TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF_STRU));

    return ulResult;
}


VOS_VOID TAF_APS_SndPppDialOrigCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_PPP_DIAL_ORIG_CNF_STRU       stPppDialOrigCnf;

    PS_MEM_SET(&stPppDialOrigCnf, 0x00, sizeof(TAF_PS_PPP_DIAL_ORIG_CNF_STRU));

    /* ��д�¼����� */
    stPppDialOrigCnf.stCtrl             = *pstCtrl;
    stPppDialOrigCnf.enCause            = enCause;

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF,
                               &stPppDialOrigCnf,
                               sizeof(TAF_PS_PPP_DIAL_ORIG_CNF_STRU));

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼PS�����쳣log */
    TAF_APS_PsCallFailErrRecord(enCause);
#endif

    return;
}
VOS_VOID  TAF_APS_SndGetDsFlowInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode,
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo
)
{
    TAF_PS_GET_DSFLOW_INFO_CNF_STRU    stGetDsFlowInfoCnf;

    stGetDsFlowInfoCnf.stCtrl       = *pstCtrl;
    stGetDsFlowInfoCnf.enCause      =  ulErrCode;
    stGetDsFlowInfoCnf.stQueryInfo  = *pstDsFlowQryInfo;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DSFLOW_INFO_CNF,
                                &stGetDsFlowInfoCnf,
                                sizeof(TAF_PS_GET_DSFLOW_INFO_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndSetCgeqosCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_EPS_QOS_INFO_CNF_STRU            stSetCgeqosCnf;

    stSetCgeqosCnf.stCtrl   = *pstCtrl;
    stSetCgeqosCnf.enCause  = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_EPS_QOS_INFO_CNF,
                                &stSetCgeqosCnf,
                                sizeof(TAF_PS_SET_EPS_QOS_INFO_CNF_STRU));

    return;
}


VOS_UINT32  TAF_APS_SndGetCgeqosCnf(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulResult;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF,
                               pData,
                               ulLength);

    return ulResult;
}


VOS_VOID  TAF_APS_SndGetCgeqosrdpCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU    stGetCgeqosCnf;

    (VOS_VOID)VOS_MemSet(&stGetCgeqosCnf, 0, sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU));

    stGetCgeqosCnf.stCtrl               = *pstCtrl;
    stGetCgeqosCnf.enCause              = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF,
                                &stGetCgeqosCnf,
                                sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU));

    return;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_SndSetDialModeCnf
 ��������  :
 �������  : TAF_CTRL_STRU                      *pstCtrl,
             VOS_UINT32                          ulErrCode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��02��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_SndSetDialModeCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          enCause
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CDATA_DIAL_MODE_CNF_STRU     stSetDialModeCnf;

    PS_MEM_SET(&stSetDialModeCnf, 0x00, sizeof(TAF_PS_CDATA_DIAL_MODE_CNF_STRU));

    stSetDialModeCnf.stCtrl     = *pstCtrl;
    stSetDialModeCnf.enCause    = enCause;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CDMA_DIAL_MODE_CNF,
                                &stSetDialModeCnf,
                                sizeof(TAF_PS_CDATA_DIAL_MODE_CNF_STRU));

    return ulResult;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */

VOS_UINT32  TAF_APS_SndGetCgmtuValueCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulMtuValue
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_GET_CGMTU_VALUE_CNF_STRU     stCgmtuValueCnf;

    PS_MEM_SET(&stCgmtuValueCnf, 0x00, sizeof(TAF_PS_GET_CGMTU_VALUE_CNF_STRU));

    stCgmtuValueCnf.stCtrl     = *pstCtrl;
    stCgmtuValueCnf.ulMtuValue = ulMtuValue;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CGMTU_VALUE_CNF,
                                &stCgmtuValueCnf,
                                sizeof(TAF_PS_GET_CGMTU_VALUE_CNF_STRU));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndCgmtuValueChangeInd(
    VOS_UINT32                          ulMtuValue
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CGMTU_VALUE_CHG_IND_STRU     stCgmtuValueChgInd;

    PS_MEM_SET(&stCgmtuValueChgInd, 0x00, sizeof(TAF_PS_CGMTU_VALUE_CHG_IND_STRU));

    stCgmtuValueChgInd.stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCgmtuValueChgInd.stCtrl.usClientId   = MN_CLIENT_ID_BROADCAST;
    stCgmtuValueChgInd.stCtrl.ucOpId       = 0;
    stCgmtuValueChgInd.ulMtuValue          = ulMtuValue;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CGMTU_VALUE_CHG_IND,
                                &stCgmtuValueChgInd,
                                sizeof(TAF_PS_CGMTU_VALUE_CHG_IND_STRU));

    return ulResult;
}


VOS_VOID  TAF_APS_SndSetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU    stSetRptCfgCnf;

    stSetRptCfgCnf.stCtrl  = *pstCtrl;
    stSetRptCfgCnf.enCause = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_APDSFLOW_RPT_CFG_CNF,
                                &stSetRptCfgCnf,
                                sizeof(TAF_PS_SET_APDSFLOW_RPT_CFG_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndGetApDsFlowRptCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APDSFLOW_RPT_CFG_STRU          *pstRptCfg
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU    stGetRptCfgCnf;

    stGetRptCfgCnf.stCtrl   = *pstCtrl;
    stGetRptCfgCnf.enCause  = enCause;
    stGetRptCfgCnf.stRptCfg = *pstRptCfg;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_APDSFLOW_RPT_CFG_CNF,
                                &stGetRptCfgCnf,
                                sizeof(TAF_PS_GET_APDSFLOW_RPT_CFG_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndApDsFlowRptInd(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APDSFLOW_REPORT_STRU           *pstRptInfo
)
{
    TAF_PS_APDSFLOW_REPORT_IND_STRU     stRptInd;

    stRptInd.stCtrl            = *pstCtrl;
    stRptInd.stApDsFlowRptInfo = *pstRptInfo;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_APDSFLOW_REPORT_IND,
                                &stRptInd,
                                sizeof(TAF_PS_APDSFLOW_REPORT_IND_STRU));

    return;
}


VOS_VOID  TAF_APS_SndSetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU stSetNvWriteCfgCnf;

    stSetNvWriteCfgCnf.stCtrl  = *pstCtrl;
    stSetNvWriteCfgCnf.enCause = enCause;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF,
                                &stSetNvWriteCfgCnf,
                                sizeof(TAF_PS_SET_DSFLOW_NV_WRITE_CFG_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndGetDsFlowNvWriteCfgCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_DSFLOW_NV_WRITE_CFG_STRU       *pstNvWriteCfg
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU stGetNvWriteCfgCnf;

    stGetNvWriteCfgCnf.stCtrl      = *pstCtrl;
    stGetNvWriteCfgCnf.enCause     = enCause;
    stGetNvWriteCfgCnf.stNvWriteCfg = *pstNvWriteCfg;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF,
                                &stGetNvWriteCfgCnf,
                                sizeof(TAF_PS_GET_DSFLOW_NV_WRITE_CFG_CNF_STRU));

    return;
}


VOS_UINT32 MN_APS_ValidateCidList(
    VOS_UINT8                       aucCidList[],
    VOS_UINT32                     *pulCidNum
)
{
    VOS_UINT32                          i;

    /* ��ʼ�� */
    *pulCidNum  = 0;

    /* ���CID�б��Ƿ�ȫ0 */
    for ( i = 1; i <= TAF_MAX_CID; i++ )
    {
        if ( VOS_TRUE == aucCidList[i] )
        {
            (*pulCidNum)++;
        }
    }

    /* CID����Ϊ0, ��CID�б���Ч */
    if ( 0 == (*pulCidNum) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 MN_APS_BuildCidProcList(
    VOS_UINT8                           aucCidList[],
    VOS_UINT8                           aucCidProcList[]
)
{
    VOS_UINT32                          ulCidNum;

    /* ��ʼ�� */
    ulCidNum = 0;

    /* ���CID�б��Ƿ���Ч */
    if ( VOS_FALSE == MN_APS_ValidateCidList(aucCidList,
                                             &ulCidNum) )
    {
        PS_MEM_SET(aucCidProcList, 0x01, (TAF_MAX_CID + 1));
    }
    else
    {
        PS_MEM_CPY(aucCidProcList, aucCidList, (TAF_MAX_CID + 1));
    }

    return VOS_OK;
}


VOS_VOID MN_APS_RandomBytes(
    VOS_UINT8                           *pucBuf,
    VOS_UINT16                           usLen
)
{
    VOS_UINT16 usLoop;

    for (usLoop = 0; usLoop < usLen; ++usLoop)
    {
        pucBuf[usLoop] = (TAF_UINT8)VOS_Rand(0xff);
    }

    return;
}


PPP_AUTH_TYPE_ENUM_UINT8 MN_APS_CtrlGetAuthType(
    PPP_AUTH_TYPE_ENUM_UINT8            enAuthType
)
{
    /* ��֧��MS_CHAPV2, Ĭ��ʹ��CHAP */
    if ( PPP_MS_CHAPV2_AUTH_TYPE == enAuthType )
    {
        return PPP_CHAP_AUTH_TYPE;
    }
    else
    {
        return enAuthType;
    }
}

/*lint -e438 -e830*/

VOS_UINT32 MN_APS_CtrlMakePCOPapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    TAF_PPP_FRAME_HEAD_STRU            *pstPppHead;
    VOS_UINT8                          *pucPapFrame;
    VOS_UINT8                          *pucBuff;
    VOS_UINT16                          usPapLen;

    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.usPapReqLen = 0;
    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq     = VOS_NULL_PTR;

    /* ����PAP֡�ܳ���*/
    usPapLen = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8) + usUserNameLen
                        + sizeof(VOS_UINT8) + usPassWordLen;

    /* �����ڴ�*/
    pucPapFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usPapLen);
    if (VOS_NULL_PTR == pucPapFrame)
    {
        MN_ERR_LOG("MN_APS_CtrlMakePCOPapAuthInfo:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ��дͷ��*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU*)pucPapFrame;
    pstPppHead->ucCode      = TAF_PPP_CODE_REQ;
    pstPppHead->ucId        = TAF_PPP_DEF_ID;
    pstPppHead->usLength    = TAF_HTONS(usPapLen);

    pucBuff  = (VOS_UINT8*)(pstPppHead + 1);
/*lint -e961*/
    /* ��д�û������� + �û���*/
    *(pucBuff ++) = (VOS_UINT8)usUserNameLen;
    if (0 != usUserNameLen)
    {
        PS_MEM_CPY(pucBuff, pucUserName, usUserNameLen);
        pucBuff += usUserNameLen;
    }

    /* ��д���볤�� + �û���*/
    *(pucBuff ++) = (VOS_UINT8)usPassWordLen;
    if (0 != usPassWordLen)
    {
        PS_MEM_CPY(pucBuff, pucPassWord, usPassWordLen);
        pucBuff += usPassWordLen;
    }
/*lint +e961*/

    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.usPapReqLen = usPapLen;
    pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq     = pucPapFrame;

    return VOS_OK;
}
/*lint +e438 +e830*/



VOS_UINT32 MN_APS_CtrlMakePCOChapAuthInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    VOS_UINT16                          usChallengeLength   = 0;
    VOS_UINT16                          usResponseLength    = 0;
    VOS_UINT8                           ucId                = TAF_PPP_DEF_ID;
    VOS_UINT8                           aucChapSrvName[]    = {'h','u','a','w','e','i','.','c','o','m'};  /* CHAP Challenge�е��û���,10 byte,����'\0'��β*/
    VOS_UINT8                          *pucChallengeFrame  = VOS_NULL_PTR;
    VOS_UINT8                          *pucChallenge       = VOS_NULL_PTR;
    VOS_UINT8                          *pucResponseFrame   = VOS_NULL_PTR;
    VOS_UINT8                          *pucBuff            = VOS_NULL_PTR;
    TAF_PPP_FRAME_HEAD_STRU            *pstPppHead         = VOS_NULL_PTR;
    TAF_MSG_DIGEST_FIVE_CTX             stCtx;

    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge = VOS_NULL_PTR;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse  = VOS_NULL_PTR;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = 0;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = 0;

    /* ����challenge�ܳ���*/
    usChallengeLength = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8)
                        + TAF_AP_PPP_CHAP_CHALLENGE_LEN + sizeof(aucChapSrvName);

    /* ����response�ܳ���*/
    usResponseLength = sizeof(TAF_PPP_FRAME_HEAD_STRU) + sizeof(VOS_UINT8)
                        + TAF_AP_PPP_CHAP_RESPONSE_LEN + usUserNameLen;

    /* ����challenge�ڴ�*/
    pucChallengeFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usChallengeLength);
    if (VOS_NULL_PTR == pucChallengeFrame)
    {
        MN_ERR_LOG("MN_APS_CtrlMakePCOChapAuthInfo: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ����response�ڴ�*/
    pucResponseFrame = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usResponseLength);
    if (VOS_NULL_PTR == pucResponseFrame)
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeFrame);
        MN_ERR_LOG("MN_APS_CtrlMakePCOChapAuthInfo: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(pucChallengeFrame, 0, usChallengeLength);
    PS_MEM_SET(pucResponseFrame, 0, usResponseLength);

   /* ����challenge*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU *)pucChallengeFrame;
    pstPppHead->ucCode      = TAF_AP_PPP_CODE_CHALLENGE;
    pstPppHead->ucId        = ucId;
    pstPppHead->usLength    = TAF_HTONS(usChallengeLength);

    pucBuff         = pucChallengeFrame + sizeof(TAF_PPP_FRAME_HEAD_STRU);

/*lint -e961*/
    /*length*/
    *(pucBuff ++)   = TAF_AP_PPP_CHAP_CHALLENGE_LEN;
    pucChallenge    = pucBuff;

    /*random challenge*/
    MN_APS_RandomBytes(pucBuff, TAF_AP_PPP_CHAP_CHALLENGE_LEN);
    pucBuff        += TAF_AP_PPP_CHAP_CHALLENGE_LEN;

    /*name*/
    PS_MEM_CPY(pucBuff, aucChapSrvName, sizeof(aucChapSrvName));

    /* ����challenge*/
    pstPppHead              = (TAF_PPP_FRAME_HEAD_STRU *)pucResponseFrame;
    pstPppHead->ucCode      = TAF_AP_PPP_CODE_RESPONSE;
    pstPppHead->ucId        = ucId;
    pstPppHead->usLength    = TAF_HTONS(usResponseLength);

    pucBuff         = pucResponseFrame + sizeof(TAF_PPP_FRAME_HEAD_STRU);

    /*length*/
    *(pucBuff ++)   = TAF_AP_PPP_CHAP_RESPONSE_LEN;
/*lint +e961*/
    TAF_InitMsgDigestFiveCtxt(&stCtx);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, &ucId, 1);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, pucPassWord, usPassWordLen);
    TAF_UpdateMsgDigestFiveCtxt(&stCtx, pucChallenge, TAF_AP_PPP_CHAP_CHALLENGE_LEN);

    /*response*/
    TAF_EndMsgDigestFive(pucBuff, &stCtx);

    pucBuff += TAF_AP_PPP_CHAP_RESPONSE_LEN;
    if (0 != usUserNameLen)
    {

        /*name*/
        PS_MEM_CPY(pucBuff, pucUserName, usUserNameLen);
    }

    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge     = pucChallengeFrame;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = usChallengeLength;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse      = pucResponseFrame;
    pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = usResponseLength;

    return VOS_OK;
}
VOS_VOID MN_APS_CtrlFreePCOContext(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqCfgInfo
)
{
    if ( PPP_PAP_AUTH_TYPE == pstPppReqCfgInfo->stAuth.ucAuthType )
    {
        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.PapContent.pPapReq );
        }
    }

    if ( PPP_CHAP_AUTH_TYPE == pstPppReqCfgInfo->stAuth.ucAuthType )
    {
        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapChallenge);
        }

        if ( VOS_NULL_PTR != pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse )
        {
            PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stAuth.AuthContent.ChapContent.pChapResponse);
        }
    }

    if ( VOS_NULL_PTR != pstPppReqCfgInfo->stIPCP.pIpcp )
    {
        PS_MEM_FREE(WUEPS_PID_TAF, pstPppReqCfgInfo->stIPCP.pIpcp);
    }

    return;
}


TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvCallOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_DIAL_PARA_STRU              *pstDialParam
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    VOS_UINT32                          ulAuthMakeRslt;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;

    ulAuthMakeRslt = VOS_OK;
    enRet          = TAF_PS_CAUSE_SUCCESS;

    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));
    PS_MEM_SET(&stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));
    PS_MEM_SET(&stApn, 0x00, sizeof(TAF_PDP_APN_STRU));

    stPdpAddr.enPdpType = pstDialParam->enPdpType;

    if ( (VOS_TRUE == pstDialParam->bitOpIpAddr)
      && (TAF_PDP_IPV4 == pstDialParam->stPdpAddr.enPdpType) )
    {
        PS_MEM_CPY(stPdpAddr.aucIpv4Addr, pstDialParam->stPdpAddr.aucIpv4Addr, TAF_IPV4_ADDR_LEN);
    }

    if (VOS_TRUE == pstDialParam->bitOpApn)
    {
        stApn.ucLength = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)pstDialParam->aucApn);
        PS_MEM_CPY(stApn.aucValue, pstDialParam->aucApn, TAF_MAX_APN_LEN);

/* Added by zhuli for K3V3VSIM��Ŀ, 2014-10-16, begin */
        PIH_GetVsimAPN(TAF_MAX_APN_LEN, stApn.aucValue, &stApn.ucLength);
/* Added by zhuli for K3V3VSIM��Ŀ, 2014-10-16, end */
    }

    /* ��ȡ��Ȩ���� */
    if ( (VOS_FALSE == pstDialParam->bitOpAuthType)
      || (VOS_FALSE == pstDialParam->bitOpUserName) )
    {
        stPppConfigInfo.stAuth.ucAuthType = PPP_NO_AUTH_TYPE;
    }
    else
    {
        stPppConfigInfo.stAuth.ucAuthType = MN_APS_CtrlGetAuthType(pstDialParam->enAuthType);
    }

    /* ���ݼ�Ȩ�������ɼ�Ȩ��Ϣ */
    if (PPP_PAP_AUTH_TYPE == stPppConfigInfo.stAuth.ucAuthType)
    {
        ulAuthMakeRslt = MN_APS_CtrlMakePCOPapAuthInfo(
                                &stPppConfigInfo,
                                pstDialParam->aucUserName,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucUserName)),
                                pstDialParam->aucPassWord,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucPassWord)));
    }
    else if (PPP_CHAP_AUTH_TYPE == stPppConfigInfo.stAuth.ucAuthType)
    {
        ulAuthMakeRslt = MN_APS_CtrlMakePCOChapAuthInfo(
                                &stPppConfigInfo,
                                pstDialParam->aucUserName,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucUserName)),
                                pstDialParam->aucPassWord,
                                (VOS_UINT16)VOS_StrLen((VOS_CHAR *)(pstDialParam->aucPassWord)));
    }
    else
    {
        ulAuthMakeRslt = VOS_OK;
    }

    if (VOS_OK != ulAuthMakeRslt)
    {
        stPppConfigInfo.stAuth.ucAuthType = PPP_NO_AUTH_TYPE;
    }

    enRet = TAF_APS_PsCallForDial(ucPdpId,
                                  &stPdpAddr,
                                  &stApn,
                                  &stPppConfigInfo);

    /* �ͷ����ɵļ�Ȩ��Ϣ */
    MN_APS_CtrlFreePCOContext(&stPppConfigInfo);

    return enRet;
}
VOS_UINT32 MN_APS_RcvCallModifyReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq,
    VOS_UINT8                          *pucErrCode
)
{
    /* ��ʼ�� */
    *pucErrCode                         = TAF_ERR_NO_ERROR;

    /* �޸�PS CALL����: QOS�� */
    Aps_PsCallModify(pstCallModifyReq->stCtrl.usClientId,
                     pstCallModifyReq->stCtrl.ucOpId,
                     ucPdpId,
                     pucErrCode);
    if (TAF_ERR_NO_ERROR != *pucErrCode)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 MN_APS_RcvGetPdpCtxStateReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulPdpStateLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_PDP_STATE_CNF_STRU       stPdpStateNullCnf;
    TAF_PS_GET_PDP_STATE_CNF_STRU      *pstGetPdpStateCnf;
    TAF_PS_GET_PDP_STATE_REQ_STRU      *pstGetPdpStateReq;

    /* ��ʼ�� */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpStateLen       = 0;
    ulCidNum            = 0;
    pstGetPdpStateCnf   = VOS_NULL_PTR;
    pstGetPdpStateReq   = (TAF_PS_GET_PDP_STATE_REQ_STRU*)pMsgData;

    /* �����¼����ݳ��� */
    ulPdpStateLen       = sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_CID_STATE_STRU));

    /* �����ڴ� */
    pstGetPdpStateCnf   = (TAF_PS_GET_PDP_STATE_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpStateLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpStateCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq:  ERROR : PS_MEM_ALLOC Error!");

        stPdpStateNullCnf.stCtrl    = pstGetPdpStateReq->stCtrl;
        stPdpStateNullCnf.ulCidNum  = 0;
        stPdpStateNullCnf.enCause   = TAF_PARA_OK;

        return TAF_APS_SndGetPdpStateCnf(&stPdpStateNullCnf,
                                        sizeof(TAF_PS_GET_PDP_STATE_CNF_STRU));
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpStateCnf->astCidStateInfo[ulCidNum]),
                   0x00, sizeof(TAF_CID_STATE_STRU));

        /* ��ȡָ��CID��Ӧ��PDP�����ĵ�״̬ */
        Aps_QueState(ucIndex,
                     &(pstGetPdpStateCnf->astCidStateInfo[ulCidNum]),
                     &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetPdpStateCnf->stCtrl   = pstGetPdpStateReq->stCtrl;
    pstGetPdpStateCnf->ulCidNum = ulCidNum;
    pstGetPdpStateCnf->enCause  = TAF_PS_CAUSE_SUCCESS;

    /* ���ش����� */
    ulResult = TAF_APS_SndGetPdpStateCnf(pstGetPdpStateCnf,
                                        ulPdpStateLen);

    /* �ͷ����ڴ��PDP������״̬���ڴ�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpStateCnf);

    return ulResult;
}
VOS_VOID MN_APS_RcvSetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                  ulErrCode;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstSetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulErrCode           = TAF_PARA_OK;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;


    /* PDP�����������Դ򿪣���ͣ���ʱ���������� */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
    {
        TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(pstSetPdpCtxInfoReq);
    }


    /* ����Primary PDP������ */
    Aps_DefPsPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                        pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                        &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                        &ulErrCode);


    /* ���ش����� */
    TAF_APS_SndSetPrimPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl),
                                              ulErrCode);

    return;
}


VOS_UINT32 MN_APS_RcvGetPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstGetPdpCtxInfoReq;
    TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU  *pstGetPdpCtxInfoCnf;

    /* ��ʼ�� */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPrimPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ��д�¼����� */
#if (FEATURE_ON == FEATURE_LTE)
    for (ucIndex = 0; ucIndex <= TAF_MAX_CID; ucIndex++)
#else
    for (ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++)
#endif
    {
        PS_MEM_SET(&(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));

        /* ��ȡPrimary PDP��������Ϣ */
        Aps_QuePri(ucIndex, &(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]), &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetPdpCtxInfoCnf->stCtrl      = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum    = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause     = TAF_PARA_OK;

    /* ���ش����� */
    ulResult =  TAF_APS_SndGetPrimPdpCtxInfoCnf(pstGetPdpCtxInfoCnf,
                                               ulPdpCtxInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return ulResult;
}
VOS_VOID MN_APS_RcvSetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                  ulErrCode;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;

    /* ��ʼ�� */
    ulErrCode           = TAF_PARA_OK;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* ����Secondary PDP������ */
    Aps_DefPsSecPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                           pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                           &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                           &ulErrCode);

    /* ���ش����� */
    TAF_APS_SndSetSecPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl),
                                             ulErrCode);

    return;
}
VOS_VOID MN_APS_RcvGetSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ucErrCode;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstGetPdpCtxInfoReq;
    TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetPdpCtxInfoCnf;

    /* ��ʼ�� */
    ucErrCode           = TAF_PARA_OK;
    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PDP_SEC_CONTEXT_STRU));

    /* �����ڴ� */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_SEC_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetSecPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_PDP_SEC_CONTEXT_STRU));

        /* ��ȡSecondary PDP��������Ϣ */
        Aps_QueSec(ucIndex, &(pstGetPdpCtxInfoCnf->astPdpContextQueryInfo[ulCidNum]), &ucErrCode);

        if ( TAF_PARA_OK == ucErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetPdpCtxInfoCnf->stCtrl   = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause  = TAF_PARA_OK;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndGetSecPdpCtxInfoCnf(pstGetPdpCtxInfoCnf,
                                             ulPdpCtxInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return;
}
VOS_VOID MN_APS_RcvSetTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstSetTftInfoReq;

    /* ��ʼ�� */
    ulErrCode           = TAF_PARA_OK;
    pstSetTftInfoReq    = (TAF_PS_SET_TFT_INFO_REQ_STRU*)pMsgData;

    /* ����TFT���� */
    TAF_APS_SetTftInfo(&(pstSetTftInfoReq->stTftInfo), &ulErrCode);

    /* ���ش����� */
    TAF_APS_SndSetTftInfoCnf(&(pstSetTftInfoReq->stCtrl),
                                       ulErrCode);

    return;
}
VOS_UINT8 TAF_APS_GetRptTftInfoCidNum(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCidNum;

    /* ������ʼ�� */
    ucIndex         = 0;
    ucCidNum        = 0;

    /* ѭ������g_TafCidTab, ��ȡ��ЧTFT������CID���� */
    for (ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++)
    {
        if (TAF_USED == g_TafCidTab[ucIndex].ucPfTabFlag)
        {
            ucCidNum++;
        }
    }

    return ucCidNum;
}


VOS_UINT32 MN_APS_RcvGetTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulTftInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_TFT_INFO_REQ_STRU       *pstGetTftInfoReq;
    TAF_PS_GET_TFT_INFO_CNF_STRU       *pstGetTftInfoCnf;

    /* ��ʼ�� */
    ulResult            = VOS_OK;
    ulTftInfoLen        = 0;
    ulCidNum            = 0;
    pstGetTftInfoReq    = (TAF_PS_GET_TFT_INFO_REQ_STRU*)pMsgData;
    pstGetTftInfoCnf    = VOS_NULL_PTR;

    /* ��ȡ��TFT������CID�ĸ��� */
    ulCidNum            = TAF_APS_GetRptTftInfoCidNum();

    /* �����¼����ݳ��� */
    ulTftInfoLen        = sizeof(TAF_PS_GET_TFT_INFO_CNF_STRU)
                            + (ulCidNum * sizeof(TAF_TFT_QUREY_INFO_STRU));

    /* �����ڴ� */
    pstGetTftInfoCnf    = (TAF_PS_GET_TFT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulTftInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetTftInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPrimPdpCtxInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    PS_MEM_SET(pstGetTftInfoCnf, 0x00, ulTftInfoLen);
    ulCidNum            = 0;

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        /* ��CID�����Ķ�TFT����û�ж��� */
        if ( TAF_FREE == g_TafCidTab[ucIndex].ucPfTabFlag)
        {
            continue;
        }

        /* ��дTft Qry Param */
        TAF_APS_FillTftQryParam(ucIndex,
                              &(pstGetTftInfoCnf->astTftQueryInfo[ulCidNum]));

        ulCidNum++;
    }

    /* ��д�¼�����ͷ */
    pstGetTftInfoCnf->stCtrl    = pstGetTftInfoReq->stCtrl;
    pstGetTftInfoCnf->ulCidNum  = ulCidNum;
    pstGetTftInfoCnf->enCause   = TAF_PARA_OK;

    /* ���ش����� */
    ulResult =  TAF_APS_SndGetTftInfoCnf(pstGetTftInfoCnf,
                                        ulTftInfoLen);

    /* �ͷ��������ڴ��TFT�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetTftInfoCnf);

    return ulResult;
}
VOS_VOID MN_APS_RcvSetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU  *pstSetUmtsQosInfoReq;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    pstSetUmtsQosInfoReq    = (TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU*)pMsgData;

    /* ����UMTS QOS���� */
    Aps_DefPs3gReqQos(pstSetUmtsQosInfoReq->stCtrl.usClientId,
                      pstSetUmtsQosInfoReq->stCtrl.ucOpId,
                      &(pstSetUmtsQosInfoReq->stUmtsQosInfo),
                      &ulErrCode);

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndSetUmtsQosInfoCnf(&(pstSetUmtsQosInfoReq->stCtrl),
                                           ulErrCode);

    return;
}
VOS_VOID MN_APS_RcvGetUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulUmtsQosInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU  *pstGetUmtsQosInfoReq;
    TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU  *pstGetUmtsQosInfoCnf;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    ulUmtsQosInfoLen        = 0;
    ulCidNum                = 0;
    pstGetUmtsQosInfoReq    = (TAF_PS_GET_UMTS_QOS_INFO_REQ_STRU*)pMsgData;
    pstGetUmtsQosInfoCnf    = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulUmtsQosInfoLen        = sizeof(TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetUmtsQosInfoCnf    = (TAF_PS_GET_UMTS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulUmtsQosInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetUmtsQosInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

        /* ��ȡCID��Ӧ��UMTS QOS���� */
        MN_APS_GetUtmsQosInfo(ucIndex,
                              &(pstGetUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                              &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetUmtsQosInfoCnf->stCtrl    = pstGetUmtsQosInfoReq->stCtrl;
    pstGetUmtsQosInfoCnf->ulCidNum  = ulCidNum;
    pstGetUmtsQosInfoCnf->enCause   = TAF_PARA_OK;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndGetUmtsQosInfoCnf(pstGetUmtsQosInfoCnf,
                                           ulUmtsQosInfoLen);

    /* �ͷ����ڴ��UMTS QOS�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetUmtsQosInfoCnf);

    return;
}
VOS_VOID MN_APS_RcvSetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU  *pstSetUmtsQosMinInfoReq;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    pstSetUmtsQosMinInfoReq = (TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU*)pMsgData;

    /* ����UMTS MIN QOS���� */
    Aps_DefPs3gMinAcceptQos(pstSetUmtsQosMinInfoReq->stCtrl.usClientId,
                            pstSetUmtsQosMinInfoReq->stCtrl.ucOpId,
                            &(pstSetUmtsQosMinInfoReq->stUmtsQosMinInfo),
                            &ulErrCode);

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndSetUmtsQosMinInfoCnf(&(pstSetUmtsQosMinInfoReq->stCtrl),
                                              ulErrCode);

    return;
}
VOS_VOID MN_APS_RcvGetUmtsQosMinInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulUmtsQosMinInfoLen;
    VOS_UINT32                              ulCidNum;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU  *pstGetUmtsQosMinInfoReq;
    TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU  *pstGetUmtsQosMinInfoCnf;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    ulUmtsQosMinInfoLen     = 0;
    ulCidNum                = 0;
    pstGetUmtsQosMinInfoReq = (TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ_STRU*)pMsgData;
    pstGetUmtsQosMinInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulUmtsQosMinInfoLen     = sizeof(TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetUmtsQosMinInfoCnf = (TAF_PS_GET_UMTS_QOS_MIN_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulUmtsQosMinInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetUmtsQosMinInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosMinInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetUmtsQosMinInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

        /* ��ȡCID��Ӧ��UMTS MIN QOS���� */
        MN_APS_GetUtmsQosMinInfo(ucIndex,
                                 &(pstGetUmtsQosMinInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                                 &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetUmtsQosMinInfoCnf->stCtrl     = pstGetUmtsQosMinInfoReq->stCtrl;
    pstGetUmtsQosMinInfoCnf->ulCidNum   = ulCidNum;
    pstGetUmtsQosMinInfoCnf->enCause    = TAF_PARA_OK;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndGetUmtsQosMinInfoCnf(pstGetUmtsQosMinInfoCnf,
                                              ulUmtsQosMinInfoLen);

    PS_MEM_FREE(WUEPS_PID_TAF, pstGetUmtsQosMinInfoCnf);

    return;
}


VOS_VOID MN_APS_RcvGetDynamicUmtsQosInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   aucCidProcList[TAF_MAX_CID + 1];
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulCidNum;
    VOS_UINT32                                  ulDynamicUmtsQosInfoLen;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU  *pstDynamicUmtsQosInfoReq;
    TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU  *pstDynamicUmtsQosInfoCnf;

    /* ��ʼ�� */
    ulErrCode                = TAF_PARA_OK;
    ulDynamicUmtsQosInfoLen  = 0;
    ulCidNum                 = 0;
    pstDynamicUmtsQosInfoReq = (TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ_STRU*)pMsgData;
    pstDynamicUmtsQosInfoCnf = VOS_NULL_PTR;

    /* ����CID�����б� */
    PS_MEM_SET(aucCidProcList, 0x00, (TAF_MAX_CID + 1));
    if ( VOS_ERR == MN_APS_BuildCidProcList(pstDynamicUmtsQosInfoReq->stCidListInfo.aucCid,
                                            aucCidProcList) )
    {
        MN_WARN_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: Invalid CID list!");
    }

    /* �����¼����ݳ��� */
    ulDynamicUmtsQosInfoLen  = sizeof(TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstDynamicUmtsQosInfoCnf = (TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulDynamicUmtsQosInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstDynamicUmtsQosInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        if ( VOS_TRUE == aucCidProcList[ucIndex] )
        {
            PS_MEM_SET(&(pstDynamicUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                       0x00, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

            /* ��ȡCID��Ӧ��UMTS QOS��Ϣ */
            Aps_QueQosNeg(ucIndex,
                          &(pstDynamicUmtsQosInfoCnf->astUmtsQosQueryInfo[ulCidNum]),
                          &ulErrCode);

            if ( TAF_PARA_OK == ulErrCode )
            {
                ulCidNum++;
            }
        }
    }

    /* ��д�¼�����ͷ */
    pstDynamicUmtsQosInfoCnf->stCtrl    = pstDynamicUmtsQosInfoReq->stCtrl;
    pstDynamicUmtsQosInfoCnf->ulCidNum  = ulCidNum;
    pstDynamicUmtsQosInfoCnf->enCause   = TAF_PARA_OK;

    /* ���ش����� */
    if ( VOS_OK != TAF_APS_SndGetDynamicUmtsQosInfoCnf(pstDynamicUmtsQosInfoCnf,
                                                  ulDynamicUmtsQosInfoLen) )
    {
        MN_WARN_LOG("MN_APS_RcvGetDynamicUmtsQosInfoReq: TAF_APS_SndGetDynamicUmtsQosInfoCnf ERROR!");
    }

    /* �ͷ��������ڴ��UMTS QOS�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstDynamicUmtsQosInfoCnf);

    return;
}


VOS_UINT32 MN_APS_RcvGetPdpIpAddrInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                                   ucIndex;
    VOS_UINT8                                   aucCidProcList[TAF_MAX_CID + 1];
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulErrCode;
    VOS_UINT32                                  ulPdpIpAddrInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU       *pstPdpIpAddrInfoReq;
    TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU       *pstPdpIpAddrInfoCnf;

    /* ��ʼ�� */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpIpAddrInfoLen  = 0;
    ulCidNum            = 0;
    pstPdpIpAddrInfoReq = (TAF_PS_GET_PDP_IP_ADDR_INFO_REQ_STRU*)pMsgData;
    pstPdpIpAddrInfoCnf = VOS_NULL_PTR;

    /* ����CID�����б� */
    PS_MEM_SET(aucCidProcList, 0x00, (TAF_MAX_CID + 1));
    if ( VOS_ERR == MN_APS_BuildCidProcList(pstPdpIpAddrInfoReq->stCidListInfo.aucCid,
                                            aucCidProcList) )
    {
        MN_WARN_LOG("MN_APS_RcvGetPdpIpAddrInfoReq: Invalid CID list!");
    }

    /* �����¼����ݳ��� */
    ulPdpIpAddrInfoLen  = sizeof(TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_PDP_ADDR_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstPdpIpAddrInfoCnf = (TAF_PS_GET_PDP_IP_ADDR_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpIpAddrInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstPdpIpAddrInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPdpIpAddrInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        if ( VOS_TRUE == aucCidProcList[ucIndex] )
        {
            PS_MEM_SET(&(pstPdpIpAddrInfoCnf->astPdpAddrQueryInfo[ulCidNum]),
                       0x00, sizeof(TAF_PDP_ADDR_QUERY_INFO_STRU));

            /* ��ȡCID��Ӧ��IP��ַ��Ϣ */
            Aps_QueRealIpAddr(ucIndex,
                              &(pstPdpIpAddrInfoCnf->astPdpAddrQueryInfo[ulCidNum]),
                              &ulErrCode);

            if ( TAF_PARA_OK == ulErrCode )
            {
                ulCidNum++;
            }
        }
    }

    /* ��д�¼�����ͷ */
    pstPdpIpAddrInfoCnf->stCtrl     = pstPdpIpAddrInfoReq->stCtrl;
    pstPdpIpAddrInfoCnf->ulCidNum   = ulCidNum;
    pstPdpIpAddrInfoCnf->enCause    = TAF_PARA_OK;

    /* ���ش����� */
    ulResult = TAF_APS_SndGetPdpIpAddrInfoCnf(pstPdpIpAddrInfoCnf,
                                             ulPdpIpAddrInfoLen);

    /* �ͷ����ڴ��IP��ַ��Ϣ���ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstPdpIpAddrInfoCnf);

    return ulResult;
}


VOS_VOID MN_APS_RcvSetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU   *pstSetAnsModeInfoReq;

    /* ��ʼ�� */
    ulErrCode            = TAF_PARA_OK;
    pstSetAnsModeInfoReq = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)pMsgData;

    /* ���Ӧ��ģʽ�Ƿ�Ϸ� */
    if ( (TAF_PDP_ANSWER_MODE_MANUAL == pstSetAnsModeInfoReq->ulAnsMode)
      || (TAF_PDP_ANSWER_MODE_AUTO   == pstSetAnsModeInfoReq->ulAnsMode) )
    {
        /* ����Ӧ��ģʽ */
        Aps_SetPsAnsMode(pstSetAnsModeInfoReq->stCtrl.usClientId,
                         pstSetAnsModeInfoReq->stCtrl.ucOpId,
                         (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstSetAnsModeInfoReq->ulAnsMode,
                         &ulErrCode);
    }
    else
    {
        ulErrCode       = TAF_PARA_SET_ERROR;
    }

    /* ���ش����� */
    TAF_APS_SndSetAnsModeInfoCnf(&(pstSetAnsModeInfoReq->stCtrl),
                                           ulErrCode);

    return;
}


VOS_VOID MN_APS_RcvGetAnsModeInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulAnsMode;
    TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU   *pstGetAnsModeInfoReq;

    /* ��ʼ�� */
    ulResult             = VOS_OK;
    ulErrCode            = TAF_PARA_OK;
    pstGetAnsModeInfoReq = (TAF_PS_GET_ANSWER_MODE_INFO_REQ_STRU*)pMsgData;

    /* ��ȡӦ��ģʽ */
    ulAnsMode            = g_PsAnsMode.enAnsMode;

    /* ���ش����� */
    ulResult = TAF_APS_SndGetAnsModeInfoCnf(&(pstGetAnsModeInfoReq->stCtrl),
                                           ulErrCode,
                                           ulAnsMode);

    MN_INFO_LOG1("MN_APS_RcvGetAnsModeInfoReq: TAF_APS_SndGetAnsModeInfoCnf Result:", (VOS_INT)ulResult);

    return;
}
VOS_UINT32 MN_APS_RcvGetDynamicPrimPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                          ulResult;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstGetDynamicPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult                    = VOS_OK;
    ulErrCode                   = TAF_PARA_OK;
    ulCidNum                    = 0;
    pstGetDynamicPdpCtxInfoReq  = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* GUģδʵ�ָ�����, ֱ�ӷ���OK */

    /* ���ش����� */
    ulResult = TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&(pstGetDynamicPdpCtxInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}
VOS_UINT32 MN_APS_RcvGetDynamicSecPdpCtxInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                                          ulResult;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstGetDynamicPdpCtxInfoReq;

    /* ��ʼ�� */
    ulResult                    = VOS_OK;
    ulErrCode                   = TAF_PARA_OK;
    ulCidNum                    = 0;
    pstGetDynamicPdpCtxInfoReq  = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pMsgData;

    /* GUģδʵ�ָ�����, ֱ�ӷ���OK */

    /* ���ش����� */
    ulResult = TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&(pstGetDynamicPdpCtxInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}
VOS_UINT32 MN_APS_RcvGetDynamicTftInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulCidNum;
    TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU   *pstGetDynamicTftInfoReq;

    /* ��ʼ�� */
    ulResult                = VOS_OK;
    ulErrCode               = TAF_PARA_OK;
    ulCidNum                = 0;
    pstGetDynamicTftInfoReq = (TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU*)pMsgData;

    /* GUģδʵ�ָ�����, ֱ�ӷ���OK */

    /* ���ش����� */
    ulResult = TAF_APS_SndGetDynamicTftInfoCnf(&(pstGetDynamicTftInfoReq->stCtrl),
                                                     ulErrCode,
                                                     ulCidNum);

    return ulResult;
}
VOS_UINT32 MN_APS_RcvSetPdpAuthInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU  *pstSetAuthInfoReq;

    ulResult          = VOS_OK;
    ulErrCode         = TAF_PARA_OK;
    pstSetAuthInfoReq = (TAF_PS_SET_PDP_AUTH_INFO_REQ_STRU*)pMsgData;

    /* ����PDP��Ȩ���� */
    Aps_DefPsPdpAuth(pstSetAuthInfoReq->stCtrl.usClientId,
                     pstSetAuthInfoReq->stCtrl.ucOpId,
                     &(pstSetAuthInfoReq->stPdpAuthInfo),
                     &ulErrCode);

    /* ���ش����� */
    ulResult = TAF_APS_SndSetPdpAuthInfoCnf(&(pstSetAuthInfoReq->stCtrl),
                                           ulErrCode);

    return ulResult;
}


VOS_UINT32 MN_APS_RcvGetPdpAuthInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulPdpAuthInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU  *pstGetPdpAuthInfoReq;
    TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU  *pstGetPdpAuthInfoCnf;

    /* ��ʼ�� */
    ulResult                = VOS_OK;
    ulErrCode               = TAF_PARA_OK;
    ulPdpAuthInfoLen        = 0;
    ulCidNum                = 0;
    pstGetPdpAuthInfoReq    = (TAF_PS_GET_PDP_AUTH_INFO_REQ_STRU*)pMsgData;
    pstGetPdpAuthInfoCnf    = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpAuthInfoLen        = sizeof(TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_AUTH_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetPdpAuthInfoCnf    = (TAF_PS_GET_PDP_AUTH_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpAuthInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpAuthInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpAuthInfoCnf->astPdpAuthQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_AUTH_QUERY_INFO_STRU));

        /* ��ȡCID��ӦPDP��Ȩ��Ϣ */
        Aps_QueAuth(ucIndex,
                    &(pstGetPdpAuthInfoCnf->astPdpAuthQueryInfo[ulCidNum]),
                    &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetPdpAuthInfoCnf->stCtrl    = pstGetPdpAuthInfoReq->stCtrl;
    pstGetPdpAuthInfoCnf->ulCidNum  = ulCidNum;
    pstGetPdpAuthInfoCnf->enCause   = TAF_PARA_OK;

    /* ���ش����� */
    ulResult = TAF_APS_SndGetPdpAuthInfoCnf(pstGetPdpAuthInfoCnf,
                                           ulPdpAuthInfoLen);

    /* �ͷ��������ڴ��PDP��Ȩ�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpAuthInfoCnf);

    return ulResult;
}
VOS_UINT32 MN_APS_RcvSetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_PDP_DNS_INFO_REQ_STRU   *pstSetDnsInfoReq;

    /* ��ʼ�� */
    ulResult          = VOS_OK;
    ulErrCode         = TAF_PARA_OK;
    pstSetDnsInfoReq  = (TAF_PS_SET_PDP_DNS_INFO_REQ_STRU*)pMsgData;

    /* ����PDP DNS��Ϣ */
    Aps_DefPsDns(pstSetDnsInfoReq->stCtrl.usClientId,
                 pstSetDnsInfoReq->stCtrl.ucOpId,
                 &(pstSetDnsInfoReq->stPdpDnsInfo),
                 &ulErrCode);

    ulResult = TAF_APS_SndSetPdpDnsInfoCnf(&(pstSetDnsInfoReq->stCtrl),
                                          ulErrCode);

    return ulResult;
}


VOS_UINT32 MN_APS_RcvGetPdpDnsInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulPdpDnsInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_PDP_DNS_INFO_REQ_STRU   *pstGetPdpDnsInfoReq;
    TAF_PS_GET_PDP_DNS_INFO_CNF_STRU   *pstGetPdpDnsInfoCnf;

    /* ��ʼ�� */
    ulResult            = VOS_OK;
    ulErrCode           = TAF_PARA_OK;
    ulPdpDnsInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpDnsInfoReq = (TAF_PS_GET_PDP_DNS_INFO_REQ_STRU*)pMsgData;
    pstGetPdpDnsInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpDnsInfoLen     = sizeof(TAF_PS_GET_PDP_DNS_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_AUTH_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetPdpDnsInfoCnf = (TAF_PS_GET_PDP_DNS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulPdpDnsInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpDnsInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetUmtsQosInfoReq: PS_MEM_ALLOC Error!");
        return VOS_ERR;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetPdpDnsInfoCnf->astPdpDnsQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_DNS_QUERY_INFO_STRU));

        /* ��ȡCID��Ӧ��PDP DNS��Ϣ */
        Aps_QueDns(ucIndex,
                   &(pstGetPdpDnsInfoCnf->astPdpDnsQueryInfo[ulCidNum]),
                   &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetPdpDnsInfoCnf->stCtrl     = pstGetPdpDnsInfoReq->stCtrl;
    pstGetPdpDnsInfoCnf->ulCidNum   = ulCidNum;
    pstGetPdpDnsInfoCnf->enCause    = TAF_PARA_OK;

    /* ���ش����� */
    ulResult = TAF_APS_SndGetPdpDnsInfoCnf(pstGetPdpDnsInfoCnf,
                                          ulPdpDnsInfoLen);

    /* �ͷ��������ڴ��PDP DNS�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpDnsInfoCnf);

    return ulResult;
}
/* Modified by wx270776 for OM�ں�, 2015-6-28, begin */

VOS_UINT32 MN_APS_RcvTrigGprsDataReq(
    VOS_VOID                           *pMsgData
)
{
    /* Deleted by wx270776 for OM�ں�, 2015-7-29, begin */

    /* Deleted by wx270776 for OM�ں�, 2015-7-29, end */

    return VOS_OK;
}
/* Modified by wx270776 for OM�ں�, 2015-6-28, end */

VOS_VOID MN_APS_RcvConfigNbnsFunctionReq(
    VOS_VOID                           *pMsgData
)
{
    TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU   *pstConfigNbnsFunReq;

    /* ��ʼ�� */
    pstConfigNbnsFunReq = (TAF_PS_CONFIG_NBNS_FUNCTION_REQ_STRU*)pMsgData;

    /* ����WINS���� */
    Aps_UpdateWinsConfig((VOS_UINT8)pstConfigNbnsFunReq->ulEnabled);

    return;
}




VOS_VOID MN_APS_RcvSetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                          ulErrCode;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU  *pstAuthDataReq;

    /* ��ʼ�� */
    ulErrCode       = TAF_PARA_OK;
    pstAuthDataReq  = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU*)pMsgData;

    /* ����AUTHDATA����(NDIS) */
    Aps_DefNdisAuthdata(pstAuthDataReq->stCtrl.usClientId,
                        pstAuthDataReq->stCtrl.ucOpId,
                        &(pstAuthDataReq->stAuthDataInfo),
                        &ulErrCode);

    /* ���ش����� */
    if (VOS_OK != TAF_APS_SndSetAuthDataInfoCnf(&(pstAuthDataReq->stCtrl),
                                            ulErrCode))
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: TAF_APS_SndGetAuthDataInfoCnf Error!");
    }

    return;
}
VOS_VOID MN_APS_RcvGetAuthDataInfoReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulAuthDataInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_GET_AUTHDATA_INFO_REQ_STRU  *pstGetAuthDataInfoReq;
    TAF_PS_GET_AUTHDATA_INFO_CNF_STRU  *pstGetAuthDataInfoCnf;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    ulAuthDataInfoLen       = 0;
    ulCidNum                = 0;
    pstGetAuthDataInfoReq   = (TAF_PS_GET_AUTHDATA_INFO_REQ_STRU*)pMsgData;
    pstGetAuthDataInfoCnf   = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulAuthDataInfoLen        = sizeof(TAF_PS_GET_AUTHDATA_INFO_CNF_STRU)
                                + ((TAF_MAX_CID + 1) * sizeof(TAF_AUTHDATA_QUERY_INFO_STRU));

    /* �����ڴ� */
    pstGetAuthDataInfoCnf    = (TAF_PS_GET_AUTHDATA_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                    WUEPS_PID_TAF,
                                    ulAuthDataInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetAuthDataInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: PS_MEM_ALLOC Error!");
        return;
    }

    /* ��д�¼����� */
    for ( ucIndex = 0; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetAuthDataInfoCnf->astAuthDataQueryInfo[ulCidNum]),
                   0x00, sizeof(TAF_AUTHDATA_QUERY_INFO_STRU));

        /* ��ȡUTHDATA����(NDIS) */
        Aps_QueAuthdata(ucIndex,
                        &(pstGetAuthDataInfoCnf->astAuthDataQueryInfo[ulCidNum]),
                        &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetAuthDataInfoCnf->stCtrl       = pstGetAuthDataInfoReq->stCtrl;
    pstGetAuthDataInfoCnf->ulCidNum     = ulCidNum;
    pstGetAuthDataInfoCnf->enCause      = TAF_PARA_OK;

    /* ���ش����� */
    if (VOS_OK != TAF_APS_SndGetAuthDataInfoCnf(pstGetAuthDataInfoCnf,
                                            ulAuthDataInfoLen))
    {
        MN_ERR_LOG("MN_APS_RcvGetAuthDataInfoReq: TAF_APS_SndGetAuthDataInfoCnf Error!");
    }

    /* �ͷ��������ڴ��AUTHDATA�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetAuthDataInfoCnf);

    return;
}


VOS_UINT32 MN_APS_RcvGetGprsActiveTypeReq(
    VOS_VOID                           *pMsgData
)
{
    VOS_UINT32                              ulResult;
    VOS_UINT32                              ulErrCode;
    TAF_PDP_TYPE_ENUM_UINT8                 enPdpType;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU           stCidGprsActiveType;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU *pstGetGprsActiveTypeReq;

    /* ��ʼ�� */
    ulResult                  = VOS_OK;
    ulErrCode                 = TAF_PARA_OK;
    pstGetGprsActiveTypeReq   = (TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU*)pMsgData;

    /* ��ȡGPRS�������� */
    PS_MEM_SET(&stCidGprsActiveType, 0x00, sizeof(TAF_CID_GPRS_ACTIVE_TYPE_STRU));
    stCidGprsActiveType.ucCid = pstGetGprsActiveTypeReq->stAtdPara.ucCid;

    enPdpType = Taf_GetCidType(pstGetGprsActiveTypeReq->stAtdPara.ucCid);

    if ( TAF_PDP_TYPE_BUTT != enPdpType )
    {
        /* L2p���� */
        if ( VOS_TRUE == pstGetGprsActiveTypeReq->stAtdPara.bitOpL2p )
        {
            if ( TAF_L2P_PPP == pstGetGprsActiveTypeReq->stAtdPara.enL2p )
            {
                /* L2PΪPPP */
                switch ( enPdpType )
                {
                    case TAF_PDP_IPV4:
                        /* IP����,����IP���TE��δ����PPP��MT�в�����PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                        break;

                #if (FEATURE_ON == FEATURE_IPV6)
                    case TAF_PDP_IPV6:
                    case TAF_PDP_IPV4V6:
                        /* IP����,����IP���TE��δ����PPP��MT�в�����PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                        break;
                #endif

                    default:
                        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                        break;
                }
            }
            else
            {
                /* L2PΪNULL */
                switch ( enPdpType )
                {
                    case TAF_PDP_IPV4:
                        /* IP����,����IP���TE��δ����PPP��MT�в�����PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE;
                        break;

                #if (FEATURE_ON == FEATURE_IPV6)
                    case TAF_PDP_IPV6:
                    case TAF_PDP_IPV4V6:
                        /* IP����,����IP���TE��δ����PPP��MT�в�����PPP */
                        stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_NOT_PPP_MT_NOT_PPP_TYPE;
                        break;
                #endif

                    case TAF_PDP_PPP:
                        /* PPP����,����PPP���TE��������PPP��MT�в�����PPP */
                        stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
                        break;

                    default:
                        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                        break;
                }
            }
        }
        else
        {
            /* L2p������ */
            switch (enPdpType)
            {
                case TAF_PDP_IPV4:
                    /* IP����,����IP���TE��������PPP��MT������PPP */
                    stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                    break;

            #if (FEATURE_ON == FEATURE_IPV6)
                case TAF_PDP_IPV6:
                case TAF_PDP_IPV4V6:
                    /* IP����,����IP���TE��������PPP��MT������PPP */
                    stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
                    break;
            #endif

                case TAF_PDP_PPP:
                    /* PPP����,����PPP���TE��������PPP��MT�в�����PPP */
                    stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
                    break;

                default:
                    ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
                    break;
            }
        }
    }
    else
    {
        ulErrCode = TAF_PARA_UNSPECIFIED_ERROR;
    }

    ulResult = TAF_APS_SndGetGprsActiveTypeCnf(&(pstGetGprsActiveTypeReq->stCtrl),
                                              ulErrCode,
                                              &stCidGprsActiveType);

    return ulResult;
}


VOS_UINT32 MN_APS_PppCovertConfigInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pstPppReqConfigInfo,
    TAF_PPP_REQ_CONFIG_INFO_STRU       *pstPppAtReqConfigInfo
)
{
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU  *pstPppActAuth;
    VOS_UINT16                          usPapLen;
    VOS_UINT8                          *pucPapBuf;
    VOS_UINT16                          usChallengeLen;
    VOS_UINT16                          usResponseLen;
    VOS_UINT8                          *pucChallengeBuf;
    VOS_UINT8                          *pucResponseBuf;
    VOS_UINT16                          usIpcpLen;
    VOS_UINT8                          *pucIpcpBuf;

    pstPppActAuth   = VOS_NULL_PTR;
    usPapLen        = 0;
    pucPapBuf       = VOS_NULL_PTR;
    usChallengeLen  = 0;
    usResponseLen   = 0;
    pucChallengeBuf = VOS_NULL_PTR;
    pucResponseBuf  = VOS_NULL_PTR;
    usIpcpLen       = 0;
    pucIpcpBuf      = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstPppReqConfigInfo)
    {
        MN_ERR_LOG("MN_APS_PppCovertConfigInfo: pstPppReqConfigInfo NULL_PTR!");
        return VOS_ERR;
    }

    /* Ŀ��ṹ��ʼ�� */
    PS_MEM_SET(pstPppReqConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));


    /* ��ȡAUTH���ݵ�ָ�� */
    pstPppActAuth = &(pstPppAtReqConfigInfo->stAuth);

    /* ��ȡ��֤���� */
    pstPppReqConfigInfo->stAuth.ucAuthType = pstPppActAuth->enAuthType;

    if (PPP_PAP_AUTH_TYPE == pstPppActAuth->enAuthType)
    {
        /* ��ȡpap req�����ĳ��� */
        usPapLen = pstPppActAuth->enAuthContent.stPapContent.usPapReqLen;

        pucPapBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usPapLen);
        if (VOS_NULL_PTR == pucPapBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");
            return VOS_ERR;
        }

        /* pap req���������鸴�Ƶ�ָ���� */
        PS_MEM_CPY(pucPapBuf, pstPppActAuth->enAuthContent.stPapContent.aucPapReqBuf,
                   usPapLen);

        pstPppReqConfigInfo->stAuth.AuthContent.PapContent.usPapReqLen = usPapLen;
        pstPppReqConfigInfo->stAuth.AuthContent.PapContent.pPapReq     = pucPapBuf;
    }
    else if (PPP_CHAP_AUTH_TYPE == pstPppActAuth->enAuthType)
    {
        /* ��ȡChapChallenge������ChapResponse�����ĳ��� */
        usChallengeLen = pstPppActAuth->enAuthContent.stChapContent.usChapChallengeLen;
        usResponseLen  = pstPppActAuth->enAuthContent.stChapContent.usChapResponseLen;

        pucChallengeBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usChallengeLen);
        if (VOS_NULL_PTR == pucChallengeBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");
            return VOS_ERR;
        }

        /* ChapChallenge���������鸴�Ƶ�ָ���� */
        PS_MEM_CPY(pucChallengeBuf, pstPppActAuth->enAuthContent.stChapContent.aucChapChallengeBuf,
                   usChallengeLen);

        pucResponseBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usResponseLen);
        if (VOS_NULL_PTR == pucResponseBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");

            /* �ͷ������ѷ�����ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeBuf);
            return VOS_ERR;
        }

        /* ChapResponse�����������и��Ƶ�ָ���� */
        PS_MEM_CPY(pucResponseBuf, pstPppActAuth->enAuthContent.stChapContent.aucChapResponseBuf,
                   usResponseLen);

        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.usChapChallengeLen = usChallengeLen;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.usChapResponseLen  = usResponseLen;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.pChapChallenge     = pucChallengeBuf;
        pstPppReqConfigInfo->stAuth.AuthContent.ChapContent.pChapResponse      = pucResponseBuf;

    }
    else
    {
    }

    /*  ��ȡIPCP��������  */
    usIpcpLen = pstPppAtReqConfigInfo->stIPCP.usIpcpLen;
    if (usIpcpLen > 0)
    {
        pucIpcpBuf = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_TAF, usIpcpLen);
        if (VOS_NULL_PTR == pucIpcpBuf)
        {
            MN_ERR_LOG("MN_APS_PppCovertConfigInfo:  ERROR : PS_MEM_ALLOC Error!");

            /* �ͷ������ѷ�����ڴ� */
            if ( VOS_NULL_PTR != pucPapBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucPapBuf);
            }
            if ( VOS_NULL_PTR != pucChallengeBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucChallengeBuf);
            }
            if ( VOS_NULL_PTR != pucResponseBuf )
            {
                PS_MEM_FREE(WUEPS_PID_TAF, pucResponseBuf);
            }
            return VOS_ERR;
        }

        /* �����������ݸ��Ƶ�ָ��ṹ�� */
        PS_MEM_CPY(pucIpcpBuf, pstPppAtReqConfigInfo->stIPCP.aucIpcp,
                   usIpcpLen);

        pstPppReqConfigInfo->stIPCP.usIpcpLen = usIpcpLen;
        pstPppReqConfigInfo->stIPCP.pIpcp     = pucIpcpBuf;
    }

    return VOS_OK;
}


TAF_PS_CAUSE_ENUM_UINT32 MN_APS_RcvPppDialOrigReq(
    VOS_UINT8                           ucPdpId,
    TAF_PPP_DIAL_PARA_STRU             *pstPppDialParaInfo
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PDP_ADDR_STRU                   stPdpAddr;
    TAF_PDP_APN_STRU                    stApn;
    TAF_PS_CAUSE_ENUM_UINT32            enRet;
    VOS_UINT8                           ucCid;

    enRet = TAF_PS_CAUSE_SUCCESS;
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));
    PS_MEM_SET(&stPdpAddr, 0x00, sizeof(TAF_PDP_ADDR_STRU));
    PS_MEM_SET(&stApn, 0x00, sizeof(TAF_PDP_APN_STRU));

    if (TAF_PDP_PPP != TAF_APS_GetTafCidInfoPdpType(ucCid))
    {
        /* ת����Ȩ���� */
        if (VOS_OK == MN_APS_PppCovertConfigInfo(&stPppConfigInfo,
                                                 &pstPppDialParaInfo->stPppReqConfigInfo))
        {
            if (TAF_PS_PARA_VALID == Taf_PsCallForDialParaCheck(&stPppConfigInfo))
            {
                stPdpAddr.enPdpType = TAF_PDP_IPV4;
                if (TAF_PDP_IPV4 == TAF_APS_GetTafCidInfoPdpType(ucCid))
                {
                    PS_MEM_CPY(stPdpAddr.aucIpv4Addr,
                               TAF_APS_GetTafCidInfoPdpIpv4Addr(ucCid),
                               TAF_IPV4_ADDR_LEN);
                }

                stApn.ucLength = TAF_APS_GetTafCidInfoApnLen(ucCid);;
                PS_MEM_CPY(stApn.aucValue,
                           TAF_APS_GetTafCidInfoApnData(ucCid),
                           TAF_MAX_APN_LEN);

                enRet = TAF_APS_PsCallForDial(ucPdpId,
                                              &stPdpAddr,
                                              &stApn,
                                              &stPppConfigInfo);
            }
            else
            {
                MN_WARN_LOG("MN_APS_RcvPppDialOrigReq: Check PPP config info failed!");
                enRet = TAF_PS_CAUSE_INVALID_PARAMETER;
            }
        }
        else
        {
            enRet = TAF_PS_CAUSE_UNKNOWN;
        }

        /* �ͷ����ɵļ�Ȩ��Ϣ */
        MN_APS_CtrlFreePCOContext(&stPppConfigInfo);
    }
    else
    {
        enRet = TAF_APS_PsCallOrig(ucPdpId);
    }

    return enRet;
}


TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallOrig(VOS_UINT8 ucPdpId)
{
    VOS_UINT8                           ucCid;

    /*��ʼ��*/
    ucCid = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /*CID������,�򰴶���Ĳ������м���*/
    return Aps_PsCallOrigNormCid(ucCid, ucPdpId);
}

/*****************************************************************************
 Prototype      : Aps_ActJudgePriOrSecAct()
 Description    : APP�������𼤻�ʱ���ô˺������ݸ�CID��PDPȫ�����ݱ��еĶ���,
                  ��������������Ƕ��μ���.
                  ���з�����μ���,������������Ѿ��õ���ADDR��APN��������������
                  ���벻�ܴ���INACTIVE״̬.�������״̬�ļ�鲻�ڴ˺����н����ˣ�
                  ���ڶ��μ���ĺ����м�顣

                  �����������
                  1.��ǰû�м����κ�PDP����AT����ļ���Ҫ�󼤻�ȫ
                  ��CID����ʱ,�������PDPû�����⣬���Լ���,������Ķ���PDP����
                  PDP��ʱ��û�м�������μ���Ļ����������϶��ܾ������Զ�����
                  ����µĶ���Ķ���PDP���;ܾ�����;��Ϊ��ʱ�û�Ҳ֪��ĳЩ����
                  ����������û�м�����ܼ�����μ���.
                  2.��ǰ�����˲���PDP��ATҪ����ĳ������PDP�ļ���,�ͼ���PDP
                  ����PDP�Ƿ��Ѿ�����,�����ˣ�������������μ���,��ʱ�������ܹ�
                  ��ȷ������μ���;���ö��μ������PDPû�м���,��ö���Ķ���PDP
                  ���ܷ�����μ���;
 Input          :
 Output         : pucResult,  #define APS_PRI_ACT         1 - ������,
                              #define APS_SEC_ACT         2 - ���μ���,
                  pucPriPdpId,����Ƕ��μ���,��ָ��ָ���PdpId����ֵΪ�������
                  PdpId,[0,6][8,14];�����������,��ָ��ָ���PdpId����ֵΪ0xFF
                              #define   APS_INVALID_PDPID   0xFF
 Return Value   :
 Data Accessed  : PDPȫ�����ݱ�g_TafCidTab[TAF_MAX_CID + 1];
 Data Updated   :
 Calls          :
 Called By      : TAF_APS_PsCallOrig()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_ActJudgePriOrSecAct (
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucResult
)
{
    /*�ڴ˺����ⲿ����CID�Ƿ����*/
    if ( 0 == ucCid)
    {
        /*����������*/
        *pucResult                      = APS_PRI_ACT;
        return;
    }

    if( APS_PDP_TABLE_PARA_INVALID      == g_TafCidTab[ucCid].ucPriCidFlag )
    {
        /*����������*/
        *pucResult                      = APS_PRI_ACT;
    }
    else
    {
        /*���μ���*/
        *pucResult                      = APS_SEC_ACT;
    }
    return ;
}


VOS_UINT32 TAF_APS_FillPapParam(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    /* ���ü�Ȩ���� */
    pstAuthParam->AuthType = TAF_PCO_AUTH_PAP;

    pstAuthParam->AuthContent.stPap.aucUserName[0] = (VOS_UINT8)usUserNameLen;

    PS_MEM_CPY(&pstAuthParam->AuthContent.stPap.aucUserName[1],
               pucUserName,
               usUserNameLen + 1);

    pstAuthParam->AuthContent.stPap.aucPassword[0] = (VOS_UINT8)usPassWordLen;

    PS_MEM_CPY(&pstAuthParam->AuthContent.stPap.aucPassword[1],
               pucPassWord,
               usPassWordLen + 1);

    return VOS_OK;
}
VOS_UINT32 TAF_APS_FillChapParam(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    VOS_UINT8                          *pucUserName,
    VOS_UINT16                          usUserNameLen,
    VOS_UINT8                          *pucPassWord,
    VOS_UINT16                          usPassWordLen
)
{
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stPsDilaParam;
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;

    PS_MEM_SET(&stPppConfigInfo, 0, sizeof(stPppConfigInfo));
    PS_MEM_SET(&stPsDilaParam, 0, sizeof(stPsDilaParam));

    /* ���ݼ�Ȩ�������ɼ�Ȩ��Ϣ */
    stPppConfigInfo.stAuth.ucAuthType = PPP_CHAP_AUTH_TYPE;

    if (VOS_OK != MN_APS_CtrlMakePCOChapAuthInfo(&stPppConfigInfo,
                                                 pucUserName,
                                                 usUserNameLen,
                                                 pucPassWord,
                                                 usPassWordLen))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillChapParam: Generate challenge param failed.\n");
        return VOS_ERR;
    }

    /* ��IPCP�������в��REQ��AUTH��Ϣ����, ���stPsDilaParam�� */
    if (TAF_APS_FAIL == Aps_GetAuthInfo(&stPppConfigInfo, &stPsDilaParam))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillChapParam: Get auth info failed.\n");
        return VOS_ERR;
    }

    /* �������˼�Ȩ��Ϣ, ��ʹ������ļ�Ȩ��Ϣ*/
    Aps_CopyAuthToActReqPara(&stPsDilaParam.AuthPara,
                             pstAuthParam);

    /* �ͷ����ɵļ�Ȩ��Ϣ */
    MN_APS_CtrlFreePCOContext(&stPppConfigInfo);

    return VOS_OK;
}


VOS_UINT32 TAF_APS_FillAuthParamFromProfile(
    TAF_PDP_PCO_AUTH_STRU              *pstAuthParam,
    TAF_NDIS_AUTHDATA_TABLE_STRU       *pstAuthProfileInfo
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usUserNameLen;
    VOS_UINT16                          usPassWordLen;

    /* �����û��������볤�� */
    usUserNameLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pstAuthProfileInfo->stAuthData.aucUsername);
    usPassWordLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)pstAuthProfileInfo->stAuthData.aucPassword);

    /* ����û���������ĳ����Ƿ�Ϸ� */
    if ( (usUserNameLen > TAF_MAX_USERNAME_LEN)
      || (usPassWordLen > TAF_MAX_PASSCODE_LEN) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_FillAuthParamFromProfile: Username or password is too long.\n");
        return VOS_ERR;
    }

    if ((VOS_FALSE != pstAuthProfileInfo->ucUsed) && (0 != usUserNameLen))
    {
        switch (pstAuthProfileInfo->stAuthData.enAuthType)
        {
            case TAF_PDP_AUTH_TYPE_PAP:
                ulRslt = TAF_APS_FillPapParam(pstAuthParam,
                                              pstAuthProfileInfo->stAuthData.aucUsername,
                                              usUserNameLen,
                                              pstAuthProfileInfo->stAuthData.aucPassword,
                                              usPassWordLen);
                break;

            case TAF_PDP_AUTH_TYPE_CHAP:
            case TAF_PDP_AUTH_TYPE_MS_CHAP_V2:
                ulRslt = TAF_APS_FillChapParam(pstAuthParam,
                                               pstAuthProfileInfo->stAuthData.aucUsername,
                                               usUserNameLen,
                                               pstAuthProfileInfo->stAuthData.aucPassword,
                                               usPassWordLen);
                break;

            default:
                ulRslt = VOS_ERR;
                break;
        }
    }
    else
    {
        ulRslt = VOS_ERR;
    }

    return ulRslt;
}


VOS_UINT32  Aps_PackApsActReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;

    TAF_NDIS_AUTHDATA_TABLE_STRU       *pstAuthProfileInfo;

    /*��ڲ������;*/
    if ( VOS_NULL == pApsActReq )
    {
        APS_WARN_LOG("VOS_NULL == pApsActReq ");
        return  TAF_APS_FAIL;
    }

    pstAuthProfileInfo              = &g_ApsNdisAuthdataTab[ucCid];

    pTafPdp                         = &g_TafCidTab[ucCid];

    pApsActReq->OP_APN              = VOS_FALSE;
    pApsActReq->OP_AUTH             = VOS_FALSE;
    pApsActReq->OP_DNS              = VOS_FALSE;
    pApsActReq->OP_NBNS             = VOS_FALSE;
    pApsActReq->OP_Sapi             = VOS_FALSE;
    pApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pApsActReq->OP_SPARE            = VOS_FALSE;
    pApsActReq->ucPdpId             = ucPdpId;

    /*V200ר��*/
    pApsActReq->OP_Sapi             = VOS_TRUE;
    pApsActReq->ucSapi              = APS_SAPI_INIT;

    if ( 0 == ucCid )
    {
        /*��̬IPV4����*/
        Aps_CopyAddrToActReqPara(   pTafPdp->CidTab.stPdpAddr.aucIpv4Addr,
                                    pApsActReq  );
    }
    else
    {
        /*����ucPdpType,aucIpAddr*/
        switch(pTafPdp->CidTab.stPdpAddr.enPdpType)
        {
            /*PPP����*/
            case TAF_PDP_PPP:
                pApsActReq->ucPdpType   = APS_ADDR_PPP;
                break;

            case TAF_PDP_IPV4:
                Aps_CopyAddrToActReqPara( pTafPdp->CidTab.stPdpAddr.aucIpv4Addr,
                                          pApsActReq  );
                break;

#if (FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
                pApsActReq->ucPdpType   = MN_APS_ADDR_IPV6;
                break;

            case TAF_PDP_IPV4V6:
                pApsActReq->ucPdpType   = MN_APS_ADDR_IPV4V6;
                break;
#endif

            default:
                APS_WARN_LOG("TAF_APS_GetPsReqPdp:PdpType is error.\r");
                return TAF_APS_FAIL;
        }
    }


    /*AUTH*/
    if ( 0 != ucCid )
    {
        if ( APS_ADDR_PPP != pApsActReq->ucPdpType )
        {
            if (VOS_OK == TAF_APS_FillAuthParamFromProfile(&pApsActReq->PdpAuth,
                                                           pstAuthProfileInfo))
            {
                pApsActReq->OP_AUTH = VOS_TRUE;
            }
            else
            {
                /*����Ȩ*/
                pApsActReq->PdpAuth.AuthType = TAF_PCO_NOT_AUTH;
                PS_MEM_SET(&pApsActReq->PdpAuth.AuthContent, 0, sizeof(pApsActReq->PdpAuth.AuthContent));
            }
        }
    }

    /*aucApn*/
    if ( 0 != ucCid )
    {
        pApsActReq->OP_APN = 1;
        Taf_LenStr2Apn(&(pTafPdp->CidTab.stApn), pApsActReq->aucApn);
    }

    /*����Qos*/
    Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);

    /*����XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    /*����DNS*/
    Aps_FillDns(pTafPdp, pApsActReq);

    /*�����ϣ�ֱ�ӷ��سɹ�*/
    return TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_CopyAuthToActReqPara
 Description    :
 Input          : pAuthTab
 Output         : pApsAuth
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_CopyAuthToActReqPara(
    CONST TAF_PDP_PCO_AUTH_STRU        *pAuthTab,
    TAF_PDP_PCO_AUTH_STRU              *pActReqParaAuth
)
{
    /*�����û���������*/
    PS_MEM_CPY(pActReqParaAuth, pAuthTab, sizeof(TAF_PDP_PCO_AUTH_STRU));
    return;
}
VOS_VOID  Aps_CopyAddrToActReqPara(
    CONST VOS_UINT8                    *pucIpAddr,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    /*��̬IP������IP��ַ,Ŀǰ��̬IP��ַֻ֧��IPV4����࿽��4���ֽ�*/
    PS_MEM_CPY(pApsActReq->aucIpAddr, pucIpAddr, TAF_IPV4_ADDR_LEN);

    if (  (0 == pApsActReq->aucIpAddr[0])
       && (0 == pApsActReq->aucIpAddr[1])
       && (0 == pApsActReq->aucIpAddr[2])
       && (0 == pApsActReq->aucIpAddr[3]) )
    {
        /*��̬IP*/
        pApsActReq->ucPdpType   = APS_ADDR_DYNAMIC_IPV4;
    }
    else
    {
        /*��̬IP*/
        pApsActReq->ucPdpType   = APS_ADDR_STATIC_IPV4;
    }

    return;
}
TAF_PS_CAUSE_ENUM_UINT32 Aps_PsCallOrigNormCid(
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId
)
{
    VOS_UINT32                          ulReturn;
    VOS_UINT8                           ucPriSecAct;
    APS_PDP_ACT_REQ_ST                  stApsActReq;
    APS_PDP_SEC_ACT_REQ_ST              stApsSecActReq;                           /*�ñ����ĳ�ʼ���ں���
                                                                                 Aps_PackApsSecActReqPara�����                                                                             */
    ulReturn                            = TAF_SUCCESS;
    ucPriSecAct                         = APS_PRI_ACT;

    PS_MEM_SET(&stApsActReq, 0, sizeof(APS_PDP_ACT_REQ_ST));
    PS_MEM_SET(&stApsSecActReq, 0, sizeof(APS_PDP_SEC_ACT_REQ_ST));

    /*�ж�������Ƕ��μ���*/
    Aps_ActJudgePriOrSecAct( ucCid, &ucPriSecAct);

    /*������*/
    if ( APS_PRI_ACT == ucPriSecAct )
    {
        /*��������������*/
        ulReturn = Aps_PackApsActReqPara( ucCid, ucPdpId, &stApsActReq );
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("JudgePriOrSecAct err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }

        /*����*/
        ulReturn = Aps_PdpActReq( &stApsActReq );
        if ( TAF_APS_SUCC != ulReturn )
        {
            APS_WARN_LOG("Aps_PdpActReq err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }
    }
    else  /*���μ���*/
    {
        /*������μ����������*/
        ulReturn = Aps_PackApsSecActReqPara( ucCid, ucPdpId, &stApsSecActReq );
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("Aps_PackApsSecActReqPara err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }

        /*���μ���*/
        ulReturn = Aps_PdpSecActReq( &stApsSecActReq );
        if ( TAF_APS_SUCC != ulReturn )
        {
            APS_WARN_LOG("Aps_PdpSecActReq err ");
            return TAF_PS_CAUSE_UNKNOWN;
        }
    }

    return TAF_PS_CAUSE_SUCCESS;
}

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-14, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-14, end */

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_PsCallForDial(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_ADDR_STRU                  *pstPdpAddr,
    TAF_PDP_APN_STRU                   *pstApn,
    PPP_REQ_CONFIG_INFO_STRU           *pstPppConfigInfo
)
{
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stDialParamExt;
    APS_PDP_ACT_REQ_ST                  stPdpActReq;
    VOS_UINT32                          ulReturn;

    PS_MEM_SET(&stDialParamExt, 0x00, sizeof(TAF_PSCALL_FOR_DIAL_EXT_STRU));
    PS_MEM_SET(&stPdpActReq, 0x00, sizeof(APS_PDP_ACT_REQ_ST));

    /* ������в���: CID, PDP���ͺ�APN��Ϣ */
    stDialParamExt.ucCid   = TAF_APS_GetPdpEntCurrCid(ucPdpId);;
    stDialParamExt.PdpType = pstPdpAddr->enPdpType;

    PS_MEM_CPY(&(stDialParamExt.stApn), pstApn, sizeof(TAF_PDP_APN_STRU));
    PS_MEM_CPY(stDialParamExt.aucPdpAddr, pstPdpAddr->aucIpv4Addr, TAF_IPV4_ADDR_LEN);

    /* ��IPCP�������в��REQ��IPCP��Ϣ����, ���stDialParamExt�� */
    Aps_GetIpcpInfo(pstPppConfigInfo, &stDialParamExt);

    /* ��IPCP�������в��REQ��AUTH��Ϣ����, ���stPdpActReq�� */
    if (TAF_APS_FAIL == Aps_GetAuthInfo(pstPppConfigInfo, &stDialParamExt))
    {
        return TAF_PS_CAUSE_INVALID_PARAMETER;
    }

    /* ���캯��Aps_PdpActReq()��Ҫ���������APS_PDP_ACT_REQ_ST */
    ulReturn = Aps_PackDialActReqPara(ucPdpId, &stDialParamExt, &stPdpActReq);
    if (ulReturn == TAF_APS_FAIL)
    {
        return TAF_PS_CAUSE_UNKNOWN;
    }

    /* ���𼤻� */
    ulReturn = Aps_PdpActReq(&stPdpActReq);
    if (TAF_APS_FAIL == ulReturn)
    {
        return TAF_PS_CAUSE_UNKNOWN;
    }

    return TAF_PS_CAUSE_SUCCESS;
}
VOS_VOID Aps_GetIpcpInfo(
    PPP_REQ_CONFIG_INFO_STRU           *pPsDialPara,
    TAF_PSCALL_FOR_DIAL_EXT_STRU       *pApsDialReqPara
)
{
    APS_PCO_IPCP_PPP_ST                 IpcpPPP;
    APS_PCO_PPP_ST                      OnePppIpcp;
    APS_PPP_ID_ST                       OnePppId;

    APS_PDP_DNS_ST                      ApsDns;
    APS_PDP_NBNS_ST                     ApsNbns;
#if 0
    VOS_UINT8                           aucIpAddr[TAF_IPV4_ADDR_LEN];
#endif

    /*����DNS��ʶ*/
    pApsDialReqPara->OP_Dns                 = VOS_FALSE;
    pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_FALSE;
    pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_FALSE;

    ApsDns.OP_PriDns                        = VOS_FALSE;
    ApsDns.OP_SecDns                        = VOS_FALSE;
    ApsDns.OP_Spare                         = VOS_FALSE;

    /*����NBNS��ʶ*/
    pApsDialReqPara->OP_Nbns                = VOS_FALSE;
    pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_FALSE;
    pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_FALSE;

    ApsNbns.OP_PriNbns                      = VOS_FALSE;
    ApsNbns.OP_SecNbns                      = VOS_FALSE;
    ApsNbns.OP_Spare                        = VOS_FALSE;

#if 0
    aucIpAddr[0]                            = 0;
    aucIpAddr[1]                            = 0;
    aucIpAddr[2]                            = 0;
    aucIpAddr[3]                            = 0;
#endif

    /*��IPCP�����������²���*/
    IpcpPPP.usLen                           = pPsDialPara->stIPCP.usIpcpLen;
    IpcpPPP.pProtIdCont                     = pPsDialPara->stIPCP.pIpcp;

    if (0 == IpcpPPP.usLen)
    {
        return;
    }

    if ( TAF_APS_SUCC == Aps_CheckOutPcoOneIpcp(&IpcpPPP,
                                            APS_PPP_CODE_REQ,
                                            &OnePppIpcp))
    {
#if 0
        /*�ҳ�REQ�����е�IPADDR*/
        if ( TAF_APS_SUCC ==  Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_IP_ADDR_ID,
                                        &OnePppId))
        {   /*�ɹ������IP ADDR��Ϣ*/
            Aps_PPPAddr2ApsAddr(        (APS_PCO_PPP_ST*)&OnePppId,
                                        aucIpAddr);

            PS_MEM_CPY(pApsDialReqPara->aucPdpAddr, aucIpAddr, TAF_IPV4_ADDR_LEN);
        }
#endif

        /*�ҳ�REQ�����е���DNS,����������*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_PRI_DNS_ID,
                                        &OnePppId))
        {
            Aps_PPPDns2ApsDns(          (APS_PCO_PPP_ST*)&OnePppId,
                                        &ApsDns);
        }

        /*��REQ��Ϣ�в����DNS��Ϣ,����������*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_SEC_DNS_ID,
                                        &OnePppId))
        {
            Aps_PPPDns2ApsDns(          (APS_PCO_PPP_ST*)&OnePppId,
                                        &ApsDns);
        }

        /*�ҳ�REQ�����е���NBNS,����������*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_PRI_NBNS_ID,
                                        &OnePppId))
        {
            Aps_PPPNbns2ApsNbns(          (APS_PCO_PPP_ST*)&OnePppId,
                                          &ApsNbns);
        }

        /*��REQ��Ϣ�в����NBNS��Ϣ,����������*/
        if ( TAF_APS_SUCC == Aps_CheckOutOneIpcpOneId(
                                        &OnePppIpcp,
                                        APS_PPP_SEC_NBNS_ID,
                                        &OnePppId))
        {
            Aps_PPPNbns2ApsNbns(          (APS_PCO_PPP_ST*)&OnePppId,
                                          &ApsNbns);
        }
    }


    /*��DNS*/
    if (ApsDns.OP_PriDns)
    {
        /*����DNS��ʶ*/
        pApsDialReqPara->OP_Dns                 = VOS_TRUE;

        pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Dns.aucPrimDnsAddr,
                   ApsDns.aucPriDns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Dns.bitOpPrimDnsAddr   = VOS_FALSE;
    }

    /*��DNS*/
    if (ApsDns.OP_SecDns)
    {
        /*����DNS��ʶ*/
        pApsDialReqPara->OP_Dns                 = VOS_TRUE;

        pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Dns.aucSecDnsAddr,
                   ApsDns.aucSecDns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Dns.bitOpSecDnsAddr    = VOS_FALSE;
    }

    /*��NBNS*/
    if (ApsNbns.OP_PriNbns)
    {
        /*����NBNS��ʶ*/
        pApsDialReqPara->OP_Nbns                = VOS_TRUE;

        pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_TRUE;

        PS_MEM_CPY(pApsDialReqPara->Nbns.aucPrimNbnsAddr,
                   ApsNbns.aucPriNbns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Nbns.bitOpPrimNbnsAddr = VOS_FALSE;
    }

    /*��NBNS*/
    if (ApsNbns.OP_SecNbns)
    {
        /*����NBNS��ʶ*/
        pApsDialReqPara->OP_Nbns                = VOS_TRUE;

        pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_TRUE;
        PS_MEM_CPY(pApsDialReqPara->Nbns.aucSecNbnsAddr,
                   ApsNbns.aucSecNbns,
                   TAF_IPV4_ADDR_LEN);
    }
    else
    {
        pApsDialReqPara->Nbns.bitOpSecNbnsAddr  = VOS_FALSE;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_GetAuthInfo()
 Description    :
 Input          : pPsCallDialPara
 Output         : pPsCallDial
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_GetAuthInfo(            PPP_REQ_CONFIG_INFO_STRU   *pPsDialPara,
                                        TAF_PSCALL_FOR_DIAL_EXT_STRU *pApsDialReqPara)
{
    APS_PPP_ID_ST                       OnePppId;
    VOS_UINT8                           ucLoc = 0;
    TAF_PDP_PCO_AUTH_STRU               *pApsAuth;

    pApsAuth                            = &pApsDialReqPara->AuthPara;

    pApsDialReqPara->OP_Auth            = VOS_FALSE;
    pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_NOT_AUTH;
    PS_MEM_SET(&pApsDialReqPara->AuthPara.AuthContent, 0, sizeof(pApsDialReqPara->AuthPara.AuthContent));

    if (PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType)
    {
        pApsDialReqPara->OP_Auth            = VOS_TRUE;
        pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_AUTH_PAP;

        OnePppId.usLen                      = pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen;
        OnePppId.pProtIdCont                = pPsDialPara->stAuth.AuthContent.PapContent.pPapReq;

        /*��Ȩ�ĳ���Ϊ0,���˳�*/
        if (0 == OnePppId.usLen)
        {
            return  TAF_APS_SUCC;
        }

        ucLoc   += 4;                       /*����CODE1�ֽ�,Identifier1�ֽ�,����2�ֽ��е�2���ֽ�*/

        /*����UserName*/
        if (OnePppId.pProtIdCont[ucLoc] > TAF_MAX_USERNAME_LEN)
        {
            return  TAF_APS_FAIL;
        }
        else
        {
        /*lint -e961*/
            pApsAuth->AuthContent.stPap.aucUserName[0]        = OnePppId.pProtIdCont[ucLoc++];
        /*lint +e961*/

            /*��UserName*/
            if (0 != pApsAuth->AuthContent.stPap.aucUserName[0])
            {
                PS_MEM_CPY(                 &pApsAuth->AuthContent.stPap.aucUserName[1],
                                            &OnePppId.pProtIdCont[ucLoc],
                                            pApsAuth->AuthContent.stPap.aucUserName[0]);
            }

            ucLoc += pApsAuth->AuthContent.stPap.aucUserName[0];              /*����USERNAME*/
        }

        /*����PassWord*/
        if (OnePppId.pProtIdCont[ucLoc] > TAF_MAX_PASSCODE_LEN)
        {
            return  TAF_APS_FAIL;
        }
        else
        {
            /*lint -e961*/
            pApsAuth->AuthContent.stPap.aucPassword[0]        = OnePppId.pProtIdCont[ucLoc++];
            /*lint +e961*/
            PS_MEM_CPY(                     &pApsAuth->AuthContent.stPap.aucPassword[1],
                                            &OnePppId.pProtIdCont[ucLoc],
                                            pApsAuth->AuthContent.stPap.aucPassword[0]);
        }
    }
    else if(PPP_CHAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType)
    {
        /*Ŀǰ��ʵ���У���ȻҪ��challenge��response����*/
        if ( (0 == pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen)
             || (0 == pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen) )
        {
            return TAF_APS_FAIL;
        }

        pApsDialReqPara->OP_Auth            = VOS_TRUE;
        pApsDialReqPara->AuthPara.AuthType  = TAF_PCO_AUTH_CHAP;

        /*����challenge ����*/
        if ( TAF_PCO_CONTENT_MAX_LEN < pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen )
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0] = TAF_PCO_CONTENT_MAX_LEN;
        }
        else
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0]
                   = (VOS_UINT8)pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen;
        }

        PS_MEM_CPY( &pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[1],
                    pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge,
                    pApsDialReqPara->AuthPara.AuthContent.stChap.aucChallenge[0]);

        /*����response ����*/
        if ( TAF_PCO_CONTENT_MAX_LEN < pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen )
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0] = TAF_PCO_CONTENT_MAX_LEN;
        }
        else
        {
            pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0]
                   = (VOS_UINT8)pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen;
        }

        PS_MEM_CPY( &pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[1],
                    pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse,
                    pApsDialReqPara->AuthPara.AuthContent.stChap.aucResponse[0]);
    }
    else
    {
        /*����Ȩ*/
    }

    return  TAF_APS_SUCC;

}


VOS_UINT32  Aps_PackDialActReqPara(
    VOS_UINT8                           ucPdpId,
    TAF_PSCALL_FOR_DIAL_EXT_STRU       *pPsCallDial,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;

    pTafPdp                     = &g_TafCidTab[pPsCallDial->ucCid];

    /*SAPI*/
    pApsActReq->OP_Sapi         = VOS_TRUE;
    pApsActReq->ucSapi          = APS_SAPI_INIT;

    pApsActReq->ucPdpId         = ucPdpId;

    /*���������PDP����,��PDP���ͺ͵�ַ*/
    if (TAF_PDP_IPV4 == pPsCallDial->PdpType)
    {
        Aps_CopyAddrToActReqPara(pPsCallDial->aucPdpAddr,
                                 pApsActReq);
    }
#if (FEATURE_ON == FEATURE_IPV6)
    else if (TAF_PDP_IPV6 == pPsCallDial->PdpType)
    {
        /* IPV6���͵�PDP��������, ����д��̬IP��ַ */
        pApsActReq->ucPdpType   = MN_APS_ADDR_IPV6;
    }
    else if (TAF_PDP_IPV4V6 == pPsCallDial->PdpType)
    {
        /* IPV4V6���͵�PDP��������, ����д��̬IP��ַ */
        pApsActReq->ucPdpType   = MN_APS_ADDR_IPV4V6;
    }
#endif
    else
    {
        /*����������PPP����*/
        pApsActReq->ucPdpType   = APS_ADDR_PPP;
    }

    /*����aucApn*/
    pApsActReq->OP_APN          = VOS_TRUE;
    Taf_LenStr2Apn(&(pPsCallDial->stApn), pApsActReq->aucApn);

    /*����ucUserAuthOrNot,aucUserName,aucPassword*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Auth )
        {
            /*�������˼�Ȩ��Ϣ,��ʹ������ļ�Ȩ��Ϣ*/
            pApsActReq->OP_AUTH = VOS_TRUE;
            Aps_CopyAuthToActReqPara(&(pPsCallDial->AuthPara),
                                     &(pApsActReq->PdpAuth));
        }
        else
        {
            /*����Ȩ*/
            pApsActReq->OP_AUTH = VOS_FALSE;
        }
    }
    else
    {
        /*PPP��PDP����Ȩ*/
        pApsActReq->OP_AUTH     = VOS_FALSE;
    }

    /*����Qos*/
    Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);

    /*����XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    /*����PdpDns*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Dns)
        {
            /*���������DNS,��ʹ�������DNS*/
            pApsActReq->OP_DNS  = VOS_TRUE;
            pApsActReq->PdpDns  = pPsCallDial->Dns;
        }
        else
        {
            /*���û��������DNS,��ʹ�ñ��ж����DNS*/
            Aps_FillDns(pTafPdp, pApsActReq);
        }
    }
    else
    {
        /*PPP��PDP��DNS*/
        pApsActReq->OP_DNS      = VOS_FALSE;
    }

    /*����PdpNbns*/
    if (APS_ADDR_PPP != pApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pPsCallDial->OP_Nbns)
        {
            /*���������NBNS,��ʹ�������NBNS*/
            pApsActReq->OP_NBNS = VOS_TRUE;
            pApsActReq->PdpNbns = pPsCallDial->Nbns;
        }
        else
        {
            /*���û������NBNS,�Ͳ�ʹ��NBNS*/
            pApsActReq->OP_NBNS = VOS_FALSE;
        }
    }
    else
    {
        /*PPP��PDP��DNS*/
        pApsActReq->OP_NBNS     = VOS_FALSE;
    }

    /*�����ϣ�ֱ�ӷ��سɹ�*/
    return  TAF_APS_SUCC;
}
VOS_VOID  Taf_FillQos_Set_MaximSduSize(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{

    if (pTafPdp->QosTab.usMaxSduSize <= APS_APP_QOS_MAXSDUSIZE_1500OCTS)
    {
        pApsQos->ucMaximSduSize
            = (VOS_UINT8)(pTafPdp->QosTab.usMaxSduSize / APS_3GPP_QOS_MAXSDUSIZE_GRANUL_10);
    }
    else
    {
        if (APS_APP_QOS_MAXSDUSIZE_1502OCTS == pTafPdp->QosTab.usMaxSduSize)
        {
            pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1502OCTS;
        }
        else
        {
            if (APS_APP_QOS_MAXSDUSIZE_1510OCTS == pTafPdp->QosTab.usMaxSduSize)
            {
                pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1510OCTS;
            }
            else
            {
                if (APS_APP_QOS_MAXSDUSIZE_1520OCTS == pTafPdp->QosTab.usMaxSduSize)
                {
                    pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_1520OCTS;
                }
                else
                {
                    pApsQos->ucMaximSduSize = APS_3GPP_QOS_MAXSDUSIZE_SUB;
                }
            }
        }
    }

}


VOS_VOID  Taf_FillQos_Set_MaxBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*  Maximum bit rate for uplink, octet 8:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps


        Maximum bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 8.

                        For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 8
                        and use the following value:
        0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol
    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucMaxBitRateForUpExt = 0;
    #endif

    if (pTafPdp->QosTab.ulMaxBitUl <= 63)
    {
        pApsQos->ucMaxBitRateForUp   = (VOS_UINT8)pTafPdp->QosTab.ulMaxBitUl;
    }
    else
    {
        if (pTafPdp->QosTab.ulMaxBitUl <= 568)
        {
            pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulMaxBitUl < 576)
            {
                pApsQos->ucMaxBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulMaxBitUl <= 8640)
                {
                    pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Maximum bit rate in octet 17 */
                    if (pTafPdp->QosTab.ulMaxBitUl < 8700)
                    {
                        pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForUp = 254;
                        if (pTafPdp->QosTab.ulMaxBitUl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulMaxBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitUl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitUl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucMaxBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

}


VOS_VOID  Taf_FillQos_Set_MaxBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucMaxBitRateForDownExt = 0;
    #endif

    if (pTafPdp->QosTab.ulMaxBitDl <= 63)
    {
        pApsQos->ucMaxBitRateForDown   = (VOS_UINT8)pTafPdp->QosTab.ulMaxBitDl;
    }
    else
    {
        if (pTafPdp->QosTab.ulMaxBitDl <= 568)
        {
            pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulMaxBitDl < 576)
            {
                pApsQos->ucMaxBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulMaxBitDl <= 8640)
                {
                    pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Maximum bit rate in octet 15. */
                    if (pTafPdp->QosTab.ulMaxBitDl < 8700)
                    {
                        pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForDown = 254;

                        if (pTafPdp->QosTab.ulMaxBitDl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulMaxBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->QosTab.ulMaxBitDl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulMaxBitDl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulMaxBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucMaxBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucMaxBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}


VOS_VOID  Taf_FillQos_Set_TransDelay(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{

    if (pTafPdp->QosTab.usTransDelay <= 150)
    {
        pApsQos->ucTransDelay = (VOS_UINT8)(pTafPdp->QosTab.usTransDelay / 10);
    }
    else
    {
        if (pTafPdp->QosTab.usTransDelay < 200)
        {
            pApsQos->ucTransDelay = 15;
        }
        else
        {
            if (pTafPdp->QosTab.usTransDelay <= 950)
            {

                pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->QosTab.usTransDelay - 200) / 50) + 16);
            }
            else
            {
                if (pTafPdp->QosTab.usTransDelay < 1000)
                {
                    pApsQos->ucTransDelay = 31;
                }
                else
                {
                    if (pTafPdp->QosTab.usTransDelay <= 4000)
                    {
                        pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->QosTab.usTransDelay - 1000) / 100) + 32);
                    }
                    else
                    {
                        pApsQos->ucTransDelay = 62;
                    }
                }

            }
        }
    }

}


VOS_VOID  Taf_FillQos_Set_GuarantBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /* Guaranteed bit rate for uplink, octet 12:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed Guaranteed bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The Guaranteed bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The Guaranteed bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps

        Guaranteed bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for uplink in octet 12.

                        For all other values: Ignore the value indicated by the Guaranteed bit rate for uplink in octet 12
                        and use the following value:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The Guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The Guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucGuarantBitRateForUpExt = 0;
    #endif

    if (pTafPdp->QosTab.ulGuarantBitUl <= 63)
    {
        pApsQos->ucGuarantBitRateForUp   = (VOS_UINT8)pTafPdp->QosTab.ulGuarantBitUl;
    }
    else
    {
        if (pTafPdp->QosTab.ulGuarantBitUl <= 568)
        {
            pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulGuarantBitUl < 576)
            {
                pApsQos->ucGuarantBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulGuarantBitUl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Guaranteed bit rate in octet 18 */
                    if (pTafPdp->QosTab.ulGuarantBitUl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;
                        if (pTafPdp->QosTab.ulGuarantBitUl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulGuarantBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitUl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitUl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucGuarantBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}


VOS_VOID  Taf_FillQos_Set_GuarantBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucGuarantBitRateForDownExt = 0;
    #endif

    if (pTafPdp->QosTab.ulGuarantBitDl <= 63)
    {
        pApsQos->ucGuarantBitRateForDown   = (VOS_UINT8)pTafPdp->QosTab.ulGuarantBitDl;
    }
    else
    {
        if (pTafPdp->QosTab.ulGuarantBitDl <= 568)
        {
            pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->QosTab.ulGuarantBitDl < 576)
            {
                pApsQos->ucGuarantBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->QosTab.ulGuarantBitDl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for downlink */
                    /* higher than 8640 kbps, it shall set octet 9 to "11111110", i.e. 8640 kbps, */
                    /* and shall encode the value for the Guaranteed bit rate in octet 16. */
                    if (pTafPdp->QosTab.ulGuarantBitDl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;

                        if (pTafPdp->QosTab.ulGuarantBitDl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->QosTab.ulGuarantBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->QosTab.ulGuarantBitDl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->QosTab.ulGuarantBitDl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->QosTab.ulGuarantBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucGuarantBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucGuarantBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

}


VOS_VOID  Taf_FillQos_Set_DelayClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucTrafficClass)
    {
        case    APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL    :
        case    APS_QOS_TRAFFIC_CLASS_STREAMING     :
            pApsQos->ucDelayClass           = 1;
            break;

        case    APS_QOS_TRAFFIC_CLASS_INTERACTIVE   :
            switch(pApsQos->ucTraffHandlPrior)
            {
                case    APS_QOS_TRAFFF_HANDL_PRIOR_1    :
                    pApsQos->ucDelayClass   = 1;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_2    :
                    pApsQos->ucDelayClass   = 2;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_3    :
                    pApsQos->ucDelayClass   = 3;
                    break;

                default :
                    pApsQos->ucDelayClass   = 0;
                    break;
            }
            break;

        case    APS_QOS_TRAFFIC_CLASS_BACKGROUND    :
            pApsQos->ucDelayClass           = 4;
            break;

        default :
            pApsQos->ucDelayClass           = 0;
            break;
    }

    return;
}


VOS_VOID  Taf_FillQos_Set_ReliabClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucSduErrRatio)
    {
        case    APS_QOS_SDU_ERR_RATIO_1EM5  :
        case    APS_QOS_SDU_ERR_RATIO_1EM6  :
        case    APS_QOS_SDU_ERR_RATIO_1EM10 :
            pApsQos->ucReliabClass          = 2;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM4  :
            pApsQos->ucReliabClass          = 3;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM2  :
        case    APS_QOS_SDU_ERR_RATIO_7EM3  :
        case    APS_QOS_SDU_ERR_RATIO_1EM3  :
            if ( pApsQos->ucResidualBer >= APS_QOS_RESIDUAL_BER_1EM4)
            {
                pApsQos->ucReliabClass      = 4;
            }
            else
            {
                pApsQos->ucReliabClass      = 5;
            }
            break;

        default:
            pApsQos->ucReliabClass          = 0;
            break;
    }

    return;
}


VOS_VOID  Taf_FillQos_Set_PeakThrough(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_SUBSCRIBE)
    {
        pApsQos->ucPeakThrough              = 0;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_16KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_32KBPS )
    {
        pApsQos->ucPeakThrough              = 2;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_64KBPS )
    {
        pApsQos->ucPeakThrough              = 3;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_128KBPS )
    {
        pApsQos->ucPeakThrough              = 4;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_256KBPS )
    {
        pApsQos->ucPeakThrough              = 5;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_512KBPS )
    {
        pApsQos->ucPeakThrough              = 6;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_1024KBPS )
    {
        pApsQos->ucPeakThrough              = 7;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_2048KBPS )
    {
        pApsQos->ucPeakThrough              = 8;
    }
    else if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_0KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else
    {
        pApsQos->ucPeakThrough              = 9;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Taf_FillQos_Set_SrcStatisticsDescriptor
 ��������  : ����Source Statistics Descriptor(Taf_FillQos��Ȧ���Ӷ�)
 �������  : pstTafPdp  --ָ���ֵ����ı䣬ָ��const��ָ��
 �������  : pstApsQos
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_SrcStatisticsDescriptor(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ((APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE     != pstApsQos->ucTrafficClass)
     && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND      != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSrcStatisticsDescriptor  = pstTafPdp->QosTab.ucSrcStatisticsDescriptor;
    }
    else
    {
        pstApsQos->ucSrcStatisticsDescriptor  = 0;    /*ĿǰĬ����дΪ0*/
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Taf_FillQos_Set_SignallingIndication
 ��������  : ����Signalling Indication(Taf_FillQos��Ȧ���Ӷ�)
 �������  : pTafPdp    --ָ���ֵ����ı䣬ָ��const��ָ��
 �������  : pApsQos
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Taf_FillQos_Set_SignallingIndication(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL  != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING       != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND      != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSignallingIndication     = pstTafPdp->QosTab.ucSignallingIndication;

        if ( 1 == pstApsQos->ucSignallingIndication)
        {
            pstApsQos->ucTraffHandlPrior      = 1;
        }
    }
    else
    {
        pstApsQos->ucSignallingIndication     = 0;    /*ĿǰĬ����дΪ0*/
    }

    return;
}
VOS_VOID  Taf_FillQos_QosTab_Used(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*ǰ5����APP/AT�������õģ�ֱ�Ӹ�ֵΪ���������*/
    /*��5��ĸ�ֵ����QOS��ֵ�������и�ֵ*/
    /*
    pApsQos->ucDelayClass            = 0;   / *0: Subscribed value* /
    pApsQos->ucReliabClass           = 0;   / *0: subscribed value* /
    pApsQos->ucPeakThrough           = 0;   / *0: Subscribed value* /
    pApsQos->ucPrecedenceClass       = 0;   / *0: Subscribed value* /
    pApsQos->ucMeanThrough           = 0;   / *0: Subscribed value* /
    */

    /*ATЭ����ȡֵ������24008�ж��岻��ͬ���ڴ���ת�� */
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if (pTafPdp->QosTab.ucTrafficClass >= APS_APP_QOS_TRAFFICCLASS_TOP)
    {
        pApsQos->ucTrafficClass = APS_3GPP_QOS_TRAFFIC_CLASS_SUBSCRIBE;
    }
    else
    {
        pApsQos->ucTrafficClass
            = pTafPdp->QosTab.ucTrafficClass
              + APS_TRAFFICCLASS_APP3GPP_DIFF_VAL;
    }

    /*
    In MS to network direction:
    0 0     Subscribed delivery order
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     With delivery order ('yes')
    1 0     Without delivery order ('no')
    1 1     Reserved
    */
    if (pTafPdp->QosTab.ucDeliverOrder <= APS_APP_QOS_DELIVERORDER_TOP)
    {
        pApsQos->ucDeliverOrder
            = APS_DELIVERORDER_APP3GPP_DIFF_VAL
              - pTafPdp->QosTab.ucDeliverOrder;
    }
    else
    {
        pApsQos->ucDeliverOrder = APS_3GPP_QOS_DELIVERORDER_SUB;
    }

    /*
    In MS to network direction:
    0 0 0       Subscribed delivery of erroneous SDUs
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       No detect ('-')
    0 1 0       Erroneous SDUs are delivered ('yes')
    0 1 1       Erroneous SDUs are not delivered ('no')
    1 1 1       Reserved
    */
    if (pTafPdp->QosTab.ucDeliverErrSdu <= APS_APP_QOS_DELIVER_ERRSDU_TOP)
    {
        pApsQos->ucDeliverOfErrSdu
            = APS_DELIVEROFERRSDU_APP3GPP_DIFF_VAL
              - pTafPdp->QosTab.ucDeliverErrSdu;
    }
    else
    {
        pApsQos->ucDeliverOfErrSdu = APS_3GPP_QOS_DELIVER_ERRSDU_SUB;
    }

    Taf_FillQos_Set_MaximSduSize(pTafPdp, pApsQos);

    Taf_FillQos_Set_MaxBitRateForUp(pTafPdp, pApsQos);

    Taf_FillQos_Set_MaxBitRateForDown(pTafPdp, pApsQos);

    /*
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
    0 0 0 1     5*10-2
    0 0 1 0     1*10-2
    0 0 1 1     5*10-3
    0 1 0 0     4*10-3
    0 1 0 1     1*10-3
    0 1 1 0     1*10-4
    0 1 1 1     1*10-5
    1 0 0 0     1*10-6
    1 0 0 1     6*10-8
    1 1 1 1     Reserved
    */
    pApsQos->ucResidualBer           = pTafPdp->QosTab.ucResidualBer;

    /*
    In MS to network direction:
    0 0 0 0     Subscribed SDU error ratio
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
    0 0 0 1     1*10-2
    0 0 1 0     7*10-3
    0 0 1 1     1*10-3
    0 1 0 0     1*10-4
    0 1 0 1     1*10-5
    0 1 1 0     1*10-6
    0 1 1 1     1*10-1
    1 1 1 1     Reserved
    */
    pApsQos->ucSduErrRatio           = pTafPdp->QosTab.ucSduErrRatio;

    Taf_FillQos_Set_TransDelay(pTafPdp, pApsQos);

    /*
    In MS to network direction:
    0 0     Subscribed traffic handling priority
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     Priority level 1
    1 0     Priority level 2
    1 1     Priority level 3
    */
    pApsQos->ucTraffHandlPrior       = pTafPdp->QosTab.ucTraffHandlePrior;

    Taf_FillQos_Set_GuarantBitRateForUp(pTafPdp, pApsQos);

    Taf_FillQos_Set_GuarantBitRateForDown(pTafPdp, pApsQos);

    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    /* Modified by w00316404 for M project A characeristic AT part, 2015-4-7, Begin */
    Taf_FillQos_Set_SrcStatisticsDescriptor(pTafPdp, pApsQos);
    Taf_FillQos_Set_SignallingIndication(pTafPdp, pApsQos);
    /* Modified by w00316404 for M project A characeristic AT part, 2015-4-7, End */
    #endif

    return;
}

/*****************************************************************************
 Function:       Taf_FillQos
 Description:    ����Qos����APP�趨��ֵ��ת��Ϊ24008�ж����ֵ.��ȫ�̳�V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pTafPdp - TAF CID���е�PDP��Ϣ
 Output:         pApsQos - APS��Ҫ��Qosȡֵ
 Return:
 Others:
******************************************************************************/
VOS_VOID  Taf_FillQos(  TAF_PDP_TABLE_STRU         *pTafPdp,
                        APS_PDP_QOS_STRU           *pApsQos   )
{

    if (TAF_USED == pTafPdp->ucQosTabFlag)
    {   /*Qos����Ч*/
        Taf_FillQos_QosTab_Used(pTafPdp, pApsQos);
    }
    else
    {   /*Qos����Ч����Ϊ�������ȡֵ*/
        /*
        pApsQos->ucDelayClass               = 0;    / *0: Subscribed value* /
        pApsQos->ucReliabClass              = 0;    / *0: Subscribed value* /
        pApsQos->ucPeakThrough              = 0;    / *0: Subscribed value* /
        pApsQos->ucPrecedenceClass          = 0;    / *0: Subscribed value* /
        pApsQos->ucMeanThrough              = 0;    / *0: Subscribed value* /
        */
        pApsQos->ucTrafficClass             = 0;    /*0: Subscribed value*/
        pApsQos->ucDeliverOrder             = 0;    /*0: Subscribed value*/
        pApsQos->ucDeliverOfErrSdu          = 0;    /*0: Subscribed value*/
        pApsQos->ucMaximSduSize             = 0;    /*0: Subscribed value*/
        pApsQos->ucMaxBitRateForUp          = 0;    /*0: Subscribed value*/
        pApsQos->ucMaxBitRateForDown        = 0;    /*0: Subscribed value*/
        pApsQos->ucResidualBer              = 0;    /*0: Subscribed value*/
        pApsQos->ucSduErrRatio              = 0;    /*0: Subscribed value*/
        pApsQos->ucTransDelay               = 0;    /*0: Subscribed value*/
        pApsQos->ucTraffHandlPrior          = 0;    /*0: Subscribed value*/
        pApsQos->ucGuarantBitRateForUp      = 0;    /*0: Subscribed value*/
        pApsQos->ucGuarantBitRateForDown    = 0;    /*0: Subscribed value*/
        #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
        pApsQos->ucSrcStatisticsDescriptor  = 0;    /*0: unknown*/
        pApsQos->ucSignallingIndication     = 0;    /*0: Not optimised for signalling traffic*/
        pApsQos->ucMaxBitRateForDownExt     = 0;
        pApsQos->ucGuarantBitRateForDownExt = 0;
        #endif
        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
        pApsQos->ucMaxBitRateForUpExt       = 0;
        pApsQos->ucGuarantBitRateForUpExt   = 0;
        #endif
    }

    /*����Traffic classȷ��DelayClass */
    Taf_FillQos_Set_DelayClass(pApsQos);

    /*����SDU error ratio��Residual bit error ratioȷ��ucReliabClass*/
    Taf_FillQos_Set_ReliabClass(pApsQos);

    /*����Maximum bitrateȷ��ucPeakThrough*/
    Taf_FillQos_Set_PeakThrough(pApsQos);

    /*As the allocation/retention priority attribute is not available in the UE
    (see 6.4.4.1) the UE shall set the R97/98 precedence class attribute to the
    value "subscribed"*/
    pApsQos->ucPrecedenceClass              = 0;

    /*Mean throughput*/
    pApsQos->ucMeanThrough                  = g_ucMeanThrough;

    return;
}
VOS_VOID  Taf_FillMinQos_Set_MaximSduSize(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{

    if (pTafPdp->MinQosTab.usMaxSduSize <= 1500)
    {
        pApsQos->ucMaximSduSize      = (VOS_UINT8)(pTafPdp->MinQosTab.usMaxSduSize / 10);
    }
    else
    {
        if (1502 == pTafPdp->MinQosTab.usMaxSduSize)
        {
            pApsQos->ucMaximSduSize = 151;
        }
        else
        {
            if (1510 == pTafPdp->MinQosTab.usMaxSduSize)
            {
                pApsQos->ucMaximSduSize = 152;
            }
            else
            {
                if (1520 == pTafPdp->MinQosTab.usMaxSduSize)
                {
                    pApsQos->ucMaximSduSize = 153;
                }
                else
                {
                    pApsQos->ucMaximSduSize = 0;
                }
            }
        }
    }

    return;
}


VOS_VOID  Taf_FillMinQos_Set_MaxBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*  In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed maximum bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The maximum bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The maximum bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The maximum bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps


        Maximum bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Maximum bit rate for uplink in octet 8.

                        For all other values: Ignore the value indicated by the Maximum bit rate for uplink in octet 8
                        and use the following value:
        0 0 0 0 0 0 0 1 The maximum bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The maximum bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The maximum bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucMaxBitRateForUpExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulMaxBitUl <= 63)
    {
        pApsQos->ucMaxBitRateForUp   = (VOS_UINT8)pTafPdp->MinQosTab.ulMaxBitUl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulMaxBitUl <= 568)
        {
            pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulMaxBitUl < 576)
            {
                pApsQos->ucMaxBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulMaxBitUl <= 8640)
                {
                    pApsQos->ucMaxBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Maximum bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Maximum bit rate in octet 17 */
                    if (pTafPdp->MinQosTab.ulMaxBitUl < 8700)
                    {
                        pApsQos->ucMaxBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForUp = 254;
                        if (pTafPdp->MinQosTab.ulMaxBitUl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulMaxBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitUl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitUl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucMaxBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}


VOS_VOID  Taf_FillMinQos_Set_MaxBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucMaxBitRateForDownExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulMaxBitDl <= 63)
    {
        pApsQos->ucMaxBitRateForDown   = (VOS_UINT8)pTafPdp->MinQosTab.ulMaxBitDl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulMaxBitDl <= 568)
        {
            pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulMaxBitDl < 576)
            {
                pApsQos->ucMaxBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulMaxBitDl <= 8640)
                {
                    pApsQos->ucMaxBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    if (pTafPdp->MinQosTab.ulMaxBitDl < 8700)
                    {
                        pApsQos->ucMaxBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucMaxBitRateForDown = 254;

                        if (pTafPdp->MinQosTab.ulMaxBitDl <= 16000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulMaxBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->MinQosTab.ulMaxBitDl <= 128000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulMaxBitDl <= 256000)
                        {
                            pApsQos->ucMaxBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulMaxBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucMaxBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucMaxBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}
VOS_VOID  Taf_FillMinQos_Set_TransDelay(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{

    if (pTafPdp->MinQosTab.usTransDelay <= 150)
    {
        pApsQos->ucTransDelay = (VOS_UINT8)(pTafPdp->MinQosTab.usTransDelay / 10);
    }
    else
    {
        if (pTafPdp->MinQosTab.usTransDelay < 200)
        {
            pApsQos->ucTransDelay = 15;
        }
        else
        {
            if (pTafPdp->MinQosTab.usTransDelay <= 950)
            {
                pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->MinQosTab.usTransDelay - 200) / 50) + 16);
            }
            else
            {
                if (pTafPdp->MinQosTab.usTransDelay < 1000)
                {
                    pApsQos->ucTransDelay = 31;
                }
                else
                {
                    if (pTafPdp->MinQosTab.usTransDelay <= 4000)
                    {
                        pApsQos->ucTransDelay = (VOS_UINT8)(((pTafPdp->MinQosTab.usTransDelay - 1000) / 100) + 32);
                    }
                    else
                    {
                        pApsQos->ucTransDelay = 62;
                    }
                }

            }
        }
    }

    return;
}


VOS_VOID  Taf_FillMinQos_Set_GuarantBitRateForUp(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /* Guaranteed bit rate for uplink, octet 12:
        In MS to network direction:
        0 0 0 0 0 0 0 0 Subscribed Guaranteed bit rate for uplink
        In network to MS direction:
        0 0 0 0 0 0 0 0 Reserved

        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is binary coded in 8 bits, using a granularity of 1 kbps
        0 0 1 1 1 1 1 1 giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

        0 1 0 0 0 0 0 0 The Guaranteed bit rate is 64 kbps + ((the binary coded value in 8 bits -01000000) * 8 kbps)
        0 1 1 1 1 1 1 1 giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

        1 0 0 0 0 0 0 0 The Guaranteed bit rate is 576 kbps + ((the binary coded value in 8 bits -10000000) * 64 kbps)
        1 1 1 1 1 1 1 0 giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

        1 1 1 1 1 1 1 1 0kbps

        Guaranteed bit rate for uplink (extended), octet 17
        Bits
        8 7 6 5 4 3 2 1
        In MS to network direction and in network to MS direction:
        0 0 0 0 0 0 0 0 Use the value indicated by the Guaranteed bit rate for uplink in octet 12.

                        For all other values: Ignore the value indicated by the Guaranteed bit rate for uplink in octet 12
                        and use the following value:
        0 0 0 0 0 0 0 1 The Guaranteed bit rate is 8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
        0 1 0 0 1 0 1 0 giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

        0 1 0 0 1 0 1 1 The Guaranteed bit rate is 16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
        1 0 1 1 1 0 1 0 giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

        1 0 1 1 1 0 1 1 The Guaranteed bit rate is 128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
        1 1 1 1 1 0 1 0 giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.

        The network shall map all other values not explicitly defined onto one of the values defined in this version of the protocol.
        The network shall return a negotiated value which is explicitly defined in this version of the protocol

    */

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pApsQos->ucGuarantBitRateForUpExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulGuarantBitUl <= 63)
    {
        pApsQos->ucGuarantBitRateForUp   = (VOS_UINT8)pTafPdp->MinQosTab.ulGuarantBitUl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulGuarantBitUl <= 568)
        {
            pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulGuarantBitUl < 576)
            {
                pApsQos->ucGuarantBitRateForUp = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulGuarantBitUl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForUp = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                    pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    /* If the sending entity wants to indicate a Guaranteed bit rate for uplink
                          higher than 8640 kbps, it shall set octet 8 to "11111110",
                          i.e. 8640 kbps, and shall encode the value for the Guaranteed bit rate in octet 18 */
                    if (pTafPdp->MinQosTab.ulGuarantBitUl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForUp = 254;
                        if (pTafPdp->MinQosTab.ulGuarantBitUl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulGuarantBitUl - 8600) / 100);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitUl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitUl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForUpExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitUl - 128000) / 2000) + 186);
                        }
                        else
                        {
                            pApsQos->ucGuarantBitRateForUpExt = 250;  /*1 1 1 1 1 0 1 0*/
                        }
                    }
                    #endif
                }
            }
        }
    }

}


VOS_VOID  Taf_FillMinQos_Set_GuarantBitRateForDown(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    pApsQos->ucGuarantBitRateForDownExt = 0;
    #endif

    if (pTafPdp->MinQosTab.ulGuarantBitDl <= 63)
    {
        pApsQos->ucGuarantBitRateForDown   = (VOS_UINT8)pTafPdp->MinQosTab.ulGuarantBitDl;
    }
    else
    {
        if (pTafPdp->MinQosTab.ulGuarantBitDl <= 568)
        {
            pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 64) / 8) + 64);
        }
        else
        {
            if (pTafPdp->MinQosTab.ulGuarantBitDl < 576)
            {
                pApsQos->ucGuarantBitRateForDown = 127;  /*0 1 1 1 1 1 1 1*/
            }
            else
            {
                if (pTafPdp->MinQosTab.ulGuarantBitDl <= 8640)
                {
                    pApsQos->ucGuarantBitRateForDown = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 576) / 64) + 128);
                }
                else
                {
                    #if(PS_UE_REL_VER < PS_PTL_VER_R5)
                    pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    #else
                    if (pTafPdp->MinQosTab.ulGuarantBitDl < 8700)
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;  /*1 1 1 1 1 1 1 0*/
                    }
                    else
                    {
                        pApsQos->ucGuarantBitRateForDown = 254;

                        if (pTafPdp->MinQosTab.ulGuarantBitDl <= 16000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)((pTafPdp->MinQosTab.ulGuarantBitDl - 8600) / 100);
                        }
                        #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
                        else if (pTafPdp->MinQosTab.ulGuarantBitDl <= 128000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 16000) / 1000) + 74);
                        }
                        else if (pTafPdp->MinQosTab.ulGuarantBitDl <= 256000)
                        {
                            pApsQos->ucGuarantBitRateForDownExt
                                = (VOS_UINT8)(((pTafPdp->MinQosTab.ulGuarantBitDl - 128000) / 2000) + 186);
                        }
                        #endif
                        else
                        {
                            #if(PS_UE_REL_VER < PS_PTL_VER_R7)
                            pApsQos->ucGuarantBitRateForDownExt = 74;   /*0 1 0 0 1 0 1 0*/
                            #else
                            pApsQos->ucGuarantBitRateForDownExt = 250;  /*1 1 1 1 1 0 1 0*/
                            #endif
                        }
                    }
                    #endif
                }
            }
        }
    }

    return;
}
VOS_VOID  Taf_FillMinQos_Set_DelayClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*����Traffic classȷ��DelayClass */
    switch(pApsQos->ucTrafficClass)
    {
        case    APS_QOS_TRAFFIC_CLASS_CONVERSATIONAL    :
        case    APS_QOS_TRAFFIC_CLASS_STREAMING     :
            pApsQos->ucDelayClass           = 1;
            break;

        case    APS_QOS_TRAFFIC_CLASS_INTERACTIVE   :
            switch(pApsQos->ucTraffHandlPrior)
            {
                case    APS_QOS_TRAFFF_HANDL_PRIOR_1    :
                    pApsQos->ucDelayClass   = 1;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_2    :
                    pApsQos->ucDelayClass   = 2;
                    break;

                case    APS_QOS_TRAFFF_HANDL_PRIOR_3    :
                    pApsQos->ucDelayClass   = 3;
                    break;

                default :
                    pApsQos->ucDelayClass   = 0;
                    break;
            }
            break;

        case    APS_QOS_TRAFFIC_CLASS_BACKGROUND    :
            pApsQos->ucDelayClass           = 4;
            break;

        default :
            pApsQos->ucDelayClass           = 0;
            break;
    }

    return;
}
VOS_VOID  Taf_FillMinQos_Set_ReliabClass(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    switch(pApsQos->ucSduErrRatio)
    {
        case    APS_QOS_SDU_ERR_RATIO_1EM5  :
        case    APS_QOS_SDU_ERR_RATIO_1EM6  :
        case    APS_QOS_SDU_ERR_RATIO_1EM10 :
            pApsQos->ucReliabClass          = 2;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM4  :
            pApsQos->ucReliabClass          = 3;
            break;

        case    APS_QOS_SDU_ERR_RATIO_1EM2  :
        case    APS_QOS_SDU_ERR_RATIO_7EM3  :
        case    APS_QOS_SDU_ERR_RATIO_1EM3  :
            if ( pApsQos->ucResidualBer >= APS_QOS_RESIDUAL_BER_1EM4)
            {
                pApsQos->ucReliabClass      = 4;
            }
            else
            {
                pApsQos->ucReliabClass      = 5;
            }
            break;

        default:
            pApsQos->ucReliabClass          = 0;
            break;
    }

    return;
}


VOS_VOID  Taf_FillMinQos_Set_PeakThrough(
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_SUBSCRIBE)
    {
        pApsQos->ucPeakThrough              = 0;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_16KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_32KBPS )
    {
        pApsQos->ucPeakThrough              = 2;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_64KBPS )
    {
        pApsQos->ucPeakThrough              = 3;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_128KBPS )
    {
        pApsQos->ucPeakThrough              = 4;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_256KBPS )
    {
        pApsQos->ucPeakThrough              = 5;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_512KBPS )
    {
        pApsQos->ucPeakThrough              = 6;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_1024KBPS )
    {
        pApsQos->ucPeakThrough              = 7;
    }
    else if ( pApsQos->ucMaxBitRateForUp < APS_QOS_MAX_BITRATE_2048KBPS )
    {
        pApsQos->ucPeakThrough              = 8;
    }
    else if ( pApsQos->ucMaxBitRateForUp == APS_QOS_MAX_BITRATE_0KBPS )
    {
        pApsQos->ucPeakThrough              = 1;
    }
    else
    {
        pApsQos->ucPeakThrough              = 9;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Taf_FillMinQos_Set_SrcStatisticsDescriptor
 ��������  : ����Source Statistics Descriptor(Taf_FillMinQos��Ȧ���Ӷ�)
 �������  : pTafPdp    --ָ���ֵ����ı䣬ָ��const��ָ��
 �������  : pApsQos
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_SrcStatisticsDescriptor(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_INTERACTIVE    != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND     != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSrcStatisticsDescriptor  = pstTafPdp->MinQosTab.ucSrcStatisticsDescriptor;
    }
    else
    {
        pstApsQos->ucSrcStatisticsDescriptor  = 0;    /*ĿǰĬ����дΪ0*/
    }

    return;
}

/*****************************************************************************
 �� �� ��  : Taf_FillMinQos_Set_SignallingIndication
 ��������  : ����Signalling Indication(Taf_FillMinQos��Ȧ���Ӷ�)
 �������  : pTafPdp    --ָ���ֵ����ı䣬ָ��const��ָ��
 �������  : pApsQos
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Taf_FillMinQos_Set_SignallingIndication(
    const TAF_PDP_TABLE_STRU            *pstTafPdp,
    APS_PDP_QOS_STRU                    *pstApsQos
)
{
    if ( (APS_3GPP_QOS_TRAFFIC_CLASS_CONVERSATIONAL     != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_STREAMING          != pstApsQos->ucTrafficClass)
      && (APS_3GPP_QOS_TRAFFIC_CLASS_BACKGROUND         != pstApsQos->ucTrafficClass))
    {
        pstApsQos->ucSignallingIndication     = pstTafPdp->MinQosTab.ucSignallingIndication;

        if ( 1 == pstApsQos->ucSignallingIndication)
        {
            pstApsQos->ucTraffHandlPrior      = 1;
        }
    }
    else
    {
        pstApsQos->ucSignallingIndication     = 0;    /*ĿǰĬ����дΪ0*/
    }

    return;
}
VOS_VOID  Taf_FillMinQos(
    TAF_PDP_TABLE_STRU                  *pTafPdp,
    APS_PDP_QOS_STRU                    *pApsQos
)
{
    /*ATЭ����ȡֵ������24008�ж��岻��ͬ���ڴ���ת�� */
    /*
    In MS to network direction:
    0 0 0       Subscribed traffic class
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       Conversational class
    0 1 0       Streaming class
    0 1 1       Interactive class
    1 0 0       Background class
    1 1 1       Reserved
    */
    if (pTafPdp->MinQosTab.ucTrafficClass >= 4)
    {
        pApsQos->ucTrafficClass = 0;
    }
    else
    {
        pApsQos->ucTrafficClass = pTafPdp->MinQosTab.ucTrafficClass + 1;
    }

    /*
    In MS to network direction:
    0 0     Subscribed delivery order
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     With delivery order ('yes')
    1 0     Without delivery order ('no')
    1 1     Reserved
    */
    if (pTafPdp->MinQosTab.ucDeliverOrder <= 2)
    {
        pApsQos->ucDeliverOrder = 2 - pTafPdp->MinQosTab.ucDeliverOrder;
    }
    else
    {
        pApsQos->ucDeliverOrder = 0;
    }

    /*
    In MS to network direction:
    0 0 0       Subscribed delivery of erroneous SDUs
    In network to MS direction:
    0 0 0       Reserved
    In MS to network direction and in network to MS direction:
    0 0 1       No detect ('-')
    0 1 0       Erroneous SDUs are delivered ('yes')
    0 1 1       Erroneous SDUs are not delivered ('no')
    1 1 1       Reserved
    */
    if (pTafPdp->MinQosTab.ucDeliverErrSdu <= 3)
    {
        pApsQos->ucDeliverOfErrSdu = 3 - pTafPdp->MinQosTab.ucDeliverErrSdu;
    }
    else
    {
        pApsQos->ucDeliverOfErrSdu = 0;
    }

    Taf_FillMinQos_Set_MaximSduSize(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_MaxBitRateForUp(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_MaxBitRateForDown(pTafPdp, pApsQos);

    /*
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The Residual BER value consists of 4 bits. The range is from 5*10-2 to 6*10-8.
    0 0 0 1     5*10-2
    0 0 1 0     1*10-2
    0 0 1 1     5*10-3
    0 1 0 0     4*10-3
    0 1 0 1     1*10-3
    0 1 1 0     1*10-4
    0 1 1 1     1*10-5
    1 0 0 0     1*10-6
    1 0 0 1     6*10-8
    1 1 1 1     Reserved
    */
    pApsQos->ucResidualBer           = pTafPdp->MinQosTab.ucResidualBer;

    /*
    In MS to network direction:
    0 0 0 0     Subscribed SDU error ratio
    In network to MS direction:
    0 0 0 0     Reserved
    In MS to network direction and in network to MS direction:
    The SDU error ratio value consists of 4 bits. The range is is from 1*10-1 to 1*10-6.
    0 0 0 1     1*10-2
    0 0 1 0     7*10-3
    0 0 1 1     1*10-3
    0 1 0 0     1*10-4
    0 1 0 1     1*10-5
    0 1 1 0     1*10-6
    0 1 1 1     1*10-1
    1 1 1 1     Reserved
    */
    pApsQos->ucSduErrRatio           = pTafPdp->MinQosTab.ucSduErrRatio;

    Taf_FillMinQos_Set_TransDelay(pTafPdp, pApsQos);

    /*
    In MS to network direction:
    0 0     Subscribed traffic handling priority
    In network to MS direction:
    0 0     Reserved
    In MS to network direction and in network to MS direction:
    0 1     Priority level 1
    1 0     Priority level 2
    1 1     Priority level 3
    */
    pApsQos->ucTraffHandlPrior       = pTafPdp->MinQosTab.ucTraffHandlePrior;

    Taf_FillMinQos_Set_GuarantBitRateForUp(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_GuarantBitRateForDown(pTafPdp, pApsQos);

    Taf_FillMinQos_Set_DelayClass(pApsQos);

    /*����SDU error ratio��Residual bit error ratioȷ��ucReliabClass*/
    Taf_FillMinQos_Set_ReliabClass(pApsQos);

    /*����Maximum bitrateȷ��ucPeakThrough*/
    Taf_FillMinQos_Set_PeakThrough(pApsQos);

    /*As the allocation/retention priority attribute is not available in the UE
    (see 6.4.4.1) the UE shall set the R97/98 precedence class attribute to the
    value "subscribed"*/
    pApsQos->ucPrecedenceClass              = 0;

    /*Mean throughput class Always set to 31*/
    pApsQos->ucMeanThrough                  = 31;

    /* Added by w00316404 for M project A characeristic AT part, 2015-4-7, Begin */
    #if(PS_UE_REL_VER >= PS_PTL_VER_R5)
    Taf_FillMinQos_Set_SrcStatisticsDescriptor(pTafPdp, pApsQos);
    Taf_FillMinQos_Set_SignallingIndication(pTafPdp, pApsQos);
    #endif
    /* Added by w00316404 for M project A characeristic AT part, 2015-4-7, End */

    return;
}
VOS_VOID Taf_LenStr2Apn(
    CONST TAF_PDP_APN_STRU              *pstApn,
    VOS_UINT8                           *pucApn
)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucLenPosition = 1;
    if (0 == pstApn->ucLength)
    {   /*APN����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
        pucApn[0] = 0;
        return;
    }

    for (i = 1; (i <= pstApn->ucLength) && (i <= TAF_MAX_APN_LEN); i++)
    {   /*�ӵ�1����Ч�ַ���ʼ���*/
        if (pstApn->aucValue[i - 1] != '.')
        {   /*�������Ч�ַ������俽��*/
            pucApn[i + 1] = pstApn->aucValue[i - 1];
            j++;  /*��Ч�ַ�����1*/
        }
        else
        {   /*����ַ���'.'�����.��ǰ��Ч�ַ�������*/
            pucApn[ucLenPosition] = j;
            j = 0;  /*��ʼ��һ����Ч�ַ��εĳ����ۼ�*/
            ucLenPosition = i + 1; /*��һ����Ч�ַ��������λ��*/
        }
    }
    pucApn[ucLenPosition] = j; /*������һ����Ч�ַ��ĳ���*/
    pucApn[0] = i;  /*�������APN�ĳ���*/
    return;
}

/******************************************************************************
 Function:       Taf_LenStr2IpAddr
 Description:    ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ.��ȫ�̳�V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucStr - �ַ�����ʽ��IP��ַ
 Output:         pucIpAddr - SMЭ�鶨���IP��ַ
 Return:         ��
 Others:
******************************************************************************/
VOS_VOID Taf_LenStr2IpAddr(CONST VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucValue = 0;

    if (0 == pucStr[0])
    {   /*ADDR����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return;
    }

    if (pucStr[1] == '.')
    {   /*�����1����Ч�ַ���'.'��IP��ַ�ǷǷ���*/
        return;
    }
    for (i = 1; (i <= pucStr[0]) && (i < TAF_MAX_IPV4_ADDR_STR_LEN); i++)
    {   /*�ӵ�1����Ч�ַ���ʼ���*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {   /*����'0'-'9'���ַ��Ƿ�*/
            return;
        }
        if (pucStr[i] != '.')
        {   /*�������Ч�ַ���ת��Ϊ����*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {   /*�ַ���ת��Ϊ��ЧIP��λֵ*/
                ucValue = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {   /*����255����*/
                return;
            }
        }
        else
        {   /*����ַ���'.'��ǰһλ��ֵ�Ѿ��������*/
            if (j <= 3)
            {   /*���汾ֻ֧��IPV4��ַ*/
                pucIpAddr[j] = ucValue;
                ucValue = 0;
                j++;  /*��ʼ��һ����Ч�ַ��εĳ����ۼ�*/
            }
            else
            {   /*����4��IPλ�Σ��Ƿ�*/
                return;
            }
        }
    }
    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return;
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 Prototype      : Aps_PackApsSecActReqPara
 Description    : ���첢�������Aps_PdpSecActReq()��Ҫ���������;
 Input          : ucCid:�ö��μ����cid
                  ucPdpId:�ö��μ����PdpId
 Output         : pApsSecActReq
 Return Value   :
 Data Accessed  : g_TafCidTab[]
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_PackApsSecActReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_SEC_ACT_REQ_ST             *pApsSecActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;
    VOS_UINT32                          ulReturn;

    pTafPdp                                     = VOS_NULL;
    ulReturn                                    = TAF_APS_SUCC;

    pTafPdp                                     = &g_TafCidTab[ucCid];

    pApsSecActReq->OP_Sapi                      = TAF_FREE;
    pApsSecActReq->Op_Xid_DCmp                  = VOS_FALSE;
    pApsSecActReq->Op_Xid_PCmp                  = VOS_FALSE;
    pApsSecActReq->Op_Tft                       = TAF_FREE;
    pApsSecActReq->Op_Spare                     = TAF_FREE;

    pApsSecActReq->Tft.OP_SourcePort            = TAF_FREE;
    pApsSecActReq->Tft.OP_DestPort              = TAF_FREE;
    pApsSecActReq->Tft.OP_SourceIpAddrAndMask   = TAF_FREE;
    pApsSecActReq->Tft.OP_ProtocolId            = TAF_FREE;
    pApsSecActReq->Tft.OP_ulSecuParaIndex       = TAF_FREE;
    pApsSecActReq->Tft.OP_ucTypeOfService       = TAF_FREE;
    pApsSecActReq->Tft.OP_Spare                 = TAF_FREE;

    /*SAPI*/
    pApsSecActReq->OP_Sapi                      = TAF_USED;
    pApsSecActReq->ucSapi                       = APS_SAPI_INIT;
    pApsSecActReq->ucPdpId                      = ucPdpId;

    /*��ȡ��PdpId*/
    pApsSecActReq->ucPriPdpId           = TAF_APS_GetPdpIdByCid(g_TafCidTab[ucCid].ucPriCid);
    if ( TAF_APS_INVALID_PDPID == pApsSecActReq->ucPriPdpId)
    {
        /*û���ҵ���PDP*/
        APS_WARN_LOG("not find pri PDP !");
        return  TAF_APS_FAIL;
    }

    /*����Qos*/
    Taf_FillQos( pTafPdp, &pApsSecActReq->Qos );

    /*����TFT*/
    if ( TAF_FREE == g_TafCidTab[ucCid].ucPfTabFlag )
    {
        /*if(PDPȫ�����ݱ��и�CID��PDPû�ж���TFT)*/
        pApsSecActReq->Op_Tft                       = TAF_FREE;
    }
    else
    {
        pApsSecActReq->Op_Tft                       = TAF_USED;
        ulReturn = Aps_FillTft( pTafPdp, &pApsSecActReq->Tft );
        if ( TAF_APS_SUCC != ulReturn )
        {
            return TAF_APS_FAIL;
        }
    }

    /*����XID*/
    Aps_FillSecXid(pTafPdp, pApsSecActReq);

    /*�����ϣ�ֱ�ӷ��سɹ�*/
    return TAF_SUCCESS;

}

/*****************************************************************************
 Prototype      : Aps_FillSecXid
 Description    : ���APS_PDP_ACT_REQ_ST�ͱ���ʱ����ñ��������XID����ʱʹ�á�
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillSecXid(         TAF_PDP_TABLE_STRU         *pTafPdp,
                                    APS_PDP_SEC_ACT_REQ_ST     *pApsSecActReq  )
{

    pApsSecActReq->Op_Xid_DCmp             = VOS_FALSE;
    pApsSecActReq->Op_Xid_PCmp             = VOS_FALSE;

    switch(pTafPdp->CidTab.enPdpDcomp)
    {
        case    TAF_PDP_D_COMP_OFF  :
            break;

        case    TAF_PDP_D_COMP_ON   :
            pApsSecActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsSecActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        case    TAF_PDP_D_COMP_V42  :
            pApsSecActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsSecActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpDcomp ERR !");
            break;
    }


    switch(pTafPdp->CidTab.enPdpHcomp)
    {
        case    TAF_PDP_H_COMP_OFF  :
            break;

        case    TAF_PDP_H_COMP_ON   :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC1144  :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_1144_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC2507  :
            pApsSecActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsSecActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpHcomp ERR !");
            break;
    }

    return;

}

/*****************************************************************************
 Prototype      : Aps_FillTft
 Description    : ���첢�������Aps_PdpSecActReq()��Ҫ���������TFT;
 Input          : ucCid:�ö��μ����cid
                  ucPdpId:�ö��μ����PdpId
 Output         : pApsSecActReq
 Return Value   :
 Data Accessed  : g_TafCidTab[]
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_FillTft( TAF_PDP_TABLE_STRU              *pTafPdp,
                         APS_PDP_TFT_ST                  *pApsTft )
{
    /* TODO: ���Ͻ� */
#if 0
    pApsTft->ucPacketFilterId               = pTafPdp->astTftTab[0].ucPacketFilterId;
    pApsTft->ucPrecedence                   = pTafPdp->astTftTab[0].ucPrecedence;

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_HighSourcePort)
    {
        pApsTft->OP_SourcePort          = VOS_TRUE;
        pApsTft->usSrcPortHighLimit     = pTafPdp->astTftTab[0].usHighSourcePort;
        pApsTft->usSrcPortLowLimit      = pTafPdp->astTftTab[0].usLowSourcePort;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_HighDestPort)
    {
        pApsTft->OP_DestPort        = VOS_TRUE;
        pApsTft->usDstPortHighLimit = pTafPdp->astTftTab[0].usHighDestPort;
        pApsTft->usDstPortLowLimit  = pTafPdp->astTftTab[0].usLowDestPort;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_SourceIpAddr)
    {
        pApsTft->OP_SourceIpAddrAndMask     = VOS_TRUE;
        if ( TAF_SUCCESS != Taf_LenStr2IpAddr( pTafPdp->astTftTab[0].aucSourceIpAddr,
                                            pApsTft->aucSrcIpAddress ) )
        {
            return  TAF_APS_FAIL;
        }
        if ( TAF_SUCCESS != Taf_LenStr2IpAddr( pTafPdp->astTftTab[0].aucSourceIpMask,
                                            pApsTft->aucSrcIpMask ) )
        {
            return  TAF_APS_FAIL;
        }
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ProtocolId)
    {
        pApsTft->OP_ProtocolId              = VOS_TRUE;
        pApsTft->ucProtocolId               = pTafPdp->astTftTab.ucProtocolId;
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ulSecuParaIndex)
    {
        pApsTft->OP_ulSecuParaIndex         = VOS_TRUE;
        pApsTft->ulSecuParaIndex            = pTafPdp->astTftTab[0].ulSecuParaIndex; /*SPI*/
    }

    if ( VOS_TRUE  == pTafPdp->astTftTab[0].OP_ucTypeOfService)
    {
        pApsTft->OP_ucTypeOfService         = VOS_TRUE;
        pApsTft->ucTypeOfService            = pTafPdp->astTftTab[0].ucTypeOfService;  /*TOS*/
        pApsTft->ucTypeOfServiceMask        = pTafPdp->astTftTab[0].ucTypeOfServiceMask;    /*TOS Mask*/
    }
#endif
    return  TAF_APS_SUCC;
}


/*****************************************************************************
 Prototype      : Aps_PackApsActReqPara
 Description    : ���첢�������Aps_PdpActReq()��Ҫ���������;��ӦV100R001�е�
                  Taf_FillApsPdp(),�����޸�.
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  : PDPȫ�����ݱ�g_TafCidTab[TAF_MAX_CID + 1];
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  Aps_MakeAnsActReq (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                 *pApsActReq
)
{
    TAF_PDP_TABLE_STRU                 *pTafPdp;

    pTafPdp                         = &g_TafCidTab[ucCid];


    pApsActReq->OP_APN              = VOS_FALSE;
    pApsActReq->OP_AUTH             = VOS_FALSE;
    pApsActReq->OP_DNS              = VOS_FALSE;
    pApsActReq->OP_NBNS             = VOS_FALSE;
    pApsActReq->OP_Sapi             = VOS_FALSE;
    pApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pApsActReq->OP_SPARE            = VOS_FALSE;

    pApsActReq->ucPdpId             = ucPdpId;

    /*SAPI*/
    pApsActReq->OP_Sapi             = VOS_TRUE;
    pApsActReq->ucSapi              = APS_SAPI_INIT;

    /*V100ר��*/
    if ( TAF_PDP_ACTIVATE_AUTH == pTafPdp->ucAuthFlag)
    {   /*��Ȩ*/

        pApsActReq->OP_AUTH          = VOS_TRUE;
        pApsActReq->PdpAuth.AuthType = TAF_PCO_AUTH_PAP;

        if (pTafPdp->AuthTab.aucUserName[0] > TAF_MAX_USERNAME_LEN)
        {
            pTafPdp->AuthTab.aucUserName[0] = TAF_MAX_USERNAME_LEN;
            APS_WARN_LOG("Aps_PackApsActReqPara:Len of UserName is over 99 bytes.\r");
        }

        if (pTafPdp->AuthTab.aucPassword[0] > TAF_MAX_PASSCODE_LEN)
        {
            pTafPdp->AuthTab.aucPassword[0] = TAF_MAX_PASSCODE_LEN;
            APS_WARN_LOG("Aps_PackApsActReqPara:Len of Password is over 99 bytes.\r");
        }
        PS_MEM_CPY(   pApsActReq->PdpAuth.AuthContent.stPap.aucUserName,
                      pTafPdp->AuthTab.aucUserName,
                      pTafPdp->AuthTab.aucUserName[0] + 1);

        PS_MEM_CPY(   pApsActReq->PdpAuth.AuthContent.stPap.aucPassword,
                      pTafPdp->AuthTab.aucPassword,
                      pTafPdp->AuthTab.aucPassword[0] + 1);
    }
    else
    {
        /*����Ȩ*/
        pApsActReq->PdpAuth.AuthType    = TAF_PCO_NOT_AUTH;
        PS_MEM_SET(&pApsActReq->PdpAuth.AuthContent, 0, sizeof(pApsActReq->PdpAuth.AuthContent));
    }

    /*���缤��ʱ������Я���ĵ�ַ���ͺ͵�ַ����Ϊ׼*/
    pApsActReq->ucPdpType    = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;
    pApsActReq->aucIpAddr[0] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0];
    pApsActReq->aucIpAddr[1] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1];
    pApsActReq->aucIpAddr[2] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2];
    pApsActReq->aucIpAddr[3] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3];

    /*�����緢����APN,���缤��ʱ������Я����APN����Ϊ׼*/
    if ((VOS_TRUE == g_PdpEntity[ucPdpId].PdpApnFlag)
     && (0 != g_PdpEntity[ucPdpId].PdpApn.ucLength))
    {
        pApsActReq->OP_APN          = VOS_TRUE;
        if (g_PdpEntity[ucPdpId].PdpApn.ucLength > TAF_MAX_APN_LEN)
        {
            g_PdpEntity[ucPdpId].PdpApn.ucLength = TAF_MAX_APN_LEN;
        }
        pApsActReq->aucApn[0] = g_PdpEntity[ucPdpId].PdpApn.ucLength;
        PS_MEM_CPY(                 &pApsActReq->aucApn[1],
                                    g_PdpEntity[ucPdpId].PdpApn.aucValue,
                                    pApsActReq->aucApn[0]);
    }
    else
    {
        /*������PDP���ݱ��е�����Ϊ׼*/
        if (VOS_TRUE == pTafPdp->ucUsed)
        {
            /*����aucApn*/
            Taf_LenStr2Apn(&(pTafPdp->CidTab.stApn), pApsActReq->aucApn);
            if ( 0 != pApsActReq->aucApn[0])
            {
                pApsActReq->OP_APN      = VOS_TRUE;
            }
        }
    }

    /*����Qos*/
    if (pTafPdp->ucQosTabFlag)
    {
        Taf_FillQos(pTafPdp, &pApsActReq->ReqQos);
    }
    else
    {   /*û�ж���QOS�������������*/
        Taf_FillQos(&g_TafCidTab[0], &pApsActReq->ReqQos);
    }

    /*����XID*/
    Aps_FillXid(pTafPdp, pApsActReq);

    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct = APS_APP_MANUL_ACT;

    /*�����ϣ�ֱ�ӷ��سɹ�*/
    return ;

}

/*****************************************************************************
 Prototype      : Aps_FillXid
 Description    : ���APS_PDP_ACT_REQ_ST�ͱ���ʱ����ñ��������XID����ʱʹ�á�
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillXid(        TAF_PDP_TABLE_STRU         *pTafPdp,
                                APS_PDP_ACT_REQ_ST         *pApsActReq  )
{

    pApsActReq->Op_Xid_DCmp             = VOS_FALSE;
    pApsActReq->Op_Xid_PCmp             = VOS_FALSE;

    switch(pTafPdp->CidTab.enPdpDcomp)
    {
        case    TAF_PDP_D_COMP_OFF  :
            break;

        case    TAF_PDP_D_COMP_ON   :
            pApsActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        case    TAF_PDP_D_COMP_V42  :
            pApsActReq->Op_Xid_DCmp     = VOS_TRUE;
            pApsActReq->ucDCmprAlgrth   = SN_V42_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpDcomp ERR !");
            break;
    }


    switch(pTafPdp->CidTab.enPdpHcomp)
    {
        case    TAF_PDP_H_COMP_OFF  :
            break;

        case    TAF_PDP_H_COMP_ON   :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC1144  :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_1144_ALGRTH;
            break;

        case    TAF_PDP_H_COMP_RFC2507  :
            pApsActReq->Op_Xid_PCmp     = VOS_TRUE;
            pApsActReq->ucPCmprAlgrth   = SN_2507_ALGRTH;
            break;

        default    :
            APS_WARN_LOG("PdpHcomp ERR !");
            break;
    }

    return;

}


/*****************************************************************************
 Prototype      : Aps_FillDns
 Description    : ���APS_PDP_ACT_REQ_ST�ͱ���ʱ����ñ��������DNS����ʱʹ�á�
 Input          : ucCid
                  ucPdpId
 Output         : pApsActReq
 Return Value   :
 Data Accessed  :
 Data Updated   :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_FillDns(                TAF_PDP_TABLE_STRU *pTafPdp,
                                        APS_PDP_ACT_REQ_ST *pApsActReq  )
{
    if (pTafPdp->ucDnsFlag)
    {
        pApsActReq->OP_DNS              = VOS_TRUE;
        pApsActReq->PdpDns              = pTafPdp->DnsTab;
    }
    else
    {
        pApsActReq->OP_DNS              = VOS_FALSE;
        pApsActReq->PdpDns.bitOpPrimDnsAddr    = VOS_FALSE;
        pApsActReq->PdpDns.bitOpSecDnsAddr    = VOS_FALSE;
    }

    return;
}


VOS_UINT32 Aps_PackApsMdfReqPara (
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucPdpId,
    APS_PDP_MDF_REQ_ST                 *pApsMdfReq
)
{
    VOS_UINT32                          ulReturn;

    ulReturn                        = TAF_APS_SUCC;

    pApsMdfReq->Op_Qos              = TAF_FREE;
    pApsMdfReq->Op_Tft              = TAF_FREE;

    pApsMdfReq->Tft.OP_SourcePort          = TAF_FREE;
    pApsMdfReq->Tft.OP_DestPort            = TAF_FREE;
    pApsMdfReq->Tft.OP_SourceIpAddrAndMask = TAF_FREE;
    pApsMdfReq->Tft.OP_ProtocolId          = TAF_FREE;
    pApsMdfReq->Tft.OP_ulSecuParaIndex     = TAF_FREE;
    pApsMdfReq->Tft.OP_ucTypeOfService     = TAF_FREE;
    pApsMdfReq->Tft.OP_Spare               = TAF_FREE;

    pApsMdfReq->OP_Sapi              = TAF_FREE;
    pApsMdfReq->Op_Spare             = TAF_FREE;


    pApsMdfReq->ucPdpId             = ucPdpId;

    /*fill SAPI*/
    pApsMdfReq->OP_Sapi             = VOS_TRUE;
    pApsMdfReq->ucSapi              = APS_SAPI_INIT;

    /*fill Qos*/
    if ( TAF_USED == g_TafCidTab[ucCid].ucQosTabFlag)
    {
        pApsMdfReq->Op_Qos          = VOS_TRUE;
        Taf_FillQos(&g_TafCidTab[ucCid], &pApsMdfReq->Qos);
    }

    /*fill Tft*/
    if ( TAF_USED == g_TafCidTab[ucCid].ucPfTabFlag)
    {
        pApsMdfReq->Op_Tft          = VOS_TRUE;
        ulReturn = Aps_FillTft(     &g_TafCidTab[ucCid],
                                    &pApsMdfReq->Tft);
        if ( TAF_APS_FAIL == ulReturn )
        {
            APS_WARN_LOG("Aps_FillTft ERR");
            return TAF_APS_FAIL;
        }
    }

    return  TAF_APS_SUCC;
}
VOS_VOID Aps_PsCallModify(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
)
{
    VOS_UINT8                           ucCid;
    VOS_UINT32                          ulResult;
    APS_PDP_MDF_REQ_ST                  ApsMdfReq;

    ulResult                            = TAF_APS_SUCC;
    ucCid                               = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ��ʼ�� */
    *pucError       = TAF_ERR_NO_ERROR;
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* clean coverity by w00316404 for clean coverity, 2015-06-26, begin */
    PS_MEM_SET(&ApsMdfReq, 0x00, sizeof(ApsMdfReq));
    /* clean coverity by w00316404 for clean coverity, 2015-06-26, end */

    ulResult        = Aps_PackApsMdfReqPara(ucCid, ucPdpId, &ApsMdfReq);
    if (TAF_APS_FAIL == ulResult)
    {
       *pucError    = TAF_ERR_UNSPECIFIED_ERROR;
    }
    else
    {
        ulResult    = Aps_PdpMdfReq(&ApsMdfReq);
        if (TAF_APS_FAIL == ulResult)
        {
            APS_WARN_LOG("Aps_PdpMdfReq err ");
            *pucError = TAF_ERR_UNSPECIFIED_ERROR;
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_PsCallEnd()
 Description    : PDPȥ����.�ú�������API����Ĳ��������ò��������Aps_PdpDeActReq()
                  ����Ҫ��Ľӿڲ���,Ȼ����ú���Aps_PdpDeActReq();
 Input          : SM_TAF_CAUSE_ENUM_UINT16            enCause,
                  VOS_UINT8                           ucPdpId,
                  VOS_UINT8                          *pucError
 Output         : pucError
 Return Value   :
 Calls          : Aps_AppDeactReq()
                  TAF_APS_SndCidInactiveEvt
 Called By      : TAFM
 History        : ---
  1.Date        : 2005-
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID Aps_PsCallEnd(
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucError
)
{
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    ulResult                            = VOS_OK;
    *pucError                           = TAF_ERR_NO_ERROR;

    /* ����PDPȥ����, ���ݷ���ֵ��д������ */
    ulResult    = Aps_AppDeactReq(ucPdpId, enCause);
    if (VOS_OK != ulResult)
    {
        *pucError   = TAF_ERR_ERROR;
    }

    return;
}


VOS_VOID    TAF_APS_SndCidInactiveEvt(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid )
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU  stCidDeActCnfEvt;

    PS_MEM_SET(&stCidDeActCnfEvt, 0, sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    stCidDeActCnfEvt.stCtrl = *pstCtrl;
    stCidDeActCnfEvt.ucCid  = ucCid;

    /*����TAFM�ṩ���¼��ϱ����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
                     &stCidDeActCnfEvt,
                     sizeof(TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU));

    APS_NORM_LOG("APS->APP ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF");
    return;
}
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid)
{
    VOS_UINT8                   ucPdpId;
    VOS_UINT8                   ucCid;
    TAF_APS_STA_ENUM_UINT32     enState;
    VOS_UINT8                   ucloop;
    VOS_UINT8                   ucValid;

    ucValid = VOS_FALSE;

    /* ������AT�Ĳ��ţ�CID��ȡ��[12, 20]�����ȡ; ������IMSA�Ĵ�[20->12]�����ȡ */
    for (ucloop = 0; ucloop <= (APS_PDP_MAX_CID - APS_PDP_RESELECT_CID); ucloop++)
    {
#if (FEATURE_IMS == FEATURE_ON)
        if (PS_PID_IMSA == ulAppPid)
        {
            ucCid = APS_PDP_MAX_CID - ucloop;
        }
        else
#endif
        {
            ucCid = APS_PDP_RESELECT_CID + ucloop;
        }

        /* �������е�PDPʵ��, ����Ƿ��з�IDLE̬��PDP����ʹ�ø�CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState) )
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            ucValid = VOS_TRUE;
            break;
        }
    }

    /* ���CID�Ƿ���Ч */
    if (VOS_TRUE != ucValid)
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}
#else
VOS_UINT8 TAF_APS_FindCidForDial(VOS_UINT32  ulAppPid)
{
    VOS_UINT8                   ucPdpId;
    VOS_UINT8                   ucCid;
    TAF_APS_STA_ENUM_UINT32     enState;
    VOS_UINT8                   ucValid;

    ucValid = VOS_FALSE;

    /* ��ȡcid */
    for (ucCid = TAF_MAX_CID; ucCid >= 1; ucCid--)
    {
        /* �������е�PDPʵ��, ����Ƿ��з�IDLE̬��PDP����ʹ�ø�CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState) )
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            ucValid = VOS_TRUE;
            break;
        }
    }

    /* ���CID�Ƿ���Ч */
    if (VOS_TRUE != ucValid)
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}
#endif /* (FEATURE_ON == FEATURE_LTE) */

VOS_UINT32 MN_APS_SetPdpContext(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                          ulResult;

    ulResult                            = VOS_OK;

    if ( (VOS_NULL_PTR == pstPdpPrimContextExt)
      || (!TAF_PS_CID_VALID(pstPdpPrimContextExt->ucCid)) )
    {
        APS_WARN_LOG("Aps_DefPsPdpContext input para err!");
        return VOS_ERR;
    }

    /*����Ӧ������ʱ���浽��ʱ����g_TmpPdpTab��*/
    g_TmpPdpTab = g_TafCidTab[pstPdpPrimContextExt->ucCid];

    /*����pPara�ж��Ƿ���ɾ��PDP_PRI����*/
    if (APS_PDPPRI_DELETE(pstPdpPrimContextExt))
    {
        /*ɾ��PDP_PRI����*/

        /*�����ն˵�Ҫ�������ָ��ɾ����CID������APS_PDP_INACTIVE״̬��
          ���ֹ��ɾ������*/
        if (VOS_TRUE == Taf_CheckActCid(pstPdpPrimContextExt->ucCid))
        {
            MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: Can't delete the Context of \
                         the CID which is not in APS_PDP_INACTIVE state!");
            return VOS_ERR;
        }

        /*��������PDP_PRI���������Ѿ�����*/
        if (VOS_TRUE == g_TmpPdpTab.ucUsed)
        {
            /*���PDP�Ķ����ʶ*/
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucUsed        = VOS_FALSE;

            /*��PDP�����Ƕ���PDP���������PDP����PDP��ʶ*/
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag  = VOS_FALSE;
        }
        else
        {
            /*��������û�ж���,��ֱ���ϱ�ɾ���ɹ�*/
            return VOS_OK;
        }
    }
    else
    {
        /*��������޸�PDP_PRI����*/
        ulResult = Aps_ChngPdpPri(pstPdpPrimContextExt, pstPdpPrimContextExt->ucCid);
        if (VOS_ERR == ulResult)
        {
            /*����޸�ʧ��*/
            MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: Aps_ChngPdpPri ERR!");
            g_TafCidTab[pstPdpPrimContextExt->ucCid] = g_TmpPdpTab;

            return VOS_ERR;
        }

        /*���ԭ���Ƕ���PDP������б�ʶ�����ͱ�Ҫ����������*/
        if (VOS_TRUE == g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag)
        {
            g_TafCidTab[pstPdpPrimContextExt->ucCid].ucPriCidFlag  = VOS_FALSE;
        }

        /*AT��APP����PdpPri����ʱ,����û������Ĳ������ô˺�������ȱʡ���塣*/
        Aps_DefPdpPri(pstPdpPrimContextExt, pstPdpPrimContextExt->ucCid);
    }

    ulResult = Aps_NvimAct(pstPdpPrimContextExt->ucCid);
    if (VOS_OK != ulResult)
    {
        /*����NVIMʧ�ܣ��ָ�ԭֵ*/
        MN_WARN_LOG("MN_APS_SetPdpContext: WARNING: NVIM ACT ERR!");
        g_TafCidTab[pstPdpPrimContextExt->ucCid] = g_TmpPdpTab;

        return VOS_ERR;
    }
    return VOS_OK;
}
VOS_UINT32 MN_APS_SetPdpCidPara(
    VOS_UINT16                          usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stPdpPrimContextExt, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /*�������*/
    if (VOS_NULL == pstPdpPrimContextExt)
    {
        MN_ERR_LOG("MN_APS_SetPdpCidPara:the point pstPdpPrimContextExt is null");
        return VOS_ERR;
    }

    stPdpPrimContextExt = *pstPdpPrimContextExt;


    /* PDP�����������Դ򿪣���ͣ���ʱ���������� */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
    {
        TAF_APS_RcvSetCidPara_PdpActLimit(&stPdpPrimContextExt);
    }


    ulResult = MN_APS_SetPdpContext(usClientId, 0, &stPdpPrimContextExt);

    return ulResult;
}


VOS_UINT32 MN_APS_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpCidInfo,
    VOS_UINT8                           ucCid
)
{
    TAF_PDP_TABLE_STRU                 *pstTafCidInfo;

    pstTafCidInfo = TAF_APS_GetTafCidInfoAddr(ucCid);

    if ((0 == ucCid) || (ucCid > TAF_MAX_CID))
    {
        MN_ERR_LOG("MN_APS_GetPdpCidPara: CID is invalid.");
        return VOS_ERR;
    }

    if (VOS_TRUE != pstTafCidInfo->ucUsed)
    {
        MN_ERR_LOG("MN_APS_GetPdpCidPara: CID tab is not defined.");
        PS_MEM_SET(pstPdpCidInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    }
    else
    {
        *pstPdpCidInfo = pstTafCidInfo->CidTab;
    }

    return VOS_OK;
}


TAF_PDP_TYPE_ENUM_UINT8 Taf_GetCidType(VOS_UINT8 ucCid)
{
    if ( ucCid > TAF_MAX_CID )
    {
        return  TAF_PDP_TYPE_BUTT;
    }

    if ( 0 == ucCid )
    {
        return  TAF_PDP_IPV4;
    }

    if (VOS_TRUE != g_TafCidTab[ucCid].ucUsed)
    {
        /*û�ж���*/
        return  TAF_PDP_TYPE_BUTT;
    }
    else
    {
        switch(g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType)
        {
            case TAF_PDP_PPP:
            case TAF_PDP_IPV4:
#if (FEATURE_ON == FEATURE_IPV6)
            case TAF_PDP_IPV6:
            case TAF_PDP_IPV4V6:
#endif
                return  g_TafCidTab[ucCid].CidTab.stPdpAddr.enPdpType;

            default:
                return TAF_PDP_TYPE_BUTT;
        }
    }
}
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, end */
/*****************************************************************************
 Prototype      : Taf_PsCallForDialParaCheck
 Description    :
 Input          : pPsDialPara
 Output         :
 Return Value   : TAF_PS_PARA_VALID��TAF_PS_PARA_INVALID
 Date Accessed  :
 Date Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT8   Taf_PsCallForDialParaCheck( PPP_REQ_CONFIG_INFO_STRU *pPsDialPara)
{
    if (TAF_NULL_PTR == pPsDialPara)
    {
        APS_NORM_LOG(" pPsDialPara is null !");
        return  TAF_PS_PARA_INVALID;
    }

    /*�����֤���ĵĺϷ���*/
    if ( PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( (0 != pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.PapContent.pPapReq) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.PapContent.pPapReq is null !");
            return  TAF_PS_PARA_INVALID;
        }
    }
    else if ( PPP_CHAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( (0 != pPsDialPara->stAuth.AuthContent.ChapContent.usChapChallengeLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.ChapContent.pChapChallenge is null !");
            return  TAF_PS_PARA_INVALID;
        }

        if ( (0 != pPsDialPara->stAuth.AuthContent.ChapContent.usChapResponseLen)
              && (TAF_NULL_PTR == pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse) )
        {
            APS_NORM_LOG(" pPsDialPara->stAuth.AuthContent.ChapContent.pChapResponse is null !");
            return  TAF_PS_PARA_INVALID;
        }
    }
    else if ( PPP_NO_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        /*����Ȩ*/
    }
    else
    {
        APS_NORM_LOG(" pPsDialPara->stAuth.ucAuthType is abnormal!");
        return  TAF_PS_PARA_INVALID;
    }

    /*���IPCP���ĵĺϷ���*/
    if ( (0 != pPsDialPara->stIPCP.usIpcpLen ) && (TAF_NULL_PTR == pPsDialPara->stIPCP.pIpcp) )
    {
        APS_NORM_LOG(" pPsDialPara->stIPCP.pIpcp is null!");
        return  TAF_PS_PARA_INVALID;
    }


    if ( PPP_PAP_AUTH_TYPE == pPsDialPara->stAuth.ucAuthType )
    {
        if ( pPsDialPara->stAuth.AuthContent.PapContent.usPapReqLen
             > ( TAF_MAX_USERNAME_LEN + TAF_MAX_PASSCODE_LEN + TAF_PPP_HEADER_LEN) )
        {
            APS_NORM_LOG(" usPapReqLen is too long !");
            return  TAF_PS_PARA_INVALID;
        }
    }

    if( pPsDialPara->stIPCP.usIpcpLen > TAF_PPP_IPCP_MAX_LEN )
    {
        APS_NORM_LOG(" IPCP Lenth is too long!");
        return  TAF_PS_PARA_INVALID;
    }

    return  TAF_PS_PARA_VALID;
}

#if(FEATURE_ON == FEATURE_LTE)
VOS_VOID  TAF_APS_SndGetLtecsInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_LTECS_CNF_STRU           stGetLtecsInfoCnf;

    stGetLtecsInfoCnf.stCtrl        = *pstCtrl;
    stGetLtecsInfoCnf.enCause       = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_LTECS_INFO_CNF,
                               &stGetLtecsInfoCnf,
                               sizeof(TAF_PS_LTECS_CNF_STRU));

    return;
}


VOS_VOID  TAF_APS_SndGetCemodeInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_CEMODE_CNF_STRU              stGetCemodeInfoCnf;

    stGetCemodeInfoCnf.stCtrl           = *pstCtrl;
    stGetCemodeInfoCnf.enCause          = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CEMODE_INFO_CNF,
                                &stGetCemodeInfoCnf,
                                sizeof(TAF_PS_CEMODE_CNF_STRU));

    return;
}

VOS_VOID  TAF_APS_SndSetPdprofInfoCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    TAF_PS_SET_PDP_PROF_INFO_CNF_STRU   stSetPdprofInfoCnf;

    stSetPdprofInfoCnf.stCtrl   = *pstCtrl;
    stSetPdprofInfoCnf.enCause  = ulErrCode;

    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_PDP_PROF_INFO_CNF,
                                &stSetPdprofInfoCnf,
                                sizeof(TAF_PS_SET_PDP_PROF_INFO_CNF_STRU));

    return;
}
#endif




VOS_UINT32 TAF_APS_IsApnChanged(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulOpApn,
    VOS_UINT8                          *pucApn
)
{
    VOS_UINT8                           aucNewApn[TAF_MAX_APN_LEN + 1];
    VOS_UINT8                           ucApnChangeFlg;

    ucApnChangeFlg = VOS_FALSE;

    /* ������޸�APN */
    if (VOS_TRUE == ulOpApn)
    {
        /* û�ж���ɵ�APN*/
        if (VOS_FALSE == g_TafCidTab[ucCid].ucUsed)
        {
            ucApnChangeFlg = VOS_TRUE;
        }
        else
        {
            /* ��ȡ�µ�APN */
            Aps_Str2LenStr(TAF_MAX_APN_LEN, pucApn, aucNewApn);


            /* �Ƚ�APN�ĳ����Ƿ�ı䣬��һ���ֽڱ�ʾ���� */
            if (aucNewApn[0] != TAF_APS_GetTafCidInfoApnLen(ucCid))
            {
                ucApnChangeFlg = VOS_TRUE;
            }
            else
            {
                /* �Ƚ�APN�����Ƿ�ı� */
                if (PS_MEM_CMP(TAF_APS_GetTafCidInfoApnData(ucCid), &aucNewApn[1], aucNewApn[0]))
                {
                    ucApnChangeFlg = VOS_TRUE;
                }
            }
        }
    }
    /* ɾ��APN */
    else
    {
        /* ���ڶ���ɵ�APN*/
        if ((VOS_TRUE == g_TafCidTab[ucCid].ucUsed)
         && (0 != TAF_APS_GetTafCidInfoApnLen(ucCid)))
        {
            ucApnChangeFlg = VOS_TRUE;
        }
    }

    return ucApnChangeFlg;
}
VOS_VOID TAF_APS_RcvSetCidPara_PdpActLimit(
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                          ulApnChangeFlg;

    ulApnChangeFlg = TAF_APS_IsApnChanged(pstPdpPrimContextExt->ucCid,
                                          pstPdpPrimContextExt->bitOpApn,
                                          pstPdpPrimContextExt->aucApn);

    if (VOS_TRUE == ulApnChangeFlg)
    {
        /* APN�ı䣬ֹͣ��ͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
    }

    return ;
}
VOS_VOID TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU    *pstSetPdpCtxInfoReq
)
{
    VOS_UINT32                          ulApnChangeFlg;

    ulApnChangeFlg = TAF_APS_IsApnChanged(pstSetPdpCtxInfoReq->stPdpContextInfo.ucCid,
                                          pstSetPdpCtxInfoReq->stPdpContextInfo.ucDefined,
                                          pstSetPdpCtxInfoReq->stPdpContextInfo.aucApn);

    if (VOS_TRUE == ulApnChangeFlg)
    {
        /* APN�ı䣬ֹͣ��ͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
    }

    return ;
}


/* Deleted by wx270776 for OM�ں�, 2015-7-24, begin */

/* Deleted by wx270776 for OM�ں�, 2015-7-24, end */

VOS_VOID TAF_APS_SndDsFlowOMRptInd(
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-10, begin */
    NAS_OM_DSFLOW_RPT_IND_STRU          stDsflowRptInd;
    DIAG_TRANS_IND_STRU                 stSendOMDsFlowRptInd;
    VOS_UINT32                          ulRet;


    /* ��ʼ�� */
    PS_MEM_SET(&stSendOMDsFlowRptInd, 0, sizeof(DIAG_TRANS_IND_STRU));

    PS_MEM_SET(&stDsflowRptInd, 0, sizeof(NAS_OM_DSFLOW_RPT_IND_STRU));

    stDsflowRptInd.usPrimId             = ID_NAS_OM_DSFLOW_RPT_IND;
    stDsflowRptInd.usToolsId            = 0;
    stDsflowRptInd.ulCurrentSendRate    = pstDsFlowRptInfo->ulCurrentSendRate;
    stDsflowRptInd.ulCurrentReceiveRate = pstDsFlowRptInfo->ulCurrentReceiveRate;
    stDsflowRptInd.ulDSLinkTime         = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime;
    stDsflowRptInd.ulDSSendFluxLow      = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow;
    stDsflowRptInd.ulDSSendFluxHigh     = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh;
    stDsflowRptInd.ulDSReceiveFluxLow   = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow;
    stDsflowRptInd.ulDSReceiveFluxHigh  = pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh;

    /* ��д��Ϣ�ṹ */
    stSendOMDsFlowRptInd.ulModule     = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_TAF), DIAG_MODE_UMTS);
    stSendOMDsFlowRptInd.ulPid        = WUEPS_PID_TAF;
    stSendOMDsFlowRptInd.ulMsgId      = ID_NAS_OM_DSFLOW_RPT_IND;
    stSendOMDsFlowRptInd.ulLength     = sizeof(NAS_OM_DSFLOW_RPT_IND_STRU);
    stSendOMDsFlowRptInd.pData        = &stDsflowRptInd;

    /* ������Ϣ */
    ulRet = DIAG_TransReport(&stSendOMDsFlowRptInd);
    if (VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_SndDsFlowOMRptInd: DIAG_TransReport Failed!");
    }

    return;
}


VOS_UINT8 TAF_APS_FindCidForAns(VOS_VOID)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_APS_STA_ENUM_UINT32             enState;

    /* CID��ȡ��LTE֧��ʱ, ��[21, 31]�����ȡ; �����[31, 21]�����ȡ */
#if(FEATURE_ON == FEATURE_LTE)
    for (ucCid = APS_PDP_MAX_CID + 1; ucCid <= TAF_MAX_CID; ucCid++)
#else
    for (ucCid = TAF_MAX_CID; ucCid >= APS_PDP_MIN_CID; ucCid--)
#endif
    {
        /* �������е�PDPʵ��, ����Ƿ��з�IDLE̬��PDP����ʹ�ø�CID */
        for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
        {
            enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

            if ((VOS_TRUE == TAF_APS_IsPdpEntBitCidMaskExit(ucPdpId, ucCid))
             && (TAF_APS_STA_INACTIVE != enState))
            {
                break;
            }
        }

        if (ucPdpId >= TAF_APS_MAX_PDPID)
        {
            break;
        }
    }

    /* ���CID�Ƿ���Ч */
#if(FEATURE_ON == FEATURE_LTE)
    if (ucCid > TAF_MAX_CID)
#else
    if (ucCid < APS_PDP_MIN_CID)
#endif
    {
        ucCid = TAF_INVALID_CID;
    }

    return ucCid;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetIpTypeAnsExtIpcpPara
 ��������  : ����Ӧ��IP��������PDP����ļ�������IPCP����
 �������  : APS_PDP_ACT_REQ_ST                 *pstApsActReq
             TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��9��
    ��    ��   : #
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_GetIpTypeAnsExtIpcpPara(
    APS_PDP_ACT_REQ_ST                 *pstApsActReq,
    TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
)
{
    /*����PdpDns*/
    if (APS_ADDR_PPP != pstApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pstApsDialReqPara->OP_Dns)
        {
            /*���������DNS,��ʹ�������DNS*/
            pstApsActReq->OP_DNS          = VOS_TRUE;
            pstApsActReq->PdpDns          = pstApsDialReqPara->Dns;
        }
    }

    /*����PdpNbns*/
    if (APS_ADDR_PPP != pstApsActReq->ucPdpType)
    {
        if (VOS_TRUE == pstApsDialReqPara->OP_Nbns)
        {
            /*���������NBNS,��ʹ�������NBNS*/
            pstApsActReq->OP_NBNS          = VOS_TRUE;
            pstApsActReq->PdpNbns          = pstApsDialReqPara->Nbns;
        }
    }

    return;
}


VOS_VOID TAF_APS_GetIpTypeAnsExtAuthPara(
    APS_PDP_ACT_REQ_ST                 *pstApsActReq,
    TAF_PSCALL_FOR_DIAL_EXT_STRU         *pstApsDialReqPara
)
{
    /* ����ucUserAuthOrNot,aucUserName,aucPassword */
    if ((VOS_TRUE == pstApsDialReqPara->OP_Auth )
     && (APS_ADDR_PPP != pstApsActReq->ucPdpType))
    {
        /* �������˼�Ȩ��Ϣ,��ʹ������ļ�Ȩ��Ϣ */
        pstApsActReq->OP_AUTH = VOS_TRUE;
        Aps_CopyAuthToActReqPara(&(pstApsDialReqPara->AuthPara),
                                 &(pstApsActReq->PdpAuth));
    }

    return;
}


VOS_VOID TAF_APS_MakeIpTypeAnsExtActReq(
    VOS_UINT8                           ucPdpId,
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq,
    APS_PDP_ACT_REQ_ST                 *pstApsActReq
)
{
    PPP_REQ_CONFIG_INFO_STRU            stPppConfigInfo;
    TAF_PSCALL_FOR_DIAL_EXT_STRU        stApsDialReqPara;

    PS_MEM_SET(&stApsDialReqPara, 0x00, sizeof(TAF_PSCALL_FOR_DIAL_EXT_STRU));

    pstApsActReq->OP_APN              = VOS_FALSE;
    pstApsActReq->OP_AUTH             = VOS_FALSE;
    pstApsActReq->OP_DNS              = VOS_FALSE;
    pstApsActReq->OP_NBNS             = VOS_FALSE;
    pstApsActReq->OP_Sapi             = VOS_FALSE;
    pstApsActReq->Op_Xid_DCmp         = VOS_FALSE;
    pstApsActReq->Op_Xid_PCmp         = VOS_FALSE;
    pstApsActReq->OP_SPARE            = VOS_FALSE;

    pstApsActReq->ucPdpId             = ucPdpId;

    /* SAPI */
    pstApsActReq->OP_Sapi             = VOS_TRUE;
    pstApsActReq->ucSapi              = APS_SAPI_INIT;

    /* Ĭ�ϲ���Ȩ */
    pstApsActReq->PdpAuth.AuthType    = TAF_PCO_NOT_AUTH;

    /* ���缤��ʱ������Я���ĵ�ַ���ͺ͵�ַ����Ϊ׼ */
    pstApsActReq->ucPdpType    = g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum;
    pstApsActReq->aucIpAddr[0] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[0];
    pstApsActReq->aucIpAddr[1] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[1];
    pstApsActReq->aucIpAddr[2] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[2];
    pstApsActReq->aucIpAddr[3] = g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr[3];

    /* ���缤��ʱ������Я����APN����Ϊ׼ */
    if ((VOS_TRUE == g_PdpEntity[ucPdpId].PdpApnFlag)
     && (0 != g_PdpEntity[ucPdpId].PdpApn.ucLength))
    {
        pstApsActReq->OP_APN = VOS_TRUE;

        if (g_PdpEntity[ucPdpId].PdpApn.ucLength > TAF_MAX_APN_LEN)
        {
            g_PdpEntity[ucPdpId].PdpApn.ucLength = TAF_MAX_APN_LEN;
        }

        pstApsActReq->aucApn[0] = g_PdpEntity[ucPdpId].PdpApn.ucLength;

        PS_MEM_CPY(&pstApsActReq->aucApn[1],
                   g_PdpEntity[ucPdpId].PdpApn.aucValue,
                   pstApsActReq->aucApn[0]);
    }

    /*û�ж���QOS�������������*/
    Taf_FillQos(&g_TafCidTab[0], &pstApsActReq->ReqQos);

    /* ����AUTH/IPCP */
    PS_MEM_SET(&stPppConfigInfo, 0x00, sizeof(PPP_REQ_CONFIG_INFO_STRU));

    if (VOS_OK == MN_APS_PppCovertConfigInfo(&stPppConfigInfo,
                                             &pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo))
    {
        if (TAF_PS_PARA_VALID == Taf_PsCallForDialParaCheck(&stPppConfigInfo))
        {
            /*��IPCP�������в��REQ��IPCP��Ϣ����,��� ApsDilaPara��*/
            Aps_GetIpcpInfo(&stPppConfigInfo, &stApsDialReqPara);

            TAF_APS_GetIpTypeAnsExtIpcpPara(pstApsActReq, &stApsDialReqPara);

            /*��IPCP�������в��REQ��AUTH��Ϣ����,��� ApsDilaPara��*/
            if (TAF_APS_SUCC == Aps_GetAuthInfo(&stPppConfigInfo, &stApsDialReqPara))
            {
               TAF_APS_GetIpTypeAnsExtAuthPara(pstApsActReq, &stApsDialReqPara);
            }
        }

        /* �ͷ����ɵļ�Ȩ��Ϣ */
        MN_APS_CtrlFreePCOContext(&stPppConfigInfo);
    }

    /*�����ϣ�ֱ�ӷ��سɹ�*/
    return;
}


VOS_UINT32 TAF_APS_GetPdpCidQosPara(
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara,
    VOS_UINT8                           ucCid
)
{
    TAF_UMTS_QOS_QUERY_INFO_STRU        stQosPara;
    TAF_UMTS_QOS_QUERY_INFO_STRU        stMinQosPara;
    VOS_UINT32                          ulErrCode;

    PS_MEM_SET(&stQosPara, 0, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));
    PS_MEM_SET(&stMinQosPara, 0, sizeof(TAF_UMTS_QOS_QUERY_INFO_STRU));

    /* ������Ч�Լ�� */
    if ((0 == ucCid) || (ucCid > TAF_MAX_CID))
    {
        MN_ERR_LOG("TAF_APS_GetPdpCidQosPara: CID is invalid.");
        return VOS_ERR;
    }

    /* ��ȡQOS���� */
    MN_APS_GetUtmsQosInfo(ucCid, &stQosPara, &ulErrCode);

    if (TAF_PARA_OK == ulErrCode)
    {
        pstQosPara->ucQosFlag = VOS_TRUE;
        PS_MEM_CPY(&(pstQosPara->stQos), &(stQosPara.stQosInfo), sizeof(TAF_UMTS_QOS_STRU));
    }

    MN_APS_GetUtmsQosMinInfo(ucCid, &stMinQosPara, &ulErrCode);

    if (TAF_PARA_OK == ulErrCode)
    {
        pstQosPara->ucMinQosFlag = VOS_TRUE;
        PS_MEM_CPY(&(pstQosPara->stMinQos), &(stMinQosPara.stQosInfo), sizeof(TAF_UMTS_QOS_STRU));
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_SetPdpCidQosPara(
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
)
{
    VOS_UINT32                          ulErrCode;

    ulErrCode = TAF_PARA_OK;

    Aps_DefPs3gReqQos(0, 0, &(pstQosPara->stQos), &ulErrCode);

    if (TAF_PARA_OK != ulErrCode)
    {
        return VOS_ERR;
    }

    Aps_DefPs3gMinAcceptQos(0, 0, &(pstQosPara->stMinQos), &ulErrCode);

    if (TAF_PARA_OK != ulErrCode)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID TAF_APS_SndImsaSrvccCancelNotify(
    TAF_SRVCC_CANCEL_NOTIFY_ENUM_UINT32   enNotificationIndicator
)
{
    TAF_SRVCC_CANCEL_NOTIFY_IND_STRU    stApsNotiInd;

    /* ��ʼ����Ϣ */
    PS_MEM_SET(&stApsNotiInd,
               0x00,
               sizeof(TAF_SRVCC_CANCEL_NOTIFY_IND_STRU));

    /* ��д��Ϣͷ */
    stApsNotiInd.stCtrl.ulModuleId          = PS_PID_IMSA;

    /* ��д�¼����� */
    stApsNotiInd.enNotificationIndicator    = enNotificationIndicator;

    /* �����¼� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND,
                     &stApsNotiInd,
                     sizeof(TAF_SRVCC_CANCEL_NOTIFY_IND_STRU));

    return;
}
#endif


VOS_UINT32  TAF_APS_SndSetCqosPriCnf(
    TAF_CTRL_STRU                    *pstCtrl,
    VOS_UINT32                        ulErrCode
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_SET_CQOS_PRI_CNF_STRU        stSetCqosPriCnf;

    stSetCqosPriCnf.stCtrl = *pstCtrl;
    stSetCqosPriCnf.ulRslt = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CQOS_PRI_CNF,
                                &stSetCqosPriCnf,
                                sizeof(TAF_PS_SET_CQOS_PRI_CNF_STRU));

    return ulResult;
}

/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, begin */

VOS_UINT32  TAF_APS_SndSet1xPktDataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                                              ulResult;
    TAF_PS_SET_CTA_INFO_CNF_STRU  stGetPktDataInactivityTimeLenCnf;

    stGetPktDataInactivityTimeLenCnf.stCtrl = *pstCtrl;
    stGetPktDataInactivityTimeLenCnf.ulRslt = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_CTA_INFO_CNF,
                                &stGetPktDataInactivityTimeLenCnf,
                                sizeof(stGetPktDataInactivityTimeLenCnf));

    return ulResult;
}


VOS_UINT32  TAF_APS_SndGet1xPktDataInactivityTimerLenCnf(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucTimeLen,
    VOS_UINT32                          ulErrCode
)
{
    VOS_UINT32                                              ulResult;
    TAF_PS_GET_CTA_INFO_CNF_STRU  stGet1XPktDtInactivityTimeLenCnf ;

    stGet1XPktDtInactivityTimeLenCnf.stCtrl                    = *pstCtrl;
    stGet1XPktDtInactivityTimeLenCnf.uc1XPktDtInactivityTmrLen = ucTimeLen;
    stGet1XPktDtInactivityTimeLenCnf.ulRslt                    = ulErrCode;

    ulResult = TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CTA_INFO_CNF,
                                &stGet1XPktDtInactivityTimeLenCnf,
                                sizeof(stGet1XPktDtInactivityTimeLenCnf));

    return ulResult;
}
/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, end */


/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

