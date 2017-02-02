

#ifndef _MTCMTAINTERFACE_H_
#define _MTCMTAINTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


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

enum MTA_MTC_MSG_ID_ENUM
{
    /* ��Ϣ���� */                         /* ��ϢID */                         /* ��ע */
    /* MTA --> MTC */
    ID_MTA_MTC_GSM_CELLINFO_QRY_REQ     = 0x0001,                               /* _H2ASN_MsgChoice MTA_MTC_RESERVE_STRU*/

    /* MTC --> MTA */
    ID_MTC_MTA_PS_TRANSFER_IND          = 0x0002,                               /* _H2ASN_MsgChoice MTC_MTA_PS_TRANSFER_IND_STRU */
    ID_MTC_MTA_MIPICLK_INFO_IND         = 0x0004,                               /* _H2ASN_MsgChoice MTC_MTA_MIPICLK_INFO_IND_STRU*/
    ID_MTC_MTA_GSM_CELLINFO_QRY_CNF     = 0x0006,                               /* _H2ASN_MsgChoice MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU*/

    ID_MTA_MTC_MSG_ID_BUTT
};
typedef VOS_UINT32  MTA_MTC_MSG_ID_ENUM_UINT32;
enum MTA_MTC_RESULT_ENUM
{
    MTA_MTC_RESULT_NO_ERROR             = 0x0000,                               /* ��Ϣ�������� */
    MTA_MTC_RESULT_ERROR,

    MTA_MTC_RESULT_BUTT
};
typedef VOS_UINT32  MTA_MTC_RESULT_ENUM_UINT32;

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
    VOS_UINT32                          ulMcc;              /* MCC,3 bytes      */
    VOS_UINT32                          ulMnc;              /* MNC,2 or 3 bytes */
} MTA_MTC_PLMN_ID_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserved[4];                         /* ����λ */
} MTA_MTC_RESERVE_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT8                           ucCause;                                /* PS���л�ԭ��ֵ */
    VOS_UINT8                           aucReserved[3];                         /*����λ*/
} MTC_MTA_PS_TRANSFER_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    VOS_UINT16                          usMipiCLk;                              /* ��ѡMIPICLKֵ���� */
    VOS_UINT8                           aucReserved[2];                         /*����λ*/
} MTC_MTA_MIPICLK_INFO_IND_STRU;
typedef struct
{
    VOS_UINT32                          ulValidFlg;                             /* GSMС����Ϣ��Ч�Ա�ʾ */
    MTA_MTC_PLMN_ID_STRU                stPlmnId;                               /* PLMN ID */
    VOS_UINT16                          usLac;                                  /* LAC */
    VOS_UINT16                          usCellId;                               /* С��ID */
} MTC_GSM_CELLINFO_EX_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MTA_MTC_RESULT_ENUM_UINT32          enResult;                               /* ������� */
    MTC_GSM_CELLINFO_EX_STRU            stCellInfoEx;                           /* GSMС����Ϣ */
} MTC_MTA_GSM_CELLINFO_QRY_CNF_STRU;

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
    MTA_MTC_MSG_ID_ENUM_UINT32          enMsgID;                                /*_H2ASN_MsgChoice_Export MTA_MTC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MTA_MTC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} MTA_MTC_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MTA_MTC_MSG_DATA                    stMsgData;
} MtaMtcInterface_MSG;

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

#endif /* end of MtaMtcInterface.h */

