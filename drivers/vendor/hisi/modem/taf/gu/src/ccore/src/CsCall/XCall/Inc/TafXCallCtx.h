

#ifndef __TAF_X_CALL_CTX_H__
#define __TAF_X_CALL_CTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "xcc_xcall_pif.h"
#include "TafCsCallCommDef.h"
#include "hi_list.h"
#include "TafXCallTimerMgmt.h"
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
#include "AtMnInterface.h"
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* call id 从1开始 */

/* 1X CALL 最大呼叫个数 */
#define TAF_XCALL_CALL_ENTITY_MAX_NUM                       (2)

#define TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM                    (10)                /* 补充业务操作管理结构 */

#define TAF_XCALL_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define TAF_XCALL_MAX(x, y)\
        (((x)>(y))?(x):(y))


#define TAF_XCALL_MAX_TIMER_ID_NUM                          (10)            /* XCALL的定时器最大个数 */
#define TAF_XCALL_INVAILD_CALL_ID                           (0)

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/* Added by y00307564 for 1X SS Project, 2014-11-12, begin */
#define TAF_XCALL_DTMF_BUF_MAX_CNT               (32)                            /* 最多缓存DTMF信息的个数 */
/* Added by y00307564 for 1X SS Project, 2014-11-12, begin */
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_XCALL_SO_TYPE_ENUM
 结构说明  : XCALL维护的SO
*****************************************************************************/
enum TAF_XCALL_SO_TYPE_ENUM
{
    TAF_XCALL_SO_3_EVRC                 = 0x0003,
    TAF_XCALL_SO_68_EVRC_B              = 0x0044,
    TAF_XCALL_SO_73_EVRC_NW             = 0x0049,

    TAF_XCALL_SO_BUTT                   = 0xFFFF
};
typedef VOS_UINT16 TAF_XCALL_SO_TYPE_ENUM_UINT16;

/*****************************************************************************
 枚举名    : TAF_XCALL_CALL_SUB_STATE_ENUM
 结构说明  : 补充业务进展事件
*****************************************************************************/
enum TAF_XCALL_SS_PROGRESS_EVT_ENUM
{
    TAF_XCALL_SS_PROG_EVT_REL,                                                  /* 有呼叫被挂断 */

    TAF_XCALL_SS_PROG_EVT_ANS,                                                  /* 有呼叫在接听*/

    TAF_XCALL_SS_PROG_EVT_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8;

/*****************************************************************************
 枚举名    : TAF_XCALL_CALL_SUB_STATE_ENUM
 结构说明  : 补充业务后续操作
*****************************************************************************/
enum TAF_XCALL_SS_SUBSEQ_OP_ENUM
{
    TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC,                                            /* 向应用层上报操作成功 */
    TAF_XCALL_SS_SUBSEQ_OP_RPT_FAIL,                                            /* 向应用层上报操作失败 */

