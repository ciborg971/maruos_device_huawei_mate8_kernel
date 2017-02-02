

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasGmmSndOm.h"
#include "NasUtranCtrlInterface.h"
#include "NasMmlCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASSUSPEND_C



/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
GMM_CAS_MSG_BUFFER_STRU     gstGmmCasMsgBuf;                /* ������Ϣ�������� */
extern VOS_UINT32 g_ulGmmDelaySuspendRsp;

/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM������Ϣ�Ļ��洦��  -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_BufferMsgQueueIn
 Description    : �õ���Ϣ������еĿ���λ��
                  HSS 4100 V200R001 ����
 Input          : struct MsgCB*     pMsgIn            ���������Ϣָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_BufferMsgQueueIn(VOS_VOID)
{
    VOS_UINT32      ulIndex = 0;
    VOS_UINT32      ulRet = GMM_CAS_MSG_NUMBER_MAX;         /* ��Чֵ */

    /* ˳����δ�ͷŵĻ�����Ϣ */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* ������Ϣ����λ�� */
        if (GMM_MSG_BUFFER_FLAG_IDLE
         == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            ulRet = ulIndex;
            break;
        }
    }

    return ulRet;   /* ������Ϣ���е�ͷ������λ�õ����� */

}

/*****************************************************************************
 Prototype      : GMM_BufferMsgQueueOut
 Description    : ����Ϣ�������ȡ��GMM������Ϣ��λ��
                  HSS 4100 V200R001 ����
 Input          : struct MsgCB*     pMsgOut            ��ȡ������Ϣָ��
 Output         :
 Return Value   : >=0
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_BufferMsgQueueOut(VOS_VOID)
{
    VOS_UINT32      ulIndex = 0;
    VOS_UINT32      ulRet = GMM_CAS_MSG_NUMBER_MAX;         /* ��Чֵ */

    /* ˳����δ�ͷŵĻ�����Ϣ */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* ��Ч�Ļ�����Ϣ */
        if (GMM_MSG_BUFFER_FLAG_USED
        == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            ulRet = ulIndex;
            break;
        }
    }

    return ulRet;   /* ������Ϣ���е�ͷ��������Ϣ������ֵ */
}


VOS_UINT32 GMM_BufferMsgSend(VOS_VOID)
{
    VOS_VOID       *pBufMsg;
    VOS_UINT32      ulIndex;
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    /* ȡ�õ�ǰ����ͷ�˵����� */
    ulIndex = GMM_BufferMsgQueueOut();
    if (GMM_CAS_MSG_NUMBER_MAX == ulIndex)
    {
        GMM_LOG_WARN("GMM_BufferMsgSend():Warning: Buffer is empty");
        return GMM_FALSE;               /* ���󷵻� */
    }

    /* ȡ����Ϣ����ָ�� */
    pBufMsg = gstGmmCasMsgBuf.apBufMsg[ulIndex];

    pNasMsgHeader = (MSG_HEADER_STRU *)pBufMsg;                                 /* �õ���Ϣͷ                               */

    if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*) pBufMsg))
        {
            return GMM_TRUE;
        }
    }

    /* ֱ�ӵ���GMM����Ϣ������ */
    Gmm_MsgDistribute(pBufMsg);

    return GMM_TRUE;
}


VOS_VOID NAS_GMM_ClearSameMsgFromBuff(
        struct MsgCB                   *pstMsgIn,
        VOS_UINT32                     *pulIndex
)
{
    MSG_HEADER_STRU                    *pstBuffMsg;
    MSG_HEADER_STRU                    *pstInputMsg;
    VOS_UINT32                          i;

    pstInputMsg = (MSG_HEADER_STRU *)pstMsgIn;

    /* ���һ������Ѿ����ڵ���ͬ����Ϣ���ͣ�����ҵ���
       ��ԭ���Ļ�����Ϣ����������µ���Ϣ�洢����λ�� */
    for (i = 0; i < gstGmmCasMsgBuf.ucBufMsgTotal; i++)
    {
        pstBuffMsg = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[i];
        if (pstBuffMsg->ulMsgName == pstInputMsg->ulMsgName)
        {
            Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[i]);
            gstGmmCasMsgBuf.apBufMsg[i]     = VOS_NULL_PTR;
            gstGmmCasMsgBuf.aucBufMsgFlg[i] = GMM_MSG_BUFFER_FLAG_IDLE;

            gstGmmCasMsgBuf.ucBufMsgTotal--;

            *pulIndex = i;
            break;
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgReceive
 Description    : GMM������Ϣ������Ϣ�������
                  HSS 4100 V200R001 ����
 Input          : struct MsgCB*     pMsgIn            ���������Ϣָ��
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_BufferMsgReceive(struct MsgCB* pMsgIn)
{
    VOS_UINT32      ulInsert;
    VOS_UINT32      ulMsgSize;
    MSG_CB         *pMsgNew;

    /* �õ���Ϣ��������Ĳ���λ�� */
    ulInsert  = GMM_BufferMsgQueueIn();
    if (GMM_CAS_MSG_NUMBER_MAX == ulInsert)
    {
        GMM_LOG_WARN("GMM_BufferMsgReceive():Warning: Buffer is full");
        return;
    }

    /* ���ƴ�������Ϣ���� */
    ulMsgSize = pMsgIn->ulLength;
    /*pMsgNew   = (MSG_CB*)VOS_AllocMsg(WUEPS_PID_GMM,
                    ulMsgSize - VOS_MSG_HEAD_LENGTH );*/
    pMsgNew   = (MSG_CB*)PS_MEM_ALLOC(WUEPS_PID_GMM, (ulMsgSize + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pMsgNew)
    {
        GMM_LOG_ERR("GMM_BufferMsgReceive():Error: Invalid results of VOS_AllocMsg()");
        return;
    }

    /* ������ͬһ����Ϣֻ�洢һ����ֻ�������µ���Ϣ��
       �ѻ����оɵ���ͬ����Ϣɾ�� */
    NAS_GMM_ClearSameMsgFromBuff(pMsgIn, &ulInsert);

    /*modify,sunxibo,2006-03-02,itt begin*/
    Gmm_MemCpy(pMsgNew, pMsgIn, (ulMsgSize + VOS_MSG_HEAD_LENGTH));                 /* ��Ϣ���ݸ��� */
    /*modify,sunxibo,2006-03-02,itt end*/

    /* ���뵽������� */
    gstGmmCasMsgBuf.apBufMsg[ulInsert]     = (VOS_VOID*)pMsgNew;
    gstGmmCasMsgBuf.aucBufMsgFlg[ulInsert] = GMM_MSG_BUFFER_FLAG_USED;

    if (gstGmmCasMsgBuf.ucBufMsgTotal < GMM_CAS_MSG_NUMBER_MAX)
    {
        gstGmmCasMsgBuf.ucBufMsgTotal ++;
    }

    return;                    /* �������� */
}
VOS_VOID NAS_GMM_ClearMsgFromBuff(
        VOS_UINT32                     ulMsgName,
        VOS_UINT32                     ulSenderPid,
        VOS_UINT32                     ulReceiverPid
)
{
    MSG_HEADER_STRU                    *pstBuffMsg;
    VOS_UINT32                          i;

    /* ���һ������Ѿ����ڵ���ͬ����Ϣ���ͣ�����ҵ���
       ��ԭ���Ļ�����Ϣ����������µ���Ϣ�洢����λ�� */
    for (i = 0; i < gstGmmCasMsgBuf.ucBufMsgTotal; i++)
    {
        pstBuffMsg = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[i];
        if ( (pstBuffMsg->ulMsgName == ulMsgName)
          && (pstBuffMsg->ulSenderPid == ulSenderPid)
          && (pstBuffMsg->ulReceiverPid == ulReceiverPid) )
        {
            Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[i]);
            gstGmmCasMsgBuf.apBufMsg[i]     = VOS_NULL_PTR;
            gstGmmCasMsgBuf.aucBufMsgFlg[i] = GMM_MSG_BUFFER_FLAG_IDLE;

            gstGmmCasMsgBuf.ucBufMsgTotal--;
            break;
        }
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_BufferMsgResume
 Description    : GMM������Ϣ�Ļָ��������
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_BufferMsgResume(VOS_VOID)
{
    VOS_UINT32  ulIndex = 0;

/*
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucBufMsgResFlg)
    {
        return GMM_FALSE;
    }

    gstGmmCasGlobalCtrl.ucBufMsgResFlg = GMM_FALSE;
*/

    /* �ж��Ƿ���ڻ�����Ϣ */
    if ( 0 == gstGmmCasMsgBuf.ucBufMsgTotal )
    {
        /* �����ڻ�����Ϣ */
        GMM_LOG_WARN("GMM_BufferMsgResume():Warning: Buffer is empty");
        return;               /* �������� */
    }

    /* ˳���黺������еĻ�����Ϣ */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* ���ͻ�����Ϣ����ͷ�˵���Ϣ */
        if (GMM_FALSE == GMM_BufferMsgSend())
        {
            continue;
        }

        /* �ͷŻ�����Ϣ���� */
        Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[ulIndex]);
        /* VOS_MemFree(WUEPS_PID_GMM, gstGmmCasMsgBuf.apBufMsg[ulIndex]); */

        gstGmmCasMsgBuf.apBufMsg[ulIndex] = VOS_NULL_PTR;   /* �ÿ�ָ�� */

        /* ��ָ���ͷű�־ */
        gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex]  = GMM_MSG_BUFFER_FLAG_IDLE;

        gstGmmCasMsgBuf.ucBufMsgTotal--;

        /* ������Ϣ�������� */
        if (0 == gstGmmCasMsgBuf.ucBufMsgTotal)
        {
            break;
        }

    }

    return;                    /* �������� */
}


VOS_VOID GMM_BufferMsgDump(VOS_VOID)
{
    VOS_UINT32  ulIndex;

    MSG_HEADER_STRU                     *pNasMsgHeader = VOS_NULL_PTR;

    /* �ж��Ƿ���ڻ�����Ϣ */
    if ( 0 == gstGmmCasMsgBuf.ucBufMsgTotal )
    {
        /* �����ڻ�����Ϣ */
        GMM_LOG_WARN("GMM_BufferMsgDump():Warning: Buffer is already empty");
        return;               /* �������� */
    }

    /* ˳���ͷŻ�������еĻ�����Ϣָ�� */
    for (ulIndex=0; ulIndex<GMM_CAS_MSG_NUMBER_MAX; ulIndex++)
    {
        /* ������Ϣ���ͷ� */
        if (GMM_MSG_BUFFER_FLAG_IDLE
         == gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex])
        {
            continue;
        }


        /* ���ͷŻ���ʱ�򣬸�SM�ظ����������SMģ��һֱ�ȴ��˽������ʱ����ʱ */
        pNasMsgHeader = (MSG_HEADER_STRU *)gstGmmCasMsgBuf.apBufMsg[ulIndex];
        if ((WUEPS_PID_SM           == pNasMsgHeader->ulSenderPid)
         && (GMMSM_ESTABLISH_REQ    == pNasMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_UNKNOWN);
        }

        /* �ͷ���Ϣָ������ */
        Gmm_MemFree(gstGmmCasMsgBuf.apBufMsg[ulIndex]);
        /* VOS_MemFree(WUEPS_PID_GMM, gstGmmCasMsgBuf.apBufMsg[ulIndex]); */
        gstGmmCasMsgBuf.apBufMsg[ulIndex] = VOS_NULL_PTR;   /* �ÿ�ָ�� */

        /* ��ָ���ͷű�־ */
        gstGmmCasMsgBuf.aucBufMsgFlg[ulIndex]  = GMM_MSG_BUFFER_FLAG_IDLE;

        /* ������Ϣ�������� */
        if (gstGmmCasMsgBuf.ucBufMsgTotal > 0)
        {
            gstGmmCasMsgBuf.ucBufMsgTotal--;
        }
        else
        {
            gstGmmCasMsgBuf.ucBufMsgTotal = 0;
        }
    }

    return;                    /* �������� */
}


