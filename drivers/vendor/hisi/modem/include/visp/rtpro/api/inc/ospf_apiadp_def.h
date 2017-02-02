/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_apiadp_def.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description: 
*   01 OSPF ����ģ�鶨��ĺ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                              
*******************************************************************************/

#ifndef OSPF_APIADP_DEF_H
#define OSPF_APIADP_DEF_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "ospf_api.h"

#if 1
#define OSPF_ADP_PT_BEGIN           (VOID)TCPIP_SmP(ospf_adp_mutex)
#define OSPF_ADP_PT_END             (VOID)TCPIP_SmV(ospf_adp_mutex)
#else
#define OSPF_ADP_PT_BEGIN
#define OSPF_ADP_PT_END
#endif

#define OSPF_TRUE 1
#define OSPF_FALSE 2

#define OSPF_CFG_ADD 1
#define OSPF_CFG_DEL 0

#define OSPF_F_PRIMARY 1
#define OSPF_F_SECONDARY 0

#define OSPF_IP_STR_LEN 32

#define OSPF_USED 1
#define OSPF_UNUSED 0

/*Begin BC3D01729 ����� liangjicheng 2009-07-06*/
#define OSPF_ADMIN_UP 1
#define OSPF_ADMIN_DOWN 0

#define OSPF_IPV4_MAX_MASKLEN   32
#define OSPF_IP_STRING_LEN      32

#define OSPF_PORCESS_ID_MIN  1          /*��С���̺�*/
#define OSPF_PORCESS_ID_MAX  0xffff     /*�����̺�*/

#define OSPF_LSA_DELAY_MIN  1           /*��СLSA��ʱʱ�� 1s*/
#define OSPF_LSA_DELAY_MAX  3600        /*���LSA��ʱʱ�� 3600s*/

#define OSPF_MTU_LEN_MIN  46            /*��СMTU����*/
#define OSPF_MTU_LEN_MAX  1560          /*���MTU����*/

#define OSPF_IF_COST_MIN  1             /*��С�ӿ�Costֵ*/
#define OSPF_IF_COST_MAX  0xffff        /*���ӿ�Costֵ*/


#define OSPF_AREA_RFSH_ITVL_MIN  1      /*��С����ˢ�¼�� s*/
#define OSPF_AREA_RFSH_ITVL_MAX  3599   /*�������ˢ�¼�� s*/

#define OSPF_POLL_ITVL_MAX  0xffff      /*�����ѯʱ��*/

#define OSPF_MIB_TRY_TIMES  4           /*MIB���ó��Դ���*/
#define OSPF_MIB_TRY_DELAY  500         /*MIB���ó�����ʱʱ�� ms*/

#define OSPF_AREA_ASYSNC_WAIT_TIMES  20   /*��������ʱ�첽�ȴ�����*/
#define OSPF_AREA_ASYSNC_WAIT_ITVL   200  /*��������ʱ�첽�ȴ���� ms*/
/*End BC3D01729*/

/*���������Ƿ�Ϊstub/nssa*/
#define OSPF_GENERAL_AREA 1
#define OSPF_STUB_AREA    2
#define OSPF_NSSA_AREA    3

/*���������*/
#define OSPF_SUMM_NO_AREA_SUMMARY     1
#define OSPF_SUMM_SEND_AREA_SUMMARY   2

#define OSPF_NO_AREA_DEFAULT_LSA  1
#define OSPF_AREA_DEFAULT_LSA     2
/*End for BC3D02758*/

#define OSPF_AREA_NSSA_NO_IMPORT  1
#define OSPF_AREA_NSSA_IMPORT     2

/*·�ɾۺ�ʱ��LSDB����*/
#define OSPF_LS_SUMMARY_LINK 3
#define OSPF_LS_NSSA_EXTERNAL_LINK 7

/*·�ɾۺ�ʱ��effect����*/
#define OSPF_EFFECT_ADV_MATCHING 1
#define OSPF_EFFECT_DO_NOT_ADV   2

#define OSPF_AREA_ADMIN_STATUS_UP   1
#define OSPF_AREA_ADMIN_STATUS_DOWN 2

#define OSPF_MAX_PROCESSES 32          /*��������*/

/*Begin BC3D01086 liangjicheng 09-01-14*/
#define OSPF_GR_MIN_PERIOD 1          /*��СGR����ʱ�� 1s*/
#define OSPF_GR_MAX_PERIOD 1800       /*���GR����ʱ�� 1800s*/
/*End BC3D01086 liangjicheng 09-01-14*/

/*Begin BC3D01513 liangjicheng 2009-04-28*/
#define OSPF_CFG_RYTRY_TIMES 5          /*ʧ�������ô���*/
#define OSPF_CFG_RYTRY_INTERVAL 200     /*ʧ�������ü�� ms*/
/*End BC3D01513 */

/*Begin BC3D01513 liangjicheng 2009-04-28*/
#define OSPF_GR_BACKUP_OFFSET  60*60    /*1Сʱ ��λ:s*/
/*End BC3D01513 */

#define ERR_NO_ERR                  OSPF_OK
#define ERR_RESOURCE_UNAVAILABLE    OSPF_ERR_NO_MEMORY
#define ERR_CFG_ALREADY_EXIST       OSPF_ERR_CFG_ALREADY_EXIST
#define ERR_CFG_NOT_EXIST           OSPF_ERR_CFG_NOT_EXIST

/*����ospf entity��ص�����*/
#define OSPF_CFG_ASBR_ROUTER 1
#define OSPF_CFG_CMD_CLEAR_OSPFPROC 2
#define OSPF_CFG_CMD_MAXPATHS 3
#define OSPF_CFG_CMD_ROUTER_OSPF_PROC 4
#define OSPF_CFG_COMP_RFC1583 5
#define OSPF_CFG_SPF_CALC_ITVL 6
#define OSPF_CFG_ROUTER_ID 7
#define OSPF_CFG_ADMIN_STATUS 8
#define OSPF_CFG_CMD_CALC_DELAY 9

#define OSPF_CALC_DELAY_MIN  1         /*��С�ӳ�ʱ�� ms*/
#define OSPF_CALC_DELAY_MAX  10000     /*����ӳ�ʱ�� ms*/

/*����ospf if��ص�����*/
#define OSPF_CFG_IF_AUTHKEY 1
#define OSPF_CFG_IP_DEAD_ITVL 2
#define OSPF_CFG_IP_HELLO_ITVL 3
#define OSPF_CFG_IP_NETWORK 4
#define OSPF_CFG_PASSIVE_IF 5
#define OSPF_CFG_IF_ENABLE 6
#define OSPF_CFG_IF_LSA_DELAY 7
#define OSPF_CFG_IF_POLL_ITVL 8
#define OSPF_CFG_IF_PRIORITY 9
#define OSPF_CFG_INTERFACE_TO_AREA 10
#define OSPF_CFG_IF_MAX_MTU 11
#define OSPF_CFG_AUTO_DEL_NBR 12
#define OSPF_CFG_GR_HELPER 13
#define OSPF_CFG_IF_COST 14
#define OSPF_CFG_IF_RETRANSMIT 15


/*struct id,���������ڴ�ʹ��*/
#define SID_OSPF_SHOWIF_KEY_S        100
#define SID_OSPF_LSDB_KEY_S          101
#define SID_OSPF_NBR_KEY_S           102
#define SID_OSPF_ROUTING_KEY_S       103
#define SID_OSPF_VIRTUAL_IF_KEY_S    104
#define SID_OSPF_VIRTUAL_LSDB_KEY_S  105
#define SID_OSPF_VIRTUAL_NBR_KEY_S   106
#define SID_OSPF_CFG_OSPF_CB_S       107
#define SID_OSPF_CFG_AREA_CB_S       108
#define SID_OSPF_CFG_AREA_INFO_S     109
#define SID_OSPF_CFG_AUTH_CB_S       110
#define SID_OSPF_CFG_NETWORK_CB_S    111
#define SID_OSPF_CFG_NETWORK_INFO_S  112
#define SID_OSPF_CFG_IF_CB_S         113
#define SID_OSPF_ENTITY_KEY_S        114
#define SID_OSPF_IF_METRIC_KEY_S     115
#define SID_OSPF_AREA_KEY_S          116
#define SID_OSPF_AREA_AGG_KEY_S      117
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
#define SID_OSPF_INIT                118
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

/*�������*/
#define SID_OSPF_DIRECT_NBR_KEY_S      118
#define SID_OSPF_DIRECT_VNBR_KEY_S      119
#define SID_OSPF_DIRECT_LSDB_KEY_S      120
#define SID_OSPF_DIRECT_VLSDB_KEY_S      121

/*����ospf area��ص�����*/
#define OSPF_CFG_CMD_AREA_NSSA 1
#define OSPF_CFG_AREA_RFSH_ITVL 2
#define OSPF_CFG_CMD_AREA_STUB 3
#define OSPF_CFG_AREA_ADMIN_STATUS 4
#define OSPF_CFG_AREA 5 /*for config area aggregate,you must config the area explicitly via MIB configured,
                            rather than implicitly created by an interface activation,otherwise return error*/

#define OSPF_IN_CLASSA(i) (0 == ((long)(i) & 0x80000000L))
#define OSPF_IN_CLASSB(i) (0x80000000L == ((long)(i) & 0xc0000000L))
#define OSPF_IN_CLASSC(i) (0xc0000000L == ((long)(i) & 0xe0000000L))


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif
