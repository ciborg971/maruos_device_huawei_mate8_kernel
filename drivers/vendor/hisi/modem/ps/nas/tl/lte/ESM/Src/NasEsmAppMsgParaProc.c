

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMAPPMSGPARAPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMAPPMSGPARAPROC_C
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

VOS_VOID NAS_ESM_AppParaSetMsgProc( VOS_VOID *pRcvMsg )
{
    APP_PS_MSG_HEADER_STRU   *pAppMsg    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ���ͣ�������Ӧ�Ĳ������ú���*/
    switch (pAppMsg->ulMsgId)
    {
        case ID_APP_ESM_SET_TFT_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetTft(pRcvMsg);
            break;

        case ID_APP_ESM_SET_EPS_QOS_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetSdfQos(pRcvMsg);
            break;

        case ID_APP_ESM_SET_APN_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetApn(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PCO_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetPco(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PDN_TYPE_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetPdnType(pRcvMsg);
            break;

        case ID_APP_ESM_SET_BEARER_TYPE_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetBearType(pRcvMsg);
            break;

        case ID_APP_ESM_SET_PDP_MANAGER_TYPE_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetPdpManagType(pRcvMsg);
            break;
        case ID_APP_ESM_SET_GW_AUTH_REQ:

            /*���ò������ú���*/
            NAS_ESM_AppParaSetGwAuthInfo(pRcvMsg);
            break;
        case ID_APP_ESM_SET_CGDCONT_REQ:

            NAS_ESM_AppSetCgdcont(pRcvMsg);
            break;
        default:
            /*��ӡ�յ��쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetMsgProc:WARNING:APP->SM ,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetMsgProc_ENUM, LNAS_MSG_INVALID);
            break;
    }

}
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_AppParaSetCnf( const NAS_ESM_APP_PARA_SET_RESLT_STRU *pstParaInfo)
{
    APP_ESM_PARA_SET_CNF_STRU   *pSmAppSetRslt   =VOS_NULL_PTR;
    VOS_UINT32                  ulCid           =0;


    /*��ȡ���ݲ����е�ulCid����*/
    ulCid = pstParaInfo->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pSmAppSetRslt = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PARA_SET_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pSmAppSetRslt)
    {
         /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaSetCnf:ERROR:SM->APP Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaSetCnf_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pSmAppSetRslt), 0, NAS_ESM_GET_MSG_LENGTH(pSmAppSetRslt));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pSmAppSetRslt,pstParaInfo->ulMsgId,\
                              pstParaInfo->usOriginalId,pstParaInfo->usTerminalId,\
                              pstParaInfo->ulSn);

    /*��װ��Ϣ����*/
    pSmAppSetRslt->ulOpId = pstParaInfo->ulOpId;
    pSmAppSetRslt->ulCid = ulCid;
    pSmAppSetRslt->ulSetRslt = pstParaInfo->ulSetRslt;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pSmAppSetRslt);

}


VOS_UINT32  NAS_ESM_CheckAppTftOperation
(
    const APP_ESM_SET_TFT_REQ_STRU     *pAppTftMsg
)
{
    VOS_UINT32                          ulIsSdfActive       = NAS_ESM_FAILURE;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    VOS_UINT32                          ulPfIdx             = NAS_ESM_NULL;
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulCnt1              = NAS_ESM_NULL;
    VOS_UINT32                          ulPfId              = NAS_ESM_NULL;
    VOS_UINT8                           ucSdfPrecedence     = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppTftMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppTftOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* ���������У��������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppTftMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppTftOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppTftOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* �ж�SDF�Ƿ��Ѽ��� */
    ulIsSdfActive = NAS_ESM_QueryEpsbCntxtTblByCid(pAppTftMsg->ulCid, &ulEpsbId);

    /* ��������Ϊɾ������� */
    if (pAppTftMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /* ����SDF�Ѽ��������ɾ��QOS��Ϣ */
        if (NAS_ESM_SUCCESS == ulIsSdfActive)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Tft can not be deleted cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckAppTftOperation_ENUM, ESM_SDF_IS_ACTIVE, 1);
            return NAS_ESM_FAILURE;
        }

        return NAS_ESM_SUCCESS;
    }

    /* �ж�TFT�����������Ч��*/
    if (NAS_ESM_FAILURE == NAS_ESM_IsTftInfoValid(&pAppTftMsg->stAppTftInfo))
    {
        return NAS_ESM_FAILURE;
    }

    /* �жϱ���TFT��������Ч�� */
    pstSdfPara = NAS_ESM_GetSdfParaAddr(pAppTftMsg->ulCid);

    /* ͬһ��Cid��,���ȼ�������ͬ*/
    for (ulCnt1 = NAS_ESM_NULL; ulCnt1 < pstSdfPara->ulPfNum; ulCnt1++)
    {
        ucSdfPrecedence = pstSdfPara->astCntxtTftInfo[ulCnt1].ucPrecedence;
        ulPfId          = pstSdfPara->astCntxtTftInfo[ulCnt1].ucPacketFilterId;

        /* �����ͬһ��Packetfilter������ͬ�����ȼ�*/
        if ((ucSdfPrecedence == pAppTftMsg->stAppTftInfo.ucPrecedence)
         && (ulPfId != pAppTftMsg->stAppTftInfo.ucPacketFilterId))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Pf precedence error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppTftOperation_ENUM, 1);
            return NAS_ESM_FAILURE;
        }
    }

    /* ����ָ��PF ID */
    if (NAS_ESM_FAILURE == NAS_ESM_QueryPfInTft(pAppTftMsg->stAppTftInfo.ucPacketFilterId,
                                                pstSdfPara->astCntxtTftInfo,
                                                pstSdfPara->ulPfNum,
                                               &ulPfIdx))
    {
        /* ��ָ��PF�����ڣ��Ҵ�SDF�Ѽ������PF���������򷵻����ô��� */
        if ((NAS_ESM_SUCCESS == ulIsSdfActive)
         || (pstSdfPara->ulPfNum >= NAS_ESM_MAX_SDF_PF_NUM))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppTftOperation:Pf can not be added cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckAppTftOperation_ENUM, ESM_SDF_IS_ACTIVE, 2);

            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppQosOperation
(
    const APP_ESM_SET_QOS_REQ_STRU           *pAppQosMsg
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppQosMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* ���������У��������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppQosMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* �Ѿ���������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(pAppQosMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppQosOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppQosOperation_ENUM, ESM_CID_IS_ACTIVE);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppSdfQosOperation
(
    const APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg
)
{
    VOS_UINT32                          ulEpsbId        = NAS_ESM_NULL;
    VOS_UINT32                          ulIsSdfActive   = NAS_ESM_FAILURE;
    VOS_UINT32                          ulStateId       = NAS_ESM_ILL_STATETAL_INDEX;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppSdfQosMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppSdfQosOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* ���������У��������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppSdfQosMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppSdfQosOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* �ж�SDF�Ƿ��Ѽ��� */
    ulIsSdfActive = NAS_ESM_QueryEpsbCntxtTblByCid(pAppSdfQosMsg->ulCid, &ulEpsbId);

    /* ��������Ϊɾ������� */
    if (pAppSdfQosMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /* ����SDF�Ѽ��������ɾ��QOS��Ϣ */
        if (NAS_ESM_SUCCESS == ulIsSdfActive)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppSdfQosOperation:Qos can not be deleted cause the sdf is active!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppSdfQosOperation_ENUM, ESM_SDF_IS_ACTIVE);

            return NAS_ESM_FAILURE;
        }

        return NAS_ESM_SUCCESS;
    }

    /* ��������Ϊ���õ���� */
    /* �ж�SDF Qos�����������Ч��*/
    if (NAS_ESM_FAILURE == NAS_ESM_IsSdfQosValid(&pAppSdfQosMsg->stSdfQosInfo))
    {
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppApnOperation
(
    VOS_UINT32                          ulCid
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*����CID�����Ƿ�Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* ���������У��������޸� */
    /* Э����û��Ҫ��Բ��������л����Ѿ������SDF�����޸��侲̬���ԣ�����ȡ����ԭ���������޸ĵ����� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,change is allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppApnOperation:APP->SM ,change is allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppApnOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    return APP_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppPcoOperation
(
    const APP_ESM_SET_PCO_REQ_STRU           *pAppPcoMsg
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppPcoMsg->ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* ���������У��������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pAppPcoMsg->ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_IS_OPERATING);
        return NAS_ESM_FAILURE;
    }

    /* �Ѿ���������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(pAppPcoMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPcoOperation_ENUM, ESM_CID_IS_ACTIVE);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppPdnTypeOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpIpv4AddrAllocType,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*����CID�����Ƿ�Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* ���������У��������޸� */
    /* Э����û��Ҫ��Բ��������л����Ѿ������SDF�����޸��侲̬���ԣ�����ȡ����ԭ���������޸ĵ����� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    /* �Ѿ����������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppPcoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    /* ��������Ϊɾ������� */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }

    if ((enPdnType >= APP_ESM_PDN_TYPE_BUTT)
      ||(enPdnType == NAS_ESM_NULL))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,Pdn type error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, ESM_PDN_TYPE_ERROR);
        return APP_ERR_SM_PDN_TYPE_ILLEGAL;
    }

    if (NAS_ESM_OP_TRUE == bitOpIpv4AddrAllocType)
    {
        if (enIpv4AddrAllocType >= APP_ESM_IPV4_ADDR_ALLOC_TYPE_BUTT)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdnTypeOperation:APP->SM ,IP address allocate type error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdnTypeOperation_ENUM, 1);
            return APP_ERR_SM_IPV4_ADDR_ALLOC_TYPE_ILLEGAL;
        }
    }
    return APP_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsTheOnlyOneDefltBearTypeSdf
 Description     : ��CID0-CID10֮�䣬�ж�ָ��CID�Ƿ���Ψһ�ĳ�������Ϊȱʡ��
                   SDF
 Input           : ulCid-------------------------CID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-8-12  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsTheOnlyOneDefltBearTypeSdf
(
     VOS_UINT32                         ulCid
)
{
    VOS_UINT32                          ulCnt                   = NAS_ESM_NULL;
    VOS_UINT32                          ulDefltBearTypeSdfNum   = NAS_ESM_NULL;
    VOS_UINT32                          ulFindCid               = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara              = VOS_NULL_PTR;

    /* ������ulCid��λ��[0,10]����ֱ�ӷ��� */
    if (ulCid >= NAS_ESM_MAX_EPSB_NUM)
    {
        return PS_FALSE;
    }

    /* ����CID0-CID10����¼��������Ϊȱʡ��SDF�������Լ����һ����������Ϊȱʡ��
       SDF��Ӧ��CID�� */
    for (ulCnt = NAS_ESM_NULL; ulCnt < NAS_ESM_MAX_EPSB_NUM; ulCnt++)
    {
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCnt);

        if (NAS_ESM_BEARER_TYPE_DEFAULT == pstSdfPara->enBearerCntxtType)
        {
            ulDefltBearTypeSdfNum++;
            ulFindCid = ulCnt;
        }
    }

    if (ulDefltBearTypeSdfNum == NAS_ESM_NULL)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_IsTheOnlyOneDefltBearTypeSdf:Default Bearer Type sdf number is 0");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_IsTheOnlyOneDefltBearTypeSdf_ENUM, 1);
    }

    /* ��CID0-CID10�У����ulCidָ��SDF�Ƿ���Ψһ�ĳ�������Ϊȱʡ��SDF��������
       ����PS_TRUE�������ǣ��򷵻�PS_FALSE */
    if ((ulDefltBearTypeSdfNum == NAS_ESM_DEFAULT_BEARER_TYPE_SDF_NUM_ONE)
         && (ulCid == ulFindCid))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}


VOS_UINT32  NAS_ESM_CheckAppBearTypeOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType,
    VOS_UINT32                          bitOpLinkdCid,
    VOS_UINT32                          ulLinkdCid
)
{
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*����CID�����Ƿ�Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }


    /* ������β���Ҫ�޸ĵ������뱾���Ѿ��洢��������ͬ���������ȱʡ���ͣ����β���Ҫ�޸ĳɵĳ���������
       ���ش洢����ͬ�����������ר�г������ͣ����β���Ҫ�޸ĳɵĳ������ͺ͹���CID��Ϣ�뱾�ش洢�Ķ���ͬ��
       ��ֱ�ӷ����ɹ��������޸ģ�������β���Ҫ�޸ĳɵ������뱾���Ѵ洢�����ݲ�ͬ�������ڲ��������л����Ѽ��
       �������޸�*/

    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);
    /*��������û�б仯*/
    if(pstSdfPara->enBearerCntxtType == enBearCidType)
    {
        /*ȱʡ����*/
        if(pstSdfPara->enBearerCntxtType != APP_ESM_CID_TYPE_DEDICATED)
        {
            return APP_SUCCESS;
        }

        if ((NAS_ESM_OP_TRUE== bitOpLinkdCid)
             &&(pstSdfPara->ulLinkdCId == ulLinkdCid))
        {
            return APP_SUCCESS;
        }
    }


    /*  ���������� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_IS_OPERATING);
        return APP_ERR_SM_CALL_CID_IN_OPERATION;
    }

    /* �Ѿ���������޸� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_IS_ACTIVE);
        return APP_ERR_SM_CALL_CID_ACTIVE;
    }

    /* ��������Ϊɾ������� */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }

    if (enBearCidType >= APP_ESM_CID_TYPE_BUTT)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,bearer type error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_TYPE_ERROR);
        return APP_ERR_SM_BEARER_TYPE_ILLEGAL;
    }

    if(APP_ESM_CID_TYPE_DEDICATED == enBearCidType)
    {
        /* ���û������LinkCid���򷵻�����ʧ�� */
        if ((NAS_ESM_OP_FALSE == bitOpLinkdCid)
         || (ulLinkdCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,required LinkCid or LinkeCid error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_CID_ERROR);
            return APP_ERR_SM_LINK_CID_INVALID;
        }

        /* ����û���������û����CID0-CID10��û��ȱʡ�������͵�SDF���򷵻����ô��� */
        if (PS_TRUE == NAS_ESM_IsTheOnlyOneDefltBearTypeSdf(ulCid))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,this sdf is the only one which is default bearer type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, ESM_SDF_ERROR);
            return APP_ERR_SM_MUST_EXIST_DEFAULT_TYPE_CID;
        }

        /* �����ר�г��ض�Ӧ��linked��������Ϊ�������ͣ��򷵻�����ʧ�� */
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulLinkdCid);
        if (APP_ESM_BEARER_TYPE_EMERGENCY == pstSdfPara->enBearerCntxtType)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_CheckAppBearTypeOperation:APP->SM ,not allow dedicated bearer type for emergency bearer");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppBearTypeOperation_ENUM, 1);
            return APP_ERR_SM_DEDICATED_FOR_EMERGENCY_NOT_ALLOWED;
        }
    }

    return APP_SUCCESS;
}

VOS_UINT32  NAS_ESM_CheckAppPdpManagTypeOperation
(
    const APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU *pAppBearManagTypeMsg
)
{
    if (pAppBearManagTypeMsg->enSetType != APP_ESM_PARA_SETTING)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdpManagTypeOperation:APP->SM ,Pdp manage type can not be del!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdpManagTypeOperation_ENUM, 1);
        return NAS_ESM_FAILURE;
    }

    if ((pAppBearManagTypeMsg->enAnsMode >= APP_ESM_ANSWER_MODE_BUTT)
      ||(pAppBearManagTypeMsg->enAnsType >= APP_ESM_ANSWER_RESULT_BUTT))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppPdpManagTypeOperation:APP->SM ,Pdp Manage Type Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppPdpManagTypeOperation_ENUM, 2);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}
VOS_UINT32  NAS_ESM_CheckAppGwAuthInfoOperation
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_GW_AUTH_INFO_STRU           *pstGwAuthInfo
)
{
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulStateId           = NAS_ESM_ILL_STATETAL_INDEX;
    VOS_UINT32                          ulEpsbId            = NAS_ESM_NULL;

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*����CID�����Ƿ�Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_ERROR);
        return APP_ERR_SM_CALL_CID_INVALID;
    }

    /* ���������У��������޸� */
    /* Э����û��Ҫ��Բ��������л����Ѿ������SDF�����޸��侲̬���ԣ�����ȡ����ԭ���������޸ĵ����� */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(ulCid,&ulStateId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,change is not allowed when cid is operating!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_IS_OPERATING);
    }

    if (NAS_ESM_SUCCESS == NAS_ESM_QueryEpsbCntxtTblByCid(ulCid,&ulEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->SM ,change is not allowed when cid is active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_CID_IS_ACTIVE);
    }

    /* ��������Ϊɾ������� */
    if (enSetType != APP_ESM_PARA_SETTING)
    {
        return APP_SUCCESS;
    }


    /* ���ü�Ȩ��Ϣǰ���û�����������APN��Ϣ����û��,����ʾû������APN*/
    if (pstSdfPara->bitOpApn == NAS_ESM_OP_FALSE)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_CheckAppGwAuthInfoOperation:APP->ESM ,no apn info!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckAppGwAuthInfoOperation_ENUM, ESM_APN_ERROR);
    }
    return NAS_ESM_IsGwAuthInfoValid(pstGwAuthInfo);
}

VOS_VOID NAS_ESM_AppParaSetTft( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid            =0;
    VOS_UINT32                          ulTftIdx         = NAS_ESM_NULL;
    VOS_UINT8                           ucPacketFilterID = NAS_ESM_NULL;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType        =0;
    APP_ESM_SET_TFT_REQ_STRU           *pAppTftMsg       =VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara       =VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetTft is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetTft_ENUM, LNAS_ENTRY);

    pAppTftMsg = (APP_ESM_SET_TFT_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid*/
    ulCid = pAppTftMsg->ulCid;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_TFT_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/
    enSetType = pAppTftMsg->enSetType;

    /* ���App���õ�TFT��Ϣ */
    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppTftOperation(pAppTftMsg))
    {
        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*����ulCid��ɾ��������Ӧ�ṹ�е�TFT��Ϣ*/
        pstSdfPara->ulPfNum = NAS_ESM_NULL;

        NAS_ESM_MEM_SET((VOS_VOID *)(pstSdfPara->astCntxtTftInfo),
                         VOS_NULL,
                         sizeof(APP_ESM_TFT_INFO_STRU) * NAS_ESM_MAX_SDF_PF_NUM);

        /*��APP��������ȷ��*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    ucPacketFilterID = pAppTftMsg->stAppTftInfo.ucPacketFilterId;

    /* ����Ԥ��ӵ�packet filter id�Ƿ��Ѵ��ڣ������ڣ�����Ԥ��ӵ�packet
       filter ��Ϣ�滻���ҵ���packet filter */
    if (NAS_ESM_SUCCESS == NAS_ESM_QueryPfInTft(ucPacketFilterID,
                                                pstSdfPara->astCntxtTftInfo,
                                                pstSdfPara->ulPfNum,
                                               &ulTftIdx))
    {
        NAS_ESM_MEM_CPY((VOS_VOID *)&(pstSdfPara->astCntxtTftInfo[ulTftIdx]), \
                        (const VOS_VOID *)&(pAppTftMsg->stAppTftInfo),
                         sizeof(APP_ESM_TFT_INFO_STRU));

        /*��APP��������ȷ��*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }


    /* ��Ԥ��ӵ�packet filter id�����ڣ��ҵ�ǰ��SDF�ľ�̬��Ϣ�е�packet filter��
       δ�ﵽ��������򽫴�packet filter��ӵ�SDF�ľ�̬��Ϣ��*/
    ulTftIdx = pstSdfPara->ulPfNum;
    pstSdfPara->ulPfNum++;
    NAS_ESM_MEM_CPY((VOS_VOID *)&(pstSdfPara->astCntxtTftInfo[ulTftIdx]), \
                    (const VOS_VOID *)&(pAppTftMsg->stAppTftInfo),
                     sizeof(APP_ESM_TFT_INFO_STRU));

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}
VOS_VOID NAS_ESM_AppParaSetSdfQos( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid               = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = 0;
    APP_ESM_SET_EPS_QOS_REQ_STRU       *pAppSdfQosMsg       = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetSdfQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetSdfQos_ENUM, LNAS_ENTRY);

    pAppSdfQosMsg=(APP_ESM_SET_EPS_QOS_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppSdfQosMsg->ulCid;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_EPS_QOS_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppSdfQosOperation(pAppSdfQosMsg))
    {
        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/
    enSetType=pAppSdfQosMsg->enSetType;

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*�ӽ�����Ϣ�л��SDFQOS��Ϣ,�����ڱ���*/
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstSdfPara->stSdfQosInfo),\
                            (VOS_VOID*)&(pAppSdfQosMsg->stSdfQosInfo),\
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    }
    else    /*��������Ϊɾ��*/
    {
        /*����ulCid��ɾ��������Ӧ�ṹ�е�SDFQOS��Ϣ*/
        pstSdfPara->bitOpSdfQos = NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET((VOS_VOID*)&(pstSdfPara->stSdfQosInfo),0,\
                            sizeof(APP_ESM_EPS_QOS_INFO_STRU));
    }

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}
VOS_VOID NAS_ESM_AppParaSetApn( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType       = 0;
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    APP_ESM_SET_APN_REQ_STRU           *pAppApnMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo      = {NAS_ESM_NULL};
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo    = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetApn_ENUM, LNAS_ENTRY);

    pAppApnMsg = (APP_ESM_SET_APN_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid = pAppApnMsg->ulCid;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_APN_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppApnOperation(pAppApnMsg->ulCid);

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetApn:NAS_ESM_CheckAppApnOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetApn_ENUM, LNAS_FAIL);

        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/
    enSetType = pAppApnMsg->enSetType;

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*�ӽ�����Ϣ�л��APN��Ϣ*/
        /*����ulCid����APN��Ϣ�����ڱ�����Ӧ�ṹ��*/
        ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                          &pAppApnMsg->stApnInfo);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetApn:WARNING:APP->SM ,App Set Apn Invalid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetApn_ENUM, 1);

            /*��APP������������ʧ����Ϣ*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }

        NAS_ESM_MEM_CPY(&pstSdfPara->stApnInfo,
                        &pAppApnMsg->stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU));

        /*������Ԫ��־λ*/
        pstSdfPara->bitOpApn = NAS_ESM_OP_TRUE;
    }
    else    /*��������Ϊɾ��*/
    {
        /*����ulCid��ɾ��������Ӧ�ṹ�е�APN��Ϣ*/
        /*������Ԫ��־λ*/
        pstSdfPara->bitOpApn= NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET((VOS_VOID*)&(pstSdfPara->stApnInfo),0,\
                   sizeof(APP_ESM_APN_INFO_STRU));
    }

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}
VOS_VOID NAS_ESM_AppParaSetPco( VOS_VOID *pRcvMsg )
{
    APP_ESM_SET_PCO_REQ_STRU           *pAppPcoMsg      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPco_ENUM, LNAS_ENTRY);

    pAppPcoMsg=(APP_ESM_SET_PCO_REQ_STRU*)pRcvMsg;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_PCO_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);


    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppPcoOperation(pAppPcoMsg))
    {
        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = APP_FAILURE;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }


    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

}


VOS_VOID NAS_ESM_AppParaSetPdnType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType       = 0;
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    APP_ESM_SET_PDN_TYPE_REQ_STRU      *pAppPdnTypeMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPdnType_ENUM, LNAS_ENTRY);

    pAppPdnTypeMsg=(APP_ESM_SET_PDN_TYPE_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppPdnTypeMsg->ulCid;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_PDN_TYPE_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppPdnTypeOperation(pAppPdnTypeMsg->ulCid,
                                              pAppPdnTypeMsg->enSetType,
                                              pAppPdnTypeMsg->enPdnType,
                                              pAppPdnTypeMsg->bitOpIpv4AddrAllocType,
                                              pAppPdnTypeMsg->enIpv4AddrAllocType);
    if (APP_SUCCESS != ulRslt)
    {
        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*�õ�������������*/
    enSetType=pAppPdnTypeMsg->enSetType;

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*������Ԫ��־λ*/
        pstSdfPara->bitOpPdnType = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType = pAppPdnTypeMsg->enPdnType;

        if (NAS_ESM_OP_TRUE == pAppPdnTypeMsg->bitOpIpv4AddrAllocType)
        {
            pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_TRUE;
            pstSdfPara->enIpv4AddrAllocType  = pAppPdnTypeMsg->enIpv4AddrAllocType;
        }
    }
    else
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_FALSE;
        pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_FALSE;
    }

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}
VOS_VOID NAS_ESM_AppParaSetBearType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulCid               = 0;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = 0;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    APP_ESM_SET_BEARER_TYPE_REQ_STRU   *pAppBearTypeMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetBearType_ENUM, LNAS_ENTRY);

    pAppBearTypeMsg=(APP_ESM_SET_BEARER_TYPE_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppBearTypeMsg->ulCid;

    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_BEARER_TYPE_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppBearTypeOperation(pAppBearTypeMsg->ulCid,
                                               pAppBearTypeMsg->enSetType,
                                               pAppBearTypeMsg->enBearCidType,
                                               pAppBearTypeMsg->bitOpLinkdCid,
                                               pAppBearTypeMsg->ulLinkdCid);

    if (APP_SUCCESS != ulRslt)
    {
        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/
    enSetType=pAppBearTypeMsg->enSetType;

    /*��������Ϊɾ��*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*����ulCid����λCID����Ϊ��ʼ��ֵ*/
        pstSdfPara->enBearerCntxtType = APP_ESM_CID_TYPE_DEFAULT;

        /*ɾ������CID*/
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
        pstSdfPara->ulLinkdCId = 0;

        /*��APP��������ȷ��*/
        stParaInfo.ulSetRslt = APP_SUCCESS;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return ;
    }

    /*�ӽ�����Ϣ�л��BearType��Ϣ,�����ڱ��ؽṹ��*/
    pstSdfPara->enBearerCntxtType = (VOS_UINT8)pAppBearTypeMsg->enBearCidType;

    /*��������Ϊ����*/
    if(APP_ESM_CID_TYPE_DEDICATED == pAppBearTypeMsg->enBearCidType)
    {

        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_TRUE;
        pstSdfPara->ulLinkdCId = pAppBearTypeMsg->ulLinkdCid;
    }
    else
    {
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
    }

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);
}
VOS_VOID NAS_ESM_AppParaSetPdpManagType( VOS_VOID *pRcvMsg )
{
    APP_ESM_PARA_SET_ENUM_UINT32           enSetType               = 0;
    APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU *pAppBearManagTypeMsg    =VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU          *pBearMagageInfo         =VOS_NULL_PTR;
    APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU *pAppBearManagTypeCnf    =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetPdpManagType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_ENTRY);

    pAppBearManagTypeMsg = (APP_ESM_SET_PDP_MANAGER_TYPE_REQ_STRU*)pRcvMsg;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppBearManagTypeCnf = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_SET_PDP_MANAGER_TYPE_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppBearManagTypeCnf)
    {
         /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaSetPdpManagType:ERROR:SM->APP Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_NULL_PTR);

        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppBearManagTypeCnf), 0, NAS_ESM_GET_MSG_LENGTH(pAppBearManagTypeCnf));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppBearManagTypeCnf,ID_APP_ESM_SET_PDP_MANAGER_TYPE_CNF,\
                               pAppBearManagTypeMsg->usTerminalId,pAppBearManagTypeMsg->usOriginalId,\
                               pAppBearManagTypeMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppBearManagTypeCnf->ulOpId = pAppBearManagTypeMsg->ulOpId;

    /*�õ�������������*/
    enSetType = pAppBearManagTypeMsg->enSetType;

    if (NAS_ESM_FAILURE == NAS_ESM_CheckAppPdpManagTypeOperation(pAppBearManagTypeMsg))
    {
        /*��APP������������ʧ����Ϣ*/
        pAppBearManagTypeCnf->ulSetRslt = APP_FAILURE;
        NAS_ESM_SND_MSG(pAppBearManagTypeCnf);
        return;
    }

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*�ӽ�����Ϣ�л�ó��ع���������Ϣ*/
        /*��ȡ���س��ع�����Ϣ�ṹָ��*/
        pBearMagageInfo=NAS_ESM_GetBearerManageInfoAddr();
        pBearMagageInfo->enMode=(VOS_UINT8)pAppBearManagTypeMsg->enAnsMode;
        pBearMagageInfo->enType=(VOS_UINT8)pAppBearManagTypeMsg->enAnsType;

        /*��APP��������ȷ��*/
        pAppBearManagTypeCnf->ulSetRslt = APP_SUCCESS;
    }
    else
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetPdpManagType:WARNING:APP->SM ,The para can not be del!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetPdpManagType_ENUM, LNAS_PARAM_INVALID);

        /*��APP������������ʧ����Ϣ*/
        pAppBearManagTypeCnf->ulSetRslt = APP_FAILURE;
    }


    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppBearManagTypeCnf);
}


VOS_VOID  NAS_ESM_AppParaSetGwAuthInfo( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType           = NAS_ESM_NULL;
    APP_ESM_SET_GW_AUTH_REQ_STRU       *pstAppGwAuthMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo          = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaSetGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaSetGwAuthInfo_ENUM, LNAS_ENTRY);

    pstAppGwAuthMsg =(APP_ESM_SET_GW_AUTH_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid = pstAppGwAuthMsg->ulCid;


    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_GW_AUTH_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    ulRslt = NAS_ESM_CheckAppGwAuthInfoOperation(pstAppGwAuthMsg->ulCid,
                                                 pstAppGwAuthMsg->enSetType,
                                                 &(pstAppGwAuthMsg->stGwAuthInfo));

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaSetGwAuthInfo:NAS_ESM_CheckAppGwAuthInfoOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaSetGwAuthInfo_ENUM, LNAS_FAIL);

        /*��APP������������ʧ����Ϣ*/
        stParaInfo.ulSetRslt = ulRslt;
        NAS_ESM_AppParaSetCnf(&stParaInfo);
        return;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/
    enSetType = pstAppGwAuthMsg->enSetType;

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    /*�����������Ϊ:����*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*������Ԫ��־λ*/
        pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_TRUE;

        /*�ӽ�����Ϣ�л��GW AUTH��Ϣ*/
        /*����ulCid����GW AUTH��Ϣ�����ڱ�����Ӧ�ṹ��*/
        NAS_ESM_MEM_CPY((VOS_VOID*)&pstSdfPara->stGwAuthInfo,
                         (VOS_VOID*)&pstAppGwAuthMsg->stGwAuthInfo,
                         sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    }
    else    /*��������Ϊɾ��*/
    {
        /*����ulCid��ɾ��������Ӧ�ṹ�е�PCO��Ϣ*/
        pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_FALSE;
        NAS_ESM_MEM_SET((VOS_VOID*)&(pstSdfPara->stGwAuthInfo), 0, \
                    sizeof(APP_ESM_GW_AUTH_INFO_STRU));
    }

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

    return;
}


