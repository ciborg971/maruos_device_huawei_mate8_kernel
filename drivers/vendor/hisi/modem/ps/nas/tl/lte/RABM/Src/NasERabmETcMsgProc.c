


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmETcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMTCMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMTCMSGPROC_C
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
VOS_VOID NAS_ERABM_TcMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg = VOS_NULL_PTR;

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_TcMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pEmmMsg->ulMsgName)
    {
        /*����յ�����ID_ETC_ERABM_ACTIVATE_TEST_MODE��Ϣ*/
        case ID_ETC_ERABM_ACTIVATE_TEST_MODE:
            NAS_ERABM_RcvRabmTcActTestMode();
            break;

        /*����յ�����ID_ETC_ERABM_DEACTIVATE_TEST_MODE��Ϣ*/
        case ID_ETC_ERABM_DEACTIVATE_TEST_MODE:
            NAS_ERABM_RcvRabmTcDeactTestMode();
            break;

        /*����յ�����ID_ETC_ERABM_REL_REQ��Ϣ*/
        case ID_ETC_ERABM_REL_REQ:
            NAS_ERABM_RcvRabmTcRelReq();
            break;

        /*����յ�����ID_ETC_ERABM_SUSPEND_RSP��Ϣ*/
        case ID_ETC_ERABM_SUSPEND_RSP:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TcMsgDistr:receive ID_ETC_ERABM_SUSPEND_RSP!");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_FUNCTION_LABEL1);
            break;

        /*����յ�����ID_ETC_ERABM_RESUME_RSP��Ϣ*/
        case ID_ETC_ERABM_RESUME_RSP:
            NAS_ERABM_NORM_LOG("NAS_ERABM_TcMsgDistr:receive ID_ETC_ERABM_RESUME_RSP!");
            TLPS_PRINT2LAYER_INFO(NAS_ERABM_TcMsgDistr_ENUM, LNAS_FUNCTION_LABEL2);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_TcMsgDistr:WARNING:TC->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_TcMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmTcActTestMode
 Description     : �յ�TCģ��ACTIVATE TEST MODE��Ϣ������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmTcActTestMode( VOS_VOID )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmTcActTestMode:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmTcActTestMode_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    /* ��ģʽ��Ϊ����ģʽ */
    NAS_ERABM_SetMode(NAS_ERABM_MODE_TYPE_LB);

    NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmTcActTestMode: Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcActTestMode_ENUM, LNAS_ERABM_UpdateIPFilterFailed);
    }
}
VOS_VOID  NAS_ERABM_RcvRabmTcDeactTestMode( VOS_VOID )
{
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        NAS_ERABM_WARN_LOG("NAS_ERABM_RcvRabmTcDeactTestMode:Rabm is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ERABM_RcvRabmTcDeactTestMode_ENUM, LNAS_ERABM_RabmSuspended);
        return ;
    }

    /* ����ģʽB��ֹͣ���ػ��涨ʱ�� */
    if (NAS_ERABM_MODE_TYPE_LB == NAS_ERABM_GetMode())
    {
        NAS_ERABM_TimerStop(NAS_ERABM_WAIT_TC_FREE_BUFFER_TIMER);
    }

    /* ��ģʽ��Ϊ����ģʽ */
    NAS_ERABM_SetMode(NAS_ERABM_MODE_TYPE_NORMAL);

    if (0 != NAS_ERABM_GetActiveEpsBearerNum())
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_VALID);
    }
    else
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);
    }

    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmTcActTestMode: Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcDeactTestMode_ENUM, LNAS_ERABM_UpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmTcRelReq
 Description     : �յ�TCģ��REL REQ��Ϣ������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-16  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmTcRelReq( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmTcRelReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ENTRY);

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
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmTcRelReq_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmTcSuspendInd
 Description     : ERABMģ����ETC����ID_ETC_ERABM_SUSPEND_IND��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmTcSuspendInd( VOS_VOID )
{
    ETC_ERABM_SUSPEND_IND_STRU           *pstRabmTcSuspendInd  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRabmTcSuspendInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ETC_ERABM_SUSPEND_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRabmTcSuspendInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmTcSuspendInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ERABM_MEM_SET( NAS_ERABM_GET_MSG_ENTITY(pstRabmTcSuspendInd), 0, NAS_ERABM_GET_MSG_LENGTH(pstRabmTcSuspendInd));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_TC_MSG_HEAD(pstRabmTcSuspendInd, ID_ETC_ERABM_SUSPEND_IND);

    /*������Ϣ���ͺ��� */
    NAS_ERABM_SND_MSG(pstRabmTcSuspendInd);
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmTcResumeInd
 Description     : ERABMģ����ETC����ID_ETC_ERABM_RESUME_IND��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-03  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmTcResumeInd( VOS_VOID )
{
    ETC_ERABM_RESUME_IND_STRU            *pstRabmTcResumeInd  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstRabmTcResumeInd = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ETC_ERABM_RESUME_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstRabmTcResumeInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmTcResumeInd:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ERABM_MEM_SET( NAS_ERABM_GET_MSG_ENTITY(pstRabmTcResumeInd), 0, NAS_ERABM_GET_MSG_LENGTH(pstRabmTcResumeInd));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_TC_MSG_HEAD(pstRabmTcResumeInd, ID_ETC_ERABM_RESUME_IND);

    /*������Ϣ���ͺ��� */
    NAS_ERABM_SND_MSG(pstRabmTcResumeInd);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

