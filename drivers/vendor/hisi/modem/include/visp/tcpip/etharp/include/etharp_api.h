

#ifndef _ETHARP_API_H_
#define _ETHARP_API_H_


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


/**********************************************************************
*                        �����ṩ�Ĵ�����
***********************************************************************/

enum tagETHARPRetCode
{
    MEM_MALLOCFAIL = VOS_ERR + 1,   /*2,�ڴ����ʧ��*/
    UNKNOWNED_FRAME,                /*3,����Ϊ��*/
    MEMPREPEND_FAIL,                /*4,����mbuf prependʧ��*/
    UNKNOWNED_PROTO,                /*5,δ֪Э���*/
    ARP_OVERMAX,                    /*6,ARP������*/
    INVALID_IFNET,                  /*7,IFNET������*/
    LINKISDOWN,                     /*8,��·״̬û��UP*/
    ARPRESOLVE_FAIL,                /*9,����ARPʧ��*/
    ARPHEADER_ERROR,                /*10,ARP�ײ���ʽ����*/
    ARPSRCMAC_BROADCAST,            /*11,ARPԴphysical��ַΪ�㲥��ַ*/
    ARPSRCMAC_ALLZERO,              /*12,ARPԴphysical��ַΪȫ���ַ*/
    ARPONESEFMAC,                   /*13,ARP����ԴMAC�뱾�ӿ�MAC��ͬ*/
    ARPONESEFIP,                    /*14,ARP����ԴIP�뱾�ӿ�IP��ͬ*/
    ARPDSTIP_NOTSAMENET,            /*15,ARP����Ŀ�ĵ�ַ�뱾�ӿڵ�ַ����ͬһ����*/
    ARPSRCIP_BROADCAST,             /*16,ARPԴ��ַIPΪ�㲥��ַ*/
    ARPINERT_FAIL,                  /*17,����ARP�ڵ�ʧ��*/
    NOTARPREQUEST,                  /*18,���Ĳ���ARP REQUEST*/
    NOTMAXIPADDR,                   /*19,�ӿڲ�������Ч��ƥ���ַ*/
    SENDING_REQUEST,                /*20,����ARP REQUEST����*/
    NOTENOUGHMEM,                   /*21,�ڴ治��*/
    GETMTSOFTFAIL,                  /*22,��ȡ��̫���ƿ�ʧ��*/
    IPXENCAP_CONFLICT,              /*23,*/
    SPLIMP_FAIL,                    /*24,���ж�ʧ��*/
    ARPNOTEXIST,                    /*25,ARP�ڵ㲻����*/
    ERR_LINKTYPE,                   /*26,��·���ʹ���*/
    ARPREQUEST_FAIL,                /*27,����ARP REQUESTʧ��*/

    ETHARP_GET_DATA_END,            /*28,�޺����ڵ�ɻ�ȡ*/
    ETHARP_INVALID_IPADDR,          /*29,��ַ���Ϸ�*/
    ETHARP_NULL_POINTER,            /*30,����ָ��Ϊ��*/
    ETHARP_ERROR_SWITCH,            /*31,ָ���Ŀ���ֵ����*/
    ETHARP_ERROR_PROXYTYPE,         /*32,ָ����ARP�������ʹ���*/
    ETHARP_INVALID_WLHANDLE,        /*33,ָ����WaitList�����Ч*/
    ETHARP_HA_IS_SMOOTHING ,        /*34,HA����ƽ��������ֶ���������*/
    ETHARP_PORT_IS_TRUNKPORT,       /*35,�ӿ���trunk�ĳ�Ա�˿ڣ����ɲ���*/
    ETHRRP_CMD_ERR,                 /*36,�����ֲ��Ϸ� */
    ETHARP_NOT_INIT,                /*37,��̫���ܱ��ü����޸ù���*/
    ETHARP_ERROR_SCOPE,             /*38 */
    ETHARP_OAM3AH_LB_LOCAL,         /*39,�ӿڴ���3AH������Ӧ̬�Ҳ���ģʽΪVISP���ģʽ     */
    ETHARP_WRONG_TYPE,              /*40,���ͳ��� */
    ETHARP_NOREG,                   /*41,ETHδע��*/
    ETHARP_VIRTUAL_IF,              /*42,��ӿڲ�֧�ִ˹��� */
    ETHARP_LOCAL_IPADDR,            /*43,Ŀ�ĵ�ַ�Ǳ���IP */
    ETHARP_SUBNET_BROADCAST,        /*44,Ŀ�ĵ�ַ�������㲥��ַ */
    ETHARP_ENABLE_VLAN_MODE,        /*45������VLANģ�������*/
    ETHARP_INVALID_VLAN_ID,         /*46 VLAN ID�Ƿ�*/
    ETHARP_ERR_MAIN_INTF,           /*47 �ӿڲ�Ӧ��Ϊ���ӿ�*/
    ETHARP_ERR_L2PORT_TYPE,         /*48 ����˿����Ͳ���ȷ*/

    ETHARP_ERROR_VLANARPPROXY,      /*49,��VLAN IF�ӿڲ���������VLAN IF����*/
    ETHARP_ERROR_L2IFNOTREG,        /*50 L2IFģ��δע��*/
    ETHARP_ERROR_L2IFCHECK,         /*51 VLAN ID�ͳ��˿ڵ���Ч��ģ���鲻ͨ��*/
    ETHARP_ERROR_VLANIFNOTEXIST,    /*52 �����ڸ�VLAN��Ӧ��VLANIF*/
    ETHARP_ERROR_NOTSAMENETWITHVLANIF, /*53 ��ַ��VLANIF����ͬһ������*/
    ETHARP_INVALID_IPADDR_IN_IF,    /*54 */
    ETHARP_ERROR_PARAWRONG,         /* 55 ����������Ϸ� */
    ETHARP_ERROR_VRRP_VMAC,         /* 56 MAC��VRRP��MAC */

    ETHARP_WAITLIST_CLOSE_FAIL,     /* 57 �ر�waitlistʧ�� */
    ETHARP_WAITLIST_OPEN_FAIL,      /* 58 ��waitlistʧ�� */
    ETHARP_WAITLIST_GET_FAIL,       /* 59 ��ȡwaitlistʧ�� */
    ETHARP_ERR_PROXY_IF,            /* 60 ���ô���Ľӿڲ���ȷ */
    ETHARP_ERR_VIRTUAL_IP,          /* 61 ��ַ��Backup·���������ַ */
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ETHARP_ERR_GET_VRFINDEX,        /* 62 ��ȡVRF Indexʧ�� */
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

    ETHARP_ERR_UNARP_DISABLE,       /*63 UNARP����δʹ��,����V1R8C01*/

    ETHARP_ERR_SUB_INTF,            /*64 �ӿڲ�Ӧ��Ϊ�ӽӿ�*/
    ETHARP_ERR_HOOK_TYPE,            /* 65 ע�ṳ�ӵ����Ͳ������� */
    ETHARP_ERR_HOOK_ALREADYREG,      /* 66 �����Ѿ�ע�� */
    ETHARP_ERR_HOOK_NOTREG,          /* 67 ����δ��ע�� */

    ARPREQUEST_FAIL_RE,             /*68,��η���ARP REQUESTʧ��*/
    ARPREQUEST_FAIL_RES,            /*69,��RESOLVING״̬����ARP REQUESTʧ��*/

    ETHARP_GUARD_PKT_INBLACKLIST,      /*70 ARP���Ľ���ں�������  */

    ETHARP_GUARD_NULL_POINTER,         /*71 ETHARP Guard��ָ�� */

    ETHARP_GUARD_SET_BLACKNUMM_ERR,    /*72 ETHARP Guard����һ��IP�º����������Ƿ�  */

    ETHARP_GUARD_GET_BLACKNUMM_FINISH, /*73 ETHARP Guard��ȡ�������ڵ���� */

    ETHARP_GUARD_OPEN_WAITLIST_ERR,    /*74 ETHARP Guard OPEN WaitListʧ�� */

    ETHARP_GUARD_SET_WAITLIST_ERR,     /*75 ETHARP Guard Set WaitListʧ�� */

    ETHARP_GUARD_CLOSE_WAITLIST_ERR,   /*76 ETHARP Guard Close WaitListʧ�� */

    ETHARP_GUARD_REG_WAITLIST_ERR,     /*77 ETHARP Guard Register WaitListʧ�� */

    ETHARP_GUARD_GET_WAITLIST_ERR,     /*78 ETHARP Guard Get WaitListʧ�� */

    ETHARP_GUARD_CLOSE_WAITLIST_PARA_ERR,/*79 ETHARP Guard Get WaitListʧ�� */

