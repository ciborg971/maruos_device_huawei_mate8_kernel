


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallProcMma.h"
#include "MnCallMnccProc.h"
#include "MnCall.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_MMA_C

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_CALL_RcvMmaPowerOffInd(
    TAF_MMA_POWER_OFF_IND_STRU         *pstMsg
)
{
    /*���������������ر�������*/
    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
        /* ������Ϣ֪ͨVC�ر�����ͨ�� */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
        /* ������Ϣ֪ͨAT����ͨ��״̬ */
        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
    }

    MN_CALL_Init(MN_CALL_POWER_STATE_OFF);
}
/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



