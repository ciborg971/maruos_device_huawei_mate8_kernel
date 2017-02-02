

#ifndef __TAFXPDSCOMMFUNC_H__
#define __TAFXPDSCOMMFUNC_H__

/*****************************************************************************
  1 Header File Include
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "TafXpdsDecode.h"
#include "TafXpdsEncode.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXpdsCtx.h"


#pragma pack(4)


/*****************************************************************************
  2 The Macro Define
*****************************************************************************/


/*****************************************************************************
  3 The Enumeration Define
*****************************************************************************/

/*****************************************************************************
  4 The Declaration Of The Gloabal Variable
*****************************************************************************/

/*****************************************************************************
  5 The Define Of the Message Header
*****************************************************************************/


/*****************************************************************************
  6 The Define of the Message Name
*****************************************************************************/


/*****************************************************************************
  7 The Struct Define
*****************************************************************************/
typedef struct
{
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt;
    VOS_UINT32                          ulCancelReason;
}TAF_XPDS_RSLT_REASON_ITEM_STRU;

/*****************************************************************************
  8 The Union Define
*****************************************************************************/


/*****************************************************************************
  9 Other Defines
*****************************************************************************/


/*****************************************************************************
  10 The Declaration Of The Function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_ConvertPrefRespQualValueToTimerLimitLen(
    VOS_UINT8                           ucPrefRespQual
);

VOS_VOID TAF_XPDS_UpdatePpmInGlobal(VOS_VOID);

VOS_VOID TAF_XPDS_GetPnbyPhaseID(
    VOS_UINT16                          usPilotPN,
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU   *pstCasRptPilotBuff
);

VOS_FLOAT TAF_XPDS_CalcDataVar
(
    VOS_UINT32                          ulDataNum,
    VOS_UINT32                         *pulData
);

VOS_FLOAT TAF_XPDS_SquareRoot(VOS_FLOAT sfNumber);

VOS_UINT8 TAF_XPDS_CalcRmsErrPhase(
    VOS_FLOAT                           sfSqrt
);

VOS_UINT8 TAF_XPDS_CalcPnPhaseSqrt(
    VOS_UINT32                         *pulData,
    VOS_UINT32                          ulDataLen
);

VOS_UINT8 TAF_XPDS_FormatPnStrength(
    VOS_INT16                           sRefPnStrength
);

VOS_UINT8 TAF_XPDS_FormatServFreqRssi(
    VOS_INT16                           sServFreqRssi
);

TAF_XPDS_CANCEL_REASON_ENUM_UINT8 TAF_XPDS_FindCancelReasonByRslt(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
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

#endif







