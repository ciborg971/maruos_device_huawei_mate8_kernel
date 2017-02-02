
#ifndef _BFD_EXT_API_H_
#define _BFD_EXT_API_H_

#ifdef __cplusplus
extern "C" {
#endif
/**************************************************/
/*               API �ṹ���궨��                 */
/**************************************************/
#define BFD_EXT_MAX_INTF_NAME_LEN   47  /* ������BFD_MAX_INTF_NAME_LEN��ͬ */
#define BFD_EXT_MAX_DESC_NAME_LEN   47  /* ������BFD_MAX_DESC_NAME_LEN��ͬ */
#define BFD_EXT_MAX_SESS_NAME_LEN   15  /* ������BFD_MAX_SESS_NAME_LEN��ͬ */
#define BFD_EXT_MAX_VRF_NAME_LEN    31  /* ������BFD_MAX_VRF_NAME_LEN��ͬ */

/*BFD EXTģ��API����������*/
#define BFD_EXT_OP_ADD  1
#define BFD_EXT_OP_DEL  0

/*OSPF�ӿڹ�������Action�ֶ�ֵ����*/
#define BFD_EXT_BLOCK      1
#define BFD_EXT_ENABLE     0

/*OSPF���������������� : �ӿڹ��������̹���*/
#define BFD_OSPF_RULE_TYPE_INTF   1
#define BFD_OSPF_RULE_TYPE_PROC   2

/*��������Чλ����ulFltFlagȡֵ����0�Ĳ��������ʹ��*/    
#define BFD_EXT_FILTER_ALL                    0
#define BFD_EXT_FILTER_DEST                0x01
#define BFD_EXT_FILTER_PREFIXLEN       0x02
#define BFD_EXT_FILTER_VRF                  0x04

/*Added by luogaowei 2012-10-28*/
#define  BFD_EXT_TYPE_STATIC 0  /*BFD ���� ���ͣ�STATIC*/
#define  BFD_EXT_TYPE_OSPF   1  /*BFD ���� ���ͣ�OSPF*/

/*Added by guojianjun178934, ����BFD6 ��OSPFv3��������Ҫָ��ʵ�� Id, 2014/8/8   ���ⵥ��:S-IP-C20-002-BFD6.002 */
/*BFD OSPF�������Ͷ���*/
#define BFD_OSPF_FILTER_NONE           0x00   /*�޹���*/
#define BFD_OSPF_FILTER_BY_PROC        0x01   /*����OSPF���̹���*/
#define BFD_OSPF_FILTER_BY_IF          0x02   /*���սӿڹ���*/
#define BFD_OSPF_FILTER_BY_INSTANCE   0x04   /*���սӿ�ʵ������(��ǰֻ֧�ְ���ָ���ӿ�ʵ������)*/
/* End of Added by guojianjun178934, 2014/8/8   ���ⵥ��:S-IP-C20-002-BFD6.002 */

/*BFD EXT���Կ�������*/
typedef enum tagBFD_RM_DEBUG_E
{
    BFD_DEBUG_NO = 0,             /*�����ĵ��Կ���*/
    BFD_DEBUG_OSPF,               /*OSPF�����ĵ��Կ���*/
    BFD_DEBUG_RTM,                /*RTM�����ĵ��Կ���*/
    BFD_DEBUG_ALL,                /*OSPF,RTM�����ĵ��Կ���*/
    BFD_DEBUG_MAX                 /*���Կ������ֵ*/
}BFD_RM_DEBUG_E;

/* BFD EXT�����붨������ */
typedef enum tagBFD_EXT_ERR_E
{
    BFD_EXT_OK,                         /* 0 */
    BFD_EXT_ERR = MID_COMP_BFDEXT + 1,  /* 1 ����������ָ��δ��ʼ��*/
    BFD_EXT_ERR_NO_INITAIL,             /* 2 BFD EXTģ��δ��ʼ��*/
    BFD_EXT_ERR_NULL_POINTER,           /* 3 ����ָ��Ϊ�� */
    BFD_EXT_ERR_INVALID_PARAMETER,      /* 4 ������Ч*/
    BFD_EXT_ERR_INTF_NOT_EXIST,         /* 5 ָ���ӿڲ����� */
    BFD_EXT_ERR_RX_INTERVAL,            /* 6 BFD����ʱ�����Ƿ� */
    BFD_EXT_ERR_TX_INTERVAL,            /* 7 BFD����ʱ�����Ƿ� */
    BFD_EXT_ERR_DETECT_MULT,            /* 8 BFD��ⱶ���Ƿ� */
    BFD_EXT_ERR_MEM_ALLOC,              /* 9 �ڴ������� */
    BFD_EXT_ERR_STATIC_RT_DETECT_TIME,  /* 10 BFD��̬·��������������ʱ��Ƿ�*/
    BFD_EXT_ERR_STATIC_RT_FULL,         /* 11 BFD For STATIC��������*/
    BFD_EXT_ERR_STATIC_RT_SESS_FAIL,    /* 12 �Ự�ѱ�ʹ�ã���̬·�ɹ���BFD�Ựʧ�� */
    BFD_EXT_ERR_STATIC_RT_NOT_EXIT,     /* 13 ָ���ľ�̬·�ɹ���������  */
    BFD_EXT_ERR_STATIC_SAME_RT,         /* 14 ��̬·�ɹ���BFD�Ựʧ�ܣ���·���Ѿ����� */
    BFD_EXT_ERR_SESSION_NAME,           /* 15 ���õ�BFD�Ự���쳣*/
    BFD_EXT_ERR_PROCID_IFNAME,          /* 16 ����ͬʱ����Process ID��Interface Name ��Process ID��Interface Name ��������*/
    BFD_EXT_ERR_ENA_BLOCK_FLAG,         /* 17 ���ýӿ�Enable��Block��־λȡֵ�쳣*/
    BFD_EXT_ERR_OSPF_RULE_FULL,         /* 18 BFD For OSPF������������*/
    BFD_EXT_ERR_OSPF_BLOCK_FULL,        /* 19 �ӿ�Block�������������*/
    BFD_EXT_ERR_OSPF_RULE_NOT_EXIT,     /* 20 ָ���Ĺ������������� */
    BFD_EXT_ERR_NO_SESS_MATCH_FILTER,   /* 21 û�з��Ϲ��������ĻỰ */
    BFD_EXT_ERR_GET_ENTRY_END,          /* 22 �ѵ����һ������ */
    BFD_EXT_ERR_WAITLIST,               /* 23 WaitList���Ʒ����쳣*/
    BFD_EXT_ERR_PROC_TYPE,              /* 24 Proc Type�������Ĳ�ͬ*/
    BFD_EXT_ERR_BFDMDL,                 /* 25 ����BFDģ��API���ش�����*/
    BFD_EXT_ERR_OSPF_PROCID,            /* 26 OSPF���̺ŷǷ�*/
    BFD_EXT_ERR_GET_VRFINDEX,           /* 27 ��ȡVRF����ʧ�� */
    BFD_EXT_ERR_GET_RTMINDEX,           /* 28 ��ȡRTMʵ����ʧ�� */
    
    BFD_EXT_ERR_MEM_RELEASE,                    /*29 BFD�ͷ��ڴ����*/
    BFD_EXT_ERR_IF_PROC_NOT_MATCH,      /* 30 OSPF���̺ͽӿ����ڵ�VRF��һ�� */
    BFD_EXT_ERR_BOTH_PID_IFNAME,        /*31 <���̺źͽӿ�������ͬʱָ��>*/
    BFD_EXT_ERR_BOTHNOT_PID_IFNAME,     /*32 <���̺źͽӿ������ܶ���ָ��>*/   
    BFD_EXT_ERR_OSPF_NOEXIST,            /* 33 OSPF���̺Ų�����*/
    BFD_EXT_ERR_GET_RELATIONBFDID,       /* 34 ͨ����̬·����Ϣ��ȡ������BFDIDʧ�� */
    BFD_EXT_ERR_INVALID_INSTANCEID,     /* 35 ���õ�OSPFV3�ӿ�InstanceID��Ч*/
    BFD_EXT_ERR_GET_RELATIONTABLE,       /*36ָ����BFD����������*/
    BFD_EXT_ERR_ADD_DUPLICATERELATIONTABLE, /*37����ظ��Ĺ�����*/
    BFD_EXT_ERR_ADD_RELATIONTABLE,          /*38��ӹ�����ʧ��*/

    BFD_EXT_ERR_MAX                     /* ���������ֵ*/
}BFD_EXT_ERR_E;

/* OSPF��BFD�Ự�Ĺ����������ýӿ� */ 
typedef struct tagBfdApiOspfRuleOption
{
    ULONG ulOpType;                                /* ������,0-ɾ����1-����*/ 
    ULONG ulProcIndex;                             /* OSPF ���̺�,����ɾ������ʱ����Ч*/ 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; /* �ӿ�����(�ַ�����ʽ),����ɾ������ʱ����Ч*/ 
    ULONG ulInstanceID;                            /*OSPFV3 ���ڽӿڵ�instance id ,�ͽӿ�һ��ʹ��*/
    ULONG ulMinTxInterval;                         /* BFD�����ķ��ͼ�� ,����������ʱ��Ч*/ 
    ULONG ulMinRxInterval;                         /* BFD�ı��ؽ������� ,����������ʱ��Ч*/ 
    ULONG ulDetectMult;                            /* BFD�ı��ؼ�ⱶ�� ,����������ʱ��Ч*/ 
    USHORT usEnable;                               /* Enable��־*/ 
    USHORT usBlock;                                /* Block��־*/ 
} BFD_API_OSPF_RULE_OP_S;

/* OSPF��BFD�Ự�Ĺ����������ݽṹ */ 
typedef struct tagBfdApiForOspfRule
{
    ULONG   ulRuleType; 
    ULONG   ulIfIdOrProcId; 
    UCHAR   szIfFullName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    ULONG   ulInstanceId;        /*OSPFV3 ���ڽӿڵ�instance id ,�ͽӿ�һ��ʹ��*/
    ULONG   ulMinTxInterval;    /* BFD�����ķ��ͼ�� */ 
    ULONG   ulMinRxInterval;    /* BFD�ı��ؽ������� */ 
    ULONG   ulDetectMult ;      /* BFD�ı��ؼ�ⱶ�� */ 
    ULONG   ulAction ;          /* ��������:�ӿڹ���������Ч,BFD_EXT_ENABLE - 0,BFD_EXT_BLOCK - 1 */ 
} BFD_API_FOR_OSPF_RULE_S;

/* OSPF��BFD�Ự�Ĺ�����Ϣ���ݽṹ */ 
typedef struct tagBfdApiForOspfRelation
{ 
    ULONG ulProcIndex; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulNeighborId; /*OSPFģ���Neighbor ID��������*/
    ULONG ulInstanceId;         /*Instance ID��OSPFV3ʱ��Ч*/
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
}BFD_API_FOR_OSPF_RELATION_S;

typedef struct tagBfdApiStaticRelationOption
{
    ULONG ulOpType;             /* ������,0-ɾ����1-����*/ 
    ULONG ulDestIp;
    ULONG ulPrefixLen;
    ULONG ulNextHop;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-12 */
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-12 */
    USHORT usSpeciRouteVrfFlag;/*1��ʾָ����̬·��Vrf*/
    USHORT usReserve;
    UCHAR  szRouteVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
} BFD_API_STATIC_RELATION_OP_S;

/* ·����Ϣ�ṹ�壬V4��V6���� */
typedef struct tagBfdApiStaticRtInfo
{
    ULONG ulDestIp[4];   /* ������,V4��ַ����ulDestIp[0]�� */
    ULONG ulPrefixLen;
    ULONG ulNextHop[4];  /* ������,V4��ַ����ulNextHop[0]�� */
    ULONG ulIfindex;
    ULONG ulVrfIndex;
    ULONG ulIpVersion;   /* 0��IPV4, 1��IPV6 */
    ULONG ulBfdSessionId; /* ���� */
    ULONG ulBfdVrfIndex;  /*BFD��VRF����*/
} BFD_API_STATIC_RTINFO_S;

/* Static Router��BFD�Ự�Ĺ�����Ϣ���ݽṹ */ 
typedef struct tagBfdApiForStaticRelation
{ 
    ULONG ulDestIp; 
    ULONG ulPrefixLen; 
    ULONG ulNextHop; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    ULONG ulVrfIndex;
    ULONG ulRouteVrfIndex; /*��̬·�ɵ�VRF ����*/
}BFD_API_FOR_STATIC_RELATION_S;

/* wangjiaqi modify for ipv6 bfd 20131125 begin */
typedef struct tagBfd6ApiStaticRelationOption
{
    ULONG ulOpType;             /* ������,0-ɾ����1-����*/ 
    ULONG ulDestIp[4];
    ULONG ulPrefixLen;
    ULONG ulNextHop[4];
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    USHORT usSpeciRouteVrfFlag;/*1��ʾָ����̬·��Vrf��Ĭ��Ϊ0����ʹ��*/
    USHORT usReserve;
    UCHAR szRouteVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1]; /*��̬·�ɰ󶨵�VRF*/
} BFD6_API_STATIC_RELATION_OP_S;

typedef struct tagBfd6ApiForStaticRelation
{ 
    ULONG ulDestIp[4]; 
    ULONG ulPrefixLen; 
    ULONG ulNextHop[4]; 
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1]; 
    ULONG ulSessionId; 
    UCHAR szSessionDes[BFD_EXT_MAX_DESC_NAME_LEN + 1]; 
    UCHAR szSessionName[BFD_EXT_MAX_SESS_NAME_LEN + 1];
    ULONG ulVrfIndex;
    ULONG ulRouteVrfIndex; /*��̬·�ɵ�VRF ����*/
}BFD6_API_FOR_STATIC_RELATION_S;
/* wangjiaqi modify for ipv6 bfd end */
/*************************************/
/*         �������ṹ��              */
/*************************************/
/* OSPF��BFD�Ự����������Ϣ���ݽṹ */
typedef struct tagBfdApiForOspfFilter
{ 
    ULONG ulProcIndex;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
}BFD_API_FOR_OSPF_FILTER_S;

/* OSPF��BFD�Ự����������Ϣ���ݽṹ */
typedef struct tagBfd6ApiForOspfFilter
{
    ULONG ulProcIndex;
    UCHAR szIfName[BFD_EXT_MAX_INTF_NAME_LEN + 1];
    ULONG ulInstanceId;  
    UCHAR ucType;         /* ֧�� OSPF ���̺š�ָ���ӿڡ�ָ���ӿ� & instance id ���ֲ�ѯģʽ*/
    UCHAR ucPad[3]; 
}BFD6_API_FOR_OSPF_FILTER_S;


