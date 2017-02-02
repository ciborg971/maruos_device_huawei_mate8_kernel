

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaMntn.h"
#include "AtMtaInterface.h"
#include "TafSdcLib.h"
#include "TafMtaTimerMgmt.h"
#include "TafMtaMain.h"
#include "TafMtaCtx.h"
#include "TafMtaComm.h"
#include "mdrv.h"
#include "NasOmInterface.h"
#include "TafAgentInterface.h"
#include "mdrv.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasErrorLog.h"
#endif

#include "NasComm.h"

/* Added by lwx277467 for UE Mode, 2015-09-10 Begin */
#include "NasMtaInterface.h"
/* Added by lwx277467 for UE Mode, 2015-09-10 End */

/* Added by z00328328 for TX_POWER_CHR, 2015-10-26, begin */
#include "NasUtranCtrlInterface.h"
/* Added by z00328328 for TX_POWER_CHR, 2015-10-26, end */

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MNTN_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID TAF_MTA_RcvQryWrrAutotestReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_WRR_AUTOTEST_PARA_STRU         *pstRrcAtQryPara = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtQryPara    = (MTA_WRR_AUTOTEST_PARA_STRU *)pstQryReq->aucContent;
    ulResult           = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrQryAutotestReqMsg(pstRrcAtQryPara);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                        TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvQryWrrCellInfoReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryCellinfoReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAtCmdCellInfo;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    ulAtCmdCellInfo        = 0;
    pstQryCellinfoReq      = (AT_MTA_MSG_STRU *)pMsg;
    ulResult               = VOS_ERR;

    PS_MEM_CPY(&ulAtCmdCellInfo, pstQryCellinfoReq->aucContent, sizeof(VOS_UINT32));

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                        ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                        sizeof(stQryCnf),
                        (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryCellinfoReqMsg(ulAtCmdCellInfo);
    }

    /* �����ǰ��Utranģʽ����FDDģʽ,ulResultΪVOS_ERR��
       ���߸�����㷢����Ϣʧ��,ulResultҲΪVOS_ERR����AT�ظ���ѯʧ�� */
    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF, TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,
                                     (VOS_UINT8*)&pstQryCellinfoReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvQryWrrMeanrptReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                    *pstQryReq = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq           = (AT_MTA_MSG_STRU *)pMsg;
    ulResult            = VOS_ERR;
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrQryMeanrptReqMsg();
    }

    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF, TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvSetWrrFreqlockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_CTRL_STRU      *pstRrcAtSetPara = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtSetPara    = (MTA_AT_WRR_FREQLOCK_CTRL_STRU *)pstQryReq->aucContent;
    ulResult           = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrSetFreqlockReqMsg((MTA_WRR_FREQLOCK_CTRL_STRU *)pstRrcAtSetPara);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,
                        TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvSetWrrRrcVersionReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stSetCnf;
    VOS_UINT32                                              ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrSetVersionReqMsg(pstSetReq->aucContent[0]);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,
                       TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvSetWrrCellsrhReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stSetCnf;
    VOS_UINT32                                              ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrSetCellsrhReqMsg(pstSetReq->aucContent[0]);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,
                       TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvQryWrrFreqlockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    ulResult           = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrQryFreqlockReqMsg();
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,
                        TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvQryWrrRrcVersionReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstQryVersionReq = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU                     stQryCnf;
    VOS_UINT32                                              ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryVersionReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult         = VOS_ERR;

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                      ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryRrcVersionReqMsg();
    }

    /* �����ǰ��Utranģʽ����FDDģʽ,ulResultΪVOS_ERR��
       ���߸�����㷢����Ϣʧ��,ulResultҲΪVOS_ERR����AT�ظ���ѯʧ�� */
    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                         ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF, TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF,
                                     (VOS_UINT8*)&pstQryVersionReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvQryWrrCellsrhReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstQryVersionReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU                         stQryCnf;
    VOS_UINT32                                              ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryVersionReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult         = VOS_ERR;

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                      ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryCellsrhReqMsg();
    }

    /* �����ǰ��Utranģʽ����FDDģʽ,ulResultΪVOS_ERR��
       ���߸�����㷢����Ϣʧ��,ulResultҲΪVOS_ERR����AT�ظ���ѯʧ�� */
    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryVersionReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF, TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF,
                                     (VOS_UINT8*)&pstQryVersionReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvAtSetNCellMonitorReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pstSetReq = VOS_NULL_PTR;
    AT_MTA_NCELL_MONITOR_SET_REQ_STRU          *pstSetRptReq = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSetCnf;
    MTA_AT_RESULT_ENUM_UINT32                   enResult;

    pstSetReq    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetRptReq = (AT_MTA_NCELL_MONITOR_SET_REQ_STRU *)pstSetReq->aucContent;
    enResult     = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF))
    {
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ���ƽ̨֧��Gģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportGsm() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        enResult = TAF_MTA_SndGrrNCellMonitorSetReq(pstSetRptReq->ucSwitch);
    }

    if (MTA_AT_RESULT_NO_ERROR != enResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
                       TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


VOS_VOID TAF_MTA_RcvAtQryNCellMonitorReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                            *pstQryReq = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU           stQryCnf;
    MTA_AT_RESULT_ENUM_UINT32                   enResult;

    pstQryReq    = (AT_MTA_MSG_STRU *)pMsg;
    enResult     = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Gģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportGsm() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        enResult = TAF_MTA_SndGrrNCellMonitorQryReq();
    }

    if (MTA_AT_RESULT_NO_ERROR != enResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,
                       TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}



VOS_VOID TAF_MTA_RcvAtSetJamDetectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstJamDetectReq = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stQryCnf;
    VOS_UINT32                          ulResult;

    pstSetReq         = (AT_MTA_MSG_STRU *)pMsg;
    pstJamDetectReq   = (AT_MTA_SET_JAM_DETECT_REQ_STRU *)(pstSetReq->aucContent);
    ulResult          = VOS_ERR;
    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_JAM_DETECT_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* ���ƽ̨֧��Gģ�����������as�������at�ظ�ʧ�� */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndGrrSetJamDetectReq(pstJamDetectReq);
    }

    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_JAM_DETECT_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,
                       TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


VOS_VOID TAF_MTA_RcvAtPhyInitReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                                        *pstAtMtaReqMsg     = VOS_NULL_PTR;
    MTA_UPHY_START_UPHY_REQ_STRU                           *pstPhyStartReq     = VOS_NULL_PTR;
    MTA_AT_PHY_INIT_CNF_STRU                                stSndAtPhyInitCnf;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8                         enPhyInitTiStatus;

    pstAtMtaReqMsg = (AT_MTA_MSG_STRU*)pMsg;


    /* ��Ϣ�ռ����� */
    pstPhyStartReq = (MTA_UPHY_START_UPHY_REQ_STRU *)PS_ALLOC_MSG( UEPS_PID_MTA,
                                                      sizeof(MTA_UPHY_START_UPHY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstPhyStartReq)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq: alloc msg fail!");

        /* ��Ϣ�������� */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* ��ATģ�鷢��ʧ����Ϣ */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf );

        return;
    }


    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    enPhyInitTiStatus  = TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DSP_INIT_CNF);
    if (TAF_MTA_TIMER_STATUS_RUNING == enPhyInitTiStatus)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq: alloc msg fail!");

        /* ��Ϣ�������� */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* ��ATģ�鷢��ʧ����Ϣ */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf);

        PS_MEM_FREE(UEPS_PID_MTA, pstPhyStartReq);
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET( ((VOS_UINT8*)pstPhyStartReq + VOS_MSG_HEAD_LENGTH), 0,
                sizeof(MTA_UPHY_START_UPHY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ����Ϣ�� */
    pstPhyStartReq->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPhyStartReq->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstPhyStartReq->ulSenderPid           = UEPS_PID_MTA;
    pstPhyStartReq->ulReceiverPid         = DSP_PID_STARTUP;
    pstPhyStartReq->usMsgID               = ID_MTA_UPHY_START_UPHY_REQ;

    /* ������Ϣ��DSP_PID_STARTUPģ�� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstPhyStartReq))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtPhyInitReq()--PS_SEND_MSG():WARNING:SEND MSG FIAL");

        /* ��Ϣ�������� */
        PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
        stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_ERROR;

        /* ��ATģ�鷢��ʧ����Ϣ */
        TAF_MTA_SndAtMsg(&pstAtMtaReqMsg->stAppCtrl,
                      ID_MTA_AT_PHY_INIT_CNF,
                      sizeof(stSndAtPhyInitCnf),
                      (VOS_UINT8*)&stSndAtPhyInitCnf );

        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_DSP_INIT_CNF, TI_TAF_MTA_WAIT_DSP_INIT_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF,
                                     (VOS_UINT8*)&pstAtMtaReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}
VOS_VOID TAF_MTA_RcvAtSetFreqLockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq         = VOS_NULL_PTR;
    AT_MTA_SET_FREQ_LOCK_REQ_STRU      *pstSetFreqLockReq = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU       stSetFreqLockCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulLength;

    pstSetReq                 = (AT_MTA_MSG_STRU *)pMsg;
    pstSetFreqLockReq         = (AT_MTA_SET_FREQ_LOCK_REQ_STRU *)(pstSetReq->aucContent);
    stSetFreqLockCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_FREQ_LOCK_CNF,
                         sizeof(stSetFreqLockCnf),
                         (VOS_UINT8*)&stSetFreqLockCnf);
        return;
    }

    ulResult = TAF_MTA_SndRrcSetFreqLockReq(pstSetFreqLockReq);

    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_FREQ_LOCK_CNF,
                         sizeof(stSetFreqLockCnf),
                         (VOS_UINT8*)&stSetFreqLockCnf);
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,
                       TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF_TIMER_LEN);

    ulLength = (sizeof(AT_MTA_MSG_STRU) + sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU)) - 4;

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF,
                                    (VOS_UINT8*)pstSetReq,
                                     ulLength);

    return;
}


