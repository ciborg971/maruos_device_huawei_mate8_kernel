




/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "EmmRabmInterface.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmEsmMsgProc.h"
#include  "CdsErabmInterface.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMRRCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMRRCMSGPROC_C
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
VOS_VOID NAS_ERABM_RrcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU            *pRrcMsg;

    pRrcMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RrcMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RrcMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pRrcMsg->ulMsgName)
    {
        /*����յ�����RRC_RABM_RAB_IND��Ϣ������NAS_ERABM_RcvRabmRrcRabInd����*/
        case ID_LRRC_LRABM_RAB_IND:
            NAS_ERABM_RcvRabmRrcRabInd((LRRC_LRABM_RAB_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����RRC_RABM_STATUS_IND��Ϣ������NAS_ERABM_RcvRabmRrcStatusInd����*/
        case ID_LRRC_LRABM_STATUS_IND:
            NAS_ERABM_RcvRabmRrcStatusInd((LRRC_LRABM_STATUS_IND_STRU *) pRcvMsg);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_RrcMsgDistr:WARNING:RRC->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RrcMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}



VOS_VOID NAS_ERABM_RcvRbSetupSucc( VOS_UINT32 ulEpsbId, VOS_UINT32 ulRbId )
{
    /*APP_DATA_STATUS_CALLBACK_FUNC AppDataStatusFun;*/

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRbSetupSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRbSetupSucc_ENUM, LNAS_ENTRY);

    /*��RBID��¼��EPS���ؼ������*/
    NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId,ulRbId);

    /*��¼RB������״̬*/
    NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_CONNECTED);

    /*֪ͨAPP��������������APP�ṩ�ĺ���*/
    /*AppDataStatusFun(NAS_ERABM_GetEpsbIdInfo(ulEpsbId),NAS_ERABM_APP_DATA_STATUS_START,NAS_ERABM_APP_DATA_START_RBSETUP_SUCC);*/
}


