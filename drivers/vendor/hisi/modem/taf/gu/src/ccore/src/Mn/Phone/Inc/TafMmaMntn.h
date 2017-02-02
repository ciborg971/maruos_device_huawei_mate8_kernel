

#ifndef __TAF_MMA_MNTN_H__
#define __TAF_MMA_MNTN_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "TafMmaCtx.h"
#include "mdrv.h"
#include "msp_diag_comm.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum TAF_MMA_MNTN_MSG_ID_ENUM
{
    TAF_MMA_LOG_FSM_INFO_IND                                , /*_H2ASN_MsgChoice TAF_MMA_LOG_FSM_INFO_STRU */
    TAF_MMA_LOG_BUFFER_MSG_INFO_IND                         , /*_H2ASN_MsgChoice TAF_MMA_LOG_BUffER_MSG_INFO_STRU */
    TAF_MMA_LOG_INTER_MSG_INFO_IND                          , /*_H2ASN_MsgChoice TAF_MMA_LOG_INTER_MSG_INFO_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_UNLOCK            , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK              , /*_H2ASN_MsgChoice TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU */

    TAF_MMA_LOG_OPER_CTX_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_OPER_CTX_INFO_STRU */

    /* Added by c00318887 for AT&T phaseII, 2015-4-8, begin */
    TAF_MMA_LOG_COPS_RLT_INFO_IND                           , /*_H2ASN_MsgChoice TAF_MMA_LOG_COPS_RLT_INFO_STRU */
    /* Added by c00318887 for AT&T phaseII, 2015-4-8, end */

    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    TAF_MMA_LOG_NETWORK_APPNETWORK_CTX_INFO_IND             , /*_H2ASN_MsgChoice TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU */
    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
    TAF_MMA_LOG_READ_NV_INFO_IND                            , /*_H2ASN_MsgChoice TAF_MMA_LOG_READ_NV_INFO_IND_STRU */
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

    TAF_MMA_LOG_BUT
};
typedef VOS_UINT32 TAF_MMA_MNTN_MSG_ID_ENUM_UINT32;

/* Added by c00318887 for AT&T phaseII, 2015-4-9, begin */
/*****************************************************************************
 枚举名    : TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8
 结构说明  : 运营商名称类型
 1.日    期   : 2015年4月8日
   作    者   : c00318887
   修改内容   : 新增
*****************************************************************************/
enum TAF_SDC_LOG_OPER_NAME_TYPE_ENUM
{
    TAF_SDC_LOG_OPER_NAME_TYPE_PNN = 1,
    TAF_SDC_LOG_OPER_NAME_TYPE_CPHS,
    TAF_SDC_LOG_OPER_NAME_TYPE_SPN,
    TAF_SDC_LOG_OPER_NAME_TYPE_MMINFO,
    TAF_SDC_LOG_OPER_NAME_TYPE_NV,
    TAF_SDC_LOG_OPER_NAME_TYPE_TABLE,
    TAF_SDC_LOG_OPER_NAME_TYPE_BUTT
};
typedef VOS_UINT8  TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8;

/* Added by c00318887 for AT&T phaseII, 2015-4-9, end */

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
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;
    VOS_UINT32                          ulState;
}TAF_MMA_LOG_FSM_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulFullFlg;
    TAF_MMA_MSG_QUEUE_STRU              stMsgQueue;
}TAF_MMA_LOG_BUffER_MSG_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_MMA_OPER_CTX_STRU               astMmaOperCtx[TAF_MMA_MAX_OPER_NUM];
}TAF_MMA_LOG_OPER_CTX_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucFullFlg;
    VOS_UINT8                           ucMsgLenValidFlg;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_LOG_INTER_MSG_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* 消息头                                   */ /*_H2ASN_Skip*/
    PWC_CLIENT_ID_E                     enClientId;
    VOS_UINT32                          ulRslt;
}TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU;

/* Modified by c00318887 for AT&T phaseII, 2015-4-8, begin */

