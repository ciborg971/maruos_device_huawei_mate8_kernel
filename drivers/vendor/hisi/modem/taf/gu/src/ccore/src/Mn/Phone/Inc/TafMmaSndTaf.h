
#ifndef _TAF_MMA_SND_TAF_H_
#define _TAF_MMA_SND_TAF_H_
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "NasStkInterface.h"
#include "MmaMsccInterface.h"

#include "TafMmaInterface.h"

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
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID TAF_MMA_SndPowerIndMsg(VOS_VOID);

VOS_VOID TAF_MMA_SndSpmServiceStatusChangeNotify(VOS_VOID);
VOS_VOID TAF_MMA_SndSpmNetworkCapabilityChangeNotify(VOS_VOID);
VOS_VOID TAF_MMA_SndSpmRatChangeNotify(VOS_VOID);

VOS_VOID TAF_MMA_SndMsgCsServiceChangeNotify(
    TAF_CS_SERVICE_ENUM_UINT32          enCsState
);

VOS_VOID MN_PH_SndMsgUsimStatus(VOS_UINT32  ulUsimSta);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID TAF_MMA_SndSpmImsVoiceCapInd(
    VOS_UINT8                           ucAvail
);

#endif

VOS_VOID TAF_MMA_SndPowerOnIndMsg(VOS_VOID);


VOS_VOID TAF_MMA_SndTaf1XServiceStatusInd(
    VOS_UINT32                          ulExist1XService
);




VOS_VOID TAF_MMA_SndApsEpdszidInfoInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
);

/* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
VOS_VOID TAF_MMA_SndPrefPlmnSetCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt
);

VOS_VOID TAF_MMA_SndPrefPlmnQueryCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
);

VOS_VOID TAF_MMA_SndPrefPlmnTestCnf(
    TAF_MMA_CTRL_STRU                                      *pstCtrl,
    TAF_MMA_APP_PREF_PLMN_OPER_RESULT_ENUM_UINT32           enRslt,
    MSCC_MMA_PREF_PLMN_QUERY_CNF_STRU                      *pstRcvMsg
);
/* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */

VOS_VOID TAF_MMA_SndTafCLServiceStatusInd(
    MMA_TAF_CL_STATUS_ENUM_UINT32       enClStatus,
    VOS_UINT8                           ucIsNewSession
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

#endif /* end of TafMmaSndTaf.h */

