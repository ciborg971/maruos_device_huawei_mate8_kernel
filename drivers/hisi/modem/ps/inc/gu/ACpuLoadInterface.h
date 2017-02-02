

#ifndef _ACPULOAD_INTERFACE_
#define _ACPULOAD_INTERFACE_

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
/* ����CPU���ر���ĺ���ԭ�� */
typedef VOS_VOID (* CPULOAD_RPT_HOOK_FUNC )(VOS_UINT32 ulCpuLoad);


/******************************************************************************
   5 ��������
******************************************************************************/
VOS_UINT32  CPULOAD_GetCpuLoad(VOS_VOID);

VOS_VOID    CPULOAD_ResetUserDefLoad(VOS_VOID);
VOS_UINT32  CPULOAD_GetUserDefLoad(VOS_VOID);

VOS_UINT32  CPULOAD_GetRegularTimerLen(VOS_VOID);

VOS_UINT32  CPULOAD_RegRptHook(CPULOAD_RPT_HOOK_FUNC pRptHook);

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

#endif /* CpuLoadInterface.h */

