

#ifndef _PP4_HDR_H_
#define _PP4_HDR_H_

#ifdef  __cplusplus
extern "C"{
#endif

typedef struct tagPP4_HEALTH_STATISTIC
{
    ULONG ulIfIndex;
    IPIFSTAT_S stPP4Statistic;
}PP4_HEALTH_STATISTIC_S;

extern VOID IP_PP4_Health_BatchCheckup();
extern ULONG IP_PP4_Health_IFStatisticCheckUp();
extern ULONG IP_PP4_Health_StatisticCheckUp();
extern ULONG IP_PP4_LastWord_BatchCheckup(CHAR *pstBuf, ULONG *pulLastWordLen);

#ifdef  __cplusplus
}
#endif
#endif


