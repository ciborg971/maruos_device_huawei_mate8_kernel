

#ifndef __BST_CORE_P_TASK_H__
#define __BST_CORE_P_TASK_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_Task.h"


#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_CORE_GetCycleToMs(ulCyc)    ( (ulCyc)*BST_SRV_DTC_BAS_UNT )
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
class BST_CTaskSchdler;
class BST_SRV_CHbDetector;

class BST_CORE_CPTask :
    BST_PUBLIC BST_CTask
{
BST_PUBLIC:
    BST_ERR_ENUM_UINT8                  ConfigCycleTicks( BST_UINT32 ulTickFct );
    BST_VOID                            Suspend         ( BST_VOID );
    BST_VOID                            Maintain        ( BST_VOID );
    BST_VOID                            Waiting         ( BST_VOID );
    BST_UINT32                          IsBusy          ( BST_VOID );
    BST_VOID                            Finished        ( BST_VOID );
    BST_VOID                            TxStart         ( BST_VOID );
    virtual BST_VOID                    onUpdateCycle   ( BST_UINT16 ulDetCycle );
    virtual BST_VOID                    onCycleError     ( BST_VOID );
    BST_VOID                            onExecute       ( BST_VOID );
    friend class                        BST_CTaskSchdler;
    friend class                        BST_SRV_CHbDetector;
BST_PROTECTED:
    BST_TICK_T                          m_ulCycle;
    BST_TICK_T                          m_ulSuspCounter;
    BST_UINT32                          m_ulBusyFlag;
                                        BST_CORE_CPTask ( BST_PROCID_T in_usProcId,
                                                          BST_TASKID_T in_usTaskId );
    virtual                            ~BST_CORE_CPTask ( BST_VOID );
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


