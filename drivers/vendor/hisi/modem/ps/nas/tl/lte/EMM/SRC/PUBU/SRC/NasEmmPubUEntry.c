/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmPubUEntry.c
    Description :
    History     :
      1.  hanlufeng 41410  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmPubUEntry.h"
#include    "NasLmmPubMOm.h"
#include    "NasLmmPubMTimer.h"
#include    "NasEmmMrrcPubInterface.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasLmmPubMPrint.h"
#include    "NasEmmAttachCnMsgProcess.h"
#include    "NasEmmPlmnInterface.h"
#include    "NasEmmTAUProc.h"
#include    "NasEmmSmsInterface.h"
#include    "NasEmmSerProc.h"
#include    "NasEmmcPublic.h"

#include    "ImsaIntraInterface.h"
#if (FEATURE_LPP == FEATURE_ON)
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmLppMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUENTRY_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUENTRY_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/* CN��Ϣ���������Ľṹ�壬��Ϣ̫�������ʺ��������ľֲ����� */
NAS_EMM_CN_MSG_STRU                     g_stCnDecodeMsgStru;

/*****************************************************************************
  3 Function
*****************************************************************************/


/*****************************************************************************
 Function Name  : NAS_EMM_MsgProcessInFsm
 Discription    : EMM ��Ϣ��״̬������
 Input          : ����״̬��ID ��Ϣָ�� �¼�����
                  pOsaOrCnStruMsg:
                        ����Ϣ����ΪID_RRC_MM_DATA_IND,��ָ��ָ�������CN��Ϣ�ṹ
                        ��������Ϣ����ʱ��ָ���DOPRA�յ�����Ϣ�ṹ
 Output         : None
 Return         :����Ϣ�Ƿ���
 History:
                  hanlufeng 41410  Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32 NAS_EMM_MsgProcessInFsm(     MsgBlock           *pMsg,
                                        VOS_UINT32          ulEventType)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgId;
    VOS_VOID                            *pOsaOrCnStruMsg;    /* ����EMM״̬���������Ϣ�ṹ��ָ�� */


    pOsaOrCnStruMsg                     = (VOS_VOID *)pMsg;


    /* EMM Ԥ����, ��Ԥ����ɹ�,���ٽ���EMM��״̬������ */
    ulRet                               = NAS_EMM_MsgPreProcess( ulEventType, pMsg );
    /* ��ȡ��ϢID */
    NAS_LMM_GetNameFromMsg(ulMsgId, pMsg);

    /* ���û��Ԥ����,����EMM״̬������ */
    if ( (NAS_LMM_MSG_DISCARD == ulRet ) )
    {

        if(ID_LRRC_LMM_DATA_IND == ulMsgId)
        {   /* ��CN��Ϣ������� CN�������� */

            /* ����EMM״̬���������Ϣ�ṹ��ָ�� ָ������Ľṹ�� */
            pOsaOrCnStruMsg         = &(g_stCnDecodeMsgStru.uCnMsgStru);
        }

        /*������ڲ��տ���Ϣת����ֱ��ȡ�տ���Ϣ�Ľ�����*/
        if(ID_NAS_LMM_INTRA_DATA_IND == ulMsgId)
        {
            pOsaOrCnStruMsg         = &(g_stCnDecodeMsgStru.uCnMsgStru);
        }

        /* Ȼ�����EMM ��״̬������ */
        ulRet = NAS_LMM_MsgProcessInFsm( NAS_LMM_PARALLEL_FSM_EMM,
                                        pOsaOrCnStruMsg,
                                        ulMsgId,
                                        ulEventType);
    }

    return ulRet;
}



