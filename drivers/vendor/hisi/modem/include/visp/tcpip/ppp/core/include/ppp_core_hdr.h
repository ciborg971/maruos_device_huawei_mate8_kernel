/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                                ppp_core_hdr.h
*
*  Project Code: VR7C03
*   Module Name: ppp  
*  Date Created: 2009-02-28
*        Author: L00105073/Z00104483
*   Description: ppp��챨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-02-28   L00105073/Z00104483     Create
*
*******************************************************************************/

#ifndef _PPP_CORE_HDR_H_
#define _PPP_CORE_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif
/* PPP�ӿ���챨�����ݽṹ */

/* PPPͳ����챨�� */
typedef struct tagPPP_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    PPPSTATISTIC_S stPPPStatistic;
} PPP_HEALTH_STATISTIC_S;

/* PPPͳ����챨�� */
typedef struct tagPPP_HEALTH_STATUSINFO
{
    ULONG ulIfIndex;
    ULONG ulPhase;
    ULONG ulMpChannelType;
}PPP_HEALTH_STATUSINFO_S;

/* ppp��Э����Ϣ��챨�� */
typedef struct tagPPP_HEALTH_SONPROTOCOL_INFO
{
    ULONG   ulIfIndex;
    ULONG   ulState;               /* Э��״̬ */
    ULONG   ulDownReason;          /* ��¼������(down��close�¼�)���µ�PPPЭ��downԭ�� */
}PPP_HEALTH_SONPROTOCOL_INFO_S;

/* ppp��Э������������Ϣ */
typedef struct tagPPP_LASTWORD_STATUS
{
    ULONG   ulIfIndex;          /* �ӿ����� */
    UCHAR   ucPppPhase;         /* PPP��Э��״̬ */
    UCHAR   ucLcpState;         /* LCP��Э��״̬ */    
    UCHAR   ucLcpDownReason;    /* LCP DOWN ��ԭ�� */      
    UCHAR   ucIpcpState;        /* IPCP��Э��״̬ */       
    UCHAR   ucIpcpDownReason;   /* IPCP DOWN ��ԭ�� */  
    /* Added by hanna55555, BC3D01693, 2009/6/24 */
    UCHAR   ucIp6cpState;        /* IP6CP��Э��״̬ */       
    UCHAR   ucIp6cpDownReason;   /* IP6CP DOWN ��ԭ�� */       
    UCHAR   ucPPPMuxcpState;     /* PPPMuxCP��Э��״̬ */       
    UCHAR   ucPPPMuxcpDownReason;/* PPPMuxCP DOWN ��ԭ�� */       
    UCHAR   ucRev[3];
    /*End of Added by hanna55555, 2009/6/24 */
}PPP_LASTWORD_STATUS_S;

extern VOID PPP_Health_BatchCheckup(VOID);
extern ULONG PPP_Health_StatisticCheckup(VOID);
extern ULONG PPP_Health_StatusInfoCheckup(VOID);
extern ULONG PPP_Health_LcpInfoCheckup(VOID);
extern ULONG PPP_Health_IpcpInfoCheckup(VOID);
/* Added by hanna55555, BC3D01693, 2009/6/24 */
extern ULONG PPP_Health_Ip6cpInfoCheckup(VOID);
/*End of Added by hanna55555, 2009/6/24 */
extern ULONG PPP_Health_PPPMuxcpInfoCheckup(VOID);
extern ULONG PPP_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);
extern ULONG PPP_LastWord_StatisticCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif

