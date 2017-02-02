

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlLib.h"
#include "MsccMmcInterface.h"
#include "NasMmcComFunc.h"
#include "NVIM_Interface.h"
#include "NasMmcSndLmm.h"
#include "siappstk.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MAIN_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

#if defined (__PS_WIN32_RECUR__)


VOS_VOID NAS_UTRANCTRL_ReloadFsmDesc(
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstFsmCtx,
    VOS_UINT32                          ulPcRecurFsmId
)
{
    switch ( ulPcRecurFsmId )
    {
        case NAS_UTRANCTRL_FSM_MAIN:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetMainFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_SWITCH_ON:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetSwitchOnFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_POWER_OFF:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetPowerOffFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_PLMN_SELECTION:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_SYSCFG:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetSysCfgFsmDescAddr();
            break;

        case NAS_UTRANCTRL_FSM_MODE_CHANGE:
            pstFsmCtx->pstFsmDesc       = NAS_UTRANCTRL_GetModeChangeFsmDescAddr();
            break;

        default:
            break;
    }

}



VOS_UINT32 NAS_UTRANCTRL_RestoreContextData_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_CTX_STRU                                  *pstUtranCtrlCtx;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;

    pstUtranCtrlCtx     = NAS_UTRANCTRL_GetUtranCtrlCtx();

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_UTRANCTRL_CTX_STRU);

    /*ע��״̬��*/
    NAS_UTRANCTRL_RegFsm();

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pstMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* g_stNasUtranCtrlCtxĿ���ַ */
    pucDest     = (VOS_UINT8 *)pstUtranCtrlCtx;
    ulDestLen   = sizeof(NAS_UTRANCTRL_CTX_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    pucSrc += (ulItemCount);

    NAS_UTRANCTRL_ReloadFsmDesc(NAS_UTRANCTRL_GetCurFsmAddr(), pstUtranCtrlCtx->stCurFsm.enFsmId);


    NAS_INFO_LOG(WUEPS_PID_MMC, "UTRANCTRL: NAS_UTRANCTRL_RestoreContextData_Main - data is restored.");

    return VOS_TRUE;
}

#endif  /* END OF #if defined (__PS_WIN32_RECUR__) */

VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;

    enPreUtranMode     = NAS_UTRANCTRL_GetPreUtranMode();

    /* �Զ�ģʽ�յ�WAS��Ϣ,ͳһ�л���FDDģʽ,д��NV�� */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* ���µ�ǰ�Ĺ���ģʽ */
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);
    }

    /* ģʽ���䲻֪ͨRRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ��Ϣδ������������������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �ѵ�ǰUtranModeд��NV�� */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* �����ϴη���������UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ����ModeChange״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrSysInfo;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    pstGrrSysInfo      = (GRRMM_SYS_INFO_IND_ST *)pstMsg;
    enPreUtranMode     = NAS_UTRANCTRL_GetPreUtranMode();

    /* �Զ�ģʽ�յ�GAS��Ϣ������ϵͳ��Ϣ�е�MCC�����µ�ǰģʽ��дNV */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* �����ǰ��MCC����TD��PLMN LIST�б��У�UTRAN MODEΪFDD */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(pstGrrSysInfo->PlmnId.ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_FDD;
        }
        else
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_TDD;

            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
        }

        NAS_UTRANCTRL_SetCurrUtranMode(enCurrUtranMode);
    }

    /* ģʽ���䲻֪ͨRRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ��Ϣδ������������������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �ѵ�ǰUtranModeд��NV�� */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_GetCurrUtranMode());

    /* �����ϴη���������UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ����ModeChange״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;

    enPreUtranMode   = NAS_UTRANCTRL_GetPreUtranMode();

    /* �Զ�ģʽ�յ�TDS��Ϣ��������FDD  ģʽ�л���TDDģʽ,��Ҫ���µ�ǰģʽ */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
    }

    /* ģʽ���䲻֪ͨRRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ��Ϣδ������������������ */
        return VOS_FALSE;
    }

    /* �ѵ�ǰUtranModeд��NV�� */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_UTRAN_MODE_TDD);

    /* �����ϴη���������UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ����ModeChange״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enPreUtranMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;
    MMC_LMM_PLMN_ID_STRU                stLmmPlmn;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmn;

    pstLmmSysInfoMsg = (LMM_MMC_SYS_INFO_IND_STRU*)pstMsg;
    enPreUtranMode   = NAS_UTRANCTRL_GetPreUtranMode();
    stLmmPlmn        = (pstLmmSysInfoMsg->stLteSysInfo.stSpecPlmnIdList.astSuitPlmnList[0]);

    /* ��LMM��PLMNת����GU NAS��PLMN��ʽ */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(&stLmmPlmn,
                                        &stGUNasPlmn);

    /* �Զ�ģʽ�յ�GAS��Ϣ����Ҫ���µ�ǰģʽ */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        /* �����ǰ��MCC����TD��PLMN LIST�б���,UTRAN MODEΪFDD */
        if (VOS_FALSE == NAS_MML_IsMccInDestMccList(stGUNasPlmn.ulMcc,
                                                    NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                    NAS_UTRANCTRL_GetSpecTdMccList()))
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_FDD;
        }
        else
        {
            enCurrUtranMode = NAS_UTRANCTRL_UTRAN_MODE_TDD;

            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);
        }

        NAS_UTRANCTRL_SetCurrUtranMode(enCurrUtranMode);
    }

    /* ģʽ���䲻֪ͨRRC */
    if (enPreUtranMode == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ��Ϣδ������������������ */
        return VOS_FALSE;
    }

    /* �ѵ�ǰUtranModeд��NV�� */
    NAS_UTRANCTRL_WriteUtranModeNvim(NAS_UTRANCTRL_GetCurrUtranMode());

    /* �����ϴη���������UtranMode */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ����ModeChange״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MODE_CHANGE);

    return VOS_TRUE;
}
#endif

