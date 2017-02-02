

#ifndef _IPSFE_IF_H_
#define _IPSFE_IF_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef SFE_MAC_LEN
#define SFE_MAC_LEN         6        /* physical��ַ���� */
#endif

/* IFID�Ŀ��� */
#define INTF_COPYIFID(pstDestIfID,pstSrcIfID)\
{\
    (pstDestIfID)->u8FrameID     = (pstSrcIfID)->u8FrameID;\
    (pstDestIfID)->u16SlotID     = (pstSrcIfID)->u16SlotID;\
    (pstDestIfID)->u16PortNo     = (pstSrcIfID)->u16PortNo;\
    (pstDestIfID)->u8PortType    = (pstSrcIfID)->u8PortType;\
    (pstDestIfID)->u16lSubPortNo = (pstSrcIfID)->u16lSubPortNo;\
}

#define INTF_COPYMAC(pu8DestMac,pu8SrcMac)\
{\
    pu8DestMac[0] = pu8SrcMac[0];\
    pu8DestMac[1] = pu8SrcMac[1];\
    pu8DestMac[2] = pu8SrcMac[2];\
    pu8DestMac[3] = pu8SrcMac[3];\
    pu8DestMac[4] = pu8SrcMac[4];\
    pu8DestMac[5] = pu8SrcMac[5];\
}

/* �ӿ���ϢID,��֤SFE_IFID��TCPIP_SFE_IFID�ṹ��Ա����С����һ�� */
typedef struct tagSFE_IFID
{
    UINT8   u8PortType;        /* �˿����� */
    UINT8   u8FrameID;         /* ���,ȫF��ʾ��ʹ�� */
    UINT16  u16SlotID;         /* �߼���λ��,ȫF��ʾ��ʹ�� */
    UINT16  u16PortNo;         /* �߼��˿ں�,һάģʽ��ϵͳ�˿ڱ��Ψһ����άģʽ����ͬһ��ͬһ��λ��Ψһ */
    UINT16  u16lSubPortNo;     /* �Ӷ˿ں� */
}SFE_IFID;

/* �ӿ���Ϣ�ṹ,��֤SFE_INTERFACE_INFO_S��TCPIP_SFE_INTF_S�ṹ��Ա����С����һ�� */ 
typedef struct tagSFE_INTERFACE_INFO
{
    SFE_IFID stIfID;
    UINT32   u32IfIndex;             /* �ӿ�����,ACLģ����Ҫ */
    UINT32   u32VrfIndex;            /* VRF���� */
    UINT32   u32LinkType;            /* �˿ڵ���·������ */    
    UINT32   u32PhyStatus;           /* �˿�����״̬ */
    UINT32   u32LineStatus;          /* IPV4��·״̬ */
    UINT32   u32Line6Status;         /* IPV6��·״̬ */    
    UINT32   u32Baud;                /* �˿ڵĲ����� */
    UINT32   u32MTU;                 /* �˿ڵ�MTU */
    UINT32   u32ReduceTTL;           /* �ӿ�ת������TTL�Ƿ��1 */
    UINT8    u8MacAddr[SFE_MAC_LEN]; /* physical��ַ */ 
    UINT8    u8Attribute;            /* �ӿ�����Fabric/spi4�� */
    UINT8    u8Origin;               /* �ӿڴ�����Դ */
    UINT32   u32IsDisableArpMiss;    /* �ӿ��Ƿ���Ҫȥʹ��ARP MISS����,ֻ����̫����Ч */
}SFE_INTERFACE_INFO_S;

/* ���ýӿ���ؿ��صĲ�����Ϣ,ARP MISS����,TTL�Ƿ��1���� */
typedef struct tagSFE_IF_SET_SWITCH
{
    SFE_IFID stIfID;                 /* �ӿ�ID */
    UINT32   u32Switch;              /* ����ֵ */
    UINT32   u32Reserved;            /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
}SFE_IF_SET_SWITCH_S;

#ifdef  __cplusplus
}
#endif

#endif

