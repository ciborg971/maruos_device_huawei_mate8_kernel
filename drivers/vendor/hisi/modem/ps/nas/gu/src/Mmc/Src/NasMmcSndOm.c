
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasComm.h"

#include "NasMmcSndOm.h"
#include "MM_Ext.h"
#include "GmmExt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcCtx.h"
#include "NasMmcProcUsim.h"

#include  "NasMmlCtx.h"

#include "NasMmcFsmMainTbl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_SND_OM_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_LogMmcState
 ��������  : ��ӡ��MMC���ڲ�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��1��13��
   ��    ��   : zhoujun /40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_LogMmcFsmInfo( VOS_VOID )
{
    NAS_MMC_LOG_FSM_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_FSM_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogMmcFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FSM_INFO_IND;
    pstMsg->enFsmId                     = NAS_MMC_GetCurrFsmId();
    pstMsg->ulTopState                  = NAS_MMC_GetFsmTopState();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}

#if (FEATURE_LTE == FEATURE_ON)

VOS_VOID NAS_MMC_LogGutiInfo(
    NAS_LMM_GUTI_STRU                  *pstGuti
)
{
    NAS_MMC_LOG_GUTI_INFO_STRU         *pstGutiMsg = VOS_NULL_PTR;

    pstGutiMsg = (NAS_MMC_LOG_GUTI_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_GUTI_INFO_STRU));
    if ( VOS_NULL_PTR == pstGutiMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_LogGutiInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstGutiMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstGutiMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstGutiMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstGutiMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_GUTI_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstGutiMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_GUTI_INFO_IND;

    PS_MEM_CPY(&(pstGutiMsg->stGutiMsg), pstGuti, sizeof(NAS_LMM_GUTI_STRU));

    DIAG_TraceReport(pstGutiMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstGutiMsg);

    return;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_MMC_LogBufferQueueMsg
 ��������  : �����������Ϣ
 �������  : ulFullFlg:�����Ƿ��Ѿ����ı�־λ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��7��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    NAS_MMC_LOG_BUffER_MSG_INFO_STRU    *pstBufferMsg = VOS_NULL_PTR;
    NAS_MMC_MSG_QUEUE_STRU              *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (NAS_MMC_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_BUffER_MSG_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_LogBufferQueueMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsgQueue                               = NAS_MMC_GetCachMsgBufferAddr();
    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstBufferMsg);

    return;
}



VOS_VOID NAS_MMC_SndOutsideFixedContextData( VOS_VOID )
{
    NAS_MMC_FIXED_CONTEXT_MSG_STRU                         *pstFixedCtx;
    NAS_MML_CTX_STRU                                       *pstMmlCtx;
    NAS_MMC_CONTEXT_STRU                                   *pstMmcCtx;
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCnt;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount = sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU);
    ulItemCount = 0;

    pstFixedCtx = (NAS_MMC_FIXED_CONTEXT_MSG_STRU *)PS_ALLOC_MSG
                         (WUEPS_PID_MMC, sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU));

    if ( VOS_NULL_PTR == pstFixedCtx )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOutsideFixedContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOutsideFixedContextData: Alloc Fail.");
        PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);
        return;
    }

    pstPcreplayCompressCnt = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* ��ȡbuf��β��ַ�����ڼ���ʣ��ռ�*/
    pucEndBuf = (VOS_UINT8 *)(pucCompressBuf + ulCompressDataLen);

    /* ѹ�� fix data */
    pucDest  = pstPcreplayCompressCnt->aucData;

    /* ԭʼ���ݴ�С */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    pstMmlCtx  =  NAS_MML_GetMmlCtx();
    pstMmcCtx  =  NAS_MMC_GetMmcCtxAddr();

    /* ����IMEI������ */
    PS_MEM_CPY(pstFixedCtx->aucImeisv,
               pstMmlCtx->stMsCfgInfo.stMsCapability.aucImeisv,
               NAS_MML_MAX_IMEISV_LEN);

    /* ��������ģʽ */
    pstFixedCtx->enSelectionMode = pstMmcCtx->stPlmnSearchCtrl.enSelectionMode;

    pstFixedCtx->ucPsAutoAttachFlg = pstMmlCtx->stMsCfgInfo.stMsSysCfgInfo.ucPsAutoAttachFlg;

    /* �����ЧPLMN */
    PS_MEM_CPY(&(pstFixedCtx->stEquPlmnInfo),
               &(pstMmlCtx->stNetworkInfo.stEquPlmnInfo),
               sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* �����ЧRPLMN��ض��� */
    PS_MEM_CPY(&(pstFixedCtx->stRplmnCfg),
               &(pstMmlCtx->stMsCfgInfo.stCustomCfg.stRplmnCfg),
               sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    /* ������������ */
    pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen = pstMmlCtx->stMsCfgInfo.stMsCapability.stMsNetworkCapability.ucNetworkCapabilityLen;

    if (pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen > NAS_MML_MAX_NETWORK_CAPABILITY_LEN)
    {
        pstFixedCtx->stMsNetworkCapability.ucNetworkCapabilityLen  = NAS_MML_MAX_NETWORK_CAPABILITY_LEN;
    }
    PS_MEM_CPY(pstFixedCtx->stMsNetworkCapability.aucNetworkCapability,
               pstMmlCtx->stMsCfgInfo.stMsCapability.stMsNetworkCapability.aucNetworkCapability,
               NAS_MML_MAX_NETWORK_CAPABILITY_LEN);


    /* ����BG���������Ϣ */
    PS_MEM_CPY(&(pstFixedCtx->stBGSrchCfg),
               &(pstMmlCtx->stMsCfgInfo.stCustomCfg.stBgSearchCfg),
               sizeof(NAS_MML_BG_SEARCH_CFG_INFO_STRU));

    /* NV��Ļָ�,�ָ����ٿ��� */
    pstFixedCtx->ulQuickStartFlag = NAS_MML_IsQuickStartFlg();


    /* ѹ��NAS_MMC_FIXED_CONTEXT_MSG_STRU */
    pucSrc      = (VOS_UINT8 *)pstFixedCtx;
    ulItemCount = sizeof(NAS_MMC_FIXED_CONTEXT_MSG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);
        return;
    }
    pucDest          += (ulCmLen);
    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCnt);

    pstPcreplayCompressCnt->ulReceiverPid      = WUEPS_PID_MMC;
    pstPcreplayCompressCnt->ulSenderPid        = WUEPS_PID_MMC;
    pstPcreplayCompressCnt->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCnt->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCnt->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCnt->ulMsgName          = MMCOM_FIXED_PART_CONTEXT;
    DIAG_TraceReport(pstPcreplayCompressCnt);

    PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
    PS_FREE_MSG(WUEPS_PID_MMC, pstFixedCtx);

}
VOS_VOID NAS_MMC_SndOutsideContextData( VOS_VOID )
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

    ulCount     = sizeof(NAS_MML_CTX_STRU)
                + sizeof(MM_SUB_LAYER_SHARE_STRU)
                + sizeof(NAS_MMC_CONTEXT_STRU)
                + sizeof(TAF_PLMN_ID_STRU);  /* ��Ҫ���� g_stSetRplmn������PC�ط� */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC, ulCompressDataLen);

    if(VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* ��ȡbuf��β��ַ�����ڼ���ʣ��ռ�*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;

    /* ѹ�� fix data */
    pucDest  = pstPcreplayCompressCtx->aucData;

    /* ԭʼ���ݴ�С */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* ѹ��MML context g_stNasMmlCtx*/
    pucSrc      = (VOS_UINT8 *)NAS_MML_GetMmlCtx();
    ulItemCount = sizeof(NAS_MML_CTX_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��g_MmSubLyrShare */
    pucSrc      = (VOS_UINT8 *)&g_MmSubLyrShare;
    ulItemCount = sizeof(MM_SUB_LAYER_SHARE_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* ѹ��MMC context g_stNasMmcCtx */
    pucSrc      = (VOS_UINT8 *)NAS_MMC_GetMmcCtxAddr();
    ulItemCount = sizeof(NAS_MMC_CONTEXT_STRU);

    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/

    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

#if (FEATURE_ON == FEATURE_LTE)
#ifdef WIN32
	/* PC������Ҫ����g_stSetRplmn���ڻط� */
    PS_MEM_CPY(pucDest,&g_stSetRplmn,sizeof(TAF_PLMN_ID_STRU));
#endif
#endif
    pucDest += sizeof(TAF_PLMN_ID_STRU);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_MMC;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = MMCOM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);


    PS_MEM_FREE(WUEPS_PID_MMC, pucCompressBuf);

}


VOS_VOID NAS_MMC_SndOmOtaCnf(
    VOS_UINT32                          ulErrCode,
    OM_NAS_OTA_REQ_STRUCT              *pstOtaReq
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-1, begin */
    VOS_UINT16                          usNasOtaCnfLen;
    NAS_OM_OTA_CNF_STRUCT              *pstNasOtaCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* �����ڴ� */
    usNasOtaCnfLen = sizeof(NAS_OM_OTA_CNF_STRUCT) - VOS_MSG_HEAD_LENGTH;

    pstNasOtaCnf   = (NAS_OM_OTA_CNF_STRUCT *)PS_ALLOC_MSG(WUEPS_PID_MMC, usNasOtaCnfLen);
    if ( VOS_NULL_PTR == pstNasOtaCnf )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_RcvOmOtaReq:WARNING: Alloc Memory Fail.");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstNasOtaCnf + VOS_MSG_HEAD_LENGTH, 0x00, usNasOtaCnfLen);

    /* ��д��Ϣ���� */
    pstNasOtaCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasOtaCnf->ulMsgId          = NAS_OM_OTA_CNF;
    pstNasOtaCnf->usOriginalId     = pstOtaReq->usOriginalId;
    pstNasOtaCnf->usTerminalId     = pstOtaReq->usTerminalId;
    pstNasOtaCnf->ulTimeStamp      = pstOtaReq->ulTimeStamp;
    pstNasOtaCnf->ulSN             = pstOtaReq->ulSN;

    pstNasOtaCnf->ulErrCode        = ulErrCode;

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstNasOtaCnf);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
    }
    else
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmOtaCnf: NAS_OM_OTA_CNF has been sent.");
    }

    return;
    /* Modified by wx270776 for OM�ں�, 2015-7-1, end */

}


VOS_VOID NAS_MMC_FillNasMmImsiInfo(
    MS_ID_STRUCT                       *pstMsIdMsg
)
{
    VOS_UINT8                           i = 0;
    VOS_UINT8                           j = 0;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    pstMsIdentity           = NAS_MML_GetSimMsIdentity();

    /* SIM������λ */
    if ( VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        pstMsIdMsg->ucLength        = 0;
        return ;
    }

    pstMsIdMsg->ucLength            = 15;
    pstMsIdMsg->ucMobileIDValue[0]  = (pstMsIdentity->aucImsi[1] & 0xF0) >> 4;

    i   = 1;
    j   = 2;

    for ( ; (i < pstMsIdMsg->ucLength) && (j < 9); i++)
    {
        if ( (2 * i) >= LEN_MOBILE )
        {
            break;
        }

        pstMsIdMsg->ucMobileIDValue[(2 * i) - 1]
                    = pstMsIdentity->aucImsi[j] & 0x0F;
        pstMsIdMsg->ucMobileIDValue[2 * i]
                    = pstMsIdentity->aucImsi[j] >> 4;
        j++;
    }

    return;
}
VOS_VOID NAS_MMC_FillNasSimUpdateStatusInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;

    pstSimStatus                = NAS_MML_GetSimStatus();

    /* ��дPS��Ŀ�״̬ */
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    switch (pstSimStatus->enPsUpdateStatus)
    {
        case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU1;
            break;

        case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU2;
            break;

        case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
        case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
            pstMsg->enGmmUpdateStatus   = UPDATE_STATUS_GU3;
            break;

        default:
            pstMsg->enGmmUpdateStatus   = GMM_UPDATE_STATUS_BUTT;
            break;
    }

    /* ��дCS��Ŀ�״̬ */
    switch (pstSimStatus->enCsUpdateStatus)
    {
        case NAS_MML_LOCATION_UPDATE_STATUS_UPDATED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U1;
            break;

        case NAS_MML_LOCATION_UPDATE_STATUS_NOT_UPDATED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U2;
            break;

        case NAS_MML_LOCATION_UPDATE_STATUS_PLMN_NOT_ALLOWED:
        case NAS_MML_LOCATION_UPDATE_STATUS_LOCATION_AREA_NOT_ALLOWED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U3;
            break;

        case NAS_MML_LOCATION_UPDATE_DISABLED:
            pstMsg->enMmUpdateStatus    = UPDATE_STATUS_U4;
            break;

        default:
            pstMsg->enMmUpdateStatus    = MM_UPDATE_STATUS_BUTT;
            break;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FillNasMmSimInfo
 ��������  : ���OM��ѯ��Ϣ��SIM����Ϣ��
 �������  : ��
 �������  : pstMsg:��ǰ��ѯ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMmSimInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT8                           i;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity;

    pstMsIdentity           = NAS_MML_GetSimMsIdentity();

    /* ��дPTMSI������ */
    for (i = 0; i < LEN_PTMSI; i++)
    {
        pstMsg->ucPtmsi[i]  = pstMsIdentity->aucPtmsi[i];
    }

    /* ��дTMSI������ */
    for (i = 0; i < LEN_TMSI; i++)
    {
        pstMsg->aucTmsi[i]  = pstMsIdentity->aucTmsi[i];
    }

    /* ��дIMSI������ */
    NAS_MMC_FillNasMmImsiInfo(&(pstMsg->IMSI));

    /* ��д������״̬ */
    NAS_MMC_FillNasSimUpdateStatusInfo(pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertNetworkModeToOm
 ��������  : ���ڲ�������ģʽ��Ϣת��Ϊ��ʾ��OM��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��12��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertNetworkModeToDispalyFormat(
    NAS_MML_NET_MODE_ENUM_UINT8         enNetworkMode,
    NET_OPERATE_MODE_ENUM_UINT8        *penNetOperateMode

)
{
    if ( NAS_MML_NET_MODE_I == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_1;
    }
    else if ( NAS_MML_NET_MODE_II == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_2;
    }
    else if ( NAS_MML_NET_MODE_III == enNetworkMode )
    {
        *penNetOperateMode = NET_OPERATE_MODE_3;
    }
    else
    {
        *penNetOperateMode = NET_OPERATE_MODE_BUTT;
    }
}




NAS_OM_PLMN_HUO_TYPE_ENUM_UINT32 NAS_MMC_GetPlmnHUOType(NAS_MML_PLMN_ID_STRU *pstPlmn)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                             *pstCampPlmnInfo;
    NAS_MML_PLMN_ID_STRU                                     stRPlmnId;

    if (VOS_FALSE == NAS_MML_IsPlmnIdValid(pstPlmn))
    {
        return NAS_MMC_HUO_INVALID_PLMN;
    }

    /* ��ȡRPLMN������Ϣ */
    pstCampPlmnInfo         = NAS_MML_GetCurrCampPlmnInfo();

    if (VOS_TRUE == NAS_MMC_GetRPlmn_PlmnSelectionStrategy(pstCampPlmnInfo->enNetRatType, &stRPlmnId))
    {
        if (VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstPlmn, &stRPlmnId))
        {
            return NAS_MMC_HUO_RPLMN;
        }
    }

    /* ����Ƿ���HOME PLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithHplmn(pstPlmn))
    {
        return NAS_MMC_HUO_HPLMN;
    }

    /* ����Ƿ��� UPLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithUplmn(pstPlmn))
    {
        return NAS_MMC_HUO_UPLMN;
    }

    /* ����Ƿ��� OPLMN */
    if (VOS_TRUE == NAS_MML_ComparePlmnIdWithOplmn(pstPlmn))
    {
        return NAS_MMC_HUO_OPLMN;
    }

    /* ����PLMN */
    return NAS_MMC_HUO_OTHER_PLMN;
}

VOS_VOID NAS_MMC_FillNasTinInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_LMM_INFO_STRU                   stLmmInfo;

    NAS_MMC_FSM_ID_ENUM_UINT32  enFsmId;
    VOS_UINT32                  ucMmcTopState;
    VOS_UINT8                   aucPtmsiAddr[20];

    PS_MEM_SET(&stLmmInfo, 0, sizeof(NAS_LMM_INFO_STRU));
    PS_MEM_SET(aucPtmsiAddr, 0x00, sizeof(aucPtmsiAddr));
    pstMsg->enTinType     = NAS_MML_GetTinType();
    pstMsg->stMsId.ulMsId = 0;


    enFsmId         = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    ucMmcTopState   = (VOS_UINT8)NAS_MMC_GetFsmTopState();


    /*�ػ�״̬�·�����Чֵ,���ܵ���NAS_Gmm_FillPtmsiIeForSnd����ӿ�*/
    if ( ( NAS_MMC_FSM_L1_MAIN == enFsmId )
      && ( NAS_MMC_L1_STA_NULL == ucMmcTopState ))
    {
        pstMsg->stMsId.ulMsId = 0;
        PS_MEM_SET(&(pstMsg->stMsId.stGuti),0xFF,sizeof(pstMsg->stMsId.stGuti));
        PS_MEM_SET(&(pstMsg->stMsId.stPtmsi),0xFF,sizeof(pstMsg->stMsId.stPtmsi));
        PS_MEM_SET((pstMsg->stMsId.aucImsi),0x00,sizeof(pstMsg->stMsId.aucImsi));

        return;
    }

    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return;
    }

    /* ����TIN TYPE��ֵ��д��Ӧ��TINֵ */
    if (NAS_MML_TIN_TYPE_PTMSI == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    }
    else if (NAS_MML_TIN_TYPE_GUTI == pstMsg->enTinType)
    {
        if ( VOS_TRUE == NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
        {
            PS_MEM_CPY(&(pstMsg->stMsId.stGuti), &(stLmmInfo.u.stGuti), sizeof(NAS_LMM_GUTI_STRU));
            pstMsg->stMsId.ulMsId |= NAS_MS_ID_GUTI_VALID;
        }
    }
    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;

        if ( VOS_TRUE == NAS_GMM_GetLteInfo( NAS_LMM_GUTI, &stLmmInfo ) )
        {
            PS_MEM_CPY(&(pstMsg->stMsId.stGuti), &(stLmmInfo.u.stGuti), sizeof(NAS_LMM_GUTI_STRU));
            pstMsg->stMsId.ulMsId |= NAS_MS_ID_GUTI_VALID;
        }
    }
    else if (NAS_MML_TIN_TYPE_INVALID == pstMsg->enTinType)
    {
        (VOS_VOID)NAS_Gmm_FillPtmsiIeForSnd(aucPtmsiAddr);
        PS_MEM_CPY((pstMsg->stMsId).stPtmsi.aucPtmsi,&aucPtmsiAddr[2],NAS_MAX_SIZE_PTMSI);
        pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    }
    else
    {
    }

#else
/*
    pstMsg->enTinType     = NAS_MML_TIN_TYPE_BUTT;
    pstMsg->stMsId.ulMsId = 0;
    NAS_Gmm_FillPtmsiIeForSnd( (pstMsg->stMsId).stPtmsi.aucPtmsi );
    pstMsg->stMsId.ulMsId |= NAS_MS_ID_PTMSI_IMSI_VALID;
    */
#endif
}



