

#ifndef __CSSPROCSRCHRSLT_H__
#define __CSSPROCSRCHRSLT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include    "CssInterface.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/




/*****************************************************************************
  5 STRUCT
*****************************************************************************/



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  CSS_ProcBandScanReqest(VOS_VOID);
extern VOS_UINT32  CSS_ProcLphyBandScanRslt(const CSS_LPHY_BAND_SCAN_RESULT_LIST_STRU *pstLphyBandScanRslt);
extern VOS_UINT32 CSS_IsNeedSndLphyNextBandScanReq(VOS_VOID);

extern VOS_VOID CSS_SortRsltByRatSupport
(
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo,
    VOS_UINT8                          *pcRatSupportFlag
);
extern VOS_VOID CSS_AddBandToRslt
(
    CSS_RAT_COVERAGE_STRU                        *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU                 *pstDest,
    CSS_BAND_SCAN_INFO_STRU                      *pstSour,
    VOS_UINT16                                    usBand,
    VOS_UINT32                                    ulBandIndex
);
extern VOS_VOID CSS_AddOverlapBandToRslt
(
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo
);
extern VOS_UINT32 CSS_IsUeSupportBandByReq
(
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    VOS_UINT16                          ucBand
);
extern VOS_UINT32 CSS_IsNeedAddToRslt
(
    CSS_BAND_SCAN_LIST_INFO_STRU       *pstCssBandInfo,
    CSS_RAT_COVERAGE_STRU              *pstRatCoverage,
    VOS_UINT16                          ucBand
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

#endif /* end of CssProcSrchRslt.h */










