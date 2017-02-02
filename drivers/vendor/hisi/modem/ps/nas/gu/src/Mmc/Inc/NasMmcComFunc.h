

#ifndef _NAS_MMC_COM_FUNC_H__
#define _NAS_MMC_COM_FUNC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#include "Nasrrcinterface.h"
#include "NasMmcCtx.h"
#include "NasMmcSndInternalMsg.h"
#include "PsRrmInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��װOSA������Ϣ�ӿ� */
#define NAS_MMC_ALLOC_MSG_WITH_HDR(ulMsgLen)\
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMC, (ulMsgLen))

/* ��װOSA��Ϣͷ�� ����MMC���ڲ���Ϣ���ͣ���Ϣ�ڴ������ʱ��û�н�ulLength��ֵ����Ҫ�ֶ���ֵ */
#define NAS_MMC_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId, ulLen)\
               { \
                ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_MMC;\
                ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
                ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
                ((MSG_HEADER_STRU *)(pstMsg))->ulLength        = (ulLen); \
               }

    /* ��װOSA��Ϣͷ(MMC�ڲ���Ϣ) */
#define NAS_MMC_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
                NAS_MMC_CFG_MSG_HDR(pstMsg, WUEPS_PID_MMC, ulMsgId)

    /* ��ȡOSA��Ϣ���� */
#define NAS_MMC_GET_MSG_ENTITY(pstMsg)\
                ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

    /* ��ȡOSA��Ϣ���� */
#define NAS_MMC_GET_MSG_LENGTH(pstMsg)\
                (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

    /* ��װOSA��Ϣ��ʼ����Ϣ���ݽӿ� */
#define NAS_MMC_CLR_MSG_ENTITY(pstMsg)\
                PS_MEM_SET(NAS_MMC_GET_MSG_ENTITY(pstMsg), 0x0, NAS_MMC_GET_MSG_LENGTH(pstMsg))

    /* ��װOSA������Ϣ�ӿ� */
#define NAS_MMC_SEND_MSG(pstMsg)\
                PS_SEND_MSG(WUEPS_PID_MMC, pstMsg)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
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

VOS_UINT32 NAS_MMC_IsNeedSndEplmn( VOS_VOID );

VOS_UINT32 NAS_MMC_GetLaiForbTypeManualSelMode(
    NAS_MML_LAI_STRU                   *pstLai
);

VOS_UINT32 NAS_MMC_GetLaiForbTypeAutoSelMode(
    NAS_MML_LAI_STRU                   *pstLai
);

VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenType(VOS_VOID);


VOS_UINT32 NAS_MMC_GetHPlmnSpecDomainAccessCapa(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegCnDomain
);

VOS_UINT32  NAS_MMC_GetPlmnIndexInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulRegPlmnListNum,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
);


VOS_UINT32  NAS_MMC_GetOptMask_WasSysinfo(
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd
);

/*ɾ��NAS_MMC_ConvertUserSpecAccessMode2MmlRat����*/

TAF_SYS_SUBMODE_ENUM_UINT8 NAS_MMC_CovertMmlSysSubModeToMsccSysSubMode(
    NAS_MML_RRC_SYS_SUBMODE_ENUM_UINT8  enSysSubMode
);

VOS_UINT32 NAS_MMC_IsHighPrioPlmnSearchVaild( VOS_VOID );


VOS_UINT32 NAS_MMC_IsHplmnTimerLenValid( VOS_VOID );


VOS_VOID NAS_MMC_ConvertRrcPlmnList2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRC_PLMN_ID_LIST_STRU                                  *pstPlmnIdList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_ConvertRrcBgPlmnSearchRslt2SearchedPlmnListInfo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    RRMM_BG_PLMN_SEARCH_CNF_ST                             *pstBgSearchRslt,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_UINT32 NAS_MMC_IsCampOnHPlmn(VOS_VOID);

