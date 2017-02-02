/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaMbms.c
  �� �� ��   : ����
  ��    ��   : w00316404
  ��������   : 2015��5��22��
  ����޸�   :
  ��������   : MTAģ�鴦��MBMS���Թ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : eMBMS��Ŀ����

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaMbms.h"
#include "TafSdcLib.h"
#include "TafMtaComm.h"
#include "TafMtaMain.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MBMS_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#if((FEATURE_ON == FEATURE_LTE) && (FEATURE_ON == FEATURE_LTE_MBMS))
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg
 ��������  : ��lrrc��������MBMS����������Ϣ
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg(
    VOS_UINT8                           ucMBMSServiceOption
)
{
    MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU      *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_SERVICE_OPTION_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrSetCellsrhReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_SERVICE_OPTION_REQ;
    pstMtaLrrcSetReq->enOption                      = ucMBMSServiceOption;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSServiceOptionSetReq
 ��������  : MTA����^MBMSCMD="MBMS_SERVICE_ENABLER",<param1>�������MBMS��������
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
VOS_VOID TAF_MTA_RcvAtMBMSServiceOptionSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult= VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }
    
    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetMBMSServiceOptionReqMsg(pstSetReq->aucContent[0]);

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_OPTION_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf
 ��������  : MTA�յ�LRRC����MBMS�������Խ��
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
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU      *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceOptionSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_SERVICE_OPTION_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption
 ��������  : ����MBMS�������Գ�ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceOption(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_OPTION_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_OPTION_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg
 ��������  : ��lrrc��������MBMS����״̬��Ϣ
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg(
    AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU      *pstMBMSServiceState
)
{
    MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU       *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_SERVICE_STATE_SET_REQ;
    pstMtaLrrcSetReq->enStateSet                    = pstMBMSServiceState->enStateSet;
    pstMtaLrrcSetReq->ulAreaId                      = pstMBMSServiceState->ulAreaId;
    pstMtaLrrcSetReq->stTMGI.ulMbmsSerId            = pstMBMSServiceState->stTMGI.ulMbmsSerId;
    pstMtaLrrcSetReq->stTMGI.stPlmnId.ulMcc         = pstMBMSServiceState->stTMGI.stPlmnId.ulMcc;
    pstMtaLrrcSetReq->stTMGI.stPlmnId.ulMnc         = pstMBMSServiceState->stTMGI.stPlmnId.ulMnc;

    TAF_SDC_ConvertPlmnId2NasStyle(&pstMtaLrrcSetReq->stTMGI.stPlmnId);

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSServiceStateSetReq
 ��������  : MTA����^MBMSCMD="ACTIVATE",<param1>,<param2>
                    ^MBMSCMD="DEACTIVATE",<param1>,<param2>
                    ^MBMSCMD="DEACTIVATE_ALL"
             �������MBMS����״̬
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
VOS_VOID TAF_MTA_RcvAtMBMSServiceStateSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetMBMSServiceStateReqMsg((AT_MTA_MBMS_SERVICE_STATE_SET_REQ_STRU *)pstSetReq->aucContent);

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_MBMS_SERVICE_STATE_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSServiceStateSetCnf
 ��������  : MTA�յ�LRRC����MBMS����״̬���
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
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceStateSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU   *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceStateSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSServiceStateSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_SERVICE_STATE_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState
 ��������  : ����MBMS����״̬��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSServiceState(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_STATE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SERVICE_STATE_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg
 ��������  : ��lrrc��������MBMS�㲥ģʽ��Ϣ
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg(
    VOS_UINT8                           ucMBMSCastMode
)
{
    MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU      *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_PREFERENCE_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_PREFERENCE_SET_REQ;
    pstMtaLrrcSetReq->enCastMode                    = ucMBMSCastMode;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg: Send msg fail!");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSPreferenceSetReq
 ��������  : MTA����^MBMSCMD="MBMS_PREFERENCE",<param1>�������MBMS�㲥ģʽ
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
VOS_VOID TAF_MTA_RcvAtMBMSPreferenceSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg(pstSetReq->aucContent[0]);

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_MBMS_PREFERENCE_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSPreferenceSetCnf
 ��������  : MTA�յ�LRRC����MBMS�㲥ģʽ���
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
VOS_VOID TAF_MTA_RcvLrrcMBMSPreferenceSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU      *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSPreferenceSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSPreferenceSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_PREFERENCE_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetMBMSPreference
 ��������  : ����MBMS�㲥ģʽ��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSPreference(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_PREFERENCE_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_PREFERENCE_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetMBMSPreferenceReqMsg
 ��������  : ��lrrc���Ͳ�ѯSIB16����ʱ����Ϣ
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
VOS_VOID TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg(VOS_VOID)
{
    MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU   *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_SIB16_NETWORK_TIME_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg: Send msg fail!");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSIB16NetworkTimeQryReq
 ��������  : MTA����^MBMSCMD="SIB16_GET_NETWORK_TIME"����ѯSIB16����ʱ��
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
VOS_VOID TAF_MTA_RcvAtSIB16NetworkTimeQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU             stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;
    
    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode()) 
    {
        ulResult  = VOS_ERR;
    }

    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcQrySIB16NetworkTimeReqMsg();

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
                       TI_TAF_MTA_WAIT_QRY_MBMS_SIB16_NETWORK_TIME_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf
 ��������  : MTA�յ�LRRC��ѯSIB16����ʱ����
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
VOS_VOID TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU   *pstRcvLrrcCnf           = VOS_NULL_PTR;
    VOS_UINT64                                 *pullUTC;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSSIB16NetworkTimeQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_SIB16_NETWORK_TIME_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    pullUTC                 = (VOS_UINT64 *)stSndAtCnf.aulUTC;
    *pullUTC                = pstRcvLrrcCnf->ullUTC;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime
 ��������  : ��ѯSIB16����ʱ�䳬ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQrySIB16NetworkTime(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_SIB16_NETWORK_TIME_QRY_CNF_STRU stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_SIB16_NETWORK_TIME_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_SIB16_NETWORK_TIME_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg
 ��������  : ��lrrc���Ͳ�ѯBSSI�ź�ǿ����Ϣ
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
VOS_VOID TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg(VOS_VOID)
{
    MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU    *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_BSSI_SIGNAL_LEVEL_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtBSSISignalLevelQryReq
 ��������  : MTA����^MBMSCMD="BSSI_SIGNAL_LEVEL"����ѯBSSI�ź�ǿ��
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
VOS_VOID TAF_MTA_RcvAtBSSISignalLevelQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU              stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;
    
    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode()) 
    {
        ulResult  = VOS_ERR;
    }
    
    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcQryBSSISignalLevelReqMsg();

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
                       TI_TAF_MTA_WAIT_QRY_MBMS_BSSI_SIGNAL_LEVEL_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf
 ��������  : MTA�յ�LRRC��ѯBSSI�ź�ǿ�Ƚ��
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
VOS_VOID TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU  stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSBSSISignalLevelQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ucBSSILevel  = pstRcvLrrcCnf->ucBSSILevel;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel
 ��������  : ��ѯBSSI�ź�ǿ�ȳ�ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryBSSISignalLevel(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF_STRU  stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_BSSI_SIGNAL_LEVEL_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_BSSI_SIGNAL_LEVEL_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcQryNetworkInfoReqMsg
 ��������  : ��lrrc���Ͳ�ѯ������Ϣ��Ϣ
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
VOS_VOID TAF_MTA_SndLrrcQryNetworkInfoReqMsg(VOS_VOID)
{
    MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU         *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_NETWORK_INFO_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryNetworkInfoReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_NETWORK_INFO_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryNetworkInfoReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtNetworkInfoQryReq
 ��������  : MTA����^MBMSCMD="NETWORK_INFORMATION"����ѯ������Ϣ
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
VOS_VOID TAF_MTA_RcvAtNetworkInfoQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU                   stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;
    
    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode()) 
    {
        ulResult  = VOS_ERR;
    }
    
    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcQryNetworkInfoReqMsg();

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
                       TI_TAF_MTA_WAIT_QRY_MBMS_NETWORK_INFO_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf
 ��������  : MTA�յ�LRRC��ѯ������Ϣ���
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
VOS_VOID TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU         *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU       stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSNetworkInfoQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_NETWORK_INFO_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ulCellId     = pstRcvLrrcCnf->ulCellId;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcQryNetworkInfo
 ��������  : ��ѯ������Ϣ��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryNetworkInfo(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_NETWORK_INFO_QRY_CNF_STRU       stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_NETWORK_INFO_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_NETWORK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcQryEMBMSStatusReqMsg
 ��������  : ��lrrc���Ͳ�ѯEMBMS����״̬��Ϣ
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
VOS_VOID TAF_MTA_SndLrrcQryEMBMSStatusReqMsg(VOS_VOID)
{
    MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU         *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_EMBMS_STATUS_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryEMBMSStatusReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_EMBMS_STATUS_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryEMBMSStatusReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtEMBMSStatusQryReq
 ��������  : MTA����^MBMSCMD="MODEM_STATUS"����ѯeMBMS����״̬
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
VOS_VOID TAF_MTA_RcvAtEMBMSStatusQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU                        stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;
    
    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode()) 
    {
        ulResult  = VOS_ERR;
    }
    
    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcQryEMBMSStatusReqMsg();

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
                       TI_TAF_MTA_WAIT_QRY_EMBMS_STATUS_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcEMBMSStatusQryCnf
 ��������  : MTA�յ�LRRC��ѯEMBMS����״̬���
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
VOS_VOID TAF_MTA_RcvLrrcEMBMSStatusQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU         *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU            stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcEMBMSStatusQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcEMBMSStatusQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_EMBMS_STATUS_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;
    stSndAtCnf.enStatus     = pstRcvLrrcCnf->enStatus;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus
 ��������  : ��ѯEMBMS����״̬��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryEMBMSStatus(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_EMBMS_STATUS_QRY_CNF_STRU            stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_EMBMS_STATUS_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_EMBMS_STATUS_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg
 ��������  : ��lrrc��������MBMS�����ϱ�������Ϣ
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
VOS_VOID TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg(
    VOS_UINT8                           ucMBMSUnsolicitedCfg
)
{
    MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_UNSOLICITED_CFG_SET_REQ;
    pstMtaLrrcSetReq->enCfg                         = ucMBMSUnsolicitedCfg;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcSetReq->aucReserved, 0, sizeof(pstMtaLrrcSetReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq
 ��������  : MTA����^MBMSEV�������MBMS�����ϱ�����
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
VOS_VOID TAF_MTA_RcvAtMBMSUnsolicitedCfgSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetMBMSUnsolicitedCfgReqMsg(pstSetReq->aucContent[0]);

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_MBMS_UNSOLICITED_CFG_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf
 ��������  : MTA�յ�LRRC����MBMS�����ϱ����ý��
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
VOS_VOID TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSUnsolicitedCfgSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_MBMS_UNSOLICITED_CFG_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg
 ��������  : ����MBMS�����ϱ����ó�ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetMBMSUnsolicitedCfg(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_UNSOLICITED_CFG_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_UNSOLICITED_CFG_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSServiceEventInd
 ��������  : mta�յ�lrrc ID_LRRC_MTA_MBMS_SERVICE_EVENT_IND��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcMBMSServiceEventInd(
    VOS_VOID                           *pMsg
)
{
    LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU               *pstLrrcMtaInd = VOS_NULL_PTR;
    MTA_AT_MBMS_SERVICE_EVENT_IND_STRU                  stMtaAtInd;
    AT_APPCTRL_STRU                                     stAppCtrl;

    /* ��д�����ϱ�����Ϣ���� */
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(stMtaAtInd));
    pstLrrcMtaInd           = (LRRC_MTA_MBMS_SERVICE_EVENT_IND_STRU *)pMsg;
    stMtaAtInd.enEvent      = pstLrrcMtaInd->enEvent;

    /* ��д��Ϣͷ���ϱ�����Ϊ�㲥�¼� */
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId     = MTA_INVALID_TAB_INDEX;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_MBMS_SERVICE_EVENT_IND,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetInterestListReqMsg
 ��������  : ��lrrc��������Interest��Ϣ
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
VOS_VOID TAF_MTA_SndLrrcSetInterestListReqMsg(
    AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU           *pstMBMSInterestList
)
{
    MTA_LRRC_INTEREST_LIST_SET_REQ_STRU            *pstMtaLrrcSetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_INTEREST_LIST_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcSetReq      = (MTA_LRRC_INTEREST_LIST_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcSetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetInterestListReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcSetReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcSetReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_INTEREST_LIST_SET_REQ;
    pstMtaLrrcSetReq->bMbmsPriority                 = (VOS_BOOL)pstMBMSInterestList->enMbmsPriority;
    PS_MEM_CPY(pstMtaLrrcSetReq->aulFreqList, pstMBMSInterestList->aulFreqList, sizeof(pstMtaLrrcSetReq->aulFreqList));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcSetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetInterestListReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSInterestListSetReq
 ��������  : MTA����^MBMSINTERESTLIST�������INTERESTLIST����
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
VOS_VOID TAF_MTA_RcvAtMBMSInterestListSetReq(
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
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_INTEREST_LIST_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }
    
    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcSetInterestListReqMsg((AT_MTA_MBMS_INTERESTLIST_SET_REQ_STRU *)pstSetReq->aucContent);

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_MBMS_INTERESTLIST_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcInterestListSetCnf
 ��������  : MTA�յ�LRRC����Interest List���
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
VOS_VOID TAF_MTA_RcvLrrcInterestListSetCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_INTEREST_LIST_SET_CNF_STRU            *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcInterestListSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcInterestListSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf           = (LRRC_MTA_INTEREST_LIST_SET_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult     = pstRcvLrrcCnf->enResult;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_INTEREST_LIST_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcSetInterestList
 ��������  : ����Interest List��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcSetInterestList(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_INTEREST_LIST_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_INTERESTLIST_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcQryAvlServiceListReqMsg
 ��������  : ��lrrc���Ͳ�ѯMBMS���÷����б���Ϣ
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
VOS_VOID TAF_MTA_SndLrrcQryAvlServiceListReqMsg(VOS_VOID)
{
    MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU    *pstMtaLrrcQryReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaLrrcQryReq      = (MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLrrcQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryAvlServiceListReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(&pstMtaLrrcQryReq->stMsgHeader, PS_PID_ERRC);
    pstMtaLrrcQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_MBMS_AVL_SERVICE_LIST_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_SET(pstMtaLrrcQryReq->aucReserved, 0, sizeof(pstMtaLrrcQryReq->aucReserved));

    /* ������Ϣ��LRRC */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLrrcQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcQryAvlServiceListReqMsg: Send msg fail!");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtMBMSAvlServiceListQryReq
 ��������  : MTA����^MBMSCMD?
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
VOS_VOID TAF_MTA_RcvAtMBMSAvlServiceListQryReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU               stQryCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;
    
    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode()) 
    {
        ulResult  = VOS_ERR;
    }
    
    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨas */
    TAF_MTA_SndLrrcQryAvlServiceListReqMsg();

    /* ����������ʱ�� */
    TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                       TI_TAF_MTA_WAIT_QRY_MBMS_AVL_SERVICE_LIST_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf
 ��������  : MTA�յ�LRRC��ѯMBMS���÷�����Ϣ���
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
VOS_VOID TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf(
    VOS_VOID                           *pLrrcCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU    *pstRcvLrrcCnf           = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU       stSndAtCnf;
    VOS_UINT32                                      ulAvlServiceListNum;

    PS_MEM_SET(&stSndAtCnf, 0x0, sizeof(stSndAtCnf));

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcMBMSAvlServiceListQryCnf: get command buffer failed!");
        return;
    }

    pstRcvLrrcCnf               = (LRRC_MTA_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU *)pLrrcCnfMsg;
    stSndAtCnf.enResult         = pstRcvLrrcCnf->enResult;
    stSndAtCnf.ulAvlServiceNum  = pstRcvLrrcCnf->ulAvlServiceNum;

    if(0 != stSndAtCnf.ulAvlServiceNum)
    {
        PS_MEM_CPY(&stSndAtCnf.astAvlServices[0], &pstRcvLrrcCnf->astAvlServices[0], sizeof(MTA_AT_MBMS_AVL_SERVICE_STRU) * stSndAtCnf.ulAvlServiceNum);
    }

    for (ulAvlServiceListNum = 0; ulAvlServiceListNum < stSndAtCnf.ulAvlServiceNum; ulAvlServiceListNum++)
    {
        TAF_SDC_PlmnId2Bcd(&stSndAtCnf.astAvlServices[ulAvlServiceListNum].stTMGI.stPlmnId);
    }
    
    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcQryAvlServiceList
 ��������  : ��ѯMBMS���÷����б���Ϣ��ʱ�Ĵ�����
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
VOS_VOID TAF_MTA_RcvTiWaitLrrcQryAvlServiceList(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_APPCTRL_STRU                            *pstAppCtrl      = VOS_NULL_PTR;
    MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF_STRU   stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstAppCtrl          = (AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(pstAppCtrl,
                     ID_MTA_AT_MBMS_AVL_SERVICE_LIST_QRY_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LRRC_MBMS_AVL_SERVICE_LIST_QRY_CNF);

    return;
}
#endif
/* Added by w00316404 for eMBMS project, 2015-5-22, end */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

