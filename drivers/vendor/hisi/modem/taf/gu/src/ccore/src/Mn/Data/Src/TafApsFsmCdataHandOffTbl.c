/******************************************************************************

                   ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsFsmCdataHandOffTbl.c��
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
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafMmaInterface.h"
#include "TafApsFsmCdataHandOff.h"
#include "TafApsFsmCdataHandOffTbl.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"

#endif


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_HANDOFF_TBL_C

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
/* TAF APS״̬������:CDATA HANDOFF ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataHandOffFsmDesc;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/* TAF_APS_CDATA_HANDOFF_SUBSTA_INIT������ */
TAF_ACT_STRU   g_astTafApsCdataHandOffSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ,
                     TAF_APS_RcvPsInter1XToHrpdHandOff_CdataHandOff_Init),

};

/* TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF������ */
TAF_ACT_STRU   g_astTafApsCdataHandOffSubStaWaitHsmHandOffCnfActTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF,
                     TAF_APS_RcvHsmHandOffCnf_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_1X_TO_HRPD_HANDOFF_TIMER,
                     TAF_APS_RcvTi1XToHrpdHandOffExpired_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataHandOff_WaitHsmHandOffCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataHandOff_WaitHsmHandOffCnf),

};


TAF_STA_STRU g_astTafApsCdataHandOffStaTbl[] =
{
    /*****************����TAF_APS_MS_ACTIVATING_SUBSTA_INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_HANDOFF_SUBSTA_INIT,
                      g_astTafApsCdataHandOffSubStaInitTbl ),

    /*****************����TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_HANDOFF_SUBSTA_WAIT_HSM_HANDOFF_CNF,
                      g_astTafApsCdataHandOffSubStaWaitHsmHandOffCnfActTbl ),
};

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCdataHandOffStaTblSize
 ��������  : ��ȡCDATA HANDOFF״̬���Ĵ�С
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_GetCdataHandOffStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataHandOffStaTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCdataHandOffFsmDescAddr
 ��������  : ��ȡCDATA HANDOFF״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_FSM_DESC_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_APS_GetCdataHandOffFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataHandOffFsmDesc);
}



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



