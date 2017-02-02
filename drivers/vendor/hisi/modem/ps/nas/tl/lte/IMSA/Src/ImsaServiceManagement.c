/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaServiceManagement.c
  Description     : ��C�ļ�ʵ�ַ������ģ��ĳ�ʼ�����ڲ���Ϣ�Ĵ���ͷ���
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaServiceManagement.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaInterface.h"
#include "ImsaProcMsccMsg.h"
#include "ImsaCallManagement.h"
#include "ImsaProcAtMsg.h"
#include "ImsaProcSpmMsg.h"
#include "ImsaProcSmsMsg.h"
/* modify by jiqiang 2014.03.25 pclint fix error 718 begin */
#include "ImsaProcUssdMsg.h"
/* modify by jiqiang 2014.03.25 pclint fix error 718 end */
#include "ImsaImsAdaption.h"

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSASERVICEMANAGEMENT_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSASERVICEMANAGEMENT_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
IMSA_SUBSCRIPTION_INFO_LIST_STRU    g_stSubcriptionInfoList = {0};              /**< ������Ϣ�б� */

extern VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID );
extern VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID );
extern VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
);
extern VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID );
extern IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID );
extern VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID );
/*extern VOS_VOID IMSA_CMCCDeregProc();*/
extern IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
);
extern VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
);
extern VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);
extern VOS_VOID IMSA_SRV_SndConnRelReq
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
);
extern VOS_VOID IMSA_SRV_SndRegDeregReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enDeRegType,
    VOS_UINT32                          ulLocalFlag
);
extern VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
);
extern VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
);
extern VOS_VOID IMSA_SRV_SetServcieStatus
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
);
extern VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
);
extern VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID );
extern VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
);
extern VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID );
extern VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
);
extern VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
);
extern VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
);
extern VOS_UINT32 IMSA_IsImsVoiceContidionSatisfied( VOS_VOID );

extern VOS_VOID IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo
(
    IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason
);

extern VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);

extern VOS_UINT32 IMSA_SRV_IsReestablishEmcPdnConditonSatisfied( VOS_VOID );

extern VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/

VOS_VOID IMSA_CONTROL_InitConfigPara( VOS_VOID )
{
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara = VOS_NULL_PTR;

    pstImsaConfigPara = IMSA_GetConfigParaAddress();

    pstImsaConfigPara->ucGsmImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranImsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteImsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucGsmEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucUtranEmsSupportFlag        = VOS_FALSE;
    pstImsaConfigPara->ucLteEmsSupportFlag          = VOS_FALSE;
    pstImsaConfigPara->ucVoiceCallOnImsSupportFlag  = VOS_TRUE;
    pstImsaConfigPara->ucSmsOnImsSupportFlag        = VOS_TRUE;
    pstImsaConfigPara->ucNoCardEmcCallSupportFlag   = VOS_FALSE;
    pstImsaConfigPara->ucUeRelMediaPdpFLag          = VOS_FALSE;
    pstImsaConfigPara->ucImsLocDeregSigPdpRelFlag   = VOS_TRUE;
    pstImsaConfigPara->enVoiceDomain                = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomDeregFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTcallFlag        = VOS_FALSE;
    pstImsaConfigPara->stCMCCCustomReq.ucCMCCCustomTqosFlag         = VOS_FALSE;
}


VOS_VOID IMSA_CONTROL_InitNetworkInfo( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNetworkInfo = VOS_NULL_PTR;

    pstImsaNetworkInfo = IMSA_GetNetInfoAddress();

    pstImsaNetworkInfo->enImsaCampedRatType   = IMSA_CAMPED_RAT_TYPE_NULL;
    pstImsaNetworkInfo->enImsaImsVoPsStatus   = IMSA_IMS_VOPS_STATUS_BUTT;
    pstImsaNetworkInfo->enImsaEmsStatus       = IMSA_EMS_STAUTS_BUTT;
    pstImsaNetworkInfo->enImsaPsServiceStatus = IMSA_PS_SERVICE_STATUS_NO_SERVICE;
    pstImsaNetworkInfo->ucImsaRoamingFlg      = VOS_FALSE;
}



VOS_VOID IMSA_CONTROL_Init( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    IMSA_MEM_SET(   pstImsaControlManager,
                    0x0,
                    sizeof(IMSA_CONTROL_MANAGER_STRU));

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enImsaIsimStatus             = IMSA_ISIM_STATUS_ABSENT;

    /* ��ʼ��������ʱ�� */
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitConfigPara();

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitNetworkInfo();

    /* ��ʼ�������Գ���IMS����ʱ�� */
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* ��ʼ�������Գ��Խ���IMS����ʱ�� */
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_EMC_SRV;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_EMC_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_EMC;

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;
    /* lihong00150010 volte phaseiii 2014-1-27 begin */
    /* ��ʼ���ϴ���ͨע��״̬ */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* ��ʼ���ϴ���ͨATע��״̬ */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;
    /* lihong00150010 volte phaseiii 2014-1-27 end */
    return ;
}
VOS_VOID IMSA_CONTROL_ClearResource( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();
    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    /* ���ע��״̬�����������Ҫ�ϱ��ϲ�ע��״̬ */
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

    pstImsaControlManager->enImsaStatus                 = IMSA_STATUS_NULL;
    pstImsaControlManager->enIsImsSrvExist              = IMSA_SRV_CONN_STATUS_ISNOT_EXIST;
    pstImsaControlManager->enStopType                   = MSCC_IMSA_STOP_TYPE_BUTT;
    /* ֹͣ������ʱ�� */
    IMSA_StopTimer(&pstImsaControlManager->stProtectTimer);
    pstImsaControlManager->stProtectTimer.phTimer       = VOS_NULL_PTR;
    pstImsaControlManager->stProtectTimer.ucMode        = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stProtectTimer.usName        = TI_IMSA_START_OR_STOP;
    pstImsaControlManager->stProtectTimer.ulTimerLen    = TI_IMSA_START_OR_STOP_TIMER_LEN;

    /* ��ʼ��������Ϣ */
    IMSA_CONTROL_InitNetworkInfo();

    /* ֹͣ�����Գ���IMS����ʱ�� */
    IMSA_StopTimer(&pstImsaControlManager->stPeriodImsSrvTryTimer);
    pstImsaControlManager->stPeriodImsSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_SRV;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_NORMAL;

    /* ��ʼ�������Գ��Խ���IMS����ʱ�� */
    IMSA_StopTimer(&pstImsaControlManager->stPeriodImsEmcSrvTryTimer);
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.phTimer   = VOS_NULL_PTR;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.usName    = TI_IMSA_PERIOD_TRY_IMS_EMC_SRV;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.ucMode    = VOS_RELTIMER_NOLOOP;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.ulTimerLen= TI_IMSA_PERIOD_IMS_EMC_SRV_TRY_TIMER_LEN;
    pstImsaControlManager->stPeriodImsEmcSrvTryTimer.usPara    = (VOS_UINT16)IMSA_SRV_TYPE_EMC;

    pstImsaControlManager->enNrmSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;
    pstImsaControlManager->enEmcSrvStatus   = IMSA_SRV_STATUS_IDLE_DEREG;

    pstImsaControlManager->enDeregCause     = IMSA_SRV_DEREG_CAUSE_BUTT;

    IMSA_MEM_SET(   &pstImsaControlManager->stImsaIntraMsgQueue,
                    0x0,
                    sizeof(IMSA_INTRA_MSG_QUEUE_STRU));

    /* lihong00150010 volte phaseiii 2014-1-27 begin */
    /* ��ʼ���ϴ���ͨע��״̬ */
    pstSubcriptionInfoList->enLastNrmRegStatus  = IMSA_NORMAL_REG_STATUS_DEREG;

    /* ��ʼ���ϴ���ͨATע��״̬ */
    pstSubcriptionInfoList->enLastNrmAtRegStatus  = IMSA_NORMAL_AT_REG_STATUS_DEREG;
    /* lihong00150010 volte phaseiii 2014-1-27 end */

    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi = IMSA_OP_FALSE;

    IMSA_MEM_SET(&pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stImpi,\
                  0,\
                  IMSA_MAX_IMPI_LEN +1);


    pstImsaControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu = IMSA_OP_FALSE;

    IMSA_MEM_SET(&pstImsaControlManager->stImsaCommonInfo.stImsaUeId.stTImpu,\
                  0,\
                  IMSA_MAX_TIMPU_LEN+1);

    pstImsaControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = IMSA_OP_FALSE;

    IMSA_MEM_SET(&pstImsaControlManager->stImsaCommonInfo.stHomeNetDomainName,\
                  0,\
                  IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN +1);

    return ;
}
VOS_VOID IMSA_SRV_RatFormatTransform
(
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8    *penImsaRat,
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enMmaRat
)
{
    if (MSCC_IMSA_RAT_TYPE_GSM == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_GSM;
    }
    else if (MSCC_IMSA_RAT_TYPE_UTRAN == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_UTRAN;
    }
    else if (MSCC_IMSA_RAT_TYPE_LTE == enMmaRat)
    {
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_EUTRAN;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_SRV_RatFormatTransform:illegal rat type");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_RatFormatTransform_ENUM, LNAS_PARAM_INVALID);
        *penImsaRat = IMSA_CAMPED_RAT_TYPE_NULL;
    }
}


