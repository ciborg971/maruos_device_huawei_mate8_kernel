/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ImsNicInterface.h
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2013��7��16��
  ����޸�   :
  ��������   : IMS���������ṩ�Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __IMSNICINTERFACE_H__
#define __IMSNICINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"

#if( FEATURE_ON == FEATURE_IMS )
#include  "PsTypeDef.h"


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define   IMS_NIC_IPV4_ADDR_LENGTH          (4)     /* IPV4��ַ���ȣ���λ�ֽ� */
#define   IMS_NIC_IPV6_ADDR_LENGTH          (16)    /* IPV6��ַ����, ��λ�ֽ� */

#if ((VOS_OS_VER == VOS_RTOSCK) || ((VOS_OS_VER == VOS_WIN32) && (VOS_PC_TEST == VOS_RTOSCK)))
#define   IMS_NIC_MAX_DNS_SERVER_NUM        (6)     /* VISP����������6��DNS��������һ������ */
#else
#define   IMS_NIC_MAX_DNS_SERVER_NUM        (4)     /* Interpeak����������4��DNS��������һ������ */
#endif

//#define   IMS_NIC_DEBUG

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ����ֵ��� */
enum IMS_NIC_ERROR_CODE_ENUM
{
     IMS_NIC_SUCC                                   = 0,    /* �ɹ� */
     IMS_NIC_FAIL,                                          /* ʧ�� */

     IMS_NIC_CONFIG_PTR_NULL,                               /* ��������ýṹָ��Ϊ�� */
     IMS_NIC_MODEM_ID_INVALID,                              /* ModemId��Ч */
     IMS_NIC_RABID_INVALID,                                 /* ����ĳ��غ���Ч */
     IMS_NIC_DNS_SERVER_FULL,                               /* DNS����������������������ĸ���һ������ */
     IMS_NIC_PREFIXLEN_INVALID,                             /* IPV6ǰ׺������Ч */
     IMS_NIC_RABID_IDLE,                                    /* ����ĳ��غ���û�ж�Ӧ�����ã�ɾ���ӿ���ʹ�� */
     IMS_NIC_MTU_INVALID,                                   /* �����MTUֵ��Ч */
     IMS_NIC_ALREADY_INITED,                                /* ���������Ѿ���ʼ�� */
     IMS_NIC_NOT_INITED,                                    /* ��������û�г�ʼ�� */
     IMS_NIC_SYSCALLFAIL,                                   /* ϵͳ����ʧ�� */
     IMS_NIC_NO_CFG_PDN,                                    /* û���κ����� */

