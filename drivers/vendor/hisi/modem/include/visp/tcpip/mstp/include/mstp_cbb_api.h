/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mstp_cbb_api.h
*
*  Project Code: VISP
*   Module Name:   
*  Date Created: 2008-10-23
*        Author: wuhailan
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME           DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-10-23   wuhailan       Create
*
*******************************************************************************/
#ifndef _MSTP_CBB_API_H_
#define _MSTP_CBB_API_H_


#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef MID_COMP_BASE
#define MID_COMP_BASE               0x0E000000   /*VISP���ֶ����MIDֵ*/
#endif

#ifndef MID_COMP_MSTP
#define MID_COMP_MSTP               ( MID_COMP_BASE + 0x00390000 )
#endif


typedef enum tagMSTP_ERRCODE
{
    MSTP_OK = VOS_OK,                 /* 0 OK */
    MSTP_ERR,                         /* 1 ���� */
    MSTP_ERR_DISABLE = MID_COMP_MSTP + 1, /* 2 Э��δʹ�� */
    MSTP_ERR_PARAWRONG,               /* 3 ����������� */
    MSTP_ERR_NULL_POINTER,            /* 4 ָ��Ϊ�� */
    MSTP_ERR_MBUF_NULL,               /* 5 MBUFָ��Ϊ�� */
    MSTP_ERR_IFNET_NULL,              /* 6 IFNETָ��Ϊ�� */
    MSTP_ERR_ISNOT_L2PORT,            /* 7 ���Ƕ�����ͨ�˿� */
    MSTP_ERR_GET_PORTINDEX_FAIL,      /* 8 ��ȡport����ʧ�� */
    MSTP_ERR_PORTNUM_OVERFLOW,        /* 9 PORT����������Χ */
    
    MSTP_ERR_FUNCHOOK_NOTREG,         /* 10 ����ָ��δע�� */
    MSTP_ERR_TASK_IS_RUNNING,         /* 11 mstp�����Ѿ����� */
    MSTP_ERR_PRI_INVALID,             /* 12 �������ȼ����� */
    MSTP_ERR_CRT_TIMEQUE_FAIL,        /* 13 ������ʱ������ʧ�� */
    MSTP_ERR_CRT_EVTQUE_FAIL,         /* 14 �����¼�����ʧ�� */
    MSTP_ERR_CRT_PKTQUE_FAIL,         /* 15 �������Ķ���ʧ�� */
    MSTP_ERR_CRT_TASK_FAIL,           /* 16 ����mstp����ʧ�� */
    MSTP_ERR_CRT_TIMER_FAIL,          /* 17 ������ʱ��ʧ�� */
    MSTP_ERR_ISNOT_INIT,              /* 18 MSTP��δ��ʼ�� */
    MSTP_ERR_L2IF_NOTREG,             /* 19 MSTP������L2IFģ��δע�� */ 
    
    MSTP_ERR_PPINOREGISTER,           /* 20 MSTP�·�NP PPI�ӿ�δע�� */    
    MSTP_ERR_EVENTNOREGISTER,         /* 21 MSTP�¼�������δע�� */
    MSTP_ERR_INSTANCE_OVERFLOW,       /* 22 ���õ�ʵ��ID������Χ */
    MSTP_ERR_NOREG_GET_PORT_LINK_STATUS_HOOK,   /* 23 û��ע���ȡport��·״̬�Ĺ��Ӻ��� */
    MSTP_ERR_GET_PORT_LINK_STATUS_FAIL,         /* 24 ��ȡport��·״̬ʧ�� */
    MSTP_ERR_PORT_PRIORITY_OVERFLOW,            /* 25 �û������port���ȼ����� */
    MSTP_ERR_BRIDGE_PRIORITY_OVERFLOW,/* 26 ָ���������ȼ�������Χ */
    MSTP_ERR_BRIDGE_STP_DISABLE,      /* 27 ��STPδʹ�� */
    MSTP_ERR_PORT_NOTUSED,            /* 28 �˿�δʹ�� */
    MSTP_ERR_PARA_CIST,               /* 29 ���ܶ�CIST���в��� */
    
    MSTP_ERR_MALLOC_FAIL,             /* 30 �ڴ����ʧ�� */    
    MSTP_ERR_ENQUEUE_FAIL,            /* 31 �����ʧ��*/
    MSTP_ERR_GET_TRUNK_FAIL,          /* 32 ��ȡ��Ա�˿ڵĸ��ӿ�ʧ�� */
    MSTP_ERR_INVALID_PATHCOSTSTANDARD,/* 33 ��Ч��·���������㷽ʽ */
    MSTP_ERR_PRI_OR_SEC_ROOT,         /* 34 ����������������򱸷ݽ��������д˲��� */
    MSTP_ERR_ROOT_TYPE_WRONG,          /* 35 ���ø����ʹ��� */
    MSTP_ERR_DEBUG_TYPE,              /* 36 MSTP����ĵ������� */
    MSTP_ERR_EDGEPORT,                /* 37 �˿��Ǳ�Ե�˿ڣ�����ʧ�� */             
    MSTP_ERR_LOOPGUARD,               /* 38 �˿������˻��ر���������ʧ�� */
    MSTP_ERR_ROOTGUARD,               /* 39 �˿������ø��ű���������ʧ�� */    
    
    MSTP_ERR_WRITE_EVENT_FAILED,      /* 40 д�¼�ʧ�� */
    MSTP_ERR_STAT_NULL,               /* 41 ����ͳ��ָ��Ϊ�� */
    MSTP_ERR_HISTORY_OVERFLOW,        /* 42 ��ʷ��־������������ */
    MSTP_ERR_HISTORY_ISINIT,          /* 43 ��ʷ��¼�����Ѵ� */
    MSTP_ERR_PORT_STP_DISABLE,        /* 44 �˿�STPδʹ�� */
    MSTP_ERR_PORT_ISNOTACTIVE,        /* 45 �˿���ʵ����δ��Ч */
    
    MSTP_ERR_MAXCODE                  /* �������� */
}MSTP_ERRCODE_E;

