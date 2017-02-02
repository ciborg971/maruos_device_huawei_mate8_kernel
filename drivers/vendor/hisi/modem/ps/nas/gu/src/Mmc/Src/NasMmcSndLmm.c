
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "NasComm.h"
#include "NasMmcComFunc.h"

#include "MsccMmcInterface.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#include "NasMmcSndLmm.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "asnasapi.h"
#include "NasMmlLib.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "NasMmlMsgProc.h"
#include "MmcLmmInterface.h"
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#include "NasUtranCtrlCommFunc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_LMM_C


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */


#if (FEATURE_ON == FEATURE_LTE)

enum NAS_MMC_LMM_START_RAT_MASK{

    NAS_MMC_LMM_START_GSM_MASK          = (0x01),
    NAS_MMC_LMM_START_WCDMA_MASK        = (0x02),
    NAS_MMC_LMM_START_LTE_FDD_MASK      = (0x04),
    NAS_MMC_LMM_START_LTE_TDD_MASK      = (0x08),
    NAS_MMC_LMM_START_MASK_BUTT

};
VOS_VOID NAS_MMC_SndLmmStopReq( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_STOP_REQ_STRU              *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->ulMsgId          = ID_MMC_LMM_STOP_REQ;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopReq:ERROR:PS_SEND_MSG FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    (VOS_VOID)vos_printf("NAS_MMC_SndLmmStopReq, tick = 0x%x\r\n ", VOS_GetSlice());

    NAS_TRACE_HIGH("Snd poweroff req to LMM!");

    return;
}


VOS_VOID NAS_MMC_SndLmmUsimStatusReq(
    MMC_LMM_USIM_STATUS_ENUM_UINT32     enUsimState
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_USIM_STATUS_REQ_STRU*       pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_USIM_STATUS_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_USIM_STATUS_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_USIM_STATUS_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUsimStatusReq:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_USIM_STATUS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_USIM_STATUS_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->ulUsimState                 = enUsimState;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUsimStatusReq:ERROR: SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}





VOS_VOID NAS_MMC_SndLmmPlmnAnyCellSrchReq(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnAnyCellSrchReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;
    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_ANY;

    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
     {
         NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnAnyCellSrchReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
     }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmPlmnListReq(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnListReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;
    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_LIST;

    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnListReq():WARNING:SEND LMM PLMN list SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmSuspendReq(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_SUSPEND_REQ_STRU           *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_SUSPEND_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_SUSPEND_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_SUSPEND_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}




VOS_VOID NAS_MMC_SndLmmPlmnSrchStopReq( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_STOP_PLMN_SRCH_REQ_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_STOP_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
        pstMsg = (MMC_LMM_STOP_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnSrchStopReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_STOP_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_STOP_PLMN_SRCH_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmPlmnSrchStopReq():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmStartReq(VOS_VOID)
{
    MMC_LMM_START_REQ_STRU             *pstMsg     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                        sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_START_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_START_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStartReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET(((VOS_UCHAR *)pstMsg) + VOS_MSG_HEAD_LENGTH, 0,
                                         sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_START_REQ;

    pstMsg->enUtranMode     = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(NAS_UTRANCTRL_GetCurrUtranMode());

    /* ��ȡ��״̬ */
    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        pstMsg->ulUsimState             = MMC_LMM_USIM_VALID;
    }
    else
    {
        pstMsg->ulUsimState             = MMC_LMM_USIM_INVALID;
    }

    /* ȡ�ý������ȼ��б� */
    pstRatList  = NAS_MML_GetMsPrioRatList();

    /* ���ý���ģʽ */
    pstMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, pstRatList);
    pstMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, pstRatList);
    pstMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, pstRatList);

    /* �����֧�ֵ�3GPP2���뼼��pstMsg->aucRatPrioList[3]��дΪ1X�����ȼ�RRMM_RAT_PRIO_LOW */
    if (VOS_TRUE == NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_CDMA1X, NAS_MML_GetMs3Gpp2PrioRatList()))
    {
        pstMsg->aucRatPrioList[3]          = RRMM_RAT_PRIO_LOW;
    }
    /* ����pstMsg->aucRatPrioList[3]��дΪRRMM_RAT_PRIO_NULL */
    else
    {
        pstMsg->aucRatPrioList[3]          = RRMM_RAT_PRIO_NULL;
    }

    /* �����֧�ֵ�3GPP2���뼼��pstMsg->aucRatPrioList[4]��дΪHRPD�����ȼ�RRMM_RAT_PRIO_MIDDLE */
    if (VOS_TRUE == NAS_MML_IsSpec3Gpp2RatInRatList(NAS_MML_3GPP2_RAT_TYPE_HRPD, NAS_MML_GetMs3Gpp2PrioRatList()))
    {
        pstMsg->aucRatPrioList[4]          = RRMM_RAT_PRIO_MIDDLE;
    }
    /* ����pstMsg->aucRatPrioList[4]��дΪRRMM_RAT_PRIO_NULL */
    else
    {
        pstMsg->aucRatPrioList[4]          = RRMM_RAT_PRIO_NULL;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStartReq():WARNING:SEND LMM START REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif
    (VOS_VOID)vos_printf("NAS_MMC_SndLmmStartReq, tick = 0x%x\r\n ", VOS_GetSlice());

    return;
}


VOS_VOID NAS_MMC_BuildSndLmmEquPlmnInfo(
     NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    NAS_MML_PLMN_ID_STRU                                    astUniquePlmnList[NAS_MML_MAX_EQUPLMN_NUM];          /* ɾ���ظ�����EquPLMN�б� */
    VOS_UINT32                                              aulComparedMcc[NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER]; /*����LTE���ε�MCC�б�*/
    VOS_UINT8                                               ucSndEplmnNum;
    VOS_UINT8                                               ucEmcPdpStatusFlg;
    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                *pstDisabledRatPlmnCfg = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;

    NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU                 stDisabledRatPlmnCfg;               /* ��ֹ���뼼����PLMN�������� */
    VOS_UINT32                                              i;

    PS_MEM_SET(astUniquePlmnList, 0x00, sizeof(astUniquePlmnList));
    PS_MEM_SET(aulComparedMcc, 0x00, sizeof(aulComparedMcc));
    PS_MEM_SET(&stDisabledRatPlmnCfg, 0, sizeof(NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU));

    ucEmcPdpStatusFlg = NAS_MML_GetEmcPdpStatusFlg();


    /* ��ȡ��ֹ���뼼����PLMN��Ϣ */
    pstDisabledRatPlmnCfg = NAS_MML_GetDisabledRatPlmnInfo();

    /* ��ȡ��Ӫ�̶��Ƶ�MCC�б� */
    NAS_MML_GetRoamEnabledMccList(aulComparedMcc);

    /* ��ȡforbidden�б� */
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    ucSndEplmnNum   = pstEquPlmnInfo->ucEquPlmnNum;
    PS_MEM_CPY(astUniquePlmnList, pstEquPlmnInfo->astEquPlmnAddr, ucSndEplmnNum * sizeof(NAS_MML_PLMN_ID_STRU));

    /* ���б���ɾ���ظ������� */
    NAS_MMC_DelDuplicatedPlmnInPlmnList(&ucSndEplmnNum, astUniquePlmnList);


    /* ʹ�ý�ֹ���뼼�������б�ǰ���ж����Ƿ��гͷ�ʱ�䵽�����磬�������ɾ�� */
    (VOS_VOID)NAS_MML_DeleteExpireValidPeriodPlmnInDisabledRatPlmnList();

    PS_MEM_SET(&stDisabledRatPlmnCfg, 0X00, sizeof(NAS_MML_DISABLED_RAT_PLMN_CFG_INFO_STRU));

    /* �ӳͷ�PLMN��ɾ���ܾ�15������ */
    for ( i = 0 ; i < pstDisabledRatPlmnCfg->ulDisabledRatPlmnNum; i++ )
    {
        if (MMC_LMM_DISABLE_LTE_REASON_LMM_NOTIFY_EUTRAN_NOT_ALLOW != pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i].enDisableLteReason)
        {
            PS_MEM_CPY(&stDisabledRatPlmnCfg.astDisabledRatPlmnId[stDisabledRatPlmnCfg.ulDisabledRatPlmnNum],
                       &(pstDisabledRatPlmnCfg->astDisabledRatPlmnId[i]),
                       sizeof(NAS_MML_DISABLED_PLMN_WITH_FORBIDDEN_PERIOD_STRU));

            stDisabledRatPlmnCfg.ulDisabledRatPlmnNum++;
        }
    }



    /* ����PDN���Ӳ�����ʱ����Ҫɾ��forbidden plmn\forbidden plmn for gprs\disabled rat plmn�б��EPLMN */
    if (VOS_FALSE == ucEmcPdpStatusFlg)
    {
        /* ���б���ɾ��������LTE���ε����� */
        NAS_MML_DelEqualPlmnNotInAllowLteRoamMccList(&ucSndEplmnNum, astUniquePlmnList, NAS_MML_ROAM_ENABLED_MAX_MCC_NUMBER, aulComparedMcc);

        /* ɾ����ֹ��EPLMN������forb plmn, ����������PLMN, ���������ε�plmn, ����Ч�� */
        NAS_MML_DelForbPlmnInPlmnList(&ucSndEplmnNum, astUniquePlmnList);

        /* ɾ��forb plmn for gprs */
        NAS_MML_DelPlmnsInRefList(&ucSndEplmnNum, astUniquePlmnList,
                       pstForbidPlmnInfo->ucForbGprsPlmnNum, pstForbidPlmnInfo->astForbGprsPlmnList);


        /* ɾ���ڽ�ֹ���뼼����PLMN�б��е�EPLMN */
        NAS_MML_DelEqualPlmnsInDisableRatList(&ucSndEplmnNum,
                                              astUniquePlmnList,
                                              NAS_MML_NET_RAT_TYPE_LTE,
                                              stDisabledRatPlmnCfg.ulDisabledRatPlmnNum,
                                              stDisabledRatPlmnCfg.astDisabledRatPlmnId);

    }

    pstEquPlmnInfo->ucEquPlmnNum = ucSndEplmnNum;
    PS_MEM_CPY(pstEquPlmnInfo->astEquPlmnAddr, astUniquePlmnList, ucSndEplmnNum * sizeof(NAS_MML_PLMN_ID_STRU));

    return;
}




VOS_VOID NAS_MMC_SndLmmEquPlmnReq(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
)
{
    VOS_UINT32                          i;
    MMC_LMM_EPLMN_NOTIFY_REQ_STRU      *pstLmmEquPlmnStru = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstLmmEquPlmnStru = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmEquPlmnStru = (MMC_LMM_EPLMN_NOTIFY_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU));
#endif

    /* �������ڴ����,����ʧ�� */
    if ( VOS_NULL_PTR == pstLmmEquPlmnStru )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstLmmEquPlmnStru + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstLmmEquPlmnStru->ulReceiverPid   = PS_PID_MM;
    pstLmmEquPlmnStru->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLmmEquPlmnStru->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLmmEquPlmnStru->ulSenderPid     = WUEPS_PID_MMC;
    pstLmmEquPlmnStru->ulMsgId         = ID_MMC_LMM_EPLMN_NOTIFY_REQ;
    pstLmmEquPlmnStru->ulLength        = sizeof(MMC_LMM_EPLMN_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ���Eplmn,ת��ΪLMM�ĸ�ʽ */
    pstLmmEquPlmnStru->ulEplmnNum = pstEquPlmnInfo->ucEquPlmnNum;

    for ( i = 0 ; i < pstEquPlmnInfo->ucEquPlmnNum ; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmEquPlmnStru->astEplmnList[i]),
                                          &(pstEquPlmnInfo->astEquPlmnAddr[i]));
    }
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmEquPlmnStru ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstLmmEquPlmnStru);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstLmmEquPlmnStru);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmLocalDetachIndActionResultReq(
    MMC_LMM_GU_LOCAL_DETACH_TYPE_ENUM_UINT32                ulLocalDetachType
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
              sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLocalDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->enActionType                = MMC_LMM_ACTION_LOCAL_DETACH;
    pstMsg->bitOpLocalDetachType        = VOS_TRUE;
    pstMsg->ulLocalDetachType           = ulLocalDetachType;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;
    pstMsg->bitOpReqDomain              = VOS_TRUE;
    pstMsg->bitOpRstDomain              = VOS_TRUE;
    pstMsg->ulReqDomain                 = MMC_LMM_PS_ONLY;
    pstMsg->ulRstDomain                 = MMC_LMM_PS_ONLY;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLocalDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmMoDetachIndActionResultReq(
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  ulMoDetachType
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
              sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMoDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;
    pstMsg->enActionType                = MMC_LMM_ACTION_MO_DETACH;
    pstMsg->bitOpMoDetachType           = VOS_TRUE;
    pstMsg->ulMoDetachType              = ulMoDetachType;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;

    if (MMC_LMM_MO_DET_PS_ONLY == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
        pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
    }
    else if (MMC_LMM_MO_DET_CS_ONLY == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_IMSI_ONLY;
        pstMsg->ulRstDomain    = MMC_LMM_IMSI_ONLY;
    }
    else if(MMC_LMM_MO_DET_CS_PS == ulMoDetachType)
    {
        pstMsg->bitOpReqDomain = VOS_TRUE;
        pstMsg->bitOpRstDomain = VOS_TRUE;
        pstMsg->ulReqDomain    = MMC_LMM_COMBINED_PS_IMSI;
        pstMsg->ulRstDomain    = MMC_LMM_COMBINED_PS_IMSI;
    }
    else
    {
    }
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMoDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmMtDetachIndActionResultReq(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMtDetachIndActionResultReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(enMtType, enCnCause, pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmMtDetachIndActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmRegActionResultReq(
    NAS_MMC_GU_ACTION_RSLT_INFO_STRU   *pstGuActionRslt
)
{
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg = VOS_NULL_PTR;
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnRejCause;
    MMC_LMM_DOMAIN_ENUM_UINT32          enLmmDomain;
    MMC_LMM_ACTION_TYPE_ENUM_UINT32     enActionType;

    /* �ж�Action�����Ƿ���ȷ */
    if ( VOS_OK != NAS_MMC_FormatProcTypeToLmm(pstGuActionRslt->enProcType, &enActionType))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():NAS_MMC_FormatProcTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ACTION_RESULT_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    /* ��ʼ���ڴ� */
    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ucCnCause = NAS_EMM_CAUSE_BUTT;


    /* �����Ϣ�������� */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_ACTION_RESULT_REQ;

    pstMsg->ulOpId                          = 0;
    pstMsg->bitOpAtmpCnt                    = VOS_TRUE;

    pstMsg->ulAttemptCount                  = pstGuActionRslt->ulAttemptCount;
    pstMsg->ulMtDetachType                  = MMC_LMM_MT_DETACH_TYPE_BUTT;
    pstMsg->enActionType                    = enActionType;

    /* ��ȡע���� */
    NAS_MMC_ConvertGuRsltToLmmFormat(pstGuActionRslt->enRegRst,
                                     pstGuActionRslt->enCnCause,
                                     &(pstMsg->ulActRst));


    /* ��ȡע��ԭ��ֵ */
    if ( VOS_OK == NAS_MMC_ConvertMmCauseToEmmCause(pstGuActionRslt->enCnCause, &enCnRejCause) )
    {
        pstMsg->bitOpCnCause                = VOS_TRUE;
        pstMsg->ucCnCause                   = enCnRejCause;
    }

    if ( VOS_OK == NAS_MMC_ConverCnDomainToLmm(pstGuActionRslt->enReqDomain, &enLmmDomain) )
    {
        pstMsg->bitOpReqDomain              = VOS_TRUE;
        pstMsg->ulReqDomain                 = enLmmDomain;
    }

    if ( VOS_OK == NAS_MMC_ConverCnDomainToLmm(pstGuActionRslt->enRstDomain, &enLmmDomain) )
    {
        pstMsg->bitOpRstDomain              = VOS_TRUE;
        pstMsg->ulRstDomain                 = enLmmDomain;
    }

    /* ���CS update״̬��Lai�Ƿ�ı��־ */
    NAS_MMC_FillCsRegInfoInLmmActionRslt(pstMsg);

    /* ���PS update״̬��Rai�Ƿ�ı��־ */
    NAS_MMC_FillGprsRegInfoInLmmActionRslt(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRegActionResultReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmRelReq( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_REL_REQ_STRU               *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_REL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_REL_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRelReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_REL_REQ;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmRelReq,ERROR:SNED MSG FAIL!");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmAttachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulAttachType,
    NAS_MSCC_PIF_EPS_ATTACH_REASON_ENUM_UINT32              enEpsAttachReason
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_ATTACH_REQ_STRU            *pstMsg = VOS_NULL_PTR;

    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32    enAttachType;

    if ( VOS_OK != NAS_MMC_ConvertAttachTypeToLmm(ulAttachType, &enAttachType) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmAttachReq():NAS_MMC_ConvertAttachTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ATTACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ATTACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ATTACH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                    sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ATTACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ATTACH_REQ;
    pstMsg->ulOpId                      = ulOpId;
    pstMsg->ulAttachType                = enAttachType;

    pstMsg->ulAttachReason              = enEpsAttachReason;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmAttachReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmDetachReq(
    VOS_UINT32                                              ulOpId,
    VOS_UINT32                                              ulDetachType,
    NAS_MSCC_PIF_DETACH_REASON_ENUM_UINT32                  enDetachReason
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_DETACH_REQ_STRU            *pstMsg = VOS_NULL_PTR;
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32  enLmmDetachType;

    if ( VOS_OK != NAS_MMC_ConvertDetachTypeToLmm(ulDetachType, &enLmmDetachType) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDetachReq():NAS_MMC_ConvertDetachTypeToLmm:RETURNS FAILURE");

        return;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_DETACH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_DETACH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_DETACH_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_DETACH_REQ;
    pstMsg->ulOpId                      = ulOpId;
    pstMsg->ulDetachType                = enLmmDetachType;

    if (NAS_MSCC_PIF_DETACH_REASON_3GPP2_ATTACHED == enDetachReason)
    {
        pstMsg->ulDetachReason = MMC_LMM_DETACH_RESEAON_NON_3GPP_ATTACH;
    }
    else
    {
        pstMsg->ulDetachReason = MMC_LMM_DETACH_RESEAON_NULL;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDetachReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}



VOS_VOID NAS_MMC_SndLmmResumeNotify( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_RESUME_NOTIFY_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_RESUME_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_RESUME_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_RESUME_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmResumeNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_RESUME_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_RESUME_NOTIFY;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmResumeNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmSuspendRsp(
    VOS_UINT32                          ulRst
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_SUSPEND_RSP_STRU           *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_SUSPEND_RSP_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_SUSPEND_RSP_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_RSP_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRsp():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_SUSPEND_RSP;
    pstMsg->ulOpId                      = 0;
    pstMsg->ulRst                       = ulRst;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRsp():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID NAS_MMC_SetRatPriorityInCLMode(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrderList,
    RRMM_RAT_PRIO_ENUM_UINT8           *pstPriorityList
)
{
    VOS_UINT32                          ucHrpdRatSupp;

    ucHrpdRatSupp = NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD, pstRatOrderList);

    if ((VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_1X, pstRatOrderList))
     || (VOS_TRUE == ucHrpdRatSupp))
    {
        /* ����CLģʽ�������LTE������LTEΪHIGH�����������ظ�low��middle���� */
        if (VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_LTE, pstRatOrderList))
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_LTE) = RRMM_RAT_PRIO_HIGH;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_LTE) = RRMM_RAT_PRIO_NULL;
        }

        if (VOS_TRUE == NAS_MML_IsSpecRatInRatList(NAS_MSCC_PIF_NET_RAT_TYPE_1X, pstRatOrderList))
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_1X) = RRMM_RAT_PRIO_LOW;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_1X) = RRMM_RAT_PRIO_NULL;
        }

        if (VOS_TRUE == ucHrpdRatSupp)
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_HRPD) = RRMM_RAT_PRIO_MIDDLE;
        }
        else
        {
            *(pstPriorityList + NAS_MSCC_PIF_NET_RAT_TYPE_HRPD) = RRMM_RAT_PRIO_NULL;
        }
    }
}
#endif
VOS_VOID  NAS_MMC_SndLmmSyscfgReq(
    MSCC_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stRatList;

    /* ����ԭ������ָ�� */
    MMC_LMM_SYS_CFG_REQ_STRU           *pstSndLmmSysCfgMsg  = VOS_NULL_PTR;

    PS_MEM_SET(&stRatList, 0, sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstSndLmmSysCfgMsg = (MMC_LMM_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstSndLmmSysCfgMsg = (MMC_LMM_SYS_CFG_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SYS_CFG_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstSndLmmSysCfgMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSyscfgReq,ERRORALLOC MEM MMC_LMM_SYS_CFG_REQ_STRU FAIL");
        return ;
    }

    PS_MEM_SET( (VOS_INT8*)pstSndLmmSysCfgMsg + VOS_MSG_HEAD_LENGTH, 0X0,
                sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstSndLmmSysCfgMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstSndLmmSysCfgMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstSndLmmSysCfgMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstSndLmmSysCfgMsg->ulReceiverPid                   = PS_PID_MM;
    pstSndLmmSysCfgMsg->ulLength                        = sizeof(MMC_LMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndLmmSysCfgMsg->ulMsgId                         = ID_MMC_LMM_SYS_CFG_REQ;
    pstSndLmmSysCfgMsg->ulOpId                          = 0;

    /* ����OPTΪVOS_TRUE */
    pstSndLmmSysCfgMsg->bitOpBand                       = VOS_TRUE;
    pstSndLmmSysCfgMsg->bitOpRat                        = VOS_TRUE;

    /* ����Ƶ����Ϣ */
    PS_MEM_CPY( &(pstSndLmmSysCfgMsg->stBand.stLteBand ),
                &(pstSysCfgSetParm->stBand.stLteBand),
                sizeof(LTE_BAND_STRU) );

    pstSndLmmSysCfgMsg->stBand.stWcdmaBand.ulWcdmaBand = pstSysCfgSetParm->stBand.unWcdmaBand.ulBand;
    pstSndLmmSysCfgMsg->stBand.stGsmBand.ulGsmBand     = pstSysCfgSetParm->stBand.unGsmBand.ulBand;

    pstSndLmmSysCfgMsg->stBand.stCdmaBand.ulCdmaBand   = pstSysCfgSetParm->stBand.unCdmaBand.ulCdmaBand;
    /* ���ý���ģʽ */
    PS_MEM_CPY(&stRatList, &(pstSysCfgSetParm->stRatPrioList), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    pstSndLmmSysCfgMsg->aucRatPrioList[0]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_GSM, &stRatList);
    pstSndLmmSysCfgMsg->aucRatPrioList[1]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_WCDMA, &stRatList);
    pstSndLmmSysCfgMsg->aucRatPrioList[2]              = NAS_MMC_GetSpecRatPrio(NAS_MML_NET_RAT_TYPE_LTE, &stRatList);

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    pstSndLmmSysCfgMsg->enUtranMode = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(NAS_UTRANCTRL_GetPreUtranMode());
#else
    pstSndLmmSysCfgMsg->enUtranMode = MMC_LMM_UTRAN_MODE_FDD;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ���CDMA֧�֣������CLģʽ�£���Ҫ�����޸�RAT���ȼ� */
    NAS_MMC_SetRatPriorityInCLMode(&stRatList, &pstSndLmmSysCfgMsg->aucRatPrioList[0]);
#endif

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstSndLmmSysCfgMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrMmCellSelReq():ERROR:SEND MESSAGE FAILURE");
        return ;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndLmmSysCfgMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstSndLmmSysCfgMsg);
#endif

    return ;
}
VOS_VOID  NAS_MMC_SndLmmDisableLteNotify(
    MMC_LMM_DISABLE_LTE_REASON_ENUM_UINT32                  enDisableLteReason
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_DISABLE_LTE_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_DISABLE_LTE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_DISABLE_LTE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDisableLteNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_DISABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_DISABLE_LTE_NOTIFY;
    pstMsg->ulOpId                          = 0;
    pstMsg->enDisableLteReason              = enDisableLteReason;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmDisableLteNotify():WARNING:SEND LMM disable lte notify FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID  NAS_MMC_SndLmmEnableLteNotify(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_ENABLE_LTE_NOTIFY_STRU     *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_ENABLE_LTE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_ENABLE_LTE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEnableLteNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    pstMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                     = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_ENABLE_LTE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_ENABLE_LTE_NOTIFY;
    pstMsg->ulOpId                          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEnableLteNotify():WARNING:SEND LMM enbale lte notify FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmCsConnStatusNotify(
    VOS_UINT8                           ucCsRrConnStatusFlg,
    VOS_UINT8                           ucCsEmergencyConnStatusFlg
)
{
    MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *pstMsg = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)

    /* �����ڴ� */
    pstMsg = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU));
#endif

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_MMC_SndLmmConnStatusNotify():ERROR:MALLOC MEMORY FAILURE");
        return ;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_CS_CONN_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_CS_CONN_STATUS_NOTIFY;
    pstMsg->ulOpId                      = 0;
    pstMsg->ucCsRrConnStatusFlg         = ucCsRrConnStatusFlg;
    pstMsg->ucCsEmergencyConnStatusFlg  = ucCsEmergencyConnStatusFlg;


#if (VOS_WIN32 == VOS_OS_VER)

    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MM, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmConnStatusNotify():ERROR:SEND MESSAGE FAILURE");
        return ;
    }
#else

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);

#endif

    return;
}
VOS_UINT32  NAS_MMC_FormatProcTypeToLmm(
    NAS_MML_PROC_TYPE_ENUM_U32          enProcType,
    MMC_LMM_ACTION_TYPE_ENUM_UINT32    *penActionType
)
{
    switch (enProcType)
    {
        case NAS_MML_PROC_ATTACH:
        case NAS_MML_PROC_COMBINED_ATTACH:
            *penActionType = MMC_LMM_ACTION_ATTACH;
            break;

        case NAS_MML_PROC_MT_DETACH:
            *penActionType = MMC_LMM_ACTION_MT_DETACH;
            break;

        case NAS_MML_PROC_LOCAL_DETACH:
           *penActionType = MMC_LMM_ACTION_LOCAL_DETACH;
           break;

        case NAS_MML_PROC_UE_DETACH:
            *penActionType = MMC_LMM_ACTION_MO_DETACH;
             break;

        case NAS_MML_PROC_RAU:
        case NAS_MML_PROC_COMBINED_RAU:
            *penActionType = MMC_LMM_ACTION_RAU;

            break;

        case NAS_MML_PROC_PERIODC_RAU:
            *penActionType = MMC_LMM_ACTION_PERIODC_RAU;
            break;


        case NAS_MML_PROC_LAU:
            *penActionType = MMC_LMM_ACTION_LAU;
            break;

        case NAS_MML_PROC_SER:
            *penActionType = MMC_LMM_ACTION_PS_SERVICE_REQ;
            break;

        case NAS_MML_PROC_CM_SER:
            *penActionType = MMC_LMM_ACTION_CM_REQ;
            break;

        /* ����Abort����ת�� */
        case NAS_MML_PROC_MM_ABORT:
            *penActionType = MMC_LMM_ACTION_MM_ABORT;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32  NAS_MMC_ConvertAttachTypeToLmm(
    VOS_UINT32                          ulAttachType,
    MMC_LMM_ATT_REQ_TYPE_ENUM_UINT32   *penLmmAttachType
)
{
    switch (ulAttachType)
    {
        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_PS_ONLY;
            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_CS_PS;
            break;

        case NAS_MSCC_PIF_ATTACH_TYPE_IMSI:
            *penLmmAttachType = MMC_LMM_ATT_REQ_TYPE_CS_ONLY;
            break;

        default:
            return VOS_ERR;

    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertLmmPlmnToGUNasFormat
 ��������  : ��LMM��3�ֽڸ�ʽPLMNת��ΪMCC��MNC�ֿ��ĸ�ʽ
 �������  : pLMMPlmn
 �������  : pGUNasPlmn
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��28��
    ��    ��   : likelai
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertLmmPlmnToGUNasFormat(
    MMC_LMM_PLMN_ID_STRU               *pstLMMPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    NAS_MML_SIM_FORMAT_PLMN_ID          stSimPlmn;

    PS_MEM_SET(&stSimPlmn, 0, sizeof(NAS_MML_SIM_FORMAT_PLMN_ID));

    /* ��ת��ΪSIM��ʽ */
    PS_MEM_CPY(stSimPlmn.aucSimPlmn, pstLMMPlmn->aucPlmnId, sizeof(pstLMMPlmn->aucPlmnId));

    NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, pstGUNasPlmn);

    return;
}
VOS_VOID NAS_MMC_ConvertLmmPlmnToGUNasPlmn(
    VOS_UINT32                          ulLmmPlmnNum,
    MMC_LMM_PLMN_ID_STRU               *pstLmmPlmn,
    NAS_MML_PLMN_ID_STRU               *pstGUNasPlmn
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < ulLmmPlmnNum ; i++  )
    {
        NAS_MMC_ConvertLmmPlmnToGUNasFormat( &(pstLmmPlmn[i]), &(pstGUNasPlmn[i]) );
    }
}


VOS_UINT32  NAS_MMC_ConvertDetachTypeToLmm(
    VOS_UINT32                          ulDetachType,
    MMC_LMM_MO_DETACH_TYPE_ENUM_UINT32 *penLmmDetachType
)
{
    if ( NAS_MSCC_PIF_DETACH_TYPE_GPRS          == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_PS_ONLY;
    }
    else if ( NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI  == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_CS_PS;
    }
    else if ( NAS_MSCC_PIF_DETACH_TYPE_IMSI  == ulDetachType )
    {
        *penLmmDetachType = MMC_LMM_MO_DET_CS_ONLY;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MML_GetTinTypeToLmm
 ��������  : ��ȡTIN���͸�LMM
 �������  : ��
 �������  : penTinType:LMM��TIN����
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�,VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetTinTypeToLmm(
    MMC_LMM_TIN_TYPE_ENUM_UINT32        *penTinType
)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();
    if ( NAS_MML_TIN_TYPE_GUTI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_GUTI;
    }
    else if ( NAS_MML_TIN_TYPE_PTMSI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_P_TMSI;
    }
    else if ( NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType )
    {
        *penTinType = MMC_LMM_TIN_RAT_RELATED_TMSI;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetEplmnToLmm
 ��������  : ��ȡEPLMN֪ͨLMM
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�,VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetEplmnToLmm(
    MMC_LMM_EPLMN_STRU                  *pstEplmnList
)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstGuEplmnAddr;
    VOS_UINT32                          i;

    pstGuEplmnAddr          = NAS_MML_GetEquPlmnList();
    pstEplmnList->ulPlmnNum = pstGuEplmnAddr->ucEquPlmnNum;

    for ( i = 0 ; i <  pstEplmnList->ulPlmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstEplmnList->astEplmnList[i]),
                                          &(pstGuEplmnAddr->astEquPlmnAddr[i]));
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFplmnToLmm
 ��������  : ��ȡFPLMN֪ͨLMM
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�,VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��28��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetFplmnToLmm(
    MMC_LMM_PLMN_LIST_STRU              *pstFplmnList
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          i;

    pstForbidPlmnInfo       = NAS_MML_GetForbidPlmnInfo();
    ucFplmnNum              = pstForbidPlmnInfo->ucForbPlmnNum;
    pstFplmnList->ulPlmnNum = ucFplmnNum;

    for ( i = 0 ; i <  ucFplmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstFplmnList->astPlmnId[i]),
                                          &(pstForbidPlmnInfo->astForbPlmnIdList[i]));
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetFplmnForGprsToLmm
 ��������  : ��ȡFPLMN for Gprs֪ͨLMM
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK:��ȡ�ɹ�,VOS_ERR:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��4��28��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetFplmnForGprsToLmm(
    MMC_LMM_PLMN_LIST_STRU              *pstFplmnForGprsList
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU   *pstForbidPlmnInfo;
    VOS_UINT8                           ucFplmnNum;
    VOS_UINT32                          i;

    pstForbidPlmnInfo       = NAS_MML_GetForbidPlmnInfo();
    ucFplmnNum              = pstForbidPlmnInfo->ucForbGprsPlmnNum;

    pstFplmnForGprsList->ulPlmnNum = ucFplmnNum;

    for ( i = 0 ; i <  ucFplmnNum; i++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstFplmnForGprsList->astPlmnId[i]),
                                          &(pstForbidPlmnInfo->astForbGprsPlmnList[i]));
    }

    return VOS_OK;

}



VOS_UINT32  NAS_MMC_GetEHplmnToLmm(
    MMC_LMM_PLMN_LIST_STRU             *pstEHplmnList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulHplmnNum ;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEhplmnInfo = VOS_NULL_PTR;

    pstEhplmnInfo = NAS_MML_GetSimEhplmnList();

    if (NAS_MML_HPLMN_TYPE_EHPLMN == NAS_MML_GetHPlmnType())
    {
        /* EHPLMN��ʵ�ʸ��� */
        ulHplmnNum   = pstEhplmnInfo->ucEhPlmnNum;

        pstEHplmnList->ulPlmnNum = ulHplmnNum;

        /* ת��ΪLMM��Ҫ�ĸ�ʽ */
        for ( i = 0 ; i < ulHplmnNum; i++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstEHplmnList->astPlmnId[i]),
                                              &(pstEhplmnInfo->astEhPlmnInfo[i].stPlmnId));
        }
    }
    else
    {
        pstEHplmnList->ulPlmnNum = 0;
    }

    return VOS_OK;
}


VOS_UINT32  NAS_MMC_GetHplmnToLmm(
    MMC_LMM_PLMN_ID_STRU               *pstHplmn
)
{
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    NAS_MML_HPLMN_TYPE_ENUM_UINT8       enHplmnType;

    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;

    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    enHplmnType   = NAS_MML_GetHPlmnType();
    pstEHPlmnInfo = NAS_MML_GetSimEhplmnList();

    /* ��ǰHPLMN����ΪHPLMN����ACTING-HPLMN */
    if ((NAS_MML_HPLMN_TYPE_HPLMN == enHplmnType)
     || (NAS_MML_HPLMN_TYPE_ACTING_HPLMN == enHplmnType))
    {
        /* ��ֵHPLMN */
        stPlmnId = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId;
    }
    /* ��ǰHPLMN����ΪEHPLMN */
    else if (NAS_MML_HPLMN_TYPE_EHPLMN == enHplmnType)
    {
        /* ��ֵHPLMN */
        stPlmnId = NAS_MML_GetImsiHomePlmn(pstMsIdentity->aucImsi);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAsHplmnReq(): HPLMN TYPE ERROR");
        return VOS_ERR;
    }

    NAS_MML_ConvertNasPlmnToLMMFormat(pstHplmn, &stPlmnId);

    return VOS_OK;
}


MMC_LMM_RESULT_ID_ENUM_UINT32 Nas_GetPubInfo(
    MMC_LMM_INFO_TYPE_ENUM_UINT32       ulInfoType,
    MMC_LMM_PUB_INFO_STRU              *pstPubInfo
)
{
    VOS_UINT32                          ulRet;

    ulRet   = VOS_ERR;

    switch (ulInfoType)
    {
        case MMC_LMM_TIN_TYPE:
            ulRet = NAS_MMC_GetTinTypeToLmm(&(pstPubInfo->u.ulTinType));
            break;

        case MMC_LMM_EPLMN:
            ulRet = NAS_MMC_GetEplmnToLmm(&(pstPubInfo->u.stEplmnList));
            break;

        case MMC_LMM_FPLMN:
            ulRet = NAS_MMC_GetFplmnToLmm(&(pstPubInfo->u.stForbiddenPlmnList));
            break;

        case MMC_LMM_FPLMN_FOR_GPRS:
            ulRet = NAS_MMC_GetFplmnForGprsToLmm(&(pstPubInfo->u.stForbiddenPlmnListForGPRS));
            break;

        case MMC_LMM_EHPLMN:
            ulRet = NAS_MMC_GetEHplmnToLmm(&(pstPubInfo->u.stEHplmnList));
            break;

        case MMC_LMM_HPLMN:
            ulRet = NAS_MMC_GetHplmnToLmm(&(pstPubInfo->u.stHplmn));
            break;

        default:
            break;

    }

    if ( VOS_OK == ulRet )
    {
        return MMC_LMM_SUCC;
    }

    return MMC_LMM_FAIL;
}


VOS_VOID NAS_MMC_FillGprsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    /* �����Я��ulAttemptCount��ֱ�ӷ��� */
    if (VOS_FALSE == pstMsg->bitOpAtmpCnt)
    {
        return;
    }

    /* ���ulAttemptCountΪ0��ֱ�ӷ��� */
    if (0 == pstMsg->ulAttemptCount)
    {
        return;
    }

    /* ���������RAU������ATTACH��ulCombRegΪTRUE */
    if ((MMC_LMM_ACTION_RAU == pstMsg->enActionType)
     || (MMC_LMM_ACTION_ATTACH == pstMsg->enActionType))
    {
        /* ���ú���NAS_MML_GetPsUpdateStatus���PS update״̬ */
        pstMsg->bitOpGprsUpdateStatus = VOS_TRUE;
        pstMsg->ucGprsUpdateStatus    = NAS_MML_GetPsUpdateStatus();

        /* ���ú���NAS_MML_IsRaiChanged���Rai�Ƿ�ı��־ */
        pstMsg->bitOpRaiChangFlg      = VOS_TRUE;
        pstMsg->ucRaiChangFlg         = NAS_MML_IsRaiChanged();
    }

    return;
}
VOS_VOID NAS_MMC_FillCsRegInfoInLmmActionRslt(
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo     = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                   *pstLastSuccLai  = VOS_NULL_PTR;
    VOS_UINT32                          ulCombReg;

    pstCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstLastSuccLai = NAS_MML_GetCsLastSuccLai();

    ulCombReg      = VOS_FALSE;

    /* �������enReqDomain��ֱ�ӷ��� */
    if (VOS_FALSE == pstMsg->bitOpReqDomain)
    {
        return;
    }

    /* �����Я��ulAttemptCount��ֱ�ӷ��� */
    if (VOS_FALSE == pstMsg->bitOpAtmpCnt)
    {
        return;
    }

    /* ���ulAttemptCountΪ0��ֱ�ӷ��� */
    if (0 == pstMsg->ulAttemptCount)
    {
        return;
    }

    /* ���������RAU������ATTACH��ulCombRegΪTRUE */
    if ((MMC_LMM_ACTION_RAU == pstMsg->enActionType)
     || (MMC_LMM_ACTION_ATTACH == pstMsg->enActionType))
    {
        if (MMC_LMM_COMBINED_PS_IMSI == pstMsg->ulReqDomain)
        {
            ulCombReg = VOS_TRUE;
        }
    }

    /* �����LAU,����RAU������ATTACH,���CS update״̬��Lai�Ƿ�ı��־ */
    if ((MMC_LMM_ACTION_LAU == pstMsg->enActionType)
     || (VOS_TRUE == ulCombReg))
    {
        /* ���ú���NAS_MML_GetCsUpdateStatus���CS update״̬ */
        pstMsg->bitOpCsUpdateStatus = VOS_TRUE;
        pstMsg->ucCsUpdateStatus    = NAS_MML_GetCsUpdateStatus();

        /* ���ú���NAS_MML_CompareLai���Lai�Ƿ�ı��־ */
        pstMsg->bitOpLaiChangFlg    = VOS_TRUE;

        if (VOS_TRUE == NAS_MML_CompareLai(&(pstCampInfo->stLai), pstLastSuccLai))
        {
            pstMsg->ucLaiChangFlg = VOS_FALSE;
        }
        else
        {
            pstMsg->ucLaiChangFlg = VOS_TRUE;
        }
    }

    return;
}
VOS_UINT32 NAS_MMC_PlmnIdIsAllowRegManualMode(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserSpecPlmn = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulIsUserPlmn;

    pstEplmnInfo = NAS_MML_GetEquPlmnList();

    pstUserSpecPlmn = NAS_MMC_GetUserSpecPlmnId();

    ulIsUserPlmn = NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmnId, &(pstUserSpecPlmn->stPlmnId));

    /* �ֶ�����ģʽ��,�жϸ�plmn�Ƿ�Ϊ�û�ָ����PLMN */
    if ((NAS_MMC_PLMN_SELECTION_MODE_MANUAL == NAS_MMC_GetPlmnSelectionMode())
     && (VOS_FALSE == ulIsUserPlmn))
    {
        /* EPLMN��Ч */
        if (VOS_FALSE == NAS_MML_GetEplmnValidFlg())
        {
            return VOS_FALSE;
        }

        /* ��PLMN����EPLMN�б��� */
        if (VOS_FALSE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId,
                                                                pstEplmnInfo->ucEquPlmnNum,
                                                                pstEplmnInfo->astEquPlmnAddr))
        {
            return VOS_FALSE;
        }

        /* �û�ָ������ע��״̬Ϊ FALSE */
        if (VOS_FALSE == NAS_MMC_GetUserSpecPlmnRegisterStatus())
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