    ETHARP_GUARD_SET_SWITCH_ERR,       /*80 ����Guard����ֵ�Ƿ� */

    ETHARP_GUARD_GETMACNODEOK,         /*81 ��ȡMAC���ɹ� */

    ETHARP_GUARD_GETMACNODEFAIL,       /*82 ��ȡMAC���ʧ�� */

    ETHARP_GUARD_MALLOC_BLACKNODE,     /*83 ����BLACK NODE�ڵ�ʧ�� */

    ETHARP_GUARD_MALLOC_STATIC_BLACKNODE,     /*84 ����STATIC BLACK NODE�ڵ�ʧ�� */

    ETHARP_GUARD_DEL_NOTAT_STATIC_BLACKLIST,  /*85 ��MAC���ھ�̬�������б����� */

    ETHARP_GUARD_NULL_POINT,                  /*86 ��ָ�� */

    ETHARP_GUARD_NOT_ENABLE,                  /*87 ARP Guard����û�д� */

    ETHARP_GUARD_MAX_BLACKNUM_ONEIP,          /*88 ͬһ����ַ�µĺ������������ */

    ETHARP_GUARD_MAX_STATIC_ARPNODE,          /*89 ��̬ARP Guard��㳬����� */

    ETHARP_GUARD_VRF_ERR,                     /*90 VRFID������Χ */

    EHTARP_VLAN_DISABLE,                      /*91, VLAN����û�б�ʹ�� */

    EHTARP_INVALID_ID,                        /*92, ��Ч��VLIN ID */

    EHTARP_INVALID_VRF,                       /*93, ��Ч��VRF ��Ϣ */

    ETHARP_MACMULTICAST,                      /*94, MAC�ǶಥMAC */

    ETHARP_NOT_MAININTF,                      /*95, �ӿڲ������ӿ�,ֻ�����ӿڲ������� */

    ETHARP_GUARD_DYNAMIC_NODE_NOEXSIT,        /*96, ��̬ARP Gurad��㲻���� */

    ETHARP_NULL_POINTER_REG1XHOOK,            /*97, ע�ᴦ��802.1X����Ϊ�� */
    ETHARP_ERROR_NULL_IFNET_SNDEAP,           /*98, ����802.1X�Ȳ�Ʒ�Զ��屨�Ľӿڲ����� */
    ETHARP_ERROR_IFNOTUP_SNDEAP,              /*99, ����802.1X�Ȳ�Ʒ�Զ��屨�Ľӿ�״̬��ΪUP */
    ETHARP_ERROR_NULL_MBUF_SNDEAP,            /*100, ����802.1X�Ȳ�Ʒ�Զ��屨��MBUFָ��Ϊ�� */
    ETHARP_ERROR_NOTETH_SNDEAP,               /*101, ����802.1X�Ȳ�Ʒ�Զ��屨�Ľӿ����ͷ�Eth�� */
    ETHARP_ERROR_NO_FATHERIF,                 /* 102, �����ڸ��ӿ� */
    ETHARP_ERROR_REG_ISNATIP_NULL,            /* 103, ע���Ƿ���NAT IP�ص�����Ϊ�� */
    ETHARP_ERROR_VRF_NAMELONG=104,            /* 104, VRF���ֳ��ȴ���31 */
    ETHARP_GUARD_NOT_INIT,                     /* 105,ARP Guard δ��ʼ�� */
    ETHARP_INVALID_UNICAST_ARP_COUNT,          /* 106, ���õ���ARP�����Ƿ� */
    ETHARP_INVALID_QUELEN,                     /* 107, ARP���ı�����зǷ� */
    ETHARP_ERROR_FORMAT,                       /* 108, ��EthernetII��SNAP��ʽ */    
    ETHARP_GUARD_INVALID_PARA,                 /* 109, ��������Ƿ� */
    ETHARP_GUARD_HA_IS_SMOOTHING,              /* 110, arpguard����ƽ�� */ 
    ETHARP_MAX_SYSTEM_ARP,                    /* ���ôﵽϵͳ������ARP���� */
    ETHARP_IPCONFLICT_TBL_DISABLE,              /* 112, IP Conflict table capture is disabled */
    ETHARP_EOF_IPCONFLICT_TBL,                /* 113, End of IP Conflict table */
    ETHARP_INVALID_PRECFG,                    /* 114,������ֵ��ƥ�� */
    ETHARP_GUARD_DYNAMIC_EXCEED,              /* 115,��̬����������������� */
    ETHARP_ERROR_ALREADY_FRESHED,             /*116,��̬ARP�����Ѿ�����̬����*/
    ETHARP_ERROR_INVALID                       /* ���ֵ */
};


/**********************************************************************
*                        �����ṩ�ĺ궨��
***********************************************************************/
#define NORMAL_ARP_PROXY  0x01

/* ����ARP�����־�궨�� */
#define SPECIAL_ARP_PROXY   0x02
/* ����������ARP�����־�����ѱ�SPECIAL_ARP_PROXY���棬��ʱ���� */
#define OPTIC_ARP_PROXY   0x02


#define EXPIRETIME       1200    /*��̬ARP�ϻ�ʱ��20����*/
#define LARPTDOWN        20      /*�ӳٷ���ARP�����ʱ��(��)*/
#define NARPMAXTRIES     5       /*ÿһ������������ͬһĿ�ķ��͵�ARP������*/
#define MAXPACKETS       1000    /*ARP���еĳ���*/
#define MACADDRLEN       6       /*physical��ַ����*/
#define PROADDRLEN       4       /*Э���ַ����*/
#define MAXPKTSPERTIME   100     /*һ�δ����ARP���ĵ�������*/
#define ARP_EXPIRE_DETECT_TIMES 3/* ARP��ʱ̽�����ȱʡֵ add by xiaoshouhe 2003/10/16 */


/*��̫��֡��ʽ*/
#define PKTFMT_ETHNT_2   0         /*ETHNT_2*/
#define PKTFMT_EN_SNAP   1         /*SNAP*/
#define PKTFMT_8023_IPX  2         /*8023*/
#define PKTFMT_8022_IPX  3         /*8022*/
#define PKTFMT_ETHNT_UNKNOWN 4      /*��̫�ӿڲ�ʶ����*/
#define PKTFMT_EN_PPPOE  5         /*PPPOE֡����*/


#define ETHERTYPE_BPDU     0xFFFD  /* use for bridge */
#define ETHERTYPE_CDP      0xFFFE  /* use for bridge */
#define ETHERTYPE_OTHER    0xFFFF  /* use for bridge */


#define ETHERiiHDRLEN       14 /*sizeof(struct tagETHERHDR)*/
#define ETHERSNAPHDRLEN     22 /*sizeof(struct tagETSNAPHDR)*/
#define ETHER8023HDRLEN     14 /*sizeof(struct tagET8023HDR)*/
#define ETHER8022HDRLEN     17 /*sizeof(struct tagFMT802HDR)*/


/*Э������*/
#define ETHERTYPE_PUP       0x0200  /* PUP protocol */
#define ETHERTYPE_IP        0x0800  /* IP protocol */
#define ETHERTYPE_ARP       0x0806  /* Addr. resolution protocol */
#define ETHERTYPE_REVARP    0x8035  /* reverse Addr. resolution protocol */
#define ETHERTYPE_IPX       0x8137  /* Novell's IPX/SPX protocol */
#define ETHERTYPE_SLOW      0x8809  /* slow protocol */

#define ETHERTYPE_PPPOE_DISCOVERY 0x8863    /* PPPoEЭ�̽׶α���Э��� */
#define ETHERTYPE_PPPOE_SESSION 0x8864      /* PPPoE�Ự�׶α���Э��� */
#define ETHERTYPE_ISIS      0x8000  /*need tested with cisco*/

#define ETHERTYPE_8021X     0x888E    /* 802.1X����Э��� */

#define VLAN_DISABLE     0
#define VLAN_ENABLE      1
#define VLANTYPE_DOT1Q   0x8100  /* VLAN 802.1q��ʽ*/
#define DOT1Q_TAG_SIZE   4

/*��ַ������,��socket.h�ṩ����ʱ*/
#ifndef AF_UNSPEC
#define AF_UNSPEC   0
#endif

#ifndef AF_IPX
#define AF_IPX      23              /* Novell Internet Protocol */
#endif

#ifndef AF_INET
#define AF_INET     2               /* internetwork: UDP, TCP, etc. */
#endif

#ifndef AF_ARPREPLY
#define AF_ARPREPLY 19              /* ARPӦ����*/
#endif


#define AF_PPPOE    13              /* PPPOE */

#define AF_PPPOE_CLIENT 14          /* PPPoE Client����־*/

#define OSI_ISIS    7


#define ETHVLAN_VID_BROADCAST 4095
#define ETHVLAN_VLANID_MASK 0xfff


/*������ARPЭ���*/
#define ARP_PRELINKLEN   22        /*ARP��������·ͷ����*/
#define MAX_ARPNUMBER    512       /*��ʼ����̬ARP������*/
#define MAX_APRNUMBER_DYNAMIC 4096 /*��ʼ����̬ARP������Ŀ*/

#define ARP_TIMEOUT      1000      /*1000ms,Ϊ��ֹARP���⹥��,��������յ���ַ�뱾����ͻ��ARP����, ÿ��1�봦��һ�� */


#define ETHARP_GET_DSTMACADDR(pArp) ((pArp)->ucArpDstMacAddr)
#define ETHARP_GET_SRCMACADDR(pArp) ((pArp)->ucArpSrcMacAddr)
#define ETHARP_GET_DSTPROADDR(pArp) ((pArp)->ucArpDstProAddr)
#define ETHARP_GET_SRCPROADDR(pArp) ((pArp)->ucArpSrcProAddr)

/* D12226 ��ֹ�鲥��ַ����ARP�� */
#define IP_ETHER_MAC_MULTICAST(enaddr) ( (enaddr)[0] & 0x01 )

/*VLANIF ARP PROXY*/
#define INTER_SUB_VLAN_ARP_PROXY 0x03

/* ���º궨��ARP����״̬,��TCPIP_GetArpEntryʹ��,���ǵ�
ĳЩ��Ʒ�����Ѿ�ʹ������Щֵ,�˴�������ARP�·�PPI��������
ת��Ϊ��λ����ʽ*/
#define ETHARP_ARPF_STATIC    0  /*ARP��־:��̬*/
#define ETHARP_ARPF_RESOLVED  2  /*ARP������״̬,�Ѿ���������*/
#define ETHARP_ARPF_RESOLVING 3  /*ARP������״̬,���ڽ���*/

#define ETHARP_ARP_EXPIRE_INVALID 0XFFFFFFFF   /*ARP����ʱ�����Чֵ*/

#define ARP_GUARD_ENABLE    1
#define ARP_GUARD_DISNABLE  0

#define ETHARP_MAX_ARPQUE_LEN      128    /* ����ARP���Ķ��г������ֵ */
/**********************************************************************
*                        �����ṩ�����ݽṹ����
***********************************************************************/

#pragma    pack( 1 )

typedef struct  tagETSNAPHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ   */
    UCHAR                   ucHdrSrcMacAddr[6];     /*Դphysical��ַ     */
    USHORT                  usLen;                  /*��̫��������          */
    UCHAR                   ucDSAP;                 /* destination service access point*/
    UCHAR                   ucSSAP;                 /* source service access point */
    UCHAR                   ucCtrl;                 /* control domain */
    UCHAR                   ucORI[3];
    USHORT                  usType;
}ETHARP_ETSNAPHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct tagFMT802HDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ  */
    UCHAR                   ucHdrSrcMacAddr[6];     /*Դphysical��ַ    */
    USHORT                  usLen;                  /*��̫��������        */
    UCHAR                   ucDSAP;                 /* destination service access point*/
    UCHAR                   ucSSAP;                 /* source service access point */
    UCHAR                   ucCtrl;                 /* control domain */
}ETHARP_FMT802HDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma    pack( 1 )

typedef struct   tagET8023HDR
{
    UCHAR                   ucHdrDstMacAddr[6];  /*Ŀ��physical��ַ  */
    UCHAR                   ucHdrSrcMacAddr[6];  /*Դphysical��ַ    */
    USHORT                  usLen;               /*��̫�������� */
}ETHARP_ET8023HDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct    tagARPHDR
{
     USHORT     usHrdAddrFormat;          /* format of hardware address */
     #define    ARPHRD_ETHER     1          /* ethernet hardware format */
     #define    ARPHRD_IEEE      6          /* ieee snap hardware format */
     #define    ARPHRD_FRELAY    15          /* frame relay hardware format */
     USHORT     usProAddrFormat;          /* format of protocol address */
     UCHAR      ucHrdAddrLen;              /* length of hardware address */
     UCHAR      ucProAddrLen;              /* length of protocol address */
     USHORT     usOpType;                  /* one of operation type: */
     #define    ARPOP_REQUEST    1          /* request to resolve address */
     #define    ARPOP_REPLY      2          /* response to previous request */
     #define    ARPOP_REVREPLY   4          /* response giving protocol address */
     #define    ARPOP_INVREQUEST 8           /* request to identify peer */
     #define    ARPOP_INVREPLY   9          /* response identifying peer */
}ETHARP_ARPHDR_S;

typedef struct  tagETHERARP
{
     struct  tagARPHDR   ea_stHdr;        /* fixed-size header */
     UCHAR   ucArpSrcMacAddr[6];          /* sender hardware address */
     UCHAR   ucArpSrcProAddr[4];          /* sender protocol address */
     UCHAR   ucArpDstMacAddr[6];          /* target hardware address */
     UCHAR   ucArpDstProAddr[4];          /* target protocol address */
     #define  usHdrAddrFmt   ea_stHdr.usHrdAddrFormat
     #define  usProAddrFmt   ea_stHdr.usProAddrFormat
     #define  ucHdrAdrLen    ea_stHdr.ucHrdAddrLen
     #define  ucProAdrLen    ea_stHdr.ucProAddrLen
     #define  usOprType      ea_stHdr.usOpType
}ETHARP_ETHERARP_S;

/*Add for UNARP by 62011,62223 start*/
typedef struct  tagETHERUNARP
{
     struct  tagARPHDR   ea_stHdr;        /* fixed-size header */
     UCHAR   ucUnArpSrcProAddr[4];          /* sender protocol address */
     UCHAR   ucUnArpDstProAddr[4];          /* target protocol address */
     #define  usUnHdrAddrFmt   ea_stHdr.usHrdAddrFormat
     #define  usUnProAddrFmt   ea_stHdr.usProAddrFormat
     #define  ucUnHdrAdrLen    ea_stHdr.ucHrdAddrLen
     #define  ucUnProAdrLen    ea_stHdr.ucProAddrLen
     #define  usUnOprType      ea_stHdr.usOpType
}ETHARP_ETHERUNARP_S;
/*Add for UNARP by 62011,62223 end*/


#pragma    pack( 1 )
typedef struct  tagETHERHDR
{
    UCHAR                   ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ*/
    UCHAR                   ucHdrSrcMacAddr[6];     /*Դphysical��ַ  */
    USHORT                  usHdrType;              /*Э������   */
}ETHARP_ETHERHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagTCPIP_ETHARP_ARPRTENTRY
{
    ULONG ulRtIpAddr;             /*���������ַ*/
    UCHAR ucMacAddr[6];           /*��������physical��ַ*/
    UCHAR ucPadding_1[2];
    ULONG ulFlags;                /*��ARP�ı�־�ֶ� */
    ULONG ulRtIfIndex;            /*��������IFNET�ӿ�INDEX*/
    ULONG ulRtExpire;             /*����ʵ��ARP����ĳ�ʱ���� */
    ULONG ulVlinkIndex;           /*NP�·��󷵻ص�VLINK������*/
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG ulVrfIndex;             /* VRF���� */
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG ulOutPortIfIndex;       /*ARP���˿�����*/
}TCPIP_ETHARP_ARPRTENTRY_S;


typedef struct tagETHSTAT_S
{
    ULONG    ulRcvBytes;          /* ���յ��ֽ��� */
    ULONG    ulSndBytes;          /* ���͵��ֽ��� */
    ULONG    ulRcvPkts;           /* ���յı����� */
    ULONG    ulSndPkts;           /* ���͵ı����� */
    ULONG    ulRcvARPRqstPkts;    /* ���յ�ARP�������� */
    ULONG    ulRcvARPRplyPkts;    /* ���յ�ARPӦ������ */
    ULONG    ulSndARPRqstPkts;    /* ���͵�ARP�������� */
    ULONG    ulSndARPRplyPkts;    /* ���͵�ARPӦ������ */
    ULONG    ulSndDropPkts;       /* ����ʱ�����ı����� */
    ULONG    ulRcvDropPkts;       /* ����ʱ�����ı����� */
    /*Add for BC3D00792,DR.134��̫��ͳ����Ϣ�����ӣ�FREE ARP��ͳ��*/
    ULONG    ulSndFreeArp;        /* ���͵����ARP������ */
    /*Add for BC3D00792,DR.133��̫ģ�����ṩ����ARP ���ĵĽӿ�*/
    ULONG    ulUserSndArpRas;     /* �û�API���͵�ARP�������� */
    ULONG    ulUserSndArpRpl;     /* �û�API���͵�ARP��Ӧ������ */
    /*Add for UNARP by 62011,62223 start*/
    ULONG    ulSndUnArpPkts;      /* ���͵�UNARP������ */
    ULONG    ulRcvUnArpPkts;      /* ���յ�UNARP������ */
    /*Add for UNARP by 62011,62223 end*/
    ULONG    ulArpMissUpCount;    /* ARP Miss�ϱ�����ͳ�� */
    ULONG    ulArpMissNpCount;    /* ARP Miss�·�Np����ͳ��*/
    /*Added by wangtong207740, ETH����ͳ����ǿ, 2012/9/3 */
    ULONG    ulRcvBcastPkts;       /*�յ��Ĺ㲥���ĸ���*/
    ULONG    ulSndBcastPkts;       /*���͵Ĺ㲥���ĸ���*/
    ULONG    ulRcvMcastPkts;       /*�յ��Ķಥ���ĸ���*/
    ULONG    ulSndMcastPkts;       /*���͵Ķಥ���ĸ���*/
    ULONG    ulSndPhyFailtPkts;   /*��������ʧ�ܵı��ĸ���ͳ�ơ�*/
    /* End of Added by wangtong207740, 2012/9/3 */
}ETHSTAT_S;

typedef struct tagETHSTAT_LIST_S
{
    ULONG     ulIfIndex;
    ETHSTAT_S stEthStat;
}ETHSTAT_LIST_S;

/* �û����͵�ARP������ͳ����Ϣ */
typedef struct tagUSERARPSTAT_S
{
    ULONG    ulSendUserArpPkts;    /* �û�ָ������ARP����ɹ����� */
    ULONG    ulSendUserArpFails;   /* �û�ָ������ARP����ʧ�ܴ��� */
}USERARPSTAT_S;

typedef struct tagSPECIAL_ARPPROXY_PARA
{
    ULONG ulSrcIpAddr;
    ULONG ulDestIpAddr;
    ULONG ulSubnetMask;
    ULONG ulInIfIndex;
    ULONG ulOutIfIndex;
    ULONG ulOutIfLinePro;
    ULONG ulDestIpRtMaskLen;
}SPECIAL_ARPPROXY_PARA_S;

typedef struct tagARPINFO_S
{
    ULONG ulIfIndex;     /* �ӿ����� */
    ULONG ulIpAddr;      /* ��ַ�������ֽ��� */
    UCHAR ucMacAddr[6];  /* physical��ַ */
    USHORT ulFlags;      /* 0 ��̬ 1 ��̬ */
    ULONG ulVlinkIndex;  /* VLINK���� */
    ULONG ulVlanId;      /* VLAN ID */
    ULONG ulPortIfIndex; /* ���ӿ����� */

    /*arp Mccp support V300R001C00 --  start*/    
    
    ULONG ulRemainExpireTime;         /*Remaining Expiry Time*/
    ULONG ulLastRefTime;              /*absolute Time at which the entry was last ref.*/

    /*arp Mccp support V300R001C00 --  End*/        

} ARPINFO_S;

typedef struct tagARPINPUT_S
{
    ULONG ulIpAddr;      /* ��ַ�������ֽ��� */
    ULONG ulVrfIndex;    /* vrf index */
} ARPINPUT_S;

typedef struct tagARPWITHVLANINFO_S
{
    ULONG  ulIfIndex;     /* �ӿ����� */
    ULONG  ulIpAddr;      /* ��ַ */
    UCHAR  ucMacAddr[6];  /* physical��ַ */
    USHORT usVlanId;      /* VLAN ID */
} ARPWITHVLANINFO_S;

typedef struct tagEtharpGetRcvIfInfo_S
{
    ULONG ulMainIfIndex;         /*���ӿ�����*/
    ULONG ulSubIfIndex;          /*��ӦVLAN�ӽӿ�����*/
    ULONG ulRcvIfIndex;          /*���ص���ӿ�����*/
}ETHARP_GET_RCVIF_S;

#define ETHARP_NOT_PROCESSED_BY_VLAN              0
#define ETHARP_PROCESSED_ERR_BY_VLAN              1
#define ETHARP_PROCESSED_BY_VLAN              2

/**********************************************************************
*                        �����ṩ�����Ͷ���
***********************************************************************/

typedef ULONG (*ETHARP_INTERMEDIATE_HOOK_FUNC)(struct tagMBuf *pstMBuf);
typedef VOID (*DealIpConflict_HOOK_FUNC )(ULONG ulIfIndex, ULONG ulIpAddr, UCHAR * pucMac);
typedef ULONG ( * gpfTCPIPSpecialArpProxy) (SPECIAL_ARPPROXY_PARA_S *pstSpecArpPrxyPara);
typedef ULONG ( *gpfTCPIPGetVlanHead)(MBUF_S* pstMbuf,ULONG* pulVlanHead);
typedef ULONG(*gpfTCPIPSpecialArpProxyIP)(ULONG ulIfIndex, ULONG IPAddr);

/* �Ƿ���NAT ��ַ�ص��������ݽṹ����,��ַΪ������ */
typedef ULONG(*ETHARP_IS_NAT_IPADDR_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulIPAddr);

typedef ULONG (*ETHARP_GETARPRCVIFINDEX_HOOK_FUNC)(ETHARP_GET_RCVIF_S *pstRcvIfInfo);


#define ETHARP_NOT_PROCESSED_BY_INTERMEDIATE              0
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define ETHARP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet PP do not need to process the packet any more */
#define ETHARP_PROCESSED_BY_INTERMEDIATE                  2

#define ARP_FILTER_IFINDEX      0x00000001
#define ARP_FILTER_VALID        0x00000010
#define ARP_FILTER_IPADDR       0x00000100
#define ARP_FILTER_MAC          0x00001000
#define ARP_FILTER_ARPSTATIC    0x00010000
#define ARP_FILTER_ARPDYNAMIC   0x00100000
#define ARP_FILTER_VRF          0X01000000

#define MAX_ETHARP_EXPIRE_TIME 86400
#define MIN_ETHARP_EXPIRE_TIME 60

#define MAX_ETHARP_EXPIRE_TIME_SGSN 62640
#define MIN_ETHARP_EXPIRE_TIME_SGSN 20


/* Expire Time Mode Macros for different products*/
#define EXPIRE_TIME_MODE_SGSN 0    /* allows changing expire time for main interface and change will reflet inexisting entries*/
#define EXPIRE_TIME_MODE_HERT 1    /*allows changing expire time for main interface and sub interface and change will reflet in existing entries*/
#define EXPIRE_TIME_MODE_MCCP 2   /*allows changing expire time for main interface and sub interface and change will not reflet in existing entries*/

#define MAX_ETHARP_DETECT_TIMES 12
#define MIN_ETHARP_DETECT_TIMES 1

#define ETHARP_STATIC_ARP_TYPE 1
#define ETHARP_DYNAMIC_ARP_TYPE 2

#define ETHARP_ARP_INVALID 0
#define ETHARP_ARP_VALID 1

#define ETHARP_FREEARP_MINTIMES      3
#define ETHARP_FREEARP_DEFAULTTIMES  5
#define ETHARP_FREEARP_MAXTIMES      10

#define ETHARP_FREEARP_MINTOTALNUM      32
#define ETHARP_FREEARP_DEFAULTTOTALNUM  64
#define ETHARP_FREEARP_MAXTOTALNUM      256

#define ETHARP_FAKEUPDATE 2   /*pre-config value for g_ulArpUpdToPPISwitch for Fake node uupdate to PPI feature*/

#define ETHARP_MIN_EXPIREOFFSET 30
#define ETHARP_MAX_EXPIREOFFSET 60

typedef struct tagARPInfo
{
    ULONG     ulValid;
    ULONG     ulIfIndex;
    ULONG     ulIpAddr;
    UCHAR     ucMac[6];
    USHORT    usVID;
    ULONG     ulArpType;
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    ULONG     ulArpExpireTime;/*ARP�����ϻ�ʱ�䣬���Ϊ��̬��㣬��ֵΪ0xFFFFFFFF*/
    ULONG     ulLeftExpireTime;/*ARP����ϻ�ʣ��ʱ��,���ھ�̬ARP��㣬��ֵΪ0 */
    UCHAR     ucDArpFlag;  /* ��̬ARP��Ч, 1��ʾ���û����, 0��ʾЭ��ջ�Զ����� */
    UCHAR     ucpad[3];
} ARP_INFO_S;

