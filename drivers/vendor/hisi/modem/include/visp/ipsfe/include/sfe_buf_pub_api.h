

#ifndef _SFE_BUF_PUB_API_H_
#define _SFE_BUF_PUB_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ����ǰ��Ԥ��һ���ֽ����ڽṹ����,��Ԥ���ֽڱ�����MBUF_S�ṹ��Сͬ�� */
#define SFE_MBUF_RESERVE 2
/* MBUF�ṹ��С,�ṹ�ֶ�����ɾ���޸ı仯ʱ,��������汾��,���ڷ�ֹ�ں�̬(��Ʒ)���û�̬ʹ�õ�MBUFͷ�ļ���һ��.
   sizeof(SFE_MBUF_S)�ı��汾������:
   Version 1: sizeof(SFE_MBUF_S) == 160;
   Version 2: SCG��ƷTCP Proxy���������MBUF�ṹ�仯;
*/
#define SFE_MBUF_VERSION 2
/* Ŀǰ�汾MBUF�ṹ��С����Ϊ160 */
#define SFE_MBUF_STRUCT_SIZE 160
/* ��MBUFԤ����Ϊ��չģʽ(MBUF�ṹ��С������,����RPU MBUFӦ�÷�ʽ)ʱ,MBUF�ṹǰԤ��128�ֽڹ�MCUP���MBUF������Ϣʹ�� */
#define SFE_MBUF_MCUP_LEN   128

/* DB�ĳ���,��Ϊ��Ʒ������ڴ������Ʋ����ṩ̫���DB���ݿ�,�����������ƷԼ��DB���ݳ���Ϊ1600 */
#define SFE_MBUF_DATA_BLOCK1600_SIZE  1600
/* ����Ԥ������չMBUF��DB���� */
#define SFE_MBUF_DATA_BLOCK2048_SIZE  2048
/* MBUF��DBβ��Ԥ������,����LinuxЭ��ջshareinfoʹ�� */
#define SFE_MBUF_DB_TAIL_RESERVE_SIZE  512
/* ϵͳԤ���Ĳ�ʹ�õ�MBUF��Դ����:10K��,������ʱ���MBUF��Դʹ�����OS���������ձ������� */
#define SFE_MBUF_RESERVE_MBUF_NUM    10240

/* һ��ʽMBUF����ʱ,MBUFͷ��MBUF��չ��Ϣ,DBD,DB�Ƿ�ʹ�õı�� */
#define SFE_MBUF_IS_USED    0x01  /* MBUFͷ����չͷ�Ƿ�ʹ�ñ��*/
#define SFE_DBD_IS_USED     0x02  /* DBD�Ƿ�ʹ�ñ��*/
#define SFE_DB_IS_USED      0x04  /* DB�Ƿ�ʹ�ñ��*/

/* �ӿ���ϢID */
typedef struct tagSFE_MBUF_IFID
{
    UINT8   u8PortType;        /* �˿����� */
    UINT8   u8FrameID;         /* ���,ȫF��ʾ��ʹ�� */
    UINT16  u16SlotID;         /* �߼���λ��,ȫF��ʾ��ʹ�� */
    UINT16  u16PortNo;         /* �߼��˿ں�,һάģʽ��ϵͳ�˿ڱ��Ψһ����άģʽ����ͬһ��ͬһ��λ��Ψһ */
    UINT16  u16lSubPortNo;     /* �Ӷ˿ں� */
}SFE_MBUF_IFID_S;

/* ����IPѡ���IPͷ���� */
#define SFE_IP_HEADER_NO_OPT_LEN    20

/* IPͷ���� */
typedef struct tagSFE_IP
{
#if SFE_LITTLE_ENDIAN == SFE_YES
    UINT8   ip_chHLen:4;        /* header length */
    UINT8   ip_chVer: 4;        /* version */
#else
    UINT8  ip_chVer:  4;        /* version */
    UINT8  ip_chHLen: 4;        /* header length */
#endif
    UINT8   ip_chTOS;           /* type of service */
    UINT16  ip_usLen;           /* total length */
#define ip_sLen ip_usLen
    UINT16  ip_usId;            /* identification */
    UINT16  ip_usOff;           /* fragment offset field */
#define ip_sOff ip_usOff
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    UINT8   ip_chTTL;           /* time to live */
    UINT8   ip_chPr;            /* protocol */
    UINT16  ip_usSum;           /* checksum */
    UINT32  ip_stSrc;           /* source address */
    UINT32  ip_stDst;           /* destination address */
}SFE_IP_S;

