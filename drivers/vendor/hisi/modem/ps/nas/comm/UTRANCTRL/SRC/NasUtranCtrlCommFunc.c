

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
#include "NVIM_Interface.h"
#include "SysNvId.h"

#include "nasasapi.h"
#include "TcNasinterface.h"
#include "Nasrrcinterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasPdcpInterface.h"
#include "RabmExtFunc.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlInterface.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasRlcInterface.h"

#include "NasMmcCtx.h"
#include "NasUtranCtrlMain.h"
#include "NasMmlMsgProc.h"
#include "NasMmcComFunc.h"
#include "NasMmlLib.h"
#include "NasMmcProcUsim.h"

#include "NasMmcSndGuAs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_COMM_FUNC_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/


/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

RRC_NAS_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
)
{
    RRC_NAS_UTRAN_MODE_ENUM_UINT8       enRrcUtranMode;

    switch ( enNasUtranMode )
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_FDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_TDD;
            break;

        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode:UTRANMODE IS BUTT! ");
            /* ƽ̨��֧��GUʱ��Ĭ�ϸ�����㷢�͵�UtranModeΪTDD */
            enRrcUtranMode = RRC_NAS_UTRAN_MODE_TDD;

            break;
    }

    return enRrcUtranMode;
}

#if (FEATURE_ON == FEATURE_LTE)
MMC_LMM_UTRAN_MODE_ENUM_UINT8 NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enNasUtranMode
)
{
    MMC_LMM_UTRAN_MODE_ENUM_UINT8       enLmmUtranMode;

    switch ( enNasUtranMode )
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_FDD;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_TDD;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode:UTRANMODE IS BUTT! ");
            /* ƽ̨��֧��GUʱ��Ĭ�ϸ�LMM���͵�UtranModeΪTDD */
            enLmmUtranMode = MMC_LMM_UTRAN_MODE_TDD;
            break;
    }

    return enLmmUtranMode;
}

#endif  /* (FEATURE_ON == FEATURE_LTE) */


VOS_VOID NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(
    VOS_UINT8                           ucRbId,
    TTF_MEM_ST                         *pstData,
    VOS_UINT32                          ulDataBitLen
)
{
    /* ���ݷ��ͽ�� */
    VOS_UINT32                          ulDataSendRslt;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* ȡ�õ�ǰ��UTRANģʽ */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* Ĭ�����ݷ��ͽ�� */
    ulDataSendRslt = PS_FAIL;

    /* ���ݲ�ͬ��UTRANģʽ���ò�ͬ��API���д��� */
    switch ( enCurrentUtranMode )
    {
        /* Wģ�Ĵ��� */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            ulDataSendRslt = WTTF_PDCP_RcvRabmData(ucRbId, pstData, ulDataBitLen);
            break;

        /* TDģ�Ĵ��� */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            ulDataSendRslt = TPDCP_DATA_REQ(ucRbId, pstData, ulDataBitLen);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_AdaptPdcpDataReq:WARNING:UTRAN MODE NOT EXIST!");
            ulDataSendRslt = WTTF_PDCP_RcvRabmData(ucRbId, pstData, ulDataBitLen);
            break;
    }

    NAS_INFO_LOG2(WUEPS_PID_MMC, "NAS_UTRANCTRL_RABM_AdaptPdcpDataReq: Data Snd Failed! enCurrentUtranMode, ulDataSendRslt",
                  enCurrentUtranMode, ulDataSendRslt);

    return;
}



VOS_VOID NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize(
    VOS_UINT8                          ucRbId,
    VOS_UINT32                         ulPduSize,
    VOS_UINT8                          ucCrcSize,
    VOS_UINT32                        *pulUlPduSize
)
{
    /* ���ݷ��ͽ�� */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* ȡ�õ�ǰ��UTRANģʽ */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* ���ݲ�ͬ��UTRANģʽ���ò�ͬ��API���д��� */
    switch ( enCurrentUtranMode )
    {
        /* Wģ�Ĵ��� */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            (VOS_VOID)WTTF_RLC_GetRbSuitableUlPduSize(ucRbId,
                                           ulPduSize,
                                           ucCrcSize,
                                           pulUlPduSize);
            break;

        /* TDģ�Ĵ��� */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            (VOS_VOID)TDS_RLC_GetRbSuitableUlPduSize(ucRbId,
                                           ulPduSize,
                                           ucCrcSize,
                                           pulUlPduSize);

            break;
#endif

        default:
            NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize:ERROR:UTRAN MODE Error!");
            (VOS_VOID)WTTF_RLC_GetRbSuitableUlPduSize(ucRbId,
                                            ulPduSize,
                                            ucCrcSize,
                                            pulUlPduSize);
            break;
    }

    return;
}
VOS_UINT32 NAS_UTRANCTRL_RABM_SendTcDataNotify(VOS_VOID)
{
    PDCP_RABM_TC_DATA_IND_NOTIFY_STRU  *pstMsg;

    VOS_UINT32                          ulSendRslt;
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrentUtranMode;
#endif


    /*������Ϣ�ڴ�:*/
    pstMsg = (PDCP_RABM_TC_DATA_IND_NOTIFY_STRU *)PS_ALLOC_MSG( WUEPS_PID_RABM,
        sizeof(PDCP_RABM_TC_DATA_IND_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pstMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_SendTcDataNotify:WARNING: Allocates a message packet for ID_PDCP_RABM_TC_DATA_IND_NOTIFY msg FAIL!");
        return PS_FAIL;
    }

    /*��д��Ϣ����:*/
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;

    /* Ĭ�ϵ�ǰ�ķ���pidΪWģ */
    pstMsg->ulSenderPid     = WUEPS_PID_PDCP;

#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )

    /* ȡ�õ�ǰ��UTRANģʽ */
    enCurrentUtranMode      = NAS_UTRANCTRL_GetCurrUtranMode();

    /* TD��֧��ʱ,���ķ���PIDΪTDģ */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD == enCurrentUtranMode )
    {
        pstMsg->ulSenderPid = TPS_PID_PDC;
    }
#endif

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = WUEPS_PID_RABM;
    pstMsg->enMsgName       = ID_PDCP_RABM_TC_DATA_IND_NOTIFY;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    ulSendRslt = PS_SEND_MSG(pstMsg->ulSenderPid, pstMsg);

    if ( VOS_OK != ulSendRslt )
    {
        /* ��ӡ������Ϣ---������Ϣʧ��:*/
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_UTRANCTRL_RABM_SendTcDataNotify:WARNING: SEND ID_PDCP_RABM_TC_DATA_IND_NOTIFY msg FAIL!");
        return PS_FAIL;
    }

    return PS_SUCC;
}
VOS_VOID NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enCurrentUtranMode;

    /* ȡ�õ�ǰ��UTRANģʽ */
    enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /* ���ݲ�ͬ��UTRANģʽ���ò�ͬ��API���д��� */
    switch (enCurrentUtranMode)
    {
        /* Wģ�Ĵ��� */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD :
            WTTF_PDCP_TrigRlcUlProc();
            break;

        /* TDģ�Ĵ��� */
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
        case NAS_UTRANCTRL_UTRAN_MODE_TDD :
            TPDCP_IntUlDataProc();
            break;
#endif

        default:
            NAS_NORMAL_LOG(WUEPS_PID_RABM,
                "NAS_UTRANCTRL_RABM_SetFinIpInRdFlag:WARNING:UTRAN MODE NOT MATCH!");
            break;
    }

    return;
}


VOS_UINT32 NAS_UTRANCTRL_SndAsMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       **ppstMsg
)
{
#if ( FEATURE_ON == FEATURE_UE_MODE_TDS )
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq      = VOS_NULL_PTR;
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    pstMsgHeader    = (MSG_HEADER_STRU *)*ppstMsg;
    pstPlmnSrchReq  = (RRMM_PLMN_SEARCH_REQ_STRU *)*ppstMsg;
    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();

    /* ��GET_GEO���͵������������⴦�� */
    if ((RRMM_PLMN_SEARCH_REQ    == pstMsgHeader->ulMsgName)
     && (RRC_PLMN_SEARCH_GET_GEO == pstPlmnSrchReq->ulSearchType))
    {
        NAS_MML_SaveNwSearchReqInfo(pstPlmnSrchReq);

        NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo(ulSndPid, pstPlmnSrchReq);

        return VOS_OK;
    }

    /* �����ǰ�Ƿ���UTRANģ��ģ�����ƽ̨��FDD/TDD��֧�֣����ڷ�����Ϣǰ����Ԥ����
       ���ƽֻ̨֧��FDD/TDD�е�һ��������ҪԤ����ֱ���ж��Ƿ��滻PID���� */
    if ( (WUEPS_PID_WRR == pstMsgHeader->ulReceiverPid)
      && (VOS_TRUE == ulSupportFddFlg)
      && (VOS_TRUE == ulSupportTddFlg) )
    {

        if ( VOS_TRUE == NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode(*ppstMsg) )
        {
            /* UTRANCTRLģ��Է�����Ϣ�ı���Ԥ���� */
            NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   *ppstMsg);
            /* ��������W,ֱ�Ӹ�MMC����W������ʧ�� */
            NAS_MMC_SndInterSkipSearchWIndMsg();

            PS_FREE_MSG(ulSndPid, *ppstMsg);

            return VOS_OK;
        }

        if (VOS_TRUE == NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode(*ppstMsg))
        {
            /* UTRANCTRLģ��Է�����Ϣ�ı���Ԥ���� */
            NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   *ppstMsg);
            /* ��������tds,ֱ�Ӹ�MMC����tds������ʧ�� */
            NAS_MMC_SndInterSkipSearchTdsIndMsg();

            PS_FREE_MSG(ulSndPid, *ppstMsg);
            return VOS_OK;
        }

        NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg(ulSndPid, *ppstMsg);
    }

    /* TD��֧��ʱ,��ǰ��UTRANΪTģ  */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        switch (pstMsgHeader->ulReceiverPid)
        {
            case WUEPS_PID_PDCP:

                pstMsgHeader->ulReceiverPid = TPS_PID_PDC;
                break;

            case WUEPS_PID_WRR:

                pstMsgHeader->ulReceiverPid = TPS_PID_RRC;
                break;

            case WUEPS_PID_RLC:

                pstMsgHeader->ulReceiverPid = TPS_PID_RLC;
                break;

            default:
                break;
        }
    }

#endif

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)*ppstMsg);

    /* ��������������Ϣ */
    if (RRMM_PLMN_SEARCH_REQ == pstMsgHeader->ulMsgName)
    {
        NAS_MML_SaveNwSearchReqInfo(pstPlmnSrchReq);
    }

    if (VOS_OK != PS_SEND_MSG(ulSndPid, *ppstMsg))
    {
        /* ��ӡ������Ϣ---������Ϣʧ��:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsMsg:WARNING: SEND utran msg FAIL!");

        return VOS_ERR;
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 NAS_UTRANCTRL_BuildEventType (
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulMsgName
)
{
    VOS_UINT32                          ulEventType;

    /*
        Լ��: PID�ṹ Bit0~Bit11: ģ��ID  Bit12~Bit15: ���� Bit16~Bit19: CPU ID Bit20~Bit31: ����
        ��: PID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
            MSG: 0x0000abcd
            EVT: 0xABCDabcd
    */
    ulEventType = ((((ulSndPid) & 0xF0000) | (((ulSndPid) & 0xFFF) << 4)) << 12);

    ulEventType |= ulMsgName;

    return ulEventType;
}


VOS_UINT32 NAS_UTRANCTRL_GetMsgEventType(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    REL_TIMER_MSG                      *pRcvTimerMsg;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ���������ʱ����Ϣ���ܿ���Ϣͷ���ƽ������֣�������ṹ���ulName���������
       ���Դ˴����зֱ���
    */
    if ( VOS_PID_TIMER == pstMsgHeader->ulSenderPid )
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = NAS_UTRANCTRL_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);
    }
    else
    {
        ulEventType  = NAS_UTRANCTRL_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;

}



VOS_VOID  NAS_UTRANCTRL_ConvertSimPlmnToNasPlmn(
    NAS_MML_SIM_FORMAT_PLMN_ID          *pstSimPlmn,
    NAS_MML_PLMN_ID_STRU                *pstNasPlmn
)
{
    NAS_MMC_ConvertSimPlmnToNasPLMN(pstSimPlmn, pstNasPlmn);

    return;
}



VOS_VOID  NAS_UTRANCTRL_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
)
{
    (VOS_VOID)NAS_MMC_StartTimer(enTimerId, ulLen);
}


NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_UTRANCTRL_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_STATUS_ENUM_U8        enTimerStatus;

    enTimerStatus = NAS_MMC_GetTimerStatus(enTimerId);

    return enTimerStatus;
}


VOS_VOID  NAS_UTRANCTRL_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
   NAS_MMC_StopTimer(enTimerId);
}


VOS_VOID NAS_UTRANCTRL_SndGuAsUtranModeReq(
    VOS_UINT32                          ulRcvPid,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enMode
)
{
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_UTRAN_MODE_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_UTRAN_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  WUEPS_PID_MMC,
                                                  sizeof(RRMM_UTRAN_MODE_REQ_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsUtranModeReq():ERROR:Memory Alloc Error for pstMsg");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                     sizeof(RRMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulRcvPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->MsgHeader.ulMsgName         = RRMM_UTRAN_MODE_REQ;

    pstMsg->enUtranMode                 = NAS_UTRANCTRL_ConvertNasUtranModeToGuRrcUtranMode(enMode);

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg);

    if (VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsUtranModeReq():WARNING:MMC SEND failed!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_UTRANCTRL_SndLmmUtranModeReq(
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8  enMode
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    MMC_LMM_UTRAN_MODE_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (MMC_LMM_UTRAN_MODE_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndLmmUtranModeNotify,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = PS_PID_MM;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->ulLength        = sizeof(MMC_LMM_UTRAN_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ulMsgId         = ID_MMC_LMM_UTRAN_MODE_REQ;
    pstMsg->enUtranMode     = NAS_UTRANCTRL_ConvertNasUtranModeToLmmUtranMode(enMode);

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndLmmUtranModeNotify,ERROR:SNED MSG FAIL!");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}


#endif  /* end of #if (FEATURE_ON == FEATURE_LTE) */

VOS_VOID NAS_UTRANCTRL_SndGuAsSuspendReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_SUSPEND_REQ_ST                *pstMsg;

    /* �����ڴ�  */
    pstMsg = (RRMM_SUSPEND_REQ_ST *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSuspendReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength        = sizeof(RRMM_SUSPEND_REQ_ST) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName       = RRMM_SUSPEND_REQ;
    pstMsg->ucStopCause               = MMC_AS_SUSPEND_STOP_DSP;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSuspendReq,ERROR:SNED MSG FAIL!");
        return;
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

}


VOS_VOID  NAS_UTRANCTRL_SndAsSuspendRsp(
    RRC_NAS_SUSPEND_RESULT_ENUM_UINT8   enSuspendRslt,
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    RRMM_SUSPEND_RSP_ST                *pstAsMsg;

    /*������Ϣ  */

    pstAsMsg = (RRMM_SUSPEND_RSP_ST*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMC,
                                                 sizeof(RRMM_SUSPEND_RSP_ST));

    /* �ڴ�����ʧ��,ֱ�ӷ��� */
    if( VOS_NULL_PTR == pstAsMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsSuspendRsp():ERROR:Alloc Msg fail");
        return;
    }

    PS_MEM_SET( (VOS_INT8 *)pstAsMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH );

    /*��д��Ϣ����*/
    pstAsMsg->MsgHeader.ulMsgName       = RRMM_SUSPEND_RSP;
    pstAsMsg->MsgHeader.ulReceiverPid   = ulReceiverPid;
    pstAsMsg->MsgHeader.ulLength        = sizeof(RRMM_SUSPEND_RSP_ST) - VOS_MSG_HEAD_LENGTH;
    pstAsMsg->ucResult                  = enSuspendRslt;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstAsMsg);

    /*������Ϣ*/
    ulResult = PS_SEND_MSG(WUEPS_PID_MMC, pstAsMsg);

    if (VOS_OK != ulResult)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsSuspendRsp():WARNING:MMC SEND AS SUSPEND RSP failed!");
    }

    return ;
}



VOS_VOID NAS_UTRANCTRL_SndGuAsPlmnStopReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_PLMN_SEARCH_STOP_REQ_ST       *pstMsg = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstMsg = (RRMM_PLMN_SEARCH_STOP_REQ_ST *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPlmnStopReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH);

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength        = sizeof(RRMM_PLMN_SEARCH_STOP_REQ_ST) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName       = RRMM_PLMN_SEARCH_STOP_REQ;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPlmnStopReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}



VOS_VOID NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_PLMN_SEARCH_REQ_STRU          *pstSndMsg;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstBuffMsg;

    /* �����ڴ�  */
    pstSndMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_PLMN_SEARCH_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstBuffMsg = (RRMM_PLMN_SEARCH_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY( pstSndMsg, pstBuffMsg, sizeof(RRMM_PLMN_SEARCH_REQ_STRU) );

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    NAS_MML_SaveNwSearchReqInfo(pstSndMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}



VOS_VOID NAS_UTRANCTRL_SndGuAsSyscfgReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_SYS_CFG_REQ_STRU              *pstSndMsg;
    RRMM_SYS_CFG_REQ_STRU              *pstBuffMsg;

    /* �����ڴ�  */
    pstSndMsg = (RRMM_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                         sizeof(RRMM_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBuffMsg = (RRMM_SYS_CFG_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY(pstSndMsg, pstBuffMsg, sizeof(RRMM_SYS_CFG_REQ_STRU));

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:SNED MSG FAIL!");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif
    return;

}



VOS_VOID NAS_UTRANCTRL_SndGuAsPowerOffReq(
    VOS_UINT32                          ulReceiverPid
)
{
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RRMM_POWER_OFF_REQ_STRU            *pstMsg;                                 /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RRMM_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPowerOffReq:ERROR: Memory Alloc Error for pMsg");
        return ;
    }

    PS_MEM_SET( (VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0X00,
            sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = ulReceiverPid;
    pstMsg->MsgHeader.ulLength          = sizeof(RRMM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRMM_POWER_OFF_REQ;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMC, pstMsg);

    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsPowerOffReq:ERROR:PS_SEND_MSG ");
    }

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return ;
}
VOS_VOID NAS_UTRANCTRL_SndGuAsStartReq(
    VOS_UINT32                          ulRcvPid
)
{
    /* �������VOS���ͺ����ķ���ֵ */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    RRMM_START_REQ_STRU                *pstSndMsg;
    RRMM_START_REQ_STRU                *pstBuffMsg;

    /* �����ڴ�  */
    pstSndMsg = (RRMM_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                               sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if( VOS_NULL_PTR == pstSndMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsStartReq,ERROR:ALLOC MEM ERROR!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(RRMM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBuffMsg = (RRMM_START_REQ_STRU *) (NAS_UTRANCTRL_GetBufferedSndUtranReqMsgAddr()->aucEntryMsgBuffer);
    pstBuffMsg->MsgHeader.ulReceiverPid   = ulRcvPid;

    PS_MEM_CPY(pstSndMsg, pstBuffMsg, sizeof(RRMM_START_REQ_STRU));

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_MMC, pstSndMsg );

    if( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndGuAsSyscfgReq,ERROR:SNED MSG FAIL!");
    }

#ifdef NAS_STUB
    {
        VOS_UINT32                      ulRet;                     /* �������VOS���ͺ����ķ���ֵ */
        RRMM_START_CNF_STRU*            pStartCnfMsg;   /* ����ԭ������ָ�� */

        /* �����ڴ�  */
        pStartCnfMsg = (RRMM_START_CNF_STRU *)PS_ALLOC_MSG(ulRcvPid,
                                                   sizeof(RRMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
        if( VOS_NULL_PTR == pStartCnfMsg )
        {
            return ;
        }

        pStartCnfMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
        pStartCnfMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
        pStartCnfMsg->MsgHeader.ulMsgName           = RRMM_START_CNF;

        pStartCnfMsg->ulResult                      = MMC_START_SUCCESS;

        NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pStartCnfMsg);

        /* ����VOS����ԭ�� */
        ulRet = PS_SEND_MSG(ulRcvPid, pStartCnfMsg);

        if(VOS_OK != ulRet)
        {
            return ;
        }
    }

#endif

#ifndef __PS_WIN32_RECUR__
    NAS_UTRANCTRL_SetUePcRecurFlg(VOS_TRUE);
#endif

    return;
}



VOS_VOID NAS_UTRANCTRL_BuildRrMmStartCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    MMC_START_RESULT_ENUM_UINT32        ulResult,
    RRMM_START_CNF_STRU                *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_START_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_START_CNF;
    pstMsg->ulResult                              = ulResult;

    return;
}


VOS_VOID NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_POWER_OFF_CNF_STRU            *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_POWER_OFF_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_POWER_OFF_CNF;

    /* ��ʼ�������ֶ� */
    PS_MEM_SET(pstMsg->aucReserve1, (VOS_UINT8)0X00, sizeof(pstMsg->aucReserve1));

    return;
}
VOS_VOID NAS_UTRANCTRL_BuildRrMmSysCfgCnfMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRMM_SYS_CFG_RESULT_ENUM_UINT32     ulResult,
    RRMM_SYS_CFG_CNF_STRU              *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_SYS_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_SYS_CFG_CNF;
    pstMsg->ulResult                              = ulResult;

    return;
}


VOS_VOID NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(
    VOS_UINT32                          ulSndPid,
    VOS_UINT32                          ulRcvPid,
    RRC_PLMN_SEARCH_TYPE_ENUM_UINT32    enPlmnSearchType,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstMsg
)
{
    pstMsg->MsgHeader.ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid               = ulRcvPid;
    pstMsg->MsgHeader.ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid                 = ulSndPid;
    pstMsg->MsgHeader.ulLength                    = sizeof(RRMM_PLMN_SEARCH_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName                   = RRMM_PLMN_SEARCH_CNF;

    if (RRC_PLMN_SEARCH_HISTORY == enPlmnSearchType)
    {
        /* ��ʷƵ����ʧ�� */
        pstMsg->ulSearchRlt                       = RRC_PLMN_SEARCH_RLT_HISTORY_FAIL;
    }
    else if (RRC_PLMN_SEARCH_GET_GEO == enPlmnSearchType)
    {
        pstMsg->ulSearchRlt                       = RRC_PLMN_SEARCH_RLT_GET_GEO_FAIL;
    }
    else
    {
        /* ָ���������ʧ�� */
        pstMsg->ulSearchRlt                       = RRC_PLMN_SEARCH_RLT_SPEC_FAIL;
    }

    pstMsg->enCoverageType                        = RRC_NAS_COVERAGE_TYPE_NONE;

    /* ���б��ѽ�����  */
    PS_MEM_SET(pstMsg->astSearchRatInfo,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->astSearchRatInfo));

    /* ָ������Я���ĸ������������Ϊ0�� */
    pstMsg->PlmnIdList.ulHighPlmnNum              = 0;
    PS_MEM_SET(pstMsg->PlmnIdList.aHighPlmnList,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->PlmnIdList.aHighPlmnList));

    /* ָ������Я���ĵ������������Ϊ0�� */
    pstMsg->PlmnIdList.ulLowPlmnNum               = 0;
    PS_MEM_SET(pstMsg->PlmnIdList.aLowPlmnList,
               (VOS_UINT8)0X00,
               sizeof(pstMsg->PlmnIdList.aLowPlmnList));


    return;
}



VOS_VOID NAS_UTRANCTRL_UpdateCurUtranSwitchMode(
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                               ucSimPresentStatus,
    NAS_UTRANCTRL_UTRAN_MODE_AUTO_SWITCH_STRU              *pstUtranModeAutoSwitch
)
{
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;

    /* IMSI�б����Ϊ0��ǰ�л�ģʽΪFDD ONLY������µ�ǰUTRAN�л�ģʽΪFDD ONLY */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY == pstUtranModeAutoSwitch->ucUtranSwitchMode)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);

        return;
    }

    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY == pstUtranModeAutoSwitch->ucUtranSwitchMode)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY);

        return;
    }

    if (0 == pstUtranModeAutoSwitch->ucImsiPlmnListNum)
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);

        return;
    }

    /* ��������SIM���������W��T���л� */
    if (NAS_UTRANCTRL_SUPPORT_ALL_SIM_AUTO_SWITCH_UTRAN_NUM == pstUtranModeAutoSwitch->ucImsiPlmnListNum )
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);

        return;
    }

    /* �����ǰSIM/USIM���ļ����� */
    if (VOS_TRUE  == ucSimPresentStatus)
    {

        stHPlmn = NAS_MML_GetImsiHomePlmn(pucImsi);

        /* ��ǰ��IMSI�е�PLMN����NV���õ�IMSI PLMN LIST�У���ǰΪGULģʽ,�������Զ��л� */
        if (VOS_TRUE == NAS_MML_IsSimPlmnIdInDestBcchPlmnList(&stHPlmn,
                                    pstUtranModeAutoSwitch->ucImsiPlmnListNum,
                                    pstUtranModeAutoSwitch->astImsiPlmnList))
        {
            NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);
        }
        else
        {
            NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_FDD_ONLY);
        }
    }
    else
    {
        NAS_UTRANCTRL_SetCurUtranSwitchMode(NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO);
    }

    return;
}
VOS_UINT32 NAS_UTRANCTRL_IsSndOmPcRecurMsgValid(VOS_VOID)
{
    VOS_UINT32                          ulRslt;

    /* �жϵ�ǰ��SDT����PC �ط���Ϣ�Ƿ���Ч */
    ulRslt = NAS_MML_IsSndOmPcRecurMsgValid();

    return ulRslt;
}
VOS_UINT32 NAS_UTRANCTRL_IsNeedUtranCtrlFsmProcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulSupportFddFlg;
    VOS_UINT32                          ulSupportTddFlg;

    /* ȡ�õ�ǰ��Ϣ���¼����� */
    ulEventType = NAS_UTRANCTRL_GetMsgEventType(pstMsg);

    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();
    ulSupportTddFlg = NAS_MML_IsPlatformSupportUtranTdd();

    /* ���FDD��TDD��֧�֣����Utran״̬������ֱ�ӷ���VOS_TRUE */
    if (ulSupportFddFlg == ulSupportTddFlg)
    {
        return VOS_TRUE;
    }

    /* ������FDD/TDD��ģʱ��Ҳ����GMM�����Ŀ����ظ���Ϣ������NV�Ķ�д */
    if (ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_GMM, MMCGMM_START_CNF))
    {
        return VOS_TRUE;
    }

    if (ulEventType == NAS_UTRANCTRL_BuildEventType(VOS_PID_TIMER, TI_NAS_MMC_WAIT_MM_START_CNF))
    {
        return VOS_TRUE;
    }

    if (ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ))
    {
        return VOS_TRUE;
    }

    /* ������Ϣ��FDD/TDD��ģʱ�򣬲���Ҫ����UTRANCTRL FSM���� */
    return VOS_FALSE;
}




