

#ifndef _TCPIP_SFE_SHARE_API_H_
#define _TCPIP_SFE_SHARE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/tcpip_id.h"

/*******************************��������**********************************************************************/
#define SFE_ERRCODE_BEGIN      ( MID_COMP_PUBLIC + 0x8000 )

/* �������Ӧ�Ŀ�������뷵��ֵȫ��Ψһ��ģ����������λ���,Ϊÿ��ģ��Ԥ��512��������,0x200
   ע���������Ӧ�Ŀ����������ȡֵ��Χ�Ǵӿ�����PUBLIDģ��ֳ����ĺ���һ����,
   ���������ʱע�ⲻҪԽ��.Ŀǰ����Ĵ������������������:
   [(MID_COMP_PUBLIC + 0x8000), (MID_COMP_PUBLIC + 0xFFFF)] */
typedef enum enumTcpipSfeGlobalRetCode
{
    TCPIP_SFE_COM_BEGIN_RET_CODE = SFE_ERRCODE_BEGIN,                  /* MSG��ϢͨѶģ���������ʼֵ */
    TCPIP_SFE_TABLE_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0200),     /* POOL TABLE����ģ���������ʼֵ */
    TCPIP_SFE_ARP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0400),       /* ARPģ���������ʼֵ */
    TCPIP_SFE_ROUTE_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0600),     /* ROUTEģ���������ʼֵ */
    TCPIP_SFE_IF_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0800),        /* IF�ӿ�ģ���������ʼֵ */
    TCPIP_SFE_BFD_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0a00),       /* BFD��ϢͨѶģ���������ʼֵ */
    TCPIP_SFE_ICMP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0c00),      /* ICMPģ���������ʼֵ */
    TCPIP_SFE_IP_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x0e00),        /* IPģ���������ʼֵ */
    TCPIP_SFE_DEBUG_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x1000),     /* DEBUGά��ģ���������ʼֵ*/
    TCPIP_SFE_PUB_BEGIN_RET_CODE = (SFE_ERRCODE_BEGIN + 0x1200),       /* PUBģ���������ʼֵ*/
}TCPIP_SFE_GLOBAL_RET_CODE_E;

/*******************************�����浽��������Ϣͨ����غ�,ö��,�ṹ�ȶ���**********************************/
/* ������ͨ�Ŵ����� */
enum enumCtlComCode
{
    TCPIP_SFE_COM_SUCCESS,                      /* �����ɹ�*/
    TCPIP_SFE_COM_ERR_BEGIN = TCPIP_SFE_COM_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_COM_RCVMSG_LEN_ERR,               /* ͨ�����ݱ��ĳ��Ⱥ��յ����ĳ��Ȳ�һ�� */
    TCPIP_SFE_COM_RCVMSG_LEN_SHORT,             /* �����ܳ��ȷǷ� */
    TCPIP_SFE_COM_REG_MSGTOTSFE_NULL,           /* ע������淢����������Ϣ���Ӻ���Ϊ�� */
    TCPIP_SFE_COM_REG_MSGFROMSFE_NULL,          /* ע������������������Ϣ���Ӻ���Ϊ�� */
    TCPIP_SFE_COM_REG_ALLOC_NULL,               /* ע������ڴ湳�Ӻ���Ϊ�� */
    TCPIP_SFE_COM_REG_FREE_NULL,                /* ע���ͷ��ڴ湳�Ӻ���Ϊ�� */
    TCPIP_SFE_RECV_MSG_NULL,                    /* �����������Ϣͨ������Ϊ�� */
    TCPIP_SFE_RECV_MOUDLE_ERR,                  /* �����������������Ϣ��ģ��Ƿ� */
    TCPIP_SFE_RECV_ITEM_LEN_ERR,                /* �����������������Ϣ�б��ĳ���С��һ��TLV */
    TCPIP_SFE_COM_ARPMISS_ITEMLEN_INVALID,      /* ARP MISS��Ϣ���Ȳ��Ϸ� */

    TCPIP_SFE_MSG_PARA_INVALID,                 /* �������Ϸ�,���յ����ݳ���Ϊ0�ͽ��ջ�����ָ��NULL��������ʹ�� */
    TCPIP_SFE_MSG_SEND_PARA_INVALID,            /* �������Ϸ�,���͵����ݳ���Ϊ0�ͷ��ͻ�����ָ��NULL��������ʹ�� */
    TCPIP_SFE_MSG_MEMALLOC_FUNC_NULL,           /* ������ͨ���ڴ������ͷź���ΪNULL,δע�� */
    TCPIP_SFE_MSG_CHANNEL_FUNC_NULL,            /* ���������������ͨ��ΪNULL,δע�� */
    TCPIP_SFE_MSG_MEMALLOC_INPUT_NULL,          /* ����ͨ���ڴ�ʱ�����ָ�붼ΪNULL */
    TCPIP_SFE_MSG_MEMALLOC_SENDBUF_FAIL,        /* ���뷢�ͻ�����ʧ�� */
    TCPIP_SFE_MSG_MEMALLOC_RCVBUF_FAIL,         /* ������ջ�����ʧ�� */
    TCPIP_SFE_MSG_CHANNEL_SEND_FAIL,            /* ���������������ͨ���������ݵ�������ʧ�� */
    TCPIP_SFE_MSG_CHANNEL_RCV_FAIL,             /* ���������������ͨ����������������ݽ���ʧ�� */
    TCPIP_SFE_MSG_RCVMSG_LEN_INVALID,           /* ���յ���Ϣ���ȷǷ�,С����С��Ϣ���� */
    TCPIP_SFE_MSG_RCVMSG_LENFIELD_INVALID,      /* ���յ���Ϣ�е���Ϣ�����ֶηǷ�,�������Ϣ���Ȳ��� */
    TCPIP_SFE_MSG_RCVMSG_SEQ_INVALID,           /* ���յ���Ϣ�е���Ϣ����ֶηǷ�,�뷢����Ϣ��Ų��� */
    TCPIP_SFE_MSG_RCVMSG_ITEMLEN_INVALID,       /* ��ѡ���еĳ����ֶβ��Ƿ�,����յ���Ϣ���Ȳ�Э�� */
    TCPIP_SFE_MSG_RCVMSGLEN_NOTEXPECT,          /* ���յ���Ϣ���ȷǷ�,�����������Ľ�����Ϣ���� */
    TCPIP_SFE_MSG_RCVMSG_DATALEN_NOTEXPECT,     /* ���յ����ݳ��Ȳ������������յ����ݳ��� */
    TCPIP_SFE_MSG_RCVMSG_DATALEN_LESSTHAN4,     /* ���յ����ݳ��Ȳ��Ϸ�,С�ڴ�����4�ֽ� */

    TCPIP_SFE_COM_BFDDETECTDOWN_ITEMLEN_INVALID,/* BFD̽��DOWN��Ϣ���Ȳ��Ϸ� */
    TCPIP_SFE_COM_EVENT_OPER_TYPE_INVALID,      /* �������յ���������EVNET������Ϣ�еĲ��������ֲ��Ϸ� */

    TCPIP_SFE_COM_CHECKSUM_FAIL,                /* ͨ����ϢУ��ʹ���*/
    TCPIP_SFE_COM_CHECKSUM_EVENT_FAIL,          /* �¼���Ϣ��У��ʹ���*/
};

/*******************************IF�ӿ���غ�,ö��,�ṹ�ȶ���**********************************/
/* �ӿ�ģ������� */
typedef enum enumCTLIFERRCODE
{
    TCPIP_SFE_IF_SUCCESS,           /* �����ɹ� */
    TCPIP_SFE_IF_ERR_BEGIN = TCPIP_SFE_IF_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_IF_NULL_POINTER,      /* �������ָ��Ϊ�� */
    TCPIP_SFE_IF_COMREG_NULL,       /* ͨ����ؽӿ�δע�� */
    TCPIP_SFE_IF_MALLOCFAIL,        /* �����ڴ�ʧ�� */
    TCPIP_SFE_IF_ERROROPER,         /* ��������� */
    TCPIP_SFE_IF_OVERMAXPORTTYPE,   /* �����ڵĽӿ����� */
    TCPIP_SFE_IF_ERRPORTTYPE,       /* ��֧�ִ��ֽӿ����� */
    TCPIP_SFE_IF_GETIFNETFAIL,      /* ��ȡIFNET��Ϣʧ�� */
    TCPIP_SFE_IF_GETPORTINFOFAILFOR1DIM,/* ��ȡһά�Ľӿ�IDʧ�� */
    TCPIP_SFE_IF_GETPORTINFOFAILFOR3DIM,/* ��ȡ��ά�Ľӿ�IDʧ�� */
    TCPIP_SFE_IF_PARA_NULL_GET,     /* ָ���ӿ�ID��ȡ�ӿ���Ϣʱ����Ĳ���ΪNULL */
    TCPIP_SFE_IF_IFID_POINTER_NULL_SETARPMISSSWITCH,   /* ���ýӿ�ARP MISS����ʱ,����Ľӿ�ID����ΪNULL */
    TCPIP_SFE_IF_IFID_POINTER_NULL_SETREDUCETTLSWITCH, /* ���ýӿ�Reduce TTL����ʱ,����Ľӿ�ID����ΪNULL */
    TCPIP_SFE_IF_ERRPORTTYPE_SFEPORT,       /* ��֧�ִ��ֽӿ����� */
    TCPIP_SFE_IF_ERRPORTTYPE_CONTROLPORT,       /* ��֧�ִ��ֽӿ����� */
}CTLIFERRCODE_E;

/* physical��ַ���� */
#ifndef TCPIP_SFE_MAC_LEN
#define TCPIP_SFE_MAC_LEN 6
#endif

/* PPI�·��˿����� */
#define TCPIP_SFE_PORT_PPI     0
/* FABRIC�˿� */
#define TCPIP_SFE_PORT_FABRIC  1
/* SPI4�˿� */
#define TCPIP_SFE_PORT_SPI4    2

/* �ӿ�����״̬UP */
#define TCPIP_SFE_PHY_STATUS_UP   1
/* �ӿ�����״̬DOWN */
#define TCPIP_SFE_PHY_STATUS_DOWN 2

/* �ӿ�IPV4Э��״̬UP */
#define TCPIP_SFE_LINE4_STATUS_UP   1
/* �ӿ�IPV4Э��״̬DOWN */
#define TCPIP_SFE_LINE4_STATUS_DOWN 2

/* �ӿ�IPV6Э��״̬UP */
#define TCPIP_SFE_LINE6_STATUS_UP   1
/* �ӿ�IPV6Э��״̬DOWN */
#define TCPIP_SFE_LINE6_STATUS_DOWN 2

/* �ӿ�ת������ʱ�ݼ�TTLֵ */
#define SFE_IF_REDUCETTL_ENABLE      1
/* �ӿ�ת������ʱ���ݼ�TTLֵ */
#define SFE_IF_REDUCETTL_DISABLE     0

/* ȥʹ��ARP MISS���� */
#define SFE_ETH_ARP_MISS_DISABLE          1
/* ��ȥʹ��ARP MISS���� */
#define SFE_ETH_ARP_MISS_NOT_DISABLE      0

/* �ӿ���Ϣ��Դ�ڿ�����PPI�·� */
#define SFE_IF_SOURCE_PPI     0
/* �ӿ���Ϣ��Դ�ڲ�Ʒ���� */
#define SFE_IF_SOURCE_PRODUCT 1

/* ֱ�ӵ��ÿ�����ӿڴ���/ɾ��/���½ӿڵĽӿ�����ö�ٶ��� */
typedef enum enumTCPIP_SFE_IF_TYPE
{
    TCPIP_SFE_IF_NULL = 0,
    TCPIP_SFE_IF_INLOOPBACK,
    TCPIP_SFE_IF_LOOPBACK,
    TCPIP_SFE_IF_ETH,
    TCPIP_SFE_IF_PPP,

    TCPIP_SFE_IF_TYPEMAX = 8
}TCPIP_SFE_IF_TYPE_E;

/* IF�����������Ӧ�Ŀ�����������ò������� */
typedef enum enumTcpipSfeIfOperType
{
    TCPIP_SFE_IF_CREATE,      /* �ӿڴ��� */
    TCPIP_SFE_IF_DELETE,      /* �ӿ�ɾ�� */
    TCPIP_SFE_IF_SETMTU,      /* ����MTU */
    TCPIP_SFE_IF_UP,          /* �ӿ�UP */
    TCPIP_SFE_IF_DOWN,        /* �ӿ�DOWN*/
    TCPIP_SFE_IF_SETMAC,      /* ���ýӿ�physical��ַ */
    TCPIP_SFE_IF_VRF_BIND,    /* �ӿڰ󶨵�VRF */
    TCPIP_SFE_IF_VRF_UNBIND,  /* �ӿ�ȥ��VRF */

    TCPIP_SFE_IF_OPER_MAX     /* IF�������ò���������Ч�߽�ֵ,�Ժ������������ڴ�ǰ���� */
}TCPIP_SFE_IF_OPER_TYPE_E;

/* �ӿ���ϢID,��֤SFE_IFID��TCPIP_SFE_IFID�ṹ��Ա����С����һ�� */
typedef struct tagTCPIP_SFE_IFID
{
    UINT8   u8PortType;        /* �˿�����,�μ�TCPIP_SFE_IF_TYPE_E */
    UINT8   u8FrameID;         /* ���,ȫF��ʾ��ʹ�� */
    UINT16  u16SlotID;         /* �߼���λ��,ȫF��ʾ��ʹ�� */
    UINT16  u16PortNo;         /* �߼��˿ں�,һάģʽ��ϵͳ�˿ڱ��Ψһ,��άģʽ����ͬһ��ͬһ��λ��Ψһ,��ֵ������ */
    UINT16  u16lSubPortNo;     /* �Ӷ˿ں�,Ŀǰδʹ��,Ԥ�� */
}TCPIP_SFE_IFID;

/* �ӿ���Ϣ�ṹ,��֤SFE_INTERFACE_INFO_S��TCPIP_SFE_INTF_S�ṹ��Ա����С����һ�� */
typedef struct tagTCPIP_SFE_INTF
{
    TCPIP_SFE_IFID stIfID;          /* �ӿ�ID */
    UINT32   u32IfIndex;            /* �ӿ�����,ACLģ����Ҫ,��Ʒ��û�нӿ�������ֱ����0 */
    UINT32   u32VrfIndex;           /* VRF���� */
    UINT32   u32LinkType;           /* �˿ڵ���·������,ĿǰԤ��,��0 */
    UINT32   u32PhyStatus;          /* �˿�����״̬,ֵ:TCPIP_SFE_PHY_STATUS_UP,TCPIP_SFE_PHY_STATUS_DOWN */
    UINT32   u32LineStatus;         /* IPV4��·״̬,ֵ:TCPIP_SFE_LINE4_STATUS_UP,TCPIP_SFE_LINE4_STATUS_DOWN */
    UINT32   u32Line6Status;        /* IPV6��·״̬,ֵ:TCPIP_SFE_LINE6_STATUS_UP,TCPIP_SFE_LINE6_STATUS_DOWN */
    UINT32   u32Baud;               /* �˿ڵĲ����� */
    UINT32   u32MTU;                /* �˿ڵ�MTU */
    UINT32   u32ReduceTTL;          /* �ӿ�ת������TTL�Ƿ��1,SFE_NO(0):��ʾ����Ҫ�ݼ�TTL,SFE_YES(1):��ʾ��Ҫ�ݼ�TTL */
    UINT8    u8MacAddr[TCPIP_SFE_MAC_LEN];/* physical��ַ */
    UINT8    u8Attribute;           /* �ӿ�����Fabric/spi4��,ֵ:TCPIP_SFE_PORT_FABRIC,TCPIP_SFE_PORT_SPI4 */
    UINT8    u8Origin;              /* �ӿڴ�����Դ,��Ʒ����Ҫ��д */
    UINT32   u32IsDisableArpMiss;   /* �ӿ��Ƿ���Ҫȥʹ��ARP MISS����,ֻ����̫����Ч */
}TCPIP_SFE_INTF_S;

/*******************************ROUTE·����غ�,ö��,�ṹ�ȶ���**********************************/
/* ROUTEģ������� */
enum enumTcpipSfeRouteCode
{
    TCPIP_SFE_RT_SUCCESS = 0,           /* 0 ·�ɲ����ɹ� */
    TCPIP_SFE_RT_ERR_BEGIN = TCPIP_SFE_ROUTE_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_RT_NULL_POINTER,          /* 1 �������Ϊ�� */
    TCPIP_SFE_RT_OPER,                  /* 2 �������ʹ��� */
    TCPIP_SFE_RT_REG_FILTER_HOOK_NULL,  /* ע��·�ɹ��˻ص�Ϊ�� */
    TCPIP_SFE_RT_PARA_NULL_GET,         /* ָ��VRF��IP��ȡ·����Ϣʱ����Ĳ���ΪNULL */
};

/* ·���������� */
typedef enum enumTcpipSfeRouteOperType
{
    TCPIP_SFE_FIB4_ADD = 0,      /* ·������ */
    TCPIP_SFE_FIB4_DEL,          /* ·��ɾ�� */

    TCPIP_SFE_FIB4_OPER_MAX      /* FIB�������ò���������Ч�߽�ֵ,�Ժ������������ڴ�ǰ���� */
}TCPIP_SFE_ROUTE_OPER_TYPE_E;

/* ·����Դ�� */
#define TCPIP_SFE_ROUTE_PPI_DOWN         0   /* ������VISP�·�·�� */
#define TCPIP_SFE_ROUTE_PRO_DOWN         1   /* ��Ʒ����·�·�� */

/*·�ɱ��*/
enum ROUTE_FLAG
{
    TCPIP_SFE_ROUTE_UP        = 0x1,    /* ·�ɿ��� */
    TCPIP_SFE_ROUTE_GATEWAY   = 0x2,    /* ���·��, �޴˱����Ϊֱ��·�� */
    TCPIP_SFE_ROUTE_HOST      = 0x4,    /* ����·�ɣ��޴˱����Ϊ����·�� */
    TCPIP_SFE_ROUTE_DYNAMIC   = 0x10,   /* ��̬·�� */
    TCPIP_SFE_ROUTE_STATIC    = 0x800,  /* ��̬·�� */
    TCPIP_SFE_ROUTE_BLACKHOLE = 0x1000, /* �ڶ�·�ɣ���ʾ��Ҫ�������� */
};

#define TCPIP_SFE_OPEN_ALL_VRF 0xFFFFFFFF     /* ȫFʱ��ʾopenȫ����VRF [TCPIP_SFE_OpenTable] */

/* �û�����·�ɱ������ݽṹ */
typedef struct tagTCPIP_SFE_ROUTE
{
    UINT32    u32VrfIndex;          /* ʵ������,�û��������*/
    UINT32    u32DstIp;             /* Ŀ�ĵ�ַ,�����ֽ���,�û�������� */
    UINT32    u32Nexthop;           /* ��һ��,,�����ֽ���,�û�������� */
    TCPIP_SFE_IFID  stOutIf;        /* ���ӿ���Ϣ,�û�������� */
    UINT32    u32LocalIp;           /* ���س��ӿڵ�ַ,,�����ֽ���,��ʹ�����0 */
    UINT32    u32Flags;             /* ·�ɱ��,�û�����ָ�� */
    UINT32    u32Origin;            /* ��Դ,,����ʱ��ʹ�����0,��ȡʱ,TCPIP_SFE_ROUTE_PRO_DOWN��ʾ��Ʒ���;TCPIP_SFE_ROUTE_PPI_DOWN��ʾ�п�������� */
    UINT32    u32ATIndex;           /* �������ݲ�ʹ��*/
    UINT8     u8DstPrefixLength;    /* Ŀ�ĵ�ַ���볤�ȣ��û�������� */
    UINT8     u8LocalPrefixLength;  /* ���س��ӿڵ�ַ���볤��,��ʹ�����0 */
    UINT16    u16RTPri;             /* ·�����ȼ�,�û�����ָ��,��ָ�����0 */
}TCPIP_SFE_ROUTE_S;

/*******************************ARP��غ�,ö��,�ṹ�ȶ���**********************************/
/* ARPģ������� */
typedef enum enumTcpipSfeArpErrCode
{
    TCPIP_SFE_ARP_OK,                       /* �����ɹ� */
    TCPIP_SFE_ARP_ERR_BEGIN = TCPIP_SFE_ARP_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_ARP_PARA_NULL,                /* ����ARPʱ����NULLָ�� */
    TCPIP_SFE_ARP_OPERTYPE_INVALID,         /* ����ARPʱ����Ĳ������Ͳ��Ϸ� */
    TCPIP_SFE_ARP_MISS_GET_IFINDEX_FAIL,    /* ���ݽӿ���Ϣ��ȡ�ӿ�����ʧ�� */
    TCPIP_SFE_ARP_MISS_CALL_NOTIFY_FAIL,    /* ���ÿ�����ARP MISS֪ͨ����֪ͨʧ�� */
    TCPIP_SFE_ARP_PARA_NULL_GET,            /* ָ��VRF��IP��ȡBFD�Ự��Ϣʱ����Ĳ���ΪNULL */
    TCPIP_SFE_ARP_MISS_ETHARP_NOT_INIT,     /* ������֪ͨ������ARP MISSʱ,������ETHARPģ��û��ע�� */
}TCPIP_SFE_ARP_ERR_CODE_E;

/* ARP�����������Ӧ�Ŀ�����������ò������� */
typedef enum enumTcpipSfeArpOperType
{
    TCPIP_SFE_ARP_ADD,      /* ����ARP���� */
    TCPIP_SFE_ARP_DEL,      /* ɾ��ARP���� */

    TCPIP_SFE_ARP_OPER_MAX  /* ARP�������ò���������Ч�߽�ֵ,�Ժ������������ڴ�ǰ���� */
}TCPIP_SFE_ARP_OPER_TYPE_E;

/* ARP�ڵ���Դ�ڿ�����PPI�·� */
#define SFE_ARP_SOURCE_PPI 0
/* ARP�ڵ���Դ�ڿ������Ʒ����,��Ϊ�������ĳЩ�ӿڿ�����VISP�ǿ�������,������Ҫ��Ʒֱ������ */
#define SFE_ARP_SOURCE_PRODUCT 1

/* ��̬ARP��־ */
#define SFE_ARP_STATIC_ARPNODE 1
/* ��̬ARP��־ */
#define SFE_ARP_DYNAMIC_ARPNODE 0

/* ARP�����������Ӧ�Ŀ��������ò����ṹ */
typedef struct tagTCPIP_SFE_ARP
{
    TCPIP_SFE_IFID  stIfID;                         /* ��ARP���������Ľӿ� */
    UINT32          u32VrfIndex;                    /* IP����VRF */
    UINT32          u32IpAddr;                      /* ��ַ�������ֽ��� */
    UINT8           u8MacAddr[TCPIP_SFE_MAC_LEN];   /* physical��ַ */
    UINT8           u8StaticFlag;                   /* ����̬ARP��־,�����ýӿڸ��ֶ���Ч,�û�����SFE_ARP_STATIC_ARPNODE
                                                       ȡֵ��Χ:SFE_ARP_STATIC_ARPNODE��SFE_ARP_DYNAMIC_ARPNODE */
    UINT8           u8Source;                       /* ARP�������Դ,�����ýӿڸ��ֶ���Ч,�û���ֱ����SFE_ARP_SOURCE_PPI
                                                       ȡֵ��Χ:SFE_ARP_SOURCE_PPI��SFE_ARP_SOURCE_PRODUCT */
}TCPIP_SFE_ARP_S;

/*******************************BFD��غ�,ö��,�ṹ�ȶ���**********************************/
/* BFDģ������� */
typedef enum enumTcpipSfeBfdErrCode
{
    TCPIP_SFE_BFD_OK,                       /* �����ɹ� */
    TCPIP_SFE_BFD_ERR_BEGIN = TCPIP_SFE_BFD_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_BFD_PARA_NULL_PPI,            /* PPI����BFDʱ����Ĳ���ΪNULL */
    TCPIP_SFE_BFD_PARA_NULL_GET,            /* ָ��VRF�ͻỰID��ȡBFD�Ự��Ϣʱ����Ĳ���ΪNULL */
    TCPIP_SFE_BFD_NOTIFY_DOWN_FUNC_NULL,    /* ������̽�⵽BFD DOWN���õĿ�����֪ͨ��������δע�� */
    TCPIP_SFE_BFD_PARA_NULL_GETSTAT,        /* ��ȡBFDͳ����Ϣʱ,�������Ϊ�� */
}TCPIP_SFE_BFD_ERR_CODE_E;

/* �����κ���֤��BFD���Ʊ��ĳ��� */
#define SFE_BFD_LEN_AUTH_NONE       24

/* ����BFD�Ự */
#define SFE_BFD_SINGLE_HOP_SESS     0
/* ����BFD�Ự */
#define SFE_BFD_MULTI_HOP_SESS      1

/* BFD�Ự״̬DOWN */
#define SFE_BFD_SESS_STATE_DOWN     0
/* BFD�Ự״̬UP */
#define SFE_BFD_SESS_STATE_UP       1

/* IPv4 BFD�Ự */
#define SFE_BFD_SESS_IPV4           0
/* IPv6 BFD�Ự */
#define SFE_BFD_SESS_IPV6           1

/* BFD�ļ��ģʽ,Ŀǰ������ֻ֧�ֲ���ECHO���ܵ��첽ģʽSFE_BFD_DETECT_ASYNC_WOECHO */
/* CAUTION: ��ö�ٶ�����Ҫ�������BFD_DETECT_MODE_E���屣��һ�� */
typedef enum enumSFE_BFD_DETECT_MODE
{
    SFE_BFD_DETECT_ASYNC_WECHO = 0,                 /* ��ECHO���ܵ��첽ģʽ */
    SFE_BFD_DETECT_ASYNC_WOECHO,                    /* ����ECHO���ܵ��첽ģʽ */
    SFE_BFD_DETECT_DEMAND_WECHO,                    /* ��ECHO���ܵĲ�ѯģʽ */
    SFE_BFD_DETECT_DEMAND_WOECHO,                   /* ����ECHO���ܵĲ�ѯģʽ */
    SFE_BFD_DETECT_MODE_MAX                         /* ���ģʽ�������Чֵ */
}SFE_BFD_DETECT_MODE_E;

/* ��ַ��Ϣ�ṹ���� */
typedef union unTCPIP_SFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4��ַ */
    UINT32 u32IPv6[4];    /* IPv6��ַ */
}TCPIP_SFE_IPADDR_UN;

/* BFD�Ự��Ϣ */
typedef struct tagTCPIP_SFE_BFD_SESS_INFO
{
    UINT32 u32VrfIndex;                  /* �Ự���ڵ�VRF */
    UINT32 u32SessionId;                 /* BFD�ỰID */
    UINT32 u32SessIsUp;                  /* �Ự�Ƿ�UP��־:UP/DOWN */
    UINT32 u32DetectMode;                /* ʵ�ʵļ��ģʽ */
    UINT32 u32TxInterval;                /* ����ʵ�ʵķ���ʱ����,ms */
    UINT32 u32DetectInterval;            /* ����ʵ�ʵļ����,ms */
    UINT32 u32DetectMult;                /* ����ʵ�ʵļ�ⱶ�� */
    UINT32 u32MyDiscriminator;           /* ���˱�ʶ�� */
    UINT32 u32YourDiscriminator;         /* �Զ˱�ʶ�� */
    UINT32 u32IpVer;                     /* IP�汾��ʶ:0--��ʾ��IPv4 BFD;1--��ʾ��IPv6 BFD */
    TCPIP_SFE_IPADDR_UN unDstIPAddr;     /* �Զ˵�ַ,������ */
    TCPIP_SFE_IPADDR_UN unSrcIPAddr;     /* ���˵�ַ,������ */
    UINT32 u32TTL;                       /* TTL */
    UINT32 u32DstUdpPort;                /* UDPĿ�Ķ˿ں�,����Ϊ3784,����Ϊ4784,������ */
    UINT32 u32SrcUdpPort;                /* UDPԴ�˿ں�,ֵΪ49151+X(X>0),������ */
    UINT32 u32Tos;                       /* TOSֵ */
    UINT32 u32IsMultiHop;                /* BFD�����Ự��־,Ҫ���ڿ�������ݽӿ�����ת���� */
    TCPIP_SFE_IFID stSendIfID;           /* �Ự�ĳ��ӿ���Ϣ,����ʱ��Ч,����ʱ��Ч */

    CHAR szCtlPkt[SFE_BFD_LEN_AUTH_NONE];/* �Ự��BFD���Ʊ���,������,ֵΪ�û�����ֵ */
}TCPIP_SFE_BFD_SESS_INFO_S;

/* BFD�Ựͳ����Ϣ ,���Ӹýṹ�����ֶ�,��Ҫ������ʾ�ӿں���0�ӿ� */
typedef struct tagSFE_SESS_BFD_STATISTIC
{
    UINT32 u32Bfd_ToOwnDetectPkt;                       /* BFD�����սᱨ��ͳ�� */
    UINT32 u32Bfd_SendTotalPkt;                           /* BFD�Ự���ͱ����ܼ��� */
    UINT32 u32Bfd_SendSuccessPkt;                       /* ���˻ỰUP,BFD�ɹ����ͱ���ͳ�� */
    UINT32 u32Bfd_ToCtrlSessNotUp;                      /* �������Ӧ�Ự״̬û��UPʱ,�Ͻ�������ͳ�� */
    UINT32 u32Bfd_ToCtrlPktStateNotUp;                  /* BFD�����е�״̬��ΪBFD_STATE_UP(3)ʱ,�Ͻ�������ͳ�� */
    UINT32 u32Bfd_ToCtrlPktPollFlagSet;                 /* BFD�����е�P��־��λʱ,�Ͻ�������ͳ�� */
    UINT32 u32Bfd_ToCtrlPktFinalFlagSet;                /* BFD�����е�F��־��λʱ,�Ͻ�������ͳ�� */

    UINT32 u32Bfd_DropVrfNotMatch;                      /* ���˻ỰUP,�յ�����vrf�ͱ��˻Ựvrf��һ�¶���ͳ�� */
    UINT32 u32Bfd_DropDstIpNotMatch;                    /* ���˻ỰUP,�յ�����Ŀ��IP�ͻỰԴIP��һ�¶���ͳ�� */
    UINT32 u32Bfd_DropSrcIpNotMatch;                    /* ���˻ỰUP,�յ�����ԴIP�ͻỰĿ��IP��һ�¶���ͳ�� */
    UINT32 u32Bfd_DropSingleHopTTL;                     /* ���˻ỰUP,�����Ự�յ�����TTL����255����ͳ�� */

    UINT32 u32Bfd_DropPortTypeNotMatch;                 /* ���˻ỰUP,�����Ự�յ����Ľӿ����ͺͱ��˴����Ự�ӿ����Ͳ�һ�¶���ͳ�� */
    UINT32 u32Bfd_DropFrameIDNotMatch;                  /* ���˻ỰUP,�����Ự�յ����Ŀ�źͱ��˴����Ự������Ͳ�һ�¶���ͳ�� */
    UINT32 u32Bfd_DropSlotIDNotMatch;                   /* ���˻ỰUP,�����Ự�յ����Ĳۺźͱ��˴����Ự�ۺ����Ͳ�һ�¶���ͳ�� */
    UINT32 u32Bfd_DropPortNumNotMatch;                  /* ���˻ỰUP,�����Ự�յ����Ķ˿ںźͱ��˴����Ự�˿ںŲ�һ�¶���ͳ�� */

    UINT32 u32Bfd_DetectDownNotifyOk;                   /* ̽�ⶨʱ����ʱ,�ϱ�������Down���� */
    UINT32 u32Bfd_DetectDownNotifyFail;                 /* ̽�ⶨʱ����ʱ,�ϱ�������Downʧ�ܴ��� */

    UINT32 u32Bfd_AbnormalGetSessRecvPkt;               /* �յ�BFD����,��pool�л�ȡBFD�Ựʧ���쳣ͳ�� */
    UINT32 u32Bfd_AbnormalGetSessAtSendTimer;           /* ���Ͷ�ʱ����ʱ,��pool�л�ȡBFD�Ựʧ���쳣ͳ�� */
    UINT32 u32Bfd_AbnormalGetSessAtDetectTimer;         /* ̽�ⶨʱ����ʱ,,��pool�л�ȡBFD�Ựʧ���쳣ͳ�� */

}SFE_BFD_SESS_STATISTIC_S;


/*******************************ICMP��غ�,ö��,�ṹ�ȶ���**********************************/
/* ICMPģ������� */
enum enumTcpipSfeIcmpErrCode
{
    TCPIP_SFE_ICMP_OK,
    TCPIP_SFE_ICMP_ERR_BEGIN = TCPIP_SFE_ICMP_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_ICMP_SET_SWITCH_ERR,    /* 1 ���÷���ICMP���Կ��طǷ� */
    TCPIP_SFE_ICMP_GET_NULL_POINT,    /* 2 ��ȡ����ICMP���Կ��ز���Ϊ�� */
};

/* �رշ���ICMP����� */
#define SFE_ICMP_SEND_OFF           0x00000000
/* �������ɴ����Ĵ� */
#define SFE_ICMP_HOST_UNREACH_ON    0x00000001
/* TTLΪ0����Ĵ� */
#define SFE_ICMP_TTL_ZERO_ON        0x00000002
/* ���Ƭ��������DF��־ */
#define SFE_ICMP_NEED_FRAG_ON       0x00000004
/* �򿪷�������ICMP����� */
#define SFE_ICMP_SEND_ALL           (SFE_ICMP_HOST_UNREACH_ON | SFE_ICMP_TTL_ZERO_ON | SFE_ICMP_NEED_FRAG_ON)

/*******************************IP��غ�,ö��,�ṹ�ȶ���**********************************/
/* IPģ������� */
enum enumTcpipSfeIPErrCode
{
    TCPIP_SFE_IP_OK,
    TCPIP_SFE_IP_ERR_BEGIN = TCPIP_SFE_IP_BEGIN_RET_CODE,
    TCPIP_SFE_IP_GET_SRCIP_NULL_POINT,  /* 1 ��ȡԴIP Addrʱ���������Ϊ�� */
};

/*******************************POOL������غ�,ö�ٵȶ���**********************************/
/* POOL������������� */
enum enumTcpipSfeTblOperCode
{
    TCPIP_SFE_TABLE_SUCCESS = 0,           /* �����ɹ� */
    TCPIP_SFE_TABLE_ERR_BEGIN = TCPIP_SFE_TABLE_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */

    TCPIP_SFE_TABLE_OPEN_COM_NULL,         /* OPEN����,ͨ��ģ��ָ��û��ע�� */
    TCPIP_SFE_TABLE_OPEN_NULL_PTR,         /* OPEN����,����ָ��Ϊ�� */
    TCPIP_SFE_TABLE_OPEN_ALLOC,            /* OPEN����,�����ڴ�ռ�ʧ�� */
    TCPIP_SFE_TABLE_OPEN_SEND,             /* OPEN����,����������ͨ��ʧ�� */
    TCPIP_SFE_TABLE_OPEN_RECV,             /* OPEN����,������������Ϣʧ�� */
    TCPIP_SFE_TABLE_OPEN_HEADER_LEN,       /* OPEN����,����������ͨ�����Ⱥͱ��ĳ��Ȳ�һ�� */
    TCPIP_SFE_TABLE_OPEN_TOTAL_LEN,        /* OPEN����,���������泤�ȷǷ� */
    TCPIP_SFE_TABLE_OPEN_SEQ,              /* OPEN����,�������������кźͷ���ʱ���������кŲ�һ�� */
    TCPIP_SFE_TABLE_OPEN_ITEM_LEN,         /* OPEN����,���������汨����ѡ��ȷǷ� */

    TCPIP_SFE_TABLE_GET_OVER,              /* GET����,����������Ѿ���ȡ��� */
    TCPIP_SFE_TABLE_GET_COM_NULL,          /* GET����,ͨ��ģ��ָ��û��ע�� */
    TCPIP_SFE_TABLE_GET_NULL_PTR,          /* GET����,����ָ��Ϊ�� */
    TCPIP_SFE_TABLE_GET_ALLOC,             /* GET����,�����ڴ�ռ�ʧ�� */
    TCPIP_SFE_TABLE_GET_SEND,              /* GET����,����������ͨ��ʧ�� */
    TCPIP_SFE_TABLE_GET_RECV,              /* GET����,������������Ϣʧ�� */
    TCPIP_SFE_TABLE_GET_TOTAL_LEN,         /* GET����,���������泤�ȷǷ� */
    TCPIP_SFE_TABLE_GET_HEADER_LEN,        /* GET����,����������ͨ�����Ⱥͱ��ĳ��Ȳ�һ�� */
    TCPIP_SFE_TABLE_GET_SEQ,               /* GET����,�������������кźͷ���ʱ���������кŲ�һ�� */
    TCPIP_SFE_TABLE_GET_ITEM_LEN,          /* GET����,���������汨����ѡ��ȷǷ� */
    TCPIP_SFE_TABLE_GET_TABLE_DATA_LEN,    /* GET����,����������������ݳ��ȴ��� */
    TCPIP_SFE_TABLE_GET_NUM,               /* GET����,���������������Ŀ�Ƿ� */
    TCPIP_SFE_TABLE_GET_LARGE_LEN,         /* GET����,�������������ȴ����û����ݵĻ����� */

    TCPIP_SFE_TABLE_CLOSE_COM_NULL,        /* CLOSE����,ͨ��ģ��ָ��û��ע�� */
    TCPIP_SFE_TABLE_CLOSE_ALLOC,           /* CLOSE����,�����ڴ�ռ�ʧ�� */
    TCPIP_SFE_TABLE_CLOSE_SEND,            /* CLOSE����,����������ͨ��ʧ�� */
    TCPIP_SFE_TABLE_CLOSE_RECV,            /* CLOSE����,������������Ϣʧ�� */
    TCPIP_SFE_TABLE_CLOSE_TOTAL_LEN,       /* CLOSE����,���������泤�ȷǷ� */
    TCPIP_SFE_TABLE_CLOSE_HEADER_LEN,      /* CLOSE����,����������ͨ�����Ⱥͱ��ĳ��Ȳ�һ�� */
    TCPIP_SFE_TABLE_CLOSE_SEQ,             /* CLOSE����,�������������кźͷ���ʱ���������кŲ�һ�� */
    TCPIP_SFE_TABLE_CLOSE_ITEM_LEN,        /* CLOSE����,���������汨����ѡ��ȷǷ� */
};

/* POOL����������ͺ�, TCPIP_SFE_OpenTable��u32TableType����ֵ */
enum enumTableType
{
    TCPIP_SFE_TABLE_ETH,
    TCPIP_SFE_TABLE_NULL,
    TCPIP_SFE_TABLE_INLOOPBACK,
    TCPIP_SFE_TABLE_LOOPBACK,
    TCPIP_SFE_TABLE_ROUTE,
    TCPIP_SFE_TABLE_BALANCE_ROUTE,
    TCPIP_SFE_TABLE_RESOLVED_ARP,
    TCPIP_SFE_TABLE_RESOLVING_ARP,
    TCPIP_SFE_TABLE_BFD_SESSION,
    TCPIP_SFE_TABLE_MAX,
};

/*******************************PUB��غ�,ö�ٵȶ���**********************************/
/* ����ģ������� */
typedef enum enumTcpipSfePubErrCode
{
    TCPIP_SFE_PUB_OK,
    TCPIP_SFE_PUB_ERR_BEGIN = TCPIP_SFE_PUB_BEGIN_RET_CODE,
    TCPIP_SFE_GET_ACLFAKEREASS_SWITCH_POINT_NULL,       /* ��ȡACL�Ƿ���Ҫ��������м����鿪��ʱ,�������ΪNULL */
}TCPIP_SFE_PUB_ERR_CODE_E;

/*******************************ά��ģ����غ�,ö�ٵȶ���**********************************/
/* ά�����ͳ����־ģ������� */
typedef enum enumTcpipSfeDebugErrCode
{
    TCPIP_SFE_DEBUG_OK,                       /* �����ɹ� */
    TCPIP_SFE_DEBUG_ERR_BEGIN = TCPIP_SFE_DEBUG_BEGIN_RET_CODE,/* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    TCPIP_SFE_GET_DEBUGSWITCH_POINT_NULL,               /* 1  ��ȡ���Կ���ʱ����Ϊ��ָ�� */
    TCPIP_SFE_SET_MSGOREVENT_DEBUG_PARA_ERR,            /* 2  ������Ϣ���¼����Կ���ʱ,�������� */
    TCPIP_SFE_GET_MSGOREVENT_DEBUG_PARA_NULL,           /* 3  ��ȡ����������������Ϣ���¼����Կ���ʱָ��Ϊ�� */
    TCPIP_SFE_GET_VERBOSE_DEBUG_NULL_POINT,             /* 4  ��ȡ��ϸ���Եı��Ĵ����ͱ��ĸ��� */

    TCPIP_SFE_GET_STAT_MANUALINFO_POINT_NULL,           /* 5  ��ȡȫ��ͳ����Ϣʱ,������ֶ�ͳ��ָ��ΪNULL */
    TCPIP_SFE_GET_STAT_AUTOINFO_POINT_NULL,             /* 6  ��ȡȫ��ͳ����Ϣʱ,������Զ�ͳ��ָ��ΪNULL */
    TCPIP_SFE_GET_STAT_GETMANUALNULL,                   /* 7  ��ȡȫ��ͳ����Ϣʱ,���������ȡ��ȫ���ֶ�ͳ����Ϣָ��ΪNULL */
    TCPIP_SFE_GET_STAT_GETAUTONULL,                     /* 8  ��ȡȫ��ͳ����Ϣʱ,���������ȡ��ȫ���Զ�ͳ����Ϣָ��ΪNULL */
    TCPIP_SFE_GET_MANUSTATBYVCPU_POINT_NULL,            /* 9  ��ȡָ��VCPU��ȫ���ֶ�ͳ����Ϣʱ,�����ָ��ΪNULL */
    TCPIP_SFE_GET_MANUSTATBYVCPU_VCPU_INVALID,          /* 10 ��ȡָ��VCPU��ȫ���ֶ�ͳ����Ϣʱ,�����VCPU ID���Ϸ� */
    TCPIP_SFE_GET_MANUSTATBYVCPU_GETMANUALNULL,         /* 11 ��ȡָ��VCPU��ȫ���ֶ�ͳ����Ϣʱ,���������ȡ��ȫ���ֶ�ͳ����Ϣָ��ΪNULL */

    TCPIP_SFE_GET_FLOWSTAT_SWITCH_POINT_NULL,           /* 12 ��ȡ��ͳ�ƿ���ʱ,�����ָ�� */
    TCPIP_SFE_GET_FLOWSTAT_RULENUM_POINT_NULL,          /* 13 ��ȡ��ͳ�ƹ�����ʱ,�����ָ�� */

    TCPIP_SFE_GET_FLOWSTATRULE_RULEPOINT_NULL,          /* 14 ��ȡ��ͳ�ƹ���ʱ,����Ĵ�Ż�ȡ���������ռ�ָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATRULE_NUMPOINT_NULL,           /* 15 ��ȡ��ͳ�ƹ���ʱ,�������Ҫ��ȡ�Ĺ�����Ŀָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATRULE_GETRULENULL,             /* 16 ��ȡ��ͳ�ƹ���ʱ,���������ȡ����ͳ�ƹ���ָ��ΪNULL */

    TCPIP_SFE_GET_FLOWSTATINFO_RULEPOINT_NULL,          /* 17 ��ȡ��ͳ����Ϣʱ,�����������ָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_MANUALINFOPOINT_NULL,    /* 18 ��ȡ��ͳ����Ϣʱ,������ֶ���ͳ����Ϣָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_AUTOINFOPOINT_NULL,      /* 19 ��ȡ��ͳ����Ϣʱ,������Զ���ͳ����Ϣָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETRULENULL,             /* 20 ��ȡ��ͳ����Ϣʱ,���������ȡ����ͳ�ƹ���ָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETMANUALNULL,           /* 21 ��ȡ��ͳ����Ϣʱ,���������ȡ���ֶ���ͳ��ָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_GETAUTONULL,             /* 22 ��ȡ��ͳ����Ϣʱ,���������ȡ���Զ���ͳ��ָ��ΪNULL */
    TCPIP_SFE_GET_FLOWSTATINFO_NOT_EXIST,               /* 23 ��ȡ��ͳ����Ϣʱ,ָ���������򲻴��� */


}TCPIP_SFE_DEBUG_ERR_CODE_E;

/*******************************������غ�,ö�ٵȶ���**********************************/
/* �쳣������Ϣ���λ���� */
#define SFE_DEBUG_TYPE_ERROR        0x0001
/* ��ڳ��ڵ�����Ϣ���λ���� */
#define SFE_DEBUG_TYPE_INOUT        0x0002
/* ��Ҫ�������̵�����Ϣ���λ���� */
#define SFE_DEBUG_TYPE_PROC         0x0004
/* ��ϸ������Ϣ���λ����*/
#define SFE_DEBUG_TYPE_VERBOSE      0x0008

/* �����е������Ϳ��� */
#define SFE_DEBUG_TYPE_ALL \
    (SFE_DEBUG_TYPE_ERROR | SFE_DEBUG_TYPE_INOUT | SFE_DEBUG_TYPE_PROC | SFE_DEBUG_TYPE_VERBOSE)

/* ��IPFWDģ����Կ��� */
#define SFE_DEBUG_MODULE_IPFWD     0x00000001
/* ��ICMPģ����Կ��� */
#define SFE_DEBUG_MODULE_ICMP      0x00000002
/* ��BFDģ����Կ��� */
#define SFE_DEBUG_MODULE_BFD       0x00000004
/* �򿪵�ǰȫ��ģ��ĵ��Կ���,Notice:��ǰֻ����IPFED/ICMP/BFD����ģ��,������IR��ģ��*/
#define SFE_DEBUG_MODULE_ALL       (SFE_DEBUG_MODULE_IPFWD | SFE_DEBUG_MODULE_ICMP | SFE_DEBUG_MODULE_BFD)

/* ��ϸ������Ϣ�������Ĭ��ֵ,��ʾһ����ӡ */
#define SFE_VERBOSE_DEBUG_DEFAULT_COUNT         0xFFFFFFFF
/* ��ϸ���Ա�����Ϣ����Ĭ��ֵ,��λ:�ֽ� */
#define SFE_VERBOSE_DEBUG_PACKET_DEFAULT_LEN    128

/*******************************ͳ����غ�,ö�ٵȶ���**********************************/
/* ������֧�ֵ����VCPU���� */
#define SFE_VCPU_MAX_NUM  32

/* ��ʾ��VCPU�ֶ�ͳ��ֵ֮�� */
#define SFE_SHOW_TOTAL_MANUAL_STATISTIC  0xFFFFFFFF

/* ��ͳ�ƹ������ò����Ĳ������� */
typedef enum enumSfeFlowStatisticRuleOperType
{
    SFE_FLOWSTATISTIC_ADD,      /* �����ͳ�ƹ��� */
    SFE_FLOWSTATISTIC_DEL,      /* ɾ����ͳ�ƹ��� */
    SFE_FLOWSTATISTIC_DELALL,   /* ɾ��������ͳ�ƹ��� */

    SFE_FLOWSTATISTIC_OPER_MAX  /* ��ͳ�ƹ������ò���������Ч�߽�ֵ,�Ժ������������ڴ�ǰ���� */
}SFE_FLOWSTATISTIC_RULE_OPER_TYPE_E;

/* ��ͳ�ƿ��ش� */
#define  SFE_FLOWSTAT_SWITCH_ON     1
/* ��ͳ�ƿ��عر� */
#define  SFE_FLOWSTAT_SWITCH_OFF    0

/* �������е�VRFͨ��ֵ,��Ϊ��ֵʱ,��ʾ����VRF��ƥ�� */
#define SFE_FLOWSTAT_VRF_ALL        0xFFFFFFFF
/* �������е�Э���ͨ��ֵ,��Ϊ��ֵʱ,��ʾ����Э��Ŷ�ƥ�� */
#define SFE_FLOWSTAT_PROTO_ALL      0xFFFFFFFF
/* �������еĵ�ַͨ��ֵ,��Ϊ��ֵʱ,��ʾ����IP��ƥ�� */
#define SFE_FLOWSTAT_IP_ALL         0
/* �������еĶ˿ں�ͨ��ֵ,��Ϊ��ֵʱ,��ʾ���ж˿ںŶ�ƥ�� */
#define SFE_FLOWSTAT_PORT_ALL       0

/* ��ͳ�ƹ���ṹ����,��ͳ�ƹ��������Ҫ���û���ɾ��һ��������������һ��ʱ��(һ��������Э��ջ����ͣ�������ʱ��,
   ����6s,)֮����������������,������ܴ��ڶ�˲������������,ͳ��ֵ���ܲ�׼ȷ */
typedef struct  tagTCPIP_SFE_FlowStatisticRule
{
    UINT32              u32FlowStatId;        /* ��ͳ��ID,���ʱ��Ϊ�������,ɾ��ʱ���Ը�ֵ,��0����,��ȡʱ��ʾ��ͳ��ID,��0��ʼ��� */
    UINT32              u32VrfIndex;          /* VRF����,������ */
    TCPIP_SFE_IPADDR_UN unSrcIp;              /* ԴIP,������ */
    TCPIP_SFE_IPADDR_UN unDstIp;              /* Ŀ��IP,������ */
    UINT32              u32ProNo;             /* Э���,ȡֵ��Χ[0,255] */
    UINT16              u16SrcPort;           /* Դ�˿ں�,������,ֻ��Э��ΪUDP��TCPʱ��Ч,����Э���ʱ��Ч�û�ֱ����0���� */
    UINT16              u16DstPort;           /* Ŀ�Ķ˿ں�,������,ֻ��Э��ΪUDP��TCPʱ��Ч,����Э���ʱ��Ч�û�ֱ����0���� */
}TCPIP_SFE_FLOWSTATISTIC_RULE_S;

/* �������ֶ�ͳ����ͳ�ƽṹ���� */
typedef struct  tagSFE_IPSFEStatistic
{
    UINT64  dwLink_In;                      /* �������ͳ�� */
    UINT64  dwEth_In;                       /* eth�������ͳ�� */
    UINT64  dwNet_In;                       /* net�������ͳ�� */
    UINT64  dwIcmp_Out;                     /* �����������icmp�����ͳ�� */

    UINT64  dwArp_Deliver;                  /* ARP���ʹ���ͳ�� */
    UINT64  dwIpOpt_Deliver;                /* IPѡ�������ͳ�� */
    UINT64  dwIpBroadcast_Deliver;          /* �㲥��������ͳ�� */
    UINT64  dwIpMulticast_Deliver;          /* �ಥ��������ͳ�� */
    UINT64  dwNonFrag_Deliver;              /* ���ؽ��յķǷ�Ƭ��OSPF��BFD�����Ͻ�FWD�ַ�ͳ�� */
    UINT64  dwFragHaveFakeReassed_Deliver;  /* �������յķ�Ƭ�����Ѿ��������ط��������Ͻ�FWD�ַ�ͳ�� */
    UINT64  dwOspf_Deliver;                 /* OSPF���ʹ���ͳ�� */
    UINT64  dwUpToCtrlPlane;                /* ���Ϳ�����ͳ�� */

    UINT64  dwFakeReass_NetSuccess;         /* ���������м�����ɹ�FWD�ַ�ͳ�� */
    UINT64  dwFakeReass_LinkSuccess;        /* ����·����м�����ɹ�����ͳ�� */
    UINT64  dwFakeReass_InFragNum;          /* ���м�����ķ�Ƭ������ */
    UINT64  dwFakeReass_OutFragNum;         /* ������ɹ��ķ�Ƭ���ĸ��� */
    UINT64  dwReass_InFragNum;              /* ����������ķ�Ƭ���ĸ��� */
    UINT64  dwReass_OutReassPktNum;         /* ������ɹ����ص��������ĸ��� */

    UINT64  dwNet_Out;                      /* net���ͳ���ͳ�� */
    UINT64  dwEth_Out;                      /* eth���ͳ���ͳ��,������������ */

    UINT64  dwFrag_InNum;                   /* ��Ƭ����������� */
    UINT64  dwFrag_OutNum;                  /* ��Ƭ���ĳ������� */

    UINT64  dwFakeRease_resv;               /* ���з�Ƭ���鴦��,������ȥ����ͳ�� */
    UINT64  dwArpMiss_Resv;                 /* ARP����ʧ��,���汨�Ĳ�����ȥ����ͳ�� */

    UINT64  dwArp_ArpSearchIn;              /* ARP�������ͳ�� */
    UINT64  dwArp_HaveNormalArp;            /* ARP���ҳɹ�ͳ��(��������ARP) */
    UINT64  dwArp_HaveFakeArp;              /* ARP���Ҵ���ARP��Ԫͳ��(����������ARP��������ԪARP) */
    UINT64  dwArp_NoArp;                    /* ARP���Ҳ�����ARPͳ��(�Ȳ���������ARPҲ��������ԪARP) */
    UINT64  dwArp_ReNotifyArpMissSuccess;   /* ARP���Ҵ���ARP��Ԫʱ�����ϱ�ARP MISS�ɹ� */
    UINT64  dwArp_SendCachePktSuccess;      /* ����ARP��Ԫ�ڵ�ʱ,���ͻ��汨�ĳɹ� */

    UINT64  dwIcmp_RecvErrIcmpPkt;          /* �յ�ICMP�����,����������ĵĸ��� */
    UINT64  dwIcmp_RecvNoFirstFrg;          /* �յ����Ĳ�����Ƭ,����������ĵĸ��� */
    UINT64  dwIcmp_RecvBroadOrMultiPkt;     /* �յ��㲥��ಥ��,����������ĵĸ��� */
    UINT64  dwIcmp_RecvSrcIpErr;            /* �յ��ı���ԴIP���󣬲���������ĵĸ��� */
    UINT64  dwIcmp_SendUnreachHostNum;      /* �����������ɴﱨ�ĸ��� */
    UINT64  dwIcmp_SendNeedFragNum;         /* �������Ƭ�����ò���Ƭ����ĸ��� */
    UINT64  dwIcmp_SendTimeExceededNum;     /* ��������ʱ�䳬ʱ����ĸ��� */

    UINT64  dwBfd_In;                       /* BFD������ڱ���ͳ�� */
    UINT64  dwBfd_ToCtrlSessIdZero;         /* BFD�����е�ulYourDisctorΪ0ʱ,�Ͻ�������ͳ�� */
    UINT64  dwBfd_ToCtrlSessNotUp;          /* �������Ӧ�Ự״̬û��UPʱ,�Ͻ�������ͳ�� */
    UINT64  dwBfd_ToCtrlPktStateNotUp;      /* BFD�����е�״̬��ΪBFD_STATE_UP(3)ʱ,�Ͻ�������ͳ�� */
    UINT64  dwBfd_ToCtrlPktPollFlagSet;     /* BFD�����е�P��־��λʱ,�Ͻ�������ͳ�� */
    UINT64  dwBfd_ToCtrlPktFinalFlagSet;    /* BFD�����е�F��־��λʱ,�Ͻ�������ͳ�� */
    UINT64  dwBfd_ToOwnDetectPkt;           /* BFD�����սᱨ��ͳ�� */
    UINT64  dwBfd_DetectUp;                 /* BFD̽�⵽�Ự������ͳ�� */
    UINT64  dwBfd_DetectDownNotifyOk;       /* BFD̽�⵽�ỰDOWN��֪ͨ������ɹ���ͳ�� */
    UINT64  dwBfd_EncapsualeLinkHeader;     /* BFD��װ��·��ͷ������ͳ�� */
    UINT64  dwBfd_SendPktOk;                /* BFD���ķ��ͳɹ�ͳ�� */

    UINT64  dwFwd_HaveHandle;               /* ���ؽ��ձ��Ľ���FWD����,FWD�����Ѿ�����VISPֱ�ӷ��� */
    UINT64  dwFwd_NotHandle;                /* ���ؽ��ձ��Ľ���FWD����,FWD����δ����VISP�����洦�� */
    UINT64  dwFwd_Drop;                     /* ���ؽ��ձ��Ľ���FWD����,FWD�����Ѿ�����VISP�ͷű��� */

    UINT64  dwAcl_Forward_NotHandle;        /* ת�����Ľ���ACL����,ACL����δ����VISP����ת������ */
    UINT64  dwAcl_Forward_Drop;             /* ת�����Ľ���ACL����,ACL�����Ѵ���VISP�ͷű��� */

    UINT64  dwAcl_UpDeliver_NotHandle;      /* �Ͻ������漰FWD���Ľ���ACL����,ACL����δ����VISP����ת������ */
    UINT64  dwAcl_UpDeliver_Drop;           /* �Ͻ������漰FWD���Ľ���ACL����,ACL����δ����VISP����ת������ */

    UINT64  dwNet_BadVers;                  /* IP�汾�Ŵ��� */
    UINT64  dwNet_BadHLen;                  /* IP�ײ�������Ч�ı��ĸ��� */
    UINT64  dwNet_BadLen;                   /* IP�ײ���IP���ݳ��Ȳ�һ�µı��ĸ��� */
    UINT64  dwNet_TooShort;                 /* ������Ч���ݳ��ȵı��ĸ��� */
    UINT64  dwNet_BadSum;                   /* У��ʹ���ı����� */
    UINT64  dwNet_NoProto;                  /* ���в�֧�ֵ�Э��ı��ĸ��� */
    UINT64  dwNet_NoRoute;                  /* û��·�� */
    UINT64  dwNet_TTLExceed;                /* TTLС��1,�޷�ת���ı��ĸ��� */  
    UINT64  dwNet_CantFrag;                 /* ����DF��λ�������ı����� */

}SFE_IPSFE_STATISTIC_S;

/* Ŀǰֻ��Խ���ת�����̽�����ͳ�Ƽ���㴦��,�������͵ı���,��ICM,BFD�����ݲ����� */
/* ��������ͳ���ֶ�ͳ����ͳ�ƽṹ���� */
typedef struct  tagSFE_IPSFEFlowStatistic
{
    UINT32  u32Link_FlowStat_TcpUdpNonFrag;         /* Link��·��TCP��UDP�Ƿ�Ƭ������ͳ����ʼ�� */
    UINT32  u32Link_FlowStat_TcpUdpFrag;            /* Link��·��TCP��UDP��Ƭ������ͳ����ʼ�� */
    UINT32  u32Link_FlowStat_NonTcpUdp;             /* Link��·���TCP��UDP������ͳ����ʼ�� */

    UINT32  u32Eth_In;                              /* eth��̫�������ͳ�� */
    UINT32  u32Net_In;                              /* net�����������ͳ�� */
    UINT32  u32Acl_ForwardHook_NotHandle;           /* �Ͻ������洦����,ACL���Ӻ������������������������ */
    UINT32  u32Acl_ForwardHook_Drop;                /* �Ͻ������洦����,ACL���Ӻ����������������涪������ */
    UINT32  u32Frag_In;                             /* ��Ƭ������ڱ���ͳ�� */
    UINT32  u32Frag_Out;                            /* ��Ƭ������ڱ���ͳ�� */
    UINT32  u32Net_Out;                             /* net����㷢�ͳ���ͳ�� */
    UINT32  u32Arp_HaveFakeArp;                     /* ARP���Ҵ���ARP��Ԫͳ��(����������ARP��������ԪARP) */
    UINT32  u32Arp_NoArp;                           /* ARP���Ҳ�����ARPͳ��(�Ȳ���������ARPҲ��������ԪARP) */
    UINT32  u32Arp_FakeArpCachePkt;                 /* ������ԪARPʱ���汨��ͳ�� */
    UINT32  u32Arp_NoArpCachePkt;                   /* ������ARP(�Ȳ���������ARPҲ��������ԪARP)ʱ���汨��ͳ�� */
    UINT32  u32Eth_Out;                             /* eth��̫���ͳ���ͳ�� */
    UINT32  u32Arp_SendCachePkt;                    /* ����ARP��Ԫ���汨��ͳ�� */

    UINT32  u32UpDeliver_IpOpt;                     /* ��IPѡ��ı��Ĵ��Ͻ������洦�� */
    UINT32  u32UpDeliver_IpBroadcast;               /* IP�㲥���Ĵ��Ͻ������洦�� */
    UINT32  u32UpDeliver_IpMulticast;               /* IP�ಥ���Ĵ��Ͻ������洦�� */
    UINT32  u32UpDeliver_IpOspf;                    /* IP OSPF���Ĵ��Ͻ������洦�� */
    UINT32  u32UpDeliver_IpLocalInFragHaveFakeReass;/* �������յķ�Ƭ�����Ѿ��������ط���������Ͻ������洦�� */
    UINT32  u32UpDeliver_IpLocalInFragNetFakeReass; /* �������յķ�Ƭ�������������м�����ɹ����Ͻ������洦�� */
    UINT32  u32UpDeliver_IpLocalInNotFragOspfBfd;   /* �������յķǷ�Ƭ��OSPF��BFD���Ĵ��Ͻ������洦�� */
    UINT32  u32LocalIn_UpDeliverFwdHook_HaveHandle; /* �Ͻ������洦����,���ؽ��ձ���FWD���Ӻ����������������潫���Ľ����������� */
    UINT32  u32LocalIn_UpDeliverFwdHook_NotHandle;  /* �Ͻ������洦����,���ؽ��ձ���FWD���Ӻ���������������������Ͻ������洦�� */
    UINT32  u32LocalIn_UpDeliverFwdHook_Drop;       /* �Ͻ������洦����,���ؽ��ձ���FWD���Ӻ����������������涪������ */
    UINT32  u32Acl_UpDeliverHook_NotHandle;         /* �Ͻ������洦����,ACL���Ӻ������������������������ */
    UINT32  u32Acl_UpDeliverHook_Drop;              /* �Ͻ������洦����,ACL���Ӻ����������������涪������ */
    UINT32  u32UpToCtrlPlane;                       /* ���Ϳ�����ͳ�� */

    UINT32  u32Bfd_In;                              /* BFD������ڱ���ͳ�� */
    UINT32  u32Bfd_ToOwnDetectPkt;                  /* BFD�����������սᱨ��ͳ�� */
    UINT32  u32UpDeliver_BfdSessIdZero;             /* BFD�����е�ulYourDisctorΪ0,���Ͻ������洦��ͳ�� */
    UINT32  u32UpDeliver_BfdSessNotUp;              /* �������Ӧ�Ự״̬û��UP,���Ͻ������洦��ͳ�� */
    UINT32  u32UpDeliver_BfdPktStateNotUp;          /* BFD�����е�״̬��ΪBFD_STATE_UP(3),���Ͻ������洦��ͳ�� */
    UINT32  u32UpDeliver_BfdPktPollFlagSet;         /* BFD�����е�P��־��λ,���Ͻ������洦��ͳ�� */
    UINT32  u32UpDeliver_BfdPktFinalFlagSet;        /* BFD�����е�F��־��λ,���Ͻ������洦��ͳ�� */
}SFE_IPSFE_FLOWSTATISTIC_S;

/*�ɲ�������Ϣ��ṹ����*/
/*tml base start*/
#define SFE_STAT_BASE    0x0000
/*tml base end*/

/* �����洦���Զ�ͳ����ID */
enum SFE_STAT_ID_IPFWD_ENUM
{
    /*tml code start*/
    SFE_STAT_IPFWD_0000 = SFE_STAT_BASE,  /*Ԥ��,��ʹ��*/
    SFE_STAT_IPFWD_0001,
    SFE_STAT_IPFWD_0002,
    SFE_STAT_IPFWD_0003,
    SFE_STAT_IPFWD_0004,
    SFE_STAT_IPFWD_0005,
    SFE_STAT_IPFWD_0006,
    SFE_STAT_IPFWD_0007,
    SFE_STAT_IPFWD_0008,
    SFE_STAT_IPFWD_0009,
    SFE_STAT_IPFWD_000A,
    SFE_STAT_IPFWD_000B,
    SFE_STAT_IPFWD_000C,
    SFE_STAT_IPFWD_000D,
    SFE_STAT_IPFWD_000E,
    SFE_STAT_IPFWD_000F,
    SFE_STAT_IPFWD_0010,
    SFE_STAT_IPFWD_0011,
    SFE_STAT_IPFWD_0012,
    SFE_STAT_IPFWD_0013,
    SFE_STAT_IPFWD_0014,
    SFE_STAT_IPFWD_0015,
    SFE_STAT_IPFWD_0016,
    SFE_STAT_IPFWD_0017,
    SFE_STAT_IPFWD_0018,
    SFE_STAT_IPFWD_0019,
    SFE_STAT_IPFWD_001A,
    SFE_STAT_IPFWD_001B,
    SFE_STAT_IPFWD_001C,
    SFE_STAT_IPFWD_001D,
    SFE_STAT_IPFWD_001E,
    SFE_STAT_IPFWD_001F,
    SFE_STAT_IPFWD_0020,
    SFE_STAT_IPFWD_0021,
    SFE_STAT_IPFWD_0022,
    SFE_STAT_IPFWD_0023,
    SFE_STAT_IPFWD_0024,
    SFE_STAT_IPFWD_0025,
    SFE_STAT_IPFWD_0026,
    SFE_STAT_IPFWD_0027,
    SFE_STAT_IPFWD_0028,
    SFE_STAT_IPFWD_0029,
    SFE_STAT_IPFWD_002A,
    SFE_STAT_IPFWD_002B,
    SFE_STAT_IPFWD_002C,
    SFE_STAT_IPFWD_002D,
    SFE_STAT_IPFWD_002E,
    SFE_STAT_IPFWD_002F,
    SFE_STAT_IPFWD_0030,
    SFE_STAT_IPFWD_0031,
    SFE_STAT_IPFWD_0032,
    SFE_STAT_IPFWD_0033,
    SFE_STAT_IPFWD_0034,
    SFE_STAT_IPFWD_0035,
    SFE_STAT_IPFWD_0036,
    SFE_STAT_IPFWD_0037,
    SFE_STAT_IPFWD_0038,
    SFE_STAT_IPFWD_0039,
    SFE_STAT_IPFWD_003A,
    SFE_STAT_IPFWD_003B,
    SFE_STAT_IPFWD_003C,
    SFE_STAT_IPFWD_003D,
    SFE_STAT_IPFWD_003E,
    SFE_STAT_IPFWD_003F,
    SFE_STAT_IPFWD_0040,
    SFE_STAT_IPFWD_0041,
    SFE_STAT_IPFWD_0042,
    SFE_STAT_IPFWD_0043,
    SFE_STAT_IPFWD_0044,
    SFE_STAT_IPFWD_0045,
    SFE_STAT_IPFWD_0046,
    SFE_STAT_IPFWD_0047,
    SFE_STAT_IPFWD_0048,
    SFE_STAT_IPFWD_0049,
    SFE_STAT_IPFWD_004A,
    SFE_STAT_IPFWD_004B,
    SFE_STAT_IPFWD_004C,
    SFE_STAT_IPFWD_004D,
    SFE_STAT_IPFWD_004E,
    SFE_STAT_IPFWD_004F,
    SFE_STAT_IPFWD_0050,
    SFE_STAT_IPFWD_0051,
    SFE_STAT_IPFWD_0052,
    SFE_STAT_IPFWD_0053,
    SFE_STAT_IPFWD_0054,
    SFE_STAT_IPFWD_0055,
    SFE_STAT_IPFWD_0056,
    SFE_STAT_IPFWD_0057,
    SFE_STAT_IPFWD_0058,
    SFE_STAT_IPFWD_0059,
    SFE_STAT_IPFWD_005A,
    SFE_STAT_IPFWD_005B,
    SFE_STAT_IPFWD_005C,
    SFE_STAT_IPFWD_005D,
    SFE_STAT_IPFWD_005E,
    SFE_STAT_IPFWD_005F,
    SFE_STAT_IPFWD_0060,
    SFE_STAT_IPFWD_0061,
    SFE_STAT_IPFWD_0062,
    SFE_STAT_IPFWD_0063,
    SFE_STAT_IPFWD_0064,
    SFE_STAT_IPFWD_0065,
    SFE_STAT_IPFWD_0066,
    SFE_STAT_IPFWD_0067,
    SFE_STAT_IPFWD_0068,
    SFE_STAT_IPFWD_0069,
    SFE_STAT_IPFWD_006A,
    SFE_STAT_IPFWD_006B,
    SFE_STAT_IPFWD_006C,
    SFE_STAT_IPFWD_006D,
    SFE_STAT_IPFWD_006E,
    SFE_STAT_IPFWD_006F,
    SFE_STAT_IPFWD_0070,
    SFE_STAT_IPFWD_0071,
    SFE_STAT_IPFWD_0072,
    SFE_STAT_IPFWD_0073,
    SFE_STAT_IPFWD_0074,
    SFE_STAT_IPFWD_0075,
    SFE_STAT_IPFWD_0076,
    SFE_STAT_IPFWD_0077,
    SFE_STAT_IPFWD_0078,
    SFE_STAT_IPFWD_0079,
    SFE_STAT_IPFWD_007A,
    SFE_STAT_IPFWD_007B,
    SFE_STAT_IPFWD_007C,
    SFE_STAT_IPFWD_007D,
    SFE_STAT_IPFWD_007E,
    SFE_STAT_IPFWD_007F,
    SFE_STAT_IPFWD_0080,
    SFE_STAT_IPFWD_0081,
    SFE_STAT_IPFWD_0082,
    SFE_STAT_IPFWD_0083,
    SFE_STAT_IPFWD_0084,
    SFE_STAT_IPFWD_0085,
    SFE_STAT_IPFWD_0086,
    SFE_STAT_IPFWD_0087,
    SFE_STAT_IPFWD_0088,
    SFE_STAT_IPFWD_0089,
    SFE_STAT_IPFWD_008A,
    SFE_STAT_IPFWD_008B,
    SFE_STAT_IPFWD_008C,
    SFE_STAT_IPFWD_008D,
    SFE_STAT_IPFWD_008E,
    SFE_STAT_IPFWD_008F,
    SFE_STAT_IPFWD_0090,
    SFE_STAT_IPFWD_0091,
    SFE_STAT_IPFWD_0092,
    SFE_STAT_IPFWD_0093,
    SFE_STAT_IPFWD_0094,
    SFE_STAT_IPFWD_0095,
    SFE_STAT_IPFWD_0096,
    SFE_STAT_IPFWD_0097,
    SFE_STAT_IPFWD_0098,
    SFE_STAT_IPFWD_0099,
    SFE_STAT_IPFWD_009A,
    SFE_STAT_IPFWD_009B,
    SFE_STAT_IPFWD_009C,
    SFE_STAT_IPFWD_009D,
    SFE_STAT_IPFWD_009E,
    SFE_STAT_IPFWD_009F,
    SFE_STAT_IPFWD_00A0,
    SFE_STAT_IPFWD_00A1,
    SFE_STAT_IPFWD_00A2,
    SFE_STAT_IPFWD_00A3,
    SFE_STAT_IPFWD_00A4,
    SFE_STAT_IPFWD_00A5,
    SFE_STAT_IPFWD_00A6,
    SFE_STAT_IPFWD_00A7,
    SFE_STAT_IPFWD_00A8,
    SFE_STAT_IPFWD_00A9,
    SFE_STAT_IPFWD_00AA,
    SFE_STAT_IPFWD_00AB,
    SFE_STAT_IPFWD_00AC,
    SFE_STAT_IPFWD_00AD,
    SFE_STAT_IPFWD_00AE,
    SFE_STAT_IPFWD_00AF,
    SFE_STAT_IPFWD_00B0,
    SFE_STAT_IPFWD_00B1,
    SFE_STAT_IPFWD_00B2,
    SFE_STAT_IPFWD_00B3,
    SFE_STAT_IPFWD_00B4,
    SFE_STAT_IPFWD_00B5,
    SFE_STAT_IPFWD_00B6,
    SFE_STAT_IPFWD_00B7,
    SFE_STAT_IPFWD_00B8,
    SFE_STAT_IPFWD_00B9,
    SFE_STAT_IPFWD_00BA,
    SFE_STAT_IPFWD_00BB,
    SFE_STAT_IPFWD_00BC,
    SFE_STAT_IPFWD_00BD,
    SFE_STAT_IPFWD_00BE,
    SFE_STAT_IPFWD_00BF,
    SFE_STAT_IPFWD_00C0,
    SFE_STAT_IPFWD_00C1,
    SFE_STAT_IPFWD_00C2,
    SFE_STAT_IPFWD_00C3,
    SFE_STAT_IPFWD_00C4,
    SFE_STAT_IPFWD_00C5,
    SFE_STAT_IPFWD_00C6,
    SFE_STAT_IPFWD_00C7,
    SFE_STAT_IPFWD_00C8,
    SFE_STAT_IPFWD_00C9,
    SFE_STAT_IPFWD_00CA,
    SFE_STAT_IPFWD_00CB,
    SFE_STAT_IPFWD_00CC,
    SFE_STAT_IPFWD_00CD,
    SFE_STAT_IPFWD_00CE,
    SFE_STAT_IPFWD_00CF,
    SFE_STAT_IPFWD_00D0,
    SFE_STAT_IPFWD_00D1,
    SFE_STAT_IPFWD_00D2,
    SFE_STAT_IPFWD_00D3,
    SFE_STAT_IPFWD_00D4,
    SFE_STAT_IPFWD_00D5,
    SFE_STAT_IPFWD_00D6,
    SFE_STAT_IPFWD_00D7,
    SFE_STAT_IPFWD_00D8,
    SFE_STAT_IPFWD_00D9,
    SFE_STAT_IPFWD_00DA,
    SFE_STAT_IPFWD_00DB,
    SFE_STAT_IPFWD_00DC,
    SFE_STAT_IPFWD_00DD,
    SFE_STAT_IPFWD_00DE,
    SFE_STAT_IPFWD_00DF,
    SFE_STAT_IPFWD_00E0,
    SFE_STAT_IPFWD_00E1,
    SFE_STAT_IPFWD_00E2,
    SFE_STAT_IPFWD_00E3,
    SFE_STAT_IPFWD_00E4,
    SFE_STAT_IPFWD_00E5,
    SFE_STAT_IPFWD_00E6,
    SFE_STAT_IPFWD_00E7,
    SFE_STAT_IPFWD_00E8,
    SFE_STAT_IPFWD_00E9,
    SFE_STAT_IPFWD_00EA,
    SFE_STAT_IPFWD_00EB,
    SFE_STAT_IPFWD_00EC,
    SFE_STAT_IPFWD_00ED,
    SFE_STAT_IPFWD_00EE,
    SFE_STAT_IPFWD_00EF,
    SFE_STAT_IPFWD_00F0,
    SFE_STAT_IPFWD_00F1,
    SFE_STAT_IPFWD_00F2,
    SFE_STAT_IPFWD_00F3,
    SFE_STAT_IPFWD_00F4,
    SFE_STAT_IPFWD_00F5,
    SFE_STAT_IPFWD_00F6,
    SFE_STAT_IPFWD_00F7,
    SFE_STAT_IPFWD_00F8,
    SFE_STAT_IPFWD_00F9,
    SFE_STAT_IPFWD_00FA,
    SFE_STAT_IPFWD_00FB,
    SFE_STAT_IPFWD_00FC,
    SFE_STAT_IPFWD_00FD,
    SFE_STAT_IPFWD_00FE,
    SFE_STAT_IPFWD_00FF,
    SFE_STAT_IPFWD_0100,
    SFE_STAT_IPFWD_0101,
    SFE_STAT_IPFWD_0102,
    SFE_STAT_IPFWD_0103,
    SFE_STAT_IPFWD_0104,
    SFE_STAT_IPFWD_0105,
    SFE_STAT_IPFWD_0106,
    SFE_STAT_IPFWD_0107,
    SFE_STAT_IPFWD_0108,
    SFE_STAT_IPFWD_0109,
    SFE_STAT_IPFWD_010A,
    SFE_STAT_IPFWD_010B,
    SFE_STAT_IPFWD_010C,
    SFE_STAT_IPFWD_010D,
    SFE_STAT_IPFWD_010E,
    SFE_STAT_IPFWD_010F,
    SFE_STAT_IPFWD_0110,
    SFE_STAT_IPFWD_0111,
    SFE_STAT_IPFWD_0112,
    SFE_STAT_IPFWD_0113,
    SFE_STAT_IPFWD_0114,
    SFE_STAT_IPFWD_0115,
    SFE_STAT_IPFWD_0116,
    SFE_STAT_IPFWD_0117,
    SFE_STAT_IPFWD_0118,
    SFE_STAT_IPFWD_0119,
    SFE_STAT_IPFWD_011A,
    SFE_STAT_IPFWD_011B,
    SFE_STAT_IPFWD_011C,
    SFE_STAT_IPFWD_011D,
    SFE_STAT_IPFWD_011E,
    SFE_STAT_IPFWD_011F,
    SFE_STAT_IPFWD_0120,
    SFE_STAT_IPFWD_0121,
    SFE_STAT_IPFWD_0122,
    SFE_STAT_IPFWD_0123,
    SFE_STAT_IPFWD_0124,
    SFE_STAT_IPFWD_0125,
    SFE_STAT_IPFWD_0126,
    SFE_STAT_IPFWD_0127,
    SFE_STAT_IPFWD_0128,
    SFE_STAT_IPFWD_0129,
    SFE_STAT_IPFWD_012A,
    SFE_STAT_IPFWD_012B,
    SFE_STAT_IPFWD_012C,
    SFE_STAT_IPFWD_012D,
    SFE_STAT_IPFWD_012E,
    SFE_STAT_IPFWD_012F,
    SFE_STAT_IPFWD_0130,
    SFE_STAT_IPFWD_0131,
    SFE_STAT_IPFWD_0132,
    SFE_STAT_IPFWD_0133,
    SFE_STAT_IPFWD_0134,
    SFE_STAT_IPFWD_0135,
    SFE_STAT_IPFWD_0136,
    SFE_STAT_IPFWD_0137,
    SFE_STAT_IPFWD_0138,
    SFE_STAT_IPFWD_0139,
    SFE_STAT_IPFWD_013A,
    SFE_STAT_IPFWD_013B,
    SFE_STAT_IPFWD_013C,
    SFE_STAT_IPFWD_013D,
    SFE_STAT_IPFWD_013E,
    SFE_STAT_IPFWD_013F,
    SFE_STAT_IPFWD_0140,
    SFE_STAT_IPFWD_0141,
    SFE_STAT_IPFWD_0142,
    SFE_STAT_IPFWD_0143,
    SFE_STAT_IPFWD_0144,
    SFE_STAT_IPFWD_0145,
    SFE_STAT_IPFWD_0146,
    SFE_STAT_IPFWD_0147,
    SFE_STAT_IPFWD_0148,
    SFE_STAT_IPFWD_0149,
    SFE_STAT_IPFWD_014A,
    SFE_STAT_IPFWD_014B,
    SFE_STAT_IPFWD_014C,
    SFE_STAT_IPFWD_014D,
    SFE_STAT_IPFWD_014E,
    SFE_STAT_IPFWD_014F,
    SFE_STAT_IPFWD_0150,
    SFE_STAT_IPFWD_0151,
    SFE_STAT_IPFWD_0152,
    SFE_STAT_IPFWD_0153,
    SFE_STAT_IPFWD_0154,
    SFE_STAT_IPFWD_0155,
    SFE_STAT_IPFWD_0156,
    SFE_STAT_IPFWD_0157,
    SFE_STAT_IPFWD_0158,
    SFE_STAT_IPFWD_0159,
    SFE_STAT_IPFWD_015A,
    SFE_STAT_IPFWD_015B,
    SFE_STAT_IPFWD_015C,
    SFE_STAT_IPFWD_015D,
    SFE_STAT_IPFWD_015E,
    SFE_STAT_IPFWD_015F,
    SFE_STAT_IPFWD_0160,
    SFE_STAT_IPFWD_0161,
    SFE_STAT_IPFWD_0162,
    SFE_STAT_IPFWD_0163,
    SFE_STAT_IPFWD_0164,
    SFE_STAT_IPFWD_0165,
    SFE_STAT_IPFWD_0166,
    SFE_STAT_IPFWD_0167,
    SFE_STAT_IPFWD_0168,
    SFE_STAT_IPFWD_0169,
    SFE_STAT_IPFWD_016A,
    SFE_STAT_IPFWD_016B,
    SFE_STAT_IPFWD_016C,
    SFE_STAT_IPFWD_016D,
    SFE_STAT_IPFWD_016E,
    SFE_STAT_IPFWD_016F,
    SFE_STAT_IPFWD_0170,
    SFE_STAT_IPFWD_0171,
    SFE_STAT_IPFWD_0172,
    SFE_STAT_IPFWD_0173,
    SFE_STAT_IPFWD_0174,
    SFE_STAT_IPFWD_0175,
    SFE_STAT_IPFWD_0176,
    SFE_STAT_IPFWD_0177,
    SFE_STAT_IPFWD_0178,
    SFE_STAT_IPFWD_0179,
    SFE_STAT_IPFWD_017A,
    SFE_STAT_IPFWD_017B,
    SFE_STAT_IPFWD_017C,
    SFE_STAT_IPFWD_017D,
    SFE_STAT_IPFWD_017E,
    SFE_STAT_IPFWD_017F,
    SFE_STAT_IPFWD_0180,
    SFE_STAT_IPFWD_0181,
    SFE_STAT_IPFWD_0182,
    SFE_STAT_IPFWD_0183,
    SFE_STAT_IPFWD_0184,
    SFE_STAT_IPFWD_0185,
    SFE_STAT_IPFWD_0186,
    SFE_STAT_IPFWD_0187,
    SFE_STAT_IPFWD_0188,
    SFE_STAT_IPFWD_0189,
    SFE_STAT_IPFWD_018A,
    SFE_STAT_IPFWD_018B,
    SFE_STAT_IPFWD_018C,
    SFE_STAT_IPFWD_018D,
    SFE_STAT_IPFWD_018E,
    SFE_STAT_IPFWD_018F,
    SFE_STAT_IPFWD_0190,
    SFE_STAT_IPFWD_0191,
    SFE_STAT_IPFWD_0192,
    SFE_STAT_IPFWD_0193,
    SFE_STAT_IPFWD_0194,
    SFE_STAT_IPFWD_0195,
    SFE_STAT_IPFWD_0196,
    SFE_STAT_IPFWD_0197,
    SFE_STAT_IPFWD_0198,
    SFE_STAT_IPFWD_0199,
    SFE_STAT_IPFWD_019A,
    SFE_STAT_IPFWD_019B,
    SFE_STAT_IPFWD_019C,
    SFE_STAT_IPFWD_019D,
    SFE_STAT_IPFWD_019E,
    SFE_STAT_IPFWD_019F,
    SFE_STAT_IPFWD_01A0,
    SFE_STAT_IPFWD_01A1,
    SFE_STAT_IPFWD_01A2,
    SFE_STAT_IPFWD_01A3,
    SFE_STAT_IPFWD_01A4,
    SFE_STAT_IPFWD_01A5,
    SFE_STAT_IPFWD_01A6,
    SFE_STAT_IPFWD_01A7,
    SFE_STAT_IPFWD_01A8,
    SFE_STAT_IPFWD_01A9,
    SFE_STAT_IPFWD_01AA,
    SFE_STAT_IPFWD_01AB,
    SFE_STAT_IPFWD_01AC,
    SFE_STAT_IPFWD_01AD,
    SFE_STAT_IPFWD_01AE,
    SFE_STAT_IPFWD_01AF,
    SFE_STAT_IPFWD_01B0,
    SFE_STAT_IPFWD_01B1,
    SFE_STAT_IPFWD_01B2,
    SFE_STAT_IPFWD_01B3,
    SFE_STAT_IPFWD_01B4,
    SFE_STAT_IPFWD_01B5,
    SFE_STAT_IPFWD_01B6,
    SFE_STAT_IPFWD_01B7,
    SFE_STAT_IPFWD_01B8,
    SFE_STAT_IPFWD_01B9,
    SFE_STAT_IPFWD_01BA,
    SFE_STAT_IPFWD_01BB,
    SFE_STAT_IPFWD_01BC,
    SFE_STAT_IPFWD_01BD,
    SFE_STAT_IPFWD_01BE,
    SFE_STAT_IPFWD_01BF,
    SFE_STAT_IPFWD_01C0,
    SFE_STAT_IPFWD_01C1,
    SFE_STAT_IPFWD_01C2,
    SFE_STAT_IPFWD_01C3,
    SFE_STAT_IPFWD_01C4,
    SFE_STAT_IPFWD_01C5,
    SFE_STAT_IPFWD_01C6,
    SFE_STAT_IPFWD_01C7,
    SFE_STAT_IPFWD_01C8,
    SFE_STAT_IPFWD_01C9,
    SFE_STAT_IPFWD_01CA,
    SFE_STAT_IPFWD_01CB,
    SFE_STAT_IPFWD_01CC,
    SFE_STAT_IPFWD_01CD,
    SFE_STAT_IPFWD_01CE,
    SFE_STAT_IPFWD_01CF,
    SFE_STAT_IPFWD_01D0,
    SFE_STAT_IPFWD_01D1,
    SFE_STAT_IPFWD_01D2,
    SFE_STAT_IPFWD_01D3,
    SFE_STAT_IPFWD_01D4,
    SFE_STAT_IPFWD_01D5,
    SFE_STAT_IPFWD_01D6,
    SFE_STAT_IPFWD_01D7,
    SFE_STAT_IPFWD_01D8,
    SFE_STAT_IPFWD_01D9,
    SFE_STAT_IPFWD_01DA,
    SFE_STAT_IPFWD_01DB,
    SFE_STAT_IPFWD_01DC,
    SFE_STAT_IPFWD_01DD,
    SFE_STAT_IPFWD_01DE,
    SFE_STAT_IPFWD_01DF,
    SFE_STAT_IPFWD_01E0,
    SFE_STAT_IPFWD_01E1,
    SFE_STAT_IPFWD_01E2,
    SFE_STAT_IPFWD_01E3,
    SFE_STAT_IPFWD_01E4,
    SFE_STAT_IPFWD_01E5,
    SFE_STAT_IPFWD_01E6,
    SFE_STAT_IPFWD_01E7,
    SFE_STAT_IPFWD_01E8,
    SFE_STAT_IPFWD_01E9,
    SFE_STAT_IPFWD_01EA,
    SFE_STAT_IPFWD_01EB,
    SFE_STAT_IPFWD_01EC,
    SFE_STAT_IPFWD_01ED,
    SFE_STAT_IPFWD_01EE,
    SFE_STAT_IPFWD_01EF,
    SFE_STAT_IPFWD_01F0,
    SFE_STAT_IPFWD_01F1,
    SFE_STAT_IPFWD_01F2,
    SFE_STAT_IPFWD_01F3,
    SFE_STAT_IPFWD_01F4,
    SFE_STAT_IPFWD_01F5,
    SFE_STAT_IPFWD_01F6,
    SFE_STAT_IPFWD_01F7,
    SFE_STAT_IPFWD_01F8,
    SFE_STAT_IPFWD_01F9,
    SFE_STAT_IPFWD_01FA,
    SFE_STAT_IPFWD_01FB,
    SFE_STAT_IPFWD_01FC,
    SFE_STAT_IPFWD_01FD,
    SFE_STAT_IPFWD_01FE,
    SFE_STAT_IPFWD_01FF,
    SFE_STAT_IPFWD_0200,
    SFE_STAT_IPFWD_0201,
    SFE_STAT_IPFWD_0202,
    SFE_STAT_IPFWD_0203,
    SFE_STAT_IPFWD_0204,
    SFE_STAT_IPFWD_0205,
    SFE_STAT_IPFWD_0206,
    SFE_STAT_IPFWD_0207,
    SFE_STAT_IPFWD_0208,
    SFE_STAT_IPFWD_0209,
    SFE_STAT_IPFWD_020A,
    SFE_STAT_IPFWD_020B,
    SFE_STAT_IPFWD_020C,
    SFE_STAT_IPFWD_020D,
    SFE_STAT_IPFWD_020E,
    SFE_STAT_IPFWD_020F,
    SFE_STAT_IPFWD_0210,
    SFE_STAT_IPFWD_0211,
    SFE_STAT_IPFWD_0212,
    SFE_STAT_IPFWD_0213,
    SFE_STAT_IPFWD_0214,
    SFE_STAT_IPFWD_0215,
    SFE_STAT_IPFWD_0216,
    SFE_STAT_IPFWD_0217,
    SFE_STAT_IPFWD_0218,
    SFE_STAT_IPFWD_0219,
    SFE_STAT_IPFWD_021A,
    SFE_STAT_IPFWD_021B,
    SFE_STAT_IPFWD_021C,
    SFE_STAT_IPFWD_021D,
    SFE_STAT_IPFWD_021E,
    SFE_STAT_IPFWD_021F,
    SFE_STAT_IPFWD_0220,
    SFE_STAT_IPFWD_0221,
    SFE_STAT_IPFWD_0222,
    SFE_STAT_IPFWD_0223,
    SFE_STAT_IPFWD_0224,
    SFE_STAT_IPFWD_0225,
    SFE_STAT_IPFWD_0226,
    SFE_STAT_IPFWD_0227,
    SFE_STAT_IPFWD_0228,
    SFE_STAT_IPFWD_0229,
    SFE_STAT_IPFWD_022A,
    SFE_STAT_IPFWD_022B,
    SFE_STAT_IPFWD_022C,
    SFE_STAT_IPFWD_022D,
    SFE_STAT_IPFWD_022E,
    SFE_STAT_IPFWD_022F,
    SFE_STAT_IPFWD_0230,
    SFE_STAT_IPFWD_0231,
    SFE_STAT_IPFWD_0232,
    SFE_STAT_IPFWD_0233,
    SFE_STAT_IPFWD_0234,
    SFE_STAT_IPFWD_0235,
    SFE_STAT_IPFWD_0236,
    SFE_STAT_IPFWD_0237,
    SFE_STAT_IPFWD_0238,
    SFE_STAT_IPFWD_0239,
    SFE_STAT_IPFWD_023A,
    SFE_STAT_IPFWD_023B,
    SFE_STAT_IPFWD_023C,
    SFE_STAT_IPFWD_023D,
    SFE_STAT_IPFWD_023E,
    SFE_STAT_IPFWD_023F,
    SFE_STAT_IPFWD_0240,
    SFE_STAT_IPFWD_0241,
    SFE_STAT_IPFWD_0242,
    SFE_STAT_IPFWD_0243,
    SFE_STAT_IPFWD_0244,
    SFE_STAT_IPFWD_0245,
    SFE_STAT_IPFWD_0246,
    SFE_STAT_IPFWD_0247,
    SFE_STAT_IPFWD_0248,
    SFE_STAT_IPFWD_0249,
    SFE_STAT_IPFWD_024A,
    SFE_STAT_IPFWD_024B,
    SFE_STAT_IPFWD_024C,
    SFE_STAT_IPFWD_024D,
    SFE_STAT_IPFWD_024E,
    SFE_STAT_IPFWD_024F,
    SFE_STAT_IPFWD_0250,
    SFE_STAT_IPFWD_0251,
    SFE_STAT_IPFWD_0252,
    SFE_STAT_IPFWD_0253,
    SFE_STAT_IPFWD_0254,
    SFE_STAT_IPFWD_0255,
    SFE_STAT_IPFWD_0256,
    SFE_STAT_IPFWD_0257,
    SFE_STAT_IPFWD_0258,
    SFE_STAT_IPFWD_0259,
    SFE_STAT_IPFWD_025A,
    SFE_STAT_IPFWD_025B,
    SFE_STAT_IPFWD_025C,
    SFE_STAT_IPFWD_025D,
    SFE_STAT_IPFWD_025E,
    SFE_STAT_IPFWD_025F,
    SFE_STAT_IPFWD_0260,
    SFE_STAT_IPFWD_0261,
    SFE_STAT_IPFWD_0262,
    SFE_STAT_IPFWD_0263,
    SFE_STAT_IPFWD_0264,
    SFE_STAT_IPFWD_0265,
    SFE_STAT_IPFWD_0266,
    SFE_STAT_IPFWD_0267,
    SFE_STAT_IPFWD_0268,
    SFE_STAT_IPFWD_0269,
    SFE_STAT_IPFWD_026A,
    SFE_STAT_IPFWD_026B,
    SFE_STAT_IPFWD_026C,
    SFE_STAT_IPFWD_026D,
    SFE_STAT_IPFWD_026E,
    SFE_STAT_IPFWD_026F,
    SFE_STAT_IPFWD_0270,
    SFE_STAT_IPFWD_0271,
    SFE_STAT_IPFWD_0272,
    SFE_STAT_IPFWD_0273,
    SFE_STAT_IPFWD_0274,
    SFE_STAT_IPFWD_0275,
    SFE_STAT_IPFWD_0276,
    SFE_STAT_IPFWD_0277,
    SFE_STAT_IPFWD_0278,
    SFE_STAT_IPFWD_0279,
    SFE_STAT_IPFWD_027A,
    SFE_STAT_IPFWD_027B,
    SFE_STAT_IPFWD_027C,
    SFE_STAT_IPFWD_027D,
    SFE_STAT_IPFWD_027E,
    SFE_STAT_IPFWD_027F,
    SFE_STAT_IPFWD_0280,
    SFE_STAT_IPFWD_0281,
    SFE_STAT_IPFWD_0282,
    SFE_STAT_IPFWD_0283,
    SFE_STAT_IPFWD_0284,
    SFE_STAT_IPFWD_0285,
    SFE_STAT_IPFWD_0286,
    SFE_STAT_IPFWD_0287,
    SFE_STAT_IPFWD_0288,
    SFE_STAT_IPFWD_0289,
    SFE_STAT_IPFWD_028A,
    SFE_STAT_IPFWD_028B,
    SFE_STAT_IPFWD_028C,
    SFE_STAT_IPFWD_028D,
    SFE_STAT_IPFWD_028E,
    SFE_STAT_IPFWD_028F,
    SFE_STAT_IPFWD_0290,
    SFE_STAT_IPFWD_0291,
    SFE_STAT_IPFWD_0292,
    SFE_STAT_IPFWD_0293,
    SFE_STAT_IPFWD_0294,
    SFE_STAT_IPFWD_0295,
    SFE_STAT_IPFWD_0296,
    SFE_STAT_IPFWD_0297,
    SFE_STAT_IPFWD_0298,
    SFE_STAT_IPFWD_0299,
    SFE_STAT_IPFWD_029A,
    SFE_STAT_IPFWD_029B,
    SFE_STAT_IPFWD_029C,
    SFE_STAT_IPFWD_029D,
    SFE_STAT_IPFWD_029E,
    SFE_STAT_IPFWD_029F,
    SFE_STAT_IPFWD_0300,
    SFE_STAT_IPFWD_0301,
    SFE_STAT_IPFWD_0302,
    SFE_STAT_IPFWD_0303,
    SFE_STAT_IPFWD_0304,
    SFE_STAT_IPFWD_0305,
    SFE_STAT_IPFWD_0306,
    SFE_STAT_IPFWD_0307,
    SFE_STAT_IPFWD_0308,
    SFE_STAT_IPFWD_0309,
    SFE_STAT_IPFWD_030A,
    SFE_STAT_IPFWD_030B,
    SFE_STAT_IPFWD_030C,
    SFE_STAT_IPFWD_030D,
    SFE_STAT_IPFWD_030E,
    SFE_STAT_IPFWD_030F,
    SFE_STAT_IPFWD_0310,
    SFE_STAT_IPFWD_0311,
    SFE_STAT_IPFWD_0312,
    SFE_STAT_IPFWD_0313,
    SFE_STAT_IPFWD_0314,
    SFE_STAT_IPFWD_0315,
    SFE_STAT_IPFWD_0316,
    SFE_STAT_IPFWD_0317,
    SFE_STAT_IPFWD_0318,
    SFE_STAT_IPFWD_0319,
    SFE_STAT_IPFWD_031A,
    SFE_STAT_IPFWD_031B,
    SFE_STAT_IPFWD_031C,
    SFE_STAT_IPFWD_031D,
    SFE_STAT_IPFWD_031E,
    SFE_STAT_IPFWD_031F,
    SFE_STAT_IPFWD_0320,
    SFE_STAT_IPFWD_0321,
    SFE_STAT_IPFWD_0322,
    SFE_STAT_IPFWD_0323,
    SFE_STAT_IPFWD_0324,
    SFE_STAT_IPFWD_0325,
    SFE_STAT_IPFWD_0326,
    SFE_STAT_IPFWD_0327,
    SFE_STAT_IPFWD_0328,
    SFE_STAT_IPFWD_0329,
    SFE_STAT_IPFWD_032A,
    SFE_STAT_IPFWD_032B,
    SFE_STAT_IPFWD_032C,
    SFE_STAT_IPFWD_032D,
    SFE_STAT_IPFWD_032E,
    SFE_STAT_IPFWD_032F,
    SFE_STAT_IPFWD_0330,
    SFE_STAT_IPFWD_0331,
    SFE_STAT_IPFWD_0332,
    SFE_STAT_IPFWD_0333,
    SFE_STAT_IPFWD_0334,
    SFE_STAT_IPFWD_0335,
    SFE_STAT_IPFWD_0336,
    SFE_STAT_IPFWD_0337,
    SFE_STAT_IPFWD_0338,
    SFE_STAT_IPFWD_0339,
    SFE_STAT_IPFWD_033A,
    SFE_STAT_IPFWD_033B,
    SFE_STAT_IPFWD_033C,
    SFE_STAT_IPFWD_033D,
    SFE_STAT_IPFWD_033E,
    SFE_STAT_IPFWD_033F,
    SFE_STAT_IPFWD_0340,
    SFE_STAT_IPFWD_0341,
    SFE_STAT_IPFWD_0342,
    SFE_STAT_IPFWD_0343,
    SFE_STAT_IPFWD_0344,
    SFE_STAT_IPFWD_0345,
    SFE_STAT_IPFWD_0346,
    SFE_STAT_IPFWD_0347,
    SFE_STAT_IPFWD_0348,
    SFE_STAT_IPFWD_0349,
    SFE_STAT_IPFWD_034A,
    SFE_STAT_IPFWD_034B,
    SFE_STAT_IPFWD_034C,
    SFE_STAT_IPFWD_034D,
    SFE_STAT_IPFWD_034E,
    SFE_STAT_IPFWD_034F,
    SFE_STAT_IPFWD_0350,
    SFE_STAT_IPFWD_0351,
    SFE_STAT_IPFWD_0352,
    SFE_STAT_IPFWD_0353,
    SFE_STAT_IPFWD_0354,
    SFE_STAT_IPFWD_0355,
    SFE_STAT_IPFWD_0356,
    SFE_STAT_IPFWD_0357,
    SFE_STAT_IPFWD_0358,
    SFE_STAT_IPFWD_0359,
    SFE_STAT_IPFWD_035A, 
    SFE_STAT_IPFWD_035B,
    SFE_STAT_IPFWD_035C,
    SFE_STAT_IPFWD_035D,
    SFE_STAT_IPFWD_035E,
    SFE_STAT_IPFWD_035F,
    SFE_STAT_IPFWD_0360,
    SFE_STAT_IPFWD_0361,
    SFE_STAT_IPFWD_0362,
    SFE_STAT_IPFWD_0363,
    SFE_STAT_IPFWD_0364,
    SFE_STAT_IPFWD_0365,
    SFE_STAT_IPFWD_0366,
    SFE_STAT_IPFWD_0367,
    SFE_STAT_IPFWD_0368,
    SFE_STAT_IPFWD_0369,
    SFE_STAT_IPFWD_0370,
    SFE_STAT_IPFWD_0371,
    SFE_STAT_IPFWD_0372,
    SFE_STAT_IPFWD_0373,
    SFE_STAT_IPFWD_0374,
    SFE_STAT_IPFWD_0375,
    SFE_STAT_IPFWD_0376,
    SFE_STAT_IPFWD_0377,
    SFE_STAT_IPFWD_0378,
    SFE_STAT_IPFWD_0379,
    SFE_STAT_IPFWD_0380,
    SFE_STAT_IPFWD_MAX,
    /*tml code end*/
};



#ifdef  __cplusplus
}
#endif
#endif