/* UDPͷ�ṹ���� */
typedef struct tagSFE_UDP
{
    UINT16    u16SrcPort;        /* Դ�˿ں� */
    UINT16    u16DstPort;        /* Ŀ�Ķ˿ں� */
    INT16     i16Len;            /* UDP���� */
    UINT16    u16ChkSum;         /* UDPУ��� */
}SFE_UDP_S;

/* ������ʱ����Ϣ�ṹ���� */
typedef struct tagSFE_TimeVal
{
    UINT32 u32HighTick;       /* ��λ */
    UINT32 u32LowTick;        /* ��λ */
}SFE_TIMEVAL_S;

/* ������IP������Ϣ�ṹ���� */
typedef struct tagSFE_PKTINFO_NET
{
    UINT16 u16PktSrcPortOrIcmpType; /* ���ĵ�Դ�˿ںŻ���ICMP���ĵ�Type,�����ֽ��� */
    UINT16 u16PktDstPortOrIcmpCode; /* ���ĵ�Ŀ�Ķ˿ںŻ���ICMP���ĵ�code,�����ֽ��� */
    UINT32 u32ServiceType;          /* IPv4��IPv6���� */
}SFE_PKTINFO_NET_S;

/* ��ͳ��һ���������֧��ͬʱƥ��Ĺ����� */
#define SFE_FLOWSTAT_MATCH_MAX 7

/* �����汨����ͳ����Ϣ�ṹ���� */
typedef struct tagSFE_FLOWSTATISTIC
{
    UINT16  u16FlowStatNum;  /* ���������ͳ�������� */
    UINT16  u16FlowStat[SFE_FLOWSTAT_MATCH_MAX]; /* �����������ͳ��ID */
} SFE_FLOWSTATISTIC_S;

/* �����汨�Ĺ������Խṹ���� */
typedef struct tagSFE_PKTINFO_COMMON
{
    SFE_TIMEVAL_S Time;          /* ���ڼ��㱨�ķ��ͺ�ʱ */
    UINT32 u32LoopTimes;         /* �����������ػ����� */
    UINT32 u32VrfIndex;          /* VRF���� */
    UINT32 u32PktType;           /* ��������,��������,ת��,�㲥,�ಥ */
    UINT32 u32IsFragMent:1;      /* �ñ����Ƿ���TCP,UDP��Ƭ����,�ڽ��м������ñ�־����Ч */
    UINT32 u32IsFakeReassed:1;   /* �÷�Ƭ�����Ƿ��Ѿ������� */
    UINT32 u32IsFlowStatistic:1; /* �ñ����Ƿ���Ҫ������ͳ�� */
    UINT32 u32IsFlowDebug:1;     /* �ñ����Ƿ���Ҫ���������� */
    UINT32 u32ReserveFlag:28;    /* �����ı���ֶ� */
    SFE_FLOWSTATISTIC_S stFlowStat; /* ��ͳ����Ϣ */
    UINT32 u32DeliverType;       /* ���ͷַ�����AGENTģ��ĸ���������,��ARP.�㲥��.�ಥ��.�ַ�FWD��� */
    UINT32 u32DeliverOfflen;     /* ���ʹ���ƫ�Ƶ�ͷ���� */
} SFE_PKTINFO_COMMON_S;

/* DB����Դ */
#define SFE_MBUF_DATA_NORMAL 0  /* ����DB,ʹ��SFE�ṩ�Ĵ����ͷ�����DB MBUF�ĺ������� */
#define SFE_MBUF_DATA_ETHDRV 1  /* ����DB,�Ը�DB�Ĳ�����Ҫ���ж���Ĵ���,������������ɲ�Ʒ�ṩ(�����ͷ�,������),
                                   ��ĳЩ��������SFE��DB����������ϵͳ��DB�ڴ�,SFE����ֱ�Ӳ�����,�������������,һ���ǽ�
                                   ��������ϵͳ��DB���ݿ�����SFE��DB��,���ǲ�ƷΪ���������,ϣ��ʵ���㿽��,�����ṩ��
                                   ��һ�ַ���,SFE�ṩһ�����ݲ�Ʒ�ṩ��ϵͳDB����MBUF�ĺ���,�ú������¼��Ʒ�ṩ��һЩ
                                   ����ϵͳDB��һЩ��Ϣ,���ڲ�Ʒ�����Լ���DB,Ȼ��SFE�ڽ���MBUF��ز���ʱ��Ϊ����������Ʒ
                                   �ṩ�Ĳ�������. */
#define SFE_MBUF_DATA_PPPDRV 2  /* ����DB,�Ը�DB�Ĳ�����Ҫ���ж���Ĵ���,������������ɲ�Ʒ�ṩ,ͬ�� */



/* Mbuf�в�Ʒ������Ϣ��󳤶� */
#define SFE_MBUF_PRIVATE_DATA_LEN 64


