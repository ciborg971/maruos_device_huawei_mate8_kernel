

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmTauSerInclude.h"
#include  "NasLmmPubMPrint.h"
#include  "EmmTcInterface.h"
#include  "NasLmmPubMOm.h"
/* lihong00150010 emergency tau&service begin */
#include  "NasEmmAttDetInclude.h"
/* lihong00150010 emergency tau&service end */
#if (FEATURE_LPP == FEATURE_ON)
#include    "NasEmmLppMsgProc.h"
#include    "EmmLppInterface.h"
#include    "NasEmmSsMsgProc.h"
#include    "NasEmmSerProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSERVICEPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSERVICEPROC_C
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
NAS_EMM_SER_CTRL_STRU                   g_stEmmSERCtrlTbl;
NAS_EMM_SER_ESM_MSG_BUF_STRU            g_stEmmEsmMsgBuf;

/* ESR���̷����л�,δ����TAU,�ش�ESR��Ϣ���ƿ���:���С���л������಻�·�REL���� */
VOS_UINT32                              g_ulNasEmmHoRetransEsrFlag = PS_FALSE;
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_SER_Init(VOS_VOID)
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_Init                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_Init_ENUM,LNAS_BEGIN);

    NAS_LMM_MEM_SET(&g_stEmmSERCtrlTbl, 0, sizeof(g_stEmmSERCtrlTbl));

    NAS_LMM_MEM_SET(&g_stEmmEsmMsgBuf, 0, sizeof(g_stEmmEsmMsgBuf));

    return;
}


VOS_VOID  NAS_EMM_SER_ClearResource( VOS_VOID )
{
    NAS_EMM_SER_LOG_NORM("NAS_EMM_SER_ClearResource entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_ClearResource_ENUM,LNAS_ENTRY);

    /* ���SERȫ�ֱ���*/
    NAS_LMM_MEM_SET(&g_stEmmSERCtrlTbl, 0, sizeof(g_stEmmSERCtrlTbl));

    /* �ͷŻ����ESM��Ϣ*/
    NAS_EMM_SerClearEsmDataBuf();

    /* ��ս���Bar��Ϣ*/
    NAS_EMM_ClearBarResouce();

    /* ֹͣService������ص����ж�ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    return;
}


VOS_VOID  NAS_EMM_FreeSerDyn( VOS_VOID )
{
    /* �ͷ�SERVICEģ�黺���ESM����Ϣ */
    NAS_EMM_SerClearEsmDataBuf();

    return;
}
VOS_VOID NAS_EMM_SER_CompCnServiceReq(  LRRC_LNAS_MSG_STRU   *pNasMsg)
{
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT8                           ucKsiSn;
    VOS_UINT8                           ucKsi;
    VOS_UINT8                           ucSequenceNum;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_CompCnServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CompCnServiceReq_ENUM,LNAS_ENTRY);

    /* ��ս����CN��Ϣ�Ŀռ� */
    /* xiongxianghui00253310 delete memset 2013-11-26 begin */
    /* NAS_LMM_MEM_SET(pNasMsg->aucNasMsg, 0, pNasMsg->ulNasMsgSize); */
    /* xiongxianghui00253310 delete memset 2013-11-26 end   */

    /* ��� Security header type  +  Protocol discriminator */
    pNasMsg->aucNasMsg[ulIndex++]       = EMM_CN_SECURITY_HEADER_TYPE_SER_REQ;

    /* ���� KsiSn*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    ucSequenceNum = (VOS_UINT8)NAS_EMM_SecuGetUlNasCountVAlue();
    ucSequenceNum = ucSequenceNum & EMM_TAUSER_LOW5_BITS;
    ucKsiSn = ((VOS_UINT8)(ucKsi << 5)) | ucSequenceNum;


    /* ��� KSI and sequence number   */
    pNasMsg->aucNasMsg[ulIndex++]       = ucKsiSn;


    /* ��� Message authentication code */
    /*����ֻ��Ҫ��ʼ��Ϊ0���������Ա���ʱ������������ֽ�*/
    pNasMsg->aucNasMsg[ulIndex++]       = 0;
    pNasMsg->aucNasMsg[ulIndex]         = 0;
    return;
}

/*lint -e669*/

VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ServiceReq()
{
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulDataReqMsgLenNoHeader;
    VOS_UINT32                          ulCnMsgLen;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendMrrcDataReq_ServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendMrrcDataReq_ServiceReq_ENUM,LNAS_ENTRY);

    /* ����NAS_MSG_STRU��Ϣ���� */
    ulCnMsgLen                              = NAS_EMM_COUNT_CN_SER_REQ_LEN;
    ulDataReqMsgLenNoHeader                 = EMM_COUNT_DATA_REQ_LEN(ulCnMsgLen);

    /* ����DOPRA��Ϣ */
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    if(NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    /* xiongxianghui00253310 add memset 2013-11-26 begin */
    NAS_LMM_MEM_SET(pMrrcDataReqMsg, 0, NAS_EMM_INTRA_MSG_MAX_SIZE);
    /* xiongxianghui00253310 add memset 2013-11-26 end   */

    /* ���CSFB ABORT��ʶ */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);
    /* ��дMRRC_DATA_REQ ��DOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, ulDataReqMsgLenNoHeader);

    /* ��дMRRC_DATA_REQ ����ϢID��ʶ */
    pMrrcDataReqMsg->ulMsgId                = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��д����ԭ��*/
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_RRC_PAGING:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MT_ACCESS;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_TERMINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RRC_PAGING);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        case NAS_EMM_SER_START_CAUSE_RABM_REEST:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RABM_REEST);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        case NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        case NAS_ESM_SER_START_CAUSE_UPLINK_PENDING:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_UPLINK_PENDING);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        case NAS_EMM_SER_START_CAUSE_SMS_EST_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_SMS_EST_REQ);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        #if (FEATURE_LPP == FEATURE_ON)
        case NAS_EMM_SER_START_CAUSE_LPP_EST_REQ:
             /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-18,begin */
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_LPP_EST_REQ);
            break;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-18,end */
        case NAS_EMM_SER_START_CAUSE_SS_EST_REQ:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-18,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_SS_EST_REQ);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-18,end */
            break;
        #endif

        /* lihong00150010 emergency tau&service begin */
        case NAS_EMM_SER_START_CAUSE_ESM_DATA_REQ_EMC:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_ESM_DATA_REQ_EMC);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;

        case NAS_EMM_SER_START_CAUSE_RABM_REEST_EMC:
            pMrrcDataReqMsg->enEstCaue = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,begin */
            NAS_LMM_SndOmSerStartTypeInfo(NAS_LMM_OM_SER_START_TYPE_RABM_REEST_EMC);
            /* add by yanglei 00307272 for KEY_INFO_REPORT2, 2015-08-13,end */
            break;
        /* lihong00150010 emergency tau&service end */

        default:
            NAS_EMM_SER_LOG_ERR("Nas_Emm_SER_SendMrrcDataReq_ServiceReq:StartCause ERR");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ServiceReq_ENUM,LNAS_ERROR);
            break;
    }
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_SERVICE_REQ;

    /* ��дMRRC_DATA_REQ ��NAS��Ϣ���ȱ�ʶ */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize  = ulCnMsgLen;

    pMrrcDataReqMsg->enDataCnf              = LRRC_LMM_DATA_CNF_NEED;

    /* ����MRRC_DATA_REQ �е� NAS_MSG_STRU,��CN��Ϣ(Compose the msg of): SER_REQ */
    NAS_EMM_SER_CompCnServiceReq(               &(pMrrcDataReqMsg->stNasMsg));

    /*�տ���Ϣ�ϱ�SER REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_SER_REQ,  (NAS_MSG_STRU*)&(pMrrcDataReqMsg->stNasMsg));

    /*�ؼ��¼��ϱ�SER REQ*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_SER_REQ);
    /* ������: ����SER������� */
    NAS_LMM_AddSerCounter(NAS_LMM_OM_PCE_TIMES_TYPE_TOTAL);
    /* ������Ϣ(Send the msg of) MRRC_DATA_REQ(SER_REQ) */
    NAS_EMM_SndUplinkNasMsg((VOS_VOID*)pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    /* ��¼Ser Req����ʱ�� */
    NAS_EMM_SaveSerReqSndTimeStamp();
    return;
}
/*lint +e669*/


/*****************************************************************************
 Function Name   : NAS_EMM_CompCnExtendedSerReqMoNasMsg
 Description     : ��װEXTENDED SERVICE REQ��Ϣ
 Input           : pulIndex
 Output          : pucCnMsg
                   pulIndex
 Return          : VOS_VOID

 History         :
    1.lihong      2012-02-23  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_CompCnExtendedSerReqMoNasMsg
(
    VOS_UINT8                          *pucCnMsg,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulIndex      = NAS_EMM_NULL;
    VOS_UINT8                           ucKsi        = NAS_EMM_NULL;
    NAS_LMM_PUB_INFO_STRU              *pstEmmInfo   = VOS_NULL_PTR;
    VOS_UINT32                          ulIeLength          = 0;

    ulIndex                 = *pulIndex;
    pstEmmInfo              = NAS_LMM_GetEmmInfoAddr();

    /* ��� Protocol Discriminator + Security header type*/
    pucCnMsg[ulIndex++]     = EMM_CN_MSG_PD_EMM;

    /* ��� Detach request message identity */
    pucCnMsg[ulIndex++]     = NAS_EMM_CN_MT_EXT_SER_REQ;

    /* ���service type */
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICE_MO_CSFB_1XCSFB;
    }
    else if (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICR_MO_CSFB_1XCSFB_EMERGENCY;
    }
    else
    {
        pucCnMsg[ulIndex]   = MMC_LMM_SERVICR_MT_CSFB_1XCSFB;
    }

    /*���KSIasme*/
    ucKsi = NAS_EMM_SecuGetKSIValue();
    pucCnMsg[ulIndex++]     |= (ucKsi & 0x0F)<<4;

    /*���M-TSMI*/

    /* ��дLENGTHΪ5 */
    pucCnMsg[ulIndex++]     = 5;

    /*  ��дTYPE OF IDENTITY����EVEN/ODD��ʶ������Э��ǰ4BITΪ'1111' */
    pucCnMsg[ulIndex]       = NAS_EMM_TYPE_OF_IDENTITY_TMSI_PTMSI_MTMSI;/* [false alarm]:���뱣֤�˲���Խ�� */
    pucCnMsg[ulIndex++]     |= NAS_EMM_HIGH_4_BIT;/* [false alarm]:���뱣֤�˲���Խ�� */

    NAS_LMM_MEM_CPY(        &(pucCnMsg[ulIndex]),
                            &pstEmmInfo->stMmUeId.stGuti.stMTmsi,
                            sizeof(NAS_EMM_MTMSI_STRU));
    ulIndex                 += sizeof(NAS_EMM_MTMSI_STRU);

    /* ֻ��MT CSFB�����CSFB RESPONSE */
    if (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        pucCnMsg[ulIndex++] = NAS_EMM_EXTENDED_SER_REQ_CSFB_RSP_IEI | NAS_EMM_SER_GetEmmSerCsfbRsp();/* [false alarm]:���뱣֤�˲���Խ�� */
    }

    /* ���EPS bearer context status */
    /*leili modify for isr begin*/
    NAS_EMM_EncodeEpsBearStatus(        &(pucCnMsg[ulIndex]),
                                        &ulIeLength);
    ulIndex                             += ulIeLength;
    /*leili modify for isr end*/

    *pulIndex               = ulIndex;

    return;

}


VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq(VOS_VOID)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataReqMsg         = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulDataReqMsgLenNoHeader = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex                 = NAS_EMM_NULL;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_ENTRY);

    /*����С��Ϣ���ȣ�������Ϣ�ڴ�,��Ҫ�ǿ��Ƿ�����пռ�*/
    pMrrcDataReqMsg = (VOS_VOID *) NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pMrrcDataReqMsg)
    {
        return;
    }

    /* ���CSFB ABORT��ʶ */
    NAS_EMM_SER_SaveEmmSerCsfbAbortFlag(NAS_EMM_CSFB_ABORT_FLAG_INVALID);

    /*��װEXTENDED SERVICE REQ��Ϣ*/
    NAS_EMM_CompCnExtendedSerReqMoNasMsg(pMrrcDataReqMsg->stNasMsg.aucNasMsg, &ulIndex);

    /*�ڲ���Ϣ���ȼ���*/
    ulDataReqMsgLenNoHeader = NAS_EMM_CountMrrcDataReqLen(ulIndex);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqMsgLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
        return ;
    }

    /*�����Ϣ����*/
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = ulIndex;

    /*�����Ϣͷ*/
    EMM_COMP_MM_MSG_HEADER(pMrrcDataReqMsg, ulDataReqMsgLenNoHeader);

    /* ��дMRRC_DATA_REQ ����ϢID��ʶ */
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    /*��д����ԭ��*/
    switch(NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_MT_ACCESS;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_TERMINATING_CALL;
            break;

        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_MO_DATA;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_MO_CSFB;
            break;

        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:
            pMrrcDataReqMsg->enEstCaue  = LRRC_LNAS_EST_CAUSE_EMERGENCY_CALL;
            pMrrcDataReqMsg->enCallType = LRRC_LNAS_CALL_TYPE_EMERGENCY_CALL;
            break;

        default:
            NAS_EMM_SER_LOG_ERR("Nas_Emm_SER_SendMrrcDataReq_ServiceReq:StartCause ERR");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq_ENUM,LNAS_FUNCTION_LABEL1);
            break;
    }
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_EXTENDED_SERVICE_REQ;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;

    /*�տ���Ϣ�ϱ�SER REQ*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_EXTENDED_SER_REQ,  (NAS_MSG_STRU*)&(pMrrcDataReqMsg->stNasMsg));

    /*�ؼ��¼��ϱ�SER REQ*/
    NAS_LMM_SendOmtKeyEvent(            EMM_OMT_KE_EXTENDED_SER_REQ);

    /* ������Ϣ(Send the msg of) MRRC_DATA_REQ(SER_REQ) */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;
}
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_ESMdata
(
    EMM_ESM_MSG_STRU                   *pstEsmMsg,
    VOS_UINT32                          ulEsmmmOpId
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_SendMrrcDataReq_ESMdata is entered.", pstEsmMsg);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SendMrrcDataReq_ESMdata_ENUM,LNAS_ENTRY,pstEsmMsg);

    /*������Ϣ*/
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if ( NAS_EMM_NULL_PTR == pMrrcDataReqMsg )
    {
        NAS_EMM_SER_LOG_ERR( "Nas_Emm_SER_SendMrrcDataReq_ESMdata: NAS_LMM_ALLOC_MSG err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_ESMdata_ENUM,LNAS_NULL_PTR);
        return;
    }

    ulMsgLenthNoHeader                  = NAS_EMM_CountMrrcDataReqLen(pstEsmMsg->ulEsmMsgSize);

    /* ������Ϣ */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = pstEsmMsg->ulEsmMsgSize;

    NAS_LMM_MEM_CPY(                    (pMrrcDataReqMsg->stNasMsg.aucNasMsg),
                                        (pstEsmMsg->aucEsmMsg),
                                        (pstEsmMsg->ulEsmMsgSize));
    /* ��дDOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(             (pMrrcDataReqMsg),
                                        ulMsgLenthNoHeader);

    /*��д��ϢID*/
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��д EST CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_ESM;

    pMrrcDataReqMsg->ulEsmMmOpId        = ulEsmmmOpId;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NEED;


    /* ��MRRCת��MMESM_DATA_REQ��Ϣ */
    NAS_EMM_SndUplinkNasMsg(             pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);
    return;
}

/*******************************************************************************
  Module   :
  Function : NAS_EMM_SER_SendMrrcDataReq_Tcdata
  Input    : pMsg------------TC��Ϣ
  Output   :
  NOTE     : ��RRCת��TC_DATA_REQ��Ϣ
  Return   : VOS_VOID
  History  :
      1.lihong00150010      2009-10-16  Draft Enact
*******************************************************************************/
VOS_VOID    NAS_EMM_SER_SendMrrcDataReq_Tcdata
(
    EMM_ETC_DATA_REQ_STRU               *pMsg
)
{
    VOS_UINT32                          ulMsgLenthNoHeader;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pMrrcDataReqMsg    = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_SendMrrcDataReq_Tcdata is entered.", pMsg);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_SendMrrcDataReq_Tcdata_ENUM,LNAS_ENTRY,pMsg);


    /*������Ϣ*/
    pMrrcDataReqMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);
    if ( NAS_EMM_NULL_PTR == pMrrcDataReqMsg )
    {
        NAS_EMM_SER_LOG_ERR( "NAS_EMM_SER_SendMrrcDataReq_Tcdata: NAS_LMM_ALLOC_MSG err !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SER_SendMrrcDataReq_Tcdata_ENUM,LNAS_NULL_PTR);
        return;
    }
    ulMsgLenthNoHeader                  = NAS_EMM_CountMrrcDataReqLen(pMsg->stTcMsg.ulTcMsgSize);

    /* ������Ϣ */
    pMrrcDataReqMsg->stNasMsg.ulNasMsgSize = pMsg->stTcMsg.ulTcMsgSize;

    NAS_LMM_MEM_CPY(                        (pMrrcDataReqMsg->stNasMsg.aucNasMsg),
                                        (pMsg->stTcMsg.aucTcMsg),
                                        (pMsg->stTcMsg.ulTcMsgSize));
    /* ��дDOPRA��Ϣͷ */
    EMM_COMP_MM_MSG_HEADER(             (pMrrcDataReqMsg),
                                        ulMsgLenthNoHeader);

    /*��д��ϢID*/
    pMrrcDataReqMsg->ulMsgId            = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*��д EST CAUSE*/
    pMrrcDataReqMsg->enEstCaue          = LRRC_LNAS_EST_CAUSE_MO_DATA;
    pMrrcDataReqMsg->enCallType         = LRRC_LNAS_CALL_TYPE_ORIGINATING_CALL;
    pMrrcDataReqMsg->enEmmMsgType       = NAS_EMM_MSG_TC;

    pMrrcDataReqMsg->enDataCnf          = LRRC_LMM_DATA_CNF_NOT_NEED;

    /* ��MRRCת��TC_DATA_REQ��Ϣ */
    NAS_EMM_SndUplinkNasMsg(pMrrcDataReqMsg);

    NAS_LMM_MEM_FREE(pMrrcDataReqMsg);

    return;
}
VOS_VOID    NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_ENUM_UINT32
                                                                enRabmReestState)
{
    EMM_ERABM_REEST_IND_STRU             *pRabmReestIndMsg    = NAS_EMM_NULL_PTR;

    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_SendRabmReestInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_SendRabmReestInd_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pRabmReestIndMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ERABM_REEST_IND_STRU));

    if(NAS_EMM_NULL_PTR == pRabmReestIndMsg)
    {
        return;
    }

    /* ��дEMM_ERABM_REEST_IND ��DOPRA��Ϣͷ */
    EMM_COMP_ERABM_MSG_HEADER(pRabmReestIndMsg, sizeof(EMM_ERABM_REEST_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);

    /* ��дEMM_ERABM_REEST_IND ����ϢID��ʶ */
    pRabmReestIndMsg->ulMsgId           = ID_EMM_ERABM_REEST_IND;

    /* ����EMM_ERABM_REEST_IND �е��ؽ�״̬ */
    pRabmReestIndMsg->enReEstState      = enRabmReestState;

    /* ������Ϣ(Send the msg of) EMM_ERABM_REEST_IND */
    NAS_LMM_SEND_MSG(                   pRabmReestIndMsg);

    return;

}
VOS_VOID NAS_EMM_SER_AbnormalOver(VOS_VOID)
{
    NAS_EMM_SER_LOG_INFO( "NAS_EMM_SER_AbnormalOver is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_AbnormalOver_ENUM,LNAS_ENTRY);

    /*ֹͣT3417��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

    /*ֹͣT3440��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

    /*ֹͣT3417ext��ʱ��*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

    /*���SR����������SMS��������Ҫ�ظ�SMS����ʧ�ܣ��������SR�ķ���ԭ��*/
    if(NAS_EMM_SER_START_CAUSE_SMS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        /* SER�쳣��ԭ��ֵ�ϱ���ʱ��LMM_SMS_ERR_CAUSE_OTHERS��
           �Ժ����Ҫ������Ӧ��ԭ��ֵ���о���ϸ�ִ����ϱ�׼ȷ��ԭ��ֵ
           �˴���Ϊ�������� */
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    #if (FEATURE_LPP == FEATURE_ON)
    if(NAS_EMM_SER_START_CAUSE_LPP_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_EMM_SendLppEstCnf(LMM_LPP_EST_RESULT_FAIL_SERVICE_FAIL);
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }

    if(NAS_EMM_SER_START_CAUSE_SS_EST_REQ == NAS_EMM_SER_GetSerStartCause())
    {
        NAS_LMM_SndLmmLcsEstCnf( LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL,
                                NAS_EMM_SER_GetSsOrLppOpid());
        NAS_EMM_SER_SaveEmmSERStartCause(NAS_EMM_SER_START_CAUSE_BUTT);
    }
    #endif


    if (VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
    {
        /*Inform RABM that SER fail*/
         NAS_EMM_SER_SendRabmReestInd(EMM_ERABM_REEST_STATE_FAIL);
    }
    else
    {
        /* ֹͣESR����,֪ͨLRRC CSFB������ֹ,LRRC�յ�����Ϣ��,���ȴ������ͷŶ�ʱ������ʱ,ֹͣ��ʱ�� */
        NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_END);
    }

    /*���ESM_DATA����*/
    NAS_EMM_SerClearEsmDataBuf();

    return;
}
VOS_UINT32    NAS_EMM_SER_CHKFSMStateMsgp(
                                    NAS_EMM_MAIN_STATE_ENUM_UINT16  stMS,
                                    NAS_EMM_SUB_STATE_ENUM_UINT16   stSS,
                                    VOS_VOID   *pMsgStru)
{

    NAS_EMM_SER_LOG1_INFO( "NAS_EMM_SER_CHKFSMStateMsgp is entered.", pMsgStru);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_ENTRY,pMsgStru);

    if(NAS_EMM_CHK_STAT_INVALID(stMS, stSS))
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKFSMState: STATE ERR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    if ( NAS_EMM_NULL_PTR == pMsgStru )
    {
        NAS_EMM_SER_LOG_WARN( "NAS_EMM_TAUSER_CHKMsgp: pMsgStru is NULL_PTR !!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SER_CHKFSMStateMsgp_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}




VOS_VOID  NAS_EMM_MmcSendSerResultIndRej
(
    NAS_EMM_CN_CAUSE_ENUM_UINT8       ucCnCause
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO(               "NAS_EMM_MmcSendSerResultIndRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndRej_ENUM,LNAS_ENTRY);

    /* ����MMC�ڲ���Ϣ */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR                 == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR(            "NAS_EMM_SER_SendMmcActionResultReq: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndRej_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstRsltInd, 0, sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* ����RRC��DOPRAͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER(            pstRsltInd,
                                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);
    /*���OPID*/


    /* �����ϢID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* �����Ϣ����----SERVCIE��� */
    pstRsltInd->ulServiceRst            = MMC_LMM_SERVICE_RSLT_CN_REJ;

    /*�����Ϣ����----�ܾ�ԭ��ֵ*/
    pstRsltInd->bitOpCnCause            = NAS_EMM_BIT_SLCT;
    pstRsltInd->ucCnCause               = ucCnCause;

    /* ���SERVICE��ʱʧ�ܴ����������Ҫ���ôﵽ���������Ա�MMC�յ�
       ʱ�ж�disable LTE, CSFB�������ᱨ����ΪCSFB����CService���������1 */
    if(NAS_EMM_GetEmmInfoDamParaCserviceCnt() >= NAS_EMM_GetEmmInfoDamParaCserviceMax())
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_TRUE;
    }
    else
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_FALSE;
    }


    /* ����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}
VOS_VOID  NAS_EMM_MmcSendSerResultIndOtherType
(
    MMC_LMM_SERVICE_RSLT_ENUM_UINT32    ulSerRslt
)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú���*/
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MmcSendSerResultIndOtherType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_ENTRY);

    /* ����MMC�ڲ���Ϣ*/
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR                 == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmcSendSerResultIndOtherType: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstRsltInd, 0, sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* ����RRC��DOPRAͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER(       pstRsltInd,
                                        sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                        EMM_LEN_VOS_MSG_HEADER);
    /*���OPID*/


    /* �����ϢID */
    pstRsltInd->ulMsgId                 = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* �����Ϣ����----SERVCIE��� */
    if ((MMC_LMM_SERVICE_RSLT_FAILURE== ulSerRslt) ||
        (MMC_LMM_SERVICE_RSLT_ACCESS_BARED == ulSerRslt) ||
        (MMC_LMM_SERVICE_RSLT_AUTH_REJ == ulSerRslt))
    {

        NAS_EMM_SER_LOG1_NORM("NAS_EMM_MmcSendSerResultIndOtherType: ulSerRslt = ",
                                ulSerRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_EMM_SER_RST,
                                ulSerRslt);
        pstRsltInd->ulServiceRst            = ulSerRslt;
    }
    else
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_MmcSendSerResultIndOtherType: ulSerRslt is err! ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmcSendSerResultIndOtherType_ENUM,LNAS_ERROR);
    }


    /* ����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}
VOS_VOID  NAS_EMM_MmcSendSerResultIndT3417Exp(VOS_VOID)
{
    LMM_MMC_SERVICE_RESULT_IND_STRU     *pstRsltInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_MmcSendSerResultIndT3417Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MmcSendSerResultIndT3417Exp_ENUM,LNAS_ENTRY);

    /* ����MMC�ڲ���Ϣ */
    pstRsltInd  = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstRsltInd)
    {
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmcSendSerResultIndT3417Exp: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmcSendSerResultIndT3417Exp_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstRsltInd, 0, sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU));

    /* ����RRC��DOPRAͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstRsltInd,
                                  sizeof(LMM_MMC_SERVICE_RESULT_IND_STRU) -
                                  EMM_LEN_VOS_MSG_HEADER);
    /*���OPID*/

    /* �����ϢID */
    pstRsltInd->ulMsgId               = ID_LMM_MMC_SERVICE_RESULT_IND;

    /* SERVCIE��� */
    pstRsltInd->ulServiceRst          = MMC_LMM_SERVICE_RSLT_TIMER_EXP;

    /* �ܾ�ԭ��ֵ���� */
    pstRsltInd->bitOpCnCause          = NAS_EMM_BIT_NO_SLCT;

    /* ���SERVICE��ʱʧ�ܴ����������Ҫ���ôﵽ���������Ա�MMC�յ�ʱ�ж�disable LTE */
    if(NAS_EMM_GetEmmInfoDamParaCserviceCnt() >= NAS_EMM_GetEmmInfoDamParaCserviceMax())
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_TRUE;
    }
    else
    {
        pstRsltInd->ucIsReachMaxTimes = VOS_FALSE;
    }


    /* ����LMM_MMC_SERVICE_RESULT_IND��Ϣ */
    NAS_LMM_SendLmmMmcMsg(             pstRsltInd);

    return;
}
NAS_EMM_SER_START_CAUSE_ENUM_UINT8  NAS_EMM_SER_GetSerStartCause(
                                        VOS_VOID)
{
    return NAS_EMM_SER_GetEmmSERStartCause();
}


