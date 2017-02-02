/************************************************************************
*                                                                      *
*                             ppp_perf.h                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2013/04/17                                      *
*  Author:             wangyong                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPPģ������ͳ�ƺ궨��                           *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*                                                                      *
************************************************************************/
#ifndef      _PPP_PERF_H_
#define      _PPP_PERF_H_

#ifdef      __cplusplus
    extern "C" {
#endif      /* end of __cplusplus */


#define PPP_SNMP_PERF_PHASE_LCP        0
#define PPP_SNMP_PERF_PHASE_AUTH       1
#define PPP_SNMP_PERF_PHASE_NET        2
#define PPP_SNMP_PERF_PHASE_SUCCESS    3


enum E_PERF_ENTITY
{
    PERF_ENTITY_BEGIN = 10000,
    PERF_TYPE_PDSN_SESSION_CUR_MPPC_REAL,
    PERF_TYPE_PDSN_SESSION_CUR_MPPC_VJ_REAL,
    PERF_TYPE_PDSN_SESSION_CUR_VJ_REAL,
    PERF_TYPE_PPPC_LCP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_IPCP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_PPP_NEGO_NUM,
    PERF_TYPE_PPPC_CCP_NEGO_SUCC,
    PERF_TYPE_PPPC_SEND_NEGO_PKT_NUM,
    PERF_TYPE_PPPC_RCV_ERR_NEGO_PKT_NUM,
    PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM,
    PERF_TYPE_PPPC_PAP_AUTHEN_SUCC_NUM,
    PERF_TYPE_PPPC_IPCP_NEGO_REQ_NUM,
    PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_CONNCET_SUC_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
    PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_SUC_NUM,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_SUC,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_SUC,
    PERF_TYPE_1X_PPP_NEGOTIATIONS,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS,
    PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS_SUC,
    PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS_SUC,
    PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
    PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS,
    PERF_TYPE_PCF_PPPC_IPV6CP_NEGO_SUCC_NUM,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
    PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
    PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
    PERF_TYPE_PPPC_IPV6CP_NEGO_REQ_NUM,
    PERF_TYPE_PPPC_IPV6CP_NEGO_SUCC_NUM,
    PERF_TYPE_PPPC_LCP_NEGO_REQ_NUM,
    PERF_TYPE_PPPC_CCP_NEGO_ATTEMP,
    PERF_TYPE_EHRPD_PCF_PPP_TOTAL_TIME,
    PERF_TYPE_EHRPD_PCF_PPP_NEGO_NUM,
    PERF_TYPE_PPPC_PAP_AUTHEN_NUM,
    PERF_TYPE_PPPC_CHAP_AUTHEN_NUM,



    PERF_ENTITY_BUTT
};

typedef enum
{
    /*��Ϣ��ͳ��*/
    E_IPV6_IPV6_MSG,
    E_IPV6_ICMP_MSG,
    E_IPV6_UDP_MSG,
    E_IPV6_NS_MSG,
    E_IPV6_RS_MSG,
    E_IPV6_MSG_LEN_ERR,
    E_IPV6_MSG_LIMIT_ERR,
    E_IPV6_MSG_NOT_SUPPORT,
    E_IPV6_MSG_CHECKSUM_ERR,
    E_IPV6_TARGET_ERR,
    E_IPV6_DEST_ERR,
    E_IPV6_OPT_LEN_ERR,
    E_IPV6_OPT_DUP_ERR,
    E_IPV6_OPT_UNKOWN,
    E_IPV6_OPT_NOT_SUPPORT,
    E_IPV6_RS_NO_CONTEXT,
    E_IPV6_UDP_PORT_ERR,
    E_IPV6_DHCP_TYPE_ERR,
    E_IPV6_DHCP_IA_ERR,
    E_IPV6_DHCP_ORO_ERR,
    E_IPV6_MBUF_ERR,
    E_IPV6_PPP_INFO_ERR,
    E_IPV6_PPP_ENCAP_ERR,
    E_IPV6_INVALID_RPINDEX,
    E_IPV6_RS_IP_TYPE_ERR,

    /*����ͳ��*/
    E_IPV6_START_TIMER,
    E_IPV6_STOP_TIMER,
    E_IPV6_TIMER_NOCONTEXT,
    E_IPV6_RESTART_TIMER,
    E_IPV6_A11_NOTIFY_NOCONTEXT,
    E_IPV6_PERF_STATIC_NEGO_ATTEMPT,
    E_IPV6_PERF_STATIC_NEGO_SUCCESS,
    E_IPV6_USER_PERF_STATIC_V6_ADD,
    E_IPV6_USER_PERF_STATIC_V4V6_ADD,
    E_IPV6_USER_PERF_STATIC_V6_SUB,
    E_IPV6_USER_PERF_STATIC_V4V6_SUB,
    E_IPV6_A11_NOTIFY_SEND_RA_ERR,
    E_IPV6_SEND_RA_MSG_ERR,
    E_IPV6_SEND_DHCP_GET_CONTEXT_FAIL,
    E_IPV6_SEND_DHCP_PPP_MSG_ERR,


    E_IPV6_CNT_END,
}IPV6_CNT_E;


/* ����ͳ�ƽṹ */
typedef struct tagPppPerfStatistic
{
    VOS_SIZE_T  ulReceiveNego;          /* PPPC�յ���Э�̱������� */
    VOS_SIZE_T  ulReceiveNegoErr;       /* PPPC�յ���Ч�ı����� */
    VOS_SIZE_T  ulSendNego;             /* PPPC���͵�Э�̱������� */
    VOS_SIZE_T  ulLcpTotal;             /* LCPЭ�̳��Դ��� */
    VOS_SIZE_T  ulLcpSuccess;           /* LCPЭ�̳ɹ����� */
    VOS_SIZE_T  ulIpcpTotal;            /* IPCPЭ�̳��Դ��� */
    VOS_SIZE_T  ulIpcpSuccess;          /* IPCPЭ�̳ɹ����� */
    VOS_SIZE_T  ulPppNegoTotalTime;     /* PPPЭ����ʱ�� */
    VOS_SIZE_T  ulPppNegoTime;          /* PPPƽ��Э��ʱ�� */
    VOS_SIZE_T  ulPppNegoNum;           /* PPPЭ�̴��� */
    VOS_SIZE_T  ulPapTotal;            /* ��֤���Դ��� */
    VOS_SIZE_T  ulPapSuccess;          /* ��֤�ɹ����� */
    VOS_SIZE_T  ulChapTotal;            /* ��֤���Դ��� */
    VOS_SIZE_T  ulChapSuccess;          /* ��֤�ɹ����� */
    VOS_SIZE_T  ulCcpTotal;            /* CCPЭ�̳��Դ��� */
    VOS_SIZE_T  ulCcpSuccess;          /* CCPЭ�̳ɹ����� */
    VOS_SIZE_T  ulReceiveStac;         /* PPPC�յ���STACѹ�������� */
    VOS_SIZE_T  ulSendStac;            /* PPPC���͵�STACѹ�������� */
    VOS_SIZE_T  ulReceiveMppc;         /* PPPC�յ���MPPCѹ�������� */
    VOS_SIZE_T  ulSendMppc;            /* PPPC���͵�MPPCѹ�������� */

    VOS_SIZE_T  ulCurVjUser;           /* ��ǰVJ�û��� */
    VOS_SIZE_T  ulCurMppcUser;         /* ��ǰMppc�û��� */
    VOS_SIZE_T  ulCurMppcVjUser;       /* ��ǰMppcVJ�û��� */


    VOS_SIZE_T  ulHSGWPppNegoTime;     /* ehrpd: PPPƽ��Э��ʱ�� */
} PPPPERFSTATISTIC_S;

/*����ͳ�ƽṹ*/
typedef struct tagIpv6PerfStatistic
{
    VOS_SIZE_T  ulIpv6CpNegoSucc ;           /* IPv6CPЭ�̳ɹ����� */
    VOS_SIZE_T  ulIpv6CpNegoAttempt;         /* IPv6CPЭ�̳��Դ��� */
    VOS_SIZE_T  ulSipIpv6UserActNum ;       /* ��ǰ����ļ�IPv6��ջ�û��� */
    VOS_SIZE_T  ulMipIpv4v6UserActNum;      /* ��ǰ����ļ�IPv4/IPv6˫ջ�û��� */
}IPV6PERFSTATISTIC_S;

typedef enum
{
    FSM_ALARM_NULL = 0,    /*�������κθ澯��ΪPPP���ƿ��еĳ�ʼֵ*/

    FSM_ALARM_LCP_MS_NO_RSP = 0x81, /*129. LCPЭ�̽׶��ն�����Ӧ */
    FSM_ALARM_LCP_MS_RELEASE,       /*130. LCPЭ�̽׶��ն���������ȥ�� */
    FSM_ALARM_LCP_PCF_RELEASE,      /*131. LCPЭ�̽׶�PCF���A10 */
    FSM_ALARM_LCP_NEGOFAIL,         /*132. LCPЭ�̽׶�Э��ʧ�� */


    FSM_ALARM_AUTH_ERROR_ACCOUNT,   /*133. AUTH�׶��û�������� */
    FSM_ALARM_AUTH_AAA_NO_RSP,      /*134. AUTH�׶�AAA����Ӧ*/
    FSM_ALARM_AUTH_MS_NO_RSP,       /*135. AUTH�׶��ն�����Ӧ*/
    FSM_ALARM_AUTH_MS_RELEASE,      /*136. AUTH�׶��ն���������ȥ��*/
    FSM_ALARM_AUTH_PCF_RELEASE,     /*137. AUTH�׶�PCF���A10*/
    FSM_ALARM_AUTH_ERROR_OTHER,     /*138. AUTH�׶�����ԭ�� */

    FSM_ALARM_IPCP_MS_NO_RSP,       /*139. IPCP�׶��ն�����Ӧ*/
    FSM_ALARM_IPCP_MS_RELEASE,      /*140. IPCPЭ�̽׶��ն���������ȥ�� */
    FSM_ALARM_IPCP_PCF_RELEASE,     /*141. IPCPЭ�̽׶�PCF���A10 */
    FSM_ALARM_IPCP_NEGOFAIL,        /*142. IPCPЭ�̽׶�Э��ʧ�� */
    FSM_ALARM_IPCP_ALLOC_IP_FAIL,   /*143. IPCPЭ�̽׶�IP��ַ����ʧ�� */

    FSM_ALARM_LCP_OTHER,            /*144. LCPЭ�̽׶�����ԭ��ʧ��*/
    FSM_ALARM_AUTH_OTHER,           /*145. AUTH�׶�����ԭ��ʧ��*/
    FSM_ALARM_IPCP_OTHER,           /*146. IPCP�׶�����ԭ��ʧ��*/

    FSM_ALARM_IPCP_PCRF_FAIL,       /*147. C06����IPCP�׶�PCRFʧ��*/

    /*����ΪHSGW������LCP��EAP��VSNCP����ʧ�ܴ����� CR-0000060209 */
    FSM_ALARM_EHRPD_LCP_MS_NO_RSP = 0xA1,   /*161. eHRPD�û�LCPЭ�̽׶��ն�����Ӧ */
    FSM_ALARM_EHRPD_LCP_MS_RELEASE,         /*162. eHRPD�û�LCPЭ�̽׶��ն���������ȥ�� */
    FSM_ALARM_EHRPD_LCP_PCF_RELEASE,        /*163. eHRPD�û�LCPЭ�̽׶�PCF���A10 */
    FSM_ALARM_EHRPD_LCP_NEGOFAIL,           /*164. eHRPD�û�LCPЭ�̽׶�Э��ʧ�� */


    FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP,        /*165. eHRPD�û�AUTH�׶�AAA����Ӧ*/
    FSM_ALARM_EHRPD_AUTH_MS_NO_RSP,         /*166. eHRPD�û�AUTH�׶��ն�����Ӧ*/
    FSM_ALARM_EHRPD_AUTH_MS_RELEASE,        /*167. eHRPD�û�AUTH�׶��ն���������ȥ��*/
    FSM_ALARM_EHRPD_AUTH_PCF_RELEASE,       /*168. eHRPD�û�AUTH�׶�PCF���A10*/


    FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP,        /*169. eHRPD�û�VSNCP�׶��ն�����Ӧ*/
    FSM_ALARM_EHRPD_VSNCP_MS_RELEASE,  /*170. eHRPD�û�VSNCPЭ�̽׶��ն���������ȥ�� */
    FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE,      /*171. eHRPD�û�VSNCPЭ�̽׶�PCF���A10 */
    FSM_ALARM_EHRPD_VSNCP_NEGOFAIL,         /*172. eHRPD�û�VSNCPЭ�̽׶�Э��ʧ�� */

    FSM_ALARM_EHRPD_LCP_OTHER,              /*173. eHRPD�û�LCPЭ�̽׶�����ԭ��ʧ��*/
    FSM_ALARM_EHRPD_AUTH_OTHER,             /*174. eHRPD�û�AUTH�׶�����ԭ��ʧ��*/
    FSM_ALARM_EHRPD_VSNCP_OTHER,            /*175. eHRPD�û�VSNCP�׶�����ԭ��ʧ��*/

    FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL,        /*176. eHRPD�û�VSNCP�׶�PCRFʧ��*/
    FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP,      /*177. eHRPD�û�VSNCP�׶�PCRF����Ӧ*/
    FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER,    /*178. eHRPD�û�VSNCP�׶�PCRF����ԭ��ʧ��*/

    FSM_ALARM_EHRPD_VSNCP_PGW_FAIL,         /*179. eHRPD�û�VSNCP�׶�PGWʧ�� */
    FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP,       /*180. eHRPD�û�VSNCP�׶�PGW����Ӧ */
    FSM_ALARM_EHRPD_VSNCP_PGW_OTHER,      /*181. eHRPD�û�VSNCP�׶�PGW����ԭ��ʧ�� */
}FSM_ALARM_CODE_E;

typedef struct tagAlarmLinkNode
{
    struct tagAlarmLink stNodeInfo;
    struct tagAlarmLinkNode *pNext;
}PPPA11_AlarmLink_NODE_S;

typedef struct tagAlarmLinkHead
{
    struct tagAlarmLinkNode *pHead;
    struct tagAlarmLinkNode *pEnd;
    ULONG  ulAlarmCount;
    ULONG  ulReserved;         /* luofang--���ֽڶ��� */
}PPPA11_AlarmLink_HEAD_S;


#define M_SET_NEWPHASE(pstPppInfoT, NewPhase) \
{\
    ((PPPINFO_S *)pstPppInfoT)->bPhaseFlag = NewPhase; \
    SNMP_SetDefaultFailTypeByPhase(pstPppInfoT); \
}


/* PPP���ӳɹ����� */
#define PPP_SNMP_PERF_SET_SUCCESS(pstPppInfo) \
{ \
    if (pstPppInfo->bEhrpdUser) \
    { \
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM, \
                                        pstPppInfo->ulPcfIP, \
                                        A11_PERF_OPERATOR_PLUS, \
                                        1);     \
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_SUC_NUM, \
                                        pstPppInfo->ulPcfIP,  \
                                        A11_PERF_OPERATOR_PLUS, \
                                        1); \
        if (VOS_FALSE == pstPppInfo->bIpcpSucFlag) \
        {   \
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM, \
                                            pstPppInfo->ulPcfIP, \
                                            A11_PERF_OPERATOR_PLUS, \
                                            1);     \
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_SUC_NUM, \
                                            pstPppInfo->ulPcfIP, \
                                            A11_PERF_OPERATOR_PLUS, \
                                            1); \
        } \
    } \
    else \
    { \
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                              PERF_TYPE_1X_PPP_NEGOTIATIONS_SUC, \
                              PERF_TYPE_EVDO_PPP_NEGOTIATIONS_SUC, PERF_ADD); \
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                              PERF_TYPE_1X_PPP_NEGOTIATIONS,  \
                              PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD); \
        if (VOS_FALSE == pstPppInfo->bIpcpSucFlag) \
        {   \
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,  \
                                  PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS_SUC,  \
                                  PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS_SUC, PERF_ADD);  \
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,  \
                                  PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD); \
        } \
    } \
    \
    pstPppInfo->bIpcpSucFlag = VOS_TRUE; \
    M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_SUCCESS); \
    \
}

