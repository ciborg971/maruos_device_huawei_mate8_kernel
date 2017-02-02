

#ifndef __NASESMPUBLIC_H__
#define __NASESMPUBLIC_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "EmmEsmInterface.h"
#include "EsmRabmInterface.h"
#include "AppEsmInterface.h"
#include "PsLogdef.h"
#include "OmCommon.h"
#include "Msp_diag_cmd_id.h"
#include  "NasCommPrint.h"
#include "LPsNvInterface.h"
#include "NasCommBuffer.h"
#include "PsLib.h"
#include "SmEsmInterface.h"
#include "UsimPsInterface.h"


#include "product_config.h"

#include "NasFileId.h"


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
  2 Macro
*****************************************************************************/
#define NAS_ESM_NULL                    (0)

#define NAS_ESM_OP_TRUE                 (1)
#define NAS_ESM_OP_FALSE                (0)

#define NAS_ESM_BIT_0                   (1)

#define NAS_ESM_USIM_BACKOFF_PARA_LEN         32
#define NAS_ESM_USIM_BACKOFF_PARA_ADDR_LEN    3

#define NAS_ESM_BACKOFF_IGNORE_FX_DEFAULT_VALUE   60
#define NAS_ESM_BACKOFF_PERM_FX_DEFAULT_VALUE     30
#define NAS_ESM_BACKOFF_TEMP_FX_DEFAULT_VALUE     60

#define NAS_ESM_MAX_PTI_BUFF_ITEM_NUM   (10)                /* ���PTI�����¼���� */
#define NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM   (10)          /* ���ATTACHING�����л����¼���� */

#define NAS_ESM_MAX_EPSB_NUM            (11)                /*��������*/
#define NAS_ESM_MAX_STATETBL_NUM        (11)                /*���̬����*/
/*lint -e961*/
#define NAS_ESM_ILL_STATETAL_INDEX      (0xffffffff)        /*�Ƿ���̬��������*/
/*lint +e961*/
#define NAS_ESM_MAX_EPSB_ID             (15)                /*���ĳ��غ�*/
#define NAS_ESM_MIN_EPSB_ID             (5)                 /*��С�ĳ��غ�*/
#define NAS_ESM_UNASSIGNED_EPSB_ID      (0)                 /*δ����ĳ��غ�*/

#define NAS_ESM_MAX_SDF_PF_NUM          (16)                /*SDF��֧�ֵ����PF��*/
#define NAS_ESM_MAX_FLOW_LABEL_TYPE     (0xFFFFF)           /* ipv6������ǵ����ֵ */
#define NAS_ESM_SDF_PF_NUM_ONE      (1)                     /*SDF��PF��Ϊ1*/

#define NAS_ESM_MAX_UE_CONTRUL_CID_NUM      (NAS_ESM_MAX_UE_CONTRUL_CID + 1)
#define NAS_ESM_MAX_CID_NUM                 (NAS_ESM_MAX_CID + 1)              /*����������������������*/

#define NAS_ESM_CID_NV_NUM              (12)                /* NV��������Ŀ */

#define NAS_ESM_MAX_UE_CONTRUL_CID      (20)                /*UE���Ƶ����CID*/
#define NAS_ESM_MIN_NW_CONTROL_CID      (21)                /*NW���Ƶ���СCID*/

#define NAS_ESM_MAX_CID                 (31)                /*����CID*/
#define NAS_ESM_MIN_CID                 (0)                 /*��С��CID*/
#define NAS_ESM_ILL_CID                 (32)                /*��Ч��CID*/
#define NAS_ESM_ATTACH_CID              (0)                 /*ע��CID*/

#define NAS_ESM_MAX_PDN_NUM             (4)                 /*���PDN��*/
#define NAS_ESM_MAX_APN_NUM             (100)               /*���APN��*/

#define NAS_ESM_PTI_UNASSIGNED_VALUE    0x00                /*δ�����PTI*/
#define NAS_ESM_PTI_MAX_VALUE           0xFE                /*PTI�����ֵ*/
#define NAS_ESM_PTI_MIN_VALUE           0x01                 /*PTI����Сֵ*/

#define NAS_ESM_PTI_RESERVED_VALUE      0xFF                /*������PTIֵ*/
#define NAS_ESM_GWAUTHID_MAX_VALUE      0xFE                /*GW AUTH ID�����ֵ*/
#define NAS_ESM_GWAUTHID_MIN_VALUE      0x0                 /*GW AUTH ID����Сֵ*/
#define NAS_ESM_AUTH_CHALLENGE_VALUE_LEN    16
#define NAS_ESM_AUTH_RESPONSE_VALUE_LEN     16
#define NAS_ESM_MAX_MD5_INPUT_PARA_LEN      (1+APP_ESM_MAX_PASSWORD_LEN+NAS_ESM_AUTH_RESPONSE_VALUE_LEN)

#define NAS_ESM_RELEASE_CTRL_R8             0
#define NAS_ESM_RELEASE_CTRL_R9             1

#define NAS_ESM_RELEASE_CTRL                NAS_ESM_RELEASE_CTRL_R8
/*lint -e961*/
#define NAS_ESM_MAX_UINT32              (0xffffffff)        /*���UINT32��*/
#define NAS_ESM_MAX_OPID_VALUE          (0xfffffffe)        /*OPID�����ֵ*/
#define NAS_ESM_MIN_OPID_VALUE          (0)                 /*OPID����Сֵ*/
#define NAS_ESM_ILLEGAL_OPID            (0xffffffff)        /*��ЧOPID*/
/*lint +e961*/

#define NAS_ESM_MIN_PDN_NUM             (1)                 /*���ٵ�PDN��*/

#define NAS_ESM_MSG_LOW_BIT             0x0F
#define NAS_ESM_MSG_HIGH_BIT            0xF0
#define NAS_ESM_MSG_HIGH_3_BIT          0xE0

#define NAS_ESM_MSG_TWO_LEN             2
#define NAS_ESM_MOVEMENT_2_BITS         2
#define NAS_ESM_MOVEMENT_3_BITS         3
#define NAS_ESM_MOVEMENT_4_BITS         4
#define NAS_ESM_MOVEMENT_5_BITS         5
#define NAS_ESM_MOVEMENT_6_BITS         6
#define NAS_ESM_MOVEMENT_7_BITS         7
#define NAS_ESM_MOVEMENT_8_BITS         8
#define NAS_ESM_MOVEMENT_16_BITS        16
#define NAS_ESM_MOVEMENT_24_BITS        24

#define NAS_ESM_SEA_TABLE_ERR_LOC       0xFF
#define NAS_ESM_EVENTTYPE_FAIL          0xFFFF

#define NAS_ESM_LOW_2_BIT_MASK          0x03

#define NAS_ESM_HIGH_5_BIT_MASK         0xF8

/*״̬�������пտ���Ϣ�Ļ��泤��*/
#define NAS_ESM_AIR_MSG_BUFFER_LEN      1024

/* ���ض�Ӧ�ļ����Cid����Ϊ1 */
#define NAS_ESM_BEARER_ACT_CID_NUM_ONE  1

#define NAS_ESM_MSGID_OFFSET            (2)

#define NAS_ESM_MAX_PCSCF_NUM           (3)
#define NAS_ESM_MAX_DNS_SERVER_NUM      (2)
#define NAS_ESM_MAX_NBNS_NUM            (2)
#define NAS_ESM_PCO_OFF                 (0)
#define NAS_ESM_PCO_ON                  (1)
#define NAS_ESM_DEL_SDF_WITH_QOS_OFF    (0)
#define NAS_ESM_DEL_SDF_WITH_QOS_ON     (1)

#define NAS_ERABM_IPV6_PREFIX_LEN       (8)

/*��ʱ��ʱ��*/
#ifdef PS_ITT_PC_TEST_NAS
/* lihong00150010 emergency tau&service begin */
#define TI_NAS_ESM_T3482_TIMER_LEN      8000                /*T3482��ʱ�䳤�ȣ�in milliseconds*/
/* lihong00150010 emergency tau&service end */
#define TI_NAS_ESM_T3492_TIMER_LEN      3000                /*T3492��ʱ�䳤�ȣ�in milliseconds*/
#define TI_NAS_ESM_T3480_TIMER_LEN      7000                /*T3480��ʱ�䳤�ȣ�in milliseconds*/
#define TI_NAS_ESM_T3481_TIMER_LEN      4000                /*T3481��ʱ�䳤�ȣ�in milliseconds*/

#define TI_NAS_ESM_WAIT_APP_CNF_TIMER_LEN 5000              /*WAIT_APP_CNF_TIMER��ʱ�䳤�ȣ�in milliseconds*/

#define TI_NAS_ESM_WAIT_PTI_INVALID_TIMER_LEN 10000         /*WAIT_PTI_INVALID_TIMER��ʱ�䳤�ȣ�in milliseconds*/
#else
#define TI_NAS_ESM_T3482_TIMER_LEN      8000                /*T3482��ʱ�䳤�ȣ�in milliseconds*/
#define TI_NAS_ESM_T3492_TIMER_LEN      6000                /*T3492��ʱ�䳤�ȣ�in milliseconds*/
#define TI_NAS_ESM_T3480_TIMER_LEN      8000                /*T3480��ʱ�䳤�ȣ�in milliseconds*/
#define TI_NAS_ESM_T3481_TIMER_LEN      8000

#define TI_NAS_ESM_WAIT_APP_CNF_TIMER_LEN 10000             /*WAIT_APP_CNF_TIMER��ʱ�䳤�ȣ�in milliseconds*/

#define TI_NAS_ESM_WAIT_PTI_INVALID_TIMER_LEN 50000         /*WAIT_PTI_INVALID_TIMER��ʱ�䳤�ȣ�in milliseconds*/

#endif

#define TI_NAS_ESM_ATTACH_BEARER_REEST_TIMER_LEN    1800    /*Default value of attach bearer re-establishement timer, in second*/
#define TI_NAS_ESM_REL_NON_EMC_BEARER_TIMER_LEN     3000    /*�ӳ��ͷŷǽ������ض�ʱ��ʱ��, in milliseconds*/

#define TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF_TIMER_LEN  3000    /* BACKOFF�㷨��ز�����USIM�ļ��ȴ���ʱ��ʱ�� */

/* �����ط�ȱʡ���ؼ�������ʱ�� */
#define TI_NAS_ESM_T3485_TIMER_LEN                  8000


/*��װ��ӡLOG�ĺ�*/
#ifdef PS_ITT_PC_TEST
#define NAS_ESM_INFO_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define NAS_ESM_INFO_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define NAS_ESM_INFO_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define NAS_ESM_NORM_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define NAS_ESM_WARN_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define NAS_ESM_ERR_LOG(String) \
                 vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define NAS_ESM_LOG1(String, Para1) \
                 vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define NAS_ESM_LOG2(String, Para1, Para2) \
                 vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#else
#define NAS_ESM_INFO_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String)
#define NAS_ESM_INFO_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define NAS_ESM_INFO_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define NAS_ESM_NORM_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define NAS_ESM_WARN_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_WARNING, String)
#define NAS_ESM_ERR_LOG(String) \
                 LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_ERROR, String)
#define NAS_ESM_LOG1(String, Para1) \
                 LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define NAS_ESM_LOG2(String, Para1, Para2) \
                 LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)

#endif

#define NAS_ESM_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_ESM_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))
#define NAS_ESM_MIN(n1,n2)                  (((n1)>(n2))?(n2):(n1))

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#define NAS_ESM_GET_EHSM_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define NAS_ESM_GET_EHSM_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->enMsgId))
#endif

/*��װдAPP��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_APP_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_APP;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

#define NAS_ESM_WRITE_APP_DT_CNF_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = L3_MSP_PID_DT;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);

#define NAS_ESM_WRITE_APP_DT_IND_MSG_HEAD(pstMsg, ulApptMsgID, usOrigId, usTermId, ulSn)\
                    (pstMsg)->ulMsgId = (ulApptMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = L3_MSP_PID_DT_IND;\
                    (pstMsg)->usOriginalId = (usOrigId);\
                    (pstMsg)->usTerminalId = (usTermId);\
                    (pstMsg)->ulSN         = (ulSn);


/*��װдEMM��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_EMM_MSG_HEAD(pstMsg, ulEmmMsgID)\
                    (pstMsg)->ulMsgId   = (ulEmmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_MM;

/*��װдRABM��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_RABM_MSG_HEAD(pstMsg, ulRabmMsgID)\
                    (pstMsg)->ulMsgId   = (ulRabmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_RABM;

/*��װдSM��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_SM_MSG_HEAD(pstMsg, ulSmMsgID)\
                    (pstMsg)->ulMsgId   = (ulSmMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*��װдEHSM��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_EHSM_MSG_HEAD(pstMsg, ulEhsmMsgID)\
                    (pstMsg)->enMsgId         = (ulEhsmMsgID);\
                    (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid     = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid   = UEPS_PID_EHSM;
#endif

/*��װдIP��Ϣͷ�ĺ�*/
#define NAS_ESM_WRITE_IP_MSG_HEAD(pstMsg, ulIpMsgID)\
                    (pstMsg)->ulMsgId   = (ulIpMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_IP;

/*��װдUSIM��Ϣͷ�ĺ�*/
/*USIM����Ϣͷ����ͳһ��װ����MsgHeader��*/
#define NAS_ESM_WRITE_USIM_MSG_HEAD(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_ESM;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;


/* �ڴ濽���궨�� */
#define NAS_ESM_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) \
    {\
        if(NAS_ESM_NULL == PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen)))\
        {\
            NAS_ESM_ERR_LOG("NAS_ESM_MEM_CPY  ERR!!");\
        }\
    }

#define NAS_ESM_MEM_SET(pucBuffer, ucData, ulBufferLen) \
    {\
        if(VOS_NULL_PTR == PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen)))\
        {\
            NAS_ESM_ERR_LOG("NAS_ESM_MEM_SET  ERR!!");\
        }\
    }

#define NAS_ESM_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define NAS_ESM_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_ESM) , (ulLen))

/* ������Ϣ */
#define NAS_ESM_SND_MSG(pMsg)\
    {\
        NAS_ESM_PrintEsmSendMsg((const PS_MSG_HEADER_STRU *)pMsg,NAS_COMM_GET_ESM_PRINT_BUF());\
        if(VOS_OK != PS_SND_MSG_ALL_CHECK((PS_PID_ESM) , (pMsg)))\
            {\
                NAS_ESM_ERR_LOG("NAS_ESM_SND_MSG:Msg Snd Err!");\
            }\
    }

/*�ڴ��ͷ�*/
#define NAS_ESM_MEM_FREE(pAddr)\
    {\
        if(VOS_OK != PS_MEM_FREE_ALL_CHECK((PS_PID_ESM), (pAddr)))\
        {\
            NAS_ESM_ERR_LOG("NAS_ESM_MEM_FREE  ERR!!");\
        }\
    }

/*�ڴ涯̬����*/
#define NAS_ESM_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_ESM) , (ulSize))

#define NAS_ESM_PRINT_BEARCNTXTSTA(BearerCntxtState)\
            switch (BearerCntxtState)\
            {\
                case    NAS_ESM_BEARER_STATE_INACTIVE   :\
                    NAS_ESM_NORM_LOG("State :  BEARER_CONTEXT_INACTIVE");\
                    break;\
                case    NAS_ESM_BEARER_STATE_ACTIVE:\
                    NAS_ESM_NORM_LOG("State :  BEARER_CONTEXT_ACTIVE ");\
                    break;\
                case    NAS_ESM_BEARER_STATE_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("State :  SM UKNOWN BEARER_CONTEXT_STATE");\
                    break;\
            }

#define NAS_ESM_PRINT_PROCTRANSSTA(ProcTransState)\
            switch (ProcTransState)\
            {\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE   :\
                    NAS_ESM_NORM_LOG("State :  PROCEDURE_TRANSACTION_INACTIVE");\
                    break;\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING:\
                    NAS_ESM_NORM_LOG("State :  PROCEDURE_TRANSACTION_PENDING ");\
                    break;\
                case    NAS_ESM_BEARER_PROC_TRANS_STATE_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("State :  SM UKNOWN PROCEDURE_TRANSACTION_STATE");\
                    break;\
            }

#define NAS_ESM_PRINT_EMMSTA(EmmStatus)\
            switch (EmmStatus)\
            {\
                case    NAS_ESM_PS_REGISTER_STATUS_DETACHED   :\
                    NAS_ESM_NORM_LOG("EMM_DETACHED");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_ATTACHING:\
                    NAS_ESM_NORM_LOG("EMM_ATTACHING");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_ATTACHED:\
                    NAS_ESM_NORM_LOG("EMM_ATTACHED");\
                    break;\
                case    NAS_ESM_PS_REGISTER_STATUS_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("UKNOWN EMM REGISTER STATUS");\
                    break;\
            }

#define NAS_ESM_PRINT_LMODESTA(LModeStatus)\
            switch (LModeStatus)\
            {\
                case    NAS_ESM_L_MODE_STATUS_NORMAL   :\
                    NAS_ESM_NORM_LOG("ESM L_MODE_NORMAL");\
                    break;\
                case    NAS_ESM_L_MODE_STATUS_SUSPENDED:\
                    NAS_ESM_NORM_LOG("ESM L_MODE_SUSPENDED");\
                    break;\
                case    NAS_ESM_L_MODE_STATUS_BUTT:\
                default   :\
                    NAS_ESM_NORM_LOG("ESM UKNOWN L MODE STATUS");\
                    break;\
            }

#define NAS_ESM_IS_IPV4_ADDR_INVALID(IPADDR)\
     ((IPADDR[0] == 0)&&(IPADDR[1] == 0)&&(IPADDR[2] == 0)&&(IPADDR[3] == 0))

#define  NAS_ESM_NO                     0
#define  NAS_ESM_YES                    1
#define  NAS_ESM_EMM_OPID_NOT_VAILID    0xFFFFFFFFL



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NAS_ESM_ERROR_CODE_ENUM
{
    NAS_ESM_SUCCESS                                         = 0,         /*ESM ģ�麯�����سɹ�*/
    NAS_ESM_FAILURE                                            ,         /*ESM ģ�麯������ʧ��*/
    NAS_ESM_MSG_DISCARD                                        ,         /*������Ϣ*/
    NAS_ESM_MSG_HANDLED                                                 /*��Ϣ�Ѵ��� */
};

enum NAS_ESM_MATCH_RESULT_ENUM
{
    NAS_ESM_MATCH_FAIL                      = 0,
    NAS_ESM_MATCH_SUCCESS                   = 1,
    NAS_ESM_MATCH_PTR_NULL                  = 2,
    NAS_ESM_MATCH_RESULT_BUTT
};
typedef VOS_UINT32  NAS_ESM_MATCH_RESULT_ENUM_UINT32;


/*�տ���Ϣ����*/
enum NAS_ESMCN_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                                         /*��ϢID*/   /* ��ע */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ       = 0xC1,      /*ȱʡ���ؼ������� 1100  0001   Activate default EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC       = 0xC2,      /*ȱʡ���ؼ������ 1100  0010   Activate default EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REJ       = 0xC3,      /*ȱʡ���ؼ���ܾ� 1100  0011   Activate default EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ     = 0xC5,      /*ר�г��ؼ������� 1100  0101   Activate dedicated EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_ACC     = 0xC6,      /*ר�г��ؼ������ 1100  0110   Activate dedicated EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REJ     = 0xC7,      /*ר�г��ؼ���ܾ� 1100  0111   Activate dedicated EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ             = 0xC9,      /*�����޸����� 1100  1001   Modify EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_ACC             = 0xCA,      /*�����޸Ľ��� 1100  1010   Modify EPS bearer context accept  */
    NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REJ             = 0xCB,      /*�����޸ľܾ� 1100  1011   Modify EPS bearer context reject  */

    NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ           = 0xCD,      /*����ȥ�������� 1100  1101   Deactivate EPS bearer context request  */
    NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_ACC           = 0xCE,      /*����ȥ������� 1100  1110   Deactivate EPS bearer context accept  */

    NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ                      = 0xD0,      /*PDN�������� 1101  0000   PDN connectivity request  */
    NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ                      = 0xD1,      /*PDN���Ӿܾ� 1101  0001   PDN connectivity reject  */

    NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REQ                   = 0xD2,      /*PDNȥ�������� 1101  0010   PDN disconnect request  */
    NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REJ                   = 0xD3,      /*PDNȥ���Ӿܾ� 1101  0011   PDN disconnect reject  */

    NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REQ                 = 0xD4,      /*��Դ�������� 1101  0100   Bearer resource allocation request  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REJ                 = 0xD5,      /*��Դ����ܾ� 1101  0101   Bearer resource allocation reject  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ                   = 0xD6,      /*��Դ�޸����� 1101  0110   Bearer resource modification request  */
    NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REJ                   = 0xD7,      /*��Դ�޸ľܾ� 1101  0111   Bearer resource modification reject  */

    NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ                  = 0xD9,
    NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_RSP                  = 0xDA,

    NAS_ESMCN_MSG_TYPE_ESM_STATUS                           = 0xE8,
    NAS_ESMCN_MSG_TYPE_ESM_NOTIFICATION                     = 0xDB,

    NAS_ESMCN_MSG_TYPE_BUTT
};
typedef VOS_UINT8    NAS_ESMCN_MSG_TYPE_ENUM_UINT8;

enum NAS_ESM_CAUSE_ENUM
{
    NAS_ESM_CAUSE_SUCCESS                                   = 0,/*UE�Զ���*/
    NAS_ESM_CAUSE_ERROR                                     = 1,/*UE�Զ���*/

    NAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING                = 8,
    NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES                    = 26,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN                    = 27,
    NAS_ESM_CAUSE_UNKNOWN_PDN_TYPE                          = 28,
    NAS_ESM_CAUSE_USER_AUTH_FAIL                            = 29,
    NAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW                     = 30,
    NAS_ESM_CAUSE_REQ_REJ_UNSPECITY                         = 31,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT                = 32,
    NAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED                = 33,
    NAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER             = 34,
    NAS_ESM_CAUSE_PTI_ALREADY_IN_USED                       = 35,
    NAS_ESM_CAUSE_REGULAR_DEACTIVATION                      = 36,
    NAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT                        = 37,
    NAS_ESM_CAUSE_NETWORK_FAILURE                           = 38,
    NAS_ESM_CAUSE_FEATURE_NOT_SUPPORTED                     = 40,
    NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT                       = 41,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT                      = 42,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY               = 43,
    NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER             = 44,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER           = 45,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT                    = 46,/*UE���ܷ�����*/
    NAS_ESM_CAUSE_PTI_MISMATCH                              = 47,
    NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED              = 49,
    NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED                 = 50,
    NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED                 = 51,
    NAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED           = 52,
    NAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED              = 53,
    NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST             = 54,
    NAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED = 55,
    NAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST  = 56,
    NAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE                     = 59,
    NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN   = 66,
    NAS_ESM_CAUSE_INVALID_PTI_VALUE                         = 81,
    NAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE            = 95,
    NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION             = 96,
    NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED = 97,
    NAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA = 98,
    NAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED = 99,
    NAS_ESM_CAUSE_CONDITIONAL_IE_ERROR                      = 100,
    NAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA      = 101,
    NAS_ESM_CAUSE_PROTOCOL_ERROR                            = 111,

    NAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER = 112,

    NAS_ESM_CAUSE_MSG_TOO_SHORT                             = 200
};
typedef VOS_UINT8   NAS_ESM_CAUSE_ENUM_UINT8;

enum    NAS_ESM_PDN_REQ_TYPE_ENUM
{
    NAS_ESM_PDN_REQ_TYPE_INITIAL     = 0x00,
    NAS_ESM_PDN_REQ_TYPE_HANDOVER    = 0x01,
    NAS_ESM_PDN_REQ_TYPE_BUTT
};
typedef VOS_UINT8   NAS_ESM_PDN_REQ_TYPE_ENUM_UINT8;

enum NAS_ESM_BEARER_TYPE_ENUM
{
    NAS_ESM_BEARER_TYPE_DEFAULT = 0,                /*ȱʡ����*/
    NAS_ESM_BEARER_TYPE_DEDICATED,                  /*ר�г���*/
    NAS_ESM_BEARER_TYPE_EMERGENCY,                  /*��������*/

    NAS_ESM_BEARER_TYPE_BUTT
};/*���ص�����*/
typedef VOS_UINT8  NAS_ESM_BEARER_TYPE_ENUM_UINT8;


enum NAS_ESM_BEARER_STATE_ENUM
{
    NAS_ESM_BEARER_STATE_INACTIVE  = 0,             /*������ȥ����̬*/
    NAS_ESM_BEARER_STATE_ACTIVE,                    /*�����ļ���״̬*/

    NAS_ESM_BEARER_STATE_BUTT
};/*ESM ���ص�״̬*/
typedef VOS_UINT8  NAS_ESM_BEARER_STATE_ENUM_UINT8;

enum NAS_ESM_BEARER_PROC_TRANS_STATE_ENUM
{
    NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE = 0,           /*PROCEDURE_TRANSACTION_INACTIVE*/
    NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING,                /*PROCEDURE_TRANSACTION_PENDING���ȴ�����ظ�*/

    NAS_ESM_BEARER_PROC_TRANS_STATE_BUTT
};/*ESM  PROCEDURE_TRANSACTION״̬*/
typedef VOS_UINT8  NAS_ESM_PROC_TRANS_STATE_ENUM_UINT8;

enum NAS_ESM_TIMER_PARA_ENUM
{
    TI_NAS_ESM_T3482 = 0,
    TI_NAS_ESM_T3492,
    TI_NAS_ESM_T3480,
    TI_NAS_ESM_T3481,

    TI_NAS_ESM_WAIT_APP_CNF,                                /*�ȴ�APP�ظ���ʱ��*/

    TI_NAS_ESM_WAIT_PTI_INVALID,                            /*�ȴ�PTIʧЧ*/
    TI_NAS_ESM_ATTACH_BEARER_REEST,                         /* Timer for Attach Bearer Reest*/
    TI_NAS_ESM_REL_NON_EMC_BEARER,                          /* Timer for defer release non-emergency PDN*/

    TI_NAS_ESM_BACKOFF_WAIT_USIM_CNF,
    TI_NAS_ESM_BACKOFF_IGNORE_FORBID,
    TI_NAS_ESM_BACKOFF_PERM_REJ_FORBID,
    TI_NAS_ESM_BACKOFF_TEMP_REJ_FORBID,

    TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC,

    TI_NAS_ESM_TIMER_PARA_BUTT
};/*ESM ��ʱ�������������ö�ʱ��ʱ��para�ֶ�*/
typedef VOS_UINT8 NAS_ESM_TIMER_PARA_ENUM_UINT8;
enum NAS_ESM_OM_LOG_MSG_ENUM
{
    NAS_ESM_OM_LOG_TIMER_MIN               = PS_MSG_ID_ESM_TO_ESM_OM_BASE,

    NAS_ESM_OM_LOG_TIMER_MAX               = PS_MSG_ID_ESM_TO_ESM_OM_BASE + 0x10,  /* һ��32����������ʱ��16�� */

    NAS_ESM_OM_LOG_BACKOFF_INIT            = NAS_ESM_OM_LOG_TIMER_MAX + 0x01,
    NAS_ESM_OM_LOG_BACKOFF_JUDGMENT        = NAS_ESM_OM_LOG_TIMER_MAX + 0x02,
    NAS_ESM_OM_LOG_BACKOFF_MAINTAIN        = NAS_ESM_OM_LOG_TIMER_MAX + 0x03,
    NAS_ESM_OM_LOG_BACKOFF_RESET           = NAS_ESM_OM_LOG_TIMER_MAX + 0x04,

    NAS_ESM_OM_LOG_BACKOFF_NV_PARA         = NAS_ESM_OM_LOG_TIMER_MAX + 0x05,
    NAS_ESM_OM_LOG_BACKOFF_COMM_INFO       = NAS_ESM_OM_LOG_TIMER_MAX + 0x06,
    NAS_ESM_OM_LOG_BACKOFF_APN_ENTITY_LIST = NAS_ESM_OM_LOG_TIMER_MAX + 0x07,

    NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_NUM    = NAS_ESM_OM_LOG_TIMER_MAX + 0x08,
    NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_INFO   = NAS_ESM_OM_LOG_TIMER_MAX + 0x09,
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-08-18, begin */
    NAS_ESM_OM_LOG_REG_CID_INFO            = NAS_ESM_OM_LOG_TIMER_MAX + 0x0a
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-08-18, end */

};

enum NAS_ESM_PS_REGISTER_STATUS_ENUM
{
    NAS_ESM_PS_REGISTER_STATUS_DETACHED = 0,                /*��ע��*/
    NAS_ESM_PS_REGISTER_STATUS_ATTACHING,                   /*ע����*/
    NAS_ESM_PS_REGISTER_STATUS_ATTACHED,                    /*��ע��*/

    NAS_ESM_PS_REGISTER_STATUS_BUTT
};/*EMM��ע��״̬*/
typedef VOS_UINT8 NAS_ESM_PS_REGISTER_STATUS_ENUM_UINT8;

enum NAS_ESM_L_MODE_STATUS_ENUM
{
    NAS_ESM_L_MODE_STATUS_NORMAL        = 0,                /*����̬*/
    NAS_ESM_L_MODE_STATUS_SUSPENDED     = 1,                /*����̬*/

    NAS_ESM_L_MODE_STATUS_BUTT
};/* Lģ״̬ */

typedef VOS_UINT8 NAS_ESM_L_MODE_STATUS_ENUM_UINT8;

enum NAS_ESM_BEARER_MANAGE_TYPE_ENUM
{
    NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT = 0,                  /*����*/
    NAS_ESM_BEARER_MANAGE_TYPE_REJ,                         /*�ܾ�*/

    NAS_ESM_BEARER_MANANGE_TYPE_BUTT
}; /*��ʶ���ع�������*/
typedef VOS_UINT8  NAS_ESM_BEARER_MANAGE_TYPE_ENUM_UINT8;

enum NAS_ESM_BEARER_MANAGE_MODE_ENUM
{
    NAS_ESM_BEARER_MANAGE_MODE_AUTO = 0,                    /*�Զ�*/
    NAS_ESM_BEARER_MANAGE_MODE_MANUAL,                      /*�ֶ�*/

    NAS_ESM_BEARER_MANAGE_MODE_BUTT
}; /*��ʶ���ع���ģʽ*/
typedef VOS_UINT8  NAS_ESM_BEARER_MANAGE_MODE_ENUM_UINT8;

enum NAS_ESM_BEARER_PROC_STATE_ENUM
{
    NAS_ESM_BEARER_PROC_STATE_ALLOW = 0,                    /*����*/
    NAS_ESM_BEARER_PROC_STATE_FORBID,                       /*��ֹ*/

    NAS_ESM_BEARER_PROC_STATE_BUTT
}; /*��ʶ���ص�ǰ�Ƿ�ɴ���*/
typedef VOS_UINT8  NAS_ESM_BEARER_PROC_STATE_ENUM_UINT8;


/* tad����ö�� */
enum NAS_ESM_TFT_OP_TYPE_ENUM
{
    NAS_ESM_TFT_OP_TYPE_CREATE_TFT      = 0x01 ,
    NAS_ESM_TFT_OP_TYPE_DELETE_TFT      = 0x02,
    NAS_ESM_TFT_OP_TYPE_ADD_FILTER      = 0x03,
    NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER  = 0x04,
    NAS_ESM_TFT_OP_TYPE_DELETE_FILTER   = 0x05,
    NAS_ESM_TFT_OP_TYPE_NO_OP           = 0x06,
    NAS_ESM_TFT_OP_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_TFT_OP_TYPE_ENUM_UINT8;

/* QOSƫ��ö�� */
enum NAS_ESM_QOS_OFFSET_ENUM
{
    NAS_ESM_QOS_OFFSET_QCI              = 0x0 ,
    NAS_ESM_QOS_OFFSET_ULMAXRATE        = 0x01,
    NAS_ESM_QOS_OFFSET_DLMAXRATE        = 0x02,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE       = 0x03,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE       = 0x04,
    NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT    = 0x05,
    NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT    = 0x06,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT   = 0x07,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT   = 0x08,
    NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT_2  = 0x09,
    NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT_2  = 0x0A,
    NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT_2 = 0x0B,
    NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT_2 = 0x0C,

    NAS_ESM_QOS_OFFSET_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_OFFSET_ENUM_UINT8;


/* QOS����ö�� */
enum NAS_ESM_QOS_RATE_ENUM
{
    NAS_ESM_QOS_RATE_64KB               = 64,
    NAS_ESM_QOS_RATE_568KB              = 568 ,
    NAS_ESM_QOS_RATE_576KB              = 576 ,
    NAS_ESM_QOS_RATE_8600KB             = 8600,
    NAS_ESM_QOS_RATE_8640KB             = 8640,
    NAS_ESM_QOS_RATE_8700KB             = 8700,
    NAS_ESM_QOS_RATE_16000KB            = 16000,
    NAS_ESM_QOS_RATE_16MB               = 16*1000,
    NAS_ESM_QOS_RATE_17MB               = 17*1000,
    NAS_ESM_QOS_RATE_128MB              = 128*1000,
    NAS_ESM_QOS_RATE_130MB              = 130*1000,
    NAS_ESM_QOS_RATE_256MB              = 256*1000,
    NAS_ESM_QOS_RATE_260MB              = 260*1000,
    NAS_ESM_QOS_RATE_500MB              = 500*1000,
    NAS_ESM_QOS_RATE_510MB              = 510*1000,
    NAS_ESM_QOS_RATE_1500MB             = 1500*1000,
    NAS_ESM_QOS_RATE_1600MB             = 1600*1000,
    NAS_ESM_QOS_RATE_10GB               = 10000*1000,

