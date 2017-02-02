
#ifndef _LLDP_VAR_H_
#define _LLDP_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif

extern LLDP_LOCAL_SYS_INFO_S    g_stLldpLocalSystemData;    /*�����豸ϵͳ��Ϣ*/
extern LLDP_LOCAL_SYS_STAT_S g_stLldpLocalSysStat;     /*ϵͳͳ����Ϣ*/
extern LLDP_LOCAL_PORT_S **g_stLldpLocalPortArray;       /*���ض˿ڱ�������LLDP_LOCAL_PORT_S*/
extern ULONG g_ulLldpLocalPortNum;      /*���ض˿�����*/
extern BOOL_T g_bLLDP_ShellInit;   /*LLDP�Ƿ��ʼ���ɹ�*/

extern ULONG  g_ulLldpRemmTotal;             /*ϵͳ�ھ�����*/


/* Global semaphore for LLDP */
extern ULONG g_ulSemForLldp ;

/*LLDPRUN���������ID����Ϣ����ID*/
extern ULONG ulLLDPTaskID;


extern ULONG txFastInit;
extern ULONG reinitDelay;
extern ULONG msgTxInterval;

extern ULONG g_ulLLDPControlQueID;
extern ULONG g_ulLLDPTimerQueID;
extern ULONG g_ulLLDPRcvQueID;
extern ULONG g_ulLLDPTransmitTimerQueID;

extern ULONG g_ulLLDPDebugSwitch;
extern ULONG g_ulLLDPDebugIfIndexFilter;
extern ULONG g_ulLLDPDebugMACTypeFilter;
extern ULONG g_ulLLDPRemIndex;

extern ULONG g_ulLLDPSendPktFilter;
extern ULONG g_ulLLDPReceivePktFilter;

extern ULONG g_ulLLDPLinkAggrTlvSwitch;    /*ֵΪ0, ѡ����802.1�еĹ涨; ֵ����0��ѡ����802.3�еĹ涨��*/

extern UCHAR g_lldp_szEthDMA[LLDP_MAX_MACTYPE_SIZE][LLDP_MAC_ADDR_LEN] ;

extern LLDP_REM_INFO_S  *g_pstLLDPWarningRemInfo;

extern ULONG g_ulLLDPAddPortMode;

extern LLDP_GETEXTTLV_HOOK_FUNC g_stLLDPGetExtTlv;

extern LLDP_INPUT_HOOK_FUNC g_stLLDPInputHook;

/* Global value for storing LLDP maximum supported interface*/
extern ULONG g_ulLldpMaxLocalPortNum;

/* Global value for storing LLDP maximum neighbour interface*/
extern ULONG g_ulLldpMaxNbrNum;

#ifdef  __cplusplus
}
#endif

#endif
