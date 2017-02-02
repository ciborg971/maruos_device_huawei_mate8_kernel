


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"
#include    "NasEsmIpMsgProc.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "NasEsmSmMsgProc.h"
#include    "NasEsmNwMsgProc.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGBEARERRESMODPROC_C
#define    THIS_NAS_FILE_ID        PS_FILE_ID_NASESMNWMSGBEARERRESMODPROC_C
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

VOS_VOID  NAS_ESM_ProcValidNwMsgResModRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpStateTblIndex =  NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgResModRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgResModRej_ENUM, LNAS_ENTRY);

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3481);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* �����ͷŴ˳��صĹ���ȱʡ���غ���س��� */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulLinkedEpsbId);

            /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pstStateAddr->ulLinkedEpsbId, &ulTmpStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulTmpStateTblIndex);
            }
        }
        /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                   NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }
    else if(ID_APP_ESM_PDP_RELEASE_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType)
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* �����ͷŴ˳��� */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

            /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
        }
        else
        {
            NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex,
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        }
    }
    else
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* �����ͷŴ˳��� */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulEpsbId);

            /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);
        }
        else
        {
            /*��APP���س����޸�ʧ����Ϣ*/
            NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex, \
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        }
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}



/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_ProcValidNwMsgActDedictdEpsbReq
(
    VOS_UINT32                                      ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU              *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    EMM_ESM_INTRA_DATA_IND_STRU        *pMsg                = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pstEsmBearerManageInfo = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    pMsg = (EMM_ESM_INTRA_DATA_IND_STRU *) pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgActDedictdEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgActDedictdEpsbReq_ENUM, LNAS_ENTRY);

    /*ȡ��������Ϣ*/
    ulEpsbId = (VOS_UINT32)(pMsg->stEsmNwMsgIE.ucEpsbId);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*����������ϢЯ����PTI*/
    pstStateAddr->bitOpNwMsgRecord    = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ucPti = pMsg->stEsmNwMsgIE.ucPti;

    /*���ó�������*/
    pstEpsbCntxtInfo->enBearerCntxtType = NAS_ESM_BEARER_TYPE_DEDICATED;

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /* �����APP������������̣����Զ����� */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        /* �Զ�����ר�г��ؼ���Ĵ��� */
        NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                         &(pMsg->stEsmNwMsgIE));

        return ;
    }

    /*ȡ�ó��ع�����Ϣ*/
    pstEsmBearerManageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*APP���öԳ��ؼ����Զ�Ӧ��*/
    if( NAS_ESM_BEARER_MANAGE_MODE_AUTO == pstEsmBearerManageInfo->enMode )
    {
        /*APP����Ϊ����*/
        if( NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT == pstEsmBearerManageInfo->enType )
        {
            /* �Զ�����ר�г��ؼ���Ĵ��� */
            NAS_ESM_DediBearActMsgAutoAccept(ulStateTblIndex,
                                             stEncodeInfo,
                                             &(pMsg->stEsmNwMsgIE));
        }
        else
        {
            NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgActDedictdEpsbReq:NORM: Auto reject manage type!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgActDedictdEpsbReq_ENUM, 2);

            /*������ظ�Activate default bearer context reject*/
            stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
            stEncodeInfo.ucESMCau = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;

            NAS_ESM_ActDediBearFailProc(&stEncodeInfo,ulStateTblIndex);
        }
    }
    else
    {
        /* ר�г��ؼ����ֶ����� */
        NAS_ESM_DediBearActMsgManualProc(ulStateTblIndex,
                                          &(pMsg->stEsmNwMsgIE));
    }
}


VOS_VOID NAS_ESM_InformAppEpsBearerModFail
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if(NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        switch(pstStateAddr->stAppMsgRecord.enAppMsgType)
        {
            case ID_APP_ESM_PDP_SETUP_REQ:
                NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));
                break;

            case ID_APP_ESM_PDP_RELEASE_REQ:
                NAS_ESM_SndEsmAppSdfRelCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));

                break;
            case ID_APP_ESM_PDP_MODIFY_REQ:
                NAS_ESM_SndEsmAppSdfModCnfFailMsg(ulStateTblIndex,\
                                         NAS_ESM_GetAppErrorByEsmCause(enEsmCause));

                break;
            default:
                NAS_ESM_WARN_LOG("NAS_ESM_InformAppEpsBearerModFail:WARNING:No Support App Msg!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_InformAppEpsBearerModFail_ENUM, LNAS_MSG_INVALID);
                break;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_InformAppModEspBearerSucc
 Description     : ֪ͨAPPר�г�����Ϣ�޸ĳɹ�
 Input           : pstMsgIE--------------------�����Ŀտ���Ϣ
                   ulStateTblIndex-------------״̬���¼������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_InformAppDediBearModSucc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU           *pstStateAddr = VOS_NULL_PTR;
    APP_ESM_BEARER_MODIFY_ENUM_UINT32  enModfyType  = APP_ESM_BEARER_MODIFY_BUTT;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* APP������������� */
    if(NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        NAS_ESM_SndEsmAppSdfProcCnfSucc(ulStateTblIndex, NAS_ESM_GetBearModifyType(pstMsgIE));
        return ;
    }

    if (NAS_ESM_APP_IND_TYPE_SETUP == pstStateAddr->enAppIndType)
    {
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, APP_SUCCESS);
        return ;
    }

    if (NAS_ESM_APP_IND_TYPE_RELEASE == pstStateAddr->enAppIndType)
    {
        NAS_ESM_SndEsmAppSdfRelIndMsg(pstStateAddr->ulCid, pstMsgIE->ucEpsbId);
        return ;
    }

    enModfyType = NAS_ESM_GetBearModifyType(pstMsgIE);
    NAS_ESM_SndEsmAppSdfModIndMsg(ulStateTblIndex, enModfyType);

}
VOS_VOID NAS_ESM_InformAppEpsBearerModSucc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    VOS_UINT32                          ulStateTblIndex
)
{
    APP_ESM_BEARER_MODIFY_ENUM_UINT32  enModfyType  = APP_ESM_BEARER_MODIFY_BUTT;

    /* ����ȱʡ���أ��Ҵ�QOS�����޸�����Ϊ���޸�TFT���޸�QOS������ȱʡ���أ�
       �Ҳ���QOS�����޸�����Ϊ�޸�TFT */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(pstMsgIE->ucEpsbId)))
    {
        enModfyType = NAS_ESM_GetBearModifyType(pstMsgIE);
        NAS_ESM_SndEsmAppSdfModIndMsg(ulStateTblIndex, enModfyType);
        return ;
    }

    /* ֪ͨAPPר�г�����Ϣ�޸ĳɹ� */
    NAS_ESM_InformAppDediBearModSucc(pstMsgIE, ulStateTblIndex);
}
VOS_VOID  NAS_ESM_ProcValidNwMsgModEpsbReq
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU       *pstEsmBearerManageInfo = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgModEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgModEpsbReq_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ��������Ϣ*/
    ulEpsbId = (VOS_UINT32)(pRcvMsg->stEsmNwMsgIE.ucEpsbId);

    if(NAS_ESM_BEARER_PROC_TRANS_STATE_INACTIVE == pstStateAddr->enProcTransTState)
    {
        /*����������ϢЯ����PTI*/
        pstStateAddr->stNwMsgRecord.ucPti = pRcvMsg->stEsmNwMsgIE.ucPti;
    }

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, pstStateAddr->stTimerInfo.enPara);

    /* �����APP������������̣����Զ����� */
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        /* �Զ����ܳ����޸ĵĴ��� */
        NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                     stEncodeInfo,
                                    &(pRcvMsg->stEsmNwMsgIE));

        return ;
    }

    /*ȡ�ó��ع�����Ϣ*/
    pstEsmBearerManageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*APP���öԳ��ؼ����Զ�Ӧ��*/
    if( NAS_ESM_BEARER_MANAGE_MODE_AUTO == pstEsmBearerManageInfo->enMode )
    {
        /*APP����Ϊ����*/
        if( NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT == pstEsmBearerManageInfo->enType )
        {
            /* �Զ����ܳ����޸ĵĴ��� */
            NAS_ESM_BearModMsgAutoAccept(ulStateTblIndex,
                                         stEncodeInfo,
                                        &(pRcvMsg->stEsmNwMsgIE));
        }
        else
        {
            NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgModEpsbReq:NORM: Auto reject manage type!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgModEpsbReq_ENUM, 2);

            stEncodeInfo.bitOpESMCau = NAS_ESM_OP_TRUE;
            stEncodeInfo.ucESMCau    = NAS_ESM_CAUSE_INSUFFICIENT_RESOURCES;
            NAS_ESM_BearModFailProc(&stEncodeInfo,ulStateTblIndex);
        }
    }
    else
    {
        /* �����޸��ֶ����� */
        NAS_ESM_BearModMsgManualProc(ulStateTblIndex,
                                    &(pRcvMsg->stEsmNwMsgIE));
    }
}



VOS_UINT32 NAS_ESM_IsExistSameEpsbIdInList
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                           ucEpsBearNum,
    const VOS_UINT8                    *pucEpsbIdArray
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    for (ulCnt = NAS_ESM_NULL; ulCnt < ucEpsBearNum; ulCnt++)
    {
        if (ucEpsbId == pucEpsbIdArray[ulCnt])
        {
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsNeedPreferrenceCollision
 Description     : �ж��Ƿ���Ҫ�������ȼ���ͻ����
 Input           : pstNwMsg -- �����Ŀտ���Ϣָ��
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-08  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsNeedPreferrenceCollision
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg
)
{

    if (NAS_ESM_OP_FALSE == pstNwMsg->bitOpTadInfo)
    {
        return PS_FALSE;
    }

    if ((NAS_ESM_TFT_OP_TYPE_CREATE_TFT == pstNwMsg->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstNwMsg->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER == pstNwMsg->stTadInfo.enTftOpType))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidateLinkedEpsbId
 Description     : ��ȡ�տ���Ϣ��Я���ĳ��ع�����ȱʡ����
 Input           : pstNwMsg---------------------�����Ŀտ���Ϣָ��
                   pucLinkedEpsbId--------------ȱʡ���غ�ָ��
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-5-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_GetDefltBearLinkToBearInAirMsg
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucLinkedEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEspCntxtInfo = VOS_NULL_PTR;

    if (NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ == pstNwMsg->enEsmCnMsgType)
    {
        *pucLinkedEpsbId = pstNwMsg->ucLinkedEpsbId;
    }
    else
    {
        pstEspCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstNwMsg->ucEpsbId);
        if (NAS_ESM_BEARER_TYPE_DEDICATED == pstEspCntxtInfo->enBearerCntxtType)
        {
            *pucLinkedEpsbId = (VOS_UINT8)pstEspCntxtInfo->ulLinkedEpsbId;
        }
        else
        {
            *pucLinkedEpsbId = pstNwMsg->ucEpsbId;
        }
    }
}


