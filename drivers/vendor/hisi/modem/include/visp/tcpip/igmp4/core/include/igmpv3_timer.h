/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_timer.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP 
*  Date Created: 2008-04-10
*        Author: zengshaoyang62531
*   Description: igmp��ʱ��ģ��ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-10   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_TIMER_H_
#define _IGMPV3_TIMER_H_
    
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_CHAIN_TAIL    -1

#define IGMP_UNSOL_INT        1000L    /* [Unsolicited Report Interval] */

/*IGMP��ʱ���ص�����ָ��*/
typedef VOID (* IgmpTimeoutCall)(VOID *p,ULONG *ulDone);

typedef struct tagIgmpChainNode
{
    LONG lPrev;     /*ǰ������*/
    LONG lNext;     /*��������*/
}IgmpChainNode_S;

typedef struct tagIgmpTimerNode
{
    IgmpChainNode_S  stNode;           /*���*/
    ULONG            ulEndTimeHigh;    /*��ʱʱ��(����ڴ���ʱ��),��λ*/
    ULONG            ulEndTimeLow;     /*��ʱʱ��(����ڴ���ʱ��),��λ*/
    ULONG            ulTimerId;        /*timer id*/
    VOID             *pArg;            /*�ص������Ĳ���*/
    IgmpTimeoutCall  pfIgmpCallBack;   /*�ص�����*/
}IgmpTimerNode_S;

#define IgmpChainFirstNode(astBufHead,pstQueueHead,pstFirstNode)\
{\
    if (IGMP_CHAIN_TAIL == (pstQueueHead)->lNext)\
    {\
        pstFirstNode = NULL;\
    }\
    else\
    {\
        pstFirstNode = &(astBufHead[((pstQueueHead)->lNext)]);\
    }\
}

#define IgmpChainDelNode(astBufHead,pstQueueHead,pstNode)\
{\
    if (IGMP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext = (pstNode)->stNode.lNext;\
    }\
    else \
    { \
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode)->stNode.lNext;\
    } \
    if (IGMP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    { \
        (pstQueueHead)->lPrev =  (pstNode)->stNode.lPrev;\
    } \
    else \
    { \
        astBufHead[((pstNode)->stNode.lNext)].stNode.lPrev = (pstNode)->stNode.lPrev;\
    } \
    (pstNode)->stNode.lPrev = IGMP_CHAIN_TAIL;\
    (pstNode)->stNode.lNext = IGMP_CHAIN_TAIL;\
}

#define IgmpChainNextNode(astBufHead,pstNode,pstNextNode)\
{\
    if (IGMP_CHAIN_TAIL == ((pstNode)->stNode.lNext))\
    {\
        pstNextNode = NULL;\
    }\
    else\
    {\
        pstNextNode = &(astBufHead[((pstNode)->stNode.lNext)]);\
    }\
}

#define IgmpChainInsNode(astBufHead,pstQueueHead,pstNode,pstNewNode)\
{\
    (pstNewNode)->stNode.lNext = (pstNode) - (astBufHead);\
    if (IGMP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstNewNode)->stNode.lPrev = IGMP_CHAIN_TAIL;\
        (pstQueueHead)->lNext = (pstNewNode) - (astBufHead);\
    }\
    else\
    {\
        (pstNewNode)->stNode.lPrev =  (pstNode)->stNode.lPrev;\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNewNode) - (astBufHead);\
    }\
    (pstNode)->stNode.lPrev = (pstNewNode) - (astBufHead);\
}

#define IgmpChainAddNode(astBufHead,pstQueueHead,pstNode)\
{\
    (pstNode)->stNode.lPrev = (pstQueueHead)->lPrev;\
    (pstNode)->stNode.lNext = IGMP_CHAIN_TAIL;\
    if (IGMP_CHAIN_TAIL == ((pstNode)->stNode.lPrev))\
    {\
        (pstQueueHead)->lNext = (pstNode) - (astBufHead);\
    }\
    else\
    {\
        astBufHead[((pstNode)->stNode.lPrev)].stNode.lNext = (pstNode) - (astBufHead);\
    }\
    (pstQueueHead)->lPrev = (pstNode) - (astBufHead);\
}

/*���㶨ʱ���������ʱֵ*/
#define IGMP_TIMER_RANDOM_DELAY(ulRandomDelay) ((IGMP_Random() % (ulRandomDelay)) + 1)

extern ULONG IGMP_Random();
extern ULONG IGMP_Random_Delay(ULONG ulMaxRespTime,ULONG ulIgmpVer);
extern ULONG IGMP_Timer_Create(ULONG ulOutTime,IgmpTimeoutCall pCallBackFunc,VOID* pArg,ULONG *pulTimerId);
extern ULONG IGMP_Timer_Delete(ULONG ulTimerId);
extern ULONG IGMP_Timer_Init(IgmpTimerNode_S *pstTimerMem, ULONG ulTimerNum);
extern VOID IGMP_Timer_Out(VOID *pArg);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#endif /* _IGMPV3_TIMER_H_ */
    

