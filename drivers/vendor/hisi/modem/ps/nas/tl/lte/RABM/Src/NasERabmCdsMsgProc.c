


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmCdsMsgProc.h"
#include  "CdsErabmInterface.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmMain.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmEmmMsgProc.h"
#include  "NasEsmPublic.h"


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASERABMCDSMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASERABMCDSMSGPROC_C
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

VOS_VOID NAS_ERABM_CdsMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU                 *pSmMsg;

    pSmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_CdsMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_CdsMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pSmMsg->ulMsgName)
    {
        /*����յ�����CDS_ERABM_SERVICE_NOTIFY��Ϣ������NAS_ERABM_RcvCdsErabmServiceNotify����*/
        case ID_CDS_ERABM_SERVICE_NOTIFY:
            NAS_ERABM_RcvCdsErabmServiceNotify((CDS_ERABM_SERVICE_NOTIFY_STRU *) pRcvMsg);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_CdsMsgDistr:WARNING:CDS->ERABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_CdsMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }

    return;
}

/* lihong00150010 emergency tau&service begin */
/*****************************************************************************
 Function Name   : NAS_ERABM_IsEmcService
 Description     : �ж��Ƿ��ǽ���ҵ�����ݰ�
 Input           : ulEpsbId----------------���غ�
 Output          : None
 Return          : VOS_UINT32

 History         :
     1.lihong00150010      2012-12-14  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ERABM_IsEmcService
(
    VOS_UINT8                           ucEpsbId
)
{
    if ((ucEpsbId < NAS_ERABM_MIN_EPSB_ID) || (ucEpsbId > NAS_ERABM_MAX_EPSB_ID))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_IsEmcService:EpsbId is illegal!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_IsEmcService_ENUM, LNAS_ERABM_EpsbIdIsIllegal);

        return VOS_FALSE;
    }

    if (ESM_ERABM_BEARER_TYPE_EMERGENCY == NAS_ERABM_GetEpsbBearerType(ucEpsbId))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvCdsErabmServiceNotify
 Description     : ERABMģ��CDS_ERABM_SERVICE_NOTIFY��Ϣ�ַ�����
 Input           : CDS_ERABM_SERVICE_NOTIFY_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
     1.lihong00150010      2011-12-06  Draft Enact
     2.lihong00150010      2012-12-14  Modify:Emergency

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvCdsErabmServiceNotify
(
    const CDS_ERABM_SERVICE_NOTIFY_STRU    *pRcvMsg
)
{
    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvCdsErabmServiceNotify is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvCdsErabmServiceNotify_ENUM, LNAS_ENTRY);

    (VOS_VOID)pRcvMsg;
    /* ����ǲ��Կ����ҵ�ǰLTE���ڹ���״̬���յ�IPV6��֮���ֱ�����. */
    if(NAS_ERABM_L_MODE_STATUS_SUSPENDED == NAS_ERABM_GetLModeStatus())
    {
        if(PS_SUCC == LPS_OM_IsTestMode())
        {
            /* ֪ͨCDS�ͷŻ�������ݰ� */
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvCdsErabmServiceNotify_ENUM, LNAS_EMM_LTE_SUSPEND);
            NAS_ERABM_SndErabmCdsFreeBuffDataInd();
        }
        return ;
    }

    /* ����û�ж�Ӧ��DRB�ĳ����£����Ҷ�ʱ��û������ʱ����EMM�������� */
    if (NAS_ERABM_SUCCESS == NAS_ERABM_IsAllActtiveBearerWithoutDrb())
    {
        if(NAS_ERABM_TIMER_STATE_STOPED != NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_RB_REEST_TIMER))
        {
            NAS_ERABM_NORM_LOG("NAS_ERABM_RcvCdsErabmServiceNotify:Reest timer started!" );
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvCdsErabmServiceNotify_ENUM, LNAS_ERABM_ReestTimerStarted);
            return ;
        }

        /*����EMM_ERABM_REEST_REQ��Ϣ�����÷�����������*/
        NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_INIT);
        /* lihong00150010 emergency tau&service begin */
        if (VOS_TRUE == NAS_ERABM_IsEmcService(pRcvMsg->ucRabId))
        {
            NAS_ERABM_SndRabmEmmReestReq(VOS_TRUE);

            NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                    NAS_ERABM_WAIT_RB_REEST_TIMER,
                                    VOS_TRUE);
        }
        else
        {
            NAS_ERABM_SndRabmEmmReestReq(VOS_FALSE);

            NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_RB_REEST_LENGTH,
                                    NAS_ERABM_WAIT_RB_REEST_TIMER,
                                    VOS_FALSE);
        }
        /* lihong00150010 emergency tau&service end */
        /* ������: ��¼Mo Ser����ʱ�� */
        NAS_EMM_SaveMoSerStartTimeStamp();
    }
    else
    {
        NAS_ERABM_NORM_LOG("NAS_ERABM_RcvCdsErabmServiceNotify:Already in Connect state!" );
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvCdsErabmServiceNotify_ENUM, LNAS_ERABM_AlreadyInConnectState);
        NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

        /* ֪ͨCDS�������ι��� */
        NAS_ERABM_SndErabmCdsSndBuffDataInd(CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
    }
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ERABM_SndErabmCdsSndBuffDataInd
(
    CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32   enSndBuffDataAllowedType
)
{

    ERABM_CDS_SEND_BUFF_DATA_IND_STRU  *pstSndBuffDataInd = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstSndBuffDataInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ERABM_CDS_SEND_BUFF_DATA_IND_STRU));
    if (VOS_NULL_PTR == pstSndBuffDataInd)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndErabmCdsSndBuffDataInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(  NAS_ERABM_GET_MSG_ENTITY(pstSndBuffDataInd),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstSndBuffDataInd));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_CDS_MSG_HEAD(pstSndBuffDataInd,ID_ERABM_CDS_SEND_BUFF_DATA_IND);

    pstSndBuffDataInd->enSndBuffDataAllowedType = enSndBuffDataAllowedType;

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstSndBuffDataInd);

}


