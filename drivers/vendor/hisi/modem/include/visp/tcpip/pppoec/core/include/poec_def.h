

#ifndef  _POEC_DEF_H_
#define  _POEC_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/pppoec/include/poec_api.h"

/* ϵͳ������ͬʱ���е�PPPoE Client session��Ŀ */
#define PPPOE_CLIENT_MAX_SESSION 255

/*PPPoE ���ķ�����:0; ��:1*/
#define PPPOE_IN  0
#define PPPOE_OUT 1

/* references: RFC 2516 */
/* ���PPPoE ��ETHER_TYPE��  */
#define PPPOE_ETH_P_DISC 0x8863 /* discovery stage */
#define PPPOE_ETH_P_SESS 0x8864 /* session stage */

/*** PPPoE Client Session״̬ ***/
#define PPPOE_STATE_IDLE        0   /*����״̬��û�п�ʼPPPoE ����*/
#define PPPOE_STATE_PADI_SENT   1   /*����padi���ĵȴ�pado����*/
#define PPPOE_STATE_PADR_SENT   2   /*����padr���ĵȴ�pads����*/
#define PPPOE_STATE_PPP_NEG     3   /*��ʼsession�׶ε�pppЭ��*/
#define PPPOE_STATE_PPP_UP      4   /*session�׶�pppЭ���Ѿ�ͨ�������Դ�������*/

#define PPPOE_STATE_DISCOVERY   5   /* PPPoE����Discivery�׶� */
#define PPPOE_STATE_SESSION     6   /* PPPoE����Session�׶� */

/*PPP����֤�����д��ݸ�DDR������ԭ��*/
#define PPPOE_PPP_NEG_UP        1   /*��·���֪PPPOE IPCP UP*/
/* Added by Sunmo(44939) for A82D12574 */
#define PPPOE_PPP_NEG_DOWN      2   /*��·���֪PPPOE IPCP DOWN*/

/*** PPPoE Client��ʱ������ ***/
#define PPPOE_TIMER_MAX_LEN     32  /*PPPoE Client��ʱ��������ʱ��:32��*/
#define PPPOE_TIMER_MIN_LEN     1   /*PPPoE Client��ʱ�������Сʱ��:1��*/
#define PPPOE_SESSION_RESTART_TIMER_LEN     16  /*�Ự��reset ����������������ӵ���ʱ:16��*/


/*PPPoE Client���õ�DIALER��MTU*/
#define PPPOE_DIALER_MTU        1450

/***PPP ����ͷ��س���***/
#define PPPOE_PPP_ADD_CON_LEN   2   /*PPP ���ݵ�FF03��ַ�����ֶγ���*/
#define PPPOE_PPP_PROTOCOL_LEN  2   /*ppp Э���ֶγ���*/

/* ethernet ͷ���� */
#define PPPOE_ETHER_HEADER_LEN  14

/*PPPoE VER & Type �ֶγ���*/
#define PPPOE_VER_TYPE_LEN      1

/*PPPoE Code �ֶγ���*/
#define PPPOE_CODE_LEN          1

/*PPPoE Session ID �ֶγ���*/
#define PPPOE_SESSION_ID_LEN    2

/*PPPoE Length �ֶγ���*/
#define PPPOE_LENGTH_LEN        2

/* Я����Vlan ID�ֶε�ethernetͷ���� */
#define PPPOE_ETHER_HEADER_LEN_VLAN     18

/* ethernet �㲥��ַ */
#define PPPOE_MAC_BCAST_ADDR "\xff\xff\xff\xff\xff\xff"

/***��̫��ͷ����***/
#define PPPOE_HEADER_LEN        20  /*PPPoE ͷ��Ϣ��������̫��֡ͷ*/
#define PPPOE_HEADER_LEN_VLAN   24  /*PPPoE ͷ��Ϣ��������̫��֡ͷ(��vlan)*/


/* PPPoE ���ɵĳ��Ȱ���ͷ��Ϣ */
#define PPPOE_MIN_ETHERNET_PAYLOAD  6       /*PPPoE ֡ͷ*/
#define PPPOE_MAX_ETHERNET_PAYLOAD  1500    /*ethernet MTU*/

/*ɾ��VirtualAccess�ӿڵ��ӳ�ʱ��*/
#define PPPOE_DELVAIF_TIMER         10

/*** ����Ethernet ֡���� ***/

/*PPPoE ��̵���̫��֡��*/
#define PPPOE_MIN_ETHERNET_LEN \
    ( PPPOE_ETHER_HEADER_LEN + PPPOE_MIN_ETHERNET_PAYLOAD )
#define PPPOE_MIN_ETHERNET_LEN_VLAN \
    ( PPPOE_ETHER_HEADER_LEN_VLAN + PPPOE_MIN_ETHERNET_PAYLOAD )

/*PPPoE �����̫��֡��*/
/* ���� VLan ID*/
#define PPPOE_MAX_ETHERNET_LEN \
    ( PPPOE_ETHER_HEADER_LEN + PPPOE_MAX_ETHERNET_PAYLOAD )
/* �� VLan ID*/
#define PPPOE_MAX_ETHERNET_LEN_VLAN \
    ( PPPOE_ETHER_HEADER_LEN_VLAN + PPPOE_MAX_ETHERNET_PAYLOAD )


/*PPPoE TAG-TYPE �ֶγ���*/
#define PPPOE_TAG_TYPE_LEN      2

/*PPPoE TAG-LENGTH �ֶγ���*/
#define PPPOE_TAG_LENGTH_LEN    2

/*PPPoE TAG ͷ���ȣ�����type��length�����ֶΣ�*/
#define PPPOE_TAG_HEAD_LEN ( PPPOE_TAG_TYPE_LEN + PPPOE_TAG_LENGTH_LEN )

/*PPPoE Tag�����󳤶ȣ�����PPPOE_TAG_HEAD_LENGTH*/
#define PPPOE_MAX_TAG_LEN ( PPPOE_MAX_ETHERNET_PAYLOAD \
        - PPPOE_MIN_ETHERNET_PAYLOAD )

/*PPPoE Tag��PAYLOAD(TAGVALUE)����󳤶�*/
#define PPPOE_MAX_TAG_PAYLOAD_LEN ( PPPOE_MAX_ETHERNET_PAYLOAD \
        - PPPOE_MIN_ETHERNET_PAYLOAD - PPPOE_TAG_HEAD_LEN )

/*PPPoE Version & Type, ĿǰΪ0x11*/
#define PPPOE_VERSION_1_TYPE_1  0x11

/* PPPoE �ĸ���codes���� */
#define PPPOE_CODE_SESS 0x00 /* PPPoEʱ��  PPPoE session */
#define PPPOE_CODE_PADI 0x09 /* PPPoE�������ֿ�ʼ  PPPoE Active Discovery Initiation */
#define PPPOE_CODE_PADO 0x07 /* PPPoE����������ͼ  PPPoE Active Discovery Offer */
#define PPPOE_CODE_PADR 0x19 /* PPPoE������������  PPPoE Active Discovery Request */
#define PPPOE_CODE_PADS 0x65 /* PPPoE��������ʱ��ȷ��  PPPoE Active Discovery Session-confirmation */
#define PPPOE_CODE_PADT 0xa7 /* PPPoE����������ֹ  PPPoE Active Discovery Terminate */

/* PPPoE �ĸ���tag type���� */
#define PPPOE_TAG_END_OF_LIST           0x0000  /* PPPoE_TAG������ */
#define PPPOE_TAG_SERVICE_NAME          0x0101  /* PPPoE_TAG������ */
#define PPPOE_TAG_AC_NAME               0x0102  /* PPPoE_TAGac�� */
#define PPPOE_TAG_HOST_UNIQ             0x0103  /* PPPoE_TAG������־ */
#define PPPOE_TAG_AC_COOKIE             0x0104  /* PPPoE_TAG*/
#define PPPOE_TAG_VENDOR_SPECIFIC       0x0105  /* PPPoE_TAGϸ��*/
#define PPPOE_TAG_RELAY_SESSION_ID      0x0110  /* PPPoE_TAG�ظ�ʱ��ID*/
#define PPPOE_TAG_SERVICE_NAME_ERROR    0x0201  /* PPPoE_TAG���������� */
#define PPPOE_TAG_AC_SYSTEM_ERROR       0x0202  /* PPPoE_TAGacϵͳ���� */
#define PPPOE_TAG_GENERIC_ERROR         0x0203  /* PPPoE_TAGһ����� */

/*PPPoE ����tag�ĳ���*/
#define PPPOE_LEN_SEVICENAME_TAG        0x0000
#define PPPOE_LEN_HOSTUNIQ_TAG          0x0002

/*PPPoE PADT ���ľ��ɵĳ���*/
#define PPPOE_PADT_PAYLOAD_LEN          0


/*PPPoE Client���õ�Dialer Bundle��Χ*/
#define PPPOE_DIALER_BUNDLE_LOW         1
#define PPPOE_DIALER_BUNDLE_HIGH        255


/*Host-Uniq tag Enable or Disable*/
#define PPPOE_CLIENT_SESSION_HOSTUINQ_ENABLE    1
#define PPPOE_CLIENT_SESSION_HOSTUINQ_DISABLE   0

/*PPPoE Client Idle-Timeout Enalbe or Disable*/
#define PPPOE_CLIENT_SESSION_IDLE_TIMEOUT_ENABLE    1
#define PPPOE_CLIENT_SESSION_IDLE_TIMEOUT_DISABLE   0

