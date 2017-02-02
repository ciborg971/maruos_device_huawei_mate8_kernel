
#include  "if_def.h"
#include "tcpip/ifnet/include/ifnet_api.h"

#ifndef _IF_IIFNET_INC_H_
#define _IF_IIFNET_INC_H_

#ifdef  __cplusplus
extern "C"{
#endif


/************************************************************************
 *                             ������ʼ(Begin)                          *
 * ......           ����Ϊ�������֣���Ʒ�����޸�  luohanjun       ......*
 * ......              (ע��: ֻ�ܴ�������������֮���޸�)         ......*
 * ......                                                         ......*
 ************************************************************************/

#define MAX_IFCMD_NAME_LEN                     47
#define MAX_INTERFACE_SIMPLENAME_LEN           20       /* ���ļ򵥽ӿ������� */

#define IF_MAX_INDEX                           100000   /* ���Ľӿ���Ŀ */


/***********************************************************************/
/*usIfState value: ����������ȷ*/
#define  IF_UP                 0x01
#define  IF_DOWN               0x02
#define  IF_SETMAC             0x04
#define  IF_UNBIND             0x08
#define  IF_STATES             IF_UP | IF_DOWN
#define  OSI_UP                0x10    /*��OSICPЭ�̳ɹ���֪ͨ��Ʒ�ӿ�״̬���UP (������·��ģ��ʹ��)*/
#define  OSI_DOWN              0x20    /*��OSICPЭ��ʧ�ܣ�֪ͨ��Ʒ�ӿ�״̬���DOWN (������·��ģ��ʹ��)*/

/* #endif */ /* VRP_MODULE_RTPRO_RM */

#ifndef FORWARDIFENTRY
#define FORWARDIFENTRY
#endif

#ifndef EXTENDIFENTRY
#define EXTENDIFENTRY
#endif

typedef ULONG (* ENQUEUE_PF)(MBUF_S *);
typedef ULONG (*IF_PRETREATFUN)(ULONG ulIfindex);
typedef VOID  (*pfReceiverNotifyFun)(MBUF_S *,ULONG );

/*
typedef struct tagIFNET;
typedef struct VLINKSTATUS_S;
*/

/*�����ӿ�����
DECLARE_INTERFACE (IIF_IFS_IntFun) //�ⲿ���IFNET�����ӿ�
{
    IUNKNOWN_METHODS
    //���������������ݣ�����ʼ��
    METHOD_(ULONG , pfIF_InitIF) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
    //�������㣬����UP�¼���ִ�и��������buildrun��ͨ�����ƺ��������¼����ݵȲ��������Բ�ִ���κβ�����
    METHOD_(ULONG , pfIF_BuildrunIF) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);
    //�ӿ��������Σ���Ҫ�������·�㣬����������ṩ�պ�����
    METHOD_(ULONG , pfIF_HideCommand) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);
    //�ͷ�ָ������ƿ顣
    METHOD_(ULONG , pfIF_FreeControlBlock) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

};
*/

#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20
#endif

#ifndef DHCP4C_DOMAINNAME_SIZE
#define DHCP4C_DOMAINNAME_SIZE DNS_DOMAIN_LIST_NAME_LENGTH
#endif

#ifndef DHCP4C_DNSIP_NUM
#define DHCP4C_DNSIP_NUM 6
#endif

#ifndef DHCP4C_ROUTER_NUM
#define DHCP4C_ROUTER_NUM 8
#endif

typedef struct tagPPP_VLINK_INFO
{
    ULONG ulIfIndex;
    ULONG ulLocalIp;
    ULONG ulRemoteIp;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];
    ULONG ulFlag;
    ULONG ulVlinkIndex;
    ULONG ulMtu;
}PPP_VLINK_INFO_S;

typedef struct tagDHCP4C_VIRTUAL_INFO
{
    ULONG ulIfIndex;
    ULONG ulDHCPClientIP;
    ULONG ulDHCPClientIPMask;
    ULONG aulDNSIP[DHCP4C_DNSIP_NUM];
    ULONG aulGatewayIP[DHCP4C_ROUTER_NUM];
    ULONG ulFlag;
    UCHAR ucDomainName[DHCP4C_DOMAINNAME_SIZE];
}DHCP4C_VIRTUAL_INFO_S;

