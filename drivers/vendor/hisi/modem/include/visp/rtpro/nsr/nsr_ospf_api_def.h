#ifndef NSR_OSPF_API_DEF_INCLUDED
#define NSR_OSPF_API_DEF_INCLUDED

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*NSR��Ϣ����/�ظ�����*/
#define NSR_MSG_SIGNAL_REQUEST    0
#define NSR_MSG_SIGNAL_RESPONSE   1

#define NSR_FILTER_PROC       0x01
#define NSR_FILTER_AREA       0x02
#define NSR_FILTER_ALL        0x03

/*��ѯnsr�б��ݵ�ospf������Ϣ���Ự��������*/
typedef struct nsr_ospf_entity_filter
{
    USHORT   usProcessId;                       /* ospfʵ���� */
    USHORT   usPad;                             
}NSR_OSPF_ENTITY_FILTER;

/*�Ự: ��ѯnsr�б��ݵ�ospf������Ϣ��*/
typedef struct nsr_ospf_entity_session
{
    VOID *pstNSROSPFEntity;                        /* ָ��ǰ��ѯ�� ospfʵ�� cb*/
    NSR_OSPF_ENTITY_FILTER stFilter;            /* �������� */
}NSR_OSPF_ENTITY_SESSION;

/*OSPF���̱���״̬��Ϣ*/
typedef struct nsr_ospf_backup_info_show
{
    UCHAR ucBackupOpt;
    UCHAR ucResult; 
    USHORT   usPad; 
}NSR_OSPF_BACKUP_INFO_SHOW;

/*OSPF���̱��ݻָ�״̬��Ϣ*/
typedef struct nsr_ospf_restore_info_show
{
    UCHAR ucRestoreOpt;
    UCHAR ucResult; 
    USHORT   usPad; 
}NSR_OSPF_RESTORE_INFO_SHOW;

/*OSPF����ƽ��״̬��Ϣ*/
typedef struct nsr_ospf_smooth_info_show
{
    UCHAR ucSmoothOpt;
    UCHAR ucResult; 
    USHORT   usPad;
}NSR_OSPF_SMOOTH_INFO_SHOW;

/*��ѯҵ��ͳ�ƣ��Ự��������*/
typedef struct nsr_business_stat_filter
{
    USHORT   usProcessId;                       /*ospfʵ���� */
    USHORT   usPad;             
}NSR_BUSINESS_STAT_FILTER;

/*�Ự:��ѯҵ��ͳ��*/
typedef struct nsr_business_stat_session
{
    VOID *pstNSROSPFEntity;                        /*ָ��ǰospfʵ��*/
    NSR_BUSINESS_STAT_FILTER   stFilter;           /*�������� */
}NSR_BUSINESS_STAT_SESSION;


typedef struct nsr_ospf_business_stat
{
    USHORT usProcessId;
    ULONG ulAreaCount;
    ULONG ulIfCount;
    ULONG ulNbrCount;
    ULONG ulLSACount;
    ULONG ulDownNbrCount;
    ULONG ulAttemptNbrCount;
    ULONG ulInitNbrCount;
    ULONG ul2WayNbrCount;
    ULONG ulExstartNbrCount;
    ULONG ulExchangeNbrCount;
    ULONG ulLoadingNbrCount;
    ULONG ulFullNbrCount;
    ULONG ulRouterLSACount;
    ULONG ulNetworkLSACount;
    ULONG ulSummsryNetLSACount;
    ULONG ulSummaryASBRLSACount;
    ULONG ulExternalLSACount;
    ULONG ulNSSALSACount;
    ULONG ulOpqLSACount;
}NSR_OSPF_BUSINESS_STAT;


/*��ѯ���ģ����ݵ�ospfʵ����Ϣ*/
typedef struct nsr_ospf_entity_repl_show
{
    USHORT   usProcessId;                       /*ospfʵ����*/
    UCHAR    ucOperStatus;
    CHAR     pad[1];
    ULONG    ulRouterIdRepl;                    /*���ݵ�OSPF router id*/
    ULONG    ulCryptoSeqNumRepl;                /*��ǰ��MD5���*/
    NSR_OSPF_BACKUP_INFO_SHOW stBackupInfo;     /*OSPF���̱�����Ϣ*/
    NSR_OSPF_RESTORE_INFO_SHOW stRestoreInfo;   /*OSPF���̱��ݻָ���Ϣ*/
    NSR_OSPF_SMOOTH_INFO_SHOW stSmoothInfo;     /*OSPF����ƽ����Ϣ*/
    NSR_OSPF_BUSINESS_STAT stBusinessStat;      /*��ʱ��Ա��ҵ��ͳ������*/
}NSR_OSPF_ENTITY_REPL_SHOW;

/*��ѯnsr�б��ݵ�IF������Ϣ���Ự��������*/
typedef struct nsr_ospf_if_filter
{
    USHORT   usProcessId;                       /*ospfʵ���� */
    USHORT   usPad;             
}NSR_OSPF_IF_FILTER;

/*�Ự:��ѯnsr�б��ݵ�ospf if����*/
typedef struct nsr_ospf_if_session
{
    VOID *pstNSROSPFEntity;                        /*ָ��ǰospfʵ��*/
    VOID *pstIfCB;
    NSR_OSPF_IF_FILTER   stFilter;              /*�������� */
}NSR_OSPF_IF_SESSION;

/*��ѯ���ģ����ݵĽӿ���Ϣ*/
typedef struct nsr_ospf_if_repl_show
{
    USHORT   usProcessId;                       /* ospfʵ���� */
    USHORT   usPad;
    ULONG    ulIfIpAddress;                     /* �ӿڵĵ�ַ, ��ospf�������±�ֵΪ ATG_INET_ADDRESS*/
    ULONG    ulAreaId;
    ULONG    ulIfStateRepl;                       /*�ӿ�״̬��״̬*/
    ULONG    ulDRRepl;                          /*�ӿ�ѡ�ٵ�DR  ��ospf�������±�ֵΪ QOPM_ID_LEN*/
    ULONG    ulBDRRepl;                         /*�ӿ�ѡ�ٵ�BDR ��ospf�������±�ֵΪ QOPM_ID_LEN*/
    ULONG    ulIfNetworkType;                  /*�ӿ���������*/
    UCHAR    ulOperStatus;
    CHAR     pad[3];
}NSR_OSPF_IF_REPL_SHOW;

/*��ѯnsr�б��ݵ�nbr��Ϣ���Ự��������*/
typedef struct nsr_ospf_nbr_filter
{
    USHORT   usProcessId;                       /* ospfʵ���� */
    USHORT   usPad;             
}NSR_OSPF_NBR_FILTER;

/*�Ự:��ѯnsr�б��ݵ�ospf nbr����*/
typedef struct nsr_ospf_nbr_session
{
    VOID *pstNSROSPFEntity;                        /* ָ��ǰospfʵ��*/
    VOID *pstNbrCB;
    NSR_OSPF_NBR_FILTER   stFilter;             /* �������� */
}NSR_OSPF_NBR_SESSION;

/*��ѯ���ģ����ݵ��ھ���Ϣ*/
typedef struct nsr_ospf_nbr_repl_show
{
    USHORT  usProcessId;                        /* ospfʵ���� */
    USHORT  usPad;
    ULONG   ulAreaId;
    LONG    lNbrStateRepl;                         /*�ھ�״̬��״̬*/
    ULONG   ulDRRepl;                           /*�ھ�ѡ�ٳ���DR*//*QOPM_ID_LEN*/
    ULONG   ulBDRRepl;                          /*�ھ�ѡ�ٳ���BDR*//*QOPM_ID_LEN*/
    ULONG   ulLastDDSeqNumRepl;                     /*����յ���DD���*/
    LONG    lPermanenceRepl;                    /*�ھӱ��(��̬/����)*/
    ULONG   ulRouterIdRepl;                     /*�ھӶ�Ӧ��Router ID*/
    ULONG   ulParentIfIpAddress;                /*���ӿڵĵ�ַ */
    ULONG   ulNbrIpAddress;                     /*�ھӵ�ַ */
    UCHAR   ucPriorityRepl;                     /*�ھӵ����ȼ�*/
    UCHAR   ucLastDDOptionsRepl;                /*����յ���DDѡ��*/
    UCHAR   ucLastDDFlagsRepl;                  /*����յ���DD��ʶ*/
    UCHAR   ucFriendStatusRepl;                 /*ͬ�ھӵ��ڽӹ�ϵ*/
    UCHAR   ucOperStatus;                       /*�ھӵĲ���״̬*/
    UCHAR   ucNbrHelperStateRepl;              /*�ھ�Helper FSM״̬*/
    CHAR    pad[2];
}NSR_OSPF_NBR_REPL_SHOW;

/*��ѯnsr�б��ݵ�������Ϣ���Ự��������*/
typedef struct nsr_ospf_area_filter
{
    USHORT  usFilterFlag;                          /*ȡֵ��Χ: NSR_FILTER_PROC       0x01
                                                             NSR_FILTER_AREA       0x02
                                                             NSR_FILTER_ALL        0x03*/
    USHORT  usProcessId;                        /* ospfʵ���� */
    ULONG   ulAreaId;
}NSR_OSPF_AREA_FILTER;

/*�Ự:��ѯnsr�б��ݵ�ospf nbr����*/
typedef struct nsr_ospf_area_session
{
    VOID *pstNSROSPFEntity;                        /* ָ��ǰospfʵ��*/
    VOID *pstAreaCB;
    NSR_OSPF_AREA_FILTER   stFilter;            /* �������� */
}NSR_OSPF_AREA_SESSION;

/*��ѯ���ģ����ݵ�������Ϣ*/
typedef struct nsr_ospf_area_repl_show
{
    USHORT  usProcessId;                        /* ָ��ǰospfʵ��*/
    USHORT  usPad;
    ULONG   ulAreaId;
}NSR_OSPF_AREA_REPL_SHOW;

/*��ѯnsr�б��ݵ�lsdb��Ϣ���Ự��������*/
typedef struct nsr_ospf_lsdb_filter
{
    USHORT  usProcessId;
    UCHAR   ucLSAType;   
/*
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11*/
    UCHAR   ucPad;
}NSR_OSPF_LSDB_FILTER;

/*�Ự:��ѯnsr�б��ݵ� lsdb ����*/
typedef struct nsr_ospf_lsdb_session
{
    VOID    *pstNSROSPFEntity;                     /* ָ��ǰospfʵ��*/
    VOID    *pstLSDBCB;
    VOID    *pstAreaCB;
    NSR_OSPF_LSDB_FILTER   stFilter;            /* �������� */
}NSR_OSPF_LSDB_SESSION;


/*LSA��ͷ����Ϣ*/
typedef struct tag_nsr_ospf_lsa_hdr_repl_show
{
    ULONG   ulRouterId;
    ULONG   ulAreaId;                           /* for type-5 LSA, this field is invalid */
    USHORT  usProcessId;
    USHORT  usLSAAge;                           /* �ϻ�ʱ�� */
    UCHAR   ucOptions;                          /* ��ѡ�� */
    UCHAR   ucLSAType;                          /* LSA ���� */
    USHORT  usLength;                           /* ����LSAͷ�����ڵ�LSA���� */
    ULONG   ulLinkId;                           /* ��·ID */
    ULONG   ulAdvRoute;                         /* ͨ��·����ID */
    ULONG   ulSeqNum;                           /* ���к� */
    ULONG   ulCheckSum;                         /* У��� */
}NSR_OSPF_LSA_HDR_REPL_SHOW_S;

/*NSR�ı�������*/
typedef struct nsr_state_info_show
{
    UCHAR ucNSRRole;                            /*NSR��ɫ,Ĭ��Ϊ��*/
    UCHAR ucSlaveBoardStatus;                   /*����״̬*/
    UCHAR ucChannelStatus;                      /*����ͨ���Ƿ�OK��Ĭ��ΪFalse*/
    BOOL_T bNSRInit;                            /*NSR�Ƿ��ʼ�� 0-δ��ʼ��  1-�ѳ�ʼ��*/
    BOOL_T bBatchFirstPkt;                      /*�Ƿ�Ϊ�������ݵ��װ�, 0--��, 1--��(ע��:�����������ͬʱ����)*/
    UCHAR ucNSRState;                           /*NSR״̬����״̬*/
    UCHAR ucNSRBackupState;
}NSR_STATE_INFO_SHOW;

/*NSR����ͳ������*/
#define NSR_PERFORMANCE_BATCH_MASTER          1
#define NSR_PERFORMANCE_BATCH_SLAVE           2
#define NSR_PERFORMANCE_RESTORE               3
#define NSR_PERFORMANCE_IF_NOTIFY             4
#define NSR_PERFORMANCE_TOP_RELEARN           5
#define NSR_PERFORMANCE_SWITCH                6
#define NSR_PERFORMANCE_TRUNK_NOTIFY          7
#define NSR_PERFORMANCE_MAX                   8

/*NSR����ͳ�����ݲ�ѯ�ӿ�*/
typedef struct nsr_performance_stat_show
{
    ULONG arrNSRPerformanceStat[NSR_PERFORMANCE_MAX];
}NSR_PERFORMANCE_STAT_SHOW;

/*NSR��Ϣ�շ�����*/
#define NSR_MSG_DIRECT_SEND     0
#define NSR_MSG_DIRECT_RECEIVE  1
#define NSR_MSG_DIRECT_MAX      2

/*NSR��Ϣͳ�Ʋ�ѯ�ӿ�*/
typedef struct nsr_msg_stat_show
{
    /*NSR����Ŀ�������Ϣͳ��*/
    ULONG ulBoardMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulChannleMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulSlaveBoardMsgStat[NSR_MSG_DIRECT_MAX];
    ULONG ulMasterBackupMsgStat[NSR_MSG_DIRECT_MAX][NSR_BACKUP_MAX];
    ULONG ulSlaveBackupMsgStat[NSR_MSG_DIRECT_MAX][NSR_BACKUP_MAX];
    ULONG ulRestoreMsgStat[NSR_MSG_DIRECT_MAX][NSR_RESTORE_MAX];
    ULONG ulSmoothMsgStat[NSR_MSG_DIRECT_MAX][NSR_SMOOTH_MAX];
    /*NSR����ı���������Ϣͳ��*/
    ULONG ulBackukDataStat[NSR_MSG_DIRECT_MAX];
    /*NSR�շ������п�����ͳ��*/
    ULONG ulTotalNSRControlMsg[NSR_MSG_DIRECT_MAX];
    /*NSR�շ������б���������Ϣͳ��*/
    ULONG ulTotalBackupDataMsg[NSR_MSG_DIRECT_MAX];
}NSR_MSG_STAT_SHOW;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
