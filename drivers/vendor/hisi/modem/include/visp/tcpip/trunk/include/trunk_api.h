/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_api.h
*
*  Project Code: VISPV1R6
*   Module Name:   
*  Date Created: 2008-3-8
*        Author: LY(57500)
*   Description: trunkģ������ṩ���û��ӿ����������ݽṹ�ͺ궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-3-8  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _TRUNK_API_H_
#define _TRUNK_API_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunkģ���û�API������ */
enum enTrunkErrInfo
{
    TK_OK  = VOS_OK,
    TK_ERR = VOS_ERR,
    TK_PARAM_ERR,                  /* 2������������Ϸ� */
    TK_IF_NULL,                    /* 3�����ݽӿ�������ȡ�ӿ�ָ��Ϊ�� */
    TK_REPEAT_JOIN,                /* 4���˿��Ѿ�������Trunk */
    TK_TRUNKID_NULL,               /* 5��Trunk ID�޶�ӦTrunk�ӿ� */
    TK_PORT_FULL,                  /* 6��Trunk���Ѿ���8����Ա�˿� */
    TK_PORT_ISNOT_FE,              /* 7���˿ڲ���FE�ڻ�GE�� */
    TK_PORT_HAVE_IP,               /* 8���˿ھ���IP������ԣ����Ѿ������˵�ַ���Ѿ����õ�ַ�������ӿ� */
    TK_IF_ISNOT_MEMBERSHIPPORT,    /* 9���ӿڲ��ǳ�Ա�˿� */
    TK_TRUNKCB_NULL,               /* 10���ӿڵ�Trunk���ƿ�Ϊ�� */
    TK_PORT_HAVE_PPPOE,            /* 11���˿��Ѿ�ʹ��PPPOE */
    TK_LACP_NEGOTBL_NULL,          /* 12���˿ڵ�LACPЭ����Ϣ��Ϊ�� */
    TK_LACP_FSMTBL_NULL,           /* 13���˿ڵ�״̬����Ϣ��Ϊ�� */
    TK_TRUNK_HAVE_PORT,            /* 14��Trunk�����г�Ա�˿� */
    TK_HA_IS_SMOOTHING,            /* 15��HA�����ֶ�������ƽ������*/
    TK_IF_ISNOT_TRUNK,             /* 16���ӿڲ���Trunk�ӿ� */ 
    TK_PORT_CFG_DHCP4R,            /* 17���ӿ�������DHCP4 RELAY     */ 
    TK_TRUNKID_ERR,                /* 18��Trunk IDֵ�Ƿ�            */ 
    TK_PORT_HAVE_MULTIIP,          /* 19���˿ھ��жಥIP            */
    TK_PORT_HAVE_IPV6,             /* 20���˿���ipv6��ַ            */ 
    TK_TRUNK_IF_NULL,              /* 21��Trunk�ӿ�Ϊ��             */ 
    TK_IPIF_NULL,                  /* 22���ӿڵ�ipif���ƿ�Ϊ��      */
    TK_TRUNKCB_NOMEM,              /* 23������trunk cb���ƿ��ڴ�ʧ��    */
    TK_PORTINFO_NOMEM,             /* 24������port info���ƿ��ڴ�ʧ��   */
    TK_LACPNEGO_NOMEM,             /* 25������lacp nego���ƿ��ڴ�ʧ��   */
    TK_LACPFSM_NOMEM,              /* 26������lacp fsm���ƿ��ڴ�ʧ��    */
    TK_PORTINFO_NULL,              /* 27��port info���ƿ�Ϊ��           */
    TK_NO_PORT,                    /* 28��trunk��û�г�Ա�˿�           */ 
    TK_PORT_SETVLAN,               /* 29����Ա�˿�ʹ����vlan            */
    TK_PORT_SETARPPROXY,           /* 30����Ա�˿�������ARP����         */ 
    TK_NOT_REGISTER,               /* 31��trunkģ��δע��               */ 
    TK_DYNAMIC_MAC_FIRST_PORT,     /* 32����̬physical��ַ������Ե�һ���˿ڱ������һ���˳�  */
    TK_PORT_ENABLE_1AG,            /* 33��������Trunk��Eth���Ѿ�ʹ����1AG���� */
    
    TK_IS_NOT_L3_ETH,              /* 34����������eth�ڼ��뵽L3-TRUNK�л��߽�ӳ��˿ڼ��뵽����TRUNK�� */
    TK_IS_NOT_L2_TRUNKPORT,        /* 35������L2_TRUNKPORT�ӿڼ��뵽L2-TRUNK�� */
    TK_IS_L2IF,                    /* 36������������L2TRUNK */
    TK_IS_NOT_L2IF,                /* 37���������Ĳ���L2TRUNK */
    TK_WRONG_LACP_STATUS,          /* 38������LACP״̬ʱ��������״̬ */
    TK_NOT_VIRTUAL,                /* 39�������õĶ˿ڲ���ӳ��˿�(��������뷽ʽ����L2TRUNK) */
    TK_NEG_TIME_REACHMAX,          /* 40 �ﵽ�״�Э�̲�������澯���ʱ�� */
    TK_DELETE_TIMER_FAIL,          /* 41 ɾ���״�Э�̲�������澯��ʱ��ʧ�� */   
    TK_CREATE_TIMER_FAIL,          /* 42 �����״�Э�̲�������澯��ʱ��ʧ�� */  
    TK_NULL_POINTER,               /* 43 ����ָ�����Ϊ��       */   

    TK_GET_PORTNO_FAIL,            /* 44 ��ȡPort type��Port numberʧ�� */
    TK_IS_NOT_TRUNK_TYPE,          /* 45 ����Trunk�ӿ����� */
    TK_IS_NOT_MTON_MODE,           /* 46 ����M:N����ģʽ */
    TK_LACP_ENABLE,                /* 47 ��ʹ����LACPЭ�̣���������Ϊ1:1����ģʽ */
    TK_PORT_NOT_IN_TRUNK,          /* 48 ��Ա�˿ڲ����ڸ�TRUNK�� */
    TK_WRONG_RECOVER_MODE,         /* 49 ����Ļָ�ģʽ */
    TK_WRONG_BACKUP_MODE,          /* 50 ����ı���ģʽ */
    TK_ONETOONE_PORT_FULL,         /* 51 1:1ģʽ�˿������� */
    TK_IS_NOT_THISBORAD,           /* 52 �Ǳ���ӿ� */

    TK_POLICY_IS_RECOVER_MODE,     /* 53 ��Ʒ�ö��Ʋ�����TRUNK����Ϊ�ָ�ģʽ */
    TK_POLICY_IS_LACP_ENABLE,      /* 54 ��Ʒ�ö��Ʋ�����TRUNK����ʹ��LACP */
    TK_POLICY_HAVE_MEMBERPORT,     /* 55 ʹ��/ȥʹ�ܲ�Ʒ�ö��Ʋ�����TRUNK���ܴ��ڳ�Ա�˿� */
    TK_POLICY_IS_BAKCUP_MODE_NORMAL,  /* 56 ��Ʒ�ö��Ʋ�����TRUNK����Ϊ��������ģʽ */
    TK_POLICY_ACTIVEPORT_MUST_ONE, /* 57 ��Ʒ�ö��Ʋ�����TRUNK��M:Nģʽ�¼���˿�������Ϊ1 */
    TK_POLICY_MEMBERPORT_IS_FULL,  /* 58 ��Ʒ�ö��Ʋ�����TRUNK��M:Nģʽ����Ӷ˿������ܳ���2��*/
    TK_POLICY_WRONG_TYPE,          /* 59 ����Ķ��Ʋ��� */
    TK_POLICY_IS_STATIC_GETMAC,    /* 60 ��Ʒ�ö��Ʋ�����TRUNK��physical��ַ��ȡ���Բ���Ϊ�̶�physical��ַ������� */
    
    TK_PPI_CALLBACK,               /* 61 PPI�·����Ӻ���δע��*/

    TK_NSR_STATE_ERR,              /* 62 NSR��ǰ״̬����*/
    TK_NSR_ETHER_MAC_CHANG,        /* 63 ����Trunk��Ա�˿��ϱ�����̫MAC���ֲ�һ�� */
    TK_NSR_ETHER_MAC_INVALID,         /* 64 �������ϱ�����̫MACΪ�� */
    TK_NSR_WRONG_LINK_STATUS,          /*65 ת����ά���ĵ���·״̬����*/
    TK_NSR_WRONG_LINK_KEY,          /*66 ת����ά����keyֵ������治һ�� */ 
    TK_NSR_WRONG_LINK_PORT_NO,      /*67 ת����ά����port NO. Ϊ��Чֵ*/
    TK_NSR_WRONG_LINK_EXPIRED,      /*68 ת����ά���ĳ�ʱģʽ��һ�� */
    TK_NSR_WRONG_LINK_SYSMAC,       /*69 ת����ά����ϵͳMAC����*/
    TK_NSR_ERR_PRECONFIG,           /*70 ������δ����NSR���� */
    TK_NSR_ERR_DISABLING,           /*71 TRUNK NSR��ȥʹ�ܹ�����*/
    TK_NSR_ERR_DISABLE,             /*72 TRUNK NSRδʹ��  */
    TK_NSR_LACP_MODE,               /*73 TRUNK LACP����δʹ�� */
    TK_NSR_NOT_FINISHED,            /*74 TRUNK NSR ����û�н��� */
    TK_NSR_IF_NOT_EXIST,            /*75 ����TRUNK NSR ��ѯapiʱ�Ҳ�����Ӧ�ӿ� */
    TK_NSR_IF_NOT_ETHERNET,         /*76 ����TRUNK NSR ��ѯapiʱ��Ӧ�ӿڲ���ethernet */
    TK_NSR_IF_NOT_THIS_BOARD,       /*77 ����TRUNK NSR ��ѯapiʱ��Ӧ�ӿڲ��Ǳ���� */
    TK_NSR_LINK_RESUME_FAIL,        /*78 ����·�ָ�ʧ�� */
    TK_NSR_TRUNK_MAC_RESUME_FAIL,   /*79 ��trunk mac�ָ�ʧ�� */
    TK_HA_CFGSYSMAC_ERR,            /*80 TRUNK HA��֧�ְ���TRUNK������ϵͳMAC*/
}; 

/* �����Ա�˿�ͳ����Ϣ */
typedef struct tagPORT_STAT_INFO
{
    ULONG ulOutSum;     /* ���͵ı������� */
    ULONG ulOutLacp;    /* ���͵�LACP������ */
    ULONG ulOutDrop;    /* ����ʱ�����ı����� */
    ULONG ulInSum;      /* ���յı������� */
    ULONG ulInLacp;     /* ���յ�LACP������ */
    ULONG ulInDrop;     /* ����ʱ�����ı����� */
    ULONG ulLacpExpired;  /* NP�ϱ���ʱͳ�� */
    ULONG ulLacpPPIPKT;   /* LACP�·�NP��͸������ͳ�� */
    /* Add end */
}PORT_STAT_INFO_S;

typedef struct tagTRUNK_LACP_NOTIFY
{
    UCHAR  ucOper;             /* ֪ͨ��Ϣ���ͣ�LACP_WARNING_TIMEOUT*/
    UCHAR  ucRes[3];
    ULONG  ulPortIfIndex;      /* ��Ա�˿ڽӿ����� */
}TRUNK_LACP_NOTIFY_S;
/* Add end */

/* Trunk�ӿ���С��Ա�˿���Ŀ */
#define TRUNK_PORT_MIN_NUM      1

/* Trunk�ӿ�����Ա�˿���Ŀ */
#define TRUNK_PORT_MAX_NUM      32

/* SGSN Trunk���Э������:������άֵ��ȡPortId�Ĺ��Ӻ���ԭ�� */
typedef ULONG (*TRUNK_GETLACPPORTID_HOOK_FUNC)(
    ULONG ulFirstDimension,      /* Input: �ӿڵ�һάֵ */
    ULONG ulSecondDimension,     /* Input: �ӿڵڶ�άֵ */
    ULONG ulThirdDimension,      /* Input: �ӿڵ���άֵ */
    USHORT* pusPortID);          /* Output: ���ص�Port Id */

typedef ULONG (*TRUNK_NSR_FINISHNOTIFY)(ULONG ulMsgType);


