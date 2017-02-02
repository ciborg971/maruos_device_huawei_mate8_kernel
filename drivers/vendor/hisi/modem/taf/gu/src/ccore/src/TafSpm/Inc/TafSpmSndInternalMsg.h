
#ifndef _TAF_SPM_SND_INTERNAL_MSG_H_
#define _TAF_SPM_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafSpmCtx.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafInternalInterface.h"

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

enum TAF_SPM_SERVICE_CTRL_RESULT_ENUM
{
    TAF_SPM_SERVICE_CTRL_SUCC                                   = 0,
    TAF_SPM_SERVICE_CTRL_FAIL                                   = 1,
    TAF_SPM_SERVICE_CTRL_BUTT
};
typedef VOS_UINT32 TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32;


enum TAF_SPM_INTERNAL_MSG_ID_ENUM
{
    TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND               = ID_TAF_MNTN_MSG_SPM_BASE +0x100, /*_H2ASN_MsgChoice TAF_SPM_SERVICE_CTRL_RSLT_STRU */

    TAF_SPM_INTERNAL_DOMAIN_SEL_IND,                                                          /*_H2ASN_MsgChoice TAF_SPM_DOMAIN_SEL_IND_STRU */

    TAF_SPM_INTERNAL_MSG_BUTT
};
typedef VOS_UINT32 TAF_SPM_INTERNAL_MSG_ID_ENUM_UINT32;


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
    MSG_HEADER_STRU                             MsgHeader;                              /* ��Ϣͷ */
    TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32     enResult;                               /* SERVICE CTRL��� */
    VOS_UINT32                                  ulCause;                                /* ʧ��ʱЯ����ԭ��ֵ */
    VOS_UINT16                                  usClientId;                             /* ��Ӧ��client id */
    VOS_UINT8                                   aucRsv[2];
    TAF_SPM_ENTRY_MSG_STRU                      stEntryMsg;                             /* at��STK��SS���͵���Ϣ */
} TAF_SPM_SERVICE_CTRL_RSLT_STRU;

/* �ŵ�IMS�꿪�����湫��ʹ�� */

typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;
} TAF_SPM_DOMAIN_SEL_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID TAF_SPM_SndServiceCtrlRsltInd(
        TAF_SPM_SERVICE_CTRL_RESULT_ENUM_UINT32                 enRslt,
        VOS_UINT32                                              ulCause,
        VOS_UINT16                                              usClientId,
        TAF_SPM_ENTRY_MSG_STRU                                 *pstEntryMsg
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_SPM_SendMsgSmmaRsp(
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType,
    struct MsgCB                       *pstMsg
);
#endif

/* �ŵ�IMS�꿪�����湫��ʹ�� */
VOS_VOID TAF_SPM_SndInternalDomainSelectionInd(VOS_VOID);


#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_SPM_SndTafRelCallReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_CALL_REL_CALL_TYPE_ENUM_UINT8   enRelType
);
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

#endif