MMC_LMM_PLMN_CTRL_ENUM_UINT32  Nas_PlmnIdIsForbid(
    MMC_LMM_PLMN_ID_STRU                *pstPlmn
)
{
    NAS_MML_PLMN_ID_STRU                                    stGuPlmnId;
    NAS_MML_PLMN_WITH_RAT_STRU                              stPlmnWithRat;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    VOS_UINT8                                               ucAsAnyCampOn;

    /* ��PLMN ID����ת�� */
    NAS_MMC_ConvertLmmPlmnToGUNasFormat(pstPlmn, &stGuPlmnId);

    /* ���жϸ�Plmn�Ƿ���Ч */
    if ( VOS_FALSE == NAS_MML_IsPlmnIdValid(&stGuPlmnId) )
    {
        return MMC_LMM_PLMN_CTRL_BUTT;
    }

    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    /* ��ǰplmn��MCC�ڽ�ֹLTE�������ε�MCC�б���,PLMN��������ע�� */
    if (VOS_TRUE == NAS_MMC_IsNeedDisableLteRoam(stGuPlmnId.ulMcc))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    ucAsAnyCampOn = NAS_MMC_GetAsAnyCampOn();

    /* �����3GPP2����ע�ᣬ��ǰLΪ����פ������������ע�� */
    if ((NAS_MMC_REG_CONTROL_BY_3GPP_MMC != NAS_MMC_GetRegCtrl())
     && (VOS_TRUE == ucAsAnyCampOn))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    if (VOS_FALSE == NAS_MMC_PlmnIdIsAllowRegManualMode(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* ��PLMN ID�Ƿ�������������PLMN �б��� */
    if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInLockPlmnList(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* ����������ʱ */
    if (VOS_FALSE == NAS_MML_IsPlmnIdRoamingAllowed(&stGuPlmnId))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    /* ���쵱ǰ���뼼����PLMN ID */
    stPlmnWithRat.stPlmnId.ulMcc    = stGuPlmnId.ulMcc;
    stPlmnWithRat.stPlmnId.ulMnc    = stGuPlmnId.ulMnc;
    stPlmnWithRat.enRat             = NAS_MML_NET_RAT_TYPE_LTE;

    /* �жϵ�ǰPLMN�Ƿ��ڽ�ֹRAT��PLMN�б���ͬʱ��ǰ���뼼������ֹ,����Ϊ��ǰPLMNΪ��ֹ���� */
    if (VOS_TRUE == NAS_MML_IsPlmnIdWithRatInDestDisabledPlmnWithForbiddenPeriodList(&stPlmnWithRat))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    /* �ж�PLMN��RAT�ڽ�ֹ���뼼���б��У�����Ϊ��ǰRAT��Ӧ����Ϊ��ֹ���� */
    if (VOS_TRUE == NAS_MML_IsRatInForbiddenList(stPlmnWithRat.enRat))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }


    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    /* ��forbid plmn�б��� */
    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stGuPlmnId,
                                                         pstForbidPlmnInfo->ucForbPlmnNum,
                                                         pstForbidPlmnInfo->astForbPlmnIdList))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stGuPlmnId,
                                                            pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                                            pstForbidPlmnInfo->astForbGprsPlmnList))
    {
        return MMC_LMM_PLMN_NOT_ALLOW_REG;
    }

    return MMC_LMM_PLMN_ALLOW_REG;
}


VOS_VOID NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    VOS_UINT32                          ulIndex;

    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid                   = PS_PID_MM;
    /* ����PID��Ҫ���� */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                        = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                         = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId                          = 0;

    if (VOS_TRUE == ulUserSpecFlag)
    {
        pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_USER_SPEC;
    }
    else
    {
        pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_SPEC;
    }

    pstMsg->bitOpSpecPlmn                   = VOS_TRUE;
    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), &(pstDestPlmnList->astPlmnId[0].stPlmnId));

    if ( VOS_FALSE == ulUserSpecFlag )
    {
        if ( pstDestPlmnList->ulPlmnNum > 1 )
        {
            pstMsg->bitOpEqlPlmn = VOS_TRUE;
        }

        for ( ulIndex = 1; ulIndex < NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, MMC_LMM_MAX_EQUPLMN_NUM); ulIndex++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stEplmnList.astEplmnList[ulIndex-1]), &(pstDestPlmnList->astPlmnId[ulIndex].stPlmnId));
            pstMsg->stEplmnList.ulPlmnNum++;
        }
    }

    return;
}
VOS_VOID NAS_MMC_SndLmmSpecPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList,
    VOS_UINT32                          ulUserSpecFlag
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    NAS_MMC_BuildLmmSpecPlmnSearchReqMsg(pstMsg, pstDestPlmnList, ulUserSpecFlag);

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSpecPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FIAL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif


#ifndef __PS_WIN32_RECUR__

    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}



VOS_VOID NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg,
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
)
{
    VOS_UINT32                          ulIndex;

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_MM,
                        ID_MMC_LMM_PLMN_SRCH_REQ,
                        sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstMsg->ulOpId                          = 0;

    pstMsg->enSrchType                      = MMC_LMM_PLMN_SRCH_HISTORY;

    pstMsg->bitOpSpecPlmn                   = VOS_TRUE;
    pstMsg->bitOpPlmnInfoCampFlg            = VOS_TRUE;
    pstMsg->enFftScanType                   = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), &(pstDestPlmnList->astPlmnId[0].stPlmnId));

    /* ����EPLMN LIST���� */
    if (pstDestPlmnList->ulPlmnNum > 1)
    {
        pstMsg->bitOpEqlPlmn = VOS_TRUE;
    }

    for (ulIndex = 1; ulIndex < NAS_MML_MIN(pstDestPlmnList->ulPlmnNum, MMC_LMM_MAX_EQUPLMN_NUM); ulIndex++)
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stEplmnList.astEplmnList[ulIndex-1]), &(pstDestPlmnList->astPlmnId[ulIndex].stPlmnId));
        pstMsg->stEplmnList.ulPlmnNum++;
    }

    return;
}



VOS_VOID NAS_MMC_SndLmmHistoryPlmnSearchReq(
    NAS_MML_PLMN_LIST_WITH_RAT_STRU    *pstDestPlmnList
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmHistoryPlmnSearchReq():WARNING:PS_ALLOC_MSG FAIL");
        return;
    }

    /* ���췢����Ϣ */
    NAS_MMC_BuildLmmHistoryPlmnSearchReqMsg(pstMsg, pstDestPlmnList);

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))

    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmHistoryPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FAIL");
        return;
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmNcellSpecPlmnSearchReq(
    NAS_MMC_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    NAS_MML_EQUPLMN_INFO_STRU          *pstOtherModemEplmnInfo
)
{
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucLoopEplmnNum;
    VOS_UINT8                           ucMaxEplmnNum;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmNcellSpecPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;

    /* ����PID��Ҫ���� */
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId           = 0;

    pstMsg->enSrchType       = MMC_LMM_PLMN_SRCH_NCELL_SPEC;

    /* ��ncell Ƶ���б���Ϣ */
    pstMsg->bitOpNcellInfo   = VOS_TRUE;
    pstMsg->stNcellInfo.ucLteArfcnNum = pstLteNcellInfo->ucLteArfcnNum;
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    PS_MEM_CPY(pstMsg->stNcellInfo.aulLteArfcnList, pstLteNcellInfo->aulLteArfcnList,
               sizeof(pstMsg->stNcellInfo.aulLteArfcnList));
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */

    pstMsg->stNcellInfo.ucLteCellIdNum = pstLteNcellInfo->ucLteCellNum;
    PS_MEM_CPY(pstMsg->stNcellInfo.ausLteCellIdList, pstLteNcellInfo->ausLteCellList,
               sizeof(pstMsg->stNcellInfo.ausLteCellIdList));

    ucMaxEplmnNum        = pstOtherModemEplmnInfo->ucEquPlmnNum;

    if (ucMaxEplmnNum > MMC_LMM_MAX_EQUPLMN_NUM)
    {
        ucMaxEplmnNum = MMC_LMM_MAX_EQUPLMN_NUM;
    }

    pstMsg->stNcellInfo.stEplmnList.ulPlmnNum = ucMaxEplmnNum;

    for (ucLoopEplmnNum = 0; ucLoopEplmnNum < ucMaxEplmnNum; ucLoopEplmnNum++ )
    {
        NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stNcellInfo.stEplmnList.astEplmnList[ucLoopEplmnNum]),
                                          &(pstOtherModemEplmnInfo->astEquPlmnAddr[ucLoopEplmnNum]));
    }

    pstMsg->bitOpPlmnInfoCampFlg = VOS_TRUE;
    pstMsg->enFftScanType        = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}



