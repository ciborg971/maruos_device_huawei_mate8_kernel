/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               tcpip_dcc.h
*
*  Project Code: VR8C01
*   Module Name: PUBLIC
*  Date Created: 2009-03-25
*        Author: zhangchunyu(62474)
*   Description: ������ͨ�Լ�鴦��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-03-25   zhangchunyu(62474)      Create
*******************************************************************************/
#ifndef _TCPIP_DCC_H_
#define _TCPIP_DCC_H_

#ifdef  __cplusplus
extern "C"{
#endif


#include "tcpip/public/debug/tcpip_dcc_api.h"

/*******************************��*********************************************/
/* DCCд��Ϣ���к궨��*/ 
#define DCC_WriteQueue(ulQueueId,ulMsg,ul_Ret) \
{ \
    ul_Ret = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* DCCд�����¼��궨�� */
#define DCC_SchedTask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulDCCTaskId, ulEvent ); \
}

/* �Ǳ����ETH��TRUNK�ӿ� */
#define DCC_ISEHTORTRUNK(pstIfNet) \
    ((NULL != pstIfNet) && ((IF_ETHERNET_TYPE == pstIfNet->if_ulType) \
    || (IF_ETH_TRUNK_TYPE == pstIfNet->if_ulType)) && (IF_IS_ThisBoard(pstIfNet)))

#define DCC_EVENT                       0x00000001       /* DCC�¼� */

#define DCC_EVENT_START                 0x00000002       /* DCC�¼���ʼ */          
#define DCC_EVENT_TIMER                 (1 << 15)        /* ��ʼDCC��ͨ��鶨ʱ���¼� */

#define DCC_QMODE                       VOS_Q_FIFO     /* ���б�־ */
#define DCC_QUEDEPTH                    (512)       /* DCC���г��� */

#define DCC_ARP_DETECT_MAX_COUNT        3    /* ARP Ping�������� */
#define DCC_MAX_STEAM                   4    /* ���ͳ�������� */

#define DCC_ENABLE                      1
#define DCC_DISNABLE                    0

#define DCC_MAX_PRI                     255      /* CC����������ȼ� */
#define DCC_MAX_DATATIME                600  /* ����ͳ�Ƶ����ʱ�� */


#define DCC_TCPCOMP_ISEXIST             (g_pstDCCTcp4CfgVtbl != NULL)
#define DCC_UDPCOMP_ISEXIST             (g_pstDCCUdp4CfgVtbl != NULL)
#define DCC_RAWIPCOMP_ISEXIST           (g_pstDCCRawip4CfgVtbl != NULL)

#define DCC_PKTFLOW_SEND                0
#define DCC_PKTFLOW_RCV                 1
#define DCC_PKTFLOW_FORWARD             2

#define DCC_IS_ENABLE                   (DCC_ENABLE == g_ulDccPktFlowEnable) /*�Ƿ�ʹ��DCC����*/
#define DCC_NOTFOUND                    0
#define DCC_FOUND                       1  

#define DCC_ETHII_HEADER_LEN            14 /*��̫ͷ��δ��VLAN TAG��ǩ����*/
#define DCC_IP_HEADER_LEN               20 /*IPͷ�г���*/
#define DCC_ETHII_ETHTYPE_POSITION_LEN  12 /*��̫ͷ�����ֽ���̫���ͻ򳤶��ֶε�ƫ��λ��*/
#define DCC_ETHII_VLANTAG_LEN           4  /*��̫ͷ��VLAN TAGռ�õ��ֽڳ���*/

#define DCC_ENABLE_PING                 1  /* ��ping���� */
#define DCC_DISNABLE_PING               0  /* ����ping���� */


#define DCC_RECV_DROPSTAT(pMBuf) \
{ \
    if ((DCC_IS_ENABLE) && (NULL != pMBuf) && (MBUF_GET_DCCFLAG(pMBuf) & MBUF_FLAG_DCCSTREAM_RCV)) \
    { \
        ULONG ulLine = __LINE__; \
        UCHAR ucDccFlowId; \
        CHAR  szCurrentFileName[FILENAME_LEN]; \
        TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
        ucDccFlowId = MBUF_GET_DCC_FLOWID(pMBuf); \
        (VOID)TCPIP_strncpy(g_stDccStat.stDccStat[ucDccFlowId].stRcvStat.cFileName, FILENAME_LEN, szCurrentFileName, FILENAME_LEN - 1); \
        g_stDccStat.stDccStat[ucDccFlowId].stRcvStat.ulFileLine = ulLine; \
        MBUF_SET_DCCFLAG(pMBuf, MBUF_FLAG_DCCSTREAM_DESTROY); \
    } \
}

#define DCC_SEND_DROPSTAT(pMBuf) \
{ \
    if ((DCC_IS_ENABLE) && (NULL != pMBuf) && (MBUF_GET_DCCFLAG(pMBuf) & MBUF_FLAG_DCCSTREAM_SND)) \
    { \
        ULONG ulLine = __LINE__; \
        UCHAR ucDccFlowId; \
        CHAR  szCurrentFileName[FILENAME_LEN]; \
        TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
        ucDccFlowId = MBUF_GET_DCC_FLOWID(pMBuf); \
        (VOID)TCPIP_strncpy(g_stDccStat.stDccStat[ucDccFlowId].stSndStat.cFileName, FILENAME_LEN, szCurrentFileName, FILENAME_LEN - 1); \
        g_stDccStat.stDccStat[ucDccFlowId].stSndStat.ulFileLine = ulLine; \
        MBUF_SET_DCCFLAG(pMBuf, MBUF_FLAG_DCCSTREAM_DESTROY); \
    } \
}


/*******************************ö�ٱ���***************************************/

/* ����enumDccInfo����, һ��Ҫ����g_stDccInfoString����ַ��� */
enum enumDccInfo
{
    DCC_INFO_START = 0,              /* ��ʼ,��ӡ��ϱ��� */
    DCC_INFO_INTFPHYUP,              /* �ӿڵײ�UP */   
    DCC_INFO_INTFPHYDOWN,            /* �ӿڵײ�Down */ 
    DCC_INFO_LINEDOWN,               /* ETH��TRUNK�ӿ�Э��״̬����UP*/
    DCC_INFO_LINEUP,                 /* �ӿ�Э��״̬��UP*/
    DCC_INFO_LCPDOWN,
    DCC_INFO_LCPOPEN,
    DCC_INFO_PPPIPCPOPEN,
    DCC_INFO_PPPIPCPDOWN,
    DCC_INFO_MPIPCPOPEN,
    DCC_INFO_MPIPCPDOWN,
    DCC_INFO_NOFIB,
    DCC_INFO_EXISTFIB,
    DCC_INFO_EXISTARP,
    DCC_INFO_ARPDETECTOK,
    DCC_INFO_NOARP,   
    DCC_INFO_PINGOK,
    DCC_INFO_PINGFAIL,
    
    DCC_INFO_NOINPCB,
    DCC_INFO_INPCB,
    DCC_INFO_NOTCPCB,
    DCC_INFO_TCPCB,
    DCC_INFO_NOSOCKETCB,
    DCC_INFO_SOCKETCB,
    DCC_INFO_NOINPCB_EISTSOCKETCB,
    DCC_INFO_NOSOCKETID,
    DCC_INFO_EXISTSOCKETID,
    DCC_INFO_NOTSAME_SOCKETTYPE,
    DCC_INFO_NOTSAMESOCKET,
    
    DCC_INFO_TCP_ISNOTBEGINCONNECT,
    DCC_INFO_TCP_ISCONNECTING,
    DCC_INFO_TCP_ISCONNECTTED,
    DCC_INFO_TCP_ISDISCONNECTING,
    DCC_INFO_TCP_TCPS_FATHERLISTEN,
    DCC_INFO_TCP_TCPS_SONLISTEN,    
    DCC_INFO_TCP_TCPS_SYN_SENT,
    DCC_INFO_TCP_TCPS_SYN_RECEIVED,
    DCC_INFO_TCP_LOCALCLOSE,
    DCC_INFO_TCP_REMOTECLOSE,
    DCC_INFO_TCP_LRCLOSE,
    DCC_INFO_TCP_TCPS_FIN_WAIT_1,
    DCC_INFO_TCP_TCPS_FIN_WAIT_2,
    DCC_INFO_TCP_TCPS_TIME_WAIT,
    DCC_INFO_TCP_TCPS_CLOSE_WAIT,
    DCC_INFO_TCP_TCPS_LAST_ACK,
    
    DCC_INFO_TCP_NOACCEPT,
    DCC_INFO_TCP_ACCEPT,
    DCC_INFO_TCP_USERCLOSE,
    DCC_INFO_TCP_TCPCLOSE,
    DCC_INFO_TCP_SHUTDOWNWRITE,
    DCC_INFO_TCP_SHUTDWONREAD,
    DCC_INFO_TCP_RECVFIN,
    DCC_INFO_TCP_SHUTDOWNRW,
    DCC_INFO_TCP_SOCKETCLOSE,
    DCC_INFO_TCP_SOCKETRWOK,

    DCC_INFO_FLOWSTAT_RCV,
    DCC_INFO_FLOWSTAT_SND,
    DCC_INFO_FLOWNOSTREAM,
    DCC_INFO_ICMPERROR_RCV,
    DCC_INFO_CREATE_DCCTIME_ERR,
    DCC_INFO_INNER_ABEND,
    DCC_INFO_DELETINTF_BYDCC,
    DCC_INFO_USERSTOP,

    DCC_INFO_END,                   /* ������ */
};


typedef enum enumDccFlowStatResult
{
    DCC_FLOW_NO_DISCARD,
    DCC_FLOW_LINK_DISCARD,
    DCC_FLOW_NETWORK_DISCARD,
    DCC_FLOW_TRAN_DISCARD,
}DccFlowStatResult_E;


/* DCC ��Ͻ�� */
enum enumDccDiagResult
{
    DCC_DIAG_SUCCESS = VOS_OK,          /* 0 û������ */
    DCC_DIAG_FAILED,               /* 1 �������� */
};

/*******************************���ݽṹ***************************************/
typedef struct tagSTREAMINFO_S
{
    ULONG   ulProType;                               /* Э������ */
    ULONG   ulSipAddr;                               /* Դ��ַ,������ */
    ULONG   ulDipAddr;                               /* Ŀ�ĵ�ַ,������ */
    USHORT  usSport;                                 /* Դ�˿ں� */
    USHORT  usDport;                                 /* Ŀ�Ķ˿ں�,������ */
}STREAMINFO;


typedef struct tagDCC_STREAMSTAT_RCV
{
    ULONG ulRcvIfIndex;/*��·��������̫����PPP*/
    
    /* LINK��ͳ����Ϣ */
    ULONG ulRcvLinkBegin;
    ULONG ulRcvLinkVlan;
    ULONG ulRcvLinkEnd;    

    /* IP��ͳ����Ϣ */   
    ULONG ulRcvIPBegin;    
    ULONG ulRcvInputAllPktIntermediateHook;  
    ULONG ulRcvInputLocalPktIntermediateHook;
    ULONG ulRcvWrongIPCheckSum;
    ULONG ulRcvIPNoFrag;    
    ULONG ulRcvIPtoIPFrag;    
    ULONG ulRcvIPFragFail;  
    ULONG ulRcvIPFragOK;  

    ULONG ulRcvIcmpBegin;
    ULONG ulRcvIcmpErrNum;
    ULONG ulRcvIcmpErrType;
    ULONG ulRcvIcmpErrCode;
    ULONG ulRcvIcmpBadCode;
    ULONG ulRcvIcmpEnd;
    ULONG ulRcvIPEnd;    

    /* TRAN��ͳ����Ϣ */ 
    ULONG ulRcvTranBegin;
    
    ULONG ulRcvTcpHook;
    ULONG ulRcvUdpInterMediate;
    ULONG ulRcvUdpHook;
    ULONG ulRcvUdpBfd;
    ULONG ulRcvRawHook;

    ULONG ulRcvTcpZeroPacket;
    ULONG ulRcvDropTcpDupPacket;
    ULONG ulRcvDropTcpQueDupPacket;
    ULONG ulRcvDropTcpAfterWinPacket;
    
    ULONG ulRcvTcpReassQuePacket;
    
    ULONG ulRcvDropTcpNotRcvMore;
    ULONG ulRcvDropTcpClose;
    
    ULONG ulRcvTranEnd;
    
    ULONG ulMbufDestroy;
    
    CHAR  cFileName[FILENAME_LEN]; /*��¼��ǰ���ú������ļ���*/
    ULONG ulFileLine;              /*��¼��ǰ���ú������к�*/
}DCC_STREAMSTAT_RCV_S;


typedef struct tagDCC_STREAMSTAT_SND
{
    ULONG ulSndIfIndex; /*��·��������̫����PPP*/
        
    /* LINK��ͳ����Ϣ */
    ULONG ulSndLinkBegin;
    ULONG ulSndETHOutHookFunc;
    ULONG ulSndMpFragNum;
    ULONG ulSndPppMuxNum;
    ULONG ulSnd3DVirtualNum;
    ULONG ulSndLinkEnd;


    
    /* IP��ͳ����Ϣ */   
    ULONG ulSndIPBegin;
    ULONG ulSndAllPktIntermediateHook;
    ULONG ulSndLocalPktIntermediateHook;
    ULONG ulSndIpOutputPPI;
    ULONG ulSndIpWholePktHook;
    ULONG ulSndIpMplsHook;
    ULONG ulSndIPNoFrag;
    ULONG ulSndIPFragOK;
    ULONG ulSndIPtoIPFrag;
    ULONG ulSndIPFragFail;
    ULONG ulSndIPEnd;

    /* TRAN��ͳ����Ϣ */ 
    ULONG ulSndTranBegin;    
    ULONG ulSndTranEnd;  

    ULONG ulMbufDestroy;

    CHAR  cFileName[FILENAME_LEN]; /*��¼��ǰ���ú������ļ���*/
    ULONG ulFileLine;              /*��¼��ǰ���ú������к�*/
}DCC_STREAMSTAT_SND_S;


typedef struct tagDCC_STREAMSTAT
{
    ULONG                ulStreamNum;              /* ���������� */
    STREAMINFO           stStreamInfo;

    DCC_STREAMSTAT_RCV_S stRcvStat;
    DCC_STREAMSTAT_SND_S stSndStat;
    
}DCC_STREAMSTAT_S;

/* ȫ��DCC��鱨��ͳ����Ϣ */
typedef struct tagDccStat
{
    ULONG ulExecID;                              /* �û����ID */
    ULONG ulDataStatTime;                        /* ͳ��ʱ��,��λ�� */
    TCPIP_DCC_S stUserDcc;                       /* �û�����DCC���� */
    ULONG ulOutIfIndexforDip;                    /* ����Ŀ�ĵ�ַ��ȡ�ĳ��ӿ����� */
    ULONG ulOutIfIndexforSip;                    /* ����Դ��ַ��ȡ�ĳ��ӿ����� */
    ULONG ulNextHopforDip;                       /* ����Ŀ�ĵ�ַ��ȡ����һ��IP*/
    ULONG ulNextHopforSip;                       /* ����Դ��ַ��ȡ����һ��IP*/
    ULONG ulHaveSteam;                           /* ��ǰ���ڶ��ٸ��� */
    DCC_STREAMSTAT_S stDccStat[DCC_MAX_STEAM];   /* ����ͳ���� */ 
}DCC_STAT_S;

typedef struct tagDccOutput
{
   ULONG  ulKindID;
   ULONG  ulIfIndex;
   ULONG  ulFatherIfIndex;
   ULONG  ulDiagnoseID;
   ULONG  ulIpAddr;
   ULONG  ulFlowSndResult;
   ULONG  ulFlowRcvResult;
   ULONG  ulFlowID;
   CHAR   szInfoBuf[1024];
 }DCC_OUTPUT_S;

/*******************************ȫ�ֱ�������***************************************/
extern ULONG g_ulDCCTimerQueId;
extern ULONG g_ulDccPktFlowEnable; /*�Ƿ�ʹ��DCC���ܿ���*/
extern DCC_STAT_S g_stDccStat;
extern ULONG g_ulDCCTaskId;
extern ULONG g_ulDccOperNum; 


/*******************************����ģ����Ҫ���õĺ�������***************************************/
extern ULONG DCC_FlowClassifyInMBuf(MBUF_S *pMBuf, ULONG ulRouteFlag, ULONG ulProType);
extern VOID DCC_FlowClassifyRcvMbuf(IFNET_S *pstIfnet, MBUF_S *pstMbuf);
extern VOID DCC_FlowClassifyMbufAtIpLayer(MBUF_S *pstMbuf, ULONG ulDirect, ULONG ulSendFlag, ULONG ulVrfIndex);
extern VOID DCC_IcmpErrorFlowCheck(MBUF_S *pstMBuf, LONG lHLen);

#ifdef  __cplusplus 
}
#endif
#endif /* _TCPIP_DCC_H_ */

