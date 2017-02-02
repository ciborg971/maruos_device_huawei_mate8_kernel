

#ifndef _IPSFE_PUB_H_
#define _IPSFE_PUB_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ��ͨ���д�����ʾ������ARP��Ϣ�Ľṹ�� */
typedef struct tagSFE_ARP_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT8  uiIpAddr[LEN_16];    /* ��ַ, ���ʮ�����ַ��� */
}SFE_ARP_SHOW_S;

/* ��ͨ���д�����ʾ������BFD��Ϣ�Ľṹ�� */
typedef struct tagSFE_BFD_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT32 u32SessionID;        /* BFD�ỰID */
}SFE_BFD_SHOW_S;

/* ��ͨ���д�����ʾ������ROUTE��Ϣ�Ľṹ�� */
typedef struct tagSFE_ROUTE_SHOW
{
    UINT32 u32VrfIndex;         /* VRF���� */
    UINT8  uiIpAddr[LEN_16];    /* ��ַ, ���ʮ�����ַ��� */
}SFE_ROUTE_SHOW_S;

#ifdef  __cplusplus
}
#endif

#endif