/*****************************************************************************
 结构名    : TAF_SDC_LOG_ENHANCED_OPERATOR_NAME_INFO
 结构说明  : 记录运营商名称相关信息
 1.日    期   : 2015年4月8日
   作    者   : c00318887
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    TAF_SDC_OPER_NAME_TYPE_PRIO_STRU         stOperNameTypePrio;   /* cops或^eonsucs2查询从PNN或SPN或CPHS或NITZ获取先后顺序优先级*/
    TAF_SDC_SPN_FILE_INFO_STRU               stUsimSpnFileInfo;    /* Usim中的SPN文件0x6f46信息 */
    TAF_SDC_SPN_FILE_INFO_STRU               stSimSpnFileInfo;     /* Sim中的SPN文件0x6f46信息 */
    TAF_SDC_MM_INFO_STRU                     stMmInfo;             /* 记录MM/GMM/EMM info消息中的信息*/
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8      enCopsFormatType;
    VOS_CHAR                                 cWildCard;             /* 通配符,取值a-f,可代表0-9任意数字 */
    VOS_UINT8                                aucReserved[2];
}TAF_SDC_LOG_EONS_INFO_STRU;


/*****************************************************************************
 结构名    : TAF_MMA_LOG_COPS_RLT_INFO_STRU
 结构说明  : MMA的COPS结果信息可维可测

 修改记录  :
  1.日    期   : 2015年4月8日
    作    者   : c00318887
    修改内容   : 新增
*****************************************************************************/

typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;          /* 消息头                 */ /*_H2ASN_Skip*/
    TAF_PH_OPERATOR_NAME_STRU               stName;
    TAF_PH_NETWORKNAME_FORMAT               stNameFormat;         /*网络运营商名字格式*/
    TAF_PH_RA_MODE                          ucRaMode;            /*无线接入模式,3G/2G*/
    TAF_PH_PLMN_SEL_MODE                    ucPlmnSelMode;       /*PLMN selection mode*/
    TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8   enType;
    TAF_SDC_LOG_EONS_INFO_STRU              stEonsInfo;
}TAF_MMA_LOG_COPS_RLT_INFO_STRU;

/* Modified by c00318887 for AT&T phaseII, 2015-4-8, end */

/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32         enMsgId;                            /* 消息ID */    /* _H2ASN_Skip */
    VOS_UINT16                              enNvItem;
    VOS_UINT16                              usNvDataLength;
    VOS_UINT32                              ulPid;
    VOS_UINT8                               aucNvInfo[4];                       /* NV内容 */

}TAF_MMA_LOG_READ_NV_INFO_IND_STRU;
/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

/*****************************************************************************
 结构名    : TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU
 结构说明  :TAF的g_stTafSdcCtx中的NETWORK/APPNETWORK信息可维可测

 修改记录  :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* 消息头                                   */ /*_H2ASN_Skip*/
    TAF_SDC_NETWORK_INFO_STRU           stNetworkInfo;
    TAF_SDC_APPNETWORK_INFO             stAppNetworkInfo;
}TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_MMA_MNTN_MSG_ID_ENUM_UINT32     enMsgId;

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MMA_MNTN_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MMA_MNTN_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MNTN_MSG_DATA                 stMsgData;
}TafMmaMntn_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/* Deleted by wx270776 for OM融合, 2015-7-24, begin */
/* Deleted by wx270776 for OM融合, 2015-7-24, end */

VOS_VOID  TAF_MMA_LogFsmInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
);

VOS_VOID TAF_MMA_LogOperCtxInfo(VOS_VOID);

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_VOID  TAF_MMA_LogNetworkInfoAndAppNetworkInfo(VOS_VOID);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

VOS_VOID  TAF_MMA_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
);

VOS_VOID TAF_MMA_ShowPhoneModeCtrlInfo(VOS_VOID);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
);

VOS_VOID TAF_MMA_ShowCLConfigInfo(VOS_VOID);

/* Added by c00318887 for AT&T phaseII, 2015-4-8, begin */
VOS_VOID TAF_MMA_LogCopsRltInfo(
        TAF_PH_NETWORKNAME_STRU                   *pstOperatorName,
        TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8      enType
);
/* Added by c00318887 for AT&T phaseII, 2015-4-8, end */

VOS_VOID TAF_MMA_ModelPihSndUsimStatusInd(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardService
);
VOS_VOID TAF_MMA_ModelUphySndInitStatusInd(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16               enInitStatus
);
VOS_VOID TAF_MMA_ModelUsimStatusIndTimeOut(VOS_VOID);
VOS_VOID TAF_MMA_SndTestInterPowerInitReq(VOS_VOID);
VOS_VOID TAF_MMA_TestSetGeoIno(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, begin */
VOS_VOID TAF_MMA_LogReadNVInfo(
    VOS_UINT16                              enNvItem,
    VOS_UINT16                              usNvDataLength,
    VOS_UINT32                              ulPid,
    VOS_UINT8                              *pucData
);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-8, end */

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

#endif /* end of TafMmaMntn.h */


