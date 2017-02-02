

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmAnyCellSearch.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasMmcTimerMgmt.h"

#include "NasMmcSndInternalMsg.h"
/* ɾ��ExtAppMmcInterface.h*/

#include "MsccMmcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_ANYCELL_SEARCH_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* NAS MMC״̬������:�������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcAnyCellSearchFsmDesc;

/* NAS_MMC_ANYCELL_SEARCH_STA_INIT Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchInitActTbl[]        =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ANYCELL_SEARCH_REQ,
                      NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init),
};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf),

};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf),

};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmPlmnSrchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf),

};
#endif

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf),
};
#endif

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),


};

/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd),
};


#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF Anycell������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLmmPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasAnyCellSearchWaitLSysInfoIndActTbl[]                =
{
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLSysInfoInd),

};

#endif


/* Э��ջ�޿�����ע��L2״̬�� */
NAS_STA_STRU g_astNasMmcAnyCellSearchStaTbl[] =
{
    /* �ȴ���Ϣ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_INIT,
                          g_astNasAnyCellSearchInitActTbl ),

    /*  �ȴ�Wģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitWasPlmnSrchCnfActTbl ),

    /*  �ȴ�Gģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitGasPlmnSrchCnfActTbl),

#if   (FEATURE_ON == FEATURE_LTE)
    /*  �ȴ�Lģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF,
                          g_astNasAnyCellSearchWaitLmmPlmnSrchCnfActTbl),

#endif
    /* �ȴ�Wģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitWasSuspendCnfActTbl),

    /* �ȴ�Gģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitGasSuspendCnfActTbl),

#if   (FEATURE_ON == FEATURE_LTE)

    /* �ȴ�Lģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF,
                          g_astNasAnyCellSearchWaitLmmSuspendCnfActTbl),
#endif

    /* �ȴ�Wģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitWasPlmnStopCnfActTbl),

    /* �ȴ�Gģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitGasPlmnStopCnfActTbl),


    /* �ȴ�Wģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitWSysInfoIndActTbl ),

    /* �ȴ�Gģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitGSysInfoIndActTbl ),

#if   (FEATURE_ON == FEATURE_LTE)

    /*  �ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF,
                          g_astNasAnyCellSearchWaitLmmPlmnStopCnfActTbl),


    /* �ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND,
                          g_astNasAnyCellSearchWaitLSysInfoIndActTbl ),

#endif

};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAnyCellSearchStaTblSize
 ��������  : ��ȡanycell����״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:anycell����״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetAnyCellSearchStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMmcAnyCellSearchStaTbl)/sizeof(NAS_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetAnyCellSearchFsmDescAddr
 ��������  : ��ȡ�ֶ�������״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ���ֶ�����״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetAnyCellSearchFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcAnyCellSearchFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