#define MSTP_TRUE   1
#define MSTP_FALSE  0

#define MSTP_MAX_INSTANCE     16
#define MSTP_MAX_VLANBITMAP   128
#define MSTP_MAX_PORT_NUM     128
#define MSTP_MIN_VLAN         1
#define MSTP_MAX_VLAN         4096

#define MSTP_MAX_MAXAGE       40      /* ���MaxAge */
#define MSTP_MIN_MAXAGE       6       /* ��СMaxAge */

#define MSTP_MAX_FWDDELAY     30      /* ���Forward Delay */
#define MSTP_MIN_FWDDELAY     4       /* ��СForward Delaye */

#define MSTP_MAX_HELLOTIME    10      /* ���Hello Time */
#define MSTP_MIN_HELLOTIME    1       /* ��СHello Time */

#define MSTP_MAX_TIMEFACTOR   10      /* ���ʱ������ */
#define MSTP_MIN_TIMEFACTOR   1       /* ��Сʱ������ */

#define MSTP_MAX_DIAMETER     7       /* �������ֱ�� */
#define MSTP_MIN_DIAMETER     2       /* ��С����ֱ�� */
#define MSTP_DIAMETER_TABLE   (MSTP_MAX_DIAMETER - MSTP_MIN_DIAMETER + 1)   /* ����ֱ����Ӧ���С */

#define MSTP_MAX_MAXHOPS      40      /* ��������� */
#define MSTP_MIN_MAXHOPS      1       /* ��С������ */



#define MSTP_DEFAULT_BRIDGE_PRIORITY  32768       /* �ŵ����ȼ� */
#define MSTP_DEFAULT_PORT_PRIORITY    128         /* �˿ڵ����ȼ� */

#define MSTP_DEFAULT_DIAMETER         7           /* ����ֱ�� */
#define MSTP_DEFAULT_FWDDELAY         15          /* Forward Delayʱ���� */
#define MSTP_DEFAULT_HELLOTIME        2           /* Hello Timeʱ���� */
#define MSTP_DEFAULT_MAXAGE           20          /* Max Ageʱ���� */
#define MSTP_DEFAULT_MESSAGEAGE       0           /* Message Ageʱ��ֵ */
#define MSTP_DEFAULT_MAXHOPS          20          /* MAX Hops */
#define MSTP_DEFAULT_TIMEFACTOR       1           /* Ĭ��ʱ������ */


#define MSTP_DEFAULT_PORTID           0           /* �˿�ID */
#define MSTP_DEFAULT_TRANSMIT_LIMIT   3           /* ������������ֵ */
#define MSTP_DEFAULT_ALLTIMER_VALUE   0           /* ���ж�ʱ���ĳ�ʼֵ*/

#define MSTP_DEFAULT_REVISION_LEVEL   0           /* �޶����� */

#define MSTP_MAX_BRIDGE_PRIORITY      15          /* �ŵ�������ȼ� */
#define MSTP_MAX_PORT_PRIORITY        15          /* port������ȼ� */

#define MSTP_POINTTOPOINT      1
#define MSTP_NOPOINTTOPONIT    2
#define MSTP_AUTO              3

/* ȱʡ·�����������׼�� */
#define MSTP_PATHCOSTSTANDARD_DOT1D     1 /* 802.1D-1998 */
#define MSTP_PATHCOSTSTANDARD_DOT1T     2 /* 802.1t */
#define MSTP_PATHCOSTSTANDARD_LEGACY    3 /* legacy */

/************************ MSTP��Ϣ�¼��궨�� *******************************/
#define    MSTP_L2IF_EVENT              0x01         /*�ײ���·״̬�仯����Ϣ�¼�*/
#define    MSTP_BPDU_EVENT              0x02         /*BPDU���Ľ��յ���Ϣ�¼�*/
#define    MSTP_TIMER_EVENT             ( 1 << 15 )         /*MSTP״̬����ʱ����Ϣ�¼�*/

/* �˿ڽ�ɫ�궨�� */
#define MSTP_ROLE_DISABLED              0x01    /* ��ʼֵ        */
#define MSTP_ROLE_ALTERNATE             0x02    /* Alternate�˿� */
#define MSTP_ROLE_BACKUP                0x03    /* Backup�˿�    */
#define MSTP_ROLE_ROOT                  0x04    /* ���˿�        */
#define MSTP_ROLE_DESIGNATED            0x05    /* ָ���˿�      */
#define MSTP_ROLE_MASTER                0x06    /* master�˿�    */

/* Force Versionģʽ���� */
#define MSTP_MODE                3    /* MSTPģʽ */
#define RSTP_MODE                2    /* RSTPģʽ */
#define STP_COMP_MODE            0    /* STP����ģʽ */
/* �������Ƿ񼤻� */
#define MSTP_REGIONINFO_ACTIVE                  1
#define MSTP_REGIONINFO_INACTIVE                0


/* MSTP Enable Mode */
typedef enum tagMSTP_Enable_Mode_E
{
    MSTP_ENABLE_MODE_BRIDGE = 0,      /* ��ȫ��ģʽʹ��/ȥʹ��MSTP */
    MSTP_ENABLE_MODE_PORT,            /* ���˿�ģʽʹ��/ȥʹ��MSTP */
}MSTP_ENABLE_MODE_E;


/* MSTP PPI Msg Type */
typedef enum tagMSTP_PPI_MSG_TYPE_E
{
    PPI_SET_MSTP_ENABLE = 1,         /* ��ָ���ӿ�ʹ�ܻ�ȥʹ��MSTP */
    PPI_SET_MSTP_VLAN_INSTANCE,      /* ����VLAN��ʵ���Ĺ�ϵ */
    PPI_SET_MSTP_STATE               /* ����ָ���Ķ���˿���MSTIʵ���е�״̬ */
}MSTP_PPI_MSG_TYPE_E;