VOS_VOID  NAS_ESM_ValidatePfPrecedence
(
    const NAS_ESM_NW_MSG_STRU          *pstNwMsg,
    VOS_UINT8                          *pucEpsBearNum,
    VOS_UINT8                          *pucEpsbIdArray
)
{
    VOS_UINT8                           ucCnt1      = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt2      = NAS_ESM_NULL;
    VOS_UINT8                           ucEpsbIdTmp = NAS_ESM_NULL;
    VOS_UINT8                           ucPfNum     = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt      = NAS_ESM_FAILURE;
    NAS_ESM_PF_PRCDNC_VLDT_STRU        *pstPfPVList = VOS_NULL_PTR;

    *pucEpsBearNum = NAS_ESM_NULL;

    /* �������ȼ���֤�б�洢�ռ� */
    pstPfPVList = NAS_ESM_MEM_ALLOC(NAS_ESM_MAX_EPSB_NUM * NAS_ESM_MAX_SDF_PF_NUM
                                    * sizeof(NAS_ESM_PF_PRCDNC_VLDT_STRU));

    if (VOS_NULL_PTR == pstPfPVList)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedence:NAS_ESM_MEM_ALLOC failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /* ��ȡ�տ���Ϣ��Я���ĳ��ع�����ȱʡ���� */
    NAS_ESM_GetDefltBearLinkToBearInAirMsg(pstNwMsg, &ucEpsbIdTmp);

    /* �γ����ȼ���֤�б� */
    ulRslt = NAS_ESM_CreatePfPrecedenceValidateListInPdn(ucEpsbIdTmp,
                                                         &ucPfNum,
                                                         pstPfPVList);

    if (ulRslt != NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePfPrecedence:NAS_ESM_CreatePfPrecedenceValidateListInPdn failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_FAIL);

        /* �ͷ����ȼ���֤�б�洢�ռ� */
        NAS_ESM_MEM_FREE(pstPfPVList);

        return ;
    }

    for (ucCnt1 = NAS_ESM_NULL; ucCnt1 < pstNwMsg->stTadInfo.ucSdfPfNum; ucCnt1++)
    {
        for (ucCnt2 = NAS_ESM_NULL; ucCnt2 < ucPfNum; ucCnt2++)
        {
            if (pstPfPVList[ucCnt2].ucPrecedence != pstNwMsg->stTadInfo.astSdfPfInfo[ucCnt1].ucPrecedence)
            {
                continue;
            }
            /* �����ͬһ�����ص���ͬ��Packetfilter,�������ȼ���ͻ */
            if((pstPfPVList[ucCnt2].ucEpsbId == pstNwMsg->ucEpsbId)
            && (pstPfPVList[ucCnt2].ucPfId == pstNwMsg->stTadInfo.astSdfPfInfo[ucCnt1].ucNwPacketFilterId))
            {
                continue;
            }

            ucEpsbIdTmp = pstPfPVList[ucCnt2].ucEpsbId;

            /* �����غ������в����ڵĳ��غ���ӵ������� */
            ulRslt = NAS_ESM_IsExistSameEpsbIdInList(ucEpsbIdTmp,
                                                    *pucEpsBearNum,
                                                     pucEpsbIdArray);

            if (NAS_ESM_FAILURE == ulRslt)
            {
                NAS_ESM_INFO_LOG1("NAS_ESM_ValidatePfPrecedence:collision Epsbid =",ucEpsbIdTmp);
                TLPS_PRINT2LAYER_INFO1(NAS_ESM_ValidatePfPrecedence_ENUM, LNAS_FAIL, ucEpsbIdTmp);

                pucEpsbIdArray[*pucEpsBearNum] = ucEpsbIdTmp;
                (*pucEpsBearNum)++;
            }
        }
    }

    /* �ͷ����ȼ���֤�б�洢�ռ� */
    NAS_ESM_MEM_FREE(pstPfPVList);
}
VOS_VOID NAS_ESM_LocalDeactAlreadyActiveEpsBearer
(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulStateTblId    = NAS_ESM_NULL;

    /* �����Ѿ����ȥ������� */
    if(NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_LocalDeactAlreadyActiveEpsBearer: local deactive active bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_LocalDeactAlreadyActiveEpsBearer_ENUM, 1);

        /*Ӧ��ȥ����˳��ؼ���������ĳ���*/
        NAS_ESM_DeactBearerAndInformApp(ulEpsbId);

        /*�������ֹ��ulEpsbId������������Ϣ*/
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId,
                                                                &ulStateTblId))
        {
            NAS_ESM_RelStateTblResource(ulStateTblId);
        }
    }
}
VOS_UINT32  NAS_ESM_SndMsgToRelEpsBearer
(
    VOS_UINT32                          ulEpsbId
)
{
    VOS_UINT32                          ulStateTblIndex     = NAS_ESM_NULL;
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    VOS_UINT32                          ulPti               = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_RES_MOD_ENCODE_INFO_STRU    stResModEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndMsgToRelEpsBearer is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndMsgToRelEpsBearer_ENUM, LNAS_ENTRY);

    (VOS_VOID)NAS_ESM_QueryFirstSdfIdByEpsbId(ulEpsbId, &ulCid);

    /*����CID�����ҵ�״̬���ulStateTblIndex*/
    if( NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid,&ulStateTblIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndMsgToRelEpsBearer:WARNING: Tbl index Query Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndMsgToRelEpsBearer_ENUM, ESM_Tbl_index_Query_Fail);
        return NAS_ESM_FAILURE;
    }

    /*����PTI�������������Ϣ��*/
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->stNwMsgRecord.ucPti = (VOS_UINT8)ulPti;

    /*���NAS_ESM_ENCODE_INFO_STRU*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stResModEncodeInfo, 0, sizeof(NAS_ESM_RES_MOD_ENCODE_INFO_STRU));
    stResModEncodeInfo.bitOpESMCau        = NAS_ESM_OP_TRUE;
    stResModEncodeInfo.ucESMCau           = NAS_ESM_CAUSE_REGULAR_DEACTIVATION;
    stResModEncodeInfo.ulCid              = pstStateAddr->ulCid;
    stResModEncodeInfo.ucPti              = (VOS_UINT8)ulPti;
    stResModEncodeInfo.ulEpsbId           = ulEpsbId;
    stResModEncodeInfo.ulLinkedEpsbId     = ulEpsbId;
    stResModEncodeInfo.enSdfOpType        = NAS_ESM_SDF_OP_TYPE_DELETE_SDF;

    /*��װBearer_Res_Mod_Req��Ϣ*/
    if( NAS_ESM_FAILURE == NAS_ESM_EncodeBearerResModReqMsgRelBearer(stResModEncodeInfo, \
                                                      pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                      &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SndMsgToRelEpsBearer:EncodeBearerResModReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndMsgToRelEpsBearer_ENUM, EncodeBearerResModReqMsg_fail);

        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return NAS_ESM_FAILURE;
    }

    pstStateAddr->stNwMsgRecord.enEsmCnMsgType = NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REQ;
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq = PS_FALSE;
    pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /*���ú�����ESM��EMM������Ϣ:ID_EMM_ESM_DATA_REQ(BEARER RESOURCE MODIFICATION REQ)*/
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                pstStateAddr->stNwMsgRecord.ulMsgLength,
                                pstStateAddr->stNwMsgRecord.aucMsgBuff);

    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                           pstStateAddr->stNwMsgRecord.ulMsgLength,
                           NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                           ESM_BEARER_RESOUCE_MOD_REQ);

    /* �ͷŶ�̬�� */
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcPfPrecedenceCollision
 Description     : PF���ȼ���ͻ����
 Input           : enEsmCnMsgType-----------------------�տ���Ϣ����
                   pstEncodeInfo------------------------����������Ϣ
                   ulStateTblIndex----------------------��̬������
                   ucEpsBearNum-------------------------������
                   pucEpsbIdArray-----------------------���������׵�ַ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-5-26  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ProcPfPrecedenceCollision
(
    const NAS_ESM_NW_MSG_STRU                *pstNwMsg
)
{
    VOS_UINT8                           ucCnt               = NAS_ESM_NULL;
    VOS_UINT8                           ulEpsBearNum        = NAS_ESM_NULL;
    VOS_UINT8                           aulEpsbIdArray[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};

    /*  ��֤�տ���Ϣ��Я����PF���ȼ��뵱ǰ��PDN��*/
    /*  ���г��ص�PF�����ȼ��Ƿ��ͻ */
    NAS_ESM_ValidatePfPrecedence(pstNwMsg, &ulEpsBearNum, aulEpsbIdArray);

    if (NAS_ESM_NULL == ulEpsBearNum)
    {
        return;
    }

    /* �ж��Ƿ������ԭ�е�ȱʡ�������ȼ���ͻ����� */
    for (ucCnt = NAS_ESM_NULL; ucCnt < ulEpsBearNum; ucCnt++)
    {
        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ESM_GetBearCntxtType(aulEpsbIdArray[ucCnt])))
        {
            break;
        }
    }

    /* ����ȱʡ���ؾ��ͷ�ȱʡ���أ������ͷų�ͻ��ר�г���*/
    if (ucCnt >= ulEpsBearNum)
    {
        for (ucCnt = NAS_ESM_NULL; ucCnt < ulEpsBearNum; ucCnt++)
        {
            NAS_ESM_LOG1("NAS_ESM_ProcPfPrecedenceCollision:release dedicate bearer ",aulEpsbIdArray[ucCnt]);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 1, aulEpsbIdArray[ucCnt]);

            /* ���Ϳտ���Ϣ,�ͷų��ص�����Packetfilter */
            if (NAS_ESM_FAILURE == NAS_ESM_SndMsgToRelEpsBearer(aulEpsbIdArray[ucCnt]))
            {
                NAS_ESM_WARN_LOG("NAS_ESM_ProcPfPrecedenceCollision:Snd Rel Beare All Pf Error!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 2);
            }

            NAS_ESM_LocalDeactAlreadyActiveEpsBearer(aulEpsbIdArray[ucCnt]);
        }
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ProcPfPrecedenceCollision:release default bearer!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcPfPrecedenceCollision_ENUM, 3);

        NAS_ESM_LocalDeactAlreadyActiveEpsBearer(aulEpsbIdArray[ucCnt]);
    }


    /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

}



VOS_UINT32  NAS_ESM_GetPacketFilter
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    NAS_ESM_CONTEXT_TFT_STRU          **pstPacketFilter,
    VOS_UINT8                           ucNwPacketFilterId
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    /* ��������Ϸ��Լ�� */
    if(VOS_NULL_PTR == pstSdfCntxtInfo)
    {
        return NAS_ESM_FAILURE;
    }

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if(ucNwPacketFilterId == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucNwPacketFilterId)
        {
            *pstPacketFilter = &pstSdfCntxtInfo->astSdfPfInfo[ulCnt];
            return NAS_ESM_SUCCESS;
        }
    }
    return NAS_ESM_FAILURE;
}
VOS_VOID NAS_ESM_DeleteOnePacketFilter
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT8                           ucNwPacketFilterId
)
{
    VOS_UINT32                          ulCnt    = NAS_ESM_NULL;

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if(ucNwPacketFilterId == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucNwPacketFilterId)
        {
            break;
        }
    }

    if (ulCnt < pstSdfCntxtInfo->ulSdfPfNum)
    {
        /* �������һ����Ҫɾ����PF��λ�� */
        NAS_ESM_MEM_CPY(&pstSdfCntxtInfo->astSdfPfInfo[ulCnt],
                        &pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum - 1],
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU))

        NAS_ESM_MEM_SET(&pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum - 1],
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU))

        pstSdfCntxtInfo->ulSdfPfNum--;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_DeletePacketFilterProc
 Description     : ɾ��SDF����
 Input           : pstEpsbCntxtInfo---------------������Ϣ
                   pstSdfCntxtInfo----------------SDF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact
    2.lihong00150010      2010-5-31 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_DeletePacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo   = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo   = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_DeletePacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DeletePacketFilterProc_ENUM, LNAS_ENTRY);

    pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
    pstSdfQosInfo = &pstSdfCntxtInfo->stSdfQosInfo.stQosInfo;
    pstStateAddr    = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ɾ��SDF��������ָ����Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* ����ר�г��أ��Ҵ�SDF��packet filter��ȫ��ɾ������ɾ����SDF */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* �޸��ϱ�����ΪNAS_ESM_APP_IND_TYPE_RELEASE */
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_RELEASE;

        /* ɾ��SDF������ */
        NAS_ESM_MEM_SET(pstSdfCntxtInfo, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_ReplacePacketFilterProc
 Description     : �޸�SDF����
 Input           : pstMsgIE-----------------------��������Ϣ
                   pstSdfCntxtInfo----------------SDF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ReplacePacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    VOS_UINT32                          ulCnt            = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    VOS_UINT8                           ucPacketFilterID = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU           *pstPacketFilter  = VOS_NULL_PTR;
    NAS_ESM_TAD_INFO_STRU              *pstTadInfoTmp    = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, LNAS_ENTRY);

    pstTadInfoTmp = NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_TAD_INFO_STRU));
    if(VOS_NULL_PTR == pstTadInfoTmp)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_ReplacePacketFilterProc:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ReplacePacketFilterProc_ENUM, LNAS_NULL_PTR);
        return;
    }

    NAS_ESM_MEM_SET(pstTadInfoTmp, 0, sizeof(NAS_ESM_TAD_INFO_STRU));

    /* �޸�PF*/
    for(ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        ulRslt = NAS_ESM_GetPacketFilter(   pstSdfCntxtInfo,
                                            &pstPacketFilter,
                                            pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);

        /* ���ھ��滻�������ھ���� */
        if(NAS_ESM_SUCCESS == ulRslt)
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc:PF Exist!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, 1);
            /* buffered static packetfilter id */
            ucPacketFilterID = pstPacketFilter->ucPacketFilterId;

            NAS_ESM_MEM_CPY(    pstPacketFilter,
                                &(pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt]),
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstPacketFilter->ucPacketFilterId = ucPacketFilterID;
        }
        else
        {
            NAS_ESM_INFO_LOG("NAS_ESM_ReplacePacketFilterProc:PF Not Exist!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_ReplacePacketFilterProc_ENUM, 2);
            NAS_ESM_MEM_CPY(&pstTadInfoTmp->astSdfPfInfo[pstTadInfoTmp->ucSdfPfNum],
                            &pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt],
                            sizeof(NAS_ESM_CONTEXT_TFT_STRU));
            pstTadInfoTmp->ucSdfPfNum++;
        }
    }

    /* ���û���ҵ���filter ��Sdf��*/
    if ((NAS_ESM_NULL != pstTadInfoTmp->ucSdfPfNum)
      &&((pstSdfCntxtInfo->ulSdfPfNum + pstTadInfoTmp->ucSdfPfNum) <= NAS_ESM_MAX_SDF_PF_NUM))
    {
        NAS_ESM_MEM_CPY(&pstSdfCntxtInfo->astSdfPfInfo[pstSdfCntxtInfo->ulSdfPfNum],
                        pstTadInfoTmp->astSdfPfInfo,
                        sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstTadInfoTmp->ucSdfPfNum);
        pstSdfCntxtInfo->ulSdfPfNum += pstTadInfoTmp->ucSdfPfNum;

        /* ��ֵSDF�����ĳ�����Ϣ */
        pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;
    }

    NAS_ESM_MEM_FREE(pstTadInfoTmp);
}


VOS_VOID NAS_ESM_CreateTftProc
(
    const  NAS_ESM_NW_MSG_STRU                  *pstMsgIE,
    NAS_ESM_SDF_CNTXT_INFO_STRU                 *pstSdfCntxtInfo
)
{
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_CreateTftProc: create to default bearer.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CreateTftProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_CPY(pstSdfCntxtInfo->astSdfPfInfo,\
                    pstMsgIE->stTadInfo.astSdfPfInfo,\
                    sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);
    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;
    pstSdfCntxtInfo->ulEpsbId   = pstMsgIE->ucEpsbId;
}
VOS_VOID NAS_ESM_DeleteTftProc
(
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_DeleteTftProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DeleteTftProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET(pstSdfCntxtInfo->astSdfPfInfo,\
                    NAS_ESM_NULL,\
                    sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM);
    pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AddPacketFilterProc
 Description     : ���SDF����
 Input           : pstMsgIE-----------------------��������Ϣ
                   pstEpsbCntxtInfo---------------������Ϣ
                   pstSdfCntxtInfo----------------SDF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-2-3  Draft Enact
    2.lihong00150010      2010-5-31 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_AddPacketFilterProc
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT32                          ulLoopTimes         = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_AddPacketFilterProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AddPacketFilterProc_ENUM, LNAS_ENTRY);

    pstStateAddr    = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ���տ���Ϣ��Я����Ԥ��ӵ�packet filter�ڳ�������ȫ�����ڻ򲿷ִ���,
       ���Ѵ��ڵ�packet filter������sdf�붯̬���д洢���û�Ԥ������sdf��һ�£�
       ��ɾ���Ѵ��ڵ�packet filter������sdf�����³���QOS��Ϣ */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_AddPacketFilterProc:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AddPacketFilterProc_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* ɾ����SDF������ */
        NAS_ESM_MEM_SET(pstSdfCntxtInfoTmp, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* �ϱ�APP SDF�ͷ� */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* ������ع����Ĵ�CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }

    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* �����ר�г��أ��ҵ�ǰSDF��PF��Ϊ0,��˵���˴β���Ϊ���SDF����˽��ϱ�
       �����޸�ΪNAS_ESM_APP_IND_TYPE_SETUP */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_SETUP;
    }

    /* ��û���ҵ���ͬ������ӣ����ҵ���ͬ�����滻 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        pstSdfPara      = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

        /* ������û������,��ô��̬��������Ŀһ����*/
        /* �ڵ��ڶ�̬����; ������������������, ��̬*/
        /* ����Ҫ���ڵ��ھ�̬����*/
        ulLoopTimes     = NAS_ESM_MIN(pstSdfCntxtInfo->ulSdfPfNum, pstSdfPara->ulPfNum);

        for (ulCnt = NAS_ESM_NULL; ulCnt < ulLoopTimes; ulCnt++)
        {
            pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId =
                            pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId;

        }
    }
}


VOS_VOID  NAS_ESM_UpdatePacketFilterToSdfCntxt
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ��ʼ���ϱ�����ΪNAS_ESM_APP_IND_TYPE_MODIFY */
    pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_MODIFY;

    /* �ж��Ƿ����TFT���� */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :

            /* ���packet filter */
            NAS_ESM_AddPacketFilterProc(    pstMsgIE,
                                            pstEpsbCntxtInfo,
                                            pstSdfCntxtInfo,
                                            ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:

            /* �޸�packet filter */
            NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:

            /* ɾ��SDF�����Ĳ��޸ĳ���QOS��Ϣ */
            NAS_ESM_DeletePacketFilterProc( pstMsgIE,
                                            pstEpsbCntxtInfo,
                                            pstSdfCntxtInfo,
                                            ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:

            /* ����TFT */
            NAS_ESM_CreateTftProc(pstMsgIE, pstSdfCntxtInfo);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_TFT:

            /* ɾ��TFT */
            NAS_ESM_DeleteTftProc(pstSdfCntxtInfo);
            break;

       default:
            break;
    }

    return;

}
VOS_VOID  NAS_ESM_UpdateEpsQosInfo
(
    const  NAS_ESM_NW_MSG_STRU         *pstMsgIE,
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo,
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo
)
{
    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* ����NON-GBR���أ����յ�����ĳ����޸�����TAD��ΪADD SDF���Ҳ���QOS��Ϣʱ,
           ������QOS��Ϣ�е�QCI��ֵ������SDF��QCI*/
        if ((PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
          && (NAS_ESM_OP_TRUE == pstMsgIE->bitOpTadInfo)
          && (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstMsgIE->stTadInfo.enTftOpType))
        {
            NAS_ESM_MEM_SET(&pstSdfCntxtInfo->stSdfQosInfo,
                            NAS_ESM_NULL,
                            sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* ����SDF��QCI��Ϣ */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }

    /* ����SDF��packet filter��ȫ��ɾ�����򷵻أ���Ϊ������³���QOS�ĸ���
       �Ѿ��ں���NAS_ESM_DeletePacketFilterProc����� */
    if ((NAS_ESM_OP_TRUE == pstMsgIE->bitOpTadInfo)
     && (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER == pstMsgIE->stTadInfo.enTftOpType)
     && (NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum))
    {
        return ;
    }

    /* ����SDF��QCI��Ϣ */
    pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                      pstMsgIE->stSdfQosInfo.stQosInfo.ucQCI;

    pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                      pstMsgIE->stSdfQosInfo.ucNwQCI;

    /* �����GBR���أ��������������Ϣ */
    if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
    {
        /* �޸�SDF��QOS */
        NAS_ESM_ModEpsQos(&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo), \
                          &pstMsgIE->stSdfQosInfo.stQosInfo, \
                          &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo));

        /*����EPS QOS��ʶλ��EPS QOS����*/
        pstEpsbCntxtInfo->bitOpEpsQos = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&(pstEpsbCntxtInfo->stEpsQoSInfo), \
                        &pstMsgIE->stSdfQosInfo, \
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));
    }
}

VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr      =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfRelCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfRelCnfFailMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_RELEASE_CNF(ʧ��)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ�����ض�̬�����*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*�����ͷŽ��*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
}
VOS_VOID NAS_ESM_SndEsmAppSdfRelCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr      =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfRelCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfRelCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_RELEASE_CNF(�ɹ�)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ�õ�ǰ���غ�*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*�����ͷŽ��*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*������*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;


    NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
}


VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_SETUP_CNF(�ɹ�)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ�����ض�̬�����*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*ԭ����*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*���������Ϣ����ԭ���룬��֪ͨAPP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

    NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);

}
VOS_VOID NAS_ESM_SndEsmAppSdfSetupCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfSetupCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfSetupCnfFailMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*������*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfSetupCnfMsg(&stEsmAppCnfMsg);

}
VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfSuccMsg(   VOS_UINT32 ulStateTblIndex)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppNdisConnCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppNdisConnCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_SETUP_CNF(�ɹ�)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ�����ض�̬�����*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*ԭ����*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);

    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*���������Ϣ����ԭ���룬��֪ͨAPP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

    NAS_ESM_SndEsmAppBearerQosIndMsg(pStateTblAddr->ulEpsbId);

}
VOS_VOID NAS_ESM_SndEsmAppNdisConnCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppNdisConnCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppNdisConnCnfFailMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*������*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);

}
VOS_VOID NAS_ESM_SndEsmAppSdfModCnfSuccMsg
(
    VOS_UINT32                          ulStateTblIndex,
    APP_ESM_BEARER_MODIFY_ENUM_UINT32   enModfyType
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU            *pStateTblAddr       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfModCnfSuccMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfModCnfSuccMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ�����ض�̬�����*/
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulEpsbId = pStateTblAddr->ulEpsbId;

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /* ȡ���޸����� */
    stEsmAppCnfMsg.bitOpModifyType = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.enModfyType = enModfyType;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;

    /*ԭ����*/
    /* hongli �޸���Ϣ�в����ܴ�Esm Cause,����ɾ���������*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pStateTblAddr->ulEpsbId);
    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*���������Ϣ����ԭ���룬��֪ͨAPP*/
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

}


VOS_VOID NAS_ESM_SndEsmAppSdfModCnfFailMsg
(
    VOS_UINT32                          ulStateTblIndex,
    VOS_UINT32                          ulErrorCode
)
{
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    NAS_ESM_STATE_INFO_STRU             *pStateTblAddr      =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmAppSdfModCnfFailMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmAppSdfModCnfFailMsg_ENUM, LNAS_ENTRY);

    /*���*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    /*��ñ���StateTblָ��,��ʱ��̬��û���ͷ�*/
    pStateTblAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ��CID*/
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId = pStateTblAddr->ulCid;

    /*ȡ��opid*/
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulOpId = pStateTblAddr->stAppMsgRecord.ulAppMsgOpId;

    /*ȡ��MID*/
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.usOriginalId = pStateTblAddr->stAppMsgRecord.usOriginalId;
    stEsmAppCnfMsg.usTerminalId = pStateTblAddr->stAppMsgRecord.usTerminalId;

    /*���ؽ������*/
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;

    /*������*/
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulErrorCode = ulErrorCode;

    NAS_ESM_SndEsmAppSdfModCnfMsg(&stEsmAppCnfMsg);

}

/*****************************************************************************
 Function Name   : NAS_ESM_SndSmEspBearerMdfIndMsg
 Description     : ��SM���ͳ����޸���Ϣ
 Input           : ucEpsbId-----------------���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndSmEspBearerMdfIndMsg
(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pstEpsBearInfoInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));
    /*lint +e433 +e826*/
    if ( VOS_NULL_PTR == pstEpsBearInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndSmEspBearerMdfIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndSmEspBearerMdfIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd), 0, NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstEpsBearInfoInd->enPdpOption  = SM_ESM_PDP_OPT_MODIFY;
    pstEpsBearInfoInd->ulEpsbId     = ulEpsbId;

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEpsBearInfo(pstEpsbCntxtInfo, pstEpsBearInfoInd);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndSmEspBearerDeactIndMsg
 Description     : ��SM���ͳ���ȥ������Ϣ
 Input           : ucEpsbId-----------------���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/

VOS_VOID NAS_ESM_SndSmEspBearerDeactIndMsg
(
    VOS_UINT32                          ulEpsbId
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pstEpsBearInfoInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));
    /*lint +e433 +e826*/
    if ( VOS_NULL_PTR == pstEpsBearInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndSmEspBearerDeactIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndSmEspBearerDeactIndMsg_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd), 0, NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    pstEpsBearInfoInd->enPdpOption  = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId     = ulEpsbId;

    pstEpsBearInfoInd->ulBitCid     = pstEpsbCntxtInfo->ulBitCId;

    /* ��ֵtransaction id */
    pstEpsBearInfoInd->bitOpTransId = pstEpsbCntxtInfo->bitOpTransId;
    NAS_ESM_MEM_CPY(    &pstEpsBearInfoInd->stTransId,
                        &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
}
/*lint -specific(+e433)*/


VOS_VOID NAS_ESM_DeactBearerAndInformApp(   VOS_UINT32 ulEpsbId )
{
    VOS_UINT8                           ucCnt            =  NAS_ESM_NULL;
    VOS_UINT32                          ulCurPdnNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulEpsbIdNum      =  NAS_ESM_NULL;
    VOS_UINT32                          ulStateTblIndex  =  NAS_ESM_NULL;
    VOS_UINT32                          aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG1("NAS_ESM_DeactBearerAndInformApp is entered.", ulEpsbId);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DeactBearerAndInformApp_ENUM, LNAS_ENTRY, ulEpsbId);

    /*֪ͨAPP�����ͷ�*/
    NAS_ESM_InformAppBearerRel(ulEpsbId);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*�����ǰ����Ϊȱʡ����*/
    if(PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /*���ҵ�ǰPDN������*/
        ulCurPdnNum = NAS_ESM_GetCurPdnNum();

        /*PDN����������1��*/
        if(ulCurPdnNum > 0)
        {
            ulCurPdnNum -= 1;
        }

        /*���浱ǰPDN������*/
        NAS_ESM_SetCurPdnNum(ulCurPdnNum);

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* ֪ͨEHSM�����ͷţ���EHSMֻ֧��ͬ��ȱʡ���أ����ר�г��ز��ش��� */
        NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(ulEpsbId);
        #endif
    }

    /*����ulEpsbIdNum��aulEpsbId���Ա�֪ͨRABM*/
    aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

    /*ѭ��������Ϣ��������˳��ع�����ר�г���*/
    for( ucCnt = NAS_ESM_MIN_EPSB_ID; ucCnt <= NAS_ESM_MAX_EPSB_ID; ucCnt++ )
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucCnt);

        /*ĳһ���ص�Linked EPSB IDΪ��ǰ����ID*/
        if( (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType)
            && (NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)\
            && (pstEpsbCntxtInfo->ulLinkedEpsbId == ulEpsbId) )
        {
            /*֪ͨAPP�����ͷ�*/
            NAS_ESM_InformAppBearerRel(ucCnt);

            /*����ulEpsbIdNum��aulEpsbId���Ա�֪ͨRABM*/
            aulEpsbId[ulEpsbIdNum++] = ucCnt;

            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ucCnt, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId);

    /*�����Ѽ�¼�ĳ���ID��ѭ���ͷų�����Դ*/
    for( ucCnt = 0; ucCnt < ulEpsbIdNum; ucCnt++ )
    {
        /*�ؼ��¼��ϱ�*/
        NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_RELEASE(aulEpsbId[ucCnt]));

        NAS_ESM_SndSmEspBearerDeactIndMsg(aulEpsbId[ucCnt]);

        /*�ͷų�����Դ*/
        NAS_ESM_ClearEsmBearerResource(aulEpsbId[ucCnt]);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_GetBearModifyType
 Description     : ��ȡר�г����޸�����
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-5-25  Draft Enact

*****************************************************************************/
APP_ESM_BEARER_MODIFY_ENUM_UINT32  NAS_ESM_GetBearModifyType
(
    const  NAS_ESM_NW_MSG_STRU *pstMsgIE
)
{

    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        return APP_ESM_BEARER_MODIFY_QOS;
    }

    if (NAS_ESM_TFT_OP_TYPE_NO_OP == pstMsgIE->stTadInfo.enTftOpType)
    {
        return APP_ESM_BEARER_MODIFY_QOS;
    }

    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpEpsQos)
    {
        return APP_ESM_BEARER_MODIFY_TFT_QOS;
    }
    else
    {
        return APP_ESM_BEARER_MODIFY_TFT;
    }
}


VOS_UINT32  NAS_ESM_IsLocalPortRangeSameToSinglePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT2
)
{
    if ((NAS_ESM_OP_TRUE == pstTFT1->bitOpSingleLocalPort)
     && (NAS_ESM_OP_TRUE == pstTFT2->bitOpLocalPortRange)
     && (pstTFT2->usLcPortHighLimit == pstTFT2->usLcPortLowLimit)
     && (pstTFT1->usSingleLcPort == pstTFT2->usLcPortHighLimit))
    {
        /* CN �Ὣֻ����һ���˿ںŵĶ˿ڷ�Χ�鲢Ϊ��һ�˿� */
        return NAS_ESM_SUCCESS;
    }
    else
    {
        return NAS_ESM_FAILURE;
    }

}
VOS_UINT32  NAS_ESM_IsRemotePortRangeSameToSinglePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstTFT2
)
{
    if ((NAS_ESM_OP_TRUE == pstTFT1->bitOpSingleRemotePort)
      &&(NAS_ESM_OP_TRUE == pstTFT2->bitOpRemotePortRange)
      &&(pstTFT2->usRmtPortHighLimit == pstTFT2->usRmtPortLowLimit)
      &&(pstTFT1->usSingleRmtPort == pstTFT2->usRmtPortHighLimit))
    {
        /* CN �Ὣֻ����һ���˿ںŵĶ˿ڷ�Χ�鲢Ϊ��һ�˿� */
        return NAS_ESM_SUCCESS;
    }
    else
    {
        return NAS_ESM_FAILURE;
    }

}
/*****************************************************************************
 Function Name   : NAS_ESM_MatchIpAddrandMask
 Description     : ƥ��TFT������Ip��ַ����������
 Input           : pstNwTFT -- �����TFT��Ϣ
                   pstUeTFT -- Ue��TFT��Ϣ
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Ip��ַ������������ͬ
                   NAS_ESM_FAILURE -- Ip��ַ���������벻��ͬ
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchIpAddrandMask
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    VOS_INT32                           lMatchRslt = NAS_ESM_FAILURE;

    if ((pstPf1->bitOpRmtIpv4AddrAndMask != pstPf2->bitOpRmtIpv4AddrAndMask)
     || (pstPf1->bitOpRmtIpv6AddrAndMask != pstPf2->bitOpRmtIpv6AddrAndMask))
    {
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_OP_TRUE == pstPf1->bitOpRmtIpv4AddrAndMask)
    {
        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv4Address,
                                     pstPf2->aucRmtIpv4Address,
                                     APP_MAX_IPV4_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv4 Address not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 1);
            return NAS_ESM_FAILURE;
        }

        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv4Mask,
                                     pstPf2->aucRmtIpv4Mask,
                                     APP_MAX_IPV4_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv4 Mask not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 2);
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pstPf1->bitOpRmtIpv6AddrAndMask)
    {
        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv6Address,
                                     pstPf2->aucRmtIpv6Address,
                                     APP_MAX_IPV6_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv6 Address not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 3);
            return NAS_ESM_FAILURE;
        }

        lMatchRslt = NAS_ESM_MEM_CMP(pstPf1->aucRmtIpv6Mask,
                                     pstPf2->aucRmtIpv6Mask,
                                     APP_MAX_IPV6_ADDR_LEN);
        if (lMatchRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_NORM_LOG("NAS_ESM_MatchIpAddrandMask:Ipv6 Mask not match!");
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_MatchIpAddrandMask_ENUM, LNAS_FAIL, 4);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchLocalPort
 Description     : ƥ��TFT������Local Port
 Input           : pstNwTFT -- �����TFT��Ϣ
                   pstUeTFT -- Ue��TFT��Ϣ
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Local Port��ͬ
                   NAS_ESM_FAILURE -- Local Port����ͬ
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchLocalPort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((NAS_ESM_SUCCESS == NAS_ESM_IsLocalPortRangeSameToSinglePort(pstPf1,pstPf2))
     || (NAS_ESM_SUCCESS == NAS_ESM_IsLocalPortRangeSameToSinglePort(pstPf2,pstPf1)))
    {
        /* CN �Ὣֻ����һ���˿ںŵĶ˿ڷ�Χ�鲢Ϊ��һ�˿� */
        return NAS_ESM_SUCCESS;
    }

    if ((pstPf1->bitOpLocalPortRange != pstPf2->bitOpLocalPortRange)
     || (pstPf1->bitOpSingleLocalPort != pstPf2->bitOpSingleLocalPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSingleLocalPort)
     && (pstPf1->usSingleLcPort != pstPf2->usSingleLcPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpLocalPortRange)
     && ((pstPf1->usLcPortLowLimit != pstPf2->usLcPortLowLimit)
         || (pstPf1->usLcPortHighLimit != pstPf2->usLcPortHighLimit)))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchRemotePort
 Description     : ƥ��TFT������Remote Port
 Input           : pstNwTFT -- �����TFT��Ϣ
                   pstUeTFT -- Ue��TFT��Ϣ
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- Remote Port��ͬ
                   NAS_ESM_FAILURE -- Remote Port����ͬ
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchRemotePort
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((NAS_ESM_SUCCESS == NAS_ESM_IsRemotePortRangeSameToSinglePort(pstPf1,pstPf2))
     || (NAS_ESM_SUCCESS == NAS_ESM_IsRemotePortRangeSameToSinglePort(pstPf2,pstPf1)))
    {
        /* CN �Ὣֻ����һ���˿ںŵĶ˿ڷ�Χ�鲢Ϊ��һ�˿� */
        return NAS_ESM_SUCCESS;
    }

    if ((pstPf1->bitOpRemotePortRange != pstPf2->bitOpRemotePortRange)
     || (pstPf1->bitOpSingleRemotePort != pstPf2->bitOpSingleRemotePort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSingleRemotePort)
     && (pstPf1->usSingleRmtPort != pstPf2->usSingleRmtPort))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpRemotePortRange)
     && ((pstPf1->usRmtPortLowLimit != pstPf2->usRmtPortLowLimit)
         || (pstPf1->usRmtPortHighLimit != pstPf2->usRmtPortHighLimit)))
    {
       return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_MatchTftOtherItem
 Description     : ƥ��TFT������ProtocolId,security parameter index,
                   TypeOfService,Flow Label Type
 Input           : pstNwTFT -- �����TFT��Ϣ
                   pstUeTFT -- Ue��TFT��Ϣ
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- ��ͬ
                   NAS_ESM_FAILURE -- ����ͬ
  History         :
    1.liuwenyu00143951      2009-12-15  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_MatchTftOtherItem
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if ((pstPf1->bitOpProtocolId != pstPf2->bitOpProtocolId)
      ||(pstPf1->bitOpSecuParaIndex != pstPf2->bitOpSecuParaIndex)
      ||(pstPf1->bitOpTypeOfService != pstPf2->bitOpTypeOfService)
      ||(pstPf1->bitOpFlowLabelType != pstPf2->bitOpFlowLabelType))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpProtocolId)
     && (pstPf1->ucProtocolId != pstPf2->ucProtocolId))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpSecuParaIndex)
     && (pstPf1->ulSecuParaIndex != pstPf2->ulSecuParaIndex))
    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpTypeOfService)
     && ((pstPf1->ucTypeOfService != pstPf2->ucTypeOfService)
         || (pstPf1->ucTypeOfServiceMask != pstPf2->ucTypeOfServiceMask)))

    {
        return NAS_ESM_FAILURE;
    }

    if ((NAS_ESM_OP_TRUE == pstPf1->bitOpFlowLabelType)
     && (pstPf1->ulFlowLabelType != pstPf2->ulFlowLabelType))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name   : NAS_ESM_PfMatch
 Description     : ƥ������packet filter������(�ڶ���PF���һ��PF���)
 Input           : pstPf1 -- ��һ��PF��Ϣ
                   pstPf2 -- �ڶ���PF��Ϣ
 Output          : None
 Return          :
                   NAS_ESM_SUCCESS -- ����packet filterƥ��
                   NAS_ESM_FAILURE -- ����packet filter��ƥ��
  History         :
    1.liuwenyu00143951      2009-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_PfMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf1,
    const NAS_ESM_CONTEXT_TFT_STRU              *pstPf2
)
{
    if (pstPf1->ucPrecedence != pstPf2->ucPrecedence)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Precedence not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 1);
        return NAS_ESM_FAILURE;
    }

    if (pstPf1->enDirection != pstPf2->enDirection)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Direction not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 2);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchIpAddrandMask(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:IP address or mask not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 3);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchLocalPort(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Local port not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 4);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchRemotePort(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:Remote port not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 5);
        return NAS_ESM_FAILURE;
    }

    if (NAS_ESM_FAILURE == NAS_ESM_MatchTftOtherItem(pstPf1,pstPf2))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_PfMatch:NORM:TypeOfService or ProtocolId not match!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_PfMatch_ENUM, LNAS_FAIL, 6);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_TftMatch
 Description     : ƥ������TFT������(��һ��TFT��ڶ���TFT���)
 Input           : pstTft1PfInfo    -- TFT1��PF�����׵�ַ
                   ulTft1PfNum      -- TFT1��PF����
                   pstTft2PfInfo    -- TFT2��PF�����׵�ַ
                   ulTft2PfNum      -- TFT2��PF����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.liuwenyu00143951      2009-10-23  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_TftMatch
(
    const NAS_ESM_CONTEXT_TFT_STRU           *pstTft1PfInfo,
    VOS_UINT32                                ulTft1PfNum,
    NAS_ESM_CONTEXT_TFT_STRU                 *pstTft2PfInfo,
    VOS_UINT32                                ulTft2PfNum
)
{
    VOS_UINT32                           ulCnt1        = NAS_ESM_NULL;
    VOS_UINT32                           ulCnt2        = NAS_ESM_NULL;
    /* for decrease number of loop */
    VOS_UINT16                           usMatchedSdf  = NAS_ESM_NULL;
    VOS_UINT32                           ulTFTMatchRlt = NAS_ESM_FAILURE;

    (VOS_VOID)pstTft2PfInfo;

    if (ulTft2PfNum != ulTft1PfNum)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_TftMatch:WARNING: static and dynamic number not equal!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TftMatch_ENUM, LNAS_FAIL, 1);
        return NAS_ESM_FAILURE;
    }

    /* check every dynamic SDF context information */
    for (ulCnt1 = NAS_ESM_NULL; ulCnt1 < ulTft2PfNum; ulCnt1++)
    {
        for (ulCnt2 = NAS_ESM_NULL; ulCnt2 < ulTft1PfNum; ulCnt2++)
        {
            /* do not search sdf which has found the mapped network packetfilterid */
            if (NAS_ESM_OP_TRUE == ((usMatchedSdf >> ulCnt2) & NAS_ESM_OP_TRUE))
            {
                continue;
            }

            ulTFTMatchRlt = NAS_ESM_PfMatch(    &pstTft2PfInfo[ulCnt1],
                                                &pstTft1PfInfo[ulCnt2]);

            /*lint -e701*/
            if (NAS_ESM_SUCCESS == ulTFTMatchRlt)
            {
                /* set sdf network packetfilterid for check whether the sdf */
                /* has found mapped network packetfilterid  */
                usMatchedSdf |= (VOS_UINT16)(NAS_ESM_BIT_0 << ulCnt2);
                break;
            }
            /*lint +e701*/

         }

        if (NAS_ESM_FAILURE == ulTFTMatchRlt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_TftMatch:WARNING: static and dynamic Tft not matched !");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_TftMatch_ENUM, LNAS_FAIL, 2);
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwActDedictdEpsbReqInfo
 Description     : ����ר�г��ؼ������������Ϣ
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-02  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SaveNwActDedictdEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveNwActDedictdEpsbReqInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwActDedictdEpsbReqInfo_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    /* ����SDF��QOS���� */
    NAS_ESM_MEM_CPY(&pstSdfCntxtInfo->stSdfQosInfo,
                    &pstMsgIE->stSdfQosInfo,
                    sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /*����Linked EPS Bearer����*/
    pstEpsbCntxtInfo->ulLinkedEpsbId =(VOS_UINT32)pstMsgIE->ucLinkedEpsbId;

    /*����EPS QOS��ʶλ��EPS QOS����*/
    pstEpsbCntxtInfo->bitOpEpsQos = NAS_ESM_OP_TRUE;
    NAS_ESM_MEM_CPY(&(pstEpsbCntxtInfo->stEpsQoSInfo),
                    &(pstSdfCntxtInfo->stSdfQosInfo),
                    sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /*����Cid���PF*/
    NAS_ESM_MEM_CPY(pstSdfCntxtInfo->astSdfPfInfo,\
                    pstMsgIE->stTadInfo.astSdfPfInfo,\
                    sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);
    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;
    pstSdfCntxtInfo->ulEpsbId   = pstMsgIE->ucEpsbId;

    /* �����̬�Ͷ�̬��Ϣ��һ�£�����е��� */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);

    /*���TI(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpTransId = pstMsgIE->bitOpTransId;
    NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stTransId,
                        &pstMsgIE->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /*���PDP QOS(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpNegQos = pstMsgIE->bitOpNegQos;
    NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stCntxtQosInfo,
                        &pstMsgIE->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /*���LLC SAPI(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpLlcSapi = pstMsgIE->bitOpLlcSapi;
    pstEpsbCntxtInfo->ucLlcSapi = pstMsgIE->ucLlcSapi;

    /*���Radio Priority(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpRadioPriority = pstMsgIE->bitOpRadioPriority;
    pstEpsbCntxtInfo->ucRadioPriority = pstMsgIE->ucRadioPriority;

    /*���Packet Flow Identifer(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpPacketFlowId = pstMsgIE->bitOpPacketFlowId;
    pstEpsbCntxtInfo->ucPacketFlowId = pstMsgIE->ucPacketFlowId;

}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModEpsbReqInfo
 Description     : ��������޸ļ������������Ϣ
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-12-2  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModEpsbReqInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModEpsbReqInfo_ENUM, LNAS_ENTRY);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        NAS_ESM_SaveNwModDeftEpsbReqInfo(pstMsgIE,ulStateTblIndex);
    }
    else
    {
        NAS_ESM_SaveNwModDediEpsbReqInfo(pstMsgIE,ulStateTblIndex);
    }

    /*���PDP QOS(�������)��ֱ�Ӵ洢*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpNegQos)
    {
        pstEpsbCntxtInfo->bitOpNegQos = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(    &pstEpsbCntxtInfo->stCntxtQosInfo,
                            &pstMsgIE->stCntxtQosInfo,
                            sizeof(NAS_ESM_CONTEXT_QOS_STRU));
    }

    /*���LLC SAPI(�������)��ֱ�Ӵ洢*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpLlcSapi)
    {
        pstEpsbCntxtInfo->bitOpLlcSapi = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucLlcSapi = pstMsgIE->ucLlcSapi;
    }

    /*���Radio Priority(�������)��ֱ�Ӵ洢*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpRadioPriority)
    {
        pstEpsbCntxtInfo->bitOpRadioPriority = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucRadioPriority = pstMsgIE->ucRadioPriority;
    }

    /*���Packet Flow ID(�������)��ֱ�Ӵ洢*/
    if(NAS_ESM_OP_TRUE == pstMsgIE->bitOpPacketFlowId)
    {
        pstEpsbCntxtInfo->bitOpPacketFlowId = NAS_ESM_OP_TRUE;
        pstEpsbCntxtInfo->ucPacketFlowId = pstMsgIE->ucPacketFlowId;
    }

    /*���APN-AMBR(�������)��ֱ�Ӵ洢*/
    if( NAS_ESM_OP_TRUE == pstMsgIE->bitOpApnAmbr )
    {
        if (PS_FALSE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
        {
            pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);
        }

        pstEpsbCntxtInfo->bitOpApnAmbr = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstEpsbCntxtInfo->stApnAmbrInfo,
                        &pstMsgIE->stApnAmbrInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU));
    }

    /* ������Я��P-CSCF��ַ���򸲸�ʽ���� */
    if( NAS_ESM_OP_TRUE == pstMsgIE->bitOpPco )
    {
        if (0 != pstMsgIE->stPcoInfo.ucIpv4PcscfNum)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            /* ��¼�޸ĺ��IPV4 P-CSCF��ַ���� */
            pstEpsbCntxtInfo->stPcoInfo.ucIpv4PcscfNum = pstMsgIE->stPcoInfo.ucIpv4PcscfNum;
            NAS_ESM_MEM_CPY(&pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[0],
                            &pstMsgIE->stPcoInfo.astIpv4Pcscf[0],
                            sizeof(NAS_ESM_IPV4_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM);

        }

        if (0 != pstMsgIE->stPcoInfo.ucIpv6PcscfNum)
        {
            pstEpsbCntxtInfo->bitOpPco = NAS_ESM_OP_TRUE;
            /* ��¼�޸ĺ��IPV6 P-CSCF��ַ���� */
            pstEpsbCntxtInfo->stPcoInfo.ucIpv6PcscfNum = pstMsgIE->stPcoInfo.ucIpv6PcscfNum;
            NAS_ESM_MEM_CPY(&pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[0],
                            &pstMsgIE->stPcoInfo.astIpv6Pcscf[0],
                            sizeof(NAS_ESM_IPV6_ADDR_STRU) * NAS_ESM_MAX_PCSCF_NUM);
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_DediBearActMsgManualProc
 Description     : ר�г��ؼ����ֶ�����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DediBearActMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU        stPdpManInd;
    VOS_UINT32                          ulRslt          = NAS_ESM_FAILURE;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DediBearActMsgManualProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ���ٿռ䣬���ڻ���������������Ϣ */
    pstStateAddr->pstDecodedNwMsg = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));

    if (VOS_NULL_PTR == pstStateAddr->pstDecodedNwMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_DediBearActMsgManualProc:ERROR:SM->APP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_NULL_PTR);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* ��������������Ϣ������������ */
    NAS_ESM_MEM_CPY(pstStateAddr->pstDecodedNwMsg,
                    pstDecodedNwMsg,
                    sizeof(NAS_ESM_NW_MSG_STRU));

    /* �����ʱ����stPdpManInd */
    NAS_ESM_MEM_SET(&stPdpManInd,
                     NAS_ESM_NULL,
                     sizeof(APP_ESM_PDP_MANAGER_IND_STRU));

    /* ��дר�г��ص�linkCid */
    stPdpManInd.bitOpLinkCid = NAS_ESM_OP_TRUE;
    ulRslt = NAS_ESM_QueryFirstSdfIdByEpsbId(pstDecodedNwMsg->ucLinkedEpsbId, &stPdpManInd.ulLinkCid);
    if(NAS_ESM_FAILURE == ulRslt)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_DediBearActMsgManualProc:ERROR:Can not find linkCid by linkEpsbId!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DediBearActMsgManualProc_ENUM, LNAS_FAIL);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    stPdpManInd.bitOpModifyTpye = NAS_ESM_OP_FALSE;

    /* ��дCID */
    stPdpManInd.ulCid = pstStateAddr->ulCid;

    /* ��дOpid, OriginalId��TerminalId*/
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        stPdpManInd.ulOpId = pstStateAddr->stAppMsgRecord.ulAppMsgOpId;
        stPdpManInd.usTerminalId = pstStateAddr->stAppMsgRecord.usOriginalId;
        stPdpManInd.usOriginalId = pstStateAddr->stAppMsgRecord.usTerminalId;
    }
    else
    {
        stPdpManInd.ulOpId = NAS_ESM_OPID_TYPE_MANAGER_IND;

        /* ���䱾�ι���APP_MSG_HEADER*/
        NAS_ESM_AssignMidHeader(&stPdpManInd.usOriginalId,&stPdpManInd.usTerminalId);
    }

    /* ��д�������� */
    stPdpManInd.enOperateType = APP_ESM_BEARER_OPERATE_TYPE_DEDI_ACT;

     /* ��APP����ID_APP_ESM_PDP_MANAGER_IND��Ϣ */
    NAS_ESM_SndEsmAppPdpManageIndMsg(&stPdpManInd);

    /* ������ʱ���ȴ�APP�ظ���Ϣ */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* ���õȴ�App�ظ���־λ */
    pstStateAddr->ucIsWaitForUserAnswer = PS_TRUE;
}





