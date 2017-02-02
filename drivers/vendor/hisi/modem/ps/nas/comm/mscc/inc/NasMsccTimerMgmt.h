

#ifndef __NAS_MSCC_TIMER_MGMT_H__
#define __NAS_MSCC_TIMER_MGMT_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define NAS_MSCC_THOUSAND_MILLISECOND_UNIT                   (1000)                         /* 1000MS */

#define TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_AVAIL_IND_LEN        (35*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_IMSA_START_CNF_LEN                  (3*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_START_CNF_LEN                   (70*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_START_CNF_LEN                   (30*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_START_CNF_LEN                   (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF_LEN              (3*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF_LEN               (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF_LEN               (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF_LEN               (60*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* Added by t00323010 for CDMA Iteration 10 2015-4-3 begin */
/*BSR Retry Timer length*/
#define TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)
/* Added by t00323010 for CDMA Iteration 10 2015-4-3 end */

/* Added by m00312079 for CDMA Iteration 10 2015-4-3 begin */
#define TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF_LEN                 (335*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* Modified by t00323010 for CDMA Iteration 12 2015-6-15 begin */
#define TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF_LEN              (22*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)
/* Modified by t00323010 for CDMA Iteration 12 2015-6-15 end */

#define TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF_LEN              (7*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF_LEN               (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF_LEN             (335*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF_LEN              (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND_LEN               (145*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)
/* Added by m00312079 for CDMA Iteration 10 2015-4-3 end */

#define TI_NAS_MSCC_AVAILABLE_TIMER_COUNT_FIRST_SEARCH       (10)

#define TI_NAS_MSCC_AVAILABLE_TIMER_FIRST_SEARCH_LEN         (300*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_AVAILABLE_TIMER_DEEP_SEARCH_LEN          (2400*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_BSR_TIMER_LEN                            (960*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_BSR_RETRY_TIMER_LEN                      (10*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_SCAN_TIMER_LEN                           (600*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_SLEEP_TIMER_LEN                          (180*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_CARD_READ_CNF_LEN                   (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
#define TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF_LEN               (101*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF_LEN       (6*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF_LEN          (11*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */

/* Added by x00314862 for CDMA Iteration 10 2015-4-7 begin */
#define TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF_LEN               (181*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF_LEN          (7*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF_LEN      (1*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)
/* Added by x00314862 for CDMA Iteration 10 2015-4-7 end */

#define TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF_LEN                 (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF_LEN                 (5*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

#define TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF_LEN                 (52*NAS_MSCC_THOUSAND_MILLISECOND_UNIT)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum NAS_MSCC_TIMER_ID_ENUM
{
    /* Timer for start confirmation from IMSA */
    TI_NAS_MSCC_WAIT_IMSA_START_CNF,
    /* Timer for power off confirmation from IMSA */
    TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF,
    /* Timer for start confirmation from XSD */
    TI_NAS_MSCC_WAIT_XSD_START_CNF,
    /* Timer for power off confirmation from XSD */
    TI_NAS_MSCC_WAIT_XSD_POWER_OFF_CNF,
    /* Timer for start confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_START_CNF,
    /* Timer for power off confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_POWER_OFF_CNF,
    /* Timer for start confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_START_CNF,
    /* Timer for power off confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_POWER_OFF_CNF,
    /* 等待IMSA的IMS VOICE CAP消息的保护定时器 */
    TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY,

    /* Added by x00314862 for CDMA Iteration 10 2015-4-3 begin */
    TI_NAS_MSCC_WAIT_HSD_BG_SEARCH_CNF,

    TI_NAS_MSCC_WAIT_HSD_STOP_BG_SEARCH_CNF,

    TI_NAS_MSCC_WAIT_MMC_QRY_PLMN_PRI_CLASS_CNF,
    /* Added by x00314862 for CDMA Iteration 10 2015-4-3 end */

    /* Added by t00323010 for CDMA Iteration 10 2015-4-3 begin */
    /* Timer for BSR timer */
    TI_NAS_MSCC_BSR_TIMER,
    /* Timer for BSR period trying high pri SYSTEM*/
    TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
    /* Added by t00323010 for CDMA Iteration 10 2015-4-3 end */
    /* Added by m00312079 for CDMA Iteration 10 2015-4-3 begin */
    TI_NAS_MSCC_WAIT_HSD_ACQUIRE_CNF,
    TI_NAS_MSCC_WAIT_HSD_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_XSD_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_MMC_PLMN_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_CL_POWER_SAVE_CNF,
    TI_NAS_MSCC_WAIT_INIT_LOC_INFO_IND,
    TI_NAS_MSCC_SCAN_TIMER,
    TI_NAS_MSCC_SLEEP_TIMER,
    TI_NAS_MSCC_AVAILABLE_TIMER,
    /* Added by m00312079 for CDMA Iteration 10 2015-4-3 end */

    TI_NAS_MSCC_WAIT_CARD_READ_CNF,

    /* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
    TI_NAS_MSCC_WAIT_MMC_BG_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_MMC_STOP_BG_SEARCH_CNF,
    TI_NAS_MSCC_WAIT_HSD_QRY_HRPD_SYS_INFO_CNF,
    /* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */

    TI_NAS_MSCC_WAIT_XSD_SYS_CFG_CNF,
    /* Timer for System config confirmation from HSD */
    TI_NAS_MSCC_WAIT_HSD_SYS_CFG_CNF,
    /* Timer for System config confirmation from MMC */
    TI_NAS_MSCC_WAIT_MMC_SYS_CFG_CNF,

    TI_NAS_MSCC_TIMER_BUTT
};
typedef VOS_UINT32  NAS_MSCC_TIMER_ID_ENUM_UINT32;
enum NAS_MSCC_TIMER_STATUS_ENUM
{
    NAS_MSCC_TIMER_STATUS_STOP,              /* 定时器停止状态 */
    NAS_MSCC_TIMER_STATUS_RUNING,            /* 定时器运行状态 */
    NAS_MSCC_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_TIMER_STATUS_ENUM_UINT8;

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
    HTIMER                              hTimer;                                 /* 定时器的运行指针 */
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId;                              /* 定时器的ID */
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus;                          /* 定时器的运行状态,启动或停止 */
    VOS_UINT8                           aucReserve[3];
}NAS_MSCC_TIMER_CTX_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头*/ /*_H2ASN_Skip*/
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulLen;                                  /* 定时器时长 */
}NAS_MSCC_TIMER_INFO_STRU;



/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID  NAS_MSCC_SndOmTimerStatus(
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus,
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);

VOS_UINT32  NAS_MSCC_StartTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
);


VOS_VOID  NAS_MSCC_StopTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
);

NAS_MSCC_TIMER_STATUS_ENUM_UINT8  NAS_MSCC_GetTimerStatus(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
);

/* Added by m00312079 for CDMA Iteration 10 2015-4-6 begin */
VOS_VOID NAS_MSCC_StopAllTimer(VOS_VOID);
/* Added by m00312079 for CDMA Iteration 10 2015-4-6 end */

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

#endif /* end of NasMsccTimerMgmt.h */
