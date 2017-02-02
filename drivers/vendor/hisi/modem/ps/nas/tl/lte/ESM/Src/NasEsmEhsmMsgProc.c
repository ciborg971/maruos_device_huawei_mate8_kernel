

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

    /*根据消息ID，调用相应的消息处理函数*/
    switch (pEhsmMsg->enMsgId)
    {
        case ID_EHSM_ESM_SYNC_PDN_INFO_IND:

            NAS_ESM_EhsmSyncPdnInfoMsgProc(pRcvMsg);

            /* 可维可测，上报HIDS实体状态 */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            break;

        case ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY:

            /* 可维可测，上报HIDS实体清除承载之前的记录状态 */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

            NAS_ESM_EhsmClearAllBearerNotifyMsgProc(pRcvMsg);
            break;

        default:

            /*打印异常信息*/
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

    /* EHRPD实体处于等待恢复状态 */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* EHRPD承载记录总数为0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    pstEhrpdEntity->aucRsv[0]                     = 0;
    pstEhrpdEntity->aucRsv[1]                     = 0;

    /* 循环将每个PDN实体初始化 */
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

    /* 状态不为挂起态，说明是异常，丢弃消息 */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* 根据EHSM发来的承载信息同步操作，分别进行处理 */
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

            /*打印异常信息*/
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

    /* 状态不为挂起态，说明是异常，丢弃消息 */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* 通知RABM清除资源 */
    NAS_ESM_SndEsmRabmRelIndMsg();

    /* 删除L下的所有承载 */
    NAS_ESM_ClearEsmResource();

    /* 删除所有之前记录的EHRPD承载 */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* 通知EMM执行本地DETACH */
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

    /* 如果是EHRPD下ATTACH的PDN连接，特殊处理 */
    if (PS_TRUE == pEhsmMsg->ulAttachFlag)
    {
        /* 通知RABM清除资源 */
        NAS_ESM_SndEsmRabmRelIndMsg();

        /* 删除L下的所有承载 */
        NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc();

        /* 删除所有之前记录的所有EHRPD承载 */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();

        /* 通知EMM执行本地DETACH */
        NAS_ESM_SndEmmClLocalDetachNotifyMsg();

        /* 分配一个PDN实体 */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: ATTACH PDN Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* 设置ATTACH FLAG标识 */
        NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(ulIndex, PS_TRUE);

        /* 保存EHRPD承载信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* 分配一个未启用的PDN信息实体 */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* 保存EHRPD承载信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }

    /* 使用的PDN实体总数加1 */
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

    /* 在EHRPD实体中根据EHRPD承载ID查找当前修改的PDN连接是否存在 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* 按覆盖式处理，修改此PDN连接的信息 */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* 不存在，说明出现异常，丢弃此消息，打印异常信息*/
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

    /* 在EHRPD实体中根据EHRPD承载ID查找当前修改的PDN连接是否存在 */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* 删除此PDN连接的信息 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }
    else
    {
        /* 不存在，说明出现异常，丢弃此消息，打印异常信息*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}
VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;

    /*打印进入该函数*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc_ENUM, LNAS_ENTRY);

    /* 根据消息记录通知APP */
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_FALSE);

    /* 设置EMM的状态为未注册 */
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /* 如果支持双APN，则停止对应定时器，并设置注册承载无效 */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* 设置OPID为0 */
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

    #ifdef PS_ITT_PC_TEST_NAS
    /* NAS ST场景下，由于现有用例在注册时使用了PTI值为2，所以PTI初始化为1，调用PTI分配函数，会从2开始使用 */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
    #else

    /* PTI初始化为0，注册时，调用PTI分配函数，会从1开始使用 */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);

    /* CID0在PS融合后比较特殊，在ESM维护的内容与NV的内容会存在不一致, 需将CID0初始化为专有类型 */
    NAS_ESM_ClearCid0StaticInfo();
    #endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);

    /* 初始化CID 21~31 关联静态信息 */
    NAS_ESM_ClearNwCtrlSdfPara();

    /* 通知APP和APS 激活承载被释放，初始化承载信息 */
    for (i = NAS_ESM_MIN_EPSB_ID; i <= NAS_ESM_MAX_EPSB_ID; i++)
    {
        /* 未激活，直接删掉 */
        if (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(i))
        {
            /* 初始化承载信息 */
            NAS_ESM_InitEpsbCntxtInfo(i);
            continue;
        }

        /* 激活态且是专有承载，则需要通知APS去激活，缺省承载不能通知 */
        if (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(i))
        {
            /* 通知APP 激活承载被释放，汇聚的所有CID都通知APP释放掉 */
            NAS_ESM_InformAppBearerRel(i);

            /* 通知APS 激活承载被释放 */
            NAS_ESM_SndSmEspBearerDeactIndMsg(i);
        }

        /* 初始化承载信息 */
        NAS_ESM_InitEpsbCntxtInfo(i);
    }

    /* 初始化业务流的动态信息 */
    for (i = 0; i < NAS_ESM_MAX_CID_NUM; i++)
    {
        NAS_ESM_MEM_SET(NAS_ESM_GetSdfCntxtInfo(i),
                                        0,
                                        sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }

    /* 初始化PDN连接的个数 */
    NAS_ESM_SetCurPdnNum(0);

    /* 初始化发送空口消息的结构体 */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* 清除ESM缓存区 */
    NAS_ESM_ClearEsmBuff();

    return;

}



VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllEhrpdPdnInfoProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllEhrpdPdnInfoProc_ENUM, LNAS_ENTRY);

    /* 遍历PDN实体列表 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ ==  \
                                        NAS_ESM_GET_EHRPD_ENTITY_STATE())
            {
                /* 向APS上报承载恢复失败 */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);
            }

            /* 删除EHRPD承载记录 */
            NAS_ESM_DeleteEhrpdPdnEntityInfo(i);
        }
    }

    /* 设置EHRPD实体进入等待恢复状态 */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* 使用的实体总数强制清0 */
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

    /* 如果PDN实体使用数为最大，直接返回分配失败 */
    if (NAS_ESM_EHRPD_PDN_MAX_NUM == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        /* 未找到，返回失败 */
        NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Entity total num is Max.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_REACH_MAXNUM);
        return  NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到未使用的位置，返回成功，传出索引值 */
        if (PS_TRUE != pstPdnEntity->ucUsedFlag)
        {
            pstPdnEntity->ucUsedFlag    = PS_TRUE;
            *pulIndex                   = i;

            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
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

    /* 保存CID */
    pstPdnEntity->stEhPdnContextInfo.ulBitCid               = pEhsmMsg->ulBitCid;

    /* 保存EHRPD下的承载ID */
    pstPdnEntity->stEhPdnContextInfo.ulEpsbId               = pEhsmMsg->ulEpsbId;

    /* 保存EHRPD下的PDN地址 */
    NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stPdnAddr,      \
                                        &pEhsmMsg->stPdnAddr,         \
                                        sizeof(EHSM_ESM_PDN_ADDR_STRU));

    /* 保存APN */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApn)
    {
        /* 临时保存APN，用于APN格式转换 */
        stTmpApnInfo1.ucApnLen          = pEhsmMsg->stApn.ucApnLen;
        NAS_ESM_MEM_CPY(&stTmpApnInfo1.aucApnName,                        \
                                        &pEhsmMsg->stApn.aucApn,      \
                                        pEhsmMsg->stApn.ucApnLen);

        /* 将APN格式从未译码转为译码 */
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

    /* 保存APN AMBR */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApnAmbr)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpApnAmbr       = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stApnAmbr,  \
                                        &pEhsmMsg->stApnAmbr,         \
                                        sizeof(EHSM_ESM_APN_AMBR_STRU));
    }

    /* 保存PCO IPV4 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv4Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv4Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY(&pstPdnEntity->stEhPdnContextInfo.stPcoIpv4Item,        \
                                        &pEhsmMsg->stPcoIpv4Item,               \
                                        sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
    }

    /* 保存PCO IPV6 */
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

    /* 设置PDN实体为未使用 */
    pstPdnEntity->ucUsedFlag            = PS_FALSE;

    /* 清除实体相关标识 */
    pstPdnEntity->ucAttachPdnFlag       = PS_FALSE;
    pstPdnEntity->ucIsOnReconnFlag      = PS_FALSE;
    pstPdnEntity->ucRsv                 = 0;

    /* 清零L下恢复的承载ID */
    pstPdnEntity->ulHandoverEpsbId      = 0;

    /* 停止等待PDN恢复成功定时器 */
    NAS_ESM_TimerStop(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);

    /* 清除空口消息记录 */
    NAS_ESM_MEM_SET(&pstPdnEntity->stNwMsgRecord,           \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

    /* 清除承载上下文信息 */
    NAS_ESM_MEM_SET(&pstPdnEntity->stEhPdnContextInfo,      \
                                        0,                  \
                                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));

    /* EHRPD承载记录总数减一 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 在实体列表中逐一查找，找到正在使用的，且承载ID相同，返回成功，传出索引值 */
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

    /* 未找到，返回失败 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 转换成ulBitCid */
    ulBitCid        = (NAS_ESM_BIT_0 << ulCid);

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的，且CID相同，返回成功，传出索引值 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulBitCid == pstPdnEntity->stEhPdnContextInfo.ulBitCid))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* APN长度为0或超99，直接返回获取失败 */
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

        /* 在实体列表中逐一查找，找到正在使用的，且APN相同，返回成功，传出索引值 */
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

    /* 未找到，返回失败 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的，且OPID相同，返回成功，传出索引值 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulOpId == pstPdnEntity->stNwMsgRecord.ulNwMsgOpId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，返回失败 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* 在EHRPD PDN实体中进行循环查找 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 找到被标记为注册PDN的实体 */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(PS_TRUE == pstPdnEntity->ucAttachPdnFlag))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* 未找到，说明可能被去激活掉了，直接用下一个PDN作为ATTACH PDN */
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

    /* 找到被标记为注册PDN的实体 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        return NAS_ESM_FAILURE;
    }

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* CID转换 */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* 无效CID，返回失败 */
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

    /* 无EHRPD承载，直接返回获取失败 */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* 在实体列表中逐一查找，找到正在使用的 */
        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* 如果检查结果为不允许发起，跳过选择下一个 */
            if (NAS_ESM_SUCCESS != NAS_ESM_CheckAllowedPdnEntityToReconnect(pstPdnEntity))
            {
                /* 向APS上报承载恢复失败 */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

                /* 删除这条EHRPD承载信息记录 */
                NAS_ESM_DeleteEhrpdPdnEntityInfo(i);

                continue;
            }

            *pulIndex                   = i;

            /* 可维可测，上报HIDS实体状态 */
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

    /* L模为挂起态，停止EHRPD承载恢复流程 */
    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return NAS_ESM_FAILURE;
    }

    /* CID转换 */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* 无效CID，返回失败 */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* 分配动态表ID */
    if (NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid, &ulStateTblIndex))
    {
        /* 打印异常消息，状态表满或者该CID已经在表中 */
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_TABLE_FULL_OR_CID_ALREADY_IN);
        return NAS_ESM_FAILURE;
    }

    /* 将EHRPD承载记录中的APN信息写入对应CID的SDF表项 */
    pstSdfPara                          = NAS_ESM_GetSdfParaAddr(ulCid);
    NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

    /* 设置动态表中参数承载状态和类别 */
    pstStateAddr                        = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->enBearerCntxtState    = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstStateAddr->enPdnReqType          = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

    /* 分配PTI，并存入承载信息中 */
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /* 填充NAS_ESM_ENCODE_INFO_STRU */
    NAS_ESM_MEM_SET((VOS_VOID*)&stEncodeInfo, 0, sizeof(NAS_ESM_ENCODE_INFO_STRU));
    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /* 组装PDN_Connect_Req消息 */
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo,             \
                                        pstStateAddr->stNwMsgRecord.aucMsgBuff, \
                                        &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_ENCODE_PND_CONN_REQ_FAIL);

        /* 编码失败，释放动态表资源 */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return NAS_ESM_FAILURE;
    }

    /* 分配OPID，记录空口消息类型 */
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ulOpId            = NAS_ESM_AllocEmmEsmOpId();
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /* 设置是否为紧急PDN连接请求 */
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq     = PS_FALSE;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf              = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /* 调用函数，ESM->EMM发送消息:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ) */
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,                         \
                                                  pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,\
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* 记录空口消息 */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,                      \
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  NAS_ESM_AIR_MSG_DIR_ENUM_UP,              \
                                                  ESM_PDN_CONNECT_REQ);

    /* 启动T3482定时器 */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

    /* 状态转换 */
    NAS_ESM_SetProcTransState(ulStateTblIndex, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

    return NAS_ESM_SUCCESS;
}
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    /* 取出实体中的APN，设置到SDF中 */
    if (NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        pstSdfPara->bitOpApn            = NAS_ESM_OP_TRUE;

        pstSdfPara->stApnInfo.ucApnLen  = pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen;

        NAS_ESM_MEM_CPY(&pstSdfPara->stApnInfo.aucApnName,                      \
                                        &pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,\
                                        pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen);
    }

    /* 取出实体中的PDN类型，设置到SDF中 */
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

    /* 赋值关联CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* 赋值承载ID */
    pstPdnInfoInd->ulEpsbId             = pstEpsbCntxtInfo->ulEpsbId;

    /* 将译码的APN信息转成未译码的APN信息 */
    if(APP_SUCCESS != NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                        &pstEpsbCntxtInfo->stApnInfo))
    {
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_FALSE;
    }
    else
    {
        /* 赋值APN */
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_TRUE;
        pstPdnInfoInd->stApn.ucApnLen   = stTmpApnInfo.ucApnLen;
        NAS_ESM_MEM_CPY(&pstPdnInfoInd->stApn.aucApn,                           \
                                        &stTmpApnInfo.aucApnName,               \
                                        stTmpApnInfo.ucApnLen);
    }

    /* 赋值PDN ADDRESS */
    NAS_ESM_MEM_CPY(&pstPdnInfoInd->stPdnAddr,                                  \
                                        &pstEpsbCntxtInfo->stPdnAddrInfo,       \
                                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* 赋值APN-AMBR，暂时先不填 */

    /* 赋值PCO，暂时先不填 */

    return;
}
VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
)
{
    VOS_UINT8                           i;

    NAS_ESM_INFO_LOG1("NAS_ESM_ConvertBitCidToCid: ulBitCid = ", ulBitCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ConvertBitCidToCid_ENUM, LNAS_ENTRY, ulBitCid);

    /* 循环移位找到CID，目前不存在承载汇聚，因此只能有1个CID */
    for (i = 0; i <= NAS_ESM_MAX_CID; i++)
    {
        /* 右移几位之后的结果为1，CID就是几，找到后返回成功 */
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

    /* 缺省承载且有APN，Back-off算法判定，如果不允许发起，直接给APP回失败 */
    if(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        NAS_ESM_MEM_CPY(&stJudgmentPara,                                        \
                                        &pstPdnEntity->stEhPdnContextInfo.stApn,\
                                        sizeof(APP_ESM_APN_INFO_STRU));
    }
    else
    {
        /* 无APN直接允许发起 */
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

    /* Back-off算法判定，如果不允许发起，返回失败 */
    if (NAS_ESM_SUCCESS != NAS_ESM_IsBackOffAllowedToReconn(pstPdnEntity))
    {
        return NAS_ESM_FAILURE;
    }

    /* 在拒绝原因值#66列表中，且当前驻留PLMN是#66列表的PLMN，返回失败*/
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #66 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_66_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    ulCid = NAS_ESM_ConvertBitCidToCid(pstPdnEntity->stEhPdnContextInfo.ulBitCid);

    /* CID无效，返回失败 */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* 错误PDN类型，返回失败 */
    if ((EHSM_ESM_PDN_TYPE_IPV4 > pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      ||(EHSM_ESM_PDN_TYPE_IPV4V6 < pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect:PDN type err.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_PDN_TYPE_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* 如果当前使用的APN在#50拒绝列表中，返回失败 */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType, \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #50 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_50_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    /* 如果当前使用的APN在#51拒绝列表中，返回失败 */
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

    /* 向APS上报注册承载恢复成功 */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_SUCC);

    /* 删除这条EHRPD承载信息记录 */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* 如果PDN实体数为0，说明恢复承载流程结束，设置EHRPD实体为等待恢复态 */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverSuccProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverSuccProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);
        return;
    }

    /* 取下一条承载 */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulNextPdnIndex))
    {
        /* 获取成功，执行下一条承载恢复处理，如果执行成功，返回 */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulNextPdnIndex))
        {
            return;
        }

        /* 执行失败 */

        /* 向APS上报承载恢复失败 */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulNextPdnIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* 删除这条EHRPD承载信息记录 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulNextPdnIndex);
    }

    /* 获取下一个失败 */
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

    /* 向APS上报承载恢复失败 */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

    /* 删除这条EHRPD承载信息记录 */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* 如果PDN实体数为0，说明恢复承载流程结束，设置EHRPD实体为等待恢复态 */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverFailProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverFailProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);
        return;
    }

    /* 取下一条承载 */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulNextPdnIndex))
    {
        /* 获取成功，执行下一条承载恢复处理，如果执行成功，返回 */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulNextPdnIndex))
        {
            return;
        }

        /* 执行失败 */

        /* 向APS上报承载恢复失败 */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulNextPdnIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* 删除这条EHRPD承载信息记录 */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulNextPdnIndex);
    }

    /* 获取下一个失败 */
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

    /* 根据OPID查找对应的PDN实体索引 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 找到PDN实体，如果是激活缺省承载ACP发送成功，执行恢复成功的处理 */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
    }
    else
    {
        /* 只是PDN REQ发送成功，无动作 */
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

    /* 根据OPID查找对应的PDN实体索引 */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                        = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 找到PDN实体，如果是激活缺省承载ACP发送失败，按发送失败进行特殊的处理 */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        pstPdnEntity->stNwMsgRecord.ucSendFailTimes ++;

        /* 第一次发送失败时启动等待恢复承载成功定时器，防止网侧不再发送缺省承载激活请求导致挂死
        此定时器在删除此承载记录时停止，如果超时，删除此承载进行下一条EHRPD承载恢复流程 */
        if (NAS_ESM_FIRST_FAIL_TIME == pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_TimerStart(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);
        }

        /* 失败次数达最大，认为承载恢复失败 */
        if (NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES <= pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);
            return;
        }

    }
    else
    {
        /* 只是PDN REQ发送失败，无动作，等待T3482定时器超时重发 */
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

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),       \
                                        0,                            \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_CONNECTED;
    pstPdnInfoInd->ulAttachFlag         = ulAttachPdnFlag;

    /* 赋值承载信息 */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}


VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd   = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(      \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoModIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoModIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),                 \
                                        0,                                      \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_MODIFIED;
    pstPdnInfoInd->ulAttachFlag         = PS_FALSE;

    /* 赋值承载信息 */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}


VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),                 \
                                        0,                                      \
                                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*获取对应EpsbCntxtTbl表地址*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_DISCONNECTED;
    pstPdnInfoInd->ulEpsbId             = ulEpsbId;

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}
VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID)
{
    ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pstClearNtfMsg = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstClearNtfMsg = (ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG( \
                                                  sizeof(ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstClearNtfMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmClearAllBearerNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_EHSM_MSG_ENTITY(pstClearNtfMsg),                \
                                                  0,                            \
                                                  NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstClearNtfMsg, ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstClearNtfMsg);
    return;
}


VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* 获取对应PDN实体地址 */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* 恢复成功，向SM发送承载modify ind，接口消息复用 */
    NAS_ESM_SndSmEspBearerMdfIndMsg(pstPdnEntity->ulHandoverEpsbId);

    return;
}



VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstEpsBearInfoInd = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(    \
                                        sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstEpsBearInfoInd)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndApsEhrpdPdnReconnFailMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndApsEhrpdPdnReconnFailMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    /* 获取对应PDN实体地址 */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /*清空*/
    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),        \
                                        0,                            \
                                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /* 去激活，只填承载ID和Cid即可 */
    pstEpsBearInfoInd->enPdpOption      = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId         = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    pstEpsBearInfoInd->ulBitCid         = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /*填写消息头*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* 调用消息发送函数 */
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
        /* 恢复成功，向APS发送承载modify ind   */
        NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(ulIndex);
    }
    else
    {
        /* 恢复失败，向APS发送承载deactive ind */
        NAS_ESM_SndApsEhrpdPdnReconnFailMsg(ulIndex);
    }

    return;
}


VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID)
{
    EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU          *pstDetachMsg        = VOS_NULL_PTR;

    /*分配空间并检验分配是否成功*/
    pstDetachMsg    = (EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG(  \
                                                  sizeof(EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDetachMsg)
    {
        /*打印异常信息*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEmmClLocalDetachNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEmmClLocalDetachNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET(NAS_ESM_GET_MSG_ENTITY(pstDetachMsg),                       \
                                                  0,                            \
                                                  NAS_ESM_GET_MSG_LENGTH(pstDetachMsg));

    /*填写消息头*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstDetachMsg, ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY);

    /* 调用消息发送函数 */
    NAS_ESM_SND_MSG(pstDetachMsg);
    return;
}


VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID)
{
    NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU         *pstEntityOmMsg      = VOS_NULL_PTR;

    /* 分配空间并检验分配是否成功 */
    pstEntityOmMsg  = (NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU*)NAS_ESM_MEM_ALLOC( \
                                                  sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    if (VOS_NULL_PTR == pstEntityOmMsg)
    {
        /*打印异常信息*/
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

    /* 填充EHRPD实体当前状态 */
    pstEntityOmMsg->ulEhrpdPdnTotalNum              = NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM();

    /* 消息上报HIDS */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
    NAS_ESM_MEM_FREE(pstEntityOmMsg);

    return;
}



VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU   *pstEntityOmMsg      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    /* 先上报一下正在使用的PDN实体数量 */
    NAS_ESM_SndOmEhrpdUsedPdnEntityNum();

    /* 逐条上报正在使用的PDN实体信息 */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* 分配空间并检验分配是否成功 */
            pstEntityOmMsg = (NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU*)NAS_ESM_MEM_ALLOC(\
                                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            if (VOS_NULL_PTR == pstEntityOmMsg)
            {
                /*打印异常信息*/
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

            /* 填充EHRPD实体当前状态 */
            pstEntityOmMsg->enEntityState                   = NAS_ESM_GET_EHRPD_ENTITY_STATE();

            /* 本次发消息输出的PDN实体索引号 */
            pstEntityOmMsg->ucEntityIndex                   = (VOS_UINT8)i;
            NAS_ESM_MEM_CPY(&pstEntityOmMsg->stEhPdnEntityInfo,       \
                                        pstPdnEntity,                 \
                                        sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU));

            /* 消息上报HIDS */
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

