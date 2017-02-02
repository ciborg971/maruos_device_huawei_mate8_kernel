/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaConnManagement.c
  Description     : ��C�ļ�ʵ�����ӹ���ģ��ĳ�ʼ�����ڲ���Ϣ�Ĵ���ͷ��ͣ�
                    �ṩ�ⲿ���õ�API
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact


******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -esym(766,*)*/
#include "ImsaConnManagement.h"
#include "ImsaPublic.h"
#include "ImsaEntity.h"
#include "ImsNicInterface.h"
#include "ImsaRegManagement.h"

/*#include "ImsaProcApsMsg.h"*/
#include "ImsaProcRnicMsg.h"
#include "ImsaProcAtMsg.h"


#if (VOS_WIN32 != VOS_OS_VER)
#if (VOS_VXWORKS == VOS_OS_VER)
#include <arpa/inet.h>
#else
#include "tcpip/public/tcpip_basetype.h"
#include "tcpip/public/tcpip_sock.h"
#endif
#endif


/*lint -e767*/
#define    THIS_FILE_ID      PS_FILE_ID_IMSACONNMANAGEMENT_C
#define    THIS_NAS_FILE_ID  NAS_FILE_ID_IMSACONNMANAGEMENT_C
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
VOS_CHAR                                g_acIpStringForSt_ipv4[IMSA_IPV4_ADDR_STRING_LEN + 1] = {0};
VOS_CHAR                                g_acIpStringForSt_ipv6[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
#if (FEATURE_ON == FEATURE_PTM)
IMSA_CN_CAUSE_TRANS_STRU                g_astImsaCnRejCauseMap[] =
{
    /*------------taf casue-----------------------------------imsa cause---------------------------*/
    {TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,        IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING},
    {TAF_PS_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT},
    {TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE},
    {TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INSUFFICIENT_RESOURCES},
    {TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN},
    {TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE},
    {TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL},
    {TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW, IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN},
    {TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED},
    {TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED},
    {TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED},
    {TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER},
    {TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NSAPI_ALREADY_USED},
    {TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REGULAR_DEACTIVATION},
    {TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_QOS_NOT_ACCEPTED},
    {TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NETWORK_FAILURE},
    {TAF_PS_CAUSE_SM_NW_REACTIVATION_REQUESTED,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REACTIVATION_REQUESTED},
    {TAF_PS_CAUSE_SM_NW_FEATURE_NOT_SUPPORT,                IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_FEATURE_NOT_SUPPORT},
    {TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,                IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT},
    {TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,               IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT},
    {TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT},
    {TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER},
    {TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER},
    {TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,  IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED},
    {TAF_PS_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT},
    {TAF_PS_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION},
    {TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED},
    {TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST},
    {TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,   IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED},
    {TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST},
    {TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE},
    {TAF_PS_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED,      IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED},
    {TAF_PS_CAUSE_SM_NW_INVALID_TI,                         IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_TI},
    {TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,     IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE},
    {TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,             IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_MANDATORY_INFO},
    {TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,              IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT},
    {TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,            IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE},
    {TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_IE_NON_EXISTENT},
    {TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_CONDITIONAL_IE_ERR},
    {TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                 IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_NOT_COMPATIBLE},
    {TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,           IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED},
    {TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,       IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE}

};

static VOS_UINT32   g_astImsaCnRejCauseNum
        = sizeof(g_astImsaCnRejCauseMap)/sizeof(IMSA_CN_CAUSE_TRANS_STRU);
#endif

extern VOS_UINT32 IMSA_CONN_GetTimerLen
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
);
extern VOS_UINT32 IMSA_CONN_IsImsSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_IsPndTypeValid
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_IsEmcSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
);
extern VOS_UINT32 IMSA_CONN_FindSipSignalDialPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID IMSA_CONN_SaveSelectedSdfPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_SDF_PARA_STRU            *pstTafSdfPara
);
extern VOS_VOID IMSA_CONN_DeletePdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_UINT32 IMSA_CONN_IsPdpIpvxInfoIncludeRegPara
(
    IMSA_IP_TYPE_ENUM_UINT8                 enIpType,
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
);
extern VOS_UINT32 IMSA_CONN_IsPdpInfoIncludeRegPara
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
);
extern IMSA_FSM_PROC IMSA_FsmGetProcItem(VOS_UINT32 ulState, VOS_UINT32 ulEvt);
extern VOS_UINT32 IMSA_FsmRun(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID *pData);
extern VOS_VOID IMSA_RegResetRetryTimes
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
extern VOS_VOID IMSA_RegConverterReg2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pucIpAddr,
    const VOS_CHAR *pacPcscfAddr,
    IMSA_IMS_INPUT_EVENT_STRU *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_RegConfigIpAddress2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    const VOS_CHAR                     *pcUeAddr,
    const VOS_CHAR                     *pacPcscfAddr
);
extern VOS_VOID IMSA_RegSendImsMsgDereg
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    VOS_UINT32                          ulIsLocal
);
extern VOS_UINT32 IMSA_RegSendImsMsgReg
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    const VOS_CHAR *pcUeAddr,
    const VOS_CHAR *pcPcscfAddr
);
extern VOS_UINT32 IMSA_RegSendIntraMsgRegInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
extern VOS_UINT32 IMSA_RegSendIntraMsgDeregInd
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_RESULT_ENUM_UINT32 enResult,
    IMSA_RESULT_ACTION_ENUM_UINT32 enAction
);
extern VOS_UINT32 IMSA_RegGetAddrByParamType
(
    IMSA_REG_TYPE_ENUM_UINT8 enRegType,
    IMSA_REG_ADDR_PARAM_ENUM_UINT32 enParamType,
    VOS_CHAR *pucUeAddr,
    VOS_CHAR *pucPcscfAddr
);
extern VOS_UINT32 IMSA_RegParseImsError
(
    const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService,
    IMSA_IMS_OUTPUT_ERROR_STRU          *pstImsErrorInfo
);
extern VOS_UINT32 IMSA_RegCalculateRetryDelayTime
(
    VOS_UINT32                          ulMaxTime,
    VOS_UINT32                          ulBaseTime,
    VOS_UINT32                          ulConsecutiveFailures
);
extern VOS_UINT32 IMSA_RegCalculateRegFailureRetryIntervelTime
(
    VOS_UINT32                          ulRetryTimes,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration
);
extern VOS_VOID IMSA_RegFsmProcRegisteringImsRegFailure305
(
    IMSA_REG_ENTITY_STRU               *pstEntity
);
extern VOS_VOID IMSA_RegWaitForRetryCommonProc
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_UINT32                          ulRetryAfter,
    VOS_UINT32                          ulIsReRegisteration,
    VOS_UINT16                          usSipStatusCode
);
extern VOS_UINT32 IMSA_RegProcImsMsgState(const IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU  *pstOutputService);
extern IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairCreate
(
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr,
    const VOS_CHAR *pacPcscfAddr
);
extern VOS_VOID IMSA_RegAddrPairDestroy(IMSA_REG_ADDR_PAIR_STRU *pstAddrPair);
extern IMSA_REG_ADDR_PAIR_STRU* IMSA_RegAddrPairListAdd
(
    IMSA_REG_ADDR_PAIR_STRU **ppstListHead,
    IMSA_REG_ADDR_PAIR_STRU *pstNode
);
extern VOS_VOID IMSA_RegAddrPairListDestroy(IMSA_REG_ADDR_PAIR_STRU *pstListHead);
extern VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewPcscfAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacPcscfAddr
);
extern VOS_UINT32 IMSA_RegAddrPairMgrUpdateWithNewUeAddr
(
    IMSA_REG_ADDR_PAIR_MGR_STRU *pstAddrPairMgr,
    IMSA_IP_TYPE_ENUM_UINT8 enIpType,
    const VOS_CHAR *pacUeAddr
);
extern VOS_VOID IMSA_RegGetAddrPairListHead
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    IMSA_REG_ADDR_PAIR_STRU          ***pppstListHead
);
extern VOS_VOID IMSA_RegAddrPairListClearAllUsedFlag(IMSA_REG_ADDR_PAIR_STRU *pstList);

extern VOS_UINT32 IMSA_CONN_PdnInfoNicConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo);

extern VOS_VOID IMSA_CONN_DeleteEmcPdpInfo
(
    VOS_UINT8                               ucCid
);


extern VOS_VOID IMSA_CONN_PdnInfoNicDelete
(
    VOS_UINT8                           ucPdpId
);


extern VOS_VOID IMSA_CONN_ProcReEstablishConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
);

extern VOS_UINT32 IMSA_CONN_FilterRegedPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext
);

extern VOS_VOID IMSA_CONN_DeletePcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_ConfigPcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
);
extern VOS_VOID IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
);



/*lint -e961*/
/*****************************************************************************
  3 Function
*****************************************************************************/


VOS_VOID IMSA_CONN_ClearNicPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();

    IMSA_INFO_LOG("IMSA_CONN_ClearNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ClearNicPdpInfo_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET(pstConnManager->astNicPdpInfoArray, 0, sizeof(IMSA_CONN_NIC_PDP_INFO_STRU)*IMSA_CONN_MAX_NIC_PDP_NUM);
}


VOS_VOID IMSA_CONN_DeletePdpId2Nic(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32              i                = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        IMSA_CONN_PdnInfoNicDelete(pstConnManager->astNicPdpInfoArray[i].ucPdpId);

        if (IMSA_FALSE == pstConnManager->astNicPdpInfoArray[i].ucIsEmc)
        {
            /* ͬ�Ϻ�����ȷ�ϣ���ɾ��C����������ʱ��֪ͨRNICģ�飬ɾ������������
            ͬʱ��AT�ϱ�����״̬ */
            IMSA_SndMsgRnicPdnDeactInd(pstConnManager->astNicPdpInfoArray[i].ucPdpId);
            IMSA_SndMsgAtPdpDeactInd(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType);
        }

    }
}



VOS_VOID IMSA_CONN_Init( VOS_VOID )
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    /* ��ʼ���������� */
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    IMSA_MEM_SET(   pstEmcConn, 0x0, sizeof(IMSA_EMC_CONN_STRU));
    pstEmcConn->enImsaConnStatus            = IMSA_CONN_STATUS_IDLE;
    pstEmcConn->enFirstReqPdnType           = IMSA_IP_TYPE_BUTT;
    pstEmcConn->enCurReqPdnType             = IMSA_IP_TYPE_BUTT;
    pstEmcConn->stProtectTimer.phTimer      = VOS_NULL_PTR;
    pstEmcConn->ucCurMaxOpid                = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;

    /* ��ʼ����ͨ���� */
    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    IMSA_MEM_SET(   pstNormalConn, 0x0, sizeof(IMSA_NORMAL_CONN_STRU));
    pstNormalConn->enImsaConnStatus         = IMSA_CONN_STATUS_IDLE;
    pstNormalConn->enFirstReqPdnType        = IMSA_IP_TYPE_BUTT;
    pstNormalConn->enCurReqPdnType          = IMSA_IP_TYPE_BUTT;
    pstNormalConn->stProtectTimer.phTimer   = VOS_NULL_PTR;
    pstNormalConn->ucCurMaxOpid             = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;

    /* ��ʼ���洢���ø�NIC��PDP��Ϣ */
    IMSA_CONN_ClearNicPdpInfo();

    return ;
}

/* lihong00150010 volte phaseiii begin */

VOS_VOID IMSA_CONN_PdnInfoNicDelete
(
    VOS_UINT8                           ucPdpId
)
{
    IMSA_INFO_LOG("before IMS_NIC_PdnInfoDel");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicDelete_ENUM, LNAS_ENTRY);

    (VOS_VOID)IMS_NIC_PdnInfoDel(ucPdpId, MODEM_ID_0);

    IMSA_INFO_LOG("after IMS_NIC_PdnInfoDel");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicDelete_ENUM, LNAS_LEAVE);
}
/* lihong00150010 volte phaseiii end */

VOS_VOID IMSA_CONN_ClearResource( VOS_VOID )
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    /* VOS_UINT32                          i               = 0; */

    /* ��ʼ���������� */
    pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

    /* ֹͣ������ʱ�� */
    IMSA_StopTimer(&pstEmcConn->stProtectTimer);

    pstEmcConn->enImsaConnStatus            = IMSA_CONN_STATUS_IDLE;
    pstEmcConn->enFirstReqPdnType           = IMSA_IP_TYPE_BUTT;
    pstEmcConn->enCurReqPdnType             = IMSA_IP_TYPE_BUTT;
    pstEmcConn->stProtectTimer.phTimer      = VOS_NULL_PTR;
    pstEmcConn->ucCurMaxOpid                = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;
    pstEmcConn->ucOpid                      = IMSA_NULL;
    IMSA_MEM_SET(   &pstEmcConn->stSelSdfPara,
                    0x0,
                    sizeof(IMSA_SEL_SDF_PARA_STRU));

    IMSA_MEM_SET(   &pstEmcConn->stSipSignalPdp,
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    pstEmcConn->ulSipMediaPdpNum        = IMSA_NULL;
    IMSA_MEM_SET(   pstEmcConn->astSipMediaPdpArray,
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM);

    /* ��ʼ����ͨ���� */
    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    IMSA_StopTimer(&pstNormalConn->stProtectTimer);



    pstNormalConn->enImsaConnStatus         = IMSA_CONN_STATUS_IDLE;
    pstNormalConn->enFirstReqPdnType        = IMSA_IP_TYPE_BUTT;
    pstNormalConn->enCurReqPdnType          = IMSA_IP_TYPE_BUTT;
    pstNormalConn->stProtectTimer.phTimer   = VOS_NULL_PTR;
    pstNormalConn->ucCurMaxOpid             = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;
    pstNormalConn->ucOpid                   = IMSA_NULL;
    pstNormalConn->ulSipSignalPdpNum        = IMSA_NULL;
    IMSA_MEM_SET(   pstNormalConn->astSipSignalPdpArray,
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);

    pstNormalConn->ulSipMediaPdpNum        = IMSA_NULL;
    IMSA_MEM_SET(   pstNormalConn->astSipMediaPdpArray,
                    0x0,
                    sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM);

    /* ��NIC PDP INFO�д洢�ĳ��غ�֪ͨTTFɾ�� */
    IMSA_CONN_DeletePdpId2Nic();

    /* ����洢���ø�NIC��PDP��Ϣ*/
    IMSA_CONN_ClearNicPdpInfo();

    return ;
}



VOS_VOID IMSA_CONN_AssignOpid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                          *pucOpid
)
{
    VOS_UINT8                           ucOpid = IMSA_NULL;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        /*��ȡ��ǰ���OPID*/
        ucOpid = IMSA_CONN_GetNormalConnCurMaxOpid();

        /*�����δ�����ֵ��ֱ�Ӽ�1*/
        if( ucOpid < IMSA_CONN_NORMAL_CONN_MAX_OPID_VALUE)
        {
            *pucOpid = ucOpid + 1;
        }
        else/*����Ѿ������ֵ���ӳ�ֵ��ʼ����*/
        {
            (*pucOpid) = IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE;
        }

        IMSA_CONN_SetNormalConnCurMaxOpid(*pucOpid);

        IMSA_INFO_LOG1("IMSA_CONN_AssignOpid,normal,assin opid:", (*pucOpid));
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_AssignOpid_ENUM, IMSA_NORMAL_OPID, (*pucOpid));
    }
    else
    {
        /*��ȡ��ǰ���OPID*/
        ucOpid = IMSA_CONN_GetEmcConnCurMaxOpid();

        /*�����δ�����ֵ��ֱ�Ӽ�1*/
        if( ucOpid < IMSA_CONN_EMC_CONN_MAX_OPID_VALUE)
        {
            *pucOpid = ucOpid + 1;
        }
        else/*����Ѿ������ֵ���ӳ�ֵ��ʼ����*/
        {
            (*pucOpid) = IMSA_CONN_EMC_CONN_MIN_OPID_VALUE;
        }

        IMSA_CONN_SetEmcConnCurMaxOpid(*pucOpid);

        IMSA_INFO_LOG1("IMSA_CONN_AssignOpid,emc,assin opid:", (*pucOpid));
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_AssignOpid_ENUM, IMSA_EMERGENCY_OPID, (*pucOpid));
    }
}



