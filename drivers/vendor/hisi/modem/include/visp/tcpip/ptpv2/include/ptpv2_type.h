/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_type.h
*
*  Project Code:
*   Module Name: PTPV2 type
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description: ��Ҫ�ṩ����Ʒ�Լ�CBB�Լ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_TYPE_h_
#define _PTPV2_TYPE_h_

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
/* PTP��Ϣͷ�� */
/*
   Bits                                  Octets  Offset
   7     6     5     4   3   2   1   0
   |transportSpecific|  messageType  |     1       0
   |    reserved     |  versionPTP   |     1       1
   |           messageLength         |     2       2
   |           domainNumber          |     1       4
   |           reserved              |     1       5
   |           flagField             |     2       6
   |           correctionField       |     8       8
   |           reserved              |     4       16
   |           sourcePortIdentity    |     10      20
   |           sequenceId            |     2       30
   |           controlField          |     1       32
   |           logMessageInterval    |     1       33

*/
typedef struct tagPTPV2_MSGHEADER_S
{
    #if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR            ucmessageType              : 4 ;   /* ��Ϣ���ͣ���ϸ�������Ϣ���Ͷ��� */
    UCHAR            uctransportSpecific        : 4 ;
    #else
    UCHAR            uctransportSpecific        : 4 ;
    UCHAR            ucmessageType              : 4 ;   /* ��Ϣ���ͣ���ϸ�������Ϣ���Ͷ��� */
    #endif

    #if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR            ucversionPTP               : 4 ;   /* PTP�汾�ţ�����ʵ��1588v2����˰汾��Ϊ2 */
    UCHAR            ucreserved4                : 4 ;   /* Ԥ�� */
    #else
    UCHAR            ucreserved4                : 4 ;   /* Ԥ�� */
    UCHAR            ucversionPTP               : 4 ;   /* PTP�汾�ţ�����ʵ��1588v2����˰汾��Ϊ2 */
    #endif

    USHORT           usmessageLength                ;   /* ��Ϣ���ȣ�������Ϣͷ */
    UCHAR            ucdomainNumber                 ;   /* ��� */
    UCHAR            ucreserved2                    ;   /* Ԥ�� */
    UCHAR            ucflagField[2]                 ;   /* ��־�� */
    UULONG           uulcorrectionField             ;   /* ������Announce/Signaling/Management��Ϣ���ֶ���0 */
    UCHAR            ucreserved[4]                  ;   /* Ԥ�� */
    TCPIP_PTP_PORT_ID_S stSourcePortIdentity           ;   /* ʱ��ID */
    USHORT           usSequenceId                   ;   /* ���к� */
    UCHAR            ucControlField                 ;   /* ������ */
    CHAR             cLogMessageInterval            ;   /* ��Ϣ���������Ϣ���;��� */
}PTPV2_MSGHEADER_S;

/* ʱ������� */ 
typedef struct tagPTPV2_TIMESTAMP_S
{
    USHORT  usSecondsHigh;
    ULONG   ulSecondsLow;
    ULONG   ulNanoseconds;
}PTPV2_TIMESTAMP_S;
 
/* Announce��Ϣ��ʽ */
/*
  Bits                                Octets      Offset
  |7   6   5   4   3   2   1   0
  |    header (see 13.3)       |          34      0
  |    originTimestamp         |          10      34
  |    currentUtcOffset        |          2       44
  |    reserved                |          1       46
  |    grandmasterPriority1    |          1       47
  |    grandmasterClockQuality |          4       48
  |    grandmasterPriority2    |          1       52
  |    grandmasterIdentity     |          8       53
  |    stepsRemoved            |          2       61
  |    timeSource              |          1       63
*/
typedef struct tagPTPV2_ANNOUNCE_MSG_S
{
    PTPV2_MSGHEADER_S       stMsgHeader                    ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S       stOriginTimestamp              ;   /* Դʱ��� */
    SHORT                   sCurrentUtcOffset              ;   /* ��ǰUTCƫ�� */
    UCHAR                   ucreserved                     ;   /* Ԥ�� */
    UCHAR                   ucGrandmasterPriority1         ;   /* ���ȼ�1 */
    TCPIP_PTP_CLOCK_QA_S    stGrandmasterClockQuality      ;   /* ʱ������ */
    UCHAR                   ucGrandmasterPriority2         ;   /* ���ȼ�2 */
    TCPIP_PTP_CLOCK_ID_SZ   stGrandmasterIdentity          ;   /* masterʱ��id */
    USHORT                  usStepsRemoved                 ;   /*  */
    UCHAR                   ucTimeSource                   ;   /* ʱ��Դ */ 
}PTPV2_ANNOUNCE_MSG_S;

