

#ifndef __IMSALRRCINTERFACE_H__
#define __IMSALRRCINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "LPSCommon.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define  IMSA_LRRC_MSG_HDR   (PS_MSG_ID_IMSA_TO_ERRC_BASE)





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

enum    IMSA_LRRC_MSG_ID_ENUM
{
    ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY     = (IMSA_LRRC_MSG_HDR + 0x00),     /* _H2ASN_MsgChoice IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU */
    ID_IMSA_LRRC_END_SESSION_NOTIFY       = (IMSA_LRRC_MSG_HDR + 0x01),     /* _H2ASN_MsgChoice IMSA_LRRC_END_SESSION_NOTIFY_STRU */

    /* lihong00150010 hifi sync begin */
    ID_IMSA_LRRC_HIFI_SYNC_SWITCH_IND     = (IMSA_LRRC_MSG_HDR + 0x02),     /* _H2ASN_MsgChoice IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU */
    /* lihong00150010 hifi sync end */

    ID_IMSA_LRRC_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32   IMSA_LRRC_MSG_ID_ENUM_UINT32;



/*****************************************************************************
  4 Enum
*****************************************************************************/

enum IMSA_LRRC_SESSION_TYPE_ENUM
{
    IMSA_LRRC_SESSION_TYPE_MO_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_MT_NORMAL_CALL,
    IMSA_LRRC_SESSION_TYPE_EMERGENCY_CALL,
    IMSA_LRRC_SESSION_TYPE_MO_SS,
    IMSA_LRRC_SESSION_TYPE_MT_SS,
    IMSA_LRRC_SESSION_TYPE_MO_SMS,
    IMSA_LRRC_SESSION_TYPE_MT_SMS,
    IMSA_LRRC_SESSION_TYPE_REGISTER,
    IMSA_LRRC_SESSION_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_LRRC_SESSION_TYPE_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8               enSessionType;
    VOS_UINT8                                       aucReserved[3];
}IMSA_LRRC_END_SESSION_NOTIFY_STRU;

/* lihong00150010 hifi sync begin */

typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;          /* ��Ϣͷ    */   /*_H2ASN_Skip*/
    VOS_UINT8                                       ucHifiSyncEnabled;    /* 0��ʾ�رգ�1��ʾ�� */
    VOS_UINT8                                       ucPowerState;         /* Modem1���ػ�״̬��0��ʾ�ر�;1��ʾ�� */
    VOS_UINT8                                       aucReserved[2];
}IMSA_LRRC_HIFI_SYNC_SWITCH_IND_STRU;
/* lihong00150010 hifi sync end */


/*****************************************************************************
 ��������: IMSA_LRRC_GetSsacInfo
 Э����:
 ASN.1 ����:
 ����˵��:
*****************************************************************************/
typedef struct
{
    VOS_UINT8    ucBarFactorForVoice;   /*ȡֵ��Χ:0~15ö��ֵ*/
    VOS_UINT8    ucBarTimeForVoice;     /*ȡֵ��Χ:0~7ö��ֵ,��λ:s*/
    VOS_UINT8    ucBarFactorForVideo;   /*ȡֵ��Χ:0~15ö��ֵ*/
    VOS_UINT8    ucBarTimeForVideo;     /*ȡֵ��Χ:0~7ö��ֵ,��λ:s*/
}IMSA_LRRC_SSAC_INFO_STRU;



/*****************************************************************************
 ��������: IMSA_LRRC_GetSsacInfo
 Э����:
 ASN.1 ����:
 ����˵��:LRRC�ṩ��IMSA SSAC�����Ϣ
*****************************************************************************/
extern VOS_UINT32  IMSA_LRRC_GetSSACInfo
(
    IMSA_LRRC_SSAC_INFO_STRU *pstSsacInfo
);


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/





/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaLrrcInterface.h */








