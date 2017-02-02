

#ifndef _TCPIP_PUB_API_H_
#define _TCPIP_PUB_API_H_

#ifdef  __cplusplus
extern  "C"{
#endif

/*******************************�궨��****************************************/
#define LINK_HOOK_INPUT_PKT     0x01   /*��·��ע�ṳ�ӽ��շ���*/
#define LINK_HOOK_OUTPUT_PKT    0x02   /*��·��ע�ṳ�ӷ��ͷ���*/

/*·�ɱ��*/
#define PPI_RTF_UP              0x0001  /*·�ɿ���*/
#define PPI_RTF_GATEWAY         0x0002  /*Ŀ�ĵ�ַ��·��*/
#define PPI_RTF_HOST            0x0004  /*����·�ɣ�����Ϊ����·��*/
#define PPI_RTF_REJECT          0x0008
#define PPI_RTF_DYNAMIC         0x0010  /*��̬·��*/
#define PPI_RTF_STATIC          0x0800  /*��̬·��*/
#define PPI_RTF_SUBNET_BROCST   0x10000 /*�����㲥·��*/
#define PPI_RTF_BLACKHOLE       0x1000  /*�ڶ�·�ɣ���ʾ��Ҫ��������*/
#define PPI_RTF_REJECT2         0x8000

/*ARP��־*/
#define PPI_ARPF_RESOLVED       0x01    /*ARP�ѽ���*/
#define PPI_ARPF_RESOLVING      0x02    /*ARP���ڽ���*/
#define PPI_ARPF_STATIC         0x04    /*��̬ARP*/
#define PPI_ARPF_DYNAMIC        0x08    /*��̬ARP*/


#define PPI_RTMSG_LENGTH        sizeof(PPI_RTMSG4_S)
#define PPI_ARP_LENGTH          sizeof(PPI_ARP_S)

/*mc�Ĺ��*/
#define PPI_MC_PREFIX_MAX_NUM        16  /*ǰ׺ʡ�ԶԵ���Ŀ*/
#define PPI_MC_PREFIX_MAX_LEN        8   /*ǰ׺ʡ�Եı��ĳ���*/

/*IPHCѹ������*/
#define PPI_IPHC_COMPRESS_ALL       0   /* ��TCP/non-TCP���Ķ�ѹ�� */
#define PPI_IPHC_COMPRESS_NON_TCP   1   /* ��ѹ��no-TCP���� */
#define PPI_IPHC_COMPRESS_TCP       2   /* ��ѹ��TCP����*/
#define PPI_IPHC_COMPRESS_NONE      3   /* ��ֹѹ��TCP��non-TCP���� */

/* ������RTP Compression��Enhanced RTP Compressionѹ��*/
#define PPI_IPHC_NONE_RTP_COMPRESSION      0
/* ����RTP Compressionѹ�� */
#define PPI_IPHC_RTP_COMPRESSION           1
/* ����Enhanced RTP Compressionѹ�� */
#define PPI_IPHC_ENHANCED_RTP_COMPRESSION  2

#define DYNAMIC_ARP_TYPE_NONE         0x00  /*ARP��ʼ��ǣ��п�����ARP��Ԫ*/
#define DYNAMIC_ARP_TYPE_USER_CONFIG  0x01  /*�û����ö�̬ARP����*/
#define DYNAMIC_ARP_TYPE_LERAN        0x02  /*��̬ѧϰARP����*/
#define DYNAMIC_ARP_TYPE_REFRESH      0x03  /*�û����õĶ�̬ARP���ˢ��*/

/*1AG MD������ֳ���*/
#ifndef OAM_1AG_MAX_MDNAME_LEN
#define OAM_1AG_MAX_MDNAME_LEN 43
#endif
/*1AG MA������ֳ���*/
#ifndef OAM_1AG_MAX_MANAME_LEN
#define OAM_1AG_MAX_MANAME_LEN 43
#endif
/*Y1731 MA������ֳ���*/
#ifndef OAM_Y1731_MAX_MANAME_LEN
#define OAM_Y1731_MAX_MANAME_LEN 13
#endif

#ifndef MACADDRLEN
#define MACADDRLEN 6   /* physical��ַ���� */
#endif

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN 47       /* ���ӿ������� */
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define  TCPIP_MAX_VRFNAME_LENGTH   31      /*VPN���ֳ���*/
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*������־���������*/
#define LOG_TYPE_WARNING        0x001
#define LOG_TYPE_CFG            0x010
#define LOG_TYPE_RUN            0x100

/* HAԤ����ģ�� */
#define HA_PRECFG_BASIC         0x00000001
#define HA_PRECFG_ETH           0x00000002
#define HA_PRECFG_PPP           0x00000004
#define HA_PRECFG_POEC          0x00000008
#define HA_PRECFG_POES          0x00000010
#define HA_PRECFG_DHCP4C        0x00000020
#define HA_PRECFG_DHCP4R        0x00000040
#define HA_PRECFG_BFD           0x00000080
#define HA_PRECFG_EOAM3AH       0x00000100
#define HA_PRECFG_OAM1AG        0x00000200
#define HA_PRECFG_IGMP          0x00000400
#define HA_PRECFG_VRF           0x00000800
#define HA_PRECFG_TWAMP           0x00001000
#define HA_PRECFG_ALL           0xFFFFFFFF

#define TCPIP_HA_AMB                0x1     /* ���ð� */
#define TCPIP_HA_SMB                0x0     /* ���ð� */

/* HAע���ģ���� */
#define HA_MOUDLE_NAME_LEN          23

/* ���ע��HAģ����Ŀ */
#define HA_MAX_REGISTER_MOUDLE_NUM  16

/* Ŀǰֻ��OSP��ʹ��VISP SRM,���ǻ�ʹ��VISP FIB, ����������Ҫע���޸�*/
#define RM_DCLRTM    2
#define RM_VISPSRM   1
#define RM_PRODUCT   0
/*END Add*/
/*******************************ö��****************************************/
/*PPI��������,�޸Ĵ˽ṹ�����޸Ķ�Ӧ��TCPIP_PPI_OprType_En[]�ṹ,��common/dataplanĿ¼�¶�Ӧ�ĸýӿڵĿ���*/
enum tagPPIOprType
{
    /*do nothing*/
    PPI_OPR_NULL,

    /*·����Ϣ����*/
    PPI_ENTRY_FIB4_ADD,         /* 1 ���·����Ϣ*/
    PPI_ENTRY_FIB4_DEL,         /* 2 ɾ��·����Ϣ*/
    PPI_ENTRY_FIB4_UPDATE,      /* 3 ˢ��·����Ϣ*/

    /*ARP��������*/
    PPI_ENTRY_ARP_ADD,          /* 4 ���ARP*/
    PPI_ENTRY_ARP_DEL,          /* 5 ɾ��ARP*/
    PPI_ENTRY_ARP_UPDATE,       /* 6 ˢ��ARP*/

    /*IFNET����*/
    PPI_IF_CREATE,              /* 7 �ӿڴ���*/
    PPI_IF_DELETE,              /* 8 �ӿ�ɾ��*/
    PPI_IF_SETMTU,              /* 9 ����MTU*/
    PPI_IF_GETMAXMTU,           /* 10 ��ȡ���MTU */
    PPI_IF_UP,                  /* 11 �ӿ�UP*/
    PPI_IF_DOWN,                /* 12 �ӿ�DOWN*/
    PPI_IF_SETMAC,              /* 13 ����TRUNK�ӿڵ�physical��ַ */
    PPI_IF_SET_DEV,             /* 14 ���ýӿ��������*/

    PPI_TRUNKPORT_UP,           /* 15 PORT UP*/
    PPI_TRUNKPORT_DOWN,         /* 16 PORT DOWN*/

    /*PPP����*/
    PPI_PPP_SET_LCPGOTOPTION,   /* 17 ֪ͨNP LCP����Э��ѡ��*/
    PPI_PPP_SET_LCPHISOPTION,   /* 18 ֪ͨNP LCP�Զ�Э��ѡ��*/
    PPI_PPP_SET_IPCPGOTOPTION,  /* 19 ֪ͨNP IPCP����Э��ѡ��*/
    PPI_PPP_SET_IPCPHISOPTION,  /* 20 ֪ͨNP IPCP�Զ�Э��ѡ��*/
    PPI_PPP_SET_MUXCPGOTOPTION, /* 21 ֪ͨNP MUXCP����Э��ѡ��*/
    PPI_PPP_SET_MUXCPHISOPTION, /* 22 ֪ͨNP MUXCP�Զ�Э��ѡ��*/

    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
    PPI_PPP_SET_IP6CPGOTOPTION,  /* 23 ֪ͨNP IP6CP����Э��ѡ��*/
    PPI_PPP_SET_IP6CPHISOPTION,  /* 24 ֪ͨNP IP6CP�Զ�Э��ѡ��*/
    /*End of Added by hanna55555, 2009/3/30 */

    PPI_PPP_ADD_MLPPP,          /* 25 ֪ͨNP�ӿڼ��뵽ML PPP*/
    PPI_PPP_DEL_MLPPP,          /* 26 ֪ͨNP�ӿڴ�һ��ML PPP��ɾ��*/
    PPI_PPP_SET_CONFIGINFO,     /* 27 ֪ͨNP���˵�������Ϣ*/
    PPI_PPP_GET_INFO,           /* 28 ��ȡ�·���NP��PPP/MP��Ϣ*/

    PPI_IP_SENDPKT,                 /* 29 ����IP����*/

    PPI_3AH_CREATE,                 /* 30 ����3ah NP�Ự*/
    PPI_3AH_UPDATE,                 /* 31 ����3ah NP�Ự*/
    PPI_3AH_DELETE,                 /* 32 ɾ��3ah NP�Ự*/

    /*1AG���*/
    PPI_OAM1AG_ENABLECCM,       /* 33 ʹ��CCM����*/
    PPI_OAM1AG_DISABLECCM,      /* 34 ȥʹ��CCM����*/
    PPI_OAM1AG_SETINTERVAL,     /* 35 CCM���·�������*/
    PPI_OAM1AG_SETCOMPATIBLE,   /* 36 ����ģʽ*/
    PPI_OAM1AG_SETGLBPARA,      /* 37 1ag����ȫ������*/
    OAM_OAM1AG_SETRMEPPARA,     /* 38 ���ӻ����RMEP�Ĳ���*/
    OAM_OAM1AG_DELRMEPRARA,     /* 39 ɾ��RMEP��*/
    PPI_OAM1AG_SETMAVLANPRI,    /* 40 ���û���MA��VLAN���ȼ���δ����ȡȫ�����ȼ�*/
    PPI_OAM1AG_SETRDIFLAG,      /* 41 ����ͬһMA������MEP����CCM����ʱ��RDIFLAGֵ*/
    PPI_OAM1AG_SETGLOBALVLANPRITOMA,    /*42 ����ȫ��VLAN���ȼ���ʹ��ȫ��VLAN���ȼ���MA��*/
    /* VISP1.8.1 ֧��1AG��׼Э�鿪��*/
    PPI_OAM1AG_SET1AGVERSION,    /* 43 ����MEPʹ�õ�1AGЭ��汾 */
    /* Added for ֧�ֽ��ղ���VLANͷ��1AG����2009-05-14 */
    PPI_OAM1AG_SETMEPVLANFLAG,   /* 44 ����MEP�·��ͱ���ʱ�Ƿ���Ҫ��VLANͷ��־.
                                       0:��ʾ����Ҫ��VLANͷ,1��ʾ��Ҫ��VLAN*/
    PPI_OAM1AG_CREATE_MD,            /* 45 ����ά���� */
    PPI_OAM1AG_DELETE_MD,            /* 46 ɾ��ά���� */
    PPI_OAM1AG_CREATE_MA,            /* 47 ����ά���� */
    PPI_OAM1AG_DELETE_MA,            /* 48 ɾ��ά���� */
    PPI_OAM1AG_CREATE_MEP,           /* 49 ����ά���ڵ� */
    PPI_OAM1AG_DELETE_MEP,           /* 50 ɾ��ά���ڵ� */
    PPI_OAM1AG_GETMEP,               /* 51 ��ȡMEP��Ϣ */

    PPI_IP_JOIN_MULTI,          /* 52 ֪ͨNP��������ಥ��*/
    PPI_IP_LEAVE_MULTI,         /* 53 ֪ͨNP�����뿪�ಥ��*/

    PPI_ENTRY_FIB6_ADD,         /* 54 */
    PPI_ENTRY_FIB6_DEL,         /* 55 */
    PPI_ENTRY_FIB6_UPDATE,      /* 56 */

    /* L2IF vlan ppi cmd */
    PPI_VLAN_CREATE,                        /* 57 ֪ͨNP����VLAN */
    PPI_VLAN_DELETE,                        /* 58 ɾ��VLAN*/
    PPI_VLAN_ADDSUB,                        /* 59 ��ָ����Su*** VLAN�����Sub VLAN*/
    PPI_VLAN_REMOVESUB,                     /* 60 ��ָ����Su*** VLAN��ɾ��ָ����Sub VLAN*/
    PPI_VLAN_SET_TYPE,                      /* 61 ����VLAN���ͣ�����Su**r/Sub/Commom��*/
    PPI_VLAN_SET_UNKOWN_UNICAST_CTR_MODE,   /* 62 ����δ֪���������Ƿ���VLAN�й㲥�Ŀ��ƿ���*/
    PPI_VLAN_SET_BROADCAST_CTR_MODE,        /* 63 ֪ͨNP���ù㲥���Ĵ���ʽ */
    PPI_VLAN_SET_UNKOWN_MULTI_CTR_MODE,     /* 64 ֪ͨNP����δ֪�ಥ���Ĵ���ʽ */
    PPI_VLAN_SET_MACLEARN_MODE,             /* 65 ʹ��/��ֹVLAN�ڵ�physical��ַѧϰ*/
    PPI_VLAN_STATUS_DOWN,                   /* 66 ֪ͨNP VLAN������״̬DOWN */
    PPI_VLAN_STATUS_UP,                     /* 67 ֪ͨNP VLAN������״̬UP */
    PPI_VLANIF_CREATE,                      /* 68 ����vlanif�ӿ�ʱ֪ͨ�������·���mac*/
    PPI_VLANIF_DELETE,                      /* 69 ɾ��vlanif�ӿ�ʱ֪ͨ����*/

    /* L2 �˿���Ϣ���� */
    PPI_PORT_SET_LINK_TYPE,                 /* 70 */
    PPI_PORT_SET_PVID,                      /* 71 */
    PPI_PORT_DEL_PVID,                      /* 72 */
    PPI_VLAN_ADD_PORT_TRUNK,                /* 73 */
    PPI_VLAN_DEL_PORT_TRUNK,                /* 74 */
    PPI_PORT_SET_MAC_LEARN_MODE,            /* 75 */
    PPI_PORT_SET_PRIORITY,                  /* 76 */
    PPI_PORT_SET_FLOW_SUPPRESS,             /* 77 */

    /* L2 ת���������Ϣ���� */
    PPI_FDB_SET_AGINGTIME,                  /* 78 */
    PPI_FDB_ADD,                            /* 79 */
    PPI_FDB_DELETE,                         /* 80 */
    PPI_FDB_DELETE_BY_KEY,                  /* 81 */
    PPI_ML_ENABLE,                          /* 82 */
    PPI_ML_ADD,                             /* 83 */
    PPI_ML_DEL,                             /* 84 */

    /* L2 QinQ��Ϣ���� */
    PPI_QINQ_SET,                           /* 85 */
    PPI_QINQ_DELETE,                        /* 86 */
    PPI_QINQ_SET_PROTOCOL,                  /* 87 */

    /* VRRP��Ϣ����*/
    PPI_VRRP_ENABLE,                        /* 88 */
    PPI_VRRP_ADD_VIRTUAL_MAC,               /* 89 */
    PPI_VRRP_DEL_VIRTUAL_MAC,               /* 90 */

    PPI_VRRP_SUBVLAN_ADD_VIRTUAL_MAC,       /* 91 */
    PPI_VRRP_SUBVLAN_DEL_VIRTUAL_MAC,       /* 92 */
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
    PPI_VRF_CREATE   ,                      /* 93 VRF���� */
    PPI_VRF_DELETE   ,                      /* 94 VRFɾ�� */
    PPI_VRF_BIND   ,                        /* 95 �ӿڰ󶨵�VRF */
    PPI_VRF_UNBIND ,                        /* 96 �ӿ�ȥ��VRF */
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

    /* multicast mac operate type */
    PPI_MULTICMAC_ADD,                      /* 97 ���Ӷಥphysical��ַ */
    PPI_MULTICMAC_DEL,                      /* 98 ɾ���ಥphysical��ַ */

    PPI_TRUNK_ADDPORT,                      /* 99 TRUNK��Ӱ󶨶˿� */
    PPI_TRUNK_REMOVEPORT,                   /* 100 TRUNK�Ƴ��󶨶˿� */

    PPI_AM4_ADD,                            /* 101 AM4��ӵ�ַ */
    PPI_AM4_DELETE,                         /* 102 AM4ɾ����ַ */

    PPI_PPP_SET_OSICPGOTOPTION,             /* 103 ֪ͨNP OSICP����Э��ѡ�� */
    PPI_PPP_SET_OSICPHISOPTION,             /* 104 ֪ͨNP OSICP�Զ�Э��ѡ�� */

    PPI_PPP_GET_LCPGOTOPTION,       /* 105 ��ȡ����LCPЭ��ѡ�� */
    PPI_PPP_GET_LCPHISOPTION,       /* 106 ��ȡ�Զ�LCPЭ��ѡ�� */
    PPI_PPP_GET_IPCPGOTOPTION,      /* 107 ��ȡIPCP����Э��ѡ�� */
    PPI_PPP_GET_IPCPHISOPTION,      /* 108 ��ȡIPCP�Զ�Э��ѡ�� */
    PPI_PPP_GET_OSICPGOTOPTION,     /* 109 ��ȡOSICP����Э��ѡ�� */
    PPI_PPP_GET_OSICPHISOPTION,     /* 110 ��ȡOSICP�Զ�Э��ѡ�� */

    PPI_IP6_SENDPKT,                /* 111 ����IPv6����*/

    /* PPPOE��Ϣ���� */
    PPI_PPPOE_SESSION_CREATED,      /* 112 ֪ͨNP����PPPOE�Ự */
    PPI_PPPOE_SESSION_DELETED,      /* 113 ֪ͨNPɾ��PPPOE�Ự */
    PPI_PPPOE_SESSION_UPDATED,      /* 114 ֪ͨNP����PPPOE�Ự��Ϣ */
    PPI_PPPOE_SESSION_GETINFO,      /* 115 ��NP��ȡPPPOE�Ự��Ϣ */
    PPI_PPPOE_SESSION_RESTORED,     /* 116 ֪ͨNP PPPOE�Ự�ָ�����ɹ� */
    PPI_PPPOE_SESSION_RESTORED_FIN, /* 117 ֪ͨNP����PPPOE�Ự�ָ�������� */
    PPI_PPPOE_SESSION_SMOOTHED,     /* 118 ֪ͨNP PPPOE�Ựƽ������ɹ� */
    PPI_PPPOE_SESSION_SMOOTHED_FIN, /* 119 ֪ͨNP����PPPOE�Ựƽ��������� */
    PPI_OAM1AG_SETDETECTTIMER,      /* 120 ֪ͨNP CCM Loss���ʱ��ֵ*/
    PPI_TRUNK_IS_PHYUP,             /* 121 TRUNK PHY UP */
    PPI_TRUNK_IS_PHYDOWN,           /* 122 TRUNK PHY DOWN */
    PPI_MAP_ADD,                           /* 123 MAP ADD*/
    PPI_MAP_DEL,                           /* 124 MAP DEL*/

    /*  Add for ������, by mengzechao176865, at 2011-02-23.
        �޸�ԭ��: ��VLAN���ӽӿڶ�Ӧ��ϵ�·���tran */
    PPI_IF_SUBIF_JOIN_VLAN,         /* 125 ���ӽӿڼ���VLAN֪ͨtran */
    PPI_IF_SUBIF_LEAVE_VLAN,        /* 126 ���ӽӿ��뿪VLAN֪ͨtran */

    /* Add by zhaoyue00171897, at 2011-08-17. �޸�ԭ��: ֧�ֻ�ȡ��̬FDB���� */
    PPI_DYNAMIC_FDB_GET,            /* 127 ��NP��ȡ��̬FDB���� */

    /* Add for V2R3C06, by shuxie liu00176784, at 2011-10-04. �޸�ԭ��:  ֧��EOAMЭ��汾ȫ������  */
    PPI_OAM1AG_SETGLBVERSION,     /* 128 EOAMЭ��ȫ�ְ汾���� */

    PPI_OAMY1731_ENABLEDLM,        /* 129 ʹ��˫��֡��ʧ��� */
    PPI_OAMY1731_DISABLEDLM,       /* 130 ȥʹ��˫��֡��ʧ��� */
    PPI_OAMY1731_ENABLESLM,        /* 131 ʹ�ܵ���֡��ʧ��� */
    PPI_OAMY1731_DISABLESLM,       /* 132 ȥʹ�ܵ���֡��ʧ��� */
    PPI_OAMY1731_ENABLEDDM,        /* 133 ʹ��˫����ʱ��� */
    PPI_OAMY1731_DISABLEDDM,       /* 134 ȥʹ��˫����ʱ��� */

    /* Add for VISPV2R3C05STACK-127, by zhaoyue00171897, at 2012-02-03. �޸�ԭ��: ����ʹ��/ȥʹ��3AHʱNP�·� */
    PPI_3AH_ENABLE,                /* 135 ʹ��3AH���� */
    PPI_3AH_DISABLE,               /* 136 ȥʹ��3AH���� */

    PPI_ADD_LINK,                  /*137 TRUNK�·�ADD����*/
    PPI_DEL_LINK,                  /*138 TRUNK�·�DEL����*/
    PPI_UPDATE_LINK,               /*139 TRUNK�·�UPDATE����*/
    /* Add end */

    /*Added by limin00188004, ֧��ȫ�ֺ�VRF��Ŀ���License, 2012/9/26   ���ⵥ��:S.VRF.02.01 */
    PPI_VRF_GLOBAL_LICENCE,        /*140 VRF licence����ʹ��/ȥʹ��������*/
    PPI_VRF_SINGLE_LICENCE,        /*141 ĳ��VRF��licence����*/
    /* End of Added by limin00188004, 2012/9/26   ���ⵥ��:S.VRF.02.01 */
    PPI_OAM1AG_START_RMEP_DETECT,  /*142  ֪ͨ�ײ�����RMEP��̽��*/
    PPI_OAM1AG_STOP_RMEP_DETECT,   /*143  ֪ͨ�ײ�ֹͣRMEP��̽��*/

    /* Added by chandra 00902193 at 2013-09-10 */
    PPI_POLICYRT_ADD_POLICY,   /* 144 Add policy group */
    PPI_POLICYRT_DEL_POLICY,   /* 145 Delete policy group */
    PPI_POLICYRT_ADD_NODE,     /* 146 Add policy node entry */
    PPI_POLICYRT_UPDATE_NODE, /*147  Update policy node entry */
    PPI_POLICYRT_DEL_NODE,  /* 148 Delete policy node entry */
    PPI_POLICYRT_GET_NODE_COUNT, /*149 Get the hit count from TRAN*/
    /* End of  Added by chandra 00902193 at 2013-09-10 */
    PPI_TUNNEL_PARA_CONFIG,        /* 150 tunnel�ӿڲ�������*/
    PPI_OPR_END
};
/*PPI��������,�޸Ĵ˽ṹ�����޸Ķ�Ӧ��TCPIP_PPI_OprType_En[]�ṹ,��common/dataplanĿ¼�¶�Ӧ�ĸýӿڵĿ���*/

/* L2IF FDB�·���ֵ���� */
typedef enum tagPPI_L2IF_FDB_KEY_MODE
{
    PPI_FDB_KEY_INVALID = 0,                   /* ��Чģʽ */
    PPI_FDB_KEY_BY_VLAN,                     /* ����VLAN��ģʽ */
    PPI_FDB_KEY_BY_PORT,                     /* ����PORT��ģʽ */
    PPI_FDB_KEY_BY_DYNAMIC,
    PPI_FDB_KEY_BY_PORT_VLAN,            /* ����PORT+VLAN��ģʽ */
    PPI_FDB_KEY_BY_VLAN_MAC,            /* ����VLAN+MAC��ģʽ */
    PPI_FDB_KEY_BY_STATIC,
    PPI_FDB_KEY_BY_BLACKHOLE,
    PPI_FDB_KEY_MODE_MAX,
}PPI_L2IF_FDB_KEY_MODE_E;

/* multicast mac type*/
typedef enum tagPPI_MULTIMAC_TYPE
{
    PPI_MAC_TYPE_UNICAST = 0,   /* ����MAC���� */
    PPI_MAC_TYPE_MULTICAST,     /* �ಥMAC���� */
    PPI_MAC_TYPE_MAX,
}PPI_MULTIMAC_TYPE_E;

/*�·�PPI��Ϣ����*/
/* �޸ĸ�ö����ͬ������TCPIP_PPI_MsgType_En �� TCPIP_NPUpdate_En*/
enum tagPPIMsgType
{
    PPI_TYPE_ARPMSG,
    PPI_TYPE_IFNETMSG,
    PPI_TYPE_PKTOUT,
    PPI_TYPE_PPPMSG,
    PPI_TYPE_RTMSG,
    PPI_TYPE_TRUNKPORTMSG,
    PPI_TYPE_OSIPKTOUTMSG,
    PPI_TYPE_OAM3AH,
    PPI_TYPE_OAM1AG,
    PPI_TYPE_IGMPMSG,
    PPI_TYPE_L2IFVLANMSG,
    PPI_TYPE_L2IFPORTMSG,
    PPI_TYPE_L2IFMACMSG,
    PPI_TYPE_L2IFQINQMSG,
    PPI_TYPE_VRRPMSG,
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05 */
    PPI_TYPE_VRF,
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    PPI_TYPE_CTRLMSG,
    PPI_TYPE_TRUNKBIND,
    PPI_TYPE_AM4,
    PPI_TYPE_IP6PKTOUT,
    PPI_TYPE_RT6MSG,
    PPI_TYPE_PPPOE,
    PPI_TYPE_MAP,
    PPI_TYPE_TRUNKUPDATE,
    PPI_TYPE_POLICYRTUPDATE,  /*CHANDRA */
    PPI_TYPE_VRF6,    /*Added by apurba for VRF6*/

    PPI_TYPE_END
};

/*����ϵͳ���ú���TCPIP_PPI_HookRegisterByType����ע��ʱ��Ҫע��ĺ�����ģ���*/
/*��TCPIP_PPI_HOOK_S�ṹ����һ��˳��*/
enum tagPPIUpdateModuleType
{
    PPI_HOOKTYPE_FIB4,           /*·�ɸ���֪ͨģ��� */
    PPI_HOOKTYPE_ARP,            /*ARP����֪ͨģ��� */
    PPI_HOOKTYPE_IFNET,          /*�ӿڴ���/ɾ��/����/״̬����֪ͨģ��� */
    PPI_HOOKTYPE_PPP,            /*PPP��������֪ͨģ��� */
    PPI_HOOKTYPE_IP4,            /*NP���Ĵ���ģ��� */
    PPI_HOOKTYPE_TRUNKPORT,      /* Trunk Port NP�·�����ģ��� */
    PPI_HOOKTYPE_OSI,            /*OSI NP���ķ��ʹ�����ģ��� */
    PPI_HOOKTYPE_3AH,            /* 3ah NP �·�����ģ��� */
    PPI_HOOKTYPE_1AG,            /*  1AG ����NP�·�ģ��� */
    PPI_HOOKTYPE_IGMP,           /*IGMP�·�NP֪ͨģ���*/
    PPI_HOOKTYPE_MAP,            /* �·�MAP����ģ��� */
    PPI_HOOKTYPE_FIB6,           /* �·�FIB6·����Ϣģ��� */
    PPI_HOOKTYPE_VLAN,           /* L2IF VLAN������Ϣ֪ͨģ��� */
    PPI_HOOKTYPE_PORT,           /* L2IF PORT������Ϣ֪ͨģ��� */
    PPI_HOOKTYPE_MAC,            /* L2IF MAC������Ϣ֪ͨģ��� */
    PPI_HOOKTYPE_QINQ,           /* L2IF QINQ������Ϣ֪ͨģ��� */
    PPI_HOOKTYPE_VRRP,           /* VRRP PPI��Ϣ֪ͨ,����ʹ��VRRP������MAC��Ϣģ��� */
    PPI_HOOKTYPE_VRF,            /* �ӿڰ�/ȥ��VRF PPI�·�ģ��� */
    PPI_HOOKTYPE_CTRL,           /*�ಥMAC������Ϣģ���*/
    PPI_HOOKTYPE_TRUNKBIND,      /*TRUNK��PPI��Ϣ�·�ģ���*/
    PPI_HOOKTYPE_AM4,            /*AM4 ��ַ����PPI��Ϣ�·�ģ���*/
    PPI_HOOKTYPE_MPLSFW,         /*�������PPI���Ӻ���ģ���*/
    PPI_HOOKTYPE_IP6,            /*IPv6���ķ���PPI���Ӻ���ģ���*/
    PPI_HOOKTYPE_PPPOE,          /*�·�֪ͨNP PPPOE�Ự�������Ϣģ���*/
    PPI_HOOKTYPE_POLICYRT,    /* Hook type for policyrt -- CHANDRA */

    PPI_HOOKTYPE_END

};

/*PPI�����ķ���ֵ*/
enum tagPPIRetValue
{
    PPI_OK,
    PPI_ERR,

    PPI_PACKET_PROCESSED,       /*�����ѱ�����*/
    PPI_PACKET_NOT_PROCESSED,   /*PPI�ӿ�û�д�����*/
    PPI_RET_END
};

/*Э������*/
enum tagPPINetProto
{
    PPI_NETPROTO_LCP = 0,
    PPI_NETPROTO_IP,
    PPI_NETPROTO_IPv6,
    PPI_NETPROTO_MUXCP,
    PPI_NETPROTO_LACP,
    PPI_NETPROTO_OSICP,
    PPI_NETPROTO_END
};

/*������*/
enum tagPUBLICRetCode
{
    OVER_UPPER_LIMIT = VOS_ERR + 1,     /*2,�û�����ֵ��������1024*/
    PUBLIC_HA_IS_SMOOTHING,             /*3,HA����ƽ����������ֶ�����������*/
    DONOT_ENABLE_CACHEDPKT,             /*4,û��ʹ�ܱ��Ļ��湦��*/
    INPUT_NULL_POINTER,                 /*5,�����ָ��*/
    INPUT_OVER_MAX_SCOPE,               /*6,���볬������ķ�Χ*/
    LINK_HOOK_API_NULL_POINTER,         /*7,�����ָ��*/
    LINK_HOOK_API_TYPE_WRONG,           /*8,�������Ͳ�������*/
    LINK_HOOK_API_MEM_FAIL,             /*9,�����ڴ�ʧ��*/
    LINK_HOOK_API_HOOK_SAME,            /*10,ע�ắ��ָ����ԭ�е���ͬ*/
    PUBLIC_ERR_MBUF_NULL,               /*11,����Ϊ��*/
    PUBLIC_ERR_IF_NULL,                 /*12,�ӿڲ�����*/
    PUBLIC_ERR_QUEUE_ID,                /*13,���Ķ���ID�Ƿ�*/
    PUBLIC_ERR_ENQUEUE_FULL,            /*14,���������ʱ��������*/
    PUBLIC_ERR_ENQUEUE_SPLIMP,          /*15,���������ʱ���ж�ʧ��*/
    PUBLIC_ERR_ENQUEUE_SPLX,            /*16,���������ʱ���ж�ʧ��*/
    PUBLIC_ERR_HEALTH_PARAWRONG,        /*17,Healthģ������Ƿ�*/
    PUBLIC_ERR_HEALTH_SETFLAG,          /*18,Healthģ�鿪�ز�������*/
    PUBLIC_HEALTH_SMB,                  /*19,��ǰΪ���岻�������*/
    PUBLIC_ERR_LASTWORD_PARAWRONG,      /*20,��������ģ������Ƿ�*/
    PUBLIC_ERR_LASTWORD_MALLOCFAIL,     /*21,�������������ڴ�ʧ��*/
    PUBLIC_ERR_LASTWORD_NOREG,          /*22,���������������δע��*/
    PUBLIC_ERR_LASTWORD_CHECKUPFAIL,    /*23,�������Դ���ʧ��*/
    PUBLIC_ERR_HDRTASKNOINIT,           /*24,HDR����δ��ʼ��*/
    PUBLIC_ERR_HDRGETCOMPVTBLFAIL,      /*25,HDR�����ȡ������ʧ��*/
    PUBLIC_ERR_HDRCREATETIMERQUEFAIL,   /*26,HDR���񴴽���ʱ������ʧ��*/
    PUBLIC_ERR_HDRCREATEHELQUEFAIL,     /*27,HDR���񴴽���챨�����ʧ��*/
    PUBLIC_ERR_HDRCREATEINFOQUEFAIL,    /*28,HDR���񴴽���־��Ϣ����ʧ��*/
    PUBLIC_ERR_HDRCREATETASKFAIL,       /*29,HDR���񴴽�ʧ��*/
    PUBLIC_ERR_HDRCREATCCQUEFAIL,       /*30,HDR CC���д���ʧ��*/
    PUBLIC_ERR_HDR_PARAWRONG,           /*31,HDR��������*/
    PUBLIC_ERR_COMPRESS_PARAWRONG,      /*32,����ѹ����������*/
    PUBLIC_ERR_COMPRESS_FAILED,         /*33,����ѹ��ʧ��*/
    PUBLIC_ERR_PARA_ERR,                /*34,��������*/
    PUBLIC_ERR_CHECKBYHOOK,             /*35,ͨ�����Ӻ��������ͷ�CPU�ж�*/
    PUBLIC_ERR_TASKMONITOR_EXIST,       /*36,�̼߳��ӹ��Ӻ����Ѿ�����*/
    PUBLIC_ERR_VISP_NOT_INIT,           /*37,Э��ջ��û�г�ʼ��*/
};

enum  enTcpIpEntryErrorCode
{
    TCPIP_ENTRY_OK = 0,
    TCPIP_ENTRY_ERR,
    TCPIP_ENTRY_NO_PRE_VALUE,           /* 2  û�ж�Ӧ��Ԥ������ */
    TCPIP_ENTRY_NO_PAF_VALUE,           /* 3  û�ж�Ӧ��PAFԤ������ */
    TCPIP_ENTRY_INPUT_PARA_NULL,        /* 4  �������ΪNULL */
    TCPIP_ENTRY_INPUT_VALUE_INVALID,    /* 5  �������ֵ���Ϸ� */
};

enum  enTcpIpHAErrorCode
{
    TCPIP_HA_OK = 0,
    TCPIP_HA_ERR,
    TCPIP_HA_BATCH_IS_NOT_OVER,             /*2  ������û�����*/
    TCPIP_HA_WRITE_QUEUE_FAIL,              /*3  д��Ϣ����ʧ��*/
    TCPIP_HA_IS_SMOOTHING,                  /*4  HAû�г�ʼ�����ߴ���ƽ��״̬*/
    TCPIP_HA_SET_IFNET_IP_SOCKET_DBG_ERR,   /*5  ����IFNET��IP��SOCKET���Կ���ʧ��*/
    TCPIP_HA_SET_ETHARP_DBG_ERR,            /*6  ����ETHARP��HA���Կ���ʧ��*/
    TCPIP_HA_SET_TRUNK_DBG_ERR,             /*7  ����TRUNK��HA���Կ���ʧ��*/
    TCPIP_HA_SET_PPP_DBG_ERR,               /*8  ����PPP��HA���Կ���ʧ��*/
    TCPIP_HA_SET_POEC_DBG_ERR,              /*9  ����PPPE CLIENT ��HA���Կ���ʧ��*/
    TCPIP_HA_SET_POES_DBG_ERR,              /*10 ����PPPOE Server��HA���Կ���ʧ��*/
    TCPIP_HA_SET_DHCP4C_DBG_ERR,            /*11 ����DHCP4C��HA���Կ���ʧ��*/
    TCPIP_HA_SET_SFIB_DBG_ERR,              /*12 ����SFIB��HA���Կ���ʧ��*/
    TCPIP_HA_SET_BFD_DBG_ERR,               /*13 ����BFD��HA���Կ���ʧ��*/
    TCPIP_HA_SET_DHCP4R_DBG_ERR,            /*14 ����DHCP4R��HA���Կ���ʧ��*/
    TCPIP_HA_GET_IFNET_IP_SOCKET_DBG_ERR,   /*15 ��ȡIFNET��IP��SOCKET���Կ���ʧ��*/
    TCPIP_HA_GET_ETHARP_DBG_ERR,            /*16 ��ȡETHARP��HA���Կ���ʧ��*/
    TCPIP_HA_GET_TRUNK_DBG_ERR,             /*17 ��ȡTRUNK��HA���Կ���ʧ��*/
    TCPIP_HA_GET_PPP_DBG_ERR,               /*18 ��ȡPPP��HA���Կ���ʧ��*/
    TCPIP_HA_GET_POEC_DBG_ERR,              /*19 ��ȡPPPE CLIENT ��HA���Կ���ʧ��*/
    TCPIP_HA_GET_POES_DBG_ERR,              /*20 ��ȡPPPOE Server��HA���Կ���ʧ��*/
    TCPIP_HA_GET_DHCP4C_DBG_ERR,            /*21 ��ȡDHCP4C��HA���Կ���ʧ��*/
    TCPIP_HA_GET_SFIB_DBG_ERR,              /*22 ��ȡSFIB��HA���Կ���ʧ��*/
    TCPIP_HA_GET_DHCP4R_DBG_ERR,            /*23 ��ȡDHCP4R��HA���Կ���ʧ��*/
    TCPIP_HA_GET_PUBLIC_DBG_ERR,            /*24 ��ȡpublic��HA���Կ���ʧ��*/

    TCPIP_HA_REGISTER_TOO_MUCH_ERR,         /*25 �ⲿע��HAģ�鳬���ֵ*/
    TCPIP_HA_NAME_TO_LONG_ERR,              /*26 �ⲿע��HAģ�����ֹ���*/
    TCPIP_HA_REGISTER_LAYER_ERR,            /*27 �ⲿע��HAģ���δ���*/
    TCPIP_HA_MODULE_ID_ERR,                 /*28 �ⲿע��HAģ������ID��Χ����*/
    TCPIP_HA_CALL_BACK_NULL_ERR,            /*29 �ⲿע��HAģ������ص���������*/
    TCPIP_HA_CALL_HA_FUN_NULL_ERR,          /*30 �ⲿע��HAģ��Ĺ��ܺ���Ϊ��*/
    TCPIP_VOS_MALLOC_FAILED_1,              /*31 �ⲿע��HAģ�������ڴ�ʧ��*/
    TCPIP_VOS_MALLOC_FAILED_2,              /*32 �ⲿע��HAģ�������ڴ�ʧ��*/
    TCPIP_HA_MALLOC_FAILED_1,               /*33 TCPIP_HA_MALLOC�����ڴ�ʧ�� */
    TCPIP_HA_MALLOC_FAILED_2,               /*34 TCPIP_HA_MALLOC�����ڴ�ʧ�� */
    TCPIP_HA_WRITE_QUEUE_FAIL_1,            /*35 д��Ϣ����ʧ��  */
    TCPIP_HA_WRITE_QUEUE_FAIL_2,            /*36 д��Ϣ����ʧ��  */
    TCPIP_HA_EXIST_MODULE,                  /*37 ģ���ظ�ע�� */
    TCPIP_HA_SET_OAM3AH_DBG_ERR,            /*38 ����OAM3AHģ����Կ���ʧ��     */
    TCPIP_HA_GET_OAM3AH_DBG_ERR,            /*39 ��ȡOAM3AHģ����Կ���ʧ��     */
    TCPIP_HA_SET_OAM1AG_DBG_ERR,            /*40 ����oam1ag��HA���Կ���ʧ��*/
    TCPIP_HA_GET_OAM1AG_DBG_ERR,            /*41 ��ȡoam1ag��HA���Կ���ʧ��*/
    TCPIP_HA_GET_IGMP_DBG_ERR,              /*42 ��ȡigmp��ha���Կ���ʧ��*/

    TCPIP_HA_IF_BATCH_BACKUP_FAIL,          /*43 ��������IFNETģ��ʧ�� */
    TCPIP_HA_IP_BATCH_BACKUP_FAIL,          /*44 ��������IPģ��ʧ�� */
    TCPIP_HA_ETH_BATCH_BACKUP_FAIL,         /*45 ��������ETHģ��ʧ�� */
    TCPIP_HA_TRUNK_BATCH_BACKUP_FAIL,       /*46 ��������TRUNKģ��ʧ�� */
    TCPIP_HA_PPP_BATCH_BACKUP_FAIL,         /*47 ��������PPPģ��ʧ�� */
    TCPIP_HA_POES_BATCH_BACKUP_FAIL,        /*48 ��������POESģ��ʧ�� */
    TCPIP_HA_POEC_BATCH_BACKUP_FAIL,        /*49 ��������POECģ��ʧ�� */
    TCPIP_HA_LINKLAYER_BATCH_BACKUP_FAIL,   /*50 ���������ⲿģ����·��ʧ�� */
    TCPIP_HA_DHCP4C_BATCH_BACKUP_FAIL,      /*51 ��������DHCP4Cģ��ʧ�� */
    TCPIP_HA_DHCP4R_BATCH_BACKUP_FAIL,      /*52 ��������DHCP4Rģ��ʧ�� */
    TCPIP_HA_SFIB4_BATCH_BACKUP_FAIL,       /*53 ��������SFIB4ģ��ʧ�� */
    TCPIP_HA_IPLAYER_BATCH_BACKUP_FAIL,     /*54 ���������ⲿģ�������ʧ�� */
    TCPIP_HA_SOCK_BATCH_BACKUP_FAIL,        /*55 ��������SOCKģ��ʧ�� */
    TCPIP_HA_BFD_BATCH_BACKUP_FAIL,         /*56 ��������BFDģ��ʧ�� */
    TCPIP_HA_APPLAYER_BATCH_BACKUP_FAIL,    /*57 ���������ⲿģ��Ӧ�ò�ʧ�� */
    TCPIP_HA_PUBLIC_BATCH_BACKUP_FAIL,      /*58 ��������PUBLICģ��ʧ�� */
    TCPIP_HA_OAM3AH_BATCH_BACKUP_FAIL,      /*59 ��������OAM3AHģ��ʧ�� */
    TCPIP_HA_OAM1AG_BATCH_BACKUP_FAIL,      /*60 ��������OAM1AGģ��ʧ�� */
    TCPIP_HA_IGMP_BATCH_BACKUP_FAIL,        /*61 ��������IGMPģ��ʧ�� */
    TCPIP_HA_VRF_BATCH_BACKUP_FAIL,         /*62 ��������VRFģ��ʧ�� */
    TCPIP_HA_SET_VRF_DBG_ERR,               /*63 ����VRF��HA���Կ���ʧ��*/
    TCPIP_HA_GET_VRF_DBG_ERR,               /*64 ��ȡVRF��HA���Կ���ʧ��*/
    TCPIP_HA_NOT_INIT,                      /*65 HAδ��ʼ�� */
    TCPIP_HA_EVENT_INVALID,                 /*66 HA�¼����Ͳ��Ϸ� */
    TCPIP_HA_NOT_MASTER,                    /*67 ���岻������ */
    TCPIP_HA_ERROR_SETTIME,                 /*68 HA ��̬�������ô���*/
    TCPIP_HA_ERROR_SWITCH,                  /*69 HA��ʱѡ�񿪹����ô���*/
    TCPIP_HA_TWAMP_BATCH_BACKUP_FAIL,  /*70 Batch backup for TWAMP Module is failed*/
};

typedef enum enTcpIpDbgErrorCode
{
    TCPIP_DBG_OK = 0,
    TCPIP_DBG_ERR,
    TCPIP_DBG_TCP4,
    TCPIP_DBG_UDP4,
    TCPIP_DBG_ICMP4,
    TCPIP_DBG_PP4,
    TCPIP_DBG_ETHARP,
    TCPIP_DBG_PPP,
    TCPIP_DBG_ERR_CMD,/*����������� */
    TCPIP_DBG_ERR_MID, /*�����ģ��ID��*/
    TCPIP_DBG_ERR_DBG_LEVEL /*�����DBG�ȼ�*/
}TCPIP_DEBUG_ERR_CODE_E;

/*����Debug����*/
typedef enum TCPIP_DEBUG_LEVEL_Etag
{
    ERR_LEVEL_TEST = 1,
    ERR_LEVEL_INFO,
    ERR_LEVEL_WARNING,
    ERR_LEVEL_ERROR,
    ERR_LEVEL_END
}TCPIP_DEBUG_LEVEL_E;

/*������־������ȼ�*/
typedef enum TCPIP_LOG_LEVEL_Etag
{
    TCPIP_LOG_LEVEL_CRITICAL = 0,
    TCPIP_LOG_LEVEL_ERROR,
    TCPIP_LOG_LEVEL_WARNING,
    TCPIP_LOG_LEVEL_INFO,
    TCPIP_LOG_LEVEL_DEBUG,
    TCPIP_LOG_LEVEL_END
}TCPIP_LOG_LEVEL_E;

/*����Debug��ģ����Ϣ*/
typedef enum TCPIP_DEBUG_MID_INFO_Etag
{
    DEBUG_SOCKET = 1,
    DEBUG_TCP4,
    DEBUG_UDP4,
    DEBUG_ICMP4,
    DEBUG_PP4,
    DEBUG_ETHARP,
    DEBUG_PPP,
    DEBUG_ATTACK,
    DEBUG_RIP4,
    DEBUG_ALL
}TCPIP_DEBUG_MID_INFO_E;

/*������еı������*/
/*��ע�⡿ÿ����һ������ʱ����Ӧ����TCPIP_RESLIMIT_MSG_EN���������Ӧ���ж�������Ϣ */
enum enumQueID
{
    RESERVE    = 0,
    QUE_LINK_LAYER,
    QUE_ARP,
    QUE_PPP_NEGO,
    QUE_PPP_ASY,
    QUE_PPP_STAC,
    QUE_PPP_MP,
    QUE_IP_INPUT ,
    QUE_IPV6_INPUT,
    QUE_PPPOE_CLIENT_INPUT,

    QUE_LACP,         /* LACP���Ķ��� */
    QUE_POES,         /* PPPoE Server���Ķ��� */
    QUE_ISIS_INPUT,   /* ISIS���Ķ��� */
    QUE_INARP,

    QUE_MAX_NUMBER

};

/* �����Ż�����/���������� */
enum tagOPTEntryType
{
    OPTIM_ENTRY_RCVTYPE = 1,
    OPTIM_ENTRY_FWDTYPE,
    OPTIM_ENTRY_SNDTYPE,
};

/* �����HAע���ö��ֵ */
typedef enum enumHALAYERMID
{
    HA_LINK_LAYER = 0,
    HA_IP_LAYER = 1,
    HA_APP_LAYER = 2,
    HA_MID_LAYER_MAX = 3,
}HALAYERMID_E;

/* ������ⲿģ���ģ��ID��Χ�� (127, 255) */
typedef enum enumHAMIDExtend
{
    HA_EXTERN_MID_MIN = 127,
    HA_MID_IPOA,                /* IPOA HA */
    HA_EXTERN_MID_MAX = 255,
}HAMIDEXTEND_E;

/* HA�ص������ṹ���� */
typedef struct tagTCPIP_HA_CALLBACK
{
    /* HA��������ɻص�֪ͨ���� */
    ULONG (*pfHA_BATCH_HOOK_FUNC)(VOID);

    /* HAƽ����ɻص�֪ͨ���� */
    ULONG (*pfHA_SMOOTH_HOOK_FUNC)(VOID);

    /* HA�ֶ�������ɻص�֪ͨ���� */
    ULONG (*pfHA_NOTIFYSWITCH_HOOK_FUNC)(VOID);
} TCPIP_HA_CALLBACK_S ;

/* ע��HAģ��Ĺ��Ӻ������� */
typedef struct tagTCPIP_HA_MODULE_CALLBACK
{
    /* HA�����ݻص�֪ͨ���� */
    ULONG (*pfHA_BATCH_HOOK_FUNC)(VOID);

    /* HAƽ���ص�֪ͨ���� */
    ULONG (*pfHA_SMOOTH_HOOK_FUNC)(VOID);

    /*�������HA���Ľӿ�*/
    ULONG (*pfHA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);

    /* HA�ֶ�������ɻص�֪ͨ���� */
    ULONG (*pfHA_NOTIFYSWITCH_HOOK_FUNC)(VOID);

    ULONG (*pfHA_Clean)(VOID);/*���ģ����Ϣ�ĺ����ӿ�*/

} TCPIP_HA_MODULE_CALLBACK_S;

/* HA ͳ����Ϣ���� */
typedef struct tagHASTAT
{
    ULONG   ulIPackets;     /* ���ձ�����Ϣ������ */
    ULONG   ulOPackets;     /* ���ͱ�����Ϣ������ */
    ULONG   ulIBytes;       /* ���ձ�����Ϣ�ֽ���,����HA�ײ����� */
    ULONG   ulOBytes;       /* ���ͱ�����Ϣ�ֽ���,����HA�ײ����� */
    ULONG   ulErrPacket;    /* ������Ϣ������(�������ĳ��Ⱥ�ͨ�����ͱ��ĳ��Ȳ�һ�¡����������г����ֶ�Ϊ0) */
    ULONG   ulBadCheckSum;  /* У��ʹ�����Ϣ������ */
    ULONG   ulBadVersion;   /* ����汾��Ϣ������ */
    ULONG   ulHARcvSeq;     /* ������յı�����Ϣ��� */
    ULONG   ulHADropSeq;    /* �����ʧ�ı�����Ϣ��� */
    ULONG   ulHADropNum;    /* ����������� */
    ULONG   ulHADropSum;    /* �����ܸ��� */
    ULONG   ulHADisorder;   /* ������ͳ�Ƹ��� */
    ULONG   ulSendFailSum;  /* ���ͱ���ʧ�ܸ��� */
    ULONG   ulCreateIntfSum;/* ���崴���ӿ�ʧ�� */
    ULONG   ulNoIntfSum;    /* ����û�нӿڵ��±�����Ϣ��Ч���� */
    ULONG   ulNoTypeSum;    /* ��ʶ����ͳ����Ϣ */
    ULONG   ulNullPkt;      /*�ձ���ͳ����Ϣ*/
}HASTAT_S;

typedef struct tagHADBG_S
{
#ifndef SOCK_HA_MAX_DEBUG
#define SOCK_HA_MAX_DEBUG 5
#endif
    ULONG  ulEthDbg;            /* ��̫���ݵ��Կ���״̬ */
    ULONG  ulPppDbg;            /* PPP���ݵ��Կ���״̬ */
    ULONG  ulPoecDbg;           /* Poec���ݵ��Կ���״̬ */
    ULONG  ulIfnetDbg;          /* IFNET���ݵ��Կ���״̬ */
    ULONG  ulTrunkDbg;          /* TRUNK���ݵ��Կ���״̬ */
    ULONG  ulIpDbg;             /* IP���ݵ��Կ���״̬ */
    ULONG  ulSfibDbg;           /* SFIB���ݵ��Կ���״̬ */
    ULONG  ulBfdDbg;            /* BFD���ݵ��Կ���״̬ */
    ULONG  ulDhcpDbg;           /* DHCP���ݵ��Կ���״̬ */
    ULONG  ulDhcp4rDbg;         /* DHCP Relay���ݵ��Կ���״̬ */
    ULONG  aulSockHaDebug[SOCK_HA_MAX_DEBUG]; /* SOCKET���ݵ��Կ���״̬ */
    ULONG  ulPoesDbg;           /* Poes debug switch */
    ULONG  ulPubDbg;            /* Public debug switch */
    ULONG  ulOam3ahDbg;         /* 3AHģ�鱸�ݵ��Կ��� */
    ULONG  ulOam1agDbg;         /* 1AGģ�鱸�ݵ��Կ���*/
    ULONG  ulIgmpDbg;           /* igmp debug switch*/
    ULONG  ulVrfDbg;            /* Vrf debug switch*/
}HADBG_S;

/*·��PPI�ṹ*/
typedef struct tagPPI_RTMSG4
{
    ULONG    ulDestination;       /*Ŀ�ĵ�ַ*/
    ULONG    ulNexthop;           /*��һ��*/
    ULONG    ulLocalAddress;      /*���س��ӿڵ�ַ*/
    ULONG    ulIfIndex;           /*���ӿ�IFNET����*/
    ULONG    ulATIndex;           /*virtual link index*/
    ULONG    ulSlot;              /*·�ɵĲۺţ��ݲ�ʹ��*/
    ULONG    ulFlags;             /*·�ɱ��*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG    ulVrfIndex;          /*�ӿ�����VRF����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    ucDestPrefixLength;  /*Ŀ�ĵ�ַ���볤��*/
    UCHAR    ucLocalPrefixLength; /*���س��ӿڵ�ַ���볤��*/
    USHORT   usRTPri;             /*·�����ȼ�*/
    UCHAR    ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1]; /* �ӿ��� */
    /* Begin: a00900892, 30-01-2014, Path mtu for the route */
    ULONG ulPmtu;
    /* End: a00900892, 30-01-2014, Path mtu for the route */
}PPI_RTMSG4_S;

