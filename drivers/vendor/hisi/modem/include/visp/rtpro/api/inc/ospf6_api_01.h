/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf6_api_01.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2014-05-12
*        Author: guojianjun178934
*   Description: ���ļ�����OSPFV3ͨ��I3֪ͨ��Ʒ��صĶ���ṹ�嶨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-05-12   guojianjun178934        Create
*
*******************************************************************************/
#ifndef _OSPF6_API_01_H_
#define _OSPF6_API_01_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define OSPF6_MAX_INET_ADDR_LEN                 16         /*IPV6��ַ��󳤶�*/

/*STRUCT<IPV6��ַ�ṹ>*/
typedef struct tagINET6_ADDRESS
{
    UCHAR ucAddress[OSPF6_MAX_INET_ADDR_LEN];/*IPV6��ַ������Ϊ16�ֽ�*/
    UCHAR ucPrefixLen;                       /*���볤��,ȡֵ��Χ:0-128*/
    UCHAR ucPad[3];                          /*���*/
}INET6_ADDRESS_S;

/*Added by guojianjun178934, OSPFV3 �ھ��¼����ӿ��¼����ھ�״̬�澯, 2014/5/12   ���ⵥ��:S-IP-005-OSPFv3-005  */
/*�ӿ��¼��澯*/
typedef struct tagOSPF6_IF_EVENT_NOTIFY
{
  ULONG ulProcID; /*OSPF����ID*/
  ULONG ulLocalRouterID;  /*����router id*/
  ULONG ulAreaID; /*�ӿ������*/
  ULONG ulInstanceId; /*�ӿ�ʵ��ID*/
  ULONG ulIfIndex;  /*���ؽӿ�����*/
  UCHAR ucIfddr[OSPF6_MAX_INET_ADDR_LEN]; /*����ӿ�IP*/
  ULONG ulReason; /*�����¼�*/
  ULONG ulPrevState;  /*�ӿ�״̬��ת��ǰ��״̬*/
  ULONG ulNewState; /*�ӿ�״̬��ת����״̬*/
}OSPF6_IF_EVENT_NOTIFY_S;

/*�ھ��¼��澯*/
typedef struct tagOSPF6_NBR_EVNET_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF����*/
    ULONG ulProcID;            /*����ID*/ 
    ULONG ulLocalRouterID;    /*����route id*/
    ULONG ulAreaID;            /*����ID*/
    ULONG ulInstanceId;        /*�ӿ�ʵ��ID*/
    ULONG ulLocalIfIndex;      /*���ھӶ�Ӧ�ı��ؽӿ�����*/
    UCHAR ucIfddr[OSPF6_MAX_INET_ADDR_LEN]; /*�ھӶ�Ӧ�ӿڵĵ�ַ*/
    ULONG ulNbrRouterID;       /*�ھӵ�ַroute id*/
    UCHAR ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*�ھӶ�Ӧ�ӿڵĵ�ַ*/
    ULONG ulReason;            /*״̬�仯��ԭ��ֵ ����μ�ԭ��ֵ˵��*/
    ULONG ulPrevState;         /*ǰһ״̬ ����μ�״ֵ̬˵��*/
    ULONG ulNewState;          /*��״̬ ����μ�״ֵ̬˵��*/
}OSPF6_NBR_EVENT_NOTIFY_S;  /*�ھ�״̬֪ͨ�ṹ��*/

/*�ھ�״̬�澯*/
typedef struct tagOSPF6_NBR_STATE_NOTIFY
{
    ULONG ulVrfIndex;          /*VRF����*/
    ULONG ulProcID;            /*����ID*/
    ULONG ulLocalRouterID;    /*Router ID*/
    ULONG ulAreaID;            /*����ID*/ 
    ULONG ulInstanceId;        /*�ӿ�ʵ��ID*/
    ULONG ulLocalIfIndex;      /*���ھӶ�Ӧ�ı��ؽӿ�����*/
    ULONG ulNbrRouterID;       /*�ھ�Router ID*/
    UCHAR ucNbrAddr[OSPF6_MAX_INET_ADDR_LEN]; /*�ھӵ�ַ*/
    ULONG ulNbrReachable;      /*�ھ��Ƿ�ɴ��ʶ(0:�ھӲ��ɴ� 1:�ھӲ��ɴ�)*/
    ULONG ulReason;            /*״̬�仯��ԭ��ֵ,��ʱ�������� */
}OSPF6_NBR_STATE_NOTIFY_S;  /*�ھ�״̬֪ͨ�ṹ��*/
/* End of Added by guojianjun178934, 2014/5/12   ���ⵥ��:S-IP-005-OSPFv3-005  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

