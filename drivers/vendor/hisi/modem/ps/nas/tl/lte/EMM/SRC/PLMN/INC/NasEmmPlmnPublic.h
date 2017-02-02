

#ifndef __NASEMMPLMNPUBLIC_H__
#define __NASEMMPLMNPUBLIC_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasLmmPubMOsa.h"
#include  "NasEmmPlmnInterface.h"
#include  "NasLmmPubMEntry.h"


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

#define NAS_EMM_PLMN_NULL_PTR           VOS_NULL_PTR

#define NAS_EMM_PLMN_MSG_HEADER_LEN     VOS_MSG_HEAD_LENGTH

#define NAS_EMM_PLMN_OK                 VOS_OK
#define NAS_EMM_PLMN_ERR                VOS_ERR

#define NAS_EMM_PLMN_SUCC               VOS_OK
#define NAS_EMM_PLMN_FAIL               VOS_ERR

#define NAS_EMM_PLMN_BIT_SLCT           1
#define NAS_EMM_PLMN_BIT_NO_SLCT        0




#define NAS_LMM_EMM_PLMN_LOG_INFO(String)    NAS_LMM_LOG_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String)
#define NAS_LMM_EMM_PLMN_LOG_NORM(String)    NAS_LMM_LOG_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String)
#define NAS_LMM_EMM_PLMN_LOG_WARN(String)    NAS_LMM_LOG_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String)
#define NAS_LMM_EMM_PLMN_LOG_ERR(String)     NAS_LMM_LOG_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String)

#define NAS_LMM_EMM_PLMN_LOG1_INFO(String, Para1)    NAS_LMM_LOG1_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1)
#define NAS_LMM_EMM_PLMN_LOG1_NORM(String, Para1)    NAS_LMM_LOG1_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1)
#define NAS_LMM_EMM_PLMN_LOG1_WARN(String, Para1)    NAS_LMM_LOG1_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1)
#define NAS_LMM_EMM_PLMN_LOG1_ERR(String, Para1)     NAS_LMM_LOG1_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String,  Para1)

#define NAS_LMM_EMM_PLMN_LOG2_INFO(String, Para1, Para2)     NAS_LMM_LOG2_INFO(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1, Para2)
#define NAS_LMM_EMM_PLMN_LOG2_NORM(String, Para1, Para2)     NAS_LMM_LOG2_NORM(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1, Para2)
#define NAS_LMM_EMM_PLMN_LOG2_WARN(String, Para1, Para2)     NAS_LMM_LOG2_WARN(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String, Para1, Para2)
#define NAS_LMM_EMM_PLMN_LOG2_ERR(String, Para1, Para2)      NAS_LMM_LOG2_ERR(LOG_SUBMOD_ID_NAS_LMM_EMM_PLMN, String,  Para1, Para2)

/* ��ʼ��EMM��״̬ */
#define NAS_EMM_PLMN_INIT_EMMSTATE(EmmState) \
            { \
                    (EmmState).enFsmId     = NAS_LMM_PARALLEL_FSM_EMM; \
                    (EmmState).enMainState = NAS_EMM_CUR_MAIN_STAT; \
                    (EmmState).enSubState  = NAS_EMM_CUR_SUB_STAT; \
                    (EmmState).enStaTId    = TI_NAS_EMM_STATE_NO_TIMER;            \
            }

/* �������״̬: 0x��״̬_0x��״̬ */
#define NAS_EMM_PLMN_COMP_EMMSTATE(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT)\
            ((((VOS_UINT32)(NAS_EMM_MAIN_STAT)) << NAS_EMM_MOVEMENT_16_BITS) | (NAS_EMM_SUB_STAT))

#define NAS_EMM_PLMN_CHK_STAT_INVALID(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT)\
            (\
                NAS_EMM_PLMN_COMP_EMMSTATE(NAS_EMM_MAIN_STAT, NAS_EMM_SUB_STAT) != \
                NAS_EMM_PLMN_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT)\
            )

/* ����EMMҪ����XXX����Ϣ����, ������VOSͷ(�ⲿ��Ϣ) */
#define NAS_EMM_PLMN_MSG_LENGTH_NO_HEADER(XXX_EMM_MSG_STRU) \
                    (sizeof(XXX_EMM_MSG_STRU) - NAS_EMM_PLMN_MSG_HEADER_LEN)

/* ���APP��Ϣͷ */
#define NAS_EMM_PLMN_COMP_APP_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_APP; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            (pMsg)->usOriginalId        = UE_MODULE_MM_ID;\
            (pMsg)->usTerminalId        = UE_APP_SUBSYS_ID;\
        }

/* ���RRC��Ϣͷ */
#define NAS_EMM_PLMN_COMP_RRC_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_ERRC; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
        }

/* ���ESM��Ϣͷ */
#define NAS_EMM_PLMN_COMP_ESM_MSG_HEADER(pMsg, ulMsgLengthNoHeader) \
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
            (pMsg)->ulSenderPid         = PS_PID_MM; \
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
            (pMsg)->ulReceiverPid       = PS_PID_ESM; \
            (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
        }

/* ����MMҪ���͵��ڲ���Ϣ����, ������VOSͷ(�ڲ���Ϣ) */
#define NAS_EMM_PLMN_INTRAMSG_LENGTH_NO_HEADER(XXX_EMM_MSG_STRU) \
                    (sizeof(XXX_EMM_MSG_STRU) - NAS_EMM_PLMN_MSG_HEADER_LEN)

/* ���MM�ڲ���Ϣͷ */
#define NAS_EMM_PLMN_COMP_MM_INTRAMSG_HEADER(pMsg, ulMsgLengthNoHeader) \
            {\
                (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID; \
                (pMsg)->ulSenderPid         = PS_PID_MM; \
                (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID; \
                (pMsg)->ulReceiverPid       = PS_PID_MM; \
                (pMsg)->ulLength            = (ulMsgLengthNoHeader); \
            }

/* �����ڲ���Ϣ */
#define NAS_LMM_PLMN_SendIntraMsg(pMsg)  NAS_LMM_SendIntraMsg(pMsg)



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

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

#endif /* end of NasEmmPlmnPublic.h */
