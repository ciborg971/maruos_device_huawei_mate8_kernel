/*************************************************************************
 *
 *              Copyright 2009, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              acl6_pub.h
 *
 *  Project Code: VISP1.8
 *   Module Name: ACL6
 *  Date Created: 
 *        Author: 
 *   Description: ���ݽṹ�Ķ���
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 ************************************************************************/
#ifndef _ACL6_PUB_H_
#define _ACL6_PUB_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "acl6/include/acl6_cbb_api.h"



/* ACL6���� */
typedef struct tagACL6_RuleNode
{
    VOID  *pContent;                        /* �������ݣ�����ACL6��������;��� */
    ULONG  ulRuleIndex;                     /* �������� */
    ULONG  ulCount;                         /* ƥ��ù���Ĵ��� */
    struct tagACL6_RuleNode * pstNode;      /* ��һ������ */
}ACL6_RULE_NODE_S;

/* ACL6������ */
typedef struct tagACL6_Group
{
    ULONG ulVer;                    /* �ݲ�ʹ�ã�������չ */
    ULONG ulMatchOrder;             /* ƥ��˳��:0-����˳��,1-�Զ�˳�� */
    ULONG ulRuleNum;                /* �ù����������еĹ������� */
    ULONG ulGroupIndex;             /* ��������� */
    ULONG ulTypeID;                 /* ������������ID */

    ACL6_RULE_NODE_S *pRuleNode;    /* �������������ͷ */
    CHAR *pACL6Description;         /* �ù������������Ϣ */
    ULONG ulIndexStep;              /* �ù�����Ĳ��� */
    ULONG ulNextRuleIndex;          /* ������Ĺ������� */
    ULONG ulRuleNodeSize;           /* �������ݵĴ�С,ָpRuleNode->pCoutent�����ݴ�С */
} ACL6_GROUP_S;

/* ACL6�������� */
typedef struct tagAcl6_Type
{
    ULONG ulTypeID;         /* ��������ID��1��16�� */
    ULONG ulLowNo;          /* ������������� */
    ULONG ulUpNo;           /* ������������� */
    ULONG ulRuleNodeSize;   /* �������ݵĴ�С */
    /* �Ƚ������ڵ��Ƿ���ͬ */
    ULONG (*pFuncComp)(VOID *, VOID *); 
    /* �жϹ����Ƿ���ʲ���ĳ����֮ǰ��ǰһ�������Ǵ�������򣬺�һ�������Ǳ�������� */
    ULONG (*pFuncBefore)(VOID *, VOID *); 
    /* �Ƚ�һ������ڵ��Ƿ�Ͱ�ƥ�䣬ǰһ�������ǹ������ݣ���һ�������Ǵ�ƥ�䱨����Ϣ */
    ULONG (*pFuncRuleComp)(VOID *, VOID *); 
    /* ����һ������ڵ� */
    VOID* (*pFuncCreateNode)();
    /* �ͷ�һ������ڵ� */
    VOID (*pFuncReleaseNode)(VOID*);    
    ACL6_GROUP_S **ppstGroup;/* ������ָ������ */
} ACL6_TYPE_S;

/* ACL6�߼�����˿ںż�Э����Ϣ���ṹ */
typedef struct tagACL6_CheckProPort
{
    UCHAR ucProtoBegin;
    UCHAR ucProtoEnd;
    UCHAR ucPadding[2];
    ULONG ulPortOpType;
    ACL6_PORT_RANGE_S stPort;
} ACL6_CHECK_PRO_PORT_S;

/* ACL6�������ݽṹ��� */
typedef struct tagACL6_AccessList
{
    ULONG ulACL6GroupSum;
    ACL6_TYPE_S* pstACL6Type[ACL6_MAX_TYPEID + 1];   
} ACL6_ACCESSLIST_S;


/* ��IPv6��������ȡ����Ϣ */
typedef struct tagIP6PacketInfo 
{
    UCHAR szSrcAddr[ACL6_IPV6_ADDR_LEN];            /* ԴIPv6��ַ */            
    UCHAR szDstAddr[ACL6_IPV6_ADDR_LEN];            /* Ŀ��IPv6��ַ */ 
    USHORT usSrcPort;            /* Դ�˿ں� or ICMPv6 Type*/            
    USHORT usDstPort;            /* Ŀ�Ķ˿ں� or ICMPv6 Code*/            
    UCHAR ucFO;                  /* True - ����Ƭ�ķ�Ƭ���� 
                                                                 False - ��Ƭ�ķ�Ƭ���Ļ򲻷�Ƭ����*/
    UCHAR ucProto;               /* Э��ŷ�Χ���ֵ */
    UCHAR ucClass;               /* Traffic Class */
    UCHAR ucHopLm;               /* Hop Limitֵ */
    ULONG ulIfIndex;             /* �ӿ����� */ 
    ULONG ulVrfIndex;            /* Vrf index */
    ULONG ulIgnoreByte;          /* ���ԱȽ��ֶ� */
} IP6PACKETINFO_S;

/* ��Ʒ��Ҫʹ��ACL6_IP6_S,�����api.h��Ҳ������һ��,ע��ṹ�������acl6_cbb_api.h�е�ACL6_IP6_S���屣��һ�� */
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

/*IPv6��չ��ͷ*/
typedef struct tagACL6_Ip6NextHd
{
    UCHAR ucNextHd;      /* 8 bits next header */
    UCHAR ucHdLen;       /* 8 bits header length*/
} ACL6_IP6_NEXT_HD_S;

/* Fragment Header */
typedef struct tagACL6_Ip6Frag
{
    UCHAR  ucNextHd;     /* next header */
    UCHAR  ucReserved;   /* reserved field */
    USHORT usOfflg;      /* 13 bits offset, 2 bits reserved, 1 bit M flag */
    ULONG  ulIdent;      /* identification */
}ACL6_IP6_FRAG_S;

/* UDP6 Header*/
typedef struct tagACL6_Udp6Hd
{
    USHORT    usSrcPort;        /* source port */
    USHORT    usDstPort;        /* destination port */
    SHORT     sULen;          /* udp length */
    USHORT    usSum;          /* udp checksum */
}ACL6_UDP6_S;

/*TCP6 Header*/
typedef struct tagACL6_Tcp6Hd
{
    USHORT usSrcPort;
    USHORT usDstPort;
    ULONG ulSeqNumber;
    ULONG ulAckNumber;
#if (VRP_LITTLE_ENDIAN == VRP_YES)
    UCHAR ucX2:4,
    ucOffset:4;
#else
    UCHAR ucOffset:4, /* warning:nonstandard extn used :bit field types other than LONG. */
    ucX2:4;             /* warning:nonstandard extn used : bit field types other than LONG. */
#endif
    UCHAR ucFlags;
    USHORT usWnd;
    USHORT usCheckSum;
    USHORT usUrgentPoint;
} ACL6_TCP6_S;

/*ICMP6 Header*/
typedef struct tagACL6_Icmp6Hd
{
    UCHAR  ucType;           /* type of message, see below */
    UCHAR  ucCode;           /* type sub code */
    USHORT usChksum;         /* ones complement cksum of struct */
    UCHAR  ucData[4];        /* type-specific field */
} ACL6_ICMP6_S;

/* ACL6����˿ں�ƥ��ʹ�ýṹ�� */
typedef struct tagACL6_CheckPort
{
    USHORT usPktPort;
    UCHAR ucPadding[2];
    ULONG ulPortOpType;
    ACL6_PORT_RANGE_S stPort;
} ACL6_CHECK_PORT_S;


typedef struct tagACL6_Item
{
    ACL6_IP6ADDR_S stSrcIp;/* Դ��ַ */
    ACL6_IP6ADDR_S stDstIp;/* Ŀ�ĵ�ַ */
    UCHAR           ucPID;  /* Э��� */
    UCHAR           ucPadding[3];
    USHORT          usSP;   /* Դ�˿ںţ������� */
    USHORT          usEndSP;   /* Դ�˿ںţ������� */
    USHORT          usDP;   /* Ŀ�Ķ˿ںţ������� */
    USHORT          usEndDP;   /* Ŀ�Ķ˿ںţ������� */
    ULONG           ulVrfIndex; /* ָ��VRF�����ƥ��������VrfIndex����Ϊ0xFFFFFFFFL,���û��ʹ��VRF����д0 */
} ACL6_Item, * PACL6_Item;

#ifndef _ACL6CONFIG_S
#define _ACL6CONFIG_S
typedef struct tagAcl6Config
{
    ULONG ulAclNumMin;          /* ��С��������� */
    ULONG ulAclNumMax;          /* ����������� */
    ULONG ulAclBasMinExt;       /* ��С������������� */
    ULONG ulAclBasMaxExt;       /* ��������������� */
    ULONG ulAclAdvMinExt;       /* ��С��չ��������� */
    ULONG ulAclAdvMaxExt;       /* �����չ��������� */
    ULONG ulIpAddrAny[LEN_4];          /* ��ַͨ��� */
    ULONG ulAclDeny;            /* acl denyȡֵ */
    ULONG ulAclPermit;          /* acl permitȡֵ */
    ULONG ulAclNotfound;        /* acl notfoundȡֵ */
} ACL6CONFIG_S, *PACL6CONFIG_S;
#endif

/*acl6 �仯֪ͨ*/
#define ACL6_UPDATE_GROUP_DELETE         1
#define ACL6_UPDATE_RULE_DELETE          2
#define ACL6_UPDATE_RULE_MODIFY          3
#define ACL6_UPDATE_RULE_ADD             4
#define ACL6_UPDATE_GROUP_DELETE_ALL     5


#ifndef _PF_ACL6_REFRESHCALLBACK
#define _PF_ACL6_REFRESHCALLBACK
/*Ϊ0 ��ʾ�������е�*/
typedef VOID (*PF_ACL6_REFRESHCALLBACK)(ULONG ulGroupId, ULONG ulRuleId, ULONG ulEventType);
#endif

typedef struct tagACL6_UPDATE_CALLBACK_NODE
{
    PF_ACL6_REFRESHCALLBACK pfCallBack;
    ULONG ulModuleId;
    struct tagACL6_UPDATE_CALLBACK_NODE *pstNext;
}ACL6_UPDATE_CALLBACK_NODE_S;

#ifdef  __cplusplus
}
#endif

#endif
