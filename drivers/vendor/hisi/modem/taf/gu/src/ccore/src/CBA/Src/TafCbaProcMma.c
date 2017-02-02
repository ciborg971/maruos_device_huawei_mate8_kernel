

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "MnMsgTimerProc.h"
#include  "TafCbaMntn.h"

#include "TafMmaInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMA_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/




VOS_VOID TAF_CBA_ProcMmaMsg(
    struct MsgCB                       *pstMsg
)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    switch (pstMsgHeader->ulMsgName)
    {
        case MN_USIM_STATUS_IND:
            TAF_CBA_RcvMmaUsimStatusInd(pstMsg);
            break;

        default:
            break;
    }
}


VOS_VOID TAF_CBA_RcvMmaUsimStatusInd(
    struct MsgCB                       *pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU          *pstUsimStatus;

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;

    if (MNPH_USIM_STATUS_AVILABLE != pstUsimStatus->enUsimStatus)
    {
        /* ��ʼ��CBAģ���USIM��ص�ȫ�ֱ��� */
        TAF_CBA_InitSimInfo();
        /* ׷��NV�����õ�CBS������Ϣ�б� */
        TAF_CBA_AppendNvUserAcceptMsgIdList();
        return;
    }

    /* ��ȡCBS��ص�USIM���ļ�. �ļ���ȡ˳��: CBMI �ļ�; CBMIR �ļ� CBMID */
    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMI_ID, NAS_USIM_SVR_CBMI);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMIR_ID, NAS_USIM_SVR_CBMIR);

    TAF_CBA_ReadUsimFile(USIMM_USIM_EFCBMID_ID, NAS_USIM_SVR_DATA_DL_SMSCB);


    /* ׷��NV�����õ�CBS������Ϣ�б� */
    TAF_CBA_AppendNvUserAcceptMsgIdList();

    /* Ӧ��USIM�ļ���Ϣ�����غ�֪ͨ�ײ����ø��� */
    TAF_CBA_ApplyUsimInfo();

    /* ��NV��صĿ�ά�ɲ���Ϣ  */
    TAF_CBA_SndOmNvimInfo();

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