VOS_VOID NAS_MMC_BuildMmcLmmDetachIndActionResultReqMsg(
    NAS_MMC_GMM_NT_DETACH_ENUM_U32      enMtType,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    MMC_LMM_ACTION_RESULT_REQ_STRU     *pstMsg
)
{
    NAS_LMM_CN_CAUSE_ENUM_UINT8         enCnRejCause;

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                         sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_ACTION_RESULT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_ACTION_RESULT_REQ;
    pstMsg->ulOpId                      = 0;

    /* ����DETACH �������÷���ҵ�����ͺͽ�������� */
    switch(enMtType)
    {
        case NAS_MMC_GMM_NT_DETACH_IMSI:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_IMSI_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_IMSI_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_IMSI;
            break;

        case NAS_MMC_GMM_NT_DETACH_REATTACH:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_REATTACH_REQUIRED;
            break;

        case NAS_MMC_GMM_NT_DETACH_NOATTACH:
            pstMsg->bitOpReqDomain = VOS_TRUE;
            pstMsg->bitOpRstDomain = VOS_TRUE;
            pstMsg->ulReqDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulRstDomain    = MMC_LMM_PS_ONLY;
            pstMsg->ulMtDetachType = MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED;
            break;

        default:
            break;
    }

    pstMsg->bitOpMtDetachType           = VOS_TRUE;
    pstMsg->enActionType                = MMC_LMM_ACTION_MT_DETACH;
    pstMsg->ulActRst                    = MMC_LMM_RSLT_TYPE_SUCCESS;

    /* TS 24008,4.7.4.2.2.If the detach type IE indicates "IMSI detach", or "re-attach required" then
       the MS shall ignore the cause code if received. */
    if ( (VOS_OK == NAS_MMC_ConvertMmCauseToEmmCause(enCnCause, &enCnRejCause))
     && (MMC_LMM_MT_DET_REATTACH_NOT_REQUIRED == pstMsg->ulMtDetachType))
    {
        pstMsg->bitOpCnCause            = VOS_TRUE;
        pstMsg->ucCnCause               = enCnRejCause;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConverCnDomainToLmm
 ��������  : ��MMC�ڲ������Domainת��ΪLMM��ʽ��
 �������  : enCnDoamin:MMC�ڲ��������
 �������  : penLmmDomain:LMM��ʽ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��12��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_ConverCnDomainToLmm(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8      enCnDoamin,
    MMC_LMM_DOMAIN_ENUM_UINT32         *penLmmDomain
)
{
    if ( NAS_MMC_REG_DOMAIN_CS           == enCnDoamin)
    {
        *penLmmDomain = MMC_LMM_IMSI_ONLY;
    }
    else if ( NAS_MMC_REG_DOMAIN_PS_CS   == enCnDoamin)
    {
        *penLmmDomain = MMC_LMM_COMBINED_PS_IMSI;
    }
    else
    {
        *penLmmDomain = MMC_LMM_PS_ONLY;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertMmCauseToEmmCause
 ��������  : ��MM��ע����ת��ΪEMM��ע����,������Ҫ��ȷ����EMM�Ƿ�������
              �ܾ���������ԭ��ܾ�
 �������  : enCnCause:MMע����
 �������  : penProtolCause:Э���й涨�Ľ��
 �� �� ֵ  : VOS_OK:ת���ɹ�
              VOS_ERR:ת��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_ConvertMmCauseToEmmCause(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause,
    NAS_LMM_CN_CAUSE_ENUM_UINT8        *penProtolCause
)
{
    /* ��ԭ��ֵ����ע��ɹ�����������Ӧ */
    if ( NAS_MML_REG_FAIL_CAUSE_NULL == enCnCause )
    {
        return VOS_ERR;
    }

    if ( enCnCause >= NAS_MML_REG_FAIL_CAUSE_AUTH_REJ )
    {
        return VOS_ERR;
    }

    *penProtolCause = (VOS_UINT8)enCnCause;

    return VOS_OK;
}
VOS_VOID NAS_MMC_ConvertGuRsltToLmmFormat(
    NAS_MML_REG_RESULT_ENUM_UINT8       enGuRegRslt,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enGuCnCause,
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      *penLmmActRslt
)
{
    MMC_LMM_RSLT_TYPE_ENUM_UINT32      enRslt;

    /* ��ȡע���� */
    if ( NAS_MML_REG_RESULT_SUCCESS == enGuRegRslt )
    {
        enRslt = MMC_LMM_RSLT_TYPE_SUCCESS;
    }
    else
    {
        /* �����ж����˳�����ж�enGuCnCauseС��NAS_MML_REG_FAIL_CAUSE_AUTH_REJ
           ���ж�enGuCnCause����NAS_MML_REG_FAIL_CAUSE_AUTH_REJ
           �����ж�enGuCnCause����NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED */
        if (enGuCnCause < NAS_MML_REG_FAIL_CAUSE_AUTH_REJ)
        {
            enRslt = MMC_LMM_RSLT_TYPE_CN_REJ;
        }
        else if (NAS_MML_REG_FAIL_CAUSE_AUTH_REJ == enGuCnCause)
        {
            enRslt = MMC_LMM_RSLT_TYPE_AUTH_REJ;
        }
        else if (NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED == enGuCnCause)
        {
            enRslt = MMC_LMM_RSLT_TYPE_ACCESS_BARRED;
        }
        else
        {
            enRslt = MMC_LMM_RSLT_TYPE_FAILURE;
        }
    }

    *penLmmActRslt = enRslt;

    return;
}



VOS_VOID NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_USER_PLMN_END_NOTIFY_STRU   *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_USER_PLMN_END_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_USER_PLMN_END_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = PS_PID_MM;
    /* ����PID��Ҫ���� */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_MMC;
    pstMsg->ulLength                    = sizeof(MMC_LMM_USER_PLMN_END_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId                     = ID_MMC_LMM_USER_PLMN_END_NOTIFY;
    pstMsg->ulOpId                      = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUserSpecPlmnSearchEndNotify():WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmBgStopPlmnSearchReq(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU                   *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgStopPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_STOP_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_STOP_BG_PLMN_SEARCH_REQ;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgStopPlmnSearchReq():WARNING:SEND LMM BG STOP PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmFastPlmnSearchReq(
    NAS_MML_PLMN_ID_STRU               *pstDestPlmn
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmFastPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulLength         = sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_PLMN_SRCH_REQ;
    pstMsg->ulOpId           = 0;

    /* ����ָ����PLMN������ */
    pstMsg->enSrchType       = MMC_LMM_PLMN_SRCH_FAST_SPEC;

    pstMsg->bitOpSpecPlmn    = VOS_TRUE;
    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->stSpecPlmnId), pstDestPlmn);

    pstMsg->bitOpPlmnInfoCampFlg = VOS_TRUE;
    pstMsg->enFftScanType        = MMC_LMM_FFT_SCAN_TYPE_NONE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmFastPlmnSearchReq():WARNING:SEND LMM PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmBgPlmnSearchReq(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstDestPlmn
)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_BG_PLMN_SEARCH_REQ_STRU                        *pstMsg                          = VOS_NULL_PTR;
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
    NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU            *pstForbLaWithValidPeriodList    = VOS_NULL_PTR;
    NAS_MML_LAI_STRU                                       *pstLai                          = VOS_NULL_PTR;
    /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbPlmnInfo;
    VOS_UINT32                                              i;
    MMC_LMM_PLMN_ID_STRU                                    stLmmPlmn;

    /* ��ȫ�ֱ����л�ȡFORBIDEN ROAMING LAS��Ϣ */
    pstForbPlmnInfo = NAS_MML_GetForbidPlmnInfo();


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BG_PLMN_SEARCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgPlmnSearchReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
                sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ���췢����Ϣ */
    pstMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid     = PS_PID_MM;
    pstMsg->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->ulLength          = sizeof(MMC_LMM_BG_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId           = ID_MMC_LMM_BG_PLMN_SEARCH_REQ;
    pstMsg->ulOpId            = 0;

    NAS_MML_ConvertNasPlmnToLMMFormat(&stLmmPlmn, &pstDestPlmn->stPlmnId);
    PS_MEM_CPY(pstMsg->stSpecPlmnWithRat.aucPlmnId, stLmmPlmn.aucPlmnId, MMC_LMM_PLMN_ID_LEN);
    pstMsg->stSpecPlmnWithRat.enPlmnRat = pstDestPlmn->enRat;

    if (NAS_MML_NET_RAT_TYPE_LTE != pstDestPlmn->enRat)
    {
        /* L�±�����GU�����磬��Ҫ�����н�ֹ���� LA ��ӵ�ForbLa�б� */
        for ( i = 0; i < pstForbPlmnInfo->ucForbRoamLaNum; i++ )
        {
            NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->astForbRoamLaiList[i].stPlmnId),
                                              &(pstForbPlmnInfo->astForbRomLaList[i].stPlmnId));
            pstMsg->astForbRoamLaiList[i].stLac.ucLac   =
                pstForbPlmnInfo->astForbRomLaList[i].aucLac[0];
            pstMsg->astForbRoamLaiList[i].stLac.ucLacCnt =
                pstForbPlmnInfo->astForbRomLaList[i].aucLac[1];
        }

        /* ForbLa�б��еĽ�ֹ���� LA �ĸ��� */
        pstMsg->ulForbRoamLaiNum = pstForbPlmnInfo->ucForbRoamLaNum;

        /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, begin */
        pstForbLaWithValidPeriodList = NAS_MML_GetForbLaWithValidPeriodList();
        for ( i = 0; i < pstForbLaWithValidPeriodList->ulForbLaWithValidPeriodNum; i++ )
        {
            pstLai = &(pstForbLaWithValidPeriodList->astForbLaWithValidPeriodList[i].stForbLaWithValidPeriodLai);
            if (   (VOS_FALSE == NAS_MML_IsLaiInDestLaiList(pstLai, pstForbPlmnInfo->ucForbRoamLaNum,
                  pstForbPlmnInfo->astForbRomLaList)) 
                && ((pstMsg->ulForbRoamLaiNum) < MMC_LMM_MAX_FORB_ROAM_LAI_NUM)   )
            {
                NAS_MML_ConvertNasPlmnToLMMFormat(&(pstMsg->astForbRoamLaiList[pstMsg->ulForbRoamLaiNum].stPlmnId),
                                              &(pstLai->stPlmnId));
                pstMsg->astForbRoamLaiList[i].stLac.ucLac    = pstLai->aucLac[0];
                pstMsg->astForbRoamLaiList[i].stLac.ucLacCnt = pstLai->aucLac[1];
            }
        }
        /* Added by g00322017 for CS REG FAIL FORB LA, 2015-9-23, end */
    }


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgPlmnSearchReq():WARNING:SEND LMM BG PLMN SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}



VOS_VOID NAS_MMC_SndLmmGetGeoPlmnSearchReq(VOS_VOID)
{
    /* ����ԭ������ָ�� */
    MMC_LMM_PLMN_SRCH_REQ_STRU         *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_PLMN_SRCH_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU));
#endif

    if ( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGetGeoPlmnSearchReq:ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* �����Ϣ���� */
    NAS_MMC_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    NAS_MMC_CFG_MSG_HDR(pstMsg,
                        PS_PID_MM,
                        ID_MMC_LMM_PLMN_SRCH_REQ,
                        sizeof(MMC_LMM_PLMN_SRCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstMsg->ulOpId                      = 0;
    pstMsg->enSrchType                  = MMC_LMM_PLMN_SRCH_GET_GEO;

    pstMsg->enFftScanType               = MMC_LMM_FFT_SCAN_TYPE_LOW;
    pstMsg->bitOpPlmnInfoCampFlg        = VOS_FALSE;

    NAS_MML_SaveNwSearchReqInfo(pstMsg);

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
         NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGetGeoPlmnSearchReq:WARNING:SEND LMM PLMN ANYCELL SEARCH REQ FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;

}
VOS_VOID NAS_MMC_SndLmmStopGetGeoPlmnSearchReq(VOS_VOID)
{
    NAS_MMC_SndLmmPlmnSrchStopReq();
    return;
}







VOS_VOID  NAS_MMC_SndLmmUeOocStatusInd( VOS_VOID )
{
    /* ����ԭ������ָ�� */
    MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstMsg = (MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUeOocStatusInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid      = WUEPS_PID_MMC;
    pstMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid    = PS_PID_MM;
    pstMsg->ulLength         = sizeof(MMC_LMM_UE_OOC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId          = ID_MMC_LMM_UE_OOC_STATUS_NOTIFY;
    pstMsg->ulOpId           = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmUeOocStatusInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif
    return;
}





VOS_VOID NAS_MMC_SndLmmWcdmaSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    RRMM_SYS_INFO_IND_STRU             *pstRrMmSysInfoInd  = VOS_NULL_PTR;
    MMC_LMM_WCDMA_SYS_INFO_IND_STRU    *pstLmmWcdmaSysInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmnId;

    pstRrMmSysInfoInd = (RRMM_SYS_INFO_IND_STRU*)pstMsg;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstLmmWcdmaSysInfo = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmWcdmaSysInfo = (MMC_LMM_WCDMA_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU));
#endif

    if( VOS_NULL_PTR == pstLmmWcdmaSysInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmWcdmaSysInfoInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstLmmWcdmaSysInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstLmmWcdmaSysInfo->ulSenderPid      = WUEPS_PID_MMC;
    pstLmmWcdmaSysInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstLmmWcdmaSysInfo->ulReceiverPid    = PS_PID_MM;
    pstLmmWcdmaSysInfo->ulLength         = sizeof(MMC_LMM_WCDMA_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLmmWcdmaSysInfo->ulMsgId          = ID_MMC_LMM_WCDMA_SYS_INFO_IND;

    /* ���PLMN �ֶ� */
    stGUNasPlmnId.ulMcc = pstRrMmSysInfoInd->PlmnId.ulMcc;;
    stGUNasPlmnId.ulMnc = pstRrMmSysInfoInd->PlmnId.ulMnc;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmWcdmaSysInfo->stPlmnId),
                                      &(stGUNasPlmnId));

    /* ���С��ID */
    pstLmmWcdmaSysInfo->ulCellId = pstRrMmSysInfoInd->ulCellId;

    /* ���LAC */
    /* aucCnCommonInfo[0] �� aucCnCommonInfo[1] ���� lac[0] ��  Lac[1]*/
    pstLmmWcdmaSysInfo->usLac  = (VOS_UINT16)pstRrMmSysInfoInd->aucCnCommonInfo[1];
    pstLmmWcdmaSysInfo->usLac |= (VOS_UINT16)(pstRrMmSysInfoInd->aucCnCommonInfo[0]<< NAS_MML_OCTET_MOVE_EIGHT_BITS);


    /* ���RAC */
    if ( 0 == pstRrMmSysInfoInd->ucPsInfoSize )
    {
        pstLmmWcdmaSysInfo->bitOpRac = VOS_FALSE;
        pstLmmWcdmaSysInfo->ucRac    = 0;
    }
    else
    {
        pstLmmWcdmaSysInfo->bitOpRac = VOS_TRUE;
        pstLmmWcdmaSysInfo->ucRac    = pstRrMmSysInfoInd->aucPsInfo[0];
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmWcdmaSysInfo ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmWcdmaSysInfoInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstLmmWcdmaSysInfo);
#endif
    return;
}


VOS_VOID NAS_MMC_SndLmmGsmSysInfoInd(
    struct MsgCB                       *pstMsg
)
{
    GRRMM_SYS_INFO_IND_ST              *pstGrrMmSysInfo  = VOS_NULL_PTR;
    MMC_LMM_GSM_SYS_INFO_IND_STRU      *pstLmmGsmSysInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGUNasPlmnId;

    pstGrrMmSysInfo = (GRRMM_SYS_INFO_IND_ST*)pstMsg;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* �����ڴ�  */
    pstLmmGsmSysInfo = (MMC_LMM_GSM_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                    sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmGsmSysInfo = (MMC_LMM_GSM_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU));
#endif

    if( VOS_NULL_PTR == pstLmmGsmSysInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGsmSysInfoInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    pstLmmGsmSysInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstLmmGsmSysInfo->ulSenderPid      = WUEPS_PID_MMC;
    pstLmmGsmSysInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstLmmGsmSysInfo->ulReceiverPid    = PS_PID_MM;
    pstLmmGsmSysInfo->ulLength         = sizeof(MMC_LMM_GSM_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLmmGsmSysInfo->ulMsgId          = ID_MMC_LMM_GSM_SYS_INFO_IND;

    /* ���PLMN �ֶ� */
    stGUNasPlmnId.ulMcc = pstGrrMmSysInfo->PlmnId.ulMcc;;
    stGUNasPlmnId.ulMnc = pstGrrMmSysInfo->PlmnId.ulMnc;

    NAS_MML_ConvertNasPlmnToLMMFormat(&(pstLmmGsmSysInfo->stPlmnId),
                                      &(stGUNasPlmnId));

    /* ���С��ID */
    pstLmmGsmSysInfo->ulCellId = (VOS_UINT32)pstGrrMmSysInfo->usCellId;

    /* ���LAC */
    pstLmmGsmSysInfo->usLac    = pstGrrMmSysInfo->usLac;

    /* ���RAC */
    if ( 0 == pstGrrMmSysInfo->ucGprsSupportInd )
    {
        pstLmmGsmSysInfo->bitOpRac = VOS_FALSE;
        pstLmmGsmSysInfo->ucRac    = 0;
    }
    else
    {
        pstLmmGsmSysInfo->bitOpRac = VOS_TRUE;
        pstLmmGsmSysInfo->ucRac    = pstGrrMmSysInfo->ucRac;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmGsmSysInfo ) )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmGsmSysInfoInd():WARNING:SEND LMM MSG FIAL");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstLmmGsmSysInfo);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmCellSelReq(
    MMC_LMM_CELL_SEL_TYPE_ENUM_UINT32       ulSelType
)
{
    MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU                   *pstLmmCellSelStru = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstLmmCellSelStru = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstLmmCellSelStru = (MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU));
#endif

    /* �������ڴ����,����*/
    if ( VOS_NULL_PTR == pstLmmCellSelStru )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEquPlmnReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstLmmCellSelStru + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstLmmCellSelStru->ulReceiverPid   = PS_PID_MM;
    pstLmmCellSelStru->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstLmmCellSelStru->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstLmmCellSelStru->ulSenderPid     = WUEPS_PID_MMC;
    pstLmmCellSelStru->ulMsgId         = ID_MMC_LMM_CELL_SELECTION_CTRL_REQ;
    pstLmmCellSelStru->ulLength        = sizeof(MMC_LMM_CELL_SELECTION_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstLmmCellSelStru->ulOpId          = 0;
    pstLmmCellSelStru->ulSelecType     = ulSelType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstLmmCellSelStru ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSelReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstLmmCellSelStru);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstLmmCellSelStru);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmSuspendRelReq(VOS_VOID)
{
    MMC_LMM_SUSPEND_REL_REQ_STRU                   *pstMmcLmmSuspendRelReq = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmSuspendRelReq = (MMC_LMM_SUSPEND_REL_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmSuspendRelReq = (MMC_LMM_SUSPEND_REL_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU));
#endif

    /* �������ڴ����,����*/
    if ( VOS_NULL_PTR == pstMmcLmmSuspendRelReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRelReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmSuspendRelReq + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMmcLmmSuspendRelReq->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmSuspendRelReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmSuspendRelReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmSuspendRelReq->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmSuspendRelReq->ulMsgId         = ID_MMC_LMM_SUSPEND_REL_REQ;
    pstMmcLmmSuspendRelReq->ulLength        = sizeof(MMC_LMM_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmSuspendRelReq->ulOpId          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmSuspendRelReq ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmSuspendRelReq():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmSuspendRelReq);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMmcLmmSuspendRelReq);
#endif

    return;
}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID NAS_MMC_SndLmmOtherModemInfoNotify(
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstOtherModemInfoMsg
)
{
    MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU                   *pstMmcLmmOtherModemInfo = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmOtherModemInfo = (MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                            sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmOtherModemInfo = (MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU));
#endif

    /* �������ڴ����,����*/
    if ( VOS_NULL_PTR == pstMmcLmmOtherModemInfo )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmOtherModemInfoNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmOtherModemInfo + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    pstMmcLmmOtherModemInfo->ulReceiverPid       = PS_PID_MM;
    pstMmcLmmOtherModemInfo->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMmcLmmOtherModemInfo->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMmcLmmOtherModemInfo->ulSenderPid         = WUEPS_PID_MMC;
    pstMmcLmmOtherModemInfo->ulMsgId             = ID_MMC_LMM_OTHER_MODEM_INFO_NOTIFY;
    pstMmcLmmOtherModemInfo->ulLength            = sizeof(MMC_LMM_OTHER_MODEM_INFO_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmOtherModemInfo->bitOpCurrCampPlmnId = pstOtherModemInfoMsg->bitOpCurrCampPlmnId;

    PS_MEM_CPY(&pstMmcLmmOtherModemInfo->stCurrCampPlmnId, &pstOtherModemInfoMsg->stCurrCampPlmnId, sizeof(pstMmcLmmOtherModemInfo->stCurrCampPlmnId));

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmOtherModemInfo ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmOtherModemInfoNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmOtherModemInfo);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMmcLmmOtherModemInfo);
#endif

    return;
}
#endif



VOS_VOID NAS_MMC_SndLmmLteSysInfoInd(
    LMM_MMC_SYS_INFO_IND_STRU          *pstLmmSysInfoMsg
)
{
    MMC_LMM_LTE_SYS_INFO_IND_STRU      *pstMmcLmmSysInfoInd = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmSysInfoInd = (MMC_LMM_LTE_SYS_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU));
#endif

    /* �������ڴ����,����*/
    if ( VOS_NULL_PTR == pstMmcLmmSysInfoInd )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLteSysInfoInd():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmSysInfoInd + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    PS_MEM_CPY(pstMmcLmmSysInfoInd, pstLmmSysInfoMsg, sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU));

    pstMmcLmmSysInfoInd->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmSysInfoInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmSysInfoInd->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmSysInfoInd->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmSysInfoInd->ulMsgId         = ID_MMC_LMM_LTE_SYS_INFO_IND;
    pstMmcLmmSysInfoInd->ulLength        = sizeof(MMC_LMM_LTE_SYS_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmSysInfoInd->ulOpId          = 0;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmSysInfoInd ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmLteSysInfoInd():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmSysInfoInd);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMmcLmmSysInfoInd);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_MMC_SndLmmBeginSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    MMC_LMM_BEGIN_SESSION_NOTIFY_STRU  *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BEGIN_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU));
