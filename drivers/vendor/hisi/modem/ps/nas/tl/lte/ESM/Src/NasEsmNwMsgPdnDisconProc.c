


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGPDNDISCOCPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGPDNDISCOCPROC_C
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



/*****************************************************************************
  3 Function
*****************************************************************************/


/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_ProcValidNwMsgDeactEpsbReq
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgDeactEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgDeactEpsbReq_ENUM, LNAS_ENTRY);

    /*ȡ��������Ϣ*/
    ulEpsbId = (VOS_UINT32)(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /*����������ϢЯ����PTI*/
    pstStateAddr->bitOpNwMsgRecord = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ucPti = pRcvMsg->stEsmNwMsgIE.ucPti;

    /*֪ͨAPP�ͷ�ȱʡ���ؼ����������*/
    NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*������ظ�Deactivate EPS bearer context accept*/
    NAS_ESM_EncodeDeactEpsbCntxtAccMsg(stEncodeInfo, \
                               NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                              &ulSndNwMsgLen);

    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                       ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                       ESM_DEACT_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}
VOS_VOID  NAS_ESM_ProcValidNwMsgPdnDisconRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgPdnDisconRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgPdnDisconRej_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3492);

    /*���REJЯ��ԭ��ֵ��Ϊ:#49 NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED���򱾵�ȥ����ȱʡ����*/
    if(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED != pRcvMsg->stEsmNwMsgIE.enEsmCau)
    {
        /*�ͷű��س�����Դ,����APP�ظ������ͷųɹ�*/
        NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

        /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
        NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
    }
    else
    {
        /*��APP����ID_APP_ESM_BEARER_REL_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex, \
                 NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }

    /*��ֹPDNȥ��������,�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}
VOS_VOID  NAS_ESM_InformAppBearerRel(VOS_UINT32 ulEpsbId)
{
    VOS_UINT32                          ulStateTblIndex  = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpBitCid      = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    APP_ESM_MSG_TYPE_ENUM_UINT32        enAppMsgType;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_InformAppBearerRel is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_InformAppBearerRel_ENUM, LNAS_ENTRY);

    /*��ȡ������Ϣ��ַ*/
    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    ulTmpBitCid = pstEpsbInfo->ulBitCId;

    /* ���˳���û�ж�Ӧ��CID�����˳� */
    if((NAS_ESM_OP_FALSE == pstEpsbInfo->bitOpCId) || (NAS_ESM_NULL == ulTmpBitCid))
    {
        return;
    }

    for( ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++ )
    {
        if(NAS_ESM_OP_FALSE == ((ulTmpBitCid >> ulCnt) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        if(NAS_ESM_SUCCESS != NAS_ESM_QueryStateTblIndexByCid(ulCnt, &ulStateTblIndex))
        {
            /*��APP����ID_APP_ESM_PDP_RELEASE_IND(�ɹ�)��Ϣ*/
            NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
            continue;
        }

        pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
        if( NAS_ESM_OP_TRUE != pstStateAddr->bitOpAppMsgRecord )
        {
            /*��APP����ID_APP_ESM_PDP_RELEASE_IND(�ɹ�)��Ϣ*/
            NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
            continue;
        }

        /*ȡ���˳����м�¼��APP��Ϣ����*/
        enAppMsgType = pstStateAddr->stAppMsgRecord.enAppMsgType;

        /*��������¼����Ϣ���ͻظ���Ϣ*/
        switch( enAppMsgType )
        {
            case ID_APP_ESM_PDP_RELEASE_REQ:
                /*��APP����ID_APP_ESM_PDP_RELEASE_CNF(�ɹ�)��Ϣ*/
                NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(ulStateTblIndex);
                break;

            case ID_APP_ESM_PDP_MODIFY_REQ:

                NAS_ESM_SndEsmAppSdfModCnfFailMsg(  ulStateTblIndex, \
                                                    APP_ERR_UNSPECIFIED_ERROR);
                NAS_ESM_SndEsmAppSdfRelIndMsg(ulCnt, ulEpsbId);
                break;

            default:
                /*��ӡ�쳣��Ϣ*/
                NAS_ESM_WARN_LOG("NAS_ESM_InformAppBearerRel:App Msg Record illogic!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_InformAppBearerRel_ENUM, 1);
                break;
        }
    }

}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmNwMsgProc.c */
