
#ifndef _NAS_MM_ECALL_H_
#define _NAS_MM_ECALL_H_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


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

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
VOS_UINT8 NAS_MM_GetT3242ExpiredFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3242ExpiredFlg(VOS_UINT8 ucT3242ExpiredFlg);

VOS_VOID NAS_MM_SetT3243ExpiredFlg(VOS_UINT8 ucT3243ExpiredFlg);
VOS_UINT8 NAS_MM_GetT3243ExpiredFlg(VOS_VOID);

VOS_UINT8 NAS_MM_GetT3242StartNeededFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3242StartNeededFlg(VOS_UINT8 ucT3242StartNeededFlg);

VOS_UINT8 NAS_MM_GetT3243StartNeededFlg(VOS_VOID);
VOS_VOID NAS_MM_SetT3243StartNeededFlg(VOS_UINT8 ucT3243StartNeededFlg);

VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3242Expired_MmIdleNormalService(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNoCellAvailable(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_RcvT3243Expired_MmIdleNormalService(VOS_VOID *pRcvMsg);

VOS_VOID NAS_MM_StopAllTimersRelatedToEcall(VOS_VOID);

VOS_VOID NAS_MM_ClearAllEcallTimersExpiredFlg(VOS_VOID);

VOS_VOID NAS_MM_RcvMmcMmSysInfo_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmAttachReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);


VOS_VOID NAS_MM_ProcMmcMmDetachReq_MmIdleECallInactive( VOS_VOID );

VOS_VOID NAS_MM_RcvMmcMmPlmnSrchInit_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmCoverageLostInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmPowerOffReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvMmcMmWAcInfoChangeInd_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvSmsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvSsEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_RcvCcEstReq_MmIdleECallInactive(
    VOS_VOID                           *pRcvMsg
);

VOS_VOID NAS_MM_PerformECallInactivity( VOS_VOID );

VOS_VOID NAS_MM_RecordEcallTimerStartNeededFlag(VOS_VOID);

VOS_VOID NAS_MM_InitEcallInfo(VOS_VOID);

VOS_VOID NAS_MM_ClearEcallTimerInfo(VOS_VOID);

VOS_VOID NAS_MM_ProcEcallTimerStartNeededFlg(VOS_VOID);

VOS_VOID NAS_MM_ProcBufferMsg_MmIdleECallInactive( VOS_VOID );

#endif /* end of FEATURE_ECALL */


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

#endif /* end of NasMmEcall.h*/