    NNAS_ESM_QOS_RATE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_ENUM_UINT8;

/* QOS���ʼ��ö�� */
enum NAS_ESM_QOS_RATE_GRANULARITY_ENUM
{
    NAS_ESM_QOS_RATE_GRANULARITY_8KB    = 8,
    NAS_ESM_QOS_RATE_GRANULARITY_64KB   = 64 ,
    NAS_ESM_QOS_RATE_GRANULARITY_100KB  = 100,
    NAS_ESM_QOS_RATE_GRANULARITY_1MB    = 1000,
    NAS_ESM_QOS_RATE_GRANULARITY_2MB    = 2*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_4MB    = 4*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_10MB   = 10*1000,
    NAS_ESM_QOS_RATE_GRANULARITY_100MB  = 100*1000,

    NAS_ESM_QOS_RATE_GRANULARITY_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_GRANULARITY_ENUM_UINT8;

/* QOS��������ö�� */
enum NAS_ESM_QOS_RATE_RANGE_ENUM
{
    NAS_ESM_QOS_RATE_RANGE_568KB_GRANULARITY_8KB            = 0x7F,
    NAS_ESM_QOS_RATE_RANGE_8640KB_GRANULARITY_64KB          = 0xFE ,
    NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB         = 0x4A,
    NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB            = 0xBA,
    NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB            = 0xFA,
    NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB            = 0x3D,
    NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB          = 0xA1,
    NAS_ESM_QOS_RATE_RANGE_10GB_GRANULARITY_100MB           = 0XF6,

    NAS_ESM_QOS_RATE_RANGE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QOS_RATE_RANGE_UINT8;

/* ����CID���ö�� */
enum NAS_ESM_QUERY_CID_RSLT_ENUM
{
    NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_EQUAL_CID         = 0x01,
    NAS_ESM_QUERY_CID_RSLT_ALL_FOUND_UNEQUAL_CID       = 0x02 ,
    NAS_ESM_QUERY_CID_RSLT_PART_FOUND_EQUAL_CID        = 0x03,
    NAS_ESM_QUERY_CID_RSLT_PART_FOUND_UNEQUAL_CID      = 0x04,
    NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND                 = 0x05,

    NAS_ESM_QUERY_CID_RSLT_BUTT
};
typedef VOS_UINT8  NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8;

/* APN AMBRƫ��ö�� */
enum NAS_ESM_APN_AMBR_OFFSET_ENUM
{
    NAS_ESM_APN_AMBR_OFFSET_DLRATE        = 0x00,
    NAS_ESM_APN_AMBR_OFFSET_ULRATE        = 0x01,
    NAS_ESM_APN_AMBR_OFFSET_DLEXT1        = 0x02,
    NAS_ESM_APN_AMBR_OFFSET_ULEXT1        = 0x03,
    NAS_ESM_APN_AMBR_OFFSET_DLEXT2        = 0x04,
    NAS_ESM_APN_AMBR_OFFSET_ULEXT2        = 0x05,

    NAS_ESM_APN_AMBR_OFFSET_BUTT
};
typedef VOS_UINT8  NAS_ESM_APN_AMBR_OFFSET_ENUM_UINT8;

/* ESM OPID���� */
enum NAS_ESM_OPID_TYPE_ENUM
{
    NAS_ESM_OPID_TYPE_SETUP_IND         = DIAG_CMD_ESM_PDP_SETUP_IND,
    NAS_ESM_OPID_TYPE_MODIFY_IND        = DIAG_CMD_ESM_PDP_MODIFY_IND,
    NAS_ESM_OPID_TYPE_RELEASE_IND       = DIAG_CMD_ESM_PDP_RELEASE_IND,
    NAS_ESM_OPID_TYPE_MANAGER_IND       = DIAG_CMD_ESM_PDP_MANAGER_IND,
    NAS_ESM_OPID_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_OPID_TYPE_ENUM_UINT8;

/* QCI���� */
enum NAS_ESM_QCI_TYPE_ENUM
{
    NAS_ESM_QCI_TYPE_QCI1_GBR           = 1,
    NAS_ESM_QCI_TYPE_QCI2_GBR           = 2,
    NAS_ESM_QCI_TYPE_QCI3_GBR           = 3,
    NAS_ESM_QCI_TYPE_QCI4_GBR           = 4,
    NAS_ESM_QCI_TYPE_QCI5_NONGBR        = 5,
    NAS_ESM_QCI_TYPE_QCI6_NONGBR        = 6,
    NAS_ESM_QCI_TYPE_QCI7_NONGBR        = 7,
    NAS_ESM_QCI_TYPE_QCI8_NONGBR        = 8,
    NAS_ESM_QCI_TYPE_QCI9_NONGBR        = 9,

    NAS_ESM_QCI_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_QCI_TYPE_ENUM_UINT8;

enum NAS_ESM_BUFF_ITEM_TYPE_ENUM
{
    NAS_ESM_BUFF_ITEM_TYPE_PTI                                 = 0,             /*PTI�����¼����*/
    NAS_ESM_BUFF_ITEM_TYPE_ATTACHING                           = 1,             /*ATTACH�����л����¼����*/

    NAS_ESM_BUFF_ITEM_TYPE_BUTT
};
typedef VOS_UINT8  NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8;

enum NAS_ESM_FUN_MD5_CTRL_ENUM
{
    NAS_ESM_FUN_MD5_CTRL_OFF        = 0x00 ,
    NAS_ESM_FUN_MD5_CTRL_ON         = 0x01,

    NAS_ESM_FUN_MD5_BUTT
};
typedef VOS_UINT32  NAS_ESM_FUN_MD5_CTRL_ENUM_UINT32;

enum NAS_ESM_EPS_QOS_CHANGE_TYPE_ENUM
{
    NAS_ESM_EPS_QOS_CHANGE_TYPE_CHANGED                     = 0x00 ,
    NAS_ESM_EPS_QOS_CHANGE_TYPE_NO_CHANGE                   = 0x01,

    NAS_ESM_EPS_QOS_CHANGE_TYPE_BUTT
};
typedef VOS_UINT32  NAS_ESM_EPS_QOS_CHANGE_TYPE_ENUM_UINT32;

enum NAS_ESM_APP_IND_TYPE_ENUM
{
    NAS_ESM_APP_IND_TYPE_SETUP                              = 0x01,
    NAS_ESM_APP_IND_TYPE_RELEASE                            = 0x02,
    NAS_ESM_APP_IND_TYPE_MODIFY                             = 0x03,

    NAS_ESM_APP_IND_TYPE_BUTT
};
typedef VOS_UINT32  NAS_ESM_APP_IND_TYPE_ENUM_UINT32;

typedef SM_ESM_BCM_ENUM_UINT8 NAS_ESM_BCM_ENUM_UINT8;

/*****************************************************************************
    ö����    : NAS_ESM_NW_LOCAL_IP_CAP_ENUM
    ö��˵��  : �����Ƿ�֧��LOCAL IP
*****************************************************************************/
enum    NAS_ESM_NW_LOCAL_IP_CAP_ENUM
{
    NAS_ESM_NW_LOCAL_IP_CAP_UNSUPPORT                = 0x00,
    NAS_ESM_NW_LOCAL_IP_CAP_SUPPORT,

    NAS_ESM_NW_LOCAL_IP_CAP_BUTT
};
typedef VOS_UINT32   NAS_ESM_NW_LOCAL_IP_CAP_ENUM_UINT32;

enum NAS_ESM_FUN_CTRL_ENUM
{
    NAS_ESM_FUN_CTRL_OFF              = 0x00 ,
    NAS_ESM_FUN_CTRL_ON               = 0x01,

    NAS_ESM_FUN_CTRL_BUTT
};
typedef VOS_UINT32  NAS_ESM_FUN_CTRL_ENUM_UINT32;



/*****************************************************************************
    ö����    : NAS_TIMER_RUN_STA_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    NAS_ESM_TIMER_RUN_STA_ENUM
{
    NAS_ESM_TIMER_RUNNING                = 0x00,
    NAS_ESM_TIMER_STOPED,
    NAS_ESM_TIMER_INVALID,

    NAS_ESM_TIMER_BUTT
};
typedef VOS_UINT32   NAS_ESM_TIMER_RUN_STA_ENUM_UINT32;

enum NAS_ESM_BEARER_DATA_CNF_ENUM
{
     NAS_ESM_BEARER_STATUS_NULL = 0, /*��ʼ״̬*/
     NAS_ESM_BEARER_DATA_CNF_SENDING,     /*DATA REQ�����У� �ȴ�LRRC�ظ�*/
     NAS_ESM_BEARER_DATA_CNF_FAIL,
     NAS_ESM_BEARER_DATA_CNF_SUCC,
     NAS_ESM_BEARER_DATA_CNF_BUTT
};
typedef VOS_UINT8   NAS_ESM_BEARER_DATA_CNF_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/* ����SMPDN��ַ�Ľṹ��*/
typedef APP_ESM_IP_ADDR_STRU NAS_ESM_CONTEXT_IP_ADDR_STRU;

/* SM�����ĵ�TFT�ṹ�� */
typedef APP_ESM_TFT_INFO_STRU NAS_ESM_CONTEXT_TFT_STRU;

/* SM�����ĵ�SDF QOS�ṹ�� */

/*****************************************************************************
 �ṹ��    : NAS_ESM_CONTEXT_LTE_QOS_STRU
 �ṹ˵��  : EPS_QOS  ����
*****************************************************************************/
typedef struct
{
    APP_ESM_EPS_QOS_INFO_STRU           stQosInfo;
    VOS_UINT8                           ucNwQCI;
    VOS_UINT8                           aucReserve1[3];     /* ���ֽڶ��룬���� */
}NAS_ESM_CONTEXT_LTE_QOS_STRU;


/* SM�����ĵ�QOS�Ľṹ�� */
typedef APP_ESM_QOS_INFO_STRU NAS_ESM_CONTEXT_QOS_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_CONTEXT_APN_STRU
 �ṹ˵��  : APN�����Ժ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucApnLen;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucApnName[NAS_ESM_MAX_APN_NUM];
}NAS_ESM_CONTEXT_APN_STRU;


/* SM�����ĵ�APN AMBR�Ľṹ�� */
typedef APP_ESM_APN_AMBR_INFO_STRU NAS_ESM_CONTEXT_APN_AMBR_STRU;

/* SM�����ĵ�Transaciotn Id�Ľṹ�� */
typedef SM_ESM_TRANSACTION_ID_STRU NAS_ESM_CONTEXT_TRANS_ID_STRU;

typedef struct
{
    VOS_UINT8                           aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN];
}NAS_ESM_IPV4_ADDR_STRU;

typedef struct
{
    VOS_UINT8                           aucIpV6Addr[APP_MAX_IPV6_ADDR_LEN];
}NAS_ESM_IPV6_ADDR_STRU;

/* lihong00150010 ims begin */
/* SM�����ĵ�PCO�Ľṹ�� */
/*typedef APP_ESM_PCO_INFO_STRU NAS_ESM_CONTEXT_PCO_STRU;*/
/*****************************************************************************
 �ṹ��    : NAS_ESM_CONTEXT_PCO_STRU
 �ṹ˵��  : ������PCO����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBcm        : 1;
    VOS_UINT32                          bitOpImsCnSignalFlag :1;
    VOS_UINT32                          bitOpNwLocalIpCap :1;
    VOS_UINT32                          bitOpSpare      : 29;

    NAS_ESM_BCM_ENUM_UINT8              enBcm;
    VOS_UINT8                           ucIpv4DnsSerNum;
    VOS_UINT8                           ucIpv4PcscfNum;
    VOS_UINT8                           ucIpv6DnsSerNum;
    VOS_UINT8                           ucIpv6PcscfNum;
    VOS_UINT8                           ucIpv4NbnsNum;
    NAS_ESM_IPV4_ADDR_STRU              astIpv4DnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_IPV4_ADDR_STRU              astIpv4Pcscf[NAS_ESM_MAX_PCSCF_NUM];
    NAS_ESM_IPV4_ADDR_STRU              astIpv4Nbns[NAS_ESM_MAX_NBNS_NUM];
    NAS_ESM_IPV6_ADDR_STRU              astIpv6DnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_IPV6_ADDR_STRU              astIpv6Pcscf[NAS_ESM_MAX_PCSCF_NUM];

    APP_ESM_IMS_CN_SIG_FLAG_ENUM_UINT32 enImsCnSignalFlag;

    NAS_ESM_NW_LOCAL_IP_CAP_ENUM_UINT32 enNwLocalIPCap;
}NAS_ESM_CONTEXT_PCO_STRU;
/* lihong00150010 ims end */

/*****************************************************************************
 �ṹ��    : NAS_ESM_CONTEXT_PCO_STRU
 �ṹ˵��  : ת�����PCO����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpBcm        : 1;
    VOS_UINT32                          bitOpSpare      : 31;

    NAS_ESM_BCM_ENUM_UINT8              enBcm;
    VOS_UINT8                           ucDnsSerNum;
    VOS_UINT8                           ucPcscfNum;
    VOS_UINT8                           ucNbnsNum;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astDnsServer[NAS_ESM_MAX_DNS_SERVER_NUM];
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astPcscf[NAS_ESM_MAX_PCSCF_NUM];
    NAS_ESM_CONTEXT_IP_ADDR_STRU        astNbns[NAS_ESM_MAX_NBNS_NUM];
}NAS_ESM_PCO_TRANSFORM_STRU;



/*��¼APP��Ϣ�Ľṹ��*/
typedef struct
{
    VOS_UINT32                          ulAppMsgOpId;       /* App����SM����Ϣ������ʶ */
    VOS_UINT32                          ulEsmMsgOpId;       /* Sm����App����Ϣ������ʶ */
    VOS_UINT16                          usOriginalId;       /* ԴMID */
    VOS_UINT16                          usTerminalId;       /* Ŀ��ID */
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType;       /* ��Ϣ���� */
}NAS_ESM_APP_MSG_RECORD_STRU;


/*��¼�տ���Ϣ�Ľṹ��*/
typedef struct
{
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucIsEmcPdnReq;      /* ��ʶ�Ƿ��ǽ���PDN�������� */
    VOS_UINT8                           ucPti;              /* Procedure transaction identifier */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;     /* SM����CN�Ŀտ���Ϣ���� */
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enCnEsmMsgType;     /* CN����SM�Ŀտ���Ϣ���� */
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ESM_AIR_MSG_BUFFER_LEN];
}NAS_ESM_NW_MSG_RECORD_STRU;

/*��ʱ��ʹ�õ����ݽṹ*/
typedef struct
{
    HTIMER                              hTimer;             /* vos�����Timer Id   */
    NAS_ESM_TIMER_PARA_ENUM_UINT8       enPara;             /* Timer����   */
    VOS_UINT8                           ucExpireTimes;      /* Timer��ʱ����  */
    VOS_UINT8                           aucReserve1[2];     /* ���ֽڶ��룬���� */
}NAS_ESM_TIMER_STRU;

typedef struct tag_NAS_ESM_PDN_REJ_INFO_STRU
{
    struct tag_NAS_ESM_PDN_REJ_INFO_STRU *pstNext;

    VOS_UINT32                          bitOpApnInfo :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv     :31;

    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_PLMN_LIST_STRU              stEPlmnList;
}NAS_ESM_PDN_REJ_INFO_STRU;


/*���ع�����Ϣ�����ݽṹ*/

typedef APP_ESM_PDP_MANAGE_INFO_STRU NAS_ESM_PDP_MANAGE_INFO_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPdpManInfo :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv        :31;

    NAS_ESM_PDP_MANAGE_INFO_STRU        stPdpManInfo;
}NAS_ESM_NV_PDP_MANAGE_INFO_STRU;

typedef APP_ESM_SDF_PARA_STRU          NAS_ESM_SDF_PARA_STRU;

/*EPS������������Ϣ�����ݽṹ*/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr                      : 1;
    VOS_UINT32                          bitOpApn                          : 1;
    VOS_UINT32                          bitOpApnAmbr                      : 1;
    VOS_UINT32                          bitOpEpsQos                       : 1;
    VOS_UINT32                          bitOpPco                          : 1;
    VOS_UINT32                          bitOpEsmCause                     : 1;
    VOS_UINT32                          bitOpCId                          : 1;
    VOS_UINT32                          bitOpGateWayAddrInfo              : 1;
    VOS_UINT32                          bitOpTransId                      : 1;
    VOS_UINT32                          bitOpNegQos                       : 1;
    VOS_UINT32                          bitOpLlcSapi                      : 1;
    VOS_UINT32                          bitOpRadioPriority                : 1;
    VOS_UINT32                          bitOpPacketFlowId                 : 1;
    VOS_UINT32                          bitOpSpare                        : 19;

    NAS_ESM_BEARER_STATE_ENUM_UINT8     enBearerCntxtState; /* SM�����ĵ�״̬ */
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enBearerCntxtType;  /* �����Ķ�Ӧ���ص����� */
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCau;
    VOS_UINT8                           ucReserve1[1];         /* ���ֽڶ��룬���� */

    VOS_UINT32                          ulEpsbId;           /*��ӦEPS����ID*/
    VOS_UINT32                          ulBitCId;           /*�˳��ض�Ӧ��CID��һ��BIT��Ӧһ��CID*/
    VOS_UINT32                          ulLinkedEpsbId;     /*��˳��ع�����EPS����ID*/
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stPdnAddrInfo;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stSubnetMask;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stGateWayAddrInfo;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_CONTEXT_APN_AMBR_STRU       stApnAmbrInfo;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stEpsQoSInfo;
    NAS_ESM_CONTEXT_QOS_STRU            stCntxtQosInfo;
    NAS_ESM_CONTEXT_PCO_STRU            stPcoInfo;
    NAS_ESM_CONTEXT_TRANS_ID_STRU       stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved2[1];
}NAS_ESM_EPSB_CNTXT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulSdfPfNum;           /*SDF��ǰ��Ч��PF��*/
    NAS_ESM_CONTEXT_TFT_STRU            astSdfPfInfo[NAS_ESM_MAX_SDF_PF_NUM];
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stSdfQosInfo;
}NAS_ESM_SDF_CNTXT_INFO_STRU;

/*ESM ��¼�����͵Ŀտ���Ϣ�����ݽṹ*/
typedef struct
{
    VOS_UINT32                          ulNwMsgSize;         /* ��Ϣ���ܳ��� */
    VOS_UINT8                          *pucNwMsg;            /* ��Ϣ���׵�ַ */
}NAS_ESM_SND_NW_MSG_STRU;

/*ESM ������Э�̺��TFT��Ϣ*/
typedef struct
{
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulCid;
    NAS_ESM_CONTEXT_TFT_STRU            stCntxtUlTftInfo;
}NAS_ESM_EPSB_TFT_INFO_STRU;

/*ESM ��¼�տ���ϢIE�����ݽṹ*/
typedef struct
{
    VOS_UINT8                           ucLen;              /* IE�ĳ���       */
    VOS_UINT8                           aucReserve1[3];     /* ���ֽڶ��룬���� */
    VOS_UINT8                          *pucValue;           /* IE���׵�ַ     */
}NAS_ESM_MSG_IE_COMMON_STRU;

/*ESM ��¼�տ���Ϣ��TAD��Ϣ*/
typedef struct
{
    NAS_ESM_TFT_OP_TYPE_ENUM_UINT8      enTftOpType;
    VOS_UINT8                           ucSdfPfNum;         /*SDF��ǰ��Ч��PF��*/
    VOS_UINT8                           aucReserved[2];
    NAS_ESM_CONTEXT_TFT_STRU            astSdfPfInfo[NAS_ESM_MAX_SDF_PF_NUM];
}NAS_ESM_TAD_INFO_STRU;

/*ESM ��¼�տ���Ϣ��Notification Indicator��Ϣ*/
typedef struct
{
    VOS_UINT8                           ucValue;
    VOS_UINT8                           aucRsv[3];
}NAS_ESM_NOTIFICATION_IND_STRU;

/*ESM ��¼�տ���Ϣ�����ݽṹ*/
typedef struct
{
    VOS_UINT32                          bitOpPdnAddr                      : 1;
    VOS_UINT32                          bitOpApn                          : 1;
    VOS_UINT32                          bitOpEpsQos                       : 1;
    VOS_UINT32                          bitOpPco                          : 1;
    VOS_UINT32                          bitOpEsmCause                     : 1;
    VOS_UINT32                          bitOpLinkedEpsbId                 : 1;
    VOS_UINT32                          bitOpApnAmbr                      : 1;
    VOS_UINT32                          bitOpTadInfo                      : 1;
    VOS_UINT32                          bitOpTransId                      : 1;
    VOS_UINT32                          bitOpNegQos                       : 1;
    VOS_UINT32                          bitOpLlcSapi                      : 1;
    VOS_UINT32                          bitOpRadioPriority                : 1;
    VOS_UINT32                          bitOpPacketFlowId                 : 1;
    VOS_UINT32                          bitOpNotificationInd              : 1;
    VOS_UINT32                          bitOpSpare                        : 18;

    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           ucLinkedEpsbId;
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enEsmCnMsgType;     /* �տ���Ϣ���� */
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCau;           /* ESM Cause*/
    VOS_UINT8                           ucPti;
    VOS_UINT8                           aucReserved[3];

    NAS_ESM_TAD_INFO_STRU               stTadInfo;
    NAS_ESM_CONTEXT_LTE_QOS_STRU        stSdfQosInfo;
    NAS_ESM_CONTEXT_IP_ADDR_STRU        stPdnAddrInfo;
    APP_ESM_APN_INFO_STRU               stApnInfo;
    NAS_ESM_CONTEXT_APN_AMBR_STRU       stApnAmbrInfo;
    NAS_ESM_CONTEXT_PCO_STRU            stPcoInfo;
    NAS_ESM_CONTEXT_QOS_STRU            stCntxtQosInfo;
    NAS_ESM_CONTEXT_TRANS_ID_STRU       stTransId;
    VOS_UINT8                           ucLlcSapi;
    VOS_UINT8                           ucRadioPriority;
    VOS_UINT8                           ucPacketFlowId;
    VOS_UINT8                           aucReserved2[1];
    NAS_ESM_NOTIFICATION_IND_STRU       stNotificationInd;
}NAS_ESM_NW_MSG_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_STATE_INFO_STRU
 �ṹ˵��  : ��̬��ṹ��
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpAppMsgRecord                 : 1;
    VOS_UINT32                          bitOpNwMsgRecord                  : 1;
    VOS_UINT32                          bitOpSpare                        : 30;

    VOS_UINT32                          ulCid;              /*��ЧֵΪ0x20����ЧֵΪ0~31*/
    VOS_UINT32                          ulEpsbId;           /*��ӦEPS����ID*/
    VOS_UINT32                          ulLinkedEpsbId;     /*��˳��ع�����EPS����ID*/

    NAS_ESM_PROC_TRANS_STATE_ENUM_UINT8 enProcTransTState;  /* SM��PROCEDURE_TRANSACTION״̬ */
    NAS_ESM_BEARER_STATE_ENUM_UINT8     enBearerCntxtState; /* SM�����ĵ�״̬ */
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enBearerCntxtType;  /* �����Ķ�Ӧ���ص����� */
    VOS_UINT8                           ucIsWaitForUserAnswer;/* �Ƿ��ڵȴ��û��ظ� */
    NAS_ESM_APP_IND_TYPE_ENUM_UINT32    enAppIndType;       /* ESM�ϱ�APP���� */

    NAS_ESM_PDN_REQ_TYPE_ENUM_UINT8     enPdnReqType;       /* PDN�����������ͣ�Ŀǰ����CL��ģ����ʹ�� */

    NAS_ESM_BEARER_DATA_CNF_ENUM_UINT8  enEsmBearerDataCnf;
    VOS_UINT8                           aucRsv[2];

    NAS_ESM_APP_MSG_RECORD_STRU         stAppMsgRecord;     /*App��Ϣ��¼*/
    NAS_ESM_NW_MSG_RECORD_STRU          stNwMsgRecord;      /*�տ���Ϣ��¼*/
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /*��ʱ��ʹ����Ϣ*/

    NAS_ESM_NW_MSG_STRU                *pstDecodedNwMsg;    /* ����������������Ϣ */
} NAS_ESM_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : EMM_ESM_INTRA_DATA_IND_STRU
 �ṹ˵��  : �ڲ������ID_EMM_ESM_DATA_IND��Ϣ
 ***************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgId;           /* ��Ϣͷ */
    NAS_ESM_NW_MSG_STRU                  stEsmNwMsgIE;      /* �������������Ϣ */
}EMM_ESM_INTRA_DATA_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_ATTACHING_BUFF_ITEM_STRU
 �ṹ˵��  : �洢�����Ժ��������Ϣ�Լ��������Ľṹ��
 ***************************************************************************/
typedef struct
{
    NAS_ESM_CAUSE_ENUM_UINT8            enDecodeRslt;
    VOS_UINT8                           aucReserved[3];
    EMM_ESM_INTRA_DATA_IND_STRU         stDecodedNwMsg;
}NAS_ESM_ATTACHING_BUFF_ITEM_STRU;

/* PTI�����¼�ṹ�� */
typedef struct
{
    VOS_UINT8                           ucPti;
    VOS_UINT8                           ucEpsbId;
    VOS_UINT8                           aucReserved[2];

    VOS_UINT32                          ulOpId;             /* ���ڱ�ʶ���͵���Ϣ */
    NAS_ESM_TIMER_STRU                  stTimerInfo;        /* ��ʱ������ */
    EMM_ESM_MSG_STRU                    stEsmMsg;           /* �ظ���Ϣ���� ACCEPT��Ϣ��REJ��Ϣ */
} NAS_ESM_PTI_BUFF_ITEM_STRU;

/* ESM����ṹ�� */
typedef struct
{
    VOS_UINT8                           ucPtiBuffItemNum;
    VOS_UINT8                           ucAttBuffItemNum;
    VOS_UINT8                           aucReserved[2];

    VOS_VOID                           *paPtiBuffer[NAS_ESM_MAX_PTI_BUFF_ITEM_NUM];
    VOS_VOID                           *paAttBuffer[NAS_ESM_MAX_ATTACHING_BUFF_ITEM_NUM];
}NAS_ESM_BUFF_MANAGE_INFO_STRU;

/* Info for Attach Bearer Re-establishment feature */
typedef struct
{
    LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU stNvData;    /* NV data */
    VOS_UINT32                           ulEpsbId;    /* EBI of attach bearer */
    NAS_ESM_TIMER_STRU                   stTimerInfo; /* timer info */
} NAS_ESM_ATTACH_BEARER_REEST_INFO_STRU;

/*ESM ʵ������ݽṹ*/
typedef struct
{
    NAS_ESM_PS_REGISTER_STATUS_ENUM_UINT8 enRegisterStatus;  /* EMM��PS��ע��״̬  */
    NAS_ESM_L_MODE_STATUS_ENUM_UINT8    enLModeStatus;      /* Lģ״̬ */
    VOS_UINT8                           ucCurMaxPTI;        /* ��ǰ��ʹ�õ�PTI�����ֵ */
    VOS_UINT8                           ucCurMaxGwAuthId;   /*��ǰ��ʹ�õ�GwAuthId�����ֵ*/

    VOS_UINT32                          ulCurMaxOpId;       /* ��ǰ��ʹ�õ�OpId�����ֵ */
    VOS_UINT32                          ulCurPdnConNum;     /*��ǰPDN��������*/

    VOS_UINT8                           ucEsmErabmSessionId;     /* ESM֪ͨREABM ACT_IND��Ϣʱʹ�� */
    VOS_UINT8                           aucRsv[3];

    /* ���ش洢������SDF����  */
    NAS_ESM_SDF_PARA_STRU               astSdfPara[NAS_ESM_MAX_CID_NUM];

    /*�Ѽ�����ص�SDF����*/
    NAS_ESM_SDF_CNTXT_INFO_STRU         astSdfCntxtInfo[NAS_ESM_MAX_CID_NUM];

    /* EPS������Ϣ  */
    NAS_ESM_EPSB_CNTXT_INFO_STRU        astEpsbCntxtInfo[NAS_ESM_MAX_EPSB_NUM];

    /*�洢UE�����������Ϣ*/
    NAS_ESM_STATE_INFO_STRU             astStateTable[NAS_ESM_MAX_STATETBL_NUM];

    NAS_ESM_PDP_MANAGE_INFO_STRU        stEsmBearerManageInfo;/* ���ع�����Ϣ  */

    NAS_ESM_SND_NW_MSG_STRU             stEsmSndNwMsg;

    NAS_ESM_BUFF_MANAGE_INFO_STRU       stEsmBuffManageInfo;

    NAS_ESM_ATTACH_BEARER_REEST_INFO_STRU stAttachBearerReestInfo;

    NAS_ESM_TIMER_STRU                  stDeferRelNonEmcTimerInfo;

    VOS_UINT32                          ulBearerSessionStartFlag;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej50Info;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej51Info;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstPdnRej66Info;
    NAS_ESM_TIMER_STRU                  stBackOffWaitUsimTimerInfo;
} NAS_ESM_ENTITY_STRU;

/*ESM ���յ���Ϣͷ�����ݽṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
}NAS_ESM_GENERAL_MSG_HEADER_STRU;


/* ���������������Ͷ��� */
typedef VOS_VOID (                  * NAS_ESM_ACTION_FUN )
(
    VOS_VOID *                                              /* ��Ϣָ�� */
);


/* ������ṹ */
typedef struct ACT
{
    VOS_UINT32                          ulEventType;        /* �¼����� */
    NAS_ESM_ACTION_FUN                       pfActionFun;        /* �������� */
}  NAS_ESM_ACT_STRU;


/* ״̬ת�Ʊ�ṹ */
typedef struct STA
{
    VOS_UINT32                          ulState;            /* ״̬,�����ֽ���Ч: 0x0000_0x��_0x�� */
    VOS_UINT32                          ulSize;             /* ������Ĵ�С�ֽ�������ACT�ṹ�Ĵ�С */
    NAS_ESM_ACT_STRU                    *pActTable;         /* ������Ļ���ַ                      */
}  NAS_ESM_STA_STRU;

/*****************************************************************************
 �ṹ��    : NAS_ESM_APP_ERROR_MAPPING_STRU
 �ṹ˵��  : APP�����������������ӳ��ṹ
 ***************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAppErrorCode;
    VOS_UINT32                          enEsmCause;
}NAS_ESM_APP_ERROR_MAPPING_STRU;

/*****************************************************************************
�ṹ����    :NAS_ESM_MSG_VALIDATE_FUN
ʹ��˵��    :��Ϣ��֤����ָ��ṹ
*****************************************************************************/
typedef VOS_UINT32 ( * NAS_ESM_MSG_VALIDATE_FUN)
(
    const NAS_ESM_NW_MSG_STRU *               /* �����Ŀտ���Ϣָ�� */
);

/*****************************************************************************
�ṹ����    :NAS_ESM_MSG_VAL_ACT_STRU
ʹ��˵��    :��Ϣ��֤�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       aucRsv[3];
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8   enMsgTp;            /* ��Ϣid */
    NAS_ESM_MSG_VALIDATE_FUN        pstMsgVldtFun;      /* ��Ϣ��⺯��ָ��*/
}NAS_ESM_MSG_VAL_ACT_STRU;



typedef struct
{
    MSG_HEADER_STRU                          stMsgHeader;     /*_H2ASN_Skip*/
    NAS_ESM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus;   /* ��ʱ��״̬*/

    NAS_ESM_TIMER_PARA_ENUM_UINT8             enTimerId;       /* ��ʱ��ID*/
    VOS_UINT8                                usRsv[3];
    VOS_UINT32                               ulTimerRemainLen;/* ��ʱ����ʱ�� */
}NAS_ESM_TIMER_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/* PCO ���ر�ʶ */
extern VOS_UINT32                                           g_ulPcoFlag;
#define NAS_ESM_GetPcoFlag()                                (g_ulPcoFlag)

extern VOS_UINT32                                           g_ulDelSdfWithQosFlag;
#define NAS_ESM_GetDelSdfWithQosFlag()\
    (((g_ulDelSdfWithQosFlag)== (LPS_NV_GET_DEL_SDF_WITH_QOS_BIT))?(NAS_ESM_DEL_SDF_WITH_QOS_ON):(NAS_ESM_DEL_SDF_WITH_QOS_OFF))

/*P-CSCF���ܿ���*/
extern VOS_UINT32                                            g_ulPcscfFlag;
#define NAS_ESM_GetPcscfFlag()                              (g_ulPcscfFlag)

/*BCM���ܿ���*/
extern VOS_UINT32                                            g_ulBcmFlag;
#define NAS_ESM_GetBcmFlag()                                (g_ulBcmFlag)
/*MD5���ܿ���*/
extern VOS_UINT32                                            g_ulMd5Flag;
#define NAS_ESM_GetMd5Flag()                                (g_ulMd5Flag)

extern VOS_UINT8                                            g_aucChallengeValue[NAS_ESM_AUTH_CHALLENGE_VALUE_LEN];
#define NAS_ESM_GetChallegeValue()                          (g_aucChallengeValue)

