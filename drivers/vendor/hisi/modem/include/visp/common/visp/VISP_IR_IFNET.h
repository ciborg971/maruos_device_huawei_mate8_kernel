/*************************************************************************
 *
 *              Copyright 2006, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         VISP_IR_IFNET.H  
 *
 *  Project Code: VISP1.6
 *   Module Name: IFNET
 *  Date Created: 2006/11/16   
 *        Author: liuyong 57500
 *   Description: ���ͷ�ļ������Ǵ�VISP IFNET��صĸ���ͷ�ļ���ȡIR��Ҫ�ĺ�ͽṹ���ɣ�
 *                �ں���������ά��ʱ����Ҫ��עͬVISP����ͬ��!
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *
 ************************************************************************/
#ifndef _VISP_IR_IFNET_H_
#define _VISP_IR_IFNET_H_

#ifdef  __cplusplus
extern "C"{
#endif


/***************  from if_type.h ******************/
/* ֪ͨ������������ */
#define IFC_LINKMSG_NOTIFY  0       /* ��·����Ϣ֪ͨ���� */
#define IFC_DEVMSG_NOTIFY   1       /* �ײ���Ϣ֪ͨ���� */ 
#define IFC_ADDIF_NOTIFY    2       /* �ӿڴ���֪ͨ���� */
#define IFC_ADDSUBIF_NOTIFY 3       /* �ӽӿڴ���֪ͨ���� */
#define IFC_DELIF_NOTIFY    4       /* �ӿ�ɾ��֪ͨ���� */
#define IFC_SHUTIF_NOTIFY   5       /* �ӿ�shutdown֪ͨ���� */


/***************  from if_def.h ******************/
#define IFQUEUELENGTH                   75
#define IFMSG_QUEUE_MAX_LENGTH          0x1000          /* Max Length of IfMsg Queue */
#define MAX_IF_TYPE_LENGTH              20              /* �ӿ��������Ƴ��� */
#define MAX_IF_NAME_LENGTH              47              /* �ӿ������� */
#define MAX_IF_NAME_REAL_LENGTH         27              /* ʵ�ʿ��ܵĽӿ�����󳤶�,
                                                           ��: GigabitEthernet15/1/15.1023*/
#define VRP_MAX_INTERFACE_TYPE      20
#define MAX_IF_NUMBER_LENGTH        27 
#define VRP_IFNET_IFINDEXNUM        128             /* ��������� */        /* if_index.c */

/* IFNETģ���û�API������ */
enum enIfnetErrInfo
{
    VRP_IFNET_NOERR = 0,                /* 0 if_index.c */
    VRP_IFNET_ENOMEM,                   /* 1 if_index.c */
    VRP_IFNET_EINDEXCHAOS,              /* 2 if_index.c */
    VRP_IFNET_ECANOTSPLIMP ,            /* 3 if_index.c */
    VRP_IFNET_ENOSUCHIF,                /* 4 �ӿڲ����� */
    VRP_IFNET_GENERR,                   /* 5 ifnetģ��ͨ�ô��� */
    VRP_IFNET_EINDEXNOTINIT,            /* 6 ��ǰ������ */
    VRP_IFNET_CANOTDELVT,               /* 7 can't delete VT*/
    VRP_IFNET_CANOTDELVE,               /* 8 can't delete VE*/
    VRP_IFNET_HAVE_BEEN_DOWN,           /* 9 �ӿ��Ѿ���shutdown*/
    VRP_IFNET_NO_HAVE_BEEN_DOWN,        /* 10 �ӿ�û�б�shutdown*/
    VPR_IFNET_KEEPALIVE_VALUE_TOOBIG,   /* 11 KEEPALIVE ֵ̫��*/
    VRP_IFNET_DESC_TOO_LONG,            /* 12 �ӿ�����̫��*/
    VRP_IFNET_CANOT_BE_SHUTDOWN,        /* 13 �ӿڲ��ɱ��ر�,added for SWFD04676,20041228*/

    VRP_IFNET_NULLPOINTER,              /* 14 �������ָ��Ϊ�� */
    VRP_IFNET_MTU_INVALID,              /* 15 �û����õ�MTUֵ��������Χ֮�� */
    VRP_IFNET_REGISTERPRI_ERR,          /* 16 ע���֪ͨ���ȼ����� */
    VRP_IFNET_REGISTERTYPE_ERR,         /* 17 ע�����Ͳ�֧�� */
    VRP_IFNET_HA_IS_SMOOTHING,          /* 18 HA����ƽ��������ֶ���������*/
    VRP_IFNET_PORT_CANOT_BE_SHUTDOWN,   /* 19 ��Ա�˿�������Trunk�ӿڱ�Shutdown, ��˲��ܶԸó�Ա�˿ڽ���NoShutdown */
    VRP_IFNET_CANOTDELVTBINDED,         /* 20 ����ɾ���Ѿ��󶨵���̫�ӿڵ�VT�ӿ� */
    VRP_IFNET_ISTRUNKPORT,              /* 21 �ӿ���trunk��Ա�˿� */
    VRP_IFNET_IFNAMEERROR,              /* 22 �ӿ����ִ��� */
    VRP_IFNET_GETTRUNKIFFAILED,         /* 23 ���ݳ�Ա�˿ڻ�ȡtrunk�ӿ�ʧ�� */
    VRP_IFNET_TRUNKIFNULL,              /* 24 ���ݳ�Ա�˿ڻ�ȡtrunk�ӿ�ʧ�� */
    VRP_IFNET_WAITLISTEND,              /* 25 �����꣬waitlist���ʽ��� */
    VRP_WAITLIST_OPEN_FAILED,           /* 26 ע��waitlistʧ�� */
    VRP_WAITLIST_SET_FAILED,            /* 27 ����waitlist�ؼ�����ʧ�� */
    VRP_WAITLIST_GET_FAILED,            /* 28 ��ȡwaitlist�ؼ�����ʧ�� */
    VRP_WAITLIST_CLOSE_FAILED,          /* 29 �ر�waitlistʧ�� */
    VRP_IFNET_EENQUEUE,                 /* 30 Fail to put mbuf into link queue */
    VRP_IFNET_EWRITEQUEUE,              /* 31 Fail to write ioctl msg */

    VRP_IFNET_TYPEERR,                  /* 32 ifnet�����Ͳ�ƥ��*/
    VRP_IFNET_ISNOTTRUNK,               /* 33 ifnet�����Ͳ���TRUNK(����Ҫ����TRUNKʱ)*/
    VRP_IFNET_TRUNKVTBLNULL,            /* 34 TRUNK�麯����ָ��Ϊ��*/
    VRP_IFNET_TRUNKHAVEPORT,            /* 35 TRUNK�Ѿ����ڶ˿�*/
    
    VRP_IFNET_MPVTBLNULL,               /* 36 MP������Ϊ�� */
    VRP_IFNET_MPHAVESON,                /* 37 MP�����ӽӿ� */
    
    VRP_IFNET_ISDIALER,                 /* 38 �ӿ���Dialer�ӿڣ�������pfIf_deleteɾ�� */
    VRP_IFNET_CANOT_ISIS,               /* 39 �ýӿڲ���ʹ��ȥʹ��ISIS */
    VRP_IFNET_IOCTLERR,                 /* 40 �����������·�/����ʧ�� */
    VRP_IFNET_GETL3STATE,               /* 41 */
    VRP_IFNET_NOLCPINFO,                /* 42 */
    VRP_IFNET_NOFSM,                    /* 43 */
    VRP_IFNET_COPYCBINFO,               /* 44 */
    VRP_IFNET_NOIPCPINFO,               /* 45 */
    VRP_IFNET_NOIPCPFSM,                /* 46 */
    VRP_IFNET_PARA_INVALID,             /* 47 ���ò���Խ�� */  
    VRP_IFNET_DIMENSION_MULTI,          /* 48 �ӿ�һ��ά��Ϣ������� */  
    VRP_IFNET_IS_3D_VIRTUAL,            /* 49 ��ά����ӿ� */
    VRP_IFNET_NOT_3D_MODE,              /* 50 */
    VRP_IFNET_CREATEFAIL,               /* 51 */
    VRP_IFNET_SELF_BOARD,               /* 52 ��ά����ӿ� */
    VRP_IFNET_VISP_NOT_INIT_DONE,       /* 53 Э��ջδ��ȫ����ǰ���ܽ��ձ��� */
    VRP_IFNET_IS_3D_MODE,               /* 54 3Dģʽ */ 
    VRP_IFNET_DOWNORSHUTDOWN,           /* 55 �ӿ�Down���߱�shutdown */
    VRP_IFNET_DEL_IF_FAIL,              /* 56 ɾ���ӿ�ʧ�� */ 
    VRP_IFNET_IS_L2IF,                  /* 57 L2IF�ӿ� */
    VRP_IFNET_L2IFVTBLNULL,             /* 58 L2IF�麯����ָ��Ϊ��*/
    /*Add for BC3D00792,DR.131��ȡ��·��״̬ start*/
    VRP_IFNET_IPOA_NOINIT,              /* 59 IPOAģ��δʹ�� */ 
    VRP_IFNET_IPOA_ERR,                 /* 60 IPOAģ��API����ʧ�� */ 
    VRP_IFNET_ETH_NOINIT,               /* 61 Ethģ��δʹ��*/ 
    VRP_IFNET_ETH_ERR,                  /* 62 Ethģ��API����ʧ�� */ 
    /*Add for BC3D00792,DR.131��ȡ��·��״̬ end*/
    VRP_IFNET_PPIGETMTU_ERR,            /* 63 ��ײ��ѯ���MTU���� */
    VRP_IFNET_L2TRUNKPHYTRANSMIT_NULL,  /* 64 ����TRUNK������㱨�ķ��ͺ���Ϊ�� */
    VRP_IFNET_VRF_ERR,                  /* 65 VRFģ��API����ʧ�� */ 
    VRP_IFNET_VRF_NOT_INIT,             /* 66 VRFģ��δ��ʼ�� */ 

    VRP_IFNET_NOIP6CPFSM,               /* 67 IP6CP״̬��������*/
    /*End of Added by hanna55555, 2009/3/30 */
    VRP_IFNET_NO_DEVLINK,               /* 68 �����ڶ�Ӧ��DEVLINK�����㣬ͬ����V1R7C01 */
    VRP_IFNET_KEEPALIVE,                /* 69 PPP�ӿ�û����ɱ����,���ڱ���״̬ */ 
    VRP_IFNET_UNRECGPHYIF,              /* 70 �ӿڲ���VISP֧�ֵ�����ӿ����ͣ�ͬ����V1R6C05 */
    VRP_IFNET_NULL_PPPLINK,             /* 71 PPP�ӿ���·��ָ��Ϊ�� */    
    VRP_IFNET_NULL_ETHLINK,             /* 72 Eth�ӿ���·��ָ��Ϊ�� */
    VRP_IFNET_ERRLINETYPE,              /* 73 �ӿ����ͷ�Eth/PPP��·���� */
    VRP_IFNET_NULL_PPI,                 /* 74��Ʒע��ifnet PPIΪ��*/
    VRP_IFNET_NOTIFY_PPI_ERR,           /* 75�·�PPI����*/
    VRP_IFNET_MALLOC_FAIL,              /* 76�����ڴ�ʧ��*/
    VRP_IFNET_TUNNEL_INFO_NULL,         /* 77tunnel����Ϊ��*/

    VRP_IFNET_MAXERR                    /* ö��ֵ���ޣ���ʵ�⣬����ö��ֵ������ǰ��� */
};


#define IF_SEARCH_ALL                   0x0FFF  /* �������� */
#define IF_SEARCH_TEMPIF                0x1000  /* ����������ʱ�ӿ� */

#define IF_RTATTR_BROADCAST             0x2
#define IF_RTATTR_NBMA                  0X4
#define IF_RTATTR_LOOPBACK              0x8
#define IF_RTATTR_POINT2POINT           0x10
#define IF_RTATTR_MULTICAST             0x8000

#define IF_STATUS_PROT_DOWN             0x1
#define IF_STATUS_LOW_DOWN              0x2
#define IF_STATUS_PROT_UP               0x4
#define IF_STATUS_PROT6_DOWN            0x8   /*��ʾIPv6 line protocol ����DOWN��״̬*/
#define IF_STATUS_PROT6_UP              0x10  /*��ʾIPv6 line protocol ����UP��״̬*/

/*******************   from iifnet_inc.h  *********************************/
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* ���Ľӿ������� */ 
#define MAX_IFCMD_NAME_LEN                     47
#define MAX_INTERFACE_SIMPLENAME_LEN           20       /* ���ļ򵥽ӿ������� */ 
#define MAX_INTERFACE_DESCRIPTION_LEN          80       /* ������󳤶� */
#define IF_MAX_INDEX                           100000   /* ���Ľӿ���Ŀ */   
#define IF_MAX_MAC_LEN                         6

/***********************************************************************/
/*usIfState value: ����������ȷ*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN

/******************  from if_vlink.h  ************/
#define RTM_CREATE  0x01    /* �ӿڡ�����·���� */
#define RTM_DEL     0x02    /* �ӿڡ�����·ɾ��*/
#define RTM_STATE   0x04    /* �ӿڡ�����·��usIfStste �� usIfFlags �����ı�*/
#define RTM_CONFIG  0x08    /* �ӿڡ�����·�Ĳ�����ϢsIfData�����ı�*/
#define RTM_BOARDREMOVE 0x10
#define RTM_NEWADDRESS  0x20    /* IP��㱨���ؽӿڵĵ�ַ*/
#define RTM_DELADDRESS  0x40    /*IP��ɾ�����ؽӿڵĵ�ַ*/
#define RTM_DELVLINK    0x80    /*ɾ��VLINK*/

#define	IF_SEARCH_CONFIG_CHAIN  1000


 typedef struct  tagIFConfigVlink
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;
    ULONG   ulData;    
    ULONG   ulIfBandwidthHigh;
    ULONG   ulIfBaudrateHigh;

} IFCONFIGVLINK_S;

typedef struct tagIfVLINKentry6
{
    ULONG   ulIntfIndex;            /*�ӿ�Ψһ����ֵ*/
    ULONG   ulVlinkIndex;           /*����·����ֵ���ӿ��¼�ʱ��Ϊ0*/
    ULONG   aulPeerAddr[4];         /*�Զ˵�ַ����������·ʱ�����жԶ˵�ַ*/
    ULONG   ulMacAddrLen;
    USHORT  usSlot;                 /*�ӿ����ڲۺţ� new in 3.0 */
    USHORT  usMsgType;              /*�����涨��*/
    USHORT  usIfState;              /*�ӿ�״̬*/
    USHORT  usIfFlags;              /* �ӿڱ�־*/
    USHORT  usIfType;               /*  �ӿ�����*/
    UCHAR   ucPadding_1[2]; 
    IFCONFIGVLINK_S  stIfData;           /*�ӿڲ���*/
    UCHAR   ucMacAddr[IF_MAX_MAC_LEN];
    UCHAR   ucPadding_2[2];
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];   /*�ӿ�����*/
    ULONG   ulVrfIndex;
}IFVLINKENTRY6_S;

#define RTM_CREATE  0x01
#define RTM_DEL     0x02    

#define VLINK6_TABLELINE_EMPTY  0
#define VLINK6_TABLELINE_USED   1

