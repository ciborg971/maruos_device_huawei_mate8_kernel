

#ifndef __NAS_MSCC_SND_INTERNAL_MSG_H__
#define __NAS_MSCC_SND_INTERNAL_MSG_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasMsccCtx.h"
#include "NasMsccMntn.h"



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

enum NAS_MSCC_INTERNAL_MSG_TYPE_ENUM
{
    ID_NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF = ID_NAS_MSCC_MNTN_INTERNAL_MSG_BASE,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU*/
    ID_NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF                                     ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_SYS_ACQ_REQ                                            ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_ACQ_STRU*/
    ID_NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF                                       ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU */
    ID_NAS_MSCC_MSCC_ABORT_FSM_REQ                                          ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_ABORT_REQ_STRU*/

    /* Added by x00314862 for CDMA Iteration 6 2015-4-3 begin */
    ID_NAS_MSCC_MSCC_BSR_RSLT_CNF                                           ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU*/
    /* Added by x00314862 for CDMA Iteration 6 2015-4-3 end */

    ID_NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF                                       ,/* _H2ASN_MsgChoice NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU*/

    ID_NAS_MSCC_MSCC_PIF_MSG_TYPE_ENUM_BUTT
};
typedef VOS_UINT16 NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16;

enum NAS_MSCC_SWITCH_ON_RESULT_ENUM
{
    NAS_MSCC_SWITCH_ON_RESULT_FAILURE   = 0x00000000,
    NAS_MSCC_SWITCH_ON_RESULT_SUCCESS   = 0x00000001,
    NAS_MSCC_SWITCH_ON_RESULT_BUTT      = 0x00000003
};
typedef VOS_UINT32 NAS_MSCC_SWITCH_ON_RESULT_ENUM_UINT32;


/* Added by m00312079 for CDMA Iteration 10 2015-4-3 begin */

enum NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM
{
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_SUCCESS                 = 0x00000000,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_FAILURE                 = 0x00000001,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ABORTED                 = 0x00000002,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_L2C                     = 0x00000003,
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_BUTT                    = 0x00000004
};
typedef VOS_UINT32 NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32;
/* Added by m00312079 for CDMA Iteration 10 2015-4-3 end */

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
/****************************************************************************
Enum name       :   NAS_MSCC_BSR_RESULT_ENUM_UINT16
Description     :   Contains the better system reselection(BSR) result types
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

enum NAS_MSCC_BSR_RESULT_ENUM
{
    NAS_MSCC_BSR_RESULT_SUCCESS,
    NAS_MSCC_BSR_RESULT_FAILURE,
    NAS_MSCC_BSR_RESULT_ABORT,
    NAS_MSCC_BSR_RESULT_BUTT
};
typedef VOS_UINT16 NAS_MSCC_BSR_RESULT_ENUM_UINT16;

/****************************************************************************
Enum name       :   NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8
Description     :   是否需要重新搜网
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

enum NAS_MSCC_BSR_ACQ_SYS_ENUM
{
    NAS_MSCC_BSR_NEED_ACQ_SYS,           /* 需要搜网 */
    NAS_MSCC_BSR_NOT_NEED_ACQ_SYS,       /* 不需要搜网 */
    NAS_MSCC_BSR_ACQ_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8;

/****************************************************************************
Enum name       :   NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8
Description     :   是否需要重启retry定时器
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

enum NAS_MSCC_BSR_RETRY_TIMER_ENUM
{
    NAS_MSCC_BSR_NEED_START_RETRY_TIMER,          /* 需重启retry定时器 */
    NAS_MSCC_BSR_NOT_NEED_START_RETRY_TIMER,      /* 不需重启retry定时器 */
    NAS_MSCC_BSR_RETRY_TIMER_BUTT
};
typedef VOS_UINT8 NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8;


enum NAS_MSCC_POWEROFF_RSLT_ENUM
{
    NAS_MSCC_POWEROFF_RSLT_POWER_OFF,
    NAS_MSCC_POWEROFF_RSLT_POWER_SAVE,

    NAS_MSCC_POWEROFF_RSLT_BUTT
};
typedef VOS_UINT32 NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32;



enum NAS_MSCC_SYS_CFG_RESULT_ENUM
{
    NAS_MSCC_SYS_CFG_RESULT_SUCCESS   = 0x00000000,
    NAS_MSCC_SYS_CFG_RESULT_FAILURE   = 0x00000001,
    NAS_MSCC_SYS_CFG_RESULT_BUTT      = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32;

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */


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
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SWITCH_ON_RESULT_ENUM_UINT32                   enRslt;
}NAS_MSCC_MSCC_SWITCH_ON_RSLT_CNF_STRU;




typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32                      enRslt;
}NAS_MSCC_MSCC_POWER_OFF_RSLT_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                               aucRsv[2];
}NAS_MSCC_MSCC_ABORT_FSM_REQ_STRU;


/* Added by m00312079 for CDMA Iteration 10 2015-4-3 begin */
/****************************************************************************
Structure name  :   NAS_MSCC_MSCC_SYS_ACQ_STRU
Description     :   Contains the system acquire reqeust message structure.
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene;
}NAS_MSCC_MSCC_SYS_ACQ_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU
Description     :   Contains the system acquire result message structure.
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt;
}NAS_MSCC_MSCC_SYS_ACQ_RSLT_CNF_STRU;

/* Added by m00312079 for CDMA Iteration 10 2015-4-3 end */

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
/****************************************************************************
Structure name  :   NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU
Description     :   Contains the BSR inter message structure.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;                 /* _H2ASN_Skip */
    NAS_MSCC_BSR_RESULT_ENUM_UINT16                         enRslt;                  /* BSR 结果 */
    NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8                         enIsNeedAcqSys;          /* 是否需要搜网 */
    NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8                     enIsNeedStartRetryTimer; /* 是否要启动retry定时器 */
    VOS_UINT8                                               ucReserved[2];
}NAS_MSCC_MSCC_BSR_RSLT_CNF_STRU;
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */



typedef struct
{
    VOS_MSG_HEADER                                                   /* _H2ASN_Skip */
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId; /* _H2ASN_Skip */
    VOS_UINT8                                               aucReserved[2];
    NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32                     enRslt;
}NAS_MSCC_MSCC_SYS_CFG_RSLT_CNF_STRU;



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
    NAS_MSCC_INTERNAL_MSG_TYPE_ENUM_UINT16                  enMsgId;            /* _H2ASN_MsgChoice_Export CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                                               aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          CNAS_XSD_INTERNAL_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}NAS_MSCC_INTERNAL_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    NAS_MSCC_INTERNAL_MSG_DATA          stMsgData;
}NAS_MSCC_INTERNAL_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MSCC_SndPowerOffRslt(
    NAS_MSCC_POWEROFF_RSLT_ENUM_UINT32  enRslt
);

VOS_VOID NAS_MSCC_SndSwitchOnRslt(
    VOS_UINT32                          ulResult
);

VOS_VOID NAS_MSCC_SndAbortFsmReq(VOS_VOID);

/* Added by m00312079 for CDMA Iteration 10 2015-4-3 begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MSCC_SndInternalSysAcqReq(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene
);

VOS_VOID NAS_MSCC_SndInternalSysAcqRsltCnf(
    NAS_MSCC_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enRslt
);
/* Added by m00312079 for CDMA Iteration 10 2015-4-3 end */

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
VOS_VOID NAS_MSCC_SndBsrResult(
    NAS_MSCC_BSR_RESULT_ENUM_UINT16     enBsrRslt,
    NAS_MSCC_BSR_ACQ_SYS_ENUM_UINT8     enIsNeedAcqSys,
    NAS_MSCC_BSR_RETRY_TIMER_ENUM_UINT8 enIsNeedStartRetryTimer
);
#endif
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */

VOS_VOID NAS_MSCC_SndSysCfgRslt(
    NAS_MSCC_SYS_CFG_RESULT_ENUM_UINT32      ulResult
);

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

#endif /* end of CnasXsdSndInternalMsg.h */

