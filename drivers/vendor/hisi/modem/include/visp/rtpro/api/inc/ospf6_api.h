/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_api.h
*
*  Project Code: node
*   Module Name:   
*  Date Created: 2009-07-13
*        Author: wangbin (62223)
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-07-13   wangbin (62223)         Create
*
*******************************************************************************/
#ifndef _OSPF6_API_H_
#define _OSPF6_API_H_
    
#ifdef __cplusplus
        extern "C"{
#endif /* __cplusplus */

/*MACRO<OSPF6_Define>*/
#define OSPF6_MAX_PROCESSES                     32         /*��������*/
#define OSPF6_MAX_AREA                          50         /*���������*/

#define OSPF6_MAX_IF_NAME_LENGTH                47         /*�ӿ�����󳤶�*/
#define OSPF6_MAX_VRFNAME_LENGTH                31         /*VRF����󳤶�*/
#define OSPF6_ENCRYPT_DATA_LENGTH               255        /*���enc ���ݳ���*/

#define OSPF6_DEFAULT_CALC_DELAY                5000       /*SPF��ʱ����ʱʱ��ȱʡֵ*/
#define OSPF6_DEFAULT_CALC_PAUSE                10000      /*SPF��ʱ���ж�ʱ��ȱʡֵ*/

#define OSPF6_MIN_EQCOST_PATH                   1          /*���ƽ��·�ɸ�������Сֵ*/
#define OSPF6_MAX_EQCOST_PATH                   32         /*���ƽ��·�ɸ��������ֵ*/
#define OSPF6_DEFAULT_EQCOST_PATH               5          /*���ƽ��·��ȱʡֵ*/

#define OSPF6_MAX_SPF_TIME                      0x7fffffff /*SPF��ʱ�����������*/

#define OSPF6_MAX_INTF_PRIORITY                 255        /*Router�ӿ����ȼ����ֵ*/
#define OSPF6_DEFAULT_INTF_PRIORITY             1          /*Router�ӿ����ȼ�Ĭ��ֵ*/

#define OSPF6_ROUTER_LSA                        (0x2001)   /*·�ɾۺ�ʱ��LSDB����ΪROUTE_LSA*/
#define OSPF6_NETWORK_LSA                       (0x2002)   /*·�ɾۺ�ʱ��LSDB����ΪNETWORK_LSA*/
#define OSPF6_INTER_AREA_PRFX_LSA               (0x2003)   /*·�ɾۺ�ʱ��LSDB����ΪINTER_AREA_PRFX_LSA */
#define OSPF6_INTER_AREA_RTR_LSA                (0x2004)   /*·�ɾۺ�ʱ��LSDB����ΪINTER_AREA_RTR_LSA*/
#define OSPF6_AS_EXTERNAL_LSA                   (0x4005)   /*·�ɾۺ�ʱ��LSDB����ΪAS_EXTERNAL_LSA*/
#define OSPF6_NSSA_EXT_LSA                      (0x2007)   /*·�ɾۺ�ʱ��LSDB����ΪNSSA_EXT_LSA*/
#define OSPF6_LINK_LSA                          (0x0008)   /*·�ɾۺ�ʱ��LSDB����ΪLINK_LSA*/
#define OSPF6_INTRA_AREA_PRFX_LSA               (0x2009)   /*·�ɾۺ�ʱ��LSDB����ΪINTRA_AREA_PRFX_LSA*/
#define OSPF6_AGG_ADVRTISE                      1          /*·�ɾۺ�ʱ��effect����Ϊͨ��*/
#define OSPF6_AGG_DO_NOT_ADVRTISE               0          /*·�ɾۺ�ʱ��effect����Ϊ��ͨ��*/

#define OSPF6_SUMM_NO_AREA_SUMMARY              0          /*����Stub����ʱ��summary����ΪNO_AREA_SUMMARY*/
#define OSPF6_SUMM_SEND_AREA_SUMMARY            1          /*����Stub����ʱ��summary����ΪSEND_AREA_SUMMARY*/

#define OSPF6_REDI_INTRA_AREA                   0x000D0000 /*����·���������ʱ��Metric Type����ΪINTRA_AREA*/
#define OSPF6_REDI_INTER_AREA                   0x000D0001 /*����·���������ʱ��Metric Type����ΪINTER_AREA */
#define OSPF6_REDI_TYPE1_EXT                    0x000D0002 /*����·���������ʱ��Metric Type����ΪTYPE1_EXT*/
#define OSPF6_REDI_TYPE2_EXT                    0x000D0003 /*����·���������ʱ��Metric Type����ΪTYPE2_EXT*/


#define OSPF6_PREFERENCE_TYPE_INT               0x01       /*����·����������Ϊ:������������·���ϵĴ���*/
#define OSPF6_PREFERENCE_TYPE_EXT               0x02       /*����·����������Ϊ:�������ⲿ·���ϵĴ���*/

#define OSPF6_LSA_MAX_RTR_LINK_D                50         /*·����LSA·���������������ֵ*/
#define OSPF6_LSA_MAX_NET_NBR                   50         /*����LSA�������������������ֵ*/ 
#define OSPF6_LSA_MAX_PRFX_D                    50         /*��·LSA��·ǰ׺�����������ֵ*/ 

#define OSPF6_DIST_OSPF_TO_RM                   1           /*·�����뷽��OSPF->RTM*/
#define OSPF6_DIST_RM_TO_OSPF                   2           /*·�����뷽��RTM->OSPF*/

#define OSPF6_INPUT                             1           /*ע�ᣬȥע��OSPF6���Ӻ����ķ���:����*/
#define OSPF6_OUTPUT                            2           /*ע�ᣬȥע��OSPF6���Ӻ����ķ���:����*/

#define OSPF6_NOFLAG_ADD                        0           /*��������Ϊ���*/
#define OSPF6_NOFLAG_DEL                        1           /*��������Ϊɾ��*/

#define OSPF6_NETWORK_BROADCAST                 1           /*�ӿ�����--�㲥��������*/
#define OSPF6_NETWORK_NBMA                      2           /*�ӿ�����--NBMA��������*/
#define OSPF6_NETWORK_POINT_TO_POINT            3           /*�ӿ�����--P2P��������*/
#define OSPF6_NETWORK_POINT_T_MLTPNT            5           /*�ӿ�����--P2MP��������*/

#define OSPF6_MIN_INTF_COST                     1           /*�ӿ�����--��СCOSTֵ*/
#define OSPF6_MAX_INTF_COST                     65535       /*�ӿ�����--���COSTֵ*/

#define OSPF6_MIN_INTF_RXMT_ITVL                1           /*�ӿ�����--�ش������Сֵ*/
#define OSPF6_MAX_INTF_RXMT_ITVL                1800        /*�ӿ�����--�ش�������ֵ*/
#define OSPF6_DEF_INTF_RXMT_ITVL                5           /*�ӿ�����--�ش����Ĭ��ֵ*/

#define OSPF6_MIN_INTF_TRANS_DELAY              1           /*�ӿ�����--������ʱʱ����Сֵ*/
#define OSPF6_MAX_INTF_TRANS_DELAY              1800        /*�ӿ�����--������ʱʱ�����ֵ*/
#define OSPF6_DEF_INTF_TRANS_DELAY              1           /*�ӿ�����--������ʱʱ��Ĭ��ֵ*/

#define OSPF6_MIN_INTF_HELLO_ITVL               1           /*�ӿ�����--Hello���ļ��ʱ����Сֵ*/
#define OSPF6_MAX_INTF_HELLO_ITVL               65535       /*�ӿ�����--Hello���ļ��ʱ�����ֵ*/
#define OSPF6_DEF_INTF_HELLO_ITVL_0             10          /*�ӿ�����--��NBMA�����⣬Hello���ļ��ʱ��Ĭ��ֵ*/
#define OSPF6_DEF_INTF_HELLO_ITVL_1             30          /*�ӿ�����--NBMA�����ϣ�Hello���ļ��ʱ��Ĭ��ֵ*/

#define OSPF6_MIN_INTF_DEAD_ITVL                1           /*�ӿ�����--Dead Interval��Сֵ*/
#define OSPF6_MAX_INTF_DEAD_ITVL                65535       /*�ӿ�����--Dead Interval���ֵ*/
#define OSPF6_DEF_INTF_DEAD_ITVL_0              40          /*�ӿ�����--��NBMA�����⣬Dead IntervalĬ��ֵ*/
#define OSPF6_DEF_INTF_DEAD_ITVL_1              120         /*�ӿ�����--NBMA�����ϣ�Dead IntervalĬ��ֵ*/

#define OSPF6_MIN_INTF_FAST_HELLO_MULTIPLIER   3            /*�ӿ�����--Fast Hello���ͱ��ĸ�����Сֵ*/
#define OSPF6_MAX_INTF_FAST_HELLO_MULTIPLIER   20           /*�ӿ�����--Fast Hello���ͱ��ĸ������ֵ*/
#define OSPF6_DEF_INTF_FAST_HELLO_MULTIPLIER   5            /*�ӿ�����--Fast Hello���ͱ��ĸ���Ĭ��ֵ*/

#define OSPF6_DEF_INTF_POLL_ITVL                120         /*�ӿ�����--NBMA�����ϣ�Poll IntervalĬ��ֵ*/

#define DF_OSPF6_TO_RM                          1           /*·�����뷽��-OSPF6��RM��*/
#define DF_RM_TO_OSPF6                          2           /*·�����뷽��-RM��OSPF6��*/
 
#define OSPF6_MAX_NBR_PRIORITY                  255         /*��̬�ھ�������ȼ�*/
#define OSPF6_DEF_NBR_PRIORITY                  1           /*��̬�ھ�Ĭ�����ȼ�*/
 
#define OSPF6_ALL_INST_FILTER                   0xFFFFFFFF  /*ͨ���ѯʵ����*/ 
#define OSPF6_MAX_INSTANCE_ID                   0xFF        /*ʵ�������ֵ*/ 
#define OSPF6_MIN_INSTANCE_ID                   0           /*ʵ������Сֵ*/

#define OSPF6_INTF_ATTR_NET_TYPE_BITS           0x0001      /*OSPFv3�ӿ��������ñ���λ:��������*/
#define OSPF6_INTF_ATTR_COST_BITS               0x0002      /*OSPFv3�ӿ��������ñ���λ:costֵ*/
#define OSPF6_INTF_ATTR_PRIORITY_BITS           0x0004      /*OSPFv3�ӿ��������ñ���λ:���ȼ�*/
#define OSPF6_INTF_ATTR_MTU_IGNORE_BITS         0x0008      /*OSPFv3�ӿ��������ñ���λ:MTU����*/
#define OSPF6_INTF_ATTR_RXMT_ITVL_BITS          0x0010      /*OSPFv3�ӿ��������ñ���λ:�ش����*/
#define OSPF6_INTF_ATTR_TRANS_DELAY_BITS        0x0020      /*OSPFv3�ӿ��������ñ���λ:������ʱʱ��*/
#define OSPF6_INTF_ATTR_HELLO_ITVL_BITS         0x0040      /*OSPFv3�ӿ��������ñ���λ:Hello���ķ��ͼ��*/
#define OSPF6_INTF_ATTR_DEAD_ITVL_BITS          0x0080      /*OSPFv3�ӿ��������ñ���λ:�ϻ�ʱ��*/
#define OSPF6_INTF_ATTR_POLL_ITVL_BITS          0x0100      /*OSPFv3�ӿ��������ñ���λ:Poll���*/
#define OSPF6_INTF_ATTR_STATIC_NBR_BITS         0x0200      /* OSPFv3��̬�ھ�����/����Bits���� */
#define OSPF6_INTF_ATTR_GR_HELPER_BITS          0x0400      /*OSPFv3�ӿ��������ñ���λ��GR Helper����*/
#define OSPF6_INTF_ATTR_ALL_BITS                0x05FF

#define OSPF6_SET_INTF_ATTR_BIT(bit, flag)    ((bit) |= (flag))
#define OSPF6_CLR_INTF_ATTR_BIT(bit, flag)    ((bit) &= (~flag))

#define OSPF6_AREA_NSSAOPT_DEFAULT              0x01        /* OSPFv3��������ѡ��:NSSA�������ȱʡ·��(��ѡ���ݲ���) */
#define OSPF6_AREA_NSSAOPT_NOIMPORT             0x02        /* OSPFv3��������ѡ��:��ֹNSSA�߽�·������7��LSAת����5��LSA */
#define OSPF6_AREA_NSSAOPT_NOSUMMARY            0x04        /* OSPFv3��������ѡ��:��ֹABR·��������Summary LSA��NSSA/STUB���� */

#define OSPF6_MAX_AREA_COST_VALUE               0xFFFFFF    /*OSPFv3��������--cost���ֵ*/

#define OSPF6_MIN_AREA_RFSH_ITVL                1           /*OSPFv3��������--�鷺�����Сֵ*/
#define OSPF6_MAX_AREA_RFSH_ITVL                3599        /*OSPFv3��������--�鷺������ֵ*/

/*Ĭ��·�ɴ���ͬOSPFV2����һ��*/
#define OSPF6_DEF_PREFERENCE_INT                10          /*OSPFv3Э������--������·���ϵ�Ĭ�ϴ���*/
#define OSPF6_DEF_PREFERENCE_EXT                150         /*OSPFv3Э������--�ⲿ·���ϵ�Ĭ�ϴ���*/

#define OSPF6_IP_STR_LEN 32
#define OSPF6_INPUT  1                                     /*OSPFv3���Ľ���*/ 
#define OSPF6_OUTPUT 2                                     /*OSPFv3���ķ���*/

#define OSPF6_PORCESS_ID_MIN    1
#define OSPF6_ROUTE_ID_MIN    1

#define OSPF6_CFG_RESET_SET_DOWN     0x01
#define OSPF6_CFG_RESET_SET_UP       0x02
#define OSPF6_CFG_RESET_SET_DOWNUP   (OSPF6_CFG_RESET_SET_DOWN | OSPF6_CFG_RESET_SET_UP)

#define OSPFV3_TRUE     1
#define OSPFV3_FALSE    0

/*�ھ�״̬����*/
#define OSPF6_NBR_STATE_DOWN                ((LONG)1)
#define OSPF6_NBR_STATE_ATTEMPT             ((LONG)2)
#define OSPF6_NBR_STATE_INIT                ((LONG)3)
#define OSPF6_NBR_STATE_TWO_WAY             ((LONG)4)
#define OSPF6_NBR_STATE_EXCHANGE_START      ((LONG)5)
#define OSPF6_NBR_STATE_EXCHANGE            ((LONG)6)
#define OSPF6_NBR_STATE_LOADING             ((LONG)7)
#define OSPF6_NBR_STATE_FULL                ((LONG)8)
/*�ھ��¼�����*/
#define OSPF6_NBR_EVENT_HELLO_RCVD                  0x00
#define OSPF6_NBR_EVENT_INTERFACE_ID_CHANGED        0x01
#define OSPF6_NBR_EVENT_START                       0x02
#define OSPF6_NBR_EVENT_2WAY_RCVD                   0x03
#define OSPF6_NBR_EVENT_NEGOTIATION_DONE            0x04
#define OSPF6_NBR_EVENT_EXCHANGE_DONE               0x05
#define OSPF6_NBR_EVENT_FULLY_EXCHANGED             0x06
#define OSPF6_NBR_EVENT_BAD_LS_REQ                  0x07
#define OSPF6_NBR_EVENT_LOADING_DONE                0x08
#define OSPF6_NBR_EVENT_ADJ_OK                      0x09
#define OSPF6_NBR_EVENT_SEQ_NUMBER_ERR              0x0A
#define OSPF6_NBR_EVENT_1WAY_RCVD                   0x0B
#define OSPF6_NBR_EVENT_KILL_NBR                    0x0C
#define OSPF6_NBR_EVENT_INACTIVITY_TMR              0x0D
#define OSPF6_NBR_EVENT_LL_DOWN                     0x0E
#define OSPF6_NBR_EVENT_JUST_FRIENDS                0x0F
#define OSPF6_NBR_EVENT_SETUP_ADJ                   0x10
#define OSPF6_NBR_EVENT_SLOW_ADJ_ERR                0x11
#define OSPF6_NBR_EVENT_RESET_INACT_TIMER           0x12
/*�ӿ�״̬����*/
#define OSPF6_IF_STATE_DOWN                 ((LONG)1)
#define OSPF6_IF_STATE_LOOPBACK             ((LONG)2)
#define OSPF6_IF_STATE_WAITING              ((LONG)3)
#define OSPF6_IF_STATE_POINT_TO_POINT       ((LONG)4)
#define OSPF6_IF_STATE_DESIGNATED_ROUTER    ((LONG)5)
#define OSPF6_IF_STATE_BACKUP_DESIGNTD_RTR  ((LONG)6)
#define OSPF6_IF_STATE_OTHER_DESIGNATD_RTR  ((LONG)7)
#define OSPF6_IF_STATE_STANDBY               ((LONG)8)
/*�ӿ��¼�����*/
#define OSPF6_IF_INPUT_NON_BCAST_UP              0x00
#define OSPF6_IF_INPUT_ELIG_BCAST_UP             0x01
#define OSPF6_IF_INPUT_BCAST_UP                  0x02
#define OSPF6_IF_INPUT_WAIT_TIMER                0x03
#define OSPF6_IF_INPUT_BACKUP_SEEN               0x04
#define OSPF6_IF_INPUT_NEIGHBOR_CHANGE          0x05
#define OSPF6_IF_INPUT_DR_LOCAL                  0x06
#define OSPF6_IF_INPUT_BACKUP_LOCAL              0x07
#define OSPF6_IF_INPUT_DR_OTHER                  0x08
#define OSPF6_IF_INPUT_LOOP_IND                  0x09
#define OSPF6_IF_INPUT_UNLOOP_IND               0x0A
#define OSPF6_IF_INPUT_INTERFACE_DOWN            0x0B
#define OSPF6_IF_INPUT_MULTI_IF_TO_LINK         0x0C

/*ERRORCODE<OSPF6������>*/
typedef enum tagOSPF6_ERROR_CODE
{
    OSPF6_OK = 0,                                   /*0 <OSPF6���óɹ�>*/
    OSPF6_NO_ERROR,                                 /*1 <OSPF6ͨ�����óɹ�>*/
    OSPF6_ERR_GEN_ERROR = MID_COMP_OSPFV3 + 2,      /*0x0E3D0002 <MIB����ͨ�ô���>*/
    OSPF6_ERR_WRONG_VALUE,                          /*0x0E3D0003 <MIB���õ�ֵ����>*/
    OSPF6_ERR_INCONSISTENT_VALUE,                   /*0x0E3D0004 <MIB���õ�ֵ��һ��>*/
    OSPF6_ERR_RESOURCE_UNAVAILABLE,                 /*0x0E3D0005 <MIB���õ���Դ��Ч>*/
    OSPF6_ERR_NO_SUCH_OBJECT,                       /*0x0E3D0006 <���󲻴���>*/
    OSPF6_ERR_AMB_RC_END_OF_TABLE,                  /*0x0E3D0007 <�������>*/
    OSPF6_ERR_AGENT_ERROR,                          /*0x0E3D0008 <MIB��Ϣ�������>*/
    OSPF6_ERR_INCOMPLETE,                           /*0x0E3D0009 <MIB ������>*/
    OSPF6_ERR_PARTIAL_FAMILY_OK,                    /*0x0E3D0010 <MIB Զ�����óɹ�>*/
    OSPF6_ERR_PRODUCT_NOT_READY,                    /*0x0E3D0011 <��Ӧ���û��׼��>*/
    OSPF6_ERR_NULL_POINTER = MID_COMP_OSPFV3 + 100, /*0x0E3D0064 <���ָ��Ϊ��>*/
    OSPF6_ERR_NOT_REGISTER,                         /*0x0E3D0065 <OSPFv3û��ע��>*/
    OSPF6_ERR_CREATE_MUTUX,                         /*0x0E3D0066 <�����ź���ʧ��>*/
    OSPF6_ERR_GET_IPV6COMP,                         /*0x0E3D0067 <��ȡIPV6���ʧ��>*/
    OSPF6_ERR_ACTION,                               /*0x0E3D0068 <���������ַǷ�>*/
    OSPF6_ERR_PARAMETER,                            /*0x0E3D0069 <���ȡֵ�Ƿ�>*/
    OSPF6_ERR_PROCESS,                              /*0x0E3D006A <>*/
    OSPF6_ERR_IF_NOT_EXIST,                         /*0x0E3D006B <�ӿڲ�����>*/
    OSPF6_ERR_IF_TYPE,                              /*0x0E3D006C <�ӿ����ʹ���>*/
    OSPF6_ERR_GET_IF_INFO,                          /*0x0E3D006D <��ȡ�ӿ���Ϣ���ƿ����>*/
    OSPF6_ERR_PROCESS_NOT_EXIST,                    /*0x0E3D006E <���̲�����>*/
    OSPF6_ERR_MALLOC_FAIL,                          /*0x0E3D006F <�ڴ����ʧ��>*/
    OSPF6_ERR_SAME_BIND_INFO,                       /*0x0E3D0070 <�ý��̻�ʵ���Ѿ����ӿڰ�>*/
    OSPF6_ERR_NOT_MATCH_BIND_INFO,                  /*0x0E3D0071 <ָ�����̻�ʵ��û�а󶨵��ӿ���>*/
    OSPF6_ERR_FAIL_TO_BUILD_IPS,                    /*0x0E3D0072 <����IPS��Ϣʧ��>*/
    OSPF6_ERR_FALI_TO_OPEN_CONNECTION,              /*0x0E3D0073 <���ɷ��;��ʧ��>*/
    OSPF6_ERR_IF_NOT_ENABLE,                        /*0x0E3D0074 <�ӿ�û��ʹ��OSPFV3>*/
    OSPF6_ERR_VRF_NOT_INIT,                         /*0x0E3D0075 <VRF���û�г�ʼ��>*/
    OSPF6_ERR_GET_VRF_INDEX,                        /*0x0E3D0076 <��ȡVRF����ʧ��>*/
    OSPF6_ERR_GET_RTM_INST,                         /*0x0E3D0077 <��ȡRTMʵ����ʧ��>*/
    OSPF6_ERR_PROCESSES_REACH_MAX,                  /*0x0E3D0078 <�������ﵽ���ֵ>*/
    OSPF6_ERR_PROCESS_IPS,                          /*0x0E3D0079 <IPS��Ϣ����ʧ��>*/
    OSPF6_ERR_PROCESS_EXIST,                        /*0x0E3D007A <�����Ѵ���>*/
    OSPF6_ERR_MEM_RELEASE,                          /*0x0E3D007B <�ڴ��ͷ�ʧ��>*/
    OSPF6_ERR_KEY_IS_NULL,                          /*0x0E3D007C <���ָ��Ϊ��>*/
    OSPF6_ERR_INSTANCE,                             /*0x0E3D007D <���̺ŷǷ�>*/
    OSPF6_ERR_INVALID_LSA_TYPE,                     /*0x0E3D007E <LSA���ͷǷ�>*/
    OSPF6_ERR_HAVE_NO_AVL_NODE,                     /*0x0E3D007F <û���ҵ�ָ����AVL�ڵ�>*/
    OSPF6_ERR_PROCESS_NOT_BIND_IF,                  /*0x0E3D0080 <����û�а󶨽ӿ�>*/
    OSPF6_ERR_PROCESS_IF_NOT_MATCH,                 /*0x0E3D0081 <ָ���ӿ�û�а���ָ��������>*/
    OSPF6_ERR_CFG_PREFERENCE_INT,                   /*0x0E3D0082 <����������·������ʧ��>*/
    OSPF6_ERR_CFG_PREFERENCE_EXT,                   /*0x0E3D0083 <�����ⲿ·������ʧ��>*/
    OSPF6_ERR_GET_PREFERENCE,                       /*0x0E3D0084 <����ospfv3Э�����ȼ�ʧ��>*/
    OSPF6_ERR_VRFNAME_TOOLONG,                      /*0x0E3D0085 <VRF������>*/
    OSPF6_ERR_MAX_SPF_DELAY_TIME,                   /*0x0E3D0086 <SPF��ʱ�������ʱʱ�����>*/
    OSPF6_ERR_INVALID_MAX_LOAD_BALANCE,             /*0x0E3D0087 <���ƽ��·�ɸ��������Ƿ�>*/
    OSPF6_ERR_INVALID_PREFERENCE_VALUE,             /*0x0E3D0088 <���ȼ�ȡֵ�Ƿ�>*/
    OSPF6_ERR_INVALID_PREFERENCE_TYPE,              /*0x0E3D0089 <���ȼ����ͷǷ�>*/
    OSPF6_ERR_INVALID_NET_TYPE,                     /*0x0E3D008A <OSPFV3�������ʹ���>*/
    OSPF6_ERR_INSTANCE_NOT_EXIST,                   /*0x0E3D008B <ʵ��������>*/
    OSPF6_ERR_INSTANCE_EXIST,                       /*0x0E3D008C <ʵ�����Ѵ���>*/
    OSPF6_ERR_INVALID_INTF_COST,                    /*0x0E3D008D <�ӿ�costֵ�Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_PRIORITY,                /*0x0E3D008E <�ӿ����ȼ��Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_RXMT_ITVL,               /*0x0E3D008F <�ӿ��ش�����Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_TRANS_DELAY,             /*0x0E3D0090 <�ӿڷ�����ʱ�Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_HELLO_ITVL,              /*0x0E3D0091 <�ӿ�hello���ķ��ͼ���Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_DEAD_ITVL,               /*0x0E3D0092 <�ӿ��ϻ�ʱ��Ƿ�>*/
    OSPF6_ERR_INVALID_INTF_FAST_HELLO_MULTI,        /*0x0E3D0093 <�ӿ�Fast Hello���ķ��͸����Ƿ�>*/
    OSPF6_ERR_INVALID_NBR_PRIORITY_OPT,             /*0x0E3D0094 <���ȼ����ñ�־�Ƿ�>*/
    OSPF6_ERR_INVALID_NBR_PRIORITY,                 /*0x0E3D0095 <���ȼ�ȡֵ�Ƿ�>*/
    OSPF6_ERR_INVALID_NBR_NETWORK,                  /*0x0E3D0096 <NBR�������ʹ���>*/
    OSPF6_ERR_NBR_NOT_EXIST,                        /*0x0E3D0097 <NBR������>*/
    OSPF6_ERR_INVALID_NBR_ADDRESS,                  /*0x0E3D0098 <NBR��ַ��Ч>*/
    OSPF6_ERR_AREA_NOT_EXIST,                       /*0x0E3D0099 <���򲻴���>*/
    OSPF6_ERR_INVALID_AREA,                         /*0x0E3D009A <����ID�Ƿ�>*/
    OSPF6_ERR_AAGG_PREFIX_EXIST,                    /*0x0E3D009B <�ۺϵ�ַ�Ѿ�����>*/
    OSPF6_ERR_AAGG_PREFIX_NOT_EXIST,                /*0x0E3D009C <�ۺϵ�ַ������>*/
    OSPF6_ERR_INVALID_AREA_STUBOPT,                 /*0x0E3D009D <����ѡ��Ƿ�>*/
    OSPF6_ERR_INVALID_AREA_COST,                    /*0x0E3D009E <����costֵ�Ƿ�>*/
    OSPF6_ERR_INVALID_AREA_RFSH_ITVL,               /*0x0E3D009F <����鷺���ʱ��Ƿ�>*/
    OSPF6_ERR_GETFIRST_FAIL,                        /*0x0E3D00A0 <getfirst����ʧ��>*/
    OSPF6_ERR_INVALID_AAGG_PREFIX_LENGTH,           /*0x0E3D00A1 <����ۺ�ǰ׺������Ч>*/
    OSPF6_ERR_PROCESS_ID_IS_ZERO,                   /*0x0E3D00A2 OSPF6α����*/
    OSPF6_ERR_DISABLE_OSPF_ADMIN_STATUS,            /*0x0E3D00A3 disable����ʧ��*/
    OSPF6_ERR_ENABLE_OSPF_ADMIN_STATUS,             /*0x0E3D00A4 enable����ʧ��*/
    OSPF6_ERR_INVALID_ACCNUM,                       /*0x0E3D00A5 ��Ч��ACC���*/
    OSPF6_ERR_CFG_GR_PARA,                          /*0x0E3D00A6 OSPF6 GR���ò�������*/
    OSPF6_ERR_INVALID_GR_PERIOD,                    /*0x0E3D00A7 OSPF6 GR���ڲ�������*/
    OSPF6_ERR_GET_SOCK_INST,                        /*0x0E3D00A8 <��ȡSOCKʵ����ʧ��>*/
    OSPF6_ERR_GET_I3_INST,                          /*0x0E3D00A9 <��ȡI3ʵ����ʧ��>*/
    OSPF6_ERR_AREA_EXIST,                           /*0x0E3D00AA <�����Ѿ�����>*/
    OSPF6_ERR_DEAD_ITVL_LESS_HELLO_ITVL,            /*0x0E3D00AB <���õ�dead intervalС��hello interval>*/
    OSPF6_ERR_AREA_REACH_MAX,                       /*0x0E3D00AC <Ŀǰ������Ŀ�ﵽ���>*/
    OSPF6_ERR_END                                   /*0x0E3D00AD <Ŀǰ����������>*/
}OSPF6_ERROR_E;

/* Added by likaikun00213099, ���ڽӿ�ͳ�Ƹ�״̬���ھ�, 2014/4/15 */
/* Number of states. */
#define OSPF6_NBR_MAX_STATES  8
/* End of Added by likaikun00213099, ���ڽӿ�ͳ�Ƹ�״̬���ھ�, 2014/4/15 */

/*Added by guojianjun178934, OSPFV3�澯���Ͷ���, 2014/5/12   ���ⵥ��:S-IP-005-OSPFv3-005  */
typedef enum tagOSPFV3_WARNING_TYPE
{
    OSPFV3_WARNING_IF_EVENT = 1,    /*�ӿ��¼��澯*/
    OSPFV3_WARNING_NBR_EVENT,       /*�ھ��¼��澯*/
    OSPFV3_WARNING_NBR_STATE,       /*OSPF�ھӸ澯*/
    OSPFV3_WARNING_MAX
} OSPFV3_WARNING_TYPE_E;

typedef ULONG (*OSPFV3_WARNING_HOOK_FUNC)(ULONG ulWarningType, VOID *pWarningInfo);

#include "ospf6_api_01.h"
/* End of Added by guojianjun178934, 2014/5/12   ���ⵥ��:S-IP-005-OSPFv3-005  */
#include "ospf6_cfg_api.h"
#include "ospf6_cmm_api.h"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF6_API_H_ */