    TAF_XCALL_SS_SUBSEQ_OP_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8;

/** ****************************************************************************
 枚举名    : TAF_XCALL_DIGIT_MODE_ENUM
 结构说明  : 号码编码模式
 *******************************************************************************/
enum TAF_XCALL_DIGIT_MODE_ENUM
{
    TAF_XCALL_DIGIT_MODE_DTMF           = 0x00,
    TAF_XCALL_DIGIT_MODE_ASCII          = 0x01,
    TAF_XCALL_DIGIT_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 TAF_XCALL_DIGIT_MODE_ENUM_UINT8;

/** ****************************************************************************
 枚举名    : TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8
 结构说明  : 向xcc发送Burst DTMF或CONT DTMF后，设置等待标志，等待响应的类型
 *******************************************************************************/
enum TAF_XCALL_WAIT_XCC_CNF_TYPE
{
    TAF_XCALL_WAIT_NO_XCC_CNF               = 0x00,     /* 初始态，不等待XCC回复 */
    TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF       = 0x01,     /* 等待XCC回复BURST DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF  = 0x02,     /* 等待XCC回复START CONT DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF   = 0x03,     /* 等待XCC回复STOP CONT DTMF REQ的响应 */
    TAF_XCALL_WAIT_XCC_CNF_BUFF
};
typedef VOS_UINT8 TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8;


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

typedef struct
{
    VOS_UINT32                          ulModuleId;                             /* 发起呼叫操作的模块AT/STK */
    VOS_UINT16                          usClientId;                             /* Client ID */
    VOS_UINT8                           ucOpId;                                 /* Op ID */
    VOS_UINT8                           ucReserved;
}TAF_XCALL_CLIENT_INFO_STRU;

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/*****************************************************************************
结构名    : TAF_XCALL_DTMF_BUFFER_STRU
结构说明  : XCALL模块用于保存BURST DTMF和CONT DTMF信息
  1.日    期   : 2014年11月10日
    作    者   : f279542
    修改内容   : 新生成
  2.日    期   : 2015年7月29日
    作    者   : l00324781
    修改内容   : Iter16 修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDtmfCnt;          /* 缓存的BURST DTMF和CONT DTMF消息数量 */
    VOS_UINT8                           aucReserved1[3];
    HI_LIST_S                           stList;
} TAF_XCALL_DTMF_BUFFER_STRU;

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */



typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* 是否已被使用 */
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;                           /* 发起/接听用户的信息 */

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo;
    VOS_UINT8                           ucIsAlertAnsByPass;                     /* MT */
    VOS_UINT8                           ucConRef;                               /* Connect Reference */
    VOS_UINT8                           ucConnectId;                            /* Connect Id */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* 发起呼叫的方向 */
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucIsL2ErrReOrig;
    VOS_UINT8                           ucReOrigCount;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */

    MN_CALL_DISC_DIR                    stDiscDir;                              /* 挂断呼叫的方向 */

    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number 主叫号码 */
    MN_CALL_SUBADDR_STRU                stCallSubNumber;                        /* Call SubAddress */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number 被叫号码 */
    MN_CALL_SUBADDR_STRU                stCalledSubAddr;                        /* Called SubAddress */
    MN_CALL_BCD_NUM_STRU                stRedirectNumber;                       /* Redirect Number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Redirect Call SubAddress */
    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;                /* 等待XCC的Burst DTMF或Cont Burst回复消息 */
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;
    VOS_UINT8                           aucRsved[2];

    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    TAF_XCALL_DTMF_BUFFER_STRU          stDtmfBuffer;                           /* BURST DTMF和CONT DTMF的缓存信息,公用一个缓存*/
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

    TAF_XCALL_CLIENT_INFO_STRU          stFlashClientInfo;                      /* 发送flash用户的信息 */
}TAF_XCALL_CALL_ENTITY_STRU;


typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;
}TAF_XCALL_CS_ERR_CODE_MAP_STRU;



typedef struct
{
    VOS_UINT8                                               ucCallId;           /* 产生事件的呼叫ID */
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;              /* 事件的类型 */
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;         /* 收到该事件的后续操作 */
    VOS_UINT8                                               ucRsved;
}TAF_XCALL_SUPS_CMD_KEY_EVT_STRU;
typedef struct
{
    VOS_UINT8                               ucNumOfKeyEvt;                      /* 关注的事件个数 */
    VOS_UINT8                               aucRsved[3];
    TAF_XCALL_SUPS_CMD_KEY_EVT_STRU         astKeyEvts[TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM];  /* 关注的事件 */
}TAF_XCALL_SUPS_CMD_MGMT_STRU;


typedef struct
{
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode;

    VOS_UINT8                           ucRsved;
    
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSoInitType;

    /* Added by h00313353 for Iteration 17, 2015-7-7, begin */
    VOS_UINT32                          ulEmcRedialPeriod;      /* 紧急呼重播定时器时长 */
    /* Added by h00313353 for Iteration 17, 2015-7-7, end */
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* Stop Cont DTMF和Start Cont DTMF命令发送时间间隔定时器时长，单位:ms */
}TAF_XCALL_CONFIG_STRU;