VOS_UINT32 IMSA_CONN_GetConnTypeByOpid
(
    VOS_UINT8                           ucOpid,
    IMSA_CONN_TYPE_ENUM_UINT32         *penConnType
)
{
    if (ucOpid == IMSA_CONN_GetNormalConnOpid())
    {
        *penConnType = IMSA_CONN_TYPE_NORMAL;
        return IMSA_SUCC;
    }

    if (ucOpid == IMSA_CONN_GetEmcConnOpid())
    {
        *penConnType = IMSA_CONN_TYPE_EMC;
        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}


IMSA_PDP_STATE_ENUM_UINT8 IMSA_CONN_GetSipSignalPdpState
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && (enIpType == pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType))
        {
            return IMSA_PDP_STATE_ACTIVE;
        }

        return IMSA_PDP_STATE_INACTIVE;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();
    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState)
            && (enIpType == pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType))
        {
            return IMSA_PDP_STATE_ACTIVE;
        }
    }

    return IMSA_PDP_STATE_INACTIVE;
}


VOS_UINT32 IMSA_CONN_IsConnStatusEqual
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatusTmp = IMSA_CONN_STATUS_BUTT;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enImsaConnStatusTmp = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enImsaConnStatusTmp = IMSA_CONN_GetEmcConnStatus();
    }

    if (enImsaConnStatus == enImsaConnStatusTmp)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}


VOS_VOID IMSA_CONN_ClearConnResource
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

        IMSA_StopTimer(&pstEmcConn->stProtectTimer);
        pstEmcConn->enCurReqPdnType     = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enFirstReqPdnType   = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enImsaConnStatus    = IMSA_CONN_STATUS_IDLE;
        pstEmcConn->ucOpid              = IMSA_CONN_ILLEGAL_OPID;
        IMSA_MEM_SET(                   &pstEmcConn->stSelSdfPara,
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));

        IMSA_MEM_SET(                   &pstEmcConn->stSipSignalPdp,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU));

        pstEmcConn->ulSipMediaPdpNum    = 0;
        IMSA_MEM_SET(                   pstEmcConn->astSipMediaPdpArray,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM);
    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();
        IMSA_StopTimer(&pstNormalConn->stProtectTimer);
        pstNormalConn->enCurReqPdnType  = IMSA_IP_TYPE_BUTT;
        pstNormalConn->enFirstReqPdnType= IMSA_IP_TYPE_BUTT;
        pstNormalConn->enImsaConnStatus = IMSA_CONN_STATUS_IDLE;
        pstNormalConn->ucOpid           = IMSA_CONN_ILLEGAL_OPID;
        IMSA_MEM_SET(                   &pstNormalConn->stSelSdfPara,
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));
        pstNormalConn->ulSipSignalPdpNum= 0;
        IMSA_MEM_SET(                   pstNormalConn->astSipSignalPdpArray,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);
        pstNormalConn->ulSipMediaPdpNum = 0;
        IMSA_MEM_SET(                   pstNormalConn->astSipMediaPdpArray,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM);
    }
}


VOS_VOID IMSA_CONN_ClearConnResourceExeptMedia
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

        IMSA_StopTimer(&pstEmcConn->stProtectTimer);
        pstEmcConn->enCurReqPdnType     = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enFirstReqPdnType   = IMSA_IP_TYPE_BUTT;
        pstEmcConn->enImsaConnStatus    = IMSA_CONN_STATUS_IDLE;
        pstEmcConn->ucOpid              = IMSA_CONN_ILLEGAL_OPID;
        IMSA_MEM_SET(                   &pstEmcConn->stSelSdfPara,
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));

        IMSA_MEM_SET(                   &pstEmcConn->stSipSignalPdp,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();
        IMSA_StopTimer(&pstNormalConn->stProtectTimer);
        pstNormalConn->enCurReqPdnType  = IMSA_IP_TYPE_BUTT;
        pstNormalConn->enFirstReqPdnType= IMSA_IP_TYPE_BUTT;
        pstNormalConn->enImsaConnStatus = IMSA_CONN_STATUS_IDLE;
        pstNormalConn->ucOpid           = IMSA_CONN_ILLEGAL_OPID;
        IMSA_MEM_SET(                   &pstNormalConn->stSelSdfPara,
                                        0x0,
                                        sizeof(IMSA_SEL_SDF_PARA_STRU));
        pstNormalConn->ulSipSignalPdpNum= 0;
        IMSA_MEM_SET(                   pstNormalConn->astSipSignalPdpArray,
                                        0x0,
                                        sizeof(IMSA_PDP_CNTXT_INFO_STRU)*IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM);
    }
}


VOS_UINT32 IMSA_CONN_HasActiveSipSignalPdp
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

        if (IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
        {
            return IMSA_TRUE;
        }
        else
        {
            return IMSA_FALSE;
        }
    }
    else
    {
        pstNormalConn = IMSA_CONN_GetNormalConnAddr();

        if (0 != pstNormalConn->ulSipSignalPdpNum)
        {
            return IMSA_TRUE;
        }
        else
        {
            return IMSA_FALSE;
        }
    }
}

VOS_UINT32 IMSA_CONN_HasActiveVoicePdp
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32                          ulSipMediaPdpNum = IMSA_NULL;
    IMSA_ENTITY_STRU                   *pstImsaEntity = IMSA_CtxGet();
    VOS_UINT32                          ulPfNum = IMSA_NULL;
    VOS_UINT16                          usImsMinPort;
    VOS_UINT16                          usImsMaxPort;

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    usImsMinPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    for (ulSipMediaPdpNum = 0; ulSipMediaPdpNum < pstNormalConn->ulSipMediaPdpNum; ulSipMediaPdpNum ++)
    {
        for (ulPfNum = 0; ulPfNum < pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.ulPfNum; ulPfNum++)
        {
            /* ������ڶ�����й�������ֻ��Ҫ�ж�һ���������ı��ض˿� */
            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort >= usImsMinPort)&&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort <= usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpLocalPortRange) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortLowLimit >= usImsMinPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortHighLimit <= usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if (IMSA_VOICE_QCI == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stEpsQos.ucQCI)
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}
VOS_UINT32 IMSA_CONN_HasActiveVideoPdp
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32                          ulSipMediaPdpNum = IMSA_NULL;
    IMSA_ENTITY_STRU                   *pstImsaEntity = IMSA_CtxGet();
    VOS_UINT32                          ulPfNum = IMSA_NULL;
    VOS_UINT16                          usImsMinPort;
    VOS_UINT16                          usImsMaxPort;

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    usImsMinPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    for (ulSipMediaPdpNum = 0; ulSipMediaPdpNum < pstNormalConn->ulSipMediaPdpNum; ulSipMediaPdpNum ++)
    {
        for (ulPfNum = 0; ulPfNum < pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.ulPfNum; ulPfNum++)
        {
            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
                ((pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort < usImsMinPort)  ||
                 (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usSingleLcPort > usImsMaxPort)))
            {
                return IMSA_TRUE;
            }

            if ((IMSA_OP_TRUE == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].bitOpLocalPortRange) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortLowLimit < usImsMinPort) &&
                (pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stTft.astTftInfo[ulPfNum].usLcPortHighLimit > usImsMaxPort))
            {
                return IMSA_TRUE;
            }

            if (IMSA_VIDEO_QCI == pstNormalConn->astSipMediaPdpArray[ulSipMediaPdpNum].stEpsQos.ucQCI)
            {
                return IMSA_TRUE;
            }
        }
    }
    return IMSA_FALSE;
}



VOS_UINT32 IMSA_CONN_GetPdpContextByPdpId
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucPdpId,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn          = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && ((ucPdpId == pstEmcConn->stSipSignalPdp.ucPdpId)))
        {
            *ppstPdpContext = &pstEmcConn->stSipSignalPdp;
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;

            return IMSA_SUCC;
        }

        for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
        {
            if ((ucPdpId == pstEmcConn->astSipMediaPdpArray[i].ucPdpId)
                && (IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState))
            {
                *ppstPdpContext = &pstEmcConn->astSipMediaPdpArray[i];
                *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((ucPdpId == pstNormalConn->astSipSignalPdpArray[i].ucPdpId)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipSignalPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
            return IMSA_SUCC;
        }
    }

    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((ucPdpId == pstNormalConn->astSipMediaPdpArray[i].ucPdpId)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipMediaPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}


VOS_UINT32 IMSA_CONN_GetPdpContextByCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32 *penSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU          **ppstPdpContext
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn          = IMSA_CONN_GetEmcConnAddr();

        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
            && ((ucCid == pstEmcConn->stSipSignalPdp.ucCid)))
        {
            *ppstPdpContext = &pstEmcConn->stSipSignalPdp;
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;

            return IMSA_SUCC;
        }

        for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
        {
            if ((ucCid == pstEmcConn->astSipMediaPdpArray[i].ucCid)
                && (IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState))
            {
                *ppstPdpContext = &pstEmcConn->astSipMediaPdpArray[i];
                *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
                return IMSA_SUCC;
            }
        }

        return IMSA_FAIL;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((ucCid == pstNormalConn->astSipSignalPdpArray[i].ucCid)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipSignalPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
            return IMSA_SUCC;
        }
    }

    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((ucCid == pstNormalConn->astSipMediaPdpArray[i].ucCid)
            && (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState))
        {
            *ppstPdpContext = &pstNormalConn->astSipMediaPdpArray[i];
            *penSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
            return IMSA_SUCC;
        }
    }

    return IMSA_FAIL;
}


VOS_UINT32 IMSA_CONN_GetTimerLen
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    if (TI_IMSA_SIP_SIGAL_PDP_ORIG == enTimerId)
    {
        if (IMSA_CONN_TYPE_NORMAL == enConnType)
        {
            return TI_IMSA_NRM_SIP_SIGAL_PDP_ORIG_TIMER_LEN;
        }
        else
        {
            return TI_IMSA_EMC_SIP_SIGAL_PDP_ORIG_TIMER_LEN;
        }
    }

    if (TI_IMSA_SIP_SIGAL_PDP_END == enTimerId)
    {
        return TI_IMSA_SIP_SIGAL_PDP_END_TIMER_LEN;
    }

    if (TI_IMSA_WAIT_IPV6_INFO == enTimerId)
    {
        return TI_IMSA_WAIT_IPV6_INFO_TIMER_LEN;
    }

    return 0;
}


VOS_VOID IMSA_CONN_StartTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    VOS_UINT32                          ulTimerLen      = IMSA_NULL;
    IMSA_TIMER_STRU                    *pstProtectImer  = VOS_NULL_PTR;

    /* ��ȡ��ʱ��ʱ�� */
    ulTimerLen                  = IMSA_CONN_GetTimerLen(enConnType, enTimerId);

    IMSA_INFO_LOG2("IMSA_CONN_StartTimer:enConnType:Timer Len:", enConnType, ulTimerLen);
    TLPS_PRINT2LAYER_INFO2(IMSA_CONN_StartTimer_ENUM, 1, enConnType, ulTimerLen);

    if (IMSA_CONN_TYPE_NORMAL   == enConnType)
    {
        pstProtectImer          = IMSA_CONN_GetNormalConnProtectTimerAddr();

    }
    else
    {
        pstProtectImer          = IMSA_CONN_GetEmcConnProtectTimerAddr();
    }

    /* ��ֵ��ʱ������ */
    pstProtectImer->ulTimerLen  = ulTimerLen;
    pstProtectImer->usName      = enTimerId;
    pstProtectImer->usPara      = (VOS_UINT16)enConnType;
    pstProtectImer->ucMode      = VOS_RELTIMER_NOLOOP;

    IMSA_StartTimer(pstProtectImer);
}


VOS_VOID IMSA_CONN_StopTimer
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    IMSA_TIMER_STRU                    *pstProtectImer  = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_NORMAL   == enConnType)
    {
        pstProtectImer          = IMSA_CONN_GetNormalConnProtectTimerAddr();

    }
    else
    {
        pstProtectImer          = IMSA_CONN_GetEmcConnProtectTimerAddr();
    }

    if (pstProtectImer->usName == enTimerId)
    {
        IMSA_StopTimer(pstProtectImer);
    }
}


VOS_VOID IMSA_CONN_SetConnStatus
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus
)
{
    /* ��ȡ����ԭ״̬ */

    /* ��ӡ�������� */

    /* ��ӡ����״̬�������Ϣ */

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        IMSA_CONN_GetNormalConnStatus() = enConnStatus;
    }
    else
    {
        IMSA_CONN_GetEmcConnStatus()    = enConnStatus;
    }
}
VOS_VOID IMSA_CONN_SaveFirstReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;

    /* ��ȡPRIM PDP�����ĸ�ʽ */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        pstNormalConn->enFirstReqPdnType= enIpType;
    }
    else
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();
        pstEmcConn->enFirstReqPdnType   = enIpType;
    }
}
VOS_VOID IMSA_CONN_SaveCurReqPdnType
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_IP_TYPE_ENUM_UINT8             enIpType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;

    /* ��ȡPRIM PDP�����ĸ�ʽ */
    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
        pstNormalConn->enCurReqPdnType  = enIpType;
    }
    else
    {
        pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();
        pstEmcConn->enCurReqPdnType     = enIpType;
    }
}
VOS_UINT32 IMSA_CONN_IsImsSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if (((IMSA_OP_TRUE == pstSdfPara->bitOpImCnSignalFlg)
       && (TAF_PDP_FOR_IM_CN_SIG_ONLY == pstSdfPara->enImCnSignalFlg))
       ||((IMSA_OP_TRUE == pstSdfPara->bitOpImsSuppFlg)
       && (IMSA_TRUE == pstSdfPara->ucImsSuppFlg)))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_CONN_IsPndTypeValid
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if ((IMSA_OP_TRUE == pstSdfPara->bitOpPdnType)
       && (TAF_PDP_IPV4 <= pstSdfPara->enPdnType)
       && (TAF_PDP_IPV4V6 >= pstSdfPara->enPdnType))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_CONN_IsEmcSdf