/* ms����ȥ�� */
#define PPP_SNMP_PERF_SET_FAILREASON_MS_RELEASE(pstPppInfo, pstFsm) \
{ \
        } \
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_RELEASE); /* ��֤�׶��ն��������� */ \
            /* �յ���LCP termate req������û�����PPPЭ�̽׶Σ��򽫡�����Ự��������������1*/ \
            A11_ReqNumSubProc(pstPppInfo); \
        } \
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
        { \
            if (VOS_TRUE == pstPppInfo->bEhrpdUser) \
            { \
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_RELEASE); /* IPCP�׶��ն��������� */  \
            } \
            else \
            { \
                SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_RELEASE); /* IPCP�׶��ն��������� */  \
                /* �յ���LCP termate req������û�����PPPЭ�̽׶Σ��򽫡�����Ự��������������1*/ \
                A11_ReqNumSubProc(pstPppInfo); \
            } \
        } \
    }  \
}


/* ms����Ӧ */
#define PPP_SNMP_PERF_SET_FAILREASON_MS_NO_RSP(pstPppInfo, pstFsm) \
{ \
    if ((pstFsm->ucState != PPP_STATE_CLOSING)  \
        && (pstFsm->ucState != PPP_STATE_STOPPING)) \
    { \
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_LCP_MS_NO_RSP); \
        } \
        else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
            && (PPP_IPCP == pstFsm->usProtocol)) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);  \
        } \
        else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
            &&  (VOS_TRUE == pstPppInfo->bEhrpdUser)) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP);  \
        } \
    } \
}

/* pcf����ȥ�� */
#define PPP_SNMP_PERF_SET_FAILREASON_PCF_RELEASE(pstPppInfo, pstFsm) \
{ \
    if(PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag) \
    { \
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_LCP_PCF_RELEASE); \
    } \
    else if(PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag) \
    { \
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_PCF_RELEASE); \
    }  \
    else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag) \
    { \
        if (VOS_TRUE == pstPppInfo->bEhrpdUser) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE); \
        } \
        else if (PDSN_PPP_IPTYE_IPV6 != pstPppInfo->ucIpCapability) \
        { \
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_PCF_RELEASE); \
        } \
    } \
}

extern ULONG SNMP_CheckPhaseAndFailType(UCHAR ucPhase, UCHAR ucFailType);
extern VOID SNMP_SetFailReason(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType);
extern VOID SNMP_SetDefaultFailTypeByPhase(PPPINFO_S * pstPppInfo);
extern VOID SNMP_TerminatePhaseProc(PPPINFO_S *pstPppInfo);


extern ULONG DeleteAlarmLink(PPPA11_AlarmLink_S *pstNodeInfo);
extern VOID PPP_InsertAlarm(PPPINFO_S *pstPppInfo, UCHAR enRetType);
VOID SNMP_EhrpdUserDeaProc(SDB_PDSN_RP_CONTEXT_S * pstRpContext);
VOID SNMP_GetFailReasonByReleaseCode(ULONG ulReleaseCode, UCHAR *pucFailType);
extern ULONG PPP_A11_AlarmToFamEx(PPPA11_AlarmLink_S stAlarmReport);
extern VOID PPP_PerfStatisticByReleaseCode(PPPINFO_S *pstPppInfo);
extern VOID PPP_A11_AlarmProc(VOID);

#ifdef      __cplusplus
    }
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_DEF_H_ */

