

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "UsimPsInterface.h"
#include "PsTypeDef.h"
#include "MnComm.h"
#include "TafFsm.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "NasComm.h"
#include "TafMmaFsmPhoneMode.h"
#include "MmaMsccInterface.h"
#include "Taf_Tafm_Remote.h"
#include "TafMmaSndInternalMsg.h"
#include "MmaUphyInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_TBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_FSM_DESC_STRU                       g_stTafMmaPhoneModeFsmDesc;

/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* TAF_MMA_PHONE_MODE_STA_INIT ������ */
TAF_ACT_STRU        g_astTafMmaPhoneModeInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_POWER_INIT,
                      TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_SPY,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init ),
    TAF_ACT_TBL_ITEM( CCPU_PID_CBT,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init ),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init ),

};
/* TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT ������ */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitExternalModuleInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit ),

    TAF_ACT_TBL_ITEM( DSP_PID_STARTUP,
                      ID_UPHY_MMA_INIT_STATUS_IND,
                      TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit ),

};



/* TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF ������ */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_START_CNF,
                      TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_START_CNF,
                      TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf ),
};

/* TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF ������ */
TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccPowerOffCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_OFF_CNF,
                      TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf ),

};


TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoWaitMsccStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_START_CNF,
                      TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_START_CNF,
                      TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf ),
};



TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccGetGeoCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GET_GEO_CNF,
                      TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF,
                      TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoCmpWaitUsimStatusIndActTbl[]   =
{
    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                      TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeWaitMsccStopGetGeoCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_STOP_GET_GEO_CNF,
                      TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf ),

    /* ����Գ�ĳ���:���·�ֹͣ��ȡ�����������MSCC�ͽ���ȡ������Ľ���ϱ����� */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GET_GEO_CNF,
                      TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccStopGetGeoCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF,
                      TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf ),
};

TAF_ACT_STRU        g_astTafMmaPhoneModeGetGeoWaitMsccPowerOffCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_OFF_CNF,
                      TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf ),
};


/* �ֻ�ģʽ״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafMmaPhoneModeStaTbl[]   =
{
    /* �ֻ�ģʽ״̬���ĳ�ʼ��״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_INIT,
                       g_astTafMmaPhoneModeInitActTbl ),

    /* Ǩ��״̬���ȴ���ʼ�����״̬�ϱ� */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT,
                      g_astTafMmaPhoneModeWaitExternalModuleInitActTbl ),



    /* �ȴ�MSCC�Ŀ����ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF,
                      g_astTafMmaPhoneModeWaitMsccStartCnfActTbl ),


    /* �ȴ�MSCC�Ĺػ��ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF,
                      g_astTafMmaPhoneModeWaitMsccPowerOffCnfActTbl ),



    /* �ȴ�MSCC��ȡ����λ����Ϣ�Ŀ����ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF,
                      g_astTafMmaPhoneModeGetGeoWaitMsccStartCnfActTbl ),

    /* �ȴ�MSCC�Ļ�ȡ����λ����Ϣ�ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF,
                      g_astTafMmaPhoneModeWaitMsccGetGeoCnfActTbl ),

    /* �ȴ�MSCC�Ļ�ȡ����λ����Ϣ�ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND,
                      g_astTafMmaPhoneModeGetGeoCmpWaitUsimStatusIndActTbl ),

    /* �ȴ�MSCC��ֹͣ��ȡ����λ����Ϣ�ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF,
                      g_astTafMmaPhoneModeWaitMsccStopGetGeoCnfActTbl ),

    /* �ȴ�MSCC��ȡ����λ����Ϣ�Ĺػ��ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF,
                      g_astTafMmaPhoneModeGetGeoWaitMsccPowerOffCnfActTbl ),

};


VOS_UINT32 TAF_MMA_GetPhoneModeStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaPhoneModeStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_MMA_GetPhoneModeFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaPhoneModeFsmDesc);
}






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