VOS_VOID NAS_MMC_FillNasMsNetworkInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampPlmnInfo;

    pstCampPlmnInfo         = NAS_MML_GetCurrCampPlmnInfo();

    /* פ��������Ϣ */


    pstMsg->ucRac           = pstCampPlmnInfo->ucRac;
    pstMsg->usLac           = ((pstCampPlmnInfo->stLai.aucLac[0] << 8) | (pstCampPlmnInfo->stLai.aucLac[1]));

    /* ����ģʽ��Ϣ */
    pstMsg->enPlmnSelMode   = NAS_MMC_GetPlmnSelectionMode();

    pstMsg->enPlmnType      = NAS_MMC_GetPlmnHUOType(&(pstCampPlmnInfo->stLai.stPlmnId));

    NAS_MMC_ConvertPlmnIdToOmDispalyFormat(&(pstCampPlmnInfo->stLai.stPlmnId),
                                           &(pstMsg->SelectedPlmn));


    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    NAS_MMC_ConvertNetworkModeToDispalyFormat(pstCampPlmnInfo->enNetworkMode,
                                             &(pstMsg->enNetMode));
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */


}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FillNasMsMode
 ��������  : ���OM��ѯ��Ϣ���ֻ�ģʽ��Ϣ��
 �������  : ��
 �������  : pstMsg:��ǰ��ѯ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMsMode(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;

    enMsMode    = NAS_MML_GetMsMode();

    switch ( enMsMode )
    {
        case NAS_MML_MS_MODE_NULL:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_NULL;
            break;

        case NAS_MML_MS_MODE_PS_CS:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_A;
            if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
            {
                pstMsg->enUeOperMode = UE_OPERATE_MODE_B;
            }
            break;

        case NAS_MML_MS_MODE_PS_ONLY:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_CG;
            break;

        case NAS_MML_MS_MODE_CS_ONLY:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_CC;
            break;

        default:
            pstMsg->enUeOperMode = UE_OPERATE_MODE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_MMC,
            "NAS_MMC_FillNasMsMode:WARNING: enMsMod is Error");
            break;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FillNasImeiInfo
 ��������  : ���OM��ѯ��Ϣ��IMEI��Ϣ��
 �������  : ��
 �������  : pstMsg:��ǰ��ѯ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasImeiInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucCheckData;
    NAS_MML_MS_CAPACILITY_INFO_STRU    *pstMsCapacility;

    pstMsg->IMEI.ucLength   = LEN_MOBILE - 1;
    pstMsg->IMEISV.ucLength = LEN_MOBILE;
    pstMsCapacility         = NAS_MML_GetMsCapability();
    ucCheckData             = 0;

    for (i = 0; i < (LEN_MOBILE - 2); i += 2)
    {
        ucCheckData += (VOS_UINT8)((pstMsCapacility->aucImeisv[i]
                    + ((pstMsCapacility->aucImeisv[i + 1] * 2) / 10))
                    + ((pstMsCapacility->aucImeisv[i + 1] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData % 10)) % 10;

    pstMsg->IMEI.ucMobileIDValue[14] = ucCheckData;
    pstMsg->IMEI.ucMobileIDValue[15] = 0;


    for (i = 0; i < (LEN_MOBILE - 2); i++)
    {
        pstMsg->IMEI.ucMobileIDValue[i]     = pstMsCapacility->aucImeisv[i];
        pstMsg->IMEISV.ucMobileIDValue[i]   = pstMsCapacility->aucImeisv[i];
    }

    pstMsg->IMEISV.ucMobileIDValue[14]      = pstMsCapacility->aucImeisv[14];
    pstMsg->IMEISV.ucMobileIDValue[15]      = pstMsCapacility->aucImeisv[15];

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_FillNasMsCfgInfo
 ��������  : ���OM��ѯ��Ϣ���ֻ�������Ϣ��
 �������  : ��
 �������  : pstMsg:��ǰ��ѯ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID NAS_MMC_FillNasMsCfgInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* ��дIMEI���� */
    NAS_MMC_FillNasImeiInfo(pstMsg);


    /* ��д�ֻ�ģʽ���� */
    NAS_MMC_FillNasMsMode(pstMsg);
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ConvertPlmnIdToOmDispalyFormat
 ��������  : ���ڲ���ʽ��PlmnIDת��ΪOM��ʾ�õĸ�ʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MMC_ConvertPlmnIdToOmDispalyFormat(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    PLMN_ID_STRUCT                     *pstOmPlmnIdFormat
)
{
    pstOmPlmnIdFormat->aucMccDigit[0] = (VOS_UINT8)(pstPlmnId->ulMcc & 0x0F);
    pstOmPlmnIdFormat->aucMccDigit[1] = (VOS_UINT8)((pstPlmnId->ulMcc >> 8) & 0x0F);
    pstOmPlmnIdFormat->aucMccDigit[2] = (VOS_UINT8)((pstPlmnId->ulMcc >> 16) & 0x0F);

    pstOmPlmnIdFormat->aucMncDigit[0] = (VOS_UINT8)(pstPlmnId->ulMnc & 0x0F);
    pstOmPlmnIdFormat->aucMncDigit[1] = (VOS_UINT8)((pstPlmnId->ulMnc >> 8) & 0x0F);
    pstOmPlmnIdFormat->aucMncDigit[2] = (VOS_UINT8)((pstPlmnId->ulMnc >> 16) & 0x0F);

    pstOmPlmnIdFormat->ucMncCount = 3;

    if (0x0F == pstOmPlmnIdFormat->aucMncDigit[2])
    {
        pstOmPlmnIdFormat->ucMncCount = 2;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_FillNasServiceStatus
 ��������  : ��дNAS�ڲ�����״̬
 �������  : ��
 �������  : pstMsg:����д����Ϣ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��23��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ

*****************************************************************************/
VOS_VOID NAS_MMC_FillNasServiceStatus(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    NAS_MMC_SERVICE_INFO_CTX_STRU      *pstServiceStatus = VOS_NULL_PTR;

    pstServiceStatus = NAS_MMC_GetServiceInfo();

    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    if ( ( NAS_MMC_NORMAL_SERVICE == pstServiceStatus->enCsCurrService)
      || ( NAS_MMC_NORMAL_SERVICE == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_NORMAL_SERVICE;
    }
    else if ( ( NAS_MMC_NO_SERVICE == pstServiceStatus->enCsCurrService)
           && ( NAS_MMC_NO_SERVICE == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_NO_SERVICE;
    }
    else if ( ( NAS_MMC_LIMITED_SERVICE_REGION == pstServiceStatus->enCsCurrService)
           || ( NAS_MMC_LIMITED_SERVICE_REGION == pstServiceStatus->enPsCurrService))
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_REGIONAL_LIMITED_SERVICE;
    }
    else
    {
        pstMsg->enServiceStatus     = NAS_OM_SERVICE_STATE_LIMITED_SERVICE;
    }
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
}



VOS_VOID NAS_MMC_FillOmAvailPlmnList(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    VOS_UINT32                              i;
    VOS_UINT32                              j;
    VOS_UINT32                              ulPlmnCnt;
    AVAILABLE_PLMN_STRUCT                  *pstPlmnAddr = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enNetRat;
    NAS_MMC_NET_STATUS_ENUM_UINT8           enNetExistFlag;
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU  *pstPlmnSelectionList = VOS_NULL_PTR;

    ulPlmnCnt           = 0;
    enNetExistFlag      = NAS_MMC_NET_STATUS_BUTT;
    enNetRat            = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ֻ������״̬������ʱ�Ż���ڿ��������б� */
    if ( NAS_MMC_FSM_PLMN_SELECTION != NAS_MMC_GetCurrFsmId())
    {
        if (VOS_TRUE == NAS_MMC_IsNormalServiceStatus())
        {
            pstPlmnAddr = &(pstMsg->AvailablePlmn[ulPlmnCnt]);

            NAS_MMC_ConvertPlmnIdToOmDispalyFormat(NAS_MML_GetCurrCampPlmnId(),
                                                   &(pstPlmnAddr->Plmn));

            pstPlmnAddr->ucRat = NAS_MML_GetCurrNetRatType();

            ulPlmnCnt++;
        }

        pstMsg->ucAvailPlmnNum = (VOS_UINT8)ulPlmnCnt;

        return;
    }

    pstPlmnSelectionList = NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection();

    for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
    {
        for (j = 0; j < pstPlmnSelectionList->astPlmnSelectionList[i].ucRatNum; j++)
        {
            if ( ulPlmnCnt >= MAX_AVAILABEL_PLMN_NUM )
            {
                break;
            }

            /* ֻ��Ҫ�������ڵ����� */
            enNetExistFlag = pstPlmnSelectionList->astPlmnSelectionList[i].astPlmnRatInfo[j].enNetStatus;
            enNetRat       = pstPlmnSelectionList->astPlmnSelectionList[i].astPlmnRatInfo[j].enRatType;

            if  ( ( NAS_MMC_NET_STATUS_SEARCHED_EXIST     == enNetExistFlag)
               || ( NAS_MMC_NET_STATUS_SEARCHED_REGISTERED == enNetExistFlag ))
            {
                pstPlmnAddr = &(pstMsg->AvailablePlmn[ulPlmnCnt]);

                NAS_MMC_ConvertPlmnIdToOmDispalyFormat(&(pstPlmnSelectionList->astPlmnSelectionList[i].stPlmnId),
                                                       &(pstPlmnAddr->Plmn));

                pstPlmnAddr->ucRat = enNetRat;

                ulPlmnCnt++;

            }
        }
    }

    pstMsg->ucAvailPlmnNum = (VOS_UINT8)ulPlmnCnt;
}



VOS_VOID NAS_MMC_BuildNasOmInfo(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* ��дSIM����Ϣ */
    NAS_MMC_FillNasMmSimInfo(pstMsg);

    /* ��дMS ������Ϣ */
    NAS_MMC_FillNasMsCfgInfo(pstMsg);

    /* ��д��ǰפ��������Ϣ */
    NAS_MMC_FillNasMsNetworkInfo(pstMsg);

    /* ��дMM��״̬����״̬ */
    NAS_MM_FillNasMmState(pstMsg);

    /* ��дGMM��״̬����״̬ */
    NAS_GMM_FillNasGmmState(pstMsg);

    /* ��дTIN TYPE��MSID*/
    NAS_MMC_FillNasTinInfo(pstMsg);

    /* ��дMMC��״̬����״̬ */
    /* �˴���Ҫ��OM�����޸�MMC�ڲ��ӿ� */
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    pstMsg->enMmcFsmId = (VOS_UINT8)NAS_MMC_GetCurrFsmId();
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
    pstMsg->ucMmcState = (VOS_UINT8)NAS_MMC_GetFsmTopState();

    /* ��д���õ����� */
    NAS_MMC_FillOmAvailPlmnList(pstMsg);

    /* ��д��ǰ����״̬ */
    NAS_MMC_FillNasServiceStatus(pstMsg);

}


/* Added by wx270776 for OM�ں�, 2015-7-21, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_SndOmIndMsg
 ��������  : ����OM�Ĳ�ѯ��Ϣ͸����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��21��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_MMC_SndOmIndMsg(VOS_VOID)
{
    NAS_OM_MM_IND_STRU                  stNasOmMmInd;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    PS_MEM_SET(&stNasOmMmInd, 0x00, sizeof(NAS_OM_MM_IND_STRU));

    /* �����Ϣ���� */
    NAS_MMC_BuildNasOmInfo(&stNasOmMmInd);
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    stNasOmMmInd.enPrimId           = ID_NAS_OM_MM_CONFIRM;
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
    stNasOmMmInd.usToolsId          = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_MMC), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_MMC;
    stDiagTransInd.ulMsgId          = ID_NAS_OM_MM_CONFIRM;
    stDiagTransInd.ulLength         = sizeof(NAS_OM_MM_IND_STRU);
    stDiagTransInd.pData            = &stNasOmMmInd;

    /* ������Ϣ */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmIndMsg:WARNING: Send msg fail.");
    }

    return ulRet;
}
/* Added by wx270776 for OM�ں�, 2015-7-21, end */

VOS_VOID NAS_MMC_SndOmInquireCnfMsg(
    ID_NAS_OM_INQUIRE_STRU             *pstOmInquireMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-1, begin */
    NAS_OM_MM_CONFIRM_STRU             *pstNasOmMmCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulSndOmRet;
    VOS_UINT32                          ulRet;

    /* 1. ��OM����IND��Ϣ */
    ulSndOmRet = NAS_MMC_SndOmIndMsg();

    /* 2. �򹤾߲�ظ�CNF��Ϣ */
    /* �����ڴ� */
    ulMsgLen      = sizeof(NAS_OM_MM_CONFIRM_STRU) - VOS_MSG_HEAD_LENGTH;

    pstNasOmMmCnf = (NAS_OM_MM_CONFIRM_STRU*)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstNasOmMmCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmInquireCnfMsg:Memory Allocate fail!");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstNasOmMmCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* ��д��Ϣ���� */
    pstNasOmMmCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstNasOmMmCnf->ulMsgId          = ID_NAS_OM_MM_CONFIRM;
    pstNasOmMmCnf->usOriginalId     = pstOmInquireMsg->usOriginalId;
    pstNasOmMmCnf->usTerminalId     = pstOmInquireMsg->usTerminalId;
    pstNasOmMmCnf->ulTimeStamp      = pstOmInquireMsg->ulTimeStamp;
    pstNasOmMmCnf->ulSN             = pstOmInquireMsg->ulSN;
    pstNasOmMmCnf->enResult         = (NAS_OM_RESULT_ENUM_UINT32)ulSndOmRet;


    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstNasOmMmCnf);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmInquireCnfMsg:WARNING: Send msg fail.");
    }

    return;
    /* Modified by wx270776 for OM�ں�, 2015-7-1, end */


}



VOS_VOID NAS_MMC_SndOmPlmnSelectionList(
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                  *pstPlmnSelectionList,
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList
)
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              k;
    VOS_UINT32                                              ulPlmnNum;
    NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU               *pstMsg               = VOS_NULL_PTR;
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU                  *pstPlmnSelectionInfo = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_PLMN_SELECTION_LIST_MSG_STRU)));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogPlmnSelectionList_PlmnSelection:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_PLMN_SELECTION_LIST;

    ulPlmnNum = 0x0;

    for (i = 0; i < pstPlmnSelectionList->usSearchPlmnNum; i++)
    {
        if (i > (NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST/NAS_MML_MAX_RAT_NUM))
        {
            break;
        }

        pstPlmnSelectionInfo = &(pstPlmnSelectionList->astPlmnSelectionList[i]);

        /* ��SYSCFG���õĽ��뼼�����ȼ����β��� */
        for (k = 0; k < pstPrioRatList->ucRatNum; k++)
        {
            /* ���β���һ�����������֧�ֵĽ��뼼�� */
            for (j = 0; j < pstPlmnSelectionInfo->ucRatNum; j++)
            {
                /* ������ȵĽ��뼼���뵱ǰ���ҵ�����֧�ֵĽ��뼼����ͬ */
                if (pstPrioRatList->aucRatPrio[k] == pstPlmnSelectionInfo->astPlmnRatInfo[j].enRatType)
                {
                    pstMsg->astPlmnSelectionList[ulPlmnNum].ulMcc       = pstPlmnSelectionInfo->stPlmnId.ulMcc;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].ulMnc       = pstPlmnSelectionInfo->stPlmnId.ulMnc;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enPlmnType  = pstPlmnSelectionInfo->enPlmnType;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enRatType   = pstPlmnSelectionInfo->astPlmnRatInfo[j].enRatType;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enNetStatus = pstPlmnSelectionInfo->astPlmnRatInfo[j].enNetStatus;
                    pstMsg->astPlmnSelectionList[ulPlmnNum].enQuality   = pstPlmnSelectionInfo->astPlmnRatInfo[j].enQuality;

                    ulPlmnNum ++;
                }
            }

        }
    }

    pstMsg->ulPlmnNum                   = ulPlmnNum;

    pstMsg->stMsgHeader.ulLength        = sizeof(pstMsg->stMsgHeader.ulMsgName)
                                          + sizeof(pstMsg->ulPlmnNum)
                                          + (ulPlmnNum * sizeof(NAS_MMC_LOG_PLMN_SELECTION_LIST_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}
VOS_VOID NAS_MMC_LogRplmnRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogRplmnRelatedInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_RPLMN_RELATED_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_RPLMN_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��ȡLTE��RPLMN */
    (VOS_VOID)NAS_MML_GetLteRPlmn(&pstMsg->stGetLteRplmn);

    /* ��ȡGU��RPLMN */
    (VOS_VOID)NAS_MML_GetGURPlmn(&pstMsg->stGetGuRplmn);

    /* ��ӡRPLMN��������Ϣ */
    PS_MEM_CPY(&pstMsg->stRplmnCfg, NAS_MML_GetRplmnCfg(), sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    /* CS�����һ��ע��ɹ���LAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��LAI�����ֵΪ��Чֵ */
    PS_MEM_CPY(&pstMsg->stLastSuccLai, NAS_MML_GetCsLastSuccLai(), sizeof(NAS_MML_LAI_STRU));

    /* PS�����һ��ע��ɹ���RAI��Ϣ��ע��ʧ�ܺ���Ҫɾ��RAI�����ֵΪ��Чֵ */
    PS_MEM_CPY(&pstMsg->stLastSuccRai, NAS_MML_GetPsLastSuccRai(), sizeof(NAS_MML_RAI_STRU));

    /* PS UPDATE STATUS */
    pstMsg->enPsUpdateStatus   = NAS_MML_GetPsUpdateStatus();

    /* CS UPDATE STATUS */
    pstMsg->enCsUpdateStatus   = NAS_MML_GetCsUpdateStatus();

    /* MS MODE */
    pstMsg->enMsMode            = NAS_MML_GetMsMode();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}


VOS_VOID NAS_MMC_LogForbiddenPlmnRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU           *pstMsg       = VOS_NULL_PTR;
    NAS_MML_CUSTOM_CFG_INFO_STRU                           *pstCustomCfg = VOS_NULL_PTR;

    pstCustomCfg = NAS_MML_GetCustomCfg();

    pstMsg = (NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogForbiddenPlmnRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FORBIDDEN_PLMN_RELATED_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FORBIDDEN_PLMN_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��ӡFORB PLMN����Ϣ */
    PS_MEM_CPY(&pstMsg->stSimForbidenInfo, NAS_MML_GetForbidPlmnInfo(), sizeof(NAS_MML_SIM_FORBIDPLMN_INFO_STRU));

    /* ��ӡROMA CFG����Ϣ */
    PS_MEM_CPY(&pstMsg->stRoamCfg, NAS_MML_GetRoamCfg(), sizeof(NAS_MML_ROAM_CFG_INFO_STRU));

    /* ��ӡ������������,�����������������Ϣ */
    PS_MEM_CPY(&pstMsg->stPlmnLockCfg, NAS_MML_GetPlmnLockCfg(), sizeof(NAS_MML_PLMN_LOCK_CFG_INFO_STRU));

    /* ��ӡLTE�������ε���Ϣ */
    PS_MEM_CPY(&pstMsg->stLteRoamCfg, &(pstCustomCfg->stLteCustomCfgInfo.stLteRoamCfg), sizeof(NAS_MML_LTE_INTERNATION_ROAM_CFG_STRU));

    /* ��ӡ��ֹ���뼼������Ϣ */
    PS_MEM_CPY(&pstMsg->stRatFirbiddenStatusCfg, &(pstCustomCfg->stRatFirbiddenStatusCfg), sizeof(NAS_MML_RAT_FORBIDDEN_STATUS_STRU));

    /* ��ӡDISABLE LTE�������Ϣ����DISABLE LTEʱ�����������Ӱ�� */
    pstMsg->enLteCapabilityStatus = NAS_MML_GetLteCapabilityStatus();
    pstMsg->enDisableLteReason    = NAS_MML_GetDisableLteReason();
    pstMsg->ulDisableLteRoamFlg   = NAS_MML_GetDisableLteRoamFlg();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}



VOS_VOID NAS_MMC_LogRplmnCfgInfo(VOS_VOID)
{
    NAS_MMC_LOG_RPLMN_CFG_INFO_STRU                      *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_RPLMN_CFG_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU)));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogRplmnCfgInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_RPLMN_CFG_INFO;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_RPLMN_CFG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��ӡRPLMN��������Ϣ */
    PS_MEM_CPY(&pstMsg->stRplmnCfg, NAS_MML_GetRplmnCfg(), sizeof(NAS_MML_RPLMN_CFG_INFO_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}




VOS_VOID NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo(
    NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU                    *pstFsmPlmnSelectionCtx
)
{
    NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU    *pstMsg       = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstFsmPlmnSelectionCtx )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo:ERROR:pstFsmPlmnSelectionCtx is null pointer!");

        return;
    }

    pstMsg = (NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmPlmnSelectionCtxRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FSM_PLMN_SELECTON_CTX_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FSM_PLMN_SELECTION_CTX_RELATED_INFO;

    pstMsg->ucAbortFlg                  = pstFsmPlmnSelectionCtx->ucAbortFlg;
    pstMsg->ucRelRequestFlg             = pstFsmPlmnSelectionCtx->ucRelRequestFlg;
    pstMsg->ucInterSysSuspendRat        = pstFsmPlmnSelectionCtx->ucInterSysSuspendRat;
    pstMsg->ucSrvTrigPlmnSearchFlag     = pstFsmPlmnSelectionCtx->ucSrvTrigPlmnSearchFlag;
    PS_MEM_CPY(&pstMsg->stRegRlstInfo,      &pstFsmPlmnSelectionCtx->stRegRlstInfo,     sizeof(NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU));
    PS_MEM_CPY(pstMsg->astSearchRatInfo,   pstFsmPlmnSelectionCtx->astSearchRatInfo,  sizeof(NAS_MMC_RAT_SEARCH_INFO_STRU) * NAS_MML_MAX_RAT_NUM);
    PS_MEM_CPY(&pstMsg->stForbRoamLaInfo,   &pstFsmPlmnSelectionCtx->stForbRoamLaInfo,  sizeof(NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU));
    PS_MEM_CPY(&pstMsg->stForbGprsPlmn,     &pstFsmPlmnSelectionCtx->stForbGprsPlmn,    sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstMsg->stCsPsMode1ReCampLtePlmn,
               &pstFsmPlmnSelectionCtx->stCsPsMode1ReCampLtePlmn,  sizeof(NAS_MML_PLMN_ID_STRU));
    PS_MEM_CPY(&pstMsg->stCurrSearchingPlmn,&pstFsmPlmnSelectionCtx->stCurrSearchingPlmn,  sizeof(NAS_MML_PLMN_WITH_RAT_STRU));
    pstMsg->enCurrSearchingType         = pstFsmPlmnSelectionCtx->enCurrSearchingType;
    pstMsg->ucExistRplmnOrHplmnFlag     = pstFsmPlmnSelectionCtx->ucExistRplmnOrHplmnFlag;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}



VOS_VOID NAS_MMC_LogFsmL1MainCtxRelatedInfo(
    NAS_MMC_FSM_L1_MAIN_CTX_STRU       *pstFsmL1MainCtx
)
{
    NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    /* �쳣���� */
    if (VOS_NULL_PTR == pstFsmL1MainCtx )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmL1MainCtxRelatedInfo:ERROR:pstFsmL1MainCtx is null pointer!");

        return;
    }

    pstMsg = (NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogFsmL1MainCtxRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength            = sizeof(NAS_MMC_LOG_FSM_L1_MAIN_CTX_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = MMCOM_LOG_FSM_L1_MAIN_CTX_RELATED_INFO;

    PS_MEM_CPY(&pstMsg->stRegRsltInfo, &pstFsmL1MainCtx->stRegRsltInfo, sizeof(NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU));
    pstMsg->ulCurTimerCount                 = pstFsmL1MainCtx->ulCurTimerCount;
    pstMsg->ulCurHighRatHplmnTimerCount     = pstFsmL1MainCtx->ulCurHighRatHplmnTimerCount;
    pstMsg->ulCurNcellSearchTimerCount      = pstFsmL1MainCtx->ulCurNcellSearchTimerCount;
    pstMsg->ulCurHistorySearchTimerCount    = pstFsmL1MainCtx->ulCurHistorySearchTimerCount;
    pstMsg->enAvailableTimerType            = pstFsmL1MainCtx->enAvailableTimerType;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}
VOS_VOID NAS_MMC_LogHistoryRelatedInfo(VOS_VOID)
{
    NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU                  *pstMsg          = VOS_NULL_PTR;
    NAS_MMC_HISTORY_SEARCH_INFO_STRU                       *pstHistoryInfo  = VOS_NULL_PTR;

    pstHistoryInfo = NAS_MMC_GetHistorySearchInfo();

    pstMsg = (NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                          (sizeof(NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogHistoryRelatedInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength            = sizeof(NAS_MMC_LOG_HISTORY_RELATED_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = MMCOM_LOG_HISTORY_RELATED_INFO;

    PS_MEM_CPY(&(pstMsg->stHistorySearchInfo),    pstHistoryInfo, sizeof(NAS_MMC_HISTORY_SEARCH_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stGetGeoInfo.stGeoPlmn), NAS_MMC_GetGeoPlmn(), sizeof(NAS_MML_PLMN_WITH_RAT_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}




VOS_VOID  NAS_MMC_SndOmMmcTimerStatus(
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus,
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    NAS_MMC_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_TIMER_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmMmcTimerStart:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;

    pstMsg->stMsgHeader.ulLength        = NAS_MML_MSG_TIMER_ID_LENGTH + NAS_MML_MSG_NAME_ID_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->enTimerId                   = enTimerId;
    pstMsg->ucReserve                   = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}


VOS_VOID NAS_MMC_SndOmEquPlmn(VOS_VOID)
{
    VOS_UINT8                          *pucEplmnContent = VOS_NULL_PTR;
    VOS_UINT32                          i;
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList = VOS_NULL_PTR;
    NAS_MML_SIM_FORMAT_PLMN_ID          stReportPlmn;                           /* ��Plmn��Sim��ʽ��ͬ */
    VOS_UINT32                          ulSndEplmnNum;
    VOS_UINT32                          ulPlmnIdx;

    pstEplmnList  = NAS_MML_GetEquPlmnList();

    /* �ϱ�RPlmn+Eplmn��ǰ���� */
    ulSndEplmnNum  = pstEplmnList->ucEquPlmnNum;

    if ( 0 == ulSndEplmnNum )
    {
        /* Ϊ�˷��͵�ǰ���� */
        ulSndEplmnNum = 1;
    }

    pucEplmnContent = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                                                NAS_MML_SIM_FORMAT_PLMN_LEN * ulSndEplmnNum);
    if( VOS_NULL_PTR == pucEplmnContent )
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmEquPlmn():Memory Alloc Error for pucEplmnContent ");
        return;
    }

    PS_MEM_SET(pucEplmnContent, 0, ulSndEplmnNum * NAS_MML_SIM_FORMAT_PLMN_LEN);

    ulPlmnIdx = 0;

    if (pstEplmnList->ucEquPlmnNum > 0)
    {
        for (i = 0; i < pstEplmnList->ucEquPlmnNum; i++)
        {
            if (VOS_TRUE == NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstEplmnList->astEquPlmnAddr[i]),
                                               (VOS_UINT8)ulPlmnIdx, pstEplmnList->astEquPlmnAddr))
            {
                continue;
            }

            NAS_MMC_ConvertNasPlmnToSimFormat(&(pstEplmnList->astEquPlmnAddr[i]), &stReportPlmn);

            PS_MEM_CPY(pucEplmnContent + (ulPlmnIdx * NAS_MML_SIM_FORMAT_PLMN_LEN),
                      stReportPlmn.aucSimPlmn, NAS_MML_SIM_FORMAT_PLMN_LEN);

            ulPlmnIdx++;
        }
    }
    /* EPlmn������ʱ��ֻ��ӵ�ǰ���� */
    else
    {
        NAS_MMC_ConvertNasPlmnToSimFormat(NAS_MML_GetCurrCampPlmnId(), &stReportPlmn);

        PS_MEM_CPY(pucEplmnContent + (ulPlmnIdx * NAS_MML_SIM_FORMAT_PLMN_LEN),
                  stReportPlmn.aucSimPlmn, NAS_MML_SIM_FORMAT_PLMN_LEN);

        ulPlmnIdx++;
    }


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_EPLMN_LIST,
                    pucEplmnContent, (NAS_MML_SIM_FORMAT_PLMN_LEN * ulPlmnIdx));


    /* �ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_MMC, pucEplmnContent);

    return;
}
VOS_VOID NAS_MMC_SndOmInternalMsgQueueDetailInfo(
    NAS_MML_INTERNAL_MSG_QUEUE_STRU    *pInternalMsgQueue
)
{
    VOS_UINT32                                              ulMsgPnt;
    VOS_UINT8                                               ucHeader;
    VOS_UINT8                                               ucTail;

    ucHeader = pInternalMsgQueue->ucHeader;
    ucTail   = pInternalMsgQueue->ucTail;

    /* ��ӡ����Ϣ�����е����� */
    for (ulMsgPnt = ucHeader; ulMsgPnt != ucTail; ulMsgPnt = (ulMsgPnt + 1)%NAS_MML_MAX_MSG_QUEUE_SIZE)
    {
        DIAG_TraceReport(&pInternalMsgQueue->astNasMmMsgQueue[ulMsgPnt]);
    }

    return;
}
VOS_VOID  NAS_MMC_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
)
{
    NAS_MMC_LOG_INTER_MSG_INFO_STRU     *pstInterMsg = VOS_NULL_PTR;

    pstInterMsg = (NAS_MMC_LOG_INTER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC,
                             sizeof(NAS_MMC_LOG_INTER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstInterMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_MMC_SndOmInternalMsgQueueInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstInterMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInterMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstInterMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstInterMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_INTER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_INTER_MSG_INFO_IND;
    pstInterMsg->ucFullFlg                   = ucFullFlg;
    pstInterMsg->ucMsgLenValidFlg            = ucMsgLenValidFlg;

    DIAG_TraceReport(pstInterMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstInterMsg);

    return;
}


VOS_VOID  NAS_MMC_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
)
{
    NAS_MMC_GET_CACHE_FILE_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(NAS_MMC_GET_CACHE_FILE_STRU) + ulFileLen;

    pstMsg = (NAS_MMC_GET_CACHE_FILE_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmGetCacheFile:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ulFileId;

    pstMsg->ulFileLen                   = ulFileLen;

    PS_MEM_CPY(pstMsg->aucFileContent, pucFileContent, ulFileLen);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}

VOS_VOID  NAS_MMC_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus )
{
    NAS_MMC_DRX_TIMER_STAUTS_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(NAS_MMC_DRX_TIMER_STAUTS_STRU)  ;

    pstMsg = (NAS_MMC_DRX_TIMER_STAUTS_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmGetCacheFile:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_DRX_TIMER_STATUS_IND;
    PS_MEM_SET(pstMsg->aucReserve,0x00,sizeof(pstMsg->aucReserve));
    pstMsg->ucDrxTimerStatus            = ucDrxTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}


VOS_VOID  NAS_MMC_SndOmPlatformRatCap( VOS_VOID )
{
    NAS_MMC_PLATFORM_RAT_CAP_STRU          *pstMsg = VOS_NULL_PTR;
    NAS_MML_PLATFORM_RAT_CAP_STRU          *pstPlatformRatCap =VOS_NULL_PTR;
    VOS_UINT32                              ulMsgLen;

    pstPlatformRatCap   = NAS_MML_GetPlatformRatCap();
    ulMsgLen            = sizeof(NAS_MMC_PLATFORM_RAT_CAP_STRU);

    pstMsg = (NAS_MMC_PLATFORM_RAT_CAP_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMC, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndOmPlatformRatCap:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_MMC_PLATFORM_RAT_CAP;

    PS_MEM_CPY(&(pstMsg->stPlatformRatCap), pstPlatformRatCap, sizeof(NAS_MML_PLATFORM_RAT_CAP_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

}


#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_MMC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
 )
{
    OM_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* �ϱ�����Ϣ�ܳ��� */
    /*lint -e961*/
    ulMsgLen  = sizeof(OM_ERR_LOG_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulBufUseLen;
    /*lint +e961*/

    /* ��Ϣ�ռ����� */
    pstQryCnf = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmErrLogRptCnf: Alloc msg fail!");
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = WUEPS_PID_MMC;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    if (VOS_NULL_PTR != pbuffer)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstQryCnf))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmErrLogRptCnf: SEND MSG FAIL");
    }

    return;

}


VOS_VOID NAS_MMC_SndAcpuOmFtmRptInd(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulMsgLen;
    OM_FTM_REPROT_IND_STRU             *pstFtmRptInd = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FTM_REPROT_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + ulLen;
    /*lint +e961*/
    pstFtmRptInd = (OM_FTM_REPROT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_MMC, ulMsgLen);
    if (VOS_NULL_PTR == pstFtmRptInd)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmFtmRptInd: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstFtmRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFtmRptInd->ulSenderPid       = WUEPS_PID_MMC;
    pstFtmRptInd->ulMsgName         = ID_OM_FTM_REPROT_IND;
    pstFtmRptInd->ulMsgType         = OM_ERR_LOG_MSG_FTM_REPORT;
    pstFtmRptInd->ulMsgSN           = 0;
    pstFtmRptInd->ulRptlen          = ulLen;

    PS_MEM_CPY(pstFtmRptInd->aucContent, pucData, ulLen);

    /* ������Ϣ��ACPU OMģ�� */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMC, pstFtmRptInd))
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAcpuOmFtmRptInd: SEND MSG FIAL");
    }

    return;

}
VOS_VOID NAS_MMC_SndAcpuOmCurTmsi(VOS_VOID)
{
    VOS_UINT8                          *pucTmsi = VOS_NULL_PTR;
    NAS_FTM_TMSI_RPT_EVENT_STRU         stFtmTmsiRpt;

    /* ��ȡ��ǰ��TMSI */
    pucTmsi  = NAS_MML_GetUeIdTmsi();

    /* ��乤��ģʽ�ϱ���ͷ */
    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmTmsiRpt.stHeader,
                                   NAS_MML_MAX_TMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                   NAS_FTM_PROJECT_TMSI_RPT)

    PS_MEM_CPY(stFtmTmsiRpt.aucTmsi,   pucTmsi,  NAS_MML_MAX_TMSI_LEN);

    /* ͨ����ϢID_OM_FTM_REPROT_IND���͸�ACPU OM */
    NAS_MMC_SndAcpuOmFtmRptInd((VOS_UINT8*)&stFtmTmsiRpt,  sizeof(stFtmTmsiRpt));

    return;
}
VOS_VOID NAS_MMC_SndAcpuOmCurPtmsi(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi = VOS_NULL_PTR;
    NAS_FTM_PTMSI_RPT_EVENT_STRU        stFtmPtmsiRpt;

    /* ��ȡ��ǰ��TMSI/PTMSI */
    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    /* ��乤��ģʽ�ϱ���ͷ */
    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmPtmsiRpt.stHeader,
                                   NAS_MML_MAX_PTMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_MMC),
                                   NAS_FTM_PROJECT_PTMSI_RPT)

    PS_MEM_CPY(stFtmPtmsiRpt.aucPtmsi, pucPtmsi, NAS_MML_MAX_PTMSI_LEN);

    /* ͨ����ϢID_OM_FTM_REPROT_IND���͸�ACPU OM */
    NAS_MMC_SndAcpuOmFtmRptInd((VOS_UINT8*)&stFtmPtmsiRpt, sizeof(stFtmPtmsiRpt));
}

#endif

/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_LogForbLaWithValidPeriodListInfo
 ��������  : ����ֹLA��Чʱ���б���Ϣ���͵�OM
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_LogForbLaWithValidPeriodListInfo(VOS_VOID)
{
    NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU   *pstMsg  = VOS_NULL_PTR;

    pstMsg = (NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMC,
             (sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU)));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_LogForbLaWithValidPeriodListInfo:ERROR:Alloc Mem Fail.");

        return;
    }

    PS_MEM_SET(pstMsg, 0X00, sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MMC_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = MMCOM_LOG_FORB_LA_WITH_VALID_PERIOD_LIST_INFO;

    /* ��ӡ��ֹLA��Чʱ��������Ϣ */
    PS_MEM_CPY(&pstMsg->stForbLaWithValidPeriodCfg, NAS_MML_GetForbLaWithValidPeriodCfg(), 
               sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_CFG_INFO_LIST_STRU));

    /* ��ӡ��ֹLA��Чʱ���б���Ϣ */
    PS_MEM_CPY(&pstMsg->stForbLaWithValidPeriod, NAS_MML_GetForbLaWithValidPeriodList(),
               sizeof(NAS_MML_FORB_LA_WITH_VALID_PERIOD_LIST_STRU));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMC, pstMsg);

    return;
}
/* Added by z00359541 for CS REG FAIL FORB LA, 2015-9-23, end */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

