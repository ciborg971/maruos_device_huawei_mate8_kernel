


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMRABMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMRABMMSGPROC_C
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

VOS_VOID NAS_ESM_RabmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pRabmMsg = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RabmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RabmMsgDistr_ENUM, LNAS_ENTRY);

    pRabmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pRabmMsg->ulMsgName)
    {
        /*����յ�����ID_ESM_ERABM_REL_REQ��Ϣ*/
        case ID_ESM_ERABM_REL_REQ:

            /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
            if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
            {
                NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:Msg is discard cause ESM state is detached!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 1);
                return ;
            }


            /*����Դ*/
            NAS_ESM_ClearEsmResource();
            break;

        /*RBδ����������ȥ������Ӧ����������*/
        case ID_ESM_ERABM_BEARER_STATUS_REQ:

            /*����ȥ�������������*/
            NAS_ESM_RcvEsmRabmBearerStatusReq((ESM_ERABM_BEARER_STATUS_REQ_STRU *) pRcvMsg);
            break;

        default:
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:RABM->SM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 2);
            break;
    }
}


/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_GetPdnAddr
(
    NAS_ESM_CONTEXT_IP_ADDR_STRU *pstPdnAddr,
    VOS_UINT32 ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    if(VOS_NULL_PTR == pstPdnAddr)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:Input parameter is null!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* ����ר�г��أ����ȡ����ȱʡ���ص�EpsbCntxtTbl���ַ */
    if(NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(ulEpsbId))
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);
    }

    /* ��ȡPDN��Ϣ */
    if(NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPdnAddr)
    {
        NAS_ESM_MEM_CPY(    pstPdnAddr,
                            &pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:No Pdn Address!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, ESM_PDN_TYPE_ERROR);
    }
}
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmActIndMsg( VOS_UINT32  ulEpsbId )
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_ACT_IND_STRU              *pEsmRabmActIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pEsmRabmActIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_ACT_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmActIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmActIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmActIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pEsmRabmActIndMsg), 0, NAS_ESM_GET_MSG_LENGTH(pEsmRabmActIndMsg));

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    NAS_ESM_AssignErabmSessionId(&(pEsmRabmActIndMsg->ucSessionId));

    /* �������ص�����PF��Ϣ */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*����SDF��PF��Ϣ*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmActIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*��д��Ϣ����*/
    pEsmRabmActIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmActIndMsg->ulTftPfNum = ulTftPfNum;

    /* ��дPDN��Ϣ */
    NAS_ESM_GetPdnAddr(&pEsmRabmActIndMsg->stPdnAddr, ulEpsbId);

    pEsmRabmActIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmActIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmActIndMsg->ucQCI = pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;
    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmActIndMsg,ID_ESM_ERABM_ACT_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmActIndMsg);

}
/*lint -specific(+e433)*/



/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmMdfIndMsg( VOS_UINT32       ulEpsbId )
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_MDF_IND_STRU              *pEsmRabmMdfIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;


    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pEsmRabmMdfIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_MDF_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmMdfIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmMdfIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmMdfIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pEsmRabmMdfIndMsg), 0, NAS_ESM_GET_MSG_LENGTH(pEsmRabmMdfIndMsg));

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    /* �������ص�����PF��Ϣ */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*����SDF��PF��Ϣ*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmMdfIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*��д��Ϣ����*/
    pEsmRabmMdfIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmMdfIndMsg->ulTftPfNum = ulTftPfNum;

    /* ��дPDN��Ϣ */
    NAS_ESM_GetPdnAddr(&pEsmRabmMdfIndMsg->stPdnAddr, ulEpsbId);

    pEsmRabmMdfIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmMdfIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmMdfIndMsg->ucQCI= pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmMdfIndMsg,ID_ESM_ERABM_MDF_IND);


    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmMdfIndMsg);

}
/*lint -specific(+e433)*/



VOS_VOID NAS_ESM_SndEsmRabmDeactIndMsg(VOS_UINT32          ulEpsbIdNum,
                                                  const VOS_UINT32         *pulEpsbId)
{
    ESM_ERABM_DEACT_IND_STRU       *pEsmRabmDeactIndMsg   = VOS_NULL_PTR;

    /*�����ڲ���*/
    if( (ulEpsbIdNum == 0) || (ulEpsbIdNum > NAS_ESM_MAX_EPSB_NUM) \
            || (VOS_NULL_PTR == pulEpsbId) )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:WARNING:Input Para error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmRabmDeactIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_DEACT_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmDeactIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pEsmRabmDeactIndMsg), 0, NAS_ESM_GET_MSG_LENGTH(pEsmRabmDeactIndMsg));

    /*��ulEpsbIdNum��pulEpsbId����pEsmRabmDeactIndMsg*/
    pEsmRabmDeactIndMsg->ulEpsIdNum = ulEpsbIdNum;
    NAS_ESM_MEM_CPY((VOS_UINT8*)pEsmRabmDeactIndMsg->aulEpsId, (VOS_UINT8*)pulEpsbId,\
              (pEsmRabmDeactIndMsg->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmDeactIndMsg,ID_ESM_ERABM_DEACT_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmDeactIndMsg);
}


