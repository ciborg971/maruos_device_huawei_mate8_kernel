

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasComm.h"
#include "NasUtranCtrlMain.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMainTbl.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasMmlMsgProc.h"
#include "NasUtranCtrlMntn.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasMmlLib.h"

#include "NasMmcSndInternalMsg.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_MAIN_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    VOS_UINT32                          ulRet;

    MSG_HEADER_STRU                    *pstMsgHeader;

#ifndef __PS_WIN32_RECUR__
    VOS_UINT32                          ulIsSndOmPcRecurMsgValid;
#endif

    pstMsgHeader = (MSG_HEADER_STRU *)pstSrcMsg;

    /* Ĭ��Ϊ����Ϣ��Ҫ����ԭ��MM��ģ�鴦�� */
    ulRet        = VOS_FALSE;

#if (FEATURE_ON == FEATURE_PTM)
    if (VOS_TRUE == NAS_MML_IsNeedNwSearchInfoRecord(pstSrcMsg))
    {
        NAS_MML_RecordNwSearchInfo(pstSrcMsg);
    }
#endif

    /* ƽ̨��W/TD����֧��ʱ��ֱ�ӷ���VOS_FALSE */
    if (VOS_FALSE == NAS_MML_IsPlatformSupportUtran())
    {
        *ppstDestMsg = pstSrcMsg;
        return VOS_FALSE;
    }

    /* �жϽ���PIDΪMMC������PID���䴦���� */
    switch (pstMsgHeader->ulReceiverPid)
    {
        case WUEPS_PID_MMC:

            ulRet = NAS_UTRANCTRL_ProcessMmcMsg(pstSrcMsg);
            break;

        default:

            break;
    }

    /* ��Ϣ��Ҫ����������Ҫ����Ϣ���������罫TDS��PID����ΪWCDMA��PID */
    if (VOS_FALSE == ulRet)
    {
        NAS_UTRANCTRL_PostProcMsg(pstSrcMsg, ppstDestMsg);
    }

#ifndef __PS_WIN32_RECUR__

    /* UTRANCTRLģ��Ļط���Ϣ���� */
    ulIsSndOmPcRecurMsgValid = NAS_UTRANCTRL_IsSndOmPcRecurMsgValid();

    if ((VOS_TRUE == NAS_UTRANCTRL_GetUePcRecurFlg())
     && (VOS_TRUE == ulIsSndOmPcRecurMsgValid))
    {
        NAS_UTRANCTRL_SetUePcRecurFlg(VOS_FALSE);
        NAS_UTRANCTRL_SndOutsideContextData();
    }
#endif

    return ulRet;
#else

    *ppstDestMsg = pstSrcMsg;

    /* ���������� */
    return VOS_FALSE;
#endif
}


VOS_VOID NAS_UTRANCTRL_ProcBufferMsg(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    struct MsgCB                       *pstNextBufferMsg     = VOS_NULL_PTR;
    struct MsgCB                       *pstNextBufferDestMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /* ���ж��Ƿ���Դ���UTRANCTRLģ��Ļ�����Ϣ */
    if (NAS_UTRANCTRL_FSM_MAIN == NAS_UTRANCTRL_GetCurrFsmId())
    {
        /* ��UTRANCTRLģ���ȡ������ⲿ��Ϣ */
        pstNextBufferMsg = NAS_UTRANCTRL_GetNextCachBufferMsg();

        while (VOS_NULL_PTR != pstNextBufferMsg)
        {
            /* ����ǰ��Ϣ����UTRANCTRLģ����д��� */
            ulRslt = NAS_UTRANCTRL_MsgProc(pstNextBufferMsg, &pstNextBufferDestMsg);

            /* ��Ϣ��UTRANCTRLģ��δ�������,������MMC�������� */
            if (VOS_FALSE == ulRslt)
            {
                /* �����UTRANCTRLģ���ȡ�Ļ�����Ϣ */
                NAS_MML_MsgProc(pstNextBufferDestMsg);
            }

            /* ��Ϣ��UTRANCTRL����󣬿������½���״̬������Ҫ������ǰ������Ϣѭ������ */
            if (NAS_UTRANCTRL_FSM_MAIN != NAS_UTRANCTRL_GetCurrFsmId())
            {
                /* ����ѭ�� */
                break;
            }

            /* Ѱ����һ��UTRANCTRLģ�黺����ⲿ��Ϣ */
            pstNextBufferMsg = (struct MsgCB *)NAS_UTRANCTRL_GetNextCachBufferMsg();
        }
    }
#endif
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

VOS_UINT32 NAS_UTRANCTRL_ProcessMmcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRslt;
    MSG_HEADER_STRU                    *pstMsgHeader;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enPreFsmId;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ȡ�õ�ǰ��Ϣ���¼����� */
    ulEventType = NAS_UTRANCTRL_GetMsgEventType(pstMsg);

    /* UTRANCTRL ģ��Ķ�ʱ����Ҫ�ڳ�ʱʱͳһֹͣ��ʱ��,���㹴��SDT��Ϣ */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        /* UTRANCTRL�Ķ�ʱ����ʱ���������ֹͣ,MMC�Ķ�ʱ����MMCģ��ֹͣ */
        if (pRcvTimerMsg->ulName >= NAS_UTRANCTRL_TIMER_ID_START_INDEX)
        {
            NAS_UTRANCTRL_StopTimer((NAS_MMC_TIMER_ID_ENUM_UINT16)(pRcvTimerMsg->ulName));
        }
    }

#if defined(__PC_TRACE_RECUR__)
    /* ����������ط���Ϣ */
    if (NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY == pstMsgHeader->ulMsgName)
    {
        NAS_UTRANCTRL_RestoreContextData_Main(ulEventType, pstMsg);
        return VOS_TRUE;
    }
#endif


    /* �жϵ�ǰ�Ƿ���Ҫ��Utran״̬������*/
    if ( VOS_FALSE == NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg(pstMsg))
    {
        return VOS_FALSE;

    }

    /* ״̬������֮ǰ,ȡ�õ�ǰ��״̬������ */
    enPreFsmId = NAS_UTRANCTRL_GetCurrFsmId();

    /* �ڵ�ǰ״̬���д���ǰ��Ϣ */
    ulRslt = NAS_UTRANCTRL_ProcessMsgInFsm(ulEventType, pstMsg);

    /* �ɿ���̬ת������״̬������Ҫ��������ǰ��Ϣ */
    if ((NAS_UTRANCTRL_FSM_MAIN   != NAS_UTRANCTRL_GetCurrFsmId())
     && (NAS_UTRANCTRL_FSM_MAIN   == enPreFsmId))
    {
        /* ״̬������֮ǰ,ȡ�õ�ǰ��״̬������ */
        enPreFsmId = NAS_UTRANCTRL_GetCurrFsmId();

        ulRslt = NAS_UTRANCTRL_ProcessMsgInFsm(ulEventType, pstMsg);
    }

    /* ������״̬���л���IDLE״̬��,��������������SYSCFG������Ϣ */
    if ((NAS_UTRANCTRL_FSM_MAIN == NAS_UTRANCTRL_GetCurrFsmId())
     && (NAS_UTRANCTRL_FSM_MAIN != enPreFsmId))
    {
        NAS_UTRANCTRL_ClearBufferedSndUtranReqMsg();
    }

    /* ������Ϣ�Ĵ����� */
    return ulRslt;
}
VOS_VOID  NAS_UTRANCTRL_PostProcMsg(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    MSG_HEADER_STRU                    *pstMsgHeader;

    pstEntryMsg                         = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �ж��Ƿ���Ҫ�滻�����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetReplaceMmcMsgFlg())
    {
        *ppstDestMsg = (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer;

        /* ��Ϣ�Ѿ�ʹ�ã��ظ����ñ��λ�������������Ϣ��  */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_FALSE);
    }
    else
    {
        *ppstDestMsg = pstSrcMsg;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)(*ppstDestMsg);

    switch (pstMsgHeader->ulSenderPid)
    {
        case TPS_PID_PDC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_PDCP;
            break;

        case TPS_PID_RLC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_RLC;
            break;

        case TPS_PID_RRC:

            (*ppstDestMsg)->ulSenderPid = WUEPS_PID_WRR;
            break;

         default:
            break;
    }

}



