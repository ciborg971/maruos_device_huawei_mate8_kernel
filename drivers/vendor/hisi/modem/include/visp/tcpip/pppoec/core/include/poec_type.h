

#ifndef  _POEC_TYPE_H_
#define  _POEC_TYPE_H_

#ifdef __cplusplus
extern "C"{
#endif



/* PPPoE Client���ƿ�ṹ��ÿ����װ��PPPoE����̫���ӿڶ�Ӧһ��PPPoE Client���ƿ� */
typedef struct tagPppoeClientCb
{
    DLL_NODE_S  stPoeClientDllNode;             /* ���ƿ�����ڵ� */
    ULONG       ulEthIfIndex;                   /* ��Ӧ����̫��IFNET���� */
    DLL_S       stPPPoEClientPendingSession;    /* ����̫���ӿ��ϴ���Discovery�׶ε�Session���� */
    DLL_S       stPPPoEClientConnectedSession;  /* ����̫���ӿ��ϴ���Session�׶ε�Session���� */
} PPPOE_CLIENT_CB_S;


/* PPPoE Client Session���ƿ����ݽṹ*/
typedef struct tagPPPoE_C_Session
{
    DLL_NODE_S        stSessionNode;/*PPPoE Client Session�ڵ�*/
    
    UCHAR             szOurMacAddr[PPPOE_MAC_LEN];/*Client physical��ַ */
    UCHAR             szHisMacAddr[PPPOE_MAC_LEN];/*Server physical��ַ */
    

    PPPINFO_S         *pstLinkHandle;       /*PPPoE Client Session����Ӧ��PPP ���ƿ�ָ��*/
    PPPOE_CLIENT_CB_S *pstPoeClientCB;      /*PPPoE Client Session����Ӧ��PPPOE Client���ƿ�ָ��*/
        
    ULONG             ulDisTickCounter;     /*discovery�׶�tick����������padi,padr���ĳ�ʱ���� */
    ULONG             ulDisTimerMaxLength;  /*discovery�׶ζ�ʱ�����ȣ���ͬ�Ľ׶Σ�ֵ�᲻ͬ*/

    ULONG             ulIdleTickCounter;    /*IDLE Timeout��ʱ��tick���� */
    ULONG             ulIdleToutMaxLength;  /*IDLE Timeout��ʱ��ʱ����ͨ�����������ã�ȱʡΪ0*/

    MBUF_QUEUE_S      stHoldQueue;          /*���interesting ���ĵ�hold queue*/

    IFNET_S           *pstEthIf;            /* ��Ӧ��̫���ӿ�IFNETָ�� */
    IFNET_S           *pstVAIf;             /* ��Ӧvirtual access�ӿ�IFNETָ�� */
    IFNET_S           *pstDialerIf;         /*��Ӧ��dialer ��ָ��*/
    
    USHORT            usBundleNumber;       /*��Ӧ��dialer��bundle number,����������*/
    USHORT            usSessionId;          /* ��Session��ID */
    
    UCHAR             ucSessionTrigger;     /*PPPoE Session�Ƿ�Ϊ���Ĵ�����ʽ*/    
    UCHAR             ucHostUniq;           /*PADI�Ƿ�Я��host unique�����������ã�Ĭ��Я��*/
    USHORT            usHostUniqValue;      /*discovery�׶α�����Я����host-unique*/

    MBUF_S            *pstPadrMbuf;         /*��һ�η��͵�padr���ı���*/
    
    ULONG             ulInPacket;           /* �յ��İ��� */
    ULONG             ulInOctets;           /* �յ����ֽ��� */
    ULONG             ulInDiscards;         /* ����ʱ�����İ��� */
    ULONG             ulOutPacket;          /* ���͵İ��� */
    ULONG             ulOutOctets;          /* ���͵��ֽ��� */
    ULONG             ulOutDiscards;        /* ����ʱ�����İ��� */
    ULONG             ulInGRDiscards;       /* ����GR����״̬ʱ���շ���Ķ������� */
    ULONG             ulOutGRDiscards;      /* ����GR����״̬ʱ���ͷ���Ķ������� */

    UCHAR             ucSessionState;       /* PPPoE Client Session�����Ľ׶� */
    UCHAR             ucSessionGRState;     /* PPPOE�Ự�ı���״̬��ȡֵ��enumPPPOE_GR_STATE */
    UCHAR             ucNotifyNpFlag;       /* ֪ͨNP����/ɾ���Ự�ı�� */
    UCHAR             ucReserve;            /*����*/
} PPPOE_C_SESSION_S;

/*��̫��֡ͷ���ݽṹ*/
typedef struct tagPPPoEEtherAddr
{
    UCHAR szDestMacAddr[PPPOE_MAC_LEN]; /* Ŀ�ĵ�ַ */
    UCHAR szSourMacAddr[PPPOE_MAC_LEN]; /* Դ��ַ */
} PPPOE_ETHER_ADDR_S;

/* module info structure of PPPoE Client */
typedef struct tagPPPOE_CLIENT_MOD_INFO_S
{
    ULONG ulModID;              /* Module id*/
    ULONG ulEthMaxSessionNum;   /*��̫�������Գ��ص�PPPoE Client�Ự*/
    ULONG ulQueID;
    
} PPPOE_CLIENT_MOD_INFO_S;

/* shell api structure of SAPRO */
typedef struct tagPPPOEClientShellCallback
{
    VOID (*pfPPPOE_Client_DbgOut) ( CHAR *strDbgOut );
    VOID (*pfPPPOE_Client_CFG_ExecOutStr) ( ULONG ulExecID, ULONG ulInfoID );
    VOID (*pfPPPOE_Client_CreateDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_CreateIdleTimer) ( VOID );
    VOID (*pfPPPOE_Client_DeleteDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_DeleteIdleTimer) ( VOID );
    VOID (*pfPPPOE_Client_PauseDisTimer) ( VOID );
    VOID (*pfPPPOE_Client_ResumeDisTimer) ( VOID );
    
}PPPOE_CLIENT_SHELL_CALLBACK_S;

/*PPPoE Sessionͳ����Ϣ*/
typedef struct tagPPPOECSTAT_S
{ 
    IFNET_S          *pstDialerIf;      /* ��Ӧ��dialer ��ָ�� */
    IFNET_S          *pstEthIf;         /* ��Ӧ��̫���ӿ�IFNETָ�� */
    
    USHORT            usSessionId;      /* ��Session��ID */
    USHORT            usBundleNumber;   /* ��Ӧ��dialer��bundle number,���������� */

    UCHAR             szOurMacAddr[PPPOE_MAC_LEN]; /* Client physical��ַ */
    UCHAR             szHisMacAddr[PPPOE_MAC_LEN]; /* Server physical��ַ */
    
    ULONG             ulInPacket;       /* �յ��İ��� */
    ULONG             ulInOctets;       /* �յ����ֽ��� */
    ULONG             ulInDiscards;     /* ����ʱ�����İ��� */
    ULONG             ulOutPacket;      /* ���͵İ��� */
    ULONG             ulOutOctets;      /* ���͵��ֽ��� */
    ULONG             ulOutDiscards;    /* ����ʱ�����İ��� */
    ULONG             ulInGRDiscards;   /* ����GR����״̬ʱ���շ���Ķ������� */
    ULONG             ulOutGRDiscards;  /* ����GR����״̬ʱ���ͷ���Ķ������� */

    UCHAR             ucSessionState;   /* PPPoE Client Session�����Ľ׶� */
    UCHAR             ucReserve[3];     /* ���� */
 
}PPPOECSTAT_S;

/*VA�ӿ���ͳ����Ϣ*/
typedef struct tagVASTAT_S
{
    ULONG             ulLinkStatus;     /* ��·��״̬ */

    ULONG             ulInOctets;       /* �յ����ֽ��� */
    ULONG             ulOutOctets;      /* ���͵��ֽ��� */
    ULONG             ulInPackets;      /* �յ��İ��� */
    ULONG             ulOutPackets;     /* ���͵İ��� */
    ULONG             ulBadFcsPackets;
    ULONG             ulBadAddressPackets;
    ULONG             ulBadControlPackets;
}VASTAT_S;


#ifdef __cplusplus
}
#endif

#endif 


