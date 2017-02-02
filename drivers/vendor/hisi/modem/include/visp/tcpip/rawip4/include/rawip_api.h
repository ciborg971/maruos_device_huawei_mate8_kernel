


#ifndef        _RAWIP_API_H_
#define        _RAWIP_API_H_

#ifdef    __cplusplus
extern    "C"{
#endif

#define RAWIP_ERR_NULL_POINT 2          /* ��ȡRAWIPͳ����Ϣ,�����ָ�� */
#define RAWIP_ERR_GETSTAT_INPCB 3       /* ��ȡRAWIPͳ����Ϣ,INPCB�ṹΪ�� */
#define RAWIP_ERR_GETSTAT_SOCKETCB 4    /* ��ȡRAWIPͳ����Ϣ,SOCKETCB�ṹΪ�� */


typedef struct tagRIPSTAT
{
    ULONG rips_ulNoProto;
    ULONG rips_ulDelivered;
    ULONG rips_ulRawOut;
    ULONG rips_ulRawOutErr; /* Added for dist_sock by likaikun00213099 */
}RIPSTAT_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ����������ݽṹ */
typedef struct tagRAWIP4CONN_S
{
    ULONG    ulVrfIndex;    /* VRF����*/
    ULONG    ulLAddr;       /* ���˵�ַ (������)*/
    ULONG    ulFAddr;       /* �Զ˵�ַ (������)*/
    ULONG    ulProto;       /* Э��� */
    ULONG    ulSocketID ;   /* Socket ID */
    ULONG    ulTaskID;      /* ���� ID */
}RAWIP4CONN_S;

/* ����socket id,task id����Ԫ���ȡͳ����Ϣ���ݽṹ */
typedef struct tagRAWIP4PERSTAT_S
{
    RAWIP4CONN_S stRawIp4Conn;      /*ʵ�ʻ�ȡ��socket id task id ����Ԫ��*/
    ULONG   ulIPackets;             /* ���յ���RAWIP���İ���  */
    ULONG   ulIPacketsByte;         /* ���յ���RAWIP�����ֽ��� */

    ULONG   ulOPackets;              /* ���͵�RAWIP���İ���  */
    ULONG   ulOPacketsByte;          /* ���͵�RAWIP�����ֽ��� */

    /*socket ��������Ϣ*/
    ULONG    ulSndHiWat ;           /*���ͻ�������ˮλ*/
    ULONG    ulRcvHiWat ;           /*���ջ�������ˮλ*/
    ULONG    ulSndCC ;              /*���ͻ�������ʵ������ */
    ULONG    ulRcbCC ;              /*���ջ�������ʵ������ */
    ULONG    ulDropPackets;         /*���ڽ��ջ������������ı�����*/
    ULONG    ulDropPacketBytes;     /*���ڽ��ջ������������ı����ֽ���*/
}RAWIP4PERSTAT_S;

/*OSPF RAWIP socket ��Ϣ�ṹ, Ϊ֧�ֹ�����˫OSPF���Զ����������ݽṹ, 2005-10-31, SWID00024*/
typedef struct tagTargetSOCKET
{
            ULONG ulSockId;        /*socket��*/
            ULONG ulTaskId;        /*�����*/
}TARGET_SOCKET_S;

typedef ULONG (*LocateTargetSocket_HOOK_FUNC)(ULONG ulIfIndex,ULONG ulDestAddr, TARGET_SOCKET_S *pstTargetSkt);
VOID  TCPIP_ClrRawIPStat(VOID);

ULONG TCPIP_GetRawIPStat(RIPSTAT_S *pstRawipStats);

ULONG TCPIP_RegFuncLocateTargetSocketHook(LocateTargetSocket_HOOK_FUNC pfHookFunc);

VOID  TCPIP_ShowRipStatistic (VOID);


extern ULONG TCPIP_GetPerRawip4ConnStats(RAWIP4CONN_S *pstConnInfo, RAWIP4PERSTAT_S  *pstRetStats);


extern ULONG TCPIP_ResetPerRawip4ConnStats(RAWIP4CONN_S *pstConnInfo);


typedef ULONG (*RAWIPINPUT_HOOK_FUNC)( MBUF_S* pMbuf );
ULONG TCPIP_RegFuncRAWIPInputHook( RAWIPINPUT_HOOK_FUNC pfFuncHook );
extern RAWIPINPUT_HOOK_FUNC g_RawIP_Input_HookFunc;

#define RAWIP_NOT_PROCESSED_BY_INTERMEDIATE              0
/* intermediate found the packet has Error, Stack will Destroy the Packet */
#define RAWIP_INTER_PROCESS_ERROR                        1
/* Intermediate Processing will continue processing and will own the packet
 * PP do not need to process the packet any more */
#define RAWIP_PROCESSED_BY_INTERMEDIATE                  2


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

