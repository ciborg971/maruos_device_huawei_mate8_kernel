

#ifndef    _ETHARP_PUB_TYPE_H_
#define    _ETHARP_PUB_TYPE_H_

#ifdef    __cplusplus
extern "C"{
#endif

#include "tcpip/sfib4/include/ifiba_inc.h"
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/public/arith_cbb/include/avltree.h"
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
#include "tcpip/vlink/include/vlink.h"
#include "tcpip/etharp/include/etharp_api.h"

enum enumArpMsg
{
    Help_Mac_Info = 0
};
/*ETHARPģ��SID����*/
#define SID_COMP_ETHARP_MTSOFTC_S       ( 1 )
#define SID_COMP_ETHARP_MTSOFTCSUB_S    ( 2 )
#define SID_COMP_ETHARP_ARPRTENTRY_S    ( 3 )
#define SID_COMP_ETHARP_ARPCMD_S        ( 4 )

/*��·��ͷ����*/
/*#define ETHERNETMTU     0x0600 */
/* ��ǰ��̫��trunk�ӿڵ����MTU����Ϊ1800��Ϊ������ȷ�������ָ�ʽ����̫���ģ�
 * Ҳ��Ҫ����ETHERNETMTU,���ڵ���Ϊ1836(0x072c) */
#define ETHERNETMTU     0x072c
/*ARP���������Ŀ*/
#define ARP_TABLELEN    4096 
 

/*�ӿ�״̬*/  /*�Ѿ����ã���IFNETͳһ*/
#define IFNETDOWN 0
#define IFNETUP   1


#define RESOLVED    2            /*ARP������״̬,�Ѿ���������*/
#define RESOLVING   3            /*ARP������״̬,���ڽ���*/
#define MAXSCRIPT   6            /*��̫���ӿ������ֵ���󳤶�*/
#define HEADER_LEN  16           /*��̫����ͷ�ĳ���*/

#define PKTFMT_EN_LEG_DHCP 0xffff

/* ָ���˱��㷨�������ARPʱ�Ĵ��� */
#define ETHARP_SENDFREEARP_3TIMES  3 
#define ETHARP_SENDFREEARP_4TIMES  4

/* ��һ�γ�ʱʱ�䣬��λ���� */
#define ETHARP_SENDFREEARP_OUTTIME 2000

/* ARP����ˢ�±�� */
#define ETHARP_ARPUPDATE_BYFREEARP 0x01   /* ARP����MAC�����ARP������ */
#define ETHARP_ARPUPDATE_OUTIF     0x02   /* ��̬ARP����ˢ�³��ӿ� */

/*����ԴMAC�ļ�飬�жϱ����е�ԴMAC�Ƿ�ͽӿڵ�MAC��ͬ����ͬ����Ҫ�����Ƿ�����
 ��������Ϊ�˿����ϱ���ͻ�澯
 
0:    ETH���Ĳ����   ARPҪ���
1:    ETH���ļ��     ARPҲ���
2:    ETH���Ĳ����   ARP�����    MCCP ʹ��

*/
#define ETHARP_ETH_AND_ARP_MACCHECK_POLICY   2  /*֧��MCCP ����ԴMAC�ļ��:  ETH���Ĳ����  ARP����Ҳ�����*/

/* ARP�ϻ���ʱ�����־ */
#define ETHARP_ARP_EXPIRE_PROC       1
/* ARP���ϻ���ʱ�����־ */
#define ETHARP_NOT_ARP_EXPIRE_PROC   0 

/* �����ϱ�ARP MISS���Խ������ */
enum tagArpMissDebugCode
{
    ARPMISS_SUCCESSDOWN = 1,      /* 1 �ɹ��·�arp */
    ARPMISS_SUCCESSREQUEST,       /* 2 �ɹ�����arp���� */
    ARPMISS_NOREGPPI,             /* 3 û��ע��arp ppi���Ӻ��� */
    ARPMISS_WRONGIFINDEX,         /* 4 �ӿ����������� */
    ARPMISS_NOMTSOFT,             /* 5 �����ڽӿڿ��ƿ� */
    ARPMISS_WRONGIFTYPE,          /* 6 �ϱ��ӿ����ʹ��� */
    ARPMISS_NOSOURCEIP,           /* 7 �ӿ�û�е�ַ */
    ARPMISS_SENDFAIL,             /* 8 ����arp������ʧ�� */
    ARPMISS_INSERTNODE,           /* 9 ����ARP�ڵ�ʧ�� */
    
    ARPMISS_MAX
};

/*add by wht06310 for compatibility ARMCPU,2006-05-13*/
#ifdef TCPIP_SUPPORT_ARMCPU
#define FAST_COPY_MACADDR(Dest,Source) \
    ((VOID)TCPIP_Mem_Copy((VOID *)(Dest), 6, (VOID *)(Source), 6))
#define FAST_COPY_8BYTE(Dest,Source) \
    ((VOID)TCPIP_Mem_Copy((VOID *)(Dest), 8, (VOID *)(Source), 8))
#else
#define FAST_COPY_MACADDR(Dest,Source) \
    ((ULONG *)(Dest))[0] = ((ULONG *)(Source))[0]; \
    ((USHORT *)(((UCHAR *)(Dest))+4))[0] = ((USHORT *)(((UCHAR *)(Source))+4))[0]
#define FAST_COPY_8BYTE(Dest,Source) \
    ((ULONG *)(Dest))[0] = ((ULONG *)(Source))[0]; \
    ((ULONG *)(((UCHAR *)(Dest))+4))[0] = ((ULONG *)(((UCHAR *)(Source))+4))[0]    
#endif



/*�����Ǳ�ģ��ĺ궨��*/
#define ETHARP_GET_ETHERHDR_FROM_MTSOFTC(pMtSoft)    ((pMtSoft)->ucEthernetHeader)

#define ETHER_MAP_IP_MULTICAST(ipaddr, enaddr) \
{ \
    (enaddr)[0] = 0x01; \
    (enaddr)[1] = 0x00; \
    (enaddr)[2] = 0x5e; \
    (enaddr)[3] = ((UCHAR *)ipaddr)[1] & 0x7f; \
    (enaddr)[4] = ((UCHAR *)ipaddr)[2]; \
    (enaddr)[5] = ((UCHAR *)ipaddr)[3]; \
}


#define AF_UNICAST_ARP 20           /* ����ARP */

/*������IFNETͳһ�ṩ����ʱ*/
#define IF_LINKSTATE_LINKUP   19
#define IF_LINKSTATE_PHYDOWN  20

#define ETHARP_SNDBUF_MAX_LEN 10  
#define ETHARP_SNDBUF_TOTAL_LEN  512
#define ETHARP_WAIT_FOR_RESOLVE 3  /*����ARPʧ�����ݴ����ʱ�ķ���ֵ?for D25765*/


#define ETHERTYPE_IP6    0x86DD   /*IPv6Э��Ķ���*/
#define INTERFACEIDLEN   8

#define IP6_ETHER_MAC_MULTICAST(enaddr) ( ((UCHAR)0x33 == (enaddr)[0]) && ((UCHAR)0x33 == (enaddr)[1]) ) 

#define ETHARP_INIT_INTERFACE_ID( interface_id ) \
{\
  (interface_id)[0] = ( UCHAR ) 0x00;\
  (interface_id)[1] = ( UCHAR ) 0x00;\
  (interface_id)[2] = ( UCHAR ) 0x00;\
  (interface_id)[3] = ( UCHAR ) 0x00;\
  (interface_id)[4] = ( UCHAR ) 0x00;\
  (interface_id)[5] = ( UCHAR ) 0x00;\
  (interface_id)[6] = ( UCHAR ) 0x00;\
  (interface_id)[7] = ( UCHAR ) 0x00;\
}

#define ETHER_MAP_IP6_MULTICAST(ipaddr, enaddr) \
{ \
    (enaddr)[0] = 0x33; \
    (enaddr)[1] = 0x33; \
    (enaddr)[2] = ((UCHAR *)ipaddr)[12]; \
    (enaddr)[3] = ((UCHAR *)ipaddr)[13]; \
    (enaddr)[4] = ((UCHAR *)ipaddr)[14]; \
    (enaddr)[5] = ((UCHAR *)ipaddr)[15]; \
}

#define ETHER_MAP_MAC_INTERFACEID(enaddr , interfaceid) \
{ \
   (interfaceid)[0] = (enaddr)[0] | (CHAR)0x02; \
   (interfaceid)[1] = (enaddr)[1];  \
   (interfaceid)[2] = (enaddr)[2];  \
   (interfaceid)[3] = (CHAR)  0xff; \
   (interfaceid)[4] = (CHAR)  0xfe; \
   (interfaceid)[5] =(enaddr)[3]; \
   (interfaceid)[6] =(enaddr)[4]; \
   (interfaceid)[7] =(enaddr)[5]; \
}

typedef struct tagARPTOREPLYINFO
{
    ULONG   ulIpAddr;                     /* ��Ӧ���ARP�����е�Ŀ�ĵ�ַ */
    struct tagARPTOREPLYINFO *pstNext;   /* ��һ����Ӧ���ARP�����е�Ŀ�ĵ�ַ */
}ARPTOREPLYINFO_S;

#define  ETHER_GET_LINKSTATUS(pstIf) \
     ((pstIf->if_ulSubIndex)?((IF_GETMTSOFT(pstIf))?(((ETHARP_MTSOFTCSUB_S*)IF_GETMTSOFT(pstIf))->ulLinkStatus):0)\
     :((IF_GETMTSOFT(pstIf))?(((ETHARP_MTSOFTC_S*)IF_GETMTSOFT(pstIf))->ulLinkStatus):0))

/*#pragma VOS_BEGINPACK(1)                            ���ֽڶ���*/
typedef struct tagARPRTENTRY
{
    struct    tagARPRTENTRY*   pRtLeft;              /* ������ */
    struct    tagARPRTENTRY*   pRtRight;             /* ������ */
    ULONG                    ulRtIpAddr;             /*���������ַ*/
    UCHAR                    ucMacAddr[6];           /*��������physical��ַ*/
    UCHAR                    ucDArpFlag;             /*��¼��̬ARP��¼�Ƿ����û���� */
    UCHAR                    ucSArpConflict;         /*��̬ARP�Ͷ�̬ARP��ͻ���,1��ͻ 0����ͻ */ 
    ULONG                    ulFlags;                /*��ARP�ı�־�ֶ� */
    ULONG                    ulRtIfIndex;            /*��������IFNET�ӿ�INDEX*/
    ULONG                    ulRtExpire;             /*����ʵ��ARP����ĳ�ʱ���� */
    struct    tagARPRTENTRY*   pLPrev;       /*ָ��ǰ��ARPENTRY_S��(�ϻ���)*/
    struct    tagARPRTENTRY*   pLNext;       /*ָ����ARPENTRY_S��(�ϻ���)*/
    ULONG                     ulAsked;                /*��ARP��������Ĵ���*/ 
    ULONG                    ulVrfIndex;        /*��ʾ��ַ���ڵ�VPN*/
    /* xiehuaguo add for support np 2006-05-08 */
    /*Ŀǰ�ķ����У�Э��ջ�����ʱ��¼��Ʒ��VLINK����������UPDATE��ɾ��ʱ͸����
    Ϊ�˱���Ͳ�Ʒ������ϣ�Э��ջUPTATEʱ���������������Ƿ�Ӧ��UPDATE����ADD��
    �ɲ�Ʒ������ʱ����vlink���������ַַ���Ϣ��*/
    ULONG                   ulVlinkIndex;/*NP�·��󷵻ص�VLINK������*/
    MBUF_QUEUE_S         stSndPkts ;/*�����ݴ�ARPû�����ɷ��͵ı���*/
    struct     tagMTSOFTC* pMtSoft;           /*��̫�����ƿ�zhanghongyan*/
    UCHAR    ucReSendNum;   /*����ARP��ʱ֮����������ARP����Ĵ���*/
    UCHAR    ucHasDownLoadToNP;  /* 1 �ñ������·�NP 0 δ�·�NP.���·�ɾ��ARPʱ��,�ñ�Ǳ���Ϊ1,
                                    ����˵����ARP����û���·���NP,Ŀǰ��ADD��UPDATE�����Ѿ��Ѹñ����1 */
    USHORT   usVID;         /*��ARP��Ӧ��VLANID*/
    struct    tagARPRTENTRY*   pNodePrev;   /*ָ��ǰ��ARPENTRY_S��(˳����)*/
    struct    tagARPRTENTRY*   pNodeNext;   /*ָ����ARPENTRY_S��(˳����)*/

    ULONG     ulOutPortIfIndex;
    ULONG     ulCountToReply;   /* VLANIF����ARP����󣬴�Ӧ���ARP������� */
    ARPTOREPLYINFO_S *pstArpToRelayNode;   /* VLANIF����ARP����󣬴�Ӧ���ARP�������� */

    UCHAR        ucArpUpdateFlag;          /* ARP�����и��� */
    UCHAR        ucSourceType;      /*��̬ARP����Դ:��ѧϰ���û����á����ú����ѧϰ����*/
    UCHAR        ucReserved[2];
    TCPIP_TIME_S stEtharpUpdateTime;       /* ARP�������һ�θ���ʱ�� */
    ULONG ulDownNpTime;   /* ARP�����·�Npʱ�� */  
    VOID         *pstGuardNode;            /* ARP����ƭ�ڵ� */

    /*arp Mccp support V300R001C00 --  start*/    
    ULONG ulLastRefTime;              /*absolute Time at which the entry was last ref.*/
    struct tagARPTIMER_ENTRY_NODE *pEntryTimerNode;  /*Timer node for the arp entry node*/
    /*arp Mccp support V300R001C00 --  end*/ 
    
}ETHARP_ARPRTENTRY_S;

/*a00900872--changes for Arp Timer optimisation.*/

typedef struct tagARPTIMERLIST
{
    ULONG ulTimeoutValue;     /*Time out Value*/
    struct tagARPTIMERLIST   *pNextTimerNode;    /*next node*/    
    struct tagARPTIMERLIST   *pPrevTimerNode;    /*previous node*/        
    struct tagARPTIMER_ENTRY_NODE *ptimerEntryNodeList; /*Arp Entry node in the list*/            
    
}ETHARP_TIMER_LIST_S;

typedef struct tagARPTIMER_ROOTNODE
{

    ULONG ulTimerId;     /*Time out Value*/
    ETHARP_TIMER_LIST_S *pTimerList;      /*starting  of the timer list */    
    ULONG ulCount;
}ETHARP_TIMER_ROOTNODE_S;


/*timer helper task- linked list structure */
typedef struct tagARPHELPERTASKNODE
{
    ULONG ulListId;     /*List Id Value*/
    struct tagARPHELPERTASKNODE *pNext;
    struct tagARPTIMER_ENTRY_NODE *pArpHelperEntryNodeList;
    
}ETHARP_HELPERTASK_NODE_S;


typedef struct tagARPTIMER_ENTRY_NODE
{
    struct tagARPTIMER_ENTRY_NODE   *pNextTimerEntryNode;    /*next node*/   
    struct tagARPTIMER_ENTRY_NODE   *pPrevTimerEntryNode;    /*previous node*/  
    struct tagARPTIMER_ENTRY_NODE   **pParentTimerlistNode;     /*Parent Timerlist node*/   
    ETHARP_ARPRTENTRY_S *pActualEntryNode;                          /*Arp Entry node list*/  
    
}ETHARP_TIMERENTRY_NODE_S;


/*a00900872--changes for Arp Timer optimisation.*/


typedef struct  tagETHARP_ARPTABLE
{
    ETHARP_ARPRTENTRY_S*     pRtLeft;  /* ������ */
    ETHARP_ARPRTENTRY_S*     pRtRight; /* ������ */
}ETHARP_ARPTABLE_S;  


/* �޸ĸ����ݽṹ,��Ҫ�ں������,������ӵ��м�,����Ҫ�����Ƿ����ӽӿڿ��ƿ����Ӱ��.
   ��Ϊ��Ҫ��֤�����ݽṹ���ӽӿڿ��ƿ�tagMTSOFTCSUBǰ������ݽṹһ��,��Ӧ��pppoc������,
   ����ת��,�����һ�¿��ܵ����쳣*/
typedef struct  tagMTSOFTC
{
    struct     tagIFNET*   pMtSoftIf;             /*����ƿ�������IFNET*/
    USHORT                 usIPEncapsulation;     /*��ͬ��IP���ķ�װ��ʽ*/
    USHORT                 usIPXEncapsulation;    /*��ͬ��IPX���ķ�װ��ʽ*/
    ULONG                  ulLinkStatus;          /*�����ӿڵ�DOWN��UP״̬*/
    ULONG                  ulNetProtocolStatus;  /*protocol link status of the interface except IP */

    ULONG           ulIP6LinkStatus;          /*�����ӿڵ�IPv6 DOWN��UP״̬*/
    UCHAR           ucInterfaceID[8];          /* �ӿ�ID */

    struct     tagIFNET*   pIPXEncapsulation[4];  /*��װ��ͬIPX����*/
    struct     tagMTSOFTC* pMtSoftNext;           /*��̫�����ƿ�*/
    UCHAR       ucEthernetHeader[HEADER_LEN];      /*��̫����ͷ*/    

    BOOL_T                  bIsARPproxy;/* true or false �ýӿڵ�ARP PROXY�����Ƿ���Ч*/
    UCHAR                   ucArpDetectTimes; /* ARP��ʱ̽����� */
    UCHAR                   ucArpLog;         /* �Ƿ��¼ARP������־ */ 

    ULONG                   ulArpExpireTime;  /* ARP��ʱʱ�� */
    
    ULONG                   ulPoecDebugFlag;             /*PPPoE Client Debug Flag*/
    VOID *                  pPoeClientCB;                /*PPPoE Client CB Pointer*/
    ETHARP_ARPRTENTRY_S    sArpRoot;              /*ARP��ͷ*/
    ETHARP_ARPTABLE_S      sArpTable[ARP_TABLELEN];             /*ARP ��*/ 
    ULONG                  ulArpNumber;           /*ARP��*/
    ULONG                  ulTimerId;  /* ��ʱ��ID */
    ULONG                  ulVlanFlag ;   /*��ʶ�ӿ��Ƿ�ʹ��VLAN�� ��*/
    UCHAR                  ucBakEthMac [MACADDRLEN]; /* ���ݵ�MAC */
    USHORT                 usDhcpflag ;  /* �ӿ��Ƿ�ʹ��DHCP�ı�� */

    ETHSTAT_S              stETHStat; /* ��̫�ӿڵı���ͳ����Ϣ */
    ULONG                  ulIsIsFlag;  /*�Ƿ�ʹ���շ�ISIS���ģ�Ϊ1ʹ�ܣ�0ȥʹ��*/
    USERARPSTAT_S          stUserArpStat; /* �û�ָ������ARP����ͳ����Ϣ */   
    UINTPTR  ulVLANPortInfo;  /* The address of the VLAN port info structure */
    BOOL_T                 bIsVlanARPproxy;
    UCHAR                  ucArpUpdate;
    UCHAR                  ucReserved;
    ULONG                  ulVlanId ;      /* vlan ID */
    
    BOOL_T                 bEnableSpecArpPrxy;  /*�ýӿڵ�����ARP�������Ƿ���Ч*/
    BOOL_T                 bEnableIfArpStrict;

    /* Add by z171897/s176784, at 2011-06-02. �޸�ԭ��: ֧�ֻ�ȡ�����ARP���Ķ��� */
    MBUF_QUEUE_S           stSndArpPktQue;  
    MBUF_QUEUE_S           stRcvArpPktQue;
}ETHARP_MTSOFTC_S;
/* ע��:���ӿڿ��ƿ���ӽӿڿ��ƿ�ǰ������ݽṹ��ͬ,ת������Թ���,����������ݽṹ���ӽӿڲ�ͬ,�����ת��,
   ��ע��pPoeClientCB����ı�����ucArpLog�����ṹ���в�ͬ,���ܻᵼ��ȡֵ������쳣 */

#define IP_ARP_PROXY_DISABLE BOOL_FALSE
#define IP_ARP_PROXY_ENABLE  BOOL_TRUE

/* �޸ĸ����ݽṹ,��Ҫ�ں������,������ӵ��м�,����Ҫ�����Ƿ��Ը��ӿڿ��ƿ����Ӱ��.
   ��Ϊ��Ҫ��֤�����ݽṹ���ӽӿڿ��ƿ�tagMTSOFTCSUBǰ������ݽṹһ��,��Ӧ��pppoc������,
   ����ת��,�����һ�¿��ܵ����쳣*/
typedef struct  tagMTSOFTCSUB
{
    struct     tagIFNET*   pMtSoftIf;             /*����ƿ�������IFNET*/
    USHORT                 usIPEncapsulation;     /*��ͬ��IP���ķ�װ��ʽ*/
    USHORT                 usIPXEncapsulation;    /*��ͬ��IPX���ķ�װ��ʽ*/
    ULONG                  ulLinkStatus;          /*�����ӿڵ�DOWN��UP״̬*/
    ULONG                  ulNetProtocolStatus;  /*protocol link status of the interface except IP */
    ULONG           ulIP6LinkStatus;          /*�����ӿڵ�IPv6 DOWN��UP״̬*/
    UCHAR           ucInterfaceID[8];          /* �ӿ�ID */

    struct     tagIFNET*   pIPXEncapsulation[4];  /*��װ��ͬIPX����*/
    struct     tagMTSOFTC* pMtSoftNext;           /*��̫�����ƿ�*/
    UCHAR                  ucEthernetHeader[HEADER_LEN]; /*��̫����ͷ*/

    BOOL_T    bIsARPproxy;/* true or false �ýӿڵ�ARP PROXY�����Ƿ���Ч*/

    UCHAR      ucArpDetectTimes; /* ARP��ʱ̽����� */
    UCHAR      ucPadding;        /*ע��:�����ֶ�Ҫ��ETHARP_MTSOFTC_S �е�ucArpLog����*/
    
    ULONG      ulArpExpireTime;  /* ARP��ʱʱ��  �����ӿڽṹ��λ��һ��*/

    ULONG                   ulPoecDebugFlag;             /*PPPoE Client Debug Flag*/
    VOID *                  pPoeClientCB;                /*PPPoE Client CB Pointer*/
    
    UINTPTR      ulVLANPortInfo;  /* The address of the VLAN port info structure */
    BOOL_T                 bEnableSpecArpPrxy;
    BOOL_T                 bEnableIfArpStrict;

    ETHSTAT_S              stETHStat; /* ��̫�ӿڵı���ͳ����Ϣ */
   
}ETHARP_MTSOFTCSUB_S;
/* ע��:�ӽӿڿ��ƿ�����ӿڿ��ƿ�ǰ������ݽṹ��ͬ,ת������Թ���,����������ݽṹ�����ӿڲ�ͬ,�����ת��,
   ��ע��pPoeClientCB����ı���ucPadding�����ṹ���в�ͬ,���ܻᵼ��ȡֵ�쳣 */


typedef struct tagETHARP_MOD_INFO
{
    ULONG    ulEthModID;
    ULONG    ulSID_ETHARP_MTSOFTC_S;
    ULONG    ulSID_ETHARP_MTSOFTCSUB_S;
    ULONG    ulSID_ETHARP_ARPRTENTRY_S;
    ULONG    ulSID_ETHARP_ARPCMD_S;    
    ULONG    ulQUE_PPPOE_CLIENT_INPUT;
    ULONG    ulQUE_PPPOE_INPUT;
    ULONG    ulQUE_IP_INPUT;
    ULONG    ulQUE_IPV6_INPUT;
    ULONG    ulQUE_ARP;
    ULONG    ulMBUF_LINK_TYPE_ETHERNET;
    ULONG    ulARP_ENTRY_MAINTYPE;/*waitlist*/
    ULONG    ulETH_ENTRY_MAINTYPE;/*waitlist*/
    ULONG    ulMAX_APRNUMBER_DYNAMIC;
    ULONG    ulMAX_STATIC_ARPNUMBER;
    ULONG    ulETH_IPINPUT_OPTIMIZE;
    ULONG    ulBakDynamicArp  ; /*��ʶ�Ƿ񱸷ݶ�̬ARP*/
    ULONG    ulBakMacSet; /*��ʶphysical��ַ�����÷�ʽ*/
    ULONG    ulQUE_ISIS_INPUT;
    ULONG    ulIPConflictMode;        /*IP��ͻ����ģʽ:0,���ⲿģ�鴦��;��VISP���д���*/
    ULONG    ulStaticArpDownload;     /* ����(����ɾ������)��̬ARP�Ƿ��·�NP,��������������,
                                         Ĭ������ñ��Ϊ0,���Ԥ��������Ϊ1,�û������ɾ����̬ARPʱ,��ֱ���·�NP */
    ULONG    ulArpMissNotNetTimeOut;  /*�ϱ�ARP MISS�����ַ�ͽӿڲ���ͬһ����,��Ԫ���ϻ�ʱ��  */ 
    ULONG    ulChkPktSrcMac;          /*�Ƿ��鱨�ĵ�Դ��ַ,1Ϊ���,0Ϊ�����,Ĭ��Ϊ����� */
    ULONG    ulFreeArpReplyUnicast;   /* �Ƿ񵥲�Ӧ���ַ��ͻ�����ARP���� */
    ULONG    ulArpTimerList;  /* ARP timer list */
    ULONG    ulSysDynicArpMaxNum;        /* ����201305305465,ϵͳ���������̬ARP��Ŀ */
    ULONG    ulArpStrictLearnMode;
    ULONG    ulArpSwapFalg;
} ETHARP_MOD_INFO_S;

enum enum_Eth_ErrCode 
{    
    Eth_InvalidPacket=0, 
    Eth_NullCB, 
    Eth_NullPPPOECB, 
    Eth_LinkDown,  
    Eth_UnkonwnProType, 
    Eth_UnsupportUpPro,
    Eth_ONESEFMAC,
    Eth_MEMPREPEND_FAIL,
    ETH_UNSUPPORTISIS,
    ETH_OAM3AH_LB_LOCAL,
    Eth_OK
};

typedef struct tagETHARP_SHELL_CALLBACK_SET
{
    VOID (*pfETHARP_CreateTimer) (VOID * timerList, VOID  (*pfTimerFunc)(VOID *), ULONG *pulTimerId);
    ULONG (*pfETHARP_DelTimer)(ULONG ulTimerId);
    ULONG (*pfETHARP_CreateQueue)(ULONG ulQueID,ULONG ulGetCntPerTimes,
            ULONG (* Eth_QueDealPacketFunc)(MBUF_S *),
            ULONG (* Eth_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*),
            ULONG ulMaxLen);
    ULONG (*pfETHARP_ActiveQueue)(ULONG ulQueID);
    ULONG (*pfETHARP_EnQueue)(MBUF_S *);
    ULONG (*pfETHARP_DropQueue)(MBUF_S *);
    VOID (*pfETHARP_FreePacketInQueue)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);

    /*������Ϣ���(ֱ������ַ���), һ���Ʒ���������*/
    VOID (*pfETHARP_SimpleDebugInfo)(CHAR *pBuf, ULONG ulLen);

    /*������Ϣ���(���ģ�������������) ��
    �����ڶ������Ϣ������Ҫ��Ĳ�Ʒ*/
    VOID (*pfETHARP_DebugEthPacket)(IFNET_S *pIf, ETHARP_ETSNAPHDR_S * pHead, enum enum_Eth_ErrCode ulErrCode, ULONG ulEvent);
    VOID (*pfETHARP_DebugArpEvent)(ETHARP_ETHERARP_S *pArp, ULONG ulEvent);

    VOID (*pfPPPOE_SetOurMac)( IFNET_S *pstIfnet );
}ETHARP_SHELL_CALLBACK_SET_S;

typedef struct tagETHARP_VLAN_PROC_HOOK
{
    ULONG (*pfETHVLAN_InitPortInfo)( ETHARP_MTSOFTC_S *pBufMtSoftC);
    VOID (*pfETHVLAN_ClearPortInfo)( ETHARP_MTSOFTC_S *pBufMtSoftC);
    /*ULONG (*pfETHVLAN_Output)( IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID);*/
    ULONG (*pfETHVLAN_Output)( IFNET_S *pIf, MBUF_S * pstMBuf,USHORT usVID,ULONG *pulSndPkts);
    ULONG (*pfETHVLAN_Input)( MBUF_S * pstMbuf,IFNET_S *pIf);
    ULONG (*pfETHVLAN_VlanCheck)( IFNET_S *pIf);
    /* Added by hanna55555, Eth-link ipv6 for BC3D01596, 2009/5/14 */
    BOOL_T (*pfETHVLAN_HaveVid)( ETHARP_MTSOFTCSUB_S *pBufMtSoftC );
    /*End of Added by hanna55555, 2009/5/14 */

    ULONG (*pfETHVLAN_IsForbidIf)(IFNET_S *pstIf);

    ULONG (*pfETHVLAN_HA_BatchBackup)(VOID);
    ULONG (*pfETHVLAN_HA_RealTimeBackup)(ULONG ulBakType, VOID* pData);
    ULONG (*pfETHVLAN_HA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);
    VOID  (*pfETHVLAN_HA_VerboseOutput)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
    ULONG (*pfETHVLAN_HA_Smooth)(VOID);
    ULONG (*pfETHVLAN_HA_Clean)(VOID);
    VOID  (*pfETHVLAN_VlanConsistencyWarningProc)(MBUF_S *pstMBuf, USHORT usVlanId, ULONG ulMainIfIndex, ULONG ulVlanSubIfIndex);
    
} ETHARP_VLAN_PROC_HOOK_S;

