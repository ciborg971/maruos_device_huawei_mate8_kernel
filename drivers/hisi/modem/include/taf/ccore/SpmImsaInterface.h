
#ifndef  SPM_IMSA_INTERFACE_H
#define  SPM_IMSA_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallApi.h"
#include "TafClientApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/
/* �Ƶ�MnCallApi.h */

enum SPM_IMSA_MSG_TYPE_ENUM
{
    ID_SPM_IMSA_CALL_ORIG_REQ               = TAF_SPM_IMSA_MSG_BASE,            /* _H2ASN_MsgChoice SPM_IMSA_CALL_ORIG_REQ_STRU */
    ID_SPM_IMSA_CALL_SUPS_CMD_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_SUPS_CMD_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ,                                         /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU */
    ID_SPM_IMSA_CALL_START_DTMF_REQ,                                            /* _H2ASN_MsgChoice SPM_IMSA_CALL_START_DTMF_REQ_STRU */
    ID_SPM_IMSA_CALL_STOP_DTMF_REQ,                                             /* _H2ASN_MsgChoice SPM_IMSA_CALL_STOP_DTMF_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CUDR_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CUDR_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_CLPR_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_CLPR_REQ_STRU */
    ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ,                                       /* _H2ASN_MsgChoice SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU */

    ID_SPM_IMSA_CALL_MODIFY_REQ,                                                /* _H2ASN_MsgChoice SPM_IMSA_CALL_MODIFY_REQ_STRU */
    ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ,                                  /* _H2ASN_MsgChoice SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU */
    ID_SPM_IMSA_CALL_ECONF_DIAL_REQ,                                            /* _H2ASN_MsgChoice SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU */
    ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ,                                       /* _H2ASN_MsgChoice SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU */
    ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ,                                 /* _H2ASN_MsgChoice SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU*/
    ID_SPM_IMSA_REGISTER_SS_REQ             = TAF_SPM_IMSA_MSG_BASE+0x100,      /* _H2ASN_MsgChoice SPM_IMSA_REGISTER_SS_REQ_STRU */
    ID_SPM_IMSA_ERASE_SS_REQ,                                                   /* _H2ASN_MsgChoice SPM_IMSA_ERASE_SS_REQ_STRU */
    ID_SPM_IMSA_ACTIVATE_SS_REQ,                                                /* _H2ASN_MsgChoice SPM_IMSA_ACTIVATE_SS_REQ_STRU */
    ID_SPM_IMSA_DEACTIVATE_SS_REQ,                                              /* _H2ASN_MsgChoice SPM_IMSA_DEACTIVATE_SS_REQ_STRU */
    ID_SPM_IMSA_INTERROGATE_SS_REQ,                                             /* _H2ASN_MsgChoice SPM_IMSA_INTERROGATE_SS_REQ_STRU */
    ID_SPM_IMSA_PROCESS_USSD_REQ,                                               /* _H2ASN_MsgChoice SPM_IMSA_PROCESS_USSD_REQ_STRU */
    ID_SPM_IMSA_RELEASE_REQ,                                                    /* _H2ASN_MsgChoice SPM_IMSA_RELEASE_REQ_STRU */

    ID_IMSA_SPM_CALL_MSG                    = TAF_SPM_IMSA_MSG_BASE+0x200,      /* _H2ASN_MsgChoice IMSA_SPM_CALL_MSG_STRU */
    ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF,                                         /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU */
    ID_IMSA_SPM_CHANNEL_INFO_IND,                                               /* _H2ASN_MsgChoice IMSA_SPM_CHANNEL_INFO_IND_STRU */
    ID_IMSA_SPM_CALL_GET_CLPR_CNF,                                              /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_CLPR_CNF_STRU */
    ID_IMSA_SPM_CALL_START_DTMF_CNF,                                            /* _H2ASN_MsgChoice IMSA_SPM_CALL_START_DTMF_CNF_STRU */
    ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU */
    ID_IMSA_SPM_CALL_STOP_DTMF_CNF,                                             /* _H2ASN_MsgChoice IMSA_SPM_CALL_STOP_DTMF_CNF_STRU */
    ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND,                                        /* _H2ASN_MsgChoice IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU */
    ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU */
    ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND  ,                                    /* _H2ASN_MsgChoice IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU */
    ID_IMSA_SPM_CALL_MODIFY_CNF,                                                /* _H2ASN_MsgChoice IMSA_SPM_CALL_MODIFY_CNF_STRU */
    ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF,                                  /* _H2ASN_MsgChoice IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU */
    ID_IMSA_SPM_CALL_MODIFY_STATUS_IND,                                         /* _H2ASN_MsgChoice IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU */
    ID_IMSA_SPM_CALL_ECONF_DIAL_CNF,                                            /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU */
    ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF,                                       /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU */
    ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF,                                 /* _H2ASN_MsgChoice IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU*/
    ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND,                                          /* _H2ASN_MsgChoice IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU */
    ID_IMSA_SPM_SS_MSG                      = TAF_SPM_IMSA_MSG_BASE+0x300,     /* _H2ASN_MsgChoice IMSA_SPM_SS_MSG_STRU */