(
     const TAF_SDF_PARA_STRU            *pstSdfPara
)
{
    if ((IMSA_OP_TRUE == pstSdfPara->bitOpEmergencyInd)
       && (TAF_PDP_FOR_EMC == pstSdfPara->enEmergencyInd))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_CONN_FindSipSignalReStablishDialPara
(
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = IMSA_NULL;

    if (ulSdfNum == 0)
    {
        IMSA_ERR_LOG("IMSA_CONN_FindSipSignalReStablishDialPara:No Sdf!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_FindSipSignalReStablishDialPara_ENUM, 1);
        return IMSA_FAIL;
    }

    for (i = 0; i < ulSdfNum; i++)
    {
        if (ucCid == pstSdfPara[i].ucCid)
        {
            *pulIndex = i;

            return IMSA_SUCC;
        }
    }
    return IMSA_FAIL;
}



VOS_UINT32 IMSA_CONN_FindSipSignalDialPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT32                          ulSdfNum,
    const TAF_SDF_PARA_STRU            *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = IMSA_NULL;

    if (ulSdfNum == 0)
    {
        IMSA_ERR_LOG("IMSA_CONN_FindSipSignalDialPara:No Sdf!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_FindSipSignalDialPara_ENUM, 1);
        return IMSA_FAIL;
    }

    /* ��ͨ����ѡ�����TAF_PDP_FOR_IMS_CN_SIG_ONLY��ʶ��PDN���ͺ�APN������
       �Ҳ����Ϸ���Ч��CID����������ѡ�����TAF_PDP_FOR_IMS_CN_SIG_ONLY��ʶ
       ��TAF_PDP_FOR_EMC��PDN���ͺ�APN�������Ҳ����Ϸ���Ч��CID */
    for (i = 0; i < ulSdfNum; i++)
    {
        if (IMSA_OP_TRUE == pstSdfPara[i].bitOpLinkdCid)
        {
            continue;
        }

        if (IMSA_TRUE != IMSA_CONN_IsImsSdf(&pstSdfPara[i]))
        {
            continue;
        }

        if (IMSA_TRUE != IMSA_CONN_IsPndTypeValid(&pstSdfPara[i]))
        {
            continue;
        }

        if (IMSA_CONN_TYPE_EMC == enConnType)
        {
            if (IMSA_TRUE != IMSA_CONN_IsEmcSdf(&pstSdfPara[i]))
            {
                continue;
            }
        }
        else/* �������ͨ���ͣ���ѡ���н�����ʶ��CID */
        {
            if (IMSA_OP_TRUE != pstSdfPara[i].bitOpApn)
            {
                continue;
            }

            if (IMSA_TRUE == IMSA_CONN_IsEmcSdf(&pstSdfPara[i]))
            {
                continue;
            }
        }

        *pulIndex = i;

        return IMSA_SUCC;
    }

    return IMSA_FAIL;
}
VOS_VOID IMSA_CONN_SaveSelectedSdfPara
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const TAF_SDF_PARA_STRU            *pstTafSdfPara
)
{
    IMSA_SEL_SDF_PARA_STRU             *pstSelSdfPara = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstSelSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }
    else
    {
        pstSelSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }

    IMSA_MEM_SET(pstSelSdfPara, 0x0, sizeof(IMSA_SEL_SDF_PARA_STRU));

    pstSelSdfPara->ucCid                    = pstTafSdfPara->ucCid;

    pstSelSdfPara->bitOpLinkdCid            = pstTafSdfPara->bitOpLinkdCid;
    pstSelSdfPara->ucLinkdCid               = pstTafSdfPara->ucLinkdCid;

    pstSelSdfPara->bitOpPdnType             = pstTafSdfPara->bitOpPdnType;
    pstSelSdfPara->enPdnType                = pstTafSdfPara->enPdnType;

    pstSelSdfPara->bitOpApn = pstTafSdfPara->bitOpApn;
    IMSA_MEM_CPY(   &pstSelSdfPara->stApnInfo,
                    &pstTafSdfPara->stApnInfo,
                    sizeof(TAF_PDP_APN_STRU));

    pstSelSdfPara->bitOpGwAuthInfo = pstTafSdfPara->bitOpGwAuthInfo;
    IMSA_MEM_CPY(   &pstSelSdfPara->stGwAuthInfo,
                    &pstTafSdfPara->stGwAuthInfo,
                    sizeof(TAF_GW_AUTH_STRU));

    pstSelSdfPara->bitOpEmergencyInd        = pstTafSdfPara->bitOpEmergencyInd;
    pstSelSdfPara->enEmergencyInd           = pstTafSdfPara->enEmergencyInd;

    pstSelSdfPara->bitOpIpv4AddrAllocType   = pstTafSdfPara->bitOpIpv4AddrAllocType;
    pstSelSdfPara->enIpv4AddrAllocType      = pstTafSdfPara->enIpv4AddrAllocType;

    pstSelSdfPara->bitOpPcscfDiscovery      = pstTafSdfPara->bitOpPcscfDiscovery;
    pstSelSdfPara->enPcscfDiscovery         = pstTafSdfPara->enPcscfDiscovery;

    pstSelSdfPara->bitOpImCnSignalFlg       = pstTafSdfPara->bitOpImCnSignalFlg;
    pstSelSdfPara->enImCnSignalFlg          = pstTafSdfPara->enImCnSignalFlg;

    pstSelSdfPara->bitOpImsSuppFlg          = pstTafSdfPara->bitOpImsSuppFlg;
    pstSelSdfPara->ucImsSuppFlg             = pstTafSdfPara->ucImsSuppFlg;
}


VOS_VOID IMSA_CONN_GetPrimPdpCntFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    IMSA_MEM_SET(                       (VOS_VOID *)pstPdpPrimContextExt,
                                        0x00,
                                        sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstPdpPrimContextExt->ucCid         = pstSelectedSdfPara->ucCid;
    pstPdpPrimContextExt->ucDefined     = 1;

    /* ��ֵPDN TYPE */
    pstPdpPrimContextExt->bitOpPdpType  = pstSelectedSdfPara->bitOpPdnType;
    pstPdpPrimContextExt->enPdpType     = pstSelectedSdfPara->enPdnType;

    /* ��ֵAPN */
    pstPdpPrimContextExt->bitOpApn      = pstSelectedSdfPara->bitOpApn;
    IMSA_MEM_CPY(                       (VOS_CHAR*)pstPdpPrimContextExt->aucApn,
                                        (VOS_CHAR*)pstSelectedSdfPara->stApnInfo.aucValue,
                                        pstSelectedSdfPara->stApnInfo.ucLength);

    /* ��ֵIpv4AddrAlloc */
    pstPdpPrimContextExt->bitOpIpv4AddrAlloc    = pstSelectedSdfPara->bitOpIpv4AddrAllocType;
    pstPdpPrimContextExt->enIpv4AddrAlloc       = pstSelectedSdfPara->enIpv4AddrAllocType;

    /* ��ֵ������ʶ */
    pstPdpPrimContextExt->bitOpEmergencyInd     = pstSelectedSdfPara->bitOpEmergencyInd;
    pstPdpPrimContextExt->enEmergencyFlg        = pstSelectedSdfPara->enEmergencyInd;

    /* ��ֵP-CSCF���ַ�ʽ */
    pstPdpPrimContextExt->bitOpPcscfDiscovery   = pstSelectedSdfPara->bitOpPcscfDiscovery;
    pstPdpPrimContextExt->enPcscfDiscovery      = pstSelectedSdfPara->enPcscfDiscovery;

    /* ��ֵIMS��ʶ */
    pstPdpPrimContextExt->bitOpImCnSignalFlg    = pstSelectedSdfPara->bitOpImCnSignalFlg;
    pstPdpPrimContextExt->enImCnSignalFlg       = pstSelectedSdfPara->enImCnSignalFlg;
}



VOS_VOID IMSA_CONN_GetImsDailParaFromSelSdfPara
(
    const IMSA_SEL_SDF_PARA_STRU       *pstSelectedSdfPara,
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo
)
{
    IMSA_MEM_SET(pstDialParaInfo, 0, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstDialParaInfo->ucCid                  = pstSelectedSdfPara->ucCid;
    pstDialParaInfo->enPdpType              = pstSelectedSdfPara->enPdnType;

    /* ��ֵAPN��Ϣ */
    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpApn)
    {
        pstDialParaInfo->bitOpApn           = IMSA_OP_TRUE;

        /* ����APN����û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
        IMSA_MEM_CPY(                       pstDialParaInfo->aucApn,
                                            pstSelectedSdfPara->stApnInfo.aucValue,
                                            pstSelectedSdfPara->stApnInfo.ucLength);
    }

    /* ��ֵ��Ȩ���� */
    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpGwAuthInfo)
    {
        pstDialParaInfo->bitOpAuthType      = IMSA_OP_TRUE;
        pstDialParaInfo->enAuthType         = pstSelectedSdfPara->stGwAuthInfo.enAuthType;

        if (pstSelectedSdfPara->stGwAuthInfo.ucUserNameLen != 0)
        {
            pstDialParaInfo->bitOpUserName  = IMSA_OP_TRUE;

            /* �����û�������û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
            IMSA_MEM_CPY(                   pstDialParaInfo->aucUserName,
                                            pstSelectedSdfPara->stGwAuthInfo.aucUserName,
                                            pstSelectedSdfPara->stGwAuthInfo.ucUserNameLen);
        }

        if (pstSelectedSdfPara->stGwAuthInfo.ucPwdLen       != 0)
        {
            pstDialParaInfo->bitOpPassWord  = IMSA_OP_TRUE;

            /* �����������û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
            IMSA_MEM_CPY(                   pstDialParaInfo->aucPassWord,
                                            pstSelectedSdfPara->stGwAuthInfo.aucPwd,
                                            pstSelectedSdfPara->stGwAuthInfo.ucPwdLen);
        }
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpIpv4AddrAllocType)
    {
        pstDialParaInfo->bitOpIpv4AddrAlloc = IMSA_OP_TRUE;
        pstDialParaInfo->enIpv4AddrAlloc = pstSelectedSdfPara->enIpv4AddrAllocType;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpEmergencyInd)
    {
        pstDialParaInfo->bitOpEmergencyInd = IMSA_OP_TRUE;
        pstDialParaInfo->enEmergencyInd = pstSelectedSdfPara->enEmergencyInd;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpPcscfDiscovery)
    {
        pstDialParaInfo->bitOpPcscfDiscovery = IMSA_OP_TRUE;
        pstDialParaInfo->enPcscfDiscovery = pstSelectedSdfPara->enPcscfDiscovery;
    }

    if (IMSA_OP_TRUE == pstSelectedSdfPara->bitOpImCnSignalFlg)
    {
        pstDialParaInfo->bitOpImCnSignalFlg = IMSA_OP_TRUE;
        pstDialParaInfo->enImCnSignalFlg = pstSelectedSdfPara->enImCnSignalFlg;
    }

    pstDialParaInfo->bitOpReqType = IMSA_OP_FALSE;
    pstDialParaInfo->bitOpPdpDcomp = IMSA_OP_FALSE;
    pstDialParaInfo->bitOpPdpHcomp = IMSA_OP_FALSE;

}
VOS_VOID IMSA_CONN_ConvertIpAddress2String
(
    IMSA_IP_TYPE_ENUM_UINT8             enIpType,
    const VOS_UINT8                    *pucSrc,
    VOS_CHAR                           *pcDst
)
{
#if (VOS_OS_VER != VOS_WIN32)
#if (VOS_OS_VER == VOS_VXWORKS)
/*lint -e718 -e746 -e40 */
    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        inet_ntop(AF_INET, pucSrc , pcDst, 16);
    }
    else
    {
        inet_ntop(AF_INET6, pucSrc , pcDst, 46);
    }
/*lint +e718 +e746 +e40 */
#else
/*lint -e64*/
    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        (VOS_VOID)vrp_inet_ntop(VRP_AF_INET, (const CHAR *)pucSrc , pcDst, 16);
    }
    else
    {
        (VOS_VOID)vrp_inet_ntop(VRP_AF_INET6, (const CHAR *)pucSrc , pcDst, 46);
    }
/*lint +e64*/
#endif
#else
    VOS_UINT8                           i = 0;

    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        /* ST�е�IPV6��ַ��IPV6���͵�P-CSCF��ַ�����һ���ֽڱ�����[0,9] */
        IMSA_MEM_CPY(pcDst, g_acIpStringForSt_ipv4, (IMSA_IPV4_ADDR_STRING_LEN + 1));
        i = strlen(g_acIpStringForSt_ipv4) - 1;
        pcDst[i] = pucSrc[3] + 0x30;
        /*g_acIpStringForSt_ipv4[i] ++ ;*/
    }
    else
    {
        /* ST�е�IPV6��ַ��IPV6���͵�P-CSCF��ַ�����һ���ֽڱ����Ǵ��ڵ���16 */
        IMSA_MEM_CPY(pcDst, g_acIpStringForSt_ipv6, (IMSA_IPV6_ADDR_STRING_LEN + 1));
        i = strlen(g_acIpStringForSt_ipv6) - 1;
        pcDst[i] = (pucSrc[15] - 16) + 0x30;
        /*g_acIpStringForSt_ipv6[i] ++ ;*/
    }

#endif
}



VOS_UINT32 IMSA_CONN_FilterRegedPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext
)
{
    VOS_CHAR                            acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt          = IMSA_FAIL;

    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);

    /* ���δ��ȡ��ע���ϵĲ�������ֱ�ӷ��ز����� */
    if (IMSA_FAIL == ulRslt)
    {
        return IMSA_FALSE;
    }

    if ((IMSA_IP_TYPE_IPV4 == enIpType) || (IMSA_IP_TYPE_IPV4V6 == enIpType))
    {
        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpSecPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv4Pcscf.bitOpThiPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == enIpType) || (IMSA_IP_TYPE_IPV4V6 == enIpType))
    {
        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpSecPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }

        if (IMSA_OP_TRUE == pstPdpContext->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpContext->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);
            if (0 == VOS_StrCmp(acRegPcscfAddr, acUeAddr))
            {
                pstPdpContext->stPdpIpv6Pcscf.bitOpThiPcscfAddr = IMSA_OP_FALSE;
                return IMSA_TRUE;
            }
        }
    }

    return IMSA_FALSE;
}
VOS_VOID IMSA_CONN_DeletePcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {

        /* ɾ��IPV4 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ɾ��IPV6 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }
    }
}

VOS_VOID IMSA_CONN_ConfigPcscfInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV4 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV6 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

    }
}


VOS_VOID IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
)
{
    IMSA_PDP_CNTXT_INFO_STRU            *pstPdpContextOldTemp = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU            *pstPdpContextNewTemp = VOS_NULL_PTR;

    pstPdpContextOldTemp = IMSA_MEM_ALLOC(sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    if (VOS_NULL_PTR == pstPdpContextOldTemp)
    {
        return;
    }

    pstPdpContextNewTemp = IMSA_MEM_ALLOC(sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    if (VOS_NULL_PTR == pstPdpContextNewTemp)
    {
        IMSA_MEM_FREE(pstPdpContextOldTemp);
        return;
    }

    IMSA_MEM_SET(pstPdpContextOldTemp, 0x0, sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    IMSA_MEM_SET(pstPdpContextNewTemp, 0x0, sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    IMSA_MEM_CPY(pstPdpContextOldTemp, pstPdpContextOld, sizeof(IMSA_PDP_CNTXT_INFO_STRU));
    IMSA_MEM_CPY(pstPdpContextNewTemp, pstPdpContext, sizeof(IMSA_PDP_CNTXT_INFO_STRU));

    /* ��ԭ�б��ݵĳ�����Ϣ�й��˳���ע���PCSCF��ַ��
       ����δע���PCSCF��ַɾ�� */
    if (IMSA_TRUE == IMSA_CONN_FilterRegedPcscfInfo(enConnType, pstPdpContextOldTemp))
    {
        IMSA_CONN_DeletePcscfInfo2Reg(enConnType, pstPdpContextOldTemp);
    }

    /* ���޸ĳ�����Ϣ�й��˳�����ע���PCSCF��ַ��ͬ�ĵ�ַ��Ϣ��
       ��������PCSCF��ַ��ɵ�ַ�� */
    if (IMSA_TRUE == IMSA_CONN_FilterRegedPcscfInfo(enConnType, pstPdpContextNewTemp))
    {
        IMSA_CONN_ConfigPcscfInfo2Reg(enConnType, pstPdpContextNewTemp);
    }

    IMSA_MEM_FREE(pstPdpContextOldTemp);
    IMSA_MEM_FREE(pstPdpContextNewTemp);

    return;
}


