/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              igmpv3_query.h
*
*  Project Code: VISPV100R007
*   Module Name: IGMP  
*  Date Created: 2008-03-11
*        Author: zengshaoyang62531
*   Description: ����igmp queryģ���ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-11   zengshaoyang62531       Create
*
*******************************************************************************/
#ifndef _IGMPV3_QUERY_H
#define _IGMPV3_QUERY_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define IGMP_MIN_QUERY_LGENTH       8          /*igmp��ѯ���ĵ���С����*/
#define IGMPV3_MIN_QUERY_LENGTH     12         /*igmpv3��ѯ���ĵ���С����*/
#define IGMPV3_MIN_REPORT_LENGTH    16         /*igmpv3���汨�ĵ���С����*/

#define IGMP_INIT_ROBVAR        2          /*Default robustness variable values*/
#define IGMP_INTI_QUERYINT      125        /* Default query query interval */
#define IGMP_DEF_QRYMRT         10         /*Version.1 max response time*/
#define IGMP_TIME_SCALE         1000
#define IGMP_TIME_UNIT          10         /*ʱ�䵥λ,10��ʾ1s*/
#define IGMP_TIME_BASE          100        /*���ֵ * IGMP_TIME_BASE��ת��Ϊms*/

#define IGMP_MAXSOURCES(len)    (((len)-12)>>2)

typedef enum tagIGMP_COMPATIBLE_VAR
{
    IGMP_VER1 = 1,         /*igmpv1*/
    IGMP_VER2,             /*igmpv2*/
    IGMP_VER3              /*igmpv3*/
}IGMP_COMPATIBLE_VAR_E;

/*IGMPV3 ��ѯ�����ײ����ݽṹ*/
typedef struct tagIGMPV3_QUERY
{
    UCHAR  ucType;             /* ���� */
    UCHAR  ucCode;             /* �����Ӧ���� */
    USHORT usChkSum;           /* checksum */
    ULONG  ulGrpAddr;          /* group address */
    
    #if VRP_LITTLE_ENDIAN == VRP_YES
        UCHAR  ucQRV:3;        /* Querier's Robustness Variable */
        UCHAR  ucSFlag:1;      /* Suppress Router-Side Processing flag */
        UCHAR  ucResv:4;       /* resvered */
    #else
        UCHAR  ucResv:4;       /* resvered */
        UCHAR  ucSFlag:1;      /* Suppress Router-Side Processing flag */
        UCHAR  ucQRV:3;        /* Querier's Robustness Variable */
    #endif
    
    UCHAR  ucQQIC;             /* Querier's Query Interval Code */
    USHORT usSrcNums;          /* numbers of sources */ 
    ULONG ulSrcAddr[1];        /* Դ��ַָ�룬һ��Ҫ��֤�ڴ���������ֹ���ʷǷ��ڴ�*/
}IGMPV3_QUERY_S;

/*IGMP�����ײ����ݽṹ*/
typedef struct tagIGMPHDR
{
    UCHAR  ucType;             /* ���� */
    UCHAR  ucCode;             /* code */
    USHORT usChkSum;           /* checksum */
    ULONG  ulGrpAddr;          /* group address */
}IGMPHDR_S;

extern VOID IGMP_CheckIfCompatibleVar(IPIFNET_S *pstIpCtl);
extern ULONG IGMP_CreatOrRefresh_Timer(ULONG *pulTimerID,ULONG ulTime,ULONG ulGrpAddr,
    ULONG ulIfIndex,ULONG ulTimerType);
extern VOID IGMP_Input(MBUF_S *pstMBuf, LONG lHLen);
extern ULONG IGMP_Record_Sources(IPMULTI_S *pstIPMulti,USHORT usSrcNums,INADDR_S *pstSrc);
extern ULONG IGMP_Schedule_Curstate_Reports(MBUF_S *pstMBuf,IPIFNET_S *pstIpctl,
                                                       ULONG ulIgmpLen,ULONG ulMrt);
extern ULONG IGMP_Timer_NeedRefresh(ULONG ulNewRandTime,ULONG ulTimerID);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