VOS_UINT32 NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* Ĭ�ϲ���Ҫ֪ͨ��һģ */
    ulRslt = VOS_FALSE;

    /* �����ǰ��֧��UTRAN�Զ��л�������Ҫ֪ͨ��һģ */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    switch (pstMsgHeader->ulMsgName)
    {
        /* ����NAS COMM��Ϣ��Ҫ֪ͨ��һģ */
        case RRMM_NAS_COMM_INFO_CHANGE_REQ:
             ulRslt = VOS_TRUE;
             break;

        /* ����NAS COMM��Ϣ��Ҫ֪ͨ��һģ */
        case RRMM_AT_MSG_REQ:
             ulRslt = VOS_TRUE;
             break;

        case RRMM_BEGIN_SESSION_NOTIFY:
             ulRslt = VOS_TRUE;
             break;

        case RRMM_END_SESSION_NOTIFY:
             ulRslt = VOS_TRUE;
             break;
        default:
            break;
    }

    return ulRslt;
}


VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranFddMode(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader  = VOS_NULL_PTR;
    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* �����ǰ��֧��UTRAN�Զ��л�������Ҫ������Wģʽ */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* ��ǰ����FDDģʽ�£�����Ҫ���� */
    if ( NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())
    {
        return VOS_FALSE;
    }

    /* ��⵱ǰ�Ƿ���W�µ�������Ϣ,�������RRMM_PLMN_SEARCH_REQ������Ϣ������Ҫ����W */
    if ( (WUEPS_PID_MMC        != pstMsgHeader->ulSenderPid)
      || (RRMM_PLMN_SEARCH_REQ != pstMsgHeader->ulMsgName)  )
    {
        return VOS_FALSE;
    }

    /* ��⵱ǰ�����Ƿ��ڹ���,����ڹ��ڣ�����Ҫ����W */
    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_TRUE == NAS_MMC_GetUtranSkipWPlmnSearchFlag())
     && (VOS_TRUE == ulIsOtherModemPlmnInTdMccList))
    {
        /* ��ǰ�������й�����������������W */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_IsNeedSkipSearchUtranTddMode(
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamPlmnSelectionSortFlg;
    NAS_MML_PLMN_ID_STRU               *pstOtherModemPlmnId = VOS_NULL_PTR;
    VOS_UINT32                          ulIsCurrSearchingPlmnInTdMccList;
    NAS_MML_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          ulHongKongMcc;
    VOS_UINT32                          ulIsOtherModemPlmnInTdMccList;

    pstPlmnSearchReqMsg              = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;
    ucRoamPlmnSelectionSortFlg       = NAS_MMC_GetRoamPlmnSelectionSortActiveFlg();
    ulIsCurrSearchingPlmnInTdMccList = VOS_FALSE;
    ulIsOtherModemPlmnInTdMccList    = VOS_FALSE;
    PS_MEM_SET(&stPlmnId, 0, sizeof(stPlmnId));

    /* ��۹�������454 */
    ulHongKongMcc = NAS_UTRANCTRL_HONGKONG_MCC;

    /* �����ǰ��֧��UTRAN�Զ��л�������Ҫ������tdsģʽ */
    if ( NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* ��ǰ����TDDģʽ�£�����Ҫ���� */
    if ( NAS_UTRANCTRL_UTRAN_MODE_TDD != NAS_UTRANCTRL_GetCurrUtranMode())
    {
        return VOS_FALSE;
    }

    /* ��⵱ǰ�Ƿ���W�µ�������Ϣ,�������RRMM_PLMN_SEARCH_REQ������Ϣ������Ҫ����TDS */
    if ( (WUEPS_PID_MMC        != pstPlmnSearchReqMsg->MsgHeader.ulSenderPid)
      || (RRMM_PLMN_SEARCH_REQ != pstPlmnSearchReqMsg->MsgHeader.ulMsgName)  )
    {
        return VOS_FALSE;
    }

    /* ���ǿ�����������Ҫ����tds */
    if (VOS_FALSE == NAS_UTRANCTRL_GetSwithOnPlmnSearchFlag())
    {
        return VOS_FALSE;
    }

    /* ��⵱ǰ�����Ƿ��ڹ���,����ڹ��ڣ�����Ҫ����TDS */
    pstOtherModemPlmnId = NAS_MMC_GetOtherModemPlmnId();
    ulIsOtherModemPlmnInTdMccList = NAS_MML_IsMccInDestMccList(pstOtherModemPlmnId->ulMcc,
                                                NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                NAS_UTRANCTRL_GetSpecTdMccList());

    if (VOS_TRUE == ulIsOtherModemPlmnInTdMccList)
    {
        /* ��ǰ�������й���������������TDS */
        return VOS_FALSE;
    }

    /* anycell����������tds */
    if (0 == pstPlmnSearchReqMsg->ulPlmnIdNum)
    {
        return VOS_FALSE;
    }

    /* �����ǰ���������粻��TDS���������Ҳ���������磬������tds���� */
    stPlmnId.ulMcc = pstPlmnSearchReqMsg->aPlmnIdList[0].ulMcc;
    stPlmnId.ulMnc = pstPlmnSearchReqMsg->aPlmnIdList[0].ulMnc;


    ulIsCurrSearchingPlmnInTdMccList = NAS_MML_IsMccInDestMccList(stPlmnId.ulMcc,
                                        NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                        NAS_UTRANCTRL_GetSpecTdMccList());

    if ((VOS_FALSE == NAS_MML_ComparePlmnMcc(stPlmnId.ulMcc, ulHongKongMcc))
     && (VOS_FALSE == ulIsCurrSearchingPlmnInTdMccList)
     && (VOS_TRUE == ucRoamPlmnSelectionSortFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_REQ_STRU          *pstReqMsg           = VOS_NULL_PTR;

    pstReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* ģʽ�Զ��л�ʱ,��Ҫ��������������Ϣ,���ں���״̬��ʹ�� */
    if ( (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO == NAS_UTRANCTRL_GetCurUtranSwitchMode())
      && (RRMM_PLMN_SEARCH_REQ == pstReqMsg->MsgHeader.ulMsgName) )
    {
        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);
    }

    /*  �����ǰ����Wģ��SYSCFG������Ҳ��Ҫ���棬����UTRANCTRLģ���SYSCFG״̬��ʹ�� */
    if ( RRMM_SYS_CFG_REQ == pstReqMsg->MsgHeader.ulMsgName )
    {
        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);
    }

    /*  �����ǰ����Wģ������������Ҳ��Ҫ���棬����UTRANCTRLģ��Ŀ���״̬��ʹ�� */
    if ( RRMM_START_REQ == pstReqMsg->MsgHeader.ulMsgName )
    {
        NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg(NAS_UTRANCTRL_GetMsgEventType(pstMsg), pstMsg);
    }

    return;

}
VOS_VOID NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    struct MsgCB                       *pstTempMsg          = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstTempMsgHeader    = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;
    VOS_UINT32                          ulAnotherUtranModePid;

    enCurrUtranMode       = NAS_UTRANCTRL_GetCurrUtranMode();
    ulAnotherUtranModePid = WUEPS_PID_WRR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ��ǰ��Ϣ���ͺ󣬿��ܻ���Ҫ�ٷ��͸���һ��ģ�����������ڴ����ڱ�����Ϣ */
    pstTempMsg = (struct MsgCB *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                              pstMsgHeader->ulLength);

    if ( VOS_NULL_PTR == pstTempMsg )
    {
        /* ��ӡ������Ϣ---������Ϣʧ��:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAsMsg:error: MEM ALLOC FAIL!");

        return;
    }

    /* ����ǰ��Ϣ���浽������ѱ���֪ͨ��һģ */
    PS_MEM_CPY( pstTempMsg,
                pstMsg,
                pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);

    pstTempMsgHeader = (MSG_HEADER_STRU *)pstTempMsg;

    /* ȡ��һUTRANģ��PID */
    switch (enCurrUtranMode)
    {
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
            ulAnotherUtranModePid = TPS_PID_RRC;
            break;

        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
            ulAnotherUtranModePid = WUEPS_PID_WRR;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg():WARNING: ENTERED");
            break;
    }

    pstTempMsgHeader->ulReceiverPid = ulAnotherUtranModePid;

    NAS_MML_LogMsgInfo((MSG_HEADER_STRU*)pstTempMsg);

    /* ����һģ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(ulSndPid, pstTempMsg))
    {
        /* ��ӡ������Ϣ---������Ϣʧ��:*/
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg:WARNING: SEND utran msg FAIL!");

        return;
    }

    return;

}


VOS_VOID NAS_UTRANCTRL_StartUtranTddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg = VOS_NULL_PTR;

    pstMsgHeader        = (MSG_HEADER_STRU *)pstMsg;
    pstPlmnSearchReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        /* ���Ϳ�����Ϣʱ����������������ʱ�� */
        case RRMM_START_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_START_CNF, TI_NAS_UTRANCTRL_WAIT_TD_START_CNF_LEN);
            break;

        /* ���͹ػ���Ϣʱ�������ػ�������ʱ�� */
        case RRMM_POWER_OFF_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);
            break;

        /* ����SYSCFG������Ϣʱ������SYSCFG���ñ�����ʱ�� */
        case RRMM_SYS_CFG_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF_LEN);
            break;

        /* ����������Ϣʱ����������������ʱ�� */
        case RRMM_PLMN_SEARCH_REQ:

            /* �����ǰ���û�ָ���ѻ���HISTORY������������������ʱ�� */
            if ( (RRC_PLMN_SEARCH_SPEC      == pstPlmnSearchReqMsg->ulSearchType)
              || (RRC_PLMN_SEARCH_HISTORY   == pstPlmnSearchReqMsg->ulSearchType) )
            {
                NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN);
            }
            break;

        default:
            break;
    }

    return;

}
VOS_VOID NAS_UTRANCTRL_StartUtranFddModeMsgTimer(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSearchReqMsg = VOS_NULL_PTR;

    pstMsgHeader        = (MSG_HEADER_STRU *)pstMsg;
    pstPlmnSearchReqMsg = (RRMM_PLMN_SEARCH_REQ_STRU *)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        /* ���Ϳ�����Ϣʱ����������������ʱ�� */
        case RRMM_START_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF_LEN);
            break;

        /* ���͹ػ���Ϣʱ�������ػ�������ʱ�� */
        case RRMM_POWER_OFF_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);
            break;

        /* ����SYSCFG������Ϣʱ������SYSCFG���ñ�����ʱ�� */
        case RRMM_SYS_CFG_REQ:
            NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF_LEN);
            break;

        /* ����������Ϣʱ����������������ʱ�� */
        case RRMM_PLMN_SEARCH_REQ:

            /* �����ǰ���û�ָ���ѻ���HISTORY������������������ʱ�� */
            if ( (RRC_PLMN_SEARCH_SPEC      == pstPlmnSearchReqMsg->ulSearchType)
              || (RRC_PLMN_SEARCH_HISTORY   == pstPlmnSearchReqMsg->ulSearchType) )
            {
                NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN);
            }
            break;

        default:
            break;
    }

    return;

}
VOS_VOID NAS_UTRANCTRL_StopUtranTddModeMsgTimer(
    VOS_UINT32                          ulMsgName
)
{
    switch ( ulMsgName )
    {
        /* ����ֹͣ������Ϣ��ʱ��ֹͣ��ǰ��TDDģ������������ʱ�� */
        case RRMM_PLMN_SEARCH_STOP_REQ:

            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF))
            {
                NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);
            }
            break;

        default:

            break;
    }

    return;

}
VOS_VOID NAS_UTRANCTRL_StopUtranFddModeMsgTimer(
    VOS_UINT32                          ulMsgName
)
{
    switch ( ulMsgName )
    {
        /* ����ֹͣ������Ϣʱ��ֹͣ��ǰ��FDD����������ʱ�� */
        case RRMM_PLMN_SEARCH_STOP_REQ:
            if (NAS_MMC_TIMER_STATUS_RUNING == NAS_UTRANCTRL_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
            {
                NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
            }

            break;

        default:
            break;
    }

    return;

}
VOS_VOID NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch ( enCurrUtranMode )
    {
        /* ������Ϣʱ����������FDD������ʱ�� */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
             NAS_UTRANCTRL_StartUtranFddModeMsgTimer(ulSndPid, pstMsg);
             break;

        /* ������Ϣʱ������TDD������ʱ�� */
        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
             NAS_UTRANCTRL_StartUtranTddModeMsgTimer(ulSndPid, pstMsg);
             break;

        default:
            break;
    }

    return;

}


