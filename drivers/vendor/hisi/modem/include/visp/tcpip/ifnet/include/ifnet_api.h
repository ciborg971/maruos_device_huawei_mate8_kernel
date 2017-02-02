


#ifndef _IFNET_API_H_
#define _IFNET_API_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/**********************************************************************
*                        �����ṩ�Ĵ�����
***********************************************************************/

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
    VRP_IFNET_IS_L2IF,                   /* 57 L2IF�ӿ� */
    VRP_IFNET_L2IFVTBLNULL,              /* 58 L2IF�麯����ָ��Ϊ��*/

    /*Add for BC3D00792,DR.131��ȡ��·��״̬ start*/
    VRP_IFNET_IPOA_NOINIT,              /* 59 IPOAģ��δʹ�� */ 
    VRP_IFNET_IPOA_ERR,                 /* 60 IPOAģ��API����ʧ�� */ 
    VRP_IFNET_ETH_NOINIT,               /* 61 Ethģ��δʹ��*/ 
    VRP_IFNET_ETH_ERR,                  /* 62 Ethģ��API����ʧ�� */ 
    /*Add for BC3D00792,DR.131��ȡ��·��״̬ end*/
    VRP_IFNET_PPIGETMTU_ERR,            /* 63 ��ײ��ѯ���MTU���� */

    VRP_IFNET_L2TRUNKPHYTRANSMIT_NULL,  /* 64 ����TRUNK������㱨�ķ��ͺ���Ϊ�� */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    VRP_IFNET_VRF_ERR,                  /* 65 VRFģ��API����ʧ�� */ 
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    
    VRP_IFNET_VRF_NOT_INIT,            
    /* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
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

/**********************************************************************
*                        �����ṩ�ĺ궨�� 
***********************************************************************/

#ifndef IF_MAX_INTERFACE_NAME_LEN
#define IF_MAX_INTERFACE_NAME_LEN                 47       /* ͬiifnet_inc.h */ 
#endif
#define MAX_INTERFACE_DESCRIPTION_LEN          80       /* ������󳤶� */
#define IF_MAX_MAC_LEN                         6

#define IF_RTATTR_BROADCAST             0x2
#define IF_RTATTR_NBMA                  0X4
#define IF_RTATTR_LOOPBACK              0x8
#define IF_RTATTR_POINT2POINT           0x10
#define IF_RTATTR_MULTICAST             0x8000

#define ETHIF_DEF_MAXNUM               4096

/* �����Э������ */
#define NETPROTO_IP                    0x0001
#define NETPROTO_IPX                   0x0002
#define NETPROTO_BRIDGE                0x0004
#define NETPROTO_OSI                   0x0008
#define NETPROTO_LCP                   0x0010
#define NETPROTO_LACP                  0x0020
#define NETPROTO_IPv6                  0x0040
#define NETPROTO_PPPMUXCP              0x0080
#define NETPROTO_LQM                   0x0100
#define ALL_INDEX                      0xFFFFFFFF

/* ֪ͨ������������ */
#define IFC_LINKMSG_NOTIFY  0       /* ��·����Ϣ֪ͨ���� */
#define IFC_DEVMSG_NOTIFY   1       /* �ײ���Ϣ֪ͨ���� */ 
#define IFC_ADDIF_NOTIFY    2       /* �ӿڴ���֪ͨ���� */
#define IFC_ADDSUBIF_NOTIFY 3       /* �ӽӿڴ���֪ͨ���� */
#define IFC_DELIF_NOTIFY    4       /* �ӿ�ɾ��֪ͨ���� */
#define IFC_SHUTIF_NOTIFY   5       /* �ӿ�shutdown֪ͨ���� */

#define IFC_PRIORITY_HIGHEST   0    /* ֪ͨ���ȼ����� */
#define IFC_PRIORITY_LOWEST    5    /* ֪ͨ���ȼ����� */


/* �ӿ���·״̬ */ 
#define IF_STATUS_PROT_DOWN          0x1
#define IF_STATUS_LOW_DOWN           0x2
#define IF_STATUS_PROT_UP            0x4
#define IF_STATUS_PROT6_DOWN         0x8   /*��ʾIPv6 line protocol ����DOWN��״̬*/
#define IF_STATUS_PROT6_UP           0x10  /*��ʾIPv6 line protocol ����UP��״̬*/


/* used for if_ulShutdown */
#define IF_PHY_SHUTDOWN         1
#define IF_SHUTDOWN             ( IF_PHY_SHUTDOWN )


/*usMsgType value: */
#define RTM_CREATE  0x01    /* �ӿڡ�����·���� */
#define RTM_DEL     0x02    /* �ӿڡ�����·ɾ��*/
#define RTM_STATE   0x04    /* �ӿڡ�����·��usIfStste �� usIfFlags �����ı�*/
#define RTM_CONFIG  0x08    /* �ӿڡ�����·�Ĳ�����ϢsIfData�����ı�*/
#define RTM_BOARDREMOVE 0x10

/*usIfState value: ����������ȷ*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN
#define  OSI_UP                0x10    /*��OSICPЭ�̳ɹ���֪ͨ��Ʒ�ӿ�״̬���UP (������·��ģ��ʹ��)*/
#define  OSI_DOWN              0x20    /*��OSICPЭ��ʧ�ܣ�֪ͨ��Ʒ�ӿ�״̬���DOWN (������·��ģ��ʹ��)*/

/* l2if ifnet flag */
#define L2IF_PORT       1
#define L2IF_TRUNKPORT  2

/* NP����LCPECHO���� */
#define NP_HANDLE_LCP_ECHO   0xFFFFFFFA


typedef LONG (*FUNC_PHY_INITIAL)(VOID * , ULONG *, ULONG *, ULONG );
typedef ULONG (*FUNC_PHY_IOCTL)(VOID * , ULONG , CHAR * );

typedef ULONG (*TCPIP_GETVIADDR_HOOK_FUNC)(VOID);

/**********************************************************************
*                        �����ṩ�����ݽṹ����
***********************************************************************/
/* ���������� */
/**********************************************************
*  �ڴ˶���ioctl������case��,ע�ⲻ����syst_pub.h�е�
*  ������ DRV_TEST_ENTRY �غ�,�������������������������
\*********************************************************/
enum  enumPhyIoCtl
{
    PHY_POWERUP = 0,                    /* 0 �ϵ� */
    PHY_INIT,                           /* 1 ��ʼ����VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_SHUTDOWN,                       /* 2 �رգ�ShutDown���ײ�����ӿ� */
    PHY_NO_SHUT,                        /* 3 �򿪣�UP���ײ�����ӿ� */
    PHY_ENABLERECV,                     /* 4 ʹ�ܽ��� */
    PHY_DISABLERECV,                    /* 5 ȥʹ�ܽ��� */
    PHY_CHECKFLOW,                      /* 6 CHECKFLOW��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_BUILDRUN,                       /* 7 BUILDRUN��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_CHECK,                          /* 8 CHECK��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_DELETE,                         /* 9 ֪ͨ�ײ�ɾ������ӿ� */
    PHY_SETMACADDR,                     /* 10 ����physical��ַ */
    PHY_SETMACTABLE,                    /* 11 ����mac��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_GETMACADDR,                     /* 12 ��ȡphysical��ַ��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_MAP,                            /* 13 MAP��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_PROTOCOL_CHG,                   /* 14 ����Э������ */
    PHY_GETINFO,                        /* 15 ��ȡ�ӿ���Ϣ */
    PHY_GETSTATISTIC,                   /* 16 ��ȡͳ����Ϣ */
    PHY_CLEAR_PORT,                     /* 17 ����˿� */
    PHY_GETMAXBD,                       /* 18 GETMAXBD */
    PHY_SETLEASED,                      /* 19 SETLEASED */
    PHY_ISPURE_SYNC,                    /* 20 ISPURE_SYNC��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_ISASYNC,                        /* 21 ѯ�ʵײ���ͬ����·�����첽��·������0����ʾͬ����·������1����ʾ�첽��·��Ĭ��Ϊ0�� */
    PHY_ISSOFTCVT,                      /* 22 ѯ�ʵײ���Ӳ������������PPP���ĵ�ͬ�첽ת����0��Ӳ����ɣ�1�������ɣ�Ĭ��1��ע��ǰ�������ǵײ����첽��· */
    PHY_ATMMCLK,                        /* 23 ATMMCLK */
    PHY_ATMMSERV,                       /* 24 ATMMSERV */
    PHY_ATMMOAMPVC,                     /* 25 ATMMOAMPVC */
    PHY_ATMMOAMRETRY,                   /* 26 ATMMOAMRETRY */
    PHY_ATMAPVC,                        /* 27 ���PVC */
    PHY_ATMDPVC,                        /* 28 ɾ��PVC */
    /*added by sunyafeng for D12511 on 2002/04/05*/
    PHY_ATMINIT,                        /* 29 ATMINIT */
    /*added by lhm for D12315 on 2002/04/16*/
    PVC_STA_CHANGE,                     /* 30 ״̬�仯 */

    PHY_IMA_SETLINKNUM,                 /* 31 SETLINKNUM */
    PHY_CLI_ATMIMA_GETFRAMELENGTH,      /* 32 ATMIMA_GETFRAMELENGTH */

    /*2003/06/02 zhangwei29537,add for ima,end*/
    PHY_ATMGETPVCINFO,                  /* 33 ��ȡPVC��Ϣ��VISP�ݲ�ʹ�ã�Ԥ���� */
    PHY_LINK_DOWN,                      /* 34 ��·down */
    /*added by liuhui, for PPPoE Client, to notify PPPoE Client Link down*/
    PHY_POECLIENT_LINK_DOWN_WITHPADT,   /* 35 POEC��·��ΪPADT����down��VISP��POECģ��ʹ�ã��û����ô��� */
    PHY_POECLIENT_LINK_DOWN_NOPADT,     /* 36 POEC��·����ΪPADT����down��VISP��POECģ��ʹ�ã��û����ô��� */
    /*add ends*/
    PHY_GETMIBINFO,                     /* 37 ��ȡMIB��Ϣ */
    PHY_SETPROMODE,                     /* 38 SETPROMODE */
    PHY_SETRCVADDRSTATUS,               /* 39 SETRCVADDRSTATUS */
    /* �жϵײ��Ƿ�UP 2001-03-26 */
    PHY_ISUP,                           /* 40 �ж��Ƿ�UP��VISP��POECģ��ʹ�ã��û����ô��� */
    /* Notify low layer ACCM */
    PHY_SETACCM,                        /* 41 SETACCM��֪ͨ�ײ�ͬ�첽ת���ַ�����ACCM��ע��ǰ�������ǵײ�Ϊ�첽��· */
    /* for D10708 */
    PHY_GET_HARD_INFO,                  /* 42 GET_HARD_INFO */
    /*add by huzhiyong 2001/12/19 */
    PHY_GETASYNMODE,                    /* 43 GETASYNMODE */
    PHY_ENABLE,                         /* 44 ʹ�� */
    PHY_DISABLE,                        /* 45 ȥʹ�� */
    PHY_INIT_BUFFER,                    /* 46 ��ʼ�������� */
    PHY_GET_VER,                        /* 47 GET_VER */
    PHY_GETPHYSTATUS,                   /* 48 GETPHYSTATUS */
    PHY_DEBUG,                          /* 49 DEBUG */
    PHY_SETLOOPBACK,                    /* 50 SETLOOPBACK */
    PHY_E1DELETE,                       /* 51 E1DELETE */
    PHY_LINECODE,                       /* 52 LINECODE */
    PHY_FRAMING,                        /* 53 FRAMING */
    PHY_LINECLOCK,                      /* 54 LINECLOCK */
    PHY_E1BUILDRUN,                     /* 55 E1BUILDRUN */
    PHY_BOARD_RESET,                    /* 56 BOARD_RESET */
    PHY_E1CHECKSTAT,                    /* 57 E1CHECKSTAT */
    PHY_T1DELETE,                       /* 58 T1DELETE */
    PHY_T1BUILDRUN,                     /* 59 T1BUILDRUN */
    PHY_T1CHECKSTAT,                    /* 60 T1CHECKSTAT */
    PHY_CHANNEL_SPEED,                  /* 61 CHANNEL_SPEED */
    PHY_T1_CABLE,                       /* 62 T1_CABLE */
    PHY_READREG,                        /* 63 READREG */
    PHY_WRITEREG,                       /* 64 д�Ĵ��� */
    PHY_SETPORT,                        /* 65 SETPORT��VISP��δʹ�ã�Ԥ���� */
    /*2003/06/02 zhangwei29537,add for ima,begin*/        
    PHY_ADDLINK,                        /* 66 PHY_ADDLINK */
    PHY_DELELELINK,                     /* 67 PHY_DELELELINK */
    PHY_CANDELELTE,                     /* 68 PHY_CANDELELTE */
    /*2003/06/02 zhangwei29537,add for ima,end*/ 
    PHY_LOOPBACK_STATE,                 /* 69 PHY_LOOPBACK_STATE */
    PHY_IPV6_ADD_MCAST_ADDR,            /* 70 PHY_IPV6_ADD_MCAST_ADDR */
    PHY_IPV6_DEL_MCAST_ADDR,            /* 71 PHY_IPV6_DEL_MCAST_ADDR */
    /*This 2 value were moved here by ZhuKun 36377,20040827,For D00575*/
    PHY_JOINMULTI,                      /* 72 ����ಥ�� */
    PHY_LEAVEMULTI,                     /* 73 �뿪�ಥ�� */
    PHY_GET_ROUTFLAG,                   /* 74 ��ȡUI�ӿ�·������ */
    PHY_GETDOWNMODE,                    /* 75 ɾ���ӿڻ�shutdown�ӿڣ���ȡ�ײ���DownAll(����TR����)����Down(������TR����) */
    PHY_ADD_VRRP_VIRTUAL_MAC,           /* 76 ���VRRP����MAC */
    PHY_DEL_VRRP_VIRTUAL_MAC,           /* 77 ɾ��VRRP����MAC */
    PHY_ENABLE_VRRP,                    /* 78 ʹ��/ȥʹ��VRRP������ */
    PHY_LCPECHOOPEN,                    /* 79 LCP Echo Open������ */
    PHY_LCPECHODOWN,                    /* 80 LCP Echo Open������ */
    PHY_LCPECHOSETCONF,                 /* 81 LCP Echo Open������ */

    PHY_GETINTFSTATUS,                  /* 82 ��ѯ�ӿ�״̬������ */
    PHY_GETINTFTYPE,                    /* 83 ��ѯ�ӿ����������� */

    PHY_MAX_PHYWORD  /*No use actually.Just for adding enum word easily. ZhuKun,20041020*/
};
/* �ײ��ϱ���Ϣ */
enum enumLowToUp
{
    ISLUP = 0,              /* 0 �ײ��ϱ����˽ӿ�UP��Ϣ */
    ISLDOWN,                /* 1 �ײ��ϱ����˽ӿ�DOWN��Ϣ */
    ISLCHGBAUD,             /* 2 ���������������֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLASYTOSYN,            /* 3 ͬ�첽���������֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLSYNTOASY,            /* 4 ͬ�첽���������֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLSHUTDOWN,            /* 5 SHUTDOWN�����֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLNOSHUT,              /* 6 UNSHUTDOWN�����֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLDELETE,              /* 7 ɾ�������֣�VISP�ݲ�����������֣�Ԥ���� */
    ISLCHGPROTOCOL,         /* 8 �ı�Э�����ͣ�VISP�ݲ�����������֣�Ԥ���� */
    ISLGETPROTOCOL,         /* 9 ��ȡЭ�����ͣ�VISP�ݲ�����������֣�Ԥ���� */
    ISLSETMAC,              /* 10 ����physical��ַ */
    /*D18794*/
    ISLSPEED,               /* 11 �������������� */
    /* 2001/02/22 sunshengtao */
    ISLATMOAMSTATE,         /* 12 ����ATM��ά�ɲ�״̬�����֣�VISP�ݲ�����������֣�Ԥ���� */
     
     /* This 2 value were deleted by ZhuKun 36377, 20040827, For D00575 */
     /* ,ISLJOINMULTI, */ /*add by luohanjun*/
     /* ISLLEAVEMULTI */
     
    ISLDOWNALL,             /* 13 (������PPP�ӿ�)�ײ��ϱ�����PPP�ӿ�DOWN��Ϣ,��֪ͨ�Զ�PPP�ӿ�ҲDOWN */ 
    ISLDUPLEX,              /* 14 visvp1r7c03,l2if ADD, �ײ��ϱ�˫��ģʽ */

    /* OAM-3ah�ϱ���״̬ */
    ISLEFMNORMAL,           /* 15 3ah�ϱ���Normal״̬ */
    ISLEFMUP,               /* 16 3ah�ϱ���Up״̬ */
    ISLEFMDOWN,             /* 17 3ah�ϱ���Down״̬ */
    
    ISLPPPNPLOOKBACK,       /* 18 NP̽�⵽�Ի� */
    ISLPPPNPLCPDOWN,        /* 19 NP̽�⵽LCP Down */
    ISLPPPNPINTERCROSS,     /* 20 NP̽�⵽���� */

    ISLNEEDRESENDARP,

    /* Modified by lihaiming218630, nsr��������1way hello, 2013/4/20   ���ⵥ��:lhm */
    LSIFFINISH,             /*22 NSRʵ���У�������ײ��ϱ������нӿ�״̬�󣬻��ϱ�һ��finish*/    
    /*End of Modified by lihaiming218630, 2013/4/20   ���ⵥ��:lhm */

    ISSETLINESTATUS,        /*23 ������·״̬ */
    
    ISMAX_END     
};

/*�ӿڵ�����״̬(��ӦIFNET_S��if_ulPhyStatus�ֶ�*/
enum enumPhyStatus{
    IF_NORMAL= 0,           /* 0  Normal*/
    IF_STATUS_UP,           /* 1  UP*/
    IF_STATUS_DOWN,         /* 2  Down*/
    IF_STATUS_SPOOFING,     /* 3  spoofing*/
    IF_STATUS_STANDBY,      /* 4  stand by*/
    IF_STATUS_SHUTDOWN,     /* 5  shut down */
    IF_STATUS_NOTUSED,      /* 6  not use*/
    IF_STATUS_DELETE,       /* 7  delete*/
    IF_STATUS_NOTEXIST,     /* 8  not exist*/
    IF_STATUS_REMOVE,       /* 9  remove*/
    IF_STATUS_END
};

#define IF_1D_MODE 0                 /* ��ʾһά�ӿ� */
#define IF_3D_MODE_DISTRIBUTE 1      /* ��ʾ��ά�ֲ�ʽ�ӿ� */
#define IF_3D_MODE_CENTRAL 2         /* ��ʾ��ά����ʽ�ӿ� */
/*�ӿ�����(��ӦIFNET_S��if_ulType�ֶ�*/
enum enumIFTYPE
{
    IF_ASYNC_TYPE=0,
    IF_AUX_TYPE,  
    IF_NULL_TYPE,   
    IF_LOOPBACK_TYPE,
    IF_LOOP_TYPE,
    IF_SERIAL_TYPE,
    IF_CONSOLE_TYPE,
    IF_ETHERNET_TYPE,

    IF_VIRTUAL_TEMPLATE_TYPE,       
    IF_VLAN_TYPE,
    IF_POS_TYPE,    
    IF_VIRTUAL_ETHERNET_TYPE,
    IF_GIGABYTE_ETHERNET_TYPE,

    IF_GROUPE1_TYPE,        
    IF_ATM_TYPE,
    IF_BRI_TYPE,
    IF_E1_TYPE,
    
    IF_MPGROUP_TYPE,
    IF_DIALER_TYPE,
    IF_MTUNNEL_TYPE,

    /*VISP.III ����VA�ӿ�����*/
    IF_TEMPLATE_CHAN_TYPE,  /*ģ���µ�VA�ӿ�*/
    IF_VIRTUAL_ACCESS_TYPE, /*Dialer�µ�VA�ӿ�*/

    /* VISPV1R6����Trunk�ӿ����� */
    IF_ETH_TRUNK_TYPE,    /* ��̫Trunk�ӿ� */

    IF_VI_TYPE,         /*VI �ӿ�*/

    IF_UI_TYPE,         /*UI �ӿ�*/
    IF_TUNNEL_TYPE,
    
    IF_MAX_TYPE,
    IF_OTHER_TYPE = 0xFFFF
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
/* #if (VRP_IFNET_E1_T1_E3_T3_CPOS == VRP_YES) */
    PORT_E3,
    PORT_T3,
    PORT_CPOS,
/* #endif */
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

/*IPЭ��״̬(��ӦTCPIP_SetIpProtocolState�����ulState*/
typedef enum IP_PROTOCOL_ENUM
{
    TCPIP_IP_PROTOCOL_UP,           /* �ӿ�IPЭ��UP */
    TCPIP_IP_PROTOCOL_DOWN          /* �ӿ�IPЭ��DOWN */
}IP_PROTOCOL_ENUM;

/* VISPV1R7C03,�ײ��ϱ���ȫ˫��/��˫��״̬ */
typedef enum enPhyDuplex
{
    TCPIP_DUPLEX_FULL,    /* ȫ˫��,ETH�ӿڳ�ʼ��ʱĬ��ֵ */
    TCPIP_DUPLEX_HALF,    /* ��˫�� */
}PHY_DUPLEX_EN;

/*Add for BC3D00792,DR.131��ȡ��·��״̬*/
typedef enum IF_LINK_STATUS_ENUM
{
    TCPIP_NOMAL = 0x0,             /* �ӿ����޸�����״̬*/
    TCPIP_PROT_DOWN = 0x1,         /* IF_STATUS_PROT_DOWN*/
    TCPIP_LOW_DOWN = 0x2,          /* IF_STATUS_LOW_DOWN */
    TCPIP_PROT_UP = 0x4,           /* IF_STATUS_PROT_UP */
}IF_LINK_STATUS_ENUM;

typedef struct  tagIF_LINKSTATUS_S
{
    ULONG   ulIfLinkStatus;
    ULONG   ulIfLink6Status;
}IF_LINKSTATUS_S;
/*Add for BC3D00792,DR.131��ȡ��·��״̬*/

typedef struct  tagIF_Config
{
    USHORT  usIfDelay;
    USHORT  usIfReliability;
    USHORT  usIfLoad;
    UCHAR   ucPadding[2]; 
    ULONG   ulIfBandwidth;
    ULONG   ulIfBaudrate;
    ULONG   ulIfMtu;
    /*add sunyu for bandwidth,delay command*/
    ULONG   ulConfIfDelay;
    ULONG   ulConfIfBandwidth;
    /*end add sunyu for bandwidth,delay command*/

    ULONG   ulData;
} IF_CONFIG_S;

#define CONFIG_MTU    0x01  /*VLINKSTATUS_S��RTM_CONFIG���,��ʾMTU�仯*/
#define CONFIG_SPEED  0x00  /*VLINKSTATUS_S��RTM_CONFIG���,��ʾSPEED�仯*/

typedef struct tagVLINKSTATUS_S
{
    ULONG  ulIntfIndex;     /* �ӿ�Ψһ����ֵ */
    ULONG  ulVlinkIndex;    /* ����·����ֵ����ߵ�һ�ֽ�Ϊͬ���ţ������ֽ�Ϊ�����š��ӿ��¼�ʱ��Ϊ0 */
    USHORT  usSlot;         /* �ӿ����ڲۺţ�new in 3.0 */
    USHORT  usMsgType;      /* �����涨�� */
    USHORT  usIfState;      /* �ӿ�״̬ */
    USHORT  usIfFlags;      /* �ӿڱ�־ */        
    CHAR    cIfName[IF_MAX_INTERFACE_NAME_LEN + 1];    /* �ӿ����� */
    USHORT  usIfType;       /* �ӿ����� */
    USHORT  usConfigTag;    /*RTM_CONFIG�ı�ǣ�CONFIG_MTUΪMTU�ı�, CONFIG_SPEEDΪ�����ʸı�*/
    IF_CONFIG_S  stIfData;
    SOCKADDR_S  stPeerAddr; /* �Զ˵�ַ����������·ʱ�����жԶ˵�ַ */
    ULONG ulMacAddrLen;
    UCHAR ucMacAddr[IF_MAX_MAC_LEN + 1];
    UCHAR ucPadding_2; 
    /*added by roy to support vpn at 20031019*/
    ULONG ulVrfIndex;
    /*end added by roy to support vpn at 20031019*/    

}VLINKSTATUS_S;



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


typedef struct tagDEVLINK
{
#define DEVICE_NAME_LEN 50
    CHAR   dev_pDeviceName[DEVICE_NAME_LEN];
    USHORT dev_usSlot;           /* ���ֶ�VISP��ǰδʹ�ã�����PARC1.9��Ʒ�У������ڱ�����·������Ϣ */
                                 /* ���߲�Ʒ�õ����ֶ� */
                                 /* SGSN�õ����ֶ� */
    USHORT dev_usAdaptor;        /* ���ֶ�VISP��ǰδʹ�ã�����PARC1.9��Ʒ�У������ڱ�����·������Ϣ */
                                 /* SGSN�õ����ֶ� */
    USHORT dev_usUnit;           /* ���ֶ�VISP��ǰδʹ�ã�����PARC1.9��Ʒ�У������ڱ�����·������Ϣ */
                                 /* ���߲�Ʒ�õ����ֶ� */
                                 /* SGSN�õ����ֶ� */
                                 /* NodeBV1�汾�У����ڱ���˿ںŻ���ͨ�������� */
    USHORT dev_usSubChan;        /* ���ֶ�VISP��ǰδʹ�ã�����PARC1.9��Ʒ�У������ڱ�����·������Ϣ */
    USHORT dev_usMaxChannel;
    USHORT dev_usAuxFlag;        /* wether a AUX. 1 - aux, 0 - not aux. */
    USHORT dev_usIntPri;
    ULONG  dev_ulFlag;
    ULONG  dev_ulIf;
    /* add by xiehuaguo for support np */
    ULONG  dev_ulTimeSlotBitMap;       /* ��ͨ��ռ�õ�ʱ϶��ÿ�����ر�ʾһ��ʱ϶��Ϊ1ʱ��ʾ���ö�Ӧ��ʱ϶��
                                                Ϊ0ʱ��ʾ�����ö�Ӧ��ʱ϶ */
                                       /* ���ֶ�VISP��ǰδʹ�ã�����PARC1.9��Ʒ�У������ڱ�����·������Ϣ */
                                       /* ���߲�Ʒ�õ����ֶ� */
    ULONG  dev_ulBandWidth;            /* �ӿڴ��� */
    FUNC_PHY_INITIAL   dev_pfInitial;  /* �豸��ʼ������ */
    FUNC_PHY_IOCTL     dev_pfIoCtl;    /* �豸���ƺ��� */
    struct  tagDEVLINK *dev_pNext;     /* point to the next node in link */
}DEVLINK_S;

#ifndef _IN6ADDR_S
#define _IN6ADDR_S
typedef   struct    tagIN6Addr
{
    union
    {
        UCHAR     u6_ucaddr[16];
        USHORT    u6_usaddr[8];
        ULONG     u6_uladdr[4];
    } u6_addr;    /* 128-bit IP6 address */
} IN6ADDR_S;
#endif
/* Ϊ�����÷��㣬�������º궨��*/
#ifndef s6_addr
#define s6_addr      u6_addr.u6_ucaddr
#endif
#ifndef s6_addr8
#define s6_addr8     u6_addr.u6_ucaddr
#endif
#ifndef s6_addr16
#define s6_addr16    u6_addr.u6_usaddr
#endif
#ifndef s6_addr32
#define s6_addr32    u6_addr.u6_uladdr
#endif

typedef struct tagTCPIP_IFNET
{
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];           /* �ӿ���*/
    CHAR  if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ]; /* �ӿ������ַ��� */
    UCHAR ucPadding_1[3]; 

    ULONG if_ulIfIndex;             /* VISP˽�������ṹ */
    ULONG if_ulProductIfIndex;      /* ���Ʒ��صĽӿ����� */       
    
    ULONG if_ulSlotNum;         /* ��16λΪ���ţ���16λΪ�ۺ� */
    ULONG if_ulTopIfIndex;      /* �ýӿڵ����ø��׵����� */
    ULONG if_ulNetIfIndex;      /* �ýӿڵ��������Ը��׵����� */

    ULONG if_ulIsisFlag ;       /* �ӿ���ISISʹ�ܱ�־ */

    /* �˿����� */
    ULONG if_ulSpoofing;            /* Spoofing ��ʶ��1��ʾ���� spoofing ����, 0��ʾ������������� */
    ULONG if_ulMoving;        
    ULONG if_ulShutdown;            /* shutdown��ʶ,&IF_SHUTDOWN�ǿձ�ʾִ����shutdown����������û��ִ�� */
    ULONG if_ulSubIndex;            /*  0 ��ʾ���ӽӿڣ���0 ��ʾ�ӽӿ�(�ӽӿڱ��) */   
    ULONG if_ulSubIfNum;            /*  �ýӿ������õ��ӽӿ��� */
    ULONG if_ulLineProtocol;        /* �˿ڷ�װ����·��Э�� */
    ULONG if_ulLineStatus;          /* �˿�Э��״̬, 1 ΪUP, 2ΪDOWN*/
    ULONG if_ulPhyStatus;       /* �˿�����״̬�������ӽӿ���˵�������ӿ�״̬ */

    ULONG if_ulLine6Status;         /* �˿�Э��״̬, 1 ΪUP, 0ΪDOWN*/      
    ULONG if_ulPhyType;             /* �˿ڵ��������� */
    ULONG if_ulPortType;            /* �˿ڵ����� */
    
    /* ��������·��ģ����ص���Ϣ */
    ULONG if_ulBaud;        /* �˿ڵĲ����� */
    ULONG if_ulMTU;         /* Э����Ч��MTU */
    ULONG if_ulCfgMTU;      /* ����MTU */
    ULONG if_ulFlags;       /* P-P��NBMA��Broadcast ,  ��ʾ�ӿڵ�·������ */    
    ULONG if_ulKeepAlive;   /* ��·��Э���ú���·��̽����·״̬�� */    
        
    /* ����Ϊ��չ���� */
    ULONG if_ulBandWidth;       /* ��¼�ӿ�ȱʡ��bandwidth, ���ڽӿڳ�ʼ��ʱ�Ĳ����� */
    ULONG if_ulCfgBandWidth;    /* ��¼�ӿ����õ�bandwidth, ����������, ��ֵΪ0 */    
    ULONG if_ulType;           /*�ӿ�����*/    

    /* VISPV1R7C03 L2IF ���� */
    ULONG  if_ulL2OrL3;         /* �ӿڵĶ��������Ա��: 0��ʾ����ӿ�,1��ʾL2IF_PORT,2��ʾL2IF_TRUNKPORT */

    ULONG  if_ulDuplexStatus;   /* �ӿ�ȫ˫��/��˫������״̬,�ɵײ��ϱ�,ֻ��ETH��Ч.ȡֵPHY_DUPLEX_EN */

    /* OAMЭ����չ֧��������Ϣ�����ֶ� */
    ULONG if_ulRawPhyStatus;    /* ����ײ��ϱ���ԭʼ����״̬ */
    ULONG if_ulPhyDetectStatus; /* ����OAM״̬���ӿ�OAM״̬���������֣�0 EFMNORMAL��1 EFMUP��2 EFMDOWN */

    /* ��¼�ӿ�����Э��UP/Down�仯���� */
    ULONG if_ulPhyUpCount;      /* �ӿڱ仯������UP���� */
    ULONG if_ulPhyDownCount;    /* �ӿڱ仯������Down���� */
    ULONG if_ulLineUpCount;     /* �ӿڱ仯��Э��UP���� */
    ULONG if_ulLineDownCount;   /* �ӿڱ仯��Э��Down���� */
    
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG if_ulVrfIndex;
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    ULONG ip6if_ulMtu;
}TCPIP_IFNET_S;