typedef struct tagVLINK6TABLE
{
    ULONG  ulPrevFreeIndex;     /*previous free struct*/
    ULONG  ulNextFreeIndex;     /*next free struct*/
    ULONG  ulPrevUsedIndex;     /*previous used struct*/
    ULONG  ulNextUsedIndex;     /*next used struct*/
    ULONG  ulIfIndex;           /* the IFNET index map belong to*/
    ULONG  ulUsedFlag;          /*if the struct inused 0-empty 1-used*/
    ULONG  ulSynCount;          /*syn count */
    IFVLINKENTRY6_S tLastStatus ;   /* save last change status */
    VOID*  pCB;                 /*Control Block of VLINK */
}VLINK6TABLE_S;

typedef struct tagIF_WAITLIST_PARAM
{
    UINTPTR   ulWaitListHandle;       /* WAITLIST��� */
    ULONG     ulSearchType ;          /* �������� */
    VOID      *pSearch ;                      /* ���ָ�� */
}IF_WAITLIST_PARAM ;

/******************   from  if_def.h   *************/

/**********************************************************
*  �ڴ˶���ioctl������case��,ע�ⲻ����syst_pub.h�е�
*  ������ DRV_TEST_ENTRY �غ�,�������������������������
\*********************************************************/
enum  enumPhyIoCtl
{
    PHY_POWERUP = 0,
    PHY_INIT,
    PHY_SHUTDOWN,
    PHY_NO_SHUT,
    PHY_ENABLERECV,
    PHY_DISABLERECV,
    PHY_CHECKFLOW,
    PHY_BUILDRUN,
    PHY_CHECK,
    PHY_DELETE,
    PHY_SETMACADDR,
    PHY_SETMACTABLE,
    PHY_GETMACADDR,
    PHY_MAP,
    PHY_PROTOCOL_CHG,
    PHY_GETINFO,
    PHY_GETSTATISTIC,
    PHY_CLEAR_PORT,
    PHY_GETMAXBD,
    PHY_SETLEASED,
    PHY_ISPURE_SYNC,
    PHY_ISASYNC,
    PHY_ISSOFTCVT,
    PHY_ATMMCLK,
    PHY_ATMMSERV,
    PHY_ATMMOAMPVC,
    PHY_ATMMOAMRETRY,
    PHY_ATMAPVC,
    PHY_ATMDPVC,
    PHY_ATMINIT,   /*added by sunyafeng for D12511 on 2002/04/05*/
    PVC_STA_CHANGE,/*added by lhm for D12315 on 2002/04/16*/

    /*2003/06/02 zhangwei29537,add for ima,begin*/
    PHY_IMA_SETLINKNUM,
    PHY_CLI_ATMIMA_GETFRAMELENGTH,

    /*2003/06/02 zhangwei29537,add for ima,end*/
    PHY_ATMGETPVCINFO,
    PHY_LINK_DOWN,
    /*added by liuhui, for PPPoE Client, to notify PPPoE Client Link down*/
    PHY_POECLIENT_LINK_DOWN_WITHPADT,
    PHY_POECLIENT_LINK_DOWN_NOPADT,
    /*add ends*/
    PHY_GETMIBINFO,
    PHY_SETPROMODE,
    PHY_SETRCVADDRSTATUS,
    PHY_ISUP,       /* �жϵײ��Ƿ�UP 2001-03-26 */
    PHY_SETACCM,  /* Notify low layer ACCM */
    PHY_GET_HARD_INFO, /* for D10708 */
    /*add by huzhiyong 2001/12/19 */
    PHY_GETASYNMODE,
    PHY_ENABLE,
    PHY_DISABLE,
    PHY_INIT_BUFFER,
    PHY_GET_VER,
    PHY_GETPHYSTATUS,
    PHY_DEBUG,
    PHY_SETLOOPBACK,
    PHY_E1DELETE,
    PHY_LINECODE,
    PHY_FRAMING,
    PHY_LINECLOCK,
    PHY_E1BUILDRUN,
    PHY_BOARD_RESET,
    PHY_E1CHECKSTAT,
    PHY_T1DELETE,
    PHY_T1BUILDRUN,
    PHY_T1CHECKSTAT,
    PHY_CHANNEL_SPEED,
    PHY_T1_CABLE,
    PHY_READREG,
    PHY_WRITEREG,
    PHY_SETPORT
/*2003/06/02 zhangwei29537,add for ima,begin*/        
    ,
    PHY_ADDLINK,
    PHY_DELELELINK,
    PHY_CANDELELTE,
/*2003/06/02 zhangwei29537,add for ima,end*/    
    PHY_LOOPBACK_STATE,
    
    PHY_IPV6_ADD_MCAST_ADDR,
    PHY_IPV6_DEL_MCAST_ADDR,

    /*This 2 value were moved here by ZhuKun 36377,20040827,For D00575*/
    PHY_JOINMULTI,
    PHY_LEAVEMULTI,
    
    PHY_GET_ROUTFLAG,

    PHY_GETDOWNMODE,

    PHY_ADD_VRRP_VIRTUAL_MAC,   /* ���VRRP����MAC */
    PHY_DEL_VRRP_VIRTUAL_MAC,   /* ɾ��VRRP����MAC */
    PHY_ENABLE_VRRP,   

    PHY_LCPECHOOPEN,
    PHY_LCPECHODOWN,
    PHY_LCPECHOSETCONF,    

    PHY_GETINTFSTATUS,
    PHY_GETINTFTYPE,

    PHY_MAX_PHYWORD  /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

/* �ӿ��������� */
enum enumPhyType
{
    PHY_ETHERNET=1,
    PHY_SYNC,
    PHY_ASYNC,
    PHY_ISDN,
    PHY_DIALER,
    PHY_LOOP,
    PHY_E1,
    PHY_BRI,
    PHY_PRI,
    PHY_BCHAN,
    PHY_TEMPLATE,
    PHY_TEMPLATECHAN,
    PHY_TEMPLATEMPCHAN,
    PHY_VPN_TUNNEL,
    PHY_TUNNEL,
    PHY_ATM,
    PHY_ATMCHAN,
    PHY_ATM_NOTSURE,
    PHY_CONSOLE,
    PHY_POS,
    PHY_VIRTUAL_ETHERNET,
    PHY_GE,
    PHY_GROUPE1,
    PHY_AUX,
    PHY_NULL,
    PHY_LOOPBACK,
    PHY_VIRTUAL_ACCESSS,
    PHY_MP_GROUP,
    PHY_VLAN,
    PHY_DPT,
    PHY_ETH_TRUNK,
    PHY_IP_TRUNK,
    PHY_METH,
    PHY_MTUNNEL,
    PHY_VI,          /*VI�ӿ�*/
    PHY_UI,          /*UI�ӿ�*/
    PHY_MAX
};

/* ��������� */
enum enumPortType
{
    PORT_ETHERNET=1,
    PORT_SYNC,
    PORT_ASYNC,
    PORT_BRI,
    PORT_E1,
    PORT_T1,
    PORT_E3,
    PORT_T3,
    PORT_CPOS,
    PORT_DIALER,
    PORT_LOOP,
    PORT_TEMPLATE,
    PORT_TEMPLATECHAN,
    PORT_TEMPLATEMPCHAN,
    PORT_VPN_TUNNEL,
    PORT_TUNNEL,
    PORT_ATM,
    PORT_ATMCHAN,
    PORT_FASTETHERNET,
    PORT_CONSOLE,
    PORT_VIRTUAL_ETHERNET,
    PORT_POS ,
    PORT_GE ,
    PORT_GROUPE1,
    PORT_AUX,
    PORT_NULL,
    PORT_VIRTUAL_ACCESSS,
    PORT_MP_GROUP,
    PORT_VLAN,
    PORT_DPT,
    PORT_ETH_TRUNK,
    PORT_IP_TRUNK,
    PORT_METH,
    PORT_MTUNNEL,
    PORT_VI,     /*VI �ӿ�*/
    PORT_UI,     /*UI �ӿ�*/
    PORT_MAX
};

/* ����� to ��·�� */
enum enumUpToLink
{
    SIOCAIPADDR=0 ,
    SIOCDIPADDR ,
    SIOCMIPADDR ,
    SIOCHENCAP ,        /* ȥ��װ */
    SIOCSDOWN ,
    SIOCSUP ,
    SIOCSNETPROTO,
    SIOCHNETPROTO,
    SIOCBUILDENCAP ,
    SIOCGETINFO ,
    SIOCADDTODIALER ,
    SIOCDELFROMDIALER ,
    SIOCSIPFRAMETYPE ,
    SIOCSIPXFRAMETYPE ,
    SIOCGIPXFRAMETYPE ,
    SIOCHIPXFRAMEIF ,
    SIOCGIPXFRAMEIF ,
    SIOCSIPXFRAMEIF ,
    SIOCGIPXNODE ,
    SIOCSDELETEIF ,
    SIOCGADDRIF,
    SIOCLINKSTATE ,
    SIOCHNEGOTIATE,
    SIOCSNEGOTIATE,
    SIOCHUNNUMBER,
    SIOCSUNNUMBER,
    SIOCENCAPSUB,       /* ��װ�ӽӿ� */
    SIOCMMTU,           /*֪ͨ��·�� mtu �ı�*/
    SIOCKEEPALIVE,      /*֪ͨ��·�� keepalive �ı�*/
    SIOCGETMAC, 
    SIOCLINKSMOOTH,
    SIOCVLAN,
    SIOCAIPISIS,
    SIOCDIPISIS,
    SIOCIPADDRINVALID,
    /* �ṩһ�������֣�ֻ��ˢ��BuildRun��Ϣ�����ǲ�֪ͨ��·�㡣*/
    /* �������ⵥD1370 ���ڴӵ�ַ����� 2002/01/11 Chenwejun */
    /* ����ɾ�������Ӵӵ�ַ��Ҫʹ�ã������޸����� 2002/01/22 */
    SIOCPROADDRSEC,
    SIOCDADDRSEC,
    SIOCAIP6LINKLOCALADDR,
    SIOCAIP6GLOBALADDR,
    SIOCAIP6SITELOCALADDR,    /*���� IPv6��ַ*/
    SIOCDIP6LINKLOCALADDR,
    SIOCDIP6GLOBALADDR,
    SIOCDIP6SITELOCALADDR,     /*ɾ�� IPv6��ַ*/
    SIOC6LINKSTATE,            /*�õ�ipv6 line protocol ��״̬*/
    SIOC6GETINFO,              /*�õ���·����Ϣ*/
    SIOC6GETINTERFACEID,       /*�õ��ӿ�ID*/
    SIOCJOINMULTI,  /*add by luohanjun*/
    SIOCLEAVEMULTI,
    SIOCISISENABLE,    /*����·���ȡISIS����*/

