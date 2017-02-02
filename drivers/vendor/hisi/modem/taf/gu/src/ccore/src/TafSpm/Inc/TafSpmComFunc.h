
#ifndef _TAF_SPM_COM_FUNC_H_
#define _TAF_SPM_COM_FUNC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"

#include "TafSpmCtx.h"
#include "TafSdcCtx.h"
#include "MnCallApi.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#endif

#include "TafInternalInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MN_CALL_MAX_ASCII_NUM_LEN    (MN_CALL_MAX_BCD_NUM_LEN * 2)

#define TAF_SPM_ECONF_GET_INDEX_FROM_PARA(ulPara)       ((ulPara >> 16) & VOS_NULL_WORD)

#define TAF_SPM_ECONF_SET_SEND_PARA(ulIndex, usClient)  ((VOS_UINT32)((ulIndex << 16) | (VOS_UINT32)usClient))




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
VOS_UINT32  TAF_SPM_IsNetworkEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsAppCustomEmergencyNum(
    MN_CALL_CALLED_NUM_STRU             *pstDialNum,
    VOS_UINT32                          *pulEmerCatExist,
    VOS_UINT8                           *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);

VOS_UINT32 TAF_SPM_GetBcCallType(
    VOS_UINT32                          bExistBc,
    VOS_UINT32                          ulBcLength,
    VOS_UINT8                          *pucBc,
    MN_CALL_TYPE_ENUM_U8               *penCallType
);

VOS_UINT32 TAF_SPM_IsPhoneEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum
);

VOS_UINT32  TAF_SPM_IsEmergencyNum(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                          ulCheckEfecc,
    MN_CALL_EMERGENCY_CAT_STRU         *pstEmergencyCat
);

VOS_UINT32 TAF_SPM_IsUsimServiceAvailable(VOS_VOID);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithAtClient(
    struct MsgCB                       *pstMsg
);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithStkClient(
    struct MsgCB                       *pstMsg
);
TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestTypeWithTafClient(
    struct MsgCB                       *pstMsg
);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
VOS_VOID TAF_SPM_ConvertSrvTypeToMma(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSpmSrvReq,
    TAF_MMA_SRV_TYPE_ENUM_UINT8        *pucMmaSrvType
);
/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8 TAF_SPM_GetServiceRequestType(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_IsUssdServiceType(
    VOS_UINT32                          ulEventType
);
#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_SPM_SendTafAgentGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
);
VOS_VOID TAF_SPM_SendAtGetCallInfoCnf(
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU    *pstImsaMsg
);
#endif

VOS_VOID TAF_SPM_GetCallInfoFromFsmEntryMsg(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    MN_CALL_TYPE_ENUM_U8               *penCallType,
    MN_CALL_MODE_ENUM_U8               *penCallMode,
    MN_CALL_CS_DATA_CFG_STRU           *pstDataCfg
);


VOS_UINT32 TAF_SPM_IsNeedCheckFdn(VOS_VOID);

VOS_UINT32 TAF_SPM_IsNeedCallControl(VOS_VOID);

VOS_UINT32 TAF_SPM_IsUESupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_SPM_ProcSmsRptEvent(TAF_SPM_MSG_REPORT_IND_STRU  *pstMsgReportInd);

VOS_VOID TAF_SPM_SendAtEconfDialCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_SPM_SendAtGetEconfCallInfoCnf(
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU   *pstImsaMsg
);

VOS_VOID TAF_SPM_ParseEconfDailInfoFromMsg(
    struct MsgCB                       *pstAppMsg
);

VOS_VOID TAF_SPM_SendEconfNotifyInd(
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucNumOfCalls,
    TAF_CALL_ECONF_INFO_PARAM_STRU     *pstCallInfo
);

VOS_VOID TAF_SPM_ReportEconfCheckRslt(VOS_VOID);

VOS_VOID TAF_SPM_RecordEconfCheckRslt(
    VOS_UINT32                          ulIndex,
    VOS_UINT32                          ulResult
);

VOS_VOID TAF_SPM_SetEconfPreRslt(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_UINT32 TAF_SPM_ProcEconfCheckResult(VOS_VOID);


#endif

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SPM_ReadEcallNumber(
    VOS_UINT8                           ucFdnRecordNum,
    VOS_UINT8                           ucSdnRecordNum
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_SPM_IsImsCallTypeEmgencyCall(VOS_VOID);

VOS_VOID TAF_SPM_SndImsRelAllCall(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId
);
#endif

#endif

VOS_UINT32  TAF_SPM_IsEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);
VOS_UINT32  TAF_SPM_IsUsimEmergencyNum_CDMA(
    MN_CALL_CALLED_NUM_STRU            *pstDialNum,
    VOS_UINT32                         *pulEmcCatExist,
    VOS_UINT8                          *pucEmerCategory
);



/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
VOS_UINT32 TAF_SPM_GetRfAvailInfo(
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType,
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */

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

#endif /* end of TafSpmComFunc.h */