VOS_VOID NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader        = VOS_NULL_PTR;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch ( enCurrUtranMode )
    {
        /* ������Ϣʱ��ֹͣ����FDD������ʱ�� */
        case NAS_UTRANCTRL_UTRAN_MODE_FDD:
             NAS_UTRANCTRL_StopUtranFddModeMsgTimer(pstMsgHeader->ulMsgName);
             break;

        /* ������Ϣʱ��ֹͣ������TDD������ʱ�� */
        case NAS_UTRANCTRL_UTRAN_MODE_TDD:
             NAS_UTRANCTRL_StopUtranTddModeMsgTimer(pstMsgHeader->ulMsgName);
             break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg():WARNING:UTRAN MODE INVALID");
            break;
    }

    return;

}



VOS_VOID NAS_UTRANCTRL_SndUtranAsMsgPreProcessMsg(
    VOS_UINT32                          ulSndPid,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLģ��Է�����Ϣ�ı���Ԥ���� */
    NAS_UTRANCTRL_SaveBufferedSndUtranReqMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    /* �жϵ�ǰ��Ϣ�Ƿ���Ҫ���͸���һ��ģ */
    if ( VOS_TRUE == NAS_UTRANCTRL_IsNeedSndAnotherUtranModeMsg(pstMsg) )
    {
        /* ��ǰ��Ϣ���ͺ󣬿��ܻ���Ҫ�ٷ��͸���һ��ģ�����������ڴ����ڷ�����Ϣ */
        NAS_UTRANCTRL_SndAnotherUtranModeMsg_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    }

    /* ����MMC״̬��ģ���ڷ�����Ϣʱ�������Ķ�ʱ��ʵ�����Ǳ���Wģ��TD����ģ
       �ģ���ǰģ��δ�ܵ��������統ǰΪGTLģʽ���ڵ�TDģ����Ϣ��ʱ����ʱMMC
       ���ڵȴ�Wģ�Ļظ������ڷ�����Ϣǰ���Ե�ǰ��������Ϣ���ж�ʱ������ */
    NAS_UTRANCTRL_StartUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);


    /* ֹͣMMC״̬������������Ϣ�Ķ�ʱ������:MMCģ���WAS����������Ϣ��ʱ��
       �յ����û��Ĵ�����󣬴�ʱMMC����ֹͣ����,UTRANCTRLģ����Ҫֹͣ��ǰ����
       ��������ʱ�� */
    NAS_UTRANCTRL_StopUtranModeMsgTimer_SndUtranAsMsgPreProcessMsg(ulSndPid,
                                                                   pstMsg);

    return ;

}



VOS_UINT32 NAS_UTRANCTRL_IsSpecPlmnMccInGuRrcPlmnIdList(
    VOS_UINT32                          ulSpecPlmnMcc,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
)
{
    VOS_UINT32                          ulMccNum;
    VOS_UINT32                         *pulRrcMccList = VOS_NULL_PTR;

    pulRrcMccList = (VOS_UINT32 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                        sizeof(VOS_UINT32) * (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM));


    if ( VOS_NULL_PTR == pulRrcMccList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_IsSpecPlmnMccInDestPlmnIdList ERROR: MEM ALLOC FAIL");

        return VOS_FALSE;
    }

    /* ��RRC��PLMN ID�б��л�ȡMCC�б� */
    NAS_MMC_GetMccListInRrcPlmnIdList(&ulMccNum, pulRrcMccList, pstGuPlmnIdList);

    /* �ж�MCC�Ƿ���TD MCC�б��� */
    if (VOS_TRUE == NAS_MML_IsMccInDestMccList(ulSpecPlmnMcc, ulMccNum, pulRrcMccList))
    {
        PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
    return VOS_FALSE;
}

VOS_VOID NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(
    VOS_UINT32                          ulTdMccNum,
    VOS_UINT32                         *pulTdMccList,
    RRC_PLMN_ID_LIST_STRU              *pstGuPlmnIdList
)
{
    VOS_UINT32                          ulMccNum;
    VOS_UINT32                         *pulRrcMccList;
    VOS_UINT32                          i;

    pulRrcMccList = (VOS_UINT32 *)PS_MEM_ALLOC(WUEPS_PID_MMC,
                        sizeof(VOS_UINT32) * (RRC_MAX_HIGH_PLMN_NUM + RRC_MAX_LOW_PLMN_NUM));


    if ( VOS_NULL_PTR == pulRrcMccList )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg ERROR: MEM ALLOC FAIL");

        return;
    }

    /* ��RRC��PLMN ID�б��л�ȡMCC�б� */
    NAS_MMC_GetMccListInRrcPlmnIdList(&ulMccNum, pulRrcMccList, pstGuPlmnIdList);

    /* ����GU RRC��MCC�б� */
    for (i = 0; i < ulMccNum; i++)
    {

        /* �ж�MCC�Ƿ���TD MCC�б��� */
        if (VOS_TRUE == NAS_MML_IsMccInDestMccList(pulRrcMccList[i], ulTdMccNum, pulTdMccList))
        {
             /* ���������б�����й������� */
            NAS_UTRANCTRL_SetSearchedSpecTdMccFlg(VOS_TRUE);

            break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pulRrcMccList);
}


VOS_UINT32 NAS_UTRANCTRL_IsNeedProcGuPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    RRMM_PLMN_SEARCH_CNF_STRU          *pstPlmnSrchCnf
)
{
    /* ���Զ��л�ģʽ,��Ϣֱ��͸����MMC״̬������ */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* �����LIST�����Ľ���ظ���ֱ��͸����MMC״̬������ */
    if (VOS_TRUE == NAS_MML_IsPlmnListSrchRslt(enRat, pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ��
       1. ����ʧ��NORF
       2. ����ָ��������ָ������ �ɹ�
       3. history�ѳɹ�
       ֱ��͸������ָ�������ظ���MMC״̬������ */
    if ((RRC_PLMN_SEARCH_SPEC_FAST          == NAS_UTRANCTRL_GetBufferedPlmnSearchReqType())
     || (RRC_PLMN_SEARCH_RLT_SPEC           == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstPlmnSrchCnf->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ�������GET_GEO���ֱ��͸����MMC״̬������ */
    if (VOS_TRUE == NAS_MML_IsGetGeoPlmnSrchRslt(enRat, pstPlmnSrchCnf->ulSearchRlt))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_IsNeedProcLmmPlmnSearchCnf(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstPlmnSrchCnf
)
{
    /* ���Զ��л�ģʽ,��Ϣֱ��͸����MMC״̬������ */
    if (NAS_UTRANCTRL_UTRAN_SWITCH_MODE_AUTO != NAS_UTRANCTRL_GetCurUtranSwitchMode())
    {
        return VOS_FALSE;
    }

    /* �����LIST�����Ľ���ظ���ֱ��͸����MMC״̬������ */
    if (VOS_TRUE == NAS_MML_IsPlmnListSrchRslt(enRat, pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ�����������ʧ��NORF/����ָ��������ָ�������ɹ�/history�ѳɹ�ֱ��͸������ָ�������ظ���MMC״̬������ */
    if ((MMC_LMM_PLMN_SRCH_RLT_SPEC_SUCC        == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF       == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_HISTORY_SUCC     == pstPlmnSrchCnf->enRlst)
     || (MMC_LMM_PLMN_SRCH_RLT_HISTORY_NO_RF    == pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    /* �Զ��л�ģʽ�������GET_GEO���ֱ��͸����MMC״̬������ */
    if (VOS_TRUE == NAS_MML_IsGetGeoPlmnSrchRslt(enRat, pstPlmnSrchCnf->enRlst))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_VOID NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo(
    VOS_UINT32                          ulSndPid,
    RRMM_PLMN_SEARCH_REQ_STRU          *pstPlmnSrchReq
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstGeoPlmnSrchFail      = VOS_NULL_PTR;
    VOS_UINT32                          ulSupportFddFlg;

    ulSupportFddFlg = NAS_MML_IsPlatformSupportUtranFdd();

    /* Receive PIDΪGASʱ��ֱ�Ӹ�GAS����get_geo���͵����� */
    if (WUEPS_PID_WRR != pstPlmnSrchReq->MsgHeader.ulReceiverPid)
    {
        PS_SEND_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* Receive PIDΪWRRʱ: */

    /* ƽ̨֧��FDD������utran switch mode����TDD onlyʱ��ֱ�Ӹ�WRR����get_geo���͵����� */
    if ((NAS_UTRANCTRL_UTRAN_SWITCH_MODE_TDD_ONLY != NAS_UTRANCTRL_GetCurUtranSwitchMode())
     && (VOS_TRUE   == ulSupportFddFlg))
    {
        PS_SEND_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* ƽ̨��֧��FDD��utran switch modeΪTDD onlyʱ������geo_geoʧ�ܵ���Ϣ���͸�MMC */
    pstGeoPlmnSrchFail  = (RRMM_PLMN_SEARCH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMC,
                                                        sizeof(RRMM_PLMN_SEARCH_CNF_STRU));

    /* �ڴ�����ʧ��,ֱ�ӷ��� */
    if ( VOS_NULL_PTR == pstGeoPlmnSrchFail )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_ProcPlmnSearchReq_GetGeo():ERROR:Alloc Msg fail");

        PS_FREE_MSG(ulSndPid, pstPlmnSrchReq);

        return;
    }

    /* ���������ظ�ʧ����Ϣ*/
    NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                WUEPS_PID_MMC,
                                                pstPlmnSrchReq->ulSearchType,
                                                pstGeoPlmnSrchFail);

    PS_SEND_MSG(ulSndPid, pstGeoPlmnSrchFail);

    PS_FREE_MSG(ulSndPid, pstPlmnSrchReq);

    return;

}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