VOS_UINT32  NAS_EMM_MsgPreProcess(  NAS_EMM_EVENT_TYPE_ENUM_UINT32      ulEt,
                                    MsgBlock                           *pMsg )
{
    VOS_UINT32                          ulRet;
    LRRC_LMM_DATA_IND_STRU               *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                          *pRcvMsg            = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucPD               = NAS_EMM_NULL;
    VOS_UINT8                           ucAirMsg           = NAS_EMM_NULL;
    VOS_UINT8                           ucKeyEvent         = NAS_EMM_NULL;
    NAS_LMM_FSM_STATE_STRU              *pstFsmCtx          = NAS_LMM_NULL_PTR;

    ulRet = NAS_LMM_MSG_DISCARD;

    /*�ṹ����Ϣ��ȡ����Ϣ��*/
    pstTmpRcvMsg = (LRRC_LMM_DATA_IND_STRU*)pMsg;
    pRcvMsg      = pstTmpRcvMsg->stNasMsg.aucNasMsg;

    if(ID_LRRC_LMM_DATA_IND == pstTmpRcvMsg->enMsgId)
    {
        /*ȡ��PD*/
        ucPD = pRcvMsg[NAS_EMM_NULL]& EMM_CN_MSG_PDMASK;

        /* �����ESM��Ϣֱ���ϱ�ESM */
        if  (EMM_CN_MSG_PD_ESM == ucPD)
        {
            /* ת����ESM��Ϣ */
            NAS_EMM_EsmSendDataInd((NAS_EMM_CN_MSGCON_STRU *)&(pstTmpRcvMsg->stNasMsg));
            return  NAS_LMM_MSG_HANDLED;
        }
        /* �����TC��Ϣֱ���ϱ�TC */
        if  (EMM_CN_MSG_PD_TC == ucPD)
        {
            /* ת����TC��Ϣ */
            NAS_EMM_TcSendDataInd((NAS_EMM_CN_MSGCON_STRU *)&(pstTmpRcvMsg->stNasMsg));
            return  NAS_LMM_MSG_HANDLED;
        }

        /*�տ���Ϣ�ϱ�*/
        if(EMM_CN_MSG_PD_EMM == ucPD)
        {
            NAS_LMM_FindAirMsgId(pRcvMsg[NAS_LMM_CN_MSG_MT_POS], &ucAirMsg, &ucKeyEvent);
            /* zhaochen 00308719 begin for SMS Message hook */
            /* �жϸÿտ���Ϣ���Ƿ��ж������ݣ������У��򲻹�������Ϣ */
            if (NAS_EMM_NO == NAS_LMM_IsMsgContainsSMS(pstTmpRcvMsg->stNasMsg.ulNasMsgSize, &pstTmpRcvMsg->stNasMsg.aucNasMsg[0]))
            {
                NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_DOWN,
                                            ucAirMsg,
                                            (NAS_MSG_STRU*)&(pstTmpRcvMsg->stNasMsg));
            }
            /* zhaochen 00308719 end for SMS Message hook */

            if (NAS_EMM_NULL != ucKeyEvent)
            {
                NAS_LMM_SendOmtKeyEvent(ucKeyEvent);
            }

            NAS_LMM_MEM_SET(&g_stCnDecodeMsgStru, 0, sizeof(NAS_EMM_CN_MSG_STRU));

            ulRet = NAS_EMM_DecodeCnMsg(pMsg, &g_stCnDecodeMsgStru);

            if(NAS_EMM_FAIL == ulRet )
            {/* ���������,��ӡ���� */

                NAS_LMM_PUBM_LOG1_ERR("NAS_EMM_MsgProcessInFsm, ulEventType = ", ulEt);
                TLPS_PRINT2LAYER_ERROR1(NAS_EMM_MsgPreProcess_ENUM,LNAS_FAIL,ulEt);

                /*����EMM STATUS, ���յ���ʶ�����Ϣ */
                NAS_EMM_SendMsgEmmStatus( NAS_LMM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE );
                return NAS_LMM_MSG_HANDLED;
            }

            /* ��EMM INFO �� EMM STATUS ���д��� */
            ulRet = NAS_EMM_PreProcMsgDataInd();
            return  ulRet;

        }

        ulRet                       = NAS_LMM_MSG_DISCARD;
    }

    /* SM�쳣��Ϣ�Ĵ���*/
    if(ID_EMM_ESM_REL_REQ == pstTmpRcvMsg->enMsgId)
    {

        /* ��ȡ״̬����ַ,����ȡ״̬ */
        pstFsmCtx = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);

        switch(pstFsmCtx->enMainState)
        {
            case EMM_MS_REG:
            case EMM_MS_REG_INIT:
            case EMM_MS_TAU_INIT:
            case EMM_MS_SER_INIT:
                 NAS_EMM_SmRabmAbnarmalProc();
                 break;
            default:
                 NAS_LMM_PUBM_LOG1_INFO("current MS discard abnormal MSG=========>>>>",
                                        pstTmpRcvMsg->enMsgId);
                 TLPS_PRINT2LAYER_INFO1(NAS_EMM_MsgPreProcess_ENUM,LNAS_FUNCTION_LABEL1,pstTmpRcvMsg->enMsgId);
                 break;
        }
        ulRet                           = NAS_LMM_MSG_HANDLED;
    }

    return  ulRet;
}
VOS_VOID    NAS_EMM_SmRabmAbnarmalProc( VOS_VOID )
{

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SmRabmAbnarmalProc is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SmRabmAbnarmalProc_ENUM,LNAS_ENTRY);

    /* ��λ����*/
    NAS_EMM_SendMmcErrInd(NAS_EMM_REBOOT_TYPE_ESM_ABNORMAL);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PUB_SendMmcStartReq
 Description     : ��MMC����MMC_EMM_START_REQ��Ϣ
 Input           : None
 Output          : None
 Return          :

 History         :
    1.qilili00145085     2009-01-23 Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PUB_SendMmcStartReq( VOS_UINT32 encause  )
{
    EMMC_EMM_START_REQ_STRU              *pstMmcStartReqMsg;
    VOS_UINT32                          ulMsgLengthNoHeader;
    VOS_UINT32                          ulSendResult;

    /* ����EMMҪ�����ڲ�����ģ����ڲ���Ϣ����, ������VOSͷ */
    ulMsgLengthNoHeader = NAS_EMM_PUB_INTRAMSG_LENGTH_NO_HEADER(EMMC_EMM_START_REQ_STRU);

    /* ��ȡ�ڲ���Ϣ��ַ */
    pstMmcStartReqMsg = (VOS_VOID *) NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLengthNoHeader);
    if (NAS_EMM_NULL_PTR == pstMmcStartReqMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_PLMN_SendMmcStartReq: GET INTRAMSG ADDR ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PUB_SendMmcStartReq_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /* ����ڲ���Ϣͷ */
    NAS_EMM_COMP_INTRA_MSG_HEADER((pstMmcStartReqMsg), ulMsgLengthNoHeader);

    /* ����ڲ���ϢID */
    pstMmcStartReqMsg ->enMsgId         = ID_EMMC_EMM_START_REQ;

    /* �����Ϣ�� */
    pstMmcStartReqMsg->enCause          = encause;

    /* ��MMC����MMC_EMM_START_REQ�ڲ���Ϣ */
    NAS_EMM_SEND_INTRA_MSG(             pstMmcStartReqMsg);
    ulSendResult =                      NAS_EMM_OK;
    return ulSendResult;
}
VOS_VOID    NAS_EMM_PUB_SendEsmStatusInd
(
    VOS_UINT32  ulATTACHStatus
)
{
    EMM_ESM_STATUS_IND_STRU                *pstsmstatusInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú���*/
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_PUB_SendEsmStatusInd is entered.", ulATTACHStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PUB_SendEsmStatusInd_ENUM,LNAS_ENTRY,ulATTACHStatus);

    /* ����DOPRA��Ϣ */
    pstsmstatusInd  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_STATUS_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstsmstatusInd)
    {
        return;
    }

    /* ����ESM��DOPRAͷ */
    NAS_EMM_COMP_ESM_MSG_HEADER(pstsmstatusInd, sizeof(EMM_ESM_STATUS_IND_STRU) -
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* �����ϢID */
    pstsmstatusInd->ulMsgId             = ID_EMM_ESM_STATUS_IND;

    /* �����Ϣ���� -- stATTACHStatus */
    pstsmstatusInd->enEMMStatus         = ulATTACHStatus;

    /*clear global:EpsContextStatusChange*/
    if(ulATTACHStatus == EMM_ESM_ATTACH_STATUS_DETACHED)
    {
        NAS_EMM_GetEpsContextStatusChange() = NAS_EMM_EPS_BEARER_STATUS_NOCHANGE;
    }

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstsmstatusInd);

    return;

}

