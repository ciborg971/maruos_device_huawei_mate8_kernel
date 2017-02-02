
#ifndef _TAF_MMA_SND_APP_H_
#define _TAF_MMA_SND_APP_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasStkInterface.h"
#include "MmaMsccInterface.h"

#include "TafAppMma.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 begin */

#define TAF_MMA_TIME_ZONE_MIN                               (-24)                /* TIME ZONE 下限 */
#define TAF_MMA_TIME_ZONE_MAX                               (28)                 /* TIME ZONE 上限 */

#define TAF_MMA_MILLISECOND_FOR_ONE_SECOND                  (1000)               /* 1000ms */

#define TAF_MMA_EIGHTY_MILLISECOND_UNIT                     (80)                 /* 80ms */

#define TAF_MMA_LTM_OFF_FOR_HALF_HOUR                       (22500)              /* 30*60*1000/80 system time是以80ms为单位的 */

/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 end */

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

/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-17, begin */
VOS_VOID TAF_MMA_SndSysCfgSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);
/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-17, end */

VOS_VOID TAF_MMA_SndPhoneModeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_MODE                         ucPhMode,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

/* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
VOS_VOID TAF_MMA_SndEonsUcs2Rsp(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
);
/* Added by c00318887 for AT&T phaseII, 2015-3-12, end */

VOS_VOID TAF_MMA_SndAcqBestNetworkCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_CNF_STRU               *pstAcqCnfMsg
);

VOS_VOID TAF_MMA_SndRegCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_REG_CNF_STRU               *pstRegCnfMsg
);

VOS_VOID TAF_MMA_SndPowerSaveCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt
);

VOS_VOID TAF_MMA_SndDetachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enDetachRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

VOS_VOID TAF_MMA_SndSrvAcqCnf(
    TAF_MMA_SRV_ACQ_RESULT_ENUM_UINT8   enResult
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_VOID TAF_MMA_SndCmmcaServiceInd(VOS_VOID);

VOS_VOID TAF_MMA_SndAcqInd(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    MSCC_MMA_ACQ_IND_STRU               *pstAcqIndMsg
);

VOS_VOID TAF_MMA_SndCmmcaSysInfoInd(
    VOS_UINT32                                              ulMcc,
    VOS_UINT32                                              ulMnc,
    VOS_UINT32                                              ulArfcn,
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enPrioClass
);
VOS_VOID TAF_MMA_SndSimStatusInd(
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType,                    /* 卡类型:SIM、USIM、ROM-SIM  */
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus
);

#endif

extern VOS_VOID TAF_MMA_BuildRssiInd(
    TAF_MMA_RSSI_INFO_IND_STRU         *pstRssiInd
);

VOS_VOID TAF_MMA_SndAtRssiInd(VOS_VOID);
/* Added by h00313353 for iteration 9, 2015-2-7, begin */
VOS_VOID TAF_MMA_SndATUsimmStatusInd(
    USIMM_CARDSTATUS_IND_STRU          *pStPsUsimStatusInd,
    VOS_UINT8                          *pucIMSI
);
/* Added by h00313353 for iteration 9, 2015-2-7, end */

/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-26 begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_SndCdmaCsqSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
);

VOS_VOID TAF_MMA_SndCdmaCsqInd(VOS_INT8 cCdmaRssi,VOS_INT8 cCdmaEcIo);

VOS_UINT32 TAF_MMA_SndCFreqLockSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
);


/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 begin */
extern VOS_VOID TAF_MMA_ProcessCSystemTime(NAS_MSCC_PIF_1X_SYS_TIME_STRU *pstSysTime);

extern VOS_UINT32 TAF_MMA_FillCTimeIndStru(
    NAS_MSCC_PIF_1X_SYS_TIME_STRU      *pstSysTime,
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
);

extern VOS_UINT32 TAF_MMA_SndCTimeInd(
    TAF_MMA_TIME_ZONE_CTIME_STRU       *pstTimezoneCTime
);
/* Added by x00314862 for CDMA 1X Iteration 6 2014-12-26 end */

/* Added by z00316370 for UTS 2015-5-18 begin */
extern VOS_VOID TAF_MMA_Snd1xChanSetCnf(
    TAF_MMA_CFREQ_LOCK_SET_REQ_STRU    *pstCFreqLockSetReq,
    VOS_UINT32                          ulRslt
);

extern VOS_VOID TAF_MMA_SndGetStaQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_HANDSET_STATE_STRU                             *pstHandsetSta,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
);

extern VOS_VOID TAF_MMA_SndCHVerQryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_1X_CAS_P_REV_ENUM_UINT8                         enHighRev,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enRslt
);
/* Added by z00316370 for UTS 2015-5-18 end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
VOS_VOID TAF_MMA_SndQuitCallBackCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);
VOS_VOID TAF_MMA_SndSetCSidListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */
#endif
/* Added by m00312079 for CDMA 1X Iteration 6 2014-12-26 end */

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndImsSwitchSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);
VOS_VOID TAF_MMA_SndImsSwitchQryCnf(
    TAF_MMA_CTRL_STRU                          *pstCtrl,
    VOS_UINT8                                   ucImsSwitch
);
#endif
VOS_VOID TAF_MMA_SndVoiceDomainSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);
VOS_VOID TAF_MMA_SndVoiceDomainQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);

extern VOS_VOID TAF_MMA_SndCFPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt
);
extern VOS_VOID TAF_MMA_SndCFPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt,
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                         *pstCFPlmnCnfMsg
);

VOS_VOID TAF_MMA_SndAtRegStatus(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32       enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
);

VOS_VOID TAF_MMA_SndPlmnListCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara
);

extern VOS_VOID TAF_MMA_SndCerssiSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndAccessModeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enAccessMode,
    TAF_PH_PLMN_PRIO                    ucPlmnPrio
);

extern VOS_VOID TAF_MMA_SndCopsQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_NETWORKNAME_STRU            *pstCopsInfo
);

extern VOS_VOID TAF_MMA_SndRegStateQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_REG_STATE_STRU              *pstRegInfo
);

extern VOS_VOID TAF_MMA_SndAutoAttachQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    VOS_UINT8                           ucAutoAttachFlag
);

extern VOS_VOID TAF_MMA_SndSystemInfoQryCnf(
    TAF_MMA_SYSINFO_QRY_REQ_STRU       *pstSysInfoQryReq,
    TAF_PH_SYSINFO_STRU                *pstSysInfo
);


extern VOS_VOID TAF_MMA_SndAntennaInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_MMA_ANQUERY_PARA_STRU           *pstAnqueryInfo
);

extern VOS_VOID TAF_MMA_SndApHplmnCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU    *pstHplmnWithMnc
);

extern VOS_VOID TAF_MMA_SndSrvStatusInd(
    TAF_PHONE_CHANGED_SERVICE_STATUS    ucSrvStatus
);

extern VOS_VOID TAF_MMA_SndRegStatusInd(
    TAF_PH_REG_STATE_STRU              *pstRegState
);

extern VOS_VOID TAF_MMA_SndRegRejInd(
    TAF_PH_REG_REJ_INFO_STRU           *pstRejInfo
);

extern VOS_VOID TAF_MMA_SndPlmnSelectionInd(
    TAF_MMA_PLMN_SELECTION_INFO_STRU    *pstPlmnSelectInfo
);

extern VOS_VOID TAF_MMA_SndCipherQryCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCipherInfo,
    VOS_UINT32                          ulResult
);

/* Added by k902809 for Iteration 11, 2015-3-25, begin */
VOS_VOID TAF_MMA_SndNetScanCnf(
    TAF_MMA_NET_SCAN_CNF_STRU          *pstRcvNetScanCnf);
/* Added by k902809 for Iteration 11,  2015-3-25, end */

VOS_VOID TAF_MMA_SndBatteryCapacityQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_BATTERYPOWER_STRU          *pstBatteryStatus
);

VOS_VOID TAF_MMA_SndHandShakeQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    VOS_UINT8                          *pPara
);

extern VOS_VOID TAF_MMA_SndCFPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_CFPLMN_OPER_RESULT_ENUM_UINT32              enRslt,
    MSCC_MMA_CFPLMN_QUERY_CNF_STRU                         *pstCFPlmnCnfMsg
);

extern VOS_VOID TAF_MMA_ProcPlmnAutoReselCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_ProcPlmnSpecialSelCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndPlmnAutoReselCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndPlmnSpecialSelCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndPlmnListAbortCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndLocInfoQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_LOCATION_INFO_QRY_CNF_STRU *pstLocInfoQryCnfMsg
);

extern VOS_VOID TAF_MMA_SndPrefPlmnTypeSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
);

extern VOS_VOID TAF_MMA_SndMtPowrDownCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_ProcPlmnListAbortCnf(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);


/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-28, begin */
extern VOS_VOID TAF_MMA_SndCsqLvlQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CSQLVL_PARA_STRU           *pstCsqlvlPara,
    TAF_MMA_CSQLVLEXT_PARA_STRU        *stCsqLvlExtPara,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);

extern VOS_VOID TAF_MMA_SndCsqQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PH_RSSI_STRU                   *pstCsqPara
);

extern VOS_VOID TAF_MMA_SndAutoAttachSetCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_PARA_SET_RESULT                 enRslt
);

extern VOS_VOID TAF_MMA_SndCrpnQryCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_CRPN_QRY_INFO_STRU         *pstMnMmaCrpnQryCnf,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);
/* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-28, end */
/* Modified by l00301449 for Iteration 13, 2015-04-11, begin */
VOS_VOID TAF_MMA_SndAttachCnf(
    TAF_MMA_CTRL_STRU                  *pstCtrl,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
);
/* Modified by l00301449 for Iteration 13, 2015-04-11, end */
/* Added by h00313353 for Iteration 13, 2015-4-17, begin */
VOS_VOID TAF_MMA_SndAttachStatusQryCnf(
    TAF_MMA_ATTACH_STATUS_QRY_REQ_STRU *pstRcvMsg,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enCsStatus,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    enPsStatus
);
/* Added by h00313353 for Iteration 13, 2015-4-17, end */
extern TAF_MMA_RAT_TYPE_ENUM_UINT8 TAF_MMA_ConvertMmlRatTypeToTafRatType(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enMmlRatType
 );
extern VOS_VOID TAF_MMA_SndSrchedPlmnInfoInd(
    MSCC_MMA_SRCHED_PLMN_INFO_IND_STRU  *pstSrchedPlmnInfoInd
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

#endif /* end of TafMmaSndApp.h */

