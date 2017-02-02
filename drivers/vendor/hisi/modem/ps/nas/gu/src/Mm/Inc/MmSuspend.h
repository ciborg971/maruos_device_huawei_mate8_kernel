

#ifndef _MM_SUSPEND_H_
#define _MM_SUSPEND_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MmSelf.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MM_CONNECT_EXIST                0                   /* MM ���Ӵ��ڻ����ڽ� MM ���� */
#define MM_CONNECT_NOT_EXIST            1                   /* MM ���Ӳ����� */

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*ģ���������士HEADER
 */


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*Identification ��ʶ��MM_TIMER_ST
Type ���ͣ�
PurposeĿ�ģ���ʱ���ṹ*/
/* ucTimerStatus ȡֵ */
#define MM_TIMER_STOPPED                0
#define MM_TIMER_START                  1

typedef struct
{
    HTIMER          stTimer;
    VOS_UINT32      ulTimerLength;
    VOS_UINT8       ucTimerStatus;
}MM_TIMER_ST;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

VOS_VOID MM_SaveMsg(const VOS_VOID* pMsg, VOS_UINT8 ucEventId, VOS_UINT32 ulLength);

VOS_VOID MM_SndMsgFuncChg(VOS_VOID);

VOS_VOID MM_RetransferMsg(VOS_VOID);
VOS_VOID MM_Restore(VOS_VOID);

VOS_VOID MM_InsertMsg(VOS_VOID *pMsg, VOS_UINT8 ucEventId);

MM_SUSPEND_MSG_CELL_ST* MM_GetMsg(VOS_VOID);

VOS_VOID MM_RelMsgBuf(VOS_VOID);

VOS_VOID MM_SuspendTimeout(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_ProcResumeIndBackToLTE(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);
#endif

VOS_VOID NAS_MM_ResumeSuspendInfo(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);

VOS_VOID NAS_MM_ProcResumeIndBackToGU(
    MMCMM_RESUME_IND_STRU              *pstResumeMsg
);

VOS_VOID  NAS_MM_ChgStateIntoLMode( VOS_VOID );

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID NAS_MM_ProcResumeIndBackToGU_Srvcc(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MM_ProcResumeIndBackToLTE_Srvcc(VOS_VOID);
#endif
VOS_VOID NAS_MM_ProcSrvccFail(VOS_VOID);
VOS_VOID NAS_MM_ProcSrvccSuccess(VOS_VOID);
#endif


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmSuspend.h*/
