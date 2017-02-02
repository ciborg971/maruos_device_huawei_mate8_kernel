

#ifndef __EMMRABMINTERFACE_H__
#define __EMMRABMINTERFACE_H__

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

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define EMM_ERABM_MAX_EPSB_NUM           11

/*EMM->RABM Command��Ϣǰ3���ֽں궨�� EMM->RABM*/
#define EMM_ERABM_MSG_ID_HEADER          PS_MSG_ID_EMM_TO_RABM_BASE

/*RABM->EMM Command��Ϣǰ3���ֽں궨�� RABM->EMM*/
#define ERABM_EMM_MSG_ID_HEADER          PS_MSG_ID_RABM_TO_EMM_BASE

#define ERABM_EMM_RELEASE_R11             (0x00000b00)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : EMM_ERABM_MSG_TYPE_ENUM
 ö��˵��  : EMM��RABM��Ϣ����
*****************************************************************************/
enum EMM_ERABM_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/
    /* RABM����EMM��ԭ�� */
    ID_EMM_ERABM_REEST_REQ               = (0x02+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REEST_REQ_STRU */
    ID_EMM_ERABM_DRB_SETUP_IND           = (0x04+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_DRB_SETUP_IND_STRU */
    ID_EMM_ERABM_REL_REQ                 = (0x06+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REL_REQ_STRU */
    ID_EMM_ERABM_SUSPEND_RSP             = (0x08+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_SUSPEND_RSP_STRU */
    ID_EMM_ERABM_RESUME_RSP              = (0x0a+ERABM_EMM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RESUME_RSP_STRU */

    /* EMM����RABM��ԭ�� */
    ID_EMM_ERABM_REEST_IND               = (0x01+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REEST_IND_STRU */
    ID_EMM_ERABM_REL_IND                 = (0x03+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_REL_IND_STRU */
    ID_EMM_ERABM_RRC_CON_REL_IND         = (0x05+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RRC_CON_REL_IND_STRU */
    ID_EMM_ERABM_SUSPEND_IND             = (0x07+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_SUSPEND_IND_STRU */
    ID_EMM_ERABM_RESUME_IND              = (0x09+EMM_ERABM_MSG_ID_HEADER),/* _H2ASN_MsgChoice EMM_ERABM_RESUME_IND_STRU */

    ID_EMM_ERABM_BUTT
};
typedef VOS_UINT32 EMM_ERABM_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ERABM_REEST_STATE_ENUM_UINT32
 ö��˵��  : reest��״̬����
*****************************************************************************/
enum EMM_ERABM_REEST_STATE_ENUM
{
    EMM_ERABM_REEST_STATE_SUCC          = 0x00,             /*SR�ɹ�*/
    EMM_ERABM_REEST_STATE_FAIL,                             /*SRʧ��*/
    EMM_ERABM_REEST_STATE_INITIATE,                         /*SR����*/

    EMM_ERABM_REEST_STATE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_REEST_STATE_ENUM_UINT32;
/*****************************************************************************
 ö����    : EMM_ERABM_REL_CAUSE_ENUM
 ö��˵��  : �ͷ�ԭ��ֵ
*****************************************************************************/
enum EMM_ERABM_REL_CAUSE_ENUM
{
    EMM_ERABM_REL_CAUSE_NULL          = 0x00,
    EMM_ERABM_REL_CAUSE_NO_RF,                     /* �ͷ�ԭ��Ϊno rf */

    EMM_ERABM_REL_CAUSE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_REL_CAUSE_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ERABM_UP_DATA_PENDING_ENUM
 ö��˵��  : RABM�Ƿ����������������
*****************************************************************************/
enum EMM_ERABM_UP_DATA_PENDING_ENUM
{
    EMM_ERABM_NO_UP_DATA_PENDING      = 0x00, /*������������������*/
    EMM_ERABM_UP_DATA_PENDING         = 0x01, /*����������������*/

    EMM_ERABM_UP_DATA_PENDING_BUTT
};
typedef VOS_UINT32 EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMM_ERABM_RSLT_TYPE_ENUM
 ö��˵��  : RABM�ظ�EMM��Ϣ���ö��
*****************************************************************************/
enum EMM_ERABM_RSLT_TYPE_ENUM
{
    EMM_ERABM_RSLT_TYPE_SUCC             = 0x00, /*�ɹ�*/
    EMM_ERABM_RSLT_TYPE_FAIL             = 0x01, /*ʧ��*/

    EMM_ERABM_RSLT_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_RSLT_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����   : EMM_ERABM_SYS_CHNG_TYPE_ENUM
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ϵͳ���������
*****************************************************************************/
enum EMM_ERABM_SYS_CHNG_TYPE_ENUM
{
    EMM_ERABM_SYS_CHNG_TYPE_RESEL       = 0,
    EMM_ERABM_SYS_CHNG_TYPE_HO,
    EMM_ERABM_SYS_CHNG_TYPE_CCO,
    EMM_ERABM_SYS_CHNG_TYPE_REDIR,

    EMM_ERABM_SYS_CHNG_TYPE_RESEL_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_HO_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_CCO_REVERSE,
    EMM_ERABM_SYS_CHNG_TYPE_REDIR_REVERSE,

    EMM_ERABM_SYS_CHNG_TYPE_BUTT
};
typedef VOS_UINT32 EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32;


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : EMM_ERABM_REEST_REQ_STRU
 �ṹ˵��  : EMM_ERABM_REEST_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{/* lihong00150010 emergency tau&service begin */
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulIsEmcType;
} EMM_ERABM_REEST_REQ_STRU;
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 �ṹ��    : EMM_ERABM_DRB_SETUP_IND_STRU
 �ṹ˵��  : EMM_ERABM_DRB_SETUP_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;           /*_H2ASN_Skip*/
} EMM_ERABM_DRB_SETUP_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ERABM_REL_REQ_STRU
 �ṹ˵��  : EMM_ERABM_REL_REQ_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* ��Ϣͷ*/
    VOS_UINT32                           ulReserved;         /* ������*/
}EMM_ERABM_REL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ERABM_REL_IND_STRU
 �ṹ˵��  : EMM_ERABM_REL_IND_STRU���ݽṹ
*****************************************************************************/
typedef EMM_ERABM_REL_REQ_STRU EMM_ERABM_REL_IND_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ERABM_RRC_CON_REL_IND_STRU
 �ṹ˵��  : EMM_ERABM_RRC_CON_REL_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/            /* ��Ϣͷ*/
    EMM_ERABM_REL_CAUSE_ENUM_UINT32      enRelCause;        /* �����ͷ�ԭ�� */
}EMM_ERABM_RRC_CON_REL_IND_STRU;


/*****************************************************************************
 �ṹ��    : EMM_ERABM_REEST_IND_STRU
 �ṹ˵��  : EMM_ERABM_REEST_IND_STRU���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/                                          /*_H2ASN_Skip*/
    VOS_UINT32                           ulMsgId;           /*_H2ASN_Skip*/
    EMM_ERABM_REEST_STATE_ENUM_UINT32     enReEstState;
} EMM_ERABM_REEST_IND_STRU;

/*****************************************************************************
 �ṹ����: EMM_ERABM_SUSPEND_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:EMM->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32 enSysChngType;

    VOS_UINT8                           aucRsv[4];
} EMM_ERABM_SUSPEND_IND_STRU;

/*****************************************************************************
 �ṹ����: EMM_ERABM_SUSPEND_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:RABM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt;
} EMM_ERABM_SUSPEND_RSP_STRU;

/*****************************************************************************
 �ṹ����: EMM_ERABM_RESUME_IND_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:EMM->RABM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_SYS_CHNG_TYPE_ENUM_UINT32 enSysChngType;

    VOS_UINT8                           aucRsv[4];
} EMM_ERABM_RESUME_IND_STRU;


/*****************************************************************************
 �ṹ����: EMM_ERABM_RESUME_RSP_STRU
 Э����:
 ASN.1 ����:
 �ṹ˵��:RABM->EMM
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/

    EMM_ERABM_RSLT_TYPE_ENUM_UINT32      enRslt;
} EMM_ERABM_RESUME_RSP_STRU;


typedef struct
{
    EMM_ERABM_MSG_TYPE_ENUM_UINT32       enMsgId;            /*_H2ASN_MsgChoice_Export EMM_ERABM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          EMM_ERABM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}EMM_ERABM_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    EMM_ERABM_MSG_DATA                     stMsgData;
}EmmRabmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern EMM_ERABM_UP_DATA_PENDING_ENUM_UINT32 NAS_ERABM_IsDataPending( VOS_VOID );
extern VOS_VOID NAS_EMM_SaveMoSerStartTimeStamp(VOS_VOID);

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

#endif /* end of RabmEmmInterface.h */
