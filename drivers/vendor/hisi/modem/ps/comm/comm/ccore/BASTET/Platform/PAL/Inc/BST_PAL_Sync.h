

#ifndef __BST_PAL_SYNC_H__
#define __BST_PAL_SYNC_H__


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
#include "BST_Platform.h"

#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_sem.h"
#else
#include <semLib.h>
#endif

#include "PsLogdef.h"
#include "PsCommonDef.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (VOS_RTOSCK == VOS_OS_VER)
#define BST_PAL_IsSemInValid( hSem )    ( VOS_MAX_SEM_ID_NULL == hSem )
#else
#define BST_PAL_IsSemInValid( hSem )    ( NULL == hSem )
#endif


#if (VOS_RTOSCK == VOS_OS_VER)
#define BST_PAL_SYS_FOREVER             (OS_WAIT_FOREVER)
#define BST_PAL_SYS_NOWAIT              ( 0 )
#else
#define BST_PAL_SYS_FOREVER             ( WAIT_FOREVER )
#define BST_PAL_SYS_NOWAIT              ( NO_WAIT )
#endif


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
#if (VOS_RTOSCK == VOS_OS_VER)
typedef VOS_SEM                         BST_OS_PAL_SEM_T;
#else
typedef BST_VOID*                       BST_OS_PAL_SEM_T;
#endif


/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_OS_PalRecvSem  (
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_UINT32          ulTimeOut );

BST_ERR_ENUM_UINT8  BST_OS_PalSendSem  (
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_VOID           *pvArg );

BST_ERR_ENUM_UINT8  BST_OS_PalDeleteSem( BST_OS_PAL_SEM_T stSemHandle );

BST_OS_PAL_SEM_T    BST_OS_PalCreateSem( BST_UINT32 ulSmInit );
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