#if (FEATURE_LPP == FEATURE_ON)
VOS_VOID NAS_LMM_SndLmmLppDataInd
(
    NAS_EMM_ADDITIONAL_INFOR_STRU               *pstAdditionalInfo,
    NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU      *pstContainer
)
{
    LMM_LPP_DATA_IND_STRU                  *pLmmLppDataInd      = NAS_EMM_NULL_PTR;
    VOS_UINT32                              ulTmpLength         = 0;

    NAS_EMM_PUBU_LOG_NORM("NAS_LMM_SndLmmLppDataInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SndLmmLppDataInd_ENUM, LNAS_LPP_Func_Enter);

    if( 0 == pstContainer->usMsgLen)
    {
        return ;
    }
    else if(pstContainer->usMsgLen > NAS_EMM_4BYTES_LEN)
    {
        ulTmpLength = pstContainer->usMsgLen - NAS_EMM_4BYTES_LEN ;
        pLmmLppDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_DATA_IND_STRU) + ulTmpLength);
    }
    else/*�������С��NAS_EMM_4BYTES_LEN������Ŀռ����NAS_EMM_4BYTES_LEN*/
    {
        ulTmpLength = 0;
        pLmmLppDataInd = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(LMM_LPP_DATA_IND_STRU));
    }

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pLmmLppDataInd)
    {
        return ;
    }

    /*����ID_LMM_LPP_DATA_IND��Ϣ*/
    /*�����Ϣͷ*/
    NAS_EMM_LPP_MSG_HEADER(pLmmLppDataInd,
                           ((sizeof(LMM_LPP_DATA_IND_STRU) + ulTmpLength) - NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pLmmLppDataInd->ulMsgId = ID_LMM_LPP_DATA_IND;

    /*�����Ϣ����*/
    /*���sessionId*/
    NAS_LMM_MEM_CPY(&(pLmmLppDataInd->ulSessionId),  pstAdditionalInfo->aucMsg, pstAdditionalInfo->ucMsgLen);

    /*���LPP�տ�����*/
    pLmmLppDataInd->stLppMsg.ulLppMsgSize = pstContainer->usMsgLen;
    NAS_LMM_MEM_CPY(pLmmLppDataInd->stLppMsg.aucLppMsg,
                    pstContainer->aucMsg,
                    pLmmLppDataInd->stLppMsg.ulLppMsgSize);

    /*��LPP����ID_LMM_LPP_DATA_IND��Ϣ*/
    NAS_LMM_SEND_MSG(pLmmLppDataInd);

    return;
}
#endif
VOS_UINT32  NAS_EMM_PreProcMsgDlNasGenericTransport( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
#if (FEATURE_LPP == FEATURE_ON)
    NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU *pTmpRcvMsg          = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgDlNasGenericTransport is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_Func_Enter);

    pTmpRcvMsg = (NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU*)pCnMsg;

    if (NAS_EMM_GENERIC_CONTAINER_TYPE_LPP == pTmpRcvMsg->ucContainerType)
    {
        if (NAS_EMM_BIT_SLCT != pTmpRcvMsg->bitOpAdditionalInfo)
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_PreProcMsgDlNasGenericTransport: LPP MSG no additional info");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_NoAdditionInfo);

            return NAS_LMM_MSG_HANDLED;
        }

        NAS_LMM_SndLmmLppDataInd(&(pTmpRcvMsg->stAdditionalInfo),
                                 &(pTmpRcvMsg->stContainer));
    }

    if (NAS_EMM_GENERIC_CONTAINER_TYPE_LCS == pTmpRcvMsg->ucContainerType)
    {
        NAS_LMM_SndLcsDataInd(&(pTmpRcvMsg->stContainer));
    }

    return NAS_LMM_MSG_HANDLED;
#else
    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_PreProcMsgDlNasGenericTransport:LPP FEATURE NOT SUPPORT");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgDlNasGenericTransport_ENUM, LNAS_LPP_LppFeatureNotSupport);
    return NAS_LMM_MSG_HANDLED;
#endif
}


/*lint -e826 */

