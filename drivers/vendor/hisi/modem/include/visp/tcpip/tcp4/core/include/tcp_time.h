/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcp_time.h
*
*  Project Code: VISP1.5
*   Module Name: IP TCP4  
*  Date Created: 2000-03-25
*        Author: Chen Bin
*   Description: TCP��ʱ����صĳ����ͺ궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2000-03-25  Chen Bin         Create the first version.
*
*******************************************************************************/
#ifndef _TCP_TIME_H
#define _TCP_TIME_H

#ifdef __cplusplus
extern "C"{
#endif

/*
 * Definitions of the TCP timers.  These timers are counted
 * down PR_SLOWHZ times a second.
 */
#define    TCPT_NTIMERS     4

#define    TCPT_REXMT       0    /* retransmit                 */
#define    TCPT_PERSIST     1    /* retransmit persistance     */
#define    TCPT_KEEP        2    /* keep alive                 */
#define    TCPT_2MSL        3    /* 2*msl quiet time timer     */

/* ʱ�䳣��  Time constants */
#define    TCPTV_MSL        (30*PR_SLOWHZ)      /* �������ʱ��           max seg lifetime (hah!) */
#define    TCPTV_SRTTBASE   0                   /* ��������ʱ��           base roundtrip time;  */
                                                /* ���ֵΪ���ʾ����֪��   if 0, no idea yet */
#define    TCPTV_SRTTDFLT   (3*PR_SLOWHZ)       /* û��������Ϣʱ�ļٶ�RTTֵ          assumed RTT if no info */
                                                                
#define    TCPTV_PERSMIN    (5*PR_SLOWHZ)        /* ����ת��ʱ��           retransmit persistance */
#define    TCPTV_PERSMAX    (60*PR_SLOWHZ)       /* ������ʱ����       maximum persist interval */                                                  
#define    TCPTV_KEEP_INIT  (75*PR_SLOWHZ)       /* ά����Ч���������     initial connect keep alive */
#define    TCPTV_KEEP_IDLE  (120*60*PR_SLOWHZ)   /* ��ѯǰ����ʱ��         dflt time before probing */
#define    TCPTV_KEEPINTVL  (75*PR_SLOWHZ)       /* Ĭ�ϲ�ѯʱ����       default probe interval */
#define    TCPTV_KEEPCNT    8                    /* ����ǰ����ѯ��Ŀ     max probes before drop */
                                                
#define    TCPTV_MIN        (1*PR_SLOWHZ)        /* ��С����ֵ         minimum allowable value */
#define    TCPTV_REXMTMAX   (64*PR_SLOWHZ)       /* �������REXMTֵ    max allowable REXMT value */
                                                 
#define    TCP_LINGERTIME   120                  /* ����ʱ��2����       linger at most 2 minutes */                                            
#define    TCP_MAXRXTSHIFT  12                   /* ���ת����Ŀ     maximum retransmits */

#define    TCP_RXTSHIFT_LOGTHRESHOLD  5             /* �ش���¼��־������ */

#ifdef    TCPTIMERS
CHAR *psTCPTimers[] =
    {  "REXMT",           /* �ش���ʱ�� */
       "PERSIST",         /* ��ֶ�ʱ�� */  
       "KEEP",            /* ���Ͷ�ʱ�� */   
       "2MSL"             /* 2MSL��ʱ�� */
    };
#endif

/* Force a time value to be in a certain range. */
#define    TCPT_RANGESET(tv, value, tvmin, tvmax) { \
    if ((ULONG)(value) < (ULONG)(tvmin)) \
        (tv) = (tvmin); \
    else if ((ULONG)(value) > (ULONG)(tvmax)) \
        (tv) = (tvmax); \
    else \
        (tv) = (SHORT)(value); \
}

#define    TCPT_ACKDELAYSTAT(cur, last, total, totaldev) { \
    total += cur; \
    if (last) \
    { \
        totaldev += (cur > last) ? (cur - last) : (last - cur); \
    } \
    last = cur; \
}

/* added by chenbin 2000.5.4 for quick tcp timer */
/* insert tcpcb into g_pstTcpFastHead */
/*#define TCPT_INSFASTTIME( pTCPCB )   \
    if( ((pTCPCB)->pNextFastTimer==NULL)&&((pTCPCB)->pPrevFastTimer==NULL)) \
    { \
        (pTCPCB)->pNextFastTimer = g_pstTcpFastHead; \
        g_pstTcpFastHead = (pTCPCB); \
    }


#define TCPT_DELFASTTIME( pTCPCB )   \
{ \
    if( (pTCPCB)->pNextFastTimer ) \
    { \
        (pTCPCB)->pNextFastTimer->pPrevFastTimer = (pTCPCB)->pPrevFastTimer; \
    } \
    if( (pTCPCB)->pPrevFastTimer ) \
    { \
        (pTCPCB)->pPrevFastTimer->pNextFastTimer = (pTCPCB)->pNextFastTimer; \
    } \
    else if( g_pstTcpFastHead == (pTCPCB) ) \
    { \
        g_pstTcpFastHead = (pTCPCB)->pNextFastTimer; \
    } \
    (pTCPCB)->pNextFastTimer = NULL; \
    (pTCPCB)->pPrevFastTimer = NULL; \
}*/


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

