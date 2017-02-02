

#ifndef __NAS_MSCC_SND_MMC_H__
#define __NAS_MSCC_SND_MMC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MsccMmcInterface.h"
#include  "MmaMsccInterface.h"


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


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID NAS_MSCC_SndMmcImsVoiceCapNotify(
    VOS_UINT8                           ucImsVoiceAvail,
    VOS_UINT8                           ucIsExistPersistentBearer
);


VOS_VOID NAS_MSCC_SndMmcSignalReportReq(
    MMA_MSCC_SIGN_REPORT_REQ_STRU      *pstSigReportReq
);

VOS_VOID NAS_MSCC_SndMmcModeChangeReq(
    MMA_MSCC_MODE_CHANGE_REQ_STRU      *pstModeChangeReq
);

VOS_VOID NAS_MSCC_SndMmcAttachReq(
    MMA_MSCC_ATTACH_REQ_STRU           *pstAttachReq
);

VOS_VOID NAS_MSCC_SndMmcDetachReq(
    MMA_MSCC_DETACH_REQ_STRU           *pstDetachReq
);

VOS_VOID NAS_MSCC_SndMmcPlmnListReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcPlmnListAbortReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcPlmnUserReselReq(
    MMA_MSCC_PLMN_USER_RESEL_REQ_STRU  *pstPlmnUserReselReq
);

VOS_VOID NAS_MSCC_SndMmcPlmnSpecialReq(
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU     *pstPlmnSpecialReq
);

VOS_VOID  NAS_MSCC_SndMmcSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
);

VOS_VOID NAS_MSCC_SndMmcNetScanMsgReq(
    MMA_MSCC_NET_SCAN_REQ_STRU         *pstNetScanReq
);

VOS_VOID NAS_MSCC_SndMmcAbortNetScanMsgReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcPlmnSearchReq(
    NAS_MSCC_PIF_ACQ_REASON_ENUM_UINT32                     enAcqReason,
    NAS_MSCC_PIF_INIT_ACQ_PLMN_INFO_STRU                   *pstInitAcqPlmnInfo,
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstHighPrioPlmnInfo
);

VOS_VOID NAS_MSCC_SndMmcSpecPlmnSearchAbortReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcOmMaintainInfoInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstMaintainInfoInd
);

VOS_VOID NAS_MSCC_SndMmcUpdateUplmnNotify( VOS_VOID );

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID NAS_MSCC_SndMmcOtherModemInfoNotify(
    MSCC_MMC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstOtherModemInfoNtf
);

VOS_VOID NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify(
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU     *pstOhterModemDplmnNplmnInfoNtf
);

VOS_VOID NAS_MSCC_SndMmcNcellInfoNotify(
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstNcellInfoNtf
);

VOS_VOID NAS_MSCC_SndMmcPsTransferNotify(
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstPsTransferNtf
);
#endif

VOS_VOID NAS_MSCC_SndMmcEOPlmnSetReq(
    MMA_MSCC_EOPLMN_SET_REQ_STRU       *pstEOPlmnSetReq
);

VOS_VOID NAS_MSCC_SndMmcAcqReq(
    MMA_MSCC_ACQ_REQ_STRU              *pstAcqReq
);

VOS_VOID NAS_MSCC_SndMmcRegReq(
    MMA_MSCC_REG_REQ_STRU              *pstRegReq
);

VOS_VOID NAS_MSCC_SndMmcPowerSaveReq(VOS_VOID);

#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MSCC_SndMmcSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
);

VOS_VOID NAS_MSCC_SndMmcBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
);

VOS_VOID NAS_MSCC_SndMmcEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
);
#endif

VOS_VOID NAS_MSCC_SndMmcImsSrvInfoNotify(
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU  *pstImsSrvInfoNtf
);


VOS_VOID NAS_MSCC_TransferMsccToMmcRat(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio,
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstPlmnRatPrio,
    NAS_MSCC_PIF_3GPP2_RAT_STRU        *pst3Gpp2Rat
);

VOS_VOID NAS_MSCC_SndMmcStartReq(
    MMA_MSCC_START_REQ_STRU        *pstStartReq
);


VOS_UINT32 NAS_MSCC_SndMmcPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 enCause
);

extern VOS_VOID NAS_MSCC_SndMmcCFPlmnSetReq(
    MMA_MSCC_CFPLMN_SET_REQ_STRU       *pstCFPlmnReq
);
extern VOS_VOID NAS_MSCC_SndMmcSdtConnedInd(
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstSdtConnInfoInd
);
extern VOS_VOID NAS_MSCC_SndMmcCFPlmnQueryReq(
    MMA_MSCC_CFPLMN_QUERY_REQ_STRU     *pstCFPlmnReq
);

/* Added by y00307564 for CDMA Iteration 8 2015-2-4 begin */
VOS_VOID NAS_MSCC_SndMmcPrefPlmnQueryReq(
    MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU  *pstMsg
);
VOS_VOID NAS_MSCC_SndMmcPrefPlmnSetReq(
    MMA_MSCC_PREF_PLMN_SET_REQ_STRU    *pstMsg
);

VOS_VOID NAS_MSCC_SndMmcGetGeoReq(
    MMA_MSCC_GET_GEO_REQ_STRU          *pstMsg
);
VOS_VOID NAS_MSCC_SndMmcStopGetGeoReq(
    MMA_MSCC_STOP_GET_GEO_REQ_STRU     *pstMsg
);

/* Added by y00307564 for CDMA Iteration 8 2015-2-4 end */
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MSCC_SndMmcVoiceDomainChangeInd(
    NAS_MSCC_PIF_VOICE_DOMAIN_ENUM_UINT32                   enVoiceDomain
);

VOS_VOID NAS_MSCC_SndMmcImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
);
#endif

/* Added by y00307564 for CDMA Iteration 10 2015-4-3 begin */
VOS_VOID NAS_MSCC_SndMmcBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
);

VOS_VOID NAS_MSCC_SndMmcStopBgSearchReq(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmcPlmnPriClassQueryReq(
    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU              *pstPlmnList
);

/* Added by y00307564 for CDMA Iteration 10 2015-4-3 end */

/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_SndMmcInterSysHrpdInd(VOS_VOID);
#endif
/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, end */

VOS_VOID NAS_MSCC_SndMmcAutoReselSetReq(
    VOS_UINT8                           ucActiveFlg                
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

#endif /* end of NasMsccSndMmc.h */
