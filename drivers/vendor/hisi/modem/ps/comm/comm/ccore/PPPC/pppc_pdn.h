/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pppc_pdn.h
  �� �� ��   : ����
  ��    ��   : w00316385
  ��������   : 2015��05��29��
  ����޸�   :
  ��������   : PDN��صĶ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��05��29��
    ��    ��   : w00316385
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef _PPPC_PDN_H_
#define _PPPC_PDN_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "cnas_cttf_ehrpd_ehsm_ppp_pif.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PDN_IPV6ADDR_LEN        16      /* IPV6��ַ���� */
/*ÿ��PDN���֧��NetWrok��״̬���� */
#define MAX_STACK_PER_PDN  E_PDN_STACK_TYPE_BUTT
#define IP_POOL_NAME_LEN        31
#define PDN_MIP_SHAREKEY_LEN    32
#define PDN_USER_PROFILE_NAME_LENGTH 64
#define HSGW_MAX_APN_NAME_LEN   100
#define HSGW_MAX_PCO_LEN        253
#define RELTMR_T VOS_UINT32
#define A11_MAX_PDN_NUM         15      /* ÿ��RP��������PDN���� */
#define VSNCP_MAX_AMBR_LEN      8


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

typedef enum
{
    E_PDN_STACK_TYPE_IPV4,
    E_PDN_STACK_TYPE_IPV6,

    E_PDN_STACK_TYPE_BUTT
}PDN_STACK_TYPE_E;

/*****************************************************************************
  4 UNION����
*****************************************************************************/

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/* PPP֪ͨPDN NCP UPʱ�Ĳ��� */
typedef struct
{
    ULONG ulIpv4Addr;
    UCHAR aucIpV6Addr[PDN_IPV6ADDR_LEN];      /* IPv6CPЭ�̵ĵ�ַ */
}PDN_PPP_NCP_UP_S;

/* PDN�ĸ�����Ϣͷ */
typedef struct
{
    ULONG ulUpdateType;     /* ��������, PDN_UPDATE_TYPE_E */
    ULONG ulUpdateMask;     /* �������µ����� */
}PDN_UPDATE_MSGHEAD_S;

/* PPP���յ�PDN��ʼ���������VSNCP REQ��Ϣʱ�Ľӿڲ��� */
typedef struct
{
    PDN_UPDATE_MSGHEAD_S stHead;
    ULONG ulIpAddr;

    ULONG ulTotalMsgLen; /* vsncp��Ϣ�ܳ��� */
    USHORT usVsncpMsgBodyLen;        /* ԭʼ��VSNCP������Ϣ���� */

    UCHAR ucPdnId;
    UCHAR ucPdnType;
    UCHAR ucAttchType;
    UCHAR ucPcoLen;

    UCHAR ucErrorCode;

    UCHAR aucIpv6Addr[PDN_IPV6ADDR_LEN];

    UCHAR szApn[HSGW_MAX_APN_NAME_LEN + 1];
    UCHAR szPco[HSGW_MAX_PCO_LEN];

    UCHAR aucAMBR[VSNCP_MAX_AMBR_LEN];
    UCHAR ucAMBRLen;

    UCHAR aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];
    UCHAR ucAddressAllocCause;

    UCHAR aucVsncpMsgBody[1];       /* �ն������ԭʼVSNCP��Ϣ */
}PDN_PPP_VSNCP_REQ_S;