VOS_VOID IMSA_CONN_ProcPcscfInvalid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContext,
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpContextOld
)
{
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt   = IMSA_FAIL;
    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    /* ��ȡע�����IP���� */
    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);
    if (IMSA_FAIL == ulRslt)
    {
        return ;
    }

    if ((IMSA_IP_TYPE_IPV4V6 != pstPdpContext->stPdpAddr.enIpType) &&
        (enIpType != pstPdpContext->stPdpAddr.enIpType))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcPcscfInvalid:IP TYPE NOT MATCH!");

        /* ע�����IP�������µĳ�����ϢIP���Ͳ�һ�£�ֻ�����µĵ�ַ��
           ����Ҫ��ʶ��ע������Ƿ�ʧЧ */

        /* ����REGģ��ɾ���޸ĳ��ص�IP��ַ��P-CSCF��ַ */
        IMSA_CONN_DeletePdpInfo2Reg(enConnType, pstPdpContextOld);

        /* ��REGģ�����õ�ַ�� */
        IMSA_CONN_ConfigPdpInfo2Reg(enConnType, pstPdpContext);
        return ;
    }

    /* �����ע�����IP�������µĳ�����ϢIP����һ�£���Ҫʶ��ע������Ƿ�ʧЧ */
    if (IMSA_FALSE == IMSA_CONN_IsPdpInfoIncludeRegPara(enConnType, pstPdpContext))
    {
        /* ����REGģ��ɾ���޸ĳ��ص�IP��ַ��P-CSCF��ַ */
        IMSA_CONN_DeletePdpInfo2Reg(enConnType, pstPdpContextOld);

        /* ��REGģ�����õ�ַ�� */
        IMSA_CONN_ConfigPdpInfo2Reg(enConnType, pstPdpContext);

        /* ��CONNģ�鷢��MODIFY��Ϣ������Ϊע���ַʧЧ */
        IMSA_CONN_SndConnRegPcscfInvalid(enConnType);
    }
    else
    {
        /* ע�����û��ʧЧ�������ݳ�����Ϣ�з�ע�������PCSCFɾ����
           ���µĳ�����Ϣ�з�ע�������PCSCF���óɵ�ַ�� */
        IMSA_CONN_DeleteOldPcscfInfoAndConfigNewPcscfInfo(enConnType, pstPdpContext, pstPdpContextOld);
    }
}


VOS_VOID IMSA_CONN_ConfigPdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT8                   aucTemp[IMSA_IPV6_PREFIX_LEN]           = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV4��ַ */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV4,
                                                acUeAddr);

        /* ����IPV4 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV6��ַ */
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                    IMSA_IP_TYPE_IPV6,
                                                    acUeAddr);
        }

        /* ����IPV6 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrAddPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        IMSA_PCSCF_SRC_TYPE_PDN,
                                                        acUeAddr);
        }
    }
}


VOS_VOID IMSA_CONN_DeletePdpInfo2Reg
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ɾ��IPV4��ַ */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrRmvUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV4,
                                                acUeAddr);

        /* ɾ��IPV4 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                                pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV4,
                                                        acUeAddr);
        }



    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ɾ��IPV6��ַ */
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                            acUeAddr);

        (VOS_VOID)IMSA_RegAddrPairMgrRmvUeAddr( (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                IMSA_IP_TYPE_IPV6,
                                                acUeAddr);

        /* ɾ��IPV6 P-CSCF��ַ */
        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }

        if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
        {
            IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                                pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                                acUeAddr);

            (VOS_VOID)IMSA_RegAddrPairMgrRmvPcscfAddr(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                                        IMSA_IP_TYPE_IPV6,
                                                        acUeAddr);
        }
    }
}


VOS_UINT32 IMSA_CONN_PdnInfoNicConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConfigInfo)
{
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;

    IMSA_INFO_LOG("IMSA_CONN_PdnInfoNicConfig enter");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicConfig_ENUM, LNAS_ENTRY);
    IMSA_INFO_LOG1("IMSA_CONN_PdnInfoNicConfig ,usSockMaxPort=:", pstConfigInfo->stSockPortInfo.usSockMaxPort);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_PdnInfoNicConfig_ENUM, 1, pstConfigInfo->stSockPortInfo.usSockMaxPort);
    IMSA_INFO_LOG1("IMSA_CONN_PdnInfoNicConfig ,usSockMinPort=:", pstConfigInfo->stSockPortInfo.usSockMinPort);
    TLPS_PRINT2LAYER_INFO1(IMSA_CONN_PdnInfoNicConfig_ENUM, 2, pstConfigInfo->stSockPortInfo.usSockMinPort);

    ulRslt = IMS_NIC_PdnInfoConfig(pstConfigInfo);

    IMSA_INFO_LOG("IMSA_CONN_PdnInfoNicConfig leave");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdnInfoNicConfig_ENUM, LNAS_LEAVE);

    return ulRslt;
}


VOS_VOID IMSA_CONN_ConfigPdpIPv6Info2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConfigInfo                    = {0};
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager               = VOS_NULL_PTR;

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            IMSA_MEM_SET(&stConfigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));
            stConfigInfo.ucRabId     = pstPdpInfo->ucPdpId;
            stConfigInfo.enModemId   = MODEM_ID_0;

            /* ����IPV6��ַ */
            stConfigInfo.bitOpIpv6PdnInfo    = IMSA_OP_TRUE;
            stConfigInfo.stIpv6PdnInfo.ulBitPrefixLen = IMSA_IPV6_PREFIX_BIT_LEN;
            IMSA_MEM_CPY(   stConfigInfo.stIpv6PdnInfo.aucIpV6Addr,
                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN);

            /* ����IPV6 DNS��ַ */
            stConfigInfo.stIpv6PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv6Dns.bitOpPriDns;
            IMSA_MEM_CPY(   stConfigInfo.stIpv6PdnInfo.aucDnsPrimAddr,
                            pstPdpInfo->stPdpIpv6Dns.aucPriDns,
                            IMSA_IPV6_ADDR_LEN);

            stConfigInfo.stIpv6PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv6Dns.bitOpSecDns;
            IMSA_MEM_CPY(   stConfigInfo.stIpv6PdnInfo.aucDnsSecAddr,
                            pstPdpInfo->stPdpIpv6Dns.aucSecDns,
                            IMSA_IPV6_ADDR_LEN);

            /* ����IPջ�˿ںŷ�Χ */
            pstControlManager = IMSA_GetControlManagerAddress();
            stConfigInfo.bitOpSockPortInfo = IMSA_OP_TRUE;
            stConfigInfo.stSockPortInfo.usSockMinPort
                    = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
            stConfigInfo.stSockPortInfo.usSockMaxPort
                    = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

            ulRslt = IMSA_CONN_PdnInfoNicConfig(&stConfigInfo);
            if (IMS_NIC_SUCC != ulRslt)
            {
                IMSA_ERR_LOG1("IMS_NIC_PdnInfoConfig failed,result:", ulRslt);
                TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ConfigPdpIPv6Info2Bsp_ENUM, IMSA_CALL_API_ERROR, ulRslt);
            }
        }
    }
}
VOS_VOID IMSA_CONN_ConfigPdpInfo2Bsp
(
    const IMSA_PDP_CNTXT_INFO_STRU     *pstPdpInfo
)
{
    IMS_NIC_PDN_INFO_CONFIG_STRU        stConigInfo                     = {0};
    VOS_UINT32                          ulRslt                          = IMSA_FAIL;
    VOS_UINT8                           aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager               = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ConfigPdpInfo2Bsp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ConfigPdpInfo2Bsp_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET(&stConigInfo, 0, sizeof(IMS_NIC_PDN_INFO_CONFIG_STRU));

    stConigInfo.ucRabId     = pstPdpInfo->ucPdpId;
    stConigInfo.enModemId   = MODEM_ID_0;

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        /* ����IPV4��ַ */
        stConigInfo.bitOpIpv4PdnInfo    = IMSA_OP_TRUE;
        IMSA_MEM_CPY(   stConigInfo.stIpv4PdnInfo.aucIpV4Addr,
                        pstPdpInfo->stPdpAddr.aucIpV4Addr,
                        IMSA_IPV4_ADDR_LEN);

        /* ����IPV4 DNS��ַ */
        stConigInfo.stIpv4PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv4Dns.bitOpPriDns;
        IMSA_MEM_CPY(   stConigInfo.stIpv4PdnInfo.aucDnsPrimAddr,
                        pstPdpInfo->stPdpIpv4Dns.aucPriDns,
                        IMSA_IPV4_ADDR_LEN);

        stConigInfo.stIpv4PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv4Dns.bitOpSecDns;
        IMSA_MEM_CPY(   stConigInfo.stIpv4PdnInfo.aucDnsSecAddr,
                        pstPdpInfo->stPdpIpv4Dns.aucSecDns,
                        IMSA_IPV4_ADDR_LEN);
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (0 != IMSA_MEM_CMP(aucTemp, pstPdpInfo->stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            /* ����IPV6��ַ */
            stConigInfo.bitOpIpv6PdnInfo    = IMSA_OP_TRUE;
            stConigInfo.stIpv6PdnInfo.ulBitPrefixLen = IMSA_IPV6_PREFIX_BIT_LEN;
            IMSA_MEM_CPY(   stConigInfo.stIpv6PdnInfo.aucIpV6Addr,
                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                            IMSA_IPV6_ADDR_LEN);

            /* ����IPV6 DNS��ַ */
            stConigInfo.stIpv6PdnInfo.bitOpDnsPrim = pstPdpInfo->stPdpIpv6Dns.bitOpPriDns;
            IMSA_MEM_CPY(   stConigInfo.stIpv6PdnInfo.aucDnsPrimAddr,
                            pstPdpInfo->stPdpIpv6Dns.aucPriDns,
                            IMSA_IPV6_ADDR_LEN);

            stConigInfo.stIpv6PdnInfo.bitOpDnsSec = pstPdpInfo->stPdpIpv6Dns.bitOpSecDns;
            IMSA_MEM_CPY(   stConigInfo.stIpv6PdnInfo.aucDnsSecAddr,
                            pstPdpInfo->stPdpIpv6Dns.aucSecDns,
                            IMSA_IPV6_ADDR_LEN);
        }
    }

    if ((IMSA_OP_TRUE == stConigInfo.bitOpIpv4PdnInfo)
        || (IMSA_OP_TRUE == stConigInfo.bitOpIpv6PdnInfo))
    {
        pstControlManager = IMSA_GetControlManagerAddress();
        stConigInfo.bitOpSockPortInfo = IMSA_OP_TRUE;
        stConigInfo.stSockPortInfo.usSockMinPort
                = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
        stConigInfo.stSockPortInfo.usSockMaxPort
                = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

        ulRslt = IMSA_CONN_PdnInfoNicConfig(&stConigInfo);
        if (IMS_NIC_SUCC != ulRslt)
        {
            IMSA_ERR_LOG1("IMS_NIC_PdnInfoConfig failed,result:", ulRslt);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CONN_ConfigPdpInfo2Bsp_ENUM, IMSA_CALL_API_ERROR, ulRslt);
        }
    }
}


VOS_VOID IMSA_CONN_SaveSipSignalPdpInfo
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU    *pstPdpActivateCnf
)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    pstControlManager               = IMSA_GetControlManagerAddress();

    pstPdpInfo->ucPdpId             = pstPdpActivateCnf->ucRabId;
    pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
    if (IMSA_OP_TRUE == pstPdpActivateCnf->bitOpLinkdRabId)
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_DEDICATED;
    }
    else if ((IMSA_OP_TRUE == pstPdpActivateCnf->bitOpEmergencyInd) && (TAF_PDP_FOR_EMC == pstPdpActivateCnf->enEmergencyInd))
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_EMERGENCY;
    }
    else
    {
        pstPdpInfo->enPdpType = IMSA_PDP_TYPE_DEFAULT;
    }
    pstPdpInfo->ucCid               = pstPdpActivateCnf->ucCid;

    /* �洢IP��ַ */
    pstPdpInfo->bitOpPdpAddr        = pstPdpActivateCnf->bitOpPdpAddr;
    IMSA_MEM_CPY(                   &pstPdpInfo->stPdpAddr,
                                    &pstPdpActivateCnf->stPdpAddr,
                                    sizeof(IMSA_IP_ADDRESS_STRU));

    switch(pstControlManager->stPcscfDiscoveryPolicyInfo.enPcscfDiscoverPolicy)
    {
    case IMSA_PCSCF_DISCOVERY_POLICY_PCO:

        /* ͨ��PCO��ȡIPV4 P-CSCF */
        pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpSecPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr = pstPdpActivateCnf->stPcscf.bitOpThiPcscfAddr;

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr[0],
                                        &pstPdpActivateCnf->stPcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr[0],
                                        &pstPdpActivateCnf->stPcscf.aucSecPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr[0],
                                        &pstPdpActivateCnf->stPcscf.aucThiPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        /* ͨ��PCO��ȡIPV6 P-CSCF */
        pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpSecPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr = pstPdpActivateCnf->stIpv6Pcscf.bitOpThiPcscfAddr;

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr[0],
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr[0],
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr[0],
                                        &pstPdpActivateCnf->stIpv6Pcscf.aucThiPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo: IMSA_PCSCF_DISCOVERY_POLICY_PCO!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, 1);
        break;
    case IMSA_PCSCF_DISCOVERY_POLICY_NV:

        /* ͨ��NV���û�ȡIPV4 P-CSCF */
        pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.bitOpSecPcscfAddr;


        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr[0],
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr[0],
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV4_ADDR_LEN);

        /* ͨ��NV���û�ȡIPV6 P-CSCF */
        pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.bitOpPrimPcscfAddr;
        pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr = pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.bitOpSecPcscfAddr;

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr[0],
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.aucPrimPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr[0],
                                        &pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf.aucSecPcscfAddr[0],
                                        TAF_IPV6_ADDR_LEN);

        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo: IMSA_PCSCF_DISCOVERY_POLICY_NV!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, 2);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CONN_SaveSipSignalPdpInfo:P-CSCF policy error!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveSipSignalPdpInfo_ENUM, LNAS_ERROR);
        break;
    }

    /* �洢IPV4 DNS */
    IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv4Dns,
                                    &pstPdpActivateCnf->stDns,
                                    sizeof(IMSA_PDP_IPV4_DNS_STRU));

    /* �洢IPV6 DNS */
    IMSA_MEM_CPY(                   &pstPdpInfo->stPdpIpv6Dns,
                                    &pstPdpActivateCnf->stIpv6Dns,
                                    sizeof(IMSA_PDP_IPV6_DNS_STRU));

    /* �洢EPS QOS */
    IMSA_MEM_CPY(                   &pstPdpInfo->stEpsQos,
                                    &pstPdpActivateCnf->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU));

}


VOS_VOID IMSA_CONN_SaveSipMediaPdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32                  enConnType,
    const TAF_PS_CALL_PDP_ACTIVATE_IND_STRU    *pstPdpActivateInd
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn       = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn          = VOS_NULL_PTR;
    IMSA_PDP_CNTXT_INFO_STRU           *pstPdpInfo          = VOS_NULL_PTR;

    pstNormalConn                   = IMSA_CONN_GetNormalConnAddr();
    pstEmcConn                      = IMSA_CONN_GetEmcConnAddr();

    if (IMSA_CONN_TYPE_NORMAL       == enConnType)
    {
        pstPdpInfo                  = &pstNormalConn->astSipMediaPdpArray[pstNormalConn->ulSipMediaPdpNum];
        pstNormalConn->ulSipMediaPdpNum++;
    }
    else
    {
        pstPdpInfo                  = &pstEmcConn->astSipMediaPdpArray[pstEmcConn->ulSipMediaPdpNum];
        pstEmcConn->ulSipMediaPdpNum++;
    }

    pstPdpInfo->ucPdpId             = pstPdpActivateInd->ucRabId;
    pstPdpInfo->enPdpState          = IMSA_PDP_STATE_ACTIVE;
    pstPdpInfo->enPdpType           = IMSA_PDP_TYPE_DEDICATED;
    pstPdpInfo->ucCid               = pstPdpActivateInd->ucCid;

    /* �洢������������غ� */
    pstPdpInfo->bitOpLinkedPdpId    = pstPdpActivateInd->bitOpLinkdRabId;
    pstPdpInfo->ucLinkedPdpId       = pstPdpActivateInd->ucLinkdRabId;

    pstPdpInfo->bitOpTft            = pstPdpActivateInd->bitOpTft;
    IMSA_MEM_CPY(                   &pstPdpInfo->stTft,
                                    &pstPdpActivateInd->stTft,
                                    sizeof(IMSA_PDP_TFT_INFO_STRU));

    if (IMSA_MAX_PF_NUM < pstPdpActivateInd->stTft.ulPfNum)
    {
        pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
    }

    /* �洢EPS QOS */
    IMSA_MEM_CPY(                   &pstPdpInfo->stEpsQos,
                                    &pstPdpActivateInd->stEpsQos,
                                    sizeof(IMSA_PDP_EPS_QOS_STRU));

}