extern VOS_UINT8                                            g_aucChallegeRspValue[NAS_ESM_AUTH_RESPONSE_VALUE_LEN];
#define NAS_ESM_GetChallegeRspValue()                       (g_aucChallegeRspValue)
/*PC REPLAY MODIFY BY LEILI BEGIN*/
/*ESM  ʵ����Ϣ*/
extern NAS_ESM_ENTITY_STRU                                  g_stNasEsmEntity;
/*PC REPLAY MODIFY BY LEILI END*/
extern NAS_ESM_ENTITY_STRU                                 *pg_stNasEsmEntity;

#define NAS_ESM_Entity()                                   (pg_stNasEsmEntity)

/*ͨ��PCO����IPV6 DNS���ܿ���*/
/*extern NAS_ESM_GET_IPV6_DNS_CTRL_ENUM_UINT32     g_enIpv6DnsFlag;
 */
#define NAS_ESM_GetIpv6DnsFlag()                            (g_enIpv6DnsFlag)

extern  VOS_UINT32                                          g_ulLocalIpSupportFlag;
#define NAS_ESM_GetLocalIpSupFlag()                            (g_ulLocalIpSupportFlag)

extern  VOS_UINT32                                          g_ulNwLocalIpSupportFlag;
#define NAS_ESM_GetNwLocalIpSupFlag()                       (g_ulNwLocalIpSupportFlag)



#define NAS_ESM_GetEmmStatus()\
                  ((NAS_ESM_Entity())->enRegisterStatus)

#define NAS_ESM_GetLModeStatus()\
                  ((NAS_ESM_Entity())->enLModeStatus)

#define NAS_ESM_GetSdfCntxtInfo(ulCid)\
                  (&((NAS_ESM_Entity())->astSdfCntxtInfo[(ulCid)]))

#define NAS_ESM_SetEmmStatus(ucEmmStatus)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_NORM_LOG("EMM Register Status change----");\
             NAS_ESM_PRINT_EMMSTA(NAS_ESM_GetEmmStatus());\
             NAS_ESM_NORM_LOG("==>>");\
             (NAS_ESM_Entity())->enRegisterStatus = (ucEmmStatus);\
             NAS_ESM_PRINT_EMMSTA(ucEmmStatus);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }

#define NAS_ESM_SetLModeStatus(ucLModeStatus)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_NORM_LOG("ESM L Mode Status change----");\
             NAS_ESM_PRINT_LMODESTA(NAS_ESM_GetLModeStatus());\
             NAS_ESM_NORM_LOG("==>>");\
             (NAS_ESM_Entity())->enLModeStatus = (ucLModeStatus);\
             NAS_ESM_PRINT_LMODESTA(ucLModeStatus);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }

#define NAS_ESM_GetStateTblAddr(ulStateTblIndex)\
                  (&((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]))
#define NAS_ESM_GetStateTblBearerState(ulStateTblIndex)\
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enBearerCntxtState)
#define NAS_ESM_GetStateTblAppMsgType(ulStateTblIndex) \
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).stAppMsgRecord.enAppMsgType)

#define NAS_ESM_GetSdfParaAddr(ulCID)\
                  (&((NAS_ESM_Entity())->astSdfPara[(ulCID)]))

#define NAS_ESM_GetBearerManageInfoAddr()\
                  (&((NAS_ESM_Entity())->stEsmBearerManageInfo))
#define NAS_ESM_GetEsmSndNwMsgAddr()\
                  (&((NAS_ESM_Entity())->stEsmSndNwMsg))
#define NAS_ESM_GetCurEsmSndNwMsgAddr()\
                  ((NAS_ESM_GetEsmSndNwMsgAddr())->pucNwMsg)
#define NAS_ESM_UpdateEsmSndNwMsgLen(ulNwMsgAddLen)\
                  ((NAS_ESM_GetEsmSndNwMsgAddr())->ulNwMsgSize = ulNwMsgAddLen)
#define NAS_ESM_GetEsmSndNwMsgLen()\
                  (NAS_ESM_GetEsmSndNwMsgAddr()->ulNwMsgSize)
#define NAS_ESM_ClearEsmSndNwMsgAddr() \
        {                                                            \
            if (VOS_NULL_PTR != NAS_ESM_GetCurEsmSndNwMsgAddr())     \
            {                                                        \
                NAS_ESM_MEM_FREE(NAS_ESM_GetCurEsmSndNwMsgAddr());   \
            }                                                        \
                                                                     \
            NAS_ESM_MEM_SET(NAS_ESM_GetEsmSndNwMsgAddr(),            \
                             NAS_ESM_NULL,                           \
                             sizeof(NAS_ESM_SND_NW_MSG_STRU));       \
         }

#define NAS_ESM_GetStateTblTimer(ulStateTblIndex)\
                  (&((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)].\
                                                                   stTimerInfo))

#define NAS_ESM_GetProcTransState(ulStateTblIndex)\
                  (((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enProcTransTState)

#define NAS_ESM_SetProcTransState(ulStateTblIndex,enDestState)\
        {\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
             NAS_ESM_LOG1("SM Procedure Transaction state change----StateTblIndex : ", ulStateTblIndex);\
             NAS_ESM_PRINT_PROCTRANSSTA(NAS_ESM_GetProcTransState(ulStateTblIndex));\
             NAS_ESM_NORM_LOG("==>>");\
             ((NAS_ESM_Entity())->astStateTable[(ulStateTblIndex)]).enProcTransTState = (enDestState);\
             NAS_ESM_PRINT_PROCTRANSSTA(enDestState);\
             NAS_ESM_NORM_LOG("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");\
        }

#define NAS_ESM_GetCurMaxOpIdValue()   ((NAS_ESM_Entity())->ulCurMaxOpId)
#define NAS_ESM_SetCurMaxOpIdValue(ulOpId)\
                  ((NAS_ESM_Entity())->ulCurMaxOpId = (ulOpId))

#define NAS_ESM_GetErabmSessionIdValue()      ((NAS_ESM_Entity())->ucEsmErabmSessionId)
#define NAS_ESM_SetErabmSessionIdValue(ucId)\
                   ((NAS_ESM_Entity())->ucEsmErabmSessionId = (ucId))

#define NAS_ESM_GetCurMaxPTIValue()     ((NAS_ESM_Entity())->ucCurMaxPTI)
#define NAS_ESM_SetCurMaxPTIValue(ucPti) ((NAS_ESM_Entity())->ucCurMaxPTI = (ucPti))
#define NAS_ESM_GetCurMaxGwAuthIdVaule() ((NAS_ESM_Entity())->ucCurMaxGwAuthId)
#define NAS_ESM_SetCurMaxGwAuthIdVaule(ucGwAuthId) ((NAS_ESM_Entity())->ucCurMaxGwAuthId = (ucGwAuthId))

#define NAS_ESM_GetCurPdnNum()     ((NAS_ESM_Entity())->ulCurPdnConNum)
#define NAS_ESM_SetCurPdnNum(ucPdnNum) ((NAS_ESM_Entity())->ulCurPdnConNum = (ucPdnNum))

#define NAS_ESM_GetEsmBufferManageInfoAddr()     (&(NAS_ESM_Entity())->stEsmBuffManageInfo)

#define NAS_ESM_GetEsmAppErrorMapArrayLen()      (sizeof(g_astEsmAppErrorMappingTbl)/sizeof(NAS_ESM_APP_ERROR_MAPPING_STRU))
#define NAS_ESM_GetEsmAppErrorMapTbl()           (g_astEsmAppErrorMappingTbl)
#define NAS_ESM_GetCid(ulEpsbId)\
                ((ulEpsbId - NAS_ESM_MIN_EPSB_ID) + NAS_ESM_MAX_UE_CONTRUL_CID + 1)

#define NAS_ESM_AttachBearerReestEnable()        (NAS_ESM_Entity()->stAttachBearerReestInfo.stNvData.bitOpAttachBearerReest)
#define NAS_ESM_SetAttachBearerId(Id)            (NAS_ESM_Entity()->stAttachBearerReestInfo.ulEpsbId = Id)
#define NAS_ESM_GetAttachBearerId()              (NAS_ESM_Entity()->stAttachBearerReestInfo.ulEpsbId)
#define NAS_ESM_GetAttachBearerReestTimerLen()   (NAS_ESM_Entity()->stAttachBearerReestInfo.stNvData.ulReestTimeLen)
#define  NAS_ESM_GetBearerSessionStartFlag()                                (NAS_ESM_Entity()->ulBearerSessionStartFlag)
#define  NAS_ESM_SetBearerSessionStartFlag(ulBearerSessionStartFlag)        (NAS_ESM_GetBearerSessionStartFlag()  = (ulBearerSessionStartFlag))
#define NAS_ESM_GetEsmPdnRejCause50InfoAddr()     (NAS_ESM_Entity()->pstPdnRej50Info)
#define NAS_ESM_GetEsmPdnRejCause51InfoAddr()     (NAS_ESM_Entity()->pstPdnRej51Info)

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_ESM_SetBearCntxtType
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_TYPE_ENUM_UINT8      enDestType
);
extern NAS_ESM_BEARER_TYPE_ENUM_UINT8  NAS_ESM_GetBearCntxtType( VOS_UINT32 ulEpsbId );
extern NAS_ESM_BEARER_STATE_ENUM_UINT8 NAS_ESM_GetBearCntxtState(VOS_UINT32 ulEpsbId);
extern VOS_VOID NAS_ESM_SetBearCntxtState
(
    VOS_UINT32                          ulEpsbId,
    NAS_ESM_BEARER_STATE_ENUM_UINT8     enDestState
);
extern VOS_VOID  NAS_ESM_SetBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern VOS_VOID  NAS_ESM_ClearBearCntxtLinkCid
(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern VOS_VOID  NAS_ESM_UpdateBearCntextLinkCid
(
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg,
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulCid
);
extern NAS_ESM_EPSB_CNTXT_INFO_STRU * NAS_ESM_GetEpsbCntxtInfoAddr( VOS_UINT32 ulEpsbId );
extern VOS_VOID NAS_ESM_AssignOpId(VOS_UINT32         *pulOpId);
extern VOS_VOID NAS_ESM_AssignPTI(VOS_UINT32         *pulPti);
extern VOS_VOID NAS_ESM_AssignGwIpId( VOS_UINT8   *pucGwAuthId);
extern VOS_VOID NAS_ESM_GetGwAuthChallengeValue( VOS_UINT8 *pucValue );
extern VOS_VOID  NAS_ESM_GetGwAuthRpsValue
(
    const VOS_UINT8                    *pucPwd,
    VOS_UINT8                           ucPwdLen,
    VOS_UINT8                           ucId,
    const VOS_UINT8                    *pucChlgVal,
    VOS_UINT8                          *pucRspVal
);
extern VOS_UINT32  NAS_ESM_QueryPfInTft
(
    VOS_UINT8                           ucPacketFilterID,
    const APP_ESM_TFT_INFO_STRU        *pstCntxtTftInfo,
    VOS_UINT32                          ulPfNum,
    VOS_UINT32                         *pulIndex
);
extern VOS_VOID NAS_ESM_ClearEsmBearerResource( VOS_UINT32  ulEpsbId );
extern VOS_VOID NAS_ESM_ClearEsmResource( VOS_VOID );
extern VOS_UINT32  NAS_ESM_GetLinkCidByActiveCid
(
    VOS_UINT32                          ulCid
);
extern VOS_UINT32 NAS_ESM_GetStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByCid(VOS_UINT32  ulCId,
                                              VOS_UINT32  *pulEpsbId);
extern VOS_UINT32 NAS_ESM_QueryEpsbCntxtTblByEpsbId(VOS_UINT32  ulEpsbId,
                                              VOS_UINT32  *pulCId);
extern VOS_UINT32 NAS_ESM_QueryFirstSdfIdByEpsbId
       (
           VOS_UINT32                          ulEpsbId,
           VOS_UINT32                         *pulCid
       );
extern VOS_UINT32 NAS_ESM_QuerySdfIdByEpsbIdAndPfId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                           ucPacketFilterId,
    VOS_UINT32                         *pulCid
);

extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByCid(VOS_UINT32 ulCidRecv,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByEpsbId(VOS_UINT32 ulEpsbId,VOS_UINT32 *ulStateId);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexByPti(VOS_UINT8 ucPti,VOS_UINT32 *ulStateId);


extern VOS_VOID NAS_ESM_RelStateTblResource(VOS_UINT32  ulStateTblIndex );


extern NAS_ESM_QUERY_CID_RSLT_ENUM_UINT8  NAS_ESM_QuerySdfId
(
    const NAS_ESM_NW_MSG_STRU          *pstEsmNwMsgIE,
    VOS_UINT32                         *pulCid
);

extern VOS_UINT32  NAS_ESM_GetBearerLinkedCidNum
(
    VOS_UINT32                          ulEpsbId
);

extern VOS_UINT32 NAS_ESM_GetAppErrorByEsmCause
(
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
);

extern VOS_UINT32 NAS_ESM_QueryNWPacketFilterID
(
    VOS_UINT8                           ucPacketFilterID,
    VOS_UINT32                          ulCID,
    VOS_UINT8                          *ucNWPacketFilterID
);


extern VOS_UINT32  NAS_ESM_IsTftInfoValid
(
    const APP_ESM_TFT_INFO_STRU               *pstAppTftInfo
);

extern VOS_UINT32  NAS_ESM_IsSdfQosValid
(
    const APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo
);

extern VOS_UINT32  NAS_ESM_IsGwAuthInfoValid
(
    const APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
);

extern VOS_UINT32  NAS_ESM_IsSdfParaOtherInfoValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
);

extern VOS_UINT32  NAS_ESM_IsSdfParaValid
(
    const NAS_ESM_SDF_PARA_STRU           *pstSdfPara
);
extern VOS_UINT32  NAS_ESM_IsGbrBearer( VOS_UINT8 ucQci );
extern VOS_VOID NAS_ESM_ClearEsmBuffItem
(
    NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
    VOS_UINT32                          ulIndex
);
extern VOS_VOID  NAS_ESM_ClearEsmBuff( VOS_VOID );
extern NAS_ESM_TIMER_STRU* NAS_ESM_GetPtiBuffItemTimer
       (
           VOS_UINT32                          ulIndex
       );
extern NAS_ESM_TIMER_STRU*  NAS_ESM_GetTimer
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_GetTimerLen
       (
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID  NAS_ESM_PrintTimeStartInfo
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID  NAS_ESM_PrintTimeStopInfo
       (
            VOS_UINT32                          ulIndex,
            NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_QueryOverduePtiBuffItem
       (
           VOS_UINT8                           ucPti,
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                         *pulIndex
       );
extern VOS_UINT32  NAS_ESM_QueryPtiBuffItemByEpsbId
       (
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                         *pulIndex
       );
extern VOS_UINT32  NAS_ESM_QueryPtiBuffItemByPti
       (
           VOS_UINT8                           ucPti,
           VOS_UINT32                         *pulIndex
       );

extern VOS_UINT32 NAS_ESM_QuerySdfIdByEpsbIdAndPfId
       (
           VOS_UINT8                           ucEpsbId,
           VOS_UINT8                           ucPacketFilterId,
           VOS_UINT32                         *pulCid
       );
extern VOS_UINT32  NAS_ESM_SavePtiBuffItem
       (
           VOS_UINT8                           ucPti,
           VOS_UINT8                           ucEpsbId,
           VOS_UINT32                          ulLength,
           const VOS_UINT8                    *pucSendMsg
       );
extern VOS_VOID NAS_ESM_TimerStart
       (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_VOID NAS_ESM_TimerStop
       (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
       );
extern VOS_UINT32  NAS_ESM_GetTimerMaxExpNum
       (
           NAS_ESM_TIMER_PARA_ENUM_UINT8 enTimerType
       );
extern VOS_UINT32  NAS_ESM_IsTimerNameValid
      (
           VOS_UINT32                          ulIndex,
           NAS_ESM_TIMER_PARA_ENUM_UINT8       enTimerType
      );
extern VOS_VOID* NAS_ESM_GetBuffItemAddr
      (
           NAS_ESM_BUFF_ITEM_TYPE_ENUM_UINT8   enEsmBuffType,
           VOS_UINT32                          ulIndex
      );
extern VOS_INT32  NAS_ESM_PrintAppEsmSetManageTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);


extern VOS_INT32  NAS_ESM_PrintAppEsmSetBearerTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetPdnTypeReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetEpsQosReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetGwAuthReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmAppSetResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmAppSetManageTypeResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_VOID  NAS_ESM_PrintEsmSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);

extern VOS_VOID NAS_ESM_PrintEsmRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);

extern VOS_INT32  NAS_ESM_PrintEsmAppMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

extern VOS_INT32  NAS_ESM_PrintEsmTimer
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    VOS_UINT32                           ulTimerType
);

extern VOS_VOID NAS_ESM_PrintEpsbInfo(VOS_UINT32 ulEpsbId);

extern VOS_UINT32 NAS_ESM_GetAllEpsBearerInPdn
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucEpsBearNum,
    VOS_UINT8                          *pucEspbId
);
extern VOS_UINT32  NAS_ESM_Random();
VOS_UINT32 NAS_ESM_IsExistSamePrecedenceInTft
(
    VOS_UINT32                          ulPfNum,
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTFT
);
extern VOS_VOID NAS_ESM_DHCPGetIPv4Mask
(
    const VOS_UINT8                    *pucIpv4Addr,
    VOS_UINT8                          *pucIpv4Mask
);
extern VOS_VOID NAS_ESM_DHCPGetIPv4GateWay
(
    const VOS_UINT8                    *pucIpv4Addr,
    const VOS_UINT8                    *pucIpv4Mask,
    VOS_UINT8                          *pucIpv4GateWay
);

extern VOS_VOID NAS_ESM_ClearSdfPara(VOS_UINT32  ulCid);
extern VOS_VOID NAS_ESM_ClearNwCtrlSdfPara(VOS_VOID);

extern VOS_VOID NAS_ESM_TransformPcoStru
(
    VOS_UINT8                           ucIpType,
    const NAS_ESM_CONTEXT_PCO_STRU           *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);

extern VOS_VOID NAS_ESM_Ipv4TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);
extern VOS_VOID NAS_ESM_Ipv6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);

extern VOS_VOID NAS_ESM_Ipv4v6TransformPcoStru
(
    const NAS_ESM_CONTEXT_PCO_STRU     *pstContPco,
    NAS_ESM_PCO_TRANSFORM_STRU         *pstTransPco
);
extern VOS_INT32  NAS_ESM_PrintEsmAppProcedureAbortNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  NAS_ESM_PrintEsmAppIpv6InfoNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_VOID NAS_ESM_ClearCid0StaticInfo(VOS_VOID);

extern VOS_UINT32 NAS_ESM_HasExistedEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_HasEstingEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_HasEmergencyPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_IsEmmEmcAttachedOrAttaching(VOS_VOID);
extern VOS_VOID   NAS_ESM_ClearEsmResoureWhenEstingEmcPdn(VOS_VOID);
extern VOS_VOID   NAS_ESM_DeactAllNonEmcPdn(VOS_VOID);
extern VOS_UINT32 NAS_ESM_IsDefaultEpsBearerType(VOS_UINT32 Type);
extern VOS_UINT32 NAS_ESM_QueryStateTblIndexForEmc(VOS_UINT32 *pulStateIndex);

extern VOS_VOID  NAS_ESM_SndOmEsmTimerStatus(
    NAS_ESM_TIMER_RUN_STA_ENUM_UINT32        enTimerStatus,
    NAS_ESM_TIMER_PARA_ENUM_UINT8           enTimerId,
    VOS_UINT32                              ulTimerRemainLen
);

extern VOS_INT32  NAS_ESM_PrintAppEsmSetCgdontReqMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  NAS_ESM_PrintEsmAppCgdontResult
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
/*PC REPLAY MODIFY BY LEILI BEGIN*/
extern VOS_UINT32  NAS_ESM_GetSdfPara
(
    VOS_UINT32                         *pulSdfNum,
    APP_ESM_SDF_PARA_STRU              *pstSdfPara
);
extern VOS_UINT32  NAS_ESM_GetPdpManageInfo
(
    APP_ESM_PDP_MANAGE_INFO_STRU  *pstPdpManageInfo
);


extern VOS_VOID NAS_LMM_LogIsUpSigPend
(
    EMM_ESM_UP_SINGNAL_PENDING_ENUM_UINT32  enUpSigPend
);
extern VOS_VOID NAS_LMM_LogSdfPara
(
    const VOS_UINT32                         *pulSdfNum,
    const APP_ESM_SDF_PARA_STRU        *pstSdfPara,
    VOS_UINT32                          ulRslt
);
extern VOS_VOID NAS_LMM_LogPdpManageInfo
(
    const APP_ESM_PDP_MANAGE_INFO_STRU   *pstPdpManageInfo,
    VOS_UINT32  ulRslt
);
/*PC REPLAY MODIFY BY LEILI END*/

extern VOS_UINT32 NAS_ESM_IsExistAllFailStateTable(VOS_VOID);
extern VOS_VOID NAS_ESM_SendBeginSessionNotify(VOS_VOID);
extern VOS_VOID NAS_ESM_SendEndSessionNotify(VOS_VOID);
extern VOS_UINT32  NAS_ESM_AllocEmmEsmOpId( VOS_VOID );
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas50Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas51Rej
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnHas66Rej
(
    VOS_UINT32                           ulBitOpApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_UINT32  NAS_ESM_IsCurrentApnAvailable
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          ulBitOPApnInfo,
    const APP_ESM_APN_INFO_STRU               *pstApnInfo
);
extern VOS_VOID NAS_ESM_AssignErabmSessionId(VOS_UINT8         *pucOpId);

extern VOS_UINT32 NAS_ESM_ReadUsimBackOffRpmPdpPara(VOS_VOID);
extern VOS_VOID NAS_ESM_UsimMsgDistr(VOS_VOID *pRcvMsg);
extern VOS_UINT8 NAS_ESM_IsWaitBackOffUsimCnfTimerRunning(VOS_VOID);
extern VOS_VOID NAS_ESM_ProcReadIsimFileResult(VOS_VOID *pRcvMsg);
extern VOS_UINT32 NAS_ESM_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
);

extern VOS_UINT32 NAS_ESM_QueryPdnDisconnNumInStateTbl(VOS_VOID);
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

#endif /* end of NasEsmPublic.h */
