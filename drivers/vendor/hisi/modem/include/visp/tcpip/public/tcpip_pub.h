
#ifndef _TCPIP_PUB_H_
#define _TCPIP_PUB_H_

#ifdef  __cplusplus
extern "C"{
#endif

#define LINK_INPUT  1  /*��·��ע�ṳ�����뷽��*/
#define LINK_OUTPUT 0  /*��·��ע�ṳ���������*/

#define MAX_LINK_MAXPKT    1024           /*�û�����N_Maxֵ������*/
#define DEFAULT_LINKPKT_NUM    1          /*����Э��ջĬ��Nֵ*/
#define DEFAULT_LINK_MAXPKT   128         /*Э��ջĬ��N_Maxֵ*/

#define DEFAULT_SOCK_SCHEDULE  256        /*SOCK����Ĭ���¼������ĵ��ȴ���*/
#define MAX_SOCK_SCHEDULE      1024       /*SOCK��������¼������ĵ��ȴ���*/
#define DEFAULT_SOCK_DELAY     10         /*SOCK����Ĭ�ϴﵽ���ȴ�������ʱ*/
#define MAX_SOCK_DELAY         40         /*SOCK�������ﵽ���ȴ�������ʱ*/
#define LINK_UPDOWN_STEP       4          /*��·up/down�¼�Ȩ��*/

#define CHARACTER_BACKSLASH     0x5c   /*��ʾ�ַ�'\'*/

#define MEM_IPv4_MAX_MID    128    /*ģ���ڴ�ͳ����IPV4��������ģ��ID��Ӧ����������*/
#define MEM_MAX_MID         256    /*ģ���ڴ�ͳ������������ģ��ID��Ӧ����������*/

#define  SOCK_POINT_MAX_RUN_TIME        800  /*SOCK ���ε������ʱ�� ms*/
#define  SOCK_POINT_DEFAULT_RUN_TIME    40   /*SOCK ���ε���Ĭ��ʱ�� ms*/
#define  SOCK_POINT_MAX_FREE_TIME       100  /*SOCK �����ͷ����ʱ�� ms*/
#define  SOCK_POINT_DEFAULT_FREE_TIME   40   /*SOCK �����ͷ�Ĭ��ʱ�� ms*/

/* �ƶ��ڴ�ָ�� */
#define MEM_INCPTR(n, cp)   ((cp) += (n))
#define MEM_DECPTR(n, cp)   ((cp) -= (n))

/*���ڴ��л�ȡ4�ֽ�ֵ,����ǰƫ��4�ֽ�ָ��.
Ҫ�����ָ���׵�ַΪ4������,�Ա�֤���������ֽڶ��������*/
#define MEM_GETLONG(l, cp) { \
    (l) = *((ULONG *)cp); \
    cp += sizeof(ULONG) ; \
}
/*���ڴ�������4�ֽ�ֵ,����ǰƫ��4�ֽ�ָ��.
Ҫ�����ָ���׵�ַΪ4������,�Ա�֤���������ֽڶ��������*/
#define MEM_PUTLONG(l, cp) { \
    *((ULONG*)cp) = l; \
    cp += sizeof(ULONG); \
}

#define SOCKRUN_SCHED_NUM_MIN   32
#define SOCKRUN_SCHED_NUM_MAX   512

/*��ȡTICK�ĸߵ�λ�ṹ*/
typedef struct tagTCPIP_CPUTICK
{
    ULONG  ulLowTick;
    ULONG  ulHighTick;
}TCPIP_CPUTICK_S;

 /*��·��ע�ṳ�ӵ�����ṹ*/
typedef struct tagLINK_HOOK_NODE
{
    ULONG                     ulPriority;
    TCPIP_LINK_HOOK_FUNC      pfLinkHookFunc;
    struct tagLINK_HOOK_NODE *pstNext;
}LINK_HOOK_NODE_S;

/* ϵͳʱ��ṹ */
typedef struct tagTCPIP_TIME
{
    USHORT usYear;       /* 1970-... */
    UCHAR  ucMonth;      /* 1-12     */
    UCHAR  ucDate;       /* 1-31     */

    UCHAR  ucHour;       /* 0-23 */
    UCHAR  ucMinute;     /* 0-59 */
    UCHAR  ucSecond;     /* 0-59 */
    UCHAR  ucReseved;
}TCPIP_TIME_S;

