

#ifndef _SFE_DEBUG_API_H_
#define _SFE_DEBUG_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif


/* ������ά��ģ������붨�� */
typedef enum enumSfeDebugErrCode
{
    SFE_DEBUG_OK = SFE_OK,                          /* �����ɹ� */
    SFE_DEBUG_ERR_BEGIN = SFE_DEBUG_BEGIN_RET_CODE, /* ģ���������ʼֵ,�����ڲ���Ҫʹ�ø�ֵ */
    SFE_DEBUG_ALREADY_INIT_REGLOG,                  /* 1  ע����־�������ʱϵͳ�Ѿ���ʼ�� */
    SFE_DEBUG_ALREADY_INIT_REGDEBUG,                /* 2  ע������������ʱϵͳ�Ѿ���ʼ�� */
    SFE_DEBUG_ALREADY_INIT_REGINFO,                 /* 3  ע����Ϣ�������ʱϵͳ�Ѿ���ʼ�� */
    SFE_DEBUG_ALREADY_INIT_REGWARNING,              /* 4  ע��澯�������ʱϵͳ�Ѿ���ʼ�� */
    SFE_DEBUG_NULL_POINTER_REGLOG,                  /* 5  ע����־�������ʱ�����ָ�� */
    SFE_DEBUG_FUNC_NULL_POINTER_REGLOG,             /* 6  ע����־�������ʱ�����ע�ắ��Ϊ��ָ�� */
    SFE_DEBUG_NULL_POINTER_REGDEBUG,                /* 7  ע������������ʱ�����ָ�� */
    SFE_DEBUG_NULL_POINTER_REGINFO,                 /* 8  ע����Ϣ�������ʱ�����ָ�� */
    SFE_DEBUG_NULL_POINTER_REGWARNING,              /* 9  ע��澯�������ʱ�����ָ�� */
    SFE_DEBUG_NULL_POINTER_GETLOGLEVEL,             /* 10 ��ȡ��־����ʱ�����ָ�� */
    SFE_DEBUG_NULL_POINTER_GETLOGTYPE,              /* 11 ��ȡ��־����ʱ�����ָ�� */
    SFE_DEBUG_NULL_POINTER_GETDEBUGSWITCH,          /* 12 ��ȡ���Կ���ʱ�����ָ�� */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETLOGLEVEL,    /* 13 ������־����ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GETLOGLEVEL,    /* 14 ��ȡ��־����ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETLOGTYPE,     /* 15 ������־����ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GETLOGTYPE,     /* 16 ��ȡ��־����ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGTYPE,   /* 17 ���õ������Ϳ���ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGVCPU,   /* 18 ���õ���VCPU����ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_SETDEBUGMODULE, /* 19 ���õ���ģ�鿪��ʱ�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_TYPE_GETDEBUG,  /* 20 ��ȡ���Կ���ʱ�������Ϳ��ع������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_VCPU_GETDEBUG,  /* 21 ��ȡ���Կ���ʱ����VCPU���ع������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_MODULE_GETDEBUG,/* 22 ��ȡ���Կ���ʱ����ģ�鿪�ع������ָ��ΪNULL */
    SFE_DEBUG_MALLOC_FAIL_OUTPUTTOCOM,              /* 23 ��ʼ��ʱ���������com�ڹ�������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_LOGLEVEL,                 /* 24 ��ʼ��ʱ������־����������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_LOGTYPE,                  /* 25 ��ʼ��ʱ������־���͹�������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_MANUALSTAT,               /* 26 ��ʼ��ʱ�����ֶ�ͳ�ƹ�������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_AUTOSTAT,                 /* 27 ��ʼ��ʱ�����Զ�ͳ�ƹ�������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGTYPE,                /* 28 ��ʼ��ʱ����������͹�������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGVCPU,                /* 29 ��ʼ��ʱ�������VCPU��������ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGMODULE,              /* 30 ��ʼ��ʱ�������ģ�鹲������ռ�ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_LOGLEVEL,                  /* 31 ��ʼ��ʱ����־����������������ֿ�ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_LOGTYPE,                   /* 32 ��ʼ��ʱ����־���͹�������������ֿ�ʧ�� */
    SFE_DEBUG_LEVEL_INVALID_SETLOGLEVEL,            /* 33 ������־����ʱ��־���𲻺Ϸ� */
    SFE_DEBUG_PARA_INVALID_SETLOGTYPE,              /* 34 ������־����ʱ�������Ϸ� */
    SFE_DEBUG_GET_MAX_FLOW_NUM_PRECFG_FAIL,         /* 35 ��ʼ��ʱ��ȡ��ͳ�Ƹ���Ԥ���ù��ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_FLOWSTATINFO,             /* 36 ��ʼ��ʱ������ͳ����Ϣ�ռ�ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_FLOWSTATINFO,              /* 37 ��ʼ��ʱ����ͳ����Ϣ�ռ�����������ֿ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_FLOWSTATRULE,             /* 38 ��ʼ��ʱ������ͳ�ƹ���ռ�ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_FLOWSTATRULE,              /* 39 ��ʼ��ʱ����ͳ�ƹ���ռ�����������ֿ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_MANUALFLOWSTAT,           /* 40 ��ʼ��ʱ������ͳ���ֶ�ͳ����ռ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_AUTOFLOWSTAT,             /* 41 ��ʼ��ʱ������ͳ���Զ�ͳ����ռ�ʧ�� */

    SFE_DEBUG_NULL_POINTER_GET_STATALLINFO,         /* 42 ��ȡȫ��ͳ�������Ϣʱ,�������ָ��ΪNULL */

    SFE_DEBUG_INPUT_PARA_NULL_CFG_FLOWSTATISTIC,    /* 43 ����������ʱ,�������ΪNULL */
    SFE_DEBUG_VCPU_NOT_INIT_CFG_FLOWSTATISTIC,      /* 44 ����������ʱ,����VCPUû�г�ʼ�� */
    SFE_DEBUG_VRF_INVALID_CFG_FLOWSTATISTIC,        /* 45 ����������ʱ,VRF�����Ƿ� */
    SFE_DEBUG_PRONO_INVALID_CFG_FLOWSTATISTIC,      /* 46 ����������ʱ,Э��Ų����Ƿ� */
    SFE_DEBUG_OPERTYPE_INVALID_CFG_FLOWSTATISTIC,   /* 47 ����������ʱ,�������ͷǷ� */
    SFE_DEBUG_SHAREVAR_NULL_ADD_FLOWSTATISTIC,      /* 48 ���������ʱ,�˼乲�����ָ��ΪNULL */
    SFE_DEBUG_REACHED_MAXNUM_ADD_FLOWSTATISTIC,     /* 49 ���������ʱ,��ǰ�������Ѵﵽ���ֵ */
    SFE_DEBUG_NO_FREENODE_ADD_FLOWSTATISTIC,        /* 50 ���������ʱ,�����ڿռ��������ռ� */
    SFE_DEBUG_FLOWID_INVALID_ADD_FLOWSTATISTIC,     /* 51 ���������ʱ,������ռ��е���ID������������ID */
    SFE_DEBUG_SHAREVAR_NULL_DEL_FLOWSTATISTIC,      /* 52 ɾ��������ʱ,�˼乲�����ָ��ΪNULL */
    SFE_DEBUG_NO_RULE_DEL_FLOWSTATISTIC,            /* 53 ɾ��������ʱ,��ǰ������������,������Ϊ0 */
    SFE_DEBUG_NO_SAMERULE_DEL_FLOWSTATISTIC,        /* 54 ɾ��������ʱ,�й��򵫴�ɾ���Ĺ��򲻴��� */
    SFE_DEBUG_SHAREVAR_NULL_DELALL_FLOWSTATISTIC,   /* 55 ɾ������������ʱ,�˼乲�����ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_SET_FLOWSTATSWITCH,     /* 56 ������ͳ�ƿ���ʱ,�˼乲�����ָ��ΪNULL */
    SFE_DEBUG_SWITCH_INVALID_SET_FLOWSTATSWITCH,    /* 57 ������ͳ�ƿ���ʱ,����ֵ���Ϸ� */
    SFE_DEBUG_SHAREVAR_NULL_GET_FLOWSTATSWITCH,     /* 58 ��ȡ��ͳ�ƿ���ʱ,�˼乲�����ΪNULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATSWITCH,      /* 59 ��ȡ��ͳ�ƿ���ʱ,�������ָ��ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_GET_FLOWSTATRULENUM,    /* 60 ��ȡ��ͳ�ƹ�����ʱ,�˼乲�����ΪNULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATRULENUM,     /* 61 ��ȡ��ͳ�ƹ�����ʱ,�������ָ��ΪNULL */
    SFE_DEBUG_NULL_POINTER_GET_FLOWSTATALLINFO,     /* 62 ��ȡ��ͳ�������Ϣʱ,�������ָ��ΪNULL */

    SFE_DEBUG_FLOWSTAT_6KEY_MATCHFLOW_EXCEEDMAX,    /* 63 ��ͳ����Ԫ��ƥ��ʱ,ƥ��������������ֵ */
    SFE_DEBUG_FLOWSTAT_4KEY_MATCHFLOW_EXCEEDMAX,    /* 64 ��ͳ����Ԫ��ƥ��ʱ,ƥ��������������ֵ */

    SFE_DEBUG_MALLOC_FAIL_DEBUGCNT,                 /* 65 ��ʼ��ʱ������ϸ���Ա��ĸ����������ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_DEBUGCNT,                  /* 66 ��ʼ��ʱ����ϸ���Ա��ĸ�����������������ֿ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGCURCNT,              /* 67 ��ʼ��ʱ������ϸ���Եĵ�ǰ�����������ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGLEN,                 /* 68 ��ʼ��ʱ������ϸ���Ա��ĳ��ȹ������ʧ�� */
    SFE_DEBUG_ADD_NAMEDB_DEBUGLEN,                  /* 69 ��ʼ��ʱ����ϸ���Ա��ĳ��ȹ�������������ֿ�ʧ�� */
    SFE_DEBUG_MALLOC_FAIL_DEBUGSWITCH,              /* 70 ��ʼ��ʱ������Ϣ���¼��������ʧ�� */
    SFE_DEBUG_SHARE_NULL_POINTER_SETMSGDEBUG,       /* 71 ������Ϣ��EVENT�������ָ��ΪNULL */
    SFE_DEBUG_SHARE_PARA_ERR_SETMSGDEBUG,           /* 72 ������Ϣ���¼����Կ���,�������� */
    SFE_DEBUG_SHARE_NULL_POINTER_GETMSGDEBUG,       /* 73 ��ȡ��Ϣ��EVENT�������ָ��ΪNULL */
    SFE_DEBUG_SHARE_PARA_ERR_GETMSGDEBUG,           /* 74 ��ȡ��Ϣ���¼����Կ���,�������� */
    SFE_DEBUG_CNTSHARE_NULL_POINTER_SETVERBOSEDBG,  /* 75 ������ϸ���Եı��Ĵ����ͱ��ĳ���ʱ�������ΪNULL */
    SFE_DEBUG_LENSHARE_NULL_POINTER_SETVERBOSEDBG,  /* 76 ������ϸ���Եı��Ĵ����ͱ��ĳ���ʱ�������ΪNULL */
    SFE_DEBUG_NULL_POINT_GETVERBOSEDEBUG,           /* 77 ��ȡ������Ĵ����ͱ��ĳ���ʱ,ָ��ΪNULL */
    SFE_DEBUG_CNTSHARE_NULL_POINTER_GETVERBOSEDBG,  /* 78 ��ȡ��ϸ���Եı��Ĵ����ͱ��ĳ���ʱ�������ΪNULL */
    SFE_DEBUG_LENSHARE_NULL_POINTER_GETVERBOSEDBG,  /* 79 ��ȡ��ϸ���Եı��Ĵ����ͱ��ĳ���ʱ�������ΪNULL */
    SFE_DEBUG_DEBUGTYPE_SWITCH_INVALID,             /* 80 ���õ������Ϳ���ʱ,�������Ϳ���ֵ���Ϸ� */
    SFE_DEBUG_MANUAL_SHAREVAR_NULL_CLEARALLSTAT,    /* 81 �������ȫ��ͳ����Ϣʱ,ȫ���ֶ�ͳ�ƹ������ΪNULL */
    SFE_DEBUG_AUTO_SHAREVAR_NULL_CLEARALLSTAT,      /* 82 �������ȫ��ͳ����Ϣʱ,ȫ���Զ�ͳ�ƹ������ΪNULL */
    SFE_DEBUG_MANUAL_SHAREVAR_NULL_CLEARALLFLOWSTAT,/* 83 ���������ͳ����Ϣʱ,�ֶ���ͳ�ƹ������ΪNULL */
    SFE_DEBUG_AUTO_SHAREVAR_NULL_CLEARALLFLOWSTAT,  /* 84 ���������ͳ����Ϣʱ,�Զ���ͳ�ƹ������ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_CLR_ALLTCPSTAT, /* 85 ������к��ϵ�TCPͳ��ʱ,�˼乲�����ΪNULL */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_GET_TCPSTAT,    /* 86 ��ȡTCPͳ��ʱ,�˼乲�����ΪNULL */
    SFE_DEBUG_NULL_POINTER_GET_TCPSTAT,             /* 87 ��ȡTCPͳ����Ϣʱ,�������ָ��ΪNULL */
    SFE_DEBUG_GET_TCPSTAT_VCPU_INVALID,             /* 88 ��ȡTCPͳ����Ϣʱ,�����VCPU ID�������Ϸ� */
    SFE_DEBUG_SHAREVAR_NULL_POINTER_CLR_TCPSTAT,    /* 89 ���TCPͳ��ʱ,�˼乲�����ΪNULL */
    SFE_DEBUG_CLR_TCPSTAT_VCPU_INVALID,             /* 90 ���TCPͳ����Ϣʱ,�����VCPU ID�������Ϸ� */


}SFE_DEBUG_ERR_CODE_E;

/* �쳣������Ϣ���λ���� */
#define SFE_DEBUG_TYPE_ERROR        0x0001
/* ��ڳ��ڵ�����Ϣ���λ���� */
#define SFE_DEBUG_TYPE_INOUT        0x0002
/* ��Ҫ�������̵�����Ϣ���λ���� */
#define SFE_DEBUG_TYPE_PROC         0x0004
/* ��ϸ������Ϣ���λ����*/
#define SFE_DEBUG_TYPE_VERBOSE      0x0008

/* ��־����:�澯������־λ */
#define SFE_LOG_TYPE_WARNING        0x0001
/* ��־����:����������־λ */
#define SFE_LOG_TYPE_CFG            0x0002
/* ��־����:����������־λ */
#define SFE_LOG_TYPE_RUN            0x0004

/* ��־����ĵȼ� */
typedef enum SFE_LOG_LEVEL_Etag
{
    SFE_LOG_LEVEL_CRITICAL = 0, /* ���ؼ��� */
    SFE_LOG_LEVEL_ERROR,        /* ���󼶱� */
    SFE_LOG_LEVEL_WARNING,      /* �澯���� */
    SFE_LOG_LEVEL_INFO,         /* ��Ϣ���� */
    SFE_LOG_LEVEL_DEBUG,        /* ���Լ��� */
    SFE_LOG_LEVEL_END,          /* ������Ч�߽�ֵ */
}SFE_LOG_LEVEL_E;

/* �澯���� */
typedef enum SFE_WARNING_TYPE_Etag
{
    SFE_WARNING_TYPE_EVENT = 0, /* �¼����͸澯 */
    SFE_WARNING_TYPE_OPERATION, /* �������͸澯 */
    SFE_WARNING_TYPE_END,       /* �澯������Ч�߽�ֵ */
}SFE_WARNING_TYPE_E;

/* �澯ID */
typedef enum SFE_WARNING_ID_Etag
{
    SFE_WARNING_ID_DRV_RCVQUE_STATE = 0,    /* �������ձ��Ķ��е�ǰ״̬(������)�澯 */
    SFE_WARNING_ID_DRV_IFSTATE,             /* �����ӿ�UP/DOWN�仯�澯 */
    SFE_WARNING_ID_SOCK_RCVBUF_FULL,        /* socket���ջ��������澯 */

    SFE_WARNING_ID_END,       /* �澯������Ч�߽�ֵ */
}SFE_WARNING_ID_E;

/* �������Ľ��ն���״̬Ϊ,��ǰ���ձ��Ķ����еı�����С�ڵ����û��趨�ĸ澯����ֵ */
#define SFE_DRV_RCVQUESTATE_LOWTHAN_LOWLIMIT      0
/* �������Ľ��ն���״̬Ϊ,��ǰ���ձ��Ķ����еı��������ڵ����û��趨�ĸ澯����ֵ */
#define SFE_DRV_RCVQUESTATE_EXCEED_UPLIMIT        1
/* �������Ľ��ն���״̬Ϊ,�������ձ��Ķ���������ʼ�����澯 */
#define SFE_DRV_RCVQUESTATE_FULL_DROPPKT     2
/* �������ձ��Ķ��е�ǰ״̬(������)�澯��Ϣ���ݽṹ���� */
typedef struct tagSFE_WARNING_DRV_RCVQUESTATE
{
    UINT32      u32VcpuId;      /* ����澯�ı��Ľ��ն������ڵ�VCPUID */
    UINT32      u32RcvQueState; /* ��VCPUID�µı��Ľ��ն��и澯״̬ */
}SFE_WARNING_DRV_RCVQUESTATE_S;

