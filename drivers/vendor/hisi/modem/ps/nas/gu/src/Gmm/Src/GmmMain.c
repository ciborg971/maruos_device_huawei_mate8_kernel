
#include "GmmInc.h"
#include "psprimitive.h"
#include "GmmCasGlobal.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasCommDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "GmmLmmInterface.h"
#include "NasGmmProcLResult.h"
#endif
#include "GmmMmInterface.h"
#include "NasMmcSndOm.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUsimmApi.h"

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_MAIN_C

NAS_GMM_CTRL_STATUS_ENUM_UINT8  gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

/*lint -save -e958 */

/*******************************************************************************
  Module:      GMM_ReportN2MOtaMsg
  Function:    ��trace�й�ȡGMM�Ŀտ���Ϣ
  Input:       NAS_MSG_STRU*   pNasMsg     SM�տ���Ϣ
  NOTE:
  Return:      VOS_VOID
  History:
      1. ³��    2009.07.11   �¹�����
*******************************************************************************/
VOS_VOID GMM_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportN2MOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_ACCEPT;
            break;

        case GMM_MSG_ATTACH_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REJECT;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ_BY_NET;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT;
            break;

        case GMM_MSG_RAU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_ACCEPT;
            break;

        case GMM_MSG_RAU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REJECT;
            break;

        case GMM_MSG_SERVICE_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_ACC;
            break;

        case GMM_MSG_SERVICE_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REJ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REQ;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REJ;
            break;

        case GMM_MSG_IDENTITY_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_REQUEST;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS;
            break;

        case GMM_MSG_GMM_INFORMATION:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_INFORMATION;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*������GMMģ��Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8 *)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__
VOS_VOID  NAS_GMM_SetGmmSigFunc(VOS_VOID)
{
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;
}



VOS_UINT32 NAS_GMM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;
    VOS_UINT32                                               ulMsgAddrForSm;

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                  + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                  + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                  + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                  + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                  + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                  + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                  + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                  + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                  + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                  + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                  + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                  + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pMsg;
    pucSrc   = pstRcMsg->aucData;

    /* �����ܳ��� */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* gucGmmInitStateĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gucGmmInitState;
    ulDestLen   = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmInterRatCellReselectĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulDestLen   = sizeof(g_GmmInterRatCellReselect);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmCasGlobalCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulDestLen   = sizeof(GMM_CAS_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmSuspendCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulDestLen   = sizeof(GMM_SUSPEND_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmGlobalCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulDestLen   = sizeof(GMM_GLOBAL_CTRL_STRU);

    /*GTR����ʱGMM�����SM�������ݰ�Ϊ��ַ������ʵ�ʻط�ʱSM���������ַ��ͬ�����Բ���Ҫ�ָ��õ�ַ��*/
    ulMsgAddrForSm = g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = ulMsgAddrForSm;
    pucSrc += (ulItemCount);

    /* g_GmmTimerMngĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmTimerMng;
    ulDestLen   = sizeof(GMM_TIMER_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAttachCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulDestLen   = sizeof(GMM_ATTACH_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmRauCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulDestLen   = sizeof(GMM_RAU_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDownLinkNpduBakeĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulDestLen   = sizeof(GMM_DOWNLINK_NPDU_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDetachCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulDestLen   = sizeof(GMM_DETACH_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAuthenCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulDestLen   = sizeof(GMM_AUTHEN_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmReqCnfMngĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulDestLen   = sizeof(GMM_REQ_CNF_MNG_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmServiceCtrlĿ���ַ */
    pucDest     = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulDestLen   = sizeof(GMM_SR_CTRL_STRU);

    /* ��ѹ�� */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RestoreContextData - data is restored.");

    NAS_GMM_SetGmmSigFunc();

    return VOS_TRUE;
}
#endif
VOS_VOID NAS_GMM_SndOutsideContextData()
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_GMM, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM,"NAS_GMM_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* ��ȡbuf��β��ַ�����ڼ���ʣ��ռ�*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;
    pucDest   = pstPcreplayCompressCtx->aucData;

    /* ԭʼ���ݴ�С */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* ѹ��gucGmmInitState*/
    pucSrc      = (VOS_UINT8 *)&gucGmmInitState;
    ulItemCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmInterRatCellReselect */
    pucSrc      = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulItemCount = sizeof(g_GmmInterRatCellReselect);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��gstGmmCasGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulItemCount = sizeof(GMM_CAS_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��gstGmmSuspendCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulItemCount = sizeof(GMM_SUSPEND_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulItemCount = sizeof(GMM_GLOBAL_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmTimerMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmTimerMng;
    ulItemCount = sizeof(GMM_TIMER_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmAttachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulItemCount = sizeof(GMM_ATTACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmRauCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulItemCount = sizeof(GMM_RAU_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmDownLinkNpduBake */
    pucSrc      = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulItemCount = sizeof(GMM_DOWNLINK_NPDU_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmDetachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulItemCount = sizeof(GMM_DETACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);


    /* ѹ��g_GmmAuthenCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulItemCount = sizeof(GMM_AUTHEN_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmReqCnfMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulItemCount = sizeof(GMM_REQ_CNF_MNG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_GmmServiceCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulItemCount = sizeof(GMM_SR_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);

    return;
}


VOS_VOID NAS_GMM_MsgProcAtStatusNull(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_ADMIN == pMsgHeader->ulSenderPid)
     && (WUEPS_START_REQ == pMsgHeader->ulMsgName))
    {
        #ifdef __PS_WIN32_RECUR__
        Gmm_TaskInit();
        #endif

        gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;
    }

    return;
}


VOS_VOID NAS_GMM_MsgProcAtStatusStartup(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsgHeader->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_TaskInit();
        Gmm_RcvMmcStartReq();
        gucGmmInitState = NAS_GMM_CTRL_STATUS_INSERVICE;

        #ifndef __PS_WIN32_RECUR__


        if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
        {
            NAS_GMM_SndOutsideContextData();
        }

        #endif
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusStartup:Receive message at state NAS_GMM_CTRL_STATUS_STARTUP.");

        if ((WUEPS_PID_SM == pMsgHeader->ulSenderPid)
            && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_STARTUP);
        }
        else if ((WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
            && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {

        }
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_PreProc(
    VOS_VOID                           *pstRcvMsg                               /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* ����ԭ������ָ��                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* ǿ������ת��                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;                         /* ��CSͨ����Ϊ��                           */
    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;
    }
    else
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                        /* ��CSͨ����Ϊ��                           */
    }

    return;                                                                     /* ����                                     */
}


VOS_UINT8 NAS_GMM_MsgProcAtStatusInService(
    struct MsgCB                        *pMsg
)
{
    VOS_UINT8                           ucFollowOn;
    REL_TIMER_MSG                       *pTimerMsg;
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_RcvMmcStartReq();
        return VOS_TRUE;
    }

    if ((WUEPS_PID_MM         == pMsg->ulSenderPid)
     && (MMGMM_CS_CONNECT_IND == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvMmCsConnectInd_PreProc(pMsg);
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
    && (MMCGMM_DETACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcDetachReq_PreProc((MMCGMM_DETACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SMS == pMsg->ulSenderPid)
    {
        if (GMMSMS_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsBeginSessionNotify_PreProc((GMMSMS_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSMS_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsEndSessionNotify_PreProc((GMMSMS_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SM == pMsg->ulSenderPid)
    {
        if (GMMSM_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmBeginSessionNotify_PreProc((GMMSM_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSM_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmEndSessionNotify_PreProc((GMMSM_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;

        }
    }

    if ((WUEPS_PID_RABM == pMsg->ulSenderPid)
    && (ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvRabmMmlProcStatusQryReq((struct MsgCB *)pMsg);
        return VOS_TRUE;
    }

    if (RRMM_GMM_PROC_ENQ == pMsgHeader->ulMsgName)
    {
        if ( (WUEPS_PID_WRR == pMsgHeader->ulSenderPid)
          || (UEPS_PID_GAS == pMsgHeader->ulSenderPid) )
        {
            NAS_GMM_SndRrmmGmmProcAns();
        }

        return VOS_TRUE;
    }

    GMM_CasMsgProc(pMsg, &ucFollowOn);

    if (VOS_FALSE == ucFollowOn)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;

        Gmm_RcvTimerExpired((VOS_UINT8)pTimerMsg->ulName);
    }
    else if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    {
        if (WUEPS_RESET_REQ == pMsgHeader->ulMsgName)
        {
            gucGmmInitState = NAS_GMM_CTRL_STATUS_NULL;
        }
    }
    else
    {
        if (WUEPS_PID_GMM == pMsgHeader->ulReceiverPid)
        {
            Gmm_MsgDistribute((VOS_VOID*)pMsg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusInService: The message is not GMM message.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}

VOS_VOID GmmMsgProc(
    struct MsgCB*                       pMsg
)
{
    VOS_UINT8                ucResult;

#ifdef __PS_WIN32_RECUR__
    if ((WUEPS_PID_GMM == pMsg->ulSenderPid)
     && (WUEPS_PID_GMM == pMsg->ulReceiverPid))
    {
        NAS_GMM_RestoreContextData(pMsg);
    }
#endif


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    switch (gucGmmInitState)
    {
        case NAS_GMM_CTRL_STATUS_NULL:
            NAS_GMM_MsgProcAtStatusNull(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_STARTUP:
            NAS_GMM_MsgProcAtStatusStartup(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_INSERVICE:
            ucResult = NAS_GMM_MsgProcAtStatusInService(pMsg);
            if (VOS_FALSE == ucResult)
            {
                return;
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GmmMsgProc:WARNING: gucGmmInitState is Abnormal!");
            break;
    }
/*
#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
*/
    return;
}


VOS_UINT8 Gmm_MsgDistribute_GMM_TC_ACTIVE(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    MMCGMM_DETACH_REQ_STRU             *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq  = (MMCGMM_DETACH_REQ_STRU *)pRcvMsg;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if ((WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT,RABM,SM or SMS is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_DATA_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_PAGING_IND != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg except RRMM_REL_IND,RRMM_DATA_IND is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
           &&(MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    else if ( (WUEPS_PID_MMC     == pNasMsgHeader->ulSenderPid)
           && (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName) )
    {
        /* �жϵȴ�Detach��־�Ƿ���ڣ������������detach */
        if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
        {
            Gmm_MsInitNormalDetach(pstDetachReq->enDetachType);
        }

        /* ��ǰDETACH��Ϣ����Ҫ�ٽ��д��� */
        ucRst = GMM_FALSE;
    }
    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = NAS_Gmm_IsValidMmcMsg_GmmTcActive(pRcvMsg);
    }
    else
    {
    }
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: GMM is in GMM_TC_ACTIVE");


    /* �յ������PS�������ͷ���Ϣʱ��֪ͨTC�����ͷ� */
    if ( (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
      && (RRMM_REL_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }

    /* ��MMC�յ�COVERAGE LOST��Ϣʱ��֪ͨTC�����ͷ� */
    if ( (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
      && (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }


    return ucRst;
}


VOS_UINT8 Gmm_MsgDistribute_GMM_NULL(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
    {
        if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
    {
        if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_NULL);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
    {
        if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {
        }
        ucRst = GMM_FALSE;
    }

    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = Gmm_MsgDistribute_ProcMmcMsg_GmmNull(pRcvMsg);
    }
    else if(WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT or RRC is Abnormal when GMM is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_TC == pNasMsgHeader->ulSenderPid)
        && (TCGMM_TEST_REQ != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive TCGMM_TEST_REQ Msg is Abnormal when  is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else
    {
    }

    return ucRst;
}
VOS_UINT8 Gmm_MsgDistribute_SpecProc_Handling(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc)
    {
        if (WUEPS_PID_MMC != pNasMsgHeader->ulSenderPid)
        {
            if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
                && (RRMM_REL_IND == pNasMsgHeader->ulMsgName))
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
            }
            else
            {
                ucRst = GMM_FALSE;
            }
        }
    }

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {
        if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        {
            if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        {
            if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else
            {
            }
            ucRst = GMM_FALSE;
        }
        else if((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
            || (WUEPS_PID_TC == pNasMsgHeader->ulSenderPid))
        {
            if (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName)
            {

                /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
                if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                         & GMM_WAIT_PS_ATTACH))
                {
                    NAS_GMM_SndMmcAttachCnf();
                }
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
            }

            ucRst = GMM_FALSE;
        }
        else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
            && (RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
            && (RRMM_REL_IND != pNasMsgHeader->ulMsgName))
        {
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_Rat_Handling
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: ��ͬ���뼼������Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_Rat_Handling(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G����ģʽ */
        /* ������WRRC��Ϣ��SMS��Ϣ */
        if (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
        else if (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        {
            if ((RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
                && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
                && (RRMM_INTER_RAT_HANDOVER_INFO_CNF != pNasMsgHeader->ulMsgName))
            {
                ucRst = GMM_FALSE;
            }
        }
        else
        {
        }
    }
    else
    {/* 3G����ģʽ */
        /* ������GAS��Ϣ��LLC��Ϣ */
        if (UEPS_PID_LL == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_USIM
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: USIM��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_USIM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case USIMM_AUTHENTICATION_CNF:
        Gmm_RcvAgentUsimAuthenticationCnf(pRcvMsg);                         /* AGENT_USIM_AUTHENTICATION_CNF���մ���    */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from USIM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RRCF
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: RRCF��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RRCF(
    VOS_VOID                            *pRcvMsg
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
    case RRMM_PAGING_IND:
        Gmm_RcvRrmmPagingInd(pRcvMsg);
        break;
    case RRMM_EST_CNF:
        Gmm_RcvRrmmEstCnf(pRcvMsg);
        break;
    case RRMM_DATA_IND:
        Gmm_RcvRrmmDataInd(pRcvMsg);
        break;
    case RRMM_REL_IND:
        Gmm_RcvRrmmRelInd(pRcvMsg);
        break;
    case RRMM_SECURITY_IND:
        Gmm_RcvRrmmSecurityInd(pRcvMsg);
        break;
    case RRMM_INTER_RAT_HANDOVER_INFO_CNF:
        NAS_GMM_RcvInterRatHandoverInfoCnf(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RRC is ignored");
        break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute_From_RABM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_RABM_GMM_REESTABLISH_REQ:
        Gmm_RcvRabmReestablishReq(pRcvMsg);                                 /* GMMRABM_REESTABLISH_REQ���մ���          */
        break;
    case ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP:
        NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(pRcvMsg);
        break;
    case ID_RABM_GMM_RAB_REL_IND:
        Gmm_RcvRabRelInd();                                                 /* RAB�ͷ�ָʾ���մ���                      */
        break;

    case ID_RABM_GMM_RAB_SETUP_IND:
        NAS_GMM_RcvRabmRabSetupInd((GMMRABM_RAB_SETUP_IND_STRU *)pRcvMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RABM is ignored");
        break;
    }

    return;
}
VOS_VOID Gmm_MsgDistribute_From_MMC(
    VOS_VOID                            *pRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case MMCGMM_SYS_INFO_IND:
        Gmm_RcvMmcSysInfoInd(pRcvMsg);                                      /* MMCGMM_SYS_INFO_IND���մ���              */

        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_WRR);


        /* �����ʱGMM��Ҫ��ȡLMM�İ�ȫ������,���ܻ�������ʱ��,��ʱ������Ӧ����ʱ�����
           ���յ�LMM�İ�ȫ�����ĵĻظ����߶�ʱ����ʱ������� */
        if ( VOS_FALSE == NAS_GMM_GetLmmSecInfoFlg())
        {
            /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
            gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_WCDMA;

            g_GmmInterRatCellReselect = 0;
        }


        break;
    case MMCGMM_COVERAGE_LOST_IND:
        Gmm_RcvMmcCoverageLostInd();                                        /* MMCGMM_COVERAGE_LOST_IND���մ���         */
        break;
    case MMCGMM_POWER_OFF_REQ:
        Gmm_RcvMmcPowerOffReq(pRcvMsg);                                     /* MMCGMM_POWER_OFF_REQ���մ���             */
        break;

    case MMCGMM_PLMN_SEARCH_INITIATED:
        Gmm_RcvMmcPlmnSearchInitiated();                                    /* MMCGMM_PLMN_SEARCH_INITIATED���մ���     */
        break;
    case MMCGMM_START_REQ:
        Gmm_RcvMmcStartReq();                                               /* MMCGMM_START_REQ���մ���                 */
        break;
    case MMCGMM_PLMN_USER_SEL_REQ:
        Gmm_RcvMmcPlmnUserSelReq();                                         /* MMCGMM_PLMN_USER_SEL_REQ���մ���         */
        break;
    case MMCGMM_DETACH_REQ:
        Gmm_RcvMmcDetachReq(pRcvMsg);                                       /* MMCGMM_DETACH_REQ���մ���                */
        break;
    case MMCGMM_MODE_CHANGE_REQ:
        Gmm_RcvMmcGmmModeChangeReq(pRcvMsg);                                /* MMCGMM_MODE_CHANGE_REQ���մ���           */
        break;
    case MMCGMM_ATTACH_REQ:
        Gmm_RcvMmcGmmAttachReq(pRcvMsg);                                    /* MMCGMM_ATTACH_REQ���մ���                */
        break;
    case MMCGMM_GSM_SYS_INFO_IND:
        GMM_RcvGasSysInfoInd(pRcvMsg);



        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_GAS);


        break;
    case MMCGMM_SUSPEND_IND:
        GMM_RcvMmcSuspendInd(pRcvMsg);
        break;
    case MMCGMM_RESUME_IND:
        GMM_RcvMmcResumeInd(pRcvMsg);
        break;
    case MMCGMM_REL_REQ:
        GMM_RcvMmcRelReq(pRcvMsg);
        break;
    case MMCGMM_W_AC_INFO_CHANGE_IND:
        NAS_GMM_RcvMmcWasAcInfoChgInd((NAS_MSG_STRU *)pRcvMsg);
        break;
#if (FEATURE_ON == FEATURE_LTE)
    case MMCGMM_LTE_SYS_INFO_IND:
        NAS_GMM_RcvMmcLteSysInfoInd((MMC_GMM_LTE_SYS_INFO_IND_STRU*)pRcvMsg);
        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_LTE;
        break;

    case MMCGMM_LMM_ATTACH_IND:
        NAS_GMM_RcvLmmAttachResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_TAU_RESULT_IND:
        NAS_GMM_RcvLmmTauResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MT_DETACH_IND:
        NAS_GMM_RcvLmmMtDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_SERVICE_RESULT_IND:
        NAS_GMM_RcvLmmServiceResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MO_DETACH_IND:
        NAS_GMM_RcvLmmMoDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_LOCAL_DETACH_IND:
        NAS_GMM_RcvLmmLocalDetachInd((struct MsgCB*)pRcvMsg);
        break;


    case MMCGMM_LMM_STATUS_IND:
        NAS_GMM_RcvMmcLmmStatusInd((MMCGMM_LMM_STATUS_IND_STRU*)pRcvMsg);
        break;

    case MMCGMM_LMM_TIMER_STATE_NOTIFY:
        NAS_GMM_RcvLmmTimerStateNotify((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_EMERGENCY_NUM_LIST_IND:
        NAS_GMM_RcvMmcEmergencyNumList((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY:
        NAS_GMM_RcvMmcVoiceDomainChangeNotify((struct MsgCB*)pRcvMsg);
        break;
#endif

    default :
        NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pNasMsgHeader->ulMsgName);
        break;
    }

    return;
}
VOS_VOID NAS_GMM_RcvSmAbortReq(
    VOS_VOID                            *pRcvMsg)
{
    NAS_GMM_ClearBufferedSmDataReq();
}


VOS_VOID Gmm_MsgDistribute_From_SM(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case GMMSM_ESTABLISH_REQ:
        Gmm_RcvSmEstablishReq(pRcvMsg);                                     /* GMMSM_ESTABLISH_REQ���մ���              */
        break;
    case GMMSM_DATA_REQ:
        Gmm_RcvSmDataReq(pRcvMsg);                                          /* GMMSM_DATA_REQ���մ���                   */
        break;
    case GMMSM_PDP_STATUS_IND:
        Gmm_RcvSmPdpStatusInd(pRcvMsg);                                     /* GMMSM_PDP_STATUS_IND���մ���             */
        break;
    case GMMSM_PDP_DEACTIVATED_IND:
        NAS_GMM_RcvSmPdpDeactivatedInd(pRcvMsg);
        break;

    case GMMSM_ABORT_REQ:
        NAS_GMM_RcvSmAbortReq(pRcvMsg);
        break;

    case GMMSM_PDP_MODIFY_IND:
        NAS_GMM_RcvSmPdpModifyInd(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SMS
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: SMS��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SMS(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case PMMSMS_EST_REQ:
        Gmm_RcvSmsEstReq(pRcvMsg);                                          /* PMMSMS_EST_REQ���մ���                   */
        break;
    case PMMSMS_UNITDATA_REQ:
        Gmm_RcvSmsUnitdataReq(pRcvMsg);                                     /* GMMSM_DATA_REQ���մ���                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SMS is ignored");
        break;
    }

    return;
}
VOS_VOID Gmm_MsgDistribute_From_LL(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_LL_GMM_STATUS_IND:                                                  /* �ϱ�LLC״̬��Ϣ */
        GMM_CasCellS0E45(pRcvMsg);
        break;
    case ID_LL_UNITDATA_IND:                                                    /* ֱ���������� */
        GMM_RcvLlcDataInd(pRcvMsg);
        break;

    case ID_LL_UNITDATA_CNF:                                                    /* ֱ���������� */
        NAS_GMM_RcvLlcDataCnf(pRcvMsg);
        break;

    case ID_LL_DATA_INFORM :
        Gmm_RcvLLCInform(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from LLC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_TC
 *  FUNCTION : Gmm_MsgDistribute���������Ӷ�: TC��Ϣ�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_TC(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case TCGMM_DATA_REQ:
        Gmm_RcvTcDataReq(pRcvMsg);                                          /* TCGMM_DATA_REQ���մ���                   */
        break;
    case TCGMM_TEST_REQ:
        Gmm_RcvTcTestReq(pRcvMsg);                                          /* TCGMM_TEST_REQ���մ���                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from TC is ignored");
        break;
    }

    return;
}
VOS_VOID Gmm_MsgDistribute_From_GAS(
                       VOS_VOID *pRcvMsg                                        /* ������Ϣʹ�õ�ͷ��ַ����                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pNasMsgHeader->ulMsgName)
    {
        case GRRMM_PAGING_IND:                                                  /* GASѰ������ */
            GMM_RcvGasPagingInd(pRcvMsg);
            break;
        case RRMM_GPRS_SUSPENSION_IND:                                          /* GAS GPRS����ָʾ */
            GMM_RcvGasSuspensionInd(pRcvMsg);
            break;
        case RRMM_GPRS_RESUME_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasGprsResumeInd(pRcvMsg);
            break;
        case RRMM_CELL_RESELECT_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvCellReselectInd(pRcvMsg);
            break;
        case GRRGMM_TBF_REL_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasTbfRleInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasRadioAccessCapa(pRcvMsg);
            break;

        case RRMM_CLASSMARK_CHANGE_IND:
            GMM_RcvGasClassMarkChangeInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND:                                              /* GAS GPRS�ָ�ָʾ */
            GMM_RcvGasTdsRadioAccessCapa(pRcvMsg);
            break;

        case GRRGMM_GPRS_ACCESS_RESULT_IND:
            NAS_GMM_RcvGprsAccessResultInd(pRcvMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from GAS is ignored");
            break;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)


VOS_VOID NAS_GMM_RcvLmmReselSecInfoCnf(
    VOS_VOID                             *pRcvMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU     *pstMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8       enCurrRat;

    pstMsg = (LMM_GMM_RESEL_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInReselect((struct MsgCB *)pstMsg);

    enCurrRat   = NAS_MML_GetCurrNetRatType();

    /* ��Lģ��ȡӳ��İ�ȫ������֮��֪ͨGUģ */
    if (NAS_MML_NET_RAT_TYPE_WCDMA  == enCurrRat)
    {
        NAS_GMM_SndWasInfoChangeReq(RRC_NAS_MASK_MAPPED_SECURITY_KEY);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM  == enCurrRat)
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_MAPPED_SECURITY_KEY);
    }
    else
    {
    }

    /* ��Lģ��ȡ��ȫ�����ĺ������ǰ״̬����ATTACH_INIT��RAU_INIT������attach/rau req
       ��Ӧ����Ϊ:LTE���Ʒ�����available timer,��ѡ��GU������available timer��ʱ����������
       GMM״̬����ΪPLMN_SRCH,������RAU���̳�ͻ */
    if ( (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
        {
            Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        }
        else
        {
            Gmm_SndAttachReq();
        }

        /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
        gstGmmSuspendCtrl.ucPreRat = enCurrRat;
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;


    gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);

}
VOS_VOID NAS_GMM_RcvLmmHoSecInfoCnf(
    VOS_VOID                            *pRcvMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU       *pstMsg;

    pstMsg = (LMM_GMM_HO_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver((struct MsgCB *)pstMsg);

    /* �����ʱ��GMM�Ĺ���״̬�����ҹ�����ΪLTE������MMC�ظ�����ظ� */
    if ( (NAS_MML_NET_RAT_TYPE_LTE      == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE  == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }
}
VOS_VOID Gmm_MsgDistribute_From_Lmm(
    VOS_VOID *pRcvMsg
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
        case ID_LMM_GMM_RESEL_SECU_INFO_CNF:
            NAS_GMM_RcvLmmReselSecInfoCnf(pRcvMsg);
            break;

        case ID_LMM_GMM_HO_SECU_INFO_CNF:
            NAS_GMM_RcvLmmHoSecInfoCnf(pRcvMsg);
            break;

        default :
            break;
    }

    return;
}

#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
VOS_VOID NAS_GMM_ProcMtcRrcAreaLostInd(VOS_VOID  *pstRcvMsg)
{

    /* svlte���Կ���ʱps��modem0Ǩ�Ƶ�modem1������ȫ�ֱ���������gmm�յ�
       detach ps����ֱ�ӽ��б���detach�Լ���ʱ�� */
    NAS_MML_SetPsLocalDetachFlag(VOS_TRUE);

    return;
}



VOS_VOID NAS_GMM_ProcMtcMsg(VOS_VOID  *pstRcvMsg)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;

    switch (pstNasMsgHeader->ulMsgName)
    {
        case ID_MTC_GMM_RRC_AREA_LOST_IND:
            NAS_GMM_ProcMtcRrcAreaLostInd(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_ProcMtcMsg: The Msg from MTC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

#endif




VOS_VOID Gmm_MsgDistribute_From_MM(
    VOS_VOID                           *pstRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;                                 /* �õ���Ϣͷ                               */

    switch (pstNasMsgHeader->ulMsgName)
    {
        case MMGMM_LU_RESULT_IND:
            NAS_GMM_ProcMmLuResult(pstRcvMsg);
            break;

        case MMGMM_CS_CONNECT_IND:
            NAS_GMM_RcvMmCsConnectInd(pstRcvMsg);                               /* MMGMM_CS_CONNECT_IND���մ���            */
            break;
        case MMGMM_CM_SERVICE_REJECT_IND:
            NAS_GMM_RcvMmCmServiceRejectInd(pstRcvMsg);                         /* MMGMM_CM_SERVICE_REJECT_IND���մ���     */
            break;

        case MMGMM_AUTHENTICATON_FAILURE_IND:
            NAS_GMM_RcvMmAuthenticationFailureInd();                            /* MMCGMM_AUTHENTICATON_FAILURE_IND���մ��� */
            break;

        case MMGMM_REGISTER_INITIATION:
            Gmm_RcvMmRegisterInitiation(pstRcvMsg);                              /* MMCGMM_REGISTER_INITIATION���մ���       */
            break;

        case MMGMM_CS_LOCAL_DETACH_IND:
            NAS_Gmm_RcvMmCsLocalDetachInd(pstRcvMsg);                           /* MMGMM_CS_LOCAL_DETACH_IND���մ��� */
            break;


        case MMGMM_T3211_TIMER_EXPIRED_NOTIFY:
            NAS_Gmm_RcvMmT3211ExpiredNotify(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}


VOS_VOID Gmm_MsgDistribute(
    VOS_VOID                            *pRcvMsg                                /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* �õ���Ϣͷ                               */
    if (WUEPS_PID_GMM != pNasMsgHeader->ulReceiverPid)
    {                                                                           /* ulDestTskId����GMM                       */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive PID is not GMM.");
        return;
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_TC_ACTIVE(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_NULL(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    ucRst = Gmm_MsgDistribute_SpecProc_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    ucRst = Gmm_MsgDistribute_Rat_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    switch (pNasMsgHeader->ulSenderPid)
    {                                                                           /* ����message class�ַ���Ϣ                */
    case WUEPS_PID_USIM:                                                        /* AGENT���͸�GMM                           */
        Gmm_MsgDistribute_From_USIM(pRcvMsg);
        break;

    case WUEPS_PID_WRR:                                                        /* RRC���͸�GMM                             */
        Gmm_MsgDistribute_From_RRCF(pRcvMsg);
        break;

    case WUEPS_PID_RABM:                                                        /* RABM���͸�GMM                            */
        Gmm_MsgDistribute_From_RABM(pRcvMsg);
        break;

    case WUEPS_PID_MMC:                                                         /* MMC���͸�GMM                             */
        Gmm_MsgDistribute_From_MMC(pRcvMsg);
        break;

    case WUEPS_PID_MM:                                                         /* SMS���͸�GMM                             */
        Gmm_MsgDistribute_From_MM(pRcvMsg);
        break;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    case UEPS_PID_MTC:
        NAS_GMM_ProcMtcMsg(pRcvMsg);
        break;
#endif

    case WUEPS_PID_SM:                                                          /* SM���͸�GMM                              */
        Gmm_MsgDistribute_From_SM(pRcvMsg);
        break;

    case WUEPS_PID_SMS:                                                         /* SMS���͸�GMM                             */
        Gmm_MsgDistribute_From_SMS(pRcvMsg);
        break;

    case WUEPS_PID_TC:                                                        /* TC���͸�GMM                              */
        Gmm_MsgDistribute_From_TC(pRcvMsg);
        break;

    case UEPS_PID_LL:                                                           /* LLC���͸�GMM */
        Gmm_MsgDistribute_From_LL(pRcvMsg);
        break;

    case UEPS_PID_GAS:                                                          /* GRR���͸�GMM */
        Gmm_MsgDistribute_From_GAS(pRcvMsg);
        break;

#if   (FEATURE_ON == FEATURE_LTE)
    case PS_PID_MM:                                                          /* GRR���͸�GMM */
        Gmm_MsgDistribute_From_Lmm(pRcvMsg);
        break;
#endif

    default :
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive Message from unexpected PID, PID : ", pNasMsgHeader->ulSenderPid);
        break;
    }

    return;
}


VOS_VOID Gmm_ComVariantInit(VOS_VOID)
{
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usNonDrxTimerLen;
    VOS_UINT8                           aucDefaultRac[] = {0x15, 0x17, 0x73, 0x43, 0x2b, 0x25, 0x96, 0x62, 0x00,
                                                           0x42, 0x68, 0x8b, 0x19, 0x88, 0x01, 0x0b, 0xa2,
                                                           0x8c, 0x66, 0x20, 0x04, 0x00};
    NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU    stRelConnAfterPdpDeact;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulLength;

    NAS_MML_PLMN_WITH_RAT_STRU                  stPlmnWithRat;

    stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;


    usNonDrxTimerLen = 0;

    /* ��GMM��ȫ�ֱ������ڻ�Ϊ0 */
    Gmm_MemSet(&g_GmmGlobalCtrl, 0, sizeof(GMM_GLOBAL_CTRL_STRU));
    Gmm_MemSet(&g_GmmReqCnfMng,  0, sizeof(GMM_REQ_CNF_MNG_STRU));
    Gmm_MemSet(&g_GmmAttachCtrl, 0, sizeof(GMM_ATTACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmRauCtrl,    0, sizeof(GMM_RAU_CTRL_STRU));
    Gmm_MemSet(&g_GmmDetachCtrl, 0, sizeof(GMM_DETACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmAuthenCtrl, 0, sizeof(GMM_AUTHEN_CTRL_STRU));
    Gmm_MemSet(&g_GmmServiceCtrl,0, sizeof(GMM_SR_CTRL_STRU));
    Gmm_MemSet(&g_MmSubLyrShare.GmmShare, 0, sizeof(GMM_SHARE_STRU));
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    g_GmmTimerMng.ulTimerRunMask             = 0;
    g_GmmTimerMng.ulTimerSusMask             = 0;
    g_GmmTimerMng.ulTimerValMask             = 0;
    g_GmmTimerMng.ulTimerRunMaskEx           = 0;
    g_GmmTimerMng.ulTimerSusMaskEx           = 0;
    g_GmmTimerMng.ulTimerValMaskEx           = 0;    
    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    GMM_InitCasGlobalVariable();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);

    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg  = GMM_SUPPORT_INFORMATION_MSG;


    /* ��GASά����NV���ж�ȡnonDRXTimerֵ */
    if(NV_OK != NV_Read (en_NV_Item_GPRS_Non_Drx_Timer_Length, &usNonDrxTimerLen, sizeof(VOS_UINT16)))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_ComVariantInit():en_NV_Item_GPRS_Non_Drx_Timer_Length Error");
        usNonDrxTimerLen = 0;
    }

    NAS_MML_SetNonDrxTimer((VOS_UINT8)usNonDrxTimerLen);



    g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = VOS_FALSE;
    PS_MEM_SET(&stRelConnAfterPdpDeact, 0x00, sizeof(NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU));

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT, &ulLength);
    if (ulLength > sizeof(stRelConnAfterPdpDeact))
    {
        return;
    }
    ulResult = NV_Read(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT,
                       &stRelConnAfterPdpDeact,
                       ulLength);

    if (NV_OK == ulResult)
    {
        g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = stRelConnAfterPdpDeact.ucRelFlg;
    }

    /*���ｫ��¼�ϴ�attach��RAU�Ƿ�Я��Drx�����ı���enLatestAttachOrRauContainDrx ��ʼ��*/
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;

    g_GmmGlobalCtrl.ucSuspendProc                = GMM_FALSE;
    g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult   = RRC_NAS_EST_RESULT_BUTT;
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;

    g_GmmInterRatCellReselect = 0;
    g_GmmGlobalCtrl.ucEventCause = GMM_EVENT_CAUSE_INVALID;
    /* ��ʼ��Ϊû���յ�����detach��Ϣ */
    g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_FALSE;

    g_GmmGlobalCtrl.ucIsNeedStartT3340PdpExist = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    /* Ĭ��֧��L���� */
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs     = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq          = NAS_MML_GetVoiceDomainPreference();
#endif

    /* ��RAC����ʼֵ */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, aucDefaultRac, ucLen);

    /* ��RAC����ʼֵ */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, aucDefaultRac, ucLen);

    /* ��ʼ��3311��ʱ��δ��ʱ */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    return;
}


VOS_VOID Gmm_TaskInit(VOS_VOID)
{
    VOS_UINT8 i;

    Gmm_MemSet(&g_GmmTimerMng, 0, sizeof(GMM_TIMER_STRU));

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3310].ulTimerVal = GMM_TIMER_T3310_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3311].ulTimerVal = GMM_TIMER_T3311_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = GMM_TIMER_T3312_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3316].ulTimerVal = GMM_TIMER_T3316_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3317].ulTimerVal = GMM_TIMER_T3317_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3318].ulTimerVal = GMM_TIMER_T3318_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3319].ulTimerVal = GMM_TIMER_T3319_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3320].ulTimerVal = GMM_TIMER_T3320_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3321].ulTimerVal = GMM_TIMER_T3321_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3330].ulTimerVal = GMM_TIMER_T3330_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_1S   ].ulTimerVal = GMM_TIMER_1S_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_POWER_OFF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;

    /* GCF����,�ػ�detach��ʱ��ʱ��Ϊ8S */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_GCF_POWER_OFF_VALUE;
    }

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT].ulTimerVal
            = GMM_TIMER_PROTECT_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_FOR_SIGNALING].ulTimerVal
            = GMM_TIMER_PROTECT_FOR_SIGNALING_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_SUSPENDED].ulTimerVal
            = GMM_TIMER_SUSPENDED_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_RAU_RSP].ulTimerVal
            = GMM_TIMER_RAU_RSP_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_OLD_TLLI].ulTimerVal
            = GMM_TIMER_PROTECT_OLD_TLLI_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF].ulTimerVal = GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF].ulTimerVal = GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerVal    = GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_CONNECT_REL].ulTimerVal    = GMM_TIMER_WAIT_CONNECT_REL_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_TC_DELAY_SUSPEND_RSP].ulTimerVal = GMM_TIMER_TC_DELAY_SUSPEND_RSP_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3323].ulTimerVal = GMM_TIMER_T3323_VALUE;


    /* GMM HO��GU���ϵͳ��Ϣ��ʱ�� */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_HO_WAIT_SYSINFO].ulTimerVal = GMM_TIMER_WAIT_SYSINFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU].ulTimerVal = GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU_VALUE;


    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO].ulTimerVal = GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU].ulTimerVal = GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_PS_SMS_CONN_REL].ulTimerVal    = GMM_TIMER_DELAY_PS_SMS_CONN_REL_VALUE;
    
    for (i = 0; i < GMM_TIMER_NUM; i++)
    {
        g_GmmTimerMng.aTimerInf[i].ucMode = VOS_RELTIMER_NOLOOP;
        g_GmmTimerMng.aTimerInf[i].hTimer = VOS_NULL_PTR;
    }
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;

    Gmm_MemSet(&gstGmmSuspendCtrl, 0x0, sizeof(GMM_SUSPEND_CTRL_STRU));

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_NET_RAT_TYPE_WCDMA;
    gstGmmSuspendCtrl.ucRauCause                  = GMM_RAU_FOR_NORMAL;
    gstGmmSuspendCtrl.ucT3312State                = GMM_T3312_NOT_TIMEOUT;
    gstGmmSuspendCtrl.ucNetModeChange             = GMM_FALSE;
    gstGmmSuspendCtrl.ucPowerOff                  = GMM_POWER_OFF_NOT_RCV;

    gstGmmSuspendCtrl.ucGetLteSecContext          = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif

    Gmm_ComVariantInit();

    return;
}


MMCGMM_DETACH_REQ_STRU* NAS_GMM_MakeDetachMsg( VOS_UINT32  ulDetachCause )
{

    MMCGMM_DETACH_REQ_STRU* pSndMsg = VOS_NULL_PTR;                                     /* ����ԭ������ָ��                         */

    /*������Ϣ  */
    pSndMsg = (MMCGMM_DETACH_REQ_STRU*)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

    if ( VOS_NULL_PTR == pSndMsg )
    {                                                                           /* �ڴ�����ʧ��                             */
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mmc_SndGmmDetachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_NULL_PTR;                                                                 /* ����                                     */
    }

    /* Added by h00313353 for Iteration 13, 2015-4-29, begin */
    Gmm_MemSet(pSndMsg, 0x00, sizeof(MMCGMM_DETACH_REQ_STRU));
    /* Added by h00313353 for Iteration 13, 2015-4-29, end */

    pSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    /* Added by h00313353 for Iteration 13, 2015-4-29, begin */
    pSndMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    /* Added by h00313353 for Iteration 13, 2015-4-29, end */

    /* ��д��Ϣ���                             */
    pSndMsg->MsgHeader.ulMsgName   = MMCGMM_DETACH_REQ;                         /* ��д��Ϣ����                             */

    pSndMsg->enDetachType          = ulDetachCause;

    return pSndMsg;

}

VOS_VOID NAS_GMM_RcvSmPdpModifyInd(VOS_VOID *pRcvMsg)
{
#if (FEATURE_LTE == FEATURE_ON)
    GMMSM_PDP_MODIFY_IND_STRU          *pSmPdpModifyInd;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enCurrTinType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT8                           ucNsapi;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pSmPdpModifyInd = (GMMSM_PDP_MODIFY_IND_STRU *)pRcvMsg;
    ucNsapi         =  pSmPdpModifyInd->ucNsapi;
    enCurrTinType   =  NAS_MML_GetTinType();
    enCurrRatType   =  NAS_MML_GetCurrNetRatType();
    pstRplmnCfgInfo =  NAS_MML_GetRplmnCfg();

    /* 3GPP 24008 6.3  Coordination between SM and GMM for supporting ISR�½�������
       This subclause applies to a MS with its TIN set as "RAT related TMSI" for which ISR is activated.
       The MS shall change its TIN to "P-TMSI" to deactivate ISR:
       -   upon modification of any PDP context which was activated before the ISR is activated in the MS
    */
    if ((VOS_TRUE == NAS_MML_IsPsBearerExistBeforeIsrAct(ucNsapi))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enCurrTinType)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrRatType))
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif
    return;
}
VOS_VOID NAS_GMM_RcvSmPdpDeactivatedInd(VOS_VOID *pRcvMsg)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pSmPdpStatusInd;
    MMCGMM_DETACH_REQ_STRU             *ptr;
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurRat;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();

    pstConnStatus   = NAS_MML_GetConnStatus();

    pSmPdpStatusInd = (GMMSM_PDP_DEACTIVATED_IND_STRU *)pRcvMsg;

    /* û�ж���ʱ,���follow on��־ */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }


    /* ����ǰ�л�����Ϣ,���ͷŵ�����TD���ڲ�list��ʱ������û�����PDP���
       ��ʱ��ȻulMsgHoldMskΪ�գ����Ի�����PS SERVICE��ʶ��������Ҫ����� */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvSmPdpDeactivatedInd(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        /* pSmPdpStatusInd->ulPdpContextStatus�н��õ��˵�ʮ��λ */
        if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
        {
            /* �Ѿ�û�м����PDP */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "NAS_GMM_RcvSmPdpDeactivatedInd:Normal: Service is CS ONLY,Detach PS");

            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

            /* ����GMM״̬��ȥע�ỹ��������ȥע�� */
            if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
             || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
            {
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

                ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);

                if (VOS_NULL_PTR == ptr)
                {
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                    return;
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
            }
            else if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
            {
                Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                && (GMM_RRC_RRMM_EST_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                {                                                               /* �����������ڽ�����������                 */
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

                    ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);

                    if (VOS_NULL_PTR == ptr)
                    {
                        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                        return;
                    }
                    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
                }
                else
                {
                    Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
                }
            }
            else if ((GMM_REGISTERED_PLMN_SEARCH== g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
            {   /* ���ؽ�GMM״̬Ǩ��δע��״̬,����ǳ���������LL�Ѿ�������,��������ʱ��t3312δ��ʱ
                   �Ƿ���Ҫ����DETACH,����*/
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
                NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );


                /* ֪ͨGMM��ǰPS��DETACH��� */
                NAS_GMM_SndMmGprsDetachComplete();

                Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);

                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    Gmm_TimerStop(GMM_TIMER_T3314);
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

                    /* default 44s */
                    gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                }
            }
            else
            {
            }
        }
    }


    /* W��PDPȥ������GMM������������״̬��GMM_SERVICE_REQUEST_INITIATED��û�ж���ҵ��ʱ��Ҫ��T3340,
       �ȴ�RRC��·�ͷ�,�ڼ��յ���PDP��������GMM�������PDPȥ������·�ͷź��ٷ��� */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
     && (VOS_TRUE == g_GmmGlobalCtrl.ucRelConnAfterPdpDeact))
    {
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || ((GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
          && (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)))
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_WAIT_REL_PS_SIGNAL_VALUE;
            Gmm_TimerStart(GMM_TIMER_T3340);
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
        }
    }

    if ((VOS_FALSE == pstConnStatus->ucPsTbfStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_SndMmcTBFRelInd();
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
    {
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (NAS_MML_NET_RAT_TYPE_LTE != enCurRat))
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);

            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    return;
}
VOS_VOID Gmm_RcvSmPdpStatusInd(
                           VOS_VOID *pRcvMsg                                    /* ������Ϣʹ�õ�ͷ��ַ����                 */
                           )
{
    GMMSM_PDP_STATUS_IND_STRU          *pSmPdpStatusInd;                        /* ����GMMSM_PDP_STATUS_IND_STRU����ָ��    */
    VOS_UINT8                           ucPrePdpStatusFlg;                      /* ԭ���Ƿ���ڼ����PDP context��־        */
    VOS_UINT8                           ucCurPdpStatusFlg;                      /* ��ǰ�Ƿ���ڼ����PDP context��־        */
    NAS_MML_PS_BEARER_CONTEXT_STRU      stPsBearCtx;
    VOS_UINT32                          i;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();


    PS_MEM_SET(&stPsBearCtx, 0x00, sizeof(stPsBearCtx));

    ucCurPdpStatusFlg = MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST;

    pSmPdpStatusInd = (GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg;                     /* �õ���Ϣָ��                             */

    ucPrePdpStatusFlg = pstConnStatus->ucPdpStatusFlg;

    /* ������Ϣ��pdp״̬����MML��ȫ�ֱ��� g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        stPsBearCtx.enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        stPsBearCtx.ucPsActPending   = VOS_FALSE;
        stPsBearCtx.ucPsDeactPending = VOS_FALSE;

        if (GMMSM_PDP_STATE_ACTIVE == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;

            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
            }
        }
        else if (GMMSM_PDP_STATE_ACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsActPending  = VOS_TRUE;
            /* Modify by zwx247453 for 3 modem tas, 2015-07-20, Begin */
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
            /* Modify by zwx247453 for 3 modem tas, 2015-07-20, End */
        }
        else if (GMMSM_PDP_STATE_INACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsDeactPending = VOS_TRUE;
            ucCurPdpStatusFlg            = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else
        {
        }

        /* פ����L,��L����pdp״̬ */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetPsBearerCtx((VOS_UINT8)(i + NAS_MML_MIN_NSAPI), &stPsBearCtx);
        }
        /* LTE��ʱ,ֻ��Ҫ����״̬ΪPENDING��PDP״̬ */
        else
        {
            NAS_Gmm_ClearPendingPdpStatus();
        }

    }

    if ( MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;
    }
    else
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_TRUE;
    }

    if (ucPrePdpStatusFlg != pstConnStatus->ucPdpStatusFlg)
    {                                                                           /* PDP CONTEXT״̬�仯                      */
        Gmm_SndMmcPdpStatusInd(ucCurPdpStatusFlg);                              /* ֪ͨMMC���µ�PDP CONTEXT״̬             */
    }

    /* PDPȥ�����֪ͨLL��GRM���������û������������� */
    if(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID NAS_GMM_ConvertSmSessionTypeToRrc(
    GMMSM_SESSION_TYPE_ENUM_UINT8       enGmmSmSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmSessionType)
    {
        case GMMSM_SESSION_TYPE_CONVERSAT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case GMMSM_SESSION_TYPE_STREAM_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case GMMSM_SESSION_TYPE_INTERACT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case GMMSM_SESSION_TYPE_BACKGROUND_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif


VOS_VOID NAS_GMM_RcvSmBeginSessionNotify_PreProc(
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif     

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_START);

    return;
}


VOS_VOID NAS_GMM_RcvSmEndSessionNotify_PreProc(
    GMMSM_END_SESSION_NOTIFY_STRU      *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif 

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_FINISH);

    return;
}



VOS_VOID Gmm_ComPlmnSearchInit()
{
    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {
        /* ��ǰ��ΪPS����Ч */
        if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);                        /* ����״̬�Ĺ�������                       */
            if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
            {
                Gmm_TimerStop(GMM_TIMER_T3311);

                if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    Gmm_TimerStop(GMM_TIMER_T3302);
                }
            }
        }
    }
    else if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM != g_GmmGlobalCtrl.ucPlmnSrchPreSta))
    {                                                                           /* REGISTERED״̬���ҷ�������               */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);                              /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);

        if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Gmm_TimerStop(GMM_TIMER_T3302);
        }
    }

    else if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }


        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {   /*ֻ���û������detach���̲Ż����GMM_DEREGISTERED_INITIATED*/
        /*����Ҫ�жϵ�ǰdetach����*/
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }
        else
        {

        }

        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        if (GMM_MSG_HOLD_FOR_RAU
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {                                                                       /* ����б�����RAUԭ��                      */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);   /* ��ȡRAUԭ���ַ                          */
        }
        Gmm_ComCnfHandle();
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        Gmm_ComCnfHandle();
    }
    else if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_SUSPENDED);

        g_GmmRauCtrl.ucNpduCnt = 0x0;
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        else
        {
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                           GMM_RABM_IMMEDIATELY_RAU);
#endif

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        GMM_BufferMsgDump();

        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }
    else if ( GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState )
    {
        /* ǩ������״̬ */
        if ( (0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
          || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
        }

        /* GSM�µ�ϵͳ��Ϣ��ʼ�� */
        NAS_GMM_FreeGsmSysInfo();

        /* �������ݵĴ��� */
        GMM_BufferMsgResume();
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* �����еȴ�cnf                            */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �����ǰ����                             */
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* ��������Ĺ���                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* �����¼��CSͨ��������                   */

}



VOS_VOID Gmm_RcvMmcPlmnUserSelReq(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_VOID            *pAddr;

    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ж��Ƿ����������                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                   /* �ͷ�����                                 */
    }

    if (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    Gmm_ComPlmnSearchInit();

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* �õ���Ϣͷ                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* ���P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
                /* Modified by h00313353 for iteration 9, 2015-2-4, end */
            }
            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */
            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC����MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* ����״̬�Ĺ�������                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);                /* ��SIM�������ڱ�־                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* ���IMSI����MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* ���P_TMSI����MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;      /* ���P_TMSI_SIGNATURE����MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                 /* ֪ͨRRC NAS����Ϣ�仯                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */

    return;                                                                     /* ����                                     */
}


VOS_UINT32 GMM_ComCheckRauIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                                VOS_UINT32  ulMsgLen)
{
    GMM_RAI_STRU                        stRauRai;
    VOS_UINT8                           aucRauPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT8                           ucPtmsiAvail;
    VOS_UINT32                          ulIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*ROUTING AREA UPDATE ACCEPT (at periodic routing area update with no
        change of routing area or temporary identity)*/
        if (GMM_FALSE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            return GMM_FALSE;
        }

        /* ��ȡ RAU ACCEPT��Ϣ RAI����*/
        Gmm_FillRaiForRcv(&stRauRai, &pucMsgContent[4]);

        ucPtmsiAvail = GMM_FALSE;
        PS_MEM_SET(aucRauPtmsi, 0x00, NAS_MML_MAX_PTMSI_LEN);

        /* ��ȡ RAU ACCEPT��Ϣ PTMSI����*/
        for (ulIeCount=10; ulIeCount < ulMsgLen; ulIeCount++ )
        {
            if (GMM_IEI_P_TMSI_SIGNATURE == pucMsgContent[ulIeCount])
            {
                /* P-TMSI signatureΪ4���ֽڣ��˴���3��Forѭ���ټ�1 */
                ulIeCount += 3;
                continue;
            }

            if (GMM_IEI_ALLOCATED_PTMSI == pucMsgContent[ulIeCount])
            {
                if ( GMM_MOBILE_ID_TMSI_PTMSI == (pucMsgContent[ulIeCount+2] & 0x07) )
                {
                    ucPtmsiAvail = GMM_TRUE;
                    PS_MEM_CPY(aucRauPtmsi, &pucMsgContent[ulIeCount+3], NAS_MML_MAX_PTMSI_LEN);
                }
                break;
            }
        }

        /* ���RAIû�з����ı� */
        if (GMM_TRUE == Gmm_Com_CmpRai(&stRauRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
        {
            /* û�з���PTMSI */
            if (GMM_FALSE == ucPtmsiAvail)
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            /* �����PTMSI����ǰ��ͬ */
            else if ( 0 == VOS_MemCmp(aucRauPtmsi,NAS_MML_GetUeIdPtmsi(),NAS_MML_MAX_PTMSI_LEN) )
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}


VOS_UINT32 GMM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                            VOS_UINT32  ulMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* ���ٽ���ģʽ���ڲ���ģʽ�������������Լ�� */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return GMM_TRUE;
    }

    /* �����Լ���������UMTS���� */


    /* �����Լ���������UMTS���� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }

    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())

    {
        return GMM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* �����Ա����Ѿ����� */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* �����Ա���û������ */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (GMM_PD_GMM == ucPD)
        {
            ucMsgType = pucMsgContent[1];
            switch (ucMsgType)
            {
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                case GMM_MSG_IDENTITY_REQUEST:
                case GMM_MSG_ATTACH_REJECT:
                case GMM_MSG_RAU_REJECT:
                case GMM_MSG_SERVICE_REJECT:
                    ulIntegrityCheckResult = GMM_TRUE;
                    break;
                case GMM_MSG_RAU_ACCEPT:
                    ulIntegrityCheckResult =
                     GMM_ComCheckRauIntegrityProtection(pucMsgContent,ulMsgLen);
                    break;

                case GMM_MSG_DETACH_ACCEPT:
                    /* DETACH ACCEPT (for non power-off) */
                    if ((GMM_GPRS_DETACH_POWEROFF != g_GmmGlobalCtrl.ucSpecProc)
                      && (GMM_COMBINED_DETACH_POWEROFF !=
                                            g_GmmGlobalCtrl.ucSpecProc))
                    {
                        ulIntegrityCheckResult = GMM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if (GMM_PD_RSV_FOR_TEST == ucPD)
        {
            ulIntegrityCheckResult = GMM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}
VOS_UINT32 NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg (VOS_VOID)
{
    /* 24008 4.7.5.1.5 �½���������:
    Routing area updating and P-TMSI reallocation procedure collision
    - If the MS receives a P-TMSI REALLOCATION C0MMAND message before the routing area
    updating procedure has been completed, the P-TMSI reallocation procedure shall
    be aborted and the routing area updating procedure shall be progressed.*/
    if (NAS_GMM_SPEC_PROC_TYPE_RAU == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
    {
        return VOS_FALSE;
    }

    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_UINT32 NAS_GMM_IsNeedProcStatusMsg (VOS_VOID)
{

    /* detach���������detach ���Ͳ�Ϊimsi detach�򲻴��� */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_GMM_IsNeedProcGmmInfoMsg (VOS_VOID)
{

    /* detach���������detach ���Ͳ�Ϊimsi detach�򲻴��� */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}




VOS_VOID Gmm_RcvRrmmDataInd(
                        VOS_VOID *pRcvMsg                                       /* ������Ϣʹ�õ�ͷ��ַ����                 */
                        )
{
    RRMM_DATA_IND_FOR_PCLINT_STRU  *pRrmmDataInd;
    NAS_MSG_FOR_PCLINT_STRU        *pNasMsg;
    NAS_MSG_STRU                   *pGmmStatus;

    pRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pRcvMsg;                    /* �õ���Ϣ���׵�ַ                         */
    if ( RRC_NAS_CS_DOMAIN == pRrmmDataInd->ulCnDomainId )
    {                                                                           /* �������Ϣ                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: CS data is received in RRMM_DATA_IND");
        return;
    }
    if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��ǰû������                             */
        if (GMM_FALSE == GMM_IsCasGsmMode())
        {                                                                       /*3G�������ǰû�����ֱ�ӷ��ء�2G���������ӱ�־ʼ����Ч */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Signalling connection is not existed");
            return;
        }
    }

    pNasMsg = &pRrmmDataInd->RcvNasMsg;                                         /* �õ�NAS��Ϣ�ṹ�ĵ�ַ                    */
    if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        && (GMM_PD_RSV_FOR_TEST != (pNasMsg->aucNasMsg[0] & 0x0F)))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: In TC_ACTIVE, other NT message than TC is omitted");
        Gmm_MemFree(pRcvMsg);                                                   /* �ͷŽ��յ�����Ϣ�ڴ�                     */
        return;
    }

    if (2 > pNasMsg->ulNasMsgSize)
    {                                                                           /* ��Ϣ����                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Message from NT is too short");
        return;
    }

    if (GMM_FALSE == GMM_ComCheckIntegrityProtection(pNasMsg->aucNasMsg, pNasMsg->ulNasMsgSize))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Integrity Check Fail");
    }
    else
    {

        /* �յ��˴���������NAS����Ϣ */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch (pNasMsg->aucNasMsg[0] & 0x0F)
        {                                                                       /* ����Protocol discriminator�ַ�           */
        case GMM_PD_GMM:
            if (0 != ( pNasMsg->aucNasMsg[0] & 0xF0))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: NT message is invalid");
                return;
            }

            GMM_ReportN2MOtaMsg((NAS_MSG_STRU *)pNasMsg);


            switch (pNasMsg->aucNasMsg[1])
            {                                                                   /* ����Message type�ַ�                     */
            case GMM_MSG_ATTACH_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* 2G�����£�֪ͨGAS��GMM������ɣ�GRR��ֹͣnon_DRX״̬ */



                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }

                Gmm_RcvAttachAcceptMsg(pNasMsg);                                /* �տ���ϢAttach accept�Ľ��մ���          */
                break;
            case GMM_MSG_ATTACH_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {/* 2G�����£�֪ͨGAS��GMM������ɣ�GRR��ֹͣnon_DRX״̬ */



                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvAttachRejectMsg(pNasMsg);                                /* �տ���ϢAttach reject�Ľ��մ���          */
                break;
            case GMM_MSG_DETACH_REQUEST:
                if(GMM_TRUE == GMM_IsCasGsmMode())
                {
                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvDetachRequestMsg(pNasMsg);                               /* �տ���ϢDetach request�Ľ��մ���         */
                break;
            case GMM_MSG_DETACH_ACCEPT:
                Gmm_RcvDetachAcceptMsg(pNasMsg);                                /* �տ���ϢDetach accept�Ľ��մ���          */
                break;
            case GMM_MSG_RAU_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {


                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateAcceptMsg(pNasMsg);                     /* �տ���ϢRouting area update accept�Ľ��� */
                break;
            case GMM_MSG_RAU_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {


                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateRejectMsg(pNasMsg);                     /* �տ���ϢRouting area update reject�Ľ��� */
                break;
            case GMM_MSG_SERVICE_ACCEPT:
                Gmm_RcvServiceAcceptMsg(pNasMsg);                               /* �տ���ϢService Accept�Ľ��մ���         */
                break;
            case GMM_MSG_SERVICE_REJECT:
                Gmm_RcvServiceRejectMsg(pNasMsg);                               /* �տ���ϢService Reject�Ľ��մ���         */
                break;
            case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
                if (VOS_TRUE == NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg())
                {
                    Gmm_RcvPtmsiReallocationCommandMsg(pNasMsg);                /* �տ���ϢP-TMSI reallocation command����  */
                }
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                Gmm_RcvAuthenAndCipherRequestMsg(pNasMsg);                      /* Authentication and ciphering request���� */
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                Gmm_RcvAuthenAndCipherRejectMsg(pNasMsg);                       /* Authentication and ciphering reject����  */
                break;
            case GMM_MSG_IDENTITY_REQUEST:
                Gmm_RcvIdentityRequestMsg(pNasMsg);                             /* �տ���ϢIdentity request�Ľ��մ���       */
                break;
            case GMM_MSG_GMM_STATUS:
                if (VOS_TRUE == NAS_GMM_IsNeedProcStatusMsg())
                {
                    Gmm_RcvGmmStatusMsg(pNasMsg);                               /* �տ���ϢGMM Status�Ľ��մ��� */
                }
                break;
            case GMM_MSG_GMM_INFORMATION:
                if (VOS_TRUE == NAS_GMM_IsNeedProcGmmInfoMsg())
                {
                    Gmm_RcvGmmInformationMsg(pNasMsg);                          /* �տ���ϢGMM Information�Ľ��մ��� */
                }
                break;
            default :
                pGmmStatus = Gmm_GmmStatusMsgMake(
                    NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: The MsgType is Abnormal");
                break;
            }
            break;

        case GMM_PD_SM:
            Gmm_SndSmDataInd(pNasMsg);                                          /* ԭ��GMMSM_DATA_IND�ķ��ʹ���             */
            break;

        case GMM_PD_SMS:
            if (GMM_NULL_PROCEDURE == g_GmmGlobalCtrl.ucSpecProc)
            {
                Gmm_SndSmsUnitdataInd(pNasMsg);                                 /* ԭ��PMMSMS_UNITDATA_IND�ķ��ʹ���        */
            }
            break;

        case GMM_PD_RSV_FOR_TEST:
            Gmm_SndTcDataInd(pNasMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Protocol discriminator is Error");
            break;
        }
    }

    return;
}


VOS_VOID GMM_RcvMmcRelReq(
    VOS_VOID                           *pMsg                                    /* ��Ϣָ��                                 */
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* GU�´���PSҵ��ʱ��MMC��MM/GMM�����ͷ�����
       GMM������㷢���ͷ����������ͷź��·�SYSCFG */

    /* ֪ͨWRR�ͷ�����.��״̬������״̬ʱ,˵��ԭ���Ѿ�֪ͨ�������ͷ�,����Ҫ�ظ�֪ͨ */
    if (((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
        case GMM_REGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegInit();
            break;
        case GMM_DEREGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_DeregInit();
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_GMM_RcvMmcRelReq_RauInit();
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegImsiDtchInit();
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo();
            break;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            break;
        default:
            break;
    }

    if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {                                                                           /* ��ǰ���ڷ�ע��״̬                       */
        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }
    else
    {                                                                           /* ��ǰ����ע��״̬                         */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    /* �����û��棬��֤���ݲ����·� */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_RegInit()
{
    /* ֹͣע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3310);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }


    /* �յ�MMC��rel req,��Ϊע��ʧ�ܣ�����ע��ʧ�ܵĴ�����RauInit״̬ʱ�յ�rel_ind�Ĵ������� */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);             /* ����attach attempt counter�Ĵ���         */

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���fallowon��־                         */

    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);



    return;
}
VOS_VOID NAS_GMM_RcvMmcRelReq_DeregInit()
{
    /* ֹͣȥע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_RR_REL);

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
    }
    else
    {
        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_DeregInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_RauInit()
{

    /* ֹͣ·���������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3330);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* �յ�MMC��rel req,��Ϊע��ʧ�ܣ�����ע��ʧ�ܵĴ�����RauInit״̬ʱ�յ�rel_ind�Ĵ������� */

    /* �����Ա�����־��ΪDEACTIVE */
    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* ���RAU��LU��־ */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    /* ������ڼ�Ȩ��������ȴ���־ */
    NAS_GMM_ClearAuthInfo();


    /* ������ڽ���������ȴ���־ */
    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ���Ӧ��־                           */
    }

    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* ����RAU attempt counter�Ĵ���            */

    /* free֮ǰ�����ϵͳ��Ϣ */
    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();


    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}
VOS_VOID NAS_GMM_RcvMmcRelReq_RegImsiDtchInit()
{
    /* ֹͣȥע������е���ض�ʱ�� */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    /* ������ڼ�Ȩ��������ȴ���־ */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_RegImsiDtchInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

    return;
}


VOS_VOID NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo()
{
    /*��ϵͳ�ı�ʱ֪ͨRABM*/
    g_GmmRauCtrl.ucNpduCnt = 0x0;
    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
}



VOS_VOID Gmm_RcvMmcCoverageLostInd(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* ����MSG_HEADER_STRU����ָ��              */
    VOS_VOID            *pAddr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* ����ʱ, ָʾRABM��ǰϵͳģʽ, ������RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* ��GSMģʽ�£����������������ʱ��Ҫ����LLC����ֹ�û�������������� */
    if(GMM_TRUE == GMM_IsCasGsmMode())
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE;
        }
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    g_GmmGlobalCtrl.ucCvrgAreaLostFlg     = GMM_TRUE;
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg   = GMM_FALSE;
    g_GmmGlobalCtrl.ucCipherStartFlg      = GMM_FALSE;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ֹͣT3310                                */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ֹͣT3317                                */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ֹͣT3321                                */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ֹͣT3330                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* ֹͣT3340                                */

    if (GMM_TIMER_PROTECT_FOR_SIGNALING_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_PROTECT_FOR_SIGNALING_FLG))

    {                                                                           /* ����Timer�Ƿ�������,��                   */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);                         /* ͣ����Timer                              */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ�cnf                                */
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���T3311������                          */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ֹͣT3311                                */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* �ָ����б������Timer                    */
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvCoverLost_RegInit();
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvCoverLost_DeregInit();
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvCoverLost_RauInit();
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvCoverLost_ServReqInit();
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_RcvCoverLost_RegNmlServ();
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvCoverLost_RegImsiDtchInit();
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvCoverLost_SuspendWaitForSys();
        break;
    default:
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* PS ����Ч��״̬��Ǩ�� */
    if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {                                                                       /* ��ǰ���ڷ�ע��״̬                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                  /* ����״̬�Ĺ�������                       */
        }
        else
        {                                                                       /* ��ǰ����ע��״̬                         */
            Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);                    /* ����״̬�Ĺ�������                       */
        }
    }

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* �õ���Ϣͷ                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* ���P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
                /* Modified by h00313353 for iteration 9, 2015-2-4, end */
            }
            Gmm_ComStaChg(GMM_NULL);                     /* ����״̬�Ĺ�������                       */
            Gmm_SndMmcPowerOffCnf();                                            /* ��MMC����MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* ����״̬�Ĺ�������                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* �嵱ǰ����                               */
            NAS_MML_SetSimPresentStatus(VOS_FALSE);                             /* ��SIM�������ڱ�־                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* ���IMSI����MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* ���P_TMSI����MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;/* ���P_TMSI_SIGNATURE����MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                /* ֪ͨRRC NAS����Ϣ�仯                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */

        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;
        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                             /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }

    Gmm_FreeBufferMsgWithoutSm();

    g_GmmReqCnfMng.ucCnfMask            = 0;                                    /* �����еȴ�cnf                            */
    g_GmmGlobalCtrl.ucSpecProc          = GMM_NULL_PROCEDURE;                   /* �����ǰ����                             */
    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_NULL_PROCEDURE;                   /* ��������Ĺ���                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* �����¼��CSͨ��������                   */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcCoverageLostInd:INFO: specific procedure ended");

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvMmcPlmnSearchInitiated(VOS_VOID)
{

    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;                          /* ����ϵͳ��Ϣ��Ч�ı�־                   */

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);
    }
    else
    {
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬ΪNULL״̬                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPlmnSearchInitiated:WARNING: GMM state is VOS_NULL_PTR(Gmm_RcvMmcPlmnSearchInitiated)");
        return;
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    if ((GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
        }
        else
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
        }

        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);

        Gmm_ComPlmnSearchInit();
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcStartReq(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucTmpTmsi;
    VOS_UINT32                          ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsiSig;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;
#endif

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* ��ǰפ����������뼼�� */

    enNetRatType = NAS_MML_GetCurrNetRatType();

    Gmm_ComReset();                                                             /* ����reset�������� */

    GMM_CasChangSysMode(enNetRatType);


#if (FEATURE_ON == FEATURE_LTE)

    /* ��¼����ʱ��MS Radio Capability��Ӧ�Ľ��뼼���б� */
    PS_MEM_CPY(&(g_GmmGlobalCtrl.UeInfo.stRadioCpbRelatedRatList),
               NAS_MML_GetMsPrioRatList(),
               sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
#endif


    /* ��ǰ��Ȼ֧��UMTS��Ȩ */
    g_GmmAuthenCtrl.ucUmtsAuthFlg           = GMM_UMTS_AUTHEN_SUPPORTED;

    /* ��ǰ��Ȼ֧��GMM INFORMATION */
    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg = GMM_SUPPORT_INFORMATION_MSG;

    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

#if (FEATURE_ON == FEATURE_ECALL)
    enCallMode = NAS_MML_GetCallMode();
#endif

    /* ���õ�ǰPS���Ƿ���Ч */
    if ((VOS_TRUE == NAS_MML_GetSimPresentStatus())
#if (FEATURE_ON == FEATURE_ECALL)
     /* ����3GPP 24.008 section 4.7:
     * 1. An eCall only mobile station shall not perform a normal or combined GPRS attach procedure.
     * 2. An eCall only mobile station shall not perform any kind of GPRS detach procedure.
     * 3. An eCall only mobile station shall not perform a normal or combined routing area updating procedure.
     * �����GMM��������PS sim��Ч��ʹ����GMM����NO_IMSI״̬
     */

     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    {
        NAS_MML_SetSimPsRegStatus(VOS_TRUE);
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_IMSI;
    }
    else
    {
        NAS_MML_SetSimPsRegStatus(VOS_FALSE);
        Gmm_SndMmcStartCnf();
        return;
    }

    /* ���ݵ�ǰ�洢��TMSI�Ƿ���Ч���趨�Ƿ����PTMSI */
    ulInvalidCnt = 0;
    pucTmpTmsi = NAS_MML_GetUeIdPtmsi();
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (GMM_PTMSI_INVALID == pucTmpTmsi[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI ��Ч                              */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }
    else
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;
    }

    ulInvalidCnt = 0;
    pucTmpTmsiSig = NAS_MML_GetUeIdPtmsiSignature();

    ulInvalidCnt = 0;
    for (i=0; i<NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        if (GMM_PTMSI_SIGNATURE_INVALID == pucTmpTmsiSig[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI signature��Ч                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

    }
    else
    {                                                                           /* P-TMSI signature��Ч                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* ������Ӧ���ڱ�ʶ                         */
    }


    /* Ϊ�˷�ֹʹ�ò��ԺŶαܹ�IMSI�ļ�飬ʹ���ܹ�ʹ��TMSI����ע�ᣬ��Ҫ
       ���з��������ж�����NV��������£�����Ŷ�TMSI��Ϊ��Ч
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdPtmisInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }


    Gmm_SndMmcStartCnf();

    return;                                                                     /* ����                                     */
}
VOS_UINT32 NAS_GMM_CheckSimStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS����Ч��MMC_GMM_ATTACH_TYPE_GPRS_IMSI����ת��ΪMMC_GMM_ATTACH_TYPE_GPRS */
    if ( ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
      && ( VOS_TRUE != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: CS USIM is invalid.");

        if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* USIM PS����Ч��ֱ�ӻظ�ATTACH CNF */
    if ( ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
      && ( VOS_TRUE                 != pstUsimStatus->ucSimPsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM,"NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: PS USIM is invalid.");

        NAS_GMM_SndMmcAttachCnf();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_ModifyAttachType(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        /* ������ģʽI���յ�CS ATTACH��GMM������ */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType)
        {
            return VOS_TRUE;
        }

        /* ������ģʽI���յ�CS+PS ATTACH����ΪGPRS ATTACH */
        if (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* ֮ǰ����PS ATTACH �յ�PS ATTACH������OPID��ֱ�ӷ��� */
    if ( ( GMM_WAIT_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType ) )
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    /* ֮ǰ����CS ATTACH �յ�CS ATTACH��ֱ�ӷ��� */
    if ( ( GMM_WAIT_CS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType ) )
    {
        return VOS_TRUE;
    }

    if ( GMM_WAIT_CS_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
    {
        /* ֮ǰ����PS ATTACH �յ�CS+PS ATTACH���յ�PS ATTACH����OPID */
        if (MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_IsDetachNotAcceptNeedAttach(VOS_VOID)
{
    if (GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            NAS_GMM_SndMmGprsDetachComplete();

            NAS_GMM_SndMmcDetachCnf();
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType &=~GMM_WAIT_PS_DETACH;


        /* GMMֹͣPS���DETACH������ʱ�� */
        Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_IsAttachDetachConflicted(VOS_UINT32 ulAttachType)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* ֮ǰ������DETACH���� */
    if ( GMM_WAIT_NULL_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        return VOS_FALSE;
    }

    /* A+Iģʽ */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* ����ģʽI��,��DETACH����,ֱ�ӻظ�CNF */
        if ( MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType
                                        & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
            {
                return VOS_FALSE;
            }

            NAS_GMM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }

    /* ��A+Iģʽ */
    if ( ( ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType )
        && (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_PS_DETACH ) ) )
      || ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
    {
        if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
        {
            return VOS_FALSE;
        }

        NAS_GMM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* IMSI ATTACH��֮ǰ���г�ͻ */
    if ( (MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType )
        && (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_CS_DETACH ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_CheckSigConnStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    /* ����Ƿ���ר�����̴��� */
    if((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
    && ( MMC_MM_ATTACH_TYPE_GPRS == pstAttachReq->enAttachType )
    && (GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg))
    {
        return VOS_TRUE;
    }

    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_CheckAttachStatus(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_TRUE;

    if ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
    {                                                                           /* Ҫ��ATTACH PS��                          */
        NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_TRUE;

        /* GMM����ע��״̬��ֱ�ӻظ�PS CNF */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta )
         && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
        {                                                                       /* PS���Ѿ�ATTACH                           */
            NAS_GMM_SndMmcAttachCnf();

            if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_IMSI;
                ulRet                      = VOS_FALSE;
            }
        }
        else
        {                                                                       /* PS��û��ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_PS_ATTACH;
            g_GmmGlobalCtrl.stAttachInfo.ulOpid        = pstAttachReq->ulOpid;
            ulRet = VOS_FALSE;
        }
    }

    if ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
    {                                                                           /* Ҫ��ATTACH CS��                          */
        /* CS ����ATTACHED״̬���޸�GPRS_IMSI����ΪGPRS ATTACH */
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {                                                                       /* CS���Ѿ�ATTACH                           */
            ulRet = VOS_TRUE;

            if ( NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType  = MMC_GMM_ATTACH_TYPE_GPRS;
                ulRet                       = VOS_FALSE;
            }

        }
        else
        {                                                                       /* CS��û��ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_CS_ATTACH;
            ulRet                                      = VOS_FALSE;
        }
    }

    return ulRet;
}



VOS_UINT32 NAS_GMM_RcvMmcAttachReq_PreProc(
    MMCGMM_ATTACH_REQ_STRU             *pstmsg
)
{
    /* �ж��Ƿ���Ҫ�������Ϣ����Ч��Ϣ���������� */
    if ((MMC_MM_ATTACH_TYPE_IMSI      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pstmsg->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return VOS_TRUE;
    }


    if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = pstmsg->ulOpid;
    }


    /* ����Ƿ���ҵ����� */
    if (VOS_TRUE == NAS_GMM_CheckSigConnStatusAffectAttach(pstmsg))
    {
        if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
        {
            NAS_GMM_SndMmcAttachCnf();
        }

        return VOS_TRUE;
    }

    /* ���ATTACH�����Ƿ��SIM��״̬��ͻ */
    if ( VOS_TRUE == NAS_GMM_CheckSimStatusAffectAttach(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* ��������ģʽ����ATTACH���� */
    if ( VOS_TRUE == NAS_GMM_ModifyAttachType(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* ����Ƿ��֮ǰ����DETACH�г�ͻ */
    if ( VOS_TRUE == NAS_GMM_IsAttachDetachConflicted(pstmsg->enAttachType) )
    {
        return VOS_TRUE;
    }

    /* ���֮ǰ����ATTACH */
    if ( VOS_TRUE == NAS_GMM_IsAttachRepeated(pstmsg->enAttachType, pstmsg->ulOpid) )
    {
        return VOS_TRUE;
    }

    /* ���ע����� */
    if ( VOS_TRUE == NAS_GMM_CheckAttachStatus(pstmsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_CheckNeedBuffDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    MMCGMM_DETACH_REQ_STRU             *pstDetach;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        /* �Ѿ���DETACH���̽���ʱ������ģʽI�»���DETACH��Ϣ */
        if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
          && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode) )
        {
            pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
            if ( VOS_NULL_PTR == pstDetach )
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_CheckNeedBuffDetach:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                  return VOS_TRUE;
            }

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* ��ԭ�ﻺ���־                           */
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

            Gmm_MemCpy(pstDetach, pstmsg, sizeof(MMCGMM_DETACH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstDetach;       /* ����ԭ��                                 */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT32 NAS_GMM_ProcPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_FALSE;


    g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());



    g_GmmGlobalCtrl.stAttachInfo.enAttachType &=~GMM_WAIT_PS_ATTACH;
    g_GmmGlobalCtrl.stDetachInfo.enDetachType |= GMM_WAIT_PS_DETACH;

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_ProcCsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    /* ������ģʽI�£�������ֱ�ӷ��� */

    if (VOS_FALSE == NAS_GMM_IsNeedProcUserCsDetach())
    {
        return VOS_TRUE;
    }
    else
    {
        /* CS����ATTACHED״̬������־λ, ����ֱ�ӻظ�DETACH CNF*/
        if ( (MM_STATUS_ATTACHED                  == g_MmSubLyrShare.MmShare.ucCsAttachState)
          || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_INITIATED            == g_GmmGlobalCtrl.ucState) )
        {
            if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
            {
                /*  ����ģʽI�£�CS��ǰ��ҵ�����Ӵ��ڣ�syscfg���������detach cs��������ֱ�ӷ��� */
                if (VOS_TRUE == g_GmmDetachCtrl.ucSysCfgDetachFlg)
                {
                    return VOS_TRUE;
                }
            }

            g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
            g_GmmGlobalCtrl.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_GMM_ProcCsPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    /* ������ģʽI��,ֻ����PS�ı�־λ */
    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~GMM_WAIT_PS_ATTACH;
        g_GmmGlobalCtrl.stDetachInfo.enDetachType |=  GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid        = pstmsg->ulOpid;
    }
    else
    {
        /* ���ATTACH�ȴ���־ */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

        /* CS����ATTACHED״̬������־λ */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_CS_DETACH;
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid           = pstmsg->ulOpid;
    }

    g_GmmGlobalCtrl.ucUserPsAttachFlag = VOS_FALSE;

    return VOS_FALSE;
}


VOS_UINT32 NAS_GMM_RcvMmcDetachReq_PreProc(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    /* ����Detach���̱�����ʱ�� */
    NAS_GMM_StartDetachProtectingTimer(pstmsg);

    /* �ж��Ƿ���Ҫ����DETACH */
    if ( VOS_TRUE == NAS_GMM_CheckNeedBuffDetach(pstmsg) )
    {
        return VOS_TRUE;
    }


    if ( (MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH == pstmsg->enDetachReason)
      || (MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE  == pstmsg->enDetachReason) )
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_TRUE;
    }
    else
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;
    }

    /*  ����DETACH���ͷֱ��� */
    switch ( pstmsg->enDetachType )
    {
        case MMC_GMM_PS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;

        case MMC_GMM_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        case MMC_GMM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        default:
            GMM_LOG_WARN("NAS_GMM_RcvMmcDetachReq_PreProc:DETACH TYPE INVALID!");
            return VOS_TRUE;
     }


    return VOS_FALSE;
}
VOS_VOID Gmm_ComReset(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* ͣ����Timer                              */
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ��Ҫ��SM����Ӧ                           */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GMM_RESET);/* ֪ͨSM GMMע��ʧ��                       */

        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS�ڵȴ���Ӧ                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {                                                                           /* GMM��ǰ״̬ΪATTACHED                    */
        GMM_CasFsmStateChangeTo(GMM_NULL);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_ComReset:NORMAL: STATUS IS GMM_NULL");

        Gmm_SndSmStatusInd();                                                   /* ����ԭ��GMMSM_STATUS_IND                 */
    }
    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��Ҫ��RABM����Ӧ                         */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ����GMMRABM_REESTABLISH_CNF(failure)     */
    }
    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* ��PS������                               */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                                    /* �ͷ�����                                 */
    }
    Gmm_HoldBufferFree();                                                       /* ���������Ϣ                             */
    Gmm_ComVariantInit();                                                       /* GMM��ʼ��                                */

    return;                                                                     /* ����                                     */
}


VOS_UINT8 Gmm_DealWithBuffInProc(VOS_VOID)
{
    VOS_VOID               *pAddr;                                              /* ����ָ��                                 */
    VOS_UINT8               ucRet;                                              /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ����ֵ��ʼ��ΪFALSE                      */

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* ��ȡpower offԭ���ַ                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        NAS_GMM_FreeBufferCmMsg();
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        Gmm_MsgDistribute(pAddr);                                               /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }
    else
    {
    }
    return ucRet;
}
VOS_VOID Gmm_DealWithBuffAfterProc(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMSM_DATA_REQ_STRU                 *ptr;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ��������־                             */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*����ַ���Ϣ*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*�ͷű����RAMB��Ϣ*/
        Gmm_MemFree(pMsg);

        /*�ַ������Service��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*�ͷ���������ڴ�*/
        Gmm_MemFree(pRabmReEst);
    }

    if (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* ��������־                             */
        Gmm_MsgDistribute((VOS_VOID *)(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS)); /* ��������Ϣ�ַ�                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;

    }

    /* ����SM��Ϣ��GMM������̬����Ҫ���λ��棬��һ�λ���ȵ�GMM����
    *  ��������̬�Ŵ�����ʱ�ȷ������������Ϣ��Ҫ�ڶ��λ���
    *  �ȵ���ȫģʽ��ɺ��ٴ����������λ���ʹ��ͬһ������¼��Ϣ��ַ��
    *  ���ÿ�δ���ʱ������������ռ䣬��ʱ�ͷ�ԭ����ռ䡣
    */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        /*�������SM��Ϣ�ı�־*/
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

        if (VOS_NULL_PTR == pMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: GMM MSG HOLD FOR SM PTR IS NULL.");
            return;
        }
        /*���뻺����Ϣ���ڴ�*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
                   + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
        }
        if (VOS_NULL_PTR == ptr)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        /*����Ϣ�ݴ浽������ڴ���*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
                + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_DealWithBuffAfterProc(): Process cached SM Data Req");
        /*�ͷű����SM��Ϣ*/
        Gmm_MemFree(pMsg);
        /*�ַ������SM��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(ptr));
        /*�ͷ���������ڴ�*/
        Gmm_MemFree(ptr);
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_HoldBufferFree(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ��������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* ����б�����SmDataReqԭ��                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_HoldBufferFree(): Clear cached SM Data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* ��ȡSmDataReqԭ���ַ                    */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_GMM_RcvMmCmServiceRejectInd(
    VOS_VOID                           *pstMsg
)
{
    MMGMM_CM_SERVICE_REJECT_IND_STRU   *pstMmServRejInd;                      /* ����ָ��                                 */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceRejectInd:WARNING: It is not A+I(Gmm_RcvMmcCmServiceRejectInd)");
        return;
    }

    pstMmServRejInd = (MMGMM_CM_SERVICE_REJECT_IND_STRU *)pstMsg;                 /* ��ʼ��ָ��                               */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == pstMmServRejInd->enCause)
    {                                                                           /* ԭ��ֵΪ#4                               */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_TRUE;                               /* ����MmcCmServiceRejectInd#4����RAU�ı�־ */
    }

    return;
}
VOS_VOID NAS_GMM_RcvMmCsConnectInd_InProc(
    VOS_VOID                           *pstMsg                               /* ԭ��ָ��                                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstTmpMsg;

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ����ΪRAU                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ����ΪATTACH                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
        return;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* �����������ڽ�����������                 */
        pstTmpMsg = (MMGMM_CS_CONNECT_IND_STRU *)Gmm_MemMalloc(sizeof(MMGMM_CS_CONNECT_IND_STRU));
        if (VOS_NULL_PTR == pstTmpMsg)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcCmServiceInd_InProc:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(pstTmpMsg, pstMsg, sizeof(MMGMM_CS_CONNECT_IND_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)pstTmpMsg;              /* ������ԭ��                               */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* �ñ�����־                               */
    }
    else
    {                                                                           /* �������û�������һ�û������             */
        if (GMM_TIMER_T3317_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3317_FLG))
        {                                                                       /* ���T3317������                          */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* ͣT3317                                  */
        }
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                               /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ִ��RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* ���CS����RAU�ı�־                      */
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_RegNmlServ(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* ȡ�õ�ǰ��������Ϣ */
    pstConnStatus = NAS_MML_GetConnStatus();

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState )
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }

    /* CSҵ�������GS���������ڣ�RRC���ڣ�������������RAU��������ϱ�ϵͳ��Ϣ���ٷ�������rau*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRatType)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvMmCsConnectInd_RrcConnExist();
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* ���CS����RAU�ı�־                      */
    }
    else
    {
    }
}


VOS_UINT32 NAS_GMM_IsRcvRrmmEstCnfMsgValid(
    RRMM_EST_CNF_STRU                  *pRrmmEstCnf
)
{
    if (RRC_NAS_PS_DOMAIN != pRrmmEstCnf->ulCnDomainId)
    {                                                                           /* �ж���PS����Ϣ,��                        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: It is not PS domain(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }
    if (GMM_RRC_RRMM_EST_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ж��Ƿ����ڵȸ���Ӧ,��                  */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected");
        return VOS_FALSE;
    }
    if (g_GmmReqCnfMng.ucRrmmEstOpid != pRrmmEstCnf->ulOpId)
    {                                                                           /* OP ID�����                              */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected(OPID is not same)");
        return VOS_FALSE;
    }

    if (RRC_EST_ESTING == pRrmmEstCnf->ulResult)
    {                                                                           /* ���Ϊ���ڽ�                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: The result is invalid(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

VOS_VOID Gmm_RcvRrmmEstCnf(
                       VOS_VOID *pMsg                                           /* ԭ��ָ��                                 */
                       )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* ����ָ��                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    if (VOS_FALSE == NAS_GMM_IsRcvRrmmEstCnfMsgValid(pRrEstCnf))
    {
        return;
    }

    if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
    {                                                                           /* ���Ϊ�Ѿ�����                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result of RRMM_EST_CNF is unexpected");
    }

    switch(pRrEstCnf->ulResult)
    {
    case RRC_EST_RJ_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_EST_OTHER_ACCESS_BARRED:
        g_GmmGlobalCtrl.ucRelCause =
                    RR_REL_CAUSE_ACCESS_BARRED_CAUSE_ACCESS_CLASS_CONTROL;
        break;
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_NO_RF:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        break;

    case RRC_EST_RJ_SNW:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RRC_SNW;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result item of RRMM_EST_CNF Msg is SUCCESS");
        break;

    }

    g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                      /* ��ȴ���Ӧ��־                           */

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* ������ɹ�                             */
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* �������־λ                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: PS signatual exist");
        if (GMM_TIMER_T3312_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {                                                                       /* ���T3312������                          */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);         /* ֪ͨMMC PS���������Ӵ���                 */

#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        /* 24.008, 4.4.4.9, case f1, CR1099 update:
           W�¸���GMM��·���ƽṹ��������RRC��·״̬ */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            /* ���յ�RRMM_RESUME_INDʱ,û��ֹͣT3314,��Ϊ�˱���CCOʧ�ܻ���
               �������յ����ӽ����ɹ�ʱ��Ҫֹͣ�˶�ʱ�� */
            Gmm_TimerStop(GMM_TIMER_T3314);

            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

            NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

            gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

        }

    }
    else
    {
        /* ��·����ʧ�ܣ����GMM��·���Ʊ��� */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_GMM_ClearGmmLinkCtrlStru();
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
    }


    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_RegInit(pRrEstCnf);                                   /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_DeregInit(pRrEstCnf);                                 /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmEstCnf_RauInit(pRrEstCnf);                                   /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmEstCnf_ServReqInit(pRrEstCnf);                               /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmEstCnf_DeregNmlServ(pRrEstCnf);                              /* ���ø�״̬�µĴ���                       */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmEstCnf_RegImsiDtchInit(pRrEstCnf);                           /* ���ø�״̬�µĴ���                       */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmEstCnf:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}


VOS_VOID Gmm_RcvRrmmEstCnf_RegInit(
                               VOS_VOID *pMsg                                   /* ԭ��ָ��                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* ����ָ��                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ����Ϣ����                               */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3310);                                        /* ��T3310                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);                          /* ����״̬�Ĺ�������                       */
        enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_ATTACH_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* ��ǰ����Ϊcombined attach                */
            NAS_GMM_SndMmCombinedAttachRejected(enCause);       /* ����MMCGMM_COMBINED_ATTACH_REJECTED      */
        }
        else
        {                                                                       /* ��ǰ����Ϊnormal attach                  */
            NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                            enCause);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND         */
        }


        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        &enCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN
                        );

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);      /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_AttachAttemptCounter(enCause);                                      /* ����attach attempt counter�Ĵ���         */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* ������ڽ��е�specific���̱�־           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvRrmmEstCnf_DeregInit(
                                 VOS_VOID *pMsg                                 /* ԭ��ָ��                                 */
                                 )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_DeregInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );         /* ����PS���ֹע���־                     */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                      GMM_MMC_ACTION_RESULT_FAILURE,
                                      NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_DeregInit:INFO: specific procedure ended");
    }
    return;
}



VOS_VOID Gmm_RcvRrmmEstCnfAccessBar_RauInit( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);                            /* ����״̬�Ĺ�������                       */
    Gmm_ComCnfHandle();
    enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* �����ǰ������combined RAU               */
        NAS_GMM_SndMmCombinedRauRejected(enCause);          /* ����MMCGMM_COMBINED_ATTACH_REJECTED      */
    }
    else
    {                                                                       /* �����ǰ������normal RAU                 */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                         /* ����MMCGMM_GMM_ACTION_RESULT_IND         */
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnfAccessBar_RauInit:INFO: specific procedure ended");

}


VOS_VOID Gmm_RcvRrmmEstCnf_RauInit(
                               VOS_VOID *pMsg                                   /* ԭ��ָ��                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* ����ָ��                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;
    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_RauFailureInterSys();
        }
    }
    else
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }
    }


    /* ��RAU�����У�������Detach */
    if (0 != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & ~GMM_MSG_HOLD_FOR_DETACH) )
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RauInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3330);                                        /* ��T3330                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        /* Ϊ���ͺ������Ӷȣ�������Access bar�Ĵ����װΪ���µĺ��� */
        Gmm_RcvRrmmEstCnfAccessBar_RauInit();
    }
    else
    {
        /* TS24.008
        4.7.5.1.5 Abnormal cases in the MS
        g) Routing area updating and detach procedure collision
        GPRS detach containing detach type"re-attach required" or "re-attach not required":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be aborted and the GPRS detach procedure shall be
        progressed. If the DETACH REQUEST message contains detach type "re-attach not required" and GMM
        cause #2 "IMSI unknown in HLR", the MS will follow the procedure as described below for the detach type
        "IMSI detach".
        GPRS detach containing detach type "IMSI detach":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be progressed, i.e. the DETACH REQUEST message
        shall be ignored.


            4.7.4.1.4 Abnormal cases in the MS

            f) Change of cell into a new routing area
        If a cell change into a new routing area occurs before a DETACH ACCEPT message has been received, the
        GPRS detach procedure shall be aborted and re-initiated after successfully performing a routing area updating
        procedure. If the detach procedure is performed due to the removal of the SIM/USIM the MS shall abort the
        detach procedure and enter the state GMM-DEREGISTERED. */

        /* �������ӽ���ʧ��                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_RoutingAreaUpdateAttemptCounter(enCause);                           /* ����RAU attempt counter�Ĵ���            */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);


        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvRrmmEstCnf_ServReqInit(
                                   VOS_VOID *pMsg                               /* ԭ��ָ��                                 */
                                   )
{
    VOS_UINT32           ulCause;                                               /* ����ֲ�����                             */
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_ServReqInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3317);                                        /* ��T3317                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        if (RRC_EST_OTHER_ACCESS_BARRED == pRrEstCnf->ulResult)
        {                                                                       /* ��������                                 */
            ulCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

            /* ��ǰ��SM����� Service Request����, ��SM �ظ� Service Rej ��Ϣ�����ͷ��ϲ�Ӧ�á� */
            if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
                && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
            {
                GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

                g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
            }
        }
        else
        {
            ulCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
        }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmEstCnf_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

        /* �˴����ϱ�����״̬����Ϊ���������Ѿ������޷���ĵƣ�����ϱ�����ĵ�״̬ */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
        Gmm_ComCnfHandle();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        {                                                                       /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* ���ڱ������T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* �ָ�T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* ���ڱ������T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* �ָ�T3302                                */
            }
            else
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);                                /* ��T3312                                  */
            }
        }
        else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* ���ڱ������T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* �ָ�T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* ���ڱ������T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* �ָ�T3302                                */
            }
            else
            {
            }
        }
        else
        {
        }

        if ((VOS_TRUE == NAS_MML_GetDailRejectCfg())
         && (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == ulCause))
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_RRC_EST_FAIL);
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }


        /* �����ǰ��NO RF�Ľ���ʧ�ܣ���֪ͨSM��Ҫ���·���PDP���� */
        else if ( (GMM_FALSE         == GMM_IsCasGsmMode())
          && (RRC_EST_RJ_NO_RF  == pRrEstCnf->ulResult) )
        {
            Gmm_SndSmRelInd();
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }
        else
        {

        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulCause);                             /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulCause);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ulCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_ServReqInit:INFO: specific procedure ended");
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}
VOS_VOID Gmm_RcvRrmmEstCnf_DeregNmlServ(
                                    VOS_VOID *pMsg                              /* ԭ��ָ��                                 */
                                    )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* ����ָ��                                 */
    NAS_MSG_STRU           *pNasMsg;                                            /* ����ָ��                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����Ϊpower off����                  */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* ����RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* �������ӽ���ʧ��                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSIM���γ���detach����          */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* ����RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* �������ӽ���ʧ��                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    return;
}