/*****************************************************************************
 Function Name   : NAS_ESM_DediBearActMsgAutoAccept
 Description     : �Զ�����ר�г��ؼ���Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact
    2.lihong00150010      2010-02-10 Modify

*****************************************************************************/
VOS_VOID NAS_ESM_DediBearActMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DediBearActMsgAutoAccept is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ����ר�г��ؼ������������Ϣ */
    NAS_ESM_SaveNwActDedictdEpsbReqInfo(pstDecodedNwMsg, ulStateTblIndex);

    /*������ظ�Activate dedicated bearer context accept*/
    NAS_ESM_EncodeActDedictdEpsbCntxtAccMsg(stEncodeInfo, \
                                    NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   &ulSndNwMsgLen);
    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,
                               NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                               ESM_ACT_DEDICT_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /*ת��״̬�����ó�������*/
    NAS_ESM_SetBearCntxtState(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
    NAS_ESM_SetBearCntxtType(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_TYPE_DEDICATED);
    NAS_ESM_SetBearCntxtLinkCid(stEncodeInfo.ulEpsbId,pstStateAddr->ulCid);

    /*�ؼ��¼��ϱ�*/
    NAS_ESM_SndKeyEventReportInd((OM_PS_KEY_EVENT_ENUM_UINT8)NAS_ESM_EVENT_BEARER_SETUP(stEncodeInfo.ulEpsbId));

    if (NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
    {
        if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
        {
            /*��APP����ID_APP_ESM_PDP_SETUP_CNF(�ɹ�)��Ϣ*/
            NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(ulStateTblIndex);

        }
        else
        {
            NAS_ESM_SndEsmAppSdfModCnfSuccMsg(ulStateTblIndex,
                                              APP_ESM_BEARER_MODIFY_TFT_QOS);

            NAS_ESM_SndEsmAppBearerQosIndMsg(stEncodeInfo.ulEpsbId);
        }

         /* ����PTI�ͻظ���Ϣ */
        ulRslt = NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                         (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DediBearActMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_FAIL, 1);
        }
    }
    else
    {
        /*��APP����APP_ESM_BEARER_SETUP_IND*/
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, APP_SUCCESS);
    }

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != stEncodeInfo.ucPti)
    {
         /* ����PTI�ͻظ���Ϣ */
        ulRslt = NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                         (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DediBearActMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DediBearActMsgAutoAccept_ENUM, LNAS_FAIL, 2);
        }
    }

    /*��EMM����ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /*��RABM����ID_ESM_ERABM_ACT_IND*/
    NAS_ESM_SndEsmRabmActIndMsg(stEncodeInfo.ulEpsbId);

    NAS_ESM_PrintEpsbInfo(stEncodeInfo.ulEpsbId);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    /* ֪ͨSM���ؼ��� */
    NAS_ESM_SndSmEspBearerActIndMsg(stEncodeInfo.ulEpsbId);

    /* PF���ȼ���ͻ���� */
    NAS_ESM_ProcPfPrecedenceCollision(pstDecodedNwMsg);
}


/*****************************************************************************
 Function Name   : NAS_ESM_BearModMsgManualProc
 Description     : �����޸��ֶ�����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_BearModMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU        stPdpManInd;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModMsgManualProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModMsgManualProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ���ٿռ䣬���ڻ���������������Ϣ */
    pstStateAddr->pstDecodedNwMsg = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));

    if (VOS_NULL_PTR == pstStateAddr->pstDecodedNwMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_BearModMsgManualProc:ERROR:SM->APP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_BearModMsgManualProc_ENUM, LNAS_NULL_PTR);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

    /* ��������������Ϣ������������ */
    NAS_ESM_MEM_CPY(pstStateAddr->pstDecodedNwMsg,
                    pstDecodedNwMsg,
                    sizeof(NAS_ESM_NW_MSG_STRU));

    /* �����ʱ����stPdpManInd */
    NAS_ESM_MEM_SET(&stPdpManInd,
                     NAS_ESM_NULL,
                     sizeof(APP_ESM_PDP_MANAGER_IND_STRU));

    stPdpManInd.bitOpLinkCid = NAS_ESM_OP_FALSE;

    /* ��д�����޸����� */
    stPdpManInd.bitOpModifyTpye = NAS_ESM_OP_TRUE;
    stPdpManInd.enBearerModifyType = NAS_ESM_GetBearModifyType(pstDecodedNwMsg);

    /* ��дCID */
    stPdpManInd.ulCid = pstStateAddr->ulCid;

    /* ��дOpid, OriginalId��TerminalId*/
    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstStateAddr->stNwMsgRecord.ucPti)
    {
        stPdpManInd.ulOpId = pstStateAddr->stAppMsgRecord.ulAppMsgOpId;
        stPdpManInd.usTerminalId = pstStateAddr->stAppMsgRecord.usOriginalId;
        stPdpManInd.usOriginalId = pstStateAddr->stAppMsgRecord.usTerminalId;
    }
    else
    {
        stPdpManInd.ulOpId = NAS_ESM_OPID_TYPE_MANAGER_IND;

        /* ���䱾�ι���APP_MSG_HEADER*/
        NAS_ESM_AssignMidHeader(&stPdpManInd.usOriginalId,&stPdpManInd.usTerminalId);
    }

    /* ��д�������� */
    stPdpManInd.enOperateType = APP_ESM_BEARER_OPERATE_TYPE_MODIFY;

     /* ��APP����ID_APP_ESM_PDP_MANAGER_IND��Ϣ */
    NAS_ESM_SndEsmAppPdpManageIndMsg(&stPdpManInd);

    /* ������ʱ���ȴ�APP�ظ���Ϣ */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* ���õȴ�App�ظ���־λ */
    pstStateAddr->ucIsWaitForUserAnswer = PS_TRUE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearModMsgAutoAccept
 Description     : �Զ����ܳ����޸ĵĴ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-12-3  Draft Enact
    2.lihong00150010        2010-02-10 Modify

*****************************************************************************/
VOS_VOID NAS_ESM_BearModMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    #endif

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModMsgAutoAccept is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModMsgAutoAccept_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ��������޸���Ϣ */
    NAS_ESM_SaveNwModEpsbReqInfo(pstDecodedNwMsg, ulStateTblIndex);

    /*������ظ�Modify EPS bearer context accept*/
    NAS_ESM_EncodeModEpsbCntxtAccMsg(&stEncodeInfo, \
                                     NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                    &ulSndNwMsgLen);

    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                               ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                               ESM_MOD_EPS_BEARER_CNTXT_ACP);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /* ��TAD��ΪNAS_ESM_TFT_OP_TYPE_ADD_FILTER������Ҫ���γɳ�����SDF�Ĺ�����ϵ��
       ���ϱ�APP,�������ϱ�APPʱ������ȷ��дlinkcid����TAD��ΪNAS_ESM_TFT_OP_TYPE_DELETE_FILTER
       ʱ���������ϱ�APP����ɾ��������SDF�Ĺ�����ϵ��,�������ϱ�APPʱ������ȷ��дlinkcid */
    if (NAS_ESM_TFT_OP_TYPE_DELETE_FILTER != pstDecodedNwMsg->stTadInfo.enTftOpType)
    {
        NAS_ESM_UpdateBearCntextLinkCid(pstDecodedNwMsg,
                                        stEncodeInfo.ulEpsbId,
                                        pstStateAddr->ulCid);
        NAS_ESM_InformAppEpsBearerModSucc(pstDecodedNwMsg, \
                                          ulStateTblIndex);
    }
    else
    {
        NAS_ESM_InformAppEpsBearerModSucc(pstDecodedNwMsg, \
                                          ulStateTblIndex);
        NAS_ESM_UpdateBearCntextLinkCid(pstDecodedNwMsg,
                                        stEncodeInfo.ulEpsbId,
                                        pstStateAddr->ulCid);
    }

    /*�ؼ��¼��ϱ�*/
    NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_MODIFY(stEncodeInfo.ulEpsbId));

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != stEncodeInfo.ucPti)
    {
        /* ����PTI�ͻظ���Ϣ */
        ulRslt= NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                        (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                        ulSndNwMsgLen,
                                        NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_BearModMsgAutoAccept:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BearModMsgAutoAccept_ENUM, LNAS_FAIL);
        }
    }
    /*leili modify for isr begin*/
    NAS_ESM_SndEsmEmmBearerModifyReq(stEncodeInfo.ulEpsbId);
    /*leili modify for isr end*/

    /*��RABM����ID_ESM_ERABM_MDF_IND*/
    if((NAS_ESM_OP_TRUE == pstDecodedNwMsg->bitOpTadInfo)
        && (NAS_ESM_TFT_OP_TYPE_NO_OP != pstDecodedNwMsg->stTadInfo.enTftOpType))
    {
        NAS_ESM_SndEsmRabmMdfIndMsg(stEncodeInfo.ulEpsbId);
    }

    NAS_ESM_PrintEpsbInfo(stEncodeInfo.ulEpsbId);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    NAS_ESM_SndSmEspBearerMdfIndMsg(stEncodeInfo.ulEpsbId);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(stEncodeInfo.ulEpsbId);

    /* �����ȱʡ���أ�֪ͨEHSM�����޸� */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(stEncodeInfo.ulEpsbId);
    }
    #endif

    /* PF���ȼ���ͻ���� */
    if (PS_TRUE == NAS_ESM_IsNeedPreferrenceCollision(pstDecodedNwMsg))
    {
        NAS_ESM_ProcPfPrecedenceCollision(pstDecodedNwMsg);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_ActDediBearFailProc
 Description     : ר�г��ؼ���ʧ�ܴ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact
    2.lihong00150010      2010-02-10 Modify

*****************************************************************************/
VOS_VOID  NAS_ESM_ActDediBearFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ActDediBearFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ActDediBearFailProc_ENUM, LNAS_ENTRY);

    if( NAS_ESM_CAUSE_ERROR != pstEncodeInfo->ucESMCau )
    {
        /*������ظ�Activate dedicated bearer context reject*/
        NAS_ESM_EncodeActDedictdEpsbCntxtRejMsg(*pstEncodeInfo, \
                                                NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                                &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),ulSndNwMsgLen,\
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
    }

    if (ulStateTblIndex == NAS_ESM_ILL_STATETAL_INDEX)
    {
        return ;
    }

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*��APP����SmAppCnf��Ϣ,*/
    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                                 NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));

        if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstEncodeInfo->ucPti)
        {
            /* ����PTI�ͻظ���Ϣ��������CAUSEԭ��ֵΪNAS_ESM_CAUSE_ERROR����� */
            ulRslt= NAS_ESM_SavePtiBuffItem(pstEncodeInfo->ucPti,
                                            (VOS_UINT8)pstEncodeInfo->ulEpsbId,
                                            ulSndNwMsgLen,
                                            NAS_ESM_GetCurEsmSndNwMsgAddr());
            if (ulRslt != NAS_ESM_SUCCESS)
            {
                NAS_ESM_WARN_LOG("NAS_ESM_ActDediBearFailProc:WARN:Save pti buffer item failed!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_ActDediBearFailProc_ENUM, LNAS_FAIL);
            }
        }
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_BearModFailProc
 Description     : �����޸�ʧ�ܴ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact
    2.lihong00150010      2010-02-10 Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_BearModFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_BearModFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModFailProc_ENUM, LNAS_ENTRY);

    if( NAS_ESM_CAUSE_ERROR != pstEncodeInfo->ucESMCau )
    {
        /*������ظ�Modify EPS bearer context reject*/
        NAS_ESM_EncodeModEpsbCntxtRejMsg(   *pstEncodeInfo, \
                                            NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                            &ulSndNwMsgLen);
        NAS_ESM_SndAirMsgReportInd(     NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                        ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                        ESM_MOD_EPS_BEARER_CNTXT_REJ);
        NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
        NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);
    }

    if (ulStateTblIndex == NAS_ESM_ILL_STATETAL_INDEX)
    {
        return ;
    }

    /* ����APP����������ظ�ʧ����Ϣ */
    NAS_ESM_InformAppEpsBearerModFail(ulStateTblIndex, pstEncodeInfo->ucESMCau);

    if (NAS_ESM_PTI_UNASSIGNED_VALUE != pstEncodeInfo->ucPti)
    {
        /* ����PTI�ͻظ���Ϣ��������CAUSEԭ��ֵΪNAS_ESM_CAUSE_ERROR����� */
        ulRslt = NAS_ESM_SavePtiBuffItem(pstEncodeInfo->ucPti,
                                         (VOS_UINT8)pstEncodeInfo->ulEpsbId,
                                         ulSndNwMsgLen,
                                         NAS_ESM_GetCurEsmSndNwMsgAddr());
        if (ulRslt != NAS_ESM_SUCCESS)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_BearModFailProc:WARN:Save pti buffer item failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_BearModFailProc_ENUM, LNAS_FAIL);
        }
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModEpsbNoTft
 Description     : ��������޸ļ������������Ϣ(NO TFT)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModEpsbNoTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModEpsbNoTft:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_BearModFailProc_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbAddPf
 Description     : ����ȱʡ�����޸ļ������������Ϣ(ADD PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* ��û���ҵ���ͬ������ӣ����ҵ���ͬ�����滻 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbAddPf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbAddPf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbReplacePf
 Description     : ����ȱʡ�����޸ļ������������Ϣ(REPLACE PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* ��û���ҵ���ͬ������ӣ����ҵ���ͬ�����滻 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReplacePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReplacePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbDeletePf
 Description     : ����ȱʡ�����޸ļ������������Ϣ(DELETE PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ɾ��SDF��������ָ����Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbDeletePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbDeletePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbNoOperation
 Description     : ����ȱʡ�����޸ļ������������Ϣ(NO OPERATION)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbNoOperation:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbNoOperation_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbCreateTft
 Description     : ����ȱʡ�����޸ļ������������Ϣ(CREATE TFT)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbCreateTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ����TFT */
    NAS_ESM_CreateTftProc(pstMsgIE, pstSdfCntxtInfo);

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbDeleteTft
 Description     : ����ȱʡ�����޸ļ������������Ϣ(DELETE TFT)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbDeleteTft
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;

    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    (VOS_VOID)(pstMsgIE);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ɾ��TFT */
    NAS_ESM_DeleteTftProc(pstSdfCntxtInfo);

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);
}
VOS_VOID NAS_ESM_SetAppPfId
(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara
)
{
    VOS_UINT32                          ulCnt = NAS_ESM_NULL;

    /* �жϳ��� */
    if (pstSdfPara->ulPfNum > NAS_ESM_MAX_SDF_PF_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_SetAppPfId:Pf Num is overflow!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SetAppPfId_ENUM, 1);

        return;
    }

    /* ѭ����ֵ */
    for (ulCnt = 0; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId
                   = pstSdfPara->astCntxtTftInfo[ulCnt].ucNwPacketFilterId;
    }

    return;
}



VOS_UINT32 NAS_ESM_IsExistlinkedPfInSdfCntxt( VOS_UINT32 ulCid,VOS_UINT32 ulSdfParaPfId )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT32                          ulCnt;

    pstSdfCntxtInfo    = NAS_ESM_GetSdfCntxtInfo(ulCid);

    for(ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId == ulSdfParaPfId)
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}


VOS_UINT8 NAS_ESM_GetAppPfId( VOS_UINT32 ulCid )
{
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    VOS_UINT8                           ucCnt;
    VOS_UINT32                          ulDynCnt;

    pstSdfCntxtInfo    = NAS_ESM_GetSdfCntxtInfo(ulCid);

    for (ucCnt = 1; ucCnt <= NAS_ESM_MAX_SDF_PF_NUM; ucCnt++)
    {
        for (ulDynCnt = 0; ulDynCnt < pstSdfCntxtInfo->ulSdfPfNum; ulDynCnt++)
        {
            if (pstSdfCntxtInfo->astSdfPfInfo[ulDynCnt].ucPacketFilterId == ucCnt)
            {
                break;
            }
        }

        if (ulDynCnt >= pstSdfCntxtInfo->ulSdfPfNum)
        {
            return ucCnt;
        }
    }

    return NAS_ESM_NULL;
}