/* Sync �� Delay_Req��Ϣ��ʽ */
/*
  Bits                             Octets  Offset
  7   6   5   4   3   2   1   0
  |    header (see 13.3)      |    34      0
  |    originTimestamp        |    10      34
*/
typedef struct tagPTPV2_SYNC_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
}PTPV2_SYNC_MSG_S;

typedef struct tagPTPV2_DELAY_REQ_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
}PTPV2_DELAY_REQ_MSG_S;

/* Delay_Resp��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    receiveTimestamp        |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_DELAY_RESP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stReceiveTimestamp             ;   /* ����ʱ��� */
    TCPIP_PTP_PORT_ID_S stRequestingPortIdentity       ;   /* ����˿� */
}PTPV2_DELAY_RESP_MSG_S;

/* Pdelay_Req��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    originTimestamp         |   10      34
    |    reserved                |   10      44
*/
typedef struct tagPTPV2_PDELAY_REQ_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
    UCHAR             ucReserved[10]                 ;   /* Ԥ�� */
}PTPV2_PDELAY_REQ_MSG_S;

/* Pdelay_Resp��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    requestReceiptTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_PDELAY_RESP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stRequestReceiptTimestamp      ;   /* �������ʱ��� */
    TCPIP_PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* ����˿� */
}PTPV2_PDELAY_RESP_MSG_S;

/* Pdelay_Resp_Follow_Up��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    responseOriginTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTPV2_PDELAY_RESP_FOLLOW_UP_MSG_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTPV2_TIMESTAMP_S   stResponseOriginTimestamp      ;   /* ��ӦԴʱ��� */
    TCPIP_PTP_PORT_ID_S stRequestingPortIdentity       ;   /* ����˿� */
}PTPV2_PDELAY_RESP_FOLLOW_UP_MSG_S;

/* Signaling��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    targetPortIdentity      |   10      34
    |    One or more TLVs        |   M       44
*/
typedef struct tagPTPV2_SIGNALING_HEARDER_S
{
    PTPV2_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    TCPIP_PTP_PORT_ID_S     stTargetPortIdentity           ;   /* Ŀ��ʱ�Ӷ˿� */
}PTPV2_SIGNALING_HEARDER_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

#pragma pack(1)
typedef struct  tagTCPIP_PTPv2_VLANTAG/* VLAN��ǩ�ṹ�嶨�� */
{
#if VRP_LITTLE_ENDIAN == VRP_YES
    USHORT  usVlanId   :12;                           /* VLanID */
    USHORT  usCfi      :1;                            /* 0��ʾphysical��ַ�Ǿ����ʽ��1��ʾphysical��ַ���Ǿ����ʽ��Ĭ����0 */
    USHORT  usPriority :3;                            /* �������ȼ� */
#else
    USHORT  usPriority :3;                            /* �������ȼ� */
    USHORT  usCfi      :1;                            /* 0��ʾphysical��ַ�Ǿ����ʽ��1��ʾphysical��ַ���Ǿ����ʽ��Ĭ����0 */
    USHORT  usVlanId   :12;                           /* VLanID */
#endif
}TCPIP_PTPV2_VLANTAG_S;

typedef  struct  tagTCPIP_PTPV2IEEE8023VlanHead
{
    UCHAR   ucDstMacAddr[6];     /* Э��ಥMAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[6];     /* ԴMAC                          */
    USHORT  usTPID;                                 /* 802.1q Protype 8100            */
    TCPIP_PTPV2_VLANTAG_S stVlanTag;                        /* Vlan��ǩ                       */
    USHORT  usPTPType;                              /* PTPЭ������0x88F7              */
}TCPIP_PTPV2_IEEE8023VLAN_HEAD_S;