VOS_UINT32 IMSA_SRV_IsCurRatSupportIms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:GSM support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteImsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportIms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_SRV_IsCurRatSupportEms( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    if ((IMSA_CAMPED_RAT_TYPE_GSM == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucGsmEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportEms:GSM support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 1);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_UTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucUtranEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:UNTRAN support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 2);
        return IMSA_TRUE;
    }

    if ((IMSA_CAMPED_RAT_TYPE_EUTRAN == pstImsaNwInfo->enImsaCampedRatType)
        && (VOS_TRUE == pstImsaConfigPara->ucLteEmsSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsCurRatSupportIms:LTE support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsCurRatSupportEms_ENUM, 3);
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_SRV_IsNrmSrvIsimParaSatisfied( VOS_VOID )
{
    IMSA_COMMON_INFO_STRU              *pstImsaCommonInfo = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    /* �ж�USIM��״̬�Ƿ����� */
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();
    if (IMSA_PS_SIMM_INVALID == pstControlMagnaer->ucImsaUsimStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:USIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    if (IMSA_ISIM_STATUS_AVAILABLE != IMSA_GetIsimStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:ISIM not available!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    pstImsaCommonInfo = IMSA_GetCommonInfoAddress();
    if (IMSA_OP_TRUE != pstImsaCommonInfo->bitOpHomeNetDomainName)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No home network domain name!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 3);
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpImpi)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No impi!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 4);
        return IMSA_FALSE;
    }

    if (IMSA_OP_TRUE != pstImsaCommonInfo->stImsaUeId.bitOpTImpu)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvIsimParaSatisfied:No temporary IMPU!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 5);
        return IMSA_FALSE;
    }

    /*zhaochen 00308719 begin for card lock 2015-10-31*/
    if (IMSA_TRUE == pstControlMagnaer->ucIsCardLocked)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvIsimParaSatisfied_ENUM, 6);
        return IMSA_FALSE;
    }
    /*zhaochen 00308719 end for card lock 2015-10-31*/

    return IMSA_TRUE;
}
IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32 IMSA_SRV_IsNrmSrvConditonSatisfied( VOS_VOID )
{
    /* ��ǰ���뼼��֧��IMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 1);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT;
    }

    /* IMS������֧�֣��򷵻����������� */
    if ((IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
            || (VOS_FALSE == IMSA_GetUeImsVoiceCap())
            || (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap()))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:voice not support!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 2);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT;
    }

    /* PS�����״̬Ϊ�������� */
    if (IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE != IMSA_GetPsServiceStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Ps service not normal!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 3);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS;
    }


    /* ����������������£���UE����Ϊ��֧�����������µ�ע�ᣬ��ֱ���˳�������֪ͨMMA VOICE������ */
    if ((VOS_TRUE == IMSA_GetNetInfoAddress()->ucImsaRoamingFlg) &&
        (VOS_TRUE == IMSA_GetConfigParaAddress()->ucRoamingImsNotSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:Roaming and not support !");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 4);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT;
    }


    /* ��״̬Ϊ��Ч���ã���IMPI��IMPU��DOMAIN������Ч */
    if (IMSA_TRUE != IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsNrmSrvConditonSatisfied:ISIM PARA not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsNrmSrvConditonSatisfied_ENUM, 5);
        return IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT;
    }


    return IMSA_NRM_SRV_CON_SAT_STATUE_SUCC;
}
VOS_UINT32 IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();

    /* �Ƿ���HPLMN�� */
    if (VOS_TRUE == pstImsaNwInfo->ucImsaRoamingFlg)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:NOT HPLMN!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    /* ���������Ƿ���ע��ɹ� */
    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:normal service not reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    /* �����˽���������������֧�ֽ��������� */
    if ((IMSA_TRUE == IMSA_CONN_IsEmcPdpDefined())
        && (IMSA_EMS_STAUTS_SUPPORT == pstImsaNwInfo->enImsaEmsStatus))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied:defined emc pdp and nw support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied_ENUM, 3);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}
VOS_UINT32 IMSA_SRV_IsEmcSrvConditonSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;
    IMSA_CONFIG_PARA_STRU              *pstImsaConfigPara   = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();
    pstImsaConfigPara   = IMSA_GetConfigParaAddress();

    /* ��ǰ���뼼��֧��IMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 1);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* ��ǰ���뼼��֧��EMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:cur rat not support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 2);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_EMC_IMS,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* UE�Ƿ�֧������ */
    if (VOS_FALSE == IMSA_GetUeImsVoiceCap())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:ue not support voice!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 3);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* �ܷ������������´������ */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 4);
        return IMSA_TRUE;
    }

    /* �ܷ���޿������� */
    if ((IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        && (VOS_FALSE == pstImsaConfigPara->ucNoCardEmcCallSupportFlag))
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:not support anonymous emc call!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 5);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CANNOT_MAKE_NOCAR_EMC_CALL,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_FALSE;
    }

    /* �����Ƿ�֧�ֽ��������� */
    if (IMSA_EMS_STAUTS_NOT_SUPPORT == pstImsaNwInfo->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsEmcSrvConditonSatisfied:nw not support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsEmcSrvConditonSatisfied_ENUM, 6);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( IMSA_CALL_TYPE_EMC,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NW_NOT_SUPPORT_EMC_BEAR,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}


VOS_UINT32 IMSA_SRV_IsReestablishEmcPdnConditonSatisfied( VOS_VOID )
{
    IMSA_NETWORK_INFO_STRU             *pstImsaNwInfo       = VOS_NULL_PTR;

    pstImsaNwInfo       = IMSA_GetNetInfoAddress();

    /* ��ǰ���뼼��֧��IMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsReestablishEmcPdnConditonSatisfied:cur rat not support ims!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsReestablishEmcPdnConditonSatisfied_ENUM, 1);
        return IMSA_FALSE;
    }

    /* ��ǰ���뼼��֧��EMS���� */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsReestablishEmcPdnConditonSatisfied:cur rat not support Ems!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsReestablishEmcPdnConditonSatisfied_ENUM, 2);
        return IMSA_FALSE;
    }

    /* �����˽��������� */
    if (IMSA_FALSE == IMSA_CONN_IsEmcPdpDefined())
    {
        IMSA_INFO_LOG("IMSA_SRV_IsReestablishEmcPdnConditonSatisfied:not defined emc pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsReestablishEmcPdnConditonSatisfied_ENUM, 3);

        return IMSA_FALSE;
    }

    /* �����Ƿ�֧�ֽ��������� */
    if (IMSA_EMS_STAUTS_NOT_SUPPORT == pstImsaNwInfo->enImsaEmsStatus)
    {
        IMSA_INFO_LOG("IMSA_SRV_IsReestablishEmcPdnConditonSatisfied:nw not support emc bearer!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_IsReestablishEmcPdnConditonSatisfied_ENUM, 4);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}



IMSA_NORMAL_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
        /* case IMSA_SRV_STATUS_CONNING_DEREG: */
        case IMSA_SRV_STATUS_RELEASING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            return IMSA_NORMAL_REG_STATUS_DEREG;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            return IMSA_NORMAL_REG_STATUS_DEREGING;

        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONNING_REG:
            return IMSA_NORMAL_REG_STATUS_REGING;

        default:

            return IMSA_NORMAL_REG_STATUS_REG;
    }
}
IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetAtRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    switch (enSrvStatus)
    {
        case IMSA_SRV_STATUS_CONNING_REG:
        case IMSA_SRV_STATUS_CONN_REG:

            return IMSA_NORMAL_AT_REG_STATUS_REG;

        default:

            return IMSA_NORMAL_AT_REG_STATUS_DEREG;
    }
}



VOS_UINT32 IMSA_SRV_IsSrvStatusEqual
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatusTmp = IMSA_SRV_STATUS_BUTT;

    if (IMSA_SRV_TYPE_NORMAL == enSrvType)
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetNormalSrvStatus();
    }
    else
    {
        enImsaSrvStatusTmp = IMSA_SRV_GetEmcSrvStatus();
    }

    if (enImsaSrvStatus == enImsaSrvStatusTmp)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}



VOS_VOID IMSA_SRV_SndConnSetupReq
(
    VOS_UINT32                          ulReEstablishFlag,
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_CONN_SETUP_REQ_STRU           *pstConnSetupReq     = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnSetupReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnSetupReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnSetupReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    /* ���Ҫ����������ͨ���ӣ���ֹͣ�����Գ���IMS��ͨ����ʱ�� */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }
    /* ���Ҫ�������ǽ������ӣ���ֹͣ�����Գ���IMS��������ʱ�� */
    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsEmcSrvTryTimer);
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnSetupReq), 0, IMSA_GET_MSG_LENGTH(pstConnSetupReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupReq,
                                ID_IMSA_CONN_SETUP_REQ,
                                sizeof(IMSA_CONN_SETUP_REQ_STRU));

    /*��д��Ϣ����*/
    pstConnSetupReq->ulReEstablishFlag  = ulReEstablishFlag;
    pstConnSetupReq->enConnType     = enConnType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnSetupReq);
}
VOS_VOID IMSA_SRV_SndConnRelReq
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_REL_REQ_STRU             *pstConnRelReq       = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndConnRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndConnRelReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnRelReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_REL_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnRelReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndConnSetupReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndConnRelReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnRelReq), 0, IMSA_GET_MSG_LENGTH(pstConnRelReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnRelReq,
                                ID_IMSA_CONN_REL_REQ,
                                sizeof(IMSA_CONN_REL_REQ_STRU));

    /*��д��Ϣ����*/
    pstConnRelReq->enConnType       = enConnType;
    pstConnRelReq->enSipPdpType     = enSipPdpType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnRelReq);
}
VOS_VOID IMSA_SRV_SndRegRegReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enAddrType
)
{
    IMSA_REG_REG_REQ_STRU              *pstRegRegReq        = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegRegReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegRegReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRegRegReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_REG_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRegRegReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegRegReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /* �ر������Գ���IMS����ʱ�� */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
    }

    if (IMSA_REG_TYPE_EMC == enRegType)
    {
        IMSA_StopTimer(&pstControlMagnaer->stPeriodImsEmcSrvTryTimer);
    }


    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstRegRegReq), 0, IMSA_GET_MSG_LENGTH(pstRegRegReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegRegReq,
                                ID_IMSA_REG_REG_REQ,
                                sizeof(IMSA_REG_REG_REQ_STRU));

    /*��д��Ϣ����*/
    pstRegRegReq->enRegType     = enRegType;
    pstRegRegReq->enAddrType    = enAddrType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstRegRegReq);
}


VOS_VOID IMSA_SRV_SndNrmCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_NRM_CALL_SRV_STATUS_IND_STRU    *pstNrmCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstNrmCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstNrmCallSrvStatusInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstNrmCallSrvStatusInd), 0, IMSA_GET_MSG_LENGTH(pstNrmCallSrvStatusInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstNrmCallSrvStatusInd,
                                ID_IMSA_NRM_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_NRM_CALL_SRV_STATUS_IND_STRU));

    /*��д��Ϣ����*/
    pstNrmCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstNrmCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstNrmCallSrvStatusInd);
}
VOS_VOID IMSA_SRV_SndEmcCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
)
{
    IMSA_EMC_CALL_SRV_STATUS_IND_STRU     *pstEmcCallSrvStatusInd = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndEmcCallSrvStatusInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstEmcCallSrvStatusInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEmcCallSrvStatusInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndEmcCallSrvStatusInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndEmcCallSrvStatusInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstEmcCallSrvStatusInd), 0, IMSA_GET_MSG_LENGTH(pstEmcCallSrvStatusInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstEmcCallSrvStatusInd,
                                ID_IMSA_EMC_CALL_SRV_STATUS_IND,
                                sizeof(IMSA_EMC_CALL_SRV_STATUS_IND_STRU));

    /*��д��Ϣ����*/
    pstEmcCallSrvStatusInd->enCallSrvStatus = enCallSrvStatus;
    pstEmcCallSrvStatusInd->enNoSrvCause    = enNoSrvCause;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstEmcCallSrvStatusInd);
}
VOS_VOID IMSA_SRV_SndRegDeregReq
(
    IMSA_REG_TYPE_ENUM_UINT8            enDeRegType,
    VOS_UINT32                          ulLocalFlag
)
{
    IMSA_REG_DEREG_REQ_STRU            *pstRegDeregReq  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndRegDeregReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRegDeregReq = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRegDeregReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndRegRegReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndRegDeregReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstRegDeregReq), 0, IMSA_GET_MSG_LENGTH(pstRegDeregReq));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstRegDeregReq,
                                ID_IMSA_REG_DEREG_REQ,
                                sizeof(IMSA_REG_DEREG_REQ_STRU));

    /*��д��Ϣ����*/
    pstRegDeregReq->enDeRegType   = enDeRegType;
    pstRegDeregReq->ulLocalFlag   = ulLocalFlag;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstRegDeregReq);
}
VOS_VOID IMSA_SRV_SndNrmRegStatusNotify
(
    const IMSA_SUBSCRIPTION_INFO_STRU  *pstSubsciptionInfo,
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNormalRegStatus
)
{
    IMSA_NORMAL_REG_STATUS_NOTIFY_STRU     *pstNrmRegStatusNotify = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_SndNrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstNrmRegStatusNotify = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORMAL_REG_STATUS_NOTIFY_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstNrmRegStatusNotify)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SRV_SndNrmRegStatusNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SRV_SndNrmRegStatusNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstNrmRegStatusNotify), 0, IMSA_GET_MSG_LENGTH(pstNrmRegStatusNotify));

    /*��д��Ϣͷ*/
    pstNrmRegStatusNotify->ulMsgId          = ID_IMSA_NORMAL_REG_STATUS_NOTIFY;
    pstNrmRegStatusNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulSenderPid      = PS_PID_IMSA;
    pstNrmRegStatusNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNrmRegStatusNotify->ulReceiverPid    = pstSubsciptionInfo->ulPid;

    /* ��д��Ϣ���� */
    pstNrmRegStatusNotify->enNormalRegStatus= enNormalRegStatus;
    pstNrmRegStatusNotify->ulPara           = pstSubsciptionInfo->ulPara;
    pstNrmRegStatusNotify->ulSubscriptionId = pstSubsciptionInfo->ulSubscriptionId;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstNrmRegStatusNotify);
}
VOS_VOID IMSA_SRV_NrmRegStatusNotify
(
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_NrmRegStatusNotify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_NrmRegStatusNotify_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[i];
        if (IMSA_SUBCRIBE_TYPE_NORMAL_REG == pstSubcriptionInfo->enType)
        {
            IMSA_SRV_SndNrmRegStatusNotify(pstSubcriptionInfo, enNrmRegStatus);
        }
    }
}


VOS_UINT32 IMSA_SRV_GetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8 *penImsVoiceCap)
{
    VOS_UINT32                    ulResult           = IMSA_FALSE;
    IMSA_CONTROL_MANAGER_STRU     *pstControlMagnaer = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            if (VOS_FALSE == IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
                ulResult = IMSA_TRUE;
            }
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE;
            }
            else
            {
                *penImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE;
            }
            ulResult = IMSA_TRUE;
            break;
        default:
            break;
    }

    return ulResult;
}



VOS_VOID IMSA_SRV_SetServcieStatus
(
    IMSA_SRV_TYPE_ENUM_UINT8            enSrvType,
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
)
{
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enNrmRegStatus = IMSA_NORMAL_REG_STATUS_BUTT;
    IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 enNrmAtRegStatus = IMSA_NORMAL_AT_REG_STATUS_BUTT;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  enImsVoiceCap = MSCC_IMSA_IMS_VOICE_CAP_BUTT;

    /* ��ȡ����ԭ״̬ */

    /* ��ӡ�������� */

    /* ��ӡ����״̬�������Ϣ */

    if (IMSA_SRV_TYPE_EMC == enSrvType)
    {
        IMSA_SRV_GetEmcSrvStatus() = enSrvStatus;

        /* ���ȡ��IMS VOICE���������ϱ�IMS VOICE���� */
        if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
        }
        return ;
    }

    /* ���ݷ���״̬����ȡ��ͨע��״̬ */
    enNrmRegStatus = IMSA_SRV_GetRegStatusFromSrvStatus(enSrvStatus);

    /* �����ͨע��״̬�����������֪ͨǩԼ��ģ�����µ���ͨע��״̬ */
    if (enNrmRegStatus != IMSA_GetLastNrmRegStatus())
    {
        IMSA_SRV_NrmRegStatusNotify(enNrmRegStatus);

        IMSA_SetLastNrmRegStatus(enNrmRegStatus);
    }

    /* ���ݷ���״̬����ȡ��ͨATע��״̬ */
    enNrmAtRegStatus = IMSA_SRV_GetAtRegStatusFromSrvStatus(enSrvStatus);

    IMSA_INFO_LOG2("IMSA_SRV_SetServcieStatus:enNrmAtRegStatus = ,IMSA_GetLastNrmAtRegStatus()=",
                   enNrmAtRegStatus,IMSA_GetLastNrmAtRegStatus());
    TLPS_PRINT2LAYER_INFO2(IMSA_SRV_SetServcieStatus_ENUM, 1, enNrmAtRegStatus, IMSA_GetLastNrmAtRegStatus());

    /* �����ͨATע��״̬�����������֪ͨAT���µ���ͨATע��״̬ */
    if (enNrmAtRegStatus != IMSA_GetLastNrmAtRegStatus())
    {
        IMSA_SndMsgAtCireguInd(enNrmAtRegStatus);

        IMSA_SetLastNrmAtRegStatus(enNrmAtRegStatus);
    }

    IMSA_SRV_GetNormalSrvStatus() = enSrvStatus;

    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        /* SRVCC�쳣(����ػ���DEREG REQ��״̬Ǩ��CONN+REG)���建�� */
        IMSA_SrvccAbormalClearBuff(IMSA_SRVCC_ABNORMAL_STATUS_CHANGE);

        IMSA_SMS_ClearResource();

        IMSA_USSD_ClearResource();
    }

    /* ���ȡ��IMS VOICE���������ϱ�IMS VOICE���� */
    if (IMSA_TRUE == IMSA_SRV_GetImsVoiceCapability(&enImsVoiceCap))
    {
        IMSA_SndMsccMsgImsVoiceCapNotify(enImsVoiceCap, IMSA_CONN_IsExitPersistentBearer());
    }

}