/*����ӿ��·�PPI��Ϣ����*/
#define TUNNEL_PPI_ADD  0x1
#define TUNNEL_PPI_DEL   0x2

/*���IP�汾��ʶ*/
#define TUNNEL_IP_VERSION_IPV4    0x1 /*IPv4�汾*/
#define TUNNEL_IP_VERSION_IPV6    0x2 /*IPv6�汾*/

/*���Э��ģʽ*/
#define TUNNEL_MODE_TYPE_NONE   0x0  /*���Э��Ϊ��*/
#define TUNNEL_MODE_TYPE_GRE    0x1  /*GRE���Э��*/

/* v6��ַ���� */
#define TCPIP_ADDR_LINKLOCAL_FLAG  0x1
#define TCPIP_ADDR_GLOBAL_FLAG     0x2

typedef struct tagTCPIP_TUNNEL_IF_PPI
{
    ULONG  ulMsgType;      /*��Ϣ���ͣ�ָ�����ò�������ɾ������*/
    ULONG  ulIpVer;        /* IP�汾��ʶ:TUNNEL_IP_VERSION_IPV4--IPv4;TUNNEL_IP_VERSION_IPV6--IPv6 */
    ULONG  ulProMode;      /* ���Э��ģʽ*/
    ULONG  ulDstIP[4];     /* �����Ŀ�ĵ�ַ��������V4��ַulDstIP[0]��Ч*/
    ULONG  ulSrcIP[4];     /* �����Դ��ַ��������V4��ַulSrcIP[0]��Ч*/
    ULONG  ulGreKey;       /* GRE Key����ΧΪ0~0xFFFFFFFF*/
    UCHAR  ucNeedGreKey;   /* ��ʶ�û��Ƿ�������Gre key��1(VRP_YES)��ʾ����Gre Key�� 0(VRP_NO)��ʾ������Gre Key*/
    UCHAR  ucPad[3];       /* �����ֶ�*/
}TCPIP_TUNNEL_IF_PPI_S;

/**********************************************************************
*                        �����ṩ���û�API����
***********************************************************************/

/*�ӿ�������ģʽԤ���������������Խ��ӿ�����ת��ΪĳЩ������������port index*/
typedef VOID (*IF_MSG_NOTIFYFN)( ULONG ulIfIndex, ULONG ulCmd, CHAR *pcData);
typedef VOID (*IF_LMSG_NOTIFYFN)( ULONG ulProtocol,ULONG ulIfIndex, ULONG ulCmd, CHAR *pcData);

typedef VOID (*IF_PTR_NOTIFYFN)(ULONG ulIfIndex);/*֪ͨ�ӿ����ӡ�ɾ�����رգ�����Ϊ�ӿ�ָ��*/

typedef ULONG (*IF_TRANSMIT_FUNC)(ULONG,MBUF_S *);
typedef ULONG (*IF_PHYIOCTL_FUNC)(ULONG, ULONG, CHAR *);
typedef ULONG (*LinkMsgSend_HOOK_FUNC)(VLINKSTATUS_S *pstIFNETMsg);
/* Added by hanna55555, VISPV1R8C03, 2009/12/1 */
typedef ULONG(*LinkMsg6Send_HOOK_FUNC)(IFVLINKENTRY6_S *pstIFNETMsg);
/*End of Added by hanna55555, 2009/12/1 */
typedef ULONG (*ATMLinkIntVTable_HOOK_FUNC)(VOID** ppstLinkInt);
typedef VOID  (*NotifyIfState_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulProtoType, ULONG ulIFState);
typedef ULONG (*VIOutput_HOOK_FUNC)(MBUF_S* pstMbuf);

typedef ULONG (*L2Trunk_PhyTransmit_HOOK_FUNC)(ULONG ulIfIndex, MBUF_S* pstMbuf);

/* Description:Ϊ���������RPU��Ӧ��,VISPʵ��L2 TrunkĬ�ϵķַ�����:��VISPĬ��ѡ�����
               Trunk��һ����Ա�˿ڽ��б��ķ���.���͹�����ͬʱЯ��Tunrk�ӿ�������Ĭ��ѡ���
               һ����Ա�˿ڵĽӿ�����,���û����о���ʹ���ĸ����� 
   Parameter : ULONG ulTrunkIfIndex: L2 Trunk�ӿ�����
               ULONG ulTrunkPortIfIndex:VISPĬ��ѡ���һ����Ա�˿ڵĽӿ�����
               MBUF_S *pstMbuf:����*/
typedef ULONG (*L2TrunkPort_PhyTransmit_HOOK_FUNC)(ULONG ulTrunkIfIndex, 
                                                           ULONG ulTrunkPortIfIndex,
                                                           MBUF_S *pstMbuf);

typedef ULONG (*IF_VLANCHECKFN)(VOID *pIf);

/* ��Ʒע����·�㷢�ͺ������ҿ�����ά��ӿ��� */
typedef ULONG (* Interface3dOutput_HOOK_FUNC) (MBUF_S *pMBuf);
typedef ULONG (*PhySetDevLink_HOOK_FUNC)(VOID);

/* ��Ʒע��Ľӿ�QoS���ͺ���ԭ�� */
typedef ULONG (*IF_QosTransmitDone_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
typedef ULONG (*IF_QosTransmit_HOOK_FUNC)(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (* IF_PROD_CHECK_HOOK_FUNC) (CHAR *szFullName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

typedef ULONG (* IF_GET_VLINK_INDEX_HOOK_FUNC) (ULONG ulIfIndex,ULONG ulNextHop,ULONG ulVrfIndex,ULONG *pulVLinkIndex);

typedef struct tagTCPIP_ADDR_INFO
{
    ULONG ulIfIndex;
    IN6ADDR_S stDestAddr;
    IN6ADDR_S stSrcAddr;
    ULONG ulFlag;
}TCPIP_ADDR_INFO_S;

typedef struct tagTCPIP_ADDR_HOOK
{
    ULONG (*pfIF_MATCHSRCADDR_FUNC)(TCPIP_ADDR_INFO_S *pstMatchSrcAddr);
    ULONG (*pfIF_ISLOCALADDR_FUNC)(TCPIP_ADDR_INFO_S *pstLocalAddr);
    ULONG (*pfIF_HAVEADDRCHECK_FUNC)(TCPIP_ADDR_INFO_S *pstAddrCheck);
}TCPIP_ADDR_HOOK_S;



extern ULONG TCPIP_ShutDownIf(ULONG ulIfIndex);

extern ULONG  TCPIP_CloseIfConfigEntry( UINTPTR ulWaitListHandle );

extern ULONG  TCPIP_CreateIFByDev( DEVLINK_S * pstDev, ULONG *pulIfIndex );

extern ULONG  TCPIP_DeleteIF( ULONG ulIfIndex );

extern ULONG  TCPIP_DynamicCreateIF( CHAR* szFullName,  ULONG *pulIfIndex );


extern ULONG TCPIP_RegFuncL2TrunkPhyTransmitHook(L2Trunk_PhyTransmit_HOOK_FUNC pfHookFunc);


extern ULONG TCPIP_RegFuncL2TrunkPortPhyTransmitHook(L2TrunkPort_PhyTransmit_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_CreateL2Trunk
* Date Created: 2008-11-18
*       Author: LY(57500)
*  Description: ����L2 trunk�ӿ�
*        Input: CHAR* szFullName: �ӿ���
*               ULONG *pulIfIndex: ��������ӿڵĽӿ�����
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-18    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_CreateL2Trunk(CHAR* szFullName, ULONG *pulIfIndex);


extern ULONG  TCPIP_GetConfigMtu( ULONG ulIfIndex, ULONG *pulMtu );

extern ULONG  TCPIP_GetFullNameByIfIndex( ULONG ulIfIndex,CHAR *pszIfName );

extern ULONG  TCPIP_GetIfConfigEntry( UINTPTR ulEntryWaitList, TCPIP_IFNET_S * pstIfConfig );

extern ULONG  TCPIP_GetIfIndexByFullName( CHAR *pszIfName, ULONG *pulIfIndex );

extern ULONG  TCPIP_GetIfindexByPortInfo( ULONG *pulIfIndex, ULONG ulPortType,  ULONG ulPortNo);

extern ULONG  TCPIP_GetIfnetHADbg( ULONG *pulDbg );

extern ULONG  TCPIP_GetIsisFlag(  ULONG ulIfIndex ,ULONG *pulFlag );

extern ULONG  TCPIP_GetKeepAliveValue( ULONG ulIfIndex, ULONG *pulValue );

extern ULONG  TCPIP_GetLinkMtu( ULONG ulIfIndex, ULONG *pulMtu );

extern ULONG  TCPIP_GetLinkState( ULONG ulIfIndex, ULONG *pulState );


extern ULONG  TCPIP_GetIP6LinkState(ULONG ulIfIndex, ULONG *pulState);


extern ULONG  TCPIP_GetPhyCtlBlk( ULONG ulIfIndex,UINTPTR *pulPhyCtlBlk );

extern ULONG   TCPIP_GetPortInfo( ULONG ulIfIndex, ULONG *pulPortType, ULONG *pulPortNo);

extern ULONG  TCPIP_IF_LinkIoCtl( ULONG ulIfIndex, ULONG ulCmdIndex, CHAR *pData );

extern ULONG  TCPIP_IF_LinkReceived( ULONG ulIfIndex,MBUF_S *pstMbuf);

extern ULONG  TCPIP_OpenIfConfigEntry( UINTPTR *pulWaitListHandle );

extern ULONG  TCPIP_RegFuncATMLinkIntVTableHook( ATMLinkIntVTable_HOOK_FUNC pfHookFunc );

extern ULONG  TCPIP_RegFuncIFNotifyHook( ULONG ulType, ULONG ulPriority, VOID *pfNotifyFn );

extern ULONG  TCPIP_RegFuncLinkMsgSendHook( LinkMsgSend_HOOK_FUNC pfHookFunc  );

extern ULONG  TCPIP_RegFuncNotifyIfStateHook( NotifyIfState_HOOK_FUNC pfHookFunc );


extern ULONG  TCPIP_RegFuncPhyIoCtlHook( ULONG ulIfIndex,IF_PHYIOCTL_FUNC pfPhyIocl );

extern ULONG  TCPIP_RegFuncPhyTransmitHook( ULONG ulIfIndex,IF_TRANSMIT_FUNC pfTransmitFn );

extern ULONG  TCPIP_RegFuncVIOutputHook( VIOutput_HOOK_FUNC pfHookFunc );

extern ULONG  TCPIP_ResumeIf( ULONG ulIfIndex );

extern ULONG  TCPIP_SetIfnetHADbg( ULONG ulDbg );

extern ULONG  TCPIP_SetIsisFlag( ULONG ulIfIndex ,ULONG ulFlag );

extern ULONG  TCPIP_SetKeepAliveValue( ULONG ulIfIndex, ULONG ulValue );

extern ULONG  TCPIP_SetLinkMtu( ULONG ulIfIndex, ULONG ulMtu);

extern ULONG  TCPIP_SetPhyCtlBlk( ULONG ulIfIndex,UINTPTR ulPhyCtlBlk );

extern ULONG  TCPIP_UnRegFuncIFNotifyHook ( ULONG ulType, VOID *pfNotifyFn );

extern ULONG  TCPIP_QosTransmitDone(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
/*��չ֧����ά�ӿ���ص��û�API*/
/*******************************************************************************
*    Func Name: TCPIP_SetIFDimension
*  Description: ���ñ���ӿڵ�һ��άֵ��
*        Input: ULONG ulPara1:�ӿڵ�һάֵ
*               ULONG ulPara2:�ӿڵڶ�άֵ
*       Output: 
*       Return: VRP_IFNET_HA_IS_SMOOTHING:  ϵͳ����ƽ�����ֶ������׶�
                VRP_IFNET_PARA_INVALID:     ��������
                VRP_IFNET_DIMENSION_MULTI:  ����ظ�����
                VRP_IFNET_NOERR:            ����ɹ�
*      Caution: ��Э��ջ��ʼ����������������·�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIFDimension(ULONG ulPara1, ULONG ulPara2);
/*******************************************************************************
*    Func Name: TCPIP_GetIFDimension
*  Description: ��ȡ����ӿڵ�һ��άֵ
*        Input: 
*               
*       Output: ULONG* pulPara1
                ULONG* pulPara2
*       Return: VRP_IFNET_NULLPOINTER:ָ��Ϊ��
                VRP_IFNET_NOERR:      ����ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIFDimension(ULONG* pulPara1, ULONG* pulPara2);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncInterface3dOutputHook
*  Description: ע���Ʒ���͹��Ӻ���
*        Input: Interface3dOutput_HOOK_FUNC pfHookFunc
*               
*       Output: 
*       Return: VOS_ERR
                VOS_OK
*      Caution:��άģʽ��,���ڷǱ���ӿڵķ��ͺ���ָ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/

extern ULONG TCPIP_RegFuncInterface3dOutputHook(Interface3dOutput_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_GetPortInfoEx
*  Description: ���ݽӿ�������ȡ�ӿڵ�һ����άֵ
*        Input: ULONG ulIfIndex:    �ӿ�����
*               
*       Output: ULONG *pulPortType: �˿�����
                ULONG *pulFirstDim: �ӿڵ�һάֵ
                ULONG *pulSecondDim:�ӿڵڶ�άֵ
                ULONG *pulThirdDim: �ӿڵ���άֵ
*       Return: VOS_ERR
                VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wangbin(62223)           Create
*
*******************************************************************************/

extern ULONG  TCPIP_GetPortInfoEx(ULONG ulIfIndex, 
                                  ULONG *pulPortType, 
                                  ULONG *pulFirstDim,
                                  ULONG *pulSecondDim,
                                  ULONG *pulThirdDim);
/*******************************************************************************
*    Func Name: TCPIP_GetIfindexByPortInfoEx
*  Description: ���ݽӿ����ͼ��ӿڵ�һ����άֵ��ȡ�ӿ�����
*        Input: ULONG ulPortType:   �˿�����
*               ULONG pulFirstDim:  �ӿڵ�һάֵ
*               ULONG ulSecondDim:�ӿڵڶ�άֵ
*               ULONG ulThirdDim: �ӿڵ���άֵ
*       Output: ULONG ulIfIndex:  �ӿ�����
*       Return: VOS_ERR
                VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-20   wangbin(62223)                Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfindexByPortInfoEx(ULONG *pulIfIndex, 
                                          ULONG ulPortType,  
                                          ULONG ulFirstDim,
                                          ULONG ulSecondDim,
                                          ULONG ulThirdDim);
/*******************************************************************************
*    Func Name: TCPIP_SetIpProtocolState
*  Description: ������ά����ӿڵ�IPЭ��״̬
*        Input: ULONG ulIfIndex:
*               ULONG ulState:
                        0:TCPIP_IP_PROTOCOL_UP:     IPЭ��UP
                        1:TCPIP_IP_PROTOCOL_DOWN:   IPЭ��DOWN
*       Output: 
*       Return: VRP_IFNET_HA_IS_SMOOTHING:          ϵͳ����ƽ�����ֶ������׶�
                VRP_IFNET_PARA_INVALID:             ��������
                VRP_IFNET_NOT_3D_MODE:              ����άģʽ��
                VRP_IFNET_ENOSUCHIF:                �ӿ�ָ��Ϊ��
                VRP_IFNET_NOERR:                    ����ɹ�
*      Caution: �ýӿ���ʵ�ӿ����ϱ���Ʒȫ�ֹ���ģ����ڷַ����õ��Ǳ����Ӧ��ӿ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-14   wangbin62223                Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIpProtocolState(ULONG ulIfIndex,ULONG ulState);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetCrossVIAddr
*  Description: ע�ṳ�Ӻ������Ի�ȡ���ӿ�ΪVI�ı���Դ��ַ
*        Input: TCPIP_GETVIADDR_HOOK_FUNC pfHookFunc: ���Ӻ���,���ص�ַΪ������
*       Output: 
*       Return: VOS_OK: �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-4-2    wujie(61195)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncGetCrossVIAddr(TCPIP_GETVIADDR_HOOK_FUNC pfHookFunc);

extern ULONG TCPIP_QosTransmit(ULONG ulIfIndex, UINTPTR ulPhyLink, MBUF_S *pMBuf);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncPhySetDevLink
*  Description: ע���ʼ���豸���Ĺ��Ӻ���
*        Input: PhySetDevLink_HOOK_FUNC pfHookFunc:�豸����ʼ���Ĺ��Ӻ���
*       Output: 
*       Return: �ɹ�: VRP_IFNET_NOERR; ʧ��: VRP_IFNET_NULLPOINTER
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-06-17   XiongChangSheng36317    Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPhySetDevLink(PhySetDevLink_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_IF_RegFuncQosTransmitDoneHook
*  Description: ��Ʒ��ӿ�IFNETע��QOS���ͺ���
*        Input: ULONG ulIfIndex: �ӿ�����
*               IF_QosTransmitDone_HOOK_FUNC pfHookFunc: ע��ĺ���ָ��
*       Output: 
*       Return: VRP_IFNET_NOERR: ע��ɹ�/����: ע��ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-23    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IF_RegFuncQosTransmitDoneHook(ULONG ulIfIndex, IF_QosTransmitDone_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_IF_RegFuncQosTransmitHook
*  Description: ��Ʒ��ӿ�IFNETע��QOS���ͺ���(��ӵ������)
*        Input: ULONG ulIfIndex: 
*               IF_QosTransmit_HOOK_FUNC pfHookFunc: ע��ĺ���ָ��
*       Output: 
*       Return: VRP_IFNET_NOERR: ע��ɹ�/����: ע��ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-7-23    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_IF_RegFuncQosTransmitHook(ULONG ulIfIndex, IF_QosTransmit_HOOK_FUNC pfHookFunc);
extern ULONG TCPIP_CreateDelSubIf( ULONG ulOperType, CHAR* szFullName );
extern ULONG TCPIP_GetIfInfobyFullName(  TCPIP_IFNET_S* pstIfnetInfo, CHAR* szName );
extern ULONG TCPIP_VlinkIoCtl(VLINKSTATUS_S *pVLinkStatus, VOID *pCB);
extern ULONG TCPIP_Vlink6IoCtl(IFVLINKENTRY6_S *pVLinkStatus, VOID *pCB);

/*Add for BC3D00792,DR.131��ȡ��·��״̬ start*/

extern ULONG TCPIP_GetLinkStatus(ULONG ulIfIndex,IF_LINKSTATUS_S *pStatus);
/*Add for BC3D00792,DR.131��ȡ��·��״̬ end*/

extern ULONG TCPIP_GetPortInfoByIfNameEx(UCHAR *pucName, ULONG *pulPortType, 
                                        ULONG *pulFirstDim,ULONG *pulSecondDim,
                                        ULONG *pulThirdDim);
extern ULONG TCPIP_GetPortInfoByIfName(UCHAR *pucName,
                                       ULONG *pulPortType, 
                                       ULONG *pulPortNo);

extern ULONG TCPIP_IF_FindNextSubIfIndex( ULONG ulNextSubIfIndex, 
                                          ULONG* ulSubIfIndex);

extern ULONG TCPIP_GetMainIfIndex(ULONG ulIfIndex,ULONG *pulMainIfIndex);

extern ULONG TCPIP_GetPortInfoExSub(ULONG ulIfIndex, ULONG *pulPortType, 
                             ULONG *pulFirstDim,ULONG *pulSecondDim,
                             ULONG *pulThirdDim,ULONG *pulSubPortNum);
                             
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
/*******************************************************************************
*    Func Name: TCPIP_RegProdIfCheckHook
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ע���Ʒ�������ӿڵĹ��Ӻ���
*        Input: IF_PROD_CHECK_HOOK_FUNC pfHookFunc
*       Output: 
*       Return: VOS_OK
                VOS_ERR
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG TCPIP_RegProdIfCheckHook(IF_PROD_CHECK_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_GetVrfByIfIndex
* Date Created: 2009-02-02
*       Author: qinyun
*  Description: ��ȡVRF ID
*        Input: ULONG ulIfIndex:�ӿ�����
*               
*       Output: ULONG *pulVrfIndex:VRF ID
*       Return: �ɹ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-02   qinyun                  Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetVrfByIfIndex(ULONG ulIfIndex, ULONG *pulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*******************************************************************************
*    Func Name: TCPIP_GetVrf6ByIfIndex
* Date Created: 2013-09-26
*       Author: a00900872
*  Description: get the VRF6 index from the interface index
*        Input: ULONG ulIfIndex:interface index
*
*       Output: ULONG *pulVrfIndex:VRF6 ID
*       Return: VRF6 Id will get as output
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-09-26   a00900872        Create
*
*******************************************************************************/
ULONG  TCPIP_GetVrf6ByIfIndex(ULONG ulIfIndex, ULONG *pulVrf6Index);


extern ULONG TCPIP_GetIfInfobyIfIndex(  TCPIP_IFNET_S* pstIfnetInfo, ULONG ulIfIndex );


extern ULONG TCPIP_SetDevLink(DEVLINK_S *pstDevLink);


extern ULONG TCPIP_GetDevLink(ULONG ulIfIndex, DEVLINK_S *pstDevLink);


extern VOID TCPIP_ShowDevLink(CHAR *szIfName);


extern ULONG TCPIP_SetIfEventDebugSwitch(ULONG ulValue);


extern ULONG TCPIP_GetIfEventDebugSwitch(ULONG *pulValue);


extern VOID TCPIP_ShowInterfaceByName(CHAR *pszIfName);



extern ULONG TCPIP_IF_GetISIStatus(ULONG ulIfIndex, ULONG *pulIfState);


extern ULONG TCPIP_IF_GetIfNum(ULONG *pulIfNum);


extern ULONG TCPIP_IF_GetAllIfIndex(ULONG *pulIfNum, ULONG *pulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncLinkMsg6SendHook
* Date Created: 2009-12-07
*       Author: hanna55555
*  Description: ע��IPv6�ӿ�״̬�仯֪ͨ·�ɹ���ģ��Ĺ���
*        Input: LinkMsg6Send_HOOK_FUNC pfHookFunc:�ӿ�״̬�仯֪ͨ������
*       Output: 
*       Return: �ɹ�����FIB6_OK
*               ʧ�ܷ��ش�����
*      Caution: ֻ���ڹ����綨��RM��ʽ������ʹ��.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-07   hanna55555              Create for VISPV1R8C03
*
*******************************************************************************/
ULONG TCPIP_RegFuncLinkMsg6SendHook(LinkMsg6Send_HOOK_FUNC pfHookFunc);

/* ֪ͨ��Ʒ�����߼��ӿڵĹ��Ӻ���ԭ�� */
typedef ULONG (*TCPIP_CreateLogicIf_HookFunc)(ULONG ulIfIndex);
extern ULONG TCPIP_RegFuncCreateLogicIfHook(TCPIP_CreateLogicIf_HookFunc pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegRtVLinkIndexHook
* Date Created: 2010-09-07
*       Author: wangbin (62223)
*  Description: ע���ȡIPC·�ɵ�vlink Index
*        Input: IF_GET_VLINK_INDEX_HOOK_FUNC pfHookFunc:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-07   wangbin (62223)         Create
*
*******************************************************************************/
extern ULONG TCPIP_RegRtVLinkIndexHook(IF_GET_VLINK_INDEX_HOOK_FUNC pfHookFunc);


extern ULONG TCPIP_GetPortInfoSub(  ULONG ulIfIndex,
                                    ULONG *pulPortType,
                                    ULONG *pulMainPortNo, 
                                    ULONG *pulSubPortNo );

/*******************************************************************************
*    Func Name: TCPIP_GetIfIndexByPortSub
* Date Created: 2010-12-07
*       Author: wangbin (62223)
*  Description: ���ݽӿ����ͺͽӿڵ�һ����άֵ���ӽӿںŻ�ȡ��Ӧ�Ľӿ�����ֵ
*        Input:   
*               ULONG ulPortType:�ӿ�����
*               ULONG ulFirstDim:�ӿڵ�һάֵ
*               ULONG ulSecondDim:�ӿڵڶ�άֵ
*               ULONG ulThirdDim:�ӿڵ���άֵ
*               ULONG ulSubPortNum:�ӽӿں�
*       Output: ULONG *pulIfIndex:  �ӿ�����
*       Return: 
*      Caution: ��ulSubPortNumΪ0�򷵻����ӿڶ�Ӧ�����������򷵻��ӽӿڶ�Ӧ������ֵ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-12-07   wangbin (62223)         Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIfIndexByPortSub(ULONG *pulIfIndex, ULONG ulPortType, 
                          ULONG ulFirstDim,ULONG ulSecondDim,
                          ULONG ulThirdDim,ULONG ulSubPortNum);

/*******************************************************************************
*    Func Name: TCPIP_SetLineStatus
* Date Created: 2014-05-28
*       Author: likaikun213099
*  Description: ����ָ���˿ڵ�Э��״̬
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulStatus:  �˿�Э��״̬, 1 ΪUP, 2ΪDOWN
*       Output: 
*       Return: 
*      Caution: ����˵�����ڲ�Ʒ���ӿ�DOWN�ӿں�UP�ӿ�ǰ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-28   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetLineStatus(ULONG ulIfIndex, ULONG ulStatus);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_SetTunnelPara
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:����ӿ�����
*               TCPIP_TUNNEL_IF_PPI_S *pstTunnelInfo:���������Ϣ
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
extern ULONG TCPIP_Tunn_SetTunnelPara(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelInfo);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_GetIfInfoByIfIndex
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:  ����ӿ�����
*       Output: TCPIP_TUNNEL_IF_PPI_S *pstTunnInfo:���������Ϣ
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_GetIfInfoByIfIndex(ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnInfo);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_ShowIfByName
* Date Created: 2014-11-13
*       Author: wuling201943
*  Description: 
*        Input: CHAR *szIfName:tunnel�ӿ���
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-13   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_ShowIfByName(CHAR *szIfName);

/*******************************************************************************
*    Func Name: TCPIP_Tunn_DelTunnelPara
* Date Created: 2014-11-14
*       Author: wuling201943
*  Description: 
*        Input: ULONG ulIfIndex:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-14   wuling201943            Create
*
*******************************************************************************/
ULONG TCPIP_Tunn_DelTunnelPara(ULONG ulIfIndex);


/*******************************************************************************
*    Func Name: ADDR_AddIP6Address
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: cfg ipv6 addr on host mode
*        Input: CHAR *szIfName:interface name
*               CHAR *szIP6Addr:ipv6 addr
*               ULONG ulIP6PrefixLen:PrefixLen:128,host mode
*               ULONG ulFlag:0 -Global Address support only
*       Output: 
*       Return: 
*      Caution: host mode, ipv6 addr custom-tailor API for balong
*               support global-addr only,support config an ipv6 address only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_AddIP6Address(CHAR *szIfName, CHAR *szIP6Addr,ULONG ulIP6PrefixLen, ULONG ulFlag);


/*******************************************************************************
*    Func Name: ADDR_DelIP6Address
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: delete ipv6 addr on host mode
*        Input: CHAR *szIfName:interface name
*               CHAR *szIP6Addr:ipv6 addr
*               ULONG ulIP6PrefixLen:PrefixLen:128,host mode
*               ULONG ulFlag:0 -Global Address support only
*       Output: 
*       Return: 
*      Caution: host mode, ipv6 addr custom-tailor API for balong
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_DelIP6Address(CHAR *szIfName, CHAR *szIP6Addr,ULONG ulIP6PrefixLen, ULONG ulFlag);


/*******************************************************************************
*    Func Name: ADDR_Set_Mtu
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: set ipv6 if mtu
*        Input: ULONG ulIfIndex
*               ULONG ulMtu
*       Output: 
*       Return: 
*      Caution: host mode, set ipv6 if mtu
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_Set_Mtu(ULONG ulIfIndex, ULONG ulMtu);


/*******************************************************************************
*    Func Name: ADDR_IPv6EnableOnIntf_Host
* Date Created: 2015-03-02
*       Author: wangbin
*  Description: Enable/disable IPv6 on host mode
*        Input: CHAR *szIfName
*               ULONG ulFlag
*       Output: 
*       Return: 
*      Caution: host mode, enable ipv6
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2015-03-02   wangbin          Create
*
*******************************************************************************/
extern ULONG ADDR_IPv6EnableOnIntf_Host(CHAR *szIfName,ULONG ulFlag);


ULONG TCPIP_RegAddrHook(TCPIP_ADDR_HOOK_S *pstAddrHook);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _IFNET_API_H_ */

