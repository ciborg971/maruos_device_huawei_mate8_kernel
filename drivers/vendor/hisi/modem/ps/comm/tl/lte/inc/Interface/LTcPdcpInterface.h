/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : LTCPdcpInterface.h
  �� �� ��   : ����
  ��    ��   : L62099
  ��������   : 2009��10��9��
  ����޸�   :
  ��������   : TC��PDCP֮�价��ģʽ�ӿڶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2009��10��9��
    ��    ��   : L62099
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __TCLPDCPINTERFACE_H__
#define __TCLPDCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


#include "vos.h"
#include "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

#define LLOOP_BACK_MODE_MAX_LB_NUM       (8)

#define LTC_LPDCP_MSG_HDR                (PS_MSG_ID_LTC_TO_LPDCP_BASE)
#define LPDCP_LTC_MSG_HDR                (PS_MSG_ID_LPDCP_TO_LTC_BASE)

/*****************************************************************************
 �ṹ��    : TC_LPDCP_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TC��PDCP��Ľӿ���Ϣ
*****************************************************************************/
enum LTC_LPDCP_MSG_TYPE_ENUM
{
    ID_LTC_LPDCP_ACTIVATE_TEST_MODE          = (LTC_LPDCP_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice LTC_LPDCP_ACTIVATE_TEST_MODE_STRU */
    ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF      = (LPDCP_LTC_MSG_HDR + 0x00),  /* _H2ASN_MsgChoice LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU */

    ID_LTC_LPDCP_START_TEST_LOOP             = (LTC_LPDCP_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice LTC_LPDCP_START_TEST_LOOP_STRU */
    ID_LTC_LPDCP_START_TEST_LOOP_CNF         = (LPDCP_LTC_MSG_HDR + 0x01),  /* _H2ASN_MsgChoice LTC_LPDCP_START_TEST_LOOP_CNF_STRU */

    ID_LTC_LPDCP_STOP_TEST_LOOP              = (LTC_LPDCP_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice LTC_LPDCP_STOP_TEST_LOOP_STRU */
    ID_LTC_LPDCP_STOP_TEST_LOOP_CNF          = (LPDCP_LTC_MSG_HDR + 0x02),  /* _H2ASN_MsgChoice LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU */

    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE        = (LTC_LPDCP_MSG_HDR + 0x03),  /* _H2ASN_MsgChoice LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU */
    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF    = (LPDCP_LTC_MSG_HDR + 0x03)   /* _H2ASN_MsgChoice LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU */
};
typedef VOS_UINT32 LTC_LPDCP_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ����ö��
*****************************************************************************/
enum LTC_LPDCP_LOOPBACK_MODE_ENUM
{
    LLOOP_BACK_MODE_A = 0,
    LLOOP_BACK_MODE_B = 1,
    LLOOP_BACK_MODE_BUTT
};
typedef VOS_UINT32 LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_ACTIVATE_TEST_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PDCP���ع�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32  enLoopBackMode;
}LTC_LPDCP_ACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PDCP���ع���ȷ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                         ulResult;
}LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU;


/*****************************************************************************
 �ṹ��    : LLOOP_BACK_DRB_SETUP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽAʱ��չ�������ýṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrbId;
    VOS_UINT32                          ulSduSize;
}LLOOP_BACK_DRB_SETUP_STRU;

/*****************************************************************************
 �ṹ��    : LLOOP_BACK_MODE_A_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽAʱLB����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrbNum;
    LLOOP_BACK_DRB_SETUP_STRU           astDrbSetup[LLOOP_BACK_MODE_MAX_LB_NUM];
}LLOOP_BACK_MODE_A_STRU;

/*****************************************************************************
 �ṹ��    : LLOOP_BACK_MODE_B_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽBʱLB����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDelayTime;
}LLOOP_BACK_MODE_B_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_START_TEST_LOOP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ģʽ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    LTC_LPDCP_LOOPBACK_MODE_ENUM_UINT32  enLoopBackMode;
    union
    {
        LLOOP_BACK_MODE_A_STRU           stLBModeA;
        LLOOP_BACK_MODE_B_STRU           stLBModeB;
    }u;
}LTC_LPDCP_START_TEST_LOOP_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_START_TEST_LOOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ģʽȷ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_START_TEST_LOOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_STOP_TEST_LOOP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ����ģʽ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
}LTC_LPDCP_STOP_TEST_LOOP_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ����ģʽȷ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȥ�����ģʽ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
}LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU;

/*****************************************************************************
 �ṹ��    : LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ȥ�����ģʽȷ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32       enMsgName;           /*_H2ASN_Skip*/
    VOS_UINT32                          ulResult;
}LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU;

typedef struct
{
    LTC_LPDCP_MSG_TYPE_ENUM_UINT32        enMsgId;            /*_H2ASN_MsgChoice_Export LTC_LPDCP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LTC_LPDCP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LTC_LPDCP_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LTC_LPDCP_MSG_DATA                    stMsgData;
}LTcLPdcpInterface_MSG;

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

#endif

