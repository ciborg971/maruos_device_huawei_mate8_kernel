
#ifndef _IPSFE_ROUTE_H_
#define _IPSFE_ROUTE_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ·�����ݽṹ */
typedef struct tagSFE_ROUTE
{
    UINT32    u32VrfIndex;          /* ʵ������ */
    UINT32    u32DstIp;             /* Ŀ�ĵ�ַ */
    UINT32    u32Nexthop;           /* ��һ�� */
    SFE_IFID  stOutIf;              /* ���ӿ���Ϣ */
    UINT32    u32LocalIp;           /* ���س��ӿڵ�ַ */
    UINT32    u32Flags;             /* ·�ɱ�� */
    UINT32    u32Origin;            /* ��Դ */
    UINT32    u32ATIndex;           /* �������ݲ�ʹ��*/
    UINT8     u8DstPrefixLength;    /* Ŀ�ĵ�ַ���볤�� */
    UINT8     u8LocalPrefixLength;  /* ���س��ӿڵ�ַ���볤�� */
    UINT16    u16RTPri;             /* ·�����ȼ� */
    UINT32    u32OutIfIndex;        /* ���ӿڽӿ����� */
}SFE_ROUTE_S;

/* ·�ɻ�ȡKEY */
typedef struct tagSFE_ROUTE_GET
{
    UINT32    u32VrfIndex;          /* ʵ������ */
    UINT32    u32DstIp;             /* Ŀ�ĵ�ַ */
}SFE_GET_ROUTE_KEY_S;

/* ����������Դ��ַ���ݽṹ,Ŀǰ������ӿ�û��ά����ַ,�ڷ��ͱ��ĵ�ʱ��,
   �����û�����VRF�µ�IP��䱨�ĵ�ԴIP */
typedef struct tagSFE_SRCIPADDR
{
    UINT32 u32VrfIndex;                    /* VRF index */
    UINT32 u32SrcIpAddr;                   /* IP Addr */
}SFE_SRCIPADDR_S;

#ifdef  __cplusplus
}
#endif

#endif

