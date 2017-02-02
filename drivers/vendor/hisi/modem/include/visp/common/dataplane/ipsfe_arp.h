

#ifndef _IPSFE_ARP_H_
#define _IPSFE_ARP_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ��ЧARP�ڵ��־ */
#define SFE_ARP_NORMAL_ARPNODE 0
/* ARPα�ڵ��־ */
#define SFE_ARP_FAKE_ARPNODE 1

/* ARP���������ò����ṹ */
typedef struct tagSFE_ARP_PARA
{
    SFE_IFID stIfID;
    UINT32   u32VrfIndex;       /* �ӿ�����VRF */
    UINT32   u32IpAddr;         /* ��ַ�������ֽ��� */
    UINT32   u32VlanId;         /* �ݲ�ʹ�� */
    UINT32   u32IsFake:1;       /* �Ƿ�����Ԫ��־��1��ʾ����Ԫ���� 0��ʾ����Ԫ���� */
    UINT32   u32IsStatic:1;     /* ����̬��־��1��ʾ�Ǿ�̬���� 0��ʾ��̬���� */
    UINT32   u32FlagReserve:30;     /* ����̬��־��1��ʾ�Ǿ�̬���� 0��ʾ��̬���� */
    UINT8    u8MacAddr[SFE_MAC_LEN]; /* physical��ַ */
    UINT8    u8Source;         /* ��Դ */
    UINT8    u8Reserve;
}SFE_ARP_PARA_S;

/* ARP MISS������֪ͨ���������Ϣ�ṹ */
typedef struct tagSFE_ARP_MISS_PARA
{
    SFE_IFID stIfID;            /* �ӿ���Ϣ */
    UINT32   u32VrfIndex;       /* �ӿ�����VRF */
    UINT32   u32IpAddr;         /* ��ַ�������ֽ��� */
}SFE_ARP_MISS_PARA_S;

/* ����ARP������Ϣ��ȡ�ؼ��� */
typedef struct tagSFE_ARP_KEY
{
    UINT32 u32VrfIndex;  /* VRF���� */
    UINT32 u32IpAddr;    /* ��ַ�������ֽ��� */
}SFE_ARP_KEY_S;

#ifdef  __cplusplus
}
#endif

#endif

