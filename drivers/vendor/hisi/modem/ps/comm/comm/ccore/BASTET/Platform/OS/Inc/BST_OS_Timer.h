

#ifndef __BST_OS_TIMER_H__
#define __BST_OS_TIMER_H__

#include "BST_Platform.h"
#include "BST_PAL_Timer.h"
#include "BST_PAL_Net.h"
#include "BST_PAL_Thread.h"
#include "BST_LIB_List.h"
#include "BST_SRV_Define.h"
#include "BST_OS_Sync.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_OS_TIMER_START_ID           ( 1 )
#define BST_OS_SleepMs( ulCnt )         ( BST_OS_PalSleepMs( ulCnt ) )
#define BST_OS_INVALID_TIMER_ID         ( BST_INVALID_SNID )
#define BST_OS_IsTimerValid( ulId )     ( BST_OS_INVALID_TIMER_ID != (ulId) )
#define BST_OS_GetTimerIdGnrtor()       ( g_cBstOsTimerIdGenrator )
#define BST_OS_TIMER_PRECISION          ( BST_OS_TICKS_MS )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
enum BST_OS_TMCB_MODE_ENUM
{
    BST_OS_TIMER_CB_FUN                 = 0,
    BST_OS_TIMER_CB_CLASS,
};
typedef BST_UINT32                      BST_OS_TMCB_MODE_ENUM_UINT32;

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_UINT32                      BST_OS_TIMERID_T;
typedef BST_VOID(*BST_OS_TIMER_CB_T)( BST_OS_TIMERID_T, BST_VOID* );

#ifdef __cplusplus

class BST_OS_CTimerCb
{
BST_PUBLIC:
    virtual BST_VOID TimerExpired( BST_OS_TIMERID_T ulId, BST_VOID* pvPara )
    {
        return;
    }
};
BST_OS_TIMERID_T BST_OS_TimerCreateCpp(
    BST_OS_CTimerCb    *pcCallBack,
    BST_VOID           *pvPara,
    BST_OS_MBX_T       *pstMsgHandle );
#endif

typedef union
{
    BST_OS_TIMER_CB_T                   pf;
#ifdef __cplusplus
    BST_OS_CTimerCb                    *pc;
#endif
}BST_OS_TIMER_CB_UNION;

typedef struct
{
    NODE                                node;
    BST_OS_TIMERID_T                    ulId;
    BST_UINT32                          ulLength;
    BST_UINT32                          ulStartTime;
    BST_UINT32                          ulStoped;
    BST_VOID                           *pvPara;
    BST_OS_MBX_T                       *pstRcver;
    BST_OS_TIMER_CB_UNION               unCallBack;
    BST_OS_TMCB_MODE_ENUM_UINT32        enCbMode;
} BST_OS_TIMER_STRU;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_VOID            BST_OS_TimerSysInit( BST_VOID );

BST_OS_TIMERID_T    BST_OS_TimerCreate(
    BST_OS_TIMER_CB_T   pfCallBack,
    BST_VOID           *pvPara,
    BST_OS_MBX_T       *pstMsgHandle );

BST_VOID            BST_OS_TimerStart(
    BST_OS_TIMERID_T    ulId,
    BST_UINT32          ulLength );

BST_VOID            BST_OS_TimerStop( BST_OS_TIMERID_T ulId );

BST_VOID            BST_OS_TimerRemove( BST_OS_TIMERID_T ulId );

BST_UINT32          BST_OS_TimeGetRemain( BST_OS_TIMERID_T ulId );

BST_BOOL            BST_OS_TimerIsStop( BST_OS_TIMERID_T ulId );

BST_OS_TIMER_STRU  *BST_OS_TimerSrch( BST_OS_TIMERID_T ulId );

BST_UINT32          BST_OS_TimerNowMs( BST_VOID );

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif
