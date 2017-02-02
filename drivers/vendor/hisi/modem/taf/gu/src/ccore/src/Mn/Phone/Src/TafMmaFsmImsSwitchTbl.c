

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafFsm.h"
#include "TafAppMma.h"
#include "TafMmaTimerMgmt.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "MmaMsccInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_TBL_C

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_FSM_DESC_STRU                       g_stTafMmaImsSwitchFsmDesc;

/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* TAF_MMA_IMS_SWITCH_STA_INIT ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_SET_REQ,
                      TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_START_CNF ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStartCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_START_CNF,
                      TAF_MMA_RcvMsccImsStartCnf_ImsSwitch_WaitMsccImsStartCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF,
                      TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf ),

};

/* TAF_MMA_IMS_SWITCH_STA_WAIT_IMSA_STOP_CNF ������ */
TAF_ACT_STRU        g_astTafMmaImsSwitchWaitImsaStopCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_STOP_CNF,
                      TAF_MMA_RcvMsccImsStopCnf_ImsSwitch_WaitMsccImsStopCnf ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF,
                      TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf ),

};

/* IMS����״̬���������Ϣ ״̬�� */
TAF_STA_STRU        g_astTafMmaImsSwitchStaTbl[]   =
{
    /* IMS����״̬���ĳ�ʼ��״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_INIT,
                       g_astTafMmaImsSwitchInitActTbl ),

    /* �ȴ�IMSA�Ŀ����ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_START_CNF,
                      g_astTafMmaImsSwitchWaitImsaStartCnfActTbl ),

    /* �ȴ�IMSA�Ĺػ��ظ�״̬ */
    TAF_STA_TBL_ITEM( TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_STOP_CNF,
                      g_astTafMmaImsSwitchWaitImsaStopCnfActTbl ),
};



VOS_UINT32 TAF_MMA_GetImsSwitchStaTblSize(VOS_VOID)
{
    return (sizeof(g_astTafMmaImsSwitchStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_MMA_GetImsSwitchFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaImsSwitchFsmDesc);
}
#endif /* FEATURE_IMS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



