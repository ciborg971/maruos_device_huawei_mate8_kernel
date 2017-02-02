
#ifndef _TAF_MMA_CTX_H_
#define _TAF_MMA_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "TafAppMma.h"
#include  "TafFsm.h"
#include  "TafMmaTimerMgmt.h"
#include  "TafSdcCtx.h"
#include  "MmaUphyInterface.h"

//#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TAF_MMA_MAX_MSG_BUFFER_LEN                      (500)                  /* 缓存的最大长度 */
#define TAF_MMA_MAX_MSG_QUEUE_NUM                       (4)                     /* 最大缓存的个数 */
#define TAF_MMA_MAX_STACK_DEPTH                         (4)                     /* 状态机栈的深度 */
#define TAF_MMA_ExtractMsgNameFromEvtType(ulEventType)     ((VOS_UINT16)((ulEventType) & 0x0000FFFF))          /* 从EventType中获取MsgName     */
#define TAF_MMA_MAX_MSG_QUEUE_SIZE                      (11)                    /* 内部消息队列最大的长度 */

#define TAF_MMA_MAX_OPER_NUM                            (5)

#define TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM           (4)                     /* 当前需要发送开关机命令模块的最大个数 */

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
#define TAF_MMA_WILDCARD_CDMAPN_VALUE                   (0xFFFF)
#define TAF_MMA_WILDCARD_EVDOPN_VALUE                   (0xFFFF)
/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, begin */

typedef VOS_UINT16   TAF_MMA_SYS_CFG_OPER_TYPE;
#define  TAF_MMA_SYS_CFG_NONE_SET                           (0x0000) /*设置为空*/
#define  TAF_MMA_SYS_CFG_ROAM_SET                           (0x0001) /*设置了漫游*/
#define  TAF_MMA_SYS_CFG_MODE_SET                           (0x0002) /*设置了接入模式或接入次序*/
#define  TAF_MMA_SYS_CFG_BAND_SET                           (0x0004) /*设置了频带*/
#define  TAF_MMA_SYS_CFG_CS_DETACH_SET                      (0x0010) /*由于设置了服务域需要进行CS Detach*/
#define  TAF_MMA_SYS_CFG_PS_DETACH_SET                      (0x0020) /*由于设置了服务域需要进行PS Detach*/
#define  TAF_MMA_SYS_CFG_CS_ATTACH_SET                      (0x0040) /*由于设置了服务域需要进行CS Attach*/
#define  TAF_MMA_SYS_CFG_PS_ATTACH_SET                      (0x0080) /*由于设置了服务域需要进行PS Attach*/


#define  TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_ATTACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_ATTACH_SET)

#define  TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED                (TAF_MMA_SYS_CFG_CS_DETACH_SET  \
                                                            |TAF_MMA_SYS_CFG_PS_DETACH_SET)

/* 需要发送syscfg请求 */
#define  TAF_MMA_SYS_CFG_SET_REQ_REQUIRED                   (TAF_MMA_SYS_CFG_ROAM_SET  \
                                                            |TAF_MMA_SYS_CFG_MODE_SET  \
                                                            |TAF_MMA_SYS_CFG_BAND_SET)

#define TAF_MMA_SYS_CFG_RAT_NONE_SET                        (0x00)
#define TAF_MMA_SYS_CFG_RAT_G_SET                           (0x01)
#define TAF_MMA_SYS_CFG_RAT_W_SET                           (0x02)
#define TAF_MMA_SYS_CFG_RAT_1X_SET                          (0x04)
#define TAF_MMA_SYS_CFG_RAT_DO_SET                          (0x08)

#define TAF_MMA_SYS_CFG_RAT_C_SET                           (TAF_MMA_SYS_CFG_RAT_1X_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_DO_SET)

#define TAF_MMA_SYS_CFG_RAT_GU_SET                          (TAF_MMA_SYS_CFG_RAT_G_SET  \
                                                            |TAF_MMA_SYS_CFG_RAT_W_SET)

/* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, end */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_MMA_MSG_CACHE_PRIO_ENUM
{
    TAF_MMA_MSG_CACHE_PRIO_HIGH              ,                           /* 高优先级缓存 */
    TAF_MMA_MSG_CACHE_PRIO_MIDDLE            ,                           /* 中优先级缓存 */
    TAF_MMA_MSG_CACHE_PRIO_LOW               ,                           /* 低优先级缓存 */

    TAF_MMA_MSG_CACHE_PRIO_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8;
enum TAF_MMA_FSM_ID_ENUM
{
    TAF_MMA_FSM_MAIN                                            = 0X00,

    TAF_MMA_FSM_PHONE_MODE                                      = 0X01,

    TAF_MMA_FSM_IMS_SWITCH                                      = 0X02,
    /* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
    TAF_MMA_FSM_SYS_CFG                                         =0x03,
    /* Modified by l00301449 for Iteration 13, 2015-04-09, end */

    TAF_MMA_FSM_BUTT

};
typedef VOS_UINT32 TAF_MMA_FSM_ID_ENUM_UINT32;


enum TAF_MMA_INIT_CTX_TYPE_ENUM
{
    TAF_MMA_INIT_CTX_STARTUP                    = 0,
    TAF_MMA_INIT_CTX_POWEROFF                   = 1,
    TAF_MMA_INIT_CTX_BUTT
};
typedef VOS_UINT32 TAF_MMA_INIT_CTX_TYPE_ENUM_UINT8;


enum TAF_MMA_OPER_TYPE_ENUM
{

    TAF_MMA_OPER_SYS_CFG_REQ                    = 0,
    TAF_MMA_OPER_ACQ_REQ                        = 1,
    TAF_MMA_OPER_REG_REQ                        = 2,
    TAF_MMA_OPER_POWER_SAVE_REQ                 = 3,
    TAF_MMA_OPER_DETACH_REQ                     = 4,
    TAF_MMA_OPER_CFPLMN_SET_REQ                 = 5,
    TAF_MMA_OPER_CFPLMN_QRY_REQ                 = 6,

    /* Added by y00307564 for CDMA Iteration 8 2015-2-13 begin */
    TAF_MMA_OPER_PREF_PLMN_SET_REQ              = 7,
    TAF_MMA_OPER_PREF_PLMN_QUERY_REQ            = 8,
    TAF_MMA_OPER_PREF_PLMN_TEST_REQ             = 9,
    TAF_MMA_OPER_CDMACSQ_SET_REQ                = 10,
    /* Added by y00307564 for CDMA Iteration 8 2015-2-13 end */
    /* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
    TAF_MMA_OPER_PLMN_LIST_REQ                  = 11,
    TAF_MMA_OPER_EONS_UCS2_REQ                  = 12,
    /* Added by c00318887 for AT&T phaseII, 2015-3-12, end */
    TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ            = 13,
    TAF_MMA_OPER_PLMN_SPEC_SEL_REQ              = 14,
    TAF_MMA_OPER_PLMN_LIST_ABORT_REQ            = 15,

	/* Added by z00316370 for UTS 2015-5-21 begin */
    TAF_MMA_OPER_GETSTA_QUERY_REQ               = 16,
    TAF_MMA_OPER_CHVER_QUERY_REQ                = 17,
    /* Added by z00316370 for UTS 2015-5-21 end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-10, begin */
    TAF_MMA_OPER_SET_CSIDLIST_REQ               = 18,
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-10, end */

    TAF_MMA_OPER_BUTT

};
typedef VOS_UINT32 TAF_MMA_OPER_TYPE_ENUM_UINT32;

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

/*****************************************************************************
 结构名    : TAF_MMA_ENTRY_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要保存的入口消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[TAF_MMA_MAX_MSG_BUFFER_LEN];
} TAF_MMA_ENTRY_MSG_STRU;

/*****************************************************************************
 结构名    : TAF_MMA_PHONE_MODE_SET_ORDER_STRU
 结构说明  : 记录给底层下发开机请求的先后顺序
              举例说明:
              若开机顺序为IMSA->CDMA->MSCC,那么aulSwitchOnModuleID中存放的
              先后顺序为IMSA->CDMA->MSCC,数组的总个数为3,在向IMSA模块发送开机请求的时候，
              usSwitchOnIndex存放的值为0；

              若开机顺序为IMSA->MSCC;那么aulSwitchOnModuleID中存放底层的
              先后顺序为IMSA->MSCC,数组的总个数为2,在向MSCC模发送开机请求的时候，
              usSwitchOnIndex存放的值为1;

              使用如下结构后，MMA能容易的满足底层可能要求的开机顺序变更。

*****************************************************************************/
typedef struct
{
    VOS_UINT16      usNum;                                                      /* 向下层发送开机请求的总个数 */
    VOS_UINT16      usIndex;                                                    /* 指向需要开机对应模块的接入技术的下标 */
    VOS_UINT32      aulModuleID[TAF_MMA_MAX_PHONE_MODE_SET_MODULE_NUM];         /* 存放设置开机需要发给底层模块的先后顺序 */
}TAF_MMA_PHONE_MODE_SET_ORDER_STRU;
typedef struct
{
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;       /* 开关机的错误原因值 */
    TAF_MMA_PHONE_MODE_SET_ORDER_STRU   stPhoneModeOrder;                    /* TAF MMA开机顺序队列 */
}TAF_MMA_FSM_PHONE_MODE_CTX_STRU;

/* Added by h00313353 for Iteration 13, 2015-4-9, begin */
/*****************************************************************************
 结构名    : TAF_MMA_FSM_SYSCFG_CTX_STRU
 结构说明  : 系统配置状态机上下文
 1.日    期   : 2015年4月9日
   作    者   : h00313353
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;                             /* 记录SYSCFG的操作类型 */
    VOS_UINT8                           ucAttachOpId;                           /* 记录attach发送时的OpId*/
    VOS_UINT8                           aucReserved[1];

    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
}TAF_MMA_FSM_SYS_CFG_CTX_STRU;
/* Added by h00313353 for Iteration 13, 2015-4-9, end */

