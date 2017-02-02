


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmEsmMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMESMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMESMMSGPROC_C
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
VOS_VOID NAS_ERABM_EsmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU                 *pSmMsg;

    pSmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_EsmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_EsmMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pSmMsg->ulMsgName)
    {
        /*����յ�����ESM_ERABM_ACT_IND��Ϣ������NAS_ERABM_RcvRabmEsmActInd����*/
        case ID_ESM_ERABM_ACT_IND:
            NAS_ERABM_RcvRabmEsmActInd((ESM_ERABM_ACT_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_MDF_IND��Ϣ������NAS_ERABM_RcvRabmEsmMdfInd����*/
        case ID_ESM_ERABM_MDF_IND:
            NAS_ERABM_RcvRabmEsmMdfInd((ESM_ERABM_MDF_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_DEACT_IND��Ϣ������NAS_ERABM_RcvRabmEsmDeactInd����*/
        case ID_ESM_ERABM_DEACT_IND:
            NAS_ERABM_RcvRabmEsmDeactInd((ESM_ERABM_DEACT_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_REL_IND��Ϣ������NAS_ERABM_RcvRabmEsmRelInd����*/
        case ID_ESM_ERABM_REL_IND:
            NAS_ERABM_RcvRabmEsmRelInd();
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_EsmMsgDistr:WARNING:SM->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_EsmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }

    /*�������ؼ�������ֻ��һ�����ؼ���жϸó������û������TFT,��¼�ó��غ�*/
    NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb();

    return;
}
VOS_VOID  NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb( VOS_VOID )
{

    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;
    VOS_UINT32                          ulTempActEpsbId = NAS_ERABM_NULL;
    VOS_UINT32                          ulActEpsbNum = NAS_ERABM_NULL;

    /*�������ؼ������¼������صĸ��������һ��������غ�*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            ulTempActEpsbId = ulEpsbId;
            ulActEpsbNum++;
        }
    }

    /*���������������� 1���򲻼�¼�κγ��أ�����*/
    if(NAS_ERABM_ACT_EPSB_NUM_ONE != ulActEpsbNum)
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_INFO_LOG("NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb:the active EpsbNum is not one!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb_ENUM, LNAS_ERABM_ActiveEpsbNumIsNotOne);
        return;
    }

    /*���ֻ��һ��������أ��жϸó����������������TFT����¼���غ�*/
    if(PS_FALSE == NAS_ERABM_IsExistUplinkPfinTft(ulTempActEpsbId))
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(ulTempActEpsbId);
    }
    else
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(NAS_ERABM_ILL_EPSB_ID);
    }

    return;
}
VOS_VOID NAS_ERABM_SaveUeIpAddr(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId)
{
    VOS_UINT8                           ucIpType   = ESM_ERABM_PDN_TYPE_IPV4;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SaveUeIpAddr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_SaveUeIpAddr_ENUM, LNAS_ENTRY);

    ucIpType = pRcvMsg->stPdnAddr.ucIpType;

    pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);

    switch(ucIpType)
    {
        /*����IPv4��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV4:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV4;
            NAS_ERABM_MEM_CPY(pstPdnAddr->aucIpV4Addr, pRcvMsg->stPdnAddr.aucIpV4Addr,\
                                                              APP_MAX_IPV4_ADDR_LEN);
            break;

        /*����IPv6��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV6:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV6;
            NAS_ERABM_MEM_CPY(pstPdnAddr->aucIpV6Addr, pRcvMsg->stPdnAddr.aucIpV6Addr,\
                                                              APP_MAX_IPV6_ADDR_LEN);
            break;

        /*���δ��IPV4��IPV6��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV4_IPV6:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV4_IPV6;
            NAS_ERABM_MEM_CPY(pstPdnAddr->aucIpV4Addr, pRcvMsg->stPdnAddr.aucIpV4Addr,\
                                                              APP_MAX_IPV4_ADDR_LEN);
            NAS_ERABM_MEM_CPY(pstPdnAddr->aucIpV6Addr, pRcvMsg->stPdnAddr.aucIpV6Addr,\
                                                              APP_MAX_IPV6_ADDR_LEN);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_SaveUeIpAddr:WARNING:ESM->RABM Invalid IP Type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_SaveUeIpAddr_ENUM, LNAS_ERABM_InvalidIPType);
            NAS_ERABM_MEM_SET((VOS_VOID*)pstPdnAddr,
                        0,
                        sizeof(APP_ESM_IP_ADDR_STRU));
            break;
    }
}


VOS_VOID NAS_ERABM_SaveEpsbActInfo(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId )
{
    VOS_UINT32                          ulEpsTftPfNum           = pRcvMsg->ulTftPfNum;
    VOS_UINT32                          ulTftPfCnt              = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU               *pstTftPf                = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SaveEpsbActInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_SaveEpsbActInfo_ENUM, LNAS_ENTRY);

    if(ulEpsTftPfNum > ESM_ERABM_MAX_PF_NUM_IN_BEARER)
    {
        ulEpsTftPfNum = ESM_ERABM_MAX_PF_NUM_IN_BEARER;
    }

    /*����IP��ַ*/
    NAS_ERABM_SaveUeIpAddr(pRcvMsg, ulEpsbId);

    /* ��¼����������������PF��Ϣ */
    for(ulTftPfCnt = 0; ulTftPfCnt < ulEpsTftPfNum; ulTftPfCnt++)
    {
        pstTftPf = NAS_ERABM_GetEpsbTftAddr(ulEpsbId, ulTftPfCnt);

        /* ������PF��Ϣ */
        NAS_ERABM_MEM_CPY(pstTftPf, &pRcvMsg->astTftPf[ulTftPfCnt], sizeof(ESM_ERABM_TFT_PF_STRU));

        /* Ϊ�˷�ֹNDIS�������ݰ����͵��տڣ�NDIS�������ݰ��Ĺ����������ȼ�
           Ҫ���ڿտ���Ϣ�е�TFT�����ȼ���Ŀǰ���ȼ�0-5Ԥ����NDIS�������ݰ���
           ���������ȼ� */
        pstTftPf->ucPrecedence += NAS_ERABM_IPF_UL_NDIS_PRIORITY_NUM;
    }

    /* ���ó��ذ�����PF���� */
    NAS_ERABM_SetEpsbTftPfNum(ulEpsbId, ulEpsTftPfNum);

    /*��¼���������ļ���״̬*/
    NAS_ERABM_SetEpsbStateInfo(ulEpsbId, NAS_ERABM_EPSB_ACTIVE);

    NAS_ERABM_SetEpsbBearerType(ulEpsbId, (pRcvMsg->enBearerCntxtType));
    NAS_ERABM_SetEpsbLinkedEpsbId(ulEpsbId, (pRcvMsg->ulLinkedEpsbId));
    NAS_ERABM_SetEpsbQCI(ulEpsbId, (pRcvMsg->ucQCI));

    /* �����һ�����ؼ����Ҳ��ǻ���ģʽʱ������enUlNdisFilterValidFlagΪ��Ч */
    if ((1 == NAS_ERABM_GetActiveEpsBearerNum())
        && (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode()))
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_VALID);
    }
}
VOS_VOID NAS_ERABM_ClearEpsbResource( VOS_UINT32 ulEpsbId )
{
    VOS_UINT32                          ulEpsTftPfNum   = NAS_ERABM_NULL;
    VOS_UINT32                          ulTftPfCnt      = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU               *pstTftPf        = VOS_NULL_PTR;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr      = VOS_NULL_PTR;

    NAS_ERABM_SetEpsbStateInfo(ulEpsbId, NAS_ERABM_EPSB_INACTIVE);

    pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);

    ulEpsTftPfNum = NAS_ERABM_GetEpsbTftPfNum(ulEpsbId);

    /* ��ճ��ذ���������PF��Ϣ��PF��־ */
    for(ulTftPfCnt = 0; ulTftPfCnt < ulEpsTftPfNum; ulTftPfCnt++)
    {
         pstTftPf = NAS_ERABM_GetEpsbTftAddr(ulEpsbId, ulTftPfCnt);

        /* ���PF��Ϣ */
        NAS_ERABM_MEM_SET(pstTftPf, NAS_ERABM_NULL, sizeof(ESM_ERABM_TFT_PF_STRU));
    }

    NAS_ERABM_SetEpsbTftPfNum(ulEpsbId, NAS_ERABM_NULL);

    NAS_ERABM_MEM_SET(pstPdnAddr, NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
}



