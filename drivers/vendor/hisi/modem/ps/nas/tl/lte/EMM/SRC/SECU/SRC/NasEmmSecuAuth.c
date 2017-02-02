


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmSecuInclude.h"
#include    "NasLmmPubMPrint.h"
#include    "NasLmmPubMStack.h"
#include    "NasEmmSerProc.h"
#include    "NasEmmAttDetInterface.h"
#include    "NasEmmTauInterface.h"
#include    "NasEmmAttach.h"
#include    "NasEmmTAUProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMSECUAUTH_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMSECUAUTH_C
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
NAS_LMM_SECU_CONTROL_STRU    g_NasEmmSecuControl;
VOS_UINT8                           *g_pucSecuSrcBuf;
VOS_UINT8                           *g_pucSecuDstBuf;
#if (VOS_WIN32 == VOS_OS_VER)
VOS_UINT8           aucSrcBuf[LRRC_LNAS_MAX_DATA_LENGTH];
VOS_UINT8           aucDstBuf[LRRC_LNAS_MAX_DATA_LENGTH];
#endif



/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID NAS_EMM_SecuDmaMalloc(VOS_VOID)
{
    VOS_UINT_PTR            ulTempAddr  = VOS_NULL_PTR;

#if (VOS_WIN32 != VOS_OS_VER)
    NAS_EMM_GetSecuSrcSpace() = (VOS_UINT8*)LPS_CacheDmaMalloc(LRRC_LNAS_MAX_DATA_LENGTH,&ulTempAddr);
    if(VOS_NULL == NAS_EMM_GetSecuSrcSpace())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuInit: SecuSrc Malloc not success.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDmaMalloc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }
    NAS_EMM_GetSecuDstSpace() = (VOS_UINT8*)LPS_CacheDmaMalloc(LRRC_LNAS_MAX_DATA_LENGTH,&ulTempAddr);
    if(VOS_NULL == NAS_EMM_GetSecuDstSpace())
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuInit: SecuDst Malloc not success.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuDmaMalloc_ENUM,LNAS_FUNCTION_LABEL2);
        return;
    }
#else
    NAS_EMM_GetSecuSrcSpace() = aucSrcBuf;
    NAS_EMM_GetSecuDstSpace() = aucDstBuf;
#endif
    (VOS_VOID)ulTempAddr;
}



/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_DeriveKasme(        const VOS_UINT8 *pucCK,
                                        const VOS_UINT8 *pucIK,
                                        VOS_UINT8 *pucKasme)
{
    VOS_UINT8                       aucAlgParam[NAS_EMM_SECU_MAX_ALG_PARAM_LEN];
    VOS_UINT8                       aucKeyParam[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                      ulIndex      = 0;
    VOS_UINT32                      ulRslt = NAS_EMM_SECU_FAIL;
    NAS_EMM_PLMN_ID_STRU           *pstSerPlmn = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_DeriveKasme is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveKasme_ENUM,LNAS_ENTRY);

    /*��ָ��*/
    if((VOS_NULL_PTR == pucCK) || (VOS_NULL_PTR == pucIK))
    {
         NAS_EMM_SECU_LOG_ERR("NAS_EMM_DeriveKasme:-> Input Pointer Null!");
         TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveKasme_ENUM,LNAS_NULL_PTR);
         return NAS_EMM_SECU_FAIL;
    }

    /*��ȡ current PLMN��Ϊ����Kasme�Ĳ���*/
    pstSerPlmn = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    /* ����KDF�㷨��Ҫ�Ĳ��� */

    /*encode FC*/
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_FC;

    /*encode PLMNID&Len*/
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[0];
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[1];
    aucAlgParam[ulIndex++] = pstSerPlmn->aucPlmnId[2];

    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++] = NAS_EMM_SECU_ALG_PARAM_KASME_PLMNID_LEN;

    /* encode SQN&AK */
    NAS_LMM_MEM_CPY(                    &aucAlgParam[ulIndex],
                                        NAS_EMM_AuthReqAutnAddr(),
                                        NAS_EMM_SECU_SQN_LEN);

    ulIndex                             += NAS_EMM_SECU_SQN_LEN;

    aucAlgParam[ulIndex++]              = NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN;
    aucAlgParam[ulIndex++]              = NAS_EMM_SECU_SQN_LEN;

    NAS_LMM_MEM_CPY((VOS_VOID *)aucKeyParam,pucCK,NAS_EMM_SECU_CKEY_LEN);

    NAS_LMM_MEM_CPY((VOS_VOID *)&aucKeyParam[NAS_EMM_SECU_CKEY_LEN],
                                      pucIK,NAS_EMM_SECU_IKEY_LEN);

    ulRslt = NAS_EMM_KDF_HmacSha256(aucAlgParam,ulIndex,aucKeyParam,pucKasme);

    return ulRslt;

}


VOS_VOID NAS_EMM_SendAuthRsp(VOS_VOID)
{
     VOS_UINT32                         ulPos          = 0;
     NAS_EMM_MRRC_DATA_REQ_STRU        *pIntraMsg      = VOS_NULL_PTR;
     VOS_UINT32                         uldataReqMsgLenNoHeader;

     /* ��ӡ����ú����� INFO_LEVEL */
     NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendAuthRsp entered.");
     TLPS_PRINT2LAYER_INFO(NAS_EMM_SendAuthRsp_ENUM,LNAS_ENTRY);

     /* ������Ϣ�ڴ� */
     pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

     /* �ж�����������ʧ���˳� */
     if (NAS_EMM_NULL_PTR == pIntraMsg)
     {
         return;
     }

     /* ����AUTH RSP��Ϣ */
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = EMM_CN_MSG_PD_EMM;
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_CN_MT_AUTH_RSP;

     /* ���� RES�ĳ��Ⱥ����� */
     pIntraMsg->stNasMsg.aucNasMsg[ulPos++] = NAS_EMM_GetSecuAuthResLen();
     NAS_LMM_MEM_CPY(      (VOS_VOID *)&(pIntraMsg->stNasMsg.aucNasMsg[ulPos]),
                                        NAS_EMM_GetSecuAuthResVAddr(),
                                        NAS_EMM_GetSecuAuthResLen());

     ulPos += NAS_EMM_GetSecuAuthResLen();

     /* �����Ϣ�� */
     pIntraMsg->ulMsgId                 = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
     pIntraMsg->enEstCaue               = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
     pIntraMsg->enCallType              = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
     pIntraMsg->enEmmMsgType            = NAS_EMM_MSG_AUTH_RSP;

     pIntraMsg->enDataCnf               = LRRC_LMM_DATA_CNF_NEED;

     /* ������е�NAS CN��Ϣ�ĳ��� */
     pIntraMsg->stNasMsg.ulNasMsgSize   = ulPos;

     /*���㲻������Ϣͷ����Ϣ����*/
     uldataReqMsgLenNoHeader = NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(
                                        pIntraMsg->stNasMsg.ulNasMsgSize);

     /* �����Ϣͷ */
     NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*�տ���Ϣ�ϱ� AUTH RSP*/
    NAS_LMM_SendOmtAirMsg(              NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_AUTH_RSP,
                                        (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*�ؼ��¼��ϱ� AUTH RSP*/
    NAS_LMM_SendOmtKeyEvent(            EMM_OMT_KE_AUTH_RSP);


    /*��MRRC����AUTH RSP��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(            pIntraMsg);

     NAS_LMM_MEM_FREE(pIntraMsg);

     return;
}


VOS_VOID NAS_EMM_SendAuthFail(NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8 enAuthFailCause)
{
    VOS_UINT32                          uldataReqMsgLenNoHeader     = 0;
    VOS_UINT32                          ulPos                       = 0;
    VOS_UINT8                           aucNasMsg[NAS_EMM_AUTH_LEN_CN_MAX_FAIL_MSG];
    NAS_EMM_MRRC_DATA_REQ_STRU          *pIntraMsg                  = VOS_NULL_PTR;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendAuthFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendAuthFail_ENUM,LNAS_ENTRY);

    /*������Ϣ�ڴ�*/
    pIntraMsg = (VOS_VOID *)NAS_LMM_MEM_ALLOC(NAS_EMM_INTRA_MSG_MAX_SIZE);

    /*�ж�����������ʧ���˳�*/
    if (NAS_EMM_NULL_PTR == pIntraMsg)
    {
        return;
    }

    /* ����Auth Fai��Ϣ */
    aucNasMsg[ulPos++]                  = EMM_CN_MSG_PD_EMM;
    aucNasMsg[ulPos++]                  = NAS_EMM_CN_MT_AUTH_FAIl;
    aucNasMsg[ulPos++]                  = enAuthFailCause;

    if (NAS_EMM_AUTH_SYNC_FAILURE == enAuthFailCause)
    {
        aucNasMsg[ulPos++]              = NAS_EMM_AUTH_FAIl_PARAM_IEI;

        aucNasMsg[ulPos++]              = NAS_EMM_SECU_AUTH_AUTS_LEN;

        /* ��� AUTS*/
        NAS_LMM_MEM_CPY(   (VOS_VOID *)&aucNasMsg[ulPos],
                                        NAS_EMM_GetSecuAuthAutsAddr(),
                                        NAS_EMM_SECU_AUTH_AUTS_LEN);

        ulPos += NAS_EMM_SECU_AUTH_AUTS_LEN;

    }

    /*lint -e669*/
    NAS_LMM_MEM_CPY(pIntraMsg->stNasMsg.aucNasMsg, aucNasMsg,ulPos);
    /*lint +e669*/

    /* �����ϢID */
    pIntraMsg->ulMsgId                  = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;
    pIntraMsg->enEstCaue                = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pIntraMsg->enCallType               = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pIntraMsg->enEmmMsgType             = NAS_EMM_MSG_AUTH_FAIL;

    pIntraMsg->enDataCnf                = LRRC_LMM_DATA_CNF_NEED;

    /* �����Ϣ���� */
    pIntraMsg->stNasMsg.ulNasMsgSize = ulPos;

    /*���㲻������Ϣͷ����Ϣ����*/
    uldataReqMsgLenNoHeader =
            NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(pIntraMsg->stNasMsg.ulNasMsgSize);

    /* �����Ϣͷ */
    NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pIntraMsg, uldataReqMsgLenNoHeader);

    /*�տ���Ϣ�ϱ� AUTH FAIL*/
    NAS_LMM_SendOmtAirMsg(               NAS_EMM_OMT_AIR_MSG_UP,
                                        NAS_EMM_AUTH_FAIL,
                       (NAS_MSG_STRU*)&(pIntraMsg->stNasMsg));

    /*�ؼ��¼��ϱ� AUTH FAIL*/
    NAS_LMM_SendOmtKeyEvent(             EMM_OMT_KE_AUTH_FAIL);

    /*��MRRC����Auth Fai��Ϣ*/
    NAS_EMM_SndUplinkNasMsg(pIntraMsg);

    NAS_LMM_MEM_FREE(pIntraMsg);

    return;

}

/*****************************************************************************
 Function Name  : NAS_EMM_SendUsimAuthenticationReq()
 Description    : ��USIM���ͼ�Ȩ����
 Input          : ulAppType     Ӧ������
                  enAuthType    ��Ȩ����
                  ulOpId
                  uAuth         ��Ȩ����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719  2015-02-09   Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_SendUsimAuthenticationReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType,
    VOS_UINT8                       ulOpId,
    USIMM_AUTH_DATA_UNION          *puAuth
)
{
    USIMM_AUTHENTICATION_REQ_STRU           *pstUsimAuthenticationReq;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SendUsimAuthenticationReq entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUsimAuthenticationReq_ENUM,LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUsimAuthenticationReq = (VOS_VOID*)NAS_LMM_ALLOC_MSG(sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstUsimAuthenticationReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_SendUsimAuthenticationReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendUsimAuthenticationReq_ENUM,LNAS_NULL_PTR);
        return ;
    }


    /*��д��Ϣͷ*/
    /*��Ϣ�ṹ���е�SendPara�����洢OpId*/
    NAS_EMM_SET_USIM_MSG_HEADER(pstUsimAuthenticationReq, USIMM_AUTHENTICATION_REQ, ulAppType, ulOpId);

    pstUsimAuthenticationReq->enAuthType = enAuthType;\
    NAS_LMM_MEM_CPY(&(pstUsimAuthenticationReq->uAuth),
                   puAuth,
                   sizeof(USIMM_AUTH_DATA_UNION));

    /*������Ϣ���ͺ��� */
    NAS_LMM_SEND_MSG(pstUsimAuthenticationReq);
}


