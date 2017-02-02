/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ppp_lqm.h
*
*  Project Code: VISPV100R006C02
*   Module Name: lqm  
*  Date Created: 2007-7-26
*        Author: yebo(62004)
*   Description: ��·�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2007-7-26  yebo(62004)         Create the first version.
*
*******************************************************************************/

#ifndef _LQM_DEF_H_
#define _LQM_DEF_H_


#ifdef __cplusplus
extern "C"{
#endif 

#define LQM_ADD_LEN       3    /* ����LQR����ʱ�����ӵĳ��� */
#define LQR_PACKET_FIELDLEN 48   /* LQR�����򳤶� */
#define LQM_MAXFAILTIME   3    /* ���������̽����� */
#define LQM_MAXUSABLETIME 3    /* ���������̽����� */
#define LQM_INSPECTPERIOD 10   /* ������ʱ���±��ĵļ��*/
#define MAXLOOPSBACK      10   /* ������������ */
#define LQM_MAX_PERIODVALUE 100/* �������ֵ */
#define LQM_MIN_PERIODVALUE 10/* ������Сֵ */
#define LQRPACKETLEN 52        /* LQR���ĳ���*/
#define LQM_MAX_GATE 100      /* ��ֵ���ֵ */
#define LQM_DEFAULT_PERIOD 50 /* Ĭ������*/
#define LQM_DEFAULT_GATE 80   /*Ĭ������ֵ*/
#define LQR_MAX_SENDTIME 10   /*��·̽��������*/
#define LQR_PERIOD_MINUNIT 10  /* LQR���ķ�����С���ֵ */
#define LQR_10MS_TIMERVALUE 10  /* LQR���ķ�����С���ֵ */


extern DLL_S g_stLqmDllList;       /* LQM ˫������ */
extern ULONG g_ulLqmTimerId;       /* LQM���ڷ��Ͷ�ʱ��*/

/* �˽ṹ�屣����LQR�����е�ͳ��ֵ�ֶΣ������߼��ֶ� */
typedef struct tagPppLqrInfo
{          
    ULONG   ulLastOutLQRs;   /*������LQR������*/
    ULONG   ulLastOutPackets;/*�����ı�����*/
    ULONG   ulLastOutoctets; /*�������ֽ���*/
    ULONG   ulPeerInLQRs;    /*�Զ˽��յ�LQR������*/
    ULONG   ulPeerInPackets; /*�Զ˽��յ��ֽ���*/
    ULONG   ulPeerInDiscards;/*�Զ˶����ı�����*/
    ULONG   ulPeerInErrors;  /*�Զ˽ӿڵ��Ĵ�������*/
    ULONG   ulPeerInOctets;  /*�Զ˽ӿڵ��ֽ���*/
    ULONG   ulPeerOutLQRs;   /*�Զ˷��͵�LQR������*/
    ULONG   ulPeerOutPackets;/*�Զ˷��͵ı�����*/
    ULONG   ulPeerOutOctets; /*�Զ˷��͵��ֽ���*/
    ULONG   ulSaveInLQRs;    /*���˽���LQR������*/
    ULONG   ulSaveInPackets; /*���˽��ձ�����*/
    ULONG   ulSaveInDiscards;/*���˶���������*/
    ULONG   ulSaveInErrors;  /*���˽��մ�������*/
    ULONG   ulSaveInOctets;  /*���˽����ֽ���*/
}PPPLQRINFO_S;

/*��·���Ļ�����Ϣ*/
typedef struct tagPppLqmInfo
{
    DLL_NODE_S stLqmDllNode;         /* Lqr DLL���� */
    ULONG  ulInLQRs;                 /*�˿ڽ��յ���LQR���ļ����� */
    ULONG  ulOutLQRs;                /*�˿ڷ��ͳ�ȥLQR���ĵļ����� */
    ULONG  ulNumFailure_Up;          /*�������ڹر���·���޵Ĵ���*/
    ULONG  ulNumUsable_Down;         /*�������ڻ��������������·���޵Ĵ���*/
    ULONG  ulNumInLQR_Down;          /*�������յ���LQR���ļ���,����·DOWN���Ժ�ʹ��*/
    ULONG  ulNumLQRNoEcho;           /*δ�յ�LQR����ʱ�������͵�LQR������*/
    ULONG  ulAllowSendTimeoutID;     /*������LQR���ĵ���С��ʱ��ID*/
    ULONG  ulLqmTimerSet;            /*Lqr���ķ�����������ֵ */
    ULONG  ulLqmTimerCount;          /*Lqr���ķ������ڼ���ֵ(������)*/
    
    PPPINFO_S *pstPppInfo;
    struct tagPppLqrInfo  stFirstLQR;         /* �ϴα����LQR��Ϣ */
    struct tagPppLqrInfo  stSecondLQR;        /* �����յ���LQR��Ϣ */
    struct tagPppLqrInfo  *pstLastSavedLQR;   /* �ϴα����LQR��Ϣ�ṹ��ָ�� */
    struct tagPppLqrInfo  *pstCurrentLQR;     /* �����յ���LQR��Ϣ�ṹ��ָ�� */
    ULONG bIsForbidden:1,                     /* ��ǰ��·�����ñ�־ */
          bIsAllowSendLQR:1,                  /* �Ƿ�������LQR����*/
          bIsFirstInLqr:1,                    /* �Ƿ��ǵ�һ��LQR����*/
          bReserved   : 29;                   /*reserved for later use*/
}PPPLQMINFO_S;



extern ULONG TCPIP_ADP_GetLQRStat(ULONG ulIfIndex,TCPIP_LQR_STAT_S *pstLQRStat);
extern ULONG  PPP_LQM_Delta_ulong(ULONG ulFirstNum, ULONG ulSecondNum);
extern VOID PPP_LQM_Init(PPPINFO_S  *pPppInfo);
extern VOID PPP_LQM_InputLQR(PPPINFO_S  *pPppInfo, UCHAR* pPacket, ULONG ulLen);
extern ULONG PPP_LQM_isLinkUsable(PPPINFO_S  *pPppInfo);
extern VOID PPP_LQM_LinkResume( PPPINFO_S *pPppInfo );
extern VOID PPP_LQM_SendLQR(VOID  *pPppInfo);
extern VOID PPP_LqmTimerOut(VOID *pTemp);
#ifdef __cplusplus
}
#endif 

#endif 

