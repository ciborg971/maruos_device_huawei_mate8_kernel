

#ifndef __IMSAPUBLIC_H__
#define __IMSAPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "PsCommonDef.h"
#include "LPSCommon.h"
#include "ImsaEntity.h"
#include "LPsOm.h"
#include "ImsaImsEvent.h"
#include "ImsParm.h"
#include "ImsaLrrcInterface.h"
#include "NasFileId.h"
/*zhaochen 00308719 add for USIM Interface modify begin*/
#include "UsimPsInterface.h"
/*zhaochen 00308719 add for USIM Interface modify end*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_NULL                       (0)
#define IMSA_SUCC                       (0)
#define IMSA_FAIL                       (1)
#define IMSA_OP_FALSE                   (0)
#define IMSA_OP_TRUE                    (1)
#define IMSA_TRUE                       (1)
#define IMSA_FALSE                      (0)
#define IMSA_CLIENT_ID                  (0x66)

#define IMSA_PRINT_BUFF_LEN             (3096)              /* 1024每次打印预设缓存 */
extern VOS_CHAR                         g_acImsaPrintBuf[IMSA_PRINT_BUFF_LEN];
#define IMSA_GET_IMSA_PRINT_BUF()       (g_acImsaPrintBuf)

#define IMSA_Min(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX2) : (ulX1))
#define IMSA_Max(ulX1, ulX2)            (((ulX1) > (ulX2)) ? (ulX1) : (ulX2))

#define IMSA_MOVEMENT_8                 (8)
#define IMSA_MOVEMENT_16                (16)
#define IMSA_MOVEMENT_24                (24)

#define IMSA_MSG_NOT_PROC               (0)
#define IMSA_MSG_PROCED                 (1)
#define IMSA_NV_INFO_LEN                (4)

#define IMSA_TIMER_1_TICK_10_MS         (10)            /* 1 tick为10ms */

#define IMSA_AUTH_TYPE_AKA               (0)
#define IMSA_AUTH_TYPE_DIGIST            (1)
#define IMSA_AUTH_TYPE_AKA_IPSEC         (2)

#define IMSA_USIM_MAX_OPID              (0x7F)

#ifdef PS_ITT_PC_TEST
#define IMSA_INFO_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
 */
#define IMSA_INFO_LOG1(String, Para1) \
                 (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
 */
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
 */
#define IMSA_NORM_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
 */
#define IMSA_NORM_LOG1(String, Para1) \
                 (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
 */
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
 */
#define IMSA_WARN_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
 */
#define IMSA_WARN_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1 )
 */
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1, (long)Para2)
 */
#define IMSA_ERR_LOG(String) \
                 (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
 */
#define IMSA_ERR_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String, (long)Para1 )
 */

#else
/*打印转层间打开*/
#if (!defined(_lint) && (PRINT_SWITCH == PRINT_OFF) && (VOS_WIN32 != VOS_OS_VER))
#define IMSA_INFO_LOG(String)
#define IMSA_INFO_LOG1(String, Para1)
#define IMSA_INFO_LOG2(String, Para1, Para2)
#define IMSA_NORM_LOG(String)
#define IMSA_NORM_LOG1(String, Para1)
#define IMSA_NORM_LOG2(String, Para1, Para2)
#define IMSA_WARN_LOG(String)
#define IMSA_WARN_LOG1(String, Para1)
#define IMSA_WARN_LOG2(String, Para1, Para2)
#define IMSA_ERR_LOG(String)
#define IMSA_ERR_LOG1(String, Para1)
#else
#define IMSA_INFO_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String)
#define IMSA_INFO_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define IMSA_INFO_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define IMSA_NORM_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define IMSA_NORM_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define IMSA_NORM_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define IMSA_WARN_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String)
#define IMSA_WARN_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1 )
#define IMSA_WARN_LOG2(String, Para1, Para2) \
                 (VOS_VOID)LPS_LOG2(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2)
#define IMSA_ERR_LOG(String) \
                 (VOS_VOID)LPS_LOG(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String)
#define IMSA_ERR_LOG1(String, Para1) \
                 (VOS_VOID)LPS_LOG1(PS_PID_IMSA, VOS_NULL, LOG_LEVEL_ERROR, String, (long)Para1 )

#endif
#endif

/* 内存拷贝宏定义 */
#define IMSA_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) (VOS_VOID)PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen))

#define IMSA_MEM_SET(pucBuffer, ucData, ulBufferLen) \
            (VOS_VOID)PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen))


#define IMSA_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define IMSA_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_IMSA) , (ulLen))

#define IMSA_FREE_MSG(pMsg) \
            PS_FREE_MSG( PS_PID_IMSA, pMsg )

extern VOS_VOID IMSA_Send_Msg(VOS_VOID* pMsg);

/* 发送消息 */
#define IMSA_SND_MSG(pMsg)\
            IMSA_Send_Msg(pMsg)

extern VOS_VOID IMSA_Send_Msg_Normally(VOS_VOID* pMsg);

#define IMSA_SND_MSG_NORMALLY(pMsg)\
            IMSA_Send_Msg_Normally(pMsg)


extern VOS_VOID IMSA_Send_Intra_Msg(VOS_VOID* pIntraMsg);

#define IMSA_SEND_INTRA_MSG(pIntraMsg)\
            IMSA_Send_Intra_Msg(pIntraMsg)

/*内存释放*/
#define IMSA_MEM_FREE(pAddr)  PS_MEM_FREE(PS_PID_IMSA, pAddr)

/*内存动态分配*/
#define IMSA_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_IMSA) , (ulSize))


#define IMSA_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)

#define IMSA_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define IMSA_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

#define IMSA_GET_MSG_ENTITY_BY_NAME(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgName))

/*封装写SPM消息头的宏*/
#define IMSA_WRITE_SPM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

/*封装写MMA消息头的宏*/
#define IMSA_WRITE_MSCC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = UEPS_PID_MSCC;

/*封装写IMSA内部消息头的宏*/
#define IMSA_WRITE_INTRA_MSG_HEAD(pstMsg, ulMsgID, ulLen)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;\
                    (pstMsg)->ulLength          = (ulLen - VOS_MSG_HEAD_LENGTH);

/*封装写CDS消息头的宏*/
#define IMSA_WRITE_CDS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_CDS;


/*封装写VC消息头的宏*/
#define IMSA_WRITE_VC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_VC;

/*封装写IMS消息头的宏*/
#define IMSA_WRITE_IMS_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSVA;

/*封装D2写IMSA消息头的宏*/
#define IMSA_WRITE_IMSA_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSVA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_IMSA;

/*封装写MSG消息头的宏*/
#define IMSA_WRITE_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgName         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_TAF;

/*封装写AT MSG消息头的宏*/
#define IMSA_WRITE_AT_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId         = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = WUEPS_PID_AT;

/*封装写SPM消息头的宏*/
#define IMSA_WRITE_CALL_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = WUEPS_PID_TAF;

#define IMSA_WRITE_RNIC_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ACPU_PID_RNIC;


/*封装写LRRC消息头的宏*/
#define IMSA_WRITE_LRRC_MSG_HEAD(pstMsg, ulMsgID,ulLen)\
                    (pstMsg)->stMsgHeader.ulMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulReceiverPid = PS_PID_ERRC;\
                    (pstMsg)->stMsgHeader.ulLength      = (ulLen - VOS_MSG_HEAD_LENGTH);


/*封装写MTC MSG消息头的宏*/
#define IMSA_WRITE_MTC_MSG_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId           = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = UEPS_PID_MTC;
#define IMSA_WRITE_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
                    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_IMSA; \
                    (pstHeader)->usModemId         = ModemId; \
                    (pstHeader)->usAlmId           = AlmId; \
                    (pstHeader)->usAlmLevel        = AlmLevel; \
                    (pstHeader)->usAlmType         = IMSA_ERR_LOG_ALARM_TYPE_COMMUNICATION; \
                    (pstHeader)->usAlmLowSlice     = ulSlice; \
                    (pstHeader)->usAlmHighSlice    = 0; \
                    (pstHeader)->ulAlmLength       = ulLength;

#define IMSA_WRITE_OM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = MSP_PID_DIAG_APP_AGENT;
/* zhaochen 00308719 begin for USIM Interface modify 2015-02-07 */
/*封装写USIM消息头的宏*/
/*USIM的消息头都被统一封装在了MsgHeader中*/
#define IMSA_WRITE_USIM_MSG_HEAD(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_IMSA;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;
/* zhaochen 00308719 end for USIM Interface modify 2015-02-07 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
    枚举名    : IMSA_TIMER_ID_ENUM
    枚举说明  : 定时器ID
*****************************************************************************/
enum IMSA_TIMER_ID_ENUM
{
    TI_IMSA_START_OR_STOP               = 0x0000,           /* 开关机定时器 */
    TI_IMSA_PERIOD_TRY_IMS_SRV          = 0x0001,           /* 周期性尝试IMS服务定时器 */
    TI_IMSA_PERIOD_TRY_IMS_EMC_SRV          = 0x0002,           /* 周期性尝试紧急IMS服务定时器 */

    TI_IMSA_SIP_SIGAL_PDP_ORIG          = 0x0100,           /* SIP信令承载拨号定时器 */
    TI_IMSA_SIP_SIGAL_PDP_END           = 0x0101,           /* SIP信令承载去拨号定时器 */
    TI_IMSA_WAIT_IPV6_INFO              = 0x0102,           /* 等待IPV6信息定时器 */

    TI_IMSA_REG_PROTECT                 = 0x0200,           /* 注册模块的保护定时器 */
    TI_IMSA_REG_RETRY                   = 0x0201,           /* 注册模块的重试定时器 */
    TI_IMSA_REG_PERIOD_TRY              = 0x0202,           /* 注册模块的周期尝试IMS注册定时器 */
    TI_IMSA_CALL_PROTECT                = 0x0300,           /* 呼叫模块的保护定时器 */
    TI_IMSA_CALL_RES_READY              = 0x0301,           /* 呼叫模块等待资源预留结果定时器 */
    TI_IMSA_CALL_DTMF_DURATION          = 0x0302,           /* 呼叫模块dtmf持续时长定时器 */
    TI_IMSA_CALL_DTMF_PROTECT           = 0x0303,           /* 呼叫模块dtmf保护定时器 */
    TI_IMSA_CALL_REDIAL_MAX_TIME        = 0x0304,           /* 呼叫模块重播最大时长定时器 */
    TI_IMSA_CALL_REDIAL_INTERVEL        = 0x0305,           /* 呼叫模块重播间隔定时器 */
    TI_IMSA_CALL_NORMAL_TCALL           = 0x0306,           /* NORMAL Tcall定时器*/
    TI_IMSA_CALL_EMC_TCALL              = 0x0307,           /* EMC Tcall定时器 */
    TI_IMSA_SMS_TR1M                    = 0x0400,           /* 短信TR1M定时器 */
    TI_IMSA_SMS_TR2M                    = 0x0401,           /* 短信TR2M定时器 */
    TI_IMSA_SMS_TRAM                    = 0x0402,           /* 短信TRAM定时器 */

    TI_IMSA_BACK_OFF_TX                 = 0x0500,           /* SSAC*/
    TI_IMSA_BACK_OFF_TY                 = 0x0501,           /**/

    TI_IMSA_USSD_WAIT_NET_RSP           = 0x0600,           /*USSD等待网侧响应定时器*/
    TI_IMSA_USSD_WAIT_APP_RSP           = 0x0601,           /*USSD等待上层响应定时器*/

    TI_IMSA_HIFI_ACK_PROTECT            = 0x0701,           /*HIFI数据包回执保护定时器*/

    IMSA_TIMER_ID_BUTT
};
typedef VOS_UINT16 IMSA_TIMER_ID_ENUM_UINT16;

/*del by zhaochen 00308719 for USIM Interface*/



/*****************************************************************************
    枚举名    : IMSA_SIP_NW_ERROR_CAUSE_ENUM
    枚举说明  : SIP空口拒绝原因值
*****************************************************************************/
enum IMSA_SIP_NW_ERROR_CAUSE_ENUM
{
    IMSA_SIP_NW_ERROR_CAUSE_USE_PROXY               = 305,
    IMSA_SIP_NW_ERROR_CAUSE_ALTERNATIVE_SERVICE     = 380,
    IMSA_SIP_NW_ERROR_CAUSE_UNAUTHORIZED            = 401,
    IMSA_SIP_NW_ERROR_CAUSE_REQUEST_TIMEOUT         = 408,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_INTERNAL_ERROR   = 500,
    IMSA_SIP_NW_ERROR_CAUSE_SERVICE_UNAVAILABLE     = 503,
    IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT          = 504,
    IMSA_SIP_NW_ERROR_CAUSE_BUSY_EVERYWHERE         = 600,

    IMSA_SIP_NW_ERROR_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_SIP_NW_ERROR_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
#if (FEATURE_ON == FEATURE_PTM)

typedef struct
{
    IMSA_ERR_LOG_ALM_ID_ENUM_UINT16         enAlmID;        /* 异常模块ID */
    VOS_UINT16                              usLogLevel;     /* 上报log等级 */
}IMSA_ERR_LOG_ALM_LEVEL_STRU;
#endif

typedef struct
{
    VOS_UINT8            *pData;      /*数据*/
    VOS_UINT16          usDataLen;   /*长度*/
}IMSA_ISIM_DATA_STRU;

typedef VOS_UINT32 ( * IMSA_ISIM_ACTION_FUN )
(
    const IMSA_ISIM_DATA_STRU *    /*数据指针*/
);


typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32        enIsimFileId;        /* ISIM协议文件ID*/
    IMSA_ISIM_ACTION_FUN                pfDecodeActionFun;   /* 动作函数 */
    IMSA_ISIM_ACTION_FUN                pfEncodeActionFun;   /* 动作函数 */
}IMSA_ISIM_ACT_STRU;

/*******************************************************************************
 结构名    :IMSA_DSDS_MSG_COUNT_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 统计DSDS消息个数
*******************************************************************************/
typedef struct
{
      VOS_UINT32                           ulBeginMsgCnt;
      VOS_UINT32                           ulEndMsgCnt;
}IMSA_DSDS_MSG_COUNT_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern IMSA_DSDS_MSG_COUNT_STRU  g_astImsaDsdsNotifyMsgNum[IMSA_LRRC_SESSION_TYPE_BUTT];

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


extern VOS_VOID IMSA_ReadImsaNV(VOS_VOID);

extern VOS_VOID IMSA_StartTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_StopTimer(IMSA_TIMER_STRU *pstTimer);
extern VOS_UINT32 IMSA_IsTimerRunning(const IMSA_TIMER_STRU *pstTimer);
extern VOS_VOID IMSA_GetRemainTimeLen
(
    IMSA_TIMER_STRU                    *pstTimer,
    VOS_UINT32                         *pulRemainTimeLen
);
extern VOS_UINT32 IMSA_AllocImsOpId(VOS_VOID);
extern VOS_VOID   IMSA_ResetImsOpId(VOS_VOID);
extern VOS_UINT32 IMSA_GetImsOpId(VOS_VOID);
extern VOS_VOID IMSA_SaveRcvImsNormOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsNormOpid(VOS_VOID);

extern VOS_VOID IMSA_SaveRcvImsEmcOpid(VOS_UINT32 ulImsOpid);

extern VOS_UINT32 IMSA_GetRcvImsEmcOpid(VOS_VOID);
extern VOS_UINT8 IMSA_AllocUsimOpId(VOS_VOID);
extern VOS_VOID IMSA_ResetUsimOpId(VOS_VOID);
extern VOS_UINT8 IMSA_GetUsimOpId(VOS_VOID);

extern VOS_VOID IMSA_ProcIsimStatusInd(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimRefreshInd(const VOS_VOID *pRcvMsg);

extern VOS_UINT32 IMSA_ProcReadIsimFileResult(VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ProcIsimAuthRsp(const VOS_VOID *pRcvMsg);
extern VOS_VOID IMSA_ReadIsimFile(VOS_VOID);
extern VOS_UINT32  IMSA_UtilBcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
);
extern VOS_UINT32  IMSA_UtilAsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
);


extern VOS_VOID IMSA_UtilStrNCpy(VOS_CHAR *pDst, const VOS_CHAR *pSrc, VOS_UINT32 ulLen);
extern VOS_VOID IMSA_PrintImsaSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
);
extern VOS_INT32  IMSA_PrintSpmImsaCallSupsCmdReq
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaSpmCallMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintCallImsaSrvccStatusNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsInputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_INT32  IMSA_PrintImsaImsOutputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);
extern VOS_INT32  IMSA_PrintImsaImsOutputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
);