/* ���Trunk�ӿ���Ϣ�����³�Ա�˿���Ϣ */
typedef struct tagTRUNK_INFO
{
    ULONG ulIfIndex;                             /* Trunk�ӿ����� */
    ULONG ulTrunkId;                             /* Trunk ID */
    UCHAR ucMacAddress[6];                       /* Trunk��physical��ַ */
    UCHAR ucBfdTrunkMode;                        /* trunk���Ա�˿��Ͻ�������bfd����Чģʽ,Ĭ��trunk���� */   
    UCHAR ucMacDynamic;                          /* Trunk physical��ַ��ȡģʽ�Ƿ�Ϊ��̬��ȡģʽ              */
    ULONG ulPortNum;                             /* Trunk��Ա�˿����� */
    ULONG ulPortIfIndex[TRUNK_PORT_MAX_NUM];     /* ��Ա�˿ڽӿ��������� */
    ULONG ulUpPortNum;                           /* UP�ĳ�Ա�˿��� */
    ULONG ulUpPortIfIndex[TRUNK_PORT_MAX_NUM];   /* UP�ĳ�Ա�˿ڽӿ��������� */
    ULONG ulEnableLacp;                          /* �Ƿ�ʹ��LACP */
    ULONG ulRefIfIndex;                          /* �ο��˿ڽӿ����� */
    ULONG ulMacPortIndex;                        /* ��̬��ȡTrunk macʱ��ʹ��mac�ĳ�Ա�˿����� */
    ULONG ulGateValue;                           /* Trunk ��ֵ��Ϣ */
    ULONG ulVPortIfIndex[TRUNK_PORT_MAX_NUM];    /* Trunk����ӳ��˿ڷ�ʽ����ĳ�Ա�˿����� */
    ULONG ulPassive;                             /* �������˻��Ǳ����� */
    UCHAR ucBackupMode;                          /* �˿ڱ���ģʽ,0,��ͨģʽ;1,1:1����ģʽ��2,M:N����ģʽ */ 
    UCHAR ucRecoverMode;                         /* �˿ڱ��ݵĻָ�ģʽ,0,�ָ�ģʽ;1,�ǻָ�ģʽ */
    USHORT usSysPri;                             /* Trunk���ϵͳ���ȼ� */
    ULONG ulMasterIfIndex;                       /* �˿�1:1ģʽ�����õ����˿����� */
    ULONG ulActiveNum;                           /* �˿�M:Nģʽ�����õļ���˿��� */
    ULONG ulProductPolicy;                       /* ��Ʒ���Ƶ�TRUNK���� */
}TRUNK_INFO_S;

/* �����Ա�˿ڵ�״̬����Ϣ����Ϣ */
typedef struct tagLACP_FSM_INFO
{
    BOOL_T bRXBegin;              /* ����״̬����ʼ����־ */
    BOOL_T bPTXBegin;             /* ���ڷ���״̬����ʼ����־ */
    BOOL_T bMUXBegin;             /* MUX״̬����ʼ����־ */
    BOOL_T bPortEnable;           /* �˿�����״̬��־ */
    USHORT usSelected;            /* �˿�ѡ���� */
    BOOL_T bCurWhileTimerActive;  /* ���ն�ʱ��������־ */
    BOOL_T bPeriodicTimerActive;  /* ���ڷ��Ͷ�ʱ��������־ */
    UCHAR ucRXState;              /* ����״̬��״̬ */
    UCHAR ucPTXState;             /* ���ڷ���״̬��״̬ */
    UCHAR ucMUXState;             /* MUX״̬��״̬ */
    UCHAR ucPadding[3];
} LACP_FSM_INFO_S;

/* �����Ա�˿ڵ�Э����Ϣ����Ϣ */
typedef struct tagLACP_NEGO_INFO
{
    ULONG ulActor_TimeOutMode;    /* ��������ģʽ��0�������ڣ�1�������ڣ�*/
    BOOL_T bActor_PortUp;         /* ���˶˿������շ�ʹ�ܱ�־ */
    BOOL_T bActor_Defaulted;      /* ���˶˿ڴ���Ĭ��״̬��־ */
    ULONG ulActor_Key;            /* ���˶˿�����key */
    ULONG ulActor_PortPri;        /* ���˶˿����ȼ� */
    ULONG ulActor_PortNum;        /* ���˶˿ں� */

    ULONG ulPartner_TimeOutMode;  /* �Զ�����ģʽ��0�������ڣ�1�������ڣ�*/
    BOOL_T bPartner_Collecting;   /* �Զ˶˿����ݽ���ʹ�ܱ�־ */
    BOOL_T bPartner_Distributing; /* �Զ˶˿����ݷ���ʹ�ܱ�־ */
    ULONG ulPartner_Key;          /* �Զ˶˿�����key */
    ULONG ulPartner_PortPri;      /* �Զ˶˿����ȼ� */
    ULONG ulPartner_PortNum;      /* �Զ˶˿ں� */
    ULONG ulPartner_SysPri;       /* �Զ�ϵͳ���ȼ� */
    BOOL_T bPartner_Syn;          /* �Զ˶˿�ͬ��״̬���Ƿ�ѡ��ɹ��� */
    UCHAR ucPartner_SysMac[6];    /* �Զ�ϵͳMAC */
}LACP_NEGO_INFO_S;

typedef struct tagTRUNK_NSR_GLOBAL_INFO
{
    ULONG ulTrunkNsrState;                  /* ��ǰTrunk Nsr״̬ */
    ULONG ulTrunkNsrTimeout;                /* Trunk Nsr ��ʱ */
    ULONG ulAddPortNum;                     /* NSR�����У��û���ӳ�Ա�˿���Ŀ*/
    ULONG ulRemovePortNum;                  /* NSR�����У��û��Ƴ���Ա�˿���Ŀ*/
    ULONG ulSuccessResumeLinkNum;           /* �ָ��ɹ���·���� */
    ULONG ulResumeWrongInfoNum;             /* ת����ָ���Ϣ���� */
    ULONG ulResumeWrongMacNum;              /* ת����ָ���̫mac���� */
    ULONG ulResumeLinkNotExistNum;          /* û�дӵײ��ȡ�� */
    ULONG ulSuccessSmoothLinkNum;           /* ƽ���ɵ���·���� */
    ULONG ulFailSmoothLinkNum;              /* ƽ��ʧ����·���� */
    ULONG ulFailSmoothWrongMacNum;          /* ��ָ���trunk��mac����trunk�κ�һ����Ա�˿ڵ�mac��ƽ��ʧ����·���� */
}TRUNK_NSR_GLOBAL_INFO_S;

typedef struct tagTRUNK_NSR_LINK_INFO
{
    ULONG  ulTrunkNsrFailReason;                /* NSRʧ��ԭ���¼ */
    UCHAR  ucNsrPPIFlag;                        /* NSR������PPI�·���־*/
    UCHAR  ucPad[3];
}TRUNK_NSR_LINK_INFO_S;

/* Trunkģ�������Ϣ���� */
enum enumTRUNKDEBUGTYPE
{
    TRUNK_DEBUG_ALL = 0,           /* ����ȫ��������Ϣ */
    TRUNK_DEBUG_LACPPKT,           /* ����LACP������Ϣ */
    TRUNK_DEBUG_OTHERPPKT,         /* �����������ĵ�����Ϣ */
    TRUNK_DEBUG_FSM                /* ����״̬����Ǩ������Ϣ */
};

/* LACP״̬���¼� */
enum enumLACPFSMEVENTTYPE
{
    LACP_UP = 0,
    LACP_DOWN, 
};

