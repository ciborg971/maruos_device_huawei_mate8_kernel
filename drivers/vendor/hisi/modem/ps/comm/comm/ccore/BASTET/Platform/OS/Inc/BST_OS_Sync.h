

#ifndef __BST_OS_SYNC_H__
#define __BST_OS_SYNC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Sync.h"
#include "BST_LIB_List.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_OS_SYS_FOREVER              ( BST_PAL_SYS_FOREVER )
#define BST_OS_SYS_NOWAIT               BST_PAL_SYS_NOWAIT
#define BST_OS_SYS_TIMEOUT              ( 0xFFFFFFFFU )
#define BST_OS_SYS_IsSemValid(sem)      BST_PAL_IsSemInValid(sem)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef BST_OS_PAL_SEM_T                BST_OS_SEM_T;

typedef struct
{
    BST_OS_SEM_T                        stHandle;
#ifdef BST_OS_SIGNAL_COUNTER
    BST_UINT32                          ulCounter;
#endif
    BST_VOID                           *pvArg;
}BST_OS_SEM_STRU;

typedef struct
{
    BST_OS_SEM_STRU                    *hSem;
    LIST                                hList;
    BST_UINT32                          ulSize;
}BST_OS_MBX_T;

typedef struct
{
    NODE                                stNode;
    BST_VOID                           *ulContent;
}BST_OS_MAIL_T;

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_OS_SEM_STRU    *BST_OS_CreateSem(
    BST_VOID           *pvArg,
    BST_UINT32          ulInitCnt );
BST_UINT32          BST_OS_RecvSem(
    BST_OS_SEM_STRU    *pstSemHandle,
    BST_UINT32          ulTimeOut );

BST_ERR_ENUM_UINT8  BST_OS_SendSem(
    BST_OS_SEM_STRU    *pstSemHandle );

BST_ERR_ENUM_UINT8  BST_OS_DeleteSem(
    BST_OS_SEM_STRU    *pstSemHandle );

BST_OS_MBX_T       *BST_OS_CreateMbx(
    BST_VOID           *pvArg,
    BST_UINT32          ulSize );

BST_ERR_ENUM_UINT8  BST_OS_SendMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID           *pMsg );

BST_UINT32          BST_OS_RecvMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID          **pMsg,
    BST_UINT32          ulExTime );

BST_ERR_ENUM_UINT8  BST_OS_DeleteMbx(
    BST_OS_MBX_T       *pstMbx );

BST_UINT32          BST_OS_GetMailAmount(
    BST_OS_MBX_T       *pstMbx );

BST_UINT32          BST_OS_PeekMail(
    BST_OS_MBX_T       *pstMbx,
    BST_VOID          **pMsg );
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