VOS_VOID TAF_MTA_RcvWrrAutotestQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_AUTOTEST_QRY_CNF_STRU      *pstRcvWrrAutotestCnf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stSndAtAutotestCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrAutotestCnf                 = (WRR_MTA_AUTOTEST_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtAutotestCnf.ulResult          = pstRcvWrrAutotestCnf->ulResult;
    stSndAtAutotestCnf.stWrrAutoTestRslt.ulRsltNum = pstRcvWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum;
    PS_MEM_CPY(stSndAtAutotestCnf.stWrrAutoTestRslt.aulRslt,
               pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt,
               sizeof(pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stSndAtAutotestCnf),
                     (VOS_UINT8*)&stSndAtAutotestCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrCellInfoQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_CELLINFO_QRY_CNF_STRU      *pstRcvWrrCellinfoCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stSndAtCellinfoQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellinfoCnf           = (WRR_MTA_CELLINFO_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellinfoQryCnf.ulResult = pstRcvWrrCellinfoCnf->ulResult;
    PS_MEM_CPY(&(stSndAtCellinfoQryCnf.stWrrCellInfo),
                &(pstRcvWrrCellinfoCnf->stWrrCellInfo),
                sizeof(pstRcvWrrCellinfoCnf->stWrrCellInfo));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stSndAtCellinfoQryCnf),
                     (VOS_UINT8*)&stSndAtCellinfoQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrMeanrptQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    WRR_MTA_MEANRPT_QRY_CNF_STRU       *pstRcvWrrMeanrptCnf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stSndAtMeanrptQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrMeanrptCnf                         = (WRR_MTA_MEANRPT_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtMeanrptQryCnf.ulResult               = pstRcvWrrMeanrptCnf->ulResult;
    stSndAtMeanrptQryCnf.stMeanRptRslt.ulRptNum = pstRcvWrrMeanrptCnf->stMeanRptRslt.ulRptNum;
    PS_MEM_CPY((stSndAtMeanrptQryCnf.stMeanRptRslt.astMeanRptInfo), pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo, sizeof(pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stSndAtMeanrptQryCnf),
                     (VOS_UINT8*)&stSndAtMeanrptQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrFreqlockSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_FREQLOCK_SET_CNF_STRU      *pstRcvWrrFreqlockCnf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stSndAtFreqlockCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrFreqlockCnf        = (WRR_MTA_FREQLOCK_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtFreqlockCnf.ulResult = pstRcvWrrFreqlockCnf->ulResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                     sizeof(stSndAtFreqlockCnf),
                     (VOS_UINT8*)&stSndAtFreqlockCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrVersionSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_RRC_VERSION_SET_CNF_STRU                       *pstRcvWrrVersionSetCnf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stSndAtVersionSetCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrVersionSetCnf        = (WRR_MTA_RRC_VERSION_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtVersionSetCnf.ulResult = pstRcvWrrVersionSetCnf->ulResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                     sizeof(stSndAtVersionSetCnf),
                     (VOS_UINT8*)&stSndAtVersionSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrCellsrhSetCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_CELLSRH_SET_CNF_STRU                           *pstRcvWrrCellsrhSetCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stSndAtCellsrhSetCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhSetCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellsrhSetCnf            = (WRR_MTA_CELLSRH_SET_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellsrhSetCnf.ulResult     = pstRcvWrrCellsrhSetCnf->ulResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                     sizeof(stSndAtCellsrhSetCnf),
                     (VOS_UINT8*)&stSndAtCellsrhSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrFreqlockQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_FREQLOCK_QRY_CNF_STRU      *pstRcvWrrFreqlockCnf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stSndAtFreqlockCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrFreqlockQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrFreqlockCnf              = (WRR_MTA_FREQLOCK_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtFreqlockCnf.ulResult       = pstRcvWrrFreqlockCnf->ulResult;
    stSndAtFreqlockCnf.stFreqLockInfo.ucFreqLockEnable = pstRcvWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable;
    stSndAtFreqlockCnf.stFreqLockInfo.usLockedFreq     = pstRcvWrrFreqlockCnf->stFreqLockInfo.usLockedFreq;
    PS_MEM_SET(stSndAtFreqlockCnf.stFreqLockInfo.aucReserved, 0, sizeof(stSndAtFreqlockCnf.stFreqLockInfo.aucReserved));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                     sizeof(stSndAtFreqlockCnf),
                     (VOS_UINT8*)&stSndAtFreqlockCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrVersionQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_RRC_VERSION_QRY_CNF_STRU   *pstRcvWrrVersionQryCnf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU stSndAtVersionQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrVersionQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrVersionQryCnf            = (WRR_MTA_RRC_VERSION_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtVersionQryCnf.ulResult     = pstRcvWrrVersionQryCnf->ulResult;
    stSndAtVersionQryCnf.ucRrcVersion = pstRcvWrrVersionQryCnf->ucRrcVersion;
    PS_MEM_SET((stSndAtVersionQryCnf.aucReserved), 0, sizeof(stSndAtVersionQryCnf.aucReserved));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                     sizeof(stSndAtVersionQryCnf),
                     (VOS_UINT8*)&stSndAtVersionQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvWrrCellsrhQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf              = VOS_NULL_PTR;
    WRR_MTA_CELLSRH_QRY_CNF_STRU       *pstRcvWrrCellsrhQryCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU     stSndAtCellsrhQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellsrhQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellsrhQryCnf                = (WRR_MTA_CELLSRH_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellsrhQryCnf.ulResult         = pstRcvWrrCellsrhQryCnf->ulResult;
    stSndAtCellsrhQryCnf.ucCellSearchType = pstRcvWrrCellsrhQryCnf->ucCellSearchType;
    PS_MEM_SET((stSndAtCellsrhQryCnf.aucReserve), 0, sizeof(stSndAtCellsrhQryCnf.aucReserve));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                     sizeof(stSndAtCellsrhQryCnf),
                     (VOS_UINT8*)&stSndAtCellsrhQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvRrcSetNCellMonitorCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf       = VOS_NULL_PTR;
    GRR_MTA_NCELL_MONITOR_SET_CNF_STRU                     *pstGrrMtaSetCnf = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU                     stMtaAtSetCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcSetNCellMonitorCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcSetNCellMonitorCnf: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtSetCnf, 0, sizeof(stMtaAtSetCnf));
    pstGrrMtaSetCnf        = (GRR_MTA_NCELL_MONITOR_SET_CNF_STRU *)pMsg;

    if (VOS_OK == pstGrrMtaSetCnf->ulResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvRrcQryNCellMonitorCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf       = VOS_NULL_PTR;
    GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU                     *pstGrrMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU                       stMtaAtQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcQryNCellMonitorCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcQryNCellMonitorCnf: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtQryCnf, 0, sizeof(stMtaAtQryCnf));
    pstGrrMtaQryCnf            = (GRR_MTA_NCELL_MONITOR_QRY_CNF_STRU *)pMsg;
    stMtaAtQryCnf.enResult     = pstGrrMtaQryCnf->ulResult;
    stMtaAtQryCnf.ucSwitch     = pstGrrMtaQryCnf->ucSwitch;
    stMtaAtQryCnf.ucNcellState = pstGrrMtaQryCnf->enNcellState;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                     sizeof(stMtaAtQryCnf),
                     (VOS_UINT8*)&stMtaAtQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);
    return;
}
VOS_VOID TAF_MTA_RcvPhyInitCnf(VOS_VOID *pMsg)
{
    MTA_AT_RESULT_ENUM_UINT32                               enResult;
    MTA_AT_PHY_INIT_CNF_STRU                                stSndAtPhyInitCnf;
    UPHY_MTA_START_UPHY_CNF_STRU                           *pstPhyStartCnf     = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf          = VOS_NULL_PTR;

    pstPhyStartCnf = (UPHY_MTA_START_UPHY_CNF_STRU*)pMsg;

    /* ���ýṹ�� */
    PS_MEM_SET(&stSndAtPhyInitCnf, 0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));

    /* �鿴timer״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DSP_INIT_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyInitCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ��ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_DSP_INIT_CNF);

    /* ��ȡ����buff */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* phy���ת�� */
    if (MTA_UPHY_INIT_STATUS_SUCCESS == pstPhyStartCnf->enInitStatus)
    {
        enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        enResult = MTA_AT_RESULT_ERROR;
    }

    /* ��д��Ϣ�ṹ */
    stSndAtPhyInitCnf.enResult = enResult;

    /* ��ATģ�鷢��ID_MTA_AT_PHY_INIT_CNF��Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_PHY_INIT_CNF,
                     sizeof(stSndAtPhyInitCnf),
                     (VOS_UINT8*)&stSndAtPhyInitCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}


VOS_VOID TAF_MTA_RcvRrcNCellMonitorInd(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NCELL_MONITOR_IND_STRU                     *pstGrrMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU                       stMtaAtInd;
    AT_APPCTRL_STRU                                     stAppCtrl;

    /* ��д�����ϱ�����Ϣ���� */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    pstGrrMtaQryCnf        = (GRR_MTA_NCELL_MONITOR_IND_STRU *)pMsg;
    stMtaAtInd.ucNcellState = pstGrrMtaQryCnf->enNcellState;

    /* ��д��Ϣͷ���ϱ�����Ϊ�㲥�¼� */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_NCELL_MONITOR_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}
VOS_VOID TAF_MTA_RcvRrcJamDetectCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    RRC_MTA_JAM_DETECT_CNF_STRU        *pstGrrMtaSetCnf = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stMtaAtSetCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcJamDetectCnf: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcJamDetectCnf: get command buffer failed!");
        return;
    }

    pstGrrMtaSetCnf = (RRC_MTA_JAM_DETECT_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtSetCnf, 0, sizeof(stMtaAtSetCnf));

    if (MTA_RRC_RESULT_NO_ERROR == pstGrrMtaSetCnf->enResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_JAM_DETECT_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);
    return;

}
VOS_VOID TAF_MTA_RcvRrcJamDetectInd(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_JAM_DETECT_IND_STRU        *pstJamDetectInd = VOS_NULL_PTR;
    MTA_AT_JAM_DETECT_IND_STRU          stMtaAtInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));

    pstJamDetectInd = (RRC_MTA_JAM_DETECT_IND_STRU *)pMsg;

    /* ��д�����ϱ�����Ϣ���� */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    stMtaAtInd.enJamResult = (MTA_AT_JAM_RESULT_ENUM_UINT32)pstJamDetectInd->enResult;

    /* ��д��Ϣͷ���ϱ�����Ϊ�㲥�¼� */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* ͨ����ȡNV����ȡJam Detect��ǰ����ֵ */
    if (NV_OK != NV_Read(en_NV_Item_JAM_DETECT_CFG,
                         &stNvJamDetect,
                         sizeof(NV_NAS_JAM_DETECT_CFG_STRU)))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRrcJamDetectInd: NV_Read en_NV_Item_JAM_DETECT_CFG fail!");
        return;
    }

    /* ���jam detect����δʹ�ܣ���ʹ�յ�GAS��Ϣ��Ҳ�����ϱ� */
    if (VOS_FALSE == stNvJamDetect.ucMode)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRrcJamDetectInd: Jam Detect function is disabled!");
        return ;
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_JAM_DETECT_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}


VOS_VOID TAF_MTA_RcvRrcCheckFreqValidityCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf         = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                                        *pstAtMtaMsgBuf    = VOS_NULL_PTR;
    RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU                   *pstCheckCnf       = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU                           stMtaAtSetCnf;

    /* ��ʼ����Ϣ���� */
    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcCheckFreqValidityCnf:Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvRrcCheckFreqValidityCnf: get command buffer failed!");
        return;
    }

    /* ȡ��֮ǰ�������Ƶ�������ò��� */
    pstAtMtaMsgBuf = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    /* ֻ��Ƶ����Ч����дNV�ɹ��󣬲Ż�����ϱ�AT��ȷ��� */
    pstCheckCnf    = (RRC_MTA_CHECK_FREQ_VALIDITY_CNF_STRU *)pMsg;

    if (MTA_RRC_RESULT_NO_ERROR == pstCheckCnf->enResult)
    {
        if (NV_OK == NV_Write(en_NV_Item_FREQ_LOCK_CFG,
                              pstAtMtaMsgBuf->aucContent,
                              sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU)))
        {
            stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        }
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsgBuf->stAppCtrl),
                     ID_MTA_AT_SET_FREQ_LOCK_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);
    return;
}


VOS_VOID TAF_MTA_RcvTiReqAutotestQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryAutotestCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqAutotestQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stQryAutotestCnf, 0x0, sizeof(stQryAutotestCnf));

    stQryAutotestCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stQryAutotestCnf),
                     (VOS_UINT8*)&stQryAutotestCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}


VOS_VOID TAF_MTA_RcvTiReqCellInfoQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stCellinfoQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellInfoQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellinfoQryCnf, 0x0, sizeof(stCellinfoQryCnf));

    stCellinfoQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stCellinfoQryCnf),
                     (VOS_UINT8*)&stCellinfoQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}




VOS_VOID TAF_MTA_RcvTiReqMeanrptQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stMeanrptQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqMeanrptQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMeanrptQryCnf, 0x0, sizeof(stMeanrptQryCnf));

    stMeanrptQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stMeanrptQryCnf),
                     (VOS_UINT8*)&stMeanrptQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}


VOS_VOID TAF_MTA_RcvTiReqFreqlockSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU    stSetFreqlockCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqFreqlockSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stSetFreqlockCnf, 0x0, sizeof(stSetFreqlockCnf));

    stSetFreqlockCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_SET_CNF,
                     sizeof(stSetFreqlockCnf),
                     (VOS_UINT8*)&stSetFreqlockCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}


VOS_VOID TAF_MTA_RcvTiReqRrcVersionSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU                     stVersionSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqRrcVersionSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stVersionSetCnf, 0x0, sizeof(stVersionSetCnf));

    stVersionSetCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,
                     sizeof(stVersionSetCnf),
                     (VOS_UINT8*)&stVersionSetCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}




VOS_VOID TAF_MTA_RcvTiReqCellsrhSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU                         stCellsrhSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellsrhSetExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellsrhSetCnf, 0x0, sizeof(stCellsrhSetCnf));

    stCellsrhSetCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_SET_CNF,
                     sizeof(stCellsrhSetCnf),
                     (VOS_UINT8*)&stCellsrhSetCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}



VOS_VOID TAF_MTA_RcvTiReqFreqlockQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU    stQryFreqlockCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_FREQLOCK_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqFreqlockQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stQryFreqlockCnf, 0x0, sizeof(stQryFreqlockCnf));

    stQryFreqlockCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,
                     sizeof(stQryFreqlockCnf),
                     (VOS_UINT8*)&stQryFreqlockCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}


VOS_VOID TAF_MTA_RcvTiReqRrcVersionQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU                     stVersionQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_RRC_VERSION_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqRrcVersionQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stVersionQryCnf, 0x0, sizeof(stVersionQryCnf));

    stVersionQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,
                     sizeof(stVersionQryCnf),
                     (VOS_UINT8*)&stVersionQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}




VOS_VOID TAF_MTA_RcvTiReqCellsrhQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                                *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU                         stCellsrhQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLSRH_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellsrhQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellsrhQryCnf, 0x0, sizeof(stCellsrhQryCnf));

    stCellsrhQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLSRH_QRY_CNF,
                     sizeof(stCellsrhQryCnf),
                     (VOS_UINT8*)&stCellsrhQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}


VOS_VOID TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ�����ô��� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_SET_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_SET_CNF);

    return;
}
VOS_VOID TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU       stQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NCELL_MONITOR_QRY_CNF,
                     sizeof(stQryCnf),
                     (VOS_UINT8*)&stQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GRR_NCELLMONITOR_QRY_CNF);

    return;
}
VOS_VOID TAF_MTA_RcvTiWaitGrrSetJamDetectExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_SET_JAM_DETECT_CNF_STRU      stQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    stQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_JAM_DETECT_CNF,
                     sizeof(stQryCnf),
                     (VOS_UINT8*)&stQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_JAM_DETECT_SET_CNF);

    return;
}
VOS_VOID TAF_MTA_RcvTiPhyInitExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf;
    MTA_AT_PHY_INIT_CNF_STRU            stSndAtPhyInitCnf;

    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DSP_INIT_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiPhyInitExpired: WARNING: buffer is null!");
        return;
    }

    /* ��Ϣ�������� */
    PS_MEM_SET(&stSndAtPhyInitCnf, 0x0, sizeof(MTA_AT_PHY_INIT_CNF_STRU));
    stSndAtPhyInitCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* ��ATģ�鷢��ʧ����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                  ID_MTA_AT_PHY_INIT_CNF,
                  sizeof(stSndAtPhyInitCnf),
                  (VOS_UINT8*)&stSndAtPhyInitCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
