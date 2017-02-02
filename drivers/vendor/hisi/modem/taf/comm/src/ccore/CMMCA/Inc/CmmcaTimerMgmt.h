

#ifndef __CMMCATIMERMGMT_H__
#define __CMMCATIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* CMMCA��ͬʱ���еĶ�ʱ���������Ŀ */
#define CMMCA_MAX_TIMER_NUM             (TI_CMMCA_TIMER_BUTT)

/* ��ʱ��TI_CMMCA_WAIT_IPV6_RA_INFO��ʱ�� */
#define TI_CMMCA_WAIT_IPV6_RA_INFO_LEN  (6 * 1000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum CMMCA_TIMER_ID_ENUM
{
    TI_CMMCA_WAIT_IPV6_RA_INFO,                                                 /* �ȴ�IPV6 RA INFO��ʱ�� */

    TI_CMMCA_TIMER_BUTT
};
typedef VOS_UINT32  CMMCA_TIMER_ID_ENUM_UINT32;
enum CMMCA_TIMER_STATUS_ENUM
{
    CMMCA_TIMER_STATUS_STOP,                                                    /* ��ʱ��ֹͣ״̬ */
    CMMCA_TIMER_STATUS_RUNNING,                                                 /* ��ʱ������״̬ */
    CMMCA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 CMMCA_TIMER_STATUS_ENUM_UINT8;


enum CMMCA_TIMER_OPERATION_TYPE_ENUM
{
    CMMCA_TIMER_OPERATION_START,                                                /*������ʱ��*/
    CMMCA_TIMER_OPERATION_STOP,                                                 /*ֹͣ��ʱ��*/
    CMMCA_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_PID                             ulPid;                    /* ����Timer��PID */
    VOS_UINT32                          ulTimerName;              /* Timer�� */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;              /* ��ʱ������ */
}CMMCA_TIMER_PRECISION_STRU;
typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId;                              /* ��ʱ����ID */
    CMMCA_TIMER_STATUS_ENUM_UINT8       enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucRsv[3];                              /* ����*/
}CMMCA_TIMER_CTX_STRU;


typedef struct
{
    VOS_MSG_HEADER                                            /* _H2ASN_Skip */
    CMMCA_TIMER_ID_ENUM_UINT32            enTimerId;          /* _H2ASN_Skip */
    VOS_UINT32                            ulTimerLen;         /* ��ʱ������*/
    CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction;      /* ��ʱ���������� */
    VOS_UINT8                             aucReserved[3];
}CMMCA_TIMER_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID  CMMCA_StartTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulParam
);

VOS_VOID CMMCA_StopTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
);

CMMCA_TIMER_STATUS_ENUM_UINT8 CMMCA_GetTimerStatus(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
);

/* Deleted by wx270776 for OM�ں�, 2015-6-28, begin */
/* Deleted by wx270776 for OM�ں�, 2015-6-28, end */

#endif



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CmmcaTimerMgmt.h */
