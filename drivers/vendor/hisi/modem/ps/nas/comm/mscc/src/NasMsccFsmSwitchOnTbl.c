


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasFsm.h"
#include  "NasMsccFsmSwitchOn.h"
#include  "NasMsccFsmSwitchOnTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_SWITCH_ON_TBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
NAS_FSM_DESC_STRU                       g_stNasMsccSwitchOnFsmDesc;

/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* NAS_MSCC_SWITCHON_STA_INIT Action table */
NAS_ACT_STRU        g_astNasMsccSwitchOnInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      ID_MMA_MSCC_START_REQ,
                      NAS_MSCC_RcvMmaStartReq_SwitchOn_Init)
};

/* NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF Action table */
#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitCardReadCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      NAS_MSCC_RcvUsimmReadFileCnf_SwitchOn_WaitCardReadCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_CARD_READ_CNF,
                      NAS_MSCC_RcvTiWaitCardReadTimerExpire_SwitchOn_WaitCardReadCnf )

};
#endif

#if (FEATURE_IMS == FEATURE_ON)

/* NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF Action table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitImsaStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( PS_PID_IMSA,
                      ID_IMSA_MSCC_START_CNF,
                      NAS_MSCC_RcvImsaStartCnf_SwitchOn_WaitImsaStartCnf ),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_IMSA_START_CNF,
                      NAS_MSCC_RcvTiWaitImsaStartCnfExpired_SwitchOn_WaitImsaStartCnf )

};

#endif

/* NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitMmcStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      ID_MMC_MSCC_START_CNF,
                      NAS_MSCC_RcvMmcStartCnf_SwitchOn_WaitMmcStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_MMC_START_CNF,
                      NAS_MSCC_RcvTiWaitMmcStartCnfExpired_SwitchOn_WaitMmcStartCnf )

};


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/* NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF Action table */
NAS_ACT_STRU        g_astNasMsccSWitchOnWaitXsdStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_XSD,
                      ID_XSD_MSCC_START_CNF,
                      NAS_MSCC_RcvXsdStartCnf_SwitchOn_WaitXsdStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_XSD_START_CNF,
                      NAS_MSCC_RcvTiWaitXsdStartCnfExpired_SwitchOn_WaitXsdStartCnf )

};

/* NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF Action Table */
NAS_ACT_STRU        g_astNasMsccSwitchOnWaitHsdStartCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_HSD,
                      ID_HSD_MSCC_START_CNF,
                      NAS_MSCC_RcvHsdStartCnf_SwitchOn_WaitHsdStartCnf ),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MSCC_WAIT_HSD_START_CNF,
                      NAS_MSCC_RcvTiWaitHsdStartCnfExpired_SwitchOn_WaitHsdStartCnf )

};
#endif


/* NAS MSCC Switch On state table */
NAS_STA_STRU        g_astNasMsccSwitchOnStaTbl[]   =
{
    /* �ֻ�ģʽ״̬���ĳ�ʼ��״̬ */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_INIT,
                       g_astNasMsccSwitchOnInitActTbl ),

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_CARD_READ_CNF,
                      g_astNasMsccSwitchOnWaitCardReadCnfActTbl ),
#endif

#if (FEATURE_LTE == FEATURE_ON) && (FEATURE_IMS == FEATURE_ON)

    /* �ȴ�IMSA�Ŀ����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_IMSA_START_CNF,
                      g_astNasMsccSwitchOnWaitImsaStartCnfActTbl ),

#endif

    /* �ȴ�MMC�Ŀ����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_MMC_START_CNF,
                      g_astNasMsccSwitchOnWaitMmcStartCnfActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* �ȴ�XSD�Ŀ����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_XSD_START_CNF,
                      g_astNasMsccSWitchOnWaitXsdStartCnfActTbl ),


    /* �ȴ�HSD�Ŀ����ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_MSCC_SWITCHON_STA_WAIT_HSD_START_CNF,
                      g_astNasMsccSwitchOnWaitHsdStartCnfActTbl )

#endif
};

VOS_UINT32 NAS_MSCC_GetSwitchOnStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMsccSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
Function Name   :   NAS_MSCC_GetSwitchOnFsmDescAddr
Description     :
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   &NAS_FSM_DESC_STRU

Modify History:
    1)  Date    :   2015-1-30
        Author  :   k902809
        Modify content :    Create
*****************************************************************************/
NAS_FSM_DESC_STRU *NAS_MSCC_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMsccSwitchOnFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


