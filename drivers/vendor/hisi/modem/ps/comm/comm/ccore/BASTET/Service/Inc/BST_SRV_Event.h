

#ifndef __BST_SRV_EVENT_H__
#define __BST_SRV_EVENT_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_SRV_Define.h"

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
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/

/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/
BST_UINT32  BST_SRV_ApiSendAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_UINT32 BST_SRV_ApiSendLwipAsEvent(
    BST_VOID               *pcInAsRcver,
    BST_AS_EVT_ENUM_UINT32  enAsEvent,
    BST_UINT32              ulLength,
    BST_VOID               *pvData );

BST_UINT32  BST_SRV_ApiSendPTaskEvent(
    BST_VOID               *pvTask,
    BST_UINT16              enComdId,
    BST_UINT16              usContnt );

BST_UINT32  BST_SRV_ApiSendAcomRxEvent(
    BST_UINT32              ulLength,
    BST_UINT8              *pucData );

BST_UINT32  BST_SRV_ApiSendExpiredEvent(
    BST_VOID               *pstRcvHandle,
    BST_UINT32              ulTimerId );

BST_UINT32  BST_SRV_ApiSendTcpIpEvent(
    BST_VOID               *pstRcver,
    BST_VOID               *pstEvent );

BST_UINT32 BST_SRV_ApiSendDsppEvent(
    BST_UINT32             ulMsgId,
    BST_UINT32             ulApVer,
    BST_UINT32             const ulBufLen,
    BST_VOID              *const pstHeadInfo,
    BST_VOID              *pstRcvHandle );

BST_VOID    BST_SRV_ProcSysEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID    BST_SRV_ProcAppEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID BST_SRV_ProcChnlCtrEvent(
    BST_EVT_HEAD_STRU      *pstEvent );

BST_VOID BST_SRV_EvtProcLwipExpired(
    BST_VOID               *pstLwipMsg );

BST_VOID BST_SRV_EvtProcLwipAsEvent(
    BST_VOID               *pstLwipMsg );

BST_VOID BST_SRV_InitInstance( BST_VOID );

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#ifdef __cplusplus
#if    __cplusplus
           }
#endif
#endif


#endif
