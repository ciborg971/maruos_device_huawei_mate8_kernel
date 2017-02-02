
#ifndef  VC_COMM_H
#define  VC_COMM_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnComm.h"
#include "VcCodecInterface.h"
#include "VcCallInterface.h"

/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define NV_COPY_DATA_OFFSET                     (80)
#define VC_VOLUME_DEFAULT_VALUE                 (-6)

/*�ط�����ϢID*/
#define EVT_NAS_VC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa         /* ΪPC���̻طŶ������Ϣ */

#define APP_VC_VOICE_TEST_FLAG_DEFALUT                   (0x0)                  /* Ƶ�ײ���ģʽ��־Ĭ��ֵ��Ĭ�ϲ�����Ƶ�ײ���ģʽ */
#define APP_VC_VOICE_TEST_FLAG_ENABLE                    (0x55aa55aa)           /* 0x55aa55aaֵƵ�ײ���ģʽ���� */
#define APP_VC_VOICE_NORMAL_MODE_IN_QUICK_START          (0x34343434)           /* 0x34343434ֵƵ�ײ���ģʽ������ */

#define    APP_VC_QUICK_START_DISABLE    0x00000000
#define    APP_VC_QUICK_START_ENABLE     0x01000101
/*****************************************************************************
  3���Ͷ���
*****************************************************************************/

/* VC��ʱ��ID���� */
enum APP_VC_TIMER_ID_ENUM
{
    APP_VC_TIMER_START,
    APP_VC_TIMER_STOP,
    APP_VC_TIMER_SET_DEV,
    APP_VC_TIMER_SET_VOLUME,
    APP_VC_TIMER_SET_CODEC,
    APP_VC_TIMER_SET_FOREGROUND,
    APP_VC_TIMER_SET_BACKGROUND,
    APP_VC_TIMER_QRY_GROUND,

    APP_VC_TIMER_SET_ECALL_CFG,

    APP_VC_TIMER_BUTT
};
typedef VOS_UINT16  APP_VC_TIMER_ID_ENUM_U16;

enum APP_VC_AUDIO_SAMPLE_RATE_ENUM
{
    APP_VC_SAMPLE_RATE_8K       =0,
    APP_VC_SAMPLE_RATE_11K025,
    APP_VC_SAMPLE_RATE_12K,
    APP_VC_SAMPLE_RATE_16K,
    APP_VC_SAMPLE_RATE_22K05,
    APP_VC_SAMPLE_RATE_24K,
    APP_VC_SAMPLE_RATE_32K,
    APP_VC_SAMPLE_RATE_44K1,
    APP_VC_SAMPLE_RATE_48K,
    APP_VC_SAMPLE_RATE_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_SAMPLE_RATE_ENUM_U16;

enum APP_VC_AUDIO_IN_DEV_SELECT_ENUM
{
    APP_VC_AUDIO_IN_HEADSET_OUT_MIC         = 1,
    APP_VC_AUDIO_IN_HEADSET_INTERNAL_MIC    = 2,
    APP_VC_AUDIO_IN_HEADFREE_INTERNAL_MIC   = 4,
    APP_VC_AUDIO_IN_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_IN_DEV_SELECT_ENUM_U16;

enum APP_VC_AUDIO_OUT_DEV_SELECT_ENUM
{
    APP_VC_AUDIO_OUT_HEADSET_EARPHONE   = 1,
    APP_VC_AUDIO_OUT_HEADSET_RECEIVER   = 2,
    APP_VC_AUDIO_OUT_HEADFREE_SPEAKER   = 4,
    APP_VC_AUDIO_OUT_BUTT
};
typedef VOS_UINT16  APP_VC_AUDIO_OUT_DEV_SELECT_ENUM_U16;

enum VC_NVIM_WORK_MODE_ENUM
{
    en_NV_Item_HANDSET_W_PARAM_ID           = 0X3000,                           /*Wģ�ֳֹ�������ID*/
    en_NV_Item_HANDHELD_HANDFREE_W_PARAM_ID = 0X3001,                           /*Wģ�ֳ����Ṥ������ID*/
    en_NV_Item_VECHILE_HANDFREE_W_PARAM_ID  = 0X3002,                           /*Wģ�������Ṥ������ID*/
    en_NV_Item_HEADSET_W_PARAM_ID           = 0X3003,                           /*Wģ������������ID*/
    en_NV_Item_BT_W_PARAM_ID                = 0X3004,                           /*Wģ������������ID*/
    en_NV_Item_HANDSET_G_PARAM_ID           = 0X3005,                           /*Gģ�ֳֹ�������ID*/
    en_NV_Item_HANDHELD_HANDFREE_G_PARAM_ID = 0X3006,                           /*Gģ�ֳ����Ṥ������ID*/
    en_NV_Item_VECHILE_HANDFREE_G_PARAM_ID  = 0X3007,                           /*Gģ�������Ṥ������ID*/
    en_NV_Item_HEADSET_G_PARAM_ID           = 0X3008,                           /*Gģ������������ID*/
    en_NV_Item_BT_G_PARAM_ID                = 0X3009,                           /*Gģ������������ID*/
    en_NV_Item_PCVOICE_PARAM_ID_W           = 0X300F,                           /*W PC VOICE��������ID*/

