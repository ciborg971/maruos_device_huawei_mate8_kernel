

#ifndef _IPSFE_DEBUG_H_
#define _IPSFE_DEBUG_H_

#ifdef  __cplusplus
    extern "C"{
#endif

/* �������Զ�ͳ��������ռ��С */
#define SFE_STATISTIC_AUTOSTAT_SIZE     (SFE_STAT_IPFWD_MAX * sizeof(UINT32))

/* ��Ӧ����ͳ����δ��ʹ��,��ʾ��������ͳ�ƹ��� */
#define  SFE_FLOWSTAT_IS_NOTUSED    0
/* ��Ӧ����ͳ�����ѱ�ʹ��,��ʾ��������ͳ�ƹ��� */
#define  SFE_FLOWSTAT_IS_USED       1

/* TCPЭ��� */
#define SFE_FLOWSTAT_IPPROTO_TCP    6 
/* UDPЭ��� */
#define SFE_FLOWSTAT_IPPROTO_UDP    17 

/* ������ͳ�ƹ���ʱ�������ΪNULL */
#define SFE_FLOWSTAT_CFGRULE_IS_NULL  1
/* ������ͳ�ƹ���ʱ���������ΪNULL */
#define SFE_FLOWSTAT_CFGRULE_IS_NOT_NULL  0

/* �ж��Ƿ�����Ԫ���VRF���� */
#define SFE_FLOWSTAT_IS_6KEY_FLOW(u32ProtocalNo) \
    ((SFE_FLOWSTAT_IPPROTO_UDP ==  (u32ProtocalNo)) || (SFE_FLOWSTAT_IPPROTO_TCP == (u32ProtocalNo)))

/* �ۼӸ�VCPU���ֶ�ͳ����Ϣ */
#define SFE_STAT_SUM_VCPU_MANUALSTAT(pstSumSfeManualStat, pstTempSfeVcpuManualStat) \
{\
    (pstSumSfeManualStat)->dwLink_In += (pstTempSfeVcpuManualStat)->dwLink_In;\
    (pstSumSfeManualStat)->dwEth_In += (pstTempSfeVcpuManualStat)->dwEth_In;\
    (pstSumSfeManualStat)->dwNet_In += (pstTempSfeVcpuManualStat)->dwNet_In;\
    (pstSumSfeManualStat)->dwIcmp_Out += (pstTempSfeVcpuManualStat)->dwIcmp_Out;\
    \
    (pstSumSfeManualStat)->dwArp_Deliver += (pstTempSfeVcpuManualStat)->dwArp_Deliver;\
    (pstSumSfeManualStat)->dwIpOpt_Deliver += (pstTempSfeVcpuManualStat)->dwIpOpt_Deliver;\
    (pstSumSfeManualStat)->dwIpBroadcast_Deliver += (pstTempSfeVcpuManualStat)->dwIpBroadcast_Deliver;\
    (pstSumSfeManualStat)->dwIpMulticast_Deliver += (pstTempSfeVcpuManualStat)->dwIpMulticast_Deliver;\
    (pstSumSfeManualStat)->dwNonFrag_Deliver += (pstTempSfeVcpuManualStat)->dwNonFrag_Deliver;\
    (pstSumSfeManualStat)->dwFragHaveFakeReassed_Deliver += (pstTempSfeVcpuManualStat)->dwFragHaveFakeReassed_Deliver;\
    (pstSumSfeManualStat)->dwOspf_Deliver += (pstTempSfeVcpuManualStat)->dwOspf_Deliver;\
    (pstSumSfeManualStat)->dwUpToCtrlPlane += (pstTempSfeVcpuManualStat)->dwUpToCtrlPlane;\
    \
    (pstSumSfeManualStat)->dwFakeReass_NetSuccess += (pstTempSfeVcpuManualStat)->dwFakeReass_NetSuccess;\
    (pstSumSfeManualStat)->dwFakeReass_LinkSuccess += (pstTempSfeVcpuManualStat)->dwFakeReass_LinkSuccess;\
    \
    (pstSumSfeManualStat)->dwFakeReass_InFragNum += (pstTempSfeVcpuManualStat)->dwFakeReass_InFragNum;\
    (pstSumSfeManualStat)->dwFakeReass_OutFragNum += (pstTempSfeVcpuManualStat)->dwFakeReass_OutFragNum;\
    (pstSumSfeManualStat)->dwReass_InFragNum += (pstTempSfeVcpuManualStat)->dwReass_InFragNum;\
    (pstSumSfeManualStat)->dwReass_OutReassPktNum += (pstTempSfeVcpuManualStat)->dwReass_OutReassPktNum;\
    \
    (pstSumSfeManualStat)->dwNet_Out += (pstTempSfeVcpuManualStat)->dwNet_Out;\
    (pstSumSfeManualStat)->dwEth_Out += (pstTempSfeVcpuManualStat)->dwEth_Out;\
    \
    (pstSumSfeManualStat)->dwFrag_InNum += (pstTempSfeVcpuManualStat)->dwFrag_InNum;\
    (pstSumSfeManualStat)->dwFrag_OutNum += (pstTempSfeVcpuManualStat)->dwFrag_OutNum;\
    \
    (pstSumSfeManualStat)->dwFakeRease_resv += (pstTempSfeVcpuManualStat)->dwFakeRease_resv;\
    (pstSumSfeManualStat)->dwArpMiss_Resv += (pstTempSfeVcpuManualStat)->dwArpMiss_Resv;\
    \
    (pstSumSfeManualStat)->dwArp_ArpSearchIn += (pstTempSfeVcpuManualStat)->dwArp_ArpSearchIn;\
    (pstSumSfeManualStat)->dwArp_HaveNormalArp += (pstTempSfeVcpuManualStat)->dwArp_HaveNormalArp;\
    (pstSumSfeManualStat)->dwArp_HaveFakeArp += (pstTempSfeVcpuManualStat)->dwArp_HaveFakeArp;\
    (pstSumSfeManualStat)->dwArp_NoArp += (pstTempSfeVcpuManualStat)->dwArp_NoArp;\
    (pstSumSfeManualStat)->dwArp_ReNotifyArpMissSuccess += (pstTempSfeVcpuManualStat)->dwArp_ReNotifyArpMissSuccess;\
    (pstSumSfeManualStat)->dwArp_SendCachePktSuccess += (pstTempSfeVcpuManualStat)->dwArp_SendCachePktSuccess;\
    \
    (pstSumSfeManualStat)->dwIcmp_RecvErrIcmpPkt += (pstTempSfeVcpuManualStat)->dwIcmp_RecvErrIcmpPkt;\
    (pstSumSfeManualStat)->dwIcmp_RecvNoFirstFrg += (pstTempSfeVcpuManualStat)->dwIcmp_RecvNoFirstFrg;\
    (pstSumSfeManualStat)->dwIcmp_RecvBroadOrMultiPkt += (pstTempSfeVcpuManualStat)->dwIcmp_RecvBroadOrMultiPkt;\
    (pstSumSfeManualStat)->dwIcmp_RecvSrcIpErr += (pstTempSfeVcpuManualStat)->dwIcmp_RecvSrcIpErr;\
    (pstSumSfeManualStat)->dwIcmp_SendUnreachHostNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendUnreachHostNum;\
    (pstSumSfeManualStat)->dwIcmp_SendNeedFragNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendNeedFragNum;\
    (pstSumSfeManualStat)->dwIcmp_SendTimeExceededNum += (pstTempSfeVcpuManualStat)->dwIcmp_SendTimeExceededNum;\
    \
    (pstSumSfeManualStat)->dwBfd_In += (pstTempSfeVcpuManualStat)->dwBfd_In;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlSessIdZero += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlSessIdZero;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlSessNotUp += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlSessNotUp;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktStateNotUp += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktStateNotUp;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktPollFlagSet += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktPollFlagSet;\
    (pstSumSfeManualStat)->dwBfd_ToCtrlPktFinalFlagSet += (pstTempSfeVcpuManualStat)->dwBfd_ToCtrlPktFinalFlagSet;\
    (pstSumSfeManualStat)->dwBfd_ToOwnDetectPkt += (pstTempSfeVcpuManualStat)->dwBfd_ToOwnDetectPkt;\
    (pstSumSfeManualStat)->dwBfd_DetectUp += (pstTempSfeVcpuManualStat)->dwBfd_DetectUp;\
    (pstSumSfeManualStat)->dwBfd_DetectDownNotifyOk += (pstTempSfeVcpuManualStat)->dwBfd_DetectDownNotifyOk;\
    (pstSumSfeManualStat)->dwBfd_EncapsualeLinkHeader += (pstTempSfeVcpuManualStat)->dwBfd_EncapsualeLinkHeader;\
    (pstSumSfeManualStat)->dwBfd_SendPktOk += (pstTempSfeVcpuManualStat)->dwBfd_SendPktOk;\
    \
    (pstSumSfeManualStat)->dwFwd_HaveHandle += (pstTempSfeVcpuManualStat)->dwFwd_HaveHandle;\
    (pstSumSfeManualStat)->dwFwd_NotHandle += (pstTempSfeVcpuManualStat)->dwFwd_NotHandle;\
    (pstSumSfeManualStat)->dwFwd_Drop += (pstTempSfeVcpuManualStat)->dwFwd_Drop;\
    \
    (pstSumSfeManualStat)->dwAcl_Forward_NotHandle += (pstTempSfeVcpuManualStat)->dwAcl_Forward_NotHandle;\
    (pstSumSfeManualStat)->dwAcl_Forward_Drop += (pstTempSfeVcpuManualStat)->dwAcl_Forward_Drop;\
    \
    (pstSumSfeManualStat)->dwAcl_UpDeliver_NotHandle +=(pstTempSfeVcpuManualStat)->dwAcl_UpDeliver_NotHandle;\
    (pstSumSfeManualStat)->dwAcl_UpDeliver_Drop += (pstTempSfeVcpuManualStat)->dwAcl_UpDeliver_Drop;\
}
    

/* ��ͳ�ƹ���ṹ����,��ͳ�ƹ��������Ҫ���û���ɾ��һ��������������һ��ʱ��(һ��������Э��ջ����ͣ�������ʱ��,
   ����6s,)֮����������������,������ܴ��ڶ�˲������������,ͳ��ֵ���ܲ�׼ȷ */
typedef struct  tagSFE_FlowStatisticRule
{
    UINT32         u32FlowStatId;        /* ��ͳ��ID,���ʱ��Ϊ�������,ɾ��ʱ���Ը�ֵ,��0����,��ȡʱ��ʾ��ͳ��ID,��0��ʼ��� */
    UINT32         u32VrfIndex;          /* VRF����,������ */
    SFE_IPADDR_UN  unSrcIp;              /* ԴIP,������ */
    SFE_IPADDR_UN  unDstIp;              /* Ŀ��IP,������ */
    UINT32         u32ProNo;             /* Э���,ȡֵ��Χ[0,255] */
    UINT16         u16SrcPort;           /* Դ�˿ں�,������,ֻ��Э��ΪUDP��TCPʱ��Ч,����Э���ʱ��Ч�û�ֱ����0���� */
    UINT16         u16DstPort;           /* Ŀ�Ķ˿ں�,������,ֻ��Э��ΪUDP��TCPʱ��Ч,����Э���ʱ��Ч�û�ֱ����0���� */
}SFE_FLOWSTATISTIC_RULE_S;

/* ��ͳ�ƹ���������Ϣ�ṹ */
typedef struct tagSFE_FlowStatisticRuleCfgInfo
{
    UINT32   u32OperType;                           /* ��ͳ�ƹ������ò������� */
    UINT32   u32IsFlowRulePointerNull;              /* ��ͳ�ƹ������ָ���Ƿ�ΪNULL */
    SFE_FLOWSTATISTIC_RULE_S stFlowStatisticRule;   /* ��ͳ�ƹ������ */
}SFE_FLOWSTATISTIC_RULE_CFG_INFO_S;

/* ��ͳ����Ϣ�ṹ����,����Ϊ�ṹ����Ϊ�˱����Ժ���չ�����ֶ� */
typedef struct tagSFE_FlowStatisticInfo
{
    UINT32  u32FlowStatNum;               /* ��ǰ��ͳ�Ƹ��� */
    UINT32  u32FlowStatSwitch;            /* ��ͳ�ƿ��� */
}SFE_FLOW_STATISTIC_INFO_S;

/* ��ͳ�ƹ���ṹ����,��ͳ�ƹ��������Ҫ���û���ɾ��һ��������������һ��ʱ��(һ��������Э��ջ����ͣ�������ʱ��,
   ����6s,)֮����������������,������ܴ��ڶ�˲������������,ͳ��ֵ���ܲ�׼ȷ */
typedef struct  tagSFE_FlowStatisticRuleInfo
{
    UINT32         u32IsUsed;            /* ����ͳ�����Ƿ����,�Ƿ�ʹ�� */
    UINT32         u32FlowStatId;        /* ��ͳ��ID,������,����ʱ���Ը�ֵ,��0����,��ȡʱ��ʾ��ͳ��ID,��0��ʼ��� */
    UINT32         u32VrfIndex;          /* VRF����,������ */
    UINT32         u32Reserved;          /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
    SFE_IPADDR_UN  unSrcIp;              /* ԴIP,��·�� */
    SFE_IPADDR_UN  unDstIp;              /* Ŀ��IP,��·�� */
    UINT32         u32ProNo;             /* Э��� */
    UINT16         u16SrcPort;           /* Դ�˿ں�,��·�� */
    UINT16         u16DstPort;           /* Ŀ�Ķ˿ں�,��·�� */
}SFE_FLOW_STATISTIC_RULE_INFO_S;

/* ��ͳ�����������Ϣ�ṹ */
typedef struct tagSFE_FLOWSTATISTIC_ALLINFO
{
    UINT32                           u32SfeFlowStatMaxNum;      /* ��ͳ������������� */
    UINT32                           u32Reserved;               /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
    SFE_FLOW_STATISTIC_INFO_S       *pstSfeFlowStatInfo;        /* ��ͳ�ƹ�����Ϣָ�� */
    SFE_FLOW_STATISTIC_RULE_INFO_S  *pstSfeFlowStatRule;        /* ��ͳ�ƹ�����Ϣָ�� */
    SFE_IPSFE_FLOWSTATISTIC_S       *pstSfeFlowStatManualInfo;  /* ��ͳ���ֶ�ͳ����Ϣָ�� */
    UINT32                          *pu32SfeFlowStatAutolInfo;  /* ��ͳ���Զ�ͳ����Ϣָ�� */
}SFE_FLOWSTATISTIC_ALLINFO_S;

/* ͳ�����������Ϣ�ṹ */
typedef struct tagSFE_STATISTIC_ALLINFO
{
    SFE_IPSFE_STATISTIC_S           *pstSfeStatManualInfo;      /* ȫ��ͳ���ֶ�ͳ����Ϣָ�� */
    UINT32                          *pu32SfeStatAutolInfo;      /* ȫ��ͳ���Զ�ͳ����Ϣָ�� */
}SFE_STATISTIC_ALLINFO_S;

/* ������־���Ϳ��ض�Ӧ�����ݽṹ */
typedef struct tagSFE_LOG_TYPESWITCH
{
    UINT32    ul32WarningLogEnable;     /* �澯��־��¼���� */
    UINT32    u32CfgLogEnable;          /* ������־��¼���� */
    UINT32    u32RunLogEnable;          /* ������־��¼���� */
    UINT32    u32Reserved;              /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
}SFE_LOG_TYPESWITCH_S;

/* ��ȡ���Կ��ض�Ӧ�����ݽṹ */
typedef struct tagSFE_DEBUGSWITCH
{
    UINT32    u32DebugTypeSwitch;       /* �������Ϳ��� */
    UINT32    u32DebugVcpuSwitch;       /* VCPU���Կ��� */
    UINT32    u32DebugModuleSwitch;     /* ģ����Կ��� */
    UINT32    u32Reserved;              /* ���4�ֽڱ�֤��64λ��8�ֽڶ��� */
}SFE_DEBUGSWITCH_S;

/* ��ϸ����ʱ��ָ�����Ĵ��������ĳ��� */
typedef struct tagSFE_VERBOSEDEBUG
{
    UINT32 u32PktNum;                   /* ���Ĵ��� */
    UINT32 u32Length;                   /* ���ĳ��� */
}SFE_VERBOSEDEBUG_S;

/* ��Ϣ���� */
#define TCPIP_SFE_MSG_DEBUG     0      
/* �¼����� */
#define TCPIP_SFE_EVENT_DEBUG   1        

/* ���շ��� */
#define TCPIP_SFE_INPUT     0  
/* ���ͷ��� */
#define TCPIP_SFE_OUTPUT    1            

#ifdef  __cplusplus
}
#endif

#endif