VOS_UINT32  NAS_EMM_PreProcMsgDataInd( VOS_VOID )
{
    VOS_UINT32                           ulRet;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgDataInd enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDataInd_ENUM,LNAS_ENTRY);

    /*������Ϣ���ͽ��벻ͬ�Ĵ��������������EmmInformation����EmmStatus��Ϣ�ͽ���״̬��*/
    if (NAS_EMM_CN_MT_EMM_INFO == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgEmmInfo(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_MT_EMM_STATUS == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgEmmStatus(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgDlNasTransport(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    else if (NAS_EMM_CN_CS_SER_NOTIFICATION == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgCsSerNotification(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    #if (FEATURE_LPP == FEATURE_ON)
    else if (NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT == g_stCnDecodeMsgStru.ulCnMsgType)
    {
        ulRet = NAS_EMM_PreProcMsgDlNasGenericTransport(&(g_stCnDecodeMsgStru.uCnMsgStru));
    }
    #endif
    else
    {
        ulRet = NAS_LMM_MSG_DISCARD;
    }

    return ulRet;
}
VOS_UINT32  NAS_EMM_PreProcMsgEmmInfo( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_INFO_STRU                   *pstEmmInfo;
    NAS_EMM_CN_EMM_INFO_STRU            *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucCount = 0;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgEmmInfo enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEmmInfo_ENUM,LNAS_ENTRY);

    pstTmpRcvMsg               = (NAS_EMM_CN_EMM_INFO_STRU*)pCnMsg;
    pstEmmInfo                 = NAS_LMM_GetEmmInfoNasEmmInfoListAddr();

    NAS_LMM_MEM_SET(pstEmmInfo, 0, sizeof(NAS_EMM_INFO_STRU));

    /* �ϱ�����ʱ����������ƣ�ֻҪ���յ����Ϳ����ϱ���AT��������û��Ӱ�죬���Բ������ƣ�
    ����δע��ʱ������Ҳ������������Ϣ�·�*/
    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpFullName)
    {
        pstEmmInfo->bitOpFullName           = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                   pstEmmInfo->aucOperatorNameLong,
                                           pstTmpRcvMsg->aucOperatorNameLong,
                                           MMC_LMM_MAX_OPER_LONG_NAME_LEN);
        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpShortName)
    {
        pstEmmInfo->bitOpShortName          = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                   pstEmmInfo->aucOperatorNameShort,
                                           pstTmpRcvMsg->aucOperatorNameShort,
                                           MMC_LMM_MAX_OPER_SHORT_NAME_LEN);
        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpLocTimeZone)
    {
        pstEmmInfo->bitOpLocTimeZone        = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                   &(pstEmmInfo->stLocTimeZone),
                                           &(pstTmpRcvMsg->stLocTimeZone),
                                           sizeof(NAS_EMM_CN_TIMEZONE_STRU));
        ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpUniTimeLocTimeZone)
    {
        pstEmmInfo->bitOpUniTimeLocTimeZone = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                   &(pstEmmInfo->stTimeZoneAndTime),
                                           &(pstTmpRcvMsg->stTimeZoneAndTime),
                                           sizeof(NAS_EMM_CN_TIMEZONE_UNITIME_STRU));
    ucCount++;
    }

    if(NAS_EMM_BIT_SLCT == pstTmpRcvMsg->bitOpDaylightTime)
    {
        pstEmmInfo->bitOpDaylightTime       = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(                   &(pstEmmInfo->enDaylightSavingTime),
                                           &(pstTmpRcvMsg->enDaylightSavingTime),
                                           sizeof(NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8));
        ucCount++;
    }
    if(0 != ucCount)
    {
        NAS_EMM_SendMmcEmmInfoInd(pstEmmInfo);
    }
    return NAS_LMM_MSG_HANDLED;
}
/*lint +e826 */

VOS_UINT32  NAS_EMM_PreProcMsgEmmStatus( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_CN_EMM_STATU_STRU           *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_PreProcMsgEmmStatus enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEmmStatus_ENUM,LNAS_ENTRY);

    /*�ṹ����Ϣ��ȡ����Ϣ��*/
    pstTmpRcvMsg                 = (NAS_EMM_CN_EMM_STATU_STRU *)pCnMsg;

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_PreProcMsgEmmStatus: EMM ERROR CAUSE ",pstTmpRcvMsg->ucEmmCause);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgEmmStatus_ENUM,LNAS_CAUSE_NUMBER,pstTmpRcvMsg->ucEmmCause);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgDlNasTransport
 Description     : Ԥ�������������NAS͸����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing 49683      2011-11-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgDlNasTransport( NAS_EMM_CN_MSG_STRU_UNION  * pCnMsg )
{
    NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU *pTmpRcvMsg          = NAS_EMM_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgDlNasTransport is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgDlNasTransport_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = (NAS_EMM_CN_DOWNLINK_NAS_TRANSPORT_STRU*)pCnMsg;

    NAS_LMM_SndLmmSmsDataInd(pTmpRcvMsg->aucDownlinkNasTransportMsg,
                             pTmpRcvMsg->ucDownlinkNasTransportLen);

    return NAS_LMM_MSG_HANDLED;
}



VOS_VOID  NAS_EMM_ProcMsgCsSerNotification(
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU          *pstCsSerNotification
)
{
    /* ����÷�֧�Ŀ϶���MT���͵�CSFB */
    if (NAS_EMM_FAIL == NAS_EMM_SER_VerifyMtCsfb())
    {
        /* ����UE�ܾ�CSFB */
        NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

        /* ����EXTENDED SERVICE REQ��Ϣ��֪ͨ����CSFB���ܷ��� */
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
    }
    else
    {
        /* ��MMģ�鷢��MM_MM_CSFB_SERVICE_PAGING_IND��Ϣ */
        NAS_EMM_MmSendCsfbSerPaingInd(NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION,
                                        pstCsSerNotification,
                                        LRRC_PAGE_UE_ID_BUTT);
    }

    return;
}




