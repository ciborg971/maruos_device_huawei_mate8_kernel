

#ifndef __TAFAPS_COMFUNC_H__
#define __TAFAPS_COMFUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasStkInterface.h"
#include "TafApsGetPdpIdList.h"
#include "taf_aps_ppp_pif.h"
#include "hsm_aps_pif.h"
#include "TafSdcCtx.h"
#include "taf_aps_dhcp_pif.h"
#include "ehsm_aps_pif.h"
#include "TafMmaInterface.h"
#include "TafApsSndInternalMsg.h"

#include "NasMmlCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define TAF_APS_GET_SM_ERR_CODE_MAP_TBL_PTR()   (g_astTafApsSmErrCodeMapTbl)
#define TAF_APS_GET_SM_ERR_CODE_MAP_TBL_SIZE()  (sizeof(g_astTafApsSmErrCodeMapTbl)/sizeof(TAF_APS_SM_ERR_CODE_MAP_STRU))

#define TAF_APS_GET_L4A_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsL4aErrCodeMapTbl)
#define TAF_APS_GET_L4A_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsL4aErrCodeMapTbl)/sizeof(TAF_APS_L4A_ERR_CODE_MAP_STRU))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsXccErrCodeMapTbl)
#define TAF_APS_GET_XCC_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsXccErrCodeMapTbl)/sizeof(TAF_APS_XCC_ERR_CODE_MAP_STRU))

#define TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsHsmErrCodeMapTbl)
#define TAF_APS_GET_HSM_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsHsmErrCodeMapTbl)/sizeof(TAF_APS_HSM_ERR_CODE_MAP_STRU))


/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, begin */
#define TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_PTR()  (g_astTafApsEHsmErrCodeMapTbl)
#define TAF_APS_GET_EHSM_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astTafApsEHsmErrCodeMapTbl)/sizeof(TAF_APS_EHSM_ERR_CODE_MAP_STRU))
/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, end */
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT8 NAS_MML_GetPsAttachAllowFlg(VOS_VOID);

extern NAS_MML_TIMER_INFO_ENUM_UINT8 NAS_MML_GetT3402Status(VOS_VOID);

VOS_UINT32   TAF_APS_AllocPdpId(
    TAF_CTRL_STRU                      *pstCtrl,
    VOS_UINT8                           ucCid,
    VOS_UINT8                          *pucPdpId
);
VOS_UINT32   TAF_APS_IsPdpIdValid(
    VOS_UINT8                           ucPdpId
);

VOS_UINT8 TAF_APS_GetCidValue(
    VOS_UINT32                          ulBearerActivateFlg,
    VOS_UINT8                          *pucCidList
);

VOS_UINT32 TAF_APS_CheckCidDefinedCtx(
    VOS_UINT8                           ucCid
)
;
VOS_UINT8   TAF_APS_GetPdpIdByNsapi(
    VOS_UINT8                           ucNsapi
);
VOS_UINT8 TAF_APS_GetPdpIdByLlcSapi(
    VOS_UINT8                           ucLlcSapi
);

VOS_UINT32 TAF_APS_CheckBearerPdpTypeSuitable(
    VOS_UINT8                           ucDefaultPdpType,
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType
);

VOS_VOID TAF_APS_String2Hex(
    VOS_UINT8                          *pucStr,
    VOS_UINT16                          usStrLen,
    VOS_UINT32                         *pulResult
);
VOS_UINT8   TAF_APS_GetPdpIdByCid(
    VOS_UINT8                           ucCid
);
VOS_UINT8   TAF_APS_GetPdpIdByCid_InEpsBearerIndOptActivate(
    VOS_UINT8                           ucCid
);
VOS_UINT8   TAF_APS_GetPdpIdByCid_InL4aDeactivateInd(
    VOS_UINT8                           ucCid
);
VOS_UINT8 TAF_APS_GetPdpIdByEpsbId_InL4aDeactivateInd(VOS_UINT32 ulEpsbId);
VOS_UINT8 TAF_APS_GetPdpIdByEpsbId(VOS_UINT32 ulEpsbId);

VOS_UINT8   TAF_APS_GetPdpEntOpId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32   TAF_APS_GetPdpEntModuleId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT8  TAF_APS_GetPdpIdByDefaultCid (VOS_VOID);

VOS_VOID TAF_APS_SetPdpEntClientId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT16                          usClientId
);
VOS_VOID TAF_APS_SetPdpEntOpId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT8                           ucOpId
);
VOS_UINT32  TAF_APS_GetTiFromPdpId(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTi
);
VOS_UINT32  TAF_APS_GetPdpIdFromTi(
    SM_TAF_TRANS_ID_STRU               *pstTi,
    VOS_UINT8                          *pucPdpId
);
VOS_VOID  TAF_APS_SetPdpEntityTi(
    VOS_UINT8                           ucPdpId,
    SM_TAF_TRANS_ID_STRU               *pstTis
);
VOS_UINT8 TAF_APS_GetCidFromLteBitCid(
    VOS_UINT32                          ulBitCid
);

VOS_UINT32  TAF_APS_GetActivedCid(
    VOS_UINT8                           *pucActivedCid
);

VOS_UINT32 TAF_APS_Ipv4AddrAtoi(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT32 TAF_APS_ValidatePdpType(
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeReq,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpTypeCnf
);

VOS_UINT32 TAF_APS_Ipv4AddrItoa(
    VOS_CHAR                           *pcString,
    VOS_UINT8                          *pucNumber
);

VOS_UINT8 TAF_APS_ConverUserDefPdpTypeToApsEntityPdpType (
    TAF_PDP_TYPE_ENUM_UINT8             enUserPdpType,
    VOS_UINT8                           ucDefaultPdpType
);

/* Added by y00314741 for CDMA Iteration 11, 2015-4-8, begin */
TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmcRatType (
    MMC_APS_RAT_TYPE_ENUM_UINT32       enRatType
);

TAF_APS_RAT_TYPE_ENUM_UINT32 TAF_APS_ConvertMmaClServiceToApsRatType (
    MMA_TAF_RAT_TYPE_ENUM_UINT32       enRatType
);

/* Added by y00314741 for CDMA Iteration 11, 2015-4-8, end */

VOS_VOID TAF_APS_GetSpecPdpLinkedPdpInfo (
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList,
    VOS_UINT8                           ucNsapi
);

extern TAF_APS_USER_CONN_STATUS_ENUM_UINT8 TAF_APS_GetUserConnStatus(VOS_VOID);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapSmCause(
    SM_TAF_CAUSE_ENUM_UINT16            enSmCause
);

#if (FEATURE_ON == FEATURE_LTE)
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapL4aCause(
    VOS_UINT32                          ulL4aCause
);
#endif

TAF_PDP_TYPE_ENUM_UINT8 TAF_APS_ConvertPdpType(VOS_UINT8 ucPdpTypeNum);

VOS_UINT32 TAF_APS_GetCtrlHdrFromCmdBufferQueue(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimer,
    VOS_UINT32                          ulPara
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_APS_PsCallFailErrRecord(TAF_PS_CAUSE_ENUM_UINT32 enCause);
#endif

VOS_VOID TAF_APS_SetPdpEntModuleId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId
);

VOS_VOID TAF_APS_SetPdpEntCidValue (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_RmvPdpEntClientInfo (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_APS_BITCID_INFO_STRU           *pstBitCid
);

VOS_VOID   TAF_APS_SetPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_VOID   TAF_APS_AddPdpEntClientInfo(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    CONST TAF_CTRL_STRU                *pstCtrl
);

VOS_VOID TAF_APS_SetPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);
VOS_VOID TAF_APS_RmvPdpEntBitCidMask (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_IsPdpEntBitCidMaskExit (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_APS_CheckImsBearerByCid (
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_CheckImsBearerByRabId (
    VOS_UINT32                          ulRabId
);

VOS_VOID TAF_APS_GetImsBearerCid (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                          *pucCid
);
#endif

VOS_VOID TAF_APS_GetPdpEntBitCidInfo(
    VOS_UINT8                           ucPdpId,
    TAF_APS_BITCID_INFO_STRU                    *pstCid
);

VOS_VOID TAF_APS_SetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_APS_GetPdpEntAttachBearerFlag (
    VOS_UINT8                           ucPdpId
);

VOS_VOID   TAF_APS_SetPsCallEvtCtrl(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_CTRL_STRU                      *pstCtrl
);

VOS_INT32 TAF_APS_CompareApn(
    const VOS_UINT8                 aucBearerApn[],
    VOS_UINT8                       ucBearerApnLen,
    const VOS_UINT8                 aucUserApn[],
    VOS_UINT8                       ucUserApnLen
);

VOS_VOID TAF_APS_SetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_UINT8 TAF_APS_GetPdpEntDialPdpType(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_UINT32 TAF_APS_MatchCallWithAllBearer(
    CONST TAF_CTRL_STRU                *pstCtrl,
    CONST TAF_APS_MATCH_PARAM_STRU     *pstMatchParam,
    VOS_UINT8                          *pucPdpId
);

VOS_UINT16   TAF_APS_GetPdpEntClientId(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_SetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
);

VOS_VOID TAF_APS_GetPdpEntModDialInfo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_PDP_MOD_DIAL_STRU          *pstModDial
);

VOS_VOID TAF_APS_SetPdpEntAddrType(
    VOS_UINT8                           ucPdpId,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

VOS_UINT32 TAF_APS_IsAnyBearerExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_IsAttachBearerExist(VOS_VOID);
VOS_UINT32 TAF_APS_IsPdnCntxtValid(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsPdnCntxtDefault(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsAnyOtherNormalPdnActive(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntx);
VOS_UINT32 TAF_APS_IsPdnCntxtTeardownAllowed(TAF_APS_PDN_CONTEXT_STRU *pstPdnCntxt);
#endif

VOS_UINT8 TAF_APS_GetAttachAllowFlg(VOS_VOID);

VOS_UINT8 TAF_APS_IsT3402Running(VOS_VOID);

VOS_VOID TAF_APS_GenMatchParamByCidInfo(
    CONST TAF_PDP_TABLE_STRU           *pstPdpTblInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
);

VOS_VOID TAF_APS_GenMatchParamByDailInfo(
    CONST TAF_PS_DIAL_PARA_STRU        *pstDialParaInfo,
    TAF_APS_MATCH_PARAM_STRU           *pstMatchParam
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapXccCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
);

VOS_VOID TAF_APS_SetPdpEntSo (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_SO_TYPE_ENUM_UINT16   enSo
);

TAF_APS_CDATA_SO_TYPE_ENUM_UINT16 TAF_APS_GetPdpEntSo (
    VOS_UINT8                           ucPdpId
);


VOS_VOID TAF_APS_SetPdpEntConRef (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConRef
);

VOS_VOID TAF_APS_SetPdpEntConnectId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucConnectId
);



VOS_VOID TAF_APS_SetPdpEntPppState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState
);

TAF_APS_CDATA_PPP_STATE_ENUM_UINT8 TAF_APS_GetPdpEntPppState (
    VOS_UINT8                           ucPdpId
);
VOS_UINT8   TAF_APS_GetPdpIdByConRef(
    VOS_UINT8                           ucConRef
);

VOS_UINT8   TAF_APS_GetPdpIdByCallId(
    VOS_UINT8                           ucCallId
);



VOS_VOID TAF_APS_SetPdpEntCdsServiceIndFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucFlag
);

VOS_UINT8 TAF_APS_GetPdpEntCdsServiceIndFlag (
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_IsNeedSilentRedial(
    TAF_PS_CAUSE_ENUM_UINT32            enCause,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatMode
);

VOS_UINT32 TAF_APS_IsNeedRedial1xSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT32 TAF_APS_IsNeedRedialHrpdSystemAcquire(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);


VOS_VOID TAF_APS_SetPdpEntL2ErrReOrigFlag (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucIsL2ErrReOrig
);

VOS_VOID TAF_APS_SetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucL2ErrReOrigCount
);

VOS_UINT8 TAF_APS_GetPdpEntReOrigCount (
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_Is1xRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause,
    TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8    enType
);


VOS_VOID TAF_APS_PdpEntityEnterDormant(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulIsNeedStartTimer
);

VOS_VOID TAF_APS_SetPdpEntSrId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucSrId
);
VOS_UINT8 TAF_APS_GetPdpEntSrId (
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_UpdataCdataIpv4Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
);

VOS_VOID TAF_APS_UpdataCdataIpv6Addr(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf
);

TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapHsmCause(
    HSM_APS_CAUSE_ENUM_UINT32           enhHsmCause
);

VOS_UINT8 TAF_APS_IsHrpdRedialCause(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT8 TAF_APS_IsNeedRedialImmediately(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);


VOS_UINT8   TAF_APS_GetPdpIdByPndId(
    VOS_UINT8                           ucPdnId
);

APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataEhrpdSvcSta(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_AddCauseForCdataDoalStackDailNotSuport(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActCnfEvt,
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

TAF_APS_CDATA_REDIAL_TYPE_ENUM_UINT8 TAF_APS_IsNeedRedialEventType(
    VOS_UINT32            ulEventType
);



VOS_UINT32 TAF_APS_IsAllowCdataEsting(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
);

VOS_UINT8 TAF_APS_GetDrsValueByScene(
    VOS_UINT32                          ulEventType
);

VOS_UINT8 TAF_APS_IsRedialCallFromDormantState(
    VOS_UINT8                           ucPdnId
);

VOS_VOID TAF_APS_SetPdpEntCdataEstFailCause(
    VOS_UINT8                           ucPdnId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
);

#endif

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_Get1XServiceStatus(VOS_VOID);

TAF_SDC_SERVICE_STATUS_ENUM_UINT8 TAF_APS_GetHrpdServiceStatus(VOS_VOID);

/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, begin */
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_MapEhsmCause(
    EHSM_APS_CAUSE_ENUM_UINT32          enEhsmCause
);

VOS_VOID TAF_APS_SetPdpEntCdataPdnId (
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucPdnId
);

VOS_UINT8 TAF_APS_GetPdpEntCdataPdnId(
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_UpdateCdataEhsmPdnInfo (
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    EHSM_APS_PDN_ADDR_STRU             *pstPdnAddr,
    EHSM_APS_APN_STRU                  *pstApn,
    EHSM_APS_DNS_IPV4_STRU             *pstIpv4Dns
);

VOS_VOID TAF_APS_UpdateCdataIpv4Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf
);

VOS_VOID TAF_APS_UpdateCdataIpv6Dns(
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity,
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstDhcpDnsIpv6Cnf
);

VOS_VOID TAF_APS_SndExternalModulePsRatTypeNtf(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
);

VOS_VOID TAF_APS_RcvSequenceProcessDhcpNdclient(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucCid
);

VOS_VOID TAF_APS_ProcCdataDhcpNegotiateFail(
    VOS_UINT8                                     ucPdpId,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8      enEndReason
);

VOS_VOID TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(
    VOS_UINT8                                               ucPdpId,
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd
);

VOS_UINT8 TAF_APS_IsExistXcallOrXsmsOpreation(VOS_VOID);

/* Added by y00314741 for CDMA Iteration 15, 2015-5-15, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
VOS_VOID TAF_APS_LocalReleaseProc(
    VOS_UINT8                           ucPdpId
);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

VOS_UINT8 TAF_APS_IsCdataLocalReleaseCause(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
);

VOS_VOID TAF_APS_SetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId,
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8   enPsState
);

TAF_APS_CDATA_PS_STATE_ENUM_UINT8 TAF_APS_GetPdpEntCdataPsState (
    VOS_UINT8                           ucPdpId
);


VOS_RATMODE_ENUM_UINT32 TAF_APS_MapRatType2VosRatMode(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType
);


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

#endif /* end of TafApsCtx.h */