VOS_VOID NAS_GMM_BackupCcoFallbackCtx(VOS_VOID)
{
    /* ��g_GmmGlobalCtrl.stBackShare���и�ֵ����g_GmmGlobalCtrl.stBackShare
       �ĳ�Աȡֵ������g_GmmGlobalCtrl��������Ա���� */
    g_GmmGlobalCtrl.stBackupShare.ucState                   = g_GmmGlobalCtrl.ucState;

    g_GmmGlobalCtrl.stBackupShare.ucNtMod                   = g_GmmGlobalCtrl.ucNetMod;

    g_GmmGlobalCtrl.stBackupShare.ucPsSigConnFlg            = g_GmmGlobalCtrl.ucSigConFlg;

    g_GmmGlobalCtrl.stBackupShare.enPsIntegrityProtect      = g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect;

    g_GmmGlobalCtrl.stBackupShare.ucRauAttmptCnt            = g_GmmRauCtrl.ucRauAttmptCnt;

    g_GmmGlobalCtrl.stBackupShare.ucSrvState                = gstGmmCasGlobalCtrl.GmmSrvState;

    /* PS���security information */
    g_GmmGlobalCtrl.stBackupShare.stPsSecutityInfo = g_GmmGlobalCtrl.PsSecutityInfo;

    /* �ϴ�פ����ϵͳ��Ϣ  */
    g_GmmGlobalCtrl.stBackupShare.stSysInfo = g_GmmGlobalCtrl.SysInfo;


    /* UE ��Ϣ */
    g_GmmGlobalCtrl.stBackupShare.stUeInfo =  g_GmmGlobalCtrl.UeInfo;
    g_GmmGlobalCtrl.stBackupShare.stUeInfo.ucUpdateSta = NAS_MML_GetPsUpdateStatus();


    PS_MEM_CPY(&(g_GmmGlobalCtrl.stBackupShare.stBackupEquPlmnInfo),
               NAS_MML_GetEquPlmnList(), sizeof(NAS_MML_EQUPLMN_INFO_STRU));


#if (FEATURE_ON == FEATURE_LTE)
    g_GmmGlobalCtrl.stBackupShare.enTinType = NAS_MML_GetTinType();
#endif

    g_GmmGlobalCtrl.stBackupShare.ucT3311Status = (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3311));
}
VOS_VOID NAS_GMM_ResumeCcoFallbackCtx(VOS_VOID)
{

    /* ��g_GmmGlobalCtrl�ĳ�Ա������ֵ����ֵ����Դ
       ������g_GmmGlobalCtrl.stBackupShare */

    NAS_MML_EQUPLMN_INFO_STRU          *pstBackupEplmnList;
    NAS_MML_EQUPLMN_INFO_STRU          *pstCurrentEplmnList;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif


    g_GmmGlobalCtrl.ucState                                 = g_GmmGlobalCtrl.stBackupShare.ucState;

    g_GmmGlobalCtrl.ucNetMod                                = g_GmmGlobalCtrl.stBackupShare.ucNtMod;

    g_GmmGlobalCtrl.ucSigConFlg                             = g_GmmGlobalCtrl.stBackupShare.ucPsSigConnFlg;

    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect           = g_GmmGlobalCtrl.stBackupShare.enPsIntegrityProtect;

    g_GmmRauCtrl.ucRauAttmptCnt                             = g_GmmGlobalCtrl.stBackupShare.ucRauAttmptCnt;

    gstGmmCasGlobalCtrl.GmmSrvState                         = g_GmmGlobalCtrl.stBackupShare.ucSrvState;

    /* PS���security information */
    g_GmmGlobalCtrl.PsSecutityInfo = g_GmmGlobalCtrl.stBackupShare.stPsSecutityInfo;

    /* �ϴ�פ����ϵͳ��Ϣ  */
    g_GmmGlobalCtrl.SysInfo = g_GmmGlobalCtrl.stBackupShare.stSysInfo;

    /* UE ��Ϣ */
    g_GmmGlobalCtrl.UeInfo = g_GmmGlobalCtrl.stBackupShare.stUeInfo;

    NAS_MML_SetPsUpdateStatus(g_GmmGlobalCtrl.stBackupShare.stUeInfo.ucUpdateSta);


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);

    pstBackupEplmnList  = &(g_GmmGlobalCtrl.stBackupShare.stBackupEquPlmnInfo);

    pstCurrentEplmnList = NAS_MML_GetEquPlmnList();

    if (VOS_TRUE == NAS_MML_IsEquPlmnInfoChanged(pstBackupEplmnList))
    {
        /* ��EPLMN���浽MMLȫ�ֱ��� */
        PS_MEM_CPY(pstCurrentEplmnList, pstBackupEplmnList, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

        /* ��EPLMN���µ�NV�� */
        NAS_GMM_WriteEplmnNvim(pstCurrentEplmnList);
    }


 #if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_WriteTinInfoNvim(g_GmmGlobalCtrl.stBackupShare.enTinType, pstRplmnCfgInfo->aucLastImsi);
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != g_GmmGlobalCtrl.stBackupShare.enTinType)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }

 #endif

    /* ���ݱ���ǰ��3311��ʱ��״̬�ָ����� */
    if (0 != (g_GmmGlobalCtrl.stBackupShare.ucT3311Status & (0x00000001 << GMM_TIMER_T3311)))
    {
        Gmm_TimerStart(GMM_TIMER_T3311);
    }


#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
#else
{
    /* W��PMM-CONNECTED̬��Ҫֹͣ3312 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg))
    {
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
    }

    /* G��ready timer��������ֹͣ3312 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TIMER_T3314_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3314_FLG)))
    {
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);
    }
}

#endif
}




VOS_VOID GMM_RcvMmcSuspendInd(VOS_VOID* pRcvMsg)
{
    MMCGMM_SUSPEND_IND_ST              *pSuspendIndMsg;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurUtranMode;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGprsSuspendFlg;


    ulGprsSuspendFlg    = VOS_FALSE;
#endif

    /* GSMģʽ������� */
    pSuspendIndMsg      = (MMCGMM_SUSPEND_IND_ST *)pRcvMsg;

    GMM_LOG_INFO("GMM_RcvMmcSuspendInd:Receive MMC_SUSPEND_IND");

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    /* ָʾRABM��ǰϵͳģʽ, ������RABM, bRatChangeFlgΪTRUE */
    NAS_GMM_SndRabmSysSrvChgInd(pSuspendIndMsg->ucSuspendOrigen,
                                VOS_TRUE,
                                VOS_TRUE,
                                VOS_TRUE);



    if ( NAS_MML_NET_RAT_TYPE_GSM == pSuspendIndMsg->ucSuspendDestination)
    {
        NAS_GMM_SndGasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI | RRC_NAS_MASK_ATTACH);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_GPRS_SUSPENSION:
            gstGmmCasGlobalCtrl.GmmSrvState       = gstGmmSuspendCtrl.ucPreSrvState;

#if (FEATURE_ON == FEATURE_LTE)
            ulGprsSuspendFlg    = VOS_TRUE;
#endif

            break;

        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            Gmm_TimerStop(GMM_TIMER_SUSPENDED);
            GMM_ResumeFailure();
            break;

        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_WARN("GMM_RcvGasSuspensionInd:Receive RRMM_GPRS_SUSPENSION_IND in abnormal state.");
            return;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
            {
                GMM_BufferMsgDump();
            }
            break;
        case GMM_DEREGISTERED_INITIATED:
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {
                Gmm_TimerStop(GMM_TIMER_PROTECT);
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
            }
            /*��ϵͳ�ı�ʱ,���RA�����ı䣬��RAU��ɺ����Detach���̣�
            ���RAû�иı䣬��ͨ��Detach��ʱ����ʱ��֤Detach���̼�������ϵͳ���ı�ʱ
            ֱ�����¿�ʼDetach����*/
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            break;
        default:
            break;
    }

    /*�����л�֮ǰ��״̬������ģʽ*/
    if ((GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_NORMAL_SERVICE != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
     && (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {
        gstGmmSuspendCtrl.ucPreState                  = g_GmmGlobalCtrl.ucState;
    }

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_GetCurrNetRatType();
    gstGmmSuspendCtrl.ucSuspendCause              = pSuspendIndMsg->ucSuspendCause;

    /* ��ȡ�л�֮ǰ�ķ���״̬ */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if (VOS_TRUE == NAS_GMM_IsDeregisterState(g_GmmGlobalCtrl.ucState))
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            gstGmmSuspendCtrl.ucPreSrvState       = GMM_IU_PMM_IDLE;
        }
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        gstGmmSuspendCtrl.ucPreSrvState           = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    else
    {
        ;
    }

    if (MMC_SUSPEND_CAUSE_CELLCHANGE == pSuspendIndMsg->ucSuspendCause)
    {
        /* ����GMM��ȫ�ֱ���������CCO����ʱʹ�� */
        NAS_GMM_BackupCcoFallbackCtx();
    }


    GMM_SuspendTimer();

    Gmm_ComStaChg(GMM_SUSPENDED_NORMAL_SERVICE);

    /* HO�����У�L���й�������ʱ����Ҫ��L��ȡ��ȫ������ */
#if   (FEATURE_ON == FEATURE_LTE)
    /* 3GPP 24008 4.7.5.1.1�½�����:
       If the routing area updating procedure is not initiated by the MS due to
       an S1 mode to Iu mode or S1 mode to A/Gb mode intersystem change,
       or if it is initiated due to such an intersystem change and the TIN
       indicates "RAT related TMSI", the MS shall use the existing UMTS
       security context for the PS domain. The ROUTING AREA UPDATE REQUEST
       message shall contain the P-TMSI signature when received in a previous
       ATTACH ACCEPT or ROUTING AREA UPDATE ACCEPT message.
       If the MS has a valid UMTS security context, the MS shall indicate
       it in the GPRS ciphering key sequence number IE.*/

    if ((MMC_SUSPEND_CAUSE_HANDOVER == pSuspendIndMsg->ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_LTE == pSuspendIndMsg->ucSuspendOrigen))
    {
        /* ����PS�İ�ȫ������,����HOʧ�ܵĻ��� */
        PS_MEM_CPY(&(g_GmmGlobalCtrl.stBackupShare.stSimPsSecurity),
                   NAS_MML_GetSimPsSecurity(), sizeof(NAS_MML_SIM_PS_SECURITY_INFO_STRU));


        /* ��Lģ����GMM_LMM_HO_SECU_INFO_REQ */
        NAS_GMM_SndLmmHoSecuInfoReq();

        gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

        return;
    }
    /* �������Ŀ�ķ�ΪLTE��֪ͨLMMģ��Gmm������״̬ */
    if ((NAS_MML_NET_RAT_TYPE_LTE == pSuspendIndMsg->ucSuspendDestination)
     && (NAS_MML_NET_RAT_TYPE_LTE != pSuspendIndMsg->ucSuspendOrigen))
    {
        /* ֻ��Gģ������״̬,����PS��״̬�ǹ��������������յ�gas��gprs suspend ind��Ϣʱ֪ͨ */
        NAS_GMM_SndLmmInfoChangeNotifyReq(NAS_MML_GetCurrNetRatType(),
                                          VOS_TRUE,
                                          VOS_FALSE,
                                          gstGmmSuspendCtrl.ucPreSrvState,
                                          ulGprsSuspendFlg);
    }

#endif

#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
    if (1 == g_ulGmmDelaySuspendRsp)
    {
        Gmm_TimerStart(GMM_TIMER_TC_DELAY_SUSPEND_RSP);
        return;
    }
#endif


    /* ����GCF����ԭ��TC״̬�£���W2G����ϵͳ�л�����£���Ҫ�ӳ�һ��ʱ���ٻظ�
       ������������������ʱ��������ʱ����ʱ���ٻظ���������
       ���ڴ˴�״̬��Ǩ�ƣ���ʹ���л�֮ǰGMM״̬�����жϡ�
       W2L����ʱ���˴���֪�������Ŀ�ķ�����Ҳ�����˴�����ֻ���ӳ��ϱ���������û������Ӱ�� */
    /* ����Ŀ�ķ�ΪGSM,������ʱ��,ΪLTEʱ��������ʱ�� */
    enCurUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurUtranMode)
     && (NAS_MML_NET_RAT_TYPE_GSM == pSuspendIndMsg->ucSuspendDestination))
    {
        Gmm_TimerStart(GMM_TIMER_TC_DELAY_SUSPEND_RSP);
        return;
    }


    Gmm_TimerStart(GMM_TIMER_SUSPENDED);

    GMM_SndMmcSuspendRsp();
}


VOS_VOID GMM_RcvMmcResumeInd(VOS_VOID* pRcvMsg)
{
    MMCGMM_RESUME_IND_ST                *pResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurrNetType;


    enCurrNetType = NAS_MML_GetCurrNetRatType();
    /* GSMģʽ������� */
    pResumeIndMsg = (MMCGMM_RESUME_IND_ST *)pRcvMsg;

    /* �յ�resume ind��Ϣ��ָ�RABM�Ĵ��� */
    NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd();

    /* �յ�resume ind��Ϣ��PS�������ӵĴ��� */
    NAS_GMM_ProcPsSigConn_ResumeInd(pResumeIndMsg);


    /* GMM��mmc����resume rsp */
    NAS_GMM_SndMmcResumeRsp();


    if (GMM_SUSPENDED_NORMAL_SERVICE != g_GmmGlobalCtrl.ucState)
    {
        GMM_LOG_WARN("GMM_RcvMmcResumeInd:Receive MMCGMM_RESUME_IND in abnormal State.");
        return;
    }


    NAS_GMM_RcvMmcResumeInd_CcoFallbak();

    NAS_GMM_RcvMmcResumeInd_Handover(pResumeIndMsg);

    /*���������ϵͳ��ı䣬��Ҫ֪ͨ�����PTMSI��Ϣ*/
    if ( ( gstGmmSuspendCtrl.ucPreRat != enCurrNetType )
      && ( ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType )
        || ( NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType ) ) )
    {
        /* ��ϵͳ��GU�Ĵ��� */
        NAS_GMM_ProcResumeToGU(pResumeIndMsg);
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType)
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;

        /* GMM_TIMER_PROTECT_FOR_SIGNALING ����Ҫ�ָ� */
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_PROTECT_FOR_SIGNALING);

        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

        /* T3340����Ҫ�ָ� */
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(GMM_TIMER_T3340_FLG);

        /*���PS���ж���Ϣ�����ͣ���֪ͨSMSģ�鷢��ʧ��*/
        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
        {                                                                         /* SMS�ڵȴ���Ӧ                            */
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
            g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
        }
        /*add,sunxibo,2007-10-12,for intersystem end*/
    }
    /* ==>A32D12436 */
    else if (NAS_MML_NET_RAT_TYPE_GSM == gstGmmSuspendCtrl.ucPreRat)
    {
        if (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != gstGmmSuspendCtrl.ucSuspendCause)
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        }

        Gmm_TimerStop(GMM_TIMER_T3314);
        gstGmmSuspendCtrl.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_PROTECT_OLD_TLLI);

    }
    else
    {
    }
    /* <==A32D12436 */
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

#if   (FEATURE_ON == FEATURE_LTE)

    if ( NAS_MML_NET_RAT_TYPE_LTE == enCurrNetType )
    {
        NAS_GMM_ProcResumeToLTE();

        return ;
    }
#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* ��ϵͳ�任��EHRPD�µĴ��� */
    if ( MMC_RESUME_ORIGEN_HRPD == pResumeIndMsg->ucResumeOrigen )
    {
        NAS_GMM_ProcResumeToHRPD(pResumeIndMsg);

        return;
    }
#endif

    switch (pResumeIndMsg->ucPsResumeResult)
    {
        case MMC_RESUME_RESULT_SUCCESS:
            if (gstGmmSuspendCtrl.ucPreRat == enCurrNetType)
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:Switch back,PS resume successfully.");
                /*���˳ɹ�������*/
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

                if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                 && (GMM_SERVICE_REQUEST_INITIATED != gstGmmSuspendCtrl.ucPreState))
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    Gmm_RoutingAreaUpdateHandleFollowOn();
                }
            }
            else if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
                  || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS not register.");
                /*���˳ɹ�������*/
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_TimerStop( GMM_TIMER_T3310 );
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                /*  ��ע�������,˵��ԭ����ȥע����������״̬ */
                if (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState)
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                }

                GMM_ResumeFailure();

                /* resume�ɹ�ʱ������� */
                NAS_GMM_ProcBufferSmMsg_ResumeSuccess();
            }
            /*  rau init״̬cco����û�лָ�t3330����Ҫ����������״̬���仹��GMM_ROUTING_AREA_UPDATING_INITIATED��
                t3330��ʱ���·���rau�������ͷ����ӣ�ͣt3330������t3311��t3311��ʱ�ٽ���rau */
            else if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
                  && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause))
            {
                Gmm_TimerStart(GMM_TIMER_T3330);
            }
            else if ((MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
                  && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                  && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                Gmm_TimerStop(GMM_TIMER_T3312);

                NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);

                NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);

                /* PS�������ӵĸ���������MMCת����resume indָʾ */
            }
            else
            {
                GMM_LOG_INFO("GMM_RcvMmcResumeInd:Intersystem change,PS resume successfully.");
                if ( MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause )
                {
                    Gmm_TimerStart(GMM_TIMER_SUSPENDED);
                }
                Gmm_ComStaChg(GMM_SUSPENDED_WAIT_FOR_SYSINFO);
            }

            if ( gstGmmSuspendCtrl.ucPreRat != enCurrNetType )
            {
                if ( NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
                {
                    /* ����ѡ,cco,cco���˻ָ�ʱ��Ҫ�ô�ȫ�ֱ�����¼�����ں���������ԭ��ֵ��д */
                    if ((MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                        ||(MMC_SUSPEND_CAUSE_REDIRECTION == gstGmmSuspendCtrl.ucSuspendCause)
                        ||(MMC_SUSPEND_CAUSE_CELLCHANGE == gstGmmSuspendCtrl.ucSuspendCause))
                    {
                        g_GmmInterRatCellReselect = 1;
                    }
                }
            }

            break;
        case MMC_RESUME_RESULT_FAILURE:
            GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS resume failure.");
            GMM_ResumeTimer(GMM_TIMER_RESUME);
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            GMM_ResumeFailure();
            break;
        case MMC_RESUME_GPRS_SUSPENSION:
            if (NAS_MML_NET_RAT_TYPE_GSM != enCurrNetType)
            {
                GMM_LOG_WARN("GMM_RcvMmcResumeInd:PS resume result of MMCGMM_RESUME_IND is abnormal.");
                GMM_ResumeTimer(GMM_TIMER_RESUME);
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeFailure();
                return;
            }
            GMM_LOG_INFO("GMM_RcvMmcResumeInd:PS resume result is GPRS_SUSPENSION.");
            if (gstGmmSuspendCtrl.ucPreRat == enCurrNetType)
            {
                GMM_BufferMsgDump();
                Gmm_HoldBufferFree();                                           /* ���������Ϣ                             */
                Gmm_ComCnfHandle();
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);
                /*add,sunxibo,2007-10-05,for intersystem begin*/
                if (GMM_REGISTERED_NORMAL_SERVICE == gstGmmSuspendCtrl.ucPreState)
                {
                    g_GmmGlobalCtrl.ucSuspendProc                = GMM_TRUE;
                }
                /*add,sunxibo,2007-10-05,for intersystem end*/
            }
            else
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);
            }
            break;
        default:
            GMM_LOG_WARN("GMM_RcvMmcResumeInd:Receive MMCGMM_RESUME_IND in abnormal State.");
            break;
    }
}

/*****************************************************************************
 Prototype      : GMM_ResumeSuccess
 Description    : �յ�MMC�ָ�ָʾ�Ĵ���
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ResumeSuccess()
{
    GMM_BufferMsgResume();

    if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
    }

}


VOS_VOID GMM_ResumeFailure()
{
    RRMM_REL_IND_STRU      stRrRelIndMsg;

    if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
    {
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH);
        }
    }
    else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        stRrRelIndMsg.ulCnDomainId    = RRC_NAS_PS_DOMAIN;
        stRrRelIndMsg.ulRelCause      = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrRelIndMsg.ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrRelIndMsg);
    }
    else
    {
    }

    if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
    {
        gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
    }

    GMM_BufferMsgDump();
    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */
    Gmm_ComCnfHandle();
}
VOS_VOID NAS_GMM_ProcBufferSmMsg_ResumeSuccess()
{
    VOS_VOID                           *pstBuffMsg      = VOS_NULL_PTR;
    MSG_CB                             *pstTmpBuffMsg   = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ȡ�õ�ǰ����ͷ�˵����� */
    ulIndex = GMM_BufferMsgQueueOut();

    if (GMM_CAS_MSG_NUMBER_MAX == ulIndex)
    {
        return;
    }

    /* ȡ����Ϣ����ָ�� */
    pstTmpBuffMsg = (MSG_CB *)gstGmmCasMsgBuf.apBufMsg[ulIndex];

    /* ��Ϊ�ڹ��������,�����յ�PDP��������,������ҵ�񴥷���ATTACH������,
       ������ϵͳ����ѡ,�����ʱ��������SM��Ϣ,�ᵼ��PDP����ʧ��,
       ���Դ�ʱ�������SM��Ϣ */
    if ((WUEPS_PID_SM == pstTmpBuffMsg->ulSenderPid)
     && (GMM_CAS_MSG_NUMBER_MAX != ulIndex))
    {
        pstBuffMsg = (MSG_CB *)PS_MEM_ALLOC(WUEPS_PID_GMM, (pstTmpBuffMsg->ulLength + VOS_MSG_HEAD_LENGTH));

        if (VOS_NULL_PTR == pstBuffMsg)
        {
            GMM_LOG_ERR("NAS_GMM_ProcBufferSmMsg_ResumeSuccess():Error: Invalid results of VOS_AllocMsg()");
            return;
        }

        Gmm_MemCpy(pstBuffMsg, pstTmpBuffMsg, (pstTmpBuffMsg->ulLength + VOS_MSG_HEAD_LENGTH));                 /* ��Ϣ���ݸ��� */
    }

    if (VOS_NULL_PTR != pstBuffMsg)
    {
        GMM_BufferMsgReceive((struct MsgCB *)(pstBuffMsg));

        Gmm_MemFree(pstBuffMsg);
    }
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_GMM_ProcResumeToLTE(VOS_VOID)
{
    RRMM_REL_IND_STRU                    stRrMmRelIndMsg;

    VOS_UINT8                           aucTimerId[3];

    /* ps�İ�ȫ������ʧ�ܻ��� */
    if (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
    {
        NAS_MML_SetSimPsSecurity(&(g_GmmGlobalCtrl.stBackupShare.stSimPsSecurity));
    }

    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        NAS_GMM_SuspendLlcForInterSys();

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

        Gmm_TimerStop(GMM_TIMER_T3314);
    }

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);
    }
    else
    {
        GMM_ResumeTimer(GMM_TIMER_RESUME);
    }


    if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
     || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
    }

    gstGmmSuspendCtrl.ucPreState = GMM_SUSPENDED_NORMAL_SERVICE;

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        stRrMmRelIndMsg.ulCnDomainId    = RRC_NAS_PS_DOMAIN;
        stRrMmRelIndMsg.ulRelCause      = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrMmRelIndMsg.ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrMmRelIndMsg);
    }

    GMM_BufferMsgDump();

    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */

    Gmm_ComCnfHandle();

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        Gmm_TimerStop(GMM_TIMER_ALL_EXCEPT_T3312_T3323);
        return;
    }

    aucTimerId[0] = GMM_TIMER_T3312;
    aucTimerId[1] = GMM_TIMER_T3323;
    aucTimerId[2] = GMM_TIMER_T3302;
    NAS_GMM_TimerStopExceptSpecialTimers(3, aucTimerId);


    return;
}
#endif


#if (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_VOID NAS_GMM_ProcResumeToHRPD(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    /* ���ָ���ʱ�� */
    GMM_ResumeTimer(GMM_TIMER_NOT_RESUME);

    /* ״̬Ǩ�Ƶ��޷���״̬ */
    if ((0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
     || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
    }

    /* ������л���Ĳ��� */
    GMM_BufferMsgDump();

    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */

    Gmm_ComCnfHandle();

    /* ֹͣ���ж�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_ALL);

    return;
}
#endif

/*lint -restore */


VOS_VOID NAS_GMM_ProcRabmSysSrvChgInd_ResumeInd(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurrNetType;

    enCurrNetType   = NAS_MML_GetCurrNetRatType();

    /* �����W��ָʾRABM��ǰϵͳģʽ, ����PsResumeResult�����ָ�RABM, bRatChangeFlgΪTRUE,
       �����G�µȵ��յ�ϵͳ��Ϣ��ָ�RABM */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
    {
        /* L��W��HO�ɹ�, ��֪ͨ RABM �ȴ��ȴ�W�����RAB�Ļָ�; */
        /* CCO���˹�����, �������ϱ�RAB SETUP��SUCCESS, Ҳ��֪ͨ RABM �ȴ��ȴ�W�����RAB�Ļָ�; */
        if ( MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause
#if   (FEATURE_ON == FEATURE_LTE)
          || ( (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
             &&(NAS_MML_NET_RAT_TYPE_LTE   == gstGmmSuspendCtrl.ucPreRat) )
#endif
        )
        {
            NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_WCDMA,
                                        VOS_TRUE,
                                        VOS_FALSE,
                                        VOS_FALSE);
        }
        else
        {
            NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_WCDMA,
                                        VOS_TRUE,
                                        VOS_FALSE,
                                        VOS_TRUE);
        }
    }
    else
    {
        NAS_GMM_SndRabmSysSrvChgInd(enCurrNetType,
                                    VOS_TRUE,
                                    VOS_TRUE,
                                    VOS_TRUE);
    }

    return;
}


VOS_VOID NAS_GMM_ProcPsSigConn_ResumeInd(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    /* ��HO,���뼼�������ı� ɾ��PS�������� */
    if ((gstGmmSuspendCtrl.ucPreRat != NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause))
    {
        if (VOS_TRUE == NAS_MML_GetConnStatus()->ucPsSigConnStatusFlg)
        {
            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSigConFlg = VOS_FALSE;
    }

    if ((VOS_TRUE                   == pstResumeMsg->ucPsSigExistFlg)
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
    {
        /* HO����ʱ��PS�����Ѿ����ã��˴��������Ӵ��� */
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);

        NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
    }

    return;
}


VOS_VOID NAS_GMM_ProcResumeToGU(
    MMCGMM_RESUME_IND_ST               *pstResumeMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;
    RRMM_REL_IND_STRU                   stRrMmRelIndMsg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurrNetType = NAS_MML_GetCurrNetRatType();

    /* ��Ϊ�ڽ���TC���Է���ϵͳ���л�ʱ��ý���޷������������л���
       �ڷ���ϵͳ���л�ʱ�������л��ɹ�ʱ����Ҫ֪ͨTC�л��¼����Ա�TC����֪ͨý��.
       L to Gʱ ����Ҫ������Ϣ */
    if ( (GMM_TC_ACTIVE == gstGmmSuspendCtrl.ucPreState)
      && (gstGmmSuspendCtrl.ucPreRat != NAS_MML_NET_RAT_TYPE_LTE) )
    {
        NAS_GMM_SndTcHandoverInd();
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, gstGmmSuspendCtrl.ucSuspendCause);

    if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif

    /* ����W��G��ϵͳ�л� */
    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrNetType)
    {
        g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect = NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;
        if ((0x10 != (gstGmmSuspendCtrl.ucPreState & 0xF0))
         && (GMM_REGISTERED_INITIATED != gstGmmSuspendCtrl.ucPreState))
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

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);

    if ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrNetType)
     && (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
    {
        NAS_GMM_SuspendLlcForInterSys();

        if (MMC_SUSPEND_CAUSE_CELLCHANGE != gstGmmSuspendCtrl.ucSuspendCause)
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

            Gmm_TimerStop(GMM_TIMER_T3314);
        }

        if ((0x10 != (gstGmmSuspendCtrl.ucPreState & 0xF0))
         && (GMM_REGISTERED_INITIATED != gstGmmSuspendCtrl.ucPreState))
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

    /* ������ϵͳ�л���W��G��������ڽ������������ */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == gstGmmSuspendCtrl.ucPreRat)
     && ((GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
       || (GMM_SERVICE_REQUEST_INITIATED == gstGmmSuspendCtrl.ucPreState)))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

        Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
        stRrMmRelIndMsg.ulCnDomainId              = RRC_NAS_PS_DOMAIN;
        stRrMmRelIndMsg.ulRelCause                = RRC_REL_CAUSE_RR_NORM_EVENT;
        stRrMmRelIndMsg.ulRrcConnStatus           = RRC_RRC_CONN_STATUS_ABSENT;
        Gmm_RcvRrmmRelInd(&stRrMmRelIndMsg);

        gstGmmSuspendCtrl.ucPreState = g_GmmGlobalCtrl.ucState;
    }

    return;
}
VOS_VOID NAS_GMM_RcvMmcResumeInd_CcoFallbak(VOS_VOID)
{

    /* ����CCO�������̲��ڸú����д��� */
    if (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK != gstGmmSuspendCtrl.ucSuspendCause )
    {
        return;
    }

    NAS_GMM_ResumeCcoFallbackCtx();

    /* ��CCO������T3314���ܳ�ʱ,������Ҫ����T3314������״̬��������״̬ */
    if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3314))
     && (0xffffffff != gstGmmCasGlobalCtrl.ulReadyTimerValue)
     && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
    {
        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.stBackupShare.ucState)
    {
        gstGmmSuspendCtrl.ucPreState = GMM_REGISTERED_NORMAL_SERVICE;
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmcResumeInd_Handover(
    MMCGMM_RESUME_IND_ST               *pstResumeIndMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    enCurrNetType   = NAS_MML_GetCurrNetRatType();

    /* ����HO���̲��ڸú����д��� */
    if (MMC_SUSPEND_CAUSE_HANDOVER != gstGmmSuspendCtrl.ucSuspendCause )
    {
        return;
    }

    /* L��GU��HO��GU֮���HO���̣�����ʱ����ʱ����NV���� */
    /* GU��L��HO,�����ȷ�ϣ������ϵͳ��Ϣ������TAU�����û��ϵͳ��Ϣ�����·�ͷ�����פ������TAU��TAU֮���ϱ�TAU����ͷ���״̬ */
    if ( (enCurrNetType != gstGmmSuspendCtrl.ucPreRat)
#if (FEATURE_ON == FEATURE_LTE)
      && (enCurrNetType != NAS_MML_NET_RAT_TYPE_LTE)
#endif
      )
    {
        /* ��ͣ���� */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

        Gmm_TimerStart(GMM_TIMER_HO_WAIT_SYSINFO);
    }

    /* L->GU,CS handover���»�ȡ�ض���İ�ȫ������ */
    if ((VOS_FALSE                   == pstResumeIndMsg->ucPsSigExistFlg)
     && (NAS_MML_NET_RAT_TYPE_LTE    != enCurrNetType)
     && (NAS_MML_NET_RAT_TYPE_LTE    == gstGmmSuspendCtrl.ucPreRat))
    {
        gstGmmSuspendCtrl.ucGetLteSecContext = VOS_FALSE;
    }

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
