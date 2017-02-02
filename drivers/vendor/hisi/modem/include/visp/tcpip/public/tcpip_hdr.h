/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                               tcpip_hdr.h
*
*  Project Code: VISPV100R007C03
*   Module Name: PUBLIC  
*  Date Created: 2009-02-28
*        Author: zhangchi
*   Description: VISP �������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   zhangchi                Create
*******************************************************************************/
#ifndef _TCPIP_HDR_H_
#define _TCPIP_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

/* ����������10000���� */
#define HEALTH_MAX_TIME    10000

/* ��챨����󳤶� */
#define HEALTH_MAXMSG_LEN           2048       

/* �������� */
#define TYPE_HEALTH_CHECKUP         1
#define TYPE_LASTWORD_CHECKUP       2

/* HEALTH��ʱ����ʱ�� */
#define HEALTH_DELAY_TIME           1          

/* ���С�������Ҫ�õ���һЩ�궨�� */
#define HDR_TQDEPTH                     2048         /* ��ʱ�����г��� */
#define HDR_HQDEPTH                    (2048 * 4)    /* ��챨����г��� */
#define HDR_LQDEPTH                    (2048 * 4)    /* ��־���г��� */
#define HDR_QMODE                      VOS_Q_FIFO   /* ���б�־ */

#define CC_HQDEPTH                      (1024)       /* CC������г��� */
#define CC_QMODE                      VOS_Q_FIFO     /* CC���б�־ */

#define HDR_LASTWORD_MIN_MEMSIZE     1024

#define HDR_MAX_TASK_PRI             255         /* HDR����������ȼ� */


/* ���ģ��ʹ�ܱ�� */
#define HEALTH_CHECKUP_BASIC         0x00000001
#define HEALTH_CHECKUP_ETH           0x00000002
#define HEALTH_CHECKUP_PPP           0x00000004
#define HEALTH_CHECKUP_POEC          0x00000008
#define HEALTH_CHECKUP_POES          0x00000010
#define HEALTH_CHECKUP_DHCP4C        0x00000020
#define HEALTH_CHECKUP_DHCP4R        0x00000040
#define HEALTH_CHECKUP_BFD           0x00000080
#define HEALTH_CHECKUP_OAM3AH        0x00000100
#define HEALTH_CHECKUP_OAM1AG        0x00000200
#define HEALTH_CHECKUP_IGMP          0x00000400
#define HEALTH_CHECKUP_TRUNK         0x00000800
#define HEALTH_CHECKUP_MSTP          0x00001000
#define HEALTH_CHECKUP_MP            0x00002000
#define HEALTH_CHECKUP_PP4           0x00004000
#define HEALTH_CHECKUP_ALL           0xFFFFFFFF

/* ��������ģ��ʹ�ܱ�� */
#define LASTWORD_CHECKUP_IFNET       0x00000001
#define LASTWORD_CHECKUP_PUBLIC      0x00000002
#define LASTWORD_CHECKUP_PPP         0x00000004
#define LASTWORD_CHECKUP_TRUNK       0x00000008
#define LASTWORD_CHECKUP_MP          0x00000010
#define LASTWORD_CHECKUP_ETH         0x00000020
#define LASTWORD_CHECKUP_PP4         0x00000040
#define LASTWORD_CHECKUP_BFD         0x00000080
#define LASTWORD_CHECKUP_ALL         0xFFFFFFFF

/* OUTPUT�¼�λ���� */
#define OUTPUT_LOG_EVENT             0x00000001      /* ��־����¼� */
#define OUTPUT_HEALTH_EVENT          0x00000002      /* ��챨���¼� */
#define OUTPUT_CC_EVENT              0x00000004      /* CC����¼� */
#define OUTPUT_TIMER_ENVNT           ( 1 << 15 )     /* ��ʱ����ʱ�¼� */

/* ��챨����ȴ������� */
#define HDR_SCHED_NUM_MIN            32
#define HDR_SCHED_NUM_MAX            512

#define HDR_LASTWORD_MIN_MEMBUF         32768          /* ����������Сѹ������32K */
#define HDR_LASTWORD_COMPRESSHEAD       0xDCBADCBA
#define OFFSET_CODING_LENGTH (6)
#define MAX_WND_SIZE 64
#define OFFSET_MASK_CODE (MAX_WND_SIZE-1)
#define HDR_COMPRESS_M 3

/* HEALTHд��Ϣ���к궨��*/ 
#define HEALTH_WriteQueue(ulQueueId,ulMsg,ul_Ret) \
{ \
    ul_Ret = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* HEALTHд�����¼��궨�� */
#define HEALTH_SchedTask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulTCPIPOutputTaskId, ulEvent ); \
}

/* CCд��Ϣ���к궨��*/ 
#define CC_WriteQueue(ulQueueId,ulMsg,ul_Ret) \
{ \
    ul_Ret = VOS_Que_Write (ulQueueId, ulMsg, VOS_NO_WAIT | VOS_NORMAL, 0);\
}

/* CCд�����¼��궨�� */
#define CC_SchedTask(ulEvent) \
{ \
    (VOID)VOS_Ev_Write( g_ulTCPIPOutputTaskId, ulEvent ); \
}

typedef struct tagHealthMsgHead
{
    ULONG         ulMsgType;
    ULONG         ulSeq ; 
    TCPIP_TIME_S    stTime;
    USHORT        usModID;
    USHORT        usMsgLen;
    ULONG         ulMsgNum;
}HDR_MSG_HEAD_S;

typedef struct tagHDR_TLVHEAD
{
    USHORT usType;
    USHORT usLen;
}HDR_TLVHEAD_S;


#define OUTPUT_FIXLEN     1
#define OUTPUT_VARLEN     2

/* ������־��Ϣ����ṹ */
typedef struct tagTCPIP_FIXLEN_OUTPUT
{
    ULONG ulCode;
    ULONG ulLogLevel;
    ULONG ulLogType;
    UCHAR ucMessage[LEN_256];
    ULONG ulPara1;
    ULONG ulPara2;
    ULONG ulPara3;
    ULONG ulPara4;
}TCPIP_FIXLEN_OUTPUT_S;

/* �䳤��־��Ϣ����ṹ */
typedef struct tagTCPIP_VARLEN_OUTPUT
{
    ULONG ulCode;
    ULONG ulLogLevel;
    ULONG ulLogType;
    UCHAR ucMessage[LEN_256];
    UCHAR ucPara[LEN_256];
}TCPIP_VARLEN_OUTPUT_S;

typedef struct tagLASTWORD_COMPRESSHEAD
{
    ULONG ulCompressHead;
    ULONG ulCompressLen;
}LASTWORD_COMPRESSHEAD_S;

typedef enum enumHEALTHMID
{
    HEALTH_MID_MIN,
    HEALTH_MID_IFNET = 1,   /* 1 */
    HEALTH_MID_IP,          /* 2 */
    HEALTH_MID_ETHARP,      /* 3 */
    HEALTH_MID_TRUNK,       /* 4 */
    HEALTH_MID_PPP,         /* 5 */
    HEALTH_MID_POES,        /* 6 */
    HEALTH_MID_PPPOE,       /* 7 */
    HEALTH_MID_DHCP4C,      /* 8 */
    HEALTH_MID_DHCP4R,      /* 9 */
    HEALTH_MID_SFIB,        /* 10 */
    HEALTH_MID_SOCKET,      /* 11 */
    HEALTH_MID_BFD,         /* 12 */
    HEALTH_MID_PUBLIC,      /* 13 */
    HEALTH_MID_TCP,         /* 14 */
    HEALTH_MID_OAM3AH,      /* 15 */
    HEALTH_MID_OAM1AG,      /* 16 */    
    HEALTH_MID_IGMP,        /* 17 */
    HEALTH_MID_MSTP,        /* 18 */
    HEALTH_MID_MP,          /* 19 */
    HEALTH_MID_PP4,         /* 20 */
    
    HEALTH_MID_MAX, /* VISP�ڲ�ģ������ޣ�������ֵ��Ϊ�ⲿע���ģ��� */
}HEALTHMID_E;


/* ��Ϣ�ײ����� */
typedef enum enumHEALTH_TYPE
{
    HEALTH_IF_STATUS,
    HEALTH_PUBLIC_MEMINFO,
    HEALTH_PUBLIC_MBUFMIDSTAT,
    HEALTH_PUBLIC_MBUFCACHE,
    HEALTH_IF_STATISTIC,
    HEALTH_3AH_STATISTIC,
    HEALTH_3AH_FSMSTATE,
    HEALTH_ETH_STATICARPUPDATE,
    HEALTH_ETH_DYNAMICARPUPDATE,
    HEALTH_ETH_ARPRESOLVEFAIL,
    HEALTH_ETH_STATISTIC,
    HEALTH_ETH_ARPPROXYREPLY,
    HEALTH_MSTP_STATISTIC,
    HEALTH_MSTP_HISTORY,
    HEALTH_PPP_STATISTIC,
    HEALTH_PPP_STATUSINFO,
    HEALTH_PPP_LCPINFO,
    HEALTH_PPP_IPCPINFO,
    HEALTH_MP_STATISTIC,    
    HEALTH_MP_BINDINFO, 
    HEALTH_TRUNK_INFO,        /* trunk */
    HEALTH_TRUNKPORT_INFO,
    HEALTH_MP_SUBINFO,
    HEALTH_PPP_IP6CPINFO,/* Added by hanna55555, BC3D01693, 2009/6/24 */
    HEALTH_PPP_PPPMUXCPINFO,
    HEALTH_PUBLIC_NPSTAT,
    HEALTH_PUBLIC_CTLMSGSTAT,
    HEALTH_PP4_IFSTAT,
    HEALTH_PP4_STATISITC,
    HEALTH_BFD_SESSIONINFO,
    HEALTH_BFD_NPINFO,
}HEALTH_TYPE_E;