/* lihong00150010 ims begin */

VOS_VOID  NAS_EMM_UsimAuthSucc( const USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf  )
{
    VOS_UINT32                          ulDeriveKeyRslt;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstAuthCnf;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UsimAuthSucc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UsimAuthSucc_ENUM,LNAS_ENTRY);

    pstAuthCnf = (USIMM_TELECOM_AUTH_CNF_STRU*)&pstUsimAuthCnf->uCnfData.stTELECnf;

    /*1.�����°�ȫ������:����AuthReq��ϢЯ����Ksi�������µ�Kasme*/
    NAS_EMM_ClearNonCurNativeSecuCntxt();
    NAS_EMM_SetSecuNewNativeKSIasme(NAS_EMM_AuthReqKsi());
    ulDeriveKeyRslt = NAS_EMM_DeriveKasme(&pstAuthCnf->aucCK[1],
                                          &pstAuthCnf->aucIK[1],
                                          NAS_EMM_GetSecuNewNativeKasmeAddr());
    if( NAS_EMM_SECU_FAIL == ulDeriveKeyRslt)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_PreProcUsimAuthCnf: Caculate Kasme ERR.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_UsimAuthSucc_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*��ȫ������״̬Ǩ��*/
    NAS_EMM_SecuStateConvert(NAS_LMM_GetSecuCurFsmCS() ,EMM_NEW_SECU_EXIST);

    /*2. ����T3416,����Rand �� Res*/
    /*����T3416*/
    NAS_LMM_StartPtlTimer(                TI_NAS_EMM_PTL_T3416);

    /*����Rand*/
    NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY(                    NAS_EMM_GetSecuAuthRandAddr(),
                                        NAS_EMM_AuthReqRandAddr(),
                                        NAS_EMM_SECU_AUTH_RAND_LEN);

    /*����Res:pstUsimAuthCnf->u.aucAuthRes��һ���ֽ�ΪRes�ĳ���*/
    NAS_EMM_GetSecuAuthResLen() = pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_L_POS];
    NAS_LMM_MEM_CPY( NAS_EMM_GetSecuAuthResVAddr(),
                   &(pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_V_POS]),
                     NAS_EMM_GetSecuAuthResLen());

    /*3. ���AUTHʧ�ܴ�����Ϊ�㣬��ջ����ʧ�ܴ�������*/
    if(0 != NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_FSM_PopState();
        NAS_EMM_GetAuthFailTimes() = 0;
    }

    /*4. ����AUTH RSP*/
    NAS_EMM_SendAuthRsp();

    return;
}
/* lihong00150010 ims end */

VOS_VOID  NAS_EMM_UsimAuthFail( NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8 enAuthFailCause )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_UsimAuthFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_UsimAuthFail_ENUM,LNAS_ENTRY);

    /*1.��Ȩʧ�ܵĴ���*/
    NAS_EMM_GetAuthFailTimes()++;

    if(NAS_EMM_FIRST_AUTH_FAIL == NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_FSM_PushState();
    }

    /*������Ȩʧ�ܴﵽ���Σ����ٷ���AUTH FAIL,�ͷ����ӣ�֪ͨRRC��ǰС����Bar*/
    if(NAS_EMM_MAX_AUTH_FAIL_TIMES == NAS_EMM_GetAuthFailTimes())
    {
        NAS_EMM_AuthCheckFail();
        return;
    }

    /*2.ת��״̬*/
    if(NAS_EMM_AUTH_SYNC_FAILURE == enAuthFailCause)
    {
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3420);
        NAS_EMM_AuthStateConvert(       EMM_MS_AUTH_INIT,
                                        EMM_SS_AUTH_WAIT_CN_AUTH,
                                        TI_NAS_EMM_T3420);
    }
    else
    {
        NAS_LMM_StartStateTimer(         TI_NAS_EMM_T3418);
        NAS_EMM_AuthStateConvert(       EMM_MS_AUTH_INIT,
                                        EMM_SS_AUTH_WAIT_CN_AUTH,
                                        TI_NAS_EMM_T3418);
    }

    /*3.ֹͣT3416��ɾ�� Rand��Res*/
    NAS_LMM_StopPtlTimer(                TI_NAS_EMM_PTL_T3416);
    NAS_EMM_SecuClearRandRes();

    /*4.����AUTH FAIL��Ϣ*/
    NAS_EMM_SendAuthFail(enAuthFailCause);

    return;
}
VOS_VOID NAS_EMM_AuthCheckFail(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AuthCheckFail entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AuthCheckFail_ENUM,LNAS_ENTRY);

    /* �޸�״̬��������״̬EMM_MS_AUTH_INIT��״̬EMM_SS_AUTH_WAIT_RRC_REL_IND */


    /*��MRRC����NAS_EMM_MRRC_REL_REQ��Ϣ*/
    NAS_EMM_RelReq(                     NAS_LMM_BARRED);
}


VOS_VOID  NAS_EMM_SecuClearRandRes( VOS_VOID )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_SecuClearRandRes entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SecuClearRandRes_ENUM,LNAS_ENTRY);

    /* ɾ��RAND and RES */
    NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_MEM_SET(                    NAS_EMM_GetSecuAuthRandAddr(),
                                        0,
                                        NAS_EMM_SECU_AUTH_RAND_LEN);
    NAS_LMM_MEM_SET(                    NAS_EMM_GetSecuAuthResAddr(),
                                        0,
                                        sizeof(NAS_EMM_SECU_AUTH_RES_STRU));
    return;
}
VOS_VOID NAS_EMM_AbortAuthProcedure(VOS_VOID)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AbortAuthProcedure entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AbortAuthProcedure_ENUM,LNAS_ENTRY);

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    return;
}
VOS_VOID  NAS_EMM_AuthStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 ucMs,
                                   NAS_EMM_SUB_STATE_ENUM_UINT16 ucSs,
                                   NAS_EMM_STATE_TI_ENUM_UINT16 ucStaTId)
{
    NAS_EMM_FSM_STATE_STRU              stDestState;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_AuthStateConvert is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AuthStateConvert_ENUM,LNAS_ENTRY);

    stDestState.enFsmId                 = NAS_LMM_PARALLEL_FSM_EMM;
    stDestState.enMainState             = ucMs;
    stDestState.enSubState              = ucSs;
    stDestState.enStaTId                = ucStaTId;
    NAS_LMM_StaTransProc(stDestState);

    return;
}


VOS_VOID NAS_EMM_SendEsmDeactNonEmcBearInd( VOS_VOID )
{
    EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU *pstDeactNonEmerBearInd = NAS_EMM_NULL_PTR;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_SendEsmDeactNonEmcBearInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendEsmDeactNonEmcBearInd_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pstDeactNonEmerBearInd = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstDeactNonEmerBearInd)
    {
        return;
    }

    /* ��дDOPRA��Ϣͷ */
    NAS_EMM_SET_SECU_ESM_MSG_HEADER(pstDeactNonEmerBearInd, sizeof(EMM_ESM_DEACT_NON_EMC_BEARER_IND_STRU) -
                                        NAS_EMM_VOS_HEADER_LEN);

    /* ��д��ϢID��ʶ */
    pstDeactNonEmerBearInd->ulMsgId    = ID_EMM_ESM_DEACT_NON_EMC_BEARER_IND;

    /* ������Ϣ*/
    NAS_LMM_SEND_MSG(pstDeactNonEmerBearInd);

    return;
}
/* lihong00150010 ims begin */

VOS_UINT32 NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq(        VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsg )
{
    NAS_EMM_AUTH_REQ_STRU              *pstAuthReq = VOS_NULL_PTR;
    /*NAS_EMM_USIM_PARAM_STRU             stAuthVector;*/
    /*VOS_UINT32                          ulHardUsimAuthRslt;*/
    VOS_UINT8                           ucSepBitInAMF;
    VOS_UINT8                           ucKsiAuthReq = 0;
    USIMM_AUTH_DATA_UNION               uAuth;
    VOS_UINT8                           ulOpId;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_ENTRY);

    pstAuthReq                          = (NAS_EMM_AUTH_REQ_STRU *)pMsg;
    NAS_LMM_MEM_SET(                    &uAuth,
                                        0,
                                        sizeof(USIMM_AUTH_DATA_UNION));
    /* lihong00150010 emergency tau&service begin */
    if ((NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        || (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity()))
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: no USIM");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_EMM_NO_USIM);

        return NAS_LMM_MSG_HANDLED;
    }
    /* lihong00150010 emergency tau&service end */
    /* �ж�AUTH REQ��Ϣ��AMFЯ���� Separation BIT,�Ƿ� For E_UTRAN*/
    ucSepBitInAMF = ((pstAuthReq->aucAutn[NAS_EMM_AUTH_AMF_IN_AUTN_POS])&0x80) >> 7;
    if(NAS_EMM_AUTH_FOR_EUTRAN != ucSepBitInAMF)
    {
        NAS_EMM_SECU_LOG1_NORM("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: ERR. AMF Separation BIT = ",
                                        ucSepBitInAMF);
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_NON_EPS_AUTH_UNACCEPTABLE);
        return NAS_LMM_MSG_HANDLED;
    }

    /* �жϵ�ǰ���ֵ�Ƿ���Ч�������Ч���ж�AUTH REQ��ϢЯ���� RAND�뱾�α���� RAND,�����ͬ��ֱ�ӻظ�AUTH RSP*/
    if((NAS_EMM_BIT_SLCT == NAS_EMM_GetSecuAuthOpRand())
       &&(NAS_EMM_SECU_MEM_CMP_EQUAL == NAS_LMM_MEM_CMP(pstAuthReq->aucRand,
                                                    NAS_EMM_GetSecuAuthRandAddr(),
                                                    NAS_EMM_SECU_AUTH_RAND_LEN)))
    {
        NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: New Rand == Old Rand!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_EMM_SendAuthRsp();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTH REQ��ϢЯ����Ksi�����뵱ǰ��ȫ�����ĵ�Ksi��ͬ*/
    ucKsiAuthReq = pstAuthReq->ucKsi & NAS_EMM_LOW_HALF_BYTE_F;
    if(NAS_EMM_GetSecuCurKSIasme() == ucKsiAuthReq)
    {
        NAS_EMM_SECU_LOG_WARN("NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq: Ksi Of AUTH REQ same as Cur Ksi!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq_ENUM,LNAS_FUNCTION_LABEL3);
    }

    /*��¼AUTH REQ��ϢЯ���� KSI,Rand,Autn:AUTN
      USIM�ظ���Ȩ�ɹ�ʱ��Ksi���浽stNewSecuContext,Rand���浽stNasUsimAuthParam*/
    NAS_EMM_AuthReqKsi()                = ucKsiAuthReq;
    NAS_LMM_MEM_CPY(                    NAS_EMM_AuthReqRandAddr(),
                                        pstAuthReq->aucRand,
                                        NAS_EMM_SECU_AUTH_RAND_LEN);
    NAS_LMM_MEM_CPY(                    NAS_EMM_AuthReqAutnAddr(),
                                        pstAuthReq->aucAutn,
                                        NAS_EMM_SECU_AUTH_AUTN_LEN);

    /*zhaochen 00308719 begin for USIM interface modify*/
    /*����ӲUSIM���м�Ȩ*/
    uAuth.st3GAuth.stAutn.ucDataLen = \
                     (VOS_UINT8)pstAuthReq->ulAutnLen;
    //uAuth.st3GAuth.stAutn.aucData = NAS_EMM_AuthReqAutnAddr();
    NAS_LMM_MEM_CPY(                    uAuth.st3GAuth.stAutn.aucData,
                                        NAS_EMM_AuthReqAutnAddr(),
                                        NAS_EMM_SECU_AUTH_AUTN_LEN);

    uAuth.st3GAuth.stRand.ucDataLen = \
                     NAS_EMM_SECU_AUTH_RAND_LEN;
    //uAuth.st3GAuth.stRand.aucData = NAS_EMM_AuthReqRandAddr();
    NAS_LMM_MEM_CPY(                    uAuth.st3GAuth.stRand.aucData,
                                        NAS_EMM_AuthReqRandAddr(),
                                        NAS_EMM_SECU_AUTH_AUTN_LEN);

    NAS_EMM_GetSecuAuthOpId()++;

    ulOpId = NAS_EMM_GetSecuAuthOpId();


    /* ����USIM�ļ�Ȩ��Ϣ��Ȼ��ȴ�USIM�ļ�Ȩ�������������ʱ����״̬�ȴ� */
    NAS_EMM_SendUsimAuthenticationReq(USIMM_GUTL_APP, USIMM_3G_AUTH, ulOpId, &uAuth);
    /*zhaochen 00308719 end for USIM interface modify*/


    return NAS_LMM_MSG_HANDLED;

}
/* lihong00150010 ims end */

VOS_UINT32 NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq(        VOS_UINT32  ulMsgId,
                                                            VOS_VOID   *pMsg )
{
    VOS_UINT32                          ulAuthRslt;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq_ENUM,LNAS_ENTRY);

    /*ֹͣ3418,T3420 */
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(TI_NAS_EMM_T3420);

    ulAuthRslt = NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq(ulMsgId, pMsg);

    return ulAuthRslt;
}
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{

    VOS_UINT32                          ulCurEmmStat;

    (VOS_VOID)(pMsgStru);
    (VOS_VOID)ulMsgId;

    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej_ENUM,LNAS_ENTRY);

    /* ��Ȩ�ܾ��Ż����� */
    if (NAS_EMM_YES == NAS_EMM_IsNeedIgnoreHplmnAuthRej())
    {
        return  NAS_LMM_MSG_HANDLED;
    }

    #if (FEATURE_PTM == FEATURE_ON)
    NAS_EMM_AuthCnFailErrRecord(EMM_OM_ERRLOG_AUTH_FAIL_CN_REJ);
    #endif

    /* ͣT3420��T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                NAS_EMM_MsRegSsNmlSrvProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                NAS_EMM_ProcDetachAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_EMM_MsTauInitSsWaitCnTauCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgAuthRej(NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL);
                break;
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej_ENUM,LNAS_ENTRY);

    /* ͣT3420��T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    /*״̬��ջ֮���൱����reg_init+wait_cn_attach_cnf״̬�´���attach rej��Ϣ��
      �����ת�崦���������Ӧ�ķ�֧���д�����
    */
    (VOS_VOID)NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachReject(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);


    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej_ENUM,LNAS_ENTRY);

    /* ͣT3420��T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    /*״̬��ջ֮���൱����tau_init+wait_cn_tau_cnf״̬�´���tau rej��Ϣ��
      �����ת�崦���������Ӧ�ķ�֧���д�����
    */
    (VOS_VOID)NAS_EMM_MsTauInitSsWaitCNCnfMsgTAURej(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);


    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej_ENUM,LNAS_ENTRY);
    /* ͣT3420��T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    /*״̬��ջ֮���൱����ser_init+wait_cn_ser_cnf״̬�´���ser rej��Ϣ��
      �����ת�崦���������Ӧ�ķ�֧���д�����
    */
    (VOS_VOID)NAS_EMM_MsSerInitSsWaitCNSerCnfMsgServiceReject(ulMsgId, pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}


VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* �����ǰû�����ڽ�������������û�н������أ���֪ͨRRC�ͷ���·����BAR���� */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        /*ȷ�����಻��ͨ�����μ�Ȩ*/
        NAS_EMM_AuthCheckFail();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    /* ֪ͨESMȥ�������зǽ������� */
    if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        NAS_EMM_SendEsmDeactNonEmcBearInd();
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru )
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* �����ǰû�����ڽ�������������û�н������أ���֪ͨRRC�ͷ���·����BAR���� */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        /*ȷ�����಻��ͨ�����μ�Ȩ*/
        NAS_EMM_AuthCheckFail();
        return NAS_LMM_MSG_HANDLED;
    }

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    /* ֪ͨESMȥ�������зǽ������� */
    if ((EMM_MS_REG == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_TAU_INIT == NAS_EMM_CUR_MAIN_STAT)
        || (EMM_MS_SER_INIT == NAS_EMM_CUR_MAIN_STAT))
    {
        NAS_EMM_SendEsmDeactNonEmcBearInd();
    }

    return NAS_LMM_MSG_HANDLED;
}
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru)
{
    LRRC_LMM_REL_IND_STRU                *pRrcRelInd =       VOS_NULL_PTR;
    VOS_UINT32                           ulCause;
    VOS_UINT32                          ulCurEmmStat;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    pRrcRelInd                          = (LRRC_LMM_REL_IND_STRU*)(pMsgStru);
    ulCause                             = pRrcRelInd->enRelCause;

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                            NAS_EMM_CUR_SUB_STAT);
    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
                NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
                NAS_EMM_MsRegSsNmlSrvProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
                NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
                NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd(ulCause);
                break;
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
                NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd(ulCause);
                break;
        default:
                break;
    }

    return NAS_LMM_MSG_HANDLED;

}
/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify
 Description     : ��AuthInit�ȴ�CN��Ϣʱ����EIA0 ACT NOTIFY��Ϣ
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify_ENUM,LNAS_ENTRY);

    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsgStru);

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd
 Description     : ��AuthInit�ȴ�CN��Ϣʱ����DRB������Ϣ
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                     *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }
    (VOS_VOID)ulMsgId;

    /* ջ����״̬�����ΪSERVICE_INIT̬������ */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT,EMM_SS_SER_WAIT_CN_SER_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:not service_init+wait_cn_ser_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* �����ǰû�����ڽ�������������û�н������أ����� */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd:no emergency bearer and not esting emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    NAS_EMM_SER_RcvRabmDrbSetupInd(pMsgStru);

    return NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept
 Description     : ��AuthInit�ȴ�CN��ϢʱATTACH ACCPET��Ϣ
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ջ����״̬�����ΪREG_INIT̬������ */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT,EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:not reg_init+wait_cn_attach_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* �����ǰ���ǽ���ע������У����� */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGING))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept:not emergency attach");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    return NAS_EMM_MsRegInitSsWtCnAttCnfMsgCnAttachAcp(ulMsgId, pMsgStru);
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept
 Description     : ��AuthInit�ȴ�CN��ϢʱTAU ACCPET��Ϣ
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ջ����״̬�����ΪTAU_INIT̬������ */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT,EMM_SS_TAU_WAIT_CN_TAU_CNF))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:not tau_init+wait_cn_tau_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* �����ǰû�����ڽ�������������û�н������أ����� */
    if ((VOS_TRUE != NAS_LMM_GetEmmInfoIsEmerPndEsting())
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept:no emergency bearer and not esting emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    return NAS_EMM_MsTauInitSsWaitCNCnfMsgTAUAcp(ulMsgId, pMsgStru);
}

/*****************************************************************************
 Function Name   : NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp
 Description     : ��AuthInit�ȴ�CN��ϢʱDETACH ACCPET��Ϣ
 Input           : ulMsgId,pMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010        2012-10-19      Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
)
{
    VOS_UINT32                          ulStaAtStackTop = NAS_EMM_NULL;
    VOS_UINT32                          ulCurEmmStat    = NAS_EMM_NULL;

    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_ENTRY);

    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_NULL_PTR);
        return  NAS_LMM_ERR_CODE_PTR_NULL;
    }

    /* ջ����״̬�����ΪTAU_INIT̬������ */
    ulStaAtStackTop = NAS_LMM_FSM_GetStaAtStackTop(NAS_LMM_PARALLEL_FSM_EMM);
    if ((ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT,EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
        && (ulStaAtStackTop != NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG,EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF)))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:not dereg_init+wait_cn_detach_cnf and not reg+wait_imsi_detach_cnf state!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_LMM_MSG_DISCARD;
    }

    /* �����ǰû�н������أ����� */
    if ((NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_EMC_REGED)
        && (NAS_LMM_GetEmmInfoRegStatus() != NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR))
    {
        NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp:no emergency bearer");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_LMM_MSG_DISCARD;
    }

    /* ͣT3420,T3418*/
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3418);
    NAS_LMM_StopStateTimer(              TI_NAS_EMM_T3420);

    /* AUTHʧ�ܴ�������*/
    NAS_EMM_GetAuthFailTimes() = 0;

    /* ״̬��ջ*/
    NAS_EMM_FSM_PopState();

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_DEREG_INIT,
                                                    EMM_SS_DETACH_WAIT_CN_DETACH_CNF))
    {
        return NAS_EMM_MsDrgInitSsWtCnDetCnfMsgCnDetachAcp(ulMsgId, pMsgStru);
    }
    else
    {
        return NAS_EMM_MsRegImsiDetachWtCnDetCnfMsgCnDetachAcp(ulMsgId, pMsgStru);
    }
}
/* lihong00150010 ims begin */

