

#ifndef __TAF_X_CALL_CTX_H__
#define __TAF_X_CALL_CTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
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
  2 �궨��
*****************************************************************************/
/* call id ��1��ʼ */

/* 1X CALL �����и��� */
#define TAF_XCALL_CALL_ENTITY_MAX_NUM                       (2)

#define TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM                    (10)                /* ����ҵ���������ṹ */

#define TAF_XCALL_MIN(x, y)\
        (((x)<(y))?(x):(y))

#define TAF_XCALL_MAX(x, y)\
        (((x)>(y))?(x):(y))


#define TAF_XCALL_MAX_TIMER_ID_NUM                          (10)            /* XCALL�Ķ�ʱ�������� */
#define TAF_XCALL_INVAILD_CALL_ID                           (0)

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/* Added by y00307564 for 1X SS Project, 2014-11-12, begin */
#define TAF_XCALL_DTMF_BUF_MAX_CNT               (32)                            /* ��໺��DTMF��Ϣ�ĸ��� */
/* Added by y00307564 for 1X SS Project, 2014-11-12, begin */
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XCALL_SO_TYPE_ENUM
 �ṹ˵��  : XCALLά����SO
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
 ö����    : TAF_XCALL_CALL_SUB_STATE_ENUM
 �ṹ˵��  : ����ҵ���չ�¼�
*****************************************************************************/
enum TAF_XCALL_SS_PROGRESS_EVT_ENUM
{
    TAF_XCALL_SS_PROG_EVT_REL,                                                  /* �к��б��Ҷ� */

    TAF_XCALL_SS_PROG_EVT_ANS,                                                  /* �к����ڽ���*/

    TAF_XCALL_SS_PROG_EVT_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XCALL_CALL_SUB_STATE_ENUM
 �ṹ˵��  : ����ҵ���������
*****************************************************************************/
enum TAF_XCALL_SS_SUBSEQ_OP_ENUM
{
    TAF_XCALL_SS_SUBSEQ_OP_RPT_SUCC,                                            /* ��Ӧ�ò��ϱ������ɹ� */
    TAF_XCALL_SS_SUBSEQ_OP_RPT_FAIL,                                            /* ��Ӧ�ò��ϱ�����ʧ�� */

    TAF_XCALL_SS_SUBSEQ_OP_BUTT
};

typedef VOS_UINT8 TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8;

/** ****************************************************************************
 ö����    : TAF_XCALL_DIGIT_MODE_ENUM
 �ṹ˵��  : �������ģʽ
 *******************************************************************************/
enum TAF_XCALL_DIGIT_MODE_ENUM
{
    TAF_XCALL_DIGIT_MODE_DTMF           = 0x00,
    TAF_XCALL_DIGIT_MODE_ASCII          = 0x01,
    TAF_XCALL_DIGIT_MODE_BUTT           = 0x02
};
typedef VOS_UINT8 TAF_XCALL_DIGIT_MODE_ENUM_UINT8;

/** ****************************************************************************
 ö����    : TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8
 �ṹ˵��  : ��xcc����Burst DTMF��CONT DTMF�����õȴ���־���ȴ���Ӧ������
 *******************************************************************************/
enum TAF_XCALL_WAIT_XCC_CNF_TYPE
{
    TAF_XCALL_WAIT_NO_XCC_CNF               = 0x00,     /* ��ʼ̬�����ȴ�XCC�ظ� */
    TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF       = 0x01,     /* �ȴ�XCC�ظ�BURST DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF  = 0x02,     /* �ȴ�XCC�ظ�START CONT DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_STOP_CONT_DTMF   = 0x03,     /* �ȴ�XCC�ظ�STOP CONT DTMF REQ����Ӧ */
    TAF_XCALL_WAIT_XCC_CNF_BUFF
};
typedef VOS_UINT8 TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8;


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
    VOS_UINT32                          ulModuleId;                             /* ������в�����ģ��AT/STK */
    VOS_UINT16                          usClientId;                             /* Client ID */
    VOS_UINT8                           ucOpId;                                 /* Op ID */
    VOS_UINT8                           ucReserved;
}TAF_XCALL_CLIENT_INFO_STRU;

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
/*****************************************************************************
�ṹ��    : TAF_XCALL_DTMF_BUFFER_STRU
�ṹ˵��  : XCALLģ�����ڱ���BURST DTMF��CONT DTMF��Ϣ
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : ������
  2.��    ��   : 2015��7��29��
    ��    ��   : l00324781
    �޸�����   : Iter16 �޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDtmfCnt;          /* �����BURST DTMF��CONT DTMF��Ϣ���� */
    VOS_UINT8                           aucReserved1[3];
    HI_LIST_S                           stList;
} TAF_XCALL_DTMF_BUFFER_STRU;

/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */



typedef struct
{
    VOS_UINT32                          ulUsed;                                 /* �Ƿ��ѱ�ʹ�� */
    TAF_XCALL_CLIENT_INFO_STRU          stClientInfo;                           /* ����/�����û�����Ϣ */

    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSo;
    VOS_UINT8                           ucIsAlertAnsByPass;                     /* MT */
    VOS_UINT8                           ucConRef;                               /* Connect Reference */
    VOS_UINT8                           ucConnectId;                            /* Connect Id */
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* Call State */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* Call Type */
    MN_CALL_DIR_ENUM_U8                 enCallDir;                              /* ������еķ��� */
    VOS_UINT8                           ucPi;
    VOS_UINT8                           ucSi;
    VOS_UINT8                           ucIsL2ErrReOrig;
    VOS_UINT8                           ucReOrigCount;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */

    MN_CALL_DISC_DIR                    stDiscDir;                              /* �ҶϺ��еķ��� */

    MN_CALL_BCD_NUM_STRU                stCallNumber;                           /* Call Number ���к��� */
    MN_CALL_SUBADDR_STRU                stCallSubNumber;                        /* Call SubAddress */
    MN_CALL_CALLED_NUM_STRU             stCalledNumber;                         /* Called Number ���к��� */
    MN_CALL_SUBADDR_STRU                stCalledSubAddr;                        /* Called SubAddress */
    MN_CALL_BCD_NUM_STRU                stRedirectNumber;                       /* Redirect Number */
    MN_CALL_SUBADDR_STRU                stRedirectSubaddr;                      /* Redirect Call SubAddress */
    MN_CALL_BCD_NUM_STRU                stConnectNumber;                        /* Connect Number */
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;                /* �ȴ�XCC��Burst DTMF��Cont Burst�ظ���Ϣ */
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enLastReOrigErr;
    VOS_UINT8                           aucRsved[2];

    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    TAF_XCALL_DTMF_BUFFER_STRU          stDtmfBuffer;                           /* BURST DTMF��CONT DTMF�Ļ�����Ϣ,����һ������*/
    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

    TAF_XCALL_CLIENT_INFO_STRU          stFlashClientInfo;                      /* ����flash�û�����Ϣ */
}TAF_XCALL_CALL_ENTITY_STRU;


typedef struct
{
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;
    TAF_XCC_CAUSE_ENUM_UINT32           enXccCause;
}TAF_XCALL_CS_ERR_CODE_MAP_STRU;



typedef struct
{
    VOS_UINT8                                               ucCallId;           /* �����¼��ĺ���ID */
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;              /* �¼������� */
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;         /* �յ����¼��ĺ������� */
    VOS_UINT8                                               ucRsved;
}TAF_XCALL_SUPS_CMD_KEY_EVT_STRU;
typedef struct
{
    VOS_UINT8                               ucNumOfKeyEvt;                      /* ��ע���¼����� */
    VOS_UINT8                               aucRsved[3];
    TAF_XCALL_SUPS_CMD_KEY_EVT_STRU         astKeyEvts[TAF_XCALL_MAX_SS_CMD_KEY_EVT_NUM];  /* ��ע���¼� */
}TAF_XCALL_SUPS_CMD_MGMT_STRU;


typedef struct
{
    TAF_XCALL_DIGIT_MODE_ENUM_UINT8     enDigitMode;

    VOS_UINT8                           ucRsved;
    
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enSoInitType;

    /* Added by h00313353 for Iteration 17, 2015-7-7, begin */
    VOS_UINT32                          ulEmcRedialPeriod;      /* �������ز���ʱ��ʱ�� */
    /* Added by h00313353 for Iteration 17, 2015-7-7, end */
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;  /* Stop Cont DTMF��Start Cont DTMF�����ʱ������ʱ��ʱ������λ:ms */
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
�ṹ��    : TAF_XCALL_DTMF_NODE_UNION
�ṹ˵��  : CALLģ��DTMF������Ϣ���ݽṹ������Cont DTMF��Burst DTMF
1.��    ��   : 2015��7��29��
  ��    ��   : l00324781
  �޸�����   : Iter16����

*****************************************************************************/
typedef union
{
    TAF_CALL_BURST_DTMF_PARA_STRU   stBurstDtmf;
    TAF_CALL_CONT_DTMF_PARA_STRU    stContDtmf;
}TAF_XCALL_DTMF_NODE_UNION;

/*****************************************************************************
�ṹ��    : TAF_XCALL_DTMF_NODE_STRU
�ṹ˵��  : CALLģ��DTMF��������ڵ�ṹ������Cont DTMF��Burst DTMF
1.��    ��   : 2015��7��29��
  ��    ��   : l00324781
  �޸�����   : Iter16����

*****************************************************************************/
typedef struct
{
    TAF_XCALL_DTMF_NODE_UNION                    unDtmf;        /* ����Buffer,Burst DTMF��CONT DTMF */
    AT_MN_MSGTYPE_ENUM_UINT16                    enMsgType;     /* �������Ϣ���� */
    VOS_UINT8                                    aucRsved[2];
    HI_LIST_S                                    stList;
} TAF_XCALL_DTMF_NODE_STRU;

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
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
/*  �޸�����:
   1. Buffer����������XCallProcAppŲ��XCallCtx.c��
   2. Cont DTMF��Burst DTMF����һ������
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


