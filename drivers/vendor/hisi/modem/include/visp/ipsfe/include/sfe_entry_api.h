

#ifndef _SFE_ENTRY_API_H_
#define _SFE_ENTRY_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* �����淵��ֵȫ��Ψһ��ģ����������λ��� */
typedef enum enumSfeGlobalRetCode
{
    SFE_ENTRY_BEGIN_RET_CODE = 1000,           /* ENTRYģ���������ʼֵ */
    SFE_DEBUG_BEGIN_RET_CODE = 2000,           /* DEBUGģ���������ʼֵ */
    SFE_MBUF_BEGIN_RET_CODE = 3000,            /* MBUFģ���������ʼֵ */
    SFE_POOL_BEGIN_RET_CODE = 4000,            /* POOLģ���������ʼֵ */
    SFE_ARP_BEGIN_RET_CODE = 5000,             /* ARPģ���������ʼֵ */
    SFE_ROUTE_BEGIN_RET_CODE = 6000,           /* ROUTEģ���������ʼֵ */
    SFE_IF_BEGIN_RET_CODE = 7000,              /* IF�ӿ�ģ���������ʼֵ */
    SFE_ETH_BEGIN_RET_CODE = 8000,             /* ETHģ���������ʼֵ */
    SFE_COM_BEGIN_RET_CODE = 9000,             /* MSG��ϢͨѶģ���������ʼֵ */
    SFE_BFD_BEGIN_RET_CODE = 10000,            /* BFD��ϢͨѶģ���������ʼֵ */
    SFE_FAKEREASS_BEGIN_RET_CODE = 11000,      /* ������ģ���������ʼֵ */
    SFE_REASS_BEGIN_RET_CODE = 12000,          /* ������ģ���������ʼֵ */
    SFE_ICMP_BEGIN_RET_CODE = 13000,           /* ICMPģ���������ʼֵ */
    SFE_IPFWD_BEGIN_RET_CODE = 14000,          /* IPģ���������ʼֵ */
    SFE_PUB_BEGIN_RET_CODE = 15000,            /* PUB����ģ���������ʼֵ */
    SFE_TCP_BEGIN_RET_CODE = 16000,            /* TCPģ���������ʼֵ */
    SFE_UDP_BEGIN_RET_CODE = 17000,            /* UDPģ���������ʼֵ */
    SFE_SOCK_BEGIN_RET_CODE = 18000,           /* socketģ���������ʼֵ */
    SFE_ADDR_BEGIN_RET_CODE = 19000,           /* ADDRģ���������ʼֵ */
    SFE_DRV_BEGIN_RET_CODE  = 20000,           /* DRIVERģ���������ʼֵ */

    SFE_STUB_RET_CODE = 0x0fffffff             /* ֧�ֿɲü�ͳһ���صĴ�����. */
}SFE_GLOBAL_RET_CODE_E;