/* ��Ա�˿ڵ�ѡ��״̬ */
enum enumAggPortType
{
    LACP_UNSELECTED = 0,
    LACP_SELECTED,
    LACP_STANDBY,
};

/* �˿����� */
enum enumTrunkType
{
    TRUNK_ISTRUNK = 0,      /* TRUNK�ӿ�    */
    TRUNK_ISTRUNKPORT,      /* ��Ա�˿�     */
    TRUNK_IFTYPEERR,        /* �������Ͷ˿� */
    TRUNK_IFNULL,           /* �˿�Ϊ��     */
    TRUNK_INNERERR,         /* �˿��ڲ��쳣 */
};

typedef enum enumTcpipLacpWarning
{
    LACP_WARNING_NO = 0,
    LACP_WARNING_TIMEOUT = 1,  /*NP ̽�⵽*/     

    LACP_WARNING_NOTIFY_MAX,
}TCPIP_LACP_WARNING_E;
/* End of Added by wangtong207740, 2012/5/26 */

enum tagTrunkNsrPpiType
{
    PPI_TRUNK_NSR_GET_LINKINFO  ,                       /* �ӵײ��ȡ��Ϣ */
    PPI_TRUNK_NSR_LINK_SMOOTH_SUCCESS,                  /* ֪ͨת����·�ָ��ɹ�*/
    PPI_TRUNK_NSR_LINK_SMOOTH_FAIL,                     /* ֪ͨת������·�ָ�ʧ��*/
    PPI_TRUNK_NSR_PROCESS_COMPLETE,                     /* ��·�ָ����֮���·�֪ͨ������ */
    PPI_TRUNK_NSR_PROCESS_FAIL,                         /* ��·�ָ�ʧ��֪ͨ���� */
    PPI_TRUNK_NSR_ENABLE,                               /* ֪ͨת����ʹ��NSR���� */
    PPI_TRUNK_NSR_DISABLE,                              /* ֪ͨת����ȥʹ��NSR���� */
    PPI_TRUNK_NSR_MAX,
};

/* trunk�����û��ַ����Ժ��������ַ���ֵ */
#define TRUNK_PKT_USEROUT      0   /* ���û�ָ����Ա�˿ڷ��� */
#define TRUNK_PKT_DEFAULTOUT   1   /* ��VISPȱʡ�ַ����Է��� */
#define TRUNK_PKT_DISCARD      2   /* �������ģ����跢�� */


/* ����Trunk�ĳ�Ա�˿���ʵ�˿ڻ���ӳ��˿� */
#define TRUNK_PORT_REAL        0
#define TRUNK_PORT_VIRTUAL     1

#define   TRUNK_BACKUP_MODE_NORMAL        0  /*����ģʽ(Ĭ��)*/
#define   TRUNK_BACKUP_MODE_ONE_TO_ONE    1  /*1:1 ����ģʽ*/
#define   TRUNK_BACKUP_MODE_M_TO_N        2  /*M:N����ģʽ*/

#define   TRUNK_RECOVER_MODE_YES        0  /*�ָ�ģʽ*/
#define   TRUNK_RECOVER_MODE_NO         1  /*�ǻָ�ģʽ*/

#define   TRUNK_MIN_ACTIVE_NUMBER       1 /* M:Nģʽ��С����˿��� */
#define   TRUNK_MAX_ACTIVE_NUMBER       8 /* M:Nģʽ��󼤻�˿��� */

/* Add by shuxieliu00176784/baiweiqiang00177000, at 2011-06-30. �޸�ԭ��:  ��Ʒ���Ʋ������� */
#define   TRUNK_POLICY_DEFAULT_PROCESS          0 /* VISPĬ�ϴ���ʽ */
#define   TRUNK_POLICY_PROTMAC_NOTREFRESH       1 /* ����TRUNK�����Ż����ܲ���(TRUNK��Ա�˿�physical��ַ�����,TRUNK physical��ַ�뵱ǰUP�ĳ�Ա�˿�physical��ַһ�£� */


/* ����˵����
struct tagMBuf *pstMBuf         ����MBufָ��
USHORT usPid                    ��̫����Э���
ULONG ulIsVanPkt                ��̫�����Ƿ���VLAN����
ULONG ulUpPortNum               UP�ĳ�Ա�˿���
ULONG* pulUpPortIfIndex         UP�ĳ�Ա�˿���������ָ��
ULONG* pulIfIndex               ����������ַ��ӿ������������ĸ��˿ڷ���
*/
typedef ULONG (*TRUNK_DISTRIBUTE_HOOK_FUNC)(struct tagMBuf *pstMBuf, USHORT usPid, ULONG ulIsVanPkt, ULONG ulUpPortNum, ULONG* pulUpPortIfIndex, ULONG* pulIfIndex);

/* ��ȡphysical��ַ */
typedef ULONG (*TRUNK_GETMACADDRRESS_HOOK_FUNC)(ULONG ulTrunkId, UCHAR* pucMacAddr);
/* �ͷ�physical��ַ */
typedef VOID  (*TRUNK_FREEMACADDRRESS_HOOK_FUNC)(ULONG ulTrunkId, UCHAR* pucMacAddr);

typedef ULONG (*TRUNK_NSR_PPI_HOOK)(ULONG ulIfIndex, ULONG ulCmd, UCHAR *pucData);
    
