
#ifndef __NAS_MTA_INTERFACE_H__
#define __NAS_MTA_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "AppNasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* Added by lwx277467 for UE Mode, 2015-9-7, begin */
#define MTA_LNAS_MSG_TYPE_BASE          (0x0100)                               /*MTAģ����LNASģ�����Ϣ����*/
#define LNAS_MTA_MSG_TYPE_BASE          (0x0200)                               /*LNASģ����MTAģ�����Ϣ����*/
/* Added by lwx277467 for UE Mode, 2015-9-7, end */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
 �ṹ����: NAS_MTA_MSG_TYPE_ENUM_UINT32
 �ṹ˵��: MTA��NAS֮���ԭ��
*****************************************************************************/
enum NAS_MTA_MSG_TYPE_ENUM
{
    ID_NAS_MTA_AREA_LOST_IND           = 0x0001,          /* _H2ASN_MsgChoice NAS_MTA_AREA_LOST_IND_STRU */

    /* Added by lwx277467 for UE Mode, 2015-9-7, begin */
    ID_MTA_LNAS_SET_UE_CENTER_REQ      = MTA_LNAS_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice MTA_LNAS_SET_UE_CENTER_REQ_STRU */

    ID_LNAS_MTA_SET_UE_CENTER_CNF      = LNAS_MTA_MSG_TYPE_BASE + 0x01,        /* _H2ASN_MsgChoice LNAS_MTA_SET_UE_CENTER_CNF_STRU */

    ID_MTA_LNAS_QRY_UE_CENTER_REQ      = MTA_LNAS_MSG_TYPE_BASE + 0x02,        /* _H2ASN_MsgChoice MTA_LNAS_QRY_UE_CENTER_REQ_STRU */

    ID_LNAS_MTA_QRY_UE_CENTER_CNF      = LNAS_MTA_MSG_TYPE_BASE + 0x02,        /* _H2ASN_MsgChoice LNAS_MTA_QRY_UE_CENTER_CNF_STRU */
    /* Added by lwx277467 for UE Mode, 2015-9-7, end */

    ID_NAS_MTA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 NAS_MTA_MSG_TYPE_ENUM_UINT32;

/* Added by lwx277467 for UE Mode, 2015-9-7, begin */
/*****************************************************************************
 ö����    : MTA_LMM_RESULT_ENUM
 �ṹ˵��  : MTAģ����LMM��Ľ����ö��

  1.��    ��   : 2015��09��09��
    ��    ��   : lwx277467
    �޸�����   : ����
*****************************************************************************/
enum MTA_LMM_RESULT_ENUM
{
    MTA_LMM_RESULT_NO_ERROR                     = 0x000000,                     /* ��Ϣ�������� */
    MTA_LMM_RESULT_ERROR,                                                       /* ��Ϣ������� */

    MTA_LMM_RESULT_BUTT
};
typedef VOS_UINT32 MTA_LMM_RESULT_ENUM_UINT32;
/* Added by lwx277467 for UE Mode, 2015-9-7, end */

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
    MSG_HEADER_STRU                             stMsgHeader;                    /*_H2ASN_Skip*/

    VOS_UINT8                                   aucRsv[4];                      /* ����λ */
}NAS_MTA_AREA_LOST_IND_STRU;

/* Added by lwx277467 for UE Mode, 2015-9-7, begin */
/*******************************************************************************
 �ṹ��    : MTA_LNAS_SET_UE_CENTER_REQ_STRU
 �ṹ˵��  : ����UEģʽ�������Ϣ�ṹ
 1.��    ��   : 2015��09��07��
   ��    ��   : lwx277467
   �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT32                                  ulOpId;
    LNAS_LMM_UE_CENTER_ENUM_UINT32              enUeCenter;
}MTA_LNAS_SET_UE_CENTER_REQ_STRU;

/*******************************************************************************
 �ṹ��    : LNAS_MTA_SET_UE_CENTER_CNF_STRU
 �ṹ˵��  : ����UEģʽ����ظ�����Ϣ�ṹ
 1.��    ��   : 2015��09��07��
   ��    ��   : lwx277467
   �޸�����   : 
*******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                                  ulMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulRslt;                         /*0�ɹ���1ʧ��*/
}LNAS_MTA_SET_UE_CENTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MTA_LNAS_UE_CENTER_QRY_REQ_STRU
 �ṹ˵��  : MTA��LNAS��ѯUEģʽ����ID_MTA_LNAS_TRANSMODE_QRY_REQ�ṹ��

  1.��    ��   : 2015��9��7��
    ��    ��   : lwx277467
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           aucReserved[4];                         /* ����λ */
} MTA_LNAS_QRY_UE_CENTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : LNAS_MTA_UE_CENTER_QRY_CNF_STRU
 �ṹ˵��  : LNAS�ظ�MTA UEģʽ��ѯ���ID_LRRC_MTA_TRANSMODE_QRY_CNF�ṹ��

  1.��    ��   : 2015��9��7��
    ��    ��   : lwx277467
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          enResult;                               /*��ѯ�������*/
    VOS_UINT32                          enUeCenter;                             /*UEģʽ*/
} LNAS_MTA_QRY_UE_CENTER_CNF_STRU;
/* Added by lwx277467 for UE Mode, 2015-9-7, end */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    NAS_MTA_MSG_TYPE_ENUM_UINT32        enMsgID;                                /*_H2ASN_MsgChoice_Export NAS_MTA_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_MTA_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}NAS_MTA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_MTA_MSG_DATA                     stMsgData;
} NasMtaInterface_MSG;


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

#endif