/* ������ENTRYģ������붨�� */
typedef enum enumSfeEntryErrCode
{
    SFE_ENTRY_OK = SFE_OK,                      /* �����ɹ� */
    SFE_ENTRY_ERR_BEGIN = SFE_ENTRY_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_ENTRY_CREATE_SPINLOCK_FAIL,             /* 1  ����������ʧ�� */
    SFE_ENTRY_GET_SPINLOCK_FAIL,                /* 2  ��ȡ������ʧ�� */
    SFE_ENTRY_VCPU_ALREADY_INIT_SETPRECFG,      /* 3  ����Ԥ������ʱVCPU �Ѿ���ʼ�� */
    SFE_ENTRY_MALLOC_MEMORY_FAIL_PRECFGVAR,     /* 4  ��ʼ��ʱ����Ԥ���ù������ʧ�� */
    SFE_ENTRY_ADD_SHARE_DB_FAIL_PRECFGVAR,      /* 5  ��ʼ��ʱԤ���ù���������빲�����ֿ�ʧ�� */
    SFE_ENTRY_NULL_POINTER_GETPRECFG,           /* 6  ��ȡԤ������ʱ�������Ϊ��ָ�� */
    SFE_ENTRY_NO_PRE_VALUE_SETPRECFG,           /* 7  ����Ԥ������ʱû��Ԥ������ */
    SFE_ENTRY_NO_PRE_VALUE_GETPRECFG,           /* 8  ��ȡԤ������ʱû��Ԥ������ */
    SFE_ENTRY_PARA_INVALID_SETPRECFG,           /* 9  ����Ԥ������ʱ�������Ϸ� */
    SFE_ENTRY_GET_VRF_PRECONFIG_FAIL,           /* 10 ��ȡVRFԤ������ʧ�� */
    SFE_ENTRY_VCPU_ALREADY_INIT_SETSHAREMEMID,  /* 11 ���ù����ڴ������ʱVCPU�Ѿ���ʼ�� */
    SFE_ENTRY_NULL_POINTER_GETSHAREMEMID,       /* 12 ��ȡ�����ڴ������ʱ�������Ϊ��ָ�� */
    SFE_ENTRY_GET_SFE_VCPU_MAX_NUM_PRECFG_FAIL, /* 13 ��ȡ���VCPU����Ԥ����ֵʧ�� */
    SFE_ENTRY_GET_SFE_ALIGN_LEN_PRECFG_FAIL,    /* 14 ��ȡ������Դ��ʱʹ�õ��ֽڶ���ֵԤ����ֵʧ�� */
    SFE_ENTRY_GET_SFE_IP_OPTION_PROCESS_MODE_PRECFG_FAIL,/* 15 ��ȡ������IPѡ���ʽԤ����ֵʧ�� */
    SFE_ENTRY_GET_SFE_VLAN_PKT_PROCESS_MODE_PRECFG_FAIL, /* 16 ��ȡ������VLAN���Ĵ���ʽԤ����ֵʧ�� */
    SFE_ENTRY_GET_SFE_PKT_FAST_PATH_PROCESS_PRECFG_FAIL, /* 17 ��ȡ�����汨�Ľ��տ�ͨ������Ԥ����ֵʧ�� */
    SFE_ENTRY_CREATE_SEMA_FAIL,                          /* 18  �����ź���ʧ�� */  
}SFE_ENTRY_ERR_CODE_E;

/************************************************************
 * ��VCPUĬ�ϵ�������Ԥ���������ֵ
 * - - -
 * ע�⣬����/����Ԥ������ʱ�����¼�����ͬ���޸�:
 * (1)ö�ٶ���SFE_PRECONFIG_INFO_E
 * (2)Ԥ���ó�ʼֵg_stSFE_ComPara
 ************************************************************/