/* ��Դռ�ó�����ֵ����������ʱ������ά��ʱ�Ĺ�ϣ�������С */
#define RESLIMIT_TIME_MAX       0xFFFFFFFF
#define RESLIMIT_TIME_MINUTE    60

#define RESLIMIT_RESTRAINTIME_MIN 0
#define RESLIMIT_RESTRAINTIME_MAX 60

/* Ŀǰ֧��16����Դ���� */
#define RESLIMIT_MAXGROUP_SIZE  17

#define VISP_VRRP 1
#define EXTR_VRRP  2

/*Added for PTPV2, PTP ��������*/
#define PTPCOMP_VERSION_NULL  0
#define PTPCOMP_VERSION_OLD  1 
#define PTPCOMP_VERSION_NEW  2

/* Added by qinyun62011, (Distribute socket)�ֲ�ʽsocket�ü�, 2014/3/11 */
typedef struct tagTCPIP_DESTINFO
{
    UCHAR ucFamilyType;     /*Э������:AF_INET/AF_INET6*/
    UCHAR ucRes[3];
    ULONG ulDestAddr[4];    /*Ŀ�ĵ�ַ��������
                            ��Ŀ�ĵ�ַΪ�㲥��ַ��ȫ0��ַ���򷵻ر�VRF���һ����Ч��ַ�ͼ��ӿڼ���*/
    ULONG ulVrfIndex;       /*VRF����*/
}TCPIP_DESTINFO_S;
typedef struct tagTCPIP_GETSRCADDROUT
{
    ULONG ulSrcAddr[4];     /*Դ��ַ��������*/
    ULONG ulNexthop[4];     /*��һ����ַ��������*/
    ULONG ulIfIndex;        /*���ӿ���Ϣ*/
}TCPIP_GETSRCADDROUT_S;
typedef ULONG (*TCPIP_GETSRCADDRHOOK_FUNC)(TCPIP_DESTINFO_S *pInfoIn,TCPIP_GETSRCADDROUT_S *pInfoOut);
typedef ULONG (*TCPIPGETMTU_HOOK_FUNC)( TCPIP_DESTINFO_S* pInfo,LONG *plMTU );
/* End of Added by qinyun62011, 2014/3/11 */

/* ��Դռ�ó�����ֵʱ��Ҫ��¼��־�����ռ�ó�����ֵ���������������
����Ҫ����־��¼�����������(�ڹ涨ʱ����ֻ���һ����־)�����Ʋ����Ǹ�����Դ���ͽ��е� */
typedef enum tagResLimit_ResType
{
    RESTYPE_QUE_LINK_LAYER = QUE_LINK_LAYER,                 /* ��·�������Դ */
    RESTYPE_QUE_ARP = QUE_ARP,                               /* ARP������Դ */
    RESTYPE_QUE_PPP_NEGO = QUE_PPP_NEGO,                     /* PPPЭ�̶�����Դ */
    RESTYPE_QUE_PPP_ASY = QUE_PPP_ASY,                       /* PPPͬ��������Դ */
    RESTYPE_QUE_PPP_STAC = QUE_PPP_STAC,                     /* PPP STAC������Դ */
    RESTYPE_QUE_PPP_MP = QUE_PPP_MP,                         /* MP������Դ */
    RESTYPE_QUE_IP_INPUT = QUE_IP_INPUT,                     /* IPv4������Դ */
    RESTYPE_QUE_IPV6_INPUT = QUE_IPV6_INPUT,                 /* IPv6����Դ */
    RESTYPE_QUE_PPPOE_CLIENT_INPUT = QUE_PPPOE_CLIENT_INPUT, /* PPPoE Client������Դ */
    RESTYPE_QUE_PPPMUX_INPUT = QUE_PPPMUX_INPUT,             /* PPPMUX������Դ */
    RESTYPE_QUE_LACP = QUE_LACP,                             /* LACP���Ķ�����Դ */
    RESTYPE_QUE_POES = QUE_POES,                             /* PPPoE Server���Ķ�����Դ */
    RESTYPE_QUE_ISIS_INPUT = QUE_ISIS_INPUT,                 /* ISIS���Ķ��� */
    RESTYPE_QUE_INARP = QUE_INARP,                           /* INARP������Դ */

    RESTYPE_MP_REORDER_WIN,                                  /* MP���鴰����Դ */

    RESTYPE_MAX                                              /* ��Դ�������ֵ */
}RESLIMIT_RESTYPE_E;

extern ULONG g_ulPingForbidFlag;

extern ULONG g_ulMemStat[MEM_MAX_MID];
extern ULONG g_ulSockScheduleTime;
extern ULONG g_ulSockScheduleSwitch;
extern ULONG g_ulSockRunTime;
extern ULONG g_ulSockScheduleDelay;

extern ULONG g_ulCreateEthIfTimeTotal ;
extern ULONG g_ulCreateEthIfCount ;
extern ULONG g_ulCreateEthIfPPITimeTotal ;
extern ULONG g_ulCreateEthIfPhyIoTimeTotal ;
extern ULONG g_ulCreateLoopIfTimeTotal ;
extern ULONG g_ulCreateLoopIfCount ;
extern ULONG g_ulSubIfCreateTimeTotal ;
extern ULONG g_ulSubIfCreateCount ;
extern ULONG g_ulCreateLoopIfPPITimeTotal ;
extern ULONG g_ulSubIfNpTimeTotal ;
extern ULONG g_ulAddrPerfCfgTime ;
extern ULONG g_ulAddrPerfCfgCount ;
extern ULONG g_ulAddrPPIPerfTime;
/*End of Add*/

typedef VOID (*BFD_IF_DEL_HOOK_FUNC)(ULONG);

extern VOID *TCPIP_MemMove(VOID *pVoidDes, const VOID *pVoidSrc, ULONG ulLen);
extern CHAR *TCPIP_GetMidInfo(ULONG ulMid);
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
extern ULONG TCPIP_DealLinkHook(MBUF_S *pstMBuf, ULONG ulInputOrOutput);
extern ULONG TCPIP_GetCpuTickPerMs(ULONG *pulCPU_TICKS_PER_MS);
extern VOID TCPIP_MacToString(CHAR *szMac,CHAR *szString);
extern ULONG TCPIP_Get_CurrentTime(TCPIP_TIME_S *pstTime);
extern ULONG TCPIP_ResLimit_IsOverTime(ULONG ulResType, ULONG ulTimeHigh, ULONG ulTimeLow);
extern VOID TCPIP_ResLimitMaintain(ULONG ulIfIndex, ULONG ulResType, ULONG ulResLimitVal, ULONG ulCurrentVal);
extern VOID TCPIP_RecordMemErrInfo(ULONG ulType,  ULONG ulPara0, ULONG ulPara1, ULONG ulPara2, ULONG ulPara3);
extern ULONG TCPIP_VirtualIpAddrConflict(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr);
extern ULONG TCPIP_CompareVirtualMac(VOID *pfCompTbl, VOID *pstIf, UCHAR *aucMacAddr);
extern ULONG TCPIP_GetVirtualMacByVip(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);
extern ULONG TCPIP_GetVirtualMacByIpAddr(VOID *pfCompTbl, ULONG ulIfIndex, ULONG ulIpAddr, UCHAR *aucMacAddr);
extern ULONG TCPIP_IsVipInVrf(ULONG ulVrfIndex, ULONG ulIpAddr);
extern ULONG TCPIP_ISVirtualMacToFillEthSourcMac(VOID *pfCompTbl, MBUF_S *pstMbuf);

extern ULONG TCPIP_GetMemInfo(ULONG ulInfo);
extern VOID TCPIP_AddrSpecoOptimizeFlag(VOID);
extern VOID TCPIP_ShowPerfInfo(VOID);
extern VOID TCPIP_ClearPerfInfo(ULONG ulFlag);
/*End of Add*/
/*���º�����ɾ��VRF��I3ͬ��*/
#define I3_SYN_WAITING  0xAAAA
#define I3_SYN_FINISHED 0xEEEE
#define I3_SYN_INTERVAL 10
#define I3_CFG_SEM_MAX_WAIT_TIME 20000
/*End of Add*/
#define I3_SYN_TRY_TIMES 500
extern VOID I3_WaitI3Syn(VOID);

