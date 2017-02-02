

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcMain.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcCtx.h"
#include "NasMmlCtx.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcProcNvim.h"
#include "NasComm.h"
#include "NasMmcFsmPowerOff.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#include "PsRrmInterface.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMCFSMPOWEROFF_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/


/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

VOS_UINT32 NAS_MMC_RcvTafPowerOffReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)
    MSCC_MMC_POWER_OFF_REQ_STRU          *pstPowerOffMsg = VOS_NULL_PTR;
#endif
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;

#if   (FEATURE_ON == FEATURE_LTE)
    pstPowerOffMsg = (MSCC_MMC_POWER_OFF_REQ_STRU*)pstMsg;
#endif

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_USER_POWER_OFF);

    /* ֹͣ���ж�ʱ�� */
    NAS_MMC_StopAllTimer();


    /*��RRM����ȥע����Ϣ*/
    NAS_MMC_DeregisterRrmResourceNtfAllRat(RRM_PS_TASK_TYPE_NAS_SEARCH);

    /* ���õ�ǰ����ģ������ */
    NAS_MMC_SetMasterModeRat_PowerOff( NAS_MML_GetCurrNetRatType() );
    /* ��ȡ��ǰ��ģ */
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* ��ģȷ���Ժ󣬹����ģ�б��Ա�������ģ���ػ�����ʱʹ�� */
    NAS_MMC_BuildSlaveModeRatList_PowerOff(enMasterModeRat);

#if   (FEATURE_ON == FEATURE_LTE)

    /* ��������Ĺػ����� */
    if ( ( NAS_MML_NET_RAT_TYPE_LTE         ==  enMasterModeRat)
      && ( NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE ==  pstPowerOffMsg->enCause) )
    {

        /* ֪ͨLMM��״̬�����仯 */
        NAS_MMC_SndLmmUsimStatusReq(MMC_LMM_USIM_INVALID);

        /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF״̬,����������ʱ��*/
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF,TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF_LEN);

        return VOS_TRUE;
    }


    if ( NAS_MML_NET_RAT_TYPE_LTE == enMasterModeRat )
    {

        /* ��LTE���͹ػ���Ϣ */
        NAS_MMC_SndLmmStopReq();

        /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }

#endif

    /* ֪ͨMM�ػ��������õȴ�MM�ظ���־ */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* ֪ͨGMM�ػ��������õȴ�GMM�ظ���־ */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /*****************************************************************
       ��ܳ���:
       PS only�ĳ����£�AT+CFUN=0�ػ�������PS detach
       GMM�����෢��detach���������δ�ظ�detach accept����rel indʱ��
       ��ʱͨ����һ��ͨ���·�AT+CGREG����ע��״̬��ѯ���ػ�ʱ��MMC��MM/
       GMM���͹ػ�����ʱ��MM��GMMǨ״̬��Ǩ��״̬���жϵ�ǰ��Ҫ��MMC
       ����Service Status Indָʾ��ǰCS/PS�����״̬��MMC�յ�MM/GMM����
       ״̬�ϱ��󣬻��MSCC�ϱ���ǰ����״̬���÷���״̬��AT+COPS?ʱ��ʹ��
       ������MMC��MM/GMMģ�鷢��POWER OFF REQ֮��AT+COPS?��ѯ���Ϊ
       �޷��񡣵���ʱCS/PSע��״̬���Ǵ���ע�ᣬע��״̬�����յ�MM/GMM
       CNF֮����и��¡������಻�ظ�detach accept����rel ind��GMM�㲻��
       MMC�ϱ�POWER OFF CNF���������ʱ���ڲ�ѯAT+CGREG?��AT+COPS?������
       ����ά��״̬��һ�¡�

       ����:MMC��MSCC����ע��״̬�����GMM��δ������״̬��MMC�ϱ�ʱ����
            �ö�ʱ���ڲ�ѯͬ������ֲ�һ�¡�
    *******************************************************************/
    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF״̬,������������ʱ��TI_NAS_MMC_WAIT_MM_POWEROFF_CNF */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMsccPowerSaveReq_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enNetRatType;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == NAS_MML_GetCsServiceExistFlg())
    {
        NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_FAILURE);

        /* �ػ���ɣ��˳����״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ��ǰ���뼼�� */
    enNetRatType = NAS_MML_GetCurrNetRatType();

    /* �������Ӵ��� */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        /* ���ݵ�ǰ��ͬ�Ľ��뼼��,�����ͷ�����,Ǩ�Ƶ���ͬ�ĵȴ������ͷŵ�L2״̬��������������ʱ�� */
        NAS_MMC_SndRelReq_PowerOff(enNetRatType);

        return VOS_TRUE;
    }

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvMmPowerOffCnf_PowerOff_WaitMmPoweroffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat     = NAS_MMC_GetMasterModeRat_PowerOff();

    /* ����MM�Ĺػ�ȷ�ϱ�־ */
    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS, NAS_MMC_NO_SERVICE);

    /* δ����MM��GMM�Ĺػ�ȷ����Ϣ�����ؼ����ȴ� */
    if ( NAS_MMC_MMGMM_POWER_OFF_NULL_FLG != NAS_MMC_GetMmPowerOffCnfFlg_PowerOff())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_POWEROFF_CNF );

    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* �ϱ���TAF���ػ��ɹ� */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

                /* �ػ���ɣ��˳����״̬��*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS��ģ���͹ػ���Ϣ,���õȴ�Was�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS��ģ���͹ػ���Ϣ,���õȴ�gas�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* ��ǰû����ģ */
        default:

            /* �����ģ����Ϊ0����û����ģ����λ */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���ɻָ�����,���õ���ӿ�RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmPowerOffCnf_PowerOff_WaitMmPoweroffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* ����GMM�Ĺػ�ȷ�ϱ�־ */
    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_PS, NAS_MMC_NO_SERVICE);

    /*  δ����MM��GMM�Ĺػ�ȷ����Ϣ�����ؼ����ȴ� */
    if ( NAS_MMC_MMGMM_POWER_OFF_NULL_FLG != NAS_MMC_GetMmPowerOffCnfFlg_PowerOff())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_POWEROFF_CNF );

    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* �ϱ���TAF���ػ��ɹ� */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

                /* �ػ���ɣ��˳����״̬��*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS���͹ػ���Ϣ,���õȴ�Was�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS���͹ػ���Ϣ,���õȴ�gas�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* ��ǰû����ģ */
        default:

            /* �����ģ����Ϊ0����û����ģ����λ */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���ɻָ�����,���õ���ӿ�RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf ENTERED");

    /* ���MM�Ĺػ�ȷ�ϱ�־ */
    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff();

    NAS_MMC_ChangePsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);
    NAS_MMC_ChangeCsRegState(NAS_MML_REG_NOT_REGISTERED_NOT_SEARCH);

    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);


    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* �ϱ���TAF���ػ��ɹ� */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

                /* �ػ���ɣ��˳����״̬��*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* ��WAS���͹ػ���Ϣ,���õȴ�Was�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��GAS���͹ػ���Ϣ,���õȴ�gas�ظ���־ */
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);

            /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������������ʱ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

            break;

        /* ��ǰû����ģ */
        default:

            /* �����ģ����Ϊ0����û����ģ����λ */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���ɻָ�����,���õ���ӿ�RESET */
                NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE);

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;
    }


    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    NAS_TRACE_HIGH("Enter!");

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* ֹͣ�յ���ģ�ظ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
    if (0 == pstSlaveModeRatList->ucRatNum)
    {
        /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
        NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

        /* �ϱ���TAF���ػ��ɹ� */
        NAS_Mmc_SndMsccPowerOffCnf();

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

        /* �ػ���ɣ��˳����״̬��*/
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* ����ģ���͹ػ����� */
        NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

        /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* ֹͣ�յ���ģ�ظ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    (VOS_VOID)vos_printf("NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf, tick = 0x%x\r\n ", VOS_GetSlice());

    /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
    if (0 == pstSlaveModeRatList->ucRatNum)
    {
        /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
        NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

        /* �ϱ���TAF���ػ��ɹ� */
        NAS_Mmc_SndMsccPowerOffCnf();

        /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
        NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

        /* �ػ���ɣ��˳����״̬��*/
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* ����ģ���͹ػ����� */
        NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

        /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstSlaveModeRatList = VOS_NULL_PTR;

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();
    enMasterModeRat = NAS_MMC_GetMasterModeRat_PowerOff();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    switch ( enMasterModeRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ֪ͨMM�ػ��������õȴ�MM�ظ���־ */
            NAS_MMC_SndMmPowerOffReq();
            NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

            /* ֪ͨGMM�ػ��������õȴ�GMM�ظ���־ */
            NAS_MMC_SndGmmPowerOffReq();
            NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

            /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF״̬,������������ʱ��TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* �ϱ���TAF���ػ��ɹ� */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

                /* �ػ���ɣ��˳����״̬��*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:

            /* �����ģ����Ϊ0����ʾƽ̨֧�ֵ�ģ������Ҫ�ٸ�����ģ���͹ػ���Ϣ��ֱ����״̬�� */
            if (0 == pstSlaveModeRatList->ucRatNum)
            {
                /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
                NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

                /* �ϱ���TAF���ػ��ɹ� */
                NAS_Mmc_SndMsccPowerOffCnf();

                /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
                NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

                /* �ػ���ɣ��˳����״̬��*/
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;
            }
            else
            {
                /* ����ģ���͹ػ����� */
                NAS_MMC_SndSlaveModePowerOffReq_PowerOff();

                /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,������������ʱ�� */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF);
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF_LEN);
            }
            break;

        /* ��ǰû����ģ */
        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf:NO MASTER MODE!");
            break;
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* ����GAS�����Ĺػ�ȷ����Ϣ��¼��־ */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_GAS_POWER_OFF_FLG );

    /* δ�������н����Ĺػ�ȷ����Ϣ�����ؼ����ȴ� */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }


    /* ��ǰGģΪ��ģ���յ������н����Ĺػ��ظ� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* �ϱ���TAF���ػ��ɹ� */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* ���½����WAS�Ĺػ�ȷ����Ϣ��¼��־ */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_WAS_POWER_OFF_FLG );

    /* δ�������н����Ĺػ�ȷ����Ϣ,���ؼ����ȴ� */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* �ϱ���TAF���ػ��ɹ� */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    /* ���GAS��WAS��LMM�Ĺػ�ȷ����Ϣ��¼��־ */
    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff();

    /* �ϱ���TAF���ػ��ɹ� */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}



#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvLmmStopCnf_PowerOff_WaitMasterModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF);

    /* ֪ͨMM�ػ��������õȴ�MM�ظ���־ */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* ֪ͨGMM�ػ��������õȴ�GMM�ظ���־ */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF״̬,������������ʱ��TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    /* ֹͣ������ʱ��TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    /* �������ʧ��ֱ�Ӹ�λ */
    if (MMC_LMM_FAIL == pstSuspendCnf->ulRst)
    {
        /* �쳣��ӡ */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf: SUSPEND FAIL !");

        /* ���ɻָ�����,���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* ���õ�ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* �ϱ���MSCC Power Save�ɹ� */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* �ػ���ɣ��˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf: Enter !");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvLmmStopCnf_PowerOff_WaitSlaveModePowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* ���½����LTE�Ĺػ�ȷ����Ϣ��¼��־ */
    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff( NAS_MMC_LTE_POWER_OFF_FLG );

    /* δ�������н����Ĺػ�ȷ����Ϣ�����ؼ����ȴ� */
    if ( NAS_MMC_AS_POWER_OFF_NULL_FLG != NAS_MMC_GetAsPowerOffCnfFlg_PowerOff() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF);

    /* �ϱ���TAF���ػ��ɹ� */
    NAS_Mmc_SndMsccPowerOffCnf();

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_OFF);

    /* �ػ���ɣ��˳����״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvLmmUsimStatusCnf_PowerOff_WaitLmmUsimStatusCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* MMCֹͣ��ʱ��: TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF );

#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetMasterModeRat_PowerOff() )
    {

        /* ��LTE��ģ���͹ػ���Ϣ */
        NAS_MMC_SndLmmStopReq();

        /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,������10s������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }

#endif

    /* ֪ͨMM�ػ��������õȴ�MM�ظ���־ */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* ֪ͨGMM�ػ��������õȴ�GMM�ظ���־ */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF״̬,������������ʱ��TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmUsimStatusExpired_PowerOff_WaitLmmUsimStatusCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetMasterModeRat_PowerOff() )
    {

        /* ��LTE���͹ػ���Ϣ */
        NAS_MMC_SndLmmStopReq();

        /* Ǩ��״̬��NAS_MMC_POWEROFF::NAS_MMC_POWER_OFF_STA_WAIT_AS_POWEROFF_CNF,������10s������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF, TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF_LEN);

        return VOS_TRUE;
    }
#endif

    /* ֪ͨMM�ػ��������õȴ�MM�ظ���־ */
    NAS_MMC_SndMmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_MM_POWER_OFF_FLG );

    /* ֪ͨGMM�ػ��������õȴ�GMM�ظ���־ */
    NAS_MMC_SndGmmPowerOffReq();

    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff( NAS_MMC_GMM_POWER_OFF_FLG );

    /* Ǩ�Ƶ� NAS_MMC_L2_STA_POWER_OFF:NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF״̬,������������ʱ��TI_NAS_MMC_WAIT_MM_POWEROFF_CNF*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_POWEROFF_CNF, TI_NAS_MMC_WAIT_MM_POWEROFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU                                *pstLmmStatusIndMsg = VOS_NULL_PTR;

    pstLmmStatusIndMsg  = ( LMM_MMC_STATUS_IND_STRU* )pstMsg;

    /* ����EPS������Ӵ���״̬ */
    if ( (MMC_LMM_CONN_ESTING == pstLmmStatusIndMsg->ulConnState)
      || (MMC_LMM_CONNECTED_SIG == pstLmmStatusIndMsg->ulConnState) )
    {
        /* ���ô���EPS�������� */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONNECTED_DATA == pstLmmStatusIndMsg->ulConnState)
    {
        /* ���ô���EPSҵ������ */
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);
    }
    else if (MMC_LMM_CONN_IDLE == pstLmmStatusIndMsg->ulConnState)
    {
        /* ���ò�����EPS�������� */
        NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);
        NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);
    }
    else
    {
        ;
    }

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʱ����ʱ��ֱ�Ӹ���ǰ���뼼�������� */
    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_PowerOff_WaitEpsConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndLmmSuspendRsp(MMC_LMM_FAIL);

    return VOS_TRUE;
}

#endif


VOS_VOID NAS_MMC_SndSlaveModePowerOffReq_PowerOff(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU                 *pstSlaveModeRatList = VOS_NULL_PTR;
    VOS_UINT32                                  i;

    /* ��ȡ��ģ�ػ��б� */
    pstSlaveModeRatList = NAS_MMC_GetSlaveModeRatList_PowerOff();

    /* ƽ̨���ǵ�ģʱ������ģ���͹ػ���Ϣ */
    for (i = 0; i < pstSlaveModeRatList->ucRatNum; i++)
    {
        /* ��GAS���͹ػ���Ϣ,���õȴ�gas�ظ���־ */
        if (NAS_MML_NET_RAT_TYPE_GSM == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndAsPowerOffReq(UEPS_PID_GAS);
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_GAS_POWER_OFF_FLG );
        }

        /* ��WAS���͹ػ���Ϣ,���õȴ�Was�ظ���־ */
        else if (NAS_MML_NET_RAT_TYPE_WCDMA == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndAsPowerOffReq(WUEPS_PID_WRR);
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_WAS_POWER_OFF_FLG );
        }

        /* ��LMM���͹ػ���Ϣ,���õȴ�LMM�ظ���־ */
#if (FEATURE_ON == FEATURE_LTE)
        else if (NAS_MML_NET_RAT_TYPE_LTE == pstSlaveModeRatList->aucRatPrio[i])
        {
            NAS_MMC_SndLmmStopReq();
            NAS_MMC_SetAsPowerOffCnfFlag_PowerOff( NAS_MMC_LTE_POWER_OFF_FLG );
        }
#endif
        else
        {
        }
    }

    return;

}



#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MMC_ProcRrmDeRegister_PowerOff(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                usModemId;

    /* ȡ�õ�ǰMODEM��ID��Ϣ  */
    usModemId = VOS_GetModemIDFromPid(WUEPS_PID_MMC);

    /* �����ǰNVδ����DSDS,����RRM���͹ػ�ȥע�� */
    if ( VOS_FALSE == NAS_MML_GetDsdsRfShareFlg() )
    {
        return;
    }

    /* ��MODEM0ʱ����RRM����W�µ�ȥע����Ϣ */
    if ( MODEM_ID_0 == usModemId )
    {
        NAS_MMC_SndRrmDeRegisterInd(MODEM_ID_0,
                                    RRM_PS_TASK_TYPE_NAS_SEARCH,
                                    VOS_RATMODE_WCDMA);
    }

    /* ��MODEM1ʱ����RRM����G�µ�ȥע����Ϣ */
    if ( MODEM_ID_1 == usModemId )
    {
        NAS_MMC_SndRrmDeRegisterInd(MODEM_ID_1,
                                    RRM_PS_TASK_TYPE_NAS_SEARCH,
                                    VOS_RATMODE_GSM);
    }

    return;
}

#endif


VOS_VOID NAS_MMC_SndSuspendReq_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ״̬����Ϊ��ǰδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    /* ���ݲ�ͬ�Ľ��뼼�����õȴ������ظ���״̬ */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_PowerOff: Rat not support.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_SndRelReq_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ���ݲ�ͬ�Ľ��뼼���ֱ��� */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            /* ��EMM�����ͷ����� */
            NAS_MMC_SndLmmRelReq();
            /* Modified by h00313353 for Iteration 13, 2015-4-17, begin */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EPS_CONN_REL_IND, TI_NAS_MMC_WAIT_EPS_CONN_REL_IND_LEN);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_EPS_CONN_REL_IND);
            /* Modified by h00313353 for Iteration 13, 2015-4-17, end */
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* ��MM/GMM�����ͷ����� */
            NAS_MMC_SndMmRelReq();
            NAS_MMC_SndGmmRelReq();
            /* Modified by h00313353 for Iteration 13, 2015-4-17, begin */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL, TI_NAS_MMC_WAIT_RRC_CONN_REL_LEN);

            NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND);
            /* Modified by h00313353 for Iteration 13, 2015-4-17, end */

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRelReq_PowerOff: Rat not support.");
            break;
    }

    return;
}
VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ������ͷŶ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvMmConnInfoInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmRrRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvRrMmRelInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelIndMsg = VOS_NULL_PTR;

    pstRelIndMsg = ( RRMM_REL_IND_STRU * )pstMsg;

    /* ������Ӵ��ڱ�־ */
    if (RRC_RRC_CONN_STATUS_ABSENT == pstRelIndMsg->ulRrcConnStatus)
    {
        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
    }

    /*  ��������������ӣ�������ȴ�  */
    if (VOS_TRUE == NAS_MML_IsRrcConnExist())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_RRC_CONN_REL);

    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }


    /* ���õ�ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* �ϱ���MSCC Power Save�ɹ� */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* �ػ���ɣ��˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_PLMN_WITH_RAT_STRU          stDestPlmn;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ����汾Coverity���� */
    PS_MEM_SET(&stDestPlmn, 0, sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    /* ���õ�ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* �ϱ���MSCC Power Save�ɹ� */
    NAS_MMC_SndMsccPowerSaveCnf(NAS_MSCC_PIF_POWER_SAVE_SUCCESS);

    /* ��������н��֪ͨ��һ����һ�յ�����Ϣ����в�һ״̬��Ǩ�� */
    NAS_MMC_SndPowerOffRslt(NAS_MMC_POWEROFF_RSLT_POWER_SAVE);

    /* �ػ���ɣ��˳����״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitRrcConnRelExpired_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʱ����ʱ��ֱ�Ӹ���ǰ���뼼�������� */
    /* ��MM/GMM����Cover lostָʾ */
    NAS_MMC_SndMmCoverageLostInd();
    NAS_MMC_SndGmmCoverageLostInd();

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ����ǰ�����������SUSPEND REQ����ָʾ��ǰ��������POWER SAVEģʽ */
    NAS_MMC_SndSuspendReq_PowerOff(NAS_MML_GetCurrNetRatType());

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvWasSuspendInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, WUEPS_PID_WRR);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGasSuspendInd_PowerOff_WaitRrcConnRelInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SndAsSuspendRsp(RRC_NAS_SUSPEND_FAILURE, UEPS_PID_GAS);

    return VOS_TRUE;
}



/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