/* 
 * Add this struct for suppotting CBSC and NodeB 
 * or another requirements submitted by special product,
 * using this as adapter function's parameter 
 */





#define ETHARP_GET_STATIC         1
#define ETHARP_GET_DYNAMIC        2
#define ETHARP_GET_NEXT_INTERFACE 1
#define ETHARP_DEFAULT_VRF_INDEX  0


#define ETHARP_SCOPE_STATIC          0x01
#define ETHARP_SCOPE_DYNAMIC         0x02
#define ETHARP_SCOPE_ALL             (ETHARP_SCOPE_STATIC | ETHARP_SCOPE_DYNAMIC)
#define ETHARP_SCOPE_THIS_INTERFACE 0x04
#define ETHARP_SCOPE_PER_INTERFACE  0x08

#define ETHARP_SEND_PACKET 1
#define ETHARP_RECE_PACKET 2
#define ETHARP_DISC_PACKET 3

#define ETHARP_SEND_ARP_PACKET 1
#define ETHARP_RECE_ARP_PACKET 2
#define ETHARP_ADD_ARP_ENTRY   3
#define ETHARP_DEL_ARP_ENTRY   4




/* ��Ʒ��Ҫ��������ARP������ */
#define SPECIAL_ARP_PROXY_ACTIVE    0x01
/* ��Ʒ����Ҫ��������ARP������ */
#define SPECIAL_ARP_PROXY_INACTIVE  0x02

#define DYNA_ARP_ENTRY     0 /*�ҵ���̬ARP����*/
#define STATIC_ARP_ENTRY   1 /*�ҵ���̬ARP����*/
#define NO_ARP_ENTRY       2 /*û���ҵ�ARP����*/


#define ETH_IF_POSITION_UP     0 /*��̫�ӿ�λ�ã��䵱�ϲ�*/
#define ETH_IF_POSITION_LINK   2 /*��̫�ӿ�λ�ã��䵱��·��*/
#define ETH_IF_POSITION_DEV    3 /*��̫�ӿ�λ�ã��䵱�豸��*/

/* xiehuaguo add for support np 2006-05-08 */
#define     ETHARP_DEFAULT_VLINK_INDEX     0/*�Ƿ�VLINK����ֵ*/
#define ETHARP_CONFLICT_WARNING(pNode, WFlag, IfIndex) \
{ \
    pNode->ucSArpConflict = WFlag; \
    if (TCPIP_HA_AMB == TCPIP_HA_GetBoardType()) \
    { \
        ETH_SARPCONFLICT_PARAM_S stArpConflict = {0}; \
        stArpConflict.ulIfIndex = IfIndex; \
        stArpConflict.ulVrfID = pNode->ulVrfIndex; \
        stArpConflict.ulIPAddr = pNode->ulRtIpAddr; \
        stArpConflict.ucAlmSt = WFlag; \
        (VOID)TCPIP_Mem_Copy(stArpConflict.szMacAddr, MACADDRLEN, pNode->ucMacAddr, MACADDRLEN); \
        TCPIP_WarningOut(WARNING_ARP_CONFLICT, (VOID *)&stArpConflict); \
    } \
}

