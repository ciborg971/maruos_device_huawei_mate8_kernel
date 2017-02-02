

#ifndef __WASTIMERASN1_H__
#define __WASTIMERASN1_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "product_config.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 Description    : Э�鶨ʱ���͹��ܶ�ʱ�� ����
                  BOUNDARY_START����ʶ��ģ�鶨ʱ���ڶ�ʱ�����е���ʼ�±�;
                  BOUNDARY_END����ʶ��ģ�鶨ʱ���ڶ�ʱ�����еĽ����±�;
                  ����ģ��Ķ�ʱ��������Ҫ�����ڸ�����Ӧ��������.
 Message origin :
*****************************************************************************/
enum WAS_TI_ENUM
{
    /* Э�鶨ʱ������ */

    /* RB ģ�鶨ʱ�� */
    WAS_PTL_TI_RB_BOUNDARY_START                 = 0,                           /* RB ��ʱ����ʼ�߽�      */

    WAS_PTL_TI_RB_BOUNDARY_END                   = 4,                           /* RB ��ʱ�������߽�      */

    /* RRC ģ�鶨ʱ�� */
    WAS_PTL_TI_RRC_BOUNDARY_START                = 5,                       /* RRC ��ʱ����ʼ�߽�     */
    TI_WAS_IDLE_T300                             = 6,
    TI_WAS_CONN_T304                             = 7,
    TI_WAS_CONN_T308                             = 8,
    TI_WAS_RRC_REJECT_WAIT_TIME                  = 9,                           /* �ȴ��ط�RRC CONN REQ��ʱ�� */
    TI_WAS_RRC_CS_INDI_WAIT_RLC_CNF              = 10,                           /* CS���ʼֱ�������еȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_PS_INDI_WAIT_RLC_CNF              = 11,                           /* PS���ʼֱ�������еȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_FIRST_UL_DIRECT_WAIT_RLC_CNF      = 12,                           /* ��1λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_SECOND_UL_DIRECT_WAIT_RLC_CNF     = 13,                           /* ��2λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_THIRD_UL_DIRECT_WAIT_RLC_CNF      = 14,                           /* ��3λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_FOURTH_UL_DIRECT_WAIT_RLC_CNF     = 15,                           /* ��4λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_FIFTH_UL_DIRECT_WAIT_RLC_CNF      = 16,                           /* ��5λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_SIXTH_UL_DIRECT_WAIT_RLC_CNF      = 17,                           /* ��6λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_SEVENTH_UL_DIRECT_WAIT_RLC_CNF    = 18,                           /* ��7λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_EIGHTH_UL_DIRECT_WAIT_RLC_CNF     = 19,                           /* ��8λ����ֱ����Ϣ�ȴ�RLC CNF�ı�����ʱ�� */
    TI_WAS_RRC_CS_SIGNAL_WAIT_RLC_CNF            = 20,                           /* CS�������ͷŹ����еȴ�RLC CNF�ı�����ʱ��*/
    TI_WAS_RRC_PS_SIGNAL_WAIT_RLC_CNF            = 21,                           /* PS�������ͷŹ����еȴ�RLC CNF�ı�����ʱ��*/
    TI_WAS_RRC_WAIT_SIB_CHG_SFN                  = 22,                           /* �ȴ�SIB CHG SFN�������ϵͳ��Ϣ���յĶ�ʱ��*/
    TI_WAS_RRC_SIGNAL_REL_WAIT_NW_REL            = 23,
    TI_WAS_RRC_FR                                = 24,                           /* �ȴ�FR�Ķ�ʱ�� */
    TI_WAS_PS_SUSPEND_PROTECT                    = 26,                              /* ����PSҵ�񱣻���ʱ�� */
    TI_WAS_CONN_T320                             = 27,                          /* T320��ʱ������cuʱֹͣ���յ�cu cnf��p����ura_p,��waittimeʱ���� */
    WAS_PTL_TI_RRC_BOUNDARY_END                  = 31,                           /* RRC ��ʱ�������߽�     */

    /* SMC ģ�鶨ʱ�� */
    WAS_PTL_TI_SMC_BOUNDARY_START                = 32,                        /* SMC ��ʱ��ID��ʼ�߽�     */

    WAS_PTL_TI_SMC_BOUNDARY_END                  = 35,                           /* SMC ��ʱ��ID�����߽�     */

    /* CU  ģ�鶨ʱ�� */
    WAS_PTL_TI_CU_BOUNDARY_START                 = 36,                        /* CU ��ʱ����ʼ�߽�      */
    TI_WAS_CONN_T302                             = 37,
    TI_WAS_CONN_T314                             = 38,
    TI_WAS_CONN_T315                             = 39,

    TI_WAS_CU_PROCESS_MSG_DISCARD                = 40,                       /*�Զ��嶨ʱ��,����CU����ǰ������*/

    WAS_PTL_TI_CU_BOUNDARY_END                   = 46,                           /* CU ��ʱ�������߽�      */

    /* CSELPC ģ�鶨ʱ�� */
    WAS_PTL_TI_CSELPC_BOUNDARY_START             = 47,                        /* CSELPC ��ʱ����ʼ�߽�  */
    TI_WAS_CSELPC_OUT_SERV                       = 48,                           /* ���ݵĳ������������Ѻ�С����ʱ��*/
    TI_WAS_CSELPC_UNRECOVERABLE_WAIT             = 49,                           /* CSELPC���յ�L2���ɻָ����ʱ����Ҫ��3s�������ֲ���Ǩ������ʱ�����ɻָ��Ĵ�*/
    TI_WAS_CSELPC_UNRECOVERABLE_RESTART          = 50,                           /* CSELPC��Ǩ�����̺���Ҫ�ٵ�1�����ٴ����ɻָ��Ĵ�*/
    TI_WAS_CSELPC_IDLE_CAND_SEARCH               = 51,                           /* CSELPC��IDLE̬�³�����������30s������������С��*/
    TI_WAS_CONN_T317                             = 52,
    TI_WAS_CSELPC_RF_UNAVAILABLE                 = 53,                           /* ��Դ�����ö�ʱ�� */
    TI_WAS_NOISE_DETECT                          = 54,                           /* ��ˮ����ⶨʱ����ʱ */
    WAS_PTL_TI_CSELPC_BOUNDARY_END               = 62,                           /* CSELPC ��ʱ�������߽�  */

    /* SHO ģ�鶨ʱ�� */
    WAS_PTL_TI_SHO_BOUNDARY_START                = 63,                           /* SHO ��ʱ����ʼ�߽�     */

    WAS_PTL_TI_SHO_BOUNDARY_END                  = 66,                           /* SHO ��ʱ�������߽�     */


    /* SYSHO ģ�鶨ʱ�� */
    WAS_PTL_TI_SYSHO_BOUNDARY_START              = 67,                           /* SYSHO ��ʱ����ʼ�߽�   */
    TI_WAS_SYSHO_DELAY_FOR_L2ACK                 = 68,                           /* W2GС������ͷŲ�2ǰ�ı�����ʱ�� */
    TI_WAS_SYSHO_W2L_DELAY_FOR_L2ACK             = 69,                           /* W2LС���л��Ų�2ǰ�ı�����ʱ�� */
    WAS_PTL_TI_SYSHO_BOUNDARY_END                = 71,                           /* SYSHO ��ʱ�������߽�   */

    /* RM ģ�鶨ʱ�� */
    WAS_PTL_TI_RM_BOUNDARY_START                 = 72,                           /* RM ��ʱ����ʼ�߽�      */
    TI_WAS_RM_INTRA_FREQ_MEAS_EVT_TRIG           = 73,                           /* ͬƵ������trigger timer*/
    TI_WAS_RM_INTRA_FREQ_MEAS_PERI_RPT           = 74,                           /* ͬƵ���������ڱ���ģʽʹ�õ����ڶ�ʱ��   */
    TI_WAS_RM_INTRA_FREQ_MEAS_EVT_PERI_RPT       = 75,                           /* ͬƵ�������¼�����ģʽʹ�õ����ڶ�ʱ��   */
    TI_WAS_RM_INTER_FREQ_MEAS_EVT_TRIG           = 76,                           /* ��Ƶ������trigger timer*/
    TI_WAS_RM_INTER_FREQ_MEAS_PERI_RPT           = 77,                           /* ��Ƶ���������ڶ�ʱ��   */
    TI_WAS_RM_INTER_FREQ_MEAS_VAS_EVT_TRIG       = 78,                           /* �鼤���trigger timer*/
    TI_WAS_RM_INTER_RAT_MEAS_EVT_TRIG            = 79,                           /* ��ϵͳ������trigger timer*/
    TI_WAS_RM_INTER_RAT_MEAS_PERI_RPT            = 80,                           /* ��ϵͳ���������ڶ�ʱ�� */
    TI_WAS_RM_UE_INTERNAL_MEAS_EVT_TRIG          = 81,                           /* UE�ڲ�������trigger timer*/
    TI_WAS_RM_UE_INTERNAL_MEAS_PERI_RPT          = 82,                           /* Ue�ڲ����������ڶ�ʱ�� */
    TI_WAS_RM_TRAF_VOL_MEAS_PERI_RPT             = 83,                           /* ҵ���������������ڶ�ʱ��*/
    TI_WAS_RM_QUAL_MEAS_PERI_RPT                 = 84,                           /* �������������ڶ�ʱ��   */
    TI_WAS_RM_POS_MEAS_PERI_RPT                  = 85,                           /* ��λ���������ڶ�ʱ�� */
    TI_WAS_RM_RPT_BUF                            = 86,                           /* RM���Ͳ�������ʱ,����ġ�����rpt buf��Ķ�̬�ڴ�ı�����ʱ��*/
    TI_WAS_RM_EUTRA_MEAS_EVT_TRIG                = 87,                           /* EUTRA������trigger timer*/
    TI_WAS_RM_EUTRA_MEAS_PERI_RPT                = 88,                           /* EUTRA���������ڶ�ʱ�� */
    TI_WAS_RM_REQ_SAME_ADD_ASSIST_DATA           = 89,                           /* ������ͬ�ĸ������ݵĶ�ʱ�� */
    WAS_PTL_TI_RM_BOUNDARY_END                   = 100,                           /* RM ��ʱ�������߽�      */

    /* SIB ģ�鶨ʱ�� */
    WAS_PTL_TI_SIB_BOUNDARY_START                = 101,                           /* SIB ��ʱ����ʼ�߽�     */
    TI_WAS_SIB_REPEAT_SIB7                       = 102,                           /* ����SIB7���ڶ�ʱ��     */
    TI_WAS_SIB_6HOUR_PERIOD                      = 103,                           /* 6Сʱ���ڶ�ʱ��        */
    WAS_PTL_TI_SIB_BOUNDARY_END                  = 109,                           /* SIB ��ʱ�������߽�     */

    /* CSEL ģ�鶨ʱ�� */
    WAS_PTL_TI_CSEL_BOUNDARY_START               = 110,                           /* CSEL ��ʱ����ʼ�߽�    */
    TI_WAS_CSEL_CELL_LIST_VALID                  = 111,                           /* ����ʱ�洢��С����Ϣ��Ч�Ķ�ʱ����30s*/
    TI_WAS_CSEL_USER_PLMN_LIST_RSSI_BAND_VALID   = 112,                           /* �û�ָ������PLMN List����ʱ��ȫƵ�ε�RSSI�����Ƿ���Ч�Ķ�ʱ�� */
    TI_WAS_CSEL_TRESELECTION                     = 113,                           /* ��ѡ��ʱ��,��λ100ms */
    TI_WAS_CSEL_TEVALUATE                        = 114,                           /* Treselection = 0ʱ,����ʱ�䶨ʱ������λ100ms */
    TI_WAS_CSEL_TN                               = 115,                           /* ʹ��HCS�ṹʱ��Ϊ����ά����Tn��ʱ��  */
    TI_WAS_CSEL_TBARRED                          = 116,                           /* ����С����ʱ�� */
    TI_WAS_CSEL_OUT_OF_SERVICE                   = 117,                           /* IDLE��P״̬����ѡ��ʱ��,12s;FACH�³���������ʱ����4s */
    TI_WAS_CSEL_RESEL_BARRED                     = 118,                           /* ��ֹ��ѡ��ʱ����1s        */
    TI_WAS_CSEL_GSM_BSIC_VERIFY                  = 119,                           /* BSIC��֤�Ķ�ʱ������:IDLE��P״̬��ʱ��30s;FACH��ʱ��10s��*/
    TI_WAS_CSEL_WAIT_GSM_BSIC_VERIFY_IND         = 120,                           /* BSIC��֤������ȴ���֤����ı�����ʱ�� */
    TI_WAS_CSEL_DETECT_UE_MOBILITY_STATE         = 121,                           /* ���UE�ƶ�״̬�ĵ�λ��ʱ����10s*/
    TI_WAS_CSEL_DETECT_EXIT_HIGH_MOBILITY        = 122,                           /* ����˳������ƶ�״̬�Ķ�ʱ�� */
    TI_WAS_CSEL_JAM_DETECTING                    = 123,                           /* ���������и��ż�ⶨʱ�� */
    TI_WAS_CSEL_JAM_DETECTED                     = 124,                           /* ���������и��Ŵ��ڶ�ʱ�� */
#if (FEATURE_ON == FEATURE_LTE)
    TI_WAS_CSEL_W2L_RESEL_PENALTY                = 125,                           /* W2L��ѡ�ͷ���ʱ�� */
#endif
    WAS_PTL_TI_CSEL_BOUNDARY_END                 = 132,                           /* CSEL ��ʱ�������߽�    */

    /* MAIN ģ�鶨ʱ�� */
    WAS_PTL_TI_MAIN_BOUNDARY_START               = 133,                           /* MAIN ��ʱ����ʼ�߽�    */
    TI_WAS_MAIN_INTERRAT_RESEL_WAIT_EST_REQ      = 134,                           /* l2w����g2w��ѡ������ʱ��ȴ�ע����Ϣ */
    WAS_PTL_TI_MAIN_BOUNDARY_END                 = 136,                           /* MAIN ��ʱ�������߽�    */

    /* COMM ģ�鶨ʱ�� */
    WAS_PTL_TI_COMM_BOUNDARY_START               = 137,                           /* COMM ��ʱ����ʼ�߽�    */

    WAS_PTL_TI_COMM_BOUNDARY_END                 = 139,                           /* COMM ��ʱ�������߽�    */

    /* NASITF ģ�鶨ʱ�� */
    WAS_PTL_TI_NASITF_BOUNDARY_START             = 140,                           /* NASITF ��ʱ����ʼ�߽�  */

    WAS_PTL_TI_NASITF_BOUNDARY_END               = 142,                           /* NASITF ��ʱ�������߽�  */

    /* TAFITF ģ�鶨ʱ�� */
    WAS_PTL_TI_TAFITF_BOUNDARY_START             = 143,                           /* TAFITF ��ʱ����ʼ�߽�  */

    WAS_PTL_TI_TAFITF_BOUNDARY_END               = 145,                           /* TAFITF ��ʱ�������߽�  */

    /* PHYITF ģ�鶨ʱ�� */
    WAS_PTL_TI_PHYITF_BOUNDARY_START             = 146,                           /* PHYITF ��ʱ����ʼ�߽�  */
    TI_WAS_CONN_T312                             = 147,
    TI_WAS_IDLE_T312                             = 148,
    TI_WAS_CONN_T313                             = 149,
    TI_WAS_SYNC_DETECT                           = 150,                           /* ͬ��Ԥ��ⶨʱ�� */
    TI_WAS_JUDGE_DISABLE_UL_TX                   = 151,                           /* ʧ��ʱ�����в��ٷ���   */
    WAS_PTL_TI_PHYITF_BOUNDARY_END               = 152,                           /* PHYITF ��ʱ�������߽�  */

    /* L2ITF ģ�鶨ʱ�� */
    WAS_PTL_TI_L2ITF_BOUNDARY_START              = 153,                         /* L2ITF ��ʱ����ʼ�߽�   */

    WAS_PTL_TI_L2ITF_BOUNDARY_END                = 159,                           /* L2ITF ��ʱ�������߽�   */

    /* ASN1 ģ�鶨ʱ�� */
    WAS_PTL_TI_ASN1_BOUNDARY_START               = 160,                           /* ASN1 ��ʱ����ʼ�߽�    */

    WAS_PTL_TI_ASN1_BOUNDARY_END                 = 162,                           /* ASN1 ��ʱ�������߽�    */

    /* MNTN ģ�鶨ʱ�� */
    WAS_PTL_TI_MNTN_BOUNDARY_START               = 163,                           /* MNTN ��ʱ����ʼ�߽�    */

    TI_WAS_MNTN_ACT_OR_SERV_CELL_INFO_PERI_RPT   = 164,                           /* �����ϱ���С���򼤻С����ʱ�� */
    TI_WAS_MNTN_W_NEIGH_CELL_INFO_PERI_RPT       = 165,                           /* ����W��С����ʱ��                */
    TI_WAS_MNTN_G_NEIGH_CELL_INFO_PERI_RPT       = 166,                           /* ����G��С����ʱ��                */
    TI_WAS_MNTN_SECOND_CELL_INFO_PERI_RPT        = 167,                           /* SECOND CELL�ϱ���С���򼤻С�����Լ�SECOND CELL������ʱ�� */
    TI_WAS_MNTN_L_NEIGH_CELL_INFO_PERI_RPT       = 168,                           /* ����LTE��С����ʱ��  */
    TI_WAS_MNTN_ERROR_LOG_SAMPLE_IND             = 169,                           /* error log������ʱ����ʱ�䳤��Ϊ1����*/
    TI_WAS_MNTN_GET_TAF_SRV_STATUS_FLAG          = 170,                         /* ����̬��,�ӳٻ�ȡTAF����״̬��ʱ�� */
#if (FEATURE_ON == FEATURE_PTM)
    TI_WAS_MNTN_ERRORLOG_3G_NOT_TO_LTE_TIMER     = 171,                           /* ��Wģ��פ����ʱ�䶨ʱ�� */
#endif    

    WAS_PTL_TI_MNTN_BOUNDARY_END                 = 180,                           /* MNTN ��ʱ�������߽�    */


    /* ������ʱ������,����������ʱ�͹�����ʱ�� */
    WAS_PTL_TI_OTHERS                            = 181,                           /* ������ʱ����ʼ�߽� */
    TI_WAS_CONN_T305                             = 182,                           /*RB �� CSELPC*/
    TI_WAS_CONN_T309                             = 183,
    TI_WAS_CONN_T310                             = 184,
    TI_WAS_CONN_T311                             = 185,
    TI_WAS_CONN_T316                             = 186,                           /*RB �� CSELPC */
    TI_WAS_CONN_T307                             = 187,                           /*RB �� CSELPC */
    TI_WAS_SRB_DELAY                             = 188,                           /* ��DCH��ģ�鶼��Ҫ */
    TI_WAS_RESEL_DELAY                           = 189,       /* ��ʱ�ȴ���ѡ�ϱ������gcf���� */

    TI_WAS_TIMER_OUT_OF_SERVICE                  = 190,       /*��������Э�鶨ʱ��,TimerOutOfService time (default value 30 seconds)*/
    TI_WAS_OUT_OF_SERVICE_PERIOD_SEARCH_SUITABLE = 191,
    TI_WAS_CONN_T319                             = 192,                         /* CSELPC T319˫DRX��ʱ����ʱ��ʱ�� */
    TI_WAS_CONN_T322                             = 193,                         /* ���ȼ���ʱ�� */
    TI_WAS_CONN_T323                             = 194,                         /* FastDormancy ��ʱ�� */

    WAS_PTL_TI_NAS_SESSION_BOUNDARY_START        = 200,                         /* NAS_SESSION ��ʱ����ʼ�߽�   */

    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_NORMAL_CALL        = 201,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_EMERGENCY_CALL     = 202,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_SS                 = 203,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_SMS                = 204,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_NORMAL_CALL        = 205,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_EMERGENCY_CALLBACK = 206,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_SS                 = 207,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_SMS                = 208,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_LAU                   = 209,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_DETACH                = 210,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_NORMAL_CSFB        = 211,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MO_EMERGENCY_CSFB     = 212,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_CS_MT_CSFB               = 213,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_CONVERSAT_CALL        = 214,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_STREAM_CALL           = 215,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_INTERACT_CALL         = 216,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_BACKGROUND_CALL       = 217,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_SUBSCRIB_TRAFFIC_CALL = 218,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_MO_SMS                = 219,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_MT_SMS                = 220,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_ATTACH                = 221,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_RAU                   = 222,
    TI_WAS_RRC_NAS_SESSION_WAIT_RRM_RF_RES_PS_DETACH                = 223,

    WAS_PTL_TI_NAS_SESSION_BOUNDARY_END             = 229,                      /* NAS_SESSION ��ʱ�������߽�   */

    WAS_PTL_TI_BUTT                                 = 230,

    /* ״̬������ʱ������ */
    /* RB ģ�鶨ʱ�� */
    WAS_STATE_TI_RB_BOUNDARY_START                 = 0xF000 ,                   /* RB ��ʱ����ʼ�߽�      */
    TI_WAS_RB_WAIT_WCOM_CNF                                 ,                   /* �ڸ�WCOMM����Ϣ�����ö�ʱ��
                                                                                    �ȴ�WCOMM����Ӧ��Ϣ */
    TI_WAS_RB_WAIT_NAS_RSP                                  ,                   /* �ȴ�NAS RSP��״̬������ʱ�� */
    TI_WAS_RB_WAIT_ACTIVE_IND                               ,                   /* ���ú�ȴ�����ʱ�䵽ind������ʱ�� */
    TI_WAS_RB_WAIT_AM_DATA_CNF                              ,                   /* �ȴ�AM Data ȷ�ϱ�����ʱ�� */
    TI_WAS_RB_WAIT_DLSYNC_CNF                               ,                   /* �ȴ�DL SYNC CNF������ʱ�� */
    TI_WAS_RB_WAIT_TI_SRBDELAY                              ,                   /* �Եȴ�SRB Delay��ʱ����ʱ����״̬���б��� */
    TI_WAS_RB_WAIT_CELL_SEARCH_CNF                          ,                   /* �ȴ�С������������ʱ�� */
    TI_WAS_RB_WAIT_CELL_CHANGE_RPT                          ,                   /* �ȴ�С����ѡ����Ķ�ʱ��ʱ����9s*/
    WAS_STATE_TI_RB_BOUNDARY_END                            ,                   /* RB ��ʱ�������߽�      */

    /* RRC ģ�鶨ʱ�� */
    WAS_STATE_TI_RRC_BOUNDARY_START                         ,                   /* RRC ��ʱ����ʼ�߽�     */
    TI_WAS_RRC_CONN_SETUP_CMP_CNF                           ,                   /* �ȴ�RLC��RRC CONN SETUP CMP�ķ���ȷ��*/
    TI_WAS_RRC_WAIT_PHY_CAMPED_CNF                          ,                   /* �ȴ�PHY CAMPED CNF�Ķ�ʱ��_*/
    TI_WAS_RRC_WAIT_WCOMM_CNF                               ,                   /* �ȴ�WCOMM�ظ��ı�����ʱ��*/
    TI_WAS_RRC_WAIT_SIB_CNF                                 ,                   /* �ȴ�SIB�ظ��ı�����ʱ��*/
    TI_WAS_RRC_WAIT_RM_CNF                                  ,                   /* �ȴ�RM�ظ��ı�����ʱ��*/
    TI_WAS_RRC_WAIT_CSEL_CNF                                ,                   /* �ȴ�CSEL�ظ��ı�����ʱ��*/
    TI_WAS_RRC_WAIT_SIB_CHG_CNF                             ,                   /* �ȴ�SIBϵͳ��Ϣ������ջظ��ı�����ʱ��*/
    TI_WAS_RRC_WAIT_CSEL_SEARCH_CNF                         ,                   /* �ȴ�CSELС�������ظ��ı�����ʱ��*/
    TI_WAS_RRC_REL_STATE                                    ,                   /* RRC RELEASE���̴����е�״̬������ʱ�� */
    TI_WAS_MAC_STATUS_IND                                   ,                   /* �ȴ�MAC STATUS IND��ʱ��*/
    TI_WAS_PHY_DL_SYNC_IND                                  ,                   /* �ȴ�DL SYNC IND �Ķ�ʱ��*/
    TI_WAS_RRC_WAIT_GAS_RESEL_CNF                           ,                   /* �ȴ�GAS�ظ�WRRCRR_CELL_RESEL_TIMER_EXPIRED_CNF�Ķ�ʱ�� */
    TI_WAS_RRC_WAIT_CELL_CHANGE_RPT                         ,                   /* �ȴ�С����ѡ����Ķ�ʱ��ʱ����9s*/
    TI_WAS_RRC_WAIT_REDIRECTION_CNF                         ,
    TI_WAS_RRC_WAIT_BG_SEARCH_STOP_CNF                      ,                   /* ֹͣ�����ѽ���Ķ�ʱ����5s     */

#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_RRC_WAIT_RRM_RF_RES_APPLY_CNF                    ,                   /* �ȴ�RF��Դ������Ӧ�Ķ�ʱ�� */
    TI_WAS_RRC_SEARCH_WAIT_RRM_RF_RES_APPLY_CNF             ,                   /* RRC��������Դ���룬�ȴ�RF��Դ������Ӧ�Ķ�ʱ�� */
    TI_WAS_RRC_REL_WAIT_RRM_RF_RES_APPLY_CNF                ,                   /* RRC REL ��������Դ���� */
#endif

    WAS_STATE_TI_RRC_BOUNDARY_END                           ,                   /* RRC ��ʱ�������߽�     */

    /* CBS ģ�鶨ʱ�� */
    WAS_STATE_TI_CBS_BOUNDARY_START                         ,
    TI_WAS_CBS_STATE_PROTECT                                ,                   /* CBS ״̬������ʱ�� */
    TI_WAS_CBS_NO_USE                                       ,                   /* ��ʹ�� */
    WAS_STATE_TI_CBS_BOUNDARY_END,

    /* SMC ģ�鶨ʱ�� */
    WAS_STATE_TI_SMC_BOUNDARY_START                         ,
    TI_WAS_SMC_WAIT_RLC_CNF                                 ,                   /* */
    TI_WAS_SMC_CELL_CHG_WAIT_RLC_CNF                        ,                   /* ����SMC cmpl������ѡ��ȴ�RLC CNF�ı�����ʱ��*/
    WAS_STATE_TI_SMC_BOUNDARY_END                           ,

    /* CU  ģ�鶨ʱ�� */
    WAS_STATE_TI_CU_BOUNDARY_START                          ,                   /* CU ��ʱ����ʼ�߽�      */
    TI_WAS_CU_WAIT_CNF                                      ,
    TI_WAS_CU_WAIT_DLSYNC_CNF                               ,                   /* �ȴ�DL SYNC CNF������ʱ�� */
    TI_WAS_CU_WAIT_TI_SRBDELAY                              ,                   /* �Եȴ�SRB Delay��ʱ����ʱ����״̬���б��� */
    TI_WAS_CU_WAIT_CELL_SEARCH_CNF                          ,                   /* CU����С������״̬��ʱ��*/
    TI_WAS_CU_WAIT_PLMN_SEARCH_CNF                          ,                   /* CU�ȴ�WȫƵ����״̬������ʱ��*/
    TI_WAS_CU_WAIT_ANY_CELL_SEARCH_CNF                      ,
    TI_WAS_CU_WAIT_GSM_SEARCH_CNF                           ,                   /* �ȴ�GSMС��������ʱ��ʱ��,1����*/
    TI_WAS_CU_WAIT_LTE_SEARCH_CNF                           ,
    TI_WAS_CU_WAIT_CELL_CHANGE_RPT                          ,                   /* �ȴ�С����ѡ����Ķ�ʱ��ʱ����9s*/
    TI_WAS_CU_WAIT_BG_SEARCH_STOP_CNF                       ,                   /* �ȴ�ֹͣ�����ѽ���Ķ�ʱ��ʱ����5s */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, begin */
    TI_WAS_CU_WAIT_WCOM_CNF                                 ,                   /* CU�ڸ�WCOMM����Ϣ�����ö�ʱ�����ȴ�WCOMM����Ӧ��Ϣ */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, end */
    WAS_STATE_TI_CU_BOUNDARY_END                            ,                   /* CU ��ʱ�������߽�      */

    /* CSELPC ģ�鶨ʱ�� */
    WAS_STATE_TI_CSELPC_BOUNDARY_START                      ,                   /* CSELPC ��ʱ����ʼ�߽�  */
    TI_WAS_CSELPC_WAIT_CNF                                  ,
    TI_WAS_CSELPC_WAIT_GAS_RESEL_CNF                        ,                   /* CSELPC W2G��ϵͳ��ѡʱ�ȴ�GAS��Ӧ�ı�����ʱ��*/
    TI_WAS_CSELPC_WAIT_LRRC_RESEL_CNF                        ,                  /* CSELPC W2L��ϵͳ��ѡʱ�ȴ�GAS��Ӧ�ı�����ʱ��*/
    TI_WAS_CSELPC_WAIT_LOAD_AMR_CODEC                       ,                   /* CSELPC �ȴ������������ı�����ʱ��*/
    TI_WAS_CSELPC_WAIT_PLMN_SEARCH_CNF                      ,
    TI_WAS_CSELPC_WAIT_CAND_CELL_SEARCH_CNF                 ,
    TI_WAS_CSELPC_WAIT_SPEC_FREQ_SEARCH_CNF                 ,                   /* CSELPC �ȴ�ָ��Ƶ����������ı�����ʱ��*/
    TI_WAS_CSELPC_WAIT_ANY_CELL_SEARCH_CNF                  ,
    TI_WAS_CSELPC_WAIT_G_PLMN_SEARCH_TIMER                  ,
    TI_WAS_CSELPC_WAIT_L_PLMN_SEARCH_TIMER                  ,
    TI_WAS_CSELPC_DEACTIVE_WAIT_RESUME_REQ                  ,                   /* cselpc�����ȴ�gas�ָ������� */
    TI_WAS_CSELPC_DEACTIVE_WAIT_STOP_CNF                    ,                   /* cselpc�ȴ�csel�ظ�stop cnf */
    TI_WAS_CSELPC_DEACTIVE_WAIT_SUSPEND_OR_RESUME_CNF       ,                   /* ��ģ��������cselpc�ȴ�csel�ظ�BG SUSPEND����RESUME CNF�Ķ�ʱ�� */
    TI_WAS_CSELPC_WAIT_PLMN_LIST_SEARCH_CNF                 ,                   /* cselpc�ȴ�csel�ظ�PLMN LIST CNF�Ķ�ʱ�� */
    TI_WAS_CSELPC_WAIT_BG_SEARCH_STOP_CNF                   ,                   /* cselpc�ȴ�csel�ظ�BG STOP CNF�Ķ�ʱ�� */
    TI_WAS_CSELPC_GET_CGI_INFO_WAIT_STOP_CNF                ,                   /* cselpc�ȴ�csel�ظ�stop cnf */
    WAS_STATE_TI_CSELPC_BOUNDARY_END                        ,                   /* CSELPC ��ʱ�������߽�  */

    /* SHO ģ�鶨ʱ�� */
    WAS_STATE_TI_SHO_BOUNDARY_START                         ,                   /* SHO ��ʱ����ʼ�߽�     */
    TI_WAS_SHO_WAIT_RM_SHO_RSP                              ,                   /* SHO�ȴ�ID_WAS_RM_SHO_RSPʱ�ı�����ʱ�� */
    TI_WAS_SHO_WAIT_ACTIVE_IND                              ,                   /* SHO�ȴ�L2��PHY��ACTIVE IND�ı�����ʱ��*/
    TI_WAS_SHO_WAIT_RM_DC_CHG_RSP                           ,                   /* SHO�ȴ�ID_WAS_RM_DC_CHANGE_RSP�ı�����ʱ��*/
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, begin */
    TI_WAS_SHO_WAIT_WCOM_CNF                                ,                   /* SHO�ڸ�WCOMM����Ϣ�����ö�ʱ�����ȴ�WCOMM����Ӧ��Ϣ */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, end */
    WAS_STATE_TI_SHO_BOUNDARY_END                           ,                   /* SHO ��ʱ�������߽�     */

    /* SYSHO ģ�鶨ʱ�� */
    WAS_STATE_TI_SYSHO_BOUNDARY_START                       ,                   /* SYSHO ��ʱ����ʼ�߽�   */
    TI_WAS_SYSHO_WAIT_LOAD_VOCODEC_CNF                      ,                   /* �ȴ�LOAD DSP�ظ�CNF��Ϣ״̬������ʱ����ʱ    */
    TI_WAS_SYSHO_WAIT_CSEL_SEARCH_CNF                       ,                   /* �ȴ�CSEL�ظ�����CNFʱ��Ϣ״̬������ʱ����ʱ      */
    TI_WAS_SYSHO_WAIT_PLMN_SEARCH_CNF                       ,
    TI_WAS_SYSHO_WAIT_NAS_RSP                               ,                   /* �ȴ�NAS�ظ�RSPʱ��Ϣ״̬������ʱ����ʱ       */
    TI_WAS_SYSHO_WAIT_RM_RSP                                ,                   /* �ȴ�RM�ظ�RSPʱ��Ϣ״̬������ʱ����ʱ        */
    TI_WAS_SYSHO_WAIT_GAS_RSP                               ,                   /* �ȴ�GAS�ظ���Ϣ״̬������ʱ����ʱ            */
    TI_WAS_SYSHO_WAIT_GAS_CNF                               ,                   /* �ȴ�GAS�ظ�CNF��״̬������ʱ����ʱ,����HHO   */
    TI_WAS_SYSHO_WAIT_SIB_CNF                               ,                   /* �ȴ�SIB�ظ�CNFʱ��Ϣ״̬������ʱ����ʱ       */
    TI_WAS_SYSHO_WAIT_CSEL_CNF                              ,                   /* �ȴ�CSEL�ظ�CNFʱ��Ϣ״̬������ʱ����ʱ      */
    TI_WAS_SYSHO_WAIT_LRRC_CNF                              ,
    TI_WAS_SYSHO_WAIT_LRRC_HO_CNF                           ,
    TI_WAS_SYSHO_WAIT_LRRC_HO_STOP_CNF                      ,
    TI_WAS_SYSHO_WAIT_GAS_STOP_CNF                          ,                   /* �ȴ�GAS�ظ�HO_STOP_CNFʱ��Ϣ״̬������ʱ����ʱ      */
    WAS_STATE_TI_SYSHO_BOUNDARY_END                         ,                   /* SYSHO ��ʱ�������߽�   */

    /* RM ģ�鶨ʱ�� */
    WAS_STATE_TI_RM_BOUNDARY_START                          ,                   /* RM ��ʱ����ʼ�߽�      */
    TI_WAS_RM_WAIT_PHY_CNF                                  ,                   /* RM �������ͷ������������󱣻���ʱ�� */
    TI_WAS_RM_WAIT_L2_CNF                                   ,                   /* RM �������ͷ�L2�������󱣻���ʱ�� */
    TI_WAS_RM_INTER_RAT_BSIC_VERIFIED                       ,                   /* ��ϵͳ�����з���Bsic��֤�Ķ�ʱ�� */

    /* Modify by shenghua for Indenpendent Multi-Mode, 2014-5-4, begin */
    TI_WAS_RM_WAIT_GSM_BSIC_VERIFIED_CNF                  ,                   /* �ȴ�GSM BSIC CNF, ʱ��1s */
    /* Modify by shenghua for Indenpendent Multi-Mode, 2014-5-4, end */

    TI_WAS_RM_INTER_RAT_WAIT_BSIC_IND                       ,                   /* ��ϵͳ�����ȴ������BSIC_IND������ʱ�� */
    WAS_STATE_TI_RM_BOUNDARY_END                            ,                   /* RM ��ʱ�������߽�      */

    /* SIB ģ�鶨ʱ�� */
    WAS_STATE_TI_SIB_BOUNDARY_START                         ,                   /* SIB ��ʱ����ʼ�߽�     */
    TI_WAS_SIB_WAIT_PCCPCH_SETUP_CNF                        ,                   /* ����PCCPCH������ʱ��   */
    TI_WAS_SIB_WAIT_RCV_SYSINFO                             ,                   /* ����ϵͳ��Ϣ������ʱ�� */
    TI_WAS_SIB_WAIT_RCV_SIB7                                ,                   /* ����sib7���̱�����ʱ�� */
    TI_WAS_SIB_WAIT_PCCPCH_RELEASE_CNF                      ,                   /* �ͷ�PCCPCH������ʱ��   */
    TI_WAS_SIB_WAIT_ACT_TIME                                ,                   /* �ȴ�����ʱ�䶨ʱ��     */
    TI_WAS_SIB_WAIT_CHG_CMPL_RSP                            ,                   /* �ȴ�SysInfo Chg Rsp������ʱ�� */
    TI_WAS_SIB_WAIT_COUNT_BCCH_DATA                         ,                   /* �յ���һ��BCCH DATA IND��1s������ʱ�� */
    TI_WAS_SIB_WAIT_POS_NOTIFY_CNF                          ,                   /* �ȴ�λ����Ϣ������Ӧ������ʱ����ʱ��1s */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, begin */
    TI_WAS_SIB_WAIT_RCV_DCH_SYSINFO                         ,                   /* ����DCHϵͳ��Ϣ���̱�����ʱ�� */
    /* Added by p00316393 for reading sysinfo in cell_dch state, 2015-06-02, end */
    WAS_STATE_TI_SIB_BOUNDARY_END                           ,                   /* SIB ��ʱ�������߽�     */

