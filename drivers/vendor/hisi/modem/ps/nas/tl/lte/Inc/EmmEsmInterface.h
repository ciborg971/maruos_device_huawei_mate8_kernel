

#ifndef __EMMESMINTERFACE_H__
#define __EMMESMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "LPSCommon.h"
#include "AppNasComm.h"

#include    "LnasErrlogInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/

#define EMM_ESM_MAX_EPS_BEARER_NUM       11

/*EMM->SM Command��Ϣǰ3���ֽں궨�� EMM->SM*/
#define EMM_ESM_MSG_ID_HEADER            PS_MSG_ID_EMM_TO_ESM_BASE

/*ESM ->EMM Command��Ϣǰ3���ֽں궨�� SM->EMM*/
#define ESM_EMM_MSG_ID_HEADER            PS_MSG_ID_ESM_TO_EMM_BASE

#define ESM_EMM_PLMN_ID_LEN             (3)
#define ESM_EMM_MAX_EQUPLMN_NUM         (16)

#define ESM_EMM_RELEASE_R11             (0x00000b00)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : EMM_ESM_MSG_TYPE_ENUM
 ö��˵��  : EMM��SM��Ϣ����
*****************************************************************************/
enum EMM_ESM_MSG_TYPE_ENUM
{
    /*��Ϣԭ��*/
    /*ESM ���͸�EMM����Ϣԭ��*/
    ID_EMM_ESM_EST_REQ                   = (0x01+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EST_REQ_STRU */
    ID_EMM_ESM_BEARER_STATUS_REQ         = (0x03+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_STATUS_REQ_STRU */
    ID_EMM_ESM_DATA_REQ                  = (0x05+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DATA_REQ_STRU */
    ID_EMM_ESM_REL_REQ                   = (0x07+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_REL_REQ_STRU */
    ID_EMM_ESM_PDN_CON_RSP               = (0x09+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_RSP_STRU */
    ID_EMM_ESM_PDN_CON_SUCC_REQ          = (0x0B+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_SUCC_REQ_STRU */
    ID_EMM_ESM_SUSPEND_RSP               = (0x0D+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_SUSPEND_RSP_STRU */
    ID_EMM_ESM_RESUME_RSP                = (0x0F+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_RESUME_RSP_STRU */
    ID_EMM_ESM_BEARER_MODIFY_REQ         = (0x11+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_MODIFY_REQ_STRU */
    ID_EMM_ESM_CLR_ESM_PROC_RES_NOTIFY   = (0x13+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU */
    ID_EMM_ESM_BEGIN_SESSION_NOTITY      = (0x15+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_BEGIN_SESSION_NOTIFY_STRU */
    ID_EMM_ESM_END_SESSION_NOTITY        = (0x16+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_END_SESSION_NOTIFY_STRU */
    ID_EMM_ESM_SAVE_ERRLOG_IND           = (0x19+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_SAVE_ERRLOG_IND_STRU */

    ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY    = (0x1a+ESM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU */

    /*EMM���͸�SM����Ϣԭ��*/
    ID_EMM_ESM_EST_CNF                   = (0x02+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EST_CNF_STRU */
    ID_EMM_ESM_STATUS_IND                = (0x04+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_STATUS_IND_STRU */
    ID_EMM_ESM_DATA_IND                  = (0x06+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DATA_IND_STRU */
    ID_EMM_ESM_REL_IND                   = (0x08+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_REL_IND_STRU */
    ID_EMM_ESM_PDN_CON_IND               = (0x0A+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PDN_CON_IND_STRU */
    ID_EMM_ESM_BEARER_STATUS_IND         = (0x0C+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_BEARER_STATUS_IND_STRU */
    ID_EMM_ESM_SUSPEND_IND               = (0x0D+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_SUSPEND_IND_STRU */
    ID_EMM_ESM_RESUME_IND                = (0x10+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_RESUME_IND_STRU */
    ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND  = (0x12+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU */
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ID_EMM_ESM_REPLAY_EXPORT_CTX_IND     = (0x14+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_EXPORT_CTX_IND_STRU */
    /*PC REPLAY MODIFY BY LEILI END*/
    ID_EMM_ESM_STOP_NOTIFY_IND          = (0x15+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_STOP_NOTIFY_IND_STRU */

    ID_EMM_ESM_START_NOTIFY_IND          = (0x16+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_START_NOTIFY_IND_STRU */
    ID_EMM_ESM_PLMN_CHANGE_IND           = (0x17+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_PLMN_CHANGE_IND_STRU */

    ID_EMM_ESM_DATA_CNF                  = (0x18+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice  EMM_ESM_DATA_CNF_STRU*/

    ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY    = (0x19+EMM_ESM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU */


    ID_EMM_ESM_BUTT
};
typedef VOS_UINT32 EMM_ESM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_PDN_CON_RSLT_ENUM
 ö��˵��  : PDN��������Ľ������
*****************************************************************************/
enum EMM_ESM_PDN_CON_RSLT_ENUM
{
    EMM_ESM_PDN_CON_RSLT_SUCC            = 0x00,
    EMM_ESM_PDN_CON_RSLT_FAIL            = 0x01,
    EMM_ESM_PDN_CON_RSLT_BUTT
};
typedef VOS_UINT32 EMM_ESM_PDN_CON_RSLT_ENUM_UINT32;

enum EMM_ESM_PDN_CON_REQ_TYPE_ENUM
{
    EMM_ESM_PDN_CON_REQ_TYPE_INITIAL              = 0,    /* ���ݳ��������жϸ���initial��emergency */
    EMM_ESM_PDN_CON_REQ_TYPE_HANDOVER           = 1,    /* ��handover */
    EMM_ESM_PDN_CON_REQ_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_ATTACH_STATUS_ENUM
 ö��˵��  : SMע��״̬������
*****************************************************************************/
enum EMM_ESM_ATTACH_STATUS_ENUM
{
    EMM_ESM_ATTACH_STATUS_DETACHED       = 0x00,
    EMM_ESM_ATTACH_STATUS_ATTACHED       = 0x01,
    EMM_ESM_ATTACH_STATUS_AREA_RE_ENTRY  = 0x02,
    EMM_ESM_ATTACH_STATUS_EMC_ATTACHING  = 0x03,
    EMM_ESM_ATTACH_STATUS_BUTT
};
typedef VOS_UINT32 EMM_ESM_ATTACH_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_ATTACH_RESULT_ENUM
 ö��˵��  : SMע����������
*****************************************************************************/
enum EMM_ESM_ATTACH_RESULT_ENUM
{
    EMM_ESM_ATTACH_RESULT_FAIL          = 0x00,
    EMM_ESM_ATTACH_RESULT_SUCC          = 0x01,

    EMM_ESM_ATTACH_RESULT_BUTT
};
typedef VOS_UINT32 EMM_ESM_ATTACH_RESULT_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_BEARER_CNTXT_MOD_ENUM
 ö��˵��  : ESM�޸ĳ��������ĵķ�ʽ
*****************************************************************************/
enum EMM_ESM_BEARER_CNTXT_MOD_ENUM
{
    EMM_ESM_BEARER_CNTXT_MOD_MUTUAL         = 0x00, /*�ɹ������ཻ�����޸ĳ���������*/
    EMM_ESM_BEARER_CNTXT_MOD_LOCAL          = 0x01, /*ESM�����޸ĳ���������*/

    EMM_ESM_BEARER_CNTXT_MOD_BUTT
};
typedef VOS_UINT32 EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_UP_SINGNAL_PENDING_ENUM
 ö��˵��  : ESM�Ƿ����������������
*****************************************************************************/
enum EMM_ESM_UP_SINGNAL_PENDING_ENUM
{
    EMM_ESM_NO_UP_SINGNAL_PENDING      = 0x00, /*������������������*/
    EMM_ESM_UP_SINGNAL_PENDING         = 0x01, /*����������������*/

    EMM_ESM_UP_SINGNAL_PENDING_BUTT
};
typedef VOS_UINT32 EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_RSLT_TYPE_ENUM
 ö��˵��  : ESM�ظ�EMM��Ϣ���ö��
*****************************************************************************/
enum EMM_ESM_RSLT_TYPE_ENUM
{
    EMM_ESM_RSLT_TYPE_SUCC             = 0x00, /*�ɹ�*/
    EMM_ESM_RSLT_TYPE_FAIL             = 0x01, /*ʧ��*/

    EMM_ESM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ESM_RSLT_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ESM_RAT_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : UE֧�ֵĽ��뼼������
*****************************************************************************/
enum EMM_ESM_RAT_TYPE_ENUM
{
    /* ������ĳ�ֻ������н��뼼�� */
    EMM_ESM_RAT_NONE                = 0,
    EMM_ESM_RAT_LTE_FDD             = 1,
    EMM_ESM_RAT_LTE_TDD             = 2,
    EMM_ESM_RAT_LTE_ALL             = 3,
    EMM_ESM_RAT_UTRAN_FDD           = 4,
    EMM_ESM_RAT_UTRAN_TDD           = 8,
    EMM_ESM_RAT_UTRAN_ALL           = 12,
    EMM_ESM_RAT_GERAN               = 16,
    EMM_ESM_RAT_ALL                 = 31,
    EMM_ESM_RAT_BUTT
};
typedef VOS_UINT8 EMM_ESM_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : ESM_EMM_SESSION_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum EMM_ESM_SESSION_TYPE_ENUM
{
    EMM_ESM_SESSION_TYPE_ESM = 0,/*��������ϸ�ֿ���չ*/
    EMS_ESM_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 EMM_ESM_SESSION_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : EMM_ESM_SEND_RSLT_ENUM
 ö��˵��  :
*****************************************************************************/
enum EMM_ESM_SEND_RSLT_ENUM
{
    EMM_ESM_SEND_RSLT_SUCCESS    = 0,
    EMM_ESM_SEND_RSLT_EMM_DISCARD,
    EMM_ESM_SEND_RSLT_FAILURE_HO,
    EMM_ESM_SEND_RSLT_FAILURE_CONN_REL,
    EMM_ESM_SEND_RSLT_FAILURE_CTRL_NOT_CONN,
    EMM_ESM_SEND_RSLT_FAILURE_TXN,
    EMM_ESM_SEND_RSLT_FAILURE_RLF,
    EMM_ESM_SEND_RSLT_NORF,
    EMM_ESM_SEND_RSLT_BUTT
};
typedef VOS_UINT32 EMM_ESM_SEND_RSLT_ENUM_UINT32;

/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : EMM_ESM_FAIL_CAUSE_NOTIFY_STRU
 �ṹ˵��  : EMM_ESM_FAIL_CAUSE_NOTIFY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           ucEsmCause;           /* ESM Cause*/
    VOS_UINT8                           ucRsv[3];
} EMM_ESM_FAIL_CAUSE_NOTIFY_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_MSG_STRU
 �ṹ˵��  : EMM_ESM_MSG_STRU�տ���Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulEsmMsgSize;
    VOS_UINT8                          aucEsmMsg[4];       /* ��Ϣ��ǰ�ĸ��ֽ�����             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}EMM_ESM_MSG_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ESM_EST_REQ_STRU
 �ṹ˵��  : EMM_ESM_EST_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/    /*msg ID*/

    VOS_UINT32                          ulOpId;              /* Operation Id */

    VOS_UINT32                          ulIsEmcType;         /* �Ƿ��ǽ���PDN�������� */
    EMM_ESM_MSG_STRU                    stEsmMsg;            /* SM MSG */
} EMM_ESM_EST_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_EST_CNF_STRU
 �ṹ˵��  : EMM_ESM_EST_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    EMM_ESM_ATTACH_RESULT_ENUM_UINT32   ulEstRst;           /*ATTACH ���:    "1:success,0:fail"*/
} EMM_ESM_EST_CNF_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ESM_BEARER_STATUS_REQ_STRU
 �ṹ˵��  : EMM_ESM_BEARER_STATUS_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    EMM_ESM_BEARER_CNTXT_MOD_ENUM_UINT32 enBearerCntxtMod;  /*�Ƿ񱾵��޸��˳���������*/
    VOS_UINT32                          ulExistEmcPdnFlag;  /*��ǰ�Ƿ���ڽ���PDN����*/
    VOS_UINT32                          ulEpsIdNum;         /*��ǰ�Ѽ����EPSID����*/
    VOS_UINT32                          aulEsmEpsId[EMM_ESM_MAX_EPS_BEARER_NUM];     /*�����Ѽ����EPS BID  */
} EMM_ESM_BEARER_STATUS_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_BEARER_STATUS_IND_STRU
 �ṹ˵��  : EMM_ESM_BEARER_STATUS_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT32                          ulEpsIdNum;         /* ��ǰ�Ѽ����EPSID���� */
    VOS_UINT32                          aulEsmEpsId[EMM_ESM_MAX_EPS_BEARER_NUM];     /*�����Ѽ����EPS BID  */
} EMM_ESM_BEARER_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_DATA_REQ_STRU
 �ṹ˵��  : EMM_ESM_DATA_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */

    VOS_UINT32                          ulOpId;              /* Operation Id */

    VOS_UINT32                          ulIsEmcType;         /* �Ƿ��ǽ���PDN�������� */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SMģ����SAEЯ��������Ϣ*/
}EMM_ESM_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_DATA_IND_STRU
 �ṹ˵��  : EMM_ESM_DATA_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */

    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SMģ����SAEЯ��������Ϣ*/
}EMM_ESM_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_REL_REQ_STRU
 �ṹ˵��  : EMM_ESM_REL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT32                           ulReserved;         /* ������ */
}EMM_ESM_REL_REQ_STRU;

typedef EMM_ESM_REL_REQ_STRU EMM_ESM_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_PDN_CON_SUCC_REQ_STRU
 �ṹ˵��  : EMM_ESM_PDN_CON_SUCC_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* SM MSG :SMģ����SAEЯ��������Ϣ*/
}EMM_ESM_PDN_CON_SUCC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_PDN_CON_IND_STRU
 �ṹ˵��  : EMM_ESM_PDN_CON_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;            /*_H2ASN_Skip*/           /* ��Ϣͷ */
    VOS_UINT32                           ulCId;             /*����������Id */ /*range:0~31*/
    EMM_ESM_PDN_CON_REQ_TYPE_ENUM_UINT32 enPdnReqType;      /* EMMָ��ESM�����PDN������������ */
}EMM_ESM_PDN_CON_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_PDN_CON_RSP_STRU
 �ṹ˵��  : EMM_ESM_PDN_CON_RSP_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */

    EMM_ESM_PDN_CON_RSLT_ENUM_UINT32    ulRst;              /* ��Ӧ��� ,   0:succ,1:fail  */
    EMM_ESM_MSG_STRU                    stEsmMsg;            /* ATTACH �����а�����PDN_CON_REQ��Ϣ*/
} EMM_ESM_PDN_CON_RSP_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ESM_STATUS_IND_STRU
 �ṹ˵��  : EMM_ESM_STATUS_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    EMM_ESM_ATTACH_STATUS_ENUM_UINT32   enEMMStatus;        /*��ǰEMMע��״̬ */
                                                            /*0:DETACHED,1:ATTACHED*/
}EMM_ESM_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ����: EMM_ESM_SUSPEND_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_SUSPEND_IND_STRU;

/*****************************************************************************
 �ṹ����: EMM_ESM_SUSPEND_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:ESM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt;
} EMM_ESM_SUSPEND_RSP_STRU;

/*****************************************************************************
 �ṹ����: EMM_ESM_RESUME_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_RESUME_IND_STRU;


/*****************************************************************************
 �ṹ����: EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:EMM->ESM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
} EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU;


/*****************************************************************************
 �ṹ����: EMM_ESM_RESUME_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:ESM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_RSLT_TYPE_ENUM_UINT32       enRslt;
} EMM_ESM_RESUME_RSP_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ESM_BEARER_MODIFY_REQ_STRU
 �ṹ˵��  : EMM_ESM_BEARER_MODIFY_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT32                          ulEpsId;         /* ��ǰ�޸ĵ�EPSID*/
} EMM_ESM_BEARER_MODIFY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_ERRLOG_STRU
 �ṹ˵��  : ESM����EMM��ERRLOG��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulEsmMsgSize;
    VOS_UINT8                          aucEsmMsg[4];       /* ERRLOG��ǰ�ĸ��ֽ�����*/
}EMM_ESM_ERRLOG_STRU;

/*****************************************************************************
�ṹ��    : EMM_ESM_SAVE_ERRLOG_IND_STRU
�ṹ˵��  : EMM_ESM_SAVE_ERRLOG_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;      /*_H2ASN_Skip*/

    EMM_ESM_ERRLOG_STRU                             stEmmEsmErrlog;
}EMM_ESM_SAVE_ERRLOG_IND_STRU;

/*****************************************************************************
 �ṹ��    : ESM_EMM_SESSION_NOTIFY_STRU
 �ṹ˵��  : ESM_EMM_SESSION_NOTIFY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                /*_H2ASN_Skip*/
    VOS_UINT32                                      ulMsgId;      /*_H2ASN_Skip*/

    EMM_ESM_SESSION_TYPE_ENUM_UINT8                 enSessionType;
    VOS_UINT8                                       aucReserved[3];
} EMM_ESM_SESSION_NOTIFY_STRU;

typedef EMM_ESM_SESSION_NOTIFY_STRU     EMM_ESM_BEGIN_SESSION_NOTIFY_STRU;
typedef EMM_ESM_SESSION_NOTIFY_STRU     EMM_ESM_END_SESSION_NOTIFY_STRU;


/*****************************************************************************
�ṹ��    : EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU
�ṹ˵��  : EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                    /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;      /*_H2ASN_Skip*/

    VOS_UINT8                           aucRsv[4];
}EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU;



/*****************************************************************************
 �ṹ��    : EMM_ESM_DATA_CNF_STRU
 �ṹ˵��  : EMM_ESM_DATA_CNF_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;            /*_H2ASN_Skip*/

    EMM_ESM_SEND_RSLT_ENUM_UINT32               enDataCnfRst;
    VOS_UINT32                                  ulEsmEmmOpId;
}EMM_ESM_DATA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU
 �ṹ˵��  : EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpId;              /*Operation Id*/
    VOS_UINT32                          ulIsEmcType;         /*�Ƿ��ǽ���PDN��Ӧ��ESM����*/
} EMM_ESM_CLR_ESM_PROC_RES_NOTIFY_STRU;

/*PC REPLAY MODIFY BY LEILI BEGIN*/
/*****************************************************************************
 �ṹ��    : EMM_ESM_EXPORT_CTX_IND_STRU
 �ṹ˵��  : EMM_ESM_EXPORT_CTX_IND_STRU���ݽṹ,PC�ط���Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT8                           aucRsv[4];

}EMM_ESM_EXPORT_CTX_IND_STRU;
/*****************************************************************************
�ṹ��    :ESM_EMM_PLMN_ID_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[ESM_EMM_PLMN_ID_LEN];
    VOS_UINT8                           ucRsv;
}ESM_EMM_PLMN_ID_STRU;

/*****************************************************************************
�ṹ��    :ESM_EMM_EPLMN_LIST_STRU��
Э����  :
ASN.1���� :
�ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEplmnNum;

    ESM_EMM_PLMN_ID_STRU                astEplmnList[ESM_EMM_MAX_EQUPLMN_NUM];
}ESM_EMM_EPLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : ESM_EMM_CURRENT_CAMP_INFO_STRU
 �ṹ˵��  : ESM_EMM_CURRENT_CAMP_INFO_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    ESM_EMM_PLMN_ID_STRU                stPlmnId;
}ESM_EMM_CURRENT_CAMP_INFO_STRU;


/*PC REPLAY MODIFY BY LEILI END*/
/*****************************************************************************
 �ṹ��    : EMM_ESM_STOP_NOTIFY_IND_STRU
 �ṹ˵��  : EMM_ESM_STOP_NOTIFY_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT8                           aucRsv[4];

}EMM_ESM_STOP_NOTIFY_IND_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ESM_START_NOTIFY_IND_STRU
 �ṹ˵��  : EMM_ESM_START_NOTIFY_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_START_NOTIFY_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_PLMN_CHANGE_IND_STRU
 �ṹ˵��  : EMM_ESM_PLMN_CHANGE_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/            /* ��Ϣͷ */
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_PLMN_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU
 �ṹ˵��  : EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucRsv[4];
}EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU;


typedef struct
{
    EMM_ESM_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export EMM_ESM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          EMM_ESM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_ESM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    EMM_ESM_MSG_DATA                     stMsgData;
}EmmEsmInterface_MSG;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulDsdsRFSharedFlag;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32 NAS_ESM_IsUpSingnalPending( VOS_VOID );
extern VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID);

extern VOS_UINT32 NAS_ESM_DecodeNwEsmMsgGetEsmCause
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulMsgLen,
    VOS_UINT8                          *enEsmCause
);

extern VOS_VOID NAS_EMM_GetCurrentCampInfo
(
    ESM_EMM_PLMN_ID_STRU *pstCurrentCampInfo
);
extern VOS_VOID NAS_EMM_GetEplmnList
(
    NAS_ESM_PLMN_LIST_STRU *pstEplmnList
);
extern VOS_UINT32 NAS_EMM_GetNasRelease(VOS_VOID);
extern VOS_UINT16 NAS_EMM_GetErrLogAlmLevel(LNAS_OM_ERRLOG_ALM_ID_ENUM_UINT16 enAlmId);
extern VOS_UINT32 NAS_EMM_IsErrLogNeedRecord(VOS_UINT16 usLevel);
/* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, Begin */
extern VOS_UINT32 NAS_LMM_GetPositionInfo(LNAS_OM_ERRLOG_POSITION_INFO_STRU *pstPositionInfo);
/* Add by y00307272 for LNAS_POSITION_INFO, 2015-09-29, End */

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

#endif /* end of EmmEsmInterface.h */





