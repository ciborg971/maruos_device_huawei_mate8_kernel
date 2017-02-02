
#ifndef  MN_CALL_MGMT_H
#define  MN_CALL_MGMT_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallCtx.h"
#include "MnCallApi.h"
#include "UsimPsApi.h"
#include "MnCallMnccProc.h"
#include "MnCallFacilityDecode.h"
#include "product_config.h"
#include "siappstk.h"
#include "hi_list.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
#define MN_CALL_DISC_EVENT_CAUSE_LEN        (3)

#define MN_CALL_IS_OPEN_CODEC(ucCallState, ucStartedHifiFlag)           \
               ( (CALL_IMSA_SRVCC_CALL_ACTIVE       == ucCallState)        \
              || (CALL_IMSA_SRVCC_CALL_HELD         == ucCallState)         \
              || ((CALL_IMSA_SRVCC_CALL_ALERTING    == ucCallState)         \
               && (VOS_TRUE                         == ucStartedHifiFlag)))

/*****************************************************************************
  3���Ͷ���
*****************************************************************************/


enum MN_CALL_POWER_STATE_ENUM
{
    MN_CALL_POWER_STATE_OFF                 = 0, /*�ػ�*/
    MN_CALL_POWER_STATE_ON                  = 1, /*����*/
    MN_CALL_POWER_STATE_BUTT
};
typedef VOS_UINT8  MN_CALL_POWER_STATE_ENUM_U8;

/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define MN_CALL_SIM_ABSENT              PS_USIM_GET_STATUS_ABSENT               /* SIM������                                */
#define MN_CALL_SIM_PRESENT             PS_USIM_GET_STATUS_PRESENT              /* SIM����                                  */


/* PC�طŵ���ȫ�ֱ���ʹ�� */
#define EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