typedef enum SFE_PRECONFIG_INFO_Etag
{
    /* ͬ��ͬ�������LoopBack���� */
    SFE_MAX_LOOPBACK_PORT_NUM,

    /* ���п�������LoopBack���� */
    SFE_MAX_TOTAL_LOOPBACK_PORT_NUM,

    /* ͬ��ͬ���������̫������ */
    SFE_MAX_ETH_PORT_NUM,

    /* ���п���������̫������ */
    SFE_MAX_TOTAL_ETH_PORT_NUM,

    /* ���VRF����,ʵ�������VRF���������ø�����1,Ŀ����Ϊ����������Ԥ������屣��һ��. */
    SFE_MAX_VRF_NUM,

    /* ���·������ */
    SFE_MAX_ROUTE_NUM,

    /* ���ƽ��·������ */
    SFE_MAX_BALANCE_ROUTE_NUM,

    /* ����ѽ���ARP�������� */
    SFE_MAX_ARP_RESOLVED_NUM,

    /* ��������ARP�������� */
    SFE_MAX_ARP_RESOLVING_NUM,

    /* ���ARP�������ڵ㻺�汨�ĸ��� */
    SFE_MAX_ARP_CACHE_PACKET_NUM,

    /* ϵͳ���������ڵ��ܸ���,һ���ڵ㻺��һ�����ķ�Ƭ����,Ŀǰ�����Ƭ���ĵ�������Ϊ2����ϵͳ����ļ�����ڵ���� */
    SFE_NET_FAKE_REASS_MAX_NUM,

    /* ������ڵ㳬ʱʱ��,��λ���� */
    SFE_NET_FAKE_REASSNODE_TIMEOUT,

    /* ϵͳ����������ڵ��ܸ���,һ���ڵ㻺��һ�����ķ�Ƭ����,Ŀǰ�����Ƭ���ĵ�������Ϊ2����ϵͳ�����������ڵ���� */
    SFE_NET_REASS_MAX_NUM,

    /* ������ڵ㳬ʱʱ��,��λ���� */
    SFE_NET_REASSNODE_TIMEOUT,

    /* ���BFD�Ự���� */
    SFE_MAX_BFD_SESSION_NUM,

    /* BFD�����Ự����ģʽ,ȡֵ��Χ[0,1],0��ʾ�����Ự����ģʽ,1��ʾ�����Ự���⴦��ģʽ,Ĭ��ֵΪ0(����������ģʽ) */
    SFE_BFD_SINGLE_HOP_PROC_MODE,

    /* ��ͳ��֧�ֵ������������ */
    SFE_FLOW_STATISTIC_MAX_FLOW_NUM,

    /* ��ϻ��������ڴ��С */
    SFE_BOX_SIZE,

    /*Maximum number of rules for whitelist*/
    SFE_FW_WLS_MAX_RULE,

    /*Maximum number of rules for blacklist*/
    SFE_FW_BLS_MAX_RULE,

    /*Maximum number of interface based attack rules*/
    SFE_FW_AD_IF_CFG_MAX_RULE,

    /*Maximum number flood based atrack rules*/
    SFE_FW_AD_FLOOD_CFG_MAX_RULE,

    /*Maximum number interface indexes binding with acl group*/
    SFE_FW_ACLFW_MAX_IFINDEX,

    /*Maximum memory usage for acl rfc*/
    SFE_FW_ACL_RFC_MAX_MEM_USE,

    /*To enable/disable mac based acl filter*/
    SFE_FW_ENABLE_MAC_BASE_ACL_FILTER,

    /* ��չMBUF�ṹ���СԤ����,Ĭ��ֵΪ0,Ϊ�˼���ԭ��RPU��Ʒ������Ӧ��;
       Ԥ����Ϊ0:��32λϵͳ��MBUF�ṹ���С�̶�Ϊ160�ֽ�,DBD�ṹ���С�̶�Ϊ32�ֽڱ��ֲ���;
       Ԥ����Ϊ1:MBUF�ṹ���С��DBD�ṹ���Сû������,��64λϵͳ��,MBUF�ṹ���С�仯,��Ʒ����Ԥ����Ϊ1 */
    SFE_MBUF_EXPEND_SIZE,

    /* MBUF��ʼ��Դ�ش�С,ָ����MBUF�����������ں�̬ģ�����ʱָ���ĸ���һ�� */
    SFE_MBUF_POOL_INIT_NUM,

    /* ���socket���� */
    SFE_SOCKET_MAX_NUM,

    /* ���TCP���ƿ�����,һ��TCP socket��Ӧһ��TCP���ƿ� */
    SFE_TCP_MAX_NUM,

    /* ���VCPU���� */
    SFE_MAX_VCPU_NUM,

    /* ������Դ��ʱʹ�õ��ֽڶ���ֵ,ָ�����뷽ʽ�������ں�̬ģ�����ʱָ���Ķ��뷽ʽһ��,�����Ʒֱ����0,Ĭ��ֵΪ0��ʾ��Ȼ����. */
    SFE_ALIGN_BYTE_NUM,

    /* TCP�Ƿ�֧��rfc1323��ʱ����ʹ�����������ѡ�� */
    SFE_TCP_DORFC1323_FLAG,

    /* ������IPѡ���ʽ */
    SFE_IP_OPTION_PROCESS_MODE,

    /* ������VLAN���Ĵ���ʽ */
    SFE_VLAN_PKT_PROCESS_MODE,

    /* ���IP ADDR���� */
    SFE_IPADDR_MAX_NUM,

    /* ÿ���ӿ�����ַ��Ŀ */
    SFE_IPADDR_MAX_NUM_PER_IF,

    /* TCP���ű��ʱ�����ܿ��� */
    SFE_TCP_REORDER_KEEPALIVE_TIMER_SWITCH,

    /* TCP���ŵ����������ظ������ģ */
    SFE_TCP_REORDER_REASS_CACHE_NUM,

    /* �����ӿڹ���֧�ֹ�������ӿ��� */
    SFE_DRV_INTF_MNG_MAX_NUM,

    /* ��������һ�δ��ں˽��յ�����ĸ��� */
    SFE_DRV_ONCE_RCV_PKT_NUM,

    /* ��������һ�����ں˷��͵�����ĸ��� */
    SFE_DRV_ONCE_SND_PKT_NUM,

    /* �������ں˷��ͱ��ĵĳ�ʱʱ��,�����ĸ�������һ�����ں˷��͵ĸ���ʱ,��ʱʱ�б���Ҳ�ᷢ�� */
    SFE_DRV_ONCE_SND_PKT_TIMEOUT,

    /* �����汨�Ŀ�ͨ������ */
    SFE_PKT_FAST_PATH_PROCESS,

    /* TCP֧��У��ͼ��ı�־ */
    SFE_TCP_CKSUM_FLAG,

    /* UDP֧��У��ͼ��ı�־ */
    SFE_UDP_CKSUM_FLAG,

    /* TCP���ջ����ȡ���Ƿ����������ڸ����Ż� */
    SFE_TCP_UPDATEWND_FLAG,

    /* TCP�յ����Ĳ������ݳ����Ƿ�����ͨ��0�����Ż� */    
    SFE_TCP_UPDATE_ZEROWND_FLAG,    

    /* ����TCP MSL�ϻ�ʱ�� */
    SFE_TCP_MSL_TIME,

    /* TCP�ӳ�ACK���ܿ���*/
    SFE_TCP_DELAYED_ACK_SWITCH,

    /* ö�ٱ߽�ֵ,����Ԥ������ʱ�����ڴ�֮ǰ���� */
    SFE_MAX_COM_PARA_NUM,
}SFE_PRECONFIG_INFO_E;

