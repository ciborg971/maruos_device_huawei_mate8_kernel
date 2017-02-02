

#ifndef _TCPIP_NCC_H_
#define _TCPIP_NCC_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/public/debug/tcpip_ncc_api.h"


/*******************************�궨��*****************************************/
/* NCC���б�־ */
#define NCC_QMODE                       VOS_Q_FIFO  
/* NCC���г��� */
#define NCC_QUEDEPTH                    512       

/* NCC�¼� */
#define NCC_EVENT                       0x00000001 
/* NCC��ʱ����Ϣ�����¼� */
#define NCC_EVENT_TIMER                 (1 << 15)

/* NCC�������ȼ����ֵ */
#define NCC_TASK_MAX_PRI                255
/* NCC����ջ��С16k(16384) */
#define NCC_TASK_STACKSIZE              (16*1024)

/* PPP����NCC���֧�ֵ������Ŀ */
#define NCC_DIAGNOSE_PPP_MAX            8

/* ����NCC���,NCC�����Ѵ��� */
#define NCC_TASK_ALREADY_START          0
/* �������κ�NCC���,������NCC���ʱ��Ҫ����NCC����,��ֹͣNCC��ϻ���NCC������ʱ��Ҫɾ������ */
#define NCC_TASK_NOT_START              1

/* PPP����NCC���ʱ����Сֵ,��λ:�� */
#define NCC_PPP_DETECT_TIME_MIN         10
/* PPP����NCC���ʱ�����ֵ,��λ:�� */
#define NCC_PPP_DETECT_TIME_MAX         600
/* PPP����NCC���ʱ��Ĭ��ֵ,��λ:�� */
#define NCC_PPP_DETECT_TIME_DEFAULT     30

/* NCC�������ʹ�� */
#define NCC_DIAGNOSE_USE                1
/* NCC�����δʹ�� */
#define NCC_DIAGNOSE_NOTUSE             0

/* NCC��ϴ��� */
#define NCC_DIAGNOSE_EXIST              1
/* NCC��ϲ����� */
#define NCC_DIAGNOSE_NOTEXIST           0

/* PPP��Ϣ�ռ����ر�� */
#define NCC_DIAGNOSE_DOT_START_FLAG     1

/* PPP����NCC���ͳ�Ƴ�ʼֵ��־ */
#define NCC_DIAGNOSE_STATISTIC_START_FLAG    1

/* PPP��Ϣ�ռ���¼�������ֵ */
#define NCC_PPP_DIAGNOSE_NUM            8
/* PPPɨ���¼�������ֵ */
#define NCC_PPP_DOT_NUM                 4

/* ��Ͻ��� */
#define NCC_DIAGNOSE_END                1
/* ��ϼ��� */
#define NCC_DIAGNOSE_CONTINUE           2

/* �ӿ�״̬ͳ�Ƴ�ֵ��־ */
#define NCC_PPP_IFCOUNT_FIRST           1
/* �ӿ�״̬ͳ�ƽ���ֵ��־ */
#define NCC_PPP_IFCOUNT_LAST            2

/* PPP���͵�NCC����Ƿ�ʹ�� */
#define NCC_PPP_ISENABLE (VRP_YES == g_ulNccDiagnosePppSwitch)

/*******************************ö�ٶ���***************************************/
/* NCC����ڲ������ϢID */
typedef enum enNCC_DiagnoseInfo
{
    NCC_INFO_START = 0,                 /* ��Ͽ�ʼ,��ӡ��ϱ��� */
        
    NCC_INFO_PPP_NO_INTERFACE,          /* PPP������Ͻӿڲ�����              */
    NCC_INFO_PPP_NO_PPPCTL,             /* û�нӿڶ�Ӧ��PPP���ƿ�            */
    NCC_INFO_PPP_NO_CONFIG,             /* û�нӿڶ�Ӧ��PPP���ÿ��ƿ�        */
    NCC_INFO_PPP_NO_USEDCONFIG,         /* û�нӿڶ�Ӧ��PPP��Ч���ÿ��ƿ�    */

    NCC_INFO_PPP_NORMAL_PPP,            /* �ýӿ�����ͨPPP�ӿ�                */
    NCC_INFO_PPP_MP_SUBCHANNEL,         /* �ýӿ���MP�ӽӿ�                   */
    NCC_INFO_PPP_MP_SUBCHANNEL_NORESET, /* �ýӿڱ�����ΪMP�ӽӿ�,����δ��Ч,ʵ����Ϊ��ͨPPP�ӿ����� */
    NCC_INFO_PPP_NORMAL_PPP_NORESET,    /* �ýӿڱ�����Ϊ��ͨPPP�ӿ�,����δ��Ч,ʵ����ΪMP�ӽӿ����� */
    
    NCC_INFO_PPP_SHUTDOWN,              /* PPP������Ͻӿڱ�shutdown          */
    NCC_INFO_PPP_PHY_UP,                /* PPP������Ͻӿ�����״̬UP          */
    NCC_INFO_PPP_PHY_DOWN,              /* PPP������Ͻӿ�����״̬DOWN        */
    NCC_INFO_PPP_PHY_UPDOWN_REPEAT,     /* PPP������Ͻӿ�����״̬����UP/DOWN */
    NCC_INFO_PPP_MP_PHY_DOWN,           /* PPP�������MP�ӿ�����״̬DOWN      */
    NCC_INFO_PPP_MP_PHY_UPDOWN_REPEAT,  /* PPP�������MP�ӿ�����״̬����UP/DOWN */
    NCC_INFO_PPP_LINE_UP,               /* PPP������Ͻӿ�Э��״̬UP          */
    NCC_INFO_PPP_LINE_DOWN,             /* PPP������Ͻӿ�Э��״̬DOWN        */
    NCC_INFO_PPP_LINE_UPDOWN_REPEAT,    /* PPP������Ͻӿ�Э��״̬����UP/DOWN */
    NCC_INFO_PPP_LCP_UP,                /* PPP�������LCP UP                  */
    NCC_INFO_PPP_LCP_DOWN,              /* PPP�������LCP DOWN                */
    NCC_INFO_PPP_LCP_UPDOWN_REPEAT,     /* PPP�������LCP ����UP/DOWN         */
    NCC_INFO_PPP_IPCP_UP,               /* PPP�������IPCP UP                 */
    NCC_INFO_PPP_IPCP_DOWN,             /* PPP�������IPCP DOWN               */
    NCC_INFO_PPP_IPCP_UPDOWN_REPEAT,    /* PPP�������IPCP ����UP/DOWN        */
    NCC_INFO_PPP_SHOW_DOWNREASON,       /* PPP���������ʾPPP DOWNԭ��        */

    NCC_INFO_PPP_SHOW_PPPINFO,          /* ��ʾPPP��Ϣ                        */
    NCC_INFO_PPP_MPINFO,                /* ��ʾMP��Ϣ                         */
    NCC_INFO_PPP_SHOW_NEGPKT_STATISTIC, /* ��ʾPPPЭ�̱���ͳ����Ϣ            */

    NCC_INFO_PPP_LCP_DOTINFO,           /* ��ʾLCP��ϴ��ɨ����Ϣ            */
    NCC_INFO_PPP_IPCP_DOTINFO,          /* ��ʾIPCP��ϴ��ɨ����Ϣ           */

    NCC_INFO_PPP_LOCAL_NOBINDTOMP,          /* ����δ����MP,�Զ��Ѽ���MP */
    NCC_INFO_PPP_LOCAL_BINDTOMP_NORESET,    /* �����Ѽ���MP,����δ��Ч,�Զ��Ѽ���MP */
    NCC_INFO_PPP_REMOTE_NOBINDTOMP,         /* �Զ�δ����MP,�����Ѽ���MP */
    NCC_INFO_PPP_LOCAL_NOBINDTOMP_NORESET,  /* �Զ�δ����MP,�������Ƴ�MP,����δ��Ч */

    NCC_INFO_PPP_DISCR_NEG_FAIL,            /* ����ϣ��Э���ն�������,�����ն�������Э��ʧ��,
                                               Э�̽���������˶�Э���ն�������,���±���LCPЭ�̲��� */
    NCC_INFO_PPP_DISCR_CONSISTENT_DADDR,    /* ���ӽӿ�Э�̵��ĶԶ˵��ն�����������MP���ӿڵĶԶ˵��ն�������ֵ����ͬ */
    
    NCC_INFO_PPP_MHF_PREFIX_CLASS_INVALID,  /* �Զ�������Э��ǰ׺ʡ��,���Ǳ������õ�ǰ׺ʡ�����ȼ����ڶԶ˵�
                                               MHF���ȼ�����Э�̲���.
                                              (ԭ��:MHFѡ����Э�̵�class�ȼ����������ǰ׺ʡ����֧�ֵ����ȼ�) */

    NCC_INFO_PPP_LCP_UPCHECK_NEG_NOPAP,     /* ������Ϊ��֤��,������PAPЭ��,����û��Э��ͨ��,
                                               ���ܶԶ�û�������û�����pwd */
    NCC_INFO_PPP_LCP_PAP_AUTH_FAIL,         /* ��֤�����з���PAP���ƿ�ʧ��,�ڴ治�� */
    NCC_INFO_PPP_LCP_PAP_AUTH_SERVER_FAIL,  /* ��֤��������֤��SERVER PAP��֤ʧ�� */
    NCC_INFO_PPP_LCP_PAP_AUTH_CLIENT_FAIL,  /* ��֤�����б���֤��CLIENT PAP��֤ʧ�� */

    NCC_INFO_PPP_LCP_UPCHECK_NEG_NOCHAP,    /* ������Ϊ��֤��,������CHAPЭ��,����û��Э��ͨ��,
                                               ���ܶԶ�û�������û�����pwd */
    NCC_INFO_PPP_LCP_CHAP_AUTH_FAIL,        /* ��֤�����з���CHAP���ƿ�ʧ��,�ڴ治�� */
    NCC_INFO_PPP_LCP_CHAP_AUTH_SERVER_FAIL, /* ��֤��������֤��SERVER CHAP��֤ʧ�� */
    NCC_INFO_PPP_LCP_CHAP_AUTH_CLIENT_FAIL, /* ��֤�����б���֤��CLIENT CHAP��֤ʧ�� */

    NCC_INFO_PPP_MP_NOUPTOLOWLIMIT,         /* MP�󶨵�����·��δ�ﵽ�û�ָ������С�����δ����NCP��Э�� */
    
    NCC_INFO_PPP_NOCONFIGIP,                /* �ӿ���δ���õ�ַ����IPCPЭ�̲��� */
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIP_ZERO,   /* ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַΪ0 */
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIP_INVALID,/* ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַ�Ƿ�(��ЧIP) */
    NCC_INFO_PPP_IPCP_UPCHECK_HISIP_INVALID,/* �Զ�����ΪЭ�̻�ȡ��ַ,���ǶԶ�Э�̻�õĵ�ַ�Ƿ�(��ЧIP) */
    NCC_INFO_PPP_IPCP_IPCONFLICT_LOCALSAME, /* ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õĵ�ַ�뱾������IP��ͬ(��ͻ) */
    NCC_INFO_PPP_IPCP_UPCHECK_IPCONFLIT_PEERSAME, /* ��������ΪЭ�̻�ȡ��ַ,����Э�̻�õ�����IP��ͬ(��ͻ),
                                                     �������˶�����IP����IP��ͻ*/
    NCC_INFO_PPP_IPCP_UPCHECK_GOTIPCONFLIT_MODE,  /* ���������Լ���IP,���Զ���Ȼ�����˷���IP���³�ͻ */
    NCC_INFO_PPP_IPCP_UPCHECK_HISIPCONFLIT_MODE,  /* �Զ������Լ���IP,��������Ȼ���Զ˷���IP���³�ͻ */

    NCC_INFO_PPP_IPCP_UPCHECK_IPHCINIT_FAIL,      /* IPHCģ���ʼ��ʧ�ܵ���IPCPЭ��ʧ�� */

    NCC_INFO_PPP_RCV_NO_NEGPKT,   /* �����з�������,����û���յ��Զ˵��κ�����,����Ϊ�ײ㲻ͨ
                                     ���߶Զ�����Ϊ��Э��LCP/IPCP */
    NCC_INFO_PPP_RCV_WRONG_PKTID, /* �յ�ID��ƥ��ı���,���ܵ�ԭ��:�ײ����ͱ��Ĳ���ʱ,�ײ��շ�ʱ������PPP��·����,
                                     �ײ��շ�����ʱ���� */

    NCC_INFO_PPP_MP_PARAMS_INCONSISTENT, /*Inconsistencies in the Group and Member link parameters*/

    NCC_INFO_PPP_RTR,                 /*Recived the Termination request*/ 

    NCC_INFO_PPP_ECHO_TIMEOUT,           /*Echo packet timed out */

    NCC_INFO_PPP_RCR,          /*Recived the Configureation request*/

    NCC_INFO_PPP_IPCP_RCR, /*Recived the Configureation request In OpenState*/

    NCC_INFO_PPP_IPCP_RTR, /*Recived the Termination request In OpenState*/

    NCC_INFO_PPP_NO_REASON, /* û����ϳ�����ԭ��,����ݱ��˺ͶԶ˵Ĳο���Ϣ���ж�λ */    
    
    NCC_INFO_END           /* ��Ͻ���,��ӡ��Ͻ�����Ϣ          */
}NCC_DIAGNOSEINFO_E;

/* PPP LCPɨ���ID */
typedef enum enNCC_PPPLCPDOT
{
    LCP_REQCI_LOCAL_REJ_MRRU = 0,    /* ����û�м���MP,�Զ˼���MP���±���LCP����UP/DOWN */
    LCP_REJCI_REMOTE_REJ_MRRU,       /* �Զ�û�м���MP,���˼���MP���±���LCPЭ�̲��� */
    LCP_REQCI_MRRU_INVALID,          /* �Զ˵�MRRUֵ�����ϱ�����Сֵ128��Ҫ��,NAK�Զ� */
    LCP_NAKCI_MRRU_INVALID,          /* ���ڶԶ�NAK��ֵ������Ҫ��,���Ա��˲��ٽ���MRRUЭ�� */
    LCP_UPCHECK_NO_NEG_MRRU,         /* ���˼�����MP, ����Э�̽���������˶�������MP,������LCP UP֮ǰ��鲻ͨ�� */
    
    LCP_REQCI_DISCR_NOT_NEG,         /* ���˲�����Э���ն������� */
    LCP_REQCI_DISCR_LEN_INVALID,     /* �ն�����������ΪLCP_DISCR_NULLʱ���Ȳ�Ϊ3 */
    LCP_REQCI_DISCR_TELENUM_INVALID, /* ��֧���ն�����������,����֧��HDLC�Զ������Ǳ�������,
                                        �ɽ�����g_ulDiscrSpecial����֧�ָ����͵�Э�� */
    LCP_REQCI_DISCR_CLASS_INVALID,   /* ��Ч���ն����������� */    
    LCP_UPCHECK_NO_NEG_DISCR,        /* ���˼�����MP����Ҫ��Э���ն�������, ����Э�̽���������˶�Э���ն�������,
                                        ������LCP UP֮ǰ��鲻ͨ�� */

    LCP_MPBIND_DISCR_CONSISTENT_NEGD,       /* ������·Э�̵��ĶԶ��Ƿ�Э��MP�ն��������븸ͨ����һ��*/
    LCP_MPBIND_DISCR_CONSISTENT_DLENCLASS,  /* ������·Э�̵��ĶԶ˵�MP�ն����������������븸ͨ����һ��*/
    LCP_MPBIND_DISCR_CONSISTENT_DADDR,      /* ������·Э�̵��ĶԶ˵�MP�ն�������ֵ�븸ͨ����һ��*/

    LCP_UPCHECK_NEG_NOPAPCHAP,    /* ����������PAP/CHAPЭ��,����һ����û��Э��ͨ�� */
    LCP_UPCHECK_NEG_NOCHAP,       /* ����������CHAPЭ��,����û��Э��ͨ�� */
    LCP_UPCHECK_NEG_NOPAP,        /* ����������PAPЭ��,����û��Э��ͨ�� */
    LCP_UPCHECK_MHFCLASS,         /* �Զ�������ǰ׺ʡ��Э��,���ǶԶ˵�MHF CALSS�ȼ�������֧�ֵĵȼ�������û��Э��ͨ��
                                     (ԭ��:MHFѡ����Э�̵�class�ȼ����������ǰ׺ʡ����֧�ֵ����ȼ�) */

    LCP_PAP_AUTH_SERVER_SUCCESS,                /* PAP��֤������,��֤��Server��֤�ɹ� */
    LCP_PAP_AUTH_CLIENT_SUCCESS,                /* PAP��֤������,����֤��Client��֤�ɹ� */
    LCP_PAP_AUTH_FAIL_MALLOC_PAP,               /* PAP��֤������,��ʼ��֤ʱ����PAP���ƿ�ʧ�� */
    LCP_PAP_AUTH_SERVER_FAIL,                   /* PAP��֤������,��֤��Server�յ��˶Զ˵���֤����,������֤����֤ʧ�� */
    LCP_PAP_AUTH_SERVER_FAIL_WAITREQ_TIMEOUT,   /* PAP��֤������,��֤��Server�ȴ��Զ˷�����֤����ʱ */
    LCP_PAP_AUTH_CLIENT_FAIL_SENDREQ_TIMEOUT,   /* PAP��֤������,����֤��Client�ȴ��Զ���֤�����ʱ */
    LCP_PAP_AUTH_CLIENT_FAIL_SERVER_NAK,        /* PAP��֤������,����֤��Client���Զ˾ܾ�,����֤����֤ʧ�� */
    
    LCP_CHAP_AUTH_SERVER_SUCCESS,               /* CHAP��֤������,��Ϊ��֤��Server��֤�ɹ� */
    LCP_CHAP_AUTH_CLIENT_SUCCESS,               /* CHAP��֤������,��Ϊ����֤��Client��֤�ɹ� */
    LCP_CHAP_AUTH_FAIL_MALLOC_CHAP,             /* CHAP��֤������,��ʼ��֤ʱ����CHAP���ƿ�ʧ�� */
    LCP_CHAP_AUTH_SERVER_FAIL,                  /* CHAP��֤������,��Ϊ��֤��Server��֤ʧ�� */
    LCP_CHAP_AUTH_CLIENT_FAIL,                  /* CHAP��֤������,��Ϊ����֤��Client��֤ʧ�� */
    
    LCP_FSM_OPEN_RCR,             /* ��OPEN ״̬���յ�CR���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RCA,             /* ��OPEN ״̬���յ�CA���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RCN,             /* ��OPEN ״̬���յ�CN���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RXJ_SUB_CR,      /* ��OPEN ״̬���յ�RXJ-(code reject)���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RXJ_SUB_PR,      /* ��OPEN ״̬���յ�RXJ-(protocol reject)���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RTR,             /* ��OPEN ״̬���յ�RTR(Terminate Req)���ĵ���LCPDOWN */
    LCP_FSM_OPEN_RTA,             /* ��OPEN ״̬���յ�RTA(Terminate Ack)���ĵ���LCPDOWN */

    LCP_FSM_REQCI_MAXNAKTOREJ,    /* LCPЭ�̹�����NAK�����ﵽ���ֵ��REJ��Э�̲��� */
    
    LCP_FSM_NOT_NEED_NEGO,        /* ��������Ϊ��Э��LCPֱ��UP,�Զ�����Э��LCP���±��˲�����Э�̱���,�Զ�Э�̲��� */
    
    LCP_LOOPBACK_NAK,       /* Э�̹����з��ֻ���,�յ��˶Զ˵�ħ����NAK����.�Զ˼�⵽��·,���˻���������ħ���ֺ�Э�� */
    LCP_LOOPBACK_REJ,       /* Э�̹����з��ֻ���,�յ��˶Զ˵�ħ����REJ����.�Զ˼�⵽��·,���˻���������ħ���ֺ�Э�� */
    LCP_LOOPBACK_ECHO,      /* ECHO����̽�⵽����,���յ���EchoReply����̽�⵽����,�����е�ħ���ֺͱ�����ͬ */
    LCP_LOOPBACK_IN_SERIES, /* ECHO����̽�⵽��·����,���յ���EchoReply����̽�⵽����,
                               �����е�ħ������Э�̵��ı���ħ���ֺͶԶ�ħ���ֶ�����ͬ,����Ϊ���Ӵ��� */
    LCP_PPP_MP_PARAMS_INCONSISTENT,
    LCP_PPP_ECHO_TIMEOUT,
    LCP_FSM_NEG_RTR,
    LCP_DOT_MAX_END,        /* LCP���ɼ���Ŀ  */
}NCC_PPPLCPDOT_E;

/* PPP IPCPɨ���ID */
typedef enum enNCC_PPPIPCPDOT
{
    IPCP_FSM_OPEN_RCR,        /* ��OPEN ״̬���յ�CR���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RCA,        /* ��OPEN ״̬���յ�CA���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RCN,        /* ��OPEN ״̬���յ�CN���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RXJ_SUB_CR, /* ��OPEN ״̬���յ�RXJ-(code reject)���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RXJ_SUB_PR, /* ��OPEN ״̬���յ�RXJ-(protocol reject)���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RTR,        /* ��OPEN ״̬���յ�RTR(Terminate Req)���ĵ���IPCPDOWN */
    IPCP_FSM_OPEN_RTA,        /* ��OPEN ״̬���յ�RTA(Terminate Ack)���ĵ���IPCPDOWN */

    IPCP_FSM_REQCI_MAXNAKTOREJ,     /* IPCPЭ�̹�����NAK�����ﵽ���ֵ��REJ��Э�̲��� */

    IPCP_FSM_NOT_NEED_NEGO,         /* ��������Ϊ��Э��IPCPֱ��UP,�Զ�����Э��IPCP���±��˲�����Э�̱���,�Զ�Э�̲��� */

    IPCP_IPNEG_NOIPADDR,            /* ���ӿ�δ���õ�ַ���²�����IPCP��Э��,�Ӷ�IPCPЭ�̲��� */

    IPCP_IPCONFLICT_LOCALSAME,      /* ��ַЭ�̹�����Э�̵�����ַ�뱾������IP��ͻ */
    IPCP_UPCHECK_GOTIPCONFLIT_MODE, /* ��ַЭ�̹����жԶ˸����˷���IP�����������Լ�IP���³�ͻ */
    IPCP_UPCHECK_IPCONFLIT_PEERSAME,/* ��ַЭ�̹�����Э�̵õ�������IP��ͻ */
    IPCP_UPCHECK_HISIPCONFLIT_MODE, /* ��ַЭ�̹����б��˸��Զ˷���IP�����Զ����Լ�IP���³�ͻ */

    IPCP_UPCHECK_GOTIP_ZERO,        /* ��ַЭ�̹�����Э�̵õ��ı��˵�ַΪ0 */
    IPCP_UPCHECK_GOTIP_INVALID,     /* ��ַЭ�̹�����Э�̵õ��ı��˵�ַ��Ч */
    IPCP_UPCHECK_HISIP_INVALID,     /* ��ַЭ�̹�����Э�̵õ��ĶԶ˵�ַ��Ч */
    IPCP_UPCHECK_IPHCINIT_FAIL,     /* ʹ��IPHC���ʼ��������ʧ�� */

    IPCP_MPBIND_UPSUBLINKLOWLIMIT,  /* MP�󶨵�����·��δ�����û����õ����޵���NCPδ����Э�� */
    IPCP_MPBIND_UPTODOWN_UPSUBLINKLOWLIMIT,/* MP������·DOWN��MP���Ƴ�,���߸���MP����ֵ����MP�󶨵�����·��δ
                                              �����û����õ����޵���MP IPCP DOWN */
    
    IPCP_DOT_MAX_END,         /* IPCP���ɼ���Ŀ */
}NCC_PPPIPCPDOT_E;

/* PPP MUXCPɨ���ID */
typedef enum enNCC_PPPMUXCPDOT
{
    MUXCP_DOT_MAX_END = 1,          /* MUXCP���ɼ���Ŀ */
}NCC_PPPMUXCPDOT_E;


/*******************************�ṹ���Ͷ���***********************************/
/* NCC��������Ϣ�ṹ */
typedef struct tagNCC_OUTPUT
{
    ULONG  ulInfoID;            /* NCC����ڲ������ϢID    */
    ULONG  ulResultID;          /* NCC��Ͻ�����ID        */
    ULONG  ulExecID;            /* NCC������û�ִ��ID      */
    ULONG  ulNccType;           /* NCC�������              */
    ULONG  ulIfIndex;           /* NCC��Ͻӿ�����          */
    ULONG  ulDetectTime;        /* NCC���ʱ��              */
    
    ULONG  ulDiagnoseIndex;     /* �洢��NCC��ϵ������±�  */
 }NCC_OUTPUT_S;

/* PPP����NCC PPPЭ��DOWNԭ���¼�ṹ */
typedef struct NCC_PPP_DOWNREASON
{
    ULONG ulDownReasonNum;                  /* ��ǰ��Downԭ���¼�±�,��������¼��Ŀ���Զ���ת      */
    ULONG ulDownReason[NCC_PPP_DOT_NUM];    /* Downԭ��ֵ,0��ʾû�м�¼DOWNԭ��,��0��ʾ��¼��DOWNԭ�� */
}NCC_PPP_DOWNREASON_S;




typedef struct tagNCCPPPLCPOPTION
{
    ULONG negoption;
    USHORT  mru;
    USHORT  mrru;
    UCHAR ucMhfCode; 
    UCHAR ucMhfClass;
    USHORT usGotorHis;     /* 0 - His, 1 -Got */     
    MC_PREFIXE_S stPrefixEInfo;       /*Prefix Info*/
} NCC_PPP_LCP_OPTION_S;


/* PPP����NCC PPPɨ������Ϣ��¼�ṹ */
typedef struct NCC_PPP_SCAN_DOT
{
    NCC_PPP_DOWNREASON_S stLcpDownReason;   /* LCP DOWNԭ��      */
    NCC_PPP_DOWNREASON_S stIpcpDownReason;  /* IPCP DOWNԭ��     */
    NCC_PPP_DOWNREASON_S stMuxcpDownReason; /* PPPMUXCP DOWNԭ�� */

    UCHAR   ucLcpScanDot[LCP_DOT_MAX_END];
    UCHAR   ucIpcpScanDot[IPCP_DOT_MAX_END];
    UCHAR   ucMuxcpScanDot[MUXCP_DOT_MAX_END];
    UCHAR   ucPadding[4-((LCP_DOT_MAX_END+(LONG)IPCP_DOT_MAX_END+(LONG)MUXCP_DOT_MAX_END)%4)];
    NCC_PPP_LCP_OPTION_S stLcpOption[2];   /*[0]- will contain the Group Option, [1]- will contain the Sublink Option.*/    
}NCC_PPP_SCAN_DOT_S;


/* PPP����NCC ͳ����Ϣ��¼�ṹ */
typedef struct NCC_PPP_COUNT
{
    ULONG ulFirstCount;     /* ͳ�Ƴ�ʼֵ */
    ULONG ulLastCount;      /* ͳ�ƽ���ֵ */
}NCC_PPP_COUNT_S;

/* PPP����NCC����ͳ�ƽṹ */
typedef struct tagNCC_PPP_PKTSTAT
{
    ULONG ulSndPktAll;     /* PPP���͵�Э�̱����ܵĸ��� */
    ULONG ulRcvPktAll;     /* PPP���յ�Э�̱����ܵĸ��� */

    ULONG ulRcvWrongID;    /* PPP�յ�WRONG ID���ĵĸ��� */

    ULONG ulRcvUnknownCode;/* PPP�յ�Code�ֶβ�ʶ��ı��ĸ��� */
    
    ULONG ulSndLcpRetran;  /* PPP���͵��ش����ĵĴ��� */
    ULONG ulSndIpcpRetran; /* PPP���͵��ش����ĵĴ��� */
    ULONG ulSndMuxcpRetran;/* PPP���͵��ش����ĵĴ��� */

    ULONG ulSndLcpCR;      /* PPP���͵�LCP CRЭ�̱��ĸ��� */
    ULONG ulSndIpcpCR;     /* PPP���͵�IPCP CRЭ�̱��ĸ��� */
    ULONG ulSndMuxcpCR;    /* PPP���͵�MUXCP CRЭ�̱��ĸ��� */

    ULONG ulRcvLcpCR;      /* PPP���͵�LCP��CR���ĵĴ��� */
    ULONG ulRcvIpcpCR;     /* PPP���͵��յ�IPCP��CR���ĸ��� */
    ULONG ulRcvMuxcpCR;    /* PPP���͵��յ�PPPMUXCP��CR���ĸ��� */
    

    ULONG ulSndLcpCA;      /* PPP���͵�LCP CAЭ�̱��ĸ��� */
    ULONG ulSndIpcpCA;     /* PPP���͵�IPCP CAЭ�̱��ĸ��� */
    ULONG ulSndMuxcpCA;    /* PPP���͵�MUXCP CAЭ�̱��ĸ��� */

    ULONG ulRcvLcpCA;      /* PPP���͵��յ�LCP CA���ĵ��ܸ��� */
    ULONG ulRcvIpcpCA;     /* PPP���͵��յ�IPCP CA���ĵ��ܸ��� */
    ULONG ulRcvMuxcpCA;    /* PPP���͵��յ�MUXCP CA���ĵ��ܸ��� */
    

    ULONG ulSndLcpNAK;      /* PPP���͵�LCP NAKЭ�̱��ĸ��� */
    ULONG ulSndIpcpNAK;     /* PPP���͵�IPCP NAKЭ�̱��ĸ��� */
    ULONG ulSndMuxcpNAK;    /* PPP���͵�MUXCP NAKЭ�̱��ĸ��� */

    ULONG ulRcvLcpNAK;      /* PPP���͵��յ�LCP NAK���ĵ��ܸ��� */
    ULONG ulRcvIpcpNAK;     /* PPP���͵��յ�IPCP NAK���ĵ��ܸ��� */
    ULONG ulRcvMuxcpNAK;    /* PPP���͵��յ�MUXCP NAK���ĵ��ܸ��� */
    

    ULONG ulSndLcpTR;      /* PPP���͵�LCP TRЭ�̱��ĸ��� */
    ULONG ulSndIpcpTR;     /* PPP���͵�IPCP TRЭ�̱��ĸ��� */
    ULONG ulSndMuxcpTR;    /* PPP���͵�MUXCP TRЭ�̱��ĸ��� */
    
    ULONG ulRcvLcpTR;      /* PPP���͵��յ�LCP TR���ĵ��ܸ��� */
    ULONG ulRcvIpcpTR;     /* PPP���͵��յ�IPCP TR���ĵ��ܸ��� */
    ULONG ulRcvMuxcpTR;    /* PPP���͵��յ�MUXCP TR���ĵ��ܸ��� */
    

    ULONG ulSndLcpTA;      /* PPP���͵�LCP TAЭ�̱��ĸ��� */
    ULONG ulSndIpcpTA;     /* PPP���͵�IPCP TAЭ�̱��ĸ��� */
    ULONG ulSndMuxcpTA;    /* PPP���͵�MUXCP TAЭ�̱��ĸ��� */
    
    ULONG ulRcvLcpTA;      /* PPP���͵��յ�LCP TA���ĵ��ܸ��� */
    ULONG ulRcvIpcpTA;     /* PPP���͵��յ�IPCP TA���ĵ��ܸ��� */
    ULONG ulRcvMuxcpTA;    /* PPP���͵��յ�MUXCP TA���ĵ��ܸ��� */


    ULONG ulSndLcpConfREJ;     /* PPP���͵�LCP CONFREJЭ�̱��ĸ��� */
    ULONG ulSndIpcpConfREJ;    /* PPP���͵�IPCP CONFREJЭ�̱��ĸ��� */
    ULONG ulSndMuxcpConfREJ;   /* PPP���͵�MUXCP CONFREJЭ�̱��ĸ��� */

    ULONG ulRcvLcpConfREJ;     /* PPP���յ�LCP CONFREJЭ�̱��ĸ��� */
    ULONG ulRcvIpcpConfREJ;    /* PPP���յ�IPCP CONFREJЭ�̱��ĸ��� */
    ULONG ulRcvMuxcpConfREJ;   /* PPP���յ�MUXCP CONFREJЭ�̱��ĸ��� */
    

    ULONG ulSndLcpCodeREJ;     /* PPP���͵�LCP CODEREJЭ�̱��ĸ��� */
    ULONG ulSndIpcpCodeREJ;    /* PPP���͵�IPCP CODEREJЭ�̱��ĸ��� */
    ULONG ulSndMuxcpCodeREJ;   /* PPP���͵�MUXCP CODEREJЭ�̱��ĸ��� */

    ULONG ulRcvLcpCodeREJ;     /* PPP���յ�LCP CODEREJЭ�̱��ĸ��� */
    ULONG ulRcvIpcpCodeREJ;    /* PPP���յ�IPCP CODEREJЭ�̱��ĸ��� */
    ULONG ulRcvMuxcpCodeREJ;   /* PPP���յ�MUXCP CODEREJЭ�̱��ĸ��� */
    

    ULONG ulSndProtREJ;        /* PPP���͵�PROTREJЭ�̱��ĸ��� */
    ULONG ulRcvProtREJ;        /* PPP���յ�ROTREJЭ�̱��ĸ��� */
    
    ULONG ulSndLcpEchoReq;     /* PPP���͵�EHCOREQЭ�̱��ĸ��� */
    ULONG ulSndLcpEchoReply;   /* PPP���͵�EHCOREPЭ�̱��ĸ��� */
    
    ULONG ulRcvLcpEchoReq;     /* PPP���յ�EHCOREQЭ�̱��ĸ��� */    
    ULONG ulRcvLcpEchoReply;   /* PPP���յ�EHCOREPЭ�̱��ĸ��� */
} NCC_PPP_PKTSTAT;

/* PPP����NCC �ռ���Ϣ��¼�ṹ */
typedef struct NCC_PPP_INFO
{
    ULONG ulDiagnoseNum;                        /* ��ǰ��״̬��¼�±�,��������¼��Ŀ���Զ���ת */
    UCHAR ucIfPhyState[NCC_PPP_DIAGNOSE_NUM];   /* �ӿ�����״̬                                  */
    UCHAR ucIfLineState[NCC_PPP_DIAGNOSE_NUM];  /* �ӿ�IPЭ��״̬                                */
    UCHAR ucLcpState[NCC_PPP_DIAGNOSE_NUM];     /* �ӿ�LCP״̬                                   */
    UCHAR ucIpcpState[NCC_PPP_DIAGNOSE_NUM];    /* �ӿ�IPCPЭ��״̬                              */
    UCHAR ucMuxcpState[NCC_PPP_DIAGNOSE_NUM];   /* �ӿ�PPPMUXCPЭ��״̬                          */

    NCC_PPP_COUNT_S stPhyUpCount;               /* �ӿڵײ��ϱ���Ч����UP����                    */
    NCC_PPP_COUNT_S stPhyDownCount;             /* �ӿڵײ��ϱ���Ч����DOWN����                  */    
    NCC_PPP_COUNT_S stLineUpCount;              /* �ӿ�IPЭ��UP����                              */
    NCC_PPP_COUNT_S stLineDownCount;            /* �ӿ�IPЭ��DOWN����                            */
    ULONG ulLcpOpenCount;                       /* �ӿ�LCPЭ��UP����                             */
    ULONG ulLcpDownCount;                       /* �ӿ�LCPЭ��DOWN����                           */
    ULONG ulIpcpOpenCount;                      /* �ӿ�IPCPЭ��UP����                            */
    ULONG ulIpcpDownCount;                      /* �ӿ�IPCPЭ��DOWN����                          */
    ULONG ulMuxcpOpenCount;                     /* �ӿ�PPPMUXCPЭ��UP����                        */
    ULONG ulMuxcpDownCount;                     /* �ӿ�PPPMUXCPЭ��DOWN����                      */
    
    NCC_PPP_SCAN_DOT_S stPppScanDot;            /* ���ɨ���ռ�����Ϣ                            */
    NCC_PPP_PKTSTAT    stPppStat;               /* PPPЭ�̱���ͳ����Ϣ */

    VOID *pInfo; /* �ÿռ��ɸ�����Ϣ���diagnose���̰���Ҫ�Լ����벢�����֪ͨ��diagnoseoutputʱ�ͷ� */
}NCC_PPP_INFO_S;

/* PPP����NCC �����Ϣ��¼�ṹ */
typedef struct NCC_DIAGNOSE_PPP
{
    ULONG ulIsUsed;                 /* ����ϱ����Ƿ��ѱ�ʹ��,���Ƿ�������.1��ʾ��ʹ��,0��ʾδʹ��       */
    ULONG ulExecID;                 /* �û������ִ��ID,����Ϊ0                                            */
    ULONG ulDetectTime;             /* �û���������ʱ��,��λ:��                                          */
    ULONG ulIfIndex;                /* �û��������Ͻӿ�����                                              */
    ULONG ulTimeCount;              /* ѭ����ʱ����ʱ����,��������Ϊ0ʱ��ʾ���ʱ�䵽,��ʼ���������Ͻ�� */
    ULONG ulTimeBase;               /* ѭ����ʱ������,��λ:��                                              */
    ULONG ulStatisticStartFlag;     /* ��ȡͳ�Ƴ�ʼֵ��־,1��ʾ��Ҫ��ȡͳ�Ƴ�ֵ,����(0)����ȡ              */
    NCC_PPP_INFO_S stNccPppInfo;    /* ��¼�ռ��������Ϣ                                                  */
}NCC_DIAGNOSE_PPP_S;


/*******************************ȫ�ֱ�������***********************************/
/* ��¼PPP�����Ϣ��ȫ��������� */
extern NCC_DIAGNOSE_PPP_S g_stNccDiagnosePpp[NCC_DIAGNOSE_PPP_MAX];

/* PPP����NCC��Ͽ��� */
extern ULONG g_ulNccDiagnosePppSwitch;


/*******************************��������***********************************/
extern ULONG NCC_InitCom(ULONG ulType);
extern VOID NCC_Release(VOID);
extern VOID NCC_TaskMain(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);
extern ULONG NCC_StartTask(ULONG ulTaskPri);
extern ULONG NCC_IsTaskStart(VOID);
extern ULONG NCC_IsExistUserID(ULONG ulExecID, ULONG *pulType, ULONG *pulDiagnoseIndex);
extern ULONG NCC_IsExistDiagnoseByType(ULONG ulType);
extern ULONG NCC_CheckUserID(ULONG ulExecID);
extern ULONG NCC_CheckParaByType(ULONG ulType, ULONG ulDetectTime, VOID *pstPara, ULONG *pulNccDetectTime);
extern ULONG NCC_CreateTimerByType(ULONG ulType, ULONG *pTimeBase);
extern ULONG NCC_DeleteTimerByType(ULONG ulType);
extern ULONG NCC_SetDiagnoseNccInfo(ULONG ulExecID, ULONG ulDetectTime, ULONG ulType, 
                                            VOID * pstPara, ULONG ulTimeBase);
extern VOID NCC_NotifyRelease(VOID);

extern VOID NCC_DiagnosePppTimerOut(VOID *);
extern ULONG NCC_DiagnosePpp(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppType(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIsShutdown(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppPhyState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLineState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLcpState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIpcpState(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppLcpDot(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppIpcpDot(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppMpInfo(ULONG ulDiagnoseIndex);
extern ULONG NCC_DiagnosePppStatistic(ULONG ulDiagnoseIndex);

extern VOID NCC_RecordPppState(ULONG ulDiagnoseIndex, IFNET_S *pstIfnet);
extern VOID NCC_RecordIfStatusCount(ULONG ulDiagnoseIndex, IFNET_S *pstIfnet, ULONG ulType);
extern VOID NCC_RecordPppDownReason(ULONG ulIfIndex, ULONG ulDownReason, USHORT usProtoType);
extern VOID NCC_RecordPppLcpDot(ULONG ulLcpDotIndex, ULONG ulIfIndex);
extern VOID NCC_RecordPppIpcpDot(ULONG ulIpcpDotIndex, ULONG ulIfIndex);
extern VOID NCC_RecordPppStateStatistic(ULONG ulIfIndex, UCHAR ucState, USHORT usProtocol);

extern VOID NCC_RecordPppRcvWrongID(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRetran(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvUnknownCode(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndNAK(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvNAK(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndTR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvTR(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndTA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvTA(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndConfREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvConfREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndCodeREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvCodeREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndProtREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvProtREJ(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndEchoReq(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvEchoReq(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndEchoReply(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvEchoReply(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppSndAll(PPPFSM_S *pstFsm);
extern VOID NCC_RecordPppRcvAll(PPPFSM_S *pstFsm);

extern VOID NCC_ReleaseOfInfoEnd(ULONG ulType, ULONG ulDiagnoseIndex);
extern VOID NCC_InfoOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
extern VOID NCC_AsynOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
extern VOID NCC_DiagnoseOutput(NCC_OUTPUT_S *pszOutput);
extern VOID NCC_ShowStartInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppUpdownStatistic(ULONG ulDiagnoseIndex, ULONG ulStatType, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppDownReason(NCC_OUTPUT_S *pszOutput, USHORT usProtoType, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppLcpDotInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppIpcpDotInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppDiagnoseInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowMpDiagnoseInfo(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);
extern VOID NCC_ShowPppNegPktStatistic(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);

extern VOID NCC_ShowPppCfgInfo(ULONG ulExecID, ULONG ulDiagnoseIndex);

extern VOID NCC_PrintPppState(ULONG ulPppState, CHAR *szOutBuf, ULONG ulStrLen);

extern VOID NCC_RecordPppInsconsistentOptions(ULONG ulIfIndex, PPP_LCP_OPTION_S *pstGrpOption,
        PPP_LCP_OPTION_S *pstLinkOption,USHORT ulGotFlag);

extern VOID NCC_ShowMPParameterDiffernce(NCC_OUTPUT_S *pszOutput, CHAR *pstInfo, ULONG ulStrLen);

extern VOID NCC_ShowLCPOption(NCC_PPP_LCP_OPTION_S *pstLcpOption, CHAR *pstInfo, ULONG ulStrLen);


#ifdef  __cplusplus 
}
#endif

#endif /* _TCPIP_NCC_H_ */