VOS_VOID TAF_MTA_RcvTiWaitRrcCheckFreqValidityExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf      = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                    *pstAtMtaMsgBuf = VOS_NULL_PTR;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU       stSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAtMtaMsgBuf = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsgBuf->stAppCtrl),
                     ID_MTA_AT_SET_FREQ_LOCK_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_CHECK_FREQ_VALIDITY_CNF);

    return;
}
VOS_UINT32 TAF_MTA_SndWrrQryAutotestReqMsg(
    MTA_WRR_AUTOTEST_PARA_STRU         *pAutotestQryPara
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_AUTOTEST_QRY_REQ_STRU      *pstMtaWrrQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_AUTOTEST_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryReq       = (MTA_WRR_AUTOTEST_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryReq->ulMsgName         = ID_MTA_WRR_AUTOTEST_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_CPY(&(pstMtaWrrQryReq->stWrrAutotestPara),
        pAutotestQryPara,
        sizeof(MTA_WRR_AUTOTEST_PARA_STRU));

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_SndWrrQryCellinfoReqMsg(
    VOS_UINT32                          ulSetCellInfo
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLINFO_QRY_REQ_STRU      *pstMtaWrrQryCellinfoReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_CELLINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryCellinfoReq     = (MTA_WRR_CELLINFO_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryCellinfoReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryCellinfoReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryCellinfoReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryCellinfoReq->ulMsgName         = ID_MTA_WRR_CELLINFO_QRY_REQ;
    pstMtaWrrQryCellinfoReq->ulSetCellInfo     = ulSetCellInfo;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryCellinfoReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndWrrQryMeanrptReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_MEANRPT_QRY_REQ_STRU       *pstMtaWrrQryMeanrptReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_MEANRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryMeanrptReq      = (MTA_WRR_MEANRPT_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryMeanrptReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryMeanrptReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryMeanrptReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryMeanrptReq->ulMsgName         = ID_MTA_WRR_MEASRPT_QRY_REQ;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryMeanrptReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndWrrSetFreqlockReqMsg(
    MTA_WRR_FREQLOCK_CTRL_STRU         *pFreqlockCtrlPara
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_FREQLOCK_SET_REQ_STRU      *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_FREQLOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_FREQLOCK_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetFreqlockReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_FREQLOCK_SET_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_CPY(&(pstMtaWrrSetReq->stFrelock), pFreqlockCtrlPara, sizeof(MTA_WRR_FREQLOCK_CTRL_STRU));

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetFreqlockReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_SndWrrSetVersionReqMsg(
    VOS_UINT8                           ucRrcVersion
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_RRC_VERSION_SET_REQ_STRU   *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_RRC_VERSION_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_RRC_VERSION_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetVersionReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_RRC_VERSION_SET_REQ;
    pstMtaWrrSetReq->ucRRCVersion      = ucRrcVersion;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET((pstMtaWrrSetReq->aucReserv), 0, sizeof(pstMtaWrrSetReq->aucReserv));

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetVersionReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_SndWrrSetCellsrhReqMsg(
    VOS_UINT8                           ucCellSrh
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLSRH_SET_REQ_STRU       *pstMtaWrrSetReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_CELLSRH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrSetReq       = (MTA_WRR_CELLSRH_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrSetReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrSetReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrSetReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrSetReq->ulMsgName         = ID_MTA_WRR_CELLSRH_SET_REQ;
    pstMtaWrrSetReq->ucCellSrh         = ucCellSrh;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET((pstMtaWrrSetReq->aucReserve), 0, sizeof(pstMtaWrrSetReq->aucReserve));

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 TAF_MTA_SndWrrQryFreqlockReqMsg(VOS_VOID)
{

    VOS_UINT32                          ulLength;
    MTA_WRR_FREQLOCK_QRY_REQ_STRU      *pstMtaWrrQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_FREQLOCK_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryReq       = (MTA_WRR_FREQLOCK_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryFreqlockReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryReq->ulMsgName         = ID_MTA_WRR_FREQLOCK_QRY_REQ;

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryFreqlockReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndWrrQryRrcVersionReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_RRC_VERSION_QRY_REQ_STRU   *pstMtaWrrQryVersionReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_RRC_VERSION_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryVersionReq      = (MTA_WRR_RRC_VERSION_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryVersionReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryRrcVersionReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryVersionReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryVersionReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryVersionReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryVersionReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryVersionReq->ulMsgName         = ID_MTA_WRR_RRC_VERSION_QRY_REQ;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryVersionReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryRrcVersionReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndWrrQryCellsrhReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLSRH_QRY_REQ_STRU       *pstMtaWrrQryCellsrhReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_CELLSRH_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryCellsrhReq      = (MTA_WRR_CELLSRH_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryCellsrhReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellsrhReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryCellsrhReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellsrhReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryCellsrhReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellsrhReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryCellsrhReq->ulMsgName         = ID_MTA_WRR_CELLSRH_QRY_REQ;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryCellsrhReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellsrhReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndGrrNCellMonitorSetReq(
    VOS_UINT8                         ucRptCmdStatus
)
{
    MTA_GRR_NCELL_MONITOR_SET_REQ_STRU          *pstNCellMonitorSetReq  = VOS_NULL_PTR;

    /* �����ڴ� */
    pstNCellMonitorSetReq = (MTA_GRR_NCELL_MONITOR_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ڴ�����쳣���� */
    if (VOS_NULL_PTR == pstNCellMonitorSetReq)
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorSetReq:alloc msg failed.");
        return VOS_ERR;
    }

    /* ��д����Ϣ���� */
    PS_MEM_SET(pstNCellMonitorSetReq, 0, sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU));
    pstNCellMonitorSetReq->ulSenderPid      = UEPS_PID_MTA;
    pstNCellMonitorSetReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNCellMonitorSetReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNCellMonitorSetReq->ulReceiverPid    = UEPS_PID_GAS;
    pstNCellMonitorSetReq->ulMsgName        = ID_MTA_GRR_NCELL_MONITOR_SET_REQ;
    pstNCellMonitorSetReq->ulLength         = sizeof(MTA_GRR_NCELL_MONITOR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstNCellMonitorSetReq->ucSwitch         = ucRptCmdStatus;

    /* ������Ϣ�쳣���� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstNCellMonitorSetReq))
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorSetReq: PS_SEND_MSG ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MTA_SndGrrNCellMonitorQryReq(VOS_VOID)
{
    MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU          *pstNCellMonitorQryReq  = VOS_NULL_PTR;

    /* �����ڴ� */
    pstNCellMonitorQryReq = (MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ڴ�����쳣���� */
    if (VOS_NULL_PTR == pstNCellMonitorQryReq)
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorQryReq:alloc msg failed.");
        return VOS_ERR;
    }

    /* ��д����Ϣ���� */
    PS_MEM_SET(pstNCellMonitorQryReq, 0, sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU));
    pstNCellMonitorQryReq->ulSenderPid      = UEPS_PID_MTA;
    pstNCellMonitorQryReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstNCellMonitorQryReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstNCellMonitorQryReq->ulReceiverPid    = UEPS_PID_GAS;
    pstNCellMonitorQryReq->ulMsgName        = ID_MTA_GRR_NCELL_MONITOR_QRY_REQ;
    pstNCellMonitorQryReq->ulLength         = sizeof(MTA_GRR_NCELL_MONITOR_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�쳣���� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstNCellMonitorQryReq))
    {
        MTA_WARNING_LOG("TAF_MTA_SndGrrNCellMonitorQryReq: PS_SEND_MSG ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 TAF_MTA_SndGrrSetJamDetectReq(
    AT_MTA_SET_JAM_DETECT_REQ_STRU     *pstSetJdrReq
)
{
    VOS_UINT32                          ulLength;
    MTA_RRC_JAM_DETECT_REQ_STRU        *pstMtaGrrJamDetectReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_RRC_JAM_DETECT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaGrrJamDetectReq = (MTA_RRC_JAM_DETECT_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaGrrJamDetectReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGrrSetJamDetectReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaGrrJamDetectReq->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaGrrJamDetectReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstMtaGrrJamDetectReq->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaGrrJamDetectReq->stMsgHeader.ulReceiverPid     = UEPS_PID_GAS;
    pstMtaGrrJamDetectReq->stMsgHeader.ulLength          = ulLength;
    pstMtaGrrJamDetectReq->stMsgHeader.ulMsgName         = ID_MTA_RRC_JAM_DETECT_REQ;

    pstMtaGrrJamDetectReq->enMode      = (MTA_RRC_JAM_MODE_ENUM_UINT8)pstSetJdrReq->ucFlag;
    pstMtaGrrJamDetectReq->ucMethod    = pstSetJdrReq->ucMethod;
    pstMtaGrrJamDetectReq->ucThreshold = pstSetJdrReq->ucThreshold;
    pstMtaGrrJamDetectReq->ucFreqNum   = pstSetJdrReq->ucFreqNum;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaGrrJamDetectReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGrrSetJamDetectReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndRrcSetFreqLockReq(
    AT_MTA_SET_FREQ_LOCK_REQ_STRU      *pstSetFreqLockReq
)
{
    MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU   *pstMtaRrcCheckFreqReq = VOS_NULL_PTR;
    VOS_UINT32                              ulReceiverPid;
    VOS_UINT32                              ulLength;

    /* ������ReceiverPid */
    switch (pstSetFreqLockReq->enRatMode)
    {
        case AT_MTA_FREQLOCK_RATMODE_GSM:
            ulReceiverPid = UEPS_PID_GAS;
            break;

        case AT_MTA_FREQLOCK_RATMODE_WCDMA:
            ulReceiverPid = WUEPS_PID_WRR;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case AT_MTA_FREQLOCK_RATMODE_LTE:
            ulReceiverPid = PS_PID_ERRC;
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        case AT_MTA_FREQLOCK_RATMODE_TD:
            ulReceiverPid = TPS_PID_RRC;
            break;
#endif

        default:
            MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: RatMode not support");
            return VOS_ERR;
    }

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaRrcCheckFreqReq = (MTA_RRC_CHECK_FREQ_VALIDITY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaRrcCheckFreqReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: Alloc msg fail!");
        return VOS_ERR;
    }

    pstMtaRrcCheckFreqReq->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMtaRrcCheckFreqReq->stMsgHeader.ulMsgName     = ID_MTA_RRC_CHECK_FREQ_VALIDITY_REQ;
    pstMtaRrcCheckFreqReq->usFreq                    = pstSetFreqLockReq->usLockedFreq;
    pstMtaRrcCheckFreqReq->enBand                    = (MTA_RRC_GSM_BAND_ENUM_UINT16)pstSetFreqLockReq->enBand;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaRrcCheckFreqReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetFreqLockReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID TAF_MTA_RcvNasAreaLostInd(
    VOS_VOID                           *pMsg
)
{
    VOS_INT32                           lRslt;

    /* ���õ���ӿڣ��������0����ʾPA�����������κβ��������ط�0��ʾPA�쳣������й��� */
#if defined(INSTANCE_1)
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_1);
#elif defined(INSTANCE_2)
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_2);
#else
    lRslt = mdrv_pmu_check_pastar((PWC_COMM_MODEM_E)MODEM_ID_0);
#endif

    if (VOS_OK == lRslt)
    {
        return;
    }

    NAS_EventReport(UEPS_PID_MTA,
                    NAS_OM_EVENT_PA_STAR_ABNORMAL,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
VOS_VOID TAF_MTA_RcvTafAgentGetAntStateReq(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT                                ulAntState;
    MODEM_ID_ENUM_UINT16                    enModemId;
    TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU    *pstMsg= VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_MTA);
    ulAntState  = 0;

    pstMsg = (TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                                 sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetAntStateReq:alloc msg failed.");

        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH), 0, (sizeof(TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_TAFAGENT;
    pstMsg->enMsgId         = ID_TAFAGENT_MTA_GET_ANT_STATE_CNF;
    pstMsg->ulRslt          = VOS_ERR;
    pstMsg->usAntState      = 0;

    /* ���õ���ӿڻ�ȡ����״̬ */
    if (VOS_OK == mdrv_anten_get_lockstate((PWC_COMM_MODEM_E)enModemId, &ulAntState))
    {
        pstMsg->ulRslt      = VOS_OK;
        pstMsg->usAntState  = (VOS_UINT16)ulAntState;
    }

    /* ��TAFAGENT���Ͳ�ѯ�ظ� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetAntStateReq:send msg failed.");

        return;
    }

    return;
}

#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_MTA_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
)
{
    OM_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* �ϱ�����Ϣ�ܳ��� */
    ulMsgLen  = ((sizeof(OM_ERR_LOG_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH) - 4) + ulBufUseLen;

    /* ��Ϣ�ռ����� */
    pstQryCnf = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmErrLogRptCnf: alloc msg fail!");
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = UEPS_PID_MTA;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    /* buffer��Ϊ��ʱ��lenҲ�ǲ���Ϊ�յ� */
    if (VOS_NULL_PTR != pbuffer)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstQryCnf))
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmErrLogRptCnf: SEND MSG FAIL");
    }

    return;

}
VOS_VOID TAF_MTA_RcvAcpuOmErrLogRptReq(
    VOS_VOID                           *pMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    NAS_ERR_LOG_MNTN_EVENT_STRU         stNasErrLogMntnEvent;

    /* ��ѯһ��RING BUFFER���ж������ݣ��Ա�����ڴ� */
    ulBufUseLen = TAF_SDC_GetErrLogRingBufferUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)PS_MEM_ALLOC(UEPS_PID_MTA, ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        TAF_MTA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    PS_MEM_SET(pbuffer, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = TAF_SDC_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        TAF_MTA_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        PS_MEM_FREE(UEPS_PID_MTA, pbuffer);
        return;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                      VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                      NAS_ERR_LOG_ALM_MNTN,
                                      NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MNTN),
                                      VOS_GetSlice(),
                                      (sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = TAF_SDC_GetErrlogOverflowCnt();

    PS_MEM_CPY(pbuffer + ulBufUseLen, &stNasErrLogMntnEvent, sizeof(stNasErrLogMntnEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    TAF_SDC_CleanErrLogRingBuf();

    /* ����������� */
    TAF_SDC_SetErrlogOverflowCnt(0);

    /* ��ά�ɲ�BUF����Ĺ��� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           UEPS_PID_MTA,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    TAF_MTA_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    PS_MEM_FREE(UEPS_PID_MTA, pbuffer);

    return;
}
VOS_VOID TAF_MTA_RcvAcpuOmErrLogCtrlInd(
    VOS_VOID                           *pMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pMsg;

    /* ����ERRLOG���Ʊ�ʶ */
    if ((VOS_FALSE == pstRcvMsg->ucAlmStatus)
     || (VOS_TRUE  == pstRcvMsg->ucAlmStatus))
    {
        TAF_SDC_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);
    }

    if ((pstRcvMsg->ucAlmLevel >= NAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= NAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        TAF_SDC_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return;
}
VOS_VOID TAF_MTA_SndAcpuOmInfoCltRptCnf(
    VOS_VOID                           *pMsg,
    VOS_UINT32                          ulLength
)
{
    OM_INFO_CLT_REPORT_CNF_STRU        *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* �ϱ�����Ϣ�ܳ��� */
    ulMsgLen  = (sizeof(OM_INFO_CLT_REPORT_CNF_STRU) - 4) + ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    pstQryCnf = (OM_INFO_CLT_REPORT_CNF_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(ulMsgLen);

    if (VOS_NULL_PTR == pstQryCnf)
    {
        MTA_ERROR_LOG("TAF_MTA_SndAcpuOmInfoCltRptCnf: Alloc msg fail!");
        return;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstQryCnf);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstQryCnf, MSP_PID_DIAG_APP_AGENT, ID_OM_INFO_CLT_REPORT_CNF);

    /* ��д��Ϣ���� */
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_INFO_CLT_CNF;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptLen         = ulLength;

    /* ��Ϣ��Ϊ��ʱ��lenҲ�ǲ���Ϊ�յ� */
    if (VOS_NULL_PTR != pMsg)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pMsg, ulLength);
    }

    /* ������Ϣ */
    TAF_MTA_SEND_MSG(pstQryCnf);

    return;

}
VOS_VOID TAF_MTA_RcvAcpuOmInfoCltRptReq(
    VOS_VOID                           *pMsg
)
{
    OM_INFO_CLT_REPORT_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstRcvMsg = (OM_INFO_CLT_REPORT_REQ_STRU *)pMsg;

    switch (pstRcvMsg->enSceneType)
    {
        /* �жϵ�ǰ��������Ϊ��ͨ����Ϣ�ɼ� */
        case OM_INFO_CLT_SCENE_TYPE_FREQ_BAND:
            TAF_MTA_RcvAcpuOmFreqBandQryReq((VOS_VOID *)pstRcvMsg);
            break;

        /* Added by z00328328 for TX_POWER_CHR, 2015-10-19, begin */
        /* �жϵ�ǰ��������Ϊ���з��书�ʲɼ� */
        case OM_INFO_CLT_SCENE_TYPE_TX_POWER:
            TAF_MTA_RcvAcpuOmTxPowerQryReq((VOS_VOID *)pstRcvMsg);
            break;
        /* Added by z00328328 for TX_POWER_CHR, 2015-10-19, end */

        default:
            /* ����ID_OM_INFO_CLT_REPORT_CNF����Ϊ�յ���Ϣ��OM */
            TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);

            MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmInfoCltRptReq: Scense type error!");
            break;
    }

    return;
}


VOS_VOID TAF_MTA_SndAcpuOmFreqBandQryCnf(
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                      *pstInfoCltCtx = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU        *pstFreqInfo   = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                           *pstCurrPlmn   = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* �ֲ�������ʼ�� */

    /* ��ȡMTA�������б�����ͨ��Ƶ��ɼ������� */
    pstInfoCltCtx = TAF_MTA_GetInfoCltAddr();
    pstFreqInfo   = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* ��ͨ��Ƶ�����������Ϣ��� */
    if (TAF_MTA_INFO_CLT_RESULT_SUCC == enCltResult)
    {
        pstCurrPlmn = TAF_SDC_GetCurrCampPlmnId();

        pstFreqInfo->enNetMode      = TAF_SDC_GetSysMode();
        pstFreqInfo->stPlmn.ulMcc   = pstCurrPlmn->ulMcc;
        pstFreqInfo->stPlmn.ulMnc   = pstCurrPlmn->ulMnc;
        pstFreqInfo->ucRac          = TAF_SDC_GetCurrCampRac();
        pstFreqInfo->usLac          = TAF_SDC_GetCurrCampLac();
        pstFreqInfo->ulCellId       = TAF_SDC_GetCurrCampCellId();

        ulLength = sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU) - sizeof(OM_INFO_CLT_HEADER_STRU);

        NAS_COMM_BULID_INFOCLT_HEADER_INFO(&pstFreqInfo->stHeader,
                                          VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                          OM_INFO_CLT_SCENE_TYPE_FREQ_BAND,
                                          ulLength);

        TAF_MTA_SndAcpuOmInfoCltRptCnf((VOS_VOID *)pstFreqInfo,
                                       sizeof(NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU));
    }
    else
    {
        /* ����ID_OM_INFO_CLT_REPORT_CNF����Ϣ��OM */
        TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);
    }

    /* ������Ƶ����Ϣ����Ҫ�ͷ�Ƶ����Ϣ�������� */
    TAF_MMA_FreeFreqInfoCltCtx();

    return;

}
VOS_VOID TAF_MTA_RcvAcpuOmFreqBandQryReq(
    VOS_VOID                           *pMsg
)
{
    OM_INFO_CLT_REPORT_REQ_STRU        *pstRcvMsg = VOS_NULL_PTR;
    MNTN_PLMN_ID_STRU                  *pstPlmnId = VOS_NULL_PTR;
    TAF_MTA_INFO_CLT_PLMN_LIST_STRU     stInfoCltPlmnList;

    /* �ֲ�������ʼ�� */
    pstRcvMsg   = (OM_INFO_CLT_REPORT_REQ_STRU*)pMsg;
    pstPlmnId   = (MNTN_PLMN_ID_STRU *)pstRcvMsg->aucContent;

    /* ����·���PLMN�Ƿ�Ϸ� */
    if (sizeof(MNTN_PLMN_ID_STRU) != pstRcvMsg->ulMsgLen)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmFreqBandQryReq: Receive PLMN Length is Invalid!");
        TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    if (VOS_FALSE == TAF_SDC_IsPlmnIdValid((TAF_SDC_PLMN_ID_STRU *)pstPlmnId))
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAcpuOmFreqBandQryReq: Receive PLMN Value is Invalid!");
        TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    /* Ŀǰֻ֧��һ��PLMN�Ĳ�ѯ���� */
    PS_MEM_SET(&stInfoCltPlmnList, 0, sizeof(TAF_MTA_INFO_CLT_PLMN_LIST_STRU));
    stInfoCltPlmnList.ucPlmnNum = 1;
    PS_MEM_CPY(&stInfoCltPlmnList.astPlmnInfo[0], pstPlmnId, sizeof(MNTN_PLMN_ID_STRU));

    /* ����Ƶ���ռ��������� */
    TAF_MMA_AllocFreqInfoCltCtx();

    /* ���ƽ̨֧��GSM����GASȥ��ȡƵ����Ϣ */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, UEPS_PID_GAS);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS);
    }

    /* ���ƽ̨֧��WCDMA����WASȥ��ȡƵ����Ϣ */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, WUEPS_PID_WRR);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS);
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ���ƽ̨֧��LTE����LRRCȥ��ȡƵ����Ϣ */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        TAF_MTA_SndRrcPlmnFreqQryReq(&stInfoCltPlmnList, PS_PID_ERRC);

        TAF_MTA_SetWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC);
    }
#endif

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF,
                                 TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF_TIMER_LEN);

    return;
}



VOS_VOID TAF_MTA_SndRrcPlmnFreqQryReq(
    VOS_VOID                           *pData,
    VOS_UINT32                          ulReceiverPid
)
{
    TAF_MTA_INFO_CLT_PLMN_LIST_STRU    *pstPlmnList = VOS_NULL_PTR;
    MTA_RRC_PLMN_FREQ_QRY_REQ_STRU     *pstMsg      = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstPlmnList                  = (TAF_MTA_INFO_CLT_PLMN_LIST_STRU *)pData;

    /* ������Ϣ�ṹ�ڴ� */
    pstMsg = (MTA_RRC_PLMN_FREQ_QRY_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_RRC_PLMN_FREQ_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcPlmnFreqQryReq: Alloc msg fail!");
        return;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstMsg, ulReceiverPid, ID_MTA_RRC_PLMN_FREQ_QRY_REQ);

    /* ��д��Ϣ���� */
    if (0 == pstPlmnList->ucPlmnNum)
    {
        pstMsg->enQueryType             = MTA_RRC_FREQ_QRY_TYPE_ALL_PLMN;
        pstMsg->ucPlmnIdNum             = 0;
    }
    else
    {
        pstMsg->enQueryType             = MTA_RRC_FREQ_QRY_TYPE_SPEC_PLMN;
        pstMsg->ucPlmnIdNum             = pstPlmnList->ucPlmnNum;
        PS_MEM_CPY(pstMsg->astPlmnIdList,
                   pstPlmnList->astPlmnInfo,
                   MTA_RRC_MAX_PLMN_NUM * sizeof(MNTN_PLMN_ID_STRU));
    }

    pstMsg->aucRsv[0]                   = 0;
    pstMsg->aucRsv[1]                   = 0;

    /* ������Ϣ */
    TAF_MTA_SEND_MSG(pstMsg);

    return;
}


VOS_VOID TAF_MTA_RcvGasPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_GSM_PLMN_FREQ_LIST_STRU                        *pstGsmFreqList          = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* ��ȡMTA�������б�����ͨ��Ƶ��ɼ������� */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ����GAS��ͨ��Ƶ����Ϣ */
    pstGsmFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stGsmFreqList;

    if (0 < pstGsmFreqList->ucPlmnNum)
    {
        /* Ŀǰֻ֧�ֵ���PLMNƵ��ɼ� */
        pstFreqInfoClt->stGFreqList.stPlmnId.ulMcc = pstGsmFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stGFreqList.stPlmnId.ulMnc = pstGsmFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstGsmFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_GSM_FREQ_NUM >= pstGsmFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stGFreqList.usFreqNum = pstGsmFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stGFreqList.usFreqNum = NAS_INFO_CLT_MAX_GSM_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stGFreqList.astFreqInfo[0],
                       &pstGsmFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_GU_FREQ_INFO_STRU) * pstFreqInfoClt->stGFreqList.usFreqNum);
        }
    }

    /*  ������Ϣ�ɼ���ʶ */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_GAS);

    /* �ж���Ϣ�ɼ��Ƿ���� */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* ����ͨ��Ƶ����Ϣ��OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}
VOS_VOID TAF_MTA_RcvWrrPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_WCDMA_PLMN_FREQ_LIST_STRU                      *pstWcdmaFreqList        = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* ��ȡMTA�������б�����ͨ��Ƶ��ɼ������� */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ����WRR��ͨ��Ƶ����Ϣ */
    pstWcdmaFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stWcdmaFreqList;

    if (0 < pstWcdmaFreqList->ucPlmnNum)
    {
        /* Ŀǰֻ֧�ֵ���PLMNƵ��ɼ� */
        pstFreqInfoClt->stWFreqList.stPlmnId.ulMcc = pstWcdmaFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stWFreqList.stPlmnId.ulMnc = pstWcdmaFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM >= pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stWFreqList.usFreqNum = pstWcdmaFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stWFreqList.usFreqNum = NAS_INFO_CLT_MAX_WCDMA_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stWFreqList.astFreqInfo[0],
                       &pstWcdmaFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_GU_FREQ_INFO_STRU) * pstFreqInfoClt->stWFreqList.usFreqNum);
        }
    }

    /*  ������Ϣ�ɼ���ʶ */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_WAS);

    /* �ж���Ϣ�ɼ��Ƿ���� */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* ����ͨ��Ƶ����Ϣ��OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MTA_RcvLrrcPlmnFreqQryCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_INFO_CLT_CTX_STRU                              *pstInfoCltCtx           = VOS_NULL_PTR;
    RRC_MTA_PLMN_FREQ_QRY_CNF_STRU                         *pstRrcMtaPlmnFreqQryCnf = VOS_NULL_PTR;
    NAS_INFO_CLT_CLOUD_FREQ_BAND_EVENT_STRU                *pstFreqInfoClt          = VOS_NULL_PTR;
    RRC_MTA_LTE_PLMN_FREQ_LIST_STRU                        *pstLteFreqList          = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstRrcMtaPlmnFreqQryCnf           = (RRC_MTA_PLMN_FREQ_QRY_CNF_STRU*)pMsg;

    /* ��ȡMTA�������б�����ͨ��Ƶ��ɼ������� */
    pstInfoCltCtx  = TAF_MTA_GetInfoCltAddr();
    pstFreqInfoClt = pstInfoCltCtx->pstFreqInfoCltCtx;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcPlmnFreqQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ����LRRC��ͨ��Ƶ����Ϣ */
    pstLteFreqList = &pstRrcMtaPlmnFreqQryCnf->u.stLteFreqList;

    if (0 < pstLteFreqList->ucPlmnNum)
    {
        /* Ŀǰֻ֧�ֵ���PLMNƵ��ɼ� */
        pstFreqInfoClt->stLFreqList.stPlmnId.ulMcc = pstLteFreqList->astPlmnFreqList[0].stPlmnId.ulMcc;
        pstFreqInfoClt->stLFreqList.stPlmnId.ulMnc = pstLteFreqList->astPlmnFreqList[0].stPlmnId.ulMnc;

        if (0 < pstLteFreqList->astPlmnFreqList[0].usFreqNum)
        {
            if (NAS_INFO_CLT_MAX_LTE_FREQ_NUM >= pstLteFreqList->astPlmnFreqList[0].usFreqNum)
            {
                pstFreqInfoClt->stLFreqList.usFreqNum = pstLteFreqList->astPlmnFreqList[0].usFreqNum;
            }
            else
            {
                pstFreqInfoClt->stLFreqList.usFreqNum = NAS_INFO_CLT_MAX_LTE_FREQ_NUM;
            }

            PS_MEM_CPY(&pstFreqInfoClt->stLFreqList.astFreqInfo[0],
                       &pstLteFreqList->astPlmnFreqList[0].astFreqList[0],
                       sizeof(NAS_INFO_CLT_LTE_FREQ_INFO_STRU) * pstFreqInfoClt->stLFreqList.usFreqNum);
        }
    }

    /*  ������Ϣ�ɼ���ʶ */
    TAF_MTA_ClrWaitFreqCltCnfFlag(TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_LRRC);

    /* �ж���Ϣ�ɼ��Ƿ���� */
    if (TAF_MTA_WAIT_FREQ_CLT_CNF_FLAG_NULL != TAF_MTA_GetWaitFreqCltCnfFlag())
    {
        return;
    }

    /* ����ͨ��Ƶ����Ϣ��OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_FREQ_CLT_QRY_CNF);

    return;
}
#endif
VOS_VOID TAF_MTA_RcvTiWaitFreqCltQryCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    /* ����ͨ��Ƶ����Ϣ��OM */
    TAF_MTA_SndAcpuOmFreqBandQryCnf(TAF_MTA_INFO_CLT_RESULT_SUCC);

    /* ������е�Ƶ���ռ��ظ���ʶ */
    TAF_MTA_ClrAllWaitFreqCltCnfFlag();

    return;
}



/* Added by z00328328 for TX_POWER_CHR, 2015-10-19, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAcpuOmTxPowerQryReq
 ��������  : �յ����з��书�ʲɼ�����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : ���巼 z00328328
    �޸�����   : ���з��书�ʲɼ���Ŀ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAcpuOmTxPowerQryReq(
    VOS_VOID                           *pMsg
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranctrlMode;

    /* ��ȡ��ǰ���뼼�� */
    enRatType                           = TAF_SDC_GetSysMode();
    enUtranctrlMode                     = NAS_UTRANCTRL_GetCurrUtranMode();

    /* ���GSM, WCDMA��������GWPHYȥ��ȡ���з��书�� */
    if ((TAF_SDC_SYS_MODE_GSM == enRatType)
     || ((TAF_SDC_SYS_MODE_WCDMA       == enRatType)
      && (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranctrlMode)))
    {
        TAF_MTA_SndPhyTxPwrQryReq(DSP_PID_APM);
    }
    /* ���TDS, LTE��������TLPHYȥ��ȡ���з��书�� */
    else if ((TAF_SDC_SYS_MODE_LTE == enRatType)
          || ((TAF_SDC_SYS_MODE_WCDMA == enRatType)
           && (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranctrlMode)))
    {
        TAF_MTA_SndPhyTxPwrQryReq(TLPHY_PID_RTTAGENT);
    }
    else
    {
        /* ���಻֧�ֵ���ʽ��ֱ�ӷ���ʧ�� */
        TAF_MTA_SndAcpuOmTxPowerQryCnf(VOS_NULL_PTR, TAF_MTA_INFO_CLT_RESULT_FAIL);
        return;
    }

    /* ��ΪG,Wģʽ������������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF,
                                 TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF_TIMER_LEN);


    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_SndAcpuOmTxPowerQryCnf
 ��������  : ��ACPU OM�ظ����з��书���ռ���Ϣ
 �������  : enCltResult �ռ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : ���巼 z00328328
    �޸�����   : ���з��书�ʲɼ���Ŀ��������
*****************************************************************************/
VOS_VOID TAF_MTA_SndAcpuOmTxPowerQryCnf(
    VOS_VOID                           *pMsg,
    TAF_MTA_INFO_CLT_RESULT_ENUM_U32    enCltResult
)
{
    NAS_INFO_CLT_TX_POWER_EVENT_STRU   *pstTxPwrInfo        = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    pstTxPwrInfo                        = (NAS_INFO_CLT_TX_POWER_EVENT_STRU *)pMsg;

    /* ���з��书�����������Ϣ��� */
    if (TAF_MTA_INFO_CLT_RESULT_SUCC == enCltResult)
    {
        ulLength = sizeof(NAS_INFO_CLT_TX_POWER_EVENT_STRU) - sizeof(OM_INFO_CLT_HEADER_STRU);

        NAS_COMM_BULID_INFOCLT_HEADER_INFO(&pstTxPwrInfo->stHeader,
                                            VOS_GetModemIDFromPid(UEPS_PID_MTA),
                                            OM_INFO_CLT_SCENE_TYPE_TX_POWER,
                                            ulLength);

        TAF_MTA_SndAcpuOmInfoCltRptCnf((VOS_VOID *)pstTxPwrInfo,
                                        sizeof(NAS_INFO_CLT_TX_POWER_EVENT_STRU));
    }
    else
    {
        /* ����ID_OM_INFO_CLT_REPORT_CNF����Ϣ��OM */
        TAF_MTA_SndAcpuOmInfoCltRptCnf(VOS_NULL_PTR, 0);
    }

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyTxPwrQryReq
 ��������  : MTA��PHY������Ϣ�ɼ�����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : ���巼 z00328328
    �޸�����   : ���з��书�ʲɼ���Ŀ��������
*****************************************************************************/
VOS_VOID TAF_MTA_SndPhyTxPwrQryReq(
    VOS_UINT32                          ulReceiverPid
)
{
    MTA_PHY_TX_POWER_QRY_REQ_STRU      *pstMsg              = VOS_NULL_PTR;
    MTA_PHY_MSG_TYPE_ENUM_UINT16        enMsgId;

    /* ���PID */
    if (TLPHY_PID_RTTAGENT == ulReceiverPid)
    {
        enMsgId = ID_MTA_TLPHY_GET_TX_POWER_INFO_REQ;
    }
    else if (DSP_PID_APM == ulReceiverPid)
    {
        enMsgId = ID_MTA_APM_GET_TX_POWER_INFO_REQ;
    }
    else
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyTxPwrQryReq: PID is not allowed!");
        return;
    }

    /* ������Ϣ�ṹ�ڴ� */
    pstMsg = (MTA_PHY_TX_POWER_QRY_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_PHY_TX_POWER_QRY_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyTxPwrQryReq: Alloc msg fail!");
        return;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstMsg);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstMsg, ulReceiverPid, enMsgId);

    /* ������Ϣ */
    TAF_MTA_SEND_MSG(pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGphyTxPwrQryCnf
 ��������  : mta�յ�WPHY ID_GUPHY_MTA_TX_POWER_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : ���巼 z00328328
    �޸�����   : ���з��书�ʲɼ���Ŀ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyTxPwrQryCnf(
    VOS_VOID                           *pMsg
)
{
    PHY_MTA_TX_POWER_QRY_CNF_STRU      *pstMtaTxPwrQryCnf   = VOS_NULL_PTR;
    NAS_INFO_CLT_TX_POWER_EVENT_STRU    stTxPwrInfo;

    /* �ֲ�������ʼ�� */
    pstMtaTxPwrQryCnf                   = (PHY_MTA_TX_POWER_QRY_CNF_STRU *)pMsg;
    PS_MEM_SET(&stTxPwrInfo, 0, sizeof(NAS_INFO_CLT_TX_POWER_EVENT_STRU));

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF))
    {
        MTA_WARNING_LOG( "TAF_MTA_RcvPhyTxPwrQryCnf: WARNING: Timer was already stop!" );
        return;
    }

    stTxPwrInfo.lTxPower                = pstMtaTxPwrQryCnf->lTxPower;
    stTxPwrInfo.ulSavedSlice            = pstMtaTxPwrQryCnf->ulSavedSlice;

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_TX_PWR_CLT_QRY_CNF);

    /* �����з��书�ʲɼ���Ϣ��OM */
    TAF_MTA_SndAcpuOmTxPowerQryCnf(&stTxPwrInfo, TAF_MTA_INFO_CLT_RESULT_SUCC);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitTxPwrCltQryCnfExpired
 ��������  : MTA�յ���ʱ����ʱ��Ϣ������
 �������  : pstMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : ���巼 z00328328
    �޸�����   : ���з��书�ʲɼ���Ŀ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitTxPwrCltQryCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    /* ��ʱ, ���Ϳ���Ϣ��OM�����ϲ���� */
    TAF_MTA_SndAcpuOmTxPowerQryCnf(VOS_NULL_PTR, TAF_MTA_INFO_CLT_RESULT_FAIL);

    return;
}
/* Added by z00328328 for TX_POWER_CHR, 2015-10-19, end */

#endif

#if ( (FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS) )

VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_SET_DPDTTEST_FLAG_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_SET_DPDTTEST_FLAG_NTF;
    pstMsg->ucFlag                  = pstSetDpdtFlagReq->ucFlag;

    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }

    /* ������Ϣ��TLRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU  *pstSetDpdtReq
)
{
    MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtValueNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_SET_DPDT_VALUE_NTF;
    pstMsg->ulDpdtValue             = pstSetDpdtReq->ulDpdtValue;

    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }

    /* ������Ϣ��LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcSetDpdtValueNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_MTA_SndTLrrcQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_TLRRC_QRY_DPDT_VALUE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = ID_MTA_TLRRC_QRY_DPDT_VALUE_REQ;

    if (AT_MTA_CMD_RATMODE_LTE == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid           = PS_PID_ERRC;
    }
    else
    {
        pstMsg->ulReceiverPid           = TPS_PID_RRC;
    }

    /* ������Ϣ��LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTLrrcQryDpdtValueReqMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID TAF_MTA_RcvTLrrcDpdtValueQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf        = VOS_NULL_PTR;
    TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU  *pstLrrcMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* �ֲ�������ʼ�� */
    pstLrrcMtaQryCnf = (TLRRC_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTLrrcDpdtValueQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ������Ϣ�ṹ�� */
    if (MTA_RRC_RESULT_NO_ERROR == pstLrrcMtaQryCnf->enResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stMtaAtQryCnf.ulDpdtValue = pstLrrcMtaQryCnf->ulDpdtValue;
    }
    else
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;
        stMtaAtQryCnf.ulDpdtValue = 0;
    }

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetFrReqMsg
 ��������  : ��LRRC����ID_MTA_LRRC_SET_FR_REQ
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��03��
    ��    ��   : wx270776
    �޸�����   : �½�����

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndLrrcSetFrReqMsg(
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstAtMtaSetFrReq = VOS_NULL_PTR;
    MTA_LRRC_SET_FR_REQ_STRU           *pstMtaLrrcSetFrReq = VOS_NULL_PTR;
    AT_MTA_SET_FR_REQ_STRU              stAtMtaSetFrReq;
    VOS_UINT32                          ulLength;

    PS_MEM_SET(&stAtMtaSetFrReq, 0, sizeof(AT_MTA_SET_FR_REQ_STRU));

    pstAtMtaSetFrReq   = (MN_APP_REQ_MSG_STRU*)pstMsg;
    PS_MEM_CPY(&stAtMtaSetFrReq, pstAtMtaSetFrReq->aucContent, sizeof(AT_MTA_SET_FR_REQ_STRU));

    /* ������Ϣ�ṹ�ڴ� */
    ulLength           = sizeof(MTA_LRRC_SET_FR_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetFrReq = (MTA_LRRC_SET_FR_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetFrReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetFrReqMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    /* �����Ϣ�� */
    pstMtaLrrcSetFrReq->stMsgHeader.ulSenderPid     = UEPS_PID_MTA;
    pstMtaLrrcSetFrReq->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMtaLrrcSetFrReq->stMsgHeader.ulReceiverPid   = PS_PID_ERRC;
    pstMtaLrrcSetFrReq->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMtaLrrcSetFrReq->stMsgHeader.ulLength        = ulLength;
    pstMtaLrrcSetFrReq->stMsgHeader.ulMsgName       = ID_MTA_LRRC_SET_FR_REQ;
    pstMtaLrrcSetFrReq->enActFrFlag                 = stAtMtaSetFrReq.enActFrFlag;
    pstMtaLrrcSetFrReq->aucRsv[0]                   = 0;
    pstMtaLrrcSetFrReq->aucRsv[1]                   = 0;
    pstMtaLrrcSetFrReq->aucRsv[2]                   = 0;

    /* ������Ϣ��LRRC */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetFrReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetFrReqMsg: Send msg fail!");

        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetFrReq
 ��������  : MTA�յ�AT������ID_AT_MTA_SET_FR_REQ��Ϣ������
 �������  : pstMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : wx270776
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetFrReq(
    VOS_VOID                           *pstMsg
)
{
    AT_MTA_MSG_STRU                    *pstAtMtaMsg      = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* �ֲ�������ʼ�� */
    pstAtMtaMsg                       = (AT_MTA_MSG_STRU*)pstMsg;
    ulResult                          = VOS_ERR;
    PS_MEM_SET(&stMtaAtSetFrCnf, 0, sizeof(MTA_AT_SET_FR_CNF_STRU));

    /* �����ǰ��ʱ������������ֱ�ӷ���ʧ�� */
    if (TAF_MTA_TIMER_STATUS_STOP != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_FR_CNF))
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstAtMtaMsg->stAppCtrl,
                         ID_MTA_AT_SET_FR_CNF,
                         sizeof(MTA_AT_SET_FR_CNF_STRU),
                         (VOS_UINT8*)&stMtaAtSetFrCnf );
        return;
    }

    /* �յ�at��Set Fr�������󣬷�ID_MTA_LRRC_SET_FR_REQ��Ϣ֪ͨLRRC */
    ulResult = TAF_MTA_SndLrrcSetFrReqMsg(pstMsg);

    /* ��Ϣ����ʧ�ܣ���AT�ظ�ERROR */
    if (VOS_OK != ulResult)
    {
        stMtaAtSetFrCnf.enRslt = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstAtMtaMsg->stAppCtrl,
                          ID_MTA_AT_SET_FR_CNF,
                          sizeof(MTA_AT_SET_FR_CNF_STRU),
                          (VOS_UINT8*)&stMtaAtSetFrCnf );
        return;
    }

    /* ����������ʱ�� */
    if (TAF_MTA_TIMER_START_FAILURE == TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_SET_FR_CNF, TI_TAF_MTA_WAIT_SET_FR_CNF_TIMER_LEN))
    {
        MTA_WARNING_LOG("TAF_MMA_RcvAtSetFrReq: WARNING: Start Timer failed!");
    }

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF,
                                     (VOS_UINT8*)&pstAtMtaMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvLrrcSetFrCnf
 ��������  : MTA�յ�LRRC������ID_MTA_AT_SET_FR_CNF��Ϣ������
 �������  : pstMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : wx270776
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcSetFrCnf(
    VOS_VOID                           *pstMsg
)
{
    LRRC_MTA_SET_FR_CNF_STRU           *pstLrrcMtaSetFrCnf = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* ��ʼ���ֲ����� */
    pstLrrcMtaSetFrCnf                = (LRRC_MTA_SET_FR_CNF_STRU*)pstMsg;
    PS_MEM_SET(&stMtaAtSetFrCnf, 0, sizeof(MTA_AT_SET_FR_CNF_STRU));

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_FR_CNF))
    {
        MTA_WARNING_LOG("TAF_MMA_RcvLrrcSetFrCnf: WARNING: Timer was already stop!");

        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_SET_FR_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* �����Ϣ�� */
    if ( MTA_RRC_RESULT_NO_ERROR == pstLrrcMtaSetFrCnf->enRslt )
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtSetFrCnf.enRslt        = MTA_AT_RESULT_ERROR;
    }

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_SET_FR_CNF,
                      sizeof(MTA_AT_SET_FR_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtSetFrCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired
 ��������  : MTA�յ���ʱ����ʱ��Ϣ������
 �������  : pstMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��01��
    ��    ��   : wx270776
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetFrCnfExpired(
    VOS_VOID                           *pstMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_SET_FR_CNF_STRU              stMtaAtSetFrCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stMtaAtSetFrCnf.enRslt = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_SET_FR_CNF,
                     sizeof(stMtaAtSetFrCnf),
                     (VOS_UINT8*)&stMtaAtSetFrCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_FR_CNF);

    return;

}

#endif
VOS_UINT32 TAF_MTA_SndGasSetFreqLockReq(
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU   *pstSetGFreqLockReq
)
{
    MTA_GRR_FREQLOCK_SET_REQ_STRU      *pstSetGFreqReq = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_GRR_FREQLOCK_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSetGFreqReq        = (MTA_GRR_FREQLOCK_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstSetGFreqReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasSetFreqLockReq: Alloc msg fail!");
        return VOS_ERR;
    }

    pstSetGFreqReq->stMsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pstSetGFreqReq->stMsgHeader.ulMsgName       = ID_MTA_GRR_FREQLOCK_SET_REQ;
    pstSetGFreqReq->enLockFlg                   = pstSetGFreqLockReq->enableFlag;
    pstSetGFreqReq->usFreq                      = pstSetGFreqLockReq->usFreq;
    pstSetGFreqReq->aucReserved[0]              = 0;
    pstSetGFreqReq->aucReserved[1]              = 0;
    pstSetGFreqReq->aucReserved[2]              = 0;
    pstSetGFreqReq->enBand                      = (MTA_RRC_GSM_BAND_ENUM_UINT16)pstSetGFreqLockReq->enBand;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstSetGFreqReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasSetFreqLockReq: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID TAF_MTA_RcvAtSetGFreqLockReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq           = VOS_NULL_PTR;
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU   *pstSetGFreqLockReq  = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stSetGFreqLockCnf;
    VOS_UINT32                          ulResult;

    pstSetReq                   = (AT_MTA_MSG_STRU *)pMsg;
    pstSetGFreqLockReq          = (AT_MTA_SET_GSM_FREQLOCK_REQ_STRU *)(pstSetReq->aucContent);
    stSetGFreqLockCnf.enResult  = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                         sizeof(stSetGFreqLockCnf),
                         (VOS_UINT8*)&stSetGFreqLockCnf);
        return;
    }

    ulResult = TAF_MTA_SndGasSetFreqLockReq(pstSetGFreqLockReq);

    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                         sizeof(stSetGFreqLockCnf),
                         (VOS_UINT8*)&stSetGFreqLockCnf);
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,
                       TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}


VOS_VOID TAF_MTA_RcvGasSetFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    GRR_MTA_FREQLOCK_SET_CNF_STRU      *pstSetCnf       = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stMtaAtSetCnf;

    /* ��ʼ����Ϣ���� */
    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasSetFreqLockCnf:Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasSetFreqLockCnf: get command buffer failed!");
        return;
    }

    /* ȡ��֮ǰ�������Ƶ��Ϣ */
    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    /* ��ȡ���ý�����ϱ�AT��� */
    pstSetCnf    = (GRR_MTA_FREQLOCK_SET_CNF_STRU *)pMsg;

    if (MTA_RRC_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        stMtaAtSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstAppCtrl,
                     ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);
    return;
}


VOS_VOID TAF_MTA_RcvTiWaitGasSetGFreqLockExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                    *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU    stSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstAppCtrl,
                     ID_MTA_AT_SET_GSM_FREQLOCK_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_SET_GSM_FREQLOCK_CNF);

    return;
}
VOS_VOID TAF_MTA_RcvGphyXpassInfoInd(VOS_VOID *pMsg)
{
    GPHY_MTA_XPASS_INFO_IND_STRU       *pstGphyXpassInfo = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU          stXpassInfoInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulChkCurcRptFlg;

    PS_MEM_SET(&stXpassInfoInd, 0x0, sizeof(stXpassInfoInd));

    /* ��д��Ϣͷ���ϱ�����Ϊ�㲥�¼� */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    pstGphyXpassInfo = (GPHY_MTA_XPASS_INFO_IND_STRU *)pMsg;

    stXpassInfoInd.enWphyXpassMode = PHY_MTA_WPHY_HIGHWAY_MODE_DISABLE;
    stXpassInfoInd.enGphyXpassMode = pstGphyXpassInfo->enXpassMode;

    /* �жϵ�ǰ�����ϱ��Ƿ�ر� */
    ulChkCurcRptFlg = TAF_MTA_GetXpassInfoRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_XPASS_INFO_IND,
                     sizeof(stXpassInfoInd),
                     (VOS_UINT8*)&stXpassInfoInd );

    return;
}


VOS_VOID TAF_MTA_RcvWphyXpassInfoInd(VOS_VOID *pMsg)
{
    WPHY_MTA_XPASS_INFO_IND_STRU       *pstWphyXpassInfo = VOS_NULL_PTR;
    MTA_AT_XPASS_INFO_IND_STRU          stXpassInfoInd;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulChkCurcRptFlg;

    PS_MEM_SET(&stXpassInfoInd, 0x0, sizeof(stXpassInfoInd));

    /* ��д��Ϣͷ���ϱ�����Ϊ�㲥�¼� */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    pstWphyXpassInfo = (WPHY_MTA_XPASS_INFO_IND_STRU *)pMsg;

    stXpassInfoInd.enGphyXpassMode = PHY_MTA_GPHY_XPASS_MODE_DISABLE;
    stXpassInfoInd.enWphyXpassMode = pstWphyXpassInfo->enHighwayMode;

    /* �жϵ�ǰ�����ϱ��Ƿ�ر� */
    ulChkCurcRptFlg = TAF_MTA_GetXpassInfoRptCtl();
    if (VOS_FALSE == ulChkCurcRptFlg)
    {
        return;
    }

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_XPASS_INFO_IND,
                     sizeof(stXpassInfoInd),
                     (VOS_UINT8*)&stXpassInfoInd );

    return;
}


VOS_UINT32 TAF_MTA_GetXpassInfoRptCtl(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl      = VOS_NULL_PTR;
    VOS_UINT32                          ulChkCurcRptFlg;

    /* �жϵ�ǰ�����ϱ��Ƿ�ر� */
    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();
    ulChkCurcRptFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_XPASSINFO);

    return ulChkCurcRptFlg;
}
VOS_VOID TAF_MTA_RcvAtSetFemctrlReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    MTA_AT_SET_FEMCTRL_CNF_STRU         stSetCnf;
    AT_MTA_SET_FEMCTRL_REQ_STRU        *pstFemctrl;
    VOS_INT32                          lResult;

    pstSetReq          = (AT_MTA_MSG_STRU *)pMsg;
    lResult           = MTA_AT_RESULT_ERROR;
    pstFemctrl         = (AT_MTA_SET_FEMCTRL_REQ_STRU *)pstSetReq->aucContent;
    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    /* ���õ��������gpio��mipi���� */
    lResult = mdrv_fem_ioctrl((FEMIO_CTRL_TYPE)pstFemctrl->ulCtrlType, pstFemctrl->ulPara1, pstFemctrl->ulPara2, pstFemctrl->ulPara3);

    if (lResult == VOS_OK)
    {
        stSetCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_AT_MTA_SET_FEMCTRL_CNF,
                     sizeof(stSetCnf),
                     (VOS_UINT8*)&stSetCnf );

    return;
}
/*lint +e958*/

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetLteLowPowerConsumptionReqMsg
 ��������  : ��lrrc�������õ͹�����Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg(
    VOS_UINT8                           ucLowPowerConsumption
)
{
    MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU    *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_LOW_POWER_CONSUMPTION_SET_REQ;
    pstMtaLrrcSetReq->bLowPowerFlg                  = (VOS_BOOL)ucLowPowerConsumption;

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetsLowPowerConsumptionReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtLteLowPowerConsumptionSetReq
 ��������  : MTA����^LTELOWPOWER������õ͹�������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtLteLowPowerConsumptionSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                                  stSetCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }


    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetLowPowerConsumptionReqMsg(pstSetReq->aucContent[0]);

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_LOW_POWER_CONSUMPTION_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf
 ��������  : MTA�յ�LRRC���õ͹��Ľ��
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcLowPowerConsumptionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_LOW_POWER_CONSUMPTION_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption
 ��������  : ���õ͹��ĳ�ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetLowPowerConsumption(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_LTE_LOW_POWER_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_LOW_POWER_CONSUMPTION_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetIsmCoexReqMsg
 ��������  : ��lrrc������������^SIMCOEX
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcSetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU  *pstCoexPara
)
{
    MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU            *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;
    VOS_UINT32                                      ulCoexParaPtr;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(pstCoexPara->astCoexPara) + sizeof(MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH - 4;
    pstMtaLrrcSetReq      = (MTA_LRRC_LTE_WIFI_COEX_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetIsmCoexReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_LTE_WIFI_COEX_SET_REQ;
    pstMtaLrrcSetReq->usCoexParaNum                 = pstCoexPara->usCoexParaNum;
    pstMtaLrrcSetReq->usCoexParaSize                = pstCoexPara->usCoexParaSize;
    ulCoexParaPtr                                   = (VOS_UINT32)pstMtaLrrcSetReq->aucCoexPara;
    PS_MEM_CPY((VOS_UINT8 *)ulCoexParaPtr, pstCoexPara->astCoexPara, sizeof(pstCoexPara->astCoexPara));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetIsmCoexReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcIsmCoexSetCnf
 ��������  : MTA�յ�LRRC ^ISMCOEX���ý��
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcIsmCoexSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU            *pstRcvLrrcCnf           = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                                *pstMsg                  = VOS_NULL_PTR;
    AT_MTA_COEX_PARA_STRU                          *pstCoexPara             = VOS_NULL_PTR;
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU              *pstBufferCoex           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;
    VOS_UINT32                                      i;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcIsmCoexSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcIsmCoexSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_LTE_WIFI_COEX_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    pstMsg                  = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    /* ����IsmCoex�б� */
    if (VOS_OK == stSndAtCnf.enResult)
    {
        pstCoexPara     = TAF_MTA_GetIsmCoexAddr();
        pstBufferCoex   = (AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstMsg->aucContent;
        for ( i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
        {
            PS_MEM_CPY(pstCoexPara + i, &pstBufferCoex->astCoexPara[i], sizeof(TAF_MTA_COEX_PARA_STRU));
        }
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtIsmCoexQryReq
 ��������  : MTA����^ISMCOEX?
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtIsmCoexQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq               = VOS_NULL_PTR;
    TAF_MTA_COEX_PARA_STRU             *pstCoexPara             = VOS_NULL_PTR;
    MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU   stCoexCnf;
    VOS_UINT32                          i;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    pstCoexPara = TAF_MTA_GetIsmCoexAddr();
    PS_MEM_SET(&stCoexCnf, 0x00, sizeof(MTA_AT_LTE_WIFI_COEX_QRY_CNF_STRU));

    for (i = 0; i < TAF_MTA_ISMCOEX_BANDWIDTH_NUM; i++)
    {
        PS_MEM_CPY(&stCoexCnf.astCoexPara[i], pstCoexPara + i, sizeof(TAF_MTA_COEX_PARA_STRU));
    }

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_QRY_CNF,
                     sizeof(stCoexCnf),
                     (VOS_UINT8*)&stCoexCnf );

    return;
}
#endif
/* Added by w00316404 for eMBMS project, 2015-5-22, end */

/* Added by lwx277467 for Transmission Mode, 2015/7/30, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtTransModeQryReq
 ��������  : mta�յ�ID_AT_MTA_TRANSMODE_QRY_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 ��    ��   : 2015��7��30��
 ��    ��   : lwx277467
 �޸�����   : ^TRANSMODE��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtTransModeQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstTransModeQryReq      = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stTransModeQryCnf;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;

    pstTransModeQryReq      = (AT_MTA_MSG_STRU *)pMsg;
    enRatType               = TAF_SDC_GetSysMode();
    PS_MEM_SET(&stTransModeQryCnf, 0x0, sizeof(stTransModeQryCnf));

    /* ��ѯ�Ƿ���LTEģʽ�£����򷵻�ʧ��*/
    if (TAF_SDC_SYS_MODE_LTE != enRatType)
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );

        return;
    }

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    TAF_MTA_SndLrrcTransModeQryReq();

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF, TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,
                                     (VOS_UINT8*)&pstTransModeQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
#else
    stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

    TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                  ID_MTA_AT_TRANSMODE_QRY_CNF,
                  sizeof(stTransModeQryCnf),
                  (VOS_UINT8*)&stTransModeQryCnf );
#endif
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcTransModeQryReq
 ��������  : MTA����ϢID_MTA_LRRC_TRANSMODE_QRY_REQ��LRRC��ѯLTE����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����^TRANSMODE����
*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcTransModeQryReq(VOS_VOID)
{
    VOS_UINT32                           ulLength;
    MTA_LRRC_TRANSMODE_QRY_REQ_STRU     *pstTransModeQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength               = sizeof(MTA_LRRC_TRANSMODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstTransModeQryReq     = (MTA_LRRC_TRANSMODE_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstTransModeQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstTransModeQryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstTransModeQryReq->stMsgHeader.ulReceiverPid     = PS_PID_ERRC;
    pstTransModeQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_TRANSMODE_QRY_REQ;

    PS_MEM_SET(pstTransModeQryReq->aucReserved, 0, sizeof(pstTransModeQryReq->aucReserved));

    /* ������Ϣ��LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstTransModeQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcTransModeQryCnf
 ��������  : MTA�յ�LTE����㴫��ģʽ��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����^TRANSMODE����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcTransModeQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf          = VOS_NULL_PTR;
    LRRC_MTA_TRANSMODE_QRY_CNF_STRU     *pstTransModeQryCnf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU        stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x00, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    pstTransModeQryCnf = (LRRC_MTA_TRANSMODE_QRY_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: No Buffer!");
        return;
    }

    if (MTA_RRC_RESULT_NO_ERROR != pstTransModeQryCnf->enResult)
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_NO_ERROR;
        stMtaAtTransModeQryCnf.ucTransMode = pstTransModeQryCnf->ucTransMode;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtTransModeQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcTransModeQryExpired
 ��������  : ��ѯLTE����ģʽ��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��08��04��
    ��    ��   : lwx277467
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcTransModeQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLrrcTransModeQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x0, sizeof(stMtaAtTransModeQryCnf));

    stMtaAtTransModeQryCnf.enResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_TRANSMODE_QRY_CNF,
                     sizeof(stMtaAtTransModeQryCnf),
                     (VOS_UINT8*)&stMtaAtTransModeQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif
/* Added by lwx277467 for Transmission Mode, 2015/7/30, end */

/* Added by lwx277467 for UE Mode, 2015/9/7, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtUECenterSetReq
 ��������  : MTA�յ�ID_AT_MTA_UECENTER_SET_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 ��    ��   : 2015��7��30��
 ��    ��   : lwx277467
 �޸�����   : +CEUS��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtUECenterSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstUECenterSetReq      = VOS_NULL_PTR;
    AT_MTA_SET_UE_CENTER_REQ_STRU      *pstAtMtaUECenterSetReq = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU       stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    pstUECenterSetReq      = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaUECenterSetReq = (AT_MTA_SET_UE_CENTER_REQ_STRU *)(pstUECenterSetReq->aucContent);

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF))
    {
        stMtaAtUECenterSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstUECenterSetReq->stAppCtrl,
                        ID_MTA_AT_UE_CENTER_SET_CNF,
                        sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                        (VOS_UINT8*)&stMtaAtUECenterSetCnf);
        return;
    }

    TAF_MTA_SndLnasUECenterSetReq(pstAtMtaUECenterSetReq);

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF, TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF,
                                     (VOS_UINT8*)&pstUECenterSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLnasUECenterSetReq
 ��������  : MTA����Ϣ��LNAS����UEģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����+CEUS����
*****************************************************************************/
VOS_VOID TAF_MTA_SndLnasUECenterSetReq(AT_MTA_SET_UE_CENTER_REQ_STRU *pstAtMtaUECenterSetReq)
{
    MTA_LNAS_SET_UE_CENTER_REQ_STRU     *pstUECenterSetReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstUECenterSetReq = (MTA_LNAS_SET_UE_CENTER_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LNAS_SET_UE_CENTER_REQ_STRU));
    if (VOS_NULL_PTR == pstUECenterSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq: Alloc msg fail!");
        return;
    }

    TAF_MTA_CLR_MSG_ENTITY(pstUECenterSetReq);

    /* ������Ϣ�ṹ�� */
    pstUECenterSetReq->enUeCenter = pstAtMtaUECenterSetReq->enUeCenter;
    TAF_MTA_CFG_MSG_HDR(pstUECenterSetReq,PS_PID_MM,ID_MTA_LNAS_SET_UE_CENTER_REQ);

    /* ������Ϣ��LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstUECenterSetReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLnasUECenterSetCnf
 ��������  : MTA�յ�LNAS����UEģʽ��Ϣ�ظ�������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����+CEUS����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLnasUECenterSetCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf              = VOS_NULL_PTR;
    LNAS_MTA_SET_UE_CENTER_CNF_STRU     *pstUECenterSetCnf      = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU        stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    pstUECenterSetCnf = (LNAS_MTA_SET_UE_CENTER_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLnasUECenterSetCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLnasUECenterSetCnf: No Buffer!");
        return;
    }

    if (MTA_LMM_RESULT_NO_ERROR != pstUECenterSetCnf->ulRslt)
    {
        stMtaAtUECenterSetCnf.enResult= MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtUECenterSetCnf.enResult= MTA_AT_RESULT_NO_ERROR;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_UE_CENTER_SET_CNF,
                      sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterSetCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLnasUECenterSetExpired
 ��������  : ����UEģʽ��ʱ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��08��04��
    ��    ��   : lwx277467
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterSetExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_SET_UE_CENTER_CNF_STRU       stMtaAtUECenterSetCnf;

    PS_MEM_SET(&stMtaAtUECenterSetCnf, 0x0, sizeof(stMtaAtUECenterSetCnf));

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLnasUECenterSetExpired: get command buffer failed!");
        return;
    }

    stMtaAtUECenterSetCnf.enResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_UE_CENTER_SET_CNF,
                     sizeof(MTA_AT_SET_UE_CENTER_CNF_STRU),
                     (VOS_UINT8*)&stMtaAtUECenterSetCnf);


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtUECenterQryReq
 ��������  : MTA�յ�ID_AT_MTA_UECENTER_QRY_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 ��    ��   : 2015��7��30��
 ��    ��   : lwx277467
 �޸�����   : +CEUS��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtUECenterQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstUECenterQryReq = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    pstUECenterQryReq      = (AT_MTA_MSG_STRU *)pMsg;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF))
    {
        stMtaAtUECenterQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstUECenterQryReq->stAppCtrl,
                      ID_MTA_AT_UE_CENTER_QRY_CNF,
                      sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterQryCnf);
        return;
    }

    TAF_MTA_SndLnasUECenterQryReq();

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF, TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF,
                                     (VOS_UINT8*)&pstUECenterQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLnasUECenterSetReq
 ��������  : MTA����Ϣ��LNAS��ѯUEģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����+CEUS����
*****************************************************************************/
VOS_VOID TAF_MTA_SndLnasUECenterQryReq(VOS_VOID)
{
    MTA_LNAS_QRY_UE_CENTER_REQ_STRU     *pstUECenterQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstUECenterQryReq = (MTA_LNAS_QRY_UE_CENTER_REQ_STRU *)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LNAS_QRY_UE_CENTER_REQ_STRU));

    if (VOS_NULL_PTR == pstUECenterQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterQryReq: Alloc msg fail!");
        return;
    }

    TAF_MTA_CLR_MSG_ENTITY(pstUECenterQryReq);

    /* ������Ϣ�ṹ�� */
    TAF_MTA_CFG_MSG_HDR(pstUECenterQryReq,PS_PID_MM,ID_MTA_LNAS_QRY_UE_CENTER_REQ);

    /* ������Ϣ��LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstUECenterQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLnasUECenterSetReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLnasUECenterSetCnf
 ��������  : MTA�յ�LNAS����UEģʽ��Ϣ�ظ�������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����+CEUS����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLnasUECenterQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf         = VOS_NULL_PTR;
    LNAS_MTA_QRY_UE_CENTER_CNF_STRU     *pstUECenterQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    pstUECenterQryCnf = (LNAS_MTA_QRY_UE_CENTER_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLnasUECenterSetCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLnasUECenterSetCnf: No Buffer!");
        return;
    }

    if (MTA_LMM_RESULT_NO_ERROR != pstUECenterQryCnf->enResult)
    {
        stMtaAtUECenterQryCnf.enResult      = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtUECenterQryCnf.enResult      = MTA_AT_RESULT_NO_ERROR;
        stMtaAtUECenterQryCnf.enUeCenter    = pstUECenterQryCnf->enUeCenter;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_UE_CENTER_QRY_CNF,
                      sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtUECenterQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLnasUECenterSetExpired
 ��������  : ����UEģʽ��ʱ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��08��04��
    ��    ��   : lwx277467
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLnasUECenterQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_QRY_UE_CENTER_CNF_STRU       stMtaAtUECenterQryCnf;

    PS_MEM_SET(&stMtaAtUECenterQryCnf, 0x0, sizeof(stMtaAtUECenterQryCnf));

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_UE_CENTER_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLnasUECenterSetExpired: get command buffer failed!");
        return;
    }

    stMtaAtUECenterQryCnf.enResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_UE_CENTER_QRY_CNF,
                     sizeof(MTA_AT_QRY_UE_CENTER_CNF_STRU),
                     (VOS_UINT8*)&stMtaAtUECenterQryCnf);


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
/* Added by lwx277467 for UE Mode, 2015/9/7, end */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

