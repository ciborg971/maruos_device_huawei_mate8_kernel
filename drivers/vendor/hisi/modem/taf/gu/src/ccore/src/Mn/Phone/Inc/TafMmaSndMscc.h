
#ifndef _TAF_MMA_SND_MSCC_H_
#define _TAF_MMA_SND_MSCC_H_
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "MmaMsccInterface.h"
#include  "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


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

typedef struct
{
    VOS_UINT32                                  ulCsPsCause;
    NAS_MSCC_PIF_CDMA_CALL_CAUSE_ENUM_UINT8     enMsccCause;
}TAF_MMA_CS_PS_ERR_CODE_MAP_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* Modified by h00313353 for iteration 9, 2015-2-9, begin */
VOS_UINT32 TAF_MMA_SndMsccStartReq(
    TAF_MMA_RAT_ORDER_STRU                  *pstPlmnRatPrio,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus,
    VOS_UINT8                                ucIsCardRefresh
);
/* Modified by h00313353 for iteration 9, 2015-2-9, end */

VOS_UINT32 TAF_MMA_SndMsccSignalReportReq(
    VOS_UINT8                           ucActionType,
    VOS_UINT8                           ucRrcMsgType,
    VOS_UINT8                           ucSignThreshold,
    VOS_UINT8                           ucMinRptTimerInterval
);

VOS_VOID TAF_MMA_SndMsccModeChangeReq(
    NAS_MSCC_PIF_MS_MODE_ENUM_UINT32         enMsMode
);

VOS_UINT32 TAF_MMA_SndMsccAttachReq(
    VOS_UINT32                                              ulOpID,
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                         enAttachType,
    TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8                    enAttachReason
);

/* Modified by h00313353 for Iteration 13, 2015-4-13, begin */
VOS_UINT32 TAF_MMA_SndMsccDetachReq(
    VOS_UINT8                                  ucOpID,
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32            enDetachType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8            enDetachCause
);
/* Modified by h00313353 for Iteration 13, 2015-4-13, end */

VOS_UINT32 TAF_MMA_SndMsccPlmnListReq(VOS_VOID);
VOS_UINT32 TAF_MMA_SndMsccPlmnListAbortReq(VOS_VOID);
VOS_UINT32 TAF_MMA_SndMsccPlmnUserReselReq(NAS_MSCC_PIF_PLMN_SEL_MODE_ENUM_UINT32 enPlmnSelMode);

VOS_UINT32 TAF_MMA_SndMsccPlmnSpecialReq(
    MMA_MSCC_PLMN_ID_STRU               *pstPlmnId,
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8     enAccessMode
);

VOS_VOID TAF_MMA_SndMsccPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
);

/* Modified by l00301449 for Iteration 13, 2015-04-10, begin */
VOS_VOID  TAF_MMA_SndMsccSysCfgReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pSysCfgReq,
    VOS_UINT8                           ucOnlyRoamParaChanged,
    VOS_UINT8                           ucIsNeedAttachPs
);
/* Modified by l00301449 for Iteration 13, 2015-04-10, end */


VOS_VOID TAF_MMA_SndMsccNetScanMsgReq(
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanReq
);

VOS_VOID TAF_MMA_SndMsccAbortNetScanMsgReq(VOS_VOID);





VOS_VOID TAF_MMA_SndMsccSystemAcquireReq(VOS_VOID);

VOS_UINT32 TAF_MMA_SndMsccSpecPlmnSearchAbortReq(VOS_VOID);

VOS_VOID TAF_MMA_SndMsccOmMaintainInfoInd(
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
);

VOS_UINT32 TAF_MMA_SndMsccUpdateUplmnNtf( VOS_VOID );

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_UINT32 TAF_MMA_SndMsccOtherModemInfoNotify(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_SndMsccOtherModemDplmnNplmnInfoNotify(
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_SndMsccNcellInfoInd(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_SndMsccPsTransferNotify(
    struct MsgCB                       *pstMsg
);


#endif

VOS_VOID TAF_MMA_SndMsccEOPlmnSetReq(
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnSetPara
);


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
VOS_VOID TAF_MMA_SndMsccSrvAcqReq(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8    enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList
);
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, begin */
VOS_VOID TAF_MMA_SndMsccBeginSessionNotify(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8         enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU      *pstRatList
);
VOS_VOID TAF_MMA_SndMsccEndSessionNotify(
    NAS_MSCC_PIF_SRV_TYPE_ENUM_UINT8         enSrvType,
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU      *pstRatList
);
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-16, end */



VOS_UINT32 TAF_MMA_SndMsccAcqReq(
    TAF_MMA_ACQ_PARA_STRU              *pstMmaAcqPara
);

VOS_UINT32 TAF_MMA_SndMsccRegReq(
    TAF_MMA_REG_PARA_STRU              *pstMmaRegPara
);

VOS_UINT32 TAF_MMA_SndMsccPowerSaveReq(
    TAF_MMA_POWER_SAVE_PARA_STRU       *pstMmaPowerSavePara
);

VOS_VOID TAF_MMA_SndMsccImsSrvInfoNotify(
    VOS_UINT8                           ucImsCallFlg
);

VOS_VOID TAF_MMA_SndMsccCdmaMoCallStartNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);

/* Added by h00313353 for Iteration 17, 2015-7-21, begin */
VOS_VOID TAF_MMA_SndMsccQuitCallBackNtf( VOS_VOID );
/* Added by h00313353 for Iteration 17, 2015-7-21, end */

VOS_VOID TAF_MMA_SndMsccCdmaMoCallEndNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);
VOS_VOID TAF_MMA_SndMsccCdmaMoCallSuccessNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType
);
VOS_VOID TAF_MMA_SndMsccCdmaMoCallRedialSysAcqNtf(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enCallType,
    VOS_UINT32                          ulCause
);
VOS_VOID TAF_MMA_SndMsccCFreqLockNtf(
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU *pstCFreqLockSetPara
);
VOS_UINT32 TAF_MMA_SndMsccCdmaCsqSetReq(
    NAS_MSCC_PIF_CDMACSQ_SET_PARA_STRU     stCdmaCsqSetPara
);


extern VOS_VOID TAF_MMA_SndMsccCFPlmnSetReq(
    TAF_PH_FPLMN_OPERATE_STRU          *pstFPlmnOperInfo
);

extern VOS_VOID TAF_MMA_SndMsccCFPlmnQueryReq(VOS_VOID);

/* Added by y00307564 for CDMA Iteration 8 2015-2-7 begin */
VOS_VOID TAF_MMA_SndMsccPrefPlmnSetReq(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt
);

VOS_VOID TAF_MMA_SndMsccPrefPlmnQueryReq(
    TAF_MMA_PREF_PLMN_QUERY_REQ_STRU   *pstRcvMsg
);

VOS_VOID TAF_MMA_SndMsccPrefPlmnTestReq(
    TAF_MMA_PREF_PLMN_TEST_REQ_STRU    *pstRcvMsg
);
/* Added by y00307564 for CDMA Iteration 8 2015-2-7 end */

NAS_MSCC_PIF_CDMA_CALL_TYPE_ENUM_UINT8 TAF_MMA_MapMmaCallTypeToMsccFormat(
    TAF_MMA_CDMA_CALL_TYPE_ENUM_UINT8   enMmaCallType
);

/* Added by y00314741 for CDMA Iteration 15, 2015-6-1, begin */
VOS_VOID TAF_MMA_SndMsccPsRatTypeNtf(
    TAF_MMA_PS_RAT_TYPE_ENUM_UINT32     enCurrCdataServiceMode
);
/* Added by y00314741 for CDMA Iteration 15, 2015-6-1, end */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndMsccVoiceDomainChangeInd(
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32                   enVoiceDomain
);

VOS_VOID TAF_MMA_SndMsccImsStartReq(VOS_VOID);


VOS_VOID TAF_MMA_SndMsccImsStopReq(VOS_VOID);
#endif

VOS_VOID TAF_MMA_SndMsccAutoReselSetReq(VOS_UINT8 ucActiveFlg);

/* Added by z00316370 for UTS 2015-5-22 begin */
VOS_UINT32 TAF_MMA_SndMsccHandsetInfoQryReq(
     MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32  enInfoType
);
/* Added by z00316370 for UTS 2015-5-22 end */

VOS_VOID TAF_MMA_SndMsccGetGeoReq(VOS_VOID);
VOS_VOID TAF_MMA_SndMsccStopGetGeoReq(VOS_VOID);

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

#endif /* end of TafSdcLib.h */
