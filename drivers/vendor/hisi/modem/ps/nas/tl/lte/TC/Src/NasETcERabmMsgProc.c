


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcERabmMsgProc.h"
#include    "TcRabmInterface.h"
#include    "NasETcMain.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCRABMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCRABMMSGPROC_C
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
/*****************************************************************************
 Function Name   : NAS_ETC_RabmMsgDistr
 Description     : RABM��Ϣ������
 Input           : pRcvMsg-----------�յ�����Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ETC_RabmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pRabmMsg  = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ETC_INFO_LOG("NAS_ETC_RabmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_RabmMsgDistr_ENUM, LNAS_ENTRY);

    pRabmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pRabmMsg->ulMsgName)
    {
        /*����յ�����ID_ETC_ERABM_REL_IND��Ϣ*/
        case ID_ETC_ERABM_REL_IND:
            break;

        /*����յ�����ID_ETC_ERABM_SUSPEND_IND��Ϣ*/
        case ID_ETC_ERABM_SUSPEND_IND:
            NAS_ETC_RcvTcRabmSuspendInd( (ETC_ERABM_SUSPEND_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_ETC_ERABM_RESUME_IND��Ϣ*/
        case ID_ETC_ERABM_RESUME_IND:
            NAS_ETC_RcvTcRabmResumeInd( (ETC_ERABM_RESUME_IND_STRU *) pRcvMsg );
            break;

        default:
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmActTestModeMsg
 Description     : ��RABM����ACTIVATE TEST MODE��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcRabmActTestModeMsg( VOS_VOID )
{
    ETC_ERABM_ACTIVATE_TEST_MODE_STRU     *pstTcRabmActTestMode = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcRabmActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_ACTIVATE_TEST_MODE_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcRabmActTestMode)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmActTestModeMsg:ERROR:TC->RABM,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_MSG_ENTITY(pstTcRabmActTestMode), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcRabmActTestMode));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmActTestMode,ID_ETC_ERABM_ACTIVATE_TEST_MODE);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcRabmActTestMode);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcRabmActTestModeMsg:NORM:Send ID_ETC_ERABM_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcRabmActTestModeMsg_ENUM, LNAS_FUNCTION_LABEL1);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmDeactTestModeMsg
 Description     : ��RABM����DEACTIVATE TEST MODE��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcRabmDeactTestModeMsg( VOS_VOID )
{
    ETC_ERABM_DEACTIVATE_TEST_MODE_STRU     *pstTcRabmDeactTestMode = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcRabmDeactTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_DEACTIVATE_TEST_MODE_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcRabmDeactTestMode)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmDeactTestModeMsg:ERROR:TC->RABM,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_MSG_ENTITY(pstTcRabmDeactTestMode), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcRabmDeactTestMode));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmDeactTestMode,ID_ETC_ERABM_DEACTIVATE_TEST_MODE);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcRabmDeactTestMode);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcRabmDeactTestModeMsg:NORM:Send ID_ETC_ERABM_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcRabmDeactTestModeMsg_ENUM, LNAS_FUNCTION_LABEL1);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmSuspendRsp
 Description     : ETCģ��ظ�ID_ETC_ERABM_SUSPEND_RSP��Ϣ
 Input           : ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-04  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ETC_SndTcRabmSuspendRsp
(
    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    ETC_ERABM_SUSPEND_RSP_STRU           *pstTcRabmSuspendRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstTcRabmSuspendRsp = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_SUSPEND_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstTcRabmSuspendRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmSuspendRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ETC_MEM_SET( NAS_ETC_GET_MSG_ENTITY(pstTcRabmSuspendRsp), 0, NAS_ETC_GET_MSG_LENGTH(pstTcRabmSuspendRsp));

    /*��д��Ϣͷ*/
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmSuspendRsp, ID_ETC_ERABM_SUSPEND_RSP);

    /*��д��Ӧ���*/
    pstTcRabmSuspendRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcRabmSuspendRsp);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcRabmResumeRsp
 Description     : ESMģ��ظ�ID_ETC_ERABM_RESUME_RSP��Ϣ
 Input           : ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-05-04  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ETC_SndTcRabmResumeRsp
(
    ETC_ERABM_RSLT_TYPE_ENUM_UINT32       enRslt
)
{
    ETC_ERABM_RESUME_RSP_STRU            *pstTcRabmResumeRsp  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstTcRabmResumeRsp = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_ERABM_RESUME_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstTcRabmResumeRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcRabmResumeRsp:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ETC_MEM_SET( NAS_ETC_GET_MSG_ENTITY(pstTcRabmResumeRsp), 0, NAS_ETC_GET_MSG_LENGTH(pstTcRabmResumeRsp));

    /*��д��Ϣͷ*/
    NAS_ETC_WRITE_RABM_MSG_HEAD(pstTcRabmResumeRsp, ID_ETC_ERABM_RESUME_RSP);

    /*��д��Ӧ���*/
    pstTcRabmResumeRsp->enRslt= enRslt;

    /*������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcRabmResumeRsp);
}


/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcRabmSuspendInd
 Description     : ETCģ���յ�ID_ETC_ERABM_SUSPEND_IND������
 Input           : ETC_ERABM_SUSPEND_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcRabmSuspendInd(const ETC_ERABM_SUSPEND_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* ����״̬Ϊ����̬ */
    NAS_ETC_SetLModeStatus(NAS_ETC_L_MODE_STATUS_SUSPENDED);

    /* �ظ�ERABM����ɹ� */
    NAS_ETC_SndTcRabmSuspendRsp(ETC_ERABM_RSLT_TYPE_SUCC);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcRabmResumeInd
 Description     : SMģ���յ�ID_EMM_ERABM_RESUME_IND������
 Input           : ETC_ERABM_RESUME_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010            2011-05-04      Draft Enact
*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcRabmResumeInd(const ETC_ERABM_RESUME_IND_STRU *pRcvMsg )
{
    (VOS_VOID)pRcvMsg;

    /* ����״̬Ϊ����̬ */
    NAS_ETC_SetLModeStatus(NAS_ETC_L_MODE_STATUS_NORMAL);

    /* �ظ�ERABM��ҳɹ� */
    NAS_ETC_SndTcRabmResumeRsp(ETC_ERABM_RSLT_TYPE_SUCC);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasETcRabmMsgProc.c */
