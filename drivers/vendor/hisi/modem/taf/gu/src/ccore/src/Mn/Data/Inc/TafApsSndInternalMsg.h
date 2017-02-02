
#ifndef _TAF_APS_SND_INTERNAL_MSG_H_
#define _TAF_APS_SND_INTERNAL_MSG_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "Taf_Aps.h"
#include "TafSmInterface.h"
#include "TafApsCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* 封装内部消息OSA消息头 */
#define TAF_APS_CFG_INTER_MSG_HDR(pstMsg, ulLen)\
            (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pstMsg)->ulSenderPid     = WUEPS_PID_TAF;\
            (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pstMsg)->ulReceiverPid   = WUEPS_PID_TAF;\
            (pstMsg)->ulLength        = (ulLen)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 以下是APS内部消息[0x0700, 0x0799] */
enum TAF_PS_INTER_MSG_ID_ENUM
{
    /* APS内部去激活请求 */
    ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ           = TAF_PS_MSG_ID_BASE + 0x0700,  /* _H2ASN_MsgChoice TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU */

    /* APS内部去激活指示 */
    ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND              = TAF_PS_MSG_ID_BASE + 0x0701,  /* _H2ASN_MsgChoice TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU */

    /* 注册承载激活指示 */
    ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND                = TAF_PS_MSG_ID_BASE + 0x0702,  /* _H2ASN_MsgChoice TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU */

    /* CDMA下，内部完成挂断电话流程 */
    ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ                   = TAF_PS_MSG_ID_BASE + 0x0703,  /* _H2ASN_MsgChoice TAF_APS_INTER_END_CDMA_CALL_REQ_STRU */

    /* EPDSZID change, Start reorig req */
    ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ                  = TAF_PS_MSG_ID_BASE + 0x0704,  /* _H2ASN_MsgChoice TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU */

    ID_MSG_TAF_PS_INTER_HT_EXPIRED_REQ                      = TAF_PS_MSG_ID_BASE + 0x0705,  /* _H2ASN_MsgChoice TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU */

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-31, begin */
    ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ              = TAF_PS_MSG_ID_BASE + 0x0706,  /* _H2ASN_MsgChoice TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU */

    ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ              = TAF_PS_MSG_ID_BASE + 0x0707,  /* _H2ASN_MsgChoice TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU */

    ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND           = TAF_PS_MSG_ID_BASE + 0x0708,  /* _H2ASN_MsgChoice TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU */

    ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND          = TAF_PS_MSG_ID_BASE + 0x0709,  /* _H2ASN_MsgChoice TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU */

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-31, end */

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND          = TAF_PS_MSG_ID_BASE + 0x070A,  /* _H2ASN_MsgChoice TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

    ID_MSG_TAF_PS_INTER_BUTT

};
typedef VOS_UINT32 TAF_PS_INTER_MSG_ID_ENUM_UINT32;
enum TAF_APS_INTER_END_CALL_REASON_ENUM
{
    TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL           = 0x00000000,           /* PPP激活协商失败 */
    TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT       = 0x00000001,           /* PPP激活协商超时 */
    TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT  = 0x00000002,           /* SO协商超时 */
    TAF_APS_INTER_END_CALL_REASON_USER_END               = 0x00000003,           /* 用户去激活 */
    TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED        = 0x00000004,           /* PPP的IP地址改变了 */
    TAF_APS_INTER_EDN_CALL_REASON_HANDOFF                = 0x00000005,           /* 发生HandOff */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-29, begin */
    TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_FAIL     = 0X00000006,           /* DHCP Ipv4激活协商失败  */
    TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_FAIL     = 0X00000007,           /* DHCP Ipv6激活协商失败  */
    TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_TIEM_OUT = 0X00000008,           /* DHCP Ipv4激活协商超时  */
    TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_TIEM_OUT = 0X00000009,           /* DHCP Ipv6激活协商超时  */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-29, end */


    TAF_APS_INTER_END_CALL_REASON_BUTT

};
typedef VOS_UINT8 TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8;



enum TAF_APS_INTER_END_CALL_SCENE_ENUM
{
    TAF_APS_INTER_END_CALL_SCENE_USER_END               = 0x00000000,
    TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL              = 0x00000001,
    TAF_APS_INTER_END_CALL_SCENE_REEST_FAIL             = 0x00000002,

    /* Added by y00314741 for CDMA Iteration 11, 2015-4-11, begin */
    TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY             = 0x00000003,
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-11, end */

    TAF_APS_INTER_END_CALL_SCENE_HANDOFF                = 0x00000004,

    TAF_APS_INTER_END_CALL_SCENE_BUTT
};
typedef VOS_UINT8 TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8;



enum TAF_APS_INTER_PS_OPTION_TYPE_ENUM
{
    TAF_APS_INTER_PS_OPTION_DISCONNECTED                   = 0x00000000,
    TAF_APS_INTER_PS_OPTION_CONNECTED                      = 0x00000001,
    TAF_APS_INTER_PS_OPTION_SWITCH                         = 0x00000002,

    TAF_APS_INTER_PS_OPTION_TYPE_BUTT                      = 0xFFFFFFFF
};
typedef VOS_UINT8 TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8;

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
    MSG_HEADER_STRU                     stMsgHeader;                    /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[1];
    SM_TAF_CAUSE_ENUM_UINT16            enCause;

} TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                    /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
    APS_PDP_ACT_REQ_ST                  stApsPdpActReq;

} TAF_APS_INTER_PDP_ACTIVATE_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;            /* _H2ASN_Skip */
    VOS_UINT8                                       ucPdpId;
    TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8         enEndScene;
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8        enEndReason;            /* 仅在scene场景为state abnormal时使用 */
    VOS_UINT8                                       aucReserved[1];
    VOS_UINT32                                      ulRemainTmrLen;
}TAF_APS_INTER_END_CDMA_CALL_REQ_STRU;


/* Added by y00314741 for CDMA Iteration 11, 2015-3-31, begin */
/*****************************************************************************
 结构名    : TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU
 结构说明  : 数据模式从1x切换到HRPD
 1.日    期   : 2015年03月31日
   作    者   : y00314741
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU;

/*****************************************************************************
 结构名    : TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU
 结构说明  : 数据模式从HRPD切换到1X
 1.日    期   : 2015年03月31日
   作    者   : y00314741
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU;

/*****************************************************************************
 结构名    : TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU
 结构说明  : 收到MMA或MMC的SERVICE_STATUS_IND消息，转发内部消息
 1.日    期   : 2015年04月08日
   作    者   : y00314741
   修改内容   : 新建结构
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucIsNewSession;
    VOS_UINT8                           aucReserved[2];
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType;
    VOS_UINT32                          ulPsSimRegStatus;
}TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU;
/* Added by y00314741 for CDMA Iteration 11, 2015-3-31, end */



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */
} TAF_APS_ATTACH_BEARER_ACTIVATE_IND_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          enMsgId;            /* 消息类型     */  /* _H2ASN_Skip */
} TAF_APS_PDP_ENTITY_TRACE_MAG_STRU;

/** ****************************************************************************
 * Name        : TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           aucReserved[4];
}TAF_PS_CALL_INTER_EPDSZID_REORIG_REQ_STRU;


/** ****************************************************************************
 * Name        : TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           aucReserved[4];
}TAF_PS_CALL_INTER_HT_EXPIRED_IND_STRU;

/** ****************************************************************************
 * Name        : TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                         stMsgHeader;                        /* _H2ASN_Skip */
    TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8 enPsOptionType;
    VOS_UINT8                               aucReserved[3];
}TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU;

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/** ****************************************************************************
 * Name        : TAF_PS_CALL_INTER_END_1X_CALL_IN_DORMANT_IND_STRU
 *
 * Description :
 *******************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* _H2ASN_Skip */
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           aucReserved[3];
}TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU;
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    TAF_PS_INTER_MSG_ID_ENUM_UINT32     ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_PS_INTER_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_PS_INTER_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_APS_INTER_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_APS_INTER_REQ                   stMsgReq;
}TafApsSndInternalMsg_MSG;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/

/*****************************************************************************
 函 数 名  : TAF_APS_SndInterPdpDeactivateReq
 功能描述  : 发送内部去激活PDP请求消息
 输入参数  : enCause                    - 去激活原因
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TAF_APS_SndInterPdpDeactivateReq(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

/*****************************************************************************
 函 数 名  : TAF_APS_SndLocalPdpDeactivateInd
 功能描述  : 发送本地去激活PDP请求消息
 输入参数  : enCause                  - 去激活原因
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TAF_APS_SndLocalPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

/*****************************************************************************
 函 数 名  : TAF_APS_SndLocalAllSecPdpDeactivateInd
 功能描述  : 发送本地所有从PDP去激活指示
 输入参数  : VOS_UINT8 ucPdpId
             VOS_UINT8 ucSmCause
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
VOS_VOID TAF_APS_SndLocalAllSecPdpDeactivateInd(
    VOS_UINT8                           ucPdpId,
    SM_TAF_CAUSE_ENUM_UINT16            enCause
);

/*****************************************************************************
 函 数 名  : TAF_APS_SndInterPdpActivateReq
 功能描述  : 发送内部激活PDP请求消息
 输入参数  : ucPdpId
             stApsPdpActReq
 输出参数  : 无
 返 回 值  : VOS_OK                     - 发送内部消息成功
             VOS_OERR                   - 发送内部消息失败
*****************************************************************************/
VOS_UINT32 TAF_APS_SndInterPdpActivateReq(
    VOS_UINT8                           ucPdpId,
    APS_PDP_ACT_REQ_ST                  stApsPdpActReq
);


/*****************************************************************************
 函 数 名  : TAF_APS_SndInterAttachBearerActivateInd
 功能描述  : 发送注册承载激活指示消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_SndInterAttachBearerActivateInd(VOS_VOID);

/*****************************************************************************
 函 数 名  : TAF_APS_SndInterFsmEntryMsg
 功能描述  : 发送状态机入口消息至内部消息队列
 输入参数  : pstEntryMsg --- 状态机入口消息
 输出参数  : 无
 返 回 值  : VOS_VOID
*****************************************************************************/
VOS_VOID TAF_APS_SndInterFsmEntryMsg(TAF_APS_ENTRY_MSG_STRU *pstEntryMsg);


VOS_UINT32 TAF_APS_SndEnterDormantInd(
    VOS_UINT8                                       ucPdpId
);

VOS_UINT32 TAF_APS_SndInterEndCdmaCallReq(
    TAF_APS_INTER_END_CALL_SCENE_ENUM_UINT8     enEndScene,
    TAF_APS_INTER_END_CALL_REASON_ENUM_UINT8    enEndReason,
    VOS_UINT8                                   ucPdpId,
    VOS_UINT32                                  ulRemainTmrLen
);

VOS_UINT32 TAF_APS_SndInterEpdszidReOrigReq(VOS_VOID);

VOS_UINT32 TAF_APS_SndInterHtExpiredInd(VOS_VOID);

/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, begin */
VOS_UINT32 TAF_APS_SndHaiChangeInd(
    VOS_UINT8                           ucPdpId
);
/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, end */
/* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
VOS_UINT32 TAF_APS_SndInterHrpdTo1XHandOffReq(
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_SndInter1XToHrpdHandOffReq(
    VOS_UINT8                           ucPdpId
);

VOS_UINT32 TAF_APS_SndInterServiceStatusChangeInd(
    VOS_UINT8                           ucPdpId,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType,
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType,
    VOS_UINT32                          ulPsSimRegStatus,
    VOS_UINT8                           ucIsNewSession
);
/* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

VOS_UINT32 TAF_APS_SndInterPsServiceModeModifyInd(
    TAF_APS_INTER_PS_OPTION_TYPE_ENUM_UINT8 enPsOptionType
);


/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
VOS_UINT32 TAF_APS_SndInterEnd1xServiceInDormantInd(
    VOS_UINT8                           ucPdpId
);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
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

#endif

