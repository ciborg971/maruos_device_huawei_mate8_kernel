

#ifndef __IMSAREGMANAGEMENT_H__
#define __IMSAREGMANAGEMENT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_REG_FAILURE_RETRY_INTERVEL_5_MIN   (5*60)

#define IMSA_REG_GetRegCntxt()          (&pgstImsaEntity->stImsaRegManager)
#define IMSA_REG_GetNormalRegEntity()   (&pgstImsaEntity->stImsaRegManager.stNormalRegEntity)
#define IMSA_REG_GetEmcRegEntity()      (&pgstImsaEntity->stImsaRegManager.stEmcRegEntity)

#ifdef PS_ITT_PC_TEST_NAS
#define IMSA_REG_TIMER_LEN_PROTECT              (8*1000)
#define IMSA_REG_TIMER_LEN_RETRY                (6*1000)
#define IMSA_REG_TIMER_LEN_PERIOD_TRY_REG       (60*1000)
#else
#define IMSA_REG_TIMER_LEN_PROTECT              (30*1000)
#define IMSA_REG_TIMER_LEN_RETRY                (5*60*1000)
#define IMSA_REG_TIMER_LEN_PERIOD_TRY_REG       (60*1000)
#endif
#define IMSA_PRIOD_TRY_REG_MAX_TIMES            (5)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    ö����    : IMSA_REG_EVT_ENUM
    ö��˵��  : ���ⲿ���ú��²�֪ͨ���/�¼�ͳһ��ַΪ�¼��������ڲ�״̬���Ĵ���
*****************************************************************************/
enum IMSA_REG_EVT_ENUM
{
    IMSA_REG_EVT_USER_REG_REQ,
    IMSA_REG_EVT_USER_DEREG_REQ,

    IMSA_REG_EVT_IMS_REG_SUCCESS,
    IMSA_REG_EVT_IMS_REG_FAILURE,

    IMSA_REG_EVT_TIMEOUT_PROTECT,
    IMSA_REG_EVT_TIMEOUT_RETRY,
    IMSA_REG_EVT_TIMEOUT_PERIOD_TRY,
    IMSA_REG_EVT_BUTT
};
typedef VOS_UINT32 IMSA_REG_EVT_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : IMSA_FSM_PROC
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ע��״̬��������ԭ�Ͷ���
*****************************************************************************/
typedef VOS_UINT32 (*IMSA_FSM_PROC)(IMSA_REG_ENTITY_STRU *pstEntity, VOS_UINT32 ulEvt, VOS_VOID* pData);


/*****************************************************************************
 �ṹ��    : IMSA_REG_FSM_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ״̬��������ṹ�嶨��
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulState;
    VOS_UINT32 ulEvent;
    IMSA_FSM_PROC ProcFun;
} IMSA_REG_FSM_ITEM_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/**
 * Declaration for global entity context
 */
extern IMSA_ENTITY_STRU *pgstImsaEntity;
/*extern HICSM_ImsError g_ImsErrorInfo;*/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
#define IMSA_RegCtxGet()    (&pgstImsaEntity->stImsaRegManager)
#define IMSA_CtxGet()       (pgstImsaEntity)

extern VOS_VOID   IMSA_RegMgrInit(VOS_VOID);
extern VOS_VOID   IMSA_RegMgrDeinit(VOS_VOID);

extern VOS_VOID IMSA_RegEntityInit(IMSA_REG_ENTITY_STRU *pstRegEntity);
extern IMSA_REG_ENTITY_STRU* IMSA_RegEntityGetByType(IMSA_REG_TYPE_ENUM_UINT8 enRegType);

extern VOS_UINT32 IMSA_RegProcUserRegReqMsg(const VOS_VOID *pRcvMsg);
extern VOS_UINT32 IMSA_RegProcUserDeregReqMsg(const VOS_VOID *pRcvMsg);

extern VOS_VOID IMSA_RegProcTimeoutProtect(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_RegProcTimeoutRetry(const VOS_VOID *pTimerMsg);
extern VOS_VOID IMSA_RegProcTimeoutPeriodTry(const VOS_VOID *pTimerMsg);
extern VOS_UINT32 IMSA_RegSendIntraMsg(VOS_UINT32 ulMsgId, const VOS_UINT8 *pucMsg, VOS_UINT32 ulLen);
extern VOS_VOID IMSA_RegEntityDeinit(IMSA_REG_ENTITY_STRU *pstRegEntity);
extern VOS_VOID IMSA_RegPrintEmcRegState( VOS_VOID );
extern VOS_VOID IMSA_RegPrintNrmRegState( VOS_VOID );
extern VOS_VOID IMSA_SndD2MsgServiceRegInfo(IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason);
extern VOS_VOID IMSA_RegSaveRegedPara
(
    IMSA_REG_TYPE_ENUM_UINT8            ulRegType,
    VOS_UINT8                           ucCid,
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType
);

extern VOS_VOID IMSA_RegProcNwNotifyMsgByEvent
(
    IMSA_REG_ENTITY_STRU               *pstEntity,
    VOS_VOID                           *pData
);

#if (FEATURE_ON == FEATURE_PTM)
extern VOS_VOID IMSA_SndRegErrLogInfo
(
    IMSA_ERR_LOG_REG_FAIL_STRU  stImsRegRstEvent
);
extern VOS_VOID IMSA_NormRegFailErrRecord
(
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8 enRegFailReason,
    VOS_UINT16                              usSipStatusCode,
    VOS_UINT32                              ulRetryTimerLen
);

extern VOS_VOID IMSA_RegFailErrLogRecord
(
    IMSA_REG_TYPE_ENUM_UINT8                        enRegType,
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enNormRegFailReason,
    VOS_UINT16                                      usSipStatusCode,
    VOS_UINT32                                      ulRetryTimerLen,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
);
extern VOS_VOID IMSA_PdnConnFailErrLogRecord
(
    IMSA_CONN_TYPE_ENUM_UINT32                      enConnType,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enEmcRegFailReason
);
#endif
/* lihong00150010 lte pclint 717 begin */
#define IMSA_RegTimerStart(timer, para)   \
{                               \
    (timer)->usPara = (para);   \
    IMSA_StartTimer(timer);     \
}


#define IMSA_RegTimerStop(timer)          \
{                               \
    IMSA_StopTimer(timer);      \
}

#define IMSA_RegTimerRefresh(timer, para) \
{                               \
    if (IMSA_IsTimerRunning(timer)) \
    {                           \
        IMSA_StopTimer(timer);  \
    }                           \
    (timer)->usPara = (para);   \
    IMSA_StartTimer(timer);     \
}

#define IMSA_REG_FSM_STATE_TRANS(pstEntity, state)      \
{                                                       \
    if (IMSA_REG_TYPE_NORMAL == (pstEntity)->enRegType) \
    {                                                   \
        IMSA_INFO_LOG2("Normal REG entity state changed: ", (pstEntity)->enStatus, (state));    \
    }                                                   \
    else                                                \
    {                                                   \
        IMSA_INFO_LOG2("Emergency REG entity state changed: ", (pstEntity)->enStatus, (state)); \
    }                                                   \
                                                        \
    ((pstEntity)->enStatus = (state));                  \
}
/* lihong00150010 lte pclint 717 end */

/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaRegManagement.h */




