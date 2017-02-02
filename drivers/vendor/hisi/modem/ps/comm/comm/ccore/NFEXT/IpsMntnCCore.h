/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : IpsMntnCCore.h
  �� �� ��   : ����
  ��    ��   : caikai
  ��������   : 2013��7��23��
  ����޸�   :
  ��������   : IPS MNTNģ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��16��
    ��    ��   : caikai
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __IPSMNTNCCORE_H__
#define __IPSMNTNCCORE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TTFComm.h"

#if (FEATURE_ON == FEATURE_IMS)
#include "ImsNicInterface.h"
#include "ImsNic.h"
#include "TtfOamInterface.h"

#include "tcpip/tcpip.h"
#include "tcpip/public/arith_cbb/include/mbuf.h"
#include "tcpip/public/arith_cbb/include/utlsll.h"
#include "tcpip/tcpip_ipv6.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define IPS_MNTN_CCORE_INFO_LEN                 (10000)           /*TCP/IPЭ��ջ������Ϣ�����*/

#define IPS_MNTN_CCORE_INFO_TYPE_LEN            (2)
#define IPS_MNTN_CCORE_INFO_TYPE_OFFSET         (4)               /*TCP/IPЭ��ջ������Ϣ����ƫ��*/
#define IPS_MNTN_CCORE_INFO_LEN_OFFSET          (4)               /*TCP/IPЭ��ջ������Ϣ����ƫ��*/

#define IPS_MNTN_CCORE_OK                       (0)
#define IPS_MNTN_CCORE_ERROR                    (-1)

#define IPS_CCORE_IFNAMSIZ                      (16)                    /*�����������Ƴ���*/
#define IPS_CCORE_END_NAME                      (8)
#define IPS_CCORE_APP_CMD_INFO_LEN              (256)                   /*����APP��������������*/
#define IPS_MNTN_CCORE_TRACE_MAX_BYTE_LEN       (1514)                  /*����TCP/IPЭ��ջ��������� */
#define IPS_MNTN_CCORE_NAT_MAPPING_INFO_LEN     (40)                    /*����TCP/IPЭ��ջNATӳ����Ϣ��������*/
#define IPS_ARRAY_SIZE(x)                       (sizeof(x) / sizeof(x[0]))

#define IPS_MNTN_CCORE_LINK_LAYER_UP_MASK       (1)                     /* ��·������ץ����־ */
#define IPS_MNTN_CCORE_LINK_LAYER_DOWN_MASK     (1 << 1)                /* ��·������ץ����־ */
#define IPS_MNTN_CCORE_IPV4_CAPTRURE_UP_MASK    (1 << 2)                /* IPV4��������ץ����־ */
#define IPS_MNTN_CCORE_IPV4_CAPTRURE_DOWN_MASK  (1 << 3)                /* IPV4��������ץ����־ */
#define IPS_MNTN_CCORE_IPV6_CAPTRURE_UP_MASK    (1 << 4)                /* IPV6��������ץ����־ */
#define IPS_MNTN_CCORE_IPV6_CAPTRURE_DOWN_MASK  (1 << 5)                /* IPV6��������ץ����־ */
#define ARRAY_SIZE(x)                           (sizeof(x) / sizeof(struct x))                  /* ���������Ա���� */
#define IPS_MNTN_CCORE_LINK_UP_TYPE             (0)                    /* ��·��ץ���������� */
#define IPS_MNTN_CCORE_LINK_DOWN_TYPE           (1)                    /* ��·��ץ���������� */
#define IPS_MNTN_CCORE_MAX_IPV4_ADDR_NUM        (100)                  /* ���ϱ�OM�����IPV4��ַ���� */
#define IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN     (12)                   /* ������Ϣͷ���� */

/* ���ϱ�OM�����IPV6·������ */
#define IPS_MNTN_CCORE_MAX_IPV6_ROUTE_ITEM              \
    (IPS_MNTN_CCORE_INFO_LEN / (IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN + sizeof(TCPIP_RT6_ENTRY_S)))

/* ���ϱ�OM�����IPV4·������ */
#define IPS_MNTN_CCORE_MAX_IPV4_ROUTE_ITEM              \
    (IPS_MNTN_CCORE_INFO_LEN / (IPS_MNTN_CCORE_BASE_INFO_OFFSET_LEN + sizeof(TCPIP_RT4_ENTRY_S)))

/*�����Ϣͷ*/
#define IPS_CCORE_FILL_MSG_HEADER(pSendMsg, RecvPid)    \
        (pSendMsg)->ulReceiverCpuId  = VOS_LOCAL_CPUID; \
        (pSendMsg)->ulReceiverPid    = RecvPid;

#define IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN        /*lint -e(545) -e(413)*/(sizeof(DIAG_TRANS_IND_STRU))

#define IPS_CCORE_PKT_INFO_OFFSET_LEN             /*lint -e(545) -e(413)*/(offsetof(IPS_MNTN_CCORE_PKT_INFO_STRU, aucData))

#define IPS_CCORE_BRIDGE_PKT_INFO_OFFSET_LEN      /*lint -e(545) -e(413)*/(offsetof(IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU, aucData))

#define IPS_CCORE_APP_CMD_INFO_OFFSET_LEN         /*lint -e(545) -e(413)*/(offsetof(IPS_MNTN_CCORE_APP_CMD_INFO_STRU, aucData))

#define IPS_CCORE_INFO_LEN                      (IPS_CCORE_OM_TRANS_DATA_OFFSET_LEN + IPS_MNTN_CCORE_INFO_LEN)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum IPS_MNTN_CCORE_TIMER_NAME_ENUM
{
    IPS_MNTN_CCORE_INFO_TIMER                 = 0x00000001,           /*�����Բ���TCP/IPЭ��ջ������Ϣ��ʱ��*/

    IPS_MNTN_CCORE_TIMER_NAME_BUTT
};
typedef VOS_UINT32 IPS_MNTN_CCORE_TIMER_NAME_ENUM_UINT32;

/*TCP/IPЭ��ջ������Ϣ����*/
enum IPS_MNTN_CCORE_BASE_INFO_ENUM
{
    ID_IPS_MNTN_CCORE_NETIF_INFO              = 0x1001,               /* ����������Ϣ */
    ID_IPS_MNTN_CCORE_TCP_INFO                = 0x1002,               /* TCP����������Ϣ */
    ID_IPS_MNTN_CCORE_UDP_INFO                = 0x1003,               /* UDP����������Ϣ */
    ID_IPS_MNTN_CCORE_IPV4_ROUTE_INFO         = 0x1004,               /* IPV4·����Ϣ */
    ID_IPS_MNTN_CCORE_IPV6_ROUTE_INFO         = 0x1005,               /* IPV6·����Ϣ */
    ID_IPS_MNTN_CCORE_IPV4_ADDR_INFO          = 0x1006,               /* IPV4��ַ��Ϣ */
    ID_IPS_MNTN_CCORE_IPV6_ADDR_INFO          = 0x1007,               /* IPV6��ַ��Ϣ */

    ID_IPS_MNTN_CCORE_BASE_INFO_BUTT          = 0xffff
};
typedef unsigned short IPS_MNTN_CCORE_BASE_INFO_ENUM_UINT16;

/*TCP/IPЭ��ջ������Ϣ����*/
enum IPS_MNTN_CCORE_INFO_TYPE_ENUM
{
    ID_IPS_MNTN_CCORE_IFCONFIG_INFO           = 0x1001,               /*����������Ϣ*/
    ID_IPS_MNTN_CCORE_NETSTAT_ROUTES_INFO     = 0x1002,               /*·����Ϣ*/
    ID_IPS_MNTN_CCORE_NETSTAT_ENTRIES_INFO    = 0x1003,               /*����״̬��Ϣ*/
    ID_IPS_MNTN_CCORE_NAT_RULES_INFO          = 0x1004,               /*NAT�������Ϣ*/
    ID_IPS_MNTN_CCORE_NAT_STATS_INFO          = 0x1005,               /*NAT��״̬��Ϣ*/
    ID_IPS_MNTN_CCORE_NAT_PROXIES_INFO        = 0x1006,               /*NAT��Э����Ϣ*/
    ID_IPS_MNTN_CCORE_NAT_MAPPINGS_INFO       = 0x1007,               /*NAT��ӳ����Ϣ*/

    ID_IPS_MNTN_CCORE_NAT_TYPE_BUTT           = 0xffff
};
typedef unsigned short IPS_MNTN_CCORE_INFO_TYPE_ENUM_UINT16;

/* Interpeak��ά�ɲ�ص������±�ָʾ */
enum IPS_MNTN_CCORE_CB_TYPE_ENUM
{
    IPS_MNTN_CCORE_INPUT_DATA_CB        = 0,    /*TCP/IP��ά�ɲ���ձ���*/
    IPS_MNTN_CCORE_OUTPUT_DATA_CB,              /*TCP/IP��ά�ɲⷢ�ͱ���*/
    IPS_MNTN_CCORE_BRIDGE_DATA_CB,              /*TCP/IP������ת����*/
    IPS_MNTN_CCORE_RECV_ARP_CB,                 /*TCP/IPЭ��ջ���յ�ARP���Ʊ���*/
    IPS_MNTN_CCORE_SEND_ARP_CB,                 /*TCP/IPЭ��ջ���͵�ARP���Ʊ���*/
    IPS_MNTN_CCORE_RECV_DHCPC_CB,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    IPS_MNTN_CCORE_SEND_DHCPC_CB,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    IPS_MNTN_CCORE_RECV_DHCPS_CB,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    IPS_MNTN_CCORE_SEND_DHCPS_CB,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    IPS_MNTN_CCORE_APP_CMD_CB,                  /*APP����������Ϣ*/

    IPS_MNTN_CCORE_CB_TYPE_BUTT
};
typedef unsigned short  IPS_MNTN_CCORE_CB_TYPE_ENUM_UINT16;

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
#pragma pack(4)

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_CAPTURE_CB_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Interpeak��ά�ɲ�ص����������ṹ
*****************************************************************************/
typedef struct
{
    unsigned char      *paucNetIfName;  /* ����������Ϣ*/
    unsigned char      *paucSrcPort;    /* ��������������Ϣ������ʹ��*/
    unsigned char      *paucDestPort;   /* ��������������Ϣ������ʹ��*/
    unsigned char      *pucData;        /* ��������ָ��,����Ϊ������Ϣ����APP���� */
    unsigned short      usLen;          /* �������ݳ��� */
    unsigned char       aucRsv[2];      /* �������ݳ��� */
}IPS_MNTN_CCORE_CAPTURE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_INFO_ENTITY
 �ṹ˵��  : ����TCP/IPЭ��ջ������Ϣʵ��
*****************************************************************************/
typedef struct
{
    HTIMER                                    hIpsMntnTimer;          /*��ʱ��*/
    VOS_UINT32                                ulIpsMntnTimerLen;      /*��ʱ�����ȣ��̶�1s*/
    IPS_MNTN_CCORE_INFO_ACTION_ENUM_UINT16    enIpsMntnFlag;          /*����TCP/IPЭ��ջ������Ϣ������־*/
    VOS_UINT8                                 aucRsv[2];
}IPS_MNTN_CCORE_INFO_ENTITY;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_PKT_INFO_STRU
 �ṹ˵��  : TCP/IPЭ��ջ���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT8                               aucNetIfName[IPS_CCORE_IFNAMSIZ]; /* ������������ */

    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_CCORE_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU
 �ṹ˵��  : ������ת���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT8                               aucSrcPort[IPS_CCORE_END_NAME];   /* ��������������Ϣ */
    VOS_UINT8                               aucDestPort[IPS_CCORE_END_NAME];  /* ���������������� */

    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_CCORE_BRIDGE_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_APP_CMD_INFO_STRU
 �ṹ˵��  : APP���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usPrimId;
    VOS_UINT16                              usToolId;

    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_CCORE_APP_CMD_INFO_STRU;