/**********************************
����Ϊ�½ӿڹ���͵�ַ����������
**********************************/
#define ETH_IF_GetIfByIndex g_pstCoreIFNETFunTable->pfIF_GetIfByIndex
#define ETH_IF_GetMainIf g_pstCoreIFNETFunTable->pfIF_GetMainIf
#define ETH_IF_GETMTSOFT IF_GETMTSOFT
#define ETH_IF_GETINDEXBYIF IF_GETINDEXBYIF
#define ETH_IF_GetIfByIndex_XY IF_GetIfByIndex_XY
#define ETH_IP_Eth_IsValidIpAddr g_pstCoreAM4FunTable->pfIP_Eth_IsValidIpAddr
#define ETH_IF_SearchIfFromChain g_pstCoreIFNETFunTable->pfIF_SearchIfFromChain
#define ETH_IF_GETLINKTYPE IF_GETLINKTYPE
#define ETH_IP_IF_HaveIpAddr g_pstCoreAM4FunTable->pfIP_IF_HaveIpAddr
#define ETH_IP_IF_MaxIpAddr g_pstCoreAM4FunTable->pfIP_IF_MaxIpAddr
#define ETH_IP_IF_IsThisIfIpAddr g_pstCoreAM4FunTable->pfIP_IF_IsThisIfIpAddr
#define ETH_IP_ArpProxy_IsValidIpAddr g_pstCoreAM4FunTable->pfIP_ArpProxy_IsValidIpAddr
/* ��ѯָ���ĵ�ַ�Ƿ�ͽӿ��ϵĵ�ַ������ͬ���� */
#define ETH_IP_IF_IsSameNet g_pstCoreAM4FunTable->pfIP_IF_IsSameNet
/* End of addition */

#define ETH_IP_IsLocalIfAddr g_pstCoreAM4FunTable->pfIP_IsLocalIfAddr
#define ETH_IP_IsBroadcast g_pstCoreAM4FunTable->pfIP_IsBroadcast

/* Added by likaikun213099, ��ַ��ͻ�澯����, 2014/10/24 */
#define ETH_IP_SetIpConflictFlag   g_pstCoreAM4FunTable->pfIP_SetIpConflictFlag
#define ETH_IP_ClearIpConflictFlag g_pstCoreAM4FunTable->pfIP_ClearIpConflictFlag
/* End of Added by likaikun213099, 2014/10/24 */

extern ULONG IP_Eth_IsValidIpAddr( IFNET_S *pstIfNet, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, USHORT usOpType);
extern IFNET_S * IF_SearchIfFromChain( IFNET_S * pIf , ULONG ulSearch );

#define ETHARP_INPUT 0
#define ETHARP_OUTPUT 1

#define ETHARP_MAX_IP_CONFLICT_ITEM         8  /* ��ͻ��ַ�����*/
#define ETHARP_MAX_IP_MAC_ITEM              4  /* һ����ͻIP��Ӧphysical��ַ�����*/
#define ETHARP_IP_CONFLICT_DETECT_TIMEOUT   10 /* ��ͻ��ⶨʱ��TimeOutʱ�� */
#define ETHARP_IP_CONFLICT_UPDATE_TIMEOUT   10 /* ��ͻ���¶�ʱ��TimeOutʱ�� */
#define ETHARP_STATE_CONFLICT               1  /* ��ͻ״̬ */
#define ETHARP_STATE_WAITFORREPLY           2  /* �ȴ��ظ�״̬ */
#define ETHARP_IP_CONFLICT_NOT_FOUND        0xffff
#define ETHARP_IPCONFLICTITEM_ADD_SUCC      2  /* IP��ͻ������ӳɹ� */
#define ETHARP_IPCONFLICTITEM_REF_SUCC      3  /* IP��ͻ����ˢ�³ɹ� */
#define ETHARP_CONFLICTIP_IS_NOEXIT         0  /* �����еĳ�ͻIP������ */
#define ETHARP_CONFLICTIP_IS_EXIT           1  /* �����еĳ�ͻIP���� */

/* ʹ��VLANIF����󣬶�ͬһ����ַ������Ӧ���ARP������� */
#define ETHARP_MAX_COUNT_TOREPLY        64

/* ��ַ��ͻ���� */
typedef struct tagMacFlagItem
{
    UCHAR  ucMac[6];        /*���ַ��ͻ��Ӧ��physical��ַ*/
    UCHAR  ucFlag;          /*��ַphysical��ַȷ���ĳ�ͻ��ĳ�ͻ��־ ETHARP_STATE_CONFLICT, ETHARP_STATE_WAITFORREPLY */
    UCHAR  ucTimeCount;     /*��ʱ�� ��λs */
}ETHARP_MAC_Flag_Item_S;  
typedef struct tagIpConflictItem
{
    ULONG ulIPConflictType; /*��ͻ�ĵ�ַ����:ETHIP(1);OMIP(2)*/
    ULONG ulIfIndex;        /*��ͻ��IfIndex*/    
    ULONG ulIpAddr;         /*��ͻ��ַ*/
    ULONG ulMacNum;         /*ͬһ����ͻ��ַ��Ӧ��ͻphysical��ַ����*/
    ETHARP_MAC_Flag_Item_S stMacFlagItem[ETHARP_MAX_IP_MAC_ITEM] ;/*һ����ַ���Լ��4�������ͻ��physical��ַ*/
    ULONG ulVrfIndex;
}ETHARP_IP_CONFLICT_ITEM_S;

typedef struct tagIpSendFreeArpNode
{
    SLL_NODE_S stSllNode;
    ULONG ulIfIndex;
    ULONG ulIpAddr;
    ULONG ulCount;
    ULONG ulOutTimes;
}ETHARP_IPSENDFREEARPNODE_S;

#pragma    pack(1)

typedef  struct  tagDOT1QHDR
{
    UCHAR     aucDestAddr[6];/* Destination physical address */
    UCHAR     aucSrcAddr[6]; /* Source physical address */
    USHORT    usTPID;        /* 802.1q Protype 8100 */
    USHORT    usTCI;         /*user User_priority CFI VLANID */
    USHORT    usLenEtype;    /* Length or the type field */
}ETHARP_VLAN_DOT1QHDR_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* ARP������Ϣ�ṹ */
typedef struct tagETHARP_RESOLVE_FAILED
{
    ULONG       ulIfIndex;              /* �ӿ����� */
    ULONG       ulIpAddr;               /* ��ַ */
    TCPIP_TIME_S stResolveFailedTime;  /* ����ʧ��ʱ�� */
}ETHARP_RESOLVE_FAILED_S;

/* ARP����ʧ�ܼ�¼������� */
#define ETHARP_MAX_RESOVLEFILED    8   

/* ARP����ʧ�ܼ�¼�ṹ */
typedef struct tagETHARP_RESOLVE_RECORD
{
    ETHARP_RESOLVE_FAILED_S g_stArpResloveFailed[ETHARP_MAX_RESOVLEFILED];    /* ARP����ʧ����Ϣ��¼�� */
    ULONG          ulArpRecordCount;                                          /* ����ʧ�ܴ��� */
}ETHARP_RESOLVE_RECORD_S;

/*��¼ARP����ʧ����Ϣ*/
#define ETHARP_ARP_RESOVLEFAIL_NOTE(ul_ArpIfIndex,ul_ArpIpAddr)\
{\
    ULONG ii = g_stEtharpResolveRecord.ulArpRecordCount;\
    ETHARP_RESOLVE_FAILED_S *pstArpResolveFailed = NULL;\
    ii %= ETHARP_MAX_RESOVLEFILED;\
    pstArpResolveFailed = &g_stEtharpResolveRecord.g_stArpResloveFailed[ii];\
    (VOID)TCPIP_Get_CurrentTime(&pstArpResolveFailed->stResolveFailedTime);\
    pstArpResolveFailed->ulIfIndex = ul_ArpIfIndex;\
    pstArpResolveFailed->ulIpAddr = ul_ArpIpAddr;\
    g_stEtharpResolveRecord.ulArpRecordCount++;\
}

/* ETHARP���Ĵ�����(��������) */
typedef struct tagEtharpIntermediateDeal
{
    ULONG ulPriority;
    ETHARP_INTERMEDIATE_HOOK_FUNC pfEtharpDealHookFunc;  /* The Registered Function Pointer */
    struct tagEtharpIntermediateDeal *pstNext;
}ETHARP_INTERMEDIATE_DEAL_HOOK_S;

/* MAC��Ϣ�ڵ� */
typedef struct tagMACNode
{
    ULONG  ulPktCount;           /* һ��ʱ�����յ���MAC�ļ��� */
    ULONG  ulTimeCount;          /* ��ʱ���� */
    UCHAR  ucMac[MACADDRLEN];    /* physical��ַ */
    UCHAR  ucPadding[2];         /* ���λ */ 
}MAC_NODE_S;

/* ��̬�������ڵ� */
typedef struct tagArpBlackNode
{
    ULONG                  ulPktCount;           /* һ��ʱ�����յ���MAC�ļ��� */
    ULONG                  ulBlakNodeTimeOut;    /* �������ڵ��ϻ�ʱ��� */
    UCHAR                  ucMac[MACADDRLEN];
    UCHAR                  ucPadding[2];
    struct tagArpBlackNode *pstPreNode;
    struct tagArpBlackNode *pstNextNode;
}BLACK_NODE_S;

/* ��̬������ͷ�ڵ� */
typedef struct tagArpGuardBlackNodeHead
{
    BLACK_NODE_S            *pstNodeList; 
    BLACK_NODE_S            *pstNodeListTail;   /*����ָ������β����ָ�� */
    ULONG                   ulNodeNum;
}ARP_GUARD_BLACK_HEAD;

/* ARPǱ�ڹ����߽ڵ� */
typedef struct tagArpGuardAttackNode
{
    struct tagArpGuardAttackNode *pstPreNode;     /* ǰһ�������� */
    struct tagArpGuardAttackNode *pstNextNode;    /* ��һ�������� */
    MAC_NODE_S                    stAttackNode;   /* ��ǰ��������Ϣ,ֻʹ��ulPktCount��ucMac�ֶ�,��ʹ�ó�ʱ�ֶ�ulTimeCount */
}ARP_GUARD_ATTACK_NODE_S;

/* ARPǱ�ڹ���������ͷ�ڵ� */
typedef struct tagArpGuardAttackHead
{
    ULONG                   ulNodeNum;             /* ��ǰ��Ǳ�ڹ����߸��� */
    ARP_GUARD_ATTACK_NODE_S *pstNodeList;          /* Ǳ�ڹ���������ͷ */
}ARP_GUARD_ATTACK_HEAD_S;

