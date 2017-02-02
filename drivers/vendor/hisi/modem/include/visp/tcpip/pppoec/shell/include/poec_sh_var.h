

#ifndef  _POEC_SH_VAR_H_
#define  _POEC_SH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/*ȫ��PPPoE Client Discovery�׶ζ�ʱ��ID��������Session ��padi��padr����ʹ��*/
extern ULONG  g_ulPPPoEClientDisTimerID;

/*ȫ��IDLE Timer��ʱ��ʱ��ID */
extern ULONG  g_ulPPPoEClientIdleTimerID;

/*ȫ��PPPoE Clientģ��Session�ַ���*/
extern CHAR *g_PPPoESessionInfo[2];

/*ȫ��PPPoE Clientģ��Session ״̬�ַ���*/
extern CHAR *g_SessionState[]; 

extern CHAR g_cPppoeClientDebugBuf[];

extern CHAR *Inf_PPPOE_Client_En[];   /* Ӣ�İ�����Ϣ */

extern struct ComponentInfo m_PPPOE_CLIENT_CompInfo;  /* PPPOE�����Ϣ */

extern struct IIF_PPPOE_CLIENT_ComIntCFGVtbl   * g_pstPPPOEClientComCfgTable; /* PPPOE���ù����麯���� */
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl   * g_pstPPPOEClientComFunTable; /* PPPOE���ܺ������ */
extern struct IIF_PPPOE_CLIENT_ComIntSSAVtbl   * g_pstPPPOEClientComSsaTable; /* PPPOEϵͳ֧���麯���� */

extern APP_INIT_INFO_S g_stPPPoEClientAppInfo; 

#if __cplusplus
}
#endif

#endif