VOS_VOID NAS_ERABM_SndErabmCdsFreeBuffDataInd( VOS_VOID )
{

    ERABM_CDS_FREE_BUFF_DATA_IND_STRU  *pstFreeBuffDataInd = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstFreeBuffDataInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ERABM_CDS_FREE_BUFF_DATA_IND_STRU));
    if (VOS_NULL_PTR == pstFreeBuffDataInd)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndErabmCdsSndBuffDataInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(  NAS_ERABM_GET_MSG_ENTITY(pstFreeBuffDataInd),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstFreeBuffDataInd));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_CDS_MSG_HEAD(pstFreeBuffDataInd,ID_ERABM_CDS_FREE_BUFF_DATA_IND);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstFreeBuffDataInd);

}


VOS_VOID NAS_ERABM_SndErabmCdsRabCreatInd( VOS_UINT32 ulEpsbId )
{
#if (VOS_OS_VER != VOS_WIN32)

    CDS_ERABM_RAB_CREATE_IND_STRU  *pstRabCreatInd = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRabCreatInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(CDS_ERABM_RAB_CREATE_IND_STRU));

    if (VOS_NULL_PTR == pstRabCreatInd)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndErabmCdsRabCreatInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(  NAS_ERABM_GET_MSG_ENTITY(pstRabCreatInd),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstRabCreatInd));

    /* ��ֵQCI */
    pstRabCreatInd->enQci = NAS_ERABM_GetEpsbQCI(ulEpsbId);


    /*��ֵ EpsbId������EPsbId */
    pstRabCreatInd->ucRabId = (VOS_UINT8)ulEpsbId;
    if (ESM_ERABM_BEARER_TYPE_DEDICATED == NAS_ERABM_GetEpsbBearerType(ulEpsbId))
    {
        pstRabCreatInd->ucLinkRabId = (VOS_UINT8)NAS_ERABM_GetEpsbLinkedEpsbId(ulEpsbId);
    }
    else
    {
        pstRabCreatInd->ucLinkRabId = pstRabCreatInd->ucRabId;
    }

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_CDS_MSG_HEAD(pstRabCreatInd,ID_QOS_FC_ERABM_RAB_CREATE_IND);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstRabCreatInd);
#endif
}

