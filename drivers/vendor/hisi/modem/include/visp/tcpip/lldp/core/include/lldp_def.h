
#ifndef _LLDP_DEF_H_
#define _LLDP_DEF_H_

#ifdef  __cplusplus
extern "C"{
#endif

/***********  �¼�����  ***********/
#define LLDP_EV_CNTRL   0x00010000
#define LLDP_EV_TIMER   0x00020000 
#define LLDP_EV_RCV     0x00040000
#define LLDP_EV_INER    0x00080000


/****** ������Ϣ����  ******/
#define LLDP_DISABLED_MSG       0
#define LLDP_RX_MSG             1
#define LLDP_TX_MSG             2
#define LLDP_RXTX_MSG           3
#define LLDP_LOCALCHANGE_MSG    4
#define LLDP_PORTENABLE_MSG     5
#define LLDP_PORTDISABLE_MSG    6
#define LLDP_PORTENABLE_AGE_MSG 7
#define LLDP_BEGIN_MSG           8
#define LLDP_DEL_PORT_MSG        9



/****** ��ʱ���������¼���Ϣ����**********/
#define LLDP_TXTTR_MSG              0
#define LLDP_TXSHUTDOWNWHILE_MSG    1
#define LLDP_TXTICK_MSG             2
#define LLDP_TXINFOAGE_MSG          3

/****** ״̬���ڲ��������¼���Ϣ����**********/
#define LLDP_TXNOW_MSG              0
#define LLDP_NEWNEIGHBOR_MSG        1

/****** �ײ��հ��������¼���Ϣ����******/
#define LLDP_RCVFRAME_MSG           0


#define VRP_TASK_LLDP_NAME  "LLDP"
#define VRP_TASK_LLDP_MODE 0


#define LLDP_TIMEER_PERIOD 1000
#define LLDP_QUEUE_LENGHTH    1024
#define LLDP_TIMER_QUEUE_LENGTH 1024

#define MID_LLDP    MID_COMP_LLDP

/*ȫ��������Ϣ�������*/
#define LLDP_GLOBALCFG_TXINTERVAL           1
#define LLDP_GLOBALCFG_TXHOLDMULTIPLIER     2
#define LLDP_GLOBALCFG_REINITDELAY          3
#define LLDP_GLOBALCFG_FASTTXPACKETNUM      4
#define LLDP_GLOBALCFG_MSGFASTTX            5

/*LLDP Ĭ��ȫ��������Ϣ,start*/
#define LLDP_DEFAULT_MSG_TX_INTERVAL      30     /*���͵�Ĭ��ʱ������Ĭ��30��*/
#define LLDP_MIN_MSG_TX_INTERVAL          1      /*���͵���Сʱ����*/
#define LLDP_MAX_MSG_TX_INTERVAL          32768  /*���͵����ʱ����*/

#define LLDP_DEFAULT_MSG_TX_HOLD          4      /*���͵�Ĭ��ʱ����ϵ����Ĭ��4*/
#define LLDP_MIN_MSG_TX_HOLD              1      /*���͵���Сʱ����ϵ��*/
#define LLDP_MAX_MSG_TX_HOLD              100     /*���͵����ʱ����ϵ��*/

#define LLDP_DEFAULT_REINIT_DELAY         2      /*���Ͷ����³�ʼ����Ĭ���ӳ�ʱ�䣬Ĭ��Ϊ2��*/
#define LLDP_MIN_REINIT_DELAY             1      /*���Ͷ����³�ʼ������С�ӳ�ʱ��*/
#define LLDP_MAX_REINIT_DELAY             10     /*���Ͷ����³�ʼ��������ӳ�ʱ��*/

#define LLDP_DEFAULT_FASTPKTNUM           4      /*FASTģʽĬ�ϴ��䱨�ĸ�����Ĭ��4��*/
#define LLDP_MIN_FASTPKTNUM               1      /*FASTģʽ��С���䱨�ĸ���*/
#define LLDP_MAX_FASTPKTNUM               8      /*FASTģʽ����䱨�ĸ���*/
/*LLDP Ĭ��ȫ��������Ϣ,end*/

#define LLDP_DEFAULT_TXCREDITMAX              5     /*txCreditMax*/
#define LLDP_DEFAULT_MSG_TX_FAST              1     /*���ٷ��ͼ����Ĭ��1��*/
#define LLDP_MIN_MSG_TX_FAST              1      /*FASTģʽ�·��͵���Сʱ����*/
#define LLDP_MAX_MSG_TX_FAST              8192   /*FASTģʽ�·��͵����ʱ����*/


#define ETHERTYPE_LLDP 0x88CC

#define ETHERTYPE_VLAN_LLDP 0X8100      /*vlan��ʽ*/
#define ETHERTYPE_ARP   0x0806           /*APR����*/
#define ETHERTYPE_IP    0x0800           /*IP����*/
#define ETHERTYPE_RARP   0x0835          /*ARPӦ��*/

#define LLDP_ETHII_ETHTYPE      1       /*Ethernet II ��ʽ����*/
#define LLDP_SNAP_ETHTYPE       2       /*SNAP��ʽ����*/
#define LLDP_VLAN_ETHII_ETHTYPE 3       /*��VLAN ��Ethernet II ��ʽ����*/
#define LLDP_VLAN_SNAP_ETHTYPE  4       /*��VLAN ��SNAP��ʽ����*/
#define LLDP_ERR_ETHTYPE        0xFF    /*�����ʽ*/


#define LLDP_ETH_ETHII_HEAD_LENGTH      14           /*Ethernet II ��ʽ��̫ͷ����*/
#define LLDP_ETH_ETHII_TYPE_OFFSET      12           /*Ethernet II ��ʽ����ֵƫ����*/
#define LLDP_ETH_SNAP_HEAD_LENGTH       22           /*SNAP��ʽ��̫ͷ����*/
#define LLDP_ETH_SNAP_TYPE_OFFSET       14           /*SNAP��ʽ����ֵƫ����*/
#define LLDP_ETH_VLAN_ETHII_HEAD_LENGTH 18           /*��VLAN ��Ethernet II ��ʽ��̫ͷ����*/
#define LLDP_ETH_VLAN_ETHII_TYPE_OFFSET 16           /*��VLAN ��Ethernet II ��ʽ����ֵƫ����*/
#define LLDP_ETH_VLAN_SNAP_HEAD_LENGTH  26           /*��VLAN ��SNAP��ʽ��̫ͷ����*/
#define LLDP_ETH_VLAN_SNAP_TYPE_OFFSET  18           /*��VLAN ��SNAP��ʽ����ֵƫ����*/

#define LLDP_PROTOCOLVER     0x88CC
#define LLDP_TLV_LENGTH_LEN  9
#define LLDP_TLV_HEAD_LEN    2 
#define LLDP_TLV_MAXLEN      512
#define LLDP_PKT_LLDPU_LENGTH_MIN  14 /*LLDP���ĵ�LLDPU(TLV����)��С����Ϊ14*/

/*�����ַЭ����*/
#define LLDP_NETWORKADDRESS_IPV4_FAMILY 1
#define LLDP_NETWORKADDRESS_IPV6_FAMILY 2
#define LLDP_NETWORKADDRESS_802_FAMILY  6


/*ÿ��LLDPDU����Я����TLV���£���25�ֽ�:
Chassis ID TLV(4B),Port ID TLV(4B),Time To Live TLV(4B),Management Address TLV(11B),END OF TLV(2B)*/
#define MIN_LLDPDU_LEN      25
#define MAX_LLDPDU_LEN      1500

/*TLV��type��length�ֶεĳ���,��λ:����*/
#define LLDP_TLV_TYPE_LEN   7

#define LLDP_ETH_SNAP_LENGTH 8


/*LLDP chassis id TLV/port id TLV information length scope*/
#define LLDP_BASSIC_TLVINFO_LENMAX 256
#define LLDP_BASSIC_TLVINFO_LENMIN 2

/*LLDP TTL TLV information length scope*/
#define LLDP_TTL_TLVINFO_LEN 2

/*LLDP management address TLV information length scope*/
#define LLDP_MANADDR_TLVINFO_LENMAX 167
#define LLDP_MANADDR_TLVINFO_LENMIN 9

/*LLDP system name TLV information length scope*/
#define LLDP_SYSNAME_TLVINFO_LENMAX 255
#define LLDP_SYSNAME_TLVINFO_LENMIN 0

/*LLDP system description TLV information length scope*/
#define LLDP_SYSDESC_TLVINFO_LENMAX 255
#define LLDP_SYSDESC_TLVINFO_LENMIN 0

/*LLDP system capabilities TLV information length scope*/
#define LLDP_SYSCAP_TLVINFO_LEN 4   /*Э���й��ڴ˴���������������*/

/*LLDP port description TLV information length scope*/
#define LLDP_PORTDESC_TLVINFO_LENMAX 255
#define LLDP_PORTDESC_TLVINFO_LENMIN 0

/*LLDP 8023TLV TLV length scope*/
#define LLDP_MAX_FRAME_SIZE_TLVINFO_LEN (6-3)
#define LLDP_LINK_AGG_TLVINFO_LEN (9-3)
#define LLDP_PHY_CFG_STATUS_TLVINFO_LEN (9-3)
#define LLDP_POWER_VIA_MDI_TLVINFO_LEN (7-3)


#define LLDP_IPV4_SUBTYPE_LEN 4
#define LLDP_IPV6_SUBTYPE_LEN 16
#define LLDP_MAC_SUBTYPE_LEN  6

/*Management Address subtype*/
#define LLDP_OTHER_SUBTYPE 0
#define LLDP_IPV4_SUBTYPE 1
#define LLDP_IPV6_SUBTYPE 2
#define LLDP_NSAP_SUBTYPE 3
#define LLDP_HDLC_SUBTYPE 4
#define LLDP_BBNL1822_SUBTYPE 5
#define LLDP_MAC_SUBTYPE  6
#define LLDP_E163_SUBTYPE 7
#define LLDP_E164_SUBTYPE 8
#define LLDP_F69_SUBTYPE  9
#define LLDP_X121_SUBTYPE 10
#define LLDP_IPX_SUBTYPE  11
#define LLDP_APPLETALK_SUBTYPE  12
#define LLDP_DECNETIV_SUBTYPE 13
#define LLDP_BANYANVINES_SUBTYPE  14
#define LLDP_E164WITHNSAP_SUBTYPE 15
#define LLDP_DNS_SUBTYPE 16
#define LLDP_DISTINGUISHEDNAME_SUBTYPE 17
#define LLDP_ASNUMBER_SUBTYPE 18
#define LLDP_XTPOVERIPV4 19
#define LLDP_XTPOVERIPV6 20
#define LLDP_RESERVED_SUBTYPE 21

#define LLDP_SYSTEM_CAPABILITIES_BRIDGE                 0x04
#define LLDP_SYSTEM_CAPABILITIES_ROUTE                  0x10

/*LLDP TLV type=127 information, start*/
#define LLDP_ORGSPEC_TLVINFO_SUBTYPE1   3  /*TLV information string�б�ʾ��TLVΪ802.1��802.3�ֶεĳ��ȣ���λ�ֽ�*/
#define LLDP_ORGSPEC_TLVINFO_SUBTYPE2   1  /*TLV information string�б�ʾЭ���������ֶεĳ��ȣ���λ�ֽ�*/ 

#define LLDP_PROTOCOLVER1_SUB1   0x00    /*TLV type=127 802.1Э�����͵�1���ֽڵ�ֵ*/
#define LLDP_PROTOCOLVER1_SUB2   0x80    /*TLV type=127 802.1Э�����͵�2���ֽڵ�ֵ*/
#define LLDP_PROTOCOLVER1_SUB3   0xC2    /*TLV type=127 802.1Э�����͵�3���ֽڵ�ֵ*/

#define LLDP_PROTOCOLVER2_SUB1   0x00    /*TLV type=127 802.3Э�����͵�1���ֽڵ�ֵ*/
#define LLDP_PROTOCOLVER2_SUB2   0x12    /*TLV type=127 802.3Э�����͵�2���ֽڵ�ֵ*/
#define LLDP_PROTOCOLVER2_SUB3   0x0F    /*TLV type=127 802.3Э�����͵�3���ֽڵ�ֵ*/

#define LLDP_TLV_SUBTYPE1   1   /*802.1Э���е�TLV*/
#define LLDP_TLV_SUBTYPE2   2   /*802.3Э���е�TLV*/

#define LLDP_TLV_SUBTYPE1_PVID           1  /*802.1Э����Port VLAN ID TLV SubType*/
#define LLDP_TLV_SUBTYPE1_PPVID          2  /*802.1Э����Port And Protocol VLAN ID TLV SubType*/
#define LLDP_TLV_SUBTYPE1_VLAN_NAME      3  /*802.1Э����VLAN NAME TLV SubType*/
#define LLDP_TLV_SUBTYPE1_MANAGE_VID     6 /*802.1Э����Management VID TLV SubType*/
#define LLDP_TLV_SUBTYPE1_LINK_AGGR      7 /*802.1Э����Link Aggregation TLV SubType*/

#define LLDP_TLV_SUBTYPE2_MAC_PHY_CFG     1  /*802.3Э����MAC/PHY Configuration/Status TLV SubType*/
#define LLDP_TLV_SUBTYPE2_POWER_VIA_MDI   2  /*802.3Э����Power Via MDI TLV SubType*/
#define LLDP_TLV_SUBTYPE2_LINK_AGGR        3 /*802.3Э����Link Aggregation TLV SubType*/
#define LLDP_TLV_SUBTYPE2_MTU              4 /*802.3Э����Maximum Frame Size TLV SubType*/

#define LLDP_PVID_TLVINFO_LEN       2  /*Port VLAN ID TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_PPVID_TLVINFO_LEN      3  /*PPVID TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_LINKAGGR_TLVINFO_LEN   5  /*LinkAggregation TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_MACPHYCFG_TLVINFO_LEN  5  /*MAC/PHY Configuration/Status TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_POWERVIAMDI_TLVINFO_LEN 3 /*PowerViaMDI TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_MTU_TLVINFO_LEN         2  /*Maximum Frame Size TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_MANAGE_VID_TLVINFO_LEN  2  /*Management VID TLV��ȥTLVͷ����802.1��802.3Э�����ͣ���Э�������ͺ�ĳ���*/
#define LLDP_VLANNAME_VLANID__LEN    2  /*Vlan name TLV ��VLAN ID�ֶγ���*/
#define LLDP_VLANNAME_LENGTH__LEN    1  /*Vlan name TLV ��VLAN name length�ֶγ���*/

#define LLDP_TLV_STATUS_ENABLE       0x03  /*supported and enabled*/
#define LLDP_TLV_STATUS_INVALIDABLE  0x02  /*unsupported but enabled*/
#define LLDP_TLV_STATUS_DISABLE      0x01  /*supported but disabled*/
#define LLDP_TLV_STATUS_UNSUPPORTED  0x00  /*unsupported and disabled*/
#define LLDP_TLV_4BIT_ENABLE       0x0F  /*1���ֽ��е�λ4��bitλ��Ϊ1ʱ��ֵ*/

#define LLDP_TLV_BIT_L1    0x01    /*��ȡ1���ֽ��е����1bit��ֵ*/
#define LLDP_TLV_BIT_H7     0xfe    /*��ȡ1���ֽ��е�ǰ7��bit��ֵ*/

#define LLDP_TLV_PPVID_MIN_VALUE    1      /*Э��涨��PPVID��Сֵ*/
#define LLDP_TLV_PPVID_MAX_VALUE    4094  /*Э��涨��PPVID���ֵ*/

/*3�C8 bit reserved for future standardization (set to zero)
  If the support bit (bit 1) of the flag field indicates that the port is not capable of supporting port and
  protocol VLANs but the enabled bit (bit 2) indicates that the port is enabled with one or more port
  and protocol VLANs, the Port And Protocol VLAN ID TLV is interpreted as containing an error and
  will be discarded.*/
#define LLDP_TLV_PPVID_FLAG_INVALID(ucFlags)   \
   (((ucFlags)&0xFC) > 0 || ((ucFlags)&0x03) == 0x2) 


/*LLDP TLV type=127 information, end*/

#define LLDP_AGENT_MAX_REMOTE_TABLE     4    /*һ��agent���ھӱ�����ھ�����*/


#define LLDP_INTERFACE_AND_NEIGBOR_DEFAULT 64


#define LLDP_IF_NAME_LEN  48

#define LLDP_REMOTE_DELTE   0       /* ɾ���ھ� */
#define LLDP_REMOTE_UPDATE  1       /* �����ھ� */
#define LLDP_REMOTE_AGE     2       /*�ھ��ϻ�*/

#define LLDP_DEBUG_TYPES 8

#define LLDP_LEN_4        4
#define LLDP_LEN_8        8
#define LLDP_LEN_16       16
#define LLDP_LEN_32       32
#define LLDP_LEN_64       64
#define LLDP_LEN_128      128
#define LLDP_LEN_192      192
#define LLDP_LEN_256      256
#define LLDP_LEN_512      512
#define LLDP_LEN_1024     1024
#define LLDP_LEN_2048     2048
#define LLDP_LEN_4096     4096

#define LLDP_LEN_200      200

#define LLDP_INIT_POS 0xffffffff

/*Remote��ulTlvValidFlag��BITλ, Я���Ŀ�ѡTLV��Ч��־��bit��ʶ��,START*/
#define LLDP_TLV_BIT_SYS_NAME         0x0001  /*LLDP_REM_INFO_S��ulTlvValidFlag��System Name TLV BITλ*/
#define LLDP_TLV_BIT_SYS_DESC         0x0002  /*System Description TLV*/
#define LLDP_TLV_BIT_SYS_CAPABILITY   0x0004  /*System Capability TLV*/
#define LLDP_TLV_BIT_PORT_DESC        0x0008  /*Port Description TLV*/
#define LLDP_TLV_BIT_MAN_ADDR         0x0010  /*Management Address TLV*/
#define LLDP_TLV_BIT_MAC_PHY_CFG      0x0020  /*MAC/PHY Configuration/Status TLV*/
#define LLDP_TLV_BIT_PORT_VLAN_ID     0x0040  /*Port Vlan Id TLV*/
#define LLDP_TLV_BIT_MAX_FRAME_SIZE   0x0080  /*Max Frame Size TLV*/
#define LLDP_TLV_BIT_LINK_AGGREGATION 0x0100  /*Link Aggregation TLV*/
#define LLDP_TLV_BIT_POWER_VIA_MDI    0x0200  /*Power Via Mdi TLV*/
#define LLDP_TLV_BIT_PPVID            0x0400  /*Port and Protocol Vlan ID TLV*/

#define LLDP_TLV_BIT_VLAN_NAME        0x0800  /*VLAN NAME TLV*/
#define LLDP_TLV_BIT_MANAGE_VID       0x1000  /*Management VID TLV*/


#define LLDP_TLV_BIT_CHASSIS_ID       0x00010000
#define LLDP_TLV_BIT_PORT_ID          0x00020000
#define LLDP_TLV_BIT_TIME_TO_LIVE     0x00040000
#define LLDP_TLV_BIT_END_OF_LLDPDU    0x00080000

/*Remote��ulTlvValidFlag��BITλ, Я���Ŀ�ѡTLV��Ч��־��bit��ʶ��,END*/

/*Added by guo00178934, LLDP���Ľ���������, ��ǰ��Ч��TLV�����ʶ0xFFFF, ֧��16��TLV, 
2011/10/29   ���ⵥ��:20110927 */

/*�����TLV�����±��Ķ�������ǰ3������TLV�����ظ���ȱ��End TLV��*/
#define LLDP_TLV_ERR_DROP_PKT               0x00100000 

/*TLV��Ϣ����ֻ����TLV�������ᶪ���������δ�ж�TLV���ͣ��޷�ͳ����������֪��TLV�е������
  ��802.1��802.3��չTLV��TLV����С��4���ֽ�*/
#define LLDP_TLV_ERR_OTHER               0x00200000 

/*��ʶ���TLV��������TLV���������������TLV*/
#define LLDP_TLV_ERR_UNKNOWN             0x00400000

/*�����TLV��������Э��Ĺ涨����������ʶ���TLV*/
#define LLDP_TLV_ERR_ALL                0x003FFFFF

#define LLDP_PACKET_ERR_OTHER            0x00800000

/*�����ĵ�ͳ��*/
#define LLDP_PACKET_ERR_ALL    (LLDP_TLV_ERR_DROP_PKT         \
                                | LLDP_PACKET_ERR_OTHER       \
                                | LLDP_TLV_BIT_CHASSIS_ID     \
                                | LLDP_TLV_BIT_PORT_ID        \
                                | LLDP_TLV_BIT_TIME_TO_LIVE   \
                                | LLDP_TLV_BIT_END_OF_LLDPDU)

#define LLDP_PACKET_DROP                 0x08000000


#define LLDP_AGENT_REM_AGE              0x20000000
#define LLDP_PACKET_SEND                0x40000000
#define LLDP_PACKET_RECEIVE             0x80000000
/* End of Added by guo00178934, 2011/10/29   ���ⵥ��:20110927 */

/*******************************************************************************/
typedef enum enumLLDP_8023_TLV_SUBTYPE
{
    LLDP_8023_TLV_SUBTYPE_NULL = 0,      /*����*/
    LLDP_8023_TLV_SUBTYPE_PHY_CFG_STATUS,  /*MAC/PHY Configuration/Status TLV*/
    LLDP_8023_TLV_SUBTYPE_POWER_VIA_MDI,   /*Power Via MDI TLV*/
    LLDP_8023_TLV_SUBTYPE_LINK_AGG,         /*Link Aggregation TLV*/
    LLDP_8023_TLV_SUBTYPE_MAX_FRAME_SIZE,  /*Maximum Frame Size TLV*/
    LLDP_8023_TLV_SUBTYPE_MAX
}LLDP_8023_TLV_SUBTYPE_E;

typedef enum enumLLDP_TLV_TYPE
{
    LLDP_TLV_TYPE_END_OF_LLDPDU = 0,      /*����*/
    LLDP_TLV_TYPE_CHASSIS_ID ,                    /*�豸(��)��ʶ*/
    LLDP_TLV_TYPE_PORT_ID,                         /*�˿ڱ�ʶ*/
    LLDP_TLV_TYPE_TIME_TO_LIVE,               /*��Чʱ��*/
    LLDP_TLV_TYPE_PORT_DESCRIPTION,       /*�˿�����*/
    LLDP_TLV_TYPE_SYSTEM_NAME,                /*ϵͳ����*/
    LLDP_TLV_TYPE_SYSTEM_DESCRIPTION,     /*ϵͳ����*/
    LLDP_TLV_TYPE_SYSTEM_CAPABILITIES,    /*ϵͳ����*/
    LLDP_TLV_TYPE_MANAGEMENT_ADDRESS,  /*�����ַ*/
    LLDP_TLV_TYPE_ORGANIZATIONALLY_SPECIFIC = 127, /*��֯�����*/
    LLDP_TLV_TYPE_SHUTDOWN_TIME_TO_LIVE = 0xffff /*ShutDown TTL TLV*/
}LLDP_TLV_TYPE_E;


/***************ChassisID Subtype**************/
typedef enum enumLLDP_CHASSISID_SUBTYPE
{
    LLDP_CHASSISID_RESERVED = 0,
    LLDP_CHASSISID_CHASSIS_COMPONENT,
    LLDP_CHASSISID_INTERFACE_ALIAS,
    LLDP_CHASSISID_PORT_COMPONENT,    
    LLDP_CHASSISID_MAC_ADDRESS,
    LLDP_CHASSISID_NETWORK_ADDRESS,
    LLDP_CHASSISID_INTERFACE_NAME,
    LLDP_CHASSISID_LOCALLY_ASSIGNED,
}LLDP_CHASSISID_SUBTYPE_E;

typedef enum enumLLDP_PORTID_SUBTYPE
{
    LLDP_PORTID_RESERVED = 0,
    LLDP_PORTID_INTERFACE_ALIAS,
    LLDP_PORTID_PORT_COMPONENT,    
    LLDP_PORTID_MAC_ADDRESS,
    LLDP_PORTID_NETWORK_ADDRESS,
    LLDP_PORTID_INTERFACE_NAME,
    LLDP_PORTID_AGENT_CIRCUITID,
    LLDP_PORTID_LOCALLY_ASSIGNED,
}LLDP_PORTID_SUBTYPE_E;

/***********ManAddr  Interface numbering subtype******************/
typedef enum enumLLDP_MANADDR_IFNUM_SUBTYPE
{
    LLDP_MANADDR_IFNUM_UNKNOWN = 1,
    LLDP_MANADDR_IFNUM_IFINDEX ,
    LLDP_MANADDR_IFNUM_SYSPORTNUM,
}LLDP_MANADDR_IFNUM_SUBTYPE_E;


/****************** AdminStatus ״̬ **********************************/
typedef enum enumLLDP_ADMIN_STATUS
{
    LLDP_ADMIN_STATUS_DISABLED = 0,       /*�˿ڽ���*/        
    LLDP_ADMIN_STATUS_TX,                   /*������, Ŀǰ��֧��*/
    LLDP_ADMIN_STATUS_RX,                   /*������, Ŀǰ��֧��*/
    LLDP_ADMIN_STATUS_TX_RX,             /*ͬʱ֧�ַ��ͺͽ���*/
}LLDP_ADMIN_STATUS_E;

/* ������������ȡ��UCHAR��ֵ */
#define LLDP_GETCHAR(c, cp) \
{ \
    (c) = *(cp); \
    (cp) ++ ; \
}


#define LLDP_CopyConstByPointer4(pA, B) \
{ \
    unsigned long _vos_long_x_; \
     \
    _vos_long_x_ = (ULONG)(B); \
    (VOID)TCPIP_Mem_Copy( (VOID*)(pA), 4, (VOID*)(&_vos_long_x_), 4); \
}