/*  �����˿ڵ�MSTPת��״̬*/
typedef enum enMstpPortStatus
{
    PORT_MSTP_DISCARDING = 0,
    PORT_MSTP_LEARNING,
    PORT_MSTP_FORWARDING,
}MSTP_PORT_STATE_E;
typedef struct tagMSTP_INSTANCE_VLAN_MAPPING
{
    ULONG    ucInstanceID;       
    ULONG    ulVLANIDMap[MSTP_MAX_VLANBITMAP];
}MSTP_INSTANCE_VLAN_MAPPING_S;

/* ������������ */
typedef enum tagMSTP_ROOT_TYPE
{
    MSTP_NORMAL_ROOT = 0,   /* ��ͨ���� */ 
    MSTP_PRIMARY_ROOT,      /* ���������� */
    MSTP_SECONDARY_ROOT,    /* ���ݸ������� */
}MSTP_ROOT_TYPE_E;

/* ɾ��MAC��ARP����Ϣ*/
typedef enum tagMSTP_EVENT_TYPE
{
    MSTP_FDB_DEL_BY_VLANS_AND_ALL_PORT = 0,
    MSTP_ARP_DEL_BY_VLANS_AND_ALL_PORT,
    MSTP_ARP_AGE_BY_VLANS_AND_ALL_PORT,
    MSTP_L2IF_MSG_REFRESH_VLAN,
    MSTP_STP_PORT_STATE_DISCARDING,
    MSTP_STP_PORT_STATE_FORWARDING,
}MSTP_EVENT_TYPE_E;

/*Э������*/
typedef enum tagMSTP_PROTOCOLTYPE
{
    MSTP_802DOT1S,          /*802.1s��׼Э��*/
    MSTP_LEGACY,            /*��Ϊ˽��Э��*/
    MSTP_COMPLIANCE_AUTO,   /*��������Ӧ��ʽ*/
}MSTP_PROTOCOLTYPE_E;

typedef enum enMstpPortGuardType        
{
    MSTP_NOTGUARD,         /* δ���ñ��� */
    MSTP_ROOTGUARD,        /* �����˸����� */   
    MSTP_LOOPGUARD,        /* �����˻����� */
    MSTP_BPDUGUARD,        /* BPDU���� */
}MSTP_PORTGUARDTYPE_E;


typedef struct tagMSTP_PPI_STATE_MSG
{ 
    /*ULONG ulIfIndex;*/
    ULONG ulInstance;
    ULONG ulState;
}MSTP_PPI_STATE_MSG_S;

typedef struct tagMSTP_PPI_VLANMAP_MSG
{ 
    ULONG ulInstance;
    ULONG ulVLANIDMap[MSTP_MAX_VLANBITMAP];
}MSTP_PPI_VLANMAP_MSG_S;

typedef struct tagMSTP_PPI_ENABLE_MSG
{ 
    ULONG ulIfIndex;
    ULONG ulMSTPEnable;
}MSTP_PPI_ENABLE_MSG_S;


typedef struct tagMSTP_PPI_COUNT
{ 
    ULONG ulMSTPUpdateTotal;  /* MSTP����֪ͨ�ܴ��� */
    ULONG ulMSTPUpdateFailure; /* MSTP����֪ͨʧ�ܴ��� */    
}MSTP_PPI_COUNT_S;

typedef struct tagMstpStateChangeInfo
{
    ULONG  ulState;                /*������ʲô״̬�����仯*/
    ULONG  ulPortIndex;             /* �˿ڵ��߼�����ֵ */
    ULONG  ulCurrentValue;          /* ��Ӧ��״̬�仯��ȡֵ */
}MSTP_STATECHANGEINFO_S;

typedef enum enARP_AGE_TYPE
{
    ARP_AGING_MODE_DEL = 0x01,  /* ����ֱ��ɾ�����ϻ���ʽ */
    ARP_AGING_MODE_AGE,         /* ���÷��ͱ��ĵ��ϻ���ʽ */
}ARP_AGE_TYPE_E;

typedef struct tagMSTP_GUARD_WARNING
{
    ULONG ulIfIndex;     /* �ӿ�����*/
    ULONG ulInstanceId;  /* ʵ��ID */
    ULONG ulWarningType; /* �澯����*/
}MSTP_GUARD_WARNING_S;

#define MSTP_WARN_BPDUGUARD      1   /* BPDU�����澯����*/
#define MSTP_WARN_LOOPGUARD      2   /* ���ر����澯����*/
#define MSTP_WARN_ROOTGUARD      3   /* ROOT�����澯����*/

/* �˿�ͳ����Ϣ */
typedef struct tagMSTPStatistic
{
    ULONG   ulTxConfigBPDU;     /* �˿ڷ��͵�Config BPDU����Ŀ */
    ULONG   ulTxTCNBPDU;        /* �˿ڷ��͵�TCN BPDU����Ŀ */
    ULONG   ulTxRSTPBPDU;       /* �˿ڷ��͵�RSTP BPDU����Ŀ */ 
    ULONG   ulTxMSTPBPDU;       /* �˿ڷ��͵�MSTP BPDU����Ŀ */ 

    ULONG   ulRcvdConfigBPDU;   /* �˿ڽ��յ���Config BPDU����Ŀ */
    ULONG   ulRcvdTCNBPDU;      /* �˿ڽ��յ���TCN BPDU����Ŀ */
    ULONG   ulRcvdRSTPBPDU;     /* �˿ڽ��յ���RSTP BPDU����Ŀ */
    ULONG   ulRcvdMSTPBPDU;     /* �˿ڽ��յ���MSTP BPDU����Ŀ */
    
    ULONG   ulRcvdTCBPDU;       /* �˿ڼ�¼�յ���TC�������˱仯����Ŀ */

    ULONG   ulRecordFlag;       /* �˿��շ����ı�־�����շ�������Ϊ1������Ϊ0 */
}MSTP_PORTSTATISTIC_S;

typedef MSTP_PORTSTATISTIC_S MSTP_PORTSTATISTIC_S_ARRAY[MSTP_MAX_PORT_NUM];  

typedef ULONG (*MSTP_GET_LOCALMAC_HOOK_FUNC)(UCHAR szMacAddr[6]);
typedef ULONG (*MSTP_GET_PORTLINKSTATUS_HOOK_FUNC)(ULONG ulPortIndex, ULONG *pulLinkStatus);
typedef ULONG (*MSTP_GET_PORTINDEXBYIFINDEX_HOOK_FUNC)(ULONG ulIfIndex,ULONG *pulPortIndex);
typedef ULONG (*MSTP_GET_IFINDEXBYPORTINDEX_HOOK_FUNC)(ULONG ulPortIndex,ULONG *pulIfIndex);
typedef ULONG (*MSTP_IF_PORTISUSED_HOOK_FUNC)(ULONG ulPortIndex);
typedef ULONG (*MSTP_GET_PORTLISTINVLAN_HOOK_FUNC)(USHORT usVlanId, ULONG *pulPortNum, ULONG ulIfList[MSTP_MAX_PORT_NUM]);
typedef ULONG (*MSTP_SENDPACKET_HOOK_FUNC)(ULONG ulIfIndex, UCHAR *pucBuf, ULONG ulDataLen);
typedef ULONG (*MSTP_PPI_HOOK_FUNC)(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);
typedef ULONG (*MSTP_EVENT_HOOK_FUNC)(ULONG ulIfIndex,ULONG ulCmd, ULONG ulInstanceId);
typedef ULONG (*MSTP_GET_PORT_DUPLEX_STATE_HOOK_FUNC)(ULONG ulIfIndex, ULONG *pulPortDuplexState);
typedef ULONG (*MSTP_GET_IFNAMEBYINDEX_HOOK_FUNC)(ULONG ulIfIndex, UCHAR *pIfName);
typedef ULONG (*MSTP_GET_IFINDEXBYNAME_HOOK_FUNC)(CHAR* szIfName, ULONG *pulIfIndex);
typedef ULONG (*MSTP_IF_ISL2PORT_HOOK_FUNC)(ULONG ulIfIndex);
typedef ULONG (*MSTP_GET_PORTSPEED_HOOK_FUNC)(ULONG ulPortIndex,ULONG *pulPortActualSpeed);
typedef ULONG (*MSTP_ISPORTINVLAN_HOOK_FUNC)(ULONG ulPortIndex,USHORT usVlanId);
typedef ULONG (*MSTP_IF_SHUTDOWN_HOOK_FUNC)(ULONG ulIfIndex);
typedef VOID (*MSTP_BEGIN_PT_HOOK_FUNC)();
typedef VOID (*MSTP_END_PT_HOOK_FUNC)();
typedef VOID (*MSTP_INFOOUTPUT_HOOK_FUNC)(CHAR *pszMsg);
typedef VOID (*MSTP_WARNINGOUTPUT_HOOK_FUNC)(ULONG ulWarningID, VOID* pWarnParam);
typedef VOID (*MSTP_DEBUGOUTPUT_HOOK_FUNC)(CHAR *pBuf);
typedef VOID (*MSTP_HEALTH_BATCHCHECKUP_HOOK_FUNC)();

/* �ű�ʶ��,�����ŵı�ʶ�� */
typedef struct tagMSTP_BridgeID
{
    ULONG   ulHigh;         /* ��32λ */
    ULONG   ulLow;          /* ��32λ */
}MSTP_BRIDGEID_S;

/* CIST����Ϣ */
typedef struct tagMSTP_CISTBRIDGE_INFO
{
    MSTP_BRIDGEID_S  stLocalBridgeID;  /* ����ID */
    MSTP_BRIDGEID_S  stRootBridgeID;   /* ����ID */
    MSTP_BRIDGEID_S  stRegRootBridgeID;/* ���ID */
    ULONG  ulPortIfIndex;              /* ���˿ڽӿ����� */
    ULONG  ulPriority;                 /* ����ʵ���е����ȼ� */
    ULONG  ulExtRootPathCost;          /* ���ŵ�CIST���ŵ�·������ */
    ULONG  ulIntRootPathCost;          /* ���ŵ������·������ */
       
    /* ʱ������ */
    UCHAR  ucAdminMaxAge;              /* ������Ϣ����������� */
    UCHAR  ucAdminFwdDelay;            /* �˿ڽ���Forwarding״̬���ӳ�ʱ�� */
    UCHAR  ucAdminHelloTime;           /* ��ʱ��������BPDUs�������ʱ�� */
    UCHAR  ucAdminMaxHops;             /* ���õ�������� */

    UCHAR  ucOperMaxAge;               /* ��Ч��BPDU����������� */
    UCHAR  ucOperMessageAge;           /* ��Ч��BPDU�ĵ�ǰ������ */
    UCHAR  ucOperFwdDelay;             /* ��Ч�Ķ˿ڽ���Forwarding״̬���ӳ�ʱ�� */
    UCHAR  ucOperHelloTime;            /* ��Ч�Ķ�ʱ��������BPDUs�������ʱ�� */
    UCHAR  ucOperMaxHops;              /* ��Ч��������� */
    
    UCHAR  ucBridgeStpEnable;          /* True:�ŵ�������Э���Ѿ����� False:�ŵ�������Э��δ���� */ 
    UCHAR  ucTimeFactor;               /* ʱ������ */
    UCHAR  ucArpAgingMode;             /* ARP����ɾ��ʱ���õ��ϻ���ʽ����ʼ��ΪARP_AGING_MODE_SEND  */
    UCHAR  ucStpDiameter;              /* CIST�ϵ�����ֱ�� */
    UCHAR  ucForceVersion;             /* 0:STP����ģʽ; 2:RSTPģʽ ;3:MSTPģʽ */
    UCHAR  ucBpduGuard;                /* ����BPDU Guard�����portfast�˿��յ�BPDU���ģ� ��ö˿ڽ���shutdown�� */
    UCHAR  ucDefaultPathCostStandard;  /* ȱʡPathCost�����׼1- IEEE 802.1D-1998  2- IEEE 802.1t */
    UCHAR  ucRootType;                 /* �������ĸ����� 0: normal; 1:Secondary Root; 2: Primary Root */
    UCHAR  ucReserve[3];
}MSTP_CISTBRIDGE_INFO_S;

/* MSTI����Ϣ */
typedef struct tagMSTP_MSTIBRIDGE_INFO
{
    MSTP_BRIDGEID_S  stLocalBridgeID;     /* ����ID */
    MSTP_BRIDGEID_S  stRegRootBridgeID;   /* ���ID */
    MSTP_BRIDGEID_S  stMasterBridgeID;    /* MASTER��ID */

    ULONG            ulIntRegRootPathCost;/* ���ŵ�MSTI�����·������ */
    ULONG            ulIntMasterPathCost; /* ���ŵ�MASTER�ŵ�·������ */
    ULONG            ulPortIfIndex;       /* ���˿ڽӿ����� */
    ULONG            ulPriority;          /* ����ʵ���е����ȼ� */
    UCHAR            ucAdminMaxHops;      /* ���õ�������� */
    UCHAR            ucOperMaxHops;       /* ��Ч��������� */ 
    UCHAR            ucRootType;          /* �������ĸ����� 0: normal; 1:Secondary Root; 2: Primary Root */
    UCHAR            ucReserve;
}MSTP_MSTIBRIDGE_INFO_S;

/* CIST�˿���Ϣ */
typedef struct tagMSTP_CISTPORT_INFO
{
    MSTP_BRIDGEID_S stDesignatedBridgeID; /* ָ����ID */
    UCHAR ucPortStpEnable;                /* �˿�Э���Ƿ�ʹ�� */
    UCHAR ucPortState;                    /* �˿�״̬ */
    UCHAR ucPortRole;                     /* �˿ڽ�ɫ */
    UCHAR ucPortProtection;               /* �˿ڱ�����Ϣ,BPDU�������Ե�˿ڱ��� */
    
    UCHAR ucAdminPointToPointMAC;         /* �ö˿��Ƿ�����ӵ�Ե���·������Ϣ */
    UCHAR ucOperPointToPointMAC;          /* �ö˿��Ƿ�����ӵ�Ե���·��Ч��Ϣ */
    UCHAR ucNoAgreementCheck;             /* �Ƿ�����NoAgreement���� */ 
    UCHAR ucConfigDigestSnoop;            /* �Ƿ�����ժҪ̽�⹦�� */ 
    
    ULONG ulAdminPortPathCost;            /* ϵͳ���õĶ˿�·��ֵ */ 
    ULONG ulOperPortPathCost;             /* �˿�ʵ�ʶ�Ӧ��·������ */  
    ULONG ulPortPriority;                 /* �˿����ȼ�ֵ */
    ULONG ulTransitLimit;                 /* hello timeʱ���������͵ı��ĸ��� */
    
    USHORT usDesignatedPortID;            /* ָ���˿�ID*/
    UCHAR ucIsAdminEdged;                 /* �Ƿ�����Ϊ��Ե�˿� */
    UCHAR ucIsOperEdged;                  /* �Ƿ���Ч�ı�Ե�˿� */

    UCHAR ucAdminProtocolType;            /* ���õĶ˿��շ�BPDU���ĸ�ʽ */  
    UCHAR ucOperProtocolType;             /* ��Ч�Ķ˿��շ�BPDU���ĸ�ʽ */  
    UCHAR ucSendVersion;                  /* ����BPDU���İ汾 */
    UCHAR ucPortActive;                   /* �˿��Ƿ�ʹ��MSTP���˿�UP */
}MSTP_CISTPORT_INFO_S;

/* MSTI�˿���Ϣ */
typedef struct tagMSTP_MSTIPORT_INFO
{
    MSTP_BRIDGEID_S stDesignatedBridgeID; /* ָ����ID */
    ULONG ulPortPriority;                 /* �˿����ȼ�ֵ */
    ULONG ulAdminPortPathCost;            /* ϵͳ���õĶ˿�·��ֵ */ 
    ULONG ulOperPortPathCost;             /* �˿�ʵ�ʶ�Ӧ��·������ */  

    USHORT usDesignatedPortID;            /* ָ���˿�ID*/
    UCHAR ucPortStpEnable;                /* �˿�Э���Ƿ�ʹ�� */
    UCHAR ucPortState;                    /* �˿�״̬ */

    UCHAR ucPortRole;                     /* �˿ڽ�ɫ */
    UCHAR ucPortActive;                   /* �˿��Ƿ�ʹ��MSTP���˿�UP */
    UCHAR ucReserve[2];
}MSTP_MSTIPORT_INFO_S;

/* �˿ڼ�Ҫ��Ϣ */
typedef struct tagMSTP_BRIEF_INFO
{
    UCHAR ucPortRole;         /* �˿ڽ�ɫ */
    UCHAR ucPortState;        /* �˿�״̬ */
    UCHAR ucReserve[2];
}MSTP_BRIEF_INFO_S;


extern ULONG MSTP_SetRegionName(UCHAR *pcRegionName);


