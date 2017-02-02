#ifndef __DHCPM_INTERFACE_H__
#define __DHCPM_INTERFACE_H__

/* deleted by w00316385 start */
#if 0
typedef struct tagDHCP_SERVER_STATUS_S
{
    PGP_SPINLOCK_ID stSpinLockId;

    UCHAR   ucPrimarySrvStatus:3;
    UCHAR   ucPrimarySrvTest:1;
    UCHAR   ucSecondarySrvStatus:3;
    UCHAR   ucSecondarySrvTest:1;
    UCHAR   ucPrimSrvTimerStatus;       /* ���÷�����״̬ɨ�趨ʱ��״̬ */
    UCHAR   ucPrimTimeoutNum;           /* �����������ϸ澯���� */
    UCHAR   ucSecTimeoutNum;            /* �����������ϸ澯���� */

    USHORT  usPrimTryTimeInterval;      /* ����������ΪTry��ʣ��ʱ�� */
    USHORT  usSecTryTimeInterval;       /* ����������ΪTry��ʣ��ʱ�� */

    UCHAR   ucPrimRequestTimeout;
    UCHAR   ucSecRequestTimeout;
    UCHAR   ucPrimaryAlarmFlag:1;       /* ���������Ѿ����͹���·�ϸ澯�ı�־ */
    UCHAR   ucSecondaryAlarmFlag:1;     /* �Ѿ����͹���·�ϸ澯�ı�־ */
    UCHAR   ucResBit:6;               /* �����ֶ� */
    UCHAR   ucReserve;            /* �����ֶ� */
}DHCP_SERVER_STATUS_S;
#endif
/* deleted by w00316385 end */

#define DHCPM_MAX_REQUEST_TIMEOUT_NUM 5

extern DHCP_SERVER_STATUS_S *g_pstDhcpServerStatus;

ULONG DHCPM_GetDhcpSrvCfgByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer);
ULONG DHCPM_GetDhcpSrvCfgStatusByIndex(ULONG ulDhcpIndex, LAP_DHCP_CFG_S *pstDhcpServer,
                                       DHCP_SERVER_STATUS_S *pstDhcpServerStatus);
ULONG inline DHCPM_SetPrimarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetPrimarySrvTestByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetSecondarySrvStatusByIndex(ULONG ulDhcpIndex, ULONG ulValue);
ULONG inline DHCPM_SetPrimSrvTimerStatusByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
ULONG inline DHCPM_SetPrimTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
ULONG inline DHCPM_SetSecTimeoutNumByIndex(ULONG ulDhcpIndex, UCHAR ucValue);
extern ULONG DHCPM_RegDhcpServer();
extern ULONG inline DHCPM_GetRetransmitCfgByIndex(ULONG ulDhcpIndex, UCHAR *pucRetransmitNum, UCHAR *pucRetransmitTimeOut);
extern ULONG inline DHCPM_TrySetPrimStatusAbnormalByIndex(ULONG ulDhcpIndex);
extern ULONG inline DHCPM_TrySetSecStatusAbnormalByIndex(ULONG ulDhcpIndex);
extern ULONG DHCPM_GetDhcpSrvStatusByIndex(ULONG ulDhcpIndex, DHCP_SERVER_STATUS_S *pstDhcpServerStatus);
#endif /* end of __DHCP_INC_H__ */