VOS_VOID NAS_UTRANCTRL_RegFsm( VOS_VOID  )
{
    /* ������ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetMainFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:MainProcess",
                         NAS_UTRANCTRL_GetMainProcessStaTblSize(),
                         NAS_UTRANCTRL_GetMainProcessStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_Main);


    /* ����״̬��ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetSwitchOnFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:SwitchOnProcess",
                         NAS_UTRANCTRL_GetSwitchOnStaTblSize(),
                         NAS_UTRANCTRL_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_SwitchOn);

    /* �ػ�״̬��ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetPowerOffFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:PowerOffProcess",
                         NAS_UTRANCTRL_GetPowerOffStaTblSize(),
                         NAS_UTRANCTRL_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_PowerOff);

    /* ����״̬��ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetPlmnSelectionFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:PlmnSelectionProcess",
                         NAS_UTRANCTRL_GetPlmnSelectionStaTblSize(),
                         NAS_UTRANCTRL_GetPlmnSelectionStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_PlmnSelection);

    /* SYSCFG״̬��ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetSysCfgFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:SYSCFG",
                         NAS_UTRANCTRL_GetSysCfgStaTblSize(),
                         NAS_UTRANCTRL_GetSysCfgStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_Syscfg);

    /* mode change״̬��ע�� */
    NAS_FSM_RegisterFsm(NAS_UTRANCTRL_GetModeChangeFsmDescAddr(),
                         "NAS_UTRANCTRL:FSM:ModeChange",
                         NAS_UTRANCTRL_GetModeChangeStaTblSize(),
                         NAS_UTRANCTRL_GetModeChangeStaTbl(),
                         VOS_NULL_PTR,
                         NAS_UTRANCTRL_InitFsmCtx_ModeChange);


    return;
}




VOS_UINT32 NAS_UTRANCTRL_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_UTRANCTRL_FSM_CTX_STRU         *pstCurFsm;
    VOS_UINT32                          ulRslt;

    NAS_UTRANCTRL_FSM_ID_ENUM_UINT32    enCurrFsmId;

    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ȡ�õ�ǰ��״̬������ */
    enCurrFsmId = NAS_UTRANCTRL_GetCurrFsmId();

    /* ��ȡ��ǰUTRANCTRL��״̬����ַ */
    pstCurFsm           = NAS_UTRANCTRL_GetCurFsmAddr();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstCurFsm->pstFsmDesc, pstCurFsm->ulState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* ��״̬���ж���Ϣ���д��� */
        ulRslt = (*pActFun) (ulEventType, (struct MsgCB *)pstMsg);
        return ulRslt;
    }

    /* ֪ͨ�����ģʽ֪ͨ��SYSCFG���õ�ʱ�򣬻��������Ҳ�������Ϣ */
    if ((NAS_UTRANCTRL_FSM_MODE_CHANGE == enCurrFsmId)
     || (NAS_UTRANCTRL_FSM_SYSCFG      == enCurrFsmId))
    {
        /* ��Ϣ���ȳ����˻���ĳ��ȣ��򲻱���, ��ֹ����Խ�� */
        if ( (pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH) > NAS_UTRANCTRL_MAX_MSG_BUFFER_LEN )
        {
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ProcessMsgInFsm:Msg too big to save ");

            /* ״̬����δ�ҵ�Ҫ�������Ϣ,����������� */
            return VOS_FALSE;
        }

        NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

        /* ������Ϣ,��ǰMMC״̬��������,������������㻺�� */
        return VOS_TRUE;
    }

    /* ״̬����δ�ҵ�Ҫ�������Ϣ,����������� */
    return VOS_FALSE;
}

#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