/* ARP����ƭ�ڵ���Ϣ */
typedef struct tagArpGuardNode
{
    ULONG ulIpAddr;                                 /* ��ַ */
    ETHARP_ARPRTENTRY_S     *pstArpEntry;           /* ARP��� */
    ARP_GUARD_BLACK_HEAD    stBlackListHead;        /* ��̬������ͷ�ڵ�,��̬�������ڵ��ڴ���Ҫ��̬�����ͷ� */
    MAC_NODE_S              stCurNode;              /* ��ǰ�ڵ���Ϣ,���һ���յ���ARP������Ϣ,
                                                       ֻʹ��ulTimeCount��ucMac�ֶ�,��ʹ��ulPktCount�ֶ� */
    struct tagArpGuardNode  *pstPreNode;
    struct tagArpGuardNode  *pstNextNode;
    UCHAR                   ucNodeState;            /* ARP����ƭ�ڵ��״̬,���κͷ�����״̬ */
    UCHAR                   ucWarningFlag;          /* �澯��־,1��ʾ�Ѿ��ϱ��澯��0��ʾ�ָ��澯 */
    UCHAR                   ucAttackWarningFlag;    /* ARP�����澯��־,1��ʾ�Ѿ��ϱ��澯��0��ʾ��ǰ�޸澯 */
    UCHAR                   ucPadd;                 /* �����ֶ� */
    MAC_NODE_S              stTrustNode;            /* ��ŵ�ǰ������MAC��Ϣ,ֻʹ��ulPktCount,ulTimeCount��ucMac�ֶ�.
                                                       ���νڵ�ulTimeCount�ڴ���Ǳ�ڹ�����ʱ,1�붨ʱ����ʱ1�ξ͵���,
                                                       ��ʾ���Է���ARP���ĵĴ���.ulPktCount��ʾ�յ�������MAC��Ӧ��ARP���ļ���. */
    ARP_GUARD_ATTACK_HEAD_S stAttackListHead;       /* Ǳ�ڹ�����ͷ�ڵ�,Ǳ�ڹ����߽ڵ��ڴ���Ҫ��̬�����ͷ� */   
    ULONG                   ulAttackCount;          /* ��������,��ͼ�ı�MAC�Ĵ��� */
    ULONG                   ulAttackWarningTimeOut; /* �����澯�ļ������1����, �����Ǹ澯���ĳ�ʱ������� */
    MAC_NODE_S              stAttackMaxWaningNode;  /* ������������Ǳ�ڹ�������Ϣ,���ڸ澯�ϱ�*/
    ARP_GUARD_ATTACK_HEAD_S stWarningAttackListHead;      /* 60��澯�ڼ乥���߼�¼����*/   

}ARP_GUARD_NODE_S;

/* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-01. �޸�ԭ��: libС�ͻ�,֧��ARP����ƭ���ܿɲü� */
typedef struct tagETHARP_GUARD_PROC_HOOK
{
    VOID (*pfARP_Guard_FreeNode)(ARP_GUARD_NODE_S *pstGuardNode);
    VOID (*pfARP_Guard_Update)(ARP_GUARD_NODE_S *pstGuardNode, UCHAR *pszMac);
    ULONG (*pfARP_Guard_SearchDynamicBlackMac)(ARP_GUARD_NODE_S *pstGuardNode, UCHAR *pszMac);
    VOID (*pfARP_Guard_NewNode)(ETHARP_ARPRTENTRY_S *pstArpEntry, ULONG ulIpAddr, UCHAR *pszMac);
    ULONG (*pfARP_Guard_SearchStaticBlackMac)(ULONG ulIpAddr, ULONG ulVrfIndex, UCHAR *pszMac);

    ULONG (*pfARPGUARD_HA_BatchBackup)(VOID);
    ULONG (*pfARPGUARD_HA_RealTimePack)(USHORT usType, UCHAR * pucData, USHORT usInBufLen);
    ULONG (*pfARPGUARD_HA_Input)(UCHAR *pucBuf, ULONG ulMsgLen);
    VOID  (*pfARPGUARD_HA_DebugOutPut)(UCHAR *pBuf, ULONG ulMsgLen, ULONG ulCmd);
    ULONG (*pfARPGUARD_HA_Smooth)(VOID);
    ULONG (*pfARPGUARD_HA_Clean)(VOID);
    ULONG (*pfARP_Guard_GetSwitch)(ULONG *pulValue);
    ULONG  (*pfARP_Guard_BlackList_Is_Full)(ARP_GUARD_NODE_S *pstGuardNode);
    ULONG  (*pfARP_Guard_Is_Trust)(ARP_GUARD_NODE_S *pstGuardNode);
}ETHARP_GUARD_PROC_HOOK_S;

#pragma    pack( 1 )

/* ��VLAN��SNAP��̫ͷ */
typedef struct tagETHSNAPHDR_WITHVLAN
{
    UCHAR  ucHdrDstMacAddr[6];     /*Ŀ��physical��ַ*/ 
    UCHAR  ucHdrSrcMacAddr[6];     /*Դphysical��ַ  */
    USHORT  usVlanEthtype;                   /*0x8100*/
    USHORT  usVlanTag;               /* vlan��ǩ */
    USHORT usLen;                  /* Э�����ͳ����ֶ�    */
    UCHAR  ucDSAP;                 /* destination service access point*/
    UCHAR  ucSSAP;                 /* source service access point */
    UCHAR  ucCtrl;                 /* control domain */
    UCHAR  ucORI[3];                              
    USHORT usType;
}ETHSNAPHDR_WITHVLAN_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Begin Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. �޸�ԭ��: ֧��VLAN���ò�һ�µĸ澯 */
/* ������Ϣ */
typedef struct tagETHARP_PKT_INFO
{                                
    USHORT usType;  /* ��������,IP,ARP�� */
    USHORT usRes;   /* �����ֶ� */
    ULONG  ulSrcIp; /* ARP�����е�ԴIP,������.ֻ��ARP������Ч */
    ULONG  ulDstIp; /* ARP�����е�Ŀ��IP,������.ֻ��ARP������Ч */
}ETHARP_PKT_INFO_S;
/* End Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. �޸�ԭ��: ֧��VLAN���ò�һ�µĸ澯 */


#define ETHARP_ARP_QUE_MIN_PKTS_ONETIME     40 /*ARP����һ�δ����ARP���ĸ�����Сֵ*/

/* Begin: Added by a00900892 on 2014-10-16, for AR-IP-MCCP.007 */
/* Support maximum of 8 response to GARP with Conflictiong IP. */
#define ETHARP_MAX_CONFLICT_RESP    8

/* Structure to store details of conflicted incoming GARP. */
typedef struct tagArpConflictTime
{
    ULONG ulSecHigh;        /* Dynamic ARP entries timestamp higher 4 bytes */ 
    ULONG ulSecLow;         /* Dynamic ARP entries timestamp lower 4 bytes */ 
    ULONG ulIpAddr;         /* Conflicting address */
    ULONG ulVrfIndex;       /* Attached Vrf Index */
} ARP_CONFLICT_TIME_S;
/* End: Added by a00900892 on 2014-10-16, for AR-IP-MCCP.007 */

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _ETHARP_H_ */

