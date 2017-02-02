

#ifndef __TAF_MMA_COM_FUNC_H__
#define __TAF_MMA_COM_FUNC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "TafAppMma.h"
#include "TafSdcCtx.h"
#include "MmaMsccInterface.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, begin */
#include "hsm_mma_pif.h"
#include "NasOmTrans.h"
#include "omnvinterface.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 封装OSA申请消息接口 */
#define TAF_MMA_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA, (ulMsgLen))

/* 封装OSA消息头 */
#define TAF_MMA_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = WUEPS_PID_MMA;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* 封装OSA消息头(MMA内部消息) */
#define TAF_MMA_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            TAF_MMA_CFG_MSG_HDR(pstMsg, WUEPS_PID_MMA, ulMsgId)

/* 获取OSA消息内容 */
#define TAF_MMA_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* 获取OSA消息长度 */
#define TAF_MMA_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* 封装OSA消息初始化消息内容接口 */
#define TAF_MMA_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(TAF_MMA_GET_MSG_ENTITY(pstMsg), 0x0, TAF_MMA_GET_MSG_LENGTH(pstMsg))

/* 封装OSA发送消息接口 */
#define TAF_MMA_SEND_MSG(pstMsg)\
            PS_SEND_MSG(WUEPS_PID_MMA, pstMsg)

/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define TAF_MMA_SESSION_STATUS_MAP_TBL_PTR()           (g_astTafMmaSessionStatusMapTbl)
#define TAF_MMA_SESSION_STATUS_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSessionStatusMapTbl)/sizeof(TAF_MMA_SESSION_STATUS_MAP_STRU))

#define TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_PTR()           (g_astTafMmaCdmaPhoneModeMapTbl)
#define TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaCdmaPhoneModeMapTbl)/sizeof(TAF_MMA_CDMA_PHONE_MODE_MAP_STRU))

#define TAF_MMA_SYS_MODE_MAP_TBL_PTR()           (g_astTafMmaSysModeMapTbl)
#define TAF_MMA_SYS_MODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSysModeMapTbl)/sizeof(TAF_MMA_SYS_MODE_MAP_STRU))

#define TAF_MMA_SYS_SUBMODE_MAP_TBL_PTR()           (g_astTafMmaSysSubModeMapTbl)
#define TAF_MMA_SYS_SUBMODE_MAP_TBL_SIZE()          (sizeof(g_astTafMmaSysSubModeMapTbl)/sizeof(TAF_MMA_SYS_SUBMODE_MAP_STRU))

#endif
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, end */

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

typedef struct
{
    NAS_OM_MMA_HRPD_SESSION_STATUS_ENUM_UINT8   enMmaSessionStatus;
    HSM_MMA_SESSION_STATUS_ENUM_UINT8           enHsmSessionStatus;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SESSION_STATUS_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_PHONE_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma phone mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_PHONE_MODE_ENUM_UINT8            enNasOmCdmaPhoneMode;
    TAF_SDC_PHONE_MODE_ENUM_UINT8               enTafCdmaPhoneMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_CDMA_PHONE_MODE_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_SYS_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma sys mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_SYS_MODE_ENUM_UINT8             enNasOmCdmaSysMode;
    TAF_SDC_SYS_MODE_ENUM_UINT8               enTafCdmaSysMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SYS_MODE_MAP_STRU;
/*****************************************************************************
 结构名  : TAF_MMA_CDMA_SYS_MODE_MAP_STRU
 结构说明: taf 与 nas om的cdma sys mode转换表

 修改历史      :
  1.日    期   : 2015年05月26日
    作    者   : y00322978
    修改内容   : 新增结构
*****************************************************************************/
typedef struct
{
    NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8             enNasOmSysSubMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8               enTafSysSubMode;
    VOS_UINT8                                   aucReserved[2];
} TAF_MMA_SYS_SUBMODE_MAP_STRU;
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

VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
);

VOS_VOID TAF_MMA_TransMsccImsStartResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
);

VOS_VOID TAF_MMA_TransMsccImsStopResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
);
#endif

VOS_UINT32 TAF_MMA_IsUserSettedSysCfgParaValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

VOS_UINT32  TAF_MMA_IsUserSettedGuBandValid(
    TAF_USER_SET_PREF_BAND64           *pstGuBand
);
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32  TAF_MMA_IsUserSettedLBandValid(
    TAF_USER_SET_PREF_BAND64           *pstLBand
);
#endif

/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_MMA_RatFrequentlySwitchRecord(VOS_VOID);

VOS_VOID TAF_MMA_ReportErrlogOosBegin(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain
);
VOS_VOID TAF_MMA_ReportErrlogOosEnd(
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain
);
VOS_VOID TAF_MMA_ProcErrlogDomainOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldRegState,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState,
    VOS_UINT32                          ulOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enOosDomain
);
VOS_VOID TAF_MMA_ProcErrlogOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);
#endif
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */

VOS_VOID TAF_MMA_RecordRegStatusReportFlag(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
);
VOS_UINT32 TAF_MMA_IsUsimServiceAvailable(VOS_VOID);

VOS_VOID TAF_MMA_UpdateGeoInfo(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
);

VOS_VOID TAF_MMA_SetAttachAllowFlg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8     ulAttachType
);

VOS_UINT32 TAF_MMA_IsRatOrderChange(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
);
VOS_UINT32 TAF_MMA_GetSysCfgRatFlag(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    VOS_UINT32                         *pulRatExistedFlg
);

/* Added by h00313353 for CDMA Iteration 15, 2015-5-29, begin */
VOS_VOID TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penOutSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                         *penOutSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                   *ppTafSdcSysmodServiceRegStaUpdateFunc
);

VOS_VOID TAF_MMA_UpdateSerRegSta_HrpdToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAT_MMA_UpdateSerRegSta_HybridTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_1xToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_HybridToHrpd(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteToLte(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_LteToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ChgSysModeAndSrvRegSta(
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct,
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, begin */
VOS_UINT8 TAF_MMA_MapHsmSessionStatus(
    HSM_MMA_SESSION_STATUS_ENUM_UINT8   enSessionStatus
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-7, begin */
VOS_UINT32 TAF_MMA_QryCdmaStatusInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU                *pstCdmaCommInfo,
    NAS_OM_MMA_1X_SYS_INFO_STRU                            *pst1xSysInfo,
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                          *pstHrpdSysInfo
);
VOS_UINT8 TAF_MMA_MapSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
);
VOS_UINT8 TAF_MMA_MapCdmaPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
);
VOS_VOID TAF_MMA_ConvertMeidToUl(
    VOS_UINT8                          *pucMeid,
    VOS_UINT32                         *pMeid,
    VOS_UINT32                         *pMeidCnt
);
VOS_UINT32 TAF_MMA_ConvertUatiToUl(
    VOS_UINT8                          *pstUati
);
VOS_UINT8 TAF_MMA_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
);
VOS_UINT8 TAF_MMA_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
);
VOS_UINT8 TAF_MMA_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
);
MODEM_ID_ASN_ENUM_UINT16 TAF_MMA_MapModemId(
    MODEM_ID_ENUM_UINT16                enModemId
);
/* Added by y00322978 for CDMA Iteration 17, 2015-7-7, end */
#endif
/* Added by h00313353 for CDMA Iteration 15, 2015-5-29, end */



VOS_VOID TAF_MMA_ConvertSysInfoExSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
    MN_PH_SYS_MODE_EX_ENUM_U8          *penDestSysMode
);

VOS_VOID TAF_MMA_ConvertSysInfoExSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
);

VOS_UINT8 TAF_MMA_IsSameAsAppServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_UpdateAppSrvStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);

VOS_VOID TAF_MMA_UpdateAppRegStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_UpdateAppNetworkInfo(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppServPlmnInfo(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppReportSrvStatus(VOS_VOID);
VOS_VOID TAF_MMA_UpdateAppReportSrvDomain(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
);
VOS_VOID TAF_MMA_ProcDelayReport(VOS_VOID);
VOS_VOID TAF_MMA_ProcServiceStatusImmediatelyReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);
VOS_VOID TAF_MMA_ProcServiceStatusNotReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
);

VOS_VOID TAF_MMA_FillActForAtCmdCregInClMode(
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType,
    TAF_PH_ACCESS_TECH_ENUM_UINT8                          *pucAct
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

#endif /* end of TafMmaFsmImsSwitch.h */


