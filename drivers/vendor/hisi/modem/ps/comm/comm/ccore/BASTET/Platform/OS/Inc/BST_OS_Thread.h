

#ifndef __BST_OS_THREAD_H__
#define __BST_OS_THREAD_H__

#include "BST_Platform.h"
#include "BST_PAL_Thread.h"

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
#define BST_OS_GetCurrentThreadId()     BST_OS_PalGetCurrentThreadId()  
#define BST_OS_ThreadUnLock(lCnt)       BST_OS_PalThreadUnLock( lCnt )
#define BST_OS_ThreadLock()             BST_OS_PalThreadLock()
#define BST_OS_InitSpinLock(pLock)      BST_OS_PalInitSpinLock(pLock)
#define BST_OS_SpinLock(pLock)          BST_OS_PalSpinLock(pLock)
#define BST_OS_SpinUnLock(p,ulcnt)      BST_OS_PalSpinUnLock(p,ulcnt)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_OS_PAL_THREAD_ID            BST_OS_THREAD_ID;
typedef BST_OS_PAL_SPINLOCK_T           BST_OS_SPINLOCK_T;
typedef BST_OS_PAL_LOCKCNT_T            BST_OS_LOCKCNT_T;
/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_VOID    BST_OS_InitLock     ( BST_VOID );
BST_VOID    BST_OS_CreateThread (
    BST_INT8           *pacTaskName,
    BST_OS_THREAD_T     ThreadEntry,
    BST_VOID           *pvArg,
    BST_UINT32          ulStackSize,
    BST_UINT32          ulPrio );

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
