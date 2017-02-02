/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_cbb_api.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP api
*  Date Created: 2008-05-15
*        Author: lishenchuan
*   Description: ��Ҫ�ṩ����Ʒ�Լ�CBB�Լ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-05-15      lishenchuan       Create
*  2008-06-26      lishenchuan       modify the default and the range of
*                                    logAnnounceInterval    default:1      range: -3 to 3
*                                    logSycInterval         default:-4     range: -7 to 1
*                                    logMinDelayInterval    default:-4     range: -7 to 6
*                                    logMinPdelayInterval   default:-4     range: -7 to 6
*                                    RecipteTimeOut         default: 3     rangge  2 to 255
*  2008-12-17      wangchengyang     ����visp���߰汾������ͷ�ļ�
*******************************************************************************/

#ifndef __ptp__cbb__api__h__
#define __ptp__cbb__api__h__

#ifdef __cplusplus
extern "C" {
#endif

/*����ClockIdentity����*/
#define PTP_CLOCK_ID_LEN                8

/* �¼���ϢUDP�˿ں� */
#define PTP_EVENT_PORT                  319

/* ��ͨ��ϢUDP�˿ں� */
#define PTP_GENERAL_PORT                320

/*����PTPģ��֧�ֵĶ˿������*/
#define PTP_SUPPORT_PORT_NUMBER         2

/* PTP�ಥĿ������ַ��������:224.0.1.129,All except peer delay mechanism messages */
#define PTP_PRIMARY_MULTICAST_IP        0xE0000181L

/* PTP-Pdelay�ಥĿ�ĵ�ַ�������򣬸õ�ַ���ڲ���:224.0.0.107,Peer delay mechanism messages */
#define PTP_PDELAY_MULTICAST_IP         0xE000006BL

/*���嵥��Master�б����ܹ��*/
#define PTP_UNICAST_MASTR_LEN           5

/*����ACCEPTABLE Master�б��ȹ��*/
#define PTP_ACCEPT_MASTR_LEN            2


#define PTPIF_MAX_VLAN_ID        4094
#define PTPIF_MIN_VLAN_ID        1

/* Master����������ַ���� */
/* Modified by dutianyi00217007 2014-1-17 ֧��PTP�˿ڵ�ַ��չ */
#define PTP_MAX_IP_NUM         48
#define PTP_DEFAULT_IP_NUM     1

/* Slave �� ����VRF������� */
#define PTP_MAX_VRF_NUM         5

/*Added by luogaowei 2013-4-7 ֧��1588 16.1��ѡ����

ע��: PTP_NEGO_MODE_DURATION;���뱣֤��ֵ��PTP_KEEP_ALIVE_MODE_NEW ��ͬ
*/
#define PTP_NEGO_MODE_NO_DURATION   0   /*PTP ��Э��ģʽ: ��duration ,������1588�ݰ�*/
#define PTP_NEGO_MODE_DURATION      1   /*PTP ��Э��ģʽ: ��duration ,��1588v2�Ŀ�ѡ16.1 ��G8265.1*/
#define PTP_BMC_MODE_IEEE_1588      0   /*ѡԴ�㷨: 1588��׼ */
#define PTP_BMC_MODE_ITU_G82651     1   /*ѡԴ�㷨: 8265.1��׼*/
/*End by luogaowei 2013-4-7*/

/*Added by luogaowei 2013-4-7 ֧��1588 16.1��ѡ����
  ���弸����� ����PTP_SetNegoAndBmcSplitMode ��PTP_SetKeepAliveMode���û���*/
#define PTP_MODE_API_FLAG_INIT      0
#define PTP_MODE_API_FLAG_KEEPVLIE  1
#define PTP_MODE_API_FLAG_SPLIT     2
/*End by luogaowei 2013-4-7*/

#define PTP_SLAVE_ALREADY_EXIST 1
#define PTP_SLAVE_NOT_EXIST 0

/*�����붨��*/
typedef enum tagPTP_ERR_E
{
    PTP_OK =0,
    PTP_ERR,
    PTP_ERR_NULL,                      /* 2.ָ��Ϊ�մ��� */
    PTP_ERR_CLOCK_UNINIT,              /* 3.ʱ��ʵ��δ��ʼ�� */
    PTP_ERR_CLOCK_ACCURACY,            /* 4.ʱ�Ӿ��ȷ�Χ���Ϸ� */
    PTP_ERR_LEAP_CONFLIT,              /* 5.ʱ��leap��ͻ */
    PTP_ERR_PORT_NUMBER,               /* 6.�˿ںŲ���ȷ */
    PTP_ERR_PORT_ADDR,                 /* 7.�˿ڵ�ַ��Ч */
    PTP_ERR_MAX_SIZE,                  /* 8.�������Χ */
    PTP_ERR_ALREADY_EXIST,             /* 9.�ýڵ��Ѿ����� */
    PTP_ERR_NOT_FOUND,                 /* 10.δ�ҵ��ýڵ� */
    PTP_ERR_DELAY_MACHENISM,           /* 11.��ʱ�������ô��� */
    PTP_ERR_PORT_UNVALID,              /* 12.�˿���Ч */
    PTP_ERR_MEMORY,                    /* 13.�ڴ����ʧ�� */
    PTP_ERR_INTERUPT,                  /* 14.���ж�ʧ�� */
    PTP_ERR_STATE_UNICAST,             /* 15.����Э�̱��λ״̬���� */
    PTP_ERR_FSM_EVENT_TYPE_ERR,        /* 16.״̬���¼������������*/
    PTP_ERR_CLKTYPE,                   /* 17.ʱ�����ͷǷ� */
    PTP_ERR_SOFTMODE,                  /* 18.������ͷǷ�����Ϊ������ߴ���+FPGA�ܹ� */
    PTP_ERR_SOCKET_INIT,               /* 19.socket��ʼ��ʧ�� */
    PTP_ERR_GET_SYSINFO,               /* 20.��ȡϵͳ��Ϣʧ�� */
    PTP_ERR_SET_ASYNSOCKET,            /* 21.����socket�첽����ʧ�� */
    PTP_ERR_MSGTYPE,                   /* 22.�������ͷǷ� */
    PTP_ERR_PACKET_BUFFER,             /* 23.���Ļ���Ϊ�� */
    PTP_ERR_PACKET_LEN,                /* 24.���ĳ��ȷǷ� */
    PTP_ERR_SETMULTICAST,              /* 25.���öಥsocketʧ�� */
    PTP_ERR_PACKET,                    /* 26.�������ݷǷ� */
    PTP_ERR_MASTER_NOTEXIST,           /* 27.���ڵ���master��/�ɽ���master�б��� */
    PTP_ERR_DELAY_INTERVAL,            /* 28.delay��ʱ������ò��Ϸ� */
    PTP_ERR_CLOCK_FSM_MODE,            /* 29.ʱ��״̬��ģʽ���� */
    PTP_ERR_ANN_INTERVAL,              /* 30.announce��Ϣ������ô��� */
    PTP_ERR_SYNC_INTERVAL,             /* 31.sync��Ϣ������ô��� */
    PTP_ERR_SYNC_MODE,                 /* 32.ʱ��/Ƶ��ͬ�����ô��� */
    PTP_ERR_CAST_MODE,                 /* 33.����/�ಥģʽ���ô��� */
    PTP_ERR_TIME_SOURCE,               /* 34.ʱ��Դ���ô��� */
    PTP_ERR_SEQUENCEID,                /* 35.�������кŷǷ� */
    PTP_ERR_PORTNOTFIND,               /* 36.����Ŀ��IPδ�ҵ�ʱ�Ӷ˿� */
    PTP_ERR_ACPTMSTR_NOTENABLE,        /* 37.�ɽ���master��û��ʹ�� */
    PTP_ERR_ANNOUNCE,                  /* 38.announce��Ϣ�Ƿ� */
    PTP_ERR_PORTSTATE,                 /* 39.�˿�״̬���󣬴�ʱ���ܽ��պͷ��ͱ��� */
    PTP_ERR_MALLOC,                    /* 40.�����ڴ���� */
    PTP_ERR_SLAVE_NOTEXIST,            /* 41.���ڵ���slave�б��� */
    PTP_ERR_TLVTYPE,                   /* 42.tlv���ͷǷ� */
    PTP_ERR_DEV_NOTHUAWEI,             /* 43.�Զ˲��ǻ�Ϊ�豸������չtlv����ʱ�� */
    PTP_ERR_DSCP_PRIORITY,             /* 44.DSCPֵ�Ƿ� */
    PTP_ERR_CLOSESOCKET,               /* 45.�ر�socket */
    PTP_ERR_CREATESOCKET,              /* 46.����socketʧ�� */
    PTP_ERR_SET_SOCKETOPTION,          /* 47.����socket����ʧ�� */
    PTP_ERR_BINDSOCKET,                /* 48.��socketʧ�� */
    PTP_ERR_RECVPKT,                   /* 49.socket���ձ���ʧ�� */
    PTP_ERR_RECVMSG,                   /* 50.socket���ո�������ʧ�� */
    PTP_ERR_SOCKETID,                  /* 51.socket id�Ƿ� */
    PTP_ERR_SOCKET_MSGTYPE,            /* 52.socket�첽��Ϣ�Ƿ� */
    PTP_ERR_SND_GENERALPKT,            /* 53.socket���ķ���ʧ�� */
    PTP_ERR_IP_NOT_EXIST,              /* 54.Դ��ַ���ڱ��� */
    PTP_ERR_CLRSOCKETMULTICAST,        /* 55.����ಥѡ�� */
    PTP_ERR_GET_PORTADDR,              /* 56.��ȡ��ַ�Ƿ� */
    PTP_ERR_VERSION,                   /* 57.PTP version�Ƿ� */
    PTP_ERR_DOMAINNUMBER,              /* 58.domain number�Ƿ� */
    PTP_ERR_FLAGFIELD,                 /* 59.flag field�Ƿ� */
    PTP_ERR_PORTID,                    /* 60.ʱ��id�Ƿ� */
    PTP_ERR_ORGSUBTYPE,                /* 61.OrganizationSubType�Ƿ� */
    PTP_ERR_EXTEN_EVENT,               /* 62.�ⲿ�¼����� */
    PTP_ERR_WRITEQUE_FAIL,             /* 63.д����ʧ�� */
    PTP_ERR_NOT_SUPP_BC,               /* 64.PTP CBB��֧��BC�ڵ�*/
    PTP_ERR_DEV_TYPE,                  /* 65.PTP �豸���ͷǷ�*/
    PTP_ERR_CREATE_QUEUE,              /* 66.PTP �������д���*/
    PTP_ERR_CREATE_TIMER,              /* 67.PTP ������ʱ������*/
    PTP_ERR_CREATE_TASK,               /* 68.PTP �����������*/
    PTP_ERR_FSM_STATE,                 /* 69.PTP ״̬��״̬����*/
    PTP_ERR_RECOMD_STATE,              /* 70.PTP �Ƽ�״̬����*/
    PTP_ERR_UNIMASTER_NOT_VALID,       /* 71.PTP ����Master��Ч*/

    PTP_ERR_DONT_PROCMSG,              /* 72.��������Ϣ*/
    PTP_ERR_MASTR_NOT_IN_UNICASTM_TAB, /* 73.Master���ڵ���Mst���� */
    PTP_ERR_MASTR_NOT_IN_ACCEPTM_TAB,  /* 74Mst���ڿɽ���Mst���� */
    PTP_ERR_ITEM_EXIST,                /* 75.�������*/
    PTP_ERR_TAB_FULL,                  /* 76.����Ϊ��*/
    PTP_ERR_LOGIC_TIMER_OVER,          /* 77.�߼���ʱ�������*/
    PTP_ERR_LOGIC_TIMER_FUNC_NULL,     /* 78.�����߼���ʱ���ĺ���ָ��Ϊ��*/
    PTP_ERR_LOGIC_TIMER_MALLOC_FAIL,   /* 79.�߼���ʱ��MALLOCʧ��*/
    PTP_ERR_LOGIC_TIMERID_NULL,        /* 80.�߼���ʱ��IdΪ��*/


    PTP_ERR_PROF_NOTSUPPORT,           /* 81.��֧�ָ�Э��ģ��*/
    PTP_ERR_BMC_PARAM ,                /* 82.ѡԴ�����Ƿ� */
    PTP_ERR_BMC_MASTER_INVALID,        /* 83.Master��Ч */
    PTP_ERR_BMC_MASTER_NOT_UP,         /* 84.Masterû��up */
    PTP_ERR_BMC_NO_MASTER,             /* 85.û��master��ѡ */
    PTP_ERR_ANN_NOTPROC,               /* 86.������announce���� */

    PTP_ERR_PROTOCAL,                   /* 87.Э�����*/
    PTP_ERR_TIMEOUT_SCALE,              /* 88.timer scale�Ƿ�*/
    PTP_ERR_LOGIC_TIMER_NUM_ZERO,       /* 89.�߼���ʱ����Ϊ0*/
    PTP_ERR_LOGIC_TIMER_POINTER_INVALID,/* 90.�߼���ʱ��ָ����Ч*/
    PTP_ERR_UNICASTFLAG,                /* 91.flagfiel��unicastflag�Ƿ� */
    PTP_ERR_ALTERNATE_MASTERFLAG,       /* 92.flagfiel��alternate mastter flag�Ƿ� */

    PTP_ERR_GROUPWARE_FALSE,            /* 93.���ָ��δ��*/
    PTP_ERR_CREATE_MUTEX_FAILED,        /* 94.����PTP������ź���ʧ�� */
    PTP_ERR_SND_EVENTPKT,               /* 95.����event��Ϣʧ�� */
    PTP_ERR_MAX_CFG_SIZE,               /* 96.���ù�񳬹����ֵ */
    PTP_ERR_NEGO_STATE_INCORRECT,       /* 97.����Э��״̬��״̬����ȷ�������� */
    PTP_ERR_UNIMASTER_RUN_TAB_NULL,     /* 98.����Master���б�Ϊ�ջ�δ���� */
    PTP_ERR_REFUSEGRANT,                /* 99.��ͬ����Ȩ*/
    PTP_ERR_BMC_SELECT_MODE,            /* 100.ѡԴģʽ������� */
    PTP_ERR_SLAVETABLE_FULL,            /* 101 ����SLAVE�б������10000*/
    PTP_ERR_LIVE_INTERVAL,              /* 102 Keep alive ���ֵ�Ƿ� */
    PTP_ERR_MODE_INTERVAL,              /* 103 ģʽ����  */
    PTP_ERR_RECEIPT_TIMEOUT,            /* 104 receipt time out�����Ƿ� */
    PTP_ERR_DEBUG_SWITCH,               /* 105 debug���ͷǷ� */
    PTP_ERR_NULL_P,                     /* 106 �������Ϊ��(�˿ں�) */
    
    /* Added by hanna55555, VISPV1R8C03, 2009/11/20 */
    PTP_ERR_MAC_NOT_CFG,                /* 107 physical��ַû������ */
    PTP_ERR_INTF_NOT_EXIST,             /* 108 �ʺ�physical��ַ�Ľӿڲ����� */
    PTP_ERR_CREATE_MBUF,                /* 109 ����Mbufʧ�� */
    PTP_ERR_PREPEND_MEM_SPACE,          /* 110 ��չ�ڴ�ռ�ʧ�� */
    PTP_ERR_INVALID_ENCAP_TYPE,         /* 111 ��Ч��̫��װ���� */
    /*End of Added by hanna55555, 2009/11/20 */  
    
    PTP_ERR_DURATION_FIELD_INVALID, /*112 ��Ч�ķ���ʱ��*/
    PTP_ERR_STEPFLAG_SCOPE,         /*113 �����STEP���λ*/
    PTP_ERR_PARA_INVALID,           /*114 ��������*/
    PTP_ERR_INVALID_VLANID,         /*115 �����VLan id*/
    /*Add End*/
    PTP_ERR_BMC_NO_PRI_CLOCK_SOURCE,/* 116 û�п���ѡ�Ĳο�Դ*/
    /*Add End*/
    
    PTP_ERR_ALIVE_MODE,/* 117 ��KEEPALIVE�Ǿ�ģʽʱ���ǲ������ٴε�����Э�̽ӿڵ�*/
    /*Add End*/
    /*Added by zhangbo146309, �����ಥ���ַ��Ӧ, 2010/8/20 */
    PTP_ERR_GET_IFINDEXGP,/* 118 ��ȡ�ӿ�������ʧ��*/
    PTP_ERR_SET_MULTISOCK_OPTION,/* 119 ��ƶಥSOCKETѡ��ʧ��*/
    /* End of Added by zhangbo146309, 2010/8/20 */
    PTP_ERR_GET_IPV6_CMP_FAIL, /*120 ��ȡIPv6��ַģ���齨ʧ��*/
    PTP_ERR_IPV6_UNENABLE,  /*121 PTP IPV6δʹ��(δ����Ԥ��ֵ)*/
    PTP_ERR_SET_SOCKET_IOCTL, /*122 ����socket IOCTLʧ��*/
    PTP_ERR_PORT_ADDR_STATE, /*123 slave״̬�½�����������������һ�����͵�ַ*/
    /*Added by Anish K Kurian & Wangchengyang72338 & 62830, for new profile, 2010/9/21 */
    PTP_ERR_PROFILE_MODE,               /* 124 profile mode error */
    PTP_ERR_BMC_LOCAL_ClASS,            /* 125 local class is better than master,only use at BMC */
    PTP_ERR_API_USAGE,                  /* 126 Wrong usage of API - Please check the API Description*/
    
    /* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/9/21 */
    PTP_ERR_IPADDR,    /*127 add unicast master cann't add 0 addr*/
    PTP_ERR_IPSCOPE,     /*128 unicast master can't be the multi address*/
    PTP_ERR_INVALID_VLANPRI,         /*129 �����VLan ���ȼ�*/
    PTP_ERR_NO_SUCH_MASTER_ADDR,     /* 130 ��Ч/δ���õ�master��ַ */
    PTP_ERR_IS_NOT_MASTER,           /* 131 ��clock ��master, ֻ���master��API���ɲ��� */
    PTP_ERR_WRONG_PROTOCAL,          /* 132 Э��Ŵ��� */
    PTP_ERR_WRONG_LIMIT_IP_NUM,      /* 133 ��������IP������Χ,����������� */
    PTP_ERR_IP_LIMIT_LT_EXIST,       /* 134 ���õ�ip��������ֵ���Ѿ�����IP����С */
    PTP_ERR_ADDR_FULL,               /* 135 ��ַ�Ѿ��ﵽ������� */
    PTP_ERR_ADDR_ALREADY_EXIST,      /* 136 ���ӵ�ַ������ַ�Ѿ����� */
    PTP_ERR_SET_ADDRESS_FAILED,      /* 137 ���ӵ�ַʧ�� */
    PTP_ERR_DEST_IP_NOT_EXIST,       /* 138 ���ܱ���Ŀ��ip���������б��� */
    PTP_ERR_NO_PORT_ADDR,            /* 139 û�����õ�ַ */

    /* 149-200 ����VRF��� */
    PTP_ERR_VRF_NO_CONFIG = 149,     /* 149 û���ҵ�VRF */
    PTP_ERR_VRF,                     /* 150 VRF���� */
    PTP_ERR_VRF_ADDR_FULL,           /* 151 vrf��ַ ���� */
    PTP_ERR_VRF_ADDR_EXIST,          /* 152 VRF��ַ �Ѵ��� */
    PTP_ERR_VRF_ADDR_NULL,           /* 153 vrf��ַ ������ */
    PTP_ERR_VRF_FULL,                /* 154 VRF�Ѿ�������� */
    PTP_ERR_VRF_EXIST,               /* 155 VRF�Ѿ����� */
    PTP_ERR_VRF_NULL,                /* 156 VRF������ */
    PTP_ERR_VRF_ONE_ADDR_ONE_VRF,    /* 157 1��VRF��ֻһ���˿ڵ�ַ */
    PTP_ERR_VRF_MORE_ADDR_ONE_VRF,   /* 158 1��VRF�´����˶���˿ڵ�ַ */
    PTP_ERR_VRF_DEFAULT_FOBBIDEN,    /* 159 Ĭ��VRF����ʹ�� */
    PTP_ERR_VRF_NOT_MATCH,           /* 160 �յ�����VRF�뱾��VRF id��ƥ�� */
    PTP_ERR_VRF_INUSE,               /* 161 ��vrf��UnicastMasterʹ���� */
    PTP_ERR_VRF_ADDR_ONE,            /* 162 slave ��ÿ��portֻ��������һ�����˵�ַ*/
    /* end of VRF ��� */
    PTP_ERR_NOT_NEED_DOFSM,          /* 163 ����ҪѡԴ���� */
    PTP_ERR_DURATION_PRECENT_INVALID, /*164 �趨Duration��Э��ʱ��(���Duration�ٷֱ�)��Ч*/
    PTP_ERR_WRITEVENT_FAIL,           /*165 д�¼�ʧ�� */
    PTP_ERR_NEGO_AND_BMC_SPLIT_MODE,  /*166 �����Э�̺�ѡԴ����ģʽ*/
    PTP_ERR_INVALID_MASTER_CLASS,     /*167 �����master class,����80-110��Χ���߶�Ӧ��QLΪ0*/
    PTP_ERR_OTHER_PTP_USED,           /*168 �����汾��PTPģ������ʹ����*/
    PTP_ERR_BMC_G82751_ERRNO1,        /*169 ��G8275.1��׼ѡԴ����ForeMaster�뱾�˵�ʱ��Idһ��*/
    PTP_ERR_BMC_G82751_ERRNO2,        /*170 ��G8275.1��׼ѡԴ�������ForeMaster��ʱ��Idһ��*/
    PTP_ERR_MAX                       /* ���������ֵ������Ҫ��Ӷ��������֮ǰ */
}PTP_ERR_E;

/*����ʱ���豸����ö��*/
typedef enum tagPTP_DEV_TYPE_E
{
    PTP_DEV_TYPE_OC =0,     /*0  OC*/
    PTP_DEV_TYPE_E2ETC,     /*1  E2ETC */
    PTP_DEV_TYPE_P2PTC,     /*2  P2PTC */
    PTP_DEV_TYPE_OC_E2ETC,  /*3  OC + E2ETC */
    PTP_DEV_TYPE_OC_P2PTC,  /*4  OC + P2PTC */
    PTP_DEV_TYPE_BC,        /*5  BC Ŀǰ��֧�֣�Ϊ����*/
    PTP_DEV_TYPE_END
}PTP_DEV_TYPE_E;

/*����ʱ����������ģʽ*/
typedef enum tagPTP_SOFT_MODE_E
{
    PTP_SOFT_MODE_ALLSOFT = 0,    /* ����ģʽ */
    PTP_SOFT_MODE_SOFTFPGA,       /* PTP����FPGAͬ��ģʽ */
    PTP_SOFT_MODE_END
}PTP_SOFT_MODE_E;


/* ����Э��ö������ */
typedef enum tagPTP_PROTOCAL_TYPE_E
{
    PTP_PROTOCAL_UDP_IPV4 = 1,
    PTP_PROTOCAL_UDP_IPV6,
    PTP_PROTOCAL_IEEE_802,
    PTP_PROTOCAL_DEVICE_NET,   /*��ʹ��*/
    PTP_PROTOCAL_CONTROL_NET,  /*��ʹ��*/
    PTP_PROTOCAL_PROFI_NET     /*��ʹ��*/
}PTP_PROTOCAL_TYPE_E;

/* ʱ�侫��ö�ٶ��� */
typedef enum tagPTP_CLOCK_ACCURACY_E
{
    PTP_CLOCK_ACCURACY_25NS = 0X20, /*The time is accurate to within 25 ns*/
    PTP_CLOCK_ACCURACY_100NS,       /*The time is accurate to within 100 ns*/
    PTP_CLOCK_ACCURACY_250NS,       /*The time is accurate to within 250 ns*/
    PTP_CLOCK_ACCURACY_1US,         /*The time is accurate to within 1 us*/
    PTP_CLOCK_ACCURACY_2P5US,       /*The time is accurate to within 2.5 us*/
    PTP_CLOCK_ACCURACY_10US,        /*The time is accurate to within 10 us*/
    PTP_CLOCK_ACCURACY_25US,        /*The time is accurate to within 25 us*/
    PTP_CLOCK_ACCURACY_100US,       /*The time is accurate to within 100 us*/
    PTP_CLOCK_ACCURACY_250US,       /*The time is accurate to within 250 us*/
    PTP_CLOCK_ACCURACY_1MS,         /*The time is accurate to within 1 ms*/
    PTP_CLOCK_ACCURACY_2P5MS,       /*The time is accurate to within 2.5 ms*/
    PTP_CLOCK_ACCURACY_10MS,        /*The time is accurate to within 10 ms*/
    PTP_CLOCK_ACCURACY_25MS,        /*The time is accurate to within 25 ms*/
    PTP_CLOCK_ACCURACY_100MS,       /*The time is accurate to within 100 ms*/
    PTP_CLOCK_ACCURACY_250MS,       /*The time is accurate to within 250 ms*/
    PTP_CLOCK_ACCURACY_1S,          /*The time is accurate to within 1 s*/
    PTP_CLOCK_ACCURACY_10S,         /*The time is accurate to within 10 s*/
    PTP_CLOCK_ACCURACY_M10S,         /*The time is accurate to >10 s*/
    PTP_CLOCK_ACCURACY_UNKNOWN = 0xFE  /*The time is unknown*/
}PTP_CLOCK_ACCURACY_E;

/* ��ʱ���ƶ��� */
typedef enum tagPTP_DELAY_MACHENISM_E
{
    /* In new profile:'01' for a two-way slave, and 'FE' for a one-way slave */
    PTP_DELAY_MACHENISM_E2E = 0X01,          /* ����_��Ӧ��ʱ���� */
    PTP_DELAY_MACHENISM_P2P = 0X02,        /*  �Զ���ʱ���� */
    PTP_DELAY_MACHENISM_DISABLE = 0XFE      /*  ��ʱ���Ʋ����� */
}PTP_DELAY_MECHENISM_E;

/* ����״̬��ģʽ */
typedef enum tagPTP_CLOCK_FSM_MODE_E
{
    PTP_CLOCK_FSM_MODE_SLAVE_ONLY = 0,      /* slave_only ״̬���豸 */
    PTP_CLOCK_FSM_MODE_MASTER_ONLY,     /* master_only ״̬���豸*/
    PTP_CLOCK_FSM_MODE_FULL ,            /* ȫ״̬���豸, �ݲ�֧�� */
}PTP_CLOCK_FSM_MODE_E;

/* ���嵥�ಥģʽ */
typedef enum tagPTP_CLOCK_CAST_MODE_E
{
    PTP_CLOCK_UNICAST_MODE,             /* ����ģʽ*/
    PTP_CLOCK_MULTICAST_MODE,           /* �ಥģʽ*/
    PTP_CLOCK_IEEE8023_MODE,            /* OVER MACģʽ*/
}PTP_CLOCK_CAST_MODE_E;

/*  ����ʱ��/Ƶ��ͬ��ģʽ */
typedef enum tagPTP_SYNC_MODE_E
{
    PTP_SYNC_MODE_TIME,
    PTP_SYNC_MODE_FREQUENCY
}PTP_SYNC_MODE_E;

/* ����Э��״̬����־ö�ٶ��� */
typedef enum tagPTP_STATE_UNICAST_NEGO_E
{
    PTP_STATE_UNICAST_NEGO_NULL = 0,
    PTP_STATE_UNICAST_NEGO_REQ,
    PTP_STATE_UNICAST_NEGO_GRANT,
    PTP_STATE_UNICAST_NEGO_REFUSE,
    PTP_STATE_UNICAST_NEGO_FAILURE,  /* ������Ϣn�ζԷ�����Ӧ */
    PTP_STATE_UNICAST_NEGO_CANCEL,
    PTP_STATE_UNICAST_NEGO_ACK
}PTP_STATE_UNICAST_NEGO_E;

/* �������Ͷ��� */
typedef enum tagPTP_MSG_TYPE_E
{
    PTP_MSG_SYNC              =       0,     /* Sync */
    PTP_MSG_DELAY_REQ,                       /* Delay_Req */
    PTP_MSG_PDELAY_REQ,                      /* Pdelay_Req */
    PTP_MSG_PDELAY_RESP,                     /* Pdelay_Resp */
    PTP_MSG_LIVE,                            /* keep alive packet */
                                             /* 5~7Ԥ�� */
    PTP_MSG_FOLLOW_UP         =       0x8,   /* Follow_Up */
    PTP_MSG_DELAY_RESP,                      /* Delay_Resp */
    PTP_MSG_PDELAY_RESP_FOLLOW_UP,           /* Pdelay_Resp_Follow_Up */
    PTP_MSG_ANNOUNCE,                        /* Announce */
    PTP_MSG_SIGNALING,                       /* Signaling */
    PTP_MSG_MANAGEMENT,                      /* Management */
    /* ����������ϢΪ�Զ���������Ϣ */
    PTP_MSG_HANDSHAKE_REQ     =       0xE,
    PTP_MSG_HANDSHAKE_RESP,
    PTP_MSG_MAX
}PTP_MSG_TYPE_E;

/*�澯���*/
typedef enum tagPTP_WARN_ID_E
{
    PTP_WARN_LINK_DOWN = 0x80,                      /* 128.��·down��ʵ�ֱ���Ϊannounce��ʱ����ʱ,��������·��һ�˵�IP*/
    PTP_WARN_LINK_UP,                               /* 129.��·UP, ��������·��һ�˵�IP */
    PTP_WARN_BMC_FAILED,                            /* 130.ѡԴʧ��,����϶�,��ʱ�����澯���� */
    PTP_WARN_MASTER_CHANGED,                        /* 131.��ǰԴ�ı�, Я����Դ����, ͬ�� */
    PTP_WARN_MASTER_SYNCHRONIZATION_FAULT,          /* 132.����Masterͬ������ */
    PTP_WARN_ANNOUCE_NEGO_FAILED,                   /* 133.Annouce����Э��ʧ�� */

    /* Added by wangchengyang for Muticast Notify,2008-9-1 */
    PTP_WARN_MUTICAST_FIRST_UP,                     /* 134.�ಥ��һ��up��ѡԴ���֮���ϱ� */

    /* added by wangchengyang for sync link notify,2008-8-22 */
    PTP_WARN_SYNC_UP,                               /* 135.Sync����Э�̳ɹ�,ʱ��ͬ����·�����ɹ�֮��֪ͨ��Ʒ�߲���� */
    PTP_WARN_SYNC_DOWN,                             /* 136.Sync����Э��ʧ�ܻ��ߵ���ȡ��,ʱ��ͬ����·����ʧ��֮��֪ͨ��Ʒ�߲����
                                                     * �ಥ��ʱ����ʱʱ�ϱ�  */
    PTP_WARN_DELAY_NEGO_DOWN,                     /*137.DelayЭ��ʧ�ܣ��ϱ�Down�澯*/
    PTP_WARN_DELAY_NEGO_UP,                       /*138.DelayЭ�̳ɹ����ϱ�Up�澯*/
    PTP_WARN_ANN_NEGO_REFUSE,                     /*139.AnnЭ�ܾ̾����ϱ�Refuse�澯*/
    PTP_WARN_SYNC_NEGO_TIMEOUT,                   /*140.SyncЭ�̳�ʱ���ϱ�Timeout�澯*/
    PTP_WARN_SYNC_NEGO_REFUSE,                    /*141.SyncЭ�ܾ̾����ϱ�Refuse�澯*/
    PTP_WARN_DELAY_TIMEOUT,                       /*142.DelayЭ�̳�ʱ���ϱ�Timeout�澯*/
    PTP_WANR_DELAY_REFUSE,                        /*143.DelayЭ�ܾ̾����ϱ�Refuse�澯*/
    PTP_WARN_ID_MAX                                 /* 144.PTP WARNING ID ���ֵ */
    /* the end of wangchengyang's addition */
}PTP_WARNINGID_E;

/* ���Կ��� */
typedef enum tagPTP_DEBUG_FLAG_E
{
    PTP_DEBUG_STATE  = 0x01,        /* PTP״̬��Ǩ���� */
    PTP_DEBUG_INPUT  = 0X02,        /* ���յ�PTP���ĵ��� */
    PTP_DEBUG_OUTPUT = 0X04,        /* ���͵�PTP���ĵ��� */
    PTP_DEBUG_TIMER  = 0X08,        /* PTP��ʱ���ĵ��� */
    PTP_DEBUG_WARN   = 0X10         /* PTP�澯�ĵ��� */
}PTP_DEBUG_FLAG_E;

/*ѡԴģʽ����*/
typedef enum tagPTP_BMC_SELECT_MODE_E
{
    PTP_BMC_SELECT_AUTO,       /*  �Զ�ѡԴ�� Ĭ��ֵ */
    PTP_BMC_SELECT_MANUAL,     /*  �ֶ�ѡԴ�� ָ��ĳ��ԴΪͬ��Դ */
}PTP_BMC_SELECT_MODE_E;

/* �����ⲿ֪ͨ���� */
typedef enum tagPTP_EXTERN_EVENT_E
{
    PTP_EXTERN_EVENT_MASTER_LOCKED =0,     /* 0  master������׼ʱ��Դ */
    PTP_EXTERN_EVENT_MASTER_UNLOCKED,      /* 1  masterʧ��*/
    PTP_EXTERN_EVENT_MAX
}PTP_EXTERN_EVENT_E;

/* Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/3/26 */
/* ʱ��Դ����ö��ֵ���� */
typedef enum tagPTP_TIMESOURCE_E
{
    PTP_TIMESOURCE_ATOMIC     = 0x10,
    PTP_TIMESOURCE_GPS        = 0x20,
    PTP_TIMESOURCE_TRADIO     = 0x30,
    PTP_TIMESOURCE_PTP        = 0x40,
    PTP_TIMESOURCE_NTP        = 0x50,
    PTP_TIMESOURCE_HANDSET    = 0x60,
    PTP_TIMESOURCE_OTHER      = 0x90,
    PTP_TIMESOURCE_OSCILLATOR = 0xa0,
    PTP_TIMESOURCE_MAX        = 0xFF
}PTP_TIMESOURCE_E;
/*End of Added by wangchengyang-xujun62830-57575, 2009/3/26 */

/*Added by Anish K Kurian & Wangchengyang72338 & 62830, for New profile, 2010/9/21 */
/*  define way mode */
typedef enum tagPTP_WAY_MODE_E
{
    PTP_WAY_MODE_ONE,
    PTP_WAY_MODE_TWO
}PTP_WAY_MODE_E;

/* define PTST types */
typedef enum tagPTP_PTSF_TYPE_E
{
    PTP_PTSF_ANNOUNCE,
    PTP_PTSF_SYNC,
    PTP_PTSF_UNUSED
}PTP_PTSF_TYPE_E;

/*define the cause of warning*/
typedef enum tagPTP_WARN_CAUSE_E
{
    PTP_WARN_CAUSE_LOCALCLASS,              /* server��class���ڱ��˵�class����ѡԴʧ�� */
    PTP_WARN_CAUSE_INVALID_MASTER_CLASS,    /* server��class��Ч������80-110��Χ��*/
    PTP_WARN_CAUSE_COMMON_MASTER_INVALID ,  /*ͨ��ԭ��:Դ��Ч����PTSF�ȣ���������չ*/
    PTP_WARN_CAUSE_MAX
}PTP_WARN_CAUSE_E;/*ѡԴʧ��ԭ��*/

/* End of Added by Anish K Kurian & Wangchengyang72338 & 62830, 2010/9/21 */

/* Add by dutianyi00217007, 2014/2/12,  */
typedef enum tagPTP_MASTER_CFG_CLOCK_CLASS_FLAG_E
{
    PTP_MASTER_CFG_INIT_CLOCK_CLASS,
    PTP_MASTER_CFG_MULTI_CLOCK_CLASS,
    PTP_MASTER_CFG_G8275_CLOCK_CLASS,
    PTP_MASTER_CFG_CLOCK_CLASS_MAX
}PTP_MASTER_CFG_CLOCK_CLASS_FLAG_E;
/* End of addition by dutianyi00217007, 2014/2/12 */

/* ʱ�������� */
typedef struct tagPTP_TIME_INTERVAL_S
{
    UULONG ullScaledNanoseconds;
}PTP_TIME_INTERVAL_S;

/* Modified by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/3/23 */
/* �˿ڵ�ַ���� */
typedef struct tagPTP_PORT_ADDR_S
{
    USHORT  usNetworkProtocol;
    USHORT  usAddressLength;
    union
    {
        ULONG   ulIpv4;        /* �����ֽ��� */
        UCHAR   ucMacAddr[8];  /*physical��ַ 8�ֽ�Ϊ�˶���*/
        ULONG   ulIpv6[4];  /*IPv6��ַ�������ֽ��� */
    }unAddr;
}PTP_PORT_ADDR_S;
/*End of Modified by wangchengyang-xujun62830-57575, 2009/3/23 */

typedef struct tagPTP_PACKET_STAT_S
{
    /* Announce��Sync���շ�ֻ������һ�˴��ڣ�
     * �����slave���ǽ��ո����������master���Ƿ��͸���
     * Sync��Ϣ�շ���FPGAʵ�֣�����ͳ�������壬ֻ��Ԥ���������� */
    ULONG ulRcvSndAnnouncePackets;
    ULONG ulRcvSndSyncPackets;
    ULONG ulRcvSignalingPackets;
    ULONG ulSndSignalingPackets;

    /* ͳ����Ϣ */
    ULONG ulTotalRcvPackets;
    ULONG ulTotalSndPackets;

    /* ���յ��Ĵ������syncΪ�������� */
    ULONG ulTotalErrorPackets;
    /*������ */
    ULONG ulTotalDropPackets;

    /* ����,����һ�㲻��Ӱ��Э�鴦��������֪����;��·���˶��ٰ�added by wangchengyang for stat. 2008-06-16 */
    ULONG ulAnnSequenceError;  /* announce���� */
    ULONG ulSigSequenceError;  /* signaling���� */
}PTP_PACKET_STAT_S;

typedef struct tagPTP_SLAVE_PACKET_S
{       
    ULONG ulSndAnnReqPackets;        /*����announceЭ��������*/
    ULONG ulRcvAnnReplyPackets;      /*����announceЭ��Ӧ����*/
    ULONG ulRcvAnnRefusePackets;     /*����announceЭ�ܾ̾�����*/
    
    ULONG ulRcvAnnPackets;           /*����announce���� */
  
    ULONG ulSndSyncReqPackets;       /*����sync������*/    
    ULONG ulRcvSyncReplyPackets;     /*����syncӦ����*/
    ULONG ulRcvSyncRefusePackets;    /*����sync �ܾ�����*/
  
    ULONG ulSndDelayReqPackets;      /*����Delay������ */
    ULONG ulRcvDelayReplyPackets;    /*����DelayӦ����*/
    ULONG ulRcvDelayRefusePackets;   /*����Delay �ܾ�����*/
  
    ULONG ulAnnSequenceError;         /* ����announce���� */
    ULONG ulSignalingSequenceError;   /* ����signaling���� */
    ULONG ulSndSignalingError;        /* ����signaling����ʧ�� */

    ULONG ulSndAnnCancelPackets;     /*����announce ȡ������*/
    ULONG ulRcvAnnCancelAckPackets;  /*����announce ȡ��ȷ�ϱ���*/    
    ULONG ulRcvAnnCancelPackets;     /*����announce ȡ������*/
    ULONG ulSndAnnCancelAckPackets;  /*����announce ȡ��ȷ�ϱ���*/

    ULONG ulSndSyncCancelPackets;    /*����sync ȡ������*/
    ULONG ulRcvSyncCancelAckPackets; /*����sync ȡ��ȷ�ϱ���*/
    ULONG ulRcvSyncCancelPackets;    /*����sync ȡ������*/
    ULONG ulSndSyncCancelAckPackets; /*����sync ȡ��ȷ�ϱ���*/  

    ULONG ulSndDelayCancelPackets;    /*����delay ȡ������*/
    ULONG ulRcvDelayCancelAckPackets; /*����delay ȡ��ȷ�ϱ���*/
    ULONG ulRcvDelayCancelPackets;    /*����delay ȡ������*/
    ULONG ulSndDelayCancelAckPackets; /*����delay ȡ��ȷ�ϱ���*/
    
    ULONG  ulReserve[8];        /*�����ֶΣ����Ժ���չ*/
      
}PTP_SLAVE_STAT_S;

/* ʹ�ܱ����Ϣ */
typedef struct tagPTP_ENABLEINFO_S
{
    BOOL_T bAccepMasterTabEnable;   /* �ɽ���master�б�ʹ�ܱ�� */
    BOOL_T bUnicastNego;            /* ʹ�ܵ���Э�̱�� */
    ULONG ulPortEnable;             /* �˿�ʹ�ܱ�� */
}PTP_ENABLEINFO_S;

/* ʱ��ID���� */
#pragma pack(1)
typedef UCHAR PTP_CLOCK_ID_SZ[PTP_CLOCK_ID_LEN];
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/* �˿�ID���� */
#pragma pack(1)
typedef struct tagPTP_PORT_ID_S
{
    PTP_CLOCK_ID_SZ szClockId;
    USHORT          usPortNumber;
}PTP_PORT_ID_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

typedef struct tagSLAVE_PACKET_LIST_S
{
    PTP_CLOCK_ID_SZ  szClockId;
    PTP_SLAVE_STAT_S stSlaveStat;
}PTP_SLAVE_STAT_LIST_S;

/*Added by weishanfengwKF61331, ���Ӻ�����������Ϣ�ṹ��, 2011/11/23   ���ⵥ��:S.PTP.ANNCHOOK.01 */
typedef struct tagPTP_Grant_Para_S
{
    ULONG           ulMsgType;           /*��Ϣ����: Ann ����Sync����Delay/Pdelay����*/
    PTP_PORT_ID_S   stPortId;            /*Slave�˵�Port Id*/
    CHAR            cAnnInterval;        /*Announce���ͼ��-3~ 4 ,ʵ��ʱ��ȡ��ֵ�Ķ���*/
    CHAR            cSlaveFlag;          /*��������������Ƿ�����slave�б�*/
    CHAR            cPad[4];             /*�����ֶ�*/
}PTP_GRANT_PARA_S;
/* End of Added by weishanfengwKF61331, 2011/11/23   ���ⵥ��:S.PTP.ANNCHOOK.01 */

typedef struct tagPTP_UNICAST_MASTER_S
{
    /* ������ */
    BOOL_T              bLink;   /*��·ͨ�ϱ��*/
    BOOL_T              bValid;  /*�ڵ��Ƿ���Ч */
    BOOL_T              bNegoEnable; /* ��������Э�̱�� */

    /* Э��״̬��� */
    UCHAR           ucAnnFlag; 
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;   /* pdelay �� delay ���� */
    UCHAR           ucReserved[3];

    /* ����Э�������ȡ������Ϣ�ļ����� */
    ULONG            ulAnnReqCounter;
    ULONG            ulSyncReqCounter;
    ULONG            ulDelayReqCounter;

    ULONG            ulAnnCancelCounter;
    ULONG            ulSyncCancelCounter;
    ULONG            ulDelayCancelCounter;

    PTP_PORT_ID_S   stPortId;   /*master target id ���ṩclock id��Ϣ*/
    CHAR            cPad[2];/*���*/
}PTP_UNICAST_MASTER_S;

typedef struct tagPTP_UNICAST_SLAVE_S
{
    /* Э��״̬��� */
    UCHAR           ucAnnFlag;
    UCHAR           ucSyncFlag;
    UCHAR           ucDelayFlag;       /* pdelay �� delay ���� */
    UCHAR           ucReserved;

    CHAR cLogAnnInterval;/*Ann���ķ��ͼ��*/
    CHAR cLogSyncInterval;/*Sync���ķ��ͼ��*/
    CHAR cDelayReqInterval;/*DelayReq���ķ��ͼ��*/
    UCHAR ucReserved2;

    ULONG ulAnnDurationField;/*Ann���ķ���ʱ��*/
    ULONG ulSyncDurationField;/*SYNC���ķ���ʱ��*/
    ULONG ulDelayReqDurationField;/*Delay Req���ķ���ʱ��*/

    /* Э��״̬��� */
    PTP_PORT_ADDR_S stSlaveAddr;       /*Slave�ĵ�ַ*/
    PTP_PORT_ADDR_S stExtSlaveAddr;
    PTP_PORT_ID_S   stSlaveId;         /* slave Id */
    USHORT usExtUdpPort;
}PTP_UNICAST_SLAVE_S;

typedef struct tagPTP_ACCEPT_MASTER_S
{
    BOOL_T          bValid;
    UCHAR           ucAlternatePri1;
    CHAR            cLogAnnInterval;       /* announce���ļ�� */
    PTP_PORT_ADDR_S stAcceptAddr;
    USHORT          usRcvAnnSequenceId;    /* ���յ���Announce��Ϣ��sequence id */

    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01-201, 2009/5/8 */
    /* USHORT          usResvered; */
    BOOL_T          bLink;                 /* ��·ͨ�ϱ��,TRUE��ʾ��·up,FALSE��ʾ��·down */
    ULONG           ulOutTimeHigh;         /* announce���ճ�ʱʱ���HIGHλ*/
    ULONG           ulOutTimeLow;          /* announce���ճ�ʱʱ���LOWλ*/
    /* End of Added by wangchengyang-xujun62830-57575, 2009/5/8 */
}PTP_ACCEPT_MASTER_S;


/* ʱ���������� */
#pragma pack(1)
typedef struct tagPTP_CLOCK_QA_S
{
    UCHAR   ucClockClass;                   /* ʱ�ӵȼ� */
    UCHAR   ucClockAccuracy;                /* ʱ�Ӿ��� */
    USHORT  usOffsetScaledLogVariance;      /* ʱ���ȶ��� */
}PTP_CLOCK_QA_S;
#if (VOS_ARM == VOS_HARDWARE_PLATFORM)
#pragma pack(0)
#else
#pragma pack()
#endif

/*����Ĭ�����ݼ��Ĳ�ѯ���ݽṹ*/
typedef struct tagPTP_QUERY_DEFAULT_DS
{
    /*��̬��Ա*/
    BOOL_T          bTwoStep;
    USHORT          usNumberPorts;
    PTP_CLOCK_ID_SZ szClockId ;

    /*��̬��Ա*/
    PTP_CLOCK_QA_S  stClockQuality;

    /*�����ó�Ա*/
    UCHAR           ucPriority1;
    UCHAR           ucPriority2;
    USHORT          usClockFsmMode;
    UCHAR           ucDomainNumber;
    CHAR            szReserved[3];
}PTP_QUERY_DEFAULT_DS_S;

/*���嵱ǰ���ݼ��Ĳ�ѯ���ݽṹ*/
typedef struct tagPTP_QUERY_CURRENT_DS
{
    USHORT              usStepsRemoved;
    USHORT              usReserved;
    PTP_TIME_INTERVAL_S stOffsetFromMaster;
    PTP_TIME_INTERVAL_S stMeanPathDelay;
}PTP_QUERY_CURRENT_DS_S;

/*���常�����ݼ��Ĳ�ѯ���ݽṹ*/
typedef struct tagPTP_QUERY_PARENT_DS
{
    PTP_PORT_ID_S   stParentPortId;
    BOOL_T          bParentStats;
    USHORT          usObservedParentOffsetScaledLogVar;
    UCHAR           ucGrandmasterPriority1;
    UCHAR           ucGrandmasterPriority2;
    LONG            lObservedParentClockChangeRate;
    PTP_CLOCK_ID_SZ szGrandMasterId;
    PTP_CLOCK_QA_S  stGrandmasterClockQuality;      /* ʱ������ */
    SHORT           sCurrentUtcOffset;              /* ��ǰUTCƫ�� */
    BOOL_T          bTimeScale;
    UCHAR           ucTimeSource;                   /* ʱ��Դ */
    UCHAR           ucPadding[3];


    /*��Ҫ����PortAddress: ���߶�������2���˿ڵ�ַ��ע��ͬ������*/
    PTP_PORT_ADDR_S stParentAddr[2]; /*��ǰͬ����Master�������ַ��
                                    0Ϊ��׼�ģ�1ΪAP IPSEC�ĳ���*/
    /*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
}PTP_QUERY_PARENT_DS_S;

/*����˿����ݼ��Ĳ�ѯ���ݽṹ*/
typedef struct tagPTP_QUERY_PORT_DS
{
    /*��̬��Ա*/
    PTP_PORT_ID_S stPortId;

    /*��̬��Ա*/
    UCHAR       ucPortState;
    CHAR        cLogMinDelayReqInterval;
    PTP_TIME_INTERVAL_S stPeerMeanPathDelay;
    CHAR        cLogAnnInterval;
    UCHAR       ucAnnReceiptTimeout;
    CHAR        cLogSyncInterval;
    UCHAR       ucDelayMechanism;
    CHAR        cLogMinPdelayReqInterval;
    CHAR        versionNumber;
    USHORT      usReserveed;
}PTP_QUERY_PORT_DS_S;

/* IP/UDP��Ϣ����Ҫ����
   1)�յ�����֮�󣬽��յ����ĵ�IP/UDP��Ϣ��֯��������Ϊ�����������Ľ��պ���
   2)�û�����IP��UDP�˿ڵ�ʱ�����
*/
typedef struct tagPTP_ADDRINFO_S
{
    PTP_PORT_ADDR_S  stDstPortAddr;    /* Ŀ�ĵ�ַ��Ϣ�������򡣶Խ��ձ�����˵��Ŀ�ĵ�ַ��Ϊ���ص�ַ���Է��ͱ�����˵��Ŀ�ĵ�ַΪ�Զ˵�ַ */
    PTP_PORT_ADDR_S  stSrcPortAddr;    /* Դ��ַ��Ϣ�������򡣶Խ��ձ�����˵��Դ��ַ��Ϊ�Զ˵�ַ���Է��ͱ�����˵��Դ��ַΪ���˵�ַ */
    ULONG            ulDstUdpPort;     /* Ŀ��UDP�˿ڣ������� */
    ULONG            ulSrcUdpPort;     /* ԴUDP�˿ںţ������� */
    ULONG            ulVrfIndex;       /* ����VRF index */
    ULONG            ulIfIndex;        /* �����ڱ��Ľ��մ����б�����ӿ����������������в�ʹ��*//*qinyun&luogaowei 0��ַ���� 2011-12-12*/
}PTP_ADDRINFO_S;

/*�澯,ά�����*/
typedef struct tagPTP_WARN_PARAM_S
{
    /*���и澯�Ĺ�������*/
    USHORT usPtpPortNum;              /*ʱ�Ӷ˿ں�*/
    USHORT usReserved;
    PTP_PORT_ADDR_S stLocalPortAddr;    /*���ض˿ڵ�ַ���������ϱ���Ŀ�Ķ˿ڵ�ַSLAVE OR master*/
    PTP_PORT_ADDR_S stDstPortAddr;      /*Ŀ�Ķ˿ڵ�ַ���������ϱ���Ŀ�Ķ˿ڵ�ַSLAVE OR master*/

    /*ѡԴ��صĸ澯����*/
    UCHAR           ucOldGMPriority1;     /*ʱ�����ȼ�1*/
    UCHAR           ucOldGMPriority2;     /*ʱ�����ȼ�2*/
    UCHAR           ucNewGMPriority1;     /*ʱ�����ȼ�1*/
    UCHAR           ucNewGMPriority2;     /*ʱ�����ȼ�2*/
    PTP_PORT_ID_S   stOldMPortId;         /*�ϵ�Master PortId*/
    PTP_PORT_ID_S   stNewMPortId;         /*�µ�Master PortId*/
    PTP_CLOCK_ID_SZ szOldGMId;            /*���ֶζ���Ŀǰ��һ������������Fore��Clock ID*/
    PTP_CLOCK_QA_S  stOldGMClockQuality;   /*ʱ��*/
    PTP_PORT_ADDR_S stOldMPortAddr;        /*Ŀ�Ķ˿ڵ�ַ���������ϱ���Ŀ�Ķ˿ڵ�ַSLAVE OR master*/
    PTP_CLOCK_ID_SZ szNewGMId;            /*���ֶζ���Ŀǰ��һ������������Fore��Clock ID*/
    PTP_CLOCK_QA_S  stNewGMClockQuality;   /*ʱ��*/
    PTP_PORT_ADDR_S stNewMPortAddr;        /*Ŀ�Ķ˿ڵ�ַ���������ϱ���Ŀ�Ķ˿ڵ�ַSLAVE OR master*/
    ULONG ulCause;                        /*�澯ԭ��*/
    ULONG ulOldVrfIndex;
    ULONG ulVrfIndex;
}PTP_WARN_PARAM_S;

/*Э���ѡ����������*/
typedef struct tagPTP_UNICAST_MASTER_TAB_S
{
    USHORT  usPtpPortNumber;
    USHORT  usCfgTableSize;       /* ��ǰ���õĵ���master�б�Ĵ�С,���֧��2�� */
    USHORT  usRunTableSize;       /* ��ǰ����״̬�ﵥ��master�б�Ĵ�С,��ɾ������master�б��𵥲�ȡ��֮�󣬻�û�յ���Ӧ����±����ô�С�� */
    USHORT  usTotalTableSize;     /* ��ǰ�ڵ��С */
    PTP_UNICAST_MASTER_S stUnicastMasterTab[PTP_UNICAST_MASTR_LEN];
}PTP_UNICAST_MASTER_TAB_S;      /*�ýṹ����unicastMasterTable*/

typedef struct tag_PTP_ACCEPT_MASTER_TAB_S
{
    USHORT              usActualTabSize; /*Э��Ĭ��ֵΪ0*/
    USHORT              usReserved;
    PTP_ACCEPT_MASTER_S stAcceptMaster[PTP_ACCEPT_MASTR_LEN];
}PTP_ACCEPT_MASTER_TAB_S;

/*����ʱ���������ݼ��Ĳ�ѯ���ݽṹ*/
typedef struct tagPTP_QUERY_TIME_PROPERTIES_DS
{
    /*ʱ���������ݼ���ȫ���Ƕ�̬��Ա*/
    SHORT     sCurrentUtcOffset;
    BOOL_T    bCurrentUtcOffsetValid;
    BOOL_T    bLeap59;
    BOOL_T    bLeap61;
    BOOL_T    bTimeTraceable;
    BOOL_T    bFrequencyTraceable;
    BOOL_T    bPtpTimescale;
    UCHAR     ucTimeSource;
    UCHAR     ucReserved;
}PTP_QUERY_TIME_PROPERTIES_DS_S;

/* IP struct, for query master's config */
typedef struct tagPTP_MULTI_PORT_ADDR
{
    PTP_PORT_ADDR_S stPortAddr[PTP_MAX_IP_NUM]; /*�������*/
    USHORT usNum;                  /*��ǰ���õĸ���      �������*/
    USHORT usReserved;             /* ���� */
}PTP_MULTI_PORT_ADDR_S;

/*vrf address info*/
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/

typedef struct tagPTP_ALL_PORT_ADDR_VRF_S
{
    ULONG ulNum;
    PTP_PORT_ADDR_S szPortAddr[PTP_MAX_VRF_NUM];
}PTP_ALL_PORT_ADDR_VRF_S;


/*���Ĳ�����ԭ��*/
typedef ULONG (* PTP_CAPTURE_PACKET_FUNC)(ULONG ulInOrOut, UCHAR* pucPacket, ULONG ulPacketLen, PTP_ADDRINFO_S *pstSrcIpUdpInfo);

/*SYNC�����Ƿ���Ȩ�ص�����*/
typedef ULONG (*PTP_GRANT_ACQUIRED_FUNC)(PTP_PORT_ADDR_S *pstPtpPortAdd, BOOL_T *pbGrant ,ULONG ulMsgType);

/*Modified by weishanfengwKF61331, ��Ʒ��Ȩ���º������������ı� 2011/11/23   ���ⵥ��:S.PTP.ANNCHOOK.01 */
/*SYNC�����Ƿ���Ȩ�ص�����(��)*/
typedef ULONG (*PTP_GRANT_ACQUIRED_ID_FUNC)(PTP_GRANT_PARA_S  *pstGrtInfo, BOOL_T *pbGrant);
/* End of Modified by weishanfengwKF61331, 2011/11/23   ���ⵥ��:S.PTP.ANNCHOOK.01 */

/* Debug��Ϣ�������ָ�����Ͷ��� */
typedef VOID (*PTP_DBG_OUTPUT_HOOK_FUNC)(CHAR *pszMsg);

/* Warning��Ϣ�������ָ�����Ͷ��� */
typedef VOID (*PTP_WARN_OUTPUT_HOOK_FUNC)(ULONG ulWarnID, VOID *pWarnParam);

/* Added by dutianyi00217007, MANAGEMENT MESSAGE�ص����������� */
typedef VOID (*PTP_GetInManagePkt_Func)(UCHAR *pucPacket, ULONG ulPacketLen, PTP_ADDRINFO_S *pstAddrInfo);
/* End of adding by dutianyi00217007, MANAGEMENT MESSAGE�ص����������� */

#define PTP_COPY_UNICAST_SLAVE_OBJ(DEST, SRC)                         \
    (DEST)->ucAnnFlag               = (SRC)->ucAnnFlag;               \
    (DEST)->ucSyncFlag              = (SRC)->ucSyncFlag;              \
    (DEST)->ucDelayFlag             = (SRC)->ucDelayFlag;             \
    (DEST)->cLogAnnInterval         = (SRC)->cLogAnnInterval;         \
    (DEST)->cLogSyncInterval        = (SRC)->cLogSyncInterval;        \
    (DEST)->cDelayReqInterval       = (SRC)->cDelayReqInterval;       \
    (DEST)->ulAnnDurationField      = (SRC)->ulAnnDurationField;      \
    (DEST)->ulSyncDurationField     = (SRC)->ulSyncDurationField;     \
    (DEST)->ulDelayReqDurationField = (SRC)->ulDelayReqDurationField; \
    VOS_CopyVar((DEST)->stSlaveAddr,  (SRC)->stSlaveAddr);            \
    VOS_CopyVar((DEST)->stExtSlaveAddr,  (SRC)->stExtSlaveAddr);      \
    VOS_CopyVar((DEST)->stSlaveId,  (SRC)->stSlaveId)


/******************************************************************************
*Func Name   : PTP_Init
*Description : PTP CBB ��ʼ��
*Input       : ulPtpDevType��PTP�豸���ͣ�
*              ulPtpSoftMode��PTP���ģʽ��
*              ulPtpTaskPri��PTP��������ȼ�(0~255)
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : CBBʹ����
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG  PTP_Init(ULONG ulPtpDevType,ULONG ulPtpSoftMode, ULONG ulPtpTaskPri);

/******************************************************************************
*Func Name   : PTP_UnInit
*Description : PTP CBB ȥ��ʼ��
*Input       : .
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : CBBʹ����
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_UnInit(VOID);

/******************************************************************************
*Func Name   : PTP_SetClockAccuracy
*Description : ����ʱ��ʱ�侫�ȣ���Ӧ������ϢTLV��CLOCK_ACCURACY��
*Input       : UCHAR ucClockAccuracy:ʱ��ʱ�侫�ȡ�
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockAccuracy(UCHAR ucClockAccuracy);

/******************************************************************************
*Func Name   : PTP_GetClockAccuracy
*Description : ��ȡʱ��ʱ�侫�ȣ���Ӧ������ϢTLV��CLOCK_ACCURACY��
*Input       : .
*Output      : UCHAR * pucClockAccuracy:ʱ��ʱ�侫�ȡ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockAccuracy(UCHAR *pucClockAccuracy);

/******************************************************************************
*Func Name   : PTP_SetUtcProperties
*Description : ����ʱ�ӵ�UTC���ԣ���Ӧ������ϢTLV��UTC_PROPERTIES��
*Input       : SHORT sCurrentUtcOffset:currentUtcOffset����;
*              BOOL_T bLeap61:leap61����;
*              BOOL_T bLeap59:leap59����;
*              BOOL_T bCurrentUtcOffsetValid:currentUtcOffsetValid����;
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetUtcProperties(SHORT sCurrentUtcOffset,BOOL_T bLeap61,BOOL_T bLeap59,BOOL_T bCurrentUtcOffsetValid);


/******************************************************************************
*Func Name   : PTP_GetUtcProperties
*Description : ��ȡʱ�ӵ�UTC���ԣ���Ӧ������ϢTLV��UTC_PROPERTIES.
*Input       : .
*Output      : SHORT *psCurrentUtcOffset:currentUtcOffset����;
*              BOOL_T *pbLeap61:leap61����;
*              BOOL_T *pbLeap59:leap59����;
*              BOOL_T *pbCurrentUtcOffsetValid:currentUtcOffsetValid����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetUtcProperties(SHORT* psCurrentUtcOffset,BOOL_T *pbLeap61,BOOL_T* pbLeap59,BOOL_T* pbCurrentUtcOffsetValid);


/******************************************************************************
*Func Name   : PTP_SetTraceabilityProperties
*Description : ����ʱ�ӵ�TRACEABILITY_PROPERTIES����Ӧ������ϢTLV��
                TRACEABILITY_PROPERTIES.
*Input       : .
*Output      : BOOL_T bTimeTraceable:timeTraceable����;
*              BOOL_T bFrequencyTraceable:frequencyTraceable����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetTraceabilityProperties(BOOL_T bTimeTraceable,BOOL_T bFrequencyTraceable);


/******************************************************************************
*Func Name   : PTP_GetTraceabilityProperties
*Description : ��ȡʱ�ӵ�TRACEABILITY_PROPERTIES����Ӧ������ϢTLV��
TRACEABILITY_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbTimeTraceable:timeTraceable����;
*              BOOL_T *pbFrequencyTraceable:frequencyTraceable����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTraceabilityProperties(BOOL_T *pbTimeTraceable,BOOL_T *pbFrequencyTraceable);


/******************************************************************************
*Func Name   : PTP_SetTimescaleProperties
*Description : ����ʱ�ӵ�TIMESCALE_PROPERTIES����Ӧ������ϢTLV��
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : bPtpTimescale:ptpTimescale����;
*              ucTimeSource:timeSource����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetTimescaleProperties(BOOL_T bPtpTimescale,UCHAR ucTimeSource);


/******************************************************************************
*Func Name   : PTP_GetTimescaleProperties
*Description : ��ȡʱ�ӵ�TIMESCALE_PROPERTIES����Ӧ������ϢTLV��
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbPtpTimescale:ptpTimescale����;
*              UCHAR *pucTimeSource:timeSource����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTimescaleProperties(BOOL_T *pbPtpTimescale,UCHAR *pucTimeSource);

/******************************************************************************
*Func Name   : PTP_SetUnicastNegotiate
*Description : ʹ�ܶ˿ڵ���Э�̹��ܣ���Ӧ����TLV��UNICAST_NEGOTIATION_ENABLE.
*Input       : USHORT usPtpPortNumber:PTP�˿ںţ�
               BOOL_T bEnable:ʹ�ܱ�ǡ�
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetUnicastNegotiate(USHORT usPtpPortNumber,BOOL_T bEnable);

/******************************************************************************
*Func Name   : PTP_SetLogQueryInterval
*Description : ���õ���master�б�����Ϣ��������
*Input       : cLogQueryInterval:������Ϣ���͵�����/ȡ�����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogQueryInterval(CHAR cLogQueryInterval);

/******************************************************************************
*Func Name   : PTP_GetLogQueryInterval
*Description : ��ȡ����master�б�����Ϣ��������
*Input       : 
*Output      : pcLogQueryInterval:  ��ȡ������Ϣ����/ȡ�����ֵ��ָ�롣
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogQueryInterval(CHAR* pcLogQueryInterval);

/******************************************************************************
*Func Name   : PTP_GetUnicastMasterTableSize
*Description : ��ȡ����master�б��Ԫ�ظ���
*Input       : 
*Output      : pusTableSize: ���Ԫ�ظ�����
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_GetUnicastMasterTableSize(USHORT* pusTableSize);

/******************************************************************************
*Func Name   : PTP_AddUnicastMaster
*Description : ������master���м���һ������master
*Input       : *pstPortAddr:Ҫ��ӵĵ���master,
               *pstExtPortAddr:��չ��ַ
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_AddUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_ADDR_S *pstExtPortAddr);

/******************************************************************************
*Func Name   : PTP_DelUnicastMaster
*Description : ɾ������master���е�һ��master
*Input       : *pstPortAddr:Ҫɾ���ĵ���master
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_DelUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_QueryUnicastMaster
*Description : ��ѯĳһ��ַ�Ƿ���UnicastMasterTable��
*Input       : *pstPortAddr: ��ѯ�ĵ�ַ
*Output      : *pstUnicastMaster: ���ҽڵ����Ϣ, �ⲿ�����ͷ��ڴ�
*Return      : �ɹ�����PTP_OK�����ڱ��з���PTP_ERR_NOT_FOUND,����ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryUnicastMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_UNICAST_MASTER_S *pstUnicastMaster);


/******************************************************************************
*Func Name   : PTP_QueryUnicastMasterTable
*Description : ��ѯ����master�б�
*Input       : 
*Output      : pstUnicastMasterTable:ָ�򵥲�master�б��ָ��;�ⲿ������ͷ�,����ulActualSize������
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : 
*Calls       :
*Called by   :������Ҫ�޸�
*******************************************************************************/
extern ULONG PTP_QueryUnicastMasterTable(PTP_UNICAST_MASTER_TAB_S* pstUnicastMasterTable);

/******************************************************************************
*Func Name   : PTP_QueryUnicastSlave
*Description : ��ѯĳһ��ַ�Ƿ���UnicastSalveTable��
*Input       : stPortAddr: ��ѯ��IP
               ucPtpPortNumber: ��Ӧ�Ķ˿ں�
               pstUnicastSlave: ��ѯ��Unicast slave, �ⲿ������ͷ��ڴ�
*Return      : �ɹ�����PTP_OK�������ڷ���PTP_ERR_NOT_FOUND,ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   : need modify
*******************************************************************************/
extern ULONG PTP_QueryUnicastSlave(USHORT usPtpPortNumber,
                                   PTP_PORT_ADDR_S *pstPortAddr,
                                   PTP_UNICAST_SLAVE_S *pstUnicastSlave);


/******************************************************************************
*Func Name   : PTP_AddAcceptMaster
*Description : ��AddAcceptMaster���м���һ��acceptableMaster
*Input       : *pstPortAddr:Ҫ��ӵĵ���acceptableMaster
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_AddAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_DelAcceptMaster
*Description : ɾ��AcceptMaster���е�һ��acceptableMaster
*Input       :  *pstPortAddr: Ҫɾ���ĵ���acceptableMaster�Ķ˿ڵ�ַ
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_DelAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_QueryAcceptMaster
*Description : ��ѯĳһ��ַ�Ƿ���AcceptMasterTable��
*Input       : *pstPortAddr: ��ѯ�ĵ�ַ
*Output      : *pstAcceptMaster: ���ز�ѯ�Ľڵ�
               pstAcceptMaster: �ⲿ������ͷ��ڴ�
*Return      : �ɹ�����PTP_OK��δ�ҵ�����PTP_ERR_NOT_FOUND,ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryAcceptMaster(PTP_PORT_ADDR_S *pstPortAddr, PTP_ACCEPT_MASTER_S *pstAcceptMaster);


/******************************************************************************
*Func Name   : PTP_QueryAcceptMasterTable
*Description : ��ȡʱ�ӿɽ��ܵ�Master�б���Ӧ����TLV��
ACCEPTABLE_MASTER_TABLE��
*Input       : .
*Output      : pstAcceptMasterTable: AcceptableMasterTable���ⲿ�û�������ͷ�;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryAcceptMasterTable(PTP_ACCEPT_MASTER_TAB_S *pstAcceptMasterTable);


/******************************************************************************
*Func Name   : PTP_GetAcceptMasterTableSize
*Description : ��ȡAcceptMasterTable��ʵ�ʹ��
*Input       : 
*Output      : PpActualTableSize:ָ��AcceptMaster�б�ʵ�ʹ���ָ��;��
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetAcceptMasterTableSize(USHORT * pusActualTableSize);


/******************************************************************************
*Func Name   : PTP_SetAccepMasterTableEnable
*Description : ���ö˿ڵĿɽ���Master�б��ʹ�ܿ��أ���Ӧ������ϢTLV��
ACCPTABLE_MASTER_TABLE_ENABLED��
*Input       : BOOL_T bAccepMasterTabEnable:PTP�˿�AcceptableMaster
                usPtpPortNumber: ʹ�ܵĶ˿ں�
�б�ʹ�ܿ��ء�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ��ע��:�ýӿ������ʱ�Ӷ˿����õġ�
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetAcceptMasterTableEnable(USHORT usPtpPortNumber, BOOL_T bAccepMasterTabEnable);

/******************************************************************************
*Func Name   : PTP_SetDelayMechanism
*Description : ����ʱ�Ӷ˿ڵ�DELAY_MECHANISM����Ӧ������ϢTLV��DELAY_MECHANISM
��
*Input       : USHORT usPtpPortNumber:PTP�˿ںţ�
               UCHAR ucDelayMechanism:��ʱ���ơ�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetDelayMechanism(USHORT usPtpPortNumber,UCHAR ucDelayMechanism);

/******************************************************************************
*Func Name   : PTP_GetDelayMechanism
*Description : ����ʱ�Ӷ˿ڵ�DELAY_MECHANISM
*Input       : usPtpPortNumber:PTP�˿ںţ�
*Output      : UCHAR *pucDelayMechanism:��ʱ���ơ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetDelayMechanism(USHORT usPtpPortNumber,UCHAR *pucDelayMechanism);

/******************************************************************************
*Func Name   : PTP_SetLogMinDelayReqInterval
*Description : ����ʱ�Ӷ˿ڵ�logMinDelayReqInterval
*Input       : usPtpPortNumber:PTPʱ�Ӷ˿ںţ�
               cLogMinDelayReqInterval: LogMinDelayReqInterval����ֵ
*               default:-4     range: -7 to 6
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogMinDelayReqInterval(USHORT usPtpPortNumber, CHAR cLogMinDelayReqInterval);

/******************************************************************************
*Func Name   : PTP_GetLogMinDelayReqInterval
*Description : ��ȡʱ�Ӷ˿ڵ�logMinDelayReqInterval
*Input       : usPtpPortNumber:PTPʱ�Ӷ˿ںţ�
*Output      : *pcLogMinDelayReqInterval: LogMinDelayReqInterval����ֵ��
*               default:-4     range: -7 to 6
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogMinDelayReqInterval(USHORT usPtpPortNumber,CHAR *pcLogMinDelayReqInterval);

/******************************************************************************
*Func Name   : PTP_SetLogMinPdelayReqInterval
*Description : ����ʱ�Ӷ˿ڵ�logMinPdelayReqInterval����Ӧ������ϢTLV��
LOG_MIN_MEAN_PDELAY_REQ_INTERVAL��
*Input       : usPtpPortNumber:PTP�˿ںţ�
               cLogMinPdelayReqInterval: LogMinPdelayReqInterval����ֵ��
*               default:-4     range: -7 to 6
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogMinPdelayReqInterval(USHORT usPtpPortNumber,CHAR cLogMinPdelayReqInterval);

/******************************************************************************
*Func Name   : PTP_SetLogMinPdelayReqInterval
*Description : ����ʱ�Ӷ˿ڵ�logMinPdelayReqInterval����Ӧ������ϢTLV��
LOG_MIN_MEAN_PDELAY_REQ_INTERVAL��
*Input       : usPtpPortNumber:PTP�˿ںţ�
               cLogMinPdelayReqInterval: LogMinPdelayReqInterval����ֵ��
*               default:-4     range: -7 to 6
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogMinPdelayReqInterval(USHORT usPtpPortNumber,CHAR *pcLogMinPdelayReqInterval);

/******************************************************************************
*Func Name   : PTP_PtpPortEnable
*Description : ʹ��ʱ�Ӷ˿ڣ���Ӧ������ϢTLV��ENABLE_PORT��
*Input       : USHORT usPtpPortNumber:PTPʱ�Ӷ˿ںš�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ����DESIGNATED_ENABLED�¼����뵽ʱ�Ӷ˿ڡ�
*Calls       : ״̬������
*Called by   :
*******************************************************************************/
extern ULONG PTP_PtpPortEnable(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_PtpPortDisable
*Description : ȥʹ��ʱ�Ӷ˿ڣ���Ӧ������ϢTLV��ENABLE_PORT��
*Input       : USHORT usPtpPortNumber:PTPʱ�Ӷ˿ںš�
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ����DESIGNATED_DISABLED�¼����뵽ʱ�Ӷ˿ڡ�
*Calls       : ״̬������
*Called by   :
*******************************************************************************/
extern ULONG PTP_PtpPortDisable(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_ExternNotifyPTPWithClass
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: extern module notify PTP the master's status
*        Input: USHORT usPtpPortNumber: port number
*               USHORT usCmd: notify commands
*               UCHAR ucClass:the master's class,should ensure the correction by caller
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: caller should ensure the validity of the clock class
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_ExternNotifyPTPWithClass(USHORT usPtpPortNumber, USHORT usCmd, UCHAR ucClass);

/*******************************************************************************
*    Func Name: PTP_MasterAutoNotifyWithClass
* Date Created: 2012-09-13
*       Author: wuxiaowu217009
*  Description: ͬʱ�����¡���ģʽ��ʱ�ӵȼ�ʱ���ⲿ֪ͨmaster״̬����ת��api��
*        Input: USHORT usPtpPortNumber:PTP�˿ں�
*               USHORT usCmd:notify�����֣�0:master������׼ʱ��Դ��1:masterʧ��
*               UCHAR uc1588Class:��������master����ģʽʱ�ӵȼ���
*               UCHAR ucG8265Class:��������master����ģʽʱ�ӵȼ���
*       Output: 
*       Return: 
*      Caution: ֻ������Master�࣬ͬʱ�����¡���ģʽClockClass���ⲿ�¼�֪ͨ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-13   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_MasterAutoNotifyWithClass(USHORT usPtpPortNumber, USHORT usCmd, UCHAR uc1588Class, UCHAR ucG8265Class);

/*******************************************************************************
*    Func Name: PTP_MasterGetProtocalClockClass
* Date Created: 2012-09-14
*       Author: wuxiaowu217009
*  Description: ��ѯ�¡���ģʽ��ʱ�ӵȼ�
*        Input: 
*       Output: UCHAR *uc1588Class:������ģʽʱ�ӵȼ�
*               UCHAR *ucG8265Class:������ģʽʱ�ӵȼ�
*       Return: PTP_OK:��ѯ�ɹ�
*               PTP_ERR_CLOCK_UNINIT:ʱ��ʵ��δ��ʼ��
*               PTP_ERR_MODE_INTERVAL:��Master���δʹ�ܶ�ʱ�ӵȼ�
*               PTP_ERR_PARA_INVALID:��������Ƿ�
*      Caution: ֻ������Master��ʹ����ͬʱ�����¡���ģʽClockClass�ĳ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-14   wuxiaowu217009          Create
*
*******************************************************************************/
extern ULONG PTP_MasterGetCfgClockClass(UCHAR *uc1588Class, UCHAR *ucG8265Class);

/******************************************************************************
*Func Name   : PTP_ExternChangeNotifyStack
*Description : �ⲿ����쳣֮���Э��ջ֪ͨ
*Input       : ULONG ulPtpPortNumber  ʱ�Ӷ˿ں�
*              ULONG ulCmd            �ⲿ֪ͨ�¼�
*Output      : ��
*Return      : �ɹ�����OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_ExternNotifyPTP(USHORT usPtpPortNumber, USHORT usCmd);


/******************************************************************************
*Func Name   : PTP_GetGrandClockQuality
*Description : ��ȡGrand Master ʱ������
*Input       : 
*Output      : pstGrandClockQA: ��ʱ������
                    ���û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetGrandClockQuality(PTP_CLOCK_QA_S* pstGrandClockQA);


/******************************************************************************
*Func Name   : PTP_QueryLinkStatus
*Description : ��ȡĳ����·��ͨ�����
*Input       : stPortAddr: Ҫ��ѯ��·�ĶԶ˶˿ڵ�ַ
                usPortNumber: ��Ӧ�Ķ˿ں�
*Output      : pbLinkstatus: BOOL_TRUE: ͨ  BOOL_FALSE: ��
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_QueryLinkStatus(USHORT usPortNumber, PTP_PORT_ADDR_S *pstPortAddr, BOOL_T* pbLinkstatus);


/******************************************************************************
*������      : PTP_SetClockFsmMode
*����        : ����ʱ���豸��״̬��ģʽ
*����        : ucClockFsmMode:ʱ���豸��״̬��ģʽ��
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ����Ӷ˿ں� ʹ�ܵ���Э��֮ǰ����
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockFsmMode(UCHAR ucClockFsmMode);

/******************************************************************************
*������      : PTP_GetClockFsmMode
*����        : ����ʱ���豸��״̬��ģʽ
*����        : 
*���        : pucClockFsmMode:ʱ���豸��״̬��ģʽ����
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockFsmMode(UCHAR *pucClockFsmMode);

/******************************************************************************
*������      : PTP_SetlogAnnounceInterval
*����        : ���ö˿ڵ�logAnnounceInterval���ԣ���Ӧ������ϢTLV��LOG_ ANNOUNCE_INTERVAL��
*����        : pusPtpPortNumber:ʱ�Ӷ˿ں�;
*              cLogAnnounceInterval:ʱ�Ӷ˿�LogAnnounceIntervalֵ
*               default:1      range: -3 to 3
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetLogAnnounceInterval(USHORT usPtpPortNumber, CHAR cLogAnnounceInterval);

/******************************************************************************
*������      : PTP_GetLogAnnounceInterval
*����        : ��ȡ�˿ڵ�logAnnounceInterval����
*����        : pusPtpPortNumber:ʱ�Ӷ˿ں�;
*              cLogAnnounceInterval:ʱ�Ӷ˿�cLogAnnounceIntervalֵ;
*               default:1      range: -3 to 3
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetLogAnnounceInterval(USHORT usPtpPortNumber, CHAR *pcLogAnnounceInterval);

/******************************************************************************
*������      : PTP_SetlogSyncInterval
*����        : ���ö˿ڵ�logSyncInterval���ԣ���Ӧ������ϢTLV��LOG_ ANNOUNCE_INTERVAL��
*����        : pusPtpPortNumber:ʱ�Ӷ˿ں�;
*              ucLogSyncInterval:ʱ�Ӷ˿�LogSyncIntervalֵ;
*               logSycInterval         default:-4     range: -7 to 1
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogSyncInterval(USHORT usPtpPortNumber,CHAR cLogSyncInterval);

/******************************************************************************
*������      : PTP_GetlogSyncInterval
*����        : ��ȡ�˿ڵ�LogSyncInterval����
*����        : pusPtpPortNumber:ʱ�Ӷ˿ں�;
*              pucLogSyncInterval:ʱ�Ӷ˿�LogSyncIntervalֵ;
*               logSycInterval         default:-4     range: -7 to 1
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogSyncInterval(USHORT usPtpPortNumber, CHAR * pcLogSyncInterval);

/******************************************************************************
*Func Name   : PTP_SetSyncMode
*Description : ����ʱ�ӵ�ͬ��ģʽ
*Input       : ucSyncMode: ʱ��ͬ��orƵ��ͬ��
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetSyncMode(UCHAR ucSyncMode);

/******************************************************************************
*Func Name   : PTP_GetSyncMode
*Description : ��ȡʱ�ӵ�ͬ��ģʽ
*Input       : 
*Output      : *pucSyncMode: ʱ��ͬ��orƵ��ͬ����
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetSyncMode(UCHAR *pucSyncMode);

/******************************************************************************
*Func Name   : PTP_SetCastMode
*Description : ����ʱ�ӵĵ��ಥģʽ
*Input       : ucCastMode: ����or�ಥ
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ����Ӷ˿ں� ʹ�ܵ���Э��֮ǰ����
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetCastMode(UCHAR ucCastMode);

/******************************************************************************
*Func Name   : PTP_GetCastMode
*Description : ��ȡʱ�ӵĵ��ಥģʽ
*Input       : 
*Output      : *pucCastMode: ����or�ಥor OVER MACģʽ
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetCastMode(UCHAR *pucCastMode);

/******************************************************************************
*Func Name   : PTP_GetCurrentParent
*Description : ���ǰʱ��Դ�˿ڵ�ַ
*Input       : 
*Output      : *pstParentPortAddr: ��ȡ�ĵ�ǰԴ��Ϣ?
*Return      : PTP_OK:�ɹ�.
               else: ʧ��
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-17         Lishenchuan         Create
*******************************************************************************/
extern ULONG PTP_GetCurrentParent(PTP_PORT_ADDR_S *pstParentPortAddr);

/******************************************************************************
*Func Name   : PTP_GetTotalPacketStat
*Description : ��ñ���ͳ����Ϣ
*Input       : usPtpPortNumber:��Ҫ���ͳ����Ϣ�Ķ˿ں�
*Output      : pPacketStat: ��ñ���ͳ����Ϣ��ָ�롣
*Return      : PTP_OK:�ɹ�.
               else: ʧ��
*******************************************************************************/
extern ULONG PTP_GetTotalPacketStat(USHORT usPtpPortNumber, PTP_PACKET_STAT_S *pPacketStat);

/******************************************************************************
*Func Name   : PTP_ClearTotalPacketStat
*Description : �������ͳ����Ϣ
*Input       : usPtpPortNumber:Ҫ���ͳ����Ϣ�Ķ˿ں�
*Output      : 
*Return      : PTP_OK:�ɹ�.
               else: ʧ��
*******************************************************************************/
extern ULONG PTP_ClearTotalPacketStat(USHORT usPtpPortNumber);

/******************************************************************************
*Func Name   : PTP_GetLinkPacketStat
*Description : �����·����ͳ����Ϣ
*Input       : *pstMasterPortAddress:��·Զ�˵������ַ
*Output      : *pLinkPacketStat: ��ñ���ͳ����Ϣ��ָ�롣
*Return      : PTP_OK:�ɹ�.
               else: ʧ��
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_GetLinkPacketStat(PTP_PORT_ADDR_S *pstMasterPortAddress, PTP_PACKET_STAT_S *pLinkPacketStat);

/******************************************************************************
*Func Name   : PTP_ClearLinkPacketStat
*Description : �����·����ͳ����Ϣ
*Input       : *pstMasterPortAddress:��·Զ�˵������ַ
*Output      : 
*Return      : PTP_OK:�ɹ�.
               else: ʧ��
*Remark      : Need modify
*******************************************************************************/
extern ULONG PTP_ClearLinkPacketStat(PTP_PORT_ADDR_S *pstMasterPortAddress);

/******************************************************************************
*Func Name   : PTP_SetClockQuality
*Description : ����ʱ��Դ
*Input       : *pstClockQuality: ʱ��Դ����
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetClockQuality(PTP_CLOCK_QA_S *pstClockQuality);


extern ULONG PTP_GetClockTwoStepFlag(BOOL_T   *bTwoStepFlag);



extern ULONG PTP_SetClockTwoStepFlag(BOOL_T   bTwoStepFlag);


extern ULONG PTP_SetKeepAliveMode(UCHAR ucMode);


extern ULONG PTP_SetAnnDurationField(USHORT usPtpPortNumber, ULONG ulAnnDuration);



extern ULONG PTP_SetSyncDurationField(USHORT usPtpPortNumber, ULONG ulSyncDuration);


extern ULONG PTP_SetDelayDurationField(USHORT usPtpPortNumber, ULONG ulDelayRespDuration);



extern ULONG PTP_GetKeepAliveMode(UCHAR *pucMode);


extern ULONG PTP_GetAnnDurationField(USHORT usPtpPortNumber, ULONG *pulAnnDuration);


extern ULONG PTP_GetSyncDurationField(USHORT usPtpPortNumber, ULONG *pulSyncDuration);



extern ULONG PTP_GetDelayDurationField(USHORT usPtpPortNumber, ULONG *pulDelayRespDuration);


/******************************************************************************
*Func Name   : PTP_GetClockQuality
*Description : ��ȡʱ��Դ����
*Input       : 
*Output      : *pstClockQuality: ʱ��Դ����, �ⲿ�����ڴ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetClockQuality(PTP_CLOCK_QA_S *pstClockQuality);

/******************************************************************************
*������      : PTP_SetPtpPortMaster
*����        : ʱ��ѡԴģʽ
*����        : lBMCSelectMode:ѡԴģʽ
               *pstPortAddr: �ֶ�ѡԴ���õĶ˿ڵ�ַ
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetBMCSelectMode(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*������      : PTP_GetBMCSelectMode
*����        : ʱ��ѡԴģʽ
*����        : 
*���        : pulBMCSelectMode:ѡԴģʽ
*              pstPortAddr:�ֶ�ѡԴ����Ч���ֶ�ѡԴ��Master��ַ
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : 
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-06-03         lishenchuan        create
*******************************************************************************/
extern ULONG PTP_GetBMCSelectMode(ULONG *pulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*Func Name   : PTP_GetDefaultDS
*Description : ��ȡʱ�ӵ�Ĭ�����ݼ�����Ӧ������ϢTLV��DEFAULT_DATA_SET��
*Input       : .
*Output      : PTP_QUERY_DEFAULT_DS_S* pstQueryDefaultDS
:Ĭ�����ݼ������û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetDefaultDS(PTP_QUERY_DEFAULT_DS_S* pstQueryDefaultDS);

/******************************************************************************
*Func Name   : PTP_GetCurrentDS
*Description : ��ȡʱ�ӵ�ǰ���ݼ�����Ӧ������ϢTLV��CURRENT_DATA_SET��
*Input       : .
*Output      : QUERY_CURRENT_DS_S* pstQueryCurrentDS
:��ǰ���ݼ������û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetCurrentDS(PTP_QUERY_CURRENT_DS_S* pstQueryCurrentDS);

/******************************************************************************
*Func Name   : PTP_GetParentDS
*Description : ��ȡʱ�Ӹ������ݼ�����Ӧ������ϢTLV��PARENT_DATA_SET��
*Input       : .
*Output      : PTP_QUERY_PARENT_DS_S* pstQueryDefaultDS
:�������ݼ������û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetParentDS(PTP_QUERY_PARENT_DS_S* pstQueryParentDS);

/******************************************************************************
*Func Name   : PTP_GetTimePropertiesDS
*Description : ��ȡʱ���������ݼ�����Ӧ������ϢTLV��TIME_PROPERTIES_DATA_SET��
*Input       : .
*Output      : PTP_QUERY_TIME_PROPERTIES_DS_S* pstQueryTimePropertiesDS:ʱ���������ݼ������û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetTimePropertiesDS(PTP_QUERY_TIME_PROPERTIES_DS_S* pstQueryTimePropertiesDS);

/******************************************************************************
*Func Name   : PTP_GetPtpPortDS
*Description : ��ȡָ���˿ڵ����ݼ�����Ӧ������ϢTLV��PORT_DATA_SET��
*Input       : USHORT usPtpPortNumber:PTPʱ�Ӷ˿ں�.
*Output      : PTP_QUERY_PORT_DS_S* pstQueryPtpPortDS:ʱ�Ӷ˿�����
                            �������û�������ͷš�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetPtpPortDS(USHORT usPtpPortNumber,PTP_QUERY_PORT_DS_S* pstQueryPtpPortDS);

/******************************************************************************
*������      : PTP_AddPtpPort
*����        : ����ʱ�Ӷ˿�
*����        : ulIntfNumber������˿ڱ�ʶ
*���        : pusPtpPortNumber:ʱ�Ӷ˿ں�
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_AddPtpPort(ULONG ulIntfNumber,USHORT *pusPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_AddMultiPortAddr
* Date Created: 2011-11-04
*       Author: luogaowei jijianhua00169178 
*  Description: 
*        Input: USHORT usPtpPortNumber:
*               PTP_PORT_ADDR_S *pstPortAddr:
*       Output: 
*       Return: 
*      Caution: master only & unicast only & IPv4 Only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-04   jijianhua00169178       Create
*
*******************************************************************************/
extern ULONG PTP_AddMultiPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S * pstPortAddr);

/*******************************************************************************
*    Func Name: PTP_DelMultiPortAddr
* Date Created: 2011-10-31
*       Author: jijianhua00169178
*  Description: delete a address of the special port, for master only
*        Input: USHORT usPtpPortNumber:
*               PTP_PORT_ADDR_S *pstPortAddr:
*       Output: 
*       Return: 
*      Caution: master, ipv4, unicast only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   jijianhua00169178       Create
*
*******************************************************************************/
ULONG PTP_DelMultiPortAddr(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr);

/*******************************************************************************
*    Func Name: PTP_GetMultiPortAddr
* Date Created: 2011-11-05
*       Author: jijianhua00169178
*  Description: Get Master's MultiPortAddr
*        Input: USHORT usPtpPortNumber:
*               USHORT usNetworkProtocol:
*       Output: PTP_MASTER_CFG_PORT_ADDR_S *pstMasterCfgAddr:
*       Return: 
*      Caution: Master , IPv4, Unicast only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-11-05   jijianhua00169178       Create
*
*******************************************************************************/
extern ULONG PTP_GetMultiPortAddr(USHORT usPtpPortNumber, USHORT usNetworkProtocol, PTP_MULTI_PORT_ADDR_S *pstMultiPortAddr);

/*******************************************************************************
*    Func Name: PTP_ShowMultiPortAddr
* Date Created: 2011-10-31
*       Author: jijianhua00169178
*  Description: display the address, for master only
*        Input: USHORT usNetworkProtocol:
*       Output: 
*       Return: VOID
*      Caution: master, IPv4, unicast only
                And do effect only when you configed the Multi-address
                or, it will get the address configed by API SetPtpPortAddr
                and return only one address
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   jijianhua00169178       Create
*
*******************************************************************************/
extern  ULONG  PTP_ShowMultiPortAddr(USHORT usPtpPortNumber, USHORT usNetworkProtocol);

/******************************************************************************
*������      : PTP_SetPtpPortAddr
*����        : ����ʱ�Ӷ˿ڵ�������ַ
*����        : usPtpPortNumber������˿ڱ�ʶ
             : *pstPortAddr:������ַ
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstPortAddr);

/******************************************************************************
*������      : PTP_GetPtpPortAddr
*����        : ��ȡʱ�Ӷ˿ڵ�������ַ
*����        : usPtpPortNumber������˿ڱ�ʶ
*���        : ptpPortAddr:������ַ
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpPortAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S* pPtpPortAddr);

/******************************************************************************
*������      : PTP_SetPtpPortExtendAddr
*����        : ����ʱ�Ӷ˿ڵ���չ��ַ
*����        : usPtpPortNumber������˿ڱ�ʶ
             : *pstPortAddr):��չ��ַ
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpPortExtAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstExtPortAddr);

/******************************************************************************
*������      : PTP_GetPtpPortExtendAddr
*����        : ��ȡʱ�Ӷ˿ڵ�������ַ
*����        : usPtpPortNumber������˿ڱ�ʶ
*���        : ptpPortAddr:������ַ
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpPortExtAddr(USHORT usPtpPortNumber,PTP_PORT_ADDR_S* pPtpPortAddr);

/******************************************************************************
*������      : PTP_SetPtpExtUdpPort
*����        : ����ʱ�Ӷ˿ڵ���չudp�˿ں�
*����        : usPtpPortNumber: ʱ�Ӷ˿ڱ�ʶ
             : usUdpPort      : ��չUDP�˿ں�,������
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPtpExtUdpPort (USHORT usPtpPortNumber,USHORT usUdpPort);

/******************************************************************************
*������      : PTP_GetPtpExtUdpPort
*����        : ��ȡʱ�Ӷ˿ڵ���չudp�˿ں�
*����        : usPtpPortNumber: ʱ�Ӷ˿ڱ�ʶ
*���        : pusUdpPort      : ��չUDP�˿ں�,������
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPtpExtUdpPort(USHORT usPtpPortNumber,USHORT *pusUdpPort);

/******************************************************************************
*������      : PTP_GetVersion
*����        : ��ȡPTP CBB�İ汾�źͱ���ʱ��
*����        : 
*���        : CHAR *pcVerInfo:���ص�PTP CBB�İ汾�źͱ���ʱ���ַ��������û�
                ����256�ֽڿռ�.
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetVersion(CHAR *pcVerInfo);


/******************************************************************************
*������      : PTP_GetVersion
*����        : ��ȡ��ǰ�˿ڵİ汾��
*����        : usPtpPortNumber:�˿ں�
*���        : *pcVersionNumber:�˿ڰ汾��
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPTPVersion(USHORT usPtpPortNumber,CHAR *pcVersionNumber);


/******************************************************************************
*������      : PTP_SetDomain
*����        : ����TCʱ���豸�����������Ӧ������ϢTLV��DOMAIN��
*����        : cDomainNumber:ʱ���豸��
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetDomain(UCHAR ucDomainNumber);

/******************************************************************************
*������      : PTP_GetDomain
*����        : ��ȡOC/BCʱ���豸�����������Ӧ������ϢTLV��DOMAIN��
*Input       : 
*Output      : *pcDomainNumber:ʱ���豸��
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetDomain(UCHAR *pucDomainNumber);

/******************************************************************************
*������      : PTP_SetClockIdentity
*����        : ����ʱ�ӱ�ʶ��
*����        : PTP_ClockIdentity clockIdentity:ʱ�ӱ�ʶ��
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetClockIdentity(PTP_CLOCK_ID_SZ clockIdentity);

/******************************************************************************
*������      : PTP_GetClockIdentity
*����        : ��ȡʱ�ӱ�ʶ��
*����        : 
*���        : PTP_ClockIdentity clockIdentity:ʱ�ӱ�ʶ����
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetClockIdentity(PTP_CLOCK_ID_SZ szClockID);

/******************************************************************************
*������      : PTP_SetPriority1
*����        : ����ʱ���豸��PRIORITY1��������Ӧ������ϢTLV��PRIORITY1��
*����        : cPriority1:ʱ���豸priority1��
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPriority1(UCHAR ucPriority1);

/******************************************************************************
*������      : PTP_GetPriority1
*����        : ��ȡʱ���豸��PRIORITY1��������Ӧ������ϢTLV��PRIORITY1��
*����        : 
*���        : *pcPriority1:ʱ���豸priority1��
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPriority1(UCHAR *pucPriority1);

/******************************************************************************
*������      : PTP_SetPriority2
*����        : ����ʱ���豸��PRIORITY2��������Ӧ������ϢTLV��PRIORITY2��
*����        : cPriority2:ʱ���豸priority2��
*���        : 
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_SetPriority2(UCHAR ucPriority2);

/******************************************************************************
*������      : PTP_GetPriority2
*����        : ��ȡʱ���豸��PRIORITY2��������Ӧ������ϢTLV��PRIORITY2��
*����        : 
*���        : *pcPriority2:ʱ���豸priority2��
*����ֵ      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*
*******************************************************************************/
extern ULONG PTP_GetPriority2(UCHAR *pucPriority2);

/******************************************************************************
*Func Name   : PTP_SetUniNegoQueryMaxTimes
*Description : ���õ���������Ϣ���ͳ�ʱ������
*Input       : ulUniNegoQueryMaxTimes:��������������, Э��δ˵��ȡֵ��Χ
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_SetUniNegoQueryMaxTimes(ULONG ulUniNegoQueryMaxTimes);

/******************************************************************************
*Func Name   : PTP_GetUniNegoQueryMaxTimes
*Description : ��ȡ����������Ϣ���ͳ�ʱ������
*Input       : 
*Output      : pulUniNegoQueryMaxTimes:��������������, Э��δ˵��ȡֵ��Χ��
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-27        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetUniNegoQueryMaxTimes(ULONG *pulUniNegoQueryMaxTimes);

/******************************************************************************
*Func Name   : PTP_RegFuncCapturePacketHook
*Description : ���Ĳ���ע�ắ������
*Input       : PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket ������
*Output      :
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش����룬
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             wangchengyang  Create
*******************************************************************************/
extern ULONG PTP_RegFuncCapturePacketHook(PTP_CAPTURE_PACKET_FUNC pfPtpCapturePacket);

/******************************************************************************
*Func Name   : PTP_SetReceiptTimeout
*Description : ����Announce��Ϣ���ճ�ʱ����  Ĭ��3  ��Χ2--255
*Input       : 
*Output      : ReceiptTimeout: ���ճ�ʱ����, �ⲿ�����ڴ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetReceiptTimeout(UCHAR ReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_GetReceiptTimeout
*Description : ��ȡAnnounce��Ϣ���ճ�ʱ����  Ĭ��3  ��Χ2--255
*Input       : 
*Output      : *ReceiptTimeout: ���ճ�ʱ����, �ⲿ�����ڴ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : Ŀǰ���Ϊ
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetReceiptTimeout(UCHAR *pucReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_StartNego
*Description : ������ĳ��Master�ĵ���Э��
*Input       : *pstMasterPortAddr:Ҫ�����ĵ���master
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-29        yaochengliang           Create
*******************************************************************************/
extern ULONG PTP_StartNego(PTP_PORT_ADDR_S *pstMasterPortAddr);

/******************************************************************************
*Func Name   : PTP_EndNego
*Description : ��ֹ��ĳ��Master�ĵ���Э��
*Input       : *pstMasterPortAddr:Ҫ��ֹ�ĵ���master
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-7-29        yaochengliang           Create
*******************************************************************************/
extern ULONG PTP_EndNego(PTP_PORT_ADDR_S *pstMasterPortAddr);

/******************************************************************************
*Func Name   : PTP_RegFuncSetSyncGrantNotifyHook
*Description : ANN���������Ƿ���Ȩ���Ӻ�������OMʵ��
*Input       : PTP_SYNC_GRANT_NOTIFY_FUNC pfPtpSetSyncGrantNotify ������
*Output      :
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش����룬
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-3             ����           Create
*******************************************************************************/
extern ULONG PTP_RegFuncGrantAcquiredHook(PTP_GRANT_ACQUIRED_FUNC pfPtpSetSyncGrantNotify);


/******************************************************************************
*Func Name   : PTP_ReqCancel
*Description : Master�൥������ȡ����slave�಻��ʹ�ø�API��
*Input       : usPtpPortNumber:   �˿ں�
               ulMessageType:     ��Ϣ����
               pstPtpAddrInfo:    Ҫȡ���ĵ�ַ
*Output      : *ReceiptTimeout: ���ճ�ʱ����, �ⲿ�����ڴ�
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_ReqCancel(USHORT usPtpPortNumber,ULONG ulMessageType,PTP_PORT_ADDR_S *pstPortAddr);


/*******************************************************************************
*    Func Name: PTP_ShowVersion
* Date Created: 2008-9-11
*       Author: wangchengyang
*  Description: ��ʾPTP�汾�źͱ���ʱ��
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern VOID PTP_ShowVersion(VOID);

/*******************************************************************************
*    Func Name: PTP_ShowUnicastMaster
* Date Created: 2008-9-11
*       Author: wangchengyang
*  Description: ��ʾ����master�б�
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-9-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern VOID PTP_ShowUnicastMaster(VOID);

/*******************************************************************************
*    Func Name: PTP_GetSlaveNumber
* Date Created: 2008-11-11
*       Author: wangchengyang
*  Description: master��ȡslave�б����
*        Input: VOID
*       Output: 
*       Return: �ɹ�����PTP_OK;ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-11-11    Wangchengyang    Creat the first version.
*
*******************************************************************************/
extern ULONG PTP_GetSlaveNumber(USHORT usPtpPortNumber,USHORT *pusSlaveNumber);

/******************************************************************************
*Func Name   : PTP_SetLogLiveInterval
*Description : ����keep alive����ʱ����,Ŀǰ��֧��Э��,master��slave���˱�������һ��
*Input       : CHAR cLogInterval:ʱ����(2��n����)
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLogLiveInterval (CHAR cLogInterval);

/******************************************************************************
*Func Name   : PTP_GetLogLiveInterval
*Description : ��ȡkeep alive����ʱ����
*Input       : 
*Output      : CHAR *pcLogInterval:ʱ����(2��n����):1-10
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLogLiveInterval (CHAR *pcLogInterval);

/******************************************************************************
*Func Name   : PTP_SetLiveReceiptTimeout
*Description : ����keep alive���Ľ��ճ�ʱ����
*Input       : ULONG ulReceiptTimeout:���ڵ���2,���Ǻ�ʱ�����ĳ˻�ֵ����Ч
*Output      : 
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : ��Ҫ�ȵ��ýӿ�PTP_SetLogLiveInterval���ü��
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_SetLiveReceiptTimeout (ULONG ulReceiptTimeout);

/******************************************************************************
*Func Name   : PTP_GetLiveReceiptTimeout
*Description : ��ȡkeep alive���Ľ��ճ�ʱ����
*Input       : 
*Output      : ULONG ulReceiptTimeout:��ʱ����
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     : 
*Calls       :
*Called by   :
*******************************************************************************/
extern ULONG PTP_GetLiveReceiptTimeout (ULONG *pulReceiptTimeout);

/* ע�ắ���ӿ� */
/******************************************************************************
*Func Name   : PTP_RegFuncDebugHook
*Description : ��ֵgDebugOutputָ��
*Input       : pfDebugOutPut: ����ĺ�����ַ
*Output      : 
*Return      : .
*Caution     :
*Calls       : ����ͳһ��
*Called by   :
*******************************************************************************/
extern VOID PTP_RegFuncDebugHook(PTP_DBG_OUTPUT_HOOK_FUNC pfDbgOutPut);

/******************************************************************************
*Func Name   : PTP_RegFuncWarningHook
*Description : ��ֵgWarnOutput����ָ��
*Input       : pfWarnOutPut: ����ĺ�����ַ
*Output      : 
*Return      : .
*Caution     :
*Calls       : ����ͳһ��
*Called by   :
*******************************************************************************/
extern VOID PTP_RegFuncWarningHook(PTP_WARN_OUTPUT_HOOK_FUNC pfWarnOutPut);

/******************************************************************************
*Func Name   : PTP_SetDbgSwitch
*Description : ���������Ϣ
*Input       : dbgFlag:���õ��Ա��,��(�ر�)����Ӧ��־��λ(����)
*               PTP_DEBUG_STATE  = 0x01,        PTP״̬��Ǩ����
*               PTP_DEBUG_INPUT  = 0X02,        ���յ�PTP���ĵ���
*               PTP_DEBUG_OUTPUT = 0X04,        ���͵�PTP���ĵ���
*               PTP_DEBUG_TIMER  = 0X08         PTP��ʱ���ĵ���
*               ����Ҫ���������,���λ��
*Output      : 
*Return      : .
*******************************************************************************/
extern ULONG PTP_SetDbgSwitch (ULONG ulDbgFlag);

/*Added by wangchengyang-xujun62830-57575, VISPV1R8C01, 2009/3/27 */
/******************************************************************************
*Func Name   : PTP_SetTimescaleProperties
*Description : ����ʱ�ӵ�TIMESCALE_PROPERTIES����Ӧ������ϢTLV��
TIMESCALE_PROPERTIES.
*Input       : .
*Output      : bPtpTimescale:ptpTimescale����;
*              ucTimeSource:timeSource����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-25        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_SetTimescaleProperties(BOOL_T bPtpTimescale,UCHAR ucTimeSource);

/******************************************************************************
*Func Name   : PTP_GetTimescaleProperties
*Description : ��ȡʱ�ӵ�TIMESCALE_PROPERTIES����Ӧ������ϢTLV��
                TIMESCALE_PROPERTIES.
*Input       : .
*Output      : BOOL_T *pbPtpTimescale:ptpTimescale����;
*              UCHAR *pucTimeSource:timeSource����;
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-5-25        Lishenchuan           Create
*******************************************************************************/
extern ULONG PTP_GetTimescaleProperties(BOOL_T *pbPtpTimescale,UCHAR *pucTimeSource);
/* End of Added by wangchengyang-xujun62830-57575, 2009/3/27 */

extern ULONG PTP_SetClockClassIdentify(BOOL_T bClassIdentify);


extern ULONG PTP_GetClockClassIdentify(BOOL_T *pbClassIdentify);


extern ULONG PTP_SetPriClassGroup(UCHAR ucClass0,UCHAR ucClass1,UCHAR ucClass2,UCHAR ucClass3);


extern ULONG PTP_GetPriClassGroup(UCHAR *pucClass0,UCHAR *pucClass1,UCHAR *pucClass2,UCHAR *pucClass3);


extern VOID PTP_ShowClockInfo(VOID);


extern VOID PTP_ShowPortInfo(USHORT usPtpPortNumber);


extern VOID PTP_ShowTotalPacketStatistic(USHORT usPtpPortNumber);


extern VOID PTP_ShowLinkPacketStatistic(USHORT usNetworkProtocol,
                                                                USHORT usAddressLength, UCHAR *pszIPOrMacAddr);


extern VOID PTP_ShowSlaveInfoByAddress(USHORT usNetworkProtocol,
                                                                USHORT usAddressLength, UCHAR *pszIPOrMacAddr);


extern VOID PTP_ShowAcceptMaster(VOID);


extern VOID PTP_ShowLinkStatus(VOID);


extern ULONG  Ptp_SetMacVlan(ULONG ulPhyPortNo, USHORT usVlanId, USHORT usVlanPri);



extern ULONG  Ptp_GetMacVlan(ULONG ulPhyPortNo, USHORT * pusVlanId, USHORT * pusVlanPri);

/*******************************************************************************
*    Func Name: Ptp_ShowVlanInfo
* Date Created: 2010-04-22
*       Author: zhangbo146309
*  Description: ��������˿ں���ʾ���õ�vlan id
*        Input: ULONG ulPhyPortNo:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-04-22   zhangbo146309           Create
*
*******************************************************************************/
extern VOID Ptp_ShowVlanInfo(ULONG ulPhyPortNo);

/*******************************************************************************
*    Func Name: PTP_SetMasterWeight
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Set the weigth(in new profile is priority) of the UnicastMaster
*        Input: PTP_PORT_ADDR_S *pstMaster:UnicastMaster
*               ULONG ulWeight: new profile's priority,the lesser value has high priority,no range
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: to be used only on the slave side and new profile,
*               cause don't impact the functionality, we don't check it.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_SetMasterWeight(PTP_PORT_ADDR_S *pstMaster, ULONG ulWeight);

/*******************************************************************************
*    Func Name: PTP_GetMasterWeight
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Get the weigth(in new profile is priority) of the UnicastMaster
*        Input: PTP_PORT_ADDR_S *pstMaster:UnicastMaster
*       Output: ULONG *pulWeight:to get new profile's priority
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: to be used only on the slave side and new profile,
*               cause don't impact the functionality, we don't check it.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_GetMasterWeight(PTP_PORT_ADDR_S *pstMaster, ULONG *pulWeight);


/*******************************************************************************
*    Func Name: PTP_SetPTSFByType
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Set the PTSF value of Unicast Master for different types
*        Input: PTP_PORT_ADDR_S *pstMaster:Master's Address
*               ULONG ulType: (Sync/Unusable)
*               ULONG ulPTSFValue:  0       - none PTSF
*                                   non zero- PTSF happened
*       Output: None
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: PTSF of Announce is set internally,can't be configured bu can be got
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_SetPTSFByType(PTP_PORT_ADDR_S *pstMaster, ULONG ulType, ULONG ulPTSFValue);

/*******************************************************************************
*    Func Name: PTP_GetPTSFByType
* Date Created: 2010-09-25
*       Author: Anish K Kurian & Wangchengyang72338 & 62830
*  Description: Get the PTSF value of Unicast Master for different types
*        Input: PTP_PORT_ADDR_S *pstMaster:Unicast Master's Address
*               ULONG ulType:(Sync/Unusable/Announce)
*       Output: ULONG *pulPTSFValue:
*       Return: success: PTP_OK,
*               failure:respective error code
*      Caution: PTSF of Announce is set internally,can't be configured bu can be got
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-09-25   Anish K Kurian & Wangchengyang72338 & 62830  Create
*
*******************************************************************************/
extern ULONG PTP_GetPTSFByType(PTP_PORT_ADDR_S *pstMaster, ULONG ulType, ULONG *pulPTSFValue);



extern ULONG PTP_SetDomainSwitch(UCHAR ucSwitch);


extern ULONG PTP_GetDomainSwitch(UCHAR *pucSwitch);


extern ULONG PTP_SetConformitySwitch(UCHAR ucSwitch);


extern ULONG PTP_GetConformitySwitch(UCHAR *pucSwitch);

/*******************************************************************************
*    Func Name: PTP_SetCancelQueryMaxTimes
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: ���õ���ȡ�����ķ��ʹ���
*        Input: ULONG ulCancelQueryMaxTimes:����ȡ�����Ĵ�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create
*
*******************************************************************************/
extern ULONG PTP_SetCancelQueryMaxTimes(ULONG ulCancelQueryMaxTimes);

/*******************************************************************************
*    Func Name: PTP_GetCancelQueryMaxTimes
* Date Created: 2011-03-18
*       Author: wangchengyang62830
*  Description: ��ȡ����ȡ�����ķ��ʹ���
*        Input: 
*       Output: ULONG *pulCancelQueryMaxTimes:����ȡ�����Ĵ���
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-03-18   wangchengyang62830      Create
*
*******************************************************************************/
extern ULONG PTP_GetCancelQueryMaxTimes(ULONG *pulCancelQueryMaxTimes);


extern ULONG PTP_SetLogAnnounceSendTime(USHORT usPtpPortNumber, CHAR cLogAnnSndTime);


extern ULONG PTP_GetLogAnnounceSendTime(USHORT usPtpPortNumber, CHAR *pcLogAnnSndTime);


extern ULONG PTP_SetTimerDelayCount(ULONG ulCount);


extern ULONG PTP_GetTimerDelayCount(ULONG *pulCount);

/******************************************************************************
*Func Name   : PTP_RegFuncGrantAcquiredByIdHook
*Description : ���������Ƿ���Ȩ���Ӻ���(����Slave id����Ȩ)���ɲ�Ʒ�߲����ʵ��
*Input       : PTP_GRANT_ACQUIRED_ID_FUNC pfPtpSetSyncGrantNotify ������
*Output      :
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش����룬
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME                DESCRIPTION
*  2011-6-22            heyijun KF37287     Create
*******************************************************************************/
extern ULONG PTP_RegFuncGrantAcquiredByIdHook(PTP_GRANT_ACQUIRED_ID_FUNC pfPtpSetSyncGrantNotify);

/*******************************************************************************
*    Func Name: PTP_SetPortAddrMaxCfgNum
* Date Created: 2011-10-31
*       Author: jijianhua00169178
*  Description: set the limit of address num, max:4, for master only
*        Input: USHORT usNetworkProtocol:
*               USHORT usMaxNum:
*       Output: 
*       Return: 
*      Caution: master, IPv4, Unicast only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   jijianhua00169178       Create
*
*******************************************************************************/
extern ULONG PTP_SetPortAddrMaxCfgNum(USHORT usNetworkProtocol, USHORT usMaxNum);

/*******************************************************************************
*    Func Name: PTP_GetPortAddrMaxCfgNum
* Date Created: 2011-10-31
*       Author: jijianhua00169178
*  Description: get the limit of address num
*        Input: USHORT usNetworkProtocol:
*       Output: USHORT *pusMaxNum:
*       Return: 
*      Caution: master, IPv4, unicast only
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   jijianhua00169178       Create
*
*******************************************************************************/
extern ULONG PTP_GetPortAddrMaxCfgNum(USHORT usNetworkProtocol, USHORT *pusMaxNum);


extern ULONG PTP_SetAlternateMasterFlag(UCHAR ucFlag);


extern ULONG PTP_GetAlternateMasterFlag(UCHAR *pucFlag);


VOID PTP_ShowMultCastTimerInfo(USHORT usPtpPortNumber);


extern ULONG PTP_SetPacketFilter(BOOL_T bSetYes, USHORT usNetworkProtocol, 
                                UCHAR *pszSrcIPorMacAddr, UCHAR *pszDstIPorMacAddr);


extern ULONG PTP_AddPortAddrWithVrf(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);


extern ULONG PTP_DelPortAddrWithVrf(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);


extern ULONG PTP_GetPortAddrWithVrf(USHORT usPtpPortNumber, CHAR *pcVrfName, PTP_ALL_PORT_ADDR_VRF_S *pstAllPortAddrVrf);


extern ULONG PTP_ShowPortAddrWithVrf(USHORT usPtpPortNumber);


extern ULONG PTP_StartNegoWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);


extern ULONG PTP_EndNegoWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddr, CHAR *pcVrfName);


extern ULONG PTP_AddUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, PTP_PORT_ADDR_S*pstExtPortAddr, CHAR *pcVrfName);



extern ULONG PTP_DelUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);


extern ULONG PTP_QueryUnicastMasterWithVrf(PTP_PORT_ADDR_S *pstPortAddr, 
                                  CHAR *pcVrfName, 
                                  PTP_UNICAST_MASTER_S *pstUnicastMaster);


extern ULONG PTP_QueryLinkStatusWithVrf(USHORT usPortNumber, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName, BOOL_T* pbLink);



extern ULONG PTP_GetLinkPacketStatWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddress, 
                                 CHAR *pcVrfName, 
                                 PTP_PACKET_STAT_S *pLinkPacketStat);


extern ULONG PTP_ClearLinkPacketStatWithVrf(PTP_PORT_ADDR_S *pstMasterPortAddress, CHAR *pcVrfName);



extern ULONG PTP_SetBMCSelectModeWithVrf(ULONG ulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);


extern ULONG PTP_GetBMCSelectModeWithVrf(ULONG *pulBMCSelectMode, PTP_PORT_ADDR_S *pstPortAddr, CHAR *pcVrfName);



extern ULONG PTP_SetMasterWeightWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulWeight);



extern ULONG PTP_GetMasterWeightWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG *pulWeight);



extern ULONG PTP_SetPTSFByTypeWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulType, ULONG ulPTSFValue);



extern ULONG PTP_GetPTSFByTypeWithVrf(PTP_PORT_ADDR_S *pstMaster, CHAR *pcVrfName, ULONG ulType, ULONG *pulPTSFValue);



extern ULONG PTP_GetCurrentParentWithVrf(PTP_PORT_ADDR_S *pstParentPortAddr, CHAR *pcVrfName);



extern ULONG PTP_ShowLinkPacketStatisticWithVrf(USHORT usNetworkProtocol, USHORT usAddressLength, UCHAR *pszIPOrMacAddr, CHAR *pcVrfName);


/*******************************************************************************
*    Func Name: PTP_SetSlaveMultiSelMode
* Date Created: 2011-12-28
*       Author: limin00188004/zhangliangzhi00187023/jijianhua00169178
*  Description: ����PTP 5·ѡԴ��Ĭ��Ϊ��·ѡԴ��
*        Input: ULONG ulMultiSelMode: 0��Ϊ��·��1��Ϊ5·��Ĭ��Ϊ0������·��
*       Output: 
*       Return: PTP_OK�������롣
*      Caution: ������PTP_AddPtpPort()֮ǰ�����Ƿ�Ϊ5·ѡԴ��������Э�̺�̬���á�
*               Slave, unicast, ipv4, keepAlive new mode only.
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-28   limin00188004/zhangliangzhi00187023/jijianhua00169178    Create
*
*******************************************************************************/
extern ULONG PTP_SetSlaveMultiSelectMode(ULONG ulMultiSelMode);

/*******************************************************************************
*    Func Name: PTP_GetSlaveMultiSelMode
* Date Created: 2011-12-28
*       Author: limin00188004/zhangliangzhi00187023/jijianhua00169178
*  Description: ��ȡ�Ƿ�Ϊ5·ѡԴ��
*        Input: 
*       Output: ULONG *pulMultiSelMode:  0��Ϊ��·��1��Ϊ5·��Ĭ��Ϊ0������·��
*       Return: PTP_OK, ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-12-28   limin00188004/zhangliangzhi00187023/jijianhua00169178   Create
*
*******************************************************************************/
extern ULONG PTP_GetSlaveMultiSelectMode(ULONG *pulMultiSelMode);

/*******************************************************************************
*    Func Name: PTP_SetSeqIdCompatSwitch
* Date Created: 2012-01-06
*       Author: guo00178934
*  Description: �趨Slave��Single����SequenceID�Ƚ�ģʽ
*        Input: ULONG ulSwitch:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-06   guo00178934             Create
*
*******************************************************************************/
extern ULONG PTP_SetSeqIdCompatSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: PTP_SetDurationTimeoutPercent
* Date Created: 2012-01-07
*       Author: guo00178934
*  Description: ����Annc��Sync�� Delay Duration��Э�̳�ʱ�ٷֱ�(���Duration�İٷֱ�)
*        Input: USHORT usPtpPortNumber:
*               ULONG ulDurationType:
*               ULONG ulTimeoutPrecent:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-07   guo00178934             Create
*
*******************************************************************************/
extern ULONG PTP_SetDurationTimeoutPercent(USHORT usPtpPortNumber, ULONG ulDurationType, ULONG ulTimeoutPrecent);

