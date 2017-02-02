
#ifndef _VC_CTX_H_
#define _VC_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "AppVcApi.h"
#include  "VcMain.h"
#include  "VcCallInterface.h"
#include  "PsTypeDef.h"
/* Added by w00316404 for OPT VC, 2015-02-07, Begin */
#include "hi_list.h"
/* Added by w00316404 for OPT VC, 2015-02-07, End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define APP_VC_MAX_MSG_BUFF_LEN         (100)
#define APP_VC_BUFF_MSG_MAX_CNT         32                                      /* VCģ�黺�������Ϣ���� */

#define APP_VC_MSD_DATA_LEN              (140)

#define VC_MAX_AL_ACK_NUM                   (20)

/* ��BIT n��λ */
#define VC_SET_BIT(n)                       (0x01 << n)

#define VC_AL_ACK_CLEAR_DOWN_BIT            VC_SET_BIT(1)                      /* ��ʶclean Down */



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
/* APP_VC_BUFF_MSG_UNIONɾ�� */

typedef struct
{
    VOS_UINT16                           usVcPcvoiceSupportFlag;                /*Pcvoiceҵ��*/
}APP_VC_MS_CFG_INFO_STRU;

typedef struct
{
    APP_VC_MSG_ORIGIN_ENUM_U16              enMsgOrigin;
    VOS_UINT16                              usReserved;
    /* IMSA��Ϣ��ΪSTART_HIFI��STOP_HIFI��HIFI_PARA_CHANGE�����ṹ�壬��ԭ����һ��
       ͳһ�ĳ�VOS_UINT8 */
    VOS_UINT8                               aucBufMsg[APP_VC_MAX_MSG_BUFF_LEN];
} APP_VC_BUFFER_MSG_STRU;


typedef struct
{
    VOS_UINT32                          ulTimeStamp;                            /* �ϱ�ʱ��, ��λΪtickֵ */
    VOS_UINT8                           ucAlAckValue;                           /* AL_ACKֵ */
    VOS_UINT8                           aucReserved[3];
}VC_AL_ACK_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulIndex;
    VC_AL_ACK_INFO_STRU                 astAlAckInfo[VC_MAX_AL_ACK_NUM];        /* �ϱ�ʱ�� */
}VC_AL_ACK_REPORT_INFO_STRU;
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
    VC_AL_ACK_REPORT_INFO_STRU              stVcAlAckReportInfo;                /* AlAck ��Ϣ */
}VC_ECALL_CTX_STRU;


typedef struct
{

    APP_VC_GLOBAL_STATE_ENUM_U16            enState;                            /* VC��ȫ��״̬ */
    MN_CLIENT_ID_T                          clientId;
    MN_OPERATION_ID_T                       opId;
    APP_VC_VOICE_PORT_ENUM_U8               ucVoicePort;
    VOS_UINT8                               ucPcVoiceSupportFlag;
    APP_VC_START_HIFI_ORIG_ENUM_UINT8       enStartHifiOrig;                    /* ������IMSA����CALLҪ����HIFI */
    VOS_BOOL                                bParaUpdate;
    CALL_VC_RADIO_MODE_ENUM_U8              enRadioMode;                        /* ����ģʽ */
    CALL_VC_CODEC_TYPE_ENUM_U8              enCodecType;                        /* codec type */
    APP_VC_MUTE_STATUS_ENUM_UINT8           enPreMuteStatus;
    APP_VC_MUTE_STATUS_ENUM_UINT8           enCurrMuteStatus;
    VOS_UINT32                              ulBuffMsgCnt;
    /* Added by W00316404 for OPT VC, 2015-02-07, Begin */
    HI_LIST_S                               stBuffMsgListHead;                  /* ������Ϣ�б�ͷ�ڵ� */
    /* Added by W00316404 for OPT VC, 2015-02-07, End */
    HTIMER                                  protectTimer;
    VOS_INT32                               iDevHandle;
    VOS_BOOL                                bInCall;                            /* ��ǰ�Ƿ��ں��й����� */
    APP_VC_MS_CFG_INFO_STRU                 stMsCfgInfo;                        /* MS��������Ϣ */
    VOS_UINT32                              ulVoiceTestFlag;

    VC_ECALL_CTX_STRU                       stEcallCtx;
} APP_VC_STATE_MGMT_STRU;

/* �����طŵ���ȫ�ֱ���ʹ��*/
typedef struct
{
    APP_VC_STATE_MGMT_STRU                   pc_g_g_stVcStateMgmt;
} NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST;



/*****************************************************************************
 Structure      : NAS_CC_SDT_MSG_ST
 Description    : PC�طŹ��̣�CC��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST      stOutsideCtx;
}NAS_VC_SDT_MSG_ST;

/*****************************************************************************
 �ṹ��    : APP_VC_BUFF_MSG_NODE_STRU
 �ṹ˵��  : VCģ��Buffer������Ϣ����ڵ�ṹ

  1.��    ��   : 2015��02��07��
    ��    ��   : W00316404
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    MsgBlock                           *pBuffMsg;
    HI_LIST_S                           stList;
} APP_VC_BUFF_MSG_NODE_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
APP_VC_MS_CFG_INFO_STRU* APP_VC_GetCustomCfgInfo( VOS_VOID );
APP_VC_STATE_MGMT_STRU*  APP_VC_GetCtx( VOS_VOID );

APP_VC_STATE_MGMT_STRU*  APP_VC_GetVcStateMgmtAddr( VOS_VOID );

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT8* APP_VC_GetEcallMsdAddr( VOS_VOID );
VOS_VOID APP_VC_SetNewEcallCfg( VOS_UINT16 usMode, VOS_UINT16 usVocConfig);
VOS_VOID APP_VC_UpdateCurrEcallCfg(VOS_VOID);
VOS_VOID APP_VC_GetCurrEcallCfg( VOS_UINT16 *pusMode, VOS_UINT16 *pusVocConfig);
VOS_VOID APP_VC_SetInEcallFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetInEcallFlag(VOS_VOID);
VOS_VOID APP_VC_SetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetMsdFlag(VOS_VOID);
VOS_VOID APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 enState);
APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8 APP_VC_GetEcallState(VOS_VOID);
VOS_VOID APP_VC_SetEcallDescription(VOS_UINT32 ulDesc);
VOS_UINT32 APP_VC_GetEcallDescription(VOS_VOID);
VOS_VOID APP_VC_SetAllowSetMsdFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 APP_VC_GetAllowSetMsdFlag(VOS_VOID);

VC_AL_ACK_REPORT_INFO_STRU* APP_VC_GetAlAckInfoAddr(VOS_VOID);

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

#endif /* end of VcCtx.h */

