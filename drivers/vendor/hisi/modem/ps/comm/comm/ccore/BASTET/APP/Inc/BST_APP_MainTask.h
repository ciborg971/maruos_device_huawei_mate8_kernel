

#ifndef __BST_APP_MAINTASK_H__
#define __BST_APP_MAINTASK_H__
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_SRV_AsEvnt.h"
#include "BST_DSPP_Report.h"
#include "BST_CORE_NPTask.h"
#include "BST_DRV_Net.h"
#include "BST_SRV_Define.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_APP_TASK_TRFCFLOW_COUNT_SIZE \
                                        ( BST_OS_SIZEOF( BST_UINT16 ) )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef struct
{
    BST_PROCID_T                usProcId;
    BST_TASKID_T                usTaskId;
    BST_IP_TRAFFIC_FLOW_STRU    strFlowInfo;
}BST_APP_TASK_TRFCFLOW_STRU;

typedef struct
{
    NODE                        node;
    BST_CORE_CNPTask           *pcNpTask;
}BST_APP_NPTASK_NODE_STRU;


class BST_APP_CMainTask :
    BST_PUBLIC BST_CTask, BST_PUBLIC BST_CORE_CAPACallBack, BST_PUBLIC BST_SRV_CAsRcver
{
BST_PUBLIC:
    static BST_APP_CMainTask   *GetInstance( BST_VOID );

    BST_VOID    Attach( BST_CORE_CNPTask *pC_NPTask );

    BST_VOID    Detach( BST_CORE_CNPTask *pC_NPTask );

    BST_ERR_ENUM_UINT8  TrafficOverFlow( BST_UINT32 ulRealFlowValue );

    BST_VOID    Entry ( BST_VOID );
BST_PRIVATE:
                BST_APP_CMainTask(
        BST_PROCID_T                usInProcID,
        BST_TASKID_T                usInTaskID );
               ~BST_APP_CMainTask( BST_VOID );

    BST_VOID    AsEventCallback(
        BST_AS_EVT_ENUM_UINT32        enEvent,
        BST_UINT32                    ulLength,
        BST_VOID                     *pData );

    BST_UINT16  Inquired(
        BST_CORE_PID_ENUM_UINT16      enParamId,
        BST_UINT16                    usDataSize,
        BST_VOID                     *const pData );

    BST_ERR_ENUM_UINT8  Configed(
        BST_CORE_PID_ENUM_UINT16      enParamId,
        BST_UINT16                    usLen,
        const BST_VOID               *const pData,
        BST_UINT8                   **pucNewAddr );

    BST_ERR_ENUM_UINT8  SaveLocalIp( NET_DRV_LOCAL_IP_INFO_STRU   *pstLocalMsg );

    BST_ERR_ENUM_UINT8  ConfigNetState( BST_NET_STATE_STRU *pstNetState );

    BST_VOID    Start( BST_VOID );

    BST_VOID    Stop( BST_VOID );

    BST_VOID    Remove( BST_VOID );

    BST_UINT16  GetTotalTrFlow(
        BST_UINT8           pucBuf[],
        BST_UINT16          usBufLen );

    LIST                                m_stNpTaskList;
    NET_DRV_LOCAL_IP_INFO_STRU          m_LocalIpInfo;
    BST_UINT32                          m_ulApSleepState;
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