#define LLDP_CopyConstByPointer2(pA, B) \
{ \
    unsigned short _vos_short_x_; \
     \
    _vos_short_x_ = (USHORT)(B); \
    (VOID)TCPIP_Mem_Copy( (VOID*)(pA), 2, (VOID*)(&_vos_short_x_), 2); \
}


/* ��UCHAR��ֵ�������������� */
#define LLDP_PUTCHAR(c, cp) \
{ \
    *(cp) = (UCHAR) (c); \
    (cp) ++ ; \
}

/* ��USHORT��ֵ���������ֽ�˳��������������� */
#define LLDP_PUTSHORT(s, cp) \
{ \
    LLDP_CopyConstByPointer2( (cp), (USHORT)VOS_HTONS(s) ); \
    (cp) +=2 ; \
}

/* ��ULONG��ֵ���������ֽ�˳��������������� */
#define LLDP_PUTLONG(l, cp) \
{ \
    LLDP_CopyConstByPointer4( (cp), (ULONG)VOS_HTONL(l) ); \
    (cp) += 4 ; \
}

/* ������������ȡ��ULONG��ֵ��ת���ɱ����ֽ�˳�� */
#define LLDP_GETLONG(l, cp) \
{ \
    (l) = (ULONG) ( ((ULONG)((UCHAR *)(cp))[0] << 24) |     \
                    ((ULONG)((UCHAR *)(cp))[1] << 16) |     \
                    ((ULONG)((UCHAR *)(cp))[2] << 8) |      \
                    ((ULONG)((UCHAR *)(cp))[3]) );\
    (cp) += 4 ; \
}

/* ������������ȡ��USHORT��ֵ��ת���ɱ����ֽ�˳�� */
#define LLDP_GETSHORT(s, cp) \
{ \
    (s) = (USHORT)((((UCHAR *)(cp))[0] << 8) | (((UCHAR *)(cp))[1])); \
    (cp) += 2 ; \
}



/*
#define LLDP_CHASSISID_INFO_EQUAL(pstChassisidInfoA, pstChassisidInfoB)   \
  ((pstChassisidInfoA)->ulChassisIdSubtype == (pstChassisidInfoB)->ulChassisIdSubtype   \
  && (!VOS_strcmp((pstChassisidInfoA)->szChassisId, (pstChassisidInfoB)->szChassisId)))  
*/
#define LLDP_PORT_DESC_INFO_EQUAL(pstPortDescInfoA, pstPortDescInfoB)   \
  (!VOS_strcmp((pstPortDescInfoA)->szPortDesc, (pstPortDescInfoB)->szPortDesc))
#define LLDP_LINK_AGG_INFO_EQUAL(pstLinkAggInfoA, pstLinkAggInfoB)   \
  ((pstLinkAggInfoA)->ucLinkAggCapStatus == (pstLinkAggInfoB)->ucLinkAggCapStatus   \
  && (pstLinkAggInfoA)->ulLinkAggPortID == (pstLinkAggInfoB)->ulLinkAggPortID) 

