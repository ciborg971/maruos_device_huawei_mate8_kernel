/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_cmm_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-13
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-13   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_CMM_API_H_
#define _OSPF6_CMM_API_H_
        
#ifdef __cplusplus
            extern "C"{
#endif /* __cplusplus */

/*STRUCT<OSPF6 LSDB���������ṹ��>*/
typedef struct tagOSPF6_LSDB_FILTER
{
    USHORT usProcessId;                    /*����ID
                                             ��Χ��0~0xffff��
                                             0�����ڵ����н��̣�
                                             1��0xffff��ָ����OSPF���̺š�*/
    USHORT usLsaType;                      /*LSA���ͣ�
                                                OSPF6_ROUTER_LSA
                                                OSPF6_NETWORK_LSA
                                                OSPF6_INTER_AREA_PRFX_LSA
                                                OSPF6_INTER_AREA_RTR_LSA
                                                OSPF6_AS_EXTERNAL_LSA
                                                OSPF6_NSSA_EXT_LSA
                                                OSPF6_LINK_LSA
                                                OSPF6_INTRA_AREA_PRFX_LSA */
} OSPF6_LSDB_FILTER_S;

/*STRUCT<ͨ��OSPF6�ۺϲ�ѯ���������ṹ��>*/
typedef struct tagOSPF6_AREA_AGG_FILTER
{
    USHORT usProcessId;                     /*����ID
                                              ��Χ��0~0xffff��
                                              0�����ڵ����н��̣�(ulAreaId�ֶ���Ч)
                                              1��0xffff��ָ����OSPF���̺š�*/
    UCHAR  ucPadding[2];                    /*���*/
    ULONG  ulAreaId;                        /*����ID��0-0xffffffff*/
} OSPF6_AREA_AGG_FILTER_S;

/*STRUCT<ͨ��OSPF6���������ṹ��>*/
typedef struct tagOSPF6_FILTER
{
    USHORT usProcessId;                      /*����ID
                                              ��Χ��0-0xffff��
                                              0�����ڵ����н��̣�
                                              1-0xffff��ָ����OSPF���̺š�*/
    UCHAR  ucPadding[2];                     /*���*/
} OSPF6_FILTER_S;

/*STRUCT<OSPF6 ��̬�ھ���Ч���������ṹ��>*/
typedef struct tagOSPF6_PEER_FILTER
{
    USHORT usProcessId;                      /*����ID
                                              ��Χ��0-0xffff��
                                              0�����ڵ����н��̣�
                                              1-0xffff��ָ����OSPF���̺š�*/
    UCHAR  ucPadding[2];                     /*���*/
    ULONG  ulInstanceId;                     /*ʵ�� ID 
                                                ��Χ: 0-255
                                                OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ*/ 
    ULONG  ulIfIndex;                        /*�ӿ�������Ϊ0��ʾ��ָ���ӿڲ�ѯ*/
} OSPF6_PEER_FILTER_S;

/*STRUCT<OSPF6 ��̬�ھ����ù��������ṹ��>*/
typedef struct tagOSPF6_CFGPEER_FILTER
{
    ULONG  ulInstanceId;                     /*ʵ�� ID 
                                                ��Χ: 0~255
                                                OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ*/ 
    ULONG  ulIfIndex;                        /*�ӿ�������Ϊ0��ʾ��ָ���ӿڲ�ѯ*/
} OSPF6_CFGPEER_FILTER_S;

/*STRUCT<OSPF6�ӿڰ���Ϣ��ѯ�Ĺ��������ṹ��>*/
typedef struct tagOSPF6_INTF_BIND_FILTER
{
    USHORT usProcessId;                      /*����ID
                                              ��Χ��0-0xffff��
                                              0�����ڵ����н��̣�
                                              1-0xffff��ָ����OSPF���̺š�*/
    UCHAR  ucPadding[2];                     /*���*/
    ULONG  ulIfIndex;                        /*�ӿ�������Ϊ0��ʾ��ָ���ӿڲ�ѯ*/
} OSPF6_INTF_BIND_FILTER_S;

/*STRUCT<OSPF6 �ӿ����Թ��������ṹ��>*/
typedef struct tagOSPF6_INTF_ATTR_FILTER
{
    ULONG  ulInstanceId;                     /*Instance ID 
                                                ��Χ: 0~255
                                                OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ*/ 
    ULONG  ulIfIndex;                        /*�ӿ�������Ϊ0��ʾ��ָ���ӿڲ�ѯ*/
} OSPF6_INTF_ATTR_FILTER_S;

/*STRUCT<OSPF6ʵ����Ϣ��ѯ�ṹ�壬�����ݽṹ����ospf6 entity mib(amb_osp3_pm_ent)�й��û���ȡ���ֶ�>*/
typedef struct tagOSPF6_ENTITY_SHOW
{
    ULONG  ulProcessId;                     /*����ID*/
    ULONG  ulRouterId;                      /*Router ID*/
    ULONG  ulAdminStatus;                   /*����״̬: 1-up��0-down*/
    ULONG  ulOperStatus;                    /*����״̬*/
    ULONG  ulOspfVersion;                   /*Ospf6�汾*/
    ULONG  ulAbrFlg;                        /*Abr��־*/
    ULONG  ulAsbrFlg;                       /*Asbr��־*/
    ULONG  ulAsChkSumSum;                   /*����������LSA CheckSum�ĺͣ�����ȷ��LSA�Ƿ��б仯*/
    ULONG  ulAsExtLsa;                      /*����������LSA��Ŀ*/
    ULONG  ulMaxPaths;                      /*�ȼ�·����Ŀ*/
    ULONG  ulCalcPauseFreq;                 /*�������ؼ���ͣ��ʱ��*/
    ULONG  ulCalcMaxDelay;                  /*�������ؼ�����ʱʱ��*/
    ULONG  ulVrfIndex;                      /*VRF��*/
    ULONG  ulCfgRouterId;                   /*Cfg Route ID*/
    ULONG  ulDoGR;                          /*�Ƿ�ʹ�ܼƻ�GR*/
    ULONG  ulDoGRUnplanned;                 /*�Ƿ�ʹ�ܷǼƻ�GR*/
    ULONG  ulGRPeriod;                      /*GR����*/
    ULONG  ulRestartReson;                  /*GR����ԭ��*/
    ULONG  ulTrafficEngSupport;             /*This flag is used to determine if this router canoriginate its own traffic engineering LSAs.*/       
}OSPF6_ENTITY_SHOW_S;


/*STRUCT<OSPF6�ӿڰ���Ϣ��ѯ�ṹ�壬�����ݽṹ����ospf6 if mib(amb_osp3_pm_if)���û������ĵ��ֶ�>*/
typedef struct tagOSPF6_SHOWINTF
{
    ULONG  ulProcessId;                         /*����ID*/
    ULONG  ulInstanceId;                        /*Instance ID */ 
    ULONG  ulAreaId;                            /*����ID*/
    UCHAR ucIpAddr[OSPF6_MAX_INET_ADDR_LEN];     /*IP6��ַ*/
    ULONG  ulIfNetworkType;                     /*�ӿ���������
                                                  1 - �㲥
                                                  2 - NBMA
                                                  3 - �㵽��
                                                  5 - �㵽���
                                                  10 - ����*/
    ULONG  ulIfIndex;                           /*�ӿ����� */ 
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*�ӿ���*/
    ULONG  ulIfState;                           /*�ӿ�״̬*/  
    ULONG  ulAdminStatus;                       /*admin ״̬*/
    ULONG  ulOperStatus;                        /*����״̬*/
    ULONG  ulIfMetric;                          /*�ӿ�COST*/
    ULONG  ulIfPriority;                        /*���ȼ�*/
    ULONG  ulDr;                                /*DR*/ 
    ULONG  ulBdr;                               /*BDR*/ 
    ULONG  ulFastHelloMultiplier;               /*FastHelloƵ��*/
    ULONG  ulFastHelloInterval;                 /*FastHello��� 0��Ч ������Ч*/
    ULONG  ulRxmtInterval;                      /*LSA�ش�ʱ��*/ 
    ULONG  ulTransDelay;                        /*�ӿڴ�����ʱ*/ 
    ULONG  ulHelloInterval;                     /*Hello��� FastHello��Чʱ��Ч*/  
    ULONG  ulDeadInterval;                      /*Dead���*/ 
    ULONG  ulPollInterval;                      /*��ѯ���*/ 
    ULONG  ulIfMtuSize;                         /*�ӿ��ϵ�MTU*/
    ULONG  ulMtuSizePcntge;                     /*�ӿ�MTU*/ 
    ULONG  ulMtuIgnoreFlg;                      /*�ӿ�MTU���Ա��*/ 
    ULONG  ulLSUTransmitDelay;                  /*LSU packet delay for reduce the network traffic Unit:ms Default:100 */
    ULONG  ulLsaCount;                          /*LSA��*/   
    ULONG  ulPassive;                           /*������־,Ĭ��:0
                                                  1 - �ӿڲ��ٽ��շ���Hello����*/

    /* Added by likaikun00213099, ���ڽӿ�ͳ�Ƹ�״̬���ھ�, 2014/4/15 */
    USHORT usNumNeighbors;                      /*���ӿ��ھӸ���*/
    USHORT usNeighborsInState[OSPF6_NBR_MAX_STATES + 1]; /*��ͬ״̬�ھӸ���*/
    ULONG  ulRouterId;                          /*���ӿ������ڵ�Router ID*/
    ULONG ulInterfaceId;            /* ���ӿڵĽӿ�ID */
    ULONG ulAddrlessif;
    ULONG ulMaxHitlessGracePeriod;
    ULONG ulAutoDelNbrFlag;                         /*Default: 1*/
    ULONG ulGrHelperMode;
    ULONG ulAccNum;
    ULONG ulRemoteIfIndex;
    /* End of Added by likaikun00213099, ���ڽӿ�ͳ�Ƹ�״̬���ھ�, 2014/4/15 */
}OSPF6_SHOWINTF_S;

/*STRUCT<�����ѯ��Ϣ�ṹ�壬�����ݽṹ����ospf6 area mib(amb_osp3_pm_area)���û������ĵ��ֶ�>*/
typedef struct tagOSPF6_SHOW_AREA
{
    ULONG  ulProcessId;                     /*����ID*/
    ULONG  ulAreaId;                        /*����ID*/
    ULONG  ulAdminStatus;                   /*admin״̬*/
    ULONG  ulOperStatus;                    /*����״̬*/
    ULONG  ulImportAsExtern;                /*��������
                                              1 - IMPORT_EXTERNAL
                                              2 - IMPORT_NO_EXTERNAL
                                              3 - IMPORT_NSSA*/
    ULONG  ulSummary;                       /*����Summary LSAs��stub��NSSA����ı�־
                                              1 - SEND_AREA_SUMMARY
                                              0 - NO_AREA_SUMMARY*/
    ULONG  ulNssaTranslatorRole;            /*NSSA�����еı߽�·���а�7�౨��ת��Ϊ5�౨�ĵ�����
                                              1 - ALWAYS
                                              2 - CANDIDATE��ѡ*/
    ULONG  ulNssaTranslatorState;           /*NSSA�����еı߽�·���Ƿ��7�౨��ת��Ϊ5�౨��
                                              1 - STATE_ENABLED������������޸�ΪALWAYS
                                              2 - STATE_ELECTED����ѡNSSA�߽�·�ɽ����б���ת��
                                              3 - STATE_DISABLED����ѡNSSA�߽�·�ɲ����б���ת��*/
    ULONG  ulTransitCapability;             /*This parameter indicates whether the area can carry data
                                              traffic that neither originates nor terminates in the area itself.
                                              1 - TRUE
                                              2 - FASLE*/
    ULONG  ulLsaRfshIntvl;                  /*LSA���ڷ�����ʱ��*/
    ULONG  ulStubMetric;                    /*Stub�����Ĭ��Metricֵ*/
}OSPF6_SHOW_AREA_S;

/*STRUCT<NBR��ʾ�ṹ�壬�����ݽṹ����ospf6 nbr mib(amb_osp3_pm_nbr)���û������ĵ��ֶ�>*/
typedef struct tagOSPF6_SHOWNBR_S
{     
    ULONG  ulProcessId;                     /*����ID*/
    ULONG  ulInstanceId;                    /*Instance ID */ 
    ULONG  ulAreaId;                        /*����ID*/
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/ 
    ULONG  ulNbrId;                         /*�ھ�Router ID*/   
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*�ھӵ�ַ*/
    ULONG  ulNbrState;                      /*�ھ�״̬*/
    ULONG  ulNbrPriority;                   /*�ھ����ȼ�*/
    ULONG  ulDeadTime;                      /*�ھ�ʧЧ���*/
    ULONG  ulBFDSessionID;                  /*�ھ�BFD�ỰID*/
    ULONG  ulHelloSuppressed;               /*Hello����*/
    ULONG  ulPermanence;                    /*�ھӶ�̬or��̬*/

    /* Added by likaikun00213099, �ھӲ�ѯ����ά����Ϣ, 2014/4/18 */
    UCHAR  ucNbrIfIpAddr[OSPF6_MAX_INET_ADDR_LEN]; /*�ھӽӿڵ�ַ*/
    ULONG  ulNeighbourDR;                   /*�ھ�DR*/
    ULONG  ulNeighbourBDR;                  /*�ھ�BDR*/
    ULONG  ulNeighbourGRState;              /*�ھ�GR״̬*/
    ULONG  ulNbrLastUpdTime;                /*�ھӴﵽFULL���뿪FULL֮����ۼ�ʱ�䣬��λ:��*/
    ULONG  ulNbrUpDownTimes;                /*�ھ�UP/DOWN����*/
    ULONG  ulOptions;                       /*�ھ�ѡ��*/
    /* End of Added by likaikun00213099, �ھӲ�ѯ����ά����Ϣ, 2014/4/18 */
}OSPF6_SHOWNBR_S;

typedef struct tagOSPF6_PMMJSHOW_S
{
  ULONG ApplIndex;
  ULONG InterfaceId;              
  ULONG PartnerIndex;
  ULONG RowStatus;                
  ULONG AdminStatus;      
  ULONG OperStatus;                      
  ULONG JoinStatus;           
} OSPF6_PMMJSHOW_S;

typedef struct tagOSPF6_PMSJSHOW_S
{
  ULONG ApplIndex;
  ULONG MasterIndex;
  ULONG JoinIndex;
  ULONG JoinStatus;
  ULONG InterfaceId;
} OSPF6_PMSJSHOW_S;


/*STRUCT<·����LSA������Ϣ>*/
typedef struct tagOSPF6_LINK_DESC
{
    UCHAR   ucType;                            /* Type(1~4) */
    UCHAR   ucPadding;                         /*���*/
    USHORT  usMetric;                          /* Metric */
    ULONG   ulLinkIfId;                        /* Link Interface ID */
    ULONG   ulNbrLinkIfId;                     /* Neighbor Link Interface ID */
    ULONG   ulNbrRouterId;                     /* Neighbor Router ID */
}OSPF6_LINK_DESC_S;

/*STRUCT<·����LSA�ṹ��>*/
typedef struct tagOSPF6_ROUTER_LSA
{
    ULONG  ulOptions;                          /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    UCHAR  ucBitFlags;                         /* Bit:NT(0x10) W(0x08) V(0x04) E(0x02) B(0x01)*/
    UCHAR  ucPadding;                          /*���*/
    USHORT usLinkCount;                        /*link��*/
    OSPF6_LINK_DESC_S   stRtrDescription[OSPF6_LSA_MAX_RTR_LINK_D]; /*Route LSA������Ϣ*/
}OSPF6_ROUTER_LSA_S;

/*STRUCT<����LSA�ṹ��>*/
typedef struct tagOSPF6_NETWORK_LSA
{
    ULONG  ulOptions;                             /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulNetNum;                              /* ������� */
    ULONG  ulAttachedRtrId[OSPF6_LSA_MAX_NET_NBR];/*attached rt ID*/
}OSPF6_NETWORK_LSA_S;

/*STRUCT<�����ǰ׺LSA�ṹ��>*/
typedef struct tagOSPF6_PREFIX_DESC
{
    UCHAR  ucPrfxLen;                           /* Prefix Length */
    UCHAR  ucPrfxOpt;                           /* Prefix Option:NU(0x01) LA(0x02) MC(0x04)P(0x08) */
    USHORT usPrfxMetric;                        /* Prefix Metric */
    UCHAR  ucPrfxAddr[OSPF6_MAX_INET_ADDR_LEN];  /* Prefix address */
}OSPF6_PREFIX_DESC_S;

/*STRUCT<������·����LSA�ṹ��>*/
typedef struct tagOSPF6_INTRA_PREFIX_LSA
{
    ULONG  ulMetric;                            /* Metric */
    OSPF6_PREFIX_DESC_S stPrfxDescription;      /*ǰ׺������Ϣ*/
}OSPF6_INTRA_PREFIX_LSA_S;

/*STRUCT<�����·����LSA�ṹ��>*/
typedef struct tagOSPF6_INTER_AREA_RTR_LSA
{
    ULONG  ulOptions;                           /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulMetric;                            /* Metric */
    ULONG  ulDestRouterId;                      /* Destination Router ID */
}OSPF6_INTER_AREA_RTR_LSA_S;

/*STRUCT<AS�ⲿLSA�ṹ��>*/
typedef struct tagOSPF6_AS_EXTERNAL_LSA
{
    UCHAR  ucBitFlags;                          /* Bit:E(0x04) F(0x02) T(0x01)*/
    UCHAR  ucPadding[3];                        /*���*/
    ULONG  ulMetric;                            /* Metric */
    UCHAR  ucPrfxLen;                           /* Prefix Length */
    UCHAR  ucPrfxOpt;                           /* Prefix Option:NU(0x01) LA(0x02) MC(0x04)P(0x08) */
    USHORT usRefLsType;                         /* Referenced LS type */
    UCHAR ucPrfxAddr[OSPF6_MAX_INET_ADDR_LEN]; /* Prefix address */
    UCHAR ucFwdAddr[OSPF6_MAX_INET_ADDR_LEN];   /* Forwarding address */
    ULONG  ulExtRouteTag;                       /* External Route Tag */
    ULONG  ulRefLinkStateID;                    /* Referenced Link State ID : ��ʱ���ֶ�Ϊ0
                                                   ȡ����usRefLsType*/
}OSPF6_AS_EXTERNAL_LSA_S;

/*STRUCT<NSSA LSA�ṹ��>*/
typedef OSPF6_AS_EXTERNAL_LSA_S OSPF6_NSSA_LSA_S;

/*STRUCT<��·LSA�ṹ��>*/
typedef struct tagOSPF6_LINK_LSA
{
    UCHAR  ucRtrPri;                            /* Router Priority */
    UCHAR  ucPadding[3];                        /*���*/
    ULONG  ulOptions;                           /* Option:DC(0x20) R(0x10) NP(0x08) MC(0x04) E(0x02) V6(0x01)*/
    ULONG  ulPrfxNum;                           /* prefixes number */
    UCHAR ucLinkLocalAddr[OSPF6_MAX_INET_ADDR_LEN]; /* link-local address */
    OSPF6_PREFIX_DESC_S stPrfxDescription[OSPF6_LSA_MAX_PRFX_D];/*ǰ׺������Ϣ*/
}OSPF6_LINK_LSA_S;

/*STRUCT<������ǰ׺LSA�ṹ��>*/
typedef struct tagOSPF6_INTRA_AREA_PRFX_LSA
{
    USHORT usPrfxNum;                           /* Prefix Number */
    USHORT usRefLsType;                         /* Referenced LS type */
    ULONG  ulRefLsId;                           /* Referenced LS ID */
    ULONG  ulRefAdvRouterId;                    /* Referenced advertising router ID */
    OSPF6_PREFIX_DESC_S stPrfxDescription[OSPF6_LSA_MAX_PRFX_D];/*ǰ׺������Ϣ*/
}OSPF6_INTRA_AREA_PRFX_LSA_S;

/*STRUCT<LSA��ͷ����Ϣ�ṹ��>*/
typedef struct tagOSPF6_LSAHdr
{
    USHORT usLsAge;                             /* �ϻ�ʱ�� */
    USHORT usLsType;                            /* LSA ���� */
    UCHAR  ucLsTypeBits;                        /* ��·״̬:U(0x80,LSA Handling) S2(0x40) S1(0x20,Flooding Scope) */
    UCHAR  ucPadding[3];                        /*���*/
    ULONG  ulLinkId;                            /* ��·ID */
    ULONG  ulAdvRtr;                            /* ͨ��·����ID */
    LONG   lLsSeqNum;                           /* ���к� */
    USHORT usLsChksum;                          /* У��� */
    USHORT usLength;                            /* ����LSAͷ�����ڵ�LSA���� */
}OSPF6_LSAHDR_S;

/*STRUCT<���е�LSA���нṹ��>*/
typedef struct tagOSPF6_SHOW_LSADATA
{
    OSPF6_LSAHDR_S stLsaHdr;                            /* LSA header */
    union
    {
        OSPF6_ROUTER_LSA_S          stRtr6Lsa;           /* Router LSA */
        OSPF6_NETWORK_LSA_S         stNet6Lsa;           /* Network LSA */
        OSPF6_INTRA_PREFIX_LSA_S    stIntraPrfx6Lsa;     /* Intra-prefix LSA */
        OSPF6_INTER_AREA_RTR_LSA_S  stInterAreaRtr6Lsa;  /* Inter-Area_Router LSA */ 
        OSPF6_AS_EXTERNAL_LSA_S     stAsExternal6Lsa;    /* AS-external LSA */ 
        OSPF6_NSSA_LSA_S            stNssa6Lsa;          /* NSSA LSA */ 
        OSPF6_LINK_LSA_S            stLink6Lsa;          /* Link LSA*/ 
        OSPF6_INTRA_AREA_PRFX_LSA_S stInterAreaPrfx6Lsa; /* Inter_Area_prefix LSA */ 
    }OSPF6_LSA_U;
}OSPF6_SHOW_LSADATA_S;

/*STRUCT<LSA DB��ѯ�ṹ��>*/
typedef struct tagOSPF6_SHOWLSDB 
{ 
    ULONG  ulRouterId;                          /*Router ID*/
    ULONG  ulAreaId;                            /*����ID*/
    USHORT usProcessId;                         /*����ID*/
    USHORT usRes;                               /*���*/
    OSPF6_SHOW_LSADATA_S stLSAData;             /*�����ѯ��Ϣ*/
} OSPF6_SHOWLSDB_S;

#define  stRtrLsa   stLSAData.OSPF6_LSA_U.stRtr6Lsa
#define  stNetLsa   stLSAData.OSPF6_LSA_U.stNet6Lsa
#define  stIntraPrfxLsa   stLSAData.OSPF6_LSA_U.stIntraPrfx6Lsa
#define  stInterAreaRtrLsa   stLSAData.OSPF6_LSA_U.stInterAreaRtr6Lsa
#define  stAsExternalLsa   stLSAData.OSPF6_LSA_U.stAsExternal6Lsa
#define  stNssaLsa   stLSAData.OSPF6_LSA_U.stNssa6Lsa
#define  stLinkLsa   stLSAData.OSPF6_LSA_U.stLink6Lsa
#define  stInterAreaPrfxLsa   stLSAData.OSPF6_LSA_U.stInterAreaPrfx6Lsa


/*STRUCT<·����һ����Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_ROUTING_NEXTHOP
{
    ULONG ulOutIfIndex;                         /*���ӿ�����*/
    UCHAR ucAddress[OSPF6_MAX_INET_ADDR_LEN];   /*��һ����ַ*/
}OSPF6_ROUTING_NEXTHOP_S;

