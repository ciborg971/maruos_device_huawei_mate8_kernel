

#ifndef __CSSPUBLIC_H__
#define __CSSPUBLIC_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "CssInterface.h"
#include    "CssLphyInterface.h"
#include    "CssNvInterface.h"
#include    "LmmCssInterface.h"
#include    "LNvCommon.h"
#include    "PsTypeDef.h"
#include    "LPsNvInterface.h"
#include    "PsCommonDef.h"
#include    "PsLogdef.h"
#include    "CssOmInterface.h"
#include    "NasMmlCtx.h"
#if (VOS_OS_VER != VOS_WIN32)
#include    "NasMntn.h"
#endif
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
#define INT16_MAX                       (0x7FFF)

#define CSS_NULL_PTR                    (VOS_NULL_PTR)
#define CSS_NULL                        (0)

#define CSS_SUCC                        (0)/* 函数可能的返回值begin */
#define CSS_FAIL                        (1)
#define CSS_CAUSE_NULL_PTR              (2)/* 函数可能的返回值end */

#define CSS_OP_FALSE                    (0)
#define CSS_OP_TRUE                     (1)
#define CSS_TRUE                        (1)
#define CSS_FALSE                       (0)

#define CSS_COMM_BAND_DEFAULT_NUM       (9)

#define CSS_GSM_HIGH_THRESHOLD          (-85)
#define CSS_GSM_LOW_THRESHOLD           (-95)

#define CSS_WCDMA_HIGH_THRESHOLD        (-99)
#define CSS_WCDMA_LOW_THRESHOLD         (-100)

#define CSS_LTE_HIGH_THRESHOLD          (-90)
#define CSS_LTE_LOW_THRESHOLD           (-104)

#define CSS_RSSI_64DB                   (64)

#define CSS_FREQ_RANGE_999_100KHZ       (999)

#define CSS_MIN_OPID                    (1)
#define CSS_MAX_OPID                    (65535) /**/

#define CSS_GSM_SUPORT_OP               (0x01)
#define CSS_WCDMA_SUPORT_OP             (0x02)
#define CSS_LTE_SUPORT_OP               (0x04)


#define CSS_GSM_OP_OFFSET               (0x00)
#define CSS_WCDMA_OP_OFFSET             (0x01)
#define CSS_LTE_OP_OFFSET               (0x02)









#define CSS_PRINT_BUFF_LEN              (3096)              /* 1024每次打印预设缓存 */
extern VOS_CHAR                         g_acCssPrintBuf[CSS_PRINT_BUFF_LEN];
#define CSS_GET_CSS_PRINT_BUF()         (g_acCssPrintBuf)

#ifdef PS_ITT_PC_TEST_NAS
#define TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN           (5000)
#define TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN             (5000)
#define TI_CSS_WAIT_FOR_SCAN_IND_LEN                        (10000)
#define TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN                   (5000)
#else
#define TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF_LEN           (1000)
#define TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF_LEN             (1000)
#define TI_CSS_WAIT_FOR_SCAN_IND_LEN                        (1500)
#define TI_CSS_WAIT_FOR_STOP_SCAN_CNF_LEN                   (1000)
#endif

#define CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT           (12)
#define CSS_REBOOT_TYPE_STOP_SCAN_TIMEOUT                   (13)
#define CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL              (14)
#define CSS_REBOOT_TYPE_STOP_SCAN_FAIL                      (15)


typedef VOS_INT (*CSS_COMP_FUNC)(const VOS_VOID*, const VOS_VOID*);

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
#ifdef PS_ITT_PC_TEST
#define CSS_INFO_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String)
     */
#define CSS_INFO_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1 )
     */
#define CSS_INFO_LOG2(String, Para1, Para2) \
                     (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_INFO, String, (long)Para1, (long)Para2)
     */
#define CSS_NORM_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String)
     */
#define CSS_NORM_LOG1(String, Para1) \
                     (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG1(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1 )
     */
#define CSS_NORM_LOG2(String, Para1, Para2) \
                     (VOS_VOID)vos_printf(" %s %d %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG2(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_NORMAL, String, (long)Para1, (long)Para2)
     */
#define CSS_WARN_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String)
     */
#define CSS_WARN_LOG1(String, Para1) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1 )
     */
#define CSS_WARN_LOG2(String, Para1, Para2) \
                             (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1, (long)Para2)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_WARNING, String, (long)Para1, (long)Para2)
     */
#define CSS_ERR_LOG(String) \
                     (VOS_VOID)vos_printf(" %s\r\n",String)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String)
     */
#define CSS_ERR_LOG1(String, Para1) \
                         (VOS_VOID)vos_printf(" %s %d\r\n",String, (long)Para1)/*LPS_LOG(UE_MODULE_ESM_ID, VOS_NULL, PS_PRINT_ERROR, String, (long)Para1 )
     */

#else
/*旧打印关闭时*/
#if (!defined(_lint) && (PRINT_SWITCH == PRINT_OFF)&& (VOS_WIN32 != VOS_OS_VER))
#define CSS_INFO_LOG(String)
#define CSS_INFO_LOG1(String, Para1)
#define CSS_INFO_LOG2(String, Para1, Para2)
#define CSS_NORM_LOG(String)
#define CSS_NORM_LOG1(String, Para1)
#define CSS_NORM_LOG2(String, Para1, Para2)
#define CSS_WARN_LOG(String)
#define CSS_WARN_LOG1(String, Para1)
#define CSS_WARN_LOG2(String, Para1, Para2)
#define CSS_ERR_LOG(String)
#define CSS_ERR_LOG1(String, Para1)

#else
#define CSS_INFO_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String)
#define CSS_INFO_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1 )
#define CSS_INFO_LOG2(String, Para1, Para2) \
                     (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_INFO, String, (long)Para1, (long)Para2)
#define CSS_NORM_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String)
#define CSS_NORM_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1 )
#define CSS_NORM_LOG2(String, Para1, Para2) \
                     (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_NORMAL, String, (long)Para1, (long)Para2)
#define CSS_WARN_LOG(String) \
        {\
            (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String);\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8)VOS_NULL_PTR, \
                                        (VOS_UINT8)VOS_NULL_PTR, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_WARN_LOG1(String, Para1) \
        {\
            (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1 );\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8)Para1, \
                                        (VOS_UINT8)VOS_NULL_PTR, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_WARN_LOG2(String, Para1, Para2) \
        {\
            (VOS_VOID)LPS_LOG2(PS_PID_CSS, VOS_NULL, LOG_LEVEL_WARNING, String, (long)Para1, (long)Para2);\
            CSS_SndOmBandScanAbnormalInfo(THIS_FILE_ID, __LINE__,(CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8)Para1, \
                                            (VOS_UINT8)Para2, (VOS_UINT8)VOS_NULL_PTR);\
        }
#define CSS_ERR_LOG(String) \
                     (VOS_VOID)LPS_LOG(PS_PID_CSS, VOS_NULL, LOG_LEVEL_ERROR, String)
#define CSS_ERR_LOG1(String, Para1) \
                     (VOS_VOID)LPS_LOG1(PS_PID_CSS, VOS_NULL, LOG_LEVEL_ERROR, String, (long)Para1 )

#endif
#endif

#define CSS_MAX(a,b) (((a)>(b))?(a):(b))
#define CSS_MIN(a,b) (((a)<(b))?(a):(b))


/* 内存拷贝宏定义 */
#define CSS_MEM_CPY(pucDestBuffer, pucSrcBuffer, ulBufferLen) (VOS_VOID)PS_MEM_CPY_ALL_CHECK((pucDestBuffer),(pucSrcBuffer),(ulBufferLen))

#define CSS_MEM_SET(pucBuffer, ucData, ulBufferLen) \
            (VOS_VOID)PS_MEM_SET_ALL_CHECK( (pucBuffer), (ucData), (ulBufferLen))


#define CSS_MEM_CMP(pucDestBuffer, pucSrcBuffer, ulBufferLen)\
            PS_MEM_CMP ((pucDestBuffer), (pucSrcBuffer), (ulBufferLen))

#define CSS_ALLOC_MSG(ulLen) \
            PS_ALLOC_MSG_ALL_CHECK((PS_PID_CSS) , (ulLen))

#define CSS_FREE_MSG(pMsg) \
            PS_FREE_MSG( PS_PID_CSS, pMsg )