#define LLDP_PPVID_INFO_EQUAL(pstPpvidInfoA, pstPpvidInfoB)   \
  ((pstPpvidInfoA)->usPpvid == (pstPpvidInfoB)->usPpvid   \
  && (pstPpvidInfoA)->ucFlags == (pstPpvidInfoB)->ucFlags)  

#define LLDP_SYS_NAME_INFO_EQUAL(pstSysNameInfoA, pstSysNameInfoB)   \
  (!VOS_strcmp((pstSysNameInfoA)->szSysName, (pstSysNameInfoB)->szSysName))

#define LLDP_SYS_DESC_INFO_EQUAL(pstSysDescInfoA, pstSysDescInfoB)   \
  (!VOS_strcmp((pstSysDescInfoA)->szSysDesc, (pstSysDescInfoB)->szSysDesc))

#define LLDP_SYS_CAP_INFO_EQUAL(pstSysCapInfoA, pstSysCapInfoB)   \
  ((pstSysCapInfoA)->usSysCapSupported == (pstSysCapInfoB)->usSysCapSupported   \
  && (pstSysCapInfoA)->usSysCapEnabled == (pstSysCapInfoB)->usSysCapEnabled)  
  
#define LLDP_MANAGEMENT_VID_INFO_EQUAL(pstManageVidInfoA, pstManageVidInfoB)   \
  ((pstManageVidInfoA)->usManagementVid == (pstManageVidInfoB)->usManagementVid)
  
#define LLDP_PORTID_INFO_EQUAL(pstPortIdInfoA, pstPortIdInfoB)   \
  ((pstPortIdInfoA)->ucPortIdSubtype == (pstPortIdInfoB)->ucPortIdSubtype   \
  && (!VOS_strcmp((pstPortIdInfoA)->szPortId, (pstPortIdInfoB)->szPortId)))  
  
#define LLDP_GLOBAL_CFG_EQUAL(pstGlobalCfgInfoA, pstGlobalCfgInfoB)   \
  ((pstGlobalCfgInfoA)->ulTxInterval == (pstGlobalCfgInfoB)->ulTxInterval   \
  && (pstGlobalCfgInfoA)->ulTxHoldMultiplier == (pstGlobalCfgInfoB)->ulTxHoldMultiplier  \
  && (pstGlobalCfgInfoA)->ulReinitDelay == (pstGlobalCfgInfoB)->ulReinitDelay  \
  && (pstGlobalCfgInfoA)->ulFastTxPktNum == (pstGlobalCfgInfoB)->ulFastTxPktNum)   

#define LLDP_TTL_EQUAL(pstGlobalCfgInfoA, pstGlobalCfgInfoB)   \
  ((pstGlobalCfgInfoA)->ulTxInterval == (pstGlobalCfgInfoB)->ulTxInterval   \
  && (pstGlobalCfgInfoA)->ulTxHoldMultiplier == (pstGlobalCfgInfoB)->ulTxHoldMultiplier) 

#define LLDP_MANAGEMENT_INFO_EQUAL(pstManagementInfoA, pstManagementInfoB)   \
  ((pstManagementInfoA)->ulManAddrSubtype == (pstManagementInfoB)->ulManAddrSubtype   \
  && (LLDP_ManageAddressCmp((pstManagementInfoA)->szManAddr, (pstManagementInfoB)->szManAddr,(pstManagementInfoA)->ulManAddrSubtype))  \
  && (pstManagementInfoA)->ulManAddrIfSubtype == (pstManagementInfoB)->ulManAddrIfSubtype \
  && (pstManagementInfoA)->ulManAddrIfId == (pstManagementInfoB)->ulManAddrIfId) 

#define LLDP_PVID_INFO_EQUAL(pstPvidInfoA, pstPvidInfoB)   \
    ((pstPvidInfoA)->usPvid == (pstPvidInfoB)->usPvid) 
    
#define LLDP_MAX_FRAME_SIZE_INFO_EQUAL(pstMaxFrameSizeInfoA, pstMaxFrameSizeInfoB)   \
      ((pstMaxFrameSizeInfoA)->usMaxFrameSize == (pstMaxFrameSizeInfoB)->usMaxFrameSize)

#define LLDP_POWER_VIA_MDI_INFO_EQUAL(pstPowerViaMdiInfoA, pstPowerViaMdiInfoB)   \
      ((pstPowerViaMdiInfoA)->ucMdiPowerSupport == (pstPowerViaMdiInfoB)->ucMdiPowerSupport   \
      && (pstPowerViaMdiInfoA)->ucPsePowerPair == (pstPowerViaMdiInfoB)->ucPsePowerPair  \
      && (pstPowerViaMdiInfoA)->ucPowerClass == (pstPowerViaMdiInfoB)->ucPowerClass) 

#define LLDP_MAC_PHY_CONF_INFO_EQUAL(pstMacPhyCfgInfoA, pstMacPhyCfgInfoB)   \
    ((pstMacPhyCfgInfoA)->ucLinkAutoNegoCapStatus == (pstMacPhyCfgInfoB)->ucLinkAutoNegoCapStatus   \
    && (pstMacPhyCfgInfoA)->usLinkPmdAutoNegoCap == (pstMacPhyCfgInfoB)->usLinkPmdAutoNegoCap  \
    && (pstMacPhyCfgInfoA)->usLinkOperMauType == (pstMacPhyCfgInfoB)->usLinkOperMauType)   


#define LLDP_CFG_SYS_INFO_EQUAL(pstSysInfoA, pstCfgSysInfoB)   \
  (LLDP_ChassisidCmp(&((pstSysInfoA)->stChassisId), &((pstCfgSysInfoB)->stChassisId))   \
  && LLDP_SYS_NAME_INFO_EQUAL(&((pstSysInfoA)->stSysName), &((pstCfgSysInfoB)->stSysName))  \
  && LLDP_SYS_DESC_INFO_EQUAL(&((pstSysInfoA)->stSysDesc), &((pstCfgSysInfoB)->stSysDesc))  \
  && LLDP_MANAGEMENT_INFO_EQUAL(&((pstSysInfoA)->stManagement), &((pstCfgSysInfoB)->stManagement))) 

/*
#define LLDP_SYS_INFO_EQUAL(pstSysInfoA, pstSysInfoB)    \
  (LLDP_CHASSISID_INFO_EQUAL(&((pstSysInfoA)->stChassisId), &((pstSysInfoB)->stChassisId))   \
  && LLDP_SYS_NAME_INFO_EQUAL(&((pstSysInfoA)->stSysName), &((pstSysInfoB)->stSysName))  \
  && LLDP_SYS_DESC_INFO_EQUAL(&((pstSysInfoA)->stSysDesc), &((pstSysInfoB)->stSysDesc))  \
  && LLDP_MANAGEMENT_INFO_EQUAL(&((pstSysInfoA)->stManagement), &((pstSysInfoB)->stManagement)) \
  && LLDP_SYS_CAP_INFO_EQUAL(&((pstSysInfoA)->stSysCapability), &((pstSysInfoB)->stSysCapability)))   
 
#define LLDP_LOCAL_SYS_INFO_EQUAL(pstLocalSysInfoA, pstLocalSysInfoB)   \
    (LLDP_ChassisidCmp(&((pstLocalSysInfoA)->stChassisId), &((pstLocalSysInfoB)->stChassisId))   \
    && LLDP_SYS_NAME_INFO_EQUAL(&((pstLocalSysInfoA)->stLocSysName), &((pstLocalSysInfoB)->stLocSysName))  \
    && LLDP_SYS_DESC_INFO_EQUAL(&((pstLocalSysInfoA)->stLocSysDesc), &((pstLocalSysInfoB)->stLocSysDesc))  \
    && LLDP_SYS_CAP_INFO_EQUAL(&((pstLocalSysInfoA)->stSysCapability), &((pstLocalSysInfoB)->stSysCapability))   \
    && LLDP_MANAGEMENT_INFO_EQUAL(&((pstLocalSysInfoA)->stManagement), &((pstLocalSysInfoB)->stManagement))   \
    && LLDP_GLOBAL_CFG_EQUAL(&((pstLocalSysInfoA)->stConfigutation), &((pstLocalSysInfoB)->stConfigutation)))  
*/ 
#define LLDP_MAC_INDEX_CFG(ulMacIndex) ((ulMacIndex) - 1)
#define LLDP_MAC_INDEX_GET(ulMacIndex) ((ulMacIndex) + 1)

#define LLDP_DEST_ADDR_GROUP_VALID(ulDestAddrGroup)  \
  ((ulDestAddrGroup) == LLDP_NEAREST_BRIDGE ||          \
  (ulDestAddrGroup) == LLDP_NEAREST_NON_TPMR_BRIDGE ||  \
  (ulDestAddrGroup) == LLDP_NEAREST_CUSTOMER_BRIDGE)

#define LLDP_CHECK_FIRST_3BASIC_TLV(usTLVType)\
    ((LLDP_TLV_TYPE_CHASSIS_ID == usTLVType)\
        || (LLDP_TLV_TYPE_PORT_ID == usTLVType)\
        || (LLDP_TLV_TYPE_TIME_TO_LIVE == usTLVType))

#ifdef  __cplusplus
}
#endif

#endif

