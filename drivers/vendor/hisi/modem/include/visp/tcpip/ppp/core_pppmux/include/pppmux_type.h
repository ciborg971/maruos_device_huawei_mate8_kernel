/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pppmux_type.h
*
*  Project Code: VISPV100R005
*   Module Name: PPPMUX
*  Date Created: 2006-5-11
*        Author: ZhouTong(43740)
*   Description: PPPMUXģ������Ͷ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-5-11  ZhouTong(43740)   Create
*
*******************************************************************************/

#ifndef _PPPMUX_TYPE_H_
#define _PPPMUX_TYPE_H_

#ifdef  __cplusplus
extern "C"{
#endif

#include "tcpip/ppp/include/pppmux_api.h"



/* PPPMUXCP���ƿ����ݽṹ */
typedef struct tagPppMuxcpInfo
{
    PPPINFO_S *pstPppInfo;              /* PPP���ƿ�ָ�� */
    PPPFSM_S  stFsm;                    /* MUXCPЭ��״̬�� */
    PPP_MUXCP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_MUXCP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_MUXCP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_MUXCP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
    DLL_NODE_S stPppInfoLink;           /* ����PPPЭ����ƿ������ָ�� */
} PPPMUXCPINFO_S ;

/* PPPMUX���Ͻṹ */
typedef struct tagPPPMUX_MUX_STRUCT
{
    ULONG   ulBeginHigh;        /*���Ͽ�ʼʱ��,��32λ*/
    ULONG   ulBeginLow;         /*���Ͽ�ʼʱ��,��32λ*/
    USHORT  usLastPID;          /*����Э���*/
    USHORT  usFrameLen;         /*��ǰ����֡����*/
    USHORT  usPayLoadLen;       /*��ǰ���ľ��ɳ���*/
    USHORT  usSubFrameCount;    /*��ǰ��֡����*/
    MBUF_S *pstMuxMBuf;         /*���ϱ���*/
}PPPMUXSTRUCT_S;

/* PPPMUX���������Ĵ洢�ṹ */
typedef struct tagPPPMUX_CONTEXT_STRUCT
{
    PPPMUXSTRUCT_S stMuxStructArray[MC_MAX_LSCLASS];
    PPPMUXSTATS_S  stMuxStat;
}PPPMUXCONTEXT_S;


/*PPPMUXģ����Ϣ*/
typedef struct tagMUXCP_ModInfo
{
    ULONG ulMID_PPPMUX;          /*ģ��ID*/
    ULONG ulQUE_PPPMUX_INPUT;    /*���ն���ID*/
    ULONG ulCPU_TICKS_PER_MS;    /*ÿ����CPU Ticks*/
    ULONG ulNPMode;              /*NPģʽ���*/
}PPPMUX_MOD_INFO_S;

/*shell ��coreע��Ļص���������*/
typedef struct tagPPPMUX_SHELL_CALLBACK
{
    ULONG (*pfQOS_GetPacketClass)(ULONG ulIfIndex, MBUF_S* pstMBuf,UCHAR* pulClass);    
    VOID  (*pfPPPMUX_DebugOutput)(CHAR *pInfo);
}PPPMUX_SHELL_CALLBACK_S;

/* ���Э��ѡ��� */
#define ADDCIPID(opt, neg, val) \
{\
    if (neg)\
    { \
        PPP_PUTCHAR(opt, pucPacket); \
        PPP_PUTCHAR(MUXCP_CILEN_PID, pucPacket); \
        PPP_PUTSHORT(val, pucPacket); \
    }\
}

/* �����յ���ACK����PIDѡ��� */
#define ACKCIPID(opt, neg, val) \
{\
    if (neg) \
    { \
        if ((LONG)(ulLen -= MUXCP_CILEN_PID) < 0) \
        {\
            goto bad; \
        }\
        PPP_GETCHAR(ucCiType, pucPacket); \
        PPP_GETCHAR(ucCiLen,  pucPacket); \
        if ( (ucCiLen != MUXCP_CILEN_PID) || (ucCiType != opt) ) \
        {\
            goto bad; \
        }\
        PPP_GETSHORT(usCiShort, pucPacket); \
        if (usCiShort != val) \
        {\
            goto bad; \
        }\
    }\
}

/* �����ܵ���NAK���ĵ�PIDѡ��� */
#define NAKCIPID(opt, neg, code) \
{\
    if (pstGotOptions->neg && ulLen >= MUXCP_CILEN_PID && \
        MUXCP_CILEN_PID == pucPacket[1] && pucPacket[0] == opt) \
    { \
        ulLen -= MUXCP_CILEN_PID; \
        PPP_INCPTR(MUXCP_CILEN_VOID, pucPacket); \
        PPP_GETSHORT(usCiShort, pucPacket); \
        stNoOption.neg = 1; \
        code \
    }\
}

/* �����յ���REJ����PIDѡ��� */
#define REJCIPID(opt, neg, val) \
{\
    if (pstGotOptions->neg && ulLen >= MUXCP_CILEN_PID && \
        MUXCP_CILEN_PID == pucPacket[1] && pucPacket[0] == opt) \
    { \
        ulLen -= MUXCP_CILEN_PID; \
        PPP_INCPTR(MUXCP_CILEN_VOID, pucPacket); \
        PPP_GETSHORT(usCiShort, pucPacket); \
        /* Check rejected value. */ \
        if(usCiShort != val) \
        {\
            goto bad; \
        }\
        stTryOption.neg = 0; \
    }\
}

/* Э�̽�����ɽ���,����Э�� */
#define PPP_MUXCP_NegotiationDown(pMuxcpInfo)\
{\
    PPP_MUXCP_ReceiveEventFromCore(pMuxcpInfo, (ULONG)PPP_EVENT_FSM_CLOSE, NULL); \
    PPP_MUXCP_ReceiveEventFromCore(pMuxcpInfo, (ULONG)PPP_EVENT_FSM_OPEN, NULL); \
}

#ifdef  __cplusplus
}
#endif

#endif /* end of _PPPMUX_TYPE_H_ */