#endif

    /* �������ڴ����,����*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBeginSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_LMM_BEGIN_SESSION_NOTIFY;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSessionType   = enSessionType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBeginSessionNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}


VOS_VOID NAS_MMC_SndLmmEndSessionNotify(
    MMC_LMM_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    MMC_LMM_END_SESSION_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_END_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU));
#endif

    /* �������ڴ����,����*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEndSessionNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMC_LMM_END_SESSION_NOTIFY;
    pstMsg->stMsgHeader.ulLength        = sizeof(MMC_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSessionType               = enSessionType;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmEndSessionNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

#endif


VOS_VOID NAS_MMC_SndLmmImsVoiceCapChangeNtf(
    VOS_UINT8       ucImsVoiceAvail
)
{
    MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU               *pstMmcLmmImsVoiceChgNtf = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMmcLmmImsVoiceChgNtf = (MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMmcLmmImsVoiceChgNtf = (MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU));
#endif

    /* �������ڴ����,����*/
    if ( VOS_NULL_PTR == pstMmcLmmImsVoiceChgNtf )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmImsVoiceCapChangeNtf():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMmcLmmImsVoiceChgNtf + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    pstMmcLmmImsVoiceChgNtf->ulReceiverPid   = PS_PID_MM;
    pstMmcLmmImsVoiceChgNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcLmmImsVoiceChgNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcLmmImsVoiceChgNtf->ulSenderPid     = WUEPS_PID_MMC;
    pstMmcLmmImsVoiceChgNtf->ulMsgId         = ID_MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY;
    pstMmcLmmImsVoiceChgNtf->ulLength        = sizeof(MMC_LMM_IMS_VOICE_CAP_CHANGE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMmcLmmImsVoiceChgNtf->ulOpId          = 0;

    pstMmcLmmImsVoiceChgNtf->enImsVoiceCap   = MMC_LMM_IMS_VOICE_CAP_UNAVAILABLE;

    if (VOS_TRUE == ucImsVoiceAvail)
    {
        pstMmcLmmImsVoiceChgNtf->enImsVoiceCap   = MMC_LMM_IMS_VOICE_CAP_AVAILABLE;
    }

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMmcLmmImsVoiceChgNtf ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmImsVoiceCapChangeNtf():ERROR:SEND MESSAGE FAILURE");
    }
#else

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMmcLmmImsVoiceChgNtf);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMmcLmmImsVoiceChgNtf);
#endif

    return;
}


/*lint -restore */

VOS_VOID NAS_MMC_SndLmmCellSignReportNotify(VOS_VOID)
{
    /* NAS_MMC_GetMaintainInfo��ȡ��ucSignThreshold��ucMinRptTimerInterval��֪ͨLMM */
    MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU   *pstMsg     = VOS_NULL_PTR;
    NAS_MMC_MAINTAIN_CTX_STRU              *pstMainCtx = VOS_NULL_PTR;

    pstMainCtx = NAS_MMC_GetMaintainInfo();

    /* ƽ̨��֧��LTEʱ������Ҫ��LTE����ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():NORMAL:Platform Not Support LTE");

        /* ���� */
        return;
    }


#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU));
#endif

    /* �������ڴ����,����*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->ucSignThreshold            = pstMainCtx->ucSignThreshold;
    pstMsg->ucMinRptTimerInterval      = pstMainCtx->ucMinRptTimerInterval;

    /* ��ϢIE�ֵ */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_CELL_SIGN_REPORT_NOTIFY;
    pstMsg->ulLength        = sizeof(MMC_LMM_CELL_SIGN_REPORT_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmCellSignReportNotify():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
VOS_VOID NAS_MMC_SndLmmVoiceDomainChangeInd(
    MMC_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU       *pstMsg     = VOS_NULL_PTR;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU));
#endif

    /* �������ڴ����,����*/
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmVoiceDomainChangeInd():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    /* ��ϢIE�ֵ */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_VOICE_DOMAIN_CHANGE_IND;
    pstMsg->ulLength        = sizeof(MMC_LMM_VOICE_DOMAIN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enVoiceDomain   = enVoiceDomain;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* ����VOS����ԭ�� */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmVoiceDomainChangeInd():ERROR:SEND MESSAGE FAILURE");
    }
#else
    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, begin */
/*****************************************************************************
Function Name   :   NAS_MMC_SndLmmBgSearchHrpdReq
Description     :   MMC send message MMC_LMM_BG_SEARCH_HRPD_REQ to LMM
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmBgSearchHrpdReq(VOS_VOID)
{
    MMC_LMM_BG_SEARCH_HRPD_REQ_STRU    *pstMsg     = VOS_NULL_PTR;

    /* apply for memory */
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_BG_SEARCH_HRPD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_BG_SEARCH_HRPD_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU));
#endif

    /* apply for memory  error, returns  */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgSearchHrpdReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    /* fill message head */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_BG_SEARCH_HRPD_REQ;
    pstMsg->ulLength        = sizeof(MMC_LMM_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* Call Vos function send message */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmBgSearchHrpdReq():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* internal message send */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}

/*****************************************************************************
Function Name   :   NAS_MMC_SndLmmStopBgSearchHrpdReq
Description     :   MMC send message MMC_LMM_STOP_BG_SEARCH_HRPD_REQ to LMM
Input parameters:   VOS_VOID
Outout parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-04-07
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_VOID NAS_MMC_SndLmmStopBgSearchHrpdReq(VOS_VOID)
{
    MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU                   *pstMsg     = VOS_NULL_PTR;

    /* apply for memory */
#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    pstMsg = (MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstMsg = (MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU));
#endif

    /* apply for memory  error, returns  */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopBgSearchHrpdReq():ERROR:Memory Alloc Error for pstMsg");

        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0X0,
               sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    /* fill message head */
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulMsgId         = ID_MMC_LMM_STOP_BG_SEARCH_HRPD_REQ;
    pstMsg->ulLength        = sizeof(MMC_LMM_STOP_BG_SEARCH_HRPD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

#if (defined (NAS_STUB) || defined(__PS_WIN32_RECUR__))
    /* Call Vos function send message */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMC, pstMsg ))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndLmmStopBgSearchHrpdReq():ERROR:SEND MESSAGE FAILURE");
    }
#else
    /* internal message send */
    NAS_MML_SndInternalMsg(pstMsg);
#endif

    return;
}
/* Added by l00324781 for CDMA Iteration 10, 2015-4-7, end */
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

