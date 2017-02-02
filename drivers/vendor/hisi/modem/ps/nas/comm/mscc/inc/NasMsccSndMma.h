

#ifndef __NAS_MSCC_SND_MMA_H__
#define __NAS_MSCC_SND_MMA_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"
#include "xsd_mscc_pif.h"
#include "hsd_mscc_pif.h"

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
VOS_VOID NAS_MSCC_SndMmaImsVoiceCapInd(
    VOS_UINT8                           ucImsVoiceAvail
);

VOS_VOID NAS_MSCC_SndMmaNetworkCapabilityInfoInd(
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU              *pstNwCapInfoInd
);

VOS_VOID NAS_MSCC_SndMmaRegResultInd(
    MMC_MSCC_REG_RESULT_IND_STRU       *pstRegResultInd
);

VOS_VOID NAS_MSCC_SndMma3gppSysInfoInd(
    MMC_MSCC_SYS_INFO_IND_STRU         *pstSysInfoInd
);

VOS_VOID NAS_MSCC_SndMmaServiceStatusInd(
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd
);

/* Added by x00314862 for CDMA 1X Iteration 8 2015-1-31 begin */
VOS_VOID NAS_MSCC_SndMmaUserSpecPlmnSearchRej( VOS_VOID );

VOS_VOID NAS_MSCC_SndMmaAcInfoChangeInd(
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU  *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaEplmnInfoInd(
    MMC_MSCC_EPLMN_INFO_IND_STRU       *pstMsg
);


VOS_VOID NAS_MSCC_SndMmaEOPlmnSetCnf(
    MMC_MSCC_EOPLMN_SET_CNF_STRU       *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCampOnInd(
    MMC_MSCC_CAMP_ON_IND_STRU_STRU     *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaWCipherInfo(
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaGCipherInfo(
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAcqCnf(
    MMC_MSCC_ACQ_CNF_STRU              *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAcqInd(
    MMC_MSCC_ACQ_IND_STRU               *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaRegCnf(
    MMC_MSCC_REG_CNF_STRU              *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaPowerSaveCnf(
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPsServiceConnStatusInd(
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaRfAvailInd(
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnListCnf(
    MMC_MSCC_PLMN_LIST_CNF_STRU        *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnListRej(
    MMC_MSCC_PLMN_LIST_REJ_STRU        *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelCnf(
   MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnSpecialSelRej(
  MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPlmnReselCnf(
  MMC_MSCC_PLMN_RESEL_CNF_STRU         *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaRssiInd(
    MMC_MSCC_RSSI_IND_STRU             *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaMmInfo(
    MMC_MSCC_MM_INFO_IND_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSystemAcquireStartInd(
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32   enSysType
);

VOS_VOID NAS_MSCC_SndMmaDataTranAttri(
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCoverageInd(
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaNetScanCnf(
    MSCC_MMA_NET_SCAN_CNF_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAbortNetScanCnf(
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaUsimAuthFailInd(
    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCsServiceConnStatusInd(
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU               *pstMsg
);

VOS_UINT32 NAS_MSCC_SndMmaServRejRsltInd(
    MMC_MSCC_SERV_REJ_IND_STRU         * pstMsg
);

VOS_VOID NAS_MSCC_SndMmaAttachCnf(
     MMC_MSCC_ATTACH_CNF_STRU          *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDetachInd(
    MMC_MSCC_DETACH_IND_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaDetachCnf(
    MMC_MSCC_DETACH_CNF_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSysCfgCnf(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32      ulSysCfgCnfRst
);

VOS_VOID NAS_MSCC_SndMmaPlmnListAbortCnf(
    MSCC_MMA_PLMN_LIST_ABORT_CNF_STRU    *pstMmcPlmnListAbortCnf
);

VOS_VOID NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf(
    MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU               *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaGetGeoCnf(
    MMC_MSCC_GET_GEO_CNF_STRU            *pstMsg
);
VOS_VOID NAS_MSCC_SndMmaStopGetGeoCnf(
    MMC_MSCC_STOP_GET_GEO_CNF_STRU     *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaSrvAcqCnf(
    MMC_MSCC_SRV_ACQ_CNF_STRU          *pstMsg
);


VOS_VOID NAS_MSCC_SndMmaSwitchOnRsltCnf(
    NAS_MSCC_PIF_START_RESULT_ENUM_UINT32                   ulRslt
);

VOS_VOID NAS_MSCC_SndMmaPowerOffRsltCnf(VOS_VOID);

VOS_VOID NAS_MSCC_SndMmaSystemAcquireEndInd(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult,
    MSCC_MMA_ACQ_SYS_TYPE_ENUM_UINT32                       enAcqSysType,
    MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_ENUM_UINT32      enAcqRsltType
);

/* Added by x00314862 for CDMA 1X Iteration 8 2015-1-31 end */
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
VOS_VOID NAS_MSCC_SndMmaHrpdServiceStatusInd(
    MSCC_MMA_HRPD_SERVICE_STATUS_ENUM_UINT32                enHrpdSrvSta,
    VOS_UINT8                                               ucIsNewSession,
    VOS_UINT8                                               ucIsEhrpdSupport,
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType
);
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */

VOS_VOID NAS_MSCC_SndMmaHrpdOverheadMsgInd(
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstMsccOhmMsgs
);



extern VOS_VOID NAS_MSCC_SndMmaCFPlmnSetCnf(
    MMC_MSCC_CFPLMN_SET_CNF_STRU       *pstMsg
);
extern VOS_VOID NAS_MSCC_SndMmaCFPlmnQueryCnf(
    MMC_MSCC_CFPLMN_QUERY_CNF_STRU     *pstMsg
);

/* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
VOS_VOID NAS_MSCC_SndMmaPrefPlmnQueryCnf(
    MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU  *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaPrefPlmnSetCnf(
    MMC_MSCC_PREF_PLMN_SET_CNF_STRU  *pstMsg
);
/* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */

/* Added by x00314862 for CDMA Iteration 9 2015-2-11 begin */
VOS_VOID NAS_MSCC_SndMmaCdmacsqSetCnf(
    XSD_MSCC_CDMACSQ_SET_CNF_STRU      *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaCdmacsqSignalQualityInd(
   XSD_MSCC_CDMACSQ_IND_STRU           *pstMsg
);

VOS_VOID NAS_MSCC_SndMma1xSystemServiceInfoInd(
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaLmmCellSignInfoReportInd(
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstMsg
);

/* Added by x00314862 for CDMA Iteration 9 2015-2-11 end */

VOS_VOID NAS_MSCC_SndMma1xSystemTimeInd(
    XSD_MSCC_1X_SYSTEM_TIME_IND_STRU   *pstMsg
);

VOS_VOID NAS_MSCC_SndMmaUeStatusInd(
    VOS_UINT8                           ucUeMainState,
    VOS_UINT8                           ucUeSubState
);



#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MSCC_SndMmaImsStartCnf(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult
);

VOS_VOID NAS_MSCC_SndMmaImsStopCnf(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult
);

VOS_VOID NAS_MSCC_SndMmaImsSwitchStateInd(
    NAS_MSCC_PIF_IMS_SWITCH_STATE_ENUM_UINT8                enImsSwitch
);
#endif


/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_SndMmaInterSysStartInd(
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause
);

VOS_VOID NAS_MSCC_SndMmaInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCampedRatMode
);
VOS_VOID NAS_MSCC_SndMmaSidInd(
    VOS_UINT16                          usSid
);

VOS_VOID NAS_MSCC_SndMmaSyncServiceAvailInd(
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                   *pstSyncSrvAvailInd
);
#endif

VOS_VOID NAS_MSCC_SndMmaSrchedPlmnInfo(
    MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU                     *pstMsg
);
/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, end */

/* Added by z00316370 for UTS 2015-5-22 begin */
VOS_VOID NAS_MSCC_SndMmaHandsetInfoQryCnf(
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU                     *pstInfo
);
/* Added by z00316370 for UTS 2015-5-22 end */

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

#endif /* end of NasMsccSndMma.h */