VOS_VOID IMSA_CONN_ModifySipPdpInfo
(
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32          enSipPdpType,
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_CALL_PDP_MODIFY_IND_STRU      *pstPdpModifyInd
)
{

    /* �洢EPS QOS */
    IMSA_MEM_CPY(       &pstPdpInfo->stEpsQos,
                        &pstPdpModifyInd->stEpsQos,
                        sizeof(IMSA_PDP_EPS_QOS_STRU));
    if (IMSA_CONN_SIP_PDP_TYPE_SIGNAL == enSipPdpType)
    {
        /* �洢IPV4 P-CSCF */
        IMSA_MEM_CPY(   &pstPdpInfo->stPdpIpv4Pcscf,
                        &pstPdpModifyInd->stPcscf,
                        sizeof(IMSA_PDP_IPV4_PCSCF_STRU));

        /* �洢IPV4 DNS */
        IMSA_MEM_CPY(   &pstPdpInfo->stPdpIpv4Dns,
                        &pstPdpModifyInd->stDns,
                        sizeof(IMSA_PDP_IPV4_DNS_STRU));

        /* �洢IPV6 P-CSCF */
        IMSA_MEM_CPY(   &pstPdpInfo->stPdpIpv6Pcscf,
                        &pstPdpModifyInd->stIpv6Pcscf,
                        sizeof(IMSA_PDP_IPV6_PCSCF_STRU));

        /* �洢IPV6 DNS */
        IMSA_MEM_CPY(   &pstPdpInfo->stPdpIpv6Dns,
                        &pstPdpModifyInd->stIpv6Dns,
                        sizeof(IMSA_PDP_IPV6_DNS_STRU));
    }
    else if(IMSA_CONN_SIP_PDP_TYPE_MEDIA == enSipPdpType)/* ý����ص�����£�����TFT��Ϣ */
    {
        pstPdpInfo->bitOpTft            = pstPdpModifyInd->bitOpTft;
        IMSA_MEM_CPY(                   &pstPdpInfo->stTft,
                                        &pstPdpModifyInd->stTft,
                                        sizeof(IMSA_PDP_TFT_INFO_STRU));

        if (IMSA_MAX_PF_NUM < pstPdpModifyInd->stTft.ulPfNum)
        {
            pstPdpInfo->stTft.ulPfNum = IMSA_MAX_PF_NUM;
        }
    }
    else
    {
    }
}

VOS_UINT32 IMSA_CONN_IsVoiceMediaPdpType
(
    IMSA_PDP_TFT_INFO_STRU              *pstTft,
    VOS_UINT8                           ucQCI
)
{
    VOS_UINT32                          ulPfNum             = IMSA_NULL;
    VOS_UINT16                          usImsMinPort        = IMSA_NULL;
    VOS_UINT16                          usImsMaxPort        = IMSA_NULL;
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_IsVoiceMediaPdpType is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsVoiceMediaPdpType_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pstTft)
    {
        return IMSA_TRUE;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstControlManager = IMSA_GetControlManagerAddress();
    usImsMinPort = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort;
    usImsMaxPort = pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort;

    /* ��Ƶ����Ҫ��A�ˣ����Բ���Ҫ���ø�CDS��ͨ��TFT�Ķ˿���Ϣ�����ֳ����Ƿ�����Ƶ���� */
    /* ��������ж��������������Ҫ�ж�һ�����ض˿ھͿ��ԣ����಻���һ������������C�˶˿ڣ�
    ��һ������A�˶˿� */
    if (0 == pstTft->ulPfNum)
    {
        return IMSA_TRUE;
    }
    for (ulPfNum = 0; ulPfNum < pstTft->ulPfNum; ulPfNum ++ )
    {
        if ((IMSA_OP_TRUE == pstTft->astTftInfo[ulPfNum].bitOpSingleLocalPort) &&
            (pstTft->astTftInfo[ulPfNum].usSingleLcPort >= usImsMinPort) &&
            (pstTft->astTftInfo[ulPfNum].usSingleLcPort <= usImsMaxPort))
        {
            return IMSA_TRUE;
        }

        if ((IMSA_OP_TRUE == pstTft->astTftInfo[ulPfNum].bitOpLocalPortRange) &&
            (pstTft->astTftInfo[ulPfNum].usLcPortLowLimit >= usImsMinPort) &&
            (pstTft->astTftInfo[ulPfNum].usLcPortHighLimit <= usImsMaxPort))
        {
            return IMSA_TRUE;
        }

        /* �����Я�����ض˿ںţ�Ҳ��Я�����ض˿ںŷ�Χ����ͨ��QCI�жϵ�ǰ�ǲ����������� */
        if (IMSA_VOICE_QCI == ucQCI)
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}
VOS_VOID IMSA_CONN_SaveIpv6Info
(
    IMSA_PDP_CNTXT_INFO_STRU                   *pstPdpInfo,
    const TAF_PS_IPV6_INFO_IND_STRU            *pstIpv6InfoInd
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
    IMSA_MEM_CPY(   pstPdpInfo->stPdpAddr.aucIpV6Addr,
                    pstIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                    IMSA_IPV6_PREFIX_LEN);
}


VOS_UINT32 IMSA_CONN_IsPdpIpv4InfoIncludeRegPara
(
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acPdpUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acPdpPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                        pstPdpInfo->stPdpAddr.aucIpV4Addr,
                                        acPdpUeAddr);

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucPrimPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpSecPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucSecPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv4Pcscf.bitOpThiPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV4,
                                            pstPdpInfo->stPdpIpv4Pcscf.aucThiPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}
VOS_UINT32 IMSA_CONN_IsPdpIpv6InfoIncludeRegPara
(
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acPdpUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acPdpPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};

    IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpAddr.aucIpV6Addr,
                                            acPdpUeAddr);

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucPrimPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucSecPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }
    if (IMSA_OP_TRUE == pstPdpInfo->stPdpIpv6Pcscf.bitOpThiPcscfAddr)
    {
        IMSA_CONN_ConvertIpAddress2String(  IMSA_IP_TYPE_IPV6,
                                            pstPdpInfo->stPdpIpv6Pcscf.aucThiPcscfAddr,
                                            acPdpPcscfAddr);

        /* �Ƚϵ�ַ�� */
        if ((0 == VOS_StrCmp(pcRegUeAddr, acPdpUeAddr))
            && (0 == VOS_StrCmp(pcRegPcscfAddr, acPdpPcscfAddr)))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}
VOS_UINT32 IMSA_CONN_IsPdpIpvxInfoIncludeRegPara
(
    IMSA_IP_TYPE_ENUM_UINT8                 enIpType,
    VOS_CHAR                               *pcRegUeAddr,
    VOS_CHAR                               *pcRegPcscfAddr,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_UINT32                          ulResult = IMSA_FALSE;

    if (IMSA_IP_TYPE_IPV4 == enIpType)
    {
        ulResult = IMSA_CONN_IsPdpIpv4InfoIncludeRegPara(pcRegUeAddr, pcRegPcscfAddr, pstPdpInfo);
        return ulResult;
    }
    else
    {
        ulResult = IMSA_CONN_IsPdpIpv6InfoIncludeRegPara(pcRegUeAddr, pcRegPcscfAddr, pstPdpInfo);
        return ulResult;
    }

}



