/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_type.h
*
*  Project Code:
*   Module Name: PTPV2 def
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description: PTPV2���Ժ궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_DEF_H_
#define _PTPV2_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PTPV2_YES 1
#define PTPV2_NO  0

#define PTPV2_CREATE  1
#define PTPV2_DELETE  0

/*����PTPV2ģ��MID/SID*/
#define PTPV2_MID       MID_COMP_PTPV2
#define SID_PTP_FOREIGN_MASTER   1
#define SID_PTP_PORTINFO         2
#define SID_PTP_SUBPORTINFO      3
#define SID_PTP_PORTMANAGEINFO   4
#define SID_PTP_GLOBALINFO       5
#define SID_PTP_TIMER            6

/* PTP�汾�� */
#define PTPV2_VERSION       2

/* Keep alive ���ĵķ��ͼ�� 64S */
#define PTPV2_LIVE_INTERVAL     6

/* PTPV2������ */
#define PTPV2_TASK_NAME     "PTP2"

/*PTPV2���г���*/
#define PTPV2_QDEPTH      2048

/*PTPV2�������ͱ�־*/
#define PTPV2_QMODE       VOS_Q_FIFO | VOS_Q_SYN

#define PTPV2_EVT_TASK_OVER_Q      0x00010000

/* �¼�id��Ҫʹ�ø�16λ*/
#define PTPV2_IEEE8023MSG_EVENT_ID  0x00020000      /*MAC����д�뵽PTP����ʹ�ø���Ϣ*/
#define PTPV2_IEEE8023_MSG_TYPE 0x00001000          /*MAC����д�뵽PTP����MSG[0]ʹ�øñ�ʶ*/



#define VLANTYPE_DOT1Q  0x8100              /* VLAN 802.1q��ʽ*/
#define PTPV2_IEEE8023_ETHTYPE  0x88F7      /*1588 OVER MAC ��̫����*/

#define DOT1Q_TAG_SIZE  4

#define PTPV2_MACADDRLEN  6

#define PTPV2_HEADER_LEN 34

/* PTP������󳤶� */
#define PTPV2_MAXIMUM_PKT_SIZE   2048

#define PTPV2_VERSION                     2

#define PTPV2_MAX_PORTNO    128  /*����PTP�˿ڸ���*/
#define PTPV2_MIN_PORTNO     1   /*��С��PTP�˿ڸ���*/

#define SE_ASYNC   0x0020


#define TCPIP_PTP_WARN_BMC_FAIL_FLAG    0x0001  /* PTPѡԴʧ�ܸ澯���*/

#define PTPV2_TIMER_DELETE 1
#define PTPV2_TIMER_NOT_DELETE 0

#define  PTPV2_FSM_MODE_OC_MASTER  1
#define  PTPV2_FSM_MODE_OC_SLAVE   2
#define  PTPV2_FSM_MODE_BC         3

extern int PTPV2_compare(void *a, void *b);
#define PTPV2_init_avl_node(NODE)            (NODE).parent = 0;                \
                                             (NODE).left = 0;                  \
                                             (NODE).right = 0;                 \
                                             (NODE).sLeftHeight = -1;                \
                                             (NODE).sLeftHeight = -1
#define PTPV2_Tree_offset(STRUCT,FIELD) (unsigned short)((unsigned char *)(&((STRUCT *)1)->FIELD) - (unsigned char *)1)
#define PTPV2_avl_insert(TREE, NODE, TREE_INFO) (NULL == AVL3_FindToInsert(&(TREE), &(NODE), &(TREE_INFO)))
#define PTPV2_avl_delete(TREE, NODE)            AVL3_DeleteNode(&(TREE), &(NODE))
#define PTPV2_find(TREE, KEY, TREE_INFO) AVL3_FindNode(&(TREE), (KEY), &(TREE_INFO))

#define PTPV2_avl_next(NODE, TREE_INFO) AVL3_GetNextNode(&(NODE), &(TREE_INFO))
#define PTPV2_avl_first(TREE, TREE_INFO) AVL3_GetFirstNode(&(TREE), &(TREE_INFO))

#define  TCPIP_PTP_FOREIGN_MASTER_LEN   8

#define PTPV2_CLASSQL_NUM     16

/*BMC ѡԴ���ԣ�Ŀǰ��֧��1588ѡԴ*/
#define  TCPIP_PTP_BMC_POLICY_1588     1
#define  TCPIP_PTP_BMC_POLICY_G8265    2
#define  TCPIP_PTP_BMC_POLICY_G8275    3

/*��ǰԴ�Ƿ���ѡԴ���*/
#define PTPV2_PRI_CLASS  1
#define PTPV2_NOT_PRI_CLASS  0

/*stepsRemoved�����Чֵ*/
#define PTPV2_MAX_STEPSREMOVED  255

/* ��ʱ���ƶ��� */
typedef enum tagTCPIP_PTP_DELAY_MACHENISM_E
{
    /*Ŀǰ��֧��E2E*/
    TCPIP_PTP_DELAY_MACHENISM_E2E = 0X01,          /* ����_��Ӧ��ʱ���� */
    TCPIP_PTP_DELAY_MACHENISM_P2P = 0X02,          /* �Զ���ʱ���� */
    TCPIP_PTP_DELAY_MACHENISM_DISABLE = 0XFE       /* ��ʱ���Ʋ����� */
} TCPIP_PTP_DELAY_MECHENISM_E;


/* ���嵥�ಥģʽ */
typedef enum tagTCPIP_PTP_CLOCK_CAST_MODE_E
{
    TCPIP_PTP_CLOCK_UNICAST_MODE,             /* ����ģʽ*/
    TCPIP_PTP_CLOCK_MULTICAST_MODE,           /* �ಥģʽ*/
    TCPIP_PTP_CLOCK_IEEE8023_MODE             /* OVER MACģʽ*/
} TCPIP_PTP_CLOCK_CAST_MODE_E;


/* ����Э��ö������ */
typedef enum tagTCPIP_PTP_PROTOCAL_TYPE_E
{
    TCPIP_PTP_PROTOCAL_UDP_IPV4 = 1,
    TCPIP_PTP_PROTOCAL_UDP_IPV6,
    TCPIP_PTP_PROTOCAL_IEEE_802
} TCPIP_PTP_PROTOCAL_TYPE_E;

#ifdef __cplusplus
}
#endif


#endif