/* ��̬·����BFD�Ự����������Ϣ���ݽṹ */ 
typedef struct tagBfdApiForStaticFilter
{ 
    ULONG ulFltFlag;/*ȡֵ��Χ:BFD_EXT_FILTER_ALL                0    
                              BFD_EXT_FILTER_DEST                0x01
                              BFD_EXT_FILTER_PREFIXLEN       0x02
                              BFD_EXT_FILTER_VRF                  0x04*/
    ULONG ulDestIp;
    ULONG ulPrefixLen;
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
    /* End for BC3D02529 */
}BFD_API_FOR_STATIC_FILTER_S;
/* wangjiaqi modify for ipv6 bfd 20131125 begin */
typedef struct tagBfd6ApiForStaticFilter
{ 
    ULONG ulFltFlag;/*ȡֵ��Χ:BFD_EXT_FILTER_ALL                0    
                              BFD_EXT_FILTER_DEST                0x01
                              BFD_EXT_FILTER_PREFIXLEN       0x02
                              BFD_EXT_FILTER_VRF                  0x04*/
    ULONG ulDestIp[4];
    ULONG ulPrefixLen;
    UCHAR szVrfName[BFD_EXT_MAX_VRF_NAME_LEN + 1];
}BFD6_API_FOR_STATIC_FILTER_S;
/* wangjiaqi modify for ipv6 bfd end */

typedef ULONG(*BFD_RM_NOTIFY_HOOK_FUNC)( ULONG ulType, ULONG ulProcIndex, ULONG ulStat,VOID * pPara);


typedef struct tagBfdApiDynamicNodeInfo
{ 
    ULONG ulProcType;   /* ���ͣ�BFD_EXT_TYPE_OSPF ��Ŀǰ��֧��OSPF���ͣ�*/
    ULONG ulProcId;     /* OSPFʵ����*/
    ULONG ulVrfIndex;   /* VRF����*/
    ULONG ulInstanceId; /* Instace ID��OSPFV3��Ч*/
    ULONG ulRouterId;    /* Route ID(������)*/
    ULONG ulIfIndex;    /* ���ھӵĽӿ�����*/
    ULONG ulNetworkType;/* ��ַ����:IPv4 BFD_EXT_TABLE_IPV4 ����IPv6 BFD_EXT_TABLE_IPV6*/
    ULONG ulSrcIP[4];   /* ���˵�ַ*/
    ULONG ulDstIP[4];   /* �Զ˵�ַ*/
}BFD_API_DYNAMIC_NODE_INFO_S;

typedef struct tagBfdApiDynamicNodeCfg
{ 
    ULONG ulProtocal;  /*�ݰ�4Э���RFCЭ���BFD    
                       BFD_PROTO_DRAFT4    0 
                       BFD_PROTO_STD       1*/
}BFD_API_DYNAMIC_NODE_CFG_S;

typedef ULONG(*BFD_GET_DYN_SESS_PRO_HOOK_FUNC)(BFD_API_DYNAMIC_NODE_INFO_S *pstNode, BFD_API_DYNAMIC_NODE_CFG_S *pstOutInfo);

/*BFD For OSPF API*/
extern ULONG BFD_SetRtStaticDetecTime(ULONG ulTime);
extern ULONG BFD_AddDelOspfRule(BFD_API_OSPF_RULE_OP_S stOspfRule);
extern ULONG BFD_OpenOspfRuleTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspfRuleTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspfRuleEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RULE_S *pstRules);
extern ULONG BFD_OpenOspfRelationTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspfRelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspfRelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RELATION_S *pstRelations);
extern ULONG BFD_AddDelOspf6Rule(BFD_API_OSPF_RULE_OP_S stOspfRule);
extern ULONG BFD_OpenOspf6RuleTable(UINTPTR *pulWaitListHandle, BFD6_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspf6RuleTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspf6RuleEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RULE_S *pstRules);
extern ULONG BFD_OpenOspf6RelationTable(UINTPTR *pulWaitListHandle,BFD6_API_FOR_OSPF_FILTER_S *pstFilter);
extern ULONG BFD_CloseOspf6RelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetOspf6RelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_OSPF_RELATION_S *pstRelations);

/*BFD For Static API*/
extern ULONG BFD_AddDelRtStatic(BFD_API_STATIC_RELATION_OP_S stStaticRelation);
extern ULONG BFD_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD_API_FOR_STATIC_FILTER_S *pstFilter);
extern ULONG BFD_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);
extern ULONG BFD_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList, BFD_API_FOR_STATIC_RELATION_S *pstRelations);

/*��ά�ɲ� API*/
extern ULONG BFD_SetDbgSwitch(ULONG ulSwitch);
extern ULONG BFD_SetV6DbgSwitch(ULONG ulSwitch);
extern VOID BFD_ShowOspfRule(VOID);
extern VOID BFD_ShowOspfSession(VOID);
extern VOID BFD_ShowRtStaticSession(VOID);
extern VOID BFD_ShowOspf6Rule(VOID);
extern VOID BFD_ShowOspf6Session(VOID);

extern ULONG BFD_RegFuncGetDynamicSessionPro (BFD_GET_DYN_SESS_PRO_HOOK_FUNC pfFunc);
/* wangjiaqi modify for ipv6 bfd 20131125 begin */
/*******************************************************************************
*    Func Name:    BFD6_AddDelRtStatic
*    Date Created: 
*    Author: 
*    Description:  ���ӡ�ɾ����̬·����BFD6�Ự����
*    Input:        stStaticRelation: BFD��·�ɹ����Ự���ò�����
*    Output:       �ޣ�
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_AddDelRtStatic(BFD6_API_STATIC_RELATION_OP_S stStaticRelation);

/*******************************************************************************
*    Func Name:    BFD6_OpenRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  ��ȡBFD6��Ststic�Ự�������WaitList���
*    Input:        pFilter: ������
*                  ulSizeOfFilter: ����������
*    Output:       pulWaitListHandle: WaitList���
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*                  BFD_EXT_ERR_GET_ENTRY_END �ӱ��л�ȡ�������Ϲ�����������ָ��
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD6_API_FOR_STATIC_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name:    BFD6_CloseRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  �ر�BFD6��Ststic�Ự�������WaitList���
*    Input:        ulWaitListHandle: WaitList���
*    Output:       
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);

/*******************************************************************************
*    Func Name:    BFD6_GetRtStaticRelationEntry
*    Date Created: 
*    Author: 
*    Description:  ͨ��WaitList�������ȡ��һ�����������������ָ��
*    Input:        ulEntryWaitList: WaitList���
*    Output:       pstRelations:��ȡ��������
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*                  BFD_EXT_ERR_GET_ENTRY_END �ӱ��л�ȡ�������Ϲ�����������ָ��
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG BFD6_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList, BFD6_API_FOR_STATIC_RELATION_S *pstRelations);

/*******************************************************************************
*    Func Name:    BFD6_ShowRtStaticSession
*    Date Created: 
*    Author: 
*    Description:  ��ʾ���о�̬·����BFD6�Ự�Ĺ�������
*    Input:        
*    Output:       
*    Return:       
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
VOID BFD6_ShowRtStaticSession(VOID);
/* wangjiaqi modify for ipv6 bfd end */

/*******************************************************************************
*    Func Name:    BFD_GetBFDSessionByRtInfo
*    Date Created: 2014-07-07
*    Author:       fengjing209023
*    Description:  ͨ����̬·����Ϣ��ȡ�󶨵Ĺ���BFD�ỰID
*    Input:        BFD_API_STATIC_RTINFO_S pstBfdRtInfo: ·����Ϣ�ṹ�壬
*                  ����Ҳ����������
*    Output:       pstBfdRtInfo->ulBfdSessionId
*    Return:       �ɹ�����BFD_EXT_OK�����򷵻ش�����
*    Caution:      �������豣֤��������Ч��
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2014-07-07      fengjing209023        Create
*******************************************************************************/
ULONG BFD_GetBFDSessionByRtInfo(BFD_API_STATIC_RTINFO_S *pstBfdRtInfo);

#ifdef __cplusplus
}
#endif

#endif