/*STRUCT<·����Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWROUTE
{
    ULONG  ulProcessId;                     /*����ID*/
    ULONG  ulAreaId;                        /*����ID*/
    INET6_ADDRESS_S stDestIpAddr;           /*Ŀ����·��ַ*/
    ULONG  ulAdvRouterId;                   /*ͨ��·����ID*/
    ULONG  ulPathCost;                      /*·������*/   
    ULONG  ulType2Cost;                     /*Only valid for type 2 external paths*/
    UCHAR  ucPathType;                      /*·������
                                              0x01 Indicates a path to a destination belonging to one of the router's 
                                                   attached OSPF areas.  
                                              0x02 Indicates a path to a destination in another OSPF area. 
                                              0x03 Indicates a path to a destination external to OSPF with a metric
                                                   expressed in the same units as the OSPF internal metric.  
                                              0x04 Indicates a path to a destination external to OSPF with a metric an order
                                                   of magnitude larger than the OSPF internal metric.  A cost in the type-2
                                                   metric is considered greater than any cost in the type-1 metric. */
    UCHAR  ucOriginType;                    /*DCL ��δ����,ĿǰֻΪ0*/
    UCHAR  ucDestType;                      /*·��Ŀ�ĵ�ַ���� 
                                              0x01 Area boundary or AS boundary router.    
                                              0x02 Transit or stub network.    
                                              0x03 Address range which if active will be a reject route. 
                                              0x04 Address range corresponding to an NSSA type-7 area aggregation.
                                              0x05 Route entry used solely for the root of the patricia tree.   */    
    UCHAR  ucEntryType;                     /*·��״̬0-active 1-Inactive*/
    UCHAR  ucRouterEntryFlags;              /*·�ɱ��1*/
    UCHAR  ucRouterEntryFlags2;             /*·�ɱ��2*/
    UCHAR  ucPadding[2];                    /*���*/
    ULONG  ulExternalRouteTag;              /*�ⲿ·�ɱ��*/
    USHORT usNumOfEqualCostPaths;           /*ƽ��·�ɸ���*/
    USHORT usPadding;                       /*���*/                                     
    OSPF6_ROUTING_NEXTHOP_S stOspf6Rt[OSPF6_MAX_EQCOST_PATH];/*path Infomation*/
}OSPF6_SHOWROUTE_S;