VOS_VOID NAS_ERABM_RcvRbReconfig( VOS_UINT32 ulEpsbId, VOS_UINT32 ulRbId )
{
    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRbReconfig is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRbReconfig_ENUM, LNAS_ENTRY);

    /* ֻ�г��ش��ڼ���״̬���޸Ĺ�����ϵ */
    if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
    {
        /*��RBID��¼��EPS���ؼ������*/
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId,ulRbId);

        NAS_ERABM_LOG2("NAS_ERABM_RcvRbReconfig, RAB change:", ulEpsbId, ulRbId);
        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_RcvRbReconfig_ENUM, 2, ulEpsbId, ulRbId);
    }
}
VOS_VOID  NAS_ERABM_RcvRbSetupFail( VOS_UINT32 ulEpsbId )
{
    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRbSetupFail is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRbSetupFail_ENUM, LNAS_ENTRY);

    /*��RBID��Ϊ��ЧID*/
    NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);

    /*��¼RB�ķ�����״̬*/
    NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRbRelease
 Description     : ����rrc�ͷ�rb��Ϣ
 Input           : VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683              2009-4-27  Draft Enact
    2.lihong00150010            2009-12-24  Modify

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRbRelease( VOS_UINT32 ulEpsbId )
{
    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRbRelease is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRbRelease_ENUM, LNAS_ENTRY);

    /*��RBID��Ϊ��ЧID*/
    NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);

    /*��¼RB�ķ�����״̬*/
    NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
}
VOS_VOID  NAS_ERABM_InformEsmBearerStatus( VOS_UINT8 uclOpid )
{
    VOS_UINT32                          ulRbNumWithRb  = NAS_ERABM_NULL;
    VOS_UINT32                          ulActEpsbNum   = NAS_ERABM_NULL;
    VOS_UINT32                          aulEpsIdWithRb[NAS_ERABM_MAX_EPSB_NUM] = {0};
    VOS_UINT32                          ulEpsbId         = NAS_ERABM_NULL;

    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId<= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        NAS_ERABM_LOG2("NAS_ERABM_InformEsmBearerStatus", NAS_ERABM_GetEpsbStateInfo(ulEpsbId), NAS_ERABM_GetRbStateInfo(ulEpsbId));
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_InformEsmBearerStatus_ENUM, LNAS_ERABM_GetEpsbStateInfo, NAS_ERABM_GetEpsbStateInfo(ulEpsbId));
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_InformEsmBearerStatus_ENUM, LNAS_ERABM_GetRbStateInfo, NAS_ERABM_GetRbStateInfo(ulEpsbId));

        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            ulActEpsbNum ++;
            if(NAS_ERABM_RB_DISCONNECTED != NAS_ERABM_GetRbStateInfo(ulEpsbId))
            {
                aulEpsIdWithRb[ulRbNumWithRb] = ulEpsbId;
                ulRbNumWithRb++;
            }
        }
    }

    NAS_ERABM_LOG1("NAS_ERABM_InformEsmBearerStatus", ulActEpsbNum);
    TLPS_PRINT2LAYER_INFO1(NAS_ERABM_InformEsmBearerStatus_ENUM, LNAS_ERABM_ActEpsbNum, ulActEpsbNum);

    /*ֻ���ڴ���EPS���صĳ����£�����Ҫ֪ͨESM*/
    if(ulActEpsbNum > 0)
    {
        NAS_ERABM_SndRabmEsmBearerStatusReq(aulEpsIdWithRb,ulRbNumWithRb,uclOpid);
    }
}
VOS_VOID  NAS_ERABM_RcvRabmRrcRabInd(const LRRC_LRABM_RAB_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulRbSetupReqNum  = 0;             /*��¼��������RB����*/
    VOS_UINT32                          ulLoop           = 0;
    VOS_UINT32                          ulRabcnt         = pRcvMsg->ulRabCnt;
    PS_BOOL_ENUM_UINT8                  enIsRecSetupSucc = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsRecSetupFail = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsRecRelease   = PS_FALSE;
    VOS_UINT32                          aulRabId[NAS_ERABM_MAX_EPSB_NUM] = {0};
    /*APP_DATA_STATUS_CALLBACK_FUNC     AppDataStatusFun = APP_DATA_STATUS_FUNC;*/

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmRrcRabInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmRrcRabInd_ENUM, LNAS_ENTRY);

    /*����RB�Ĳ������ͽ�����Ӧ����*/
    for (ulLoop = 0; ulLoop < ulRabcnt; ulLoop++)
    {
        switch ( pRcvMsg->astRabInfo[ulLoop].enRabChangeType)
        {
            /*�յ�������RB��Ϣ��LTEϵͳ�в����յ�RRC_NAS_RAB_SETUP_REQUEST*/
            case LRRC_LNAS_RAB_SETUP_REQUEST:
                /*��Ҫ������RB����Ϣ��������ʱ����*/
                NAS_ERABM_SetRbSetupRbIdInfo(ulRbSetupReqNum, pRcvMsg->astRabInfo[ulLoop].ulRbId);
                NAS_ERABM_SetRbSetupEpsbIdInfo(ulRbSetupReqNum, pRcvMsg->astRabInfo[ulLoop].ulRabId);
                ulRbSetupReqNum++;
                NAS_ERABM_SetRbNumInfo(ulRbSetupReqNum);
                break;

            /*�յ�RB�����ɹ���Ϣ*/
            case LRRC_LNAS_RAB_SETUP_SUCCESS:
                NAS_ERABM_RcvRbSetupSucc( pRcvMsg->astRabInfo[ulLoop].ulRabId, pRcvMsg->astRabInfo[ulLoop].ulRbId );
                enIsRecSetupSucc = PS_TRUE;
                break;

            /*�յ�RB����ʧ����Ϣ*/
            case LRRC_LNAS_RAB_SETUP_FAILURE:
                NAS_ERABM_RcvRbSetupFail( pRcvMsg->astRabInfo[ulLoop].ulRabId );
                enIsRecSetupFail = PS_TRUE;
                break;

            /*�յ�RB�ͷ���Ϣ*/
            case LRRC_LNAS_RAB_RELEASE:
                NAS_ERABM_RcvRbRelease(pRcvMsg->astRabInfo[ulLoop].ulRabId);
                enIsRecRelease = PS_TRUE;

                /*֪ͨAPPֹͣ����,����APP�ṩ�ĺ���*/
                /*AppDataStatusFun(pRcvMsg->astRabInfo[ulLoop].ulRabId,NAS_ERABM_APP_DATA_STATUS_STOP,0xFF);*/
                break;
            /*�յ�DRB������Ϣ*/
            case LRRC_LNAS_RAB_RECONFIG:
                NAS_ERABM_RcvRbReconfig(pRcvMsg->astRabInfo[ulLoop].ulRabId, pRcvMsg->astRabInfo[ulLoop].ulRbId);
                break;
            default:
                /*��ӡ������Ϣ*/
                NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmRrcRabInd: the message is error!");
                TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmRrcRabInd_ENUM, LNAS_MSG_INVALID);
                break;
         }
    }

    /* �����յ�����������RB��ԭ�ⲻ�����γ�RRC_RABM_RAB_RSP��Ϣ */
    if (ulRbSetupReqNum > 0)
    {
        for (ulLoop = 0; ulLoop < NAS_ERABM_GetRbNumInfo(); ulLoop++)
        {
            aulRabId[ulLoop] = NAS_ERABM_GetRbSetupEpsbIdInfo(ulLoop);
        }

        /*��RRC�ظ�RRC_RABM_RAB_RSP��Ϣ*/
        NAS_ERABM_SndRabmRrcRabRsp(aulRabId, NAS_ERABM_GetRbNumInfo());

        return ;
    }

    /* RRC_RABM_RAB_IND��Ϣ������� */
    NAS_ERABM_RrcRabIndResultProc(enIsRecSetupSucc, enIsRecSetupFail, enIsRecRelease);
}

VOS_VOID  NAS_ERABM_RcvRabmRrcStatusMsgProc( VOS_UINT32 ulRabCnt,
                                                             VOS_UINT32 ulStatus,
                                                             const VOS_UINT32 *pulEpsbId)

{
    VOS_UINT32                           ulLoop           = 0;
    VOS_UINT32                           ulAllRbIsConn    = NAS_ERABM_SUCCESS;
    /*APP_DATA_STATUS_CALLBACK_FUNC      AppDataStatusFun;*/

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmRrcStatusMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmRrcStatusMsgProc_ENUM, LNAS_ENTRY);

    if (LRRC_LNAS_RAB_STATUS_STOP == ulStatus)
    {
        for (ulLoop = 0; ulLoop < ulRabCnt; ulLoop++)
        {
            /*����RB��״̬Ϊ��̬ͣ*/
            NAS_ERABM_SetRbStateInfo(pulEpsbId[ulLoop], NAS_ERABM_RB_SUSPENDED);

            /*֪ͨAPP��ͣ����,����APP�ṩ�ĺ���*/
            /*AppDataStatusFun(pulEpsbId[ulLoop], NAS_ERABM_APP_DATA_STATUS_STOP, NAS_ERABM_APP_DATA_START_RRC_IND);*/
        }
        /* lihong00150010 emergency tau&service begin */
        /*����������ʱ������ʱ֪ͨEMM�ͷ�RRC��·*/
        NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_DRB_RESUME_LENGTH,
                                NAS_ERABM_WAIT_RB_RESUME_TIMER,
                                NAS_ERABM_WAIT_RB_RESUME_TIMER);
    }   /* lihong00150010 emergency tau&service end */
    else if (LRRC_LNAS_RAB_STATUS_CONTINUE == ulStatus)
    {
        for (ulLoop = 0; ulLoop < ulRabCnt; ulLoop++)
        {
            if ( NAS_ERABM_ILL_RB_ID != NAS_ERABM_GetEpsbRbIdInfo(pulEpsbId[ulLoop]))
            {
                /* �����ǰ�ֳ��ص�DRB�ɷ�����̬ת������̬ */
                if (NAS_ERABM_RB_CONNECTED != NAS_ERABM_GetRbStateInfo(pulEpsbId[ulLoop]))
                {
                    ulAllRbIsConn = NAS_ERABM_FAILURE;
                }
                /*����RB��״̬Ϊ����̬*/
                NAS_ERABM_SetRbStateInfo(pulEpsbId[ulLoop], NAS_ERABM_RB_CONNECTED);
            }

            /*֪ͨAPP�ָ�����*/
            /*AppDataStatusFun(pulEpsbId[ulLoop], NAS_ERABM_APP_DATA_STATUS_START, NAS_ERABM_APP_DATA_START_RRC_IND);*/
        }

        NAS_ERABM_TimerStop( NAS_ERABM_WAIT_RB_RESUME_TIMER);

        /* ֪ͨL2���ͻ�������ݰ� */
        /*APPITF_SendDataofRabmBuf();*/

        /* ֻ�е���DRB�ɷ�����̬ת������̬ʱ�Ÿ�CDS�����ι������� */
        if (NAS_ERABM_FAILURE == ulAllRbIsConn)
        {
            /* ֪ͨCDS�������ι��� */
            NAS_ERABM_SndErabmCdsSndBuffDataInd(CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_DRB_CONN);

            /* �����������������־*/
            NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);
        }

        /* L-GU�л�����CCOʧ�ܣ����˳ɹ������£� RRC�����ϱ�LRRC_LRABM_RAB_IND��Ϣ��
           ��ֻ�ϱ�LRRC_LRABM_STATUS_IND��Ϣ�ָ�������ERABMͨ��EMM_ERABM_DRB_SETUP_IND
           ��Ϣ֪ͨEMM������������̬��Ŀǰ���յ��ָ�������Ϣ������EMM_ERABM_DRB_SETUP_IND
           ��Ϣ�����������Ż����л�����CCO���˳ɹ������ŷ� */
    }

    else
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmRrcStatusMsgProc:WARNING: RRC STATE non-exist!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmRrcStatusMsgProc_ENUM, LNAS_FUNCTION_LABEL1);
    }
}