    /* CSEL ģ�鶨ʱ�� */
    WAS_STATE_TI_CSEL_BOUNDARY_START                        ,                   /* CSEL ��ʱ����ʼ�߽�    */
    TI_WAS_CSEL_WAIT_PHY_CELL_SEARCH_CNF                    ,                   /* ����Ƶ������ʱ�Ķ�ʱ��*/
    TI_WAS_CSEL_FREQ_BAND_WAIT_PHY_CELL_SEARCH_CNF          ,                   /* Ƶ������ʱ�Ķ�ʱ��*/
    TI_WAS_CSEL_WAIT_PHY_CAMPED_MAINCELL_CNF                ,
    TI_WAS_CSEL_WAIT_PHY_MEASUREMENT_CNF                    ,
    TI_WAS_CSEL_WAIT_PHY_BSIC_VERIFIED_CNF                  ,
    /* Modify by shenghua for Indenpendent Multi-Mode, 2014-5-4, begin */
    TI_WAS_CSEL_WAIT_GSM_BSIC_VERIFIED_CNF                  ,                   /* �ȴ�GSM BSIC CNF, ʱ��1s */
    /* Modify by shenghua for Indenpendent Multi-Mode, 2014-5-4, end */
    TI_WAS_CSEL_WAIT_SIB_GET_SYSINFO_CNF                    ,
    TI_WAS_CSEL_WAIT_SIB_REL_SYSINFO_CNF                    ,
    TI_WAS_CSEL_WAIT_CELL_CHANGE_RSP                        ,
    TI_WAS_CSEL_WAIT_PHY_MEAS_SND_CNF                       ,                   /* CSEL IDLE/CONN̬�ȴ���������CNF��Ϣ��ʱ�� */
    TI_WAS_CSEL_WAIT_PHY_FREQ_MEASURE_IND                   ,                   /* �ȴ�PHY�ϱ���ɨ��� */
    TI_WAS_CSEL_WAIT_BG_SUSPEND_CNF                         ,                   /* �ȴ�BG��ͣ�����ѻ����ֶ���������Ӧ */
    TI_WAS_CSEL_WAIT_BG_RESUME_CNF                          ,                   /* �ȴ�BG���������ѻ����ֶ���������Ӧ */
    WAS_STATE_TI_CSEL_BOUNDARY_END                          ,                   /* CSEL ��ʱ�������߽� */

    WAS_STATE_TI_BG_BOUNDARY_START                          ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_CSEL_BG_SEARCH_RESUEM_REQ                ,
    TI_WAS_BG_WAIT_PHY_BG_SEARCH_RESUEM_CNF                 ,

    /* Added by shenghua for Indenpendent Multi-Mode, 2014-5-4, begin */
    TI_WAS_BG_WAIT_GSM_PHY_BG_SEARCH_CNF                    ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_IND                        ,
    /* Added by shenghua for Indenpendent Multi-Mode, 2014-5-4, end */

    TI_WAS_BG_WAIT_GSM_BG_SEARCH_CNF                        ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_GSM_BG_SEARCH_RESUME_CNF                 ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_CNF                  ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_IND                        ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_STOP_CNF                   ,
    TI_WAS_BG_WAIT_LTE_PHY_BG_SEARCH_CNF              ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_SUSPEND_CNF                ,
    TI_WAS_BG_WAIT_LTE_BG_SEARCH_RESUME_CNF                 ,
    TI_WAS_BG_DEACTIVE_WAIT_RESUME_REQ                      ,                   /* cselpc�����ȴ�gas�ָ������� */
    WAS_STATE_TI_BG_BOUNDARY_END                            ,

    /* MAIN ģ�鶨ʱ�� */
    WAS_STATE_TI_MAIN_BOUNDARY_START                        ,                   /* MAIN ��ʱ����ʼ�߽�    */
    TI_WAS_MAIN_WAIT_USIM_RSP                               ,                   /* �ȴ�USIM�ظ���ʱ�� */
    TI_WAS_MAIN_WAIT_L2_RSP                                 ,
    TI_WAS_MAIN_WAIT_PHY_RSP                                ,
    TI_WAS_MAIN_WAIT_WCOMM_CNF                              ,
#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_MAIN_WAIT_CONN_RES_APPLY_CNF                     ,                   /* ����̬�µȴ���Դ����ɹ���ʱ��, ͳһ5s */
    TI_WAS_MAIN_WAIT_GAS_RESEL_TIMER_EXP_CNF                ,                   /* �ȴ� GAS �ظ� ֹͣ��ѡ��Ӧ�Ķ�ʱ�� */
#endif
    WAS_STATE_TI_MAIN_BOUNDARY_END                          ,                   /* MAIN ��ʱ�������߽�    */

    /* COMM ģ�鶨ʱ�� */
    WAS_STATE_TI_COMM_BOUNDARY_START                        ,                   /* COMM ��ʱ����ʼ�߽�    */
    WAS_STATE_TI_COMM_BOUNDARY_END                          ,                   /* COMM ��ʱ�������߽�    */

    /* NASITF ģ�鶨ʱ�� */
    WAS_STATE_TI_NASITF_BOUNDARY_START                      ,                   /* NASITF ��ʱ����ʼ�߽�  */
    WAS_STATE_TI_NASITF_BOUNDARY_END                        ,                   /* NASITF ��ʱ�������߽�  */

    /* TAFITF ģ�鶨ʱ�� */
    WAS_STATE_TI_TAFITF_BOUNDARY_START                      ,                   /* TAFITF ��ʱ����ʼ�߽�  */
    WAS_STATE_TI_TAFITF_BOUNDARY_END                        ,                   /* TAFITF ��ʱ�������߽�  */

    /* PHYITF ģ�鶨ʱ�� */
    WAS_STATE_TI_PHYITF_BOUNDARY_START                      ,                   /* PHYITF ��ʱ����ʼ�߽�  */
    TI_WAS_PHYITF_WRR_WAIT_PHY_CNF                          ,                   /* WRR PhyItf �ȴ������Ӧ��ʱ��ʱ��*/
    WAS_STATE_TI_PHYITF_BOUNDARY_END                        ,                   /* PHYITF ��ʱ�������߽�  */

    /* L2ITF ģ�鶨ʱ�� */
    WAS_STATE_TI_L2ITF_BOUNDARY_START                       ,                   /* L2ITF ��ʱ����ʼ�߽�   */
    TI_WAS_L2ITF_WAIT_CNF                                   ,                   /* �ȴ�L2Ӧ��ʱ���� */
    WAS_STATE_TI_L2ITF_BOUNDARY_END                         ,                   /* L2ITF ��ʱ�������߽�   */

    /* ASN1 ģ�鶨ʱ�� */
    WAS_STATE_TI_ASN1_BOUNDARY_START                        ,                   /* ASN1 ��ʱ����ʼ�߽�    */
    WAS_STATE_TI_ASN1_BOUNDARY_END                          ,                   /* ASN1 ��ʱ�������߽�    */

    /* MNTN ģ�鶨ʱ�� */
    WAS_STATE_TI_MNTN_BOUNDARY_START                        ,                   /* MNTN ��ʱ����ʼ�߽�    */
    WAS_STATE_TI_MNTN_BOUNDARY_END                          ,                   /* MNTN ��ʱ�������߽�    */

    /* PFC ��ʱ�� */
    WAS_STATE_TI_PFC_BOUNDARY_START                         ,                   /* PFC ��ʱ����ʼ�߽�    */
    TI_WAS_PFC_WAIT_MEAS_CTRL_CNF                           ,                   /* �ȴ�RM�ظ�ID_WAS_RM_MEAS_CTRL_CNF��ʱ�� */
    TI_WAS_PFC_WAIT_ASSIST_DATA_RSP                         ,                   /* �ȴ�RM�ظ�ID_WAS_RM_ASSIST_DATA_RSP��ʱ�� */
    WAS_STATE_TI_PFC_BOUNDARY_END                           ,                   /* PFC ��ʱ�������߽�    */

    WAS_STATE_TI_FSM_PROTECT_WRR                            ,                   /* WRR״̬������������ʱ�� */
    WAS_STATE_TI_FSM_PROTECT_SIB                            ,                   /* SIB״̬������������ʱ�� */
    WAS_STATE_TI_FSM_PROTECT_CSEL                           ,                   /* CSEL״̬������������ʱ�� */
    WAS_STATE_TI_FSM_PROTECT_RM                             ,                   /* RM״̬������������ʱ�� */
    WAS_STATE_TI_FSM_PROTECT_BG                             ,                   /* BG״̬������������ʱ�� */
    TI_WAS_RRC_WAIT_NAS_SUSPEND_CNF                         ,                   /* �ȴ�NAS�ظ�SUSPEND RSP�Ķ�ʱ�� */

    TI_WAS_SYSHO_WAIT_DLSYNC_CNF                            ,                   /* �ȴ�DL SYNC CNF������ʱ�� */

    TI_WAS_CSELPC_BG_WAIT_NAS_CNF                           ,                   /* BG�����з���W2G��ѡ */

    TI_WAS_SYSHO_PCCO_WAIT_RRMM_EST_REQ                     ,                   /* G2W PCCO �ȴ�NAS����RRMM_EST_REQ������ʱ�� */
    TI_WAS_CU_WAIT_NAS_SUSPEND_RSP                          ,                   /* �ȴ�nas�ظ�rrmm suspend rsp�Ķ�ʱ��ʱ����10s */
    TI_WAS_CU_WAIT_NAS_RESUME_RSP                           ,                   /* �ȴ�nas�ظ�RRMM RESUME RSP��Ϣ�Ķ�ʱ�� */
    TI_WAS_CSELPC_WAIT_NAS_SUSPEND_RSP                      ,                   /* cselpc�ȴ�nas�ظ�RRMM SUSPEND RSP��Ϣ�Ķ�ʱ�� */
    TI_WAS_CSELPC_WAIT_NAS_RESUME_RSP                       ,                   /* cselpc�ȴ�nas�ظ�RRMM RESUME RSP��Ϣ�Ķ�ʱ�� */
    TI_WAS_SYSHO_WAIT_NAS_SUSPEND_RSP                       ,                   /* �ȴ�nas�ظ�RRMM SUSPEND RSP��Ϣ�Ķ�ʱ�� */

#if (FEATURE_ON == FEATURE_DSDS)
    TI_WAS_SYSHO_WAIT_RRM_RF_RES_APPLY_CNF                  ,                   /* �ȴ�RRM�ظ���Դ����CNF��Ϣ�Ķ�ʱ�� */

    TI_WAS_CSELPC_WAIT_PLMN_ID_SRCH_RES_APPLY_CNF           ,                   /* �ȴ�ָ������Դ������Ϣ��ʱʱ��60s */
    TI_WAS_CSELPC_WAIT_PLMN_LIST_SRCH_RES_APPLY_CNF         ,                   /* �ȴ�lIST����Դ������Ϣ��ʱʱ��5S */
    TI_WAS_CSELPC_WAIT_AS_SRCH_RES_APPLY_CNF                ,                   /* �ȴ�AS������Դ���볬��ʱ��10s */
    TI_WAS_CSELPC_WAIT_G_OR_L_RES_APPLY_CNF                 ,                   /* ��ϵͳ��ѡ�ȴ�G��L��AS������Դ���볬ʱʱ��5s */
#endif
    TI_WAS_CSELPC_WAIT_GAS_RESEL_TIMER_EXP_CNF              ,                   /* �ȴ� GAS �ظ� ֹͣ��ѡ��Ӧ�Ķ�ʱ�� */

    TI_WAS_SYSHO_WAIT_NAS_RESUME_RSP                        ,                   /* �ȴ�nas�ظ�RRMM RESUME RSP��Ϣ�Ķ�ʱ�� */
    TI_WAS_RRC_WAIT_NAS_SUSPEND_RSP                         ,                   /* �ȴ�nas�ظ�rrmm suspend rsp�Ķ�ʱ��ʱ����10s */
    TI_WAS_RRC_WAIT_NAS_RESUME_RSP                          ,                   /* ��nas�ظ�RRMM RESUME RSP��Ϣ�Ķ�ʱ�� */
    TI_WAS_CSELPC_OOS_REL_WAIT_NAS_MSG                      ,                   /* ����̬�����������յ�nas��rel req��Ϣ��rel all������״̬����ı�����ʱ�� */
    TI_WAS_CSELPC_WAIT_NETSCAN_CNF                          ,                   /*  CSELPC�ȴ�csel��������Ķ�ʱ�� */
    TI_WAS_CSEL_WAIT_GAS_MEAS_CNF                           ,                   /* CSEL IDLE/CONN̬�ȴ���������CNF��Ϣ��ʱ�� */

    TI_WAS_MAIN_WAIT_BG_SEARCH_STOP_CNF                     ,
    TI_WAS_CSELPC_OOS_SBM_DUAL_IMSI                        ,                   /* CSELPC������������˫imsi��Ķ�ʱ��60s */
    WAS_STATE_TI_BUTT
};
typedef VOS_UINT16 WAS_TI_ENUM_UINT16;

/*lint -e958 �޸���: shiweizhou �����ˣ��¹� ԭ���������ʱ����Ϣ�����޷��޸���Ϣ�ṹ */
typedef struct
{
   VOS_UINT8            ucType;
   VOS_UINT8            ucValid;
   VOS_UINT16           usRsv;
   WAS_TI_ENUM_UINT16   enName;
   VOS_UINT32           ulPara;
   VOS_UINT32           pNext;
   VOS_UINT32           pPrev;
   VOS_UINT8            aucData[24];
}WAS_TI_MSG_DATA;
/*_H2ASN_Length UINT32*/
/*lint +e958 �޸���: shiweizhou �����ˣ��¹� ԭ���������ʱ����Ϣ�����޷��޸���Ϣ�ṹ */

/*����ASN.1����ͷ*/

typedef struct
{
    VOS_MSG_HEADER
    WAS_TI_MSG_DATA   stMsgData;
}WasTimer_MSG;




/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/








#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of WasMntnMsg.h */