typedef union
{
    TAF_MMA_FSM_PHONE_MODE_CTX_STRU                         stPhoneModeCtx;
    /* Added by h00313353 for Iteration 13, 2015-4-9, begin */
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                            stSysCfgCtx;
    /* Added by h00313353 for Iteration 13, 2015-4-9, end */

}TAF_MMA_FSM_EXTRA_CTX_UNION;


typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    TAF_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    /* 当前状态 */
    VOS_UINT32                          ulState;                                /* L1状态 */

    /* 入口消息MSGID和内容  */
    TAF_MMA_ENTRY_MSG_STRU              stEntryMsg;

    /* 状态机数据 */
    TAF_MMA_FSM_EXTRA_CTX_UNION         unFsmCtx;
}TAF_MMA_FSM_CTX_STRU;


typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    TAF_MMA_FSM_CTX_STRU                astFsmStack[TAF_MMA_MAX_STACK_DEPTH];   /* 状态机栈的深度 */
}TAF_MMA_FSM_STACK_STRU;
typedef struct
{
    TAF_MMA_ENTRY_MSG_STRU              stMsgEntry;     /* 缓存的具体内容   */
}TAF_MMA_CACH_MSG_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    TAF_MMA_CACH_MSG_INFO_STRU          astMsgQueue[TAF_MMA_MAX_MSG_QUEUE_NUM]; /* MMA的消息队列数组，存储的是带通用消息头的消息 */
}TAF_MMA_MSG_QUEUE_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgID;                                /* 消息ID */
    VOS_UINT8                           aucReserve[2];

    VOS_UINT8                           aucBuf[TAF_MMA_MAX_MSG_BUFFER_LEN];     /* 消息内容 */
}TAF_MMA_INTERNAL_MSG_BUF_STRU;



typedef struct
{
    /* TAF MMA内部消息队列 */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       astMmaMsgQueue[TAF_MMA_MAX_MSG_QUEUE_SIZE];

    /* 发送消息临时缓存buff,申请局部变量时直接使用该空间,为了避免发送内部消息时
    占用较大的栈空间 */
    TAF_MMA_INTERNAL_MSG_BUF_STRU       stSendMsgBuf;

    /* 内部消息缓冲队列的索引尾指针 */
    VOS_UINT8                           ucTail;

    /* 内部消息缓冲队列的索引头指针 */
    VOS_UINT8                           ucHeader;

    VOS_UINT16                          usReserved;
} TAF_MMA_INTERNAL_MSG_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           aucRsv[4];
    VOS_UINT32                          ulAutoInitPsFlg;                        /* 上电是否初始化协议栈 */
    VOS_UINT32                          ulAutoSwitchOnFlg;                      /* 上电是否自动开机(发送内部搜网请求给MSCC) */
}TAF_MMA_PHONE_MODE_CTRL_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucMmaLogInfoFlag;
    VOS_UINT8                           aucReserve[3];
}TAF_MMA_MAINTAIN_CTX_STRU;


typedef struct
{
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU;

typedef struct
{
    TAF_MMA_CTRL_STRU                   stCtrl;
    VOS_UINT8                           ucUsedFlag;
    VOS_UINT8                           aucReserved[3];
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType;
    VOS_VOID                           *pPara;
} TAF_MMA_OPER_CTX_STRU;

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
/*****************************************************************************
 结构名    : TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU
 结构说明  : en_NV_Item_DELAY_REPORT_SERVICE_STATUS_CFG NV项结构
 1. 日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnable;                               /* 0:NV 未激活; 1:NV 激活 */
    VOS_UINT8                           aucReserved[3];                               
    VOS_UINT32                          ulRptSrvStaDelayTimerValue;             /* 延时上报定时器时长,单位:秒 */               
}TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU;
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

typedef struct
{
    VOS_UINT8                           ucCfgGetGeoFlag;                        /* 获取国家码的开关 */
    VOS_UINT8                           ucCcpuResetFlag;                        /* 0:不是C核单独复位，而是上电 ;
                                                                                   1:是C核单独复位*/
    VOS_UINT8                           aucReserved[2];
    VOS_UINT32                          ulGetGeoTimerLen;                       /* 获取国家码定时器时长，单位为秒 */
    VOS_UINT32                          ulGeoEffectiveTimeLen;                  /* 国家码有效时长，单位为分钟 */
} TAF_MMA_GET_GEO_NV_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulGetGeoTickTime;                       /* 时间戳，单位为秒 */
    TAF_SDC_PLMN_ID_STRU                stGeoPlmnId;                            /* 地理位置信息的PLMN信息 */
    TAF_MMA_GET_GEO_NV_CFG_STRU         stGetGeoNvCfg;
} TAF_MMA_GET_GEO_CTX_STRU;


typedef struct
{
    VOS_UINT32  BandSpare7                   : 7;
    VOS_UINT32  BandGsmDcs1800               : 1;
    VOS_UINT32  BandGsmEgsm900               : 1;
    VOS_UINT32  BandGsmPgsm900               : 1;
    VOS_UINT32  Spare6                       : 6;
    VOS_UINT32  BandWcdma_VII_2600           : 1;
    VOS_UINT32  BandWcdma_VIII_900           : 1;
    VOS_UINT32  BandWcdma_IX_1700            : 1;
    VOS_UINT32  BandGsm850                   : 1;
    VOS_UINT32  BandGsmRgsm900               : 1;
    VOS_UINT32  BandGsmPcs1900               : 1;
    VOS_UINT32  BandWcdma_I_Imt2k1           : 1;
    VOS_UINT32  BandWcdma_II_PCS_1900        : 1;
    VOS_UINT32  BandWcdma_III_1800           : 1;
    VOS_UINT32  BandWcdma_IV_1700            : 1;
    VOS_UINT32  BandWcdma_V_850              : 1;
    VOS_UINT32  BandWcdma_VI_800             : 1;
    VOS_UINT32  BandWCDMA_XIX_850            : 1;
    VOS_UINT32  BandWcdma_XI_1500            : 1;
    VOS_UINT32  Spare2                       : 2;
}TAF_MMA_USER_PREF_BAND_STRU;


typedef struct
{
    VOS_UINT32                          BandGsm450      :1;
    VOS_UINT32                          BandGsm480      :1;
    VOS_UINT32                          BandGsm850      :1;
    VOS_UINT32                          BandGsmP900     :1;
    VOS_UINT32                          BandGsmR900     :1;
    VOS_UINT32                          BandGsmE900     :1;
    VOS_UINT32                          BandGsm1800     :1;
    VOS_UINT32                          BandGsm1900     :1;
    VOS_UINT32                          BandGsm700      :1;
    VOS_UINT32                          BandSpare7      :23;
}TAF_MMA_GSM_PREF_BAND_STRU;


