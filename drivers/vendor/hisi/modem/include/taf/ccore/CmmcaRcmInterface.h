/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CmmcaRcmInterface.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2014��09��30��
  ����޸�   :
  ��������   : Rcm��CMMCA֮��ӿ��ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��30��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef __CMMCA_RCM_INTERFACE_H__
#define __CMMCA_RCM_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CMMCA_RCM_SCELL_PN_PHASE_NUM    (7)
#define CMMCA_RCM_SCELL_ECIO_NUM        (7)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum CMMCA_RCM_MSG_TYPE_ENUM
{
    /* CMMCA->RCM CDMA MSG: */
    ID_CMMCA_RCM_TAS_MEASUREMENT_IND                        = 0x181b,          /* _H2ASN_MsgChoice CMMCA_RCM_MEASUREMENT_INFO_IND_STRU */
    ID_CMMCA_RCM_TAS_EVENT_IND                              = 0x181c,          /* _H2ASN_MsgChoice CDMA_TAS_EVENT_DATA_INFO_IND_STRU */

    ID_CMMCA_RCM_MSG_TYPE_BUTT
};
typedef VOS_UINT32  CMMCA_RCM_MSG_TYPE_ENUM_UINT32;
enum CDMA_TAS_EVENT_TYPE_ENUM
{
    CDMA_TAS_EVENT_NONE                 = 0x00,
    CDMA_TAS_EVENT_SIGNAL_GOOD          = 0x01,
    CDMA_TAS_EVENT_SIGNAL_POOR          = 0x02,
    CDMA_TAS_EVENT_S_PASS               = 0x03,
    CDMA_TAS_EVENT_S_FAIL               = 0x04,

    CDMA_TAS_EVENT_TYPE_BUTT
};
typedef VOS_UINT8  CDMA_TAS_EVENT_TYPE_ENUM_UINT8;

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
    VOS_UINT16                          usScellFreq;                                            /* Ƶ�� */
    VOS_INT16                           sScellRxAgc;                                           /* ���� */
    VOS_UINT16                          ausScellPnPhase[CMMCA_RCM_SCELL_PN_PHASE_NUM];          /* С���� */
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           aucScellEcIo[CMMCA_RCM_SCELL_ECIO_NUM];                 /* �������ű� */
    VOS_UINT8                           ucReserved2;
}CMMCA_RCM_MEASUREMENT_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                 /*_H2ASN_Skip*/
    CMMCA_RCM_MSG_TYPE_ENUM_UINT32      enMsgId;   /*_H2ASN_Skip*/
    CMMCA_RCM_MEASUREMENT_INFO_STRU     stMeasurementInfo;
}CMMCA_RCM_MEASUREMENT_INFO_IND_STRU;


typedef struct
{
    CDMA_TAS_EVENT_TYPE_ENUM_UINT8      enCdmaTasEvent;
    VOS_UINT8                           aucRsv[3];
}CDMA_TAS_EVENT_INFO_STRU;



typedef struct
{
    VOS_MSG_HEADER                                 /*_H2ASN_Skip*/
    CMMCA_RCM_MSG_TYPE_ENUM_UINT32      enMsgId;   /*_H2ASN_Skip*/
    CDMA_TAS_EVENT_INFO_STRU            stCdmaEventData;
}CDMA_TAS_EVENT_DATA_INFO_IND_STRU;




typedef struct
{
    CMMCA_RCM_MSG_TYPE_ENUM_UINT32      enMsgID;                                /*_H2ASN_MsgChoice_Export CMMCA_RCM_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
/***************************************************************************
_H2ASN_MsgChoice_When_Comment          CMMCA_RCM_MSG_TYPE_ENUM_UINT32
****************************************************************************/
}CMMCA_RCM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    CMMCA_RCM_MSG_DATA                  stMsgData;
}CmmcaRcmInterface_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif /* end of CmmcaRcmInterface.h */

