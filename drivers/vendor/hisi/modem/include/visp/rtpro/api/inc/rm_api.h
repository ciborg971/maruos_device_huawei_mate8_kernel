#ifndef _RM_API_H
#define _RM_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH            47              /* �ӿ������� */
#endif

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RM_MAX_VRF_NAME_LENGTH        31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define RM_USR_DSCP_LEN               19
#define RM_IPV6_ADDRESS_WORD_LEN      16

#define RM_INETWK_ADDR_TYPE_IPV4         0x00000001
#define RM_INETWK_ADDR_TYPE_IPV6         0x00000002

/*static route 's max number*/
/* mody for BC3D03406 at 2010-06-24 */
/*#define MAX_STATIC_ROUTE_NUM         1024 */

/* modified by jijianhua For MCCP routeing extend                             */
/* 10K -> 25K                                                                 */
/* checked with SGSN, No impact, as SGSN has its own limition                 */
#define MAX_STATIC_ROUTE_NUM         25000 
/* end of modification by jijianhua                                           */

/*equal route 's max number*/
#define MAX_EQUAL_ROUTE_NUM          16
#define MAX_STATIC_ROUTE_COST        0xFFFF


/*static route's ulOper*/
#define RM_CFGAPI_OPER_CREATE  1
#define RM_CFGAPI_OPER_DELETE  0
#define RM_CFGAPI_OPER_ENABLE  1
#define RM_CFGAPI_OPER_DISABLE 0


/*static route's ulAction*/
#define ROUTE_ACTION_LOCAL           0x01
#define ROUTE_ACTION_FORWARD         0x02
#define ROUTE_ACTION_REJECT          0x03
#define ROUTE_ACTION_DISCARD         0x04

/*API's parameter - ulInstance*/
/*RIB/ACRT/��̬·�ɵ�ʵ���Ų�������,��RM_FILTER_RTMINST��ʹ��ʱ����Ч */
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define RM_INSTANCE_IPV4            1
#define RM_INSTANCE_IPV6            2
#define RM_API_TYPE_IPV4            1
#define RM_API_TYPE_IPV6            2
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*RIB/ACRT/��̬·�ɵĲ��ҹ��˱��- �ṹRM_RIB_FILTER_S ��RM_ACRT_FILTER_S���ֶ�ulFilterFlag*/
#define RM_CFGAPI_SHOW_ALL           0 
#define RM_CFGAPI_SHOW_WITH_FILTER   1

/*RIB/ACRT���ҹ��������ͣ��������ʹ��*
*  - �ṹRM_RIB_FILTER_S ��RM_ACRT_FILTER_S���ֶ�ulFilterLevel*/
#define RM_FILTER_RTMINST   0x00000001
#define RM_FILTER_DESTADDR  0x00000010
#define RM_FILTER_MASK      0x00000100
#define RM_FILTER_PROTOCOL  0x00001000
#define RM_FILTER_RPMINDEX  0x00010000
#define RM_FILTER_VRF       0x00100000

/*RIB/ACRT Э���ѯ���ͣ�ֱ��/��̬/RIP/OSPF,
* �� RM_FILTER_PROTOCOL ��ʹ��ʱ����Ч*/
#define RM_PROTO_CONNECTED  0x2  
#define RM_PROTO_STATIC     0x3
#define RM_PROTO_RIP        0x8
#define RM_PROTO_OSPF       0xD
#define RM_PROTO_VLINK      0x12
#define RM_PROTO_DHCP       0x13
/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   ���ⵥ��:V2R3C03-ROTUE-MERGE  */
#define RM_PROTO_NET        0x14
#define RM_PROTO_RIPNG      0x18
#define RM_PROTO_OSPF6      0x1D


/*OSPF��Э������*/
#define RM_SUBPROT_OSPF_INTRA_AREA           0x000D0000
#define RM_SUBPROT_OSPF_INTER_AREA           0x000D0001
#define RM_SUBPROT_OSPF_TYPE1_EXT            0x000D0002
#define RM_SUBPROT_OSPF_TYPE2_EXT            0x000D0003
#define RM_SUBPROT_OSPF_NSSA1                0x000D0004
#define RM_SUBPROT_OSPF_NSSA2                0x000D0005

/*RIB/ACRT ·�ɲ�ѯʱ��route type����*/
#define RM_ROUTE_TYPE_OTHER                    1
#define RM_ROUTE_TYPE_REJECT                   2
#define RM_ROUTE_TYPE_LOCAL                    3
#define RM_ROUTE_TYPE_REMOTE                   4

/*��̬·��ʹ��״̬*/
#define RM_STATIC_ROUTE_ENABLE        1
#define RM_STATIC_ROUTE_DISABLE       0

#define RM_TRUE        1
#define RM_FALSE       0

#define RM_IPV4_ADDRESS_LEN     4
#define RM_IPV4_MASK_LEN     32
/*End*/
typedef struct tagRM_CFG_USR4
{
    ULONG ulOper; /*���û�ɾ����0-delete��1-create*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/
    ULONG ulRtPri;/*·�����ȼ���Ĭ��Ϊ1��ȡֵ1-255*/
    ULONG ulDestAddr;/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-32*/
    ULONG ulNextHopAddr;/*��һ�������ص�ַ*/
    ULONG ulAction; /*��̬·�ɵ�ACTION����*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*·������ 19 bytes*/
    ULONG ulPathCost;/*·��costֵ��ȡֵ0��0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_CFG_USR4_S;

typedef struct tagRM_ENABLE_USR4
{
    ULONG ulOper; /*ʹ�ܻ�ȥʹ�ܣ�0-disable��1-enable*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/
    ULONG ulDestAddr;/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-32*/
    ULONG ulNextHopAddr;/*��һ�������ص�ַ*/
    ULONG ulAction; /*��̬·�ɵ�ACTION����*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_ENABLE_USR4_S;

typedef struct tagRM_MOD_USR4
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/
    ULONG ulRtPri;/*·�����ȼ���Ĭ��Ϊ1��ȡֵ1-255*/
    ULONG ulDestAddr;/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-32*/
    ULONG ulNextHopAddr;/*��һ�������ص�ַ*/
    ULONG ulAction; /*��̬·�ɵ�ACTION����*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*·������ 19 bytes*/
    ULONG ulPathCost;/*·��costֵ��ȡֵ0��0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_MOD_USR4_S;

typedef struct tagRM_CFG_USR6
{
    ULONG ulOper; /*���û�ɾ����0-delete��1-create*/
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/
    ULONG ulRtPri;/*·�����ȼ���Ĭ��Ϊ1��ȡֵ1-255*/
    UCHAR aucDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ 4*4 bytes*/
    ULONG ulPrefixLen;/*ǰ׺���ȣ�ȡֵ0-128*/
    UCHAR aucNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ 4*4 bytes*/
    ULONG ulAction; /*��̬·�ɵ�ACTION����*/   
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*·������ 19 chars*/
    ULONG ulPathCost;/*·��costֵ��ȡֵ0��0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_CFG_USR6_S;

typedef struct tagRM_MOD_USR6
{
    UCHAR szIfName[MAX_IF_NAME_LENGTH+1];/*���ӿ�����*/
    ULONG ulRtPri;/*·�����ȼ���Ĭ��Ϊ1��ȡֵ1-255*/
    UCHAR aucDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ 4*4 bytes*/
    ULONG ulPrefixLen;/*ǰ׺���ȣ�ȡֵ0-128*/
    UCHAR aucNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ 4*4 bytes*/
    ULONG ulAction; /*��̬·�ɵ�ACTION����*/   
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*·������ 19 chars*/
    ULONG ulPathCost;/*·��costֵ��ȡֵ0��0xFFFF*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szVrfName[RM_MAX_VRF_NAME_LENGTH+1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_MOD_USR6_S;

typedef struct tagRM_RIB_FILTER
{
    ULONG ulFilterFlag; /*���˱�ǣ�1Ϊ���ˣ�0Ϊ������*/
    ULONG ulFilterLevel;/*������ʹ�ü�������*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    ULONG ulType;/*����IPv4����IPv6���͹���*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*����·��Ŀ�ĵ�ַ����*/
    ULONG ulMask; /*����·��������ˣ�ȡֵ0-128*/    
    ULONG ulProtocol; /*����·��Э��Ź���*/ 
    ULONG ulProcessId; /*�����ṩ·�ɵĽ���ID����*/   
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_RIB_FILTER_S;

typedef struct tagRM_ACRT_FILTER
{
    ULONG ulFilterFlag; /*���˱�ǣ�1Ϊ���ˣ�0Ϊ������*/
    ULONG ulFilterLevel;/*������ʹ�ü�������*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    ULONG ulType;/*����IPv4����IPv6���͹���*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*����·��Ŀ�ĵ�ַ����*/
    ULONG ulMask; /*����·��������ˣ�ȡֵ0-128*/     
    ULONG ulProtocol; /*����·��Э��Ź���*/ 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_ACRT_FILTER_S;

typedef struct tagRM_STATIC_FILTER
{
    ULONG ulFilterFlag; /*���˱�ǣ�1Ϊ���ˣ�0Ϊ������*/
    ULONG ulFilterLevel;/*������ʹ�ü�������*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    ULONG ulType;/*����IPv4����IPv6ʵ���Ź���*/
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}RM_STATIC_FILTER_S;

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   ���ⵥ��:V2R3C03-ROTUE-MERGE  */
typedef struct tagRM_NETRT_FILTER
{
    ULONG ulIfIndex;/*�ӿ�����,0Ϊ������,��0Ϊָ���ӿ�����*/
}RM_NETRT_FILTER_S;
/*End of Modified by lixs00177467, 2011/1/22   ���ⵥ��:V2R3C03-ROTUE-MERGE  */


typedef struct tagRM_DSP_RIB
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ����ַ*/
    UCHAR szRelayNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*������һ����ַ*/
    ULONG ulExitIf; /*���ӿ�*/
    ULONG ulRoutetype;  /*·�����ͣ���ʾ·���Ǳ���������ת��*/
    ULONG ulProto;  /*·��Э��8-RIP;13-OSPF;*/  
    ULONG ulSubProto;  /*·����Э�飬ֻ��OSPF��Ч;*/  
    ULONG ulRouteAge; /*·���ϻ�ʱ��*/
    ULONG ulPriority; /*���ȼ�*/ 
    LONG lMetric1; /*costֵ*/
    LONG lMetric2; /*costֵ��RIP��Ч��OSPF��Ч*/
    ULONG ulFibRoute;  /*�Ƿ��µ�FIB��1-�µ�FIB�У�0-û���µ�FIB��*/ 
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    ULONG ulType;
}RM_DSP_RIB_S;


typedef struct tagRM_DSP_ACRT
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ*/
    UCHAR szRelayNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*������һ����ַ*/
    ULONG ulExitIf; /*���ӿ�*/
    ULONG ulRoutetype;  /*·�����ͣ���ʾ·���Ǳ���������ת��*/
    ULONG ulProto;  /*·��Э��8-RIP;13-OSPF;*/    
    ULONG ulSubProto;  /*·����Э�飬ֻ��OSPF��Ч;*/  
    ULONG ulRouteAge; /*·���ϻ�ʱ��*/
    ULONG ulPriority; /*���ȼ�*/
    LONG lMetric1; /*costֵ*/
    LONG lMetric2; /*costֵ��RIP��Ч��OSPF��Ч*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    
    ULONG ulType;
}RM_DSP_ACRT_S;
/*End of Modify */


typedef struct tagRM_DSP_STATICRT
{
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    /*ULONG ulInstance;*/ /*����IPv4����IPv6ʵ���Ź���*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ*/
    ULONG ulMask;/*���룬ȡֵ0-128*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ*/
    ULONG ulExitIf; /*���ӿ�*/
    ULONG ulPriority; /*���ȼ�*/
    ULONG ulPathCost; /*Cost*/
    ULONG ulAdminStat; /*����״̬��1-ʹ��״̬��0-ȥʹ��״̬*/
    UCHAR aucDescription[RM_USR_DSCP_LEN + 1];/*·������ 19 chars*/
    
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����·��Ŀ�ĵ�ַ����*/
    ULONG ulType;
    
    ULONG loose_num;
    /*Mod End*/
}RM_DSP_STATICRT_S;

/*RTM��Ҫ��Ϣ���ݽṹ*/
typedef struct tagRM_BRIEF_INFO
{
  CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];  /*VRF NAME*/
  ULONG ulEqualCostOpt;              /* ��RPM��RTM��ѯ·��ʱ���������ƽ��·�ɣ��Ƿ�������ƽ��·�ɻ���ֻ��������һ��,*/
                                                 /*AMB_RTM_EQUAL_COST_ALL ---��������ƽ��·�ɡ�AMB_RTM_EQUAL_COST_ONE ---��������һ��,*/
                                                 /*Ĭ�ϣ�AMB_RTM_EQUAL_COST_ALL;  */
  ULONG ulAddrFamily;                 /* Э����.Ĭ��: AMB_INETWK_ADDR_TYPE_IPV4; */
  ULONG ulTotalRouteNum;             /* ��ǰ·�ɱ��е�·������*/   
  ULONG ulActRouteNum;             /* ��ǰ·�ɱ��м����·����*/                                       
  ULONG ulStaticRouteNum;          /*��ǰ·�ɱ��о�̬��·����*/
  ULONG ulActStaticRouteNum;          /*��ǰ·�ɱ��о�̬��·����*/
  ULONG ulFromOspfRtNum;          /*��ǰ·�ɱ�������OSPF��·����*/
  ULONG ulFromRipRtNum;             /*��ǰ·�ɱ�������RIP��·����*/
  ULONG ulVlinkRtNum;                 /*��ǰ·�ɱ��е�Vlink·�ɸ���*/
  ULONG ulConnectRtNum;            /*��ǰ·�ɱ��е�ֱ��·�ɸ���*/
}RM_BRIEF_INFO_S;

typedef struct tagRM_BRIEF_FILTER
{
    ULONG ulFilterFlag;    /*���˱�ǣ�1Ϊ���ˣ�0Ϊ������*/
    ULONG ulFilterLevel;  /*������ʹ�ü�������*/
    ULONG ulType;/*����IPv4����IPv6ʵ���Ź���*/
    CHAR szVrfName[RM_MAX_VRF_NAME_LENGTH + 1];/*����VRF���ˣ���������ʾ���е�*/
}RM_BRIEF_FILTER_S;

/* Modified by lixs00177467, for rtm net route, VISPV2R3C03SPC010-G2 2011/1/22   ���ⵥ��:V2R3C03-ROTUE-MERGE  */
typedef struct tagRM_DSP_NETRT
{
    UCHAR szDestAddr[RM_IPV6_ADDRESS_WORD_LEN];/*Ŀ�ĵ�ַ*/
    ULONG ulPrefixLen;/*ǰ׺����*/
    UCHAR szNextHopAddr[RM_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ*/
    ULONG ulIfIndex; /*���ӿ�*/
}RM_DSP_NETRT_S;
/*End of Modified by lixs00177467, 2011/1/22   ���ⵥ��:V2R3C03-ROTUE-MERGE  */

typedef enum enumRMError
{
    RM_OK = 0,
    /*���´�������DCLͨ��mib����ֱ�ӷ���,ֻ��IPS���ص�ʱ���ʹ��*/
    RM_NO_ERROR,                 /*�ɹ�*/
    RM_ERR_GEN_ERROR = MID_COMP_RTM + 2,
    /*End*/
    RM_ERR_WRONG_VALUE,                             /*MIB���õ�ֵ����*/
    RM_ERR_INCONSISTENT_VALUE,                      /*MIB���õ�ֵ��һ��*/
    RM_ERR_RESOURCE_UNAVAILABLE,                    /*MIB���õ���Դ��Ч*/
    RM_ERR_NO_SUCH_OBJECT,                          /*���󲻴���*/
    RM_ERR_AMB_RC_END_OF_TABLE,                     /*�������*/
    RM_ERR_AGENT_ERROR,
    RM_ERR_INCOMPLETE,
    RM_ERR_PARTIAL_FAMILY_OK,
    RM_ERR_PRODUCT_NOT_READY,
    RM_ERR_CFG_TIME_OUT = MID_COMP_RTM + 15,        /*15*/
    /*����API�ڲ�ͨ���������*/
    RM_ERR_ADDR_LINKLOCAL,
    RM_ERR_PARA, 
    RM_ERR_MALLOC_FAILED,
    RM_ERR_HANDLE_IS_NOT_EXSIT,
    RM_ERR_CONF_DATA_IS_NULL,                       /*20*/
    RM_ERR_CONN_CB_IS_NULL,
    RM_ERR_RETURN_IPS_IS_NULL,
    RM_ERR_REDIST_STEP,
    /*����API�ڲ�ר���������*/    
    RM_ERR_ACTIONTYPE,
    RM_ERR_ROUTE_ACTION,
    RM_ERR_ENABLE,
    RM_ERR_INSTANCE,
    RM_ERR_IFNAME,
    RM_ERR_IFLLOOPBACK,
    RM_ERR_IFNULL,                                  /*30*/
    RM_ERR_RTPRI,
    RM_ERR_DESTADDR,
    RM_ERR_DESTADDR_1,
    RM_ERR_DESTADDR_2,
    RM_ERR_DESTADDR_3,
    RM_ERR_MASK,
    RM_ERR_HOPADDR,
    RM_ERR_HOPADDR_1,
    RM_ERR_HOPADDR_2,
    RM_ERR_HOPADDR_3,                               /*40*/
    RM_ERR_NOT_HOPIFNAME,
    RM_ERR_NOT_PPP_LINE,
    RM_ERR_MAX_SROUTE_NUM,
    RM_ERR_ADDRFAMILY,
    RM_ERR_PROTO,
    RM_ERR_IF_NH_CHECK,
    RM_ERR_EQUAL_ROUTE_NUM,
    RM_ERR_DIRECT_ROUTE_COST,
    RM_ERR_STATIC_ROUTE_COST,
    RM_ERR_DESTACL_NUM,                             /*50*/
    RM_ERR_POINTER_IS_NULL,                         /*ָ��Ϊ��*/
    RM_ERR_RTM_HAVE_NOT_ENABLE,                     /*RTM��û�д���*/
    RM_ERR_CAN_NOT_FIND_ROUTE,                      /*�Ҳ���·��*/
    RM_ERR_CAN_NOT_FIND_NEXT_ROUTE,                 /*�Ҳ�����һ��·��*/
    RM_ERR_HANDLE_IS_NULL,
    RM_ERR_INVALID_VERSION,                         /*����İ汾����IPV4����IPV6*/
    RM_ERR_REDIST_SRCINST_FILTER,
    RM_ERR_REDIST_DESTINST_FILTER,
    RM_ERR_REDIST_IFINDEX_FILTER,
    RM_ERR_REDIST_OSPFAREA_FILTER,                  /*60*/
    RM_ERR_REDIST_OSPFTAG_FILTER,
    RM_ERR_REDIST_FLAG_FILTER,
    RM_ERR_REDIST_PATHTYPE_FILTER,
    RM_ERR_REDIST_DESTACL_FILTER,
    RM_ERR_REDIST_PRIORITY,
    RM_ERR_REDIST_DIRECTFLAG,
    RM_ERR_REDIST_RIP_COST,
    RM_ERR_REDIST_OSPF_COST,
    RM_ERR_REDIST_METRIC_CONV,
    RM_ERR_REDIST_POLICY_NOT_EXIST,                 /*70*/
    RM_ERR_REDIST_SRCPROTO,
    RM_ERR_REDIST_PROTO_NO_PROCESS,
    RM_ERR_REDIST_NO_SRC_PROCESS,
    RM_ERR_REDIST_SRC_SAME_PROTO,
    RM_ERR_REDIST_SRC_SAME_PROCESS,
    RM_ERR_REDIST_DESTPROTO_1,
    RM_ERR_REDIST_DESTPROTO_2,
    RM_ERR_REDIST_NO_DEST_PROCESS,
    RM_ERR_REDIST_DEST_SAME_PROTO,
    RM_ERR_REDIST_DEST_SAME_PROCESS,                /*80*/
    RM_ERR_REDIST_SRC_NOT_OSPF_1,
    RM_ERR_REDIST_SRC_NOT_OSPF_2,
    RM_ERR_REDIST_RIP_NO_PATHTYPE,
    RM_ERR_REDIST_RIP_NO_OSPFTAG,
    RM_ERR_REDIST_OSPF_PATHTYPE,
    RM_ERR_REDIST_OSPF_OSPFTAG,  
    RM_ERR_REDIST_NO_SRC_DEST,
    RM_ERR_REDIST_MAX_POLICY_NUM,
    RM_ERR_CONFIG_FLAG_INVALID,                     /*���ò������󣬲���TUREҲ����FALSE*/
    RM_ERR_PRAR_INVALID,                            /*90:�������󲻺Ϸ�*/
    RM_ERR_PROCID_CAN_NOT_ZERO,                     /*����Id����Ϊ0*/
    RM_ERR_POLICY_ID_NOT_EXIST,                     /*����ID������*/
    RM_ERR_POLICY_ID_EXIST,                         /*����ID����*/
    RM_ERR_POLICY_ID_EXCEED_LIMIT,                  /*����ID�������ֵ*/
    RM_ERR_POLICY_ID_ZERO,                          /*����ID����Ϊ0*/
    RM_ERR_SOURCE_PRO_TYPE,                         /*�����ԴЭ������*/
    RM_ERR_INIT_FAILED,                             /*RMȫ����Դû�г�ʼ�����*/
    RM_ERR_HOPADDR_IN_DEST,                         /*ָֻ����һ����ַʱ����һ����������Ŀ��������*/
    RM_ERR_HOOKFUNC_IS_NULL,
    RM_ERR_IFNET_IS_NULL,                           /*100:�ӿ�ifnetΪ��*/
    RM_ERR_INTERFACE_IS_L2,                         /*�ӿ�Ϊ����ӿ�*/
    RM_ERR_METRIC_TYPE,                             /*�����metric ����*/
    RM_ERR_NOT_OSPF_METRIC_TYPE_MUST_ZERO,          /*�� OSPF ���͵�metric���ͱ�����0*/
    RM_ERR_PROCID_MUST_ZERO,                        /*��̬����ֱ����ʵ���ű�����0*/
    RM_ERR_GET_IPV6_FUNCTION,                       /*��ȡIPv6���ָ�����*/
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    RM_ERR_GET_VRF_INDEX,
    RM_ERR_VRF_INDEX_INVALID,
    RM_ERR_GET_INST_NUM,
    RM_ERR_GET_VRF_NAME,
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    RM_ERR_DIRECT_ROUTE,                            /*110*/
    RM_ERR_IPV_TYPE,                      /*�����IPV����(��IPV4/IPV6)*/

    /* BEGIN V2R3TEST */

    RM_ERR_FILTER_RULE_NOT_EXIST,   /*���˹��򲻴���:����/����*/
    RM_ERR_FILTER_RULE_EXIST,        /*���˹����Ѿ�����:����/����*/
    RM_ERR_GET_HAVE_NOT_OPEN,    /*û�н���OPEN����*/
    RM_ERR_GETFIRST_FAIL,       /*FIRST����ʧ�ܲ���*/
    RM_ERR_VRF_NULL_POINT,/*VRF��Ϊ��*/
    RM_ERR_VRF_ADDR_NULL_POINT,/*VRF��ַ��Ϊ��*/
    RM_ERR_DESTADDR_NOT_GLOBAL,/*��̬·��Ŀ�ĵ�ַ��ΪGlobal��ȫ0��ַ*/
    RM_ERR_NETRT_PREFIX,/*����·��ǰ׺��Ч*//*VISPV1R8C03 for rtm net route*/
    RM_ERR_NETRT_GET_IF_INFO,/*120:*//*��ȡ����·�ɳ��ӿ���Ϣ����*/
    RM_ERR_NETRT_IF_TYPE_INVALID,/*����·�ɳ��ӿ�������Ч*/
    RM_ERR_NETRT_NEXTHOP_INVALID,/*��һ������Ϊָ���ӿ�Global��ַ*/
    RM_ERR_NETRT_DESTADDR_INVALID,/*Ŀ�ĵ�ַ����һ����ǰ׺����������*/
    RM_ERR_NETRT_EXIST,/*����·���Ѿ�����*/
    RM_ERR_NETRT_NO_MORE,/*�����и�������·��*/
    RM_ERR_NETRT_NOT_EXIST,/*����·�ɲ�����*/
    RM_ERR_NETRT_RM_MODE,/*RMģʽ����*/
    /*Begin BC3D02905 liangjicheng 2010-04-12*/
    RM_ERR_REDIST_HOPACL_FILTER,  /*128 ��һ��ACL����*/
    RM_ERR_HOPACL_NUM,
    RM_ERR_DESTHOPACL_NUM,
/* END V2R3TEST */

    RM_ERR_MAX = MID_COMP_RTM + 255
}RM_ERROR_S;


extern RM_ERROR_S RM_SetIpv4Route(RM_CFG_USR4_S * pstUsrIpTable);
extern RM_ERROR_S RM_EnableIpv4Route(RM_ENABLE_USR4_S * pstUsrIpEnable);
extern RM_ERROR_S RM_UpdateIpv4Route(RM_MOD_USR4_S * pstUsrIpTable);
extern RM_ERROR_S RM_SetIpv6Route(RM_CFG_USR6_S *pstUsrIpTable);
extern RM_ERROR_S RM_SetEqualRouteNum(ULONG ulInstance,ULONG ulEqualRtNum);
extern RM_ERROR_S RM_GetEqualRouteNum(ULONG ulInstance,ULONG *pulEqualRtNum);
/*END of Add*/
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern RM_ERROR_S RM_SetEqualRouteNumByVrf(ULONG ulType,ULONG ulEqualRtNum,CHAR *pszVrfName);
extern RM_ERROR_S RM_GetEqualRouteNumByVrf(ULONG ulType,ULONG *pulEqualRtNum,CHAR *pszVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

extern RM_ERROR_S RM_CMM_RIB_TableOpen(ULONG * pulSessionID,RM_RIB_FILTER_S *pstRIBFilter);
extern RM_ERROR_S RM_CMM_RIB_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_RIB_GetFirst(ULONG ulSessionID, RM_DSP_RIB_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_RIB_GetNext(ULONG ulSessionID, RM_DSP_RIB_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_ACRT_TableOpen(ULONG * pulSessionID,RM_ACRT_FILTER_S *pstACRTFilter);
extern RM_ERROR_S RM_CMM_ACRT_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_ACRT_GetFirst(ULONG ulSessionID, RM_DSP_ACRT_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_ACRT_GetNext(ULONG ulSessionID, RM_DSP_ACRT_S * pstConfigInfo);
extern RM_ERROR_S RM_CMM_StaticRt_TableOpen(ULONG * pulSessionID,RM_STATIC_FILTER_S *pstStaticFilter);
extern RM_ERROR_S RM_CMM_StaticRt_TableClose(ULONG ulSessionID );
extern RM_ERROR_S RM_CMM_StaticRt_GetFirst(ULONG ulSessionID, RM_DSP_STATICRT_S * pstConfigInfo);  
extern RM_ERROR_S RM_CMM_StaticRt_GetNext(ULONG ulSessionID, RM_DSP_STATICRT_S * pstConfigInfo);

extern RM_ERROR_S RM_CMM_Brief_Open(ULONG *pulSessionID,RM_BRIEF_FILTER_S *pstBriefFilter);
extern RM_ERROR_S RM_CMM_Brief_GetFirst(ULONG ulSessionID,RM_BRIEF_INFO_S *psBriefInfo);
extern RM_ERROR_S RM_CMM_Brief_GetNext(ULONG ulSessionID, RM_BRIEF_INFO_S *psBriefInfo);
extern RM_ERROR_S RM_CMM_Brief_Close(ULONG ulSessionID );

extern VOID RM_ShowEqualRouteNum(ULONG ulInstance);
extern VOID RM_ShowIPv4RIBInfoAll(VOID);
extern VOID RM_ShowIPv6RIBInfoAll(VOID);
extern VOID RM_ShowIPv4ACRTInfoAll(VOID);
extern VOID RM_ShowIPv6ACRTInfoAll(VOID);
extern VOID RM_ShowIPv4StaticInfoAll(VOID);
extern VOID RM_ShowIPv6StaticInfoAll(VOID);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
extern VOID RM_ShowEqualRouteNumByVrf(ULONG ulType,CHAR *pszVrfName);
extern VOID RM_ShowIPv4RIBInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6RIBInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv4ACRTInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6ACRTInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv4StaticInfoAllByVrf(CHAR *szVrfName);
extern VOID RM_ShowIPv6StaticInfoAllByVrf(CHAR *szVrfName);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

extern VOID RM_ShowIPv4RtmBriefInfoByVrf(CHAR *szVrfName,ULONG ulFlag,ULONG ulFilterLevel);
/* wangjiaqi modify for ipv6 20130926 begin */
extern VOID RM_ShowIPv6RtmBriefInfoByVrf(CHAR *szVrfName,ULONG ulFlag,ULONG ulFilterLevel);
/* wangjiaqi modify for ipv6 end */

/*rm_api.h ���ݽṹ
*/
#define RM_RPM_MTYPE_INVALID   0
#define RM_RPM_MTYPE_INTERNAL  1
#define RM_RPM_MTYPE_EXTERNAL  2
#define RM_RPM_MTYPE_TYPE1     3
#define RM_RPM_MTYPE_TYPE2     4

typedef struct tagRM_RPM_PLCYDIST
{
    union
    {
        ULONG ulAccNum;         /* Access List Number */
    } stFltrName;            
    USHORT  usProcessID;        /* AS Number/Process ID */
    UCHAR   ucProtocolID;       /* Protocol ID */    
    UCHAR  ucPad;
} RM_RPM_PLCYDIST_S;

typedef struct tagRM_RPM_PLCYREDIS
{
    UCHAR   ucRPAID;
    UCHAR   ucPad;
    USHORT  usRPAProcessID;
    ULONG   enMetricType;/*���ڲ�Ʒ�Ѿ�ʹ�ã��������޸�Ϊul��ͷ*/ 
    ULONG   ulMetricVal;
} RM_RPM_PLCYREDIS_S;  

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
typedef ULONG (*DCL_SET_RT4_FUNC)(RM_CFG_USR4_S * pstUsrIpTable);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

#define NBASE_CPU_SWITCH_VALUE_MIN  1     
#define NBASE_CPU_SWITCH_VALUE_MAX  1000 

#define SCKSTUB_CPU_SWITCH_VALUE_MIN  1     
#define SCKSTUB_CPU_SWITCH_VALUE_MAX  1000 

#define SCKSTUB_CPU_SWITCH_TIME_MIN  1     
#define SCKSTUB_CPU_SWITCH_TIME_MAX  100 

#define OSPF_PERTENLSA_CALC_DELAY_MIN  1     
#define OSPF_PERTENLSA_CALC_DELAY_MAX  100 

typedef struct tagDCL_CPUSW
{
    ULONG ulNbaseCpuSwitchValue;    /* Nbase��Ϣ����������ޣ�Ĭ��10��IPS   ��Χ:1~1000*/
    ULONG ulSckStubCpuSwitchValue;  /* SckStub������������ޣ�Ĭ��10��IPS ��Χ:1~1000*/
    ULONG ulSwitchTime;             /* �л�CPU������ʱ�䣬Ĭ��Ϊ1ms         ��Χ:1~100 */
    ULONG ulOspfPerTenLSACalcDelay; /* OSPF ����·�ɼ������ʱ���ƣ���λ:ÿ10��LSA��С��ʱʱ��(ms)��Ĭ��50 (ms/10-lsa) ��Χ:1~100 */
}DCL_CPUSW_S;


ULONG TCPIP_SetDclCpuSwitchValue(DCL_CPUSW_S *pstSwitchValue);


ULONG TCPIP_GetDclCpuSwitchValue(DCL_CPUSW_S *pstSwitchValue);

/*******************************************************************************
*    Func Name: TCPIP_SetDclCpuSwitchValue
* Date Created: 2013-4-16
*       Author: qinyun 62011
*  Description: ����RTM�����ݹ��������
*        Input: ULONG ulCoun:ֵ����Ч��0��ʾ�������޴���Ĭ��Ϊ0
*       Output: 
*       Return: �ɹ����� RM_OK; ʧ�ܷ���  RM_ERR_PARA RM_ERR_WRONG_VALUE; 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-4-16  qinyun 62011   Create
*
*******************************************************************************/
ULONG TCPIP_SetRtmResolveCount(ULONG ulCount);

extern RM_ERROR_S RM_EnableIpv4RouteExt(RM_ENABLE_USR4_S * pstUsrIpEnable, ULONG ulVrfIndex);

#ifdef  __cplusplus
}
#endif

#endif 

