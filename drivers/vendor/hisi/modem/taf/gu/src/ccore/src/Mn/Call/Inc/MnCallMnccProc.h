
#ifndef  MN_CALL_MNCC_PROC_H
#define  MN_CALL_MNCC_PROC_H



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasMncc.h"
#include "product_config.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/

#define CALL_MAX_ENT_NUM  7

/* �ýṹ����CCBS����������
   ��ʱ�洢CCBS��Ϣ */
#define MN_CALL_CCBS_INVALID_INDEX              (0)
#define MN_CALL_CCBS_MAX_INDEX                  (5)
#define MN_CALL_CCBS_DEFAULT_INDEX              (1)

#define CCA_SS_DIAG_CCBS_POSSIBLE               (7)
#define MN_CALL_NET_TYPE_GSM                    (0)

typedef struct
{
    VOS_BOOL                            bWaitSendAlertStatus;
    VOS_UINT8                           ucCallId;
} MN_CALL_WAIT_SEND_ALERT_STRU;


#define MN_CALL_BCD_ODD_NUMBER_END                          (0xF0)

/* MN_CALL_MM_EMERGENCY_CONTENT_STRU��MN_CALL_MM_EMERGENCY_LIST_STRU������SDC */


typedef enum
{
    MN_CALL_ACTIVE_SWITCH_ON = 0,
    MN_CALL_ACTIVE_SWITCH_OFF,

    RMN_CALL_ACTIVE_SWITCH_BUTT
}MN_CALL_TIMER_ACTIVE_SWITCH_ENUM;               /*��ʶĳCALLID�Ƿ񼤻���*/


typedef struct
{
    VOS_UINT32                          ulStartCallTime;                        /* ��ǰͨ����ʼʱ�� ��λΪ�� */
    VOS_UINT32                          ulTotalCallTime;                        /*�ۼ�ͨ��ʱ��*/
    VOS_UINT32                          ulPreCallTime;                          /*�ϴ�ͨ��ʱ��*/
    MN_CALL_TIMER_ACTIVE_SWITCH_ENUM       CallidActiveSwitch;                  /*��ʶ��Callid�Ƿ񼤻�*/
}MN_CALL_TIMER_CALC_ST;


typedef struct
{
    MN_CLIENT_ID_T                                          clientId;
    MN_OPERATION_ID_T                                       opId;
    VOS_UINT8                                               ucCallId;
    VOS_UINT8                                               ucTi;                      /* TI��Ϣ������TI FLAG��TI��������ʽ�ο��������� */
    MN_CALL_STATE_ENUM_UINT8                                enCallState;               /* IMSAͬ��������IMS���µĺ���״̬ */
    MN_CALL_MODE_ENUM_U8                                    enCallMode;
    MN_CALL_MPTY_STATE_ENUM_U8                              enMptyState;
    MN_CALL_DIR_ENUM_U8                                     enCallDir;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    VOS_UINT8                                               ucLocalAlertedFlag;        /* IMS���Ƿ���й��������� */
    VOS_UINT8                                               aucReserve1[1];
    MN_CALL_BCD_NUM_STRU                                    stCallNumber;
    MN_CALL_CALLED_NUM_STRU                                 stCalledNumber;
    MN_CALL_BCD_NUM_STRU                                    stRedirectNumber;
    MN_CALL_BCD_NUM_STRU                                    stConnectNumber;
}TAF_CALL_SRVCC_CALL_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucRslt;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           aucReserve[2];
    TAF_CALL_SRVCC_CALL_INFO_STRU       astCallInfo[CALL_MAX_ENT_NUM];
}TAF_CALL_LOG_IMSA_API_GET_SRVCC_CALL_INFO_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32 VOS_GetTick(VOS_VOID);

/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsMtCallAllowed(
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup,
    VOS_UINT8                           ucCallId,
    MN_CALL_CC_CAUSE_ENUM_U8           *penCause
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccSetupInd
 ��������  : ����MNCC_SETUP_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccSetupCnf
 ��������  : ����MNCC_SETUP_CNFԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccSetupComplInd
 ��������  : ����MNCC_SETUP_COMPL_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSetupComplInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccCallProcInd
 ��������  : ����MNCC_CALL_PROC_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccCallProcInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccSyncInd
 ��������  : ����MNCC_SYNC_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccSyncInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccAlertInd
 ��������  : ����MNCC_ALERT_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccAlertInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccDiscInd
 ��������  : ����MNCC_DISC_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccDiscInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccRelInd
 ��������  : ����MNCC_REL_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccRelCnf
 ��������  : ����MNCC_REL_CNFԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRelCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccRejInd
 ��������  : ����MNCC_REJ_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRejInd(
    MNCC_IND_PRIM_MSG_STRU             *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccFacilityInd
 ��������  : ����MNCC_FACILITYS_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccHoldCnf
 ��������  : ����MNCC_HOLD_CNFԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccHoldRej
 ��������  : ����MNCC_HOLD_REJԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccHoldRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccRetrieveCnf
 ��������  : ����MNCC_RETRIEVE_CNFԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccRetrieveRej
 ��������  : ����MNCC_RETRIEVE_REJԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccRetrieveRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccFacilityLocalRej
 ��������  : ����MNCC_RETRIEVE_REJԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccFacilityLocalRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);
/*****************************************************************************
 �� �� ��  : MN_CALL_ReportCoeceEvent
 ��������  : �ϱ������������¼�
 �������  : callId - ��Ҫ�ϱ��¼��ĺ��е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ReportChannelEvent(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enEventType
);

/*****************************************************************************
 �� �� ��  : CALL_SetChannelOpenFlg
 ��������  : �����ŵ��򿪱�־
 �������  : bChannelOpenFlg - �����ŵ��򿪱�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetChannelOpenFlg(
    VOS_BOOL                            bChannelOpenFlg
);
/*****************************************************************************
 �� �� ��  : CALL_GetChannelOpenFlg
 ��������  :
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
VOS_BOOL MN_CALL_GetChannelOpenFlg( VOS_VOID );

/*****************************************************************************
 �� �� ��  : CALL_SetWaitSendAlertStatus
 ��������  :
 �������  : bWaitSendAlertStatus   - ҵ���ŵ���״̬
             uccallId               - ����Id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetWaitSendAlertStatus(
    VOS_BOOL                            bWaitSendAlertStatus,
    VOS_UINT8                           uccallId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccProgressInd
 ��������  : ����MNCC_PROGRESS_INDԭ��
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccProgressInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

/*****************************************************************************
 �� �� ��  : MN_CALL_SetMmEmerNumList
 ��������  : �洢����MM�Ӳ�Ľ������к����б�
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU        *pstMnccEmcListInd
);

VOS_UINT32 MN_CALL_GetTchParm(
    MN_CALL_CHANNEL_PARAM_STRU          *pstChannParm
);
/*****************************************************************************
 �� �� ��  : MN_CALL_GetTchStatus
 ��������  :
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
VOS_BOOL MN_CALL_GetTchStatus( VOS_VOID );




VOS_VOID MN_CALL_PorcMnccPromptInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


VOS_VOID MN_CALL_ProcMnccEstInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ProcMnccRecallInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);


/*****************************************************************************
 �� �� ��  : CALL_GetWaitSendAlertStatus
 ��������  :
 �������  :
 �������  : pbWaitSendAlertStatus - ��ǰ�Ƿ��ڵȴ�����alerting��Ϣ״̬
              puccallId             - ��Ӧ�ĺ���Id
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_GetWaitSendAlertStatus(
    VOS_BOOL                            *pbWaitSendAlertStatus,
    VOS_UINT8                           *puccallId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcUus1Info
 ��������  : ����CCģ���к�������UUS1��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateCcUus1Info(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcUus1Info
 ��������  : ��ȡCC�����UUS1�����Ϣ
 �������  : ��
 �������  : pulActNum      :CC�ܹ��������
             pstUus1Info    :����UUS1����Ϣ
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcUus1Info(
    VOS_UINT32                          *pulActNum,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
);

VOS_VOID  MN_CALL_ProcUusInfoInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  MN_CALL_ProcEmergencyListInd(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);



VOS_VOID MN_CALL_ReportHoldEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );

VOS_VOID MN_CALL_ReportRetrieveEvent(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCallNum,
    const VOS_UINT8                    *pucCallId );


/* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
VOS_VOID  MN_CALL_ProcBufferedCall(
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);

VOS_VOID TAF_CALL_ProcBufferedRedialMessage(
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);
/* Modified by zwx247453 for CHR optimize, 2015-07-07, end */



VOS_VOID MN_CALL_SndAtChannelInfoInd(
    MN_CALL_CHANNEL_EVENT_ENUM_U32      enChannelEvent,
    MN_CALL_CHANNEL_INFO_STRU          *pstChannelInfo,
    VOS_UINT8                           ucIsLocalAlertingFlag
);

/* ɾ���ú���������ʵ���Ƶ�����MN_CALL_ReportChannelEvent�� */

VOS_UINT32 TAF_CALL_IsNeedLocalAlerting(const NAS_CC_IE_PROGRESS_INDICATOR_STRU *pstProgInd);

VOS_VOID  TAF_CALL_RcvCcStartDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStartDtmfRej(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

VOS_VOID  TAF_CALL_RcvCcStopDtmfCnf(
    const MNCC_IND_PRIM_MSG_STRU        *pstMsg
);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_ProcMnccSrvccStatusInd(
    MNCC_SRVCC_STATUS_IND_STRU         *pstSrvccMsg
);

VOS_VOID TAF_CALL_MapCallInfoToCcInfo(
    MNCC_ENTITY_STATUS_STRU            *pstCcInfo,
    VOS_UINT8                          *pucCallNum
);

VOS_VOID TAF_CALL_ProcDtmfBuffer(VOS_VOID);

VOS_VOID TAF_CALL_ProcSrvccSyncInfo(VOS_VOID);
#endif

VOS_UINT8 TAF_CALL_IsEcallRedialExist(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ProcessEcallPeriodTimerLen(VOS_UINT8 ucCallId);

VOS_VOID TAF_CALL_ProcEcallRel(
    MN_CALL_MGMT_STRU                  *pstCallEntity);
#endif

VOS_VOID  MN_CALL_SendVcMsg(
    CALL_VC_MSG_ID_ENUM_U16             enEventType
);

VOS_VOID TAF_CALL_SetTchCallType(TAF_CALL_TYPE_ENUM_UINT16 enCallType);



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

#endif /* MN_CALL_MNCC_PROC_H */