/* api declare  */
/*******************************************************************************
*    Func Name: TCPIP_AddToTrunk
*  Description: ���Trunk��Ա�˿ڣ��й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ����ӵĳ�Ա�˿ڽӿ�����
*               ULONG ulTrunkId: Trunk ID��0��31��
*               USHORT usPri:    �˿����ȼ���ֵ����Ч��0Ϊ������ȼ���
*       Output: 
*       Return: VOS_OK��0��                  �ɹ�
*               VOS_ERR��1��                 ʧ��
*               TK_PARAM_ERR                 2������������Ϸ� 
*               TK_IF_NULL                   3�����ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_REPEAT_JOIN               4���˿��Ѿ�������Trunk 
*               TK_TRUNKID_NULL              5��Trunk ID�޶�ӦTrunk�ӿ�
*               TK_PORT_FULL                 6��Trunk���Ѿ���8����Ա�˿�
*               TK_PORT_ISNOT_FE             7���˿ڲ���FE��
*               TK_PORT_HAVE_IP              8���˿ھ���IP������ԣ����Ѿ������˵�ַ���Ѿ����õ�ַ�������ӿ�
*               TK_TRUNKCB_NULL              10��Trunk�ӿڵ�Trunk���ƿ�Ϊ��
*               TK_PORT_HAVE_PPPOE           11���˿��Ѿ�������PPPOE
*               TK_PORT_CFG_DHCP4R           12���˿���ʹ��dhcp relay
*               TK_TRUNKID_ERR               18��trunk id�Ƿ�
*               TK_PORT_HAVE_MULTIIP         19���˿��жಥip
*               TK_PORT_HAVE_IPV6            20���˿���ipv6��ַ
*               TK_TRUNK_IF_NULL             21��Trunk�ӿ�Ϊ��
*               TK_IPIF_NULL                 22���ӿڵ�ipif���ƿ�Ϊ��
*               TK_TRUNKCB_NOMEM             23������trunk cb���ƿ��ڴ�ʧ��
*               TK_PORTINFO_NOMEM            24������port info���ƿ��ڴ�ʧ��
*               TK_LACPNEGO_NOMEM            25������lacp nego���ƿ��ڴ�ʧ��
*               TK_LACPFSM_NOMEM             26������lacp fsm���ƿ��ڴ�ʧ��
*               TK_PORT_SETVLAN              29���˿��Ѿ�ʹ����VLAN     
*               TK_PORT_SETARPPROXY          30���˿�������ARP����
*               TK_NOT_REGISTER              31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_AddToTrunk(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

/*******************************************************************************
*    Func Name: TCPIP_AddVPortToTrunk
* Date Created: 2008-11-21
*       Author: luowentong105073
*  Description: ��ӳ��˿ڼ��뵽TRUNK(vispv1r7c03 l2if,TGWӦ�ó���)
*        Input: ULONG ulIfIndex:������Ķ˿�����
*               ULONG ulTrunkId:Ҫ�����trunkid
*               USHORT usPri:���ȼ�
*       Output: 
*       Return: TK_OK:�ɹ�/����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-21   luowentong105073        Create
*
*******************************************************************************/
extern ULONG  TCPIP_AddVPortToTrunk(ULONG ulIfIndex, ULONG ulTrunkId, USHORT usPri);