/* ASSERT */
#ifdef  _DEBUG
#define  MN_CALL_ASSERT(expr) \
        if(!(expr)) \
        { \
            MN_ERR_LOG("Assertion failed: " #expr); \
        }
#else
#define  MN_CALL_ASSERT(expr)   ((VOS_VOID)0)
#endif /* _DEBUG */

enum MN_CALL_HOOK_MSG_ID_ENUM
{
    /* STK�����¼� MT CALL  SI_STK_MT_CALL_EVENT_STRU */
    MN_CALL_HOOK_STK_MT_CALL_EVENT                          = 0x02aa,           /* _H2ASN_MsgChoice SI_STK_MT_CALL_EVENT_STRU        */
    /* STK�����¼� CALL Disconnect SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_DISC_EVENT                        = 0x02ab,           /* _H2ASN_MsgChoice SI_STK_CALL_DISCONNECTED_EVENT_STRU */
    /* STK�����¼� CALL Connect SI_STK_CALL_CONNECTED_EVENT_STRU */
    MN_CALL_HOOK_STK_CALL_CONN_EVENT                        = 0x02ac,           /* _H2ASN_MsgChoice SI_STK_CALL_CONNECTED_EVENT_STRU */

    MN_CALL_HOOK_STK_ENVELOPE                               = 0x0300,           /* _H2ASN_MsgChoice SI_STK_ENVELOPE_STRU */

    MN_CALL_HOOK_MSG_ID_BUTT
};
typedef VOS_UINT32 MN_CALL_HOOK_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT����
*****************************************************************************/


typedef struct
{
    VOS_MSG_HEADER
    MN_CALL_HOOK_MSG_ID_ENUM_UINT32     enMsgId;                                /* ��Ϣ�� */
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
} MN_CALL_HOOK_MSG_STRU;


typedef struct
{
    MN_CALL_ID_T                        CallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF����ʱ�䣬0: ����ֹͣDTMF */

    VOS_UINT16                          usOffLength;                            /* stop dtmf req��start dtmf reqʱ��������λms*/
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   opId;
    VOS_UINT8                           aucReserved1[3];
} TAF_CALL_DTMF_INFO_STRU;
typedef struct
{
    TAF_CALL_DTMF_INFO_STRU             stDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_NODE_STRU;

#define TAF_CALL_DTMF_BUF_MAX_CNT               (32)                            /* ��໺��DTMF��Ϣ�ĸ��� */

typedef struct
{
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT8                           ucDtmfCnt;
    VOS_UINT8                           aucReserved1[2];
    TAF_CALL_DTMF_INFO_STRU             stCurrDtmf;
    HI_LIST_S                           stList;
} TAF_CALL_DTMF_CTX_STRU;

/*****************************************************************************
  6 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  7 �ӿں�������
*****************************************************************************/


extern VOS_VOID  MN_CALL_StartFluxCalculate( VOS_UINT8 ucCallId);


VOS_VOID  MN_CALL_StopFluxCalculate( VOS_UINT8 ucCallId);

/* ��λ���еĺ�����Ϣ */
VOS_VOID   MN_CALL_ResetAllCalls(MN_CALL_POWER_STATE_ENUM_U8 enPowerState);

/* ����Call ID */
VOS_UINT32 MN_CALL_AllocCallId(MN_CALL_ID_T *pCallId);

/* �ͷ�Call ID */
VOS_VOID   MN_CALL_FreeCallId(MN_CALL_ID_T  callId);

/* ����Ƿ���Է���/����һ���µĺ��� */
VOS_BOOL   MN_CALL_IsAllowToMakeNewCall(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);

/* �½�һ�����й���ʵ�� */
VOS_VOID  MN_CALL_CreateCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulTi,
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo,
    const MN_CALL_BCD_NUM_STRU          *pstNumber
);

VOS_VOID  MN_CALL_CreateMoCallEntity(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT8 TAF_CALL_IsCallTypeEcall(MN_CALL_ID_T ucCallId);
#endif

VOS_VOID TAF_CALL_UpdateCallInfo(
    MN_CALL_ID_T                        ucCallId,
    MN_CALL_INFO_STRU                  *pstCallInfo
);

VOS_UINT32 MN_CALL_GetSpecificCallInfo(
    MN_CALL_ID_T                        CallId,
    MN_CALL_MGMT_STRU                  *pstCallInfo
);

VOS_VOID MN_CALL_GetCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                           *pbReleaseFlag
);

VOS_VOID TAF_CALL_FillDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf
);

VOS_UINT8 TAF_CALL_IsCallTypeEmgencyCall(MN_CALL_ID_T ucCallId);


VOS_VOID  MN_CALL_CreateMtCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
);