/*ARP PPI�ṹ*/
typedef struct tagPPI_ARP
{
    ULONG   ulFlags;           /*resolved or resolving����̬���Ƕ�̬*/
    ULONG   ulRtIfIndex;       /*�ӿ�����*/
    ULONG   ulRtIpAddr;        /*��ַ�������ֽ���*/
    ULONG   ulVlinkIndex;      /*VLINK index*/
    ULONG   ulVlanFlag ;       /*�ݲ�ʹ��*/
    ULONG   ulVlanId;          /*�ݲ�ʹ��*/
    UCHAR   ucMacAddr[6];      /*physical��ַ*/
    UCHAR   ucSourceType;      /*��̬ARP����Դ:��ѧϰ���û����á����ú����ѧϰ����*/
    UCHAR   ucReserved;
    ULONG   ulPortIfIndex;     /*����˿�����*/
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
    ULONG    ulVrfIndex;
    /* End: VISP1.7C03 VRF wangchengyang , 2009-01-09 */

    /*arp Mccp support V300R001C00 --  start*/
    ULONG ulRemainExpireTime;         /*Remaining Expiry Time*/
    /*arp Mccp support V300R001C00 --  start*/

}PPI_ARP_S;

typedef struct tagPPI_MAP
{
    UCHAR   ucType;             /* MAP����: IP/InARP/Default */
    UCHAR   ucPadding[3];
    ULONG   ulRtIfIndex;        /* �ӿ����� */
    ULONG   ulIPAddr;           /* ��ַ */
    ULONG   ulVLinkIndex;       /* virtual link index */
    USHORT  usVPI;              /* VPI */
    USHORT  usVCI;              /* VCI */
    ULONG   ulVccIndex;         /* Vcc Index */
}PPI_MAP_S;
typedef struct tagPPI_RTMSG6
{
    ULONG    ulDestination[4];       /*Ŀ�ĵ�ַ*/
    ULONG    ulNexthop[4];           /*��һ��*/
    ULONG    ulIfIndex;           /*���ӿ�IFNET����*/
    ULONG    ulATIndex;           /*virtual link index*/
    ULONG    ulSlot;              /*·�ɵĲۺţ��ݲ�ʹ��*/
    ULONG    ulFlags;             /*·�ɱ��*/
    ULONG    ulDestPrefixLength;  /*Ŀ�ĵ�ַ���볤��*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG    ulVrfIndex;          /*�ӿ�����VRF */
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    ucIfName[IF_MAX_INTERFACE_NAME_LEN + 1];   /*�ӿ���*/
    /* Added by hanna55555, VISPV1R8C03, 2009/11/30 */
    ULONG    ulRtPri;             /*·�����ȼ�*/
    /*End of Added by hanna55555, 2009/11/30 */
}PPI_RTMSG6_S;
/* 3ah PPI�·���Ϣ���ݽṹ */
#define LCLRMT_INFOTLV_LEN  32
#define INFOTLV_MAX_LEN     47  /* INFO OAMPDU�����ܳ��Ⱥ�,ʵ��NP�·�tlv������ulTlvPktLenΪ׼ */
#define PPI_3AH_LB_LOCAL    1
#define PPI_3AH_LB_REMOTE   2
typedef struct tagPpi3ah
{
    UCHAR  aucTlvPkt[INFOTLV_MAX_LEN];      /* ����/�Զ�TLV���� + ��֯�Զ���tlv(������)[����end tlv],���ֶζ�Ϊ������ */
    UCHAR  ucTlvPktLen;                     /* ʵ���·���info tlv pkt���� */

    USHORT usFlags;                         /* ���ĵ�FLAG���,������,��ͬ   */
    UCHAR  aucPeerMac[6];                   /* �Զ�physical��ַ                  */
    ULONG  ulDetectInterval;                /* ̽������,msΪ��λ            */
    ULONG  ulLbState;                       /* ���˻���״̬,1-LB_LOCAL/2-LB_REMOTE              */
    ULONG  ulLbTestMode;                    /* ���ز���ģʽ,0��visp�������ģʽ��1��NP����ģʽ  */

    /* ������Ϣ */
    USHORT usLclOamPduCfg;                  /* �������õ�OAMPDU��С     */
    USHORT usLclRevision;                   /* ����Revisionֵ           */

    /* �Զ���Ϣ */
    USHORT usRmtOamPduCfg;                  /* �Զ����õ�OAMPDU��С     */
    USHORT usRmtRevision;                   /* �Զ�Revisionֵ           */
}PPI_3AH_S;

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-04 */
typedef struct tagVRF_PPI_S
{
    ULONG ulVrfIndex;               /* VRF���� */
    ULONG ulIfIndex;                /* �ӿ����� */
    /*Added by limin00188004, ֧��ȫ�ֺ�VRF��Ŀ���License, 2012/9/26   ���ⵥ��:S.VRF.02.01 */
    ULONG ulLicence;                /* Licence��ʶ��0�ǹرգ�1�Ǵ�*/
    /* End of Added by limin00188004, 2012/9/26   ���ⵥ��:S.VRF.02.01 */
}VRF_PPI_S;
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-04 */

