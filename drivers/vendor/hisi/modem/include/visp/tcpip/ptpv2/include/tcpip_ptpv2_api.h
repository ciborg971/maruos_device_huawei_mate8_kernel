/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_ptpv2_api.h
*
*  Project Code:
*   Module Name: PTPV2 api
*  Date Created: 2014-03-3
*        Author: luoagwoei & dutianyi
*   Description: ��Ҫ�ṩ����Ʒ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-3      luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _TCPIP_PTPV2_API_h_
#define _TCPIP_PTPV2_API_h_

#ifdef __cplusplus
extern "C" {
#endif

/*PTP  �˿ڵ�״̬��ɫ*/
#define  TCPIP_PTP_PORT_ROLE_UNDEFINED  0
#define  TCPIP_PTP_PORT_ROLE_MASTER     1
#define  TCPIP_PTP_PORT_ROLE_SLAVE      2
#define  TCPIP_PTP_PORT_ROLE_PASSIVE    3  /*BC�� ϵͳû��ѡ��Դʱ��˿ڵ�״̬*/

/* announce��С���ճ�ʱ���� */
#define TCPPI_PTP_MIN_ANN_RCV_TIMEOUT        2

/* announce��С���ͼ��(ָ��) */
#define TCPPI_PTP_MIN_ANN_SND_TIMEOUT        -3
/* announce����ͼ��(ָ��) */
#define TCPPI_PTP_MAX_ANN_SND_TIMEOUT        3

/* PPI��Ϣ�е�Դ�����仯��� */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_NONE   0     /* Դû�в��������仯 */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_BMC    0x01  /* ��ѡԴ�����仯 */
#define  TCPIP_PTP_PARA_CHANGE_FIELD_UTC    0x02  /* Դ��UTC���������仯 */

/*����ʱ���豸����ö��*/
typedef enum tagPTPV2_TYPE_E
{
    PTPV2_CLOCK_TYPE_NULL = 0,    /*0  NULL*/
    PTPV2_CLOCK_TYPE_OC,         /*1  OC */
    PTPV2_CLOCK_TYPE_BC,        /*2  BC*/
    PTPV2_CLOCK_TYPE_END
} PTPV2_TYPE_E;

/*PTP�����붨��*/
typedef enum tagTCPIP_PTP_ERR_E
{
    TCPIP_PTP_OK = 0,
    TCPIP_PTP_ERR,
    TCPIP_PTP_ERR_POINTER_NULL,         /* 2.ָ��Ϊ�մ��� */
    TCPIP_PTP_ERR_UNINIT,               /* 3.ʱ��ʵ��δ��ʼ�� */
    TCPIP_PTP_ERR_OTHER_PTP_USED,       /* 4.PTPV1�Ѿ���ʼ�� */
    TCPIP_PTP_ERR_INVALID_PARA,         /* 5.�������� */
    TCPIP_PTP_ERR_HOOK_UNREG,           /* 6.�ص�����δע�� */
    TCPIP_PTP_ERR_INVALID_RCVINDEX,     /* 7.һ��Master�ı��Ĵӱ��˵Ķ���ӿ������յ� */
    TCPIP_PTP_ERR_INVALID_MBUF,         /* 8.MBUF�Ƿ� */
    TCPIP_PTP_ERR_WRITE_QUE_FAIL,       /* 9.д����ʧ�� */
    TCPIP_PTP_ERR_PACKET_LEN,           /* 10.���ĳ��ȷǷ� */
    TCPIP_PTP_ERR_INTF_NOT_EXIST,       /* 11.�ӿڲ����� */
    TCPIP_PTP_ERR_MSGTYPE,              /* 12.��Ϣ���ʹ��� */
    TCPIP_PTP_ERR_NOT_SUPPORT_IN_OC,    /* 13.OC�²�Ӧ����PPI�·������ */
    TCPIP_PTP_ERR_NO_TIME_SOURCE,       /* 14.PTP��û��ѡ����ʱ��Դ */
    TCPIP_PTP_ERR_MASTER_UP_MAX,        /* 15.ForeignMaster�����Ѵ����ֵ */
    TCPIP_PTP_ERR_MALLOC_FAIL,          /* 16.�ڴ����ʧ�� */
    TCPIP_PTP_ERR_INTF_TYPE,            /* 17.��֧�ֵĽӿ����� */
    TCPIP_PTP_ERR_PROTNO_FULL,          /* 18.�˿ں����þ� */
    TCPIP_PTP_ERR_PROTINFO_NOT_EXIST,   /* 19.�˿���Ϣ������ */
    TCPIP_PTP_ERR_PACKET,               /* 20.���Ŀ������ֶδ���*/
    TCPIP_PTP_ERR_PORTID,               /* 21.ForeignMaster��ClockID�Ͷ˿ںŷ����˱仯*/
    TCPIP_PTP_ERR_NON_L2IF,             /* 22.��ǰʹ���˷ǲ�2�ӿ�*/
    TCPIP_PTP_ERR_TIMER_NUM_FULL,       /* 23.�߼���ʱ�������Ѵ����ֵ */
    TCPIP_PTP_ERR_INVALID_DOMAIN,       /* 24.�յ��˲���ͬһ����ı��� */
    TCPIP_PTP_ERR_LOGIC_TIMERID_NULL,   /* 25.�߼���ʱ��IDΪ�� */
    TCPIP_PTP_ERR_LOGIC_TIMER_NUM_ZERO, /* 26.��ǰû���߼���ʱ�� */
    TCPIP_PTP_ERR_CAST_MODE,            /* 27.��֧�ֱ��ĵ�CastMode */
    TCPIP_PTP_ERR_CLOCK_ACCURACY,       /* 28.��Ч��ʱ�Ӿ��� */
    TCPIP_PTP_ERR_SYSTEM_EXCEPTION,     /* 29.ϵͳ�쳣��ȫ��/�˿���Ϣ�޷���ȡ */
    TCPIP_PTP_ERR_NO_START,             /* 30.�˿�δ���� */
    TCPIP_PTP_ERR_CREATE_QUEUE_FAILED,  /* 31.��������ʧ�� */
    TCPIP_PTP_ERR_CREATE_TIMER,         /* 32.��ʱ������ʧ�� */
    TCPIP_PTP_ERR_PORTNO,               /* 33.��Ч�Ķ˿ں� */
    TCPIP_PTP_ERR_VERSION,              /* 34.�����PTP�汾 */
    TCPIP_PTP_ERR_SEQUENCEID,           /* 35.�����PTP��� */
    TCPIP_PTP_ERR_UNICASTFLAG,          /* 36.���ĵĵ��ಥģʽ�Ƿ� */
    TCPIP_PTP_ERR_CREATE_TASK,          /* 37.��������ʧ�� */
    TCPIP_PTP_ERR_SMP_TIMEOUT,          /* 38.ȥ��ʼ���ȴ��ź�����ʱ */
    TCPIP_PTP_ERR_ALREADY_STARTED,      /* 39.��ǰ�˿��Ѿ����� */
    TCPIP_PTP_ERR_CLOCKID,              /* 40.�����ʱ��ID */
    TCPIP_PTP_ERR_BMC_ERRNO1,           /* 41.ForeMaster�뱾�˵�ʱ��Idһ��,AR-IP-PTP.002*/
    TCPIP_PTP_ERR_BMC_ERRNO2,           /* 42.ForeMaster�뱾�˵�ʱ��portnumһ��,AR-IP-PTP.002*/
    TCPIP_PTP_ERR_STEPSREMOVED,         /* 43.�յ���StepsRemoved���ڵ���255��Ann���� */
    TCPIP_PTP_ERR_MAX = 255
} TCPIP_PTP_ERR_E;


/* ʱ�侫��ö�ٶ��� */
typedef enum tagTCPIP_PTP_CLOCK_ACCURACY_E
{
    TCPIP_PTP_CLOCK_ACCURACY_25NS = 0X20, /*The time is accurate to within 25 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_100NS,       /*The time is accurate to within 100 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_250NS,       /*The time is accurate to within 250 ns*/
    TCPIP_PTP_CLOCK_ACCURACY_1US,         /*The time is accurate to within 1 us*/
    TCPIP_PTP_CLOCK_ACCURACY_2P5US,       /*The time is accurate to within 2.5 us*/
    TCPIP_PTP_CLOCK_ACCURACY_10US,        /*The time is accurate to within 10 us*/
    TCPIP_PTP_CLOCK_ACCURACY_25US,        /*The time is accurate to within 25 us*/
    TCPIP_PTP_CLOCK_ACCURACY_100US,       /*The time is accurate to within 100 us*/
    TCPIP_PTP_CLOCK_ACCURACY_250US,       /*The time is accurate to within 250 us*/
    TCPIP_PTP_CLOCK_ACCURACY_1MS,         /*The time is accurate to within 1 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_2P5MS,       /*The time is accurate to within 2.5 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_10MS,        /*The time is accurate to within 10 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_25MS,        /*The time is accurate to within 25 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_100MS,       /*The time is accurate to within 100 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_250MS,       /*The time is accurate to within 250 ms*/
    TCPIP_PTP_CLOCK_ACCURACY_1S,          /*The time is accurate to within 1 s*/
    TCPIP_PTP_CLOCK_ACCURACY_10S,         /*The time is accurate to within 10 s*/
    TCPIP_PTP_CLOCK_ACCURACY_M10S         /*The time is accurate to >10 s*/
} TCPIP_PTP_CLOCK_ACCURACY_E;


/* �������Ͷ��� */
typedef enum tagTCPIP_PTP_MSG_TYPE_E
{
    TCPIP_PTP_MSG_SYNC              =       0,     /* Sync */
    TCPIP_PTP_MSG_DELAY_REQ,                       /* Delay_Req */
    TCPIP_PTP_MSG_PDELAY_REQ,                      /* Pdelay_Req */
    TCPIP_PTP_MSG_PDELAY_RESP,                     /* Pdelay_Resp */
    TCPIP_PTP_MSG_LIVE,                            /* keep alive packet */
    /* 5~7Ԥ�� */
    TCPIP_PTP_MSG_FOLLOW_UP         =       0x8,   /* Follow_Up */
    TCPIP_PTP_MSG_DELAY_RESP,                      /* Delay_Resp */
    TCPIP_PTP_MSG_PDELAY_RESP_FOLLOW_UP,           /* Pdelay_Resp_Follow_Up */
    TCPIP_PTP_MSG_ANNOUNCE,                        /* Announce */
    TCPIP_PTP_MSG_SIGNALING,                       /* Signaling */
    TCPIP_PTP_MSG_MANAGEMENT,                      /* Management */
    TCPIP_PTP_MSG_MAX
} TCPIP_PTP_MSG_TYPE_E;

/*PPI ����ö�ٶ���*/
typedef enum tagTCPIP_PTP_PPI_CMD_E
{
        TCPIP_PTP_PPI_ADD = 0,        /* ѡ��ʱ��Դ*/
        TCPIP_PTP_PPI_DEL,            /* ɾ��ʱ��Դ*/
        TCPIP_PTP_PPI_UPDATE,         /* Դ��UTC�������Ƿ���ѡԴ�����仯*/
        TCPIP_PTP_PPI_MAX
} TCPIP_PTP_PPI_CMD_E;

/* �˿ڵ�ַ���� */
typedef struct tagTCPIP_PTP_PORT_ADDR_S
{
    USHORT  usNetworkProtocol;
    USHORT  usAddressLength;
    union
    {
        ULONG   ulIpv4;         /* �����ֽ��� */
        UCHAR   ucMacAddr[8];   /*physical��ַ 8�ֽ�Ϊ�˶���*/
        ULONG   ulIpv6[4];      /*IPv6��ַ�������ֽ��� */
    } unAddr;
} TCPIP_PTP_PORT_ADDR_S;

#define TCPIP_PTP_CLOCK_ID_LEN      8

#pragma pack(1)
/*PTP clock ID*/
typedef UCHAR TCPIP_PTP_CLOCK_ID_SZ[TCPIP_PTP_CLOCK_ID_LEN];

typedef struct tagTCPIP_PTP_PORT_ID_S   /*PTP port ID*/
{
    TCPIP_PTP_CLOCK_ID_SZ szClockId;
    USHORT          usPortNumber;
}TCPIP_PTP_PORT_ID_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*�˿����ݼ�*/
typedef struct tagTCPIP_PTP_PORT_DS
{
    ULONG ulIfIndex;  /*�ӿ�����������OC�����ص�һ��*/
    USHORT usPortNo;  /*port number*/
    UCHAR ucPortState; /*�˿ڵ�״̬*/
    CHAR   clogAnnounceInterval;      /*Announce���ͼ��*/
    UCHAR  ucAnnRcvTimeoutNum;  /*announce���ճ�ʱ����*/
    UCHAR  ucCastMode;/*�������ಥģʽ��Ŀǰ��֧��L2�鲥*/
    UCHAR  ucDomain;  /*��*/
    UCHAR  ucPortRole; /*�˿ڽ�ɫ*/
    UCHAR  ulPading[32]; /*Ԥ���ֶ�*/
} TCPIP_PTP_PORT_INFO_S;

typedef struct tagTCPIP_PTP_CLOCK_QA_S
{
    UCHAR   ucClockClass;                   /* ʱ�ӵȼ� */
    UCHAR   ucClockAccuracy;                /* ʱ�Ӿ��� */
    USHORT  usOffsetScaledLogVariance;      /* ʱ���ȶ��� */
} TCPIP_PTP_CLOCK_QA_S;

typedef struct tagPTCPIP_PTP_PKT_STAT
{
    ULONG ulSndAnnPackets;              /*����Announce���� */
    ULONG ulRcvAnnPackets;              /*����announce���� */
    ULONG ulRcvErrorPackets;
    ULONG ulRcvErrorTotalLenPackets;    /*����TotalLen�Ƿ��ı���*/
    ULONG ulRcvErrorDomainNoPackets;    /*���ղ���ͬ��ı���*/
    ULONG ulRcvErrorPtpLenPackets;      /*����PtpLen�Ƿ��ı���*/
    ULONG ulRcvErrorAddrPackets;        /*���յ�ַ��Ϣ�Ƿ��ı���*/
    ULONG ulRcvErrorClockIdPackets;     /*����ClockId��ͬ�ı���*/
    ULONG ulRcvErrorSeqIdPackets;       /*����SeqId����ı���*/
    ULONG ulRcvErrorUnexpectedSeqIdPackets; /*���շ�Ԥ��SeqId�ı��ģ����Ǵ���*/
    ULONG ulRcvErrorIfPackets;          /*ͬһ��ForeMaster�ı��ĴӲ�ͬ����ڱ��յ�*/
    ULONG ulRcvErrorForeMasterPackets;  /*���յ���ForeMaster���������ʧ�ܵı���*/

    ULONG ulSndDropPackets;             /*Ifģ�鷢��ʧ�ܶ���*/
    ULONG ulSndBuildDropPackets;        /*���͹���ʧ�ܶ���*/
    ULONG ulSndGetIfDropPackets;        /*���ͻ�ȡIf���ƿ�ʧ�ܶ���*/
    ULONG ulReserve[25];
} TCPIP_PTP_PKT_STAT_S; /*PTP ����ͳ��*/

/* IP/UDP��Ϣ����Ҫ����
   1)�յ�����֮�󣬽��յ����ĵ�IP/UDP��Ϣ��֯��������Ϊ�����������Ľ��պ���
   2)�û�����IP��UDP�˿ڵ�ʱ�����
*/
typedef struct tagTCPIP_PTP_ADDRINFO_S
{
    TCPIP_PTP_PORT_ADDR_S  stDstPortAddr;   /* Ŀ�ĵ�ַ��Ϣ�������򡣶Խ��ձ�����˵��Ŀ�ĵ�ַ��Ϊ���ص�ַ���Է��ͱ�����˵��Ŀ�ĵ�ַΪ�Զ˵�ַ */
    TCPIP_PTP_PORT_ADDR_S  stSrcPortAddr;   /* Դ��ַ��Ϣ�������򡣶Խ��ձ�����˵��Դ��ַ��Ϊ�Զ˵�ַ���Է��ͱ�����˵��Դ��ַΪ���˵�ַ */
    ULONG            ulDstUdpPort;      /* Ŀ��UDP�˿ڣ������� */
    ULONG            ulSrcUdpPort;      /* ԴUDP�˿ںţ������� */
    ULONG            ulVrfIndex;        /* ����VRF index */
    ULONG            ulIfIndex;         /* �����ڱ��Ľ��մ����б�����ӿ����������������в�ʹ��*//*qinyun&luogaowei 0��ַ���� 2011-12-12*/
}TCPIP_PTP_ADDRINFO_S;

typedef ULONG (* TCPIP_PTP_PPI_HOOK_FUNC) (ULONG ulPtpFsmRole, ULONG ulPtpPpiCmd, void* pstPtpPpiInfo);
typedef ULONG (* TCPIP_PTP_CAPTURE_PACKET_FUNC)(ULONG ulInOrOut, UCHAR* pucPacket, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstIpUdpInfo, ULONG ulPortNo);

/*�澯,ά�����*/
#define TCPIP_PTP_WARNING_BEGIN 1  /*�澯�ϱ�*/
#define TCPIP_PTP_WARNING_END  0   /*�澯ȡ��*/

/*�澯ID*/
typedef enum tagTCPIP_PTP_WARN_ID_E
{
    TCPIP_PTP_WARN_BMC_FAIL = 0,    /*30����ѡ����Դ�ĸ澯*/
    TCPIP_PTP_WARN_ID_MAX           /*PTP WARNING ID ���ֵ */
}TCPIP_PTP_WARNINGID_E;

typedef struct tagTCPIP_PTP_WARN_PARAM_S
{
    UCHAR ucWarnType;/*�澯����*/
    UCHAR ucWarnState; /*�澯����,1-�澯,0-�ָ��澯*/
    UCHAR ucReserve[2];
}TCPIP_PTP_WARN_PARAM_S;

/* ��ȡ���ķ���:1--�뷽��;0--������ */
#define TCPIP_PTP_PKT_IN    1
#define TCPIP_PTP_PKT_OUT   0

/* �澯��Ϣ�������ָ�����Ͷ��� */
typedef ULONG (* TCPIP_PTP_WARN_OUTPUT_FUNC) (TCPIP_PTP_WARN_PARAM_S *pstPtpWarnPara);

/* Debug��Ϣ�������ָ�����Ͷ��� */
typedef VOID (* TCPIP_PTP_DBG_OUTPUT_FUNC)(CHAR *pszMsg);

/*PTP defualt DS*/
typedef struct tagTCPIP_PTP_DEFAULT_DS
{
    ULONG   ulNumberPorts;
    TCPIP_PTP_CLOCK_QA_S stCfgClockQa;/* ʱ�ӵȼ� ʱ�Ӿ��� ʱ���ȶ��� */
    BOOL_T  bTwoStepFlag;
    UCHAR   ucPriority1;
    UCHAR   ucPriority2;
    USHORT  usClockFsmMode;
    /*master ʹ�� UTC ����*/
    SHORT   sCurrentUtcOffset;
    BOOL_T  bCurrentUtcOffsetValid;
    BOOL_T  bLeap61;
    BOOL_T  bLeap59;

    UCHAR   ucDomainNumber;
    UCHAR   ucPriClassFlag;/*����Ƿ�ѡ����ѡԴ*/
    UCHAR   ucClass0;/*��ѡԴ0*/
    UCHAR   ucClass1;/*��ѡԴ1*/
    UCHAR   ucClass2;/*��ѡԴ2*/
    UCHAR   ucClass3;/*��ѡԴ3*/

    CHAR    szReserved[8];
} TCPIP_PTP_DEFAULT_DS_S;

/*����ѡ�е�ʱ��Դ*/
typedef struct TagTCPIP_PTP_PARENT_DS
{
    TCPIP_PTP_CLOCK_ID_SZ   szGrandMasterId;
    TCPIP_PTP_PORT_ID_S     stParentPortId;
    TCPIP_PTP_PORT_ADDR_S   stParentAddr;
    TCPIP_PTP_CLOCK_QA_S    stParentClockQA;
    UCHAR   ucGrandmasterPriority1;
    UCHAR   ucGrandmasterPriority2;

    BOOL_T      bCurrentUtcOffsetValid;
    SHORT       sCurrentUtcOffset;      /*��ǰUTCƫ�� */
    BOOL_T      bLeap59;
    BOOL_T      bLeap61;

    BOOL_T      bTimeTraceable;
    BOOL_T      bFrequencyTraceable;    /*�Ƿ�׷�ٵ���ʱ��Ƶ��*/
    BOOL_T      bTimeScale;
    BOOL_T      bPtpTimescale;          /*����һ��ʱ�ӻ�ȡʱ����*/
    UCHAR       ucTimeSource;           /*ʱ��Դ :����һ��ʱ�ӻ�ȡ*/
    CHAR        cLogMAnnInterval;       /*Ann�ķ��ͼ������Ann����ѧ�����ಥ��ʹ��*/
    USHORT      usStepsRemoved;         /*����Ϊ0*/
    UCHAR       ucBestClassFlag;        /*�Ƿ������ѡԴ���*/
    UCHAR       ucPadding[9];
} TCPIP_PTP_PARENT_DS_S;

/*slave�·�PPI*/
typedef struct tagTCPIP_PTP_SLAVE_PPI
{
    ULONG   ulIfIndex;                      /*�ӿ�����*/
    TCPIP_PTP_PORT_ADDR_S stLocalAddr;      /*����ַ*/
    USHORT  usLocalPortNo;                  /*PTP�˿ں�*/
    BOOL_T  bTwoStep;                       /*�Ƿ��ǵ�˫��ʱ��*/
    ULONG   ulChangeField;                  /*Դ�仯����Ϣ: UTC�仯��class�仯*/    
    UCHAR   Reserved[124];
    TCPIP_PTP_PARENT_DS_S  stParentDS;      /*ѡ��Դ����Ϣ*/
} TCPIP_PTP_SLAVE_PPI_S;

typedef struct tagTCPIP_PTP_SYSTEM_INFO
{
    TCPIP_PTP_CLOCK_ID_SZ   szClockId;      /*clock id*/
    TCPIP_PTP_DEFAULT_DS_S  stDefaultDS;    /* ���豸���õ�ʱ����Ϣ*/
    TCPIP_PTP_PARENT_DS_S   stParentMasterDS;/*ѡ�е�ʱ��Դ��Ϣ*/
} TCPIP_PTP_SYSTEM_INFO_S;

/*�˿�״̬������ȷ�ϳ��˿ڽ�ɫ,��PPI�·�����Ϣ����,AR-IP-PTP.002*/
typedef struct tagTCPIP_PTP_PASSIVE_PPI
{
    ULONG   ulIfIndex;                      /*�ӿ�����*/
    TCPIP_PTP_PORT_ADDR_S stLocalAddr;      /*����ַ*/
    USHORT  usLocalPortNo;                  /*PTP�˿ں�*/
    UCHAR   Reserved[122];
} TCPIP_PTP_PASSIVE_PPI_S;

/* ���Կ��� */
typedef enum tagTCPIP_PTP_DEBUG_FLAG_E
{
    TCPIP_PTP_DEBUG_FOREMASTER  = 0x01,   /* PTP ForeMaster���� */
    TCPIP_PTP_DEBUG_INPUT  = 0X02,        /* ���յ�PTP���ĵ��� */
    TCPIP_PTP_DEBUG_OUTPUT = 0X04,        /* ���͵�PTP���ĵ��� */
    TCPIP_PTP_DEBUG_TIMER  = 0X08,        /* PTP��ʱ���ĵ��� */
    TCPIP_PTP_DEBUG_WARN   = 0X10,        /* PTP�澯�ĵ��� */
    TCPIP_PTP_DEBUG_PPI    = 0x20         /* PPI��Ϣ�ĵ��� */
}TCPIP_PTP_DEBUG_FLAG_E;

/*Ptsf���ͣ�Ŀǰ��֧��TCPIP_PTP_PTSF_SYNC*/
typedef enum tagTCPIP_PTP_PTSF_TYPE_E
{
    TCPIP_PTP_PTSF_SYNC,
    TCPIP_PTP_PTSF_UNUSED
}TCPIP_PTP_PTSF_TYPE_E;

typedef struct TCPIP_PTP_FOREIGN_MASTER
{
    TCPIP_PTP_PORT_ID_S szForeignMasterPortId;  /*ForeginMaster Id*/
    UCHAR               ucPad[2];
    ULONG               ulRcvIfIndex;           /*Master���ڵĽӿ�����*/
    ULONG               ulPtsfValue;            /*Ptsfֵ*/
    ULONG               ulAnnRcvTimeoutNum;     /*����ann ���ĳ�ʱ����*/
    UCHAR               ucReserve[120];         /*Ԥ���ֶ�*/
}TCPIP_PTP_FOREIGN_MASTER_S;

/*ȫ������*/
/*******************************************************************************
*    Func Name: TCPIP_PTP_Init
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2��ʼ��
*  Description: PTPV2��ʼ����������ʱ�������ġ�������Ϣ���У�����PTP���񣬷���˿���Դ
*        Input: ulPtpClockType: PTPʱ�����ͣ�OC����BC
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Init(ULONG ulPtpClockType);

/*******************************************************************************
*    Func Name: TCPIP_PTP_UnInit
* Date Created: 2014-03-03
*       Author: luogaowei
*      Purpose: PTPV2ȥ��ʼ��
*  Description: PTPV2ȥ��ʼ����д�¼���PTP�����񣬲��ȴ�������ж�����
*        Input: 
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-03   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_UnInit();

/*******************************************************************************
*    Func Name: TCPIP_PTP_AddPort
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: �������õ�PTP�˿�
*  Description: �������õ�PTP�˿�
*        Input: ULONG ulIfIndex: �ӿ�����
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: ��ӵ�PTP��ַ��Ŀǰ��ʹ�ã����ڽ�����չ
*       Output: USHORT* pusPtpPortNo:���ص�PTP�˿ں�
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.Ŀǰ��֧��Overmac�����ڽӿ����ò���Ҫָ��physical��ַ
*               2.OC�£����صĶ˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_AddPort(ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr,
                        USHORT* pusPtpPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_DelPort
* Date Created: 2014-03-21
*       Author: luogaowei & dutianyi
*      Purpose: ɾ��ָ����PTP�˿�
*  Description: ɾ��ָ����PTP�˿�
*        Input: USHORT usPtpPortNo:PTP�˿ں�
*               ULONG ulIfIndex:�ӿ�����
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr:PTP��ַ
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1. BCֻ��Ҫָ���Ķ˿ںż��ɣ�����������������ֵ����
*               2. OC���ڹ�����Ƕ˿ں�1����Ҫָ���ӿ�����(����Ҳ������Ҫָ����ַ)
*               3. pstPtpAddr��Ϊδ����չԤ������OC�£�ͬһ���ӿڲ�ͬ�ĵ�ַ��������PTPӦ��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-21   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_DelPort(USHORT usPtpPortNo, ULONG ulIfIndex, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr);

/*******************************************************************************
*    Func Name: TCPIP_PTP_Start
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����PTP�Ĺ���
*  Description: ����PTP�Ĺ��ܣ�����ָ���˿ڵķ��Ͷ�ʱ��
*        Input: USHORT usPtpPortNo: ������PTP�˿ں�
*               TCPIP_PTP_PORT_ADDR_S* pstPtpAddr: ��ַ��ϢĿǰ��ʹ�ã�������չ
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.����pstPtpAddr��ʱ��ʹ�ã����ڽ�����չ֧�ֲ�3��������
*               2.OC�½���һ���˿ڣ�������ö˿����е�����ڶ��ᷢ�ͱ���
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_Start(USHORT usPtpPortNo, TCPIP_PTP_PORT_ADDR_S* pstPtpAddr);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockIdentity
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����PTPʱ��ID
*  Description: ����PTPʱ��ID
*        Input: TCPIP_PTP_CLOCK_ID_SZ szClockID:PTPʱ��ID
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockIdentity(TCPIP_PTP_CLOCK_ID_SZ szClockID);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetClockQuality
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����ʱ��Դ����
*  Description: ����ʱ��Դ����
*        Input: TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality:ʱ��Դ����
*                 pstPtpCfgClockQuality->ucClockClass:ʱ�����Ĭ��0
*                 pstPtpCfgClockQuality->ucClockAccuracy: ʱ�Ӿ��ȣ�Ĭ��0����Χ0x20-0x32
*                 pstPtpCfgClockQuality->usOffsetScaledLogVariance:ʱ���ȶ��ȣ�Ĭ��0
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ʱ�ӵȼ�/ʱ���ȶ��ȵ���Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetClockQuality(TCPIP_PTP_CLOCK_QA_S *pstPtpCfgClockQuality);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetUtcProperties
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi
*      Purpose: OC matser������UTC
*  Description: OC matser������UTC
*        Input: SHORT sCurrentUtcOffset:UTCƫ����
*               BOOL_T bLeap61:Leap61
*               BOOL_T bLeap59:Leap59
*               BOOL_T bCurrentUtcOffsetValid:UTCƫ������Ч��
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 1.Leap61��Leap59����ͬʱΪ��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetUtcProperties(SHORT sCurrentUtcOffset, BOOL_T bLeap61, BOOL_T bLeap59, 
                                    BOOL_T bCurrentUtcOffsetValid);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetPriClassGroup
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ����PTP��ѡԴ
*  Description: ����PTP��ѡԴ��ѡ������ѡԴһ�µ�Դ����PPI�·�ʱ��Я����ѡԴ���
*        Input: UCHAR ucClass0
*               UCHAR ucClass1
*               UCHAR ucClass2
*               UCHAR ucClass3
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetPriClassGroup(UCHAR ucClass0, UCHAR ucClass1, UCHAR ucClass2, UCHAR ucClass3);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDomain
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ����ʱ���豸�������
*  Description: ����ʱ���豸���������PTPͨ�Ž���ͬһ�����ʱ�Ӽ����
*        Input: UCHAR ucDomainNumber:ʱ���豸��
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: ������Ч���ɲ�Ʒ��֤
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDomain(UCHAR ucDomainNumber);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnInterval
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi
*      Purpose: ���ö˿ڵ�Ann������Ϣ���(ָ����ʽ)
*  Description: ���ö˿ڵ�Ann������Ϣ���(ָ����ʽ)
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*               CHAR cLogAnnInterval:ʱ�Ӷ˿�LogAnnounceIntervalֵ, Ĭ��1����Χ0--4
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1��ʱ�����ɲ�Ʒ��֤��Ч��
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnInterval(USHORT usPtpPortNo, CHAR cLogAnnInterval);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetAnnRcvTimeoutNum
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ����announce���Ľ��ճ�ʱ������
*  Description: ����announce���Ľ��ճ�ʱ�������������ô������ɾ���˿��϶�Ӧ��ForeignMaster
*        Input: USHORT usPtpPortNo:PTP�˿ں�
*               UCHAR ucReceiptTimeout:���ճ�ʱ�����������ճ�ʱ������Ĭ��ֵΪ3����Χ2-10
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetAnnRcvTimeoutNum(USHORT usPtpPortNo, UCHAR ucAnnRcvTimeoutNum);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetSysInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ��ȡPTP��ǰ��ȫ����Ϣ
*  Description: ��ȡPTP��ǰ��ȫ����Ϣ(�û�������Ϣ��ѡ�е�����ʱ��Դ��Ϣ)
*        Input: 
*       Output: TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo:PTPȫ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetSysInfo(TCPIP_PTP_SYSTEM_INFO_S *pstSysInfo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPortInfo
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi
*      Purpose: ��ȡPTP�˿ڼ���Ϣ
*  Description: ��ȡPTP�˿ڼ���Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: TCPIP_PTP_PORT_INFO_S *pstPortPara:PTP�˿ڼ���Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPortInfo(USHORT usPtpPortNo, TCPIP_PTP_PORT_INFO_S *pstPortPara);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ��ȫ����Ϣ
*  Description: ��ӡPTP��ǰ��ȫ����Ϣ
*        Input: 
*       Output: PTP��ǰ��ȫ����Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysInfo();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP�˿ڼ���Ϣ
*  Description: ��ӡPTP�˿ڼ���Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: PTP�Ķ˿ڼ���Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortInfo(USHORT usPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowSysPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTPϵͳ������ͳ����Ϣ
*  Description: ��ӡPTPϵͳ������ͳ����Ϣ
*        Input: 
*       Output: PTP��ϵͳ������ͳ����Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowSysPktStatics();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowPortPktStatics
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP�˿ڼ�����ͳ����Ϣ
*  Description: ��ӡPTP�˿ڼ�����ͳ����Ϣ
*        Input: 
*       Output: PTP�Ķ˿ڼ�����ͳ����Ϣ
*       Return: 
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowPortPktStatics(USHORT usPortNo);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncWarningHook
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ע��澯����
*  Description: ע��澯����
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:�澯������
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncWarningHook(TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncPpiHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: ע��PPI�·�������
*  Description: ע��PPI�·�������
*        Input: TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook:PPI�·�������
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi    Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_RegFuncPpiHook(TCPIP_PTP_PPI_HOOK_FUNC pfPtpPpiHook);

/*******************************************************************************
*    Func Name: TCPIP_PTP_RegFuncCapturePacketHook
* Date Created: 2014-03-15
*       Author: luogaowei
*      Purpose: ע�ᱨ�Ĳ�����
*  Description: ע�ᱨ�Ĳ�����
*        Input: TCPIP_PTP_WARN_OUTPUT_FUNC pfWarnOutPut:���Ĳ�����
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei               Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_RegFuncCapturePacketHook(TCPIP_PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktPortStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ȡ�˿ڵı���ͳ����Ϣ
*  Description: ��ȡ�˿ڵı���ͳ����Ϣ
*        Input: USHORT usPtpPortNo:ʱ�Ӷ˿ں�
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:���ڶ˿ڵı���ͳ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: OC�¶˿ں�ֻ��Ϊ1
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktPortStat(USHORT usPortNo, TCPIP_PTP_PKT_STAT_S *pStatPackets);

/*******************************************************************************
*    Func Name: TCPIP_PTP_GetPktStat
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ȡȫ�ֵı���ͳ����Ϣ
*  Description: ��ȡȫ�ֵı���ͳ����Ϣ
*        Input: 
*       Output: TCPIP_PTP_PKT_STAT_S *pStatPackets:ȫ�ֵı���ͳ����Ϣ
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_GetPktStat(TCPIP_PTP_PKT_STAT_S *pStatPackets);

/*******************************************************************************
*    Func Name: TCPIP_PTP_SetDbgSwitch
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ����Debug����
*  Description: ����Debug����
*        Input: ULONG ulDbgFlag:
*                   TCPIP_PTP_DEBUG_FOREMASTER  = 0x01,   PTP ForeMaster����
*                   TCPIP_PTP_DEBUG_INPUT  = 0X02,        ���յ�PTP���ĵ���
*                   TCPIP_PTP_DEBUG_OUTPUT = 0X04,        ���͵�PTP���ĵ���
*                   TCPIP_PTP_DEBUG_TIMER  = 0X08,        PTP��ʱ���ĵ���
*                   TCPIP_PTP_DEBUG_WARN   = 0X10         PTP�澯�ĵ���
*       Output: 
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
ULONG TCPIP_PTP_SetDbgSwitch (ULONG ulDbgFlag);

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowTimerInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ���еĶ�ʱ����Ϣ
*  Description: ��ӡPTP��ǰ���еĶ�ʱ����Ϣ
*        Input: 
*       Output: PTP��ǰ���еĶ�ʱ����Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowTimerInfo();

/*******************************************************************************
*    Func Name: TCPIP_PTP_ShowForeMasterInfo
* Date Created: 2014-04-07
*       Author: dutianyi
*      Purpose: ��ӡPTP��ǰ���е�ForeMaster��Ϣ
*  Description: ��ӡPTP��ǰ���е�ForeMaster��Ϣ
*        Input: 
*       Output: PTP��ǰ��ǰ���е�ForeMaster��Ϣ
*       Return: 
*      Caution: 
*        Since: V300R002C10
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-07   dutianyi                Create the first version.
*******************************************************************************/
VOID TCPIP_PTP_ShowForeMasterInfo();


ULONG TCPIP_PTP_GetForeignMasterInfo(ULONG ulVrfIndex,
    TCPIP_PTP_PORT_ADDR_S   *pstInForeignMasterPortAddr,
    TCPIP_PTP_FOREIGN_MASTER_S *pstOutForeignMasterInfo);


ULONG TCPIP_PTP_SetPtsf(ULONG ulVrfIndex, TCPIP_PTP_PORT_ADDR_S* pstForeignMasterAddr, ULONG ulPtsfType,ULONG ulPTSFValue);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _TCPIP_PTPV2_API_h_   */
