/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_type.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP PKTģ�麯��ͷ�ļ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-06-02      Lishenchuan       Create
*
*******************************************************************************/
#ifndef __ptp__type__h__
#define __ptp__type__h__

#ifdef __cplusplus
extern "C" {
#endif

/* controlField ö��ֵ */
typedef enum tagPTP_CONTROLFIELD_E
{
    PTP_CONTROLFIELD_SYNC      = 0x00,
    PTP_CONTROLFIELD_DELAY_REQ,
    PTP_CONTROLFIELD_FOLLOW_UP,
    PTP_CONTROLFIELD_DELAY_RESP,
    PTP_CONTROLFIELD_MANAGEMENT,
    PTP_CONTROLFIELD_ALL_OTHER,
    PTP_CONTROLFIELD_RESERVED
}PTP_CONTROLFIELD_E;

/* ������־�ȼ�ö�ٶ��� */
typedef enum tagPTP_FAULT_LOG_E
{
    PTP_FAULT_EMERGENCY = 0X00,     /* ������������־ */
    PTP_FAULT_ALERT,                /* alert��������־ */
    PTP_FAULT_CRITICAL,             /* critical��������־ */
    PTP_FAULT_ERROR,                /* error��������־ */
    PTP_FAULT_WARNING,              /* warning��������־ */
    PTP_FAULT_NOTICE,               /* notice��������־ */
    PTP_FAULT_INFORMATION,          /* information��������־ */
    PTP_FAULT_DEBUG                 /* debug��������־ */
}PTP_FAULT_LOG_E;

/*״̬��״̬����*/
typedef enum tagPTP_FSM_STATE_E
{
    PTP_FSM_STATE_INITIALIZING=1,  /*1  INITIALIZING״̬*/
    PTP_FSM_STATE_FAULTY,          /*2  FAULTY״̬*/
    PTP_FSM_STATE_DISABLED,        /*3  DISABLED״̬*/
    PTP_FSM_STATE_LISTENING,       /*4  LISTENING״̬*/
    PTP_FSM_STATE_PRE_MASTER,      /*5  PRE_MASTER״̬*/
    PTP_FSM_STATE_MASTER,          /*6  MASTER״̬*/
    PTP_FSM_STATE_PASSIVE,         /*7  PASSIVE״̬*/
    PTP_FSM_STATE_UNCALIBRATED,    /*8  UNCALIBRATED״̬*/
    PTP_FSM_STATE_SLAVE,           /*9  SLAVE״̬*/
    PTP_FSM_STATE_END              /*   ö�ٽ���*/
}PTP_FSM_STATE_E;

/*״̬���¼�����*/
typedef enum tagPTP_FSM_EVENT_E
{
    PTP_FSM_EVENT_POWERUP = 1,                              /*1,POWERUP�¼�*/
    PTP_FSM_EVENT_INITIALIZE,                               /*2,INITIALIZE�¼�*/
    PTP_FSM_EVENT_DESIGNATED_ENABLED,                       /*3,DESIGNATED_ENABLED�¼�*/
    PTP_FSM_EVENT_DESIGNATED_DISABLED,                      /*4,DESIGNATED_DISABLED�¼�*/
    PTP_FSM_EVENT_FAULT_CLEARED,                            /*5,FAULT_CLEARED�¼�*/
    PTP_FSM_EVENT_FAULT_DETECTED,                           /*6,FAULT_DETECTED�¼�*/
    PTP_FSM_EVENT_STATE_DECISION,                           /*7,STATE_DECISION�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_PASSIVE,                 /*8,Recommended State == BMC_PASSIVE�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE,                   /*9,Recommended State == BMC_SLAVE�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_MASTER,                  /*10,Recommended State == BMC_MASTER�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_MASTER_STATE_NOT_MASTER, /*11,Recommended State==BMC_MASTER AND state!=MASTER�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE_NEW_NOT_OLD,       /*12,Recommended State==BMC_SLAVE && new_master != old_master�¼�*/
    PTP_FSM_EVENT_RECOMD_STATE_BMC_SLAVE_NEW_IS_OLD,        /*13,Recommended State==BMC_SLAVE && new_master == old_master�¼�*/
    PTP_FSM_EVENT_QUALIFICATION_TIMEOUT_EXPIRES,            /*14,QUALIFICATION_TIMEOUT_EXPIRES�¼�*/
    PTP_FSM_EVENT_ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES,         /*15,ANNOUNCE_RECEIPT_TIMEOUT_EXPIRES�¼�*/
    PTP_FSM_EVENT_SYNCHRONIZATION_FAULT,                    /*16,SYNCHRONIZATION_FAULT�¼�*/
    PTP_FSM_EVENT_MASTER_CLOCK_SELECTED,                    /*17,MASTER_CLOCK_SELECTED�¼�*/
    PTP_FSM_EVENT_LOCKED,                                   /*18 ���߶��Ƶ�Master-only״̬��LOCKED�¼�*/
    PTP_FSM_EVENT_END                                       /*   ö�ٽ���*/
}PTP_FSM_EVENT_E;

/*״̬��ѡԴ���Ƽ�״̬�궨��,��ѡԴ�㷨����ʹ��*/
typedef enum tagPTP_RECOMD_STATE_E
{
    PTP_RECOMD_STATE_BMC_SLAVE = 1,
    PTP_RECOMD_STATE_BMC_MASTER,
    PTP_RECOMD_STATE_BMC_PASSIVE
}PTP_RECOMD_STATE_E;

/* TLV���� */
typedef enum tagPTP_TLV_TYPE_E
{
    PTP_TLV_NULL         =    0,   /* ��ʱ���� */

    /* Standard TLVs */
    PTP_MANAGEMENT,
    PTP_MANAGEMENT_ERROR_STATUS,
    PTP_ORGANIZATION_EXTENSION,

    /* Optional unicast message negotiation TLVs */
    PTP_REQUEST_UNICAST_TRANSMISSION,
    PTP_GRANT_UNICAST_TRANSMISSION,
    PTP_CANCEL_UNICAST_TRANSMISSION,
    PTP_ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION,

    /* Optional path trace mechanism TLV */
    PTP_PATH_TRACE,

    /* Optional alternate timescale TLV */
    PTP_ALTERNATE_TIME_OFFSET_INDICATOR,

    /* 000A - 1FFF,Reserved for standard TLVs */

    /* Security TLVs ,Annex K */
    PTP_AUTHENTICATION      =    0x2000,
    PTP_AUTHENTICATION_CHALLENGE,
    PTP_SECURITY_ASSOCIATION_UPDATE,

    /* Cumulative frequency scale_factor offset */
    PTP_CUM_FREQ_SCALE_FACTOR_OFFSET,

    /*
      2004 - 3FFF,Reserved for Experimental TLVs
      4000 - FFFF,Reserved
    */
    PTP_TLV_MAX

}PTP_TLV_TYPE_E;

/* ��־ID�����0xc000��ʼ*/
/* ������չTLV ö��ֵ organizationSubType,����<1588v2ϵͳslave-master��Ԫ�ӿ�˵����.doc>���� */
typedef enum tagPTP_ORG_SUB_TYPE_E
{
    PTP_ORG_SUB_TYPE_NULL,
    PTP_ORG_SUB_TYPE_REQ,
    PTP_ORG_SUB_TYPE_GRANT,
    PTP_ORG_SUB_TYPE_MAX
}PTP_ORG_SUB_TYPE_E;

/* ��Ԫ����,����<1588v2ϵͳslave-master��Ԫ�ӿ�˵����.doc>���� */
typedef enum tagPTP_ORG_ELEMENT_TYPE_E
{
    PTP_ORG_ELEMENT_CLKSERVER,
    PTP_ORG_ELEMENT_AP,
    PTP_ORG_ELEMENT_NodeB,
    PTP_ORG_ELEMENT_TYPE_MAX
}PTP_ORG_ELEMENT_TYPE_E;

/* ʱ������� */
#pragma pack(1)
typedef struct tagPTP_TIMESTAMP_S
{
    USHORT  usSecondsHigh;
    ULONG   ulSecondsLow;
    ULONG   ulNanoseconds;
}PTP_TIMESTAMP_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagPTP_TLV_S
{
    USHORT  usTlvType;
    SHORT   sLengthField;
}PTP_TLV_S;

typedef struct tagPTP_PTP_TXT_S
{
    UCHAR   ucLengthField;
    CHAR    szReserved[3];
    CHAR    szTextField[PTP_TXT_SUPPORT_LEN];
}PTP_PTP_TXT_S;

typedef struct tagPTP_FAULTRECORD_S
{
    USHORT          usFaultRecordLength;
    UCHAR           ucSeverityCode;
    CHAR            szReserved[3];
    PTP_TIMESTAMP_S stFaultTime;
    PTP_PTP_TXT_S   stFaultName;
    PTP_PTP_TXT_S   stFaultValue;
    PTP_PTP_TXT_S   stFaultDescription;
}PTP_FAULTRECORD_S;

typedef struct tagPTP_FOREIGN_MASTER_S
{
    BOOL_T          bValid;                     /*��ʾ�����Ƿ�Ϊ��Ч��*/
    PTP_PORT_ID_S   stForeignMasterPortId;
    USHORT          usForeignMasterAnnMsgs;     /*ָ��ʱ�����ڴ�foreign
                                                master���յ���annouce��Ϣ������*/
    UCHAR           ucGrandmasterPriority1;     /*ʱ�����ȼ�1*/
    UCHAR           ucGrandmasterPriority2;     /*ʱ�����ȼ�2*/
    UCHAR           ucFlagField[2];             /* flagfield��,ѡԴ����֮�����ʱ���������ݼ���Ҫ */
    UCHAR           ucTimeSource;               /* ʱ��Դ,����ʱ���������ݼ���ʱ����Ҫ */
    CHAR            cLogMAnnInterval;            /* Ann�ķ��ͼ������Ann����ѧ�����ಥ��ʹ�ã�
                                                   ��������ͨ������Э�̻�ȡ�����ڵ���Master�б���*/
    SHORT sCurrentUtcOffset; /* ��ǰUTCƫ�� */
    /*Add End*/
    /*Add by dutianyi 2014-7-24 ֧��G8275.1��׼ѡԴ*/
    USHORT usStepsRemoved;   
    /*End of adding by dutianyi*/

    /*���ֶ�������ʵ��ʱ��ӣ���Ϊ����ʵ�ֶ��ǲ���PORT ADDR���б�ʶ*/
    PTP_PORT_ADDR_S  stForeignMasterPortAddr;   /*PTP_PORT_ADDR_Sʱ��Դ��ַ*/

    ULONG           ulVrfIndex; 
    
    /*�����Ǹ�ForeignMaster��GrandMaster�����ԣ�����ʱ�����������ȼ��ȣ���Щ����
      ���ʾ���grand�ģ�foreign��û�еģ���ѡԴʱҲӦ�òο���*/

    PTP_CLOCK_ID_SZ szGrandMasterId;            /*���ֶζ���Ŀǰ��һ������������Fore��Clock ID*/
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;  /*ʱ������������ʱ�Ӿ��ȡ�ʱ���ȶ���*/
    ULONG           ulIfIndex;                    /*Master���ڵĽӿ�����*//*qinyun&luogaowei 0��ַ���� 2011-12-12*/
    /*����ϵ�ppi����*/
    PTP_PPI_S stPtpPpi;

    ULONG ulMulRcvAnnPackets;                      /* OverMac,�ಥͳ�� */
    ULONG ulMulAnnSequenceError;                   /* OverMac,�ಥͳ�� */

    ULONG  ulPtsfLossSync;      /* �鲥��·Sync PTSF */
    
}PTP_FOREIGN_MASTER_S;

typedef struct tagPTP_FOREIGN_MASTER_TAB_S
{
    USHORT                usActualTabSize; /*����ʵ����ЧԪ�ش�С*/
    USHORT                usReserved;
    ULONG                 ulSelectMasterMode; /*ѡԴģʽ*/

    PTP_PORT_ADDR_S       stManualMasterAddr; /*�ֶ�ѡԴģʽ�µ�Master��PORT ADDR*/
    ULONG                 ulManualVrfIndex;   /* �ֶ�ѡԴVRF index */

    PTP_FOREIGN_MASTER_S *pstBmcParent;   /*��ǰBMCѡ����Parent����Fore Master���е�Ԫ��*/
    PTP_FOREIGN_MASTER_S  stForeignMaster[PTP_UNICAST_MASTR_LEN];
}PTP_FOREIGN_MASTER_TAB_S;


/*����SLAVE�����б����߹��֧��10000����˫ʮ�����������ѯ���̳�*/
typedef struct tagPTP_UNI_SLAVE_NODE_S
{
    struct tagPTP_UNI_SLAVE_NODE_S *pstPrev;
    struct tagPTP_UNI_SLAVE_NODE_S *pstNext;


    /* Э��״̬��� */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;       /* pdelay �� delay ���� */
    UCHAR           ucReserved;

    /*��Ϣ��sequence id*/
    USHORT            usSndAnnSequenceId;    /* Announce��Ϣ��sequence id */
    USHORT            usSndSigSequenceId;    /* signaling��Ϣ��sequence id */
    USHORT            usRcvSigSequenceId;    /* ���յ���signaling��Ϣsequence id */
    USHORT            usReserved1;

    ULONG ulReserved1[3];/*ɾ����ԭ����3���ֶΣ����ڱ���*/

    CHAR cLogAnnInterval;/*Ann���ķ��ͼ��*/
    CHAR cLogSyncInterval;/*Sync���ķ��ͼ��*/
    CHAR cDelayReqInterval;/*DelayReq���ķ��ͼ��*/
    UCHAR ucReserved2;

    ULONG ulAnnDurationField;/*Ann���ķ���ʱ��*/
    ULONG ulSyncDurationField;/*SYNC���ķ���ʱ��*/
    ULONG ulDelayReqDurationField;/*Delay Req���ķ���ʱ��*/
    /*End*/

    /*��Ӧkeep alive ���Ľ��ն�ʱ��*/
    ULONG ulLiveRcvTimerId;
    ULONG ulLiveCounter;

    /* ��ӦQuality timer out ��ʱ��Id */
    ULONG ulQualityTimerId;
    ULONG ulDelayDurationTimerId; /*LGW_QY delay duration��ʱ��*/

    /* ��ӦAnnouce Request Cancel timer out ��ʱ��Id */
    ULONG ulAnnCancelQueryTimerId;
    ULONG ulAnnCancelCounter;

    /* ��ӦSync Request Cancel timer out ��ʱ��Id */
    ULONG ulSyncCancelQueryTimerId;
    ULONG ulSyncCancelCounter;

    /* ��ӦDelay Request Cancel timer out ��ʱ��Id */
    ULONG ulDelayCancelQueryTimerId;
    ULONG ulDelayCancelCounter;

    /* Э��״̬��� */
    PTP_PORT_ADDR_S stSlaveAddr;       /*Slave�ĵ�ַ*/
    PTP_PORT_ADDR_S stExtSlaveAddr;

    PTP_PORT_ID_S   stSlaveId;         /* slave Id */


    USHORT usExtUdpPort;
    /*End*/

    /* ͳ����Ϣ */
    PTP_PACKET_STAT_S stPacketStat;
    struct tagPTP_PORT_S          *pstPtpPort;
    struct tagPTP_UNI_SLAVE_TBL_S *pstPtpUniSlaveTbl;

    ULONG ulNextAnnLow;
    ULONG ulNextAnnHigh;
    ULONG ulDurationLow;
    ULONG ulDurationHigh;
    /* End of Added by wangchengyang62830, 2011/3/8*/

    /* slave����stPtpPort.ucDelayMechanism; master��Ӧʹ��PTP_UNI_SLAVE_NODE_S.ucDelayMechanism */
    UCHAR ucDelayMechanism;  /* slave�ڵ��DELAY_MECHANISM */
    UCHAR ucReserved3[3];    /* Ԥ�� */ 
}PTP_UNI_SLAVE_NODE_S;

typedef struct tagPTP_UNI_SLAVE_TBL_S
{
    struct tagPTP_UNI_SLAVE_TBL_S *pstNextUniSlaveTbl;     /* ��һ��UniSlaveTbl�ڵ�,NULL��ʾ����һ��UniSlaveTbl�ڵ� */
    PTP_PORT_ADDR_S stMasterIPAddr; /* master�˵�ַ */
    USHORT  usActualTabSize;
    USHORT  usReserved;
    PTP_UNI_SLAVE_NODE_S *pstUnitcastSlave;
}PTP_UNI_SLAVE_TBL_S;


/*TC �˿����ݼ�����*/
typedef struct tagPTP_TC_PORT_DS
{
    BOOL_T              bValid;
    BOOL_T              bFaultyFlag;
    CHAR                cLogMinPdelayReqInterval;
    CHAR                cReserved;
    PTP_PORT_ID_S       stPortId;
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;/*��ʼֵΪ0*/
    ULONG               ulPhyPortNo  ;           /* ������� */
}PTP_TC_PORT_DS_S;

/*TCʱ�����ݽṹ����*/
typedef struct tagPTP_TCLOCK_S
{
    /*Ĭ�����ݼ�*/
    PTP_CLOCK_ID_SZ szClockId;
    USHORT          usNumberPorts;
    UCHAR           ucDelayMechanism;
    UCHAR           ucPrimaryDomain;
    PTP_TC_PORT_DS_S stTcPortDS[PTP_SUPPORT_PORT_NUMBER];
}PTP_TCLOCK_S;


/*����ʱ�Ӷ˿ڵ�������Ϣ�����ݽṹ*/
/*
Array index (hex)Description
0 he node implements an ordinary clock
1 he node implements a boundary clock
2 he node implements a peer-to-peer transparent clock
3 he node implements an end-to-end transparent clock
4 he node implements a management node
5 - F  Reserved
*/
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/

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
typedef struct tagPTP_MSGHEADER_S
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
    PTP_PORT_ID_S    stSourcePortIdentity           ;   /* ʱ��ID */
    USHORT           usSequenceId                   ;   /* ���к� */
    UCHAR            ucControlField                 ;   /* ������ */
    CHAR             cLogMessageInterval            ;   /* ��Ϣ���������Ϣ���;��� */
}PTP_MSGHEADER_S;

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
typedef struct tagPTP_ANNOUNCE_MSG_S
{
    PTP_MSGHEADER_S   stMsgHeader                    ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
    SHORT             sCurrentUtcOffset              ;   /* ��ǰUTCƫ�� */
    UCHAR             ucreserved                     ;   /* Ԥ�� */
    UCHAR             ucGrandmasterPriority1         ;   /* ���ȼ�1 */
    PTP_CLOCK_QA_S    stGrandmasterClockQuality      ;   /* ʱ������ */
    UCHAR             ucGrandmasterPriority2         ;   /* ���ȼ�2 */
    PTP_CLOCK_ID_SZ   stGrandmasterIdentity          ;   /* masterʱ��id */
    USHORT            usStepsRemoved                 ;   /*  */
    UCHAR             ucTimeSource                   ;   /* ʱ��Դ */
}PTP_ANNOUNCE_MSG_S;

/* Sync �� Delay_Req��Ϣ��ʽ */
/*
  Bits                             Octets  Offset
  7   6   5   4   3   2   1   0
  |    header (see 13.3)      |    34      0
  |    originTimestamp        |    10      34
*/
typedef struct tagPTP_SYNC_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
}PTP_SYNC_MSG_S;

typedef struct tagPTP_DELAY_REQ_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
}PTP_DELAY_REQ_MSG_S;

/* Delay_Resp��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    receiveTimestamp        |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_DELAY_RESP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stReceiveTimestamp             ;   /* ����ʱ��� */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* ����˿� */
}PTP_DELAY_RESP_MSG_S;

/* Pdelay_Req��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    originTimestamp         |   10      34
    |    reserved                |   10      44
*/
typedef struct tagPTP_PDELAY_REQ_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stOriginTimestamp              ;   /* Դʱ��� */
    UCHAR             ucReserved[10]                 ;   /* Ԥ�� */
}PTP_PDELAY_REQ_MSG_S;


/* Pdelay_Resp��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    requestReceiptTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_PDELAY_RESP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stRequestReceiptTimestamp      ;   /* �������ʱ��� */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* ����˿� */
}PTP_PDELAY_RESP_MSG_S;


/* Pdelay_Resp_Follow_Up��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    responseOriginTimestamp |   10      34
    |    requestingPortIdentity  |   10      44
*/
typedef struct tagPTP_PDELAY_RESP_FOLLOW_UP_MSG_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_TIMESTAMP_S   stResponseOriginTimestamp      ;   /* ��ӦԴʱ��� */
    PTP_PORT_ID_S     stRequestingPortIdentity       ;   /* ����˿� */
}PTP_PDELAY_RESP_FOLLOW_UP_MSG_S;


/* Signaling��Ϣ��ʽ */
/*
    Bits                             Octets  Offset
    |7   6   5   4   3   2   1   0
    |    header (see 13.3)       |   34      0
    |    targetPortIdentity      |   10      34
    |    One or more TLVs        |   M       44
*/
typedef struct tagPTP_SIGNALING_HEARDER_S
{
    PTP_MSGHEADER_S   stPtpMsgHeader                 ;   /* ��Ϣͷ */
    PTP_PORT_ID_S     stTargetPortIdentity           ;   /* Ŀ��ʱ�Ӷ˿� */

}PTP_SIGNALING_HEARDER_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* REQUEST_UNICAST_TRANSMISSION TLV ��ʽ */
/*
  Bits                                 Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  | messageType   | Reserved       |     1        4
  |   logInterMessagePeriod        |     1        5
  |        durationField           |     4        6
*/

#pragma pack(1)
/* TLV Header */
typedef struct tagPTP_TLVHEADER_S
{
    USHORT        usType;                 /* ���� */
    USHORT        usLength;               /* ���� */
}PTP_TLVHEADER_S;

/*��������TLV�ṹ����*/
typedef struct tagPTP_REQUEST_UNICAST_TLV_S
{
    USHORT usTlvType;
    USHORT usLengthField;
#if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR  ucMessageType:4;
    UCHAR  ucReserved:4;
#else
    UCHAR  ucReserved:4;
    UCHAR  ucMessageType:4;
#endif
    CHAR   cLogInterMessagePeriod;
    ULONG  ulDurationField;
}PTP_REQUEST_UNICAST_TLV_S;