/*****************************************************************************
 �� �� ��  : MN_CALL_DeleteCallEntity
 ��������  : ���һ�����й���ʵ��
 �������  : callId - ��Ҫ����ĺ��е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_DeleteCallEntity(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcEntityId
 ��������  : ����CallId��ȡEntityId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcTi(
    MN_CALL_ID_T                        callId
);
/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcCallDir
 ��������  : ����CallId��ȡEntityId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcCallDir(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ReportEvent
 ��������  : ������Client�ϱ������¼�
 �������  : callId      - ��Ҫ�ϱ��¼��ĺ��е�ID
              enEventType - �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ReportEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_EVENT_ENUM_U32              enEventType
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateClientId
 ��������  : ����ָ�����е�Client ID��Ϣ
 �������  : callId   - ��Ҫ����Client ID�ĺ��е�ID
              clientId - �µ�Client IDֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateClientId(
    MN_CALL_ID_T                        callId,
    MN_CLIENT_ID_T                      ucClientId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallState
 ��������  : ����ָ�����еĺ���״̬��Ϣ
 �������  : callId      - ��Ҫ����״̬�ĺ��е�ID
              enCallState - �µĺ���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateMptyState
 ��������  : ����ָ�����е�MPTY״̬��Ϣ
 �������  : callId      - ��Ҫ����MPTY״̬�ĺ��е�ID
              enMptyState - �µ�MPTY״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateMptyState(
    MN_CALL_ID_T                        callId,
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallType
 ��������  : ����ָ�����еĺ���������Ϣ
 �������  : callId     - ��Ҫ���º������͵ĺ��е�ID
              enCallType - �µĺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallType(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallMode
 ��������  : ����ָ�����еĺ���ģʽ��Ϣ
 �������  : callId     - ��Ҫ���º���ģʽ�ĺ��е�ID
              enCallMode - �µĺ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallMode(
    MN_CALL_ID_T                        callId,
    MN_CALL_MODE_ENUM_U8                enCallMode
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateDataCallCfgInfo
 ��������  : ����ָ�����е����ݺ���������Ϣ
 �������  : callId     - ��Ҫ�������ݺ������õĺ��е�ID
             pstDataCfg - �µ����ݺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo
);


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRedirNumber
 ��������  : ����ָ�����е�ת�ƺ�����Ϣ
 �������  : callId         - ��Ҫ����ת�ƺ���ĺ��е�ID
              pstRedirNumber - �µ�ת�ƺ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRedirNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNumber
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateConnNumber
 ��������  : ����ָ�����е����Ӻ�����Ϣ
 �������  : callId        - ��Ҫ�������Ӻ���ĺ��е�ID
              pstConnNumber - �µ����Ӻ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateConnNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstConnNumber
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallNumber
 ��������  : ����ָ���������������Ϣ
 �������  : callId        - ��Ҫ�������Ӻ���ĺ��е�ID
              pstCallNumber - �µ����Ӻ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstCallNumber
);


VOS_VOID  MN_CALL_UpdateCalledNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CALLED_NUM_STRU      *pstCalledNumber
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateSsNotify
 ��������  : ����ָ�����еĲ���ҵ��֪ͨ��Ϣ
 �������  : callId    - ��Ҫ���²���ҵ������ĺ��е�ID
              pstSsInfo - �µĲ���ҵ��֪ͨ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateSsNotify(
    MN_CALL_ID_T                        callId,
    const MN_CALL_SS_NOTIFY_STRU        *pstSsInfo
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcCause
 ��������  : ����ָ�����е�CCԭ��ֵ��Ϣ
 �������  : callId    - ��Ҫ����CCԭ��ֵ�ĺ��е�ID
              enCcCause - �µ�CCԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcCause(
    MN_CALL_ID_T                        callId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateNoCliCause
 ��������  : ����ָ�����е��޺�����ʾԭ����Ϣ
 �������  : callId       - ��Ҫ�����޺�����ʾԭ��ĺ��е�ID
              enNoCliCause - �µ��޺�����ʾԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateNoCliCause(
    MN_CALL_ID_T                        callId,
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRabId
 ��������  : ����ָ�����е�RAB ID��Ϣ
 �������  : callId  - ��Ҫ����RAB ID�ĺ��е�ID
              ucRabId - �µ�RAB ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRabId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucRabId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallState
 ��������  : ��ȡָ�����е�״̬��Ϣ
 �������  : callId       - ��Ҫ��ȡ״̬��Ϣ�ĺ��е�ID
 �������  : penCallState - ��õĺ���״̬
              penMptyState - ��õ�MPTY״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               *penCallState,
    MN_CALL_MPTY_STATE_ENUM_U8          *penMptyState
);

TAF_CALL_SUB_STATE_ENUM_UINT8 TAF_CALL_GetCallSubState(
    MN_CALL_ID_T                        callId
);

VOS_VOID TAF_CALL_SetCallSubState(
    MN_CALL_ID_T                        callId,
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState
);


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallsByState
 ��������  : ��ȡ�ض�����״̬�����к���
 �������  : CallState     - ָ���ĺ���״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
              pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);


/*****************************************************************************
 �� �� ��  : MN_CALL_RegSsKeyEvent
 ��������  : ע�Ჹ��ҵ������Ĺ�ע�¼�
             ����ע�ĺ����Ϸ�����ע���¼�ʱ��ע��ĺ�������(enSubseqOp)
             ����ִ��; �����¼��ڷ���ʱ���������κβ���, ��������
 �������  : callId     - ��ʶ�����¼��ĺ���
              enEvt      - ��ע���¼�����
              enSubseqOp - ���¼�������Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_RegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ClearSsKeyEvent
 ��������  : ������еĹ�ע�¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ClearSsKeyEvent(VOS_VOID);


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallMgmtProgress
 ��������  : �������˲���ҵ�������ص��¼�ʱ, ���²���ҵ������Ľ�չ.
             �ú������ݷ������¼�����ע��Ĺ�ע�¼��������ض�����.
 �������  : callId  - ��ʶ�����¼��ĺ���
             enEvt   - �������¼�����
             ulErrno - ����ǲ����ܾ�����¼�, ��ҪЯ�������룬�ò���ֻ����
                       ���ϲ��ϱ�����ʧ��ʱ����Ч.
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallSupsProgress(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    VOS_UINT32                          ulErrno
);

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCsCallExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS CALL �ͽ��������
 �������  : ucCallExitFlg - �Ƿ���call
             enCallType    - call type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    TAF_CALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
);

/*****************************************************************************
 �� �� ��  : MN_CALL_BeginCallMgmtCmdProgress
 ��������  : ��ʼ���в���ҵ�����, ��¼��ʼ��Ϣ, ���ò���ҵ����б�־
 �������  : clientId - ����ò���ҵ�������Client��ID
              enCallMgmtCmd    - ����Ĳ���ҵ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_BeginCallSupsCmdProgress(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd
);

/*****************************************************************************
 �� �� ��  : MN_CALL_IsCallSupsCmdInProgress
 ��������  : �鿴��ǰ�Ƿ��ڽ��в���ҵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ���ڽ��в���ҵ�����,  VOS_FALSE - û�н��в���ҵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_IsCallSupsCmdInProgress(VOS_VOID);


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallInfoList
 ��������  : ��ȡ��ǰ����״̬��ΪIDLE�ĺ�����Ϣ
 �������  : pucNumOfCalls - �����������ܴ洢�ĺ�����Ϣ����
 �������  : pucNumOfCalls - ʵ�������(״̬��ΪIDLE��)������Ϣ����
              pstCallInfos  - ����ĺ�����Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallsByState
 ��������  : ��ȡ�ض�MPTY״̬�����к���
 �������  : enMptyState   - ָ����MPTY״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
             pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByMptyState(
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);

/*****************************************************************************
 �� �� ��  : MN_CALL_TiUsedCheck
 ��������  : ��鵱ǰTi�Ƿ�����ĳ������ʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ����FDN����,  VOS_FALSE - ������FDN����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_TiUsedCheck(
    VOS_UINT32                          ulTi
);


/*****************************************************************************
 �� �� ��  : MN_CALL_CheckNotIdleStateExist
 ��������  : �ж���ǰ�Ƿ��з�Idle̬��ʵ�����
 �������  : CallState     - ָ���ĺ���״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
             pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckNotIdleStateExist( VOS_VOID );


/*****************************************************************************
 �� �� ��  : MN_CALL_CheckCallEntityExist
 ��������  : �ж���ǰָ��call id��ʵ���Ƿ����
 �������  : CallState     - ָ���ĺ���״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
             pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckCallEntityExist(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 Prototype      : MN_CALL_InvokeId_Alloc()
 Description    : ����InvokeId���˺���Ϊԭ���Ĵ��������ֲ
 Input          : ucTi: ���б�ʶ
 Output         : *pInvokeId: �����InvokeId
 Return Value   : VOS_OK    ����ɹ�
                : VOS_ERROR ����ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_INT32 MN_CALL_InvokeIdAlloc(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           *pInvokeId,
    VOS_UINT8                           ucOperateCode
);


/*****************************************************************************
 �� �� ��  : MN_CALL_GetDataCallCfgInfo
 ��������  : ��ȡָ�����е����ݺ���������Ϣ
 �������  : callId     - ��Ҫ�������ݺ������õĺ��е�ID
             pstDataCfg - �µ����ݺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateTi
 ��������  : ����ָ�����е�TI��Ϣ
 �������  : callId  - ��Ҫ����RAB ID�ĺ��е�ID
             ucTi    - �µ�Tiֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateTi(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
);

VOS_UINT8 TAF_CALL_GetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId
);
VOS_VOID TAF_CALL_SetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucSrvccLocalAlertedFlag
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetNotIdleStateCalls
 ��������  : ��ȡ������Idle״̬��Call
 �������  : callId  - ��Ҫ��ȡ״̬��Ϣ�ĺ��е�ID
 �������  : pCallState - ��õĺ���״̬
             pMptyState - ��õ�MPTY״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetNotIdleStateCalls(
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
);


VOS_UINT32  MN_CALL_SsOpCodeTransToSsEvent(
    MN_CALL_SS_OPERATION_CODE_T         sSOpCode,
    MN_CALL_SS_PROGRESS_EVT_ENUM        *penEvent
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallInfoByCallId
 ��������  : ���ݺ���Id����ȡ��Ӧ��ʵ����й�����Ϣ
 �������  : callId        - ��Ҫ�������ݺ������õĺ��е�ID
             pstMgmtEntity - ���й���ʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_INFO_STRU                   *pstCallInfo
);

/*****************************************************************************
 �� �� ��  : MN_CALL_DeRegSsKeyEvent
 ��������  : ɾ������ҵ������Ĺ�ע�¼�
 �������  : callId     - ��ʶ�����¼��ĺ���
             enEvt      - ����Ҫ��ע���¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_DeRegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
);

/*****************************************************************************
 �� �� ��  : TAF_CALL_ProcRelCallSsKeyEvent
 ��������  : ����ҵ���ڽ����ж��쳣״̬����Ӧ����
 �������  : callId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��12��
    ��    ��   : ���� 44270
    �޸�����   : �����ɺ��������ⵥ��:AT2D04057
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
);



VOS_VOID  MN_CALL_UpdateCcbsSetup(
    const NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);


VOS_VOID  MN_CALL_UpdateCcbsSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);


VOS_VOID  MN_CALL_GetCcbsSetup(
    NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
);

VOS_VOID MN_CALL_UpdateCcCallDir(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
);


VOS_VOID  MN_CALL_UpdateRecallSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
);

/*****************************************************************************
 Prototype      : MN_CALL_CallCtrlProcess
 Description    : ����USIMģ���ṩ��call control�ӿڣ�����Envelop�����USIMģ��
 Input          : pstParam - ���е���Ϣ��������дEnvelop�����е���Ӧ����
 Output         :
 Return Value   : VOS_OK    - �����ɹ�
                : VOS_ERR - ����ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-08-19
    Author      : huwen
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_CallCtrlProcess(
    MN_CALL_ORIG_PARAM_STRU             *pstParam
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallCtrlState
 ��������  : ����ָ�����еĺ���״̬��Ϣ
 �������  : callId          - ��Ҫ����״̬�ĺ��е�ID
              enCallCtrlState - �µĺ��п���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallCtrlState(
    MN_CALL_ID_T                        callId,
    MN_CALL_CTRL_STATE_ENUM_U32         enCallCtrlState
);


MN_CALL_ALS_LINE_NO_ENUM_U8  MN_CALL_GetAlsLineInfo(VOS_VOID);


VOS_VOID  MN_CALL_UpdateAlsLineNbr(
    MN_CALL_ID_T                        callId,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNbr
);


VOS_UINT32 MN_CALL_UpdateAlsLineInfo(
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine,
    VOS_BOOL                            bUpdateNvim
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallType
 ��������  : ��ȡָ�����еĺ���������Ϣ
 �������  : callId     - ��Ҫ���º������͵ĺ��е�ID
              enCallType - �µĺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
extern MN_CALL_TYPE_ENUM_U8  MN_CALL_GetCallType(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRbId
 ��������  : ˢ��RbId
 �������  : ��
 �������  : pulNumOfCalls - ���и���
              pCallIds - ��Ӧ�ĺ���Id
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_VOID  MN_CALL_UpdateRbId(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulRbId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetRbId
 ��������  : ����CallId��ȡRbId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT32 MN_CALL_GetRbId(MN_CALL_ID_T callId);


VOS_VOID MN_CALL_SetVideoCallChannelOpenFlg(
    VOS_BOOL                            bVideoCallChannelOpenFlg,
    MN_CALL_ID_T                        callId
);


VOS_BOOL MN_CALL_GetVideoCallChannelOpenFlg(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ConCallMsgTypeToCcMsgType
 ��������  : ��CALLL�Ķ������Ϣ����ת��ΪCC�������Ϣ����
 �������  : enCallMsgType :  ������Я��UUS1����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCallMsgTypeToCcMsgType(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType,
    NAS_CC_MSG_TYPE_ENUM_U8             *penCcMsgType
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ConCcMsgTypeToCallMsgType
 ��������  : ��CC����Ϣ����ת��ΪCALL����Ϣ����
 �������  : enCcMsgType    :CC�������Ϣ����
 �������  : penCallMsgType :CALL�������Ϣ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCcMsgTypeToCallMsgType(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      *penCallMsgType
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRptUus1Info
 ��������  : �����ϱ�Call��Ϣ��UUS1ֵ
 �������  : callId         :����ID
             enCcMsgType    :����µ���Ϣ����
             pstUserUser    :UUS1��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_UpdateRptUus1Info(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ConCcUusInfoToCall
 ��������  : ��CC��UUS��Ϣ��ʽת��Ϊ���ϱ�����Ϣ��ʽ
 �������  : enCcMsgType        :��ת������Ϣ����
             pstUserUser        :CC�ϱ���UUS����Ϣ��ʽ
 �������  : pstUus1Info        :ת�����ϱ���UUS����Ϣ��ʽ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_ConCcUusInfoToCall(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ConCallUusInfoToCc
 ��������  : ��伤��UUS1�����Ϣ
 �������  : enMsgType    :  ��ת������Ϣ����
             pstUus1Info  :  �û���Ҫ����UUS1�����Ϣ
 �������  : pstUuieInfo  :  ���͵�����UUIE��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  MN_CALL_ConCallUusInfoToCc(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
);

VOS_VOID NAS_CALL_SndOutsideContextData(VOS_VOID);

VOS_UINT32 NAS_CALL_RestoreContextData(struct MsgCB * pMsg);


VOS_VOID  MN_CALL_CallInfoReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
);



VOS_VOID  MN_CALL_GetCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
);


VOS_VOID MN_CALL_RcvTafAgentGetCallInfo(VOS_VOID);


VOS_UINT32  MN_CALL_GetSpecificStatusCallInfo(
    MN_CALL_STATE_ENUM_U8                enCallStatus,
    MN_CALL_INFO_STRU                   *pstCallInfo
);



/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */

VOS_VOID  MN_CALL_CreateStkMoCallEntity(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkCallOrig);


VOS_VOID MN_CALL_UpdateSubAddress(
    VOS_UINT8                           ucCallId,
    MN_CALL_SUBADDR_STRU               *pstSubCallNumber
);


VOS_VOID MN_CALL_UpdateOpId(
    VOS_UINT8                           ucCallId,
    MN_OPERATION_ID_T                   opId
);


VOS_VOID MN_CALL_UpdateCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                            bReleaseFlag
);


VOS_VOID  MN_CALL_RecordCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        NAS_CC_MSG_SETUP_MT_STRU            *pstSetup);


VOS_VOID  MN_CALL_ReadCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        MN_CALL_CLPR_GET_CNF_STRU          *pstGetClprCnf);





VOS_UINT32 MN_CALL_AllowSupsOperation(VOS_VOID);



/*****************************************************************************
 �� �� ��  : MN_CALL_GetNetDiscEventInfo
 ��������  : ��ȡUE�����DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ��CAUSE, CALLID��TI
 �������  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ
 �������  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent �����ͷ��¼��ṹ
             VOS_UINT8                          *pucTi,     ��Ϣ��Ӧ�ĺ���TI
             VOS_UINT8                          *pucCallId  ��Ϣ��Ӧ��CALL ID
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR     ��ȡ�����ɹ�
                ����                ��ȡ����ʧ��

*****************************************************************************/
VOS_UINT32 MN_CALL_GetNetDiscEventInfo(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetUeDiscEventInfo
 ��������  : ��ȡUE�����DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ��CAUSE,CALLID��TI
 �������  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ
 �������  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent �����ͷ��¼��ṹ
             VOS_UINT8                          *pucTi,     ��Ϣ��Ӧ�ĺ���TI
             VOS_UINT8                          *pucCallId  ��Ϣ��Ӧ��CALL ID
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR     ��ȡ�����ɹ�
                ����                ��ȡ����ʧ��

*****************************************************************************/
VOS_UINT32 MN_CALL_GetUeDiscEventInfo(
    const MNCC_REQ_PRIM_MSG_STRU       *pstMsg,
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
);

VOS_UINT32 MN_CALL_IsNeedCallRedial(
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);
VOS_UINT32 TAF_CALL_IsOrigNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConfNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsConnNeedRpt(VOS_VOID);
VOS_UINT32 TAF_CALL_IsCendNeedRpt(VOS_VOID);


TAF_CS_CAUSE_ENUM_UINT32  MN_CALL_GetCsCause(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateDiscCallDir
 ��������  : ����CALL�Ҷϵķ���
 �������  : callId     - ����ID
             ucIsUser   - �Ƿ����û�����ĹҶ�
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_CALL_UpdateDiscCallDir(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucIsUser
);

VOS_VOID  MN_CALL_GetMgmtEntityInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_MGMT_STRU                   *pstMgmtEntity
);

VOS_UINT8 TAF_CALL_GetDisconnectFlg(
    MN_CALL_ID_T                        callId
);

VOS_VOID TAF_CALL_InitDtmfCtx(VOS_VOID);

VOS_VOID TAF_CALL_ResetDtmfCtx(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_CheckUserDtmfCallId(
    MN_CALL_ID_T                        CallId
);

TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_GetAllowedDtmfCallId(
    MN_CALL_ID_T                       *pCallId
);

TAF_CALL_DTMF_CTX_STRU* TAF_CALL_GetDtmfCtx(VOS_VOID);

TAF_CALL_DTMF_STATE_ENUM_UINT8 TAF_CALL_GetDtmfState(VOS_VOID);

VOS_VOID TAF_CALL_SetDtmfState(
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enState
);

VOS_UINT8 TAF_CALL_GetDtmfBufCnt(VOS_VOID);

HI_LIST_S* TAF_CALL_GetDtmfListHead(VOS_VOID);

TAF_CALL_DTMF_INFO_STRU* TAF_CALL_GetDtmfCurInfo(VOS_VOID);

/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */

TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_SaveDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
);

VOS_VOID TAF_CALL_DelDtmfNode(
    TAF_CALL_DTMF_NODE_STRU            *pstNode
);

VOS_VOID TAF_CALL_PreProcRelAllCall(VOS_VOID);

/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */

#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_CreateCallEntitiesWithImsCallInfo(
    VOS_UINT8                           ucSrvccCallNum,
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstSrvccCallInfo,
    VOS_UINT8                           ucStartedHifiFlag
);

VOS_VOID TAF_CALL_ProcSrvccDtmfBuffInfo(TAF_CALL_DTMF_BUFF_STRU *pstDtmfBuffInfo);
#endif
MN_CALL_MGMT_STRU *TAF_CALL_GetCallEntityAddr(VOS_VOID);

VOS_UINT32 TAF_CALL_IsCallRedialCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_VOID MN_CALl_VoicePreferJudgeVoiceCallExist(VOS_VOID);
VOS_VOID MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_UINT32 ulVoiceFlag);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* MN_CALL_MGMT_H */

