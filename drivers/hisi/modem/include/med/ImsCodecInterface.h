/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ImsCodecInterface.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2013��7��15��
  ����޸�   :
  ��������   : IMSA��CODECģ���Ľӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��15��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __IMSACODECINTERFACE_H__
#define __IMSACODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* _H2ASN_Include v_typedef.h */
/* _H2ASN_Include ImsaCodecInterface.h */
#include "vos.h"
#include "CodecInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define IMSA_CODEC_MAX_DATA_LEN                     (32)           /* ��λ��16 bit */

/*
IMSA_TX_DATA_STRU�ṹ��������
usFrameType     --���б�֡��FrameType
ausData         --IF1Э���е�A��B��C������ABC�������У�Byte����
*/
#define IMSA_TX_DATA_STRU                                                       \
    VOS_UINT16                      usMsgId;    /* ԭ������ */ /*_H2ASN_Skip*/\
    VOS_UINT16                      usReserve;  /* ������   */                            \
    CODEC_AMR_TYPE_TX_ENUM_UINT16   usStatus;   /* AMR����������  */                            \
    VOS_UINT16                      usFrameType; /* ֡����   */                           \
    VOS_UINT16                      ausData[IMSA_CODEC_MAX_DATA_LEN];

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum IMSA_VOICE_MSG_ID_ENUM
{
    /*====== VOICE->IMSA ======*/
    ID_VOICE_IMSA_TX_DATA_IND                       = 0x49A8,                   /* IMS�������������� */           /* _H2ASN_MsgChoice VOICE_IMSA_TX_DATA_IND_STRU */
    ID_VOICE_IMSA_CFG_CNF                           = 0x49A9,                   /* ����HIFI���еĽ������ڽ�� */    /* _H2ASN_MsgChoice VOICE_IMSA_CFG_CNF_STRU */
    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    ID_VOICE_IMSA_RX_DATA_ACK                       = 0x49AA,                   /* �ظ�RX_DATA������ */           /* _H2ASN_MsgChoice VOICE_IMSA_RX_DATA_ACK_STRU */
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

    /*====== IMSA->VOICE ======*/
    ID_IMSA_VOICE_RX_DATA_IND                       = 0x94A8,                   /* IMS������������ */               /* _H2ASN_MsgChoice IMSA_VOICE_RX_DATA_IND_STRU */
    ID_IMSA_VOICE_CFG_REQ                           = 0x94A9,                   /* ����HIFI���еĽ������� */        /* _H2ASN_MsgChoice IMSA_VOICE_CFG_REQ_STRU */

    IMSA_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 IMSA_VOICE_MSG_ID_ENUM_UINT16;

enum IMSA_VOICE_ERRORFLAG_ENUM
{
    IMSA_VOICE_NO_ERROR = 0,                                                    /* Jitter Buffer������ */
    IMSA_VOICE_ERROR,                                                           /* Jitter Bufferû������ */
    IMSA_VOICE_ERRORFLAG_BUTT
};
typedef VOS_UINT16 IMSA_VOICE_ERRORFLAG_ENUM_UINT16;

enum IMSA_VOICE_CFG_ENUM
{
    IMSA_VOICE_CFG_SUCC         = 0,                /* ���óɹ� */
    IMSA_VOICE_CFG_FAIL,                            /* ����ʧ�� */
    IMSA_VOICE_CFG_BUTT
};
typedef VOS_UINT32 IMSA_VOICE_CFG_ENUM_UINT32;



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
 ʵ������  : IMSA_VOICE_RX_DATA_IND_STRU
 ��������  : IMS��ȡIP�������RTP�����ͨ��IMSA���͸���Ϣ��VOICE�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94A8*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usSN;                                   /* �����к� */
    VOS_UINT32                          ulTS;                                   /* ��ʱ��� */
    CODEC_ENUM_UINT16                   usCodecType;                            /* ���������� */
    CODEC_DTX_ENUM_UINT16               usDtxEnable;                            /* ���б����DTX */
    VOS_UINT16                          usRateMode;                             /* ���б����RateMode */
    IMSA_VOICE_ERRORFLAG_ENUM_UINT16    usErrorFlag;                            /* Bufferû����ʱ��ErrorFlag */
    VOS_UINT16                          usFrameType;                            /* ���б�֡��FrameType */
    VOS_UINT16                          usQualityIdx;                           /* Quality indification */
    VOS_UINT16                          ausData[IMSA_CODEC_MAX_DATA_LEN];       /* IF1Э���е�A��B��C������ABC�������У�Byte���� */
    VOS_UINT32                          ulSSRC;                                 /* SSRC��Ϣ */
    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    VOS_UINT32                          ulNeedAckFlag;                          /* �Ƿ���ҪHIFI�ظ���־ */
    VOS_UINT32                          ulOpid;                                 /* Opid�ţ�����ͬ����Ϣ */
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */
}IMSA_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_IMSA_RX_DATA_ACK_STRU
 ��������  : ��ҪHIFI�ظ�ack,HIFI�Ļظ��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94AA*/ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserved;
    VOS_UINT32                          ulOpid;                                 /* Opid�ţ�����ͬ����Ϣ */
}VOICE_IMSA_RX_DATA_ACK_STRU;

/*****************************************************************************
 ʵ������  : VOICE_IMSA_TX_DATA_IND_STRU
 ��������  : VOICE���������ݴ���ͱ���OK��ͨ������Ϣ�����ݷ��͸�IMSA
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    IMSA_TX_DATA_STRU
}VOICE_IMSA_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : IMSA_VOICE_CFG_REQ_STRU
 ��������  : ����HIFI���еĽ�������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    VOS_UINT16                          usMsgId;                                /* 0x94a9 */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;
    VOS_UINT32                          ulTransTime;                            /* ���к�IMSA�Ľ������� */
    VOS_UINT32                          ulSendBitrate;                          /* Ims���������� */
}IMSA_VOICE_CFG_REQ_STRU;

/*****************************************************************************
 ʵ������  : IMSA_VOICE_CFG_CNF_STRU
 ��������  : IMSA_VOICE_CFG_REQ�Ļظ�
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER																/*_H2ASN_Skip*/
    VOS_UINT16                              usMsgId;                            /* 0x49a9 */ /*_H2ASN_Skip*/
    VOS_UINT16                              usReserve;
    IMSA_VOICE_CFG_ENUM_UINT32              ulResult;                           /* ִ�н�� */
}VOICE_IMSA_CFG_CNF_STRU;



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#if 0                                                                           /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    IMSA_VOICE_MSG_ID_ENUM_UINT16          enMsgID;                              /* _H2ASN_MsgChoice_Export IMSA_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_IMSA_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_IMSA_TRACE_MSG_DATA              stMsgData;
}VoiceImsaTrace_MSG;

#endif    																		/* _H2ASN_Skip */
/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of imsacodecinterface.h */

