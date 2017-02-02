


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasETcPdcpMsgProc.h"
#include  "NasETcNwMsgEncode.h"
#include  "NasETcEmmMsgProc.h"
#include  "NasETcERabmMsgProc.h"
#include  "NasETcOmMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasETcMain.h"
#include  "CdsEtcInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASTCPDCPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASTCPDCPMSGPROC_C
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
 Function Name   : NAS_ETC_PdcpUlMsgDistr
 Description     : PDCP UL����Ϣ������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ETC_PdcpUlMsgDistr
(
    VOS_VOID                           *pRcvMsg
)
{
    PS_MSG_HEADER_STRU         *pPdcpUlMsg  = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ETC_INFO_LOG("NAS_ETC_PdcpUlMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_PdcpUlMsgDistr_ENUM, LNAS_ENTRY);

    /* ��ETC�յ�EMM��Ϣ�����Ѿ������жϣ������ǰL�ǹ���״̬����������²����յ���ȥ
    ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF����ļ�����Ϣ��Lģ���𣬻���״̬����յ��ػ���Ϣʱ��
    ���PDCP����ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF������֪ͨPDCPȥ�����״̬*/


    pPdcpUlMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pPdcpUlMsg->ulMsgName)
    {
        /*����յ�����ID_TC_PDCP_ACTIVATE_TEST_MODE_CNF��Ϣ*/
        case ID_LTC_LPDCP_ACTIVATE_TEST_MODE_CNF:

            NAS_ETC_RcvTcPdcpUlActTestModeCnf( (LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_TC_PDCP_START_TEST_LOOP_CNF��Ϣ*/
        case ID_LTC_LPDCP_START_TEST_LOOP_CNF:

            NAS_ETC_RcvTcPdcpUlStartTestLoopCnf( (LTC_LPDCP_START_TEST_LOOP_CNF_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_TC_PDCP_STOP_TEST_LOOP_CNF��Ϣ*/
        case ID_LTC_LPDCP_STOP_TEST_LOOP_CNF:

            NAS_ETC_RcvTcPdcpUlStopTestLoopCnf( (LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU *) pRcvMsg );
            break;

        /*����յ�����ID_TC_PDCP_DEACTIVATE_TEST_MODE_CNF��Ϣ*/
        case ID_LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF:

            NAS_ETC_RcvTcPdcpUlDeactTestModeCnf( (LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU *) pRcvMsg );
            break;

        default:
            NAS_ETC_WARN_LOG("NAS_ETC_PdcpUlMsgDistr:WARNING:PDCP->TC Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ETC_PdcpUlMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlActTestModeCnf
 Description     : PDCP ULģ�鷢����ACTIVATE TEST MODE CNF��Ϣ������
 Input           : pRcvMsg-----------�յ���ACTIVATE TEST MODE CNF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlActTestModeCnf
(
    const LTC_LPDCP_ACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* �����Ϊʧ�ܣ���ֱ�ӷ��� */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlActTestModeCnf:WARNING:Act test mode failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlActTestModeCnf_ENUM, LNAS_TC_StartTestLoopFailed);
        return;
    }

    /* �����γ�ACTIVATE TEST MODE COMPLETE��Ϣ */
    NAS_ETC_EncodeActTestModeComplete(aucMsgBuff, &ulMsgLength);

    /* ��ACTIVATE TEST MODE COMPLETE��Ϣ���͸�EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* ��ģʽ����Ϊ����ģʽ */
    NAS_ETC_SetModeType(NAS_ETC_MODE_TYPE_LB);

    /* ֪ͨRABM���뻷��ģʽ */
    NAS_ETC_SndTcRabmActTestModeMsg();

    /* ֪ͨCDS���뻷��ģʽ */
    NAS_ETC_SndTcCdsActTestModeMsg();

    /* �տ���Ϣ�ϱ� */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_ACT_TEST_MODE_CMP);

}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlStartTestLoopCnf
 Description     : PDCP ULģ�鷢����START TEST LOOP CNF��Ϣ������
 Input           : pRcvMsg-----------�յ���START TEST LOOP CNF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlStartTestLoopCnf
(
    const LTC_LPDCP_START_TEST_LOOP_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* �����Ϊʧ�ܣ���ֱ�ӷ��� */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlStartTestLoopCnf:WARNING:Start test loop failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlStartTestLoopCnf_ENUM, LNAS_TC_StartTestLoopFailed);
        return;
    }

    /* �����γ�CLOSE UE TEST LOOP COMPLETE��Ϣ */
    NAS_ETC_EncodeCloseUeTestLoopComplete(aucMsgBuff, &ulMsgLength);

    /* ��CLOSE UE TEST LOOP COMPLETE��Ϣ���͸�EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* �տ���Ϣ�ϱ� */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_CLOSE_UE_TEST_LOOP_CMP);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlStopTestLoopCnf
 Description     : PDCP ULģ�鷢����STOP TEST LOOP CNF��Ϣ������
 Input           : pRcvMsg-----------�յ���STOP TEST LOOP CNF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlStopTestLoopCnf
(
    const LTC_LPDCP_STOP_TEST_LOOP_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* �����Ϊʧ�ܣ���ֱ�ӷ��� */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlStopTestLoopCnf:WARNING:Stop test loop failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlStopTestLoopCnf_ENUM, LNAS_TC_StopTestLoopFailed);
        return;
    }

    /* �����γ�OPEN UE TEST LOOP COMPLETE��Ϣ */
    NAS_ETC_EncodeOpenUeTestLoopComplete(aucMsgBuff, &ulMsgLength);

    /* ��OPEN UE TEST LOOP COMPLETE��Ϣ���͸�EMM */
    NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

    /* �տ���Ϣ�ϱ� */
    NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                TC_OPEN_UE_TEST_LOOP_CMP);
}

/*****************************************************************************
 Function Name   : NAS_ETC_RcvTcPdcpUlDeactTestModeCnf
 Description     : PDCP ULģ�鷢����DEACTIVATE TEST MODE CNF��Ϣ������
 Input           : pRcvMsg-----------�յ���DEACTIVATE TEST MODE CNF��Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_RcvTcPdcpUlDeactTestModeCnf
(
    const LTC_LPDCP_DEACTIVATE_TEST_MODE_CNF_STRU *pRcvMsg
)
{
    VOS_UINT32                          ulMsgLength;
    VOS_UINT8                           aucMsgBuff[NAS_ETC_UL_AIR_MSG_BUFFER_LEN];

    /* �����Ϊʧ�ܣ���ֱ�ӷ��� */
    if (NAS_ETC_RESULT_TYPE_SUCCESS != pRcvMsg->ulResult)
    {
        NAS_ETC_WARN_LOG("NAS_ETC_RcvTcPdcpUlDeactTestModeCnf:WARNING:Deact test mode failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ETC_RcvTcPdcpUlDeactTestModeCnf_ENUM, LNAS_TC_StopTestLoopFailed);
        return;
    }

    /* ��ģʽ����Ϊ����ģʽ */
    NAS_ETC_SetModeType(NAS_ETC_MODE_TYPE_NORMAL);

    /* ֪ͨCDS�˳�����ģʽ */
    NAS_ETC_SndTcCdsDeactTestModeMsg();

    /* Lģ���������£�����Ҫ��EMM����COMPLETR��Ϣ������Ҫ�ϱ��տ���Ϣ */
    if (NAS_ETC_L_MODE_STATUS_NORMAL == NAS_ETC_GetLModeStatus())
    {
        /* Lģ����״̬��ERABM�յ�ETC���͵�ȥ�����ģʽ��Ϣ��ֱ�Ӷ������յ��ػ���Ϣ��
        ESM���ERABM����ID_ESM_ERABM_REL_IND��Ϣ��֪ͨERABM�����Դ�������ڹ���״̬�²���Ҫ��
        ��ERABM����ȥ�����״̬��Ϣ */
        /* ֪ͨRABM��������ģʽ */
        NAS_ETC_SndTcRabmDeactTestModeMsg();

        /* �����γ�DEACTIVATE TEST MODE COMPLETE��Ϣ */
        NAS_ETC_EncodeDeactTestModeComplete(aucMsgBuff, &ulMsgLength);

        /* ��DEACTIVATE TEST MODE COMPLETE��Ϣ���͸�EMM */
        NAS_ETC_SndTcEmmDataReqMsg(aucMsgBuff, ulMsgLength);

        /* �տ���Ϣ�ϱ� */
        NAS_ETC_SndAirMsgReportInd(  aucMsgBuff,ulMsgLength,
                                    NAS_ETC_AIR_MSG_DIR_ENUM_UP,
                                    TC_DEACT_TEST_MODE_CMP);
    }

}


/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpActTestModeMsg
 Description     : TCģ����PDCPģ�鷢��ACTIVATE TEST MODE��Ϣ
 Input           : pstTcNwMsgIE--------�����Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-14  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpActTestModeMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_ACTIVATE_TEST_MODE_STRU     *pstTcPdcpActTestMode = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcPdcpActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_ACTIVATE_TEST_MODE_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcPdcpActTestMode)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpActTestModeMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpActTestMode), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpActTestMode));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpActTestMode,ID_LTC_LPDCP_ACTIVATE_TEST_MODE);

    /* ��д����ģʽ */
    pstTcPdcpActTestMode->enLoopBackMode = pstTcNwMsgIE->enLoopBackMode;

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcPdcpActTestMode);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpActTestModeMsg:NORM:Send ID_LTC_LPDCP_ACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpActTestModeMsg_ENUM, LNAS_TC_SndMsg);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpDeactTestModeMsg
 Description     : TCģ����PDCPģ�鷢��DEACTIVATE TEST MODE��Ϣ
 Input           : pstTcNwMsgIE--------�����Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpDeactTestModeMsg( VOS_VOID )
{
    LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU     *pstTcPdcpDeActTestMode = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcPdcpDeActTestMode = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_DEACTIVATE_TEST_MODE_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcPdcpDeActTestMode)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpDeactTestModeMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpDeActTestMode), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpDeActTestMode));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpDeActTestMode,ID_LTC_LPDCP_DEACTIVATE_TEST_MODE);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcPdcpDeActTestMode);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpDeactTestModeMsg:NORM:Send ID_LTC_LPDCP_DEACTIVATE_TEST_MODE!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpDeactTestModeMsg_ENUM, LNAS_TC_SndMsg);
}
/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpStartTestLoopMsg
 Description     : TCģ����PDCPģ�鷢��START TEST LOOP��Ϣ
 Input           : pstTcNwMsgIE--------�����Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID


 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpStartTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_START_TEST_LOOP_STRU       *pstTcPdcpStartTestLoop = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcPdcpStartTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_START_TEST_LOOP_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcPdcpStartTestLoop)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpStartTestLoopMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpStartTestLoop), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStartTestLoop));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpStartTestLoop,ID_LTC_LPDCP_START_TEST_LOOP);

    /* ��д����ģʽ */
    pstTcPdcpStartTestLoop->enLoopBackMode = pstTcNwMsgIE->enLoopBackMode;

    /* ��д����ģʽ�������� */
    if (pstTcPdcpStartTestLoop->enLoopBackMode == LLOOP_BACK_MODE_A)
    {
        NAS_ETC_MEM_CPY( &pstTcPdcpStartTestLoop->u.stLBModeA,
                        &pstTcNwMsgIE->stLBModeA,
                        sizeof(LLOOP_BACK_MODE_A_STRU));

    }
    else
    {
        NAS_ETC_MEM_CPY( &pstTcPdcpStartTestLoop->u.stLBModeB,
                        &pstTcNwMsgIE->stLBModeB,
                        sizeof(LLOOP_BACK_MODE_B_STRU));
    }

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcPdcpStartTestLoop);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpStartTestLoopMsg:NORM:Send ID_LTC_LPDCP_START_TEST_LOOP!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpStartTestLoopMsg_ENUM, LNAS_TC_SndMsg);
}

/*****************************************************************************
 Function Name   : NAS_ETC_SndTcPdcpStopTestLoopMsg
 Description     : TCģ����PDCPģ�鷢��STOP TEST LOOP��Ϣ
 Input           : pstTcNwMsgIE--------�����Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-10-15  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ETC_SndTcPdcpStopTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    LTC_LPDCP_STOP_TEST_LOOP_STRU        *pstTcPdcpStopTestLoop = VOS_NULL_PTR;

    (VOS_VOID)pstTcNwMsgIE;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcPdcpStopTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(LTC_LPDCP_STOP_TEST_LOOP_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcPdcpStopTestLoop)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcPdcpStopTestLoopMsg:ERROR:TC->PDCP,Memory Alloc FAIL!");
        return ;
    }

    /* ��� */
    NAS_ETC_MEM_SET( NAS_ETC_GET_TC_PDCP_MSG_ENTITY(pstTcPdcpStopTestLoop), 0,
                            NAS_ETC_GET_MSG_LENGTH(pstTcPdcpStopTestLoop));

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_PDCP_MSG_HEAD(pstTcPdcpStopTestLoop,ID_LTC_LPDCP_STOP_TEST_LOOP);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcPdcpStopTestLoop);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcPdcpStopTestLoopMsg:NORM:Send ID_LTC_LPDCP_STOP_TEST_LOOP!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcPdcpStopTestLoopMsg_ENUM, LNAS_TC_SndMsg);
}
VOS_VOID  NAS_ETC_SndTcCdsActTestModeMsg(VOS_VOID)
{
    CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU        *pstTcCdsActTestLoop = VOS_NULL_PTR;


    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcCdsActTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(CDS_ETC_ACT_TEST_MODE_NOTIFY_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcCdsActTestLoop)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsActTestModeMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstTcCdsActTestLoop,ID_ETC_CDS_ACT_TEST_MODE_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcCdsActTestLoop);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsActTestModeMsg:NORM:Send ID_ETC_CDS_ACT_TEST_MODE_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsActTestModeMsg_ENUM, LNAS_TC_SndMsg);

}


VOS_VOID  NAS_ETC_SndTcCdsDeactTestModeMsg(VOS_VOID)
{
    ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU        *pstTcCdsDeactTestLoop = VOS_NULL_PTR;


    /* ����ռ䲢��������Ƿ�ɹ� */
    pstTcCdsDeactTestLoop = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_DEACT_TEST_MODE_NOTIFY_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstTcCdsDeactTestLoop)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsDeactTestModeMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstTcCdsDeactTestLoop,ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstTcCdsDeactTestLoop);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsDeactTestModeMsg:NORM:Send ID_ETC_CDS_DEACT_TEST_MODE_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsDeactTestModeMsg_ENUM, LNAS_TC_SndMsg);

}


VOS_VOID  NAS_ETC_SndTcCdsStartTestLoopMsg
(
    const NAS_ETC_NW_MSG_STRU           *pstTcNwMsgIE
)
{
    ETC_CDS_START_TEST_LOOP_NOTIFY_STRU *pstStartNfyMsg;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStartNfyMsg = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_START_TEST_LOOP_NOTIFY_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstStartNfyMsg)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsStartTestLoopMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstStartNfyMsg,ID_ETC_CDS_START_TEST_LOOP_NOTIFY);

    /* ��д����ģʽ */
    if (LLOOP_BACK_MODE_B == pstTcNwMsgIE->enLoopBackMode)
    {
        pstStartNfyMsg->ulLBMode = CDS_ETC_LB_MODE_B;
        pstStartNfyMsg->ulLBModeBTmrLen = pstTcNwMsgIE->stLBModeB.ulDelayTime;
    }
    else
    {
        pstStartNfyMsg->ulLBMode = LLOOP_BACK_MODE_A;
        pstStartNfyMsg->ulLBModeBTmrLen = 0;
    }

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstStartNfyMsg);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsStartTestLoopMsg:NORM:Send ID_ETC_CDS_START_TEST_LOOP_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsStartTestLoopMsg_ENUM, LNAS_TC_SndMsg);

    return;
}
VOS_VOID  NAS_ETC_SndTcCdsStopTestLoopMsg(VOS_VOID)
{
    ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU *pstStopNfyMsg;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStopNfyMsg = (VOS_VOID*)NAS_ETC_ALLOC_MSG(sizeof(ETC_CDS_STOP_TEST_LOOP_NOTIFY_STRU));

    /* ����Ƿ����ɹ� */
    if (VOS_NULL_PTR == pstStopNfyMsg)
    {
        /* ��ӡ�쳣��Ϣ */
        NAS_ETC_ERR_LOG("NAS_ETC_SndTcCdsStopTestLoopMsg:ERROR:TC->CDS,Memory Alloc FAIL!");
        return ;
    }

    /* ��д��Ϣͷ */
    NAS_ETC_WRITE_CDS_MSG_HEAD(pstStopNfyMsg,ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ETC_SND_MSG(pstStopNfyMsg);

    /* ��ӡ������Ϣ */
    NAS_ETC_NORM_LOG("NAS_ETC_SndTcCdsStopTestLoopMsg:NORM:Send ID_ETC_CDS_STOP_TEST_LOOP_NOTIFY!");
    TLPS_PRINT2LAYER_INFO(NAS_ETC_SndTcCdsStopTestLoopMsg_ENUM, LNAS_TC_SndMsg);

    return;
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasTcPdcpMsgProc.c */

