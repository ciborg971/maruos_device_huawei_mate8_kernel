

#ifndef __TAFMTACTX_H__
#define __TAFMTACTX_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMtaTimerMgmt.h"
#include "AtMtaInterface.h"

#include "NasErrorLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* 等待消息结果的队列长度。由于起定时器时，会同时保存消息，故该值与TAF_MTA_CTX_MAX_TIMER_NUM一致 */
#define TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE                   (5)

#define TAF_MTA_REFCLOCK_DEFAULT_FREQ                       (49152000)
#define TAF_MTA_REFCLOCK_DEFAULT_PRECISION                  (100)

#define TAF_MTA_INVALID_MCC                                 (0x0FFF)

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#define TAF_MTA_ISMCOEX_BANDWIDTH_NUM                       (AT_MTA_ISMCOEX_BANDWIDTH_NUM)
/* Added by w00316404 for eMBMS project, 2015-5-22, end */



/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 频点收集回复标记枚举
*****************************************************************************/
enum TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM
{
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL          = 0x00,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS           = 0x01,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS           = 0x02,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC          = 0x04,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GUL           = 0x07,
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_BUTT
};
typedef VOS_UINT8 TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8;

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
    VOS_CHAR                           *pcBufHead;                              /* 存放XML码流内存的首地址 */
    VOS_CHAR                           *pcBufCur;                               /* 当前空闲内存的首地址 */
}TAF_MTA_XML_TEXT_STRU;


typedef struct
{
    AT_MTA_CMD_RPT_FLG_ENUM_UINT8       enRptFlg;                               /* 命令上报开关标志 */
    VOS_UINT8                           aucReserved1[3];                        /* 保留位 */
    VOS_UINT32                          ulFreq;                                 /* GPS参考时钟的频率值，单位Hz */
    VOS_UINT32                          ulPrecision;                            /* 当前GPS参考时钟的精度，单位ppb */
    PHY_MTA_REFCLOCK_STATUS_ENUM_UINT16 enStatus;                               /* 时钟频率锁定状态 */
    VOS_UINT8                           aucReserved2[2];                        /* 保留位 */
} TAF_MTA_REFCLOCK_INFO_STRU;


typedef struct
{
    TAF_MTA_XML_TEXT_STRU               stXmlText;                              /* 存放XML码流的内存 */
    TAF_MTA_REFCLOCK_INFO_STRU          stRefClockInfo;                         /* GPS参考时钟状态信息 */
    TAF_NVIM_ECID_TL2GSM_CFG_STRU       stEcidCfg;                              /* ECID命令配置 */
}TAF_MTA_AGPS_CTX_STRU;
typedef struct
{
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;
    VOS_UINT8                          *pucMsgInfo;
    VOS_UINT32                          ulMsgInfoLen;
}TAF_MTA_CMD_BUFFER_STRU;


typedef struct
{
    VOS_UINT16                          usNewMipiClk;                           /* 保存最新的MIPICLK值 */
    VOS_UINT16                          usReportMipiClk;                        /* 保存已经上报过的的MIPICLK值 */
    VOS_UINT32                          ulTimerInterVal;                        /* 保存MIPICLK上报的时间间隔 */
    VOS_UINT16                          usEnableBitMap;                         /* 使能开关，每个bit代表不同的算法，非0代表使能 */
    VOS_UINT8                           aucReserved2[2];                        /* 保留位 */
}TAF_MTA_RF_LCD_CTX_STRU;


/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
/*****************************************************************************
 结构名    : MTA_LRRC_COEX_PARA_STRU
 结构说明  : LTE&WIFI共存参数结构体

  1.日    期   : 2015年5月22日
    作    者   : w00316404
    修改内容   : 新增
*****************************************************************************/
typedef AT_MTA_COEX_PARA_STRU TAF_MTA_COEX_PARA_STRU;
/* Added by w00316404 for eMBMS project, 2015-5-22, end */

typedef struct
{
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU    *pstFreqInfoCltCtx;
    VOS_UINT8                                   ucWaitFreqCltCnfFlag;
    VOS_UINT8                                   aucRsv[3];
}TAF_MTA_INFO_CLT_CTX_STRU;


typedef struct
{
    /* 记录AGPS XML码流的上下文资源 */
    TAF_MTA_AGPS_CTX_STRU           stAgpsCtx;

    /* MTA当前正在运行的定时器资源 */
    TAF_MTA_TIMER_CTX_STRU          astTimerCtx[TAF_MTA_CTX_MAX_TIMER_NUM];

    /* MTA命令消息缓存 */
    TAF_MTA_CMD_BUFFER_STRU         astCmdBufferQueue[TAF_MTA_MAX_CMD_BUFFER_QUEUE_SIZE];

    TAF_MTA_RF_LCD_CTX_STRU         stMtaRfLcdCtx;

    /* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#if(FEATURE_ON == FEATURE_LTE)
    TAF_MTA_COEX_PARA_STRU           astIsmCoex[TAF_MTA_ISMCOEX_BANDWIDTH_NUM];
#endif
    /* Added by w00316404 for eMBMS project, 2015-5-22, end */

    TAF_MTA_INFO_CLT_CTX_STRU       stInfoCltCtx;

}TAF_MTA_CONTEXT_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/
/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern TAF_MTA_AGPS_CTX_STRU*  TAF_MTA_GetMtaAgpsCtxAddr( VOS_VOID );

extern TAF_MTA_CONTEXT_STRU*  TAF_MTA_GetMtaCtxAddr( VOS_VOID );

extern TAF_MTA_TIMER_CTX_STRU*  TAF_MTA_GetTimerCtxAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_InitCmdBufferQueue(
            TAF_MTA_CMD_BUFFER_STRU            *pstCmdBufferQueue);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetCmdBufferQueueAddr( VOS_VOID );

extern VOS_VOID  TAF_MTA_DelItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId);

extern VOS_VOID  TAF_MTA_SaveItemInCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
            VOS_UINT8                          *pucMsgInfo,
            VOS_UINT32                          ulMsgInfoLen);

extern TAF_MTA_CMD_BUFFER_STRU  *TAF_MTA_GetItemFromCmdBufferQueue(
            TAF_MTA_TIMER_ID_ENUM_UINT32                enTimerId);


extern VOS_VOID TAF_MTA_InitRefClockInfo(
    TAF_MTA_REFCLOCK_INFO_STRU         *pstRefClockInfo
);

extern TAF_MTA_REFCLOCK_INFO_STRU* TAF_MTA_GetRefClockInfo(VOS_VOID);

VOS_VOID  TAF_MTA_InitRfLcdIntrusionCtx(
    TAF_MTA_RF_LCD_CTX_STRU            *pstRfLcdCtx
);
TAF_MTA_RF_LCD_CTX_STRU* TAF_MTA_GetRfLcdCtxAddr( VOS_VOID );


VOS_VOID TAF_MTA_InitEcidCfg(
    TAF_NVIM_ECID_TL2GSM_CFG_STRU      *pstEcidCfg);

TAF_NVIM_ECID_TL2GSM_CFG_STRU* TAF_MTA_GetEcidCfg(VOS_VOID);

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#if(FEATURE_ON == FEATURE_LTE)
TAF_MTA_COEX_PARA_STRU*  TAF_MTA_GetIsmCoexAddr( VOS_VOID );
VOS_VOID  TAF_MTA_InitIsmCoex(
    TAF_MTA_COEX_PARA_STRU              *pstMtaCoexPara
);
#endif
/* Added by w00316404 for eMBMS project, 2015-5-22, end */

VOS_VOID  TAF_MMA_InitInfoCltCtx(
    TAF_MTA_INFO_CLT_CTX_STRU          *pstInfoCltCtx
);
VOS_VOID  TAF_MMA_AllocFreqInfoCltCtx(VOS_VOID);
VOS_VOID  TAF_MMA_FreeFreqInfoCltCtx(VOS_VOID);
TAF_MTA_INFO_CLT_CTX_STRU*  TAF_MTA_GetInfoCltAddr(VOS_VOID);
VOS_UINT8 TAF_MTA_GetWaitFreqCltCnfFlag(VOS_VOID);
VOS_VOID TAF_MTA_SetWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrWaitFreqCltCnfFlag(
    TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_ENUM_UINT8    enFreqCltCnf
);
VOS_VOID TAF_MTA_ClrAllWaitFreqCltCnfFlag(VOS_VOID);

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