VOS_VOID  NAS_ESM_AppSetCgdcont( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_SET_CGDCONT_REQ_STRU       *pstAppCgdcontMsg    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_APP_PARA_SET_RESLT_STRU     stParaInfo          = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppSetCgdcont is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppSetCgdcont_ENUM, LNAS_ENTRY);

    pstAppCgdcontMsg =(APP_ESM_SET_CGDCONT_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid = pstAppCgdcontMsg->ulCid;


    /*���ûظ���Ϣ�Ĳ�������*/
    stParaInfo.ulMsgId = ID_APP_ESM_SET_CGDCONT_CNF;
    NAS_ESM_AppSetCnfParaInfo(&stParaInfo,(NAS_ESM_APP_PARA_SET_HEAD_STRU*)pRcvMsg);

    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pstAppCgdcontMsg->ulCid,
                                                    pstAppCgdcontMsg->enSetType,
                                                    pstAppCgdcontMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 1);

            /*��APP������������ʧ����Ϣ*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }


    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pstAppCgdcontMsg->ulCid,
                                                        pstAppCgdcontMsg->enSetType,
                                                        pstAppCgdcontMsg->enPdnType,
                                                        pstAppCgdcontMsg->bitOpIpv4AddrAllocType,
                                                        pstAppCgdcontMsg->enIpv4AddrAllocType);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 2);

            /*��APP������������ʧ����Ϣ*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }

    if (NAS_ESM_OP_TRUE == pstAppCgdcontMsg->bitOpBearType)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetBearType(pstAppCgdcontMsg->ulCid,
                                                           pstAppCgdcontMsg->enSetType,
                                                           pstAppCgdcontMsg->enBearCidType,
                                                           NAS_ESM_OP_FALSE,
                                                           0);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppSetCgdcont: APN ERROR!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_AppSetCgdcont_ENUM, ESM_APN_ERROR, 3);

            /*��APP������������ʧ����Ϣ*/
            stParaInfo.ulSetRslt = ulRslt;
            NAS_ESM_AppParaSetCnf(&stParaInfo);
            return ;
        }
    }

    /* lihong00150010 ims begin */
    pstSdfPara                      = NAS_ESM_GetSdfParaAddr(ulCid);
    pstSdfPara->bitOpPcscfDiscovery = pstAppCgdcontMsg->bitOpPcscfDiscovery;
    pstSdfPara->enPcscfDiscovery    = pstAppCgdcontMsg->enPcscfDiscovery;
    pstSdfPara->bitOpImsCnSignalFlag= pstAppCgdcontMsg->bitOpImsCnSignalFlag;
    pstSdfPara->enImsCnSignalFlag   = pstAppCgdcontMsg->enImsCnSignalFlag;
    /* lihong00150010 ims end */

    /*��APP��������ȷ��*/
    stParaInfo.ulSetRslt = APP_SUCCESS;
    NAS_ESM_AppParaSetCnf(&stParaInfo);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_AppSetCnfParaInfo
 Description     : ���ò������ûظ��Ĳ�����Ϣ
 Input           : NAS_ESM_APP_PARA_SET_HEAD_STRU* pstRcvInfo
 Output          : NAS_ESM_APP_PARA_SET_RESLT_STRU*  pstParaInfo
 Return          : VOS_VOID

 History         :
    1.sunbing      2008-10-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_AppSetCnfParaInfo( NAS_ESM_APP_PARA_SET_RESLT_STRU*  pstParaInfo,
                                                const NAS_ESM_APP_PARA_SET_HEAD_STRU * pstRcvInfo)
{
    /*�õ���Ϣ��ָʾ��ulOpId,ulCid*/
    pstParaInfo->ulCid = pstRcvInfo->ulCid;
    pstParaInfo->ulOpId = pstRcvInfo->ulOpId;

    /*����MID����*/
    pstParaInfo->usOriginalId = pstRcvInfo->usTerminalId;
    pstParaInfo->usTerminalId = pstRcvInfo->usOriginalId;

    /*����SN����*/
    pstParaInfo->ulSn = pstRcvInfo->ulSN;
}
VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetBearType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_CID_TYPE_ENUM_UINT32        enBearCidType,
    VOS_UINT32                          bitOpLinkdCid,
    VOS_UINT32                          ulLinkdCid
)
{
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdcontOrNdisConnSetBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdcontOrNdisConnSetBearType_ENUM, LNAS_ENTRY);

    if(APP_ESM_CID_TYPE_DEDICATED == enBearCidType)
    {

        return APP_ERR_SM_BEARER_TYPE_ILLEGAL;
    }
    /*�õ���Ϣ��ָʾ��ulCid**/

    ulRslt = NAS_ESM_CheckAppBearTypeOperation(ulCid,
                                               enSetType,
                                               enBearCidType,
                                               bitOpLinkdCid,
                                               ulLinkdCid);

    /* �Ѿ���������޸� */
    if (NAS_ESM_SUCCESS != ulRslt)
    {
        return ulRslt;
    }


    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*�õ�������������*/

    /*��������Ϊɾ��*/
    if(APP_ESM_PARA_SETTING != enSetType)
    {
        /*����ulCid����λCID����Ϊ��ʼ��ֵ*/
        pstSdfPara->enBearerCntxtType = APP_ESM_CID_TYPE_DEFAULT;

        /*ɾ������CID*/
        pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;
        pstSdfPara->ulLinkdCId = 0;

        return APP_SUCCESS;
    }
    /*�ӽ�����Ϣ�л��BearType��Ϣ,�����ڱ��ؽṹ��*/
    pstSdfPara->enBearerCntxtType = (VOS_UINT8)enBearCidType;
    pstSdfPara->bitOpLinkdCId = NAS_ESM_OP_FALSE;

    return APP_SUCCESS;
}
VOS_UINT32 NAS_ESM_AppCgdconntOrNDISconnSetPdnType
(
    VOS_UINT32                          ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32        enSetType,
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpIpv4AddrAllocType,
    APP_ESM_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT32 enIpv4AddrAllocType

)
{
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdconntOrNDISconnSetPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdconntOrNDISconnSetPdnType_ENUM, LNAS_ENTRY);


    /*�õ���Ϣ��ָʾ��ulCid**/

    ulRslt = NAS_ESM_CheckAppPdnTypeOperation(ulCid,
                                              enSetType,
                                              enPdnType,
                                              bitOpIpv4AddrAllocType,
                                              enIpv4AddrAllocType);

    if (APP_SUCCESS != ulRslt)
    {
        /*��APP������������ʧ����Ϣ*/
        return ulRslt;
    }

    /*�õ�������������*/

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*������Ԫ��־λ*/
        pstSdfPara->bitOpPdnType = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType = enPdnType;
        if (NAS_ESM_OP_TRUE == bitOpIpv4AddrAllocType)
        {
            pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_TRUE;
            pstSdfPara->enIpv4AddrAllocType  = enIpv4AddrAllocType;
        }

    }
    else
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_FALSE;
        pstSdfPara->bitIpv4AddrAllocType = NAS_ESM_OP_FALSE;
    }

    return APP_SUCCESS;
}
VOS_UINT32 NAS_ESM_AppCgdcontOrNdisConnSetApn
(
    VOS_UINT32                                  ulCid,
    APP_ESM_PARA_SET_ENUM_UINT32                enSetType,
    APP_ESM_APN_INFO_STRU                       stApnInfo
)
{
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo    = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, LNAS_ENTRY);


    /*�õ���Ϣ��ָʾ��ulCid**/
    ulRslt = NAS_ESM_CheckAppApnOperation(ulCid);
    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn:NAS_ESM_CheckAppApnOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, LNAS_FAIL);
        return ulRslt;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);


    /*���ݲ����������ͣ�������Ϣ��������ɾ������*/
    if(APP_ESM_PARA_SETTING == enSetType)
    {
        /*�ӽ�����Ϣ�л��APN��Ϣ*/
        /*����ulCid����APN��Ϣ�����ڱ�����Ӧ�ṹ��*/
        ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                          &stApnInfo);
        if(APP_SUCCESS != ulRslt)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_AppCgdcontOrNdisConnSetApn:WARNING:APP->SM ,App Set Apn Invalid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppCgdcontOrNdisConnSetApn_ENUM, 1);

            return ulRslt;
        }

        NAS_ESM_MEM_CPY(&pstSdfPara->stApnInfo,
                        &stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU));

        /*������Ԫ��־λ*/
        pstSdfPara->bitOpApn = NAS_ESM_OP_TRUE;
    }
    else    /*��������Ϊɾ��*/
    {
        /*����ulCid��ɾ��������Ӧ�ṹ�е�APN��Ϣ*/
        /*������Ԫ��־λ*/
        pstSdfPara->bitOpApn= NAS_ESM_OP_FALSE;

        NAS_ESM_MEM_SET((VOS_VOID*)&(pstSdfPara->stApnInfo),0,\
                   sizeof(APP_ESM_APN_INFO_STRU));
    }

    return APP_SUCCESS;

}

/* lihong00150010 ims begin */

VOS_UINT32  NAS_ESM_AppNdisConnSetGwAuthInfo( VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulCid               = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pstAppGwAuthMsg     = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt              = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppNdisConnSetGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppNdisConnSetGwAuthInfo_ENUM, LNAS_ENTRY);

    pstAppGwAuthMsg =(APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid = pstAppGwAuthMsg->ulCid;

    ulRslt = NAS_ESM_CheckAppGwAuthInfoOperation(pstAppGwAuthMsg->ulCid,
                                                 APP_ESM_PARA_SETTING,
                                                 &(pstAppGwAuthMsg->stGwAuthInfo));

    if (APP_SUCCESS != ulRslt)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppNdisConnSetGwAuthInfo:NAS_ESM_CheckAppGwAuthInfoOperation failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppNdisConnSetGwAuthInfo_ENUM, LNAS_FAIL);

        /*��APP������������ʧ����Ϣ*/
        return ulRslt;
    }

    /*����ulCid����ȡ����NAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*������Ԫ��־λ*/
    pstSdfPara->bitOpGwAuthInfo = NAS_ESM_OP_TRUE;

    /*�ӽ�����Ϣ�л��GW AUTH��Ϣ*/
    /*����ulCid����GW AUTH��Ϣ�����ڱ�����Ӧ�ṹ��*/
    NAS_ESM_MEM_CPY((VOS_VOID*)&pstSdfPara->stGwAuthInfo,
                     (VOS_VOID*)&pstAppGwAuthMsg->stGwAuthInfo,
                     sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    return APP_SUCCESS;
}
/* lihong00150010 ims end */



VOS_VOID NAS_ESM_AppParaQueryMsgProc(VOS_VOID *pRcvMsg)
{
    APP_PS_MSG_HEADER_STRU   *pAppMsg    = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = (APP_PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ���ͣ�������Ӧ�Ĳ�����ѯ����*/
    switch (pAppMsg->ulMsgId)
    {

        case ID_APP_ESM_INQ_BEAER_QOS_REQ:

            /*���ò�����ѯ����*/
            NAS_ESM_AppParaQueryBearQos(pRcvMsg);

            break;

        case ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ:

             NAS_ESM_AppQueryDynamicPdpMsgProc(pRcvMsg);

             break;
        case ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ:

             NAS_ESM_AppQueryDynamicEpsQosMsgProc(pRcvMsg);

             break;
        case ID_APP_ESM_INQ_DYNAMIC_TFT_REQ:

             NAS_ESM_AppQueryDynamicTftMsgProc(pRcvMsg);

             break;
        default:

            /*��ӡ�յ��쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryMsgProc:WARNING:APP->SM ,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryMsgProc_ENUM, LNAS_MSG_INVALID);

            break;
    }
}

/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryTft( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_TFT_REQ_STRU         *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_TFT_CNF_STRU         *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryTft is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryTft_ENUM, LNAS_ENTRY);

    pAppQueryMsg =(APP_ESM_INQ_TFT_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_TFT_CNF_STRU));
    /*lint +e433 +e826*/

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryTft:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryTft_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ��MID����*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_TFT_CNF,\
                              pAppQueryMsg->usTerminalId,pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid =ulCid;
    pAppCnfMsg->ulOpId =ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*����CID�����Ƿ�Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryTft:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryTft_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_NULL == pstSdfPara->ulPfNum)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            /*����TFT����*/
            pAppCnfMsg->ulPfNum = pstSdfPara->ulPfNum;

            NAS_ESM_MEM_CPY((VOS_VOID *)pAppCnfMsg->astPfInfo,
                            (const VOS_VOID *)pstSdfPara->astCntxtTftInfo,
                             sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstSdfPara->ulPfNum);
        }
    }
    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}
/*lint -specific(+e433)*/

VOS_VOID NAS_ESM_AppParaQuerySdfQos( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_EPS_QOS_REQ_STRU     *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_EPS_QOS_CNF_STRU     *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQuerySdfQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQuerySdfQos_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_EPS_QOS_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_EPS_QOS_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQuerySdfQos:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQuerySdfQos_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_EPS_QOS_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId= ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*���CID�������Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQuerySdfQos:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQuerySdfQos_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpSdfQos)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            /*��װSDF QOS��Ϣ�ṹ*/
            NAS_ESM_MEM_CPY((VOS_VOID*)&(pAppCnfMsg->stSdfQosInfo),\
                        (VOS_VOID*)&(pstSdfPara->stSdfQosInfo),\
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));
        }
    }

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}
VOS_VOID NAS_ESM_AppParaQueryApn( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                      ulOpId          = 0;
    VOS_UINT32                      ulCid           = 0;
    APP_ESM_INQ_APN_REQ_STRU       *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_APN_CNF_STRU       *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU          *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryApn_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_APN_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_APN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryApn:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryApn_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_APN_CNF,
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId= ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*���CID�������Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryApn:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryApn_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpApn)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {

            NAS_ESM_MEM_CPY(&pAppCnfMsg->stApnInfo,
                            &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));
        }
    }

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}




/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryPco( VOS_VOID *pRcvMsg )
{

    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_PCO_REQ_STRU         *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_PCO_CNF_STRU         *pAppCnfMsg      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPco_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_PCO_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PCO_CNF_STRU));/* lint !e826 */
    /*lint +e433 +e826*/

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPco:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPco_ENUM, LNAS_NULL_PTR);
        return;
    }



    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PCO_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;


    /*���CID�������Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryPco:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryPco_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }


    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);


}
/*lint -specific(+e433)*/


VOS_VOID NAS_ESM_AppParaQueryPdnType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                          ulOpId          = 0;
    VOS_UINT32                          ulCid           = 0;
    APP_ESM_INQ_PDN_TYPE_REQ_STRU    *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_PDN_TYPE_CNF_STRU    *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPdnType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPdnType_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_PDN_TYPE_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDN_TYPE_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPdnType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPdnType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PDN_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*���CID�������Ϸ�*/
    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryPdnType:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryPdnType_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if (NAS_ESM_OP_FALSE == pstSdfPara->bitOpPdnType)
        {
            pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        }
        else
        {
            pAppCnfMsg->enPdnType = pstSdfPara->enPdnType;

            if (NAS_ESM_OP_TRUE == pstSdfPara->bitIpv4AddrAllocType)
            {
                pAppCnfMsg->bitOpIpv4AddrAllocType = NAS_ESM_OP_TRUE;
                pAppCnfMsg->enIpv4AddrAllocType    = pstSdfPara->enIpv4AddrAllocType;
            }
        }
    }

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}


VOS_VOID NAS_ESM_AppParaQueryBearType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                              ulOpId          = 0;
    VOS_UINT32                              ulCid           = 0;
    APP_ESM_INQ_BEARER_TYPE_REQ_STRU     *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_BEARER_TYPE_CNF_STRU     *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU                  *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryBearType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryBearType_ENUM, LNAS_ENTRY);

    pAppQueryMsg=(APP_ESM_INQ_BEARER_TYPE_REQ_STRU*)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;

    /*�õ���Ϣ��ָʾ��ulCid**/
    ulCid =pAppQueryMsg->ulCid;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEARER_TYPE_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryBearType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryBearType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_BEARER_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid = ulCid;
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryBearType:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryBearType_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
    }
    else
    {
        /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
        pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

        if ((NAS_ESM_OP_TRUE == pstSdfPara->bitOpLinkdCId)
         && (APP_ESM_CID_TYPE_DEDICATED == pstSdfPara->enBearerCntxtType))
        {

            /*���ع�������CID�ͳ�������*/
            pAppCnfMsg->bitOpLinkdCid = NAS_ESM_OP_TRUE;
            pAppCnfMsg->enBearCidType = pstSdfPara->enBearerCntxtType;
            pAppCnfMsg->ulLinkdCid = pstSdfPara->ulLinkdCId;
        }
        else
        {
            /*ֻ���س�������*/
            pAppCnfMsg->bitOpLinkdCid = NAS_ESM_OP_FALSE;
            pAppCnfMsg->enBearCidType = pstSdfPara->enBearerCntxtType;
        }
    }

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

}
VOS_VOID NAS_ESM_AppParaQueryPdpManagType( VOS_VOID *pRcvMsg )
{
    VOS_UINT32                                  ulOpId          =0;
    APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU      *pAppQueryMsg    =VOS_NULL_PTR;
    APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU      *pAppCnfMsg      =VOS_NULL_PTR;
    NAS_ESM_PDP_MANAGE_INFO_STRU               *pBearMagageInfo =VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryPdpManagType is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryPdpManagType_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_PDP_MANAGER_TYPE_REQ_STRU *)pRcvMsg;

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId = pAppQueryMsg->ulOpId;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDP_MANAGER_TYPE_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryPdpManagType:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryPdpManagType_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ������ID��Ϣ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_PDP_MANAGER_TYPE_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulOpId = ulOpId;

    /*��ȡNAS_ESM_PDP_MANAGE_INFO_STRU�ṹָ��*/
    pBearMagageInfo = NAS_ESM_GetBearerManageInfoAddr();

    /*����Ӧ��ģʽ:0,�Զ���1,�ֶ�*/
    pAppCnfMsg->enAnsMode = pBearMagageInfo->enMode;

    /*��Ӧ��ģʽΪ�Զ�*/
    if(APP_ESM_ANSWER_MODE_AUTO == pAppCnfMsg->enAnsMode)
    {
        /*�����Զ�Ӧ������*/
        pAppCnfMsg->enAnsType = pBearMagageInfo->enType;
    }

    pAppCnfMsg->ulRslt = APP_SUCCESS;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}
VOS_VOID NAS_ESM_QueryBearQos(VOS_UINT32   ulEpsbId,
                                          APP_ESM_INQ_BEAER_QOS_CNF_STRU      *pAppCnfMsg)
{
    VOS_UINT32                          ulTmpEpsbId      = ulEpsbId;
    VOS_UINT32                          ulCIdNum         = VOS_NULL;
    VOS_UINT32                          ulCnt            = VOS_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    APP_ESM_INQ_BEAER_QOS_CNF_STRU     *pTmpAppCnfMsg    = pAppCnfMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_QueryBearQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_QueryBearQos_ENUM, LNAS_ENTRY);

    if(((ulTmpEpsbId < NAS_ESM_MIN_EPSB_ID) || (ulTmpEpsbId > NAS_ESM_MAX_EPSB_ID))
        && (NAS_ESM_UNASSIGNED_EPSB_ID != ulTmpEpsbId))
    {
        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
        return;
    }
    else if(NAS_ESM_UNASSIGNED_EPSB_ID == ulTmpEpsbId)
    {
        /*�������г�����Ϣ*/
        for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
        {
            /*����EpsIdȡ��������Ϣ*/
            pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulCnt);

            /*����˳���Ϊָ���������ͣ����ѹ���CID*/
            if( NAS_ESM_BEARER_STATE_ACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)
            {
                /*��¼��pTmpAppCnfMsg*/
                pTmpAppCnfMsg->astQosInfo[ulCIdNum].ulEpsbId = ulCnt;

                NAS_ESM_MEM_CPY((VOS_VOID*)&(pTmpAppCnfMsg->astQosInfo[ulCIdNum].stQos),\
                    (VOS_VOID*)&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),\
                    sizeof(APP_ESM_EPS_QOS_INFO_STRU));

                ulCIdNum ++;
            }
        }
        if(VOS_NULL == ulCIdNum)
        {
            pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
            return;
        }
        pTmpAppCnfMsg->ulEpsbIdNum = ulCIdNum;
        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_ACCEPT;
        return;
    }
    else
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulTmpEpsbId);

        if(NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState)
        {
            pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_REJ;
            return;
        }

        pTmpAppCnfMsg->ulEpsbIdNum = 1;
        pTmpAppCnfMsg->astQosInfo[0].ulEpsbId = ulTmpEpsbId;

        NAS_ESM_MEM_CPY((VOS_VOID*)&(pTmpAppCnfMsg->astQosInfo[0].stQos),\
                (VOS_VOID*)&(pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo),\
                sizeof(APP_ESM_EPS_QOS_INFO_STRU));

        pTmpAppCnfMsg->enAnsType = APP_ESM_ANSWER_ACCEPT;
        return;
    }
}
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppParaQueryBearQos( VOS_VOID *pRcvMsg)
{
    VOS_UINT32                           ulEpsbId        = VOS_NULL;
    APP_ESM_INQ_BEAER_QOS_REQ_STRU      *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_BEAER_QOS_CNF_STRU      *pAppCnfMsg      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryBearQos is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryBearQos_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_BEAER_QOS_REQ_STRU*)pRcvMsg;

    ulEpsbId = pAppQueryMsg->ulEpsbId;
    /*lint -e433 -e826*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEAER_QOS_CNF_STRU));
    /*lint +e433 +e826*/
    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryBearQos:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryBearQos_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ������ID��Ϣ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_BEAER_QOS_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    NAS_ESM_QueryBearQos(ulEpsbId, pAppCnfMsg);

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}
/*lint -specific(+e433)*/