typedef struct
{
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
    TAF_XCALL_CONFIG_STRU               stConfig;
    TAF_XCALL_TIMER_CTX_STRU            astTimerCtx[TAF_XCALL_MAX_TIMER_ID_NUM];
}TAF_XCALL_CTX_STRU;


/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/*****************************************************************************
结构名    : TAF_XCALL_DTMF_NODE_UNION
结构说明  : CALL模块DTMF缓存消息内容结构，缓存Cont DTMF和Burst DTMF
1.日    期   : 2015年7月29日
  作    者   : l00324781
  修改内容   : Iter16新增

*****************************************************************************/
typedef union
{
    TAF_CALL_BURST_DTMF_PARA_STRU   stBurstDtmf;
    TAF_CALL_CONT_DTMF_PARA_STRU    stContDtmf;
}TAF_XCALL_DTMF_NODE_UNION;

/*****************************************************************************
结构名    : TAF_XCALL_DTMF_NODE_STRU
结构说明  : CALL模块DTMF缓存链表节点结构，缓存Cont DTMF和Burst DTMF
1.日    期   : 2015年7月29日
  作    者   : l00324781
  修改内容   : Iter16新增

*****************************************************************************/
typedef struct
{
    TAF_XCALL_DTMF_NODE_UNION                    unDtmf;        /* 缓存Buffer,Burst DTMF或CONT DTMF */
    AT_MN_MSGTYPE_ENUM_UINT16                    enMsgType;     /* 缓存的消息类型 */
    VOS_UINT8                                    aucRsved[2];
    HI_LIST_S                                    stList;
} TAF_XCALL_DTMF_NODE_STRU;

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_XCALL_CTX_STRU* TAF_XCALL_GetCtxAddr(VOS_VOID);

VOS_VOID TAF_XCALL_InitCtx(VOS_VOID);

VOS_UINT32 TAF_XCALL_AllocCallId(
    VOS_UINT8                      *pucCallId
);

VOS_UINT32 TAF_XCALL_IsAllowMoCallInCurrentStatus(
    MN_CALL_TYPE_ENUM_U8                enCallType
);


VOS_VOID TAF_XCALL_CreateMoCallEntity(
    VOS_UINT8                           ucCallId,
    MN_CALL_APP_REQ_MSG_STRU           *pstOrigPara
);

VOS_VOID TAF_XCALL_CreateMtCallEntity(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd
);

