/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ipsfe_msg.h
*
*  Project Code: VISPV100R008C02
*   Module Name: ipsfe_msg 
*  Date Created: 2009-8-21
*        Author: zhangchunyu(62474)
*   Description: ������Ϳ����湫��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                      DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-7-28  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _IPSFE_MSG_H_
#define _IPSFE_MSG_H_

#ifdef __cplusplus
    extern "C"{
#endif

/* �����淢����������Ϣ����,��ӦMSG_HEADER��u16MsgType�ֶ�,�޸ĸö���ʱ,
   ��ע���޸�g_ai8TCPIPSFE_MsgTypeInfo��g_ai8SFE_MsgTypeInfo�ַ�������Ϣ */
enum enMsgType
{
    MSG_TYPE_NPCFG,     /* NP PPI�·����� */
    MSG_TYPE_NP_TABLE,  /* ��ȡPOOL��Դ����Ϣ */
    MSG_TYPE_NP_NPPI,   /* ��PPI����Ϣ���� */
    
    MSG_TYPE_NP_MAX,    /* MAX */
};

/* �����淢��������ģ������,��ӦMSG_ITEM_HEADER_S��u8MoudleID�ֶ�,
   �޸���ɾģ��IDʱ,��Ҫ�޸���ɾ��Ӧ��g_SfeDispatchMsg��g_SfeNPpiDispatchMsg�ַ���������
   �޸�g_ai8TCPIPSFE_ModuleTypeInfo��g_ai8SFE_ModuleTypeInfo��Ӧ�ַ�������Ϣ*/
enum enMoudleType
{
    MOUDLE_TYPE_IFNET,
    MOUDLE_TYPE_ROUTE,
    MOUDLE_TYPE_ARP,
    MOUDLE_TYPE_BFD,
    MOUDLE_TYPE_ICMP,
    MOUDLE_TYPE_ACL,
    MOUDLE_TYPE_IP,
    MOUDLE_TYPE_DEBUG,
    MOUDLE_TYPE_PUB,
    MOUDLE_TYPE_MAX,
};

/* �����浽�������������� */
enum enSfeTableOpType
{  
    SFE_TABLE_OPEN,
    SFE_TABLE_GET_DATA,
    SFE_TABLE_CLOSE,
    SFE_TABLE_OP_MAX,    
};

/* �����淢����������Ϣ����,��ӦMSG_HEADER��u16MsgType�ֶ� */
enum enSfeToCtlMsgType
{
    SFE_MSG_EVENT,
    SFE_MSG_NP_ACK,
};

/* �����淢��������ģ������,��ӦMSG_ITEM_HEADER_S��u8MoudleID�ֶ� */
enum enSfeToCtlMoudleType
{
    SFE_ARP_MOUDLE,
    SFE_BFD_MOUDLE,
    SFE_MAX_MOUDLE,
};

/* �����浽�������������,�޸ĸö���ʱ,
   ��ע���޸�g_ai8TCPIPSFE_EventTypeInfo��g_ai8SFE_EventTypeInfo�ַ�������Ϣ */
enum enOpTypeCtl
{  
    SFE_ARP_MISS_EVENT,             /* ARP MISS֪ͨ */
    SFE_BFD_DETECT_DOWN_EVENT,      /* BFD̽�⵽�ỰDOWN֪ͨ */
    
    SFE_MAX_EVENT,                  /* �������ϱ��¼���Ϣ���ͱ߽���Чֵ */
};

/* NPPI(��PPI)��Ϣ�����µĲ��������� */
enum enSfeNPpiType
{
    /* ARP���������� */
    SFE_NPPI_ARP_GET,                       /* ָ��ID��ȡARP��Ϣ */
    SFE_NPPI_ARP_SHOWALLARPINFO,            /* ��ʾ����ARP���� */
    SFE_NPPI_ARP_SHOWARPINFOBYVRF,          /* ����VRF��ʾARP */
    SFE_NPPI_ARP_SHOW_ONEARPINFO,           /* ����VRF��IP��ʾARP */

    /* �ӿڴ��������� */
    SFE_NPPI_IF_GET,                        /* ָ��ID��ȡ�ӿ���Ϣ */
    SFE_NPPI_IF_SET_ETH_ARPMISSSWITCH,      /* ������̫�ӿڵ�ARP MISS���� */
    SFE_NPPI_IF_SET_REDUCETTLSWITCH,        /* ���ýӿ�TTL�Ƿ��һ���� */
    SFE_NPPI_IF_SHOWALLIFINFO,              /* ��ʾ���нӿ���Ϣ */
    SFE_NPPI_IF_SHOWBYID,                   /* ���ݽӿ�ID��ʾ�ӿ���Ϣ */

    /* ROUTE���������� */
    SFE_NPPI_ROUTE_GET,                     /* ָ����ȡ·����Ϣ */
    SFE_NPPI_ROUTE_SHOWALLINFO,             /* ��ʾ����·����Ϣ */
    SFE_NPPI_ROUTE_SHOWBYIP,                /* ��ʾָ��IP·����Ϣ */

    /* BFD���������� */
    SFE_NPPI_BFD_GET,                       /* ָ��ID��ȡBFD�Ự��Ϣ */
    SFE_NPPI_BFD_SET_DEBUG_SWITCH,          /* ���û���BFD�ĵ��Կ��� */
    SFE_NPPI_BFD_GET_DEBUG_SWITCH,          /* ��ȡ����BFD�ĵ��Կ��� */
    SFE_NPPI_BFD_SHOWALLBFDINFO,            /* ��ʾ����BFD��Ϣ*/
    SFE_NPPI_BFD_SHOWBFDINFO_BYVRF,         /* ��ʾָ��VRF�µ�����BFD�Ự��Ϣ */
    SFE_NPPI_BFD_SHOWBFDINFO_BYID,          /* ��ʾָ��VRF�ỰID��BFD�Ự��Ϣ */
    SFE_NPPI_BFD_CLEAR_STATISTIC,           /* ��0ָ��BFD�Ự��ͳ����Ϣ */
    SFE_NPPI_BFD_GET_STATISTIC,             /* ��ȡָ��BFD�Ự��ͳ����Ϣ */
    SFE_NPPI_BFD_SHOW_STATISTIC,            /* ��ʾָ��BFD�Ự��ͳ����Ϣ */
    
    
    /* ICMP���������� */
    SFE_NPPI_ICMP_SETSWITCH,                /* ����ICMP����ĵ��Կ��� */
    SFE_NPPI_ICMP_GETSWITCH,                /* ��ȡICMP����ĵ��Կ��� */
    
    /* IP���������� */
    SFE_NPPI_IP_SETRTID,                    /* ����Router ID */
    SFE_NPPI_IP_GETRTID,                    /* ��ȡRouter ID */

    /* ͳ�ƴ��������� */
    SFE_NPPI_STAT_GET_ALLINFO,              /* ��ȡȫ��ͳ�����������Ϣ,�����洢ͳ�������Ϣ�ĵ�ַ */    
    SFE_NPPI_STAT_SHOW_ALLSTAT,             /* ��ʾ�����ܵ�ȫ��ͳ����Ϣ */
    SFE_NPPI_STAT_SHOW_AUTOSTAT,            /* ��ʾȫ���Զ�ͳ����Ϣ */
    SFE_NPPI_STAT_SHOW_MANUALSTAT,          /* ��ʾȫ�ָ�VCPU�ֶ�ͳ����Ϣ֮��,���ܵ��ֶ�ͳ����Ϣ */
    SFE_NPPI_STAT_SHOW_MANUALSTATBYVCPU,    /* ��ʾָ��VCPU��ȫ���ֶ�ͳ����Ϣ */
    SFE_NPPI_STAT_CLEAR_ALLSTAT,            /* �������ȫ��ͳ����Ϣ */

    /* ��ͳ�ƴ��������� */
    SFE_NPPI_FLOWSTAT_SET_SWITCH,           /* ������ͳ�ƿ��� */
    SFE_NPPI_FLOWSTAT_GET_SWITCH,           /* ��ȡ��ͳ�ƿ��� */
    SFE_NPPI_FLOWSTAT_SHOW_SWITCH,          /* ��ʾ��ͳ�ƿ��� */
    SFE_NPPI_FLOWSTAT_CFG_FLOWRULE,         /* ������ͳ�ƹ��� */
    SFE_NPPI_FLOWSTAT_GET_RULENUM,          /* ��ȡ���������� */
    SFE_NPPI_FLOWSTAT_GET_ALLINFO,          /* ��ȡ��ͳ�����������Ϣ,�����洢��ͳ�������Ϣ�ĵ�ַ */

    SFE_NPPI_FLOWSTAT_SHOW_ALLRULE,         /* ��ʾ������ͳ�ƹ��� */    
    SFE_NPPI_FLOWSTAT_SHOW_RULE_BYFLOWID,   /* ��ʾָ����ID����ͳ�ƹ��� */
    
    SFE_NPPI_FLOWSTAT_SHOW_ALLSTAT,         /* ��ʾ������ͳ����Ϣ */    
    SFE_NPPI_FLOWSTAT_SHOW_STAT_BYRULE,     /* ��ʾָ���������ͳ����Ϣ */
    SFE_NPPI_FLOWSTAT_SHOW_STAT_BYFLOWID,   /* ��ʾָ����ID����ͳ����Ϣ */

    SFE_NPPI_FLOWSTAT_CLEAR_ALLSTAT,        /* ���������ͳ����Ϣ */
    

    /* ���Դ��������� */
    SFE_NPPI_DEBUG_SET_DEBUGTYPE,           /* ����Debug���Ϳ��� */
    SFE_NPPI_DEBUG_SET_DEBUGVCPU,           /* ����vcpu Debug���Ϳ��� */
    SFE_NPPI_DEBUG_SET_DEBUGMODU,           /* ����ģ��Debug���� */
    SFE_NPPI_DEBUG_GET_DEBUGSWITCH,         /* ��ȡDebug���� */
    SFE_NPPI_DEBUG_SETMSGOREVT_DEBUGSWITCH, /* ������Ϣ���¼����Կ��� */
    SFE_NPPI_DEBUG_GETMSGOREVT_DEBUGSWITCH, /* ��ȡ��Ϣ���¼����Կ��� */
    SFE_NPPI_DEBUG_SETVERBOSE_DEBUG,        /* ������ϸ���Եı��Ĵ��������ĳ��� */
    SFE_NPPI_DEBUG_GETVERBOSE_DEBUG,        /* ��ȡ��ϸ���Եı��Ĵ��������ĳ��� */
    SFE_NPPI_DEBUG_SHOW_DEBUGSWITCH,        /* ��ʾ���Կ�����Ϣ */

    /* ��־���� */
    SFE_NPPI_LOG_SET_LOGLEVEL,              /* ������־���� */
    SFE_NPPI_LOG_SET_LOGTYPE,               /* ������־���� */
    SFE_NPPI_LOG_SHOW_LOGSWITCH,            /* ��ʾ��־���� */

    /* ������������ */
    SFE_NPPI_PUB_SHOW_VERSION,              /* ��ʾ������汾�� */
    SFE_NPPI_PUB_SHOW_PRECONFIG,            /* ��ʾ������Ԥ������Ϣ */
    SFE_NPPI_PUB_SHOW_SHAREMEMID,           /* ��ʾ�����湲���ڴ�ID��Ϣ */
    SFE_NPPI_PUB_SHOW_STUBMODULE,           /* ��ʾ������ģ��ü���� */
    SFE_NPPI_PUB_SET_ACLFAKEREASS,          /* ����ACL�����Ƿ���Ҫ��������м����鿪�� */
    SFE_NPPI_PUB_GET_ACLFAKEREASS,          /* ��ȡACL�����Ƿ���Ҫ��������м����鿪�� */
    SFE_NPPI_PUB_SHOW_ACLFAKEREASS,         /* ��ʾACL�����Ƿ���Ҫ��������м����鿪�� */
    SFE_NPPI_PUB_SHOW_MSGSEQ,               /* ��ʾ��������Ϣ��� */
    SFE_NPPI_PUB_SET_OUTPUT_TOCOM,          /* ���������������com�ڵĿ��� */
    
};

/* ��Ϣ������ͷ��С */
#define TCPIP_SFE_MSG_HEADER_LEN   (sizeof(MSG_HEADER) + sizeof(MSG_ITEM_HEADER_S))

/* �����Ϣͷ */
#define SET_MSG_HEAD(pstMsgHdr,u16MsgTypeH,u16MsgLenH,u32SeqH,u8OriginH)\
{\
    (pstMsgHdr)->u16MsgType = (u16MsgTypeH);\
    (pstMsgHdr)->u16MsgLen  = (u16MsgLenH);\
    (pstMsgHdr)->u32Ver     = 0;\
    (pstMsgHdr)->u32Seq     = (u32SeqH);\
    (pstMsgHdr)->u8Pri      = 0;\
    (pstMsgHdr)->u8Origin   = (u8OriginH);\
    (pstMsgHdr)->u16Chksum  = 0;\
}

/* �������Ϣͷ */
#define SET_MSG_ITEMHDR(pstItem,u8MoudleIDH,u8OperTypeH,u16ItemLenH)\
{\
    (pstItem)->u8MoudleID = (u8MoudleIDH);\
    (pstItem)->u8OperType = (u8OperTypeH);\
    (pstItem)->u16ItemLen = (u16ItemLenH);\
}

/* ������Ϳ�����ͨ����Ϣ����ͷ */
typedef struct tagMsgHead
{
    UINT16   u16MsgType;             /* ��Ϣ���� */
    UINT16   u16MsgLen;              /* ��Ϣ�ܳ��� */
    UINT32   u32Ver;                 /* SFE�汾�� */
    UINT32   u32Seq;                 /* SFE������Ϣ��� */
    UINT8    u8Pri;                  /* ���ȼ� */
    UINT8    u8Origin;               /* ������Դ */
    UINT16   u16Chksum;              /* У���, ȱʡΪ0 */
}MSG_HEADER;

/* ������Ϳ�����TL, �������������V */
typedef struct tagItem
{
    UINT8   u8MoudleID;              /* ģ��ID */
    UINT8   u8OperType ;             /* �������� */
    UINT16  u16ItemLen;              /* ��Ϣ���� */
}MSG_ITEM_HEADER_S;

/* �����淢��������OPEN TABLE������ݽṹ */
typedef struct tagSfeOpen
{
    UINT32 u32TableType;
    UINT32 u32VrfIndex;
}TCPIP_SFE_OPEN_S;

/* ������ظ�OPEN TABLE������ݽṹ */
typedef struct tagSfeOpenRet
{
    UINT32 u32Ret;
    UINT32 u32Handle;
}SFE_OPEN_RET_S;

/* �����淢��������GET TABLE DATA������ݽṹ */
typedef struct tagSfeGet
{
    UINT32 u32Handle;        
    UINT32 u32GetNum;
    UINT32 u32BufLen;
}TCPIP_SFE_GET_S;

/* ������ظ�GET TABLE DATA������ݽṹ */
typedef struct tagSfeGetRet
{
    UINT32 u32Ret;
    UINT32 u32Len;
    UINT32 u32Num;
}SFE_GET_RET_S;

/* �������Ӧ�Ŀ�����PPI������Ϣ�ַ��������Ͷ���*/
typedef UINT32 (*MsgDispatchFuncPtr)(VOID *pstMsg);

/* �������Ӧ�Ŀ������PPI������Ϣ�ַ��������Ͷ���*/
typedef UINT32 (*MsgNPpiDispatchFuncPtr)(VOID *pstMsg, UINT32 u32DataBufLen, CHAR *pDataBuf, UINT32 *pu32ActualDataLen);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