/* GRANT_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  | messageType   | Reserved       |     1        4
  |   logInterMessagePeriod        |     1        5
  |        durationField           |     4        6
  |          reserved              |     1        10
  |  0   0   0   0   0   0   0   R |     1        11
  
*/
/*����GRANT����Ϣ���ݽṹ*/
typedef struct tagPTP_GRANT_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif

    CHAR      cLogInterMsgPeriod;
    ULONG     ulDuration;
    CHAR      cReserved2;
     #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucReserved3 :  7;
    UCHAR     ucR         :  1;
    #else
    UCHAR     ucR         :  1;
    UCHAR     ucReserved3 :  7;
    #endif
}PTP_GRANT_TLV_S;

/* ACKNOWLEDGE_CANCEL_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  |    messageType |  reserved     |     1        4
  |          reserved              |     1        5
  
*/
/*����ACK_CANCEL����Ϣ���ݽṹ -- ����*/
typedef struct tagPTP_ACK_CANCEL_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif

    CHAR      cReserved2;
}PTP_ACK_CANCEL_TLV_S;

/* CANCEL_UNICAST_TRANSMISSION */
/*
  Bits                                Octets    TLV offset
  |  7   6   5   4   3   2   1   0 |
  |          tlvType               |     2        0
  |          lengthField           |     2        2
  |    messageType |  reserved     |     1        4
  |          reserved              |     1        5
  
*/
/*����CANCEL����Ϣ���ݽṹ -- ����*/
typedef struct tagPTP_CANCEL_TLV_S
{
    USHORT    usType ;
    USHORT    usLength;
    #if (VRP_BIG_ENDIAN == VRP_YES)
    UCHAR     ucMsgType   :  4;
    UCHAR     ucReserved1 :  4;
    #else
    UCHAR     ucReserved1 :  4;
    UCHAR     ucMsgType   :  4;
    #endif
    CHAR      cReserved2;
}PTP_CANCEL_TLV_S;

/* PTP������Ϣ */
/* �Զ���������Ϣ
                Bits                               Octets  Offset
    7      6      5     4    3     2     1     0
    | transportSpecific |    messageType(0xE)  |   1       0
    |      reserved     |     versionPTP       |   1       1
    |               Random(�����)             |   2       2
*/
typedef struct tagPTP_HANDSHAKE_REQ_S
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
    UCHAR            ucreserved                 : 4 ;   /* Ԥ�� */
    #else
    UCHAR            ucreserved                 : 4 ;   /* Ԥ�� */
    UCHAR            ucversionPTP               : 4 ;   /* PTP�汾�ţ�����ʵ��1588v2����˰汾��Ϊ2 */
    #endif
    USHORT           usRandom                       ;   /* ����� */
}PTP_HANDSHAKE_REQ_S;