VOS_VOID  NAS_ESM_AppParaQueryGwAuthInfo(VOS_VOID *pRcvMsg  )
{
    VOS_UINT32                          ulOpId          = NAS_ESM_NULL;
    VOS_UINT32                          ulCid           = NAS_ESM_NULL;
    APP_ESM_INQ_GW_AUTH_REQ_STRU       *pAppQueryMsg    = VOS_NULL_PTR;
    APP_ESM_INQ_GW_AUTH_CNF_STRU       *pAppCnfMsg      = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppParaQueryGwAuthInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, LNAS_ENTRY);

    pAppQueryMsg = (APP_ESM_INQ_GW_AUTH_REQ_STRU*)pRcvMsg;

    ulCid = pAppQueryMsg->ulCid;
    ulOpId = pAppQueryMsg->ulOpId;

    /*����ulCid����ȡNAS_ESM_BEARER_CNTXT_PARA_STRU�ṹָ��*/
    pstSdfPara = NAS_ESM_GetSdfParaAddr(ulCid);

    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_GW_AUTH_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppParaQueryGwAuthInfo:ERROR:APP->ESM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pAppCnfMsg), 0, NAS_ESM_GET_MSG_LENGTH(pAppCnfMsg));

    /*��д��Ϣͷ������ID��Ϣ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_INQ_GW_AUTH_CNF,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->ulSN);

    /*��װ��Ϣ����*/
    pAppCnfMsg->ulCid                   = ulCid;
    pAppCnfMsg->ulOpId                  = ulOpId;

    pAppCnfMsg->ulRslt                  = APP_SUCCESS;

    if(ulCid >= NAS_ESM_MAX_UE_CONTRUL_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryGwAuthInfo:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, ESM_CID_ERROR);
        pAppCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;
        NAS_ESM_SND_MSG(pAppCnfMsg);
        return;
    }

    if ((NAS_ESM_OP_FALSE == pstSdfPara->bitOpGwAuthInfo)
        || (NAS_ESM_BEARER_TYPE_DEDICATED == pstSdfPara->enBearerCntxtType))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppParaQueryGwAuthInfo:WARNING:APP->SM ,Gw Auth info is not exit or Bear type is err!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppParaQueryGwAuthInfo_ENUM, 1);
        pAppCnfMsg->ulRslt = APP_ERR_PARA_ERROR;
        NAS_ESM_SND_MSG(pAppCnfMsg);
        return;
    }

    NAS_ESM_MEM_CPY((VOS_VOID*)&pAppCnfMsg->stGwAuthInfo,\
                    (VOS_VOID*)&pstSdfPara->stGwAuthInfo,\
                    sizeof(APP_ESM_GW_AUTH_INFO_STRU));

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);
}


VOS_VOID  NAS_ESM_SndEsmAppBearerQosIndMsg(VOS_UINT32 ulEpsbId)
{
    VOS_UINT16                          usOriginalId        = 0;
    VOS_UINT16                          usTerminalId        = 0;
    APP_ESM_INQ_BEAER_QOS_IND_STRU     *pEsmAppQosInd      =VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pEpsCntxtInfo       =VOS_NULL_PTR;

    /*��ñ���EpsB���������Ľṹָ��*/
    pEpsCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmAppQosInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_BEAER_QOS_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pEsmAppQosInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppBearerQosIndMsg:ERROR:APP->SM,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppBearerQosIndMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pEsmAppQosInd), 0, \
                NAS_ESM_GET_MSG_LENGTH(pEsmAppQosInd));

    /*���䱾�ι���APP_MSG_HEADER*/
    NAS_ESM_AssignMidHeader(&usOriginalId,&usTerminalId);

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pEsmAppQosInd,ID_APP_ESM_INQ_BEAER_QOS_IND,\
                              usOriginalId,usTerminalId,0);

    /*��װ��Ϣ����*/
    NAS_ESM_MEM_CPY((VOS_VOID*)&(pEsmAppQosInd->stQosInfo),\
        (VOS_VOID*)&(pEpsCntxtInfo->stEpsQoSInfo.stQosInfo),\
        sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    pEsmAppQosInd->ulEpsbId = ulEpsbId;

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmAppQosInd);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicPdpMsgProc
 Description     : ����APP��ѯPDP��̬��Ϣ����Ϣ
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu00143951      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryDynamicPdpMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU      *pstEsmAppPdpDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU               *pstEpsbCntxtInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU      *pAppMsg                = VOS_NULL_PTR;
    VOS_UINT32                                  ulEpsbId               = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_PDP_CONT_REQ_STRU* )pRcvMsg;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pstEsmAppPdpDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU));
    /*lint +e433 +e826*/
    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEsmAppPdpDynaCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pstEsmAppPdpDynaCnfMsg),
                     0,
                     NAS_ESM_GET_MSG_LENGTH(pstEsmAppPdpDynaCnfMsg));

    /*��д��Ϣͷ��MID����*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppPdpDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*��װ��Ϣ����*/
    pstEsmAppPdpDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppPdpDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppPdpDynaCnfMsg->ulRslt = APP_SUCCESS;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppPdpDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);
        return ;
    }

    /*there is a EpsID mapped CID, get EpsID or return*/
    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicPdpMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicPdpMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppPdpDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);
        return;
    }

    /*����EpsIdȡ��������Ϣ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstEsmAppPdpDynaCnfMsg->ulEpsbId = pstEpsbCntxtInfo->ulEpsbId;

    /* set PDN address information for this msg response,if Eps bearer has */
    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPdnAddr)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpPdnAddr = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stPDNAddrInfo,
                        (const VOS_VOID *)&pstEpsbCntxtInfo->stPdnAddrInfo,
                         sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY((VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stSubnetMask,
                        (const VOS_VOID *)&pstEpsbCntxtInfo->stSubnetMask,
                         sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpGateWayAddrInfo)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID *)&pstEsmAppPdpDynaCnfMsg->stGateWayAddrInfo,
                        (const VOS_VOID *)&pstEpsbCntxtInfo->stGateWayAddrInfo,
                         sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }

    /* set APN information for this msg response,if Eps bearer has */
    if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpApn)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpApn = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&pstEsmAppPdpDynaCnfMsg->stApnInfo,
                        (const VOS_VOID*)&pstEpsbCntxtInfo->stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU));
    }

    /* set Link Cid for the msg response,if Eps bearer has */
    pstEsmAppPdpDynaCnfMsg->ulLinkCid    = NAS_ESM_GetLinkCidByActiveCid(pAppMsg->ulCid);
    if (NAS_ESM_ILL_CID != pstEsmAppPdpDynaCnfMsg->ulLinkCid)
    {
        pstEsmAppPdpDynaCnfMsg->bitOpLinkCid = NAS_ESM_OP_TRUE;
    }
    else
    {
        pstEsmAppPdpDynaCnfMsg->bitOpLinkCid = NAS_ESM_OP_FALSE;
    }

    /*����PCO��Ϣ*/
    if(NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPco)
    {
        NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo(pstEsmAppPdpDynaCnfMsg,pstEpsbCntxtInfo);
    }

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEsmAppPdpDynaCnfMsg);

    return;
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicEpsQosMsgProc
 Description     : ����APP��ѯ��̬QOS��Ϣ����Ϣ
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_AppQueryDynamicEpsQosMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU     *pstEsmAppQosDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU                *pstSdfInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU     *pAppMsg          = VOS_NULL_PTR;
    VOS_UINT32                                  ulEpsbId;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_EPS_QOS_REQ_STRU* )pRcvMsg;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstEsmAppQosDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEsmAppQosDynaCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pstEsmAppQosDynaCnfMsg),
                     0,
                     NAS_ESM_GET_MSG_LENGTH(pstEsmAppQosDynaCnfMsg));

    /*��д��Ϣͷ��MID����*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppQosDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_EPS_QOS_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*��װ��Ϣ����*/
    pstEsmAppQosDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppQosDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppQosDynaCnfMsg->ulRslt   = APP_SUCCESS;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppPDPDynamicQueryMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppQosDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);
        return;
    }

    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicEpsQosMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicEpsQosMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppQosDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);
        return;
    }

    pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(pAppMsg->ulCid);

    /* ����QOS��̬��Ϣ */
    NAS_ESM_MEM_CPY((VOS_VOID *)&pstEsmAppQosDynaCnfMsg->stSdfQosInfo,
                            (const VOS_VOID *)&pstSdfInfo->stSdfQosInfo.stQosInfo,
                             sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEsmAppQosDynaCnfMsg);

}


/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryDynamicTftMsgProc
 Description     : ����APP��ѯ��̬TFT��Ϣ����Ϣ
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryDynamicTftMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU         *pstEsmAppTftDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU              *pstSdfInfo       = VOS_NULL_PTR;
    APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU         *pAppMsg          = VOS_NULL_PTR;
    VOS_UINT32                                ulEpsbId;
    VOS_UINT32                                ulCnt            = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_AppQueryDynamicTftMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, LNAS_ENTRY);

    pAppMsg = ( APP_ESM_INQ_DYNAMIC_TFT_REQ_STRU* )pRcvMsg;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pstEsmAppTftDynaCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_DYNAMIC_TFT_CNF_STRU));
    /*lint +e433 +e826*/
    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstEsmAppTftDynaCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET( NAS_ESM_GET_MSG_ENTITY(pstEsmAppTftDynaCnfMsg),
                     0,
                     NAS_ESM_GET_MSG_LENGTH(pstEsmAppTftDynaCnfMsg));

    /*��д��Ϣͷ��MID����*/
    NAS_ESM_WRITE_APP_MSG_HEAD(pstEsmAppTftDynaCnfMsg,
                               ID_APP_ESM_INQ_DYNAMIC_TFT_CNF,
                               pAppMsg->usTerminalId,
                               pAppMsg->usOriginalId,
                               pAppMsg->ulSN);

    /*��װ��Ϣ����*/
    pstEsmAppTftDynaCnfMsg->ulCid  = pAppMsg->ulCid;
    pstEsmAppTftDynaCnfMsg->ulOpId = pAppMsg->ulOpId;
    pstEsmAppTftDynaCnfMsg->ulRslt   = APP_SUCCESS;

    /*����CID�����Ƿ�Ϸ�*/
    if(pAppMsg->ulCid >= NAS_ESM_MAX_CID_NUM)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:WARNING:APP->SM ,Invalid CID Number!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, ESM_CID_ERROR);
        pstEsmAppTftDynaCnfMsg->ulRslt = APP_ERR_SM_CALL_CID_INVALID;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);
        return;
    }

    if (NAS_ESM_SUCCESS != NAS_ESM_QueryEpsbCntxtTblByCid(pAppMsg->ulCid,&ulEpsbId))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_AppQueryDynamicTftMsgProc:Warning: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryDynamicTftMsgProc_ENUM, ESM_Cid_is_dealing_or_resource_is_insufficient);
        pstEsmAppTftDynaCnfMsg->ulRslt = APP_ERR_SM_BEARER_INACTIVE;

        /*������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);
        return;
    }

    pstSdfInfo = NAS_ESM_GetSdfCntxtInfo(pAppMsg->ulCid);

    /* ����TFT��̬��Ϣ */
    pstEsmAppTftDynaCnfMsg->ulPfNum = pstSdfInfo->ulSdfPfNum;
    NAS_ESM_MEM_CPY((VOS_VOID *)&pstEsmAppTftDynaCnfMsg->astPfInfo[0],
                            (const VOS_VOID *)&pstSdfInfo->astSdfPfInfo[0],
                             sizeof(NAS_ESM_CONTEXT_TFT_STRU) * pstSdfInfo->ulSdfPfNum);

    for (ulCnt = NAS_ESM_NULL; ulCnt < pstEsmAppTftDynaCnfMsg->ulPfNum; ulCnt++)
    {
        pstEsmAppTftDynaCnfMsg->astPfInfo[ulCnt].ucNwPacketFilterId++;
    }
    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEsmAppTftDynaCnfMsg);

}
/*lint -specific(+e433)*/


VOS_VOID  NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo( VOS_VOID *pstRsvMsg ,VOS_VOID *pstCntxtInfo)
{
    APP_ESM_INQ_DYNAMIC_PDP_CONT_CNF_STRU       *pstEsmAppPdpDynaCnfMsg = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU                *pstEpsCntxtInfo        = VOS_NULL_PTR;
    NAS_ESM_PCO_TRANSFORM_STRU                   stTransPco             = {NAS_ESM_NULL};

    pstEpsCntxtInfo = pstCntxtInfo;
    pstEsmAppPdpDynaCnfMsg = pstRsvMsg;

    NAS_ESM_TransformPcoStru(   pstEpsCntxtInfo->stPdnAddrInfo.ucIpType,
                                    &(pstEpsCntxtInfo->stPcoInfo),
                                    &stTransPco);

    if (stTransPco.ucDnsSerNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo:Dns is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 1);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_FALSE;
        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucDnsSerNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 2);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Dns is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 3);
        pstEsmAppPdpDynaCnfMsg->bitOpDnsPrim    = NAS_ESM_OP_TRUE;
        pstEsmAppPdpDynaCnfMsg->bitOpDnsSec     = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stDnsSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astDnsServer[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }

    if (stTransPco.ucPcscfNum == 0)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 4);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_FALSE;
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else if (stTransPco.ucPcscfNum == 1)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:Prim P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 5);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));

        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_FALSE;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_ProcSetUpMsgPcoInfo:P-CSCF is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcQueryDynamicPdpMsgPcoInfo_ENUM, 6);
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfPrim  = NAS_ESM_OP_TRUE;
        pstEsmAppPdpDynaCnfMsg->bitOpPCscfSec   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY((VOS_VOID*)(VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfPrimAddrInfo),\
                    (VOS_VOID*)(VOS_VOID*)&(stTransPco.astPcscf[0]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstEsmAppPdpDynaCnfMsg->stPCscfSecAddrInfo),\
                    (VOS_VOID*)&(stTransPco.astPcscf[1]), \
                     sizeof(APP_ESM_IP_ADDR_STRU));
    }

    /* lihong00150010 ims begin */
    pstEsmAppPdpDynaCnfMsg->bitOpImsCnSignalFlag    = pstEpsCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag;
    pstEsmAppPdpDynaCnfMsg->enImsCnSignalFlag       = pstEpsCntxtInfo->stPcoInfo.enImsCnSignalFlag;
    /* lihong00150010 ims end */
}


VOS_VOID  NAS_ESM_BearerCntxtParaInit( VOS_VOID )
{
    NAS_ESM_SDF_PARA_STRU          *pstBearCntxtPara  = VOS_NULL_PTR;
    VOS_UINT32                      ulCur             = NAS_ESM_NULL;

    /* ��ʼ����CID0-CID19�ĳ�������Ϊר�г��� */
    for (ulCur = 0; ulCur < NAS_ESM_MAX_UE_CONTRUL_CID; ulCur++ )
    {
        pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(ulCur);
        NAS_ESM_MEM_SET(pstBearCntxtPara, 0, sizeof(NAS_ESM_SDF_PARA_STRU));

        pstBearCntxtPara->bitOpLinkdCId         = NAS_ESM_OP_TRUE;
        pstBearCntxtPara->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEDICATED;
        pstBearCntxtPara->ulLinkdCId            = 20;
    }

    /* ��ʼ����CID20�ĳ�������Ϊȱʡ���� */
    pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(NAS_ESM_MAX_UE_CONTRUL_CID);
    NAS_ESM_MEM_SET(pstBearCntxtPara, 0, sizeof(NAS_ESM_SDF_PARA_STRU));

    pstBearCntxtPara->bitOpPdnType          = NAS_ESM_OP_TRUE;
    pstBearCntxtPara->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstBearCntxtPara->enPdnType             = APP_ESM_PDN_TYPE_IPV4;

    for (ulCur = 0; ulCur < NAS_ESM_MAX_CID_NUM; ulCur++ )
    {
        pstBearCntxtPara = NAS_ESM_GetSdfParaAddr(ulCur);
        pstBearCntxtPara->ulCId = ulCur;
    }
}


VOS_VOID  NAS_ESM_BearerManageInfoInit(NAS_ESM_PDP_MANAGE_INFO_STRU *pstBearerManInfo  )
{
    /*��ʼ�����ع�������Ϊ�����������󣬳�ʼ�����ع���ģʽΪ�Զ�Ӧ��*/
    pstBearerManInfo->enType = NAS_ESM_BEARER_MANAGE_TYPE_ACCEPT;   /* ���ع������ͳ�ʼ�� */
    pstBearerManInfo->enMode = NAS_ESM_BEARER_MANAGE_MODE_AUTO;     /* ���ع���ģʽ��ʼ�� */

}
/*leili modify for isr begin*/

VOS_UINT32  NAS_ESM_IsPrefixInfoExist(VOS_UINT8 ucEpsId)
{
    VOS_UINT32                          i;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsId);

    /*ǰ׺��Ϣ�����ڣ�ǰ8���ֽ�ȫ0��ʾ�����ڣ�����Ҫ����*/

    for (i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        if (NAS_ESM_NULL != pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr[i])
        {
            return NAS_ESM_SUCCESS;
        }
    }

    return NAS_ESM_FAILURE;
}
VOS_UINT32  NAS_ESM_MatchPrefixInfo
(
    const VOS_UINT8  *pucLocalPrefix,
    const VOS_UINT8  *pucPrefix
)
{
    VOS_UINT32                          i;

    /*ǰ׺��Ϣǰ8���ֽ�ȫ��ͬ��ʾ��ͬ������Ҫ����*/
    for (i = 0; i < (APP_MAX_IPV6_ADDR_LEN/2); i++)
    {
        if (pucLocalPrefix[i] != pucPrefix[i])
        {
            return NAS_ESM_FAILURE;
        }
    }

    return NAS_ESM_SUCCESS;
}

/*leili modify for isr end*/

VOS_VOID NAS_ESM_AppIpv6InfoNotifyMsgProc(VOS_VOID* pRcvMsg)
{
    APP_ESM_IPV6_INFO_NOTIFY_STRU      *pstIpv6Notify = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucEpsbId = 0;

    pstIpv6Notify = (APP_ESM_IPV6_INFO_NOTIFY_STRU *)pRcvMsg;
    ucEpsbId = pstIpv6Notify->ucEpsbId;
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsbId);

    if (NAS_ESM_BEARER_STATE_ACTIVE != pstEpsbCntxtInfo->enBearerCntxtState)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Eps bearer is not active!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 1);
        return;
    }

    /* ���ǰ׺����Ϊ�㣬��ֱ�ӷ��� */
    if (NAS_ESM_NULL == pstIpv6Notify->ucIpv6PrefixNum)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc: Ipv6 prefix num is zero!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 2);
        return;
    }

    /*leili modify for isr begin*/
    /*ǰ׺��Ϣ�����ڣ�ǰ8���ֽ�ȫ0��ʾ�����ڣ�����Ҫ����*/
    if (NAS_ESM_SUCCESS == NAS_ESM_IsPrefixInfoExist(ucEpsbId))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Prefix info is exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 3);

        /*�ж�ǰ׺�Ƿ��������������Ͳ�����*/
        if (NAS_ESM_FAILURE == NAS_ESM_MatchPrefixInfo(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,pstIpv6Notify->astIpv6PrefixArray[0].aucPrefix))
        {
            NAS_ESM_NORM_LOG("NAS_ESM_AppIpv6InfoNotifyMsgProc:Prefix info change!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_AppIpv6InfoNotifyMsgProc_ENUM, 4);
            NAS_ESM_SndEsmEmmBearerModifyReq(ucEpsbId);
        }
    }
    /*leili modify for isr end*/

    NAS_ESM_MEM_SET(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,
                    NAS_ESM_NULL,pstIpv6Notify->astIpv6PrefixArray[0].ucPrefixLen);

    /* ȡ��һ��IPv6ǰ׺����������Pdn��ַ IPv6��ַǰ8���ֽ� */
    NAS_ESM_MEM_CPY(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV6Addr,
                    pstIpv6Notify->astIpv6PrefixArray[0].aucPrefix,
                    pstIpv6Notify->astIpv6PrefixArray[0].ucPrefixLen);

    /* ����ID_ESM_ERABM_MDF_IND��Ϣ */
    NAS_ESM_SndEsmRabmMdfIndMsg((VOS_UINT32)ucEpsbId);

   /* ��SM���ͳ����޸���Ϣ */
    NAS_ESM_SndSmEspBearerMdfIndMsg((VOS_UINT32)ucEpsbId);

}
/*lint +e961*/
/*lint +e960*/

/* niuxiufan DT begin */

/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_GetActPdpInfo
(
        NAS_OM_ACT_PDP_INFO_STRU   *pActPdpInfo
)
{
    VOS_UINT32          ulEpsbId = NAS_ESM_MIN_EPSB_ID;
    VOS_UINT32          ulActEpsbNum = 0;

    for (ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ESM_BEARER_STATE_ACTIVE ==
            NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->enBearerCntxtState)
        {
            pActPdpInfo->stEpsbInfo[ulActEpsbNum].ulEpsbId = ulEpsbId;
            pActPdpInfo->stEpsbInfo[ulActEpsbNum].enBearerType =
                            NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->enBearerCntxtType;

            if ( NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpApn)
            {
                NAS_ESM_MEM_CPY(&(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stApn),
                                &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU));
            }

            if (NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpPdnAddr)
            {

                NAS_ESM_MEM_CPY(&(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stIpAddr),
                                &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stPdnAddrInfo),
                                sizeof(APP_ESM_IP_ADDR_STRU));
            }

            if (NAS_ESM_OP_TRUE == NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->bitOpEpsQos)
            {

                NAS_ESM_MEM_CPY(&(pActPdpInfo->stEpsbInfo[ulActEpsbNum].stSdfQosInfo),
                                &(NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId)->stEpsQoSInfo.stQosInfo),
                                sizeof(APP_ESM_EPS_QOS_INFO_STRU));
            }

            ulActEpsbNum++;

        }
    }

    pActPdpInfo->ulActEpsbNum = ulActEpsbNum;

}

/*****************************************************************************
 Function Name   : NAS_ESM_AppQueryActPdpInfoMsgProc
 Description     : ����APP��ѯ��̬PDP��Ϣ����Ϣ
 Input           : VOS_VOID *pRcvMsg
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-09-21  Draft Enact
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_AppQueryActPdpInfoMsgProc
(
        const VOS_VOID   *pRcvMsg
)
{
    APP_ESM_INQ_PDP_INFO_REQ_STRU    *pAppQueryMsg;
    APP_ESM_INQ_PDP_INFO_CNF_STRU    *pAppCnfMsg;
    VOS_UINT32                        ulOpId;

    pAppQueryMsg=(APP_ESM_INQ_PDP_INFO_REQ_STRU*)pRcvMsg;

    if (pAppQueryMsg->enCmd == DT_CMD_STOP)
    {
        g_ulRptPdpStatus  = APP_ESM_DT_REPORT_STATUS_CLOSE;
    }
    else
    {
        g_ulRptPdpStatus  = APP_ESM_DT_REPORT_STATUS_OPEN;
    }

    /*�õ���Ϣ��ָʾ��ulOpId*/
    ulOpId =pAppQueryMsg->ulOpId;


    /*����ռ䲢��������Ƿ�ɹ�*/
    pAppCnfMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_INQ_PDP_INFO_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pAppCnfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AppQueryActPdpInfoMsgProc:ERROR:APP->SM ,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_AppQueryActPdpInfoMsgProc_ENUM, LNAS_NULL_PTR);
        return;
    }


    /*��д��Ϣͷ*/
    /* OM�ںϣ�����͸����ϢCNF��REQ�е�usOriginalId��usTerminalId�����Ӧ�����ܵߵ� */
    NAS_ESM_WRITE_APP_DT_CNF_MSG_HEAD(pAppCnfMsg,ID_APP_ESM_DT_INQ_PDP_INFO_CNF,\
                              pAppQueryMsg->usOriginalId,\
                              pAppQueryMsg->usTerminalId,\
                              pAppQueryMsg->ulSN);
    /*��װ��Ϣ����*/
    pAppCnfMsg->ulOpId = ulOpId;

    pAppCnfMsg->ulRslt = APP_SUCCESS;

#if (VOS_OS_VER != VOS_WIN32)
    if (1 == g_ulNasEsmOmMsgHookFlag)
    {
        (VOS_VOID)LTE_MsgHook((VOS_VOID *)pAppCnfMsg);
    }
#endif
    /*������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pAppCnfMsg);

    NAS_ESM_ReportActPdpInfo();

}

/* niuxiufan DT end */

VOS_VOID  NAS_ESM_InitLocalIpsupportInfo(VOS_VOID)
{
    LNAS_LMM_NV_NAS_LOCALIP_CAP_STRU    stNasLocalIpCap;
    VOS_UINT32                          ulRslt;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    usDataLen = sizeof(LNAS_LMM_NV_NAS_LOCALIP_CAP_STRU);

    pData                               = (VOS_VOID *)&(stNasLocalIpCap);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_PS_LOCALIP_CAP,
                                        pData,
                                        &usDataLen);

    if(ulRslt == VOS_OK)
    {
        if (VOS_TRUE == stNasLocalIpCap.bitOpLocalIpCap)
        {
            NAS_ESM_GetLocalIpSupFlag() = stNasLocalIpCap.ulLocalIpCap;
        }
    }
    else
    {
        NAS_ESM_GetLocalIpSupFlag() = NAS_ESM_FUN_CTRL_OFF;
    }
}



VOS_UINT32 NAS_ESM_SaveAppNdisConnInfo(VOS_VOID *pRcvMsg)
{
    VOS_UINT32                          ulRslt;
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT16                          usOriginalId        = NAS_ESM_NULL;
    VOS_UINT16                          usTerminalId        = NAS_ESM_NULL;
    VOS_UINT32                          ulCidRecv           = NAS_ESM_NULL;
    VOS_UINT32                          ulOpId              = NAS_ESM_NULL;
    APP_ESM_NDISCONN_REQ_STRU          *pAppMsg;

    pAppMsg = (APP_ESM_NDISCONN_REQ_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG1("NAS_ESM_SaveAppNdisConnInfo is entered.", pAppMsg->ulCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, LNAS_ENTRY, pAppMsg->ulCid);

    /*ȡ����Ϣ�а���CID����*/
    ulCidRecv=pAppMsg->ulCid;

    /*����Ϣ��ȡ�����ι��̵�ulOPID����*/
    ulOpId=pAppMsg->ulOpId;

    /*����Ϣ��ȡ��MID����*/
    usOriginalId = pAppMsg->usOriginalId;
    usTerminalId = pAppMsg->usTerminalId;

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET((VOS_VOID*)&stEsmAppCnfMsg, 0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));
    stEsmAppCnfMsg.bitOpEpsbId = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulRst = NAS_ESM_FAILURE;
    stEsmAppCnfMsg.ulCId = ulCidRecv;
    stEsmAppCnfMsg.ulOpId= ulOpId;
    stEsmAppCnfMsg.usOriginalId = usOriginalId;
    stEsmAppCnfMsg.usTerminalId = usTerminalId;

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpApn)
    {
        ulRslt = NAS_ESM_AppCgdcontOrNdisConnSetApn(pAppMsg->ulCid,
                                                    APP_ESM_PARA_SETTING,
                                                    pAppMsg->stApnInfo);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_SaveAppNdisConnInfo: APN ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, ESM_APN_ERROR, ulRslt);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpGwAuth)
    {
        ulRslt = NAS_ESM_AppNdisConnSetGwAuthInfo(pRcvMsg);
        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: GwAuth ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, LNAS_ERROR, ulRslt);

            /*��װ�ṹ��pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }

    if (NAS_ESM_OP_TRUE == pAppMsg->bitOpPdnType)
    {
        ulRslt = NAS_ESM_AppCgdconntOrNDISconnSetPdnType(pAppMsg->ulCid,
                                                        APP_ESM_PARA_SETTING,
                                                        pAppMsg->enPdnType,
                                                        pAppMsg->bitOpIpv4AddrAlloc,
                                                        pAppMsg->enIpv4AddrAlloc);

        if (APP_SUCCESS != ulRslt)
        {
            NAS_ESM_LOG1("NAS_ESM_AppNdisconnMsgProc: Pdn ERROR, ", ulRslt);
            TLPS_PRINT2LAYER_INFO1(NAS_ESM_SaveAppNdisConnInfo_ENUM, ESM_PDN_TYPE_ERROR, ulRslt);
            /*��װ�ṹ��pstEsmAppCnfMsg*/
            stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
            stEsmAppCnfMsg.ulErrorCode = ulRslt;

            /*ESM ��APP����ID_APP_ESM_NDISCONN_CNF��Ϣ��ͨ�潨��ʧ��*/
            /*lint -e433*/
            NAS_ESM_SndEsmAppNdisConnCnfMsg(&stEsmAppCnfMsg);
            /*lint +e433*/
            return NAS_ESM_FAILURE;
        }
    }
    return NAS_ESM_SUCCESS;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