VOS_VOID IMSA_SRV_ProcConnSetupIndSucc
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU              *pstImsaControlManager   = VOS_NULL_PTR;
    VOS_CHAR                                acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                                acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndSucc_ENUM, LNAS_ENTRY);

    pstImsaControlManager = IMSA_GetControlManagerAddress();

    /* ��CALL�ķ���״̬���������֪ͨCALL;�����ǰ���뼼����֧��IMS�������޷���
       ��ǰ���뼼��֧��IMSʱ�������������ж�:
       CONN REG�з���CONN DEREG���Ƿ����޿�
    ������޿������з��񣬷������޷������������޷���,CALLģ���յ��޷�����Ҫ�ͷ�
    CALL��*/

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        /* ֪ͨCALLģ������Ѿ��߱� */
        IMSA_ProcCallResourceIsReady(pstConnSetupIndMsg->enConnType, pstConnSetupIndMsg->enMediaPdpType);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stNrmRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stNrmRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    else
    {
        IMSA_UtilStrNCpy(acUeAddr, pstImsaControlManager->stEmcRegParaInfo.acUeAddr, IMSA_IPV6_ADDR_STRING_LEN);
        IMSA_UtilStrNCpy(acPcscfAddr, pstImsaControlManager->stEmcRegParaInfo.acPcscfAddr, IMSA_IPV6_ADDR_STRING_LEN);
    }
    /* �����ǰ����REG+CONNING״̬ */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                    IMSA_SRV_STATUS_CONNING_REG))
    {
        /* ������ݵ�ע�������Ч�������ݵ�ע���������ΪCURRENT����������ǰ����״̬�޸�ΪCONN+REG״̬ */
        if (IMSA_TRUE == IMSA_IsRegParaAvailable((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                  acUeAddr,
                                                  acPcscfAddr))
        {
            (VOS_VOID)IMSA_SetCurrentPara((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                          acUeAddr,
                                          acPcscfAddr);
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REG);
        }
        else
        /* ������ݵ�ע�������Ч���򽫱���ȥע�ᣬ����֪ͨREGģ�����·���ע�� */
        {
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq((IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType, IMSA_REG_ADDR_PARAM_NEW);


        }

        /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
        if (IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
        }
        else
        {
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);
        }

        return;
    }

    /* ������ؼ���ɹ���֧ */

    /* �������CONNING&DEREG̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndSucc:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndSucc_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* ������޿�����������ת��CONN&DEREG̬�����ٷ���ע�ᣬ֪ͨCALL����
           ����߱�;����ת��CONN&REGING̬������REGģ�鷢�����ע�� */
        if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

            /* �޿��������������ע�ᣬ���֪ͨCALLģ��������з���߱� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_BUTT);
        }
        else
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
        }
    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);

        IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);
    }

    return ;
}
VOS_VOID IMSA_SRV_ProcConnSetupIndFail
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnSetupIndMsg->enSipPdpType)
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:can not happen when nw initiate pdp activation!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, 2);
        return ;
    }

    /* ������ؼ���ʧ�ܷ�֧ */
    /* �ؽ������̴���REG+CONNING״̬ */
    if ((IMSA_CONN_TYPE_NORMAL == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* ����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
        /* ���������Գ��Զ�ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);
        #endif
        return;
    }

    if ((IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
        && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,
                                                   IMSA_SRV_STATUS_CONNING_REG)))
    {
        /* ����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_EMC, IMSA_DEREG_LOCAL);
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        return;
    }

    /* �������CONNING&DEREG̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual( (IMSA_SRV_TYPE_ENUM_UINT8)pstConnSetupIndMsg->enConnType,
                                                IMSA_SRV_STATUS_CONNING_DEREG))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcConnSetupIndFail:SRV status is not conningdereg!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcConnSetupIndFail_ENUM, IMSA_STATE_ERROR);
        return ;
    }

    if (IMSA_CONN_TYPE_EMC == pstConnSetupIndMsg->enConnType)
    {
        /* ״̬ת��IDLE&DEREG̬��֪ͨCALL�������񲻾߱� */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }
    else
    {
        if ((IMSA_CONN_RESULT_FAIL_TIMER_EXP == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_CONN_RELEASING == pstConnSetupIndMsg->enResult)
            || (IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING == pstConnSetupIndMsg->enResult))
        {
            /* ���������Գ���IMS����ʱ�� */
            IMSA_INFO_LOG("IMSA_SRV_ProcConnSetupIndFail:start period ims service tyr timer!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnSetupIndFail_ENUM, 4);
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
        }

        /* ״̬ת��IDLE&DEREG̬��֪ͨCALL�������񲻾߱�������IMSA_SRV_SetServcieStatus
           �л��õ������Գ���IMS����ʱ��������������ҵ�ǰ����ע������У�
           ������Ҫ��������ʱ����ת״̬ */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
    }
}


VOS_VOID IMSA_SRV_ProcRegRegIndSucc
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndSucc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndSucc_ENUM, LNAS_ENTRY);

    /* ���������������״̬ת��CONN&REG̬��֪ͨCALLģ����������߱� */
    if (IMSA_REG_TYPE_NORMAL == pstRegRegIndMsg->enRegType)
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REG);

        /* ֪ͨCALLģ����ͨ���з�������з���״̬ */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);
    }
    else
    {
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_REG);

        /* ֪ͨCALLģ��������з�������з���״̬ */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_BUTT);
    }

    return ;
}
VOS_VOID IMSA_SRV_ProcRegRegIndFail
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_ENTRY);

    switch (pstRegRegIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_NULL:
            /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }

            break;
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEW);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_SAME);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            IMSA_SRV_SndRegRegReq(pstRegRegIndMsg->enRegType, IMSA_REG_ADDR_PARAM_NEXT);
            break;
        case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
            IMSA_SRV_SetServcieStatus((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                       IMSA_SRV_STATUS_CONN_DEREG);

            /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
            IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                          IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                          IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
            break;
        default:

            IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndFail:illegal result action!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndFail_ENUM, LNAS_PARAM_INVALID);

            /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
            IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegRegIndMsg->enRegType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                        IMSA_SRV_STATUS_RELEASING_DEREG);

            if (IMSA_REG_TYPE_EMC == pstRegRegIndMsg->enRegType)
            {
                /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
                IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                                IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
            }

            break;
    }
}
VOS_VOID IMSA_SRV_ProcRegRegIndMsg
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegRegIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegRegIndMsg_ENUM, LNAS_ENTRY);

    /* �������CONN&REGING̬����ֱ���˳� */
    if (IMSA_TRUE != IMSA_SRV_IsSrvStatusEqual(     (IMSA_SRV_TYPE_ENUM_UINT8)pstRegRegIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REGING))
    {
        IMSA_WARN_LOG("IMSA_SRV_ProcRegRegIndMsg:Not conn&reging state!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcRegRegIndMsg_ENUM, IMSA_STATE_ERROR);

        return ;
    }

    if (IMSA_REG_RESULT_SUCCESS == pstRegRegIndMsg->enResult)
    {
        IMSA_SRV_ProcRegRegIndSucc(pstRegRegIndMsg);
    }
    else
    {
        IMSA_SRV_ProcRegRegIndFail(pstRegRegIndMsg);
    }
}
VOS_VOID IMSA_SRV_RegConningStateProcRegDeregIndMsg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;

    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        /* �������Գ��Զ�ʱ����ʱ */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaControlManager->stPeriodImsSrvTryTimer))
        {
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_IDLE_DEREG);
        }
        else
        {
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
        }
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

        return;
    }
    /* ����ע�� */
    if (IMSA_REG_TYPE_EMC == enRegType)
    {
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaControlManager->stPeriodImsEmcSrvTryTimer))
        {
            IMSA_StopTimer(&pstImsaControlManager->stPeriodImsEmcSrvTryTimer);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                        IMSA_SRV_STATUS_IDLE_DEREG);
        }
        else
        {
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
        }
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        return;
    }
}


VOS_VOID IMSA_SRV_ProcRegDeregIndMsg
(
    const IMSA_REG_DEREG_IND_STRU      *pstRegDeregIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_ENTRY);

    /* �����CONN&DEREGING״̬���������ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_DEREGING))
    {
        /* Ŀǰֻ��MMA DEREG REG���µ�ȥע�����ͣ������������������͵�ȥע�ᣬ
           �˴���Ҫ���ӿ��� */
        IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegDeregIndMsg->enRegType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                    IMSA_SRV_STATUS_RELEASING_DEREG);
        IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

        return ;
    }

    /* �����CONNING&REG״̬���򱾵�ȥע�ᣬ״̬�޸�ΪCONNING&DEREG״̬ */
    if (((IMSA_REG_TYPE_NORMAL == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_NORMAL,IMSA_SRV_STATUS_CONNING_REG)))
        ||((IMSA_REG_TYPE_EMC == pstRegDeregIndMsg->enRegType)
            && (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual(IMSA_SRV_TYPE_EMC,IMSA_SRV_STATUS_CONNING_REG))))
    {
        IMSA_SRV_RegConningStateProcRegDeregIndMsg(pstRegDeregIndMsg->enRegType);

        return;
    }

    if (IMSA_TRUE == IMSA_SRV_IsSrvStatusEqual((    IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                                    IMSA_SRV_STATUS_CONN_REG))
    {
        switch (pstRegDeregIndMsg->enResultAction)
        {
            case IMSA_RESULT_ACTION_NULL:

                /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
                IMSA_SRV_SndConnRelReq(     (IMSA_CONN_TYPE_ENUM_UINT32)pstRegDeregIndMsg->enRegType,
                                            IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_RELEASING_DEREG);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
                break;
            case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

                /* ���г�ʼע�ᣬʹ�õ�һ����ַ�ԣ�״̬ת��CONN&REGING̬ */
                IMSA_SRV_SndRegRegReq(      pstRegDeregIndMsg->enRegType,
                                            IMSA_REG_ADDR_PARAM_NEW);

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_REGING);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
                break;
            case IMSA_RESULT_ACTION_REG_WITH_CURRENT_ADDR_PAIR:

                /* ���г�ʼע�ᣬʹ�õ�ǰ��ַ�ԣ�״̬ת��CONN&REGING̬ */
                IMSA_SRV_SndRegRegReq(      pstRegDeregIndMsg->enRegType,
                                            IMSA_REG_ADDR_PARAM_SAME);

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_REGING);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
                break;
            case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

                /* ���г�ʼע�ᣬʹ����һ����ַ�ԣ�״̬ת��CONN&REGING̬ */
                IMSA_SRV_SndRegRegReq(      pstRegDeregIndMsg->enRegType,
                                            IMSA_REG_ADDR_PARAM_NEXT);

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_REGING);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

                break;
            case IMSA_RESULT_ACTION_REG_LOCAL_DEREG:
                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_CONN_DEREG);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

                break;
            default:

                IMSA_INFO_LOG("IMSA_SRV_ProcRegDeregIndMsg:illegal result action!");
                TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcRegDeregIndMsg_ENUM, LNAS_PARAM_INVALID);

                /* ��������ע�ᣬ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬ */
                IMSA_SRV_SndConnRelReq((IMSA_CONN_TYPE_ENUM_UINT32)pstRegDeregIndMsg->enRegType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

                IMSA_SRV_SetServcieStatus(  (IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                            IMSA_SRV_STATUS_RELEASING_DEREG);

                /* ����CONN&REG̬�����֪ͨCALL���з�������޷���״̬ */
                IMSA_SRV_SndCallSrvStatusInd((IMSA_SRV_TYPE_ENUM_UINT8)pstRegDeregIndMsg->enRegType,
                                              IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                              IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

                break;
        }
    }

    return ;
}


VOS_VOID IMSA_SRV_ProcConnSetupIndMsg
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
)
{
    if (IMSA_CONN_RESULT_SUCCESS == pstConnSetupIndMsg->enResult)
    {
        IMSA_SRV_ProcConnSetupIndSucc(pstConnSetupIndMsg);
    }
    else
    {
        IMSA_SRV_ProcConnSetupIndFail(pstConnSetupIndMsg);
    }
}


VOS_VOID IMSA_SRV_ProcEmcConnRelIndMsg
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{

    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc dedicated release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 1);

        /* ֪ͨCALLģ��ý������ͷ� */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_EMC);

        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcEmcConnRelIndMsg:emc default release!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcEmcConnRelIndMsg_ENUM, 2);

    /* ����ע��״̬���յ����෢�͵��ͷ�SIP�������غ�Ĵ��� */
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* ��Ҫ����PDN�ؽ�����Ҫ֪ͨIMS�������� */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_EMC_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONNING_REG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsEmcSrvTryTimer);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return;
    }
    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ֪ͨIMSA����ȥע�� */
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        return;
    }

    /* �������������״̬����֪ͨREGģ�鱾��ȥע�� */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* ��Ҫ֪ͨCALLģ��������з�������޷���״̬����ʹ���ͷŻ���Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* �����Ѿ����б���ȥע�ᣬ����֪ͨCALLģ����з���״̬�����޷���
           ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */
    }

    IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);
}