/* ��Ʒ������Ϣ�ṹ */
typedef struct tagSFE_PKTINFO_USERPRIVATE
{
    UINT8  u8UserFlag;          /* ��Ʒ˽�б�־ */
    UINT8  u8Reserve[3];        /* �����ֶ� */
    UINT32 u32UsrPrivateLen;                            /* ��Ʒ�������ݳ��� */
    UINT8  au8PktUsrPrivate[SFE_MBUF_PRIVATE_DATA_LEN]; /* ��Ʒ�������ݻ����� */
    UINT8 *pu8UserPointer1;     /* ��Ʒ������Ϣָ��1,��ָ��ָ����ڴ��ɲ�Ʒ����������ͷ�. */
    UINT8 *pu8UserPointer2;     /* ��Ʒ������Ϣָ��2,��ָ��ָ����ڴ��ɲ�Ʒ����������ͷ�. */
}SFE_PKTINFO_USERPRIVATE_S;

/* ������������������ */
#define SFE_PKT_NO_DIRECTION_FLOW   0
/* ���б����� */
#define SFE_PKT_UP_DIRECTION_FLOW   1
/* ���б����� */
#define SFE_PKT_DOWN_DIRECTION_FLOW   2
/* Ӳ��IO�ۺ�֧�ֵ�MBUF���DB���� */
#define SFE_SGO_DB_MAX_NUM      4

/* ��¼MBUF��չ��Ϣ,������Ʒ������Ϣ��MBUF�����ֶ���Ϣ,����MBUF�����ֶ�ͳһ�ڸýṹ������ */
typedef struct tagSFE_MBUF_EXPAND
{
    UINT32 u32IpPktRcvPolicy;   /* IP���Ľ��մ������ */
    UINT32 u32PktDispatchKey;   /* ���ķַ���ĳһ���̶��˵�KEYֵ */
    UINT32 u32ConnectionId;     /* ��¼��Ʒ����ID�����ں�����չ */
    UINT32 u32FlowDirection;    /* �������������� */
    UINT32 u32IpPktLen;         /* IP���ĳ��� */
    UINT32 u32PktDataLen;       /* �����еĴ����ݳ���(����IP�ʹ����ͷ�ĳ���) */
    UINT32 u32HdrDataOffset;    /* ������ͷ���ظ����ݲ�����,�Ҳ��ܶ���.
                                   ��ʱ��¼ͷ���ظ����ݳ���,������ʱƫ�Ƶ���������Ӧ����ɴ�����ʱƫ�ر����ײ�ʱ�õ� */
    UINT32 u32TailDataOffset;   /* ������β���ظ����ݲ�����,�Ҳ��ܶ���.
                                   ��ʱ��¼β���ظ����ݳ���,������(����)�ͷ���(����)ʱ�����ܳ��Ⱥʹ����ݳ���ƫ�ƻ��õ� */
    UINT32 u32PktSrcIp;         /* ���ĵ�ԴIP,�����ֽ��� */
    UINT32 u32PktDstIp;         /* ���ĵ�Ŀ��IP,�����ֽ��� */
    UINT8  u8IpHdrLen;          /* IPͷ���� */
    UINT8  u8TransHdrLen;       /* �����ͷ�ĳ��� */
    UINT8  u8StatDirection;
    UINT8  u8Reserve;           /* Ԥ���ֶ� */    
    UINT32 u32DupPktLen;        /* TCP������ʱ��ʶ�ش����ݳ��� */
    SFE_PKTINFO_USERPRIVATE_S    stUsrPrivateData;  /* ��Ʒ������Ϣ */
    UINT64 au64SgoAddr[SFE_SGO_DB_MAX_NUM];     /* �������Ӳ��IO�ۺϵĸ�DB������ʼ��ַ */
    UINT32 au32SgoDataLen[SFE_SGO_DB_MAX_NUM];/* �������Ӳ��IO�ۺϵĸ�DB���ݳ��� */
    UINT32 u32PktTimeStamp;     /* ����L7����ʱ�Ӳ���ʱ��¼��ʱ���,����:���ջ��ͷű���ʱ��ʱ��� */
    UINT32 u32PktGenNum;        /* ����L7����ʱ�Ӳ���ʱ���������Ĳ������ */
}SFE_MBUF_EXPAND_S;

/* ���������ݿ�������DBD�ṹ����,
   Ϊ�˼���ԭ��RPU��Ʒ������MBUFӦ��(Ҫ��DBD�Ĵ�С�̶�Ϊ32�ֽ�),�ýṹ������ʾ8�ֽڶ���. */
typedef struct tagSFE_MBUF_DataBlockDescriptor
{
    UINT8 *pu8Data;                                      /* ��ǰ���ݿ������ݵ���ʼ��ַ��NULL��ʾ��Ч��������ʾ��Ч */
    UINT8 *pu8DataBlock;                                 /* ��ǰ���ݿ����ʼ��ַ��NULL��ʾ��Ч��������ʾ��Ч */
    struct tagSFE_MBUF_DataBlockDescriptor *pstPrevDBD;  /* ǰһ�����ݿ���������NULL��ʾû�� */
    struct tagSFE_MBUF_DataBlockDescriptor *pstNextDBD;  /* ��һ�����ݿ���������NULL��ʾû�� */
    VOID  *pstSysDBCtrl;                                 /* ϵͳDB��Ӧ�Ŀ��ƿ�, ��ѡ */
    UINT32 u32DataBlockSource;                           /* DB����Դ����ϸ���ͼ��Ϻ궨�� */
    UINT32 u32DataLength;                                /* ��ǰ���ݿ������ݵ��ܳ��� */
    UINT32 u32DataBlockLength;                           /* ��ǰ���ݿ���ܳ��� */
} SFE_MBUF_DATABLOCKDESCRIPTOR_S;

/* ������MBUF�ṹ���� */
typedef struct tagSFE_MBuf
{
    /* Ϊ��֧���㿽������MBUF��ǰ��ָ����밴������˳�����MBUF�ṹ����ǰ�� */
    struct tagSFE_MBuf              *pstNextMbuf;                       /* ��һ��MBuf */
    struct tagSFE_MBuf              *pstPrevMbuf;                       /* ǰһ��MBuf */
    UINT32                           u32MBufVersion;                    /* ������дΪSFE_MBUF_VERSION */
    UINT32                           u32TotalDataLength;                /* mbuf�б������ݵ��ܳ��� */
    SFE_MBUF_IFID_S                  stPhyRecvIfInfo;                   /* ����������սӿ���Ϣ */
    VOID                            *pPhyRecvLink;                      /* ����������սӿ���·ͷ��Ϣָ�� */
    VOID                            *pPhyRecvBase;                      /* ����������սӿڻ�����Ϣָ�� */

    UINT8                           *pu8LinkLayerHead;                  /* ָ���ĵ���·���ײ� */
    UINT8                           *pu8NetLayerHeader;                 /* ָ���ĵ�������ײ� */
    UINT8                           *pu8TranLayerHeader;                /* ָ���ĵĴ�����ײ� */
    SFE_MBUF_IFID_S                  stPhySendIfInfo;                   /* ���������ͽӿ���Ϣ */
    VOID                            *pPhySendLink;                      /* ���������ͽӿ���·ͷ��Ϣָ�� */
    VOID                            *pPhySendBase;                      /* ���������ͽӿڻ�����Ϣָ�� */
    SFE_MBUF_DATABLOCKDESCRIPTOR_S  *pstDBD;                            /* ��һ�����ݿ���������ַ�������ݿ�����������ĵ�һ����� */

    SFE_PKTINFO_NET_S                stPktNetInfo;                      /* ��ű�������㼰�����֮�ϵ������Ϣ */
    SFE_PKTINFO_COMMON_S             stPktCommonInfo;                   /* ��ű��ĵ�ͨ����Ϣ */

    SFE_IPADDR_UN                    unNextHopIp;                       /* ��һ����ַ */
    UINT32                           u32ModuleID;                       /* ������MBUF��ģ��ID */
    UINT32                           u32DataBlockNumber;                /* mbuf�����ݿ�ĸ��� */

    SFE_MBUF_EXPAND_S               *pstExpandInfo;                     /* ��¼MBUF��չ��Ϣ,������Ʒ������Ϣ��MBUF�����ֶ���Ϣ */

    UINT32                           u32VcpuId;                         /* ��ǰ�˺� */
    UINT32                           u32IfIndex;                        /* Linux�µ��豸�ӿ����� */
    UINT8                            u8IsUsed;                          /* MBUF����һ��ʽ����,MBUFͷ,DBD,DB,��MBUF��չ��Ϣ�Ƿ���ʹ�õı��,*/
                                                                        /* ��λ��ʾ, 1:��ʾ�ö��ڴ���ʹ��, 0:��ʾ�ö��ڴ�δʹ�� */
    UINT8                            u8UserStatFlag;
    UINT8                            au8IsReorderSend;                    /*�ж��Ƿ�����ת����*/ 
    UINT8                            au8PktReserved;  /* Ԥ�� */
} SFE_MBUF_S;


/* ����ת�����,û��ת�� */
#define SFE_PKT_NO_REORDER_SEND   0
/* ����ת�����,��ת�� */
#define SFE_PKT_REORDER_SENDED   1

/* ��ȡ����ת�����*/
#define SFE_MBUF_GET_IS_REORDER_SEND(pstMbuf) ((pstMbuf)->au8IsReorderSend)
/* ��ȡǰһ��MBUF */
#define SFE_MBUF_GET_PREV(pstMbuf) ((pstMbuf)->pstPrevMbuf)
/* ����ǰһ��MBUF */
#define SFE_MBUF_SET_PREV(pstMbuf, pstPreMbufM) ((pstMbuf)->pstPrevMbuf = (pstPreMbufM))
/* ��ȡ��һ��MBUF */
#define SFE_MBUF_GET_NEXT(pstMbuf) ((pstMbuf)->pstNextMbuf)
/* ���ú�һ��MBUF */
#define SFE_MBUF_SET_NEXT(pstMbuf, pstNextMbufM) ((pstMbuf)->pstNextMbuf = (pstNextMbufM))

/* ����MBUF�İ汾�� */
#define SFE_MBUF_SET_VERSION(pstMbuf, u32Version)(((pstMbuf)->u32MBufVersion) = (u32Version))
/* ��ȡMBUF�汾�� */
#define SFE_MBUF_GET_VERSION(pstMbuf) ((pstMbuf)->u32MBufVersion)

/* ��ȡMBUF�������ܳ��� */
#define SFE_MBUF_GET_TOTAL_DATA_LENGTH(pstMbuf) ((pstMbuf)->u32TotalDataLength)

/* ��ȡMBUF��DBD�ĸ���(��DB�ĸ���, DBD��DB��һһ��Ӧ��) */
#define SFE_MBUF_GET_DBD_NUMBER(pstMbuf) ((pstMbuf)->u32DataBlockNumber)
/* ��ȡMBUF�׸�DBD��ַ */
#define SFE_MBUF_GET_FIRST_DBD_ADDR(pstMbuf) ((pstMbuf)->pstDBD)

/* ��ȡǰһ��DBD��ַ */
#define SFE_DBD_GET_PREV(pstDBD) ((pstDBD)->pstPrevDBD)
/* ��ȡ��һ��DBD��ַ */
#define SFE_DBD_GET_NEXT(pstDBD) ((pstDBD)->pstNextDBD)

/* ��ȡDBD��Ӧ��DB��ַ */
#define SFE_DBD_GET_DB_ADDR(pstDBD) ((pstDBD)->pu8DataBlock)
/* ��ȡDBD��Ӧ��DB���� */
#define SFE_DBD_GET_DB_LENGTH(pstDBD) ((pstDBD)->u32DataBlockLength)

/* ��ȡDBD��Ӧ��������ʼ��ַ */
#define SFE_DBD_GET_DATA_ADDR(pstDBD) ((pstDBD)->pu8Data)
/* ��ȡDBD��Ӧ�����ݳ��� */
#define SFE_DBD_GET_DATA_LENGTH(pstDBD) ((pstDBD)->u32DataLength)

/* ��ȡDBD�д�ŵ�ϵͳDB���ƿ��ַ */
#define SFE_DBD_GET_SYSDB_CTRL(pstDBD) ((pstDBD)->pstSysDBCtrl)


/*
  ���RPU, ������εĺ�������:

 *ppstMbuf   *ppstDBDAddr                      pu8DBAddr         pu8DataAddr
     |            |                                |                  |
     V____________V________________________________V__________________V_________________________
     |            |                                |                  |                  |      |
     | SFE_MBUF_S | SFE_MBUF_DATABLOCKDESCRIPTOR_S |        64        |    ��·�㱨��    | ��ѡ |
     |____________|________________________________|__________________|__________________|______|
     |                                             |                  |                  |      |
     |                                             |                  |<-- u32DataLen -->|      |
     |                                             |                                            |
     |                                             |<---------------- u32DBLen ---------------->|
     |                                                                                          |
     |<--------------------------------------- �����ڴ� --------------------------------------->|

*/

/* ������䲻ʹ�õ��ֶ� */
#define SFE_NOT_USE_NUM 0xFFFFFFFF

/* �����Чֵ */
#define SFE_FRAME_NOT_USE 0xFF
/* �ۺ���Чֵ */
#define SFE_SLOT_NOT_USE 0xFFFF
/* �Ӷ˿ں���Чֵ */
#define SFE_SUBPORT_NOT_USE 0xFFFF

/* Modify by huangqingxin177429, at 2012-05-04. �޸�ԭ��: pclint�澯���� */
/* һά�ӿ�ģʽ��, ���ñ�����ӿڵ���Ϣ */
#define SFE_MBUF_SET_RX_IFINFO(pstMbuf, u8RcvPortType, u16RcvPortID) \
{ \
    ((pstMbuf)->stPhyRecvIfInfo.u8PortType) = (u8RcvPortType); \
    ((pstMbuf)->stPhyRecvIfInfo.u16PortNo) = (u16RcvPortID); \
    ((pstMbuf)->stPhyRecvIfInfo.u8FrameID) = SFE_FRAME_NOT_USE; \
    ((pstMbuf)->stPhyRecvIfInfo.u16SlotID) = SFE_SLOT_NOT_USE; \
    ((pstMbuf)->stPhyRecvIfInfo.u16lSubPortNo) = SFE_SUBPORT_NOT_USE; \
}


/* һά�ӿ�ģʽ��, ���ñ��ĳ��ӿڵ���Ϣ */
#define SFE_MBUF_SET_TX_IFINFO(pstMbuf, u8SndPortType, u16SndPortID) \
{ \
    ((pstMbuf)->stPhySendIfInfo.u8PortType) = (u8SndPortType); \
    ((pstMbuf)->stPhySendIfInfo.u16PortNo) = (u16SndPortID); \
    ((pstMbuf)->stPhySendIfInfo.u8FrameID) = SFE_FRAME_NOT_USE; \
    ((pstMbuf)->stPhySendIfInfo.u16SlotID) = SFE_SLOT_NOT_USE; \
    ((pstMbuf)->stPhySendIfInfo.u16lSubPortNo) = SFE_SUBPORT_NOT_USE; \
}


/* ��ȡMBUF�з��ͽӿ����� */
#define SFE_MBUF_GET_SNDIF_TYPE(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u8PortType)
/* ��ȡMBUF�з��ͽӿڿ�� */
#define SFE_MBUF_GET_SNDIF_FRAMEID(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u8FrameID)
/* ��ȡMBUF�з��ͽӿڲۺ� */
#define SFE_MBUF_GET_SNDIF_SLOTID(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16SlotID)
/* ��ȡMBUF�з��ͽӿڶ˿ں� */
#define SFE_MBUF_GET_SNDIF_PORTNO(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16PortNo)
/* ��ȡMBUF�з��ͽӿ��Ӷ˿ں� */
#define SFE_MBUF_GET_SNDIF_SUBPORTNO(pstMbuf) ((pstMbuf)->stPhySendIfInfo.u16lSubPortNo)


/* ��ȡMBUF�н��սӿ����� */
#define SFE_MBUF_GET_RCVIF_TYPE(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u8PortType)
/* ��ȡMBUF�н��սӿڿ�� */
#define SFE_MBUF_GET_RCVIF_FRAMEID(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u8FrameID)
/* ��ȡMBUF�н��սӿڲۺ� */
#define SFE_MBUF_GET_RCVIF_SLOTID(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16SlotID)
/* ��ȡMBUF�н��սӿڶ˿ں� */
#define SFE_MBUF_GET_RCVIF_PORTNO(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16PortNo)
/* ��ȡMBUF�н��սӿ��Ӷ˿ں� */
#define SFE_MBUF_GET_RCVIF_SUBPORTNO(pstMbuf) ((pstMbuf)->stPhyRecvIfInfo.u16lSubPortNo)


/* ָ���ĵ���·���ײ� */
#define SFE_MBUF_GET_LINK_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8LinkLayerHead))
/* ָ���ĵ�������ײ� */
#define SFE_MBUF_GET_NET_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8NetLayerHeader))
/* ָ���ĵĴ�����ײ� */
#define SFE_MBUF_GET_TRAN_LAYER_HEAD(pstMbuf) (((pstMbuf)->pu8TranLayerHeader))

/* ��ȡIPͷ�е�Դ��ַ */
#define SFE_MBUF_GET_PKT_SRC_IP(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_stSrc : 0)
/* ��ȡIPͷ�е�Ŀ�ĵ�ַ */
#define SFE_MBUF_GET_PKT_DST_IP(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_stDst : 0)
/* ��ȡIPͷ�е�Э��� */
#define SFE_MBUF_GET_PKT_PRO(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_chPr : 0)
/* ��ȡ����TOS */
#define SFE_MBUF_GET_PKT_TOS(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
                                      ((SFE_IP_S *)(VOID *)((pstMbuf)->pu8NetLayerHeader))->ip_chTOS : 0)

/* ��ȡ����Դ�˿ڣ���Ƭ���Ĵ�MBUF��ȡ, �Ƿ�Ƭ���Ĵӱ�����ȡ,
   TCP��UDP�Ķ˿ں�λ��һ��,��������ֱ��ʹ��UDP�ṹȡ�˿ں��ֶ� */
#define SFE_MBUF_GET_PKT_SRC_PORT(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (((pstMbuf)->stPktCommonInfo.u32IsFragMent)? \
               ((pstMbuf)->stPktNetInfo.u16PktSrcPortOrIcmpType)\
                : (((SFE_UDP_S *)((pstMbuf)->pu8NetLayerHeader \
                     + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))->u16SrcPort))\
             : 0)

/* ��ȡ����Ŀ�Ķ˿ڣ���Ƭ���Ĵ�MBUF��ȡ, �Ƿ�Ƭ���Ĵӱ�����ȡ,
   TCP��UDP�Ķ˿ں�λ��һ��,��������ֱ��ʹ��UDP�ṹȡ�˿ں��ֶ� */
#define SFE_MBUF_GET_PKT_DST_PORT(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (((pstMbuf)->stPktCommonInfo.u32IsFragMent)? \
               ((pstMbuf)->stPktNetInfo.u16PktDstPortOrIcmpCode)\
                : (((SFE_UDP_S *)((pstMbuf)->pu8NetLayerHeader \
                     + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))->u16DstPort))\
             : 0)

/* ��ȡ����ICMP����,��֧��ICMP��Ƭ������Ϣ�Ļ�ȡ,ֱ�Ӵӱ����л�ȡ,��ȡֵΪ0xFFʱ��ʾ����Чֵ */
#define SFE_MBUF_GET_PKT_ICMP_TYPE(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (*((UINT8 *)((pstMbuf)->pu8NetLayerHeader \
               + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 )))) : 0xFF)

/* ��ȡ����ICMP code,��֧��ICMP��Ƭ������Ϣ�Ļ�ȡ,ֱ�Ӵӱ����л�ȡ,��ȡֵΪ0xFFʱ��ʾ����Чֵ */
#define SFE_MBUF_GET_PKT_ICMP_CODE(pstMbuf) (((pstMbuf)->pu8NetLayerHeader)? \
            (*((UINT8 *)((pstMbuf)->pu8NetLayerHeader \
               + ((((SFE_IP_S *)((pstMbuf)->pu8NetLayerHeader))->ip_chHLen) << 2 ) + 1))) : 0xFF)

/* ��ȡ����VRF���� */
#define SFE_MBUF_GET_PKT_VRFINDEX(pstMbuf) (((pstMbuf)->stPktCommonInfo.u32VrfIndex))

/* ����MBUF�еı���VRF���� */
#define SFE_MBUF_SET_PKT_VRFINDEX(pstMbuf,u32VrfIndexM) (((pstMbuf)->stPktCommonInfo.u32VrfIndex) = u32VrfIndexM)

/* ����ǿ��ת��, ����ʱ���뱣֤MBUF��NULL�����ҵ��øô���֮������жϷ���ֵ�Ƿ�ΪNULL */
#define SFE_MBUF_MTOD(pstMBufM, DataTypeM) (((pstMBufM)->pstDBD) ? ((DataTypeM)((pstMBufM)->pstDBD->pu8Data)) : NULL)


/*******************************************************************************
*    Func Name: SFE_MBUF_BACKWARD_MOVE
* Date Created: 2009-07-28
*       Author: wangmingxia/luowentong
*  Description: ���ײ�����MBUF�е����ݳ���
*        Input: pstMbuf: MBUFָ��
*               u32Length: ���ӵ��ײ�����
*       Output: u32Result: ���ؽ��
*       Return: �ɹ�: SFE_MBUF_OK
*               ʧ��: ���ش�����
*      Caution: ���뱣֤��һ��DB�ײ����㹻�Ŀ��пռ䣬����Ҫ��֤MBUF����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-28   wangmingxia/luowentong    Create
*
*******************************************************************************/
#define SFE_MBUF_BACKWARD_MOVE(pstMbuf, u32Length, u32Result) \
{\
    if ((NULL != ((pstMbuf)->pstDBD)) && (NULL != ((pstMbuf)->pstDBD->pu8Data)))\
    {\
        /*lint -e946*/\
        if ((u32Length) <= ((pstMbuf)->pstDBD->pu8Data) - ((pstMbuf)->pstDBD->pu8DataBlock))\
        /*lint +e946*/\
        {\
            (pstMbuf)->pstDBD->pu8Data -= (u32Length);\
            (pstMbuf)->pstDBD->u32DataLength += (u32Length);\
            (pstMbuf)->u32TotalDataLength += (u32Length);\
            (u32Result) = SFE_MBUF_OK;\
        }\
        else\
        {\
            (u32Result) = SFE_MBUF_DB_LENGTH_NOTENOUGH_BACKWARD;\
        }\
    }\
    else\
    {\
        (u32Result) = SFE_MBUF_NULL_POINTER_BACKWARD;\
    }\
}

