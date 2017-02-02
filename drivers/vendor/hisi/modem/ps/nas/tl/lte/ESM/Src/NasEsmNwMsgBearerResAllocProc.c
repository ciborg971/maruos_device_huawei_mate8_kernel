



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGBEARERRESALLOCPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGBEARERRESALLOCPROC_C
/*lint +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgResAllocRej
 Description     : ������Դ����ܾ������տ���Ϣ
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : None

 History         :
    1.lihong00150010      2009-7-21  Draft Enact
    2.lihong00150010      2010-2-02  Modify
    3.liuwenyu00143951    2010-11-11 Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgResAllocRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr       = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpStateTblIndex =  NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgResAllocRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgResAllocRej_ENUM, LNAS_ENTRY);

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3480);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        if( NAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY == pRcvMsg->stEsmNwMsgIE.enEsmCau )
        {
            /* �����ͷŴ˳��صĹ���ȱʡ���غ���س��� */
            NAS_ESM_DeactBearerAndInformApp(pstStateAddr->ulLinkedEpsbId);

            /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
            NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(pstStateAddr->ulLinkedEpsbId, &ulTmpStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulTmpStateTblIndex);
            }
        }
        /*��APP����ID_APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                 NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}



/* end of NasEsmNwMsgBearerResAllocProc.c */