VOS_VOID  NAS_ERABM_RcvRabmEsmActInd(const ESM_ERABM_ACT_IND_STRU *pRcvMsg )
{
    VOS_UINT32               ulEpsbId          = 0;                         /*������¼EPS���ؼ�����е�EPSID*/

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmActInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ENTRY);

    /*�ҵ���Ӧ��EPS����*/
    ulEpsbId = pRcvMsg->ulEpsId;

    (VOS_VOID)VOS_TaskLock();

    /*�����Ӧ��EPS���ص������Ϣ*/
    NAS_ERABM_ClearEpsbResource(ulEpsbId);

    /*��¼��Ӧ�Ĳ���*/
    NAS_ERABM_SaveEpsbActInfo(pRcvMsg, ulEpsbId);

    (VOS_VOID)VOS_TaskUnlock();

    /* ��CDS����CDS_ERABM_RAB_CREATE_IND */
    NAS_ERABM_SndErabmCdsRabCreatInd(ulEpsbId);

    /*�ж��Ƿ��ڵȴ����ؼ���*/
    if (NAS_ERABM_WAIT_EPSB_ACT_MSG == NAS_ERABM_GetWaitEpsbActSign())
    {
        /* �ж��Ƿ����DRB�ѽ�������������EPS������δ��������*/
        if (NAS_ERABM_FAILURE == NAS_ERABM_HasDrbWithoutRelatingEpsBear())
        {
            /*ֹͣ�����ȴ���ʱ��*/
            NAS_ERABM_TimerStop(NAS_ERABM_WAIT_EPSB_ACT_TIMER);

            /* ��ESM������״̬��Ϣ */
            NAS_ERABM_InformEsmBearerStatus(pRcvMsg->ucSessionId);

            /*����ȴ���ʶ*/
            NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);
        }
    }

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }
    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmMdfInd()
 Description     : RABMģ��ESM_ERABM_MDF_IND_STRU��Ϣ�ַ�����
 Input           : ESM_ERABM_MDF_IND_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.RabmStru      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmMdfInd(const ESM_ERABM_MDF_IND_STRU *pRcvMsg )
{
    VOS_UINT32                         ulEpsbId = 0;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmMdfInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ENTRY);

    /*�ҵ�Ҫ�޸ĵ�EPS����*/
    ulEpsbId = pRcvMsg->ulEpsId;
    /* ��ֹ�ڱ��������Ӧ���������У��ϲ�����CDS�������񣬵��ýӿڻ�ȡ���غ����ڳ�����Ϣ��û�б����굼�»�ȡ���غ�ʧ�ܣ������ڴ˴�������  */
    (VOS_VOID)VOS_TaskLock();

    /*�����Ӧ��EPS���ص������Ϣ*/
    NAS_ERABM_ClearEpsbResource(ulEpsbId);

    /*��¼��Ӧ�Ĳ���*/
    NAS_ERABM_SaveEpsbActInfo(pRcvMsg, ulEpsbId);

    (VOS_VOID)VOS_TaskUnlock();

    /* ��CDS����CDS_ERABM_RAB_CREATE_IND_STRU */
    NAS_ERABM_SndErabmCdsRabCreatInd(ulEpsbId);

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
}


/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmDeactInd()
 Description     : RABMģ��ESM_ERABM_DEACT_IND_STRU��Ϣ�ַ�����
 Input           : ESM_ERABM_DEACT_IND_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.yangqianhui      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmDeactInd(const ESM_ERABM_DEACT_IND_STRU *pRcvMsg )
{
    VOS_UINT32          ulEpsbId   = 0;
    VOS_UINT32          ulEpsIdCnt = 0;
    VOS_UINT32          ulLoop     = 0;


    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmDeactInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ENTRY);

    /*��ȡȥ����ĳ�����*/
    ulEpsIdCnt = pRcvMsg->ulEpsIdNum;

    /*�ҵ�Ҫȥ�����EPS����*/
    for (ulLoop = 0; ulLoop < ulEpsIdCnt; ulLoop++)
    {
        ulEpsbId = pRcvMsg->aulEpsId[ulLoop];

        /* ��CDS����CDS_ERABM_RAB_RELEASE_IND_STRU */
        NAS_ERABM_SndErabmCdsRabReleaseInd(ulEpsbId);

        /*RABM�ͷ�������ص���Դ*/
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
    }

    /* ������ر��ͷţ�����enUlNdisFilterValidFlagΪ��Ч */
    if (0 == NAS_ERABM_GetActiveEpsBearerNum())
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

        /* lihong00150010 erabm code begin */
        /* ֪ͨCDS�ͷŻ�������ݰ� */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();
        /* lihong00150010 erabm code end */
    }

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmRelInd()
 Description     : RABMģ��ESM_ERABM_REL_IND_STRU��Ϣ�ַ�����
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.RabmStru      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmRelInd( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;


    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ENTRY);

    /* ֪ͨCDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* ��CDS����CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }

    /*�ͷ�������Դ���ص�������ʼ�����״̬*/
    NAS_ERABM_ClearRabmResource();

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

}