VOS_UINT32  NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf(  VOS_UINT32  ulMsgId,
                                                         VOS_VOID   *pMsg )
{
    USIMM_AUTHENTICATION_CNF_STRU*pstUsimAuthCnf = VOS_NULL_PTR;

    (VOS_VOID)ulMsgId;
    NAS_EMM_SECU_LOG_INFO("NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf_ENUM,LNAS_ENTRY);
    NAS_LMM_PrintFsmState(NAS_LMM_PARALLEL_FSM_EMM);

    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;
    /* ���OpId��ͬ��˵���������ȨCNF֮ǰ���յ�������ļ�Ȩ���� ,�����ȴ�USIM�ظ�*/
    if((pstUsimAuthCnf->stCmdResult).ulSendPara!= NAS_EMM_GetSecuAuthOpId())
    {
        return NAS_LMM_MSG_HANDLED;
    }

    /* ��Ȩ�ɹ������OpId */
    NAS_EMM_GetSecuAuthOpId() = 0;
    /*���� USIM_AUTH_CNF�еĽ�����в�ͬ����*/
    switch(pstUsimAuthCnf->enResult)
    {
             /*USIM��Ȩ�ɹ�*/
        case USIMM_AUTH_UMTS_SUCCESS:
             NAS_EMM_UsimAuthSucc(pstUsimAuthCnf);
             break;

             /*USIM��Ȩʧ��:MAC FAIL*/
        case USIMM_AUTH_MAC_FAILURE:
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_MAC_FAILURE);
             NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_MAC_FAILURE);
             break;

             /*USIM��Ȩʧ��:SYNCFAIL*/
        case USIMM_AUTH_SYNC_FAILURE:
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_SYNC_FAILURE);

             /*��ȡUSIM_AUTH_CNFЯ����AUTS:pstUsimAuthCnf->u.aucAuts��һ���ֽ�ΪAuts�ĳ���*/
             NAS_LMM_MEM_CPY( NAS_EMM_GetSecuAuthAutsAddr(),
                            &(pstUsimAuthCnf->uCnfData.stTELECnf.aucAuts[NAS_EMM_USIM_CNF_AUTS_V_POS]),
                              pstUsimAuthCnf->uCnfData.stTELECnf.aucAuts[NAS_EMM_USIM_CNF_AUTS_L_POS]);

             /*����ʧ�ܴ�����*/
             NAS_EMM_UsimAuthFail(NAS_EMM_AUTH_SYNC_FAILURE);
             break;

        default:
             NAS_EMM_SECU_LOG_ERR("NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf: USIM CNF RSLT ERR.");
             TLPS_PRINT2LAYER_ERROR(NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf_ENUM,LNAS_FUNCTION_LABEL1);
             NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_OTHER);
             break;
    }

    return NAS_LMM_MSG_HANDLED;
}
/* lihong00150010 ims end */

VOS_VOID NAS_LMM_PreProcAnyStateUsimAuthCnf(const USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf)
{
    VOS_UINT32                          ulDeriveKeyRslt;
    USIMM_TELECOM_AUTH_CNF_STRU        *pstAuthCnf;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_PreProcAnyStateUsimAuthCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcAnyStateUsimAuthCnf_ENUM,LNAS_ENTRY);

    pstAuthCnf = (USIMM_TELECOM_AUTH_CNF_STRU*)&pstUsimAuthCnf->uCnfData.stTELECnf;

    if( USIMM_AUTH_UMTS_SUCCESS == pstUsimAuthCnf->enResult)
    {
        /*1.�����°�ȫ������:����AuthReq��ϢЯ����Ksi�������µ�Kasme*/
        NAS_EMM_ClearNonCurNativeSecuCntxt();
        NAS_EMM_SetSecuNewNativeKSIasme(NAS_EMM_AuthReqKsi());
        ulDeriveKeyRslt = NAS_EMM_DeriveKasme(&pstAuthCnf->aucCK[1],
                                                  &pstAuthCnf->aucIK[1],
                                                  NAS_EMM_GetSecuNewNativeKasmeAddr());

        if( NAS_EMM_SECU_FAIL == ulDeriveKeyRslt)
        {
            NAS_EMM_SECU_LOG_ERR("NAS_LMM_PreProcAnyStateUsimAuthCnf: Caculate Kasme ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_PreProcAnyStateUsimAuthCnf_ENUM,LNAS_ERROR);
        }

        /*��ȫ������״̬Ǩ��*/
        NAS_EMM_SecuStateConvert(NAS_LMM_GetSecuCurFsmCS() ,EMM_NEW_SECU_EXIST);

        /*2. ����T3416,����Rand �� Res*/
        /*����T3416*/
        NAS_LMM_StartPtlTimer(TI_NAS_EMM_PTL_T3416);

        /* ��Ȩ�ɹ������OpId */
        NAS_EMM_GetSecuAuthOpId() = 0;

        /*����Rand*/
        NAS_EMM_GetSecuAuthOpRand() = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(NAS_EMM_GetSecuAuthRandAddr(),
                            NAS_EMM_AuthReqRandAddr(),
                            NAS_EMM_SECU_AUTH_RAND_LEN);

        /*����Res:pstUsimAuthCnf->u.aucAuthRes��һ���ֽ�ΪRes�ĳ���*/
        NAS_EMM_GetSecuAuthResLen() = pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_L_POS];
        NAS_LMM_MEM_CPY( NAS_EMM_GetSecuAuthResVAddr(),
                           &(pstAuthCnf->aucAuthRes[NAS_EMM_USIM_CNF_RES_V_POS]),
                             NAS_EMM_GetSecuAuthResLen());

    }

    return;
}
VOS_UINT32 NAS_LMM_PreProcUsimAuthCnf(MsgBlock  *pMsg)
{
    VOS_UINT32                          ulCurEmmStat;
    VOS_UINT32                          ulRslt;
    USIMM_AUTHENTICATION_CNF_STRU       *pstUsimAuthCnf;
    pstUsimAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU *)pMsg;


    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ProcUsimAuthCnf is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_PreProcUsimAuthCnf_ENUM,LNAS_ENTRY);

    /* ���OpId��ͬ��˵���������ȨCNF֮ǰ���յ�������ļ�Ȩ���� ,�����ȴ�USIM�ظ�*/
    /* �µ����ݽṹ�У�SendPara�����洢OpId */
    if(pstUsimAuthCnf->stCmdResult.ulSendPara != NAS_EMM_GetSecuAuthOpId())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    /* ����״̬�£�LMM���USIM��CNF���д�����ô����Щ״̬��LMM��Ԥ����*/
    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    switch(ulCurEmmStat)
    {
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG_INIT, EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_NORMAL_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_LIMITED_SERVICE):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_ATTEMPTING_TO_UPDATE_MM):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_REG, EMM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_TAU_INIT, EMM_SS_TAU_WAIT_CN_TAU_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_DEREG_INIT, EMM_SS_DETACH_WAIT_CN_DETACH_CNF):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_AUTH_INIT, EMM_SS_AUTH_WAIT_CN_AUTH):
        case    NAS_LMM_PUB_COMP_EMMSTATE(EMM_MS_SER_INIT, EMM_SS_SER_WAIT_CN_SER_CNF):
                ulRslt = NAS_LMM_MSG_DISCARD;
                break;
        default:
                NAS_LMM_PreProcAnyStateUsimAuthCnf(pstUsimAuthCnf);
                ulRslt = NAS_LMM_MSG_HANDLED;
                break;
    }

    return  ulRslt;
}

VOS_VOID NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16  enSimAuthFailValue)
{
    LMM_MMC_SIM_AUTH_FAIL_IND_STRU    *pstSimAuthFailInd = NAS_EMM_NULL_PTR;
    VOS_UINT32                        ulCompStaOfStackBase;              /*ջ��״̬*/
    NAS_LMM_MAIN_STATE_ENUM_UINT16       enMainState;                    /*��״̬*/

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_SECU_LOG_INFO( "NAS_EMM_SndMmcSimAuthFailInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_ENTRY);

    /* ����DOPRA��Ϣ */
    pstSimAuthFailInd = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_SIM_AUTH_FAIL_IND_STRU));

    if(NAS_EMM_NULL_PTR == pstSimAuthFailInd)
    {
        NAS_EMM_SECU_LOG_ERR( "NAS_EMM_SndMmcSimAuthFailInd: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ��дDOPRA��Ϣͷ */
    /*EMM_PUBU_COMP_MMC_MSG_HEADER(pstSimAuthFailInd, sizeof(LMM_MMC_SIM_AUTH_FAIL_IND_STRU) - EMM_LEN_VOS_MSG_HEADER);*/
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstSimAuthFailInd, NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_SIM_AUTH_FAIL_IND_STRU));

    /* ��д��ϢID��ʶ */
    pstSimAuthFailInd->ulMsgId    = ID_LMM_MMC_SIM_AUTH_FAIL_IND;

    pstSimAuthFailInd->enSimAuthFailValue          = enSimAuthFailValue;
    pstSimAuthFailInd->enSrvDomain                 = LMM_MMC_SRV_DOMAIN_PS;

    enMainState = NAS_LMM_GetEmmCurFsmMS();

    /*����Ȩʧ��ʱ����service domainĬ��ΪPS�����������ΪCS_PS*/
    if ((EMM_MS_REG_INIT == enMainState && MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType())
         || (EMM_MS_TAU_INIT == enMainState && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
         || (EMM_MS_TAU_INIT == enMainState && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        pstSimAuthFailInd->enSrvDomain             = LMM_MMC_SRV_DOMAIN_CS_PS;

        NAS_EMM_SECU_LOG_INFO( "attach or tau state send mmc msg");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstSimAuthFailInd);
        /*NAS_LMM_SEND_MSG(pstSimAuthFailInd);*/

        return;
    }

    /*����Ǽ�Ȩѹջ�������ջ��״̬Ϊattach��tauʱ*/
    ulCompStaOfStackBase = NAS_LMM_FSM_GetStaAtStackBase(NAS_LMM_PARALLEL_FSM_EMM);
    if ((EMM_MS_REG_INIT == ulCompStaOfStackBase && MMC_LMM_ATT_REQ_TYPE_CS_PS == NAS_EMM_GLO_GetAttReqType())
         || (EMM_MS_TAU_INIT == ulCompStaOfStackBase && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING == NAS_EMM_TAU_GetTAUtype())
         || (EMM_MS_TAU_INIT == ulCompStaOfStackBase && NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_WITH_IMSI == NAS_EMM_TAU_GetTAUtype()))
    {
        pstSimAuthFailInd->enSrvDomain             = LMM_MMC_SRV_DOMAIN_CS_PS;

        NAS_EMM_SECU_LOG_INFO( "stack bottom attach or tau state send mmc msg");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SndMmcSimAuthFailInd_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstSimAuthFailInd);
        /*NAS_LMM_SEND_MSG(pstSimAuthFailInd);*/

        return;
    }

}
VOS_VOID    NAS_EMM_SECU_ClearResource(VOS_VOID)
{
    NAS_EMM_SECU_LOG_NORM("NAS_EMM_SECU_ClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SECU_ClearResource_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET( NAS_EMM_GetSecuUsimAuthParamAddr(),
                    0,
                    sizeof(NAS_LMM_USIM_AUTH_PARAM_STRU));

    NAS_EMM_GetSmcType() = NAS_EMM_SMC_UPDATE_BUTT;

    NAS_LMM_MEM_SET( NAS_EMM_GetSecuSrcSpace(),
                    0,
                    LRRC_LNAS_MAX_DATA_LENGTH);

    NAS_LMM_MEM_SET( NAS_EMM_GetSecuDstSpace(),
                    0,
                    LRRC_LNAS_MAX_DATA_LENGTH);

    NAS_LMM_MEM_SET( NAS_EMM_GetSecuBufSpace(),
                    0,
                    LRRC_LNAS_MAX_DATA_LENGTH);
    NAS_LMM_MEM_SET( NAS_EMM_GetAuthReqParamAddr(),
                    0,
                    sizeof(NAS_LMM_AUTH_REQ_PARAM_STRU));

    NAS_EMM_AuthReqKsi() = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;

    NAS_EMM_GetAuthFailTimes() = 0;

    return;
}
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