VOS_UINT32 IMSA_CONN_IsPdpInfoIncludeRegPara
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    const IMSA_PDP_CNTXT_INFO_STRU         *pstPdpInfo
)
{
    VOS_CHAR                            acRegUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_CHAR                            acRegPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1] = {0};
    VOS_UINT32                          ulRslt          = IMSA_FAIL;

    IMSA_IP_TYPE_ENUM_UINT8             enIpType = IMSA_IP_TYPE_BUTT;

    ulRslt = IMSA_RegGetRegedPara(  (IMSA_REG_TYPE_ENUM_UINT8)enConnType,
                                    acRegUeAddr,
                                    acRegPcscfAddr,
                                    &enIpType);

    /* ���δ��ȡ��ע���ϵĲ�������ֱ�ӷ��ز����� */
    if (IMSA_FAIL == ulRslt)
    {
        return IMSA_FALSE;
    }

    if (IMSA_IP_TYPE_BUTT != enIpType)
    {
        if ((IMSA_IP_TYPE_IPV4V6 != pstPdpInfo->stPdpAddr.enIpType) && (enIpType != pstPdpInfo->stPdpAddr.enIpType))
        {
            return IMSA_FALSE;
        }
    }

    if ((IMSA_IP_TYPE_IPV4 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (IMSA_TRUE == IMSA_CONN_IsPdpIpvxInfoIncludeRegPara( IMSA_IP_TYPE_IPV4,
                                                                acRegUeAddr,
                                                                acRegPcscfAddr,
                                                                pstPdpInfo))
        {
            return IMSA_TRUE;
        }
    }

    if ((IMSA_IP_TYPE_IPV6 == pstPdpInfo->stPdpAddr.enIpType)
        || (IMSA_IP_TYPE_IPV4V6 == pstPdpInfo->stPdpAddr.enIpType))
    {
        if (IMSA_TRUE == IMSA_CONN_IsPdpIpvxInfoIncludeRegPara( IMSA_IP_TYPE_IPV6,
                                                                acRegUeAddr,
                                                                acRegPcscfAddr,
                                                                pstPdpInfo))
        {
            return IMSA_TRUE;
        }
    }

    return IMSA_FALSE;
}
VOS_VOID IMSA_CONN_DeleteEmcPdpInfo
(
    VOS_UINT8                               ucCid
)
{
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    pstEmcConn  = IMSA_CONN_GetEmcConnAddr();

    if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->stSipSignalPdp.enPdpState)
        &&(ucCid == pstEmcConn->stSipSignalPdp.ucCid))
    {
        /* ȥ��������������������IP��ַ��Ч,����DNS��ַ��Ч */
        /* lihong00150010 volte phaseiii begin */
        /* IMSA_CONN_PdnInfoNicDelete(pstEmcConn->stSipSignalPdp.ucPdpId); */
        /* lihong00150010 volte phaseiii end */

        /* ����REGģ��ɾ��IP��ַ��P-CSCF��ַ */
        IMSA_CONN_DeletePdpInfo2Reg(IMSA_CONN_TYPE_EMC, &pstEmcConn->stSipSignalPdp);

        IMSA_MEM_SET(       &pstEmcConn->stSipSignalPdp,
                            0x0,
                            sizeof(IMSA_PDP_CNTXT_INFO_STRU));

        /* ֪ͨCDS���й��˳��� */
        IMSA_CONN_SndCdsSetImsBearerReq();

        return ;
    }

    /* ������ͨý����أ���ɾ�� */
    for (i = 0; i < pstEmcConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstEmcConn->astSipMediaPdpArray[i].enPdpState)
            &&(ucCid == pstEmcConn->astSipMediaPdpArray[i].ucCid))
        {
            if (i < (IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM - 1))
            {
                IMSA_MEM_CPY(   &pstEmcConn->astSipMediaPdpArray[i],
                                &pstEmcConn->astSipMediaPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET(       &pstEmcConn->astSipMediaPdpArray[IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM-1],
                                0x0,
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstEmcConn->ulSipMediaPdpNum--;

            /* ֪ͨCDS���й��˳��� */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    return ;
}


VOS_VOID IMSA_CONN_DeletePdpInfo
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    VOS_UINT8                               ucCid,
    VOS_UINT32                             *pulRegParaValid
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    /* IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR; */
    VOS_UINT32                          i               = IMSA_NULL;

    *pulRegParaValid = IMSA_CONN_REG_PARA_VALID;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        IMSA_INFO_LOG("IMSA_CONN_DeletePdpInfo:delete emc pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeletePdpInfo_ENUM, IMSA_EMERGENCY);

        IMSA_CONN_DeleteEmcPdpInfo(ucCid);

        return ;
    }

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    /* ������ͨ������أ���ɾ�� */
    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipSignalPdpArray[i].enPdpState)
            &&(ucCid == pstNormalConn->astSipSignalPdpArray[i].ucCid))
        {
            /* ȥ��������������������IP��ַ��Ч,����DNS��ַ��Ч */
            /* lihong00150010 volte phaseiii begin */
            /* IMSA_CONN_PdnInfoNicDelete(pstNormalConn->astSipSignalPdpArray[i].ucPdpId); */
            /* lihong00150010 volte phaseiii end */

            /* ʶ��ע������Ƿ�ʧЧ */
            if (IMSA_TRUE == IMSA_CONN_IsPdpInfoIncludeRegPara( IMSA_CONN_TYPE_NORMAL,
                                                                &pstNormalConn->astSipSignalPdpArray[i]))
            {
                *pulRegParaValid = IMSA_CONN_REG_PARA_INVALID;
            }

            /* ����REGģ��ɾ��IP��ַ��P-CSCF��ַ */
            IMSA_CONN_DeletePdpInfo2Reg(IMSA_CONN_TYPE_NORMAL, &pstNormalConn->astSipSignalPdpArray[i]);

            if (i < (IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM - 1))
            {
                IMSA_MEM_CPY(   &pstNormalConn->astSipSignalPdpArray[i],
                                &pstNormalConn->astSipSignalPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET(       &pstNormalConn->astSipSignalPdpArray[IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM-1],
                                0x0,
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstNormalConn->ulSipSignalPdpNum--;

            /* ֪ͨCDS���й��˳��� */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    /* ������ͨý����أ���ɾ�� */
    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if ((IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
            &&(ucCid == pstNormalConn->astSipMediaPdpArray[i].ucCid))
        {
            if (i < (IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM - 1))
            {
                IMSA_MEM_CPY(   &pstNormalConn->astSipMediaPdpArray[i],
                                &pstNormalConn->astSipMediaPdpArray[i+1],
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU)*((IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM-1)-i));
            }

            IMSA_MEM_SET(       &pstNormalConn->astSipMediaPdpArray[IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM-1],
                                0x0,
                                sizeof(IMSA_PDP_CNTXT_INFO_STRU));

            pstNormalConn->ulSipMediaPdpNum--;

            /* ֪ͨCDS���й��˳��� */
            IMSA_CONN_SndCdsSetImsBearerReq();

            return ;
        }
    }

    return ;
}
VOS_UINT32 IMSA_CONN_IsExitPersistentBearer
(
    VOS_VOID
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                  *pstEmclConn   = VOS_NULL_PTR;
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CONN_IsExitPersistentBearer:enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsExitPersistentBearer_ENUM, LNAS_ENTRY);


    pstNormalConn = IMSA_CONN_GetNormalConnAddr();
    pstEmclConn = IMSA_CONN_GetEmcConnAddr();

    /* ������ͨý����أ���ɾ�� */
    for (i = 0; i < pstNormalConn->ulSipMediaPdpNum; i++)
    {
        if (IMSA_PDP_STATE_ACTIVE == pstNormalConn->astSipMediaPdpArray[i].enPdpState)
        {
            return IMSA_TRUE;
        }
    }

    if (IMSA_PDP_STATE_ACTIVE == pstEmclConn->stSipSignalPdp.enPdpType)
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}
VOS_VOID IMSA_CONN_SndConnSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_SETUP_IND_STRU           *pstConnSetupInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnSetupInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnSetupInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnSetupInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnSetupInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnSetupInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnSetupInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnSetupInd), 0, IMSA_GET_MSG_LENGTH(pstConnSetupInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupInd,
                                ID_IMSA_CONN_SETUP_IND,
                                sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*��д��Ӧ���*/
    pstConnSetupInd->enResult       = enResult;
    pstConnSetupInd->enConnType     = enConnType;
    pstConnSetupInd->enSipPdpType   = enSipPdpType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnSetupInd);
}
VOS_VOID IMSA_CONN_SndConnMediaSetupInd
(
    IMSA_CONN_RESULT_ENUM_UINT32            enResult,
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
)
{
    IMSA_CONN_SETUP_IND_STRU           *pstConnSetupInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnMediaSetupInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnMediaSetupInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnSetupInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnSetupInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnSetupInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnMediaSetupInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnSetupInd), 0, IMSA_GET_MSG_LENGTH(pstConnSetupInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnSetupInd,
                                ID_IMSA_CONN_SETUP_IND,
                                sizeof(IMSA_CONN_SETUP_IND_STRU));

    /*��д��Ӧ���*/
    pstConnSetupInd->enResult       = enResult;
    pstConnSetupInd->enConnType     = enConnType;
    pstConnSetupInd->enSipPdpType   = IMSA_CONN_SIP_PDP_TYPE_MEDIA;
    pstConnSetupInd->enMediaPdpType = enMediaPdpType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnSetupInd);
}
VOS_VOID IMSA_CONN_SndConnMediaPdpModifyInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMeiadModifyType
)
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnMediaPdpModifyInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnMediaPdpModifyInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnMediaPdpModifyInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnModifyInd), 0, IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd,
                                ID_IMSA_CONN_MODIFY_IND,
                                sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*��д��Ӧ���*/
    pstConnModifyInd->enConnType    = enConnType;
    pstConnModifyInd->enSipPdpType  = IMSA_CONN_SIP_PDP_TYPE_MEDIA;

    pstConnModifyInd->bitOpMediaModifyType = IMSA_OP_TRUE;
    pstConnModifyInd->enMediaPdpType  = enMeiadModifyType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);
}
VOS_VOID IMSA_CONN_SndConnRegParaInvalid( VOS_VOID )
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRegParaInvalid is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnRegParaInvalid_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnRegParaInvalid_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnModifyInd), 0, IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd,
                                ID_IMSA_CONN_MODIFY_IND,
                                sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*��д��Ӧ���*/
    pstConnModifyInd->enConnType            = IMSA_CONN_TYPE_NORMAL;
    pstConnModifyInd->enSipPdpType          = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
    pstConnModifyInd->bitOpModifyType       = IMSA_OP_TRUE;
    pstConnModifyInd->enModifyType          = IMSA_CONN_MODIFY_TYPE_REG_PARA_INVALID;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);
}
VOS_VOID IMSA_CONN_SndConnRegPcscfInvalid( IMSA_CONN_TYPE_ENUM_UINT32 enConnType )
{
    IMSA_CONN_MODIFY_IND_STRU           *pstConnModifyInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRegParaInvalid is entered!");

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnModifyInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnModifyInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnMediaPdpModifyInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnModifyInd), 0, IMSA_GET_MSG_LENGTH(pstConnModifyInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnModifyInd, ID_IMSA_CONN_MODIFY_IND, sizeof(IMSA_CONN_MODIFY_IND_STRU));

    /*��д��Ӧ���*/
    pstConnModifyInd->enConnType            = enConnType;
    pstConnModifyInd->enSipPdpType          = IMSA_CONN_SIP_PDP_TYPE_SIGNAL;
    pstConnModifyInd->bitOpModifyType       = IMSA_OP_TRUE;
    pstConnModifyInd->enModifyType          = IMSA_CONN_MODIFY_TYPE_PCSCF_INVALID;

    /* ������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnModifyInd);

}
VOS_VOID IMSA_CONN_SndConnRelInd
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_SIP_PDP_TYPE_ENUM_UINT32      enSipPdpType
)
{
    IMSA_CONN_REL_IND_STRU             *pstConnRelInd  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_SndConnRelInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SndConnRelInd_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstConnRelInd = (VOS_VOID*)IMSA_GetIntraMsgBuffAddr(sizeof(IMSA_CONN_REL_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstConnRelInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_SndConnRelInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_SndConnRelInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstConnRelInd), 0, IMSA_GET_MSG_LENGTH(pstConnRelInd));

    /*��д��Ϣͷ*/
    IMSA_WRITE_INTRA_MSG_HEAD(  pstConnRelInd,
                                ID_IMSA_CONN_REL_IND,
                                sizeof(IMSA_CONN_REL_IND_STRU));

    /*��д��Ӧ���*/
    pstConnRelInd->enConnType     = enConnType;
    pstConnRelInd->enSipPdpType   = enSipPdpType;

    /*������Ϣ���ͺ��� */
    IMSA_SEND_INTRA_MSG(pstConnRelInd);
}
VOS_VOID IMSA_CONN_ProcReEstablishConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    /* TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo     = VOS_NULL_PTR; */
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnSetupReqMsg->enConnType;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;
    /* IMSA_SEL_SDF_PARA_STRU             *pstSelectedSdfPara  = VOS_NULL_PTR; */
    IMSA_CONTROL_MANAGER_STRU          *pstImsaControlManager   = VOS_NULL_PTR;
    VOS_UINT8                           ucCid               = IMSA_FAIL;
    IMSA_IP_TYPE_ENUM_UINT8             enIpType            = IMSA_FAIL;

    IMSA_INFO_LOG("IMSA_CONN_ProcReEstablishConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_ENTRY);

    pstImsaControlManager   = IMSA_GetControlManagerAddress();

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();

        ucCid= pstImsaControlManager->stNrmRegParaInfo.ucCid;

        enIpType = pstImsaControlManager->stNrmRegParaInfo.enIpType;
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();

        ucCid= pstImsaControlManager->stEmcRegParaInfo.ucCid;

        enIpType = pstImsaControlManager->stEmcRegParaInfo.enIpType;
    }

    /* �����CONNING̬������ */
    if (IMSA_CONN_STATUS_CONNING == enConnStatus)
    {
        return ;
    }

    /* �����RELEASING̬����ֱ�ӻظ����ӽ���ʧ�ܣ�ԭ��ֵΪIMSA_CONN_RESULT_FAIL_CONN_RELEASING */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_CONN_RELEASING,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return;
    }

    /* ��ȡ����NV���е�SDF������Ϣ */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:TAF_PS_GetCidSdfParaInfo fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        /* �����ȡSDF��Ϣʧ�ܣ��Ҵ�������PDN������£�ֱ�ӷ��سɹ���SERVICEģ������ж�
        ��IP��ַ�����仯���᱾��ȥע�ᣬȻ�������·���ע�� */
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_SUCCESS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        }
        else
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }
        return;
    }
    ulRslt = IMSA_CONN_FindSipSignalDialPara(   enConnType,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    if (IMSA_FAIL == ulRslt)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:ERROR: Err Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, 1);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);


        return;
    }

    /* ���Ҳ��Ų����������IPV4V6���ͣ��ҵ�ǰ�޼�����أ���ֱ�ӷ����������� */
    if (TAF_PDP_IPV4V6 == pstSdfQueryInfo->astSdfPara[ulFoundIndex].enPdnType)
    {
        if (IMSA_FALSE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            enIpType = IMSA_IP_TYPE_IPV4V6;
        }
        /* �����V4V6���ͣ��ҵ�ǰ����������ĳ��أ�����Ҫ�ж�CID�ͱ��ݵ�CID�Ƿ���ͬ�������ͬ����
       ֱ���õ�ǰ��CID�����������󣻷�����Ҫ���»�ȡδʹ�õ�CID�����·��𲦺����� */
        else if (ucCid != pstSdfQueryInfo->astSdfPara[ulFoundIndex].ucCid)
        {
            /* ����һ��δ�����CID���м��� */
            IMSA_CONN_AssignOpid(enConnType, &ucOpid);

            if (VOS_OK != TAF_PS_GetUnusedCid(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, &ucCid))
            {
                IMSA_WARN_LOG("IMSA_CONN_ProcReEstablishConnSetupReq:get cid failed!");
                IMSA_MEM_FREE(pstSdfQueryInfo);

                TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcReEstablishConnSetupReq_ENUM, LNAS_FUNCTION_LABEL2);

                IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                            enConnType,
                                            IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
                return ;
            }

        }
    }


    /* ��PDN�����޸�Ϊ���ݵ�PDN���� */
    pstSdfQueryInfo->astSdfPara[ulFoundIndex].enPdnType = enIpType;

    /* �洢ѡ���SDF���� */
    IMSA_CONN_SaveSelectedSdfPara(  enConnType,
                                    &pstSdfQueryInfo->astSdfPara[ulFoundIndex]);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    /* pstSelectedSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr(); */


    ulRslt = IMSA_CONN_SipSignalPdpActOrig(enConnType,
                                           ucCid,
                                           enIpType);

    if (IMSA_FAIL== ulRslt)
    {
        /* �������ʧ�ܣ��Ҵ�������PDN������£�ֱ�ӷ��سɹ���SERVICEģ������ж�
        ��IP��ַ�����仯���᱾��ȥע�ᣬȻ�������·���ע�� */
        if (IMSA_TRUE == IMSA_CONN_HasActiveSipSignalPdp(enConnType))
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_SUCCESS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        }
        else
        {
            IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                        enConnType,
                                        IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        }
        return;
    }

    /* ����״̬ת��CONNING״̬ */
    IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_CONNING);

    /* �洢��������PDN����Ϊ����PDN���� */
    IMSA_CONN_SaveFirstReqPdnType(enConnType, enIpType);

}


VOS_VOID IMSA_CONN_ProcConnSetupReq
(
    const IMSA_CONN_SETUP_REQ_STRU     *pstConnSetupReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnSetupReqMsg->enConnType;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;
    IMSA_SEL_SDF_PARA_STRU             *pstSelectedSdfPara  = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_ProcConnSetupReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_ENTRY);

    if (IMSA_TRUE == pstConnSetupReqMsg->ulReEstablishFlag)
    {
        IMSA_CONN_ProcReEstablishConnSetupReq(pstConnSetupReqMsg);
        return;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();
    }

    /* �����CONN̬����ֱ�ӷ������ӽ����ɹ� */
    if (IMSA_CONN_STATUS_CONN == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_SUCCESS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* �����CONNING̬������ */
    if (IMSA_CONN_STATUS_CONNING == enConnStatus)
    {
        return ;
    }

    /* �����RELEASING̬����ֱ�ӻظ����ӽ���ʧ�ܣ�ԭ��ֵΪIMSA_CONN_RESULT_FAIL_CONN_RELEASING */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_CONN_RELEASING,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING);

        /* ��ʱ�Ȳ�ɾ���ɵ�CHR����Ϊ��Ʒ�߶�������CHR��δ���ӽ������Ȳ�Ʒ��������
        �ٽ�ԭ����ɾ�� */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR);
        #endif
        return ;
    }

    /* �����IDLE̬���������ӽ������� */

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif
        return;
    }

    /* ��ȡ����NV���е�SDF������Ϣ */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:TAF_PS_GetCidSdfParaInfo fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

        return;
    }

    ulRslt = IMSA_CONN_FindSipSignalDialPara(   enConnType,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    if (IMSA_FAIL == ulRslt)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:ERROR: Err Para!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_PARAM_INVALID);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_PARA_ERR,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR);
        /* ��ʱ�Ȳ�ɾ���ɵ�CHR����Ϊ��Ʒ�߶�������CHR��δ���ӽ������Ȳ�Ʒ��������
        �ٽ�ԭ����ɾ�� */
        IMSA_PdnConnFailErrLogRecord(   enConnType,
                                        IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NO_IMS_PDP_CONTXT,
                                        IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                        IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_EMC_PDP_CONTEXT);
        #endif

        return;
    }

    /* �洢ѡ���SDF���� */
    IMSA_CONN_SaveSelectedSdfPara(  enConnType,
                                    &pstSdfQueryInfo->astSdfPara[ulFoundIndex]);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstSelectedSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }
    else
    {
        pstSelectedSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }

    pstDialParaInfo = IMSA_MEM_ALLOC(sizeof(TAF_PS_DIAL_PARA_STRU));

    if (VOS_NULL_PTR == pstDialParaInfo)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcNormalConnSetupReq:TAF_PS_DIAL_PARA_STRU ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, LNAS_NULL_PTR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

        return;
    }

    /* ��ѡ���SDF����ת���ɲ��Ų�����ʽ */
    IMSA_CONN_GetImsDailParaFromSelSdfPara( pstSelectedSdfPara,
                                            pstDialParaInfo);


    /* ����OPID���洢 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    IMSA_CONN_SetOpid(enConnType, ucOpid);

    /* ����API�ӿ�TAF_PS_CallOrig����APS����IMS������� */
    if (VOS_OK == TAF_PS_CallOrig(PS_PID_IMSA,IMSA_CLIENT_ID, ucOpid, pstDialParaInfo))
    {
        /* ����IMS���Ŷ�ʱ�� */
        IMSA_CONN_StartTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

        /* ����״̬ת��CONNING״̬ */
        IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_CONNING);

        /* �洢������������PDN���� */
        IMSA_CONN_SaveFirstReqPdnType(enConnType, pstDialParaInfo->enPdpType);

        /* �洢��ǰ���������PDN���� */
        IMSA_CONN_SaveCurReqPdnType(enConnType, pstDialParaInfo->enPdpType);

        IMSA_INFO_LOG1("global enFirstReqPdnType:", IMSA_CONN_GetNormalConnFirstReqPdnType());
        TLPS_PRINT2LAYER_INFO1(IMSA_CONN_ProcConnSetupReq_ENUM, 1, IMSA_CONN_GetNormalConnFirstReqPdnType());
    }
    else
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_ProcConnSetupReq:TAF_PS_CallOrig fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnSetupReq_ENUM, IMSA_CALL_API_ERROR);

        IMSA_CONN_SndConnSetupInd(  IMSA_CONN_RESULT_FAIL_OHTERS,
                                    enConnType,
                                    IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_PdnRejErrRecord(IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS);
        #endif

    }

    IMSA_MEM_FREE(pstDialParaInfo);
}


