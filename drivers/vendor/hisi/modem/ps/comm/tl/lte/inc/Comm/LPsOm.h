

#ifndef __PSOM_H__
#define __PSOM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "product_config.h"
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "PsLogdef.h"
#include  "PsCommonDef.h"
#include  "msp.h"
#include  "LPSCommon.h"
#include  "OmCommon.h"
#include  "AppRrcInterface.h"
#include  "LPsNvInterface.h"
#include  "TLPsPrintDict.h"

/*#include  "LHpaMsgDebug.h" deleted by hujianbo 20130809:��Ʒ�߲ü�����ʱ���ܰ����ǿ���ͷ�ļ����ʽ���ȥ��*/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/

#define  MAX_HMAC_HASH_SIZE              32  /* KDF�㷨�õ������HMAC���� */
#define  LPS_GAS_OM_OTA_IND                 0xA025

#define  LPS_GNAS_OM_OTA_IND                0xC103

#define  LPS_WAS_OM_OTA_IND                 0XB022

#define  EN_NV_ID_TEST_MODE_FLAG            6656

#define TLRRC_VERSION_V9R1                  0x91

#define TLRRC_VERSION_V7R2                  0x72

#define TLRRC_VERSION_V7R1                  0x71

#define TLRRC_FEATURE_ON                    1
#define TLRRC_FEATURE_OFF                   0
#define TLRRC_FEATURE_STK_V9R1              TLRRC_FEATURE_ON

#define  TLRRC_VERSION                      TLRRC_VERSION_V7R2

/*g_astMsgIdToPidTbl��������ٵ�message id�Ľ��޸���*/
#define LPS_OM_MSG_TABLE_MIN_NUM             2

/*VOS_PID_BUTT��Ч��PID*/
#define LPS_PID_NULL                         VOS_PID_BUTT

#define LPS_OM_SPECIFY_FLG                   (0x0000000FUL)

#define TLRRC_FEATURE_ON                    1
#define TLRRC_FEATURE_OFF                   0

#define TLRRC_FAST_CSFB_FEATURE             TLRRC_FEATURE_ON
#define LHPA_DATA_ABORT_LAST_MSG           16

/*32KTime Stamp��תһ�ζ�Ӧ��ʱ�䣬�뼶��λ����Ӧ����λ��*/
#define TLPS_32TSTAMP_HIGHBIT_MOVE_BIT_IN_SECOND  (17)

/*32KTime Stamp����Ķ�Ӧ��ϵ������32768��������15λ*/
#define TLPS_32TSTAMP_ACCURACY_MOVE_BIT_IN_SECOND       (15)

/*32KTime Stamp ��λ���ֵ�������ֵ���ڴ�ֵ��������32λ����ﵽ���*/
#define TLPS_32TSTAMP_MAX_HIGH_VAL       (0x7FFFUL)

#define TLPS_PRINT2LAYER_INVALID_VALUE     (0xa5a5a5a5)

#if (VOS_OS_VER != VOS_WIN32)
#define PS_LOG_RETURN() \
            if(0 != g_ulTimeDelaySwitch) \
            {\
              return;\
            }

#define PS_LOG_RETURN_SUCC() \
            if(0 != g_ulTimeDelaySwitch) \
            {\
              return VOS_OK;\
            }

#define PS_HOOK_LOG_RETURN_SUCC() \
            if(0 != g_ulTimeDelayHookSwitch) \
            {\
              return VOS_OK;\
            }

#else
#define PS_LOG_RETURN()

#define PS_LOG_RETURN_SUCC()

#define PS_HOOK_LOG_RETURN_SUCC()
#endif

/*LOG��ӡ*/
#define LPS_OM_INFO_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString)

#define LPS_OM_INFO_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString, lPara1)

#define LPS_OM_INFO_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_INFO, pcString, lPara1,lPara2)

#define LPS_OM_WARNING_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString)

#define LPS_OM_WARNING_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString, lPara1)

#define LPS_OM_WARNING_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_WARNING, pcString, lPara1,lPara2)

#define LPS_OM_ERROR_LOG(pcString)\
        LPS_LOG(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString)

#define LPS_OM_ERROR_LOG1(pcString, lPara1)\
        LPS_LOG1(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString, lPara1)

#define LPS_OM_ERROR_LOG2(pcString, lPara1, lPara2)\
        LPS_LOG2(UE_MODULE_PS_OM, 0, LOG_LEVEL_ERROR, pcString, lPara1,lPara2)



/*PS������APP����������Ϣ�󣬰���Ϣ�Ŀռ��ͷ�*/
#define LPS_OM_FREE_APP_MSG_MEM(pAddr)   PS_MEM_FREE(PS_PID_OM, pAddr);

/* ���ʱ��ͳ����Ϣ */
#define LPS_OM_Get_LATENCY_INFO() (&g_stPsLatencyStat)

#if (VOS_OS_VER != VOS_WIN32)
/* ����HO����ʱ�� */
#define LPS_HO_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stHoLatency.aulHoLatency, ucLatencyType, LPS_HO_LATENCY_BUFF);\
}
/* ���ý�����ʱ�� */
#define LPS_EST_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stEstLatency.aulEstLatency, ucLatencyType, LPS_EST_LATENCY_BUFF);\
}
/* �����ؽ�ʱ�� */
#define LPS_REEST_SET_LATENCY_TIME(ucLatencyType) \
{\
    LPS_OM_SetLatency(g_stPsLatencyStat.stReestLatency.aulReestLatency, ucLatencyType, LPS_REEST_LATENCY_BUFF);\
}

/* ��ý���������ʱ���Ƿ���Ч��־ */
#define LPS_EST_GET_LATENCY_FLAG() (g_stPsLatencyStat.stEstLatency.enContralPlaneValidFlag)

#define LPS_EST_SET_LATENCY_FLAG(ulFlag) (g_stPsLatencyStat.stEstLatency.enContralPlaneValidFlag = ulFlag)

/* ����ؽ�ʱ���Ƿ���Ч��־ */
#define LPS_REEST_GET_LATENCY_FLAG() (g_stPsLatencyStat.stReestLatency.enReestValidFlag)

#define LPS_REEST_SET_LATENCY_FLAG(ulFlag) (g_stPsLatencyStat.stReestLatency.enReestValidFlag = ulFlag)



/* mod by guojiyu ��ά�ɲ��л�ʱ�� begin */
#define LPS_GET_HO_LatencyInfo()            (&g_stPsHoInfo)

#define LPS_HO_GET_HO_TYPE()                (g_stPsHoInfo.enHoType)
#define LPS_HO_SET_HO_TYPE(enHoType)        (LPS_HO_GET_HO_TYPE() = (enHoType))

#define LPS_GET_HO_LatestHOLatency()        (g_stPsHoInfo.usLatestHOLatency)
#define LPS_GET_HO_HoLatencyInfo(enHoType)  (g_stPsHoInfo.astHOLatencyInfo + (enHoType))

#define LPS_GET_HO_AllSuccTime(enHoType)    (g_stPsHoInfo.aulAllHoSuccTime[enHoType])
/* mod by guojiyu ��ά�ɲ��л�ʱ�� end */
#define LPS_OM_GET32K_TIMESTAMP(pulHigBit,pulLowBit)  (VOS_VOID)mdrv_timer_get_accuracy_timestamp((pulHigBit),(pulLowBit))
#else
#define LPS_HO_SET_LATENCY_TIME(ucLatencyType)
/* ���ý�����ʱ�� */
#define LPS_EST_SET_LATENCY_TIME(ucLatencyType)
/* �����ؽ�ʱ�� */
#define LPS_REEST_SET_LATENCY_TIME(ucLatencyType)


/* ��ý���������ʱ���Ƿ���Ч��־ */
#define LPS_EST_GET_LATENCY_FLAG()                                  PS_FALSE

#define LPS_EST_SET_LATENCY_FLAG(ulFlag)

/* ����ؽ�ʱ���Ƿ���Ч��־ */
#define LPS_REEST_GET_LATENCY_FLAG()                                PS_FALSE

#define LPS_REEST_SET_LATENCY_FLAG(ulFlag)

/* mod by guojiyu ��ά�ɲ��л�ʱ�� begin */
#define LPS_GET_HO_LatencyInfo()

#define LPS_HO_GET_HO_TYPE()
#define LPS_HO_SET_HO_TYPE(enHoType)

#define LPS_GET_HO_LatestHOLatency()
#define LPS_GET_HO_HoLatencyInfo(enHoType)

#define LPS_GET_HO_AllSuccTime(enHoType)
/* mod by guojiyu ��ά�ɲ��л�ʱ�� end */

#define LPS_OM_GET32K_TIMESTAMP(pulHigBit,pulLowBit)  mdrv_timer_get_accuracy_timestamp((pulHigBit),(pulLowBit))


#endif
/*TDS begin*/

#if ((!defined(_lint)) && (PRINT_SWITCH == PRINT_OFF) && (VOS_WIN32 != VOS_OS_VER))

#define tra01_10tdynamicTrace(pcString, ...)
#define tgl01_21dynamicTraceToLog(pcString, ...)
#define fpv01_30SpvDynamicTraceToLog(pcString, ...)
#define fpv01_32AtrDynamicTraceToLog(pcString, ...)
#define fpv01_33AtcDynamicTraceToLog(pcString, ...)
#define fpv01_31SimDynamicTraceToLog(pcString, ...)
#define tra06_40dynamicTrace(ulId,pcString, ...)

#else
#define tra01_10tdynamicTrace TDS_OM_DiagPrint
#define tgl01_21dynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_30SpvDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_32AtrDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_33AtcDynamicTraceToLog TDS_OM_DiagPrint
#define fpv01_31SimDynamicTraceToLog TDS_OM_DiagPrint
#define tra06_40dynamicTrace TDS_OM_DiagPrint1
#endif
/*TDS end*/


#define LPS_GET_NV_MEAS_THRESHOLD()                      (&g_LPsNvCellMeasThredhold)

#define LPS_GET_NV_RSRP_THRESHOLD()                      (g_LPsNvCellMeasThredhold.sRsrpHoldThreshold) /* PHY�ϱ��Ĳ���ֵС��ĳֵ ucRsrpLowCount++*/
#define LPS_SET_NV_RSRP_THRESHOLD(sRsrpHoldThreshold)    (LPS_GET_NV_RSRP_THRESHOLD() = (sRsrpHoldThreshold)) /* PHY�ϱ��Ĳ���ֵС��ĳֵ ucRsrpLowCount++*/

#define LPS_GET_NV_RSRP_LOW_CONT()                       (g_LPsNvCellMeasThredhold.ucRsrpLowCount)  /* PHY�ϱ��Ĳ���ֵС��sRsrpHoldThreshold�ﵽ���Ρ������ؽ����� */
#define LPS_SET_NV_RSRP_LOW_CONT(ucRsrpLowCount)         (LPS_GET_NV_RSRP_LOW_CONT() = (ucRsrpLowCount))  /* PHY�ϱ��Ĳ���ֵС��sRsrpHoldThreshold�ﵽ���Ρ������ؽ����� */

#define LPS_GET_NV_SYNSSWITCH()                           (g_LPsNvCellMeasThredhold.ucSynsSwitch) /*�Ƿ���������ֵ���׷����ؽ����� */
#define LPS_SET_NV_SYNSSWITCH(ucSynsSwitch)               (LPS_GET_NV_SYNSSWITCH() = (ucSynsSwitch)) /*�Ƿ���������ֵ���׷����ؽ����� */


#define LPS_VERSION_V_NO                     (700)                                 /* V�汾�� */
#define LPS_VERSION_R_NO                     (  1)                                 /* R�汾�� */
#define LPS_VERSION_C_NO                     ( 10)                                 /* C�汾�� */
#define LPS_VERSION_B_NO                     ( 60)                                 /* B�汾�� */
#define LPS_VERSION_SPC_NO                   (000)                                 /* SPC�汾�� */
#define LPS_VERSION_PRODUCT_NO               (1)                                   /* Product Version */

/* Print To Layer Begin */

#define TLPS_TIMER_LENGTH_OF_SEND_PRINT               (8000)
#define TLPS_PRINT_NUM_OF_BUFFER                      (3)
#if (VOS_OS_VER != VOS_WIN32)
#define TLPS_LOG_GetSendPrintFlagTimerAddr()   (&(g_stSendPrintFlagTimer))

#define TLPS_LOG_GetBufferTimer()              (TLPS_LOG_GetSendPrintFlagTimerAddr()->pucSendPrintTimer)
#define TLPS_LOG_GetSendFlag()                 (TLPS_LOG_GetSendPrintFlagTimerAddr()->enSendFlag)
#define TLPS_LOG_SetSendFlag(enFlag)           (TLPS_LOG_GetSendFlag() = (enFlag))

#define TLPS_LOG_GetPrintLevel()            (TLPS_LOG_GetSendPrintFlagTimerAddr()->enPrintLevel)
#define TLPS_LOG_SetPrintLevel(enLevel)     (TLPS_LOG_GetPrintLevel() = (enLevel))

#define TLPS_LOG_GetPrintInfoIndAddr()         (&(g_stPrintInfoInd))

#define TLPS_LOG_GetPrintListAddr()            (&(g_stPrintInfoList))
#define TLPS_LOG_GetSendPrintListAddr(ucIndex) (&(g_astSendPrintInfoList[ucIndex]))
#define TLPS_LOG_GetSendPrintListFLAG(ucIndex) (TLPS_LOG_GetSendPrintListAddr(ucIndex)->enFlag)

#define TLPS_LOG_GetCntofPrint()               (TLPS_LOG_GetPrintListAddr()->usCntofPrint)
#define TLPS_LOG_SetCntofPrint(usNum)          (TLPS_LOG_GetCntofPrint() = (usNum))

#define TLPS_LOG_GetPrintInfo(usCnt)             (&(TLPS_LOG_GetPrintListAddr()->astPrintInfo[(usCnt)]))

#define TLPS_LOG_GetStartTimeStampLow32(usCnt)              (TLPS_LOG_GetPrintInfo(usCnt)->ulStartTimeStampLow32)
#define TLPS_LOG_SetStartTimeStampLow32(usCnt, ulTimeStamp) (TLPS_LOG_GetStartTimeStampLow32(usCnt) = (ulTimeStamp))

#define TLPS_LOG_GetStartTimeStampHigh16(usCnt)             (TLPS_LOG_GetPrintInfo(usCnt)->usStartTimeStampHigh16)
#define TLPS_LOG_SetStartTimeStampHigh16(usCnt, usTimeStamp)(TLPS_LOG_GetStartTimeStampHigh16(usCnt) = (usTimeStamp))


#define TLPS_LOG_SetPrintInfoFunctionID(usCnt, enInFunctionId)  \
                                (TLPS_LOG_GetPrintInfo(usCnt)->enFunctionId = (enInFunctionId))

#define TLPS_LOG_SetPrintInfoProcFlag(usCnt, enInProcFlag) \
                                (TLPS_LOG_GetPrintInfo(usCnt)->enProcFlag = (enInProcFlag))

#define TLPS_LOG_SetPrintInfoPara1(usCnt, lInPara1)  \
                                (TLPS_LOG_GetPrintInfo(usCnt)->lPara1 = (lInPara1))

#define TLPS_LOG_SetPrintInfoPara2(usCnt, lInPara2) \
                                (TLPS_LOG_GetPrintInfo(usCnt)->lPara2 = (lInPara2))
#else
#define TLPS_LOG_SetPrintLevel(enLevel)
#endif
/***************************PRINT2LAYER  �ӿ� begin*************************/
#if ((PRINT2LAYER_SWITCH == PRINT_OFF) || (VOS_OS_VER == VOS_WIN32))
#define TLPS_PRINT2LAYER_INFO(enFunction, enProcFlag)

#define TLPS_PRINT2LAYER_INFO1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_INFO2(enFunction, enProcFlag, lPara1, lPara2)

#define TLPS_PRINT2LAYER_WARNING(enFunction, enProcFlag)
#define TLPS_PRINT2LAYER_WARNING1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_WARNING2(enFunction, enProcFlag, lPara1, lPara2)

#define TLPS_PRINT2LAYER_ERROR(enFunction, enProcFlag)

#define TLPS_PRINT2LAYER_ERROR1(enFunction, enProcFlag, lPara1)

#define TLPS_PRINT2LAYER_ERROR2(enFunction, enProcFlag, lPara1, lPara2)
#else

#define TLPS_PRINT2LAYER_INFO(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_INFO1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_INFO2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_INFO, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#define TLPS_PRINT2LAYER_WARNING(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_WARNING1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_WARNING2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_WARNING, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#define TLPS_PRINT2LAYER_ERROR(enFunction, enProcFlag)\
            TLPS_ProcPrint2LayerLevel(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag))

#define TLPS_PRINT2LAYER_ERROR1(enFunction, enProcFlag, lPara1)\
            TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag), (VOS_INT32)(lPara1))

#define TLPS_PRINT2LAYER_ERROR2(enFunction, enProcFlag, lPara1, lPara2)  \
            TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_ERROR, (enFunction),\
                (enProcFlag),(VOS_INT32)(lPara1), (VOS_INT32)(lPara2))

#endif

/***************************PRINT2LAYER  �ӿ� end*************************/


/* Print To Layer End */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : LPS_PRINT_LOCATION_ENUM
 �ṹ˵��  : LRRC��ӡʱ���ڱ�Ǵ���λ�õ�ö��
*****************************************************************************/
enum LPS_PRINT_LOCATION_ENUM
{
    LPS_PRINT_LOCATION_1 = 1,
    LPS_PRINT_LOCATION_2,
    LPS_PRINT_LOCATION_3,
    LPS_PRINT_LOCATION_4,
    LPS_PRINT_LOCATION_5,
    LPS_PRINT_LOCATION_6,
    LPS_PRINT_LOCATION_7,
    LPS_PRINT_LOCATION_8,
    LPS_PRINT_LOCATION_9,
    LPS_PRINT_LOCATION_10,
    LPS_PRINT_LOCATION_11,
    LPS_PRINT_LOCATION_12,
    LPS_PRINT_LOCATION_13,
    LPS_PRINT_LOCATION_14,
    LPS_PRINT_LOCATION_15,
    LPS_PRINT_LOCATION_BUTT
};
typedef VOS_UINT32 LPS_PRINT_LOCATION_ENUM_UINT32;

/* mod by guojiyu 0xffff begin */
/*****************************************************************************
 �ṹ��    : LPS_HO_TYPE_ENUM
 �ṹ˵��  : �л�����ö��
*****************************************************************************/
enum LPS_HO_TYPE_ENUM
{
    LPS_INTRA_FREQ_HO = 0,
    LPS_INTER_FREQ_HO,
    LPS_INTER_RAT_HO,
    LPS_HO_TYPE_BUFF
};
typedef VOS_UINT8 LPS_HO_TYPE_ENUM_UINT8;
/* mod by guojiyu 0xffff END */

/*****************************************************************************
 �ṹ��    : LPS_HO_LATENCY_ENUM
 �ṹ˵��  : �л�ʱ�ӽ׶�ö��
*****************************************************************************/
enum LPS_HO_LATENCY_ENUM
{
    LPS_HO_LATENCY_LRRC_SND_MEAS_RPT = 0,/* mod by guojiyu 0xffff begin */
    LPS_HO_LATENCY_LRRC_RCV_HO_RECFG,
    LPS_HO_LATENCY_LRRC_RCV_NAS_RABM_RSP,
    LPS_HO_LATENCY_LRRC_RCV_CMM_HO_CNF,
    LPS_HO_LATENCY_LRRC_RCV_STOP_PDCP_CNF,
    LPS_HO_LATENCY_LRRC_SND_DSP_HO_REQ,
    LPS_HO_LATENCY_LRRC_RCV_DSP_HO_CNF,
    LPS_HO_LATENCY_LRRC_SND_MAC_RA_REQ,
    LPS_HO_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_HO_LATENCY_LMAC_RCV_RAR,
    LPS_HO_LATENCY_LRRC_RCV_MAC_RA_CNF,
    LPS_HO_LLATENCY_RRC_SND_SMC_SECU_CFG,
    LPS_HO_LATENCY_LRRC_SND_RECFG_CMP,
    LPS_HO_LATENCY_LRRC_RCV_AM_DATA_CNF,
    LPS_HO_LATENCY_LRRC_RCV_CQI_SRS_CNF,
    LPS_HO_LATENCY_LRRC_RCV_PDCP_CONTINUE_CNF,
    LPS_HO_LATENCY_LRRC_RCV_RABM_STATUS_RSP,
    LPS_HO_LATENCY_BUFF
};

/*****************************************************************************
 �ṹ��    : LPS_REEST_LATENCY_ENUM
 �ṹ˵��  : �ؽ�ʱ�ӽ׶�ö��
*****************************************************************************/
enum LPS_REEST_LATENCY_ENUM
{
    LPS_REEST_LATENCY_LRRC_RCV_REESTIND,
    LPS_REEST_LATENCY_LRRC_SND_CELL_SEARCH_REQ,
    LPS_REEST_LATENCY_LRRC_RCV_CELLSEARCH_IND,
    LPS_REEST_LATENCY_LRRC_RCV_SI,
    LPS_REEST_LATENCY_LRRC_CAMP_REQ,
    LPS_REEST_LATENCY_LRRC_CAMP_CNF,
    LPS_REEST_LATENCY_LRRC_SND_LMAC_RA_REQ ,
    LPS_REEST_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_REEST_LATENCY_LMAC_RCV_RAR,
    LPS_REEST_LATENCY_LRRC_RCV_LMAC_RA_CNF,
    LPS_REEST_LATENCY_LMAC_SND_MSG3,
    LPS_REEST_LATENCY_LRRC_RCV_REEST,
    LPS_REEST_LATENCY_LRRC_SND_REEST_CMPL,
    LPS_REEST_LATENCY_BUFF
};
typedef VOS_UINT8 LPS_REEST_LATENCY_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : LPS_EST_LATENCY_ENUM
 �ṹ˵��  : ������ʱ�ӽ׶�ö��
*****************************************************************************/
enum LPS_EST_LATENCY_ENUM
{
    LPS_EST_LATENCY_LRRC_SND_LMAC_RA_REQ = 0,
    LPS_EST_LATENCY_LMAC_LPHY_ACCESS_REQ,
    LPS_EST_LATENCY_LMAC_RCV_RAR,
    LPS_EST_LATENCY_LRRC_RCV_LMAC_RA_CNF,
    LPS_EST_LATENCY_LMAC_SND_MSG3,
    LPS_EST_LATENCY_LRRC_RCV_SETUP,
    LPS_EST_LATENCY_LRRC_SND_SETUP_CMP,
    LPS_EST_LATENCY_LRRC_RCV_CAP_ENQ,
    LPS_EST_LATENCY_LRRC_SND_CAP_INFO,
    LPS_EST_LATENCY_LRRC_RCV_SEC_CMD,
    LPS_EST_LATENCY_LRRC_RCV_RECFG,
    LPS_EST_LATENCY_LRRC_SND_SEC_CMD_CMP,
    LPS_EST_LATENCY_LRRC_SND_RECFG_CMP,
    LPS_EST_LATENCY_BUFF
};
typedef VOS_UINT8 LPS_EST_LATENCY_ENUM_UINT8;


enum LPS_REBOOT_MOD_ID_ENUM
{
    LPS_REBOOT_MOD_ID_MML   = 0Xa0000000,
    LPS_REBOOT_MOD_ID_BUTT  = 0X6FFFFFFF
};
typedef VOS_UINT32 LPS_REBOOT_MOD_ID_ENUM_UINT32;


typedef enum
{
    TL_KPI_TYPE_EST         = 0x0,
    TL_KPI_TYPE_KEEP        = 0x1,
    TL_KPI_TYPE_MOBILITY    = 0x2,
    TL_KPI_TYPE_DELAY       = 0x3,
    TL_KPI_TYPE_BUTT
}TL_KPI_TYPE_ENUM;
typedef VOS_UINT32 TL_KPI_TYPE_ENUM_UINT32;



enum TLPS_PRINT_LEVEL_ENUM
{
    TLPS_PRINT_INFO = 0,
    TLPS_PRINT_WARNING,
    TLPS_PRINT_ERROR,
    TLPS_PRINT_CLOSE,
    TLPS_PRINT_BUTT
};
typedef VOS_UINT8 TLPS_PRINT_LEVEL_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


#define TLPS_EXC_BUILD_MSG_PID(ulSendPid, ulRcvPid) \
            ((ulSendPid << 16) | (ulRcvPid & 0xffff))

#define TLPS_EXC_MSG_PRIVATE_OFFSET        6
#define TLPS_EXC_MAX_SAVE_MSG_NUM          200
#define TLPS_EXC_HPA_SEND_FAIL_MSG_NUM      8

typedef struct
{
    VOS_UINT32 ulTimeStamp; /* ʱ���*/
    VOS_UINT32 ulCompPid;   /* ulSendPid | ulRcvPid */
    VOS_UINT32 ulMsgId;     /* ��ϢID */
    VOS_UINT32 ulPrivate;   /* ��������һЩ��Ҫ��Ϣ�Ĺؼ�����*/
}TLPS_EXC_MSG_ELEMENT_STRU;


typedef struct
{
    VOS_UINT32                ulNextIndex;
    TLPS_EXC_MSG_ELEMENT_STRU astMsgList[TLPS_EXC_MAX_SAVE_MSG_NUM];
}TLPS_EXC_MSG_MNTN_STRU;
 /*****************************************************************************
 �ṹ��    : LPS_HO_LATENCY_STRU
 �ṹ˵��  : PS�л�ʱ��ͳ����Ϣ���ݽṹ(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enHoValidFlag;                          /* ���β���ֵ�Ƿ���Ч */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulHoLatency[LPS_HO_LATENCY_BUFF];        /* ��¼ÿ���ؼ���Ĳ���ֵ */
}LPS_HO_LATENCY_STRU;
/*****************************************************************************
 �ṹ��    : LPS_REEST_LATENCY_STRU
 �ṹ˵��  : PS�ؽ�ʱ��ͳ����Ϣ���ݽṹ(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enReestValidFlag;                       /* ���β���ֵ�Ƿ���Ч */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulReestLatency[LPS_REEST_LATENCY_BUFF];  /* ��¼ÿ���ؼ���Ĳ���ֵ */
}LPS_REEST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    : LPS_EST_LATENCY_STRU
 �ṹ˵��  : PS������ʱ��ͳ����Ϣ���ݽṹ(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enContralPlaneValidFlag;                /* ���β���ֵ�Ƿ���Ч */
    VOS_UINT8                           aucReservered[3];
    VOS_UINT32                          aulEstLatency[LPS_EST_LATENCY_BUFF];      /* ��¼ÿ���ؼ���Ĳ���ֵ */
}LPS_EST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    : LPS_LATENCY_STAT_STRU
 �ṹ˵��  : PSʱ��ͳ����Ϣ���ݽṹ(
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                   enReportFlg;                            /* ʱ����Ϣ�Ƿ��ϱ���־ */
    VOS_UINT8                            aucReserved[3];
    LPS_HO_LATENCY_STRU                  stHoLatency;                         /* �л�ʱ��ͳ����Ϣ */
    LPS_REEST_LATENCY_STRU               stReestLatency;                      /* �ؽ�ʱ��ͳ����Ϣ */
    LPS_EST_LATENCY_STRU                 stEstLatency;                          /* ���ӽ���ʱ��ͳ����Ϣ */
}LPS_LATENCY_STAT_STRU;
/*****************************************************************************
 �ṹ��    : LPS_OM_MSG_PID_PAIR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ϢID��ȡֵ����ʼֵ��PID�Ķ�Ӧ��ϵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulMsgIdStartVal;
    VOS_PID                         ulPid;
}LPS_OM_MSG_PID_PAIR_STRU;


/*****************************************************************************
 �ṹ��    : LPS_OM_MSG_ID_SEARCH_COMM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ulMsgId��ȡֵ��ulSpare�Ķ�Ӧ��ϵ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulMsgId;
    VOS_UINT32                      ulSpare;
}LPS_OM_MSG_ID_SEARCH_COMM_STRU;

/*added by guojiyu*/
/*****************************************************************************
 �ṹ��    : LPS_HANDOVER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          aulAllHoSuccTime[LPS_HO_TYPE_BUFF];
    VOS_UINT16                          usLatestHOLatency;      /*���һ���л�ʱ��*/
    VOS_UINT16                          usAverageHOLatency;     /*ƽ���л�ʱ��*/
    LPS_HO_TYPE_ENUM_UINT8              enHoType;
    VOS_UINT8                           ucResvd[3];
    LPS_HO_STAT_INFO_STRU               astHOLatencyInfo[LPS_HO_TYPE_BUFF];
}LPS_HANDOVER_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER                   /* VOS��Ϣͷ */
    VOS_UINT16    usTransPrimId;     /* �̶�ֵ 0x5001 */
    VOS_UINT16    usRsv1;            /* ���� */
    VOS_UINT8     ucFuncType;        /* ��Ϣ���٣��̶�ֵ 2 */
    VOS_UINT8     ucReserve;         /* ���� */
    VOS_UINT16    usLength;          /* ��һ�ֽ�����β�ĳ��ȣ���λΪ�ֽ� */
    VOS_UINT32    ulSn;              /* �ϱ���Ϣ�����к� */
    VOS_UINT32    ulTimeStamp;       /* ��Ϣ��ʱ��� */
    VOS_UINT16    usPrimId;          /* ԭ��ID */
    VOS_UINT16    usRsv2;             /* ���� */
    VOS_UINT16    usOtaMsgID;
    VOS_UINT8     ucUpDown;
    VOS_UINT8     ucRsv;
    VOS_UINT32    ulLengthASN;
    VOS_UINT8     aucData[4];
}LTE_GAS_OM_OTA_IND_STRUCT;

/*****************************************************************************
 �ṹ��    : T_DlRecvMsgStat
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��¼TDS���н���������Ϣ��ͳ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32    ulSccpchReadIndNum;
    VOS_UINT32    ulDpchReadIndNum;
    VOS_UINT32    ulHspdschReadIndNum;
    VOS_UINT32    ulHsUpaInfoIndNum;
}T_DlRecvMsgStat;
typedef struct
{
    VOS_UINT32      ulTimeStamp;
    VOS_UINT32      ulPid;
    VOS_UINT32      ulOpId;
    VOS_UINT32      MsgId;
}LHPA_DATA_ABORT_MSG_STRU;

typedef struct
{
    VOS_UINT32                    ulDownCurrCnt;
    VOS_UINT32                    ulUpCurrCnt;
    LHPA_DATA_ABORT_MSG_STRU      ulForMailBoxDownDataAbortMsg[LHPA_DATA_ABORT_LAST_MSG];
    LHPA_DATA_ABORT_MSG_STRU      ulForMailBoxUpDataAbortMsg[LHPA_DATA_ABORT_LAST_MSG];
    VOS_UINT32                    ulCurrMailBoxLen;
}LHPA_MAILBOX_DATAABORT_STRU;

extern LHPA_MAILBOX_DATAABORT_STRU  g_stHpaMailBoxDataAbortMsg;

#define     TDS_AIR_MSG_MAX    64

typedef struct
{
    VOS_UINT32                    ulTimeStamp;
    VOS_UINT32                    ulMsgId;
}TDS_AIR_MSG_STRU;

typedef struct
{
    VOS_UINT32                    ulMsgCnt;
    TDS_AIR_MSG_STRU              ulTdsMsg[TDS_AIR_MSG_MAX];

}TDS_AIR_MSG_RECORD_STRU;

extern TDS_AIR_MSG_RECORD_STRU  g_stTdsAirMsgRecord;


/*****************************************************************************
 �ṹ��    : LPS_32K_TIMESTAMP
 �ṹ˵��  : 32KTIMESTAMP
*****************************************************************************/
typedef struct
{
    VOS_UINT32   ul32KTStampHighBit;
    VOS_UINT32   ul32KTStampLowBit;
}LPS_32K_TIMESTAMP;
/*****************************************************************************
 �ṹ��    : TL_KPI_HDR_STRU
 �ṹ˵��  : KPI�ϱ���Ϣ����ͷ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;
    TL_KPI_TYPE_ENUM_UINT32     enType;
}TL_KPI_HDR_STRU;
/*****************************************************************************
 �ṹ��    : TL_KPI_DELAY_HDR_STRU
 �ṹ˵��  : ʱ���ϱ�����ͷ
*****************************************************************************/
typedef struct
{
    TL_KPI_HDR_STRU     stKpiHdr;
    VOS_UINT32          ulStartTime;
    VOS_UINT32          ulEnd;
    VOS_UINT32          ulDelay;
    VOS_UINT32          ulAvgDelay;
}TL_KPI_DELAY_HDR_STRU;
/* Print To Layer Begin */


typedef struct
{
    TLPS_PRINT_LEVEL_ENUM_UINT8            enPrintLevel;
    PS_BOOL_ENUM_UINT8                     enSendFlag;
    VOS_UINT8                              aucRev[2];
    HTIMER                                 pucSendPrintTimer;
}TLPS_PRINT_SEND_TIMER_STRU;




typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;
    APP_MSG_HEADER
    TLPS_PRINT_LEVEL_ENUM_UINT8         enPrintLevel;
    UINT8                               aucReserve[3];
} TLPS_SET_TLPS_PRINT2LAYER_REQ_STRU;

typedef  TLPS_SET_TLPS_PRINT2LAYER_REQ_STRU TLPS_SET_TLPS_PRINT2LAYER_CNF_STRU;

/* Print To Layer End */

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*#if (VOS_OS_VER != VOS_WIN32)
 */
extern LPS_LATENCY_STAT_STRU               g_stPsLatencyStat;
/*#endif
 */
#if (VOS_OS_VER != VOS_WIN32)
extern MSW_VER_INFO_S g_stPSVersionInfo;
#endif

/* mod by guojiyu ��ά�ɲ��л�ʱ�� begin */
/* �л�ʱ��ͳ��ȫ�ֱ��� */
extern LPS_HANDOVER_INFO_STRU          g_stPsHoInfo;
/* mod by guojiyu ��ά�ɲ��л�ʱ�� end */

/* gaojishan-remove-kdf-hmac-sha */

extern VOS_UINT32                       g_ulPsBandwidthSupportFlg;
/* modify by lishangfeng freq all begin */
extern VOS_UINT32                       g_ulPsFreqInAllBandWidthFlg;
/* modify by lishangfeng freq all end */

extern LPS_NV_MEAS_THRESHOLD_STRU g_LPsNvCellMeasThredhold;

extern VOS_UINT32 g_ulNasPlainRejMsgFlag;

extern VOS_UINT32 g_ulNasCsfbTauType2Flag;
#if (VOS_OS_VER != VOS_WIN32)
extern DIAG_TRANS_IND_STRU                    g_stPrintInfoInd;
extern TLPS_PRINT_INFO_LIST_STRU              g_stPrintInfoList;
extern TLPS_SEND_PRINT_BUFFER_STRU            g_astSendPrintInfoList[TLPS_PRINT_NUM_OF_BUFFER];
extern TLPS_PRINT_SEND_TIMER_STRU             g_stSendPrintFlagTimer;
#endif
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  LPS_OM_PidMsgProc(const MsgBlock *pMsg  );
extern VOS_UINT32 LPS_OM_SearchMsgIdTbl( VOS_UINT32 ulMsgId,
                                                 CONST LPS_OM_MSG_ID_SEARCH_COMM_STRU *pstTbl,
                                                 VOS_UINT32 ulTblSize,
                                                 VOS_UINT32 *pulTblIdx);
extern VOS_UINT32 LPS_OM_SearchMsgIdTblForHpa( VOS_UINT32 ulMsgId,
                                          CONST LPS_OM_MSG_ID_SEARCH_COMM_STRU *pstTbl,
                                          VOS_UINT32 ulTblSize,
                                          VOS_UINT32 *pulTblIdx);
extern VOS_UINT32 LPS_OM_TraceMsgHook( VOS_VOID *pMsg );

extern VOS_VOID LPS_OM_SetLatency(VOS_UINT32* pulLatency,
                            VOS_UINT8 ucLatencyType,VOS_UINT32 ulLatencyBuff);

extern VOS_VOID LNAS_LPSOM_GetNvRaMod ( VOS_UINT32       *pulPsCfgDspRatMod);
extern     VOS_VOID LNAS_LPSOM_GetCampedCellInfo(LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
        LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo);
extern  VOS_VOID LNAS_LPSOM_GetIpAddrInfo(APP_LPS_CAMPED_CELL_INFO_STRU *pstCampedCellInfo);
extern VOS_VOID LRRC_LPSOM_GetCampedCellInfo(APP_LPS_CAMPED_CELL_INFO_STRU *pstCampedCellInfo);
extern VOS_VOID LPS_OM_GetHoInfo(APP_LPS_HANDOVER_INFO_STRU *psPsOmGetHoinfo);
extern  VOS_VOID L2_LPSOM_GetMacPrachInfo(APP_LPS_PRACH_SR_INFO_STRU *pstLMacOmInfo);
extern  VOS_VOID L2_LPSOM_GetMacBsrInfo(APP_LPS_BSR_INFO_STRU *pstLMacOmBsrInfo);

VOS_VOID LPS_OM_CampedCellInfoInd(VOS_VOID);
VOS_VOID LPS_OM_CellHOInfoInd(VOS_VOID);
VOS_VOID LPS_OM_CampedCellInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_CellHOInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_PrachSrInfoReq(APP_OM_MSG_STRU *pMsg);
VOS_VOID LPS_OM_BsrInfoReq(APP_OM_MSG_STRU *pMsg);
extern VOS_UINT32 LTE_MsgHook( VOS_VOID *pMsg );
extern VOS_UINT32 LRrc_Om_MsgHookNoFilter( VOS_VOID *pMsg );
extern VOS_VOID  LPS_OM_StatInit(VOS_VOID);
/* gaojishan-Dug-mod-Begin */
/* gaojishan-reboot-save-lrrc-para-for-nas-reboot */
extern VOS_VOID LPS_SoftReBoot_SaveLRrc( VOS_VOID );
extern VOS_UINT32 LPS_SoftReBoot_WithLineNoAndFileID(VOS_UINT32 ulDbgNum,VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID);
/* gaojishan-Dug-mod-End */

extern VOS_VOID LHPA_ProcGetSelfAdjustPara( VOS_VOID );
#if (VOS_OS_VER != VOS_WIN32)

extern VOS_UINT32 LPS_OM_GetTmode(FTM_TMODE_ENUM* penFtmMode);
#endif
extern VOS_UINT32 LPS_OM_IsTestMode(VOS_VOID);

#if (FEATURE_ON == FEATURE_VERSION_V8)
#if (VOS_OS_VER != VOS_WIN32)
extern VOS_VOID TLPS_ExcLog_Save(cb_buf_t *pstData);
#endif
#else
extern VOS_VOID TLPS_ExcLog_Save(VOS_VOID);
#endif
extern VOS_UINT32 TLPS_TaskDelay(VOS_UINT32 ulLength);

/*��װȡ��ʱ�������*/
/*���ڵ����װ�ĺ�DRV_32K_GET_TICK()�޷�ʹ�ã�����ֻ���������壬FPGA�޷�ʹ��32K���Բ���*/
#define PS_GET_TICK()    VOS_GetTick()


extern VOS_UINT32 TDS_OM_DiagPrint(const VOS_CHAR *pcString, ...);
extern VOS_UINT32 TDS_OM_DiagPrint1(VOS_UINT32 ulId, const VOS_CHAR *pcString, ...);

extern VOS_VOID LPS_OM_StatInfoMsgProc(MsgBlock CONST *pMsg);
extern VOS_VOID TRRC_GetCurrentState(VOS_UINT8 *pCurrentProtocolState,
           VOS_UINT8 *pCurrentState  );

extern VOS_VOID TLPS_ExcLog_SaveMsgList(VOS_VOID *pMsg);
extern VOS_UINT32 PS_OM_SendMsg(VOS_UINT32 Pid, VOS_VOID *pMsg);
extern VOS_UINT32 LPsOm_GetTimeDiffByStampWithSecondUnit(LPS_32K_TIMESTAMP *pstOldTStamp,
                                                                         LPS_32K_TIMESTAMP *pstNewTStamp);

extern VOS_VOID  TLPS_Print2Layer(VOS_UINT16  enFunction, \
                                      VOS_UINT16 enProcFlag, \
                                      VOS_INT32 lPara1, VOS_INT32 lPara2);
extern VOS_VOID  TLPS_ProcPrint2LayerLevel(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16 enProcFlag);
extern  VOS_VOID  TLPS_ProcPrint2LayerLevel1(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16 enProcFlag, \
                                           VOS_INT32 lPara1);

extern  VOS_VOID  TLPS_ProcPrint2LayerLevel2(TLPS_PRINT_LEVEL_ENUM_UINT8 enPrintLevel,\
                                           VOS_UINT16  enFunction, \
                                           VOS_UINT16  enProcFlag, \
                                           VOS_INT32 lPara1, VOS_INT32 lPara2);
extern VOS_VOID  TLPS_COMM_SendAndFreePrintInfoInd(VOS_UINT32 ulSize, TLPS_SEND_PRINT_BUFFER_STRU * pData);
extern TLPS_SEND_PRINT_BUFFER_STRU * TLPS_AllocAndCopyPrintInfo(VOS_UINT32 ulSize);
extern VOS_VOID  TLPS_SendPrintBufferInfo(VOS_VOID);
extern VOS_VOID  TLPS_ProcSendPrintBufferExpire(VOS_VOID);
extern VOS_VOID  TLPS_StopPrint2LayerBufferTimer(VOS_VOID);
extern VOS_VOID  TLPS_StartPrint2LayerBufferTimer(VOS_VOID);

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

#endif /* end of LPsOm.h */