/*STRUCT<����ۺϲ�ѯ��Ϣ�ṹ�壬�����ݽṹ����ospf6 area agg(amb_osp3_pm_area_aggregate)���û����ĵ��ֶ�>*/
typedef struct tagOSPF6_SHOWAREA_AGG
{
    ULONG  ulProcessId;                     /*����ID*/
    ULONG  ulAreaId;                        /*����ID*/
    ULONG  ulAdvert;                        /*1����ͨ�棬 0����ͨ��*/
    INET6_ADDRESS_S stPrefixAddr;           /*Prefix address*/
}OSPF6_SHOWAREA_AGG_S;


/*STRUCT<OSPF6���������Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWREDIST
{
    ULONG  ulProcessId;                     /*����ID*/
    OSPF6_RPM_PLCYREDIS_S stReDis;          /*ָ�����̶�Ӧ�����������Ϣ*/
}OSPF6_SHOWREDIST_S;

/*STRUCT<OSPF6���������Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOW_EXPORT_FILTER_S
{
    ULONG  ulProcessId;                     /*����ID*/
    OSPF6_RPM_PLCYDIST_S stPlcyDist;        /*ָ�����̶�Ӧ�����������Ϣ*/
}OSPF6_SHOW_EXPORT_FILTER_S;

/*STRUCT<OSPF6���չ�����Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOW_IMPORT_FILTER_S
{
    ULONG  ulProcessId;                     /*����ID*/
    union
    {
        ULONG ulAclNum;                    /*ACL6�������
                                              ��Χ:2000~2999*/
    } stFltrName;   
}OSPF6_SHOW_IMPORT_FILTER_S;

/*STRUCT<OSPF6��̬�ھ���Ч��Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWPEER
{
    ULONG  ulProcessId;                          /*����ID*/
    ULONG  ulInstanceId;                         /*Instance ID*/ 
    ULONG  ulIfIndex;                            /*�ӿ�����*/ 
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];   /*�ֹ����öԶ˵ĵ�ַ*/
    ULONG  ulNbrPriority;                        /*�ھ����ȼ�*/
    ULONG  ulNbrState;                          /*�ھӵ�״̬*/
    ULONG  ulNbrRtrId;                          /*�ھ�router id*/
}OSPF6_SHOWPEER_S;

/*STRUCT<OSPF6��̬�ھ�������Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWCFGPEER
{
    ULONG  ulInstanceId;                         /*Instance ID*/ 
    ULONG  ulIfIndex;                            /*�ӿ�����*/ 
    UCHAR  ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN];   /*�ֹ����öԶ˵ĵ�ַ*/
    ULONG  ulNbrPriority;                        /*�ھ����ȼ�*/
}OSPF6_SHOWCFGPEER_S;

/*STRUCT<�ӿڰ���Ϣ��ѯ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWINTFBIND
{
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*�ӿ���*/
    UCHAR  ucIpAddr[OSPF6_MAX_INET_ADDR_LEN];       /*IP6��ַ*/
    ULONG  ulProcessId;                           /*����ID*/
    ULONG  ulInstanceId;                          /*Instance ID */ 
    ULONG  ulAreaId;                              /*����ID*/
    ULONG  ulIfIndex;                             /*�ӿ�����ֵ*/
}OSPF6_SHOWINTFBIND_S;

