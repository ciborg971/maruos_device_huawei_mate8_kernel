

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASTIMER_C


VOS_VOID GMM_TimReadyExpired(VOS_VOID)
{
    VOS_UINT32                          ulT3311Status;
    VOS_UINT32                          ulT3302Status;

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    /* WCDMAģʽ����HSS 4100 V100R001���봦�� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* ��ע��״̬,���ҷ���״̬�ǿ���̬ʱ,����3312 */
        if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
         && (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_TRUE != g_GmmRauCtrl.ucT3312ExpiredFlg ))
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        return;     /* ���账���� */
    }

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        ulT3311Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3311);
        ulT3302Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState))
        {
            if ((VOS_FALSE == ulT3311Status)
             && (VOS_FALSE == ulT3302Status))
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }
        else
        {
            if ((0x10 != (g_GmmGlobalCtrl.ucState & 0xF0))
             && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
                {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }

        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    return;
}
VOS_VOID GMM_TimRauRspExpired(VOS_VOID)
{
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    /* ����Ҫ�ȴ�WRR�Ļظ���Ϣ�������Ѿ��յ�WRR�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
