

#ifndef __FCCDSINTERFACE_H__
#define __FCCDSINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "OmApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/
enum CDS_FC_MSG_TYPE_ENUM
{
    ID_CDS_FC_START_CHANNEL_IND       = 0x0001,     /* _H2ASN_MsgChoice CDS_FC_START_CHANNEL_IND_STRU */
    ID_CDS_FC_STOP_CHANNEL_IND        = 0x0002,     /* _H2ASN_MsgChoice CDS_FC_STOP_CHANNEL_IND_STRU */
    ID_FC_CDS_DL_THRES_CHG_IND        = 0x0003,     /* _H2ASN_MsgChoice FC_CDS_THRES_CHG_IND_STRU */
    ID_CDS_FC_MSG_TYPE_BUTT           = 0xFFFF
};
typedef VOS_UINT32 CDS_FC_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  2 �궨��
*****************************************************************************/


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
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[1];
} CDS_FC_START_CHANNEL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;          /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucReserved[1];
} CDS_FC_STOP_CHANNEL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgName;          /* _H2ASN_Skip */
    VOS_UINT8                           ucThres;
    VOS_UINT8                           aucReserved[3];
}FC_CDS_THRES_CHG_IND_STRU;
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
    CDS_FC_MSG_TYPE_ENUM_UINT32         enMsgID;    /*_H2ASN_MsgChoice_Export CDS_FC_MSG_TYPE_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CDS_FC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}FC_CDS_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    FC_CDS_MSG_DATA                     stMsgData;
}FcCdsInterface_MSG;


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_DownUlGradeProcess(VOS_VOID);
extern SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_UpUlGradeProcess(VOS_VOID);
extern VOS_VOID FC_RecoverUlGradeProcess(VOS_VOID);
extern unsigned int FC_CPU_Process( unsigned int ulCpuLoad );


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

#endif /* end of FcCdsInterface.h */