/* ����VLAN��PTP Heard */
typedef struct tagTCPIP_PTPV2IEEE8023Head
{
    UCHAR   ucDstMacAddr[PTPV2_MACADDRLEN];     /* Э��ಥMAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTPV2_MACADDRLEN];     /* ԴMAC                            */
    USHORT   usPTPType;                             /* PTPЭ������0x88F7               */
}TCPIP_PTPV2_IEEE8023_HEAD_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagPTPV2_PORT_ANN_INFO
{
    USHORT usSndAnnSequenceId;
    CHAR   clogAnnounceInterval;        /*Announce���ͼ��*/
    UCHAR  ucAnnRcvTimeoutNum;
}PTPV2_PORT_ANN_INFO_S;

/*Local�˿���Ϣ*/
typedef struct tagPTPV2_PORT_SUB_INFO
{
    PTPV2_PORT_ANN_INFO_S  stPortAnnInfo;    
    ULONG  ulAnnSndTimerId;                 /*���Ͷ�ʱ��,ÿ���˿ڵķ������ڿ����ã���һ����ͬ*/
    UCHAR  ucWorkState;                     /*��������ֹͣ*/
    UCHAR  ucPtpPortRole;                   /*�˿ڽ�ɫ, PTPV2_MASTER ��PTPV2_SLAVE, PTPV2_PASSIVE*/
    USHORT usPortNo;                        /*port �˿ں�*/
    UCHAR  ucDelayMechanism;                /*E2E P2P  none*/
    UCHAR  ucCastMode;                      /*�������ಥģʽ��Ŀǰ��֧��L2�鲥*/
    UCHAR  ucPtpPortFsmState;               /*�˿�״̬, AR-IP-PTP.002*/
    UCHAR  ucPpiRoleFlag;                   /*�·��˿ڽ�ɫ*/
    UCHAR  ucPading[8];                    /*Ԥ�� */
}PTPV2_PORT_SUB_INFO_S;

typedef struct tagPTPV2_PORT_S
{
    ULONG ulIfIndex;                        /*�ӿ�����*/
    ULONG ulPtpPortAllocIndex;              /*PTP �˿ڷ�����������Ӧg_pstPortManageInfo->ulPortInfoHandle*/
    TCPIP_PTP_PORT_ADDR_S stPtpPortAddr;    /*��ַ*/
    DLL_S  dllForeignMasterHead;            /*����master ����*/
    TCPIP_PTP_PKT_STAT_S stPacketStat;      /* ����ͳ����Ϣ */
    AVL3_TREE_S stSlavetreeRoot;            /*slave ������ʱԤ��*/
    PTPV2_PORT_SUB_INFO_S *pstSubPortInfo;  /*OC �¹���ͬһ���ṹ��BC ÿ���˿�һ��*/
    ULONG (*pfPtpStartFunc)(VOID *pThis, VOID *pData); /*����PTP ����*/
    ULONG (*pfPtpStopFunc)(VOID *pThis, VOID *pData);  /*�ر�PTP ����*/ 
    ULONG (*pfPtpBuildAnnPktFunc)(VOID *pThis, VOID **ppData);
    ULONG (*pfPtpSndAnnPktFunc)(VOID *pThis, VOID *pData, VOID *pAddr);
    AVL3_NODE_S stPtpPortNode;             /* AVL Node */
} PTPV2_PORT_S;

/*  PTP ȫ����Ϣ�Ļ�ȡ����������*/
#define   PTPV2_CMD_BMC_POLICY          0x0000001
#define   PTPV2_CMD_MASTER_NUM_LIMIT    0x0000002
#define   PTPV2_CMD_CURRENT_MASTER_NUMS 0x0000004
#define   PTPV2_CMD_PORT_FSM_MODE       0x0000005

typedef struct tagPTPV2_FOREIGN_MASTER_S
{
    DLL_NODE_S      stPortDllNode;                      /* ���ڶ˿ڽ��Ĵ洢*/
    DLL_NODE_S      stGlobalDllNode;                    /* ����ȫ�ֽ��Ĵ洢*/
    PTPV2_PORT_S   *pstPortInfo;
    TCPIP_PTP_PORT_ID_S szForeignMasterPortId;
    UCHAR           ucGrandmasterPriority1;             /*ʱ�����ȼ�1*/
    UCHAR           ucGrandmasterPriority2;             /*ʱ�����ȼ�2*/
    UCHAR           ucFlagField[2];                     /* flagfield��,ѡԴ����֮�����ʱ���������ݼ���Ҫ */
    UCHAR           ucTimeSource;                       /* ʱ��Դ,����ʱ���������ݼ���ʱ����Ҫ */
    CHAR            cLogMAnnInterval;                   /* Ann�ķ��ͼ������Ann����ѧ�����ಥ��ʹ�ã�
                                                       ��������ͨ������Э�̻�ȡ�����ڵ���Master�б���*/
    SHORT           sCurrentUtcOffset;                  /* ��ǰUTCƫ�� */
    TCPIP_PTP_PORT_ADDR_S   stForeignMasterPortAddr;     /*PTP_PORT_ADDR_Sʱ��Դ��ַ*/
    ULONG           ulVrfIndex;

    /*�����Ǹ�ForeignMaster��GrandMaster�����ԣ�����ʱ�����������ȼ��ȣ���Щ����
      ���ʾ���grand�ģ�foreign��û�еģ���ѡԴʱҲӦ�òο���*/
    TCPIP_PTP_CLOCK_ID_SZ   szGrandMasterId;            /*���ֶζ���Ŀǰ��һ������������Fore��Clock ID*/
    TCPIP_PTP_CLOCK_QA_S    stGrandmasterClockQuality;  /*ʱ������������ʱ�Ӿ��ȡ�ʱ���ȶ���*/
    ULONG           ulRcvIfIndex;                       /*Master���ڵĽӿ����� ������Ͷ˿ڵ�������һ�£�����*/
    ULONG           ulAnnRcvTimerId;                    /*���ն�ʱ��*/
    ULONG           ulAnnRcvTimerCount;                 /*����ann ���Ķ�ʱ����ͳ��*/
    USHORT          usRcvAnnSequenceId;                 /*master announce ���к� ����˳��*/
    USHORT          usStepsRemoved;                     /*������*/

    ULONG            ulPtsfSync;                        /*Sync PTSF*/
    ULONG            ulPtsfUnused;                      /*��ǰδʹ��*/
    ULONG            ulRecvAnnCount;                    /*���յ���ann����ͳ��,����2�����ܲ���ѡԴ*/
}PTPV2_FOREIGN_MASTER_S;

typedef struct tagPTPV2_PORT_MANAGE
{
    ULONG ulCrtPortCount;   /*��ǰ��ptp������*/
    ULONG ulPortInfoHandle[PTPV2_MAX_PORTNO + 1];
}PTPV2_PORT_MANAGE_S;

typedef struct tagPTPv2_Global_INFO
{
    TCPIP_PTP_CLOCK_ID_SZ   szClockId;
    TCPIP_PTP_DEFAULT_DS_S  stCfgDefaultDs;     /*�û�����ֵ*/
    TCPIP_PTP_PARENT_DS_S   stParentDs;         /*���һ��ѡ�е�Դ����Ϣ*/

    ULONG       ulMaxMasterNum;             /*���master ������8��*/
    UCHAR       ucBMCPolicy;                /*ѡԴ���ԣ�Ŀǰ��֧��1588ѡԴ*/
    UCHAR       ucReserved[3];

    /*masterʹ��*/
    USHORT      usSndPortMaxNum;            /*OC master�Ķ˿ڷ��͸���*/
    BOOL_T      bPtpTimescale;
    BOOL_T      bTimeTraceable;
    BOOL_T      bFrequencyTraceable;
    USHORT      usStepsRemoved;             /*����Ϊ0*/
    USHORT      usWarningRecord;            /*�澯��¼*/
    UCHAR       ucTimeSource;

    UCHAR       ucPad[31];
}PTPV2_GLOBAL_INFO_S;


