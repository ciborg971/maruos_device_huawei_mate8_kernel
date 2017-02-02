

#ifndef __TAFMTATIMERMGMT_H__
#define __TAFMTATIMERMGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MnComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*将定时器的秒转换成DOPRA定时器所需的毫秒，需要乘以1000 */
#define TIMER_S_TO_MS_1000                      (1000)

/* MTA 接收CPOS下发XML码流流程保护定时器时长 */
#define TI_TAF_MTA_CPOS_TIMER_LEN               (2 * TIMER_S_TO_MS_1000)

/* MTA启停GPS RF时钟流程保护定时器时长 */
#define TI_TAF_MTA_GPS_TIMER_LEN                (1 * TIMER_S_TO_MS_1000)

/* ^nmr等待接入层回复nmr数据查询结果保护定时器时长 */
#define TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF_TIMER_LEN            (3 * TIMER_S_TO_MS_1000)

#define TAF_MTA_CTX_MAX_TIMER_NUM                           (6)

#define TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF_TIMER_LEN       (1 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF_TIMER_LEN  (2 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF_TIMER_LEN  (2 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_AS_ECID_SET_CNF_TIMER_LEN           (3 * TIMER_S_TO_MS_1000)


#define TAF_MTA_RF_LCD_TIMER_INTERVAL_DEFAULT               (60 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_DSP_INIT_CNF_TIMER_LEN              (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)

#define TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#define TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_OPTION_CNF_TIMER_LEN       (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_STATE_CNF_TIMER_LEN        (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_PREFERENCE_CNF_TIMER_LEN           (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_SIB16_NETWORK_TIME_CNF_TIMER_LEN   (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_BSSI_SIGNAL_LEVEL_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_NETWORK_INFO_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_EMBMS_STATUS_CNF_TIMER_LEN              (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_UNSOLICITED_CFG_CNF_TIMER_LEN      (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_LOW_POWER_CONSUMPTION_CNF_TIMER_LEN     (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_MBMS_INTERESTLIST_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_MBMS_AVL_SERVICE_LIST_CNF_TIMER_LEN     (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_SET_LTE_WIFI_COEX_CNF_TIMER_LEN             (6 * TIMER_S_TO_MS_1000)
/* Added by w00316404 for eMBMS project, 2015-5-22, end */


#define TI_TAF_MTA_WAIT_SET_FR_CNF_TIMER_LEN                (3 * TIMER_S_TO_MS_1000)

/* Added by zwx247453 for Refclkfreq, 2015-06-17, begin */
#define TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND_TIMER_LEN       (1 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF_TIMER_LEN    (3 * TIMER_S_TO_MS_1000)
/* Added by zwx247453 for Refclkfreq, 2015-06-17, end */

#define TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF_TIMER_LEN         (2 * TIMER_S_TO_MS_1000)

/* Added by z00328328 for TX_POWER_CHR, 2015-10-23, begin */
#define TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF_TIMER_LEN        (2 * TIMER_S_TO_MS_1000)
/* Added by z00328328 for TX_POWER_CHR, 2015-10-23, end */

/* Added by lwx277467 for Transmission Mode, 2015-07-30, Begin */
#define TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
/* Added by lwx277467 for Transmission Mode, 2014-07-30, End */