VOS_UINT32  NAS_EMM_PreProcMsgCsSerNotification
(
    NAS_EMM_CN_MSG_STRU_UNION           *pCnMsg
)
{
    VOS_UINT32                           ulCurEmmStat = NAS_EMM_NULL;
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM,LNAS_ENTRY);

    pstCsSerNotification = (NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *)pCnMsg;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT, NAS_EMM_CUR_SUB_STAT);

    /* ������ͷŹ����У�ֱ�Ӵ����(��Ȧ���Ӷ�) */
    if ((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
      ||(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_T3440)))
    {
        NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
        return NAS_LMM_MSG_HANDLED;
    }

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_NORMAL_SERVICE)         :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH)          :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,  EMM_SS_TAU_WAIT_CN_TAU_CNF)        :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_ATTEMPTING_TO_UPDATE)   :
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):

                NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,  EMM_SS_SER_WAIT_CN_SER_CNF):

                /* �������й����У��յ����У���ֱ�Ӷ��������й������յ�
                CS SERVICE NOTIFICATION��Ϣ�������ط�����Ҫ���·���ESR */
                if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause())
                    && (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ != NAS_EMM_SER_GetEmmSERStartCause()))
                {
                    NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                }
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,        EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):

                /* ����UE�ܾ�CSFB */
                NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
                NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

                /* ����EXTENDED SERVICE REQ��Ϣ��֪ͨ����CSFB���ܷ��� */
                NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,  EMM_SS_ATTACH_WAIT_RRC_DATA_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,  EMM_SS_ATTACH_WAIT_ESM_BEARER_CNF):

                /* ��MMģ�鷢��MM_MM_CSFB_SERVICE_PAGING_IND��Ϣ */
                NAS_EMM_MmSendCsfbSerPaingInd(NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION,
                                              pstCsSerNotification,
                                              LRRC_PAGE_UE_ID_BUTT);
                break;

        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,       EMM_SS_REG_LIMITED_SERVICE)     :

                /* �����IMS�绰��֪ͨ���಻�ܷ���CSFB��������MM��PAGING IND */
                #if (FEATURE_ON == FEATURE_IMS)
                if (VOS_TRUE == IMSA_IsCallConnExist())
                {
                    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification:IMS call is going!");
                    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM, LNAS_FUNCTION_LABEL1);

                    /* ����UE�ܾ�CSFB */
                    NAS_EMM_SER_SaveEmmSerCsfbRsp(NAS_EMM_CSFB_RSP_REJECTED_BY_UE);
                    NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ);

                    /* ����EXTENDED SERVICE REQ��Ϣ��֪ͨ����CSFB���ܷ��� */
                    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
                }
                else
                #endif
                {
                    NAS_EMM_ProcMsgCsSerNotification(pstCsSerNotification);
                }
                break;

        default :
                #if (FEATURE_PTM == FEATURE_ON)
                NAS_EMM_PagingErrRecord(EMM_OM_ERRLOG_PAGING_CS,EMM_OM_LMM_PAGING_FAIL_CAUSE_ABNORMAL_STATUS);
                #endif
                NAS_EMM_PUBU_LOG_NORM("NAS_EMM_PreProcMsgCsSerNotification:Illegal state!");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgCsSerNotification_ENUM, LNAS_ERROR);
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}

/*lint -e669*/

VOS_VOID  NAS_EMM_SendMsgEmmStatus( VOS_UINT8 ucRes )
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pIntraMsg;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;
    NAS_MSG_STRU                       *pstNasMsg;
    VOS_UINT32                          ulIndex             =0;

    NAS_EMM_ATTACH_LOG_INFO("Enter NAS_EMM_SendMsgEmmStatus,Status MSG LEN");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMsgEmmStatus_ENUM,LNAS_ENTRY);

    /*������Ϣ�ڴ�*/
    pIntraMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /* xiongxianghui00253310 add memset 2013-11-26 begin */
    NAS_LMM_MEM_SET(pIntraMsg, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);
    /* xiongxianghui00253310 add memset 2013-11-26 end   */

    /*����EmmStatus��Ϣ*/
    NAS_EMM_CompCnEmmStatus(            &(pIntraMsg->stNasMsg),&ulIndex,ucRes);

    ulDataReqMsgLenNoHeader             = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendMsgEmmStatus, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMsgEmmStatus_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pIntraMsg);
        return ;
    }

    /*�����Ϣͷ*/
    NAS_EMM_INTRA_MSG_HEADER(pIntraMsg, ulDataReqMsgLenNoHeader);

    /*�����ϢID*/
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*�����Ϣ����*/
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_NAS_STATUS;

    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NOT_NEED;

    /*�����Ϣ����*/
    pIntraMsg->stNasMsg.ulNasMsgSize    = ulIndex;

    /*��OM���Ϳտ���ϢATTACH COMPLETE*/
    pstNasMsg = (NAS_MSG_STRU *)(&(pIntraMsg->stNasMsg));
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_STATUS, pstNasMsg);

    /*��MRRC������Ϣ*/
    NAS_EMM_SndUplinkNasMsg(             pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);
    return;
}
/*lint +e669*/

VOS_VOID   NAS_EMM_CompCnEmmStatus( LRRC_LNAS_MSG_STRU    *pEmmStatus,
                                                  VOS_UINT32          *pulIndex,
                                                  VOS_UINT8            ucEmmCause)
{
    VOS_UINT32                          ulIndex             = *pulIndex;

    /*������CN��Ϣ�Ŀռ�*/
    /* xiongxianghui00253310 delete memset 2013-11-26 begin */
    /* NAS_LMM_MEM_SET(pEmmStatus->aucNasMsg, 0, pEmmStatus->ulNasMsgSize); */
    /* xiongxianghui00253310 delete memset 2013-11-26 end   */

    /* ��� Protocol Discriminator + Security header type */
    pEmmStatus->aucNasMsg[ulIndex++]       = EMM_CN_MSG_PD_EMM;

    /* ���  message identity */
    pEmmStatus->aucNasMsg[ulIndex++]       = NAS_EMM_CN_MT_EMM_STATUS;

    /*���Status Cause */
    pEmmStatus->aucNasMsg[ulIndex++]       = ucEmmCause;

    *pulIndex                              = ulIndex;

    return;
}


VOS_UINT32  NAS_LMM_PreProcMmcDisableReq( MsgBlock  *pMsg )
{
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcDisableReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcDisableReq_ENUM,LNAS_ENTRY);

    /* ����������IDLE̬����ֱ�Ӷ���*/
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_PreProcMmcDisableReq:NOT IDLE.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcMmcDisableReq_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_HANDLED;
    }
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    /* ��¼LTE���뼼��ΪDISABLE̬*/
    NAS_EMM_SetLteEnableSta(            NAS_LMM_LTE_DISABLED);

    /* ���T3412Exp��־*/
    NAS_LMM_SetEmmInfoT3412ExpCtrl(    NAS_EMM_T3412_EXP_NO);
    /*NAS_LMM_SetEmmInfoUpdateMmFlag(NAS_EMM_UPDATE_MM_FLAG_INVALID);*/

    /*���DrxNetCapability��־*/
    NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_NO);

    /*���RRCɾ��ԭ���ʶ*/
    NAS_LMM_SetEmmInfoTriggerTauRrcRel(NAS_EMM_TRIGGER_TAU_RRC_REL_NO);

    /* ���GU�����LAU��������RAU��ʶ*/
    NAS_LMM_SetEmmInfoLauOrComRauFlag(NAS_EMM_LAU_OR_COMBINED_RAU_NOT_HAPPENED);
    NAS_LMM_SetEmmInfoSrvccFlag(NAS_EMM_SRVCC_NOT_HAPPENED);
    /*��� EPS ���������ı����־*/
    NAS_EMM_SetEpsContextStatusChange(NAS_EMM_EPS_BEARER_STATUS_NOCHANGE);
    NAS_LMM_SetEmmInfoTriggerTauSysChange(NAS_EMM_NO);

    /* ���VOICE DOMAIN�����仯�ı�ʶ */
    NAS_EMM_SetVoiceDomainChange(NAS_EMM_NO);
    NAS_LMM_SetEmmInfoLaiChangeFlag(VOS_FALSE);
    NAS_LMM_SetEmmInfoCsEmcConneExitFlag(VOS_FALSE);
    /* �����ϵͳ�任���������ͼ�¼��Ϣ */
    NAS_EMM_ClearResumeInfo();

    NAS_LMM_SetEmmInfoPsState(GMM_LMM_GPRS_NOT_SUSPENSION);

    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */

    NAS_EMM_ClrAllUlDataReqBufferMsg();


    /*�ο�Э��24301��5.5.3.3.4.2��  5.5.3.3.4.3��
      5.5.1.3.4.2����ǰ����λ��������&IMS�����ã� ���
      TAU 5�ζ���eps only�ɹ�����ʱ��disable LTE����ʱ
      ��Ҫֹͣ��ʱ��3402������ص�L��ʱ�򲻻���������TAU
    */
    /*NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3402);*/
    /* ���֮ǰTAU��ATTACH���ΪEPS ONLY��ԭ��ֵΪ16/17/22������UE����ģʽΪCSPS1��
    ��������3402��ʱ��������Ҫ���ö�ʱ��ͣ�� */
    if (VOS_TRUE == NAS_LMM_IsNeedStop3402Timer())
    {
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
        NAS_LMM_Stop3402Timer();
        /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
    }

    /* ����AT&T��������: disable LTE���CService���� */
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    /* ֪ͨLRRC��ǰLTE��disable */
    NAS_LMM_SendRrcDisableLteNotify();
    /* ������: �����ϵͳTAU��־���ñ�־����ϵͳTAUʱ���� */
    NAS_EMM_SetOmInterTauFlag(NAS_EMM_NO);
    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_LMM_PreProcMmcEnableReq
 Description     : �յ�MMC Enable LTE������Ĵ���

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan      2011-11-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LMM_PreProcMmcEnableReq( MsgBlock  *pMsg )
{
    (void)pMsg;
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcMmcEnableReq Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcMmcEnableReq_ENUM,LNAS_ENTRY);

    /* ��¼LTE���뼼��ΪENABLE̬*/
    NAS_EMM_SetLteEnableSta(            NAS_LMM_LTE_ENABLED);

    return NAS_LMM_MSG_HANDLED;
}

/*leili modify for isr begin*/
/*PC REPLAY MODIFY BY LEILI BEGIN*/

VOS_UINT32  NAS_EMM_IsBearIsrActBefore
(
    VOS_UINT32      ulEpsId
)
{
    VOS_UINT32                              ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = NAS_MML_IsPsBearerExistBeforeIsrAct((VOS_UINT8)ulEpsId);

    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsBearIsrActBefore:ulRslt = ",ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsBearIsrActBefore_ENUM,LNAS_FUNCTION_LABEL1,ulRslt);

    NAS_LMM_LogIsBearIsrActBeforeInfo(ulRslt);

    #else
    ulRslt = Stub_NAS_MML_IsPsBearerExistBeforeIsrAct();
    #endif

    if (VOS_TRUE == ulRslt)
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}


VOS_UINT32  NAS_EMM_IsBearIsrActAfter(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = NAS_MML_IsPsBearerAfterIsrActExist();

    NAS_LMM_LogIsBearIsrActAfterInfo(ulRslt);

    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsBearIsrActAfter:ulRslt = ",ulRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsBearIsrActAfter_ENUM,LNAS_FUNCTION_LABEL1,ulRslt);
    #else
    ulRslt = Stub_NAS_MML_IsPsBearerAfterIsrActExist();
    #endif
    if (VOS_TRUE == ulRslt)
    {
        return NAS_EMM_SUCC;
    }
    else
    {
        return NAS_EMM_FAIL;
    }
}
/*PC REPLAY MODIFY BY LEILI END*/

VOS_VOID  NAS_EMM_UpdateBearISRFlag(NAS_MML_PS_BEARER_CONTEXT_STRU  *pstBearerCtx)
{
     VOS_UINT32                          i = NAS_EMM_NULL;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_UpdateBearISRFlag Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UpdateBearISRFlag_ENUM,LNAS_ENTRY);

    if (NAS_EMM_NULL_PTR == pstBearerCtx)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_UpdateBearISRFlag:Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_UpdateBearISRFlag_ENUM,LNAS_NULL_PTR);
        return;
    }

    for (i = 0; i < EMM_ESM_MAX_EPS_BEARER_NUM; i++)
    {
        pstBearerCtx[i].enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
    }
    return;
}


