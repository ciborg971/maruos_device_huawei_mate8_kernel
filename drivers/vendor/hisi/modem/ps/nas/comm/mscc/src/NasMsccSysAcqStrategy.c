

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "NasMsccCtx.h"
#include "PsCommonDef.h"
#include "NasMsccMntn.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccComFunc.h"
#include "NasMsccSysAcqStrategy.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_SYS_ACQ_STRATEGY_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* according to different acquire scene,here provide the sys acq list build table */
NAS_MSCC_SYS_ACQ_LIST_BUILD_TBL_STRU    g_astNasMsccSysAcqListBuildTbl[] =
{
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON,                      NAS_MSCC_BuildSysAcqList_SwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_SUCC,        NAS_MSCC_BuildSysAcqList_InitAcqSuccInSwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON_INIT_ACQ_FAIL,        NAS_MSCC_BuildSysAcqList_InitAcqFailInSwitchOn},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_AVAILABLE_TIMER_EXPIRED,        NAS_MSCC_BuildSysAcqList_AvailableTimerExpired},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_LOST,                      NAS_MSCC_BuildSysAcqList_HrpdLost},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_LOST,                       NAS_MSCC_BuildSysAcqList_LteLost},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SLEEP_TIMER_EXPIRED,            NAS_MSCC_BuildSysAcqList_SleepTimerExpired},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_RF_AVAILABLE,               NAS_MSCC_BuildSysAcqList_LteRfAvailable},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_RF_AVAILABLE,              NAS_MSCC_BuildSysAcqList_HrpdRfAvailable},
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SYS_CFG_SET,                    NAS_MSCC_BuildSysAcqList_SysCfgSet},
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, begin */
    {NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_MO_TRIGGER,                          NAS_MSCC_BuildSysAcqList_MoTrigger},
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, end */
};


/*****************************************************************************
  3 函数定义
*****************************************************************************/


VOS_VOID NAS_MSCC_BuildSysAcqList(
    NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_UINT32           enSysAcqScene,
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT32                          i;
    pNasMsccSysAcqListBuildFunc         pfunSysAcqListBuild = VOS_NULL_PTR;

    for (i = 0; i < (sizeof(g_astNasMsccSysAcqListBuildTbl)/sizeof(NAS_MSCC_SYS_ACQ_LIST_BUILD_TBL_STRU)); i++)
    {
        if (enSysAcqScene == g_astNasMsccSysAcqListBuildTbl[i].enSysAcqScene)
        {
            pfunSysAcqListBuild = g_astNasMsccSysAcqListBuildTbl[i].pfunSysAcqListBuild;
            break;
        }
    }

    if (VOS_NULL_PTR != pfunSysAcqListBuild)
    {
        pfunSysAcqListBuild(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);
    }

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_SwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmsLocInfo;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstMmsLocInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* if the MMSS location info values are not valid or GUL mode, should do initial sytem acquire */
    if ((VOS_FALSE                    == pstMmsLocInfo->ucIsLocInfoUsedInSwitchOn)
     || (NAS_MSCC_LC_RAT_COMBINED_GUL == pstMmsLocInfo->enSysAcqMode))
    {
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_1X))
        {
            pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_1X;
            pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
            ucIndex++;
        }

        pstSysAcqListInfo->ucInitialAcqSysNum = ucIndex;

        return;
    }

    /* using last locaiton info to determine the prefered rat */
    enPriSys = NAS_MSCC_GetPrefRatWithLastLocInfo();

    if (NAS_MSCC_LTE_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else
    {
        /* the prior is butt indicate we could not judge the perfered rat,we have to do the initial system acqquire */
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_1X;
        pstSysAcqListInfo->astInitialAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucInitialAcqSysNum = ucIndex;
    }

    return;
}

VOS_VOID NAS_MSCC_BuildSysAcqList_InitAcqSuccInSwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    enPriSys = NAS_MSCC_PRIOR_SYS_BUTT;

    /* use lte location to determine the preferred rat */
    if (VOS_NULL_PTR != pstLteLocInfo)
    {
        enPriSys = NAS_MSCC_GetPrefRatWithLteLocInfo(pstLteLocInfo);
    }

    /* use 1x location to determine the preferred rat */
    if (VOS_NULL_PTR != pst1xLocInfo)
    {
        enPriSys = NAS_MSCC_GetPrefRatWith1xLocInfo(pst1xLocInfo);
    }

    if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;
    }
    else if (NAS_MSCC_LTE_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;
    }
    else
    {
        /* use initial system acquire result could not determine which prefer,should continue
           uset the less prefered rat to do the initial system acquire */

        pstSysAcqListInfo->ucNormalAcqSysNum = 0;

        return;
    }

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_InitAcqFailInSwitchOn(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    /* while initial acquire failed,we directly acquire hrpd, so
       use the same logic in lte lost scene */
    NAS_MSCC_BuildSysAcqList_LteLost(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8       enPriSys;
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    /* using last locaiton info to determine the prefered rat */
    enPriSys = NAS_MSCC_GetPrefRatWithLastLocInfo();

    if (NAS_MSCC_HRPD_PRIOR == enPriSys)
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }
    else
    {
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
        pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
        ucIndex++;

        pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;
    }

    return;
}

VOS_VOID NAS_MSCC_BuildSysAcqList_HrpdLost(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}




VOS_VOID NAS_MSCC_BuildSysAcqList_LteLost(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_SleepTimerExpired(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}


/* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_BuildSysAcqList_MoTrigger
Description     :   The function is used to build system acquire list sleep timer expired
Input parameters:   pst1xLocInfo ---- 1x location info
                    pstLteLocInfo-----lte location info
Output parameters:  pstSysAcqListInfo---system acqurie list info
Return Value    :   VOS_VOID
Modify History:
    1)  Date    :   2015-07-16
        Author  :   y00314741
        Modify content :Create
*****************************************************************************/

VOS_VOID NAS_MSCC_BuildSysAcqList_MoTrigger(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_AvailableTimerExpired(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, end */


VOS_VOID NAS_MSCC_BuildSysAcqList_LteRfAvailable(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}


VOS_VOID NAS_MSCC_BuildSysAcqList_HrpdRfAvailable(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    VOS_UINT8                           ucIndex;

    ucIndex  = 0;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_HRPD;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].ulRatMode   = VOS_RATMODE_LTE;
    pstSysAcqListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    ucIndex++;

    pstSysAcqListInfo->ucNormalAcqSysNum = ucIndex;

    return;
}



VOS_VOID NAS_MSCC_BuildSysAcqList_SysCfgSet(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocInfo,
    NAS_MSCC_LTE_LOC_INFO_STRU                             *pstLteLocInfo,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstSysAcqListInfo
)
{
    NAS_MSCC_BuildSysAcqList_SwitchOn(pst1xLocInfo, pstLteLocInfo, pstSysAcqListInfo);

    return;
}




VOS_UINT32 NAS_MSCC_GetNextNormalAcquireSysInAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo,
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                         *pstNextAcqSysInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        if (NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED == pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus)
        {
            pstNextAcqSysInfo->enAcqStatus = pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus;
            pstNextAcqSysInfo->ulRatMode   = pstAcqSysListInfo->astNormalAcqSysList[ucIndex].ulRatMode;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_GetNextInitialAcquireSysInAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo,
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU                         *pstNextAcqSysInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucInitialAcqSysNum; ucIndex++)
    {
        if (NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED == pstAcqSysListInfo->astInitialAcqSysList[ucIndex].enAcqStatus)
        {
            pstNextAcqSysInfo->enAcqStatus = pstAcqSysListInfo->astInitialAcqSysList[ucIndex].enAcqStatus;
            pstNextAcqSysInfo->ulRatMode   = pstAcqSysListInfo->astInitialAcqSysList[ucIndex].ulRatMode;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MSCC_UpdateAcqRatStatusInNormalAcqSysList(
    VOS_RATMODE_ENUM_UINT32                                 ulRatMode,
    NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8                      enSysAcqStatus,
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        if (ulRatMode == pstAcqSysListInfo->astNormalAcqSysList[ucIndex].ulRatMode)
        {
            pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = enSysAcqStatus;
        }
    }

    return;
}



VOS_VOID NAS_MSCC_ResetAcqRatStatusInNormalAcqSysList(
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                    *pstAcqSysListInfo
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < pstAcqSysListInfo->ucNormalAcqSysNum; ucIndex++)
    {
        pstAcqSysListInfo->astNormalAcqSysList[ucIndex].enAcqStatus = NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED;
    }

    return;
}





NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWithLastLocInfo(VOS_VOID)
{
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo = VOS_NULL_PTR;
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU                          *pstMmssSysAcqCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;

    pstMmssLocationInfo = NAS_MSCC_GetMmssLastLocationInfoAddr();

    /* Get the MMSS Cfg Info Address */
    pstMmssSysAcqCfgInfo = NAS_MSCC_GetMmssSysAcqCfgInfoAddr();

    /* Default value is invalid RAT */
    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    /* Check if CDMA 1x Location Info is preferred. If TRUE, use the MCC, SID and NID values to find the preferred RAT in MSPL */
    if ((VOS_TRUE == pstMmssSysAcqCfgInfo->ucIs1xLocInfoPrefThanLte)
     && (VOS_TRUE == pstMmssLocationInfo->ucCdma1xActiveFlag))
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWith1xLocInfo(&(pstMmssLocationInfo->st1xLocationInfo));
    }
    else if (VOS_TRUE == pstMmssLocationInfo->ucLteActiveFlag)
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWithLteLocInfo(&pstMmssLocationInfo->stLteLocationInfo);
    }
    else if (VOS_TRUE == pstMmssLocationInfo->ucCdma1xActiveFlag)
    {
        enPreferredRat = NAS_MSCC_GetPrefRatWith1xLocInfo(&(pstMmssLocationInfo->st1xLocationInfo));
    }
    else /* When HRPD and LTE System priority is not found */
    {
        enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;
    }

    return enPreferredRat;
}



NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWith1xLocInfo(
    NAS_MSCC_1X_LOC_INFO_STRU                              *pst1xLocationInfo
)
{
    NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU                  st1xSysInfo;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList = VOS_NULL_PTR;

    pstMsplList = (NAS_MSCC_MSPL_SYS_LIST_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                   sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstMsplList)
    {
        return NAS_MSCC_PRIOR_SYS_BUTT;
    }

    /* Clear the Structure variables */
    PS_MEM_SET(&st1xSysInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_1X_INPUT_INFO_STRU));
    PS_MEM_SET(pstMsplList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    st1xSysInfo.ulMcc                  = pst1xLocationInfo->ulMcc;
    st1xSysInfo.ulMnc                  = pst1xLocationInfo->ulMnc;
    st1xSysInfo.ucIsMccValid           = VOS_TRUE;
    st1xSysInfo.ucIsMncValid           = VOS_TRUE;
    st1xSysInfo.usSid                  = pst1xLocationInfo->usSid;
    st1xSysInfo.usNid                  = pst1xLocationInfo->usNid;

    st1xSysInfo.enPriClassCdma20001x   = pst1xLocationInfo->en1xPrioClass;
    st1xSysInfo.enPriClassCdma2000Ai   = pst1xLocationInfo->enAIPrioClass;

    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    if (VOS_TRUE == NAS_MSCC_GetMsplSysListBy1xLoc(&st1xSysInfo, pstMsplList))
    {
        if (VOS_TRUE == NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(pstMsplList))
        {
            enPreferredRat = NAS_MSCC_LTE_PRIOR;
        }

        /* If 3GPP or LTE is not the more preferred RAT, return HRPD priority */
        else
        {
            enPreferredRat = NAS_MSCC_HRPD_PRIOR;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplList);

    return enPreferredRat;
}




NAS_MSCC_PRIOR_SYS_ENUM_UINT8  NAS_MSCC_GetPrefRatWithLteLocInfo(
    NAS_MSCC_LTE_LOC_INFO_STRU         *pstLteLocInfo
)
{
    NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU                st3gppLocationInfo;
    NAS_MSCC_PRIOR_SYS_ENUM_UINT8                           enPreferredRat;
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstMsplList = VOS_NULL_PTR;

    pstMsplList = (NAS_MSCC_MSPL_SYS_LIST_INFO_STRU *)PS_MEM_ALLOC(UEPS_PID_MSCC,
                                                                   sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    if (VOS_NULL_PTR == pstMsplList)
    {
        return NAS_MSCC_PRIOR_SYS_BUTT;
    }

    /* Clear the Structure variables */
    PS_MEM_SET(&st3gppLocationInfo, 0x00 , sizeof(NAS_MSCC_MMSS_MATCH_3GPP_INPUT_INFO_STRU));
    PS_MEM_SET(pstMsplList, 0x00, sizeof(NAS_MSCC_MSPL_SYS_LIST_INFO_STRU));

    /* Initialize the input structure */
    st3gppLocationInfo.stPlmnId.ulMcc = pstLteLocInfo->ulMcc;
    st3gppLocationInfo.stPlmnId.ulMnc = pstLteLocInfo->ulMnc;
    st3gppLocationInfo.enPriClass     = pstLteLocInfo->enPrioClass;
    st3gppLocationInfo.enSysRat       = VOS_RATMODE_LTE;

    enPreferredRat = NAS_MSCC_PRIOR_SYS_BUTT;

    if (VOS_TRUE == NAS_MSCC_GetHigherPriMsplSysListThan3gpp(&st3gppLocationInfo, pstMsplList))
    {
        if (VOS_TRUE == NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(pstMsplList))
        {
            enPreferredRat = NAS_MSCC_LTE_PRIOR;
        }

        /* If 3GPP or LTE is not the more preferred RAT, return HRPD priority */
        else
        {
            enPreferredRat = NAS_MSCC_HRPD_PRIOR;
        }
    }

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsplList);

    return enPreferredRat;

}

VOS_UINT8  NAS_MSCC_IsLteMorePreferredThanHrpdInMspl(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstMsplSysList
)
{
    VOS_UINT8                           i;

    /* Loop through the MSPL Info list. If LTE or 3GPP AI occurs first in the List, then return LTE is preferred */
    for (i = 0; i < pstMsplSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI == pstMsplSysList->astSysList[i].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstMsplSysList->astSysList[i].enSysType))
        {
            /* If the system type is HRPD or CDMA2000Ai, then return VOS_FALSE */
            return VOS_FALSE;
        }

        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstMsplSysList->astSysList[i].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE == pstMsplSysList->astSysList[i].enSysType))
        {
            /* If the system type is LTE or 3GPPAi, then return VOS_TRUE */
            return VOS_TRUE;
        }

    }

    /* here in mlpl sys list hrpd and lte both not exist,we consider lte more prefered */
    return VOS_TRUE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_GetDestBsrSysTypeInSysList
Description     :   get higher pri systype than 3gpp in MSPL
Input parameters:   enCurSysRat                             the current camped sys rat
                    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU       *pstOutSysList
Output parameters:  None
Return Value    :   NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8

Modify History:
    1)  Date    :   2015-4-3
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysTypeInSysList(
    VOS_RATMODE_ENUM_UINT32                                 enCurSysRat,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType;
    VOS_UINT8                                               ucLoop;

    enSysType = NAS_MSCC_MLPL_MSPL_SYS_TYPE_BUTT;

    for (ucLoop = 0; ucLoop < pstOutSysList->ucSysCount; ucLoop++)
    {
        if ((VOS_RATMODE_LTE                            == enCurSysRat)
         && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstOutSysList->astSysList[ucLoop].enSysType)
          || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enSysType =  pstOutSysList->astSysList[ucLoop].enSysType;
            break;
        }

        if ((VOS_RATMODE_HRPD                    == enCurSysRat)
        && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstOutSysList->astSysList[ucLoop].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enSysType =  pstOutSysList->astSysList[ucLoop].enSysType;
            break;
        }
    }

    return enSysType;
}


NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClassInSysList(
    VOS_RATMODE_ENUM_UINT32                                 enCurSysRat,
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU                       *pstOutSysList
)
{
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enPriClass;
    VOS_UINT8                                               ucLoop;

    enPriClass = NAS_MSCC_MSPL_SYS_PRI_CLASS_BUTT;

    for (ucLoop = 0; ucLoop < pstOutSysList->ucSysCount; ucLoop++)
    {
        if ((VOS_RATMODE_LTE                            == enCurSysRat)
         && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstOutSysList->astSysList[ucLoop].enSysType)
          || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enPriClass =  pstOutSysList->astSysList[ucLoop].enPriClass;
            break;
        }

        if ((VOS_RATMODE_HRPD                    == enCurSysRat)
        && ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstOutSysList->astSysList[ucLoop].enSysType)
         || (NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstOutSysList->astSysList[ucLoop].enSysType)))
        {
            enPriClass =  pstOutSysList->astSysList[ucLoop].enPriClass;
            break;
        }
    }

    return enPriClass;
}


/*****************************************************************************
Function Name   :   NAS_MSCC_IsLteSysTypeExistInSysList
Description     :   The function is used to find is Lte Sys Type exist in SysList.
Input parameters:   NAS_MSCC_MSPL_SYS_LIST_INFO_STRU: System List.
Output parameters:  None.
Return Value    :   True - exist.
                    False - not exist.
Modify History:
    1)  Date    :   2015-04-16
        Author  :   t00323010
        Modify content :    Create
*****************************************************************************/
VOS_UINT8  NAS_MSCC_IsLteSysTypeExistInSysList(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstSysList
)
{
    VOS_UINT8                           i;

    for (i = 0; i < pstSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_3GPP_AI == pstSysList->astSysList[i].enSysType)
          ||(NAS_MSCC_MLPL_MSPL_SYS_TYPE_LTE     == pstSysList->astSysList[i].enSysType))
        {
            return VOS_TRUE;
        }

    }

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :   NAS_MSCC_IsHrpdSysTypeExistInSysList
Description     :   The function is used to find is Hrpd Sys Type exist in SysList.
Input parameters:   NAS_MSCC_MSPL_SYS_LIST_INFO_STRU: System List.
Output parameters:  None.
Return Value    :   True - exist.
                    False - not exist.
Modify History:
    1)  Date    :   2015-04-16
        Author  :   t00323010
        Modify content :    Create
*****************************************************************************/
VOS_UINT8  NAS_MSCC_IsHrpdSysTypeExistInSysList(
    NAS_MSCC_MSPL_SYS_LIST_INFO_STRU   *pstSysList
)
{
    VOS_UINT8                           i;

    for (i = 0; i < pstSysList->ucSysCount; i++)
    {
        if ((NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_AI   == pstSysList->astSysList[i].enSysType)
          ||(NAS_MSCC_MLPL_MSPL_SYS_TYPE_CDMA2000_HRPD == pstSysList->astSysList[i].enSysType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_VOID  NAS_MSCC_ConvertSysAcqSceneToBuildSysAcqListScene(
    NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_UINT32          *penBuildSysAcqListScene
)
{
    switch (enSysAcqScene)
    {
        case NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SWITCH_ON;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_AVAILABLE_TIMER_EXPIRED;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_LOST;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_LOST;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SLEEP_TIMER_EXPIRED;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_SYS_CFG_SET;
            break;


        case NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_LTE_RF_AVAILABLE;
            break;

        case NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_HRPD_RF_AVAILABLE;
            break;

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, begin */
        case NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_MO_TRIGGER;
            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, end */

        default:

            *penBuildSysAcqListScene = NAS_MSCC_BUILD_SYS_ACQ_LIST_SCENE_ENUM_BUTT;
            break;
    }

}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




