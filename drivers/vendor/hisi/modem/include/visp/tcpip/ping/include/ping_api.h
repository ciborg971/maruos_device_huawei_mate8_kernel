/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ping_api.h
*
*  Project Code: VISPV1R7
*   Module Name: ping
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: ping�û�API�ӿ��ļ�,��ͷ�ļ��漰��IPV6�ĵ�ַ���ݽṹVRP_IN6ADDR_S
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
#ifndef _PING_API_H_
#define _PING_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

#ifndef IP_HOSTNAME_LEN
#define IP_HOSTNAME_LEN    254   /* ����������*/
#endif

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH  47   /* �ӿ������� */
#endif

#define PIN_PADLEN          80   /* ping ������䳤�� */
#define PIN_VRFNAMELEN      31   /* ˽����ʶ�� */


typedef struct tagPing_Comm_s
{
    CHAR   szHostName[IP_HOSTNAME_LEN + 1];
    UCHAR  ucPadding_1[4-((IP_HOSTNAME_LEN + 1)%4)];
    CHAR   szPattern[PIN_PADLEN];   /* ���ĵ����ֵ */
    ULONG  ulPackets;        /* ���͵ı������� */
    ULONG  lDatalen;         /* ���͵ı��ĳ��� */
    ULONG  ulTimeout;        /* ���ͱ��ĵĳ�ʱʱ�� */
    ULONG  ulFlag;           /* ping6: 1 or ping4 : 0 */
    ULONG  ulMore;           /* ���ķ���ʱ����,��λ:ms */

    union
    {
        struct tagPing6_S
        {
            CHAR szInterface[MAX_IF_NAME_LENGTH + 1]; /* �ӿ�������Ϣ ָ�����ӿڷ���,����ping6ȫ�򵥲���ַ���ָ�����ӿ�һ��ָ����һ��.����ping6��·���ص�ַһ��ָ�����ӿڲ���ָ����һ�� */
            VRP_IN6ADDR_S stSourAddr;                 /* ���ӿڵ�Դ��ַ,������ */
            VRP_IN6ADDR_S stNextHop;                  /* ָ����һ��,������,����ping6ָ����һ��һ��Ҫָ�����ӿ�,������Բ�ָ�� */
            ULONG ulHopLimit;                         /* ������Hop limit */
            ULONG ulTos6;                             /* ������Tos */
            ULONG ulForeverFlag;                      /* �����ping6, 1��ʾ�����ping, 0���ֶ������� */
            ULONG ulVrf6Flag ;      /* PING_Vrf_NO or  PING_Vrf_YES */
            CHAR  szVrf6Name[PIN_VRFNAMELEN + 1]; /* ˽����ʶ��,���ֶκ�����ulVrfIndex�ֶ���ͬ,���ȿ��Ǹ��ֶ� */
            ULONG ulVrf6Index;      /* VRF Index,���ֶκ�����szVrfName�ֶ���ͬ,���ȿ��Ǹ�szVrfName */
        }Ping6_Comm;

        struct tagPing4_S
        {
            ULONG ulTTL;           /* ���õ�TTLֵ */
            ULONG ulTos;           /* ���õ�TOSֵ */
            ULONG ulIfIndex;       /* ���ӿ����� */
            ULONG ulRdqnv[6];      /* Flag of Parameter (-R -d -q -n -v -t) have been specified */
            ULONG ulVrfFlag ;      /* PING_Vrf_NO or  PING_Vrf_YES */
            CHAR  szVrfName[PIN_VRFNAMELEN + 1]; /* ˽����ʶ��,���ֶκ�����ulVrfIndex�ֶ���ͬ,���ȿ��Ǹ��ֶ� */
            ULONG ulSourceAddr;    /* ���ӿڵ�Դ��ַ,������ */
            ULONG ulVrfIndex;      /* VRF Index,���ֶκ�����szVrfName�ֶ���ͬ,���ȿ��Ǹ�szVrfName */
            ULONG ulNextHop;       /* ָ����һ��,������ */
            USHORT usDF;           /* Ϊ0��ʾ������DF��־��Ϊ1������DF��־��Ĭ��Ϊ0 */
            UCHAR  ucRes[2];
        }Ping4_Comm;
    }Ping_Un;

#define   Ping_szInterface    Ping_Un.Ping6_Comm.szInterface
#define   Ping_stSourAddr     Ping_Un.Ping6_Comm.stSourAddr
#define   Ping_stNextHop      Ping_Un.Ping6_Comm.stNextHop
#define   Ping_ulHopLimit     Ping_Un.Ping6_Comm.ulHopLimit
#define   Ping_ulTos6         Ping_Un.Ping6_Comm.ulTos6
#define   Ping_ulForeverFlag  Ping_Un.Ping6_Comm.ulForeverFlag
#define   Ping_ulVrf6Flag      Ping_Un.Ping6_Comm.ulVrf6Flag
#define   Ping_ulVrf6Index     Ping_Un.Ping6_Comm.ulVrf6Index
#define   Ping_szVrf6Name      Ping_Un.Ping6_Comm.szVrf6Name


#define   Ping_ulTTL          Ping_Un.Ping4_Comm.ulTTL
#define   Ping_ulTos          Ping_Un.Ping4_Comm.ulTos
#define   Ping_ulIfIndex      Ping_Un.Ping4_Comm.ulIfIndex
#define   Ping_ulRdqnv        Ping_Un.Ping4_Comm.ulRdqnv
#define   Ping_ulSourceAddr   Ping_Un.Ping4_Comm.ulSourceAddr
#define   Ping_szVrfName      Ping_Un.Ping4_Comm.szVrfName
#define   Ping_ulVrfFlag      Ping_Un.Ping4_Comm.ulVrfFlag
#define   Ping_ulVrfIndex     Ping_Un.Ping4_Comm.ulVrfIndex
#define   Ping_ulNextHop      Ping_Un.Ping4_Comm.ulNextHop
#define   Ping_usDF           Ping_Un.Ping4_Comm.usDF
}Ping_Comm_S;

typedef struct tagTCPIP_PING_STAT
{
    ULONG ulIPAddr;      /* Ŀ�ĵ�ַ�������� */
    ULONG ulSendCount;   /* ���͸���*/
    ULONG ulRecvCount;   /* ���ո���*/
    ULONG ulLostCount;   /* ��������*/
    ULONG ulMinTime;     /* ��С��Ӧʱ�䣨���룩*/
    ULONG ulMaxTime;     /* �����Ӧʱ�䣨���룩*/
    ULONG ulAvgTime;     /* ƽ����Ӧʱ�䣨���룩*/
    VRP_IN6ADDR_S stIPAddr6;  /* Ŀ��IPv6��ַ, ������ */
}TCPIP_PING_STAT_S;

/*pingģ�������*/
enum tagEnum_PINGERR
{
    PING_ERR_RECVALL = 0,      /* 0 PING�����ɹ���������PING�����ľ��յ���ȷ��PING��Ӧ���� */
    PING_ERR_RECVPART,         /* 1 PING�������ֳɹ���������PING�������յ�����PING��Ӧ���� */
    PING_ERR_NORECV,           /* 2 PING����ʧ�ܣ�������PING������δ�յ��κ�PING��Ӧ���� */
    PING_ERR_UNKNOWN_HOST,     /* 3 �Ƿ��ĵ�ַ�������� */
    PING_ERR_INVAILD_ADDRESS,  /* 4 ��Ч�ĵ�ַ����㲥��ַ��D��/E���ַ�� */
    PING_ERR_OUT_MEMORY,       /* 5 �����ڴ�ʧ�� */
    PING_ERR_FILL_PACKET,      /* 6 �������ʧ�� */
    PING_ERR_SOCKET,           /* 7 ����socketʧ�� */
    PING_ERR_UNKNOWN_VRF,      /* 8 �����VRF */
    PING_ERR_UNABLE_GETADDR,   /* 9 ��ȡԴ��ַʧ�� */
    PING_ERR_BIND,             /* 10 Bindʧ�� */
    PING_ERR_IFINDEX,          /* 11 �ӿ����������IP���ƿ���� */
    PING_ERR_TTL,              /* 12 ����socket��TTLѡ��ʧ�� */
    PING_ERR_TOS,              /* 13 ����socket��TOSѡ��ʧ�� */
    PING_ERR_INTERFACE,        /* 14 ����socket���ض��ӿڷ���ѡ��ʧ�� */
    PING_ERR_RECORD_ROUTE,     /* 15 ����socket��¼·��ѡ��ʧ�� */
    PING_ERR_IPV6_UNSPECIFIED, /* 16 IPv6��Դ��ַΪ�� */
    PING_ERR_IPV6_SOURCEADDR,  /* 17 IPv6��Դ��ַ�Ƿ� */
    PING_ERR_IPV6_DESTADDR,    /* 18 IPv6��Ŀ�ĵ�ַ�Ƿ� */
    PING_ERR_IPV6_INTERNAME,   /* 19 �Ƿ��Ľӿ��� ��IPv6��*/
    PING_ERR_IPV6_GETTABLE,    /* 20 ��ȡ���ʧ�� ��IPv6��*/
    PING_ERR_IPV6_INTERADDR,   /* 21 ��ȡ��ַʧ�� ��IPv6��,Ŀ�ĵ�ַ��ȫ�򵥲���û��ָ��ԴIP,�ӿڱ������ȫ�򵥲���ַ */
    PING_ERR_IPV6_LINKLOCAL,   /* 22 ��·���ص�ַ�ӿڷǷ���IPv6��*/
    PING_ERR_IPV6_NOLINKLOCAL, /* 23 ����·���ص�ַ�ӿڷǷ���IPv6��*/
    PING_ERR_IPV6_NOINTERNAME, /* 24 ����·�����ҷǶಥȴָ���˳��ӿڣ�IPv6��*/
    PING_ERR_IPV6_BIND,        /* 25 Bindʧ�ܣ�IPv6��*/
    PING_ERR_IPV6_RECVMSG,     /* 26 ��ȡICMPv6replay���ĵ�Դ��ַʧ�ܣ�IPv6��*/
    PING_ERR_SETOPT_DEBUG,     /* 27 ����socket��SO_DEBUGѡ��ʧ�� */
    PING_ERR_SETOPT_DONTROUTE, /* 28 ����socket��SO_DONTROUTEѡ��ʧ�� */
    PING_ERR_SETOPT_RCVBUF,    /* 29 ����socket��SO_RCVBUFѡ��ʧ�� */
    PING_ERR_DATALEN,          /* 30 ���ĳ��ȴ���,��Χ��0~8100 */
    PING_ERR_PARAM,            /* 31 �����������,���ָ��� */

