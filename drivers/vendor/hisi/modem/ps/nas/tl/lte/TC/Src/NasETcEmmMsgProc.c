


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasETcEmmMsgProc.h"
#include    "NasETcPdcpMsgProc.h"
#include    "NasETcNwMsgDecode.h"
#include    "NasETcMain.h"

#include    "NasETcMtcMsgProc.h"

#if ( FEATURE_LPP == FEATURE_ON )
#include    "EtcLppInterface.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCEMMMSGPROC_C
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
VOS_VOID NAS_ETC_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ETC_INFO_LOG("NAS_ETC_EmmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_EmmMsgDistr_ENUM, LNAS_ENTRY);

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pEmmMsg->ulMsgName)
    {
        /*����յ�����ID_EMM_ETC_DATA_IND��Ϣ*/
        case ID_EMM_ETC_DATA_IND:
            if (NAS_ETC_L_MODE_STATUS_NORMAL != NAS_ETC_GetLModeStatus())
            {
                NAS_ETC_WARN_LOG("NAS_ETC_EmmMsgDistr:Tc is already suspended!");
                TLPS_PRINT2LAYER_WARNING(NAS_ETC_EmmMsgDistr_ENUM, LNAS_TC_Tcsuspended);
                return ;
            }

            /*����TC_RcvTcEmmDataInd����*/
            NAS_ETC_RcvTcEmmDataInd( (EMM_ETC_DATA_IND_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_EMM_ETC_REL_IND��Ϣ*/
        case ID_EMM_ETC_REL_IND:
            if (NAS_ETC_MODE_TYPE_LB == NAS_ETC_GetModeType())
            {
                /* ֪ͨPDCP�˳�����ģʽ */
                NAS_ETC_SndTcPdcpDeactTestModeMsg();

                /* �յ�PDCP��ȥ����ظ�֮�󣬻��Զ���CDS����ȥ�������󣬲���Ҫ�ڴ˴����� */
            }
            break;

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_EmmMsgDistr:WARNING:EMM->TC Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_EmmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

#if ( FEATURE_LPP == FEATURE_ON )
VOS_VOID  NAS_ETC_SndTcResetUePositionInfoMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    ETC_LPP_RESET_POSTION_INFO_STRU       *pstTcLppRestPostion = VOS_NULL_PTR;
    TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcResetUePositionInfoMsg_ENUM, LNAS_LPP_Func_Enter);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcLppRestPostion = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_LPP_RESET_POSTION_INFO_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcLppRestPostion)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcResetUePositionInfoMsg:ERROR:TC->LPP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcResetUePositionInfoMsg_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_LPP_MSG_HEAD(pstTcLppRestPostion,ID_ETC_LPP_RESET_POSTION_INFO_IND);

    /*��д��Ϣ����*/
    pstTcLppRestPostion->enRestType = pstTcNwMsgIE->ucUePositionTech;

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcLppRestPostion);
}
#endif

