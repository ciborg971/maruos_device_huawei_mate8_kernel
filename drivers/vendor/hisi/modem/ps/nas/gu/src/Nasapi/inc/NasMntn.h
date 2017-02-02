

#ifndef __NAS_MNTN_H__
#define __NAS_MNTN_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "NasOmInterface.h"
#include "NasOmTrans.h"
#include "NasErrorLog.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#include "msp_diag_comm.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, end */

#if (FEATURE_ON == FEATURE_PTM)
#include "omerrorlog.h"
#endif

/* Determine if a C++ compiler is being used.  If so, ensure that standard
   C is used to process the API information.  */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* #if __cplusplus */
#endif /* #ifdef __cplusplus */

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*****************************************************************************
 NAS��LOG��������:
*****************************************************************************/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define    NAS_INFO_LOG(Mod, String)                                    PS_NAS_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_INFO, (String) )
#define    NAS_INFO_LOG1(Mod, String,Para1)                             PS_NAS_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1) )
#define    NAS_INFO_LOG2(Mod, String,Para1,Para2)                       PS_NAS_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    NAS_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 PS_NAS_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    NAS_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           PS_NAS_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    NAS_NORMAL_LOG(Mod, String)                                  PS_NAS_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_NORMAL, (String) )
#define    NAS_NORMAL_LOG1(Mod, String,Para1)                           PS_NAS_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1) )
#define    NAS_NORMAL_LOG2(Mod, String,Para1,Para2)                     PS_NAS_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    NAS_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               PS_NAS_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    NAS_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         PS_NAS_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    NAS_WARNING_LOG(Mod, String)                                 PS_NAS_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_WARNING, (String) )
#define    NAS_WARNING_LOG1(Mod, String,Para1)                          PS_NAS_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1) )
#define    NAS_WARNING_LOG2(Mod, String,Para1,Para2)                    PS_NAS_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    NAS_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              PS_NAS_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    NAS_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        PS_NAS_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    NAS_ERROR_LOG(Mod, String)                                   PS_NAS_LOG ( (Mod), SUBMOD_NULL,  PS_LOG_LEVEL_ERROR, (String) )
#define    NAS_ERROR_LOG1(Mod, String,Para1)                            PS_NAS_LOG1 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1) )
#define    NAS_ERROR_LOG2(Mod, String,Para1,Para2)                      PS_NAS_LOG2 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    NAS_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                PS_NAS_LOG3 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    NAS_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          PS_NAS_LOG4 ( (Mod), SUBMOD_NULL, PS_LOG_LEVEL_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )


/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#define   PS_NAS_LOG(Mod, SubMod, Level, String) \
          DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, (String) )

#define   PS_NAS_LOG1(Mod, Level, Num, String, Para1) \
          DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, (String), (VOS_INT32)(Para1) )

#define   PS_NAS_LOG2(Mod, Level, Num, String, Para1, Para2) \
          DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )

#define   PS_NAS_LOG3(Mod, Level, Num, String, Para1, Para2, Para3) \
          DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )

#define   PS_NAS_LOG4(Mod, Level, Num, String, Para1, Para2, Para3, Para4) \
          DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

/* Added by wx270776 for OM�ں�, 2015-7-24, end */


#define NAS_COMM_BULID_ERRLOG_HEADER_INFO(pstHeader, ModemId, AlmId, AlmLevel, ulSlice, ulLength) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_GUNAS; \
    (pstHeader)->usModemId         = ModemId; \
    (pstHeader)->usAlmId           = AlmId; \
    (pstHeader)->usAlmLevel        = AlmLevel; \
    (pstHeader)->usAlmType         = NAS_ERR_LOG_ALM_TYPE_COMMUNICATION; \
    (pstHeader)->usAlmLowSlice     = ulSlice; \
    (pstHeader)->usAlmHighSlice    = 0; \
    (pstHeader)->ulAlmLength       = ulLength; \
}

#define NAS_COMM_BULID_INFOCLT_HEADER_INFO(pstHeader, ModemId, SceneType, ulLength) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_GUNAS; \
    (pstHeader)->usModemId         = ModemId; \
    (pstHeader)->usSceneType       = SceneType; \
    (pstHeader)->ulMsgLength       = ulLength; \
}

#define NAS_COMM_BULID_FTM_HEADER_INFO(pstHeader, ulLen, ModemId, usFuncId) \
{ \
    (pstHeader)->ulMsgModuleId     = OM_ERR_LOG_MOUDLE_ID_GUNAS; \
    (pstHeader)->usModemId         = ModemId; \
    (pstHeader)->usProjectId       = usFuncId; \
    (pstHeader)->ulProjectLength   = ulLen; \
}


#define NAS_TRACE_BUF_LEN 	            (256)

#define NAS_TRACE_LEVEL_LOW             (0x00000001)
#define NAS_TRACE_LEVEL_MED             (0x00000002)
#define NAS_TRACE_LEVEL_HIGH            (0x00000004)
#define NAS_TRACE_LEVEL_TOP             (NAS_TRACE_LEVEL_LOW | NAS_TRACE_LEVEL_MED | NAS_TRACE_LEVEL_HIGH)

#define NAS_TRACE_OUTPUT_ASHELL         (0x00000001)
#define NAS_TRACE_OUTPUT_CSHELL         (0x00000002)
#define NAS_TRACE_OUTPUT_ALL            (NAS_TRACE_OUTPUT_ASHELL | NAS_TRACE_OUTPUT_CSHELL)

#define NAS_MNTN_LOG_FORMAT(ulPrintLength, pcBuf, ulBufSize, pcFmt)\
            {\
                va_list pArgList;\
                /*lint -e586*/\
                va_start(pArgList, pcFmt);\
                ulPrintLength += VOS_nvsprintf(pcBuf + ulPrintLength,\
                                    ulBufSize - ulPrintLength, pcFmt, pArgList);\
                va_end(pArgList);\
                /*lint +e586*/\
                if (ulPrintLength > (ulBufSize - 1))\
                {\
                    ulPrintLength = ulBufSize - 1;\
                }\
                *(pcBuf + ulPrintLength) = '\0';\
            }

#if (VOS_OS_VER == VOS_WIN32) || defined(_lint)
#define NAS_DBG_PRINT(lvl, fmt, ...)\
            (VOS_VOID)vos_printf(fmt, ##__VA_ARGS__)
#else
#define NAS_DBG_PRINT(lvl, fmt, ...)\
            do\
            {\
                if (lvl == (g_ulNasTraceLevle & lvl))\
                {\
                    NAS_MNTN_LogPrintf("[TICK:%u][%s][LINE:%d] "fmt"\n", VOS_GetTick(), __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                }\
            }while(0)
#endif

#define NAS_TRACE_LOW(...)\
            NAS_DBG_PRINT(NAS_TRACE_LEVEL_LOW, __VA_ARGS__)

#define NAS_TRACE_MED(...)\
            NAS_DBG_PRINT(NAS_TRACE_LEVEL_MED, __VA_ARGS__)

#define NAS_TRACE_HIGH(...)\
            NAS_DBG_PRINT(NAS_TRACE_LEVEL_HIGH, __VA_ARGS__)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32 g_ulNasTraceLevle;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT16                          usPid;
    VOS_UINT16                          usTimerName;
}NAS_TIMER_EVENT_STRU;

/* Deleted by wx270776 for OM�ں�, 2015-7-23, begin */

/* Deleted by wx270776 for OM�ں�, 2015-7-23, end */


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;

    VOS_UINT16                          usOriginalId;
    VOS_UINT16                          usTerminalId;
    VOS_UINT32                          ulTimeStamp;
    VOS_UINT32                          ulSN;

    VOS_UINT32                          ulCommand;
    NAS_TIMER_EVENT_INFO_STRU           stTimerMsg;
}OM_MMC_TIMER_REPORT_CFG_REQ_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 NAS_MMC_IsRoam();

extern VOS_UINT32 NAS_MNTN_CheckServiceUnavailableEvent(
    NAS_OM_EVENT_ID_ENUM                enEventId
);
extern VOS_VOID NAS_MNTN_ServiceUnavailableType(
    VOS_UINT16                          usCause,
    VOS_BOOL                           *pbEventRequired
);

extern VOS_VOID NAS_MMA_OutputPlmnSrchBand(VOS_UINT32 *pulBand);

extern VOS_VOID NAS_MMA_OutputUsimInfo(NAS_MNTN_USIM_INFO_STRU *pstUsimInfo);

extern NAS_TIMER_EVENT_INFO_STRU* NAS_GetTimerEventReportCfg(VOS_VOID);

VOS_VOID NAS_TIMER_EventReport(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId
);
VOS_UINT32 NAS_IsNeedTimerEventReport(
    VOS_UINT32                          ulEventType
);

extern VOS_VOID NAS_MNTN_OutputPositionInfo(NAS_MNTN_POSITION_INFO_STRU *pstPositionInfo);

extern VOS_VOID NAS_MNTN_RecordPdpActiveFail(
    NAS_MNTN_ACTIVE_FAIL_TYPE_ENUM_UINT32                       enFailType,
    VOS_UINT8                                                   ucCntxtIndex,
    VOS_UINT8                                                   ucSmCause,
    VOS_UINT8                                                   ucRegisterFlg
);

extern VOS_VOID NAS_MNTN_RecordServiceUnavailable(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM                enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
);
extern VOS_VOID NAS_MNTN_RecordPlmnUnavailable(
    VOS_UINT8                           ucValIndex,
    VOS_UINT8                           ucCurTimes
);

VOS_VOID  NAS_SetNasOtaSwitch(
    VOS_UINT32                          ulNasOTASwitch
);

VOS_UINT32 NAS_GetNasOtaSwitch(VOS_VOID);

#if (FEATURE_ON == FEATURE_PTM)
VOS_UINT16 NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId);
NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16 NAS_GetErrLogUnsoliReportType(NAS_ERR_LOG_ALM_ID_ENUM_U16 enAlmId);
VOS_VOID NAS_COM_MntnPutRingbuf(
    VOS_UINT32                          ulName,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
);
#endif

NAS_ERR_LOG_CSFB_MT_STATE_ENUM_U32 NAS_MNTN_ConvertBaseStateToCsfbMtState(
    NAS_ERR_LOG_BASE_STATE_ENUM_U32     enBaseState
);

NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32 NAS_MNTN_ConvertOosEventToOosCause(
    NAS_ERR_LOG_OOS_EVENT_ENUM_UINT32   enOosEvent
);

VOS_VOID NAS_MNTN_SndLogMsg(VOS_CHAR *pcData, VOS_UINT32 ulDataLength);
VOS_VOID NAS_MNTN_LogPrintf(VOS_CHAR *pcFmt, ...);
VOS_VOID NAS_MNTN_SetTraceLevel(VOS_UINT32 ulLvl);
VOS_VOID NAS_MNTN_SetTraceOutput(VOS_UINT32 ulOutput);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif                                                                                 /* __cpluscplus                              */

#endif