extern VOS_VOID IMSA_PrintImsaRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID IMSA_ConfigCgi2Ims( VOS_VOID );
extern VOS_CHAR IMSA_ConverterDigit2Chacter
(
    VOS_UINT8                           ucDigit
);
extern VOS_VOID IMSA_ConfigImei2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigTimerLength2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigUeCapabilityInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigNetCapInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigAccoutInfo2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
);
extern VOS_UINT32  IMSA_AsciiToDtmfKeyEnum
(
    VOS_CHAR                            cAsciiCode,
    IMSA_IMS_DTMF_KEY_ENUM_UINT8       *penDtmfKey
);
extern VOS_VOID IMSA_ConfigSipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigVoipInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigCodeInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSsConfInfo2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConfigSecurityInfo2Ims( VOS_VOID );

extern VOS_VOID IMSA_ConfigMediaParmInfo2Ims( VOS_VOID );


extern VOS_VOID IMSA_ConfigSipPort2Ims( VOS_VOID );
extern VOS_VOID IMSA_ConverterSipPort2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
);
extern VOS_UINT32 IMSA_SetCurrentPara
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);
extern VOS_UINT32 IMSA_IsRegParaAvailable
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
);

extern VOS_VOID IMSA_SndMtcSrvConnStatusNotify(VOS_UINT8 ucIsImsExist);
extern VOS_UINT32 IMSA_IsImsExist(VOS_VOID);
extern VOS_VOID IMSA_WhenImsSrvConnStatusChangeNotifyMtc(VOS_VOID);

extern VOS_VOID IMSA_DSDS_Init(VOS_VOID);
extern VOS_INT32   IMSA_PrintErrcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);
extern VOS_VOID  IMSA_SendRrcDsdsBeginNotify
(
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8  ucSessionType
);
extern VOS_VOID  IMSA_SendRrcDsdsEndNotify
(
    IMSA_LRRC_SESSION_TYPE_ENUM_UINT8  ucSessionType
);

extern VOS_UINT32 IMSA_IsCurrentAccessTypeSupportIms(VOS_VOID);
/* zhaochen 00308719 begin for usim interface modify 2015-03-16*/
extern VOS_VOID IMSA_SndUsimAuthenticationReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType,
    VOS_UINT8                       ulOpId,
    USIMM_AUTH_DATA_UNION          *puAuth
);
extern VOS_VOID IMSA_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
);
/* zhaochen 00308719 end for usim interface modify 2015-03-16*/
#if (FEATURE_ON == FEATURE_PTM)

extern VOS_VOID IMSA_InitErrLogInfo(VOS_VOID);
extern IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8 IMSA_CallImsaState2ErrlogState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState);
extern VOS_UINT16 IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_ID_ENUM_UINT16 enAlmId);

extern VOS_UINT32 IMSA_IsErrLogNeedRecord(VOS_UINT16 usLevel);

extern VOS_UINT32 IMSA_GetErrLogRingBufContent
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern VOS_UINT32 IMSA_GetErrLogRingBufferUseBytes(VOS_VOID);
extern VOS_VOID IMSA_CleanErrLogRingBuf(VOS_VOID);
extern VOS_UINT32 IMSA_PutErrLogRingBuf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
);
extern IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8 IMSA_PsSerStates2ErrlogPsStates
(
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8 enImsaPsStates
);
extern IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8 IMSA_ConnState2ErrlogConnState(IMSA_CONN_STATUS_ENUM_UINT8 enImsaConnState);
extern IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8 IMSA_VoPsState2ErrlogVoPsState(IMSA_IMS_VOPS_STATUS_ENUM_UINT8 enImsaImsVoPsStatus);
extern IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8 IMSA_CallImsaMpty2ErrlogMpty(MN_CALL_MPTY_STATE_ENUM_UINT8 enImsaMpty);
extern IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8 IMSA_RegState2ErrlogState(IMSA_REG_STAUTS_ENUM_UINT8 enImsaRegState);
extern IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8 IMSA_RegAddrType2ErrlogRegReason(IMSA_REG_ADDR_PARAM_ENUM_UINT32 enImsaRegAddr);
#endif

extern VOS_VOID IMSA_ProcMtcMsgModem1InfoInd
(
    const VOS_VOID                     *pRcvMsg
);

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

#endif /* end of ImsaPublic.h */