/*PPPoE Client Session Trigger mode Enalbe or Disable*/
#define PPPOE_CLIENT_SESSION_TRIGGER_ENABLE     1
#define PPPOE_CLIENT_SESSION_TRIGGER_DISABLE    0


/*PPPoE ClientӦ���Ƿ�ʹ��*/
#define PPPOE_CLIENT_ENABLE     1   /*ʹ��*/
#define PPPOE_CLIENT_DISABLE    0   /*��ֹ*/

#define PPPOE_SUCCESS           0   /*����ɹ�*/
#define PPPOE_FAILURE           1   /*����ʧ��*/

/*Queue Length�ĸ��ֳ���*/
#define PPPOE_CLIENT_QUEUE_LENGTH_MIN_LENGTH        1   /*��С*/
#define PPPOE_CLIENT_QUEUE_LENGTH_MAX_LENGTH        100 /*���*/
#define PPPOE_CLIENT_SESSION_DEFAULT_QUEUE_LENGTH   10  /*ȱʡ*/

#define PPPOE_CLIENT_IDLE_MIN_TIME  1       /*��СIdle��ʱ*/
#define PPPOE_CLIENT_IDLE_MAX_TIME  65535   /*���Idle��ʱ*/

#ifndef AF_PPPOE_CLIENT
#define AF_PPPOE_CLIENT             14      /*PPPoE Client����־*/
#endif

#define PPPOE_CLINET_BACKUP_DISC    1 
#define PPPOE_CLINET_BACKUP_CONN    2

/*PPPoE Client��ʹ�õ�һЩ�����*/
/* ���ַ�ָ��cp���һ��char��c��cpָ���1 */
#define PPPOE_GET_CHAR(c, cp) { \
    (c) = *( (UCHAR *)(cp) ); \
    (cp) += 1 ; \
}

/* ���ַ�cд���ַ�ָ��cp����cpָ���1 */
#define PPPOE_PUT_CHAR(c, cp) { \
    *( (UCHAR *)(cp) ) = (c) ; \
    (cp) += 1 ; \
}

/* ���ַ�ָ��cp���һ��ushortֵ��s��cpָ���2 */
#define PPPOE_GET_SHORT(s, cp) { \
    VOS_CopyVar((s), *((USHORT *)(cp))); \
    (cp) += 2 ; \
}

/* ��ushort����s��ֵд���ַ�ָ��cp����cpָ���2 */
#define PPPOE_PUT_SHORT(s, cp) { \
    VOS_CopyVar(*((USHORT*)(cp)), (s)) ; \
    (cp) += 2 ; \
}

/* ���ַ�ָ��cp���һ��ulongֵ��s��cpָ���4 */
#define PPPOE_GET_LONG(l, cp) { \
    VOS_CopyVar((l) , *((ULONG *)(cp))); \
    (cp) += 4 ; \
}

/* ��ulong����l��ֵд���ַ�ָ��cp����cpָ���4 */
#define PPPOE_PUT_LONG(l, cp) { \
    VOS_CopyVar(*((ULONG*)(cp)),(l)) ; \
    (cp) += 4 ; \
}

/*����ַULONG��ת����SOCKADDR_S����(���������˳��ͬ��ת��)*/
#define PPPOE_IpAddrUlongToSock(ulAddr,pstAddr) \
{ \
    pstAddr->sa_ucLen = sizeof(ULONG) + 2; \
    pstAddr->sa_ucFamily = AF_INET; \
    VOS_CopyVar(*(ULONG*)(pstAddr->sa_cData), ulAddr); \
}

/* ����/���debug��־�ĺ� */
#define POEC_CMD_SETDBGFLAG(ulTargetFlag, ulFlagToSet, bSetFlag) \
        ((ulTargetFlag) = ((bSetFlag)?((ulTargetFlag) | (ulFlagToSet)):((ulTargetFlag) & ~(ulFlagToSet))))


/*���ķ���*/
#define PPPOE_CLIENT_IN  0
#define PPPOE_CLIENT_OUT 1


/*Add DialNumber*/
#define NO_BUNDLENUMBER         0       /*Dialer BundleNumber��С�������1*/
#define MIN_BUNDLENUMBER        1       /*Dialer BundleNumber��С�������1*/
#define MAX_BUNDLENUMBER        255     /*Dialer BundleNumber���������255*/
/*End of Add*/

#ifndef VOS_TM_IS_TICKING
#define VOS_TM_IS_TICKING       0xA5
#endif
#ifndef VOS_TM_IS_PAUSED
#define VOS_TM_IS_PAUSED        0xAE
#endif


/*----------------------------------------------*
 * ���������
 *----------------------------------------------*/