    PING_API_COM_NULL,         /* 32 �������Ϊ�� */
    PING_API_PARA_WRONG,       /* 33 �����������,���ָ��� */
    PING_ERR_NOT_L3INT,        /* 34 ����˿ڲ�֧��Ping */
    PING_ERR_VRF_NOT_INIT,     /* 35 VRFģ��δע�� */
    PING_ERR_IPV6_GET_IPCTL,   /* 36 ��ȡIPV6���ƿ�ָ��Ϊ��  */
    PING_ERR_LOCAL_NOT_NEXTHOP,/* 37 ��·���ص�ַ����ָ����һ��  */
    PING_ERR_NEXTHOP_NOTGLOBAL,/* 38 ��һ����ַ������ȫ�򵥲���ַ  */
    PING_ERR_IF_NOTNEXTHOP,    /* 39 ȫ�򵥲���ַָ�����ӿ�ʱ,����Ҫָ����һ�� */
    PING_ERR_NEXTHOP_NOTIF,    /* 40 ȫ�򵥲���ַָ����һ��ʱ,����Ҫָ�����ӿ� */
    PING_ERR_NH_NOINTF,        /* 41 PING4ָ����һ��һ��Ҫָ�����ӿ� */
    PING_ERR_IFANDNEXTHOP,     /* 42 PING4ָ�����ӿں���һ��ʧ�� */

    PING_ERR_IFANDNEXTHOP_2,   /* 43 ͨ������·�ɱ��ҵ���һ�������ó��ӿں���һ��ʧ�� */
    PING_ERR_IFANDNEXTHOP_3,   /* 44 ͨ������·�ɱ��ҵ����ӿں����ó��ӿں���һ��ʧ�� */
    PING_ERR_GETNEXTHOP_BY_FIB,/* 45 ͨ������·�ɻ�ȡ��һ��ʧ�� */
    PING_ERR_GETIFINDEX_BY_FIB,/* 46 ͨ������·�ɻ�ȡ���ӿ�ʧ�� */
    PING_ERR_SETOPT_HDRINCL,   /* 47 ����socket��IP_HDRINCLѡ��ʧ�� */
    PING_ERR_INVAILD_DF,       /* 48 ��Ч��DF������ֻ��Ϊ0����1 */
};

typedef VOID (*TCPIP_PINGOutput_HOOK_FUNC)(CHAR *pstBuf);

/* pingͳ����Ϣ֪ͨ�ص�����ԭ��, ͳ����Ϣ�ڴ���VISP����, �����������ָ�벻Ϊ��, ����Ҫ��Ʒ�ͷ� */
typedef VOID (*TCPIP_PINGSTAT_HOOK_FUNC)(TCPIP_PING_STAT_S *pstPingStat);

/* ������pingͳ����Ϣ֪ͨ�ص�����ԭ��, ͳ����Ϣ�ڴ���VISP����, �����������ָ�벻Ϊ��, ����Ҫ��Ʒ�ͷ� */
typedef VOID (*TCPIP_PINGEXSTAT_HOOK_FUNC)(TCPIP_PING_STAT_S *pstPingStat, ULONG ulExecID);


typedef VOID (*TCPIP_PINGExOutput_HOOK_FUNC)(CHAR *pstBuf,ULONG ulExecID);

/*******************************************************************************
*    Func Name: TCPIP_Ping
*  Description: PING���ܺ���
*        Input: Ping_Comm_S *pPingParam:PING�ṹ�������Ϣָ��
*       Output: ��
*       Return: �ɹ�����0
*               ʧ�ܷ��ش�����
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Ping(Ping_Comm_S *pPingParam);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPINGOutputHook
*  Description: PING��Ϣ������亯��ע��ӿ�
*        Input: TCPIP_PINGOutput_HOOK_FUNC pfHookFuc:�ṩ���û�ע���PINGģ����Ϣ�������ָ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPINGOutputHook(TCPIP_PINGOutput_HOOK_FUNC pfHookFuc);
/*******************************************************************************
*    Func Name: TCPIP_SetPingTos
*  Description: ����pingģ���tosֵ
*        Input: UCHAR ucTos: Ҫ���õ�tosֵ��ֵ����Ч
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_SetPingTos(UCHAR ucTos);
/*******************************************************************************
*    Func Name: TCPIP_GetPingTos
*  Description: ��ȡpingģ�����õ�tosֵ
*        Input: UCHAR *pucTos: ���������tosֵ
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-8-19    LY(57500)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_GetPingTos(UCHAR *pucTos);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPingStatHook
*  Description: ע��Pingͳ����Ϣ֪ͨ�ص�����
*        Input: TCPIP_PINGSTAT_HOOK_FUNC pfFunc: �ص�����
*       Output: 
*       Return: PING_API_PARA_WRONG���ص�����ָ��Ϊ��
*               VOS_OK������ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-21  wujie(61195)     Create the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncPingStatHook(TCPIP_PINGSTAT_HOOK_FUNC pfFunc);



ULONG TCPIP_PingEx(ULONG ulExecID, Ping_Comm_S *pPingParam);




ULONG TCPIP_RegFuncPINGExOutputHook(TCPIP_PINGExOutput_HOOK_FUNC pfHookFuc);


extern VOID TCPIP_VispPing(CHAR *szHostName, ULONG ulTimeout, CHAR *szVrfName, ULONG ulDatalen, ULONG ulPackets,
    ULONG ulTos, ULONG ulTtl, CHAR *szIfName, CHAR *szSrcIp, ULONG ulTaskPri);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncPingExStatHook
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: ע�������PINGͳ����Ϣ���Ӻ���
*        Input: TCPIP_PINGEXSTAT_HOOK_FUNC pfFunc: ���ӻص�����
*       Output: 
*       Return: VOS_OK:�ɹ�  ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncPingExStatHook(TCPIP_PINGEXSTAT_HOOK_FUNC pfFunc);


/*******************************************************************************
*    Func Name: TCPIP_SetPing6Tos
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: ����ping6ȫ��tosֵ,��ping6�����,���û��ָ��tos,��ʹ��ȫ��tosֵ
*        Input: UCHAR ucTos: ����Tosֵ[0,255]
*       Output:
*       Return: VOS_OK:�ɹ�  ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetPing6Tos(UCHAR ucTos);

/*******************************************************************************
*    Func Name: TCPIP_GetPing6Tos
* Date Created: 2009-12-14
*       Author: zhangchunyu(62474)
*  Description: ��ȡȫ��tosֵ
*        Input: UCHAR *pucTos: �������,��ȡȫ��tosֵ,��ȡֵ��Χ[0,255]
*       Output:
*       Return: VOS_OK:�ɹ�  ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-12-14    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetPing6Tos(UCHAR *pucTos);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _PING_API_H_ */

