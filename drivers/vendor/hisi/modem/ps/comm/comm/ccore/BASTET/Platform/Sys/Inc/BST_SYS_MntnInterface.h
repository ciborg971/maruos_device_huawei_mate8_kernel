

#ifndef __BST_SYSMNTN_ITF_H__
#define __BST_SYSMNTN_ITF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Typedefine.h"

#if (BST_OS_VER != BST_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_DBG_INITIAL()   BST_SYS_MntnInit()

#define BST_DBG_CONFIG_LOCAL_IP( aucLocalIp, usBufLen ) \
    BST_SYS_MntnCofigLoacalIpAddress( (BST_UINT8 *)aucLocalIp,\
                                      (BST_UINT16)usBufLen )

#define BST_DBG_ADD_TASK( usType, usTaskId )    \
    BST_SYS_MntnAddTask( (BST_UINT16)usType,    \
                         (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_STATE( usType, usTaskId, usState )   \
    BST_SYS_MntnUpdateState( (BST_UINT16)usType,            \
                             (BST_UINT16)usTaskId,          \
                             (BST_UINT16)usState )

#define BST_DBG_UPDATE_IP_INFO( usType, usTaskId, pstIpInfo )   \
    BST_SYS_MntnUpdateIpInfo( (BST_UINT16)usType,               \
                              (BST_UINT16)usTaskId,             \
                              pstIpInfo )

#define BST_DBG_UPDATE_CYC_LEN( usType, usTaskId, usCycleLen )  \
    BST_SYS_MntnUpdateCycleLen( (BST_UINT16)usType,             \
                                (BST_UINT16)usTaskId,           \
                                (BST_UINT16)usCycleLen )

#define BST_DBG_UPDATE_SUC_NUM( usType, usTaskId )      \
    BST_SYS_MntnUpdateSuccNum( (BST_UINT16)usType,      \
                               (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_ERR_NUM( usType, usTaskId )      \
    BST_SYS_MntnUpdateErrorNum( (BST_UINT16)usType,     \
                                (BST_UINT16)usTaskId )

#define BST_DBG_UPDATE_TX_FLOW( usLocalPort,ulTxFlow )  \
    BST_SYS_MntnUpdateTxFlow( (BST_UINT16)usLocalPort,  \
                              (BST_UINT32)ulTxFlow )

#define BST_DBG_UPDATE_RX_FLOW( usLocalPort,ulRxFlow )  \
    BST_SYS_MntnUpdateRxFlow( (BST_UINT16)usLocalPort,  \
                              (BST_UINT32)ulRxFlow )

#define BST_DBG_RMV_TASK( usType, usTaskId )    \
    BST_SYS_MntnRemoveTask( (BST_UINT16)usType, \
                            (BST_UINT16)usTaskId )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 STRUCT����
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
BST_VOID BST_SYS_MntnInit( BST_VOID );

BST_VOID BST_SYS_MntnCofigLoacalIpAddress(
    BST_UINT8  *aucLocalIp,
    BST_UINT16  usBufLen );

BST_VOID BST_SYS_MntnAddTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateState(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usState );

BST_VOID BST_SYS_MntnUpdateIpInfo(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_VOID   *pstIpInfo );

BST_VOID BST_SYS_MntnUpdateCycleLen(
    BST_UINT16  usType,
    BST_UINT16  usTaskId,
    BST_UINT16  usCycleLen );

BST_VOID BST_SYS_MntnUpdateSuccNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateErrorNum(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

BST_VOID BST_SYS_MntnUpdateTxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulTxFlow );

BST_VOID BST_SYS_MntnUpdateRxFlow(
    BST_UINT16  usLocalPort,
    BST_UINT32  ulRxFlow );

BST_VOID BST_SYS_MntnRemoveTask(
    BST_UINT16  usType,
    BST_UINT16  usTaskId );

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (BST_OS_VER != BST_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