/*STRUCT<OSPF6�ӿ�������Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_SHOWINTFATTR
{
    CHAR   szIfName[OSPF6_MAX_IF_NAME_LENGTH + 1];/*�ӿ���*/
    ULONG  ulInstanceId;                        /*Instance ID */ 
    ULONG  ulIfIndex;                           /*�ӿ�����*/ 
    ULONG  ulAttrBits;                          /*��Ч����Bitsλ */ 
    ULONG  ulIfNetworkType;                     /*�ӿ���������
                                                  1 - �㲥
                                                  2 - NBMA
                                                  3 - �㵽��
                                                  5 - �㵽���*/
    ULONG  ulIfMetric;                          /*�ӿ�COST*/
    ULONG  ulIfPriority;                        /*���ȼ�*/
    ULONG  ulRxmtInterval;                      /*LSA�ش�ʱ��*/ 
    ULONG  ulTransDelay;                        /*�ӿڴ�����ʱ*/ 
    ULONG  ulHelloInterval;                     /*Hello��� FastHello��Чʱ��Ч*/  
    ULONG  ulDeadInterval;                      /*Dead���*/ 
    ULONG  ulFastHelloMulti;                    /*Fast Hello Multiple*/
    ULONG  ulPollInterval;                      /*��ѯ���*/ 
    ULONG  ulMtuIgnoreFlg;                      /*MTU���Ա��*/ 
    ULONG  ulGrHelperMode;
    ULONG  ulGrHelperPeriod;
    ULONG  ulGrHelperAccNum;
}OSPF6_SHOWINTFATTR_S;

/*STRUCT<OSPF6Э�����ȼ���Ϣ�ṹ�壬����ѯ�ӿ����>*/
typedef struct tagOSPF6_PREFERENCE_SHOW
{
    ULONG  ulVrfIndex;                      /*VRF����*/
    UCHAR  ucPreferenceInt;                 /*������·���ϵĴ��ۣ���Χ:1~255*/
    UCHAR  ucPreferenceExt;                 /*�ⲿ·���ϵĴ��ۣ���Χ:1~255*/    
    UCHAR  ucPadding[2];                    /*���*/
}OSPF6_PREFERENCE_SHOW_S;




typedef struct tagOSPF6_SHOWCUMLTVE_OUT
{
    ULONG  ulRouterId;
    USHORT usProcessId;
    USHORT usPadding;/*������չ*/
   
    /* packets stat. */
    ULONG  ulInHello;              /* input hello pkts */
    ULONG  ulOutHello;
    ULONG  ulInDbDescr;            /* input DB Description */
    ULONG  ulOutDbDescr;   
    ULONG  ulInLinkStateReq;       /* input Link-State Req */
    ULONG  ulOutLinkStateReq;  
    ULONG  ulInLinkStateUpdate;    /* Input Link-State Update */
    ULONG  ulOutLinkStateUpdate;
    ULONG  ulInLinkStateAck;       /* Link-State Ack  */
    ULONG  ulOutLinkStateAck;

    /* LSAs originated by this router  */
    ULONG  ulRouter;
    ULONG  ulNetwork;
    ULONG  ulInterAreaPrefix;
    ULONG  ulInterAreaRouter;
    ULONG  ulExternal;
    ULONG  ulNssa;   
    ULONG  ulLinkScope;
    ULONG  ulIntraAreaPrefix;
    ULONG  ulIntraAreaTE;
    ULONG  ulOpqExternal;
    ULONG  ulOriginateNewLsas;
    ULONG  ulRxNewLsas;

    ULONG  ulAreaBdr;    /* Area �߽�·���� */
    ULONG  ulAsBdr;      /* as �߽�·���� */

    /* Added by likaikun00213099, ͳ�ƽ��̵ĸ�״̬���ھ�, 2014/4/21 */
    ULONG  ulNumNbr;     /* ���̵��ھ����� */
    ULONG  ulNbrState[OSPF6_NBR_MAX_STATES + 1]; /* ��ͬ״̬���ھӸ��� */
    /* End of Added by likaikun00213099, ͳ�ƽ��̵ĸ�״̬���ھ�, 2014/4/21 */
}OSPF6_SHOWCUMLTVE_OUT_S;

typedef struct tagOSPF6_SHOWERROR_OUT
{    
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
 
    /* general error,��δʶ����������� */
    ULONG ulGenErrLen;       /* ���ȷǷ� */
    ULONG ulGenErrIntf;      /* �Ҳ�����Ӧ�Ľӿ� */
    ULONG ulGenErrType;      /* �������ͷǷ� */
    ULONG ulGenErrChck;      /* check sum �Ƿ� */
    ULONG ulGenErrArea;      /* ��Ƿ� */
    ULONG ulGenErrNbr;       /* �ھӲ�ƥ�� */
    ULONG ulGenErrAuth;

    /* hello error */
    ULONG ulHelloErrSuppressed; /* ��ֹhello���� */
    ULONG ulHelloErrLen;        /* ���ĳ��ȷǷ� */
    ULONG ulHelloErrChck;       /* check sum ʧ�� */
    ULONG ulHelloErrNBMA;       /* δ֪��NBMA�ھ� */
    ULONG ulHelloErrP2P;        /* δ֪��P2P�ھ� */

    /* DD error */
    ULONG ulDdErrLen;           /* ���ĳ��� */
    ULONG ulDdErrMTU;           /* MTU�Ƿ� */
    ULONG ulDdErrNbState;       /* �ھ�״̬�Ƿ� */
    ULONG ulDdErrSequence;      /* �������кŷǷ� */
    ULONG ulDdErrDuplicate;     /* ����Ϊ���� */
    ULONG ulDdErrBadPkt;        /* �����Ƿ� */

    /* LS Req error */
    ULONG ulLsReqErrNbState;    /* �ھ�״̬�Ƿ� */
    ULONG ulLsReqErrLen;        /* ���ĳ��ȷǷ� */
    ULONG ulLsReqErrBadReq;     /* ����ls req�Ƿ� */

    /* LS Update error */
    ULONG ulLsUdpErrLen;        /* ���ĳ��ȷǷ� */
    ULONG ulLsUdpErrNbState;    /* �ھ�״̬�Ƿ� */
    
    /* LS Ack error */
    ULONG ulLsAckErrLen;       /* ���ĳ��ȷǷ� */
    ULONG ulLsAckErrNbState;   /* �ھ�״̬�Ƿ� */
}OSPF6_SHOWERROR_OUT_S;

/*add for S-IP-003-OSPFv3-102*/
typedef struct tagOSPF6_SHOWPLCYDIST_OUT
{
    USHORT  usProcessId;
    CHAR    ucPadding[2];
    /* 
    for ulPlcyDirectFlag:
        #define DF_OSPF_TO_RM 1
        #define DF_RM_TO_OSPF 2
    */
    ULONG   ulPlcyDirectFlag;
    OSPF6_RPM_PLCYDIST_S stPlcyDist;
}OSPF6_SHOWPLCYDIST_OUT_S;

/*******************************************************************************
*    Func Name: OSPF6_CMM_Handle_Close
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����OSPF6 ��ѯ�Ĺرղ���
*  Description: �ر�Handle���
*        Input: ULONG ulHandle:Handle<�ǿ�>
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Handle_Close(ULONG ulHandle);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: OSPF6������Ϣ��ѯ��Open����
*  Description: OSPF6������Ϣ��ѯ��Open����,���ڻ�ȡOSPF6������Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������ָ��<�ǿ�> 
*       Output: ULONG *pulHandle:Handle���<�ǿ�>
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Entity_GetFirst
*               OSPF6_CMM_Entity_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��OSPFv3ʵ����Ϣ
*  Description: ��ȡ��һ��OSPFv3ʵ����Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�> 
*       Output: OSPF6_ENTITY_SHOW_S *pstShow:ʵ����Ϣ<�ǿ�> 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Entity_Open
*               OSPF6_CMM_Entity_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_GetFirst(ULONG ulHandle,OSPF6_ENTITY_SHOW_S *pstShow); 
/*******************************************************************************
*    Func Name: OSPF6_CMM_Entity_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��OSPFv3ʵ����Ϣ
*  Description: ��ȡ��һ��OSPFv3ʵ����Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�> 
*       Output: OSPF6_ENTITY_SHOW_S *pstShow:ʵ����Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Entity_Open
*               OSPF6_CMM_Entity_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Entity_GetNext(ULONG ulHandle,OSPF6_ENTITY_SHOW_S *pstShow);
/*******************************************************************************
*    Func Name: OSPF6_ShowEntityInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾOSPFv3ʵ����Ϣ
*  Description: ��ʾOSPFv3ʵ����Ϣ
*        Input: USHORT usProcId:����ID<0~0xffff��0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺�>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowEntityInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ�ӿ���Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ�ӿ���Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������<�ǿ�>
*       Output: ULONG *pulHandle:Handle���
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Intf_GetFirst
*               OSPF6_CMM_Intf_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ���ӿ���Ϣ
*  Description: ��ȡһ���ӿ���Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*       Output: OSPF6_SHOWINTF_S *pstIntfIn:�ӿ���Ϣ<�ǿ�>
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Intf_Open
*               OSPF6_CMM_Intf_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_GetFirst(ULONG ulHandle,OSPF6_SHOWINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Intf_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ���ӿ���Ϣ
*  Description: ��ȡ��һ���ӿ���Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*       Output: OSPF6_SHOWINTF_S *pstIntfIn:�ӿ���Ϣ<�ǿ�>
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Intf_Open
*               OSPF6_CMM_Intf_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Intf_GetNext (ULONG ulHandle,OSPF6_SHOWINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ�ӿ���Ϣ
*  Description: ��ʾ�ӿ���Ϣ
*        Input: USHORT usProcId:����ID<0~0xffff��0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺�>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ������Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ������Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Area_GetFirst
*               OSPF6_CMM_Area_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ��������Ϣ
*  Description: ��ȡһ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_AREA_S *pstAreaIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Area_Open
*               OSPF6_CMM_Area_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_GetFirst(ULONG ulHandle,OSPF6_SHOW_AREA_S *pstAreaIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Area_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��������Ϣ
*  Description: ��ȡ��һ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_AREA_S *pstAreaIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Area_Open
*               OSPF6_CMM_Area_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Area_GetNext (ULONG ulHandle,OSPF6_SHOW_AREA_S *pstAreaIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowAreaInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ������Ϣ
*  Description: ��ʾ������Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                               0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowAreaInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ�ھ���Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ�ھ���Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������<�ǿ�>
*       Output: ULONG *pulHandle:Handle���
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_GetFirst
*               OSPF6_CMM_Nbr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ���ھ���Ϣ
*  Description: ��ȡһ���ھ���Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*       Output: OSPF6_SHOWNBR_S *pstNbrIn:�ھ���Ϣ<�ǿ�>
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_Open
*               OSPF6_CMM_Nbr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_GetFirst(ULONG ulHandle,OSPF6_SHOWNBR_S *pstNbrIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Nbr_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ���ھ���Ϣ
*  Description: ��ȡ��һ���ھ���Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*       Output: OSPF6_SHOWNBR_S *pstNbrIn:�ھ���Ϣ<�ǿ�>
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Nbr_Open
*               OSPF6_CMM_Nbr_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Nbr_GetNext (ULONG ulHandle,OSPF6_SHOWNBR_S *pstNbrIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowNbrInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ�ھ���Ϣ
*  Description: ��ʾ�ھ���Ϣ
*        Input: USHORT usProcId:����ID<0~0xffff��0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺�>
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowNbrInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡLSDB��Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡLSDB��Ϣ
*        Input: OSPF6_LSDB_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_GetFirst
*               OSPF6_CMM_Lsdb_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_Open(ULONG *pulHandle,OSPF6_LSDB_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ��LSDB��Ϣ
*  Description: ��ȡһ��LSDB��Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWLSDB_S *pstLsdbIn:LSDB��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_Open
*               OSPF6_CMM_Lsdb_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_GetFirst(ULONG ulHandle,OSPF6_SHOWLSDB_S *pstLsdbIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Lsdb_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��LSDB��Ϣ
*  Description: ��ȡ��һ��LSDB��Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWLSDB_S *pstLsdbIn:LSDB��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Lsdb_Open
*               OSPF6_CMM_Lsdb_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Lsdb_GetNext (ULONG ulHandle,OSPF6_SHOWLSDB_S *pstLsdbIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowLsdbInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾLSDB��Ϣ
*  Description: ��ʾLSDB��Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                               0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*               USHORT usLsaType:LSA����,��Χ��0,�궨��OSPF6_XXXXX_LSA
*                               0�����е�LSA���ͣ�OSPF6_XXXXX_LSA��ָ����LSA���͡�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowLsdbInfo(USHORT usProcId,USHORT usLsaType);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡRoute��Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡRoute��Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Route_GetFirst
*               OSPF6_CMM_Route_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ��Route��Ϣ
*  Description: ��ȡһ��Route��Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWROUTE_S *pstRouteIn:Route��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Route_Open
*               OSPF6_CMM_Route_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_GetFirst(ULONG ulHandle,OSPF6_SHOWROUTE_S *pstRouteOut);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Route_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��Route��Ϣ
*  Description: ��ȡ��һ��Route��Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWROUTE_S *pstRouteIn:Route��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Route_Open
*               OSPF6_CMM_Route_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Route_GetNext (ULONG ulHandle,OSPF6_SHOWROUTE_S *pstRouteOut);
/*******************************************************************************
*    Func Name: OSPF6_ShowRouteInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾRoute��Ϣ
*  Description: ��ʾRoute��Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                               0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowRouteInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ѯOSPF6����������õĵ�һ����Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡRedistribute��Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Redist_GetFirst
*               OSPF6_CMM_Redist_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ��·�����������Ϣ
*  Description: ��ȡһ��·�����������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWREDIST_S *pstRedistIn:Redistribute��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Redist_Open
*               OSPF6_CMM_Redist_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_GetFirst(ULONG ulHandle,OSPF6_SHOWREDIST_S *pstRedistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Redist_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��·�����������Ϣ
*  Description: ��ȡ��һ��·�����������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWREDIST_S *pstRedistIn:Redistribute��Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Redist_Open
*               OSPF6_CMM_Redist_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Redist_GetNext (ULONG ulHandle,OSPF6_SHOWREDIST_S *pstRedistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowRedistInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ·�����������Ϣ
*  Description: ��ʾ·�����������Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                                  0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowRedistInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ѯOSPF6����������õĵ�һ����Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ������Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_GetFirst
*               OSPF6_CMM_ExportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_Open(ULONG *pulHandle,OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ��������Ϣ
*  Description: ��ȡһ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_Open
*               OSPF6_CMM_ExportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_GetFirst(ULONG ulHandle,OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ExportFilter_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ��������Ϣ
*  Description: ��ȡ��һ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ExportFilter_Open
*               OSPF6_CMM_ExportFilter_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ExportFilter_GetNext (ULONG ulHandle,OSPF6_SHOW_EXPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowExportFilterInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ������Ϣ
*  Description: ��ʾ������Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                                  0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowExportFilterInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ѯOSPF6����ۺϵĵ�һ����Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ����ۺ���Ϣ
*        Input: OSPF6_AREA_AGG_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_GetFirst
*               OSPF6_CMM_AreaAgg_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_Open(ULONG *pulHandle,OSPF6_AREA_AGG_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ������ۺ���Ϣ
*  Description: ��ȡһ������ۺ���Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWAREA_AGG_S *pstAreaAggIn:����ۺ���Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_Open
*               OSPF6_CMM_AreaAgg_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_GetFirst(ULONG ulHandle,OSPF6_SHOWAREA_AGG_S *pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_AreaAgg_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ������ۺ���Ϣ
*  Description: ��ȡ��һ������ۺ���Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWAREA_AGG_S *pstAreaAggIn:����ۺ���Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_AreaAgg_Open
*               OSPF6_CMM_AreaAgg_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_AreaAgg_GetNext (ULONG ulHandle,OSPF6_SHOWAREA_AGG_S *pstAreaAggIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowAreaAggInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ����ۺ���Ϣ
*  Description: ��ʾ����ۺ���Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                               0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*               ULONG ulAreaId: ����ID
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowAreaAggInfo(USHORT usProcId,ULONG ulAreaId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_Open
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ��̬�����ھ���Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ��̬�����ھ���Ϣ
*        Input: OSPF6_PEER_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Peer_GetFirst
*               OSPF6_CMM_Peer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_Open(ULONG *pulHandle,OSPF6_PEER_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_GetFirst
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡһ����̬�����ھ���Ϣ
*  Description: ��ȡһ����̬�����ھ���Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWPEER_S *pstPeerIn:��̬�����ھ���Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Peer_Open
*               OSPF6_CMM_Peer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_GetFirst(ULONG ulHandle,OSPF6_SHOWPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_Peer_GetNext
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ȡ��һ����̬�����ھ���Ϣ
*  Description: ��ȡ��һ����̬�����ھ���Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOWPEER_S *pstPeerIn:��̬�����ھ���Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_Peer_Open
*               OSPF6_CMM_Peer_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Peer_GetNext (ULONG ulHandle,OSPF6_SHOWPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowPeerInfo
* Date Created: 2009-06-17
*       Author: qinyun62011
*      Purpose: ��ʾ��̬�����ھ���Ϣ
*  Description: ��ʾ��̬�����ھ���Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                                  0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*               ULONG ulInstanceId:ʵ��ID,��Χ: 0~255��
*                                  OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ��
*               CHAR *szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowPeerInfo(USHORT usProcId,ULONG ulInstanceId,CHAR *szIfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_Open
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ�ӿ�������Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ�ӿ�������Ϣ�����й��������ӿ�����
*               �ͽ���ID������ϲ�ѯ
*        Input: OSPF6_INTF_BIND_FILTER_S *pstFilterIn:��������<�ǿ�>
*       Output: ULONG *pulHandle:Handle���
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_GetFirst
*               OSPF6_CMM_IntfBind_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_Open(ULONG *pulHandle,OSPF6_INTF_BIND_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_GetFirst
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ȡһ���ӿ�������Ϣ
*  Description: ��ȡһ���ӿ�������Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:�ӿ�������Ϣ<�ǿ�>
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_Open
*               OSPF6_CMM_IntfBind_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_GetFirst(ULONG ulHandle,OSPF6_SHOWINTFBIND_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfBind_GetNext
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ȡ��һ���ӿ�������Ϣ
*  Description: ��ȡ��һ���ӿ�������Ϣ
*        Input: ULONG ulHandle:Handle���<�ǿ�>
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:�ӿ�������Ϣ<�ǿ�>
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfBind_Open
*               OSPF6_CMM_IntfBind_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfBind_GetNext(ULONG ulHandle,OSPF6_SHOWINTFBIND_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfBindInfo
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ʾ�û����õĽӿ���Ϣ
*  Description: ��ʾ�û����õĽӿ���Ϣ
*        Input: USHORT usProcId:����ID<0~0xffff��0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺�>
*               CHAR *szIfName:�ӿ���<�ǿ�>
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfBindInfo(USHORT usProcId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Pref_GetByVrfName
* Date Created: 2009-09-04
*       Author: hanna55555
*      Purpose: ��ȡָ��VRF�µ�OSPFЭ�����ȼ�
*  Description: ��ȡָ��VRF�µ�OSPFЭ�����ȼ�
*        Input: CHAR *pszVrfName:VRF����
*               OSPF6_PREFERENCE_SHOW_S *pstPrefIn:���ȼ�������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Pref_GetByVrfName(CHAR *pszVrfName,OSPF6_PREFERENCE_SHOW_S *pstPrefIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowPreferenceInfo
* Date Created: 2009-09-04
*       Author: hanna55555
*      Purpose: ��ʾָ��VRF�µ�OSPFЭ�����ȼ�
*  Description: ��ʾָ��VRF�µ�OSPFЭ�����ȼ�
*        Input: CHAR *pszVrfName:VRF����
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-04   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowPreferenceInfo(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_Open
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: ��ѯOSPF6���չ������õĵ�һ����Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ������Ϣ
*        Input: OSPF6_FILTER_S *pstFilterIn:��������
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_GetFirst
*               OSPF6_CMM_ImportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_Open(ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_GetFirst
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: ��ȡһ��������Ϣ
*  Description: ��ȡһ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_Open
*               OSPF6_CMM_ImportFilter_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_GetFirst(ULONG ulHandle, OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_ImportFilter_GetNext
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: ��ȡ��һ��������Ϣ
*  Description: ��ȡ��һ��������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn:������Ϣ
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_ImportFilter_Open
*               OSPF6_CMM_ImportFilter_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-06-17   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
ULONG OSPF6_CMM_ImportFilter_GetNext (ULONG ulHandle, OSPF6_SHOW_IMPORT_FILTER_S *pstDistIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowImportFilterInfo
* Date Created: 2009-06-17
*       Author: wangbin (62223) & luogaowei(61496)
*      Purpose: ��ʾ���չ�����Ϣ
*  Description: ��ʾ���չ�����Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*                                  0�����ڵ����н��̣�1��0xffff��ָ����OSPF���̺š�
*       Output: 
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-10   wangbin (62223) & luogaowei(61496)             Create
*
*******************************************************************************/
VOID OSPF6_ShowImportFilterInfo(USHORT usProcId);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_Open
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ�ӿ�����������Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ�ӿ�����������Ϣ
*        Input: OSPF6_INTF_ATTR_FILTER_S *pstFilterIn:ʵ��ID�ͽӿ�����������ϲ�ѯ
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_GetFirst
*               OSPF6_CMM_IntfAttr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_Open(ULONG *pulHandle,OSPF6_INTF_ATTR_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_GetFirst
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: ��ȡһ���ӿ�����������Ϣ
*  Description: ��ȡһ���ӿ�����������Ϣ
*        Input: ULONG ulHandle:���
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:�ӿ�����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_Open
*               OSPF6_CMM_IntfAttr_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_GetFirst(ULONG ulHandle,OSPF6_SHOWINTFATTR_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_IntfAttr_GetNext
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: ��ȡ��һ���ӿ�����������Ϣ
*  Description: ��ȡ��һ���ӿ�����������Ϣ
*        Input: ULONG ulHandle:���
*               OSPF6_SHOWINTFBIND_S *pstIntfIn:�ӿ�����������Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_IntfAttr_Open
*               OSPF6_CMM_IntfAttr_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_IntfAttr_GetNext(ULONG ulHandle,OSPF6_SHOWINTFATTR_S *pstIntfIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowIntfAttrInfo
* Date Created: 2009-09-18
*       Author: hanna55555
*      Purpose: ��ʾ�û����õĽӿ�������Ϣ
*  Description: ��ʾ�û����õĽӿ�������Ϣ
*        Input: ULONG ulInstanceId:ʵ��ID,��Χ: 0~255��
*                                  OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ��
*               CHAR *szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-18   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowIntfAttrInfo(ULONG ulInstanceId,CHAR *szIfName);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_Open
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ��̬�ھ�������Ϣ
*  Description: ����һ��Handle�����ڴ���һ������ȡ��̬�ھ�������Ϣ
*        Input: OSPF6_CFGPEER_FILTER_S *pstFilterIn:ʵ��ID�ͽӿ�����������ϲ�ѯ
*       Output: ULONG *pulHandle:���
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_GetFirst
*               OSPF6_CMM_CfgPeer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_Open(ULONG *pulHandle,OSPF6_CFGPEER_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_GetFirst
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: ��ȡ�û����õĵ�һ����̬�ھ���Ϣ
*  Description: ��ȡ�û����õĵ�һ����̬�ھ���Ϣ
*        Input: ULONG ulHandle:���
*               OSPF6_SHOWCFGPEER_S *pstPeerIn:�û����þ�̬�ھ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_Open
*               OSPF6_CMM_CfgPeer_GetNext
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_GetFirst(ULONG ulHandle,OSPF6_SHOWCFGPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_CMM_CfgPeer_GetNext
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: ��ȡ�û����õ���һ����̬�ھ���Ϣ
*  Description: ��ȡ�û����õ���һ����̬�ھ���Ϣ
*        Input: ULONG ulHandle:���
*               OSPF6_SHOWCFGPEER_S *pstPeerIn:�û����þ�̬�ھ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: OSPF6_CMM_CfgPeer_Open
*               OSPF6_CMM_CfgPeer_GetFirst
*               OSPF6_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
ULONG OSPF6_CMM_CfgPeer_GetNext(ULONG ulHandle,OSPF6_SHOWCFGPEER_S *pstPeerIn);
/*******************************************************************************
*    Func Name: OSPF6_ShowCfgPeerInfo
* Date Created: 2009-09-21
*       Author: hanna55555
*      Purpose: ��ʾ�û����õľ�̬�ھ���Ϣ
*  Description: ��ʾ�û����õľ�̬�ھ���Ϣ
*        Input: ULONG ulInstanceId:ʵ��ID,��Χ: 0~255��
*                                  OSPF6_ALL_INST_FILTER:��ָ��ʵ���Ų�ѯ��
*               CHAR *szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-21   hanna55555              Create
*
*******************************************************************************/
VOID OSPF6_ShowCfgPeerInfo(ULONG ulInstanceId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_Clear
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ���OSPF6����ȷ����ͳ����Ϣ
*        Input: USHORT usProcessId:����ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_CMM_Cumul_Clear(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_Open
* Date Created: 2010-03-30
*       Author: zhangbo146309
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ��ȷ���ĵ�ͳ����Ϣ
*        Input: ULONG* pulHandle: Handle���
*               OSPF6_FILTER_S *pstFilterIn: ��ȷ����ͳ�ƵĹ�����Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_Open(ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_GetFirst
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ����һ��Handle�����ڴ򿪵�һ������ȡ��ȷ���ĵ�ͳ����Ϣ
*        Input: ULONG ulHandle: Handle���
*               OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut: ��ȷ����ͳ�Ƶ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_GetFirst (ULONG ulHandle, OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Cumul_GetNext
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ��ȡһ��Handle�����ڴ���һ������ȡ��ȷ���ĵ�ͳ����Ϣ
*        Input: ULONG ulHandle: Handle���
*               OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut: ��ȷ����ͳ�Ƶ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Cumul_GetNext (ULONG ulHandle, OSPF6_SHOWCUMLTVE_OUT_S *pstCumulOut); 

/*******************************************************************************
*    Func Name: OSPF6_ShowCumul
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ��ʾOSPF6����ȷ����ͳ����Ϣ
*        Input: USHORT usProcessId:����ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_ShowCumul(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_Clear
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ���OSPF6�Ĵ�����ͳ����Ϣ
*        Input: USHORT usProcessId:����ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_CMM_Error_Clear(USHORT usProcessId);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_Open
* Date Created: 2010-03-30
*       Author: zhangbo146309
*      Purpose: ����һ��Handle�����ڴ���һ������ȡ����ı��ĵ�ͳ����Ϣ
*        Input: ULONG* pulHandle: Handle���
*               OSPF6_FILTER_S *pstFilterIn: ������ͳ�ƵĹ�����Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_Open (ULONG *pulHandle, OSPF6_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_GetFirst
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ����һ��Handle�����ڴ򿪵�һ������ȡ�����ĵ�ͳ����Ϣ
*        Input: ULONG ulHandle: Handle���
*               OSPF6_SHOWERROR_OUT_S *pstErrorOut: ������ͳ�Ƶ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_GetFirst (ULONG ulHandle,OSPF6_SHOWERROR_OUT_S * pstErrorOut );


/*******************************************************************************
*    Func Name: OSPF6_CMM_Error_GetNext
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ����һ��Handle�����ڴ���һ������ȡ�����ĵ�ͳ����Ϣ
*        Input: ULONG ulHandle: Handle���
*               OSPF6_SHOWERROR_OUT_S *pstErrorOut: ������ͳ�Ƶ���Ϣ
*       Output: 
*       Return: �ɹ�����OSPF6_OK
*               ʧ�ܷ��ش�����
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
ULONG OSPF6_CMM_Error_GetNext (ULONG ulHandle, OSPF6_SHOWERROR_OUT_S * pstErrorOut );

/*******************************************************************************
*    Func Name: OSPF6_ShowError
* Date Created: 2010-03-30
*       Author: zhangbo146309
*  Description: ��ʾOSPF6�Ĵ�����ͳ����Ϣ
*        Input: USHORT usProcessId:����ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-03-30   zhangbo146309           Create
*
*******************************************************************************/
VOID OSPF6_ShowError(USHORT usProcessId);

ULONG  OSPF6_CMM_PolicyDist_Open ( ULONG* pulHandle, OSPF6_FILTER_S * pstPolicyDistIn );

ULONG OSPF6_CMM_PolicyDist_GetFirst ( ULONG ulHandle, OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );


ULONG OSPF6_CMM_PolicyDist_GetNext ( ULONG ulHandle, OSPF6_SHOWPLCYDIST_OUT_S * pstPolicyDistOut );


VOID OSPF6_ShowPolicyDistInfo(USHORT usProcessId);


#ifdef __cplusplus
        }
#endif /* __cplusplus */
        
#endif /* _OSPF6_CMM_API_H_ */

