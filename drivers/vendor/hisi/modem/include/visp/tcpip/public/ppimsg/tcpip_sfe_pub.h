

#ifndef _TCPIP_SFE_PUB_H_
#define _TCPIP_SFE_PUB_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#ifndef SFE_OK
#define SFE_OK      0
#endif

#ifndef LEN_64
#define LEN_64   64
#endif

/* �������ַ��Ϣ�ṹ���� */
typedef union unSFE_IPADDR
{
    UINT32 u32IPv4;       /* IPv4��ַ */
    UINT32 u32IPv6[4];    /* IPv6��ַ */
}SFE_IPADDR_UN;

/* ������������Ϣ,�ӿ��������ṹ�п��������������ýṹ�� */
#define TCPIP_SFE_FLOWSTAT_COPY_RULE_CTRLTOSFE(pstSfeFlowStatCfgRule, pstCtrlFlowStatCfgRule) \
{\
        (pstSfeFlowStatCfgRule)->u32FlowStatId = (pstCtrlFlowStatCfgRule)->u32FlowStatId;\
        (pstSfeFlowStatCfgRule)->u32VrfIndex = (pstCtrlFlowStatCfgRule)->u32VrfIndex;\
        (pstSfeFlowStatCfgRule)->unSrcIp.u32IPv4 = VOS_HTONL((pstCtrlFlowStatCfgRule)->unSrcIp.u32IPv4);\
        (pstSfeFlowStatCfgRule)->unDstIp.u32IPv4 = VOS_HTONL((pstCtrlFlowStatCfgRule)->unDstIp.u32IPv4);\
        (pstSfeFlowStatCfgRule)->u32ProNo = (pstCtrlFlowStatCfgRule)->u32ProNo;\
        (pstSfeFlowStatCfgRule)->u16SrcPort = VOS_HTONS((pstCtrlFlowStatCfgRule)->u16SrcPort);\
        (pstSfeFlowStatCfgRule)->u16DstPort = VOS_HTONS((pstCtrlFlowStatCfgRule)->u16DstPort);\
}

#ifdef  __cplusplus
}
#endif

#endif