/* Added by lwx277467 for Transmission Mode, 2015-07-30, Begin */
#define TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
#define TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF_TIMER_LEN         (3 * TIMER_S_TO_MS_1000)
/* Added by lwx277467 for Transmission Mode, 2014-07-30, End */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_MTA_TIMER_ID_ENUM
{
    /* CPOS下MTA等待AT下发XML码流保护定时器 */
    TI_TAF_MTA_WAIT_AT_SET_CPOS_CNF                 = 0,

    /* GPS时钟G模式启停保护定时器 */
    TI_TAF_MTA_WAIT_GPHY_SET_CGPSCLOCK_CNF,

    /* GPS时钟W模式启停保护定时器 */
    TI_TAF_MTA_WAIT_WPHY_SET_CGPSCLOCK_CNF,

    TI_TAF_MTA_WAIT_AS_QRY_NMR_CNF,

    TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,

    TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF,

    TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF,

    TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF,

    TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
    TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,

    TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
    TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,

    TI_TAF_MTA_WAIT_AS_ECID_SET_CNF,
    TI_TAF_MTA_WAIT_DSP_INIT_CNF,

    TI_TAF_MTA_RF_LCD_MIPI_CLK_REPORT,

    TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,

    TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,

    TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,

    TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,

    /* Added by w00316404 for eMBMS project, 2015-5-22, begin */
    TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
    TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
    TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,
    /* Added by w00316404 for eMBMS project, 2015-5-22, end */

    TI_TAF_MTA_WAIT_SET_FR_CNF,

    /* Added by zwx247453 for Refclkfreq, 2015-06-17, begin */
    TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,
    TI_TAF_MTA_WAIT_QRY_AFCLOCK_STATUS_CNF,
    /* Added by zwx247453 for Refclkfreq, 2015-06-17, end */

    TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF,

	/* Added by lwx277467 for Transmission Mode, 2015-07-30, Begin */
    TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,
    /* Added by lwx277467 for Transmission Mode, 2015-07-30, End */

    /* Added by lwx277467 for UE Mode, 2015-09-07, Begin */
    TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF,
    TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF,
    /* Added by lwx277467 for UE Mode, 2015-09-07, End */

    /* Added by z00328328 for TX_POWER_CHR, 2015-10-23, begin */
    TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF,
    /* Added by z00328328 for TX_POWER_CHR, 2015-10-23, end */

    TI_TAF_MTA_TIMER_BUTT
};
typedef VOS_UINT32  TAF_MTA_TIMER_ID_ENUM_UINT32;
enum TAF_MTA_TIMER_STATUS_ENUM
{
    TAF_MTA_TIMER_STATUS_STOP                       = 0,    /* 定时器停止状态 */
    TAF_MTA_TIMER_STATUS_RUNING,                            /* 定时器运行状态 */
    TAF_MTA_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MTA_TIMER_STATUS_ENUM_UINT8;


enum TAF_MTA_TIMER_START_RESULT_ENUM
{
    TAF_MTA_TIMER_START_SUCCEE              = 0,            /* 定时器启动成功 */
    TAF_MTA_TIMER_START_FAILURE,                            /* 定时器启动失败 */

    TAF_MTA_TIMER_START_BUTT
};
typedef VOS_UINT8 TAF_MTA_TIMER_START_RESULT_ENUM_UINT8;
/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
/*****************************************************************************
  5 消息头定义
*****************************************************************************/
/*****************************************************************************
  6 消息定义
*****************************************************************************/
/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

typedef struct
{
    HTIMER                              hTimer;             /* 定时器的运行指针 */
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;          /* 定时器的ID */
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
} TAF_MTA_TIMER_CTX_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;      /* 定时器状态 */
    VOS_UINT8                           aucReserve[3];      /* 保留位 */
    VOS_UINT32                          ulLen;              /* 定时器时长 */
}TAF_MTA_TIMER_INFO_STRU;

/* Added by zwx247453 for Refclkfreq, 2015-6-17, begin */
/*****************************************************************************
 结构名    : TAF_MTA_TIMER_PRECISION_STRU
 结构说明  : 非32K精度定时器消息表
  1.日    期   : 2015年6月17日
    作    者   : zwx247453
    修改内容   : Refclkfreq项目新增
*****************************************************************************/
typedef struct
{
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;          /* TimerID */
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;        /* 定时器精度 */
}TAF_MTA_TIMER_PRECISION_STRU;
/* Added by zwx247453 for Refclkfreq, 2015-6-17, end */

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*lint -e958*/
VOS_VOID  TAF_MTA_SndOmTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus
);
/*lint +e958*/

VOS_VOID  TAF_MTA_InitAllTimers(
    TAF_MTA_TIMER_CTX_STRU              *pstMtaTimerCtx
);

TAF_MTA_TIMER_START_RESULT_ENUM_UINT8  TAF_MTA_StartTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID  TAF_MTA_StopTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
);

TAF_MTA_TIMER_STATUS_ENUM_UINT8  TAF_MTA_GetTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
);

/* Deleted by wx270776 for OM融合, 2015-7-16, begin */
/* Deleted by wx270776 for OM融合, 2015-7-16, end */

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

#endif