/*Added by apurba for VRF6*/
typedef struct tagVRF6_PPI_S
{
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
    ULONG ulLicence;
}VRF6_PPI_S;
/*End of Added by apurba for VRF6*/

/* L2IF FDB PPI�ṹ*/
typedef struct tagPPI_L2IF_FDB_ENTRY
{
    UCHAR aucMacAddr[MACADDRLEN];        /* physical��ַ */
    USHORT usVlanId;             /* physical��ַ����VLAN ID */
    ULONG ulIfIndex;            /* �ӿ����� */
    USHORT usOutCeVlanId;    /*�û���VLAN ID */
    UCHAR ucType;              /* physical��ַ�������� */
    UCHAR usReserved;       /* �����ֶ�*/
}PPI_L2IF_FDB_ENTRY_S;

/* PPI FDB KEY�ṹ����Ҫ����FDB����ɾ������ */
typedef struct tagPPI_L2IF_FDB_KEY
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical��ַ */
    USHORT usVlanId;                     /* VLAN ID */
    ULONG  ulIfIndex;                    /* �ӿ����� */
    ULONG ulTransMode;   /*��ʶstacking������mapping*/
    USHORT usFlag;         /* ���ڶ˿��뿪vlan,�ñ�־λ���ڲ�Ʒ�ж��Ƿ�Ҫ�����·�,
                              ����·��������·����ǰ�ԭ�����̵����·�
                              0:��ԭ�����̵����·�
                              1:�����·�
                              2:�����κδ���*/
    USHORT usStartVlan;    /* ���������·�startvlan*/
    USHORT usEndVlan;      /* ���������·�endvlan*/
    USHORT usPVID;        /* PVID */
    UCHAR  ucFdbFlag;       /* VLAN/QINQ ��־ */
    UCHAR  ucType;                  /* �������� */
    UCHAR  ucKeyMode;        /* ��ֵ���� */
    UCHAR  ucResved;        /* �����ֶ� */
}PPI_L2IF_FDB_KEY_S;

/* VRRP PPI�ṹ �������ɾ����IP */
typedef struct tagPPI_VRRP_UPDATEMAC
{
    ULONG ulVrId;                             /* ������ID */
    ULONG ulVirtualIP;                        /* ��IP(������) */
    UCHAR aucVirtualMacAddr[MACADDRLEN];      /* ��physical��ַ */
    UCHAR ucReserved[2];                      /* �����ֶ� */
}PPI_VRRP_UPDATEMAC_S;

/* VRRP PPI�ṹ ����S***R VLAN����Ƴ�SUB VLANʱ֪ͨSUB VLAN��ɾ����MAC�Ĵ��� */
typedef struct tagPPI_VRRP_VLAN
{
    ULONG ulVrId;                             /* ������ID */
    UCHAR aucVirtualMacAddr[MACADDRLEN];      /* ��physical��ַ */
    UCHAR ucReserved[2];                      /* �����ֶ� */
    ULONG ulIfIndex;
    ULONG ulSuperVlanId;
    ULONG ulSubVlanId;
}PPI_VRRP_VLAN_S;

/* �ಥphysical��ַPPI�ṹ���� */
typedef struct tagPPI_MULTIMAC
{
    ULONG ulIfIndex;
    UCHAR aucMultiMacAddr[MACADDRLEN];  /* �ಥphysical��ַ */
    UCHAR aucMultiMacMask[MACADDRLEN];  /* physical��ַ������*/
}PPI_MULTIMAC_S;


/*TRUNK��PPI��Ϣ�·��ṹ*/
typedef struct tagPPI_TRUNK_BIND
{
    ULONG   ulIfIndex;    /* �ӿ����� */
    ULONG   ulTrunkId;    /* TRUNK�ӿ�ID */
    USHORT  usPri;        /* �󶨶˿����ȼ� */
    USHORT  usReserved;   /* ���� */
}PPI_TRUNK_BIND_S;

/*AM4 ��ַ����PPI��Ϣ�·��ṹ*/
typedef struct tagPPI_IPADDR_INFO
{
    ULONG   ulIfIndex;      /* �ӿ����� */
    ULONG   ulVrfIndex;     /* VRF���� */
    ULONG   ulIpAddr;       /* ��ַ,������ */
    ULONG   ulSubnetMask;   /* ��ַ���� */
    ULONG   ulFlag;         /* ���ӵ�ַ���,1 ��IP���, 2 ��IP��� */
}PPI_IPADDR_INFO_S;

/*TRUNK LACP��·��������PPI��Ϣ�·�*/
typedef struct tagPPI_TRUNK_LACP
{
    ULONG  ulPortIfIndex;                           /* ��Ա�˿ڽӿ����� */
    UCHAR  ucPortMacAddress[MACADDRLEN];            /* TRUNK�ӿ�MAC�������װ��*/
    UCHAR  ucActorExpiredType;                      /* ���˵ķ�������ģʽ0--�����ڣ�1--������*/
    UCHAR  ucPartnerExpiredType;                    /*�Զ˵ķ�������ģʽ0--�����ڣ�1--������*/
    /* ������Ϣ */
    USHORT usActorOperKey;                          /* ���˶˿�����Key */
    USHORT usActorOperPortPri;                      /* ���˶˿��������ȼ� */
    USHORT usActorOperPortIndex;                    /* ���˶˿������˿ں� */
    USHORT usActorOperSysPri;                       /* ����ϵͳ�������ȼ� */
    UCHAR  ucActorOperSysMac[MACADDRLEN];           /* ����ϵͳ����MAC */
    UCHAR  ucActorOperState;                        /* ���˶˿�����״ֵ̬ */
    UCHAR  ucActorReserve;                          /* �����ֶ� */

    /* �Զ���Ϣ */
    USHORT usPartnerOperKey;                        /* �Զ˶˿�����Key */
    USHORT usPartnerOperPortPri;                    /* �Զ˶˿��������ȼ� */
    USHORT usPartnerOperPortIndex;                  /* �Զ˶˿������˿ں� */
    USHORT usPartnerOperSysPri;                     /* �Զ�ϵͳ�������ȼ� */
    UCHAR  ucPartnerOperSysMac[MACADDRLEN];         /* �Զ�ϵͳ����MAC */
    UCHAR  ucPartnerOperState;                       /* �Զ˶˿�����״ֵ̬ */
    UCHAR  ucPartnerReserve;                         /* �����ֶ� */
}PPI_TRUNK_LACP_S;
/* Add end*/

/* Added by chandra 00902193 on 2013-09-10 for policy rt */
typedef struct tagPPI_POLICYRT
{
    ULONG ulPolicyID;
    ULONG ulVrfIndex;
    ULONG ulNodeID;
    ULONG ulMatchCountLow32;
    ULONG ulMatchCountHigh32; /*���д�����ֻ�е�PPI_POLICYRT_ GET_NODE_COUNT ʱ��TRAN����*/
    ULONG ulAclGroup;      /*ACL�������*/
    ULONG ulOutIfIndex;    /*ƥ��ɹ������õĳ��ӿ�����*/
    ULONG ulUserData;      /*�Զ�������*/
    ULONG ulNextHop;       /*ƥ��ɹ������õ���һ����Ϣ��������*/
} PPI_POLICYRT_S;
/* End of Added by chandra 00902193 on 2013-09-10 for policy rt */

typedef struct tagTCPIP_PPI_HOOK
{
    /*·�ɸ���֪ͨ */
    ULONG (*pfTCPIP_PPI_FIB4_Update)(ULONG ulOperType, PPI_RTMSG4_S *pstRtMsg);
    /*ARP����֪ͨ */
    ULONG (*pfTCPIP_PPI_ARP_Update)(ULONG ulOperType, PPI_ARP_S *pstArpMsg);
    /*�ӿڴ���/ɾ��*/
    /*�ӿ�����/״̬����֪ͨ */
    ULONG (*pfTCPIP_PPI_IFNET_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);
    /*PPP��������֪ͨ */
    ULONG (*pfTCPIP_PPI_PPP_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData );
    /*NP���Ĵ��� */
    ULONG (*pfTCPIP_PPI_IP4_Output)(MBUF_S *pstMbuf);

    /* Trunk Port NP�·����� */
    ULONG (*pfTCPIP_PPI_TRUNKPORT_Update)(ULONG ulPortIfIndex, ULONG ulCmd, ULONG ulTrunkIfIndex);

    ULONG (*pfTCPIP_PPI_OSI_Output)(MBUF_S *pstMbuf);

    /* 3ah NP �·����� */
    ULONG (*pfTCPIP_PPI_3AH_Update)(ULONG ulIfIndex, ULONG ulOprType, PPI_3AH_S *pstPpi3ah);

    /*  1AG ����NP�·� */
    ULONG  (*pfTCPIP_PPI_1AG_Update) (ULONG ulIfIndex, ULONG ulOprType,VOID* pEoam1agMsg);

    /*IGMP�·�NP֪ͨ*/
    ULONG (*pfTCPIP_PPI_IGMP_Update)(ULONG ulIfIndex,ULONG ulCmd,ULONG ulMultiAddr);

    /* �·�MAP���� */
    ULONG (*pfTCPIP_PPI_MAP_Update)(PPI_MAP_S *pstMapInfo, ULONG ulOperType);

    /* �·�FIB6·����Ϣ */
    ULONG (*pfTCPIP_PPI_FIB6_Update)(ULONG ulOperType, PPI_RTMSG6_S *pstRtMsg);

    /* L2IF VLAN������Ϣ֪ͨ */
    ULONG (*pfTCPIP_PPI_VLAN_Update)(ULONG ulVid, ULONG ulCmd, VOID *pData);

    /* L2IF PORT������Ϣ֪ͨ */
    ULONG (*pfTCPIP_PPI_PORT_Update)(ULONG ulIndex, ULONG ulCmd, VOID *pData);

    /* L2IF MAC������Ϣ֪ͨ */
    ULONG (*pfTCPIP_PPI_MAC_Update)(ULONG ulCmd, VOID *pData);

    /* L2IF QINQ������Ϣ֪ͨ */
    ULONG (*pfTCPIP_PPI_QINQ_Update)(ULONG ulIndex, ULONG ulCmd, VOID *pData);

    /* VRRP PPI��Ϣ֪ͨ,����ʹ��VRRP������MAC��Ϣ */
    ULONG (*pfTCPIP_PPI_VRRP_Update)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);

    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-04 */
    /* �ӿڰ�/ȥ��VRF PPI�·� */
    ULONG (*pfTCPIP_PPI_VRF_Update)(ULONG ulOperType, VRF_PPI_S *pstVrfMsg);
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-04 */

    /* Download multicase mac control message  */
    /*
     ulOperType  ==  add or del
     ulMsgType  ==  MultiMac��.....
     pData  :  struct for xxx
        typedef struct tagPPI_MULTIMAC
        {
            ULONG ulIfIndex;
            UCHAR aucMultiMacAddr[MACADDRLEN];
            UCHAR aucMultiMacMask[MACADDRLEN];
        }PPI_MULTIMAC_S;
    */
    ULONG (*pfTCPIP_PPI_CTRL_Update)(ULONG ulOperType, ULONG ulMsgType, VOID * pData);

    ULONG (*pfTCPIP_PPI_TRUNKBIND_Update)(ULONG ulOperType, PPI_TRUNK_BIND_S *pstTrunkBind);

    ULONG (*pfTCPIP_PPI_AM4_Update)(ULONG ulOperType, PPI_IPADDR_INFO_S *pstIpAddrInfo);

    ULONG (*pfTCPIP_PPI_MPLSFW_Output)(MBUF_S *pstMbuf, ULONG  ulTunnelInfo);
    /* End: VISP Support multi-instance project */

    /*NP IPV6 ���Ĵ��� */
    ULONG (*pfTCPIP_PPI_IP6_Output)(MBUF_S *pstMbuf);

    /* �·�֪ͨNP PPPOE�Ự�������Ϣ */
    ULONG (*pfTCPIP_PPI_PPPOE_Update)(ULONG ulSessionId, ULONG ulPpiCmd, VOID *pData);
    /*TRUNK �·�֪ͨNP LACP��·���������Ϣ*/
    ULONG (*pfTCPIP_PPI_TRUNK_LACP_Update)(ULONG ulOperType, PPI_TRUNK_LACP_S *pstRtMsg);

    /* Add for policyrt by chandra 00902193 on 2013-09-10 */
    ULONG (*pfTCPIP_PPI_POLICYRT_Update)(ULONG ulOperType, PPI_POLICYRT_S *pstRtMsg);
    /* End of Add for policyrt by chandra 00902193 on 2013-09-10 */

    /*Added by apurba for VRF6*/
    ULONG (*pfTCPIP_PPI_VRF6_Update)(ULONG ulOperType, VRF6_PPI_S *pstVrfMsg);
   /*End of Added by apurba for VRF6*/

}TCPIP_PPI_HOOK_S;

/*ǰ׺ʡ�Խṹ*/
typedef struct tagPPIMcPrefix
{
    UCHAR     ucPrefixValid;                    /*�Ƿ���Ч*/
    UCHAR     ucClass;                          /*class*/
    USHORT    usPrefixLength;                   /*Prefix����*/
    UCHAR     aucPrefix[PPI_MC_PREFIX_MAX_LEN]; /*Prefix����*/
}PPI_MC_PREFIX_S;

#define     PPI_MP_MP_DISCR_MAX_LENGTH   20  /* �ն�����������󳤶� */

/*LCPѡ��PPI�ṹ*/
typedef struct tagNpPppLcpOption
{
    /* �Ƿ�Э�� */
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved          : 22,
            neg_discr          : 1,       /*�Ƿ�Э���ն�������*/
            neg_magicnumber    : 1,       /* Э��ħ����*/
            neg_prefix         : 1,       /*�Ƿ�Э��ǰ׺ʡ��*/
            neg_mhf            : 1,       /*�Ƿ�Э��MHF*/
            neg_ssnhf          : 1,       /*�Ƿ���ö����к�*/
            neg_mrru           : 1,       /*�Ƿ�Э��mrru*/
            neg_mru            : 1,       /**/
            neg_asyncmap       : 1,       /*�Ƿ�Э��ACCM*/
            neg_accompression  : 1,       /*ACFC Compression */
            neg_pcompression   : 1;       /*PFC Compression */
#else
    ULONG   neg_pcompression   : 1,       /*PFC Compression */
            neg_accompression  : 1,       /*ACFC Compression */
            neg_asyncmap       : 1,       /*�Ƿ�Э��ACCM*/
            neg_mru            : 1,       /**/
            neg_mrru           : 1,       /*�Ƿ�Э��mrru*/
            neg_ssnhf          : 1,       /*�Ƿ���ö����к�*/
            neg_mhf            : 1,       /*�Ƿ�Э��MHF*/
            neg_prefix         : 1,       /*�Ƿ�Э��ǰ׺ʡ��*/
            neg_magicnumber    : 1,       /* Э��ħ����*/
            neg_discr          : 1,       /*�Ƿ�Э���ն�������*/
            breserved          : 22;
#endif
    USHORT  usMru;         /*�����յ�Ԫ*/
    USHORT  usMrru;        /*���������鵥Ԫ*/
    ULONG   ulAsyncmap;    /*ACCM��ֵ*/
    UCHAR   ucCode;        /*MHFЭ�̵�codeֵ*/
    UCHAR   ucClass;       /*MHFЭ�̵�classֵ*/
    UCHAR   ucDiscr_len;
    UCHAR   ucDiscr_class;
    PPI_MC_PREFIX_S astPrefix[PPI_MC_PREFIX_MAX_NUM];/*ǰ׺ʡ��ӳ��ṹ*/
    UCHAR   discr_addr[PPI_MP_MP_DISCR_MAX_LENGTH];
    ULONG   ulMagicnumber; /*Э�̵�ħ����*/
}PPI_PPP_LCP_OPTION_S ;


/*IPCP PPI�ṹ*/
typedef struct tagNpPppIpcpOption
{
    /* �Ƿ�Э�� */
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved     : 30,
            neg_vj        : 1,
            neg_iphc      : 1;
#else
    ULONG   neg_iphc      : 1,  /* IPHC Compression? */
            neg_vj        : 1,
            breserved     : 30;
#endif

    /*��ַ*/
    ULONG   ulOurAddr;          /*���˵�ַ�������ֽ���*/
    ULONG   ulHisAddr;          /*�Զ˵�ַ�������ֽ���*/
    /*IPHCЭ�̽��*/
    USHORT  usTcpSpace;         /* TCPѹ�����CIDֵ*/
    USHORT  usNonTcpSpace;      /* Non-TCPѹ�����CIDֵ*/
    USHORT  usMaxPeriod;        /*ͬһ����������������ѹ�����ĵ������*/
    USHORT  usMaxTime;          /*ͬһ�������з��������ײ����ĵ����ʱ����*/
    USHORT  usMaxHeader;        /*����ѹ�����ײ���󳤶�*/
    UCHAR   ucCompressType;     /*����ѹ������*/
    UCHAR   ucRtpCompressType;  /*RTP����ѹ������*/
}PPI_PPP_IPCP_OPTION_S ;

/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
/*IP6CP PPI�ṹ*/
typedef struct tagNpPppIp6cpOption
{
    /* �Ƿ�Э�� */
#if (VRP_BIG_ENDIAN == VRP_YES)
    ULONG   neg_interfaceid :  1,   /* Negotiate interface id */
            neg_compprotocol:  1,
            bReserve        :  30;  /* Ϊ���Ժ���չԤ��Э��λ */
#else
    ULONG   bReserve        :  30,  /* Ϊ���Ժ���չԤ��Э��λ */
            neg_compprotocol:  1,
            neg_interfaceid :  1;   /*  Negotiate interface id */
#endif

    UCHAR   my_interface_id[8],his_interface_id[8];
    USHORT  comp_protocol;   /* protocol value to use in compress protocol option */
    UCHAR   ucPadding[2];
}PPI_PPP_IP6CP_OPTION_S ;
/*End of Added by hanna55555, 2009/3/30 */

typedef struct tagNpPppMuxcpOption
{
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved      : 31,
            neg_defaultpid : 1; /*�Ƿ�Э��Defualt PID*/
#else
    ULONG   neg_defaultpid : 1,
            breserved      : 31;
#endif

    USHORT  usDefaultPid;       /*Defualt PID*/
    USHORT  usReserved;
}PPI_PPP_MUXCP_OPTION_S ;

typedef struct tagNpPppConfigInfo
{
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    ULONG   breserved           : 30,
            bPppReorderWindow   : 1,  /*MP�Ƿ�ʹ����reorder windows*/
            bPppInterleave      : 1;  /*MP�Ƿ�ʹ����LFI����*/
#else
    ULONG   bPppInterleave      : 1,  /*MP�Ƿ�ʹ����LFI����*/
            bPppReorderWindow   : 1,  /*MP�Ƿ�ʹ����reorder windows*/
            breserved           : 30;
#endif
     /*������PPPMUX���ò���*/
    USHORT usMaxSubFrameLen;    /*�����֡����*/
    USHORT usMaxFrameLen;       /*��󸴺�֡����*/
    USHORT usMaxSubFrameNum;    /*�����֡��Ŀ*/
    USHORT usMaxDelay;          /*��ʱ����ʱʱ��*/
    /*MP���ò���*/
    USHORT usMinFragLen;        /*��С��Ƭ����*/
    USHORT usMaxDelayLFI;       /*����Ƭʱ��*/
    ULONG  ulNegoSubOptions ;  /*�Ƿ�Э����ѡ��*/
}PPI_PPPCONFIGINFO_S;

#define PPI_MP_SUPPORT_MAX_BIND  128   /*MP֧����������·��*/

/*MP�ӿں˲�������Ϣ*/
typedef struct tagPPIMpInfo
{
    /*MP��ͨ���󶨵�����·��������(����Ч��)*/
    ULONG ulMpBindSubLink[PPI_MP_SUPPORT_MAX_BIND];
    /*MP��ͨ���󶨵�����·��*/
    ULONG ulMpBindNum;
}PPI_MPINFO_S;

/*��Ҫ�˲����Ϣ�ṹ*/
typedef struct tagPPIPppInfo
{
    ULONG                   ulIfIndex;        /*�ӿ�����*/
    PPI_PPP_LCP_OPTION_S    stLCPGotOption;
    PPI_PPP_LCP_OPTION_S    stLCPHisOption;
    PPI_PPP_IPCP_OPTION_S   stIPCPGotOption;
    PPI_PPP_IPCP_OPTION_S   stIPCPHisOption;
    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
    PPI_PPP_IP6CP_OPTION_S   stIP6CPGotOption;
    PPI_PPP_IP6CP_OPTION_S   stIP6CPHisOption;
    /*End of Added by hanna55555, 2009/3/30 */
    PPI_PPP_MUXCP_OPTION_S  stMUXCPGotOption;
    PPI_PPP_MUXCP_OPTION_S  stMUXCPHisOption;
    PPI_PPPCONFIGINFO_S     stConfigInfo;
    PPI_MPINFO_S            stMPInfo;         /*MP�ӿ������Ϣ������Ƿ�MP�ӿ���Ϊ��*/
}PPI_PPP_INFO_S;

/*����ģ��CCM���Ĳ����ṹ��*/
typedef struct tagPpi_1AGCcmMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD�� ,44�ֽ�*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MD�� ,44�ֽ�*/
    USHORT usMepId;             /*MEPIDֵ*/
    USHORT usVId;               /*vlan IDֵ*/
    UCHAR  ucMdLevel;           /*MD Level��Ϣ*/
    UCHAR  ucCcmInterval;       /*��������*/
    UCHAR  ucRdiFlag;           /*MA�ڵ�RDI���,ȡֵ0��1*/
    UCHAR  ucMaPri;             /*MA��VLAN���ȼ�*/
    UCHAR  ucCompatibleType;    /*1AG����ģʽ*/
    UCHAR  uc1agVersion;        /*MEPʹ�õ�1AG�汾��,0:Draft7�汾;1:��׼�汾;2:Y1731�汾*/
    UCHAR  ucVlanFlag;          /*��MEP�·��͵ı����Ƿ��VLANͷ��־.
                                  0:��ʾ����Ҫ��VLANͷ,1��ʾ��Ҫ��VLAN*/
    UCHAR  ucCcSendEnable ;     /* CCM ʹ�ܱ��*/
    ULONG  ulIfIndex;           /* MEP�����Ľӿ�����*/
    USHORT usLossDetectTimer;

    USHORT  ucPadding;
}PPI_1AGCCMMSG_S;

/* ����1731 PM�ṹ�� */
typedef struct tagPpi_Y1731PMMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD�� ,44�ֽ�*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MA�� ,44�ֽ�*/
    USHORT usMepId;                               /*MEPIDֵ*/
    USHORT usRmepId;                              /*RMEPIDֵ*/
    ULONG  ulInterval;                            /*��������*/
    ULONG  ulTimeOut;                             /*��ʱʱ��*/
}PPI_Y1731PMMSG_S;

/* 1AG MA���� */
typedef struct tagPpi_1AGMaMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];  /*MD�� ,44�ֽ�*/
    UCHAR  szMaName[OAM_1AG_MAX_MANAME_LEN + 1];  /*MD�� ,44�ֽ�*/
    UCHAR  ucCcmInterval;       /* ��������*/
    UCHAR  ucCompatibleType;    /* 1AG����ģʽ*/
    USHORT usVlanId;            /* MA��VLAN id */
    UCHAR  ucMaPri;             /* MA��VLAN���ȼ�*/
    UCHAR  ucRdiFlag;           /* MA�ڵ�RDI���,ȡֵ0��1*/
    UCHAR  ucMaNameType;        /* MD��������,Ŀǰֻ֧���ַ�����ʽ*/
    UCHAR  ucRes;
}PPI_1AGMAMSG_S;

/* 1AGȫ�ֱ��� */
typedef struct tagPpi_1AGGlobalMsg
{
    USHORT usPktType;       /*1AG��������*/
    UCHAR  ucPktPriority;   /*1AG�������ȼ�*/
    UCHAR  ucRes;
    ULONG  ulCompatibleSwitch; /*Э������Կ���*/
}PPI_1AGGLOBALMSG_S;

/* Add for V2R3C06, by shuxieliu00176784, at 2011-10-04. �޸�ԭ��: 1AGȫ��Э��汾 ֧��EOAMЭ��汾ȫ������  */
typedef struct tagPpi_1AGVersionMsg
{
    ULONG  ulGlobalVersion;  /* ȫ��Э��汾 */
}PPI_1AGVERSION_MSG_S;

/*1AG RMEP����*/
typedef struct tagPpi_1AGRmepPara
{
    ULONG  ulIfIndex;       /*Rmep��Ӧ�ĳ��ӿ�,��ͬ�ӿ��Ͽ���ά����ͬԶ��MEP*/
    USHORT usVlanId;        /*VLAN ID,ͨ��VLAN ID���ҵ���Ӧ��MA��MD*/
    USHORT usRmepId;        /*Rmep Idֵ*/
    UCHAR  ucInterval;      /*Զ��MEP�ķ�����������, ΢���������յ�������ת��Ϊ��������ʾ�ļ��ֵ��Ȼ�����3.5����Ϊ��ʱ����*/
    UCHAR  ucMdLevelFlag;   /*�յ�RMEP���ڱ���MD Level,����ֻ���ϻ���ʱ,��������ͬʱ���ϻ�����ʱ��ʱ*/
    UCHAR  aucMacAddr[MACADDRLEN];   /*Զ��physical��ַ*/
    UCHAR  aucMdName[OAM_1AG_MAX_MDNAME_LEN + 1];   /*ά�������� */
    UCHAR  aucMaName[OAM_1AG_MAX_MANAME_LEN + 1];   /*ά�������� */

    UCHAR  ucRdiFlag;         /* Rdi ��ʶ*/
    UCHAR  ucRemoteIfFlag;    /* 0: û��Interface TLV 1: �У��ҽӿ�ΪUP  2�� �У��ҽӿ�ΪDOWN */
    UCHAR  ucVlanFlag;        /* ��ʶ�ϴ��յ���CCM�Ƿ����VLAN 1 :��  0 :û��*/
    UCHAR  ucRMepStatic;      /* 0��ʾ��̬���ɵ�RMEP ��1��ʾ��̬������RMEP */
    UCHAR  ucMdLevel;         /* MD Level */
    UCHAR  ucPad[3];
}PPI_1AGRMEPPARA_S;

/* 1AG MD���� */
typedef struct tagPpi_1AGMDMsg
{
    UCHAR  szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];   /* MD�� ,44�ֽ� */
    UCHAR  ucMdLevel;                              /* MD Level */
    UCHAR  ucMdNameType ;                          /* MD��������,Ŀǰֻ֧���ַ�����ʽ */
    UCHAR  ucPad[2];
}PPI_1AGMDMSG_S; /*�ýṹΪ����*/

typedef struct tagNpIGMPConfigInfo
{
    ULONG ulMultiAddr;          /* �ಥ���ַ */
    ULONG ulIfIndex;            /* �ӿ����� */
}PPI_IGMPConfigInfo_S;

/* VISVP1R7C03 L2IF,PPI�·����ݽṹ���� */
typedef struct tagPPI_VlanIf
{
    ULONG   ulIfIndex;           /* vlanif�ӿ����� */
    UCHAR   aucMac[MACADDRLEN];  /* vlanif physical��ַ*/
    UCHAR   ucReserved[2];
}PPI_VLANIF_S;

/* �˿�����PPI�·���Ϣ */
typedef struct tagPPI_RATELIMIT
{
    ULONG ulLimitEnable;   /* ���û�ȡ���˿���ָ������������ */
    ULONG ulLimitType;     /* �������ͣ�����/���й㲥������/���жಥ������/����δ֪�������� */
    ULONG ulSuppressType;  /* ���ֶ������������������Ʊ�������������ռ�ô���ľ���ֵ */
    ULONG ulSetValue;      /* ���õ�ֵ����ulSuppressType��ʾ�����Ʊ���ʱ��ȡ����ֵ����ulSuppressType
                              ��ʾռ�ô���ľ���ֵʱ����ʾ����ֵ��
                              ������ֵ����ʾ�ĺ����������Լ���⣬�������Ϊ���ĸ�������*/
}PPI_RATE_LIMIT_S;

/* �˿ڼ����Ƴ�vlan����PPI�·���Ϣ */
typedef struct tagPPI_VLAN_LIST
{
    ULONG  ulTagFlag;    /* �Ƿ��TAG: VLAN_TAGGED,VLAN_UNTAGGED */
    USHORT usStartVlanID;
    USHORT usEndVlanID;
}PPI_VLAN_LIST_S;

/* ����TRANSʱ�·��ײ���Ϣ */
typedef struct tagPPI_L2TRANS_CONFIGINFO
{
    ULONG  ulIfIndex;      /*����˿�����*/
    ULONG  ulMode;         /*MODE:stacking ,mapping */
    USHORT usPEVlan;       /*PEVlan��Ҫ��װ�����VLAN��*/
    USHORT usMapVlan;      /*Stacking֮ǰ��CEVlan����Mapping��ֵ*/
    USHORT usCEVlanBegin;  /*CEVlan��ʼֵ���뱨��Я����ǩ�е�VLAN�ţ�*/
    USHORT usCEVlanEnd;    /*CEVlan��ֵֹ���뱨��Я����ǩ�е�VLAN�ţ�*/
} PPI_L2TRANS_CONFIGINFO_S;


typedef struct tagTCPIP_PPI_COUNT
{
    /*·�ɸ���֪ͨ�ܴ��� */
    ULONG ulRtMsg4Total;
    /*·�ɸ���֪ͨʧ�ܴ��� */
    ULONG ulRtMsg4Failure;
    /*ARP����֪ͨ�ܴ��� */
    ULONG ulArpUpdateTotal;
    /*ARP����֪ͨʧ�ܴ��� */
    ULONG ulArpUpdateFailure;
    /*�ӿ����Ը���֪ͨ�ܴ��� */
    ULONG ulIfUpdateTotal;
    /*�ӿ����Ը���֪ͨʧ�ܴ��� */
    ULONG ulIfUpdateFailure;

    /*TRUNK PORT���Ը���֪ͨ�ܴ��� */
    ULONG ulTrunkPortTotal;
    /*TRUNK PORT���Ը���֪ͨʧ�ܴ��� */
    ULONG ulTrunkPortFailure;

    /*PPP��������֪ͨ�ܴ��� */
    ULONG ulPPPUpdateTotal;
    /*PPP��������֪ͨʧ�ܴ��� */
    ULONG ulPPPUpdateFailure;
    /*NP���Ĵ����ܴ��� */
    ULONG ulNPOutputTotal;
    /*NP���Ĵ���ʧ�ܴ��� */
    ULONG ulNPOutputFailure;

    /*OSI NP���Ĵ����ܴ��� */
    ULONG ulOSINPOutputTotal;
    /*OSI NP���Ĵ���ʧ�ܴ��� */
    ULONG ulOSINPOutputFailure;

    /* 3AH NP���Ĵ����ܴ��� */
    ULONG ul3ahNpOutputTotal;
    /* 3AH NP���Ĵ���ʧ�ܴ��� */
    ULONG ul3ahNpOutputFailure;

    /*1AG ֪ͨNP�ܴ���*/
    ULONG ul1agNPOutputTotal;
    /*1AG ֪ͨNPʧ�ܴ���*/
    ULONG ul1agNPOutputFailure;

    /*IGMP ֪ͨNP�ܴ��� byz00104207*/
    ULONG ulIGMPNPOutputTotal;
    /*IGMP ֪ͨNPʧ�ܴ���*/
    ULONG ulIGMPNPOutputFailure;

    /*·�ɸ���֪ͨ�ܴ��� */
    ULONG ulRtMsg6Total;
    /*·�ɸ���֪ͨʧ�ܴ��� */
    ULONG ulRtMsg6Failure;

    /* L2IF VLAN ֪ͨNP�ܴ��� */
    ULONG ulL2ifVlanNPOutputTotal;
    /* L2IF VLAN ֪ͨNPʧ�ܴ��� */
    ULONG ulL2ifVlanNPOutputFailure;

    /* L2IF PORT ֪ͨNP�ܴ��� */
    ULONG ulL2ifPortNPOutputTotal;
    /* L2IF PORT ֪ͨNPʧ�ܴ��� */
    ULONG ulL2ifPortNPOutputFailure;

    /* L2IF MAC ֪ͨNP�ܴ��� */
    ULONG ulL2ifMacNPOutputTotal;
    /* L2IF MAC ֪ͨNPʧ�ܴ��� */
    ULONG ulL2ifMacNPOutputFailure;

    /* L2IF QinQ ֪ͨNP�ܴ��� */
    ULONG ulL2ifQinQNPOutputTotal;
    /* L2IF VLAN ֪ͨNPʧ�ܴ��� */
    ULONG ulL2ifQinQNPOutputFailure;

    /* VRRP ֪ͨNP�ܴ���*/
    ULONG ulVrrpNPOutputTotal;
    /* VRRP ֪ͨNPʧ���ܴ���*/
    ULONG ulVrrpNPOutputFailure;

    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    /* VRF����֪ͨ�ܴ��� */
    ULONG ulVrfUpdateTotal;
    /* VRF����֪ͨʧ�ܴ��� */
    ULONG ulVrfUpdateFailure;
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

    /* �ಥMAC����֪ͨ�ܴ��� */
    ULONG ulMultiMacUpdateTotal;
    /* �ಥMAC����֪ͨʧ�ܴ��� */
    ULONG ulMultiMacUpdateFailure;

    ULONG ulTrunkBindTotal;
    ULONG ulTrunkBindFailure;

    ULONG ulAM4IPConfigTotal;
    ULONG ulAM4IPConfigFailure;

    ULONG  ulVpnPacketRecvTotal;
    ULONG  ulVpnPacketSendTotal;
    ULONG  ulVpnPacketErrorTotal;
    /* End: VISP Support multi-instance project */

    /* IPv6�����·�PPIͳ�� */
    ULONG  ulNPIp6OutputTotal;
    /* IPv6�����·�PPIʧ��ͳ�� */
    ULONG ulNPIp6OutputFailure;

    /* Begin: Ϊ֧��PPPOEЭ�鱣�����������ֶ� */
    /* �·�PPPOE PPI�������ܴ��� */
    ULONG ulPppoeUpdateTotal;
    /* �·�PPPOE PPI������ʧ���ܴ��� */
    ULONG ulPppoeUpdateFailure;
    /* End: PPPOEЭ�鱣���ʱ��ͳ���ֶ���ӽ��� */
    /* Map����֪ͨ�ܴ��� */
    ULONG ulMapUpdateTotal;
    /* Map����֪ͨʧ�ܴ��� */
    ULONG ulMapUpdateFailure;
    /* �·�TRUNK PPI�������ܴ���*/
    ULONG ulTrunkUpdateTotal;
    /* �·�TRUNK PPI������ʧ���ܴ���*/
    ULONG ulTrunkUpdateFailure;
    /* Added by c00902193, policy rt PPI updated, 2013/09/25 */
    ULONG ulPolicyRtUpdateTotal;
    ULONG ulPolicyRtUpdateFailure;
    /*End of  Added by c00902193, policy rt PPI updated, 2013/09/25 */

   /*Added by apurba for VRF6*/
    ULONG ulVrf6UpdateTotal;
    ULONG ulVrf6UpdateFailure;
   /*End of Added by apurba for VRF6*/
}TCPIP_PPI_COUNT_S;



/************************�澯������ݽṹ���궨��begin****************************/
typedef enum TCPIP_WARING_Etag
{
    WARNING_IF_PROTOCOL_UPDOWN,   /* 0 �ӿ��ϵ�Э��״̬�仯 */
    WARNING_PPP_AUTH_FAILURE,     /* 1 PPPЭ����֤ʧ��(�����Է�����) */
    WARNING_ETHARP_IP_CONFLICT,   /* 2 ETH��·�ϼ���е�ַ�뱾����ͻ */
    WARNING_TCP_QLIMIT,           /* 3 TCP�����׽ӿ������������Ѵ����ޣ��µ��������󱻺��� */
    WARNING_SOCKET_NUMBER_MAX,    /* 4 SOCKET��Ŀ�Ѵﵽϵͳ�������ޣ��޷������µ�SOCKET */
    WARNING_DHCP_FAILURE,         /* 5 DHCP Client�ò���������Server����Ӧ */
    WARNING_HA_FAIL,              /* 6 HAƽ��У��ʱ����Э��ջ����������Ϣ */
    WARNING_BFD_IPCHANGE,         /* 7 BFDʹ�õĵ�ַ���û����� */
    WARNING_BFD_TRUNKPORTCHANGE,  /* 8 BFDʹ�õĳ��ӿڱ�������Ƴ�trunk��Ա�˿� */
    WARNING_ERR_NETWORK_CONFIGURE,/* 9 ������һ�������������ʽ,�����������ӿ��γɵ�vlink·���������շ�����ȷ */
    WARNING_PPP_IPHC_PARA_DIFF,   /* 10 PPP�������õĲ����ͱ���Э�̻�õĲ�����һ��, ������Э�̻�õĲ�����һ�� */
    WARNING_PPP_IPCONFLICT,       /* 11 PPPЭ�����˵�ַ��ͻ */
    WARNING_PPP_LOOPBACK,         /* 12 PPP��·���ص���Э�̲����澯*/
    WARNING_MP_ED_NOCONSISTENT,   /* 13 MP ED��һ�µ��°�ʧ��Э�̲����澯*/
    WARNING_PPP_REMOVE,           /* 14 PPP�澯����ͨ��*/
    WARNING_3AH,                  /* 15 3ah����澯ID */
    WARNING_1AG_ACROSS,           /* 16 1AG�������Ӹ澯*/
    WARNING_1AG_ERR,              /* 17 1AG����CC_LOST��MEPID�ظ���Զ�˽ӿ�״̬��CCM Interval��ƥ�䡢MD Level��ƥ��澯*/
    WARNING_1AG_RDI,              /* 18 1AG����RDI�澯*/
    WARNING_PPP_LCP_AUTH_NEGOTIATE_FAILURE, /* 19 LCP��֤Э��Э��ʧ�ܸ澯 */
    WARNING_PPP_LCP_MP_NOBIND,      /* 20 LCPЭ��ʱ̽�⵽һ�˰󶨵�MP����һ��û�а󶨵�MP�� */
    WARNING_PPP_MP_SUBLINKLOWLIMIT, /* 21 �趨MP���޷�ֵ������·�����澯 */
    WARNING_PPP_NPINFO_NOCONSISTENT,/* 22 VISP�·���NP����Ϣ��NP��Ч����Ϣ��һ��*/
    WARNING_RM_ROUTENUM_MAX,        /* 23 RM FIB����·�������ﵽϵͳ���ø澯����ֵ */
    WARNING_MSTP_GUARD,             /* 24 MSTP������澯��Ϣ */
    WARNING_PPI_DOWN_PPP_FAIL,      /* 25 NP�·�ʧ��  */
    WARNING_LACP_NEGOUT,            /* 26 TRUNK�˿�LACP�״�Э�̲�ͨ������澯 */
    WARNING_PPP_NEG_NOT_PASS,       /* 27 �û�ָ��ʱ����Э�̲�������澯*/
    WARNING_MP_CFG_NOCONSISTENT,    /* 28 ���˻�Զ���ͨ��PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX��һ�µ���LCP down */
    WARNING_ARPGUARD_HAPPEN,        /* 29 ARP�������澯���� */
    WARNING_ARPGUARD_RESTORE,       /* 30 ARP�������澯�ָ� */
    WARNING_ARP_CONFLICT,           /* 31 ��̬ARP�Ͷ�̬ARP��ͻ */
    WARNING_LACP_PARAM_WRONG,       /* 32 TRUNK��Ա�˿ڲ�������ȷ����Э��ʧ�ܸ澯���������� SGSN���� BC3D02743 20100224 */
    WARNING_BFD_SESSION_CONFLICT,   /* 33 BFD�Ự������ͻ */
    WARNING_VLAN_CONSISTENCY,       /* 34 VLAN ID ��һ�¸澯 */
    WARNING_ARPGUARD_ARPCONFLICT,   /* 35 ARP�������澯 */
    WARNING_Y1731_AIS,              /* 36   Y1731 AIS �澯*/
    WARNING_LLDP_REMOTE_TABLE_UPDATE, /*37 LLDP�澯*/
    WARNING_ATTACK,                 /*38 Attack ���޸澯, added for IP attack statistics. */

    WARNING_MAX                   /* ö��ֵ���ޣ���ʵ�� */
}TCPIP_WARING_E;

/* SGSN���� BC3D02743 20100224: TRUNK��Ա�˿ڲ�������ȷ����Э��ʧ�ܸ澯���������� */
typedef struct tagLACP_PARAM_WRONG
{
    ULONG ulPortIfIndex;
    CHAR  szPortIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulBeginOrEnd;    /* 1 �����澯��0 �����澯 */
    ULONG ulParamType;     /* 0 ˫��ģʽ����ȷ�� 1 ���ʲ�һ�� */
}LACP_PARAM_WRONG_S;

typedef struct tagIF_PROTOCOL_PARAM
{
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulProtocolID;
    ULONG ulUpDown;     /* ������궨�� */
}IF_PROTOCOL_PARAM_S;
#define IF_WARN_PROTOCOLISUP   1 /* Э��UP */
#define IF_WARN_PROTOCOLISDOWN 2 /* Э��DOWN */

#define LQM_CHANGE_BAD  3
#define LQM_CHANGE_GOOD 4

typedef struct tagPPP_AUTH_PARAM
{
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulAuthType;   /* ������궨�� */
}PPP_AUTH_PARAM_S;
#define PPP_WARN_PAPAUTH  1 /* PAP��֤���� */
#define PPP_WARN_CHAPAUTH 2 /* CHAP��֤���� */

/*�û�ָ��ʱ����Э�̲�������澯�����ݽṹ*/
typedef struct tagPPP_NEG_NOT_PASS_WARNINGOUT
{
    ULONG ulIfIndex;                   /*�ӿ�����*/
    ULONG ulLcpState;                  /*LCP״̬*/
    ULONG ulIpcpState;                 /*IPCP״̬*/
    /* Added by hanna55555, BC3D01643, 2009/6/4 */
    ULONG ulIp6cpState;                /*IP6CP״̬*/
    /*End of Added by hanna55555, 2009/6/4 */
    ULONG ulPppmuxState;               /*PPPMUX״̬*/
    ULONG ulMpIfIndex;                 /*mp���ӿ�����*/
}PPP_NEG_NOT_PASS_WARNINGOUT_S;

typedef struct tagETH_IPCONFLICT_PARAM
{
    ULONG ulIPConflictType;
    ULONG ulIfIndex;
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulIPAddr;     /* �������ַ */
    UCHAR szMacAddr[6]; /* ��ͻ�ߵ�physical��ַ,6�ֽ� */
    CHAR  ucReserved[2];
    ULONG ulVrfIndex;   /* VRF���� */
    /* Add end */
}ETH_IPCONFLICT_PARAM_S;

/* ����̬ARP��ͻ�澯����ṹ */
typedef struct tagETH_SARPCONFLICT_PARAM
{
    ULONG     ulIfIndex;        /* �ӿ����� */
    ULONG     ulVrfID;          /* VRF ʵ�� */
    ULONG     ulIPAddr;         /* �������ַ */
    UCHAR     szMacAddr[6];     /* ��ͻ�ߵľ�̬physical��ַ */
    UCHAR     ucAlmSt;          /* �澯״̬,1�澯���� 0�澯���� */
    UCHAR     ucPadding;
}ETH_SARPCONFLICT_PARAM_S;

#define ETH_WARN_ETHIP_CONFLICT     1   /* ��̫�ӿڵ�ַ��ͻ���� */
#define ETH_WARN_OMIP_CONFLICT      2   /* ����ARP������߼��ӿڵ�ַ��ͻ���ͣ����ڵ�ַ��ͻ�澯ʱʹ�� */
#define ETH_WARN_ETHIP_CONFLICT_CLEAR_CONFIGURE     3   /*��̫�ӿڵ�ַ��ͻ�����澯���Լ��޸�����������*/
#define ETH_WARN_ETHIP_CONFLICT_CLEAR_DETECT        4   /*��̫�ӿڵ�ַ��ͻ�����澯��̽�������� */
#define ETH_WARN_OMIP_CONFLICT_CLEAR_CONFIGURE      5   /* ARP������߼��ӿڵ�ַ��ͻ�����澯���Լ��޸����������� */
#define ETH_WARN_OMIP_CONFLICT_CLEAR_DETECT         6   /* ARP������߼��ӿڵ�ַ��ͻ�����澯��̽�������� */

#define ETH_WARN_CLEAR_BY_CONFIG 0
#define ETH_WARN_CLEAR_BY_DETECT 1

typedef struct tagTCP_QLIMIT_PARAM
{
    ULONG ulSockFD;     /* ����Socket��Fd */
    ULONG ulLPort;      /* ����Socket�İ󶨶˿ں� */
    ULONG ulQLimit;     /* ����Socket���õ�listen��ֵ */
}TCP_QLIMIT_PARAM_S;

typedef struct tagDHCP_FAILURE_PARAM
{
    ULONG ulIfIndex;    /* DHCP�����ڵĽӿ����� */
    CHAR  szIfName[IF_MAX_INTERFACE_NAME_LEN+1];
    ULONG ulFailType;   /* ������ĺ궨�� */
    ULONG ulIPAddr;     /* ��ַ, ������ */
    ULONG ulIPMask;     /* ��������, ������ */
}DHCP_FAILURE_PARAM_S;
#define DHCP4C_WARN_NOSERVER 1 /* DHCP Client�ò���������Server����Ӧ */
#define DHCP4C_WARN_RCVNAK   2 /* DHCP Client�����ӳ����ڡ������ذ�ʱ��NAK�������ַ */
#define DHCP4C_WARN_LEASEOUT 3 /* DHCP Client�������������ַ */
#define DHCP4C_WARN_IPCONFLICT     4 /* DHCP Client��ȡ��ַ��������������ַ��ͻ */
#define DHCP4C_WARN_BINDFAIL    5 /* DHCP Client��ȡ��ַ��ʧ�� */

typedef struct tagBFD_WARNING_PARAM
{
    ULONG ulIfIndex;     /* ��ַ���ڵĽӿ�����;����Ϊtrunk��Ա�˿����� */
    ULONG ulBfdSessionID;/* BFD�ỰID */
    ULONG ulIPAddr[4];      /* ��ֵַ�������� */
    ULONG ulIpVersion;
    ULONG ulWarnType;     /* ������ĺ궨�� */
}BFD_WARNING_PARAM_S;
#define BFD_WARN_DELETESRCADRR  1 /* BFD�Ựʹ�õ�Դ��ַ��ɾ��; */
#define BFD_WARN_DSTADRRISLOCAL 2 /* BFD�Ựʹ�õ�Ŀ�ĵ�ַ��Ϊ�˱��ص�ַ */
#define BFD_WARN_ADDPORT        3 /* �ӿ����ӵ�trunk�� */
#define BFD_WARN_REMOVEPORT     4 /* �ӿڴ�trunk���Ƴ� */
#define BFD_WARN_STATICSESSIONEXIST  5 /* �Ѿ����ھ�̬Session�����ܴ�����̬Session*/
#define BFD_WARN_DYNAMICSESSIONEXIST 6 /* �Ѿ����ڶ�̬Session�����ܴ�����̬Session */

/* HA�澯�ṹ*/
typedef struct tagHAWARM_S
{
    ULONG  ulflag ; /* �澯ID��������ĺ궨�� */
    ULONG  ulPara ; /* �澯���� */
}HAWARM_S;
#define WARNING_HA_PACKET_REASS             0x1
#define WARNING_HA_OUT_OF_ORDER             0x2
#define WARNING_HA_DEL_IF_BY_CHECK          0x3
#define WARNING_HA_SMOOTH_CHK_SOCKET_FAIL   0x4
#define WARNING_HA_KEEPALIVE_TIMEOUT        0x5
#define WARNING_HA_OUT_OF_ORDER_DETECT      0x6
#define WARNING_HA_CKSUM_ERROR              0x7
#define WARNING_HA_SENDMSG_FAIL             0x8

typedef struct tagPPP_PARA_S
{
    ULONG ul_is_different; /* 0 ��������������ȫһ��  1 ����������������ȫһ�� */
    ULONG ul_want_value;  /* �������õ�ֵ */
    ULONG ul_got_value;   /* ����Э�̻�õ�ֵ */
    ULONG ul_his_value;   /* Э�̻�õĶԶ˵�ֵ */
}PPP_PARA_S;

typedef struct tagPPP_IPHC_PARA_WARNING_S
{
    ULONG ul_flag;  /* 0 �澯����  1 �澯 */
    ULONG ul_if_index;  /* �ӿ����� */
    PPP_PARA_S st_neg_iphc;  /* �Ƿ�ʹ��IPHC, ����ȡֵ: 0 δʹ��  1 ʹ�� */
    PPP_PARA_S st_rtp_compression;  /* �Ƿ�ʹ��RTPѹ��, ����ȡֵ: 0 δʹ��  1 ʹ�� */
    /* ����ѹ������, ����ȡֵ: 0 ȫ��ѹ��  1 ��ѹ����TCP����  2 ��ѹ��TCP����  3 ����ѹ�� */
    PPP_PARA_S st_compress_type;
    PPP_PARA_S st_tcp_space;  /* TCP������,  ����ȡֵ��Χ[0, 255] */
    PPP_PARA_S st_non_tcp_space;  /* ��TCP������,  ����ȡֵ��Χ[0, 65535] */
}PPP_IPHC_PARA_WARNING_S;


/*����PPPЭ�̵�ַ��ͻ�澯��ED��������һ�¸澯�����س�ͻ�澯����Ӧ�ĸ澯����,add by wuhailan,2008-04-11.*/

/*֧��PPPЭ�̵�ַ��ͻ�澯*/
typedef struct tagPPP_IPCONFLICT_PARAM
{
    ULONG ulIPConflictType;   /* PPPЭ��IP��ͻ�����ͣ����궨�� */
    ULONG ulIfIndex;          /* ��ͻ�ӿڵ����� */
    ULONG ulIPAddr;           /* �������ַ */
}PPP_IPCONFLICT_PARAM_S;
#define PPP_WARN_IPCONFLIT_PEERSAME     1   /* Э�����˵�ַ��ͻ */
#define PPP_WARN_IPCONFLIT_MODE         2   /* ���˸��Զ˷����ַ�����ǶԶ����Լ��ĵ�ַ */
#define PPP_WARN_IPCONFLIT_LOCALSAME    3   /* Э�̵�����ַ�뱾������IP��ͻ */

/*֧��PPP��·���ص���Э�̲����澯*/
typedef struct tagPPP_LOOPBACK_PARAM_WARNING
{
    ULONG ulLoopBackType;     /* ���ؽ׶�����*/
    ULONG ulIfIndex;          /* ��ͻ�ӿڵ����� */
    ULONG ulgot_magic_value;  /* ����Э�̵���ħ���� */
    ULONG ulhis_magic_value;  /* �Զ�Э�̵���ħ���� */
    ULONG ulpck_magic_value;  /* �յ����ĵ�ħ���� */
}PPP_LOOPBACK_PARAM_WARNING_S;
#define PPP_WARN_LOOPBACK_NAK      1   /* Э�̹����з��ֻ��� */
#define PPP_WARN_LOOPBACK_ECHO     2   /* ECHO����̽�⵽���� */
#define PPP_WARN_IN_SERIES         3   /* ECHO����̽�⵽��·���� */


#ifndef PPP_MP_DISCR_MAX_LENGTH
#define PPP_MP_DISCR_MAX_LENGTH    20
#endif

typedef struct tagMP_ED_PARA_S
{
    ULONG ulIfIndex;     /* �ӿ����� */
    ULONG ulneg_discr;   /* �Ƿ�Э���ն������� */
    ULONG uldiscr_len;   /* �ն����������� */
    ULONG uldiscr_class; /* �ն����������� */
    UCHAR szdiscr_addr[PPP_MP_DISCR_MAX_LENGTH]; /* Э�̻�õĶԶ˵�ֵ */
}MP_ED_PARA_S;

/*֧��MP�ն���������һ�¸澯*/
typedef struct tagMP_ED_CONSISTENT_WARNING
{
    ULONG        uledConsistentType;     /* MP�ն���������һ�¸澯����*/
    MP_ED_PARA_S stfather_ed_Info;       /* ��ͨ���ն���������Ϣ */
    MP_ED_PARA_S stson_ed_Info;          /* ����·�ն���������Ϣ */
}MP_ED_CONSISTENT_WARNING_S;
#define PPP_WARN_ED_CONSISTENT_NEGD      1   /* �Ƿ�Э��ED */
#define PPP_WARN_ED_CONSISTENT_DLENCLASS 2   /* ED���Ȼ����� */
#define PPP_WARN_ED_CONSISTENT_DADDR     3   /* EDֵ */

typedef struct tagPPP_WARNING_REMOVE
{
    ULONG ulIfIndex;     /* �ӿ�����*/
    ULONG ulWarningType; /* �澯����*/
}PPP_WARNING_REMOVE_S;
#define PPP_WARN_LOOPBACK        1   /*�������ظ澯����*/
#define PPP_WARN_IPCONFLICT      2   /*����IPЭ�̵�ַ��ͻ�澯����*/
#define PPP_WARN_ED_NOCONSISTENT 3   /*����MP�ն���������һ�¸澯����*/
#define PPP_WARN_LCP_AUTH_NEGOTIATE_FAILURE  4   /*����LCP��֤Э��Э��ʧ������*/
#define PPP_WARN_LCP_MP_NOBIND      5   /*����LCPЭ��ʱ̽�⵽һ�˰󶨵�MP����һ��û�а󶨵�MP������*/
#define PPP_WARN_MP_SUBLINKLOWLIMIT 6   /*�����趨MP���޷�ֵ������·��������*/

/* �������˻�Զ���ͨ��PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX��һ�µ���LCP down */
#define PPP_WARN_MP_CFG_NOCONSISTENT       7

/* 3ah����澯��������ݽṹ */
typedef struct tagOam3ahWarnParam
{
    ULONG ulIfIndex;            /* �ӿ�����                                             */
    ULONG ulEventType;          /* �澯�¼�����                                         */
    ULONG ulLclRmt;             /* �澯�������Ա��˻��ǶԶ�(���¼�����ϸ澯������)   */
    ULONG ulFaultStartEnd;      /*���Ͽ�ʼ����ֹ(�Թ��ϸ澯������)                      */
}OAM3AH_WARN_PARAM_S;

/* 3AH����澯���� */
typedef enum enOam3ahWarnType
{
    OAM3AH_WARN_ERR_SYMPRD = 1, /* ������������¼� */
    OAM3AH_WARN_ERR_FRAME,      /* ��֡�¼�         */
    OAM3AH_WARN_ERR_FRMPRD,     /* ��֡�����¼�     */
    OAM3AH_WARN_ERR_FRMSECSUM,  /* ��֡���¼�       */

    OAM3AH_WARN_LINKFAULT,      /* ��·����         */
    OAM3AH_WARN_DYINGGASP,      /* ��������         */
    OAM3AH_WARN_CRITICALEVT,    /* �����¼�         */

    OAM3AH_WARN_SENDANY_START,  /* ����SENDANY      */
    OAM3AH_WARN_SENDANY_END,    /* �˳�SENDANY      */

    OAM3AH_WARN_LB_LCL_START,   /* ���뻷����Ӧ��̬ */
    OAM3AH_WARN_LB_LCL_END,     /* �˳�������Ӧ��̬ */
    OAM3AH_WARN_LB_RMT_START,   /* ���뻷�ط�����̬ */
    OAM3AH_WARN_LB_RMT_END,     /* �˳����ط�����̬ */

    OAM3AH_WARN_NEGTIMEOUT,          /* �״�Э�̲�ͨ������澯 */
}OAM3AH_WARN_TYPE_E;


/*1AG����澯��������������ݽṹ��*/
typedef struct tagOAM_1AG_CROSSCONPARA
{
    ULONG ulIfIndex; /*�ӿ�����*/
    USHORT usVlanId; /*������VLAN ID*/
    UCHAR ucWarnState; /*�澯����,1-�澯,0-�ָ��澯*/
    UCHAR ucres;
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*����MD��*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*����MA��*/
    UCHAR szRemoteMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*Զ��MD��*/
    UCHAR szRemoteMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*Զ��MA��*/
}OAM_1AG_CROSSCONPARA_S;

/*1AG����澯���MEPID�ظ���CC_LOST��Զ�˽ӿ�״̬�仯
CCM Interval��ƥ�䡢MD Level��ƥ�����ݽṹ��*/
typedef struct tagOAM_1AG_ERRPARA
{
    ULONG  ulIfIndex;/*�澯�ӿ�����*/
    USHORT usRMepID; /*�澯��Զ��MEPID*/
    UCHAR ucWarnType;/*�澯����*/
    UCHAR ucWarnState; /*�澯����,1-�澯,0-�ָ��澯*/
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*����MD��*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*����MA��*/
}OAM_1AG_ERRPARA_S;

/*1AG����澯���RDI�澯��*/
typedef struct tagOAM_1AG_RDIPARA
{
    UCHAR ucWarnState; /*�澯����,1-�澯,0-�ָ��澯*/
    UCHAR ucRes[3];
    UCHAR szLocalMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*����MD��*/
    UCHAR szLocalMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*����MA��*/
}OAM_1AG_RDIPARA_S;

typedef enum enumTcpipOAMWarn1AGType
{
    OAM_1AG_MEPIDREPEAT = 0, /*mep id�ظ�*/
    OAM_1AG_CCLOST,       /*rmep CCM���Ķ�ʧ*/
    OAM_1AG_IFSTATE,     /*rmep �ӿ�״̬*/
    OAM_1AG_CCM_INTERVAL,  /*rmep CCM���� �������������� */
    OAM_1AG_MD_LEVEL,     /*MD Level ������MEG Level */
    OAM_Y1731_MEGID,    /* ������MEGID */
    OAM_Y1731_MEPID,    /* ������MEPID */

    OAM_WARN_TYPE_MAX
}TCPIP_OAM_1AG_WARN_TYPE_E;

typedef struct tagPPP_AUTH_NEGOTIATE_PARAM
{
    ULONG ulIfIndex;
    ULONG ulWantNegCHAP;    /* ���������Ƿ�Э��CHAP(1-��,0-��) */
    ULONG ulWantNegPAP;     /* ���������Ƿ�Э��PAP(1-��,0-��) */
    ULONG ulGotNegCHAP;     /* Э�̽���Ƿ����CHAP��֤(1-��,0-��) */
    ULONG ulGotNegPAP;      /* Э�̽���Ƿ����PAP��֤(1-��,0-��) */
}PPP_AUTH_NEGOTIATE_PARAM_S;

typedef struct tagPPP_MP_NOBIND_PARAM
{
    ULONG ulIfIndex;
    ULONG ulMpNobindType;   /*������궨��*/
}PPP_MP_NOBIND_PARAM_S;
#define PPP_WARN_NOBIND_LOCAL     1  /* ����δ����MP�� */
#define PPP_WARN_NOBIND_REMOTE    2  /* �Զ�δ����MP�� */

typedef struct tagPPP_MP_SUBLINKLOWLIMIT_PARAM
{
    ULONG ulIfIndex;
    ULONG ulMpBindNum;   /*��ǰ��ͨ���󶨵�����·��(����Ч)*/
    ULONG ulUpSublinkLowLimit; /*���޷�ֵ*/
}PPP_MP_SUBLINKLOWLIMIT_PARAM_S;

/*�˲鲻һ��ʱ�ϱ��澯�Ĳ���*/
typedef struct tagPPP_NPINFO_PARAM
{
    ULONG ulIfIndex;    /*�ӿ�����*/
    PPI_PPP_INFO_S stPPIInfo;  /*VISP����Ϣ*/
    PPI_PPP_INFO_S stNPInfo;  /*NP����Ϣ*/
}PPP_NPINFO_PARAM_S;

/*1AG����澯���AIS�澯��*/
typedef struct tagOAM_1AG_AISPARA
{
    UCHAR ucWarnState; /*�澯����,1-�澯,0-�ָ��澯*/
    UCHAR ucMdLevel;    /* MD �ȼ� */
    UCHAR ucRes[2];
    UCHAR szMdName[OAM_1AG_MAX_MDNAME_LEN + 1];/*����MD��*/
    UCHAR szMAName[OAM_1AG_MAX_MANAME_LEN + 1];/*����MA��*/
}OAM_1AG_AISPARA_S;


/* PPPģ��NP�·�ʧ�ܱ�־λ */
#define    PPI_LCPGOTOPTION     0x0001    /* LCP����Э��ѡ�� */
#define    PPI_LCPHISOPTION     0x0002    /* LCP�Զ�Э��ѡ�� */
#define    PPI_IPCPGOTOPTION    0x0004    /* IPCP����Э��ѡ�� */
#define    PPI_IPCPHISOPTION    0x0008    /* IPCP�Զ�Э��ѡ�� */
#define    PPI_MUXCPGOTOPTION   0x0010    /* MUXCP����Э��ѡ�� */
#define    PPI_MUXCPHISOPTION   0x0020    /* MUXCP�Զ�Э��ѡ�� */
#define    PPI_ADD_MLPPP        0x0040    /* �ӿڼ��뵽ML PPP */
#define    PPI_DEL_MLPPP        0x0080    /* �ӿڴ�һ��ML PPP��ɾ�� */
#define    PPI_CONFIGINFO       0x0100    /* ���˵�������Ϣ*/
/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
#define    PPI_IP6CPGOTOPTION    0x0200    /* IP6CP����Э��ѡ�� */
#define    PPI_IP6CPHISOPTION    0x0400    /* IP6CP�Զ�Э��ѡ�� */

#define     PPI_SET_OSICPGOTOPTION      0x0800      /*֪ͨNP OSICP����Э��ѡ��*/
#define     PPI_SET_OSICPHISOPTION      0x1000      /*֪ͨNP OSICP�Զ�Э��ѡ��*/
#define     PPI_GET_LCPGOTOPTION        0x2000      /* ��ȡ����LCPЭ��ѡ�� */
#define     PPI_GET_LCPHISOPTION        0x4000      /* ��ȡ�Զ�LCPЭ��ѡ�� */
#define     PPI_GET_IPCPGOTOPTION       0x8000      /* ��ȡIPCP����Э��ѡ�� */
#define     PPI_GET_IPCPHISOPTION       0x10000     /* ��ȡIPCP�Զ�Э��ѡ�� */
#define     PPI_GET_OSICPGOTOPTION      0x20000     /* ��ȡOSICP����Э��ѡ�� */
#define     PPI_GET_OSICPHISOPTION      0x40000     /* ��ȡOSICP�Զ�Э��ѡ�� */

/*End of Added by hanna55555, 2009/3/30 */

/* PPPģ��NP�·�ʧ���ϱ��澯�Ĳ��� */
typedef struct tagPPI_DOWN_PPP_FAIL
{
    ULONG ulIfIndex;    /* PPP�ӿ����� */
    ULONG ulNpFailed;   /* �·�ʧ�ܵ����ͣ�����LCP,IPCP,MCP,MP,CONFIG����λ��ʶ */
}PPI_DOWN_PPP_FAIL;


/*RM·�������澯*/
typedef struct tagRM_ROUTENUMMAX_PARAM
{
    ULONG ulWarnType;  /*�澯���ͣ�1-�澯��������2-�澯����*/
    ULONG ulInstace;   /*ʵ����*/
    ULONG ulCurRouteNum; /*��ǰFIB��·������*/
}RM_ROUTENUMMAX_PARAM_S;
#define RM_WARN_RTNUM_EXCEED           1   /* FIB��·���������� */
#define RM_WARN_RTNUM_CLEAR_EXCEED     2   /*FIB��·���������������澯 */

#define CONTROL_PACKET_OUTPUT 0      /* ��ʾ���ĵ�������� */
#define CONTROL_PACKET_INPUT  1      /* ��ʾ���ĵ����뷽�� */


/* TRUNK�˿�LACP�״�Э�̲�ͨ������澯�ṹ
  �澯ID: WARNING_LACP_NEGOUT */
typedef struct tagTrunkLacpNotPassWarning
{
    ULONG ulPortIfIndex;    /* �˿����� */
    ULONG ulTkId;           /* �˿�����TrunkId */
}TRUNKPORT_LACPNOTPASS_WARNING_S;



/* ���˻�Զ���ͨ��PFC/ACFC/MHF/SSNHF/MRU/MRRU/PREFIX��һ�µ���LCP down */
typedef struct tagMP_SONCFG_NOCONSISTENT_WARNING
{
    ULONG ulFatherIfIndex;
    ULONG ulSonIfIndex;
    PPI_PPP_LCP_OPTION_S stFatherGotOption;
    PPI_PPP_LCP_OPTION_S stSonGotOption;
    PPI_PPP_LCP_OPTION_S stFatherHisOption;
    PPI_PPP_LCP_OPTION_S stSonHisOption;
}MP_SONCFG_NOCONSISTENT_WARNING_S;

#define MEM_ERR_RECORDNUM   10
/* �ڴ����ʧ������ */
enum enMemErrType
{
    MEM_ERR_ALLOCMID = 1,  /* 1 �����ڴ�ʱ,MID���� */
    MEM_ERR_FREEMID,       /* 2 �ͷ��ڴ�ʱ,MID���� */
    MEM_ERR_FREELEN,       /* 3 �ͷ��ڴ�ʱ,���ȴ��� */

    MEM_ERR_MAX,
};

/*��¼�ڴ淢��������Ϣ���ݽṹ*/
typedef struct tagMemErrRecord
{
    ULONG ulErrType;   /* ������Ϣ����, ȡֵΪenMemErrType*/
    ULONG ulPara[4];   /* ������Ϣ��ز��� */
}MEM_ERR_RECORD_S;

/* ͳ���ڴ������Ϣ���ݽṹ */
typedef struct tagMemErrStat
{
    ULONG ulAllocMidErrNum;   /* �����ڴ�ʱMID������� */
    ULONG ulFreeMidErrNum;    /* �ͷ��ڴ�ʱMID������� */
    ULONG ulFreeLenErrNum;    /* �ͷ��ڴ�ʱLEN������� */
    MEM_ERR_RECORD_S stMemErrRecord[MEM_ERR_RECORDNUM];     /* ��¼���MEM_ERR_RECORDNUM������Ϣ */
    ULONG ulCurRecordTag;  /*��ǰӦ�ü�¼ͳ����Ϣ�±�,�����μ�¼��stMemErrRecord��Ա�����±�ֵ */
}MEMERRSTAT_S;

/* Add End */

/* ARP����ƭ�ϱ��澯���ݽṹ */
typedef struct tagARPGuardWarning
{
    ULONG ulIPAddr;                   /* ��ַ */
    UCHAR ucCurMac[MACADDRLEN];       /* ��ǰ�����ε�MAC���ڸ澯�ָ�ʱʹ�ã��澯ʱ��дΪ0 */
    UCHAR ucPad[2];                   /* �����ֶ� */
}ARP_GUARD_WARNING_S;

typedef struct tagPPI_PPPOE_INFO
{
    ULONG ulSessionId;              /* PPPOE�ỰID */
    ULONG ulEthIfIndex;             /* Ethernet�ӿڵĽӿ����� */
    ULONG ulDialerIfIndex;          /* Dialer�ӿڵĽӿ����� */
    ULONG ulVaIfIndex;              /* ��Ӧ��VA�ӿڵĽӿ����� */
    ULONG ulSessionState;           /* PPPOE�Ự��״̬ */
    UCHAR szOurMacAddr[MACADDRLEN]; /* ���˶�ӦEthernet�ӿڵ�physical��ַ */
    UCHAR szHisMacAddr[MACADDRLEN]; /* �Զ˵�physical��ַ */
    ULONG ulReserved;               /* �����ֶΣ������Ժ���չʱʹ�� */
}PPI_PPPOE_INFO_S;


/* Add by zhaoyue00171897, at 2011-08-17. �޸�ԭ��: ֧�ֻ�ȡ��̬FDB���� */
/* ��ȡ��̬FDB����PPI�ṹ�� */
typedef struct tagPPI_L2IF_DYNAMIC_FDB_INFO
{
    UCHAR  aucMacAddr[MACADDRLEN];       /* physical��ַ             */
    USHORT usVlanId;                     /* physical��ַ����VLAN ID  */
    ULONG  ulIfIndex;                    /* �ӿ�����            */
    ULONG  ulAgingTime;                  /* �ϻ�ʱ�� */
}PPI_L2IF_DYNAMIC_FDB_INFO_S;

typedef ULONG (*TCPIP_REBOOT_MODE_HOOK_FUNC)(ULONG ulModID);

/************************�澯������ݽṹ���궨��end****************************/



/*********************************����ԭ�Ͷ���********************************/


typedef struct tagTCPIP_LOG_HOOK_FUNC
{
    VOID (*pfTCPIP_FixlenLogOutput)(ULONG ulLogCode, ULONG ulLogLevel,
                                    ULONG ulLogType, VOID* pcFormat,
                                    ULONG lPara1, ULONG lPara2,
                                    ULONG lPara3, ULONG lPara4);
    VOID (*pfTCPIP_VarlenLogOutput)(ULONG ulLogCode, ULONG ulLogLevel,
                                    ULONG ulLogType, VOID* pcFormat, VOID* pData);
}TCPIP_LOG_HOOK_FUNC;

typedef VOID (*gpfTCPIPDebugOutput)(CHAR *pDebugInfo);
typedef VOID (*gpfTCPIPWarningOutput)(ULONG ulWarningID, VOID* pWarnParam);
typedef VOID (*gpfTCPIPInfoOutput)(CHAR *pInfo);
typedef VOID (*gpfVOSAssertX)(LONG lExpression, CHAR *pcFileName, ULONG ulLine);
typedef ULONG (*gpfTCPIPUserStop)(VOID);
typedef ULONG (*gpfTCPIPTrrtUserStopEx )(ULONG ulExecID);
typedef ULONG (*gpfTCPIPPingUserStopEx )(ULONG ulExecID);
typedef ULONG (*gpfGetSockMaxNum)(VOID);
typedef ULONG (*gpfRegAllAppInfo)(VOID);
typedef ULONG (*CreateMutex_HOOK_FUNC)(CHAR *pMutexName, ULONG *pulMutexID);
typedef ULONG (*CreateSm_HOOK_FUNC)(CHAR *pCountName, ULONG ulSmInit, ULONG *pulCountID);
typedef ULONG (*SmP_HOOK_FUNC)(ULONG ulMutexID);
typedef ULONG (*SmV_HOOK_FUNC)(ULONG ulMutexID);
typedef ULONG (*DeleteMutex_HOOK_FUNC)(ULONG ulMutexID);

typedef ULONG (*NPDOWNLOAD_FAILED_PROCESS)(ULONG ulMid, ULONG ulNpErrcode, ULONG ulIfIndex, ULONG ulCmdOrType, VOID *pArg);
typedef ULONG (*GetLinkControlPacket_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulSndOrRcv, ULONG ulProtocolType,
                                                ULONG ulSubProtocolType,  MBUF_S *pstBuf);

typedef VOID (*GoNext_HOOK_FUNC)(VOID);

typedef ULONG (*gpfTCPIP_GetTunnelMtu_HOOK_FUNC)(ULONG *pulTunnelMtu, ULONG ulTunnelInfo);

/*******************************************************************************
*    Func Name: TCPIP_Malloc
*  Description: VISP�ڴ����뺯��,Ҫ��COMMON/MBUFģ�鲻�������.�����漰��VOS_Mem_IncRef
*               /VOS_Mem_GetRef�ȴ��ڷ��ʿ��ڴ��׵�ַ��ģ��Ҳ������ͨ���ýӿ��������ڴ�����
*               ����CBBģ��Ҳʹ���˴��ദ��,���Զ�VISP CBBģ�������ڸ��ڴ�������ͷź���
*        Input: ULONG ulInfo:ģ��ID,���贫��VISP֧�ֵ�ģ��ID(��tcpip_id.h�ļ�)
*               ULONG ulSize:������ڴ��С
*       Output: ��
*       Return: ���뵽���ڴ��׵�ַ
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
/*******************************************************************************
*    Func Name: TCPIP_Free
*  Description: VISP�ڴ��ͷź���,��TCPIP_Malloc����ʹ��.Ҫ��MBUFģ�鲻�������.
*               �����漰��VOS_Mem_IncRef/VOS_Mem_GetRef�ȴ��ڷ��ʿ��ڴ��׵�ַ��ģ��Ҳ������ͨ���ýӿ��������ڴ��ͷ�
*               ����CBBģ��Ҳʹ���˴��ദ��,���Զ�VISP CBBģ�������ڸ��ڴ�������ͷź���
*        Input: VOID* pBuf:Ҫ�ͷŵ��ڴ��׵�ַ
*       Output: ��
*       Return: �ɹ�/ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Free(VOID* pBuf);

/*******************************************************************************
*    Func Name: TCPIP_SetMemPid
*  Description: �����ڴ�����ʹ�õ�DOPRA PIDֵ,VISPĬ��ֵΪ0x1234
*        Input: ULONG ulPid:�ڴ�����ʹ�õ�DOPRA PIDֵ
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-16   wuhailan(06310)         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMemPid(USHORT usPid);
typedef ULONG (*TCPIP_LINK_HOOK_FUNC)(struct tagMBuf *pstMBuf);

typedef ULONG (*HA_GETBOARDTYPE_FUNC)(VOID);
typedef VOID* (*HA_MALLOC_FUNC)(ULONG ulModID, ULONG ulLength);
typedef ULONG (*HA_FREE_FUNC)(VOID *pBuf);
typedef ULONG (*HA_GETPHYINITBYTYPE_FUNC)(ULONG ulType, UCHAR * szIfName, ULONG *pfPhyInitial);
typedef ULONG (*HA_GETIFPHYSTATE_FUNC)(ULONG ulIfIndex);
typedef ULONG (*HA_SENDMSG_FUNC)(UCHAR *pMsgBuf, ULONG ulMsgLen);
typedef ULONG (*HA_SLAVEISREADY_FUNC)(VOID);
typedef VOID  (*HA_BADVERNOTIFY_FUNC)(ULONG ulCurrentSysVer, ULONG ulVerInBakMsg);

/* ��ȡ����������ID�Ĺ��Ӻ��� */
typedef ULONG (*SELFTASKID_HOOK)(VOID);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLogOutputHook
*  Description: ע����־���������
*        Input: TCPIP_LOG_HOOK_FUNC  * pfHookFunc: ����ָ�뼯��
*       Output: 
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע�����������ȵ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncLogOutputHook(TCPIP_LOG_HOOK_FUNC *pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDebugOutputHook
*  Description: ע�������Ϣ���������
*        Input: gpfTCPIPDebugOutput pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDebugOutputHook(gpfTCPIPDebugOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncWarningOutputHook
*  Description: ע��澯������
*        Input: gpfTCPIPWarningOutput pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncWarningOutputHook(gpfTCPIPWarningOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncInfoOutputHook
*  Description: ע����Ϣ���������
*        Input: gpfTCPIPInfoOutput pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncInfoOutputHook(gpfTCPIPInfoOutput pstHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncVOSAssertXHook
*  Description: ע��������䴦����
*        Input: gpfVOSAssertX pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncVOSAssertXHook(gpfVOSAssertX pstHookFunc);

typedef VOID (*TCPIP_CC_OUTPUT_HOOK_FUNC)(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCCOutputHook
* Date Created: 2009-3-26
*       Author: zhangchunyu(62474)
*  Description: �û�ע��������ͨ��������溯��
*        Input: TCPIP_CC_OUTPUT_HOOK_FUNC pfHookFun:
*       Output:
*       Return: DCC_SUCCESS:�ɹ�  DCC_FAILED:ע��ָ��Ϊ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-3-26    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCCOutputHook(TCPIP_CC_OUTPUT_HOOK_FUNC pfHookFun);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncUserStopHook
*  Description: ע���û�ֹͣ�����
*        Input: gpfTCPIPUserStop pfHookFunc: ����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncUserStopHook(gpfTCPIPUserStop pstHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreateMutexHook
*  Description: ע���ź������뺯��
*        Input: CreateMutex_HOOK_FUNC pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreateMutexHook(CreateMutex_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncCreateSmHook
*  Description: ע��ͬ���ź������빳�Ӻ���
*        Input: CreateSm_HOOK_FUNC pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-18   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncCreateSmHook(CreateSm_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSmPHook
*  Description: ע���ź�����ȡ����
*        Input: SmP_HOOK_FUNC pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSmPHook(SmP_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncSmVHook
*  Description: ע���ź����ͷź���
*        Input: SmV_HOOK_FUNC pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncSmVHook(SmV_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDeleteMutexHook
*  Description: ע���ź���ɾ������
*        Input: DeleteMutex_HOOK_FUNC pfHookFunc:����ָ��
*       Output:
*       Return: �ɹ�:VOS_OK
*               ʧ��:VOS_ERR
*      Caution: ���ص���������ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncDeleteMutexHook(DeleteMutex_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetBoardTypeHook
*  Description: ע���ȡ�����������ͺ���
*        Input: HA_GETBOARDTYPE_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetBoardTypeHook(HA_GETBOARDTYPE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHAMallocHook
*  Description: ע��HA�����ڴ����뺯��
*        Input: HA_MALLOC_FUNC  pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHAMallocHook(HA_MALLOC_FUNC  pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHAFreeHook
*  Description: ע��HA�����ڴ��ͷź���
*        Input: HA_FREE_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHAFreeHook(HA_FREE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetPhyInitByTypeHook
*  Description: ע���ȡ�ӿڵײ��ʼ������ָ��ĺ���
*        Input: HA_GETPHYINITBYTYPE_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetPhyInitByTypeHook(HA_GETPHYINITBYTYPE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetIfPhyStateHook
*  Description: ע���ȡ�ӿڵײ�״̬����
*        Input: HA_GETIFPHYSTATE_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetIfPhyStateHook(HA_GETIFPHYSTATE_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHASendMsgHook
*  Description: ע�ᱸ����Ϣ���ͺ���
*        Input: HA_SENDMSG_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHASendMsgHook(HA_SENDMSG_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHASlaveIsReadyHook
*  Description: ע���ѯ�����Ƿ�����ĺ���
*        Input: HA_SLAVEISREADY_FUNC pfFunc: ����ָ��
*       Output:
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ʧ��
*      Caution: ���ص���������ע�ᣬ�Ҳ���ע��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHASlaveIsReadyHook(HA_SLAVEISREADY_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncHABadVerNotifyHook
*  Description: ע��HA�汾��У��ʧ�ܵ�֪ͨ����
*        Input: HA_BADVERNOTIFY_FUNC pfFunc: HA�汾��У��ʧ�ܵ�֪ͨ����
*       Output: 
*       Return: VOS_OK �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-15  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncHABadVerNotifyHook(HA_BADVERNOTIFY_FUNC pfFunc);
/*******************************************************************************
*    Func Name: TCPIP_HA_RegisterCallBack
*  Description: HA�ص�֪ͨ����ע��ӿ�
*        Input:
*               pfBatchCallBack  : �ص�����ָ��
*       Output: ��
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*
*******************************************************************************/
extern ULONG TCPIP_HA_RegisterCallBack (TCPIP_HA_CALLBACK_S  * pfBatchCallBack);


extern ULONG TCPIP_HA_NotifySwitch(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_SlavePlugOut
*  Description: ����γ�����ӿ�(��������)
*        Input: VOID
*       Output: ��
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*   2007-04-04  xiehuaguo       modify by defect A82D13585
*
*******************************************************************************/
extern ULONG TCPIP_HA_SlavePlugOut(VOID);

extern ULONG TCPIP_HA_VerifyInterface(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_HA_BatchBackup
*  Description: VISP HA�������ݴ��������(��������)
*        Input: VOID
*       Output: ��
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution:
*------------------------------------------------------------------------------*
* Modification History
*  DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*  2006-12-04  xiehuaguo       create
*  2007-07-30  jiangtao(51916) modify
*
*******************************************************************************/
extern ULONG TCPIP_HA_BatchBackup(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_Smooth
*  Description: VISP HAƽ��������(������Ϊ����ʱ����)
*        Input: VOID
*       Output: ��
*       Return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*      Caution:
*------------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------------*
*   2006-12-04  xiehuaguo       create
*
*******************************************************************************/
extern ULONG TCPIP_HA_Smooth(VOID);

extern ULONG TCPIP_HA_VerifySocket(LONG lSocketID);

extern ULONG TCPIP_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
/*******************************************************************************
*    Func Name: TCPIP_HA_BadVerNotify
*  Description: ����֪ͨHA������Ϣ�İ汾�Ŵ��󣬿ɹ�ʹ��VISP HA���Ƶ��ⲿģ��(����IPOA HA)����
*        Input: ULONG ulCurrentHAVer:  ģ�鵱ǰ��HA�汾��
*               ULONG ulBadVerInBakMsg: �յ��ı�����Ϣ��Я����HA�汾��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern VOID  TCPIP_HA_BadVerNotify(ULONG ulCurrentSysVer, ULONG ulVerInBakMsg);

/*************************************************************************
*    Func Name: TCPIP_HA_GetStat
*  Description: VISP HAͳ����Ϣ��ȡ�ӿ�
*        Input: ��
*       Output: HAStat_S *pstStat HAͳ����Ϣ
*       return: VOS_OK  �ɹ�
*               VOS_ERR ʧ��
*         Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*
*************************************************************************/
extern ULONG TCPIP_HA_GetStat(HASTAT_S *pstStat);
/*************************************************************************
*    Func Name: TCPIP_HA_ResetStat
*  Description: VISP HAͳ����Ϣ����ӿ�
*        Input: VOID
*       Output: ��
*       return:
*      Caution:
*------------------------------------------------------------------------*
*  Modification History
*   DATE        NAME            DESCRIPTION
*------------------------------------------------------------------------*
*   2006-12-06  zhangchunyu(62474)     Create
*
*************************************************************************/
extern VOID  TCPIP_HA_ResetStat(VOID);

extern ULONG TCPIP_HA_SetAllDbg(ULONG ulDbg);

extern ULONG TCPIP_HA_GetDbg(HADBG_S *pstDbg);

/*******************************************************************************
*    Func Name: TCPIP_HA_RegisterModule
*  Description: register Ha back_up module
*        Input: ULONG ulLayer: registe layer number(0-2)
*               ULONG ulModId: module id
*               ULONG ulPriority: the calling of ha register module is sequence
*               UCHAR *pucModuleName: module name
*               TCPIP_HA_MODULE_CALLBACK_S pstModCallback: register
*       Output: ULONG *pulModId: return to the register to identify a ha module
*       Return:
*              HA_REGISTER_TOO_MUCH_ERR   2
*              HA_NAME_TO_LONG_ERR        3
*              HA_REGISTER_LAYER_ERR      4
*              HA_MODULE_ID_NULL_ERR      5
*              HA_CALL_BACK_NULL_ERR      6
*              HA_CALL_HA_INPUT_NULL_ERR  7
*              VOS_MALLOC_FAILED_1        8
*              VOS_MALLOC_FAILED_2        9
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-28   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_RegisterModule(ULONG ulLayer, ULONG ulModId, ULONG ulPriority, UCHAR *pucModuleName,
                                         TCPIP_HA_MODULE_CALLBACK_S *pstModCallback);

extern VOID TCPIP_HA_TravelRegisteredLayer(ULONG ulLayer);
/*******************************************************************************
*    Func Name: TCPIP_HA_ModuleSendMsg
*  Description: send ha packet interface for every module except transmit layer
*        Input: UCHAR *pucData:
*               ULONG ulDataLen:
*       Output:
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_ModuleSendMsg(UCHAR *pucData, ULONG ulDataLen);
/*******************************************************************************
*    Func Name: TCPIP_HA_GetIsSmoothOrManual
*  Description: obtain the smooth and manual status
*        Input: VOID
*       Output:
*       Return: 1: in smoothing or manualing
*               0: on the contrary
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetIsSmoothOrManual(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_BeforeSmooth
*  Description: obtain the status of smooth
*        Input: VOID
*       Output:
*       Return: 1: smoothed
*               0: unsmoothed
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_BeforeSmooth(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_InitComplete
*  Description: obtain the ha initialization status
*        Input: VOID
*       Output:
*       Return: 1: initializtion
*               0: uninitializtion
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_InitComplete(VOID);
/*******************************************************************************
*    Func Name: TCPIP_HA_CanSendPack
*  Description: checking the moudle sending status
*        Input: ULONG ulModeId: the ha module id for checking the moudle sending status
*       Output:
*       Return: 1: can send HA packet
*               0: can't send HA packet
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-30   jiangtao(51916)         Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_CanSendPack(ULONG ulModeId);

/*******************************************************************************
*    Func Name: TCPIP_HA_SetCksumSwitch
*  Description: ���÷���HA������Ϣʱ�Ƿ����У���
*        Input: ULONG ulOpenOrClose: 0-������, 1-����
*       Output: 
*       Return: VOS_OK �ɹ�  VOS_ERR ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_HA_SetCksumSwitch(ULONG ulOpenOrClose);
/*******************************************************************************
*    Func Name: TCPIP_HA_GetCksumSwitch
*  Description: ��ȡ�Ƿ����HA������ϢУ��͵Ŀ���
*        Input: VOID
*       Output: 
*       Return: ����ֵ: 0-������, 1-����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-3-17  wujie(61195)      Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetCksumSwitch(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetPublicHADbg
*  Description: ���õ��Կ���
*        Input: ULONG ulDbg: ���õĵ��Կ���ֵ1--����0--��
*       Output: ��
*       Return: �ɹ�: VOS_OK
                ʧ��: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPublicHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPublicHADbg
*  Description: ��ȡ���Կ��ص�ֵ
*        Input: ULONG *pulDbg   ��Ҫ����ֵ��ָ��
*       Output: ULONG *pulDbg   �Ѿ�����ֵ��ָ��
*       Return: �ɹ�: VOS_OK
                ʧ��: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPublicHADbg(ULONG *pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetPublicHAVerboseDbg
*  Description: ����HA���ĵ��Կ��صĽӿ�
*        Input: ULONG ulDbg: ���õĵ��Կ���ֵ
*       Output: ��
*       Return: �ɹ�: VOS_OK
                ʧ��: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetPublicHAVerboseDbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetPublicHAVerboseDbg
*  Description: ��ȡHA���ĵ��Կ��صĽӿ�
*        Input: ULONG *pulDbg ��Ҫ����ֵ��ָ��
*       Output: ULONG *pulDbg �Ѿ�����ֵ��ָ��
*       Return: �ɹ�: VOS_OK
                ʧ��: VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetPublicHAVerboseDbg(ULONG *pulDbg);


extern ULONG TCPIP_PPI_HookRegister(TCPIP_PPI_HOOK_S *pstHookFunc);

ULONG TCPIP_PPI_HookRegisterByType(ULONG ulType, VOID *pfHook);


extern ULONG TCPIP_PPI_Count_Get(TCPIP_PPI_COUNT_S *pstCount);

extern ULONG TCPIP_PPI_Count_Reset(VOID);

extern ULONG TCPIP_SetPpiDebugSwitch(ULONG ulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_GetPpiDebugSwitch
*  Description: ��ȡPPI���Կ���
*        Input:
*       Output: ULONG* pulSwitch: PPI����
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPpiDebugSwitch(ULONG* pulSwitch);

/* ���úͻ�ȡ���Ķ�����󻺴��� */
/*******************************************************************************
*    Func Name: TCPIP_SetMaxCachedPkt
*  Description: �û�������󻺴汨�����Ľӿ�
*        Input: ULONG ulMax:�û�����ֵ����Χ0--1024������0ʱȡVISPĬ��ֵ128
*       Output: 
*       Return: �ɹ�:VOS_OK
                ʧ��:������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_SetMaxCachedPkt(ULONG ulMax);
/*******************************************************************************
*    Func Name: TCPIP_GetMaxCachedPkt
*  Description: ��ȡ���Ļ�����������ֵN_Max
*        Input: ULONG* pulMax:��ŵ�N_Max��ָ���ַ
*       Output: ULONG* pulMax: N_Max��ֵ
*       Return: �ɹ�:VOS_OK
                ʧ��:������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMaxCachedPkt(ULONG* pulMax);
/*******************************************************************************
*    Func Name: TCPIP_GetCurCachedPkt
*  Description: ��ȡ��ǰNֵ
*        Input: ULONG* pulCurrent:��ŵ�Nֵ��ָ���ַ
*       Output: ULONG* pulCurrent: N��ֵ
*       Return: �ɹ�:VOS_OK
                ʧ��:������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-27   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_GetCurCachedPkt(ULONG* pulCurrent);

/* ȫ�ֵ��Ժ��� */

extern VOID TCPIP_ShowARP(VOID);

extern VOID TCPIP_ShowCompInfo(VOID);

extern VOID TCPIP_ShowFIB(VOID);

extern VOID TCPIP_ShowInterface(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowInterfaceBriefInfo
*  Description: ��ѯ�ӿڼ�Ҫ��Ϣ
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-28    sunmo(44939)     Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowInterfaceBriefInfo(VOID);

extern VOID TCPIP_ShowIPAddr(VOID);

extern VOID TCPIP_ShowNetStatus(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowPacketStatics
*  Description: ��ѯ����ͳ����Ϣ
*        Input: ULONG ulMid, ģ��ID
*               ULONG ulIfIndex, �ӿ�����
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-28    sunmo(44939)     Create the first version.
*  2006-5-17    sunmo(44939)     Modify output info format.
*  2007-5-17    wujie(61195)     Modified for A82D15480����ʾ�����޷���ֵ
*
*******************************************************************************/
extern VOID TCPIP_ShowPacketStatics(ULONG ulMid, ULONG ulIfIndex);

extern VOID TCPIP_ShowPPPNegoInfo(VOID);

extern VOID TCPIP_ShowPPPState(VOID);

extern VOID TCPIP_ShowPreConfig(VOID);

extern VOID TCPIP_ShowRIB(VOID);

extern VOID TCPIP_ShowRunInfo(VOID);

extern VOID TCPIP_ShowVersion(VOID);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_ShowRIBByVrf
*  Description: ��ʾָ��VRF��RIB����
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowRIBByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowFIBByVrf
*  Description: ��ʾָ��VRF��FIB����
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowFIBByVrf(CHAR *pszVrfName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPAddrByVrf
*  Description: ��ʾָ��VRF�ĵ�ַ��Ϣ
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-01  qinyun           Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowIPAddrByVrf(CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

extern ULONG TCPIP_Set_ICDbgLevel(ULONG ulLevel);
/*******************************************************************************
*    Func Name: TCPIP_Get_ICDbgLevel
*  Description: ��ȡVISP����Ϣ����ȼ�
*        Input: ULONG *pulLevel:
*       Output:
*       Return: �ɹ�����VOS_OK, ʧ�ܷ���VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-11-19   zhanghuihui(55157)      Create
*
*******************************************************************************/
extern ULONG TCPIP_Get_ICDbgLevel(ULONG *pulLevel);

extern ULONG TCPIP_SetPacketTrace(ULONG ulMid, ULONG ulEnable);

extern ULONG TCPIP_SetDebugLevel(ULONG ulMid, ULONG ulDebugLevel);
/*******************************************************************************
*    Func Name: TCPIP_GetDebugLevel
*  Description: ��ȡģ����Լ���
*        Input: ULONG ulMid:
*
*       Output: ULONG* pulDebugLevel:
*       Return: VOS_OK
*               V0S_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetDebugLevel(ULONG ulMid, ULONG* pulDebugLevel);

/*******************************************************************************
*    Func Name: TCPIP_SetLogType
*  Description: ��־����������ƽӿ�
*        Input: ULONG ulWarningEnable:�澯��־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*               ULONG ulCfgEnable:������־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*               ULONG ulRunEnable:������־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*       Output: ��
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLogType(ULONG ulWarningEnable, ULONG ulCfgEnable, ULONG ulRunEnable);
/*******************************************************************************
*    Func Name: TCPIP_GetLogType
*  Description: ��ȡ��־����ֵ
*        Input: ��
*       Output: ULONG* pulWarningEnable:Ҫ��ȡ�ĸ澯��־����ֵ,1ʹ��,0ȥʹ��
*               ULONG* pulCfgEnable:Ҫ��ȡ�Ĳ�����־����ֵ,1ʹ��,0ȥʹ��
*               ULONG* pulRunEnable:Ҫ��ȡ��������־����ֵ,1ʹ��,0ȥʹ��
*       Return: �ɹ�VOS_OK;ʧ��VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLogType(ULONG* pulWarningEnable, ULONG* pulCfgEnable, ULONG* pulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_SetLogTypeNoLevelLimit
* Date Created: 2010-07-22
*       Author: liangjicheng
*  Description: ��־����������ƽӿ�-����Level����
*        Input: ULONG ulWarningEnable:�澯��־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*               ULONG ulCfgEnable:������־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*               ULONG ulRunEnable:������־ʹ�ܿ���,0 ȥʹ��,1 ʹ��
*       Output: ��
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-22   liangjicheng            Create BC3D03507 ��ǿ��־����
*******************************************************************************/
ULONG TCPIP_SetLogTypeNoLevelLimit(ULONG ulWarningEnable, ULONG ulCfgEnable, ULONG ulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_GetLogTypeNoLevelLimit
* Date Created: 2010-07-22
*       Author: liangjicheng
*  Description: ��ȡ����Level���Ƶ���־����ֵ
*        Input: ��
*       Output: ULONG* pulWarningEnable:Ҫ��ȡ�ĸ澯��־����ֵ,1ʹ��,0ȥʹ��
*               ULONG* pulCfgEnable:Ҫ��ȡ�Ĳ�����־����ֵ,1ʹ��,0ȥʹ��
*               ULONG* pulRunEnable:Ҫ��ȡ��������־����ֵ,1ʹ��,0ȥʹ��
*       Return: �ɹ�VOS_OK;ʧ��VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-22   liangjicheng            Create BC3D03507 ��ǿ��־����
*
*******************************************************************************/
ULONG TCPIP_GetLogTypeNoLevelLimit(ULONG* pulWarningEnable, ULONG* pulCfgEnable, ULONG* pulRunEnable);

/*******************************************************************************
*    Func Name: TCPIP_SetLogLevel
* Date Created: 2006-4-29
*       Author: wuhailan(HT06310)
*  Description: ����Ҫ��¼����־��Ϣ�ļ���
*        Input: ULONG ulLogLevel:LOG��Ϣ�ȼ�.VISP��־�����Ϊ�������:
*               0 TCPIP_LOG_LEVEL_CRITICAL,1 TCPIP_LOG_LEVEL_ERROR,2 TCPIP_LOG_LEVEL_WARNING,
*               3 TCPIP_LOG_LEVEL_INFO,4 TCPIP_LOG_LEVEL_DEBUG,VISPĬ��ΪINFO����.
*       Output: ��
*       Return: �ɹ� 0,ʧ�� 1
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2006-4-29  wuhailan(06310)   Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetLogLevel(ULONG ulLogLevel);

/*******************************************************************************
*    Func Name: TCPIP_GetLogLevel
* Date Created: 2007-7-27
*       Author: mafeng(59090)
*  Description: ��ȡ��¼��־��Ϣ�ļ���
*        Input: 
*       Output: ULONG* pulLogLevel:VISP��־�����Ϊ�������:
*               0 TCPIP_LOG_LEVEL_CRITICAL,1 TCPIP_LOG_LEVEL_ERROR,2 TCPIP_LOG_LEVEL_WARNING,
*               3 TCPIP_LOG_LEVEL_INFO,4 TCPIP_LOG_LEVEL_DEBUG,VISPĬ��ΪINFO����.
*       Return: VOS_OK
*               VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-7-27    mafeng(59090)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetLogLevel(ULONG* pulLogLevel);

/*******************************************************************************
*    Func Name: TCPIP_ShowHASmoothCost
*  Description: ��ʾ����HAƽ��ʱ��ʱ�估TICK��ֵ
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-14   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowHASmoothCost(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowHAStatistic
*  Description: ��ʾHAͳ����Ϣ
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowHAStatistic(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPCount
*  Description: ��ʾNP�·�ͳ����Ϣ
*        Input:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPCount(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPRegisterInfo
*  Description: ��ʾNP���Ӻ���ע�����
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-08   zhoutong(43740)         Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPRegisterInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ComputeNPUpdateCost
*  Description: ʹ�ܼ���NP�·�ʱ�ӿ���
*        Input: ULONG ulSetYes:ʹ�ܿ���:1ʹ��,0ȥʹ��
*       Output: ��
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_ComputeNPUpdateCost(ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_ShowNPUpdateCost
*  Description: ��ʾNP�·���ʱ��Ϣ
*        Input: ��
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowNPUpdateCost(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetMemInfoByMid
*  Description: ��ȡָ��ģ����ڴ�ͳ��ֵ,���ulMid��0����Ϊ��ȡ�ܵ�ͳ����Ϣ
*               ����MBUFģ��ͳ���޷���ȡ,����ͨ��MBUF�ṩ�Ľӿڲ鿴DB��ʹ�����
*        Input: ULONG ulMid:ģ��ID
*       Output: ULONG *pulSize:����ָ����ģ���ڴ�ͳ��ֵ
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetMemInfoByMid(ULONG ulMid,ULONG *pulSize);
/*******************************************************************************
*    Func Name: TCPIP_ShowMemInfo
*  Description: ��ʾ��ģ���ڴ�ͳ�������Ϣ,����MBUF���ֻ��ͳ����ʾMBUF CACHE��
*               ��HEAD/DBD/DB����Ŀ,���û�����MBUF CACHE֧�ֵ������,���޷�ͳ��.
*        Input: ��
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowMemInfo(VOID);


extern VOID TCPIP_ShowMbufInfo(VOID);


extern ULONG TCPIP_SystemEntry(VOID);

extern ULONG TCPIP_Set_PreConfigPara(ULONG ulKey, ULONG ulValue);

extern LONG  TCPIP_GetVersion(CHAR *pVerInfo);

/*******************************************************************************
*    Func Name: TCPIP_EnMBufQueue
*  Description: ��MBUF��������ָ���ı��Ķ���
*        Input: MBUF_S* pMBuf:����ָ��
*               ULONG ulQueueID: ����ID
*               ulIfIndex: ��ӿ�����
*       Output:
*       Return: PUBLIC_ERR_MBUF_NULL ����Ϊ��
*               PUBLIC_ERR_QUEUE_ID  ���Ķ��зǷ�
*               VOS_ERR              ʧ��
*               VOS_OK               �ɹ�
*      Caution: ���������·����У���ӿ�����Ϊ�յ����ĵ�����ӿڵ�������
*               ��������������У���ӿ�����Ϊ·�ɿɼ��ӿڵ�������
*               �ú������۳ɹ����,���Ķ��ɸú����ڲ��ͷ�,�����߲������ͷű���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-17   zhoutong(43740)         Create
*
*******************************************************************************/
extern ULONG TCPIP_EnMBufQueue(MBUF_S* pMBuf, ULONG ulQueueID,ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLinkHook
*  Description: ��·�㹳�ӽ��ע�ắ��
*        Input: ULONG ulType:ע������,1���շ���,2���ͷ���
*               TCPIP_LINK_HOOK_FUNC pfHook:����ָ��
*               ULONG ulPriority:���ȼ�,���ȼ��ߵĲ��������ǰ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncLinkHook(ULONG ulType, TCPIP_LINK_HOOK_FUNC pfHook, ULONG ulPriority);
/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncLinkHook
*  Description: ��·�㹳�ӽ��ע������
*        Input: ULONG ulType:ע������,1���շ���,2���ͷ���
*               TCPIP_LINK_HOOK_FUNC pfHook:����ָ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-15   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_UnRegFuncLinkHook(ULONG ulType, TCPIP_LINK_HOOK_FUNC pfHook);

/***********************�����Ż��ṩ���û��ӿ�***********************/

/* �����Ż��û��ӿڷ��صĴ����� */
enum tagOPTErrCode
{
    OPTIM_OK = VOS_OK,
    OPTIM_ERR = VOS_ERR,
    OPTIM_ERR_HA_IS_SMOOTHING,       /* 2, HA�����ֶ���ƽ���� */
    OPTIM_ERR_FILTER,                /* 3, NPδ������ */
    OPTIM_ERR_ST_PARAM,              /* 4, ʹ���Ż���������(0/1֮��) */
    OPTIM_ERR_SUM_PARAM,             /* 5, ʹ�ܻ������������������ */
    OPTIM_ERR_RTMODE,                /* 6, ·��ģʽԤ���ò�����ʹ���Ż� */
    OPTIM_ERR_SKTMODE,               /* 7, socket��ȫ��ģʽ������ʹ���Ż� */
    OPTIM_ERR_MEMORY,                /* 8, ���仺������ڴ���Դʧ�� */
    OPTIM_ERR_TIMER,                 /* 9, ���������ˢ�¶�ʱ��ʧ�� */
    OPTIM_ERR_DISABLE,               /* 10, δʹ�������Ż� */
    OPTIM_ERR_HOOK_NULL,             /* 11, δע�ṳ�Ӵ����� */
    OPTIM_ERR_ENTRY_NULL,            /* 12, δ���ҵ�������� */
    OPTIM_ERR_VRF_INIT,              /* 13, ʹ��VRF���ܽ��������Ż� */
};

typedef ULONG(*OPTIM_INTERMEDIATE_HOOK_FUNC)(ULONG ulPktFlowType, MBUF_S *pstMbuf);

/* IP��������Ԫ�����Ϣnetwork seq */
typedef struct tagTcpipOptimIpInfo
{
    ULONG ulSIP;    /* Դ��ַ */
    ULONG ulDIP;    /* Ŀ�ĵ�ַ */
    USHORT usSP;    /* Դ�˿ں� */
    USHORT usDP;    /* Ŀ�Ķ˿ں� */
    UCHAR ucPID;    /* Э��� */
    UCHAR ucPadding[3];
}TCPIP_OPTIMIPINFO_S;


/* �û���ȡ���������Ϣ���ݽṹ */
typedef struct tagTcpipOptimEntryInfo
{
    /* 1, host receive, 2, forward, 3, host send */
    UCHAR ucCacheType; /* SEND/RECEIVE/FORWARD */

    /* 17:udp,6:tcp,0:rawip,17:iwf */
    UCHAR ucPktType;   /* UDP/TCP/RAWIP/IWF */
    UCHAR ucNPFlag;    /* NP flag */
    UCHAR ucTmFlag;    /* time �ϻ���־*/

    LONG  iFd;            /* visp rcv/send skt id  */
    ULONG ulOutIfIndex;   /* snd ifnet index */
    ULONG ulVLINKIndex;   /* vlink index */
    ULONG ulNextHop;      /* next hop,network seq */

    TCPIP_OPTIMIPINFO_S stOptIpInfo; /* SIP/DIP/SP/DP/PID */
}TCPIP_OPTENTRYINFO_S;

/* �����Ż�����ͳ�����ݽṹ */
typedef struct tagOptimStat
{
    ULONG   ulUdpRcv;   /* UDP received */
    ULONG   ulIWFRcv;   /* IWF received */
    ULONG   ulTcpRcv;   /* TCP received */
    ULONG   ulRipRcv;   /* RIP received */
    ULONG   ulEthRcv;   /* ETH received */
    ULONG   ulNoEthRcv; /* PPP received */
    ULONG   ulNPRcv;    /* NP received */

    ULONG   ulUdpSnd;   /* UDP Send */
    ULONG   ulTcpSnd;   /* TCP Send */
    ULONG   ulRipSnd;   /* RIP Send */
    ULONG   ulIWFSnd;   /* IWF Send */
    ULONG   ulEthSnd;   /* ETH Send */
    ULONG   ulNoEthSnd; /* No ETH Send */
    ULONG   ulPPISnd;   /* PPI Send */

    ULONG   ulNoOpt_E;  /* NoOptim_NoEntry */
}TCPIP_OPTIMSTAT_S;

/*******************************************************************************
*    Func Name: TCPIP_ClearOptimStatics
*  Description: ���Э��ջ�����Ż�ͳ����Ϣ
*        Input: VOID
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR_DISABLE
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_ClearOptimStatics(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetOptDbgSwitch
*  Description: ��ȡ�����Ż����Կ���״̬
*        Input: ULONG *pulOptDebug:���ص��Կ���״̬
*       Output: pulOptDebug:�����Ż����Կ���״̬
*       Return: OPTIM_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptDbgSwitch(ULONG *pulOptDebug);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimFlag
*  Description: ��ȡЭ��ջ����ʹ��/ȥʹ��״̬
*        Input: ULONG* pulFlag:�����Ż�ʹ�ܱ�־
*               ULONG *pulOptEntryNum:�����Ż����û����������
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimFlag(ULONG* pulFlag, ULONG *pulOptEntryNum);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimStatics
*  Description: ��ȡЭ��ջ�����Ż�ͳ����Ϣ
*        Input: TCPIP_OPTIMSTAT_S* pstOptStat: �����Ż�����ͳ����Ϣָ��
*       Output:
*       Return: OPTIM_OK
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimStatics(TCPIP_OPTIMSTAT_S* pstOptStat);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncOptimHook
*  Description: �û�ע�������Ż��м䴦���Ӻ���(ע��/��ע��)
*        Input: OPTIM_INTERMEDIATE_HOOK_FUNC pfHookFuc:
*                  �û�ע��Ĺ��Ӵ�����ָ�룬Ϊ�����ʶ��ע��
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR_HOOK_NULL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncOptimHook(OPTIM_INTERMEDIATE_HOOK_FUNC pfHookFuc);
/*******************************************************************************
*    Func Name: TCPIP_SetOptDbgSwitch
*  Description: ���õ��Կ���״̬
*        Input: ULONG ulOptDebug:��־���Կ���״̬(1:�򿪵��Կ���,0:�رյ��Կ���)
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetOptDbgSwitch(ULONG ulOptDebug);
/*******************************************************************************
*    Func Name: TCPIP_SetOptimFlag
*  Description: ����Э��ջ�����Ż�ʹ��/ȥʹ��(1:ʹ��/0:ȥʹ��)
*        Input: ULONG ulEnableFlag: 1:ʹ�� 0:ȥʹ��
*               ULONG ulOptEntryNum: �����Ż����������(0�û�ȱʡ/32-1024)
*       Output:
*       Return: VOS_OK
*               OPTIM_ERR_HA_IS_SMOOTHING
*               OPTIM_ERR_ST_PARAM
*               OPTIM_ERR_RTMODE
*               OPTIM_ERR_SKTMODE
*               OPTIM_ERR_MEMORY
*               OPTIM_ERR_TIMER
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetOptimFlag(ULONG ulEnableFlag, ULONG ulOptEntryNum);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimFlag
*  Description: ��ʾ�����Ż�ʹ��״̬
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-04   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowOptimFlag(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimStatics
*  Description: ��ʾЭ��ջ�����Ż�ͳ����Ϣ
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID  TCPIP_ShowOptimStatics(VOID);
/*******************************************************************************
*    Func Name: TCPIP_GetOptimEntryInfo
*  Description: �û�������Ԫ����Ϣ��ȡ���������Ϣ
*        Input: TCPIP_OPTIPINFO_S *pstOptIpInfo:��Ԫ����Ϣ
*       Output: TCPIP_OPTENTRYINFO_S *pstOptEntryInfo:���������Ϣ
*       Return: OPTIM_OK
*               OPTIM_ERR
*               OPTIM_ERR_DISABLE
*               OPTIM_ERR_ENTRY_NULL
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetOptimEntryInfo(TCPIP_OPTIMIPINFO_S *pstOptIpInfo, TCPIP_OPTENTRYINFO_S *pstOptEntryInfo);
/*******************************************************************************
*    Func Name: TCPIP_ShowOptimEntryInfo
*  Description: ��������ʾ�������������Ϣ
*        Input: ULONG ulEntryType:��������-1��ת��-2����������-3���໺�����
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-25   mafeng(59090)           Create
*
*******************************************************************************/
extern VOID TCPIP_ShowOptimEntryInfo(ULONG ulEntryType);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncNPDownloadFailedProcFunc
*  Description: ע�ṳ�Ӻ���, ���NP�·�ʧ��, VISP����ô˹��Ӻ�������֪ͨ
*        Input: NPDOWNLOAD_FAILED_PROCESS pfHookFunc: ���Ӻ���
*       Output: 
*       Return: VOS_OK �ɹ�  VOS_ERR ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-15  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncNPDownloadFailedProcFunc( NPDOWNLOAD_FAILED_PROCESS pfHookFunc );


extern ULONG TCPIP_HDR_Init(ULONG ulTaskPri,ULONG ulTaskStackSize);


extern ULONG TCPIP_Health_Checkup(ULONG ulSwitch, ULONG ulTimer, ULONG ulHeadthBatchFlag);

typedef ULONG (*TCPIP_HEALTH_OUTPUT_HOOK_FUNC)(CHAR *pcBuf, ULONG ulMsglen, ULONG ulScanId);

extern ULONG TCPIP_RegFuncHealthOutputHook(TCPIP_HEALTH_OUTPUT_HOOK_FUNC pfFunc);

typedef ULONG (*TCPIP_LASTWORD_OUTPUT_HOOK_FUNC)(CHAR *pcMemAddr, ULONG ulMemlen);

extern ULONG TCPIP_RegFuncLastWordOutputHook(TCPIP_LASTWORD_OUTPUT_HOOK_FUNC pfFunc);


extern ULONG TCPIP_LastWord_Checkup(ULONG ulMemSize,ULONG ulLastWordBatchFlag);


extern ULONG TCPIP_RegFuncGetLinkControlPacketHook(GetLinkControlPacket_HOOK_FUNC  pfHookFunc);


extern ULONG TCPIP_UnRegFuncGetLinkControlPacketHook(VOID);


extern ULONG TCPIP_SetResLimitRestrainTime(ULONG ulTime);

/*******************************************************************************
*    Func Name: TCPIP_ClearMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: ����ڴ����ͳ��
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ClearMemErrInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: ��ʾ�ڴ������Ϣ
*        Input: VOID
*       Output: ��
*       Return: VOID
*      Caution: Ŀǰ��¼���������Ϣֻ���һ������,������չ��Ҫ�޸ĸú���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowMemErrInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_GetMemErrInfo
* Date Created: 2008-12-13
*       Author: zhangchunyu(62474)
*  Description: ��ȡ�ڴ����ͳ����Ϣ
*        Input: MEMERRSTAT_S *pstMemErrStat:
*       Output: pstMemErrStat�ڴ����ͳ����Ϣ
*       Return: VOS_OK,�ɹ�, ����,ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-13    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetMemErrInfo(MEMERRSTAT_S * pstMemErrStat);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGoNextHook
* Date Created: 2009-03-04
*       Author: wangbin (62223)
*  Description: ע��֪ͨdopra��һ�׶���������
*        Input: VOID
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-04   wangbin (62223)         Create
*
*******************************************************************************/

extern ULONG TCPIP_RegFuncGoNextHook(GoNext_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_PrintToCOM
* Date Created: 2008-9-28
*       Author: wujie(61195)
*  Description: ������־��������Ϣ����ʾ��Ϣ�Ƿ��ӡ��com��
*        Input: ULONG ulSwitch:
*               bit 0: �Ƿ����������־��com�� 0 ��  1 ��
*               bit 1: �Ƿ�����䳤��־��com�� 0 ��  1 ��
*               bit 2: �Ƿ����������Ϣ��com�� 0 ��  1 ��
*               bit 3: �Ƿ������ʾ��Ϣ��com�� 0 ��  1 ��
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-9-28   wujie(61195)     Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_OutputToCOM(ULONG ulSwitch);


/*******************************************************************************
*    Func Name: TCPIP_SetSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: ����sockrun���񵥴ε��ȱ��Ĵ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSockRunSchedNum( ULONG ulSockRunSchedNum );

/*******************************************************************************
*    Func Name: TCPIP_GetSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: ��ȡsockrun���񵥴ε��ȱ��Ĵ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSockRunSchedNum( ULONG* pulSockRunSchedNum );

/*******************************************************************************
*    Func Name: TCPIP_ShowSockRunSchedNum
* Date Created: 2008-08-05
*       Author: fangpu
*  Description: ��ʾsockrun���񵥴ε��ȱ��Ĵ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-05   fangpu                Create
*
*******************************************************************************/
extern ULONG TCPIP_ShowSockRunSchedNum( VOID );

/*********************************ȫ�ֱ�������********************************/


extern ULONG TCPIP_GetInterfaceInfo(ULONG ulIfIndex,CHAR *szBuf,ULONG ulBufLen,ULONG *pulLen);



extern ULONG TCPIP_RegFuncTrrtUserStopHook(gpfTCPIPTrrtUserStopEx pfHookFunc);




extern ULONG TCPIP_RegFuncPingUserStopHook(gpfTCPIPPingUserStopEx pfHookFunc);


/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetTunnelMtuHook
* Date Created: 2009-11-19
*       Author: zhangchunyu(62474)
*  Description: ע���Ʒ��ȡ���MTU
*        Input: gpfTCPIP_GetTunnelMtu_HOOK_FUNC pfHookFunc: ��ȡ���
*       Output:
*       Return: �ɹ�VOS_OK
*               ʧ��VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-19    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetTunnelMtuHook(gpfTCPIP_GetTunnelMtu_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncRebootModeHook
* Date Created: 2008-8-15
*       Author: zhangchunyu(62474)
*  Description: ע�᱾���������Ӻ���
*        Input: TCPIP_REBOOT_MODE_HOOK_FUNC pfHookFuc: ʵ�ֱ���������ʽ���Ӻ���
*       Output:
*       Return: GR_SUCCESS: �ɹ� ����: ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-15    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncRebootModeHook(TCPIP_REBOOT_MODE_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_GetInterfaceInfoByIfIndex
* Date Created: 2008-8-16
*       Author: zhangchunyu(62474)
*  Description: ����IFINDEX��ѯ�˿����Ͷ˿ںŵ�API����
*        Input: ULONG ulIfIndex:�ӿ�����
*
*       Output: ULONG *pulPortType:�ӿ�����
*               ULONG *pulPortNo:�ӿں�
*       Return: GR_SUCCESS: �ɹ�, ����: ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-16    zhangchunyu(62474)     Creat the first version.
*******************************************************************************/
ULONG TCPIP_GetInterfaceInfoByIfIndex(ULONG ulIfIndex, ULONG *pulPortType, ULONG *pulPortNo);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetSockMaxNum
* Date Created: 2009-10-22
*       Author: LY(57500)
*  Description: ��Ʒע��VISP�ܴ��������socket�������Ӻ���
*        Input: gpfGetSockMaxNum pfHookFunc:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-22    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetSockMaxNum(gpfGetSockMaxNum pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncRegAllAppInfo
* Date Created: 2014-11-26
*       Author: yanlei00216869
*  Description: ��Ʒע�����ע��Ĺ��Ӻ���
*        Input: gpfRegAllAppInfo pfHookFunc
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-26   yanlei00216869   Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncRegAllAppInfo(gpfRegAllAppInfo pfHookFunc);


/*******************************************************************************
*    Func Name: TCPIP_ShowAllVpnArpInfo
* Date Created: 2008-5-15
*       Author: zhangchunyu(62474)
*  Description: ��ʾ����ARP����ں���ETHARP_ShowArpInfo������������ʾVPN ��Ϣ��VLAN ID��Ϣ
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-15    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVpnArpInfo(VOID);

/*******************************************************************************
*    Func Name: TCPIP_ShowAllVrfIPAddr
* Date Created: 2008-5-14
*       Author: zhangchunyu(62474)
*  Description: ��ʾ����ʵ���µĵ�ַ
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowAllVrfIPAddr(VOID);


/*********************************ȫ�ֱ�������********************************/

/* ���Ӻ���ԭ�ͣ�ʵ�ֵĹ�����:��Master·����������IP��ͻ��⣬����⴫��ĵ�ַ�Ƿ���ָ����
   ���ϵ�ĳ��Master���������IP��ͻ�����Ƿ���ȣ�����򷵻�1�����򷵻�0������ε�ַ�������� */
typedef ULONG (*TCPIP_VirtualIpAddrConflict_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr);


extern ULONG TCPIP_RegFuncVirtualIpAddrConflict(TCPIP_VirtualIpAddrConflict_HOOKFUNC pfHookFunc);


/* ���Ӻ���ԭ�ͣ�ʵ�ֵĹ�����:�ж�physical��ַ�Ƿ���ָ���ӿ���ĳ�����������MAC��ͬ�����򷵻�1�����򷵻�0 */
typedef ULONG (*TCPIP_CompareVirtualMac_HOOKFUNC)(ULONG ulIfIndex, UCHAR *aucMacAddr);
extern ULONG TCPIP_RegFuncCompareVirtualMac(TCPIP_CompareVirtualMac_HOOKFUNC pfHookFunc);

/* ���Ӻ���ԭ�ͣ�ʵ�ֵĹ�����:�жϵ�ַ�Ƿ����ַ�����򷵻�1�����򷵻�0��
   �����aucMacAddr��Ϊ��ʱ���践�ض�Ӧ���ַ����MAC���������践�أ���ȡ��MAC�ɹ�Ҳ�Ƿ���1�����򷵻�0����ε�ַ�������� */
typedef ULONG (*TCPIP_IsVipInIf_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);


extern ULONG TCPIP_RegFuncIsVipInIf(TCPIP_IsVipInIf_HOOKFUNC pfHookFunc);


/* ���Ӻ���ԭ�ͣ�ʵ�ֵĹ�����:���ݵ�ַ��ȡ����֮����ƥ�����IP��Ӧ����MAC������ARP����ĳ��������б��ķ���/ת��ʱ��
   ����ԴIP���Ǳ��ӿ��ϵĵ�ַ������һ���ĵ�ַ��ӿ��ϵ���IP��ͬһ����ʱ�����ĵ�ԴMAC�滻Ϊ��MAC���ɹ��򷵻�0�����򷵻ط�0��
   ��ε�ַ�������� */
typedef ULONG (*TCPIP_GetVirtualMacByIpAddr_HOOKFUNC)(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);


extern ULONG TCPIP_RegFuncGetVirtualMacByIpAddr(TCPIP_GetVirtualMacByIpAddr_HOOKFUNC pfHookFunc);


/* ���Ӻ���ԭ�ͣ�ʵ�ֵĹ�����:����VRF�����͵�ַ���ж�ָ���ĵ�ַ�Ƿ�VRF��ĳ��VRRP����������ַ�����򷵻�1�����򷵻�0 */
typedef ULONG (*TCPIP_IsVipInVrf_HOOKFUC)(ULONG ulVrfIndex, ULONG ulIpAddr);
extern ULONG TCPIP_RegFuncIsVipInVrf(TCPIP_IsVipInVrf_HOOKFUC pfHookFunc);


typedef enum tagTCPIP_VRRP_DEBUG
{
    TCPIP_VRRP_DEBUG_IPCLFT      = 0x1,     /* �жϵ�ַ����IP�Ƿ��ͻ�ĵ��Կ��� */
    TCPIP_VRRP_DEBUG_CMPVMAC     = 0x2,     /* �Ƚ�ָ��MAC�Ƿ���MAC�ĵ��Կ��� */
    TCPIP_VRRP_DEBUG_ISVIPINIF   = 0x4,     /* �ж�IP�Ƿ�ָ���ӿڵ���IP�ĵ��Կ��� */
    TCPIP_VRRP_DEBUG_GETVMACBYIP = 0x8,    /* ���ݵ�ַ��ȡ�ӿ���ͬ������IP��Ӧ����MAC�ĵ��Կ��� */
    TCPIP_VRRP_DEBUG_ISVIPINVRF  = 0x10     /* �жϵ�ַ�Ƿ�ָ��VRF�ڵ���IP�ĵ��Կ��� */
}TCPIP_VRRP_DEBUG_E;
extern ULONG TCPIP_SetVrrpDebug(ULONG ulDebugFlag);


extern ULONG TCPIP_GetVrrpDebug(ULONG *pulDebugFlag);
/* IPV6���Ԥ����KEYֵ,Ϊ�ַ��� */
/* Total number of PMTU entries */
#define PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM                 "PAF_LCS_IPV6_PMTU_SPECS_ENTRIES_NUM"
/* Total number of Neighbor entries */
#define PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM                   "PAF_LCS_IPV6_ND_SPECS_ENTRIES_NUM"
#define PAF_DHCP6C_SPECS_INTF_PER_CLIENT                    "PAF_DHCP6C_SPECS_INTF_PER_CLIENT"
#define PAF_DHCP6C_SPECS_IA_PER_INTF                        "PAF_DHCP6C_SPECS_IA_PER_INTF"
#define PAF_DHCP6C_SPECS_ADDR_PER_IA                        "PAF_DHCP6C_SPECS_ADDR_PER_IA"
#define PAF_DHCP6R_SPECS_HOP_COUNT                          "PAF_DHCP6R_SPECS_HOP_COUNT"
#define PAF_DHCP6R_ADDR_PER_INTF                            "PAF_DHCP6R_ADDR_PER_INTF"
/* Total number of default router entries per interface */
#define PAF_IP6ND_SPECS_DEFRTR_PER_INTF                     "PAF_IP6ND_SPECS_DEFRTR_PER_INTF"
/* Total number of prefix list entries per interface */
#define PAF_IP6ND_SPECS_PREFLIST_PER_INTF                   "PAF_IP6ND_SPECS_PREFLIST_PER_INTF"
/* Total Number of Destination Cache entries */
#define PAF_IP6ND_SPECS_DESTCACHE_PER_HOST                  "PAF_IP6ND_SPECS_DESTCACHE_PER_HOST"
/* Total number of addresses per interface */
#define PAF_LCS_IPV6_ADDR_ND_SPECS_INF_ADDR_PREFIX_NUM      "PAF_LCS_IPV6_ADDR_ND_SPECS_INF_ADDR_PREFIX_NUM"
/* Total neighbor entries per interface as a percent of total number of neighbor entries in the system */
#define PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES                "PAF_LCS_IPV6_ND_SPECS_INF_NB_ENTRIES"
/* Static neighbor entries per interface, as a percentage of total number of neighbor entries per interface */
#define PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES         "PAF_LCS_IPV6_ND_SPECS_INF_STATIC_NB_ENTRIES"
/* Total number of static PMTU entries */
#define PAF_LCS_IPV6_PMTU_SPECS_STATIC_ENTRIES_NUM          "PAF_LCS_IPV6_PMTU_SPECS_STATIC_ENTRIES_NUM"
/* Total number of static neighbor entries */
#define PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES         "PAF_LCS_IPV6_ND_SPECS_TOT_STATIC_NB_ENTRIES"
/* Set MTU range for Gigabye Ethernet */
#define PAF_LCS_IPV6_ADDR_SPECS_GETH_MTU_NUM                "PAF_LCS_IPV6_ADDR_SPECS_GETH_MTU_NUM"


/* IPV6����Ԥ����KEYֵ,Ϊ�ַ��� */
/* IPV6�������ܿ��� */
#define PAF_LCS_IPV6_BASE_SPECS_ENABLED                     "PAF_LCS_IPV6_BASE_SPECS_ENABLED"
/* �ӿ��Զ�����IPV6��ַ���� */
#define PAF_LCS_IPV6_ADDR_AUTOCONFIG_SWITCH                 "PAF_LCS_IPV6_ADDR_AUTOCONFIG_SWITCH"
extern ULONG TCPIP_Set_PAF_ResValue(CHAR *pcKey, ULONG ulValue);


extern ULONG TCPIP_Set_PAF_FunValue(CHAR *pcKey, ULONG ulValue);


extern VOID TCPIP_Show_PAF_Value(VOID);



extern ULONG TCPIP_SetHDRSchedNum(ULONG ulHDRSchedNum);


extern ULONG TCPIP_GetHDRSchedNum(ULONG* pulHDRSchedNum);


extern ULONG TCPIP_ShowHDRSchedNum(VOID);


extern ULONG TCPIP_SetLastCompressBuf(ULONG ulMemSize);


extern ULONG TCPIP_GetLastCompressBuf(ULONG *pulMemSize);


extern ULONG TCPIP_Compress(UCHAR* pcInputData,ULONG ulInputDataLength,UCHAR* pcOutputData,ULONG* pulOutputDateLength);


extern ULONG TCPIP_SetSockSchedule(ULONG ulSwitch,ULONG ulTimes,ULONG ulDelayTime);


extern ULONG TCPIP_GetSockSchedule(ULONG *pulSwitch,ULONG *pulTimes,ULONG *pulDelayTime);


extern ULONG TCPIP_ShowSockSchedule(VOID);

/* ��ȡ�Ƿ��ͷ�CPU�Ĺ��Ӻ��� */
typedef ULONG (*CHECK_TASKDELAY_HOOK)(ULONG ulTaskId,ULONG *pulDelayTime);
extern ULONG TCPIP_RegFuncCheckTaskDelayHook(CHECK_TASKDELAY_HOOK pfHookFunc);


extern ULONG TCPIP_CheckTaskDelay(ULONG ulTaskId,ULONG *pulDelayTime);


extern ULONG TCPIP_HA_EventNotify(ULONG ulEventType);

/*******************************************************************************
*    Func Name: TCPIP_SetLogOutputMod
* Date Created: 2010-07-07
*       Author: mafeng59090
*  Description: ������־���ģʽ(�Ƿ�ʹ��VISP��INFO�������)
*        Input: ULONG ulMod:0:�첽ģʽ(ʹ��INFO����)��1:ͬ��ģʽ
*       Output: 
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-07   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLogOutputMod(ULONG ulMod);

/*******************************************************************************
*    Func Name: TCPIP_GetLogOutputMod
* Date Created: 2010-07-07
*       Author: mafeng59090
*  Description: ��ȡVISP��־��Ϣ���ģʽ
*        Input: ULONG *pulMod:
*       Output: ��־���ģʽ
*       Return: PUBLIC_ERR_PARA_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-07-07   mafeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetLogOutputMod(ULONG *pulMod);

/*******************************************************************************
*    Func Name: TCPIP_AddVlanHead
* Date Created: 2008-03-29
*       Author: mafeng(59090)
*  Description: ����VLAN�ֶ�
*        Input: MBUF_S *pMBuf:����MBUFָ��
*               ULONG ulVlanHead:VLAN�ֶ�(������)
*       Output:
*       Return: OPTIM_OK:����ɹ�
*               OPTIM_ERR:����ʧ�ܣ��ͷű���
*      Caution: ��������(�ͷ�)������ETH���ƿ�ͳ����Ϣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-29   mafeng(59090)           Create-123456789
*
*******************************************************************************/
extern ULONG TCPIP_AddVlanHead(MBUF_S *pMBuf, ULONG ulVlanHead);



extern ULONG TCPIP_RegFuncHATaskDelayHook(CHECK_TASKDELAY_HOOK pfHookFunc);



extern ULONG TCPIP_HA_SetDelaySetting(ULONG ulHADelaySwitch, ULONG ulDelayTime, ULONG ulDelayPacket);


extern ULONG TCPIP_HA_GetDelaySetting(ULONG *pulDelaySwitch, ULONG *pulDelayTime, ULONG *pulDelayPacket);




extern VOID TCPIP_ShowHADelaySetting(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetSockRateTime
* Date Created: 2011-05-16
*       Author: luogaowei61496
*  Description: ����SOCK ����ʱ����ͷ�CPUʱ�����������SOCK ����CPUռ�ñ���
*        Input: ULONG ulSwitch:����(1��ʾ�򿪣�0��ʾ�ر�)
*               ULONG ulRunTime:SOCKһ������ռ��ʱ��(0��ʾȡĬ��ֵ40ms)
*               ULONG ulFreeTime:SOCK����һ�κ��ͷ�CPUʱ��(0��ʾȡĬ��ֵ40ms)
*       Output: 
*       Return: VOS_OK���ߴ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-05-16   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetSockRateTime(ULONG ulSwitch, ULONG ulRunTime, ULONG ulFreeTime);

/*******************************************************************************
*    Func Name: TCPIP_GetSockRateTime
* Date Created: 2011-05-16
*       Author: luogaowei61496
*  Description: ��ȡSOCK����ʱ����ͷ�CPUʱ�����
*        Input: 
*       Output: ULONG *pulSwitch:����
*               ULONG *pulRunTime:SOCKһ������ռ��ʱ��
*               ULONG *pulFreeTime:SOCK����һ�κ��ͷ�CPUʱ��
*       Return: VOS_OK���ߴ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-05-16   luogaowei61496          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSockRateTime(ULONG *pulSwitch, ULONG *pulRunTime, ULONG *pulFreeTime);

typedef LONG  (*TCPIP_IsNeedWarning_HOOK_FUNC)(ULONG ulWarningID, VOID *pWarnParam);

extern ULONG  TCPIP_RegFuncIsNeedWarningHook(TCPIP_IsNeedWarning_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_HA_SetKeepalive
* Date Created: 2012-09-03
*       Author: MaFeng59090
*  Description: ����HA����̽�ⳬʱ����
*        Input: ULONG ulDetectThr:��ʱ����[1-20]
*       Output: ��
*       Return: �ɹ�/ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-03   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_SetKeepalive(ULONG ulDetectThr);

/*******************************************************************************
*    Func Name: TCPIP_HA_GetKeepalive
* Date Created: 2012-09-03
*       Author: MaFeng59090
*  Description: ��ȡ���õ�HA����̽�ⱶ��
*        Input: ULONG *pulDetectThr:̽�ⱶ��ָ��
*       Output: ̽�ⱶ��
*       Return: �ɹ�/ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-03   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetKeepalive(ULONG *pulDetectThr);

/*******************************************************************************
*    Func Name: TCPIP_HA_EnableDetect
* Date Created: 2012-09-07
*       Author: MaFeng59090
*  Description: ��Ʒ������ֹͣHA����̽�⹦��
*        Input: ULONG ulStart:1:����,0:ֹͣ
*       Output:
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-07   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_EnableDetect(ULONG ulStart);

/*******************************************************************************
*    Func Name: TCPIP_HA_GetDetect
* Date Created: 2012-09-07
*       Author: MaFeng59090
*  Description: ��ȡ��ǰ�Ƿ�������HA����̽�⹦��
*        Input: ULONG *pulStart:��ǰHA����̽���״̬
*       Output:
*       Return: VOS_ERR/VOS_OK
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-07   MaFeng59090             Create
*
*******************************************************************************/
extern ULONG TCPIP_HA_GetDetectState(ULONG *pulState);


typedef ULONG  (*TCPIP_TaskExceptionHandlerFunc)(VOID);   /*��������쳣������*/
typedef ULONG  (*TCPIP_TaskIdGetThreadHook)(ULONG ulTaskId);/*��������IDת����threadid �Ļص�����*/

/* ע����Ҫ���ӵ�����,
   ulThreadId: PthreadID��
   ulMaxSec: ����δ�����ȵ����������λΪ�룩������Ϊ0
   pfHandler:����������δ�����ȴﵽ����ֵ�Ĵ�������NULL��ʾ����Ĭ�ϴ���(��λ����)��
*/
typedef ULONG (*TCPIP_RegMonitorTaskFunc)(ULONG ulThreadId, ULONG ulMaxSec, TCPIP_TaskExceptionHandlerFunc pfHandler);

/* ����������ʱ���ô˽ӿ��ϱ����� */
typedef VOID   (*TCPIP_TaskHeartbeatFunc)(VOID);

typedef struct tagTCPIPTaskMonitorPARA
{
    TCPIP_TaskIdGetThreadHook pfGetThreadIdFunc;   /*��������IDת����threadid �Ļص�����*/
    TCPIP_RegMonitorTaskFunc   pfRegTaskFunc;      /*ע����Ҫ���ӵ�����*/
    TCPIP_TaskHeartbeatFunc    pfHeartbeatFunc;    /*��Ʒע���VISP����������*/
}TCPIP_TASK_MONITOR_PARA_S;
/*********************************ȫ�ֱ�������********************************/

/*************************************************************************
Function     : TCPIP_RegTaskMonitorFuncHook
Description  : �ṩ����Ʒע��������Ӻ�����������ӻ����ɲ�Ʒʵ��
Input        : pfHookFunc: ������ӽӿ�
Output       :
Return       : 0--�ɹ�����0--ʧ��
Create By    :
Modification :
Restriction  :
*************************************************************************/
ULONG TCPIP_RegTaskMonitorFuncHook(TCPIP_TASK_MONITOR_PARA_S *pfHookFunc);


ULONG TCPIP_SetSockCpuScheTimeWay(ULONG ulSwitch);


ULONG TCPIP_GetSockCpuScheTimeWay(ULONG* pulSwitch);

ULONG TCPIP_SetShutIFFlagForVRFChange(ULONG ulShutFlag);

/*******************************************************************************
*    Func Name: TCPIP_SetTcpPrecisionSwitch
* Date Created: 2015-08-26
*       Author: wangbin
*  Description: ����TCP 2MSLʱ�侫�ȿ���
*        Input: ulSwitch  : ����ֵ
*       Output: NA
*       Return: VOS_ERR  ʧ��
*               	VOS_OK �ɹ�
*      Caution: �ýӿ���Ҫ����Ӧ��ϵͳ�ṩ����ʱ��ʱ������׼������
*(��Ҫָϵͳ����ʱ����ʱ��δ��������ʱ�����������ʱ��ʱ���ѳ�ʱ�޷���������)
*Ŀǰ�ն��ֻ������ڹ���KPIָ�꣬�������ָó���
* *
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-08-26   Create
*
*******************************************************************************/
ULONG TCPIP_SetTcpPrecisionSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetTcpPrecisionSwitch
* Date Created: 2015-08-26
*       Author: wangbin
*  Description: ��ȡTCP 2MSLʱ�侫�ȿ���
*        Input:  NA
*       Output: pulSwitch :����ֵָ��
*       Return: VOS_ERR  ʧ��
*               	VOS_OK �ɹ�
*      Caution: s
* *
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-08-26   Create
*
*******************************************************************************/
ULONG TCPIP_GetTcpPrecisionSwitch(ULONG *pulSwitch);


#ifdef  __cplusplus
}
#endif

#endif