typedef VOS_UINT32 (*pfHookCb)(MBUF_S *pstMBuf);
typedef VOS_UINT32 (*pfRegHook)(VOS_UINT32 ulType, VOS_UINT32 ulPriority, pfHookCb pfHookCbFunc);
typedef VOS_UINT32 (*pfUnRegHook)(VOS_UINT32 ulType, pfHookCb pfHookCbFunc);

/*****************************************************************************
 �ṹ��    : IPS_MNTN_CCORE_HOOK_MASK_OPS_STRU
 �ṹ˵��  : RTOSckƽ̨��ά�ɲ�ӿڹ��Ӻ���������ע��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                              ulMask;
    VOS_UINT32                              ulType;
    VOS_UINT32                              ulPriority;
    pfHookCb                                pfHookCbFunc;
    pfRegHook                               pfRegHookFunc;
    pfUnRegHook                             pfUnRegHookFunc;
}IPS_MNTN_CCORE_HOOK_MASK_OPS_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern IPS_MNTN_CCORE_TRACE_CONFIG_REQ_STRU          g_stIpsCcoreTraceMsgCfg;

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IPS_MNTN_CCORE_PktInfo
(
    VOS_UINT8                                    *pucPktData,
    VOS_UINT16                                    usPktLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                 usType
);
extern VOS_VOID IPS_MNTN_CCORE_IpsMntnInfoTimeoutProc(VOS_VOID);
extern VOS_VOID IPS_MNTN_CCORE_OutputIpsInfo
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usType
);
extern VOS_VOID IPS_MNTN_CCORE_OutputIpsNatMappingsInfo
(
    VOS_UINT8                          *pucData
);
extern VOS_VOID IPS_MNTN_CCORE_OutputImsNicStatsInfo
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usType
);
extern VOS_UINT32 IPS_MNTN_CCORE_GetPktLenByTraceCfg
(
    IPS_MNTN_CCORE_TRACE_CONFIG_STRU     *pstTraceCfg,
    VOS_UINT16                            usPktLen,
    VOS_UINT32                           *pulDataLen
);
extern VOS_VOID IPS_MNTN_CCORE_TransMsg
(
    VOS_UINT8                                       *pucTransMsg,
    VOS_UINT32                                       ulTransMsgContentLen,
    TTF_MNTN_MSG_TYPE_ENUM_UINT16                    enMsgName
);
extern VOS_UINT32 IPS_MNTN_CCORE_ReRegHooks(VOS_UINT32 ulMask);
extern VOS_VOID IPS_MNTN_CCORE_UnregHooks(VOS_UINT32 ulMask);
extern VOS_UINT32 IPS_MNTN_CCORE_RegHooks(VOS_UINT32 ulMask);
extern VOS_UINT32 IPS_MNTN_CCORE_IpLayerUpCapCB(MBUF_S *pMBuf);
extern VOS_UINT32 IPS_MNTN_CCORE_IpLayerDownCapCB(MBUF_S *pMBuf);
extern VOS_VOID IPS_MNTN_CCORE_OutputNetIfInfo(VOS_UINT8 *pucData, VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_CCORE_OutputUdpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_CCORE_OutputTcpInfo(VOS_UINT8 *pucData, VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_CCORE_OutputRouteIpv4Info(VOS_UINT8 *pucData, VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_CCORE_OutputIpv4AddrInfo(VOS_UINT8 *pucData, VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_CCORE_PrintInfoCB(VOS_CHAR *pucData);
extern VOID IPS_MNTN_CCORE_TCPIP_FixlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel, ULONG ulLogType, VOID *ucMessage,
                        ULONG ulPara1, ULONG ulPara2, ULONG ulPara3, ULONG ulPara4);
extern VOID IPS_MNTN_CCORE_TCPIP_VarlenLogOutput(ULONG ulLogCode, ULONG ulLogLevel,
                        ULONG ulLogType, VOID* pcFormat, VOID* pData);
extern ULONG TCPIP_IPSEC_SetDebug (ULONG ulSet, ULONG ulDebugType);


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

#endif /* end of IpsMntnCCore.h */