VOS_UINT32 NAS_EMM_SER_IsCsfbProcedure( VOS_VOID )
{
    if ((NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
        || (NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause()))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_EMM_SER_IsMoCsfbProcedure( VOS_VOID )
{
    if (NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ == NAS_EMM_SER_GetEmmSERStartCause())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID  NAS_EMM_MmSendCsfbSerPaingInd
(
    NAS_EMM_MT_CSFB_TYPE_ENUM_UINT8     enMtCsfbType,
    const NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification,
    LRRC_LNAS_PAGING_UE_ID_ENUM_UINT32 enPagingUeId
)
{
    LMM_MM_CSFB_SERVICE_PAGING_IND_STRU   *pstMmCsfbSerPaingInd = VOS_NULL_PTR;

    /* ����DOPRA��Ϣ */
    pstMmCsfbSerPaingInd = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmCsfbSerPaingInd)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmSendCsfbSerPaingInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmSendCsfbSerPaingInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmCsfbSerPaingInd, 0, sizeof(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmCsfbSerPaingInd),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_CSFB_SERVICE_PAGING_IND_STRU));

    /* �����ϢID */
    pstMmCsfbSerPaingInd->ulMsgId    = ID_LMM_MM_CSFB_SERVICE_PAGING_IND;

    /* �����Ϣ�� */
    pstMmCsfbSerPaingInd->ulOpId     = NAS_EMM_OPID_MM;

    if (NAS_EMM_MT_CSFB_TYPE_CS_SER_NOTIFICATION == enMtCsfbType)
    {
        /* ���CLI */
        pstMmCsfbSerPaingInd->bitOpCli = pstCsSerNotification->bitOpCli;
        pstMmCsfbSerPaingInd->ucCliLength = pstCsSerNotification->ucCliLength;
        NAS_LMM_MEM_CPY(    pstMmCsfbSerPaingInd->aucCliValue,
                            pstCsSerNotification->aucCliValue,
                            pstCsSerNotification->ucCliLength);

        /* ���SS CODE */
        pstMmCsfbSerPaingInd->bitOpSsCodeValue = pstCsSerNotification->bitOpSsCode;
        pstMmCsfbSerPaingInd->ucSsCodeValue = pstCsSerNotification->ucSsCodeValue;
        if (0 == pstCsSerNotification->ucPagingIdenity)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_IMSI;
        }
        else
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_TMSI;
        }

    }
    else
    {
        if(LRRC_LNAS_S_TMSI_LTE == enPagingUeId)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_S_TMSI;
        }
        else if(LRRC_LNAS_IMSI_LTE == enPagingUeId)
        {
            pstMmCsfbSerPaingInd->enPagingUeId = LMM_MM_PAGING_IND_UE_ID_IMSI;
        }
        else
        {

        }
    }

    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmCsfbSerPaingInd);

    return;
}
VOS_VOID  NAS_EMM_MmSendCsfbSerEndInd
(
    MM_LMM_CSFB_SERVICE_RSLT_ENUM_UINT32     enCsfbSrvRslt,
    NAS_EMM_CN_CAUSE_ENUM_UINT8              ucEMMCnCause
)
{
    LMM_MM_CSFB_SERVICE_END_IND_STRU   *pstMmCsfbSerEndInd = VOS_NULL_PTR;

    /* ����Ѿ��յ�ABORT��Ϣ������֪ͨMM��ֹCSFB���� */
    if (NAS_EMM_CSFB_ABORT_FLAG_VALID == NAS_EMM_SER_GetEmmSerCsfbAbortFlag())
    {
        NAS_EMM_SER_LOG_WARN("NAS_EMM_MmSendCsfbSerEndInd:CSFB is already aborted!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MmSendCsfbSerEndInd_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }

    /* ����DOPRA��Ϣ */
    pstMmCsfbSerEndInd = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_CSFB_SERVICE_END_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmCsfbSerEndInd)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_SER_LOG_ERR("NAS_EMM_MmSendCsfbSerEndInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MmSendCsfbSerEndInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmCsfbSerEndInd, 0, sizeof(LMM_MM_CSFB_SERVICE_END_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmCsfbSerEndInd),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_CSFB_SERVICE_END_IND_STRU));

    /* �����ϢID */
    pstMmCsfbSerEndInd->ulMsgId    = ID_LMM_MM_CSFB_SERVICE_END_IND;

    /* �����Ϣ�� */
    pstMmCsfbSerEndInd->ulOpId     = NAS_EMM_OPID_MM;

    pstMmCsfbSerEndInd->enCsfbSrvRslt = enCsfbSrvRslt;

    pstMmCsfbSerEndInd->ulCnCause = ucEMMCnCause;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmCsfbSerEndInd);

    return;
}
/*lint +e961*/
/*lint +e960*/

VOS_VOID NAS_EMM_RestartSerProcedural(VOS_VOID)
{
    /* ����SERVICE���� */
    switch (NAS_EMM_SER_GetEmmSERStartCause())
    {
        case NAS_EMM_SER_START_CAUSE_MT_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MO_CSFB_REQ:
        case NAS_EMM_SER_START_CAUSE_MO_EMERGENCY_CSFB_REQ:

            /*ֹͣT3417��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ֹͣT3440��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*ֹͣT3417ext��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*������ʱ��3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();
            break;

        default :

            /*ֹͣT3417��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ֹͣT3440��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);

            /*ֹͣT3417ext��ʱ��*/
            NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417_EXT);

            /*������ʱ��3417*/
            NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_SERVICE_T3417);

            /*ת��EMM״̬��MS_SER_INIT+SS_SER_WAIT_CN_CNF*/
            NAS_EMM_TAUSER_FSMTranState(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF, TI_NAS_EMM_STATE_SERVICE_T3417);

            /*��ϲ�����MRRC_DATA_REQ(SERVICE_REQ)*/
            NAS_EMM_SER_SendMrrcDataReq_ServiceReq();
            break;
    }

    return ;
}


/* lihong00150010 emergency tau&service begin */

VOS_VOID  NAS_EMM_EmcPndReqSerAbnormalCommProc
(
    NAS_EMM_SUB_STATE_ENUM_UINT16       ucSs
)
{
    NAS_EMM_TAU_SendEsmStatusInd(EMM_ESM_ATTACH_STATUS_EMC_ATTACHING);

    /* ����DETACH�ͷ���Դ:��̬�ڴ桢����ֵ */
    NAS_LMM_DeregReleaseResource();

    /*��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ*/
    NAS_EMM_MmcSendDetIndLocal( MMC_LMM_L_LOCAL_DETACH_OTHERS);

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_OTHER);
    #endif

    /* ��¼ATTACH����ԭ��ֵ */
    NAS_EMM_GLO_AD_GetAttCau() = EMM_ATTACH_CAUSE_ESM_ATTACH_FOR_INIT_EMC_BERER;

    NAS_EMM_AdStateConvert(     EMM_MS_DEREG,
                                ucSs,
                                TI_NAS_EMM_STATE_NO_TIMER);
}
/* lihong00150010 emergency tau&service end */


VOS_VOID NAS_EMM_ExtSerReqRetranProc(VOS_UINT32 ulOpid)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData;
    VOS_UINT32                          ulIndex = 0;
    NAS_EMM_MRRC_DATA_REQ_STRU          *pMrrcDataMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    pEmmMrrcMgmtData = NAS_EMM_FindMsgInDataReqBuffer(ulOpid);
    if(VOS_NULL_PTR == pEmmMrrcMgmtData)
    {
        return;
    }
    ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)+
                                   pEmmMrrcMgmtData->ulNasMsgLength) -
                                   NAS_EMM_4BYTES_LEN;

    /* ������Ϣ�ڴ�*/
    pMrrcDataMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)(VOS_VOID*)NAS_LMM_MEM_ALLOC(ulRrcMmDataReqMsgLen);
    if(VOS_NULL_PTR == pMrrcDataMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcHoWaitSysInfoBufferMsg: Mem Alloc Fail");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_ExtSerReqRetranProc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /* �ط�EXTENDED SERVICE REQ��Ϣ */
    pMrrcDataMsg->enDataCnf = LRRC_LMM_DATA_CNF_NEED;

    pMrrcDataMsg->enEmmMsgType = NAS_EMM_MSG_EXTENDED_SERVICE_REQ;
    pMrrcDataMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pMrrcDataMsg->ulEsmMmOpId = pEmmMrrcMgmtData->ulEsmMmOpId;

    /*��װEXTENDED SERVICE REQ��Ϣ*/
    NAS_EMM_CompCnExtendedSerReqMoNasMsg(pMrrcDataMsg->stNasMsg.aucNasMsg, &ulIndex);

    pMrrcDataMsg->stNasMsg.ulNasMsgSize = ulIndex;

    NAS_EMM_SndUplinkNasMsg(pMrrcDataMsg);
     /*�ͷ��������ڴ� */
    NAS_LMM_MEM_FREE(pMrrcDataMsg);
}


VOS_VOID  NAS_EMM_SER_CServiceCountProc(VOS_VOID)
{
    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SER_LOG_INFO("NAS_EMM_SER_CServiceCountProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SER_CServiceCountProc_ENUM,LNAS_ENTRY);

    if(NAS_EMM_YES != NAS_EMM_IsDamConfitionSatisfied())
    {
         return;
    }

    if(VOS_FALSE != NAS_EMM_SER_IsCsfbProcedure())
    {
        return;
    }

    NAS_EMM_GetEmmInfoDamParaCserviceCnt()++;

    /* �������֮��Ĳ�����OM */
    NAS_LMM_SndOmDamPara();

    return;
}


VOS_VOID NAS_EMM_ProcHoRetransESRMsg(VOS_VOID)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex = 0;

    /* ��ǰ����CSFB����,�����ش�ESR��ϢNVδ��,�����ǲ��Կ�,
        ���ߵ�ǰ�������û���RB,���˳���ǰ���� */
    if ((VOS_TRUE != NAS_EMM_SER_IsCsfbProcedure())
         ||(PS_SUCC == LPS_OM_IsTestMode())
         ||(PS_FALSE == g_ulNasEmmHoRetransEsrFlag)
         ||(NAS_EMM_CONN_DATA != NAS_EMM_GetConnState()))
    {
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL1, g_ulNasEmmHoRetransEsrFlag);
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ProcHoRetransESRMsg g_ulNasEmmHoRetransEsrFlag = ", g_ulNasEmmHoRetransEsrFlag);
        return;
    }

    /* δ���ͳɹ���Ϣ�����Ϸ��Լ�� */
    if ( g_ulSaveMsgNum > NAS_LMM_RRC_SAVE_MSG_MAX_NUM )
    {
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL2, g_ulSaveMsgNum);
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_ProcHoRetransESRMsg: g_ulSaveMsgNum is error");
        g_ulSaveMsgNum = NAS_LMM_RRC_SAVE_MSG_MAX_NUM;
    }
    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();
    /* ���һ����¼,�Ƿ���δ���ͳɹ���ESR��Ϣ */
    while((ulIndex < g_ulSaveMsgNum))
    {
        if ( NAS_EMM_MSG_EXTENDED_SERVICE_REQ == pEmmMrrcMgmtData->enLastMsgId )
        {
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL3, ulIndex);
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProcHoRetransESRMsg: ESR MSG is exit");
            break;
        }

        pEmmMrrcMgmtData++;

        ulIndex ++;
    }

    /* δ�ҵ������ESR,��T3417ext������,���ش�ESR */
    if ((ulIndex == g_ulSaveMsgNum)
        &&(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_SERVICE_T3417_EXT)))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_ProcHoRetransESRMsg: RetransESR");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ProcHoRetransESRMsg_ENUM, LNAS_FUNCTION_LABEL4);
        NAS_EMM_SER_SendMrrcDataReq_ExtendedServiceReq();

        #if (FEATURE_ON == FEATURE_PTM)
        NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_ESR_RESEND_FOR_HO);
        #endif
    }

    return;
}
VOS_VOID NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_ENUM_UINT16 enCsfbStatus)
{
    LRRC_LMM_CSFB_NOTIFY_STRU           *pstLrrcCsfbNotifyMsg;

    /* INIT��Ҫ����EXT�տڷ��͹����з����ؽ�,ֱ�������ͷ�����ȥGU,�������̲����ܷ����ؽ�,
       ����IDLE̬����Ҫ֪ͨRRC INIT(�տڷ��ͳɹ���LMM��֪ͨLRRC CSFB START) */
    if((LRRC_LNAS_CSFB_STATUS_INIT == enCsfbStatus)
        &&((NAS_EMM_CONN_SIG != NAS_EMM_GetConnState())
            && (NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())))
    {
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndLrrcLmmCsfbNotify_ENUM, LNAS_EMM_NOT_CONN_STATUS);
        NAS_EMM_PUBU_LOG_INFO(" NAS_EMM_SndLrrcLmmCsfbNotify Not Notfiy Csfb Init ");
        return;
    }
    /* ����DOPRA��Ϣ */
    pstLrrcCsfbNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_SUSPEND_RSP_STRU));
    if (NAS_LMM_NULL_PTR == pstLrrcCsfbNotifyMsg)
    {
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstLrrcCsfbNotifyMsg, 0, sizeof(LRRC_LMM_SUSPEND_RSP_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstLrrcCsfbNotifyMsg),
            NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_CSFB_NOTIFY_STRU));

    /* �����ϢID */
    pstLrrcCsfbNotifyMsg->enMsgId       = ID_LRRC_LMM_CSFB_NOTIFY;
    pstLrrcCsfbNotifyMsg->enCsfbStatus  = enCsfbStatus;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstLrrcCsfbNotifyMsg);

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