VOS_VOID NAS_ESM_SndEsmRabmRelIndMsg( VOS_VOID )
{
    ESM_ERABM_REL_IND_STRU       *pEsmRabmRelIndMsg   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmRabmRelIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_REL_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmRelIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmRelIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmRelIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pEsmRabmRelIndMsg), 0, NAS_ESM_GET_MSG_LENGTH(pEsmRabmRelIndMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmRelIndMsg,ID_ESM_ERABM_REL_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmRelIndMsg);

}
VOS_VOID NAS_ESM_SndEsmRabmDeactAllMsg( VOS_VOID )
{
    VOS_UINT32                  ulEpsbId                    = NAS_ESM_NULL;
    VOS_UINT32                  ulActiveFlg                 = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmRabmDeactAllMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, LNAS_ENTRY);

    /*�ҳ��Ѽ�����أ�����¼��ID*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*�˳����Ѽ���*/
        if( NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId) )
        {
            /*�����Ѽ������ID,׼�����͸�RABM*/
            aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

            /*���ñ�ʶλ*/
            ulActiveFlg = NAS_ESM_SUCCESS;
        }
    }

    /*������еĳ��ؾ�δ����*/
    if( NAS_ESM_FAILURE == ulActiveFlg )
    {
        /*��ӡ��Ϣ*/
        NAS_ESM_NORM_LOG("NAS_ESM_SndEsmRabmDeactAllMsg:NORMAL:no bearer active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, 1);
        return ;
    }

    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId);

}
VOS_VOID NAS_ESM_CopyRabmTftInfo( ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo,
                                         const NAS_ESM_CONTEXT_TFT_STRU* pstCntxtTftInfo,
                                            VOS_UINT32 ulSdfPfNum)
{
    VOS_UINT32                          ulPfNum = NAS_ESM_NULL;

    ulPfNum = ulSdfPfNum;

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)pstRabmTftInfo, 0, ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));

    /* ����*/
    NAS_ESM_MEM_CPY(pstRabmTftInfo, pstCntxtTftInfo, ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));
}



VOS_VOID  NAS_ESM_RcvEsmRabmBearerStatusReq(const ESM_ERABM_BEARER_STATUS_REQ_STRU *pRcvMsg )
{
    VOS_UINT32                  ulCnt                           = NAS_ESM_NULL;
    VOS_UINT32                  ulQueryRslt                     = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbId                        = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                     = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                  ulStateTblIndex                 =  NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo              = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ENTRY);

    /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_FAIL);
        return ;
    }

    /* ����������������ʱ������ERABM���͵�BEAR_STATUS_REQ��Ϣʱ�����ʱ������ı���ȥ������أ��������
    OPID����ƥ�䣻�����RABM�������͵���Ϣ������ƥ�䣻RABM���ESM��ACT_IND��Ϣ�ظ�BEAR_STATUS_REQ��Ϣʱ��
    ����OPIDƥ�䣬���ƥ�䲻�ɹ���ֱ�Ӷ��� */
    if ((pRcvMsg->ucSessionId != 0) && (pRcvMsg->ucSessionId != NAS_ESM_GetErabmSessionIdValue()))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause OPID is not match!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ERROR);
        return;
    }

    /*ȡ����Ϣ�е�EPSID��Ϣ*/
    ulEpsbIdNum = pRcvMsg->ulEpsIdNum;
    NAS_ESM_MEM_CPY(aulEpsbId, pRcvMsg->aulEpsId, ulEpsbIdNum*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��ѯÿһ��������Ϣ*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*ȡ��������Ϣ*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*����˳���δ����*/
        if( NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState )
        {
            continue;
        }

        ulQueryRslt = NAS_ESM_FAILURE;

        /*��ѯID_ESM_ERABM_BEARER_STATUS_IND��Ϣ��EPSID��Ϣ���Ƿ�����˳���ID*/
        for( ulCnt = 0; ulCnt < ulEpsbIdNum; ulCnt++ )
        {
            if( ulEpsbId == aulEpsbId[ulCnt] )
            {
                ulQueryRslt = NAS_ESM_SUCCESS;
                break;
            }
        }

        /*���������*/
        if( NAS_ESM_FAILURE == ulQueryRslt )
        {
            /*֪ͨAPP�ͷų��أ����ͷ���س��غ���Դ*/
            NAS_ESM_DeactBearerAndInformApp(ulEpsbId);
            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

}
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmRabmMsgProc.c */