VOS_VOID NAS_ERABM_SndErabmCdsRabReleaseInd( VOS_UINT32 ulEpsbId )
{
#if (VOS_OS_VER != VOS_WIN32)

    CDS_ERABM_RAB_RELEASE_IND_STRU  *pstRabReleaseInd = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRabReleaseInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(CDS_ERABM_RAB_RELEASE_IND_STRU));
    if (VOS_NULL_PTR == pstRabReleaseInd)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndErabmCdsRabReleaseInd:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(  NAS_ERABM_GET_MSG_ENTITY(pstRabReleaseInd),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstRabReleaseInd));

    /*��ֵ EpsbId*/
    pstRabReleaseInd->ucRabId = (VOS_UINT8)ulEpsbId;


    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_CDS_MSG_HEAD(pstRabReleaseInd,ID_QOS_FC_ERABM_RAB_RELEASE_IND);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstRabReleaseInd);
#endif
}
VOS_UINT32 CDS_ERABM_GetIpFragEpsbId
(
    VOS_UINT8                           *pucEpsbId,
    TTF_MEM_ST                          *pstIpFrag,
    VOS_UINT32                           ulIpFragLen
)
{
    VOS_UINT8                          *pucIpv4Data = VOS_NULL_PTR;
    VOS_UINT8                          *pstDataAddr = VOS_NULL_PTR;
    VOS_UINT8                          *pucIpv6Data = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstIpFragTmp= pstIpFrag;
    VOS_UINT8                           ucIpVersion = NAS_ERABM_NULL;
    VOS_UINT8                           ucRslt      = NAS_ERABM_NULL;
    VOS_UINT8                           ucBearerIdTmp = NAS_ERABM_NULL;

    /* ��������Ϸ��Լ�� */
    if (VOS_NULL_PTR == pucEpsbId)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetIpFragEpsbId:pucEpsbId is NULL!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetIpFragEpsbId_ENUM, LNAS_ERABM_EpsbIdIsNULL);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == pstIpFragTmp)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetIpFragEpsbId:pstIpFrag is NULL!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetIpFragEpsbId_ENUM, LNAS_ERABM_IpFragIsNULL);
        return PS_FAIL;
    }

    if (NAS_ERABM_NULL == ulIpFragLen)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetIpFragEpsbId:ulIpFragLen is zero!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetIpFragEpsbId_ENUM, LNAS_ERABM_IpFragLenIsZero);
        return PS_FAIL;
    }

    pstDataAddr = pstIpFragTmp->pData;

    /* ����IP��ͷ��ȡIP���� */
    ucIpVersion = NAS_ERABM_GetIpVersion(pstDataAddr);

    if (NAS_ERABM_IP_VERSION_4 == ucIpVersion)
    {
        /* ����IPV4��ͷ���洢ԴIPV4��ַ��Ŀ��IPV4��ַ��identifier */
        pucIpv4Data = NAS_ERABM_GET_IP_HEADER_BUFFER();

        NAS_ERABM_DecodeIpV4Data(pstDataAddr, (NAS_ERABM_IPV4_HEADER_STRU *)pucIpv4Data);

        /* ��������ȱʡ���أ�����ԴIP��ַƥ��ĳ��� */
        ucRslt = NAS_ERABM_GetSrcIpv4MatchedDeftBearerId((NAS_ERABM_IPV4_HEADER_STRU *)pucIpv4Data, &ucBearerIdTmp);

        if (NAS_ERABM_SUCCESS == ucRslt)
        {
            *pucEpsbId = ucBearerIdTmp;
            return PS_SUCC;
        }

        *pucEpsbId = NAS_ERABM_IPF_INVALID_BEARER_ID;
        return PS_FAIL;
    }
    else
    {
        /* ����IPV6��ͷ���洢ԴIPV6��ַ */
        pucIpv6Data = NAS_ERABM_GET_IP_HEADER_BUFFER();

        NAS_ERABM_DecodeIpV6Data(pstDataAddr, (NAS_ERABM_IPV6_HEADER_STRU *)pucIpv6Data);

        /* ��������ȱʡ���أ�����ԴIP��ַƥ��ĳ��� */
        ucRslt = NAS_ERABM_GetSrcIpv6MatchedDeftBearerId(   (NAS_ERABM_IPV6_HEADER_STRU *)pucIpv6Data,
                                                            &ucBearerIdTmp);

        if (NAS_ERABM_SUCCESS == ucRslt)
        {
            *pucEpsbId = ucBearerIdTmp;
            return PS_SUCC;
        }

        *pucEpsbId = NAS_ERABM_IPF_INVALID_BEARER_ID;
        return PS_FAIL;
    }
}


CDS_ERABM_TRANSFER_RESULT_ENUM_UINT32 CDS_ERABM_GetDrbId
(
    VOS_UINT8                           ucEpsbId,
    VOS_UINT8                          *pucDrbId
)
{
     /* �����յ����ݰ�����ͳ�� */
    NAS_ERABM_AddUlReceivePackageNum();

    /* ��������Ϸ��Լ�� */
    if (VOS_NULL_PTR == pucDrbId)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetDrbId:pucDrbId is NULL!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetDrbId_ENUM, LNAS_ERABM_DrbIdIsNULL);

        /* ���ж������ݰ�����ͳ�� */
        NAS_ERABM_AddUlDiscardPackageNum();

        return PS_FAIL;
    }

    if ((ucEpsbId < NAS_ERABM_MIN_EPSB_ID) || (ucEpsbId > NAS_ERABM_MAX_EPSB_ID))
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetDrbId:EpsbId is illegal!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetDrbId_ENUM, LNAS_ERABM_EpsbIdIsIllegal);

        /* ���ж������ݰ�����ͳ�� */
        NAS_ERABM_AddUlDiscardPackageNum();

        return CDS_ERABM_TRANSFER_RESULT_FAIL;
    }

    if (NAS_ERABM_RB_CONNECTED == NAS_ERABM_GetRbStateInfo(ucEpsbId))
    {
        *pucDrbId = (VOS_UINT8)NAS_ERABM_GetEpsbRbIdInfo(ucEpsbId);

        /* �������з��������ݰ��� */
        NAS_ERABM_AddUlSendPackageNum();

        /* ���ӳ������з��������ݰ��� */
        NAS_ERABM_AddBearerSendPackageNum((VOS_UINT32)ucEpsbId);

        return CDS_ERABM_TRANSFER_RESULT_SUCC;
    }
    else if(NAS_ERABM_RB_SUSPENDED == NAS_ERABM_GetRbStateInfo(ucEpsbId))
    {
        /* ������������������־*/
        NAS_ERABM_SetUpDataPending(EMM_ERABM_UP_DATA_PENDING);
        NAS_ERABM_LOG1("CDS_ERABM_GetDrbId:DRB_SUSPENDED, set data pending = ",NAS_ERABM_GetUpDataPending());
        TLPS_PRINT2LAYER_INFO1(CDS_ERABM_GetDrbId_ENUM, LNAS_UpDataPendingValue, NAS_ERABM_GetUpDataPending());

        *pucDrbId = (VOS_UINT8)NAS_ERABM_GetEpsbRbIdInfo(ucEpsbId);

        /* ��������Suspend�����ݰ��� */
        NAS_ERABM_AddUlSuspendPackageNum();

        /* ���ӳ�������Suspend�����ݰ��� */
        NAS_ERABM_AddBearerSuspendPackageNum((VOS_UINT32)ucEpsbId);

        return CDS_ERABM_TRANSFER_RESULT_DRB_SUSPEND;
    }
    else
    {
        /* �ж��Ƿ�������̬ */
        if (NAS_ERABM_SUCCESS == NAS_ERABM_IsAllActtiveBearerWithoutDrb())
        {
            /* ������������������־*/
            NAS_ERABM_SetUpDataPending(EMM_ERABM_UP_DATA_PENDING);
            NAS_ERABM_LOG1("CDS_ERABM_GetDrbId:AllActtiveBearerWithoutDrb, set data pending = ",NAS_ERABM_GetUpDataPending());
            TLPS_PRINT2LAYER_INFO2(CDS_ERABM_GetDrbId_ENUM, LNAS_UpDataPendingValue, NAS_ERABM_GetUpDataPending(),LNAS_FUNCTION_LABEL1);


            /* ��������IDLE�����ݰ��� */
             NAS_ERABM_AddUlIdlePackageNum();

            /* ���ӳ�������IDLE�����ݰ��� */
            NAS_ERABM_AddBearerIdlePackageNum((VOS_UINT32)ucEpsbId);

            return CDS_ERABM_TRANSFER_RESULT_IDLE;
        }

        /* ���ڵ�ǰ��������̬�������ض�Ӧ��DRB������������̬����ʱ�ȷ���
           CDS_ERABM_TRANSFER_RESULT_FAIL����CDS�ͷ��ڴ棬�����Ż�ʱ�ٷ���
           CDS_ERABM_TRANSFER_RESULT_DRB_NOT_EXIST����CDS���𻺴����ݰ���*/

        /* ���ж������ݰ�����ͳ�� */
        NAS_ERABM_AddUlDiscardPackageNum();

        /* �������ж������ݰ�����ͳ�� */
        NAS_ERABM_AddBearerDiscardPackageNum((VOS_UINT32)ucEpsbId);

        return APP_ERABM_TRANSFER_RESULT_FAIL;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_GetEpsbIdByDrbId
 Description     : ����DRB�Ż�ȡEPS���غ�
 Input           : ulRbId-------------------DRB��
 Output          : pulEpsbId----------------���غ�ָ��
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-12-06  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ERABM_GetEpsbIdByDrbId
(
    VOS_UINT32                           ulRbId,
    VOS_UINT32                          *pulEpsbId
)
{
    VOS_UINT32                     ulEpsbId   = NAS_ERABM_NULL;

    /*�ҵ�RBID��Ӧ��EPS����*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE != NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            continue;
        }

        if (NAS_ERABM_GetEpsbRbIdInfo(ulEpsbId) == ulRbId)
        {
            *pulEpsbId = ulEpsbId;
            return NAS_ERABM_SUCCESS;
        }
    }

    return NAS_ERABM_FAILURE;
}
/*lint +e961*/
/*lint +e960*/

VOS_UINT32 CDS_ERABM_GetDefaultEpsbId
(
    VOS_UINT8                           ucDrbId,
    VOS_UINT8                          *pucDeftEpsbId
)
{
    VOS_UINT32                           ulEpsbId = NAS_ERABM_NULL;

    if (VOS_NULL_PTR == pucDeftEpsbId)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetDefaultEpsbId:pucEpsbId is NULL!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetDefaultEpsbId_ENUM, LNAS_ERABM_EpsbIdIsNULL);
        return PS_FAIL;
    }

    /* ��ȡDRB�������غ� */
    if (NAS_ERABM_SUCCESS != NAS_ERABM_GetEpsbIdByDrbId(  ucDrbId,
                                                         &ulEpsbId))
    {
        NAS_ERABM_WARN_LOG("CDS_ERABM_GetDefaultEpsbId:NAS_ERABM_GetEpsbIdByDrbId failed!");
        TLPS_PRINT2LAYER_WARNING(CDS_ERABM_GetDefaultEpsbId_ENUM, LNAS_ERABM_GetEpsbIdByDrbId_Failed);

        return PS_FAIL;
    }

    /* �жϳ��������Ƿ�Ϊȱʡ */
    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(NAS_ERABM_GetEpsbBearerType(ulEpsbId)))
    {
        *pucDeftEpsbId = (VOS_UINT8)ulEpsbId;
    }
    else
    {
        *pucDeftEpsbId = (VOS_UINT8)NAS_ERABM_GetEpsbLinkedEpsbId(ulEpsbId);
    }

    return PS_SUCC ;
}


VOS_UINT32 CDS_ERABM_GetEpsbId
(
    VOS_UINT8                           ucDrbId,
    VOS_UINT8                          *pucEpsbId
)
{
    VOS_UINT32                           ulEpsbId = NAS_ERABM_NULL;

    if (VOS_NULL_PTR == pucEpsbId)
    {
        NAS_ERABM_ERR_LOG("CDS_ERABM_GetEpsbId:pucEpsbId is NULL!");
        TLPS_PRINT2LAYER_ERROR(CDS_ERABM_GetEpsbId_ENUM, LNAS_ERABM_EpsbIdIsNULL);
        return PS_FAIL;
    }

    /* ��ȡDRB�������غ� */
    if (NAS_ERABM_SUCCESS != NAS_ERABM_GetEpsbIdByDrbId(  ucDrbId,
                                                         &ulEpsbId))
    {

        return PS_FAIL;
    }

    *pucEpsbId = (VOS_UINT8)ulEpsbId;

    return PS_SUCC;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

