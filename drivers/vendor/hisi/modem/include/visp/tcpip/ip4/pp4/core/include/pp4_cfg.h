/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_cfg.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: PP4_cfg.Cͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         �淶������
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_CFG_H_
#define _PP4_CFG_H_


/***************************************************************
 *        ���������Ϣ����                                     *
 ***************************************************************/
#define IP_DEBUG_ON                 0x0001
#define IP_DEBUG_OFF                0x0000


#define IP_NO_ACL                   0
/* Modify End */

/* IPͳ����Ϣ��ʾ��� */
#define IP_SHOW_TRAFFIC_ALL         0
#define IP_SHOW_TRAFFIC_MAIN        1
#define IP_SHOW_TRAFFIC_IO          2

/* ���ͳ����Ϣ��� */
#define IP_CLEAR_COUNTERS_ALL       0
#define IP_CLEAR_COUNTERS_MAIN      1
#define IP_CLEAR_COUNTERS_IO        2
#define IP_CLEAR_COUNTERS_INTERFACE 3

extern ULONG ulDebugIpPacketFlag;   /* IP���Ŀ��� */
extern ULONG ulDebugIpPacketErrFlag;/* IP���Ĵ�����Ϣ���� */
extern ULONG ulDebugIpDebugInfo;    /* IP���ĵ�����Ϣ���� */

extern ULONG g_ulDubugIpAcl;       /* ��׼ACL������ţ����ڹ��˵�����Ϣ */
extern ULONG g_ulDubugIpIfAcl;     /* ���ڽӿڵ�ACL������ţ����ڹ��˵�����Ϣ */
extern ULONG g_ulDebugIpIfOpt;     /* ���ڽӿڵ�ACL������˷����ݲ�ʵ��in|out interface, �����Ժ���չ */

extern UCHAR g_ucbIpSendRedirects; /* �����ض����Ŀ��� */
extern UCHAR g_ucbIpForwarding;    /* IP����ת������ */
extern LONG  nIpDefTTL ;           /* Ĭ��TTL */

extern ULONG g_ulIpDebugFilter[IP_DEBUG_FILTER_MAX];

extern ULONG IP_PP4_GetStatics(IPSTAT_S* pstIpStat);
extern VOID IP_PP4_ClearIpCounters( ULONG  ulSlotNumber );

extern ULONG IP_PP4_GetDebugFlag(ULONG *pulDebugFlag,
                                 ULONG *pulDebugIpAcl,
                                 ULONG *pulDebugIpIfAcl,
                                 ULONG *pulDebugIpIfOpt,
                                 ULONG *pulDebugIpErr,
                                 ULONG *ulDebugPacketVerbose);
extern ULONG IP_PP4_SetDebugFlag(ULONG ulIpDebugNo, 
                                 ULONG ulDebugAcl,
                                 ULONG ulDebugIfAcl,
                                 ULONG ulDebugIfOpt, 
                                 ULONG ulDebugIpErr, 
                                 ULONG ulDebugPacketVerbose);

ULONG IP_PP4_SetForwardFlag(ULONG ulFlag);
ULONG IP_PP4_GetForwardFlag();
ULONG IP_PP4_SetDefaultTTL(ULONG ulTtl);
ULONG IP_PP4_GetDefaultTTL();
/*Add by Zhangchunyu(62474) for A82D12543, 2007-03-13*/
ULONG IP_PP4_GetInterfaceStatics(ULONG ulIfIndex, IPIFSTAT_S * pIpif_stData);
ULONG IP_PP4_ClearInterfaceStatics(ULONG ulIfIndex);

VOID IP_PP4_ClearIpInterface( IPIFNET_S *  pstIpIf);
/* Added by Sunmo(44939) for A82D01805, 2006-05-31 */
ULONG IP_ICMP_RedirectsFunc(IFNET_S * pIf, ULONG ulFlag);
ULONG IP_ICMP_HostUnreachFunc(IFNET_S * pIf, ULONG ulFlag);
/*·�ɱ仯��ջ���ӿ�*/
extern ULONG IP_ClearRouteCache(VOID);
extern ULONG IP_SetIpDebugFilter(ULONG ulSetYes, ULONG ulIfIndex, CHAR *szSrcIp, CHAR *szDstIp,
    ULONG ulProtocol, ULONG ulSrcPort, ULONG ulDstPort);
extern ULONG IP_GetIpDebugFilter(ULONG *pulDebugFlag, ULONG *pulDebugFilter);
extern ULONG IP_PP4_GetInterfaceStaticsByIfNum(IPIFSTAT_LIST_S *pIpif_stData, ULONG ulIfNum);

#endif  /* _PP4_CFG_H_  */

#ifdef  __cplusplus
}
#endif


