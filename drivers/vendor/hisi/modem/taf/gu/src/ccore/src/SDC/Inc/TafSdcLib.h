
#ifndef _TAF_SDC_LIB_H_
#define _TAF_SDC_LIB_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "TafSdcCtx.h"

#include "TafOamInterface.h"
/* Added by wx270776 for OM融合, 2015-7-25, begin */
#include "TafLog.h"
/* Added by wx270776 for OM融合, 2015-7-25, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PRE_SECOND_TO_TICK                      (100)

#define TAF_SDC_REV_IN_USE_7                    (7)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcCurcRptCmdTable[0])
#define TAF_SDC_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcCurcRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))

#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenTafSdcUnsolicitedRptCmdTable[0])
#define TAF_SDC_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenTafSdcUnsolicitedRptCmdTable)/sizeof(TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8))

#define TAF_SDC_MIN(n1,n2)                                  (((n1) > (n2)) ? (n2):(n1))


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
extern VOS_VOID DIAG_TraceReport(VOS_VOID* pMsg);

VOS_UINT32  TAF_SDC_IsPlatformRatSupported(
    TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8                    enSpecRat
);

VOS_UINT32  TAF_SDC_IsPlatformSupportLte( VOS_VOID );

VOS_UINT32  TAF_SDC_IsPlatformSupportUtran( VOS_VOID );
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranFdd( VOS_VOID );
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32  TAF_SDC_IsPlatformSupportUtranTdd( VOS_VOID );
#endif

VOS_UINT32  TAF_SDC_IsPlatformSupportGsm( VOS_VOID );

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp2(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlatformSupport1x(VOS_VOID);
VOS_UINT32 TAF_SDC_IsPlatformSupportHrpd(VOS_VOID);

#endif

VOS_UINT32 TAF_SDC_IsPlatformSupport3Gpp(VOS_VOID);


VOS_UINT32 TAF_SDC_CheckRptCmdStatus(
    VOS_UINT8                                  *pRptCfg,
    TAF_SDC_CMD_RPT_CTRL_TYPE_ENUM_UINT8        enRptCtrlType,
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex
);
VOS_VOID TAF_SDC_UpdateRptCmdStatus(
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex,
    VOS_UINT32                                  ulRptCmdStatus
);

VOS_UINT32 TAF_SDC_ConvertOamSendPid(
    VOS_UINT32                          ulConvertedSendPid
);

VOS_UINT32 TAF_SDC_GetCsSrvExistFlg(VOS_VOID);



VOS_UINT32 TAF_SDC_GetImsSupportFlag(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT32 TAF_SDC_IsErrLogNeedRecord(VOS_UINT16 usLevel);
#endif

VOS_UINT32  TAF_CalcTime(
                VOS_UINT32  ulFirTime,
                VOS_UINT32  ulSecTime,
                VOS_UINT32 *pulTotalTime
);

VOS_UINT32 TAF_SDC_IsUsimStausValid(VOS_VOID);


#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInUE(VOS_VOID);
VOS_UINT32 TAF_SDC_IsImsVoiceSupportedInNW(VOS_VOID);
#endif

VOS_VOID TAF_SDC_PlmnId2Bcd(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);


VOS_UINT32 TAF_SDC_IsConfigCLInterWorkCOutside(VOS_VOID);


VOS_UINT32 TAF_SDC_IsBcchPlmnIdInDestSimPlmnList (
    TAF_SDC_PLMN_ID_STRU               *pstBcchPlmnId,
    VOS_UINT8                           ucSimPlmnNum,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnIdList
);
VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);

VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId,
    VOS_CHAR                             cWildcard
);

TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetOplFileType(VOS_VOID);
TAF_SDC_FILE_TYPE_ENUM_UINT8  TAF_SDC_GetPnnFileType(VOS_VOID);
TAF_SDC_SPDI_FILE_INFO_STRU* TAF_SDC_GetSpdiFileInfo(VOS_VOID);
VOS_VOID TAF_SDC_ConvertPlmnId2NasStyle(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);


VOS_UINT32 TAF_SDC_IsLteOnlyMode(
    TAF_SDC_RAT_PRIO_STRU              *pstRatOrder
);

VOS_UINT32 TAF_SDC_CheckDtmfKey(
    VOS_CHAR                           *pckey
);

VOS_UINT32 TAF_SDC_IsCsNormalService(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlatformSupportHybrid(VOS_VOID);

VOS_UINT32 TAF_SDC_IsImsSrvExist(VOID);


VOS_UINT8 TAF_SDC_IsCurrentNormalServiceStatus(void);

VOS_UINT8 TAF_SDC_IsCurrentNormalRegStatus(void);

VOS_VOID TAF_MMA_UpdateRoamFlag(
    TAF_SDC_REG_STATUS_ENUM_UINT8      enRegState
);

VOS_UINT32 TAF_SDC_IsAppSepcDomainRegStaChg(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
);


/* Added by c00318887 for AT&T phaseII, 2015-2-27, begin */
VOS_UINT32 TAF_SDC_ExactlyCompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);
VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn(
    TAF_SDC_PLMN_ID_STRU                *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU                *pstSimPlmnId
);

