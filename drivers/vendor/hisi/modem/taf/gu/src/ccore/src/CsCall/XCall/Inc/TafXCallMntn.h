

#ifndef __TAF_X_CALL_MNTN_H__
#define __TAF_X_CALL_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"


#include "TafMntn.h"
#include "TafXCallCtx.h"

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


enum TAF_XCALL_MNTN_MSG_ID_ENUM
{
    ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND   = ID_TAF_MNTN_XCALL_BASE,             /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_CALL_INFO_STRU */
    ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT,                                        /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU*/
    /* Added by h00313353 for Iteration 17, 2015-8-7, begin */
    ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD,
    /* Added by h00313353 for Iteration 17, 2015-8-7, end */
    ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL,                    /*_H2ASN_MsgChoice  TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU*/
    ID_TAF_XCALL_MNTN_MSG_ID_BUTT
};
typedef VOS_UINT32 TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32;


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
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_CALL_ENTITY_STRU          astCallEntity[TAF_XCALL_CALL_ENTITY_MAX_NUM];
}TAF_XCALL_MNTN_LOG_CALL_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    TAF_XCALL_SUPS_CMD_MGMT_STRU        stSupsCmdMgmt;
}TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU;

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT����Ϣ�ṹ
 1.��    ��   : 2015��08��09��
   ��    ��   : h00313353
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulEmcRedialPeriod;                      /* �������ز���ʱ��ʱ�� */
} TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU;

/* Added by h00313353 for Iteration 17, 2015-8-7, end */

/*****************************************************************************
 �ṹ��    : TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU
 �ṹ˵��  : ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL����Ϣ�ṹ
 1.��    ��   : 2015��08��18��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulStartAndStopContDtmfInterval;         /* Stop Cont DTMF ��Start Cont DTMF��Ϣ���ͼ����ʱ��ʱ�� */
} TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32   enMsgId;            /* _H2ASN_MsgChoice_Export TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_XCALL_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_XCALL_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_XCALL_MNTN_MSG_DATA             stMsgData;
}TAF_XCALL_MNTN_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID);
VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID);

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID);
/* Added by h00313353 for Iteration 17, 2015-8-7, end */

VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID);

/* Deleted by wx270776 for OM�ں�, 2015-6-28, begin */
/* Deleted by wx270776 for OM�ں�, 2015-6-28, end */
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

#endif /* end of TafXCallMntn.h */