    en_NV_Item_ID_BUTT                      = 0X3100
};
typedef VOS_UINT16 VC_NVIM_WORK_MODE_ENUM_U16;

enum APP_VC_IOCTL_AUDIO_IN_DEV_ENUM
{
    APP_VC_IN_DEV_HEADSET_EXTERNAL_MIC = 1,
    APP_VC_IN_DEV_HANDSET_INTERNAL_MIC  = 2,
    APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC = 4,

    APP_VC_IN_DEV_BUTT
};
typedef VOS_UINT16 APP_VC_IOCTL_AUDIO_IN_DEV_ENUM_U16;

enum APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM
{
    APP_VC_OUT_DEV_HEADSET_EXTERNAL_MIC = 1,
    APP_VC_OUT_DEV_HANDSET_INTERNAL_MIC  = 2,
    APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC = 4,

    APP_VC_OUT_DEV_BUTT
};
typedef VOS_UINT16 APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM_U16;



/*****************************************************************************
 �ṹ��    : VC_OM_PCVOICE_TRANS_STATUS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :����ϢVC_OM_PCVOICE_TRANS_STATUS_STRU�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                        /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT16                     usPcVoiceChannelOper;  /* ��PC VOICE����ͨ�����еĲ���: �򿪡��޸ġ��ر�*/
    VOS_UINT16                     usPort;                /* ����ͨ���˿� */
    VOS_UINT32                     usOmOperResult;        /* OMִ�н�� */
} VC_OM_PCVOICE_TRANS_STATUS_STRU;


/*****************************************************************************
  4 �궨��
*****************************************************************************/
#define APP_VC_INVALID_DEV_HANDLE                   -1

#define APP_VC_AUDIO_IOCTL_BASE                     0x30000000
#define APP_VC_IOCTL_AUDIO_PCM_MODE_SET             0x30000000 + 7
#define APP_VC_IOCTL_AUDIO_SAMPLE_RATE_SET          0x30000000 + 1
#define APP_VC_IOCTL_AUDIO_IN_DEV_SELECT            0x30000000 + 11
#define APP_VC_IOCTL_AUDIO_OUT_DEV_SELECT           0x30000000 + 12
#define APP_VC_IOCTL_AUDIO_IN_DEV_UNSELECT          0x30000000 + 14
#define APP_VC_IOCTL_AUDIO_OUT_DEV_UNSELECT         0x30000000 + 13
#define APP_VC_IOCTL_AUDIO_VOICE_OPEN               0x30000000 + 23
#define APP_VC_IOCTL_AUDIO_VOICE_CLOSE              0x30000000 + 24


/* ������� */
#define VC_INFO_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str)
#define VC_NORM_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str)
#define VC_WARN_LOG(str)      TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str)
#define VC_ERR_LOG(str)       TAF_LOG(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str)

#define VC_INFO_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_INFO, str, x)
#define VC_NORM_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_NORMAL, str, x)
#define VC_WARN_LOG1(str, x)  TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x)
#define VC_ERR_LOG1(str, x)   TAF_LOG1(WUEPS_PID_VC, 0, PS_LOG_LEVEL_ERROR, str, x)

#define VC_WARN_LOG2(str, x1, x2)  TAF_LOG2(WUEPS_PID_VC, 0, PS_LOG_LEVEL_WARNING, str, x1, x2)

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
extern VOS_UINT32 WuepsVCPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
extern VOS_VOID   APP_VC_MsgProc(MsgBlock* pMsg);
extern  VCVOICE_WORK_TYPE_ENUM_UINT16 APP_VC_GetWorkType(VOS_VOID);


VOS_VOID NAS_VC_SndOutsideContextData(VOS_VOID);


VOS_UINT32  APP_VC_SendVcReqToOm(VOS_UINT32 ulStatus, VOS_UINT32 ulPort);

VCVOICE_TYPE_ENUM_UINT16 APP_VC_ConvertCallCodeTypeToVodecType(
    CALL_VC_CODEC_TYPE_ENUM_U8       enCodeType
);


#ifdef __PS_WIN32_RECUR__

VOS_UINT32 NAS_VC_RestoreContextData(struct MsgCB * pMsg);
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

#endif /* VC_COMM_H */

