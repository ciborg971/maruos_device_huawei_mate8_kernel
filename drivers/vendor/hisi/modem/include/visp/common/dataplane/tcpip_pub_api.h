
#ifndef _TCPIP_PUB_API_H_
#define _TCPIP_PUB_API_H_

#ifdef __cplusplus
    extern "C"{
#endif

/* PPI��������,�ö����ǿ������Ӧ����Ŀ���,����ر�֤������涨��һ�� */
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
    PPI_IF_SETMAC,              /* 13 ����TRUNK�ӿڵ��pphysical��ַ */
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

    PPI_TRUNK_ADDPORT,   /* TRUNK��Ӱ󶨶˿� */
    PPI_TRUNK_REMOVEPORT,/* TRUNK�Ƴ��󶨶˿� */

    PPI_AM4_ADD,         /* AM4��ӵ�ַ */
    PPI_AM4_DELETE,      /* AM4ɾ����ַ */

    PPI_PPP_SET_OSICPGOTOPTION, /*֪ͨNP OSICP����Э��ѡ��*/
    PPI_PPP_SET_OSICPHISOPTION, /*֪ͨNP OSICP�Զ�Э��ѡ��*/

    PPI_PPP_GET_LCPGOTOPTION,    /* ��ȡ����LCPЭ��ѡ�� */
    PPI_PPP_GET_LCPHISOPTION,    /* ��ȡ�Զ�LCPЭ��ѡ�� */
    PPI_PPP_GET_IPCPGOTOPTION,   /* ��ȡIPCP����Э��ѡ�� */
    PPI_PPP_GET_IPCPHISOPTION,   /* ��ȡIPCP�Զ�Э��ѡ�� */
    PPI_PPP_GET_OSICPGOTOPTION,  /* ��ȡOSICP����Э��ѡ�� */
    PPI_PPP_GET_OSICPHISOPTION,  /* ��ȡOSICP�Զ�Э��ѡ�� */

    PPI_IP6_SENDPKT,             /* ����IPv6����*/

    /* PPPOE��Ϣ���� */
    PPI_PPPOE_SESSION_CREATED,      /* ֪ͨNP����PPPOE�Ự */
    PPI_PPPOE_SESSION_DELETED,      /* ֪ͨNPɾ��PPPOE�Ự */
    PPI_PPPOE_SESSION_UPDATED,      /* ֪ͨNP����PPPOE�Ự��Ϣ */
    PPI_PPPOE_SESSION_GETINFO,      /* ��NP��ȡPPPOE�Ự��Ϣ */
    PPI_PPPOE_SESSION_RESTORED,     /* ֪ͨNP PPPOE�Ự�ָ�����ɹ� */
    PPI_PPPOE_SESSION_RESTORED_FIN, /* ֪ͨNP����PPPOE�Ự�ָ�������� */
    PPI_PPPOE_SESSION_SMOOTHED,     /* ֪ͨNP PPPOE�Ựƽ������ɹ� */
    PPI_PPPOE_SESSION_SMOOTHED_FIN, /* ֪ͨNP����PPPOE�Ựƽ��������� */
    PPI_OAM1AG_SETDETECTTIMER,      /* ֪ͨNP CCM Loss���ʱ��ֵ*/
    PPI_TRUNK_IS_PHYUP,             /* 121 TRUNK PHY UP */
    PPI_TRUNK_IS_PHYDOWN,           /* 122 TRUNK PHY DOWN */
    PPI_MAP_ADD,                    /* 123 MAP ADD*/
    PPI_MAP_DEL,                    /* 124 MAP DEL*/

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
/* PPI��������,�ö����ǿ������Ӧ����Ŀ���,����ر�֤������涨��һ�� */


/* BFD PPI Msg Type,�ö����ǿ������Ӧ����Ŀ���,����ر�֤������涨��һ�� */
typedef enum tagPPI_MSG_TYPE_E
{
    BFD_PPI_SESSION_CREATE        = 1              ,         /* �����Ự */
    BFD_PPI_SESSION_REFRESH                        ,         /* ���»Ự */
    BFD_PPI_SESSION_DELETE                         ,         /* ɾ���Ự */
    BFD_PPI_START_SEND_SEQUENCE                    ,         /* ֪ͨ��ʼ���Ͳ�ѯ���� */
    BFD_PPI_STOP_SEND_SEQUENCE                     ,         /* ֹ֪ͨͣ���Ͳ�ѯ���� */
    BFD_PPI_USER_CREATE                            ,         /* API�����Ự */
    BFD_PPI_USER_DELETE                            ,         /* APIɾ���Ự */

    BFD_PPI_SESSION_GET                            ,         /* ��ȡ�ײ�NP�ĻỰ��Ϣ */
    /* SGSN BFD������:���ֻỰɾ����ԭ�� */
    BFD_PPI_SESSION_DELETE_ADMINDOWN               ,         /* ����Admin down���»Ựɾ�� */
    BFD_PPI_SESSION_DELETE_DOWN                    ,         /* ��������ԭ���»Ựɾ�� */
    BFD_PPI_SESSION_STOP_SEND_DETECT_PKT           ,         /* ֪ͨ���ٷ���������BFD���� */
    BFD_PPI_SESSION_START_SEND_DETECT_PKT          ,         /* ֪ͨ���·���������BFD���� */
    BFD_PPI_MSG_MAX
}PPI_MSG_TYPE_E;


#ifdef __cplusplus
}
#endif
#endif


