/******************************************************************************

                   ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmCdataHandOff.c��
  �� �� ��   : ����
  ��    ��   : y00314741
  ��������   : 2015��04��07��
  ����޸�   :
  ��������   :
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��04��07��
    ��    ��   : y00314741
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafSdcLib.h"
#include "TafApsCtx.h"
#include "TafMmaInterface.h"
#include "TafApsSndXcc.h"
#include "TafApsSndPpp.h"
#include "TafApsSndAds.h"
#include "TafApsSndCds.h"

#include "taf_aps_ppp_pif.h"
#include "TafApsComFunc.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"
#include "TafSdcCtx.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsDsFlowStats.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafApsFsmCdataHandOff.h"
#include "TafApsFsmCdataHandOffTbl.h"
#include "TafApsSndRlp.h"
#include "TafApsSndCds.h"
#include "TafApsProcIpFilter.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#include "xcc_aps_pif.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_HANDOFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInter1XHrpdHandOff_CdataHandOff_Init
 ��������  : CDATA HANDOFF INIT��״̬���յ�ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInter1XToHrpdHandOff_CdataHandOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ݷ����л�����ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER,
                       TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER_LEN,
                       ucPdpId);

    /* ����ģʽ�л������HSM */
    TAF_APS_SndHsm1XToHrpdHandOffReq(ucPdpId);

    /* ��״̬TAF_APS_STA_CDATA_HANDOFF */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_HANDOFF);

    /* Ǩ��TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF��״̬ */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf
 ��������  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF��״̬��
             �յ�ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU  *pstApsHandOffCnf;
    VOS_UINT8                             ucPdpId;

    /* ��ʼ�� */
    pstApsHandOffCnf  = (HSM_APS_1X_TO_HRPD_HANDOFF_CNF_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣģʽ�л���ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    /* ���ݷ����л��ɹ� */
    if (HSM_APS_CAUSE_SUCCESS == pstApsHandOffCnf->ulCause)
    {
        /* ���½������ݷ���Ľ��뼼�� */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);
    }

    /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_DORMANT);

    /* �˳���״̬״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf
 ��������  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF��״̬��
             �յ�TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_DORMANT);

    /* �˳���״̬״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEndReq_CdataEHandOff_WaitHsmHandOffCnf
 ��������  : TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ֹͣ�����ݷ����л�������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    //To do:��ʱ���մ�������������ο��������

    /* ���PPP�Ѽ��֪ͨPPPȥ���� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }


    /* �ϱ�ȥ������¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, end */

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccIncomingCallInd_CdataEHandOff_WaitHsmHandOffCnf
 ��������  : TAF_APS_RcvXccIncomingCallInd_CdataEHandOff_WaitHsmHandOffCnf��״̬��
             �յ�ID_XCC_APS_INCOMING_CALL_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��21��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataHandOff_WaitHsmHandOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�����ݷ����л�������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER, ucPdpId);

    /*-------------------------------------------------------
    ����TAF_APS_FSM_CDATA_ESTING״̬��
    ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

    ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
    ID_XCC_APS_INCOMING_CALL_IND��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}




VOS_VOID TAF_APS_Proc1xToHrpdHandOff(
    VOS_UINT8                           ucPdpId,
    VOS_UINT8                           ucIsNewSession
)
{
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /* ��1X�л���HRPD */
    if (VOS_TRUE == ucIsNewSession)
    {
        /* ���µ�ǰ�������ݷ����ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_HRPD);
    }
    else
    {
        /* �����ڲ�1X��HRPD�л�������Ϣ */
        TAF_APS_SndInter1XToHrpdHandOffReq(ucPdpId);
    }

    return;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