typedef struct
{
    RELTMR_T        ulTimeOutID;                /* config request���ĵĶ�ʱ�� */
    ULONG           ulPmipv6UpdTimeOutID;       /* ��ȡPCO�Ķ�ʱ�� */
    ULONG           ulReconnectDnsTimeOutID;    /* �ؽ�PDNʱ�ȴ�DNS�Ķ�ʱ�� */
    SHORT           sRetransmits;               /* config request�����ش����� */
    UCHAR           ucState;                    /* Э��״̬ */
    UCHAR           ucPktId;                    /* ��Э�鵱ǰ���ĵ�ID */
    UCHAR           ucPDNID;
    UCHAR           ucPdnReleaseCode;
    UCHAR           ucUsedFlag : 1;
    UCHAR           ucRenegoFlag : 1;
    UCHAR           ucGetPCOFlag : 1;           /* ���ڻ�ȡPCO�ı�� */
    UCHAR           ucStartingFlag : 1;
    UCHAR           ucStoppingFlag : 1;
    VOS_UINT8       aucReserved[1];
}PDN_VSNCP_INFO_S;

typedef struct
{
    UCHAR  *pucVsncpReq;                        /* �����VSNCP��Ϣ */
    UCHAR  *pucFlowInfo;                        /* �����RESV QosCheck��Ϣ���� */
    UCHAR  *pucPcrfcReq;                        /* �����PCRFC������Ϣ PCRFC_REQ_LIST_INFO*/

    UCHAR  aucLmaAddrV6[PDN_IPV6ADDR_LEN];      /* PGW��IPv6��ַ */
    UCHAR  aucLinkLocalAddr[PDN_IPV6ADDR_LEN];  /* ��PGW��ȡ����LinkLocalAddr */

    ULONG  ulLmaAddrV4;                 /* PGW��IPv4��ַ */
    ULONG  ulRouterAddrV4;

    ULONG  ulChargingId;                /* PGW��ChargingId */
    ULONG  ulGreKey;                    /* PGW���������GRE Key*/

    ULONG  ulApnAmbrUL;                 /* AAA��Ȩ��AMBR */
    ULONG  ulApnAmbrDL;                 /* AAA��Ȩ��AMBR */

    ULONG  ulWtQosCheckTimerId;         /* �ȴ�PCRFC��QosCheckӦ��ʱ�� */

    USHORT usApnIndex;                  /* APN�������� */
    USHORT usChargeCharacter;           /* AAA��Ȩ��3GPP Charge character */
    UCHAR  ucPdnId;                     /* PDN ID, 0~14 */
    UCHAR  ucQci;                       /* AAA��Ȩ��QCI */
    UCHAR  ucArp;                       /* AAA��Ȩ��ARP */
    UCHAR  ucPdnIndicatorCause;
    UCHAR  ucPdnTypeIndicator   : 2,    /* PDN IP���ͱ�ʶ */
           ucDelayFlag          : 1,    /* ��ʱ�����ʶ */
           ucLmaAddrType        : 1,    /* PGW��ַ���ͱ�ʶ */
           ucDefAPNFlag         : 1,    /* �Ƿ���default apn��ʶ */
           ucApnAmbrDLFlag      : 1,    /* AAA�·�ambr dl��� */
           ucApnAmbrULFlag      : 1,    /* AAA�·�ambr ul��� */
           ucNotifyDhcpRelFlag   : 1;    /* ֪ͨDHCPɾ����� */
    UCHAR  ucAttchType;
    UCHAR  ucFQDNType;                  /* FQDN�������� */
    UCHAR  ucbit1L2CReconnectFlg : 1,  /* L��C�����ؽ�PDN���� */
           ucbit7Res             : 7;
    ULONG  ulSendDnsTimeStamp;

    CNAS_CTTF_EHRPD_ATTACH_TYPE_ENUM_UINT8                  enAttachType;
    CNAS_CTTF_EHRPD_PDN_TYPE_ENUM_UINT8                     enPdnType;
    VOS_UINT8                                               ucAddressAllocCause;
    VOS_UINT8                                               aucReserved[1];
    CNAS_CTTF_EHRPD_APN_STRU                                stApn;
    CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU                        stPdnAddress;
    CNAS_CTTF_EHRPD_PCO_STRU                                stPco;
    VOS_UINT8                                               aucIpv4DefaultRouterAddress[CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN];

    CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_UINT16 enErrorCode;
    VOS_UINT8                              aucReserved1[2];
    CNAS_CTTF_EHRPD_APN_AMBR_STRU          stApnAmbr;

    PDN_VSNCP_INFO_S stVSNCP;
}PDN_EHRPD_INFO_S;


typedef struct
{
    USHORT usV4PoolIdx;
    UCHAR  ucV4AllocType;
    UCHAR  ucV4SectionNum;
    UCHAR  szV4PoolName[IP_POOL_NAME_LEN + 1];
    USHORT usV6PoolIdx;
    UCHAR  ucV6AllocType;
    UCHAR  ucV6SectionNum;
    UCHAR  szV6PoolName[IP_POOL_NAME_LEN + 1];
    UCHAR  ucV4LapNo;
    UCHAR  ucV4StaticIpRouteType;
    UCHAR  ucV6LapNo;
    UCHAR  ucV6StaticIpRouteType;
}PDN_SIP_INFO_S;

typedef struct
{
    ULONG ulFaIpAddr;

    /*.................���²�����A10����Ҫ����luofang��ӣ���ȷ��..............*/
    ULONG ulMipKey;

    ULONG ulHaAddr;    /*Home Agent address*/

    /* add by luofang for a10table */
    UCHAR ucGRESwitchFlag:1;      /*GRESwitchFlag*/
    UCHAR ucRevTunnelFlag: 1;     /*support reverse tunnel*/
    UCHAR ucMsSendMethodFlag: 1;  /*MS send method on reverse tunnel*/
    UCHAR ucMiniFlag:1;           /*Mini encapsulation type*/
    UCHAR ucGreFlag:1;            /*Gre encapsulation type*/
    UCHAR ucReserv:3;             /*Gre encapsulation type*/

    UCHAR aucResved11[3];         /* ����λ */

}PDN_MIP_INFO_S;

typedef struct
{
    ULONG  ulSpi;                               /* ��LMA֮����֤��SPI */

    UCHAR  aucLmaAddrV6[PDN_IPV6ADDR_LEN];      /* LMA��IPv6��ַ */
    UCHAR  aucLinkLocalAddr[PDN_IPV6ADDR_LEN];  /* ��PGW��ȡ����LinkLocalAddr */
    UCHAR  aucShareKey[PDN_MIP_SHAREKEY_LEN];   /* ������Կ */
}PDN_MIPV6_INFO_S;

typedef struct
{
    ULONG   ulIfIndex;      /* LAC�ı���PI�ӿ����� */
    ULONG   ulLnsAddr;      /* LNS��ַ */
    ULONG   ulLacAddr;      /* LAC���˵�ַ */
    USHORT  usLocalTid;     /* ����TunnelId */
    USHORT  usLocalSid;     /* ����SessionId */
    USHORT  usPeerTid;      /* �Զ�TunnelId */
    USHORT  usPeerSid;      /* �Զ�SessionId */
}PDN_L2TP_INFO_S;

typedef struct tag_PDN_MSG_BUFF_S
{
    struct tag_PDN_MSG_BUFF_S *pstNext;     /* ��������ָ�� */

    ULONG ulEvent;                          /* ��Ϣ��, PDN_MSGCODE_E */
    ULONG ulMsgLen;                         /* ��Ϣ���� */
    UCHAR aucMsgBody[0];                    /* ��Ϣ�� */

}PDN_MSG_BUFF_S;

typedef struct
{
    UCHAR ucFsmId;
    UCHAR ucState;
    UCHAR ucRev[2];

    ULONG ulStateTimerId;
}PDN_SUBNET_FSM_S;

typedef struct
{
    ULONG ulPdnIndex;           /* PDN���������� */
    ULONG ulRpIndex;            /* ������RP���������� */

    ULONG ulIpV4Addr;                       /* PDN��IPv4��ַ */
    UCHAR aucIpV6Addr[PDN_IPV6ADDR_LEN];    /* PDN��IPv6��ַ */
    USHORT usV4VpnId;
    USHORT usV6VpnId;

    USHORT usDomainIdx;         /* Domain���� */
    UCHAR ucPdnState;           /* PDN״̬��״̬, PDN_STATE_E */
    UCHAR ucPdnType;            /* PDN����, PDN_TYPE_E */

    ULONG ulPdnStateTimerId;    /* PDN״̬��������ʱ�� */
    ULONG ulWtIpcpTimerId;      /* SIP/CMIPδȷ��ʱ������ʱ���ȴ��ն�����Э�̶�ʱ�� */
    ULONG ulPriV4Dns;
    ULONG ulSecV4Dns;

    UCHAR szPriV6Dns[PDN_IPV6ADDR_LEN];
    UCHAR szSecV6Dns[PDN_IPV6ADDR_LEN];

    ///TODO:ע��:��������ӵ��ֶΣ����ڴ�֮����ӣ�ǰ����ֶ�����hash�������������ֽ�hashʧ��!!!

    ULONG ulMipIndex;           /* PMIPv6/FA���������� */
    ULONG ulIpv6Timer;          /* IPV6 ��ʱ��id*/
    ULONG ulTeidc;               /* PDN?TEIDC */
    ULONG ulGREkey;              /* ulGREkey */

    UCHAR ucIpcpRetryNum;       /* ��������IPCP���� */
    UCHAR ucIpv6RouteMsgNum;    /* ipv6ģ��ʹ�ã����ھ���RA��Ϣ�ķ��ͼ�������� */
    UCHAR ucPdnCapability   : 2,    /* PDN��ǰ���� */
          ucInitCapbility   : 2,    /* PDSN��ʼ���� */
          ucIPv4NotifyLap   : 1,
          ucIPv6NotifyLap   : 1,
          ucLapRecycleIPv4  : 1,
          ucLapRecycleIPv6  : 1;
    UCHAR bIpV4Used         : 1,    /* IPv4ջʹ��״̬ */
          bIpV6Used         : 1,    /* IPv6ջʹ��״̬ */
          bIpV4StaticIp     : 1,    /* IPv4��ַ�Ƿ�Ϊ��̬��ַ */
          bIpV6StaticIp     : 1,    /* IPv6��ַ�Ƿ�Ϊ��̬��ַ */
          bNotifyPcrf       : 1,    /* �Ƿ��Ѿ�֪ͨPCRFC */
          bNotifyCm         : 1,    /* �Ƿ��Ѿ�֪ͨCM */
          bUsmRelFlag       : 1,    /* �Ƿ�ΪUSM��������� */
          bNotifyNcp        : 1;    /* �Ƿ��Ѿ�֪ͨ��VSNCP */

    UCHAR bIpV4GipiFlag     : 1,    /* IPv4 gipi���·���� VOS_TRUE:�·���VOS_FALSE:δ�·� �˱�־����Ҫ����*/
          bIpV6GipiFlag     : 1,    /* IPv4 gipi���·���� VOS_TRUE:�·���VOS_FALSE:δ�·� �˱�־����Ҫ����*/
          bIpv6NumFlg       : 1,    /* �Ƿ�ͳ�ƹ�ipv6��ջ�û�����־ �˱�־����Ҫ����*/
          bIpv4v6NumFlg     : 1,    /* �Ƿ�ͳ�ƹ�ipv6˫ջ�û�����־ �˱�־����Ҫ����*/
          bNotifySm         : 1,    /* �Ƿ��Ѿ�֪ͨSM */
          bNotifyMip        : 1,    /* �Ƿ��Ѿ�֪ͨFA/MIPv6 */
          bRuleUpdFlag      : 1,    /* PCRF������±�� �ñ��Я����SM*/
          bL2tpChkFlg       : 1;

    UCHAR bSeqLinkNo : 3,      /*���ڼ�¼����teidc�󶨵�sequece������*/
          bIpv4ActiveState:1,  /* v4ջ����ɹ���� pdsn��̬��Ч������Ҫ���ݵ���Ҫ�ڱ�����лָ� */
          bIpv6ActiveState:1,  /* v6ջ����ɹ���� pdsn��̬��Ч������Ҫ���ݵ���Ҫ�ڱ�����лָ� */
          bEhrpdPdnFlag : 1,   /* ehrpd pdn���·���� VOS_TRUE:�·���VOS_FALSE:δ�·� */
          b2Bcm : 2;        /*MS Support of Network Requested Bearer Control indicator */

    UCHAR bit1OflChrgEnabled : 1,  /* ���ֶ�cmά�� */
          bit1OnlChrgEnabled : 1,
          bit1FbcChrgEnabled : 1,
          bit1PostpaidEnabled : 1,
          bit1SgwOflChrgEnabled : 1,
          bit1ActByTauOrHo : 1,        /* �Ƿ����л������ģ�����hsgw�û���Ч */
          bit1PcrfReferUserprofileId :1,
          bit1PcrfQciFlag : 1;   /*ehrpd PCC �û� , ���pcrfC��Ϣ֪ͨ��qci ��1*/

    UCHAR ucTFTNumbers;

    PDN_MSG_BUFF_S *pstMsgBuffHead; /* ��Ϣ�������ͷ */
    UCHAR       *pstUpdateMsg;      /* ������Ϣ��PCC�û��ȴ�PCRFC״̬ʱ��Ҫ�ȱ��浽������ */
    ULONG       ulTFTIndexArray[8];
    UCHAR       ucTFTtype[8];

    PDN_SUBNET_FSM_S astSubNetFsm[MAX_STACK_PER_PDN];   /* ������״̬����֧��˫ջ */

    union
    {
        ///TODO:ע��:���¼���Ϊ�����壬�������ucPdnType���ܷ����ض��ṹ
        PDN_SIP_INFO_S      stSip;
        PDN_MIP_INFO_S      stMip;
        PDN_MIPV6_INFO_S    stPmipv6;
        PDN_L2TP_INFO_S     stL2tp;
        PDN_EHRPD_INFO_S    stEhrpd;
    };

    /*PCCʹ��*/
    ULONG   ulFilterPrecedenceBitMap;
    UCHAR   ucExtenPrecedence;
    UCHAR   ucBitUECreateV4FilterFlag : 1;                /* UE ���������v4filter */
    UCHAR   ucBitUECreateV6FilterFlag : 1;                /* UE ���������v6filter */
    UCHAR   ucBitReserved6: 6;
    UCHAR   ucReserve2[2];

    /* �Ʒ�������� */
    ULONG   ulBearerIndex;
    ULONG   ulSessionIndex;

    ULONG   ulAcctInterimInterval;
    ULONG   ulIdleTimeout;

    USHORT  usUserProfileID;           /* ���û�ƥ���User Profile ID*/
    USHORT  usPcrfGrpIndex;

    UCHAR   ucPcrfLocalIndex;
    UCHAR   ucFilterID;
    UCHAR   ucChargePropertyFlag    : 4;    /*�û��ļƷ����� 1:FBC, 2: PDP*/
    UCHAR   ucChargeMode            : 4;    /*�Ʒ����ԣ�0:���߼Ʒ� , 1:���߼Ʒ�*/
    UCHAR   ucPreparedFlag          : 2;    /* �Ƿ���Ԥ�����û� */
    UCHAR   ucPccMode               : 2;
    UCHAR   ucAnyToAnyFlag          : 1;    /*PCRF�Ƿ��·���Any to Any�Ĺ���*/
    UCHAR   ucActiveStopIndication  : 1;    /*Accounting-Stop-triggered-by-Active-Stop-Indication */
    UCHAR   ucSmNotifyQosUpdFlag    : 1;
    UCHAR   ucPdnUserNumFlg         : 1;    /*�Ƿ�ͳ�ƹ��û�����־ �˱�־����Ҫ����*/

    ULONG ulpdpActTimeStampHig;
    ULONG ulpdpActTimeStampLow;
    ULONG ulpdpDelTimeStampHig;
    ULONG ulpdpDelTimeStampLow;

    /*========SMʹ��=======*/
    USHORT   usUserGroupID;                 /*�û���ID��ͬʱҲ���û��鼶BWM_CB�����������*/
    USHORT   usUserProfileGroupID;          /* ���û�ƥ���User Profile Group ID*/
    ULONG    ulUsageRptCBIndex;             /*Added by liupeng for SM pdsn10.1 ͬ��*/

    UCHAR    ucGroupLevelServiceType;       /* ��¼�û��鼶��ҵ�����ͣ� tos /non-tos*/
    UCHAR    szUserProfileName[PDN_USER_PROFILE_NAME_LENGTH + 1];    /*User Profile���Ƶ��ַ��� ��charge-rule-base-name*/

    UCHAR    ucBwmSubscriberEnable  : 2;    /* �û��鼶BWM����ʹ�ܱ�־*/
    UCHAR    ucBwmGroupEnable       : 2;    /* �û���BWM����ʹ�ܱ�־ */
    UCHAR    ucBwmGlobalEnable      : 2;    /* ȫ�ּ�BWM����ʹ�ܱ�־ */
    UCHAR    ucAliasMarking         : 1;    /* Alias Markingʹ�ܱ�ʶ,0:δʹ��,1:ʹ�� */
    UCHAR    ucDDosFlag             : 1;    /* ��DDOS����ʹ��,0:δʹ��,1:ʹ�� */

    UCHAR    ucAAAUserProfileFlag   : 1;    /* 0��ʾuserprofile�Ǳ��ط��䣻1��ʾAAAָ��*/
    UCHAR    ucAAAUserGroupFlag     : 1;    /*0��ʾusergroup�Ǳ��ط��䣻1��ʾAAAָ��*/
    UCHAR    ucActionSupport        : 1;
    UCHAR    ucUserClassAAAFlag     : 1;
    UCHAR    ucPCCNumFlag           : 1;    /*�Ƿ�ͳ�ƹ�pcc�û� �˱�־����Ҫ����*/
    UCHAR    ucBitRedirectRptTriggerFlag : 1;  /*ֻ��PDSN֧��*/
    UCHAR    ucbit1BwmUserFlg      : 1;  /* �Ƿ���BWM�û�,��Ҫ����,����ƽ��ʱ����ͳ�ƻָ� */
    UCHAR    ucbit1BwmUserPerfFlg   : 1;  /* �Ƿ��BWM����ͳ��,����Ҫ����,��ֹƽ����û�лָ�ʱ�û�ȥ��IPN���ӿڼ� */
    ULONG    ulSlaveActiveTimeStemp; /* ���崴��PDN��ʱ���,ƽ��ʱ�����·�ת������ʹ�� */

    USHORT   usReleaseCode;        /* ȥ��ԭ��AM_RELEASE_CODE_E */
    UCHAR    ucBit2SelectType    : 2;   /*PCCʹ���ֶ�: 0 ����pcrfgrpѡ��service��1:����ȫ��realmIdexѡ��������2:����apn�µ�realmѡ������; 3:��ʼ��ֵ(��AM��֤)*/
    UCHAR    ucBitV4CanForwardData :1;  /* v4�����ܷ�����ת�����vos_true����������Э�̳����������ؽ� */
    UCHAR    ucBitV6CanForwardData :1;  /* v6�����ܷ�����ת�����vos_true����������Э�̳����������ؽ� */
    UCHAR    ucBitDelPDNBackupFlag :1;  /* PDN�Ƿ񵥶�֪ͨ����ɾ����� */
    UCHAR    ucBit345678Resv     : 3;
    UCHAR    ucReserve;
}PDN_CONTEXT_S;           /* 384 bytes */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pppc_pdn.h */