/* �澯ʱʹ�õĽӿ��� */
#define SFE_WARNING_DRV_IFNAME_MAXLEN  16
/* �ӿ�����״̬:UP */
#define SFE_WARNING_DRV_IFSTATE_UP   1
/* �ӿ�����״̬:DOWN */
#define SFE_WARNING_DRV_IFSTATE_DOWN 2
/* �����ӿ�UP/DOWN�仯�澯��Ϣ���ݽṹ���� */
typedef struct tagSFE_WARNING_DRV_IFSTATE
{
    UINT8                       u8PortType;       /* VISP������ӿ����� */
    UINT8                       u8Reserved;       /* �˿����� */
    UINT16                      u16PortNo;        /* VISP������ӿ�ID */
    UINT32                      u32DrvIfIndex;    /* �����ӿ�����(SCG��Ʒʹ�÷�ʽ��ΪLinux�ӿ�����) */
    UINT32                      u32DrvIfPhyState; /* �㿽���ں��ϱ��Ľӿ�����״̬,��ǰ���ֶ�δʹ��,δ��Ч */
    UINT8                       u8DrvIfName[SFE_WARNING_DRV_IFNAME_MAXLEN]; /* �����ӿ��� */
}SFE_WARNING_DRV_IFSTATE_S;

/* ��ǰ���ձ��Ĵ�С���Ͻ��ջ��������������ݳ������ܵĽ��ջ�������С */
#define SFE_WARNING_SOCK_BUFFULL_REASON_NORMAL   0
/* ��ǰ���ձ��Ĵ�С�������ܵĽ��ջ�������С */
#define SFE_WARNING_SOCK_BUFFULL_REASON_ONEPKT_EXCEED_RCVBUF   1
/* socket���ջ��������澯��Ϣ���ݽṹ���� */
typedef struct tagSFE_WARNING_SOCK_RCVBUF_FULL
{
    INT32  i32Fd;                                 /* socket id */
    INT32  i32RelativeFd;                         /* �������socket id(�����),����TCP/UDP���� */
    UINT32 u32LocalIP;                            /* ���ص�ַ,�����е�Ŀ�ĵ�ַ(�����ֽ���) */
    UINT32 u32RemoteIP;                           /* Զ�˵�ַ,�����е�Դ��ַ(�����ֽ���) */
    UINT16 u16LocalPort;                          /* ���ض˿�,�����е�Ŀ�Ķ˿�(�����ֽ���) */
    UINT16 u16RemotePort;                         /* Զ�˶˿�,�����е�Դ�˿�(�����ֽ���) */
    UINT8  u8Protocol;                            /* Э��� */
    UINT8  u8Reason;                              /* ����������ԭ�� */
    UINT8  u8Reserved[2];                         /* �����ֶ� */
}SFE_WARNING_SOCK_RCVBUF_FULL_S;

