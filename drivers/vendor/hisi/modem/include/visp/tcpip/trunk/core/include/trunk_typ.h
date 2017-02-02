/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_typ.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunkģ������ݽṹ����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_TYP_H_
#define _TRUNK_TYP_H_

#ifdef __cplusplus
extern "C"{
#endif

/* Trunk��Ϣ�� */
typedef struct tagTrunkInfoTbl
{
    ULONG ulIfIndex;                                 /* Trunk�ӿ����� */
    ULONG ulIsUsed;                                  /* �ñ����Ƿ���ʹ�ã�1��ʹ�ã�0��δʹ�� */
    ULONG ulPortNum;                                 /* ��Ա�˿����� */
    ULONG ulTrunkPortIfIndex[TRUNK_PORT_MAX_NUM];    /* ��Ա�˿���Ϣ�� */
    ULONG ulUpPortNum;                               /* ������·UP�ĳ�Ա�˿����� */
    ULONG ulTrunkUpPortIfIndex[TRUNK_PORT_MAX_NUM];  /* UP�ĳ�Ա�˿���Ϣ�� */
    ULONG ulEnableLacp;                              /* �Ƿ�ʹ��LACP��Ĭ��Ϊʹ�� */
    ULONG ulRefIfIndex;                              /* �ο��˿ڵĽӿ����� */
    UCHAR ucMacAddress[TRUNK_MACADDR_LEN];           /* Trunk�ӿ�physical��ַ */
    UCHAR ucBfdTrunkMode;                            /* trunk���Ա�˿��Ͻ�������bfd����Чģʽ,Ĭ��trunk���� */   
    UCHAR ucMacDynamic;                              /* Trunk physical��ַ��ȡģʽ�Ƿ�Ϊ��̬��ȡģʽ     */
    ULONG ulMacPortIndex;                            /* ��̬��ȡTrunk macʱ��ʹ��mac�ĳ�Ա�˿�����  */
    ULONG ulGateValue;                               /* Trunk��ֵ */
    ULONG ulPassive;                                 /* �������˻��Ǳ����� */
    UCHAR ucBackupMode;                              /* �˿ڱ���ģʽ,0,��ͨģʽ;1,1:1����ģʽ��2,M:N����ģʽ */ 
    UCHAR ucRecoverMode;                             /* �˿ڱ��ݵĻָ�ģʽ,0,�ָ�ģʽ;1,�ǻָ�ģʽ */
    USHORT usSysPri;                                 /* Trunkϵͳ���ȼ� */
    ULONG ulMasterIfIndex;                           /* �˿�1:1ģʽ�����õ����˿����� */
    ULONG ulActiveNum;                               /* �˿�M:Nģʽ�����õļ���˿��� */
    ULONG ulProductPolicy;                           /* ��Ʒ���Ƶ�TRUNK���� */
    UCHAR ucIsTrunkNeedKeepUp;                       /* Trunk��UP��Ա�˿ھ�DOWN��ʱ�Ƿ���ҪDOWN, 1-����DOWN��0-��DOWN(Ĭ��) */
    UCHAR ucPadding[3];                              /* �����ֶ� */
    ULONG ulLbCheckTimerId;                          /* ���ؼ�ⶨʱ�� */ 
    UCHAR ucTrunkIdSysMac[TRUNK_MACADDR_LEN];        /* ����TRUNK������ϵͳMAC*/
    UCHAR ucReserve[2];                              /* �����ֶ�*/
}TRUNK_INFO_TBL_S;

/* ����ͳ����Ϣ�� */
typedef struct tagTrunkPortPktStat
{
    ULONG ulOutSum;       /* ���͵ı������� */
    ULONG ulOutLacp;      /* ���͵�LACP������ */
    ULONG ulOutDrop;      /* ����ʱ�����ı����� */
    ULONG ulInSum;        /* ���յı������� */
    ULONG ulInLacp;       /* ���յ�LACP������ */
    ULONG ulInDrop;       /* ����ʱ�����ı����� */
    ULONG ulLacpExpired;  /* NP�ϱ���ʱͳ�� */
    ULONG ulLacpPPIPKT;   /* LACP�·�NP��͸������ͳ�� */
    /* Add end */
}TRUNK_PORT_PKT_STAT_S;


/* LACPЭ����Ϣ�� */
typedef struct tagLacpNego
{
    /* ������Ϣ */
    ULONG ulDefaulted;             /* �˿��Ƿ�Ϊdefaulted�˿� */
    UCHAR ucActorAdminState;       /* ���˶˿ڹ���״ֵ̬ */
    UCHAR ucActorOperState;        /* ���˶˿�����״ֵ̬ */
    USHORT usActorAdminKey;        /* ���˶˿ڹ���Key */
    USHORT usActorOperKey;         /* ���˶˿�����Key */
    USHORT usActorPortPri;         /* ���˶˿����ȼ� */
    USHORT usActorPortIndex;       /* ���˶˿ں� */

    /* �Զ���Ϣ */
    UCHAR ucPartnerAdminState;     /* �Զ˶˿ڹ���״ֵ̬ */
    UCHAR ucPartnerOperState;      /* �Զ˶˿�����״ֵ̬ */
    USHORT usPartnerAdminKey;      /* �Զ˶˿ڹ���KEY */
    USHORT usPartnerOperKey;       /* �Զ˶˿�����Key */
    USHORT usPartnerAdminPortPri;  /* �Զ˶˿ڹ������ȼ� */
    USHORT usPartnerOperPortPri;   /* �Զ˶˿��������ȼ� */
    USHORT usPartnerAdminPortIndex; /* �Զ˶˿ڹ���˿ں� */
    USHORT usPartnerOperPortIndex;  /* �Զ˶˿������˿ں� */
    USHORT usPartnerAdminSysPri;   /* �Զ�ϵͳ�������ȼ� */
    USHORT usPartnerOperSysPri;    /* �Զ�ϵͳ�������ȼ� */
    UCHAR ucPartnerAdminSysMac[6]; /* �Զ�ϵͳ����physical��ַ */
    UCHAR ucPartnerOperSysMac[6];  /* �Զ�ϵͳ����physical��ַ */
    ULONG ulRemoteDefaulted;        /* �Զ��Ƿ����default״̬ */
}LACP_NEGO_S;

/* ״̬��״̬ */
typedef struct tagLacpFsm
{
    BOOL_T bEnter;       /* �Ƿ��ܹ�����״̬�� FALSE��ʾ�˳�״̬�� */
    UCHAR  ucState;      /* ״̬����ǰ��״̬ */
    UCHAR ucPadding;     /* �����ֶ� */
}LACP_FSM_S;

/* �߼���ʱ����Ϣ */
typedef struct tagLacpTimers
{
    BOOL_T bActive;                 /*��ʱ���Ƿ���*/
    USHORT usValue;
}LACP_TIMERS_S;

/* LACPЭ��״̬����Ϣ�� */
typedef struct tagLacpPortFsm
{
    BOOL_T bRXBEGIN;                /* RX״̬����ʼ����־ */
    BOOL_T bPTXBEGIN;               /* PTX״̬����ʼ����־ */
    BOOL_T bMUXBEGIN;               /* MUX״̬����ʼ����־ */

    BOOL_T bNTT;                    /* NTT��־ */
    BOOL_T bPortEnable;             /* �˿�Enable/Disable�¼����� */    
    BOOL_T bLacpOperEnabled;        /* TURE���˿�ȫ˫�� */
    BOOL_T bReady;                  /* �˿�Ready_N��λ��ʾ�ö˿ڿ���Attach�� */
    BOOL_T bPortMoved;              /* DOWN�˿����������Ϣ�������˿��յ�����λ */
    USHORT usSelected;              /* �˿�Selected״̬��־ */
    USHORT usTxSendCount;           /* Tx״̬����1s�ڷ��ͱ��ĵĴ��� */

    /*����ΪLACP����ʱ���ĵ�ǰ״̬*/
    LACP_TIMERS_S stPeriodicTimer;  /* short_periodic_timer��ʱ�� */
    LACP_TIMERS_S stCurWhileTimer;  /* CurrentWhileTimer��ʱ�� */

    /* ����ΪLACP��״̬���ĵ�ǰ״̬ */
    LACP_FSM_S stRx;                /* ����״̬�� */
    LACP_FSM_S stPtx;               /* �����Է���״̬�� */
    LACP_FSM_S stMux;               /* MUX״̬�� */
}LACP_PORT_FSM_S;


#define WARN_PORT_DUPLEX  0x1
#define WARN_PORT_SPEED   0x2

/* λ����/���/�Ƿ������жϺ� */
#define BITS_FLAG_SET(t,f)    ((t) |= (f))
#define BITS_FLAG_CLR(t,f)    ((t) &= ~(f))
#define BITS_FLAG_ISSET(t,f)  (((t) & (f)) ? 1 : 0)

#define LACP_UNDOWNLOAD 0
#define LACP_DOWNLOAD   1

/* ��Ա�˿ڿ��ƿ� */
typedef struct tagTrunkPortInfo
{
    ULONG  ulIfIndex;                          /* �˿ڵĽӿ����� */
    ULONG  ulLacpStatus;                       /* �˿�LACPЭ��״̬��0��DOWN��1��UP */
    LACP_NEGO_S* pstLacpNego;                  /* LACPЭ����Ϣ��ָ�� */
    LACP_PORT_FSM_S* pstLacpPortFsm;           /* LACP״̬����Ϣ��ָ�� */
    TRUNK_PORT_PKT_STAT_S stPortPktStat;       /* ��Ա�˿ڱ���ͳ����Ϣ */
    UCHAR  ucOldMacAddress[6];                 /* ��Ա�˿ڼ���Trunkǰ��physical��ַ */
    UCHAR  ucBakMacAddress[6];              /* ���������Ա�˿ڵ�physical��ַ����������һ�� */
    UCHAR  ucVirtualAdd;                       /* ��ʵ�˿ڻ���ӳ��˿� */
    UCHAR  ucNoWarningFlag;                    /* ������Ϊ1ʱ,����Ա�˿ڴ�Trunk���Ƴ�ʱ�����и澯 */
    USHORT usNoLacpPortKey;                    /* �ֹ��󶨷�ʽ�¼�¼�˿ڵ����ܣ���֧������/˫��ģʽ�ȱ仯 */
    ULONG  ulNegTimeCnt;                       /* �״�Э��δͨ����ʱ */ 
    ULONG  ulPortWarnFlag;                     /* ����澯״̬��¼: WARN_PORT_DUPLEX(0x1) ��ͨ��˫��ģʽ����ȷ�澯, 
                                                                    WARN_PORT_SPEED (0x2) ��ͨ�����ʲ�һ�¸澯 */
    USHORT usPortPri;                          /* ��¼�˿����ȼ� */
    USHORT usPortIndex;                        /* ��¼�˿ں� */

    ULONG  ulNeedResendArpFlag;
    ULONG  ulDownReason;                       /* LACPЭ��down ԭ��ID */
    ULONG  ulLacpLinkMode;                      /*Lacp�շ�ģʽ 1���������շ���0���������շ�*/
#if (TCPIP_NSR == VRP_YES)    
    ULONG  ulTrunkNsrFailReason;                /* NSRʧ��ԭ���¼ */
    USHORT usLacpNsrCurrentMode;                /* ��¼��·��ǰ�ָ�״̬ */
    UCHAR  ucNsrPPIFlag;                        /* NSR������PPI�·���־*/
    UCHAR  ucPad[1];
#endif
}TRUNK_PORT_INFO_S;

/* Trunk���ƿ� */
typedef struct tagTrunkBasicInfo
{
    ULONG ulType;                             /* �ӿ����ͣ�0��Trunk�ӿڣ�1����Ա�˿� */
    ULONG ulTrunkId;                          /* Trunk ID��0��31�� */
    TRUNK_PORT_INFO_S* pstTrunkPortInfo;      /* ��Ա�˿ڿ��ƿ飬����Trunk�ӿ���˵����ָ��Ϊ�� */

    ULONG ulTrunk1agMepCnt;  /* Trunk���ϵ�MEP��������Ա�˿��ϸü���������
                                ��Ϊ��Ա�˿��ϵĶಥ�·���������MEP�������������ﲻ��Ҫ��������
                                ����TRUNK���ϵĶಥ�·��������ܲ�����MEP���� */
}TRUNK_BASIC_INFO_S;

#pragma    pack( 1 )

/* LACP�����ײ��ṹ */
typedef struct tagLacpPdu
{
    UCHAR  ucSubType;                  /* ����Э����LACP��Э��� */
    UCHAR  ucVersion;                  /* Э��汾�� */
    UCHAR  ucActorType;                /* ָʾΪActor���� */
    UCHAR  ucActorInfoLen;             /* Actor��Ϣ�ĳ��� */
    USHORT usActorSysPriority;         /* Actor��ϵͳ���ȼ� */
    UCHAR  ucActorSysMac[6];           /* Actor��ϵͳMAC */
    USHORT usActorKey;                 /* Actor�Ķ˿ڲ���Key */
    USHORT usActorPortPriority;        /* Actor�Ķ˿����ȼ� */
    USHORT usActorPortIndex;           /* Actor�Ķ˿ں� */
    UCHAR  ucActorPortState;           /* Actor�Ķ˿�LACP״̬ */
    UCHAR  ucReserved1[3];             /* ���� */
    UCHAR  ucPartnerType;              /* ָʾΪpartner������ */
    UCHAR  ucPartnerInfoLen;           /* partner��Ϣ�ĳ��� */
    USHORT usPartnerSysPriority;       /* Partner��ϵͳ���ȼ� */
    UCHAR  ucPartnerSysMac[6];         /* Partner��ϵͳMAC */
    USHORT usPartnerKey;               /* Partner�Ķ˿ڲ���Key */
    USHORT usPartnerPortPriority;      /* Partner�Ķ˿����ȼ� */
    USHORT usPartnerPortIndex;         /* Partner�Ķ˿ں� */
    UCHAR  ucPartnerPortState;         /* Partner�Ķ˿�LACP״̬ */
    UCHAR  ucReserved2[3];             /* ���� */
    UCHAR  ucCollectorType;            /* ָʾΪcollector���� */
    UCHAR  ucCollectorLen;             /* collector��Ϣ�ĳ��� */
    USHORT usMaxCollectDelay;          /* ����ռ��ӳ�,״̬����û��ʹ��������� */
    UCHAR  ucReserved3[12];            /* ���� */
    UCHAR  ucTerminatorType;           /* ָʾΪterminator���� */
    UCHAR  ucTerminatorLen;            /* terminator��Ϣ�ĳ��� */
    UCHAR  ucReserved4[50];            /* ���� */
} LACP_PDU_S;

#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* Trunkģ����Ϣ */
typedef struct tagTrunkModInfo
{
    ULONG ulMID_Trunk;  /* Trunkģ��ID */
    ULONG ulQUE_LACP;   /* LACP���Ķ���ID */
}TRUNK_MOD_INFO_S;

/* Shell��Coreע��Ļص������� */
typedef struct tagTrunkShellCallbackSet
{
    /* ������Ϣ������� */
    VOID (*pfTRUNK_DebugOutString) (CHAR * szStr);

    /* �������к��� */
    ULONG (*pfTRUNK_CreateQueue)(ULONG ulQueID,ULONG ulGetCntPerTimes,
            ULONG (*TRUNK_QueDealPacketFunc)(MBUF_S *),
            ULONG (*TRUNK_QueIsDropThisPacketFunc)(MBUF_S *,ULONG,CHAR*),
            ULONG ulMaxLen);

    /* ������к��� */
    ULONG (*pfTRUNK_ActiveQueue)(ULONG ulQueID);

    /* ����к��� */
    ULONG (*pfTRUNK_EnQueue)(MBUF_S *);

    /* �������ĺ��� */
    ULONG (*pfTRUNK_DropQueue)(MBUF_S *);

    /* �ͷŶ�����ָ�����ͱ��ĵĺ��� */
    VOID (*pfTRUNK_FreePacketInQueue)(ULONG ulQueID,ULONG ulCmd,CHAR* pData);

    /* �պ��� */
    ULONG (*pfTRUNK_DoNothing)(MBUF_S *);
    
}TRUNK_SHELL_CALLBACK_SET_S;


/* LACP״̬��������ݽṹ */
/* ��״̬��Ǩ��״̬�� */
enum enumLacpFsm
{
    LACP_FSM_RX = 0,        /* RX״̬�� */
    LACP_FSM_PTX,           /* PTX״̬�� */
    LACP_FSM_MUX,           /* MUX״̬�� */
        
    LACP_FSM_END           
};

/* ����״̬���ĸ�״̬ */
enum enumLacpFsmRx
{
    LACP_RX_NOSTATE = 0,            /* 0 ״̬����״̬ */
    LACP_RX_CURRENT = 1,            /* 1 CURRENT״̬ */
    LACP_RX_EXPIRED,                /* 2 EXPIRED״̬ */
    LACP_RX_DEFAULT,                /* 3 DEFAULT״̬ */
    LACP_RX_INIT,                   /* 4 INITLIZE״̬*/
    LACP_RX_LACP_DISABLED,          /* 5 LACP_DISABLED״̬ */
    LACP_RX_PORT_DISABLED           /* 6 PORT_DISABLED״̬*/
};

/* ���ڷ���״̬���ĸ�״̬ */
enum enumLacpFsmPtx
{
    LACP_PTX_NOSTATE = 0,           /* ״̬����״̬ */
    LACP_PTX_NO_PERIODIC = 1,       /* NO_PERIODIC״̬*/
    LACP_PTX_FAST_PERIODIC,         /* FAST_PERIODIC״̬ */
    LACP_PTX_SLOW_PERIODIC,         /* SLOW_PERIODIC״̬ */
    LACP_PTX_PERIODIC_TX            /* PERIODIC_TX״̬ */
};

/* MUX״̬���ĸ�״̬ */
enum enumLacpFsmMux
{
    LACP_MUX_NOSTATE = 0,       /* ״̬����״̬ */
    LACP_MUX_DETACHED = 1,      /* DETACHED״̬*/
    LACP_MUX_WAITING,           /* WAITING״̬ */
    LACP_MUX_ATTACHED,          /* ATTACHED״̬ */
    LACP_MUX_COLLECTING,        /*COLLECTING״̬*/
    LACP_MUX_DISTRIBUTING,      /*DISTRIBUTING״̬*/
    LACP_MUX_DISTRICOLLECT      /* DISTRIBUTING_COLLECTING״̬ */
};

/* ״̬��״̬��Ǩ��ԭ�� */
enum enumLacpSti
{
    LACP_BEGIN_FALSE =1,            /* �ǳ�ʼ��״̬*/
    LACP_BEGIN_TRUE,                /* ��ʼ��*/
    LACP_UCT,                       /* ������ת�� */
    LACP_PORTMOVED_TRUE,            /* �˿�ת��*/
    LACP_PORTMOVED_FALSE,           /* �˿�δת��*/
    LACP_PORT_ENABLED_TRUE,         /* �˿ڿ���*/
    LACP_PORT_ENABLED_FALSE,        /* �˿ڲ�����*/
    LACP_ENABLED_TRUE,              /* �˿�ʹ��LACP*/
    LACP_ENABLED_FALSE,             /* �˿ڹر�LACP*/
    LACP_PDU_INDICATE,              /*�յ�LACPDU*/
    LACP_CURRENTTIMER_EXPIRED,      /*CURRENT��ʱ����ʱ*/
    LACP_PASSIVE,                   /*˫������passiveģʽ*/    
    LACP_PERIOTIMER_EXPIRED,        /* ���ڶ�ʱ����ʱ*/
    LACP_LONGTIMEOUT,               /* LACP��Ϣ����ʱ*/
    LACP_SHORTTIMEOUT,              /* LACP��Ϣ�̳�ʱ*/
    LACP_PORT_SELECTED,             /* Selected����ΪSELECTED*/
    LACP_PORT_UNSELECTED,           /* Selected����ΪUNSELECTED*/
    LACP_PORT_STANDBY,              /* Selected����ΪSTANDBY*/
    LACP_READY,                     /* READYΪ��*/
    LACP_ACTOR_INSYNC,              /* ����Э����Ϣͬ��*/
    LACP_ACTOR_OUTSYNC,             /* ����Э����Ϣʧ��*/
    LACP_PARTNER_INSYNC,            /* �Զ�Э����Ϣͬ��*/
    LACP_PARTNER_OUTSYNC,           /* �Զ�Э����Ϣʧ��*/
    LACP_ACTORCHURNTIMER_EXPIRED,   /* ACTORCHURN��ʱ����ʱ*/
    LACP_PARTNERCHURNTIMER_EXPIRED, /* PARTNERCHURN��ʱ����ʱ*/
    LACP_NTT_TRUE,                  /* ��Ҫ����LACPDU*/
};

/* ��Ա�˿ڵ�״̬ */
enum enumPortLinkStatus
{
    LACP_PORT_DOWN = 0,            /* lacp status �˿�DOWN */
    LACP_PORT_UP = 1,              /* lacp status �˿�UP */
};

/* ����Ϊ״̬��Ǩ�Ƶ����ݽṹ���� */
typedef struct tagLacpFsmTran
{
    UCHAR ucStartState;       /* ��ʼ״̬,ö��ֵ,�μ���ض��� */
    UCHAR ucTranCondition;     /* ��������,ö��ֵ,�μ���ض��� */
    UCHAR ucEndState;          /* ��ֹ״̬,ö��ֵ,�μ���ض��� */
}LACP_FSMTRAN_S;

/* End of LACP״̬��������ݽṹ */

/* LACP���յ��ⲿ�¼� */
enum enumLACPEVENTTYPE
{
    LACP_EVENT_UP = 0,
    LACP_EVENT_DOWN,  
    LACP_EVENT_INIT,   
    LACP_EVENT_LEAVE
};

/* ѡ���߼��еĴ�ѡ�˿���Ϣ */
typedef struct tagTrunkLacpSelectPortInfo
{ 
    IFNET_S *pIf;         /* ��Ա�˿�IFNETָ�� */
    LACP_NEGO_S * pstLacpNego;    /* ��Ա�˿ڿ��ƿ� */
    LACP_PORT_FSM_S *pstLacpPortFsm; /* ״̬����Ϣ��ָ�� */
}TRUNK_LACP_SELECT_PORT_INFO_S;

/* �ֹ�trunk��ѡ���߼��еĴ�ѡ�˿���Ϣ */
typedef struct tagTrunkNoLacpSelectPortInfo
{ 
    IFNET_S *pIf;                       /* ��Ա�˿�IFNETָ�� */
    TRUNK_PORT_INFO_S * pstPortInfo;    /* ��Ա�˿ڿ��ƿ� */
}TRUNK_NOLACP_SELECT_PORT_INFO_S;

/* SGSN���� BC3D02743 20100224: Ϊ֧�ָ澯�������������ݽṹ����ѡ���߼�����ʱ��¼��Ҫ��Ϣ����ֹΪ�澯�ظ����� */
typedef struct tagTrunkWarnPortInfo
{ 
    IFNET_S *pIf;         /* ��Ա�˿�IFNETָ�� */
    TRUNK_PORT_INFO_S * pstPortInfo;    /* ��Ա�˿ڿ��ƿ� */        
    ULONG    ulIsHalfDuplex;
    ULONG    ulPortSpeedKey;
}TRUNK_WARN_SELECT_PORT_INFO_S;

/* ѡ���߼��еĴ�ѡM:N�˿���Ϣ */
typedef struct tagTrunkMtoNSelectPortInfo
{ 
    ULONG  ulIndex; /*�˿�����*/
    USHORT usPortNumber;
    USHORT usPortPri;
    ULONG  ulRemoteDefault;         /* �Զ��Ƿ���Defaulted״̬ */
}TRUNK_LACP_MTON_PORT_INFO_S;

/* LACP״̬�ֶε�activityλ��ȡֵ */
enum enumLacpStateActivity
{
    LACP_State_Passive = 0,
    LACP_State_Active,
};

/* LACP״̬�ֶε�TimeOutλ��ȡֵ */
enum enumLacpStateTimeOut
{
    LACP_State_LongTimeOut = 0,
    LACP_State_ShortTimeOut,
};

typedef ULONG (*TRUNK_VLANCHECK_HOOK_FUNC)(IFNET_S *pIfnet);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_TYP_H_ */
