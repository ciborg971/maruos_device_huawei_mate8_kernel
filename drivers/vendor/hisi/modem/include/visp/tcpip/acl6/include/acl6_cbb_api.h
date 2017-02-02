/***********************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_cbb_api.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: ACL6 CBB�����ṩ�����ݽṹ����ͺ�������
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 ***********************************************************************************/
#ifndef _ACL6_CBB_API_H_
#define _ACL6_CBB_API_H_

#ifdef  __cplusplus
extern "C" 
{
#endif

/* ACL6�Ĵ����� */
enum enumAcl6Help
{
    Help_ACL6_OK = 0,
    Help_ACL6_ERR = MID_COMP_ACL6 + 1,   /* 1 ���� */
    Help_ACL6_NullPoint,                 /* 2 ����ָ��Ϊ�� */
    Help_ACL6_InitErr,                   /* 3 ACL6 CBB�Ѿ���ɳ�ʼ��*/
    Help_ACL6_NotInit,                   /* 4 ACL6 CBBδ�ɹ���ʼ��*/
    Help_ACL6_CreateSmErr,               /* 5 �����ź���ʧ�� */
    Help_ACL6_TooMuchRulesInSys,         /* 6 ����������ϵͳ���� */
    Help_ACL6_TooMuchRulesInGroup,       /* 7 �������������������� */
    Help_ACL6_OperTypeErr,               /* 8 ����Ĳ�������*/ 
    Help_ACL6_GroupIndexErr,             /* 9 �������������� */
    Help_ACL6_GroupExist,                /* 10 �������Ѿ����� */
    Help_ACL6_GroupNotExist,             /* 11 �����鲻���� */
    Help_ACL6_MatchOrderErr,             /* 12 ������ƥ��˳����� */
    Help_ACL6_StepErr,                   /* 13 ����Ĳ��� */
    Help_ACL6_DescriptionTooLong,        /* 14 ���������������Ϣ����128�ֽ� */
    Help_ACL6_NotChangeMatchOrder,       /* 15 ���������ù���󲻿ɸı�ƥ��˳�� */
    Help_ACL6_RuleNotExist,              /* 16 ���򲻴��� */
    Help_ACL6_RuleExist,                 /* 17 �����Ѿ����� */
    Help_ACL6_RuleIndexTooLarge,         /* 18 �����������꣬�޷������µĹ�������*/
    Help_ACL6_CanNotGiveRuleIndex,       /* 19 ����������˳��Ϊ�Զ�ƥ��ʱ��������ָ������� */
    Help_ACL6_DescriptionInvalid,        /* 20 ���������������Ϣ���Ϸ� */
    Help_ACL6_RuleIndexErr,              /* 21 ��������������� */
    Help_ACL6_CanNotModify,              /* 22 �Զ�ƥ��ʱ��ֹ�޸Ĺ��� */
    Help_ACL6_RuleManageErr,             /* 23 ���ù���ʧ�� */
    Help_ACL6_RuleNodeMallocErr,         /* 24 �������ڵ�ʧ�� */
    Help_ACL6_CfgOpErr,                  /* 25 ��������ѡ����� */
    Help_ACL6_ActionErr,                 /* 26 ����Actionȡֵ���� */
    Help_ACL6_SrcAddrMaskErr,            /* 27 ������ϢԴ��ַ���볤�ȴ���*/
    Help_ACL6_DstAddrMaskErr,            /* 28 ������ϢĿ�ĵ�ַ���볤�ȴ���*/
    Help_ACL6_HopLmErr,                  /* 29 Hop Limitֵȡֵ���� */
    Help_ACL6_ClassErr,                  /* 30 ���ȼ�ȡֵ���� */
    Help_ACL6_FragErr,                   /* 31 ��Ƭ���ȡֵ���� */
    Help_ACL6_SrcPortTypeErr,            /* 32 Դ�˿����ʹ��� */
    Help_ACL6_SrcPortRangeErr,           /* 33 Դ�˿ڷ�Χ���� */
    Help_ACL6_DstPortTypeErr,            /* 34 Ŀ�Ķ˿����ʹ��� */
    Help_ACL6_DstPortRangeErr,           /* 35 Ŀ�Ķ˿ڷ�Χ���� */
    Help_ACL6_ProtocalErr,               /* 36 Э��Ŵ��� */
    Help_ACL6_GetVrfIndexErr,            /* 37 ��ȡVRF Indexʧ�� */
    Help_ACL6_IfIndexErr,                /* 38 �ӿ������Ƿ� */
    Help_ACL6_MallocErr,                 /* 39 ���ù����з����ڴ���� */
    Help_ACL6_TypeNotExist,              /* 40 �������Ͳ����� */
    Help_ACL6_TypeIdErr,                 /* 41 ��������ID���� */
    Help_ACL6_ContentNull,               /* 42 ������Ϣ���ݽṹ�еĹ�������ָ��Ϊ��*/
    Help_ACL6_ContentSizeZero,           /* 43 ע���������ݽṹ�еĹ������ݴ�СΪ0*/
    Help_ACL6_FuncNull,                  /* 44 ע���������ݽṹ���к���ָ��Ϊ��*/
    Help_ACL6_PortNumErr,                /* 45 �˿ڷ�Χ�Ķ������Ϸ� */
    Help_ACL6_GroupMallocErr,            /* 46 Ϊ����������ڴ�ʧ�� */
    Help_ACL6_TypeBasicMallocErr,        /* 47 Ϊ�����������ͷ����ڴ�ʧ�� */
    Help_ACL6_TypeAdvMallocErr,          /* 48 Ϊ�߼��������ͷ����ڴ�ʧ�� */
    Help_ACL6_TypeIfMallocErr,           /* 49 Ϊ���ڽӿڹ������ͷ����ڴ�ʧ�� */
    Help_ACL6_GroupBasicMallocErr,       /* 50 Ϊ��������������ڴ�ʧ�� */
    Help_ACL6_GroupAdvMallocErr,         /* 51 Ϊ�߼�����������ڴ�ʧ�� */
    Help_ACL6_GroupIfMallocErr,          /* 52 Ϊ���ڽӿڵĹ���������ڴ�ʧ�� */
    Help_ACL6_WaitlistOpenFail,          /* 53 ��waitlistʧ�� */
    Help_ACL6_WaitlistSetFail,           /* 54 ����waitlistʧ�� */
    Help_ACL6_WaitlistGetFail,           /* 55 ��ȡwaitlist�ڵ�ʧ�� */
    Help_ACL6_WaitlistCloseFail,         /* 56 �ر�waitlistʧ�� */
    Help_ACL6_GetMatchCountErr,          /* 57 ��ȡPPI������Ĺ���ƥ��ͳ����Ϣʧ�� */
    Help_ACL6_End,                       /* 58 ��������ʱ�������һ������ */
    Help_ACL6_DefaultPortErr,            /* 59 Protocal����Ϊ����ʱ������ָ����Դ�˿ںź�Ŀ�Ķ˿ںŻָ�ΪĬ��ֵ */
    Help_ACL6_SetPortRgWithInvalidPro,   /* 60 ���ö˿ں�ʱ������Э�����ͱ���Ϊ��һֵ��
                                                                                     �ҽ�֧��ICMP6��TCP6��UDP6��SCTP */
    Help_ACL6_Icmp6TypeErr,              /* 61 ICMP6 ���ʹ��� */
    Help_ACL6_Icmp6CodeErr,              /* 62 ICMP6 Code���� */
    Help_ACL6_PpiFuncNotExist,           /* 63 PPI�·�����δע�� */
    Help_ACL6_PpiUpdateErr,              /* 64 PPI�·�����ʧ�� */
    Help_ACL6_RuleNotFound,              /* 65 û���ҵ�ƥ����� */
    Help_ACL6_MbufOperErr,               /* 66 Mbuf����ʧ�� */
    Help_ACL6_MbufPktNull,               /* 67 Mbuf���ݶ�Ϊ��*/
    Help_ACL6_GetIpv6VTable,             /* 68 ��ȡipv6������ʧ�� */
    Help_ACL6_CALLBACK_EXIST,            /* 69 ͬһģ��Ļص������Ѿ�ע�� */
    Help_ACL6_NoRuleInGroup,             /* 70 ��������û���κι��� */
    Help_ACL6_MbufNull,                  /* 71 MbufΪ�� */
    
    Help_ACLFW6_ERR_GET_PRECONFIG,       /* 72 Not able to extract preconfig value */
    Help_ACLFW6_ERR_HASH_INIT,           /* 73 Unable to initailize the hash table */
    Help_ACLFW6_ERR_NULL,                /* 74 Null Input */
    Help_ACLFW6_ERR_INTERFACE_NAME,      /* 75 Interface name length is not valid*/
    Help_ACLFW6_ERR_GET_IFINDEX,         /* 76 Unable to derive IfIndex based on Interface name */    
    Help_ACLFW6_INVALID_FLAG,            /* 77 Invalid operation flag it must be ACLFW6_CFG_DEL/ACLFW6_CFG_ADD */
    Help_ACLFW6_INVALID_DIRECTION,       /* 78 Invalid filter direction.*/
    Help_ACLFW6_INVALID_PERMISSION,      /* 79 Invalid ACL6 permission it must be either ACL6_DENY or ACL6_PERMIT */
    Help_ACLFW6_GROUP_NOT_EXIST,         /* 80 The group does not exist */
    Help_ACLFW6_ERR_CFGSECPOLICY_INIT,   /* 81 ACLFW6 Securiy policy module is not initialized*/
    Help_ACLFW6_ERR_NO_NODE,             /* 82 There is no aclgroup assigned to interface*/
    Help_ACLFW6_ERR_HASH_INVALID_PARA,   /* 83 Unable to initialize the hash table*/
    Help_ACLFW6_ERR_HASH_MALLOC_FAIL,    /* 84 Malloc failure for hash table*/
    Help_ACLFW6_HASH_TABLE_OK,           /* 85 If the hash insertion is successful */
    Help_ACLFW6_HASH_TABLE_ITEM_EXIST,   /* 86 If the hash table already have the entry for a given key*/
    Help_ACLFW6_ERR_HASH_INSERT_TYPE,    /* 87 Invalid hash insertion type is used.*/
    Help_ACLFW6_HASH_TABLE_FULL,         /* 88 Error when hash table is filled */    
    Help_ACLFW6_HASH_ITEM_NOT_EXIST,     /* 89 No entry is present in hash table for a given key*/    
    Help_ACLFW6_ERR_NO_MATCH,            /* 90 The cofig value does not matched with the entry */        
    Help_ACLFW6_ERR_MALLOC,              /* 91 malloc failure*/
    Help_ACLFW6_ERR_IF_TABLE,            /* 92 Unable to open the ifnet table*/    
    Help_ACLFW6_ERR_GET_IF_TABLE,        /* 93 Error to get interface entry from ifnet table*/    
    Help_ACLFW6_END_IF_TABLE,            /* 94 End of ifnet waitlst table */
    Help_ACLFW6_ERR_FILTER_INPUT,        /* 95 Using filter with waitlsit next api is not permited */
    Help_ACLFW6_ERR_IF_TABLE_CLOSE,      /* 96 Unable to close waitlist table of IFNET for a given handle.*/
    Help_ACLFW6_ERR_HASH_TABLE_NULL,     /* 97 Invalid input for hash table delete*/
    Help_ACLFW6_ERR_PPI_CFG_DOWNLOAD,    /* 98 Unable to download the PPI info.*/
    Help_ACLFW6_INVALID_STAT_SWITCH,     /* 99 Invalid flow statistsic switch option.*/

    Help_ACL6_Max   /* ��ʶö��������,��ʵ�ʴ�����, ����֮ǰ����µĴ����� */
};

/**********************************************************
*   ������غ궨��
***********************************************************/
/*�������������*/
#define ACL6_DEL 0
#define ACL6_ADD 1

/* ����ƥ�������� */
#define ACL6_DENY         0 
#define ACL6_PERMIT       1

/*�ӿڹ�������*/
#define ACL6_IFIN    1    /* ��ӿڹ��� */
#define ACL6_IFOUT   2    /* ���ӿڹ��� */
#define ACL6_IFANY   3    /* �����ӿڹ��� */

#define ACL6_CFG_NOOPER  0 /*�����ñ��*/
#define ACL6_CFG_SET     1 /*���ñ��*/
#define ACL6_CFG_DEFAULT 2 /*�ָ�Ĭ��ֵ���*/

/* ������ƥ��˳�� */
#define ACL6_MATCHORDER_CONFIG   1
#define ACL6_MATCHORDER_AUTO     2

/* ȱʡ��������ID */
#define ACL6_BASIC_RULE_TYPE     1
#define ACL6_ADVANCE_RULE_TYPE   2
#define ACL6_IFBASED_RULE_TYPE   3

#define ACL6_MAX_VRFNAME_LENGTH  31   /* VRF����������Ϣ���� */    
#define ACL6_DESCRIPTIONSTR_LEN  127  /* ������������Ϣ���� */

/* ��Ч��������� */
#define ACL6_INVALID_GROUP_INDEX    0
/* ��Ч�������� */
#define ACL6_INVALID_RULE_INDEX     0xFFFFFFFFL
/* IPv6��ַ���� */
#define ACL6_IPV6_ADDR_LEN 16
/* ����ӿ����� */
#define ACL6_IFINDEXANY 0
/* ����VRF���� */
#define ACL6_ANY_VRFINDEX     0xFFFFFFFFL

/* ��Ʒ��Ҫʹ��Ĭ�ϲ���,������API�ж���һ��,ע��ú궨�������acl6_def.h�е�ACL6_DEFAULT_STEP���屣��һ�� */
/* ������Ĭ�ϲ��� */
#ifndef ACL6_DEFAULT_STEP
#define ACL6_DEFAULT_STEP 5
#endif
/**********************************************************
*   ����λ��غ궨�壬�ڱ���ƥ��ʱ�ɶ�ָ���ֶβ���Ƚ�
***********************************************************/
/* �����ֶθ�λ�Ķ��� */
#define ACL6_SIPByte     0x0001     
#define ACL6_DIPByte     0x0002
#define ACL6_PROByte     0x0004
#define ACL6_HLMByte     0x0008
#define ACL6_CLSByte     0x0010
#define ACL6_SPORTByte   0x0020
#define ACL6_DPORTByte   0x0040
#define ACL6_VRFByte     0x0080

/* �˿ڱȽ����� */
typedef enum enumAcl6PortOpType
{
    ACL6_PORT_OP_TYPE_IN, /* 0: us*Begin <= IN <= us*End */  
    ACL6_PORT_OP_TYPE_EQ, /* 1: IN == us*Begin */
    ACL6_PORT_OP_TYPE_NEQ,/* 2: IN != us*Begin */  
    ACL6_PORT_OP_TYPE_GE, /* 3: IN >= us*Begin */
    ACL6_PORT_OP_TYPE_LE, /* 4: IN <= us*Begin */
    ACL6_PORT_OP_TYPE_MAX
}ACL6_PORT_OP_TYPE_E;

/**********************************************************
*   �������ݽṹ
***********************************************************/
/* ��Ź����е�IPv6��ַ������ */
typedef struct tagAcl6Ip6Addr 
{
    UCHAR ucAddr[ACL6_IPV6_ADDR_LEN];    /*IPv6��ַ��Ϣ*/
    ULONG ulMaskLen;     /*IPv6��ַ���볤��*/
} ACL6_IP6ADDR_S;

/* ACL6��ѯ������*/
typedef struct tagAcl6Filter
{    
    ULONG  ulGroupIndex; /*����������*/
    ULONG  ulRuleIndex;  /*��������*/
}ACL6_FILTER_S;

/* ACL6 ���������ýṹ*/
typedef struct tagAcl6CfgManageGroup
{
    ULONG ulOperType;           /*��������:ACL6_ADD����������£�ACL6_DEL��ɾ��*/
    ULONG ulGroupIndex;         /*����������*/
    ULONG ulSetMatchOrder;      /*�Ƿ�����ƥ��˳��:
                                  ACL6_CFG_NOOPER �� �����ñ�ǣ�
                                  ACL6_CFG_SET �� ���ñ�ǣ�
                                  ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulMatchOrder;         /*ƥ��˳��:(Ĭ��ΪACL6_MATCHORDER_CONFIG)
                                  ACL6_MATCHORDER_CONFIG �� ����˳��
                                  ACL6_MATCHORDER_AUTO �� �Զ�˳��*/      
    ULONG ulSetStep;            /*�Ƿ����ò���:
                                  ACL6_CFG_NOOPER �� �����ñ�ǣ�
                                  ACL6_CFG_SET �� ���ñ�ǣ�
                                  ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulStep;               /*��������Χ1-20(Ĭ��Ϊ5)*/
    ULONG ulSetDes;             /*�Ƿ�����������Ϣ:
                                  ACL6_CFG_NOOPER �� �����ñ�ǣ�
                                  ACL6_CFG_SET �� ���ñ�ǣ�
                                  ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    CHAR szDescription[ACL6_DESCRIPTIONSTR_LEN + 1];/*������Ϣ��1-127���ַ�*/
}ACL6_CFG_MANAGEGROUP_S;

/* ACL6 �����������ýṹ*/
typedef struct tagAcl6CfgBasicRule
{
    ULONG ulOperType;     /*��������:ACL6_ADD����������£�ACL6_DEL��ɾ��*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulVrfOp;        /*�ݲ�֧�ָ�����
                            �Ƿ����ñ���VRF������:
                            ACL6_CFG_NOOPER �� �����ñ�ǣ�
                            ACL6_CFG_SET �� ���ñ�ǣ�
                            ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulVrfIndex;
    ULONG ulActionOp;     /*�Ƿ�����action�Ĳ������ͣ�
                             ACL6_CFG_NOOPER �� �����ñ�ǣ�
                             ACL6_CFG_SET �� ���ñ�ǣ�
                             ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulAction;       /*�����õ��µ�actionֵ:(Ĭ��ΪACL6_DENY)
                             ACL6_DENY �� Deny
                             ACL6_PERMIT �� Permit*/
    ULONG ulFragOp;         /*�Ƿ����ñ��ķ�Ƭ��־:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulFrag;           /*���ķ�Ƭ(Ĭ��Ϊ0������Ƭ)*/
    ULONG ulSrcIpOp;      /*�Ƿ����ñ���Դ��ַ:
                            ACL6_CFG_NOOPER �� �����ñ�ǣ�
                            ACL6_CFG_SET �� ���ñ�ǣ�
                            ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ACL6_IP6ADDR_S stSrcIp;/*����Դ��ַ(Ĭ��Ϊ0������Ĭ��128)*/
}ACL6_CFG_BASIC_RULE_S;

/* ACL6 �˿ڷ�Χ�ṹ*/
typedef struct tagAcl6PortRange
{
    USHORT usBegin;  /*��ʼ�˿�*/
    USHORT usEnd;    /*��ֹ�˿�*/
}ACL6_PORT_RANGE_S;

/* ACL6 �߼��������ýṹ*/
typedef struct tagAcl6CfgAdvRule
{
    ULONG ulOperType;       /*��������:ACL6_ADD����������£�ACL6_DEL��ɾ��*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulVrfOp;          /*�ݲ�֧�ָ�����
                            �Ƿ����ñ���VRF������:
                            ACL6_CFG_NOOPER �� �����ñ�ǣ�
                            ACL6_CFG_SET �� ���ñ�ǣ�
                            ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulVrfIndex;
    ULONG ulActionOp;       /*�Ƿ�����action�Ĳ������ͣ�
                               ACL6_CFG_NOOPER �� �����ñ�ǣ�
                               ACL6_CFG_SET �� ���ñ�ǣ�
                               ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulAction;         /*�����õ��µ�actionֵ:(Ĭ��ΪACL6_DENY)
                               ACL6_DENY �� Deny
                               ACL6_PERMIT �� Permit*/
    ULONG ulFragOp;         /*�Ƿ����ñ��ķ�Ƭ��־:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulFrag;           /*���ķ�Ƭ(Ĭ��Ϊ0������Ƭ)*/
    ULONG ulSrcIpOp;        /*�Ƿ����ñ���Դ��ַ:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ACL6_IP6ADDR_S stSrcIp; /*����Դ��ַ(Ĭ��Ϊ0������Ĭ��128)*/
    ULONG ulDstIpOp;        /*�Ƿ����ñ���Ŀ�ĵ�ַ:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ACL6_IP6ADDR_S stDstIp; /*����Ŀ�ĵ�ַ(Ĭ��Ϊ0������Ĭ��128)*/
    ULONG ulHopLmOp;        /*�Ƿ����ñ���Hop Limit:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulHopLm;          /*����Hop Limit(Ĭ��Ϊ255)*/
    ULONG ulClassOp;        /*�Ƿ����ñ���Traffic Class:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulClass;          /*����Traffic Class(Ĭ��Ϊ255)*/
    ULONG ulSrcPortOp;      /*�Ƿ����ñ���Դ�˿ڱ�־:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulSrcPortOpType;  /*�˿ڱȽ�����:(Ĭ��ΪACL6_PORT_OP_TYPE_IN)
                              ACL6_PORT_OP_TYPE_IN - ��Χ��
                              ACL6_PORT_OP_TYPE_EQ - ����
                              ACL6_PORT_OP_TYPE_NEQ - ������
                              ACL6_PORT_OP_TYPE_GE - ����
                              ACL6_PORT_OP_TYPE_LE - С��*/
    ACL6_PORT_RANGE_S stSrcPort;/*����Դ�˿�(Ĭ��ΪBegain:0,End:65535)*/
    ULONG ulDstPortOp;      /*�Ƿ����ñ���Ŀ�Ķ˿ڱ�־:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulDstPortOpType;  /*�˿ڱȽ�����:(Ĭ��ΪACL6_PORT_OP_TYPE_IN)
                              ACL6_PORT_OP_TYPE_IN - ��Χ��
                              ACL6_PORT_OP_TYPE_EQ - ����
                              ACL6_PORT_OP_TYPE_NEQ - ������
                              ACL6_PORT_OP_TYPE_GE - ����
                              ACL6_PORT_OP_TYPE_LE - С��*/
    ACL6_PORT_RANGE_S stDstPort;/*����Ŀ�Ķ˿�(Ĭ��ΪBegain:0,End:65535)*/
    ULONG ulProtoOp;        /*�Ƿ����ñ���Э�����ͱ�־:
                              ACL6_CFG_NOOPER �� �����ñ�ǣ�
                              ACL6_CFG_SET �� ���ñ�ǣ�
                              ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    UCHAR ucProtoBegin;     /*����Э������(Ĭ��Ϊ0)*/
    UCHAR ucProtoEnd;       /*����Э������(Ĭ��Ϊ255)*/
    UCHAR ucPadding[2];
}ACL6_CFG_ADV_RULE_S;

/* ACL6 ���ڽӿڹ������ýṹ*/
typedef struct tagAcl6CfgIfBasedRuleInfo
{
    ULONG ulOperType;       /*��������:
                               ACL6_ADD����������£�
                               ACL6_DEL��ɾ��*/
    ULONG ulGroupIndex;
    ULONG ulRuleIndex;
    ULONG ulActionOp;       /*�Ƿ�����action�Ĳ������ͣ�
                               ACL6_CFG_NOOPER �� �����ñ�ǣ�
                               ACL6_CFG_SET �� ���ñ�ǣ�
                               ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulAction;         /*�����õ��µ�actionֵ:(Ĭ��ΪACL6_DENY)
                               ACL6_DENY �� Deny
                               ACL6_PERMIT �� Permit*/
    ULONG ulIfOp;           /*�Ƿ����ýӿڱ�־��
                               ACL6_CFG_NOOPER �� �����ñ�ǣ�
                               ACL6_CFG_SET �� ���ñ�ǣ�
                               ACL6_CFG_DEFAULT �� �ָ�Ĭ��ֵ���*/
    ULONG ulIfIndex;        /*�����õ��µĽӿ�����(Ĭ��ֵΪ0)*/
} ACL6_CFG_IFBASED_RULEINFO_S;

/*������������ ContentInfo*/
typedef struct tagAcl6BasicContentInfo
{
    ULONG ulAction;     /* ƥ��ɹ���Ķ��� */
    ULONG ulFrag;       /* �Ƿ����Ƭѡ�� */
    ULONG ulVrfIndex;   /* VRF���� */
    ACL6_IP6ADDR_S stSrcIp;
} ACL6_BASIC_CONTENT_INFO_S;

/*�߼��������� ContentInfo*/
typedef struct tagAcl6AdvanceContentInfo 
{
    ULONG ulAction;     /* ƥ��ɹ���Ķ��� 
                           ACL6_DENY �� Deny
                           ACL6_PERMIT �� Permit*/    
    ULONG ulFrag;       /* �Ƿ����Ƭѡ�� */
    ULONG ulVrfIndex;       /* VRF���� */
    ACL6_IP6ADDR_S stSrcIp;
    ACL6_IP6ADDR_S stDstIp;
    
    ULONG ulSrcPortOpType;
    ACL6_PORT_RANGE_S stSrcPort;/*����Դ�˿ڷ�Χ*/
    ULONG ulDstPortOpType;
    ACL6_PORT_RANGE_S stDstPort;/*����Ŀ�Ķ˿ڷ�Χ*/
    
    UCHAR ucProtoBegin;     /* Э��ŷ�Χ��Сֵ */
    UCHAR ucProtoEnd;       /* Э��ŷ�Χ���ֵ */
    UCHAR ucClass;          /* Traffic Class */
    UCHAR ucHopLm;          /* Hop Limitֵ */
} ACL6_ADVANCE_CONTENT_INFO_S;

/*���ڽӿڹ������� ContentInfo*/
typedef struct tagAcl6IfbasedContentInfo
{
    ULONG ulAction;     /* ƥ��ɹ���Ķ��� */
    ULONG ulIfIndex;    /* �ӿ�������0xffffffffΪANY */
} ACL6_IFBASED_CONTENT_INFO_S;

/*������Ϣ*/
typedef struct tagAcl6RuleInfoOut
{
    ULONG ulTypeID;        /*��������ID*/
    ULONG ulGroupIndex;    /*����������*/
    ULONG ulRuleIndex;     /*��������*/
    ULONG ulCount;         /*ƥ��Ӧ�ü���*/
    union
    {
        ACL6_BASIC_CONTENT_INFO_S stBasicContentInfo;     /*����������Ϣ*/
        ACL6_ADVANCE_CONTENT_INFO_S stAdvContentInfo;     /*�߼�������Ϣ*/
        ACL6_IFBASED_CONTENT_INFO_S stIfBasedContentInfo; /*���ڽӿڹ�����Ϣ*/
    } stContent;
} ACL6_RULE_INFO_OUT_S;

/*��������Ϣ*/
typedef struct tagAcl6GetGroupInfo
{
    ULONG ulGroupIndex;                /* ����������*/
    ULONG ulTypeID;                    /* ��������ID 
                                          ACL6_BASIC_RULE_TYPE �� ����������
                                          ACL6_ADVANCE_RULE_TYPE �� �߼�������
                                          ACL6_IFBASED_RULE_TYPE �� ���ڽӿڵĹ�����*/
    ULONG ulMatchOrder;                /* ƥ��˳��:
                                          ACL6_MATCHORDER_CONFIG �� ����˳��
                                          ACL6_MATCHORDER_AUTO �� �Զ�˳�� */
    ULONG ulStep;                      /* ����*/
    CHAR  szDescription[ACL6_DESCRIPTIONSTR_LEN + 1];   /* ������Ϣ */
    ULONG ulRuleNum;                   /* ������Ŀ */
} ACL6_GET_GROUP_INFO_S;

/* ACL6 ���ڽӿڹ�������ṹ*/
typedef struct tagAcl6ClassifyByIfIn
{
    ULONG ulInIfIndex;
    ULONG ulOutIfIndex;
    ULONG ulIfType;             /*�ӿڹ�������
                                      ACL6_IFIN �� ��ӿڹ��� 
                                      ACL6_IFOUT �� ���ӿڹ���
                                      ACL6_IFANY �� �����ӿڹ���*/
    ULONG ulGroupIndex;
} ACL6_CLASSIFY_IF_IN_S;

/* ACL6 ���ڽӿڹ�������ṹ*/
typedef struct tagAcl6ClassifyByIfOut
{
    ULONG ulAction;     /* ƥ��ɹ���Ķ��� 
                           ACL6_DENY �� Deny
                           ACL6_PERMIT �� Permit*/
    ULONG ulRuleIndex;  /*��������*/
} ACL6_CLASSIFY_IF_OUT_S;


/* ACL6 ���ڻ���/�߼������������ṹ*/
typedef struct tagAcl6ClassifyByIpIn
{
    VOID *pPktHdr;
    ULONG ulGroupIndex;
    ULONG ulVrfIndex; 
    ULONG ulIgnoreByte;   /*�ȽϺ����ֶ�
                                ACL6_SIPByte ������Դ��ַ
                                ACL6_DIPByte ������Ŀ�ĵ�ַ
                                ACL6_PROByte ������Э������
                                ACL6_HLMByte ������Hop Limit
                                ACL6_CLSByte ������Traffic Class
                                ACL6_SPORTByte ������Դ�˿�
                                ACL6_DPORTByte ������Ŀ�Ķ˿�
                                ACL6_VRFByte ������vrf*/
} ACL6_CLASSIFY_IP_IN_S;

/* ACL6 ���ڻ���/�߼������������ṹ*/
typedef struct tagAcl6ClassifyByIpOut
{
    ULONG ulAction;     /* ƥ��ɹ���Ķ��� 
                           ACL6_DENY �� Deny
                           ACL6_PERMIT �� Permit*/
    ULONG ulRuleIndex;  /*��������*/
} ACL6_CLASSIFY_IP_OUT_S;

/* ��Ʒ��Ҫʹ��ACL6_IP6_S,�����api.h�ж���һ��,ע��ṹ�������acl6_pub.h�е�ACL6_IP6_S���屣��һ�� */
/*IPv6������ͷ*/
#ifndef _ACL6_IP6_S
#define _ACL6_IP6_S
typedef struct tagACL6_Ip6
{
    ULONG ulTclassFlow;      /* 4 bits version, 8 bits traffic class and 20 bits of flow-ID */
    USHORT usPayLen;         /* 16 bits payload length */
    UCHAR ucNextHd;          /* 8 bits next header */
    UCHAR ucHopLm;           /* 8 bits hop limit */
    UCHAR szSrcAddr[ACL6_IPV6_ADDR_LEN];            /* ԴIPv6��ַ */            
    UCHAR szDstAddr[ACL6_IPV6_ADDR_LEN];            /* Ŀ��IPv6��ַ */ 
} ACL6_IP6_S;
#endif

/**********************************************************
*   �û�API����
***********************************************************/
/*******************************************************************************
*    Func Name: ACL6_ManageGroup
* Date Created: 2009-04-08
*       Author: hanna55555
*  Description:���/ɾ��/�޸Ĺ����顣
*        Input: ACL6_CFG_MANAGEGROUP_S *pstManageGroup:��������Ϣ
*       Output: 
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_WAITLIST_CloseFail : �ر�waitlistʧ��
*                    Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_ManageGroup(ACL6_CFG_MANAGEGROUP_S *pstManageGroup);
/*************************************************************************
*    Func Name: ACL6_ManageBasicRule
*  Description: ����ACL6�������ýӿ�(����һ���¹�������һ���Ѵ��ڵĹ���)
*        Input: ACL6_CFG_BASIC_RULE_S *pstAcl6_BasicRule������acl6������Ϣ
*       Output: ��
*       Return: Help_ACL6_OK,Help_ACL6_ERR,������
*      Caution: ��
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageBasicRule(ACL6_CFG_BASIC_RULE_S* pstAcl6_BasicRule);
/*************************************************************************
*    Func Name: ACL6_ManageAdvRule
*  Description: �߼�ACL6�������ýӿ�(����һ���¹�������һ���Ѵ��ڵĹ���)
*        Input: ACL6_CFG_ADV_RULE_S* pstAcl6_AdvRule���߼�������Ϣ
*       Output: ��
*       Return: Help_ACL6_OK,Help_ACL6_ERR,������
*      Caution: ��
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageAdvRule(ACL6_CFG_ADV_RULE_S* pstAcl6_AdvRule);
/*************************************************************************
*    Func Name: ACL6_ManageIfBasedRule
*  Description: �ӿ�ACL6�������ýӿ�(����һ���¹�������һ���Ѵ��ڵĹ���)
*        Input: ACL6_CFG_IFBASED_RULEINFO_S* pstAcl6_IfBaseRule�����ڽӿڵ�acl6������Ϣ
*       Output: ��
*       Return: Help_ACL6_OK,Help_ACL6_ERR,������
*      Caution: ��
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern ULONG ACL6_ManageIfBasedRule(ACL6_CFG_IFBASED_RULEINFO_S* pstAcl6_IfBaseRule);
/*******************************************************************************
*    Func Name: ACL6_ClassifyByIfInfo
*  Description: �жϽӿ������Ƿ�����һ���ӿ�ACL6����������,������ƥ��Ľڵ��
*        Input: pstAcl6_ClassifyIn   ��ƥ����Ϣ
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    ƥ���ACL6����ĵڼ����ڵ�
*               pstAcl6_ClassifyOut->ulLog           ƥ���ACL6����Ľڵ��"�Ƿ���־"��
*       Return: ACL6_PERMIT      ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"permit"
*               ACL6_DENY        ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"deny"
*               Help_ACL6_RuleNotFound    �͸�ACL��������нڵ㶼��ƥ��, pulSubitem������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_ClassifyByIfInfo(ACL6_CLASSIFY_IF_IN_S* pstAcl6_ClassifyIn,
                                         ACL6_CLASSIFY_IF_OUT_S* pstAcl6_ClassifyOut);
/*******************************************************************************
*    Func Name: ACL6_ClassifyByIpInfo
*  Description: �ж�һ�������Ƿ�����һ��ACL6 Group����������,������ƥ��Ľڵ��
*        Input: pstAcl6_ClassifyIn   ��ƥ����Ϣ
*       Output: pstAcl6_ClassifyOut->ulRuleIndex    ƥ���ACL6����ĵڼ����ڵ�
*               pstAcl6_ClassifyOut->ulLog           ƥ���ACL6����Ľڵ��"�Ƿ���־"��
*       Return: ACL6_PERMIT      ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"permit"
*               ACL6_DENY        ƥ���Ҹ�ƥ��ڵ�Ķ���Ϊ"deny"
*               Help_ACL6_RuleNotFound    �͸�ACL6��������нڵ㶼��ƥ��, pulSubitem������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*
*******************************************************************************/
extern ULONG ACL6_ClassifyByIpInfo(ACL6_CLASSIFY_IP_IN_S* pstAcl6_ClassifyIn,
                                          ACL6_CLASSIFY_IP_OUT_S* pstAcl6_ClassifyOut,
                                          ULONG ulFlag);

/* ��������ӿ� */
/*******************************************************************************
*    Func Name: ACL6_Init
* Date Created: 2009-04-08
*       Author: hanna55555
*  Description: ��ʼ��ACL6����������ȱʡ������ָ��
*        Input: ULONG ulMID:ģ��ID
*       Output: 
*       Return: Help_ACL6_INIT_ERR : ACL CBB�Ѿ���ɳ�ʼ��
*                   Help_ACL6_ERR_CreateSm :�����ź���ʧ��
*                   Help_ACL6_TYPE_BASIC_MallocErr : Ϊ�����������ͷ����ڴ�ʧ�� 
*                   Help_ACL6_GROUP_BASIC_MallocErr : Ϊ��������������ڴ�ʧ��
*                   Help_ACL6_TYPE_ADV_MallocErr :  Ϊ�߼��������ͷ����ڴ�ʧ�� 
*                   Help_ACL6_GROUP_ADV_MallocErr : Ϊ�߼�����������ڴ�ʧ�� 
*                   Help_ACL6_TYPE_IF_MallocErr : Ϊ���ڽӿڹ������ͷ����ڴ�ʧ�� 
*                   Help_ACL6_GROUP_IF_MallocErr : Ϊ���ڽӿڵĹ���������ڴ�ʧ�� 
*                   Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_Init(ULONG ulMID);
/*******************************************************************************
*    Func Name: ACL6_GetVersion
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: ��ȡACL6�İ汾��
*        Input: CHAR *pszVerInfo:�汾��Ϣ
*       Output: 
*       Return: Help_ACL6_NullPoint:����ָ��Ϊ�� 
*                   Help_ACL6_OK: �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetVersion(CHAR *pszVerInfo);
/*******************************************************************************
*    Func Name: ACL6_ShowVersion
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: ��ʾACL6�汾����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: ACL6_GetGroupInfo
* Date Created: 2009-04-13
*       Author: hanna55555
*  Description: 
*        Input: ACL6_FILTER_S *pstACL6Filter:
*               ACL6_GET_GROUP_INFO_S *pstGroupInfo:
*       Output: 
*       Return: Help_ACL6_NotInit :ACL CBBδ�ɹ���ʼ��
*                   Help_ACL6_NullPoint : ����ָ��Ϊ��
*                   Help_ACL6_GroupIndexError :�������������� 
*                   Help_ACL6_GroupNotExist :�����鲻����
*                   Help_ACL6_OK :�ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-13   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetGroupInfo(ACL6_FILTER_S *pstACL6Filter,ACL6_GET_GROUP_INFO_S *pstGroupInfo);
/*******************************************************************************
*    Func Name: ACL6_GetGroupSum
* Date Created: 2009-04-14
*       Author: hanna55555
*  Description: ��ȡ�����й���Ĺ���������
*        Input: 
*       Output: ULONG *pulGroupSum:����������
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-14   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetGroupSum(ULONG *pulGroupSum);
/*******************************************************************************
*    Func Name: ACL6_ShowGroupSum
* Date Created: 2009-04-09
*       Author: hanna55555
*  Description: 
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-09   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowGroupSum(VOID);
/*******************************************************************************
*    Func Name: ACL6_GetRuleInfo
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ȡָ��������ָ������Ĺ�����Ϣ
*        Input: ACL6_FILTER_S *pstACL6Filter:������
*                  pstACL6Filter->ulGroupIndex:����������������ָ��
*                  pstACL6Filter->ulRuleIndex:��������������ָ��
*       Output: ACL6_RULE_INFO_OUT_S *pstRuleInfo:������Ϣ
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetRuleInfo(ACL6_FILTER_S *pstACL6Filter,ACL6_RULE_INFO_OUT_S *pstRuleInfo);
/*******************************************************************************
*    Func Name: ACL6_GetRuleSum
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ȡ���й�������
*        Input: ULONG *pulRuleSum:��������
*       Output: 
*       Return:  Help_ACL6_NotInit : ACL CBBδ�ɹ���ʼ��
*                    Help_ACL6_NullPoint : ����ָ��Ϊ��
*                    Help_ACL6_OK : �ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-23   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_GetRuleSum(ULONG *pulRuleSum);
/*******************************************************************************
*    Func Name: ACL6_ShowRuleSum
* Date Created: 2009-04-16
*       Author: hanna55555
*  Description: ��ʾ��������
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-16   hanna55555              Create
*
*******************************************************************************/
extern VOID ACL6_ShowRuleSum(VOID);
/*******************************************************************************
*    Func Name: ACL6_ClearMatchStat
* Date Created: 2009-04-14
*       Author: hanna55555
*  Description: ���ȫ����ָ�������������л�ָ�������ƥ��ͳ����Ϣ
*        Input: ACL6_FILTER_S *pstACL6Filter:������Ϣ
*       Output: 
*       Return: Help_ACL6_NotInit:  ACL CBBδ�ɹ���ʼ��
*                   Help_ACL6_GroupIndexError : ��������������
*                   Help_ACL6_OK:�ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-14   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_ClearMatchStat(ACL6_FILTER_S *pstACL6Filter);
/*******************************************************************************
*    Func Name: ACL6_CheckGroupRuleExist
* Date Created: 2009-04-10
*       Author: hanna55555
*  Description: �������鼰�����Ƿ��Ѵ���
*        Input: ACL6_FILTER_S *pstACL6Filter:������Ϣ
*       Output: 
*       Return: Help_ACL6_NotInit: ACL CBBδ�ɹ���ʼ��
*                   Help_ACL6_NullPoint:����ָ��Ϊ��
*                   Help_ACL6_GroupIndexError:�������������� 
*                   Help_ACL6_GroupNotExist:�����鲻����
*                   Help_ACL6_RuleNotExist:���򲻴��� 
*                   Help_ACL6_OK:�ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-10   hanna55555              Create
*
*******************************************************************************/
extern ULONG ACL6_CheckGroupRuleExist(ACL6_FILTER_S *pstACL6Filter);
/*************************************************************************
*    Func Name: ACL6_IFDelete
*  Description: ɾ���ӿ�ʱ�����ñ�������ɾ�����л��ڽӿڵ�acl����
*        Input: ULONG ulIfIndex Ҫɾ���Ľӿ�����
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------*
*  Modification History
*  DATE        NAME             DESCRIPTION
*------------------------------------------------------------------------*
*
*************************************************************************/
extern VOID ACL6_IFDelete(ULONG ulIfIndex);

#ifdef  __cplusplus
}
#endif
   
#endif