/*****************************************************************************
 Function Name   : NAS_ETC_NwMsgProcess
 Description     : ����տ���Ϣ
 Input           : pstTcNwMsgIE-------�����Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_NwMsgProcess
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    switch(pstTcNwMsgIE->enTcCnMsgType)
    {
        case NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_ACT_TEST_MODE!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL1);
            NAS_ETC_SndTcPdcpActTestModeMsg(pstTcNwMsgIE);

            NAS_ETC_SndTcMtcStatusInfoMsg(MTC_NAS_TC_START);
            break;

        case NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_DEACT_TEST_MODE!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL2);
            NAS_ETC_SndTcPdcpDeactTestModeMsg();

            NAS_ETC_SndTcMtcStatusInfoMsg(MTC_NAS_TC_STOP);
            break;

        case NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_CLOSE_UE_TEST_LOOP!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL3);
            NAS_ETC_SndTcPdcpStartTestLoopMsg(pstTcNwMsgIE);
            NAS_ETC_SndTcCdsStartTestLoopMsg(pstTcNwMsgIE);
            break;

        case NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_OPEN_UE_TEST_LOOP!");
            TLPS_PRINT2LAYER_INFO(NAS_ETC_NwMsgProcess_ENUM, LNAS_FUNCTION_LABEL4);
            NAS_ETC_SndTcPdcpStopTestLoopMsg(pstTcNwMsgIE);
            NAS_ETC_SndTcCdsStopTestLoopMsg();
            break;

        #if ( FEATURE_LPP == FEATURE_ON )
        case NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO:
            NAS_ETC_NORM_LOG("NAS_ETC_NwMsgProcess:Receive Msg Type is NAS_ETC_CNMSG_TYPE_RESET_UE_POSITION_INFO!");
            NAS_ETC_SndTcResetUePositionInfoMsg(pstTcNwMsgIE);
            break;
        #endif

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_NwMsgProcess:WARNNING: Illegal Msg Type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_NwMsgProcess_ENUM, LNAS_MSG_INVALID);
            break;
    }
}



VOS_VOID NAS_ETC_RcvTcEmmDataInd( EMM_ETC_DATA_IND_STRU *pRcvMsg )
{
    NAS_ETC_CAUSE_ENUM_UINT8             enTcCause           = NAS_ETC_CAUSE_SUCCESS;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_ETC_NULL;
    NAS_ETC_NW_MSG_STRU                  stTcNwMsgIE;
    VOS_UINT8                          *pucTmpTcMsg         = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ETC_INFO_LOG("NAS_ETC_RcvTcEmmDataInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_RcvTcEmmDataInd_ENUM, LNAS_ENTRY);

    /*ȡ������Ϣ��������SM��Ϣ�ĳ���*/
    ulRcvNwMsgLen = pRcvMsg->stTcMsg.ulTcMsgSize;

    /*ȡ��SM��Ϣ�׵�ַ*/
    pucTmpTcMsg = pRcvMsg->stTcMsg.aucTcMsg;

    /*���NAS_ESM_NW_MSG_STRU*/
    NAS_ETC_MEM_SET((VOS_VOID*)&stTcNwMsgIE, 0, sizeof(NAS_ETC_NW_MSG_STRU));

    /*���ÿտ���Ϣ��������, �������ʧ��ֱ�ӷ���*/
    enTcCause = NAS_ETC_DecodeNwMsg( pucTmpTcMsg,
                                   &ulRcvNwMsgLen,
                                   &stTcNwMsgIE );

    /*����������󣬴�ӡ�������*/
    if (NAS_ETC_CAUSE_SUCCESS != enTcCause)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcEmmDataInd:WARNING: Decode Nw Msg Error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcEmmDataInd_ENUM, LNAS_TC_NwMsgError);
    }
    else
    {
        /*��������տ���Ϣ*/
        NAS_ETC_NwMsgProcess(&stTcNwMsgIE);
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcEmmDataReqMsg
 Description     : ��EMMģ�鷢��DATA REQ��Ϣ
 Input           : None
 Output          : pSendMsg-----------������Ϣ�洢��
                   pulLength----------������Ϣ����
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcEmmDataReqMsg
(
    const VOS_UINT8                    *pucSendMsg,
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulTmpLength         = NAS_ETC_NULL;
    EMM_ETC_DATA_REQ_STRU               *pTcEmmDataReq       = VOS_NULL_PTR;

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if (NAS_ETC_NULL == ulLength)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_SndTcEmmDataReqMsg: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_SndTcEmmDataReqMsg_ENUM, LNAS_EMM_MSG_LENGTH_ERROR);
        return ;
    }
    else if (ulLength > TC_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLength - TC_MIN_SND_MSG_LEN ;
        pTcEmmDataReq = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(EMM_ETC_DATA_REQ_STRU) + ulTmpLength);
    }
    else
    {
        pTcEmmDataReq = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(EMM_ETC_DATA_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pTcEmmDataReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcEmmDataReqMsg:ERROR:Alloc Msg fail!");
        return ;
    }

    /*���*/
    NAS_ETC_MEM_SET( NAS_ETC_GET_MSG_ENTITY(pTcEmmDataReq), 0, NAS_ETC_GET_MSG_LENGTH(pTcEmmDataReq));

    /*��д�տ���Ϣͷ����*/
    pTcEmmDataReq->stTcMsg.ulTcMsgSize = ulLength;

    /*���տ���Ϣ��ŵ�EMM_ESM_DATA_REQ_STRU�ṹ��*/
    /*lint -e669*/
    NAS_ETC_MEM_CPY(pTcEmmDataReq->stTcMsg.aucTcMsg, pucSendMsg, ulLength);
    /*lint +e669*/

    /*��д��Ϣͷ*/
    NAS_ETC_WRITE_EMM_MSG_HEAD(pTcEmmDataReq,ID_EMM_ETC_DATA_REQ);

    /*������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pTcEmmDataReq);

    NAS_ETC_NORM_LOG("NAS_ETC_SndTcEmmDataReqMsg:NORM:Send ID_EMM_ETC_DATA_REQ!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcEmmDataReqMsg_ENUM, LNAS_FUNCTION_LABEL1);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcEmmMsgProc.c */