/**********************************************************
Ϊ��������ģ�� ��
�벻Ҫ�Ķ������ڽṹ���������ֶ�
***********************************************************/
typedef struct tagIFNET
{

    /* ����Ϊ�����ӿڵĻ����ṹ */
    /* �ӿ������ӿ��������ۺ��ڴ���IFNETʱ���� */
    CHAR  if_szIfName[ IF_MAX_INTERFACE_NAME_LEN+1];
    CHAR  if_szDescript[ MAX_INTERFACE_DESCRIPTION_LEN+1 ]; /* �ӿ������ַ��� */
    UCHAR ucPadding_1[3];

    /* if_ulIfIndex�ֶθ����ֵĺ���
     *         6bit                19bit                  4bit               3bit
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-
     * +    �ۺ�(Slot)    |      ƫ��(IndexOff)     |  ͬ����(SynFlag) | ����(Type) +
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-
     *                                                �ӿ�ÿ��ɾ��һ�Σ�  �ӿ�����
     *                                                    ��ֵ��1
     */
    ULONG if_ulIfIndex;             /* VISP˽�������ṹ */
    ULONG if_ulProductIfIndex;      /* ���Ʒ��صĽӿ����� */

    ULONG if_ulSlotNum;         /* ��16λΪ���ţ���16λΪ�ۺ� */
    ULONG if_ulTopIfIndex;      /* �ýӿڵ����ø��׵����� */
    ULONG if_ulNetIfIndex;      /* �ýӿڵ��������Ը��׵����� */

    /* �������ƿ� */
    UINTPTR if_ulIpIf;              /* IP���ƿ� */
    UINTPTR if_ulIpv6If;            /* IPv6 Control Block */
    ULONG if_ulIsisFlag ;     /* �ӿ���ISISʹ�ܱ�־ */

    /* �˿����� */
    ULONG if_ulSpoofing;       /* Spoofing ��ʶ��1��ʾ���� spoofing ����, 0��ʾ������������� */
    /*
     * &IF_MOVING      ��ʾ�ö˿ڿɱ�ɾ��
     * &IF_TEMPIF      ��ʱ�ӿڱ�־
     * &IF_NOCONFIG    �ӿڲ�������
     * &IF_INVISIBLE   �ӿڲ�����ʾ( ������ʾ�ӿ���Ϣ )
     * ȱʡ״̬�� ����ɾ��������ʱ�ӿڡ��ɼ���������
     */
    ULONG if_ulMoving;
    ULONG if_ulShutdown;            /* shutdown��ʶ,&IF_SHUTDOWN�ǿձ�ʾִ����shutdown����������û��ִ�� */
    ULONG if_ulSubIndex;            /*  0 ��ʾ���ӽӿڣ���0 ��ʾ�ӽӿ�(�ӽӿڱ��) */
    ULONG if_ulSubIfNum;            /*  �ýӿ������õ��ӽӿ��� */
    ULONG if_ulLineProtocol;        /* �˿ڷ�װ����·��Э�� */
    ULONG if_ulLineEncapsulation;   /* �˿ڷ�װ����·���װDTE����DCE,�Լ�֧�ֵ�Э��*/
    /* ULONG Basic_if_ulProtocolType;   ��װ����·��Э����ϸ */
    ULONG if_ulLineStatus;          /* �˿�Э��״̬, 1 ΪUP, 2ΪDOWN*/

    /* �˿�����״̬�������ӽӿ���˵�������ӿ�״̬ */
    /* ʹ����OAM-3ah���ܺ󣬽ӿڵ�����״̬ȡ���ڵײ�״̬��OAM״̬�ĵ���
        ����ײ�DOWN����ӿ�����״̬ΪDOWN��
        ����ײ�UP����3ah����EFMNORMAL��EFMUP��ӿ�����״̬ΪUP������ΪDOWN��
    */
    ULONG if_ulPhyStatus;

    ULONG if_ulLine6Status; /* �˿�Э��״̬, 1 ΪUP, 0ΪDOWN*/
    ULONG if_ulPhyType;             /* �˿ڵ��������� */
    ULONG if_ulPortType;            /* �˿ڵ����� */
    /* ��������·��ģ����ص���Ϣ */
    ULONG if_ulBaud;        /* �˿ڵĲ����� */
    ULONG if_ulMTU;         /* �˿ڵ�MTU */
    ULONG if_ulCfgMTU;      /* Э�����ɵ�MTU */
    ULONG if_ulFlags;       /* P-P��NBMA��Broadcast ,  ��ʾ�ӿڵ�·������ */
    ULONG if_ulSubType;     /* P-P��MP ,  ��ʾ�ӽӿڵ����� */
    ULONG if_ulKeepAlive;   /* ��·��Э���ú���·��̽����·״̬�� */
    USHORT if_usLinkUpDownTrapEnable; /* �ӿ�UP/DOWNʱ����trap���ĵĿ��� */
    
    /* Add by zhaoyue00171897/shuxieliu00176784, at 2011-06-04. �޸�ԭ��: ֧��VLAN���ò�һ�µĸ澯 */
    USHORT usVlanWarningFlag;         /* Vlan һ���Ը澯����,����ֵ,0��ʾû��ʹ�ܸù���,��0��ʾ���ӿ���ʹ�ܸù��ܵ��ӽӿ��� */

    ULONG if_ulPassive ;              /* �ӿڵ�PASSIVE����,�Է�ֹ·��й© */
    ULONG if_ulLastChange ;           /* �ӿ���һ�β���״̬�ı��ʱ�� */
    /*
     * ��·����ƿ飬�����µ���·��Э��ʱ�������µ�Э����ƿ�
     * ʹ�ú궨��ʵ����·��Э��Ŀɲü���
     * ʵ��ֻ��һ����·����ƿ�
     */
    UINTPTR if_ulLinkLink;    /*  ��·����ƿ�ָ��,��CE1�б���ʱ϶ռ�ñ�ʾ����*/
    UINTPTR if_ulLogicLink;   /* added by zhouxiaoniu 2001-01-17 */

    /* IFNET�����˽ṹ�����ⲻ�ɼ� */
    struct tagIFNET* if_pFather;            /* ��ͨ��ָ��ͨ����ָ��*/
    struct tagIFNET* if_pSon;               /* ��ͨ��ָ���һ����ͨ����ָ�� */
    struct tagIFNET* if_pBrother;           /* ��ͨ��ָ����һ���ֵܵ�ָ��*/
    struct tagIFNET* if_pMain;              /* �ӽӿ�ָ�����ӿڵ�ָ��*/
    struct tagIFNET* if_pSub;               /* ���ӿ�ָ���һ���ӽӿڵ�ָ�� */
    struct tagIFNET* if_pConfig;            /* ָ����һ�������õĽӿڵ�ָ�� */
    /* ע�ắ��ָ�� */
    /*
     * �ϲ�ģ�飨IPIF_Output()������IPXIF_Output()���������ͱ���ʹ�õĺ���
     * ����Ϊָ������͵ı��ĵ�ָ��
     */
    ULONG (*if_pfOutput)(MBUF_S *);

    /*
     * ��·��Э����IFNET��ע��Ľ����ݴ��͸���·��ķ��ͺ���
     * ����Ϊָ������͵ı��ĵ�ָ��
     */
    ULONG (*if_pfLLCOutput)(MBUF_S *);

    /*
     * ��·����IFNET��ע��Ĺ��ϲ�ʹ�õ����п��ƺ���
     * ��һ������Ϊָ��IFNET��ָ��
     * �ڶ�������Ϊ�ϲ㴫�ݸ���·��Ŀ���������
     * ����������Ϊ�������ݣ�����·����ݿ��������ֽ��н���
     */
    ULONG (*if_pfLinkDownIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /*
     * �ϲ��ṩ����·������ϴ��ݿ�����Ϣ�ĺ���
     * ��һ������Ϊ�ϲ�Э���ʶ
     * �ڶ�������Ϊָ��IFNET��ָ��
     * ����������Ϊ��·�㴫�ݸ��ϲ�Ŀ���������
     * ���ĸ�����Ϊ�������ݣ����ϲ������������ֽ��н���
     */
    ULONG (*if_pfUpIOCtl)(ULONG,struct tagIFNET *,ULONG,CHAR *);

    /*
     * IFNET�ṩ�Ļ�������·�����ϴ��ݿ�����Ϣ�ĺ���
     * ��һ������Ϊ�ϲ�Э���ʶ
     * �ڶ�������Ϊָ��IFNET��ָ��
     * ����������Ϊ��·�㴫�ݸ��ϲ�Ŀ���������
     * ���ĸ�����Ϊ�������ݣ����ϲ������������ֽ��н���
     */
    ULONG (*if_pfLinkUpIOCtl)(ULONG,struct tagIFNET *,ULONG,CHAR *);

    /*
    * IFNET֪ͨ·�ɹ���ģ��ӿ�UP/DOWN�ĺ���
    * һ������£��ú�����·�ɹ���ģ�鸺��ע��
    * BackUpģ��ע���Լ��ĺ�����ʵ�������л����ԵĽӿ�UP/DOWN���ƹ���
    * ��һ������Ϊָ��IFNET��ָ��
    * �ڶ�������Ϊ�ӿ�UP/DOWN����Ϣ������
    * ����������Ϊ��������
    */
    ULONG (*if_pfNotifyRouter)(struct tagIFNET *, ULONG, UINTPTR);

    /*
     * IFNETע��Ĵ���shutdown����ĺ���
     * ��һ������Ϊָ��shutdown�������õ�IFNET��ָ��
     */
    ULONG (*if_pfShutdown)(struct tagIFNET *);

    /*
     * IFNETע��Ĵ���no shutdown����ĺ���
     * ��һ������Ϊָ��no shutdown�������õ�IFNET��ָ��
     */
    ULONG (*if_pfNoShutdown)(struct tagIFNET *);

    /*
     * IFNETע���ɾ���ӿ����ݽṹ�ĺ���
    ** ��һ������Ϊָ��ɾ���������õ�IFNET��ָ��
    */
    ULONG (*if_pfDelete)(struct tagIFNET *);

/* ����Ϊת������ */
#ifdef FORWARDIFENTRY

    VOID * if_pstNatpt;

    ULONG if_ulMaxFrag;                     /* �ײ������͵�����ķ�Ƭ�� */
    MBUF_QUEUE_S if_stFIFOQueue;            /* ���ƽ̨��֧��QOSӵ�����ƣ�����FIFO���нṹȡ���� */

    UINTPTR if_ulCryptMapOut;                 /* enc �����Կ��ƿ� */

    void    * if_pToken;


    /* ���Դ���������Ӧ�����оٵ����� */
    /* �ⲿ�����ݽṹ�ǿ�ѡ��*/
    /* ��ʹ��ע����IFNET�ϵ����Դ�����������ֱ��ʹ�þ���ĺ��� */
    /* �ɾ��������ģ���ʹ�����Ե�ģ��Э�̾��� */
    /* �ӿڹ���ģ�鲻��ͳһ�涨 */
    /* ������������*/

#endif /*FORWARDIFENTRY*/

/* ����Ϊ��չ���� */
#ifdef EXTENDIFENTRY
    /*
    ISDN��������
    ����CC��Q921��Q931ͬʱ����
    */
    /*VRPV3R001M07_IFNET_XHZ_BEG for R.FUNC.IFNET.010 ����pri-groupʱ϶����ӿ�*/
    /*#if ( VRP_MODULE_LINK_ISDN == VRP_YES || VRP_IFNET_ISDN_PRI == VRP_YES )*/
    UINTPTR if_ulUserInfo;            /*�ӿڱ����������Ϣ��*/
    /*#endif  VRP_MODULE_LINK_ISDN */
    /*VRPV3R001M07_IFNET_XHZ_END for R.FUNC.IFNET.010 ����pri-groupʱ϶����ӿ� #endif VRP_MODULE_LINK_ISDN */

    /* �������ƿ飬����û�еײ���ƿ�Ķ˿ڿ��Գ���������ָ�� */
    UINTPTR if_ulPhyLink;             /* �ײ���ƿ�ָ�� */

    ULONG if_ulLoopBack;    /* Ϊ֧��IPv6����D21ͬ�� */

    /* PPPoE Server���ƿ� */
    UINTPTR if_ulPPPOE ;
    /* ע�ắ��ָ�� */

    /* �ײ�ʹ�øú������ϲ㴫�ݱ��� */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊָ����յı��ĵ�ָ�� */
    ENQUEUE_PF (* if_pfReceived)(struct tagIFNET *,MBUF_S *);

    /* ��·��Э����IFNET��ע��Ľ��պ������ӵײ㣩 */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊָ����յı��ĵ�ָ�� */
    ENQUEUE_PF (* if_pfLinkReceived)(struct tagIFNET *,MBUF_S *);

    /* Qos��IFNET��ע��Ĺ��ײ���õ�TransmitDone���� */
    /* ֻ��LAPB���������·��Э����Ҫר�Ŵ��� */
    /* ��������·��Э�齫����Ϊ�� */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊָ��ײ���ƿ��ָ��  */
    /* ����������Ϊָ������͵ı��ĵ�ָ�� */
    ULONG (*if_pfQosTransmitDone)(struct tagIFNET*,UINTPTR, MBUF_S *);

    /* Qos��IFNET��ע��Ĺ���·��ʹ�õķ��ͺ�����������ӵ������ */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊָ��ײ���ƿ��ָ��  */
    /* ����������Ϊָ������͵ı��ĵ�ָ�� */
    ULONG (*if_pfQosTransmit)(struct tagIFNET*, UINTPTR, MBUF_S *);

    /* �ײ���IFNET��ע��Ĺ���·��ʹ�õķ��ͺ�����������ӵ������ */
    /* ��һ������Ϊָ��ײ���ƿ��ָ�� */
    /* �ڶ�������Ϊָ������͵ı��ĵ�ָ�� */
    ULONG (*if_pfPhyTransmit)(UINTPTR,MBUF_S *);

    /* �ײ���IFNET��ע��Ĺ��ϲ�ʹ�õ����̿��ƺ��� */
    /* ��һ������Ϊָ���������ƿ��ָ�� */
    /* �ڶ�������Ϊ���ݸ��ײ�Ŀ��������� */
    /* ����������Ϊ�������ݣ��ɵײ���ݿ��������ֽ��н��� */
    ULONG (*if_pfPhyIOCtl)(UINTPTR, ULONG, CHAR *);

    /* IFNET�ṩ�Ĺ��ײ�ʹ�õ���·�����̿��ƺ��� */
    /* IFNET����ʹ�øú���ð��ײ�����·�㷢�Ϳ�����Ϣ */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊ�ײ㴫�ݸ���·��Ŀ��������� */
    /* ����������Ϊ�������ݣ�����·����ݿ��������ֽ��н��� */
    ULONG (*if_pfLinkIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /* ��·����IFNET��ע��Ĺ��ײ�ʹ�õ����̿��ƺ��� */
    /* IFNET����ʹ�øú���ð��ײ�����·�㷢�Ϳ�����Ϣ */
    /* ��һ������Ϊָ��IFNET��ָ�� */
    /* �ڶ�������Ϊ�ײ㴫�ݸ���·��Ŀ��������� */
    /* ����������Ϊ�������ݣ�����·����ݿ��������ֽ��н��� */
    ULONG (*if_pfLLCIOCtl)(struct tagIFNET *,ULONG,CHAR *);

    /* �ṩ��LINEģ����жϸ�����IFNET�Ƿ����л���ָ����װ�ĺ��� */
    /* ������Dialer Group���첽com�ڲ������л���SLIPЭ�� */
    /* ��һ������Ϊָ��IFNET�ṹ��ָ�� */
    /* �ڶ�������Ϊָ���ķ�װ */
    ULONG (*if_pfIsIfSupportEncap)(struct tagIFNET *,ULONG);

/* ��̫����PPPOE֮�䴫�ݿ������̵ĺ���ָ�� */
    ULONG (*if_pfPPPOEIOCtl)(UINTPTR, ULONG, CHAR *);

    /* Add Begin: by Chenxia, 2002/10/18, for QoS transplant */
    ULONG if_ulVAInfo;           /* ��¼VT�ӿڵ�ǰ�VA������(���8λ)�����ڵĲ�λ(��24λ)*/

    ULONG if_ulBandWidth;       /* ��¼�ӿ�ȱʡ��bandwidth, ���ڽӿڳ�ʼ��ʱ�Ĳ����� */
    ULONG if_ulCfgBandWidth;    /* ��¼�ӿ����õ�bandwidth, ����������, ��ֵΪ0 */
    /* Add End */

    UINTPTR if_pMultilinkInterface;  /* MP��ͨ���ϼ�¼�ĸ�ͨ��Mp-Group�ӿ���ָ�� */

    ULONG if_ulSAstatus; /*��־ͬ�첽com�ڵ�ͬ��/�첽״̬*/

#endif /*EXTENDIFENTRY*/


    /* Ϊ��������ģ����ݣ�������������ֶΡ� */

    ULONG if_ulType;          /* �ӿ����� for VISP add by luohanjun 2004/03/24 */

    /* IFNET֪ͨ·�ɹ���ģ��ӿ�UP/DOWN�ĺ��� */
    ULONG (*if_pfNotifyRouter6)(struct tagIFNET *, ULONG, UINTPTR);/* add by luohanjun 2004-04-08*/

    /* ULONG (*if_pfVLINKIOCtl)(struct VLINKSTATUS_S * , VOID *);*/ /*add by luohanjun for VLINK*/

    ULONG if_ulBaudHigh  ;

    VOID* Forward_if_pstSec ;

    UINTPTR pQueueInfo;    /*ָ��QoS���ƿ飬NULL��ʾû��ʹ��QoS.*/
    ULONG ulHAflag ; /*HA��ǣ�ȡֵ�����������ߵ����
                     # define  IFNET_BAK_NO_RECOVER   0x01  �ӿ�δ�ڲ�ƽ��
                     # define  IFNET_BAK_CHECK_OVER  0x02 �ӿ����ⲿƽ��
                     */
    ULONG if_ulIfNum;           /*  �ӿں� */

    PPP_VLINK_INFO_S *pstPppVlink;
    DHCP4C_VIRTUAL_INFO_S *pstDhcpcInfo;

    /* Qos��IFNET��ע��Ĺ��ײ���õ�TransmitDone���� */
    /* ֻ��LAPB���������·��Э����Ҫר�Ŵ��� */
    /* ��������·��Э�齫����Ϊ�� */
    /* ��һ������ΪIFNET�ӿ����� */
    /* �ڶ�������Ϊָ��ײ���ƿ��ָ��  */
    /* ����������Ϊָ������͵ı��ĵ�ָ�� */
    ULONG (*if_pfQosTransmitDoneByIndex)(ULONG,UINTPTR, MBUF_S *);

    /* Qos��IFNET��ע��Ĺ���·��ʹ�õķ��ͺ�����������ӵ������ */
    /* ��һ������ΪIFNET�ӿ����� */
    /* �ڶ�������Ϊָ��ײ���ƿ��ָ��  */
    /* ����������Ϊָ������͵ı��ĵ�ָ�� */
    ULONG (*if_pfQosTransmitByIndex)(ULONG, UINTPTR, MBUF_S *);

    /* L2IF��չ */
    ULONG  if_ulL2OrL3;      /* �ӿڵĶ��������Ա��: SWITCHPORT_L3IF/SWITCHPORT_L2IF_PORT/SWITCHPORT_L2IF_TRUNKPORT */
    ULONG  if_ulL2ifPortIndex;  /* SWITCHPORT_L2IF_PORT����ӿڱ����PORT��Ϣ�������� */
    ULONG  if_ulDuplexStatus;   /* �ӿ�ȫ˫��/��˫������״̬,�ɵײ��ϱ�,ֻ��ETH��Ч.ȡֵPHY_DUPLEX_EN */

    /* vrrp��չ */
    UINTPTR  if_ulStandbyPointer; /* ָ��ýӿ��µĵ�һ��vrrp������ */

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
    VOID  *if_ulVrfIfListNode;
    /*Begin: adding VRF6 index for VRF6 support*/
    ULONG if_ulVrf6Index;
    /*End: adding VRF6 index for VRF6 support*/
    VOID  *if_ulVrf6IfListNode;

    /* VISP1.8.1 ֧��1AG��׼Э�鿪��*/
    UCHAR if_uc1agVersion; /* 0:Draft7�汾;1:��׼�汾 */
    UCHAR if_uc1agNpVersion; /* 0:Draft7�汾;1:��׼�汾 */
    /* Added for ֧�ֽ��ղ���VLANͷ��1AG����2009-05-14 */
    USHORT if_us1agRcvDefaultVlan;

    ULONG if_ul1agMultiCount;
    ULONG ulHost6RtReserved;  /*IPV6��������·�ɱ�� ��IPV4�Ѿ���IP
                             ���ƿ��У���IPV6���ƿ���IR����*/
    ULONG ulMacChangeFlag;   /* physical��ַ�ı���*/     

    /* Added by likaikun00213099 for multi MAs with same VLAN at 20140910 */
    VOID *pst1agMepListOnIf;
    /* End of Added by likaikun00213099 for multi MAs with same VLAN at 20140910 */
#if (TCPIP_MODULE_MINI == VRP_YES)
    IN6ADDR_S ia6_stAddr;
    ULONG ia6_ulPrefixLength;
    ULONG ip6if_ulMtu;
    UCHAR ucIpv6EnableFlag;
    UCHAR ucReserved[3];
#endif        
}IFNET_S, *PIFNET_S;


typedef struct  tagIFMsgHdr
{
    USHORT  usMsgID;                /* ��ϢID */
    USHORT  usMsgType;              /* ��Ϣ���� */
    USHORT  usSerialNum;
    USHORT  usMsgMode;              /* ��Ϣģʽ */
    USHORT  usSlot;                 /* �ۺ� */
    USHORT  usData;                 /* ���� */
    ULONG   ulIfIndex;              /* �ӿ����� */
    /*VRPV3R001M07_IFNET_XHZ_BEG base on 8060V100R001M01B01D003_021209*/
    /* ULONG   ulBriSonIfIndex[2]; */
    /*VRPV3R001M07_IFNET_XHZ_END */
    ULONG   ulProductIndex;
    ULONG   ulData;                 /* ���� */
    ULONG   ulLen;                  /* ��Ϣ���� */
    ULONG   ulSubType;              /* �ӽӿ����� */

    struct tagIFMsgHdr*     pNext;
}IFMSGHDR_S;            /* message header 32 bytes */


/* #define IF_DEFAULT_IF                           (&gstDefaultIf) */
extern IFNET_S *IF_GetIfByIndex(ULONG ulIfIndex);
extern ULONG IF_IsTrunkPort(IFNET_S* pIf);

#define IF_NULL(m_pstIf)                (NULL == (m_pstIf))
#define IF_GETSLOT(ulIf)                (IF_GetSlotByIndex(ulIf))

/* ���к�������� */
/*
#define IF_GETNAME(ulIf)                (IF_GetIfByIndex(ulIf)->if_szIfName)
#define IF_GETLINKTYPE(ulIf)            (IF_GetIfByIndex(ulIf)->if_ulPortType)
#define IF_GETLINKPTR(ulIf)             (IF_GetIfByIndex(ulIf)->if_ulLinkLink)
#define IF_GETLINKPTRBYINDEX(ulIf)      (IF_GetIfByIndex(ulIf)->if_ulLinkLink) */

#define IF_GETNAME(ulIf)            (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_szIfName : "\0")
#define IF_GETLINKTYPE(ulIf)        (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulPortType : PORT_MAX)
#define IF_GETLINKPTR(ulIf)         (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulLinkLink : NULL)
#define IF_GETLINKPTRBYINDEX(ulIf)  (IF_GetIfByIndex(ulIf) ? IF_GetIfByIndex(ulIf)->if_ulLinkLink : NULL)

/* ���к��޵ط�����,ɾ�� */
/* #define IF_GETLINKPROTO(ulIf)           (IF_GetIfByIndex(ulIf)->if_ulLineProtocol)
#define IF_GETPHYTYPE(ulIf)             (IF_GetIfByIndex(ulIf)->if_ulPhyType)
#define IF_GETSHUTDOWN(ulIf)            (IF_GetIfByIndex(ulIf)->if_ulShutdown)*/


#define IF_GETLINKPTRBYIF(pIf)          ((pIf)->if_ulLinkLink)


/*------------------------------------------------------
   �ӿ��������ṹ�����ڷ����ӿ����ַ����Ĺ���
-------------------------------------------------------*/
typedef struct tagIFNAME
{
    CHAR    if_pName[MAX_IF_NAME_LENGTH+1];   /* save the real ifnet name */
    VOID*   if_pClass;                        /* IFNET�ڲ��ֶ� (��Ӧ�Ľӿ���ָ�룬��VAʱΪ��Ӧ�����ӿ���) */
    CHAR    if_pMainName[MAX_IF_NAME_LENGTH+1];/* ���ӿ����� */
    ULONG   if_pOp[IFNET_MAX_IFNAME_INDEX];   /* the part of the name, max is 6 */
    ULONG   if_ulIndex;                       /* the number of the part */
    ULONG   if_ulColon;                       /* ��ͨ����־ */
    ULONG   if_ulSub;                         /* �ӽӿڱ�־ */
}IFNAME_S, *PIFNAME_S;

/*------------------------------------------------------
   �ӿ������ṹ
-------------------------------------------------------*/
typedef struct tagIFIndex
{
    USHORT usSynFlag;       /* �������ṹ��Ӧ��ͬ���� */
    UCHAR  ucPadding[2];
    IFNET_S *if_pIf;        /* ָ��ýӿ�������Ӧ�Ľӿ����ݽṹ��ָ�� */
}IFINDEX_S;

typedef struct tag_IF_INFO_S
{
    ULONG   ulIndex ;       /* �ӿ�ָ������ */
    ULONG   ulLanguage ;    /* ��ǰ����ģʽ */
    CHAR    *pInfo ;         /* ��Ϣ������ */
    ULONG   ulSize ;         /* ��������С */
}IF_INFO_S ;

typedef struct tagIF_WAITLIST_PARAM
{
    UINTPTR   ulWaitListHandle;       /* WAITLIST��� */
    ULONG   ulSearchType ;          /* �������� */
    VOID    *pSearch ;                      /* ���ָ�� */
}IF_WAITLIST_PARAM ;

typedef struct tagIFCreate              /* create a single ifnet */
{
    IFMSGHDR_S      stMsgHdr;
    CHAR    if_pName[VRP_INTERFACE_NAME_LENGTH];
    ULONG   if_ulShutDown;
    ULONG   if_ulLineProto;
}IF_CREATE_S;

typedef struct  tagIFMIB
{
    USHORT  usTableType;    /* ������ */
    UCHAR   ucPadding[2];
    ULONG   ulTableAddr;   /* ��ṹ��ַ,�ֱ��Ÿ�����ṹ���׵�ַ */
}IFMIB_S;

typedef struct tagIFHotInsert           /* create a single ifnet */
{
    IFMSGHDR_S      stMsgHdr;
    ULONG    ulCfgMTU;
    ULONG    ulIsisFlag;
    ULONG    ulProtoLimit;
    /* Add Begin: by Chenxia, 2002/10/18, for QoS transplant */
    ULONG    ulCfgBandWidth;   /*bandwidth-threshold*/
    /* Add End*/
    CHAR     if_pName[VRP_INTERFACE_NAME_LENGTH];
}IF_HOT_INSERT_S;

#define COMMON_MSG \
    IFNET_S *  pIf;    \
    ULONG ulHandle;    \
                       \
    DULONG   dulInPkts;  \
    DULONG   dulOutPkts; \
    DULONG   dulInBytes; \
    DULONG   dulOutBytes;\
    DULONG   dulInDrops; \
    DULONG   dulOutDrops;\
                       \
    ULONG   ulLastInBytes;\
    ULONG   ulLastInPkts;\
    ULONG   ulLastOutBytes;\
    ULONG   ulLastOutPkts;\
                          \
    ULONG   ulInByteRate; \
    ULONG   ulOutByteRate;\
    ULONG   ulInPacketRate;\
    ULONG   ulOutPacketRate;\
                            \
    ULONG   ulPhyType

typedef struct tagCommonIfPhyMsg
{
    COMMON_MSG;

} COMMON_PHY_MSG;


/*
�豸���ṹ
*/
/*-------------------------
���ڽ��нӿڷ����������ṹ
----------------------------*/
typedef struct tagAnalVector
{
    ULONG   if_ulMaxEntry;                  /* ���ɷ������Ŀ */
    ULONG   if_ulAlloced[2];                /* ���ڲ�ͬ����ʽ�������Ŀ */
    ULONG   if_ulLower;                     /* ����������Ŀ */
    ULONG   if_ulUpper;                     /* ����������Ŀ */
    ULONG   if_ulHelpIndex;                 /* �ӿ������İ�����Ϣ */
    ULONG   * if_pSymbol[2];                /* ��һ��ķ��ű� */
    ULONG   if_ulProperty;                  /* �ӿڵı�־λ */

    /* ��һ������slot/card/interface������ʽ,�ڶ�������slot/card/interface:timeslot������ʽ
     �ӽӿ�slot/card/interface.subport���õڶ�������Ŀǰ֧����ͨ����Dialer\VT�ڲ�֧���ӽӿ�*/
    struct tagAnalVector    **if_pIndex[2];
}IF_ANAL_VECTOR_S,*PIF_ANAL_VECTOR_S;


/***************************************************************************************/
/********ע������ĺ���Ϊ�˼����ϵ�ģ�飬��ģ�鲻Ҫʹ��! *****/
/***************************************************************************************/
extern ULONG gulIfnetLineProtocol[8];
/* �ӿڹ����ṩ��IPģ�� */
#define IF_IS_InLOOPBACK(pIf)            ((pIf != NULL) && (pIf->if_ulPhyType == PHY_LOOP))

/* ������IFNET����������ֵ��0������LoopBack�ӿڻ�����InLoopBack�ӿ� */
#define IF_IS_LOOPBACK(m_ulIndex)        ((gulIfnetLineProtocol[(m_ulIndex) & 0x00000007]) == PORT_LOOP)
#define IF_GETIPCTLBLK(m_pIf)            ((m_pIf)->if_ulIpIf)    /* ������IFNETָ�룬����ֵ�ǽӿڵ�IP���ƿ�ָ�� */
#define IF_GETIPv6CTLBLK(m_pIf)          ((m_pIf)->if_ulIpv6If)  /* ������IFNETָ�룬����ֵ�ǽӿڵ�IPv6���ƿ�ָ�� */
#define IF_IS_InNull(pIf)                ((pIf != NULL) && (pIf->if_ulPhyType == PHY_NULL))

#define IF_IS_InVI(pIf)                  ((pIf != NULL) && (pIf->if_ulPhyType == PHY_VI))

#define IF_IS_InUI(pIf)                  ((pIf != NULL) && (pIf->if_ulPhyType == PHY_UI))

#define IF_IS_MTUNNEL(pIf)       ((pIf != NULL) && (pIf->if_ulPortType == PORT_MTUNNEL))

#define IF_IS_VLANIF(pIf)                ((pIf != NULL) && (pIf->if_ulPortType == PORT_VLAN))
#define IF_IS_ETHTRUNKIF(pIf)            ((pIf != NULL) && (pIf->if_ulPortType == PORT_ETH_TRUNK))
#define IF_IS_IPTRUNKIF(pIf)             ((pIf != NULL) && (pIf->if_ulPortType == PORT_IP_TRUNK))

/* ����pstIfNet�ǽӿ�ָ�룬pstIpCtlBlk��IP���ƿ�ָ�룬��IP���ƿ�ָ�����õ��ӿ��� */
#define IF_SETIPCTLBLK(m_pIf,pstIpCtlBlk)    (((m_pIf)->if_ulIpIf) = (UINTPTR)pstIpCtlBlk)

/* ����pstIfNet�ǽӿ�ָ�룬pstIpv6CtlBlk��IPv6���ƿ�ָ�룬��IPv6���ƿ�ָ�����õ��ӿ��� */
#define IF_SETIPv6CTLBLK(m_pIf,pstIpv6CtlBlk)    (((m_pIf)->if_ulIpv6If) = (UINTPTR)pstIpv6CtlBlk)

/* �û���֤�ӿ�ָ���׼ȷ�ԡ����룺�ӿ�ָ�룬����ֵ�ǽӿ����� */
#define IF_GETINDEXBYIF(pIf)                 ((pIf)->if_ulIfIndex)
#define IF_GETTOPIF(pIf)                     (IF_GetIfByIndex((pIf)->if_ulTopIfIndex))
#define IF_GETMTU(pIf)                       ((pIf)->if_ulMTU)

#define IF_SETMTU(pIf,ulMTU) \
{\
    if ((pIf)->if_ulMTU >= (ulMTU))\
    {\
        (pIf)->if_ulMTU = (ulMTU);\
    }\
}

#define IF_GETCFGMTU(pIf)                    ((pIf)->if_ulCfgMTU)
#define IF_SETCFGMTU(pIf,ulMTU)              ((pIf)->if_ulCfgMTU = ulMTU)
#define IF_SETMTSOFT(pIf, pMTSoft)          (((pIf)->if_ulLinkLink) = (UINTPTR)pMTSoft)
#define IF_GETMTSOFT(pIf)                    ((pIf)->if_ulLinkLink)
#define IF_ISBROADCAST(pIf)                  ((pIf)->if_ulFlags & IF_RTATTR_BROADCAST)

/*���Ӽ���ʽ�Ȳ�κͿ��Ȳ����Ŀ   pengjimei for DEV_HOTCTL 2002/12/13
#define IF_GETSLOTBYPTR(pIf)     ((pIf)->if_ulSlotNum & 0xffff)*/

/*
#if (VRP_CENTERALIZATION == VRP_YES)
#define IF_GETSLOTBYPTR(pIf)                           (getSelfBoardId())
#else
*/
#define IF_GETSLOTBYPTR(pIf)                  ((pIf)->if_ulSlotNum & 0xffff)
/*
#endif
*/
/*end*/

#define IF_GETIFTYPE(pIf)                     ((pIf)->if_ulType)

#define IF_SLOT2IPCNODE(m_ulSlot)            (m_ulSlot)
#define IF_IPCNODE2SLOT(m_ulNode)            (m_ulNode)     /* m_ulNode MUST NOT BE ZERO */
#define IF_GETLOOPBACKNAME()                 "InLoopBack0"
#define IF_GETIFNAMEBYIF(pIf)                (pIf->if_szIfName)

#define IF_ISVALIDINDEX(m_ulIndex) \
{\
    if((m_ulIndex) != IF_GetIfByIndex(m_ulIndex)->if_ulIfIndex) \
    {\
        VOS_DBGASSERT(0);\
    }\
}

#define IF_ISVALIDIF(m_pIf)\
{\
    if((m_pIf) != IF_GetIfByIndex((m_pIf)->if_ulIfIndex))\
    {\
        VOS_DBGASSERT(0);\
    }\
}

#define IF_IS_SHUTDOWN(pIf)  ((pIf)->if_ulShutdown & IF_SHUTDOWN)
#define IF_IS_NOPHY_SHUTDOWN(pIf) ((pIf)->if_ulShutdown & IF_NO_PHY_SHUTDOWN)
#define IF_IS_SUBIF(pIf)     ((pIf)->if_ulSubIndex)

/* #define MACADDRLEN       6 */      /*physical��ַ����*/

/* Added bu zk36377. */
#define IF_GetIfByIndex_XY( pstIfNet, ulIfIndex )  ((pstIfNet)= IF_GetIfByIndex(ulIfIndex))

extern ULONG g_ulFirstDimension;
extern ULONG g_ulSecondDimension;
extern ULONG g_ulIfnetPre3D;

#define IF_GET_FIRST_DIM(pIf) (pIf->if_ulSlotNum) & 0x0000ffff
#define IF_GET_SECOND_DIM(pIf) (pIf->if_ulSlotNum >> 16) & 0x0000ffff
#define IF_GET_THIRD_DIM(pIf) (pIf->if_ulIfNum)

extern ULONG IF_Is_3Dim();
extern ULONG IF_Is_Distribute_3Dim();
extern ULONG IF_Is_Central_3Dim();

/* �ж��Ƿ񱾰�ӿ� */
#define IF_IS_ThisBoard(pIf)  ((pIf != NULL)\
                              &&((!IF_Is_3Dim())\
                                ||( IF_Is_Central_3Dim())\
                                ||((IF_Is_Distribute_3Dim())\
                                    &&(((pIf->if_ulSlotNum)&0x0000ffff) == g_ulFirstDimension )\
                                    &&(((pIf->if_ulSlotNum >>16)&0x0000ffff) == g_ulSecondDimension)\
                                   )\
                                 )\
                               )

/* �·��ײ�NP LCP ECHO���ݽṹ */
typedef struct tagPPPNPLCPECHO
{
    ULONG  ulGotMagicNum;             /* ����MAGIC NUMBER */
    ULONG  ulHisMagicNum;             /* �Զ�MAGIC NUMBER */
    ULONG  ulKeepAlive;               /* ���ͱ����Ƶ��,��λ�� */
    USHORT usLoopBackNum;             /* �ж��Ի����� */
    UCHAR  ucPacketID;                /* ��ʼ������ID */
    UCHAR  ucPppDownNum;              /* ����û���յ��Զ˻�ӦPPP�����Ĵ���,Down��������· */
    UCHAR  szEchoReq[12];             /*PPP LCP Echo������*/
}PPPNPLCPECHO_S;


#ifdef  __cplusplus
}
#endif

#endif  /* end of _IF_PUB_H_ */


