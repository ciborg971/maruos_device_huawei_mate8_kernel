

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "NasRabmFastdorm.h"
#include "NasRabmMain.h"
#include "rabmdef.h"
#include "NasMmlCtx.h"
#include "TafNvInterface.h"
#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_FASTDORM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

NAS_RABM_FASTDORM_CTX_STRU              g_stNasRabmFastDormCtx;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID NAS_RABM_RcvAtFastDormStartReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* ��ȡ��ǰ�������� */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* ����FD�����־ */
    NAS_RABM_SET_FD_ACT_FLG(VOS_TRUE);

    /* ����FAST DORMANCYΪW�����ԣ������W�����£��Ҵ���PDPʵ�弤�����Ҫά��FD״̬ */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
    {
        if (NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
        {
            /* ����PDP RAB״̬�л�FD״̬ */
            if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
            {
                NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
                /* FD���ݼ��������� */
                NAS_RABM_CLR_FD_ULDATA_CNT();
                NAS_RABM_CLR_FD_DLDATA_CNT();
                /* ������ʱ��������0 */
                NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

                /* ����������������ⶨʱ�� */
                NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
            }
        }
    }

    /* �ظ���AT ID_RABM_AT_FASTDORM_START_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    NAS_RABM_SndOmFastdormStatus();
}



VOS_VOID NAS_RABM_RcvAtFastDormStopReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        /* ��ԭfd�Ĺ���������ʹ�õĸ��ֱ����Ͷ�ʱ�� */
        NAS_RABM_RevertFastDormEnv();

        /* ����ΪFD����û�м��� */
        NAS_RABM_SET_FD_ACT_FLG(VOS_FALSE);
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    /* �ظ���AT ID_RABM_AT_SET_FASTDORM_PARA_CNF */
    NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     AT_RABM_PARA_SET_RSLT_SUCC);

    return;
}
VOS_VOID NAS_RABM_RcvSetFastDormParaReq(
    AT_RABM_SET_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlg;
    VOS_UINT32                                              ulLength;

    ulLength                 = 0;
    stEnableFlg.ucEnableFlag = VOS_FALSE;

    /* ��NVʧ�ܣ���Ϊ������Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlg,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvSetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* ������Fastdormancy */
    if (VOS_FALSE == stEnableFlg.ucEnableFlag)
    {
        /* �ظ���AT ID_RABM_AT_FASTDORM_START_CNF */
        NAS_RABM_SndAtSetFastDormParaCnf(pstFastDormPara->usClientId,
                                         pstFastDormPara->ucOpId,
                                         AT_RABM_PARA_SET_RSLT_FAIL);

        return;
    }

    /* �����û����õĲ��� */
    NAS_RABM_SET_FD_OPERATION_TYPE(pstFastDormPara->stFastDormPara.enFastDormOperationType);
    NAS_RABM_SET_FD_USER_DEF_NOFLUX_CNT(pstFastDormPara->stFastDormPara.ulTimeLen);

    if (AT_RABM_FASTDORM_STOP_FD_ASCR == pstFastDormPara->stFastDormPara.enFastDormOperationType)
    {
        /* ���ú�����ֹͣFAST DORMANCY */
        NAS_RABM_RcvAtFastDormStopReq(pstFastDormPara);
    }
    else
    {
        /* ���ú��� ������������FAST DORMANCY */
        NAS_RABM_RcvAtFastDormStartReq(pstFastDormPara);
    }
    /*lint +e958 */
}


VOS_VOID NAS_RABM_RcvGetFastDormParaReq(
    AT_RABM_QRY_FASTDORM_PARA_REQ_STRU *pstFastDormPara
)
{
    /*lint -e958 */
    NAS_RABM_NVIM_FASTDORM_ENABLE_FLG_STRU                  stEnableFlag;
    VOS_UINT32                                              ulLength;

    ulLength                  = 0;
    stEnableFlag.ucEnableFlag = VOS_FALSE;

    /* ��NVʧ�ܣ���Ϊ������Fastdormancy */
    (VOS_VOID)NV_GetLength(en_NV_Item_Fastdorm_Enable_Flag, &ulLength);

    if (NV_OK != NV_Read(en_NV_Item_Fastdorm_Enable_Flag, &stEnableFlag,
                          ulLength))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_RcvGetFastDormParaReq:WARNING:NV_Read faild!");
    }

    /* �ظ���ѯ��� */
    NAS_RABM_SndAtQryFastDormParaCnf(pstFastDormPara->usClientId,
                                     pstFastDormPara->ucOpId,
                                     stEnableFlag.ucEnableFlag);

    /*lint +e958 */
}