typedef struct
{
    VOS_UINT32                          BandWCDMA_I_2100      :1;
    VOS_UINT32                          BandWCDMA_II_1900     :1;
    VOS_UINT32                          BandWCDMA_III_1800    :1;
    VOS_UINT32                          BandWCDMA_IV_1700     :1;
    VOS_UINT32                          BandWCDMA_V_850       :1;
    VOS_UINT32                          BandWCDMA_VI_800      :1;
    VOS_UINT32                          BandWCDMA_VII_2600    :1;
    VOS_UINT32                          BandWCDMA_VIII_900    :1;
    VOS_UINT32                          BandWCDMA_IX_J1700    :1;
    VOS_UINT32                          BandSpare10           :1;
    VOS_UINT32                          BandWCDMA_XI_1500     :1;
    VOS_UINT32                          BandSpare7            :7;
    VOS_UINT32                          BandWCDMA_XIX_850     :1;
    VOS_UINT32                          BandSpare13           :13;
}TAF_MMA_WCDMA_PREF_BAND_STRU;


typedef union
{
    VOS_UINT32                          ulPrefBand;
    TAF_MMA_USER_PREF_BAND_STRU         BitBand;
}TAF_MMA_USER_BAND_SET_UN;


typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_WCDMA_PREF_BAND_STRU        BitBand;
}TAF_MMA_WCDMA_BAND_SET_UN;


typedef union
{
    VOS_UINT32                          ulBand;
    TAF_MMA_GSM_PREF_BAND_STRU          BitBand;
}TAF_MMA_GSM_BAND_SET_UN;


typedef struct
{
    TAF_MMA_WCDMA_BAND_SET_UN               unWcdmaBand;
    TAF_MMA_GSM_BAND_SET_UN                 unGsmBand;
    VOS_UINT8                               aucReserved1[12];
    VOS_UINT8                               aucReserved2[12];
}TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU;


typedef struct
{
    TAF_MMA_USER_BAND_SET_UN            uUserSetGuBand;                         /* 上次用户设置成功当前生效的GU频段 */
    TAF_USER_SET_PREF_BAND64            stOrigUserSetGuBand;                    /* 上次用户设置成功的GU 64位原始频段,仅供查询使用 */
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   uUserSetUeFormatGuBand;                 /* 转换为UE支持格式的上次用户设置成功当前生效的GU频段 */
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUserSetLteBand;                       /* 上次用户设置成功当前生效的LTE频段 */
#endif
}TAF_MMA_SYSCFG_USER_SET_BAND_STRU;


typedef struct
{
    TAF_MMA_RAT_ORDER_STRU              stRatPrioList;                          /* 上次用户设置成功当前生效的接入模式优先级*/
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enRoam;                                 /* 上次用户设置成功当前生效的漫游能力 */
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8   enPrioRat;                              /* 上次用户设置成功当前生效的接入优先级 */
    VOS_UINT8                           ucReserve;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;                            /* 上次用户设置成功当前生效的服务域 */
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU   stUserSetBand;                          /* 上次用户设置成功当前生效的频段信息 */
}TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU;
typedef struct
{
    VOS_UINT32                          ulUeGSptBand;
    VOS_UINT32                          ulUeWSptBand;
    VOS_UINT32                          ulAllUeBand;
    TAF_MMA_WCDMA_BAND_SET_UN           unWRFSptBand;
    TAF_MMA_GSM_BAND_SET_UN             unGRFSptBand;

#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64            stUeSupportLteBand;
#endif
}TAF_MMA_UE_BAND_CAPA_ST;


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
/*****************************************************************************
 结构名    : TAF_MMA_DSDS_INFO_STRU
 结构说明  : DSDS相关的信息
 1.日    期   : 2015年5月15日
   作    者   : L00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU       stSrvAcqRatList;
}TAF_MMA_DSDS_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_MMA_ATTACH_INFO_STRU
 结构说明  : ATTACH相关的信息
 1.日    期   : 2015年5月15日
   作    者   : L00301449
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAttachOpId;
    VOS_UINT8                           aucRsved[3];
}TAF_MMA_ATTACH_INFO_STRU;

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

typedef struct
{
    /**************************************************************************
                        MMA状态机状态及其状态栈
    **************************************************************************/
    TAF_MMA_FSM_CTX_STRU                                    stCurFsm;                               /* 状态机当前的状态机数组 */
    TAF_MMA_FSM_STACK_STRU                                  stFsmStack;                             /* 状态机的状态机栈数组   */

    TAF_MMA_PHONE_MODE_CTRL_CTX_STRU                        stPhoneModeCtrl;                        /* 手机模式控制上下文 */

    TAF_MMA_TIMER_CTX_STRU                                  astMmaTimerCtx[TAF_MMA_MAX_TIMER_NUM];  /* MMA当前正在运行的定时器资源 */
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU                stMmaExternalModuleInitStatusCtx;       /* MMA初始化状态信息 */
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];  /* MMA L-C互操作上下文 */


    /**************************************************************************
                        TAF MMA缓存消息队列
    **************************************************************************/
    TAF_MMA_MSG_QUEUE_STRU                                  stBufferEntryMsgQueue;

    TAF_MMA_INTERNAL_MSG_QUEUE_STRU                         stInternalMsgQueue;                     /* MMA子层的内部消息队列 */

    TAF_MMA_MAINTAIN_CTX_STRU                               stMaintainInfo;

    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU                        stCFreqLockValue;                       /* 1x&evdo锁频信息 */
    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     stLastSyscfgSet;                        /* 上次用户设置成功的syscfg参数 */

    TAF_MMA_UE_BAND_CAPA_ST                                 stUeBandCap;                            /* UE支持的频段能力 */

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
    /* Modified by l00301449 for Iteration 13, 2015-04-13, begin */
    TAF_MMA_ATTACH_INFO_STRU                                stAttachInfo;
    /* Modified by l00301449 for Iteration 13, 2015-04-13, end */

    TAF_MMA_DSDS_INFO_STRU                                  stDsdsInfo;
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */

    TAF_MMA_GET_GEO_CTX_STRU                                stGetGeoInfo;
    
    TAF_MMA_DELAY_REPORT_SERVICE_STATUS_STRU stDelayReportServiceInfo;

    
}TAF_MMA_CONTEXT_STRU;

extern TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
);

VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID );

VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID );

VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID );

TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID);
TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID);

TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID);

VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
);


VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID);

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID);
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */


TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID);

TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID);

VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
);

VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID );

VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
);

VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
);


VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA的内部消息队列 */
);
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
);

VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
);

TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID);

VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID );

VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
);

VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID );

TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID);

TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
);

VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID);

VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
);

VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID);




TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID );

VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
);

TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID);
VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID );

VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
);

VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
);

MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus(VOS_VOID);

VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted(VOS_VOID);
TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID );
VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
);

VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
);

VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
);

VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
);

VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
);


/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(VOS_UINT8 ucDelayReportServiceStatusFlg);
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID);
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(VOS_UINT32 ulTimerLen);
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */



/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID);

VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID);

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID);
VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID);
VOS_VOID  TAF_MMA_SetGeoNoSimStartFlag(
    VOS_UINT8                           ucNoSimStartFlag
);
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID );
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID );
VOS_UINT8  TAF_MMA_GetGeoNoSimStartFlag(VOS_VOID);
VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID);
VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag);
VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID);
VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID);
VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID);
VOS_UINT8 TAF_MMA_GetGeoCmpFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetGeoCmpFlag(VOS_UINT8 ucGetGeoCmpFlag);
VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID);

/* Modified by l00301449 for Iteration 13, 2015-04-10, begin */
VOS_VOID  TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
);
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag);
VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID);
VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen);
VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID);

VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID);

VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
);

/* Modified by l00301449 for Iteration 13, 2015-04-10, end */

#if (FEATURE_ON == FEATURE_LTE)
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID);

TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID);

#endif

TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID);

TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID);

TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID);

TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID);

TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID);

VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID);


/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID);

VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
);

VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID);

/* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


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

#endif /* end of TafMmaCtx.h */

