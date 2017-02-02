

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmEhsmMsgProc.h"
#include    "NasEsmInclude.h"


/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_NASESMEHSMMSGPROC_C
#define    THIS_NAS_FILE_ID             NAS_FILE_ID_NASESMEHSMMSGPROC_C
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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
NAS_ESM_EHRPD_ENTITY_STRU               g_stEsmEhrpdEntity;



VOS_VOID NAS_ESM_EhsmMsgDistr(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_MSG_HEADER_STRU           *pEhsmMsg  = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_MSG_HEADER_STRU*)pRcvMsg;

    /*������ϢID��������Ӧ����Ϣ������*/
    switch (pEhsmMsg->enMsgId)
    {
        case ID_EHSM_ESM_SYNC_PDN_INFO_IND:

            NAS_ESM_EhsmSyncPdnInfoMsgProc(pRcvMsg);

            /* ��ά�ɲ⣬�ϱ�HIDSʵ��״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            break;

        case ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY:

            /* ��ά�ɲ⣬�ϱ�HIDSʵ���������֮ǰ�ļ�¼״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

            NAS_ESM_EhsmClearAllBearerNotifyMsgProc(pRcvMsg);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmMsgDistr:Warning:EHSM->SM,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}



VOS_VOID NAS_ESM_InitEhrpdEntity(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_ENTITY_STRU          *pstEhrpdEntity      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_InitEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_InitEhrpdEntity_ENUM, LNAS_ENTRY);

    pstEhrpdEntity = NAS_ESM_GET_EHRPD_ENTITY_ADDR();

    /* EHRPDʵ�崦�ڵȴ��ָ�״̬ */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* EHRPD���ؼ�¼����Ϊ0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    pstEhrpdEntity->aucRsv[0]                     = 0;
    pstEhrpdEntity->aucRsv[1]                     = 0;

    /* ѭ����ÿ��PDNʵ���ʼ�� */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);
        pstPdnEntity->ucUsedFlag        = PS_FALSE;
        pstPdnEntity->ucAttachPdnFlag   = PS_FALSE;
        pstPdnEntity->ucIsOnReconnFlag  = PS_FALSE;
        pstPdnEntity->ucRsv             = 0;
        pstPdnEntity->ulHandoverEpsbId  = 0;

        NAS_ESM_MEM_SET(&pstPdnEntity->stNwMsgRecord,       \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

        NAS_ESM_MEM_SET(&pstPdnEntity->stTimerInfo,         \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

        NAS_ESM_MEM_SET(&pstPdnEntity->stEhPdnContextInfo,  \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));
    }

    return;
}
VOS_VOID NAS_ESM_EhsmSyncPdnInfoMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg            = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_SYNC_PDN_INFO_IND_STRU*)pRcvMsg;

    /* ״̬��Ϊ����̬��˵�����쳣��������Ϣ */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* ����EHSM�����ĳ�����Ϣͬ���������ֱ���д��� */
    switch (pEhsmMsg->enPdnOption)
    {
        case EHSM_ESM_PDN_OPT_CONNECTED:

            NAS_ESM_EhsmSyncPdnInfoConnectedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_MODIFIED:

            NAS_ESM_EhsmSyncPdnInfoModifiedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_DISCONNECTED:

            NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(pEhsmMsg);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc:Warning:EHSM->SM,Receive Abnormal PdnOption!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}
VOS_VOID NAS_ESM_EhsmClearAllBearerNotifyMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pEhsmMsg  = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY_STRU*)pRcvMsg;

    /* ״̬��Ϊ����̬��˵�����쳣��������Ϣ */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* ֪ͨRABM�����Դ */
    NAS_ESM_SndEsmRabmRelIndMsg();

    /* ɾ��L�µ����г��� */
    NAS_ESM_ClearEsmResource();

    /* ɾ������֮ǰ��¼��EHRPD���� */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* ֪ͨEMMִ�б���DETACH */
    NAS_ESM_SndEmmClLocalDetachNotifyMsg();

    return;
}
VOS_VOID NAS_ESM_EhsmSyncPdnInfoConnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, LNAS_ENTRY);

    /* �����EHRPD��ATTACH��PDN���ӣ����⴦�� */
    if (PS_TRUE == pEhsmMsg->ulAttachFlag)
    {
        /* ֪ͨRABM�����Դ */
        NAS_ESM_SndEsmRabmRelIndMsg();

        /* ɾ��L�µ����г��� */
        NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc();

        /* ɾ������֮ǰ��¼������EHRPD���� */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();

        /* ֪ͨEMMִ�б���DETACH */
        NAS_ESM_SndEmmClLocalDetachNotifyMsg();

        /* ����һ��PDNʵ�� */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: ATTACH PDN Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* ����ATTACH FLAG��ʶ */
        NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(ulIndex, PS_TRUE);

        /* ����EHRPD������Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* ����һ��δ���õ�PDN��Ϣʵ�� */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* ����EHRPD������Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }

    /* ʹ�õ�PDNʵ��������1 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() ++;

    return;
}
VOS_VOID NAS_ESM_EhsmSyncPdnInfoModifiedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, LNAS_ENTRY);

    /* ��EHRPDʵ���и���EHRPD����ID���ҵ�ǰ�޸ĵ�PDN�����Ƿ���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* ������ʽ�����޸Ĵ�PDN���ӵ���Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* �����ڣ�˵�������쳣����������Ϣ����ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}
VOS_VOID NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, LNAS_ENTRY);

    /* ��EHRPDʵ���и���EHRPD����ID���ҵ�ǰ�޸ĵ�PDN�����Ƿ���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* ɾ����PDN���ӵ���Ϣ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }
    else
    {
        /* �����ڣ�˵�������쳣����������Ϣ����ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}
VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc_ENUM, LNAS_ENTRY);

    /* ������Ϣ��¼֪ͨAPP */
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_FALSE);

    /* ����EMM��״̬Ϊδע�� */
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /* ���֧��˫APN����ֹͣ��Ӧ��ʱ����������ע�������Ч */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* ����OPIDΪ0 */
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

    #ifdef PS_ITT_PC_TEST_NAS
    /* NAS ST�����£���������������ע��ʱʹ����PTIֵΪ2������PTI��ʼ��Ϊ1������PTI���亯�������2��ʼʹ�� */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
    #else

    /* PTI��ʼ��Ϊ0��ע��ʱ������PTI���亯�������1��ʼʹ�� */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);

    /* CID0��PS�ںϺ�Ƚ����⣬��ESMά����������NV�����ݻ���ڲ�һ��, �轫CID0��ʼ��Ϊר������ */
    NAS_ESM_ClearCid0StaticInfo();
    #endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);

    /* ��ʼ��CID 21~31 ������̬��Ϣ */
    NAS_ESM_ClearNwCtrlSdfPara();

    /* ֪ͨAPP��APS ������ر��ͷţ���ʼ��������Ϣ */
    for (i = NAS_ESM_MIN_EPSB_ID; i <= NAS_ESM_MAX_EPSB_ID; i++)
    {
        /* δ���ֱ��ɾ�� */
        if (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(i))
        {
            /* ��ʼ��������Ϣ */
            NAS_ESM_InitEpsbCntxtInfo(i);
            continue;
        }

        /* ����̬����ר�г��أ�����Ҫ֪ͨAPSȥ���ȱʡ���ز���֪ͨ */
        if (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(i))
        {
            /* ֪ͨAPP ������ر��ͷţ���۵�����CID��֪ͨAPP�ͷŵ� */
            NAS_ESM_InformAppBearerRel(i);

            /* ֪ͨAPS ������ر��ͷ� */
            NAS_ESM_SndSmEspBearerDeactIndMsg(i);
        }

        /* ��ʼ��������Ϣ */
        NAS_ESM_InitEpsbCntxtInfo(i);
    }

    /* ��ʼ��ҵ�����Ķ�̬��Ϣ */
    for (i = 0; i < NAS_ESM_MAX_CID_NUM; i++)
    {
        NAS_ESM_MEM_SET(NAS_ESM_GetSdfCntxtInfo(i),
                                        0,
                                        sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }

    /* ��ʼ��PDN���ӵĸ��� */
    NAS_ESM_SetCurPdnNum(0);

    /* ��ʼ�����Ϳտ���Ϣ�Ľṹ�� */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* ���ESM������ */
    NAS_ESM_ClearEsmBuff();

    return;

}



VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllEhrpdPdnInfoProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllEhrpdPdnInfoProc_ENUM, LNAS_ENTRY);

    /* ����PDNʵ���б� */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ ==  \
                                        NAS_ESM_GET_EHRPD_ENTITY_STATE())
            {
                /* ��APS�ϱ����ػָ�ʧ�� */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);
            }

            /* ɾ��EHRPD���ؼ�¼ */
            NAS_ESM_DeleteEhrpdPdnEntityInfo(i);
        }
    }

    /* ����EHRPDʵ�����ȴ��ָ�״̬ */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* ʹ�õ�ʵ������ǿ����0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    return;
}
VOS_UINT32 NAS_ESM_AllocPdnIndexInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* ���PDNʵ��ʹ����Ϊ���ֱ�ӷ��ط���ʧ�� */
    if (NAS_ESM_EHRPD_PDN_MAX_NUM == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        /* δ�ҵ�������ʧ�� */
        NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Entity total num is Max.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_REACH_MAXNUM);
        return  NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�δʹ�õ�λ�ã����سɹ�����������ֵ */
        if (PS_TRUE != pstPdnEntity->ucUsedFlag)
        {
            pstPdnEntity->ucUsedFlag    = PS_TRUE;
            *pulIndex                   = i;

            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_WARN_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Alloc failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);

    return NAS_ESM_FAILURE;
}


VOS_VOID NAS_ESM_SaveEhrpdPdnInfo(
    VOS_UINT32                          ulIndex,
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1;
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveEhrpdPdnInfo_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET(&stTmpApnInfo1, 0, sizeof(NAS_ESM_CONTEXT_APN_STRU));
    NAS_ESM_MEM_SET(&stTmpApnInfo2, 0, sizeof(APP_ESM_APN_INFO_STRU));

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ����CID */
    pstPdnEntity->stEhPdnContextInfo.ulBitCid               = pEhsmMsg->ulBitCid;

    /* ����EHRPD�µĳ���ID */
    pstPdnEntity->stEhPdnContextInfo.ulEpsbId               = pEhsmMsg->ulEpsbId;

    /* ����EHRPD�µ�PDN��ַ */
    NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stPdnAddr,      \
                                        &pEhsmMsg->stPdnAddr,         \
                                        sizeof(EHSM_ESM_PDN_ADDR_STRU));

    /* ����APN */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApn)
    {
        /* ��ʱ����APN������APN��ʽת�� */
        stTmpApnInfo1.ucApnLen          = pEhsmMsg->stApn.ucApnLen;
        NAS_ESM_MEM_CPY(&stTmpApnInfo1.aucApnName,                        \
                                        &pEhsmMsg->stApn.aucApn,      \
                                        pEhsmMsg->stApn.ucApnLen);

        /* ��APN��ʽ��δ����תΪ���� */
        if(NAS_ESM_SUCCESS != NAS_ESM_ApnReverseTransformation(&stTmpApnInfo2, &stTmpApnInfo1))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_SaveEhrpdPdnInfo:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_SaveEhrpdPdnInfo_ENUM, ESM_EHSM_APN_FORMAT_ILL);
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_FALSE;
        }
        else
        {
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stApn,  \
                                        &stTmpApnInfo2,               \
                                        sizeof(APP_ESM_APN_INFO_STRU));
        }
    }

    /* ����APN AMBR */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApnAmbr)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpApnAmbr       = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stApnAmbr,  \
                                        &pEhsmMsg->stApnAmbr,         \
                                        sizeof(EHSM_ESM_APN_AMBR_STRU));
    }

    /* ����PCO IPV4 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv4Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv4Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stPcoIpv4Item,        \
                                        &pEhsmMsg->stPcoIpv4Item,               \
                                        sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
    }

    /* ����PCO IPV6 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv6Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv6Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stPcoIpv6Item,        \
                                        &pEhsmMsg->stPcoIpv6Item,               \
                                        sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU));
    }

    return;
}
VOS_VOID NAS_ESM_DeleteEhrpdPdnEntityInfo(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG1("NAS_ESM_DeleteEhrpdPdnEntityInfo:delete entity index = ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DeleteEhrpdPdnEntityInfo_ENUM, LNAS_ENTRY, ulIndex);

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ����PDNʵ��Ϊδʹ�� */
    pstPdnEntity->ucUsedFlag            = PS_FALSE;

    /* ���ʵ����ر�ʶ */
    pstPdnEntity->ucAttachPdnFlag       = PS_FALSE;
    pstPdnEntity->ucIsOnReconnFlag      = PS_FALSE;
    pstPdnEntity->ucRsv                 = 0;

    /* ����L�»ָ��ĳ���ID */
    pstPdnEntity->ulHandoverEpsbId      = 0;

    /* ֹͣ�ȴ�PDN�ָ��ɹ���ʱ�� */
    NAS_ESM_TimerStop(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);

    /* ����տ���Ϣ��¼ */
    NAS_ESM_MEM_SET(&pstPdnEntity->stNwMsgRecord,           \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

    /* ���������������Ϣ */
    NAS_ESM_MEM_SET(&pstPdnEntity->stEhPdnContextInfo,      \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));

    /* EHRPD���ؼ�¼������һ */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() --;

    return;
}
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ��ҳ���ID��ͬ�����سɹ�����������ֵ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulEpsbId == pstPdnEntity->stEhPdnContextInfo.ulEpsbId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: Not find same EpsbId.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NOT_FIND_SAME_EPSBID);
    return NAS_ESM_FAILURE;
}
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ת����ulBitCid */
    ulBitCid        = (NAS_ESM_BIT_0 << ulCid);

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���CID��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulBitCid == pstPdnEntity->stEhPdnContextInfo.ulBitCid))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same CID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NOT_FIND_SAME_CID);
    return NAS_ESM_FAILURE;
}



VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(
    APP_ESM_APN_INFO_STRU              *pstApn,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* APN����Ϊ0��99��ֱ�ӷ��ػ�ȡʧ�� */
    if ((0 == pstApn->ucApnLen)
      ||(APP_MAX_APN_LEN < pstApn->ucApnLen))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: APN len is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_APN_LEN_0);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���APN��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn))
        {
            if ((pstApn->ucApnLen == pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen)
              &&(NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(&pstApn->aucApnName,                   \
                                        &pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,\
                                        pstApn->ucApnLen)))
            {
                *pulIndex               = i;
                return NAS_ESM_SUCCESS;
            }
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same APN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NOT_FIND_SAME_APN);
    return NAS_ESM_FAILURE;
}


VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���OPID��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulOpId == pstPdnEntity->stNwMsgRecord.ulNwMsgOpId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same OPID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NOT_FIND_SAME_OPID);
    return NAS_ESM_FAILURE;
}
VOS_UINT32 NAS_ESM_GetAttachPdnInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ��EHRPD PDNʵ���н���ѭ������ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* �ҵ������Ϊע��PDN��ʵ�� */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(PS_TRUE == pstPdnEntity->ucAttachPdnFlag))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ���˵�����ܱ�ȥ������ˣ�ֱ������һ��PDN��ΪATTACH PDN */
    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: NO attachflag PDN, get next reconnect PDN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN_GET_NEXT_PND);
    if (NAS_ESM_SUCCESS ==  NAS_ESM_GetNextReconnectEhrpdPdn(pulIndex))
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(*pulIndex);
        pstPdnEntity->ucAttachPdnFlag   = PS_TRUE;
    }

    return NAS_ESM_FAILURE;
}



VOS_UINT32 NAS_ESM_GetAttachCidInEhrpdEntity(
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachCidInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachCidInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* �ҵ������Ϊע��PDN��ʵ�� */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        return NAS_ESM_FAILURE;
    }

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* CIDת�� */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* ��ЧCID������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    *pulCid         = ulCid;

    return NAS_ESM_SUCCESS;

}
VOS_UINT32 NAS_ESM_GetNextReconnectEhrpdPdn(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õ� */
        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* ��������Ϊ������������ѡ����һ�� */
            if (NAS_ESM_SUCCESS != NAS_ESM_CheckAllowedPdnEntityToReconnect(pstPdnEntity))
            {
                /* ��APS�ϱ����ػָ�ʧ�� */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

                /* ɾ������EHRPD������Ϣ��¼ */
                NAS_ESM_DeleteEhrpdPdnEntityInfo(i);

                continue;
            }

            *pulIndex                   = i;

            /* ��ά�ɲ⣬�ϱ�HIDSʵ��״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            return NAS_ESM_SUCCESS;
        }
    }

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: Get next PDN failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_NEXT_PDN);
    return NAS_ESM_FAILURE;
}


VOS_UINT32 NAS_ESM_PerformEhrpdPdnReconnect(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          ulPti;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    VOS_UINT32                          ulStateTblIndex;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_PerformEhrpdPdnReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, LNAS_ENTRY);

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* LģΪ����̬��ֹͣEHRPD���ػָ����� */
    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return NAS_ESM_FAILURE;
    }

    /* CIDת�� */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* ��ЧCID������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* ���䶯̬��ID */
    if (NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid, &ulStateTblIndex))
    {
        /* ��ӡ�쳣��Ϣ��״̬�������߸�CID�Ѿ��ڱ��� */
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_TABLE_FULL_OR_CID_ALREADY_IN);
        return NAS_ESM_FAILURE;
    }

    /* ��EHRPD���ؼ�¼�е�APN��Ϣд���ӦCID��SDF���� */
    pstSdfPara                          = NAS_ESM_GetSdfParaAddr(ulCid);
    NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

    /* ���ö�̬���в�������״̬����� */
    pstStateAddr                        = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->enBearerCntxtState    = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstStateAddr->enPdnReqType          = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

    /* ����PTI�������������Ϣ�� */
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /* ���NAS_ESM_ENCODE_INFO_STRU */
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /* ��װPDN_Connect_Req��Ϣ */
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo,             \
                                        pstStateAddr->stNwMsgRecord.aucMsgBuff, \
                                        &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_ENCODE_PND_CONN_REQ_FAIL);

        /* ����ʧ�ܣ��ͷŶ�̬����Դ */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return NAS_ESM_FAILURE;
    }

    /* ����OPID����¼�տ���Ϣ���� */
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ulOpId            = NAS_ESM_AllocEmmEsmOpId();
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /* �����Ƿ�Ϊ����PDN�������� */
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq     = PS_FALSE;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf              = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /* ���ú�����ESM->EMM������Ϣ:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ) */
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,                         \
                                                  pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,\
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,                      \
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  NAS_ESM_AIR_MSG_DIR_ENUM_UP,              \
                                                  ESM_PDN_CONNECT_REQ);

    /* ����T3482��ʱ�� */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

    /* ״̬ת�� */
    NAS_ESM_SetProcTransState(ulStateTblIndex, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

    return NAS_ESM_SUCCESS;
}
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    /* ȡ��ʵ���е�APN�����õ�SDF�� */
    if (NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        pstSdfPara->bitOpApn            = NAS_ESM_OP_TRUE;

        pstSdfPara->stApnInfo.ucApnLen  = pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen;

        NAS_ESM_MEM_CPY(&pstSdfPara->stApnInfo.aucApnName,                      \
                                        &pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,\
                                        pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen);
    }

    /* ȡ��ʵ���е�PDN���ͣ����õ�SDF�� */
    if ((EHSM_ESM_PDN_TYPE_IPV4 <= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      &&(EHSM_ESM_PDN_TYPE_IPV4V6 >= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType            = pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType;
    }

    return;
}


VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd
)
{
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo;

    NAS_ESM_MEM_SET(&stTmpApnInfo, 0, sizeof(NAS_ESM_CONTEXT_APN_STRU));

    NAS_ESM_INFO_LOG("NAS_ESM_SetEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg_ENUM, LNAS_ENTRY);

    /* ��ֵ����CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* ��ֵ����ID */
    pstPdnInfoInd->ulEpsbId             = pstEpsbCntxtInfo->ulEpsbId;

    /* �������APN��Ϣת��δ�����APN��Ϣ */
    if(APP_SUCCESS != NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                        &pstEpsbCntxtInfo->stApnInfo))
    {
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_FALSE;
    }
    else
    {
        /* ��ֵAPN */
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_TRUE;
        pstPdnInfoInd->stApn.ucApnLen   = stTmpApnInfo.ucApnLen;
        NAS_ESM_MEM_CPY(&pstPdnInfoInd->stApn.aucApn,                           \
                                        &stTmpApnInfo.aucApnName,               \
                                        stTmpApnInfo.ucApnLen);
    }

    /* ��ֵPDN ADDRESS */
    NAS_ESM_MEM_CPY(&pstPdnInfoInd->stPdnAddr,                                  \
                                        &pstEpsbCntxtInfo->stPdnAddrInfo,       \
                                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* ��ֵAPN-AMBR����ʱ�Ȳ��� */

    /* ��ֵPCO����ʱ�Ȳ��� */

    return;
}
VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
)
{
    VOS_UINT8                           i;

    NAS_ESM_INFO_LOG1("NAS_ESM_ConvertBitCidToCid: ulBitCid = ", ulBitCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ConvertBitCidToCid_ENUM, LNAS_ENTRY, ulBitCid);

    /* ѭ����λ�ҵ�CID��Ŀǰ�����ڳ��ػ�ۣ����ֻ����1��CID */
    for (i = 0; i <= NAS_ESM_MAX_CID; i++)
    {
        /* ���Ƽ�λ֮��Ľ��Ϊ1��CID���Ǽ����ҵ��󷵻سɹ� */
        if (NAS_ESM_OP_TRUE == ((ulBitCid >> i) & 0x00000001))
        {
            return i;
        }
    }

    return NAS_ESM_ILL_CID;
}


VOS_UINT32 NAS_ESM_IsBackOffAllowedToReconn(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    NAS_ESM_MEM_SET(&stJudgmentPara, 0, sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));

    /* ȱʡ��������APN��Back-off�㷨�ж��������������ֱ�Ӹ�APP��ʧ�� */
    if(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        NAS_ESM_MEM_CPY(&stJudgmentPara,                                        \
                                        &pstPdnEntity->stEhPdnContextInfo.stApn,\
                                        sizeof(APP_ESM_APN_INFO_STRU));
    }
    else
    {
        /* ��APNֱ�������� */
        return NAS_ESM_SUCCESS;
    }

    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_IsBackOffAllowedToReconn: Back-off not allowed send PDN req.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsBackOffAllowedToReconn_ENUM, ESM_EHSM_BACKOFF_NOT_ALLOW_PDN_REQ);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}



VOS_UINT32 NAS_ESM_CheckAllowedPdnEntityToReconnect(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    VOS_UINT32                          ulCid;

    NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, LNAS_ENTRY);

    /* Back-off�㷨�ж�������������𣬷���ʧ�� */
    if (NAS_ESM_SUCCESS != NAS_ESM_IsBackOffAllowedToReconn(pstPdnEntity))
    {
        return NAS_ESM_FAILURE;
    }

    /* �ھܾ�ԭ��ֵ#66�б��У��ҵ�ǰפ��PLMN��#66�б��PLMN������ʧ��*/
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #66 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_66_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    ulCid = NAS_ESM_ConvertBitCidToCid(pstPdnEntity->stEhPdnContextInfo.ulBitCid);

    /* CID��Ч������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* ����PDN���ͣ�����ʧ�� */
    if ((EHSM_ESM_PDN_TYPE_IPV4 > pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      ||(EHSM_ESM_PDN_TYPE_IPV4V6 < pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect:PDN type err.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_PDN_TYPE_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* �����ǰʹ�õ�APN��#50�ܾ��б��У�����ʧ�� */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType, \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #50 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_50_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    /* �����ǰʹ�õ�APN��#51�ܾ��б��У�����ʧ�� */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType,  \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #51 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_51_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}



VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverSuccProc(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          ulNextPdnIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverSuccProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverSuccProc_ENUM, LNAS_ENTRY);

    /* ��APS�ϱ�ע����ػָ��ɹ� */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_SUCC);

    /* ɾ������EHRPD������Ϣ��¼ */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* ���PDNʵ����Ϊ0��˵���ָ��������̽���������EHRPDʵ��Ϊ�ȴ��ָ�̬ */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverSuccProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverSuccProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);
        return;
    }

    /* ȡ��һ������ */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulNextPdnIndex))
    {
        /* ��ȡ�ɹ���ִ����һ�����ػָ��������ִ�гɹ������� */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulNextPdnIndex))
        {
            return;
        }

        /* ִ��ʧ�� */

        /* ��APS�ϱ����ػָ�ʧ�� */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulNextPdnIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* ɾ������EHRPD������Ϣ��¼ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulNextPdnIndex);
    }

    /* ��ȡ��һ��ʧ�� */
    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_ESM_SendEndSessionNotify();
    #endif

    return;
}
VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverFailProc(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          ulNextPdnIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverFailProc_ENUM, LNAS_ENTRY);

    /* ��APS�ϱ����ػָ�ʧ�� */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

    /* ɾ������EHRPD������Ϣ��¼ */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* ���PDNʵ����Ϊ0��˵���ָ��������̽���������EHRPDʵ��Ϊ�ȴ��ָ�̬ */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverFailProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverFailProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);
        return;
    }

    /* ȡ��һ������ */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulNextPdnIndex))
    {
        /* ��ȡ�ɹ���ִ����һ�����ػָ��������ִ�гɹ������� */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulNextPdnIndex))
        {
            return;
        }

        /* ִ��ʧ�� */

        /* ��APS�ϱ����ػָ�ʧ�� */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulNextPdnIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* ɾ������EHRPD������Ϣ��¼ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulNextPdnIndex);
    }

    /* ��ȡ��һ��ʧ�� */
    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_ESM_SendEndSessionNotify();
    #endif

    return;
}
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, LNAS_ENTRY);

    /* ����OPID���Ҷ�Ӧ��PDNʵ������ */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ҵ�PDNʵ�壬����Ǽ���ȱʡ����ACP���ͳɹ���ִ�лָ��ɹ��Ĵ��� */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
    }
    else
    {
        /* ֻ��PDN REQ���ͳɹ����޶��� */
    }

    return;
}
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, LNAS_ENTRY);

    /* ����OPID���Ҷ�Ӧ��PDNʵ������ */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                        = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ҵ�PDNʵ�壬����Ǽ���ȱʡ����ACP����ʧ�ܣ�������ʧ�ܽ�������Ĵ��� */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        pstPdnEntity->stNwMsgRecord.ucSendFailTimes ++;

        /* ��һ�η���ʧ��ʱ�����ȴ��ָ����سɹ���ʱ������ֹ���಻�ٷ���ȱʡ���ؼ��������¹���
        �˶�ʱ����ɾ���˳��ؼ�¼ʱֹͣ�������ʱ��ɾ���˳��ؽ�����һ��EHRPD���ػָ����� */
        if (NAS_ESM_FIRST_FAIL_TIME == pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_TimerStart(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);
        }

        /* ʧ�ܴ����������Ϊ���ػָ�ʧ�� */
        if (NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES <= pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);
            return;
        }

    }
    else
    {
        /* ֻ��PDN REQ����ʧ�ܣ��޶������ȴ�T3482��ʱ����ʱ�ط� */
    }

    return;
}



/*lint -specific(-e433)*/

VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulAttachPdnFlag
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),       \
                                        0,                            \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_CONNECTED;
    pstPdnInfoInd->ulAttachFlag         = ulAttachPdnFlag;

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}


VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd   = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(      \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoModIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoModIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),                 \
                                        0,                                      \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_MODIFIED;
    pstPdnInfoInd->ulAttachFlag         = PS_FALSE;

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}


VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),                 \
                                        0,                                      \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_DISCONNECTED;
    pstPdnInfoInd->ulEpsbId             = ulEpsbId;

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}
VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID)
{
    ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pstClearNtfMsg = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstClearNtfMsg = (ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG( \
                                                  sizeof(ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstClearNtfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmClearAllBearerNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstClearNtfMsg),                \
                                                  0,                            \
                                                  NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstClearNtfMsg, ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstClearNtfMsg);
    return;
}


VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* ��ȡ��ӦPDNʵ���ַ */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ָ��ɹ�����SM���ͳ���modify ind���ӿ���Ϣ���� */
    NAS_ESM_SndSmEspBearerMdfIndMsg(pstPdnEntity->ulHandoverEpsbId);

    return;
}



VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEpsBearInfoInd = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(    \
                                        sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstEpsBearInfoInd)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndApsEhrpdPdnReconnFailMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndApsEhrpdPdnReconnFailMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    /* ��ȡ��ӦPDNʵ���ַ */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /*���*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),        \
                                        0,                            \
                                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /* ȥ���ֻ�����ID��Cid���� */
    pstEpsBearInfoInd->enPdpOption      = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId         = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    pstEpsBearInfoInd->ulBitCid         = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
    return;
}



VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(
    VOS_UINT32                                    ulIndex,
    NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8       enResult
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU                *pstPdnEntity = VOS_NULL_PTR;

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    if (NAS_ESM_PDN_RECONNECT_RESULT_SUCC == enResult)
    {
        /* �ָ��ɹ�����APS���ͳ���modify ind   */
        NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(ulIndex);
    }
    else
    {
        /* �ָ�ʧ�ܣ���APS���ͳ���deactive ind */
        NAS_ESM_SndApsEhrpdPdnReconnFailMsg(ulIndex);
    }

    return;
}


VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID)
{
    EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU          *pstDetachMsg        = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstDetachMsg    = (EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG(  \
                                                  sizeof(EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDetachMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEmmClLocalDetachNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEmmClLocalDetachNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstDetachMsg),                       \
                                                  0,                            \
                                                  NAS_ESM_GET_MSG_LENGTH(pstDetachMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstDetachMsg, ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstDetachMsg);
    return;
}


VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID)
{
    NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU         *pstEntityOmMsg      = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEntityOmMsg  = (NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU*)NAS_ESM_MEM_ALLOC( \
                                                  sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    if (VOS_NULL_PTR == pstEntityOmMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityNum:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityNum_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    NAS_ESM_MEM_SET(pstEntityOmMsg, 0, sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU) - 20;

    pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_NUM;

    /* ���EHRPDʵ�嵱ǰ״̬ */
    pstEntityOmMsg->ulEhrpdPdnTotalNum              = NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM();

    /* ��Ϣ�ϱ�HIDS */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
    NAS_ESM_MEM_FREE(pstEntityOmMsg);

    return;
}



VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU   *pstEntityOmMsg      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    /* ���ϱ�һ������ʹ�õ�PDNʵ������ */
    NAS_ESM_SndOmEhrpdUsedPdnEntityNum();

    /* �����ϱ�����ʹ�õ�PDNʵ����Ϣ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* ����ռ䲢��������Ƿ�ɹ� */
            pstEntityOmMsg = (NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU*)NAS_ESM_MEM_ALLOC(\
                                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            if (VOS_NULL_PTR == pstEntityOmMsg)
            {
                /*��ӡ�쳣��Ϣ*/
                NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo:Alloc Msg fail!");
                TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
                return;
            }

            NAS_ESM_MEM_SET(pstEntityOmMsg, 0, sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU) - 20;

            pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_INFO;

            /* ���EHRPDʵ�嵱ǰ״̬ */
            pstEntityOmMsg->enEntityState                   = NAS_ESM_GET_EHRPD_ENTITY_STATE();

            /* ���η���Ϣ�����PDNʵ�������� */
            pstEntityOmMsg->ucEntityIndex                   = (VOS_UINT8)i;
            NAS_ESM_MEM_CPY(&pstEntityOmMsg->stEhPdnEntityInfo,       \
                                        pstPdnEntity,                 \
                                        sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU));

            /* ��Ϣ�ϱ�HIDS */
            (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
            NAS_ESM_MEM_FREE(pstEntityOmMsg);
        }
    }

    return;
}


/*lint -specific(+e433)*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