/*******************************************************************************
*    Func Name: TCPIP_DelFromTrunk
*  Description: ���˿ڴ�Trunk�ӿ��н�����й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: �ӿ�����
*       Output: 
*       Return: VOS_OK��0��                  �ɹ�
*               VOS_ERR��1��                 ʧ��
*               TK_IF_NULL                   3�����ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_IF_ISNOT_MEMBERSHIPPORT   9���ӿڲ��ǳ�Ա�˿�
*               TK_TRUNKID_NULL              5��Trunk ID�޶�ӦTrunk�ӿ�
*               TK_TRUNKCB_NULL              10���ӿڵ�Trunk���ƿ�Ϊ�� 
*               TK_TRUNKID_ERR               18��Trunk IDֵ�Ƿ�               
*               TK_IPIF_NULL                 22���ӿڵ�ipif���ƿ�Ϊ�� 
*               TK_PORTINFO_NULL             27��port info���ƿ�Ϊ��
*               TK_NO_PORT                   28��trunk��û�г�Ա�˿�
*               TK_NOT_REGISTER              31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_DelFromTrunk(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSonStat
*  Description: ��ȡ��Ա�˿�ͳ����Ϣ���й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ifnet�ӿ�����
*               PORT_STAT_INFO_S *pstPortStatInfo: ��ȡ��Ա�˿���Ϣָ��
*       Output: pstPortStatInfo:��Ա�˿�ͳ����Ϣ
*       Return: VOS_OK:�ɹ�
*               TK_PARAM_ERR:�������Ϸ�
*               TK_IF_NULL:ifnet�ӿ�ָ��Ϊ��
*               TK_IF_ISNOT_MEMBERSHIPPORT:�ӿڲ��ǳ�Ա�˿�
*               TK_TRUNKCB_NULL  10���ӿڵ�Trunk���ƿ�Ϊ��
*               TK_NOT_REGISTER  31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkSonStat(ULONG ulIfIndex, PORT_STAT_INFO_S * pstPortStatInfo);
/*******************************************************************************
*    Func Name: TCPIP_ClrTrunkSonStat
*  Description: �����Ա�˿���Ϣ���й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ��Ա�˿�ifnetָ��
*       Output: 
*       Return: VOS_OK:�ɹ�
*               TK_PARAM_ERR:�������Ϸ�
*               TK_IF_NULL:ifnet�ӿ�ָ��Ϊ��
*               TK_IF_ISNOT_MEMBERSHIPPORT:�ӿڲ��ǳ�Ա�˿�
*               TK_TRUNKCB_NULL  10���ӿڵ�Trunk���ƿ�Ϊ��
*               TK_NOT_REGISTER  31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_ClrTrunkSonStat(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkDebug
*  Description: ���õ��Կ���ѡ��й������ݻ��Ᵽ��
*        Input: ULONG ulSwitch: �������ͣ�0��������Ϣ��1��LACP���Ĵ�����Ϣ
*                               2���������Ĵ�����Ϣ��3��״̬����Ǩ��Ϣ���������Ƿ�ֵ��
*               ULONG ulValue: ����ֵ��0���رգ�1���򿪣������Ƿ���
*       Output: 
*       Return: VOS_OK��0��        �ɹ�
*               TK_PARAM_ERR��2��  ����������Ϸ�
*               TK_NOT_REGISTER  31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkDebug(ULONG ulSwitch, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkDebug
*  Description: ��ȡtrunk���Կ���״̬
*        Input: ULONG *pulLacpPktDbgSw: LACP���ĵ��Կ���
*               ULONG *pulOtherPktDbgSw: �������ĵ��Կ���
*               ULONG *pulFsmDbgSw: ״̬�����Կ���
*       Output: 
*       Return: VOS_OK ��ȡ�ɹ�
*               TK_PARAM_ERR ��������
*               TK_NOT_REGISTER  31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkDebug(ULONG *pulLacpPktDbgSw, ULONG *pulOtherPktDbgSw, ULONG *pulFsmDbgSw);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkInfo
*  Description: ��ѯTrunk�ӿڼ���������Ա�˿���Ϣ���й������ݻ��Ᵽ��
*        Input: ULONG ulTrunkId: ��ԱID
*               TRUNK_INFO_S * pstTrunkInfo: �������Trunk�ӿ���Ϣ�Ŀռ�ָ��
*       Output: TRUNK_INFO_S * pstTrunkInfo: ���Trunk�ӿ���Ϣ�����³�Ա�˿���Ϣ
*       Return: VOS_OK                  0 �ɹ�
*               TK_PARAM_ERR            2������������Ϸ�
*               TK_TRUNKID_NULL         5��Trunk ID�޶�Ӧ��Trunk�ӿ�
*               TK_TRUNKID_ERR          18��Trunk IDֵ�Ƿ�
*               TK_NOT_REGISTER         31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkInfo(ULONG ulTrunkId, TRUNK_INFO_S *  pstTrunkInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkIdByIf
*  Description: ���ݽӿ�������ȡTrunk ID���й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ����ifnet����
*               ULONG *pulTrunkId: ���������trunk ID�ŵĿռ�ָ��
*       Output: ULONG *pulTrunkId: �����trunk ID��
*       Return: VOS_OK��0��             �ɹ�
*               TK_PARAM_ERR��2��       ����������Ϸ�
*               TK_IF_NULL��3��         ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_TRUNKCB_NULL��10��   �ӿڵ�Trunk���ƿ�Ϊ��
*               TK_NOT_REGISTER         31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkIdByIf(ULONG ulIfIndex, ULONG *pulTrunkId);
/*******************************************************************************
*    Func Name: TCPIP_Lacp
*  Description: ʹ��/ȥʹ��LACP���й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ����ifnet�ӿ�����
*               ULONG ulValue:  ʹ��/ȥʹ�ܱ�ǣ�0��ȥʹ�ܣ�1��ʹ�ܣ�
*       Output: 
*       Return: VOS_OK��0��                  �ɹ�
*               TK_PARAM_ERR��2��            ����������Ϸ�
*               TK_IF_NULL��3��              ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_TRUNKID_NULL��5��         Trunk ID�޶�ӦTrunk�ӿ�
*               TK_TRUNKCB_NULL��10��        �ӿڵ�Trunk���ƿ�Ϊ��
*               TK_TRUNK_HAVE_PORT(14)       Trunk�����г�Ա�˿�
*               TK_IF_ISNOT_TRUNK(16)        �ӿڲ���Trunk�ӿ�
*               TK_HA_IS_SMOOTHING(15)       HA�����ֶ�������ƽ������ 
*               TK_NOT_REGISTER              31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_Lacp(ULONG ulIfIndex, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_SetLacpPeriodMode
* Description: ���ó�����/������ģʽ���й������ݻ��Ᵽ��
*       Input: ULONG ulIfIndex: ifnet�ӿ�����
*              ULONG ulValue:  ������/����������ֵ��0��������,1�������ڣ�
*      Output: 
*      Return: VOS_OK��0��                       �ɹ�
*              TK_PARAM_ERR��2��                 ����������Ϸ�
*              TK_IF_NULL��3��                   ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*              TK_IF_ISNOT_MEMBERSHIPPORT��9��   �ӿڲ��ǳ�Ա�˿�
*              TK_LACP_NEGOTBL_NULL��12��        �˿ڵ�LACPЭ����Ϣ��Ϊ��
*              TK_LACP_FSMTBL_NULL (13��         �˿ڵ�״̬����Ϣ��Ϊ��
*              TK_HA_IS_SMOOTHING(15)            HA�����ֶ�������ƽ������
*              TK_NOT_REGISTER                   31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetLacpPeriodMode(ULONG ulIfIndex, ULONG ulValue);
/*******************************************************************************
*    Func Name: TCPIP_GetLacpFsmInfo
*  Description:��ѯָ���˿ڵ�LACP״̬����Ϣ���й������ݻ��Ᵽ��
*        Input: ULONG ulIfIndex: ifnet�ӿ�ָ��
*               LACP_FSM_INFO_S *pstFsmInfo: (stay here for avoid HCC warning)
*       Output: LACP_FSM_INFO_S *pstFsmInfo: �������LACP״̬��Ϣ��Ľṹָ��
*       Return: VOS_OK��0��                       �ɹ�
*               TK_PARAM_ERR��2��                 ����������Ϸ�
*               TK_IF_NULL��3��                   ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_IF_ISNOT_MEMBERSHIPPORT��9��   �ӿڲ��ǳ�Ա�˿�
*               TK_LACP_FSMTBL_NULL (13��         �˿ڵ�״̬����Ϣ��Ϊ��
*               TK_TRUNKCB_NULL(10)               �ӿڵ�Trunk���ƿ�Ϊ��
*               TK_NOT_REGISTER                   31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetLacpFsmInfo(ULONG ulIfIndex, LACP_FSM_INFO_S * pstFsmInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetLacpNegoInfo
*  Description: ��ѯָ���˿ڵ�LACPЭ����Ϣ
*        Input: ULONG ulIfIndex: ifnet�ӿ�ָ��
*               LACP_NEGO_INFO_S *pstNegoInfo: �����LACPЭ����Ϣ
*       Output: 
*       Return: VOS_OK��0��                        �ɹ�
*               TK_PARAM_ERR��2��                  ����������Ϸ�
*               TK_IF_NULL��3��                    ���ݽӿ�������ȡ�ӿ�ָ��Ϊ��
*               TK_IF_ISNOT_MEMBERSHIPPORT��9��    �ӿڲ��ǳ�Ա�˿�
*               TK_LACP_NEGOTBL_NULL��12��         �˿ڵ�LACPЭ����Ϣ��Ϊ��
*               TK_TRUNKCB_NULL(10)                �ӿڵ�Trunk���ƿ�Ϊ��
*               TK_NOT_REGISTER                    31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetLacpNegoInfo(ULONG ulIfIndex, LACP_NEGO_INFO_S * pstNegoInfo);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkSysPri
*  Description: ��ȡTRUNKϵͳ���ȼ�
*        Input: USHORT *pusSysPri: �������ϵͳ���ȼ����ڴ�ָ��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-10    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkSysPri(USHORT *pusSysPri);

extern ULONG  TCPIP_GetTrunkSysPriById(ULONG ulTrunkId, USHORT *pusSysPri);
/*******************************************************************************
*    Func Name: TCPIP_TrunkDistributeHookRegister
*  Description: 
*        Input: TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc:ע��ķַ����Ժ���ָ�� 
*       Output: 
*       Return: TK_OK: ע��/��ע��ɹ�
*               TK_NOT_REGISTER  31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_TrunkDistributeHookRegister (TRUNK_DISTRIBUTE_HOOK_FUNC pfTrunkHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetMacAddressHook
*  Description: �û�ע���ȡϵͳmac��trunk mac�����亯��
*        Input: TRUNK_GETMACADDRRESS_HOOK_FUNC pfHookFunc: ����ָ��
*       Output: 
*       Return: TK_OK:  ע��ɹ�
*               TK_ERR: ע��ʧ��
*      Caution: ��Ʒʵ��ʱ�������physical��ַCopy��pucMacAddrָ����ڴ棬pucMacAddrָ����ڴ���VISP����
*               ���ڸ���Trunk�ӿڶ���ֱ����Զ����������Trunk��physical��ַ�Ƿ���ͬ����Ӱ�챨���շ���
*               �����ƷΪϵͳMAC�͸���Trunk�ӿڷֱ���䲻ͬ��physical��ַ����ô��ɾ��Trunk�ӿ�ʱҪע������ѷ����physical��ַ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncGetMacAddressHook(TRUNK_GETMACADDRRESS_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeMacAddressHook
*  Description: �û�ע���ͷ�TRUNK MAC�����亯��
*        Input: TRUNK_FREEMACADDRRESS_HOOK_FUNC pfHookFunc: ����ָ��
*       Output: 
*       Return: TK_OK:  ע��ɹ�
*               TK_ERR: ע��ʧ��
*      Caution: �ͷ�VISP��ȡ��physical��ַ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_RegFuncFreeMacAddressHook(TRUNK_FREEMACADDRRESS_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_JudgeTrunkIf
*  Description: ��ȡTrunk����
*        Input: ULONG ulIfIndex: ifnet�ӿ�����
*       Output: 
*       Return: TRUNK_ISTRUNK(0)       �ӿ���Trunk�ӿ�
*               TRUNK_ISTRUNKPORT(1)   �ӿ��ǳ�Ա�˿�
*               TRUNK_IFTYPEERR(2)     �ӿڲ����ڻ������������ͽӿ�
*               TRUNK_IFNULL(3),       �˿�Ϊ��
*               TRUNK_INNERERR(4),     �˿��ڲ��쳣
*               TK_NOT_REGISTER        31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_JudgeTrunkIf(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkHADbg
*  Description: ����trunk ha���Կ���
*        Input: ULONG ulDbg: ����״̬ 1-open;0-close
*       Output: 
*       Return: VOS_OK                 ���óɹ�
*               VOS_ERR                ����ʧ��
*               TK_NOT_REGISTER        31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkHADbg(ULONG ulDbg);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkHADbg
*  Description: ��ȡtrunk ha���Կ���
*        Input: ULONG* pulDbg: ���������ha���Կ���״̬
*       Output: 
*       Return: VOS_OK:     ��ȡ�ɹ�
*               VOS_ERR:    ��ȡʧ��(ָ�����Ϊ��)
*               TK_NOT_REGISTER        31��trunkģ��δע��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkHADbg(ULONG* pulDbg);
/*******************************************************************************
*    Func Name: TCPIP_SetTrunkBfdMode
*  Description: trunk���Ա�˿��ϴ�������bfd�Ựʱ��Ҫָ����Чģʽ��ֻ��������Чģʽ�ĻỰ�ſ���UP
*        Input: ULONG ulTrunkIfIndex: trunk�ӿ�����
*               ULONG ucValue: ��Чģʽ 0,trunk�ϵĵ���bfd�Ự��Ч;1-��Ա�˿��ϵĵ���bfd�Ự��Ч(Ĭ��trunk��Ч)
*       Output: 
*       Return: TK_OK: ���óɹ�
*               ����:  ����ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_SetTrunkBfdMode( ULONG ulTrunkIfIndex, UCHAR ucValue);
/*******************************************************************************
*    Func Name: TCPIP_GetTrunkBfdMode
*  Description: ��ȡtrunk���Ա�˿��Ͻ���bfd�Ự����Чģʽ
*        Input: ULONG ulTrunkIfIndex: trunk����
*               ULONG *pucValue: �������ֵ��ָ��
*       Output: 
*       Return: TK_OK: ��ȡ�ɹ�
*               ����:  ��ȡʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern ULONG  TCPIP_GetTrunkBfdMode( ULONG ulTrunkIfIndex, UCHAR* pucValue);
/*******************************************************************************
*    Func Name: TCPIP_ShowTrunkInfo
*  Description: ��ʾtrunk����Ϣ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID   TCPIP_ShowTrunkInfo(VOID);
/*******************************************************************************
*    Func Name: TCPIP_ShowTrunkStatistic
*  Description: ��ʾ��Ա�˿ڽӿ���trunkͳ����Ϣ
*        Input: CHAR * pName: �ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-3-8    LY(57500)     Creat the first version.
*
*******************************************************************************/
extern VOID   TCPIP_ShowTrunkStatistic(CHAR * pName);
extern ULONG TCPIP_SetTrunkGateValue(ULONG ulTrunkId,ULONG ulGateValue);
extern ULONG TCPIP_GetTrunkGateValue(ULONG ulTrunkId,ULONG *pulGateValue);