#define PPPOE_CLIENT_ERR_NULL_IFNET           0x01000001  /*IFNETָ��ΪNULL*/
#define PPPOE_CLIENT_ERR_NOT_ENABLE_PPPOE     0x01000002  /*û��ʹ��PPPOE Clientģ��*/
#define PPPOE_CLIENT_ERR_SOURCE_MAC           0x01000003  /*Դphysical��ַ�Ƿ�*/
#define PPPOE_CLIENT_ERR_ETHER_TYPE           0x01000004  /*��̫��֡���ʹ���*/
#define PPPOE_CLIENT_ERR_PACKET_LEN           0x01000005  /*���ĳ��ȷǷ�*/
#define PPPOE_CLIENT_ERR_COMMAND              0x01000006  /*����Ŀ�����Ϣ������*/
#define PPPOE_CLIENT_ERR_NULL_POINTER         0x01000007  /*MBUF����ָ��ΪNULL*/


/*-----------------------------------------------------------*
 * ����SID��PPPoE Clientģ���ڲ�ʹ��(��ɾȥvos_id.h�еĶ���)
 *-----------------------------------------------------------*/
#define SID_COMP_PPPOEC_CLIENT_CB        ( 1 )
#define SID_COMP_PPPOEC_SESSION          ( 2 )

/*Debug information ID*/
/*ע��:
����޸Ĵ����룬��ͬ���޸�poec_proc.c�ļ��е�
char * Inf_PPPOE_Client_Dbg_Err[]������Ϣ*/
typedef enum tagPOEC_DEBUG_INFO_INDEX
{
    /****parsing tag error*****/
    PPPOE_CLIENT_PARSE_ERR_TAG_LEN_ERR_PADO,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADO1,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADO2,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_NOT_2_PADO,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_OUT_OF_RANGE_PADO,
    PPPOE_CLIENT_PARSE_ERR_TAG_LEN_ERR_PADS,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADS1,
    PPPOE_CLIENT_PARSE_ERR_NONZERO_END_OF_LIST_PADS2,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_NOT_2_PADS,
    PPPOE_CLIENT_PARSE_ERR_HOST_UNIQ_OUT_OF_RANGE_PADS,
    /****parsing tag error*****/

    PPPOE_CLIENT_PARSE_ERR_INFO_INDEX_MAX
}POEC_DEBUG_INFO_INDEX;


/* PPPOE Client��debug ���� */
#define PPPOE_CLIENT_DEBUG_DATA_FLAG    0x0001
#define PPPOE_CLIENT_DEBUG_ERROR_FLAG   0x0002
#define PPPOE_CLIENT_DEBUG_EVENT_FLAG   0x0004
#define PPPOE_CLIENT_DEBUG_PACKET_FLAG  0x0008
#define PPPOE_CLIENT_DEBUG_VERBOSE_FLAG 0x0010
#define PPPOE_CLIENT_DEBUG_GR_FLAG      0x0020
#define PPPOE_CLIENT_DEBUG_ALL_FLAG     0xffff /* ����0xffffffff�������е�CLI_USELESS_PARAֵ����ʹ��0xffff */


#ifndef IC_INFO_PARA_MAXLEN
#define IC_INFO_PARA_MAXLEN             1024
#endif

/*���Դ�ӡ���ĵ���󳤶�*/
#define PPPOE_CLIENT_PRINT_PACKET_LEN   128

#define POEC_SET_SESSION_INFO(pstSession, stSessionInfo)\
{\
    (stSessionInfo).ulEthIfIndex = ((TCPIP_HA_GetBoardType() == TCPIP_HA_AMB) ? \
                                    (pstSession)->pstEthIf->if_ulIfIndex : (ULONG)(UINTPTR)(pstSession)->pstEthIf);\
    (stSessionInfo).ulSessionId  = (pstSession)->usSessionId;\
    (VOID)TCPIP_Mem_Copy((stSessionInfo).szHisMacAddr, PPPOE_MAC_LEN, (pstSession)->szHisMacAddr, PPPOE_MAC_LEN);\
    (VOID)TCPIP_Mem_Copy((stSessionInfo).szOurMacAddr, PPPOE_MAC_LEN, (pstSession)->szOurMacAddr, PPPOE_MAC_LEN);\
}

#define POEC_NP_CREATE 0x1

typedef enum tagPOEC_PKT_TYPE_TO_SEND
{
    POEC_PKT_TYPE_PADI,             /* Ҫ����PADI���� */
    POEC_PKT_TYPE_PADR,             /* Ҫ����PADR���� */
    POEC_PKT_TYPE_PADT,             /* Ҫ����PADT���� */
}POEC_PKT_TYPE_TO_SEND_E;

#define PPPOE_CLIENT_RCV_PADO      1  /* �յ�PADO���� */
#define PPPOE_CLIENT_RCV_PADS      2  /* �յ�PADS���� */


#ifdef __cplusplus
}
#endif

#endif 

