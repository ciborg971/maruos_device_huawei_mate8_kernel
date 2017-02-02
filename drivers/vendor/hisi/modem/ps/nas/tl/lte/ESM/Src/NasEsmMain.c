

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmMain.h"
#include    "NasEsmInclude.h"
#include    "NasEsmTest.h"
#include    "LPsOm.h"
#include    "TlPsDrv.h"
/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMMAIN_C
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
NAS_ESM_ENTITY_STRU      g_stNasEsmEntity;                        /*ESM ʵ�嶨��*/
NAS_ESM_ENTITY_STRU      *pg_stNasEsmEntity = &g_stNasEsmEntity;

OM_ESM_STATE_INFO_STRU   g_stEsmOmInfo[APP_ESM_MAX_EPSB_NUM];

extern VOS_VOID  NAS_ERABM_TaskEntry( MsgBlock* pMsg );
extern VOS_UINT32 NAS_ERABM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 NAS_ETC_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  NAS_ETC_TaskEntry( MsgBlock* pMsg );

extern VOS_UINT32 NAS_LPP_PidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  NAS_LPP_TaskEntry(MsgBlock * pMsg);

/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : IP_TaskEntry
 Description     : ɾ��NAS IP��ع��ܣ����ǿ��ǵ�ֱ��ɾ�����ܻᵼ�������ָ�룬
                   ����д�˿պ�������PID������Ϊ���á�
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :

*****************************************************************************/
VOS_VOID  IP_TaskEntry
(
    MsgBlock                           *pstMsg
)
{
    return;
}

/*****************************************************************************
 Function Name  : IP_PidInit
 Discription    : ɾ��NAS IP��ع��ܣ����ǿ��ǵ�ֱ��ɾ�����ܻᵼ�������ָ�룬
                   ����д�˿պ�������PID������Ϊ���á�
 Input          :
 Output         : None
 Return         : None
 History:
*****************************************************************************/
VOS_UINT32 IP_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    return VOS_OK;
}


VOS_VOID  NAS_ESM_TaskEntry(MsgBlock * pMsg)
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;
    #if (VOS_WIN32 != VOS_OS_VER)
    DIAG_TRANS_IND_STRU stDiagTransInd;
    #endif

    /* �ж���ڲ����Ƿ�Ϸ�*/
    if( VOS_NULL_PTR == pMsg)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_TaskEntry_ENUM, LNAS_NULL_PTR);
        return;
    }

#if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList(pMsg);
#endif


    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    NAS_ESM_PrintEsmRevMsg(pHeader,NAS_COMM_GET_ESM_PRINT_BUF());

    switch(pHeader->ulSenderPid)
    {
        case WUEPS_PID_USIM:
            NAS_ESM_UsimMsgDistr(pMsg);
            break;

        /*�����EMM��Ϣ������EMM������*/
        case PS_PID_MM:
            NAS_ESM_EmmMsgDistr(pMsg);
            break;

        /*�����RABM��Ϣ������RABM������*/
        case PS_PID_RABM:
            NAS_ESM_RabmMsgDistr(pMsg);
            break;

        /*�����APP��Ϣ������APP������*/
        case PS_PID_APP:
            NAS_ESM_AppMsgDistr(pMsg);
            break;

        case WUEPS_PID_TAF:
            NAS_ESM_SmMsgDistr(pMsg);
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case UEPS_PID_EHSM:
            NAS_ESM_EhsmMsgDistr(pMsg);
            break;
        #endif

        case MSP_PID_DIAG_APP_AGENT:
            (VOS_VOID)LTE_MsgHook((VOS_VOID*)pMsg);
            NAS_ESM_OmMsgDistr(pMsg);
            break;

        /*�����Timer��Ϣ������Timer���������*/
        case VOS_PID_TIMER:
            NAS_ESM_TimerMsgDistr(pMsg);
            break;
        /* del by yanglei 00307272 for OM_DIAG_PHASE2 2015-07-17 begin */
        /* xiongxianghui00253310 add fot errlog 20131212 begin */
        /*�����OM��Ϣ������OM������*/
        /*#if (FEATURE_PTM == FEATURE_ON)
        case MSP_PID_DIAG_APP_AGENT:
            NAS_ESM_OmMsgDistrForAcpuPidOm(pMsg);
            break;
        #endif*/
        /* xiongxianghui00253310 add fot errlog 20131212 end */
        /* del by yanglei 00307272 for OM_DIAG_PHASE2 2015-07-17 end */
        /*���Ͷ�����󣬱���*/
        default:
            NAS_ESM_WARN_LOG("NAS_ESM_TaskEntry:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_TaskEntry_ENUM, LNAS_MSG_INVALID);
            break;
    }
    if (OM_ESM_REPORT_INFO_OPEN == g_NasEsmOmInfoIndFlag)
    {
        if (NAS_ESM_FAILURE == NAS_ESM_CompareEsmInfo())
        {
            #if (VOS_WIN32 != VOS_OS_VER)
            PS_MEM_SET(&stDiagTransInd, 0, sizeof(DIAG_TRANS_IND_STRU));
            stDiagTransInd.ulMsgId = DIAG_CMD_ESM_APP_ESM_INFO_IND;
            stDiagTransInd.ulLength = (sizeof(OM_ESM_STATE_INFO_STRU))*OM_ESM_MAX_EPSB_NUM;
            stDiagTransInd.pData = (VOS_VOID *)(g_stEsmOmInfo);
            stDiagTransInd.ulModule = LPS_OM_ID(PS_PID_ESM, PS_PRINT_INFO);
            stDiagTransInd.ulPid = PS_PID_ESM;

            /* ͨ��DIAG�ϱ� */
            (VOS_VOID)LDRV_DIAG_COMMONREPORT(&stDiagTransInd);
            #endif
        }
    }

    NAS_ESM_DtJudgeifNeedRpt();

    /* xiongxianghui00253310 modify for ftmerrlog begin */
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_OmInfoIndProc();
    #endif
    /* xiongxianghui00253310 modify for ftmerrlog end   */
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,begin */
    /* ESM��Ϣ���������ʹ�ӡ */
    TLPS_SendPrintBufferInfo();
    /* add by yanglei 00307272 for PRINTLOG_SEND,2015-08-14,end */
}
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_InitAttachBearerReestInfo()
{
    VOS_UINT32 ulResult;
    NAS_ESM_ENTITY_STRU *pEsmEntityInfo = NAS_ESM_Entity();
    LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU stTmpAttachBearerNvData = {0};
    /*lint -e718*/
    /*lint -e732*/
    ulResult = LPs_NvimItem_Read((EN_NV_ID_ATTACH_BEARER_RE_ESTABLISH),\
                            (VOS_VOID *)(&stTmpAttachBearerNvData),\
                            sizeof(LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU));
    /*lint +e732*/
    /*lint +e718*/

    /* �ж϶�ȡ��� */
    if (ulResult != ERR_MSP_SUCCESS)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_AttachBearerReestInfoInit:ERROR: Cannot Read from NV .");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_InitAttachBearerReestInfo_ENUM, LNAS_FAIL);

        stTmpAttachBearerNvData.bitOpAttachBearerReest = NAS_ESM_OP_FALSE;
        stTmpAttachBearerNvData.ulReestTimeLen = 0;
    }

    /*  �ж϶�ȡ��������Ч�� */
    if ((NAS_ESM_OP_TRUE == stTmpAttachBearerNvData.bitOpAttachBearerReest) &&
        (stTmpAttachBearerNvData.ulReestTimeLen > TI_NAS_ESM_ATTACH_BEARER_REEST_TIMER_LEN))
    {
        NAS_ESM_ERR_LOG("NAS_ESM_AttachBearerReestInfoInit:Timer is too long, use default value");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_InitAttachBearerReestInfo_ENUM, LNAS_PARAM_INVALID);
        stTmpAttachBearerNvData.ulReestTimeLen = TI_NAS_ESM_ATTACH_BEARER_REEST_TIMER_LEN;
    }

    /* ������Ч���ݵ�ESM Entity */
    pEsmEntityInfo->stAttachBearerReestInfo.stNvData.bitOpAttachBearerReest= stTmpAttachBearerNvData.bitOpAttachBearerReest;
    pEsmEntityInfo->stAttachBearerReestInfo.stNvData.bitOpRsv = 0;
    pEsmEntityInfo->stAttachBearerReestInfo.stNvData.ulReestTimeLen =
                                stTmpAttachBearerNvData.ulReestTimeLen * 1000;

    pEsmEntityInfo->stAttachBearerReestInfo.ulEpsbId = NAS_ESM_UNASSIGNED_EPSB_ID;

    NAS_ESM_MEM_SET(&(pEsmEntityInfo->stAttachBearerReestInfo.stTimerInfo), 0, sizeof(NAS_ESM_TIMER_STRU));
    pEsmEntityInfo->stAttachBearerReestInfo.stTimerInfo.enPara = TI_NAS_ESM_ATTACH_BEARER_REEST;

    NAS_ESM_INFO_LOG2("NAS_ESM_AttachBearerReestInfoInit: Param ",
                      pEsmEntityInfo->stAttachBearerReestInfo.stNvData.bitOpAttachBearerReest,
                      pEsmEntityInfo->stAttachBearerReestInfo.stNvData.ulReestTimeLen);
}


VOS_VOID NAS_ESM_Init(VOS_VOID)
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_SM                           START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_Init_ENUM, LNAS_ENTRY);

    /*��ʼ��SMʵ��*/
    NAS_ESM_MEM_SET((VOS_VOID*)NAS_ESM_Entity(),NAS_ESM_NULL,sizeof(NAS_ESM_ENTITY_STRU));

    /*����EMM��״̬Ϊδע��*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /*����L MODE��״̬ΪSUSPENDED*/
    NAS_ESM_SetLModeStatus(NAS_ESM_L_MODE_STATUS_SUSPENDED);
    /*�����Ѽ���ĳ�����ĿΪ��*/
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

#ifdef PS_ITT_PC_TEST_NAS
    /*NAS ST�����£���������������ע��ʱʹ����PTIֵΪ2������PTI��ʼ��Ϊ1������PTI���亯�������2��ʼʹ��*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
#else
    /*PTI��ʼ��Ϊ0��ע��ʱ������PTI���亯�������1��ʼʹ��*/
    /*lint -e778*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);
    /*lint +e778*/
#endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);

    /*��ʼ�����ز���*/
    NAS_ESM_BearerCntxtParaInit();

    /*��ʼ�����ع���ʽ*/
    NAS_ESM_BearerManageInfoInit(NAS_ESM_GetBearerManageInfoAddr());

    /*��ʼ��״̬����Ϣ*/
    for( ulCnt = 0; ulCnt < NAS_ESM_MAX_STATETBL_NUM; ulCnt++ )
    {
        NAS_ESM_RelStateTblResource(ulCnt);
    }

    /*��ʼ��������Ϣ*/
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        NAS_ESM_InitEpsbCntxtInfo(ulCnt);

        NAS_ESM_MEM_SET(&(g_stEsmOmInfo[ulCnt - NAS_ESM_MIN_EPSB_ID]),
                        NAS_ESM_NULL,
                        sizeof(OM_ESM_STATE_INFO_STRU));
    }

    /* ��ʼ��ESM������ */
    NAS_COMM_InitBuff(NAS_COMM_BUFF_TYPE_ESM);

    /* ��ʼ��ע������������ */
    NAS_ESM_InitAttachBearerReestInfo();

    /* ESM�����ʼ�� */
    NAS_ESM_DebugInit();

    /* ��ʼ���ӳ��ͷŷǽ���PDN���Ӷ�ʱ�� */
    NAS_ESM_Entity()->stDeferRelNonEmcTimerInfo.enPara = TI_NAS_ESM_REL_NON_EMC_BEARER;

    /* ��LOCAL IP��NV��ж�UE�Ƿ�֧��LOCAL IP */
    NAS_ESM_InitLocalIpsupportInfo();

    /* xiongxianghui00253310 modify for ftmerrlog begin */
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_FtmInfoInit();
    #endif
    /* xiongxianghui00253310 modify for ftmerrlog end   */

}


VOS_VOID NAS_ESM_ClearEsmResource( VOS_VOID )
{
    VOS_UINT32                          ulCnt               = NAS_ESM_NULL;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    #endif


    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearEsmResource is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearEsmResource_ENUM, LNAS_ENTRY);

    /*������Ϣ��¼֪ͨAPP*/
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_FALSE);

    /* ����EMM��״̬Ϊδע�� */
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /* ���֧��˫APN����ֹͣ��Ӧ��ʱ����������ע�������Ч */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* �����Ѽ���ĳ�����ĿΪ�� */
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

#ifdef PS_ITT_PC_TEST_NAS
    /*NAS ST�����£���������������ע��ʱʹ����PTIֵΪ2������PTI��ʼ��Ϊ1������PTI���亯�������2��ʼʹ��*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
#else
    /*PTI��ʼ��Ϊ0��ע��ʱ������PTI���亯�������1��ʼʹ��*/
    /*lint -e778*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);
    /*lint +e778*/

    /* CID0��PS�ںϺ�Ƚ����⣬��ESMά����������NV�����ݻ���ڲ�һ��, �轫CID0��ʼ��Ϊר������ */
    NAS_ESM_ClearCid0StaticInfo();
#endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);


    /* ��ʼ��CID 21~31 ������̬��Ϣ */
    NAS_ESM_ClearNwCtrlSdfPara();
    /* ֪ͨAPP��SM ������ر��ͷţ���ʼ��������Ϣ */
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        if (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(ulCnt))
        {
            /* ��ʼ��������Ϣ */
            NAS_ESM_InitEpsbCntxtInfo(ulCnt);
            continue;
        }

        #ifndef PS_ITT_PC_TEST_NAS
        /* ֪ͨAPP ������ر��ͷ� */
        NAS_ESM_InformAppBearerRel(ulCnt);

        /* ֪ͨSM ������ر��ͷ� */
        NAS_ESM_SndSmEspBearerDeactIndMsg(ulCnt);
        #endif

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulCnt);
        /* �����ȱʡ���أ�֪ͨEHSM����ȥ���� */
        if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
        {
            NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(ulCnt);
        }
        #endif

        /* ��ʼ��������Ϣ */
        NAS_ESM_InitEpsbCntxtInfo(ulCnt);
    }

    /* ��ʼ��ҵ�����Ķ�̬��Ϣ */
    for( ulCnt = 0; ulCnt < NAS_ESM_MAX_CID_NUM; ulCnt++ )
    {
        NAS_ESM_MEM_SET(NAS_ESM_GetSdfCntxtInfo(ulCnt),
                        NAS_ESM_NULL,
                        sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }

    /* ��ʼ��PDN���ӵĸ��� */
    NAS_ESM_SetCurPdnNum(NAS_ESM_NULL);

    /* ��ʼ�����Ϳտ���Ϣ�Ľṹ�� */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* ���ESM������ */
    NAS_ESM_ClearEsmBuff();

}
VOS_VOID NAS_ESM_InitEpsbCntxtInfo(VOS_UINT32 ulEpsbId)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbInfo         = VOS_NULL_PTR;

    pstEpsbInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    NAS_ESM_MEM_SET(pstEpsbInfo,
                    NAS_ESM_NULL,
                    sizeof(NAS_ESM_EPSB_CNTXT_INFO_STRU));

    pstEpsbInfo->bitOpCId             = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpApn             = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpPco             = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpPdnAddr         = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpEpsQos          = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpEsmCause        = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpApnAmbr         = NAS_ESM_OP_FALSE;
    pstEpsbInfo->bitOpGateWayAddrInfo = NAS_ESM_OP_FALSE;
    pstEpsbInfo->ulEpsbId             = ulEpsbId;
    pstEpsbInfo->enBearerCntxtType    = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstEpsbInfo->enBearerCntxtState   = NAS_ESM_BEARER_STATE_INACTIVE;
    pstEpsbInfo->ulLinkedEpsbId       = NAS_ESM_UNASSIGNED_EPSB_ID;
}


VOS_UINT32 NAS_ESM_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_ESM_Init();
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}


/*added by hujianbo for PTT*/
VOS_UINT32 NAS_PTT_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    (VOS_VOID)vos_printf("NAS_PTT_PidInit Pid:%d\n", PS_PID_PTT);
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }

    return VOS_OK;
}

VOS_VOID  NAS_PTT_TaskEntry( MsgBlock* pMsg )
{
    (VOS_VOID)vos_printf("NAS_PTT_TaskEntry:PTT Rcv Error Msg %x!", pMsg);

    return;
}

VOS_UINT32 CM_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                #if (VOS_OS_VER != VOS_WIN32)
                ulRet = VOS_RegisterPIDInfo(PS_PID_PTT,
                                            NAS_PTT_PidInit,
                                            NAS_PTT_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }
                #endif

                ulRet = VOS_RegisterPIDInfo(PS_PID_ESM,
                                            NAS_ESM_PidInit,
                                            NAS_ESM_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(PS_PID_RABM,
                                            NAS_ERABM_PidInit,
                                            NAS_ERABM_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(PS_PID_LPP,
                                            NAS_LPP_PidInit,
                                            NAS_LPP_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(PS_PID_TC,
                                            NAS_ETC_PidInit,
                                            NAS_ETC_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterPIDInfo(PS_PID_IP,
                                            IP_PidInit,
                                            IP_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterMsgTaskPrio(PS_FID_CM, VOS_PRIORITY_M5);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
                }

                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;
    }

    return VOS_OK;
}
VOS_VOID LNAS_LPSOM_GetIpAddrInfo(APP_LPS_CAMPED_CELL_INFO_STRU *pstCampedCellInfo)
{
    VOS_UINT32 i = 0;

    for (i = 0; i < NAS_ESM_MAX_EPSB_NUM; i++)
    {
        pstCampedCellInfo->astEpsbCntxtInfo[i].ulEpsbId = pg_stNasEsmEntity->astEpsbCntxtInfo[i].ulEpsbId;
        NAS_ESM_MEM_CPY(&(pstCampedCellInfo->astEpsbCntxtInfo[i].stPdnAddrInfo),
                            &(pg_stNasEsmEntity->astEpsbCntxtInfo[i].stPdnAddrInfo),
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }

    return;
}


VOS_VOID NAS_ESM_ClearEsmResoureWhenEstingEmcPdn(VOS_VOID)
{
    VOS_UINT32 ulCnt = 0;

    NAS_ESM_INFO_LOG("NAS_ESM_ClearEsmResoureWhenEstingEmcPdn: enter");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearEsmResoureWhenEstingEmcPdn_ENUM, LNAS_ENTRY);


    /*����ESM״̬Ϊ����ע��*/
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_ATTACHING);

    /* ���֧��˫APN����ֹͣ��Ӧ��ʱ����������ע�������Ч */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* ����ȥ���������֮������г��� */
    for( ulCnt = NAS_ESM_MIN_EPSB_ID; ulCnt <= NAS_ESM_MAX_EPSB_ID; ulCnt++ )
    {
        /*
         * ����Ǽ���ķǽ���Ĭ�ϳ��أ���ȥ���
         * ����ǷǼ����Ĭ�ϳ��ػ������Ĭ�ϳ��أ�����Ҫȥ�������
         * �����ר�г��أ�����NAS_ESM_DeactBearerAndInformApp�н���ȥ����
         */
        if ((NAS_ESM_BEARER_TYPE_DEFAULT == NAS_ESM_GetBearCntxtType(ulCnt)) &&
            (NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulCnt)))
        {
            NAS_ESM_DeactBearerAndInformApp(ulCnt);
        }
    }

    /* ��ʼ��PDN���ӵĸ��� */
    NAS_ESM_SetCurPdnNum(NAS_ESM_NULL);

    /* ֪ͨRABM�����Դ */
    NAS_ESM_SndEsmRabmRelIndMsg();

    /*�����̬��������س���*/
    NAS_ESM_ClearStateTable(APP_ERR_SM_NON_EMERGENCY_NOT_ALLOWED, PS_TRUE);

    /* ��ʼ�����Ϳտ���Ϣ�Ľṹ�� */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* ���ESM������ */
    NAS_ESM_ClearEsmBuff();
}
/*lint +e961*/
/*lint +e960*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmMain.c */