VOS_UINT32 NAS_MMC_IsCampOnHighestPrioPlmn(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedStartHPlmnTimer(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(
    MMC_LMM_PLMN_ID_LIST_STRU                              *pstLMMPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo
);

VOS_VOID NAS_MMC_ConvertLmmBgPlmnSearchRslt2SearchedPlmnListInfo(
    LMM_MMC_BG_PLMN_SEARCH_CNF_STRU                        *pstLmmPlmnList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSearchedPlmnListInfo,
     NAS_MML_NET_RAT_TYPE_ENUM_UINT8                        enRatType
);

#endif
VOS_UINT32 NAS_MMC_IsPlmnWithRatInPlmnList (
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo,
    VOS_UINT32                                              ulPlmnNum
);

VOS_VOID NAS_MMC_ConvertPlmnId2NasFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT8                           ucPlmnMncNum
);
VOS_UINT32 NAS_MMC_IsPlmnMccSameWithRplmn(
    VOS_UINT32                          ulMcc
);

VOS_VOID NAS_MMC_UpdateDplmnNplmnInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_INFO_STRU                 *pstNvimCfgDPlmnNPlmnInfo
);

VOS_VOID NAS_MMC_UpdateDPlmnNPlmnFlagInfo(
    NAS_MMC_NVIM_CFG_DPLMN_NPLMN_FLAG_STRU                 *pstNvimCfgDPlmnNPlmnFlagInfo
);

VOS_UINT32 NAS_MMC_IsPlmnMccSameWithHplmn(
    VOS_UINT32                          ulMcc
);

VOS_VOID  NAS_MMC_DelDuplicatedPlmnWithRatInPlmnList (
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);
VOS_UINT32 NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId,
    VOS_UINT32                          ulEventType
);

VOS_UINT32 NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(VOS_VOID);

VOS_UINT32 NAS_MMC_IsSpecTypePlmnIdInDestPlmnList (
    NAS_MML_PLMN_ID_STRU               *pstSpecPlmnId,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    VOS_UINT8                           ucPlmnNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnIdList
);

VOS_VOID NAS_MMC_UpdateCsPsRestriction_WasInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
);

VOS_VOID NAS_MMC_UpdateCsPsRestriction_GasSysInfo(
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
);

VOS_VOID NAS_MMC_UpdateOperNameInfo(
    RRC_PLMN_ID_STRU                   *pstPlmnId
);

VOS_VOID NAS_MMC_UpdateNetworkInfo_GasSysInfo(
    struct MsgCB                       *pstMsg
);
VOS_VOID NAS_MMC_UpdateNetworkInfo_WasSysInfo(
    struct MsgCB                       *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_UpdateNetworkInfo_LmmSysInfo(
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_UpdateSuitPlmnList_LmmSysInfo(
    MMC_LMM_SYS_INFO_STRU              *pstLteSysInfo
);


#endif
NAS_MML_NET_MODE_ENUM_UINT8 NAS_MMC_ConvertGasNetModeToMmlNetMode(
    GRRMM_NW_OP_MODE_ENUM_UINT8         enGasNetMode
);

VOS_UINT32 NAS_MMC_IsOptItemVaild_WasSysInfo(
    RRMM_SYS_INFO_IND_STRU             *pstWrrSysInfo
);

VOS_VOID   NAS_MMC_ConvertRrcRatToNasFormat(
    RRC_NAS_RAT_TYPE_ENUM_UINT32        ulRrcRat,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
);


VOS_VOID NAS_MMC_ConvertNasRatToRrcFormat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32       *penRrcRat
);



VOS_VOID   NAS_MMC_ConvertRrcCoverTypeToNasFormat(
    RRC_NAS_COVERAGE_TYPE_ENUM_UINT32   enRrcCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID   NAS_MMC_ConvertLmmCoverTypeToNasFormat(
    MMC_LMM_COVERAGE_TYPE_ENUM_UINT32   enLmmCoverType,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8   *penCoverType
);
#endif

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_MMC_ConvertLmmRatToRrcFormat(
    MMC_LMM_RAT_TYPE_ENUM_UINT8         ucLmmRat,
    RRC_NAS_RAT_TYPE_ENUM_UINT32    *penRat
);
#endif

VOS_VOID NAS_MMC_GetDomainRegStatusInRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetRatType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penCsCause,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penPsCause
);


VOS_VOID NAS_MMC_NotifyModeChange(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType,
    VOS_UINT8                                   ucSimPsRegStatus
);

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsPlmnAllowedInManualMode(
    NAS_MML_PLMN_ID_STRU                         *pstPlmnId
);

VOS_UINT32 NAS_MMC_IsNeedDisableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_SysCfg(
    NAS_MMCMMC_SysCfg_RSLT_STRU        *pstSyscfgRsltMsg
);

VOS_UINT32 NAS_MMC_IsNeedDisableLte_ModeChange(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_ModeChange(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableLte_AttachCsPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_AttachCsPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedDisableLte_DetachCsPs(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedEnableLte_DetachCsPs(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsNeedDisableLte_ImsVoiceNotAvail(VOS_VOID);

VOS_VOID  NAS_MMC_SndEnableLteNotify(VOS_VOID);
VOS_VOID  NAS_MMC_SndDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
);



#endif

VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInDisabledPlmnWithForbiddenPeriodList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU       *pstPlmnIdList
);




VOS_UINT32 NAS_MMC_IsNeedDisableLteRoam(
    VOS_UINT32                          ulMcc
);

VOS_UINT32 NAS_MMC_IsNeedEnableLteRoam(
    VOS_UINT32                          ulMcc
);

VOS_UINT32 NAS_MMC_IsNeedEnableLte_ImsSwitchOnOrNotCsOnly(VOS_VOID);

VOS_UINT32 NAS_MMC_IsCampLteNormalService(VOS_VOID);

VOS_UINT32  NAS_MMC_IsReCampLteLimitedService( VOS_VOID );


#endif

VOS_UINT32  NAS_MMC_IsPlmnRegInfoAllSucc(
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegList
);

VOS_VOID NAS_MMC_GetMmlCsTransactionStatus(
    RRC_NAS_CS_TRANSACTION_ENUM_UINT8                        *penAsCsTransactionsStatus
);


VOS_VOID NAS_MMC_SortPlmnSearchListSpecRatPrioLowest(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enAdjustRatType,
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionListInfo
);

VOS_VOID NAS_MMC_UpdateCsPsRestriction_AcChangeInd(
    RRMM_W_AC_INFO_CHANGE_IND_STRU     *pstWAcChangeInd,
    NAS_MML_NETWORK_INFO_STRU          *pstNetWorkInfo
);

VOS_UINT32 NAS_MMC_IsRejectedBySpecCause(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

VOS_UINT32  NAS_MMC_IsAisRoamingEffect( VOS_VOID );

VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatusWhenRegFail(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause
);

VOS_VOID  NAS_MMC_UpdateEhplmnRat(VOS_VOID);
VOS_VOID  NAS_MMC_UpdateHomePlmn(
    VOS_UINT8                           *pucIMSI
);
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithEhplmnRatList(
    NAS_MML_PLMN_ID_STRU                stPlmnId,
    VOS_UINT16                         *pusRatForOneEhplmnItem,
    VOS_UINT32                         *pulPlmnNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstPlmnWithRatInfo
);


VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithOrigSimHplmnAct(VOS_VOID);
VOS_VOID  NAS_MMC_UpdateEhplmnRat_WithNvPrioHplmnAct(VOS_VOID);

VOS_VOID  NAS_MMC_DelLowPrioEHPlmn(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstReportList
);




VOS_VOID NAS_MMC_UpdateUserSpecPlmnRegisterStatus(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

#if (FEATURE_LTE == FEATURE_ON)

VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteRoamAbility(
    VOS_UINT32                                              ulSysInfoMcc,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
);

VOS_UINT32 NAS_MCC_IsNeedDisableLteWBand(
    VOS_UINT32                         ulBand
);
VOS_VOID  NAS_MMC_RcvGuSysInfoIndSetLteAbility(
    struct MsgCB                       *pstMsg,
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus
);

VOS_VOID    NAS_MMC_ConvertLmmPlmnIdListToGUFormat_PlmnList(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstSrcPlmnIdList,
    RRC_PLMN_ID_LIST_STRU              *pstDestPlmnIdList
);

VOS_UINT32 NAS_MMC_IsDisableLteNeedLocalReleaseEpsConn(VOS_VOID);

#endif

VOS_UINT32 NAS_MMC_IsInterNationalRoamingSearchRPLMN(
    VOS_UINT32                          ulMcc
);

VOS_VOID  NAS_MMC_DelPlmnSelectionRatInfoInPlmnWithRatList (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmn,
    VOS_UINT32                                              ulPlmnNum,
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstPlmnIdList
);

VOS_VOID  NAS_MMC_DeleteForbiddenRatInPlmnSeleInfo (
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU *pstPlmn
);

VOS_VOID NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus (VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedEnableUtran_AnyCellSearch (VOS_VOID);

VOS_UINT32 NAS_MMC_IsNeedDisableUtran_RcvGasSysInfo (VOS_VOID);

VOS_VOID NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init (VOS_VOID);


VOS_VOID  NAS_MMC_GetMccListInRrcPlmnIdList(
    VOS_UINT32                         *pulMccNum,
    VOS_UINT32                         *pulMccList,
    RRC_PLMN_ID_LIST_STRU              *pstRrcPlmnIdList
);
VOS_VOID NAS_MMC_AddPlmnListIntoSimEhplmnInfo(
    VOS_UINT32                          ulPlmnListNum,
    NAS_MML_PLMN_ID_STRU               *pstPlmnList,
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enSpecPlmnType,
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo
);

VOS_VOID NAS_MMC_DelHplmnInFplmn(VOS_VOID);

VOS_UINT32  NAS_MMC_IsCurrentWcdmaMode(VOS_VOID);

VOS_UINT32  NAS_MMC_IsCurrentTdscdmaMode(VOS_VOID);

VOS_UINT32 NAS_MMC_IsNetRatSupportedTdscdma(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_MMC_DelForbInfo_LmmAttRsltSucc(
    MMC_LMM_LAI_STRU                   *pstLmmLai,
    VOS_UINT32                          ulEpsEmergencyAttachFlag
);

VOS_UINT32  NAS_MMC_IsEpsEmergencyAttachType(
    MMC_LMM_ATTACH_TYPE_ENUM_UINT32     ulReqType
);
VOS_UINT32 NAS_MMC_IsCsPsBothRegSucc(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType
);

VOS_UINT32 NAS_MMC_IsNeedRelPsConnEnableLteTimerExpired(VOS_VOID);
VOS_UINT32 NAS_MMC_IsLmmAttachCnfTriggerPlmnSrch(
    LMM_MMC_ATTACH_CNF_STRU            *pstLmmAttachCnf
);
#endif
VOS_VOID  NAS_MMC_DelForbInfo_GuRegRsltSucc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
);
#endif

VOS_VOID  NAS_MMC_ChangeCsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucCsRegState
);

VOS_VOID  NAS_MMC_ChangePsRegState(
    NAS_MML_REG_STATUS_ENUM_UINT8       ucPsRegState
);

VOS_VOID  NAS_MMC_UpdateRegStateSpecPlmnSearch(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateRegStateAnyCellSearchSucc(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateServiceStateSpecPlmnSearch(VOS_VOID);


VOS_VOID  NAS_MMC_UpdateCsRegStateCsRegSucc(VOS_VOID);

VOS_VOID  NAS_MMC_UpdatePsRegStatePsRegSucc(VOS_VOID);

VOS_VOID NAS_MMC_ConvertToMsccSrvStatus(
    NAS_MMC_SERVICE_ENUM_UINT8          enMmcServiceState,
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32 *penMsccServiceState
);
VOS_VOID  NAS_MMC_ChangeServiceState(
    VOS_UINT32                          ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
);

VOS_VOID  NAS_MMC_UpdateServiceState_RegSucc(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  ulCnDomainId,
    NAS_MMC_SERVICE_ENUM_UINT8          enServiceState
);

NAS_MML_MS_MODE_ENUM_UINT8  NAS_MMC_ConvertMsccMsModeToMmlMsMode(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32    enMsccMsMode
);
NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8  NAS_MMC_GetCsDomainCapaChangeType(
    NAS_MML_MS_MODE_ENUM_UINT8          enOldMsMode,
    NAS_MML_MS_MODE_ENUM_UINT8          enNewMsMode
);

VOS_VOID NAS_MMC_DelForbPlmnFromAsSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    *pstSrchedPlmn
);


VOS_VOID NAS_MMC_DelNotUserSpecPlmnFromSrchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstSrchedPlmn
);

VOS_VOID NAS_MMC_UpdateSearchedPlmnListInfo(
    RRC_PLMN_ID_LIST_STRU                                  *pstRrcList,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
);

VOS_UINT32 NAS_MMC_IsExistAvailPlmnInSearchedPlmnList(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pastIntraPlmnSrchInfo
);

VOS_VOID NAS_MMC_InitSearchedPlmnListInfo(
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstListInfo
);



VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrchCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);
VOS_UINT32  NAS_MMC_IsSingleDomainRegFailNeedPlmnSrch(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enRegFailDomain
);

VOS_UINT32 NAS_MMC_IsRegReqTriggerPlmnSrch_L1Main(
    MSCC_MMC_REG_REQ_STRU                         *pstRegReq
);

VOS_VOID NAS_MMC_BuildEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU         *pstOutEplmnInfo
);


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_CsRegErrRecord(MMMMC_CS_REG_RESULT_IND_STRU *pstCsRegRstInd);
VOS_VOID NAS_MMC_PsRegErrRecord(GMMMMC_PS_REG_RESULT_IND_STRU *pstPsRegRstInd);
VOS_VOID NAS_MMC_PsServiceRegErrRecord(GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU *pstServiceRsltInd);
/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
VOS_VOID NAS_MMC_CmServiceRejErrRecord(
    VOS_UINT32                                       ulCause,
    VOS_UINT32                                       ulServiceStatus
);
VOS_VOID NAS_MMC_MoDetachIndRecord(
    VOS_UINT32                              ulDetachType
);
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */

VOS_VOID NAS_MMC_LteNwSearchCnfInfoRecord(
    VOS_VOID                           *pstMsg
);
VOS_VOID NAS_MMC_ProcNwSearchInfoRecord(
    VOS_VOID                           *pstMsg
);
#endif

VOS_UINT32 NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(
    VOS_UINT32                          ulUserSpecSearchFlg
);


VOS_VOID NAS_MMC_RegisterRrmResourceNtf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
);

VOS_VOID NAS_MMC_DeregisterRrmResourceNtf(
    VOS_RATMODE_ENUM_UINT32             enNasRat,
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
);

VOS_VOID NAS_MMC_DeregisterRrmResourceNtfAllRat(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enRrmTaskType
);

VOS_RATMODE_ENUM_UINT32 NAS_MMC_ConvertRatToRrmPsRat(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMmcRat
);

VOS_VOID NAS_MMC_ErrLogRecordCsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldCsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewCsRegStatus
);
VOS_VOID NAS_MMC_ErrLogRecordPsOosCause(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldPsRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewPsRegStatus
);
VOS_VOID NAS_MMC_ErrLogClrNwSearchCount(
    NAS_MML_REG_STATUS_ENUM_UINT8        enOldRegStatus,
    NAS_MML_REG_STATUS_ENUM_UINT8        enNewRegStatus
);
VOS_VOID NAS_MMC_RecordOosEvent(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32    enOosCause
);
VOS_VOID NAS_MMC_RecordOosEventForPlmnSearchScene(
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32    enPlmnSearchScene
);
VOS_VOID NAS_MMC_RecordOosEventForDetachReason(
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32  enDetachReason
);

VOS_UINT32 NAS_MMC_IsCampOnHighestPrioRatHplmn(VOS_VOID);

VOS_UINT32 NAS_MMC_IsHighPrioRatHplmnSearchVaild( VOS_VOID );

VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer(VOS_VOID);

VOS_VOID NAS_MMC_UpdateHighPrioRatHPlmnTimerTdCount(VOS_VOID);
VOS_UINT32 NAS_MMC_IsNeedStartHighPrioRatHPlmnTimer_CsfbEnd( VOS_VOID );

VOS_UINT32  NAS_MMC_IsSorTriggerAdditionalLau(VOS_VOID);

NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8 NAS_MMC_GetPlmnPrioClass(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

VOS_UINT32 NAS_MMC_ComParePlmnPrioClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enSrcPrioClass,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enDestPrioClass
);

VOS_UINT32 NAS_MMC_IsSuccRegInSpecCellInfo(
    MSCC_MMC_REG_CELL_INFO_STRU         *pstCellInfo
);

NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccRegReq(
    MSCC_MMC_REG_REQ_STRU               *pstRegReq
);

VOS_VOID   NAS_MMC_Convert3GPP2RatType(
    NAS_MSCC_PIF_3GPP2_RAT_TYPE_ENUM_UINT8   enMSCC3GPP2RatType,
    NAS_MML_3GPP2_RAT_TYPE_ENUM_UINT8  *penMML3GPP2RatType
);

VOS_VOID NAS_MMC_SndMsccCurrServiceRelatedInfo(VOS_VOID);

VOS_VOID  NAS_MMC_UpdateDPlmnNPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
);
VOS_VOID  NAS_MMC_DeleteDPlmnNPlmnList(
    NAS_MML_PLMN_ID_STRU               *pstCurrPlmn,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRegDomain,
    VOS_UINT16                                             *pulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
);
VOS_UINT16  NAS_MMC_ConvertNetRatToSimRat(NAS_MML_NET_RAT_TYPE_ENUM_UINT8   enPlmnNetRat);

VOS_UINT32 NAS_MMC_IsBcchPlmnIdWithRatInDestSimPlmnList (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstBcchPlmnIdWithRat,
    VOS_UINT16                          usSimPlmnWithRatNum,
    NAS_MML_SIM_PLMN_WITH_RAT_STRU     *pstSimPlmnWithRatList
);

VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithUplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
);

VOS_UINT32 NAS_MMC_ComparePlmnIdWithRatWithOplmn (
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnIdWithRat
);

VOS_UINT32 NAS_MMC_IsPlmnIdWithSimRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_ID_STRU                                   *pstPlmnId,
    VOS_UINT16                                              usSimRat,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
);

VOS_UINT32 NAS_MMC_IsPlmnIdWithRatInSimPlmnWithRegDomainList(
    NAS_MML_PLMN_WITH_RAT_STRU                             *pstSrcPlmnId,
    VOS_UINT32                                              ulDestPlmnNum,
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU                  *pstDestPlmnIdList
);
NAS_MML_NET_RAT_TYPE_ENUM_UINT8  NAS_MMC_ConvertSimRatToNetRat(
    VOS_UINT16                          usSimRat
);




VOS_UINT32 NAS_MMC_IsEnableLteTriggerPlmnSearch_ImsSwitchOnOrNotCsOnly(VOS_VOID);

