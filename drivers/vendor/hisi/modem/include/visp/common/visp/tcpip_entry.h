

#ifndef _TCPIP_ENTRY_H_
#define _TCPIP_ENTRY_H_
#ifdef  __cplusplus
extern "C"{
#endif

#define TCPIP_UNREFERENCED_PARAMETER(P) { (P) = (P); }

/*--------------------------------*/
/* �����¼�λ:��ʱ���¼�          */
/*--------------------------------*/
#define VRP_EVENT_TIMERREQ          0X00008000

/*Added by zhukun*/ /*IPv6 Pmtu�������¼�*/
#define VRP_EVENT_PMTUREQ           0X00080000
#define VRP_EVENT_PMTUFLUSH         0X00100000

/* Prabhu Add Begin */

#define APP_NAME_MAX_LEN        15 
#define APP_TASK_NAME_LEN       7  
#define APP_TASK_PARA_NUM       4

typedef VOID  (*APP_TASK_ENTRY) (UINTPTR ulArg0, UINTPTR ulArg1, UINTPTR ulArg2, UINTPTR ulArg3);
typedef ULONG (*APP_INIT_FUNC)();
typedef VOID  (*APP_MIB_REG)();
typedef VOID  (*APP_IFNET_HOT_NOTIFY_CB)(ULONG ulEvent, ULONG ulSlot, VOID * pstIfnet, ULONG ulIfIndex);
typedef ULONG (*APP_CFA_CB)(VOID *, VOID **);


typedef struct tagAPP_INIT_INFO
{
    ULONG                   ulMID;                          /*MID*/
    UCHAR                   szAppName[APP_NAME_MAX_LEN + 1];    /*Application name, '\0' terminated */
    VOID                   *pstComponentInfo;

    APP_TASK_ENTRY          pfTaskEntry;                    /*Task entry, NULL for no own task*/
    UCHAR                   szTaskName[APP_TASK_NAME_LEN + 1];  /*Task name, zero terminated*/
    ULONG                   ulTaskPriority;                 /*Task priority*/   
    ULONG                   ulTaskMode;                     /*task mode*/
    ULONG                   ulTaskStackSize;                /*task stack size */
    UINTPTR                 ulTaskArg[APP_TASK_PARA_NUM];   /*task entry parameters*/

    APP_INIT_FUNC           pfAppInit;
    APP_MIB_REG             pfMibReg;                       /*register MIB*/
    APP_IFNET_HOT_NOTIFY_CB pfIfnetHotNotifyCB;
    APP_CFA_CB              pfCfaCB;                        /*config process func on IO board*/

    CHAR                  **ppcExecInfor_EN;                
    CHAR                  **ppcExecInfor_CN;                
    CHAR                  **ppcExecInfor_EXTD;              

    ULONG                   ulAppIndex;                     /*to store app id*/ 
    ULONG                   ulTaskId;                       /*to store the task ID*/
    ULONG                   ulExecInforIndex;               /*to store the execinfo index*/

}APP_INIT_INFO_S;

typedef struct tagTCPIP_PRECFG_VALUE
{
    ULONG ulKey;        /* Ԥ���ò���ID */
    ULONG ulCfg_Value;  /* ����ֵ */
    ULONG ulMin_Value;  /* ������ֵ������ */
    ULONG ulMax_Value;  /* ������ֵ������ */
}TCPIP_PRECFG_VALUE_S;

VOID TCPIP_InfoOutput(CHAR *pInfo);
#define TCPIP_printf TCPIP_InfoOutput

/* Prabhu Add End */


ULONG SYS_RegAppInfo(APP_INIT_INFO_S *);

extern ULONG        ulVRPTID_SOCK;      
extern ULONG        ulSOCKTmrQueID; 

ULONG TCPIP_IC_SendMsg(ULONG ulMId, ULONG ulInfoId, char *pBuf);

/****************************************************************************
* Prototype    : TCPIP_Set_PreConfigPara
* Description  : VISP Ԥ���ò������ú���
* Called by     : Ӧ��VISP�Ĳ�Ʒ
* Calls           : 
*----------------------------------------------------------------------------
* NOTICE       : Ӧ��VISPʱ�����ô˺�������VISPϵͳ������
* NOTICE       : ulKeyȡֵΪTCPIP_PRECONFIG_INFO_E�е�ö��ֵ��
* NOTICE       : ulValueȡֵ�ο�ulKey��Ӧ��ȡֵ˵����
*****************************************************************************/
ULONG TCPIP_Set_PreConfigPara(ULONG ulKey, ULONG ulValue);

/****************************************************************************
* Prototype    : TCPIP_Set_PreConfigPara
* Description  : VISP Ԥ���ò���ֵ��ȡ����
* Called by     : Ӧ��VISP�Ĳ�Ʒ
* Calls           : 
*----------------------------------------------------------------------------
* NOTICE       : Ӧ��VISPʱ�����ô˺�����ȡVISPϵͳ����Ĭ��ֵ��
* NOTICE       : ulKeyȡֵΪTCPIP_PRECONFIG_INFO_E�е�ö��ֵ��
* NOTICE       : ���ص�ulCfg_ValueΪVISPϵͳ����Ĭ��ֵ��
*****************************************************************************/
ULONG TCPIP_Get_PreConfigPara(TCPIP_PRECFG_VALUE_S *pstComPara);

/*Begin 2013-02-07 liangjicheng ����Linux Ĭ��ջ���� Ĭ��ֵ:8M ����DLC����Ƕ��*/

#define  LINUX_DEFAULTSTACKSIZE 1024*1024*8
#define  LINUX_MAXSTACKSIZE 1024*1024*16

/*End   2008-09-10 liangjicheng */

#ifdef  __cplusplus
}
#endif
#endif