VOS_VOID TAF_XCALL_FreeCallEntity(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailCallId(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_IsAvailVoiceCallSo(
    VOS_UINT16                          usSo
);

VOS_VOID TAF_XCALL_UpdateCallState(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_XCALL_UpdateCallType(
    VOS_UINT8                           ucCallId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

VOS_VOID TAF_XCALL_UpdateCallDir(
    VOS_UINT8                           ucCallId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

VOS_VOID TAF_XCALL_UpdateSo(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo
);

VOS_VOID TAF_XCALL_UpdateConnectId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_XCALL_UpdateConnectRef(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConRef
);

VOS_VOID TAF_XCALL_UpdateAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsAlertAnsByPass
);

VOS_VOID TAF_XCALL_UpdateCcCause(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCcCause
);

VOS_VOID TAF_XCALL_UpdateDiscCallDir(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID TAF_XCALL_UpdateCallingNum(
    VOS_UINT8                                               ucCallId,
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU                  *pstXccCallNum
);

TAF_XCALL_SUPS_CMD_MGMT_STRU* TAF_XCALL_GetSupsCmdMgmt(VOS_VOID);

TAF_XCALL_CLIENT_INFO_STRU* TAF_XCALL_GetClientInfo(
    VOS_UINT8                           ucCallId
);

TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_GetSo(
    VOS_UINT8                           ucCallId
);

MN_CALL_STATE_ENUM_U8 TAF_XCALL_GetCallState(
    VOS_UINT8                           ucCallId
);

MN_CALL_TYPE_ENUM_U8 TAF_XCALL_GetCallType(
    VOS_UINT8                           ucCallId
);

VOS_UINT8 TAF_XCALL_GetAlertAnsByPassFlg(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_GetCcCause(
    VOS_UINT8                           ucCallId
);

VOS_UINT32 TAF_XCALL_GetCallIdFromConnectId(
    VOS_UINT8                           ucConnectId,
    VOS_UINT8                          *pucCallId
);

VOS_VOID TAF_XCALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_GetNotIdleStateCalls(
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT8                          *pucCallIds
);

VOS_VOID TAF_XCALL_UpdateClientInfo(
    VOS_UINT8                           ucCallId,
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

TAF_XCALL_CALL_ENTITY_STRU* TAF_XCALL_GetCallEntityAddr(
    VOS_UINT8                           ucCallId
);

TAF_CS_CAUSE_ENUM_UINT32 TAF_XCALL_MapXccCauseToCsCause(
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause
);

VOS_UINT32 TAF_XCALL_ExistCallInstance(VOS_VOID);

VOS_VOID TAF_XCALL_RegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp
);

VOS_VOID TAF_XCALL_DeRegSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt
);


VOS_VOID TAF_XCALL_GetSsKeyEvent(
    VOS_UINT8                                               ucCallId,
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                   *penEvt,
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                      *penSubseqOp
);

VOS_VOID TAF_XCALL_UpdateDigitMode(
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode
);

TAF_XCALL_CONFIG_STRU* TAF_XCALL_GetConfigInfo(VOS_VOID);

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
VOS_VOID TAF_XCALL_SetWaitForXCCDTMFCnfFlag(
    VOS_UINT8                           ucCallId,
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag
);

TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8 TAF_XCALL_GetWaitForXCCDTMFCnfFlag(
    VOS_UINT8       ucCallId
);
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

VOS_UINT32 TAF_XCALL_IsMtCallInstanceExist(VOS_VOID);

TAF_XCALL_TIMER_CTX_STRU*  TAF_XCALL_GetTimerCtxAddr( VOS_VOID );

MN_CALL_DIR_ENUM_U8 TAF_XCALL_GetCallDir(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_TranlatePlusToCallNum(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);

#if 0
VOS_VOID TAF_XCALL_TranlateCallNumToPlus(
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity
);
#endif


VOS_VOID TAF_XCALL_GetEccNumList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
);

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, begin */
/*  修改内容:
   1. Buffer操作函数从XCallProcApp挪到XCallCtx.c中
   2. Cont DTMF和Burst DTMF公用一个缓存
*/

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, begin */
extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveBurstDtmfInfo(
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU   *pstBurstDtmfInfo
);

extern VOS_VOID TAF_XCALL_ProcDtmfBuffer(VOS_UINT8 ucCallId);

extern VOS_VOID TAF_XCALL_CleanDtmfBuff(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DelDtmfNode(
    TAF_XCALL_DTMF_NODE_STRU     *pstNode,
    VOS_UINT8                     ucCallId
);

extern HI_LIST_S* TAF_XCALL_GetDtmfBuffListHead(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_IncrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_VOID TAF_XCALL_DecrementDtmfBufCnt(VOS_UINT8   ucCallId);

extern VOS_UINT8 TAF_XCALL_GetDtmfBufCnt(VOS_UINT8   ucCallId);


/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, end */

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-29, end */

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */

TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_AddContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);

TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SaveContDtmfInfo(
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU    *pstContDtmfInfo
);

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

VOS_UINT32 TAF_XCALL_GetStartAndStopContDtmfIntervalLen(VOS_VOID);
#endif



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

#endif /* end of TafXCallCtx.h */