extern VOS_VOID CSS_Send_Msg(VOS_VOID* pMsg);

/* 发送消息 */
#define CSS_SND_MSG(pMsg)\
            CSS_Send_Msg(pMsg)


/*内存释放*/
#define CSS_MEM_FREE(pAddr)  PS_MEM_FREE(PS_PID_CSS, pAddr)

/*内存动态分配*/
#define CSS_MEM_ALLOC(ulSize)\
            PS_MEM_ALLOC_All_CHECK((PS_PID_CSS) , (ulSize))


#define CSS_NV_Read( ulId, pItemData, usItemDataLen ) \
        LPs_NvimItem_Read( ulId, pItemData, usItemDataLen)

#define CSS_GET_MSG_LENGTH(pMsg)        ((pMsg)->ulLength)
#define CSS_GET_MSG_ENTITY(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgId))

#define CSS_GET_MSG_ENTITY_BY_NAME(pMsg)        ((VOS_VOID*)&((pMsg)->ulMsgName))

/*封装写COMM消息头的宏*/
#define CSS_WRITE_COMM_MSG_HEAD(pstMsg, ulMsgID, ulReceiverPid)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = ulReceiverPid;

/*封装写LPHY消息头的宏*/
#define CSS_WRITE_LPHY_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_HPA;

/*封装写内部消息头的宏*/
#define CSS_WRITE_OM_MSG_HEAD(pstMsg, ulMsgID)\
                    (pstMsg)->ulMsgId   = (ulMsgID);\
                    (pstMsg)->ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid = PS_PID_CSS;\
                    (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid = PS_PID_CSS;

/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
    枚举名    : CSS_TIMER_ID_ENUM
    枚举说明  : 定时器ID
*****************************************************************************/
enum CSS_TIMER_ID_ENUM
{
    TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF           = 0x0000,           /* 等待设置从模定时器 */
    TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF             = 0x0001,           /* 等待设置主模定时器 */

    TI_CSS_WAIT_FOR_SCAN_IND                        = 0x0002,           /* 等待lphy上报扫频结果 */
    TI_CSS_WAIT_FOR_STOP_SCAN_CNF                   = 0x0003,           /* 等待lphy上报停止扫频结果 */

    CSS_TIMER_ID_BUTT
};
typedef VOS_UINT16 CSS_TIMER_ID_ENUM_UINT16;


/*****************************************************************************
 结构名    : CSS_MAIN_STATE_ENUM
 结构说明  : CSS层所有并行状态机的主状态的枚举定义
*****************************************************************************/
enum    CSS_MAIN_STATE_ENUM
{
    /*=================== CSS的主状态 ===================*/
    CSS_MS_IDLE                         = 0x0000,
    CSS_MS_SCAN                                 ,           /* 扫频过程中的状态 */
    CSS_MS_STOP_SCAN                            ,           /* 停止扫频过程中状态 */

    CSS_MAIN_STATE_BUTT
};
typedef VOS_UINT16 CSS_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 结构名    : CSS_SUB_STATE_ENUM
 结构说明  : CSS层所有并行状态机的子状态的枚举定义
*****************************************************************************/
enum    CSS_SUB_STATE_ENUM
{
    /*=================== CSS的子状态 ===================*/
    CSS_SS_WAIT_START_IND                   = 0x0000,           /* 等待开机的状态，只处理开机消息 */
    CSS_SS_IDLE                                     ,
    CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF            ,           /* 等待设置主模回复状态 */
    CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF          ,           /* 等待设置从模回复状态 */
    CSS_SS_WAIT_BAND_SCAN_IND                       ,           /* 等待物理层上报扫频结果状态 */
    CSS_SS_WAIT_STOP_SCAN_CNF                       ,           /* 等待物理层上报停止扫频结果状态 */

    CSS_SS_STATE_BUTT
};
typedef VOS_UINT16 CSS_SUB_STATE_ENUM_UINT16;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : CSS_COMM_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存当前处理的GUNAS/AS发送的消息
*****************************************************************************/
typedef struct
{
    /* 扫频请求进行存储 */
    VOS_UINT32                          bitOpSaveMsg : 1;
    VOS_UINT32                          bitOpHighRssi : 1; /* 存储扫频类型是否是高质量的，仅在存储REQ消息时设置为TRUE */
    VOS_UINT32                          bitOpMcc : 1;      /*是否mcc扫频*/
    VOS_UINT32                          bitOpRsv : 29;

    CSS_MSG_ID_ENUM_UINT32              enMsgId;                    /*消息名称*/
    VOS_UINT32                          ulOpid;
    VOS_UINT32                          ulReceiverPid;

    CSS_BAND_SCAN_TYPE_ENUM_UINT32      enBandScanType;             /*扫描类型*/
    VOS_UINT8                           aucMcc[2];                  /* MCC类型,MCC_BASED类型搜网时才需要携带 */
    CSS_RAT_LIST                        stRatList;                  /* 搜索BAND的rat list */


    /* 扫频结果进行存储 */
}CSS_COMM_MSG_STRU;

typedef struct
{

    HTIMER                              phTimer;            /* Timer句柄 */
    VOS_UINT16                          usName;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT16                          usPara;             /* 即 IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    VOS_UINT8                           ucResv[3];
    VOS_UINT32                          ulTimerLen;         /* Timer时长(UNIT: ms) */
}CSS_TIMER_STRU;

typedef struct
{
    VOS_UINT8                                  bitOpLteSupport: 1;
    VOS_UINT8                                  bitOpWcdmaSupport: 1;
    VOS_UINT8                                  bitOpGsmSupport: 1;
    VOS_UINT8                                  bitOpSpace: 5;

    VOS_UINT8                                  ucBandInd;
    VOS_UINT8                                  ucScanReqCount;
    VOS_UINT8                                  ucScanRsltArrayCount;

    CSS_LPHY_FREQ_RANGE_INFO_STRU             *pstScanReqArray;/* 初始化后一直存在 */
    CSS_FREQ_RANGE_STRU                       *pstScanRsltArray;
} CSS_COMM_SCAN_BAND_INFO_STRU;

typedef struct tagCSS_COMM_SCAN_BAND_NODE_STRU
{
    CSS_COMM_SCAN_BAND_INFO_STRU                  stBandInfo;
    struct tagCSS_COMM_SCAN_BAND_NODE_STRU       *pstNext;
} CSS_COMM_SCAN_BAND_NODE_STRU;

typedef struct
{
    VOS_UINT8                           ucBandCount;
    VOS_UINT8                           ucCurFreqRangeIdx;/* 当前扫频的频段索引 */
    VOS_UINT8                           aucRsv[2];
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstCurr;/* 当前扫频的BAND结点指针 */
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstHead;/* 指向头结点 */
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstTail;/* 指向尾结点，便于插入 */
} CSS_COMM_SCAN_BAND_LIST_STRU;

typedef CSS_NV_RAT_RSSI_THRESHOLD_STRU   CSS_RSSI_THRESHOLD_STRU;
typedef CSS_NV_COMM_BAND_CONFIG_STRU     CSS_COMM_BAND_INFO_STRU;



typedef struct
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState;    /* 当前处于的主状态 */
    CSS_SUB_STATE_ENUM_UINT16           enSubState;     /* 当前处于的子状态 */

    CSS_COMM_MSG_STRU                   stCommMsg;

    VOS_UINT32                          ulCssLphyOpid;  /* CSS模块和LPHY模块间的OPID */

    CSS_TIMER_STRU                      stSetInactiveModeTimer;
    CSS_TIMER_STRU                      stSetactiveModeTimer;
    CSS_TIMER_STRU                      stBandScanIndTimer;
    CSS_TIMER_STRU                      stStopBandScanTimer;

    CSS_RSSI_THRESHOLD_STRU             stRssiThreshold;           /* 用来保存NV的门限 */
    CSS_COMM_BAND_INFO_STRU             stCommBandInfo;            /* 用来保存NV的COMM BAND */

    CSS_COMM_SCAN_BAND_LIST_STRU        stCommScanBandList;
    VOS_UINT8                           aucRatSupportFlag[CSS_MAX_BAND_NUM];       /* 用来保存API结果中各个BAND的制式支持情况 */
}CSS_CONTROL_STRU;

