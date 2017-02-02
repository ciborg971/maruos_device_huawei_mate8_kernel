

#ifndef __IMSASERVICEMANAGEMENT_H__
#define __IMSASERVICEMANAGEMENT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "ImsaMsccInterface.h"
#include "ImsaIntraInterface.h"
#include "ImsaEntity.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_PS_SIMM_INVALID                        (VOS_FALSE)
#define IMSA_DEREG_LOCAL                            (1)
#define IMSA_DEREG_NOT_LOCAL                        (0)

#ifdef PS_ITT_PC_TEST_NAS
#define TI_IMSA_START_OR_STOP_TIMER_LEN             (5*1000)
#define TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN        (5*1000)
#define TI_IMSA_PERIOD_IMS_EMC_SRV_TRY_TIMER_LEN    (5*1000)
#else
#define TI_IMSA_START_OR_STOP_TIMER_LEN             (2*1000)
#define TI_IMSA_PERIOD_IMS_SRV_TRY_TIMER_LEN        (2*1000)
#define TI_IMSA_PERIOD_IMS_EMC_SRV_TRY_TIMER_LEN    (2*1000)
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    ö����    : IMSA_NORMAL_REG_STATUS_ENUM
    ö��˵��  : ��ͨע��״̬
*****************************************************************************/
enum IMSA_NORMAL_AT_REG_STATUS_ENUM
{
    IMSA_NORMAL_AT_REG_STATUS_DEREG        = 0x00,
    IMSA_NORMAL_AT_REG_STATUS_REG          = 0x01,

    IMSA_NORMAL_AT_REG_STATUS_BUTT
};
typedef VOS_UINT32 IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32;



/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ����: IMSA_SUBSCRIPTION_INFO_STRU
 �ṹ˵��: ������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPid;
    IMSA_SUBCRIBE_TYPE_ENUM_UINT8       enType;
    VOS_UINT32                          ulPara;
    VOS_UINT32                          ulSubscriptionId;
}IMSA_SUBSCRIPTION_INFO_STRU;

/*****************************************************************************
 �ṹ����: IMSA_SUBSCRIPTION_INFO_LIST_STRU
 �ṹ˵��: ������Ϣ�б�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSubscriptionNum;                      /**< ������ */
    IMSA_SUBSCRIPTION_INFO_STRU         astSubcriptionInfoArray[IMSA_MAX_SUBSCRIPTION_NUM];/**< ������Ϣ���� */

    VOS_UINT32                          ulMaxSubscriptionId;                    /* ���������ǩԼ�� */
    IMSA_NORMAL_REG_STATUS_ENUM_UINT32  enLastNrmRegStatus;                     /* �洢�ϴ���ͨע��״̬ */
    IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 enLastNrmAtRegStatus;                 /*�洢�ϴ��ձ�ע���ϱ���AT��״̬*/
}IMSA_SUBSCRIPTION_INFO_LIST_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern IMSA_SUBSCRIPTION_INFO_LIST_STRU    g_stSubcriptionInfoList;

#define IMSA_GetSubcriptionInfoListAddr()               (&g_stSubcriptionInfoList)
#define IMSA_GetLastNrmRegStatus()                      (g_stSubcriptionInfoList.enLastNrmRegStatus)
#define IMSA_SetLastNrmRegStatus(enLastNrmRegStatus)    (IMSA_GetLastNrmRegStatus() = (enLastNrmRegStatus))
#define IMSA_GetLastNrmAtRegStatus()                      (g_stSubcriptionInfoList.enLastNrmAtRegStatus)
#define IMSA_SetLastNrmAtRegStatus(enLastNrmAtRegStatus)    (IMSA_GetLastNrmAtRegStatus() = (enLastNrmAtRegStatus))



/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID IMSA_SRV_ProcRegRegIndMsg
(
    const IMSA_REG_REG_IND_STRU        *pstRegRegIndMsg
);
extern VOS_VOID IMSA_SRV_ProcRegDeregIndMsg
(
    const IMSA_REG_DEREG_IND_STRU      *pstRegDeregIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnSetupIndMsg
(
    const IMSA_CONN_SETUP_IND_STRU     *pstConnSetupIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnRelIndMsg
(
    const IMSA_CONN_REL_IND_STRU       *pstConnRelIndMsg
);
extern VOS_VOID IMSA_SRV_ProcConnModifyIndMsg
(
    const IMSA_CONN_MODIFY_IND_STRU    *pstConnModifyIndMsg
);
extern VOS_VOID IMSA_SRV_ProcCallRsltActionIndMsg
(
    const IMSA_CALL_RESULT_ACTION_IND_STRU *pstCallRsltActionIndMsg
);
extern VOS_VOID IMSA_SRV_ProcDeregReq
(
    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause
);
extern VOS_VOID IMSA_SRV_ProcServiceChangeInd
(
    const MSCC_IMSA_SERVICE_CHANGE_IND_STRU     *pstServiceChangeInd
);
extern VOS_VOID IMSA_CONTROL_Init( VOS_VOID );

extern VOS_VOID IMSA_ProcTimerMsgPeriodTryImsSrvExp(const VOS_VOID *pRcvMsg );
extern VOS_VOID IMSA_CONTROL_ClearResource( VOS_VOID );
extern VOS_VOID IMSA_SRV_ProcCampInfoChangeInd
(
    const MSCC_IMSA_CAMP_INFO_CHANGE_IND_STRU     *pstCampInfoChangeInd
);
extern VOS_VOID IMSA_SRV_PrintNrmSrvState( VOS_VOID );
extern VOS_VOID IMSA_SRV_PrintEmcSrvState( VOS_VOID );
extern VOS_VOID IMSA_SRV_SndNrmCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
);
extern VOS_VOID IMSA_SRV_SndEmcCallSrvStatusInd
(
    IMSA_CALL_SERVICE_STATUS_ENUM_UINT32       enCallSrvStatus,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32         enNoSrvCause
);
extern IMSA_NORMAL_AT_REG_STATUS_ENUM_UINT32 IMSA_SRV_GetAtRegStatusFromSrvStatus
(
    IMSA_SRV_STATUS_ENUM_UINT8          enSrvStatus
);
extern VOS_VOID IMSA_ProcTimerMsgPeriodTryImsEmcSrvExp(const VOS_VOID *pRcvMsg );
extern VOS_UINT32 IMSA_SRV_IsHasActiveSipSignalPdp
(
    IMSA_CONN_TYPE_ENUM_UINT32          enConnType
);

extern VOS_VOID IMSA_SRV_ProcVoiceDomainChangeInd
(
    const MSCC_IMSA_VOICE_DOMAIN_CHANGE_IND_STRU     *pstVoiceDomainChangeInd
);

/* Added by zhaochen 00308719 2015-08-26 for volte,begin */
extern VOS_VOID IMSA_SRV_ProcWhenRoamNotSatisfied(VOS_VOID);
/* Added by zhaochen 00308719 2015-08-26 for volte,end */


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif

#endif /* end of ImsaServiceManagement.h */




