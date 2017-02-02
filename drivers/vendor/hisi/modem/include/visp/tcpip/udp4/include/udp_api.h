


#ifndef        _UDP_API_H
#define        _UDP_API_H

#ifdef    __cplusplus
extern    "C"{
#endif

/* added by tangcongfeng for VISP D02170 */
#define UDP_MAXFILTNUM      5  /* �������е�SOCKET��Ŀ���� */
#define UDP_FILTOK          0  /* �����ɹ����ӹ�������Ƴ�һ��socket */
#define UDP_FILTINUSE       1  /* ��������Ѿ����ڸ�socket */
#define UDP_FILTTOOMUCH     2  /* �������socket�������� */
#define UDP_FILTNOTFOUND    3  /* �������û�и�socket */
#define UDP_FILTNONE        4  /* ������ѿգ�UDP�ĵ��Կ���Ҳͬʱ�ر� */
#define UDP_FILTISANY       5  /* ��socket���������� */
#define UDP_FILTCMDERR      6  /* �����ִ��� */
#define UDP_NOT_REGISTERED  7  /* UDP���δע�� */
#define UDP_ENOBUFS         10 /* ����ָ��Ϊ�� */

#define UDP_INPUT_NULL_POINT 11 /* ָ��socket��ȡudpͳ����Ϣ�����ָ�� */
#define UDP_ERR_NULL_INPCB   12 /* INPCB���ƿ�Ϊ�� */
#define UDP_ERR_GETSTAT_INPCB 13 /* ָ��socket��ȡudpͳ����ϢINPCB���ƿ�Ϊ�� */
#define UDP_ERR_GETSTAT_SOCKETCB  14 /* ָ��socket��ȡudpͳ����ϢSOCKETCB���ƿ�Ϊ�� */

/* ended */

#define UDP_NETINFO_FINISH        15 /* UDPNetInfo ��ѯ���� */
#define UDP_GETBFD_ERROR          16 /* ��ȡBFD���Ӷ˿���Ϣʧ�� */
#define UDP_ERR_PARAWRONG         17 /* ����������� */
#define UDP_GETINPCB_WRONG        18 /* ��ȡ�õ���INPCBΪ�� */

/* debug ����ֵ */
#define UDP_DEBUG_OFF       0
#define UDP_DEBUG_ON        1

typedef struct tagUDPHDR
{
    USHORT    uh_usSPort;        /* source port */
    USHORT    uh_usDPort;        /* destination port */
    SHORT     uh_sULen;          /* udp length */
    USHORT    uh_usSum;          /* udp checksum */
}UDPHDR_S;

typedef struct tagUDP_FILTER_S{
    ULONG   ulTaskId;
    ULONG   ulSockId;
}UDP_FILTER_S;

typedef struct tagUDP_DEBUGFILTER_S{       
    UDP_FILTER_S stDbugFilt[UDP_MAXFILTNUM];  /*Debug Filter*/
    ULONG        ulFiltCnt;                   /*Debug Filter Count*/
}UDP_DEBUGFILTER_S;

typedef struct tagUDPSTAT_S
{
                                        /* input statistics: */
    ULONG   udps_ulIPackets;            /* total input packets */
    ULONG   udps_ulHdrOps;              /* packet shorter than header */
    ULONG   udps_ulBadSum;              /* checksum error */
    ULONG   udps_ulBadLen;              /* data length larger than packet */
    ULONG   udps_ulNoPort;              /* no socket on port */
    ULONG   udps_ulNoPortBcast;         /* of above, arrived as broadcast */
    ULONG   udps_ulFullSock;            /* not delivered, input socket full */
    ULONG   udps_ulPcbCacheMiss;        /* input packets missing pcb cache */
                                        /* output statistics: */
    ULONG   udps_ulOPackets;            /* total output packets */
    ULONG   udps_ulOutErr;              /* Output failed packets, added for dist_sock by likaikun00213099 */
}UDPSTAT_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ����������ݽṹ */
typedef struct tagUDP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF����*/
    ULONG    ulLAddr;       /* ���˵�ַ (������)*/
    ULONG    ulFAddr;       /* �Զ˵�ַ (������)*/
    ULONG    ulLPort;       /* ���˶˿ں� */
    ULONG    ulFPort;       /* �Զ˶˿ں� */
    ULONG    ulSocketID ;   /* Socket ID */
    ULONG    ulTaskID;      /* ���� ID */
}UDP4CONN_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ���ݽṹ */
typedef struct tagUDP4PERSTAT_S
{
    UDP4CONN_S stUdp4Conn;          /* ʵ�ʻ�ȡ��socket id task id ����Ԫ�� */                                        
    ULONG   ulIPackets;             /* ���յ���UDP���İ���  */
    ULONG   ulIPacketBytes;         /* ���յ���UDP�����ֽ��� */
                                   
    ULONG   ulOPackets;              /* ���͵�UDP���İ���  */
    ULONG   ulOPacketBytes;          /* ���͵�UDP�����ֽ��� */

    /*socket ��������Ϣ*/
    ULONG    ulSndHiWat ;           /*���ͻ�������ˮλ*/
    ULONG    ulRcvHiWat ;           /*���ջ�������ˮλ*/
    ULONG    ulSndCC ;              /*���ͻ�������ʵ������ */
    ULONG    ulRcbCC ;              /*���ջ�������ʵ������ */
    ULONG    ulDropPackets;         /*���ڽ��ջ������������ı�����*/
    ULONG    ulDropPacketBytes;     /*���ڽ��ջ������������ı����ֽ���*/
}UDP4PERSTAT_S;

typedef ULONG (*UDP4InterMediate_HOOK_FUNC)(MBUF_S *pMBuf, LONG nIpHLen);

typedef struct tagTCPIP_UDPNETINFO_S
{
    ULONG   ulTaskId;       /*����ID*/
    ULONG   ulSrcIp;        /* �����ֽ��� */
    ULONG   ulDstIp;        /* �����ֽ��� */
    USHORT  usSrcPort;
    USHORT  usDestPort;
    /*Added by limin00188004, ��ȡ����״̬ʱ���socket���󶨵�VRF����, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
    ULONG   ulVrfIndex;
    /* End of Added by limin00188004, 2012/9/28   ���ⵥ��:S.VRF.02.01 */
}TCPIP_UDPNETINFO_S;
ULONG TCPIP_SetUDPDbgFilter( ULONG ulFlag, ULONG ulTaskId, ULONG ulSockId );

ULONG TCPIP_GetUDPDbgFilter( ULONG *pulDebugFlag,UDP_DEBUGFILTER_S *pstUdpDbgFilter );

VOID  TCPIP_NoDebugUDPAll(VOID);

VOID  TCPIP_DebugUDPAll(VOID);

VOID  TCPIP_GetUDPStat( UDPSTAT_S *pstUdpStatistics );

VOID  TCPIP_ClrUDPStat(VOID);

ULONG TCPIP_RegFuncUDPInterMediateHook(UDP4InterMediate_HOOK_FUNC pfHookFunc);

VOID  TCPIP_ShowUdpStatistic (VOID);

ULONG TCPIP_UdpInput( MBUF_S *pMBuf, LONG nIpHLen);


extern ULONG TCPIP_GetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo, UDP4PERSTAT_S  *pstRetStats);


extern ULONG TCPIP_ResetPerUdp4ConnStats(UDP4CONN_S *pstConnInfo);


typedef ULONG (*UDPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncUDPInputHook( UDPINPUT_HOOK_FUNC pfFuncHook );
extern UDPINPUT_HOOK_FUNC g_UDP_Input_HookFunc;

#define UDP_NOT_PROCESSED_BY_INTERMEDIATE              0 
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define UDP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define UDP_PROCESSED_BY_INTERMEDIATE                  2
/* UDP������ */
/* intermediate process not processed the packet. 
 * Stack (UDP4) will do the processing
 */
#define UDP4_NOT_PROCESSED_BY_INTERMEDIATE              1  /*���Ӻ�������������VISP����*/

/* Intermediate Processing will continue processing and will own the packet
 * UDP4 do not need to process the packet any more
 */
#define UDP4_PROCESSED_BY_INTERMEDIATE                  2  /*�ɹ��Ӻ���������VISP������*/
/*End of Added*/


extern ULONG TCPIP_OpenUdpNetInfo(UINTPTR *pulWaitlist);


extern ULONG TCPIP_GetUdpNetInfo(UINTPTR ulWaitlist, TCPIP_UDPNETINFO_S *pstNetInfo);


extern ULONG TCPIP_CloseUdpNetInfo(UINTPTR ulWaitlist);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