/*******************************************************************************
*    Func Name: SFE_MBUF_FORWARD_MOVE
* Date Created: 2009-07-28
*       Author: wangmingxia/luowentong
*  Description: ���ײ�����MBUF�е����ݳ���
*        Input: pstMbuf: MBUFָ��
*               u32Length: ���ٵ��ײ�����
*       Output: u32Result: ���ؽ��
*       Return: �ɹ�: SFE_MBUF_OK
*               ʧ��: ���ش�����
*      Caution: ���뱣֤��һ��DB�����ݳ��ȴ��ڵ���u32Length,����Ҫ��֤MBUF����
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                      DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-28   wangmingxia/luowentong    Create
*
*******************************************************************************/
#define SFE_MBUF_FORWARD_MOVE(pstMbuf, u32Length, u32Result) \
{\
    if ((NULL != ((pstMbuf)->pstDBD)) && (NULL != ((pstMbuf)->pstDBD->pu8Data)))\
    {\
        if ((u32Length) <= ((pstMbuf)->pstDBD->u32DataLength))\
        {\
            (pstMbuf)->pstDBD->pu8Data += (u32Length);\
            (pstMbuf)->pstDBD->u32DataLength -= (u32Length);\
            (pstMbuf)->u32TotalDataLength -= (u32Length);\
            (u32Result) = SFE_MBUF_OK;\
        }\
        else\
        {\
            (u32Result) = SFE_MBUF_DB_LENGTH_NOTENOUGH_FORWARD;\
        }\
    }\
    else\
    {\
        (u32Result) = SFE_MBUF_NULL_POINTER_FORWARD;\
    }\
}

/* ��ȡMBUF�м�¼����չ��Ϣ�е�����ID */
#define SFE_MBUF_GET_CONNTION_ID(pstMbufM)  ((pstMbufM)->pstExpandInfo->u32ConnectionId)
/* ��ȡMBUF�м�¼����չ��Ϣ�е������� */
#define SFE_MBUF_GET_DIRECTION(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32FlowDirection)
/* ��ȡMBUF�м�¼����չ��Ϣ�еı��ķַ�KEYֵ */
#define SFE_MBUF_GET_PKTDISPATCHKEY(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32PktDispatchKey)
/* ����MBUF�м�¼����չ��Ϣ�е�����ID */
#define SFE_MBUF_SET_CONNTION_ID(pstMbufM, u32ConnectionIdM) (((pstMbufM)->pstExpandInfo->u32ConnectionId)= (u32ConnectionIdM))
/* ����MBUF�м�¼����չ��Ϣ�е������� */
#define SFE_MBUF_SET_DIRECTION(pstMbufM, u32DirectionM) (((pstMbufM)->pstExpandInfo->u32FlowDirection)= (u32DirectionM))
/* ����MBUF�м�¼����չ��Ϣ�еı��ķַ�KEYֵ */
#define SFE_MBUF_SET_PKTDISPATCHKEY(pstMbufM, u32DispatchKeyM) (((pstMbufM)->pstExpandInfo->u32PktDispatchKey)= (u32DispatchKeyM))

/* ��ȡMBUF�м�¼�Ĳ�Ʒ˽�б�־ */
#define SFE_MBUF_GET_USERFLAG(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.u8UserFlag)
/* ��ȡMBUF�м�¼�Ĳ�Ʒ������Ϣָ��1 */
#define SFE_MBUF_GET_USERPOINTER_1(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer1)
/* ��ȡMBUF�м�¼�Ĳ�Ʒ������Ϣָ��2 */
#define SFE_MBUF_GET_USERPOINTER_2(pstMbufM)  ((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer2)
/* ����MBUF�м�¼�Ĳ�Ʒ˽�б�־ */
#define SFE_MBUF_SET_USERFLAG(pstMbufM, u8UserFlagM)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.u8UserFlag) = (u8UserFlagM))
/* ����MBUF�м�¼�Ĳ�Ʒ������Ϣָ��1 */
#define SFE_MBUF_SET_USERPOINTER_1(pstMbufM, pu8UserPointer1M)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer1) = (pu8UserPointer1M))
/* ����MBUF�м�¼�Ĳ�Ʒ������Ϣָ��2 */
#define SFE_MBUF_SET_USERPOINTER_2(pstMbufM, pu8UserPointer2M)  (((pstMbufM)->pstExpandInfo->stUsrPrivateData.pu8UserPointer2) = (pu8UserPointer2M))

/* ��ȡMBUF�м�¼��IP���ĳ���,������IPͷ,�����ͷ,�����ݵ��ܳ��� */
#define SFE_MBUF_GET_IP_PKT_LEN(pstMbufM)    ((pstMbufM)->pstExpandInfo->u32IpPktLen)


#ifdef  __cplusplus
}
#endif

#endif


