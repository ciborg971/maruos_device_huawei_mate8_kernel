/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmlMsgProc.c
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��6��29��
  ����޸�   : 2011��6��29��
  ��������   : MML_CTX������ڲ���Ϣ���д�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��6��29��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�

****************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "NasComm.h"
#include "MM_Ext.h"
#include "GmmExt.h"
#include "NasMmcMain.h"
#include "NasMmlMsgProc.h"
#include "NasMmcSndOm.h"
#include "NasUtranCtrlInterface.h"

#include "TafMmaMain.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

/*lint -e767 �޸���:zhoujun \40661;ԭ��:Log��ӡ*/
#define THIS_FILE_ID PS_FILE_ID_NASMML_MSGPROC_C
/*lint +e767 �޸���:zhoujun \40661;ԭ��:Log��ӡ*/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/
extern VOS_UINT32 WuepsMmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_UINT32 WuepsGmmPidInit ( enum VOS_INIT_PHASE_DEFINE ip );



/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

NAS_MML_INTERNAL_MSG_BUF_STRU *NAS_MML_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNasMmlMsg        = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);

    /* ���������л�ȡ��Ϣ������ָ�� */
    pstNasMmlMsg = ( NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if ( ulLen > NAS_MML_MAX_INTERNAL_MSG_LEN )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_GetIntMsgSendBuf: Buffer full" );
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return VOS_NULL_PTR;
    }

    /* ��������Ϣ���嵥Ԫ */
    PS_MEM_SET(pstNasMmlMsg, 0x00, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* ���ػ�����ָ�� */
    return pstNasMmlMsg;
}
VOS_VOID NAS_MML_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. �ж��ڲ���Ϣ�������Ƿ����� */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);

        return;
    }

    /* 2. ȡ��һ����Ϣ���嵥Ԫ */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[ucMsgPnt]);

    /* 3. �ж���Ϣ�����Ƿ�Ƿ� */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_SndInternalMsg: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. ���ڲ���Ϣ���͵��ڲ���Ϣ������ */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* �����ڲ���Ϣ������ */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= NAS_MML_MAX_MSG_QUEUE_SIZE;

    return;
}
NAS_MML_INTERNAL_MSG_BUF_STRU* NAS_MML_GetNextInternalMsg( VOS_VOID )
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;
    NAS_MML_CTX_STRU                   *pstMmlCtx  =  VOS_NULL_PTR;

    pstMmlCtx   = NAS_MML_GetMmlCtx();

    if ( pstMmlCtx->stInternalMsgQueue.ucHeader != pstMmlCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmlCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstMmlCtx->stInternalMsgQueue.astNasMmMsgQueue[ucNextIndex]);

        /* ȡ��һ����Ϣ,ͷָ�����ƫ�� */
        (pstMmlCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmlCtx->stInternalMsgQueue.ucHeader) %= NAS_MML_MAX_MSG_QUEUE_SIZE;
        return pstNextMsg;
    }

    NAS_INFO_LOG(WUEPS_PID_MM, "NAS_MML_GetNextInternalMsg:Empty Internal Msg");
    return VOS_NULL_PTR;

}
VOS_VOID NAS_MML_InsertInternalMsgHead(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstMmlMsg           = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(NAS_MML_GetMmlCtx()->stInternalMsgQueue);
    pstSndMsg                           = (NAS_MML_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. �ж��ڲ���Ϣ�������Ƿ����� */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % NAS_MML_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: The Queue is full.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        NAS_MMC_SndOmInternalMsgQueueDetailInfo(pstInternalMsgQueue);
        return;
    }
    /* 2. �ж���Ϣ�����Ƿ�Ƿ� */
    if ( pstSndMsg->ulLength > NAS_MML_MAX_INTERNAL_MSG_LEN)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead:Warning: ulBufLen is too long.");
        NAS_MMC_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_TRUE);
        return;
    }

    if ( (pstInternalMsgQueue->ucHeader % NAS_MML_MAX_MSG_QUEUE_SIZE) >= 1 )
    {
        pstInternalMsgQueue->ucHeader--;
        pstInternalMsgQueue->ucHeader         %= NAS_MML_MAX_MSG_QUEUE_SIZE;
    }
    else
    {
        pstInternalMsgQueue->ucHeader = NAS_MML_MAX_MSG_QUEUE_SIZE- 1;
    }

    /* 3. ȡ��һ����Ϣ���嵥Ԫ */
    pstMmlMsg = (NAS_MML_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astNasMmMsgQueue[pstInternalMsgQueue->ucHeader]);

    NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MML_InsertInternalMsgHead: usMsgID is ", pstMmlMsg->usMsgID);

    /* 4. ���ڲ���Ϣ���͵��ڲ���Ϣ���е���ǰ�� */
    PS_MEM_CPY(pstMmlMsg, pstSndMsg, sizeof(NAS_MML_INTERNAL_MSG_BUF_STRU));

    /* �����ڲ���Ϣ������ */

    return;
}




pNasMmPIdMsgProc NAS_MML_FindPidMsgProc(
    VOS_UINT32                          ulRcvPid
)
{
    pNasMmPIdMsgProc                    fReturnMsgProcHandle;

    fReturnMsgProcHandle =  VOS_NULL_PTR;
    switch ( ulRcvPid )
    {
        case WUEPS_PID_MM :
            fReturnMsgProcHandle    = MmMsgProc;
            break;
        case WUEPS_PID_GMM :
            fReturnMsgProcHandle    = GmmMsgProc;
            break;
        case WUEPS_PID_MMC :
            fReturnMsgProcHandle    = NAS_MMC_MsgProc;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            fReturnMsgProcHandle    = NAS_MM_PidMsgEntry;
            break;
#endif

        default:
            NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MML_FindPidMsgProc:invalide rcv pid", ulRcvPid);
            break;
    }

    return fReturnMsgProcHandle;
}



VOS_VOID NAS_MML_MsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    NAS_MML_INTERNAL_MSG_BUF_STRU      *pstNextMsg   = VOS_NULL_PTR;
    pNasMmPIdMsgProc                    pMsgProc     = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
#ifndef __PS_WIN32_RECUR__
    VOS_UINT32                          ulIsSndOmPcRecurMsgValid;
#endif
    VOS_UINT32                          ulRslt;
    struct MsgCB                       *pstNextDestMsg;

    /* ��ڲ������ */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Empty Msg");
        return;
    }

    if (VOS_TRUE == NAS_MML_GetSvlteSupportFlag())
    {
        NAS_MML_ConvertOamSendPid(&pRcvMsg->ulSenderPid);
    }

    pMsgProc = NAS_MML_FindPidMsgProc(pRcvMsg->ulReceiverPid);

    /* δ�ҵ�������ֱ�ӷ��� */
    if ( VOS_NULL_PTR == pMsgProc )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        return;
    }

    /* �ȴ����ⲿ��Ϣ */
    pMsgProc(pRcvMsg);

    /* �ⲿ��Ϣ������ɺ����ڲ���Ϣ */
    pstNextMsg = NAS_MML_GetNextInternalMsg();

    while (VOS_NULL_PTR != pstNextMsg)
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (PS_PID_MM == pstNextMsg->ulSenderPid)
        {
            pstMsgHeader = (MSG_HEADER_STRU *)pstNextMsg;

            NAS_MML_LogMsgInfo(pstMsgHeader);

        }
#endif

        pMsgProc = NAS_MML_FindPidMsgProc(pstNextMsg->ulReceiverPid);

        /* δ�ҵ�������ֱ�ӷ��� */
        if ( VOS_NULL_PTR == pMsgProc )
        {
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Invalid rcv pid");
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ((VOS_FALSE == NAS_MML_IsPlatformSupportLte())
              && (PS_PID_MM == pstNextMsg->ulReceiverPid))
        {
            NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MML_MsgProc:Platform not support Lte");
        }
#endif
        else
        {
            /* ������Ϣ������,�Ա�����PSTAS����ʾ */
            DIAG_TraceReport(pstNextMsg);

            /* Deleted by wx270776 for Omdiag_Bugfix, 2015-9-9, begin */
            /* Deleted by wx270776 for Omdiag_Bugfix, 2015-9-9, end */

            /* ����ǰ��Ϣ����UTRANCTRLģ����д��� */
            ulRslt = NAS_UTRANCTRL_MsgProc((struct MsgCB *)pstNextMsg, &pstNextDestMsg);

            /* ��Ϣ��UTRANCTRLģ�鴦����ɣ�ֱ�ӷ��أ�������������� */
            if ( VOS_FALSE == ulRslt )
            {
                pMsgProc((struct MsgCB *)pstNextDestMsg);
            }

        }

        /* Ѱ����һ���ڲ���Ϣ */
        pstNextMsg = NAS_MML_GetNextInternalMsg();
    }