extern gpfTCPIPUserStop         g_pfTCPIPUserStop;      /* �û�����ֹͣ����� */
extern gpfTCPIPTrrtUserStopEx       g_pfTCPIPTrrtUserStopEx;
extern gpfTCPIPPingUserStopEx       g_pfTCPIPPingUserStopEx;

extern CreateMutex_HOOK_FUNC    g_pfTCPIPCreateMutex;   /* �����ź������� */
extern CreateSm_HOOK_FUNC       g_pfTCPIPCreateSm;      /* �����ź������� */
extern SmP_HOOK_FUNC            g_pfTCPIPSmP;           /* ��ȡ�ź������� */
extern SmV_HOOK_FUNC            g_pfTCPIPSmV;           /* �ͷ��ź������� */
extern DeleteMutex_HOOK_FUNC    g_pfTCPIPDeleteMutex;   /* ɾ���ź������� */

extern LINK_HOOK_NODE_S      *g_pstLinkInputHook;    /*��·��ע�ṳ�ӽ��շ�������ͷ���*/
extern LINK_HOOK_NODE_S      *g_pstLinkOutputHook;   /*��·��ע�ṳ�ӷ��ͷ�������ͷ���*/

extern gpfGetSockMaxNum g_pfGetSockMaxNum;
extern gpfRegAllAppInfo g_pfRegAllAppInfo;
extern BFD_IF_DEL_HOOK_FUNC g_pfBfdIfDeleteNotify;

extern TCPIP_VirtualIpAddrConflict_HOOKFUNC g_pfVirtualIpAddrConflict;
extern TCPIP_CompareVirtualMac_HOOKFUNC     g_pfCompareVirtualMac;
extern TCPIP_IsVipInIf_HOOKFUNC             g_pfIsVipInIf;
extern TCPIP_GetVirtualMacByIpAddr_HOOKFUNC g_pfGetVirtualMacByIpAddr;

/* ��ȡ���MTU */
extern gpfTCPIP_GetTunnelMtu_HOOK_FUNC g_pfGetTunnelMtu_HOOK_FUNC;

extern TCPIP_IsNeedWarning_HOOK_FUNC        g_pfIsNeedWarning;


extern ULONG (*g_pfVrrpGetBfdMaxSessID)(VOID);

/*LLDPģ��Trunk�����շ�����*/
typedef ULONG     (*gpfTrunkLLDPRcvPkt_HOOK_FUN)(MBUF_S * pMBuf);
extern ULONG  g_ulTaskMonitorMaxtime;
extern TCPIP_TASK_MONITOR_PARA_S g_stTaskMoniterPara;

typedef ULONG  (*pfBfdMonitorHOOK_Func)(VOID); /*�����̼߳���BFD ��������*/

typedef ULONG  (*pfTWAMPMonitorHOOK_Func)(VOID); /*TWAMP Monitor Hook function*/

/* Added by qinyun62011, (Distribute socket)�ֲ�ʽsocket�ü�, 2014/3/11 */
extern TCPIP_GETSRCADDRHOOK_FUNC g_pfGetSrcAddrHookFunc;
extern TCPIPGETMTU_HOOK_FUNC g_pfGetMtu_HookFunc;
ULONG TCPIP_RegFuncGetSrcAddrHook( TCPIP_GETSRCADDRHOOK_FUNC pfFuncHook );
ULONG TCPIP_RegFuncGetMtuHook( TCPIPGETMTU_HOOK_FUNC pfFuncHook );
/* End of Added by qinyun62011, 2014/3/11 */

extern ULONG g_ulNeedShutIFForVRFChange;
extern ULONG g_ulTcpTimerFlag; /*2015/8/27 for Balong Timer modify wangbin*/
#ifdef  __cplusplus
}
#endif
#endif /* _PUBLIC_PUBLIC_H_ */


