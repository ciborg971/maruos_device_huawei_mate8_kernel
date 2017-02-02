/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Phy_Lapdm_Interface.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2007��9��5��
  ����޸�   :
  ��������   : ��ͷ�ļ���Э��ջLapdm�������֮��Ľӿ��ļ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��5��
    ��    ��   : ���ɱ�
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _PHY_LAPDM_INTERFACE_H_
#define _PHY_LAPDM_INTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(1)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* L1 �� Lapdm ֮���ԭ�� */
#define ID_PH_CONNECT_IND                           0x7301
#define ID_PH_READY_TO_SEND                         0x7302
#define ID_PH_EMPTY_FRAME                           0x3701
#define ID_PH_DATA_REQ                              0x3702
#define ID_PH_DATA_IND                              0x7303

/* �ŵ����Ͷ��� */
#define L2_CHANNEL_SACCH                            0x0001
#define L2_CHANNEL_SDCCH                            0x0002
#define L2_CHANNEL_FACCH_H                          0x0003
#define L2_CHANNEL_FACCH_F                          0x0004
#define L2_CHANNEL_CCCH                             0x0005
#define L2_CHANNEL_NBCCH                            0x0006
#define L2_CHANNEL_PCH                              0x0007
#define L2_CHANNEL_EPCH                             0x0008
#define L2_CHANNEL_CBCH                             0x0009
#define L2_CHANNEL_EBCCH                            0x000a

/* ö�����Ͷ��� */

/*******************************************************************************
 ö����   : DL_ACCH_REPEATED_ENUM
 Э���� :
 ö��˵�� : ACCH_REPEATED_CAPABILITY
*******************************************************************************/
enum DL_REPEAT_SA_FLAG_ENUM
{
    DL_NOT_REPEAT_SA_FLAG  = 0,
    DL_REPEAT_SA_FLAG      = 1,
    DL_REPEAT_SA_FLAG_BUTT
};
typedef VOS_UINT16 DL_REPEAT_SA_FLAG_ENUM_UINT16;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usChanType;
} PH_CONNECT_IND;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;   	/* �����ŵ����� */
    DL_REPEAT_SA_FLAG_ENUM_UINT16   usRepeatedSaFlg;    /* �Ƿ���Ҫ�ظ�����SACCH����usL2ChanTypeΪL2_CHANNEL_SACCHʱʹ��
                                                           usRepeatedSaCycFlg Ϊ1ʱ��ʾ�����ظ���SACCH,Ϊ0ʱ��������SACCH */
    VOS_UINT16                      usRsv;              /* �������������ֽڶ��� */
    VOS_UINT32                      ulRptFN;            /* ��Ϣ����ʱ��֡�� */
} PH_READY_TO_SEND;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;     	/* �����ŵ����� */
} PH_EMPTY_FRAME;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;
    VOS_UINT16                      usL2ChanType;
    VOS_UINT16                      usRepeatedSaFlg;    /* �Ƿ�Ϊ�ظ�����SACCH��ָʾ */
                                                        /* usRepeatedSaFlg Ϊ1ʱ��ʾ�����ظ�����SA��,Ϊ0ʱ��������SA�� */
    VOS_UINT16                      usRsv;              /* �������������ֽڶ��� */
    VOS_UINT16                      ausL2Frame[12];     /* 23x8���ص����� */
} PH_DATA_REQ;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                      usMsgID;            /* ԭ������ */
    VOS_UINT16                      usFreqInfo;         /* BCCH��Ƶ��,��ӦGSM���ŵ��� */
    VOS_UINT16                      usL2ChanType;       /* �ŵ�������,��Ӧ���������ŵ� */
    VOS_UINT16                      usErrFlag;          /* L1�Ƿ�������ȷ,0��ʾ������ȷ,1��ʾ���� */
    VOS_UINT16                      usTC;               /* ( FN div 51 ) % 8 */
    VOS_UINT16                      usCCCHLevel;        /* CCCH�ŵ��Ľ��յ�ƽ, (-120+316~-15+316)dbm */
    VOS_UINT32                      ulFN;

    /* usRepeatedSaFlg ��Ҫ���usErrFlagʹ��, usErrFlag = 0��usRepeatedSaFlg = 1,
       ˵�������ݿ���Ҫ���������ݿ�;usErrFlag = 1��usRepeatedSaFlg = 1,˵�������ݿ�����T200����
       usRepeatedSaFlg = 0���ñ�־��ʹ��  */
    VOS_UINT16                      usRepeatedFaFlg;    /*  �Ƿ�Ϊ�ظ�FACCH��ָʾ,���CRC��ȷ������ǰһ��FACCH���8֡��
                                                            CRCҲ��ȷ����������FACCH������ͬ����ñ�־��Ϊ1��������Ϊ0 ;
                                                            8֡����9֮֡ǰ�ܵ���FACCH�����CRC������ñ�־��Ϊ1��������Ϊ0*/

    VOS_UINT16                      usHarqFlg;          /* �Ƿ�Ϊ����������,1:��������(Harq) 0:���������� */
    VOS_UINT16                      ausL2Frame[12];     /* �ϱ���L2֡����, ��23X8���ص����� */
} PH_DATA_IND ;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* end of _PHY_LAPDM_INTERFACE_H_ */

