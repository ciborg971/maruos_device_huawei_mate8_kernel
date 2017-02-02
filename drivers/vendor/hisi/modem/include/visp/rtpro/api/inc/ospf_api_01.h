/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_01.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2013-09-13
*        Author: guojianjun178934
*   Description: ���ļ�����OSPFͨ��I3֪ͨ��Ʒ��صĶ���ṹ�嶨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-09-13   guojianjun178934        Create
*
*******************************************************************************/
#ifndef _OSPF_API_01_H_
#define _OSPF_API_01_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define OSPF_CLASH_ROUTER_MAX   5   /* 2-LSA��ͻ�����·������(����·��������)*/

#define OSPF_ROUTE_CALCULATE_SUCCESS   1    /*·�ɼ���ɹ�*/
#define OSPF_ROUTE_CALCULATE_FAILURE    2    /*·�ɼ���ʧ��*/

typedef struct tagOSPF_NETWORK_LSA_CLASH_WARNING_S
{
    ULONG ulProcessID;
    ULONG ulAreaID;
    ULONG ulClashIPAddr;
    ULONG ulClashRouterCount;
    ULONG szClashRouterID[OSPF_CLASH_ROUTER_MAX];
}OSPF_NETWORK_LSA_CLASH_WARNING_S;

/*·�ɼ�������֪ͨ*/
typedef struct tagOSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY
{
    ULONG ulProcessID;                   /* ����ID */
    ULONG ulCalcResult;                 /*·�ɼ�����*/
    ULONG ulAreaID;                     /* ����ID */
    ULONG ulRouterLSACount;             /*��ǰ����Router LSA����*/
    ULONG ulNetworkLSACount;           /* ��ǰ����Network LSA����*/
}OSPF_ROUTE_CALCULATE_THRESHOLD_NOTIFY;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
