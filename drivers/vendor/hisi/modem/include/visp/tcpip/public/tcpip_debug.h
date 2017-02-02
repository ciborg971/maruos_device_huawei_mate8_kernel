

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _TCPIP_DEBUG_H_
#define _TCPIP_DEBUG_H_

#include "tcpip/public/vrpvos/mbuf.h"
#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_log.h"

extern CHAR *TCPIP_MidInfo_IPV4[];
extern CHAR *TCPIP_MidInfo_IPV6[];

extern VOID TCPIP_DebugOutput(CHAR *pDebugInfo);

extern VOID TCPIP_InfoOutput(CHAR *pInfo);

extern VOID TCPIP_CCOutput(ULONG ulCCType, ULONG ulExecID, ULONG ulInfoID, CHAR *pszCCResult);
    
/* VISP�澯�ӿڣ�֪ͨ��Ʒ���ܹ��ĵĸ澯��Ϣ���������ɲ�Ʒ����ʵ�� */
extern VOID TCPIP_WarningOut(ULONG ulWarningID, VOID* pWarnParam);

ULONG IC_ErrTraceOutput(ULONG ulMid,CHAR *pucFile, CHAR *pucFunc,ULONG ulLine,ULONG ulLevel,CHAR* pucMessage);

ULONG TCPIP_SetDebugLevel (ULONG ulMid, ULONG ulDebugLevel);
ULONG TCPIP_GetDebugLevel(ULONG ulMid, ULONG* pulDebugLevel);

extern ULONG TCPIP_SelfTaskID();

extern VOID IP_ShowAllVrfIPAddr();

extern ULONG g_ulSockDbgLevel;   /*Socket4����ĵ��Լ���*/
extern ULONG g_ulTCP4DbgLevel;   /*TCP4����ĵ��Լ���*/
extern ULONG g_ulUDP4DbgLevel;   /*UDP4����ĵ��Լ���*/
extern ULONG g_ulICMP4DbgLevel;  /*ICMP4����ĵ��Լ���*/
extern ULONG g_ulPP4DbgLevel;    /*PP4����ĵ��Լ���*/
extern ULONG g_ulEthArpDbgLevel; /*ETHARP����ĵ��Լ���*/
extern ULONG g_ulPPPDbgLevel;    /*PP4����ĵ��Լ���*/
extern ULONG g_ulATKDbgLevel;    /*ATK����ĵ��Լ���*/

extern ULONG g_ulLogType;       /*LOG��Ϣ����,Ĭ�ϼ�¼����������Ϣ*/
extern ULONG g_ulLogLevel;      /*LOG��Ϣ�ȼ�,Ĭ�ϼ�¼MAJOR�ȼ���Ϣ*/
extern TCPIP_LOG_HOOK_FUNC g_stTCPIPLogOutput;  /*��־���ȫ�ֽṹ�����*/

extern gpfTCPIPDebugOutput      g_pfTCPIPDebugOutput;   /* ������Ϣ������� */
extern gpfTCPIPWarningOutput    g_pfTCPIPWarningOutput; /* �澯������� */
extern gpfTCPIPInfoOutput       g_pfTCPIPInfoOutput;    /* ��ѯ��Ϣ������� */
extern gpfVOSAssertX            g_pfVOSAssertX;         /* ����������� */
extern TCPIP_CC_OUTPUT_HOOK_FUNC pfTCPIP_CC_Output;     /* �û�CC��Ͻ��������� */

/*���º궨����Ϊ�˸�������������Ϣʱ��*/
#define SOCK_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulSockDbgLevel != ERR_LEVEL_TEST) && (g_ulSockDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulSockDbgLevel) && (ulLevel == g_ulSockDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_SOCKET,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define TCP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulTCP4DbgLevel != ERR_LEVEL_TEST) && (g_ulTCP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulTCP4DbgLevel) && (ulLevel == g_ulTCP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_TCP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define UDP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulUDP4DbgLevel != ERR_LEVEL_TEST) && (g_ulUDP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulUDP4DbgLevel) && (ulLevel == g_ulUDP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_UDP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ICMP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulICMP4DbgLevel != ERR_LEVEL_TEST) && (g_ulICMP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulICMP4DbgLevel) && (ulLevel == g_ulICMP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ICMP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }
    
#define PP4_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulPP4DbgLevel != ERR_LEVEL_TEST) && (g_ulPP4DbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulPP4DbgLevel) && (ulLevel == g_ulPP4DbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_PP4,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ETHARP_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulEthArpDbgLevel != ERR_LEVEL_TEST) && (g_ulEthArpDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulEthArpDbgLevel) && (ulLevel == g_ulEthArpDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ETHARP,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define PPP_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulPPPDbgLevel != ERR_LEVEL_TEST) && (g_ulPPPDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulPPPDbgLevel) && (ulLevel == g_ulPPPDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_PPP,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define ATK_ERROR_TRACE(ucFunc,ulLevel,ucMessage) \
    if (((g_ulATKDbgLevel != ERR_LEVEL_TEST) && (g_ulATKDbgLevel <= ulLevel)) \
        || ((ERR_LEVEL_TEST == g_ulATKDbgLevel) && (ulLevel == g_ulATKDbgLevel)))\
    {\
        (VOID)IC_ErrTraceOutput(MID_COMP_ATTACK,__FILE__,ucFunc,__LINE__,ulLevel,ucMessage);\
    }

#define OUTPUT_FIX_LOG 0x1  /* ���������־��com�� */
#define OUTPUT_VAR_LOG 0x2  /* ����䳤��־��com�� */
#define OUTPUT_DEBUG   0x4  /* ���������Ϣ��com�� */
#define OUTPUT_INFO    0x8  /* �����ʾ��Ϣ��com�� */
#define OUTPUT_CC      0x10 /* CC��Ϣ�����com�� */

#define TCPIP_CCTYPE_DCC   1
#define TCPIP_CCTYPE_NCC   2

#define LOG_ASY_OUTPUT_MOD 0
#define LOG_SYN_OUTPUT_MOD 1


/* BFD��ʼ����BFD��¼��Ŀ */
#define BFDINFO_COUNT    2

/* ������ʶ */
#define BFDINFO_ONEHOP   0

/* ������ʶ */
#define BFDINFO_MULTIHOP 1

/* BFD��ʼ���ɹ���� */
#define BFDINIT_OK       1

/* BFD�˿ڶ�����ʾ��־ */
#define BFDPORT_EXPOSE   1

/* BFDģ�鵥����Ŀ�Ķ˿� */
#define BFDINFO_SCRPORT_ONEHOP 3784

/* BFDģ�������Ŀ�Ķ˿� */
#define BFDINFO_SCRPORT_MULHOP 4784

/* BFD����״̬��� */
extern ULONG ulBFDFlag;

#endif  /* _TCPIP_DEBUG_H_ */

#ifdef  __cplusplus
}
#endif