    ID_SPM_IMSA_MSG_TYPE_BUTT
};
typedef  VOS_UINT32  SPM_IMSA_MSG_TYPE_ENUM_UINT32;


enum SPM_IMSA_CALL_MODIFY_STATUS_ENUM
{
    SPM_IMSA_CALL_MODIFY_REMOTE_USER_REQUIRE_TO_MODIFY,                         /* Զ���û������modify */
    SPM_IMSA_CALL_MODIFY_PROC_BEGIN,                                            /* modify���̿�ʼ */
    SPM_IMSA_CALL_MODIFY_PROC_END,                                              /* modify���̽��� */
    SPM_IMSA_CALL_MODIFY_STATUS_BUTT
};
typedef  VOS_UINT8  SPM_IMSA_CALL_MODIFY_STATUS_ENUM_UINT8;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_REGISTERSS_REQ_STRU          stRegSsReq;
} SPM_IMSA_REGISTER_SS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_ERASESS_REQ_STRU             stSsEraseReq;
} SPM_IMSA_ERASE_SS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_ACTIVATESS_REQ_STRU          stSsActivateReq;
} SPM_IMSA_ACTIVATE_SS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_DEACTIVATESS_REQ_STRU        stDeactivateSsReq;
} SPM_IMSA_DEACTIVATE_SS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_INTERROGATESS_REQ_STRU       stInterrogateSsReq;
} SPM_IMSA_INTERROGATE_SS_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
    TAF_SS_PROCESS_USS_REQ_STRU         stProcUssdReq;
} SPM_IMSA_PROCESS_USSD_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved2[1];
} SPM_IMSA_RELEASE_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT16                          usLen;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  stSsEventInfo;
} IMSA_SPM_SS_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_ORIG_PARAM_STRU             stOrig;
}SPM_IMSA_CALL_ORIG_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_CALLED_NUM_STRU             stNewPtptNumber;                        /* �µĵ������绰 */
}SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* Cause Value of the Call Control */
}IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtCmd;
}SPM_IMSA_CALL_SUPS_CMD_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;          /* �������� */
} SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                  /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               aucReserved[1];
    TAF_CALL_DTMF_PARAM_STRU                                stDtmf;
}SPM_IMSA_CALL_START_DTMF_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               aucReserved[1];
    TAF_CALL_DTMF_PARAM_STRU                                stDtmf;
}SPM_IMSA_CALL_STOP_DTMF_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                                                  /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;                                  /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;
    MN_OPERATION_ID_T                                       ucOpId;
    MN_CALL_ID_T                                            ucCallId;                               /* �ݲ�ʹ�ã���������չ */

    TAF_CALL_DTMF_STATE_ENUM_UINT8                          enDtmfState;                            /* �ݲ�ʹ�ã���������չ */
    VOS_UINT8                                               ucDtmfCnt;                              /* �ݲ�ʹ�ã���������չ */
    VOS_UINT8                                               aucReserved[2];
    TAF_CS_CAUSE_ENUM_UINT32                                enCause;                                /* ������ */

}IMSA_SPM_CALL_START_DTMF_CNF_STRU;


typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU;


typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_STOP_DTMF_CNF_STRU;


typedef IMSA_SPM_CALL_START_DTMF_CNF_STRU  IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;
}SPM_IMSA_CALL_GET_CUDR_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;
}SPM_IMSA_CALL_GET_CLPR_REQ_STRU;


typedef struct
{
    MN_CALL_EVENT_ENUM_U32              enEventType;
    MN_CALL_INFO_STRU                   stCallInfo;
} MN_CALL_EVT_ORIG_CNF_STRU;


typedef MN_CALL_EVT_ORIG_CNF_STRU   MN_CALL_EVT_SUPS_CMD_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT16                          usLen;
    MN_CALL_EVENT_ENUM_U32              enEventType;
    MN_CALL_INFO_STRU                   stCallInfo;
} IMSA_SPM_CALL_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;                               /* �û�ID */
    VOS_UINT8                                               ucNumOfCalls;                           /* ��������ͨ���ĸ��� */
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;                              /* �������� */
    MN_CALL_INFO_PARAM_STRU                                 astCallInfo[MN_CALL_MAX_NUM];           /* ��������ͨ������Ϣ */
} IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU;


typedef struct
{
    VOS_UINT8                                               ucNumOfCalls;                           /* ��������ͨ���ĸ��� */
    VOS_UINT8                                               aucReserve[3];
    MN_CALL_INFO_PARAM_STRU                                 astCallInfo[MN_CALL_MAX_NUM];           /* ��������ͨ������Ϣ */
} IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;

    VOS_UINT8                           ucIsLocalAlertingFlag;                  /* �Ƿ�Ϊ���ز��Ż�������ʶ1:���ز��Ż�������0:�������*/
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType;                            /* codec type */
} IMSA_SPM_CHANNEL_INFO_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulRet;                                  /* MT_call&�ɹ�VOS_OK ��MO CALL����ʧ��ʱVOS_ERR */
    MN_CALL_REDIRECT_INFO               stRedirectInfo;                         /* IMS��ʱ��֧�֣��ظ�0 */
}IMSA_SPM_CALL_GET_CLPR_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    MN_CALL_ID_T                                    ucCallId;                     /* Call ID */
    MN_CALL_TYPE_ENUM_U8                            enSrcCallType;             /* Դ�������� */
    MN_CALL_TYPE_ENUM_U8                            enDestCallType;           /* Ŀ�ĺ������� */
    VOS_UINT8                                       aucReserved[2];
    MN_CALL_EMERGENCY_CAT_STRU                      stEmergencyCat;           /* Emergency Catory */
}IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* ��ǰ�������� */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* ������������ */
    VOS_UINT8                           aucReserved1[2];
}SPM_IMSA_CALL_MODIFY_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* ������ */
}IMSA_SPM_CALL_MODIFY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    MN_CALL_TYPE_ENUM_U8                enCurrCallType;                         /* ��ǰ�������� */
    MN_CALL_TYPE_ENUM_U8                enExpectCallType;                       /* ������������ */
    VOS_UINT8                           aucReserved1[2];
}SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CALL_ID_T                        callId;                                 /* Call ID */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* ������ */
}IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    MN_CALL_ID_T                                    callId;                     /* Call ID */
    SPM_IMSA_CALL_MODIFY_STATUS_ENUM_UINT8          enModifyStatus;             /* ��ǰ��MODIFY�Ĺ���״̬ */
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8                enVoiceDomain;              /* VOICE DOMAIN������ʼ����IMS�� */
    MN_CALL_TYPE_ENUM_U8                            enCurrCallType;             /* ��ǰ�������� */
    MN_CALL_TYPE_ENUM_U8                            enExpectCallType;           /* ������������ */
    TAF_CS_CAUSE_ENUM_UINT32                        enCause;                    /* �����룬����MODIFY_PROC_END���쳣ʱ��ʹ�� */
}IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_CALL_ECONF_DIAL_REQ_STRU        stDialReq;
}SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserved[1];
    TAF_CALL_ECONF_CALL_LIST_STRU       stEconfCalllist;                        /* ����μӶ෽ͨ�������ߵ���Ϣ */
}SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           ucCallId;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;
}IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU
 �ṹ˵��  : ��ǿ�Ͷ෽ͨ���������߻ظ����

  1.��    ��   : 2014��11��28��
    ��    ��   : f0179208
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           aucReserve[1];
    TAF_CS_CAUSE_ENUM_UINT32            enCause;
}IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU;


typedef SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU  SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                              ulMsgId;            /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                          usClientId;         /* �û�ID */
    MN_OPERATION_ID_T                                       ucOpId;
    VOS_UINT8                                               ucNumOfMaxCalls;
    VOS_UINT8                                               ucNumOfCalls;       /* ��������ͨ���ĸ��� */
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType;          /* �������� */
    VOS_UINT8                                               aucReserve[2];
    TAF_CALL_ECONF_INFO_PARAM_STRU                          astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* ��������ͨ������Ϣ */
} IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                                      ulMsgId;                    /* _H2ASN_Skip */
    MN_CLIENT_ID_T                                  usClientId;
    MN_OPERATION_ID_T                               ucOpId;
    VOS_UINT8                                       ucNumOfCalls;               /* ��������ͨ���ĸ��� */
    TAF_CALL_ECONF_INFO_PARAM_STRU                  astCallInfo[TAF_CALL_MAX_ECONF_CALLED_NUM];     /* ��������ͨ������Ϣ */
}IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export SPM_IMSA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          SPM_IMSA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}SPM_IMSA_INTERFACE_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    SPM_IMSA_INTERFACE_MSG_DATA           stMsgData;
} SpmImsaInterface_MSG;

/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
extern VOS_UINT32 IMSA_SpmGetCallInfo(IMSA_SPM_CALL_GET_CALL_INFO_IND_STRU *pstCallInfo);

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

#endif /* SPM_IMSA_INTERFACE_H */