VOS_VOID Gmm_RcvRrmmEstCnf_RegImsiDtchInit(
                                       VOS_VOID *pMsg                               /* ԭ��ָ��                                 */
                                       )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* ��������Ϣ����                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* ������Ϣ����ɹ�                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
     || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* �������ӽ����ɹ�                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �������ӽ���ʧ��                         */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬�Ĺ�������                       */
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
        }
        g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;          /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:INFO: specific procedure ended");
    }
    return;
}


VOS_VOID Gmm_RcvRrmmRelInd(
                       VOS_VOID *pMsg                                           /* ԭ��ָ��                                 */
                       )
{
    VOS_VOID                *pAddr;
    RRMM_REL_IND_STRU       *pRrRelInd;                                         /* ����ָ��                                 */

    pRrRelInd = (RRMM_REL_IND_STRU *)pMsg;                                      /* ��ʼ��ָ��                               */

    /* �������PS��ģ�GMM���������� */
    /* ����������¼���״̬�ȴ�est_cnf������rel causeΪRRC_REL_CAUSE_NAS_DATA_ABSENT������������:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */
    if (VOS_FALSE == NAS_GMM_IsNeedProcRelInd(pRrRelInd))
    {
        return;
    }



    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* �����Ȩ���ȫ�ֱ��� */
    NAS_GMM_ClearAuthInfo();

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3319);                                             /* ֹͣT3319                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* ֹͣT3340                                */
        
    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       


    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ��ȴ���Ӧ��־                           */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    /* ��������йػ��¼����յ�REL_INDʱ��Ҫ���� */
    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* ����б�����power offԭ��                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO:DEAL HOLD_POWEROFF_MSG");
        Gmm_TimerStop( GMM_TIMER_PROTECT_FOR_SIGNALING );
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* ��ȡpower offԭ���ַ                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* ���������־                             */
        Gmm_MsgDistribute( pAddr );                                             /* ��������Ϣ�ַ�                           */
        Gmm_MemFree( pAddr );
        Gmm_HoldBufferFree();                                                   /* ������buffer�����е���Ϣ�ͷ�             */
        return;
    }

    switch(pRrRelInd->ulRelCause)
    {
    case RRC_REL_CAUSE_RR_NORM_EVENT:
    case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
    case RRC_REL_CAUSE_T315_EXPIRED:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
        break;
    case RRC_REL_CAUSE_RR_UNSPEC:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_REL_CAUSE_RR_PRE_EMPT_REL:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_PRE_EMPTIVE_RELEASE;
        break;
    case RRC_REL_CAUSE_RR_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_REL_CAUSE_RR_RE_EST_REJ:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RE_ESTABLISH_REJ;
        break;
    case RRC_REL_CAUSE_RR_USER_INACT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_USER_INACTIVITY;
        break;
    case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:
        g_GmmGlobalCtrl.ucRelCause =
                 RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT;
        break;
    case RRC_REL_CAUSE_NAS_REL_ABSENT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_UNEXIST_CONNECTION;
        break;
    case RRC_REL_CAUSE_NAS_REL_SUCCESS:
    case RRC_REL_CAUSE_NAS_ABORT:
    case RRC_REL_CAUSE_NAS_STOP_SETUP:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_NORMAL;
        break;
    default:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: The Relase Cause is default");
        break;

    }

    g_GmmGlobalCtrl.ucCipherStartFlg = GMM_FALSE;

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;         /* 2G���������ӱ�־ʼ����Ч */
        }
        else
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;        /* 3G���������ӱ�־��� */
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucTcPreSta)
        {
            g_GmmGlobalCtrl.ucTcPreSta = GMM_REGISTERED_NORMAL_SERVICE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucServPreSta = GMM_NULL;
        }
        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucTcPreSta)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
            Gmm_TimerPauseForTc(GMM_TIMER_T3312);                               /* ����T3312                                */
        }
        return;
    }

    if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
        &&(GMM_MSG_HOLD_FOR_SMS == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)) )
    {   /* ��ǰ�л���� SMS ��Ϣ,�ҵ�ǰ������������,���𻺴��SMS���� */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: Buffered SMS Request will be handled.");
    }
    else
    {
        if (!((GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            && (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)))
        {

            if (GMM_MSG_HOLD_FOR_SMS
                ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
            {
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL_PTR;

                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }


            /* GCF34.4.8.1���Բ�ͨ����������G�·�����ʱ���յ�T3314��ʱ���˴�֪ͨSMS�ͷ� */
            if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType() )
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                      /* ����PMMSMS_ERROR_IND                     */
            }

        }
    }

    /* GMM�յ������������ͷ�ָʾ��RABMҲһ�����յ������������ͷ�ָʾ��RABM
       �յ��ͷ�ָʾ�����ֹ��ǰ��RAB�ؽ����̣���ʱGMM��û�б�Ҫ��������RABM��
       �ؽ���Ϣ��;��ʱWRR����û���ؽ�RB,��ҪGMM֪ͨRABM ����ʧ��*/
    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);               /* ������buffer�����е���Ϣ�ͷ�             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL_PTR;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }
    if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        &&(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProcHold))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 2G���������ӱ�־ʼ����Ч */
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;                                /* 3G���������ӱ�־��� */
        /* W�����RRC����״̬ */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        if (RRC_RRC_CONN_STATUS_ABSENT == pRrRelInd->ulRrcConnStatus)
        {
            NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
        }
    }

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");

    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        if (VOS_TRUE == NAS_GMM_ProcSavedWasSysInfo())
        {
            NAS_GMM_FreeWasSysInfo();
            return;
        }
    }
    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_RegInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_DeregInit(pRrRelInd);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmRelInd_RauInit(pRrRelInd);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmRelInd_ServReqInit(pRrRelInd);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvRrmmRelInd_RegNmlServ(pRrRelInd);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmRelInd_RegImsiDtchInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmRelInd_DeregNmlServ();
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvRrmmRelInd_PlmnSearch();
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmRelInd:WARNING: g_GmmGlobalCtrl.ucState is WRong");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        break;
    }

    /* W�£���·�ͷź����GMM��·���Ʊ��� */
    if (VOS_FALSE == GMM_IsCasGsmMode())
    {
        NAS_GMM_ClearGmmLinkCtrlStru();
    }

    /* �������ͷź�����������PS DETACH��Ϣ,����PS detach */
    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* ��������Ϣ�ַ�                           */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ��������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();
    return;
}
VOS_VOID Gmm_RcvRrmmRelInd_DeregNmlServ(VOS_VOID)
{

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����Ϊpower off����                  */
        Gmm_TimerStop(GMM_TIMER_1S);                                            /* ͣ5s����Timer                            */

        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }

        if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_GMM_SndMmGprsDetachComplete();
        }

        Gmm_ComStaChg(GMM_NULL);
        Gmm_SndMmcPowerOffCnf();                                                /* ����MMCGMM_POWER_OFF_CNF                 */
        /*Gmm_TimerDistroy();*/                                                     /* ��������Timer                            */
        Gmm_ComVariantInit();                                                   /* ���ȫ�ֱ���                             */
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSIM���γ���detach����          */
        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        Gmm_TimerStop(GMM_TIMER_1S);                                            /* ͣ5s����Timer                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregNmlServ:INFO: specific procedure ended");
    }

}


VOS_VOID Gmm_RcvRrmmRelInd_RegInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    /* ����Ƿ���Ҫ���·���Attach ����*/
    ucRst = NAS_GMM_RetryAttachProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Attach���� */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���attach���� */
            g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    g_GmmAttachCtrl.ucRetryFlg = GMM_TRUE;                                      /* ���û�С��������attach��־               */


    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                        /* ����attach attempt counter�Ĵ���         */


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                         /* ������ڽ��е�specific���̱�־           */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegInit:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* ���fallowon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvRrmmRelInd_DeregInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    if (VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ����Ƿ���Ҫ���·���Detach ���� */
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Detach���� */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���Detach���� */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /*���յ���Detach Accept��Ϣ��֮ǰδע��ɹ�*/
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregInit:INFO: specific procedure ended");

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvRrmmRelInd_RauInit(
                               RRMM_REL_IND_STRU *pRrRelInd                     /* RRMM_REL_IND_STRU����ָ��                */
                               )
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {
        return;
    }

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* ����Ƿ���Ҫ���·���RAU ����*/
    ucRst = NAS_GMM_RetryRauProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���RAU���� */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���RAU���� */
            g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /* RAU�������յ�SM���󣬱����棬���RAUʧ�ܣ��жϵ�ǰ�Ƿ���SM�������������SM����REL��Ϣ */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_MSG_HOLD_FOR_SM ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause) ))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RauInit(): RAU fail, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    g_GmmRauCtrl.ucRetryFlg = GMM_TRUE;                                     /* ���û�С����Ҫ����RAU��־                */
    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);         /* ����RAU attempt counter�Ĵ���            */


    /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}
VOS_VOID Gmm_RcvRrmmRelInd_ServReqInit(
                                   RRMM_REL_IND_STRU *pRrRelInd
                                   )
{
    VOS_UINT8                           ucRst;
    NAS_MSG_STRU                       *pServiceReqMsg;
    VOS_UINT8                           ucDellRejectEnableFlg;
    VOS_UINT32                          ulIsTestCardFlg;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* ��ȡ���ű��ܶ����Ƿ�ʹ�� */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    Gmm_TimerStop(GMM_TIMER_T3317);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* ����Ƿ���Ҫ���·���SR����*/
    ucRst = NAS_GMM_RetrySrProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���SR���� */
            pServiceReqMsg = Gmm_ServiceRequestMsgMake();

            if (VOS_NULL_PTR != pServiceReqMsg)
            {
                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause,
                                  GMM_RRC_IDNNS_UNKNOWN,
                                  pServiceReqMsg);

                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

                /* ��ʱPS���������Ѿ��ͷ�,��˹���Ӧ����idle̬��������ҵ������ */
                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ��,����g_GmmGlobalCtrl.MsgHold�еĻ��棬
                ���·���SR���� */
            Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */
            g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_TRUE;

        }
        return;
    }

    if (((RRC_REL_CAUSE_RR_NORM_EVENT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_RR_USER_INACT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_T315_EXPIRED        == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_NO_RF               == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        Gmm_SndSmRelInd();
    }

    if (VOS_TRUE == ucDellRejectEnableFlg)
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* ����״̬�Ĺ�������                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                         /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* ��MMC����service request��� */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* �¼��ϱ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID *)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

    Gmm_ComCnfHandle();

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* ��T3312                                  */
        }
    }
    else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }
    }
    else
    {
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* Directed signalling connection           *
                                                                                 * re-establishment                         */
    }
    else
    {                                                                           /* ����ԭ��                                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_ServReqInit:INFO: specific procedure ended");
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvRrmmRelInd_RegNmlServ(
                                  RRMM_REL_IND_STRU *pRrRelInd                  /* ��Ϣָ��                                 */
                                  )
{
    VOS_UINT32                          ulIsTestCardFlg;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* ����ע������У��յ�SM�ļ�������ע��ɹ���������ԭ��·�Ͻ��������󷢸�
        ���࣬��·���ͷţ���ʱ��Ҫ֪ͨSM��·�ͷ���Ϣ,�����·��� */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_NO_RF             == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (GMM_MSG_HOLD_FOR_SM
            != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SM)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RegNmlServ(): Connection release, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* ���RRC�ͷ�ԭ��ΪDirected signalling con
                                                                                 * nection re-establishment                 */
        /* ������״̬�£�ֻ�п����л����SR��Ϣ�����Դ˴�ֻ��Ҫ���SR */
        if(GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStart(GMM_TIMER_T3312);

        return;
    }
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);                                            /* ��T3312                                  */

    if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauSuccessInterSys();
    }

    if(GMM_FALSE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        /* ��ǰREL����Ҫ����RAU�����Դ���������� */
        NAS_GMM_HandleDelayedEvent();
    }

    return;
}


VOS_VOID Gmm_RcvRrmmRelInd_RegImsiDtchInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;
    VOS_UINT8                           ucRst;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ����Ƿ���Ҫ���·���Detach ����*/
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC��·���ڣ�ֱ�����·���Detach���� */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* ��¼��־λ�����յ�ϵͳ��Ϣ�����·���Detach���� */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* ����״̬�Ĺ�������                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* ���������                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegImsiDtchInit:INFO: specific procedure ended");

}
VOS_VOID Gmm_RcvRrmmRelInd_PlmnSearch()
{
    Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
}


VOS_VOID Gmm_RcvCoverLost_RegInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* ��Ҫ�ϱ���SM                             */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_RRC_EST_FAIL);        /* ֪ͨSM GMMע��ʧ��                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* ��ucSmCnfFlg��־                         */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* �����־                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvCoverLost_DeregInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if ( VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* ���������                               */

    /* detach��Ǵ��ڶ���ʱֱ�ӻظ�detach��� */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    return;                                                                     /* ����                                     */
}


VOS_VOID NAS_GMM_ProcRauHoldProcedure_RcvCoverLost(VOS_VOID)
{

    /* MMC�ڷ���Coverage lost�����д���Detach��Attach��� */
    switch (g_GmmGlobalCtrl.ucSpecProcHold)
    {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;

        case GMM_DETACH_COMBINED:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                NAS_GMM_SndMmGprsDetachComplete();
            }
            break;

        case GMM_DETACH_WITH_IMSI:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        default:
            break;
    }

    g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                                 /* ���followon��־                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* ������ڽ��е�specific���̱�־           */

    return;
}
VOS_VOID Gmm_RcvCoverLost_RauInit()
{
    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    pstLastSuccRai      = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stRai.Lai.PlmnId);
    stRai.Lai.aucLac[0] = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1] = pstLastSuccRai->stLai.aucLac[1];
    stRai.ucRac         = pstLastSuccRai->ucRac;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    g_GmmRauCtrl.ucRauAttmptCnt++;                                              /* RAU Attempt Counter��1                   */

    if (5 > g_GmmRauCtrl.ucRauAttmptCnt)
    {                                                                           /* ucRauAttmptCntС��5                      */
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ((GMM_TRUE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
         && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
        {                                                                       /* RAI����Ҹ���״̬��GU1                   */
        }
        else
        {                                                                       /* RAI����Ȼ��߸���״̬����GU1             */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }
        Gmm_TimerStart(GMM_TIMER_T3311);
    }
    else
    {                                                                           /* ucRauAttmptCnt���ڵ���5                  */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* �ø���״̬ΪGU2                          */

        /* ��U2״̬�����浱ǰ��RAI��Ϣ */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;                             /* ���̽��������3312�����־               */
        g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */

        if (VOS_TRUE == NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax())
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }

        Gmm_TimerStart(GMM_TIMER_T3302);

    }



    NAS_GMM_ProcRauHoldProcedure_RcvCoverLost();

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_BufferMsgDump();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}


VOS_VOID Gmm_RcvCoverLost_ServReqInit()
{
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSR_DATA                        */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucServPreSta)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucServPreSta))
    {                                                                           /* ״̬��GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
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

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvCoverLost_RegNmlServ()
{
    if ((GMM_TRUE == GMM_IsCasGsmMode())
     || (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        return;
    }
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);

    return;
}


VOS_VOID Gmm_RcvCoverLost_RegImsiDtchInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* ���ڱ������T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* �ָ�T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* ���ڱ������T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* �ָ�T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* ��T3312                                  */
    }

    return;
}


VOS_VOID Gmm_RcvCoverLost_SuspendWaitForSys()
{
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmRauCtrl.ucNpduCnt = 0x0;
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }
    else
    {
#if 0
        GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                       GMM_RABM_IMMEDIATELY_RAU);
#endif

        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }

    GMM_BufferMsgDump();
}


VOS_VOID Gmm_RcvSmDataReq(
                      VOS_VOID       *pMsg                                          /* ָ��ԭ���ָ��                           */
                      )
{
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {/* ��ǰPS��������ޣ��ظ�SMʧ�� */
        GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        return;
    }

    NAS_GMM_ClearBufferedSmDataReq();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬���в�ͬ����                     */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM_DEREGISTERED_INITIATED״̬           */
        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        NAS_GMM_ProcSmDataReq_RAUInit(pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:

        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {
            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg); /* ���� RRMM_DATA_REQ                       */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
                Gmm_BufSmDataReqMsg(pMsg);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
            Gmm_BufSmDataReqMsg(pMsg);
        }
        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
        Gmm_BufSmDataReqMsg(pMsg);

        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PDPACT);

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PDPACT;
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
        }
        else if (g_GmmGlobalCtrl.SysInfo.ucForbMask != MMCGMM_GSM_NO_FORBIDDEN)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_FORBID_LA);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
        {
            /* �������������´��� */
            Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        }
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;                                                                     /* ����                                     */
}



VOS_VOID NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }

    /* �ڴ�G�л���Wʱ,��Ҫ���ȷ���RAU�ָ�PS,Ȼ�������SM��Ϣ */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        Gmm_BufSmDataReqMsg(pMsg);

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* �����ϵͳ��Ϣ��ʱ�������У����·�RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_BufferSmDataReq
  Function : ����SM������DATA_REQ��Ϣ
  Input    : VOS_VOID       *pMsg   ָ��ԭ���ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2010.01.07  �¹�����
*******************************************************************************/
VOS_VOID Gmm_BufferSmDataReq(VOS_VOID       *pMsg)
{
    GMMSM_DATA_REQ_STRU      *pGmmSmDataReq;                                         /* GMMSM_DATA_REQ_STRU����ָ��              */
    GMMSM_DATA_REQ_STRU      *ptr;

    pGmmSmDataReq = (GMMSM_DATA_REQ_STRU *)pMsg;

    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq_DeregInit:WARNING: VOS_NULL_PTR pointer in Gmm_RcvSmDataReq_DeregInit");
          return;
    }
    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4));
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;               /* ����SM��Ϣ                               */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk  |= GMM_MSG_HOLD_FOR_SM;           /* ��SM��Ϣ�����־                         */

    return;
}
VOS_VOID Gmm_RcvCmServReq_RegAtmpToUpdt(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    GMM_LOG_INFO("Gmm_RcvSmDataReq_RegAtmpToUpdt.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH״̬�£���ǰ�汾��֧��SMS������PS�������� */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }
    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_DATA_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* ֹͣTimer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* ֹͣTimer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*����RAU����*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        /*����SM��Ϣ*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ulEstCause = ((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause;
        return;
    }

    GMM_SndSmServiceRej(GMM_SM_CAUSE_PS_DETACH);
    return;
}


VOS_VOID Gmm_RcvCmServReq_DeregAtmpToAtch(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;


    GMM_LOG_INFO("Gmm_RcvCmServReq_DeregAtmpToAtch.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH״̬�£���ǰ�汾��֧��SMS������PS�������� */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }

    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
        MS is in substate ATTEMPTING-TO-ATTACH and
            - expiry of timer T3302;
            - a new routing area is entered; or
            - an attach is triggered by CM sublayer requests.
        */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        /* �ø�SM��EST_CNF��־ΪTRUE */
        g_GmmAttachCtrl.ucSmCnfFlg        = GMM_TRUE;

        /* ����follow on ��־ */
        g_GmmGlobalCtrl.ucFollowOnFlg     = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        /* ֹͣTimer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* ֹͣTimer3311 */
        Gmm_TimerStop(GMM_TIMER_T3311);

        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);

        /*����ATTACH����*/
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        return;
    }

    Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);

    return;
}
VOS_UINT8 NAS_GMM_GetGmmSmDataReqMsgType(NAS_MSG_STRU *pstMsg)
{
    VOS_UINT8                           ucMsgType;

    if (0x70 == (pstMsg->aucNasMsg[0] & 0x70))
    {
        /* ������չTIʱ,��Ϣ����ȡ��aucNasMsg[2] */
        ucMsgType  = pstMsg->aucNasMsg[2];
    }
    else
    {
        /* ��ȡ��Ϣ����ȡ��aucNasMsg[1] */
        ucMsgType  = pstMsg->aucNasMsg[1];
    }

    return ucMsgType;

}


VOS_UINT8 NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32                      enMsgType
)
{
    if ((SM_STATUS == enMsgType)
     || (SM_MOD_PDP_CONTEXT_ACC_M2N == enMsgType)
     || (SM_DEACT_PDP_CONTEXT_ACC == enMsgType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}




VOS_VOID Gmm_RcvSmDataReq_RegNmlServ(
                                 VOS_VOID       *pMsg                           /* ָ��ԭ���ָ��                           */
)
{
    NAS_MSG_STRU                       *pNasMsg;                                /* ����ָ��                                 */
    VOS_UINT32                          ulEstCause;                             /* RRC���ӽ���ԭ��                          */
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32  ucMsgType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT8                           ucIsUtranSmcNeeded;

    ucIsUtranSmcNeeded = NAS_UTRANCTRL_IsUtranPsSmcNeeded();

    enCurRat  = NAS_MML_GetCurrNetRatType();
    pNasMsg   = VOS_NULL_PTR;                                                     /* ��ʼ��ָ��                               */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        Gmm_BufferSmDataReq(pMsg);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && (!((NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender !=
                                    enCurRat))))
    {                                                                           /* ��ǰ����������                           */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            /* RESUME FAIL ��Ҫ��RAUʱ���Ȼ���SM����Ϣ��RAU���ٽ��д���*/
            if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
            {
                Gmm_BufSmDataReqMsg(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */
            }
        }


        /* FDD/TDD�յ������Ա�������TDD�²���Ҫ�����Ա�����Ҳ���Է���ҵ�� */
        else if ( ( (VOS_TRUE                              == ucIsUtranSmcNeeded)
                  && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
               || ( (NAS_MML_NET_RAT_TYPE_WCDMA            == enCurRat)
                 && (VOS_FALSE                             == ucIsUtranSmcNeeded) ) )

        {
            /*�ж�T3340 �Ƿ����� */
            if ((VOS_FALSE == NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(ucMsgType))
             && (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG)))
            {
                Gmm_BufferSmDataReq(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */
            }
        }
        else
        {
            /*�����Ա���δ�򿪣��軺��SM��Ϣ��
              ͨ��service request���Դ������Ա���
              ��GMM_SERVICE_REQUEST_INITIATED״̬��,
              �յ�RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_RCV)��Ϣ���������Ա�����־λ
              �յ�RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_CMPL)��Ϣ���������SM��Ϣ*/
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* �洢��ǰ������                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

            Gmm_BufSmDataReqMsg(pMsg);
            /*Service request*/
            pNasMsg = Gmm_ServiceRequestMsgMake();                          /* ����make����                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

            Gmm_TimerStop(GMM_TIMER_T3340);
        }
    }
    else if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        GMM_LOG_INFO("Gmm_RcvSmDataReq_RegNmlServ:Inter System change, Exec select RAU.");

        /*GMM_BufferMsgReceive(pMsg);*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    /* �����ǰGMM�ڽ����ӵĹ���������RAI�ı������Ҫ���ͷ����ڽ��������ӣ�
       ��ô�����ڵȴ������������ͷ�ָʾ�Լ������ͷ�ָʾ֮���ϱ���ϵͳ��Ϣ
       �������յ����ϲ�������Ҫ����*/
    else if ((GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
          || (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause))
    {
        if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }
        Gmm_BufSmDataReqMsg(pMsg);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        /* RESUME ��Ҫ��RAUʱ���Ȼ���SM����Ϣ��RAU���ٽ��д���*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            Gmm_BufSmDataReqMsg(pMsg);
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* ���� RRMM_DATA_REQ                       */

            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        }
    }
    else
    {                                                                           /* ��ǰû����������                         */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* Timer3302��������                        */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* ����Timer3302                            */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* Timer3311��������                        */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* ����Timer3311                            */
        }
        else
        {
        }
        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* �洢��ǰ������                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

        /*����SM��Ϣ*/
        Gmm_BufSmDataReqMsg(pMsg);

        pNasMsg = Gmm_ServiceRequestMsgMake();                                  /* ����service request��������              */

        switch (((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause)
        {                                                                       /* ת��ԭ��ֵ                               */
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ():INFO: The RRC Connection Setup Cause is GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL");
            ulEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
        }

        g_GmmGlobalCtrl.ulEstCause = ulEstCause;
        Gmm_SndRrmmEstReq(ulEstCause, GMM_RRC_IDNNS_UNKNOWN, pNasMsg);          /* ����service request(signalling)          */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REQ,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_RegInit(
                                  VOS_VOID    *pMsg,                                /* ��Ϣָ��                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ��ʼ��ָ��                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);       /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LAû��,������A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH��������SM������                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* ֪ͨSM GMMע��ʧ��                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* ��ucSmCnfFlg��־                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (VOS_TRUE == g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg))
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* ���GMM���ܽ���RAUʱ����Ҫ����MM��LU���� */
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregInit(
                                    VOS_VOID    *pMsg,                              /* ��Ϣָ��                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI�仯��־                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length�仯��־                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI�仯��־                              */
                                    )
{
    VOS_UINT8                           ucDetachType;
    MMCGMM_SYS_INFO_IND_STRU            *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ��ʼ��ָ��                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();

            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if (((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    {                                                                           /* RA�ı����DRX�ı�                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        ucDetachType = NAS_GMM_GetDetachTypeFromProcName(g_GmmDetachCtrl.ucDetachProc);
        if (GMM_INVALID_DETACH_TYPE != ucDetachType)
        {
            Gmm_MsInitNormalDetach(ucDetachType);
        }
    }
    else
    {
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RauInit(
                                  VOS_VOID    *pMsg,                                /* ��Ϣָ��                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        /* ��ǰפ����λ������֮ǰפ����λ����LAIû�ı�,����������ģʽI,����T3312��ʱ */
        if ((GMM_FALSE == ucLaiChgFlg)
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                        /* ֪ͨMM����LU                             */
            }
            else
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RauInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_RauInit(): call Gmm_ComCnfHandle to clear msg buffer");

        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
             == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        ||(VOS_TRUE == g_GmmRauCtrl.ucRetryRauForRelCtrlFlg))
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* ����״̬��ΪGU2                          */
        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* ���̽���֮�����RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* ���GMM���ܽ���RAUʱҪ����MM��LU����     */
    }
    else
    {
    }

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_ServReqInit(
                                      VOS_VOID    *pMsg,                            /* ��Ϣָ��                                 */
                                      VOS_UINT8   ucRaiChgFlg,                      /* RAI�仯��־                              */
                                      VOS_UINT8   ucDrxLengthChgFlg,                /* DRX length�仯��־                       */
                                      VOS_UINT8   ucLaiChgFlg                       /* LAI�仯��־                              */
                                      )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_ComCnfHandle();
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �嵱ǰ����                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_ServReqInit:INFO: specific procedure ended");
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA�ı����DRX�ı�                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* ���ԭ��ȴ���־                         */
        }

        if (GMM_TRUE == ucRaiChgFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* �������жϵ�SR����                       */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregNmlServ(
                                       VOS_VOID    *pMsg,                           /* ��Ϣָ��                                 */
                                       VOS_UINT8   ucLaiChgFlg                      /* LAI�仯��־                              */
                                       )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        /* BEGIN: Added by liurui id:40632, 2006/4/5   PN:A32D02352 */
        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
        /* END:   Added by liurui id:40632, 2006/4/5   PN:A32D02352 */

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* ����״̬�Ĺ�������                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        /* ��ʱ�����л����SMע��������Ϣ */
        GMM_BufferMsgResume();
        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* ǰһ��С��Ҳ��֧��GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (VOS_TRUE == pSysInfo->ulUserSrchFlg)
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);
    }
    else
    {                                                                           /* С���ı�                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(
                                          VOS_VOID    *pMsg,                        /* ��Ϣָ��                                 */
                                          VOS_UINT8   ucRaiChgFlg,                  /* RAI�仯��־                              */
                                          VOS_UINT8   ucDrxLengthChgFlg,            /* DRX length�仯��־                       */
                                          VOS_UINT8   ucLaiChgFlg                   /* LAI�仯��־                              */
                                          )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if ((GMM_TRUE == ucRaiChgFlg)
        &&  (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask))
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter��0                */
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }

    else if ( (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
           && (GMM_FALSE == ucRaiChgFlg)
           && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */


        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter��0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ����Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* ��С����Ҫ����attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* ����Attach                               */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }
        else
        {
            /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������һ���жϣ�UE��һֱ����ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
            else
            {


                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();
                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }
        }
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNmlServ(
                                     VOS_VOID    *pMsg,                             /* ��Ϣָ��                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI�仯��־                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length�仯��־                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI�仯��־                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������ʱ���Ƿ�Ϊ0���жϣ�UE��һֱ����ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* ��·�ͷź���Ҫ���·���Service Request���� */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }


    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* ����RAU����                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* ����RAU����                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311��������ʱ�ŷ���RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            /* <==A32D12438 */
            /*
            ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
            GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
            ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
            ��Ҫ��ǰ�汻�жϵ����̽�����
            */
            else if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                Gmm_RoutingAreaUpdateHandleFollowOn();
            }
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W������ݲ�֧�������½��յ�Ѱ��*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
    }

    /* GMM_REGISTERED_PLMN_SEARCH״̬������ȡ��һ���������� */

    else
    {
        /*
        ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
        GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
        ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
        ��Ҫ��ǰ�汻�жϵ����̽�����
        */

        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            if (VOS_FALSE == ucCsRestrictionFlg)
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }
            else
            {
                NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                   /* ����MMCGMM_GMM_ACTION_RESULT_IND��MMC    */

            }
        }


        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        /* ԭ��T3312��ʱ����suspend wait for sysinfo״̬�����,��ΪL handover to W,
           ״̬Ǩ����register normal service״̬,������Ҫ�ڴ�״̬�´���T3312��ʱ */
        if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
        }
    }
    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;                                                                     /* ����                                     */
}
VOS_VOID NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(
                                     VOS_VOID    *pMsg,                             /* ��Ϣָ��                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI�仯��־                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length�仯��־                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI�仯��־                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_TRUE == ucRaiChgFlg)
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* ����ATTEMPT TO UPDATE����REGISTERED_NO_CELL_AVAILABLE״̬����
               �������յ�ϵͳ��Ϣ����Ҫ���ATTEMPT COUNTER */
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* �����������T3302��ʱ��ʱ��Ϊ0ʱ������T3302��ʱ��������������ʱ���Ƿ�Ϊ0���жϣ�UE��һֱ����ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
    {
        NAS_GMM_IsrActiveRaiNoChg_InterSys();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* ��·�ͷź���Ҫ���·���Service Request���� */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }


    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* ����RAU����                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CSͨ���е�normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* ����RAU����                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311��������ʱ�ŷ���RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
            /* <==A32D12438 */
            /*
            ��Rau��Sr��Detach���̽����������ӵ�ʱ����RAI�ı䣬��ʱ״̬Ǩ�Ƶ�
            GMM_REGISTERED_NORMAL_SERVICE���ȴ��ײ��ͷ����ӣ����ϱ�ϵͳ��Ϣ��
            ����ϱ���ϵͳ��Ϣ��ʾ�ֻص������С������ô��ʱ���ᷢ��Rau������
            ��Ҫ��ǰ�汻�жϵ����̽�����
            */
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W������ݲ�֧�������½��յ�Ѱ��*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }
    else
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

        /* T3311δ��ʱ���������̴��� */
        else if (GMM_FALSE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                if (GMM_FALSE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;


                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }



                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                        Gmm_RoutingAreaUpdateHandleFollowOn();
                    }
                }
            }
            else if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                /*
                3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
                reset when the MS is in substate ATTEMPTING-TO-UPDATE and
                    - a new routing area is entered;
                    - expiry of timer T3302; or
                    - at request from registration function.
                */
                g_GmmRauCtrl.ucRauAttmptCnt = 0;

                /* ֹͣTimer3302 */
                Gmm_TimerStop(GMM_TIMER_T3302);

                /* ֹͣTimer3311*/
                Gmm_TimerStop(GMM_TIMER_T3311);

                /* ����RAU���� */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                if ((GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
                 || (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG)))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }

            }

            if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
            {
                /*W������ݲ�֧�������½��յ�Ѱ��*/
            }
            else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
            {
                Gmm_DealWithBuffAfterProc();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
        /* T3311��ʱ��REGISTERED_PLMN_SRCH״̬��Ҫ����RAU */
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_RegUpdtNeed(
                                        VOS_VOID    *pMsg,                          /* ��Ϣָ��                                 */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI�仯��־                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                    ucCsRestrictionFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (VOS_TRUE == pSysInfo->ulUserSrchFlg)
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else
    {                                                                           /* С���ı�                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
        {
            ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

            if (!((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)))
            {                                                                   /* ��A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                  || (VOS_TRUE == ucCsRestrictionFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
            }
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
        }

    }

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(
                                        VOS_VOID    *pMsg,                          /* ��Ϣָ��                                 */
                                        VOS_UINT8   ucRaiChgFlg,                    /* RAI�仯��־                              */
                                        VOS_UINT8   ucDrxLengthChgFlg,              /* DRX length�仯��־                       */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI�仯��־                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }

    else if ( (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
           && (GMM_FALSE == ucRaiChgFlg)
           && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        /* �û������ָ��������ǿ�Ʒ���ע�� */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı�                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX�ı�                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ����RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* ��С����Ҫ����RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* ͣT3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNoCell(
                                    VOS_VOID    *pMsg,                              /* ��Ϣָ��                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI�仯��־                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length�仯��־                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI�仯��־                              */
                                    )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictionFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucSimCsRegStatus        = NAS_MML_GetSimCsRegStatus();

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* ǿ������ת��                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* ֪ͨMM����LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
           || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
#if (FEATURE_ON == FEATURE_LTE)
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
           && (NAS_MML_TIN_TYPE_GUTI != enTinType))
#else
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg))
#endif
    {                                                                           /* �ص�ԭ����RA����DRX����û�иı�          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* ��������ʱT3312δ���                    */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED
                == NAS_MML_GetPsUpdateStatus())
            {                                                                   /* ����״̬��GU1                            */

                /* T3311��ʱ��REGISTERED_PLMN_SRCH״̬��Ҫ����RAU */
                if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* ���ü����̱�־                           */

                    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
                     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
                     || (VOS_TRUE == ucCsRestrictionFlg))
                    {                                                               /* ��A+I                                    */
                        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }

                        /* ���֮ǰ����������T3312��ʱ��������T3323,���ؽ�����������ҪֹͣT3323*/
                        Gmm_TimerStop(GMM_TIMER_T3323);
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* ����T3312                                */
                        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                        /* ��MMC����PSע���� */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                                     NAS_MML_REG_FAIL_CAUSE_NULL);

                        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                    }
                    else
                    {                                                               /* A+I                                      */
                        if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
                        {                                                           /* ����״̬��U1,����Gs�����Ѵ���            */
                            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                            {
                                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                            }
#endif
                            Gmm_TimerStart(GMM_TIMER_T3312);                        /* ����T3312                                */
                            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                            {                                                       /* ��Ҫ��SM��EST_CNF                        */
                                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM�ؽ����ɹ�����Ӧ                     */
                            }


                            /* ��MMC����PSע���� */
                            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                            if (VOS_TRUE == ucCsAttachAllow)
                            {                                                       /* CS������ע��                             */
                                NAS_GMM_SndMmCombinedRauInitiation();
                                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                               NAS_MML_REG_FAIL_CAUSE_NULL,
                                                               VOS_NULL_PTR,
                                                               VOS_NULL_PTR);                                      /* ���� MMCGMM_COMBINED_RAU_ACCEPTED        */

                                /*����RAU������ */
                                if(5<=g_GmmRauCtrl.ucRauAttmptCnt)
                                {
                                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                                }
                            }
                            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                        }
                        else
                        {                                                           /* ����״̬����U1,����Gs�����Ѿ��Ƴ�                           */
                            if ((VOS_TRUE != ucSimCsRegStatus)
                             || (VOS_FALSE == ucCsAttachAllow))
                            {                                                       /* sim��Ч����CS������ע��                */
                                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* ����״̬�Ĺ�������                       */
#if (FEATURE_LTE == FEATURE_ON)
                                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                                {
                                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                                }
#endif
                                Gmm_TimerStart(GMM_TIMER_T3312);                    /* ����T3312                                */
                                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                                {                                                   /* ��Ҫ��SM��EST_CNF                        */
                                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* ��SM�ؽ����ɹ�����Ӧ                     */
                                }
                                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                                /* ��MMC����PSע���� */
                                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* ���������̱�־                           */
                            }
                            else
                            {
                                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_UPDATING_TYPE_INVALID);                     /* ����RAU                                  */
                            }
                        }
                    }
                }
            }
            else
            {                                                                   /* ����״̬����GU1                          */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* ����RAU                                  */
            }

            if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            {
                if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                }
                if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    Gmm_DealWithBuffAfterProc();
                    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
                }
            }
        }
        else
        {                                                                       /* ��������ʱT3312���                      */
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* �������������־                         */
            if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
             || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* ��A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (VOS_TRUE == ucCsRestrictionFlg)
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {/* A+I ģʽ����CS�� BAR, ���� ��ǰ CS ͨ���� */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
            }
        }
    }
    else
    {                                                                           /* RA�ı����DRX�����仯                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* ���T3312������                        */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* ��A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU����                              */
        }
    }

    return;                                                                     /* ����                                     */
}



