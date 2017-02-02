/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcMsgPrioCompare.c
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��9��27��
  ����޸�   :
  ��������   : NasMmcMsgCompare.h��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��9��27��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "NasComm.h"
/* ɾ��ExtAppMmcInterface.h*/
#include  "MmcMmInterface.h"
#include  "MmcGmmInterface.h"
#include  "NasMmcSndInternalMsg.h"
#include  "UsimPsInterface.h"
#include  "NasMmcMsgPrioCompare.h"
#include  "NasMmcFsmSyscfg.h"
#include  "NasMmcFsmPlmnSelectionTbl.h"
#include  "NasMmcFsmPLmnListTbl.h"
#include  "NasMmcFsmBgPlmnSearchTbl.h"
#include  "NasMmcFsmAnyCellSearchTbl.h"
#include  "NasMmlCtx.h"
#include  "NasMmcCtx.h"
#include  "NasMmlLib.h"
#include  "siappstk.h"

#include "MsccMmcInterface.h"

#include "PsRrmInterface.h"

#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_MSG_PRIO_COMPARE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysCcoTbl
 ȫ�ֱ���˵��  : MMC CCO ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/

NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCcoTbl[] =
{
    /* InterSys Cco�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCco),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysHoTbl
 ȫ�ֱ���˵��  : MMC HO ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysHoTbl[] =
{

    /* InterSys HO�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysHo),

};


NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysCellReselTbl[] =
{
    /* InterSys cellresel�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel),


    /* InterSys cellresel�������յ�syscfg�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ�DETACH�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareDetachReqPrioWithInterSysCellResel),

    /* InterSys cellresel�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel),
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithInterSysOosTbl
 ȫ�ֱ���˵��  : MMC OOS ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithInterSysOosTbl[] =
{

    /* OOS�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithInterSysOos),


    /* OOS�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithInterSysOos),

    /* OOS�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),

    /* OOS�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos),


    /* OOS�������յ�syscfg�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithInterSysOos),


    /* OOS�������յ�TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithInterSysOos),

    /* OOS�������յ�TI_NAS_MMC_AVAILABLE_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_AVAILABLE_TIMER),
                             NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* OOS�������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */


    /* OOS�������յ�TI_NAS_MMC_FORBID_LA_TIMER_LEN�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_FORBID_LA_TIMER_LEN),
                             NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos),

    /* OOS�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithInterSysOos),
};


NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnSelectionTbl[] =
{

    /* PlmnSelection�������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection),
#endif

    /* PlmnSelection�������յ�SYSCFG�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* PlmnSelection�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection),

#if (FEATURE_ON == FEATURE_LTE)
    /* PlmnSelection�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection),

    /* PlmnSelection�������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection),

#endif

    /* PlmnSelection�������յ��û�MMCMM_PLMN_SEARCH_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
    /* PlmnSelection�������յ�TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */

};


NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithAnyCellTbl[] =
{
    /* anycell�������յ�SYSCFG�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection),

    /* anycell �������յ��ػ��������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnSelection),

    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnSelection),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnSelection),

    /* anycell�������յ��û���ѡ�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnSelection),

    /* anycell�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                            NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* anycell�������յ��û�ָ�������������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection),

    /* anycell�������յ��û�MMCMM_CM_SERVICE_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CM_SERVICE_IND),
                             NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_CSFB_ABORT_IND),
                             NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch),
#endif

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch),
#endif

    /* anycell�������յ��û�LIST�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection),

    /* anycell�������յ��û�MMCMM_PLMN_SEARCH_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MM, MMCMM_PLMN_SEARCH_IND),
                             NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
    /* PlmnSelection�������յ�TI_NAS_MMC_CONTROL_FIRST_SEARCH_PLMN_TIMER��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch),
    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioCompareWithSysCfgTbl
 ȫ�ֱ���˵��  : MMC syscfg ״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithSysCfgTbl[] =
{

    /* SYSCFG�������յ�MMC����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_MMC_UNIVERAL_MSG_ID,
                             NAS_MMC_CompareMmcMsgPrioWithSysCfg),

};
NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPlmnListTbl[] =
{

    /* �ڲ�list�����ʱ�û�list�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithPlmnList),

    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithPlmnList),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithPlmnList),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_SYS_CFG_SET_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithPlmnList),


    /* �ڲ�list�����������յ�MSCC_MMC_PLMN_SPECIAL_REQ_STRU����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithPlmnList),


    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_SPECIAL_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithPlmnList),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_DETACH_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithPlmnList),

    /* list�����������յ�WAS RRMM_SUSPEND_IND ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

    /* list�����������յ�GAS RRMM_SUSPEND_IND ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithPlmnList),

#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithPlmnList),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* LIST�����������յ�LMM�Ĺ���ָʾ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList),

    /* LIST�����������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList),


#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* OOS�������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

};


NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithBgSearchTbl[] =
{

    /* BG�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePoweroffPrioWithBgSearch),

    /* PlmnSelection�������յ�PowerSave�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_SAVE_REQ),
                             NAS_MMC_ComparePowerSavePrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_ACQ_REQ),
                             NAS_MMC_CompareAcqReqPrioWithBgSearch),

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_REG_REQ),
                             NAS_MMC_CompareRegReqPrioWithBgSearch),

    /* BG�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_LIST_REQ),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* BG�����������յ�TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PERIOD_TRYING_USER_PLMN_LIST),
                             NAS_MMC_CompareUserPlmnListPrioWithBgSearch),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
    /* BG�ѹ������յ�TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER�����������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER),
                             NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch),

    /* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

    /* BG�����������յ�ID_MSCC_MMC_PLMN_SPECIAL_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_SPECIAL_REQ),
                             NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch),


    /* BG�����������յ�ID_MSCC_MMC_SYS_CFG_SET_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SYS_CFG_SET_REQ),
                             NAS_MMC_CompareSysCfgSetPrioWithBgSearch),

    /* BG�����������յ�MSCC_MMC_PLMN_SPECIAL_REQ_STRU����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_PLMN_USER_RESEL_REQ),
                             NAS_MMC_CompareUserReselPrioWithBgSearch),

    /* BG�����������յ�STK_NAS_STEERING_OF_ROAMING_IND����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_STK_PID, STK_NAS_STEERING_OF_ROAMING_IND),
                             NAS_MMC_CompareStkRoamingIndPrioWithBgSearch),

    /* BG�����������յ�PS_USIM_REFRESH_IND����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(MAPS_PIH_PID, USIMM_STKREFRESH_IND),
                             NAS_MMC_CompareUsimRefreshPrioWithBgSearch),


    /* BG�����������յ�ID_MSCC_MMC_UPDATE_UPLMN_NTF����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_UPDATE_UPLMN_NTF),
                             NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch),


    /* BG�����������յ��������յ������(WAS)�ϱ���RRMM_SUSPEND_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_WRR, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),


    /* BG�����������յ��������յ������(GAS)�ϱ���RRMM_SUSPEND_IND�������Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_GAS, RRMM_SUSPEND_IND),
                             NAS_MMC_CompareSuspendIndPrioWithBgSearch),

    /* �ڲ�list�����������յ�ID_MSCC_MMC_PLMN_LIST_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_DETACH_REQ),
                             NAS_MMC_CompareUserDetachReqPrioWithBgSearch),


#if (FEATURE_ON == FEATURE_DSDS)
     NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_SRV_ACQ_REQ),
                             NAS_MMC_CompareSrvAcqReqPrioWithBgSearch),
#endif

#if (FEATURE_ON == FEATURE_LTE)

    /* BG�����������յ��������յ�LMM�Ĺ���ָʾ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SUSPEND_IND ),
                             NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch),

    /* BG�����������յ�ID_LMM_MMC_SERVICE_RESULT_IND��Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(PS_PID_MM, ID_LMM_MMC_SERVICE_RESULT_IND),
                             NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch),

#endif

    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND),
                             NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch),



};



NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithGetGeoTbl[] =
{
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_MSCC, ID_MSCC_MMC_POWER_OFF_REQ),
                             NAS_MMC_ComparePowerOffPrioWithGetGeo),
};


NAS_MMC_MSG_COMPARE_STRU g_astMmcMsgPrioCompareWithPowerOffTbl[] =
{

    /* BG�����������յ�ID_MSCC_MMC_POWER_OFF_REQ����Ϣ���ȼ��Ƚ� */
    NAS_MMC_COMPARE_TBL_ITEM(NAS_BuildEventType(UEPS_PID_RRM, ID_RRM_PS_STATUS_IND),
                             NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff)
};



