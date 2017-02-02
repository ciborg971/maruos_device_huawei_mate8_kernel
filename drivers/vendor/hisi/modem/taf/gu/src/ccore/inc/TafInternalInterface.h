

#ifndef __TAF_INTERNAL_INTERFACE_H__
#define __TAF_INTERNAL_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafMntn.h"
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnMsgApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_INTERNAL_MSG_TYPE_ENUM
 �ṹ˵��  : TAF PID�ڲ�����ҵ��ģ��֮�����Ϣ�ӿ�ö��
*****************************************************************************/
enum TAF_INTERNAL_MSG_TYPE_ENUM
{
    TAF_CALL_TAF_REL_CALL_REQ                               = ID_TAF_CALL_INTERNAL_BASE, /* _H2ASN_MsgChoice TAF_CALL_TAF_REL_CALL_REQ_STRU */
    TAF_CALL_TAF_REL_CALL_CNF                               ,                            /* _H2ASN_MsgChoice TAF_CALL_TAF_REL_CALL_CNF_STRU */

    /* MSG<->SPM */
    ID_TAF_SPM_SMMA_IND                                     = ID_TAF_MSG_INTERNAL_BASE,       /* _H2ASN_MsgChoice TAF_SPM_SMMA_IND_STRU */
    ID_TAF_SPM_MSG_REPORT_IND                               ,                                 /* _H2ASN_MsgChoice TAF_SPM_MSG_REPORT_IND_STRU */
    ID_TAF_SPM_SMMA_RSP                                     ,                                 /* _H2ASN_MsgChoice TAF_SPM_SMMA_RSP_STRU */

    ID_TAF_SPM_MSG_CHECK_RESULT_IND,                                            /* _H2ASN_MsgChoice TAF_SPM_MSG_CHECK_RESULT_IND_STRU */

    ID_TAF_INTERNAL_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_INTERNAL_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_CALL_REL_CALL_TYPE_ENUM_UINT8
 �ṹ˵��  :
             0: TAF_CALL_REL_CALL_ALL_NORMAL    �ͷ�������������
*****************************************************************************/
enum TAF_CALL_REL_CALL_TYPE_ENUM
{
    TAF_CALL_REL_CALL_ALL_NORMAL,

    TAF_CALL_REL_CALL_BUTT
};
typedef VOS_UINT8 TAF_CALL_REL_CALL_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_SMS_MO_TYPE_ENUM_UINT8
 �ṹ˵��  :
             0: TAF_SMS_MO_TYPE_MO          AT����Ķ���
             1: TAF_SMS_MO_TYPE_SMMA        SMMA
             2: TAF_SMS_MO_TYPE_BUFFER_STK  STK����Ķ���
*****************************************************************************/
enum TAF_SMS_MO_TYPE_ENUM
{
    TAF_SMS_MO_TYPE_MO,
    TAF_SMS_MO_TYPE_SMMA,
    TAF_SMS_MO_TYPE_BUFFER_STK,
    TAF_SMS_MO_TYPE_MAX
};
typedef VOS_UINT8 TAF_SMS_MO_TYPE_ENUM_UINT8;

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
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      usClientId;                             /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;                                 /* Operation ID */
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType;                              /* �ͷź������� */
}TAF_CALL_TAF_REL_CALL_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      usClientId;                             /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;                                 /* Operation ID */
    VOS_UINT8                           aucReserve[1];                          /* ���� */
    TAF_CS_CAUSE_ENUM_UINT32            enCause;                                /* �����ͷ�ԭ��ֵ */
}TAF_CALL_TAF_REL_CALL_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve[1];                         /* ���� */
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
}TAF_SPM_SMMA_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve[1];                          /* ���� */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType;
}TAF_SPM_SMMA_RSP_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      usClientId;                            /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;                                /* Operation ID */
    TAF_SMS_MO_TYPE_ENUM_UINT8          enSmsMoType;                           /* ����MO type */
    VOS_UINT8                           ucReportFlag;                          /* SMMA report��־ */
    MN_OPERATION_ID_T                   ucBcOpId;                              /* �㲥OPID */
    VOS_UINT8                           aucReserve[2];                         /* ����λ */
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enSignallingType;                      /* report��Ϣ�������� */
    MN_MSG_SUBMIT_RPT_EVT_INFO_STRU     stRptEvtInfo;                          /* ����report�¼���Ϣ */
}TAF_SPM_MSG_REPORT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    TAF_MSG_ERROR_ENUM_UINT32           enRslt;                                 /* ����� */
    MN_CLIENT_ID_T                      usClientId;                             /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;                                 /* Operation ID */
    VOS_UINT8                           aucReserve[1];                          /* ����λ */
}TAF_SPM_MSG_CHECK_RESULT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve[1];                         /* ���� */
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
}TAF_INTERNAL_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/* ASN�����ṹ */
typedef struct
{
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_INTERNAL_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_INTERNAL_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}TAF_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_INTERNAL_MSG_DATA               stMsgData;
}TafInternal_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/






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

#endif /* end of TafInternalInterface.h */



