

#ifndef __TAFAPSDSFLOWSTATS_H__
#define __TAFAPSDSFLOWSTATS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Ps.h"
#include "TafApsApi.h"
#include "ApsCdsInterface.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cttf_1x_rlp_bo_pif.h"
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
#include "cnas_cttf_hrpd_pa_pif.h"
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_APS_CDATA_NO_DATA_TIME_LEN_PER_TIMES                    (20)   /* ��λ ���� */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, begin */
#define TAF_APS_CDATA_EVDO_NO_DATA_TIME_LEN_PER_TIMES               (80)   /* ��λ ���� */
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-2, end */

/* 64λ���������㣬�ӷ� : rst = argA + argB */
#define TAF_APS_BIT64_ADD(rstHi, rstLo, argAHi, argALo, argBHi, argBLo) \
    { \
        if ((argALo) > (0xFFFFFFFF - (argBLo))) \
        { \
            (rstHi) = (argAHi) + ((argBHi) + 1); \
        } \
        else \
        { \
            (rstHi) = (argAHi) + (argBHi); \
        } \
        (rstLo) = (argALo) + (argBLo); \
    }


/* 64λ���������㣬���� : rst = argA - argB */
/* Notes: we assumed argA always great than or equal to argB */
#define TAF_APS_BIT64_SUB(rstHi, rstLo, argAHi, argALo, argBHi, argBLo) \
    { \
        if ((argALo) < (argBLo)) \
        { \
            (rstHi) = (argAHi) - ((argBHi) + 1); \
        } \
        else \
        { \
            (rstHi) = (argAHi) - (argBHi); \
        } \
        (rstLo) = (argALo) - (argBLo); \
    }


/* 64λ���������㣬�Ƚ� : rst = (argA > argB) ? GREAT : ((argA == argB) ? EQUAL : LESS) */
#define TAF_APS_BIT64_COMPARE(argAHi, argALo, argBHi, argBLo, result) \
    {\
        if ((argAHi) > (argBHi))\
        {\
            result = TAF_APS_BIT64_GREAT;\
        }\
        else if (((argAHi) == (argBHi)) && ((argALo) > (argBLo)))\
        {\
            result = TAF_APS_BIT64_GREAT;\
        }\
        else if (((argAHi) == (argBHi)) && ((argALo) == (argBLo)))\
        {\
            result = TAF_APS_BIT64_EQUAL;\
        }\
        else\
        {\
            result = TAF_APS_BIT64_LESS;\
        }\
    }


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö������  : TAF_APS_BIT64_CMP_RSLT_ENUM
 ö��˵��  : 64λ���ͱȽϽ��
*****************************************************************************/
enum TAF_APS_BIT64_CMP_RSLT_ENUM
{
    TAF_APS_BIT64_GREAT                 = 0,
    TAF_APS_BIT64_EQUAL,
    TAF_APS_BIT64_LESS
};
typedef VOS_UINT32 TAF_APS_BIT64_CMP_RSLT_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/




/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID  TAF_APS_StartDsFlowStats(
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_StopDsFlowStats(
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_QryDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo,
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_QryAllRabDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstTotalDsFlowQryInfo
);

VOS_VOID  TAF_APS_ClearDsFlowStats(
    VOS_UINT8                           ucRabId
);

VOS_VOID  TAF_APS_ClearAllRabDsFlowStats( VOS_VOID );

VOS_VOID  TAF_APS_StartDsFlowRpt( VOS_VOID );

VOS_VOID  TAF_APS_StopDsFlowRpt( VOS_VOID );

VOS_VOID TAF_APS_QryDsFlowReportInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
);

VOS_VOID TAF_APS_QryAllRabDsFlowReportInfo(
    TAF_DSFLOW_REPORT_STRU             *pstTotalDsFlowRptInfo
);
VOS_VOID  TAF_APS_GetCurrentFlowInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_INFO_STRU               *pstCurrentFlowInfo
);

VOS_VOID  TAF_APS_UpdateAllRabCurrentFlowInfo( VOS_VOID );

VOS_UINT32  TAF_APS_CheckIfActiveRabIdExist( VOS_VOID );

VOS_VOID  TAF_APS_CalcDsflowRate(
    VOS_UINT32                          ulStartHigh,
    VOS_UINT32                          ulStartLow,
    VOS_UINT32                          ulEndHigh,
    VOS_UINT32                          ulEndLow,
    VOS_UINT32                          ulPeriod,
    VOS_UINT32                         *pulRate
);

VOS_VOID TAF_APS_ClearApDsFlowStats(VOS_VOID);
VOS_VOID TAF_APS_ProcApDsFlowRpt(VOS_VOID);

VOS_VOID TAF_APS_ReleaseDfs(VOS_VOID);
VOS_VOID TAF_APS_SwitchDdrRateByCurrentRate(
    VOS_UINT32                          ulDlRate,
    VOS_UINT32                          ulUlRate
);
VOS_UINT32 TAF_APS_FindDfsReqValue(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
);

VOS_UINT32 TAF_APS_CheckIfMinDdrBand(
    VOS_UINT32                          ulReqValue
);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_ProcRlpDataStatusCb(
    const RLPITF_1X_RLP_DATA_STAT_STRU       * const pstRlpDataStat
);

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
VOS_VOID TAF_APS_ProcEvdoRlpDataStatusCb(
    PS_BOOL_ENUM_UINT8                  enFlowActivity
);
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */
#endif


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

#endif /* end of TafApsDsFlowStats.h */