/* PTP������Ӧ��Ϣ */
/*
                Bits                           Octets  Offset
    7     6     5     4    3    2    1    0
    |transportSpecific|   messageType(0xF)|    1       0
    |     Reserved    |      versionPTP   |    1       1
    |    Random(Handshake_Req�е������)  |    2       2
    |     SIP(�յ���Handshake_Req��ԴIP)  |    4       4
    |  SPort(�յ���Handshake_Req��Դ�˿�) |    2       8
    |              reserved               |    2       10
*/
typedef struct tagPTP_HANDSHAKE_RESP_S
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
    UCHAR            ucreserved                 : 4 ;   /* Ԥ�� */
    #else
    UCHAR            ucreserved                 : 4 ;   /* Ԥ�� */
    UCHAR            ucversionPTP               : 4 ;   /* PTP�汾�ţ�����ʵ��1588v2����˰汾��Ϊ2 */
    #endif

    USHORT           usRandom                       ;   /* ����� */
    ULONG            ulSrcIP                        ;   /* ԴIP */
    USHORT           usSrcPort                      ;   /* Դ�˿ں� */
    USHORT           usReserved                     ;   /* Ԥ�� */
}PTP_HANDSHAKE_RESP_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*  ��չtlv���Զ����tlv����������Ҫ��ͨ��
    ��Ҫ�����豸Ҳ֧�ָ���չtlv��
    Ŀǰ��˾��������Ը�tlv��ͨ
    Bits                            Octets  TLVOffset
    7   6   5   4   3   2   1   0
    |tlvType(0x0003)            |   2       0
    |lengthField                |   2       2
    |organizationId(��IEEE����) |   3       4
    |organizationSubType(����)  |   3       7
    |dataField(����)            |   N       10

    organizationSubTypeȡֵ
    ����           ֵ
    ��Ч           0
    ReqUnicast     1
    GrantUnicast   2
    Reserve        ����

    dataField(ReqUnicast)/GrantUnicast��dataField
    Bits                            Octets  TLVOffset
    7   6   5   4   3   2   1   0
    |    ElementType            |   1       0
    |    Reserved               |   1       1
    |    SPort(���˵Ķ˿�)      |   2       2
    |    SIP(���˵ĵ�ַ)        |   4       4

    ��Ԫ����
    ElementType   ֵ
    Clk Server    0
    AP            1
    NodeB         2
    Reserve       ����  ExtensionTlv
*/

#pragma pack(1)
typedef struct tagPTP_EXTENSIONTLV_ADDR_S
{

    USHORT    usType ;
    USHORT    usLength;
    UCHAR     szOrganizationId[3];          /* ��֯ID,ʹ�õ�ʱ��Ϊ����һ�ֽڵ����� */
    UCHAR     szOrganizationSubType[3];     /* ��֯������,ʹ�õ�ʱ��Ϊ����һ�ֽڵ����� */
    UCHAR     ucElementType;                /* ��Ԫ���� */
    UCHAR     ucReserved;                   /* Ԥ�� */
    USHORT    usSrcPort;                    /* Դ�˿� */
    ULONG     ulSrcAddr;                    /* Դ��ַ */
}PTP_EXTENSIONTLV_ADDR_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Add for BC3D03003*/
typedef struct tagPTPMIPINFO
{
  ULONG ulPortIP;                                  /* �ϴμ���ಥ���IP��Ϣ */
  ULONG ulPortIfIndex;                             /* �ϴμ���ಥ��Ľӿ���Ϣ */
  ULONG ulDownLoadFlag;                            /* �·���� */  
}PTP_MIPINFO_S;


typedef struct tagPTP_UNI_MASTER_NODE_S
{
    /* ������ */
    BOOL_T              bLink;   /*��·ͨ�ϱ��*/
    BOOL_T              bValid;  /*�ڵ��Ƿ���Ч */

    PTP_PORT_ADDR_S     stPortAddr;
    PTP_PORT_ADDR_S     stExtPortAddr;

    BOOL_T              bNegoEnable; /* ��������Э�̱�� */

    /* ���ñ� */
    BOOL_T              bCfgValid;

    /* ʵ�����б� */
    BOOL_T              bRunValid;
    
    /* Э��״̬��� */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;   /* pdelay �� delay ���� */

    /* ����ʱ����Ϣ���ͼ��, ��2ȡ���� */
    CHAR            cRunLogAnnInterval;
    CHAR            cRunLogSynInterval;
    CHAR            cRunLogDelayInterval;

    USHORT           usRcvAnnSequenceId;     /* ���յ���annouce sequence id */
    USHORT           usRcvSigSequenceId;     /* ���յ���signaling sequence id */
    USHORT           usSndSigSequenceId;      /* ���͵�signaling sequence id(slave���ᷢannounce,��˲��ö���announce���id) */

    USHORT           usReserved;

    ULONG           ulRunAnnDuration;
    ULONG           ulRunSynDuration;
    ULONG           ulRunDelayDuration; /* delay pdelay���� */

    /* timer identify ���� */
    ULONG           ulLiveSndTimerId;      /*Keep alive ���ķ��Ͷ�ʱ��*/
    ULONG           ulAnnRecvTimerId;
    ULONG           ulAnnReqQueryTimerId;
    ULONG           ulAnnDurationTimerId;
    ULONG           ulSyncReqQueryTimerId;
    ULONG           ulSyncDurationTimerId;
    ULONG           ulDelayReqQueryTimerId; /* delay pdelay���� */
    ULONG           ulDelayDurationTimerId;
    ULONG           ulAnnCancelQueryTimerId;
    ULONG           ulSyncCancelQueryTimerId;
    ULONG           ulDelayCancelQueryTimerId;/* delay pdelay���� */

    /* ����Э�������ȡ������Ϣ�ļ����� */
    ULONG            ulAnnReqCounter;
    ULONG            ulSyncReqCounter;
    ULONG            ulDelayReqCounter;
    ULONG            ulAnnCancelCounter;
    ULONG            ulSyncCancelCounter;
    ULONG            ulDelayCancelCounter;

    /*Annouce ���ն�ʱ���ļ�����*/
    ULONG            ulAnnRecvCounter;

    PTP_PACKET_STAT_S   stPacketStat; /*��·����ͳ����Ϣ */
    PTP_SLAVE_STAT_S stSlaveStat; /*Slave�˹���Master�ı���ͳ����Ϣ*/

    ULONG           ulAnnDurationOutFlag;  /* whether the duration is time out */
    /*Added by Anish K Kurian & Wangchengyang72338 & 62830, new profile, 2010/9/24 */
    /* PTSF(Packet Timing Signal Fail) of lossSync & lossResp
     * the annouce time-out mechanism can insure the lossAnnouce
     */
    ULONG            ulPtsfLossSync;
    ULONG            ulPtsfLossAnnouce;
    ULONG            ulPtsfLossUnusable;

    /* In new profile,there is a priority for local master,
     * in order to differ from the priority of 1588v2,
     * we use weight here */
    ULONG            ulWeight;          /* the lesser value has high priority,no range,default value is 0 */
    
    /* Master port Identity,set it all 1's when add the unicast master,and 
     * update the value after receiving the announce grant from the master*/
    PTP_PORT_ID_S   stMasterPortIdentity;
    UCHAR          ucSyncDurationOutFlag;     /*Sync�Ƿ�����Э��״̬(�յ���Ȩʱ����)*/
    UCHAR          ucHasNpAddFlag;/*�Ѿ��·�Add*/
    ULONG          ulVrfIndex;
    /* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/9/24 */

    /*Added by limin00188004/zhangliangzhi00187023/jijianhua00169178, PTP slave��֧��5·SYNCЭ��, 2011/12/29   ���ⵥ��:S.PTP.5SYNC.01 */
    ULONG ulUdpPort;  /* Master��UDP�˿ڣ������� */
    /* End of Added by limin00188004/zhangliangzhi00187023/jijianhua00169178, 2011/12/29   ���ⵥ��:S.PTP.5SYNC.01 */

    /*Added by guo00178934, ͳһ������·Down�澯, 2012/1/13   ���ⵥ��:20120112_1 */
    ULONG ulSyncWarning;    /*Sync Warning ����(Up, Down)*/
    ULONG ulDelayWarning;   /*Delay Warning ����(Up, Down)*/
    /* End of Added by guo00178934, 2012/1/13   ���ⵥ��:20120112_1 */

    /*Added by wuxiaowu00217009, 2012/8/9 Master�б���DSCPֵ��������Slave��ָ��Master����DSCP*/
    UCHAR ucPriority;
    UCHAR ucPad[3];
    /*End of Added by wuxiaowu00217009, 2012/8/9 */
}PTP_UNI_MASTER_NODE_S;

/*Э���ѡ����������*/
typedef struct tagPTP_UNI_MASTER_TBL_S
{
    USHORT  usPtpPortNumber;
    USHORT  usCfgTableSize;       /* ��ǰ���õĵ���master�б�Ĵ�С,���֧��2�� */
    USHORT  usRunTableSize;       /* ��ǰ����״̬�ﵥ��master�б�Ĵ�С,��ɾ������master�б��𵥲�ȡ��֮�󣬻�û�յ���Ӧ����±����ô�С�� */
    USHORT  usTotalTableSize;     /* ��ǰ�ڵ��С */
    PTP_UNI_MASTER_NODE_S stUniMasterNode[PTP_UNICAST_MASTR_LEN];
}PTP_UNI_MASTER_TBL_S;      /*�ýṹ����unicastMasterTable*/

/******************************************************************************/
/*  Slave �� ��VRF���Եĵ�ַ(��ֻ����vrf��IfIndex�Ĺ�ϵ)                      */
/******************************************************************************/
typedef struct tagPTP_PORT_ADDR_VRF_NODE_S
{
    struct tagPTP_PORT_ADDR_VRF_NODE_S *pstPrev;
    struct tagPTP_PORT_ADDR_VRF_NODE_S *pstNext;
    PTP_PORT_ADDR_S      stPtpPortAddr;
    ULONG ulVrfIndex;
    ULONG ulIfIndex;
}PTP_PORT_ADDR_VRF_NODE_S;

typedef struct tagPTP_PORT_ADDR_VRF_TBL_S
{
    ULONG ulCurNum;
    ULONG ulMaxNum;
    PTP_PORT_ADDR_VRF_NODE_S stPtpPortAddrVrfHead;
}PTP_PORT_ADDR_VRF_TBL_S;

typedef struct tagPTP_ALL_PORT_ADDR_VRF_NODE_S
{
    ULONG ulNum;
    struct tagPTP_PORT_ADDR_VRF_NODE_S szPortAddrVrf[PTP_MAX_VRF_NUM];
}PTP_ALL_PORT_ADDR_VRF_NODE_S;

typedef struct tagPTP_UNI_SLAVE_TBL_HASH
{
    PTP_UNI_SLAVE_TBL_S *pstUniSlaveTbl;   /* ָ��Hash��ͻ��ͷ�ڵ��ָ�� */
    ULONG        ulUniSlaveNum;            /* UniSlaveTbl��Hash��ͻ���ڵ���� */
}PTP_UNI_SLAVE_TBL_HASH_S;

/*����OC/BCʱ�Ӷ˿����ݽṹ*/
typedef struct tagPTP_PORT_S
{
    /*Э�鶨���ʱ�Ӷ˿����ݼ���*/
    BOOL_T    bValid;                     /*��ʱ�Ӷ˿��Ƿ���Ч�����û��Ƿ񴴽�*/
    /*��̬��Ա*/
    PTP_PORT_ID_S stPortId;

    /*��̬��Ա*/
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;
    UCHAR   ucPortState;
    CHAR    cLogAnnInterval;             /* ����Э����,����Է�����ann��Ϣ�ļ�� */
    CHAR    cLogSyncInterval;            /* ͬ�� */
    CHAR    cLogMinDelayReqInterval;     /*Delay �� Pdelay ����*/
    UCHAR   ucAnnReceiptTimeout;          /* ann��Ϣ���ճ�ʱ */
    UCHAR   ucDelayMechanism;
    CHAR    versionNumber;
    /* CHAR    cReserved; */
    CHAR    cLogAnnSndTime;              /* announce���ķ���ʱ��,Master���õ� */
    /*End of Modified by wangchengyang62830, 2011/3/18  */

    /*����Э�����Ի����߶�������*/
    ULONG   ulPhyPortNo;                /*��ʱ�Ӷ˿ڶ�Ӧ������ӿڱ��*/
    /* ������� address �洢λ��
        ipv4                ipv6                overmac
slave   stLocalPortAddr     stLocalPortAddr6    stLocalPortAddr
master  pstUniSlaveTbl      stUniSlaveTbl6      stLocalPortAddr
    */
    PTP_PORT_ADDR_S stLocalPortAddr[2]; /*���ض˿ڵĵ�ַ��0Ϊ��׼�ģ�1ΪAP IPSEC�ĳ��� */
    PTP_PORT_ADDR_S stLocalPortAddr6[2]; /*���ض˿ڵĵ�ַ��0Ϊ��׼��*/

    USHORT  usLocalUdpPort[2];          /* ���ض˿ڵ�udp�˿ںţ�0Ϊ��׼����ʱ���Բ���,��Ϊ�ǳ���˿ں�(320/319)
                                           1Ϊ��ȫ��������,���û����� */
                                            
    PTP_PORT_ADDR_VRF_TBL_S  stPtpPortAddrVrfTbl;
    /*Slave���*/
    /*foreign Master�б�*/
    PTP_FOREIGN_MASTER_TAB_S stForeignMasterTab;

    /*��Ϣ��sequence id,�ಥʱ���ã�����ʱ���õ���master/slave�б������,�ಥ����עsignaling�� sequence id */
    USHORT            usSndAnnSequenceId;    /* ���͵�signaling��Ϣ��sequence id�����master */

    /*�������*/
    BOOL_T bUnicastNego;                  /*����Э�̱�ǣ�����ʹ�ܣ���������Ϣ����*/

    /*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/

    /*Slave���*/
    ULONG ulAnnDuration;                /*Annouce��������ʱ������λ��*/
    ULONG ulSyncDuration;               /*Sync��������ʱ������λ��*/
    ULONG ulDelayRespDuration;          /*Delay_Resp��������ʱ������λ��*/

    ULONG ulAnnSndTimerId;              /*Ann���Ͷ�ʱ��Id*/

    /* �ಥAnn���ն�ʱ�� */
    ULONG ulAnnMRecvTimerId;            /* Ann�ಥ���ն�ʱ��Id */
    ULONG ulAnnMRecvCounter;            /* Ann�ಥ���ն�ʱ��������*/

    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01-201, 2009/5/8 */
    ULONG ulAcceptMasterDetecTimerId;   /* �ɽ���Master��ⶨʱ�� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/5/8 */
    BOOL_T    bAccepMasterTabEnable;      /*�ɽ���Master�б�ʹ�ܱ�־*/

    /* �ಥ��delay/pdelay resp ����Э����صı��� */
    CHAR  cMRunLogDelayInterval;        /* �ಥ���е�Delay/pdelay�������Э�̵õ� */
    UCHAR ucMDelayFlag;                 /* �ಥ��delay resp����Э�̵�FALG*/
    ULONG ulMDelayReqQueryTimerId;      /* �ಥdelay/pdelay resp ��ѯ��ʱ�� */
    ULONG ulMRunDelayDuration;          /* �ಥ���е�delay/pdelay duration����Э�̵õ� */
    /* STר�����:wangchengyang,2008-7-23,counter����ƴд���� */
    ULONG ulMDelayReqCounter;           /* �ಥ��Delay Req ������ */
    ULONG ulMDelayCancelQueryTimerId;   /* �ಥdelay/pdelay cancel ��ѯ��ʱ��*/
    ULONG ulMDelayCancelCounter;        /* �ಥ��Delay cancel ������ */

    /*Master���*/
    PTP_UNI_SLAVE_TBL_S stUniSlaveTbl6;
    /* Modified by dutianyi00217007, 2014/2/14, expanding PTP port address, using hash table to store UniSlaveTable */
    PTP_PORT_ADDR_S stMultiSlaveMasterIPAddr;          /* �ಥMaster ��ַ */
    PTP_UNI_SLAVE_TBL_HASH_S stUniSlaveTblHash[PTP_UNI_SLAVE_TBL_HASH_SIZE];
    /* Modified by dutianyi00217007, 2014/2/14 */

    PTP_PACKET_STAT_S stPacketStat;     /* ����ͳ����Ϣ */

    /*Added by zhangbo146309, PTP VLAN, 2010/4/19 */
    USHORT usVlanId;                    /*VLAN Id*/
    /* End of Added by zhangbo146309, 2010/4/19 */
    USHORT usIPv4AddrNum;
    /* ST����:ɾ�������ͻ��汨�Ľṹ����ʵ����Ҳ������ش������,wangchengyang 2008-7-18 */
    /* Add for BC3D03003*/
    PTP_MIPINFO_S stMIpInfo;            /* �·��Ķಥ��ַ��Ϣ */

    /*Added by guo00178934, Duration��ʱ��Э��ʱ���Duration�ٷֱ�, 2012/1/7   ���ⵥ��:20120107_1 */
    ULONG ulAnnDurationPercent;                /*Annouce������Э�̳�ʱ�ٷֱ�*/
    ULONG ulSyncDurationPercent;               /*Sync������Э�̳�ʱ�ٷֱ�*/
    ULONG ulDelayRespDurationPercent;         /*Delay_Resp��Э�̳�ʱ�ٷֱ�*/
    /* End of Added by guo00178934, 2012/1/7   ���ⵥ��:20120107_1 */
}PTP_PORT_S;


/******************************************************************************/
/*  VRF Node, ���ڹ���socket(�ⲿ����VRF, �ڲ������VRF��socket)              */
/******************************************************************************/
typedef struct tagPTP_VRF_NODE_S
{
    struct tagPTP_VRF_NODE_S *pstPrev;
    struct tagPTP_VRF_NODE_S *pstNext;
    ULONG ulVrfIndex;
    ULONG ulCreatTaskId; /* ������socket��Task id */
    LONG  lSocketFd;
}PTP_VRF_NODE_S;

typedef struct tagPTP_VRF_TBL_S
{
    ULONG ulCurNum;
    ULONG ulMaxNum;
    PTP_VRF_NODE_S stVrfNodeHead;
}PTP_VRF_TBL_S;

typedef struct tagPTP_ALL_VRF_NODE_S
{
    ULONG ulNum;
    struct tagPTP_VRF_NODE_S szVrfNode[PTP_MAX_VRF_NUM];
}PTP_ALL_VRF_NODE_S;

/*ʱ�ӵȼ��ṹ�壬ֻ������Master�࣬���ڴ洢�¡���ģʽ��ʱ�ӵȼ�*/
typedef struct tagPTP_CLOCK_CLASS_S
{
    UCHAR   uc1588Class;            /*��ģʽ��ʱ�ӵȼ�*/
    UCHAR   ucG8265Class;           /*��ģʽ��ʱ�ӵȼ�*/
    UCHAR   ucG8275Class;           /*G8275��׼��ʱ�ӵȼ�*/
    UCHAR   szReserved;             /*����ֶ�*/
}PTP_CLOCK_CLASS_S;



/*����OC/BCʱ���豸���ݽṹ*/
typedef struct tagPTP_CLOCK_S
{
    /*Ĭ�����ݼ�*/
    /*��̬��Ա*/
    BOOL_T            bTwoStep;   /* Ĭ��FALSE, û��Follow��Ϣ */
    USHORT            usReserved;
    PTP_CLOCK_ID_SZ szClockId ;
    USHORT          usNumberPorts;
    UCHAR ucAnnReceiptTimeout;          /* ann��Ϣ���ճ�ʱ */
    /*�����ó�Ա*/
    UCHAR       ucPriority1;            /* ��Χ0--255, Ĭ��0 */
    UCHAR       ucPriority2;            /* ��Χ0--255, Ĭ��0 */
    UCHAR       ucDomainNumber;         /* ��Χ0--255, Ĭ��0 */
    UCHAR       ucClockFsmMode;         /* ��Χ 0--2 */
    UCHAR       ucSyncMode;
    UCHAR       ucCastMode;   /*ϵͳ֧���������ģʽ(����/�ಥ/OVER MAC)*/

    /* ��������/ȡ����� */
    CHAR   cLogQueryInterval;   /*�����λ����Ϊ�����ֽڶ���, Э��δ�涨ȡֵ��Χ,Ĭ��ֵΪ2*/

    /*��ǰ���ݼ���ȫ���Ƕ�̬��Ա*/
    USHORT      usStepsRemoved;

    PTP_TIME_INTERVAL_S stOffsetFromMaster;
    PTP_TIME_INTERVAL_S stMeanPathDelay;

    /*��̬��Ա*/
    PTP_CLOCK_QA_S stClockQuality;

    /*Added by wuxiaowu217009, ��̬��Ա��ֻ������Master�֧࣬��ͬʱ�����¡���ģʽClockClass, 2012/9/18   
     *���ⵥ��:S.PTP.02.01 */
    PTP_CLOCK_CLASS_S stMasterCfgClockClass;
    ULONG       ulMasterCfgClockClassFlag;    /*�ж��Ƿ�ʹ��ͬʱ�����¡���ģʽClockClass��1:ʹ�ܡ�0:δʹ��*/
    /* End of Added by wuxiaowu217009, 2012/9/18   ���ⵥ��:S.PTP.02.01 */


    /*�������ݼ���ȫ���Ƕ�̬��Ա*/
    PTP_PORT_ID_S   stParentPortId;
    BOOL_T            bParentStats;
    UCHAR           ucGrandmasterPriority1;
    UCHAR           ucGrandmasterPriority2;
    USHORT          usObservedParentOffsetScaledLogVar;
    LONG            lObservedParentClockChangeRate;
    PTP_CLOCK_ID_SZ szGrandMasterId;
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;/*Э��ǰ��һ��*/

    PTP_PORT_ADDR_S stParentPortAddr; /*����PARENT�ĵ�ַ�����ڷ�������������Master�б�*/
    PTP_PORT_ADDR_S stParentPortExtAddr;/* parent����չ��ַ */
    ULONG           ulParentVrfIndex;

    /* VRF table, �����vrf socket */
    PTP_VRF_TBL_S   stPtpVrfTbl;

    /*ʱ���������ݼ���ȫ���Ƕ�̬��Ա*/
    SHORT   sCurrentUtcOffset;
    BOOL_T    bCurrentUtcOffsetValid;
    BOOL_T    bLeap59;
    BOOL_T    bLeap61;
    BOOL_T    bTimeTraceable;
    BOOL_T    bFrequencyTraceable;
    BOOL_T    bPtpTimescale;
    BOOL_T    bClassIdentify;/*�ṩClockClassʶ���ܵĿ���*/
    UCHAR      ucClass0;/*�ṩһ�����ѡ��Classֵ��Ĭ��Ϊ6>13>7>14*/
    UCHAR      ucClass1;
    UCHAR      ucClass2;
    UCHAR      ucClass3;
    UCHAR    ucTimeSource;
    CHAR     cReserved8[3];
        /*Mod End*/

    /*�����������Ի�Э�����Ի���������*/
    PTP_PORT_S                  stPtpPort[PTP_SUPPORT_PORT_NUMBER];  /*����ʱ���豸ʱ�Ӷ˿�*/
    PTP_ACCEPT_MASTER_TAB_S     stAcceptMasterTab;                   /*����ʱ�ӿɽ��ܵ�Master�б�*/
    PTP_UNI_MASTER_TBL_S        stUniMasterTbl;                  /*����Master�б�*/
    PTP_FAULTRECORD_S           stFaultRecord;                         /*�����¼*/

    /* added by wangchengyang for event pkt stat. 2008-06-16 */
    ULONG ulRcvErrEventPkt;                                          /* �յ��Ĵ���event������ */
    ULONG ulRcvCrrctEventPkt;                                        /* �յ�����ȷ��event������*/
    ULONG ulSndEventPkt;                                             /* ���͵�event������ */
    /* the end of wangchengyang's addition */

    ULONG ulSlaveNum;

    /*����Э�̵�����ѯ����*/
    ULONG ulUniNegoQueryMaxTimes;

    /* Added by wangchengyang for cfg alive pkt interval & receipt timeout.2008-11-27 */
    /* keep alive���ĳ�ʱ���� */
    ULONG ulLiveReceiptTimeout;
    /* the end of wangchengyang's addition */
    /*Added by Anish K Kurian & Wangchengyang72338 & 62830, for new profiel, 2010/10/9 */
    ULONG ulMaxMasterNumber;
    /* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/10/9 */
    
    ULONG ulCancelQueryMaxTimes;
    /* End of Added by wangchengyang62830, 2011/3/18   */

    ULONG ulTimerDelayCount;
    /* End of Added by wangchengyang62830, 2011/3/18   */
}PTP_CLOCK_S;

/*Added by xujun-wangchengyang57575-62830 for VISPV1R8C01, 2009/3/19 */
/* ��VLANͷ��PTP���� */
#pragma pack(1)
/* VLAN��ǩ�ṹ�嶨�� */
typedef struct  tagPTPVLANTAG
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
}PTP_VLANTAG_S;

typedef  struct  tagPTPIEEE8023VlanHead
{
    UCHAR   ucDstMacAddr[PTP_ADDRLEN_IEEE8023];     /* Э��ಥMAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTP_ADDRLEN_IEEE8023];     /* ԴMAC                          */
    USHORT  usTPID;                                 /* 802.1q Protype 8100            */
    PTP_VLANTAG_S stVlanTag;                        /* Vlan��ǩ                       */
    USHORT  usPTPType;                              /* PTPЭ������0x88F7              */
}PTP_IEEE8023VLAN_HEAD_S;

/* ����VLAN��PTP Heard */
typedef struct tagPTPIEEE8023Head
{
    UCHAR   ucDstMacAddr[PTP_ADDRLEN_IEEE8023];     /* Э��ಥMAC: 01-1B-19-00-00-00 */
    UCHAR   ucSrcMacAddr[PTP_ADDRLEN_IEEE8023];     /* ԴMAC                            */

    USHORT   usPTPType;                             /* PTPЭ������0x88F7               */
}PTP_IEEE8023_HEAD_S;



/*Added by zhangbo146309, PTP VLAN, 2010/4/21 */
typedef struct tagPTP_VLANCHAIN_S
{
    DLL_NODE_S stDllNode;                             /* ���ڽ��Ĵ洢*/
    ULONG  ulPhyPortNo;                               /* ����˿ں�*/
    USHORT usVlanId;                                  /* VLAN ID*/
    USHORT usVlanPri;                                 /* VLAN���ȼ� */
}PTP_VLANCHAIN_S;
/*End of Added by wangchengyang62830, 2010/12/7 */

/* End of Added by zhangbo146309, 2010/4/21 */

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif
/* End of Added by xujun-wangchengyang57575-62830, 2009/3/19 */

#ifdef __cplusplus
}
#endif

#endif
