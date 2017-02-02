

#ifndef __RRMRCMINTERFACE_H__
#define __RRMRCMINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "vos_Id.h"



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


enum RRM_RCM_MSG_TYPE_ENUM
{
    ID_RRM_RCM_PROTECT_RF_IND           = 0x0001,       /* _H2ASN_MsgChoice RRM_RCM_PROTECT_RF_IND_STRU */

    ID_RRM_RCM_DEPROTECT_RF_IND         = 0x0002,       /* _H2ASN_MsgChoice RRM_RCM_DEPROTECT_RF_IND_STRU */

    ID_RRM_RCM_ACTIVE_ID_NTF            = 0x0003,       /* _H2ASN_MsgChoice RRM_RCM_ACTIVE_ID_NTF_STRU */

    ID_RRM_RCM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 RRM_RCM_MSG_TYPE_ENUM_UINT32;

/*******************************************************************************
 ö����    : RRM_RCM_ACTIVE_ID_ENUM
 �ṹ˵��  : RRM RCM Active Id��ʶ����
*******************************************************************************/
enum RRM_RCM_ACTIVE_ID_ENUM
{
    RRM_RCM_ACTIVE_ID_0               = 0,   /* Active Id 0 ��ʶ */
    RRM_RCM_ACTIVE_ID_1               = 1,   /* Active Id 1 ��ʶ */
    RRM_RCM_ACTIVE_ID_2               = 2,   /* Active Id 2 ��ʶ */
    RRM_RCM_ACTIVE_ID_1X              = 3,   /* Active Id 1x ��ʶ */
    RRM_RCM_ACTIVE_ID_BUTT
};
typedef VOS_UINT16 RRM_RCM_ACTIVE_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRM_RCM_MODE_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �����ģʽ��ʾ ���д����У׼����һ��
*****************************************************************************/
enum RRM_RCM_MODE_ID_ENUM
{
    RRM_RCM_LTE                         = 0,                                    /* LTE */
    RRM_RCM_WCDMA                       = 1,                                    /* WCDMA */
    RRM_RCM_1X                          = 2,                                    /* 1X */
    RRM_RCM_HRPD                        = 3,                                    /* HRPD */
    RRM_RCM_TD                          = 4,                                    /* TD */
    RRM_RCM_G0                          = 5,                                    /* G0 */
    RRM_RCM_G1                          = 6,                                    /* G1 */
    RRM_RCM_G2                          = 7,                                    /* G2 */
    RRM_RCM_MODE_ID_BUTT
};
typedef VOS_UINT16  RRM_RCM_MODE_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    : RRM_RCM_RESOURCE_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : resoure ID
*****************************************************************************/
enum RRM_RCM_RESOURCE_ID_ENUM
{
    RRM_RCM_RESOURCE_0                            = 0,                          /* RESOURCE 0 */
    RRM_RCM_RESOURCE_1                            = 1,                          /* RESOURCE 1 */
    RRM_RCM_RESOURCE_ID_BUTT
};
typedef VOS_UINT16  RRM_RCM_RESOURCE_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    : RRM_RCM_DSDS_FLG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRM_RCM_DSDS_FLG_ENUM
*****************************************************************************/
enum RRM_RCM_DSDS_FLG_ENUM
{
    RRM_RCM_DSDS_CLOSE                            = 0,                          /* DSDS CLOSE */
    RRM_RCM_DSDS_OPEN                             = 1,                          /* DSDS OPEN  */
    RRM_RCM_DSDS_BUTT
};
typedef VOS_UINT16  RRM_RCM_DSDS_FLG_ENUM_UINT16;

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
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* ��Ϣ���� */  /* _H2ASN_Skip */
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */

} RRM_RCM_PROTECT_RF_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* ��Ϣ���� */  /* _H2ASN_Skip */
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */
} RRM_RCM_DEPROTECT_RF_IND_STRU;


typedef struct
{
    RRM_RCM_MODE_ID_ENUM_UINT16                 enModeId;
    RRM_RCM_ACTIVE_ID_ENUM_UINT16               enActiveId;                     /* Active Id */
    RRM_RCM_RESOURCE_ID_ENUM_UINT16             enResourceId;                   /* Resource Id */
    RRM_RCM_DSDS_FLG_ENUM_UINT16                enDsdsFlg;                      /* DSDS flag */
} RRM_RCM_MODE_ID_PARA_STRU;
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    RRM_RCM_MSG_TYPE_ENUM_UINT32                enMsgId;                        /* ��Ϣ���� */  /* _H2ASN_Skip */
    VOS_UINT16                                  usModeIdNum;
    VOS_UINT16                                  ausReserved[1];
    RRM_RCM_MODE_ID_PARA_STRU                   astModeIdPara[RRM_RCM_MODE_ID_BUTT];
} RRM_RCM_ACTIVE_ID_NTF_STRU;


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
 �ṹ��    : RRM_RCM_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRM_RCM_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    RRM_RCM_MSG_TYPE_ENUM_UINT32        enMsgId;    /*_H2ASN_MsgChoice_Export RRM_RCM_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          RRM_RCM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}RRM_RCM_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : RrmRcmInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RrmRcmInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    RRM_RCM_MSG_DATA                             stMsgData;
}RrmRcmInterface_MSG;


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

#endif /* end of RrmRcmInterface.h */