VOS_VOID Gmm_RcvMmcSysInfoInd_SuspWaitSys(VOS_VOID* pRcvMsg,VOS_UINT8 ucRaiChgFlg,VOS_UINT8 ucLaiChgFlg)
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* ����ָ��                                 */
    VOS_VOID                           *pAddr;
    VOS_UINT8                           ucCsAttachAllow;

    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                           ucCsRestrictFlg;
    GMM_RAI_STRU                        stRai;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();

    pstConnStatus             = NAS_MML_GetConnStatus();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                             /* ǿ������ת��                             */

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* ��дLAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* ��дPLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    /*add,sunxibo,2007-09-24,for intersystem begin*/
    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* ԭ��SIM��Ч                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */

        /* BEGIN: Added by liurui id:40632, 2006/4/5   PN:A32D02352 */
        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
        /* END:   Added by liurui id:40632, 2006/4/5   PN:A32D02352 */

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* �������������־                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }
    /*add,sunxibo,2007-09-24,for intersystem end*/

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* ��֧��GPRS                               */
        GMM_LOG_INFO("Gmm_RcvMmcSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* ͣ����Timer                              */

        /*��ϵͳ�ı�ʱ֪ͨRABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            }
        }

        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LAû��                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* ֪ͨMM����LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* ��forbidden�б���                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */


        /*��ϵͳ�ı�ʱ֪ͨRABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* ���öԽ�ֹ�б�Ĳ���                     */
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {/* �µ�RA,��������ģʽ��� */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        /*add for sys chng begin*/
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        /*add for sys chng end*/
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter��0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;

        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else                                                                        /* RA ��ͬ */
    {
        /* reference to 23.401 10.5.1.3 L->GU handoverʱ,RAI���ı䲻��Ҫ����RAU; TINָʾΪGUTIʱ��Ҫ����RAU */






        if ((((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
           || (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
          && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
#if (FEATURE_ON == FEATURE_LTE)
         || (NAS_MML_TIN_TYPE_GUTI == enTinType)
#endif
         )

        {

            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* ͣT3302                                  */
            /*add for sys chng begin*/
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            /*add for sys chng end*/
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter��0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU                                  */

        }
        else if (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
        {
            /*��ϵͳ�ı�ʱ֪ͨRABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W,G�²�֧��GPRS,��W�º�,���RAI���ı�,���µ�����GMM_REGISTERED_UPDATE_NEEDED
               ״̬�½��յ�ϵͳ��Ϣ�Ĵ�����. */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState)
             || (GMM_ROUTING_AREA_UPDATING_INITIATED== gstGmmSuspendCtrl.ucPreState))
            {
                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);
            }
#if (FEATURE_ON == FEATURE_LTE)
                /* L��ѡ��G,·����δ�ı䣬ISR���������RAUʱ��Ҫ����״̬��
                  ����Ϊregister no cell available�������޷���ҵ�� */
            else if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
#endif
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
                }
                else
                {
                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    }
                    GMM_BufferMsgResume();
                }
            }
        }
        /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ���Ҫ��������ע�� */
        else if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ucCsAttachAllow)
              && (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
              && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
            /* NMO1��,��ͨ���ֻ�ģʽ�ж��Ƿ���Ҫ��������ע�� */
            if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
             && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

#endif
        else
        {
            /*��ϵͳ�ı�ʱ֪ͨRABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W, G�½����ֹ���߲�֧��GPRS����W�º����RAC���ı䣬���µ�����GMM_REGISTERED_UPDATE_NEEDED
               ״̬�µ�ϵͳ��Ϣ������ */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE == gstGmmSuspendCtrl.ucPreState))
            {

                if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
                }

                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);

                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

            }
            else
            {
                /* ������ģʽI�£�Gs�ڲ�����,���ҽ��벻����ʱ,��Ҫ�������ϵ�RAU�ؽ�Gs�� */
                /* PS access bar�Ѿ���Ԥ�������ж�,���Դ˴������ж�PS�����ֹ */
                if ((VOS_FALSE                            == Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai)))
                 && (VOS_TRUE                             == ucCsAttachAllow)
                 && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE                             == ucSimCsRegStatus)
                 && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_FALSE                            == ucCsRestrictFlg))
                {
                    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
                    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */

                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                    return;
                }

                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

#if (FEATURE_ON == FEATURE_LTE)
                /* L��ѡ��G,·����δ�ı䣬ISR���������RAUʱ��Ҫ����״̬��
                  ����Ϊregister no cell available�������޷���ҵ�� */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                 && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
                else
#endif
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    /* ��MMC����PSע���� */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                }


                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    switch (g_GmmGlobalCtrl.ucSpecProcHold)
                    {                                                               /* ������specific����                       */
                    case GMM_SERVICE_REQUEST_DATA_IDLE:
                    case GMM_SERVICE_REQUEST_DATA_CONN:
                        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* ����GMMRABM_REESTABLISH_CNF(fail)        */
                        break;
                    case GMM_SERVICE_REQUEST_SIGNALLING:
                        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
                        {
                            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);              /* ����PMMSMS_ERROR_IND                     */
                        }
                        if (GMM_MSG_HOLD_FOR_SM
                            ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                                    GMM_MSG_HOLD_FOR_SM))
                        {                                                           /* ����б�����SmDataReqԭ��                */
                            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_SuspWaitSys(): Clear cached SM data Req");

                            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &=
                                ~GMM_MSG_HOLD_FOR_SM;                               /* ���������־                             */
                            pAddr =
                                (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm; /* ��ȡSmDataReqԭ���ַ                    */
                            Gmm_MemFree(pAddr);                                     /* �ͷű����SM��Ϣ                         */
                        }
                        break;
                    default:
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:INFO: No Hold Procedure");
                        break;
                    }
                    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
                }
            }
        }
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_ComCmpLai
  Function : LAI�ıȽ�
  Input    : GMM_LAI_STRU   *pMsg       ָ��LAI��ָ��
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ��־��  2003.12.10  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_ComCmpLai(
                    GMM_LAI_STRU *pMsg                                          /* ָ��LAI��ָ��                            */
                    )
{
    VOS_UINT8 ucRet;                                                                /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ��ʼ��                                   */

    if (GMM_TRUE == Gmm_Com_CmpPlmnid(&pMsg->PlmnId))
    {                                                                           /* PLMN��ͬ                                 */
        if ((pMsg->aucLac[0]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0])
            &&(pMsg->aucLac[1]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1]))
        {                                                                       /* LAC��ͬ                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;                                                               /* ����                                     */
}
VOS_VOID NAS_GMM_RcvMmAuthenticationFailureInd(VOS_VOID)
{
    VOS_UINT8                           ucGmmPreState;
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
        case GMM_REGISTERED_INITIATED:
        case GMM_DEREGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NO_IMSI:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_UPDATE_NEEDED:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_REGISTERED_PLMN_SEARCH:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            Gmm_TimerStop(GMM_TIMER_ALL);                                           /* ͣ����Timer                              */
            g_GmmReqCnfMng.ucCnfMask = 0;                                           /* ���ԭ��ȴ���־                         */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                       /* ��Ҫ��SM����Ӧ                           */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_FAIL); /* ֪ͨSM GMMע��ʧ��                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
            }
            if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            {                                                                       /* SMS�ڵȴ���Ӧ                            */
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                          /* ����PMMSMS_ERROR_IND                     */
                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }
            if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                       /* ��Ҫ��RABM����Ӧ                         */
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ����GMMRABM_REESTABLISH_CNF(failure)     */
            }
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ����                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcAuthenticationFailureInd:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */

            Gmm_HoldBufferFree();                                                   /* ���������Ϣ                             */

            gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_IMSI;
            ucGmmPreState = g_GmmGlobalCtrl.ucState;
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* ����״̬�Ĺ�������                       */

            if (GMM_REGISTERED_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                                      NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }

            else if (GMM_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);                                /* ����״̬�Ĺ�������                       */
            }
            else if (GMM_SUSPENDED_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);                                /* ����״̬�Ĺ�������                       */
            }
            else
            {
            }

            /* �����ر�־ */
            NAS_GMM_ClearIMSIOfUeID();

            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* ����״̬����ΪGU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOC INFO                  */
            break;                                                                  /* ����                                     */

        case GMM_NULL:
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* ����״̬����ΪGU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* ���ú���ɾ��PS LOC INFO                  */

        default:                                                                    /* �������                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcAuthenticationFailureInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;                                                                  /* ����                                     */
    }
}
VOS_VOID NAS_GMM_RcvMmCsConnectInd(
    VOS_VOID                           *pstRcvMsg                               /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* ����ԭ������ָ��                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* ǿ������ת��                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {

    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        NAS_GMM_FreeGsmSysInfo();
    }
    else
    {
        NAS_GMM_ProcSavedGsmSysInfo();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        NAS_GMM_FreeWasSysInfo();
    }

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I     != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* �����û�ģʽA������ģʽI                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcCmServiceInd:NORMAL: It is not A+I(Gmm_RcvMmcCmServiceInd)");
        return;
    }

    if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
    {                                                                           /* ���CS����ͨ����                         */
        /* g_GmmRauCtrl.ucCsSpringRauFlg��ʶ�Ƿ�ΪCS������RAU��
           ֻ����CM SERVICE REJECTԭ��ֵΪ4ʱ��
           g_GmmRauCtrl.ucCsSpringRauFlg��ΪTRUE��
        */
        /*CSFB������RAU��#10�ܣ���Attach��״̬ΪGMM_ATTACH_NORMAL*/
        if( ( GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg )
            || ((VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
             || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))))
        {                                                                       /* CS����RAU                                */
             switch (g_GmmGlobalCtrl.ucState)
             {                                                                  /* ����״̬�ַ�                             */
             case GMM_REGISTERED_INITIATED:
             case GMM_ROUTING_AREA_UPDATING_INITIATED:
             case GMM_SERVICE_REQUEST_INITIATED:
                 NAS_GMM_RcvMmCsConnectInd_InProc(pstRcvMsg);                   /* ����RAU/SR�����еĴ���                   */
                 break;
             case GMM_REGISTERED_NORMAL_SERVICE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                 NAS_GMM_RcvMmCsConnectInd_RegNmlServ();                        /* ���ø�״̬�µĴ���                       */
                 break;
             default:
                 PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
                 break;
             }
             g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific ���̱�־          */
        }

        /*CSFB������RAU��#10�ܣ���Attach��״̬ΪGMM_ATTACH_NORMAL*/
        if (((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
          || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;           /* �����ǰ���е�specific ���̱�־          */
        }
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_Compare_Plmnid
  Function : �Ƚ�����PLMN ID �Ƿ���ͬ
  Input    : GMM_PLMN_ID_STRU *pPlmnId1
             GMM_PLMN_ID_STRU *pPlmnId2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE   ��ͬ
             GMM_FALSE  ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Plmnid(GMM_PLMN_ID_STRU *pPlmnId1,
                             GMM_PLMN_ID_STRU *pPlmnId2 )
{
    VOS_UINT8           i;                                                      /* ������ʱ����                             */

    for (i=0; i<3; i++)
    {                                                                           /* ��MCC�������ж�                          */
        if (pPlmnId1->aucMccDigit[i] != pPlmnId2->aucMccDigit[i])
        {                                                                       /* MCC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    if (pPlmnId1->ucMncCnt != pPlmnId2->ucMncCnt)
    {                                                                           /* MNC��������ͬ                            */
        return GMM_FALSE;                                                       /* ����GMM_FALSE                            */
    }

    for (i=0; i<pPlmnId1->ucMncCnt; i++)
    {                                                                           /* ��MNC�������ж�                          */
        if (pPlmnId1->aucMncDigit[i] != pPlmnId2->aucMncDigit[i])
        {                                                                       /* MNC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* ����GMM_TRUE                             */
}

/*******************************************************************************
  Module   : Gmm_Compare_Lai
  Function : LAI�ıȽ�
  Input    : GMM_LAI_STRU   *pLAI1
             GMM_LAI_STRU   *pLAI2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Lai(GMM_LAI_STRU *pLAI1,
                          GMM_LAI_STRU *pLAI2)
{
    VOS_UINT8 ucRet;                                                            /* ���巵��ֵ                               */

    ucRet = GMM_FALSE;                                                          /* ��ʼ��                                   */

    if (GMM_TRUE == Gmm_Compare_Plmnid(&pLAI1->PlmnId, &pLAI2->PlmnId))
    {                                                                           /* PLMN��ͬ                                 */
        if (  (pLAI1->aucLac[0] == pLAI2->aucLac[0])
            &&(pLAI1->aucLac[1] == pLAI2->aucLac[1]))
        {                                                                       /* LAC��ͬ                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Com_CmpRai
  Function : RAI�ıȽ�
  Input    : GMM_RAI_STRU   *pRAI1
             GMM_RAI_STRU   *pRAI2
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE    ��ͬ
             GMM_FALSE   ��ͬ
  History  :
    1. ŷ����  2009.02.12  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Rai(GMM_RAI_STRU  *pRAI1,
                          GMM_RAI_STRU  *pRAI2)
{
    VOS_UINT8 ucRet = GMM_FALSE;                                                /* ���巵��ֵ                               */

    if (GMM_TRUE == Gmm_Compare_Lai(&pRAI1->Lai, &pRAI2->Lai))
    {                                                                           /* LAIһ��                                  */
        if (pRAI1->ucRac == pRAI2->ucRac)
        {                                                                       /* RACһ��                                  */
            ucRet = GMM_TRUE;                                                   /* ������ֵ                                 */
        }
    }

    return ucRet;
}


 VOS_VOID Gmm_Get_Location_Change_info(
    GMM_RAI_STRU                       *pRai1,
    GMM_RAI_STRU                       *pRai2,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg,
    VOS_UINT8                           ucNetMod
)
{
    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;
    VOS_UINT32                          ulT3302Status;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());
    ulT3302Status                = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    if (GMM_FALSE == Gmm_Compare_Rai(pRai1, pRai2))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        *pucRaiChgFlg = GMM_TRUE;
    }
    else
    {
        *pucRaiChgFlg = GMM_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
    {
        /* 3GPP 23401 4.3.5.6   Idle mode signalling reduction function:
           The Idle mode Signalling Reduction (ISR) function provides a
           mechanism to limit signalling during inter-RAT cell-reselection
           in idle mode (ECM-IDLE, PMM-IDLE, GPRS STANDBY states).
        */
        /* AT&T LTE-BTR-1-1824��LTE-BTR-1-1826��LTE-BTR-1-1828����Ҫ��
           GMM��GU��attach����Ӧ�򱻾ܴ�����������T3302��ʱ����������ϵͳ
           ��������L�º�����ֹͣ��L��ע��ʧ������disable lte������GU������
           ��ԭʧ��С��ʱ����T3302��ʱ������ps attach */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != NAS_MML_GetTinType())
         && ((VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo)
          || (VOS_FALSE == ulT3302Status)))

        {
            *pucRaiChgFlg = GMM_TRUE;
        }

        /* �������ģʽI,��L��ϵͳ��GU,��Ҫ�ж�CS ��LAI�Ƿ�ı䣬����ı���Ҫ��������rau */
        if (GMM_TRUE == NAS_GMM_IsCsLaiChangeNeedRegister(ucNetMod))
        {
            *pucRaiChgFlg = GMM_TRUE;
        }
    }

#endif

    if (GMM_FALSE == Gmm_Compare_Lai(&(pRai1->Lai), &(pRai2->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        *pucLaiChgFlg = GMM_TRUE;
    }
    else
    {
        *pucLaiChgFlg = GMM_FALSE;
    }

    return;
}


VOS_UINT8 Gmm_RcvMmcSysInfoInd_PS_BAR(
    VOS_UINT8                           ucLaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (GMM_FALSE == ucLaiChgFlg))
        {
            if ( ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState ))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }

        }

        if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
        {

            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            return ucRst;
        }
        else if(GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            ucRst = GMM_FALSE;
        }
        else if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0)))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            ucRst = GMM_FALSE;
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
            ucRst = GMM_FALSE;
        }

        /* �����ǰҵ�����ޣ���������� */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        {
            Gmm_ComCnfHandle();
            GMM_BufferMsgDump();
        }
        else
        {
            GMM_BufferMsgResume();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }

    return ucRst;
}
VOS_UINT8 Gmm_RcvMmcSysInfoIndRelEstingLink(VOS_VOID)
{
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340���������У�����·�ͷź��ٴ���ϵͳ��Ϣ */
        g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
        ucRst = GMM_FALSE;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                       /* �����������ڽ�����������                 */
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {                                                                   /* GMM_REGISTERED_INITIATED״̬             */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* ����ȴ�CNF��־                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific����               */
            ucRst = GMM_FALSE;
        }
        else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);*/

            /* GMM�ĸ���״̬��U1ʱ,GMMΪ��������;����GMMǨ�Ƶ�ATT-TO-UPDATE������3311���г��� */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                g_GmmGlobalCtrl.SysInfo.Rai = stGmmRai;
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                Gmm_TimerStart(GMM_TIMER_T3311);
            }
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* ����ȴ�CNF��־                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* �����ǰ���е�specific����               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;          /* ����ȴ�CNF��־                          */

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;            /* �����ǰ���е�specific����               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: pRaiTemp�ĸ�ֵ
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(GMM_RAI_STRU         *pRaiTemp,
                                            VOS_VOID             *pRcvMsg
                                            )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */

    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* �õ�ԭ��ָ��                             */

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo��Ϊ��                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                          /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);                   /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);                  /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                          /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);                   /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);                  /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */
        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
              pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];               /* RAC                                      */
          }
    }

    return;
}
VOS_UINT8 Gmm_RcvMmcSysInfoInd_PreProcess_Handling(VOS_UINT8                    ucNetMod,
                                                   VOS_UINT8                    ucRaiChgFlg,
                                                   MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                                   VOS_UINT8                   *pucDrxLengthChgFlg
                                                )
{
    VOS_UINT8                           ucRst = GMM_TRUE;
    VOS_UINT8                           ucCsChanged2UnBarFlg;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */
    if (GMM_TRUE == *pucDrxLengthChgFlg)
    {                                                                           /* ϵͳ��Ϣ�д���DRX length��Ϣ             */
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* �洢DRX LENGTH                           */

        *pucDrxLengthChgFlg = GMM_FALSE;
    }

    ucCsChanged2UnBarFlg            =   pSysInfoInd->ucCsChanged2UnBarFlg;
    ucCsRestrictionFlg              =   NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg              =   NAS_MML_GetPsRestrictRegisterFlg();
    gstGmmCasGlobalCtrl.ucSysRauFlg = ucRaiChgFlg;
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    else
    {
        /* PS��ע�ᣬCS���bar����bar, ��Gs����δ����,��ʱGMM��Ҫ��������RAU�ؽ�Gs������ */
        if (   (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            && (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            && (VOS_TRUE == ucCsAttachAllow)
            && (VOS_TRUE == ucPsAttachAllow)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            if ( (VOS_FALSE == ucPsRestrictionFlg)
              && (VOS_FALSE == ucCsRestrictionFlg)
              && (VOS_TRUE == ucCsChanged2UnBarFlg)
              && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
              && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                ucRst = GMM_FALSE;
            }
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_CSPS_INFO
 *  FUNCTION : Gmm_RcvMmcSysInfoInd���������Ӷ�: CSPS_INFO�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  ŷ����   2009.06.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_CSPS_INFO(MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                        VOS_UINT8                   *pucNetMod
                                            )
{
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
        if (0 != pSysInfoInd->ulPsInfoSize)
        {
            if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
            {
                *pucNetMod = GMM_NET_MODE_I;
            }
            else
            {
                *pucNetMod = GMM_NET_MODE_II;
            }
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is supported");
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* ���õ�ǰС����֧��GPRS��־                */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
        }
    }
    else
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* ���õ�ǰС����֧��GPRS��־                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
    }

    return;
}


VOS_UINT8 Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
(
    VOS_UINT8                           ucNetMod,
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfoInd,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        if ((GMM_TRUE == *pucLaiChgFlg)
         || (GMM_TRUE == *pucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
                && (0x10 != g_GmmGlobalCtrl.ucState))
            {                                                                       /* �û�ģʽΪA,�����Ѿ�ע��                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {/* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                     && (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                    {
                        (VOS_VOID)Gmm_RcvMmcSysInfoIndRelEstingLink();
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                    else
                    {
                        /* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                        /* ͬϵͳ��С��ϵͳ��Ϣ���� */
                        Gmm_ComNetModeChange(pSysInfoInd);                              /* ��������ģʽ�任�Ĺ�������               */
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                }
            }
        }
        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
    }

    return ucRst;
}


VOS_VOID Gmm_RcvMmcSysInfoInd_State_Distribute(
                                  VOS_VOID    *pRcvMsg,                                 /* ��Ϣָ��                                 */
                                  VOS_UINT8    ucRaiChgFlg,                          /* RAI�仯��־                              */
                                  VOS_UINT8    ucDrxLengthChgFlg,                    /* DRX length�仯��־                       */
                                  VOS_UINT8    ucLaiChgFlg                           /* LAI�仯��־                              */
                                  )
{
    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = ucRaiChgFlg;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg = ucDrxLengthChgFlg;

    /* ��ԭ��MMCGMM_SYS_INFO_IND����״̬�ַ� */
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvMmcSysInfoInd_RegInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvMmcSysInfoInd_DeregInit(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvMmcSysInfoInd_RauInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvMmcSysInfoInd_ServReqInit(pRcvMsg,
                                         ucRaiChgFlg,
                                         ucDrxLengthChgFlg,
                                         ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvMmcSysInfoInd_DeregNmlServ(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(pRcvMsg,
                                             ucRaiChgFlg,
                                             ucDrxLengthChgFlg,
                                             ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:

        Gmm_RcvMmcSysInfoInd_RegNmlServ(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;

    case GMM_REGISTERED_PLMN_SEARCH:

        NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_REGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcSysInfoInd_RegUpdtNeed(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(pRcvMsg,
                                           ucRaiChgFlg,
                                           ucDrxLengthChgFlg,
                                           ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvMmcSysInfoInd_SuspWaitSys(pRcvMsg,ucRaiChgFlg,ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_IMSI:
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}


VOS_VOID Gmm_RcvMmcSysInfoInd(
                          VOS_VOID *pRcvMsg                                     /* ������Ϣʹ�õ�ͷ��ַ����                 */
                          )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucDrxLengthChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod = g_GmmGlobalCtrl.ucNetMod;
    VOS_UINT32                   ulNewCellId;
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    VOS_UINT8                           ucSimPsRegStatus;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();
    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* �õ�ԭ��ָ��                             */

    NAS_GMM_LogGmmCtxInfo();

    Gmm_SndSmSysInfoInd(MMCGMM_SGSN_RELEASE99_ONWARDS);

    /* �յ�Wģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, ���ָ�RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_FALSE,
                                VOS_TRUE);

    /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ�� */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_FALSE;

    NAS_GMM_SuspendLlcForInterSys();

    g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;

    Gmm_RcvMmcSysInfoInd_CSPS_INFO(pSysInfoInd, &ucNetMod);

    /* ��Ǩ��Wģʽ���ǣ���Ҫ�������ָ���־����Ϊ��ָ�����ʱ��Ҫʹ�ô˱�־ */
    if(NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
    {
        gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;

        NAS_GMM_SndMmcCipherInfoInd();
    }
    /* ֮ǰ���쳣�ͷ�,�յ�ϵͳ��Ϣ����������־ */
    if (RR_REL_CAUSE_ABORT_RR_NORMAL == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd:ERROR: Alloc mem fail.");
        return;
    }

    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pRcvMsg);

    /*�����յ�ϵͳ��Ϣ��G��ѡ��W���������Ҫ�����ԭ�����Ӵ��ڱ��
 */
    /*�˴�������Ҫ��С����BAR�Ĵ���֮ǰ����ΪС����BAR�᷵��
 */
    if((NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
       &&((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
          ||(GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)))
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);
        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);
#if (FEATURE_ON == FEATURE_LTE)
        /* L�¶�����������GU����Ҫ�ж������ISR����󼤻��pdp�����ģ���Ҫȥ����ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
#endif
    }

    /* ��ѡ��PS��BARRED��С��,������ģʽI,����T3312��ʱ */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend�������յ�T3312��ʱ����PS barred,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ( (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
               && (GMM_NET_MODE_I == ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;

    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    Gmm_Get_Location_Change_info(pRaiTemp, &stOldRai, &ucLaiChgFlg, &ucRaiChgFlg, ucNetMod);

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoInd->ulForbiddenMask) )
    {
        ucRst = Gmm_RcvMmcSysInfoInd_PS_BAR(ucLaiChgFlg);
        if(GMM_FALSE == ucRst)
        {
            g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
            g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            Gmm_MemFree(pRaiTemp);
            return;
        }
    }


    ulNewCellId = pSysInfoInd->ulCellId;

    g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;

    if (ulNewCellId != g_GmmGlobalCtrl.SysInfo.ulCellId)
    {
        g_GmmGlobalCtrl.SysInfo.ulCellId = ulNewCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_TRUE;
    }




    if (MMC_GMM_SYS_MSK_PS_DRX ==(pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PS_DRX))
    {
        /* ϵͳ��Ϣ�д���DRX length��Ϣ             */
        if (NAS_MML_GetWSysInfoDrxLen() != (VOS_UINT8)pSysInfoInd->ulPsDrxLength)
        {                                                                       /* DRX LENGTH�ı�                           */
            ucDrxLengthChgFlg = GMM_TRUE;                                       /* ����DRX length�仯��־                   */
        }
    }

    if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA�ı����DRX�ı�                        */
        ucRst = Gmm_RcvMmcSysInfoIndRelEstingLink();
        if(GMM_FALSE == ucRst)
        {
            NAS_GMM_SaveWasSysInfo(pSysInfoInd);
            Gmm_MemFree(pRaiTemp);
            return;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling(ucNetMod, pSysInfoInd, &ucLaiChgFlg, &ucRaiChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    }
    else
    {
        /*  suspend�������յ�T3312��ʱ����GPRS NOT SUPPORT,�����ٽ���suspend�Ĵ���ת��ΪexpiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_PreProcess_Handling(ucNetMod, ucRaiChgFlg, pSysInfoInd, &ucDrxLengthChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }

    Gmm_RcvMmcSysInfoInd_State_Distribute(pRcvMsg,
                                          ucRaiChgFlg,
                                          ucDrxLengthChgFlg,
                                          ucLaiChgFlg);

    Gmm_MemFree(pRaiTemp);

    /* ��·�ͷſ���: �յ�ϵͳ��Ϣ���ڴ�����Ϻ���������̵�Retry��־ */
    g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_FALSE;
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_FALSE;
    g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_GMM_RcvMmcLteSysInfoInd(
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    /* ��Ǩ��Lģʽ�£���Ҫ�������ָ���־����Ϊ��ָ�����ʱ��Ҫʹ�ô˱�־ */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
    gstGmmCasGlobalCtrl.ucGprsCipher       = VOS_FALSE;

    gstGmmSuspendCtrl.ucGetLteSecContext   = VOS_FALSE;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* �յ�Lģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, ������RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* ����ͷ�ԭ��ֵ */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;  

}
VOS_VOID NAS_GMM_RcvMmcLmmStatusInd(
    MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
)
{
    switch (pstLmmStatusInd->ulConnState)
    {
    case MMC_LMM_CONN_ESTING:
    case MMC_LMM_CONNECTED_SIG:
    case MMC_LMM_CONNECTED_DATA:

        gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_LTE;

        break;

    default:
        NAS_INFO_LOG1(WUEPS_PID_GMM, "pstLmmStatusInd->ulConnState =",pstLmmStatusInd->ulConnState);
        break;

    }

}


VOS_UINT32 NAS_GMM_IsCsLaiChangeNeedRegister(
    VOS_UINT8                           ucNetMod
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          ucMsMode;
    VOS_UINT8                           ucCsSimRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    ucMsMode           = NAS_MML_GetMsMode();
    ucCsSimRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
     && (GMM_NET_MODE_I == ucNetMod)
     && (NAS_MML_MS_MODE_PS_CS == ucMsMode)
     && (VOS_TRUE == ucCsSimRegStatus)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucCsAttachAllowFlg))
    {
        return GMM_TRUE;
    }

    return GMM_FALSE;
}

#endif
VOS_VOID NAS_GMM_StopReadyTimer_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

}


VOS_VOID NAS_GMM_SetIdleSrvState_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        if (GMM_AGB_GPRS_IDLE != gstGmmCasGlobalCtrl.GmmSrvState)
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
             NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

}


VOS_VOID Gmm_ComStaChg(VOS_UINT8 ucState)
{

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucState);
    }

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucState);
#endif

    g_GmmGlobalCtrl.ucState = ucState;                                          /* ����ҪǨ���״̬                         */

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_PrintState();

    Gmm_SndSmStatusInd();

    Gmm_SndSmsServiceStatusInd();

    if(VOS_TRUE == g_GmmGlobalCtrl.ucNeedChgServiceStatus)
    {
        Gmm_Com_ServiceStatus_Handle();                                         /* ֪ͨMMC����״̬                          */
    }
    /* 3GPP 24.008 4.7.2.2�½�������
      If the periodic routeing area update timer expires and the MS is in state
      GMM-REGISTERED.NO-CELL-AVAILABLE, the MS shall start the GERAN/UTRAN Deactivate
      ISR timer T3323. The MS shall initiate the routeing area updating procedure
      and stop the timer T3323 when the MS enters the state GMM-REGISTERED.NORMAL-SERVICE
      before timer T3323 expires. */

    if (GMM_REGISTERED_NORMAL_SERVICE == ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }


    if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
    {                                                                           /* ״̬Ǩ��GMM_DEREGISTERED_NO_IMSI         */
        if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
        {                                                                       /* sim����Ч                                */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;
        }
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_TimerStop(GMM_TIMER_T3319);                                         /* ֹͣ3319                                 */
    }


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


}

/*******************************************************************************
  Module   : Gmm_RcvMmRegisterInitiation
  Function : ԭ��MMGMM_REGISTER_INITIATION�Ľ��մ���
  Input    : VOS_VOID *pMsg  ��Ϣָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmRegisterInitiation(
    VOS_VOID                           *pMsg                                    /* ָ����Ϣ��ָ��                           */
)
{
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
    {                                                                           /* A+I                                      */
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* ���ò�ͬ״̬�µĴ���                     */
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_RcvMmcRegisterInitiation_ServReqInit(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch();
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcRegisterInitiation:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
        }
    }
    else
    {
    }
    return;
}
VOS_VOID Gmm_RcvMmcRegisterInitiation_ServReqInit(
                                              VOS_VOID *pMsg                        /* ָ����Ϣ��ָ��                           */
                                              )
{
    MMCGMM_REGISTER_INITIATION_STRU   *ptr;

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* �����������ڽ�����������                 */
        ptr = (MMCGMM_REGISTER_INITIATION_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_REGISTER_INITIATION_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcRegisterInitiation_ServReqInit:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_REGISTER_INITIATION_STRU));

        if (GMM_MSG_HOLD_FOR_RAU ==
            (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* ����Ϣ������־                           */

        return;
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask
            &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                          /* ���ԭ��ȴ���־                         */
    }
    g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;                /* �������жϵ�SR����                       */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                                   /* ����follow on��־                        */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);                   /* ����RAU                                  */
    return;
}
VOS_VOID Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */
    /*
    3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
    MS is in substate ATTEMPTING-TO-ATTACH and
        - expiry of timer T3302;
        - a new routing area is entered; or
        - an attach is triggered by CM sublayer requests.
    */
    if ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState )
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
    }
    Gmm_AttachInitiate(GMM_ATTACH_COMBINED);                                                       /* ����attach                               */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
  Function : ��GMM_REGISTERED_NORMAL_SERVICE/ATTEMPTING_TO_UPDATE_MM/
             ATTEMPTING_TO_UPDATE״̬���յ�ԭ��MMCGMM_REGISTER_INITIATION�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.02.03  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* ͣT3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* ͣT3302                                  */
    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter ��0                  */
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

    return;
}

/*******************************************************************************
  Module   : Gmm_ComUnrealProc
  Function : �����̵������жϴ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : VOS_UINT8   ucGmmAction   ����������
  History  :
    1. ��־��  2004.03.16  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_ComUnrealProc(VOS_VOID)
{
    VOS_UINT8       ucGmmAction = 0;                                                /* ����ֲ�����                             */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucGmmAction = GMM_ATTACH_NORMAL;
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        ucGmmAction = GMM_RAU_NORMAL;
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        {
            ucGmmAction = GMM_ATTACH_NORMAL;
        }
        else
        {
            ucGmmAction = GMM_RAU_NORMAL;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComUnrealProc:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return ucGmmAction;
}
VOS_UINT8 Gmm_ComGetFollowOnFlg(VOS_VOID)
{
    return  g_GmmGlobalCtrl.ucFollowOnFlg;
}


VOS_BOOL NAS_GMM_IsExistBufferService(VOS_VOID)
{
    if ((GMM_MSG_HOLD_FOR_SM == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     || (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_PAGING == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        return  VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_GMM_IsFollowOnPend() )
    {
        return  VOS_TRUE;
    }

    /* �����ж��Ƿ������� */

    return  VOS_FALSE;

}
VOS_VOID Gmm_ComForbiddenList(
                          VOS_UINT32   ulForbiddenMask                               /* ����forbidden�б������                  */
                          )
{
    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* �ȴ������                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* ���ԭ��ȴ���־                         */
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* ����״̬�Ĺ�������                       */
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* ����״̬�Ĺ�������                       */
    }

    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;                          /* ���������̱�־                           */
    g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComForbiddenList:INFO: specific procedure ended");
    return;
}


VOS_VOID Gmm_ComNetModeChange_NotSupportGprs_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucLaiChgFlg)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* ͣT3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* ͣT3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* ͣT3330                                  */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* ͣ����Timer                              */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
    g_GmmReqCnfMng.ucCnfMask = 0;

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */
    Gmm_ComCnfHandle();
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* �嵱ǰ����                               */

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_NotSupportGprs_Handling:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
        return;
    }

    if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
    }

    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* ����״̬�Ĺ�������                       */
    }

    if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* ͣT3312                                  */
    }

    else
    {
        if (GMM_TRUE == ucLaiChgFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }

        else
        {
            if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                == g_GmmGlobalCtrl.ucState)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* ͣT3312                                  */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }

            else
            {
                if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);                                /* ��T3312                                  */
                }
            }
        }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_I2II_Handling
  Function : Gmm_ComNetModeChange �����Ӷ�: ����ģʽ I => II �Ĵ���
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.11  �¹�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_I2II_Handling(
                                                  VOS_UINT8 ucNetMod,
                                                  VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /*
        Imsi Detach�����д�����ģʽI�䵽����ģʽII����ֹ��Detach����Ϊ
        �˴�Detachʧ�ܡ���Ϊ�仯������ģʽII��PS�򲻿��ܷ���Imsi Detach
        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        /*
        Combined GPRS/IMSI Detach����������ģʽ��I�仯��II��
        ��¼���жϵ�����ΪPs Detach����Ϊ����ģʽII�²��ܷ���
        Combined GPRS/IMSI Detach.
        */
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_DETACH_NORMAL;                     /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* ͣT3310                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_I2II_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}


VOS_VOID Gmm_ComNetModeChange_Netmode_II2I_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* ����ģʽ                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */



        /* ����CS��ֹע��ʱ�򣬲�������ATTACH */
        if ( VOS_FALSE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(
                                        GMM_COMBINED_RALAU_WITH_IMSI_ATTACH
                                          );
        }
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* �������жϵ�SR����                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* �����ǰ���е�specific����               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* ����follow on��־                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* ͣT3310                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_II2I_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Fill_Rai
  Function : Gmm_ComNetModeChange �����Ӷ�: ��ָ��pRaiTemp��ֵ
  Input    : GMM_RAI_STRU                *pRaiTemp,
             MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ŷ���� 2009.06.11  �¹�����
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Fill_Rai(
                          GMM_RAI_STRU                *pRaiTemp,
                          MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
                          )
{
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo��Ϊ��                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                      /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);               /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);              /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                      /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);               /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);              /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */

        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }

    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
            pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];             /* RAC                                      */
          }
    }

    return;

}
VOS_VOID Gmm_ComNetModeChange(VOS_VOID  *pMsg)
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* ����MMCGMM_SYS_INFO_IND_STRU����ָ��     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp    = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: alloc rai temp memory fail.");
        return;
    }

    Gmm_ComNetModeChange_Fill_Rai(pRaiTemp, pSysInfoInd);

    if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
    {
        ucNetMod = GMM_NET_MODE_I;
    }
    else
    {
        ucNetMod = GMM_NET_MODE_II;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, ucNetMod))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* �洢DRX LENGTH                           */
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_ComNetModeChange_NotSupportGprs_Handling(ucNetMod, ucLaiChgFlg);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* ͣT3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* ͣT3302                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* ����ģʽ��� I->II                       */
        Gmm_ComNetModeChange_Netmode_I2II_Handling(ucNetMod, ucRaiChgFlg);
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        Gmm_ComNetModeChange_Netmode_II2I_Handling(ucNetMod, ucRaiChgFlg);
    }

    Gmm_MemFree(pRaiTemp);
}


VOS_VOID Gmm_ComNetModeChangeGsm(VOS_VOID  *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfoInd;
    VOS_UINT8                           ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                           ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                       *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                           ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST         *ptr;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    if (((GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* ���ڽ�����                               */
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* ����Ϣ������־                           */
        return;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;                /* �洢��Ϣ�׵�ַ�� ulMsgAddrForAttach      */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;        /* ����Ϣ������־                           */
        return;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
          return;
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* ��дRAC */
    pRaiTemp->ucRac = pSysInfoInd->ucRac;
    /* ��дLAC */
    /* BEGIN: Modified by liurui id:40632, 2006/3/4   PN:A32D02252*/
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfoInd->usLac;       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfoInd->usLac >> 8);
    /* END:   Modified by liurui id:40632, 2006/3/4 */
    /* ��дPLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMcc & 0x0F);             /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 8) & 0x0F);      /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 16) & 0x0F);     /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMnc & 0x0F);             /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 8) & 0x0F);      /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 16) & 0x0F);     /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                       /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                  /* MNC Degit count                          */
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, pSysInfoInd->ucNetworkOperationMode))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    ucNetMod = pSysInfoInd->ucNetworkOperationMode;

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenFlg;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    /* G��ϵͳ��Ϣ����DRX LENGTH ��ɾ��*/

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        if (GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChangeGsm:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
            Gmm_MemFree(pRaiTemp);
            return;
        }
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* ����״̬�Ĺ�������                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* ����״̬�Ĺ�������                       */
        }
        if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* ͣT3312                                  */
        }
        else
        {
            if (GMM_TRUE == ucLaiChgFlg)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* ͣT3312                                  */
            }
            else
            {
                if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                    == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);                             /* ͣT3312                                  */

                    NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
                }
                else
                {
                    if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                    {
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* ��T3312                                  */
                    }
                }
            }
        }
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* ͣT3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* ͣT3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* ͣT3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* ͣT3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ����Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* ����ģʽ��� I->II                       */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        /* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
            return;
        /* END:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* ����ģʽ���                             */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */

        /* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
        /* END:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
    }
    /* BEGIN: Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* ����ģʽGSM I�ı䵽����ģʽGSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* ����ģʽGSM II�ı䵽����ģʽGSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_I == ucNetMod))
    {/* ����ģʽGSM III�ı䵽����ģʽGSM I */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_II == ucNetMod))
    {/* ����ģʽGSM III�ı䵽����ģʽGSM II */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* ����ģʽ                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* ����ģʽ                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    Gmm_MemFree(pRaiTemp);
    return;
    /* END:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */
}



VOS_VOID Gmm_RcvMmcGmmModeChangeReq(
    VOS_VOID                           *pMsg                                   /* ��Ϣָ��                                 */
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU        *pModeChg;                                   /* ����ָ��                                 */

    pModeChg = (MMCGMM_MODE_CHANGE_REQ_STRU *)pMsg;                             /* ��ʼ��ָ��                               */

    switch (pModeChg->enMsMode)
    {                                                                           /* �û�ģʽ                                 */
    case NAS_MML_MS_MODE_NULL:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS��ע�ᱻ��ֹ                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* ״̬Ǩ�Ƶ�GMM_NULL                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    case NAS_MML_MS_MODE_PS_CS:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM״̬ΪNULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS��ǰפ����С����                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM������                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM��Ч                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM��Ч                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }
                }
            }
            else
            {                                                                   /* û��С��פ��                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* ״̬Ǩ��                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_PS_ONLY:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM״̬ΪNULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS��ǰפ����С����                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM������                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM��Ч                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM��Ч                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }

                }
            }
            else
            {                                                                   /* û��С��פ��                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* ״̬Ǩ��                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_CS_ONLY:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS��ע�ᱻ��ֹ                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* ״̬Ǩ�Ƶ�GMM_NULL                       */
            if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* ״̬Ǩ��                                 */
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: The MsMode is Abnormal");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_GmmStatusMsgMake
  Function : GMM STATUS��Ϣ������
  Input    : VOS_UINT8    ucRejectCause                     ����ԭ��
  Output   : ��
  NOTE     : ��
  Return   : NAS_MSG_STRU *pGmmStatus  ָ��NAS_MSG_STRU�ṹ��ָ��
  History  :
    1. ��־��  2004.04.14  �¹�����
*******************************************************************************/
NAS_MSG_STRU *Gmm_GmmStatusMsgMake(
                                   VOS_UINT8    ucRejectCause                       /* ����ԭ��                                 */
                                   )
{
    NAS_MSG_STRU *pGmmStatus = VOS_NULL_PTR;                                            /* ָ��NAS_MSG_STRU�ṹ��ָ�����           */

    pGmmStatus = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));           /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pGmmStatus)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_GmmStatusMsgMake:ERROR: Alloc mem fail.");
        return pGmmStatus;
    }
    Gmm_MemSet(pGmmStatus, 0, sizeof(NAS_MSG_STRU));                            /* �ڴ�ռ���0                              */

    /* ��д�տ���Ϣ����             */
    pGmmStatus->ulNasMsgSize = GMM_MSG_LEN_GMM_STATUS;                          /* ��д�տ���Ϣ����                         */
    pGmmStatus->aucNasMsg[0] = GMM_PD_GMM;                                      /* ��дProtocol discriminator               */
    pGmmStatus->aucNasMsg[1] = GMM_MSG_GMM_STATUS;                              /* ��дAttach complete message identity     */
    pGmmStatus->aucNasMsg[2] = ucRejectCause;                                   /* ��дGMM cause                            */

    return pGmmStatus;
}
VOS_VOID Gmm_RcvTcTestReq(
    VOS_VOID                           *pMsg                                    /* ָ��ԭ���ָ��                           */
)
{
    TCGMM_TEST_REQ_STRU                *pTcTestReq = VOS_NULL_PTR;              /* ����ԭ������ָ��                         */

    pTcTestReq = (TCGMM_TEST_REQ_STRU *)pMsg;                                   /* ǿ������ת��                             */

    if (TC_RB_TEST_ACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC����                                   */
        g_GmmGlobalCtrl.ucTcPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_TC_ACTIVE);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS GMM_TC_ACTIVE");

        Gmm_TimerStop(GMM_TIMER_T3317);                                             /* ͣT3317                                  */
        Gmm_TimerPauseForTc(GMM_TIMER_ALL);                                     /* �������������е�Timer                    */


        /* ����PS TCҵ����ڣ��Կ���MMC�����������Ȼ��
           ͨ��PS����TC����ʱ����������PSҵ����ڣ������ڴ˴�����PS TCҵ����ڡ�

           ͨ��CS����TC���أ��յ�������PAGING��Ϣʱ����������CSҵ����ڣ���
           TC���ؽ���ʱ�����ٵ�������CSҵ����ڡ� */

        NAS_MML_SetPsTcServiceFlg(VOS_TRUE);

    }
    else if (TC_RB_TEST_DEACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TCȥ����                                 */
        GMM_CasFsmStateChangeTo(g_GmmGlobalCtrl.ucTcPreSta);

        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS ",g_GmmGlobalCtrl.ucState);

        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* �ָ����б������Timer                    */


        /* ����PS TCҵ�񲻴��� */
        NAS_MML_SetPsTcServiceFlg(VOS_FALSE);


    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_RcvTcDataReq
  Function : �յ�TCGMM_DATA_REQԭ��Ĵ���
  Input    : VOS_VOID *pMsg
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.06.18  �¹�����
*******************************************************************************/
VOS_VOID Gmm_RcvTcDataReq(
                      VOS_VOID *pMsg                                            /* ָ��ԭ���ָ��                           */
                      )
{

    TCGMM_DATA_REQ_STRU           *pTcDataReq;                                  /* ����ԭ������ָ��                         */
    NAS_MSG_STRU                  *pTcMsg;

    if (GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
    {                                                                           /* ��ǰ״̬����GMM_TC_ACTIVE                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvTcDataReq:WARNING: TCGMM_DATA_REQ is unexpected");
        return;
    }
    pTcDataReq = (TCGMM_DATA_REQ_STRU *)pMsg;                                   /* ǿ������ת��                             */

    pTcMsg = (NAS_MSG_STRU *)(&pTcDataReq->SendTcMsg);

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH, pTcMsg);              /* ���� RRMM_DATA_REQ                       */
    }
    return;
}
/*******************************************************************************
Module   : Gmm_RcvGmmStatusMsg
Function : �յ�GMM STATUS��Ϣ�Ĵ���
Input    : NAS_MSG_STRU *pMsg
Output   : ��
NOTE     : ��
Return   : ��
History  :
    1. ��־��  2005.01.25  �¹�����(for agent)
*******************************************************************************/
VOS_VOID Gmm_RcvGmmStatusMsg(
                                          NAS_MSG_FOR_PCLINT_STRU *pMsg
                                         )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_GMM_STATUS > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvGmmStatusMsg:WARNING: The length of GMM STATUS is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    return;
}
/* ��������ɾ�� */

VOS_VOID GRM_Inform_Gmm()
{
    LL_DATA_INFORM_MSG                 *pMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == gstGmmCasGlobalCtrl.ucLastDataSender))
    {
        /* ״̬���ԣ����������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
         && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
        {
            return;
        }

        /* ready timer��ʱ��ʱ��Ϊ0�����������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            return;
        }

        /* ready timer��ʱ��ʱ��Ϊ0xffffffff����Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* TC״̬t3314����������Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* ��TC״̬t3314����������Ϊready̬���ˣ������gmm ��ID_LL_DATA_INFORM��Ϣ */
        if ((GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            Gmm_TimerStart(GMM_TIMER_T3314);

            return;
        }
    }

    pMsg = (LL_DATA_INFORM_MSG *)PS_ALLOC_MSG(UEPS_PID_LL,
                  sizeof(LL_DATA_INFORM_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* ��Ϣͷ�̶��Ĳ��� */
    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = UEPS_PID_LL;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_GMM;

    /* ��д��Ϣ���Ͳ��� */
    pMsg->ulMsgName = ID_LL_DATA_INFORM;

    ulRet = PS_SEND_MSG(UEPS_PID_LL, pMsg);

    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_SendMsg()");
    }


    return;
}
/******************************************************************************
 * �������� �� WuepsGmmPidInit
 * �������� �� WUEPS GMM PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsGmmPidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}


VOS_VOID Gmm_RcvLLCInform( VOS_VOID *pMsg )
{
    /* ����GSMģʽ��PS�����ҵ������ڽ���ע�� */
    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_GSM;


    if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        return;
    }


    if (0 != gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        /*A32D12829==>*/
        if (0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
            {
                /* ��������T3314��ֹͣT3312 */
                if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
                {
                    Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
                }
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
                if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    Gmm_TimerStop(GMM_TIMER_T3323);
                }
#endif
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
            return;
        }
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
        if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        {
            if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {
                Gmm_TimerStart(GMM_TIMER_T3314);
                Gmm_TimerPauseForTc(GMM_TIMER_T3314);                               /* ����T3312                                */
            }
        }
        else
        {
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {                                                                           /* ��timer�Ѿ�����                          */
               if(VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
               {

                   Gmm_TimerStop(GMM_TIMER_T3314);
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
               else
               {
                   g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3314);         /* ��Timer��������־                        */
                   g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
            }
            else
            {
                /*<==A32D12829*/
                g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                Gmm_TimerStart(GMM_TIMER_T3314);
            }

        }
        if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
        {

            /* ��������T3314��ֹͣT3312 */
            if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
            {
                Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                 NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            }
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
            if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                Gmm_TimerStop(GMM_TIMER_T3323);
            }
#endif
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_PrintState
 Description    : ��ӡGMM״̬
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-10-17
    Author      : Roger Leo
    Modification: created
*****************************************************************************/
VOS_VOID GMM_PrintState(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            GMM_LOG_INFO("GMM State is GMM_NULL.");
            break;
        case GMM_REGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_INITIATED.");
            break;
        case GMM_DEREGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_INITIATED.");
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_ROUTING_AREA_UPDATING_INITIATED.");
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_SERVICE_REQUEST_INITIATED.");
            break;
        case GMM_TC_ACTIVE:
            GMM_LOG_INFO("GMM State is GMM_TC_ACTIVE.");
            break;
        case GMM_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_GPRS_SUSPENSION.");
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTACH_NEEDED.");
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH.");
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_PLMN_SEARCH.");
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_IMSI.");
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_UPDATE_NEEDED.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE.");
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_PLMN_SEARCH.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM.");
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_IMSI_DETACH_INITIATED.");
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_NORMAL_SERVICE.");
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_GPRS_SUSPENSION.");
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_WAIT_FOR_SYSINFO.");
            break;
        default:
            GMM_LOG_WARN("GMM State is Error.");
            break;
    }
    return;
}


VOS_UINT8 GMM_GetSignalingStatus(VOS_VOID)
{
    VOS_UINT8      ucResult = MMC_GMM_SIGNALING_STATUS_ABSENT;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        ucResult = MMC_GMM_SIGNALING_STATUS_PRESENT;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: ucResult is ",(VOS_INT32)ucResult);

    return ucResult;
}


VOS_UINT32 NAS_GMM_IsRegisteredOrRegistering(VOS_VOID)
{
    if (  (GMM_REGISTERED_NORMAL_SERVICE            == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_INITIATED                == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED     == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE     == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED           == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 GMM_IsServiceExist(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if((VOS_TRUE == NAS_MML_IsPsBearerExist())
    || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ulResult = GMM_TRUE;
    }
    else
    {
        ulResult = GMM_FALSE;
    }
    return ulResult;
}


VOS_UINT32 NAS_GMM_GetSignalingStatusInGsm(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (( ( VOS_TRUE == NAS_MML_GetPsTbfStatusFlg() )
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: ucResult is ",(VOS_INT32)ulResult);

    return ulResult;
}


VOS_VOID Gmm_BufSmDataReqMsg( VOS_VOID *pMsg )
{
    GMMSM_DATA_REQ_STRU                 *ptr;

    /*���뻺����Ϣ���ڴ�*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_RcvSmDataReq_RegNmlServ:WARNING: Gmm_MemMalloc fail !! ");
          return;
    }

    /*����Ϣ�ݴ浽������ڴ���*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
    }
    /*�÷���ֻ�������µ�һ����Ϣ,����ǰ�л�����Ϣ,���ͷŵ�*/
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SM;

    return;
}
VOS_VOID Gmm_ComCnfHandle(VOS_VOID)
{
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* ��ǰ����ΪSR_DATA                        */
        if (RR_REL_CAUSE_RRC_SNW == g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_OOS);                 /* ֪ͨRABM���                             */
        }
        else
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        }
    }


    if ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
     || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
    {

        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        NAS_GMM_SndMmcMmDetachInfo();
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_ComCnfHandle(): Clear cached SM data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL;
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* ������specific����                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* ֪ͨRABM���                             */
            break;

        case GMM_DETACH_COMBINED:
        case GMM_DETACH_NORMAL:
        case GMM_DETACH_WITH_IMSI:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
                NAS_GMM_SndMmGprsDetachComplete();
            }

            break;

        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* �����������                             */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* ���followon��־                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }
}

VOS_UINT32 Gmm_GetState()
{
    return g_GmmGlobalCtrl.ucState;
}

VOS_UINT32 Gmm_GetGprsState()
{
    VOS_UINT32  ulGprsState;
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState&0xf0))
            ||(GMM_NULL == g_GmmGlobalCtrl.ucState))
        {
            ulGprsState = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            ulGprsState = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            ulGprsState = GMM_IU_PMM_IDLE;
        }
    }
    else
    {
        ulGprsState = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    return ulGprsState;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_NetMod
 *  FUNCTION : Gmm_FillNasMmInfo���������Ӷ�: NetMod�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  ŷ����   2009.06.11  �°�����
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_NetMod(NAS_OM_MM_IND_STRU       *pMsg)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_1;
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_2;
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_3;
    }
    else
    {
        pMsg->enNetMode = NET_OPERATE_MODE_BUTT;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    return;
}


VOS_VOID NAS_GMM_FillNasGmmState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    pstMsg->enGmmSubState = GMM_SUB_STATE_BUTT;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            pstMsg->enGmmState = STATE_GMM_NULL;
            break;
        case GMM_REGISTERED_INITIATED:
            pstMsg->enGmmState = REGISTERED_INITIATED;
            break;
        case GMM_DEREGISTERED_INITIATED:
            pstMsg->enGmmState = DEREGISTERED_INITIATED;
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            pstMsg->enGmmState = ROUTING_AREA_UPDATING_INITIATED;
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            pstMsg->enGmmState = SERVICE_REQUEST_INITIATED;
            break;
        case GMM_TC_ACTIVE:
            pstMsg->enGmmState = TC_ACTIVE;
            break;
        case GMM_GPRS_SUSPENSION:
            pstMsg->enGmmState = GPRS_SUSPENSION;
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NORMAL_SERVICE;
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_LIMITED_SERVICE;
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTACH_NEEDED;
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTEMPTING_TO_ATTACH;
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_PLMN_SEARCH;
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_IMSI;
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NORMAL_SERVICE;
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_LIMITED_SERVICE;
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_UPDATE_NEEDED;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE;
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_PLMN_SEARCH;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE_MM;
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_IMSI_DETACH_INITIATED;
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            pstMsg->enGmmState = SUSPENDED_NORMAL_SERVICE;
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            pstMsg->enGmmState = SUSPENDED_GPRS_SUSPENSION;
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            pstMsg->enGmmState = SUSPENDED_WAIT_FOR_SYSINFO;
            break;
        default:
            pstMsg->enGmmState = GMM_STATE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_FillNasMmInfo:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    NAS_GMM_FillNasGmmGprsState(pstMsg);

    return;
}


VOS_VOID NAS_GMM_FillNasGmmGprsState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    pstMsg->enGmmGprsState              = NAS_OM_GMM_GPRS_STATE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        switch(gstGmmCasGlobalCtrl.GmmSrvState)
        {
            case GMM_AGB_GPRS_IDLE:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_IDLE;
                break;
            case GMM_AGB_GPRS_STANDBY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_STANDBY;
                break;
            case GMM_AGB_GPRS_READY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_READY;
                break;
            default:
                break;
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_ucUpdateSta
 *  FUNCTION : Gmm_FillNasMmInfo���������Ӷ�: ucUpdateSta�Ĵ���
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  ŷ����   2009.06.11  �°�����
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_ucUpdateSta(NAS_OM_MM_IND_STRU     *pMsg)
{
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    switch (NAS_MML_GetPsUpdateStatus())
    {
    case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU1;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU2;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
    case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU3;
        break;
    default:
        pMsg->enGmmUpdateStatus = GMM_UPDATE_STATUS_BUTT;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_FillNasMmInfo:WARNING: PsUpdateStatus is Error");
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */

    return;
}

/*******************************************************************************
Module   : Gmm_FillNasMmInfo
Function :
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :

  1.��    ��   : 2008��9��01��
    ��    ��   :
    �޸�����   :
*******************************************************************************/


VOS_VOID Gmm_Com_ServiceStatus_Handle(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {         /* ����״̬��Ҫ�ϱ�����״̬    */
    case GMM_NULL:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:


        /* �жϵȴ���־�Ƿ���ڣ������������MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        break;

    default:
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_ServiceStatus_Handle:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return;
}

NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 Gmm_ComServiceSts(VOS_VOID)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8       ucServiceSts = MM_COM_SRVST_NO_CHANGE;                     /* ������ʱ����                             */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�÷���״̬                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucServiceSts = MM_COM_SRVST_NORMAL_SERVICE;
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        ucServiceSts = NAS_GMM_GetRegUptNeededPsSrvStatus();
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;

        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
        }
        break;

    case GMM_DEREGISTERED_NO_IMSI:
        ucServiceSts = MM_COM_SRVST_NO_IMSI;
        break;

    case GMM_NULL:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        ucServiceSts = MM_COM_SRVST_NO_SERVICE;
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        if (5 == g_GmmRauCtrl.ucRauAttmptCnt)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;
        }
        else
        {
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        }
        break;
    default:
        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComServiceSts:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucServiceSts;
}

VOS_UINT32 Gmm_GetServiceStatusForSms(VOS_VOID)
{
    GMM_STATE_TYPE_UINT8    ucState;
    VOS_UINT32              ulServiceSts = GMM_SMS_NO_SERVICE;                  /* ������ʱ����                             */

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    switch (ucState)
    {                                                                           /* ����״̬�÷���״̬                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        ulServiceSts = GMM_SMS_NORMAL_SERVICE;
        break;
    default:
        break;
    }

    return ulServiceSts;
}


VOS_VOID NAS_GMM_RcvInterRatHandoverInfoCnf(VOS_VOID *pMsg)
{
    RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU   *pRrmmInterRatInfoMsg = VOS_NULL_PTR;
    NAS_MSG_STRU                            *pSendNasMsg = VOS_NULL_PTR;

    pRrmmInterRatInfoMsg = (RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU *)pMsg;

    Gmm_TimerStop(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg   = VOS_TRUE;
    g_GmmInterRatInfoCtrl.ucDataLen                 = (VOS_UINT8)pRrmmInterRatInfoMsg->usDataLen;

    if (0 == pRrmmInterRatInfoMsg->usDataLen)
    {
        /* WRR����InterRatHandoverʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Msg Len is 0.");
    }
    else
    {
        /* InterRatHandoverInfo ��Ϣ���浽ȫ�ֱ����� */
        PS_MEM_CPY(g_GmmInterRatInfoCtrl.aucData, pRrmmInterRatInfoMsg->aucData, g_GmmInterRatInfoCtrl.ucDataLen);
    }

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH��������SM������,֪ͨSM GMMע��ɹ�,����ucSmCnfFlg��־ */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* �ظ�����Attach Complete ��Ϣ */
        pSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* ����Ҫ�ȴ�RABM�Ļظ���Ϣ�������Ѿ��յ�RABM�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}
VOS_UINT32 NAS_GMM_IsInHandoverProcedure(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;

    if ((GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsInHandoverProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ulResult;
}


VOS_UINT32  NAS_GMM_IsInRegisterProcedure(VOS_VOID)
{
    /* �жϵ�ǰ�Ƿ���ע������� */
    if((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}
VOS_VOID NAS_GMM_CnfSmNotAttach(
    GMM_SM_CAUSE_ENUM_UINT16            enCause                                 /* ע��ʧ��ԭ��ֵ */
)
{
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, enCause);
        g_GmmAttachCtrl.ucSmCnfFlg            = GMM_FALSE;
        g_GmmGlobalCtrl.ucFollowOnFlg         = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
    }
}
VOS_UINT32 NAS_GMM_IsInRegOrDeregProcedure(VOS_VOID)
{
    VOS_UINT8      ucResult;

    ucResult = VOS_FALSE;

    /* WCDMAģʽ�£����ڽ���ע��/ȥע�ᣬ������ҵ�������ʱ����Ϊ�������ӣ�
      GSMģʽ�£���TBF����ʱ����Ϊ�������� */
    if ( (GMM_REGISTERED_INITIATED             == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_INITIATED           == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ucResult = VOS_TRUE;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_GMM, "NAS_GMM_IsInRegisterOrDeregisterProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucResult;
}


VOS_UINT32 NAS_Gmm_IsInServiceProcedure(VOS_VOID)
{
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetGmmRegStateForInterPLmnList
 ��������  : ��ȡGMM��״̬�Ƿ��ܷ����б�����,��Ҫ����MM�����б�����ʱ�����ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK:���Է����б�����
              VOS_ERR:���ܷ����б�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��21��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetGmmRegStateForInterPLmnList( VOS_VOID )
{
    VOS_UINT8                           ucTimerId;
    VOS_BOOL                            bTimerRunning;
    VOS_UINT32                          ulTimerRunMask;

    /* С����bar����� */
    if ( ( GMM_DEREGISTERED_ATTACH_NEEDED        == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_UPDATE_NEEDED          == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    ucTimerId   = GMM_TIMER_T3302;

    ulTimerRunMask = g_GmmTimerMng.ulTimerRunMask;

    /*lint -e701*/
    if (0 != ( ulTimerRunMask & ( 0x00000001 << ucTimerId )))
    /*lint +e701*/
    {
        bTimerRunning = VOS_TRUE;
    }
    else
    {
        bTimerRunning = VOS_FALSE;
    }

    if ( VOS_FALSE == bTimerRunning )
    {
        return VOS_ERR;
    }


    if ( ( GMM_REGISTERED_ATTEMPTING_TO_UPDATE   == g_GmmGlobalCtrl.ucState)
      || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    if ( ( GMM_DEREGISTERED_NO_IMSI   == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertPlmnIdToMmcFormat
 ��������  : ��GMM��PLMNID��ʽת��ΪMMC��ʽ��
 �������  : pstGmmPlmnId:GMM��PLMN ID��ʽ
 �������  : pstMmcPlmnId:MMC��PLMN ID��ʽ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToMmcFormat(
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId
)
{

    pstMmcPlmnId->ulMcc = pstGmmPlmnId->aucMccDigit[0]
                        | (pstGmmPlmnId->aucMccDigit[1] << 8)
                        | (pstGmmPlmnId->aucMccDigit[2] << 16);

    pstMmcPlmnId->ulMnc = pstGmmPlmnId->aucMncDigit[0]
                        | (pstGmmPlmnId->aucMncDigit[1] << 8)
                        | (pstGmmPlmnId->aucMncDigit[2] << 16);
}
/*****************************************************************************
 �� �� ��  : NAS_GMM_ConvertPlmnIdToMmcFormat
 ��������  : ��GMM��PLMNID��ʽת��ΪMMC��ʽ��
 �������  : pstMmcPlmnId:
 �������  : pstGmmPlmnId
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��28��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToGmmFormat(
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId,
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId
)
{
    pstGmmPlmnId->aucMccDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMcc & 0x0F);

    pstGmmPlmnId->aucMccDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 8) & 0x0F);

    pstGmmPlmnId->aucMccDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 16) & 0x0F);

    pstGmmPlmnId->ucMncCnt = 3;

    pstGmmPlmnId->aucMncDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMnc & 0x0F);

    pstGmmPlmnId->aucMncDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 8) & 0x0F);

    pstGmmPlmnId->aucMncDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 16) & 0x0F);

    if (GMM_PLMNID_MNC3_INVALID == pstGmmPlmnId->aucMncDigit[2])
    {
        pstGmmPlmnId->ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

}
VOS_UINT32 NAS_GMM_IsDeregisterState(
    GMM_STATE_TYPE_UINT8                ucState
)
{
    if ((GMM_REGISTERED_INITIATED == ucState)
     || (GMM_DEREGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_DEREGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_DEREGISTERED_ATTACH_NEEDED == ucState)
     || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_DEREGISTERED_PLMN_SEARCH == ucState)
     || (GMM_DEREGISTERED_NO_IMSI == ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID Gmm_FreeBufferMsgWithoutSm(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* ����б�����paging(IMSI)ԭ��             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* ��ȡpaging(IMSI)ԭ���ַ                 */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* ����б�����RAUԭ��                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* ��������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* ��ȡRAUԭ���ַ                          */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* ����б�����DETACHԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* ��ȡdetachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* ����б�����attachԭ��                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* ��ȡattachԭ���ַ                       */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}


VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiChg()
{
    g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* ���T3312������                        */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                       /* ��A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
    }
    else
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ����RAU����                              */
    }
}
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire()
{
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* ��A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
          || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* ����RAU����combined RAU with IMSI attach */
    }
}
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire()
{
    VOS_UINT8                           ucCsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    /* ��ǰPS����״̬ΪU1 */
    if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /* ������ģʽI�Ĵ��� */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
         || (VOS_TRUE != ucCsAttachAllow)
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
        else
        {
            /* CS����״̬ΪU1����Gs���Ӵ��� */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                }

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
            else                                                                /* CS����״̬����U1,����Gs�����Ѿ��Ƴ� */
            {
                /* sim��Ч����CS������ע�� */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                    }

                    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);                     /* ����RAU                                  */
                }
            }
        }
    }
    else
    {
        /* ����״̬����GU1,����RAU */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
}
VOS_VOID  NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg()
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /* T3312��ʱ��־�����ڡ�*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire();
    }
    else
    {
        /* T3312��ʱ��־���ڡ�*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire();
    }
}


VOS_VOID NAS_GMM_ComProcAcInfoChgInd(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* ��ѡ��PS��BARRED��С��,������ģʽI,����T3312��ʱ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
    }
    /* ��ǰҵ�����ޣ������ҵ�񻺴� */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    {
        /* ������� */
        Gmm_ComCnfHandle();
        GMM_BufferMsgDump();
    }
}
VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* PS ע��Ӳ����޵����� */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState)
        {
            /* ����ģʽI */
            if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* ֪ͨMM����LU                             */
            }
        }

        /* ���õ�ǰPS����״̬Ϊ���Ʒ��� */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
}
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    /* PS ע������ */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        /* Ǩ�Ƶ�ǰGMM״̬��GMM_REGISTERED_UPDATE_NEEDED */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
}

VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS ע������޵������� */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucSysValidFlg       = GMM_TRUE;
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }

        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);

        /* PS����Ч */
        if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
        {                                                                           /* ԭ��SIM��Ч                              */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
            return;
        }

        /* ��ǰ�û����ò�֧��PSע�� */
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* ����״̬�Ĺ�������                       */

            GMM_BufferMsgResume();
            return;
        }

        /* ��ǰ���粻֧��GPRS�����������ڽ�ֹ�б� */
        if ((GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
         || (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask))
        {                                                                           /* ��֧��GPRS                               */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* ����״̬�Ĺ�������                       */
        }
        else
        {                                                                           /* С���ı�                                 */
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }


}
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    VOS_UINT8                           ucCsAttachAllow;                        /* CS���Ƿ�����ע��,VOS_TRUE:����CS��ע��,VOS_FALSE:������CS��ע�� */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();
    ucCsAttachAllow     = NAS_MML_GetCsAttachAllowFlg();

    /* PS ע�᲻���޵����� */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* ֪ͨMM����LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
            }
            else
            {
                 /* ֪ͨMM����LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
    }
    else
    {
        /* ����ģʽI,�ֻ�ģʽA,CS����Ч,Gs���ӱ�־�����ڣ��ҵ�ǰCS������ڣ�
        CSע������ޱ�Ϊ������ʱ��Ҫ��������ע�� */
        if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
         && (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
         && (VOS_TRUE == ucCsAttachAllow)
         && (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
         && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
    }
}


VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS ע������޵������� */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }
        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);
        if (VOS_FALSE ==  NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* ��ǰ���粻֧��GPRS */
        else if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* ��ǰ�����ڽ�ֹ�б� */
        else if (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        }
        else if (VOS_FALSE == NAS_MML_IsRaiChanged())
        {
            /* RAIû�иı� */
            NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg();
        }
        else
        {
            /* RAI�ı� */
            NAS_GMM_ProcPsAcChgRegisterNetRaiChg();
        }
    }

}
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd(
    NAS_MSG_STRU                       *pstMsg
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    /* ��ԭ��RRMM_W_INFO_CHANGE_IND����״̬�ַ� */
    switch (g_GmmGlobalCtrl.ucState)
    {
        /* DEREG״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(pstAcInfoChangeInd);
            break;
        case GMM_DEREGISTERED_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            break;

        /* REG LIMITED SERVICE״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(pstAcInfoChangeInd);
            break;

        /* GMM_DEREGISTERED_ATTACH_NEEDED״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(pstAcInfoChangeInd);
            break;

        /* REG NORMAL״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(pstAcInfoChangeInd);
            break;

        /* GMM_REGISTERED_UPDATE_NEEDED״̬�յ�RRMM_W_INFO_CHANGE_IND�Ĵ��� */
        case GMM_REGISTERED_UPDATE_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(pstAcInfoChangeInd);
            break;
        default :
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
            break;
    }

    NAS_GMM_ComProcAcInfoChgInd(pstAcInfoChangeInd);

}

NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_GMM_GetRegUptNeededPsSrvStatus()
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* �����ǰRAI���ϴγɹ�ע���RAI��ͬ��UPDATE״̬ΪU1��OTHER������Ϊ�������񣬷���Ϊ���Ʒ��� */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
            return MM_COM_SRVST_LIMITED_SERVICE_REGION;
        }
        else
        {
            return MM_COM_SRVST_LIMITED_SERVICE;
        }
    }
}
VOS_VOID NAS_GMM_ProcSmDataReq_RAUInit(
    VOS_VOID                           *pSmDataReqMsg
)
{
    VOS_UINT8                           ucMsgType;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_GMM_ProcSmDataReq_RAUInit:NORMAL:Gmm receive SM Data Req.");

    /* ��ȥ������ܻ���SM STATUS��Ϣ,������ʱ���̷�������,û������ʱ����;
       ���򻺴���Ϣ */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
    if ((SM_DEACT_PDP_CONTEXT_ACC == ucMsgType)
     || (SM_STATUS                == ucMsgType))
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
        }
    }
    else
    {
        Gmm_BufSmDataReqMsg(pSmDataReqMsg);
    }
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_Gmm_IsPtmsiMappedFromGuti(VOS_VOID)
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* �ж�GUPTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
     && (VOS_OK == ulGetGutiRst) )
    {
        return VOS_TRUE;
    }

    if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
     && (VOS_FALSE == ulLocalPtmsiFlg)
     && (VOS_OK == ulGetGutiRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
#endif



/*****************************************************************************
 �� �� ��  : NAS_GMM_FreeBufferCmMsg
 ��������  : �ͷŻ����CM��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��22��
    ��    ��   : l5478
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_GMM_FreeBufferCmMsg(VOS_VOID)
{
    VOS_VOID                           *pAddr;                                              /* ����ָ��                                 */

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����ServiceRequestԭ��           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* ֪ͨRABM���                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* ��ȡServiceRequestԭ���ַ               */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* ����б�����SmDataReqԭ��                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_FreeBufferCmMsg(): Clear cached SM data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* ���������־                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* ��ȡSmDataReqԭ���ַ                    */
        Gmm_MemFree(pAddr);                                                     /* ������buffer�����е���Ϣ�ͷ�             */
    }
}


VOS_UINT32 NAS_GMM_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* ����������������MMC��Ҫ����enable LTE��
    (1)����disable LTE�ı��Ϊ��
    (2)PS����Ч
    (3)USIM�� */

    /* ��ȡLTE��ʹ��״̬ */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* �������ʱ�Ѿ�����en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config�����ý�ֹ��LTE���򷵻�VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* ���֮ǰδdisable LTE,Ҳ����Ҫenable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* �����SIM��������ҪEnable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* disable ��enable lte�����ж�syscfg�Ƿ�֧��L */

    /* PS����Ч */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT8 NAS_GMM_GetAttachType(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictRegister;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* ps������attach��������ע�� */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return GMM_NULL_PROCEDURE;
    }

    /* ����CS��������ʱ������NORMAL ATTACH */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* ����ģʽI, ��PS�򵥶�ע��ɹ����յ�ϵͳ��Ϣ����Ҫ�ٴδ���COMBINED ATTACH */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_ATTACH_NORMAL);
        }

        return GMM_ATTACH_NORMAL;
    }

    if (((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
      || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)))
    {
        return GMM_ATTACH_NORMAL;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS��SIM��Ч                              */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {                                                                       /* CS���Ѿ�ע��                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* ���CSͨ���е�����                       */
                return GMM_ATTACH_NORMAL_CS_TRANS;
            }

            return GMM_ATTACH_WHILE_IMSI_ATTACHED;
        }

        if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
         || (VOS_TRUE == ucCsRestrictRegister))
        {
            /* CS��ATTACH����ֹ */
            return GMM_ATTACH_NORMAL;
        }

        /* CS��ATTACHû����ֹ */
        if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {
            /* CS����ͨ����*/
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            return GMM_ATTACH_NORMAL_CS_TRANS;
        }

        /* CS����ͨ���� */
        return  GMM_ATTACH_COMBINED;

    }

    return GMM_ATTACH_NORMAL;

}


VOS_VOID NAS_GMM_RcvMmCsConnectInd_RrcConnExist(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucPsRestrictRegFlg;

    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictRegFlg = NAS_MML_GetPsRestrictRegisterFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    enCurrNetRatType   = NAS_MML_GetCurrNetRatType();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucSimCsRegStatus)
     && (VOS_FALSE == ucPsRestrictRegFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    return;
}


VOS_VOID NAS_GMM_FreeWasSysInfo(VOS_VOID)
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return;
    }

    /* ���������־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* ������buffer�����е���Ϣ�ͷ� */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID NAS_GMM_SaveWasSysInfo(
    MMCGMM_SYS_INFO_IND_STRU         *pstSysInfo
)
{
    MMCGMM_SYS_INFO_IND_STRU         *pstHoldSysInfo = VOS_NULL_PTR;

    NAS_GMM_FreeWasSysInfo();

    pstHoldSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHoldSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveWasSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* �û����־ */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* ����ϵͳ��Ϣ */
    Gmm_MemCpy(pstHoldSysInfo, pstSysInfo, sizeof(MMCGMM_SYS_INFO_IND_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = (VOS_UINT32)pstHoldSysInfo;

    return;
}


VOS_UINT32 NAS_GMM_ProcSavedWasSysInfo()
{
    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT8 Gmm_MsgDistribute_ProcMmcMsg_GmmNull(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* �õ���Ϣͷ                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_MODE_CHANGE_REQ :
            break;

        case MMCGMM_PLMN_SEARCH_INITIATED :
            break;

        case MMCGMM_SYS_INFO_IND :
            break;

        case MMCGMM_GSM_SYS_INFO_IND :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        /* ������Ϣ��Ϊ�쳣��Ϣ */
        case MMCGMM_DETACH_REQ :
            NAS_GMM_SndMmcDetachCnf();
            ucRst = GMM_FALSE;

            break;

        case MMCGMM_ATTACH_REQ :
            NAS_GMM_SndMmcAttachCnf();
            ucRst = GMM_FALSE;

            break;

        default:
            ucRst = GMM_FALSE;
            break;
    }

    return ucRst;
}




VOS_UINT8 NAS_Gmm_IsValidMmcMsg_GmmTcActive(
    VOS_VOID                           *pRcvMsg                                 /* ������Ϣʹ�õ�ͷ��ַ����                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* ����MSG_HEADER_STRU����ָ��              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* �õ���Ϣͷ                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        case MMCGMM_SUSPEND_IND :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_ATTACH_REQ :
            break;

        /* ������Ϊ��Ϣ�Ƿ��������� */
        default:
            ucRst = GMM_FALSE;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_Gmm_IsInvalidMmcMsg_GmmTcActive:WARN:INVALID MSG");
            break;
    }

    return ucRst;
}


VOS_VOID NAS_Gmm_ClearPendingPdpStatus(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearCtx;
    VOS_UINT32                          i;

    pstPsBearCtx = NAS_MML_GetPsBearerCtx();

    /* ������Ϣ��pdp״̬����MML��ȫ�ֱ��� g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (VOS_TRUE == pstPsBearCtx[i].ucPsActPending)
        {
            pstPsBearCtx[i].ucPsActPending = VOS_FALSE;
        }

        if (VOS_TRUE == pstPsBearCtx[i].ucPsDeactPending)
        {
            pstPsBearCtx[i].ucPsDeactPending = VOS_FALSE;
        }
    }

    return;
}
VOS_VOID  NAS_GMM_ClearAuthInfo(VOS_VOID)
{
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;

    /* 24.008 4.7.7.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3316, if running, shall be stopped:
    -   if the mobile station enters the GMM states GMM-DEREGISTERED or GMM-NULL.
    */
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��"RES���ڱ�־ "��Ϊ0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* ��"RAND���ڱ�־ "��Ϊ0                   */
    Gmm_TimerStop(GMM_TIMER_T3316);

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG == (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG & g_GmmReqCnfMng.ucCnfMask))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
        Gmm_TimerStop(GMM_TIMER_PROTECT);
    }


    return;
}

/*lint -restore */

VOS_UINT32  NAS_GMM_IsNeedProcRelInd(
    RRMM_REL_IND_STRU       *pstRrRelInd
)
{

    /* �������PS��,GMM����Ҫ���� */
    if (RRC_NAS_PS_DOMAIN != pstRrRelInd->ulCnDomainId)
    {
        return VOS_FALSE;
    }


    /* ����������¼���״̬�ȴ�est_cnf������rel causeΪRRC_REL_CAUSE_NAS_DATA_ABSENT������������:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */

    /* ���GMMû�ڵȽ�����est_cnf����Ҫ�������� */
    if (GMM_RRC_RRMM_EST_CNF_FLG !=
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        return VOS_TRUE;
    }

    /* ���rel cause����RRC_REL_CAUSE_NAS_DATA_ABSENT����Ҫ�������� */
    if (RRC_REL_CAUSE_NAS_DATA_ABSENT != pstRrRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    /* ״̬����init״̬����Ҫ�������� */
    if ( (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;

    pstNasMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if (MMCGMM_SUSPEND_IND == pstNasMsgHeader->ulMsgName)
    {
        GMM_LOG_INFO("NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension:Receive MMCGMM_SUSPEND_IND in GMM_GPRS_SUSPENSION state.");
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if (MMCGMM_POWER_OFF_REQ == pstNasMsgHeader->ulMsgName)
    {
        GMM_BufferMsgDump();
        Gmm_TimerStop(GMM_TIMER_ALL);
        Gmm_TimerStart(GMM_TIMER_1S);
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;
        g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;
        return VOS_TRUE;
    }
    else if ( MMCGMM_PLMN_SEARCH_INITIATED == pstNasMsgHeader->ulMsgName )
    {
        /* ���к���Ĵ���Ǩ�Ƶ�����״̬ */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if ( MMCGMM_DETACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        /* ���к���Ĵ���Ǩ�Ƶ�����״̬ */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }


    /* �յ�MMCGMM_ATTACH_REQ��Ϣ���򲻽��л��棬����ֱ�ӻظ�Attach�ɹ���
       ������פ��������������Attach */
    else if ( MMCGMM_ATTACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }

    else if (( MMCGMM_GSM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName )
          || ( MMCGMM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName ) )
    {
        /* ͣHO�ȴ�ϵͳ��Ϣ��ʱ��,����ϵͳ��Ϣ */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);
    }
    else
    {
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID  NAS_GMM_RcvMmcVoiceDomainChangeNotify(
    struct MsgCB                       *pRcvMsg
)
{
    /* ���Э���½�:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    VOS_INT8                            cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain���ϴη���ע��ʱ����ͬ������Ҫ����RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* ��ǰ�Ѿ�����ʱ���������� */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU))
    {
        Gmm_TimerStop(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        return;
    }

    /* �������CSҵ����ֱ�ӷ��� */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* ������ڷ���CSҵ����������ʱ����ҵ����ʧ��������ʱ������RAU��
       ҵ����ɹ���ʱ����ʱʱ��ֱ�ӷ��� */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