typedef struct tagARPFilter
{
    ULONG ulFilterMode;
    ULONG  ulIfIndex;
    ULONG  ulValid;
    ULONG  ulIpAddr;
    UCHAR  ucMac[6];
    USHORT usRsv;
    /* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
}ARP_FILTER_S;

/* Begin : c00902193, 2013-11-22, Added to support IPConflict-get */
#define ETHARP_MAX_MAC_INFO  4

typedef struct tagMacInfo
{
    UCHAR  ucMac[6];     /* physical address */
    UCHAR  ucFlag;       /*ETHARP_STATE_CONFLICT, ETHARP_STATE_WAITFORREPLY */
    UCHAR  ucTimeCount;  /* Timer units */
}ETHARP_MAC_INFO_S;  

typedef struct tagIpConflictInfo
{
    ULONG ulIPConflictType; /* Conflicting address type: ETHIP (1); OMIP (2) */
    ULONG ulIfIndex;        /* Conflict IfIndex */
    ULONG ulIpAddr;         /* Conflicting address */
    ULONG ulMacNum;         /* address conflicts with an address corresponding to the number of conflicts Mac */
    ETHARP_MAC_INFO_S stMacInfo[ETHARP_MAX_MAC_INFO] ;
    ULONG ulVrfIndex;       /* Attached VrfIndex */
} ETHARP_IP_CONFLICT_INFO_S;

/* IPConflictType definitions */
#define ETHARP_STATE_CONFLICT               1  
#define ETHARP_STATE_WAITFORREPLY           2  
/* End : c00902193, 2013-11-22, Added to support IPConflict-get */

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */
#ifndef MACADDRLEN
#define MACADDRLEN 6             /* physical��ַ���� */
#endif

typedef struct tagARP_CFG_S
{
    ULONG ulIpAddr ;
    UCHAR ucMacAddr[MACADDRLEN];
    USHORT usVID;
    CHAR  szVrfName[TCPIP_MAX_VRFNAME_LENGTH + 1];
}ARP_CFG_S;
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

/*Add for UNARP by 62011,62223 start*/
/*����UNARP��νṹ*/
typedef struct tagETHARP_UNARPINFO_S
{
    ULONG ulIfIndex;        /*���ӿ�*/
    ULONG ulIpAddr;         /*Դ��ַ(������)*/
}ETHARP_UNARPINFO_S;
/*Add for UNARP by 62011,62223 end*/

typedef ULONG (*ETHARP_INPUT_HOOK_FUNC)( MBUF_S* pMbuf );
typedef ULONG (*ETHARP_OUTPUT_HOOK_FUNC)( MBUF_S* pMbuf );

extern ETHARP_INPUT_HOOK_FUNC g_EthARP_Input_HookFunc;
extern ETHARP_OUTPUT_HOOK_FUNC g_EthARP_Output_HookFunc;

/* ����ARP����֪ͨ����ص�������VLAN�ײ�Ϊ������ARP��������Ϊ������ */
typedef VOID (*ETHARP_ARPINPUT_NOTIFY_HOOK)(ULONG ulIfIndex,ULONG ulVlanHead, ETHARP_ETHERARP_S *pstArp);

/* EAPģ�����802.1X���Ĺ��Ӻ���ԭ��,�����ɹ��Ӻ��������ͷ� */
typedef ULONG (*EAPOL_RECV_PKT_HOOK)(ULONG ulIfIndex, struct tagMBuf *pstMBuf, ULONG ulPktLen);

/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
/* ��̫��װVLAN�ײ�ǰ����ص����� */
typedef ULONG (*ETH_BEFORE_ADD_VLANTAG_HOOK)(ULONG ulIfIndex, MBUF_S* pstMBuf);
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */

/**********************************************************************
*                        �����ṩ���û�API����
***********************************************************************/

extern ULONG TCPIP_RegFuncARPInputFunc( ETHARP_INPUT_HOOK_FUNC pfHookFunc );
extern ULONG TCPIP_RegFuncEthArpOutputHook( ETHARP_OUTPUT_HOOK_FUNC pfHookFunc );
extern ULONG TCPIP_CloseARPInfoTable( UINTPTR ulARPInfoHandle );
extern ULONG TCPIP_GetNextARPInfo( UINTPTR ulARPInfoHandle, ARP_INFO_S* pstARPInfo );
extern ULONG TCPIP_OpenARPInfoTable(UINTPTR* pulARPInfoHandle, ARP_FILTER_S* pstARPFilter);
extern ULONG TCPIP_SetARPExpireTime( ULONG ulTime, CHAR* szIfName );
extern ULONG TCPIP_SetARPDetectTimes( ULONG ulDetectTimes, CHAR* szIfName );
extern ULONG TCPIP_SetARPDetectTimesByIndex( ULONG ulDetectTimes, ULONG ulIfIndex );
extern ULONG TCPIP_GetARPDetectTimes( ULONG* pulDetectTimes, CHAR* szIfName );
extern ULONG TCPIP_GetARPExpireTime( ULONG* pulTime, CHAR* szIfName );
extern ULONG TCPIP_ShowARPDetectTimes( CHAR* szIfName );
extern ULONG TCPIP_ShowARPExpireTime( CHAR* szIfName );

extern ULONG  TCPIP_AddStaticArpWithVlan(ULONG ulIpAddr, UCHAR *pucMacAddr,USHORT usVID);
/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

extern ULONG  TCPIP_AddStaticArpByVrf(ARP_CFG_S *pstARPIn);

/*******************************************************************************
*    Func Name: TCPIP_DelArpEntryByVrf
* Date Created: 2009-02-06
*       Author: wangchengyang
*  Description: ɾ��ĳ��ָ��VRF��ARP����
*        Input: ULONG ulIpAddr:��ַ
*               ULONG ulScope:��Χ
*       Output: ��
*       Return: �ɹ��������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-06   wangchengyang           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG  TCPIP_DelArpEntryByVrf(ULONG ulIpAddr,ULONG ulScope,CHAR *pszVrfName);

/* End:VISP1.7C03 VRF wangchengyang , 2009-02-06 */

extern ULONG  TCPIP_AddStaticArp( ULONG ulIpAddr, UCHAR *pucMacAddr );

extern ULONG  TCPIP_ClearAllARPEntry(VOID);

extern ULONG  TCPIP_ClearAllDynARPEntry(VOID);

extern ULONG  TCPIP_ClearDynARPEntryByIntf( ULONG ulIfIndex );

extern ULONG  TCPIP_ClearStaticARPEntry(VOID);

extern ULONG  TCPIP_CloseArpTable( UINTPTR ulWaitlist );

extern ULONG  TCPIP_ClrEthStat( ULONG ulIfIndex );

extern ULONG  TCPIP_DelArpEntry( ULONG ulIpAddr,ULONG ulScope );

ULONG TCPIP_EthArpmiss_SGSN(ULONG ulIfIndex, ULONG ulDstIpAddr);

extern ULONG   TCPIP_EthArpmiss( ULONG ulIfIndex, ULONG ulDstIpAddr );

extern ULONG  TCPIP_GetArpEntry( UINTPTR ulWaitlist, TCPIP_ETHARP_ARPRTENTRY_S *pstArpEntry );

extern ULONG  TCPIP_GetArpEntryByIPAddr( ULONG ulIPAddr, ARPINFO_S *pstARPInfo );

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
/*******************************************************************************
*    Func Name: TCPIP_GetArpEntryByVrfIPAddr
* Date Created: 2009-02-09
*       Author: wangchengyang
*  Description: ���ݵ�ַ��ѯARP����
*        Input: ULONG ulIPAddr: Ҫ��ѯ��ARP����ĵ�ַ��������
*               ARPINFO_S *pstARPInfo: ��Ʒ���ĵ�ARP��Ϣ��ָ����ڴ����û�����������ͷ�
*       Output: ARPINFO_S *pstARPInfo: ��Ʒ���ĵ�ARP��Ϣ��ָ����ڴ����û�����������ͷ�
*       Return: �ɹ��������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09   wangchengyang           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG  TCPIP_GetArpEntryByVrfIPAddr(ULONG ulIPAddr, ARPINFO_S *pstARPInfo,ULONG ulVrfIndex);
/* End:VISP1.7C03 VRF wangchengyang , 2009-02-09 */

/*******************************************************************************
*    Func Name: TCPIP_GetArpInfoByInput
* Date Created: 2013-08-20
*       Author: MaFeng59090
*  Description: Ϊ֧���û�ָ����Ϣ��ѯARP������Ϣ����API�ӿ�
*        Input: ARPINPUT_S *pstInputInfo: �û�ָ���Ĳ�ѯ����
*               ARPINFO_S *pstARPInfo: ��ѯ����ARP������Ϣ
*       Output: ARPINFO_S *pstARPInfo: ��ѯ����ARP������Ϣ
*       Return: 0 �ɹ�/��0 ������
*      Caution: DOPRA IP V300R001C10�汾��֧��ָ��vrf����ַ������ѯ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-08-20   MaFeng59090             Create
*
*******************************************************************************/
ULONG TCPIP_GetArpInfoByInput(ARPINPUT_S *pstInputInfo, ARPINFO_S *pstARPInfo);


extern ULONG  TCPIP_GetArpNum( ULONG ulType );

extern ULONG  TCPIP_GetArpProxy( ULONG ulIfIndex, ULONG * pulFlag );

extern ULONG  TCPIP_GetEthArpDebugSwitch( ULONG* pulDebugArp, ULONG* pulDebugEthernet, ULONG* pulAclGroupNum );

extern ULONG  TCPIP_GetEthHADbg( ULONG *pulDbg );

extern ULONG  TCPIP_GetEthStat( ULONG ulIfIndex, ETHSTAT_S * pstEthStat );

extern ULONG  TCPIP_GetPPIArpByIp(ULONG ulIfIndex, ULONG ulIpAddr, PPI_ARP_S*pstPpiArp );

extern ULONG  TCPIP_OpenArpTable( UINTPTR *pulWaitlist );

extern ULONG  TCPIP_RegFuncDealIpConflictHook( DealIpConflict_HOOK_FUNC pfHookFunc );

extern ULONG  TCPIP_RegFuncEthArpHook( ULONG  ulType, ETHARP_INTERMEDIATE_HOOK_FUNC pfFun );

extern ULONG  TCPIP_RegFuncGetVlanHeadHook( gpfTCPIPGetVlanHead pfHookFuc );

extern ULONG  TCPIP_RegFuncSpecialArpProxyHook( gpfTCPIPSpecialArpProxy pfHookFuc );

extern ULONG  TCPIP_SendGratuitousArp (ULONG ulIfIndex, ULONG ulIpAddr);

extern ULONG  TCPIP_SetArpProxy( ULONG ulIfIndex, ULONG ulFlag, ULONG ulSetYes );

extern ULONG  TCPIP_SetEthArpDebugSwitch( ULONG ulDebugArp, ULONG ulDebugEthernet, ULONG ulAclGroupNum );

extern ULONG  TCPIP_SetEthHADbg( ULONG ulDbg );

extern ULONG  TCPIP_SetVlan( ULONG ulIfIndex , ULONG ulSetYes );
/*******************************************************************************
*    Func Name: TCPIP_GetVlan
*  Description: ��ȡ�ӿ�VLANʹ��״̬
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: ULONG *pulVlanFlag:ʹ��״̬
*       Return: VOS_OK �ɹ�
*               ������ ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-09-04   mafeng(59090)           Create
*
*******************************************************************************/
extern ULONG  TCPIP_GetVlan(ULONG ulIfIndex, ULONG * pulVlanFlag);

extern VOID   TCPIP_RegFuncGetOmIpHook(gpfTCPIPSpecialArpProxyIP pfHookFunc);

extern ULONG  TCPIP_GetEtharpMac(ULONG ulIfIndex, UCHAR *pucMac);

extern VOID   TCPIP_ShowEtharpStatistic(CHAR *pName);
/*******************************************************************************
*    Func Name: TCPIP_ShowIPConflictTable
*  Description: ��ʾIP��ͻTable
*        Input: VOID
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-04   fuxiaodong(54882)       Create
*
*******************************************************************************/
extern VOID   TCPIP_ShowIPConflictTable(VOID);

/*******************************************************************************
*    Func Name: TCPIP_OpenARPIPConflictInfoTable
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to open the IPConflicttable with waitlist.
*        Input: None
*       Output: ULONG *pulConflictInfoHandle: Handle to access the table.
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_OpenARPIPConflictInfoTable(UINTPTR *pulConflictInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_GetARPIPConflictInfo
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to get the IPConflicttable entry.
*        Input: 
*               ULONG ulConflictInfoHandle: Handle to access the table.
*               
*       Output: 
*               ETHARP_IP_CONFLICT_INFO_S *pstIPConflictInfo: IPConflict table entry
*
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetARPIPConflictInfo(UINTPTR ulConflictInfoHandle, ETHARP_IP_CONFLICT_INFO_S *pstIPConflictInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseARPIPConflictInfoTable
* Date Created: 2013-11-18
*       Author: Chandra (00902193)
*  Description: Function to close the IPConflicttable with waitlist.
*        Input: ULONG ulConflictInfoHandle: Handle to close the table.
*       Output: 
*       Return: VOS_OK / Error
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-11-18  Chandra (00902193)       Create
*
*******************************************************************************/
extern ULONG TCPIP_CloseARPIPConflictInfoTable(UINTPTR  ulConflictInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_AddStaticArpWithVlanAndPortIfIndex
* Date Created: 2008-11-14
*       Author: wuhailan
*  Description:
*        Input: ULONG ulIpAddr:��ַ(������)
*               UCHAR *pucMacAddr:physical��ַ
*               USHORT usVID:VLAN ID (1~4094)
*               ULONG ulPortIfIndex:����˿ڽӿ�����
*       Output:
*       Return: �ɹ��������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-14   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_AddStaticArpWithVlanAndPortIfIndex(ULONG ulIpAddr, UCHAR *pucMacAddr,USHORT usVID, ULONG ulPortIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ShowARPByVrf
* Date Created: 2009-02-28
*       Author: wangchengyang
*  Description: ��ʾָ��VRF��ARP����
*        Input: CHAR *pszVrfName VRF����
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09  wangchengyang    Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPByVrf(CHAR *pszVrfName);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPByFilter
* Date Created: 2009-02-28
*       Author: wangchengyang
*  Description: ��ʾָ��VRF��ARP����
*        Input: CHAR *pszVrfName VRF����
*               ULONG ulFilterMode
*               ULONG ulIfIndex
*               ULONG vlValid
*               ULONG ulIpAddr
*               UCHAR *ucMac
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-02-09  wangchengyang    Create the first version.
*
*******************************************************************************/
extern VOID TCPIP_ShowARPByFilter(CHAR *pszVrfName,ULONG ulFilterMode, ULONG ulIfIndex, ULONG ulValid, ULONG ulIpAddr, UCHAR* ucMac);


extern ULONG TCPIP_SendUserArp(ULONG ulIfIndex, ULONG ulDstIP, ULONG ulIsUnicast);


extern ULONG TCPIP_GetUserArpStat(ULONG ulIfIndex, USERARPSTAT_S* pstStat);


extern ULONG TCPIP_ClearUserArpStat(ULONG ulIfIndex);


extern VOID TCPIP_ShowUserArpStat(CHAR* pszIfName);


extern ULONG TCPIP_SendArpPkt(ULONG ulIfIndex, ULONG ulSrcIpAddr,ULONG ulDstIpAddr,
                              UCHAR* pucDstMac,USHORT usVid,BOOL_T bIsReply);


extern ULONG TCPIP_SetFreeArpSendTimes(ULONG ulTimes);



extern ULONG TCPIP_SetFreeArpSendTotalNum(ULONG ulNum);


ULONG TCPIP_GetFreeArpSendTimesAndTotalNum(ULONG *pulTimes,ULONG *pulTotalNum);


extern VOID TCPIP_ETHARP_SendGratuitousArp(MBUF_S *pMBuf, UCHAR* szSrcMacAddr,
                                        UCHAR* szProAddr,USHORT usOpType,
                                        ULONG ulIfIndex);


extern ULONG TCPIP_ETHARP_EtherOutput( MBUF_S *pMbuf );


extern ULONG TCPIP_RegFuncArpInputNotifyHook(ETHARP_ARPINPUT_NOTIFY_HOOK pfHook);


extern ULONG TCPIP_SetArpLogSwitch(ULONG ulIfIndex, ULONG ulLogSwitch);


extern ULONG TCPIP_GetArpLogSwitch(ULONG ulIfIndex, ULONG* pulLogSwitch);


extern ULONG TCPIP_GetEthHeadLen(MBUF_S* pMBuf,ULONG ulIfIndex,ULONG *pulEthHeadLen);

/*Add for UNARP by 62011,62223 start*/
/*******************************************************************************
*    Func Name: TCPIP_SetUnarpCapability
* Date Created: 2009-05-19
*       Author: qinyun62011
*  Description: ʹ��/ȥʹ��UNARP����
*        Input: ULONG ulFlag:��־(1-ʹ�ܣ�0-ȥʹ��)
*       Output:
*       Return: �ɹ�����VOS_OK
*               ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-19   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_SetUnarpCapability(ULONG ulFlag);

/*******************************************************************************
*    Func Name: TCPIP_GetUnarpCapability
* Date Created: 2009-05-20
*       Author: qinyun62011
*  Description: ��ȡʹ��ȥʹ�ܱ�־
*        Input:
*       Output: ULONG *pulFlag:ʹ��ȥʹ�ܱ�־
*       Return: �ɹ�����VOS_OK
*               ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-20   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_GetUnarpCapability(ULONG *pulFlag);

/*******************************************************************************
*    Func Name: TCPIP_ShowUnarpCapability
* Date Created: 2009-05-20
*       Author: qinyun62011
*  Description: ��ʾʹ��ȥʹ�ܱ�־
*        Input: VOID
*       Output:
*       Return: �ɹ�����VOS_OK
*               ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-20   qinyun62011             Create
*
*******************************************************************************/
extern VOID TCPIP_ShowUnarpCapability(VOID);

/*******************************************************************************
*    Func Name: TCPIP_SendUnArp
* Date Created: 2009-05-19
*       Author: qinyun62011
*  Description: ����UNARP����
*        Input: ETHARP_UNARPINFO_S *pstUnarpInfo:��νṹ
*       Output:
*       Return: �ɹ�����VOS_OK
*               ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-05-19   qinyun62011             Create
*
*******************************************************************************/
extern ULONG TCPIP_SendUnArp(ETHARP_UNARPINFO_S *pstUnarpInfo);
/*Add for UNARP by 62011,62223 end*/

/****************************************************************************
*    Func Name: TCPIP_SetIPZeroArpSwitch
* Date Created: 2008-08-26
*       Author: wuhailan
*  Description: �����Ƿ����ַΪ0��ARP�����Ŀ���
*        Input: ULONG ulSwitch:����,0 �ر�, 1 ��, Ĭ�Ϲر�
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-08-26   wuhailan         Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIPZeroArpSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIPZeroArpSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: ��ȡ�Ƿ����ַΪ0��ARP�����Ŀ���
*        Input:
*       Output: ULONG *pulSwitch:���صĿ���ֵ
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIPZeroArpSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_SetArpStrictLearnSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: ֧���ϸ�ѧϰARP����ܿ������ýӿ�
*               ʹ�����ϸ�ARP����ѧϰ��,��ѧϰ�Լ����͵�ARP�����ĵ�Ӧ����,
*               ��������һ�ɲ��ٽ���ARP����ѧϰ.���Ҳ���ARP�ظ�����������,��ֱ�Ӷ��������Է�����
*        Input: ULONG ulSwitch:����,0 �ر�, 1 ��, Ĭ�Ϲر�
*       Output: 
*       Return: VOS_OK:�ɹ� ��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetArpStrictLearnSwitch(ULONG ulSwitch);


/*******************************************************************************
*    Func Name: TCPIP_GetArpStrictLearnSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: ��ȡ�ϸ�ѧϰARP����ܿ������ýӿ�
*        Input:
*       Output: ULONG *pulSwitch:���صĿ���ֵ
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetArpStrictLearnSwitch(ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_AddDynamicArp
* Date Created: 2008-10-28
*       Author: zhangchunyu(62474)
*  Description: ��Ӷ�̬ARP
*        Input: ULONG ulIfIndex: �ӿ�����
*               UCHAR *pucMacAddr: ���MAC
*               ULONG ulDstIpAddr: ��ַ,������
*       Output:
*       Return:
*      Caution: PTN����,Ӧ�ó���:�����ظ�λ,�ײ�NP�ѱ���Ķ�̬ARP��ԭ��VISP,��̬ARP
*               ���Ͻӿڻ�ԭ��
*               �ýӿ�ֻ�������ظ�λ�ָ�ʱ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_AddDynamicArp(ULONG ulIfIndex, UCHAR *pucMacAddr, ULONG ulDstIpAddr);


ULONG TCPIP_AddDynamicArpWithVlan(ARPWITHVLANINFO_S *pstArpInfo);


/*******************************************************************************
*    Func Name: TCPIP_SendArpRequestForVlan
* Date Created: 2008-10-28
*       Author: zhangchunyu(62474)
*  Description: ָ���ӿڷ�����Ӧ��ַARP����,�û��ӿ�
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulDstIpAddr: ��ַ,������
*       Output:
*       Return: VOS_OK �ɹ�, ���� ʧ��
*      Caution: �ú���Ŀ����PTN��Ʒ���þ�̬ARP֮�󣬷��͵�Ŀ�ĵ�ַ��ARP����
*               �ж϶���̬ARP�Ƿ���ڳ�ͻ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-28    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SendArpRequestForVlan(ULONG ulIfIndex, ULONG ulDstIpAddr);


ULONG TCPIP_CheckSrcMac(UCHAR *ucSrcMacAddr);

/*******************************************************************************
*    Func Name: TCPIP_SetARPExpireTimeByIndex
* Date Created: 2009-6-4
*       Author: LY(57500)
*  Description: ����ARP��ʱʱ��
*        Input: ULONG ulTime: ���õ�ʱ��
*               ULONG ulIfIndex: ���õĽӿ�����
*       Output:
*       Return: VOS_OK: ���óɹ�
*               ����:   ����ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-6-4    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_SetARPExpireTimeByIndex(ULONG ulTime, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetARPExpireTimeByIndex
* Date Created: 2009-6-4
*       Author: LY(57500)
*  Description: ��ȡ�ӿڵ�arp��ʱʱ��
*        Input: ULONG* pulTime: �������arp��ʱʱ��
*               ULONG ulIfIndex: �ӿ�����
*       Output:
*       Return: VOS_OK: ��ȡ�ɹ�
*               ����:   ��ȡʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-6-4    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_GetARPExpireTimeByIndex(ULONG* pulTime, ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: TCPIP_SetVlanTag
* Date Created: 2008-5-8
*       Author: zhangchunyu(62474)
*  Description: ���ñ�����VLAN ID���û��ӿ�
*        Input: ULONG ulIfIndex: �ӿڵ�������
*               ULONG ulVlanTag: vLandId.����ֻ��VLANID,������������
*       Output:
*       Return:
*      Caution:���ulVlanTag�����㣬����ʹ����VLAN ���ܣ���ô������VLAN ͷ����Ϣ�ɲ�Ʒ����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-8    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetVlanTag(ULONG ulIfIndex , ULONG ulVlanTag);

/*******************************************************************************
*    Func Name: TCPIP_GetVlanTag
* Date Created: 2008-5-8
*       Author: zhangchunyu(62474)
* Description :  ��ȡ�ӿ�VLAN ID
* Others      :
* Input       : ulIfIndex:�ӿڵ�������
*               pulVlanTag: �������
* Output      : pulVlanTag: ����vlanID
* Return      : �ɹ�:0  ������ʾʧ��
* Caution     :
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-5-8    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetVlanTag(ULONG ulIfIndex, ULONG* pulVlanTag);


extern VOID TCPIP_ShowArpInfoByIf(CHAR *szIfName);

extern ULONG TCPIP_RegFunc1xInputHook(EAPOL_RECV_PKT_HOOK  pfEAPoL_RecvPkt_Hook);


extern ULONG TCPIP_UnRegFunc1xInputHook(VOID);


extern ULONG TCPIP_SendMacFrameOverEth (ULONG ulIfIndex, MBUF_S * pstMbuf);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncEtharpDealHook
* Date Created: 2009-9-8
*       Author: LY(57500)
*  Description: ��Ʒע��etharp���ĵĹ��Ӻ���
*        Input: ULONG ulInOrOut: ���ͻ����
*               ULONG ulPriority: ���ȼ���ֵ����Ч��ֵԽ�����ȼ�Խ��
*               ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc: ��ע�ṳ��
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-8    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncEtharpDealHook(ULONG ulInOrOut, ULONG ulPriority, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_UnRegFuncEtharpDealHook
* Date Created: 2009-9-8
*       Author: LY(57500)
*  Description: ��Ʒ��ע��etharp���ĵĹ��Ӻ���
*        Input: ULONG ulInOrOut: ���ͻ����
*               ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc: ����ע�ṳ��
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-9-8    LY(57500)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_UnRegFuncEtharpDealHook(ULONG ulInOrOut, ETHARP_INTERMEDIATE_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncIsNatIPAddrHook
* Date Created: 2010-05-20
*       Author: zhangchunyu(62474)
*      Purpose: ע���Ƿ���NAT ��ַ�ص�����
*  Description: ����ӿ�ʹ��NAT����,֧�ֽӿڻش�����ARP����,���յ�ARP�����ж��Ƿ��Ǹýӿ�NATʹ�õĵ�ַ,
*               ��������Ӧ���ӿڵ�MAC
*        Input: ETHARP_IS_NAT_IPADDR_HOOK_FUNC pfHookFunc: ע���Ƿ���NAT IP�ص�����<�ǿպ���ָ��>
*       Output: 
*       Return: �ɹ�:VOS_OK
*               ʧ��:����
*      Caution: 
*        Since: V100R008C03
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-05-20   zhangchunyu(62474)      Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncIsNatIPAddrHook(ETHARP_IS_NAT_IPADDR_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncEthBeforeAddVlanTagHook
* Date Created: 2010-11-03
*       Author: y171195(z171897)
*  Description: ע���װVlan�ײ�ǰ����ص�����
*        Input: ETH_BEFORE_ADD_VLANTAG_HOOK  pfEthBeforeAddVlanTagHook: �ص�����
*       Output: 
*       Return: �ɹ�:VOS_OK
*               ʧ��:����
*      Caution: 1.�ù��Ӻ���֧�ֶ�̬ע��ͽ�ע��,���Բ�Ʒ������Э��ջ����֮�����
*                 ���øýӿ�ע��ͽ�ע��.
*               2.�ûص����Ӻ����в���ʹ�ò�Ʒ���ź�����������ܻ��VISP���ź�������������
*               3.Ϊ֧��DHCP VLAN Scanning���������ýӿ�.
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                          DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-11-03   y171195(z171897)              Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncEthBeforeAddVlanTagHook(ETH_BEFORE_ADD_VLANTAG_HOOK  pfEthBeforeAddVlanTagHook);


ULONG TCPIP_SetUnicastARPCount(ULONG ulCount);


ULONG TCPIP_GetUnicastARPCount(ULONG *pulCount);

/*******************************************************************************
*    Func Name: TCPIP_SetARPCapture
* Date Created: 2011-06-02
*       Author: zhaoyue00171897
*  Description: ����ARP�����շ����г���
*        Input: ULONG ulIfIndex: �ӿ���������������̫���͵����ӿ�
*               ULONG ulRcvCaptureQueLen: ���ն��г��ȣ�ȡֵ��Χ[0, 128]
*               ULONG ulSndCaptureQueLen: ���Ͷ��г��ȣ�ȡֵ��Χ[0, 128]
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*               ��֧��VLAN IF
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_SetARPCapture(ULONG ulIfIndex, ULONG ulRcvCaptureQueLen, ULONG ulSndCaptureQueLen);

/*******************************************************************************
*    Func Name: TCPIP_GetARPCapture
* Date Created: 2011-06-02
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: ��ȡARP�����շ����г���
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: ULONG *pulRcvCaptureQueLen: ���ն��г���
*               ULONG *pulSndCaptureQueLen: ���Ͷ��г���
*       Return: VOS_OK    �ɹ�
*               ����      ʧ��
*      Caution: ��֧��VLAN IF
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_GetARPCapture(ULONG ulIfIndex, ULONG *pulRcvCaptureQueLen, ULONG *pulSndCaptureQueLen);

/*******************************************************************************
*    Func Name: TCPIP_GetARPCaptureQue
* Date Created: 2011-06-02
*       Author: zhaoyue00171897/shuxieliu00176784
*  Description: ��ȡ��̫/Trunk���ӿ��ϱ����ARP���Ķ���
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: ULONG *pulRcvQueMbufNum: ���ձ��Ķ����еı��ĸ���
*               MBUF_S **ppstRcvMbuf: ARP���Ľ��ն���
*               ULONG *pulSndQueMbufNum: ���ͱ��Ķ����еı��ĸ���
*               MBUF_S **ppstSndMbuf: ARP���ķ��Ͷ���
*       Return: 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-02   zhaoyue00171897         Create
*
*******************************************************************************/
ULONG TCPIP_GetARPCaptureQue(ULONG ulIfIndex, ULONG *pulRcvQueMbufNum, MBUF_S **ppstRcvMbuf,
                             ULONG *pulSndQueMbufNum, MBUF_S **ppstSndMbuf);

/*******************************************************************************
*    Func Name: TCPIP_SetArpExpireOffsetTime
* Date Created: 2013-12-04
*       Author: mafeng 59090
*  Description: ����ARP����ϻ�ƫ��ʱ��
*        Input: UCHAR ucTime: 0 ��ƫ�ƣ�[30,60] ƫ���ϻ�ʱ��ȡֵ��Χ
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: ������Ϊ0ʱARP��������õ��ϻ�ʱ������ϻ�������0ʱ���ȡһ��
*               0~����ֵ֮���������Ϊ�ϻ�ʱ���ƫ��ֵ��
*               ��API����������ɺ����ɵ�ARP������Ч������֮ǰ��ARP�ϻ�ʱ�䲻ˢ�¡�

*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-04   mafeng 59090            Create
*
*******************************************************************************/
ULONG TCPIP_SetArpExpireOffsetTime(UCHAR ucTime);

/*******************************************************************************
*    Func Name: TCPIP_GetArpExpireOffsetTime
* Date Created: 2013-12-04
*       Author: mafeng(59090)
*  Description: ��ȡARP����ϻ�ƫ��ʱ��
*        Input: UCHAR *pucTime:0 ��ƫ�� ��0 ƫ��ʱ��(s)
*       Return: VOS_OK �ɹ�
*               ������ ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-12-04   mafeng(59090)           Create
*
*******************************************************************************/
ULONG  TCPIP_GetArpExpireOffsetTime(UCHAR *pucTime);

/*******************************************************************************
*    Func Name: TCPIP_SetArpStrictLearnSwitchByIntf
* Date Created: 2014-04-03
*       Author: likaikun213099
*  Description: ֧���ϸ�ѧϰARP����ܽӿڿ�������
*               ʹ�����ϸ�ARP����ѧϰ��,��ѧϰ�Լ����͵�ARP�����ĵ�Ӧ����,
*               ��������һ�ɲ��ٽ���ARP����ѧϰ.���Ҳ���ARP�ظ�����������,��ֱ�Ӷ��������Է�����
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulSwitch:  ����,0 �ر�, 1 ��, Ĭ�Ϲر�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_SetArpStrictLearnSwitchByIntf(ULONG ulIfIndex, ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetArpStrictLearnSwitchByIntf
* Date Created: 2014-05-27
*       Author: likaikun213099
*  Description: 
*        Input: ULONG ulIfIndex:
*               ULONG *pulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-05-27   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_GetArpStrictLearnSwitchByIntf(ULONG ulIfIndex, ULONG *pulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_DelArpEntryByVrfIndex
* Date Created: 2014-11-20
*       Author: caiqizheng
*  Description: ɾ��ĳ��ָ��VRF��ARP����
*        Input: ULONG ulIpAddr:��ַ
*               ULONG ulScope:��Χ
*               ULONG ulVrfIndex:vrf����
*       Output: ��
*       Return: �ɹ��������
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-11-20   caiqizheng           VISP1.7C03 VRF,Create
*******************************************************************************/
extern ULONG TCPIP_DelArpEntryByVrfIndex(ULONG ulIpAddr,ULONG ulScope,ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetArpEntryByIntfAndIPAddr
* Date Created: 2014-12-16
*       Author: likaikun213099
*  Description: ָ���ӿں�IP��ַ��ȡARP����
*        Input: ULONG ulIfIndex:
*               ULONG ulIPAddr:
*       Output: ARPINFO_S *pstARPInfo:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-16   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_GetArpEntryByIntfAndIPAddr(ULONG ulIfIndex, ULONG ulIPAddr, ARPINFO_S *pstARPInfo);

/*******************************************************************************
*    Func Name: TCPIP_DelDynamicArpEntryByIntf
* Date Created: 2014-12-16
*       Author: likaikun213099
*  Description: ɾ��ָ���ӿں�IP��ַ�Ķ�̬ARP�����̬ARP���õ�ʱ��û�нӿ���Ϣ��
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulIpAddr:IP��ַ(����˳��)
*       Output: ��
*       Return: VOS_OK:�ɹ�
*               ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-16   likaikun213099          Create
*
*******************************************************************************/
ULONG  TCPIP_DelDynamicArpEntryByIntf(ULONG ulIfIndex, ULONG ulIpAddr);

/*******************************************************************************
*    Func Name: TCPIP_ShowARPTimerListInfo
* Date Created: 2014-12-23
*       Author: likaikun213099
*  Description: ARP�ϻ�ʱ��ڵ���Ϣ��ѯ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-23   likaikun213099          Create
*
*******************************************************************************/
VOID TCPIP_ShowARPTimerListInfo(VOID);


ULONG TCPIP_RegFuncGetARPRcvIfIndexHook(ETHARP_GETARPRCVIFINDEX_HOOK_FUNC pfHookFunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ETHARP_API_H_ */

