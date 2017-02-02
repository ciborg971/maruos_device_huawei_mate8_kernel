
#ifndef _NAS_CC_CTX_H_
#define _NAS_CC_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "PsTypeDef.h"
#include "NasCcCommon.h"
#include "NasCcIe.h"
#include "NasCcAirMsg.h"

#include "omringbuffer.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#include "NasMntn.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_CC_ONE_THOUSAND_MILLISECOND                    (1000)              /* 1000MS */
#define NAS_CC_MAX_MSG_QUEUE_NUM                           (8)                  /* ��󻺴�ĸ��� */
#define NAS_CC_MAX_MSG_BUFFER_LEN                          (720)                /* �������󳤶� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum NAS_CC_SS_SWITCH_STATE_ENUM
{
    NAS_CC_SS_SWITCH_IDLE               = 0,                                    /* ��ǰû�в���ҵ��״̬�л� */
    NAS_CC_SS_SWITCH_WAIT_CNF,                                                  /* �����л����󣬵ȴ�����Ļظ� */
    NAS_CC_SS_SWITCH_SUCCESS,                                                   /* �����ѻظ�ACK��Ϣ */
    NAS_CC_SS_SWITCH_FAILED,                                                    /* ����ظ�REJ��ERR */
    NAS_CC_SS_SWITCH_TIME_OUT,                                                  /* ����δ�ظ����³�ʱ */

    NAS_CC_SS_SWITCH_LAST_CALL_RELEASED,

    NAS_CC_SS_SWITCH_STATE_BUTT
};
typedef VOS_UINT8 NAS_CC_SS_SWITCH_STATE_ENUM_UINT8;



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
    VOS_UINT8                           ucCcbsSupportFlg;                       /*CCBS(��æ�������)ҵ��*/
    VOS_UINT8                           ucProceedingStartT310Flag;
    VOS_UINT8                           aucReserved[2];
}NAS_CC_CUSTOM_CFG_INFO_STRU;
typedef struct
{
    NAS_CC_CUSTOM_CFG_INFO_STRU        stCustomCfg;                             /* NVIM�еĶ�����Ϣ */
}NAS_CC_MS_CFG_INFO_STRU;
typedef struct
{
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;                            /* ���б���ҵ���л�״̬ */
    VOS_UINT8                           aucReserved1[3];
    NAS_CC_CAUSE_VALUE_ENUM_U32         enHoldCause;                            /* ���б���ҵ���л�״̬ԭ��ֵ */
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrieveState;                        /* ���лָ�ҵ���л�״̬ */
    VOS_UINT8                           aucReserved2[3];
    NAS_CC_CAUSE_VALUE_ENUM_U32         enRetrieveCause;                        /* ���лָ�ҵ���л�״̬ԭ��ֵ */
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;                         /* ���б���ҵ��ʵ��ID */
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;                     /* ���лָ�ҵ��ʵ��ID */
    VOS_UINT8                           ucOpFacility;                           /* �Ƿ񱣴��������·���FACILITY��Ϣ */
    VOS_UINT8                           ucOpInvokeId;                           /* �Ƿ񱣴���InvokeId */
    VOS_UINT8                           ucInvokeId;                             /* ��¼InvokeId */
    VOS_UINT8                           aucReserved3[1];
    NAS_CC_MSG_FACILITY_MT_STRU         stFacility;                             /* ��¼�����·���FACILITY��Ϣ */
}NAS_CC_SS_SWITCH_INFO_STRU;


typedef struct
{
    NAS_CC_SS_SWITCH_INFO_STRU          stSwitchInfo;                           /* ͨ������ҵ��״̬�л���Ϣ */
} NAS_CC_SS_CONTROL_STRU;
typedef struct
{
    VOS_UINT8                           ucErrLogCtrlFlag;                       /* ERRLOG�򿪱�ʶ */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usAlmLevel;                             /* ���ϸ澯���� */
}NAS_CC_ERRLOG_CTRL_INFO_STRU;


typedef struct
{
    OM_RING_ID                          pstRingBuffer;                          /* MM��Ĺ����� */
    VOS_UINT32                          ulOverflowCnt;                          /* Ringbuf����Ĵ��� */
}NAS_CC_ERRLOG_BUFF_INFO_STRU;



typedef struct
{
    NAS_CC_ERRLOG_CTRL_INFO_STRU        stCtrlInfo;
    NAS_CC_ERRLOG_BUFF_INFO_STRU        stBuffInfo;
}NAS_CC_ERRLOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_CC_ENTRY_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ҫ����������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[NAS_CC_MAX_MSG_BUFFER_LEN];
} NAS_CC_ENTRY_MSG_STRU;


