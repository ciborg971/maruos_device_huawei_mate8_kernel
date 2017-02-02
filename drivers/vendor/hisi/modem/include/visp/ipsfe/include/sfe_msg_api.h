

#ifndef _SFE_MSG_API_H_
#define _SFE_MSG_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* ���������������ϢͨѶģ������� */
enum enumSfeComCode
{
    SFE_COM_SUCCESS,                                /* ͨ�ųɹ� */
    SFE_COM_ERR_BEGIN = SFE_COM_BEGIN_RET_CODE,     /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_COM_RCVMSG_NULL_POINTER,                    /* 1   ��ͨ�����յ���ϢΪ�� */
    SFE_COM_SENDACKHOOK_NULL,                       /* 2   ����ACK���Ӻ���Ϊ�� */
    SFE_COM_RCVMSG_LEN_ERR,                         /* 3   ͨ�����ݱ��ĳ��Ⱥ��յ����ĳ��Ȳ�һ�� */
    SFE_COM_RCVMSG_MODULE_ERR,                      /* 4   ��Ϣ��ģ��ŷǷ� */
    SFE_COM_RCVMSG_ITEM_LEN,                        /* 5   ��Ϣ����ѡ��ȷǷ� */
    SFE_COM_REG_ACKMSG_POINTER,                     /* 6   ע��ظ�ACK�ص�����ָ��Ϊ�� */
    SFE_COM_REG_SEND_EVENT_NULL,                    /* 7   ע�����Ϳ�����EVENT�ص�����ָ��Ϊ�� */
    SFE_COM_REG_SEND_PACKET_NULL,                   /* 8   ע�����Ϳ����汨�Ļص�����ָ��Ϊ�� */
    SFE_COM_ROUTE_ITEM_LEN,                         /* 9   ����·��ITEM���ȷǷ� */
    SFE_COM_IF_ITEM_LEN,                            /* 10  �����ӿ�ITEM���ȷǷ� */
    SFE_COM_ARP_ITEM_LEN_ERROR,                     /* 11  ARP ������Ϣ���ȴ��� */
    SFE_COM_ARP_SEND_MSG_FUNC_NULL,                 /* 12  ͨ����Ϣ���ͺ�������ΪNULL */
    SFE_COM_ARP_SEND_ARPMISS_MSG_FAIL,              /* 13  ͨ������ARP MISS��Ϣʧ�� */
    SFE_COM_RCVMSG_LEN_SHORT,                       /* 14  �����ܳ��ȷǷ� */
    SFE_COM_RCVMSG_ITEM_LEN_SHORT,                  /* 15  ��������ʱ,ITEM���ĳ��ȷǷ� */
    SFE_COM_RCVMSG_TYPE_ERR,                        /* 16  ������Ϣ���ͷǷ� */
    SFE_COM_RCVMSG_OPENTABLE_LEN,                   /* 17  OPEN����ʱ���ȷǷ� */
    SFE_COM_RCVMSG_OPENTABLE_TABLE,                 /* 18  OPEN����ʱTalbeֵ�Ƿ� */
    SFE_COM_RCVMSG_OPENTABLE_REGISGT,               /* 19  OPEN����ʱ,��Tableû��ע�� */
    SFE_COM_RCVMSG_OPENTABLE_POOL,                  /* 20  OPEN����ʱ,Open poolʧ�� */
    SFE_COM_RCVMSG_OPENTABLE_HAVE,                  /* 21  OPEN����ʱ,�Ѿ�Open pool */

    SFE_COM_RCVMSG_CLOSETABLE_LEN,                  /* 22  CLOSE����ʱ���ȷǷ� */
    SFE_COM_RCVMSG_CLOSETABLE_TABLE,                /* 23  CLOSE����ʱTalbeֵ�Ƿ� */
    SFE_COM_RCVMSG_CLOSETABLE_OPEN,                 /* 24  CLOSE����ʱ,��Tableû��OPEN�� */
    SFE_COM_RCVMSG_CLOSETABLE_POOL,                 /* 25  CLOSE����ʱ,Open poolʧ�� */

    SFE_COM_RCVMSG_GETTABLE_LEN,                    /* 26  GET����ʱ���ȷǷ� */
    SFE_COM_RCVMSG_GETTABLE_TABLE,                  /* 27  GET����ʱTalbeֵ�Ƿ� */
    SFE_COM_RCVMSG_GETTABLE_OPEN,                   /* 28  GET����ʱ,��Tableû��OPEN�� */

    SFE_COM_RCVMSG_INVALIDTABLE_TYPE,               /* 29  �������ʱ,�����ڸò��� */

    SFE_COM_RCVMSG_NPPI_ITEM_LEN,                   /* 30  ��������յ�NPPI������Ϣ���Ȳ��Ϸ� */
    SFE_COM_RCVMSG_NPPI_ITEM_LEN_SHORT,             /* 31  ��������յ�NPPI������Ϣ����Ϣ���Ȳ��Ϸ� */
    SFE_COM_RCVMSG_NPPI_MODULE_ERR,                 /* 32  ��������յ�NPPI������Ϣ�е�ģ��Ų��Ϸ� */

    SFE_COM_ARP_GET_ITEM_LEN_ERROR,                 /* 33  ARP��ȡ��Ϣ������Ϣ���ȴ��� */
    SFE_COM_ARP_SHOW_ALLARP_ITEM_LEN_ERROR,         /* 34  ��ʾARP��Ϣ��Ϣ���ȴ��� */
    SFE_COM_ARP_SHOW_ALLARP_BYVRF_ITEM_LEN_ERROR,   /* 35  ��ʾARP��Ϣ��Ϣ���ȴ��� */
    SFE_COM_ARP_SHOW_ONEARP_BYVRF_ERROR,            /* 36  ��ʾָ����ĳ��ARP����ʱ��Ϣ���ȴ��� */
    SFE_COM_ARP_GET_BUF_LEN_ERROR,                  /* 37  ARP��ȡ��Ϣ����ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_ARP_NPPI_CMD_INVALID,                   /* 38  ARP ��PPI�����ֲ��Ϸ� */

    SFE_COM_GET_ROUTE_ITEM_LEN_ERROR,               /* 39  ROUTE��ȡ��Ϣ������Ϣ���ȴ��� */
    SFE_COM_GET_ROUTE_BUF_LEN_ERROR,                /* 40  ROUTE��ȡ��Ϣ����ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_NPPI_ROUTE_CMD_INVALID,                 /* 41  ROUTE ��PPI�·������ִ��� */
    SFE_COM_NPPI_ROUTE_SHOW_ALL_ITEM_LEN_ERROR,     /* 42  ��ʾ����FIB��Ϣ��Ϣ���ȴ��� */
    SFE_COM_NPPI_ROUTE_SHOW_ONEIP_ITEM_LEN_ERROR,   /* 43  ��ʾĳ����ַ·����Ϣ��Ϣ���ȴ��� */

    SFE_COM_IF_GET_ITEM_LEN_ERROR,                  /* 44  IF��ȡ��Ϣ������Ϣ���ȴ��� */
    SFE_COM_IF_GET_BUF_LEN_ERROR,                   /* 45  IF��ȡ��Ϣ����ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_IF_NPPI_CMD_INVALID,                    /* 46  IF ��PPI�·������ִ��� */

    SFE_COM_BFD_GET_ITEM_LEN_ERROR,                 /* 47  BFD��ȡ��Ϣ������Ϣ���ȴ��� */
    SFE_COM_BFD_GET_BUF_LEN_ERROR,                  /* 48  BFD��ȡ��Ϣ����ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_BFD_NPPI_CMD_INVALID,                   /* 49  BFD ��PPI�����ֲ��Ϸ� */

    SFE_COM_BFD_ITEM_LEN_ERROR,                     /* 50  BFD ������Ϣ���ȴ��� */
    SFE_COM_BFD_SEND_MSG_FUNC_NULL,                 /* 51  ������ͨ����Ϣ���ͺ�������ΪNULL */
    SFE_COM_BFD_SEND_DETECTDOWN_MSG_FAIL,           /* 52  ͨ������BFD̽��ỰDOWN��Ϣʧ�� */

    SFE_COM_SET_ICMP_ITEM_LEN_ERROR,                /* 53  ICMP���ÿ�����Ϣ������Ϣ���ȴ��� */
    SFE_COM_GET_ICMP_BUF_LEN_ERROR,                 /* 54  ICMP��ȡ������Ϣʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_GET_ICMP_ITEM_LEN_ERROR,                /* 55  ICMP��ȡ������Ϣ������Ϣ���ȴ��� */
    SFE_COM_NPPI_ICMP_CMD_INVALID,                  /* 56  ICMP ��PPI�·������ִ��� */

    SFE_COM_IF_SET_ARPMISSWITCH_ITEM_LEN_ERROR,     /* 57  ����ARP MISS������Ϣ���ȴ��� */
    SFE_COM_IF_SET_REDUCETTLSWITCH_ITEM_LEN_ERROR,  /* 58  ����TTL�Ƿ�ݼ�������Ϣ���ȴ��� */
    SFE_COM_IF_SHOW_ALL_IFINFO_ITEM_LEN_ERROR,      /* 59  ��ʾ���нӿ���Ϣʱ��Ϣ���ȴ��� */
    SFE_COM_IF_SHOWBYID_IFINFO_ITEM_LEN_ERROR,      /* 60  ���ݽӿ�ID��ʾ�ӿ���Ϣʱ��Ϣ���ȴ��� */

    SFE_COM_REG_ACL_PPIMSG_DISPATCH_HOOK_NULL,      /* 61  ע��ACL PPI��Ϣ�ַ�����ָ��Ϊ�� */
    SFE_COM_REG_ACL_NPPIMSG_DISPATCH_HOOK_NULL,     /* 62  ע��ACL NPPI��Ϣ�ַ�����ָ��Ϊ�� */

    SFE_COM_SET_SRCIPADDR_ITEM_LEN_ERROR,           /* 63  ����Src IP Addr��Ϣ������Ϣ���ȴ��� */
    SFE_COM_GET_SRCIPADDR_ITEM_LEN_ERR,             /* 64  ��ȡSrc IP Addrʱ��������Ϣ���ȴ��� */
    SFE_COM_GET_SRCIPADDR_BUF_LEN_ERROR,            /* 65  ��ȡSrc IP Addrʱ��ͨ���ṩ��BUF���Ȳ��� */

    SFE_COM_NPPI_IP_CMD_INVALID,                    /* 66  IP ��PPI�·������ִ��� */

    SFE_COM_VCPU_NOT_INIT_SFERCVMSG,                /* 67  ����ͨ����ϢʱVCPUû�г�ʼ��*/
    SFE_COM_GET_CFGPPI_SPINLOCK_FAIL,               /* 68  ��ȡPPI����������ʧ�� */
    SFE_COM_GET_CFGNPPI_SPINLOCK_FAIL,              /* 69  ��ȡNPPI����������ʧ�� */
    SFE_COM_GET_CFGTABLE_SPINLOCK_FAIL,             /* 70  ��ȡTABLE����������ʧ�� */
    SFE_COM_CHECKSUM_FAIL,                          /* 71  ��ϢУ��ʹ��� */

    SFE_COM_MAINTENANCE_NPPI_CMD_INVALID,           /* 72  ά��ģ�����÷�PPI�����ֲ��Ϸ� */
    SFE_COM_DEBUG_NPPI_CMD_INVALID,                 /* 73  ά��DEBUGģ�����÷�PPI�����ֲ��Ϸ� */
    SFE_COM_FLOWSTAT_NPPI_CMD_INVALID,              /* 74  ά����ͳ��ģ�����÷�PPI�����ֲ��Ϸ� */
    SFE_COM_STATISTIC_NPPI_CMD_INVALID,             /* 75  ά��ͳ��ģ�����÷�PPI�����ֲ��Ϸ� */
    SFE_COM_LOG_NPPI_CMD_INVALID,                   /* 76  ά����־ģ�����÷�PPI�����ֲ��Ϸ� */
    SFE_COM_PUB_NPPI_CMD_INVALID,                   /* 77  ��������ģ�����÷�PPI�����ֲ��Ϸ� */

    SFE_COM_GET_STAT_ALLINFO_ITEM_LEN_ERROR,        /* 78  ��ȡȫ��ͳ����Ϣʱ��������Ϣ���ȴ��� */
    SFE_COM_GET_STAT_ALLINFO_CFG_BUF_LEN_ERROR,     /* 79  ��ȡȫ��ͳ����Ϣʱ��ͨ���ṩ��BUF���Ȳ��� */
    SFE_COM_SHOW_STAT_ALLSTAT_ITEM_LEN_ERROR,       /* 80  ��ʾ����ȫ��ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_STAT_AUTOSTAT_ITEM_LEN_ERROR,      /* 81  ��ʾȫ���Զ�ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_STAT_MANUALSTAT_ITEM_LEN_ERROR,    /* 82  ��ʾȫ���ֶ�ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_STAT_MANUALSTATBYVCPU_ITEM_LEN_ERROR,/* 82  ��ʾָ��VCPU��ȫ���ֶ�ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_CLEAR_ALLSTAT_ITEM_LEN_ERROR,           /* 83  �������ȫ��ͳ����Ϣʱ,��Ϣ���ȴ��� */

    SFE_COM_SET_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,     /* 84  ������ͳ�ƿ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,     /* 85  ��ȡ��ͳ�ƿ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_FLOWSTAT_SWITCH_CFG_BUF_LEN_ERROR,  /* 86  ��ȡ��ͳ�ƿ���ʱ,ͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_SHOW_FLOWSTAT_SWITCH_ITEM_LEN_ERROR,    /* 87  ��ʾ��ͳ�ƿ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_FLOWSTAT_CFG_ITEM_LEN_ERROR,            /* 88  ������ͳ�ƹ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_FLOWSTAT_CFG_BUF_LEN_ERROR,             /* 89  ������ͳ�ƹ���ʱ,ͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_GET_FLOWSTAT_RULENUM_ITEM_LEN_ERROR,    /* 90  ��ȡ��ͳ�ƹ�����ʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_FLOWSTAT_RULENUM_CFG_BUF_LEN_ERROR, /* 91  ��ȡ��ͳ�ƹ�����ʱ,ͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_GET_FLOWSTAT_ALLINFO_ITEM_LEN_ERROR,    /* 92  ��ȡ��ͳ�������Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_FLOWSTAT_ALLINFO_CFG_BUF_LEN_ERROR, /* 93  ��ȡ��ͳ�������Ϣʱ,ͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_SHOW_FLOWSTAT_ALLRULE_ITEM_LEN_ERROR,   /* 94  ��ʾ������ͳ�ƹ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_FLOWSTAT_RULEBYFLOWID_ITEM_LEN_ERROR,/* 95  ��ʾָ����ID����ͳ�ƹ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_FLOWSTAT_ALLSTAT_ITEM_LEN_ERROR,   /* 96  ��ʾ������ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_FLOWSTAT_BYRULE_ITEM_LEN_ERROR,    /* 97  ��ʾָ�����������ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_FLOWSTAT_BYFLOWID_ITEM_LEN_ERROR,  /* 97  ��ʾָ����ID����ͳ����Ϣʱ,��Ϣ���ȴ��� */
    SFE_COM_CLEAR_ALLFLOWSTAT_ITEM_LEN_ERROR,       /* 99  ���������ͳ����Ϣʱ,��Ϣ���ȴ��� */

    SFE_COM_SET_DEBUGTYPE_ITEM_LEN_ERROR,           /* 100 ����Debug���Ϳ���ʱ�����ȴ��� */
    SFE_COM_SET_DEBUGVCPU_ITEM_LEN_ERROR,           /* 101 ����VCPU Debug���Ϳ���ʱ�����ȴ��� */
    SFE_COM_SET_DEBUGMODU_ITEM_LEN_ERROR,           /* 102 ����MODULE Debug���Ϳ���ʱ�����ȴ��� */
    SFE_COM_GET_DEBUGSWITCH_ITEM_LEN_ERROR,         /* 103 DEBUG��ȡ������Ϣ������Ϣ���ȴ��� */
    SFE_COM_GET_DEBUGSWITCH_BUF_LEN_ERROR,          /* 104 DEBUG��ȡ������Ϣʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_SET_MSGOREVENT_DEBUG_ITEM_LEN_ERROR,    /* 105 ������Ϣ���¼����Կ���ʱ�����ȴ��� */
    SFE_COM_GET_MSGOREVENT_DEBUG_ITEM_LEN_ERROR,    /* 106 ��ȡ��Ϣ���¼����Կ���ʱ�����ȴ��� */
    SFE_COM_GET_MSGOREVENT_DEBUG_BUF_LEN_ERROR,     /* 107 ��ȡ��Ϣ���¼����Կ���ʱ��ͨ���ṩ�ĳ��ȴ��� */
    SFE_COM_SET_VERBOSE_DEBUG_ITEM_LEN_ERROR,       /* 108 ������ϸ���Եı��ĸ����ͳ���ʱ�����ȴ��� */
    SFE_COM_GET_VERBOSE_DEBUG_ITEM_LEN_ERROR,       /* 109 ��ȡ��ϸ���Եı��ĸ����ͳ���ʱ�����ȴ��� */
    SFE_COM_GET_VERBOSE_DEBUG_BUF_LEN_ERROR,        /* 110 ��ȡ��ϸ���Եı��ĸ����ͳ���ʱ��ͨ���ṩ�ĳ��ȴ��� */
    SFE_COM_SHOW_DEBUG_SWITCH_ITEM_LEN_ERROR,       /* 111 ��ʾ���Կ�����Ϣʱ,��Ϣ���ȴ��� */

    SFE_COM_BFD_SET_DEBUGSWITCH_ITEM_LEN_ERROR,     /* 112 BFD���õ��Կ�����Ϣ���ȴ��� */
    SFE_COM_BFD_GET_DEBUGSWITCH_ITEM_LEN_ERROR,     /* 113 BFD��ȡ���Կ�����Ϣ���ȴ��� */
    SFE_COM_BFD_GET_DEBUGSWITCH_BUF_LEN_ERROR,      /* 114 BFD��ȡ���Կ��ز���ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_BFD_SHOW_ALLINFO_ITEM_LEN_ERROR,        /* 115 ��ʾ����BFD��Ϣ���ȴ���*/
    SFE_COM_BFD_SHOW_INFO_BYVRF_ITEM_LEN_ERROR,     /* 116 ����VRF��ʾBFD��Ϣ���ȴ���*/
    SFE_COM_BFD_SHOW_INFO_BYID_ITEM_LEN_ERROR,      /* 117 ����BFD �ỰID��ʾBFD��Ϣ���ȴ���*/

    SFE_COM_SET_LOGLEVEL_SWITCH_ITEM_LEN_ERROR,     /* 118 ������־���𿪹�ʱ,��Ϣ���ȴ��� */
    SFE_COM_SET_LOGTYPE_SWITCH_ITEM_LEN_ERROR,      /* 119 ������־���Ϳ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_LOG_SWITCH_ITEM_LEN_ERROR,         /* 120 ��ʾ��־����ʱ,��Ϣ���ȴ��� */

    SFE_COM_SHOW_VERSION_ITEM_LEN_ERROR,            /* 121 ��ʾ������汾��ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_PRECONFIG_ITEM_LEN_ERROR,          /* 122 ��ʾ������Ԥ����ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_SHAREMEMID_ITEM_LEN_ERROR,         /* 123 ��ʾ�����湲���ڴ�IDʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_STUBMODULE_ITEM_LEN_ERROR,         /* 124 ��ʾ������ģ��ü�ʱ,��Ϣ���ȴ��� */
    SFE_COM_SET_ACLFAKEREASS_SWITCH_ITEM_LEN_ERROR, /* 125 ����ACL�Ƿ���Ҫ�����鿪��ʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_ACLFAKEREASS_SWITCH_ITEM_LEN_ERROR, /* 126 ��ȡACL�Ƿ���Ҫ�����鿪��ʱ,��Ϣ���ȴ��� */
    SFE_COM_GET_ACLFAKEREASS_SWITCH_CFG_BUF_LEN_ERROR,/* 127 ��ȡACL�Ƿ���Ҫ�����鿪��ʱ,ͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_SHOW_ACLFAKEREASS_ITEM_LEN_ERROR,       /* 128 ��ʾACL�Ƿ���Ҫ�����鿪��ʱ,��Ϣ���ȴ��� */
    SFE_COM_SHOW_MSGSEQ_ITEM_LEN_ERROR,             /* 129 ��ʾ��������Ϣ���ʱ,��Ϣ���ȴ��� */
    SFE_COM_SET_OUTPUTTOCOM_SWITCH_ITEM_LEN_ERROR,  /* 130 ������������Ϣ�����com�ڿ���ʱ,��Ϣ���ȴ��� */

    SFE_COM_ARP_MISS_RESTRAIN_FAIL,                 /* 131 ARP MISS����,����1��ʾ���ϱ� */
    SFE_COM_ARP_MISS_REG_RESTRAIN_HOOK_NULL,        /* 132 ע��ARP MISS���ƹ��Ӻ���Ϊ�� */
    SFE_COM_BFD_GET_STAT_ITEM_LEN_ERROR,            /* 133 ��ȡBFD�Ựͳ����Ϣ��Ϣ���ȴ��� */
    SFE_COM_BFD_GET_STAT_BUF_LEN_ERROR,             /* 134 ��ȡBFD�Ựͳ����Ϣ����ʱͨ���ṩ�Ļ��������Ȳ��� */
    SFE_COM_BFD_CLEAR_STAT_ITEM_LEN_ERROR,          /* 135 ��0BFD�Ựͳ����Ϣ��Ϣ���ȴ��� */
    SFE_COM_BFD_SHOW_STAT_ITEM_LEN_ERROR,           /* 136 ��ʾBFD�Ựͳ����Ϣ��Ϣ���ȴ��� */
 };

/* ������ظ���������Ϣ�Ĺ���ԭ�� */
typedef UINT32 (*g_pfSFESendAckMsg)(VOID *pSrcMsg, VOID *pMsg, UINT32 u32MsgLen);
/* ������֪ͨ�������¼���Ϣ�Ĺ���ԭ�� */
typedef UINT32 (*g_pfSendEventToVISP)(VOID *pMsg, UINT32 u32MsgLen);

/*Description:������ע���ARP MISS�ϱ����ƺ����Ĺ���ԭ��.
  Input      :UINT32 u32VrfIndex: VRF����.
              UINT32 u32IpAddr: ��ַ,������.
  Return     :0,��ʾARP Miss������������������ARP Miss��Ϣ.
              1,��ʾARP Miss���ʳ��꣬��������ARP Miss��Ϣ.*/
typedef UINT32 (*g_pfSfeArpMissRestrainHook)(UINT32 u32VrfIndex, UINT32 u32IpAddr);

/*******************************************************************************
*    Func Name: SFE_RecvMsg
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: ��������տ�������Ϣ���,����NP�����
*        Input: VOID * pMsg:��Ϣ
*               UINT32 u32MsgLen: ��Ϣ����
*       Output:
*       Return: �ɹ�:SFE_COM_SUCCESS ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RecvMsg(VOID * pMsg, UINT32 u32MsgLen);

/*******************************************************************************
*    Func Name: SFE_RegSendAckMsg
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: ������ע�ᷢ��ACK�ص�����
*        Input: g_pfSFESendAckMsg pfFunc:����ָ��
*       Output:
*       Return: �ɹ�:SFE_COM_SUCCESS ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegSendAckMsg(g_pfSFESendAckMsg pfFunc);

/*******************************************************************************
*    Func Name: SFE_RegSendEventToVISP
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: ������ע�ᷢ���¼��ص�����
*        Input: g_pfSendEventToVISP pfFunc: ����ָ��
*       Output:
*       Return: �ɹ�:SFE_COM_SUCCESS ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegSendEventToVISP(g_pfSendEventToVISP pfFunc);

/*******************************************************************************
*    Func Name: SFE_RegFuncArpMissRestrainHook
* Date Created: 2009-11-16
*       Author: zengshaoyang(62531)
*  Description: ע��ARP MISS�ϱ���ֹ����
*        Input: g_pfSfeArpMissRestrainHook pfRegFunc: ����ָ��
*       Output:
*       Return: �ɹ�:SFE_COM_SUCCESS ����:ʧ��
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-11-16   zengshaoyang(62531)     Creat the first version.
*
*******************************************************************************/
extern UINT32 SFE_RegFuncArpMissRestrainHook(g_pfSfeArpMissRestrainHook pfRegFunc);


extern VOID SFE_Show_MsgSeq(VOID);


#ifdef  __cplusplus
}
#endif

#endif