/* ������Ϣ������Ӻ���ԭ�� */
typedef VOID (*gpfSFEDebugOutput)(CHAR *pcDebugInfo);
/* ��ʾ��Ϣ������Ӻ���ԭ�� */
typedef VOID (*gpfSFEInfoOutput)(CHAR *pcInfo);
/* �澯��Ϣ������Ӻ���ԭ�� */
typedef VOID (*gpfSFEWarningOutput)(UINT32 u32WarningID, UINT32 u32WarningType, VOID* pWarningPara);
/* ��־�������ԭ�ͽṹ */
typedef struct tagSFE_LOG_HOOK_FUNC
{
    VOID (*pfSFE_FixlenLogOutput)(UINT32 u32LogCode, UINT32 u32LogLevel,
                                    UINT32 u32LogType, VOID* pFormat,
                                    UINT32 u32Para1, UINT32 u32Para2,
                                    UINT32 u32Para3, UINT32 u32Para4);
    VOID (*pfSFE_VarlenLogOutput)(UINT32 u32LogCode, UINT32 u32LogLevel,
                                    UINT32 u32LogType, VOID* pFormat, VOID* pData);
}SFE_LOG_HOOK_FUNC;



extern UINT32 SFE_RegDebugOutputHookFunc(gpfSFEDebugOutput pfDebugOutput);


extern UINT32 SFE_RegInfoOutputHookFunc(gpfSFEInfoOutput pfInfoOutput);


extern UINT32 SFE_RegWarningOutputHookFunc(gpfSFEWarningOutput pfWarningOutput);


extern UINT32 SFE_RegLogHookFunc(SFE_LOG_HOOK_FUNC* pstHookFunc);


extern UINT32 SFE_SetDebugTypeSwitch (UINT32 u32DebugTypeSwitch);


extern UINT32 SFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);


extern UINT32 SFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);


extern UINT32 SFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, UINT32* pu32DebugVcpuSwitch,

                                         UINT32* pu32DebugModuleSwitch);


extern VOID   SFE_ShowDebugSwitch(VOID);


extern UINT32 SFE_SetLogLevel(UINT32 u32LogLevel);


extern UINT32 SFE_GetLogLevel(UINT32* pu32LogLevel);


extern UINT32 SFE_SetLogType(UINT32 ul32WarningLogEnable, UINT32 u32CfgLogEnable, UINT32 u32RunLogEnable);


extern UINT32 SFE_GetLogType(UINT32* pu32WarningLogEnable, UINT32* pul32CfgLogEnable, UINT32* pu32RunLogEnable);


extern VOID   SFE_ShowLogSwitch(VOID);


extern UINT32 SFE_SetMsgOrEvent_DebugSwitch(UINT32 u32DebugSwitch);


extern UINT32 SFE_GetMsgOrEvent_DebugSwitch(UINT32 *pu32DebugSwitch);


extern UINT32 SFE_SetVerboseDebug_CntAndLen(UINT32 u32PktNum, UINT32 u32Length);


extern UINT32 SFE_GetVerboseDebug_CntAndLen(UINT32 *pu32PktNum, UINT32 *pu32Length);

/*******************************************************************************
*    Func Name: SFE_ShowAllStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: ��ʾ����ͳ����Ϣ���
*  Description: ��ʾ����ͳ����Ϣ���
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowAllStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowAutoStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: ��ʾ������(�Զ�ͳ�ƴ��)�������
*  Description: ��ʾ������(�Զ�ͳ�ƴ��)�������
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowAutoStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowManualStatistic
* Date Created: 2009-08-08
*       Author: wuhailan103194
*      Purpose: ��ʾ����(�ֶ�ͳ�ƴ��)�������
*  Description: ��ʾ����(�ֶ�ͳ�ƴ��)�������
*        Input: 
*       Output:
*       Return: VOID
*      Caution:
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-08   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowManualStatistic(VOID);

/*******************************************************************************
*    Func Name: SFE_ShowManualStatisticByVCPU
* Date Created: 2009-08-17
*       Author: wuhailan103194
*      Purpose: ��ʾĳ��VCPU�µ�����(�ֶ����)ͳ����Ϣ���
*  Description: ��ʾĳ��VCPU�µ�����(�ֶ����)ͳ����Ϣ���
*        Input: UINT32 u32VCPUID:VCPU ID,
*               ID���[0,31]:��ʾ��ʾָ��VCPU��ŵ��ֶ�ͳ����Ϣ
*               SFE_VCPU_MAX_NUM(32):��ʾѭ����ʾ��VCPU���ֶ�ͳ����Ϣ
*               SFE_SHOW_TOTAL_MANUAL_STATISTIC(0xffffffff):��ʾ��ʾ��VCPU�ֶ�ͳ��ֵ֮��
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: SFE_ShowAllStatistic
*               SFE_ShowAutoStatistic
*               SFE_ShowManualStatistic
*               SFE_ShowManualStatisticByVCPU
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-17   wuhailan103194          Create
*
*******************************************************************************/
extern VOID SFE_ShowManualStatisticByVCPU(UINT32 u32VCPUID);


#ifdef  __cplusplus
}
#endif

#endif