VOS_VOID NAS_ESM_ModulateSdfTft
(
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;
    VOS_UINT8                           ucAppPfId           = NAS_ESM_NULL;
    VOS_UINT32                          ulDynNum            = NAS_ESM_NULL;
    VOS_UINT32                          ulStaNum            = NAS_ESM_NULL;
    VOS_UINT32                          aulDynPfId[NAS_ESM_MAX_SDF_PF_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                          aulStaPfId[NAS_ESM_MAX_SDF_PF_NUM] = {NAS_ESM_NULL};
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulLoopTimes         = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt              = PS_FALSE;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstSdfPara       = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* ���Ҷ�̬��Ϣ�����AppPfIdΪ0����Ϊ��δ�󶨵�SDF,���붯̬������ */
    for (ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (NAS_ESM_NULL == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId)
        {
            aulDynPfId[ulDynNum++] = ulCnt;
        }
    }

    /* �������о�̬��Ϣ�����AppPfId�޷��ڶ�̬��Ϣ���ҵ����ʾ�˾�̬��Ϣû�ж�̬
    ��Ϣ���� */
    for (ulCnt = 0; ulCnt < pstSdfPara->ulPfNum; ulCnt++)
    {
        ulRslt =  NAS_ESM_IsExistlinkedPfInSdfCntxt(pstStateAddr->ulCid,
                                                    pstSdfPara->astCntxtTftInfo[ulCnt].ucPacketFilterId);
        if (ulRslt == PS_FALSE)
        {
            aulStaPfId[ulStaNum++] = ulCnt;
        }
    }

    /* �����̬PfId�ȶ�̬�Ķ࣬��ֻ��Ҫ��֤ÿ����̬��Ϣ���о�̬��PfId�������� */
    ulLoopTimes     = NAS_ESM_MIN(ulDynNum, ulStaNum);

    for (ulCnt = NAS_ESM_NULL; ulCnt < ulLoopTimes; ulCnt++)
    {
        pstSdfCntxtInfo->astSdfPfInfo[aulDynPfId[ulCnt]].ucPacketFilterId =
                        pstSdfPara->astCntxtTftInfo[aulStaPfId[ulCnt]].ucPacketFilterId;
    }

    /* �����̬��Ϣ�Ⱦ�̬��Ϣ�࣬��������û�й����Ķ�̬PfId,��δʹ�õľ�̬PfId����������
    ������̬��Ϣ��������̬��Ϣ�� */
    for (ulCnt = 0; ulCnt < pstSdfCntxtInfo->ulSdfPfNum; ulCnt++)
    {
        if (NAS_ESM_NULL == pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId)
        {
            /* ��ȡһ��û��ʹ�õľ�̬PfId */
            ucAppPfId = NAS_ESM_GetAppPfId(pstStateAddr->ulCid);
            if (NAS_ESM_NULL == ucAppPfId)
            {
                NAS_ESM_ERR_LOG("NAS_ESM_ModulateSdfTft: Get App PfId Failed.");
                TLPS_PRINT2LAYER_ERROR(NAS_ESM_ModulateSdfTft_ENUM, LNAS_FAIL);

                return;
            }

            /* ���õ�ǰPF��APP PF IDΪulAppPfId */
            pstSdfCntxtInfo->astSdfPfInfo[ulCnt].ucPacketFilterId = ucAppPfId;

            /* ������ǰPF��SDF�ľ�̬��Ϣ�У���̬��Ϣ��PF����1 */
            NAS_ESM_MEM_CPY( &(pstSdfPara->astCntxtTftInfo[pstSdfPara->ulPfNum]),
                             &(pstSdfCntxtInfo->astSdfPfInfo[ulCnt]),
                             sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstSdfPara->ulPfNum++;
        }
    }

}
VOS_VOID NAS_ESM_ModulateSdfQos
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstSdfPara       = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* �����̬��Ϣ��û��Qci��Ϣ���򽫶�̬��Ϣ��������̬��Ϣ�� */
    if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos)
    {
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY( &(pstSdfPara->stSdfQosInfo),
                         &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo),
                         sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbAddPf
 Description     : ����ר�г����޸ļ������������Ϣ(ADD PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbAddPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo     = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    pstStateAddr     = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo  = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ���տ���Ϣ��Я����Ԥ��ӵ�packet filter�ڳ�������ȫ�����ڻ򲿷ִ���,
       ���Ѵ��ڵ�packet filter������sdf�붯̬���д洢���û�Ԥ������sdf��һ�£�
       ��ɾ���Ѵ��ڵ�packet filter������sdf�����³���QOS��Ϣ */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModDediEpsbAddPf:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbAddPf_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* ɾ����SDF������ */
        NAS_ESM_MEM_SET(pstSdfCntxtInfoTmp, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* �ϱ�APP SDF�ͷ� */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* ������ع����Ĵ�CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }

    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* �����ר�г��أ��ҵ�ǰSDF��PF��Ϊ0,��˵���˴β���Ϊ���SDF����˽��ϱ�
       �����޸�ΪNAS_ESM_APP_IND_TYPE_SETUP */
    if ((NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
        && (NAS_ESM_BEARER_TYPE_DEDICATED == pstEpsbCntxtInfo->enBearerCntxtType))
    {
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_SETUP;
    }

    /* ��û���ҵ���ͬ������ӣ����ҵ���ͬ�����滻 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* �����̬�Ͷ�̬��Ϣ��һ�£�����е��� */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* ����NON-GBR���أ����յ�����ĳ����޸�����TAD��ΪADD SDF���Ҳ���QOS��Ϣʱ,
           ������QOS��Ϣ�е�QCI��ֵ������SDF��QCI*/
        if (PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            NAS_ESM_MEM_SET(&pstSdfCntxtInfo->stSdfQosInfo,
                            NAS_ESM_NULL,
                            sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* ����SDF��QCI��Ϣ */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbReplacePf
 Description     : ����ר�г����޸ļ������������Ϣ(Replace PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbReplacePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* ��û���ҵ���ͬ������ӣ����ҵ���ͬ�����滻 */
    NAS_ESM_ReplacePacketFilterProc(pstMsgIE, pstSdfCntxtInfo);

    /* �����̬�Ͷ�̬��Ϣ��һ�£�����е��� */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReplacePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReplacePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}


VOS_VOID  NAS_ESM_SaveNwModDediEpsbCreatPf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{   VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    VOS_UINT32                          ulCidTmp            = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfoTmp  = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo       = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo       = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ���տ���Ϣ��Я����Ԥ��ӵ�packet filter�ڳ�������ȫ�����ڻ򲿷ִ���,
       ���Ѵ��ڵ�packet filter������sdf�붯̬���д洢���û�Ԥ������sdf��һ�£�
       ��ɾ���Ѵ��ڵ�packet filter������sdf�����³���QOS��Ϣ */
    ulRslt = NAS_ESM_QuerySdfId(pstMsgIE, &ulCidTmp);
    if((NAS_ESM_QUERY_CID_RSLT_ALL_UNFOUND != ulRslt)
        && (ulCidTmp != pstStateAddr->ulCid))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_SaveNwModDediEpsbCreatPf:packet filter already exist in other sdf!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbCreatPf_ENUM, ESM_packet_filter_already_exist_in_other_sdf);

        pstSdfCntxtInfoTmp = NAS_ESM_GetSdfCntxtInfo(ulCidTmp);

        pstEpsQosInfo = &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo;
        pstSdfQosInfo = &pstSdfCntxtInfoTmp->stSdfQosInfo.stQosInfo;

        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsQosInfo->ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* ɾ����SDF������ */
        NAS_ESM_MEM_SET(pstSdfCntxtInfoTmp, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        /* �ϱ�APP SDF�ͷ� */
        NAS_ESM_SndEsmAppSdfRelIndMsg(ulCidTmp, pstMsgIE->ucEpsbId);

        /* ������ع����Ĵ�CID */
        NAS_ESM_ClearBearCntxtLinkCid(pstMsgIE->ucEpsbId, ulCidTmp);
    }


    /* ��ֵSDF�����ĳ�����Ϣ */
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    /* ɾ���ɵ�TFT��Ϣ */
    NAS_ESM_MEM_SET(pstSdfCntxtInfo->astSdfPfInfo,\
                    NAS_ESM_NULL,\
                    sizeof(NAS_ESM_CONTEXT_TFT_STRU) * NAS_ESM_MAX_SDF_PF_NUM);
    pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;

    /* ����µ�TFT��Ϣ */
    NAS_ESM_MEM_CPY(pstSdfCntxtInfo->astSdfPfInfo,\
                    pstMsgIE->stTadInfo.astSdfPfInfo,\
                    sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstMsgIE->stTadInfo.ucSdfPfNum);
    pstSdfCntxtInfo->ulSdfPfNum = pstMsgIE->stTadInfo.ucSdfPfNum;

    /* �����̬�Ͷ�̬��Ϣ��һ�£�����е��� */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);


    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        /* ����NON-GBR���أ����յ�����ĳ����޸�����TAD��ΪCREAT SDF���Ҳ���QOS��Ϣʱ,
           ������QOS��Ϣ�е�QCI��ֵ������SDF��QCI*/
        if (PS_FALSE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            NAS_ESM_MEM_SET(&pstSdfCntxtInfo->stSdfQosInfo,
                            NAS_ESM_NULL,
                            sizeof (NAS_ESM_CONTEXT_LTE_QOS_STRU));

            /* ����SDF��QCI��Ϣ */
            pstSdfCntxtInfo->stSdfQosInfo.stQosInfo.ucQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI;

            pstSdfCntxtInfo->stSdfQosInfo.ucNwQCI =
                        pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

        }

        return ;
    }


    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbDeletePf
 Description     : ����ר�г����޸ļ������������Ϣ(DELETE PF)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbDeletePf
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    VOS_UINT32                          ulCnt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstEpsQosInfo   = VOS_NULL_PTR;
    APP_ESM_EPS_QOS_INFO_STRU          *pstSdfQosInfo   = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    pstEpsQosInfo = &(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo);

    pstSdfQosInfo = &(pstSdfCntxtInfo->stSdfQosInfo.stQosInfo);

    /* ɾ��SDF��������ָ����Pakketfilter */
    for (ulCnt = 0; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ulCnt++)
    {
        NAS_ESM_DeleteOnePacketFilter(pstSdfCntxtInfo,
                                      pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt].ucNwPacketFilterId);
    }

    /* ����ר�г��أ��Ҵ�SDF��packet filter��ȫ��ɾ������ɾ����SDF */
    if (NAS_ESM_NULL == pstSdfCntxtInfo->ulSdfPfNum)
    {
        if (PS_TRUE == NAS_ESM_IsGbrBearer(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo.ucQCI))
        {
            pstEpsQosInfo->ulULMaxRate -= pstSdfQosInfo->ulULMaxRate;
            pstEpsQosInfo->ulDLMaxRate -= pstSdfQosInfo->ulDLMaxRate;
            pstEpsQosInfo->ulULGMaxRate -= pstSdfQosInfo->ulULGMaxRate;
            pstEpsQosInfo->ulDLGMaxRate -= pstSdfQosInfo->ulDLGMaxRate;
        }

        /* �޸��ϱ�����ΪNAS_ESM_APP_IND_TYPE_RELEASE */
        pstStateAddr->enAppIndType = NAS_ESM_APP_IND_TYPE_RELEASE;

        /* ɾ��SDF������ */
        NAS_ESM_MEM_SET(pstSdfCntxtInfo, 0, sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));

        return ;
    }

    /* �����̬�Ͷ�̬��Ϣ��һ�£�����е��� */
    NAS_ESM_ModulateSdfTft(ulStateTblIndex);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbDeletePf:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbDeletePf_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}
/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbNoOperation
 Description     : ����ר�г����޸ļ������������Ϣ(NO OPERATION)
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbNoOperation
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo  = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* �������QOS */
    if( NAS_ESM_OP_TRUE != pstMsgIE->bitOpEpsQos)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbNoOperation:No Qos Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbNoOperation_ENUM, ESM_NO_QOS_INFO);
        return ;
    }

    NAS_ESM_UpdateEpsQosInfo(pstMsgIE, pstEpsbCntxtInfo, pstSdfCntxtInfo);

    NAS_ESM_ModulateSdfQos(ulStateTblIndex);
}


/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDeftEpsbReqInfo
 Description     : ����ȱʡ�����޸ļ������������Ϣ
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDeftEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    /* ���û��TFT��Ϣ�� �����NAS_ESM_SaveNwModDeftEpsbNoTft */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:No TFT Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_NO_TFT_INFO);
        NAS_ESM_SaveNwModEpsbNoTft(pstMsgIE, ulStateTblIndex);

        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:ADD PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_ADD_PF);
            NAS_ESM_SaveNwModDeftEpsbAddPf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:REPLACE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_REPLACE_PF);
            NAS_ESM_SaveNwModDeftEpsbReplacePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:DELETE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_DELETE_PF);
            NAS_ESM_SaveNwModDeftEpsbDeletePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_NO_OP:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:NO OPERATION!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_NO_OPERATION);
            NAS_ESM_SaveNwModDeftEpsbNoOperation(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:CRREATE TFT!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_CREATE_TFT);
            NAS_ESM_SaveNwModDeftEpsbCreateTft(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:DELETE TFT!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, ESM_DELETE_TFT);
            NAS_ESM_SaveNwModDeftEpsbDeleteTft(pstMsgIE, ulStateTblIndex);
            break;

       default:
            NAS_ESM_WARN_LOG("NAS_ESM_SaveNwModDeftEpsbReqInfo:illegal tad!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SaveNwModDeftEpsbReqInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwModDediEpsbReqInfo
 Description     : ����ר�г����޸ļ������������Ϣ
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-06-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SaveNwModDediEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    /* ���û��TFT��Ϣ�� �����NAS_ESM_SaveNwModEpsbNoTft */
    if(NAS_ESM_OP_TRUE != pstMsgIE->bitOpTadInfo)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:No TFT Info!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_NO_TFT_INFO);
        NAS_ESM_SaveNwModEpsbNoTft(pstMsgIE, ulStateTblIndex);

        return ;
    }

    switch (pstMsgIE->stTadInfo.enTftOpType)
    {
        case NAS_ESM_TFT_OP_TYPE_ADD_FILTER :
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:ADD PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_ADD_PF);
            NAS_ESM_SaveNwModDediEpsbAddPf(pstMsgIE, ulStateTblIndex);
            break;
        case NAS_ESM_TFT_OP_TYPE_CREATE_TFT:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:CREAT PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_CREATE_TFT);
            NAS_ESM_SaveNwModDediEpsbCreatPf(pstMsgIE, ulStateTblIndex);
            break;
        case NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:REPLACE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_REPLACE_PF);
            NAS_ESM_SaveNwModDediEpsbReplacePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_DELETE_FILTER:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:DELETE PF!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_DELETE_PF);
            NAS_ESM_SaveNwModDediEpsbDeletePf(pstMsgIE, ulStateTblIndex);
            break;

        case NAS_ESM_TFT_OP_TYPE_NO_OP:
            NAS_ESM_NORM_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:NO OPERATION!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, ESM_NO_OPERATION);
            NAS_ESM_SaveNwModDediEpsbNoOperation(pstMsgIE, ulStateTblIndex);
            break;

       default:
            NAS_ESM_WARN_LOG("NAS_ESM_SaveNwModDediEpsbReqInfo:illegal tad!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_SaveNwModDediEpsbReqInfo_ENUM, LNAS_PARAM_INVALID);
            break;
    }
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmNwMsgBearerResAllocProc.c */
