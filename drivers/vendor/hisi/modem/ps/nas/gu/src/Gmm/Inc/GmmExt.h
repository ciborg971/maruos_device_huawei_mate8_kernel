
#ifndef _GMMEXTERN_H_
#define _GMMEXTERN_H_


#include "GmmApi.h"
#include "MmcGmmInterface.h"
#include "LLInterface.h"
#include "MM_Share.h"
#include "GmmStru.h"
#include "GmmRabmInterface.h"
#include "Nasrrcinterface.h"

#include "NasStkInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "GmmLmmInterface.h"
#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "MtcGmmInterface.h"
#endif

#include "SmsGmmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
  2 ȫ�ֱ���������
*****************************************************************************/

extern   NAS_GMM_CTRL_STATUS_ENUM_UINT8   gucGmmInitState;
extern GMM_GLOBAL_CTRL_STRU          g_GmmGlobalCtrl;
extern GMM_TIMER_STRU                g_GmmTimerMng;
extern GMM_ATTACH_CTRL_STRU          g_GmmAttachCtrl;
extern GMM_RAU_CTRL_STRU             g_GmmRauCtrl;
extern GMM_DOWNLINK_NPDU_STRU        g_GmmDownLinkNpduBake;
extern GMM_DETACH_CTRL_STRU          g_GmmDetachCtrl;
extern GMM_AUTHEN_CTRL_STRU          g_GmmAuthenCtrl;
extern GMM_REQ_CNF_MNG_STRU          g_GmmReqCnfMng;
extern GMM_IMPORTED_FUNC_LIST_STRU   g_GmmImportFunc;
extern GMM_SR_CTRL_STRU              g_GmmServiceCtrl;
extern HTIMER                        g_stGmmProtectRrRelTimer;
extern GMM_SUSPEND_CTRL_STRU   gstGmmSuspendCtrl;

extern GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU g_GmmInterRatInfoCtrl;


extern MM_SUB_LAYER_SHARE_STRU     g_MmSubLyrShare;

extern VOS_UINT8     g_GmmInterRatCellReselect;

extern GMM_SPEC_PROC_CONTEXT_STRU    g_stGmmSpecProcCtxToGetLmmSecInfo;
extern VOS_BOOL                      g_HaveGotLmmSecInfo;

extern VOS_UINT8                       gucLteGutiValid ;


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_GMM_GetGmmState()          (g_GmmGlobalCtrl.ucState)
#define NAS_GMM_GetSpecProc()           (g_GmmGlobalCtrl.ucSpecProc)

#define NAS_GMM_GetPeriodicRauFlag()    (g_GmmRauCtrl.ucPeriodicRauFlg)

#define NAS_GMM_GetUeIdMask()                   (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask)
#define NAS_GMM_GetUeIdRadioCpbAddr()           (g_GmmGlobalCtrl.UeInfo.aucRadioCpb)

#define NAS_GMM_GetNasTokenAddr()               (g_GmmGlobalCtrl.stMappedUeInfoFromEps.aucNasToken)
#define NAS_GMM_GetMappedPtmsiAddr()            (g_GmmGlobalCtrl.stMappedUeInfoFromEps.aucPtmsi)
#define NAS_GMM_GetMappedRaiAddr()              (&g_GmmGlobalCtrl.stMappedUeInfoFromEps.Rai)
#define NAS_GMM_SetMappedRai(stRaiValue)        (g_GmmGlobalCtrl.stMappedUeInfoFromEps.Rai = stRaiValue)
#define NAS_GMM_SetMappedLai(stLaiValue)        (g_GmmGlobalCtrl.stMappedUeInfoFromEps.Rai.Lai= stLaiValue)

#define NAS_GMM_GetMappedPtmsiSignAddr()        (g_GmmGlobalCtrl.stMappedUeInfoFromEps.aucPtmsiSignature)



#define NAS_GMM_GetLmmSecInfoFlg()              (g_HaveGotLmmSecInfo)
#define NAS_GMM_SetLmmSecInfoFlg(bFlg)          (g_HaveGotLmmSecInfo = bFlg)

#define NAS_GMM_ClearIMSIOfUeID()               (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI)

#define NAS_GMM_SetSpecProcNeedSecInfo(ucSpec)  (g_stGmmSpecProcCtxToGetLmmSecInfo.enGmmSpecProc = (ucSpec))
#define NAS_GMM_SetRauUpdateType(ucPara)        (g_stGmmSpecProcCtxToGetLmmSecInfo.ucRauType = (ucPara))

#define NAS_GMM_GetSpecProcNeedSecInfo()        (g_stGmmSpecProcCtxToGetLmmSecInfo.enGmmSpecProc)
#define NAS_GMM_GetRauUpdateType()              (g_stGmmSpecProcCtxToGetLmmSecInfo.ucRauType)

#define NAS_GMM_SetSpecProcInCsTrans(ucvalue)   (g_GmmGlobalCtrl.ucSpecProcInCsTrans = ucvalue)
#define NAS_GMM_SetRetryRauForRelCtrlFlg(ucvalue)   (g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = ucvalue)

#define NAS_GMM_SetT3312ExpiredFlg(ucvalue)     (g_GmmRauCtrl.ucT3312ExpiredFlg = ucvalue)
#define NAS_GMM_GetT3312ExpiredFlg()            (g_GmmRauCtrl.ucT3312ExpiredFlg)


#define NAS_GMM_SetLteGutiValid(ucPara)         (gucLteGutiValid = ucPara)
#define NAS_GMM_GetLteGutiValid()               (gucLteGutiValid)


extern VOS_VOID NAS_GMM_SndLmmHoSecuInfoReq( VOS_VOID );
extern VOS_VOID NAS_GMM_SndLmmReselSecuInfoReq( VOS_VOID );

extern VOS_VOID NAS_GMM_SndLmmInfoChangeNotifyReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           bitOpConnState,
    VOS_UINT8                           bitOpGprsSuspend,
    VOS_UINT8                           ucSrvState,
    VOS_UINT32                          ulGprsSuspendFlg
);

/* GmmAttach.c�к��������� */
extern VOS_VOID NAS_GMM_Fill_IE_PtmsiFromSrc(
    VOS_UINT8                           *pucDestAddr,
    VOS_UINT8                           *pucSrcAddr
);
extern VOS_VOID NAS_GMM_Fill_IE_RaiFromSrc(
    VOS_UINT8                          *pucDestAddr,                           /* ��дP-TMSI���׵�ַ                       */
    GMM_RAI_STRU                       *pstRaiAddr
);
extern VOS_VOID NAS_GMM_Fill_IE_AdditionalOldRaiFromSrc(
    VOS_UINT8                          *pucDestAddr,                           /* ��дP-TMSI���׵�ַ                       */
    GMM_RAI_STRU                       *pucSrcRaiAddr
);
VOS_UINT8 NAS_Gmm_FillRaiForSnd(
    VOS_UINT8                          *pucAddr
);

VOS_UINT8  NAS_GMM_Fill_IE_UeNetwrokCapacity(
    VOS_UINT8                          *pucAddr
);

VOS_UINT8 NAS_Gmm_Fill_IE_AdditionalOldRAI(
    VOS_UINT8                          *pucAddr
);
VOS_UINT8 NAS_Gmm_Fill_IE_AdditionalMobileIdentity(
    VOS_UINT8                          *pucAddr
);

VOS_UINT8 NAS_Gmm_FillPtmsiIeForSnd(
    VOS_UINT8                          *pucAddr
);

VOS_UINT8 NAS_Gmm_FillPtmsiSignatureIeForSnd(
    VOS_UINT8                          *pucAddr
);

VOS_VOID GMM_Fill_IE_ClassMark2(
    VOS_UINT8                          *pClassMark2                             /* ��дClassMark2 IE���׵�ַ   */
);
VOS_UINT8 GMM_Fill_IE_FDD_ClassMark3(
    VOS_UINT8                          *pClassMark3                             /* ��дClassMark3 IE���׵�ַ   */
);
VOS_UINT8 GMM_Fill_IE_TDD_ClassMark3(
    VOS_UINT8                          *pClassMark3                             /* ��дClassMark3 IE���׵�ַ   */
);
VOS_UINT8  GMM_CALL_FillIeSupCodecList(
    VOS_UINT8                          *pstCodecList                            /* ��дsupport codec IE���׵�ַ   */
);

extern VOS_VOID NAS_GMM_SndAttachReq(VOS_VOID);

extern VOS_VOID  Gmm_FillRaiForRcv(GMM_RAI_STRU *, VOS_UINT8 *);
extern VOS_UINT8 Gmm_AttachRauAcceptJudgeRai(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_FillDrxPara(VOS_UINT8 *);

extern VOS_UINT8 Gmm_Fill_IE_NetworkCapability(VOS_UINT8 *pAddr);
extern VOS_UINT8 Gmm_Fill_IE_RadioAccessCapability(VOS_UINT8 *pAddr);

extern NAS_MSG_STRU* Gmm_AttachRequestMsgMake(VOS_VOID);
extern NAS_MSG_STRU* Gmm_AttachCompleteMsgMake(VOS_VOID);
extern VOS_VOID  Gmm_DelPsLocInfoUpdateUsim(VOS_VOID);
extern VOS_VOID  Gmm_AttachRejectCause3(VOS_UINT32);

extern VOS_VOID  Gmm_AttachRejectCause11(VOS_VOID);

extern VOS_VOID  Gmm_AttachRejectCause12(VOS_UINT32, VOS_BOOL bUpdateSimFlg);
extern VOS_VOID  Gmm_AttachRejectCause14(VOS_BOOL bUpdateSimFlg);

extern VOS_VOID  Gmm_AttachAttemptCounter(VOS_UINT32);
extern VOS_VOID NAS_GMM_ChangeRegRejCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg);
extern VOS_VOID NAS_GMM_ChangeDetachCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg);
extern VOS_VOID NAS_GMM_ChangePsSerRejCauseAvoidInvalidSim(VOS_UINT8 *pucRcvMsg);

extern VOS_VOID NAS_GMM_HandleHplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
);
extern VOS_VOID NAS_GMM_HandleVplmnRejCauseChange(
    NAS_MML_CHANGE_REJ_TYPE_ENUM_UINT8  enChangeRejType,
    VOS_UINT8                          *pucRcvMsg
);
extern VOS_VOID NAS_GMM_ResetRejCauseChangedCounter (VOS_VOID);

extern VOS_VOID NAS_GMM_SndStkAttachRej(VOS_UINT8 ucCause);


extern NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmAttachTypeToStkRauType (
                                         NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8 enGmmAttachType
                                         );


extern VOS_VOID  Gmm_RcvAttachRejectMsg(NAS_MSG_FOR_PCLINT_STRU *);

extern VOS_VOID  NAS_GMM_CheckCauseToStartT3340(
    VOS_UINT8                           ucCause
);

extern VOS_VOID Gmm_AttachRauAcceptCause16(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGmmCause
);
extern VOS_VOID  Gmm_SaveTimerValue(VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_AttachAcceptResolveIe(GMM_MSG_RESOLVE_STRU *, NAS_MSG_FOR_PCLINT_STRU *);
extern  VOS_VOID Gmm_AttachAcceptGprsOnly(
    GMM_MSG_RESOLVE_STRU                *pAttachAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_BOOL                            bTlliUpdateFlg,
    VOS_UINT8                           ucInterRatInfoFlg
);
extern VOS_VOID  Gmm_AttachAcceptCombined(GMM_MSG_RESOLVE_STRU *, NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_AttachAcceptHandle(NAS_MSG_FOR_PCLINT_STRU *,VOS_BOOL  bTlliUpdateFlg);
extern VOS_VOID  Gmm_SndAttachReq(VOS_VOID);
/* BEGIN: Modified by liurui id:40632, 2006/7/26   PN:A32D03975 */
extern VOS_VOID  Gmm_AttachInitiate(VOS_UINT8 ucSpecProc);
/* END:   Modified by liurui id:40632, 2006/7/26   PN:A32D03975 */
extern VOS_VOID  Gmm_RcvSmEstablishReq(VOS_VOID  *pMsg );
extern VOS_VOID  Gmm_RcvAttachAcceptMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq(VOS_VOID *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RegInit(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RauInit(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_ServReqInit(MMCGMM_ATTACH_REQ_STRU *);

extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_DeregNmlServ(MMCGMM_ATTACH_REQ_STRU *);

extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_DeregLimitServ(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_DeregAtmpToAtch(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RegNmlServ(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdt(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RegLimitServ(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  Gmm_RcvMmcGmmAttachReq_RegAtmpToUpdtMm(MMCGMM_ATTACH_REQ_STRU *);
extern VOS_VOID  GMM_RcvMmcRelReq(VOS_VOID* );

extern VOS_VOID NAS_GMM_RcvMmcRelReq_RegInit(VOS_VOID);
extern VOS_VOID NAS_GMM_RcvMmcRelReq_DeregInit(VOS_VOID);
extern VOS_VOID NAS_GMM_RcvMmcRelReq_RauInit(VOS_VOID);
extern VOS_VOID NAS_GMM_RcvMmcRelReq_RegImsiDtchInit(VOS_VOID);
extern VOS_VOID NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo(VOS_VOID);

extern VOS_VOID  Gmm_RcvSmsUnitdataReq(VOS_VOID *);

extern VOS_VOID  NAS_GMM_BufferSmsEstReq(
    VOS_VOID                            *pMsg
);
extern VOS_VOID  Gmm_RcvSmsEstReq(VOS_VOID *);

extern VOS_UINT8 Gmm_AttachAccept_Mandatory_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IeCheck_Allocated_Ptmsi(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IeCheck_Ms_Identity(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IeCheck_T3302_Value(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                              VOS_UINT8    ucIeOffset,
                                              VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IeCheck_Equivalent_Plmns(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                              VOS_UINT8    ucIeOffset,
                                              VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IECheck_AttachAccept(NAS_MSG_FOR_PCLINT_STRU *pMsg);

extern VOS_VOID Gmm_ComPlmnSearchInit();

/* GmmComm.c�к��������� */
extern VOS_VOID  Gmm_RcvRrmmPagingInd(VOS_VOID *);
extern VOS_VOID  Gmm_PagingInd_common(VOS_VOID);
extern VOS_VOID  Gmm_Attach_Prepare(VOS_VOID);
extern VOS_VOID  Gmm_RcvRrmmPagingInd_DeregInit(RRMM_PAGING_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmPagingInd_RauInit(RRMM_PAGING_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmPagingInd_ServReqInit(RRMM_PAGING_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmPagingInd_RegNmlServ(RRMM_PAGING_IND_STRU *);
extern VOS_VOID  Gmm_RcvAgentUsimAuthenticationCnf(VOS_VOID *);

/* Modified by wjf for USIM-Interface-Change 20050202 begin */
/* extern VOS_VOID  Gmm_Com_RcvAgentUsimAuthenticationCnf(AGENT_USIM_AUTHENTICATION_CNF_STRU *); */
/* Modified by h00313353 for iteration 9, 2015-2-6, begin */
extern VOS_VOID  Gmm_Com_RcvAgentUsimAuthenticationCnf(USIMM_AUTHENTICATION_CNF_STRU *);
/* Modified by h00313353 for iteration 9, 2015-2-6, end */
/* Modified by wjf for USIM-Interface-Change 20050202 end   */

extern VOS_VOID  Gmm_RcvPtmsiReallocationCommandMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_ForceToStandby(
                                      VOS_UINT8 ucForceToStandby
                                      );
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_No_Rand_Handling(VOS_VOID);
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Umts_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn,
                                                  VOS_UINT8 *pAutn);
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Gsm_Auth_Handling(
                                                  VOS_UINT8  ucCksnFlag,
                                                  VOS_UINT8 *pCksn);
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_Auth_Fail_Handling(
                                                  VOS_UINT8 ucGmmAuthType);
extern VOS_VOID Gmm_RcvAuthenAndCipherRequestMsg_T3314_Handling(VOS_VOID);
extern VOS_UINT8 Gmm_RcvAuthenAndCipherRequestMsg_Preprocess(
                                                NAS_MSG_FOR_PCLINT_STRU *pMsg
                                                );
extern VOS_VOID  Gmm_RcvAuthenAndCipherRequestMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvAuthenAndCipherRejectMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvIdentityRequestMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvGmmInformationMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern NAS_MSG_STRU *Gmm_PtmsiReallocationCompleteMsgMake(VOS_VOID);
extern NAS_MSG_STRU *Gmm_AuthenAndCipherResponseMsgMake(VOS_UINT8);
extern NAS_MSG_STRU *Gmm_AuthenAndCipherFailureMsgMake(VOS_UINT8, VOS_UINT8, VOS_UINT8 *);
extern NAS_MSG_STRU *Gmm_IdentityResponseMsgMake(VOS_UINT8);
extern VOS_VOID Gmm_Start_StopedRetransmissionTimer(VOS_VOID);
extern VOS_VOID Gmm_Stop_RetransmissionTimer(VOS_VOID);
extern VOS_VOID Gmm_AuCntFail(VOS_VOID);
extern VOS_VOID Gmm_Au_MacAutnWrong(VOS_UINT8  ucWrongCause);
/* Added by cxd for agent 20050125 begin */
extern VOS_VOID  Gmm_RcvGmmStatusMsg(NAS_MSG_FOR_PCLINT_STRU *);
/* Added by cxd for agent 20050125 end   */
extern VOS_UINT8 Gmm_RcvPtmsiRelocCmdIEChk(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ENUM_UINT8 );
extern VOS_VOID Gmm_ComGprsCipherHandle(VOS_VOID);
extern VOS_VOID NAS_GMM_SuspendLlcForInterSys(VOS_VOID);

/* GmmDetach.c�к��������� */
extern VOS_VOID  Gmm_RcvMmcDetachReq(VOS_VOID *);
extern VOS_VOID NAS_GMM_ProcDetachReq_RegNmlServ(MMCGMM_DETACH_REQ_STRU*, VOS_UINT32);
extern NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_GMM_GetRegUptNeededPsSrvStatus(VOS_VOID);
extern VOS_VOID  Gmm_MsInitNormalDetach(VOS_UINT32);
extern VOS_VOID  Gmm_Com_MsInitNormalDetach(VOS_VOID);
extern VOS_VOID  Gmm_RcvMmcPowerOffReq(VOS_VOID *);
extern VOS_VOID  Gmm_PowerOffDetach(VOS_VOID);
extern NAS_MSG_STRU* Gmm_DetachRequestMsgMake(VOS_VOID);
extern VOS_VOID  Gmm_RcvDetachRequestMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvDetachRequestMsg_RegInit(VOS_UINT8, VOS_UINT8);

extern VOS_VOID  Gmm_RcvDetachRequestMsg_DeregInit(VOS_UINT8, VOS_UINT8);

extern VOS_VOID  Gmm_RcvDetachRequestMsg_RauInit(VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvDetachRequestMsg_ServReqInit(VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvDetachRequestMsg_RegNmlServ(VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvDetachRequestMsg_RegAtmpToUpdtMm(VOS_UINT8, VOS_UINT8);

extern VOS_VOID  Gmm_RcvDetachRequestMsg_RegImsiDtchInit(VOS_UINT8, VOS_UINT8);

extern VOS_VOID  Gmm_NetInitNotRequiredDetach(VOS_UINT8);
extern VOS_VOID  Gmm_Com_Cause2Detach(VOS_VOID);
extern VOS_VOID  Gmm_Com_CauseDetach(VOS_UINT8);
extern VOS_VOID  Gmm_NetInitRequiredDetach(VOS_VOID);
extern VOS_VOID  Gmm_NetInitImsiDetach(VOS_VOID);
extern NAS_MSG_STRU* Gmm_DetachAcceptMsgMake(VOS_VOID);
extern VOS_VOID  Gmm_RcvDetachAcceptMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvDetachAcceptMsg_DeregInit(VOS_VOID);
extern VOS_VOID  Gmm_RcvDetachAcceptMsg_RegImsiDtchInit(VOS_VOID);
extern VOS_VOID  Gmm_RcvMmcDetachReq_RegNoCell(VOS_VOID);

extern VOS_VOID Gmm_SimRemoveDetach(VOS_VOID *);



extern VOS_VOID  GmmMsgProc(struct MsgCB*);
extern VOS_VOID  Gmm_MsgDistribute(VOS_VOID *);

extern VOS_UINT32 GMM_ComCheckRauIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT32  ulMsgLen);

extern VOS_UINT32 GMM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent, VOS_UINT32  ulMsgLen);

extern VOS_VOID  Gmm_RcvRrmmDataInd(VOS_VOID *);
extern VOS_VOID  Gmm_RcvSmPdpStatusInd(VOS_VOID *);
extern VOS_VOID  NAS_GMM_RcvSmPdpDeactivatedInd(VOS_VOID *);
extern VOS_VOID  Gmm_RcvMmcPlmnUserSelReq(VOS_VOID);

extern VOS_VOID NAS_GMM_RcvSmBeginSessionNotify_PreProc(
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionMsg
);
extern VOS_VOID NAS_GMM_RcvSmEndSessionNotify_PreProc(
    GMMSM_END_SESSION_NOTIFY_STRU      *pstEndSessionMsg
);

extern VOS_VOID NAS_GMM_RcvSmPdpModifyInd(VOS_VOID *pRcvMsg);

#define Gmm_MemCpy(pDestBuffer, pSrcBuffer,Count) PS_MEM_CPY((pDestBuffer), (pSrcBuffer), (Count))
#define Gmm_MemSet(pBuffer,ucData,Count) PS_MEM_SET((pBuffer), (ucData), (Count))


#define Gmm_MemMalloc(ulSize) PS_MEM_ALLOC(WUEPS_PID_GMM,ulSize)
#define Gmm_MemFree(pMem) PS_MEM_FREE(WUEPS_PID_GMM,pMem)

extern VOS_VOID  Gmm_RcvMmcCoverageLostInd(VOS_VOID);
extern VOS_VOID  Gmm_RcvMmcPlmnSearchInitiated(VOS_VOID);

extern VOS_VOID  Gmm_RcvMmcStartReq(VOS_VOID);

extern VOS_VOID  Gmm_RcvMmcGmmModeChangeReq(VOS_VOID *);

extern VOS_UINT8 Gmm_ComUnrealProc(VOS_VOID);
extern VOS_VOID  Gmm_ComForbiddenList(VOS_UINT32);

extern VOS_UINT8 Gmm_ComGetFollowOnFlg(VOS_VOID);
extern VOS_VOID  Gmm_ComReset(VOS_VOID);
extern VOS_UINT8 Gmm_DealWithBuffInProc(VOS_VOID);
extern VOS_VOID NAS_GMM_FreeBufferCmMsg(VOS_VOID);
extern VOS_VOID  Gmm_DealWithBuffAfterProc(VOS_VOID);

extern VOS_VOID  Gmm_RcvRrmmEstCnf(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_RegInit(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_DeregInit(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_RauInit(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_ServReqInit(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_DeregNmlServ(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmEstCnf_RegImsiDtchInit(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmRelInd(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmRelInd_RegInit(RRMM_REL_IND_STRU *pRrRelInd);
extern VOS_VOID  Gmm_RcvRrmmRelInd_DeregInit(RRMM_REL_IND_STRU *pRrRelInd);
extern VOS_VOID  Gmm_RcvRrmmRelInd_RauInit(RRMM_REL_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmRelInd_ServReqInit(RRMM_REL_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmRelInd_RegNmlServ(RRMM_REL_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmRelInd_RegImsiDtchInit(RRMM_REL_IND_STRU *pRrRelInd);
extern VOS_VOID Gmm_RcvRrmmRelInd_DeregNmlServ(VOS_VOID);

extern VOS_VOID Gmm_RcvRrmmEstCnfAccessBar_RauInit( VOS_VOID );

extern VOS_VOID Gmm_RcvRrmmRelInd_PlmnSearch(VOS_VOID);

extern VOS_VOID NAS_GMM_ProcRauHoldProcedure_RcvCoverLost(VOS_VOID);

extern VOS_VOID Gmm_RcvCoverLost_RegInit(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_DeregInit(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_RauInit(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_ServReqInit(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_RegNmlServ(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_RegImsiDtchInit(VOS_VOID);
extern VOS_VOID Gmm_RcvCoverLost_SuspendWaitForSys(VOS_VOID);

extern  VOS_VOID Gmm_Get_Location_Change_info(
    GMM_RAI_STRU                       *pRai1,
    GMM_RAI_STRU                       *pRai2,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg,
    VOS_UINT8                           ucNetMod
);
extern VOS_UINT8 Gmm_Compare_Rai(GMM_RAI_STRU  *pRAI1,
                                 GMM_RAI_STRU  *pRAI2);
extern VOS_UINT8 Gmm_Compare_Lai(GMM_LAI_STRU *pLAI1,
                                 GMM_LAI_STRU *pLAI2);
extern VOS_UINT8 Gmm_Compare_Plmnid(GMM_PLMN_ID_STRU *pPlmnId1,
                                    GMM_PLMN_ID_STRU *pPlmnId2 );

extern VOS_VOID  Gmm_RcvMmcSysInfoInd(VOS_VOID *);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RegInit(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_DeregInit(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RauInit(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_ServReqInit(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_DeregNmlServ(VOS_VOID *, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RegNmlServ(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RegUpdtNeed(VOS_VOID *, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  Gmm_RcvMmcSysInfoInd_RegNoCell(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);
extern VOS_VOID  NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(VOS_VOID *, VOS_UINT8, VOS_UINT8, VOS_UINT8);

extern VOS_VOID  Gmm_RcvMmcSysInfoInd_SuspWaitSys(VOS_VOID* pRcvMsg,VOS_UINT8 ucRaiChgFlg,VOS_UINT8 ucLaiChgFlg);
extern VOS_VOID GMM_PrintState(VOS_VOID);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd(NAS_MSG_STRU*);
extern VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiChg();
extern VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire();
extern VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire();
extern VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg();
extern VOS_VOID NAS_GMM_ComProcAcInfoChgInd( MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
extern VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(MMCGMM_W_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd);
VOS_UINT32 GMM_IsServiceExist(VOS_VOID);
VOS_UINT32 Gmm_IsSrvStateReady(VOS_VOID);

extern VOS_UINT8 Gmm_ComCmpLai(GMM_LAI_STRU *);

extern VOS_VOID Gmm_RcvMmcAuthenticationFailureInd(VOS_VOID);
extern VOS_VOID Gmm_RcvMmcCmServiceInd(VOS_VOID *);

extern VOS_VOID Gmm_RcvSmDataReq(VOS_VOID *);
extern VOS_VOID Gmm_RcvSmDataReq_RegNmlServ(VOS_VOID *);
extern VOS_VOID Gmm_RcvCmServReq_RegAtmpToUpdt(VOS_VOID *pMsg);
extern VOS_VOID Gmm_RcvCmServReq_DeregAtmpToAtch(VOS_VOID *pMsg);

VOS_UINT8 NAS_GMM_GetGmmSmDataReqMsgType(NAS_MSG_STRU *pstMsg);

extern VOS_VOID Gmm_ComStaChg(VOS_UINT8);
extern VOS_VOID Gmm_ComVariantInit(VOS_VOID);
extern VOS_VOID Gmm_TaskInit(VOS_VOID);
extern VOS_VOID Gmm_HoldBufferFree(VOS_VOID);

extern VOS_VOID Gmm_RcvMmcRegisterInitiation(VOS_VOID *);
extern VOS_VOID Gmm_RcvMmcRegisterInitiation_ServReqInit(VOS_VOID *);
extern VOS_VOID Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch(VOS_VOID);
extern VOS_VOID Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt(VOS_VOID);

extern VOS_VOID GMM_RcvCellReselectInd( VOS_VOID *pRcvMsg );

extern NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8  Gmm_ComServiceSts(VOS_VOID);
extern VOS_UINT32 Gmm_GetServiceStatusForSms(VOS_VOID);

extern VOS_VOID Gmm_ComNetModeChange_NotSupportGprs_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucLaiChgFlg);

extern VOS_VOID Gmm_ComNetModeChange_Netmode_I2II_Handling(
                                                  VOS_UINT8 ucNetMod,
                                                  VOS_UINT8 ucRaiChgFlg);

extern VOS_VOID Gmm_ComNetModeChange_Netmode_II2I_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucRaiChgFlg);
extern VOS_VOID Gmm_ComNetModeChange(VOS_VOID *);
extern VOS_VOID Gmm_ComNetModeChangeGsm(VOS_VOID  *);
extern VOS_VOID NAS_MML_SecContext3GTO2G(VOS_UINT8 *pucIk, VOS_UINT8 *pucCk, VOS_UINT8 *pucKc);
extern VOS_VOID NAS_MML_SecContext2GTO3G(VOS_UINT8 *pucIk, VOS_UINT8 *pucCk, VOS_UINT8 *pucKc);


extern NAS_MSG_STRU *Gmm_GmmStatusMsgMake(VOS_UINT8);


extern VOS_VOID  Gmm_RcvTcTestReq(VOS_VOID *);
extern VOS_VOID  Gmm_RcvTcDataReq(VOS_VOID *);



VOS_VOID Gmm_RcvLLCInform( VOS_VOID *pMsg );

extern  VOS_VOID    NAS_GMM_RcvInterRatHandoverInfoCnf(VOS_VOID *);


/* GmmRau.c�к��������� */
extern VOS_VOID  Gmm_RoutingAreaUpdateRejectCause13(VOS_BOOL bUpdateSimFlg);
extern VOS_VOID Gmm_RoutingAreaUpdateRejectCause11(
    VOS_UINT32                          ulGmmCause,                   /* ʧ��ԭ��ֵ                               */
    VOS_BOOL                            bUpdateSimFlg
);
extern VOS_VOID  Gmm_RoutingAreaUpdateRejectCause9(
    VOS_UINT32                              ulGmmCause,
    VOS_UINT8                              *pucAttachFlg
);
extern VOS_VOID  Gmm_RoutingAreaUpdateRejectCause3(VOS_UINT32);

extern VOS_VOID NAS_GMM_SndStkRauRej(VOS_UINT8 ucCause);

extern NAS_STK_UPDATE_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmRauTypeToStkRauType (
                                         NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8 enGmmRauType
                                         );
/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
extern TAF_MMA_RAT_TYPE_ENUM_UINT8 NAS_GMM_ConvertGmmRatTypeToStkRatType (
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
                                         NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enGmmRatType
                                         );

extern VOS_VOID  Gmm_RcvRoutingAreaUpdateRejectMsg(NAS_MSG_FOR_PCLINT_STRU *);

VOS_UINT8 Gmm_Com_CmpRai(
    GMM_RAI_STRU                       *pstNewRai,
    GMM_RAI_STRU                       *pstOldRai,
    VOS_UINT8                           ucNetMod
);


extern VOS_VOID  Gmm_RoutingAreaUpdateAttemptCounter(VOS_UINT32);
extern VOS_VOID  Gmm_RoutingAreaUpdataAcceptRaOnly(GMM_MSG_RESOLVE_STRU *,
                                               NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RoutingAreaUpdataAcceptCombined(GMM_MSG_RESOLVE_STRU *,
                                                 NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RoutingAreaUpdateResolveIe(GMM_MSG_RESOLVE_STRU *,
                                            NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RoutingAreaUpdateHandle(GMM_MSG_RESOLVE_STRU  *,
                                         NAS_MSG_FOR_PCLINT_STRU *,
                                         VOS_BOOL         bTlliUpdateFlag);
extern VOS_VOID  Gmm_RoutingAreaUpdateHandleFollowOn(VOS_VOID);
/*extern VOS_VOID  Gmm_RcvRoutingAreaUpdateAcceptMsg(NAS_MSG_STRU *, VOS_UINT32);*/

extern VOS_VOID  Gmm_RcvRoutingAreaUpdateAcceptMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  NAS_GMM_SndRoutingAreaUpdateReq(VOS_UINT8 ucUpdataType);
extern VOS_VOID  Gmm_SndRoutingAreaUpdateReq(VOS_UINT8);
extern VOS_VOID  Gmm_PeriodRoutingAreaUpdateType(VOS_VOID);
extern VOS_VOID  Gmm_RoutingAreaUpdateInitiate(VOS_UINT8);
extern VOS_VOID  Gmm_FillPdpContext(VOS_UINT8 *);
extern NAS_MSG_STRU* Gmm_RoutingAreaUpdateRequestMsgMake(VOS_UINT8);

extern VOS_UINT16 NAS_GMM_GetRauComPleteMsgLen();
extern VOS_UINT16 NAS_GMM_GetAttachComPleteMsgLen();
extern VOS_VOID NAS_GMM_RoutingAreaUpdateHandle_Handling_REQUESTED_MS_INFORMATION_IE(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pRauAcceptIe,
    VOS_UINT8                          *pucSndCompleteFlg,
    VOS_UINT8                          *pucInterRatInfoFlg

);


extern NAS_MSG_STRU* Gmm_RoutingAreaUpdateCompleteMsgMake(VOS_VOID);
extern VOS_UINT8 Gmm_RauAccept_Mandatory_Ie_Check(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    *pNeedReturn);

extern VOS_UINT8 Gmm_IeCheck_Npdu_Numbers(NAS_MSG_FOR_PCLINT_STRU *pMsg,
                                                  VOS_UINT8    ucIeOffset,
                                                  VOS_UINT8    *pNeedReturn);
extern VOS_UINT8 Gmm_IECheck_RauAccept(NAS_MSG_FOR_PCLINT_STRU *);

/* BEGIN: Added by liuyang id:48197, 2006/3/22   PN:A32D01882*/
VOS_VOID Gmm_RoutingAreaUpdateInitiateWithReEstRR(VOS_VOID);
VOS_VOID Gmm_SndRoutingAreaUpdateReqWithReEstRR(VOS_UINT8 ucUpdataType);
/* END:   Added by liuyang id:48197, 2006/3/22 */

VOS_VOID GMM_RauFailureInterSys(VOS_VOID);
VOS_VOID GMM_RauSuccessInterSys(VOS_VOID);

/* GmmSend.c�к��������� */
extern VOS_VOID  Gmm_SndMmcNetworkDetachInd(VOS_UINT8, VOS_UINT8);

extern VOS_VOID  NAS_GMM_SndMmcDetachCnf(VOS_VOID);


extern VOS_VOID  Gmm_SndMmcPowerOffCnf(VOS_VOID);

extern VOS_VOID  Gmm_SndMmcInfoInd(NAS_MM_INFO_IND_STRU *pstMmInfo);

extern VOS_VOID  Gmm_SndMmcPdpStatusInd(VOS_UINT8);
extern VOS_VOID Gmm_SndMmcTBFRelInd(VOS_VOID);
extern VOS_VOID  Gmm_SndMmcStartCnf(VOS_VOID);
extern VOS_VOID  Gmm_SndMmcLocalDetachInd(VOS_UINT32);

extern VOS_VOID  Gmm_SndRrmmEstReq(VOS_UINT32, VOS_UINT32, NAS_MSG_STRU *);
extern VOS_UINT8 Gmm_Com_CmpPlmnid(GMM_PLMN_ID_STRU *);
extern VOS_VOID  Gmm_SndRrmmDataReq(VOS_UINT8, NAS_MSG_STRU *);
extern VOS_VOID  Gmm_SndRrmmRelReq(RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg);
/*extern VOS_VOID  Gmm_SndRrmmAbortReq(VOS_UINT32);*/
extern VOS_VOID  Gmm_SndRrmmNasInfoChangeReq(VOS_UINT32);


extern   VOS_VOID  NAS_GMM_SndRrmmRelCsPsAllConnReq(VOS_VOID);

extern VOS_VOID  NAS_GMM_SyncNasInfoChange_RegisteredStatus(VOS_UINT32 ulMask);

extern VOS_VOID  Gmm_SndSmEstablishCnf(VOS_UINT32, GMM_SM_CAUSE_ENUM_UINT16);

extern VOS_VOID  Gmm_SndSmStatusInd(VOS_VOID);
extern VOS_VOID  NAS_GMM_SndSmStatusInd(VOS_UINT32, GMM_SM_CAUSE_ENUM_UINT16);
extern VOS_VOID  Gmm_SndSmDataInd(NAS_MSG_FOR_PCLINT_STRU *);

extern VOS_VOID GMM_SndSmServiceRej(GMM_SM_CAUSE_ENUM_UINT16);
extern VOS_VOID Gmm_SndSmPdpStatusInd(VOS_UINT32 ulPDPStaus, GMM_SM_CAUSE_ENUM_UINT16 enCause);
extern VOS_VOID Gmm_SndSmSysInfoInd(VOS_UINT8 ucSgsnRelease);
extern VOS_VOID Gmm_SndSmRelInd(VOS_VOID);

extern VOS_VOID  Gmm_SndRabmReestablishCnf(VOS_UINT8);
extern VOS_VOID  Gmm_SndMmcCombinedAttachInitiation(VOS_VOID);
extern VOS_VOID  Gmm_SndMmcCombinedAttachAccept(VOS_UINT32, VOS_UINT32, NAS_MSG_FOR_PCLINT_STRU *,
                                            GMM_MSG_RESOLVE_STRU *);
extern VOS_VOID  Gmm_SndMmcCombinedAttachRejected(VOS_UINT32);
extern VOS_UINT8 Gmm_Com_DealOfPlmnList(VOS_VOID *, MMCGMM_PLMN_ID_STRU *);
extern VOS_VOID  Gmm_Com_DealOfMsId(VOS_VOID *, MMC_GMM_MS_IDENTITY_STRU *);

extern VOS_VOID  Gmm_SndAgentUsimUpdateFileReq(VOS_UINT16);
extern VOS_VOID  Gmm_SndAgentUsimAuthenticationReq(VOS_UINT32, VOS_VOID *);
extern VOS_VOID Gmm_SndMmcSignalingStatusInd(VOS_UINT32);
extern VOS_VOID Gmm_SndSmsRegStateInd(VOS_VOID);
extern VOS_VOID Gmm_SndSmsEstCnf(VOS_VOID);
extern VOS_VOID Gmm_SndSmsUnitdataInd(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID Gmm_SndSmsErrorInd(VOS_UINT8);
extern VOS_VOID Gmm_SndSmsServiceStatusInd(VOS_VOID);
extern VOS_VOID Gmm_SndTcDataInd(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_SndRrmmDataReqForCm(VOS_UINT8, NAS_MSG_STRU *);
extern VOS_UINT32 NAS_GMM_SndRrmmInterRatHandoverInfoReq(VOS_VOID);
extern VOS_VOID NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);
extern VOS_VOID NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(
        VOS_UINT32                          ulForbiddenMask);
/* GmmService.c�к��������� */

extern VOS_VOID  Gmm_RcvRabmReestablishReq(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRabRelInd(VOS_VOID);
extern VOS_VOID  Gmm_RcvRrmmSecurityInd(VOS_VOID *);
extern VOS_VOID  Gmm_RcvRrmmSecurityInd_RegInit(RRMM_SECURITY_IND_STRU *);
extern VOS_VOID  Gmm_RcvRrmmSecurityInd_ServReqInit(RRMM_SECURITY_IND_STRU *);
extern VOS_VOID Gmm_RcvRrmmSecurityInd_SuspendWaitSysinfo(
    RRMM_SECURITY_IND_STRU              *pStSecurityInd
);

VOS_VOID NAS_GMM_RcvRabmRabSetupInd(
    GMMRABM_RAB_SETUP_IND_STRU         *pstRabSetupIndMsg
);
extern VOS_VOID  Gmm_RcvServiceAcceptMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_RcvServiceRejectMsg(NAS_MSG_FOR_PCLINT_STRU *);
extern VOS_VOID  Gmm_ServiceReqRejectCasue3(VOS_UINT8);
extern VOS_VOID  Gmm_ServiceReqRejectCasue7(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectCasue9(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectCasue10(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectCasue11(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectCasue12(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectCasue13(VOS_UINT8);
extern VOS_VOID  Gmm_ServiceReqRejectCasue40(VOS_VOID);
extern VOS_VOID  Gmm_ServiceReqRejectTheOtherCause(VOS_UINT8);
extern NAS_MSG_STRU *Gmm_ServiceRequestMsgMake(VOS_VOID);
extern NAS_MSG_STRU *Gmm_ServiceRequestMsgMake_ForData(VOS_UINT16 usUplinkDataStatus, VOS_UINT16 usPdpContextStatus);


/* GmmTimer.c�к��������� */
extern VOS_VOID  Gmm_Tim3312Expired_RegNmlServ(VOS_VOID);
extern VOS_VOID  Gmm_Tim3312Expired_RegNoCell(VOS_VOID);
extern VOS_VOID  Gmm_Tim3321Expired_DeregInit(VOS_VOID);
extern VOS_VOID  Gmm_Tim3321Expired_RegImsiDtchInit(VOS_VOID);
extern VOS_VOID  Gmm_TimerCreat(VOS_VOID);
extern VOS_VOID  Gmm_TimerDistroy(VOS_VOID);
extern VOS_VOID  Gmm_TimerStart(VOS_UINT8);
extern VOS_VOID  Gmm_TimerStop(VOS_UINT8);
extern VOS_VOID  Gmm_TimerPause(VOS_UINT8);
extern VOS_VOID  Gmm_TimerResume(VOS_UINT8);

extern VOS_VOID NAS_GMM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
);

extern VOS_VOID NAS_Gmm_RcvMmT3211ExpiredNotify(
    VOS_VOID                           *pstMsg
);

extern NAS_MML_RAI_STRU *NAS_GMM_GetAttemptUpdateRaiInfo(VOS_VOID);
extern VOS_VOID NAS_GMM_InitRaiInfo(
    NAS_MML_RAI_STRU                   *pstRai
);
extern VOS_UINT32 NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(
     GMM_RAI_STRU                       *pstSysinfoRai,
     GMM_RAI_STRU                       *pstAttemptUpdateRai
);
 VOS_VOID NAS_GMM_SetAttemptUpdateRaiInfo(
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo
 );



extern VOS_UINT32  NAS_GMM_QryTimerStatus(VOS_UINT8);

extern VOS_VOID  Gmm_Tim3302Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3310Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3311Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3312Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3316Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3317Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3318Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3319Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3320Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim3321Expired(VOS_VOID);

extern VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID);
extern VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(
    VOS_VOID                           *pstMsg
);

extern VOS_VOID  Gmm_Tim3330Expired(VOS_VOID);
extern VOS_VOID  Gmm_Tim5sExpired(VOS_VOID);
VOS_VOID NAS_GMM_TimerDetachForPowerOffExpired(VOS_VOID);
extern VOS_VOID  Gmm_TimProtectExpired(VOS_VOID);
extern VOS_VOID  Gmm_RcvTimerExpired(VOS_UINT8);
extern VOS_VOID  Gmm_TimerOutSet(VOS_VOID);
extern VOS_VOID  NAS_GMM_Timer3340Expired(VOS_VOID);
extern VOS_VOID NAS_GMM_TimerWaitInterRatCnfExpired( VOS_VOID );


VOS_VOID  NAS_GMM_TimerWaitReselSecuCnfExpired( VOS_VOID );


extern VOS_VOID NAS_GMM_RcvSmsBeginSessionNotify_PreProc(
    GMMSMS_BEGIN_SESSION_NOTIFY_STRU   *pstBeginSessionMsg
);
extern VOS_VOID NAS_GMM_RcvSmsEndSessionNotify_PreProc(
    GMMSMS_END_SESSION_NOTIFY_STRU     *pstEndSessionMsg
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_GMM_TimerWaitHoSecuCnfExpired( VOS_VOID );

VOS_VOID NAS_GMM_Timer3323Expired(VOS_VOID);

extern VOS_VOID NAS_GMM_SndLmmTimerInfoNotify(
   VOS_UINT8                            ucTimerId,
   GMM_LMM_TIMER_STATE_ENUM_UINT32      enTimerInfo
);


extern VOS_VOID NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired(VOS_VOID);


#if(FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID NAS_GMM_SndLmmBeginSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
);

extern VOS_VOID NAS_GMM_SndLmmEndSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
);
#endif
#endif
VOS_VOID NAS_GMM_SndMmcNetworkCapabilityInfoInd(
    GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8    enNwEmcBS,
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoPS,
    GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8 enLteCsCap
);




extern VOS_VOID NAS_GMM_TimerWaitConnectRelExpired(VOS_VOID);

extern VOS_VOID NAS_GMM_TimerTcDelaySuspendRspExpired(VOS_VOID);


extern VOS_VOID NAS_GMM_TimerDelayRadioCapaTrigedRauExpired(VOS_VOID);


extern VOS_VOID GMM_SuspendTimer(VOS_VOID);
extern VOS_VOID GMM_SuspendSingleTimer(VOS_UINT8);
extern VOS_VOID GMM_ResumeTimer(VOS_UINT8);
extern VOS_VOID GMM_TimSuspendedExpired(VOS_VOID);

extern VOS_VOID  Gmm_TimerPauseForTc(VOS_UINT8);
extern VOS_VOID  Gmm_TimerResumeForTc(VOS_UINT8);
extern VOS_VOID Gmm_TimProtectForSignalingExpired(VOS_VOID);

extern VOS_VOID GMM_TimProtectForRrRel(VOS_VOID);

extern VOS_VOID GMM_TimProtectForOldTlli(VOS_VOID);
#if 0

extern VOS_UINT32 MMC_InvokeMsg(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgNetworkDetechInd(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgActionResultInd(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgCombRauAccept(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgCombRauRej(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgCombAttAccept(VOS_VOID *pMsg);

extern VOS_UINT32 MM_InvokeMsgCombAttRej(VOS_VOID *pMsg);
#endif

extern VOS_VOID GMM_PowerOffHandle(VOS_VOID);

extern VOS_VOID Gmm_BufSmDataReqMsg(VOS_VOID *pMsg);
extern VOS_VOID Gmm_ComCnfHandle(VOS_VOID);

extern VOS_UINT32 RABM_IsExistBufferUplinkData(VOS_VOID);
extern VOS_VOID  Gmm_Com_ServiceStatus_Handle(VOS_VOID);

extern VOS_VOID Gmm_SndCcEmergencyNumberList(NAS_MML_EMERGENCY_NUM_LIST_STRU *pEmergencyList);

extern VOS_VOID Gmm_SndMmcGprsServiceInd(
    NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32               enGprsServiceType
);


extern  VOS_VOID NAS_GMM_UpdateAttemptCounterForSpecialCause(
    VOS_UINT8                           ucUpdateAttachCounter,
    VOS_UINT32                          ulGmmCause
);

extern  VOS_VOID NAS_GMM_HandleDelayedEvent(VOS_VOID);

extern  VOS_UINT8 NAS_GMM_RetryAttachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
);

extern  VOS_UINT8 NAS_GMM_RetryDetachProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
);

extern  VOS_UINT8 NAS_GMM_RetryRauProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
);

extern  VOS_UINT8 NAS_GMM_RetrySrProcedureCheck(
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause,
    RRC_RRC_CONN_STATUS_ENUM_UINT32     ulRrcConnStatus
);

extern  VOS_VOID NAS_GMM_UpdateGmmLinkCtrlStru(VOS_VOID);

extern  VOS_VOID NAS_GMM_ClearGmmLinkCtrlStru( VOS_VOID );

extern  VOS_UINT8 NAS_GMM_GetDetachTypeFromProcName(
    NAS_GMM_SPEC_PROC_TYPE_ENUM_UINT8   ucSpecProc
);

extern  VOS_INT32 NAS_GMM_AsEstReq(
    VOS_UINT32                          ulOpId,
    VOS_UINT8                           ucCnDomain,
    VOS_UINT32                          ulEstCause,
    IDNNS_STRU                          *pIdnnsInfo,
    RRC_PLMN_ID_STRU                    *pstPlmnId,
    VOS_UINT32                          ulSize,
    VOS_INT8                            *pFisrstMsg
);

extern  VOS_VOID NAS_GMM_SndStatusMsg(
    VOS_UINT8                           ucCause
);

extern  VOS_VOID NAS_GMM_ClearBufferedSmDataReq( VOS_VOID );

extern  VOS_UINT32 NAS_GMM_CheckGmmInfoMsg(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg
);

extern  VOS_UINT32 NAS_GMM_DecodeFullNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
);

extern  VOS_UINT32  NAS_GMM_DecodeShortNameforNetworkIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset
);

extern  VOS_UINT32  NAS_GMM_DecodeLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
);

extern  VOS_UINT32  NAS_GMM_DecodeUniversalTimeAndLocalTimeZoneIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
);

extern  VOS_UINT32  NAS_GMM_DecodeLSAIdentityIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
);

extern  VOS_UINT32  NAS_GMM_DecodeDaylightSavingTimeIE(
    NAS_MSG_FOR_PCLINT_STRU             *pMsg,
    VOS_UINT32                          *pulIeOffset,
    NAS_MM_INFO_IND_STRU                *pstMmInfo
);

extern  VOS_VOID  NAS_GMM_CheckIfNeedToStartTimerT3340(VOS_VOID);

VOS_UINT32 NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer(VOS_VOID);

extern  VOS_VOID NAS_GMM_TransferSmEstCause2RrcEstCause(
    VOS_UINT32                          ulSmEstCause,
    VOS_UINT32                          *pulRrcEstCause
);

extern VOS_VOID NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_ENUM_UINT16);

extern VOS_VOID NAS_GMM_FreeTlliForPowerOff(VOS_VOID);

extern VOS_UINT32 NAS_Gmm_IsInServiceProcedure(VOS_VOID);

extern VOS_BOOL NAS_GMM_IsFollowOnPend(VOS_VOID);
extern VOS_VOID NAS_GMM_HandleModeANOIWhenRAInotChange(VOS_VOID);
extern VOS_VOID NAS_GMM_HandleModeANOIWhenDeregister(VOS_VOID);

extern VOS_UINT32 NAS_GMM_IsInRegOrDeregProcedure(VOS_VOID);

extern VOS_BOOL  NAS_MMC_IsEnableRabmReset( VOS_VOID);

extern VOS_UINT8  MM_GetSignalingStatus(VOS_VOID);

extern VOS_VOID Gmm_RcvAttachRejectMsg_Cause_Handling(VOS_UINT8 ucCause);



extern VOS_VOID  NAS_GMM_SndTinTypeToMmc(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
);

#if (FEATURE_LTE == FEATURE_ON )
VOS_VOID NAS_GMM_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
);
#endif




VOS_VOID NAS_GMM_FillNasGmmState(
    NAS_OM_MM_IND_STRU                 *pstMsg
);

VOS_VOID NAS_GMM_FillNasGmmGprsState(
    NAS_OM_MM_IND_STRU                 *pstMsg
);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_GMM_RcvMmcLteSysInfoInd(
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
);

extern VOS_VOID NAS_GMM_RcvMmcLmmStatusInd(
    MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
);

extern VOS_UINT32 NAS_GMM_IsCsLaiChangeNeedRegister(
    VOS_UINT8                           ucNetMod);

#endif
VOS_UINT32 NAS_GMM_RcvMmcAttachReq_PreProc(MMCGMM_ATTACH_REQ_STRU *pstmsg);
VOS_UINT32 NAS_GMM_RcvMmcDetachReq_PreProc(MMCGMM_DETACH_REQ_STRU *pstmsg);
VOS_VOID NAS_GMM_SndMmcDetachCnf(VOS_VOID);
VOS_VOID NAS_GMM_SndMmcAttachCnf(VOS_VOID);
VOS_VOID NAS_GMM_SndMmcMmDetachInfo(VOS_VOID);

VOS_VOID NAS_GMM_SndMmLuInitiation(
    VOS_UINT32                          ulT3312TimeoutFlg
);
VOS_VOID NAS_GMM_SndMmCombinedAttachInitiation(VOS_VOID);

VOS_VOID NAS_GMM_SndMmCombinedAttachAccept(
    VOS_UINT32                          ulAttachResult,                         /* ע����                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,                                /* ʧ��ԭ��ֵ                               */
    NAS_MSG_FOR_PCLINT_STRU            *pNasMsg,                                /* NAS��Ϣ�׵�ַ                            */
    GMM_MSG_RESOLVE_STRU               *pAttachAcceptIe    /* IE�Ƿ���ڵ���Ϣ                         */
);

VOS_VOID NAS_GMM_SndMmCombinedAttachRejected(
    VOS_UINT32                          ulCause                                          /* ʧ��ԭ��ֵ                               */
);

VOS_VOID NAS_GMM_SndMmImsiDetachInitiation(VOS_VOID);
VOS_VOID NAS_GMM_SndMmImsiDetachComplete(VOS_VOID);
VOS_VOID NAS_GMM_SndMmGprsDetachInitiation(VOS_VOID);
VOS_VOID NAS_GMM_SndMmGprsDetachComplete(VOS_VOID);
VOS_VOID NAS_GMM_SndMmNetworkDetachInd(
    VOS_UINT8                           ucDetachType,                           /* detach����                               */
    VOS_UINT8                           ucDetachCause                           /* detachԭ��                               */
);
VOS_VOID NAS_GMM_SndMmGmmActionResultInd(
    VOS_UINT32                          ulActionResult,                     /* �������                                 */
    VOS_UINT32                          ulCause                            /* ����ʧ��ԭ��                             */
);
VOS_VOID NAS_GMM_SndMmCombinedRauInitiation(VOS_VOID);
VOS_VOID NAS_GMM_SndMmCombinedRauAccept(
    VOS_UINT32                          ulRauResult,                            /* ���½��                                 */
    VOS_UINT32                          ulCause,                                /* ����ʧ��ԭ��                             */
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe                            /* IE�Ƿ���ڵ���Ϣ                         */
);
VOS_VOID NAS_GMM_SndMmCombinedRauRejected(
    VOS_UINT32                          ulCause
);
VOS_VOID NAS_GMM_SndMmAuthenticationFailureInd(VOS_VOID);
VOS_VOID NAS_GMM_SndMmcPsRegResultInd(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);
VOS_VOID NAS_GMM_SndMmcServiceRequestResultInd(
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);

VOS_VOID Gmm_MsgDistribute_From_MM(
    VOS_VOID                           *pstRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
);
VOS_VOID NAS_GMM_ProcMmLuResult(
    VOS_VOID                           *pstRcvMsg
);
VOS_VOID NAS_GMM_RcvMmCsConnectInd(
    VOS_VOID                           *pstRcvMsg                               /* ������Ϣʹ�õ�ͷ��ַ����                 */
);
VOS_VOID NAS_GMM_RcvMmCmServiceRejectInd(
    VOS_VOID                           *pstMsg
);
VOS_VOID Gmm_RcvMmRegisterInitiation(
    VOS_VOID                           *pstMsg                                  /* ָ����Ϣ��ָ��                           */
);
VOS_VOID NAS_GMM_RcvMmAuthenticationFailureInd(VOS_VOID);
VOS_VOID NAS_GMM_RcvMmCsConnectInd_InProc(
    VOS_VOID                           *pstMsg                               /* ԭ��ָ��                                 */
);
VOS_VOID NAS_GMM_RcvMmCsConnectInd_RegNmlServ(VOS_VOID);


VOS_VOID  NAS_GMM_ConvertPlmnIdToMmcFormat(
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId
);
VOS_VOID  NAS_GMM_ConvertPlmnIdToGmmFormat(
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId,
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId
);


#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID NAS_GMM_ProcMtcRrcAreaLostInd(VOS_VOID  *pstRcvMsg);
VOS_VOID NAS_GMM_ProcMtcMsg(VOS_VOID  *pstRcvMsg);

#endif


VOS_UINT32 NAS_GMM_IsDeregisterState(
    GMM_STATE_TYPE_UINT8                ucState
);

extern VOS_UINT32 NAS_GMM_CheckSigConnStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
);

VOS_VOID NAS_GMM_ProcBufferSmMsg_ResumeSuccess(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_GMM_ProcResumeToLTE(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_VOID NAS_GMM_ProcResumeToHRPD(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
);
#endif

VOS_UINT32 NAS_GMM_BackToOrgPlmnAfterCoverageLost(
    VOS_VOID                           *pMsg
);

extern VOS_VOID Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(GMM_RAI_STRU         *pRaiTemp,
                                            VOS_VOID             *pRcvMsg
                                            );

extern VOS_VOID NAS_GMM_SndTcHandoverInd(VOS_VOID);
extern VOS_VOID NAS_GMM_SndTcRrRelInd(VOS_VOID);
VOS_VOID NAS_GMM_DecodeEquPlmnInfoIE(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

VOS_VOID NAS_GMM_DeleteEPlmnList(VOS_VOID);

VOS_VOID NAS_GMM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
);
VOS_UINT32 NAS_GMM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);
VOS_VOID NAS_GMM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
);

VOS_VOID NAS_GMM_NotifyMmUnrealCombinedRauResult(VOS_VOID);

VOS_VOID NAS_GMM_AttachAcceptHandle_UpdateEPlmn(
    GMM_MSG_RESOLVE_STRU               *pstAcceptIe,
    NAS_MSG_FOR_PCLINT_STRU            *pstMsg
);

extern VOS_VOID NAS_GMM_RcvRabmMmlProcStatusQryReq(
    struct MsgCB                       *pMsg
);

extern VOS_UINT32  NAS_GMM_IsInRegisterProcedure(VOS_VOID);
extern VOS_VOID NAS_GMM_SndRabmMmlProcStatusQryCnf(
    RABM_GMM_MML_PROC_STATUS_STRU     *pstMmlProcStatus
);


extern VOS_VOID NAS_GMM_StopReadyTimer_DeregStat(VOS_VOID);
extern VOS_VOID NAS_GMM_SetIdleSrvState_DeregStat(VOS_VOID);



extern VOS_UINT32  NAS_GMM_IsAttachOtherCause(VOS_UINT16 ulGmmCause );

RRC_NAS_ATTACH_STATUS_ENUM_UINT32  NAS_GMM_GetAttachStatus(VOS_VOID);

VOS_VOID  NAS_GMM_GetPTmsiRAI(
    NAS_INFO_PTMSI_RAI_STRU            *pstPtmsiRai
);

#if   (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_GMM_WriteTinInfoNvim(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
    VOS_UINT8                          *pucImsi
);

VOS_UINT8  NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting(
    VOS_UINT8                          *pucAddr
);

#endif
VOS_VOID NAS_GMM_SaveDetachMsg(VOS_VOID *pMsg);

VOS_UINT32 NAS_GMM_DeleteSavedDetachMsg(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     ulDelDetachType
);

VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmRegisteredInitiated(
    VOS_VOID                           *pMsg
);

VOS_VOID NAS_GMM_RcvMmcGmmDetachReqMsg_GmmServiceReqInitiated(
    VOS_VOID                           *pMsg
);
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach(VOS_VOID);

VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredInitiated(VOS_VOID);

VOS_VOID NAS_GMM_LocalDetach_GmmRauInitiated(VOS_VOID);
VOS_VOID NAS_GMM_LocalDetach_GprsSuspension(VOS_VOID);

VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNormalService(VOS_VOID);
VOS_VOID NAS_GMM_LocalDetach_GmmDeregisteredNoImsi(VOS_VOID);

VOS_VOID NAS_GMM_StartDetachProtectingTimer(
    MMCGMM_DETACH_REQ_STRU             *pstMsg
);

VOS_VOID NAS_GMM_GprsLocalDetach(VOS_VOID);

VOS_VOID NAS_GMM_GprsLocalDetachRelCsPsAllConn(VOS_VOID);


extern VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit(VOS_VOID);
extern VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RauInit(VOS_VOID);
extern VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd_RegInit(VOS_VOID);
extern NAS_GMM_DETACH_TYPE_ENUM_UINT32 NAS_GMM_ConvertDetachType(
    NAS_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType
);

extern VOS_VOID NAS_GMM_SndMmcCipherInfoInd(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 NAS_GMM_GetPTmsi_GUL(
    VOS_UINT8                           aucPtmsi[RRC_NAS_PTMSI_LEN]
);

VOS_UINT32 NAS_GMM_IsRegNeedFillVoiceDomainPreferenceAndUeUsageSettingIE(VOS_VOID);
VOS_UINT32 NAS_GMM_IsRegNeedFillOldLocationAreaIdentificationIE(VOS_VOID);
VOS_UINT8 NAS_GMM_FillOldLocationAreaIdentificationIE(
    VOS_UINT8                          *pucAddr
);
#endif

VOS_VOID NAS_GMM_DeleteRandAndResInfoInPmmIdleMode(VOS_VOID);
VOS_VOID NAS_GMM_SaveGprsTimer3Value(
    VOS_UINT8                            ucTimerName,
    VOS_UINT8                            ucMsgTimerValue
);
VOS_VOID NAS_GMM_StopT3311InIuPmmConnMode_T3312Exp(VOS_VOID);

VOS_UINT8 NAS_GMM_FillMsNetworkFeatureSupportIE(
    VOS_UINT8                          *pucAddr
);
VOS_UINT8 NAS_GMM_FillTmsiBasedNRIContainerIE(
    VOS_UINT8                          *pucAddr
);


VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiStatusIE(VOS_VOID);
NAS_MML_PLMN_WITH_RAT_STRU *NAS_GMM_GetAllocT3302ValuePlmnWithRat(VOS_VOID);
VOS_VOID NAS_GMM_SetAllocT3302ValuePlmnWithRat(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnWithRat
);
VOS_UINT32 NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax(VOS_VOID);
VOS_UINT32 NAS_GMM_IsRegNeedFillTmsiBasedNRIContainerIE(VOS_VOID);


VOS_VOID Gmm_FreeBufferMsgWithoutSm(VOS_VOID);

VOS_UINT8  NAS_GMM_Fill_IE_VoiceDomainPreferenceAndUeUsageSetting(
    VOS_UINT8                          *pucAddr
);




extern VOS_VOID NAS_GMM_RcvLmmTimerStateNotify(
    struct MsgCB                       *pstMsg
);

extern VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ(VOS_VOID);

extern VOS_VOID NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ(VOS_VOID);

VOS_VOID NAS_GMM_RcvMmcEmergencyNumList(
    struct MsgCB                       *pRcvMsg
);

extern VOS_UINT32 NAS_GMM_IsT3412ExpiredNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3412Status
);

extern VOS_UINT32 NAS_GMM_IsT3423StatusChangeNeedRegist(
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8                   enLteCsServiceCfg,
    NAS_MML_TIN_TYPE_ENUM_UINT8                             enTinType,
    NAS_MML_TIMER_INFO_ENUM_UINT8                           enT3423Status
);


extern VOS_UINT32 NAS_GMM_IsNeedDeactiveIsr_InterSys(
        VOS_UINT8                           ucPreRat,
        NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType,
        MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause
    );

extern VOS_VOID NAS_GMM_LogTinTypeInfo(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
);

extern VOS_VOID NAS_GMM_UpdateTinType_RauAccept(
        NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType,
        VOS_UINT8                          *pucImsi,
        VOS_UINT8                           ucUpdateResultValue);

extern VOS_UINT32 NAS_GMM_IsAbleCombinedRau_TimerStatusChg(VOS_VOID);

extern VOS_VOID NAS_GMM_IsrActiveRaiNoChg_InterSys(VOS_VOID);

extern VOS_VOID    NAS_GMM_ConverRrcGmmProcFlagToMml(
    RRMM_GMM_PROC_FLAG_ENUM_UINT16      enRrmmGmmProcFlag,
    NAS_MML_GMM_PROC_FLAG_ENUM_UINT16  *penMmlGmmProcFlag
);

extern VOS_VOID    NAS_GMM_ConverRrcGmmProcTypeToMml(
    RRMM_GMM_PROC_TYPE_ENUM_UINT16      enRrmmGmmProcType,
    NAS_MML_GMM_PROC_TYPE_ENUM_UINT16  *penMmlGmmProcType
);


extern VOS_VOID NAS_GMM_ConvertPdpCtxStatusToNetworkPdpCtxStatus(
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearerCtx,
    VOS_UINT32                         *pulPdpCtxStatus
);
VOS_VOID    NAS_GMM_GetOldRai(
    GMM_RAI_STRU                       *pstGmmRai
);

VOS_VOID NAS_GMM_ProcSmDataReq_RAUInit(
    VOS_VOID                *pSmDataReqMsg
);

extern VOS_VOID NAS_GMM_SndSmSigConnInd(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_Gmm_IsPtmsiMappedFromGuti(VOS_VOID);
#endif

extern VOS_VOID NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_ENUM_UINT16 enCause);

extern GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_GetAttach2DetachErrCode(VOS_VOID);

extern GMM_SM_CAUSE_ENUM_UINT16 NAS_GMM_TransGmmNwCause2GmmSmCause(
    VOS_UINT8  enGmmCause
);



extern VOS_VOID NAS_GMM_LogPsRegContainDrxInfo(
    NAS_MML_PS_REG_CONTAIN_DRX_PARA_ENUM_UINT8    enPsRegContainDrx
);

extern VOS_UINT32 NAS_GMM_IsAModeAndNetworkI(VOS_VOID);
extern VOS_UINT32 NAS_GMM_IsCombinedSpecProc(VOS_VOID);
extern VOS_UINT32 NAS_GMM_IsNeedEnableLte_AttachPs(VOS_VOID);


extern VOS_UINT8 NAS_GMM_GetAttachType(VOS_VOID);


VOS_VOID NAS_GMM_RcvMmCsConnectInd_RrcConnExist(VOS_VOID);
extern  VOS_UINT32 NAS_GMM_IsNeedStartT3323(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_UINT32  NAS_GMM_GetLteInfo(
    NAS_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    NAS_LMM_INFO_STRU                  *pstLmmInfo
);

extern VOS_VOID  NAS_GMM_HandleMsRadioCapLteSupportChanged(VOS_VOID);

#endif

VOS_VOID NAS_GMM_SaveWasSysInfo(
    MMCGMM_SYS_INFO_IND_STRU         *pstSysInfo
);
VOS_UINT32 NAS_GMM_ProcSavedWasSysInfo(VOS_VOID);
VOS_VOID NAS_GMM_FreeWasSysInfo(VOS_VOID);

VOS_VOID Gmm_RcvMmcGmmAttachReq_DeregInit(MMCGMM_ATTACH_REQ_STRU *pstmsg);

VOS_UINT8 Gmm_MsgDistribute_ProcMmcMsg_GmmNull(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
);
VOS_UINT8 NAS_Gmm_IsValidMmcMsg_GmmTcActive(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
);

VOS_UINT32 NAS_GMM_IsNeedProcUserCsDetach(VOS_VOID);

VOS_UINT32 NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm(VOS_VOID);
VOS_UINT8 NAS_GMM_GetRoutingAreaUpdateType(VOS_VOID);


#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_GMM_SndAcpuOmChangePtmsi(VOS_VOID);
#endif
VOS_UINT32 NAS_GMM_CheckNpduValid(
    VOS_UINT8                           ucNpduLen,
    VOS_UINT8                          *pucNpdu
);

VOS_VOID NAS_GMM_RcvRabmEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
);
VOS_VOID NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
);
VOS_VOID NAS_GMM_RcvSmsEstReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
);

extern VOS_UINT32  CDS_IsPsDataAvail(VOS_VOID);
NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16 NAS_GMM_ConvertUsimAuthFailInfo(
    USIMM_AUTH_RESULT_ENUM_UINT32    enSimFailValue
);

VOS_VOID NAS_GMM_SndMmcSimAuthFailInfo(
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16   enSimAuthFailValue
);

VOS_VOID  NAS_GMM_LogAuthInfo(
    VOS_UINT8                           ucRcvOpId,
    VOS_UINT8                           ucExpectOpId
);

VOS_VOID NAS_Gmm_ClearPendingPdpStatus(VOS_VOID);

VOS_VOID  NAS_GMM_ClearAuthInfo(VOS_VOID);

VOS_VOID  NAS_GMM_SndWasInfoChangeReq(VOS_UINT32 ulMask);

#if(FEATURE_ON == FEATURE_DSDS)
extern VOS_VOID NAS_GMM_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
);

extern VOS_VOID NAS_GMM_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
);

extern VOS_VOID NAS_GMM_NotifySessionAccordingStateChg(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
);

extern VOS_VOID NAS_GMM_TimerDelaySndAttachEndSessionNotifyExpired(VOS_VOID);

extern VOS_VOID NAS_GMM_TimerDelaySndRauEndSessionNotifyExpired(VOS_VOID);
#endif

VOS_UINT32  NAS_GMM_IsNeedProcRelInd(
    RRMM_REL_IND_STRU       *pstRrRelInd
);

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID NAS_GMM_NwDetachIndRecord(
    VOS_UINT8                           ucDetachType,
    VOS_UINT8                           ucGmmCause,
    VOS_UINT8                           ucForceToStandby
);
#endif

extern VOS_UINT8 NAS_GMM_IsEnableRelPsSigCon(VOS_VOID);
extern VOS_UINT32 NAS_GMM_GetRelPsSigConCfg_T3340TimerLen(VOS_VOID);
VOS_VOID NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd(VOS_VOID);
VOS_VOID NAS_GMM_ProcPsSigConn_ResumeInd(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
);
VOS_VOID NAS_GMM_ProcResumeToGU(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
);
VOS_VOID NAS_GMM_RcvMmcResumeInd_CcoFallbak(VOS_VOID);
VOS_VOID NAS_GMM_RcvMmcResumeInd_Handover(
    MMCGMM_RESUME_IND_ST               *pstResumeIndMsg
);
VOS_VOID NAS_GMM_TimerHoWaitSysinfoExpired(VOS_VOID);
VOS_UINT32 NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucFollowOn
);

VOS_VOID  NAS_GMM_RcvMmcVoiceDomainChangeNotify(
    struct MsgCB                       *pRcvMsg
);
VOS_VOID NAS_GMM_TimerDelayVoiceDomainTrigRauExpired(VOS_VOID);
VOS_UINT32 NAS_GMM_IsUeInfoChangeTriggerRau(VOS_VOID);

VOS_VOID NAS_GMM_RcvTiDelayPsSmsConnRelExpired(VOS_VOID);
VOS_VOID NAS_GMM_GetTimerRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerRunMask,  
    VOS_UINT8                          *pucTimerBitIndex
);
VOS_VOID NAS_GMM_GetTimerSuspendMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusMask,  
    VOS_UINT8                          *pucTimerBitIndex 
);
VOS_VOID NAS_GMM_GetTimerSuspendTcMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusTcMask,  
    VOS_UINT8                          *pucTimerBitIndex 
);
VOS_VOID NAS_GMM_GetTimerValMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerValMask,  
    VOS_UINT8                          *pucTimerBitIndex
);
VOS_VOID NAS_GMM_GetTimerSuspendCtrlRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulSuspendCtrlRunMask,  
    VOS_UINT8                          *pucTimerBitIndex 
);


/* NAS_MMA_GetServiceDomainSet�ӿڵ�������MmcMmaItf.h��Ų������ʱ�����ڴˣ�����SYSCFG�ع��ĵ��������Ż� */
extern VOS_BOOL NAS_MMA_GetServiceDomainSet(VOS_VOID);
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin */
extern VOS_VOID NAS_Gmm_SaveAttachAcceptGmmCause(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pstAttachAcceptIe
);
extern VOS_VOID NAS_Gmm_SaveRauAcceptGmmCause(
    NAS_MSG_FOR_PCLINT_STRU            *pMsg,
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe
);
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, end */
VOS_VOID Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(
    RRC_NAS_EST_RESULT_ENUM_UINT32      ulRrcEstResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 *penMmlRegFailCause
);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif /* _GMMEXTERN_H_ */
