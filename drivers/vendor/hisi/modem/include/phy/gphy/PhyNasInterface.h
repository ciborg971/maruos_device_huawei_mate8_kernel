/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : PhyNasInterface.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2007��10��26��
  ����޸�   :
  ��������   : PhyNasInterface.h
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��10��26��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PHYNASINTERFACE_H__
#define __PHYNASINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#pragma pack(4)

#define     ID_APP_PHY_CODEC_ENABLE_REQ          0x9781
#define     ID_APP_PHY_CODEC_DISABLE_REQ         0x9782

/*TC ----> L1*/
#define 	TC_CLOSE_TCH_LOOP_REQ                 0xE701
#define 	TC_OPEN_TCH_LOOP_REQ                  0xE702
#define 	TC_TEST_INTERFACE_REQ                 0xE703
#define     TC_TEST_MODE_W_TO_G_IND               0xE704

/*L1 ----> TC*/
#define     TC_CLOSE_TCH_LOOP_CNF                 0x7E01
#define     TC_OPEN_TCH_LOOP_CNF                  0x7E02
#define     TC_TEST_INTERFACE_CNF                 0x7E03

/*VC ----> L1*/
#define     ID_VC_GPHY_TEST_MODE_NOTIFY           (0xE705)

#define     TCH_LOOP_TYPE_A            0
#define     TCH_LOOP_TYPE_B            1
#define     TCH_LOOP_TYPE_C            2
#define     TCH_LOOP_TYPE_D            3
#define     TCH_LOOP_TYPE_E            4
#define     TCH_LOOP_TYPE_F            5
#define     TCH_LOOP_TYPE_G            6
#define     TCH_LOOP_TYPE_H            7
#define     TCH_LOOP_TYPE_I            8
#define     TCH_LOOP_TYPE_ABNORMAL     0xFFFF
#define     TCH_LOOP_ALLCHAN           0
#define     TCH_LOOP_SUBCHAN           1
#define     TC_CLOSE_TCH_LOOP_FAIL     0
#define     TC_CLOSE_TCH_LOOP_SUCCESS  1
#define     TC_OPEN_TCH_LOOP_FAIL      0
#define     TC_OPEN_TCH_LOOP_SUCCESS   1
#define     TC_TEST_DEVICE_0           0
#define     TC_TEST_DEVICE_1           1
#define     TC_TEST_DEVICE_2           2
#define     TC_TEST_DEVICE_3           4
#define     TC_TEST_DEVICE_ABNORMAL    0XFFFF
#define     TC_TEST_INTERFACE_FAIL     0
#define     TC_TEST_INTERFACE_SUCCESS  1
#define     BURST_BY_BURST_RTD	       7    /* 3,7,9 is good. */
#define     TCH_LOOP_DELAY             0    /* other value is error. */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16         usMsgID;        /* ԭ��ID */
    VOS_UINT16         usRsv;          /* ���� */
} APP_PHY_CODEC_ENABLE_REQ_ST;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16         usMsgID;        /* ԭ��ID */
    VOS_UINT16         usRsv;          /* ���� */
} APP_PHY_CODEC_DISABLE_REQ_ST;

typedef struct tag_DEBUG_TC
{
    VOS_UINT16      RecTcClose;
    VOS_UINT16      RecTcCloseTypeErr;
    VOS_UINT16      RecTcOpen;
    VOS_UINT16      RecTcTI;
    VOS_UINT16      RecTcTIErr;
}DEBUG_TC;

typedef struct tag_TC_CLOSE_TCH_LOOP_REQ_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usTchLoopType;
    VOS_UINT16      usSubChan;
    VOS_UINT16      usRsv;
}TC_CLOSE_TCH_LOOP_REQ_STRU;

typedef struct tag_TC_CLOSE_TCH_LOOP_CNF_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usCloseFlag;
}TC_CLOSE_TCH_LOOP_CNF_STRU;

typedef struct tag_TC_OPEN_TCH_LOOP_REQ_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usAckInfo;
}TC_OPEN_TCH_LOOP_REQ_STRU;

typedef struct tag_TC_OPEN_TCH_LOOP_CNF_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usAckInfo;
    VOS_UINT16      usOpenFlag;
    VOS_UINT16      usRsv;
}TC_OPEN_TCH_LOOP_CNF_STRU;

typedef struct tag_TC_TEST_INTERFACE_REQ_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usTestDevice;
}TC_TEST_INTERFACE_REQ_STRU;

typedef struct tag_TC_TEST_INTERFACE_CNF_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usFlag;
}TC_TEST_INTERFACE_CNF_STRU;

typedef struct tag_TC_TEST_MODE_W_TO_G_IND_STRU
{
    VOS_MSG_HEADER
    VOS_UINT16      usMsgID;
    VOS_UINT16      usRsv;
}TC_TEST_MODE_W_TO_G_IND_STRU;

/*****************************************************************************
  7 STRUCT����
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

#endif /* __PHYNASINTERFACE_H__ */
