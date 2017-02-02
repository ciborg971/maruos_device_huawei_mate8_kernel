

#ifndef DIAGNOSE_API_H
#define DIAGNOSE_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef VOID
#define VOID void
#endif


#define MAX_STOP_ON_ASSERTS 10  /* ֹͣ�������Ķ��Դ��������ֵ */

#define MIN_MEMORY_VERIFY_FREQUENCY 1   /* �ڴ���֤Ƶ�ʵ���Сֵ */
#define MAX_MEMORY_VERIFY_FREQUENCY 10  /* �ڴ���֤Ƶ�ʵ����ֵ */

/* output infomation type */
#define NBB_TEXT    1
#define NBB_BINARY  2

/* diagnose ���������� */
typedef enum tagDIAG_ERROR_E
{
    DIAG_OK,                     /*0��������*/
    DIAG_ERR = MID_COMP_DIAGNOSE + 1,                    /*1���ܴ���,�����ڲ���������ֵ*/
    DIAG_ERR_NULL_PTR,          /* ��ָ�� */
    DIAG_ERR_CFG_FLAG_INVALID,      /*����ı�־:��������Ҳ����ȡ��*/
    DIAG_ERR_PRAR_INVALID,      /*��������:������Χ*/  
    DIAG_ERR_WRONGFORMAT,            /* ����Ĳ�����ʽ */
    DIAG_ERR_MUST_SET_BEFORE_DCL_INIT,   /* �ò���Ӧ����DCL����ǰ���� */
    DIAG_ERR_MUST_SET_AFTER_DCL_INIT,   /* �ò���Ӧ����DCL���������� */
    DIAG_ERR_NEEDENABLEIPSTRACE,     /* ʹ��EventTrace��TimerTrace����ͬʱʹ��IpsTrace */
    DIAG_ERR_MALLOCBUFFERFAIL,      /* �����ڴ�ʧ�� */
    DIAG_ERR_SUPPORT_DEBUG_ONLY,    /* ֻ֧��debug�汾 */
    DIAG_ERR_EXCEED_MAX_LENGTH,     /*������󳤶�*/
    DIAG_ERR_EXCEED_MAX_NUM_LOG,    /*�������stop��־����:10*/
    DIAG_ERR_SIZE_TOO_SMALL,       /*���������Ϣ�����size̫С*/
    DIAG_ERR_INVALID_LOGLEVEL,     /*�������־�ȼ�*/
    DIAG_ERR_INVALID_LOG_DETAIL_TYPE, /*�������ϸ��־����*/
    DIAG_ERR_MAXCODE = MID_COMP_DIAGNOSE + 255             /*��������,����´�����ʱ,ֱ����ӵ�����*/
}DIAG_ERROR_E;


/* diagnose ���Դ���ʽ */
enum eDIAGASSERTACTION
{
    DIAG_ASSERT_ASSERT = 1,     /* ��ʾ�����ֶ���ʱ���˶��Խ���C���Ժ���������Win32ϵͳ�У���ᵼ��C���п���ʾһ��
                                �Ի��򲢵���JIT����������ѡ������UNIXϵͳ�лᵼ���ں�ת�� */              
    DIAG_ASSERT_EXIT,           /* ��ʾ�����ֶ���ʱ�Ὣ���Դ��͸���׼����������˳����� */   
    DIAG_ASSERT_TRAP,           /* ��Win32ϵͳ�л����JIT���������ǲ���ʾC���п�Ի��� */
    DIAG_ASSERT_CONTINUE,       /* ��ʾ�����ֶ���ʱ�Ὣ���Դ��͸���׼�����ʹ�������ִ�� */  
};

/* diagnose ��־���� */
enum eDIAGLOGLEVEL
{
    DIAG_LOG_LEVEL_NONE = 0,  
    DIAG_LOG_LEVEL_PROBLEM,     
    DIAG_LOG_LEVEL_EXCEPTION,   
    DIAG_LOG_LEVEL_AUDIT,
};

/* diagnose ��ϸ��ժҪ��־ */
enum eDIAGLOGDETAIL
{
    DIAG_LOG_DETAIL_SUMMARY = 1,    /* ժҪ��־ */
    DIAG_LOG_DETAIL_FULL,           /* ��ϸ��־ */
};

/* diagnose ��ϸ��ժҪ��־ */
enum eDIAGENABLE
{
    DIAG_DISABLE = 0,       /* ȥʹ�� */
    DIAG_ENABLE,            /* ʹ�� */
};

