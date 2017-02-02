/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_def.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF API �궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef _OSPF_API_DEF_H
#define _OSPF_API_DEF_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*01 ������־*/
#define OSPF_NOFLAG_ADD 0
#define OSPF_NOFLAG_DEL 1

#define OSPF_INPUT  1
#define OSPF_OUTPUT 2

#define DF_OSPF_TO_RM 1         /*·�����뷽��-OSPF��RM��*/
#define DF_RM_TO_OSPF 2         /*·�����뷽��-RM��OSPF��*/

/*02 ���*/
#define OSPF_ENCRYPT_DATA_LENGTH 255
#define OSPF_MAX_IF_NAME_LENGTH 47
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define OSPF_MAX_VRF_NAME_LENGTH 31
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
#define OSPF_MAX_EQCOST_PATH 32
#define OSPF_MAX_INET_ADDR_LEN 32

#define OSPF_ARRAY_SIZE_3           3
#define OSPF_LSA_MAX_RTR_PIECE     50
#define OSPF_LSA_MAX_TOS_COUNT     20
#define OSPF_LSA_MAX_NET_NBR       50
#define OSPF_LSA_MAX_SUM_PIECE     10
#define OSPF_LSA_MAX_ASE_PIECE     10
#define OSPF_LSA_MAX_OPQ_DATA      10


/*03 ���Ͷ���*/
#define OSPF_ROUTER_LSA           1
#define OSPF_NETWORK_LSA          2
#define OSPF_SUMMARY_LSA          3
#define OSPF_SUMMARY_ASBR_LSA     4
#define OSPF_ASEXTERNAL_LSA       5
#define OSPF_NSSA_LSA             7
#define OSPF_OPAQUE_LOCAL_LSA     9
#define OSPF_OPAQUE_AREA_LSA      10
#define OSPF_OPAQUE_AS_LSA        11
#define  OSPF_LSA_MAX_TYPE        11

/* 04 Ĭ��ʱ�� */
#define OSPF_HELLO_INTER_10       10     /* BROADCAST POINT_TO_POINT LOOPBACK */
#define OSPF_HELLO_INTER_30       30     /* NBMA POINT_T_MLTPNT */
#define OSPF_DEAD_INTER_40        40     /* BROADCAST POINT_TO_POINT LOOPBACK */
#define OSPF_DEAD_INTER_120       120    /* NBMA POINT_T_MLTPNT */


#define OSPF_CFG_NSSAOPT_DEFAULT    0x01 /* bring default Type-7LSA to area NSSA  */
#define OSPF_CFG_NSSAOPT_NOIMPORT   0x02 /* no import exterior route to NSSA area */
#define OSPF_CFG_NSSAOPT_NOSUMMARY  0x04 /* forbid ABR send Summary LSA to NSSA area */
#define OSPF_CFG_NSSAOPT_TRANSLATE_ROLE_ALWAYS 0x08 /*translation of type-7 LSAs into type-5 LSAs.*/


#define OSPF_CFG_IF_AUTH_NULL         0x0
#define OSPF_CFG_IF_AUTH_SIMPLE       0x1
#define OSPF_CFG_IF_AUTH_MD5          0x2
#define OSPF_CFG_IF_AUTH_HMAC         0x3
#define OSPF_CFG_IF_AUTH_MAX          OSPF_CFG_IF_AUTH_HMAC
#define OSPF_CFG_IF_AUTH_NOCFG        0xff 

#define OSPF_IF_PASSWORD_PLAIN        0x01
#define OSPF_IF_PASSWORD_CIPHER       0x02

#define OSPF_AREA_PASSWORD_PLAIN    0x01
#define OSPF_AREA_PASSWORD_CIPHER   0x02

#define OSPF_AUTH_SIMPLE_PW_LEN_MAX   8
#define OSPF_AUTH_MD5_PW_LEN_MAX      255 

#define OSPF_PREFERENCE_SWITH_INT   0x01
#define OSPF_PREFERENCE_SWITH_EXT   0x02

#define OSPF_CFG_RESET_CFG_GRPARA   0x00
#define OSPF_CFG_RESET_SET_DOWN     0x01
#define OSPF_CFG_RESET_SET_UP       0x02
#define OSPF_CFG_RESET_SET_DOWNUP   0x03

/*Begin BC3D00000 liangjicheng 2009-09-09*/
/*OSPF �ӿ��������� */
#define OSPF_NETWORK_BROADCAST       1
#define OSPF_NETWORK_NBMA            2
#define OSPF_NETWORK_POINT_TO_POINT  3
#define OSPF_NETWORK_POINT_T_MLTPNT  5
#define OSPF_NETWORK_LOOPBACK        10

/*Hitless Restart Reason*/
#define OSPF_RESTART_REASON_UNKNOWN 0
#define OSPF_RESTART_REASON_SOFTWARE_RESTART 1
#define OSPF_RESTART_REASON_SOFTWARE_RELOAD  2
#define OSPF_RESTART_REASON_SWITCH_TO_BACKUP 3

/*Helper Mode*/
#define OSPF_HELP_POLICY_NONE       0x00000000
#define OSPF_HELP_POLICY_UNKNOWN    0x00000001
#define OSPF_HELP_POLICY_SOFTWARE   0x00000002
#define OSPF_HELP_POLICY_RELOAD     0x00000004
#define OSPF_HELP_POLICY_SWITCH     0x00000008
#define OSPF_HELP_POLICY_ALL        0x0000000F
/*End   BC3D00000 liangjicheng 2009-09-09*/

/* ����/ɾ�� OSPF����·�ɵĲ���*/
typedef enum tagOSPF_RPM_METRICTYPE
{
    OSPF_RPM_MTYPE_INVALID   =   0, 
    OSPF_RPM_MTYPE_INTERNAL  =   1,
    OSPF_RPM_MTYPE_EXTERNAL  =   2,
    OSPF_RPM_MTYPE_TYPE1     =   3,
    OSPF_RPM_MTYPE_TYPE2     =   4
} OSPF_RPM_METRICTYPE_E;

/*Begin BC3D02903 liangjicheng 2010-04-19 */
#define OSPF_NBR_STATE_DOWN                ((LONG)1)
#define OSPF_NBR_STATE_ATTEMPT             ((LONG)2)
#define OSPF_NBR_STATE_INIT                ((LONG)3)
#define OSPF_NBR_STATE_TWO_WAY             ((LONG)4)
#define OSPF_NBR_STATE_EXCHANGE_START      ((LONG)5)
#define OSPF_NBR_STATE_EXCHANGE            ((LONG)6)
#define OSPF_NBR_STATE_LOADING             ((LONG)7)
#define OSPF_NBR_STATE_FULL                ((LONG)8)
/*End   BC3D02903 liangjicheng 2010-04-19 */
/*Begin BC3D03553 liangjicheng 2010-08-10 */
#define OSPF_NBR_EVENT_HELLO_RCVD                  0x00
#define OSPF_NBR_EVENT_INTERFACE_ID_CHANGED        0x01
#define OSPF_NBR_EVENT_START                       0x02
#define OSPF_NBR_EVENT_2WAY_RCVD                   0x03
#define OSPF_NBR_EVENT_NEGOTIATION_DONE            0x04
#define OSPF_NBR_EVENT_EXCHANGE_DONE               0x05
#define OSPF_NBR_EVENT_FULLY_EXCHANGED             0x06
#define OSPF_NBR_EVENT_BAD_LS_REQ                  0x07
#define OSPF_NBR_EVENT_LOADING_DONE                0x08
#define OSPF_NBR_EVENT_ADJ_OK                      0x09
#define OSPF_NBR_EVENT_SEQ_NUMBER_ERR              0x0A
#define OSPF_NBR_EVENT_1WAY_RCVD                   0x0B
#define OSPF_NBR_EVENT_KILL_NBR                    0x0C
#define OSPF_NBR_EVENT_INACTIVITY_TMR              0x0D
#define OSPF_NBR_EVENT_LL_DOWN                     0x0E
#define OSPF_NBR_EVENT_JUST_FRIENDS                0x0F
#define OSPF_NBR_EVENT_SETUP_ADJ                   0x10
#define OSPF_NBR_EVENT_SLOW_ADJ_ERR                0x11
#define OSPF_NBR_EVENT_RESET_INACT_TIMER           0x12
/*End   BC3D03553 */

/*IF FSM inputs*/
#define OSPF_IF_INPUT_NON_BCAST_UP              0x00
#define OSPF_IF_INPUT_ELIG_BCAST_UP             0x01
#define OSPF_IF_INPUT_BCAST_UP                  0x02
#define OSPF_IF_INPUT_WAIT_TIMER                0x03
#define OSPF_IF_INPUT_BACKUP_SEEN               0x04
#define OSPF_IF_INPUT_NEIGHBOR_CHANGE          0x05
#define OSPF_IF_INPUT_DR_LOCAL                  0x06
#define OSPF_IF_INPUT_BACKUP_LOCAL              0x07
#define OSPF_IF_INPUT_DR_OTHER                  0x08
#define OSPF_IF_INPUT_LOOP_IND                  0x09
#define OSPF_IF_INPUT_UNLOOP_IND               0x0A
#define OSPF_IF_INPUT_INTERFACE_DOWN            0x0B
#ifdef BLD_OSPFV3
#define OSPF_IF_INPUT_MULTI_IF_TO_LINK         0x0C
#endif
/*IF FSM states*/
#define OSPF_IF_STATE_DOWN                 ((LONG)1)
#define OSPF_IF_STATE_LOOPBACK             ((LONG)2)
#define OSPF_IF_STATE_WAITING              ((LONG)3)
#define OSPF_IF_STATE_POINT_TO_POINT       ((LONG)4)
#define OSPF_IF_STATE_DESIGNATED_ROUTER    ((LONG)5)
#define OSPF_IF_STATE_BACKUP_DESIGNTD_RTR  ((LONG)6)
#define OSPF_IF_STATE_OTHER_DESIGNATD_RTR  ((LONG)7)

/*OSPF��ʱ��ֻ�õ�ʱ�Ӻ������Ͷ���*/
/*ע�⣺��ʱ�����Ͷ����޸�ʱ����ͬ���޸�NBB_TIMER_TYPE_***�еĶ���*/
#define OSPF_TIMER_TYPE_LINUX         1    /*OSPFʹ��Linuxϵͳ�ṩ��ʱ�Ӻ���*/
#define OSPF_TIMER_TYPE_LINUX_EXT     2    /*OSPFʹ��Linux�ṩ��ʱ�Ӻ���*/

/*ospfģ��Ĵ�����*/
typedef enum tagOSPF_ERROR_CODE
{
    OSPF_OK = 0,
    /*���´�������DCLͨ��mib����ֱ�ӷ���,ֻ��IPS���ص�ʱ���ʹ��*/
    OSPF_NO_ERROR = 1,                   /*�ɹ�*/
    OSPF_ERR_GEN_ERROR = MID_COMP_OSPF + 2, /*002*/
    OSPF_ERR_WRONG_VALUE,                   /*003*/
    OSPF_ERR_INCONSISTENT_VALUE,            /*004*/
    OSPF_ERR_RESOURCE_UNAVAILABLE,          /*005*/
    OSPF_ERR_NO_SUCH_OBJECT,                /*006*/
    OSPF_ERR_AMB_RC_END_OF_TABLE,           /*007*/
    OSPF_ERR_AGENT_ERROR,                   /*008*/
    OSPF_ERR_INCOMPLETE,                    /*009*/
    OSPF_ERR_PARTIAL_FAMILY_OK,             /*010*/
    OSPF_ERR_PRODUCT_NOT_READY,             /*011*/
    OSPF_ERR_IPS_RETURN_TIME_OUT  = MID_COMP_OSPF + 15,   /*015*/
    /*���������룬��100��ʼ*/
    OSPF_ERR_NULL_POINTER  = MID_COMP_OSPF + 100,   /*100 ����Ϊ��ָ��*/
    OSPF_ERR_PARAMETER,                  /*101 ����ֵ����*/     
    OSPF_ERR_FAIL_TO_BUILD_IPS,          /*102 ����IPS��Ϣʧ��*/
    OSPF_ERR_FALI_TO_OPEN_CONNECTION,    /*103 ���ɷ��;��ʧ��*/
    OSPF_ERR_PROCESS_IPS,                /*104 ����IPS��Ϣ�󣬷���ʧ��*/
    OSPF_ERR_IF_NAME,                    /*105 ����Ľӿ���*/
    OSPF_ERR_FAIL_TO_GET_IPADDR,         /*106 ͨ���ӿ�����ȡ�׵�ַʧ��*/
    OSPF_ERR_CFG_ALREADY_EXIST,          /*107 �����Ѿ�����*/
    OSPF_ERR_NULL_MIB_ENTRY,             /*108 mibʵ��ָ��Ϊ��*/
    OSPF_ERR_CFG_NOT_EXIST,              /*109 ���ò�����*/
    OSPF_ERR_KEY_IS_NULL,                /*110 ���ڻ�ȡ��һ��mib���keyָ��ΪNULL*/
    OSPF_ERR_WRONG_CFG_TYPE,             /*111 �������������*/
    OSPF_ERR_PROCESSES_REACH_MAX,        /*112 �������ﵽ���*/
    OSPF_ERR_PROCESS_NOT_EXIST,          /*113 ���̲�����*/
    OSPF_ERR_NO_MEMORY,                  /*114 ����������*/
    OSPF_ERR_FIND_NEXT_NODE_FAIL,        /*115 fail to find next routing node*/
    OSPF_ERR_ENABLE_OSPF_ADMIN_STATUS,   /*116 fail to enable ospf process's admin status*/
    OSPF_ERR_DISABLE_OSPF_ADMIN_STATUS,  /*117 fail to disable ospf process's admin status*/
    OSPF_ERR_CFG_GR_PARA,                /*118 fail to config grace restart parameter*/
    OSPF_ERR_HAVE_NO_AVL_NODE,           /*119 �ҵ������ڵ�*/
    OSPF_ERR_HAVE_NO_NEXT_AVL_NODE,      /*120 �Ҳ�����һ���ڵ�*/
    OSPF_ERR_HAVE_NO_VNBR,               /*121 �Ҳ������ھ�*/
    OSPF_ERR_HAVE_NO_NEXT_VNBR,          /*122 �Ҳ�����һ�����ھ�*/
    OSPF_ERR_IF_HAVE_MORE_VNBR,          /*123 �ӿ��и�������ھӣ���ʾ������*/ 
    OSPF_ERR_HAVE_NO_AREA_CB,            /*124 û����*/
    OSPF_ERR_HAVE_NO_NEXT_AREA_CB,       /*125*/
    OSPF_ERR_HAVE_NO_LSDB_CB,            /*126*/
    OSPF_ERR_HAVE_NO_NEXT_LSDB_CB,       /*127*/
    OSPF_ERR_HAVE_NO_LSA,                /*128 û��LSA*/
    OSPF_ERR_INVALID_LSA_TYPE,           /*129*/
    OSPF_ERR_HAVE_NO_HANDLE,             /*130 û�о��*/
    OSPF_ERR_INSTANCE_CAN_NOT_ZERO,      /*131*/
    OSPF_ERR_MALLOC,                     /*132 �����ڴ�ʧ��*/

    OSPF_ERR_CFG_REFRESH_HELLO,          /*133 fail to Refresh other paremter */
    OSPF_ERR_CFG_REFRESH_DEAD,           /*134*/
    OSPF_ERR_PROCESS_ID_IS_ZERO,         /*135 OSPFα����Ϊ0*/
    OSPF_ERR_NO_CFG_IF,                  /*136 û�����ýӿ�*/
    OSPF_ERR_GET_NET_TYPE,               /*137*/
    OSPF_ERR_INVALID_IPADDR,             /*138*/
    OSPF_ERR_INVALID_PROCID,             /*139*/
    OSPF_ERR_INVALID_NOFLAG,             /*140*/
    OSPF_ERR_INVALID_AREA,               /*141*/
    OSPF_ERR_INVALID_VALUE,              /*142*/
    OSPF_ERR_CFG_PREFERENCE_INT,         /*143*/
    OSPF_ERR_CFG_PREFERENCE_EXT,         /*144*/
    OSPF_ERR_MODULE_NOT_REGISTERED,      /*145*/
    
    OSPF_ERR_MEM_RELEASE,
    OSPF_ERR_INVALID_GR_PERIOD,          /*147 Invalid Gr period BC3D01086 liangjicheng 09-01-14*/

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    OSPF_ERR_GET_VRF_INDEX,              /*148 */
    OSPF_ERR_INST_NOT_IN_VRF,            /*149 */
    OSPF_ERR_GET_RTM_INST,               /*150 */
    OSPF_ERR_VRF_NOT_INIT,               /*151 */
    OSPF_ERR_CFG_DEADTIME,               /*152 ���õ�Dead TimeС�ڻ����Hello Time BC3D02558 10-01-04*/
    OSPF_ERR_CFG_HELLOTIME,              /*153 ���õ�Hello Time���ڻ����Dead Time BC3D02558 10-01-04*/
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
    /* add for BC3D02908  */
    OSPF_ERR_INVALID_ACCNUM= MID_COMP_OSPF + 154,    /*154 acl���������Ч */
    /* end for BC3D02908  */
    
    OSPF_ERR_INVALID_PROTO_TYPE,         /*155 ��ЧЭ������ */
    OSPF_ERR_INVALID_METRIC_TYPE,        /*156 ��ЧMetric���� */
    OSPF_ERR_INVALID_METRIC_VAL,         /*157 ��ЧMetricֵ */
    OSPF_ERR_INVALID_STATIC_RPAID,       /*158 ��Ч��̬Э������ID */
    OSPF_ERR_INVALID_DYNAMIC_RPAID,      /*159 ��Ч��̬Э������ID */
    
    OSPF_ERR_WAIT_RTM_JOIN_STATUS_TIMEOUT, /*160 �ȴ�OSPFͬRTM Join ״̬��ʱ */
    OSPF_ERR_WAIT_RTM_JOIN_ACTIVE_TIMEOUT,      /*161 �ȴ�OSPFͬRTM Join UP��ʱ */
    OSPF_ERR_WAIT_RTM_JOIN_GONE_TIMEOUT,    /*162 �ȴ�OSPFͬRTM GONE UP��ʱ */
    OSPF_ERR_END                         
}OSPF_ERROR_E;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _OSPF_SGSN_API_DEF_H_ */