/*PTP�������Ϣ����*/
typedef enum tagPTPV2_TMSG_TYPE_E
{
    PTPV2_TMSG_ANN_REQ,                /*  0 ����ANNЭ��������Ϣ���� */
    PTPV2_TMSG_SYNC_REQ,               /*  1 ����SYNCЭ��������Ϣ���� */
    PTPV2_TMSG_ANN_CANCEL,             /*  2 ����ANNЭ��ȡ����Ϣ���� */
    PTPV2_TMSG_ANN_CANCELED,           /*  3 ANN����Э����ȡ�� */
    PTPV2_TMSG_DELAY_RESP_SYNC_CANCEL, /*  4 ����delay resp/pdelay resp ��syncЭ��ȡ��������Ϣ���� */
    PTPV2_TMSG_DELAY_RESP_REQ,         /*  5 �ಥ�յ�ann��ʱ������������� */
    PTPV2_TMSG_ACCEPT_MASTER_DEL,      /*  6 ɾ���ɽ���master���еĽڵ� */
    PTPV2_TMSG_FSM_INIT,               /*  7 ��ʼ��PTP״̬����Ϣ���� */
    PTPV2_TMSG_FSM_DISABLE,            /*  8 ȥʹ��PTP״̬����Ϣ���� */
    PTPV2_TMSG_FSM_ENABLE,             /*  9 ʹ��PTP״̬����Ϣ���� */
    PTPV2_TMSG_FSM_LOCKED,             /* 10 ��PTP״̬������LOCKED�¼���Ϣ���� */
    PTPV2_TMSG_FSM_STATE_DECISION,     /* 11 �ı��ֶ�ѡԴ�Զ�ѡԴ��ʱ����ܴ������¼� */
    PTPV2_TMSG_ACCEPT_MASTER_ENABLE,   /* 12 ʹ�ܿɽ���Master�б� */
    PTPV2_TMSG_ACCEPT_MASTER_DISABLE,  /* 13 ȥʹ�ܿɽ���Master�б� */
}PTPV2_TMSG_TYPE_E;

typedef enum tagPTPV2_CONTROLFIELD_E
{
    PTPV2_CONTROLFIELD_SYNC      = 0x00,
    PTPV2_CONTROLFIELD_DELAY_REQ,
    PTPV2_CONTROLFIELD_FOLLOW_UP,
    PTPV2_CONTROLFIELD_DELAY_RESP,
    PTPV2_CONTROLFIELD_MANAGEMENT,
    PTPV2_CONTROLFIELD_ALL_OTHER,
    PTPV2_CONTROLFIELD_RESERVED
}PTPV2_CONTROLFIELD_E;

/*�˿�״̬��״̬����, AR-IP-PTP.002*/
typedef enum tagTCPIP_PTP_FSM_STATE_E
{
    PTPV2_PORT_FSM_INITIALIZING=1,  /*1  INITIALIZING״̬       */
    PTPV2_PORT_FSM_FAULTY,          /*2  FAULTY״̬,δʵ��      */
    PTPV2_PORT_FSM_DISABLED,        /*3  DISABLED״̬,δʵ��    */
    PTPV2_PORT_FSM_LISTENING,       /*4  LISTENING״̬          */
    PTPV2_PORT_FSM_PRE_MASTER,      /*5  PRE_MASTER״̬,δʵ��  */
    PTPV2_PORT_FSM_MASTER,          /*6  MASTER״̬             */
    PTPV2_PORT_FSM_PASSIVE,         /*7  PASSIVE״̬            */
    PTPV2_PORT_FSM_UNCALIBRATED,    /*8  UNCALIBRATED״̬,δʵ��*/
    PTPV2_PORT_FSM_SLAVE,           /*9  SLAVE״̬              */
    PTPV2_PORT_FSM_END              /*   ö�ٽ���               */
}TCPIP_PTP_FSM_STATE_E;

#define PTPV2_PPI_SLAVE_FLAG     0x1   /*PPI�·� SLAVE��ɫ��־  */
#define PTPV2_PPI_PASSIVE_FLAG   0x2   /*PPI�·� PASSIVE��ɫ��־*/

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _PTPV2_TYPE_h_ */


