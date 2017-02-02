/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CdsDhcpInterface.h
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��05��18��
  ����޸�   :
  ��������   : CDS��DHCP֮��Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��05��18��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CDSDHCPINTERFACE_H__
#define __CDSDHCPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "vos.h"
#include "LPSCommon.h"
#include "PsTypeDef.h"
#include "TTFMemInterface.h"

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DHCP_CDS_MSG_HDR                      (PS_MSG_ID_DHCP_TO_CDS_BASE)
#define CDS_DHCP_MSG_HDR                      (PS_MSG_ID_CDS_TO_DHCP_BASE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : DHCP_CDS_RESULT_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��DHCP���ص�ȷ����Ϣ
*****************************************************************************/
enum DHCP_CDS_RESULT_ENUM
{
    DHCP_CDS_RESULT_SUCC                     = 0x00,
    DHCP_CDS_RESULT_FAIL                     = 0x01,

    DHCP_CDS_RESULT_BUTT
};
typedef VOS_UINT32 DHCP_CDS_RESULT_ENUM_UINT32;

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
 �ṹ��    : DHCP_CDS_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCP��CDSģ���Ľӿ���Ϣ
*****************************************************************************/
enum DHCP_CDS_MSG_TYPE_ENUM
{
    ID_DHCP_CDS_START_FILTER_REQ             = (DHCP_CDS_MSG_HDR + 0x00),       /* DHCP֪ͨCDS�������� */
    ID_CDS_DHCP_START_FILTER_CNF             = (CDS_DHCP_MSG_HDR + 0x00),       /* ������Ϣȷ����Ϣ */

    ID_DHCP_CDS_STOP_FILTER_REQ              = (DHCP_CDS_MSG_HDR + 0x01),       /* DHCP֪ͨCDSֹͣ���� */
    ID_CDS_DHCP_STOP_FILTER_CNF              = (CDS_DHCP_MSG_HDR + 0x01),       /* ������Ϣȷ����Ϣ */

    ID_DHCP_CDS_DATA_REQ                     = (DHCP_CDS_MSG_HDR + 0x02),       /* DHCP��CDS������Ϣ */

    ID_DHCP_CDS_MSG_TYPE_END
};
typedef VOS_UINT16 DHCP_CDS_MSG_TYPE_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : DHCP_CDS_DATA_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCP��CDS������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16      enMsgId;             /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16               enModemId;           /*ModemId*/
    VOS_UINT8                          ucRabId;             /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    VOS_UINT8                          aucRev[3];           /*����λ*/
    TTF_MEM_ST                        *pstIpPacket;         /*���ݰ�ָ��*/
} DHCP_CDS_DATA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : DHCP_CDS_START_FILTER_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCP��CDS���Ϳ�����������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
} DHCP_CDS_START_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CDS_DHCP_START_FILTER_CNF
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��DHCP�ظ�����DHCP��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    DHCP_CDS_RESULT_ENUM_UINT32         enRslt;
} CDS_DHCP_START_FILTER_CNF_STRU;

/*****************************************************************************
 �ṹ��    : DHCP_CDS_STOP_FILTER_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DHCP��CDS����ֹͣ��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
} DHCP_CDS_STOP_FILTER_REQ_STRU;

/*****************************************************************************
 �ṹ��    : CDS_DHCP_STOP_FILTER_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS��DHCP�ظ�ֹͣ��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    DHCP_CDS_MSG_TYPE_ENUM_UINT16       enMsgId;            /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                enModemId;          /*ModemId*/
    DHCP_CDS_RESULT_ENUM_UINT32         enRslt;
} CDS_DHCP_STOP_FILTER_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
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

#endif /* end of CdsDhcpInterface.h */