VOS_VOID IMSA_CONN_RequestApsRelConn
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
)
{
    IMSA_NORMAL_CONN_STRU              *pstNormalConn   = VOS_NULL_PTR;
    IMSA_EMC_CONN_STRU                 *pstEmcConn      = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid          = IMSA_NULL;

    if (IMSA_CONN_TYPE_EMC == enConnType)
    {
        pstEmcConn      = IMSA_CONN_GetEmcConnAddr();

        /* �����CONNING̬���������ͷ����ڽ�����������غ��Ѿ������������� */
        if (IMSA_CONN_STATUS_CONNING == pstEmcConn->enImsaConnStatus)
        {
            /* ����OPID���洢 */
            IMSA_CONN_AssignOpid(enConnType, &ucOpid);

            if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                            pstEmcConn->stSelSdfPara.ucCid))
            {
                IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:EMC,conninig,CallEnd failed!");
                TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);
            }

            IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_EMC);

            /* ֪ͨSERVICEģ�������ͷ� */
            IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_EMC, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            return ;
        }

        /* ����OPID���洢 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);
        /*lint -e774*/
        IMSA_CONN_SetOpid(enConnType, ucOpid);
        /*lint +e774*/



        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        (VOS_UINT8)pstEmcConn->stSipSignalPdp.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:EMC,conn,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);

            IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_EMC);

            IMSA_CONN_SndCdsSetImsBearerReq();

            /* ֪ͨSERVICEģ�������ͷ� */
            IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_EMC, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
            return ;
        }

        /* ����IMSAȥ���Ŷ�ʱ�� */
        IMSA_CONN_StartTimer(IMSA_CONN_TYPE_EMC, TI_IMSA_SIP_SIGAL_PDP_END);

        /* ��������״̬Ϊȥ������ */
        IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_EMC, IMSA_CONN_STATUS_RELEASING);
        return ;
    }

    pstNormalConn   = IMSA_CONN_GetNormalConnAddr();

    /* �����CONNING̬���������ͷ����ڽ�����������غ��Ѿ������������� */
    if (IMSA_CONN_STATUS_CONNING == pstNormalConn->enImsaConnStatus)
    {
        /* ����OPID���洢 */
        IMSA_CONN_AssignOpid(enConnType, &ucOpid);

        if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                        pstNormalConn->stSelSdfPara.ucCid))
        {
            IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,conninig,CallEnd failed!");
            TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, LNAS_FAIL);
        }
    }

    if (0 == pstNormalConn->ulSipSignalPdpNum)
    {
        IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,conning,no active pdp!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, IMSA_NO_ACTIVE_PDP);

        IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_NORMAL);

        /* ֪ͨSERVICEģ�������ͷ� */
        IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);
        return ;
    }

    /* ����OPID���洢 */
    IMSA_CONN_AssignOpid(enConnType, &ucOpid);
    IMSA_CONN_SetNormalConnOpid(ucOpid);

    if (VOS_OK != TAF_PS_CallEnd(   PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid,
                                    pstNormalConn->astSipSignalPdpArray[0].ucCid))
    {
        IMSA_WARN_LOG("IMSA_CONN_RequestApsRelConn:normal,CallEnd failed!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CONN_RequestApsRelConn_ENUM, IMSA_CALL_API_ERROR);

        IMSA_CONN_ClearConnResource(IMSA_CONN_TYPE_NORMAL);

        IMSA_CONN_SndCdsSetImsBearerReq();

        /* ֪ͨSERVICEģ�������ͷ� */
        IMSA_CONN_SndConnRelInd(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* ����IMSAȥ���Ŷ�ʱ�� */
    IMSA_CONN_StartTimer(IMSA_CONN_TYPE_NORMAL, TI_IMSA_SIP_SIGAL_PDP_END);

    /* ��������״̬Ϊȥ������ */
    IMSA_CONN_SetConnStatus(IMSA_CONN_TYPE_NORMAL, IMSA_CONN_STATUS_RELEASING);

    return ;
}



VOS_VOID IMSA_CONN_ProcConnRelReq
(
    const IMSA_CONN_REL_REQ_STRU       *pstConnRelReqMsg
)
{
    IMSA_CONN_STATUS_ENUM_UINT8         enConnStatus        = IMSA_CONN_STATUS_BUTT;
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType          = pstConnRelReqMsg->enConnType;

    IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, LNAS_ENTRY);

    if (IMSA_CONN_SIP_PDP_TYPE_MEDIA == pstConnRelReqMsg->enSipPdpType)
    {
        IMSA_ERR_LOG("IMSA_CONN_ProcConnRelReq:Not support release media type pdp!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_NOT_SUPPORT);
        return ;
    }

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        enConnStatus = IMSA_CONN_GetNormalConnStatus();
    }
    else
    {
        enConnStatus = IMSA_CONN_GetEmcConnStatus();
    }

    /* �����IDLE̬����ֱ�ӷ��������ͷųɹ� */
    if (IMSA_CONN_STATUS_IDLE == enConnStatus)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq: idle!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_STATUS_IDLE);

        IMSA_CONN_SndConnRelInd(  enConnType,
                                  IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

        return ;
    }

    /* �����RELEASING̬������ */
    if (IMSA_CONN_STATUS_RELEASING == enConnStatus)
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcConnRelReq: releasing!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcConnRelReq_ENUM, IMSA_STATUS_RELEASING);
        return ;
    }

    /* ֹͣIMS���Ŷ�ʱ�� */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_ORIG);

    /* ֹͣ�ȴ�IPV6������ʱ�� */
    IMSA_CONN_StopTimer(enConnType, TI_IMSA_WAIT_IPV6_INFO);

    /* ����IMSȥ���Ŷ�ʱ�� */
    IMSA_CONN_StartTimer(enConnType, TI_IMSA_SIP_SIGAL_PDP_END);

    /* ����APS�ͷ����� */
    IMSA_CONN_RequestApsRelConn(enConnType);

    return ;
}


VOS_UINT32 IMSA_CONN_IsEmcPdpDefined( VOS_VOID )
{
    VOS_UINT32                          ulRslt              = IMSA_FAIL;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucOpid              = IMSA_NULL;
    VOS_UINT32                          ulFoundIndex        = IMSA_NULL;

    pstSdfQueryInfo = IMSA_MEM_ALLOC(sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        /*��ӡ���Ϸ���Ϣ*/
        IMSA_ERR_LOG("IMSA_CONN_IsEmcPdpDefined:ERROR: Mem alloc fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_IsEmcPdpDefined_ENUM, LNAS_NULL_PTR);

        return IMSA_FALSE;
    }

    /* ��ȡ����NV���е�SDF������Ϣ */
    IMSA_CONN_AssignOpid(IMSA_CONN_TYPE_EMC, &ucOpid);
    ulRslt = TAF_PS_GetCidSdfParaInfo(PS_PID_IMSA, IMSA_CLIENT_ID, ucOpid, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        IMSA_INFO_LOG("IMSA_CONN_IsEmcPdpDefined:TAF_PS_GetCidSdfParaInfo failed!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsEmcPdpDefined_ENUM, IMSA_CALL_API_ERROR);

        IMSA_MEM_FREE(pstSdfQueryInfo);

        return IMSA_FALSE;
    }

    ulRslt = IMSA_CONN_FindSipSignalDialPara(   IMSA_CONN_TYPE_EMC,
                                                pstSdfQueryInfo->ulSdfNum,
                                                pstSdfQueryInfo->astSdfPara,
                                                &ulFoundIndex);

    IMSA_MEM_FREE(pstSdfQueryInfo);

    if (IMSA_FAIL == ulRslt)
    {
        IMSA_INFO_LOG("IMSA_CONN_IsEmcPdpDefined:not define emc pdp!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_IsEmcPdpDefined_ENUM, 1);

        return IMSA_FALSE;
    }

    return IMSA_TRUE;
}


VOS_UINT32 IMSA_CONN_IsEqualToSelectedCid
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    VOS_UINT8                           ucCid
)
{
    IMSA_SEL_SDF_PARA_STRU             *pstSelSdfPara = VOS_NULL_PTR;

    if (IMSA_CONN_TYPE_NORMAL == enConnType)
    {
        pstSelSdfPara = IMSA_CONN_GetNormalConnSelSdfParaAddr();
    }
    else
    {
        pstSelSdfPara = IMSA_CONN_GetEmcConnSelSdfParaAddr();
    }

    if (ucCid == pstSelSdfPara->ucCid)
    {
        return IMSA_TRUE;
    }
    else
    {
        return IMSA_FALSE;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PrintNrmConnState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_PrintNrmConnState( VOS_VOID )
{
    switch (IMSA_CONN_GetNormalConnStatus())
    {
        case IMSA_CONN_STATUS_IDLE:
            IMSA_INFO_LOG("Current Normal Conn State: IDLE");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_IDLE);
            break;
        case IMSA_CONN_STATUS_CONNING:
            IMSA_INFO_LOG("Current Normal Conn State: CONNING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_CONNECTING);
            break;
        case IMSA_CONN_STATUS_RELEASING:
            IMSA_INFO_LOG("Current Normal Conn State: RELEASING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_RELEASING);
            break;
        case IMSA_CONN_STATUS_CONN:
            IMSA_INFO_LOG("Current Normal Conn State: CONN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_CONN);
            break;
        default:
            IMSA_INFO_LOG("Current Normal Conn State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNrmConnState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PrintEmcConnState
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-29  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_PrintEmcConnState( VOS_VOID )
{
    switch (IMSA_CONN_GetEmcConnStatus())
    {
        case IMSA_CONN_STATUS_IDLE:
            IMSA_INFO_LOG("Current Emc Conn State: IDLE");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_IDLE);
            break;
        case IMSA_CONN_STATUS_CONNING:
            IMSA_INFO_LOG("Current Emc Conn State: CONNING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_CONNECTING);
            break;
        case IMSA_CONN_STATUS_RELEASING:
            IMSA_INFO_LOG("Current Emc Conn State: RELEASING");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_RELEASING);
            break;
        case IMSA_CONN_STATUS_CONN:
            IMSA_INFO_LOG("Current Emc Conn State: CONN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_CONN);
            break;
        default:
            IMSA_INFO_LOG("Current Emc Conn State: UNKNOWN");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintEmcConnState_ENUM, IMSA_STATUS_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PrintNicPdpInfo
 Description     : ��ӡNIC PDP INFO�洢�ṹ�е���Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_PrintNicPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    IMSA_PRINT_NIC_PDP_INFO_STRU     *pstMsgNicInfo;

    pstMsgNicInfo = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_PRINT_NIC_PDP_INFO_STRU));
    if (VOS_NULL_PTR == pstMsgNicInfo)
    {
        IMSA_ERR_LOG("IMSA_CONN_PrintNicPdpInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CONN_PrintNicPdpInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(IMSA_GET_MSG_ENTITY(pstMsgNicInfo), 0, \
                 IMSA_GET_MSG_LENGTH(pstMsgNicInfo));

    IMSA_WRITE_INTRA_MSG_HEAD(  pstMsgNicInfo,
                                ID_IMSA_NIC_PDP_INFO_IND,
                                sizeof(IMSA_PRINT_NIC_PDP_INFO_STRU));

    IMSA_MEM_CPY(pstMsgNicInfo->astNicPdpInfoArray, \
                 pstConnManager->astNicPdpInfoArray, \
                 sizeof(IMSA_CONN_NIC_PDP_INFO_STRU)*IMSA_CONN_MAX_NIC_PDP_NUM);

    IMSA_INFO_LOG("IMSA_CONN_PrintNicPdpInfo: show nic pdp info.");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PrintNicPdpInfo_ENUM, 1);

    (VOS_VOID)LTE_MsgHook(pstMsgNicInfo);

    IMSA_FREE_MSG(pstMsgNicInfo);
}


/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo
 Description     : �жϴ�����NIC PDP INFO�е�IPV4���Ƿ���������³�����Ϣ�е�IP��ַ

 Input           : pstNicPdpInfo-----------���ø����������ĳ�����Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    if (0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV4Addr, pstEmcConn->stSipSignalPdp.stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 exist in EmcPdpInfo!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 1);

        return IMSA_TRUE;
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 not exist in EmcPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 2);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ( 0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV4Addr, pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 exist in NormalPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 3);

            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo: IPV4 not exist in NormalPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo_ENUM, 4);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo
 Description     : �жϴ�����NIC PDP INFO�е�IPV6���Ƿ���������³�����Ϣ�е�IP��ַ

 Input           : pstNicPdpInfo-----------���ø����������ĳ�����Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(const IMSA_CONN_NIC_PDP_INFO_STRU *pstNicPdpInfo)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    if (0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV6Addr, pstEmcConn->stSipSignalPdp.stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 exist in EmcPdpInfo!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 1);

        return IMSA_TRUE;
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 not exist in EmcPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 2);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i++)
    {
        if ( 0 == IMSA_MEM_CMP(pstNicPdpInfo->stPdpAddr.aucIpV6Addr, pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 exist in NormalPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 3);

            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo: IPV6 not exist in NormalPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo_ENUM, 4);

    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo
 Description     : ����ʶ�������NIC PDP INFO�У��������������³�����Ϣ�е�IP��ַ��
                   �����NIC PDP INFO��ɾ������֪ͨTTFɾ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               ulRst           = IMSA_TRUE;
    VOS_UINT32               i               = 0;

    IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        switch(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType)
        {
        case IMSA_IP_TYPE_IPV4:
            if (IMSA_FALSE == IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV4 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV4);

                ulRst = IMSA_FALSE;
            }

            break;
        case IMSA_IP_TYPE_IPV6:
            if (IMSA_FALSE == IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV6 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV6);

                ulRst = IMSA_FALSE;
            }

            break;
        case IMSA_IP_TYPE_IPV4V6:
            if (IMSA_FALSE == IMSA_CONN_Ipv4NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]) ||
                IMSA_FALSE == IMSA_CONN_Ipv6NicPdpInfoIsExistInPdpInfo(&pstConnManager->astNicPdpInfoArray[i]))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IPV4V6 not exist in PdpInfo!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IPV4V6);

                ulRst = IMSA_FALSE;
            }

            break;
        default:
            IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: IP tpye error!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, IMSA_IP_TYPE_ERROR);
            break;
        }

        if (IMSA_FALSE == ulRst)
        {
            /* ��ֹ����ע��ʱ����ͨ���������ؽ��ĳ���������ͨע��ʱ��
               �������������ؽ��ĳ����������CONNING+REG״̬����ɾ*/
            if (IMSA_FALSE == IMSA_SRV_IsConningRegState(pstConnManager->astNicPdpInfoArray[i].ucIsEmc))
            {
                IMSA_INFO_LOG("IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo: NIC delete pdp info!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo_ENUM, 1);
                IMSA_CONN_PdnInfoNicDelete(pstConnManager->astNicPdpInfoArray[i].ucPdpId);

                /* ͬ�Ϻ�����ȷ�ϣ���ɾ��C����������ʱ��֪ͨRNICģ�飬ɾ������������
                ͬʱ��AT�ϱ�����״̬ */
                if (IMSA_FALSE == pstConnManager->astNicPdpInfoArray[i].ucIsEmc)
                {
                    IMSA_SndMsgRnicPdnDeactInd(pstConnManager->astNicPdpInfoArray[i].ucPdpId);
                    IMSA_SndMsgAtPdpDeactInd(pstConnManager->astNicPdpInfoArray[i].stPdpAddr.enIpType);
                }

                IMSA_MEM_SET(&pstConnManager->astNicPdpInfoArray[i], 0, sizeof(IMSA_CONN_NIC_PDP_INFO_STRU ));
                pstConnManager->astNicPdpInfoArray[i].ucIsUsed = 0;
            }

            ulRst = IMSA_TRUE;
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo
 Description     : �жϳ�����Ϣ�е�IPV4���Ƿ������NIC PDP INFO�洢�ṹ��

 Input           : pstPdpAddr---------------������Ϣ�е�IP��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i               = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if ( 0 == IMSA_MEM_CMP(pstPdpAddr->aucIpV4Addr, pstConnManager->astNicPdpInfoArray[i].stPdpAddr.aucIpV4Addr, IMSA_IPV4_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo: IPV4 exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo: IPV4 not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo
 Description     : �жϳ�����Ϣ�е�IPV6���Ƿ������NIC PDP INFO�洢�ṹ��

 Input           : pstPdpAddr---------------������Ϣ�е�IP��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager    = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i                 = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if ( 0 == IMSA_MEM_CMP(pstPdpAddr->aucIpV6Addr, pstConnManager->astNicPdpInfoArray[i].stPdpAddr.aucIpV6Addr, IMSA_IPV6_ADDR_LEN))
        {
            IMSA_INFO_LOG("IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo: IPV6 exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo: IPV6 not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_PdpIdIsExistInNicPdpInfo
 Description     : �жϳ�����Ϣ�е�PDP ID���Ƿ������NIC PDP INFO�洢�ṹ��

 Input           : pstPdpAddr-----------������Ϣ�е�IP��Ϣ
 Output          : pulArrayIndex--------PDP ID������astNicPdpInfoArray�ṹ�е�����
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_PdpIdIsExistInNicPdpInfo(VOS_UINT8 ucPdpId, VOS_UINT32 *pulArrayIndex)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager    = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i                 = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            continue;
        }

        if (ucPdpId == pstConnManager->astNicPdpInfoArray[i].ucPdpId)
        {
            IMSA_INFO_LOG("IMSA_CONN_PdpIdIsExistInNicPdpInfo: PdpId exist in NicPdpInfo!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdpIdIsExistInNicPdpInfo_ENUM, IMSA_EXISTED);
            *pulArrayIndex = i;
            return IMSA_TRUE;
        }
    }

    IMSA_INFO_LOG("IMSA_CONN_PdpIdIsExistInNicPdpInfo: PdpId not exist in NicPdpInfo!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_PdpIdIsExistInNicPdpInfo_ENUM, 2);

    return IMSA_FALSE;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_InquireNotUsedInNicPdpInfo
 Description     : ��ѯucIsUsedΪ0��NIC PDP��¼
 Input           : None
 Output          : pulArrayIndex------------ucIsUsedΪ0��astNicPdpInfoArray������
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_UINT32 IMSA_CONN_InquireNotUsedInNicPdpInfo(VOS_UINT32 *pulArrayIndex)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    VOS_UINT32               i               = 0;

    for (i = 0; i < IMSA_CONN_MAX_NIC_PDP_NUM; i++)
    {
        if (0 == pstConnManager->astNicPdpInfoArray[i].ucIsUsed)
        {
            IMSA_INFO_LOG("IMSA_CONN_InquireNotUsedInNicPdpInfo: inquire succ!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_InquireNotUsedInNicPdpInfo_ENUM, LNAS_SUCC);
            *pulArrayIndex = i;
            return  IMSA_TRUE;
        }
    }
    IMSA_INFO_LOG("IMSA_CONN_InquireNotUsedInNicPdpInfo: inquire fail!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_InquireNotUsedInNicPdpInfo_ENUM, LNAS_FAIL);

    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_SaveNicPdpInfo
 Description     : ������Ϣ���浽NIC PDP INFO�洢�ṹ��
 Input           : ucPdpId--------------------�������PDP ID
                   ucIsEmc--------------------�Ƿ�Ϊ����
                   pulArrayIndex--------------���浽NIC PDP INFO�ṹ�е�����
                   pstPdpAddr-----------------�������PDP INFO
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_SaveNicPdpInfo(VOS_UINT8 ucPdpId,        VOS_UINT8 ucIsEmc, \
                                            VOS_UINT32 ulArrayIndex, const IMSA_IP_ADDRESS_STRU *pstPdpAddr)
{
    IMSA_CONN_MANAGER_STRU  *pstConnManager  = IMSA_CONN_GetConnManagerAddr();

    IMSA_INFO_LOG("IMSA_CONN_SaveNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_SaveNicPdpInfo_ENUM, LNAS_ENTRY);

    IMSA_MEM_CPY(&pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr, pstPdpAddr, sizeof(IMSA_IP_ADDRESS_STRU));
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucIsUsed = 1;
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucIsEmc = ucIsEmc;
    pstConnManager->astNicPdpInfoArray[ulArrayIndex].ucPdpId = ucPdpId;
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddNormalPdpInfo2NicPdpInfo
 Description     : �ж�IPV4���������Ϣ�Ƿ������NIC PDP INFO�У�
                   ��������ڣ���ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV4PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV4PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    if (IMSA_FALSE == IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr))
    {
        if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
        {
            IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

            IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
            /* ͬ�Ϻ�����ȷ�ϣ��ڰ�C����������ʱ��֪ͨRNICģ�飬������������
            ͬʱ��AT�ϱ�����״̬ */
            if (VOS_FALSE == ucIsEmc)
            {
                IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
            }
        }
        else
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcIPV4PdpInfoForNic: Inquire notUsed for ipv4 fail!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4PdpInfoForNic_ENUM, LNAS_FAIL);
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_ProcIPV6PdpInfoForNic
 Description     : �ж�IPV6���������Ϣ�Ƿ������NIC PDP INFO�У�
                   ��������ڣ���ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;
    VOS_UINT8                aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    if (0 == IMSA_MEM_CMP(aucTemp, pstImsaIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic: IPV6 prefix is 0!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_PARAM_INVALID);
    }
    else
    {
        if (IMSA_FALSE == IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr))
        {
            if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
            {
                IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

                IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
                /* ͬ�Ϻ�����ȷ�ϣ��ڰ�C����������ʱ��֪ͨRNICģ�飬������������
                ͬʱ��AT�ϱ�����״̬ */
                if (VOS_FALSE == ucIsEmc)
                {
                    IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                    IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
                }
            }
            else
            {
                IMSA_INFO_LOG("IMSA_CONN_ProcIPV6PdpInfoForNic: Inquire notUsed for ipv6 fail!");
                TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV6PdpInfoForNic_ENUM, LNAS_FAIL);
            }
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_ProcIPV4V6PdpInfoForNic
 Description     : �ж�IPV4V6���������Ϣ�Ƿ������NIC PDP INFO�У�
                   ��������ڣ���ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_ProcIPV4V6PdpInfoForNic(VOS_UINT8 ucIsEmc, IMSA_PDP_CNTXT_INFO_STRU *pstPdpCntxtInfo)
{
    IMSA_CONN_MANAGER_STRU   *pstConnManager  = IMSA_CONN_GetConnManagerAddr();
    IMSA_IP_ADDRESS_STRU     *pstImsaIpAddr   = VOS_NULL_PTR;
    VOS_UINT32               ulArrayIndex     = 0;
    VOS_UINT8                ucPdpId          = 0;
    VOS_UINT8                aucTemp[IMSA_IPV6_PREFIX_LEN]   = {0};

    IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4V6PdpInfoForNic_ENUM, LNAS_ENTRY);

    pstImsaIpAddr = &pstPdpCntxtInfo->stPdpAddr;
    ucPdpId       = pstPdpCntxtInfo->ucPdpId;

    /* if (0 == IMSA_MEM_CMP(aucTemp, pstImsaIpAddr->aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: IPV6 prefix is 0, !");
        return;
    } */

    if ((IMSA_TRUE == IMSA_CONN_Ipv4PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr)) &&
        (IMSA_TRUE == IMSA_CONN_Ipv6PdpAddrIsExistInNicPdpInfo(pstImsaIpAddr)))
    {
        IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: IPV4V6 exist in PdpInfo!");
        return;
    }

    if (IMSA_TRUE == IMSA_CONN_PdpIdIsExistInNicPdpInfo(ucPdpId, &ulArrayIndex))
    {
        IMSA_CONN_PdnInfoNicDelete(ucPdpId);

        IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

        if (0 == IMSA_MEM_CMP(aucTemp, pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
        {
            pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.enIpType = IMSA_IP_TYPE_IPV4;
        }

        IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
        /* ͬ�Ϻ�����ȷ�ϣ��ڰ�C����������ʱ��֪ͨRNICģ�飬������������
        ͬʱ��AT�ϱ�����״̬ */
        if (VOS_FALSE == ucIsEmc)
        {
            IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
            IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
        }
    }
    else
    {
        if (IMSA_TRUE == IMSA_CONN_InquireNotUsedInNicPdpInfo(&ulArrayIndex))
        {
            IMSA_CONN_SaveNicPdpInfo(ucPdpId, ucIsEmc, ulArrayIndex, pstImsaIpAddr);

            if (0 == IMSA_MEM_CMP(aucTemp, pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.aucIpV6Addr, IMSA_IPV6_PREFIX_LEN))
            {
                pstConnManager->astNicPdpInfoArray[ulArrayIndex].stPdpAddr.enIpType = IMSA_IP_TYPE_IPV4;
            }

            IMSA_CONN_ConfigPdpInfo2Bsp(pstPdpCntxtInfo);
            /* ͬ�Ϻ�����ȷ�ϣ��ڰ�C����������ʱ��֪ͨRNICģ�飬������������
            ͬʱ��AT�ϱ�����״̬ */
            if (VOS_FALSE == ucIsEmc)
            {
                IMSA_SndMsgRnicPdnActInd(pstPdpCntxtInfo);
                IMSA_SndMsgAtPdpActInd(pstPdpCntxtInfo);
            }
        }
        else
        {
            IMSA_INFO_LOG("IMSA_CONN_ProcIPV4V6PdpInfoForNic: Inquire notUsed for ipv6 fail!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_ProcIPV4V6PdpInfoForNic_ENUM, LNAS_FAIL);
        }
    }

    return;
}


/*****************************************************************************
 Function Name   : IMSA_CONN_AddNormalPdpInfo2NicPdpInfo
 Description     : ������������ͨ���������Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
                   ��ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddNormalPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_NORMAL_CONN_STRU    *pstNormalConn   = VOS_NULL_PTR;
    VOS_UINT32               i                = 0;

    IMSA_INFO_LOG("IMSA_CONN_AddNormalPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddNormalPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    pstNormalConn = IMSA_CONN_GetNormalConnAddr();

    for (i = 0; i < pstNormalConn->ulSipSignalPdpNum; i ++ )
    {
        switch(pstNormalConn->astSipSignalPdpArray[i].stPdpAddr.enIpType)
        {
        case IMSA_IP_TYPE_IPV4:
            IMSA_CONN_ProcIPV4PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        case IMSA_IP_TYPE_IPV6:
            IMSA_CONN_ProcIPV6PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        case IMSA_IP_TYPE_IPV4V6:
            IMSA_CONN_ProcIPV4V6PdpInfoForNic(0, &pstNormalConn->astSipSignalPdpArray[i]);
            break;
        default:
            IMSA_INFO_LOG("IMSA_CONN_AddNormalPdpInfo2NicPdpInfo: enIpType error!");
            TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddNormalPdpInfo2NicPdpInfo_ENUM, LNAS_PARAM_INVALID);
            break;
        }
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddEmcPdpInfo2NicPdpInfo
 Description     : ���������½������������Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
                   ��ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddEmcPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_EMC_CONN_STRU       *pstEmcConn      = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CONN_AddEmcPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddEmcPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    pstEmcConn = IMSA_CONN_GetEmcConnAddr();

    switch(pstEmcConn->stSipSignalPdp.stPdpAddr.enIpType)
    {
    case IMSA_IP_TYPE_IPV4:
        IMSA_CONN_ProcIPV4PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    case IMSA_IP_TYPE_IPV6:
        IMSA_CONN_ProcIPV6PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    case IMSA_IP_TYPE_IPV4V6:
        IMSA_CONN_ProcIPV4V6PdpInfoForNic(1, &pstEmcConn->stSipSignalPdp);
        break;
    default:
        IMSA_INFO_LOG("IMSA_CONN_AddEmcPdpInfo2NicPdpInfo: enIpType error!");
        TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddEmcPdpInfo2NicPdpInfo_ENUM, LNAS_PARAM_INVALID);
        break;
    }
}

/*****************************************************************************
 Function Name   : IMSA_CONN_AddPdpInfo2NicPdpInfo
 Description     : ����ʶ����������³�����Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
                   ��ӵ�NIC PDP INFO�У������ø�TTF
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_AddPdpInfo2NicPdpInfo(VOS_VOID)
{
    IMSA_INFO_LOG("IMSA_CONN_AddPdpInfo2NicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_AddPdpInfo2NicPdpInfo_ENUM, LNAS_ENTRY);

    /* ʶ�������������ͨ���������Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
       ��ӵ�NIC PDP INFO�У������ø�TTF */
    if (IMSA_SRV_STATUS_CONNING_REG != IMSA_SRV_GetNormalSrvStatus())
    {
        IMSA_CONN_AddNormalPdpInfo2NicPdpInfo();
    }

    /* ʶ����������½������������Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
       ��ӵ�NIC PDP INFO�У������ø�TTF */
    if (IMSA_SRV_STATUS_CONNING_REG != IMSA_SRV_GetEmcSrvStatus())
    {
        IMSA_CONN_AddEmcPdpInfo2NicPdpInfo();
    }
}


/*****************************************************************************
 Function Name   : IMSA_CONN_UpdateNicPdpInfo
 Description     : ���´洢���ø�NIC��PDP��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_UpdateNicPdpInfo( VOS_VOID )
{

    IMSA_INFO_LOG("IMSA_CONN_UpdateNicPdpInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CONN_UpdateNicPdpInfo_ENUM, LNAS_ENTRY);
    /* ������ǰ��NIC PDP��Ϣ�ϴ���HIDS����ʾ */
    IMSA_CONN_PrintNicPdpInfo();

    /* ʶ�������NIC PDP INFO�У��������������³�����Ϣ�е�IP��ַ��
       �����NIC PDP INFO��ɾ������֪ͨTTFɾ�� */
    IMSA_CONN_DeleteNicPdpInfoNotExistInPdpInfo();

    /* ʶ����������³�����Ϣ�У�����������NIC PDP INFO�е�IP��ַ��
       ��ӵ�NIC PDP INFO�У������ø�TTF */
    IMSA_CONN_AddPdpInfo2NicPdpInfo ();

    /* �����º��NIC PDP��Ϣ�ϴ���HIDS����ʾ */
    IMSA_CONN_PrintNicPdpInfo();
}

/*****************************************************************************
 Function Name   : IMSA_CONN_UpdateNicPdpInfo
 Description     : ���´洢���ø�NIC��PDP��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.xiongxianghui00253310    2014-04-16  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CONN_SetupConnFail
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType,
    IMSA_CONN_RESULT_ENUM_UINT32        enResult,
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enPdnConnRejCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    #endif

    /* ��������״̬ΪIDLE */
    IMSA_CONN_SetConnStatus(enConnType, IMSA_CONN_STATUS_IDLE);

    /* �������ʵ����Ϣ */
    IMSA_CONN_ClearConnResource(enConnType);

    IMSA_CONN_SndConnSetupInd(  enResult,
                                enConnType,
                                IMSA_CONN_SIP_PDP_TYPE_SIGNAL);

    #if (FEATURE_ON == FEATURE_PTM)
    enPdnConnRejCause = IMSA_PDN_InterRejCauseProc(enResult, enCause);
    IMSA_PdnRejErrRecord(enPdnConnRejCause);
    #endif
}
#if (FEATURE_ON == FEATURE_PTM)

IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_CnRejCauseProc
(
    TAF_PS_CAUSE_ENUM_UINT32 enCause
)
{
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    VOS_UINT32 i;

    for(i = 0; i < g_astImsaCnRejCauseNum; i++)
    {
        if(enCause == g_astImsaCnRejCauseMap[i].enCause)
        {
            enImsaCnCause = g_astImsaCnRejCauseMap[i].enImsaCnRejCause;
            break;
        }
    }
    if(g_astImsaCnRejCauseNum == i)
    {
        enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;
    }

    return enImsaCnCause;
}

IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32  IMSA_PDN_InterRejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult,
    TAF_PS_CAUSE_ENUM_UINT32        enCause
)
{
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT;

    switch(enResult)
    {
        case IMSA_CONN_RESULT_FAIL_PARA_ERR:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR;
            break;

        case IMSA_CONN_RESULT_FAIL_TIMER_EXP:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_TIMER_EXP;
            break;

        case IMSA_CONN_RESULT_FAIL_CN_REJ:
            enImsaCnCause = IMSA_PDN_CnRejCauseProc(enCause);
            break;

        case IMSA_CONN_RESULT_FAIL_CONN_RELEASING:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING;
            break;

        case IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT;
            break;

        case IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_SAME_APN_OPERATING;
            break;

        case IMSA_CONN_RESULT_FAIL_OHTERS:
            enImsaCnCause = IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS;
            break;

        default:
            break;
    }
    return enImsaCnCause;
}


IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32  IMSA_Norm_PDN_RejCauseProc
(
    IMSA_CONN_RESULT_ENUM_UINT32    enResult
)
{
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_BUTT;

    switch(enResult)
    {
        case IMSA_CONN_RESULT_FAIL_PARA_ERR:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_PARA_ERR;
            break;

        case IMSA_CONN_RESULT_FAIL_TIMER_EXP:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_TIMER_EXP;
            break;

        case IMSA_CONN_RESULT_FAIL_CN_REJ:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ;
            break;

        case IMSA_CONN_RESULT_FAIL_CONN_RELEASING:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING;
            break;

        case IMSA_CONN_RESULT_FAIL_PDP_ACTIVATE_LIMIT:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT;
            break;

        case IMSA_CONN_RESULT_FAIL_SAME_APN_OPERATING:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_SAME_APN_OPERATING;
            break;

        case IMSA_CONN_RESULT_FAIL_OHTERS:
            enImsaCnCause = IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_OTHERS;
            break;

        default:
            break;
    }
    return enImsaCnCause;
}


#endif

/*lint +e961*/

#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/*lint +esym(766,*)*/
/* end of ImsaConnManagement.c */