#ifndef __PS_WIN32_RECUR__

    ulIsSndOmPcRecurMsgValid = NAS_MML_IsSndOmPcRecurMsgValid();

    if ( (VOS_TRUE == NAS_MML_GetUePcRecurFlg())
      && (VOS_TRUE == ulIsSndOmPcRecurMsgValid))
    {
        NAS_MML_SetUePcRecurFlg(VOS_FALSE);

        NAS_MMC_SndOutsideContextData();
        NAS_MM_SndOutsideContextData();
        NAS_GMM_SndOutsideContextData();
    }

#endif


    return;
}
VOS_UINT32  NAS_MML_FidMsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    struct MsgCB                       *pstDestMsg;
    VOS_UINT32                          ulRslt;


    pstDestMsg = VOS_NULL_PTR;

    /* ��ڲ������ */
    if ( VOS_NULL_PTR == pRcvMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MML_FidMsgProc:Empty Msg");
        return VOS_ERR;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    NAS_MML_LogMsgInfo(pstMsgHeader);


    /* ����ǰ��Ϣ����UTRANCTRLģ����д��� */
    ulRslt = NAS_UTRANCTRL_MsgProc(pRcvMsg, &pstDestMsg);

    /* ��Ϣ��UTRANCTRLģ�鴦����ɣ�ֱ�ӷ��أ�������������� */
    if ( VOS_TRUE == ulRslt )
    {
        return VOS_OK;
    }

    /* �����UTRANCTRLģ�鷵�ص���Ϣ */
    NAS_MML_MsgProc(pstDestMsg);

    /* ����UTRANCTRLģ�黺�����Ϣ */
    NAS_UTRANCTRL_ProcBufferMsg();

    NAS_MML_UpdateExitTime();

    return VOS_OK;
}
VOS_UINT32 NAS_MML_FidInit (
    enum VOS_INIT_PHASE_DEFINE          enInitPhase
)
{
    VOS_UINT32 ulReturnCode;

    switch( enInitPhase )
    {
        case   VOS_IP_LOAD_CONFIG:
#if defined(INSTANCE_1)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_1);
#elif defined(INSTANCE_2)
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS_2);
#else
            (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_NAS);
#endif

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MM,
                                  (Init_Fun_Type) WuepsMmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMC,
                                      (Init_Fun_Type) NAS_MMC_InitPid,
                                      (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_GMM,
                                  (Init_Fun_Type) WuepsGmmPidInit,
                                  (Msg_Fun_Type) NAS_MML_FidMsgProc);
            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(WUEPS_PID_MMA,
                                    (Init_Fun_Type) TAF_MMA_InitPid,
                                    (Msg_Fun_Type)TAF_MMA_MsgProcEntry);

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

#ifndef DMT
#if (FEATURE_ON == FEATURE_LTE)
    #if defined(INSTANCE_1) || defined(INSTANCE_2)
            /* ˫��˫ͨmodem1������Lģ */
    #else
            ulReturnCode = VOS_RegisterPIDInfo(PS_PID_MM,
                          (Init_Fun_Type) NAS_MM_PidInit,
                          (Msg_Fun_Type) NAS_MML_FidMsgProc  );
    #endif
#endif
#endif

            ulReturnCode = VOS_RegisterTaskPrio(WUEPS_FID_MM,
                                                NAS_MM_TASK_PRIO);

            if( VOS_OK != ulReturnCode )
            {
                return VOS_ERR;
            }

            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;

    }

    return VOS_OK;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