VOS_VOID  NAS_ERABM_RcvRabmRrcStatusInd(const LRRC_LRABM_STATUS_IND_STRU *pRcvMsg )
{
    VOS_UINT32                          ulRabCnt = 0;
    VOS_UINT32                          ulLoop = 0;
    VOS_UINT32                          aulEpsbId[NAS_ERABM_MAX_EPSB_NUM] = {0};

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmRrcStatusInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmRrcStatusInd_ENUM, LNAS_ENTRY);

    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmRrcStatusInd:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmRrcStatusInd_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    ulRabCnt = pRcvMsg->ulRabCnt;

    if (NAS_ERABM_NULL == ulRabCnt)
    {
        for (ulLoop = 0; ulLoop < NAS_ERABM_MAX_EPSB_NUM; ulLoop++)
        {
            aulEpsbId[ulLoop] = ulLoop + NAS_ERABM_MIN_EPSB_ID;
        }

        NAS_ERABM_RcvRabmRrcStatusMsgProc(NAS_ERABM_MAX_EPSB_NUM, pRcvMsg->enStatus, aulEpsbId);
    }
    else
    {
        NAS_ERABM_RcvRabmRrcStatusMsgProc(ulRabCnt, pRcvMsg->enStatus, pRcvMsg->aulRabId);
    }

    /*��RRC�ظ�*/
    NAS_ERABM_SndRabmRrcStatusRsp(LRRC_LNAS_STATUS_SUCC);
}


VOS_VOID NAS_ERABM_SndRabmRrcQosUpdateReq( VOS_VOID )
{
    LRRC_LRABM_QOS_UPDATE_REQ_STRU    *pstQosUpdateReq  = VOS_NULL_PTR;

    /*��ڲ�����飬ÿ��֪ͨRRC��EPS��������Ϊ1(Ŀǰû�ж����κβ���)*/

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstQosUpdateReq = (LRRC_LRABM_QOS_UPDATE_REQ_STRU*)NAS_ERABM_ALLOC_MSG(
                                        sizeof(LRRC_LRABM_QOS_UPDATE_REQ_STRU));
    if ( VOS_NULL_PTR == pstQosUpdateReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmRrcQosUpdateReq:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_RRC_MSG_ENTITY(pstQosUpdateReq), NAS_ERABM_NULL, NAS_ERABM_GET_MSG_LENGTH(pstQosUpdateReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_RRC_MSG_HEAD(pstQosUpdateReq, ID_LRRC_LRABM_QOS_UPDATE_REQ);

    /* ������Ϣ���ͺ���    */
    NAS_ERABM_SND_MSG(pstQosUpdateReq);

}
VOS_VOID NAS_ERABM_SndRabmRrcRabRsp(const VOS_UINT32* pulRabId,
                                                  VOS_UINT32 ulRabCnt)
{
    LRRC_LRABM_RAB_RSP_STRU    *pstRabRsp  = VOS_NULL_PTR;

    /*��ڲ�����飬ÿ�λظ�RRC��EPS�����������ΪNAS_ERABM_MAX_EPSB_NUM*/
    if ((VOS_NULL_PTR == pulRabId)|| (ulRabCnt > NAS_ERABM_MAX_EPSB_NUM))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmRrcRabRsp:ERROR:Input para error!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_SndRabmRrcRabRsp_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRabRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(LRRC_LRABM_RAB_RSP_STRU));
    if (VOS_NULL_PTR == pstRabRsp)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmRrcRabRsp:ERROR:Alloc msg fail!");
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_RRC_MSG_ENTITY(pstRabRsp), NAS_ERABM_NULL, NAS_ERABM_GET_MSG_LENGTH(pstRabRsp));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_RRC_MSG_HEAD(pstRabRsp,ID_LRRC_LRABM_RAB_RSP);

    /*֪ͨRRC��EPS���������������Ϣ����д��Ϣʵ��*/
    pstRabRsp->ulRabCnt = ulRabCnt;
    NAS_ERABM_MEM_CPY((VOS_UINT8*)pstRabRsp->aulRabId, (VOS_UINT8*)pulRabId,
              (pstRabRsp->ulRabCnt)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /* ������Ϣ���ͺ���    */
    NAS_ERABM_SND_MSG(pstRabRsp);

}


VOS_VOID  NAS_ERABM_SndRabmRrcStatusRsp( VOS_UINT32 ulResult )
{
   LRRC_LRABM_STATUS_RSP_STRU    *pstStatusRsp = VOS_NULL_PTR;

   /*��ڲ������*/
    if ((ulResult != LRRC_LNAS_STATUS_SUCC)&& (ulResult != LRRC_LNAS_STATUS_FAIL))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmRrcStatusRsp:ERROR:Input para error!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_SndRabmRrcStatusRsp_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstStatusRsp = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(LRRC_LRABM_STATUS_RSP_STRU));
    if ( VOS_NULL_PTR == pstStatusRsp )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmRrcRabRsp:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET(NAS_ERABM_GET_RRC_MSG_ENTITY(pstStatusRsp), 0, NAS_ERABM_GET_MSG_LENGTH(pstStatusRsp));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_RRC_MSG_HEAD(pstStatusRsp, ID_LRRC_LRABM_STATUS_RSP);

    /*��д��Ϣʵ��*/
    pstStatusRsp->enResult = ulResult;

    /* ������Ϣ���ͺ���    */
    NAS_ERABM_SND_MSG(pstStatusRsp);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_HasDrbWithoutRelatingEpsBear
 Description     : �ж��Ƿ����DRB�ѽ�������������EPS������δ��������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-12-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ERABM_HasDrbWithoutRelatingEpsBear( VOS_VOID )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;

    /* �������г��أ��ж��Ƿ����DRB�ѽ�������EPS����δ�������� */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if ((NAS_ERABM_ILL_RB_ID != NAS_ERABM_GetEpsbRbIdInfo(ulEpsbId))
            && (NAS_ERABM_EPSB_INACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId)))
        {
            return NAS_ERABM_SUCCESS;
        }
    }

    return NAS_ERABM_FAILURE;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_IsAllActtiveBearerWithoutDrb
 Description     : �ж��Ƿ����еļ�����ع�����DRB��û�н�������
                   ���û�г��ش��ڼ���̬��Ҳ����ʧ�ܡ�
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2009-12-23  Draft Enact
    2.sunbing 49683       2010-08-26  Modify
*****************************************************************************/
VOS_UINT32  NAS_ERABM_IsAllActtiveBearerWithoutDrb( VOS_VOID )
{
    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;
    VOS_UINT32                          ulActEpsbNum = 0;

    /* �������г��أ��ж��Ƿ���ڳ����Ѽ����û�ж�ӦDRB����� */
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        /* �����Ѽ���ĳ����� */
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            /*EPS�����Ѽ���*/
            ulActEpsbNum ++;

            /*EPS�����ж�Ӧ��DRB���򷵻�ʧ��*/
            if(NAS_ERABM_ILL_RB_ID != NAS_ERABM_GetEpsbRbIdInfo(ulEpsbId))
            {
                return NAS_ERABM_FAILURE;
            }
        }
    }

    /*���еĳ��ض�û�ж�Ӧ��DRB*/
    if(ulActEpsbNum > 0)
    {
        return NAS_ERABM_SUCCESS;
    }
    /*�����ڼ���ĳ���*/
    else
    {
        return NAS_ERABM_FAILURE;
    }

}


/*****************************************************************************
 Function Name   : NAS_ERABM_RrcRabIndSetupSuccProc
 Description     : RRC_RABM_RAB_IND��Ϣ�������(setup succ����setup suc��release���)
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-01-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RrcRabIndSetupSuccProc( VOS_VOID )
{
    /*SERVICE���̽���*/
    NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);
    if(NAS_ERABM_TIMER_STATE_RUNNING == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
    {
        /* �ؽ��ɹ�,ȥע��RF��Դ֪ͨ */
        NAS_ERABM_SndRrmDeRegisterInd(RRM_PS_TASK_TYPE_LTE_PS_BACKGROUND_CALL);
        /* ֹͣ��ʱ��NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER */
        NAS_ERABM_TimerStop(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER);
    }
    NAS_ERABM_TimerStop(NAS_ERABM_WAIT_RB_REEST_TIMER);

    NAS_ERABM_SndRabmEmmDrbSetupInd();

    /* ֪ͨCDS�������ι��� */
    NAS_ERABM_SndErabmCdsSndBuffDataInd(CDS_ERABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);

    /* �����������������־*/
    NAS_ERABM_SetUpDataPending(EMM_ERABM_NO_UP_DATA_PENDING);

    /* ����ģʽB�£�Drb�����ɹ���ֹͣ���ػ��涨ʱ�� */
    if (NAS_ERABM_MODE_TYPE_LB == NAS_ERABM_GetMode())
    {
        NAS_ERABM_TimerStop(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
    }

    /* ���ֻ��DRB�����ɹ��ĳ������ж��Ƿ����DRB�ѽ�������������EPS������δ����
       ���������������򲻷�ESM_ERABM_BEARER_STATUS_REQ��Ϣ�������DRB����
       ��RELEASE��ϵĳ���(service��attach���̵�DRB�����ɹ���������release��ϣ�
       ��Ϊ���е�DRB���Ὠ���ɹ���ֻ��ר�г��ؼ����DRB�����ɹ�������release��ϣ��Լ�
       �л�ʱDRB�����ɹ�������release���)��Ҳ�ж��Ƿ����DRB�ѽ�������������EPS����
       ��δ������������������򲻷�ESM_ERABM_BEARER_STATUS_REQ��Ϣ���ȴ�DRB�ѽ�����
       ��EPS����δ�����ĳ��ؽ����ɹ���ERABM�յ�ESM��ESM_ERABM_ACT_IND��Ϣ���ٷ���
       ESM_ERABM_BEARER_STATUS_REQ��Ϣ��֪ͨESM�ͷ�DRB���ͷŵĹ������� */
    if (NAS_ERABM_SUCCESS == NAS_ERABM_HasDrbWithoutRelatingEpsBear())
    {
        /*ֹͣ������������ʱ��*/
        NAS_ERABM_TimerStop(NAS_ERABM_WAIT_EPSB_ACT_TIMER);
        /* lihong00150010 emergency tau&service begin */
        NAS_ERABM_TimerStart(   NAS_ERABM_WAIT_EPSB_ACTT_LENGTH,
                                NAS_ERABM_WAIT_EPSB_ACT_TIMER,
                                NAS_ERABM_WAIT_EPSB_ACT_TIMER);
        /* lihong00150010 emergency tau&service end */
        /*���õȴ�EPS���ؼ����ʶ*/
        NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_WAIT_EPSB_ACT_MSG);
    }
    else
    {
        /* ��ESM������״̬��Ϣ,��������ʱ����Ϣ��SessionId��Ϊ0������Ҫƥ��  */
        NAS_ERABM_InformEsmBearerStatus(0);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RrcRabIndSetupFailProc
 Description     : RRC_RABM_RAB_IND��Ϣ�������(setup fail����setup fail��release���)
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-01-11  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RrcRabIndSetupFailProc
(
    PS_BOOL_ENUM_UINT8                  enIsRecRelease
)
{
    /*�ж��Ƿ���SERVICE����״̬������ǣ�������Ϣ��EMMֹͣ*/
    if (NAS_ERABM_SERVICE_STATE_INIT == NAS_ERABM_GetEmmSrState())
    {
        if(NAS_ERABM_TIMER_STATE_STOPED == NAS_ERABM_IsTimerRunning(NAS_ERABM_RF_RECOVERY_RB_REEST_TIMER))
        {
            /* NAS_ERABM_RF_RECOVERY_RB_REEST_TIMERֹͣʱ��SERVICE���̽��������򽫼�������no rf�ָ��ؽ� */
            NAS_ERABM_SetEmmSrState(NAS_ERABM_SERVICE_STATE_TERMIN);

            NAS_ERABM_TimerStop(NAS_ERABM_WAIT_RB_REEST_TIMER);
        }
    }

    /* service��attach���̵�DRB����ʧ�ܲ�������release��ϣ���Ϊ���е�DRB����
       ����ʧ�ܣ�ֻ��ר�г��ؼ����DRB����ʧ�ܿ�����release��ϣ����ֳ�������
       ����NAS_ERABM_InformEsmBearerStatus */
    if (PS_TRUE == enIsRecRelease)
    {
        /* ��ESM������״̬��Ϣ,��������ʱ����Ϣ��SessionId��Ϊ0������Ҫƥ��  */
        NAS_ERABM_InformEsmBearerStatus(0);
    }

    /* SERVICE��ATTACH�����е�����DRB����ʧ�ܣ�������NAS_ERABM_InformEsmBearerStatus
       ��Ϣ��ֻ��ר�г��ؼ����DRB����ʧ����Ҫ����NAS_ERABM_InformEsmBearerStatus */
    if(NAS_ERABM_SUCCESS != NAS_ERABM_IsAllActtiveBearerWithoutDrb())
    {
        /* ��ESM������״̬��Ϣ,��������ʱ����Ϣ��SessionId��Ϊ0������Ҫƥ��  */
        NAS_ERABM_InformEsmBearerStatus(0);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RrcRabIndResultProc
 Description     : RRC_RABM_RAB_IND��Ϣ�������
 Input           : enIsRecSetupSucc
                   enIsRecSetupFail
                   enIsRecRelease
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-25  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RrcRabIndResultProc
(
    PS_BOOL_ENUM_UINT8                  enIsRecSetupSucc,
    PS_BOOL_ENUM_UINT8                  enIsRecSetupFail,
    PS_BOOL_ENUM_UINT8                  enIsRecRelease
)
{
    if (PS_TRUE == enIsRecSetupSucc)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RrcRabIndResultProc:setup succ proc");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RrcRabIndResultProc_ENUM, LNAS_FUNCTION_LABEL1);
        NAS_ERABM_RrcRabIndSetupSuccProc();
        return ;
    }

    if (PS_TRUE == enIsRecSetupFail)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RrcRabIndResultProc:setup fail proc");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RrcRabIndResultProc_ENUM, LNAS_FUNCTION_LABEL2);
        NAS_ERABM_RrcRabIndSetupFailProc(enIsRecRelease);
        return ;
    }

    if (PS_TRUE == enIsRecRelease)
    {
        NAS_ERABM_LOG1("NAS_ERABM_RrcRabIndResultProc:release proc",
                        NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_EPSB_ACT_TIMER));
        TLPS_PRINT2LAYER_INFO1(NAS_ERABM_RrcRabIndResultProc_ENUM, LNAS_FUNCTION_LABEL3, NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_EPSB_ACT_TIMER));

        if (NAS_ERABM_TIMER_STATE_RUNNING != NAS_ERABM_IsTimerRunning(NAS_ERABM_WAIT_EPSB_ACT_TIMER))
        {
            /* ��ESM������״̬��Ϣ,��������ʱ����Ϣ��SessionId��Ϊ0������Ҫƥ��  */
            NAS_ERABM_InformEsmBearerStatus(0);
        }

        return ;
    }
}
/* lihong00150010 erabm optimize end */
/*lint +e961*/
/*lint +e960*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