VOS_VOID IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, LNAS_ENTRY);

    /* ����DETACHED̬�������ͷ�(����DETACH����MT DETACH���µ�)��IMSA��Ӧ���ؽ���·��
       ������ATTACHED̬�������ͷţ�IMSAӦ���ؽ���·��IMSAͨ��PS�����״̬�Ƿ���
       �������������֣���Ϊ�˱���ϵͳ��ʱ������(��APS֪ͨ�����ͷ���ǰ��MMA֪ͨ
       PS�����״̬�ں�)��������IMSA�ж�����IMSA�������ж�PS�����״̬��������
       �����Գ���IMS����ʱ��������ʱ����ʱ�����ж��������ӵ������Ƿ�߱� */
    pstControlMagnaer  = IMSA_GetControlManagerAddress();
    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERED);

        /* SIP��������ͷź󣬲��ٱ���ȥע�ᣬIP��ַ�����������IMS������ע�ᶨʱ����ʱ��
        ���·���IMSע�� */
        /* ��Ҫ֪ͨIMS�������� */
        IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

        /*IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);*/
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* ֪ͨCALLģ����ͨ���з�������޷���״̬ */
        IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

        return ;
    }

    if (IMSA_SRV_STATUS_CONNING_REG == IMSA_SRV_GetNormalSrvStatus())
    {
        /* �����ʱ��û�������У���ת��IDLE+DEREG״̬������ȥע�� */
        if (IMSA_TRUE != IMSA_IsTimerRunning(&pstControlMagnaer->stPeriodImsSrvTryTimer))
        {
            /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
        }
        return;
    }

    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        /* ״̬ת��IDLE&DEREG̬������IMSA_SRV_SetServcieStatus�л��õ�������
           ����IMS����ʱ��������������ҵ�ǰ��ע������У�������Ҫ��������ʱ����ת״̬ */
        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* �����Ѿ����б���ȥע�ᣬ����֪ͨCALLģ����з���״̬�����޷���
           ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        /* ���������Գ���IMS����ʱ�� */
        IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

        return ;
    }

    if ((IMSA_SRV_STATUS_RELEASING_DEREG == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:releasing&dereg or conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_RELEASING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg:conn&dereging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

        return ;
    }

    return ;
}
VOS_VOID IMSA_SRV_ProcConnRelIndMsg
(
    const IMSA_CONN_REL_IND_STRU       *pstConnRelIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, LNAS_ENTRY);

    if (IMSA_CONN_TYPE_EMC == pstConnRelIndMsg->enConnType)
    {
        IMSA_SRV_ProcEmcConnRelIndMsg(pstConnRelIndMsg->enSipPdpType);

        return ;
    }

    /* ��ͨ���ӷ�֧ */

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnRelIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnRelIndMsg:normal media pdp release!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnRelIndMsg_ENUM, 2);

        /* ֪ͨCALLģ��ý������ͷ� */
        IMSA_ProcCallResourceIsNotReady(IMSA_CONN_TYPE_NORMAL);

        /* ֪ͨMSCC����ǰ����״̬ */
        if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
        }

        /* ��IDLE+DEREG״̬�²����յ�ý����ص��ͷ���Ϣ�����Բ���Ҫ�ж� */

        /* ý����ر��ͷţ����粻֧��IMS VOICE,���뼼����֧��IMSʱ������������Ƿ�
        �Ҷϵ绰��ɾ��UE�����Ҷϵ绰�Ĺ��� */

    }
    else
    {
        IMSA_SRV_ProcNormalConnSigalBearerRelIndMsg();
    }
}


VOS_VOID IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, LNAS_ENTRY);

    /* �������ע�������Ч����ֱ���˳� */
    if (IMSA_OP_TRUE != pstConnModifyIndMsg->bitOpModifyType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:normal,not reg para invalid!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, 2);

        return ;
    }

    /* ����������ӣ���ע��P-CSCF��ַʧЧ�������·���ע�᣻����ֱ���˳�  */
    if (IMSA_CONN_TYPE_EMC == pstConnModifyIndMsg->enConnType)
    {
        if (IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID == pstConnModifyIndMsg->enModifyType)
        {
            /* ��Ҫ�ж�ע��״̬ */
            if ((IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus()) ||
                (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
            {
                IMSA_SRV_SetServcieStatus(IMSA_REG_TYPE_EMC, IMSA_SRV_STATUS_CONN_REGING);
                IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
                IMSA_SRV_SndRegRegReq(IMSA_REG_TYPE_EMC, IMSA_REG_ADDR_PARAM_NEW);
            }

        }

        return ;
    }

    /* ע�����ʧЧ */
    if (IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID == pstConnModifyIndMsg->enModifyType)
    {

        pstControlMagnaer  = IMSA_GetControlManagerAddress();

        /* �����CONN&REGIN����GCONN&REG̬��������REGģ�鱾��ȥע�ᣬ
           ����CONNģ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬�����������Գ���IMS
           ����ʱ�� */
        if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERING);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            /* �����Ѿ����б���ȥע�ᣬ����֪ͨCALLģ����з���״̬�����޷���
               ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            return ;
        }

        if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_REGISTERED);

            /* ��Ҫ֪ͨIMS�������� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONNING_REG);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            return;
        }

        /* �����CONN&DEREGING̬��������REGģ�鱾��ȥע�ᣬ����CONNģ���ͷ����ӣ�
           ״̬ת��RELEASING&DEREG̬ */
        if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereging!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_DEREGISTERING);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            return ;
        }

        /* �����CONN&DEREG̬��������CONNģ���ͷ����ӣ�״̬ת��RELEASING&DEREG̬,
           ���������Գ���IMS����ʱ�� */
        if (IMSA_SRV_STATUS_CONN_DEREG == IMSA_SRV_GetNormalSrvStatus())
        {
            IMSA_INFO_LOG("IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);

            return ;
        }
    }
    else /* P-CSCF��ַʧЧ */
    {
        if ((IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()) ||
            (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus()))
        {
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_REGING);
            IMSA_SRV_SndRegDeregReq(IMSA_SRV_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SndRegRegReq(IMSA_SRV_TYPE_NORMAL, IMSA_REG_ADDR_PARAM_NEW);

            return;
        }
    }
}



VOS_VOID IMSA_SRV_ProcConnModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);

    /* �����ý������޸ģ���ͨ��CALLģ����Դ�߱� */
    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnModifyIndMsg->enSipPdpType)
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcConnModifyIndMsg:no need notify CallModule!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcConnModifyIndMsg_ENUM, LNAS_ENTRY);
    }
    else
    {
        IMSA_SRV_ProcNormalConnSignalBearerModifyIndMsg(pstConnModifyIndMsg);
    }
}
VOS_VOID IMSA_SRV_ProcCallRsltActionIndMsg
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
)
{
    IMSA_INFO_LOG("IMSA_SRV_ProcCallRsltActionIndMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ENTRY);

    switch (pstCallRsltActionIndMsg->enResultAction)
    {
        case IMSA_RESULT_ACTION_REG_WITH_FIRST_ADDR_PAIR:

            if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,first addr pair can not happen!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 1);
                return ;
            }

            if (IMSA_SRV_STATUS_IDLE_DEREG != IMSA_SRV_GetEmcSrvStatus())
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:first addr pair,emc status is not IDLE&DEREG!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 1);
                return ;
            }

            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;
        case IMSA_RESULT_ACTION_REG_WITH_NEXT_ADDR_PAIR:

            if (IMSA_CALL_TYPE_EMC != pstCallRsltActionIndMsg->enCallType)
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:normal srv,next addr pair can not happen!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 2);
                return ;
            }

            if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetEmcSrvStatus())
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:next addr pair,emc status is not CONN&REG!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 2);
                return ;
            }

            /* �ȱ���ȥע�ᣬ�ڷ���ע������״̬ת��CONN&REGING */
            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_EMC,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEXT);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* ����CALLģ���ǻ������Ž���������˲���֪ͨCALLģ���޷��񣬷����
               ����CALLģ���������Ľ����� */
            break;
        case IMSA_RESULT_ACTION_REG_RESTORATION:

            if (IMSA_CALL_TYPE_EMC == pstCallRsltActionIndMsg->enCallType)
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:emc srv,restoration can not happen!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_PARAM_INVALID, 3);
                return ;
            }

            if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
            {
                IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:restoration,normal status is not CONN&REG!");
                TLPS_PRINT2LAYER_WARNING1(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, IMSA_STATE_ERROR, 3);
                return ;
            }

            /* �ȱ���ȥע�ᣬ�ڷ���ע������״̬ת��CONN&REGING */
            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_RESTORATION);

            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            /* �����Ѿ�֪ͨע��ģ����б���ȥע�ᣬ�������֪ͨCALLģ���޷���
               ���򱾵�ȥע�����̺��ͷ�CALL����ͬʱ���У����׳����� */

            break;

        default:

            IMSA_WARN_LOG("IMSA_SRV_ProcCallRsltActionIndMsg:illegal result action!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SRV_ProcCallRsltActionIndMsg_ENUM, LNAS_ERROR);

            break;
    }
}


VOS_VOID IMSA_SRV_ProcTransToNotSupportEms( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERED);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conning&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_INFO_LOG("IMSA_SRV_ProcTransToNotSupportEms:conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcTransToNotSupportEms_ENUM, IMSA_STATUS_REGISTERING);

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

            IMSA_SRV_SndConnRelReq( IMSA_CONN_TYPE_EMC,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_REG_ERR);

            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_RELEASING_DEREG);

            break;

        default:
            break;
    }
}



VOS_VOID IMSA_SRV_UpdateRat
(
    MSCC_IMSA_RAT_TYPE_ENUM_UINT8        enRat,
    VOS_UINT32                         *pulIsNotfiyNrmNoSrv,
    VOS_UINT32                         *pulIsNotfiyEmcNoSrv
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8     enCampedRatTypeTmp  = IMSA_CAMPED_RAT_TYPE_BUTT;
    IMSA_CALL_MANAGER_STRU              *pstImsaCallCtx   = VOS_NULL_PTR;

    pstImsaCallCtx   = IMSA_CallCtxGet();
    pstNwInfo = IMSA_GetNetInfoAddress();

    *pulIsNotfiyNrmNoSrv = IMSA_FALSE;
    *pulIsNotfiyEmcNoSrv = IMSA_FALSE;

    IMSA_SRV_RatFormatTransform(    &enCampedRatTypeTmp,
                                    enRat);

    /* �������δ�������ֱ�ӷ��� */
    if (pstNwInfo->enImsaCampedRatType == enCampedRatTypeTmp)
    {
        return ;
    }

    /* lihong00150010 hifi sync begin */
    /* ��GU�任��L���ҵ�ǰ�к��д��ڣ���֪ͨLRRC����HIFIͬ�� */
    if ((enCampedRatTypeTmp == IMSA_CAMPED_RAT_TYPE_EUTRAN)
        && (VOS_TRUE == IMSA_IsCallConnExist()))
    {
        IMSA_SndLRrcHifiSyncSwtichInd(IMSA_TRUE);
    }
    /* lihong00150010 hifi sync end */

    pstNwInfo->enImsaCampedRatType = enCampedRatTypeTmp;

    /*��ϵͳ�任����ҪֹͣBACK-OFF��ʱ��*/
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTxTimer);
    IMSA_StopTimer(&pstImsaCallCtx->stBackOffTyTimer);

    /* ������뼼�������������Ŀ�Ľ��벻֧��IMS����SRVCC��ʶΪFALSE����ָʾ
       IMSA CALL��ģ���޷���ԭ��ֵ��Ϊ��SRVCC��ϵͳ */
    if ((IMSA_FALSE == IMSA_SRV_IsCurRatSupportIms())
        && (IMSA_FALSE == IMSA_CallGetSrvccFlag()))
    {
        *pulIsNotfiyNrmNoSrv = IMSA_TRUE;

    }

    /* ������뼼�������������Ŀ�Ľ��벻֧��EMS����ָʾIMSA REG��ģ�鱾�ؽ���
       ȥע�ᣨ�������IMS����ע�ᣩ����֪ͨIMSA CONN��ģ���ͷŽ������ӣ�
       ���ֻ����IMS�������ӣ�������IMS����ע�ᣩ */
    if (IMSA_FALSE == IMSA_SRV_IsCurRatSupportEms())
    {
        *pulIsNotfiyEmcNoSrv = IMSA_TRUE;


    }
}


VOS_VOID IMSA_SRV_UpdateImsVoPsStatus
(
    MSCC_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8      enImsVoPsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    if (pstNwInfo->enImsaImsVoPsStatus != enImsVoPsInd)
    {
        pstNwInfo->enImsaImsVoPsStatus          = enImsVoPsInd;

        IMSA_SndMsgAtCirepiInd(enImsVoPsInd);

    }
    IMSA_ConfigNetCapInfo2Ims();

}


VOS_VOID IMSA_SRV_UpdateEmsStatus
(
    MSCC_IMSA_EMS_INDICATOR_ENUM_UINT8           enEmsInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    pstNwInfo = IMSA_GetNetInfoAddress();

    pstNwInfo->enImsaEmsStatus = enEmsInd;

}


VOS_VOID IMSA_SRV_ProcSrvChgIndWhenRoamNotSatisfied(VOS_VOID)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* �����ǰ�е绰���ڣ�����Ҫ�ȵ绰�����󣬲��ܷ���ȥע�� */
    if (VOS_TRUE == IMSA_IsImsExist())
    {
        return;
    }

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ֪ͨMMA IMS VOICE  ������ */
            /* �������ֳ���������IMSע������ʱ��MMA�Լ��ܹ�ʶ��ֱ����ΪIMS voice�����ã� ����ҪIMSA
            ֪ͨ���������������£��Ҳ�֧��IMSע�ᣬMMA���޷�ʶ��ģ�������ҪIMSA����֪ͨһ�� */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;

        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע���ԭ��ֵ */
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע���ԭ��ֵ */
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��Ҫ֪ͨIMS�����䷢����֪ͨ���𱾵�ע�� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע���ԭ��ֵ */
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG);
            #endif
            break;

        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            break;

        default:
            break;
    }

}


/* Modify by zhaochen 00308719 2015-08-18 for volte, begin */

VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfied(VOS_VOID)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* �����ǰ��IMSҵ����ڣ�����Ҫ��ҵ������󣬲��ܷ���ȥע�� */
    if (VOS_TRUE == IMSA_IsImsExist())
    {
        return;
    }
    /* �����ǰ��ͨ����֧�����Σ��򲻴��� */
    if (IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT != IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        return;
    }
    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_CONN_REGING:

            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            break;

        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��Ҫ֪ͨIMS�����䷢����֪ͨ���𱾵�ע�� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            break;

        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            break;

        default:
            break;
    }

}
/* Modify by zhaochen 00308719 2015-08-18 for volte, end */

VOS_VOID IMSA_SRV_ProcServiceChangeInd
(
    const MSCC_IMSA_SERVICE_CHANGE_IND_STRU     *pstServiceChangeInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus      = IMSA_SRV_STATUS_BUTT;
    VOS_UINT32                          ulIsNotfiyNrmNoSrv  = IMSA_FALSE;
    VOS_UINT32                          ulIsNotfiyEmcNoSrv  = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_SRV_ProcServiceChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcServiceChangeInd_ENUM, LNAS_ENTRY);

    /* �洢SERVICE CHANGE IND��Ϣ��Я���Ĳ��� */
    pstNwInfo                               = IMSA_GetNetInfoAddress();
    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    pstNwInfo->enImsaPsServiceStatus        = pstServiceChangeInd->enPsServiceStatus;
    /* zhaochen 00308719 begin for Roaming Flag 2015-10-13 */
    /* ֮ǰ�����α����ͨ��CAMP_INFO_CHANGE_IND�������ģ����ǲ���׼ȷ����ҪSERVICE_CHANGE_IND��֪ͨ��IMSA
       ����һ������λbitRoamingValid�����ñ���λΪ1ʱ���������α�־��Ч����ʱIMSA���±���ά��������״̬��*/
    if (VOS_TRUE == pstServiceChangeInd->bitRoamingValid)
    {
        pstNwInfo->ucImsaRoamingFlg             = pstServiceChangeInd->ucRoamingFlg;
    }
    /* zhaochen 00308719 end for Roaming Flag 2015-10-13 */

    pstControlMagnaer->ucImsaUsimStatus     = pstServiceChangeInd->ucPsSimValid;

    /* ���뼼������ */
    IMSA_SRV_UpdateRat(pstServiceChangeInd->enRat, &ulIsNotfiyNrmNoSrv, &ulIsNotfiyEmcNoSrv);

    /* ֻ������������ʱ���Ÿ�������֧��IMS��EMSָʾ */
    if (MSCC_IMSA_NORMAL_SERVICE == pstServiceChangeInd->enPsServiceStatus)
    {
        IMSA_SRV_UpdateImsVoPsStatus(pstServiceChangeInd->enImsVoPsInd);
        IMSA_SRV_UpdateEmsStatus(pstServiceChangeInd->enEmsInd);
    }

    /* ���ڴ���������ñ�־���������յ�SERVICE_CHANGE_INDʱ�����ת�Ƶ�SRVCC�ɹ�ʱ��� */

    switch(IMSA_SRV_IsNrmSrvConditonSatisfied())
    {
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT:
            IMSA_CMCCDeregProc();
            return;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT:
            /* �������ֳ���������IMSע������ʱ��MMA�Լ��ܹ�ʶ��ֱ����ΪIMS voice�����ã� ����ҪIMSA
            ֪ͨ�����ǿ���Ч�ĳ�����MMA���޷�ʶ��ģ�������ҪIMSA����֪ͨһ�� */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            return;

        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT:
            /* ��Ҫ���ݵ�ǰ�ķ���״̬���ж���ֱ��֪ͨVOICE�����ã����Ƿ���ȥע�� */
            IMSA_SRV_ProcSrvChgIndWhenRoamNotSatisfied();
            return;
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT:
            /* ���ƶ������������IMS������֧�֣�����ȥע�� */
            IMSA_CMCCDeregProc();
            return;
        case IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS:
            /* IMS������֧�ֻ���PS�����״̬��ΪNORMAL SERVICEʱ�������⴦�� */
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            return;
        default:
            break;
    }

    enNrmSrvStatus = IMSA_SRV_GetNormalSrvStatus();

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enNrmSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_NORMAL);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* ���������Գ���IMS����ʱ�� */
            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        case IMSA_SRV_STATUS_CONN_DEREGING:

            /* �����MMA DEREG REQ���͵�ȥע�ᣬ���޲�����
               �����������������͵�ȥע�ᣬ����Ҫ���⿼�ǣ�����IMS���Ը�Ϊ��֧��
               ���µ�ȥע������У�IMS����������Ϊ֧�֣�����Ҫ��ȥע�ᶯ����ɺ�
               ������ע�ᣬ�����ͷ����� */
            IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());

            /* zhaochen 00308719 begin for IMS Dereg for too long 2015-09-14 */
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);

            IMSA_SRV_SndRegDeregReq(    IMSA_REG_TYPE_NORMAL,
                                        IMSA_DEREG_LOCAL);

            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);

            /* IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer); */
            /* zhaochen 00308719 end for IMS Dereg for too long 2015-09-14 */
            break;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONNING_REG:
            /*������״̬��ע����ɺ��ϱ�IMS voice����*/
            break;
        default:
            /*IMSA������ע�ᣬ���ϱ�IMS voice����*/
            if (IMSA_TRUE == IMSA_IsImsVoiceContidionSatisfied())
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }
            else
            {
                IMSA_SndMsccMsgImsVoiceCapNotify(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE,IMSA_CONN_IsExitPersistentBearer());
            }

            break;
    }
}


VOS_VOID IMSA_SRV_ProcCampInfoChangeInd
(
    const MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU     *pstCampInfoChangeInd
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_SRV_ProcCampInfoChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcCampInfoChangeInd_ENUM, LNAS_ENTRY);

    /* �洢SERVICE CHANGE IND��Ϣ��Я���Ĳ��� */
    pstNwInfo                       = IMSA_GetNetInfoAddress();

    pstNwInfo->enAccessType         = pstCampInfoChangeInd->enAccessType;
    pstNwInfo->usLac                = pstCampInfoChangeInd->usLac;
    pstNwInfo->usTac                = pstCampInfoChangeInd->usTac;
    IMSA_MEM_CPY(                   &pstNwInfo->stPlmnId,
                                    &pstCampInfoChangeInd->stPlmnId,
                                    sizeof(MSCC_IMSA_PLMN_ID_STRU));
    pstNwInfo->ulCellId             = pstCampInfoChangeInd->ulCellId;

    /* ����CGI��Ϣ��IMS */
    IMSA_ConfigCgi2Ims();
}


VOS_VOID IMSA_SRV_ProcVoiceDomainChangeInd
(
    const MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU     *pstVoiceDomainChangeInd
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    IMSA_INFO_LOG("IMSA_SRV_ProcVoiceDomainChangeInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcVoiceDomainChangeInd_ENUM, LNAS_ENTRY);

    pstControlManager = IMSA_GetControlManagerAddress();

    /* �洢VOICE DOMAIN CHANGE IND��Ϣ��Я���Ĳ��� */
    pstControlManager->stImsaConfigPara.enVoiceDomain = (IMSA_VOICE_DOMAIN_ENUM_UINT32)pstVoiceDomainChangeInd->enVoiceDomain;
}
VOS_VOID IMSA_SRV_ProcDeregReq
(
    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause
)
{
    /* ����ȥע��ԭ��ֵ */
    IMSA_SetDeregCause(enDeregCause);

    /* �������������ע��ɹ���������ע�ᣬ��֪ͨע��ģ����б���ȥע�� */
    if (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reging!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_REG_ERR);
    }

    if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conn&reg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREG);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);

        /* �����Ѿ����б���ȥע�ᣬ������֪ͨCALLģ��������н����޷���״̬��
           ���򱾵�ȥע�����̺�CALL�ͷ�����ͬʱ���У����׳����� */
    }

    if (IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:emc,conning&dereg!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_EMERGENCY);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONNECTING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

        /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
        IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                        IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);
    }

    /* �����ͨ������ע��ɹ���������ע�ᣬ��֪ͨע��ģ�����ȥע�� */
    if ((IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetNormalSrvStatus())
        || (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:dereg normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_NORMAL);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERING);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_REGISTERED);

        IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);

        IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);

        /* �����Ѿ�����ȥע�ᣬ������֪ͨCALLģ����ͨ���н����޷���״̬��
           ����ȥע�����̺�CALL�ͷ�����ͬʱ���У����׳����� */
        return ;
    }

    if (IMSA_SRV_STATUS_CONN_DEREGING == IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:wait for dereg result!");
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, 1);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_CONN);
        TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_DEREGISTERING);
        return ;
    }

    IMSA_INFO_LOG("IMSA_SRV_ProcDeregReq:already dereg!");
    TLPS_PRINT2LAYER_INFO(IMSA_SRV_ProcDeregReq_ENUM, IMSA_STATUS_NOT_REGISTER);

    IMSA_SndMsccMsgDeregCnf();
    return ;
}

VOS_UINT32 IMSA_StartImsNormalService( IMSA_CALL_TYPE_ENUM_UINT8 enCallType)
{
    if (IMSA_SRV_STATUS_CONN_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NORM_SER_NOT_CONN_REG,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_VOICE_DOMAIN_CS_ONLY,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap())
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_IMS_VOPS_STATUS_NOT_SUPPORT,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if ((IMSA_CALL_TYPE_VOICE == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVoiceCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    if ((IMSA_CALL_TYPE_VIDEO == enCallType)
        && (VOS_FALSE == IMSA_GetUeImsVideoCap()))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallFailErrRecord( enCallType,
                                IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VIDEO_CALL,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    #if 0
    if ((IMSA_VOICE_DOMAIN_CS_ONLY == IMSA_GetVoiceDomain())
        || (IMSA_IMS_VOPS_STATUS_NOT_SUPPORT == IMSA_GetNwImsVoiceCap())
        || ((IMSA_CALL_TYPE_VOICE == enCallType)
            && (VOS_FALSE == IMSA_GetUeImsVoiceCap()))
        || ((IMSA_CALL_TYPE_VIDEO== enCallType)
            && (VOS_FALSE == IMSA_GetUeImsVideoCap())))
    {
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }
    #endif

    return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
}


VOS_UINT32 IMSA_StartImsEmergService
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32     *penEmcCallType
)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus      = IMSA_SRV_STATUS_BUTT;

    IMSA_INFO_LOG("IMSA_StartImsEmergService is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, LNAS_ENTRY);


    /* �жϻ�ȡ����IMS����������Ƿ�߱���������߱����򷵻ز��ܴ������ */
    if (IMSA_TRUE != IMSA_SRV_IsEmcSrvConditonSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;
    }

    /* ������������������Ϸ������������ֱ�ӷ����ܴ������ */
    if (IMSA_TRUE == IMSA_SRV_IsMakeEmcCallInNrmSrvSatisfied())
    {
        IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in normal service!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 2);
        *penEmcCallType = IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV;
        return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
    }

    enEmcSrvStatus      = IMSA_SRV_GetEmcSrvStatus();

    /* ���ݵ�ǰ����״̬���в�ͬ���� */
    switch (enEmcSrvStatus)
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:

            /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
            IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                        IMSA_CONN_TYPE_EMC);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONNING_DEREG);
            break;

        case IMSA_SRV_STATUS_RELEASING_DEREG:

            /* ��ʱ��ʵ�ֳɲ���������������CS���ԣ��������Ը����û��������Ϊ
               ������ʱ������·�ͷ����֮���ٽ����������� */
            IMSA_INFO_LOG("IMSA_StartImsEmergService:can not make emc call as in releasing&dereg state!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_EmcCallErrRecord(  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR,
                                    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    IMSA_ERR_LOG_CALL_STATUS_IDLE);
            #endif

            return IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL;

        case IMSA_SRV_STATUS_CONN_DEREG:

            /*  ������޿�����������ֱ�ӷ����ܴ������ */
            if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
            {
                IMSA_INFO_LOG("IMSA_StartImsEmergService:can make anonymous emc call in conn dereg!");
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
                TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_NOT_REGISTER);
                *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
                return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;
            }

            /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
            IMSA_SRV_SndRegRegReq(      IMSA_CONN_TYPE_EMC,
                                        IMSA_REG_ADDR_PARAM_NEW);
            IMSA_SRV_SetServcieStatus(  IMSA_CONN_TYPE_EMC,
                                        IMSA_SRV_STATUS_CONN_REGING);
            break;

        case IMSA_SRV_STATUS_CONN_REG:

            IMSA_INFO_LOG("IMSA_StartImsEmergService:can make emc call in conn reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, IMSA_STATUS_REGISTERED);
            *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
            return IMSA_START_SRV_RESULT_CAN_MAKE_CALL;

        default:
            break;
    }

    if (IMSA_FALSE == IMSA_SRV_IsNrmSrvIsimParaSatisfied())
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_NO_CARD;
    }
    else
    {
        *penEmcCallType = IMSA_EMC_CALL_TYPE_EMC_CONN_EMC_REG;
    }

    return IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION;
}


VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExp(const VOS_VOID *pRcvMsg )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, LNAS_ENTRY);

    pstControlMagnaer  = IMSA_GetControlManagerAddress();

    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&dereg or conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StopTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;

        /* lihong00150010 volte phaseiii 2014-02-11 begin */
        case IMSA_SRV_STATUS_RELEASING_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:releasing&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            IMSA_StartTimer(&pstControlMagnaer->stPeriodImsSrvTryTimer);
            break;
        /* lihong00150010 volte phaseiii 2014-02-11 end */

        case IMSA_SRV_STATUS_IDLE_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:idle&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            /* ������»�ȡIMS��ͨ����������߱���������ͨ���ӽ��� */
            if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC == IMSA_SRV_IsNrmSrvConditonSatisfied())
            {
                /* ��������ģ�齨�����ӣ���״̬ת��IMSA_SERVICE_STATUS_CONNING_DEREG */
                IMSA_SRV_SndConnSetupReq(   IMSA_FALSE,
                                            IMSA_CONN_TYPE_NORMAL);
                IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                            IMSA_SRV_STATUS_CONNING_DEREG);
            }

            break;
        case IMSA_SRV_STATUS_CONN_DEREG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conn&dereg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_NOT_REGISTER);

            /* ������»�ȡIMS��ͨ����������߱���������ͨע������ */
            if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC == IMSA_SRV_IsNrmSrvConditonSatisfied())
            {
                /* ����ע��ģ�鷢��ע�ᣬ��״̬ת��IMSA_SERVICE_STATUS_CONN_REGING */
                IMSA_SRV_SndRegRegReq(      IMSA_REG_TYPE_NORMAL,
                                            IMSA_REG_ADDR_PARAM_NEW);
                IMSA_SRV_SetServcieStatus(  IMSA_SRV_TYPE_NORMAL,
                                            IMSA_SRV_STATUS_CONN_REGING);
            }

            break;
        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:conning&reg!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, IMSA_STATUS_REGISTERED);
            /* ������»�ȡIMS��ͨ����������߱���������ͨע������ */
            if (IMSA_NRM_SRV_CON_SAT_STATUE_SUCC == IMSA_SRV_IsNrmSrvConditonSatisfied())
            {
                /* ��������ģ�齨������ */
                IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                            IMSA_CONN_TYPE_NORMAL);
            }
            else
            {
                IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);

                IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
                IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);

                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST);
                #endif
            }

            break;
        default:
            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsSrvExp:other states!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsSrvExp_ENUM, 1);
            break;
    }
}

