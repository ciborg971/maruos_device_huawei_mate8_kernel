
#ifndef  VC_MNTN_H
#define  VC_MNTN_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "PsTypeDef.h"
#include "AppVcApi.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ������� */
#define VC_INFO_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str)
#define VC_NORM_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str)
#define VC_WARN_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str)
#define VC_ERR_LOG(str)       TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str)

#define VC_INFO_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str, x)
#define VC_NORM_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define VC_WARN_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x)
#define VC_ERR_LOG1(str, x)   TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x)

#define VC_WARN_LOG2(str, x1, x2)   TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x1, x2)
#define VC_ERR_LOG2(str, x1, x2)    TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x1, x2)

/* ��װ��ά�ɲ��¼���Ϣͷ */
#define VC_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulEventLen)\
            (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pstMsg)->ulSenderPid     = WUEPS_PID_VC;\
            (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pstMsg)->ulReceiverPid   = WUEPS_PID_VC;\
            (pstMsg)->ulLength        = (ulEventLen);\
            (pstMsg)->enMsgId         = (enEventId)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum VC_MNTN_HOOK_MSG_ID_ENUM
{
    ID_VC_MNTN_HOOK_MSG_STATE_MGMT      = 0,                                    /* _H2ASN_MsgChoice VC_MNTN_STATE_MGMT_STRU */

    ID_VC_MNTN_HOOK_MSG_BUTT
};
typedef VOS_UINT32 VC_MNTN_HOOK_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               aucMsdData[APP_VC_MSD_DATA_LEN];     /* ���ڱ���APP�·���MSD���� */
    PS_BOOL_ENUM_UINT8                      enMsdFlag;                          /* ���ڼ�¼�Ƿ��·���MSD���� */
    PS_BOOL_ENUM_UINT8                      enInECall;                          /* ��ǰ�Ƿ���eCall���й����� */
    PS_BOOL_ENUM_UINT8                      enAllowSetMsdFlag;                  /* �Ƿ����������� */
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8    enEcallState;                       /* MSD����״̬ */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enNewEcallMode;                     /* ���ڱ�������APP�·���eCall������Ϣ(���ݴ���ģʽ) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enNewEcallVocConfig;                /* ���ڱ�������APP�·���eCall������Ϣ(�Ƿ��ڴ�������ʱ��������) */
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16       enCurrEcallMode;                    /* ���ڱ��浱ǰMEDʹ�õ�eCall������Ϣ(���ݴ���ģʽ) */
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16     enCurrEcallVocConfig;               /* ���ڱ��浱ǰMEDʹ�õ�eCall������Ϣ(�Ƿ��ڴ�������ʱ��������) */
    VOS_UINT32                              ulEcallDescription;                 /* MSD����״̬����,����ʾ�������MSD��ʱ�䴰���ȣ�����ֵ����λ�����룬��Χ��500~10000 */
}VC_MNTN_ECALL_CTX_STRU;


typedef struct
{
    VOS_UINT32                              ulInCall;                           /* ��ǰ�Ƿ��ں��й����� */
    VOS_UINT32                              ulVoiceTestFlag;
    VC_MNTN_ECALL_CTX_STRU                  stVcEcallCtx;
}VC_MNTN_HOOK_CTX_INFO;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VC_MNTN_HOOK_MSG_ID_ENUM_UINT32     enMsgId;                                /* _H2ASN_Skip *//* ��Ϣ���� */
    VC_MNTN_HOOK_CTX_INFO               stVcCtxInfo;                            /* VC״̬����ṹ */
} VC_MNTN_STATE_MGMT_STRU;

/*****************************************************************************
  7 OTHERS����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID NAS_MNTN_FailtoOpenCsChannel(
    VOS_UINT16                          usPort,
    VOS_UINT32                          ulOmOperResult
);
VOS_VOID NAS_MNTN_CsMedTimeOut(
    VOS_UINT32                          ulTimerId
);
VOS_VOID VC_MNTN_TraceEvent(
    VOS_VOID                           *pMsg
);
VOS_VOID VC_MNTN_TraceCtxInfo(VOS_VOID);

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VC_MNTN_HOOK_MSG_ID_ENUM_UINT32    enMsgId;                                /* _H2ASN_MsgChoice_Export VC_MNTN_HOOK_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                          aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_MNTN_HOOK_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} VC_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    VC_MNTN_MSG_DATA                    stMsgData;
} VcMntn_MSG;



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

#endif /* VC_MNTN_H */