/*****************************************************************************
 ȫ�ֱ�����    : g_astMmcMsgPrioHighPlmnSearchCompareTbl
 ȫ�ֱ���˵��  : MMC״̬���ȽϺ�����
 1.��    ��   : 2011��9��28��
   ��    ��   : zhoujun 40661
   �޸�����   : �½�
*****************************************************************************/
NAS_MMC_FSM_MSG_COMPARE_STRU g_astMmcMsgCompareTbl[] =
{
     /* CCO״̬���ȽϺ�����*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CCO,
                     g_astMmcMsgPrioCompareWithInterSysCcoTbl),

    /* HO״̬���ȽϺ�����*/
    NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_HO,
                      g_astMmcMsgPrioCompareWithInterSysHoTbl),


     /* cellresel״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_CELLRESEL,
                       g_astMmcMsgPrioCompareWithInterSysCellReselTbl),

     /* OOS״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_INTER_SYS_OOS,
                       g_astMmcMsgPrioCompareWithInterSysOosTbl),


     /* PLMN Selection״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_SELECTION,
                       g_astMmcMsgPrioCompareWithPlmnSelectionTbl),


     /* anycell״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_ANYCELL_SEARCH,
                       g_astMmcMsgPrioCompareWithAnyCellTbl),

     /* SYSCFG״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_SYSCFG,
                       g_astMmcMsgPrioCompareWithSysCfgTbl),


     /* PLMN LIST״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_PLMN_LIST,
                       g_astMmcMsgPrioCompareWithPlmnListTbl),

     /* BG����״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_BG_PLMN_SEARCH,
                       g_astMmcMsgPrioCompareWithBgSearchTbl),

     /* GET GEO״̬���ȽϺ�����*/
     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_GET_GEO,
                       g_astMmcMsgPrioCompareWithGetGeoTbl),

     NAS_MMC_FSM_COMPARE_TBL_ITEM(NAS_MMC_FSM_POWER_OFF,
                        g_astMmcMsgPrioCompareWithPowerOffTbl)

};

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsTrigerDisableLte_MoDetach(
    MSCC_MMC_DETACH_REQ_STRU           *pstDetachReq
)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;
    NAS_MML_LTE_UE_OPERATION_MODE_ENUM_UINT8                enLUeMode;

    /* ��������ʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return VOS_FALSE;
    }

    /* ��ȡLTE������״̬ */
    enLCapabilityStatus = NAS_MML_GetLteCapabilityStatus();

    /* ����Ѿ�disable ����Ҫ��disable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS == enLCapabilityStatus)
     || (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS == enLCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* ƽ̨��֧��LTEʱ����Ҫdisable LTE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        return VOS_FALSE;
    }

    /* �����LTE onlyģʽ����Ҫdisable LTE */
    if (VOS_TRUE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
    {
        return VOS_FALSE;
    }

    /* ��ȡLTE��UEģʽ */
    enLUeMode = NAS_MML_GetLteUeOperationMode();

    /* UEģʽΪCS PS mode1��CS PS mode2��Ҫdisable LTE */
    if ((NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_2 == enLUeMode)
     || (NAS_MML_LTE_UE_OPERATION_MODE_CS_PS_1 == enLUeMode))
    {
        /* ���detachΪ�û������������仯�����ģ��Ұ���PS detach���ͣ�����Ҫdisable LTE */
        if (VOS_TRUE == NAS_MMC_IsDetachReqestDisableLte(pstDetachReq->enDetachType,
                                                         pstDetachReq->enDetachReason))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysCco
 ��������  : ��MMC�յ�����Ϣ��CCO״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCco(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysHo
 ��������  : ��MMC�յ�����Ϣ��HO״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysHo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareDetachReqPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_DETACH_REQ_STRU             *pstTafDetachReq = VOS_NULL_PTR;

    pstTafDetachReq = (MSCC_MMC_DETACH_REQ_STRU *)pstMsg;

    /* ps���detach�ᴥ��disable LTE,��Ҫ��� */
    if ((NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI == pstTafDetachReq->enDetachType)
     || (NAS_MSCC_PIF_DETACH_TYPE_GPRS    == pstTafDetachReq->enDetachType))
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType     = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel
 ��������  : ��MMC�յ�����Ϣ��cell resel״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithInterSysCellResel(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithInterSysOos
 ��������  : ���ػ���Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithInterSysOos
 ��������  : ���û���ѡ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithInterSysOos
 ��������  : ���û�LIST������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos
 ��������  : ���û�SPEC������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithInterSysOos
 ��������  : ��SYSCFG������Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 ��������  : ��available timer��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos
 ��������  : ��forbid la timer��ʱ��Ϣ��OOS״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiForbidLaTimerExpiredPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithInterSysOos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg = VOS_NULL_PTR;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* ��������ֱ�Ӷ�������Ϣ,��������������� */
    if (MM_EMERGENCY_CALL_TRUE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType     = NAS_MMC_ABORT_FSM_IMMEDIATELY;

        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithPlmnSelection
 ��������  : ���ػ���Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��Plmn selection ״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��31��
   ��    ��   : c00318887
   �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePlmnSearchPhaseOneTotalTimePrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-8-31, end */

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch
 ��������  : ��available timer��ʱ��Ϣ��AnyCell״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimePrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */


#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_SRV_ACQ_REQ_STRU           *pstSrvAcqReq = VOS_NULL_PTR;

    pstSrvAcqReq    = (MSCC_MMC_SRV_ACQ_REQ_STRU*)pstMsg;

    /* ����ǽ���������ֱ�Ӵ�ϣ��ǽ��������򻺴棬������״̬���˳�����
       �������״̬���˳���������������ֱ�ӻظ�ҵ�񴥷������ɹ������
       ������ٴδ���ҵ�񴥷��������������� */
    if (NAS_MSCC_PIF_SRV_TYPE_CS_MO_EMERGENCY_CALL == pstSrvAcqReq->enSrvType)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}




VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 NAS_MMC_CompareSrvAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

#endif


VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;
    VOS_UINT32                          ulNeedHighPrioRat;

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* �жϵ�ǰSYSCFG�����Ƿ�ᴥ��SYSCFG���� */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    /* ���NV���ҵ�ǰδפ����������ȼ����뼼����PLMN�ϣ���Ҫ��� */
    ulNeedHighPrioRat   = NAS_MMC_IsRatPrioChangeTriggerPlmnSrch( NAS_MML_GetMsPrioRatList(), 
                                    &((MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg)->stRatPrioList);

    if ( (VOS_TRUE == NAS_MML_GetSyscfgTriHighRatSrchFlg())
      && (VOS_FALSE == ulNeedPlmnSearch)
      && (VOS_TRUE == ulNeedHighPrioRat) )
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* �Բ���Ҫ���������������ж� */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND == ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))

    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#if   (FEATURE_ON == FEATURE_LTE)

    /* ���ڲ���Ҫ���������,ֱ����״̬���д��� */
    if ( ( VOS_FALSE == ulNeedPlmnSearch )
      && ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

#endif

    /* �����������Ҫ��ϵ�ǰ״̬�� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithPlmnSelection
 ��������  : ���û���ѡ��Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection
 ��������  : ���û�LIST������Ϣ������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MSCC_MMC_PLMN_SPECIAL_REQ_STRU      *pstUserPlmnInfo;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulRlt;

    ulCurrState         = NAS_MMC_GetFsmTopState();
    pstUserPlmnInfo     = (MSCC_MMC_PLMN_SPECIAL_REQ_STRU*)pstMsg;

    *penAbortType       = NAS_MMC_ABORT_BUTT;

    /* ����Ҫ�ڵȴ�ע�����������ͷ�,��Ҫ����״̬�� */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND ==  ulCurrState ) )
    {
        /* ��ȡ��ǰפ��������Ϣ,�����յ�ϵͳ��Ϣ��ʱ��ȡ�϶�û������ */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* ��Ҫ�ж�PLMN ID�ͽ�������Ƿ���ͬ,��ͬ��ֱ�ӽ���״̬�� */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* ����ڵȴ�ϵͳ��Ϣ����Ҫ���л��� */
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND ==  ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND ==  ulCurrState ))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if ( ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState )
      || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {

        /* ��ȡ��ǰפ��������Ϣ,�����յ�ϵͳ��Ϣ��ʱ��ȡ�϶�û������ */
        pstCampPlmnInfo = NAS_MML_GetCurrCampPlmnInfo();

        ulRlt           = NAS_MML_CompareBcchPlmnwithSimPlmn(&(pstCampPlmnInfo->stLai.stPlmnId),
                                               (NAS_MML_PLMN_ID_STRU*)(&(pstUserPlmnInfo->stPlmnId)));

        /* ��Ҫ�ж�PLMN ID�ͽ�������Ƿ���ͬ,��ͬ��ֱ�ӽ���״̬�� */
        if ( ( VOS_TRUE == ulRlt)
          && ( pstCampPlmnInfo->enNetRatType ==  pstUserPlmnInfo->enAccessMode ))
        {
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
        }
    }

    /* ����ڵȴ�ϵͳ��Ϣ����Ҫ���л��� */
    if ( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND ==  ulCurrState )
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#endif

    /* �����������Ҫ��� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    MMCMM_CM_SERVICE_IND_STRU          *pstServiceIndMsg;

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;
    /* ��������ֱ�Ӷ�������Ϣ */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* �����͹���״̬ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��L���������״̬���L����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
      || (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE == ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* �����͹���״̬ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ( ( NAS_MMC_FSM_PLMN_SELECTION == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
       || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* ��L�Ĺ���ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ==  ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
         return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
#endif


VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulCurrState;
    VOS_UINT8                           ucIsLteSearched;

    ulCurrState               = NAS_MMC_GetFsmTopState();
    *penAbortType             = NAS_MMC_ABORT_BUTT;
    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ucIsLteSearched           = NAS_MMC_IsSpecRatSearched_PlmnSelection(NAS_MML_NET_RAT_TYPE_LTE);

    if ((NAS_MMC_FSM_PLMN_SELECTION       != NAS_MMC_GetCurrFsmId())
     || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ��������LTE�����Ѿ�����LTEʱ����Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState )
     || (VOS_TRUE                                            == ucIsLteSearched ))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* GU�����ɹ��ȴ�ϵͳ��Ϣ���ߵȴ�ע����ʱ���������״̬�� */
    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND    == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND       == ulCurrState)
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND   == ulCurrState))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}


VOS_UINT32 NAS_MMC_ComparePlmnSearchIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_PLMN_SEARCH_IND_STRU         *pstPlmnSearchInd;
    VOS_UINT32                          ulIsUsimStausValid;

    *penAbortType             = NAS_MMC_ABORT_BUTT;

    pstPlmnSearchInd          = (MMCMM_PLMN_SEARCH_IND_STRU*)pstMsg;
    ulIsUsimStausValid        = NAS_MML_IsUsimStausValid();

    if ( (NAS_MMC_FSM_ANYCELL_SEARCH       != NAS_MMC_GetCurrFsmId())
      || (MM_MMC_PLMN_SEARCH_TYPE_CSFB_END != pstPlmnSearchInd->enPlmnSearchType)
      || (VOS_FALSE                        == ulIsUsimStausValid))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
     return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareMmcMsgPrioWithSysCfg
 ��������  : ��MMC�յ�����Ϣ��SYSCFG״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareMmcMsgPrioWithSysCfg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* Ĭ�Ϸ�����Ϣ��Ҫ���� */
    *penAbortType = NAS_MMC_ABORT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePowerOffPrioWithPlmnList
 ��������  : ���ػ���Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareRegReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareSysCfgSetPrioWithPlmnList
 ��������  : ��SYSCFG������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithPlmnList
 ��������  : ���û���ѡ��Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserReselPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList
 ��������  : ���û�ָ��������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithPlmnList
 ��������  : ���û�LIST������Ϣ��LIST����״̬�������ȼ����бȽ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserPlmnListPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
}


VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    *penAbortType    = NAS_MMC_ABORT_BUTT;


    enRat = NAS_MML_NET_RAT_TYPE_BUTT;

    /* �жϵ�ǰ�û���detach�Ƿ�ᴥ��disable LTE */
    ulTrigerDisableLte      = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);

    ulCurrState             = NAS_MMC_GetFsmTopState();

    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* ��ǰ��L�µ��ڲ�LIST�����������յ��û�detach��Ϣ,��CS/PS mode2����Ҫdisable
           LTE,��ʱ��Ҫ���L�µ��ڲ�LIST����,�����û���detach���� */
        if (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState)
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* ��ȡ�¸���Ҫ�����Ľ��뼼�� */
        (VOS_VOID)NAS_MMC_GetNextSearchingRat_PlmnList(&enRat);

        /* ��GU���ڲ��б�����ʱ,�������RRMM_NOT_CAMP_ON_IND��Ϣ�Գ�,����GU��L
           ����������û�detach������Ҫdisable LTE,��ʱ���ڼ�����L���ڲ�LIST����
           �˳�LIST����״̬���������detach */
        if (((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SUSPEND_CNF == ulCurrState)
          || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SUSPEND_CNF == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE    == enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    *penAbortType    = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* LIST������������ϵͳָʾ�Գ�,RRC��ظ�List_REJ,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�List_REJ���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_STOP_CNF    ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }


    /* �ڵ�ϵͳ��Ϣʱ��ֱ�Ӵ��LIST����״̬����������������²��ظ�SUSPEDN RSP,GAS��λ */
    if ( ( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_GAS_SYS_INFO_IND ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_WAS_SYS_INFO_IND ==  ulCurrState )))
    {
        *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;


    /* NO RFʱ����LIST�������ȴ�LIST�����ظ�ʱ,RRM֪ͨ��Դ����,LIST������ɺ�֪ͨ������,���ܴ����ظ�ȥע��Lģ,��Ҫ��
       �ȴ�LIST�����ظ��յ���Դ���ò����� */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState)
#if (FEATURE_ON == FEATURE_LTE)
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState)
#endif
       ))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* NO RF�����LIST����״̬��,�������RRM֪ͨ��Դ����,��Ҫ��LIST
       �������̽����󴥷�һ������,��˸���Ϣ��Ҫ����,��LIST����״̬
       ���˳�����һ�� */
    *penAbortType   = NAS_MMC_MSG_COMPARE_PRIO_RSLT_BUTT;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}



/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList
 ��������  : ��TI_NAS_MMC_PLMN_SEARCH_PHASE_ONE_TOTAL_TIMER��ʱ��Ϣ��PLMN LIST״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */




VOS_UINT32 NAS_MMC_CompareCmServiceIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    MMCMM_CM_SERVICE_IND_STRU                              *pstServiceIndMsg;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    VOS_UINT32                                              ulCurrState;

    ulCurrState             =  NAS_MMC_GetFsmTopState();