typedef struct
{
    VOS_UINT16                          ucBand1;
    VOS_UINT16                          ucBand2;
}CSS_OVERLAP_BAND_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern CSS_LPHY_FREQ_RANGE_INFO_STRU                  g_ausCssLteBandFreq[];
extern CSS_OVERLAP_BAND_STRU                          g_aucOverLapBand[];
extern const VOS_UINT32                               g_aucOverLapBandSize;


extern CSS_CONTROL_STRU                               g_stCssControl;
extern CSS_CONTROL_STRU                              *pgstCssControl;

#define CSS_GetControlAddr()                          (&g_stCssControl)

#define CSS_GetCurMainStatus()                        (CSS_GetControlAddr()->enMainState)
#define CSS_GetCurSubStatus()                         (CSS_GetControlAddr()->enSubState)

#define CSS_GetLphyCurOpid()                          (CSS_GetControlAddr()->ulCssLphyOpid)
#define CSS_SetLphyCurOpid(ulOpid)                    (CSS_GetControlAddr()->ulCssLphyOpid = (ulOpid))



#define CSS_GetCommScanBandListAddr()                 (&(CSS_GetControlAddr()->stCommScanBandList))
#define CSS_GetCommScanBandListCurrNode()             (CSS_GetCommScanBandListAddr()->pstCurr)
#define CSS_GetCommScanBandListHeadNode()             (CSS_GetCommScanBandListAddr()->pstHead)
#define CSS_GetCommScanBandListTailNode()             (CSS_GetCommScanBandListAddr()->pstTail)
#define CSS_GetCommScanCurFreqRangeIdx()              (CSS_GetCommScanBandListAddr()->ucCurFreqRangeIdx)

#define CSS_GetLteModeTypeByBandInd(ucBandInd)        ((CSS_LPHY_BAND_IND_33 <= ucBandInd) ? CSS_LPHY_LTE_MODE_TYPE_TDD:CSS_LPHY_LTE_MODE_TYPE_FDD)




/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

extern VOS_UINT32  CSS_ReadNvCommBandConfig
(
    CSS_NV_COMM_BAND_CONFIG_STRU  *pstCssCommBandConfig
);

extern VOS_UINT32  CSS_ReadNvRssiThreshold
(
    CSS_NV_RAT_RSSI_THRESHOLD_STRU  *pstCssRssiTH
);

extern VOS_VOID CSS_FreeCommScanRsltMemory(VOS_VOID);

extern VOS_VOID CSS_StartTimer(CSS_TIMER_STRU *pstTimer);

extern VOS_VOID CSS_StopTimer(CSS_TIMER_STRU *pstTimer);

extern VOS_VOID CSS_PrintCssRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
);
extern VOS_VOID CSS_ClearLocalResource(VOS_VOID);

extern VOS_VOID   CSS_FSMTranState
(
    CSS_MAIN_STATE_ENUM_UINT16  enMainState,
    CSS_SUB_STATE_ENUM_UINT16   enSubState
);
extern VOS_VOID  CSS_SendOmBandScanResultInfoInd
(
    VOS_VOID
);
extern VOS_VOID  CSS_SendOmCommBandInfoInd
(
    CSS_COMM_BAND_INFO_STRU  *pstCssCommBandConfig
);
extern VOS_VOID  CSS_SendOmRatThresholdInfoInd
(
    CSS_RSSI_THRESHOLD_STRU  *pstCssRatThresholdConfig
);
extern VOS_VOID  CSS_SendOmBandApiInfoInd
(
    CSS_RAT_COVERAGE_STRU                           *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                    *pstBandScanResult
);
extern VOS_VOID  CSS_SendOmMmlUeSupportBandInfoInd
(
    NAS_MML_MS_BAND_INFO_STRU   *pstUeSupportBand
);
extern VOS_VOID  CSS_SndOmBandScanAbnormalInfo
(
    VOS_UINT32 ulFileName,
    VOS_UINT32 ulLineNo,
    CSS_BAND_SCAN_FAIL_REASON_ENUM_UINT8 enBandScanFailReason,
    VOS_UINT8 ucPara1,
    VOS_UINT8 ucPara2
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

#endif /* end of CssMain.h */