typedef struct
{
    NAS_CC_ENTRY_MSG_STRU               stMsgEntry;     /* ����ľ������� */
}NAS_CC_CACHE_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* ������Ϣ�ĸ��� */
    VOS_UINT8                           aucReserve[3];
    NAS_CC_CACHE_MSG_INFO_STRU          astMsgQueue[NAS_CC_MAX_MSG_QUEUE_NUM]; /* CC����Ϣ�������飬�洢���Ǵ�ͨ����Ϣͷ����Ϣ */
} NAS_CC_MSG_QUEUE_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    NAS_CC_MSG_QUEUE_STRU               stMsgQueue;
} NAS_CC_LOG_BUFFER_MSG_INFO_STRU;
typedef struct
{
    NAS_CC_MS_CFG_INFO_STRU             stMsCfgInfo;                            /* MS��������Ϣ */
    NAS_CC_SS_CONTROL_STRU              stSsControl;                            /* CC����ҵ�������Ϣ */

    NAS_CC_ERRLOG_INFO_STRU             stErrlogInfo;
    NAS_CC_MSG_QUEUE_STRU               stBufferEntryMsgQueue;

} NAS_CC_CONTEXT_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
NAS_CC_CUSTOM_CFG_INFO_STRU* NAS_CC_GetCustomCfgInfo( VOS_VOID );

NAS_CC_SS_SWITCH_STATE_ENUM_UINT8 NAS_CC_GetSsSwitchHoldState(VOS_VOID);

NAS_CC_SS_SWITCH_STATE_ENUM_UINT8 NAS_CC_GetSsSwitchRetrieveState(VOS_VOID);

NAS_CC_ENTITY_ID_T NAS_CC_GetSsSwitchHoldEntityID(VOS_VOID);

NAS_CC_ENTITY_ID_T NAS_CC_GetSsSwitchRetrieveEntityID(VOS_VOID);

NAS_CC_CAUSE_VALUE_ENUM_U32 NAS_CC_GetSsSwitchHoldCause(VOS_VOID);

NAS_CC_CAUSE_VALUE_ENUM_U32 NAS_CC_GetSsSwitchRetrieveCause(VOS_VOID);

VOS_VOID NAS_CC_SetSsSwitchHoldInfo(
    NAS_CC_ENTITY_ID_T                  ulEntityID,
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enState,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);

VOS_VOID NAS_CC_SetSsSwitchRetrieveInfo(
    NAS_CC_ENTITY_ID_T                  ulEntityID,
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enState,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);

VOS_UINT8 NAS_CC_GetSsSwitchOpFacility(VOS_VOID);

VOS_VOID NAS_CC_SetSsSwitchOpFacility(
    VOS_UINT32                          ulOpFlg,
    NAS_CC_MSG_FACILITY_MT_STRU        *pstFacilityMsg
);

NAS_CC_MSG_FACILITY_MT_STRU* NAS_CC_GetSsSwitchFacility(VOS_VOID);

VOS_VOID NAS_CC_SetSsSwitchInvokeId(
    VOS_UINT8                           ucFlg,
    VOS_UINT8                           ucInvokeId);

VOS_UINT8 NAS_CC_GetSsSwitchOpInvokeId(VOS_VOID);

VOS_UINT8 NAS_CC_GetSsSwitchInvokeId(VOS_VOID);

VOS_VOID NAS_CC_InitSsSwitchInfo(VOS_VOID);

NAS_CC_MSG_QUEUE_STRU* NAS_CC_GetCachMsgBufferAddr(VOS_VOID);

VOS_VOID  NAS_CC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_CC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_CC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID  NAS_CC_ClearSpecEventTypeCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID NAS_CC_ClearAllCacheMsg(VOS_VOID);

VOS_UINT32  NAS_CC_GetNextSpecEventTypeCachedMsg(
    VOS_UINT32                          ulEventType,
    NAS_CC_ENTRY_MSG_STRU              *pstEntryMsg
);

VOS_VOID NAS_CC_SetSsSwitchHoldEntityID(NAS_CC_ENTITY_ID_T ulEntityID);

VOS_VOID NAS_CC_SetSsSwitchRetrieveEntityID(NAS_CC_ENTITY_ID_T ulEntityID);


#if (FEATURE_ON == FEATURE_PTM)
OM_RING_ID NAS_CC_GetErrLogRingBufAddr(VOS_VOID);
VOS_VOID NAS_CC_SetErrLogRingBufAddr(OM_RING_ID pRingBuffer);
VOS_UINT8 NAS_CC_GetErrlogCtrlFlag(VOS_VOID);
VOS_VOID NAS_CC_SetErrlogCtrlFlag(VOS_UINT8 ucFlag);
VOS_UINT16 NAS_CC_GetErrlogAlmLevel(VOS_VOID);
VOS_VOID NAS_CC_SetErrlogAlmLevel(VOS_UINT16 usAlmLevel);
VOS_UINT32 NAS_CC_GetErrlogOverflowCnt(VOS_VOID);
VOS_VOID NAS_CC_SetErrlogOverflowCnt(VOS_UINT32 ulOverflowCnt);
VOS_VOID NAS_CC_InitErrLogInfo(VOS_VOID);
VOS_UINT32 NAS_CC_PutErrLogRingBuf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 NAS_CC_GetErrLogRingBufContent(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
VOS_UINT32 NAS_CC_GetErrLogRingBufferUseBytes(VOS_VOID);
VOS_VOID NAS_CC_CleanErrLogRingBuf(VOS_VOID);
#endif

VOS_VOID NAS_CC_SetProceedingStartT310Flag(VOS_UINT8 ucFlag);

VOS_UINT8 NAS_CC_GetProceedingStartT310Flag(VOS_VOID);




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

#endif /* end of MnCallCtx.h */