VOS_VOID NAS_ERABM_SndRabmEsmRelReq( VOS_VOID )
{
    ESM_ERABM_REL_REQ_STRU    *pstRelReq = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRelReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ESM_ERABM_REL_REQ_STRU));
    if (VOS_NULL_PTR == pstRelReq)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmRelReq:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_MSG_ENTITY(pstRelReq), NAS_ERABM_NULL, NAS_ERABM_GET_MSG_LENGTH(pstRelReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_ESM_MSG_HEAD(pstRelReq,ID_ESM_ERABM_REL_REQ);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstRelReq);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEsmBearerStatusReq
 Description     : ��ESM���ͽ���rb��EpsbId��Ϣ
 Input           : VOS_UINT32 *pulEpsbId
                   VOS_UINT32 ulEpsbIdNum
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-3-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEsmBearerStatusReq(const VOS_UINT32 *pulEpsbId,
                                                              VOS_UINT32 ulEpsbIdNum,
                                                              VOS_UINT8 ucSessionId)
{
    ESM_ERABM_BEARER_STATUS_REQ_STRU    *pstBearerStatusReq  = VOS_NULL_PTR;

    /*��ڲ������*/
    if ((VOS_NULL_PTR == pulEpsbId) || (ulEpsbIdNum > NAS_ERABM_MAX_EPSB_NUM))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmBearerStatusReq:ERROR:Input para error!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_SndRabmEsmBearerStatusReq_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstBearerStatusReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ESM_ERABM_BEARER_STATUS_REQ_STRU));
    if ( VOS_NULL_PTR == pstBearerStatusReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmBearerStatusReq:ERROR:Alloc msg fail!" );
        return;
    }

    NAS_ERABM_MEM_SET(NAS_ERABM_GET_MSG_ENTITY(pstBearerStatusReq), NAS_ERABM_NULL,\
                     NAS_ERABM_GET_MSG_LENGTH(pstBearerStatusReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_ESM_MSG_HEAD(pstBearerStatusReq, ID_ESM_ERABM_BEARER_STATUS_REQ);

    /*��д��Ϣʵ��*/
    pstBearerStatusReq->ucSessionId = ucSessionId;
    pstBearerStatusReq->ulEpsIdNum = ulEpsbIdNum;
    NAS_ERABM_MEM_CPY((VOS_UINT8*)pstBearerStatusReq->aulEpsId, (VOS_UINT8*)pulEpsbId,
              (pstBearerStatusReq->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstBearerStatusReq);

}
/*lint +e961*/
/*lint +e960*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