/* ���VRF����Ԥ��������ֵ,��VRFԤ���õ���Сֵ��1��Ϊ0,��ʾֻ��1��vrf,�������Խ�Լ�����ڴ���Դ. */
#define SFE_MAX_VRF_NUM_LOWLIMIT 0
/* ���VRF����Ԥ��������ֵ */
/* 2012-12-04 ������ҵVPN����VRF���Ϊ200����������Ϊ256 */
#define SFE_MAX_VRF_NUM_UPLIMIT 256
/* ���VRF����Ԥ����Ĭ��ֵ */
#define SFE_MAX_VRF_NUM_DEFAULT 200

/* MBUF�ṹ���С�̶�(32λ����),MBUF�ṹ���С�̶�Ϊ160�ֽ�,DBD�ṹ���С�̶�Ϊ32�ֽ�,DB��С�̶�Ϊ1600�ֽ�,���ֲ���; */
#define SFE_MBUF_EXPAND_SIZE_DISABLE 0
/* MBUF�ṹ���С����,MBUF,DB��С����,DBD��С��32λ�����̶�Ϊ32�ֽ�. */
#define SFE_MBUF_EXPAND_SIZE_ENABLE 1

/* �����治֧�ֽ��մ���VLAN���� */
#define SFE_VLAN_PKT_NOT_SUPPORT_MODE 0
/* ��������ֱ�Ӻ���VLANͷ�ķ�ʽ֧�ֽ���VLAN���� */
#define SFE_VLAN_PKT_IGNORE_VLAN_MODE 1

/* �����治֧�ֽ��մ����IPѡ��ı��� */
#define SFE_IP_OPTION_NOT_SUPPORT_MODE 0
/* ��������ֱ�Ӻ���IPѡ��ķ�ʽ֧�ֽ��մ�IPѡ��� */
#define SFE_IP_OPTION_IGNORE_OPRION_MODE 1