    SIOCMADDRSEC,  /* �޸Ĵӵ�ַ���볤��, Added by l143205 for BC3D00874, 2008-12-9 */
    SIOC_MAX_SIOCWORD1 /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

/* ��·������ */
enum enumLineProtocol
{
    LINE_ETHERNET = 1,
    LINE_ATM,
    LINE_PPP,
    LINE_SLIP,
    LINE_CISCO_HDLC,
    LINE_FR,
    LINE_X25,
    LINE_X25_BFE,
    LINE_X25_DCE,
    LINE_X25_DDN,
    LINE_X25_DTE,
    LINE_X25_IETF,
    LINE_X25_DTE_BFE,
    LINE_X25_DTE_DDN,
    LINE_X25_DCE_DDN,
    LINE_X25_DTE_IETF,
    LINE_X25_DCE_IETF,
    LINE_LAPB,
    LINE_LAPB_DTE,
    LINE_LAPB_DCE,
    LINE_LAPB_DTE_IP,
    LINE_LAPB_DCE_IP,
    LINE_LOOP,
    LINE_NULL,
    LINE_LOOPBACK,
    LINE_SHOW,
    LINE_TEMPLATE,
    LINE_VPN_TUNNEL,
    LINE_TUNNEL,
    LINE_CONSOLE,
    LINE_VIRTUAL_ETHERNET,
    LINE_GE,
    LINE_MTUNNEL,
    LINE_UI,
    LINE_VLAN,
    LINE_OTHER_TYPE = 0xFFFF
};

/* �ײ��ϱ���Ϣ */
enum enumLowToUp
{
    ISLUP=0 ,
    ISLDOWN , /*�ײ��ϱ����˽ӿ�DOWN��Ϣ*/
    ISLCHGBAUD ,
    ISLASYTOSYN ,
    ISLSYNTOASY ,
    ISLSHUTDOWN ,
    ISLNOSHUT,
    ISLDELETE,
    ISLCHGPROTOCOL,
    ISLGETPROTOCOL,
    ISLSETMAC,
    ISLSPEED,               /*D18794*/
    ISLATMOAMSTATE,     /* 2001/02/22 sunshengtao */
     
     /* This 2 value were deleted by ZhuKun 36377, 20040827, For D00575 */
     /* ,ISLJOINMULTI, */ /*add by luohanjun*/
     /* ISLLEAVEMULTI */
     
    ISLDOWNALL,   /*(������PPP�ӿ�)�ײ��ϱ�����PPP�ӿ�DOWN��Ϣ,��֪ͨ�Զ�PPP�ӿ�ҲDOWN*/ 
    ISLDUPLEX,    /* visvp1r7c03,l2if ADD, �ײ��ϱ�˫��ģʽ */

    /* OAM-3ah�ϱ���״̬ */
    ISLEFMNORMAL,
    ISLEFMUP,
    ISLEFMDOWN,
    
    ISMAX_END     
};

/* ��·�� to ����� */
enum enumLinkToUp
{
    SIOCIFUP=0 ,
    SIOCIFDOWN ,
    SIOCGIPADDR ,
    SIOCGIPMASK ,
    SIOCGIF ,
    SIOCADDR ,
    SIOCGADDR ,
    SIOCCALLBACK ,
    SIOCIFUPSPOOFING ,
    SIOCIFDOWNSPOOFING ,
    SIOCDNEGOADDR ,
    SIOCIFMTU ,
    SIOCSIPFLAGS ,
    SIOCCIPFLAGS,
    SIOCSECONDIFUP,
    SIOCFIRSTDOWN,
    SIOCSHOW,
    SIOCHOT,
    SIOCDELVLINK,   /* ɾ���ӿڰ�VLINK */
    SIOCDDRCALLIN,
    SIOCDDRNAME,
    SIOCDDRIF,
    SIOCDDRIFUP,
    SIOCOSIENABLE,
    SIOCRCVMAC,
    /*add by huzhiyong ��������PPP��DDR֮��Ľӿ�������2002/01/24*/
    SIOCDDRIFDOWN,
    SIOCDDRLOWERDOWN,

    SIOCNDDAD,  /*ND DAD���*/
    SIOCGIP6LINKLOCALADDR, /* get link-local address */
    SIOCSIP6INTERFACEID, /* notify interface id changed */

    SIOCMSPEED            /*IFNET֪֪ͨͨ�����baudrate�ı仯*/
    /* Added by Mayun for VRPv5 MPLS TE */
    ,SIOCMPLSTEB,       /* the event type for notifying resource information of MPLS TE interface */
    SIOCMPLSTEATTR     /* the event type for notifying IGP SHORT-CUT and FORWARDING information */

    ,SIOCCREATEIF, /*add by luohanjun*/
    SIOCDELETEIF,
    SIOCIFIPC,          /*IPC���ͱ�־��ǿ��Ҫ���͵����ذ���д���*/

    /*����Ϊ�������������޸ģ�ֻ�ܴӱ��к�����������  add by luohanjun*/
    SIOCIFOTHER,

    SIOCLACPUP,   /* LACP UP */
    SIOCLACPDOWN, /* LACP DOWN */

    SIOC_MAX_SIOCWORD2 /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};

enum enumRouterMsg
{
    Help_Router_Async=0,
    Help_Router_Atm,
    Help_Router_Aux,
    Help_Router_Bri ,
    Help_Router_Console,
    Help_Router_Dialer ,
    Help_Router_E1 ,
    Help_Router_Ethernet ,
    Help_Router_GE ,
    Help_Router_FastEthernet ,
    Help_Router_Loop,
    Help_Router_E1Group,
    Help_Router_Serial ,
    Help_Router_Pos ,
    Help_Router_Tunnel ,
    Help_Router_VpnTunnel ,
    Help_Router_VirtualTemplate ,
    Help_Router_MP_Group,
    Help_Router_VirtualEthernet,
    Help_Router_Null,
    Help_Router_LoopBack,
    Help_Router_AsyncIndex ,
    Help_Router_AtmIndex ,
    Help_Router_AuxIndex ,
    Help_Router_BriIndex ,
    Help_Router_DialerIndex ,
    Help_Router_E1Index ,
    Help_Router_EthernetIndex ,
    Help_Router_GEIndex ,
    Help_Router_FastEthernetIndex ,
    Help_Router_LoopIndex,
    Help_Router_E1GroupIndex ,
    Help_Router_SerialIndex ,
    Help_Router_PosIndex ,
    Help_Router_TunnelIndex ,
    Help_Router_VpnTunnelIndex ,
    Help_Router_VirtualTemplateIndex ,
    Help_Router_MP_GroupIndex,
    Help_Router_VirtualEthernetIndex,
    Help_Router_NullIndex,
    Help_Router_LoopBackIndex,
    Help_Router_SubInterface,
    Help_Router_Slot,
    Help_Router_Adaptor,
    Help_Router_InterfaceNum,
    Help_Router_Return,
    Help_Router_Colon,
    Help_Router_Point,
    Help_Router_Diagnol,
    Err_Router_NotCreate,
    Err_Router_QueueLen,
    Err_Router_UnknownQueue,
    Err_Router_MemoryStart,
    Err_Router_MemoryEnd,
    Err_Router_MemoryBeyond,
    Err_Router_ModemCantBeZero,
    Err_Router_ChannelGroup,
    Err_Router_ChannelISDN,
    Err_Router_CanNotDeleteInterface,
    Err_Router_CanNotDeleteInterface1,
    Err_Router_InDeletedInterface,
    Err_Router_CreateDeletedInterface,
    Err_Router_CanNotCreateAccress,
    Err_Router_TemplateNotEmpty,
    Help_Router_InterfaceDeleted,
    Help_Router_InterfaceRemoved,
    Help_Router_Hardware,
    Help_Router_Physical,
    Help_Router_BaudRate,
    Help_Router_Physical1,
    Help_Router_PhysicalLayer,
    Help_Router_PhysicalLayer1,
    Help_Router_Cable,
    Help_Router_Internet1,
    Help_Router_Internet2,
    Help_Router_Counter,
    Help_Router_Counter1,
    Help_Router_Ethernet2,
    Help_Router_Ethernet1,
    Help_Router_NoCable,
    Help_Router_HardTemplate,
    Help_Router_HardTemplateAccess,
    Help_Router_HardTemplateAccessMP,
    Help_Router_HardUnknown,
    Help_Router_LinkStatus,
    Help_Router_MTU,
    Help_Router_MoreThanDChannel,
    Help_Router_CanNotBackupSelf,
    Help_Router_CanNotBackupDialer,
    Help_Router_CanNotBackupSub,
    Help_Router_CanNotUseSubBackup,
    Help_Router_CanNotBackupTwoPort,
    Help_Router_CanNotMainPortBackup,
    Help_Router_CanNotBackupBackupInterface,
    Help_Router_MainIsInRotoryGroup,
    Help_Router_BackupIsInRotoryGroup,
    Help_Router_EnableDelay,
    Help_Router_DisableDelay,
    Err_Router_NotSupport,
    Help_Router_ShowBackup,
    Help_Router_Queue,
    Help_Router_TimeSlots,
    Help_Router_ShowInterfaceQueue,
    Help_Router_ShowProtocolQueue,
    Help_Router_ShowQueue,
    Help_Router_QueueLen,
    Help_Router_SetInterfaceQueLen,
    Help_Router_MemoryStart,
    Help_Router_MemoryEnd,
    Help_Router_ShowController,
    Help_Router_Balanced,
    Help_Router_Unbalanced,
    Help_Router_BriChan,
    Help_Router_PriChan,
    Help_Router_VirtualAccess,
    Help_Router_InterfaceDisabled,
    Help_Router_InterfaceHasDeleted,
    Help_Router_Loopback,
    Help_Router_Admin,
    Help_Router_Removed,
    Help_Router_E1AlreadyBeenShutdown,
    Help_Router_E1ShutDown,
    Help_Router_E1NoBeenShutdown,
    Help_Router_E1IsReset,
    Help_Router_TimeSlot,
    Err_TooManyParam ,
    Err_InvalidParam ,
    Err_IncompleteCmd ,
    Err_NoSuchInter ,
    Err_IncorrectCmd ,
    Err_InvalidIPAddr ,
    Err_InvalidIPXAddr ,
    Err_UnknownCmd ,
    Err_TooManyUsers ,
    Err_TooManyCharsInOneWord,
    Err_ExistAnotherPri ,
    Err_ExistE1 ,
    Err_ExistAnotherE1 ,
    Err_ExistPri ,
    Err_Overgroup ,
    Err_TimeSlot ,
    Err_CanNotEncap ,
    Err_CanNotEncapSLIP,
    Err_CanNotCreateSub ,
    Err_SlipIsRun ,
    Err_CanNotChange ,
    Err_AlreadyInSameMode ,
    Err_SyncProtocolIsRun ,
    Err_SyncNotModem,
    Err_OutOfMemory ,
    Err_ModemCantChange ,
    Err_ModemSync ,
    Err_ModemBackup,
    Help_Return ,
    Help_WithSemiColon ,
    Help_Point ,
    Help_Ce1TimeSlot ,
    Help_ChannellizeGroup ,
    Help_Administratively ,
    Help_ProtocolIPAddr,
    Help_ProtocolIPXAddr,
    Help_InterfaceUp,
    Help_InterfaceDown,
    Help_LineSpoofing,
    Help_InterfaceSpoofingInterface,
    Help_InterfaceStandby,
    Help_InterfaceAdminDown,
    Help_LineUp,
    Help_LineDown,
    Help_AlreadyBeenShutdown,
    Help_ShutDown,
    Help_NoBeenShutdown,
    Help_IsReset,
    Help_Enabled,
    Help_Disabled,
    Help_Sync,
    Help_Asyn,
    Help_sync,
    Help_asyn,
    Help_Modem,
    Help_ModemEnd,
    Help_SubType_P2P,
    Help_SubType_MP,
    Help_Router_Mtu,
    Help_If_Descript,
    Help_If_Route,
    IF_SHOW_ALL_INTERFACE,
    IF_SHOW_ALL_SLOT,
    Help_Router_Vlan,
    Help_Router_MEth,
    Help_Router_SRP,
    Help_Router_Eth_Trunk,
    Help_Router_IP_Trunk,
    Help_Router_SRPIndex,
    Help_Router_Eth_TrunkIndex,
    Help_Router_IP_TrunkIndex,
    Help_Router_VlanIndex,
    Help_Router_MEthIndex,
    Err_Ifnet_NoVlan,
    Err_Ifnet_CreateVlanIfOnSubvlan,
    Err_Ifnet_RoutedOnAggrPortVlan,
    Err_Ifnet_RoutedOnMultiPortVlan,
    Err_Ifnet_RoutedOnSuperVlan,
    
    Help_NullHelp,
    Help_Diagnol_Clarify,
    Err_NoSlot,

    Help_Router_VI,
    Help_Router_VIIndex,
        
    Help_Router_UI,
    Help_Router_UIIndex,
    
    RouterMsgMax
};

enum enumIfnetHotMsgNotify
{
    IFNET_HOT_MSG_INTF_INSERT = 1,
    IFNET_HOT_MSG_INTF_REMOVE,
    IFNET_HOT_MSG_SLOT_INSERT,
    IFNET_HOT_MSG_SLOT_REMOVE
};

/* ���ڱ�ʾ��������, �������еĽӿ������а������ʱʹ�� */
enum enumFuncFlag
{
    IF_FUNC_TYPE_CHECK=0,      /* ���ͼ�� */
    IF_FUNC_TYPE_HELP,         /* ���Ͱ��� */
    IF_FUNC_NUMBER_CHECK,      /* ��ż�� */
    IF_FUNC_NUMBER_HELP,       /* ��Ű��� */
    IF_FUNC_NAME_CHECK,        /* ���Ƽ�� */
    IF_FUNC_NAME_HELP,         /* ���ư��� */
    IF_FUNC_FULLNAME,          /* �ӿ�������չ */
    IF_FUNC_FULLTYPE,          /* �ӿ�������չ */
    IF_FUNC_HELP,              /* ��麯���ı�־ */
    IF_FUNC_CHECK              /* ���������ı�־ */
};

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _VISP_IR_IFNET_H_ */