/* ��Ϣ�ײ����� */
typedef enum enumLASTWORD_TYPE
{
    LASTWORD_IF_STATUS,
    LASTWORD_PUBLIC_MEMINFO,
    LASTWORD_PUBLIC_MBUFMIDSTAT,
    LASTWORD_PUBLIC_MBUFCACHE,
    LASTWORD_MP_BINDINFO,
    LASTWORD_PPP_STATUS,
    LASTWORD_TRUNK_BINDINFO,
    LASTWORD_MP_SUBINFO,
    LASTWORD_PUBLIC_NPSTAT,
    LASTWORD_ETH_STATISTIC,
    LASTWORD_PP4_STATISTIC,
    LASTWORD_PP4_IFSTAT,
    LASTWORD_PPP_STATISTIC,
    LASTWORD_MP_STATISTIC,
    LASTWORD_BFD_SESSIONINFO,
}LASTWORD_TYPE_E;

extern ULONG g_ulHealthTimerId;
extern ULONG g_ulTCPIPOutputTaskId;
extern ULONG g_ulHealthQueId;
extern ULONG g_ulLogQueId;
extern ULONG g_ulHDRTimerQueId;
extern ULONG g_ulHeadthBatchFlag;
extern ULONG g_ulHealthSeq;
extern ULONG g_ulLastwordSeq;
extern ULONG g_ulHealthScanId;
extern ULONG g_ulLastwordItems;
extern ULONG g_ulLastwordMemSize;
extern ULONG g_ulLastwordBatchFlag;
extern ULONG g_ulHdrInitFlag;
extern ULONG g_ulCCQueId;

/* ���ý������ͷ�ĺ� */
#define HEALTH_HEAD_SET(pucData,usMidId,usMsgType,usMsgOffset,usItemNum)\
{\
    HDR_MSG_HEAD_S *pstHealthHead; \
    pstHealthHead = (HDR_MSG_HEAD_S *)pucData;\
    pstHealthHead->ulMsgType = usMsgType;\
    pstHealthHead->ulSeq = g_ulHealthSeq++;\
    (VOID)TCPIP_Get_CurrentTime((VOID *)&pstHealthHead->stTime);\
    pstHealthHead->usModID = usMidId;\
    pstHealthHead->usMsgLen = usMsgOffset;\
    pstHealthHead->ulMsgNum = usItemNum;\
}

/* ����TLVͷ */
#define HEALTH_TLV_HEAD_SET(pstHealthTlv,usTlvType,usValueLen)\
{\
    (pstHealthTlv)->usType = (usTlvType);\
    (pstHealthTlv)->usLen = (usValueLen) + (sizeof(HDR_TLVHEAD_S));\
}


extern VOID TCPIP_Health_TimerExpire(VOID *pData);
extern ULONG TCPIP_HDR_GetCompVtbl(VOID);
extern VOID TCPIP_Output_Task(UINTPTR ul1, UINTPTR ul2, UINTPTR ul3, UINTPTR ul4);
extern VOID TCPIP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG TCPIP_Health_OutputMsg(UCHAR * pucData, USHORT usDataLen);
extern VOID TCPIP_HDR_FixLen_LogOutput(TCPIP_FIXLEN_OUTPUT_S *pstLogFixLen);
extern VOID TCPIP_HDR_Valen_LogOutput(TCPIP_VARLEN_OUTPUT_S *pstLogValen);
extern VOID TCPIP_WriteOneBit(UCHAR* pcBuf, ULONG ulOffset);
extern VOID TCPIP_ClearOneBit(UCHAR* pcBuf,ULONG ulOffset);
extern ULONG TCPIP_WriteGolomb(ULONG ulCodeNum,UCHAR* pBuffer,ULONG ulBitOffset);
extern ULONG TCPIP_MemCmp(UCHAR* ucStr1,UCHAR* ucStr2,ULONG ulLen);
extern VOID TCPIP_MatchLength(UCHAR* pSourceString,UCHAR* pString,ULONG ulSourceStringLength,
                                ULONG* pulSubstringOffset,ULONG* pulSubstringLength);
extern ULONG TCPIP_CompressData(UCHAR* pDataBuffer,ULONG ulDataLength,UCHAR* pOutputBuffer,ULONG* pulNumOfBits);

#ifdef  __cplusplus 
}
#endif
#endif /* _TCPIP_HDR_H_ */



