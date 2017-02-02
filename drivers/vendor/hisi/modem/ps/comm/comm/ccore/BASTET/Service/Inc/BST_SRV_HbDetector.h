

#ifndef __BST_SRV_HB_DETECTOR_H__
#define __BST_SRV_HB_DETECTOR_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_SRV_Define.h"
#include "BST_OS_Timer.h"
#include "BST_CORE_Schd.h"
#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_SRV_DTC_MAX_LEN             ( 3U )
#define BST_SRV_DTC_SYS_DLY             ( 500U )        /* �������ݣ����·�Start��APΪ500mS */
#define BST_SRV_DTC_BAS_UNT             ( 300000U )     /* �������ڵ�λ��5���ӣ�300�룩*/
#define BST_SRV_DTC_GAD_OFS             ( 10000U )      /* ���������10��*/
#define BST_SRV_DTC_UNT_REW             ( 60000U )      /* ��λ����ʱ�䣬60��*/
#define BST_SRV_DTC_MAX_REW             ( 120000U )     /* ���������˼����120��*/
#define BST_SRV_DTC_ONE_HUR             ( 3600000 )     /* 1Сʱ����ms�� */
#define BST_SRV_DTC_THR_HUR             ( 10800000 )    /* 3Сʱ����ms�� */
#define BST_SRV_DTC_SIX_HUR             ( 21600000 )    /* 6Сʱ����ms�� */
#define BST_SRV_DTC_INI_PNT             ( 2U )          /* ����̽����ʼ��*/
#define BST_SRV_DTC_MIN_PNT             ( 1U )          /* ��С���ڵ�*/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

enum BST_SRV_DET_STATE{
    BST_SRV_DET_STATE_INIT,
    BST_SRV_DET_STATE_FORWARD,
    BST_SRV_DET_STATE_REVERSE,
    BST_SRV_DET_STATE_FINISH,
    BST_SRV_DET_STATE_BUTT
};
typedef BST_UINT8   BST_SRV_DET_STATE_ENUM_UINT8;

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/

class BST_SRV_CHbDetector
    : BST_OS_CTimerCb
{
BST_PUBLIC:
    static  BST_SRV_CHbDetector*    GetInstance     ( BST_VOID );
    BST_ERR_ENUM_UINT8              DefTask         ( BST_CORE_PTASK_NODE_STRU *pDetTask );
    BST_ERR_ENUM_UINT8              ClrTask         ( BST_VOID );
    BST_VOID                        AckSendResult   ( BST_UINT16 ucResult );
    BST_VOID                        ReStart         ( BST_VOID );
    BST_VOID                        Resume          ( BST_VOID );
    BST_VOID                        Pause           ( BST_VOID );
    BST_UINT32                      GetCurrentTick  ( BST_VOID );
    BST_VOID                        onBlock         ( BST_VOID );
    BST_VOID                        onUnBlock       ( BST_VOID );
    BST_BOOL                        IsTask          ( BST_CORE_CPTask *pcTask );
    BST_BOOL                        IsRuning        ( BST_VOID );
    BST_UINT16                      GetConfCyc      ( BST_UINT16 usInAppCyc );
BST_PRIVATE:
                                    BST_SRV_CHbDetector( BST_VOID );
    virtual                        ~BST_SRV_CHbDetector( BST_VOID );
    BST_VOID                        Initial         ( BST_VOID );
    BST_VOID                        Finish          ( BST_VOID );
    BST_VOID                        ProcHbSuc       ( BST_VOID );
    BST_VOID                        ProcHbErr       ( BST_VOID );
    BST_VOID                        RunTimer        ( BST_VOID );
    BST_ERR_ENUM_UINT8              UpdateConfCyc   ( BST_UINT8 ucPoint );
    BST_VOID                        TimerExpired    (
                                        BST_OS_TIMERID_T    ulId,
                                        BST_VOID           *pvPara );
    BST_OS_TIMERID_T                m_ulDetectingTmr;                           /*̽��ר�ö�ʱ��*/
    BST_UINT32                      m_ulDetectingOfset;                         /*ÿ��̽���ƫ����*/
    BST_UINT32                      m_ulCfmSysTick_Ms;                          /*̽���ÿ��������TICKֵ��5�������ң�*/
    BST_UINT8                       m_ucDetectingCycle;                         /*Ŀǰ����̽������ڵ�ֵ��1~3��*/
    BST_SRV_DET_STATE_ENUM_UINT8    m_enDtcState;                               /*����״̬*/
    BST_UINT8                       m_ucCfmTable[ BST_SRV_DTC_MAX_LEN + 1 ];    /*Ӧ��Ҫ��ʱ����̽��ʱ��ӳ����������10���ӣ���ôucCfmTable[3]=2*/
    BST_BOOL                        m_bIsBlocked;                               /*��ǰ�Ƿ���Block״̬*/
    BST_CORE_PTASK_NODE_STRU       *pcTaskItem;                                 /*̽����������󣨻�ΪPUSH��*/
};
/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif



#endif