/* Added by y00307564 for CDMA Iteration 8 2015-3-3 begin */
VOS_BOOL NAS_MMC_IsPlmnValid(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
);

VOS_VOID NAS_MMC_PlmnId2Bcd(
    NAS_MSCC_PIF_PLMN_ID_STRU          *pstPlmnId
);

VOS_VOID NAS_MMC_PlmnId2NasStyle(NAS_MSCC_PIF_PLMN_ID_STRU *pstPlmnId);

VOS_UINT16 NAS_MMC_GetUpdateFileForPrefPlmn(
    NAS_MSCC_PIF_PARA_TYPE_ENUM_UINT8                       enPrefPLMNType
);
/* Added by y00307564 for CDMA Iteration 8 2015-3-3 end */

VOS_UINT32 NAS_MMC_GetWaitAsResumeIndTimerLen(VOS_VOID);

VOS_UINT32 NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen(VOS_VOID);

VOS_UINT32 NAS_MMC_GetWaitAsOosResumeIndTimerLen(VOS_VOID);

VOS_UINT8  NAS_MMC_IsNeedHistorySearch_L1Main(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_IsDetachReqestDisableLte(
    NAS_MMC_DETACH_TYPE_ENUM_UINT32     enDetachType,
    NAS_MMC_DETACH_REASON_ENUM_UINT32   enDetachReason
);
#endif
VOS_VOID NAS_MMC_ConvertMsccHighPrioPlmnListToMmcPlmnListInfo(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo,
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstMmcPlmnListInfo
);

NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32 NAS_MMC_GetPlmnSearchSceneMsccPlmnSrchReq(
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstPlmnSrchReq
);

VOS_UINT32  NAS_MMC_IsRatPrioChangeTriggerPlmnSrch(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstNewRatList  
);

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, begin */
VOS_UINT32 NAS_MMC_StartPlmnSearchPhaseOneTotalTimer(VOS_VOID);
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-26, end */

NAS_ERR_LOG_RATMODE_ENUM_UINT8 NAS_MMC_ConvertRatTypeFromNasMsccToNasErr (
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8 msccRatType
);
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_MMC_RecordFftSrchMccInfo( VOS_VOID );
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

#endif /* end of NasMmcComFunc.h */