VOS_VOID NAS_RABM_SysModeChgProcFastDorm(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    /* ϵͳ�仯���ж������ǰ��Wģ������ģ������FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA == enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA != enNewSysMode)
      && (NAS_MML_NET_RAT_TYPE_BUTT != enNewSysMode))
    {
        NAS_RABM_SuspendFastDorm();
    }

    /* ϵͳ�仯���ж������ǰ������ģ��Wģ���ָ�FAST DORMANCY */
    if ( (NAS_MML_NET_RAT_TYPE_WCDMA != enOldSysMode)
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enNewSysMode) )
    {
        NAS_RABM_ResumeFastDorm();
    }

}


VOS_VOID NAS_RABM_SuspendFastDorm(VOS_VOID)
{
    /* �����ǰFD����û�м����򲻴��� */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    /* ��ԭfd�Ĺ���������ʹ�õĸ��ֱ����Ͷ�ʱ�� */
    NAS_RABM_RevertFastDormEnv();

    /* ����ΪNAS_RABM_FASTDORM_INIT״̬ */
    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
    NAS_RABM_SndOmFastdormStatus();

    return;
}
VOS_VOID NAS_RABM_ResumeFastDorm(VOS_VOID)
{
    /* �����ǰFD����û�м����򲻴��� */
    if (VOS_TRUE != NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

    /* ����PDP RB״̬�л�FD״̬ */
    if (VOS_TRUE == NAS_RABM_CheckPdpRbStatus())
    {
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
        /* FD���ݼ��������� */
        NAS_RABM_CLR_FD_ULDATA_CNT();
        NAS_RABM_CLR_FD_DLDATA_CNT();

        /* ����������������ⶨʱ�� */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_FLUX_DETECT, RABM_TIMER_FASTDORM_FLUX_DETECT );
    }

    return;
}
VOS_UINT8 NAS_RABM_CheckPdpRbStatus(VOS_VOID)
{
    VOS_UINT8                               ucEntId;

    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if (g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_WITH_RAB)
        {
            break;
        }
    }

    if (ucEntId >= RABM_PS_MAX_ENT_NUM)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 NAS_RABM_CheckGmmAndRabmStatus(
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus
)
{
    VOS_UINT8                               ucEntId;

    /* ���GMM��״̬ �����ڶ��š�cs��������������������gmm���̣����ܷ���FD*/
    if ( (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpGmmSpecificProcedure)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpPsSmsService)
      || (VOS_TRUE == pstProcStatus->stMmlProcStatus.bitOpCsSignal) )
    {
        return VOS_FALSE;
    }

    /* ����PDPʵ��״̬��ֻҪ����pdpʵ������pdp�����rb�ؽ������ܷ���FD */
    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        if ((g_aRabmPsEnt[ucEntId].ucState == RABM_NSAPI_ACTIVE_PENDING)
         || (NAS_RABM_GetWPsEntRabReestFlg(ucEntId) == VOS_TRUE))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32                enAtFastDormType,
    RRC_FASTDORM_START_TYPE_ENUM_UINT32                 *penWrrFastDormType
)
{
    switch(enAtFastDormType)
    {
        case AT_RABM_FASTDORM_START_FD_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD;
            break;

        case AT_RABM_FASTDORM_START_ASCR_ONLY:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_ASCR;
            break;

        case AT_RABM_FASTDORM_START_FD_ASCR:
            *penWrrFastDormType = RRC_FASTDORM_START_TYPE_FD_ASCR;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                        "NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType: Wrong Type.");

            break;

    }
}


VOS_VOID NAS_RABM_RcvWasFastDormInfoInd(
    struct MsgCB                       *pMsg
)
{
    RRRABM_FASTDORM_INFO_IND_STRU      *pstInfoInd;

    pstInfoInd = (RRRABM_FASTDORM_INFO_IND_STRU*)pMsg;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        if (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType)
        {
            /* ����RABM_TIMER_FASTDORM_RETRY��ʱ�� */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
            NAS_RABM_SndOmFastdormStatus();
        }
        else
        {
            /* ����FD��NAS_RABM_FASTDORM_INIT״̬ */;
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);
            NAS_RABM_SndOmFastdormStatus();
        }

        return;
    }

    /* ����FD�л���INIT״̬��wrr�ֻظ�retry��Ϣ */
    if ((NAS_RABM_FASTDORM_INIT == NAS_RABM_GET_FD_STATUS())
     && (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
     && (RRRABM_FASTDORM_INFO_NEED_RETRY == pstInfoInd->enInfoType))
    {
        /* ����FD��NAS_RABM_FASTDORM_EXEC״̬ */;
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
        NAS_RABM_SndOmFastdormStatus();

        /* ����RABM_TIMER_FASTDORM_RETRY��ʱ�� */
        NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
    }

    return;
}
VOS_VOID NAS_RABM_ProcFastDormStatusInTransfer( VOS_VOID )
{
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        if (NAS_RABM_FASTDORM_DETECT != NAS_RABM_GET_FD_STATUS())
        {
            /* ��ԭfd�Ĺ���������ʹ�õĸ��ֱ����Ͷ�ʱ�� */
            NAS_RABM_RevertFastDormEnv();

            /* ����ΪNAS_RABM_FASTDORM_DETECT״̬ */
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
            NAS_RabmStartTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_SndOmFastdormStatus();
        }
    }

    return;
}


VOS_VOID NAS_RABM_RevertFastDormEnv(VOS_VOID)
{
    /* ��WAS����RRRABM_FASTDORM_STOP_REQ */
    NAS_RABM_SndWasFastDormStopReq();

    /* ֹͣ��ʱ��RABM_TIMER_FASTDORM_FLUX_DETECT */
    /* ֹͣ��ʱ��RABM_TIMER_FASTDORM_RETRY */
    /* ֹͣ��ʱ��RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT*/
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    NAS_RabmStopTimer(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON,RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);

    /* ����������������� */
    NAS_RABM_CLR_FD_ULDATA_CNT();
    NAS_RABM_CLR_FD_DLDATA_CNT();

    /* ������ʱ��������0 */
    NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

    /* ����ͷ�RRC��ʶ */
    NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();

    return;
}
VOS_VOID NAS_RABM_AbortRelRrcProcedure(VOS_VOID)
{
    /* FD���ܿ���ʱ, ��FD�Ĵ�������Ϊ׼ */
    if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
    {
        return;
    }

    if (VOS_TRUE == NAS_RABM_GET_FD_REL_RRC_EXEC_FLG())
    {
        NAS_RABM_CLR_FD_REL_RRC_EXEC_FLG();
        NAS_RABM_SndWasFastDormStopReq();
    }

    return;
}
VOS_VOID NAS_RABM_RcvReleaseRrcReq(
    AT_RABM_RELEASE_RRC_REQ_STRU *pstMsg
)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* ��ȡ��ǰ�������� */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    /* �������W�����£������ͷ�RRC���� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != enCurrentSysMode)
    {
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_ERR);
    }
    else
    {
        /* ֱ�ӻظ�rrc�ͷųɹ� */
        NAS_RABM_SndAtReleaseRrcCnf(pstMsg->usClientId, pstMsg->ucOpId, VOS_OK);

        /* ��GMM���Ͳ�ѯ��Ϣ */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_RELEASE_RRC_ENUM);

    }

    return;
}