extern ULONG MSTP_SetRegionRevisionLevel(USHORT usRevisinLevel);



extern ULONG MSTP_SetRegionInstanceVlanMap(MSTP_INSTANCE_VLAN_MAPPING_S *pstInstanceVlanMap);


extern ULONG MSTP_GetRegionInfo(ULONG ulType, UCHAR *pcRegionName, ULONG *plRevisionLevel, 
                                MSTP_INSTANCE_VLAN_MAPPING_S  stVlanMap[MSTP_MAX_INSTANCE + 1]);


extern ULONG MSTP_ActiveRegionInfo(VOID);



extern VOID MSTP_ShowRegionInfo(ULONG ulType);


/*******************************************************************************
*    Func Name: MSTP_GetPortStateInInstance
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: ��ȡ�˿���ʵ���е�ת��״̬
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulInstanceID:ʵ��ID
*       Output: ULONG *pulProtState: �˿ڵ�ת��״̬������PORT_MSTP_FORWARDING,
*               PORT_MSTP_LEARNING��PORT_MSTP_DISCARDING����
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetPortStateInInstance(ULONG ulIfIndex, ULONG ulInstanceID, ULONG *pulProtState);

/*******************************************************************************
*    Func Name: MSTP_GetInstanceIDByVlanId
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: 
*        Input: ULONG ulVlanID: VLAN ID
*       Output: ULONG *pulInstanceID: ʵ��ID
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetInstanceIDByVlanId(ULONG ulVlanID, ULONG *pulInstanceID);

/*******************************************************************************
*    Func Name: MSTP_SetEnable
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: ��ȫ��ģʽ�򰴽ӿ�ģʽʹ��/ȥʹ��MSTP
*        Input: ULONG ulType: ��ȫ��ģʽ�򰴽ӿ�ʹ��/ȥʹ��MSTP��ȡֵ��
*               MSTP_ENABLE_MODE_BRIDGE��MSTP_ENABLE_MODE_PORT
*               ULONG ulIfIndex: ����˿ڵĽӿ����������ӿ�ʹ��MSTPʱ���贫�룻��
*               ��ȫ��ģʽʹ��ʱ�����贫�룬���򲻶Ը�ֵ����
*               ULONG ulSetYes: ʹ��/ȥʹ��MSTP��ȡֵ��MSTP_TRUE��MSTP_FALSE
*       Output: 
*       Return: �ɹ��򷵻�MSTP_OK��ʧ���򷵻ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetEnable(ULONG ulType, ULONG ulIfIndex, ULONG ulSetYes);



extern ULONG MSTP_SetBridgeDiameter(ULONG ulDiameter);


extern ULONG MSTP_SetConverge(ULONG ulType);


extern ULONG MSTP_SetBpduProtection(ULONG ulSetYes);


extern ULONG MSTP_SetRootProtection(ULONG ulIfIndex, ULONG ulSetYes);


extern ULONG MSTP_SetPortLoopProtection(ULONG ulIfIndex, ULONG ulSetYes);


extern ULONG MSTP_SetPortMcheck(ULONG ulIfIndex);

/*******************************************************************************
*    Func Name: MSTP_SetPortPathCostInInstance
* Date Created: 2008-12-04
*       Author: zengshaoyang62531
*  Description: ��ʵ��������Port��·������
*        Input: ULONG ulIfIndex:Port����
*               ULONG ulInstance:ʵ��ID
*               ULONG ulCost:·������
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortPathCostInInstance(ULONG ulIfIndex, ULONG ulInstance, ULONG ulCost);

/*******************************************************************************
*    Func Name: MSTP_SetDefaultPortPathCostInInstance
* Date Created: 2009-01-13
*       Author: zengshaoyang62531
*  Description: �ָ�ʵ���нӿڵ�ȱʡ·������
*        Input: ULONG ulIfIndex:Port ifnet����
*               ULONG ulInstance:ʵ��ID
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-01-13   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG MSTP_SetDefaultPortPathCostInInstance(ULONG ulIfIndex, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_SetEdgedPort
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: ����portΪ��Ե�˿�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulSetYes:1,����Ϊ��Ե�˿ڣ�0��ʾȡ��
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                                       DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong00105073       Create
*
*******************************************************************************/
extern ULONG MSTP_SetEdgedPort(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPriorityInInstance
* Date Created: 2008-12-12
*       Author: lianglong111779
*  Description: ���ý�������ָ��ʵ���е����ȼ�
*        Input: ULONG ulInstanceID: ʵ��ID
*               ULONG ulPriority: ���ȼ�ֵ��ȡֵ��Χ0~15
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetPriorityInInstance(ULONG ulInstanceID, ULONG ulPriority);

/*******************************************************************************
*    Func Name: MSTP_SetPortPriorityInInstance
* Date Created: 2008-12-04
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʵ��������Port�����ȼ�
*        Input: ULONG ulIfIndex:Port�����ȼ�
*               ULONG ulInstance:ʵ��ID
*               ULONG ulPriority:���ȼ�
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortPriorityInInstance(ULONG ulIfIndex,ULONG ulInstance, ULONG ulPriority);

/*******************************************************************************
*    Func Name: MSTP_SetRootType
* Date Created: 2008-12-18
*       Author: lianglong111779
*  Description: ���ý������ĸ�����
*        Input: ULONG ulInstanceId: ʵ��ID
*               ULONG ulRootType:   ����
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-18   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetRootType(ULONG ulInstanceId, ULONG ulRootType);


extern ULONG MSTP_SetForwardDelay(ULONG ulTimer);


extern ULONG MSTP_SetHelloTimer(ULONG ulTimer);

/*******************************************************************************
*    Func Name: MSTP_SetMaxAge
* Date Created: 2008-10-22
*       Author: zhangchi
*  Description: ����MaxAge
*        Input: ULONG ulTimer:MaxAge Time(6~40S,Ĭ��20S)
*       Output: 
*       Return: �ɹ�����MSTP_OK���������ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   zhangchi                 Create
*
*******************************************************************************/
extern ULONG MSTP_SetMaxAge(ULONG ulTimer);


extern ULONG MSTP_SetTimerFactor(ULONG ulFactor);


extern ULONG MSTP_SetMaxhop(ULONG ulhop);

/*******************************************************************************
*    Func Name: MSTP_SetPathCostStandard
* Date Created: 2008-10-23
*       Author: lianglong111779
*  Description: ����·�������ļ��㷽ʽ
*        Input: ulong ulStandard: ·�������ļ��㷽ʽ��ȡֵ��MSTP_PATHCOSTSTANDARD_DOT1D,
*               MSTP_PATHCOSTSTANDARD_DOT1T��MSTP_PATHCOSTSTANDARD_LEGACY
*       Output: 
*       Return: �ɹ�MSTP_OK��ʧ������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-23   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_SetPathCostStandard(ULONG ulStandard);


extern ULONG MSTP_SetNoAgreementCheck(ULONG ulIfIndex, ULONG ulSetYes);



extern ULONG MSTP_SetPortConfigDigestSnoop(ULONG ulIfIndex, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_SetPortBPDUType
* Date Created: 2008-12-16
*       Author: wuhailan
*  Description: ����ָ���˿ڵ�BPDU�����շ���ʽ 
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulType:��������
*                            MSTP_802DOT1S:802.1s��׼Э��
*                            MSTP_LEGACY:��Ϊ˽��Э��
*                            MSTP_COMPLIANCE_AUTO:��������Ӧ��ʽ
*                            Ĭ������Ϊ����Ӧ��ʽ
*       Output: 
*       Return: �ɹ�: MSTP_OK��ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-16   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetPortBPDUType(ULONG ulIfIndex, ULONG ulType);

/*******************************************************************************
*    Func Name: MSTP_SetPortPointToPoint
* Date Created: 2008-12-04
*       Author: zengshaoyang62531,luowentong
*  Description: ���ö˿ڵ���·����
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulType:��·����
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong       Create
*
*******************************************************************************/
ULONG MSTP_SetPortPointToPoint(ULONG ulIfIndex, ULONG ulType);

/*******************************************************************************
*    Func Name: MSTP_SetPortTransmitLimit
* Date Created: 2008-12-04
*       Author: zengshaoyang62531,luowentong
*  Description: ����hello timeʱ���ڷ��͵�BPDU������Ŀ
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulLimit:hello timeʱ���ڷ��͵�BPDU������Ŀ
*       Output: 
*       Return: �ɹ�����MSTP_OK,ʧ�ܷ��ش����롣
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-04   zengshaoyang62531,luowentong       Create
*
*******************************************************************************/
ULONG MSTP_SetPortTransmitLimit(ULONG ulIfIndex, ULONG ulLimit);

/*******************************************************************************
*    Func Name: MSTP_GetVersion
* Date Created: 2008-10-22
*       Author: wuhailan
*  Description: ��ȡMSTP CBB�İ汾�źͱ���ʱ��
*        Input: CHAR *szVerInfo: MSTP CBB�İ汾��Ϣ�ͱ���ʱ���ַ���
*                                ���û�����256�ֽڿռ䡣
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_GetVersion(CHAR *szVerInfo);

/*******************************************************************************
*    Func Name: MSTP_ShowVersion
* Date Created: 2008-10-22
*       Author: lianglong111779
*  Description: ��ʾMSTP�汾��
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-10-22   lianglong111779         Create
*
*******************************************************************************/
extern VOID MSTP_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: MSTP_Init
* Date Created: 2008-11-29
*       Author: wuhailan 
*  Description: MSTP CBB��ʼ����ں���
*        Input: ULONG ulTaskPri:�������ȼ�
*               ULONG ulTaskStackSize:ջ��С
*       Output: 
*       Return: �ɹ�MSTP_OK,����������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-29   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_Init(ULONG ulTaskPri, ULONG ulTaskStackSize);

/*******************************************************************************
*    Func Name: MSTP_ShowBrief
* Date Created: 2008-12-03
*       Author: zengshaoyang62531
*  Description: ��ʾMSTP��Ҫ��Ϣ
*        Input: VOID
*       Output: VOID
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-03   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID MSTP_ShowBrief(VOID);

/*******************************************************************************
*    Func Name: MSTP_GetCISTBridgeInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: ��ȡCIST����Ϣ
*        Input: 
*       Output: MSTP_CISTBRIDGE_INFO_S *pstCistBridgeInfo: CIST����Ϣ���������
*       Return: �ɹ�MSTP_OK��ʧ������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetCISTBridgeInfo(MSTP_CISTBRIDGE_INFO_S *pstCistBridgeInfo);

/*******************************************************************************
*    Func Name: MSTP_GetMSTIBridgeInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: ��ȡָ��ʵ���е�MSTI����Ϣ
*        Input: ULONG ulInstanceID: ʵ��ID
*       Output: MSTP_MSTIBRIDGE_INFO_S *pstMstiBridgeInfo: MSTI����Ϣ���������
*       Return: �ɹ�MSTP_OK��ʧ������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetMSTIBridgeInfo(ULONG ulInstanceID, MSTP_MSTIBRIDGE_INFO_S *pstMstiBridgeInfo);

/*******************************************************************************
*    Func Name: MSTP_GetCISTPortInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: ��ȡCIST��ָ���˿ڵ���Ϣ
*        Input: ULONG ulIfIndex: ����˿ڶ�Ӧ�Ľӿ�����
*       Output: MSTP_CISTPORT_INFO_S *pstCistPortInfo: �˿���Ϣ���������
*       Return: �ɹ�MSTP_OK��ʧ������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetCISTPortInfo(ULONG ulIfIndex, MSTP_CISTPORT_INFO_S *pstCistPortInfo);

/*******************************************************************************
*    Func Name: MSTP_GetMSTIPortInfo
* Date Created: 2008-12-10
*       Author: lianglong111779
*  Description: ��ȡָ����MSTI�˿���Ϣ
*        Input: ULONG ulIfIndex: ����˿ڶ�Ӧ�Ľӿ�����
*               ULONG ulInstanceID: ʵ��ID
*       Output: MSTP_MSTIPORT_INFO_S *pstMstiPortInfo: �˿���Ϣ���������
*       Return: �ɹ�MSTP_OK��ʧ������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-10   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_GetMSTIPortInfo(ULONG ulIfIndex, ULONG ulInstanceID, MSTP_MSTIPORT_INFO_S *pstMstiPortInfo);


extern ULONG MSTP_GetBriefInfo(ULONG ulIfIndex, ULONG ulInstanceId, MSTP_BRIEF_INFO_S *pstMstpBriefInfo);


/*******************************************************************************
*    Func Name: MSTP_SetDebug
* Date Created: 2008-12-12
*       Author: wuhailan
*  Description: MSTP���Կ������ýӿ�
*        Input: ULONG ulIfIndex:�ӿ�����
*               ULONG ulType:���õĵ�������
*                            MSTP_DEBUG_PACKET,��������Կ���
*                            MSTP_DEBUG_ERROR,���Ĵ�������Կ���
*                            MSTP_DEBUG_STATE,״̬������Կ���
*                            MSTP_DEBUG_EVENT,�����¼�����Կ���
*                            MSTP_DEBUG_ALL,��ȫ�����͵��Կ���
*               ULONG ulSetYes:���Կ���
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetDebug(ULONG ulPortIndex, ULONG ulType, ULONG ulSetYes);

/*******************************************************************************
*    Func Name: MSTP_ShowInfoAll
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʾ����������ʵ�����˿���ϸ��Ϣ
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowInfoAll(VOID);

/*******************************************************************************
*    Func Name: MSTP_ShowStpTimer
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ָ��port��ָ��ʵ�����������ʾ����ʱ����ֵ
*        Input: CHAR* szIfName:�ӿ�����
*               ULONG ulInstance:ʵ��id
*       Output: 
*       Return: VOID
*      Caution: ����ʾ�ӿ���ʾMSTP�ڲ���ʱ������ֵ,ֻ��ΪVISP�ڲ�������Ա��λ����ο�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                              DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowStpTimer(CHAR* szIfName, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_ShowCistBridge
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʾCIST��Ϣ
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                            DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong        Create
*
*******************************************************************************/
extern VOID MSTP_ShowCistBridge(VOID);

/*******************************************************************************
*    Func Name: MSTP_ShowCISTPortInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʾCISP�˿���Ϣ
*        Input: CHAR* szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowCISTPortInfo(CHAR* szIfName);

/*******************************************************************************
*    Func Name: MSTP_ShowMSTIBridgeInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʾmsti����Ϣ
*        Input: ULONG ulInstance:ʵ��ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                        DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowMSTIBridgeInfo(ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_ShowMSTIPortInfo
* Date Created: 2008-12-12
*       Author: zengshaoyang62531/luowentong
*  Description: ��ʾMSTI�˿���Ϣ
*        Input: CHAR* szIfName:�ӿ���
*               ULONG ulInstance:ʵ��ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                               DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-12   zengshaoyang62531/luowentong       Create
*
*******************************************************************************/
extern VOID MSTP_ShowMSTIPortInfo(CHAR* szIfName, ULONG ulInstance);

/*******************************************************************************
*    Func Name: MSTP_PacketEnQueue
* Date Created: 2008-12-01
*       Author: lianglong111779
*  Description: �����յ�MSTP����ʱ��������MSTP�ı��Ķ���
*        Input: UCHAR *pucBuf:MSTP����ָ��
*               ULONG ulIfIndex:�ӿ�����
*               ULONG ulBpduLen:���ĳ���
*       Output: 
*       Return: �ɹ�MSTP_OK,�������ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-01   lianglong111779         Create
*
*******************************************************************************/
extern ULONG MSTP_PacketEnQueue(UCHAR *pucBuf, ULONG ulIfIndex, ULONG ulBpduLen);


extern ULONG MSTP_LinkChgEnQuenue(MSTP_STATECHANGEINFO_S *pstInfo);

/*******************************************************************************
*    Func Name: MSTP_SetForceVersion
* Date Created: 2008-12-16
*       Author: wuhailan
*  Description: ���ð汾���Ĵ���汾��Ϣ
*        Input: ULONG ulForceVersion:�汾��Ϣ,Ĭ��MSTP_MODE.��ȡֵMSTP_MODE/RSTP_MODE/STP_COMP_MODE
*       Output: 
*       Return: �ɹ�MSTP_OK������������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-12-16   wuhailan                Create
*
*******************************************************************************/
extern ULONG MSTP_SetForceVersion(ULONG ulForceVersion);


extern ULONG MSTP_GetVlanMapByInstance(ULONG ulType,ULONG ulInstance,
                                                        ULONG ulVLANIDMap[MSTP_MAX_VLANBITMAP]);


extern ULONG MSTP_SetRecoredHistory(ULONG ulSetYes, ULONG ulHistoryLen);


extern VOID MSTP_ShowHistory(VOID);


extern ULONG MSTP_ResetBpduStatistic(VOID);


extern ULONG MSTP_GetBpduStatistic(ULONG ulIfIndex, ULONG ulInstanceID, MSTP_PORTSTATISTIC_S *pstPortStatistic);


extern VOID MSTP_ShowBpduStatistic(VOID);


#ifdef  __cplusplus
}
#endif

#endif