#endif

    pstServiceIndMsg        = (MMCMM_CM_SERVICE_IND_STRU*)pstMsg;
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    /* ��������ֱ�Ӷ�������Ϣ */
    if (MM_EMERGENCY_CALL_FALSE == pstServiceIndMsg->ulEmcFlg)
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* GU����״̬����һ��Ҫ�����Ľ��뼼��ΪL�һ���δanycell��������GU���뼼��ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (enRat == NAS_MML_NET_RAT_TYPE_LTE)
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF  ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFBʱ��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF == ulCurrState))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
#endif

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}




#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_CompareCsfbAbortIndPrioWithAnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState   = NAS_MMC_GetFsmTopState();
    *penAbortType = NAS_MMC_ABORT_BUTT;

    /* GU����״̬����һ��Ҫ�����Ľ��뼼��ΪL�һ���δanycell��������GU���뼼��ʱ��Ҫ��ϵ�ǰ״̬�� */
    if ((NAS_MMC_FSM_ANYCELL_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )
      || (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF      ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    /* CSFBʱ��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF == ulCurrState)
    {
        *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState     = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* LIST������������ϵͳָʾ�Գ�,LMM��ظ�List_REJ,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�List_REJ���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_STOP_CNF    ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }


    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if (( NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
       || ( NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}



VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB������ʱ��L�����ظ�״̬���Lע����״̬��������ͷ�״̬��Ҫ��ϵ�ǰ״̬��  */
    
    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_FSM_PLMN_LIST == NAS_MMC_GetCurrFsmId())
          && ((NAS_MMC_PLMN_LIST_STA_WAIT_LMM_PLMN_SEARCH_CNF   == ulCurrState)
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_CONN_REL_IND      == ulCurrState )
           || (NAS_MMC_PLMN_LIST_STA_WAIT_EPS_REG_IND           == ulCurrState )))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}
VOS_UINT32 NAS_MMC_CompareLmmServiceResultIndPrioWithPlmnSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
   *penAbortType         = NAS_MMC_ABORT_BUTT;

    if (NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* CSFB������ʱ��Lע�����������ͷ�״̬��csps mode1 ��L��vplmn��Lע�����������ͷ�ʱ��Ҫ��ϵ�ǰ״̬�� */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState)
         || ( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE == ulCurrState))
        {
           *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if (VOS_TRUE == NAS_MML_IsCsfbServiceStatusExist())
    {
        if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState)
         || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState))
        {
            *penAbortType   = NAS_MMC_ABORT_FSM_IMMEDIATELY;
             return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }


    if ((NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
     || (NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE == ulCurrState ))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_ComparePoweroffPrioWithBgSearch
 ��������  : ���ػ���Ϣ���û���������״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ComparePoweroffPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* �ػ���Ϣ�����ӳ��˳� */
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
VOS_UINT32 NAS_MMC_ComparePowerSavePrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareAcqReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareRegReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareSysCfgSetPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulNeedPlmnSearch;

    /* �жϵ�ǰSYSCFG�����Ƿ�ᴥ��SYSCFG���� */
    ulNeedPlmnSearch    = NAS_MMC_IsPlmnSelectionNeeded_SysCfg( (MSCC_MMC_SYS_CFG_SET_REQ_STRU *)pstMsg );

    ulCurrState         = NAS_MMC_GetFsmTopState();

    /* �Բ���Ҫ���������������ж� */
    if  ( ( VOS_FALSE == ulNeedPlmnSearch )
       && ( ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND == ulCurrState )
#if (FEATURE_ON == FEATURE_LTE)
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState )
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND == ulCurrState )
#endif
         || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND == ulCurrState )))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������Ҫ��ϵ�ǰ״̬�� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserReselPrioWithBgSearch
 ��������  : ��user resel��ѡ��Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��9��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_CompareUserReselPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


VOS_UINT32 NAS_MMC_CompareStkRoamingIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    /* BG����״̬��������ʱ,����Ϣ�Ȼ���,�˳�״̬������ */
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}
VOS_UINT32 NAS_MMC_CompareUsimRefreshPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          i;
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_STKREFRESH_IND_STRU          *pstUsimRefreshInd = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    NAS_MML_SIM_USERPLMN_INFO_STRU      *pstUserPlmnList = VOS_NULL_PTR;
    NAS_MML_SIM_OPERPLMN_INFO_STRU      *pstOperPlmnList = VOS_NULL_PTR;
    VOS_UINT8                            ucIsUoplmnExist;

    pstUsimRefreshInd = (USIMM_STKREFRESH_IND_STRU *)pstMsg;

    if (USIMM_REFRESH_FILE_LIST != pstUsimRefreshInd->enRefreshType)
    {
        /* refresh��Ϣָʾ�����ļ��������ݲ������� */
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ��ȡUOPLMN */
    pstUserPlmnList   = NAS_MML_GetSimUserPlmnList();
    pstOperPlmnList   = NAS_MML_GetSimOperPlmnList();
    ucIsUoplmnExist   = VOS_TRUE;

    /* UPLMN������Ϊ0����OPLMN������Ϊ0 */
    if ((0 == pstUserPlmnList->ucUserPlmnNum)
     && (0 == pstOperPlmnList->usOperPlmnNum))
    {
        ucIsUoplmnExist = VOS_FALSE;
    }

    for(i = 0; i < pstUsimRefreshInd->usEfNum; i++ )
    {
        /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
        if ((USIMM_USIM_EFHPLMNwACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFHPLMNACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_USIM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_GSM_EFOPLMNWACT_ID == pstUsimRefreshInd->astEfId[i].usFileId)
		 || (USIMM_USIM_EFEHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTGSM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || (USIMM_ATTUSIM_EFACTINGHPLMN_ID == pstUsimRefreshInd->astEfId[i].usFileId)
         || ((USIMM_GSM_EFPLMNSEL_ID == pstUsimRefreshInd->astEfId[i].usFileId)
        /* Modified by h00313353 for iteration 9, 2015-2-11, end */
          && (VOS_FALSE == ucIsUoplmnExist)))
        {
            /* H��U��O�ļ�ˢ��ʱ,BG����״̬�����ݲ�ˢ��,�˳�BG����״̬����ˢ�� */
            *penAbortType   = NAS_MMC_ABORT_BUTT;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
        }
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}



VOS_UINT32 NAS_MMC_CompareMsccUpdateUplmnNtfPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;

}



/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnListPrioWithBgSearch
 ��������  : ���û�List������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnListPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}





/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch
 ��������  : ���û�SpEC������Ϣ��BG����״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��27��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareUserPlmnSpecPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{

    /* �ֶ�ģʽʱ������� */
    *penAbortType       = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}
VOS_UINT32  NAS_MMC_CompareSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG������������ϵͳָʾ�Գ�,RRC��ظ�BG ABORT,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�bg abort���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF  ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF    ==  ulCurrState)
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF    ==  ulCurrState)))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}



VOS_UINT32  NAS_MMC_CompareUserDetachReqPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulCurrState;
    VOS_UINT32                          ulTrigerDisableLte;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstCurHighPrioPlmn = VOS_NULL_PTR;

    *penAbortType               = NAS_MMC_ABORT_BUTT;

    /* ��ȡ��ǰ���ڳ��Եĸ����ȼ��������Ϣ */
    pstCurHighPrioPlmn = NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch();

    /* ��ȡ��ǰ״̬����״̬ */
    ulCurrState                 = NAS_MMC_GetFsmTopState();

    /* �жϵ�ǰ�û���detach�Ƿ�ᴥ��disable LTE */
    ulTrigerDisableLte          = NAS_MMC_IsTrigerDisableLte_MoDetach((MSCC_MMC_DETACH_REQ_STRU *)pstMsg);


    if (VOS_TRUE == ulTrigerDisableLte)
    {
        /* ��ǰ��LTE�·ǹ���״̬(detach������Ҫȷ����ǰ�Ľ���ģʽ,����״̬����ģʽΪBUTT),��Ҫdisable LTEʱ,ֱ�Ӵ����
           L1�������detach��Ϣ,disable LTE��ͨ��ָ��������GU�� */
        if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
         && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF != ulCurrState))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }

        /* ��ǰ��GU������״̬��Ҫ���:
          1)GU��BG����L,��ǰ��Ҫdisable LTE
          2)GU�µȴ�����ظ�ʱ,��ǰ��Ҫ�����ĸ����ȼ�����ΪL,��ǰ��Ҫdisable LTE
          ��ʱ��ϵ�L1�´������detach��Ϣ,�յ�GMM��ע���������L1��CS��additionalֵ
          �����Ƿ���Ҫ����ָ������ */
        if (((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF        == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF        == ulCurrState))
         && (NAS_MML_NET_RAT_TYPE_LTE == pstCurHighPrioPlmn->enRat))
        {
            *penAbortType    = NAS_MMC_ABORT_FSM_DELAY;

            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }
#endif

    /* �����������ǰ�������һ�� */
    *penAbortType               = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_CompareLmmSuspendIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCurrState;

    ulCurrState             = NAS_MMC_GetFsmTopState();

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    /* BG������������ϵͳָʾ�Գ�,RRC��ظ�BG ABORT,Ϊ��֤����������ϵͳָʾ
       MMC�Ȼ��������Ϣ,�յ�bg abort���˳�״̬��������Ĺ���ָʾ��Ϣ */
    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF  ==  ulCurrState )
      || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF    ==  ulCurrState )))
    {
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
    }

    /* ע��״ֱ̬�ӽ���״̬���д��� */
    if ( ( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
      && (( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
       || ( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )))
    {
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    /* �����������ǰ�������һ�� */
    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


VOS_UINT32  NAS_MMC_CompareLmmServiceResultIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                                              ulCurrState;

    ulCurrState          = NAS_MMC_GetFsmTopState();
    *penAbortType        = NAS_MMC_ABORT_BUTT;

    /* CSFB������ʱ��L BG�����ظ�״̬���Lע����״̬��������ͷ�״̬���L����ָ����״̬
       ���vplmn��L�����ظ�״̬��Ҫ��ϵ�ǰ״̬��  */
    if (NAS_MML_CSFB_SERVICE_STATUS_MO_EMERGENCY_EXIST == NAS_MML_GetCsfbServiceStatus())
    {
        if (( NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
         && ((NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF == ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND  ==  ulCurrState )
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF ==  ulCurrState)
          || (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN  ==  ulCurrState)))
        {
           *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;
            return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
        }
    }

    if ((NAS_MMC_FSM_BG_PLMN_SEARCH == NAS_MMC_GetCurrFsmId())
     && (NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND == ulCurrState))
    {
        /* ֱ����״̬���д��� */
        *penAbortType   = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
}


#endif
VOS_UINT32 NAS_MMC_ComparePowerOffPrioWithGetGeo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType = NAS_MMC_ABORT_FSM_IMMEDIATELY;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FindMsgPrioCompareFun
 ��������  : ������Ϣ�ȽϺ���
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
             ulFsmEntryEventType    :״̬���������Ϣ
             enFsmId                :״̬����ID
 �������  : ��
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/

NAS_MMC_MSG_COMPARE_FUNC  NAS_MMC_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
)
{
    NAS_MMC_FSM_MSG_COMPARE_STRU       *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;

    for ( i = 0 ; i < (sizeof(g_astMmcMsgCompareTbl)/sizeof(NAS_MMC_FSM_MSG_COMPARE_STRU)) ; i++ )
    {
        if ( enFsmId == g_astMmcMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astMmcMsgCompareTbl[i];
            break;
        }
    }

    /* δ���ҵ���״̬���ıȽϺ�����,ֱ�ӷ��ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* �����Ҫƥ���κ���Ϣ��ֱ�ӽ���ȽϺ��� */
        if ( NAS_MMC_UNIVERAL_MSG_ID == pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType )
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }

        /* ���Ҳ�ͬ�¼��ıȽϺ��� */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* δ�ҵ�������ֱ�ӷ��ؿ�ָ�� */
    return VOS_NULL_PTR;
}




NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 NAS_MMC_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    NAS_MMC_MSG_COMPARE_FUNC                    pfCompareFunc;
    NAS_MMC_FSM_ID_ENUM_UINT32                  enCurrFsmId;
    NAS_MMC_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32   enRslt;

    /*  ��ȡ��ǰ״̬����ID */
    enCurrFsmId         = NAS_MMC_GetCurrFsmId();
    if (NAS_FSM_BUTT <= enCurrFsmId)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }


    /*  ��ȡ�ȽϺ��� NAS_MMC_FindMsgPrioCompareFun() */
    pfCompareFunc       = NAS_MMC_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* δ�ҵ�������,��Ĭ����Ϣ���� */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = NAS_MMC_ABORT_BUTT;
        return NAS_MMC_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ñȽϺ���,�������ȼ��ʹ������ */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


VOS_UINT32 NAS_MMC_CompareMmcNvimOPlmnRefreshIndPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    VOS_UINT32                          ulCacheMsgIdx;
    VOS_UINT32                          ulExistFlg;
    VOS_UINT32                          ulCacheEventType;

    ulCacheEventType     = NAS_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_NVIM_OPLMN_REFRESH_IND);
    ulExistFlg           = NAS_MMC_IsExistCacheMsg(ulCacheEventType, &ulCacheMsgIdx);

    /* ����Ѿ���ͬ������Ϣ�ˣ��������һ������*/
    if (VOS_TRUE == ulExistFlg)
    {
        NAS_MMC_ClearCacheMsg(ulCacheEventType);
    }

    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_CompareTiAvailableTimerExpiredPrioWithInterSysOos
 ��������  : ��available timer��ʱ��Ϣ��BG ��״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��9��11��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_CompareTiPlmnSearchPhaseOneTotalTimerExpiredPrioWithBgSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType           = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}
/* Added by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-11, end */

VOS_UINT32 NAS_MMC_CompareRrmPsStatusIndPrioWithPowerOff(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    NAS_MMC_ABORT_FSM_TYPE_UINT8       *penAbortType
)
{
    *penAbortType   = NAS_MMC_ABORT_BUTT;

    return NAS_MMC_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