/*******************************************************************************
*    Func Name: TCPIP_NotifyLacpStatus
* Date Created: 2008-11-21
*       Author: luowentong105073
*  Description: �ӿڰ�״̬ͬ�������ذ壬������TGWӦ�ó���
*        Input: ULONG ulIfIndex:Ҫͬ���Ľӿ�����
*               ULONG ulStatus:Ҫͬ���Ľӿ�״̬ LACP_UP 0/LACP_DOWN 1
*       Output: 
*       Return: TK_OK: ��ȡ�ɹ�
*               ����:  ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-11-21   luowentong105073        Create
*
*******************************************************************************/
extern ULONG TCPIP_NotifyLacpStatus(ULONG ulIfIndex, ULONG ulStatus);


extern ULONG TCPIP_SetTrunkNegTimeoutWaring(ULONG ulTime);


extern ULONG TCPIP_GetTrunkNegTimeoutWaring(ULONG *pulTime);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkSysPri
* Date Created: 2009-5-11
*       Author: LY(57500)
*  Description: ����ϵͳ���ȼ�
*        Input: USHORT usSysPri: 0��65535��ֵԽС���ȼ�Խ��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-11    LY(57500)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkSysPri(USHORT usSysPri);


extern ULONG TCPIP_SetTrunkSysPriById(ULONG ulTrunkId, USHORT usSysPri);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkPortPri
* Date Created: 2009-5-11
*       Author: LY(57500)
*  Description: ����trunk�˿ڵ����ȼ���ֻ��lacpЭ�̵�trunk�˿ڲſ�����
*        Input: ULONG ulIfIndex: �˿�����
*               USHORT usPri: �˿����ȼ�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-5-11    LY(57500)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkPortPri(ULONG ulIfIndex, USHORT usPri);


extern ULONG TCPIP_GetTrunkPortPri(ULONG ulIfIndex, USHORT *pusPri);


extern ULONG TCPIP_SetTrunkBackupMode(ULONG ulTrunkId, ULONG ulMode);


extern ULONG TCPIP_GetTrunkBackupMode(ULONG ulTrunkId, ULONG *pulMode);


extern ULONG TCPIP_SetTrunkMasterPort(ULONG ulTrunkId,ULONG ulIfIndex);


extern ULONG TCPIP_GetTrunkMasterPort(ULONG ulTrunkId,ULONG *pulIfIndex);


extern ULONG TCPIP_SetTrunkActiveNum(ULONG ulTrunkId, ULONG ulActiveNum);


extern ULONG TCPIP_GetTrunkActiveNum(ULONG ulTrunkId, ULONG *pulActiveNum);


extern ULONG TCPIP_SetTrunkRecoverMode(ULONG ulTrunkId, ULONG ulMode);


extern ULONG TCPIP_GetTrunkRecoverMode(ULONG ulTrunkId, ULONG *pulMode);

typedef ULONG (* TrunkLacpChangeNotify)(ULONG ulIfIndex, ULONG ulOper);

extern ULONG TCPIP_RegFuncNotifyLacpChangeHook(TrunkLacpChangeNotify pfHookFunc);


extern VOID TCPIP_ShowTrunkPortInfo(CHAR *szIfName);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetLACPPortIDHook
* Date Created: 2010-06-22
*       Author: zengshaoyang62531
*  Description: �û�ע�ṳ�Ӻ���������������άֵ��ȡPort Id
*        Input: TRUNK_GETLACPPORTID_HOOK_FUNC pfHookFunc:��ע�ṳ�Ӻ���
*       Output: 
*       Return: VOS_OK
*      Caution: �˺��������ڼ���ʽ��ά�ӿ�ģʽ�µ��ã����򷵻ش���!
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-06-22   zengshaoyang62531       Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetLACPPortIDHook(TRUNK_GETLACPPORTID_HOOK_FUNC pfHookFunc);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkPortOriginalMac
* Date Created: 2011-06-27
*       Author: shuxieliu00176784/baiweiqiang00177000
*      Purpose: ��ȡTRUNK��Ա�˿ڵ�ԭʼphysical��ַ
*  Description: 
*        Input: ULONG ulIfIndex: ��Ա�˿�IFNET����
*               UCHAR* pucMac:   ��Ա�˿�ԭʼ��physical��ַ����֤���ȴ��ڵ���6�ֽ�
*       Output: UCHAR* pucMac:   ��Ա�˿�ԭʼ��physical��ַ
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-27   shuxieliu00176784       Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_GetTrunkPortOriginalMac(ULONG ulIfIndex, UCHAR* pucMac);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkProductProcPolicy
* Date Created: 2011-06-28
*       Author: shuxieliu00176784/baiweiqiang00177000
*      Purpose: ���ò�Ʒ�Ķ��Ʋ���
*  Description: 
*        Input: ULONG ulTrunkId:  TRUNK Id��
*               ULONG ulPolicy:   TRUNK��Ʒ�������
*                                 ȡֵ: TRUNK_POLICY_DEFAULT_PROCESS     0 VISPĬ�ϴ���ʽ 
*                                       TRUNK_POLICY_PROTMAC_NOTREFRESH  1 ����TRUNK�����Ż����ܲ���
*
*       Output: 
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*        Since: V2R3C05
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-06-27   shuxieliu00176784       Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_SetTrunkProductProcPolicy(ULONG ulTrunkId, ULONG ulPolicy);

extern ULONG TCPIP_NotifyTrunkLacp(TRUNK_LACP_NOTIFY_S *pstData);

/*******************************************************************************
*    Func Name: TCPIP_SetTrunkPartnerMacChangeDropSwitch
* Date Created: 2012-11-06
*       Author: luogaowei 61496
*      Purpose: ���öԶ�ϵͳMAC�仯�Ƿ񶪰��Ĳ��Կ���
*  Description: 
*        Input: ULONG ulSwitch:  ���öԶ�ϵͳMAC�仯��������(VRP_YES 1 :����  VRP_NO 0 :������)
*       Output: 
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-06  luogaowei 61496       Create the first version.(TD-RNC ����)
*  ��������:1���Զ˵�ϵͳMAC�����仯   && 2�����˴��ڷ�default ״̬  && 3�����˴���UP״̬
*  Ĭ�ϲ������������Դ���Э��ʱ�䳤��6�룬�����ɲ�Ʒ����������֤
*******************************************************************************/
extern ULONG TCPIP_SetTrunkPartnerMacChangeDropSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetTrunkPartnerMacChangeDropSwitch
* Date Created: 2012-11-06
*       Author: luogaowei 61496
*      Purpose: ��ȡ�Զ�ϵͳMAC�仯�Ƿ񶪰��Ŀ���
*  Description: 
*        Input: 
*       Output: ULONG *pulSwitch:  ���öԶ�ϵͳMAC�仯��������(VRP_YES 1 :����  VRP_NO 0 :������)
*       Return: VOS_OK           �ɹ�
*               ����             ʧ��
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-11-06  luogaowei 61496       Create the first version.(TD-RNC ����)
*  ��������:1���Զ˵�ϵͳMAC�����仯   && 2�����˴��ڷ�default ״̬  && 3�����˴���UP״̬
*  Ĭ�ϲ������������Դ���Э��ʱ�䳤��6�룬�����ɲ�Ʒ����������֤
*******************************************************************************/
extern ULONG TCPIP_GetTrunkPartnerMacChangeDropSwitch(ULONG *pulSwitch);

extern VOID TCPIP_NSR_TrunkSendMsg(ULONG ulMsgType, UCHAR *pucData, ULONG ulLength);


extern ULONG TCPIP_NSR_SetCheckTrunkNsrFinishTimer(ULONG ulTime);


extern ULONG TCPIP_NSR_TrunkPpiDownLoadHook(TRUNK_NSR_PPI_HOOK pstTrunkNspPpiHook);

extern ULONG TCPIP_NSR_GetCheckTrunkNsrFinishTimer(ULONG *pulTime);

extern ULONG TCPIP_NSR_GetTrunkNsrGobalInfo(TRUNK_NSR_GLOBAL_INFO_S *pstTrunkNsrGlobalInfo);
extern ULONG TCPIP_NSR_EnableTrunkNsr(UCHAR ucEnable);

extern ULONG TCPIP_NSR_GetTrunkNsrLinkInfo(CHAR *pIfname, TRUNK_NSR_LINK_INFO_S *pstTrunkNsrLinkInfo);

extern ULONG  TCPIP_SetDropNoLacpPacketSwitch(ULONG ulSwitch);

extern ULONG  TCPIP_GetDropNoLacpPacketSwitch(ULONG *pulSwitch);

ULONG TCPIP_SetTrunkSystemMac(UCHAR *pucMac);

ULONG TCPIP_GetTrunkSystemMac(UCHAR *pucMac);


extern ULONG TCPIP_SetTrunkIdSystemMac(ULONG ulTrunkId, UCHAR *pucMac);


extern ULONG TCPIP_GetTrunkIdSystemMac(ULONG ulTrunkId, UCHAR *pucMac);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_API_H_ */

