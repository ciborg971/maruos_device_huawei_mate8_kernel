/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_api.h
*
*  Project Code: VISPV100R007
*   Module Name: �û�APIͷ�ļ�
*  Date Created: 2008-04-08
*        Author: zengshaoyang62531
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _ICMP4_API_H_
#define _ICMP4_API_H_

#ifdef __cplusplus
extern  "C"{
#endif /* __cplusplus */

#define     ICMP_MAXTYPE              19

/*����ping allow listʱ�Ĳ�������*/
#define ICMP_PINGALLOWLIST_ADD          0
#define ICMP_PINGALLOWLIST_DELSINGLE    1
#define ICMP_PINGALLOWLIST_DELALL       2

#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH            47              /* �ӿ������� */
#endif

#define     ICMP_ECHOREPLY            0     /* echo reply */

#define     ICMP_UNREACH              3     /* Ŀ�Ĳ��ɴ� dest unreachable, codes: */
#define     ICMP_UNREACH_NET          0     /* ���粻�ɴ� bad net */
#define     ICMP_UNREACH_HOST         1     /* �������ɴ� bad host */
#define     ICMP_UNREACH_PROTOCOL     2     /* Э�鲻�ɴ� bad protocol */
#define     ICMP_UNREACH_PORT         3     /* �˿ڲ��ɴ� bad port */
#define     ICMP_UNREACH_NEEDFRAG     4     /* ��Ҫ���з�Ƭ�������˲���Ƭ���� IP_DF caused drop */
#define     ICMP_UNREACH_SRCFAIL      5     /* Դվѡ·ʧ�� src route failed */
#define     ICMP_UNREACH_NET_UNKNOWN  6     /* Ŀ�����粻��ʶ unknown net */
#define     ICMP_UNREACH_HOST_UNKNOWN 7     /* Ŀ����������ʶ unknown host */
#define     ICMP_UNREACH_ISOLATED     8     /* Դ���������� src host isolated */
#define     ICMP_UNREACH_NET_PROHIB   9     /* Ŀ�����类ǿ�ƽ�ֹ prohibited access */
#define     ICMP_UNREACH_HOST_PROHIB  10    /* Ŀ��������ǿ�ƽ�ֹ ditto */
#define     ICMP_UNREACH_TOSNET       11    /* ���ڷ���������tos�����粻�ɴ� bad tos for net */
#define     ICMP_UNREACH_TOSHOST      12    /* ���ڷ���������tos���������ɴ� bad tos for host */

#define     ICMP_SOURCEQUENCH         4     /* Դ�˱��رգ����Ķ�ʧ packet lost, slow down */

#define     ICMP_REDIRECT             5     /* �ض��� shorter route, codes: */
#define     ICMP_REDIRECT_NET         0     /* �������ض��� for network */
#define     ICMP_REDIRECT_HOST        1     /* �������ض��� for host */
#define     ICMP_REDIRECT_TOSNET      2     /* �Է������ͺ������ض��� for tos and net */
#define     ICMP_REDIRECT_TOSHOST     3     /* �Է������ͺ������ض��� for tos and host */

#define     ICMP_ECHO                 8     /* ������� echo service */
#define     ICMP_ROUTERADVERT         9     /* ·����ͨ�� router advertisement */
#define     ICMP_ROUTERSOLICIT        10    /* ·�������� router solicitation */

#define     ICMP_TIMXCEED             11    /* ��ʱ time exceeded, code: */
#define     ICMP_TIMXCEED_INTRANS     0     /* �����ڼ�����ʱ��Ϊ�� ttl==0 in transit */
#define     ICMP_TIMXCEED_REASS       1     /* �����ݱ���װ�ڼ�����ʱ��Ϊ�� ttl==0 in reass */

#define     ICMP_PARAMPROB            12    /* ����IP�ײ� ip header bad */
#define     ICMP_PARAMPROB_OPTABSENT  1     /* ȱ�ٱ����ѡ�� req. opt. absent */
#define     ICMP_BAD_IPHEAD           0     /* ����IP�ײ� bad ip head */

#define     ICMP_TSTAMP               13    /* ʱ������� timestamp request */
#define     ICMP_TSTAMPREPLY          14    /* ʱ���Ӧ�� timestamp reply */
#define     ICMP_IREQ                 15    /* ��Ϣ���� information request */
#define     ICMP_IREQREPLY            16    /* ��ϢӦ�� information reply */
#define     ICMP_MASKREQ              17    /* ��ַ�������� address mask request */
#define     ICMP_MASKREPLY            18    /* ��ַ����Ӧ�� address mask reply */
#define     ICMP_TOTALMSGS            19    /* ����ICMP���� total icmp messages,added by 8011 maye BYDD06214 */


#define     ICMP_MAXCODE              15


/* ICMP����ĵķ�������ֵ�궨�� */
#define ICMP_ATTACKGUARD_SWITCH_ALL            0xffffffff
#define ICMP_ATTACKGUARD_SWITCH_UNREACH        0x01
#define ICMP_ATTACKGUARD_SWITCH_REDIRECT       0x02
#define ICMP_ATTACKGUARD_SWITCH_TIMXCEED       0x04
#define ICMP_ATTACKGUARD_SWITCH_MASKREP        0x08
#define ICMP_ATTACKGUARD_SWITCH_TSREP          0x10
#define ICMP_ATTACKGUARD_SWITCH_PARAMPROB      0x20
#define ICMP_ATTACKGUARD_SWITCH_SRCADDRANY     0x40
#define ICMP_ATTACKGUARD_SWITCH_DSTBCASTORMCAST   0x80

typedef enum tagICMP_ERR
{
    ICMP_PINGALLOWLIST_OK = 0,
    ICMP_PINGALLOWLIST_LISTEMPTY,       /*ping allow listΪ��*/
    ICMP_PINGALLOWLIST_LISTFULL,        /*ping allow list����*/
    ICMP_DEBUGFLAG_ERR,                 /*icmpģ����Կ�������ֵ�Ƿ�*/
    ICMP_NULL_POINTER,                  /*ָ��Ϊ��*/
    ICMP_COMP_NULL,                     /*ICMP���Ϊ��*/
    IFNET_COMP_NULL,                    /*ifnet������Ϊ��*/
    ICMP_IFNET_NULL,                    /*ifnetָ��Ϊ��*/
    ICMP_PINGALLOWLIST_INVALIDPARAM,    /*������Ч*/
    ICMP_PINGALLOWLIST_ADDREXIST,       /*��ַ�Ѿ�����*/
    ICMP_PINGALLOWLIST_ADDRNOTEXIST,    /*��ַ������*/
    ICMP_PINGALLOWLIST_MEMERR,          /*�ڴ����*/
    ICMP_HA_IS_SMOOTHING,               /*����ƽ������*/
    ICMP_IS_L2PORT,                     /* �����Ŀ��ӿ���һ������˿� */
    ICMP_FLOWSTAT_WRONG_INPUT,          /* 14 Input parameters for icmp flow stat api is null/wrong. a00900892, 16-01-2014*/
    ICMP_FLOWSTAT_EXIST,                /* 15 Trying to get/set an already existing icmp flow stat. a00900892, 16-01-2014*/
    ICMP_FLOWSTAT_NOT_EXIST,            /* 16 Trying to a get/set icmp flow stat that does not exist. a00900892, 16-01-2014*/
    ICMP_FLOWSTAT_WRONG_VRF,            /* 17 Trying to a get icmp flow stat with invalid vrf. a00900892, 25-02-2014*/
    ICMP_FLOWSTAT_MALLOC_FAIL,          /* 18 Malloc failure. a00900892, 25-02-2014*/
    ICMP_FLOWSTAT_VRF_REG_FAIL,         /* 19 Registeration for Vrf notification failed. a00900892, 25-02-2014*/
    ICMP_STAT_NOT_EXIST,                /* 20 icmp stat does not exist. a00900892, 05-03-2014*/
    ICMP_STAT_NOT_ENABLE,               /* 21 icmp stat is not enable. a00900892, 03-04-2014*/
    
}ICMP_ERR_E;
/*
 * Variables related to this implementation
 * of the internet control message protocol.
 */
typedef struct  tagICMPSTAT
{
    /* statistics related to icmp packets generated */
    /* commented by chenxia for D23636, 2003/06/26 */
    /* icps_ulError�����Ϊ������ICMP������Ϊ����ԭ��δ�ܷ���ȥ����Ŀ, ���ڶ�Ӧmib�е�icmpOutErrors */
    ULONG   icps_ulError;       /* # of calls to icmp_error */ 
    ULONG   icps_ulOldShort;    /* no error 'cuz old ip too short */
    ULONG   icps_ulOldIcmp;     /* no error 'cuz old was icmp */
    ULONG   icps_ulOutHist_a[ICMP_MAXTYPE + 1];
    ULONG   icps_ulOutTtlExceed;/* added by chenxia for show TTL exceeded D25063, 2003/08/13 */
    /* statistics related to input messages processed */
    ULONG   icps_ulBadCode;     /* icmp_code out of range */
    ULONG   icps_ulTooShort;    /* packet < ICMP_MINLEN */
    ULONG   icps_ulChecksum;    /* bad checksum */
    ULONG   icps_ulBadLen;      /* calculated bound mismatch */
    ULONG   icps_ulReflect;     /* number of responses */
    ULONG   icps_ulInHist_a[ICMP_MAXTYPE + 1];
    ULONG   icps_ulInTtlExceed; /* added by chenxia for show TTL exceeded D25063, 2003/08/13 */
}ICMPSTAT_S;

typedef struct tagICMPMSG
{    
    MBUF_S*   pstMbuf; 
    LONG      lType;  
    LONG      lCode;
    ULONG     ulDest;
    UCHAR     szIfName[MAX_IF_NAME_LENGTH+1];
} ICMP_MSG_S;

/* Begin: 16/01/2013. Added by Antony 900892 for icmp flow statistics. */
typedef struct  tagICMPFlowStat_Echo
{
    ULONG ulLocalIPAddr;        /* Local IP Addres, host order */
    ULONG ulRemoteIPAddr;       /* Peer address, host order */
    ULONG ulEchoRequest;        /* Echo Request number of packets */
    ULONG ulEchoReplay;         /* Echo Replay number of packets */
    ULONG ulSendErr;            /* The client sends the number of failures, 
                                    (unable to send ICMP packet outside) */
}ICMPFLOWSTAT_ECHO_S;

typedef struct  tagICMPFlowStat_PortUnReach
{
    ULONG ulLocalIPAddr;        /* The end of the address, host sequence */
    ULONG ulRemoteIPAddr;       /* peer address, host sequence */
    ULONG ulCount;              /* Count of the statistics */
    ULONG ulSendErr;            /* The client sends the number of failures,
                                    (unable to send ICMP packet outside) */
}ICMPFLOWSTAT_PORTUNREACH_S;

typedef enum tagTcpipICMPFlowStatType
{
    ICMP_LOCAL_ECHO_FLOW_STAT = 0,      /* 0. Local Echo Flow stats */
    ICMP_REMOTE_ECHO_FLOW_STAT,         /* 1. Remote Echo Flow stats */
    ICMP_LOCAL_PORT_UNREACH_FLOW_STAT,  /* 2. Local Port unreachable flow stats */
    ICMP_REMOTE_PORT_UNREACH_FLOW_STAT, /* 3. Remote Port unreachable flow stats */

    ICMP_FLOW_STAT_TYPE_ALL  = 0xff     /* 255. Used to select all flow stat types*/
} TCPIP_ICMP_FLOW_STAT_TYPE_E;

typedef struct tagICMPFlowStat_Cfg
{
    UCHAR ucFlowStatType;       /* Flow statistics type */
    UCHAR ucNumber;             /* Number of statistics */
    UCHAR ucRes[2];
}ICMPFLOWSTAT_CFG_S;

/* Each element of array hold the count for currepsonding icmp type */
typedef struct tagICMPSTATVRF
{
    ULONG   icps_ulOutHist_a[ICMP_MAXTYPE + 1][ICMP_MAXCODE + 1]; /* Stores count of icmp output packets */
    ULONG   icps_ulInHist_a[ICMP_MAXTYPE + 1][ICMP_MAXCODE + 1];  /* Stores count of icmp input packets */
}ICMPSTATVRF_S;

/* End: Added by Antony 900892 for icmp flow statistics. */

extern ULONG TCPIP_ICMP_Error( ICMP_MSG_S* pstIcmpErrSend );
/*******************************************************************************
*    Func Name: TCPIP_ClrIcmpIfSta
*  Description: ����ӿڵ�icmpͳ����Ϣ(����)
*        Input: ULONG ulIfIndex:�ӿ�����
*       Output: VOS_OK
*               ICMP_COMP_NULL:icmp������Ϊ��
*               ICMP_IFNET_NULL:ifnetָ��Ϊ��
*               ICMP_NULL_POINTER:ָ��Ϊ��
*       Return: 
*      Caution: IP���ƿ�ָ��������ӿ��������жϣ���㲻���ж�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIcmpIfSta(ULONG ulIfIndex);
/*******************************************************************************
*    Func Name: TCPIP_ClrIcmpStat
*  Description: ������нӿ��ϵ�icmpͳ����Ϣ�����ȫ��icmpͳ����Ϣ
*        Input: 
*       Output: 
*       Return: VOS_OK
*               ICMP_COMP_NULL:������Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_ClrIcmpStat(VOID);
/*******************************************************************************
*    Func Name: TCPIP_DisablePing
*  Description: ���ý�PING����ʹ��/ȥʹ��
*        Input: ULONG ulSetYes:1 --- ʹ�ܣ�0 --- ȥʹ��
*       Output: 
*       Return: VOS_OK
*               PUBLIC_HA_IS_SMOOTHING:publicģ�����ֶ�������ƽ�����������
*               ICMP_COMP_NULL:icmp������Ϊ��
*               VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_DisablePing (ULONG ulSetYes);
/*******************************************************************************
*    Func Name: TCPIP_GetDisablePingSwitch
*  Description: ��ȡ��PING����ʹ��/ȥʹ�ܱ�־
*        Input: ULONG * pulSwitch:��PINGʹ��/ȥʹ�ܱ�־
*       Output: 
*       Return: VOS_OK
*               ICMP_NULL_POINTER:ָ��Ϊ��
*               ICMP_COMP_NULL:ICMP������Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetDisablePingSwitch(ULONG *pulSwitch);
/*******************************************************************************
*    Func Name: TCPIP_GetIcmpDebugFlag
*  Description: ��ȡicmpģ��ĵ��Կ���
*        Input: 
*       Output: ULONG *pulDebugFlag:icmpģ��ĵ��Կ���
*       Return: VOS_OK
*               ICMP_COMP_NULL:������Ϊ��
*               ICMP_NULL_POINTER:ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpDebugFlag(ULONG *pulDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_GetIcmpStat
*  Description: 
*        Input: 
*       Output: ICMPSTAT_S* pstStat:
*       Return: VOS_OK
*               ICMP_COMP_NULL:������Ϊ��
*               ICMP_NULL_POINTER:ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpStat (ICMPSTAT_S* pstStat);
/*******************************************************************************
*    Func Name: TCPIP_SetIcmpDebugFlag
*  Description: ����icmpģ����Կ���
*        Input: ULONG ulDebugFlag:���Կ��أ�0 --- �رգ�1 --- ��
*       Output: VOS_OK
*               ICMP_COMP_NULL:������Ϊ��
*               ICMP_DEBUGFLAG_ERR:���Կ���ֵ����
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-08   zengshaoyang62531       Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIcmpDebugFlag(ULONG ulDebugFlag);
/*******************************************************************************
*    Func Name: TCPIP_ShowIcmp4Statistic
*  Description: ��ʾicmpģ��ͳ����Ϣ
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-09   zengshaoyang62531       Create
*
*******************************************************************************/
extern VOID TCPIP_ShowIcmp4Statistic(VOID);

extern ULONG TCPIP_SetPingAllowList (ULONG ulOperation, ULONG ulIpAddr, ULONG ulMask);

extern VOID TCPIP_ShowPingAllowList (VOID);

/*******************************************************************************
*    Func Name: TCPIP_SetIcmpAttackGuardSwitch
* Date Created: 2009-09-15
*       Author: wuhailan103194
*  Description: ����ICMP������ͼ���Ϣ���͹�����������
*        Input: ULONG ulSwitch:����
*                              0 �ر�, Ĭ�Ϲر�
*                              ICMP_ATTACKGUARD_SWITCH_ALL 0xffffffff ��ȫ��������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_UNREACH 0x01 ���ɴ������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_REDIRECT 0x02 �ض��������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_TIMXCEED 0x04 TTL���������������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_MASKREP  0x08 ��Ӧ��ַ��������Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_TSREP    0x10 ��Ӧʱ�������Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_PARAMPROB 0x20 IP�ײ�ѡ������Ӧ�Ĳ���Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_SRCADDRANY 0x40 ICMP��ð����������Դ��ַΪ0.0.0.0��������
*       Output: 
*       Return: �ɹ�VOS_OK,�������ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-15   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_SetIcmpAttackGuardSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpAttackGuardSwitch
* Date Created: 2009-09-22
*       Author: wuhailan103194
*  Description: ��ȡICMP������ͼ���Ϣ���͹�����������
*        Input: 
*       Output: ULONG *pulSwitch:���صĿ���ֵ
*                              0 �ر�, Ĭ�Ϲر�
*                              ICMP_ATTACKGUARD_SWITCH_ALL 0xffffffff ��ȫ��������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_UNREACH 0x01 ���ɴ������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_REDIRECT 0x02 �ض��������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_TIMXCEED 0x04 TTL���������������ͷ���������
*                              ICMP_ATTACKGUARD_SWITCH_MASKREP  0x08 ��Ӧ��ַ��������Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_TSREP    0x10 ��Ӧʱ�������Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_PARAMPROB 0x20 IP�ײ�ѡ������Ӧ�Ĳ���Ŀ���
*                              ICMP_ATTACKGUARD_SWITCH_SRCADDRANY 0x40 ICMP��ð����������Դ��ַΪ0.0.0.0��������
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-09-22   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_GetIcmpAttackGuardSwitch(ULONG *pulSwitch);

/* ��ȡ����ҹ0ʱ����ǰʱ�̵�ϵͳʱ��Ĺ��Ӻ���ԭ�� */
typedef ULONG (*ICMP_GETTMSINCEMNHT_HOOK_FUNC)(VOID);
ULONG TCPIP_RegFuncGetTmSinceMnhtHook(ICMP_GETTMSINCEMNHT_HOOK_FUNC pfHookFunc);

/* Begin: 16/01/2014. Added by Antony 900892 for icmp flow statistics. */
/*******************************************************************************
*    Func Name: TCPIP_CreateIcmpFlowStat
* Date Created: 2014-01-16
*       Author: a00900892
*  Description: Using this user can enable the recording of the statistics of 
*                the specified category, once the user enables user cannot 
*                disable/clear the existing entries. User can also specify the
*                number of entries should be recorded, once the max entry is
*                reached then old entry will be overwritten with the new
*                statistics. 
*        Input: pstFlowStat - Specifies the type and the number of entries
*       Output: 
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-16   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_CreateIcmpFlowStat(ICMPFLOWSTAT_CFG_S *pstFlowStat);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpFlowStat
* Date Created: 2014-01-16
*       Author: a00900892
*  Description: Using this user can Retrieve the flow statistics of the 
*                specified flow category type and user can also mention the 
*                number of entries to be retrieved. If the number of entries
*                which are recorded are less than the pucNumber then pucNumber
*                should be updated with the number of entries given to the user.
*        Input: ucFlowStatType - Identifies the flow category type
*               pucNumber - Specifies the number of entries should be retrieved
*               ulVrfIndex - Index to identify the vrf. 
*       Output: pucNumber - Indicates the number of entries returned to the user
*               pStat - Contains the flow statistics (Allocated by user)
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-16   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_GetIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex, UCHAR *pucNumber, VOID *pStat);

/*******************************************************************************
*    Func Name: TCPIP_ClearIcmpFlowStat
* Date Created: 2014-02-19
*       Author: a00900892
*  Description: Using this user can clear the flow statistics of the 
*                specified flow category type. and user can also mention the 
*                number of entries to be retrieved. If the number of entries
*                which are recorded are less than the pucNumber then pucNumber
*                should be updated with the number of entries given to the user.
*        Input: ucFlowStatType - Identifies the flow category type
*               ulVrfIndex - Index to identify the vrf. 
*       Output:
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-19   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ClearIcmpFlowStat(UCHAR ucFlowStatType, ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpStatbyVrf
* Date Created: 2014-03-05
*       Author: a00900892
*  Description: According to the given index obtain the corresponding VRF
*               icmp statistics. VRF domain statistics do not support queries
*               all VRF.
*        Input: ulVrfIndex - Index to identify the vrf. 
*       Output: pstStat    - Pointer to statistics structure.
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-19   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_GetIcmpStatbyVrf(ULONG ulVrfIndex,ICMPSTATVRF_S *pstStat);

/*******************************************************************************
*    Func Name: TCPIP_ClearIcmpStatbyVrf
* Date Created: 2014-03-05
*       Author: a00900892
*  Description: According to the given index clear the corresponding VRF
*               icmp statistics. VRF domain statistics do not support queries
*               all VRF.
*        Input: ulVrfIndex - Index to identify the vrf. 
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-19   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_ClearIcmpStatbyVrf(ULONG ulVrfIndex);

/*******************************************************************************
*    Func Name: TCPIP_EnableIcmpStat
* Date Created: 2014-04-03
*       Author: a00900892
*  Description: Enable both icmp flow statistics and icmp count statistics for
*               vrf.
*        Input: ulFlag - set as 1, to enable Icmp flow stat and icmp count by vrf. 
*       Return: VOS_OK if succes
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-03   a00900892               Create
*
*******************************************************************************/
ULONG TCPIP_EnableIcmpStat(ULONG ulFlag);
/* End. Added by Antony a00900892 for icmp flow statistics. */

/*******************************************************************************
*    Func Name: TCPIP_SetIcmpSrcipProtectSwitch
* Date Created: 2014-10-25
*       Author: wangbin
*  Description: ����ICMPԴ��ַ��������
*        Input:    
*       Output:  ulSwitch 0-  �ر�, 1-��,Ĭ��1:��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-25   wangbin               
*
*******************************************************************************/
ULONG TCPIP_SetIcmpSrcipProtectSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: TCPIP_GetIcmpSrcipProtectSwitch
* Date Created: 2014-10-25
*       Author: wangbin
*  Description: ��ȡICMPԴ��ַ��������
*        Input:    
*       Output:  pulSwitch 0-  �ر�, 1-��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-10-25   wangbin               
*
*******************************************************************************/
ULONG TCPIP_GetIcmpSrcipProtectSwitch(ULONG *pulSwitch);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _ICMP4_API_H_ */