/*******************************************************************************
*    Func Name: PTP_GetDurationTimeoutPercent
* Date Created: 2012-02-03
*       Author: guo00178934
*  Description: ��ȡAnnc��Sync�� Delay Duration��Э�̳�ʱ�ٷֱ�(���Duration�İٷֱ�)
*        Input: USHORT usPtpPortNumber: ����˿ڱ�ʶ
*               ULONG ulDurationType: ��Ϣ����
*                 (PTP_MSG_ANNOUNCE/PTP_MSG_SYNC/PTP_MSG_DELAY_RESP/PTP_MSG_PDELAY_RESP)
*               
*       Output: ULONG *pulTimeoutPrecent:Duration��Э�̳�ʱ�ٷֱ�(50-99)
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-02-03   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_GetDurationTimeoutPercent(USHORT usPtpPortNumber, ULONG ulDurationType, ULONG *pulTimeoutPrecent);

/*******************************************************************************
*    Func Name: PTP_ShowDurationTimeoutPercent
* Date Created: 2012-02-03
*       Author: guo00178934
*  Description: 
*        Input: USHORT usPtpPortNumber: ����˿ڱ�ʶ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-02-03   limin00188004           Create
*
*******************************************************************************/
extern VOID PTP_ShowDurationTimeoutPercent(USHORT usPtpPortNumber);

/*******************************************************************************
*    Func Name: PTP_SetMasterLinkIndependSwitch
* Date Created: 2012-09-21
*       Author: limin00188004
*  Description: ����1588 PTP֧�ֶ�TLV�����Э����·����ɾ���Ŀ���
*        Input: ULONG ulSwitch: 0,�رտ���; 1,�򿪿���
*       Output: 
*       Return: 
*      Caution: ����Master��ʹ��; ���ش򿪺󣬲��ܶ�̬�رա�
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-21   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_SetMasterLinkIndependSwitch(ULONG ulSwitch);

/*******************************************************************************
*    Func Name: PTP_GetMasterLinkIndependSwitch
* Date Created: 2012-09-21
*       Author: limin00188004
*  Description: ��ȡ1588 PTP֧�ֶ�TLV�����Э����·����ɾ���Ŀ���
*        Input: ULONG *pulSwitch:����������
*       Output: 
*       Return: 
*      Caution: ����Master��ʹ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-09-21   limin00188004           Create
*
*******************************************************************************/
extern ULONG PTP_GetMasterLinkIndependSwitch(ULONG *pulSwitch);


ULONG PTP_GetSlaveStat(PTP_PORT_ID_S *pPortId, PTP_SLAVE_STAT_S *pStatPackets);


VOID PTP_ShowSlaveStat(CHAR *pcClockId);


ULONG PTP_ClearSlaveStat(PTP_PORT_ID_S *pPortId);


/*******************************************************************************
*    Func Name: PTP_SetNegoAndBmcSplitMode
* Date Created: 2013-03-22
*       Author: 
*  Description: ����ptp Э�̺�ѡԴģʽ(����Э�̺�ѡԴģʽ����)
*        Input: ULONG ulNegoMode: PTP��Э��ģʽ(�Ƿ���durationЭ��,Ĭ��Ϊ0)
*               ULONG ulBmcMode: PTPѡԴģʽ(1588����G8265.1,Ĭ��Ϊ0)
*       Output: 
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*#define PTP_NEGO_MODE_NO_DURATION   0   PTP ��Э��ģʽ: ��duration ,������1588�ݰ�
*#define PTP_NEGO_MODE_DURATION      1   PTP ��Э��ģʽ: ��duration ,��1588v2�Ŀ�ѡ16.1 ��G8265.1
*  
*#define PTP_BMC_MODE_IEEE_1588    0 ѡԴ�㷨: 1588��׼ 
*#define PTP_BMC_MODE_ITU_G82651   1 ѡԴ�㷨: 8265.1��׼
* Լ��: 
*     1.��֧�� Э��ģʽΪno duration��ѡԴ�㷨Ϊ8265.1������
*     2.�ݲ�֧��server�������
*     3.�˽ӿں�PTP_SetKeepAliveMode ����
*     4.���Э�̺�ѡԴ��һ�£�������ʾ����ͬ��ģʽ��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  
*
*******************************************************************************/
ULONG PTP_SetNegoAndBmcSplitMode(ULONG  ulNegoMode,  ULONG ulBmcMode);


/*******************************************************************************
*    Func Name: PTP_GetNegoAndBmcSplitMode
* Date Created: 2013-03-22
*       Author: 
*  Description: ��ȡ��ǰptp Э�̺�ѡԴģʽ(����Э�̺�ѡԴģʽ����)
*        Input: 
*       Output: 
*               pulNegoMode: PTP��Э��ģʽ(�Ƿ���durationЭ��,Ĭ��Ϊ0)
*               pulBmcMode:  PTPѡԴģʽ(1588����G8265.1,Ĭ��Ϊ0)
*       Return: �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  
*
*******************************************************************************/
ULONG PTP_GetNegoAndBmcSplitMode(ULONG  *pulNegoMode,  ULONG *pulBmcMode);

/*******************************************************************************
* Func Name: PTP_SendUsrManageMsg
* Date Created: 2014-01-20
* Author: dutianyi00217007
* Description: ����PTP������Ϣ
* Input: USHORT usPtpPortNumber:���͹�����Ϣ��PTP�˿ں�
*           ULONG ulVrfIndex:VRF����
*           PTP_PORT_ADDR_S *pstDstAddr:���͹�����Ϣ��Ŀ�ĵ�ַ
*           UCHAR *pucBuffer:����õĹ�����Ϣ
*           ULONG ulPacketLen:�����͵Ĺ�����Ϣ�ĳ���
* Output: 
* Return: PTP_OK
*             PTP_ERR_PORT_NUMBER:�˿ںŷ�0
*             PTP_ERR_VRF:VRF��0
*             PTP_ERR_NOT_FOUND:��ǰΪMaster��ʱ���Ҳ���Ŀ�ĵ�ַ����Ӧ��Slave
* Caution:PTP�˿ں���VRF����ֻ֧��0��ֻ���3�㵥��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-01-20   dutianyi00217007   Create
*
*******************************************************************************/

ULONG PTP_SendUsrManageMsg(USHORT usPtpPortNumber, ULONG ulVrfIndex, PTP_PORT_ADDR_S *pstDstAddr, UCHAR *pucBuffer, ULONG ulPacketLen);

/******************************************************************************
*Func Name   : PTP_RegManagePktInHook
*Description : �����Ļص�����ע�ắ��
*Input       : PTP_GetInManagePkt_Func pfPtpManagePkt:������Ϣ�ص� ������
*Output      :
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش����룬
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-01-20     dutianyi        Create
*******************************************************************************/
ULONG PTP_RegManagePktInHook(PTP_GetInManagePkt_Func pfPtpManagePkt);

/******************************************************************************
*Func Name   : PTP_MasterNotifyWithG8275Class
*Description : ����L2�鲥 G.8275.1 ClockClass���ⲿ֪ͨmaster״̬����ת
*Input       :  usPtpPortNumber:    PTP�˿ں�
                usCmd:              notify�����֣�0:master������׼ʱ��Դ��1:masterʧ��
                ucG8275Class:       ��������master��G.8275.1ʱ�ӵȼ�����Ч�������ñ�֤
*Output      :
*Return      : VOS_OK:     �ɹ�
               VOS_ERR:    ʧ��
*Caution     :1�����Բ�2�鲥���
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_MasterNotifyWithG8275Class(USHORT usPtpPortNumber, USHORT usCmd, UCHAR ucG8275Class);

/******************************************************************************
*Func Name   : PTP_SetG82751Mode
*Description : ���õ�ǰʱ���Ƿ�ʹ��L2�鲥G.8275.1ģʽ
*Input       : ULONG ulMode:  �Ƿ�ʹ��G8275.1ģʽ��0:��ʹ�� 1:ʹ��
*Output      :
*Return      : VOS_OK:     �ɹ�
               VOS_ERR:    ʧ��
*Caution     :1�����Բ�2�鲥���
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_SetG82751Mode(ULONG ulMode);

/******************************************************************************
*Func Name   : PTP_GetG82751Mode
*Description : ��ȡ��ǰʱ���Ƿ�ʹ��L2�鲥G.8275.1ģʽ
*Input       : 
*Output      : ULONG ulMode:  �Ƿ�ʹ��G8275.1ģʽ��0:��ʹ�� 1:ʹ��
*Return      : VOS_OK:     �ɹ�
               VOS_ERR:    ʧ��
*Caution     :1�����Բ�2�鲥���
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2014-02-10           dutianyi        Create
*******************************************************************************/
ULONG PTP_GetG82751Mode(ULONG *pulMode);


VOID PTP_ShowNonUnicastMaster (VOID);


#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of __ptp__common__h__    */