/* �����治֧�ֽ�RFC1323�涨�Ĵ������ź�ʱ���ѡ�� */
#define SFE_TCP_DORFC1323_NOT_SUPPORT 0
/* ������֧�ֽ�RFC1323�涨�Ĵ������ź�ʱ���ѡ�� */
#define SFE_TCP_DORFC1323_SUPPORT 1

/* ����TCP���ű��ʱ������ */
#define SFE_TCP_REORDER_KEEPALIVE_TIMER_DISABLE 0
/* ��TCP���ű��ʱ������ */
#define SFE_TCP_REORDER_KEEPALIVE_TIMER_ENABLE 1

/* ������Ĭ��֧�ֵ������ӿ������� */
#define SFE_DRV_INTF_DEFAULT_NUM    10
/* ��������������֧�ֵ������ӿ���С���� */
#define SFE_DRV_INTF_MIN_NUM    1
/* ��������������֧�ֵ������ӿ������� */
#define SFE_DRV_INTF_MAX_NUM    50

/* ��������һ�δ��ں˽��յ�Ĭ�ϱ��ĸ��� */
#define SFE_DRV_ONCE_RCV_PKT_DEFAULT_NUM    1
/* ��������һ�δ��ں˽��յ���С���ĸ��� */
#define SFE_DRV_ONCE_RCV_PKT_MIN_NUM        1
/* ��������һ�δ��ں˽��յ�����ĸ���,
   ��ֵ����OSԼ�������ֵ������������,����Ҫ֪��OS�㿽��ģ���޸� */
#define SFE_DRV_ONCE_RCV_PKT_MAX_NUM        500

/* ��������һ�δ����ں˷��͵�Ĭ�ϱ��ĸ��� */
#define SFE_DRV_ONCE_SND_PKT_DEFAULT_NUM    1
/* ��������һ�����ں˷��͵���С���ĸ��� */
#define SFE_DRV_ONCE_SND_PKT_MIN_NUM        1
/* ��������һ�����ں˷��͵�����ĸ���,
   ��ֵ����OSԼ�������ֵ������������,����Ҫ֪��OS�㿽��ģ���޸� */
#define SFE_DRV_ONCE_SND_PKT_MAX_NUM        500

/* �������ں˷��ͱ��ĵĳ�ʱʱ��Ĭ��ֵ,��λ���� */
#define SFE_DRV_ONCE_SND_TIMEOUT_DEFAULT    100
/* �������ں˷��ͱ��ĵĳ�ʱʱ����Сֵ,��λ���� */
#define SFE_DRV_ONCE_SND_TIMEOUT_MIN        10
/* �������ں˷��ͱ��ĵĳ�ʱʱ�����ֵ,��λ���� */
#define SFE_DRV_ONCE_SND_TIMEOUT_MAX        1000

/* �����治ʹ�ñ��Ŀ�ͨ������ */
#define SFE_PKT_FAST_PATH_DISABLE 0
/* ��������ձ�������ʹ�ñ��Ŀ�ͨ������ */
#define SFE_PKT_FAST_PATH_ENABLE 1

/* �����治֧��TCPУ��ͼ�� */
#define SFE_TCP_CKSUM_FLAG_DISABLE 0
/* ������֧��TCPУ��ͼ�� */
#define SFE_TCP_CKSUM_FLAG_ENABLE 1

/* �����治֧��TCPУ��ͼ�� */
#define SFE_UDP_CKSUM_FLAG_DISABLE 0
/* ������֧��TCPУ��ͼ�� */
#define SFE_UDP_CKSUM_FLAG_ENABLE 1

/* �����治֧��TCP�������ݺ���������ͨ���Ż� */
#define SFE_TCP_UPDATEWND_FLAG_DISABLE 0
/* ������֧��TCP�������ݺ���������ͨ���Ż� */
#define SFE_TCP_UPDATEWND_FLAG_ENABLE 1

/* TCP MSL�ϻ�ʱ����Сֵ,��λ:�� */
#define SFE_TCP_MSL_MIN_TIME 1
/* TCP MSL�ϻ�ʱ�����ֵ(Ĭ��ֵ),��λ:�� */
#define SFE_TCP_MSL_MAX_TIME 30

