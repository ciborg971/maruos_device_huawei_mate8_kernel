

#ifndef __QOS_FC_COMMON_H__
#define __QOS_FC_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CdsRabmInterface.h"
#include "FcCdsInterface.h"

#pragma pack(4)

/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef _lint
#define ACPU_PID_FC     333
#else
#define ACPU_PID_FC     UEPS_PID_FLOWCTRL_A
#endif

#define FC_MAX_RAB_NUM              (11)
#define FC_INVALID_RABID            (0xFF)
#define FC_MIN_RABID                (5)
#define FC_MAX_RABID                (15)

#define FC_MASK_RABID               (0x3f)
#define FC_MASK_MODEMID             (0x3)
#define FC_MODEMID_SHIFT            (6)

#define FC_NOT_FLOWCTRL_PRIO        (2)
#define FC_FAST_RESTORE_PRIO        (5)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern MODEM_ID_ENUM_UINT16 VOS_GetModemIDFromPid(VOS_UINT32 ulPid);

/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);
#endif
extern SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 FC_LDownUlGrade_Process (VOS_VOID);
extern SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 FC_LUpUlGrade_Process (VOS_VOID);

extern VOS_BOOL QosFc_IsDiscard(VOS_UINT8 ucRabId, MODEM_ID_ENUM_UINT16 enModemId);
extern VOS_VOID QosFc_FlowCtrl(VOS_VOID);
extern VOS_BOOL QosFc_IsInValidRabId(VOS_UINT32 ulRabId);


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

#endif /* end of QosFcCommon.h */