VOS_UINT32 TAF_SDC_CompareBcchMccwithSimMcc_WithWildcard(
    VOS_UINT32                          ulBcchMcc,
    VOS_UINT32                          ulSimMcc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMncLow2ByteWithSimMnclowLow2Byte_WithWildcard(
    VOS_UINT32                          ulBcchMnc,
    VOS_UINT32                          ulSimMnc,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMncwithSimMnc_WithWildcard(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_CHAR                            cWildcard,
    VOS_UINT8                           ucExactlyCmpFlg
);
VOS_UINT32 TAF_SDC_CompareBcchMnc3BytewithSimMnc3Byte(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_UINT8                           ucExactlyCmpFlg
);

VOS_UINT32 TAF_SDC_IsVailidWildcard(
    VOS_CHAR                            cWildcard
);

VOS_VOID TAF_SDC_HexToAsciiOfPlmnByte(
    VOS_UINT8                            ucSrc,
    VOS_UINT8                           *pucDst
);

VOS_UINT32 TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildcard(
    TAF_SDC_PLMN_ID_STRU               *pstBccPlmnId,
    TAF_SDC_PLMN_ID_STRU               *pstSimPlmnId,
    VOS_CHAR                            cWildcard
);

VOS_UINT32  TAF_SDC_IsOperNameTypeSupport(
    TAF_SDC_OPER_NAME_TYPE_ENUM_UINT8   enOperNameType
);

VOS_VOID  TAF_SDC_ConvertSimPlmnToNasPLMN(
    TAF_SDC_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    TAF_SDC_PLMN_ID_STRU                *pstNasPlmn
);

/* Added by c00318887 for AT&T phaseII, 2015-2-27, end */

VOS_UINT32 TAF_SDC_IsSysCfgRatSupportHrpdAndLte(VOS_VOID);

VOS_UINT32 TAF_SDC_IsPlmnIdValid(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_SDC_IsConfigCLMode(VOS_VOID);
VOS_UINT32 TAF_SDC_Is1xOnlyMode(VOS_VOID);

VOS_UINT32 TAF_SDC_Get1xConcurrentSupportedFlag(VOS_VOID);

#endif

VOS_UINT32 TAF_SDC_IsSpecRatSupported(
    VOS_RATMODE_ENUM_UINT32             enRatMode
);

TAF_SDC_PLATFORM_RAT_TYPE_ENUM_UINT8 TAF_SDC_ConvertNvPlatformRatToTafType(
    PLATFORM_RAT_TYPE_ENUM_UINT16       enNvPlatformRatCap
);

VOS_UINT32 TAF_SDC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

VOS_UINT32 TAF_SDC_IsSyscfgSupportSpecRat(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);

VOS_UINT32 TAF_SDC_IsSyscfgSupport3gppRat(VOS_VOID);


VOS_UINT32 TAF_SDC_IsNeedReportRegStatusWhenNonnormalService(
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState
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

#endif /* end of TafSdcLib.h */