VOS_UINT32 NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity = VOS_NULL_PTR;
    VOS_UINT8                           ucSimPresentStatus;

    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();
    ucSimPresentStatus                  = NAS_MML_GetSimPresentStatus();


    /* ������ȡ en_NV_Item_SMC_Ctrl_Flg NV�� */
    NAS_UTRANCTRL_ReadSmcCtrlFlgNvim();

    /* ������ȡ en_NV_Item_Utran_Mode_Auto_Switch NV�� */
    NAS_UTRANCTRL_ReadUtranModeAutoSwitchNvim();

    /* ������ȡ en_NV_Item_Current_Utran_Mode NV�� */
    NAS_UTRANCTRL_ReadUtranModeNvim();

    /* ����IMSI��en_NV_Item_Utran_Mode_Auto_Switch NV�������µ�ǰ��UTRAN�л�ģʽ */
    NAS_UTRANCTRL_UpdateCurUtranSwitchMode( pstMsIdentity->aucImsi,
                                            ucSimPresentStatus,
                                            NAS_UTRANCTRL_GetUtranModeAutoSwtich() );

    /* ����ʱ��֪ͨRRC��ǰ��UTRAN MODE,��ʱ��¼����,�����յ�ϵͳ��Ϣ����֪ͨ */
    NAS_UTRANCTRL_SetPreUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvPlmnSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_PLMN_SEARCH_REQ_STRU      *pstMsccPlmnSrchReq;

    pstMsccPlmnSrchReq = (MSCC_MMC_PLMN_SEARCH_REQ_STRU *)pstMsg;

    if (NAS_MSCC_PIF_ACQ_REASON_POWER_UP == pstMsccPlmnSrchReq->enAcqReason)
    {
        NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_TRUE);
    }

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvMsccAcqReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvPlmnSpecialReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_FALSE);
    }

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrStartCnfMsg;

    pstRrStartCnfMsg = (RRMM_START_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasStartCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ���Ϳ�����Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* ��UTRANģ�鿪��ʧ�ܣ���ֱ�ӽ�MMC״̬�����д��� */
        return VOS_FALSE;
    }

    /* �л�������ģ��Ŀ���״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SWITCH_ON);

    /* WAS�Ŀ����ظ���Ϣ������ģ��Ŀ���״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��������ʧ����Ϣ����ԭMMC״̬�����д��� */
    RRMM_START_CNF_STRU                *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main: ENTERED");

    /* �����ڴ� */
    pstTempMsg = (RRMM_START_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main: Alloc memeory Error");
        return VOS_FALSE;
    }

    /* ���쿪���ظ�ʧ����Ϣ */
    NAS_UTRANCTRL_BuildRrMmStartCnfMsg(WUEPS_PID_WRR,
                                       WUEPS_PID_MMC,
                                       MMC_START_FAILURE,
                                       pstTempMsg);

    /* ȡ�õ�ǰ������Ϣ������ */
    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* �����Ĺ��ĳ�ʱ��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ͷ��������Ϣ */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTdStartCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                *pstRrStartCnfMsg;

    pstRrStartCnfMsg = (RRMM_START_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdStartCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ���Ϳ�����Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* ��UTRANģ�鿪��ʧ�ܣ���ֱ�ӽ�MMC״̬�����д��� */
        return VOS_FALSE;
    }

    /* �л�������ģ��Ŀ���״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SWITCH_ON);

    /* TD�Ŀ����ظ���Ϣ������ģ��Ŀ���״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��������ʧ����Ϣ����ԭMMC״̬�����д��� */
    RRMM_START_CNF_STRU                *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main: ENTERED");

    /* �����ڴ�  */
    pstTempMsg = (RRMM_START_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main: Alloc memeory Error");
        return VOS_FALSE;

    }

    /* ���쿪���ظ�ʧ����Ϣ */
    NAS_UTRANCTRL_BuildRrMmStartCnfMsg(WUEPS_PID_WRR,
                                       WUEPS_PID_MMC,
                                       MMC_START_FAILURE,
                                       pstTempMsg);

    /* ȡ�õ�ǰ������Ϣ������ */
    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* �����Ĺ��ĳ�ʱ��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ͷ��������Ϣ */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPowerOffCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ���͹ػ���Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF);

    /* �л�������ģ��Ĺػ�״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Was�Ĺػ��ظ���Ϣ������ģ��Ĺػ�״̬�����д���  */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main: ENTERED");

    /* �����ǰΪUTRAN MODE AUTO SWITCHģʽ������Ҫ����UTRANCTRLģ��Ĺػ�״̬�� */
    /* �л�������ģ��Ĺػ�״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Was�Ĺػ��ظ���Ϣ������ģ��Ĺػ�״̬�����д���  */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPowerOffCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ���͹ػ���Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF);

    /* �л�������ģ��Ĺػ�״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* td�Ĺػ��ظ���Ϣ������ģ��Ĺػ�״̬�����д���  */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main: ENTERED");

    /* �л�������ģ��Ĺػ�״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_POWER_OFF);

    /* Td�Ĺػ��ظ���Ϣ������ģ��Ĺػ�״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasSysCfgCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf;

    pstSysCfgCnf = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasSysCfgCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ����SYSCFG������Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF);

    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        /* ��syscfg����ʧ�ܣ���ֱ�ӽ�MMC״̬�����д��� */
        return VOS_FALSE;
    }

    /* ��syscfg���ûظ��ɹ����л�������ģ���SYSCFG״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SYSCFG);

    /* Was��SYSCFG�ظ���Ϣ������ģ���SYSCFG״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main: ENTERED");

    /* ����SYSCFG����ʧ����Ϣ����ԭMMC״̬�����д��� */
    pstTempMsg = (RRMM_SYS_CFG_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main: Alloc memeory Error");
        return VOS_TRUE ;
    }

    /* ����SYSCFG���ûظ���Ϣ */
    NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(WUEPS_PID_WRR,
                                        WUEPS_PID_MMC,
                                        RRMM_SYS_CFG_RESULT_FAILURE,
                                        pstTempMsg);

    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* �����Ĺ��ĳ�ʱ��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ͷ��������Ϣ */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTdSysCfgCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstSysCfgCnf;

    pstSysCfgCnf = (RRMM_SYS_CFG_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵȿ����ظ�ʱ״̬��ʱ����������Ϊ�쳣 */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF))
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdSysCfgCnf_Main: Unexpected Plmnsrch msg!");

        /* �������쳣��Ϣ */
        return VOS_TRUE;
    }

    /* ֹͣMMCͨ��UTRANCTRLģ���UTRANģ����SYSCFG������Ϣʱ����Ķ�ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF);

    if ( RRMM_SYS_CFG_RESULT_FAILURE == pstSysCfgCnf->ulResult)
    {
        /* ��syscfg����ʧ�ܣ���ֱ�ӽ�MMC״̬�����д��� */
        return VOS_FALSE;
    }

    /* �л�������ģ���SYSCFG״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_SYSCFG);

    /* Td��SYSCFG�ظ���Ϣ������ģ���SYSCFG״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_CFG_CNF_STRU              *pstTempMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulTempMsgEventType;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main: ENTERED");

    /* ����SYSCFG����ʧ����Ϣ����ԭMMC״̬�����д��� */
    pstTempMsg = (RRMM_SYS_CFG_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_CNF_STRU));
    if( VOS_NULL_PTR == pstTempMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main: Alloc memeory Error");
        return VOS_TRUE ;
    }

    /* ����SYSCFG���ûظ���Ϣ */
    NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(WUEPS_PID_WRR,
                                        WUEPS_PID_MMC,
                                        RRMM_SYS_CFG_RESULT_FAILURE,
                                        pstTempMsg);

    ulTempMsgEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstTempMsg );

    /* �����Ĺ��ĳ�ʱ��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulTempMsgEventType,
                                           (struct MsgCB *)pstTempMsg);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ͷ��������Ϣ */
    PS_MEM_FREE(WUEPS_PID_MMC, pstTempMsg);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    VOS_UINT32                          ulExistHongKongMcc;
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    VOS_UINT8                           ucSwitchOnPlmnSearchFlag;

    enUtranMode                 = NAS_UTRANCTRL_GetCurrUtranMode();
    ulExistHongKongMcc          = VOS_FALSE;
    ucRoamPlmnSelectionSortFlg  = NAS_MMC_GetRoamPlmnSelectionSortActiveFlg();
    ucSwitchOnPlmnSearchFlag    = NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag();

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵ�ָ�������ظ�ʱ״̬��ʱ��������ֹͣ��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
    }

    /* ��Ȧ���Ӷ� */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_WCDMA, pstSrchCnfMsg))
    {
        /* ������� */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ�£�CSFB��־����ʱ�����ҵ�ǰ��FDDģʽ��������TD */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranMode))
    {
        /* ������������������Ϣ */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* ָ������ʧ�ܸ��������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }


    ulExistHongKongMcc = NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList(NAS_UTRANCTRL_HONGKONG_MCC, &(pstSrchCnfMsg->PlmnIdList));

    if ((NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
     && (VOS_FALSE == ulExistHongKongMcc)
     && (VOS_TRUE == ucRoamPlmnSelectionSortFlg)
     && (VOS_TRUE == ucSwitchOnPlmnSearchFlag)
     && ((pstSrchCnfMsg->PlmnIdList.ulHighPlmnNum != 0)
      || (pstSrchCnfMsg->PlmnIdList.ulLowPlmnNum != 0)))
    {
        /* �����������������was���������û��һ������mcc��tds mcc�б����Ҳ�����������磬�Ҹߵ��������������ȫΪ0��
           ������tds�������������*/
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* �л�������ģ���ѡ��״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* was�������ظ���Ϣ������ģ���ѡ��״̬�����д���  */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �����ǰUTRANCTRLģ�ĵ�ָ�������ظ�ʱ״̬��ʱ��������ֹͣ��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
    }

    /* ����utran modeΪfdd��utranctrl ����״̬���˳�����Ϣ��mmc��������֪ͨ���������mmc���� */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* ֪ͨmmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF*/
    NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg();

    return VOS_TRUE;

}
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������TD���Ͳ���Ҫ��״̬���������ѵ�TD search cnf��ʱ�������W */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
    {
        return VOS_TRUE;
    }
    
    /* SKIP Wʱ�������õ�ǰΪTDDģʽ */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

    /* �л�������ģ���ѡ��״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* was�������ظ���Ϣ������ģ���ѡ��״̬�����д���  */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* SKIP TDSʱ�������õ�ǰΪFDDģʽ */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* �л�������ģ���ѡ��״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* tds�������ظ���Ϣ������ģ���ѡ��״̬�����д���  */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main: ENTERED");

    /* CSFB��־����ʱ�����ҵ�ǰ��FDDģʽ��������TD */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranMode))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                        WUEPS_PID_MMC,
                                                        NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                       (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ��ǰ��Ϣ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰΪUTRAN MODE AUTO SWITCHģʽ������Ҫ����UTRANCTRLģ�������״̬�� */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode() )
    {
        /* �л�������ģ���ѡ��״̬�����д��� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* ���������ѡ��״̬������  */
        return VOS_TRUE;
    }

    /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

    /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
    pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵ������ظ�ʱ״̬��ʱ�����У���ֹͣ��ʱ�� */
    if ( NAS_MMC_TIMER_STATUS_RUNING != NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        /* ��ǰ��Ϣ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* WAS����ʱ����㸴λ����TDģ */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);


    /* ���ԭ��ΪNO RF�������MMC״̬�����д��� */
    if ( RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        return VOS_FALSE;
    }

    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode() )
    {
        /* �л�������ģ���ѡ��״̬�����д��� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* ��ǰ��Ϣ���������ѡ��״̬������ */
        return VOS_TRUE;
    }

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvGasPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ��Ȧ���Ӷ� */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_GSM, pstSrchCnfMsg))
    {
        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    /* ����״̬������ */
    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg;
    RRC_PLMN_ID_LIST_STRU                                  *pstGuPlmnIdList;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ��ȡ������utranctrl����Ҫ�������Ϣ�򳡾������ں����� */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_LTE, pstLmmSrchCnfMsg))
    {
        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    pstGuPlmnIdList   = (RRC_PLMN_ID_LIST_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                                    sizeof(RRC_PLMN_ID_LIST_STRU));
    if (VOS_NULL_PTR == pstGuPlmnIdList)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main:Invalid pstGuPlmnIdList");
        return VOS_FALSE;
    }

    /*ת��L��ʽ�������б��ΪGU��ʽ��*/
    NAS_MMC_ConvertLmmPlmnIdListToGUFormat_PlmnList(&(pstLmmSrchCnfMsg->stPlmnIdList), pstGuPlmnIdList);

    /* ���������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             pstGuPlmnIdList);

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pstGuPlmnIdList);

    /* ����MMC״̬������ */
    return VOS_FALSE;
}
#endif


VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();

    pstSrchCnfMsg   = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* �����ǰUTRANCTRLģ�ĵ�ָ�������ظ�ʱ״̬��ʱ��������ֹͣ��ʱ�� */
    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
    {
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);
    }

    /* ��Ȧ���Ӷ� */
    if (VOS_FALSE == NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(NAS_MML_NET_RAT_TYPE_WCDMA, pstSrchCnfMsg))
    {
        /* ������������������Ϣ */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ�£�CSFB��־����ʱ�����ҵ�ǰ��TDDģʽ��������W */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranMode))
    {
        /* ������������������Ϣ */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_TRUE == NAS_MMC_GetUtranSkipWPlmnSearchFlag())
     && (VOS_TRUE == ulIsOtherModemPlmnInTdMccList))
    {
        /* ���������פ���й�����������w���磬������������������Ϣ */
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();

        /* ����MMC״̬������ */
        return VOS_FALSE;
    }

    /* �л�������ģ���ѡ��״̬�����д��� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

    /* tdrrc�������ظ���Ϣ������ģ���ѡ��״̬�����д��� */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstBufferEntryMsg = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_SWITCH_MODE_ENUM_UINT8              enCurUtranSwitchMode;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                     enUtranMode;

    enUtranMode       = NAS_UTRANCTRL_GetCurrUtranMode();

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    enCurUtranSwitchMode = NAS_UTRANCTRL_GetCurUtranSwitchMode();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main: ENTERED");

    /* �Զ��л�ģʽ�£�CSFB��־����ʱ�����ҵ�ǰ��TDDģʽ��������W */
    if ((VOS_TRUE                       == NAS_MML_IsCsfbServiceStatusExist())
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranMode))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ��ǰ��Ϣ�������MMC״̬������ */
        return VOS_FALSE;
    }



    /* �����ǰΪUTRAN MODE AUTO SWITCHģʽ������Ҫ����UTRANCTRLģ�������״̬�� */
    if ( (VOS_TRUE != NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      && (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == enCurUtranSwitchMode) )
    {
        /* �л�������ģ���ѡ��״̬�����д��� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_PLMN_SELECTION);

        /* ���������ѡ��״̬������ */
        return VOS_TRUE;
    }

    /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                               (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

    /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
    pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_FALSE);
    }

    NAS_UTRANCTRL_SetSwithOnPlmnSearchFlag(VOS_FALSE);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}





VOS_UINT32 NAS_UTRANCTRL_RcvTiHplmnTimerExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiTryingHighPrioPlmnSearchExpired_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}


/*lint -restore */


#endif  /* END OF #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