/* ����TCP�ӳ�ACK���� */
#define SEF_TCP_DELAYED_ACK_DISABLE 0

/* ��TCP�ӳ�ACK���� */
#define SEF_TCP_DELAYED_ACK_ENABLE 1

/* Ԥ������ṹ���� */
typedef struct tagSFE_PRECFG_VALUE
{
    UINT32 u32Key;              /* Ԥ���ò���ID */
    UINT32 u32Cfg_Value;        /* ����ֵ */
    UINT32 u32Min_Value;        /* ������ֵ������ */
    UINT32 u32Max_Value;        /* ������ֵ������ */
    CHAR   ai8KeyName[LEN_64];  /* Ԥ���������� */
}SFE_PRECFG_VALUE_S;
extern UINT32 SFE_Init(VOID);

/*******************************************************************************
*    Func Name: SFE_Set_PreConfigPara
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: SFEԤ���ò���ֵ���ú���
*  Description: ��������Ԥ���������u32Key��ֵ����ΪulValue��
*               �ú����������������ʼ��֮ǰ���á�
*        Input: UINT32 u32Key: Ԥ������,ȡֵ��Χ��ö�ٶ���SFE_PRECONFIG_INFO_E
*               UINT32 ulValue: ����ֵ
*       Output: 
*       Return: �ɹ�: SFE_ENTRY_OK
*               ʧ��: ������
*      Caution: �˺����ṩ����Ʒ����Ԥ������ֵ,���õ��Ǳ�VCPU��ȫ�ֱ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Set_PreConfigPara(UINT32 u32Key, UINT32 ulValue);

/*******************************************************************************
*    Func Name: SFE_Get_PreConfigPara
* Date Created: 2009-7-28
*       Author: wangmingxia/luowentong
*      Purpose: SFEԤ���ò���ֵ��ȡ����
*  Description: ��������ȡԤ������pstComPara->u32Key������ֵ�������õ����ޡ�
*               �����õ����޺�Ԥ���������ƣ��������Ǵ���ڲ���pstComPara�С�
*        Input: SFE_PRECFG_VALUE_S *pstComPara: Ԥ���ýṹ��Ϣ
*       Output: SFE_PRECFG_VALUE_S *pstComPara: Ԥ���ýṹ��Ϣ
*       Return: �ɹ�: SFE_ENTRY_OK
*               ʧ��: ������
*      Caution: ����Ѿ������˹����ڴ棬�򷵻ع����ڴ��ֵ�����򷵻�˽���ڴ��ֵ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-28    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_Get_PreConfigPara(SFE_PRECFG_VALUE_S *pstComPara);

/*******************************************************************************
*    Func Name: SFE_Show_PreConfigPara
* Date Created: 2009-7-31
*       Author: wangmingxia/luowentong
*      Purpose: ��ʾԤ��������Ϣ
*  Description: ��ʾԤ��������Ϣ,��������ʾ����Ԥ��������Ϣ��Ԥ���������ơ�����ֵ�������õ����޺Ϳ����õ����ޡ�
*       Output: 
*       Return: VOID
*      Caution: Important points if any
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                         DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-7-31    wangmingxia/luowentong       Creat the first version.
*
*******************************************************************************/
extern VOID SFE_Show_PreConfigPara(VOID);


extern UINT32 SFE_Set_ShareMemoryID(UINT32 u32SfeShareMemoryID, UINT32 u32SfeUserShareMemoryID,
                                      UINT32 u32SfeCoreShareMemoryID);


extern UINT32 SFE_Get_ShareMemoryID(UINT32 *pu32SfeShareMemoryID, UINT32 *pu32SfeUserShareMemoryID,
                                      UINT32 *pu32SfeCoreShareMemoryID);


extern VOID SFE_Show_ShareMemoryID(VOID);


extern VOID SFE_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: SFE_Show_StubDeleteModule
* Date Created: 2009-10-22
*       Author: wuhailan103194
*      Purpose: ��ʾ�ü���ģ����Ϣ
*  Description: ��ʾ�ü���ģ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-22   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_Show_StubDeleteModule(VOID);

#ifdef  __cplusplus
}
#endif

#endif