VOS_UINT32  NAS_EMM_PreProcMsgEsmBearModifyReq
(
    MsgBlock *          pMsg
)
{
    EMM_ESM_BEARER_MODIFY_REQ_STRU      *pstBearModReq = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulMatchRslt;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;
    ulTinType = NAS_EMM_GetTinType();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */

    pstBearModReq = (VOS_VOID*)pMsg;

    ulMatchRslt = NAS_EMM_IsBearIsrActBefore(pstBearModReq->ulEpsId);

    NAS_LMM_PUBM_LOG3_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq:NAS_EMM_GetCurLteState()=,\
          NAS_EMM_GetTinType()= , NAS_EMM_IsBearIsrActBefore()= ",
          NAS_EMM_GetCurLteState(),
          ulTinType,
          ulMatchRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL1,NAS_EMM_GetCurLteState());
    /* coverity[unchecked_value] */
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL2,
          ulTinType,
          ulMatchRslt);
    if(NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
    {

        return NAS_LMM_MSG_HANDLED;
    }

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq: GET MML PS BEARER INFO:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL3);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    if ((MMC_LMM_TIN_RAT_RELATED_TMSI == ulTinType) &&
        (NAS_EMM_SUCC == ulMatchRslt))
    {
        /*����TINֵΪGUTI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_GUTI);
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        /*�������г��ص�ISR��ʶΪISR����ǰ*/
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
        /*PC REPLAY MODIFY BY LEILI END*/
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgEsmBearStatusReq: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgEsmBearModifyReq_ENUM,LNAS_FUNCTION_LABEL4);

    }

    return NAS_LMM_MSG_HANDLED;
}

/* lihong00150010 emergency tau&service begin */

VOS_UINT32  NAS_EMM_PreProcMsgT3412Exp(MsgBlock *          pMsg )
{
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32           ulForbdInfo;
    NAS_MM_TA_STRU                                stTa;
    VOS_UINT32                                    ulSendResult;

    (void)pMsg;
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_PreProcMsgT3412Exp enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3412Exp_ENUM,LNAS_ENTRY);

    /*֪ͨGUģt3412��ʱ*/
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_EXP);

    /*
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);
    */

    /*add by lifuxin for Lnas est process re-construct start*/
    /*��ǰ��״̬��NAS_EMM_CONN_ESTING����˵�����ڽ����������յ���������TAU��ʱ
      ���ó�ʱ��ǣ��ñ�Ǹ���δ�����?�������:
      1. ��TAU����service�����У������ɹ���TAU, SERVCIE�ɹ�����ñ�ʾ�����ٷ�������TAU
      2. ��TAU����service�����У��������ʧ�ܣ���ת����Ӧ��״̬֮�󣬵ȴ�RRC����פ����
      �ϱ�ϵͳ��Ϣ֮�󣬷���TAU֮ǰ���жϸñ�ʶ��ȷ���Ƿ�Ҫ��������TAU
    */
    if(NAS_EMM_CONN_ESTING == NAS_EMM_GetConnState())
    {
        /*��������TAU��ʱ����ʾ*/
        NAS_LMM_SetEmmInfoT3412ExpCtrl(NAS_EMM_T3412_EXP_YES_OTHER_STATE);
        return NAS_LMM_MSG_HANDLED;
    }
    /*add by lifuxin for Lnas est process re-construct end*/

    /* ���ע��״̬��Ϊ����ע�ᣬ����Ҫ����״̬�����д��� */
    if (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus())
    {
        return NAS_LMM_MSG_DISCARD;
    }

    /* ����ǽ���ע�ᣬ����DETACH */
    NAS_EMM_EsmSendStatResult(  EMM_ESM_ATTACH_STATUS_DETACHED);

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                EMM_SS_DEREG_NORMAL_SERVICE,
                                TI_NAS_EMM_STATE_NO_TIMER);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /* ��ȡС���Ƿ񱻽���ʶ��TA��Ϣ */
    NAS_EMMC_GetCurrentForbInfo(&ulForbdInfo);
    NAS_EMMC_GetCurrentTa(&stTa);

    /* ���С���������߷����������򷵻� */
    if ((EMMC_EMM_NO_FORBIDDEN != ulForbdInfo)
        || (VOS_TRUE != NAS_LMM_IsCellStatusNormal((MMC_LMM_PLMN_ID_STRU*)(&(stTa.stPlmnId)), &stTa)))
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* ����ATTACH���� */
    ulSendResult = NAS_EMM_SendIntraAttachReq();
    if (NAS_EMM_PLMN_ERR == ulSendResult)
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_PreProcMsgT3412Exp : Send IntraMsg Failure!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgT3412Exp_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_HANDLED;
    }

    return NAS_LMM_MSG_HANDLED;
}
/* lihong00150010 emergency tau&service end */


VOS_UINT32  NAS_EMM_PreProcMsgT3423Exp(MsgBlock *          pMsg )
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
    (void)pMsg;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgT3423Exp is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3423Exp_ENUM,LNAS_ENTRY);
    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    /*֪ͨGUģt3423��ʱ*/
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_EXP);



    if (MMC_LMM_TIN_RAT_RELATED_TMSI == NAS_EMM_GetTinType())
    {
        /*����TINֵΪP-TMSI*/
        NAS_EMM_SetTinType(MMC_LMM_TIN_P_TMSI);
        /*PC REPLAY MODIFY BY LEILI BEGIN*/
        /*���³���ISR��ʶ*/
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
        /*PC REPLAY MODIFY BY LEILI END*/
        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgT3423Exp: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgT3423Exp_ENUM,LNAS_FUNCTION_LABEL2);

    }



    /*����Ҫ����״̬������*/
    return NAS_LMM_MSG_HANDLED;
}

VOS_UINT32  NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg(MsgBlock *    pMsg )
{

    GMM_LMM_TIMER_STATE_NOTIFY_STRU     *pstTimerState;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg_ENUM,LNAS_ENTRY);

    pstTimerState = (VOS_VOID*)pMsg;

    if (NAS_EMM_BIT_SLCT == pstTimerState->bitOpT3312)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg: enT3312State =",
                            pstTimerState->enT3312State);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PreProcMsgGmmTimerStateNotifyMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            pstTimerState->enT3312State);
        NAS_EMM_SetEmmInfoT3312State(pstTimerState->enT3312State);
    }

    return NAS_LMM_MSG_HANDLED;
}

#if (FEATURE_ON == FEATURE_DSDS)

VOS_UINT32  NAS_LMM_PreProcDsdsBeginSessionNotify(MsgBlock *          pMsg)
{
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulIndex = 0;
    MM_SESSION_TYPE_ENUM_UINT32  enInputSessionType;
    MM_SESSION_TYPE_ENUM_UINT32  enOutputSessionType = LRRC_LNAS_SESSION_TYPE_BUTT;
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU *pSessionMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcDsdsBeginSessionNotify Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcDsdsBeginSessionNotify_ENUM,LNAS_ENTRY);

    pSessionMsg = (VOS_VOID*)pMsg;

    /*��ȡ���͵�pid��Ϣ*/
    ulSenderPid = pSessionMsg->ulSenderPid;

    /*��ȡ������Ϣ��Я����session type*/
    enInputSessionType = pSessionMsg->enSessionType;

    /*�������session typeӳ��Ϊ���ص�session type*/
    for(ulIndex=0;ulIndex<g_astDsdsCvtSessionTypeTblLen;ulIndex++)
    {
        if((ulSenderPid == g_astDsdsCvtSessionTypeTbl[ulIndex].ulSenderPid)
            && (enInputSessionType == g_astDsdsCvtSessionTypeTbl[ulIndex].enInputSessionType))
        {
            enOutputSessionType = g_astDsdsCvtSessionTypeTbl[ulIndex].enOutputSessionType;
            g_astDsdsInputNotifyMsgNum[ulIndex].ulBeginMsgCnt++;
            /*DSDS������Ϣ��������*/
            NAS_LMM_SndOmDsdsPreProcMsgInfo(NAS_LMM_DSDS_MSG_TYPE_BEGIN,ulIndex);
            break;
        }
    }

    /*��װҵ��֪ͨ��ʼ��Ϣ���͸�LRRCģ��*/
    if(LRRC_LNAS_SESSION_TYPE_BUTT != enOutputSessionType)
    {
        NAS_LMM_SendRrcDsdsBeginNotify((LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)enOutputSessionType);
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_LMM_PreProcDsdsEndSessionNotify(MsgBlock *          pMsg)
{
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulIndex = 0;
    MM_SESSION_TYPE_ENUM_UINT32  enInputSessionType;
    MM_SESSION_TYPE_ENUM_UINT32  enOutputSessionType = LRRC_LNAS_SESSION_TYPE_BUTT;
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU *pSessionMsg;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcDsdsBeginSessionNotify Enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcDsdsEndSessionNotify_ENUM,LNAS_ENTRY);

    pSessionMsg = (VOS_VOID*)pMsg;

    /*��ȡ���͵�pid��Ϣ*/
    ulSenderPid = pSessionMsg->ulSenderPid;

    /*��ȡ������Ϣ��Я����session type*/
    enInputSessionType = pSessionMsg->enSessionType;

    /*�������session typeӳ��Ϊ���ص�session type*/
    for(ulIndex=0;ulIndex<g_astDsdsCvtSessionTypeTblLen;ulIndex++)
    {
        if((ulSenderPid == g_astDsdsCvtSessionTypeTbl[ulIndex].ulSenderPid)
            && (enInputSessionType == g_astDsdsCvtSessionTypeTbl[ulIndex].enInputSessionType))
        {
            enOutputSessionType = g_astDsdsCvtSessionTypeTbl[ulIndex].enOutputSessionType;
            g_astDsdsInputNotifyMsgNum[ulIndex].ulEndMsgCnt++;
            /*DSDS������Ϣ��������*/
            NAS_LMM_SndOmDsdsPreProcMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ulIndex);
            break;
        }
    }

    /*��װҵ��֪ͨ������Ϣ���͸�LRRCģ��*/
    if(LRRC_LNAS_SESSION_TYPE_BUTT != enOutputSessionType)
    {
        NAS_LMM_SendRrcDsdsEndNotify((LRRC_LNAS_SESSION_TYPE_ENUM_UINT8)enOutputSessionType);
    }

    return NAS_LMM_MSG_HANDLED;
}
#endif

/*lint +e961*/
/*lint +e960*/
/*PC REPLAY MODIFY BY LEILI BEGIN*/
#if(VOS_WIN32 == VOS_OS_VER)
/*��������ʱ������*/

VOS_VOID    NAS_EMM_PUB_SendEsmExportCtx(VOS_VOID)
{
    EMM_ESM_EXPORT_CTX_IND_STRU                *pstEsmExportCtx = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú���*/
    vos_printf("NAS_EMM_PUB_SendEsmExportCtx is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUB_SendEsmExportCtx_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pstEsmExportCtx  = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_EXPORT_CTX_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstEsmExportCtx)
    {
        return;
    }

    /* ����ESM��DOPRAͷ */
    NAS_EMM_COMP_ESM_MSG_HEADER(pstEsmExportCtx, sizeof(EMM_ESM_EXPORT_CTX_IND_STRU) -
                                        NAS_EMM_LEN_VOS_MSG_HEADER);

    /* �����ϢID */
    pstEsmExportCtx->ulMsgId             = ID_EMM_ESM_REPLAY_EXPORT_CTX_IND;

    /* �����Ϣ����  */



    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstEsmExportCtx);

    return;

}



VOS_UINT32  NAS_EMM_PreProcMsgReplay(MsgBlock *          pMsg )
{
    (void)pMsg;

    vos_printf("NAS_EMM_PreProcMsgReplay is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgReplay_ENUM,LNAS_ENTRY);

    /*����EMMģ��ȫ�ֱ���*/
    (void)NAS_EMM_ExportContextData();


    /*��ESM����NAS_REPLAY_ESM_EXPORT_CTX_IND��Ϣ����ESM/ERABM��ȫ�ֱ���*/
    NAS_EMM_PUB_SendEsmExportCtx();

    /*����Ҫ����״̬������*/
    return NAS_LMM_MSG_HANDLED;
}
#endif
/*PC REPLAY MODIFY BY LEILI END*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ��ϵͳ+ģ��+�ļ���.c */
