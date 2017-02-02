
/*****************************************************************************
  1. Including header files
*****************************************************************************/
#include  "NasComm.h"
#include  "NasMsccSndInternalMsg.h"
#include  "NasMsccMsgPrioCompare.h"
#include  "NasMsccCtx.h"
#include  "MmaMsccInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 Global Variable Define
*****************************************************************************/




NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithSystemAcquireTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MSCC_SCAN_TIMER),
                             NAS_MSCC_CompareTiScanTimerExpiredPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire),
};



NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithBSRTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithBSR),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithBSR),
};



NAS_MSCC_MSG_COMPARE_STRU g_astMsccMsgPrioCompareWithPowerOffTbl[] =
{
    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_SYS_CFG_SET_REQ),
                             NAS_MSCC_CompareSysCfgSetPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMA, ID_MMA_MSCC_POWER_OFF_REQ),
                             NAS_MSCC_ComparePowerOffReqPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_HSD, ID_HSD_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithPowerOff),

    NAS_MSCC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_RF_AVAILABLE_IND),
                              NAS_MSCC_ComparePsStatusIndPrioWithPowerOff),
};


NAS_MSCC_FSM_MSG_COMPARE_STRU g_astMsccMsgCompareTbl[] =
{
    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_SYS_ACQ,
                                  g_astMsccMsgPrioCompareWithSystemAcquireTbl),

    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION,
                                  g_astMsccMsgPrioCompareWithBSRTbl),

    NAS_MSCC_FSM_COMPARE_TBL_ITEM(NAS_MSCC_FSM_POWER_OFF,
                                  g_astMsccMsgPrioCompareWithPowerOffTbl)

};


/*****************************************************************************
  3 Function Implement
*****************************************************************************/

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareTiScanTimerExpiredPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}

NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithSystemAcquire(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}




NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithBSR(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_CompareSysCfgSetPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePowerOffReqPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}


NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_ComparePsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_STORE;
}




NAS_MSCC_MSG_COMPARE_FUNC  NAS_MSCC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
)
{
    NAS_MSCC_FSM_MSG_COMPARE_STRU      *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for (i = 0 ; i < (sizeof(g_astMsccMsgCompareTbl)/sizeof(NAS_MSCC_FSM_MSG_COMPARE_STRU)) ; i++ )
    {
        if ( enFsmId == g_astMsccMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMsccMsgCompareTbl[i];
            break;
        }
    }

    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        #if 0
        if (NAS_MSCC_WILDCARD_MSG_ID == pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType )
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
        #endif

        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    return VOS_NULL_PTR;
}



NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8 NAS_MSCC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_COMPARE_FUNC                               pfCompareFunc;
    NAS_MSCC_FSM_ID_ENUM_UINT32                             enCurrFsmId;
    NAS_MSCC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT8               enRslt;

    enCurrFsmId         = NAS_MSCC_GetCurrFsmId();
    if (NAS_MSCC_BUTT == enCurrFsmId)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_GetMsgComparePrioRslt: NAS_MSCC_GetCurrFsmId return NAS_MSCC_BUTT");
    }

    pfCompareFunc       = NAS_MSCC_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    if (VOS_NULL_PTR == pfCompareFunc )
    {
        return NAS_MSCC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    enRslt = pfCompareFunc(ulEventType, pstMsg);

    return enRslt;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

