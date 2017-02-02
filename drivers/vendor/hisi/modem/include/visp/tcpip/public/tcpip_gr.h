/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_gr.h
*
*  Project Code: VISPV100R006C02
*   Module Name: tcpip gr
*  Date Created: 2008-08-15
*        Author: zhangchunyu
*   Description: gr����ģ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-08-15  zhangchunyu        Create

*******************************************************************************/

#ifndef _TCPIP_GR_H_
#define _TCPIP_GR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* GR������ */
enum  enGRErrorCode
{
    GR_OK = 0,          /* 0 �ɹ� */
    GR_ERR,             /* 1 ʧ�� */
    GR_NULL_POINT,      /* 2 ָ��Ϊ�� */

    GR_MAX, 
};

/* VISP����ģ��ID */
enum enumGRMID
{
    GR_MID_MIN,
    GR_MID_IFNET = 1,
    GR_MID_IP,
    GR_MID_ETHARP,
    GR_MID_TRUNK,
    GR_MID_PPP,
    GR_MID_POES,
    GR_MID_PPPOE,
    GR_MID_DHCP4C,
    GR_MID_DHCP4R,
    GR_MID_SFIB,
    GR_MID_SOCKET,
    GR_MID_BFD,
    GR_MID_PUBLIC,
    GR_MID_TCP,  
    
    GR_MID_MAX,    /* VISP�ڲ�ģ������� */
};

/* ����ģʽ */
enum enRebootMode
{
    MODE_NORMAL,       /* 0 ����ģʽ */
    MODE_KEEPALIVE,    /* 1 ����ģʽ */
};

#define NSR_MASTER_MODE     0
#define NSR_SLAVE_MODE      1


/* �ж�GR��ģ��ID�Ƿ�Ϸ� 1 �Ϸ� 0 �Ƿ� */
#define GR_MID_VALID(MID) (((MID) > GR_MID_MIN) && ((MID) < GR_MID_MAX))

#define INTF_NORMAL     0      /* �Ǳ���ӿڣ�DCN�ӿ�) */
#define INTF_KEEPALIVE  1      /* ����ӿڣ�ҵ��ӿڣ�*/

#define GR_SM_P() (VOID)TCPIP_SmP(g_ulGRSem)

#define GR_SM_V() (VOID)TCPIP_SmV(g_ulGRSem)

extern ULONG g_ulGRSem;

extern ULONG TCPIP_GetRebootMode(ULONG ulMid);
extern ULONG TCPIP_GR_Init(VOID);

#ifdef  __cplusplus 
}
#endif

#endif /* _TCPIP_GR_H_ */