     IMS_NIC_ERR_BUTT
};
typedef VOS_UINT32 IMS_NIC_ERROR_CODE_ENUM_UINT32;

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
/*****************************************************************************
 �ṹ��    : IMS_NIC_IPV4_PDN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV4 ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* �ⲿģ����д��ָʾaucDnsPrimAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* �ⲿģ����д��ָʾaucDnsSecAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT8                           aucIpV4Addr[IMS_NIC_IPV4_ADDR_LENGTH];       /* IP��ַ */
    VOS_UINT8                           aucDnsPrimAddr[IMS_NIC_IPV4_ADDR_LENGTH];    /* ��DNS������IP */
    VOS_UINT8                           aucDnsSecAddr[IMS_NIC_IPV4_ADDR_LENGTH];     /* ��DNS������IP */
}IMS_NIC_IPV4_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_IPV6_PDN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IPV6 ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpDnsPrim         :1;                     /* �ⲿģ����д��ָʾaucDnsPrimAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpDnsSec          :1;                     /* �ⲿģ����д��ָʾaucDnsSecAddr�Ƿ���Ҫ���� */
    VOS_UINT32                          bitOpSpare           :30;

    VOS_UINT32                          ulBitPrefixLen;                              /* IPV6ǰ׺����,��λΪbit */
    VOS_UINT8                           aucIpV6Addr[IMS_NIC_IPV6_ADDR_LENGTH];       /* IP��ַ */
    VOS_UINT8                           aucDnsPrimAddr[IMS_NIC_IPV6_ADDR_LENGTH];    /* ��DNS������IP */
    VOS_UINT8                           aucDnsSecAddr[IMS_NIC_IPV6_ADDR_LENGTH];     /* ��DNS������IP */
} IMS_NIC_IPV6_PDN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_SOCK_PORT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �˿ڷ�Χ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSockMinPort;      /* socket �˿ڷ�Χ���� */
    VOS_UINT16                          usSockMaxPort;      /* socket �˿ڷ�Χ���� */
} IMS_NIC_SOCK_PORT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMS_NIC_PDN_INFO_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMS��������PDN������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIpv4PdnInfo : 1;
    VOS_UINT32                          bitOpIpv6PdnInfo : 1;
    VOS_UINT32                          bitOpSockPortInfo: 1;
    VOS_UINT32                          bitOpSpare       : 29;

    MODEM_ID_ENUM_UINT16                enModemId;          /* ��ǰModem�� */
    VOS_UINT8                           ucRabId;            /* ���غţ�ȡֵ��Χ[5,15] */
    VOS_UINT8                           ucReserved[1];      /* ��Ϣ�ṹ�����*/

    IMS_NIC_IPV4_PDN_INFO_STRU          stIpv4PdnInfo;
    IMS_NIC_IPV6_PDN_INFO_STRU          stIpv6PdnInfo;
    IMS_NIC_SOCK_PORT_INFO_STRU         stSockPortInfo;
}IMS_NIC_PDN_INFO_CONFIG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/* IMS���������������ݷ��ͻص����� */
typedef VOS_UINT32 (*IMS_NIC_SEND_UL_DATA_FUNC)(VOS_UINT8 *pData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoConfig
 ��������  : IMS�����������ýӿ�,��IMSAģ�����
 �������  : pstConigInfo   IMS��������������Ϣ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_PdnInfoConfig (IMS_NIC_PDN_INFO_CONFIG_STRU *pstConigInfo);

/*****************************************************************************
 �� �� ��  : IMS_NIC_PdnInfoDel
 ��������  : IMS��������PDN������Ϣɾ������IMSAģ����PDNȥ��������
 �������  : ucRabId        ���غ�
             enModemId      ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_PdnInfoDel(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
 �� �� ��  : IMS_NIC_MtuSet
 ��������  : IMS��������MTU����
 �������  : ulMtu        ����͵�Ԫ
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��Ϊ��Ӧ�Ĵ�����

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_MtuSet(VOS_UINT32 ulMtu);

/*****************************************************************************
 �� �� ��  : IMS_NIC_RegUlDataSendCb
 ��������  : ע��IMS���������������ݷ��ͻص���������CDSģ�����
 �������  : pFunc        �������ݷ��ͻص��ӿ�
             enModemId    ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��:IMS_NIC_FAIL

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_RegUlDataSendCb(IMS_NIC_SEND_UL_DATA_FUNC pFunc, MODEM_ID_ENUM_UINT16 enModemId);

/*****************************************************************************
 �� �� ��  : IMS_NIC_RegUlDataSendCb
 ��������  : IMS���������������ݽ��սӿڣ��ṩ��CDS����
 �������  : pucData      IP������
             usLen        IP�����ȣ���λ:�ֽ�
             enModemId    ��ǰmodemID
 �������  : ��
 �� �� ֵ  : �ɹ�:IMS_NIC_SUCC��ʧ��:IMS_NIC_FAIL

*****************************************************************************/
extern VOS_UINT32 IMS_NIC_DlDataRcv(VOS_UINT8 *pucData, VOS_UINT16 usLen, MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_UINT32 IMS_NIC_InitAll(VOS_VOID);

extern VOS_UINT32 IMS_NIC_GetMntnInfo
(
    VOS_UINT8                       *pucData,
    VOS_UINT32                      *pulLen,
    VOS_UINT16                       usType
);

#endif  /*FEATURE_ON == FEATURE_IMS*/

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

#endif /* end of ImsNicInterface.h */


