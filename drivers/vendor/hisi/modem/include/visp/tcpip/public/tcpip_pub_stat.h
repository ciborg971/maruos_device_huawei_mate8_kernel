
#ifndef _TCPIP_PUB_STAT_H_
#define _TCPIP_PUB_STAT_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/tcp4/include/tcp_api.h"
#include "tcpip/ip4/am4/include/am4_api.h"
#include "tcpip/ip4/pp4/include/pp4_api.h"
#include "tcpip/dhcp4c/include/dhcp4c_api.h"
#include "tcpip/ptp/include/ptp_cbb_api.h"
#include "tcpip/synce/include/synce_api.h"
#include "tcpip/etharp/include/etharp_api.h"

#define MAX_TCP_SOCK_INFO_NUM   16
#define MAX_IPIF_STAT_NUM       12
#define MAX_PTP_SLAVE_STAT_NUM  2
#define MAX_SYNCE_PDUSTAT_NUM   2
#define MAX_ETHSTAT_NUM         3

/*��־��ħ����*/
#define PUB_STAT_MAGIC_NUM      0x1A3B5C7D

typedef struct tagTCPIPDataStat
{
    TCPSTAT_S stTcpStat;                                /*TCP ȫ��ͳ��                        */
    ULONG   ulMagicNumber0;                             /*ħ���֣����ڼ����־�Ƿ���룬��ͬ  */
    TCP_SOCK_INFO_S stTcpConStat[MAX_TCP_SOCK_INFO_NUM];/*���socket��TCPͳ��                 */
    ULONG   ulMagicNumber1;
    IPSTAT_S stGloalIpStat;                             /*ȫ��IPͳ����Ϣ                      */    
    ULONG   ulMagicNumber2;
    IPIFSTAT_LIST_S stIpIfStatList[MAX_IPIF_STAT_NUM];  /*���ڽӿڵ�IPͳ��,MP����·������ͳ�� */    
    ULONG   ulMagicNumber3;
    DHCP4C_STATISTIC_S stDhcpStat;                      /*DHCP����ͳ��                        */
    ULONG   ulMagicNumber4;
    PTP_SLAVE_STAT_LIST_S stPtpStatList[MAX_PTP_SLAVE_STAT_NUM];/*1588����ͳ��                */
    ULONG   ulMagicNumber5;
    SYNCE_PDUSTAT_LIST_S stSynceStatList[MAX_SYNCE_PDUSTAT_NUM];/*ֻ��¼eth�ӿ�               */
    ULONG   ulMagicNumber6;
    ETHSTAT_LIST_S stEthStatList[MAX_ETHSTAT_NUM];      /*ֻ��¼eth�ӿ�                       */
    ULONG   ulMagicNumber7;
} TCPIP_DATA_STAT_S;

/* ��ȡPTPͳ�ƻص� */
typedef ULONG (*PTP_PUBGET_STAT_FUNC)(PTP_SLAVE_STAT_LIST_S *pstStatList, ULONG ulListSize);
extern ULONG TCPIP_GetAllDataStats(TCPIP_DATA_STAT_S *pstIPAllData);

/*********************************ȫ�ֱ�������********************************/

#ifdef  __cplusplus
}
#endif

#endif

