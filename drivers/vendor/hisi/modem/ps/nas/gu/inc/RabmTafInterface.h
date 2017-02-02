/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : RabmTafInterface.h
  Description : RABM��TAF�ӿ�ͷ�ļ�
  History     :
      1.  ��־��      2003.12.04   �°�����
      2.��    ��  : 2006��12��4��
        ��    ��  : luojian id:60022475
        �޸�����  : ���� #pragma pack(4)�����ⵥ��:A32D07779
*******************************************************************************/

#ifndef _RABM_TAF_INTERFACE_H_
#define _RABM_TAF_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif                                                                          /* __cpluscplus                             */
#endif                                                                          /* __cpluscplus                             */

#include "TTFMem.h"


#pragma pack(4)
/* Ӧ�ò㷢�͸�RABM��ԭ�� */
#define TAFRABM_PS_DATA_REQ             0
#define TAFRABM_CS_DATA_REQ             2
/* RABM���͸�Ӧ�ò��ԭ�� */
#define TAFRABM_PS_DATA_CNF             1
#define TAFRABM_CS_DATA_CNF             3
#define TAFRABM_INACTIVE_NSAPI_IND      5
#define TAFRABM_INACTIVE_SI_IND         7
#define TAFRABM_STARTSTOP_IND           9
#define TAFRABM_PS_DATA_IND             11
#define TAFRABM_CS_DATA_IND             13

/*����TAF���޷�����RABM�Ƿ���CALL�Ļ���APS�ģ���ˣ�Ŀǰ����Ϣ������
  RABM����CALL����Ϣ����Ŵ�0x4000��ʼ��ĿǰRABM����APS�ı�ţ�Ŀǰ��
  ��0x0120��ʼ���*/
#define RABM_CALL_MSG_CLASS_BASE        (0x4000)
#define RABM_CALL_SYNC_IND              (0x4001)

/*MN_CALL֪ͨRabm�Ƿ��������ҵ��*/
#define CALL_RABM_VOICEPREFER_CS_EXIST_IND                  (0x4002)

/* ԭ��TAFRABM_PS_DATA_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    VOS_UINT32                   ulNsapi;                                            /* ָ����NSAPI                              */
    TTF_MEM_ST              *pData;                                         /* �û����ݵ�ַ                             */
}TAFRABM_PS_DATA_REQ_STRU;

/* ԭ��TAFRABM_PS_DATA_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */
    VOS_UINT32                   ulDestAddr;                                         /* ָ����TAF��ַ                            */
    VOS_UINT32                   ulNsapi;                                            /* ָ����NSAPI                              */
    VOS_UINT32                   ulDataLen;                                          /* �û����ݵĳ���                           */
    VOS_UINT8                   aucData[4];                                         /* �û����ݵ�ַ                             */
}TAFRABM_PS_DATA_IND_STRU;

/* ԭ��TAFRABM_STARTSTOP_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */

#define  TAF_RABM_MAX_NSAPI_NUM    11
    VOS_UINT32           ulNsapiOrSi;                                                /* RAB ID����Ӧ��NSAPI                      */
    VOS_UINT32           ulStartStopFlag;                                            /* ֹͣ��ʼ�������ݱ�־                     */
    VOS_UINT32           ulStartCause;                                               /* ��ʼ�������ݵ�ԭ��                        */
}TAFRABM_STARTSTOP_IND_STRU;

/* ԭ��TAFRABM_INACTIVE_NSAPI_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulNsapi;                                             /* ָ����NSAPI                              */
} TAFRABM_INACTIVE_NSAPI_IND_STRU;

/* ԭ��TAFRABM_CS_DATA_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulSi;                                                /* ָ����Si                                 */
    VOS_UINT32                  ulAmrFlg ;                                           /* �������Ƿ�����������
                                                                                 * RABM_TRUE:��;RABM_FALSE:����             */
    VOS_UINT32                  ulDataLen;                                           /* �û����ݵĳ���                            */
    VOS_UINT8                  aucData[4];                                          /* �û����ݵ�ַ                              */
}TAFRABM_CS_DATA_REQ_STRU;

/* ԭ��TAFRABM_CS_DATA_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */

    VOS_UINT32                  ulSi;                                                /* ָ����Si                                 */
    VOS_UINT32                  ulDataLen;                                           /* �û����ݵĳ���                            */
    VOS_UINT8                  aucData[4];                                          /* �û����ݵ�ַ                             */
}TAFRABM_CS_DATA_IND_STRU;

/* ԭ��TAFRABM_INACTIVE_SI_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulSi;                                                /* ָ����Si                                 */
} TAFRABM_INACTIVE_SI_IND_STRU;

/* ԭ��TAFRABM_PS_DATA_CNF�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulNsapi;                                             /* ָ����nsapi                              */
} TAFRABM_PS_DATA_CNF_STRU;

/* ԭ��TAFRABM_CS_DATA_CNF�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32                  ulSi;                                                /* specified SI                             */
}TAFRABM_CS_DATA_CNF_STRU;


#define    RABMCALL_RAB_ACTIVE      0
#define    RABMCALL_RAB_INACTIVE    1

#define    RABM_CALL_MAX_RB_NUM_PER_RAB   3
typedef struct
{
    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */
    VOS_UINT32             ulRabState;                                          /* 0��SI����ʹ�ã�1��SI������ʹ��             */
    VOS_UINT32             ulRabId;                                             /* ��RAB��Ӧ��RAB ID                        */
    VOS_UINT32             ulRbNum;                                             /* ��RAB����RB����                          */
    VOS_UINT32             aulRbId[RABM_CALL_MAX_RB_NUM_PER_RAB];                    /* RB ID�б�                                */
}RABM_CALL_SYNC_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ */
    VOS_UINT32                          ulVoiceFlag;                            /* 0������������ҵ��1����������ҵ�� */
    VOS_UINT32                          ulCampMcc;                              /* ��ǰע��plmn:mcc*/
    VOS_UINT32                          ulCampMnc;                              /* ��ǰע��plmn:mnc*/
}CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU;


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                          /* __cpluscplus                             */

#endif