VOS_VOID NAS_RABM_InitFastDormCtx(VOS_VOID)
{
    g_stNasRabmFastDormCtx.enCurrFastDormStatus    = NAS_RABM_FASTDORM_INIT;
    g_stNasRabmFastDormCtx.ulCurrNoFluxCnt         = 0;
    g_stNasRabmFastDormCtx.enFastDormOperationType = AT_RABM_FASTDORM_STOP_FD_ASCR;
    g_stNasRabmFastDormCtx.ulUserDefNoFluxCnt      = 0;

    g_stNasRabmFastDormCtx.ulDlDataCnt             = 0;
    g_stNasRabmFastDormCtx.ulUlDataCnt             = 0;

    g_stNasRabmFastDormCtx.ulRelRrcExecFlg         = VOS_FALSE;

    g_stNasRabmFastDormCtx.ulActiveFlg             = VOS_FALSE; /* Ĭ��FD����û�м��� */

    g_ulNasRabmFDFluxDetectTimer                   = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDRetryTimer                        = NAS_RABM_TIMER_STATUS_STOP;
    g_ulNasRabmFDWaitGmmQryRsltTimer               = NAS_RABM_TIMER_STATUS_STOP;
}
VOS_VOID NAS_RABM_FastDormFluxDetectExpired(VOS_VOID)
{
    VOS_UINT32                              ulUserDefNoFluxCnt;
    VOS_UINT32                              ulCurrNoFluxCnt;
    VOS_UINT32                              ulUlDataCnt;
    VOS_UINT32                              ulDlDataCnt;

    if (NAS_RABM_FASTDORM_DETECT == NAS_RABM_GET_FD_STATUS())
    {
        ulUlDataCnt = NAS_RABM_GET_FD_ULDATA_CNT();
        ulDlDataCnt = NAS_RABM_GET_FD_DLDATA_CNT();

        /* �������ݴ���ʱ���������ʱ���������ȴ�����ͳ�ƶ�ʱ����ʱ */
        if ((ulUlDataCnt > 0) || (ulDlDataCnt > 0))
        {
            /*������������*/
            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();
            /* ������ʱ������ֵ��0 */
            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            return;
        }

        ulUserDefNoFluxCnt = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
        ulCurrNoFluxCnt    = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

        ulCurrNoFluxCnt += 1;

        /* ������ʱ���ﵽ�û����õ�������ʱ�����л�FD״̬ΪNAS_RABM_FASTDORM_EXEC��ֹͣ����ͳ�ƶ�ʱ�� */
        if (ulCurrNoFluxCnt >= ulUserDefNoFluxCnt)
        {
            NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_EXEC);
            NAS_RabmStopTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

            NAS_RABM_CLR_FD_ULDATA_CNT();
            NAS_RABM_CLR_FD_DLDATA_CNT();

            NAS_RABM_SET_FD_CURR_NOFLUX_CNT(0);

            /* ��GMM���Ͳ�ѯ��Ϣ */
            NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);

            /* ������ʱ��TI_NAS_RABM_FASTDORM_WAIT_GMM_QRY_RESULT */
            NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );
            NAS_RABM_SndOmFastdormStatus();

            return;
        }

        /* �洢��ǰ������������ֵ */
        NAS_RABM_SET_FD_CURR_NOFLUX_CNT(ulCurrNoFluxCnt);
    }

    return;

}
VOS_VOID NAS_RABM_FastDormRetryExpired(VOS_VOID)
{
    /* ��retry��ʱ����״̬����Ϊstop */
    g_ulNasRabmFDRetryTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* ��GMM���Ͳ�ѯ��Ϣ */
        NAS_RABM_SndGmmMmlProcStatusQryReq(RABM_FASTDORM_ENUM);
        /* ������ʱ��RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT */
        NAS_RabmStartTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}
VOS_VOID NAS_RABM_FastDormWaitGmmProcQryRsltExpired(VOS_VOID)
{
    /* �Ѷ�ʱ��״̬��Ϊstop */
    g_ulNasRabmFDWaitGmmQryRsltTimer = NAS_RABM_TIMER_STATUS_STOP;

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /* ����FD����û�м��� */
        NAS_RABM_RevertFastDormEnv();
        NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_INIT);

        NAS_RABM_SndOmFastdormStatus();
    }

    return;
}


VOS_VOID NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT );

    if (NAS_RABM_FASTDORM_EXEC == NAS_RABM_GET_FD_STATUS())
    {
        /*if (��ǰ���Ը�WAS����FAST DORM)*/
        if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
        {
            /* ��WAS����RRRABM_FASTDORM_START_REQ */
            NAS_RABM_SndWasFastDormStartReq(RABM_FASTDORM_ENUM);
        }
        else
        {
            /* ������ʱ��RABM_TIMER_FASTDORM_RETRY */
            NAS_RabmStartTimer( RABM_TIMER_NAME_FD_RETRY, RABM_TIMER_FASTDORM_RETRY );
        }
    }

    NAS_RABM_SndOmFastdormStatus();
    return;
}


VOS_VOID NAS_RABM_RcvGmmMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (RABM_RELEASE_RRC_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(pstMsg);
    }

    if (RABM_FASTDORM_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmFastDormMmlProcStatusQryCnf(pstMsg);
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    if (RABM_VOICEPREFER_ENUM == pstProcStatus->stMmlProcStatus.enOptFlag)
    {
        NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(pstMsg);
    }
#endif

    return;
}


VOS_VOID NAS_RABM_RcvGmmReleaseRrcMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU    *pstProcStatus;

    pstProcStatus = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)pstMsg;

    if (VOS_TRUE == NAS_RABM_CheckGmmAndRabmStatus(pstProcStatus))
    {
        /* �����ͷ�RRC��ʶ */
        NAS_RABM_SET_FD_REL_RRC_EXEC_FLG();

        /* ��WAS����RRRABM_FASTDORM_START_REQ */
        NAS_RABM_SndWasFastDormStartReq(RABM_RELEASE_RRC_ENUM);
    }

    return;
}


VOS_VOID NAS_RABM_SndWasFastDormStartReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                              ulRet;                              /* �������VOS���ͺ����ķ���ֵ */
    RRRABM_FASTDORM_START_REQ_STRU         *pstMsg = VOS_NULL_PTR;              /* ����ԭ������ָ�� */
    RRC_FASTDORM_START_TYPE_ENUM_UINT32     enWrrFastDormStartType;


    enWrrFastDormStartType = RRC_FASTDORM_START_TYPE_BUTT;


    /* �����ڴ�  */
    pstMsg = (RRRABM_FASTDORM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_START_REQ;

    /* ��AT�Ĳ�������ת����Wrr��Ӧ�Ĳ������� */
    if (RABM_FASTDORM_ENUM == enOptFlag)
    {
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(NAS_RABM_GET_FD_OPERATION_TYPE(),
                                                        &enWrrFastDormStartType);
    }
    else
    {
        /* release rrc ����ͬʱ����FD��ASCR */
        NAS_RABM_ConvertAtFasTDormTypeToWrrFasTDormType(AT_RABM_FASTDORM_START_FD_ASCR,
                                                        &enWrrFastDormStartType);
    }

    pstMsg->enStartType                 = enWrrFastDormStartType;

    /* ����VOS����ԭ�� */
     ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStartReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}



VOS_VOID NAS_RABM_SndWasFastDormStopReq(VOS_VOID)
{
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RRRABM_FASTDORM_STOP_REQ_STRU     *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RRRABM_FASTDORM_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_FASTDORM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_FASTDORM_STOP_REQ;

    /* ����VOS����ԭ�� */
    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasFastDormStopReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}



VOS_VOID NAS_RABM_SndGmmMmlProcStatusQryReq(
    RABM_RELRRC_OPERATE_ENUM_UINT32     enOptFlag
)
{
    VOS_UINT32                                  ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU      *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_GMM_MML_PROC_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ;

    pstMsg->enOptFlag                     = enOptFlag;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmMmlProcStatusQryReq:ERROR:PS_SEND_MSG ");
        return ;
    }

}

/*lint -e958 */

VOS_VOID NAS_RABM_SndAtSetFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT����Ϣ��RABM������OpId */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
)
{
    /* ��AT�������ý�� */
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_AT_SET_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_SET_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_SET_FASTDORM_PARA_CNF;
    pstMsg->enRslt                        = enRslt;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}
/*lint +e958 */


VOS_VOID NAS_RABM_SndAtQryFastDormParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucRslt
)
{
    /* ��AT���Ͳ�ѯ��� */
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_AT_QRY_FASTDORM_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_QRY_FASTDORM_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_QRY_FASTDORM_PARA_CNF;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;
    pstMsg->ucRslt                        = ucRslt;

    pstMsg->stFastDormPara.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormPara.ulTimeLen               = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryFastDormParaCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}
VOS_VOID  NAS_RABM_SndOmFastdormStatus(VOS_VOID)
{
    NAS_RABM_LOG_FASTDORM_INFO_STRU    *pstMsg;

    pstMsg = (NAS_RABM_LOG_FASTDORM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_RABM,
                             sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_RABM_SndOmFastdormStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId           = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid               = WUEPS_PID_RABM;
    pstMsg->stMsgHeader.ulReceiverPid             = WUEPS_PID_RABM;

    pstMsg->stMsgHeader.ulLength                  = sizeof(NAS_RABM_LOG_FASTDORM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName                 = NAS_RABM_OM_MSG_FASTDORM_STATUS;
    pstMsg->stFastDormCtx.enCurrFastDormStatus    = NAS_RABM_GET_FD_STATUS();
    pstMsg->stFastDormCtx.enFastDormOperationType = NAS_RABM_GET_FD_OPERATION_TYPE();
    pstMsg->stFastDormCtx.ulUserDefNoFluxCnt      = NAS_RABM_GET_FD_USER_DEF_NOFLUX_CNT();
    pstMsg->stFastDormCtx.ulCurrNoFluxCnt         = NAS_RABM_GET_FD_CURR_NOFLUX_CNT();

    pstMsg->stFastDormCtx.ulActiveFlg             = NAS_RABM_GET_FD_ACT_FLG();
    pstMsg->stFastDormCtx.ulDlDataCnt             = NAS_RABM_GET_FD_DLDATA_CNT();
    pstMsg->stFastDormCtx.ulUlDataCnt             = NAS_RABM_GET_FD_ULDATA_CNT();

    pstMsg->aenTimerState[0]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);
    pstMsg->aenTimerState[1]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_COMMON, RABM_TIMER_FASTDORM_WAIT_GMM_QRY_RESULT);
    pstMsg->aenTimerState[2]                      = NAS_RABM_CheckTimerStatus(RABM_TIMER_NAME_FD_RETRY,RABM_TIMER_FASTDORM_RETRY);
    pstMsg->ucReserved                            = 0;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_RABM, pstMsg);

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