/* diagnose Trace ���� */
enum eDIAGTRACE
{
    DIAG_TRACE_ENTRY_POINT      = 0,    /* ������� */       
    DIAG_TRACE_ENTRY_EXIT       = 1,    /* �����˳��� */
    DIAG_TRACE_DETAIL           = 2,    /* ϸ�� */
    DIAG_TRACE_FLOW             = 4,    /* ���� */
    DIAG_TRACE_INTERFACE        = 6,    /* �ӿ� */
    DIAG_TRACE_STATISTICS       = 8,    /* ͳ�� */
    DIAG_TRACE_NO_TRC           = 10,   /* ����TRACE */
};

#define DIAG_TRACE_DEFAULT_LEVEL  DIAG_TRACE_NO_TRC /* Ĭ��TRACE���� */

/* diagnose flush type */
enum eDIAGFLUSHTYPE
{
    DIAG_FLUSH_ALL,     /* ת��������Ϣ */
    DIAG_FLUSH_TRACE,   /* ת��TRACE��Ϣ */
    DIAG_FLUSH_IPS,     /* ת��IPS��Ϣ */
    DIAG_FLUSH_PD,      /* ת����־��Ϣ */
};

enum eDIAGOUTPUTTYPE
{
    DIAG_OUTPUT_TRACE,  /* trace information */
    DIAG_OUTPUT_IPS,    /* IPS information */
    DIAG_OUTPUT_PD,     /* log information */
    DIAG_OUTPUT_DMP,    /* dump information */
    DIAG_OUTPUT_PER,    /* performance information */
    DIAG_OUTPUT_MEM,    /* memory information */
    DIAG_OUTPUT_IPS_MON,/* ips monitor */
    DIAG_OUTPUT_PD_MON, /* pd monitor */
    DIAG_OUTPUT_MT_PER, /* performance information in mutilthread*/
};

typedef VOID (*TCPIP_PROT_DIAGNOSTICS_HOOK_FUNC)
    (ULONG ulType, ULONG ulTextOrBinary, ULONG ulLength, CHAR* pszOutputInfo);

extern ULONG TCPIP_SetProtAssert(ULONG ulAssertDlg, ULONG ulDumpOnAssert);
extern ULONG TCPIP_SetProtBufSize(ULONG ulTrace, ULONG ulIps, ULONG ulPd);
extern ULONG TCPIP_SetProtDiagnosticsStop(CHAR* pszStopLogs, ULONG ulStopOnAsserts);
extern ULONG TCPIP_SetProtIpsFilterProcess(CHAR* pszFilterInProc, CHAR* pszFilterOutProc);
extern ULONG TCPIP_SetProtIpsFilterType(CHAR* pszFilterInType, CHAR* pszFilterOutType);
extern ULONG TCPIP_SetProtIpsTrace(ULONG ulIpsTrace, ULONG ulEventTrace, ULONG ulTimerTrace);
extern ULONG TCPIP_SetProtLog(ULONG ulLogLevel, ULONG ulDetail, ULONG ulDev, ULONG ulVerbose);
extern ULONG TCPIP_SetProtLogFilterMsgId(CHAR* pszFilterInMsgId, CHAR* pszFilterOutMsgId);
extern ULONG TCPIP_SetProtLogFilterProcess(CHAR* pszFilterInProc, CHAR* pszFilterOutProc);
extern ULONG TCPIP_SetProtMemoryCheck(ULONG ulCheck);
extern ULONG TCPIP_SetProtMemoryVerify(ULONG ulVerify, ULONG ulFrequency);
extern ULONG TCPIP_SetProtTraceFilterFile(CHAR* pszFilterInFile, CHAR* pszFilterOutFile);
extern ULONG TCPIP_SetProtTraceFilterFunc(CHAR* pszFilterInFunc, CHAR* pszFilterOutFunc);
extern ULONG TCPIP_SetProtTraceLevel(ULONG ulTraceLevel);
extern ULONG TCPIP_SetProtVerifyTraceLevel(ULONG ulTraceLevel);
extern ULONG TCPIP_FlushMemoryBuffer(ULONG ulType);
extern ULONG TCPIP_RegFuncDiagnosticsOutputHook(TCPIP_PROT_DIAGNOSTICS_HOOK_FUNC pfHookFunc);
extern VOID TCPIP_ShowDiagnosticsPara(VOID);
extern VOID TCPIP_ShowProtMemoryUsage(VOID);
extern VOID TCPIP_ShowProtMemoryTuning(ULONG ulCommonLen);

#ifdef  __cplusplus
}
#endif

#endif
