

#ifndef __VCIMSAINTERFACE_H__
#define __VCIMSAINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "NVIM_Interface.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MTA_INVALID_TAB_INDEX           (0x00)



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum IMSA_VC_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /* ��ϢID */        /* ��ע, ����ASN */
    /* IMSA����VC����Ϣ */
    ID_IMSA_VC_START_HIFI_NTF           = 0x0000,           /* _H2ASN_MsgChoice IMSA_VC_START_HIFI_NTF_STRU         */
    ID_IMSA_VC_STOP_HIFI_NTF            = 0x0001,           /* _H2ASN_MsgChoice IMSA_VC_STOP_HIFI_NTF_STRU          */
    ID_IMSA_VC_HIFI_PARA_CHANGED_NTF    = 0x0002,           /* _H2ASN_MsgChoice IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU  */


    /* VC����IMSA����Ϣ */
    ID_VC_IMSA_HIFI_EXCEPTION_NTF       = 0x1000,           /* _H2ASN_MsgChoice VC_IMSA_HIFI_EXCEPTION_NTF_STRU  */

    /* ���һ����Ϣ */
    ID_IMSA_VC_MSG_TYPE_BUTT

};
typedef VOS_UINT32 IMSA_VC_MSG_TYPE_ENUM_UINT32;


enum IMSA_VC_MODE_ENUM
{
    IMSA_VC_MODE_EUTRAN_IMS            = 0,
    IMSA_VC_MODE_UTRAN_IMS,
    IMSA_VC_MODE_BUTT
};
typedef VOS_UINT8  IMSA_VC_MODE_ENUM_UINT8;


enum IMSA_VC_CODEC_TYPE_ENUM
{
    IMSA_VC_CODEC_TYPE_AMR             = 0,
    IMSA_VC_CODEC_TYPE_AMRWB,
    IMSA_VC_CODEC_TYPE_G711,
    IMSA_VC_CODEC_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_VC_CODEC_TYPE_ENUM_UINT8;


enum VC_IMSA_EXCEPTION_CAUSE_ENUM
{
    VC_IMSA_EXCEPTION_CAUSE_SUCC                = 0,                            /* �ɹ� */
    VC_IMSA_EXCEPTION_CAUSE_STARTED,                                            /* HIFI�Ѿ����� */
    VC_IMSA_EXCEPTION_CAUSE_PORT_CFG_FAIL,                                      /* �˿����� */
    VC_IMSA_EXCEPTION_CAUSE_SET_DEVICE_FAIL,                                    /* ����Deviceʧ�� */
    VC_IMSA_EXCEPTION_CAUSE_SET_START_FAIL,                                     /* startʧ�� */
    VC_IMSA_EXCEPTION_CAUSE_SET_VOLUME_FAIL,                                    /* ��������ʧ�� */
    VC_IMSA_EXCEPTION_CAUSE_SAMPLE_RATE_FAIL,                                   /* Ƶ�ʲ���ʧ�� */
    VC_IMSA_EXCEPTION_CAUSE_TI_START_EXPIRED,                                   /* start������ʱ����ʱ */


    VC_IMSA_EXCEPTION_CAUSE_BUTT
};
typedef VOS_UINT32  VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32;

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
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /*_H2ASN_Skip*/
    IMSA_VC_MODE_ENUM_UINT8             enMode ;
    IMSA_VC_CODEC_TYPE_ENUM_UINT8       enCodeType;
    VOS_UINT8                           aucReserved[2];
} IMSA_VC_START_HIFI_NTF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /*_H2ASN_Skip*/
} IMSA_VC_STOP_HIFI_NTF_STRU;



typedef struct
{

    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;      /*_H2ASN_Skip*/
    IMSA_VC_MODE_ENUM_UINT8             enMode ;    
    IMSA_VC_CODEC_TYPE_ENUM_UINT8       enCodeType;
    VOS_UINT8                           aucReserved[2];
} IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;          /*_H2ASN_Skip*/
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32 enCause;
} VC_IMSA_HIFI_EXCEPTION_NTF_STRU;


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
    IMSA_VC_MSG_TYPE_ENUM_UINT32        enMsgId;
    
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          IMSA_VC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}VC_IMSA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    VC_IMSA_MSG_DATA                    stMsgData;
}VcImsaInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif

