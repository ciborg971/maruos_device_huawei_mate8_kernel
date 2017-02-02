

#ifndef _ETHARP_HDR_H_
#define _ETHARP_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ETHARP��챨�����ݽṹ */

/* ARP���������Ϣ�ṹ */
typedef struct tagETHARP_HEALTH_ARPUPDATE
{
    TCPIP_TIME_S stUpdateTime;
    ULONG   ulIfIndex;
    ULONG   ulIpAddr;             /* ������ */ 
    UCHAR   ucMacAddr[MACADDRLEN];  
    UCHAR   ucResevred[2];
    
    ULONG   ulVrfIndex;
    
}ETHARP_HEALTH_ARPUPDATE_S;

/* ARP����ʧ����Ϣ�ṹ */
typedef struct tagETHARP_HEALTH_ARPRESOLVEFAIL
{
    ULONG   ulIfIndex;
    ULONG   ulIpAddr;
    TCPIP_TIME_S stUpdateTime;
}ETHARP_HEALTH_ARPRESOLVEFAIL_S;

typedef struct tagETHARP_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    ETHSTAT_S stEtharpStatistic;
}ETHARP_HEALTH_STATISTIC_S;

extern VOID ETHARP_Health_BatchCheckup();

extern ULONG ETHARP_Health_ArpCheckup();
extern ULONG ETHARP_Health_StatisticCheckUp();
extern ULONG ETHARP_Health_ArpResolveFailCheckUp();
extern ULONG ETHARP_Health_ProxyRelayCheckUp();
extern ULONG ETHARP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