VOS_VOID IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp(const VOS_VOID *pRcvMsg )
{
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp_ENUM, LNAS_ENTRY);

    switch (IMSA_SRV_GetEmcSrvStatus())
    {

        case IMSA_SRV_STATUS_CONNING_REG:

            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp:conn&reging!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp_ENUM, IMSA_STATUS_REGISTERING);
            /* ������»�ȡIMS��������������߱����������ע������ */
            if (IMSA_TRUE == IMSA_SRV_IsReestablishEmcPdnConditonSatisfied())
            {
                /* ��������ģ�齨������ */
                IMSA_SRV_SndConnSetupReq(   IMSA_TRUE,
                                            IMSA_CONN_TYPE_EMC);
            }
            else
            {
                /* ����CONNING+REG̬ʱ��IMSA��Ҫ֪ͨIMS������ */
                IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV);

                IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
                IMSA_SRV_SetServcieStatus(IMSA_REG_TYPE_EMC, IMSA_SRV_STATUS_IDLE_DEREG);
            }

            break;
        default:
            IMSA_INFO_LOG("IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp:other states!");
            TLPS_PRINT2LAYER_INFO(IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp_ENUM, 1);
            break;
    }
}
VOS_UINT32  IMSA_AddSubscription
(
    VOS_UINT32                          ulPid,
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulSubscriptionId
)
{
    IMSA_SUBSCRIPTION_INFO_STRU        *pstSubcriptionInfo      = VOS_NULL_PTR;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_AddSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    /* �ж��Ƿ��Ѿ�����������ǣ��򷵻�ʧ�� */
    if (pstSubcriptionInfoList->ulSubscriptionNum >= IMSA_MAX_SUBSCRIPTION_NUM)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:can not save more!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, 1);
        return IMSA_FAIL;
    }

    /* ���������Ƿ�Ϸ� */
    if (enType >= IMSA_SUBCRIBE_TYPE_BUTT)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:type illegal!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_PARAM_INVALID);
        return IMSA_FAIL;
    }

    /* �ж�����ָ���Ƿ�Ϸ� */
    if (pulSubscriptionId == VOS_NULL_PTR)
    {
        IMSA_WARN_LOG("IMSA_AddSubscription:null pointer!");
        TLPS_PRINT2LAYER_INFO(IMSA_AddSubscription_ENUM, LNAS_NULL_PTR);
        return IMSA_FAIL;
    }

    /* �洢ǩԼ��Ϣ */
    pstSubcriptionInfo = &pstSubcriptionInfoList->astSubcriptionInfoArray[pstSubcriptionInfoList->ulSubscriptionNum];
    pstSubcriptionInfo->ulPid               = ulPid;
    pstSubcriptionInfo->enType              = enType;
    pstSubcriptionInfo->ulPara              = ulPara;
    pstSubcriptionInfo->ulSubscriptionId    = pstSubcriptionInfoList->ulMaxSubscriptionId;
    *pulSubscriptionId                      = pstSubcriptionInfoList->ulMaxSubscriptionId;
    pstSubcriptionInfoList->ulMaxSubscriptionId++;
    pstSubcriptionInfoList->ulSubscriptionNum++;

    return IMSA_SUCC;
}


VOS_UINT32 IMSA_DeleteSubscription
(
    VOS_UINT32                  ulSubscriptionId
)
{
    VOS_UINT32                          i                       = IMSA_NULL;
    IMSA_SUBSCRIPTION_INFO_LIST_STRU   *pstSubcriptionInfoList  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_DeleteSubscription is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_DeleteSubscription_ENUM, LNAS_ENTRY);

    pstSubcriptionInfoList  = IMSA_GetSubcriptionInfoListAddr();

    for (i = 0; i < pstSubcriptionInfoList->ulSubscriptionNum; i++)
    {
        if (ulSubscriptionId == pstSubcriptionInfoList->astSubcriptionInfoArray[i].ulSubscriptionId)
        {
            IMSA_MEM_CPY(   &pstSubcriptionInfoList->astSubcriptionInfoArray[i],
                            &pstSubcriptionInfoList->astSubcriptionInfoArray[i+1],
                            sizeof(IMSA_SUBSCRIPTION_INFO_STRU)*((pstSubcriptionInfoList->ulSubscriptionNum - 1) - i));

            pstSubcriptionInfoList->ulSubscriptionNum--;
            return IMSA_SUCC;
        }
    }

    return IMSA_SUCC;
}

/*****************************************************************************
 Function Name   : IMSA_SRV_PrintNrmSrvState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SRV_PrintNrmSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Normal Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Normal Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintNrmSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_SRV_PrintEmcSrvState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_SRV_PrintEmcSrvState( VOS_VOID )
{
    switch (IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_IDLE_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: IDLE+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_IDLE);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONNING_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONNING+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONNECTING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        case IMSA_SRV_STATUS_RELEASING_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: RELEASING+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_RELEASING);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_NOT_REGISTER);
            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_DEREGING:
            IMSA_INFO_LOG("Current Emc Service State: CONN+DEREGING");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_DEREGISTERING);
            break;
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_INFO_LOG("Current Emc Service State: CONN+REG");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_CONN);
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_REGISTERED);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Service State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_SRV_PrintEmcSrvState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_SRV_IsConningRegState
 Description     :
 Input           : ucIsEmc---------1:������ 0:��ͨ
 Output          : None
 Return          : VOS_INT32

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_SRV_IsConningRegState(VOS_UINT8 ucIsEmc)
{
    IMSA_SRV_STATUS_ENUM_UINT8          enImsaSrvStatus = IMSA_SRV_STATUS_BUTT;

    if (1 == ucIsEmc)
    {
        enImsaSrvStatus = IMSA_SRV_GetEmcSrvStatus();
    }
    else
    {
        enImsaSrvStatus = IMSA_SRV_GetNormalSrvStatus();
    }

    if (IMSA_SRV_STATUS_CONNING_REG != enImsaSrvStatus)
    {
        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}


VOS_VOID IMSA_CMCCDeregProc(VOS_VOID)
{
    if (VOS_FALSE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomDeregFlag)
    {
        IMSA_INFO_LOG("CMCC Custom Dereg Flag is false.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 1);
        return;
    }

    /* Modify by zhaochen 00308719 2015-08-07 for volte, begin */
    if (MSCC_IMSA_IMS_VOPS_SUPPORT == IMSA_GetNetInfoAddress()->enImsaImsVoPsStatus)
    {
        IMSA_INFO_LOG("VoPS support.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 2);
        return;
    }
    /* Modify by zhaochen 00308719 2015-08-07 for volte, end */


    if(VOS_TRUE == IMSA_IsImsExist())
    {
        IMSA_INFO_LOG("IMS call/sms/ss running. will dereg later.");
        TLPS_PRINT2LAYER_INFO(IMSA_CMCCDeregProc_ENUM, 3);
        return;
    }

    IMSA_INFO_LOG1("IMSA_CMCCDeregProc: Service status: ", IMSA_SRV_GetNormalSrvStatus());
    TLPS_PRINT2LAYER_INFO1(IMSA_CMCCDeregProc_ENUM, 4, IMSA_SRV_GetNormalSrvStatus());
    switch(IMSA_SRV_GetNormalSrvStatus())
    {
        case IMSA_SRV_STATUS_CONN_REGING:
        case IMSA_SRV_STATUS_CONN_REG:
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_NOT_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_CONN_DEREGING);
            #if (FEATURE_ON == FEATURE_PTM)
            /* ��¼����ȥע���ԭ��ֵ */
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;
        case IMSA_SRV_STATUS_CONNING_DEREG:
        case IMSA_SRV_STATUS_CONN_DEREG:
            IMSA_SRV_SndConnRelReq(IMSA_SRV_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_RELEASING_DEREG);
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;

        case IMSA_SRV_STATUS_CONNING_REG:
            /* ��Ҫ֪ͨIMS�����䷢����֪ͨ���𱾵�ע�� */
            IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo(IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV);
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_NORMAL, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_NORMAL, IMSA_SRV_STATUS_IDLE_DEREG);
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NormInitDeregErrRecord(IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT);
            #endif
            break;
        case IMSA_SRV_STATUS_IDLE_DEREG:
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_NotInitRegErrRecord();
            #endif
            break;
        default:
            break;
    }
}
/* delete by zhaochen 00308719 2015-08-26 for VoLTE begin */
/* delete by zhaochen 00308719 2015-08-26 for VoLTE end */
/*****************************************************************************
 Function Name   : IMSA_CommonDeregProc
 Description     : ���κ����ƶ���������ͨ��ȥע������
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.zhaochen 00308719    2015-08-26  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CommonDeregProc(VOS_VOID)
{

    IMSA_CMCCDeregProc();
    IMSA_SRV_ProcWhenRoamNotSatisfied();

    return;
}


VOS_UINT32 IMSA_IsImsEmcServiceEstablishSucc(VOS_VOID)
{
    VOS_UINT32    ulResult = IMSA_FALSE;

    IMSA_INFO_LOG("IMSA_IsStopImsEmcService is enter!");

    if ((IMSA_SRV_STATUS_CONNING_DEREG == IMSA_SRV_GetEmcSrvStatus()) ||
        (IMSA_SRV_STATUS_CONN_REGING == IMSA_SRV_GetEmcSrvStatus()))
    {
        ulResult = IMSA_FALSE;
    }
    else if (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetEmcSrvStatus())
    {
        ulResult = IMSA_TRUE;
    }
    else
    {
        IMSA_INFO_LOG("IMSA_IsStopImsEmcService:other status!");
    }


    return ulResult;
}


VOS_VOID IMSA_StopImsEmcService(VOS_VOID)
{
    IMSA_INFO_LOG("IMSA_StopImsEmcService is enter!");

    switch(IMSA_SRV_GetEmcSrvStatus())
    {
        case IMSA_SRV_STATUS_CONNING_DEREG:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONNING_DEREG!");

            IMSA_SRV_SndConnRelReq(IMSA_CONN_TYPE_EMC,
                                   IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

            /* ״̬ת��RELEASE+DEREG̬��֪ͨCALL�������񲻾߱� */
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC,
                                      IMSA_SRV_STATUS_RELEASING_DEREG);

            /* ֪ͨCALLģ��������з�������޷���״̬����ʹCALLģ���������Ľ����� */
            IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                            IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR);

            break;
        case IMSA_SRV_STATUS_CONN_REGING:
            IMSA_INFO_LOG("IMSA_SRV_ProcEmcTcallTimerExp:CONN_REGING!");

            /* ��Ҫ����ȥע�� */
            IMSA_SRV_SndRegDeregReq(IMSA_REG_TYPE_EMC, IMSA_DEREG_LOCAL);
            IMSA_SRV_SetServcieStatus(IMSA_SRV_TYPE_EMC, IMSA_SRV_STATUS_CONN_DEREGING);
            break;
        default:
            IMSA_INFO_LOG("IMSA_StopImsEmcService:other status!");
            break;
    }

}

/*lint +e961*/

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaServiceManagement.c */



